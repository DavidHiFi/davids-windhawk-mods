// ==WindhawkMod==
// @id              seamless-title-bars
// @name            Seamless Title Bars
// @description     One title bar look everywhere: colours, caption buttons and native frames in every kind of app
// @version         1.0.0
// @author          DavidHiFi, Th3Fanbus, grn15RenS, Ingan121, Anixx, aubymori
// @homepage        https://github.com/DavidHiFi/davids-windhawk-mods
// @donateUrl       https://ko-fi.com/DavidHiFi
// @license         MIT
// @include         *
// @include         dwm.exe
// @include         windhawk.exe
// @architecture    x86-64
// @compilerOptions -lcomctl32 -luxtheme -lgdi32 -lshlwapi -ldwmapi -luser32 -lole32 -lshell32 -loleaut32 -lruntimeobject -lversion
// ==/WindhawkMod==

// ==WindhawkModReadme==
/*
# Seamless Title Bars

Every title bar mod you need, in one place. Pick a title bar colour, move and
restyle the caption buttons, and give Store apps, browsers, Office, Discord,
Spotify and Windows Terminal a proper Windows title bar. Each part has its own
switch, so you only turn on what you want.

![Seamless Title Bars preview](https://raw.githubusercontent.com/DavidHiFi/davids-windhawk-mods/main/media/previews/seamless-title-bars.png)

## Features
- **Colours.** One colour for focused and unfocused title bars, plus dark mode
  title bars. Apps with their own blur or custom bar can be left alone.
- **Caption buttons.** Move the buttons left or right, change their order,
  space them closer, or paint them as macOS circles or your own images.
- **Icon and title.** Center, left or right alignment, icon position, gaps,
  and hiding the icon or the title.
- **Button exclusions.** Apps and window classes that keep the normal layout.
- **File Explorer tabs.** Keeps the tab bar from covering moved buttons.
- **Store apps.** A normal Windows title bar in Settings, Calculator, Photos
  and other Store apps, with an optional blur.
- **Native frames.** The standard title bar in Chromium browsers, Office,
  Visual Studio, Teams, Discord and similar apps.
- **Spotify.** Native frames and a set of Spotify tweaks.
- **Terminal bar.** Gives the Windows Terminal title bar the same blur as its
  window.
- **Basic frames.** Correct caption text colours on classic and basic frames.

## Setup
- The caption buttons part runs inside dwm.exe. Windhawk loads it there
  because the mod names dwm.exe directly.
- The Terminal bar needs Terminal's own title bar (turn off "Show tabs in
  the title bar" in Terminal).

## Notes
- Switching the button style back to Windows takes effect after dwm.exe
  restarts (sign out and back in).
- Spotify options marked with * need a Spotify restart.
- Changing the native frames app list needs those apps restarted.

## Credits
This mod merges and keeps every option of:
- Windows 11 Custom Title Bar Colours by Th3Fanbus
- Caption Buttons Customizer by grn15RenS
- Remove UWP Title Bars Plus by DavidHiFi, based on Remove UWP Title Bars by Anixx
- Titlebar For Everyone and CEF/Spotify Tweaks by Ingan121
- Fix Basic Caption Text by aubymori
- Terminal Titlebar Blur by DavidHiFi
*/
// ==/WindhawkModReadme==

// ==WindhawkModSettings==
/*
- colours:
  - enabled: true
    $name: Turn on colours
    $description: "Sets the title bar colour in apps that use the Windows title bar. When off, apps keep their own colours."
  - useImmersiveDarkMode: true
    $name: Dark mode title bars
    $description: "When on, title bars use the dark caption style."
  - activeColor: "#1E1E2E"
    $name: Focused colour
    $description: "Title bar colour of the focused window, as a hex colour like #1E1E2E."
  - inactiveColor: "#1E1E2E"
    $name: Unfocused colour
    $description: "Title bar colour of other windows, as a hex colour."
  - excludedApps: "Discord*.exe, ESDDiscord.exe, FreeDictate.exe, chrome.exe, WindowsTerminal.exe, devenv.exe, windhawk-ui.exe"
    $name: Apps to leave alone
    $description: "Process names separated by commas; * works as a wildcard. These apps keep their own title bar (blur, custom bar) instead of a flat colour."
  $name: Colours
  $description: Title bar colour for standard Windows title bars.
- buttons:
  - enabled: true
    $name: Turn on caption buttons
    $description: "When off, the buttons, icon and title keep the Windows layout everywhere."
  - moveButtons: false
    $name: Move caption buttons to the left
    $description: "On = the buttons move to the left side. Off = they stay on the right."
  - leftMargin: 0
    $name: Left margin (px)
    $description: "Gap between the left window edge and the first button. 0 to 300 (Suggested: 0)."
  - buttonTighten: 0
    $name: Tighten button spacing (px)
    $description: "0 = normal spacing. Higher = buttons closer together, up to about 20. Meant for the circle and image styles."
  - order: minMaxClose
    $name: Button order
    $description: Order of the three buttons, counted from the left.
    $options:
    - closeMinMax: Close, minimize, maximize (macOS)
    - closeMaxMin: Close, maximize, minimize
    - minMaxClose: Minimize, maximize, close
  - showDialogClose: true
    $name: Show the close button on dialogs
    $description: "For windows that only have a close button. Off = the button is hidden; Alt+F4 and Esc still close the window."
  $name: Caption buttons
  $description: Position and order of the minimize, maximize and close buttons.
- buttonStyle:
  - style: windows
    $name: Button style
    $description: "Windows = the normal glyphs. macOS = coloured circles. Custom images = your own images. Going back to Windows needs a sign out and in."
    $options:
    - macos: macOS circles
    - custom: Custom images
    - windows: Windows default
  - minimizeColor: "#FEBC2E"
    $name: Minimize colour
    $description: "Hex colour of the minimize circle, like #FEBC2E."
  - maximizeColor: "#28C840"
    $name: Maximize colour
    $description: "Hex colour of the maximize and restore circle, like #28C840."
  - closeColor: "#FF5F57"
    $name: Close colour
    $description: "Hex colour of the close circle, like #FF5F57."
  - iconFolder: ""
    $name: Image folder
    $description: "Custom images style only. A folder with minimize, restore, maximize and close images (.png, .jpg, .bmp). Optional extras: close_hover, close_pressed, close_disabled."
  - minimizeIcon: ""
    $name: Minimize image
    $description: Optional full path to an image. Overrides the folder for this button.
  - maximizeIcon: ""
    $name: Maximize image
    $description: Optional full path to an image. Overrides the folder for this button.
  - restoreIcon: ""
    $name: Restore image
    $description: Optional full path to an image, used while the window is maximized.
  - closeIcon: ""
    $name: Close image
    $description: Optional full path to an image. Overrides the folder for this button.
  - restartDwmOnUnload: false
    $name: Restart dwm.exe when the mod unloads
    $description: "Off (suggested): painted buttons stay until dwm.exe restarts. On: dwm.exe restarts when the mod unloads; the screen flickers once and apps stay open."
  $name: Button style
  $description: How the caption buttons look.
- title:
  - titleAlign: center
    $name: Icon and title alignment
    $description: "Where the icon and title sit. Left = right after the buttons."
    $options:
    - left: Left
    - center: Center
    - right: Right
  - dialogAlign: center
    $name: Alignment in dialogs
    $description: Same as above, for windows that only have a close button.
    $options:
    - left: Left
    - center: Center
    - right: Right
  - centerOnText: true
    $name: Center the title text itself
    $description: "On = the text is centered and the icon sits beside it. Off = the icon and text are centered as a group."
  - centerNudge: 0
    $name: Center fine-tune (px)
    $description: "Positive moves the centered title right, negative moves it left. -300 to 300 (Suggested: 0)."
  - iconPosition: beforeTitle
    $name: Icon position
    $description: Where the window icon goes.
    $options:
    - beforeTitle: Left of the title
    - afterTitle: Right of the title
    - farLeft: Far left
    - farRight: Far right
  - titleGap: 8
    $name: Gap after buttons (px)
    $description: "Space between the last button and the icon and title. 0 to 300 (Suggested: 8)."
  - iconTitleGap: 5
    $name: Gap between icon and title (px)
    $description: "0 to 100 (Suggested: 5)."
  - rightEdgeGap: 8
    $name: Right edge gap (px)
    $description: "Space between the right window edge and the icon and title. 0 to 100 (Suggested: 8)."
  - hideMode: off
    $name: Hide icon or title
    $description: Choose what to hide in the title bar.
    $options:
    - off: Show both
    - icon: Hide the icon
    - title: Hide the title
    - both: Hide both
  - iconClickable: true
    $name: Icon opens the window menu
    $description: "On = click opens the window menu and double-click closes. Off = the icon acts like empty title bar space."
  $name: Icon and title
  $description: Where the window icon and title text go.
- exclusions:
  - excludedApps: ""
    $name: Apps that keep normal buttons
    $description: "Process names separated by commas. Every window of these apps keeps the Windows button layout."
  - excludedClasses: "CabinetWClass"
    $name: Window classes that keep normal buttons
    $description: "Window class names separated by commas. CabinetWClass is File Explorer; remove it to move File Explorer's buttons too."
  $name: Button exclusions
  $description: Apps and windows that keep the normal button layout.
- explorerTabs:
  - enabled: true
    $name: Clickable buttons in File Explorer
    $description: "On = moved buttons can be clicked in File Explorer. Needs buttons on the left and CabinetWClass not excluded."
  - buttonsExtraMargin: 5
    $name: Extra button margin in File Explorer (px)
    $description: "Moves the buttons right in File Explorer only. -50 to 300 (Suggested: 5)."
  - extraPx: 0
    $name: Shift tab bar and toolbar (px)
    $description: "0 = leave them in place. About 145 clears the three buttons. -300 to 300."
  $name: File Explorer tabs
  $description: Keeps the File Explorer tab bar from covering the buttons.
- uwp:
  - enabled: true
    $name: Turn on Store apps
    $description: "Normal Windows title bars in Store apps like Settings and Calculator. Turning off puts open windows back the way they were."
  - blur: true
    $name: Blur
    $description: Frosted blur title bars instead of a flat colour.
  - tint: 60
    $name: Tint strength
    $description: "How much dark tint covers the blur. 0 to 100 (Suggested: 60)."
  $name: Store apps
  $description: Native title bars in Store (UWP) apps.
- nativeFrames:
  - enabled: true
    $name: Turn on native frames
    $description: "The standard Windows title bar in browsers, Office, Visual Studio, Discord and similar apps. Changes need those apps restarted."
  - apps: "chrome.exe, brave.exe, msedge.exe, opera.exe, yandex.exe, whale.exe, supermium.exe, chromium.exe, devenv.exe, PowerToys.*.exe, olk.exe, WebViewHost.exe, winword.exe, excel.exe, powerpnt.exe, msaccess.exe, onenote.exe, outlook.exe, mspub.exe, hwp.exe, Photos.exe, MuseScore*.exe, ms-teams.exe, Discord.exe, DiscordPTB.exe, DiscordCanary.exe, DiscordDevelopment.exe"
    $name: Apps
    $description: "Process names separated by commas; * works as a wildcard. Add steamwebhelper.exe for Steam."
  - buttonFaceChrome: true
    $name: Chromium - classic button face colour
    $description: "Paints the classic Windows button face colour behind the Chromium title and tab bar. Needs DWM frames, hardware acceleration and 'Windows 11 Mica titlebar' in chrome://flags."
  - clientEdge: remove
    $name: Client edge
    $description: The thin sunken border around the window content.
    $options:
    - keep: Keep the app's choice
    - add: Always show
    - remove: Always hide
  - steamToolFrames: true
    $name: Steam - hide tool window frames
    $description: Removes the frames of Steam's small tool windows.
  - steamNoScriptInject: true
    $name: Steam - turn off script injection
    $description: "Only turn on for the Change Window Parameters Millennium extension. Needs a Steam restart."
  $name: Native frames
  $description: The standard Windows title bar in apps that draw their own.
- spotify:
  - enabled: true
    $name: Turn on Spotify
    $description: Native frames and tweaks for Spotify. Options marked with * need a Spotify restart.
  - showframe: true
    $name: Native frame on the main window*
    $description: Needs a Spotify restart.
  - showframeonothers: true
    $name: Native frames on other windows
    $description: Miniplayer, DevTools and similar windows.
  - showmenu: true
    $name: Show the menu button*
    $description: When off, the Alt key no longer opens the Spotify menu either.
  - showcontrols: false
    $name: Show Spotify's own window buttons*
    $description: The buttons Spotify draws next to its title bar.
  - transparentcontrols: true
    $name: Transparent Spotify window buttons
    $description: Makes Spotify's own window buttons see-through.
  - transparentrendering: true
    $name: Transparent rendering*
    $description: Makes see-through parts of the page really see-through. Needs the Chrome runtime.
  - noforceddarkmode: false
    $name: Turn off forced dark mode*
    $description: Stops Spotify from forcing dark mode.
  - forceextensions: true
    $name: Force Chrome extensions*
    $description: Always turns on Chrome extensions. Needs the Chrome runtime.
  - blockupdates: false
    $name: Block automatic updates*
    $description: Stops Spotify from updating itself.
  - ignoreminsize: true
    $name: Ignore minimum window size
    $description: Lets the window shrink below Spotify's minimum size.
  - playbackspeed: "1"
    $name: (Old) Playback speed
    $description: "A number like 1.0. Only works on x64 Spotify 1.2.36 to 1.2.66."
  - allowuntested: false
    $name: (Advanced) Unsafe methods on untested versions*
    $description: May crash Spotify. When off, a slower safe method is used.
  $name: Spotify
  $description: Native frames and tweaks for Spotify.
- terminalBar:
  - enabled: true
    $name: Turn on Terminal bar
    $description: "Gives the Windows Terminal title bar the same blur as its window. Needs Terminal's own title bar (Show tabs in the title bar off)."
  - tint: "#1e1e2e"
    $name: Tint colour
    $description: "Colour mixed into the blur, like #1e1e2e. Use your Terminal background colour."
  - opacity: 85
    $name: Tint opacity
    $description: "How strong the tint is. 0 to 100 (Suggested: match Terminal's opacity)."
  $name: Terminal bar
  $description: Matches the Windows Terminal title bar to its blurred window.
- basicFrames:
  - enabled: false
    $name: Turn on basic frames
    $description: "Fixes caption text colours on windows without DWM frames (classic themes, ribbon text). Off by default: on some Windows builds the parts it needs are missing, and then it simply stays inactive."
  - smallIcons: true
    $name: Small window icons
    $description: Uses the small icon on basic frames instead of shrinking the large one.
  $name: Basic frames
  $description: Correct caption colours on basic and classic frames.
- debugLog: false
  $name: Write debug log
  $description: Extra caption button messages in the Windhawk log. Turn on logging for this mod to see them.
*/
// ==/WindhawkModSettings==

#include <windows.h>
#include <windhawk_utils.h>
#include <commctrl.h>
#include <tlhelp32.h>
#include <wincodec.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <wchar.h>
#include <regex>
#include <string_view>
#include <unordered_map>
#include <algorithm>
#include <string>
#include <utility>
#include <vector>
#include <dwmapi.h>
#include <propsys.h>
#include <roapi.h>
#include <shlobj.h>
#include <windowsx.h>
#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.System.h>
#include <winrt/Windows.UI.Composition.Desktop.h>
#include <winrt/Windows.UI.Composition.h>
#include <windhawk_api.h>
#include <shlwapi.h>
#include <uxtheme.h>
#include <cwchar>
#include <fstream>
#include <sstream>
#include <libloaderapi.h>
#include <cmath>
#include <condition_variable>
#include <cstdint>
#include <thread>
#include <mutex>
#include <optional>
#include <chrono>
#include <atomic>
#include <aclapi.h>
#include <sddl.h>
#include <set>

// ==========================================================================
//  Caption buttons, icon and title (dwm.exe, explorer.exe)
// ==========================================================================
namespace caption {
// ======================================================================
//  PART 1: Layout (caption buttons on the left, icon and title layout)
// ======================================================================

static struct {
    int leftMargin, order, tighten;
    bool moveButtons, moveTitle;
    int titleAlign, iconPosition, iconSide, titleGap, iconTitleGap, rightEdgeGap;
    int explorerMargin;
    bool centerOnText;
    int centerNudge;
    bool hideIcon, hideTitle, debugLog;
    bool showDialogClose;
    bool iconClickable;
    int dialogAlign;
} g_settings;

// Alignment correction (px) for windows that only have a close button
// (About Windows, message boxes, Run, ...). Not user-configurable.
static const int kCloseOnlyOffset = -1;

// Set while the mod is being unloaded: layouts are no longer changed, windows go back to default
static volatile LONG g_unloading = 0;
static volatile LONG g_unloadRelayouts = 0;

static int Clamp(int v, int lo, int hi) { return v < lo ? lo : (v > hi ? hi : v); }

// Left margin of the caption buttons; File Explorer gets an extra margin.
static int EffLeftMargin(HWND hwnd) {
    int m = g_settings.leftMargin;
    if (hwnd) {
        wchar_t c[64] = L"";
        GetClassNameW(hwnd, c, 64);
        if (wcscmp(c, L"CabinetWClass") == 0) m += g_settings.explorerMargin;
    }
    return m;
}

// Overlap (px) between neighbouring caption buttons for the given DPI.
// midW = width of the middle button; the overlap is capped so it stays usable.
static int TightenPx(int dpi, int midW) {
    if (g_settings.tighten <= 0) return 0;
    int T = MulDiv(g_settings.tighten, dpi, 96);
    int maxT = (midW - 6) / 2;
    if (T > maxT) T = maxT;
    return T < 0 ? 0 : T;
}

// True when the layout depends on the measured width of the title text
// (centered/right title, or the icon placed to the right of the title).
static bool TitleWidthMatters() {
    return g_settings.titleAlign != 0 || g_settings.dialogAlign >= 2 ||
           (g_settings.iconPosition == 0 && g_settings.iconSide == 1);
}

// Keys of the dropdown settings, in the same order as the numbers used in the code
static const wchar_t* const kOrderKeys[]   = { L"closeMinMax", L"closeMaxMin", L"minMaxClose" };
static const wchar_t* const kAlignKeys[]   = { L"left", L"center", L"right" };
static const wchar_t* const kIconPosKeys[] = { L"beforeTitle", L"afterTitle", L"farLeft", L"farRight" };

// Reads a dropdown setting and returns the index of its key in 'keys' (0 if unknown)
static int GetChoice(const wchar_t* setting, const wchar_t* const* keys, int n) {
    PCWSTR v = Wh_GetStringSetting(setting);
    int r = 0;
    if (v) {
        for (int i = 0; i < n; i++) {
            if (wcscmp(v, keys[i]) == 0) { r = i; break; }
        }
    }
    Wh_FreeStringSetting(v);
    return r;
}

static void LoadExclusions();

static void LoadSettings() {
    g_settings.moveButtons = Wh_GetIntSetting(L"buttons.moveButtons") != 0;
    g_settings.leftMargin = Clamp(Wh_GetIntSetting(L"buttons.leftMargin"), 0, 300);
    g_settings.tighten = Clamp(Wh_GetIntSetting(L"buttons.buttonTighten"), 0, 40);
    g_settings.explorerMargin = Clamp(Wh_GetIntSetting(L"explorerTabs.buttonsExtraMargin"), -50, 300);
    g_settings.order = GetChoice(L"buttons.order", kOrderKeys, 3);
    g_settings.showDialogClose = Wh_GetIntSetting(L"buttons.showDialogClose") != 0;

    g_settings.moveTitle = true;  // fixed: icon/title are always repositioned
    g_settings.titleAlign = GetChoice(L"title.titleAlign", kAlignKeys, 3);
    // dialogAlign is stored as 1..3 (0 would mean "same as general", no longer offered)
    g_settings.dialogAlign = GetChoice(L"title.dialogAlign", kAlignKeys, 3) + 1;
    g_settings.centerOnText = Wh_GetIntSetting(L"title.centerOnText") != 0;
    g_settings.centerNudge = Clamp(Wh_GetIntSetting(L"title.centerNudge"), -300, 300);

    // One dropdown, two internal values:
    // iconPosition: 0 = next to the title, 1 = far left, 2 = far right
    // iconSide: 0 = icon left of the title, 1 = icon right of the title
    int ip = GetChoice(L"title.iconPosition", kIconPosKeys, 4);
    g_settings.iconPosition = (ip <= 1) ? 0 : ip - 1;
    g_settings.iconSide = (ip == 1) ? 1 : 0;

    g_settings.titleGap = Clamp(Wh_GetIntSetting(L"title.titleGap"), 0, 300);
    g_settings.iconTitleGap = Clamp(Wh_GetIntSetting(L"title.iconTitleGap"), 0, 100);
    g_settings.rightEdgeGap = Clamp(Wh_GetIntSetting(L"title.rightEdgeGap"), 0, 100);

    // Hide dropdown: off / icon / title / both
    PCWSTR hm = Wh_GetStringSetting(L"title.hideMode");
    g_settings.hideIcon = hm && (wcscmp(hm, L"icon") == 0 || wcscmp(hm, L"both") == 0);
    g_settings.hideTitle = hm && (wcscmp(hm, L"title") == 0 || wcscmp(hm, L"both") == 0);
    Wh_FreeStringSetting(hm);

    g_settings.iconClickable = Wh_GetIntSetting(L"title.iconClickable") != 0;
    g_settings.debugLog = Wh_GetIntSetting(L"debugLog") != 0;

    LoadExclusions();
}

// ---------------- logging ----------------
static int g_logCount = 0;
static int g_hitLogCount = 0;
static wchar_t g_lastLog[800] = L"";
static wchar_t g_lastHitLog[300] = L"";

static void WriteLogLine(const wchar_t* line) {
    Wh_Log(L"%s", line);
}

static void DebugLog(const wchar_t* fmt, ...) {
    if (!g_settings.debugLog || g_logCount >= 600) return;
    wchar_t buf[800];
    va_list args;
    va_start(args, fmt);
    _vsnwprintf(buf, 799, fmt, args);
    va_end(args);
    buf[799] = 0;
    if (wcscmp(buf, g_lastLog) == 0) return;
    wcscpy(g_lastLog, buf);
    g_logCount++;
    WriteLogLine(buf);
}

static void HitLog(const wchar_t* fmt, ...) {
    if (!g_settings.debugLog || g_hitLogCount >= 200) return;
    wchar_t buf[300];
    va_list args;
    va_start(args, fmt);
    _vsnwprintf(buf, 299, fmt, args);
    va_end(args);
    buf[299] = 0;
    if (wcscmp(buf, g_lastHitLog) == 0) return;
    wcscpy(g_lastHitLog, buf);
    g_hitLogCount++;
    WriteLogLine(buf);
}

// ---------------- excluded apps ----------------
// Two lists: process names (e.g. notepad.exe) and window class names (e.g. CabinetWClass).
// Classes allow excluding specific windows only: explorer.exe hosts File Explorer
// (CabinetWClass) but also the Run/Properties dialogs (#32770).
static SRWLOCK g_exclLock = SRWLOCK_INIT;
static wchar_t g_exclExe[32][128];
static int g_exclExeN = 0;
static wchar_t g_exclCls[32][128];
static int g_exclClsN = 0;

// Per-HWND result cache (pid is checked too, so a reused HWND is not misjudged)
struct ExclCache { HWND hwnd; DWORD pid; bool excluded; };
static ExclCache g_exclCache[128];
static int g_exclCacheNext = 0;

// Split "a, b; c" into a list. exeNames = true: strip the path and add ".exe" when there is no dot.
static int ParseList(PCWSTR s, wchar_t (*out)[128], int maxN, bool exeNames) {
    int n = 0;
    if (!s) return 0;
    const wchar_t* p = s;
    while (*p && n < maxN) {
        while (*p == L' ' || *p == L',' || *p == L';' || *p == L'\t' || *p == L'\r' || *p == L'\n') p++;
        const wchar_t* st = p;
        while (*p && *p != L',' && *p != L';' && *p != L'\r' && *p != L'\n') p++;
        const wchar_t* en = p;
        while (en > st && (en[-1] == L' ' || en[-1] == L'\t')) en--;
        int len = (int)(en - st);
        if (len <= 0) continue;
        if (len > 120) len = 120;
        memcpy(out[n], st, (size_t)len * sizeof(wchar_t));
        out[n][len] = 0;
        if (exeNames) {
            wchar_t* b = wcsrchr(out[n], L'\\');
            if (b) memmove(out[n], b + 1, (wcslen(b + 1) + 1) * sizeof(wchar_t));
            if (!wcschr(out[n], L'.')) wcsncat(out[n], L".exe", 127 - wcslen(out[n]));
        }
        n++;
    }
    return n;
}

// Exe name from a pid. OpenProcess is often denied for dwm.exe, so fall back to a process snapshot.
static bool GetExeNameForPid(DWORD pid, wchar_t* out, size_t cap) {
    out[0] = 0;
    HANDLE h = OpenProcess(PROCESS_QUERY_LIMITED_INFORMATION, FALSE, pid);
    if (h) {
        wchar_t path[MAX_PATH];
        DWORD len = MAX_PATH;
        bool ok = QueryFullProcessImageNameW(h, 0, path, &len) != FALSE;
        CloseHandle(h);
        if (ok) {
            const wchar_t* exe = wcsrchr(path, L'\\');
            exe = exe ? exe + 1 : path;
            wcsncpy(out, exe, cap - 1);
            out[cap - 1] = 0;
            return true;
        }
    }
    HANDLE snap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (snap == INVALID_HANDLE_VALUE) return false;
    PROCESSENTRY32W pe = {};
    pe.dwSize = sizeof(pe);
    bool found = false;
    if (Process32FirstW(snap, &pe)) {
        do {
            if (pe.th32ProcessID == pid) {
                wcsncpy(out, pe.szExeFile, cap - 1);
                out[cap - 1] = 0;
                found = true;
                break;
            }
        } while (Process32NextW(snap, &pe));
    }
    CloseHandle(snap);
    return found;
}

static void LoadExclusions() {
    PCWSTR a = Wh_GetStringSetting(L"exclusions.excludedApps");
    PCWSTR c = Wh_GetStringSetting(L"exclusions.excludedClasses");
    AcquireSRWLockExclusive(&g_exclLock);
    g_exclExeN = ParseList(a, g_exclExe, 32, true);
    g_exclClsN = ParseList(c, g_exclCls, 32, false);
    memset(g_exclCache, 0, sizeof(g_exclCache));
    g_exclCacheNext = 0;
    int nExe = g_exclExeN, nCls = g_exclClsN;
    ReleaseSRWLockExclusive(&g_exclLock);
    Wh_FreeStringSetting(a);
    Wh_FreeStringSetting(c);
    DebugLog(L"[Exclusions] process list=%d class list=%d", nExe, nCls);
}

static bool IsHwndExcluded(HWND hwnd) {
    if (!hwnd) return false;
    DWORD pid = 0;
    GetWindowThreadProcessId(hwnd, &pid);
    if (!pid) return false;

    AcquireSRWLockShared(&g_exclLock);
    int nExe = g_exclExeN, nCls = g_exclClsN;
    for (int i = 0; i < 128; i++) {
        if (g_exclCache[i].hwnd == hwnd && g_exclCache[i].pid == pid) {
            bool r = g_exclCache[i].excluded;
            ReleaseSRWLockShared(&g_exclLock);
            return r;
        }
    }
    ReleaseSRWLockShared(&g_exclLock);
    if (nExe == 0 && nCls == 0) return false;

    wchar_t cls[128] = L"";
    GetClassNameW(hwnd, cls, 128);
    wchar_t exe[128] = L"";
    bool haveExe = (nExe > 0) && GetExeNameForPid(pid, exe, 128);

    bool excluded = false;
    AcquireSRWLockExclusive(&g_exclLock);
    if (haveExe) {
        for (int i = 0; i < g_exclExeN && !excluded; i++)
            if (_wcsicmp(exe, g_exclExe[i]) == 0) excluded = true;
    }
    for (int i = 0; i < g_exclClsN && !excluded; i++)
        if (_wcsicmp(cls, g_exclCls[i]) == 0) excluded = true;
    ExclCache& e = g_exclCache[g_exclCacheNext];
    g_exclCacheNext = (g_exclCacheNext + 1) % 128;
    e.hwnd = hwnd;
    e.pid = pid;
    e.excluded = excluded;
    ReleaseSRWLockExclusive(&g_exclLock);

    DebugLog(L"[ExclCheck] hwnd=%p pid=%lu exe=%s class=%s excluded=%d", hwnd, (unsigned long)pid, exe, cls, (int)excluded);
    return excluded;
}

// ---------------- dynamic APIs ----------------
typedef UINT (WINAPI *GetDpiForWindow_t)(HWND);
typedef UINT (WINAPI *GetDpiForSystem_t)(void);
typedef BOOL (WINAPI *SPIForDpi_t)(UINT, UINT, PVOID, UINT, UINT);
static GetDpiForWindow_t g_pGetDpiForWindow = nullptr;
static GetDpiForSystem_t g_pGetDpiForSystem = nullptr;
static SPIForDpi_t g_pSPIForDpi = nullptr;
typedef int  (WINAPI *InternalGetWindowText_t)(HWND, LPWSTR, int);
typedef BOOL (WINAPI *IsHungAppWindow_t)(HWND);
static InternalGetWindowText_t g_pInternalGetWindowText = nullptr;
static IsHungAppWindow_t g_pIsHungAppWindow = nullptr;

static const unsigned kHashUnsafe = 0xFFFFFFFFu;

// Reads the title WITHOUT sending any message to the window (safe on the DWM thread).
// Returns -1 when the window is hung or the API is unavailable.
static int SafeGetWindowText(HWND hwnd, wchar_t* buf, int cap) {
    if (!hwnd || !g_pInternalGetWindowText) return -1;
    DWORD pid = 0;
    GetWindowThreadProcessId(hwnd, &pid);
    // Ghost windows belong to dwm.exe itself: reading their text never blocks.
    if (pid != GetCurrentProcessId() && g_pIsHungAppWindow && g_pIsHungAppWindow(hwnd)) return -1;
    return g_pInternalGetWindowText(hwnd, buf, cap);
}

static int MeasureTitleWidth(HWND hwnd, int dpi) {
    if (!hwnd || !g_pSPIForDpi) return -1;
    wchar_t text[300] = {};
    int n = SafeGetWindowText(hwnd, text, 300);
    if (n < 0) return -1;   // hung / unavailable: caller falls back to the safe left layout
    if (n == 0) return 0;
    NONCLIENTMETRICSW ncm = {};
    ncm.cbSize = sizeof(ncm);
    if (!g_pSPIForDpi(SPI_GETNONCLIENTMETRICS, sizeof(ncm), &ncm, 0, dpi)) return -1;
    HFONT font = CreateFontIndirectW(&ncm.lfCaptionFont);
    if (!font) return -1;
    int result = -1;
    HDC dc = CreateCompatibleDC(nullptr);
    if (dc) {
        HGDIOBJ old = SelectObject(dc, font);
        SIZE sz = {};
        if (GetTextExtentPoint32W(dc, text, n, &sz)) result = sz.cx;
        SelectObject(dc, old);
        DeleteDC(dc);
    }
    DeleteObject(font);
    return result;
}

static unsigned HashWindowText(HWND hwnd) {
    if (!hwnd) return 0;
    wchar_t t[300] = {};
    int n = SafeGetWindowText(hwnd, t, 300);
    if (n < 0) return kHashUnsafe;
    unsigned h = 2166136261u;
    for (int i = 0; i < n; i++) {
        h ^= (unsigned)t[i];
        h *= 16777619u;
    }
    return h ^ (unsigned)n;
}

// ---------------- original function pointers ----------------
typedef void (*GetTitleBarInfo_t)(void*, TITLEBARINFOEX*, bool*);
typedef long (*UpdateNCAreaButton_t)(void*, int, int, int, int*);
typedef long (*PosAndSizes_t)(void*);
typedef void (*SetInset_t)(void*, int);
typedef bool (*DoHitTest_t)(void*, const POINT*, void**, unsigned int*);

static GetTitleBarInfo_t GetTitleBarInfo_Orig;
static UpdateNCAreaButton_t UpdateNCAreaButton_Orig;
static PosAndSizes_t PosAndSizes_Orig;
static SetInset_t SetInsetTop_Orig, SetInsetLeft_Orig, SetInsetRight_Orig;
static DoHitTest_t DoHitTest_Orig;
static bool g_hasPosHook = false;

// ---------------- HWND of a CTopLevelWindow, taken from DWM's own data ----------------
// CTopLevelWindow::GetWindowData() returns a CWindowData*, which stores the HWND.
// The offset of that member is derived at init from CWindowData::IsGhostWindow
// (see DeriveHwndOffset); if it can't be derived, no HWND is available.
typedef void* (WINAPI *GetWindowData_t)(void*);
static GetWindowData_t GetWindowData_Orig;
static void* IsGhostWindow_Func;
static size_t g_hwndOffset = SIZE_MAX;

static size_t OffsetFromAssemblyRegex(void* func, size_t defValue, const std::regex& re, int limit) {
    BYTE* p = (BYTE*)func;
    for (int i = 0; i < limit; i++) {
        WH_DISASM_RESULT result;
        if (!Wh_Disasm(p, &result)) break;
        p += result.length;
        std::string_view s = result.text;
        if (s == "ret") break;
        std::match_results<std::string_view::const_iterator> match;
        if (std::regex_match(s.begin(), s.end(), match, re)) {
            return std::stoull(match[1], nullptr, 16);
        }
    }
    Wh_Log(L"HWND offset: pattern not found in %p", func);
    return defValue;
}

static void DeriveHwndOffset() {
    if (!IsGhostWindow_Func || !GetWindowData_Orig) {
        Wh_Log(L"HWND lookup unavailable: GetWindowData or IsGhostWindow symbol not found");
        return;
    }
    // IsGhostWindow loads this->hwnd as its first argument to GetPropW, so the first
    // load whose base register is the `this` pointer (rcx on x64, x0 on ARM64) is the HWND member.
    g_hwndOffset = OffsetFromAssemblyRegex(
        IsGhostWindow_Func, SIZE_MAX,
#if defined(_M_X64)
        std::regex(R"(mov \w+, \[rcx\+0x([0-9a-f]+)\])", std::regex_constants::icase),
#elif defined(_M_ARM64)
        std::regex(R"(ldr\s+\w+, \[x0, #0x([0-9a-f]+)\])", std::regex_constants::icase),
#else
#error "Unsupported architecture"
#endif
        10);
    Wh_Log(L"CWindowData HWND offset = 0x%zx", g_hwndOffset);
}

static HWND HwndFromTopLevelWindow(void* pThis) {
    if (g_hwndOffset == SIZE_MAX || !GetWindowData_Orig || !pThis) return nullptr;
    void* data = GetWindowData_Orig(pThis);
    if (!data) return nullptr;
    HWND h = *(HWND*)((BYTE*)data + g_hwndOffset);
    return IsWindow(h) ? h : nullptr;
}

// ---------------- per-window button rectangles (window-local X) ----------------
struct WinLayout { HWND hwnd; int left[4]; int right[4]; int band; bool valid; bool iconSet; int iconL, iconR; };
// One entry per CTopLevelWindow that this mod has laid out. No size limit: an entry is
// only dropped when its window is gone (see StoreWinLayout).
static std::unordered_map<void*, WinLayout> g_winLayouts;
static SRWLOCK g_layoutLock = SRWLOCK_INIT;

static void StoreWinLayout(void* win, const int* l, const int* r, int band, HWND hwnd) {
    AcquireSRWLockExclusive(&g_layoutLock);
    auto it = g_winLayouts.find(win);
    if (it == g_winLayouts.end()) {
        // A new window: forget the entries of windows that are gone
        for (auto p = g_winLayouts.begin(); p != g_winLayouts.end();) {
            if (!p->second.valid || (p->second.hwnd && !IsWindow(p->second.hwnd)))
                p = g_winLayouts.erase(p);
            else
                ++p;
        }
        it = g_winLayouts.emplace(win, WinLayout{}).first;
    }
    WinLayout& e = it->second;
    for (int t = 1; t <= 3; t++) { e.left[t] = l[t]; e.right[t] = r[t]; }
    e.hwnd = hwnd;
    e.band = band;
    e.valid = true;
    e.iconSet = false; e.iconL = 0; e.iconR = 0;
    ReleaseSRWLockExclusive(&g_layoutLock);
}

static void ClearWinLayout(void* win) {
    AcquireSRWLockExclusive(&g_layoutLock);
    auto it = g_winLayouts.find(win);
    if (it != g_winLayouts.end()) it->second.valid = false;
    ReleaseSRWLockExclusive(&g_layoutLock);
}

static bool GetWinLayout(void* win, int* l, int* r, int* band) {
    bool ok = false;
    AcquireSRWLockShared(&g_layoutLock);
    auto it = g_winLayouts.find(win);
    if (it != g_winLayouts.end() && it->second.valid) {
        for (int t = 1; t <= 3; t++) { l[t] = it->second.left[t]; r[t] = it->second.right[t]; }
        *band = it->second.band;
        ok = true;
    }
    ReleaseSRWLockShared(&g_layoutLock);
    return ok;
}

static void SetWinIcon(void* win, bool visible, int l, int r) {
    AcquireSRWLockExclusive(&g_layoutLock);
    auto it = g_winLayouts.find(win);
    if (it != g_winLayouts.end()) {
        it->second.iconSet = true;
        it->second.iconL = visible ? l : 0;
        it->second.iconR = visible ? r : 0;
    }
    ReleaseSRWLockExclusive(&g_layoutLock);
}

static bool GetWinIcon(void* win, int* l, int* r) {
    bool set = false;
    AcquireSRWLockShared(&g_layoutLock);
    auto it = g_winLayouts.find(win);
    if (it != g_winLayouts.end() && it->second.valid && it->second.iconSet) {
        *l = it->second.iconL; *r = it->second.iconR; set = true;
    }
    ReleaseSRWLockShared(&g_layoutLock);
    return set;
}

static HWND GetWinHwnd(void* win) {
    HWND h = nullptr;
    AcquireSRWLockShared(&g_layoutLock);
    auto it = g_winLayouts.find(win);
    if (it != g_winLayouts.end() && it->second.valid) h = it->second.hwnd;
    ReleaseSRWLockShared(&g_layoutLock);
    return h;
}

// ---------------- per-window title-text state ----------------
struct HwndCache { void* win; HWND hashHwnd; unsigned hash; bool hasHash; };
static HwndCache g_hwndCache[64];
static int g_hwndCacheNext = 0;
static SRWLOCK g_hwndLock = SRWLOCK_INIT;

static HwndCache* FindOrCreateCacheLocked(void* win) {
    for (int i = 0; i < 64; i++) {
        if (g_hwndCache[i].win == win) return &g_hwndCache[i];
    }
    HwndCache* e = &g_hwndCache[g_hwndCacheNext];
    g_hwndCacheNext = (g_hwndCacheNext + 1) % 64;
    *e = HwndCache{};
    e->win = win;
    return e;
}

static void SetTitleState(void* win, HWND hashHwnd, unsigned hash) {
    AcquireSRWLockExclusive(&g_hwndLock);
    HwndCache* e = FindOrCreateCacheLocked(win);
    e->hashHwnd = hashHwnd;
    e->hash = hash;
    e->hasHash = true;
    ReleaseSRWLockExclusive(&g_hwndLock);
}

static bool GetTitleState(void* win, HWND* hashHwnd, unsigned* hash) {
    bool ok = false;
    AcquireSRWLockShared(&g_hwndLock);
    for (int i = 0; i < 64; i++) {
        if (g_hwndCache[i].win == win && g_hwndCache[i].hasHash) {
            *hashHwnd = g_hwndCache[i].hashHwnd;
            *hash = g_hwndCache[i].hash;
            ok = true;
            break;
        }
    }
    ReleaseSRWLockShared(&g_hwndLock);
    return ok;
}

// ---------------- per-sequence state ----------------
struct VisEntry { void* v; int top; int left; bool hasTop; bool hasLeft; };

struct Seq {
    bool valid;
    bool active;
    bool done;
    bool closeOnly;
    int outBefore[4];
    int w[4];
    int origFinalOut;
    int buttonEnd;
    int rightMargin;
    int winW;
    int dpi;
    HWND hwnd;
    void* win;
    int count;
    VisEntry vis[6];
};

static thread_local Seq t_seq;
static thread_local int t_posDepth;
static thread_local bool t_relayout;
static void* g_lastTitleVis = nullptr;

static VisEntry* FindEntry(void* v) {
    for (int i = 0; i < t_seq.count; i++)
        if (t_seq.vis[i].v == v) return &t_seq.vis[i];
    return nullptr;
}

static VisEntry* GetEntry(void* v) {
    VisEntry* e = FindEntry(v);
    if (e) return e;
    if (t_seq.count >= 6) return nullptr;
    e = &t_seq.vis[t_seq.count++];
    *e = VisEntry{};
    e->v = v;
    return e;
}

// ---------------- title/icon repositioning ----------------
// Alignment for the window being laid out: close-only windows (dialogs) can
// override the general setting. dialogAlign: 0 = general, 1..3 = left/center/right.
static int EffTitleAlign() {
    if (t_seq.closeOnly && g_settings.dialogAlign > 0) return g_settings.dialogAlign - 1;
    return g_settings.titleAlign;
}

static bool RepositionTitle(VisEntry* title) {
    VisEntry* icon = nullptr;
    for (int i = 0; i < t_seq.count; i++) {
        VisEntry* e = &t_seq.vis[i];
        if (e != title && e->hasLeft) { icon = e; break; }
    }
    g_lastTitleVis = title->v;

    int dpi = t_seq.dpi > 0 ? t_seq.dpi : 96;
    int iconW = MulDiv(16, dpi, 96);
    bool origHasIcon = icon && (title->left > icon->left + 4);

    int aL = t_seq.buttonEnd + g_settings.titleGap;
    int aR = t_seq.winW - t_seq.rightMargin - g_settings.rightEdgeGap;
    int gap = g_settings.iconTitleGap;

    // Very narrow window: no room next to the buttons -> hide icon and title
    bool noRoom = (aR - aL) < 24;
    bool showIcon = origHasIcon && !g_settings.hideIcon && !noRoom;
    bool showTitle = !g_settings.hideTitle && !noRoom;

    // Icon position: 0 = next to the title, 1 = far left, 2 = far right.
    // A "far" icon is detached from the title, so the title can be centered alone.
    int iconPos = g_settings.iconPosition;
    bool iconFar = showIcon && iconPos != 0;
    bool iconInGroup = showIcon && !iconFar;

    // Area available for the title (and the icon, when it sits next to it)
    int tL = aL + ((iconFar && iconPos == 1) ? iconW + gap : 0);
    int tR = aR - ((iconFar && iconPos == 2) ? iconW + gap : 0);

    int availText = tR - tL - (iconInGroup ? iconW + gap : 0);
    if (availText < 0) availText = 0;
    if (showTitle && availText < 12) showTitle = false;  // too small to show anything useful

    int align = EffTitleAlign();
    int side = iconInGroup ? g_settings.iconSide : 0;
    int textW = availText;
    bool measured = false;

    if (showTitle && (align != 0 || side == 1)) {
        int m = MeasureTitleWidth(t_seq.hwnd, dpi);
        if (m >= 0) {
            textW = m + 4;
            if (textW > availText) textW = availText;
            measured = true;
        } else {
            // Text width unknown: use the safe layout instead of guessing.
            align = 0;
            side = 0;
        }
    }

    int groupW = (iconInGroup ? iconW : 0)
               + ((iconInGroup && showTitle) ? gap : 0)
               + (showTitle ? textW : 0);

    int cx = t_seq.winW / 2 + g_settings.centerNudge;  // window center
    int gx = tL;
    if (align == 1) {
        if (g_settings.centerOnText && showTitle) {
            // Center the text itself; the icon (if attached) sits beside it
            int textX = cx - textW / 2;
            gx = textX - ((iconInGroup && side == 0) ? iconW + gap : 0);
        } else {
            gx = cx - groupW / 2;
        }
        if (gx + groupW > tR) gx = tR - groupW;
        if (gx < tL) gx = tL;
    } else if (align == 2) {
        gx = tR - groupW;
        if (gx < tL) gx = tL;
    }

    int iconX, titleX;
    if (iconInGroup) {
        if (side == 0) {
            iconX = gx;
            titleX = gx + iconW + gap;
        } else {
            titleX = gx;
            iconX = gx + (showTitle ? textW + gap : 0);
        }
    } else {
        titleX = gx;
        iconX = (iconPos == 2) ? aR - iconW : aL;
    }
    int titleRightEdge = (side == 0) ? tR : titleX + textW;

    if (icon) {
        if (g_settings.hideIcon || noRoom) SetInsetLeft_Orig(icon->v, t_seq.winW + 200);
        else if (showIcon) SetInsetLeft_Orig(icon->v, iconX);
    }

    if (icon) SetWinIcon(t_seq.win, showIcon, iconX, iconX + iconW);
    if (!showTitle) {
        SetInsetLeft_Orig(title->v, t_seq.winW + 100);
        SetInsetRight_Orig(title->v, -200);
    } else {
        SetInsetLeft_Orig(title->v, titleX);
        SetInsetRight_Orig(title->v, t_seq.winW - titleRightEdge);
    }

    DebugLog(L"[Title] vis=%p W=%d buttonEnd=%d aL=%d aR=%d iconW=%d textW=%d measured=%d hwnd=%p align=%d side=%d noRoom=%d cx=%d origIconLeft=%d origTitleLeft=%d -> iconX=%d titleX=%d titleRightEdge=%d showIcon=%d showTitle=%d",
             title->v, t_seq.winW, t_seq.buttonEnd, aL, aR, iconW, textW, (int)measured, t_seq.hwnd, align, side,
             (int)noRoom, cx, icon ? icon->left : -1, title->left, iconX, titleX, titleRightEdge,
             (int)showIcon, (int)showTitle);
    return true;
}

// ---------------- CVisual inset hooks ----------------
static void SetInsetTop_Hook(void* v, int value) {
    if (t_seq.active && !t_seq.done) {
        if (VisEntry* e = GetEntry(v)) { e->top = value; e->hasTop = true; }
    }
    SetInsetTop_Orig(v, value);
}

static void SetInsetLeft_Hook(void* v, int value) {
    // Diagnostic: someone else changing the title's position outside our sequence
    if (g_settings.debugLog && v == g_lastTitleVis && !(t_seq.active && !t_seq.done)) {
        DebugLog(L"[LateInset] vis=%p Left=%d posDepth=%d relayout=%d", v, value, t_posDepth, (int)t_relayout);
    }
    if (t_seq.active && !t_seq.done) {
        if (VisEntry* e = GetEntry(v)) { e->left = value; e->hasLeft = true; }
    }
    SetInsetLeft_Orig(v, value);
}

static void SetInsetRight_Hook(void* v, int value) {
    if (g_settings.debugLog && v == g_lastTitleVis && !(t_seq.active && !t_seq.done)) {
        DebugLog(L"[LateInset] vis=%p Right=%d posDepth=%d relayout=%d", v, value, t_posDepth, (int)t_relayout);
    }
    if (t_seq.active && !t_seq.done) {
        VisEntry* e = FindEntry(v);
        if (e && e->hasLeft && abs(value - t_seq.origFinalOut) <= 3) {
            t_seq.done = true;
            if (RepositionTitle(e)) return;
        }
    }
    SetInsetRight_Orig(v, value);
}

// ---------------- layout ----------------
static bool ComputeLayout(void* pThis, int a, int b, int baseOut) {
    struct { TITLEBARINFOEX t; BYTE pad[256]; } buf = {};
    buf.t.cbSize = sizeof(TITLEBARINFOEX);
    bool flag = false;
    GetTitleBarInfo_Orig(pThis, &buf.t, &flag);

    const RECT& tb = buf.t.rcTitleBar;
    int tbW = tb.right - tb.left;
    if (tbW <= 0 || tbW > 20000) return false;
    if (tb.left < -20000) return false;  // minimized / offscreen representation (thumbnail)

    int expectedInset = (b == 8) ? 8 : baseOut + 1;

    // Window width: the real rect of the HWND is authoritative. The title bar
    // rect can lag a maximize or restore (it still spans the old width), so the
    // estimate from it is wrong exactly when the two disagree. Trust the window
    // rect; the layout runs again on every WM_SIZE / WM_WINDOWPOSCHANGED.
    int winW = tbW + 2 * expectedInset;
    HWND hwndUsed = HwndFromTopLevelWindow(pThis);
    if (hwndUsed) {
        RECT wr;
        if (GetWindowRect(hwndUsed, &wr) && wr.right > wr.left) {
            winW = wr.right - wr.left;
        }
    }

    // The HWND is only needed to measure the title text.
    bool needHwnd = g_settings.moveTitle && !g_settings.hideTitle &&
                    TitleWidthMatters();

    // Excluded apps keep the default Windows layout (buttons on the right).
    // Returning false here is the same as any other layout failure.
    if (hwndUsed && IsHwndExcluded(hwndUsed)) {
        DebugLog(L"[Excluded] this=%p hwnd=%p -> default layout", pThis, hwndUsed);
        return false;
    }

    // Remember which title text this layout was computed for
    if (needHwnd && hwndUsed) SetTitleState(pThis, hwndUsed, HashWindowText(hwndUsed));

    int w[4] = {};
    for (int t = 1; t <= 3; t++) {
        int tmp = 0;
        UpdateNCAreaButton_Orig(pThis, t, a, b, &tmp);
        w[t] = tmp;
        if (w[t] < 0 || w[t] > 300) {
            DebugLog(L"[LayoutFail] this=%p type=%d w=%d (invalid)", pThis, t, w[t]);
            return false;
        }
    }
    // The close button is required. Minimize/maximize may be 0 (dialogs,
    // message boxes, About Windows: windows that only have a close button).
    if (w[3] <= 0) {
        DebugLog(L"[LayoutFail] this=%p close button width=%d", pThis, w[3]);
        return false;
    }

    static const int kOrders[3][3] = { {3, 1, 2}, {3, 2, 1}, {1, 2, 3} };
    int o = g_settings.order;

    // Windows with only a close button (dialogs, message boxes, About Windows)
    // are positioned slightly differently by DWM, so they get their own offset.
    bool closeOnly = (w[1] <= 0 && w[2] <= 0);

    // Tighten: buttons 2 and 3 overlap the previous one by T px (0 = default).
    // Works on both sides and in File Explorer.
    int T = 0;
    if (g_settings.tighten > 0 && w[1] > 0 && w[2] > 0) {
        int dpiT = 0;
        if (hwndUsed && g_pGetDpiForWindow) dpiT = (int)g_pGetDpiForWindow(hwndUsed);
        if (dpiT <= 0 && g_pGetDpiForSystem) dpiT = (int)g_pGetDpiForSystem();
        if (dpiT <= 0) dpiT = 96;
        // Middle button: on the left it depends on the order, on the right it is maximize
        int midW = g_settings.moveButtons ? w[kOrders[o][1]] : w[2];
        T = TightenPx(dpiT, midW);
    }

    int x = 0;                 // right edge of the button group (from the left)
    int rightMargin = baseOut; // space reserved on the right for the title area
    if (g_settings.moveButtons) {
        x = baseOut + EffLeftMargin(hwndUsed) + (closeOnly ? kCloseOnlyOffset : 0);
        for (int i = 0; i < 3; i++) {
            int t = kOrders[o][i];
            x += w[t] - (i > 0 ? T : 0);
            t_seq.outBefore[t] = winW - x;
        }
    } else {
        // Default Windows placement: close, maximize, minimize from the right.
        static const int kStock[3] = { 3, 2, 1 };
        int out = baseOut;
        for (int i = 0; i < 3; i++) {
            int t = kStock[i];
            t_seq.outBefore[t] = out;
            out += w[t] - ((i < 2) ? T : 0);
        }
        rightMargin = out;  // the buttons occupy the right side
    }

    // Close-only windows: optionally park the close button outside the window.
    // The hit-test fix treats the spot it leaves behind as plain caption.
    if (closeOnly && !g_settings.showDialogClose) {
        t_seq.outBefore[3] = winW + 200;
        if (g_settings.moveButtons) x = baseOut;
        else rightMargin = baseOut;
    }

    // Only skip tiny surfaces. Narrow windows keep the left layout (buttons may
    // extend past the right edge, just like the default layout does).
    if (winW < 100) return false;

    for (int t = 1; t <= 3; t++) t_seq.w[t] = w[t];
    t_seq.origFinalOut = baseOut + w[1] + w[2] + w[3];
    t_seq.buttonEnd = x;
    t_seq.rightMargin = rightMargin;
    t_seq.winW = winW;
    t_seq.hwnd = hwndUsed;
    t_seq.win = pThis;
    t_seq.closeOnly = closeOnly;

    int dpi = 0;
    if (hwndUsed && g_pGetDpiForWindow) dpi = (int)g_pGetDpiForWindow(hwndUsed);
    if (dpi <= 0 && g_pGetDpiForSystem) dpi = (int)g_pGetDpiForSystem();
    if (dpi <= 0) dpi = 96;
    t_seq.dpi = dpi;
    if (!g_settings.moveButtons) {
        // Title area starts where the default icon sits (16px @ 96 dpi);
        // RepositionTitle adds titleGap, so subtract it here.
        x = MulDiv(16, dpi, 96) - g_settings.titleGap;
        t_seq.buttonEnd = x;
    }
    t_seq.valid = true;

    int bl[4] = {}, br[4] = {};
    for (int t = 1; t <= 3; t++) {
        br[t] = winW - t_seq.outBefore[t];
        bl[t] = br[t] - w[t];
        if (T > 0 && w[t] > 0) { bl[t] += T / 2; br[t] -= T - T / 2; }   // hit slot = narrower than the 46px visual
    }
    StoreWinLayout(pThis, bl, br, b + a + 2, hwndUsed);

    if (g_settings.debugLog && hwndUsed) {
        RECT rr = {};
        if (GetWindowRect(hwndUsed, &rr)) {
            DebugLog(L"[Rect] this=%p hwnd=%p rect=(%ld,%ld,%ld,%ld) rectW=%ld tb=(%ld,%ld,%ld,%ld) style=%08lX zoomed=%d winW=%d expectedInset=%d",
                     pThis, hwndUsed, rr.left, rr.top, rr.right, rr.bottom, rr.right - rr.left,
                     tb.left, tb.top, tb.right, tb.bottom,
                     (unsigned long)GetWindowLongW(hwndUsed, GWL_STYLE), (int)IsZoomed(hwndUsed),
                     winW, expectedInset);
        }
    }

    DebugLog(L"[Layout] this=%p closeOnly=%d a=%d b=%d base=%d W=%d match=%d exact=%d hwnd=%p dpi=%d buttonEnd=%d close=[%d,%d] max=[%d,%d] min=[%d,%d] band=%d",
             pThis, (int)closeOnly, a, b, baseOut, winW, (int)(hwndUsed != nullptr), (int)(hwndUsed != nullptr), hwndUsed, dpi,
             x, bl[3], br[3], bl[2], br[2], bl[1], br[1], b + a + 2);
    return true;
}

static long UpdateNCAreaButton_Hook(void* pThis, int type, int a, int b, int* pOut) {
    if (type == 3) {
        t_seq = Seq{};
        ClearWinLayout(pThis);
        if (g_unloading) {
            InterlockedIncrement(&g_unloadRelayouts);
        } else if (a > 0 && pOut && (g_settings.moveButtons || g_settings.moveTitle)) {
            ComputeLayout(pThis, a, b, *pOut);
        }
    }

    if (t_seq.valid && pOut) {
        if (type >= 1 && type <= 3) *pOut = t_seq.outBefore[type];
        else if (type == 0) *pOut = t_seq.origFinalOut;
    }

    long r = UpdateNCAreaButton_Orig(pThis, type, a, b, pOut);

    if (type == 0) {
        if (t_seq.valid && g_settings.moveTitle && g_hasPosHook && t_posDepth > 0) {
            t_seq.active = true;
        }
    }
    return r;
}

static long PosAndSizes_Hook(void* p) {
    Seq saved = t_seq;
    t_seq = Seq{};
    t_posDepth++;
    long r = PosAndSizes_Orig(p);
    t_posDepth--;
    t_seq = saved;
    return r;
}

// ---------------- re-layout when the title text changes ----------------
// A tab/title change only updates the text; the full non-client layout does not
// run, so the title keeps the position computed for the old text. We re-run the
// layout BEFORE the text update (so the text is built for the final box) and
// again AFTER it (in case DWM touched the layout meanwhile).
static bool TitleDependsOnText() {
    // Without a window handle the title width can't be measured, so a text change needs no relayout.
    return g_settings.moveTitle && g_hasPosHook && g_hwndOffset != SIZE_MAX && TitleWidthMatters();
}

static void DoRelayout(void* pThis, const wchar_t* tag) {
    t_relayout = true;
    DebugLog(L"[TextRelayout] %s this=%p", tag, pThis);
    PosAndSizes_Hook(pThis);
    t_relayout = false;
}

static bool RelayoutIfTitleChanged(void* pThis, const wchar_t* tag) {
    if (!TitleDependsOnText() || t_posDepth != 0 || t_relayout) return false;

    int l[4] = {}, rr[4] = {}, band = 0;
    if (!GetWinLayout(pThis, l, rr, &band)) return false;  // never laid out by us

    HWND hw = nullptr;
    unsigned oldHash = 0;
    bool hasState = GetTitleState(pThis, &hw, &oldHash);
    if (hasState && hw && IsWindow(hw)) {
        unsigned nowHash = HashWindowText(hw);
        if (nowHash == kHashUnsafe || nowHash == oldHash) return false;   // hung window: don't relayout
    }

    DoRelayout(pThis, tag);
    return true;
}

typedef long (*UpdateText_t)(void*, void*);
static UpdateText_t UpdateText_Orig;

static long UpdateText_Hook(void* pThis, void* frame) {
    bool pre = RelayoutIfTitleChanged(pThis, L"UpdateText-pre");
    long r = UpdateText_Orig(pThis, frame);
    if (pre && t_posDepth == 0 && !t_relayout) DoRelayout(pThis, L"UpdateText-post");
    return r;
}

typedef void (*OnTitleUpdated_t)(void*);
static OnTitleUpdated_t OnTitleUpdated_Orig;

static void OnTitleUpdated_Hook(void* pThis) {
    bool pre = RelayoutIfTitleChanged(pThis, L"OnTitleUpdated-pre");
    OnTitleUpdated_Orig(pThis);
    if (pre && t_posDepth == 0 && !t_relayout) DoRelayout(pThis, L"OnTitleUpdated-post");
}

// The icon menu is delayed briefly. If a second click (double-click) arrives
// before the timer fires, the menu is cancelled and the window is closed instead.
#ifndef WM_POPUPSYSTEMMENU
#define WM_POPUPSYSTEMMENU 0x0313
#endif

static PTP_TIMER g_menuTimer;
static SRWLOCK g_menuLock = SRWLOCK_INIT;
static HWND g_menuHwnd;
static POINT g_menuPt;

static VOID CALLBACK MenuTimerCallback(PTP_CALLBACK_INSTANCE, PVOID, PTP_TIMER) {
    AcquireSRWLockExclusive(&g_menuLock);
    HWND hw = g_menuHwnd;
    POINT pt = g_menuPt;
    g_menuHwnd = nullptr;
    ReleaseSRWLockExclusive(&g_menuLock);
    if (hw && !g_unloading && IsWindow(hw))
        PostMessageW(hw, WM_POPUPSYSTEMMENU, 0, MAKELPARAM(pt.x, pt.y));
}

static void QueueIconMenu(HWND hw, int x, int y) {
    if (!g_menuTimer) return;
    AcquireSRWLockExclusive(&g_menuLock);
    g_menuHwnd = hw;
    g_menuPt = {x, y};
    ReleaseSRWLockExclusive(&g_menuLock);
    UINT dc = GetDoubleClickTime();
    LONGLONG due = -(LONGLONG)(dc > 250 ? 250 : dc) * 10000;   // relative, 100 ns units; change 250 for a faster/slower menu
    FILETIME ft = {(DWORD)due, (DWORD)(due >> 32)};
    SetThreadpoolTimer(g_menuTimer, &ft, 0, 0);
}

// ---------------- hit-test fix ----------------
// DWM stretches the close button's hit area (in maximized windows) over most of
// the title bar, assuming close is the last button. When the reported button
// does not contain the point, replace the result with the correct one:
//  - point inside another button's rectangle -> that button's code
//  - point elsewhere in the title bar band   -> HTCAPTION (drag / double-click)
//  - otherwise                               -> reject
//
// Diagnostic: [HitRaw] logs the raw DWM answer for points near the top-left
// corner, but only when the window or the returned code changes, so the log
// quota is not used up by every mouse move.
static void* g_lastRawWin = nullptr;
static unsigned g_lastRawCode = 0xFFFFFFF0u;

static bool DoHitTest_Hook(void* pThis, const POINT* pt, void** ppVisual, unsigned int* pFlags) {
    bool r = DoHitTest_Orig(pThis, pt, ppVisual, pFlags);

    if (g_settings.debugLog && pt && pFlags && pt->y <= 40) {
        unsigned c = r ? *pFlags : 0xFFFFFFF1u;
        if (pThis != g_lastRawWin || c != g_lastRawCode) {
            g_lastRawWin = pThis;
            g_lastRawCode = c;
            HitLog(L"[HitRaw] win=%p pt=(%ld,%ld) r=%d code=%u", pThis, pt->x, pt->y, (int)r, r ? *pFlags : 0);
        }
    }

    if (!r || !pt || !pFlags) return r;

    unsigned int code = *pFlags;
    if (g_settings.debugLog && pt->y <= 40 && pt->x > 200) {
        int la[4] = {}, ra[4] = {}, ba = 0, ia = 0, ib = 0;
        HitLog(L"[IconChk] pt=(%ld,%ld) code=%u hasLayout=%d hasIcon=%d",
               pt->x, pt->y, code, (int)GetWinLayout(pThis, la, ra, &ba), (int)GetWinIcon(pThis, &ia, &ib));
    }
    if (code == 3 || code == 2) {
        int l0[4] = {}, r0[4] = {}, b0 = 0, il = 0, ir = 0;
        if (GetWinLayout(pThis, l0, r0, &b0) && GetWinIcon(pThis, &il, &ir)) {
            bool onIcon = g_settings.iconClickable && ir > il &&
                          pt->y >= 0 && pt->y <= b0 &&
                          pt->x >= il - 1 && pt->x < ir + 1;
            if (onIcon) {
                for (int t = 1; t <= 3; t++)
                    if (pt->x >= l0[t] && pt->x < r0[t]) { onIcon = false; break; }
            }
            HitLog(L"[IconHit] pt=(%ld,%ld) code=%u icon=[%d,%d] onIcon=%d clickable=%d band=%d",
                   pt->x, pt->y, code, il, ir, (int)onIcon, (int)g_settings.iconClickable, b0);
            static bool s_down = false;
            static ULONGLONG s_lastMenu = 0;
            static ULONGLONG s_lastDown = 0;
            bool down = (GetAsyncKeyState(GetSystemMetrics(SM_SWAPBUTTON) ? VK_RBUTTON : VK_LBUTTON) & 0x8000) != 0;
            ULONGLONG nowTick = GetTickCount64();
            bool within = (nowTick - s_lastMenu) <= (ULONGLONG)GetDoubleClickTime();
            bool newPress = down && (!s_down || (nowTick - s_lastDown) > 100);
            bool dblIcon = false;
            if (down) s_lastDown = nowTick;
            if (g_settings.iconClickable && onIcon && newPress) {
                HWND hw = GetWinHwnd(pThis);
                if (within) {
                    // second click on the icon = double-click -> close the window
                    s_lastMenu = 0;
                    AcquireSRWLockExclusive(&g_menuLock); g_menuHwnd = nullptr; ReleaseSRWLockExclusive(&g_menuLock);   // cancel the pending menu
                    dblIcon = true;   // let Windows close it itself (HTSYSMENU)
                } else {
                    s_lastMenu = nowTick;
                    RECT wr;
                    if (hw && GetWindowRect(hw, &wr)) {
                        int sx = wr.left + il;
                        int sy = wr.top + b0 - (IsZoomed(hw) ? 6 : 0);
                        QueueIconMenu(hw, sx, sy);
                    }
                }
            }
            s_down = down;
            if (dblIcon) { *pFlags = 3; code = 3; }   // second click: double-click on the icon = close
            else { *pFlags = 2; code = 2; }           // everything else is caption, including the icon
        }
    }
    int type = (code == 20) ? 3 : (code == 9) ? 2 : (code == 8) ? 1 : 0;
    if (!type) return r;

    int l[4] = {}, rr[4] = {}, band = 0;
    if (!GetWinLayout(pThis, l, rr, &band)) return r;

    if (pt->x >= l[type] - 1 && pt->x <= rr[type] + 1) return r;  // legitimate

    static const unsigned int kCodes[4] = { 0, 8, 9, 20 };
    unsigned int newCode = 0;
    if (pt->y >= 0 && pt->y <= band) {
        for (int t = 1; t <= 3; t++) {
            if (pt->x >= l[t] && pt->x < rr[t]) { newCode = kCodes[t]; break; }
        }
        if (!newCode) newCode = 2;  // HTCAPTION
    }

    HitLog(L"[HitFix] win=%p pt=(%ld,%ld) dwmCode=%u buttonRect=[%d,%d] band=%d -> newCode=%u",
           pThis, pt->x, pt->y, code, l[type], rr[type], band, newCode);

    if (ppVisual) *ppVisual = nullptr;
    if (newCode) {
        *pFlags = newCode;
        return true;
    }
    *pFlags = 0;
    return false;
}

// ======================================================================
//  PART 2: Glyph painter (macOS-style circles / custom button images)
// ======================================================================

static volatile LONG g_tlEnabled = 1;
static volatile LONG g_styleCustom = 0;     // 1 = "Custom images" style
static volatile LONG g_painterBroken = 0;   // 1 = DWM object layout did not match, the painter stays off
static volatile LONG g_restartOnUnload = 0;
static volatile LONG g_debug = 0;
static volatile LONG g_everPainted = 0;
static volatile LONG g_pending = 0;     // 1 = repaint on the next DWM-thread hook call
static volatile LONG g_dirty = 0;
static volatile LONG g_iconVerSeen = 0;     // last icon cache version loaded by dwm.exe
static ULONGLONG g_iconVerCheck = 0;        // tick of the last version check
static int g_base[3][3] = { {254, 188, 46}, {40, 200, 64}, {255, 95, 87} };   // R,G,B: minimize, maximize/restore, close

static int HexVal(wchar_t c) {
    if (c >= L'0' && c <= L'9') return c - L'0';
    if (c >= L'a' && c <= L'f') return c - L'a' + 10;
    if (c >= L'A' && c <= L'F') return c - L'A' + 10;
    return -1;
}

// "#RRGGBB", "RRGGBB", "#RGB" or "RGB"
static bool ParseHexColor(PCWSTR s, int* out) {
    if (!s) return false;
    while (*s == L' ') s++;
    if (*s == L'#') s++;
    int d[6];
    int n = 0;
    while (*s && *s != L' ') {
        int v = HexVal(*s);
        if (v < 0 || n >= 6) return false;
        d[n++] = v;
        s++;
    }
    if (n == 6) {
        out[0] = d[0] * 16 + d[1]; out[1] = d[2] * 16 + d[3]; out[2] = d[4] * 16 + d[5];
        return true;
    }
    if (n == 3) {
        out[0] = d[0] * 17; out[1] = d[1] * 17; out[2] = d[2] * 17;
        return true;
    }
    return false;
}

static void LoadIcons();

static void TL_LoadSettings() {
    g_debug = Wh_GetIntSetting(L"debugLog") ? 1 : 0;
    PCWSTR style = Wh_GetStringSetting(L"buttonStyle.style");
    g_tlEnabled = (style && wcscmp(style, L"windows") != 0 && !g_painterBroken) ? 1 : 0;
    g_styleCustom = (style && wcscmp(style, L"custom") == 0) ? 1 : 0;
    Wh_FreeStringSetting(style);
    g_restartOnUnload = Wh_GetIntSetting(L"buttonStyle.restartDwmOnUnload") ? 1 : 0;

    static const int kDef[3][3] = { {254, 188, 46}, {40, 200, 64}, {255, 95, 87} };
    static const wchar_t* const kKeys[3] = {
        L"buttonStyle.minimizeColor", L"buttonStyle.maximizeColor", L"buttonStyle.closeColor"
    };
    for (int r = 0; r < 3; r++) {
        PCWSTR str = Wh_GetStringSetting(kKeys[r]);
        int c[3];
        if (ParseHexColor(str, c)) memcpy(g_base[r], c, sizeof(c));
        else memcpy(g_base[r], kDef[r], sizeof(c));
        Wh_FreeStringSetting(str);
    }
    LoadIcons();   // reads the images from the mod storage (also runs on the DWM thread when explorer.exe syncs new images)
}

// ---------------- painter logging (only when debugLog is on) ----------------
static SRWLOCK g_logLock = SRWLOCK_INIT;
static int g_total = 0;
static int g_catCount[8];
static wchar_t g_catLast[8][400];

static void LogCat(int cat, int cap, const wchar_t* fmt, ...) {
    if (!g_debug) return;
    wchar_t buf[400];
    va_list a;
    va_start(a, fmt);
    _vsnwprintf(buf, 399, fmt, a);
    va_end(a);
    buf[399] = 0;
    AcquireSRWLockExclusive(&g_logLock);
    if (g_catCount[cat] < cap && g_total < 800 && wcscmp(g_catLast[cat], buf) != 0) {
        wcscpy(g_catLast[cat], buf);
        g_catCount[cat]++;
        g_total++;
        Wh_Log(L"%s", buf);
    }
    ReleaseSRWLockExclusive(&g_logLock);
}

// ---------------- memory helpers ----------------
// CBitmapSource layout: +0x00 vtable, +0x08 refcount, +0x10 owner, +0x18 width, +0x1C height,
// +0x50..+0x5C rect in the atlas (left, top, right, bottom).
static bool Readable(const void* p, SIZE_T n) {
    MEMORY_BASIC_INFORMATION mbi;
    if (!p || !VirtualQuery(p, &mbi, sizeof(mbi))) return false;
    if (mbi.State != MEM_COMMIT || (mbi.Protect & (PAGE_NOACCESS | PAGE_GUARD))) return false;
    return (const char*)p + n <= (const char*)mbi.BaseAddress + mbi.RegionSize;
}

// Layout check before the painter reads or writes a glyph object: the vtable must belong to
// uDWM.dll, the size must be small, and the atlas rect must have the same size as the object.
// (Verified on all 24 objects in the debug log.) If this fails, the painter turns itself off.
static bool AddressInUdwm(const void* p) {
    HMODULE m = nullptr;
    return p && GetModuleHandleExW(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS |
                                   GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT,
                                   (LPCWSTR)p, &m) && m && m == GetModuleHandleW(L"udwm.dll");
}

static bool LooksLikeBitmapSource(const void* obj) {
    if (!Readable(obj, 0x70)) return false;
    if (!AddressInUdwm(*(void* const*)obj)) return false;
    const unsigned* d = (const unsigned*)obj;
    if (d[6] < 4 || d[6] > 64 || d[7] < 4 || d[7] > 64) return false;
    return d[22] - d[20] == d[6] && d[23] - d[21] == d[7];
}

// ---------------- registry of arrays and glyph objects ----------------
struct ArrInfo { const void* bm[4]; char kind; int set; int role; };
static ArrInfo g_arr[192];
static int g_arrCount = 0;
static int g_curSet = -1, g_curSetCount = 0;
static float g_curSetF = -1.0f;
static unsigned g_curSetH = 0;
static volatile LONG g_dpiChanged = 0;
static ULONGLONG g_lastDpiRefresh = 0;
static void RequestDwmRefresh();   // defined in the lifecycle section
// After a DPI change DWM only rebuilds the inactive glyph set (f=0.4). The active set (f=1.0) is
// created when a window's active state changes, so we flip the foreground window's frame state once.
static HANDLE g_nudgeThread = nullptr;

static DWORD WINAPI ActivateNudgeThread(LPVOID) {
    for (int i = 0; i < 12 && !g_unloading; i++) Sleep(100);   // let DWM finish rebuilding (~1.2 s)
    if (g_unloading) return 0;

    // Pick a visible window that this mod laid out (a normal caption window, not a frame host)
    HWND target = nullptr;
    HWND fg = GetForegroundWindow();
    AcquireSRWLockShared(&g_layoutLock);
    for (auto& p : g_winLayouts) {
        HWND h = p.second.hwnd;
        if (!(p.second.valid && h && IsWindow(h) && IsWindowVisible(h) && !IsIconic(h))) continue;
        if (h == fg) { target = h; break; }   // prefer the foreground window
        if (!target) target = h;              // otherwise the first usable one
    }
    ReleaseSRWLockShared(&g_layoutLock);

    if (target) {
        bool isFg = (GetForegroundWindow() == target);
        DWORD_PTR res = 0;
        // Flip the active state and put it back, so the final state is what it was
        SendMessageTimeoutW(target, WM_NCACTIVATE, isFg ? FALSE : TRUE, 0, SMTO_ABORTIFHUNG, 300, &res);
        SendMessageTimeoutW(target, WM_NCACTIVATE, isFg ? TRUE : FALSE, 0, SMTO_ABORTIFHUNG, 300, &res);
        LogCat(0, 200, L"[DpiRefresh] activation nudge sent to hwnd=%p fg=%d", target, (int)isFg);
    }
    return 0;
}

static SRWLOCK g_arrLock = SRWLOCK_INIT;

struct Glyph { const void* obj; const void* a0; int role, state; unsigned rc[4]; unsigned sz[2]; void* vt; float f; };
static Glyph g_gl[256];
static int g_glN = 0;
static int g_extR = 64, g_extB = 864;
static SRWLOCK g_glLock = SRWLOCK_INIT;

// A stored CBitmapSource pointer can outlive the object (theme/DPI change, device reset).
// Check that the memory still looks like the same kind of live object before touching it.
static bool GlyphStillValid(const Glyph& g) {
    if (!g.obj || !Readable(g.obj, 0x70)) return false;
    if (*(void* const*)g.obj != g.vt) return false;                        // same vtable
    unsigned long long ref = *(const unsigned long long*)((const char*)g.obj + 8);
    if (ref == 0 || ref > 1000000ull) return false;                        // refcount looks sane
    const unsigned* d = (const unsigned*)g.obj;
    return d[6] == g.sz[0] && d[7] == g.sz[1];                             // same size
}

static bool ReadArr(const void* arr, const void** out4) {
    if (!Readable(arr, 24)) return false;
    const unsigned long long* q = (const unsigned long long*)arr;
    const void* const* data = (const void* const*)q[0];
    unsigned cap = (unsigned)(q[2] >> 32);
    if (!data || cap < 4 || cap > 64 || !Readable(data, 32)) return false;
    for (int i = 0; i < 4; i++) out4[i] = data[i];
    return true;
}

// Cells live in the free area of the atlas (y >= 808). Each glyph height class (12, 15, 18, 21, 24 px =
// 100%..200% scaling) has its own 4x4 block of cells: 4 kinds x 4 states. A glyph of one DPI never shares a cell
// with a glyph of another DPI. Kinds: 0 = minimize, 1 = restore, 2 = maximize, 3 = close.
static const int kClsPitch[5] = { 15, 16, 21, 26, 30 };
static const int kClsX[5]     = {  1, 61, 125,  1, 105 };
static const int kClsY[5]     = { 808, 808, 808, 892, 892 };

static int SizeClass(unsigned h) {
    int c = ((int)h - 12) / 3;   // 12..14 -> 0, 15..17 -> 1, 18..20 -> 2, 21..23 -> 3, 24..26 -> 4
    return c < 0 ? 0 : (c > 4 ? 4 : c);
}

// role 0 = minimize, 1 = maximize, 2 = close, 3 = restore
static int CellKind(int role, unsigned w, unsigned h) {
    return role == 2 ? 3 : (role == 3 ? 1 : (role == 1 ? 2 : 0));
}

static void CellRect(unsigned w, unsigned h, int role, int state, unsigned* rc) {
    int cls = SizeClass(h);
    unsigned x = (unsigned)(kClsX[cls] + kClsPitch[cls] * CellKind(role, w, h));
    unsigned y = (unsigned)(kClsY[cls] + kClsPitch[cls] * state);
    rc[0] = x; rc[1] = y; rc[2] = x + w; rc[3] = y + h;
}

// Kind of the cell that contains (x, y), or -1 when the point is not inside one of our blocks
static int KindFromCell(unsigned x, unsigned y) {
    for (int c = 0; c < 5; c++) {
        int p = kClsPitch[c];
        if ((int)x >= kClsX[c] && (int)x < kClsX[c] + 4 * p && (int)y >= kClsY[c] && (int)y < kClsY[c] + 4 * p)
            return ((int)x - kClsX[c]) / p;
    }
    return -1;
}

static void MoveToCell(Glyph& g) {
    if (!GlyphStillValid(g)) return;
    CellRect(g.sz[0], g.sz[1], g.role, g.state, g.rc);
    unsigned* d = (unsigned*)g.obj;
    d[20] = g.rc[0]; d[21] = g.rc[1]; d[22] = g.rc[2]; d[23] = g.rc[3];
}

// First guess: A left margin = 4 -> close; B width = 14 -> maximize; the rest minimize.
// Minimize vs restore is corrected later from the button width (46 = middle, 47 = minimize).
static int DetectRole(const void* a0, const void* b0, int fallback) {
    if (Readable(a0, 0x70) && Readable(b0, 0x70)) {
        const unsigned* da = (const unsigned*)a0;
        const unsigned* db = (const unsigned*)b0;
        if (da[8] < 8) return 2;                  // close: margin A = 4 px at every DPI (12 for min/max)
        if (db[6] > db[7]) return 1;              // maximize: wider than tall (100%, 150%+)
        // 125%: minimize and maximize are both square, so tell them apart by order within the set
        return (fallback == 0 || fallback == 1) ? fallback : 0;
    }
    return fallback;
}

// Middle button: maximize (role 1) or restore (role 3).
// At 100% they differ in size (14x12 vs 12x12). At other DPIs the sizes are equal or
// unreliable, so the second middle set of the same size class and opacity is the other kind.
// Caller must hold g_glLock.
static int MiddleRoleLocked(const void* const* fam, float f, unsigned w, unsigned h) {
    int cls = SizeClass(h);
    if (cls == 0) return w > h ? 1 : 3;
    for (int i = 0; i < g_glN; i++) {
        const Glyph& g = g_gl[i];
        if ((g.role != 1 && g.role != 3) || g.f != f || SizeClass(g.sz[1]) != cls) continue;
        bool self = false;
        for (int s = 0; s < 4; s++) if (fam[s] && fam[s] == g.obj) self = true;
        if (self || !GlyphStillValid(g)) continue;
        return g.role == 1 ? 3 : 1;
    }
    // No sibling yet. The active set (f ~ 1.0) is built for the window that just became
    // active, so the foreground window tells whether this set is restore or maximize.
    if (f > 0.7f) {
        HWND fg = GetForegroundWindow();
        if (fg && IsZoomed(fg)) return 3;
    }
    return 1;
}

static void CorrectRole(const void* bmp, int role) {
    const void* fam[4] = {};
    bool have = false;
    AcquireSRWLockShared(&g_arrLock);
    for (int i = 0; i < g_arrCount && !have; i++) {
        if (g_arr[i].kind != 'B') continue;
        for (int s = 0; s < 4; s++) {
            if (g_arr[i].bm[s] == bmp) { memcpy(fam, g_arr[i].bm, sizeof(fam)); have = true; break; }
        }
    }
    ReleaseSRWLockShared(&g_arrLock);
    if (!have) return;
    bool changed = false;
    AcquireSRWLockExclusive(&g_glLock);
    int midRole = -1;
    for (int i = 0; i < g_glN; i++) {
        for (int s = 0; s < 4; s++) {
            if (!fam[s] || g_gl[i].obj != fam[s]) continue;
            int cur = g_gl[i].role;
            if (cur == 2) continue;
            int want = role;
            if (role == 1) {
                if (cur == 1 || cur == 3) continue;   // already the middle button
                if (midRole < 0) midRole = MiddleRoleLocked(fam, g_gl[i].f, g_gl[i].sz[0], g_gl[i].sz[1]);
                want = midRole;
            } else if (g_gl[i].sz[0] > g_gl[i].sz[1]) {
                continue;   // a wide glyph must not become minimize
            }
            if (cur == want) continue;
            g_gl[i].role = want;
            MoveToCell(g_gl[i]);
            changed = true;
        }
    }
    ReleaseSRWLockExclusive(&g_glLock);
    if (changed) g_dirty = 1;
}

static void AddExtent(const void* obj) {
    if (!Readable(obj, 0x70)) return;
    const unsigned* d = (const unsigned*)obj;
    if (d[22] > 0 && d[22] < 4096 && (int)d[22] > g_extR) g_extR = (int)d[22];
    if (d[23] > 0 && d[23] < 8192 && (int)d[23] > g_extB) g_extB = (int)d[23];
}

// Caller holds g_glLock.
static bool HeightIsLiveLocked(unsigned h) {
    for (int i = 0; i < g_glN; i++)
        if (g_gl[i].sz[1] == h && GlyphStillValid(g_gl[i])) return true;
    return false;
}

static bool RegisterPair(const void* a, const void* b, float f) {
    const void* va[4] = {};
    const void* vb[4] = {};
    if (!ReadArr(a, va) || !ReadArr(b, vb)) return false;
    if (!vb[0] || !Readable(vb[0], 0x70)) return false;   // empty/odd arrays: ignore
    if (g_painterBroken) return false;
    {
        bool known = false;
        AcquireSRWLockShared(&g_arrLock);
        for (int i = 0; i < g_arrCount; i++) {
            if (g_arr[i].kind == 'B' && g_arr[i].bm[0] == vb[0]) { known = true; break; }
        }
        ReleaseSRWLockShared(&g_arrLock);
        if (!known) {
            for (int i = 0; i < 4; i++) {
                if (vb[i] && !LooksLikeBitmapSource(vb[i])) {
                    g_painterBroken = 1;
                    g_tlEnabled = 0;
                    Wh_Log(L"[Painter] unexpected CBitmapSource layout (obj=%p), painter disabled", vb[i]);
                    return false;
                }
            }
        }
    }

    bool isNew = false;
    int set = -1, role = -1;
    AcquireSRWLockExclusive(&g_arrLock);
    bool found = false;
    for (int i = 0; i < g_arrCount; i++) {
        if (g_arr[i].kind == 'B' && g_arr[i].bm[0] == vb[0]) { found = true; break; }
    }
    if (!found && g_arrCount + 2 <= 192) {
        unsigned hNow = ((const unsigned*)vb[0])[7];
        if (g_curSet >= 0 && hNow != g_curSetH) {
            // Only a height with no live registered glyph counts as a DPI change
            AcquireSRWLockShared(&g_glLock);
            if (!HeightIsLiveLocked(hNow)) g_dpiChanged = 1;
            ReleaseSRWLockShared(&g_glLock);
        }
        if (g_curSet < 0 || g_curSetCount >= 3 || f != g_curSetF || hNow != g_curSetH) {
            g_curSet++;
            g_curSetCount = 0;
            g_curSetF = f;
            g_curSetH = hNow;
        }
        set = g_curSet;
        int idx = g_curSetCount++;
        role = DetectRole(va[0], vb[0], idx == 1 ? 1 : 0);
        // A glyph that an earlier session already moved to its cell (y >= 808): only the
        // minimize cell and the wide shape are trusted. Maximize vs restore is decided below.
        if (role != 2) {
            const unsigned* movedRc = (const unsigned*)vb[0];
            int cellKind = KindFromCell(movedRc[20], movedRc[21]);
            bool wide = movedRc[6] > movedRc[7];
            if (cellKind == 0 && !wide) role = 0;
            else if (cellKind == 1 || cellKind == 2) role = 1;   // middle button: maximize vs restore is decided below, not from the old cell
            else if (wide && role == 0) role = 1;
        }
        // The second glyph of a set that is not close is the middle button
        if (idx == 1 && role == 0) role = 1;
        // Middle button: maximize (role 1) or restore (role 3)
        if (role == 1) {
            AcquireSRWLockShared(&g_glLock);
            role = MiddleRoleLocked(vb, f, ((const unsigned*)vb[0])[6], ((const unsigned*)vb[0])[7]);
            ReleaseSRWLockShared(&g_glLock);
        }
        memcpy(g_arr[g_arrCount].bm, vb, sizeof(vb));
        g_arr[g_arrCount].kind = 'B'; g_arr[g_arrCount].set = set; g_arr[g_arrCount].role = role;
        g_arrCount++;
        memcpy(g_arr[g_arrCount].bm, va, sizeof(va));
        g_arr[g_arrCount].kind = 'A'; g_arr[g_arrCount].set = set; g_arr[g_arrCount].role = role;
        g_arrCount++;
        isNew = true;
    }
    ReleaseSRWLockExclusive(&g_arrLock);

    if (isNew) {
        AcquireSRWLockExclusive(&g_glLock);
        // forget glyph entries whose objects were freed or reused
        int keepN = 0;
        for (int k = 0; k < g_glN; k++) {
            if (GlyphStillValid(g_gl[k])) g_gl[keepN++] = g_gl[k];
        }
        g_glN = keepN;
        for (int i = 0; i < 4; i++) {
            AddExtent(va[i]);
            AddExtent(vb[i]);
            if (vb[i] && Readable(vb[i], 0x70) && g_glN < 256) {
                const unsigned* d = (const unsigned*)vb[i];
                Glyph& g = g_gl[g_glN++];
                g.obj = vb[i]; g.role = role; g.state = i;
                for (int k = 0; k < 4; k++) g.rc[k] = d[20 + k];
                g.sz[0] = d[6]; g.sz[1] = d[7];
                g.a0 = va[0];
                g.vt = *(void* const*)vb[i];
                g.f = f;
                MoveToCell(g);
            }
        }
        ReleaseSRWLockExclusive(&g_glLock);

        const unsigned* d0 = (const unsigned*)vb[0];
        unsigned lr[6] = { d0[20], d0[21], d0[22], d0[23], d0[6], d0[7] };
        unsigned aMargin = Readable(va[0], 0x70) ? ((const unsigned*)va[0])[8] : 0;
        unsigned aW = Readable(va[0], 0x70) ? ((const unsigned*)va[0])[6] : 0;
        unsigned aH = Readable(va[0], 0x70) ? ((const unsigned*)va[0])[7] : 0;
        LogCat(0, 200, L"[Pair] set=%d role=%d f=%f A0=%p B0=%p rc=(%u,%u)-(%u,%u) size=%ux%u margin=%u Asize=%ux%u",
               set, role, (double)f, va[0], vb[0], lr[0], lr[1], lr[2], lr[3], lr[4], lr[5], aMargin, aW, aH);
        if (InterlockedExchange(&g_dpiChanged, 0)) {
            ULONGLONG nowTick = GetTickCount64();
            if (nowTick - g_lastDpiRefresh > 3000) {
                g_lastDpiRefresh = nowTick;
                InterlockedExchange(&g_pending, 1);
                RequestDwmRefresh();   // posted message: runs after this hook returns
                LogCat(0, 200, L"[DpiRefresh] glyph size changed, DWM refresh requested");
                if (!g_nudgeThread || WaitForSingleObject(g_nudgeThread, 0) == WAIT_OBJECT_0) {
                    if (g_nudgeThread) CloseHandle(g_nudgeThread);
                    g_nudgeThread = CreateThread(nullptr, 0, ActivateNudgeThread, nullptr, 0, nullptr);
                }
            }
        }
    }
    return isNew;
}

static bool Classify(const void* bmp, char* kind, int* state, const void** st0) {
    bool ok = false;
    AcquireSRWLockShared(&g_arrLock);
    for (int i = 0; i < g_arrCount && !ok; i++) {
        for (int s = 0; s < 4; s++) {
            if (g_arr[i].bm[s] == bmp) {
                *kind = g_arr[i].kind; *state = s; *st0 = g_arr[i].bm[0];
                ok = true;
                break;
            }
        }
    }
    ReleaseSRWLockShared(&g_arrLock);
    return ok;
}

// ---------------- CBitmapSource::Update (address only) ----------------
// CBitmapSource::Update is only called, never hooked. Its address is resolved
// through an address-only entry in the HookSymbols array in Sec_ModInit.
typedef long (*UpdateBmp_t)(void* pThis, IWICBitmap* bmp);
static UpdateBmp_t g_updateBmp = nullptr;

// ---------------- rendering ----------------
static const GUID kPBGRA = {0x6fddc324, 0x4e03, 0x4bfe, {0xb1, 0x85, 0x3d, 0x77, 0x76, 0x8d, 0xc9, 0x10}};
static const GUID kCLSID_WICFactory = {0xcacaf262, 0x9370, 0x4615, {0xa1, 0x3b, 0x9f, 0x55, 0x39, 0xda, 0x4c, 0x0a}};
static const GUID kIID_WICFactory = {0xec5ec8a9, 0xc395, 0x4314, {0x9c, 0x77, 0x54, 0xd7, 0xa9, 0x35, 0xff, 0x70}};

static float DistSeg(float px, float py, float ax, float ay, float bx, float by) {
    float vx = bx - ax, vy = by - ay, wx = px - ax, wy = py - ay;
    float c = vx * vx + vy * vy;
    float t = c > 0.0f ? (wx * vx + wy * vy) / c : 0.0f;
    if (t < 0.0f) t = 0.0f;
    if (t > 1.0f) t = 1.0f;
    float dx = px - (ax + t * vx), dy = py - (ay + t * vy);
    return sqrtf(dx * dx + dy * dy);
}

// role 0 = minimize, 1 = maximize/restore, 2 = close
static bool InSymbol(int role, float ux, float uy) {
    const float th = 0.6f, L = 2.4f;
    if (role == 2) return DistSeg(ux, uy, -L, -L, L, L) <= th || DistSeg(ux, uy, -L, L, L, -L) <= th;
    if (role == 0) return DistSeg(ux, uy, -L - 0.4f, 0.0f, L + 0.4f, 0.0f) <= th;
    // macOS-style maximize: two right triangles (top-right and bottom-left) with a gap between them
    const float a = 3.0f, d = 4.8f;
    bool tr = ux <= a && uy >= -a && (ux - uy) >= (2.0f * a - d);
    bool bl = ux >= -a && uy <= a && (ux - uy) <= (d - 2.0f * a);
    return tr || bl;
}

static void RenderGlyph(BYTE* px, int w, int h, int role, int state) {
    if (role == 3) role = 1;   // restore uses the maximize colors
    if (role < 0 || role > 2) role = 0;
    int bg[3], sym[3];
    for (int i = 0; i < 3; i++) {
        bg[i] = state == 2 ? g_base[role][i] * 78 / 100 : g_base[role][i];
        sym[i] = g_base[role][i] * g_base[role][i] / 255 * 60 / 100;
    }
    bool drawSym = (state == 1 || state == 2);
    float cx = w / 2.0f, cy = h / 2.0f;
    float rad = (w < h ? w : h) / 2.0f - 0.25f;
    float k = 12.0f / (float)(w < h ? w : h);   // keeps the x / - / + symbols proportional at high DPI
    for (int y = 0; y < h; y++) {
        for (int x = 0; x < w; x++) {
            int nBg = 0, nSym = 0;
            for (int sy = 0; sy < 4; sy++) {
                for (int sx = 0; sx < 4; sx++) {
                    float ux = x + (sx + 0.5f) / 4.0f - cx;
                    float uy = y + (sy + 0.5f) / 4.0f - cy;
                    if (ux * ux + uy * uy <= rad * rad) {
                        if (drawSym && InSymbol(role, ux * k, uy * k)) nSym++;
                        else nBg++;
                    }
                }
            }
            BYTE* p = px + (y * w + x) * 4;
            p[0] = (BYTE)((nBg * bg[2] + nSym * sym[2]) / 16);
            p[1] = (BYTE)((nBg * bg[1] + nSym * sym[1]) / 16);
            p[2] = (BYTE)((nBg * bg[0] + nSym * sym[0]) / 16);
            p[3] = (BYTE)((nBg + nSym) * 255 / 16);
        }
    }
}

static int Pow2AtLeast(int v) {
    int p = 16;
    while (p < v && p < 8192) p <<= 1;
    return p;
}

// ---------------- custom images (png/jpg/bmp), decoded in explorer.exe ----------------
struct IconImg { int w, h; BYTE* px; };
static IconImg g_icons[4][4];   // [kind][state]; kind: 0 minimize, 1 restore, 2 maximize, 3 close
static SRWLOCK g_iconLock = SRWLOCK_INIT;

static const wchar_t* const kIconNames[4] = { L"minimize", L"restore", L"maximize", L"close" };
static const wchar_t* const kIconSuffix[4] = { L"", L"_hover", L"_pressed", L"_disabled" };
static const wchar_t* const kIconExts[4] = { L".png", L".jpg", L".jpeg", L".bmp" };

static void TrimPath(wchar_t* s) {
    size_t n = wcslen(s);
    while (n > 0 && (s[n - 1] == L' ' || s[n - 1] == L'"' || s[n - 1] == L'\t')) s[--n] = 0;
    size_t i = 0;
    while (s[i] == L' ' || s[i] == L'"' || s[i] == L'\t') i++;
    if (i) memmove(s, s + i, (n - i + 1) * sizeof(wchar_t));
}

static bool FileExistsW(const wchar_t* path) {
    DWORD a = GetFileAttributesW(path);
    return a != INVALID_FILE_ATTRIBUTES && !(a & FILE_ATTRIBUTE_DIRECTORY);
}

static const int kMaxIconPx = 64;   // images are shrunk to this size before they are stored

static bool DecodeImage(IWICImagingFactory* fac, const wchar_t* path, IconImg* out) {
    out->w = 0; out->h = 0; out->px = nullptr;

    // Read the file ourselves so a failure shows the real Win32 error
    HANDLE hf = CreateFileW(path, GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
                            nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
    if (hf == INVALID_HANDLE_VALUE) {
        LogCat(3, 40, L"[Icon] CreateFile failed, error=%lu (%s)", (unsigned long)GetLastError(), path);
        return false;
    }
    LARGE_INTEGER fsz = {};
    if (!GetFileSizeEx(hf, &fsz) || fsz.QuadPart <= 0 || fsz.QuadPart > 16 * 1024 * 1024) {
        LogCat(3, 40, L"[Icon] unusable file size %lld (%s)", (long long)fsz.QuadPart, path);
        CloseHandle(hf);
        return false;
    }
    DWORD fileSize = (DWORD)fsz.QuadPart;
    BYTE* data = (BYTE*)malloc(fileSize);
    DWORD got = 0;
    bool readOk = data && ReadFile(hf, data, fileSize, &got, nullptr) && got == fileSize;
    DWORD readErr = GetLastError();
    CloseHandle(hf);
    if (!readOk) {
        LogCat(3, 40, L"[Icon] ReadFile failed, error=%lu (%s)", (unsigned long)readErr, path);
        free(data);
        return false;
    }

    // Only hand png / jpeg / bmp data to the decoder: this keeps the other WIC codecs out of this process
    bool known = (fileSize >= 8 && memcmp(data, "\x89PNG\r\n\x1a\n", 8) == 0) ||
                 (fileSize >= 3 && data[0] == 0xFF && data[1] == 0xD8 && data[2] == 0xFF) ||
                 (fileSize >= 2 && data[0] == 'B' && data[1] == 'M');
    if (!known) {
        LogCat(3, 40, L"[Icon] not a png/jpg/bmp file, skipped (%s)", path);
        free(data);
        return false;
    }

    {
        wchar_t hdr[48] = L"";
        for (DWORD i = 0; i < 8 && i < fileSize; i++)
            _snwprintf(hdr + i * 3, 4, L"%02X ", data[i]);
        LogCat(3, 40, L"[Icon] read OK size=%lu header=%s(%s)", (unsigned long)fileSize, hdr, path);
    }

    IWICStream* stream = nullptr;
    IWICBitmapDecoder* dec = nullptr;
    IWICBitmapFrameDecode* frame = nullptr;
    IWICFormatConverter* conv = nullptr;
    IWICBitmapScaler* scl = nullptr;
    const wchar_t* step = L"CreateStream";
    bool ok = false;
    UINT w = 0, h = 0;

    HRESULT hr = fac->CreateStream(&stream);
    if (SUCCEEDED(hr) && stream) {
        step = L"InitializeFromMemory";
        hr = stream->InitializeFromMemory(data, fileSize);
    }
    if (SUCCEEDED(hr)) {
        step = L"CreateDecoderFromStream";
        hr = fac->CreateDecoderFromStream(stream, nullptr, WICDecodeMetadataCacheOnDemand, &dec);
    }
    if (SUCCEEDED(hr) && dec) {
        step = L"GetFrame";
        hr = dec->GetFrame(0, &frame);
    }
    if (SUCCEEDED(hr) && frame) {
        step = L"CreateFormatConverter";
        hr = fac->CreateFormatConverter(&conv);
    }
    if (SUCCEEDED(hr) && conv) {
        step = L"ConverterInitialize";
        hr = conv->Initialize(frame, kPBGRA, WICBitmapDitherTypeNone, nullptr, 0.0, WICBitmapPaletteTypeCustom);
    }
    if (SUCCEEDED(hr) && conv) {
        step = L"GetSize";
        hr = conv->GetSize(&w, &h);
        if (SUCCEEDED(hr) && (w == 0 || h == 0)) hr = E_FAIL;
    }
    if (SUCCEEDED(hr) && conv) {
        IWICBitmapSource* src = conv;
        if (w > kMaxIconPx || h > kMaxIconPx) {
            double k = (double)kMaxIconPx / (w > h ? w : h);
            UINT nw = (UINT)(w * k + 0.5), nh = (UINT)(h * k + 0.5);
            if (nw < 1) nw = 1;
            if (nh < 1) nh = 1;
            if (SUCCEEDED(fac->CreateBitmapScaler(&scl)) && scl &&
                SUCCEEDED(scl->Initialize(conv, nw, nh, WICBitmapInterpolationModeFant))) {
                src = scl; w = nw; h = nh;
            }
        }
        BYTE* buf = (BYTE*)malloc((size_t)w * h * 4);
        step = L"CopyPixels";
        hr = buf ? src->CopyPixels(nullptr, w * 4, w * h * 4, buf) : E_OUTOFMEMORY;
        if (SUCCEEDED(hr)) {
            out->w = (int)w; out->h = (int)h; out->px = buf;
            ok = true;
        } else {
            free(buf);
        }
    }
    if (!ok) {
        LogCat(3, 40, L"[Icon] decode step %s failed, hr=0x%08lX (%s)", step, (unsigned long)hr, path);
    }

    if (scl) scl->Release();
    if (conv) conv->Release();
    if (frame) frame->Release();
    if (dec) dec->Release();
    if (stream) stream->Release();
    free(data);   // safe now: the pixels were copied into our own buffer
    return ok;
}

static void FreeIcons() {
    AcquireSRWLockExclusive(&g_iconLock);
    for (int k = 0; k < 4; k++)
        for (int st = 0; st < 4; st++) {
            free(g_icons[k][st].px);
            g_icons[k][st] = IconImg{};
        }
    ReleaseSRWLockExclusive(&g_iconLock);
}

// ---------------- icon storage (shared between explorer.exe and dwm.exe) ----------------
// explorer.exe runs as the user and can read any folder the user can. It decodes the
// images, shrinks them to at most kMaxIconPx and stores the raw pixels in the mod's own
// storage; dwm.exe only reads those pixels back and never opens or decodes an image file.
// Stored value layout: int width, int height, then width * height * 4 bytes (premultiplied BGRA).
static void IconValueName(int kind, int st, wchar_t* out, size_t cap) {
    _snwprintf(out, cap - 1, L"icon_k%d_s%d", kind, st);
    out[cap - 1] = 0;
}

struct IconSettings {
    wchar_t folder[MAX_PATH];
    wchar_t files[4][MAX_PATH];
    bool any;
};

// Reads the image settings. 'any' is true only in the "Custom images" style:
// with the macOS or Windows style the image settings are ignored completely.
static void ReadIconSettings(IconSettings* s) {
    static const wchar_t* const kKeys[4] = {
        L"buttonStyle.minimizeIcon", L"buttonStyle.restoreIcon",
        L"buttonStyle.maximizeIcon", L"buttonStyle.closeIcon"
    };
    *s = IconSettings{};

    PCWSTR st = Wh_GetStringSetting(L"buttonStyle.style");
    bool custom = st && wcscmp(st, L"custom") == 0;
    Wh_FreeStringSetting(st);
    if (!custom) return;

    PCWSTR v = Wh_GetStringSetting(L"buttonStyle.iconFolder");
    if (v) wcsncpy(s->folder, v, MAX_PATH - 1);
    Wh_FreeStringSetting(v);
    TrimPath(s->folder);
    size_t fl = wcslen(s->folder);
    while (fl > 0 && (s->folder[fl - 1] == L'\\' || s->folder[fl - 1] == L'/')) s->folder[--fl] = 0;

    s->any = s->folder[0] != 0;
    for (int k = 0; k < 4; k++) {
        v = Wh_GetStringSetting(kKeys[k]);
        if (v) wcsncpy(s->files[k], v, MAX_PATH - 1);
        Wh_FreeStringSetting(v);
        TrimPath(s->files[k]);
        if (s->files[k][0]) s->any = true;
    }
}

// Finds the image file for (kind, state). 'cand' must hold MAX_PATH + 32 characters.
static bool FindIconFile(const IconSettings& s, int kind, int st, wchar_t* cand) {
    wchar_t stem[MAX_PATH] = L"";
    wchar_t ownExt[16] = L"";
    if (s.files[kind][0]) {
        wcsncpy(stem, s.files[kind], MAX_PATH - 1);
        wchar_t* dot = wcsrchr(stem, L'.');
        wchar_t* sl = wcsrchr(stem, L'\\');
        if (dot && (!sl || dot > sl)) { wcsncpy(ownExt, dot, 15); *dot = 0; }
    } else if (s.folder[0]) {
        _snwprintf(stem, MAX_PATH - 1, L"%s\\%s", s.folder, kIconNames[kind]);
        stem[MAX_PATH - 1] = 0;
    } else {
        return false;
    }
    const wchar_t* exts[5];
    int ne = 0;
    if (ownExt[0]) exts[ne++] = ownExt;
    for (int e = 0; e < 4; e++) exts[ne++] = kIconExts[e];
    for (int e = 0; e < ne; e++) {
        _snwprintf(cand, MAX_PATH + 31, L"%s%s%s", stem, kIconSuffix[st], exts[e]);
        cand[MAX_PATH + 31] = 0;
        if (FileExistsW(cand)) return true;
    }
    return false;
}

static void LoadIcons() {
    // Read the version BEFORE loading: if explorer bumps it meanwhile, we reload once more.
    g_iconVerSeen = Wh_GetIntValue(L"iconCacheVersion", 0);

    IconImg tmp[4][4] = {};
    const size_t maxBlob = 8 + (size_t)kMaxIconPx * kMaxIconPx * 4;
    BYTE* blob = (BYTE*)malloc(maxBlob);
    int loaded = 0;
    for (int kind = 0; kind < 4 && blob; kind++) {
        for (int st = 0; st < 4; st++) {
            wchar_t name[32];
            IconValueName(kind, st, name, 32);
            size_t size = Wh_GetBinaryValue(name, blob, maxBlob);
            if (size < 8) continue;   // not stored, or unreadable
            int w = 0, h = 0;
            memcpy(&w, blob, 4);
            memcpy(&h, blob + 4, 4);
            if (w < 1 || h < 1 || w > kMaxIconPx || h > kMaxIconPx) continue;
            if (size != 8 + (size_t)w * h * 4) continue;
            BYTE* px = (BYTE*)malloc((size_t)w * h * 4);
            if (!px) continue;
            memcpy(px, blob + 8, (size_t)w * h * 4);
            tmp[kind][st].w = w;
            tmp[kind][st].h = h;
            tmp[kind][st].px = px;
            loaded++;
        }
    }
    free(blob);
    LogCat(3, 40, L"[Icon] loaded %d image(s) from the mod storage", loaded);

    AcquireSRWLockExclusive(&g_iconLock);
    for (int k = 0; k < 4; k++)
        for (int st = 0; st < 4; st++) {
            free(g_icons[k][st].px);
            g_icons[k][st] = tmp[k][st];
        }
    ReleaseSRWLockExclusive(&g_iconLock);
}

// Scale an image into the cell (aspect kept, centered) by box-averaging premultiplied values.
// The image keeps its own shape: nothing is clipped to a circle.
static void BlitIcon(BYTE* cell, int cw, int ch, const IconImg& im) {
    float sc = (float)cw / im.w;
    float sc2 = (float)ch / im.h;
    if (sc2 < sc) sc = sc2;
    int tw = (int)(im.w * sc + 0.5f);
    int th = (int)(im.h * sc + 0.5f);
    if (tw < 1) tw = 1;
    if (th < 1) th = 1;
    if (tw > cw) tw = cw;
    if (th > ch) th = ch;
    int ox = (cw - tw) / 2, oy = (ch - th) / 2;
    for (int y = 0; y < th; y++) {
        int sy0 = y * im.h / th;
        int sy1 = ((y + 1) * im.h + th - 1) / th;
        if (sy1 <= sy0) sy1 = sy0 + 1;
        if (sy1 > im.h) sy1 = im.h;
        for (int x = 0; x < tw; x++) {
            int sx0 = x * im.w / tw;
            int sx1 = ((x + 1) * im.w + tw - 1) / tw;
            if (sx1 <= sx0) sx1 = sx0 + 1;
            if (sx1 > im.w) sx1 = im.w;
            unsigned sum[4] = { 0, 0, 0, 0 };
            int cnt = 0;
            for (int sy = sy0; sy < sy1; sy++) {
                for (int sx = sx0; sx < sx1; sx++) {
                    const BYTE* q = im.px + ((size_t)sy * im.w + sx) * 4;
                    sum[0] += q[0]; sum[1] += q[1]; sum[2] += q[2]; sum[3] += q[3];
                    cnt++;
                }
            }
            if (cnt <= 0) continue;
            BYTE* d = cell + ((size_t)(oy + y) * cw + (ox + x)) * 4;
            for (int c = 0; c < 4; c++) d[c] = (BYTE)(sum[c] / cnt);
        }
    }
}

static bool RenderCustomCell(BYTE* cell, int w, int h, int role, int state, unsigned origW, unsigned origH) {
    int kind = CellKind(role, origW, origH);
    if (kind < 0 || kind > 3 || state < 0 || state > 3) return false;
    AcquireSRWLockShared(&g_iconLock);
    const IconImg* im = nullptr;
    bool dedicated = false;
    if (g_icons[kind][state].px) { im = &g_icons[kind][state]; dedicated = true; }
    else if (g_icons[kind][0].px) im = &g_icons[kind][0];
    if (!im) { ReleaseSRWLockShared(&g_iconLock); return false; }
    memset(cell, 0, (size_t)w * h * 4);
    BlitIcon(cell, w, h, *im);
    ReleaseSRWLockShared(&g_iconLock);
    if (state == 2 && !dedicated) {   // pressed without its own image: darken like the circle
        for (int i = 0; i < w * h; i++) {
            BYTE* q = cell + i * 4;
            q[0] = (BYTE)(q[0] * 78 / 100); q[1] = (BYTE)(q[1] * 78 / 100); q[2] = (BYTE)(q[2] * 78 / 100);
        }
    }
    return true;
}

// ---------------- paint the whole atlas in one Update call ----------------
static SRWLOCK g_paintLock = SRWLOCK_INIT;

static void PaintAtlas() {
    if (!g_updateBmp || !g_tlEnabled) return;
    static Glyph snap[256];
    int n, extR, extB;

    AcquireSRWLockExclusive(&g_paintLock);
    AcquireSRWLockShared(&g_glLock);
    n = g_glN;
    memcpy(snap, g_gl, sizeof(Glyph) * n);
    extR = g_extR; extB = g_extB;
    ReleaseSRWLockShared(&g_glLock);

    int validN = 0;
    for (int i = 0; i < n; i++) {
        if (GlyphStillValid(snap[i])) snap[validN++] = snap[i];
    }
    n = validN;

    if (n == 0 || extR <= 0 || extB <= 0) { ReleaseSRWLockExclusive(&g_paintLock); return; }

    int W = Pow2AtLeast(extR);
    int H = Pow2AtLeast(extB);
    if (W < extR) W = extR;
    if (H < extB) H = extB;
    if (W > 8192 || H > 8192) { ReleaseSRWLockExclusive(&g_paintLock); return; }

    BYTE* px = (BYTE*)calloc((size_t)W * H, 4);
    if (!px) { ReleaseSRWLockExclusive(&g_paintLock); return; }

    bool painted[4][4] = {};   // [cell kind][state]: cells drawn from glyphs registered in this session
    for (int i = 0; i < n; i++) {
        int x0 = (int)snap[i].rc[0], y0 = (int)snap[i].rc[1];
        int w = (int)snap[i].rc[2] - x0, h = (int)snap[i].rc[3] - y0;
        if (w < 4 || h < 4 || w > 64 || h > 64) continue;
        if (x0 < 0 || y0 < 0 || x0 + w > W || y0 + h > H) continue;
        if (y0 >= 808 && snap[i].state >= 0 && snap[i].state < 4 && SizeClass(snap[i].sz[1]) == 0)
            painted[CellKind(snap[i].role, snap[i].sz[0], snap[i].sz[1])][snap[i].state] = true;
        BYTE cell[64 * 64 * 4];
        if (!RenderCustomCell(cell, w, h, snap[i].role, snap[i].state, snap[i].sz[0], snap[i].sz[1]))
            RenderGlyph(cell, w, h, snap[i].role, snap[i].state);
        for (int y = 0; y < h; y++) {
            memcpy(px + ((size_t)(y0 + y) * W + x0) * 4, cell + y * w * 4, (size_t)w * 4);
        }
    }
    // A glyph moved to its cell by an earlier session may not be registered in this one
    // (for example the maximize glyph when the mod was turned on while a window was maximized).
    // The cells are at fixed positions, so draw every cell that this session did not paint.
    for (int kind = 0; kind < 4; kind++) {
        for (int st = 0; st < 4; st++) {
            if (painted[kind][st]) continue;
            int w = (kind == 2) ? 14 : 12, h = 12;
            int x0 = kClsX[0] + kClsPitch[0] * kind, y0 = kClsY[0] + kClsPitch[0] * st;
            if (x0 + w > W || y0 + h > H) continue;
            int role = (kind == 0) ? 0 : (kind == 3 ? 2 : (kind == 1 ? 3 : 1));
            BYTE cell[64 * 64 * 4];
            if (!RenderCustomCell(cell, w, h, role, st, (unsigned)w, (unsigned)h))
                RenderGlyph(cell, w, h, role, st);
            for (int y = 0; y < h; y++) {
                memcpy(px + ((size_t)(y0 + y) * W + x0) * 4, cell + y * w * 4, (size_t)w * 4);
            }
        }
    }

    HRESULT hrInit = CoInitializeEx(nullptr, COINIT_MULTITHREADED);
    IWICImagingFactory* fac = nullptr;
    HRESULT hr = CoCreateInstance(kCLSID_WICFactory, nullptr, CLSCTX_INPROC_SERVER, kIID_WICFactory, (void**)&fac);
    if (SUCCEEDED(hr) && fac) {
        IWICBitmap* bmp = nullptr;
        hr = fac->CreateBitmapFromMemory((UINT)W, (UINT)H, kPBGRA, (UINT)(W * 4), (UINT)((size_t)W * H * 4), px, &bmp);
        if (SUCCEEDED(hr) && bmp) {
            // Update is called on one object only; its size and rect are restored afterwards
            void* target = (void*)snap[0].obj;
            unsigned* d = (unsigned*)target;
            unsigned keep[6] = { d[6], d[7], d[20], d[21], d[22], d[23] };
            long r = g_updateBmp(target, bmp);
            LogCat(2, 40, L"[Atlas] target=%p atlas=%dx%d glyphs=%d ext=%dx%d ret=0x%lx | before size=%ux%u rc=(%u,%u)-(%u,%u) after size=%ux%u rc=(%u,%u)-(%u,%u)",
                   target, W, H, n, extR, extB, (unsigned long)r,
                   keep[0], keep[1], keep[2], keep[3], keep[4], keep[5],
                   d[6], d[7], d[20], d[21], d[22], d[23]);
            d[6] = keep[0]; d[7] = keep[1];
            d[20] = keep[2]; d[21] = keep[3]; d[22] = keep[4]; d[23] = keep[5];
            if (r >= 0) g_everPainted = 1;
            bmp->Release();
        } else {
            LogCat(2, 40, L"[Atlas] CreateBitmapFromMemory failed hr=0x%lx", (unsigned long)hr);
        }
        fac->Release();
    } else {
        LogCat(2, 40, L"[Atlas] CoCreateInstance WIC failed hr=0x%lx", (unsigned long)hr);
    }
    if (SUCCEEDED(hrInit)) CoUninitialize();
    free(px);
    ReleaseSRWLockExclusive(&g_paintLock);
}

// Settings changes arrive on a Windhawk thread, not the DWM thread. Writing to DWM's bitmap
// objects from there races with DWM, so settings only set a flag; the work runs in the hooks below.
static void ProcessPending() {
    // explorer.exe bumps this value after it stores new images in the mod storage
    ULONGLONG now = GetTickCount64();
    if (g_pending || now - g_iconVerCheck >= 500) {
        g_iconVerCheck = now;
        if ((LONG)Wh_GetIntValue(L"iconCacheVersion", 0) != g_iconVerSeen) {
            LoadIcons();       // also updates g_iconVerSeen
            InterlockedExchange(&g_pending, 1);
        }
    }
    if (!InterlockedExchange(&g_pending, 0)) return;
    PaintAtlas();
}

static void RestartDwm() {
    // Never restart dwm.exe twice within 30 seconds (protects against restart loops)
    FILETIME ft;
    GetSystemTimeAsFileTime(&ft);
    ULONGLONG now = ((ULONGLONG)ft.dwHighDateTime << 32) | ft.dwLowDateTime;
    ULONGLONG last = 0;
    Wh_GetBinaryValue(L"lastDwmRestart", &last, sizeof(last));
    if (last && now >= last && now - last < 30ULL * 10000000ULL) {
        Wh_Log(L"[Restore] restart skipped: dwm.exe was restarted less than 30 seconds ago");
        return;
    }
    Wh_SetBinaryValue(L"lastDwmRestart", &now, sizeof(now));
    LogCat(2, 40, L"[Restore] restarting dwm.exe");
    TerminateProcess(GetCurrentProcess(), 1);
}

// ---------------- forget freed glyph objects ----------------
// CBitmapSource::~CBitmapSource runs on every free. Drop the object from our
// registries so a later object at the same address is not mistaken for a known one.
static bool ForgetBitmapSource(const void* obj) {
    if (!obj) return false;
    bool removed = false;

    AcquireSRWLockExclusive(&g_glLock);
    for (int i = 0; i < g_glN; i++) {
        if (g_gl[i].obj == obj) {
            g_gl[i] = g_gl[--g_glN];
            i--;
            removed = true;
        }
    }
    ReleaseSRWLockExclusive(&g_glLock);

    AcquireSRWLockExclusive(&g_arrLock);
    for (int i = 0; i < g_arrCount; i++) {
        for (int s = 0; s < 4; s++) {
            if (g_arr[i].bm[s] == obj) {
                g_arr[i].bm[s] = nullptr;
                removed = true;
            }
        }
    }
    ReleaseSRWLockExclusive(&g_arrLock);
    return removed;
}

typedef void (*BmpDtor_t)(void*);
static BmpDtor_t BmpDtor_Orig;
static void BmpDtor_Hook(void* pThis) {
    if (g_tlEnabled && (g_glN > 0 || g_arrCount > 0)) {
        if (ForgetBitmapSource(pThis)) {
            LogCat(4, 40, L"[Free] glyph object %p released, removed from registry", pThis);
        }
    }
    BmpDtor_Orig(pThis);
}

// ---------------- painter hooks ----------------
typedef long (*SetVisualStates_t)(void*, const void*, const void*, float);
static SetVisualStates_t SetVisualStates_Orig;
static long SetVisualStates_Hook(void* pThis, const void* a, const void* b, float f) {
    bool isNew = g_tlEnabled ? RegisterPair(a, b, f) : false;
    long r = SetVisualStates_Orig(pThis, a, b, f);
    if (g_tlEnabled) {
        // Paint after the original function so our pixels are not overwritten by DWM's own upload
        if (isNew) PaintAtlas();
        ProcessPending();
    }
    return r;
}

// Hover/pressed/disabled backgrounds (A, states 1..3) are replaced by A state 0 (transparent).
typedef void (*ImgSetBmp_t)(void*, void*);
static ImgSetBmp_t ImgSetBmp_Orig;
static void ImgSetBmp_Hook(void* img, void* bmp) {
    void* use = bmp;
    char kind = '?'; int state = -1; const void* st0 = nullptr;
    if (g_tlEnabled && bmp && Classify(bmp, &kind, &state, &st0)) {
        if (kind == 'A' && state >= 1 && state <= 3 && st0 &&
            Readable(st0, 0x70) && Readable(bmp, 0x70) &&
            *(void* const*)st0 == *(void* const*)bmp) use = (void*)st0;
    }
    ImgSetBmp_Orig(img, use);
}

// image -> last glyph bitmap B set on it (to read the button role from its width)
static void* g_imgKey[256];
static const void* g_imgBmp[256];
static int g_imgN = 0;
static SRWLOCK g_imgLock = SRWLOCK_INIT;

static void RememberImg(void* img, const void* bmp) {
    AcquireSRWLockExclusive(&g_imgLock);
    int i = 0;
    for (; i < g_imgN; i++) if (g_imgKey[i] == img) break;
    if (i == g_imgN) { if (g_imgN < 256) g_imgN++; else i = 255; }
    g_imgKey[i] = img; g_imgBmp[i] = bmp;
    ReleaseSRWLockExclusive(&g_imgLock);
}

static const void* LookupImg(void* img) {
    const void* r = nullptr;
    AcquireSRWLockShared(&g_imgLock);
    for (int i = 0; i < g_imgN; i++) if (g_imgKey[i] == img) { r = g_imgBmp[i]; break; }
    ReleaseSRWLockShared(&g_imgLock);
    return r;
}

typedef void (*SetGlyph_t)(void*, void*, int, int);
static SetGlyph_t SetGlyph_Orig;
static void SetGlyph_Hook(void* img, void* bmp, int align, int off) {
    if (g_tlEnabled && bmp) RememberImg(img, bmp);
    SetGlyph_Orig(img, bmp, align, off);
}

typedef void (*ImgSetSize_t)(void*, const SIZE*);
static ImgSetSize_t ImgSetSize_Orig;
static unsigned char g_seenW[256];   // button widths seen so far (index = width in px)
static void ImgSetSize_Hook(void* img, const SIZE* sz) {
    ImgSetSize_Orig(img, sz);
    if (g_tlEnabled && sz) {
        const void* bmp = LookupImg(img);
        if (bmp) {
            int cx = (int)sz->cx;
            if (cx == 46) CorrectRole(bmp, 1);           // 100%: middle button is 46 wide
            else if (cx == 47) CorrectRole(bmp, 0);      // minimize and close are 47 (close is left alone)
            else if (cx >= 30 && cx <= 250) {
                g_seenW[cx] = 1;
                bool lo = g_seenW[cx - 1] != 0;
                bool hi = g_seenW[cx + 1] != 0;
                // At other DPIs the middle button is 1 px narrower than minimize and close.
                // Only decide when exactly one neighbour width has been seen.
                if (hi && !lo) CorrectRole(bmp, 1);
                else if (lo && !hi) CorrectRole(bmp, 0);
                LogCat(5, 300, L"[ImgSize] bmp=%p cx=%d lo=%d hi=%d", bmp, cx, (int)lo, (int)hi);
            }
        }
    }
}

typedef void (*UpdatePos_t)(void*);
static UpdatePos_t UpdatePos_Orig;
static void UpdatePos_Hook(void* pThis) {
    UpdatePos_Orig(pThis);
    if (g_tlEnabled) {
        if (g_dirty) { g_dirty = 0; PaintAtlas(); }
        ProcessPending();
    }
}

// ======================================================================
//  PART 3: File Explorer tab bar (runs inside explorer.exe only)
// ======================================================================

static bool g_isExplorer = false;
static volatile LONG g_exEnabled = 1;
static int g_exExtra = 0;

struct TabWin { HWND hwnd; int applied; bool isTab; bool bypass; };
static TabWin g_tabs[32];
static SRWLOCK g_tabLock = SRWLOCK_INIT;

static void ExLog(const wchar_t* fmt, ...) {
    if (!g_settings.debugLog) return;
    static int s_count = 0;
    static wchar_t s_last[500] = L"";
    wchar_t buf[500];
    va_list args;
    va_start(args, fmt);
    _vsnwprintf(buf, 499, fmt, args);
    va_end(args);
    buf[499] = 0;
    if (s_count >= 300 || wcscmp(buf, s_last) == 0) return;
    wcscpy(s_last, buf);
    s_count++;
    Wh_Log(L"%s", buf);
}

static void ExLoadSettings() {
    g_exEnabled = Wh_GetIntSetting(L"explorerTabs.enabled") ? 1 : 0;
    g_exExtra = Clamp(Wh_GetIntSetting(L"explorerTabs.extraPx"), -300, 300);
}

static int TabIndexLocked(HWND h) {
    for (int i = 0; i < 32; i++) if (g_tabs[i].hwnd == h) return i;
    return -1;
}

static bool TabAdd(HWND h) {
    bool added = false;
    AcquireSRWLockExclusive(&g_tabLock);
    if (TabIndexLocked(h) < 0) {
        for (int i = 0; i < 32; i++) {
            if (!g_tabs[i].hwnd) {
                g_tabs[i] = TabWin{};
                g_tabs[i].hwnd = h;
                added = true;
                break;
            }
        }
    }
    ReleaseSRWLockExclusive(&g_tabLock);
    return added;
}

static void TabRemove(HWND h) {
    AcquireSRWLockExclusive(&g_tabLock);
    int i = TabIndexLocked(h);
    if (i >= 0) g_tabs[i] = TabWin{};
    ReleaseSRWLockExclusive(&g_tabLock);
}

static bool TabIsBypass(HWND h) {
    bool b = false;
    AcquireSRWLockShared(&g_tabLock);
    int i = TabIndexLocked(h);
    if (i >= 0) b = g_tabs[i].bypass;
    ReleaseSRWLockShared(&g_tabLock);
    return b;
}

static void TabSetBypass(HWND h, bool v) {
    AcquireSRWLockExclusive(&g_tabLock);
    int i = TabIndexLocked(h);
    if (i >= 0) g_tabs[i].bypass = v;
    ReleaseSRWLockExclusive(&g_tabLock);
}

static void TabSetState(HWND h, int applied, bool isTab) {
    AcquireSRWLockExclusive(&g_tabLock);
    int i = TabIndexLocked(h);
    if (i >= 0) { g_tabs[i].applied = applied; g_tabs[i].isTab = isTab; }
    ReleaseSRWLockExclusive(&g_tabLock);
}

static int TabGetApplied(HWND h) {
    int a = 0;
    AcquireSRWLockShared(&g_tabLock);
    int i = TabIndexLocked(h);
    if (i >= 0) a = g_tabs[i].applied;
    ReleaseSRWLockShared(&g_tabLock);
    return a;
}

static int ExDpiOf(HWND h) {
    int dpi = 0;
    if (h && g_pGetDpiForWindow) dpi = (int)g_pGetDpiForWindow(h);
    if (dpi <= 0 && g_pGetDpiForSystem) dpi = (int)g_pGetDpiForSystem();
    return dpi > 0 ? dpi : 96;
}

// Window rectangle in the coordinates of its parent
static bool GetRectInParent(HWND h, RECT* out) {
    RECT r;
    if (!GetWindowRect(h, &r)) return false;
    HWND p = GetParent(h);
    if (p) MapWindowPoints(nullptr, p, (POINT*)&r, 2);
    *out = r;
    return true;
}

// Shift (px) to apply to the tab bar window of this top-level frame; 0 = leave it alone
static int ComputeTabShift(HWND h) {
    if (!g_exEnabled || !g_settings.moveButtons) return 0;
    HWND top = GetAncestor(h, GA_ROOT);
    if (!top) return 0;
    if (IsHwndExcluded(top)) return 0;
    int s = MulDiv(g_exExtra, ExDpiOf(top), 96);   // 0 = leave the tab bar and toolbar where Explorer puts them
    return s < 0 ? 0 : s;
}

static bool IsTabBridgeClass(const wchar_t* c) {
    return c && (wcsstr(c, L"DesktopChildSiteBridge") ||
                 wcsstr(c, L"DesktopWindowContentBridge") ||
                 wcsstr(c, L"InputNonClientPointerSource") ||
                 wcsstr(c, L"InputSiteWindowClass"));
}

static void AdjustTabPos(HWND hwnd, WINDOWPOS* p) {
    HWND parent = GetParent(hwnd);
    if (!parent) return;
    RECT cur = {};
    if (!GetRectInParent(hwnd, &cur)) return;
    HWND top = GetAncestor(hwnd, GA_ROOT);
    int dpi = ExDpiOf(top ? top : hwnd);

    wchar_t cls[128] = L"";
    GetClassNameW(hwnd, cls, 128);
    bool isInputLayer = wcsstr(cls, L"InputNonClientPointerSource") || wcsstr(cls, L"InputSiteWindowClass");

    bool noSize = (p->flags & SWP_NOSIZE) != 0;
    int cx = noSize ? (int)(cur.right - cur.left) : p->cx;
    int cy = noSize ? (int)(cur.bottom - cur.top) : p->cy;

    bool looksTab = isInputLayer || (p->y <= MulDiv(24, dpi, 96) && cy <= MulDiv(150, dpi, 96));
    int s = looksTab ? ComputeTabShift(hwnd) : 0;
    int prevApplied = TabGetApplied(hwnd);   // shift already applied to the current position
    TabSetState(hwnd, s, looksTab);
    if (s == 0) return;

    // Use the original X when WinUI resized the window without moving it
    int currentX = p->x;
    if (p->flags & SWP_NOMOVE) currentX = cur.left - prevApplied;                       // resize only: strip our own shift
    else if (prevApplied != 0 && p->x == cur.left) currentX = p->x - prevApplied;       // our shifted position echoed back
    int nx = currentX + s;

    RECT pc = {};
    if (GetClientRect(parent, &pc) && pc.right > 0 && !(top && IsIconic(top)) && nx + cx > pc.right) {
        cx = pc.right - nx;
        if (cx < 0) cx = 0;
        p->cx = cx;
        p->cy = cy;
        p->flags &= ~SWP_NOSIZE;
    }

    p->x = nx;
    p->flags &= ~SWP_NOMOVE;  // required: make Windows accept the new X
    ExLog(L"[TabMove] hwnd=%p origX=%d shift=%d -> x=%d y=%d cx=%d cy=%d dpi=%d", hwnd, currentX, s, nx, p->y, cx, cy, dpi);
}

static void ApplyButtonHole(HWND h) {
    static thread_local bool busy = false;
    if (busy) return;

    HWND top = GetAncestor(h, GA_ROOT);
    if (!top || GetParent(h) != top) return;          // only islands directly under the Explorer frame

    wchar_t cls[128] = L"";
    GetClassNameW(h, cls, 128);
    if (!wcsstr(cls, L"DesktopChildSiteBridge")) return;

    // Buttons not on the left, tab bar move off, or app excluded:
    // no hole, and remove any hole that was made earlier
    if (!g_exEnabled || !g_settings.moveButtons || IsHwndExcluded(top)) {
        HRGN cur = CreateRectRgn(0, 0, 0, 0);
        bool hasRgn = GetWindowRgn(h, cur) != ERROR;
        DeleteObject(cur);
        if (hasRgn) {
            busy = true;
            SetWindowRgn(h, nullptr, TRUE);
            busy = false;
        }
        return;
    }

    RECT wr, tr;
    if (!GetWindowRect(h, &wr) || !GetWindowRect(top, &tr)) return;
    int dpi = ExDpiOf(top);
    int w = wr.right - wr.left, hgt = wr.bottom - wr.top;
    if (w <= 0 || hgt <= 0) return;
    if (wr.top - tr.top > MulDiv(40, dpi, 96)) return; // island below the title bar (folder content): skip

    int baseOut = IsZoomed(top) ? 8 : 1;
    int bx1 = tr.left + baseOut + EffLeftMargin(top) - wr.left;
    int bwH = MulDiv(46, dpi, 96);
    int bx2 = bx1 + bwH * 3 - 2 * TightenPx(dpi, bwH);
    int by1 = -10000;
    int by2 = tr.top + MulDiv(35, dpi, 96) + baseOut - wr.top;

    busy = true;
    HRGN full = CreateRectRgn(0, 0, w, hgt);
    HRGN hole = CreateRectRgn(bx1, by1, bx2, by2);
    CombineRgn(full, full, hole, RGN_DIFF);
    DeleteObject(hole);
    SetWindowRgn(h, full, TRUE);   // the system takes ownership of 'full'; do not delete it
    busy = false;
}

typedef HRESULT (WINAPI *DwmDefWindowProc_t)(HWND, UINT, WPARAM, LPARAM, LRESULT*);

// DwmDefWindowProc is what keeps the caption button hover/press look in sync with the pointer.
static bool CallDwmDefWindowProc(HWND h, UINT msg, WPARAM wp, LPARAM lp, LRESULT* res) {
    static DwmDefWindowProc_t pFn = nullptr;
    if (!pFn) {
        HMODULE hDwmApi = GetModuleHandleW(L"dwmapi.dll");
        if (!hDwmApi) hDwmApi = LoadLibraryExW(L"dwmapi.dll", nullptr, LOAD_LIBRARY_SEARCH_SYSTEM32);
        if (hDwmApi) pFn = (DwmDefWindowProc_t)GetProcAddress(hDwmApi, "DwmDefWindowProc");
    }
    return pFn && pFn(h, msg, wp, lp, res) != 0;
}

// True only when buttons are on the left AND this window is not excluded.
// Excluded windows keep the default Windows behavior (no hit-test tricks).
static bool LeftActiveFor(HWND anyWnd) {
    if (!g_settings.moveButtons) return false;
    HWND top = GetAncestor(anyWnd, GA_ROOT);
    if (!top) top = anyWnd;
    return !IsHwndExcluded(top);
}

static LRESULT TabSubclassProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam, DWORD_PTR) {
    if (msg == WM_NCHITTEST && LeftActiveFor(hwnd)) {
        HWND top = GetAncestor(hwnd, GA_ROOT);
        RECT rw;
        if (top && GetWindowRect(top, &rw)) {
            int x = (int)(short)LOWORD(lParam) - rw.left;
            int y = (int)(short)HIWORD(lParam) - rw.top;
            int dpi = ExDpiOf(top);
            int baseOut = IsZoomed(top) ? 8 : 1;
            int topBand = MulDiv(35, dpi, 96) + baseOut;
            int b1 = baseOut + EffLeftMargin(top);
            int bwT = MulDiv(46, dpi, 96);
            int b4 = b1 + bwT * 3 - 2 * TightenPx(dpi, bwT);
            if (y >= 0 && y <= topBand && x >= b1 && x < b4) return HTTRANSPARENT;
            // Pointer is over the tab bar, not over a button: tell DWM, so a button that was hot loses its hover look
            LRESULT dr = 0;
            CallDwmDefWindowProc(top, WM_NCHITTEST, wParam, lParam, &dr);
        }
    }
    if (msg == WM_WINDOWPOSCHANGING) {
        WINDOWPOS* p = (WINDOWPOS*)lParam;
        if (p && !TabIsBypass(hwnd)) AdjustTabPos(hwnd, p);
    } else if (msg == WM_NCDESTROY) {
        TabRemove(hwnd);
    }
    LRESULT res = DefSubclassProc(hwnd, msg, wParam, lParam);
    if (msg == WM_WINDOWPOSCHANGED || msg == WM_SIZE) ApplyButtonHole(hwnd);
    return res;
}

// Re-send the current position so the subclass applies the shift
static void TabNudge(HWND h) {
    RECT r;
    if (!GetRectInParent(h, &r)) return;
    if (r.right <= r.left || r.bottom <= r.top) return;
    SetWindowPos(h, nullptr, r.left - TabGetApplied(h), r.top, r.right - r.left, r.bottom - r.top,
                 SWP_NOZORDER | SWP_NOACTIVATE);
    ApplyButtonHole(h);
}

// Move by a delta without letting the subclass add the shift again
static void TabMoveBy(HWND h, int delta) {
    if (!delta) return;
    RECT r;
    if (!GetRectInParent(h, &r)) return;
    TabSetBypass(h, true);
    SetWindowPos(h, nullptr, r.left + delta, r.top, r.right - r.left, r.bottom - r.top, SWP_NOZORDER | SWP_NOACTIVATE);
    TabSetBypass(h, false);
}

// Subclass the window when it is a XAML island inside a File Explorer frame. True = newly attached.
static bool TryAttach(HWND h) {
    wchar_t cls[128] = L"";
    if (!GetClassNameW(h, cls, 128) || !IsTabBridgeClass(cls)) return false;
    HWND top = GetAncestor(h, GA_ROOT);
    if (!top || top == h) return false;
    wchar_t tc[64] = L"";
    GetClassNameW(top, tc, 64);
    if (wcscmp(tc, L"CabinetWClass") != 0) return false;
    if (!TabAdd(h)) return false;

    // Do not report the window as attached unless Windhawk actually installed
    // the subclass. Otherwise the HWND stays in g_tabs and future scans won't
    // retry, leaving the tab bar over the caption buttons.
    if (!WindhawkUtils::SetWindowSubclassFromAnyThread(h, TabSubclassProc, 0)) {
        ExLog(L"[AttachFailed] hwnd=%p class=%s top=%p", h, cls, top);
        TabRemove(h);
        return false;
    }

    ExLog(L"[AttachOK] hwnd=%p class=%s top=%p", h, cls, top);
    return true;
}

typedef HWND (WINAPI *CreateWindowExW_t)(DWORD, LPCWSTR, LPCWSTR, DWORD, int, int, int, int, HWND, HMENU, HINSTANCE, LPVOID);
static CreateWindowExW_t CreateWindowExW_Orig;

static const UINT_PTR kRescanTimerId = 0x4C46;
static UINT g_msgCleanup = 0;   // registered in ExplorerInit; asks the subclass to remove itself
static BOOL CALLBACK ExChildProc(HWND h, LPARAM);
static int TabSnapshot(HWND* hw, int* applied, bool* isTab);

static void StartRescan(HWND cab) {
    SetPropW(cab, L"CaptionButtonsTicks", (HANDLE)(INT_PTR)0);
    SetTimer(cab, kRescanTimerId, 150, nullptr);
}

static LRESULT CALLBACK CabinetSubclassProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam, DWORD_PTR) {
    if (g_msgCleanup && msg == g_msgCleanup) {
        KillTimer(hwnd, kRescanTimerId);
        RemovePropW(hwnd, L"CaptionButtonsTicks");
        WindhawkUtils::RemoveWindowSubclassFromAnyThread(hwnd, CabinetSubclassProc);
        return 0;
    }
    if (msg == WM_TIMER && wParam == kRescanTimerId) {
        int ticks = (int)(INT_PTR)GetPropW(hwnd, L"CaptionButtonsTicks") + 1;
        SetPropW(hwnd, L"CaptionButtonsTicks", (HANDLE)(INT_PTR)ticks);
        EnumChildWindows(hwnd, ExChildProc, 0);
        if (ticks >= 12) {   // 12 x 150 ms = about 1.8 seconds
            KillTimer(hwnd, kRescanTimerId);
            RemovePropW(hwnd, L"CaptionButtonsTicks");
        }
        return 0;
    }
    if (msg == WM_SHOWWINDOW && wParam) {
        StartRescan(hwnd);
    }

    // Let DWM see the pointer leaving, so the hover look of a caption button is cleared
    if (LeftActiveFor(hwnd) &&
        (msg == WM_NCMOUSELEAVE || msg == WM_MOUSELEAVE || msg == WM_NCMOUSEMOVE)) {
        LRESULT dr = 0;
        CallDwmDefWindowProc(hwnd, msg, wParam, lParam, &dr);
    }

    if (msg == WM_NCHITTEST && LeftActiveFor(hwnd)) {
        POINT pt = { (int)(short)LOWORD(lParam), (int)(short)HIWORD(lParam) };
        RECT rw;
        if (GetWindowRect(hwnd, &rw)) {
            int x = pt.x - rw.left;
            int y = pt.y - rw.top;
            int dpi = ExDpiOf(hwnd);
            int baseOut = IsZoomed(hwnd) ? 8 : 1;
            int topBand = MulDiv(35, dpi, 96) + baseOut;

            if (y >= 0 && y <= topBand) {
                int lm = EffLeftMargin(hwnd);
                int bw = MulDiv(46, dpi, 96);
                int Tx = TightenPx(dpi, bw);
                int b1 = baseOut + lm;
                int b4 = b1 + bw * 3 - 2 * Tx;
                if (x >= b1 && x < b4) {

                    // Let DWM answer the hit-test so it keeps drawing the hover animation
                    LRESULT lRes = 0;
                    if (CallDwmDefWindowProc(hwnd, msg, wParam, lParam, &lRes)) {
                        return lRes;
                    }

                    int idx = (x - b1) / (bw - Tx);
                    if (idx > 2) idx = 2;
                    int o = g_settings.order;
                    int type = 0;
                    if (o == 0) type = (idx == 0) ? 3 : (idx == 1 ? 1 : 2);
                    else if (o == 1) type = (idx == 0) ? 3 : (idx == 1 ? 2 : 1);
                    else type = (idx == 0) ? 1 : (idx == 1 ? 2 : 3);

                    if (type == 3) return HTCLOSE;
                    if (type == 2) return HTMAXBUTTON;
                    if (type == 1) return HTMINBUTTON;
                }
            }
        }
    }
    if (msg == WM_NCLBUTTONDOWN && LeftActiveFor(hwnd)) {
        if (wParam == HTCLOSE) { PostMessage(hwnd, WM_SYSCOMMAND, SC_CLOSE, lParam); return 0; }
        if (wParam == HTMINBUTTON) { PostMessage(hwnd, WM_SYSCOMMAND, SC_MINIMIZE, lParam); return 0; }
        if (wParam == HTMAXBUTTON) { PostMessage(hwnd, WM_SYSCOMMAND, IsZoomed(hwnd) ? SC_RESTORE : SC_MAXIMIZE, lParam); return 0; }
    }
    if (msg == WM_NCDESTROY) {
        KillTimer(hwnd, kRescanTimerId);
        RemovePropW(hwnd, L"CaptionButtonsTicks");
        WindhawkUtils::RemoveWindowSubclassFromAnyThread(hwnd, CabinetSubclassProc);
    }
    return DefSubclassProc(hwnd, msg, wParam, lParam);
}

static HWND WINAPI CreateWindowExW_Hook(DWORD ex, LPCWSTR cls, LPCWSTR name, DWORD style, int x, int y, int w, int h,
                                         HWND parent, HMENU menu, HINSTANCE inst, LPVOID param) {
    HWND r = CreateWindowExW_Orig(ex, cls, name, style, x, y, w, h, parent, menu, inst, param);
    if (r && !IS_INTRESOURCE(cls)) {
        if (parent && IsTabBridgeClass(cls)) {
            if (TryAttach(r)) TabNudge(r);
        } else if (!parent && wcscmp(cls, L"CabinetWClass") == 0) {
            WindhawkUtils::SetWindowSubclassFromAnyThread(r, CabinetSubclassProc, 0);
            StartRescan(r);
        }
    }
    return r;
}

// Existing windows: attach and apply. Also lists every child window (debug log) so the
// right class can be identified if the island is not found.
static BOOL CALLBACK ExChildProc(HWND h, LPARAM) {
    if (g_settings.debugLog) {
        wchar_t cls[128] = L"";
        GetClassNameW(h, cls, 128);
        RECT r = {};
        GetRectInParent(h, &r);
        ExLog(L"[Child] hwnd=%p class=%s rect=(%ld,%ld,%ld,%ld)", h, cls, r.left, r.top, r.right, r.bottom);
    }
    if (TryAttach(h)) {
        TabNudge(h);
    } else {
        // Already attached but not shifted yet: force the shift
        HWND hw[32]; int applied[32]; bool isTab[32];
        int n = TabSnapshot(hw, applied, isTab);
        for (int i = 0; i < n; i++) {
            if (hw[i] == h && applied[i] == 0) { TabNudge(h); break; }
        }
    }
    {
        wchar_t c2[128] = L"";
        GetClassNameW(h, c2, 128);
        if (wcsstr(c2, L"DesktopChildSiteBridge")) ApplyButtonHole(h);
    }
    return TRUE;
}

static BOOL CALLBACK ExTopProc(HWND h, LPARAM) {
    DWORD pid = 0;
    GetWindowThreadProcessId(h, &pid);
    if (pid != GetCurrentProcessId()) return TRUE;
    wchar_t cls[64] = L"";
    GetClassNameW(h, cls, 64);
    if (wcscmp(cls, L"CabinetWClass") == 0) {
        WindhawkUtils::SetWindowSubclassFromAnyThread(h, CabinetSubclassProc, 0);
        EnumChildWindows(h, ExChildProc, 0);
    }
    return TRUE;
}

static int TabSnapshot(HWND* hw, int* applied, bool* isTab) {
    int n = 0;
    AcquireSRWLockShared(&g_tabLock);
    for (int i = 0; i < 32; i++) {
        if (g_tabs[i].hwnd) {
            hw[n] = g_tabs[i].hwnd;
            applied[n] = g_tabs[i].applied;
            isTab[n] = g_tabs[i].isTab;
            n++;
        }
    }
    ReleaseSRWLockShared(&g_tabLock);
    return n;
}

// After a settings change: move every known tab bar to the shift of the new settings
static void ExplorerReapply() {
    HWND hw[32];
    int applied[32];
    bool isTab[32];
    int n = TabSnapshot(hw, applied, isTab);
    for (int i = 0; i < n; i++) {
        if (!IsWindow(hw[i])) continue;
        if (!isTab[i]) { TabNudge(hw[i]); continue; }
        int desired = ComputeTabShift(hw[i]);
        int delta = desired - applied[i];
        if (delta) {
            TabMoveBy(hw[i], delta);
            TabSetState(hw[i], desired, true);
        }
    }
}

// Removes CabinetSubclassProc from every File Explorer frame of this process.
// The rescan timer and the window property belong to the window's thread, so
// the subclass cleans them up itself when it receives g_msgCleanup.
static BOOL CALLBACK ExTopUninitProc(HWND h, LPARAM) {
    DWORD pid = 0;
    GetWindowThreadProcessId(h, &pid);
    if (pid != GetCurrentProcessId()) return TRUE;
    wchar_t cls[64] = L"";
    GetClassNameW(h, cls, 64);
    if (wcscmp(cls, L"CabinetWClass") != 0) return TRUE;

    DWORD_PTR res = 0;
    if (!g_msgCleanup || !SendMessageTimeoutW(h, g_msgCleanup, 0, 0, SMTO_ABORTIFHUNG, 1000, &res)) {
        // The window did not answer: remove the subclass directly
        WindhawkUtils::RemoveWindowSubclassFromAnyThread(h, CabinetSubclassProc);
    }
    return TRUE;
}

static void ExplorerUninit() {
    EnumWindows(ExTopUninitProc, 0);
    HWND hw[32];
    int applied[32];
    bool isTab[32];
    int n = TabSnapshot(hw, applied, isTab);
    for (int i = 0; i < n; i++) {
        if (!IsWindow(hw[i])) continue;
        if (applied[i]) TabMoveBy(hw[i], -applied[i]);   // put the tab bar back (Explorer re-lays it out on the next resize)
        SetWindowRgn(hw[i], nullptr, TRUE);
        WindhawkUtils::RemoveWindowSubclassFromAnyThread(hw[i], TabSubclassProc);
        TabRemove(hw[i]);
    }
}

// ---------------- icon storage writer (explorer.exe) ----------------
// explorer.exe can read the user's folders, dwm.exe usually cannot. So the images are
// decoded and shrunk here, and the raw pixels are handed to dwm.exe through the mod's
// storage (see IconValueName). dwm.exe never opens or decodes an image file.
static void SyncIconCache() {
    g_debug = g_settings.debugLog ? 1 : 0;   // DecodeImage reports through LogCat

    IconSettings s;
    ReadIconSettings(&s);   // s.any is false unless the Custom images style is selected

    IconImg img[4][4] = {};
    if (s.any) {
        HRESULT hrInit = CoInitializeEx(nullptr, COINIT_MULTITHREADED);
        IWICImagingFactory* fac = nullptr;
        HRESULT hr = CoCreateInstance(kCLSID_WICFactory, nullptr, CLSCTX_INPROC_SERVER, kIID_WICFactory, (void**)&fac);
        if (SUCCEEDED(hr) && fac) {
            for (int kind = 0; kind < 4; kind++) {
                for (int st = 0; st < 4; st++) {
                    wchar_t cand[MAX_PATH + 32];
                    if (FindIconFile(s, kind, st, cand)) DecodeImage(fac, cand, &img[kind][st]);
                }
            }
            fac->Release();
        } else {
            ExLog(L"[IconCache] CoCreateInstance WIC failed hr=0x%lx", (unsigned long)hr);
        }
        if (SUCCEEDED(hrInit)) CoUninitialize();
    }

    int stored = 0;
    for (int kind = 0; kind < 4; kind++) {
        for (int st = 0; st < 4; st++) {
            wchar_t name[32];
            IconValueName(kind, st, name, 32);
            IconImg& im = img[kind][st];
            bool ok = false;
            if (im.px) {
                size_t bytes = (size_t)im.w * im.h * 4;
                BYTE* blob = (BYTE*)malloc(8 + bytes);
                if (blob) {
                    memcpy(blob, &im.w, 4);
                    memcpy(blob + 4, &im.h, 4);
                    memcpy(blob + 8, im.px, bytes);
                    ok = Wh_SetBinaryValue(name, blob, 8 + bytes) != FALSE;
                    free(blob);
                }
                free(im.px);
            }
            if (ok) stored++;
            else Wh_DeleteValue(name);   // setting removed, file gone or store failed: no stale image
        }
    }
    // Tell dwm.exe to reload
    Wh_SetIntValue(L"iconCacheVersion", Wh_GetIntValue(L"iconCacheVersion", 0) + 1);
    ExLog(L"[IconCache] synced, %d image(s) stored", stored);
}

// Removes the stored images (called when the mod is unloaded).
static void CleanIconCache() {
    for (int kind = 0; kind < 4; kind++) {
        for (int st = 0; st < 4; st++) {
            wchar_t name[32];
            IconValueName(kind, st, name, 32);
            Wh_DeleteValue(name);
        }
    }
}

static void LoadUser32Procs() {
    HMODULE user32 = GetModuleHandleW(L"user32.dll");
    if (user32) {
        g_pGetDpiForWindow = (GetDpiForWindow_t)GetProcAddress(user32, "GetDpiForWindow");
        g_pGetDpiForSystem = (GetDpiForSystem_t)GetProcAddress(user32, "GetDpiForSystem");
        g_pSPIForDpi = (SPIForDpi_t)GetProcAddress(user32, "SystemParametersInfoForDpi");
        g_pInternalGetWindowText = (InternalGetWindowText_t)GetProcAddress(user32, "InternalGetWindowText");
        g_pIsHungAppWindow = (IsHungAppWindow_t)GetProcAddress(user32, "IsHungAppWindow");
    }
}

static BOOL ExplorerInit() {
    LoadSettings();     // moveButtons, leftMargin, exclusions
    SyncIconCache();    // copy custom images where dwm.exe can read them
    ExLoadSettings();
    LoadUser32Procs();
    g_msgCleanup = RegisterWindowMessageW(L"CaptionButtonsCustomizer_RemoveSubclass");
    Wh_SetFunctionHook((void*)CreateWindowExW, (void*)CreateWindowExW_Hook, (void**)&CreateWindowExW_Orig);
    return TRUE;
}

// ======================================================================
//  Lifecycle (all parts)
// ======================================================================
// Asks DWM to refresh itself (as if the system colors changed). DWM then lays out every
// window again, so no window has to be resized.
static void RequestDwmRefresh() {
    HWND hDwm = FindWindowW(L"Dwm", nullptr);
    if (!hDwm) {
        Wh_Log(L"DWM notification window wasn't found");
        return;
    }
    PostMessageW(hDwm, WM_SYSCOLORCHANGE, 0, 0);
}
static unsigned long long Fnv(unsigned long long h, unsigned long long v) {
    h ^= v;
    h *= 1099511628211ull;
    return h;
}

// Hash of every setting that changes where DWM puts the buttons, icon and title,
// including the exclusion lists. Colors, images, the restart option and the
// debug log are not part of it, so changing them does not trigger a relayout.
static unsigned long long LayoutSignature() {
    unsigned long long h = 1469598103934665603ull;
    h = Fnv(h, (unsigned long long)(long long)g_settings.moveButtons);
    h = Fnv(h, (unsigned long long)(long long)g_settings.leftMargin);
    h = Fnv(h, (unsigned long long)(long long)g_settings.tighten);
    h = Fnv(h, (unsigned long long)(long long)g_settings.explorerMargin);
    h = Fnv(h, (unsigned long long)(long long)g_settings.order);
    h = Fnv(h, (unsigned long long)(long long)g_settings.showDialogClose);
    h = Fnv(h, (unsigned long long)(long long)g_settings.titleAlign);
    h = Fnv(h, (unsigned long long)(long long)g_settings.dialogAlign);
    h = Fnv(h, (unsigned long long)(long long)g_settings.centerOnText);
    h = Fnv(h, (unsigned long long)(long long)g_settings.centerNudge);
    h = Fnv(h, (unsigned long long)(long long)g_settings.iconPosition);
    h = Fnv(h, (unsigned long long)(long long)g_settings.iconSide);
    h = Fnv(h, (unsigned long long)(long long)g_settings.titleGap);
    h = Fnv(h, (unsigned long long)(long long)g_settings.iconTitleGap);
    h = Fnv(h, (unsigned long long)(long long)g_settings.rightEdgeGap);
    h = Fnv(h, (unsigned long long)(long long)g_settings.hideIcon);
    h = Fnv(h, (unsigned long long)(long long)g_settings.hideTitle);

    AcquireSRWLockShared(&g_exclLock);
    h = Fnv(h, (unsigned long long)g_exclExeN);
    for (int i = 0; i < g_exclExeN; i++) {
        for (const wchar_t* p = g_exclExe[i]; *p; p++) h = Fnv(h, (unsigned long long)*p);
        h = Fnv(h, 0);
    }
    h = Fnv(h, (unsigned long long)g_exclClsN);
    for (int i = 0; i < g_exclClsN; i++) {
        for (const wchar_t* p = g_exclCls[i]; *p; p++) h = Fnv(h, (unsigned long long)*p);
        h = Fnv(h, 0);
    }
    ReleaseSRWLockShared(&g_exclLock);
    return h;
}

// Hash of the settings that change how the buttons are painted (not where they are).
static unsigned long long PaintSignature() {
    unsigned long long h = 1469598103934665603ull;
    h = Fnv(h, (unsigned long long)(long long)g_tlEnabled);
    for (int r = 0; r < 3; r++)
        for (int c = 0; c < 3; c++)
            h = Fnv(h, (unsigned long long)(long long)g_base[r][c]);
    h = Fnv(h, (unsigned long long)g_styleCustom);
    return h;
}

void Sec_ModSettingsChanged() {
    if (g_isExplorer) {
        LoadSettings();
        ExLoadSettings();
        SyncIconCache();
        ExplorerReapply();
        EnumWindows(ExTopProc, 0);
        return;
    }
    LONG iconVerBefore = (LONG)Wh_GetIntValue(L"iconCacheVersion", 0);
    bool wasCustom = g_styleCustom != 0;
    unsigned long long sigBefore = LayoutSignature();
    unsigned long long paintBefore = PaintSignature();
    LoadSettings();       // layout (including the excluded apps lists)
    TL_LoadSettings();    // painter
    InterlockedExchange(&g_pending, 1);   // repaint on the next DWM-thread hook call
    // Open windows need a new layout when a layout setting (or the exclusion lists) or the
    // painting changed. DWM refreshes itself and lays out every window again; no window is resized.
    bool refresh = (LayoutSignature() != sigBefore) || (PaintSignature() != paintBefore);

    // Custom images: explorer.exe decodes the images and bumps iconCacheVersion.
    // Wait for it (max ~2 s), so the DWM thread loads and paints them on the refresh.
    if (g_tlEnabled && (wasCustom || g_styleCustom)) {
        for (int i = 0; i < 40 && (LONG)Wh_GetIntValue(L"iconCacheVersion", 0) == iconVerBefore; i++) {
            Sleep(50);
        }
        InterlockedExchange(&g_pending, 1);
        refresh = true;
    }

    if (refresh) RequestDwmRefresh();
}

// Called by Windhawk just before the mod is unloaded, while the hooks still work
void Sec_ModBeforeUninit() {
    if (g_isExplorer) return;
    InterlockedExchange(&g_unloading, 1);
    // DWM lays every window out again; with g_unloading set the hooks restore the default layout
    RequestDwmRefresh();
    for (int i = 0; i < 25 && g_unloadRelayouts == 0; i++) Sleep(20);   // wait up to ~0.5 second
    if (g_unloadRelayouts > 0) Sleep(50);                               // let the layout pass finish
    Wh_Log(L"[Unload] DWM refresh requested, %ld layout(s) handled", (long)g_unloadRelayouts);
}

// dwm.exe starts before explorer.exe, so the images are not in the mod storage yet when
// dwm.exe loads the mod. This thread waits until explorer.exe has stored them (it bumps
// iconCacheVersion), then asks DWM to refresh so that the images are loaded and painted.
static HANDLE g_iconWaitThread = nullptr;

static DWORD WINAPI IconWaitThread(LPVOID) {
    for (int i = 0; i < 100 && !g_unloading; i++) {   // up to ~10 seconds
        Sleep(100);
        if ((LONG)Wh_GetIntValue(L"iconCacheVersion", 0) != g_iconVerSeen) {
            InterlockedExchange(&g_pending, 1);
            RequestDwmRefresh();
            break;
        }
    }
    return 0;
}

void Sec_ModAfterInit() {
    if (g_isExplorer) {
        EnumWindows(ExTopProc, 0);   // File Explorer windows that already exist
    } else {
        RequestDwmRefresh();         // windows that are already open get the new layout right away
        if (g_tlEnabled && g_styleCustom) {
            g_iconWaitThread = CreateThread(nullptr, 0, IconWaitThread, nullptr, 0, nullptr);
        }
    }
}

void Sec_ModUninit() {
    if (g_isExplorer) {
        ExplorerUninit();
        CleanIconCache();
        return;
    }
    if (g_iconWaitThread) {
        InterlockedExchange(&g_unloading, 1);   // make sure the thread stops even if Sec_ModBeforeUninit was skipped
        WaitForSingleObject(g_iconWaitThread, INFINITE);   // the thread checks g_unloading every 100 ms
        CloseHandle(g_iconWaitThread);
        g_iconWaitThread = nullptr;
    }
    if (g_menuTimer) {
        SetThreadpoolTimer(g_menuTimer, nullptr, 0, 0);
        WaitForThreadpoolTimerCallbacks(g_menuTimer, TRUE);
        CloseThreadpoolTimer(g_menuTimer);
        g_menuTimer = nullptr;
    }
    if (g_nudgeThread) {
        InterlockedExchange(&g_unloading, 1);
        WaitForSingleObject(g_nudgeThread, INFINITE);   // the thread checks g_unloading every 100 ms and sends at most two 300 ms messages
        CloseHandle(g_nudgeThread);
        g_nudgeThread = nullptr;
    }
    if (g_everPainted && g_restartOnUnload) RestartDwm();
    FreeIcons();
}

// Crash-loop guard: refuse to load when dwm.exe started 4 or more times within 60 seconds.
// Recompiling the mod inside the same dwm.exe does not count (same process start time).
static bool IsDwmRestartLoop() {
    FILETIME ct, et, kt, ut, nowFt;
    if (!GetProcessTimes(GetCurrentProcess(), &ct, &et, &kt, &ut)) return false;
    GetSystemTimeAsFileTime(&nowFt);
    ULONGLONG start = ((ULONGLONG)ct.dwHighDateTime << 32) | ct.dwLowDateTime;
    ULONGLONG now = ((ULONGLONG)nowFt.dwHighDateTime << 32) | nowFt.dwLowDateTime;
    const ULONGLONG kWindow = 60ULL * 10000000ULL;

    ULONGLONG stored[8] = {};
    size_t got = Wh_GetBinaryValue(L"dwmStartTimes", stored, sizeof(stored));
    int storedN = (int)(got / sizeof(ULONGLONG));
    if (storedN > 8) storedN = 8;

    ULONGLONG keep[8] = {};
    int n = 0;
    for (int i = 0; i < storedN; i++) {
        if (stored[i] != start && now >= stored[i] && now - stored[i] <= kWindow && n < 7)
            keep[n++] = stored[i];
    }
    keep[n++] = start;
    Wh_SetBinaryValue(L"dwmStartTimes", keep, n * sizeof(ULONGLONG));
    return n >= 4;
}

BOOL Sec_ModInit() {
    // The mod runs in two processes: dwm.exe (buttons, glyphs) and explorer.exe (tab bar)
    wchar_t exePath[MAX_PATH] = L"";
    GetModuleFileNameW(nullptr, exePath, MAX_PATH);
    const wchar_t* exeName = wcsrchr(exePath, L'\\');
    exeName = exeName ? exeName + 1 : exePath;
    g_isExplorer = _wcsicmp(exeName, L"explorer.exe") == 0;
    if (g_isExplorer) return ExplorerInit();
    if (IsDwmRestartLoop()) {
        Wh_Log(L"dwm.exe started 4 or more times within a minute, the mod stays unloaded for safety");
        return FALSE;
    }

    LoadSettings();
    TL_LoadSettings();

    LoadUser32Procs();

    HMODULE udwm = GetModuleHandleW(L"udwm.dll");
    if (!udwm) return FALSE;

    WindhawkUtils::SYMBOL_HOOK udwmDllHooks[] = {
        // ---- Layout ----
        { { LR"(public: void __cdecl CTopLevelWindow::GetTitleBarInfo(struct tagTITLEBARINFOEX *,bool *))" },
          (void**)&GetTitleBarInfo_Orig, nullptr, false },
        { { LR"(private: long __cdecl CTopLevelWindow::UpdateNCAreaButton(enum CTopLevelWindow::ButtonType,int,int,int *))" },
          (void**)&UpdateNCAreaButton_Orig, (void*)UpdateNCAreaButton_Hook, false },
        { { LR"(private: long __cdecl CTopLevelWindow::UpdateNCAreaPositionsAndSizes(void))" },
          (void**)&PosAndSizes_Orig, (void*)PosAndSizes_Hook, true },
        { { LR"(public: void __cdecl CVisual::SetInsetFromParentTop(int))" },
          (void**)&SetInsetTop_Orig, (void*)SetInsetTop_Hook, false },
        { { LR"(public: void __cdecl CVisual::SetInsetFromParentLeft(int))" },
          (void**)&SetInsetLeft_Orig, (void*)SetInsetLeft_Hook, false },
        { { LR"(public: void __cdecl CVisual::SetInsetFromParentRight(int))" },
          (void**)&SetInsetRight_Orig, (void*)SetInsetRight_Hook, false },
        { { LR"(public: virtual bool __cdecl CTopLevelWindow::DoHitTest(struct tagPOINT const &,class CVisual * *,unsigned int *))" },
          (void**)&DoHitTest_Orig, (void*)DoHitTest_Hook, true },
        { { LR"(private: long __cdecl CTopLevelWindow::UpdateText(struct CTopLevelWindow::WindowFrame *))" },
          (void**)&UpdateText_Orig, (void*)UpdateText_Hook, true },
        { { LR"(public: void __cdecl CTopLevelWindow::OnTitleUpdated(void))" },
          (void**)&OnTitleUpdated_Orig, (void*)OnTitleUpdated_Hook, true },

        // ---- HWND lookup (address only, no hook) ----
        { { LR"(public: class CWindowData * __cdecl CTopLevelWindow::GetWindowData(void)const )" },
          (void**)&GetWindowData_Orig, nullptr, true },
        { { LR"(public: bool __cdecl CWindowData::IsGhostWindow(struct HWND__ * *)const )" },
          (void**)&IsGhostWindow_Func, nullptr, true },
        // ---- Glyph painter ----
        { { LR"(public: long __cdecl CButton::SetVisualStates(class CBitmapSourceArray const &,class CBitmapSourceArray const &,float))" },
          (void**)&SetVisualStates_Orig, (void*)SetVisualStates_Hook, true },
        { { LR"(public: void __cdecl CAtlasedImage::SetBitmapSource(class CBitmapSource *))" },
          (void**)&ImgSetBmp_Orig, (void*)ImgSetBmp_Hook, true },
        { { LR"(public: void __cdecl CAtlasButton::SetGlyphImage(class CBitmapSource *,enum CAtlasButton::VerticalAlignment,int))" },
          (void**)&SetGlyph_Orig, (void*)SetGlyph_Hook, true },
        { { LR"(public: void __cdecl CAtlasedImage::SetSize(struct tagSIZE const &))" },
          (void**)&ImgSetSize_Orig, (void*)ImgSetSize_Hook, true },
        { { LR"(private: void __cdecl CButton::UpdateAtlasPositionAndSize(void))" },
          (void**)&UpdatePos_Orig, (void*)UpdatePos_Hook, true },

        // Address only (no hook): called by PaintAtlas
        { { LR"(private: long __cdecl CBitmapSource::Update(struct IWICBitmap *))" },
          (void**)&g_updateBmp, nullptr, true },
        // Frees of glyph objects: drop them from our registries
        { { LR"(protected: virtual __cdecl CBitmapSource::~CBitmapSource(void))" },
          (void**)&BmpDtor_Orig, (void*)BmpDtor_Hook, true },
    };

    BOOL ok = WindhawkUtils::HookSymbols(udwm, udwmDllHooks, ARRAYSIZE(udwmDllHooks));
    if (ok) g_menuTimer = CreateThreadpoolTimer(MenuTimerCallback, nullptr, nullptr);
    g_hasPosHook = (PosAndSizes_Orig != nullptr);
    DeriveHwndOffset();

    if (!g_updateBmp) Wh_Log(L"CBitmapSource::Update not found, custom button styles will not be painted");
    if (!BmpDtor_Orig) Wh_Log(L"CBitmapSource destructor not found, freed glyph objects are not tracked");
    return ok;
}
}  // namespace caption

// ==========================================================================
//  Store apps (ApplicationFrameHost.exe)
// ==========================================================================
namespace uwp {
#ifndef WM_POPUPSYSTEMMENU
#define WM_POPUPSYSTEMMENU 0x0313
#endif

// DWM draws neither the accent blur nor a system backdrop on frame windows, and
// the frame host already owns both composition targets of the frame
// (DCOMPOSITION_ERROR_WINDOW_ALREADY_COMPOSED), all measured. So each native
// frame gets a click-through backdrop window kept directly beneath it, holding
// a HostBackdropBrush (the source XAML's AcrylicBrush uses) under a tint. The
// see-through caption shows it; the app content covers the rest.
namespace material {

namespace composition = winrt::Windows::UI::Composition;

MIDL_INTERFACE("29E691FA-4567-4DCA-B319-D0F207EB6807")
DesktopInterop : IUnknown {
    virtual HRESULT STDMETHODCALLTYPE CreateDesktopWindowTarget(HWND, BOOL,
                                                                void**) = 0;
    virtual HRESULT STDMETHODCALLTYPE EnsureOnThread(DWORD) = 0;
};

constexpr UINT kAttach = WM_APP + 1;  // wParam: frame
constexpr UINT kDetach = WM_APP + 2;  // wParam: frame
constexpr UINT kTint = WM_APP + 3;    // wParam: tint alpha
constexpr UINT kStop = WM_APP + 4;
constexpr UINT kSync = WM_APP + 5;  // wParam: frame
constexpr WCHAR kClass[] = L"RemoveUwpTitleBarsPlus_Backdrop";
// The sprite covers the whole backdrop window, which clips it.
constexpr float kCover = 16384.0f;

struct Target {
    HWND wnd = nullptr;
    composition::Desktop::DesktopWindowTarget target{nullptr};
    composition::CompositionColorBrush shade{nullptr};
};

HANDLE g_thread, g_ready;
DWORD g_threadId;
volatile LONG g_tintAlpha;
std::unordered_map<HWND, Target>* g_targets;  // worker thread only

winrt::Windows::UI::Color TintColor() {
    return {(BYTE)g_tintAlpha, 0x1E, 0x1E, 0x2E};  // #1E1E2E
}

void Close(std::unordered_map<HWND, Target>& targets, HWND hWnd) {
    auto it = targets.find(hWnd);
    if (it == targets.end()) {
        return;
    }
    try {
        it->second.target.Close();
    } catch (...) {
    }
    DestroyWindow(it->second.wnd);
    targets.erase(it);
}

// Keeps the backdrop on the frame's bounds, right below it, and hidden while
// the frame is hidden, minimized or cloaked (another virtual desktop).
void Sync(const Target& t, HWND frame) {
    DWORD cloaked = 0;
    DwmGetWindowAttribute(frame, DWMWA_CLOAKED, &cloaked, sizeof(cloaked));
    RECT r;
    if (!IsWindowVisible(frame) || IsIconic(frame) || cloaked ||
        FAILED(DwmGetWindowAttribute(frame, DWMWA_EXTENDED_FRAME_BOUNDS, &r,
                                     sizeof(r)))) {
        if (IsWindowVisible(t.wnd)) {
            ShowWindow(t.wnd, SW_HIDE);
        }
        return;
    }
    SetWindowPos(t.wnd, frame, r.left, r.top, r.right - r.left,
                 r.bottom - r.top,
                 SWP_NOACTIVATE | SWP_SHOWWINDOW | SWP_NOOWNERZORDER);
}

LRESULT CALLBACK BackdropProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
        case WM_NCHITTEST:
            return HTTRANSPARENT;
        case WM_MOUSEACTIVATE:
            return MA_NOACTIVATE;
    }
    return DefWindowProc(hWnd, msg, wParam, lParam);
}

void CALLBACK CloakEvent(HWINEVENTHOOK,
                         DWORD,
                         HWND hWnd,
                         LONG object,
                         LONG child,
                         DWORD,
                         DWORD) {
    if (object != OBJID_WINDOW || child != CHILDID_SELF || !g_targets) {
        return;
    }
    auto it = g_targets->find(hWnd);
    if (it != g_targets->end()) {
        Sync(it->second, hWnd);
    }
}

void Attach(composition::Compositor& compositor,
            std::unordered_map<HWND, Target>& targets,
            HINSTANCE instance,
            HWND hWnd) {
    if (targets.count(hWnd) || !IsWindow(hWnd)) {
        return;
    }
    Target t;
    try {
        t.wnd = CreateWindowEx(WS_EX_TOOLWINDOW | WS_EX_NOACTIVATE |
                                   WS_EX_TRANSPARENT |
                                   WS_EX_NOREDIRECTIONBITMAP,
                               kClass, L"", WS_POPUP, 0, 0, 0, 0, nullptr,
                               nullptr, instance, nullptr);
        if (!t.wnd) {
            winrt::throw_last_error();
        }
        BOOL on = TRUE;
        DwmSetWindowAttribute(t.wnd, DWMWA_USE_HOSTBACKDROPBRUSH, &on,
                              sizeof(on));
        DwmSetWindowAttribute(t.wnd, DWMWA_EXCLUDED_FROM_PEEK, &on, sizeof(on));
        DWM_WINDOW_CORNER_PREFERENCE corner = DWMWCP_ROUND;
        DwmSetWindowAttribute(t.wnd, DWMWA_WINDOW_CORNER_PREFERENCE, &corner,
                              sizeof(corner));
        COLORREF none = DWMWA_COLOR_NONE;
        DwmSetWindowAttribute(t.wnd, DWMWA_BORDER_COLOR, &none, sizeof(none));
        winrt::com_ptr<DesktopInterop> interop;
        winrt::check_hresult(winrt::get_unknown(compositor)->QueryInterface(
            GUID{0x29E691FA,
                 0x4567,
                 0x4DCA,
                 {0xB3, 0x19, 0xD0, 0xF2, 0x07, 0xEB, 0x68, 0x07}},
            interop.put_void()));
        winrt::check_hresult(interop->CreateDesktopWindowTarget(
            t.wnd, FALSE, winrt::put_abi(t.target)));
        auto root = compositor.CreateContainerVisual();
        auto blur = compositor.CreateSpriteVisual();
        blur.Brush(compositor.CreateHostBackdropBrush());
        blur.Size({kCover, kCover});
        auto shade = compositor.CreateSpriteVisual();
        t.shade = compositor.CreateColorBrush(TintColor());
        shade.Brush(t.shade);
        shade.Size({kCover, kCover});
        root.Children().InsertAtBottom(blur);
        root.Children().InsertAtTop(shade);
        t.target.Root(root);
        Sync(t, hWnd);
        targets.emplace(hWnd, std::move(t));
        Wh_Log(L"Material on %p", hWnd);
    } catch (const winrt::hresult_error& e) {
        Wh_Log(L"Material failed on %p: %08X", hWnd, (unsigned)e.code());
        if (t.wnd) {
            DestroyWindow(t.wnd);
        }
    }
}

DWORD WINAPI Run(void*) {
    MSG msg;
    PeekMessage(&msg, nullptr, WM_USER, WM_USER, PM_NOREMOVE);
    std::unordered_map<HWND, Target> targets;
    winrt::Windows::System::DispatcherQueueController queue{nullptr};
    composition::Compositor compositor{nullptr};
    HMODULE messaging = nullptr;
    HRESULT apartment = RoInitialize(RO_INIT_SINGLETHREADED);
    try {
        winrt::check_hresult(apartment);
        struct Options {
            DWORD size, thread, apartment;
        } options{sizeof(Options), 2, 2};  // current thread, STA
        using Create = HRESULT(WINAPI*)(Options, void**);
        messaging = LoadLibraryEx(L"CoreMessaging.dll", nullptr,
                                  LOAD_LIBRARY_SEARCH_SYSTEM32);
        auto create = messaging ? (Create)GetProcAddress(
                                      messaging,
                                      "CreateDispatcherQueueController")
                                : nullptr;
        if (!create) {
            throw winrt::hresult_error(HRESULT_FROM_WIN32(ERROR_PROC_NOT_FOUND));
        }
        winrt::check_hresult(create(options, winrt::put_abi(queue)));
        compositor = composition::Compositor();
    } catch (const winrt::hresult_error& e) {
        Wh_Log(L"Compositor unavailable: %08X", (unsigned)e.code());
    }
    HINSTANCE instance = nullptr;
    GetModuleHandleEx(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS |
                          GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT,
                      (LPCWSTR)BackdropProc, &instance);
    WNDCLASS wc = {};
    wc.lpfnWndProc = BackdropProc;
    wc.hInstance = instance;
    wc.lpszClassName = kClass;
    ATOM atom = RegisterClass(&wc);
    g_targets = &targets;
    HWINEVENTHOOK cloakHook = SetWinEventHook(
        EVENT_OBJECT_CLOAKED, EVENT_OBJECT_UNCLOAKED, nullptr, CloakEvent,
        GetCurrentProcessId(), 0, WINEVENT_OUTOFCONTEXT);
    SetEvent(g_ready);

    while (GetMessage(&msg, nullptr, 0, 0) > 0 && msg.message != kStop) {
        if (msg.message == kAttach) {
            if (compositor && atom) {
                Attach(compositor, targets, instance, (HWND)msg.wParam);
            }
        } else if (msg.message == kDetach) {
            Close(targets, (HWND)msg.wParam);
        } else if (msg.message == kSync) {
            auto it = targets.find((HWND)msg.wParam);
            if (it != targets.end()) {
                Sync(it->second, it->first);
            }
        } else if (msg.message == kTint) {
            for (auto& t : targets) {
                try {
                    t.second.shade.Color(TintColor());
                } catch (...) {
                }
            }
        } else {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    if (cloakHook) {
        UnhookWinEvent(cloakHook);
    }
    while (!targets.empty()) {
        Close(targets, targets.begin()->first);
    }
    g_targets = nullptr;
    if (atom) {
        UnregisterClass(kClass, instance);
    }
    try {
        if (compositor) {
            compositor.Close();
        }
    } catch (...) {
    }
    compositor = nullptr;
    if (queue) {
        try {
            // Let the queue finish shutting down before the module unloads.
            auto done = queue.ShutdownQueueAsync();
            while (done.Status() ==
                   winrt::Windows::Foundation::AsyncStatus::Started) {
                if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
                    TranslateMessage(&msg);
                    DispatchMessage(&msg);
                } else {
                    MsgWaitForMultipleObjects(0, nullptr, FALSE, 50,
                                              QS_ALLINPUT);
                }
            }
        } catch (...) {
        }
        queue = nullptr;
    }
    if (SUCCEEDED(apartment)) {
        RoUninitialize();
    }
    return 0;
}

void Post(UINT msg, WPARAM wParam) {
    if (g_threadId) {
        PostThreadMessage(g_threadId, msg, wParam, 0);
    }
}

void SetTint(int percent) {
    InterlockedExchange(&g_tintAlpha, percent * 255 / 100);
    Post(kTint, 0);
}

bool Start() {
    g_ready = CreateEvent(nullptr, TRUE, FALSE, nullptr);
    g_thread = CreateThread(nullptr, 0, Run, nullptr, 0, &g_threadId);
    if (!g_thread) {
        g_threadId = 0;
        return false;
    }
    WaitForSingleObject(g_ready, 5000);
    return true;
}

void Stop() {
    if (g_thread) {
        Post(kStop, 0);
        WaitForSingleObject(g_thread, 5000);
        CloseHandle(g_thread);
        g_thread = nullptr;
        g_threadId = 0;
    }
    if (g_ready) {
        CloseHandle(g_ready);
        g_ready = nullptr;
    }
}

}  // namespace material

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
    bool blurred = false;              // kept active by ApplyMaterial
};

struct {
    bool blur;
    int tint;  // percent
} g_settings;

bool g_enabled;
SRWLOCK g_frameLock = SRWLOCK_INIT;
std::unordered_map<HWND, FrameInfo> g_frames;
std::unordered_map<void*, HWND> g_titleBarFrame;
UINT g_frameCheckMsg;
UINT g_frameRestoreMsg;
UINT g_frameMaterialMsg;
volatile LONG g_iconJobs;

using CreateTitleBarWindow_t = long(__cdecl*)(void* titleBar);
CreateTitleBarWindow_t CreateTitleBarWindow_Original;
using PaintButton_t =
    long(__cdecl*)(void*, void*, int, int, const RECT*, const RECT*);
PaintButton_t PaintButton_Original;
using DwmSetWindowAttribute_t = HRESULT(WINAPI*)(HWND, DWORD, LPCVOID, DWORD);
DwmSetWindowAttribute_t DwmSetWindowAttribute_Original;
using DwmExtendFrameIntoClientArea_t = HRESULT(WINAPI*)(HWND, const MARGINS*);
DwmExtendFrameIntoClientArea_t DwmExtendFrameIntoClientArea_Original;

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
        if (!buf[i] || (buf[i] >> 32) || !IsWindow(h)) {
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

// Puts the acrylic behind a native frame, or takes it away. The frame is made
// see-through (the -1 extension and blur-behind) so the material visual the
// worker thread places under the window shows in the caption strip.
void ApplyMaterial(HWND hWnd, bool blur) {
    AcquireSRWLockExclusive(&g_frameLock);
    bool was = std::exchange(g_frames[hWnd].blurred, blur);
    ReleaseSRWLockExclusive(&g_frameLock);
    Wh_Log(L"ApplyMaterial %p blur=%d was=%d", hWnd, blur, was);

    if (!blur) {
        if (was) {
            material::Post(material::kDetach, (WPARAM)hWnd);
            MARGINS margins = {};
            DwmExtendFrameIntoClientArea_Original(hWnd, &margins);
            DWM_BLURBEHIND bb = {DWM_BB_ENABLE, FALSE, nullptr, FALSE};
            DwmEnableBlurBehindWindow(hWnd, &bb);
            BOOL hostBackdrop = FALSE;
            DwmSetWindowAttribute_Original(hWnd, DWMWA_USE_HOSTBACKDROPBRUSH,
                                           &hostBackdrop,
                                           sizeof(hostBackdrop));
            DefWindowProc(hWnd, WM_NCACTIVATE,
                          GetForegroundWindow() == hWnd, -1);
        }
        return;
    }

    // Without this DWM gives the window's HostBackdropBrush nothing to draw.
    BOOL hostBackdrop = TRUE;
    DwmSetWindowAttribute_Original(hWnd, DWMWA_USE_HOSTBACKDROPBRUSH,
                                   &hostBackdrop, sizeof(hostBackdrop));
    MARGINS margins = {-1, -1, -1, -1};
    DwmExtendFrameIntoClientArea_Original(hWnd, &margins);
    HRGN region = CreateRectRgn(0, 0, -1, -1);
    DWM_BLURBEHIND bb = {DWM_BB_ENABLE | DWM_BB_BLURREGION, TRUE, region, FALSE};
    DwmEnableBlurBehindWindow(hWnd, &bb);
    if (region) {
        DeleteObject(region);
    }
    // A caption colour set by another mod before the frame went native would
    // cover the material; later ones are blocked in the DwmSetWindowAttribute
    // hook.
    COLORREF caption = DWMWA_COLOR_NONE;
    DwmSetWindowAttribute_Original(hWnd, DWMWA_CAPTION_COLOR, &caption,
                                   sizeof(caption));
    DefWindowProc(hWnd, WM_NCACTIVATE, TRUE, -1);
    material::Post(material::kAttach, (WPARAM)hWnd);
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

    ApplyMaterial(hWnd, g_settings.blur);

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
        if (info.blurred) {
            ApplyMaterial(hWnd, false);
        }
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
        } else {
            material::Post(material::kDetach, (WPARAM)hWnd);
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

    if (uMsg == g_frameMaterialMsg && uMsg) {
        ApplyMaterial(hWnd, g_settings.blur);
        SetWindowPos(hWnd, nullptr, 0, 0, 0, 0,
                     SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE |
                         SWP_FRAMECHANGED);
        return 0;
    }
    if (g_settings.blur &&
        (uMsg == WM_WINDOWPOSCHANGED || uMsg == WM_SHOWWINDOW)) {
        LRESULT r = DefSubclassProc(hWnd, uMsg, wParam, lParam);
        material::Post(material::kSync, (WPARAM)hWnd);
        return r;
    }
    if (uMsg == WM_NCACTIVATE && !wParam && g_settings.blur) {
        LRESULT r = DefSubclassProc(hWnd, uMsg, wParam, lParam);
        DefWindowProc(hWnd, WM_NCACTIVATE, TRUE, -1);
        return r;
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

void LoadSettings() {
    g_settings.blur = Wh_GetIntSetting(L"uwp.blur") != 0;
    g_settings.tint = std::clamp(Wh_GetIntSetting(L"uwp.tint"), 0, 100);
    material::SetTint(g_settings.tint);
}

void SettingsChanged() {
    LoadSettings();
    std::vector<HWND> frames;
    AcquireSRWLockShared(&g_frameLock);
    for (auto& f : g_frames) {
        if (f.second.state == FrameState::Native) {
            frames.push_back(f.first);
        }
    }
    ReleaseSRWLockShared(&g_frameLock);
    for (HWND hWnd : frames) {
        DWORD_PTR r;
        SendMessageTimeout(hWnd, g_frameMaterialMsg, 0, 0, SMTO_NORMAL, 2000,
                           &r);
    }
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
    material::Start();
    LoadSettings();
    g_frameMaterialMsg =
        RegisterWindowMessage(L"RemoveUwpTitleBarsPlus_ApplyMaterial");
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
        material::Stop();
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

BOOL Sec_ModInit() {
    Wh_Log(L">");
    return frame_host::Init();
}

void Sec_ModSettingsChanged() {
    Wh_Log(L">");
    frame_host::SettingsChanged();
}

void Sec_ModBeforeUninit() {
    Wh_Log(L">");
    // While the hooks are still in place, since restoring a frame calls the
    // original title bar function.
    frame_host::RestoreAllFrames();
}

void Sec_ModUninit() {
    Wh_Log(L">");
    material::Stop();
}
}  // namespace uwp

// ==========================================================================
//  Native frames (browsers, Office, Discord and others)
// ==========================================================================
namespace native {
enum WorkingMode {
    MODE_DEFAULT,
    MODE_OUTLOOK,
    MODE_CHROMIUM,
    MODE_VS
};

enum ClientEdgeSetting {
    CE_KEEP,
    CE_ADD,
    CE_REMOVE
};

struct tb4e_settings {
    bool btnFaceChrome = false;
    ClientEdgeSetting clientEdgeSetting = CE_KEEP;
    bool noToolWinSteam = false;
    bool noSteamHtmlInject = false;
} tb4e_settings;

WorkingMode mode = MODE_DEFAULT;

bool isSteam = false;
wchar_t steamIndexHtml[MAX_PATH];
wchar_t steamIndexHtmlModded[MAX_PATH];

bool isBrave = false;

#pragma region Subclassing
LRESULT CALLBACK HideSubclassProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, DWORD_PTR dwRefData) {
    switch (uMsg) {
        case WM_SHOWWINDOW:
            return 0;
        case WM_WINDOWPOSCHANGING: {
            WINDOWPOS* pos = (WINDOWPOS*)lParam;
            if (pos->flags & SWP_SHOWWINDOW) {
                pos->flags &= ~SWP_SHOWWINDOW;
                pos->flags |= SWP_HIDEWINDOW;
            }
            break;
        }
        case WM_WINDOWPOSCHANGED: {
            WINDOWPOS* pos = (WINDOWPOS*)lParam;
            if ((pos->flags & SWP_SHOWWINDOW) && IsWindowVisible(hWnd)) {
                ShowWindow(hWnd, SW_HIDE);  // Backup in case it still becomes visible
            }
            break;
        }
        default:
            break;
    }
    return DefSubclassProc(hWnd, uMsg, wParam, lParam);
}

LRESULT CALLBACK SubclassProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, DWORD_PTR dwRefData) {
    switch (uMsg) {
        case WM_PAINT:
            if (tb4e_settings.btnFaceChrome && mode == MODE_CHROMIUM && FindWindowExW(hWnd, NULL, L"Intermediate D3D Window", NULL))
            {
                PAINTSTRUCT ps;
                HDC hdc = BeginPaint(hWnd, &ps);
                RECT rect;
                GetClientRect(hWnd, &rect);
                FillRect(hdc, &rect, (HBRUSH)GetSysColorBrush(COLOR_BTNFACE));
                EndPaint(hWnd, &ps);
                return 0;
            }
            return DefSubclassProc(hWnd, uMsg, wParam, lParam);
        break;
        case WM_NCCALCSIZE:
            if (mode == MODE_OUTLOOK) {
                DefSubclassProc(hWnd, uMsg, wParam, lParam);
            }
            return DefWindowProc(hWnd, uMsg, wParam, lParam);
        case WM_NCPAINT:
            if (mode == MODE_CHROMIUM) {
                BOOL dwmEnabled = FALSE;
                DwmIsCompositionEnabled(&dwmEnabled);
                if (dwmEnabled) {
                    BOOL dwmFrameEnabled = FALSE;
                    HRESULT hr = DwmGetWindowAttribute(hWnd, DWMWA_NCRENDERING_ENABLED, &dwmFrameEnabled, sizeof(dwmFrameEnabled));
                    if (FAILED(hr) || dwmFrameEnabled) { // Potentially fix Aero Glass issues with Chromium browsers that still support it
                        return DefSubclassProc(hWnd, uMsg, wParam, lParam);
                    }
                }
                // If not, apply Chromium Basic/Classic NC paint fix from https://windhawk.net/mods/chromium-ncpaint-fix 
            }
        case WM_NCACTIVATE:
        case WM_NCHITTEST:
        case WM_NCLBUTTONDOWN:
            return DefWindowProc(hWnd, uMsg, wParam, lParam);
        case WM_DWMNCRENDERINGCHANGED:
            // Fix issues with hardware accelerated apps and basic themers
            RECT rect;
            GetWindowRect(hWnd, &rect);
            SetWindowPos(hWnd, NULL, rect.left, rect.top + 1, 0, 0, SWP_NOZORDER | SWP_NOOWNERZORDER | SWP_NOACTIVATE | SWP_NOSIZE);
            SetWindowPos(hWnd, NULL, rect.left, rect.top, 0, 0, SWP_FRAMECHANGED | SWP_NOZORDER | SWP_NOOWNERZORDER | SWP_NOACTIVATE | SWP_NOSIZE);
        default:
            return DefSubclassProc(hWnd, uMsg, wParam, lParam);
    }
}

void ProcessWindow(HWND hWnd, bool onlyUpdateStyle = false) {
    LONG style = GetWindowLongW(hWnd, GWL_STYLE);
    LONG exStyle = GetWindowLongW(hWnd, GWL_EXSTYLE);
    bool isToolWindow = (exStyle & WS_EX_TOOLWINDOW) != 0;

    if (isSteam && isToolWindow) {
        if (tb4e_settings.noToolWinSteam) {
            style &= ~(WS_CAPTION | WS_BORDER);
        } else {
            style |= WS_CAPTION | WS_BORDER;
        }
        SetWindowLongW(hWnd, GWL_STYLE, style);
        if (!onlyUpdateStyle) {
            if (WindhawkUtils::SetWindowSubclassFromAnyThread(hWnd, SubclassProc, 0)) {
                Wh_Log(L"Subclassed %p", hWnd);
            }
        }
        return;
    }

    // Exclude tool windows or child windows
    if (isToolWindow || GetAncestor(hWnd, GA_ROOT) != hWnd) {
        return;
    }

    // Fix a specific issue with Visual Studio's some windows
    // It simply renders nothing when WM_NCCALCSIZE is subclassed
    if (mode == MODE_VS && (exStyle & WS_EX_DLGMODALFRAME) != 0) {
        return;
    }

    if (!onlyUpdateStyle) {
        if (WindhawkUtils::SetWindowSubclassFromAnyThread(hWnd, SubclassProc, 0)) {
            Wh_Log(L"Subclassed %p", hWnd);
        }
    }

    style |= WS_CAPTION | WS_SYSMENU;
    switch (tb4e_settings.clientEdgeSetting) {
        case CE_ADD:
            exStyle |= WS_EX_CLIENTEDGE;
            break;
        case CE_REMOVE:
            exStyle &= ~WS_EX_CLIENTEDGE;
            break;
        case CE_KEEP:
            // do nothing
            // can't do anything on config change unfortunately
    }

    SetWindowLongW(hWnd, GWL_STYLE, style);
    SetWindowLongW(hWnd, GWL_EXSTYLE, exStyle);
    SetWindowPos(hWnd, NULL, 0, 0, 0, 0, SWP_FRAMECHANGED | SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_NOOWNERZORDER | SWP_NOACTIVATE);
}

void SetWinUICustomControlsVisibility(HWND parent, bool visible) {
    HWND ncInputSrcHwnd = FindWindowExW(parent, NULL, L"InputNonClientPointerSource", NULL);
    HWND windowControlHwnd = FindWindowExW(parent, NULL, L"ReunionWindowingCaptionControls", NULL);
    HWND teamsOverlayHwnd = FindWindowExW(parent, NULL, L"TeamsOverlay", NULL);
    if (ncInputSrcHwnd) {
        ShowWindow(ncInputSrcHwnd, visible);
        if (visible) {
            WindhawkUtils::RemoveWindowSubclassFromAnyThread(ncInputSrcHwnd, HideSubclassProc);
            Wh_Log(L"Restored InputNonClientPointerSource");
        } else {
            if (WindhawkUtils::SetWindowSubclassFromAnyThread(ncInputSrcHwnd, HideSubclassProc, 0)) {
                Wh_Log(L"Hid InputNonClientPointerSource (%p)", ncInputSrcHwnd);
            }
        }
    }
    if (windowControlHwnd) {
        ShowWindow(windowControlHwnd, visible);
        if (visible) {
            WindhawkUtils::RemoveWindowSubclassFromAnyThread(windowControlHwnd, HideSubclassProc);
            Wh_Log(L"Restored ReunionWindowingCaptionControls");
        } else {
            if (WindhawkUtils::SetWindowSubclassFromAnyThread(windowControlHwnd, HideSubclassProc, 0)) {
                Wh_Log(L"Hid ReunionWindowingCaptionControls (%p)", windowControlHwnd);
            }
        }
    }
    if (teamsOverlayHwnd) {
        ShowWindow(teamsOverlayHwnd, visible);
        if (visible) {
            WindhawkUtils::RemoveWindowSubclassFromAnyThread(teamsOverlayHwnd, HideSubclassProc);
            Wh_Log(L"Restored TeamsOverlay");
        } else {
            if (WindhawkUtils::SetWindowSubclassFromAnyThread(teamsOverlayHwnd, HideSubclassProc, 0)) {
                Wh_Log(L"Hid TeamsOverlay (%p)", teamsOverlayHwnd);
            }
        }
    }
}

BOOL CALLBACK InitEnumWindowsProc(HWND hWnd, LPARAM lParam) {
    HWND hParentWnd = GetAncestor(hWnd, GA_PARENT);
    if (hParentWnd && hParentWnd != GetDesktopWindow())
        return TRUE;

    bool isTarget = false;

    DWORD pid;
    GetWindowThreadProcessId(hWnd, &pid);
    // Subclass all relevant windows belonging to this process
    if (pid == GetCurrentProcessId()) {
        wchar_t className[256];
        GetClassName(hWnd, className, 256);
        // Chromium browsers / Electron apps / CEF top-level windows
        if (wcsncmp(className, L"Chrome_WidgetWin_", 17) == 0) {
            mode = MODE_CHROMIUM;
            isTarget = true;
        // WPF apps
        } else if (wcsncmp(className, L"HwndWrapper[", 12) == 0) {
            isTarget = true;
        // WinUI
        } else if (wcsncmp(className, L"WinUIDesktopWin32WindowClass", 28) == 0) {
            isTarget = true;
            SetWinUICustomControlsVisibility(hWnd, false);
        // Steam
        } else if (wcscmp(className, L"SDL_app") == 0) {
            isTarget = true;
        // Microsoft 365 Copilot
        } else if (wcscmp(className, L"OfficeApp-Frame") == 0) {
            isTarget = true;
        // New Outlook
        } else if (wcscmp(className, L"Olk Host") == 0) {
            mode = MODE_OUTLOOK;
            isTarget = true;
        // Microsoft Office apps
        } else if (wcscmp(className, L"OpusApp") == 0 || // Word
            wcscmp(className, L"XLMAIN") == 0 || // Excel
            wcscmp(className, L"PPTFrameClass") == 0 || // PowerPoint
            wcscmp(className, L"OMain") == 0 || // Access
            wcscmp(className, L"Framework::CFrame") == 0 || // OneNote
            wcscmp(className, L"rctrl_renwnd32") == 0 || // Outlook
            wcscmp(className, L"MSWinPub") == 0 // Publisher
        ) {
            isTarget = true;
        // Hangul Word Processor
        } else if (wcsncmp(className, L"HwpApp", 6) == 0) {
            isTarget = true;
        // Qt apps
        } else if (wcsstr(className, L"QWindowIcon") != 0) {
            isTarget = true;
        // New Teams
        } else if (wcsstr(className, L"TeamsWebView") != 0) {
            isTarget = true;
            SetWinUICustomControlsVisibility(hWnd, false);
        }

        if (isTarget) {
            ProcessWindow(hWnd);
        }
    }
    return TRUE;
}

BOOL CALLBACK UninitEnumWindowsProc(HWND hWnd, LPARAM lParam) {
    DWORD pid;
    GetWindowThreadProcessId(hWnd, &pid);
    // Unsubclass all windows belonging to this process
    if (pid == GetCurrentProcessId()) {
        WindhawkUtils::RemoveWindowSubclassFromAnyThread(hWnd, SubclassProc);
        SetWinUICustomControlsVisibility(hWnd, true);
        if (lParam == 1) {
            SetWindowPos(hWnd, NULL, 0, 0, 0, 0, SWP_FRAMECHANGED | SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_NOOWNERZORDER | SWP_NOACTIVATE);
        }
    }
    return TRUE;
}

BOOL CALLBACK UpdateEnumWindowsProc(HWND hWnd, LPARAM lParam) {
    DWORD pid;
    GetWindowThreadProcessId(hWnd, &pid);
    if (pid == GetCurrentProcessId()) {
        ProcessWindow(hWnd, true);
        wchar_t className[256];
        GetClassName(hWnd, className, 256);
        if (wcsncmp(className, L"Chrome_WidgetWin_", 17) == 0) {
            RedrawWindow(hWnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW | RDW_ALLCHILDREN);
        }
    }
    return TRUE;
}
#pragma endregion

using CreateWindowExW_t = decltype(&CreateWindowExW);
CreateWindowExW_t CreateWindowExW_original;
HWND WINAPI CreateWindowExW_hook(DWORD dwExStyle, LPCWSTR lpClassName, LPCWSTR lpWindowName, DWORD dwStyle, int X, int Y, int nWidth, int nHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance, LPVOID lpParam) {
    if ((dwExStyle & WS_EX_NOREDIRECTIONBITMAP) != 0) { // This makes the GDI surface invisible
        dwExStyle &= ~WS_EX_NOREDIRECTIONBITMAP;        // Just purge this cuz it's bad for Basic/Classic users anyway
    }                                                   // It must be set in CreateWindowExW. Not changeable with SetWindowLongW

    bool isTarget = false;

    HWND hWnd = CreateWindowExW_original(dwExStyle, lpClassName, lpWindowName, dwStyle, X, Y, nWidth, nHeight, hWndParent, hMenu, hInstance, lpParam);
    if (hWnd != NULL) {
        wchar_t className[256];
        GetClassName(hWnd, className, 256);
        Wh_Log(L"%s", className);
        // Chromium browsers / Electron apps / CEF top-level windows
        // Subclass late for Brave cuz somehow early subclassing makes it invisible
        if (wcsncmp(className, L"Chrome_WidgetWin_", 17) == 0) {
            if (dwStyle & WS_CAPTION) {
                mode = MODE_CHROMIUM;
                if (!isBrave) {
                    isTarget = true;
                }
            }
        // WinUI
        } else if (wcsncmp(className, L"WinUIDesktopWin32WindowClass", 28) == 0) {
            if (dwStyle & WS_CAPTION) {
                isTarget = true;
                SetWinUICustomControlsVisibility(hWnd, false);
            }
        // Steam with workarounds
        } else if (isSteam && wcscmp(className, L"Chrome_RenderWidgetHostHWND") == 0) {
            EnumWindows(InitEnumWindowsProc, 1);
        // Microsoft 365 Copilot
        } else if (wcscmp(className, L"OfficeApp-Frame") == 0) {
            isTarget = true;
        // New Outlook
        } else if (wcscmp(className, L"Olk Host") == 0) {
            mode = MODE_OUTLOOK;
            isTarget = true;
        // Hangul Word Processor
        } else if (wcsncmp(className, L"HwpApp", 6) == 0) {
            isTarget = true;
        // Qt apps
        } else if (wcsstr(className, L"QWindowIcon") != 0) {
            isTarget = true;
        // New Teams
        } else if (wcsstr(className, L"TeamsWebView") != 0) {
            isTarget = true;
            SetWinUICustomControlsVisibility(hWnd, false);
        // WinUI / Teams custom controls
        } else if (wcsstr(className, L"InputNonClientPointerSource") != 0 ||
            wcsstr(className, L"ReunionWindowingCaptionControls") != 0 ||
            wcsstr(className, L"TeamsOverlay") != 0
        ) {
            if (WindhawkUtils::SetWindowSubclassFromAnyThread(hWnd, HideSubclassProc, 0)) {
                Wh_Log(L"Hid %s (%p)", className, hWnd);
            }
        }

        if (isTarget) {
            ProcessWindow(hWnd);
        }
    }
    return hWnd;
}

// Subclassing VS windows in CreateWindowExW doesn't work for some reason, so we have to do it in ShowWindow
using ShowWindow_t = decltype(&ShowWindow);
ShowWindow_t ShowWindow_original;
BOOL WINAPI ShowWindow_hook(HWND hWnd, int nCmdShow) {
    wchar_t className[256];
    GetClassName(hWnd, className, 256);
    Wh_Log(L"ShowWindow_hook: %s", className);
    // WPF apps
    if (wcsncmp(className, L"HwndWrapper[", 12) == 0) {
        ProcessWindow(hWnd);
    // Microsoft Office apps
    } else if (wcscmp(className, L"OpusApp") == 0 || // Word
        wcscmp(className, L"XLMAIN") == 0 ||         // Excel
        wcscmp(className, L"PPTFrameClass") == 0 ||  // PowerPoint
        wcscmp(className, L"OMain") == 0 ||          // Access
        wcscmp(className, L"rctrl_renwnd32") == 0 || // Outlook
        wcscmp(className, L"MSWinPub") == 0          // Publisher
    ) {
        ProcessWindow(hWnd);
    // OneNote with workarounds
    } else if (wcscmp(className, L"Framework::CFrameApp") == 0) {
        EnumWindows(InitEnumWindowsProc, 1);
    }
    return ShowWindow_original(hWnd, nCmdShow);
}

using SetWindowThemeAttribute_t = decltype(&SetWindowThemeAttribute);
SetWindowThemeAttribute_t SetWindowThemeAttribute_original;
HRESULT WINAPI SetWindowThemeAttribute_hook(HWND hwnd, enum WINDOWTHEMEATTRIBUTETYPE eAttribute, PVOID pvAttribute, DWORD cbAttribute) {
    Wh_Log(L"SetWindowThemeAttribute_hook");
    if (eAttribute == WTA_NONCLIENT) {
        // Ignore this to make sure DWM window controls are visible
        return S_OK;
    } else {
        return SetWindowThemeAttribute_original(hwnd, eAttribute, pvAttribute, cbAttribute);
    }
}

using SetParent_t = decltype(&SetParent);
SetParent_t SetParent_original;
HWND WINAPI SetParent_hook(HWND hWndChild, HWND hWndNewParent) {
    wchar_t className[256];
    GetClassName(hWndChild, className, 256);
    Wh_Log(L"SetParent_hook: hWndChild=%p (%s), hWndNewParent=%p", hWndChild, className, hWndNewParent);
    HWND hWndOldParent = SetParent_original(hWndChild, hWndNewParent);
    if (mode == MODE_CHROMIUM && wcscmp(className, L"Intermediate D3D Window") == 0) {
        if (isBrave) {
            ProcessWindow(hWndNewParent);
        }
        if (tb4e_settings.btnFaceChrome) {
            RedrawWindow(hWndNewParent, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW | RDW_ALLCHILDREN);
        }
    }
    return hWndOldParent;
}

#pragma region Steam stuff
// From VSCode Tweaker by m417z
using CreateFileW_t = decltype(&CreateFileW);
CreateFileW_t CreateFileW_original;
HANDLE WINAPI CreateFileW_hook(
    LPCWSTR lpFileName,
    DWORD dwDesiredAccess,
    DWORD dwShareMode,
    LPSECURITY_ATTRIBUTES lpSecurityAttributes,
    DWORD dwCreationDisposition,
    DWORD dwFlagsAndAttributes,
    HANDLE hTemplateFile)
{
    PCWSTR compareFileName = lpFileName;
    if (compareFileName[0] == '\\' &&
        compareFileName[1] == '\\' &&
        compareFileName[2] == '?' &&
        compareFileName[3] == '\\') {
        compareFileName += 4;
    }

    if (!tb4e_settings.noSteamHtmlInject && wcsicmp(compareFileName, steamIndexHtml) == 0) {
        DWORD dwAttrib = GetFileAttributesW(steamIndexHtmlModded);
        if (dwAttrib != INVALID_FILE_ATTRIBUTES && !(dwAttrib & FILE_ATTRIBUTE_DIRECTORY)) {
            Wh_Log(L"lpFileName = %s => %s", compareFileName, steamIndexHtmlModded);
            lpFileName = steamIndexHtmlModded;
        }
    }

    return CreateFileW_original(
        lpFileName,
        dwDesiredAccess,
        dwShareMode,
        lpSecurityAttributes,
        dwCreationDisposition,
        dwFlagsAndAttributes,
        hTemplateFile
    );
}

bool PrepareSteamIndexHtml() {
    wchar_t tempPath[MAX_PATH];
    if (!Wh_GetModStoragePath(tempPath, MAX_PATH))
        return false;

    if (!PathCombineW(steamIndexHtmlModded, tempPath, L"tb4e-steam-index.html"))
        return false;

    std::ifstream inFile(steamIndexHtml, std::ios::binary);
    if (!inFile)
        return false;

    std::ostringstream buffer;
    buffer << inFile.rdbuf();
    std::string html = buffer.str();
    inFile.close();

    // Hook window.open to override browserType to 3, to enable Steam's built-in native frame mod for a window
    // The mode is so buggy on Windows so this mod's subclass fixes them
    const char* injectScript =
        "<script>"
            "window.open = (() => {"
                "const o = window.open;"
                "return (s, t, f) => {"
                    "try {"
                        "const u = new URL(s);"
                        "const a = typeof t === 'string' && t.startsWith('desktopoverlay_'),"
                            "b = u.searchParams.has('pid') && u.searchParams.get('pid') !== '0';"
                        "if (a || b) return o(s, t, f);" // exclude in-game overlay windows
                        "u.searchParams.set('browserType', '3');"
                        "return o(u.toString(), t, f);"
                    "} catch {"
                        "return o(s, t, f);"
                    "}"
                "};"
            "})();"
            "window._tb4eLoaded = true;" // Marker for Millennium extensions
        "</script>";

    // Look for the first <script tag
    size_t insertPos = html.find("<script");
    if (insertPos == std::string::npos)
        return false;

    html.insert(insertPos, injectScript);

    std::ofstream outFile(steamIndexHtmlModded, std::ios::binary);
    if (!outFile)
        return false;

    outFile.write(html.data(), html.size());
    outFile.close();

    Wh_Log(L"Modified steam index.html written to: %s", steamIndexHtmlModded);
    return true;
}
#pragma endregion

void LoadSettings() {
    tb4e_settings.btnFaceChrome = Wh_GetIntSetting(L"nativeFrames.buttonFaceChrome");
    auto ceSetting = WindhawkUtils::StringSetting::make(L"nativeFrames.clientEdge");
    if (*ceSetting) {
        if (wcscmp(ceSetting, L"add") == 0) {
            tb4e_settings.clientEdgeSetting = CE_ADD;
        } else if (wcscmp(ceSetting, L"remove") == 0) {
            tb4e_settings.clientEdgeSetting = CE_REMOVE;
        } else {
            tb4e_settings.clientEdgeSetting = CE_KEEP;
        }
    }
    tb4e_settings.noToolWinSteam = Wh_GetIntSetting(L"nativeFrames.steamToolFrames");
    tb4e_settings.noSteamHtmlInject = Wh_GetIntSetting(L"nativeFrames.steamNoScriptInject");
}

// The mod is being initialized, load settings, hook functions, and do other
// initialization stuff if required.
BOOL Sec_ModInit() {
    #ifdef _WIN64
        Wh_Log(L"Init - x86_64");
    #else
        Wh_Log(L"Init - x86");
    #endif

    // Check if this process is auxiliary process by checking if the arguments contain --type=
    LPWSTR args = GetCommandLineW();
    if (wcsstr(args, L"--type=") != NULL && wcsstr(args, L"--type=gpu-process") == NULL) {
        Wh_Log(L"Auxiliary process detected, skipping");
        return FALSE;
    }

    LoadSettings();

    // Check if the app is Steam
    wchar_t modulePath[MAX_PATH];
    GetModuleFileName(NULL, modulePath, MAX_PATH);
    isSteam = wcsstr(_wcsupr(modulePath), L"STEAMWEBHELPER.EXE") != NULL;
    bool steamPrepared = false;
    if (isSteam) {
        Wh_Log(L"Steam detected");

        if (wcsstr(args, L"--type=gpu-process") != NULL) { // Not used for handling Steam
            Wh_Log(L"Auxiliary process detected, skipping");
            return FALSE;
        }

        if (!tb4e_settings.noSteamHtmlInject) {
            PathRemoveFileSpecW(modulePath);

            wchar_t temp[MAX_PATH];
            PathCombineW(temp, modulePath, L"..\\..\\..\\steamui\\index.html");
            GetFullPathNameW(temp, MAX_PATH, steamIndexHtml, NULL);

            steamPrepared = PrepareSteamIndexHtml();
        }
    }

    isBrave = wcsstr(modulePath, L"BRAVE.EXE") != NULL;

    if (wcsstr(modulePath, L"DEVENV.EXE") != NULL) {
        Wh_Log(L"Visual Studio detected");
        mode = MODE_VS;
    }


    Wh_SetFunctionHook((void*)CreateWindowExW, (void*)CreateWindowExW_hook,
                       (void**)&CreateWindowExW_original);
    Wh_SetFunctionHook((void*)SetWindowThemeAttribute, (void*)SetWindowThemeAttribute_hook,
                       (void**)&SetWindowThemeAttribute_original);
    Wh_SetFunctionHook((void*)ShowWindow, (void*)ShowWindow_hook,
                       (void**)&ShowWindow_original);
    Wh_SetFunctionHook((void*)SetParent, (void*)SetParent_hook,
                       (void**)&SetParent_original);
    if (isSteam && steamPrepared && !tb4e_settings.noSteamHtmlInject) {
        Wh_SetFunctionHook((void*)CreateFileW, (void*)CreateFileW_hook,
                           (void**)&CreateFileW_original);
    }

    EnumWindows(InitEnumWindowsProc, 1);
    return TRUE;
}

// The mod is being unloaded, free all allocated resources.
void Sec_ModUninit() {
    Wh_Log(L"Uninit");
    EnumWindows(UninitEnumWindowsProc, 1);
}

void Sec_ModSettingsChanged() {
    LoadSettings();
    EnumWindows(UpdateEnumWindowsProc, 1);
}
}  // namespace native

// ==========================================================================
//  Spotify and CEF apps
// ==========================================================================
namespace cef {
/* Spotify CEF version map
90.6: 1.1.60-1.1.62
91.1: 1.1.63-1.1.67
91.3: 1.1.68-1.1.70
94: 1.1.71-1.1.72
95: 1.1.74-1.1.75
96: 1.1.76
98: 1.1.81
100: 1.1.85
101: 1.1.86-1.1.88
102: 1.1.89
104: 1.1.94
106: 1.1.97-1.2.3
109: 1.2.4-1.2.6
110: 1.2.7
111: 1.2.8-1.2.10
112: 1.2.11-1.2.12
113: 1.2.13-1.2.19
115: 1.2.20
116: 1.2.21-1.2.22
117: 1.2.23-1.2.24
118: 1.2.25
119: 1.2.26
120: 1.2.28-1.2.30
121: 1.2.31-1.2.32
122: 1.2.33-1.2.37
124: 1.2.38-1.2.39
125: 1.2.40-1.2.44
127: 1.2.45-1.2.46
128: 1.2.47-1.2.48
129: 1.2.49-1.2.50
130: 1.2.51-1.2.52
131: 1.2.53-1.2.61
134: 1.2.62-1.2.69
138: 1.2.70
139: 1.2.71-1.2.74
140: 1.2.75-1.2.77
142: 1.2.78-1.2.79
143: 1.2.80-1.2.82
144: 1.2.83-1.2.87
146: 1.2.88-1.3.1
151: 1.3.2-1.3.8
156: 1.3.9
See https://www.spotify.com/opensource/ for more
*/


using namespace std::string_view_literals;

#define NO_RENDERER_INJECTION FALSE

#define CEF_CALLBACK __stdcall
#define CEF_EXPORT __cdecl
#define cef_window_handle_t HWND
#define ANY_MINOR -1
#define PIPE_NAME L"\\\\.\\pipe\\CTEWH-IPC"
#define LAST_TESTED_CEF_VERSION 156 // Update this whenever Spotify bumps the CEF version (after verifying everything works)
#define CR_RT_1ST_VERSION 119 // First Spotify version to support Chrome runtime

struct cte_settings {
    BOOL showframe;
    BOOL showframeonothers;
    BOOL showmenu;
    BOOL showcontrols;
    BOOL transparentcontrols;
    BOOL ignoreminsize;
    BOOL transparentrendering;
    BOOL noforceddarkmode;
    BOOL forceextensions;
    BOOL blockupdates;
    BOOL allowuntested;
} cte_settings;

typedef struct cte_offset {
  int ver_major;
  int ver_minor; // -1 for any
  int offset_x86;
  int offset_x64;
} cte_offset_t;

// Apparently struct sizes are the same on x64 and arm64, so we don't need separate offsets for arm64
cte_offset_t is_frameless_offsets[] = {
    {90, 4, 0x48, 0x90},
    {90, 5, 0x48, 0x90},
    {90, 6, 0x48, 0x90},
    {91, 0, 0x48, 0x90},
    {91, 1, 0x48, 0x90},
    // (91.2 is found nowhere)
    {91, 3, 0x50, 0xa0},
    {92, ANY_MINOR, 0x50, 0xa0},
    {101, ANY_MINOR, 0x50, 0xa0},
    {102, ANY_MINOR, 0x54, 0xa8},
    {107, ANY_MINOR, 0x54, 0xa8},
    {108, ANY_MINOR, 0x5c, 0xb8},
    {114, ANY_MINOR, 0x5c, 0xb8},
    {115, ANY_MINOR, 0x60, 0xc0},
    {116, ANY_MINOR, 0x60, 0xc0},
    {117, ANY_MINOR, 0x64, 0xc8},
    {123, ANY_MINOR, 0x64, 0xc8},
    {124, ANY_MINOR, 0x68, 0xd0}
};

cte_offset_t add_child_view_offsets[] = {
    {94, ANY_MINOR, 0xf0, 0x1e0},
    {122, ANY_MINOR, 0xf0, 0x1e0},
    {124, ANY_MINOR, 0xf4, 0x1e8},
    {130, ANY_MINOR, 0xf4, 0x1e8},
    {131, ANY_MINOR, 0xf8, 0x1f0}
};

cte_offset_t get_window_handle_offsets[] = {
    {94, ANY_MINOR, 0x184, 0x308},
    {114, ANY_MINOR, 0x184, 0x308},
    {115, ANY_MINOR, 0x188, 0x310},
    {123, ANY_MINOR, 0x188, 0x310},
    {124, ANY_MINOR, 0x18c, 0x318},
    {130, ANY_MINOR, 0x18c, 0x318},
    {131, ANY_MINOR, 0x194, 0x328},
    {LAST_TESTED_CEF_VERSION, ANY_MINOR, 0x194, 0x328}
};

cte_offset_t set_background_color_offsets[] = {
    {94, ANY_MINOR, 0xbc, 0x178},
    {130, ANY_MINOR, 0xbc, 0x178},
    {131, ANY_MINOR, 0xc0, 0x180}
};

int is_frameless_offset = NULL;
int add_child_view_offset = NULL;
int get_window_handle_offset = NULL;
int set_background_color_offset = NULL;

HMODULE g_cefModule = NULL;

BOOL g_isSpotify = FALSE;
BOOL g_isSpotifyRenderer = FALSE;

HWND g_mainHwnd = NULL;
int g_minWidth = -1;
int g_minHeight = -1;
BOOL g_titleLocked = FALSE;
BOOL g_transparentMode = FALSE;

double g_playbackSpeed = 1.0;
int64_t g_currentTrackPlayer = NULL;

std::atomic<DWORD> g_lastRendererPid = NULL;
HANDLE g_hPipe = INVALID_HANDLE_VALUE;
std::atomic<HANDLE> g_hClientPipe = INVALID_HANDLE_VALUE;
std::atomic<BOOL> g_shouldClosePipe = FALSE;
std::mutex g_pipeMutex;
HANDLE g_stopEvent;
[[clang::no_destroy]] std::optional<std::thread> g_pipeThread;

std::condition_variable g_queryResponseCv;
std::mutex g_ipcMutex;
unsigned short g_lastQueryId = 1;
int g_queryResponseId = -1;
bool g_pipeDisconnected = false;

struct cte_queryResponse_t {
    BOOL success;
    int queryId;

    BOOL isMaximized;
    BOOL isTopMost;
    BOOL isLayered;
    BOOL isTransparent;
    BOOL isThemingEnabled;
    BOOL isDwmEnabled;
    BOOL hwAccelerated;
    int minWidth;
    int minHeight;
    BOOL titleLocked;
    int dpi;
    BOOL speedModSupported;
    double playbackSpeed;
    BOOL immediateSpeedChange;

    BOOL showframe;
    BOOL showframeonothers;
    BOOL showmenu;
    BOOL showcontrols;
    BOOL transparentcontrols;
    BOOL ignoreminsize;
    BOOL transparentrendering;
    BOOL noforceddarkmode;
    BOOL forceextensions;
    BOOL blockupdates;
    BOOL allowuntested;
} g_queryResponse;

#pragma region CEF structs (as minimal and cross-version compatible as possible)
// Copyright (c) 2024 Marshall A. Greenblatt. All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
//    * Redistributions of source code must retain the above copyright
// notice, this list of conditions and the following disclaimer.
//    * Redistributions in binary form must reproduce the above
// copyright notice, this list of conditions and the following disclaimer
// in the documentation and/or other materials provided with the
// distribution.
//    * Neither the name of Google Inc. nor the name Chromium Embedded
// Framework nor the names of its contributors may be used to endorse
// or promote products derived from this software without specific prior
// written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

typedef struct _cef_string_utf16_t {
  char16_t* str;
  size_t length;
  void (*dtor)(char16_t* str);
} cef_string_utf16_t;

typedef cef_string_utf16_t cef_string_t;
typedef cef_string_utf16_t* cef_string_userfree_utf16_t;
typedef cef_string_userfree_utf16_t cef_string_userfree_t;

typedef struct _cef_string_list_t* cef_string_list_t;

typedef uint32_t cef_color_t;

typedef struct _cef_base_ref_counted_t {
  size_t size;
  void(CEF_CALLBACK* add_ref)(struct _cef_base_ref_counted_t* self);
  int(CEF_CALLBACK* release)(struct _cef_base_ref_counted_t* self);
  int(CEF_CALLBACK* has_one_ref)(struct _cef_base_ref_counted_t* self);
  int(CEF_CALLBACK* has_at_least_one_ref)(struct _cef_base_ref_counted_t* self);
} cef_base_ref_counted_t;

typedef struct _cef_size_t {
  int width;
  int height;
} cef_size_t;

typedef struct _cef_view_delegate_t {
  cef_base_ref_counted_t base;
  cef_size_t(CEF_CALLBACK* get_preferred_size)(struct _cef_view_delegate_t* self);
  cef_size_t(CEF_CALLBACK* get_minimum_size)(struct _cef_view_delegate_t* self, struct _cef_view_t* view);
} cef_view_delegate_t;

typedef struct _cef_panel_delegate_t {
  cef_view_delegate_t base;
} cef_panel_delegate_t;

typedef struct _cef_window_delegate_t {
  cef_panel_delegate_t base;
} cef_window_delegate_t;

typedef struct _cef_basetime_t {
  int64_t val;
} cef_basetime_t;

typedef enum {
  V8_PROPERTY_ATTRIBUTE_NONE = 0,
  V8_PROPERTY_ATTRIBUTE_READONLY = 1 << 0,
  V8_PROPERTY_ATTRIBUTE_DONTENUM = 1 << 1,
  V8_PROPERTY_ATTRIBUTE_DONTDELETE = 1 << 2
} cef_v8_propertyattribute_t;

typedef struct _cef_v8handler_t {
  cef_base_ref_counted_t base;
  int(CEF_CALLBACK* execute)(struct _cef_v8handler_t* self,
                             const cef_string_t* name,
                             struct _cef_v8value_t* object,
                             size_t argumentsCount,
                             struct _cef_v8value_t* const* arguments,
                             struct _cef_v8value_t** retval,
                             cef_string_t* exception);
} cef_v8handler_t;

// CEF 108+
typedef struct _cef_v8value_t {
    cef_base_ref_counted_t base;

    int(CEF_CALLBACK* is_valid)(struct _cef_v8value_t* self);
    int(CEF_CALLBACK* is_undefined)(struct _cef_v8value_t* self);
    int(CEF_CALLBACK* is_null)(struct _cef_v8value_t* self);
    int(CEF_CALLBACK* is_bool)(struct _cef_v8value_t* self);
    int(CEF_CALLBACK* is_int)(struct _cef_v8value_t* self);
    int(CEF_CALLBACK* is_uint)(struct _cef_v8value_t* self);
    int(CEF_CALLBACK* is_double)(struct _cef_v8value_t* self);
    int(CEF_CALLBACK* is_date)(struct _cef_v8value_t* self);
    int(CEF_CALLBACK* is_string)(struct _cef_v8value_t* self);
    int(CEF_CALLBACK* is_object)(struct _cef_v8value_t* self);
    int(CEF_CALLBACK* is_array)(struct _cef_v8value_t* self);
    int(CEF_CALLBACK* is_array_buffer)(struct _cef_v8value_t* self);
    int(CEF_CALLBACK* is_function)(struct _cef_v8value_t* self);
    int(CEF_CALLBACK* is_promise)(struct _cef_v8value_t* self);
    int(CEF_CALLBACK* is_same)(struct _cef_v8value_t* self, struct _cef_v8value_t* that);
    int(CEF_CALLBACK* get_bool_value)(struct _cef_v8value_t* self);
    int32_t(CEF_CALLBACK* get_int_value)(struct _cef_v8value_t* self);
    uint32_t(CEF_CALLBACK* get_uint_value)(struct _cef_v8value_t* self);
    double(CEF_CALLBACK* get_double_value)(struct _cef_v8value_t* self);
    cef_basetime_t(CEF_CALLBACK* get_date_value)(struct _cef_v8value_t* self);
    cef_string_userfree_t(CEF_CALLBACK* get_string_value)(struct _cef_v8value_t* self);
    int(CEF_CALLBACK* is_user_created)(struct _cef_v8value_t* self);
    int(CEF_CALLBACK* has_exception)(struct _cef_v8value_t* self);
    struct _cef_v8exception_t*(CEF_CALLBACK* get_exception)(struct _cef_v8value_t* self);
    int(CEF_CALLBACK* clear_exception)(struct _cef_v8value_t* self);
    int(CEF_CALLBACK* will_rethrow_exceptions)(struct _cef_v8value_t* self);
    int(CEF_CALLBACK* set_rethrow_exceptions)(struct _cef_v8value_t* self, int rethrow);
    int(CEF_CALLBACK* has_value_bykey)(struct _cef_v8value_t* self, const cef_string_t* key);
    int(CEF_CALLBACK* has_value_byindex)(struct _cef_v8value_t* self, int index);
    int(CEF_CALLBACK* delete_value_bykey)(struct _cef_v8value_t* self, const cef_string_t* key);
    int(CEF_CALLBACK* delete_value_byindex)(struct _cef_v8value_t* self, int index);
    struct _cef_v8value_t*(CEF_CALLBACK* get_value_bykey)(struct _cef_v8value_t* self, const cef_string_t* key);
    struct _cef_v8value_t*(CEF_CALLBACK* get_value_byindex)(struct _cef_v8value_t* self, int index);
    int(CEF_CALLBACK* set_value_bykey)(struct _cef_v8value_t* self, const cef_string_t* key, struct _cef_v8value_t* value, cef_v8_propertyattribute_t attribute);
    int(CEF_CALLBACK* set_value_byindex)(struct _cef_v8value_t* self, int index, struct _cef_v8value_t* value);
    // below here is updated quite recently (CEF 126), so it's avoided
} cef_v8value_t;

typedef struct _cef_request_t {
    cef_base_ref_counted_t base;
    int (CEF_CALLBACK* is_read_only)(struct _cef_request_t* self);
    cef_string_userfree_t(CEF_CALLBACK* get_url)(struct _cef_request_t* self);
} cef_request_t;
#pragma endregion

#pragma region CEF V8 functions + helpers
typedef cef_v8value_t* CEF_EXPORT (*cef_v8value_create_function_t)(const cef_string_t* name, cef_v8handler_t* handler);
cef_v8value_create_function_t CEF_EXPORT cef_v8value_create_function_original;

typedef cef_v8value_t* CEF_EXPORT (*cef_v8value_create_bool_t)(int value);
cef_v8value_create_bool_t cef_v8value_create_bool;

typedef cef_v8value_t* CEF_EXPORT (*cef_v8value_create_int_t)(int value);
cef_v8value_create_int_t cef_v8value_create_int;

typedef cef_v8value_t* CEF_EXPORT (*cef_v8value_create_double_t)(double value);
cef_v8value_create_double_t cef_v8value_create_double;

typedef cef_v8value_t* CEF_EXPORT (*cef_v8value_create_string_t)(const cef_string_t* value);
cef_v8value_create_string_t cef_v8value_create_string;

typedef cef_v8value_t* CEF_EXPORT (*cef_v8value_create_object_t)(void* accessor, void* interceptor);
cef_v8value_create_object_t cef_v8value_create_object;

typedef cef_v8value_t* CEF_EXPORT (*cef_v8value_create_array_t)(int length);
cef_v8value_create_array_t cef_v8value_create_array;

typedef int (*cef_version_info_t)(int entry);

cef_string_t* GenerateCefString(std::u16string str) {
    cef_string_t* cefStr = (cef_string_t*)calloc(1, sizeof(cef_string_t));
    cefStr->str = (char16_t*)calloc(str.size() + 1, sizeof(char16_t));
    cefStr->length = str.size();
    memcpy(cefStr->str, str.c_str(), str.size() * sizeof(char16_t));
    return cefStr;
}

cef_string_t* GenerateCefString(std::wstring str) {
    return GenerateCefString(std::u16string(str.begin(), str.end()));
}

cef_string_t* FormatCefString(const wchar_t* format, ...) {
    va_list args;
    va_start(args, format);
    int len = _vscwprintf(format, args);
    std::wstring str(len + 1, L'\0');
    vswprintf_s(&str[0], len + 1, format, args);
    va_end(args);
    return GenerateCefString(std::u16string(str.begin(), str.end()));
}

int AddFunctionToObj(cef_v8value_t* obj, std::u16string name, cef_v8handler_t* handler) {
    cef_string_t* cefName = GenerateCefString(name);
    cef_v8value_t* func = cef_v8value_create_function_original(cefName, handler);
    int result = obj->set_value_bykey(obj, cefName, func, V8_PROPERTY_ATTRIBUTE_NONE);
    free(cefName->str);
    free(cefName);
    return result;
}

int AddValueToObj(cef_v8value_t* obj, std::u16string name, cef_v8value_t* value) {
    cef_string_t* cefName = GenerateCefString(name);
    int result = obj->set_value_bykey(obj, cefName, value, V8_PROPERTY_ATTRIBUTE_NONE);
    free(cefName->str);
    free(cefName);
    return result;
}

int AddValueToObj(cef_v8value_t* obj, std::u16string name, std::u16string value) {
    cef_string_t* cefValue = GenerateCefString(value);
    int result = AddValueToObj(obj, name, cef_v8value_create_string(cefValue));
    free(cefValue->str);
    free(cefValue);
    return result;
}
#pragma endregion

void CreateNamedPipeServer();

// Whether DwmExtendFrameIntoClientArea should be called
// False if DWM is disabled, visual styles are disabled, or some kind of basic themer is used
BOOL IsDwmEnabled() {
    if (!IsAppThemed() && !IsThemeActive()) {
        return FALSE;
    }
    BOOL dwmEnabled = FALSE;
    DwmIsCompositionEnabled(&dwmEnabled);
    BOOL dwmFrameEnabled = FALSE;
    if (dwmEnabled && g_mainHwnd != NULL) {
        HRESULT hr = DwmGetWindowAttribute(g_mainHwnd, DWMWA_NCRENDERING_ENABLED, &dwmFrameEnabled, sizeof(dwmFrameEnabled));
        if (!SUCCEEDED(hr)) {
            return dwmEnabled;
        }
    } else {
        return dwmEnabled;
    }
    return dwmEnabled && dwmFrameEnabled;
}

// From various Windhawk mods by m417z
UINT GetDpiForWindowWithFallback(HWND hWnd) {
    using GetDpiForWindow_t = UINT(WINAPI*)(HWND hwnd);
    static GetDpiForWindow_t pGetDpiForWindow = []() {
        HMODULE hUser32 = GetModuleHandle(L"user32.dll");
        if (hUser32) {
            return (GetDpiForWindow_t)GetProcAddress(hUser32,
                                                     "GetDpiForWindow");
        }

        return (GetDpiForWindow_t) nullptr;
    }();

    UINT dpi = 96;
    if (pGetDpiForWindow) {
        dpi = pGetDpiForWindow(hWnd);
    } else {
        HDC hdc = GetDC(nullptr);
        if (hdc) {
            dpi = GetDeviceCaps(hdc, LOGPIXELSX);
            ReleaseDC(nullptr, hdc);
        }
    }

    return dpi;
}

#pragma region Subclassing
LRESULT CALLBACK SubclassProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, DWORD_PTR dwRefData) {
    // dwRefData is 1 if the window is created by cef_window_create_top_level
    // Assumed 1 if this mod is loaded after the window is created
    // dwRefData is 2 if the window is created by cef_window_create_top_level and is_frameless is hooked
    switch (uMsg) {
        case WM_SIZE:
            // Fix Basic frames being wrongly drawn when entering and exiting fullscreen
            if (hWnd == g_mainHwnd &&!cte_settings.showframe) {
                return 0;
            } else {
                return DefWindowProc(hWnd, uMsg, wParam, lParam);
            }
            break;
        case WM_NCACTIVATE:
            if (hWnd == g_mainHwnd && cte_settings.transparentrendering && !cte_settings.showframe && IsDwmEnabled()) {
                // Fix MicaForEveryone not working well with frameless windows
                return DefWindowProc(hWnd, uMsg, wParam, lParam);
            }
            break;
        case WM_NCPAINT:
            if (hWnd == g_mainHwnd && FindWindowExW(g_mainHwnd, NULL, L"Intermediate D3D Window", NULL) != NULL && cte_settings.transparentrendering && !cte_settings.showframe && !IsDwmEnabled()) {
                // Paint black background in non-client area
                HDC hdc = GetWindowDC(hWnd);
                if (hdc) {
                    RECT rect;
                    GetWindowRect(hWnd, &rect);
                    OffsetRect(&rect, -rect.left, -rect.top); // Convert to client-relative coords
                    FillRect(hdc, &rect, (HBRUSH)GetStockObject(BLACK_BRUSH));
                    ReleaseDC(hWnd, hdc);
                }
                return 0;
            }
        case WM_NCHITTEST:
        case WM_NCLBUTTONDOWN:
        case WM_NCCALCSIZE:
            // Unhook Spotify's custom window control event handling
            // Also unhook WM_NCPAINT to fix non-DWM frames randomly going black
            // WM_NCCALCSIZE is only for windows with Chrome's custom frame (DevTools, Miniplayer, full browser UI, etc.)
            if (dwRefData) {
                if (cte_settings.showframe == TRUE || dwRefData == 2) {
                    return DefWindowProc(hWnd, uMsg, wParam, lParam);
                }
            } else if (cte_settings.showframeonothers == TRUE) {
                return DefWindowProc(hWnd, uMsg, wParam, lParam);
            }
            break;
        case WM_PAINT:
            if (hWnd == g_mainHwnd && FindWindowExW(g_mainHwnd, NULL, L"Intermediate D3D Window", NULL) != NULL && cte_settings.transparentrendering) {
                if (!cte_settings.showframe) {
                    // Do not draw anything
                    ValidateRect(hWnd, NULL);
                } else {
                    // Draw black background on the GDI surface (behind the D3D surface) to get Aero Glass/Mica/Acrylic/whatever working properly
                    PAINTSTRUCT ps;
                    HDC hdc = BeginPaint(hWnd, &ps);
                    RECT rect;
                    GetClientRect(hWnd, &rect);
                    FillRect(hdc, &rect, (HBRUSH)GetStockObject(BLACK_BRUSH));
                    EndPaint(hWnd, &ps);
                }
                return 0;
            }
            break;
    }
    return DefSubclassProc(hWnd, uMsg, wParam, lParam);
}

BOOL CALLBACK UpdateEnumWindowsProc(HWND hWnd, LPARAM lParam) {
    DWORD pid;
    GetWindowThreadProcessId(hWnd, &pid);
    if (pid == GetCurrentProcessId()) {
        // Update NonClient size
        wchar_t className[256];
        GetClassName(hWnd, className, 256);
        if (wcsncmp(className, L"Chrome_WidgetWin_", 17) == 0) {
            if (lParam == 1) {
                // Really move the window a bit to make Spotify update window control colors
                RECT rect;
                GetWindowRect(hWnd, &rect);
                SetWindowPos(hWnd, NULL, rect.left, rect.top + 1, 0, 0, SWP_NOZORDER | SWP_NOOWNERZORDER | SWP_NOACTIVATE | SWP_NOSIZE);
                SetWindowPos(hWnd, NULL, rect.left, rect.top, 0, 0, SWP_FRAMECHANGED | SWP_NOZORDER | SWP_NOOWNERZORDER | SWP_NOACTIVATE | SWP_NOSIZE);
            } else {
                SetWindowPos(hWnd, NULL, 0, 0, 0, 0, SWP_FRAMECHANGED | SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_NOOWNERZORDER | SWP_NOACTIVATE);
            }
        }
    }
    return TRUE;
}

BOOL CALLBACK InitEnumWindowsProc(HWND hWnd, LPARAM lParam) {
    DWORD pid;
    GetWindowThreadProcessId(hWnd, &pid);
    // Subclass all relevant windows belonging to this process
    if (pid == GetCurrentProcessId()) {
        wchar_t className[256];
        GetClassName(hWnd, className, 256);
        if (wcsncmp(className, L"Chrome_WidgetWin_", 17) == 0) {
            if (WindhawkUtils::SetWindowSubclassFromAnyThread(hWnd, SubclassProc, 1)) {
                Wh_Log(L"Subclassed %p", hWnd);
                if (lParam == 1) {
                    UpdateEnumWindowsProc(hWnd, 0);
                }
            }
        }
    }
    return TRUE;
}

BOOL CALLBACK UninitEnumWindowsProc(HWND hWnd, LPARAM lParam) {
    DWORD pid;
    GetWindowThreadProcessId(hWnd, &pid);
    // Unsubclass all windows belonging to this process
    if (pid == GetCurrentProcessId()) {
        WindhawkUtils::RemoveWindowSubclassFromAnyThread(hWnd, SubclassProc);
        if (lParam == 1) {
            UpdateEnumWindowsProc(hWnd, 0);
        }
    }
    return TRUE;
}
#pragma endregion

#pragma region Memory patches
// Pass an empty targetPatch to use it as a regex search
// identifier: String to identify the match, used for caching
// pbExecutable: Base address to search, pass EXE or DLL address
// targetRegex: Target regex string to search
// targetPatch: Bytes to replace the matched memory, pass an empty vector to use it as a simple regex search
// expectedSection: Section number to search, pass -1 to search all
// maxMatch: Max numbers of matches, pass -1 to search the whole memory region for all matches (not recommended for performance reasons)
// verifyRegex: Regex string to use for verifying the cache match
int64_t PatchMemory(std::wstring identifier, char* pbExecutable, const std::string& targetRegex, const std::vector<uint8_t>& targetPatch, int expectedSection = -1, int maxMatch = -1, const std::string& verifyRegex = "") {
    IMAGE_DOS_HEADER* pDosHeader = (IMAGE_DOS_HEADER*)pbExecutable;
    IMAGE_NT_HEADERS* pNtHeader = (IMAGE_NT_HEADERS*)((char*)pDosHeader + pDosHeader->e_lfanew);
    IMAGE_SECTION_HEADER* pSectionHeader = (IMAGE_SECTION_HEADER*)((char*)&pNtHeader->OptionalHeader + pNtHeader->FileHeader.SizeOfOptionalHeader);

    std::regex regex(targetRegex, std::regex::optimize);
    std::match_results<std::string_view::const_iterator> match;
    bool foundAnyMatch = false;

    for (int i = 0; i < pNtHeader->FileHeader.NumberOfSections; ++i) {
        if (expectedSection != -1 && i != expectedSection) {
            continue;
        }

        int matchCount = 0;

        // One or more cache was invalidated; prevent further caching with invalid indexes
        bool noCachingForThisSession = false;

        size_t moduleSize = pSectionHeader[i].VirtualAddress + pSectionHeader[i].SizeOfRawData;

        std::wstring keyPrefix = identifier + L"_offset_";
        if (targetPatch.size() == 0) {
            std::wstring key = keyPrefix + L"0";
            int64_t cachedOffset = Wh_GetIntValue(key.c_str(), -1);
            if (cachedOffset != -1) {
                if (cachedOffset < 0 || static_cast<size_t>(cachedOffset + targetRegex.size()) > moduleSize) {
                    Wh_Log(L"Cache offset out of bounds; invalidating...");
                    Wh_DeleteValue(key.c_str());
                } else {
                    if (!verifyRegex.empty()) {
                        regex = std::regex(verifyRegex, std::regex::optimize);
                    }
                    std::string_view candidate(pbExecutable + cachedOffset, targetRegex.size());
                    if (std::regex_search(candidate.begin(), candidate.end(), regex)) {
                        char* addr = pbExecutable + cachedOffset;
                        Wh_Log(L"Returning cached offset for function %s", identifier.c_str());
                        return (int64_t)addr;
                    } else {
                        Wh_Log(L"Match not found at the cached offset; invalidating the cache...");
                        Wh_DeleteValue(key.c_str());
                    }
                }
            }
        } else {
            std::wstring key = keyPrefix + L"cnt";
            int64_t cachedCount = Wh_GetIntValue(key.c_str(), -1);
            if (cachedCount > 0) {
                bool allOk = true;
                for (int i = 0; i < cachedCount; i++) {
                    std::wstring key = keyPrefix + std::to_wstring(i);
                    int64_t cachedOffset = Wh_GetIntValue(key.c_str(), -1);
                    if (cachedOffset != -1) {
                        if (cachedOffset < 0 || static_cast<size_t>(cachedOffset + targetRegex.size()) > moduleSize) {
                            Wh_Log(L"Cache offset out of bounds; invalidating...");
                            Wh_DeleteValue(key.c_str());
                            allOk = false;
                            continue;
                        }
                        std::string_view candidate(pbExecutable + cachedOffset, targetPatch.size());
                        if (!verifyRegex.empty()) {
                            regex = std::regex(verifyRegex, std::regex::optimize);
                        }
                        if (std::regex_search(candidate.begin(), candidate.end(), regex)) {
                            char* addr = pbExecutable + cachedOffset;
                            DWORD oldProtect;
                            if (VirtualProtect(addr, targetPatch.size(), PAGE_EXECUTE_READWRITE, &oldProtect)) {
                                memcpy(addr, targetPatch.data(), targetPatch.size());
                                VirtualProtect(addr, targetPatch.size(), oldProtect, &oldProtect);
                                Wh_Log(L"Patched cached offset for memory %s", identifier.c_str());
                                foundAnyMatch = TRUE;
                                matchCount++;
                            }
                        } else {
                            Wh_Log(L"Match #%d not found at the cached offset; invalidating the cache...", i);
                            Wh_DeleteValue(key.c_str());
                            allOk = false;
                        }
                    } else {
                        Wh_Log(L"Missing cached key: %s", key.c_str());
                        allOk = false;
                    }
                }
                if (allOk) {
                    Wh_Log(L"Successfully patched all %d cached offsets for memory %s", cachedCount, identifier.c_str());
                    return 1;
                } else {
                    // Invalidate everything for this - as match number is messed up when the offsets are partially missing
                    Wh_Log(L"Failed to patch all %d cached offsets for memory %s; invalidating the cache...", cachedCount, identifier.c_str());
                    Wh_DeleteValue(key.c_str());
                    noCachingForThisSession = true;
                }
            } else if (cachedCount == 0) {
                Wh_Log(L"Invalid cache count for memory %s!", identifier.c_str());
                Wh_DeleteValue(key.c_str());
                noCachingForThisSession = true;
            }
        }

        char* from = pbExecutable + pSectionHeader[i].VirtualAddress;
        char* to = from + pSectionHeader[i].SizeOfRawData;

        std::string_view search(from, to - from);

        while (std::regex_search(search.begin(), search.end(), match, regex)) {
            auto pos = from + match.position(0);

            Wh_Log(L"Match #%d found in section %d at position: %p", matchCount, i, pos);
            std::wstring key = keyPrefix + std::to_wstring(matchCount);
            Wh_SetIntValue(key.c_str(), static_cast<int>(pos - pbExecutable));

            if (targetPatch.size() == 0) {
                // Just return the address of the first match
                return (int64_t)pos;
            }

            // #include <iomanip>
            // #include <sstream>
            // // Log the bytes before patching
            // std::string beforePatch(pos, targetPatch.size());
            // std::ostringstream hexStreamBefore;
            // for (size_t i = 0; i < targetPatch.size(); ++i) {
            //     hexStreamBefore << std::hex << std::setw(2) << std::setfill('0') << (int)(unsigned char)beforePatch[i] << " ";
            // }
            // std::string hexStreamStrBefore = hexStreamBefore.str();
            // std::wstring hexStreamWStrBefore(hexStreamStrBefore.begin(), hexStreamStrBefore.end());
            // Wh_Log(L"Hex bytes before patch: %s", hexStreamWStrBefore.c_str());

            DWORD dwOldProtect;
            if (VirtualProtect(pos, targetPatch.size(), PAGE_EXECUTE_READWRITE, &dwOldProtect)) {
                memcpy(pos, targetPatch.data(), targetPatch.size());
                VirtualProtect(pos, targetPatch.size(), dwOldProtect, &dwOldProtect);
                Wh_Log(L"Patch applied successfully for memory %s", identifier.c_str());

                // // Log the bytes after patching
                // std::string afterPatch(pos, targetPatch.size());
                // std::ostringstream hexStreamAfter;
                // for (size_t i = 0; i < targetPatch.size(); ++i) {
                //     hexStreamAfter << std::hex << std::setw(2) << std::setfill('0') << (int)(unsigned char)afterPatch[i] << " ";
                // }
                // std::string hexStreamStrAfter = hexStreamAfter.str();
                // std::wstring hexStreamWStrAfter(hexStreamStrAfter.begin(), hexStreamStrAfter.end());
                // Wh_Log(L"Hex bytes after patch: %s", hexStreamWStrAfter.c_str());

                foundAnyMatch = true;
            } else {
                Wh_Log(L"Failed to change memory protection.");
            }

            if (maxMatch != -1 && ++matchCount >= maxMatch) {
                break;
            }

            // Move the search start position to after the current match
            from = pos + targetPatch.size();
            search = std::string_view(from, to - from);
        }

        if (!noCachingForThisSession) {
            std::wstring key = keyPrefix + L"cnt";
            Wh_SetIntValue(key.c_str(), matchCount);
        }
    }

    if (!foundAnyMatch) {
        Wh_Log(L"No match found for the regex pattern.");
    }

    return foundAnyMatch ? 1 : 0;
}

BOOL EnableTransparentRendering(char* pbExecutable) {
    std::vector<uint8_t> targetPatch = {0xba, 0x00, 0x00, 0x00, 0x00, 0xff};

    // Use ButtonFace color if classic theme is used and frames are enabled
    if (!IsAppThemed() && !IsThemeActive() && cte_settings.showframe == TRUE) {
        DWORD btnFace = GetSysColor(COLOR_BTNFACE); // ButtonFace color
        targetPatch[1] = ((btnFace >> 16) & 0xFF);
        targetPatch[2] = ((btnFace >> 8) & 0xFF);
        targetPatch[3] = (btnFace & 0xFF);
        targetPatch[4] = 0xFF; // Opaque
    }

    #if defined(_M_X64)
        std::string targetRegex = R"(\xba\x12\x12\x12\xff\xff)"; // mov edx, 0xff121212 (default background color)
    #elif defined(_M_ARM64)
        std::string targetRegex = R"(\xd6\x12\x12\x12\xff\x00)"; // apparently this long hex is saved in a dword before being used on arm64
        targetPatch[0] = 0xd6;
        targetPatch[5] = 0x00;
    #else
        std::string targetRegex = R"(\x68\x12\x12\x12\xff\x8b)"; // push 0xff121212
        targetPatch[0] = 0x68;
        targetPatch[5] = 0x8b;
    #endif

    return PatchMemory(L"BgColor", pbExecutable, targetRegex, targetPatch, 0, 4);
}

BOOL DisableForcedDarkMode(char* pbExecutable, int major) {
    std::string targetRegex = R"(force-dark-mode)";
    std::string targetPatch = "some-invalidarg";
    std::vector<uint8_t> targetPatchBytes(targetPatch.begin(), targetPatch.end());
    int section = (major >= 116 && major <= 118) ? 2 : 1; // idk why
    return PatchMemory(L"ForceDarkMode", pbExecutable, targetRegex, targetPatchBytes, section, 1);
}

BOOL ForceEnableExtensions(char* pbExecutable) {
    std::string targetRegex = R"(disable-extensions)";
    std::string targetPatch = "enable-extensions!";
    std::vector<uint8_t> targetPatchBytes(targetPatch.begin(), targetPatch.end());
    return PatchMemory(L"DisableExtensions", pbExecutable, targetRegex, targetPatchBytes, 1, 1);
}
#pragma endregion

#pragma region Spotify.exe hooks (non-exported functions)
#ifdef _M_X64
// From https://windhawk.net/mods/chrome-ui-tweaks
typedef struct {
    std::string_view search; // instructions to search for
    std::string_view prologue; // prologue of the function to be hooked (instructions at entry point)
    const size_t instr_offset; // estimated location of the searched instructions relative to the entry point
} function_search;

// Wrapper for string_view::find, that checks the needle is unique within the haystack.
const char* unique_search(std::string_view haystack, std::string_view needle, LPCWSTR symbol_name) {
    size_t index1 = haystack.find(needle);
    if (index1 == std::string_view::npos) {
        Wh_Log(L"Error: Couldn't find instructions for symbol %s", symbol_name);
        return NULL;
    }
    // Can we find the same sequence again in the rest of the haystack?
    size_t index2 = haystack.find(needle, index1 + 1);
    if (index2 != std::string_view::npos) {
        Wh_Log(L"Error: Found multiple matches for %s: at %p and at %p", symbol_name, haystack.begin()+index1, haystack.begin()+index2);
        // log_hexdump((unsigned char*)haystack.begin() + index1 - 0x50, 6);
        // Wh_Log(L"----------------");
        // log_hexdump((unsigned char*)haystack.begin() + index2 - 0x50, 6);
        return NULL;
    }
    return haystack.begin() + index1;
}

// get address and size of code section via PE header info  (expect around 200 MB)
// TODO is this actually correct? (does it include superfluous sections of the DLL?)
// https://learn.microsoft.com/en-us/windows/win32/debug/pe-format
// https://learn.microsoft.com/en-us/archive/msdn-magazine/2002/february/inside-windows-win32-portable-executable-file-format-in-detail
std::string_view getCodeSection(HMODULE chromeModule) {
    if (chromeModule == NULL) return ""sv;
    IMAGE_DOS_HEADER* dos_header = (IMAGE_DOS_HEADER*) chromeModule;
    IMAGE_NT_HEADERS* pe_header = (IMAGE_NT_HEADERS*)(((char*)dos_header) + dos_header->e_lfanew);
    if (pe_header->FileHeader.Machine != 0x8664 || pe_header->OptionalHeader.Magic != 0x20b) {
        Wh_Log(L"Mod only implemented for 64-bit windows/chrome - machine was 0x%04x and magic was 0x%04x",
        pe_header->FileHeader.Machine, pe_header->OptionalHeader.Magic);
        return ""sv;
    }
    return std::string_view{
        ((char*)dos_header) + pe_header->OptionalHeader.BaseOfCode,
        pe_header->OptionalHeader.SizeOfCode
    };
}

// Find a function address by scanning for specific instruction patterns.
// We search the entire code section once per function,
// to ensure we aren't hooking the wrong location.
// Better safe than sorry, and it shouldn't cause noticeable delay on startup.
const char* search_function_instructions(std::wstring identifier, std::string_view code_section, function_search fsearch) {
    if (code_section.size()==0) return 0;

    std::wstring key = identifier + L"_offset";
    int cached_offset = Wh_GetIntValue(key.c_str(), -1);
    auto prologue = fsearch.prologue;
    if (cached_offset >= 0 && static_cast<size_t>(cached_offset + prologue.size()) < code_section.size()) {
        std::string_view match_view = code_section.substr(cached_offset, prologue.size());
        if (match_view == prologue) {
            Wh_Log(L"Returning cached offset for function %s", identifier.c_str());
            return code_section.data() + cached_offset;
        } else {
            Wh_Log(L"Match not found at the cached offset; invalidating the cache...");
            Wh_DeleteValue(key.c_str());
        }
    }

    Wh_Log(L"Searching for function %s", identifier.c_str());
    const char* addr = unique_search(code_section, fsearch.search, identifier.c_str());
    if (addr == NULL) {
        Wh_Log(L"Could not find function %s; is the mod up to date?", identifier.c_str());
        return NULL;
    }
    Wh_Log(L"Instructions were found at address: %p", addr);
    int offset = fsearch.instr_offset;
    const char* entry = addr - offset;
    // verify the prologue is what we expect; otherwise search for it
    // and verify it is preceded by 0xcc INT3 or 0xc3 RET (or ?? JMP)
    if (prologue != std::string_view{entry, prologue.size()}) {
        Wh_Log(L"Prologue not found where expected, searching...");
        // maybe function length changed due to different compilation
        auto search_space = std::string_view{entry - 0x40, addr};
        size_t new_offset = search_space.rfind(prologue);
        if (new_offset != std::string_view::npos) {
            entry = (char*)search_space.begin() + new_offset;
        } else {
            entry = NULL;
        }
    }
    if (entry) {
        Wh_Log(L"Found entrypoint for function %s at addr %p", identifier.c_str(), entry);
        if (entry[-1]!=(char)0xcc && entry[-1]!=(char)0xc3) {
            Wh_Log(L"Warn: prologue not preceded by INT3 or RET");
        }
        Wh_SetIntValue(key.c_str(), static_cast<int>(entry - code_section.data()));
        return entry;
    } else {
        Wh_Log(L"Err: Couldn't locate function entry point for symbol %s", identifier.c_str());
        // log_hexdump(addr - 0x40, 0x5);
        return NULL;
    }
}

typedef uint64_t* __fastcall (*CreateTrackPlayer_t)(
    int64_t trackPlayer,
    uint64_t* a2,
    uint64_t* a3,
    double speed,
    unsigned int a5,
    unsigned int a6,
    int a7,
    int64_t a8,
    unsigned int a9,
    int64_t a10,
    int64_t a11,
    int64_t a12
);
CreateTrackPlayer_t CreateTrackPlayer_original;
uint64_t* __fastcall CreateTrackPlayer_hook(
    int64_t trackPlayer,
    uint64_t* a2,
    uint64_t* a3,
    double speed,
    unsigned int a5,
    unsigned int a6,
    int a7,
    int64_t a8,
    unsigned int a9,
    int64_t a10,
    int64_t a11,
    int64_t a12
) {
    Wh_Log(L"CreateTrackPlayer_hook");
    g_currentTrackPlayer = trackPlayer;
    return CreateTrackPlayer_original(trackPlayer, a2, a3, g_playbackSpeed, a5, a6, a7, a8, a9, a10, a11, a12);
}

// Find this function with xref of string "    Creating track player for track (playback_id %s)"
const std::string_view CreateTrackPlayer_instructions =
    "\x01"sv         // just a single byte before the instructions below, to distinguish from another match
    "\x49\x8B\x0F"sv // mov rcx, [r15]
    "\x48\x8B\x01"sv // mov rax, [rcx]
    "\xFF\x50\x38"sv // call qword ptr [rax+38h]
    "\x48\x8D"sv;    // lea rdx, (followed by address of "yes" in .rdata)
const std::string_view CreateTrackPlayer_instructions_2 = // Spotify 1.2.63+
    "\x01"sv             // just a single byte before the instructions below, to distinguish from another match
    "\x49\x8B\x0C\x24"sv // mov rcx, [r12]
    "\x48\x8B\x01"sv     // mov rax, [rcx]
    "\xFF\x50\x38"sv     // call qword ptr [rax+38h]
    "\x48\x8D"sv;        // lea rdx, (followed by address of "yes" in .rdata)
const std::string_view CreateTrackPlayer_prologue = "\x48\x8B\xC4USVWATAUAVAWH"sv;

typedef char __fastcall (*SetPlaybackSpeed_t)(int64_t trackPlayer, double speed);
SetPlaybackSpeed_t SetPlaybackSpeed;

// Find this function with xref of string "Setting playback speed to %d percent (playback_id %s) from %d percent"
// This function's various numbers are different in every version, so we need to perform a regex search
const std::string SetPlaybackSpeed_instructions =
    R"(\x48\x8B\xC4)"                // mov rax, rsp (beginning of function)
    R"(\x48\x89\x58\x18)"            // mov [rax+18h], rbx
    R"(\x48\x89\x70\x20)"            // mov [rax+20h], rsi
    R"(\x55\x57\x41\x56)"            // push rbp, push rdi, push r14
    R"(\x48\x8D\xA8.?\xFD\xFF\xFF)"; // lea rbp, [rax-??h]

// Only works on Spotify x64 1.2.36 and newer
// No plans to support x86 or older versions
BOOL HookCreateTrackPlayer(char* pbExecutable, BOOL shouldFindSetPlaybackSpeed) {
    std::string_view code_section = getCodeSection((HMODULE)pbExecutable);
    if (code_section.size() == 0) return FALSE;
    const char* addr = search_function_instructions(
        L"CreateTrackPlayer",
        code_section,
        {
            .search = CreateTrackPlayer_instructions,
            .prologue = CreateTrackPlayer_prologue,
            .instr_offset = 0xBA0
        }
    );
    if (addr == NULL) {
        addr = search_function_instructions(
            L"CreateTrackPlayer",
            code_section,
            {
                .search = CreateTrackPlayer_instructions_2,
                .prologue = CreateTrackPlayer_prologue,
                .instr_offset = 0xBA0
            }
        );
    }
    if (addr == NULL) return FALSE;
    Wh_Log(L"Hooking CreateTrackPlayer at %p", addr);
    WindhawkUtils::SetFunctionHook((CreateTrackPlayer_t)addr, CreateTrackPlayer_hook, &CreateTrackPlayer_original);

    // This only works on Spotify x64 1.2.45 and newer
    // Don't find SetPlaybackSpeed on a known unsupported version, as finding non-existent instructions will delay startup
    if (shouldFindSetPlaybackSpeed) {
        SetPlaybackSpeed = (SetPlaybackSpeed_t)PatchMemory(L"SetPlaybackSpeed", pbExecutable, SetPlaybackSpeed_instructions, {}, 0, 1);
        Wh_Log(L"SetPlaybackSpeed at %p", SetPlaybackSpeed);
    }
    return TRUE;
}
#else
#define CreateTrackPlayer_original NULL
#define SetPlaybackSpeed NULL
#endif
#pragma endregion

#pragma region CEF hooks
// This is only called once, during window creation
typedef int CEF_CALLBACK (*is_frameless_t)(struct _cef_window_delegate_t* self, struct _cef_window_t* window);
int CEF_CALLBACK is_frameless_hook(struct _cef_window_delegate_t* self, struct _cef_window_t* window) {
    Wh_Log(L"is_frameless_hook");
    return 0;
}

typedef cef_size_t CEF_CALLBACK (*get_minimum_size_t)(struct _cef_view_delegate_t* self, struct _cef_view_t* view);
get_minimum_size_t get_minimum_size_original;
get_minimum_size_t* get_minimum_size_addr;
cef_size_t CEF_CALLBACK get_minimum_size_hook(struct _cef_view_delegate_t* self, struct _cef_view_t* view) {
    //Wh_Log(L"get_minimum_size_hook");
    cef_size_t size = {};
    if (g_minWidth == -1 || g_minHeight == -1) {
        if (!cte_settings.ignoreminsize) {
            size = {800, 600};
        }
    } else {
        float dpi = GetDpiForWindowWithFallback(g_mainHwnd);
        size.width = g_minWidth / (dpi / 96);
        size.height = g_minHeight / (dpi / 96);
    }
    return size;
}

typedef cef_window_handle_t CEF_CALLBACK (*get_window_handle_t)(struct _cef_window_t* self);

typedef _cef_window_t* CEF_EXPORT (*cef_window_create_top_level_t)(cef_window_delegate_t* delegate);
cef_window_create_top_level_t CEF_EXPORT cef_window_create_top_level_original;
_cef_window_t* CEF_EXPORT cef_window_create_top_level_hook(cef_window_delegate_t* delegate) {
    Wh_Log(L"cef_window_create_top_level_hook");

    BOOL is_frameless_hooked = FALSE;
    if (is_frameless_offset != NULL && cte_settings.showframe == TRUE) {
        *((is_frameless_t*)((char*)delegate + is_frameless_offset)) = is_frameless_hook;
        is_frameless_hooked = TRUE;
    }
    _cef_window_t* window = cef_window_create_top_level_original(delegate);
    if (get_window_handle_offset != NULL) {
        get_window_handle_t get_window_handle = *((get_window_handle_t*)((char*)window + get_window_handle_offset));
        HWND hWnd = get_window_handle(window);
        WindhawkUtils::RemoveWindowSubclassFromAnyThread(hWnd, SubclassProc);
        if (WindhawkUtils::SetWindowSubclassFromAnyThread(hWnd, SubclassProc, is_frameless_hooked ? 2 : 1)) {
            Wh_Log(L"Subclassed %p", hWnd);
            if (FindWindowExW(g_mainHwnd, NULL, L"Intermediate D3D Window", NULL) != NULL && cte_settings.transparentrendering) {
                InvalidateRect(hWnd, NULL, TRUE);
                RedrawWindow(hWnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW | RDW_ALLCHILDREN);
            }
        }
        if (g_mainHwnd == NULL) {
            g_mainHwnd = hWnd;
            if (g_isSpotify) {
                get_minimum_size_original = delegate->base.base.get_minimum_size;
                get_minimum_size_addr = &delegate->base.base.get_minimum_size;
                *get_minimum_size_addr = get_minimum_size_hook;
                if (!NO_RENDERER_INJECTION) {
                    g_stopEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
                    if (g_stopEvent) {
                        g_pipeThread = std::thread([=]() {
                            CreateNamedPipeServer();
                        });
                    } else {
                        Wh_Log(L"CreateEvent failed, GLE=%d", GetLastError());
                    }
                }
            }
        }
    } else {
        // Just subclass everything again if get_window_handle is not available
        // Calling functions from invalid offsets will crash the app for sure
        EnumWindows(UninitEnumWindowsProc, 0);
        EnumWindows(InitEnumWindowsProc, 1);
        Wh_Log(L"Avoided calling get_window_handle on an untested version");
    }
    return window;
}

typedef void CEF_CALLBACK (*set_background_color_t)(struct _cef_view_t* self, cef_color_t color);
set_background_color_t CEF_CALLBACK set_background_color_original;
void CEF_CALLBACK set_background_color_hook(struct _cef_view_t* self, cef_color_t color) {
    //Wh_Log(L"set_background_color_hook: %#x", color);
    // 0x87000000: normal, 0x3fffffff: hover, 0x33ffffff: active, 0xffc42b1c: close button hover, 0xff941320: close button active
    if (color == 0x87000000 && cte_settings.transparentcontrols == TRUE) {
        color = 0x00000000;
    }
    set_background_color_original(self, color);
    return;
}

struct cte_control_container {
    set_background_color_t CEF_CALLBACK set_background_color_original;
    set_background_color_t* CEF_CALLBACK set_background_color_addr;
} cte_controls[3];

int cnt = -1;

// Only called during the main window creation
typedef void CEF_CALLBACK (*add_child_view_t)(struct _cef_panel_t* self, struct _cef_view_t* view);
add_child_view_t CEF_CALLBACK add_child_view_original;
void CEF_CALLBACK add_child_view_hook(struct _cef_panel_t* self, struct _cef_view_t* view) {
    cnt++;
    Wh_Log(L"add_child_view_hook: %d", cnt);
    // 0: Minimize, 1: Maximize, 2: Close, 3: Menu (removing this also prevents alt key from working)
    if (cnt < 3) {
      if (cte_settings.showcontrols == FALSE) {
        return;
      }
    } else if (cte_settings.showmenu == FALSE) {
      return;
    }
    if (cnt < 3 && set_background_color_offset != NULL) {
        set_background_color_original = *((set_background_color_t*)((char*)view + set_background_color_offset));
        *((set_background_color_t*)((char*)view + set_background_color_offset)) = set_background_color_hook;
        cte_controls[cnt].set_background_color_original = set_background_color_original;
        cte_controls[cnt].set_background_color_addr = (set_background_color_t*)((char*)view + set_background_color_offset);
    }
    add_child_view_original(self, view);
    return;
}

typedef _cef_panel_t* CEF_EXPORT (*cef_panel_create_t)(cef_panel_delegate_t* delegate);
cef_panel_create_t CEF_EXPORT cef_panel_create_original;
_cef_panel_t* CEF_EXPORT cef_panel_create_hook(cef_panel_delegate_t* delegate) {
    Wh_Log(L"cef_panel_create_hook");
    if ((cnt != 2 || cte_settings.showmenu == FALSE) && // left panel
        (cnt != -1 || cte_settings.showcontrols == FALSE) // right panel
    ) {
        // Nullify get_preferred_size to make the leftover space from hiding the window controls clickable
        // This has side effect of making the menu button ignore the height set by cosmos endpoint (used by noControls Spicetify extension)
        // So only nullify get_preferred_size for the left panel if menu button is hidden
        delegate->base.get_preferred_size = NULL;
    }
    _cef_panel_t* panel = cef_panel_create_original(delegate);
    if (add_child_view_offset != NULL) {
        add_child_view_original = *((add_child_view_t*)((char*)panel + add_child_view_offset));
        *((add_child_view_t*)((char*)panel + add_child_view_offset)) = add_child_view_hook;
    }
    return panel;
}

typedef void* CEF_EXPORT (*cef_urlrequest_create_t)(struct _cef_request_t* request, void* client, void* request_context);
cef_urlrequest_create_t CEF_EXPORT cef_urlrequest_create_original;
void* CEF_EXPORT cef_urlrequest_create_hook(struct _cef_request_t* request, void* client, void* request_context) {
    cef_string_t* url = request->get_url(request);
    std::wstring urlStr(url->str, url->str + url->length);
    Wh_Log(L"cef_urlrequest_create_hook: %s", urlStr.c_str());
    if (cte_settings.blockupdates && urlStr.find(L"https://spclient.wg.spotify.com/desktop-update/v2/update") != std::wstring::npos) {
        Wh_Log(L"Blocked update check");
        return NULL;
    }
    return cef_urlrequest_create_original(request, client, request_context);
}
#pragma endregion

#pragma region Win32 API hooks
using CreateWindowExW_t = decltype(&CreateWindowExW);
CreateWindowExW_t CreateWindowExW_original;
HWND WINAPI CreateWindowExW_hook(DWORD dwExStyle, LPCWSTR lpClassName, LPCWSTR lpWindowName, DWORD dwStyle, int X, int Y, int nWidth, int nHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance, LPVOID lpParam) {
    Wh_Log(L"CreateWindowExW_hook");
    // Flag added in CEF 139 / Spotify 1.2.71
    if ((dwExStyle & WS_EX_NOREDIRECTIONBITMAP) != 0) { // This makes the GDI surface invisible
        dwExStyle &= ~WS_EX_NOREDIRECTIONBITMAP;        // Just purge this cuz it's bad for Basic/Classic users anyway
    }                                                   // It must be set in CreateWindowExW. Not changeable with SetWindowLongW

    HWND hWnd = CreateWindowExW_original(dwExStyle, lpClassName, lpWindowName, dwStyle, X, Y, nWidth, nHeight, hWndParent, hMenu, hInstance, lpParam);
    if (hWnd != NULL) {
        wchar_t className[256];
        GetClassName(hWnd, className, 256);
        if (wcsncmp(className, L"Chrome_WidgetWin_", 17) == 0) { // Chrome_WidgetWin_1: with Chrome runtime, Chrome_WidgetWin_0: without Chrome runtime (Alloy) + some hidden windows
            if (dwStyle & WS_CAPTION) {
                // Subclass other Chromium/CEF windows, including those not created by cef_window_create_top_level (e.g. DevTools, Miniplayer (DocumentPictureInPicture), full Chromium browser UI that somehow can be opened, etc.)
                // But exclude windows without WS_CAPTION to prevent subclassing dropdowns, tooltips, etc.
                if (WindhawkUtils::SetWindowSubclassFromAnyThread(hWnd, SubclassProc, 0)) {
                    Wh_Log(L"Subclassed %p", hWnd);
                }
            }
        }
    }
    return hWnd;
}

using SetWindowThemeAttribute_t = decltype(&SetWindowThemeAttribute);
SetWindowThemeAttribute_t SetWindowThemeAttribute_original;
HRESULT WINAPI SetWindowThemeAttribute_hook(HWND hwnd, enum WINDOWTHEMEATTRIBUTETYPE eAttribute, PVOID pvAttribute, DWORD cbAttribute) {
    Wh_Log(L"SetWindowThemeAttribute_hook");
    if (eAttribute == WTA_NONCLIENT && is_frameless_offset != NULL && cte_settings.showframe == TRUE) {
        // Ignore this to make sure DWM window controls are visible
        return S_OK;
    } else {
        return SetWindowThemeAttribute_original(hwnd, eAttribute, pvAttribute, cbAttribute);
    }
}

using DwmExtendFrameIntoClientArea_t = decltype(&DwmExtendFrameIntoClientArea);
DwmExtendFrameIntoClientArea_t DwmExtendFrameIntoClientArea_original;
HRESULT WINAPI DwmExtendFrameIntoClientArea_hook(HWND hWnd, const MARGINS *pMarInset) {
    // Prevent libcef.dll (Chromium code) from unextending itself whenever a frameless window's position changes
    // https://source.chromium.org/chromium/chromium/src/+/main:ui/views/win/hwnd_message_handler.cc;drc=339fea7fafdc1ba5b16e7b2fa6f9d996b65348a3;l=616

    // Designed to be compatible with other mods that inject into applications and call DwmExtendFrameIntoClientArea
    // unless they hook DwmExtendFrameIntoClientArea themselves
    // Unfortunately, old version of the 'Translucent Windows' Windhawk mod does that, so it's likely to be incompatible with this fix
    // It is recommended to use a tool that does not involve hooking, such as MicaForEveryone
    // or just use the this mod's JavaScript API which entirely bypasses this check

    if (cte_settings.showframe) {
        // Disable this fix when native frames are enabled, as Chromium doesn't do that for framed windows
        // Translucent Windows mod should work fine in this case
        return DwmExtendFrameIntoClientArea_original(hWnd, pMarInset);
    }

    if (g_mainHwnd != NULL) {
        if (hWnd != g_mainHwnd) {
            // Ditto for non-main windows to allow Chrome runtime full browser UI's Mica mode to work
            // (No one's gonna use that seriously tho)
            return DwmExtendFrameIntoClientArea_original(hWnd, pMarInset);
        }
    }
    // Assume everything's the main window before the g_mainHwnd assignment, as it's early startup
    // Otherwise Chromium's DEFICA calls will pass through during the main window creation,
    // interfering with early frame extension attempts from some mods

    bool deny = false;

    void* returnAddress = __builtin_return_address(0);

    HMODULE callerModule;
    DWORD dwFlags = GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS | GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT;
    if (GetModuleHandleEx(dwFlags, (PCWSTR)returnAddress, &callerModule) &&
        callerModule == g_cefModule && 
        pMarInset->cxLeftWidth == 0 &&
        pMarInset->cxRightWidth == 0 &&
        (pMarInset->cyTopHeight == 0 || pMarInset->cyTopHeight == 1) &&
        pMarInset->cyBottomHeight == 0
    ) {
        deny = true;
    }

    wchar_t modulePath[MAX_PATH] = {};
    if (callerModule && GetModuleFileNameW(callerModule, modulePath, MAX_PATH)) {
        Wh_Log(L"DEFICA: {%d, %d, %d, %d}, %s%s",
            pMarInset->cxLeftWidth,
            pMarInset->cxRightWidth,
            pMarInset->cyTopHeight,
            pMarInset->cyBottomHeight,
            modulePath,
            (deny ? L" (denied)" : L"")
        );
    }

    if (deny) {
        return E_ACCESSDENIED;
    }

    return DwmExtendFrameIntoClientArea_original(hWnd, pMarInset);
}

using SetWindowTextW_t = decltype(&SetWindowTextW);
SetWindowTextW_t SetWindowTextW_original;
BOOL WINAPI SetWindowTextW_hook(HWND hWnd, LPCWSTR lpString) {
    Wh_Log(L"SetWindowTextW_hook");
    if (g_titleLocked && hWnd == g_mainHwnd) {
        return TRUE;
    }
    return SetWindowTextW_original(hWnd, lpString);
}

// renderer and gpu process spawn with this when --no-sandbox is used
using CreateProcessW_t = decltype(&CreateProcessW);
CreateProcessW_t CreateProcessW_original;
BOOL WINAPI CreateProcessW_hook(
    LPCWSTR lpApplicationName,
    LPWSTR lpCommandLine,
    LPSECURITY_ATTRIBUTES lpProcessAttributes,
    LPSECURITY_ATTRIBUTES lpThreadAttributes,
    BOOL bInheritHandles,
    DWORD dwCreationFlags,
    LPVOID lpEnvironment,
    LPCWSTR lpCurrentDirectory,
    LPSTARTUPINFOW lpStartupInfo,
    LPPROCESS_INFORMATION lpProcessInformation
) {
    Wh_Log(L"CreateProcessW_hook");

    BOOL result = CreateProcessW_original(
        lpApplicationName,
        lpCommandLine,
        lpProcessAttributes,
        lpThreadAttributes,
        bInheritHandles,
        dwCreationFlags,
        lpEnvironment,
        lpCurrentDirectory,
        lpStartupInfo,
        lpProcessInformation
    );

    if (result && lpCommandLine) {
        if (wcsstr(lpCommandLine, L"--type=renderer") != NULL &&
            wcsstr(lpCommandLine, L"--extension-process") == NULL &&
            wcsstr(lpCommandLine, L"--top-chrome-webui") == NULL
        ) {
            g_lastRendererPid.store(lpProcessInformation->dwProcessId);
            Wh_Log(L"Renderer process detected");
        }
    }
    Wh_Log(L"lpCommandLine: %s", lpCommandLine);

    return result;
}

// renderer and gpu process spawn with this when sandbox is enabled
using CreateProcessAsUserW_t = decltype(&CreateProcessAsUserW);
CreateProcessAsUserW_t CreateProcessAsUserW_original;
BOOL WINAPI CreateProcessAsUserW_hook(
    HANDLE hToken,
    LPCWSTR lpApplicationName,
    LPWSTR lpCommandLine,
    LPSECURITY_ATTRIBUTES lpProcessAttributes,
    LPSECURITY_ATTRIBUTES lpThreadAttributes,
    BOOL bInheritHandles,
    DWORD dwCreationFlags,
    LPVOID lpEnvironment,
    LPCWSTR lpCurrentDirectory,
    LPSTARTUPINFOW lpStartupInfo,
    LPPROCESS_INFORMATION lpProcessInformation
) {
    Wh_Log(L"CreateProcessAsUserW_hook");

    // Inject %PROGRAMDATA% to get Windhawk 1.5.1 and below to work with sandboxed renderers
    const wchar_t* lpEnvironmentCopy = (wchar_t*)lpEnvironment;
    wchar_t* newEnv = NULL;
    if (lpCommandLine && wcsstr(lpCommandLine, L"--type=renderer")) {
        if (lpEnvironment) {
            const wchar_t* env = (const wchar_t*)lpEnvironment;
            BOOL found = FALSE;
            while (*env) {
                if (wcsstr(env, L"PROGRAMDATA") != NULL) {
                    found = TRUE;
                    break;
                }
                env += wcslen(env) + 1;
            }

            if (!found) {
                size_t envLen = 0;
                while (((wchar_t*)lpEnvironment)[envLen] != L'\0' || ((wchar_t*)lpEnvironment)[envLen + 1] != L'\0') {
                    envLen++;
                }
                envLen += 1; // Only include one null terminator at the end

                std::wstring append1 = L"PROGRAMDATA=";
                std::wstring append2(MAX_PATH, L'\0');
                GetEnvironmentVariableW(L"PROGRAMDATA", append2.data(), MAX_PATH);
                std::wstring append3 = L"\0\0";
                std::wstring append = append1 + append2 + append3;
                size_t appendLen = append.size();

                newEnv = new wchar_t[envLen + appendLen];
                memcpy(newEnv, lpEnvironment, envLen * sizeof(wchar_t));
                memcpy(newEnv + envLen, append.c_str(), appendLen * sizeof(wchar_t));

                lpEnvironmentCopy = newEnv;
            }
        }
    }

    BOOL result = CreateProcessAsUserW_original(
        hToken,
        lpApplicationName,
        lpCommandLine,
        lpProcessAttributes,
        lpThreadAttributes,
        bInheritHandles,
        dwCreationFlags,
        (LPVOID)lpEnvironmentCopy,
        lpCurrentDirectory,
        lpStartupInfo,
        lpProcessInformation
    );

    if (newEnv) {
        delete[] newEnv;
    }

    if (result && lpCommandLine) {
        if (wcsstr(lpCommandLine, L"--type=renderer") != NULL &&
            wcsstr(lpCommandLine, L"--extension-process") == NULL &&
            wcsstr(lpCommandLine, L"--top-chrome-webui") == NULL
        ) {
            g_lastRendererPid.store(lpProcessInformation->dwProcessId);
            Wh_Log(L"Renderer process detected");
        }
    }
    Wh_Log(L"lpCommandLine: %s", lpCommandLine);

    return result;
}
#pragma endregion

#pragma region Renderer JS API injection + IPC
void HandleWindhawkComm(LPCWSTR command) {
    if (g_mainHwnd == NULL) {
        return;
    }

    std::lock_guard<std::mutex> lock(g_ipcMutex); // Protect shared resources

    int len = wcslen(command);
    Wh_Log(L"HandleWindhawkComm: %s, len: %d, size: %d", command, len, sizeof(command));

    // Validate command length
    if (len >= 269) { // "/WH:SetTitle:" + max title length (255) + null terminator
        Wh_Log(L"Command too long");
        return;
    }

    // /WH:ExtendFrame:<left>:<right>:<top>:<bottom>
    // Set DWM margins to extend frame into client area
    if (wcsncmp(command, L"/WH:ExtendFrame:", 16) == 0) {
        if (g_transparentMode) {
            int ncRenderingPolicy = DWMNCRP_ENABLED;
            DwmSetWindowAttribute(g_mainHwnd, DWMWA_NCRENDERING_POLICY, &ncRenderingPolicy, sizeof(ncRenderingPolicy));
            g_transparentMode = FALSE;
        }
        if (!IsDwmEnabled()) {
            return;
        }
        int left, right, top, bottom;
        if (swscanf(command + 16, L"%d:%d:%d:%d", &left, &right, &top, &bottom) == 4) {
            MARGINS margins = {left, right, top, bottom};
            DwmExtendFrameIntoClientArea_original(g_mainHwnd, &margins);
        }
    // /WH:Minimize, /WH:MaximizeRestore, /WH:Close
    // Send respective window messages to the main window
    } else if (wcscmp(command, L"/WH:Minimize") == 0) {
        ShowWindow(g_mainHwnd, SW_MINIMIZE);
    } else if (wcscmp(command, L"/WH:MaximizeRestore") == 0) {
        if (IsIconic(g_mainHwnd)) {
            ShowWindow(g_mainHwnd, SW_RESTORE);
        } else {
            ShowWindow(g_mainHwnd, IsZoomed(g_mainHwnd) ? SW_RESTORE : SW_MAXIMIZE);
        }
    } else if (wcscmp(command, L"/WH:Close") == 0) {
        PostMessage(g_mainHwnd, WM_CLOSE, 0, 0);
    // /WH:Focus
    // Set focus to the main window
    } else if (wcscmp(command, L"/WH:Focus") == 0) {
        SetForegroundWindow(g_mainHwnd);
    // /WH:SetLayered:<layered (1/0)>:<alpha>:<optional-transparentColor>
    // Make the window layered with optional transparent color key
    } else if (wcsncmp(command, L"/WH:SetLayered:", 15) == 0) {
        int layered, alpha, color;
        if (swscanf(command + 15, L"%d:%d:%x", &layered, &alpha, &color) == 3) {
            if (layered) {
                SetWindowLong(g_mainHwnd, GWL_EXSTYLE, GetWindowLong(g_mainHwnd, GWL_EXSTYLE) | WS_EX_LAYERED);
                SetLayeredWindowAttributes(g_mainHwnd, color, alpha, LWA_COLORKEY | LWA_ALPHA);
            } else {
                SetWindowLong(g_mainHwnd, GWL_EXSTYLE, GetWindowLong(g_mainHwnd, GWL_EXSTYLE) & ~WS_EX_LAYERED);
            }
        } else if (swscanf(command + 15, L"%d:%d", &layered, &alpha) == 2) {
            if (layered) {
                SetWindowLong(g_mainHwnd, GWL_EXSTYLE, GetWindowLong(g_mainHwnd, GWL_EXSTYLE) | WS_EX_LAYERED);
                SetLayeredWindowAttributes(g_mainHwnd, 0, alpha, LWA_ALPHA);
            } else {
                SetWindowLong(g_mainHwnd, GWL_EXSTYLE, GetWindowLong(g_mainHwnd, GWL_EXSTYLE) & ~WS_EX_LAYERED);
            }
        } else if (swscanf(command + 15, L"%d", &layered) == 1) {
            if (layered) {
                SetWindowLong(g_mainHwnd, GWL_EXSTYLE, GetWindowLong(g_mainHwnd, GWL_EXSTYLE) | WS_EX_LAYERED);
            } else {
                SetWindowLong(g_mainHwnd, GWL_EXSTYLE, GetWindowLong(g_mainHwnd, GWL_EXSTYLE) & ~WS_EX_LAYERED);
            }
        }
    // /WH:SetTransparent:<transparent (1/0)>
    // Enable or disable true transparency trick for frameless windows
    } else if (wcsncmp(command, L"/WH:SetTransparent:", 19) == 0) {
        // CEF paints non-alpha-blended black background by default
        // I tried things like suppressing WM_PAINT to stop that, but I couldn't get rid of black painting on window maximize
        // (I think this is a DWM quirk? Transparency by not drawing anything isn't a documented behavior after all)
        // So instead we use DwmExtendFrameIntoClientArea to enable DWM's transparency handling of alphaless pixels (which just turns black to transparent)
        // And disable DWM frames to get real transparency instead of DWM frames/effects
        if (cte_settings.showframe) {
            // Don't do this if native frames are enabled, as it breaks the frame
            return;
        }
        int transparent;
        if (swscanf(command + 19, L"%d", &transparent) == 1) {
            MARGINS margins = { transparent ? -1 : 0 };
            DwmExtendFrameIntoClientArea_original(g_mainHwnd, &margins);
            BOOL value = FALSE;
            DwmSetWindowAttribute(g_mainHwnd, DWMWA_USE_HOSTBACKDROPBRUSH, &value, sizeof(value));
            int backdrop_type = DWMSBT_NONE;
            DwmSetWindowAttribute(g_mainHwnd, DWMWA_SYSTEMBACKDROP_TYPE, &backdrop_type, sizeof(backdrop_type));
            int ncRenderingPolicy = transparent ? DWMNCRP_DISABLED : DWMNCRP_ENABLED;
            DwmSetWindowAttribute(g_mainHwnd, DWMWA_NCRENDERING_POLICY, &ncRenderingPolicy, sizeof(ncRenderingPolicy));
            g_transparentMode = transparent;
        }
    // /WH:SetBackdrop:<none|mica|acrylic|tabbed>
    // Set the window backdrop type (Windows 11 only)
    } else if (wcsncmp(command, L"/WH:SetBackdrop:", 16) == 0) {
        if (wcscmp(command + 16, L"none") == 0) {
            BOOL value = FALSE;
            DwmSetWindowAttribute(g_mainHwnd, DWMWA_USE_HOSTBACKDROPBRUSH, &value, sizeof(value));
            int backdrop_type = DWMSBT_NONE;
            DwmSetWindowAttribute(g_mainHwnd, DWMWA_SYSTEMBACKDROP_TYPE, &backdrop_type, sizeof(backdrop_type));
        } else if (wcscmp(command + 16, L"mica") == 0) {
            BOOL value = TRUE;
            DwmSetWindowAttribute(g_mainHwnd, DWMWA_USE_HOSTBACKDROPBRUSH, &value, sizeof(value));
            int backdrop_type = DWMSBT_MAINWINDOW;
            DwmSetWindowAttribute(g_mainHwnd, DWMWA_SYSTEMBACKDROP_TYPE, &backdrop_type, sizeof(backdrop_type));
        } else if (wcscmp(command + 16, L"acrylic") == 0) {
            BOOL value = TRUE;
            DwmSetWindowAttribute(g_mainHwnd, DWMWA_USE_HOSTBACKDROPBRUSH, &value, sizeof(value));
            int backdrop_type = DWMSBT_TRANSIENTWINDOW;
            DwmSetWindowAttribute(g_mainHwnd, DWMWA_SYSTEMBACKDROP_TYPE, &backdrop_type, sizeof(backdrop_type));
        } else if (wcscmp(command + 16, L"tabbed") == 0) {
            BOOL value = TRUE;
            DwmSetWindowAttribute(g_mainHwnd, DWMWA_USE_HOSTBACKDROPBRUSH, &value, sizeof(value));
            int backdrop_type = DWMSBT_TABBEDWINDOW;
            DwmSetWindowAttribute(g_mainHwnd, DWMWA_SYSTEMBACKDROP_TYPE, &backdrop_type, sizeof(backdrop_type));
        }
    // /WH:ResizeTo:<width>:<height>
    } else if (wcsncmp(command, L"/WH:ResizeTo:", 13) == 0) {
        int width, height;
        if (swscanf(command + 13, L"%d:%d", &width, &height) == 2) {
            SetWindowPos(g_mainHwnd, NULL, 0, 0, width, height, SWP_NOMOVE | SWP_NOZORDER | SWP_NOOWNERZORDER | SWP_NOACTIVATE);
        }
    // /WH:SetMinSize:<width>:<height>
    } else if (wcsncmp(command, L"/WH:SetMinSize:", 15) == 0) {
        int width, height;
        if (swscanf(command + 15, L"%d:%d", &width, &height) == 2) {
            g_minWidth = width;
            g_minHeight = height;
        }
    // /WH:SetTopMost:<topmost (1/0), toggle if absent>
    } else if (wcsncmp(command, L"/WH:SetTopMost:", 15) == 0) {
        int topmost;
        if (swscanf(command + 15, L"%d", &topmost) == 1) {
            SetWindowPos(g_mainHwnd, topmost ? HWND_TOPMOST : HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
        } else {
            SetWindowPos(g_mainHwnd, GetWindowLong(g_mainHwnd, GWL_EXSTYLE) & WS_EX_TOPMOST ? HWND_NOTOPMOST : HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
        }
    // /WH:SetTitle:<title>
    // Set the window title (ignores title lock)
    } else if (wcsncmp(command, L"/WH:SetTitle:", 13) == 0) {
        SetWindowTextW_original(g_mainHwnd, command + 13);
    // /WH:LockTitle:<lock (1/0), toggle if absent>
    // Prevent Spotify from changing the window title
    } else if (wcsncmp(command, L"/WH:LockTitle:", 14) == 0) {
        int lock;
        if (swscanf(command + 14, L"%d", &lock) == 1) {
            g_titleLocked = lock;
        } else {
            g_titleLocked = !g_titleLocked;
        }
    // /WH:OpenSpotifyMenu
    // Open the Spotify menu (Alt, won't work if the menu button is hidden in the mod options)
    } else if (wcscmp(command, L"/WH:OpenSpotifyMenu") == 0) {
        PostMessage(g_mainHwnd, WM_SYSCOMMAND, SC_KEYMENU, 0);
    // /WH:SetPlaybackSpeed:<speed> (64-bit only)
    #ifdef _M_X64
    } else if (wcsncmp(command, L"/WH:SetPlaybackSpeed:", 21) == 0) {
        double speed;
        if (swscanf(command + 21, L"%lf", &speed) == 1) {
            g_playbackSpeed = speed;
            if (SetPlaybackSpeed != NULL && g_currentTrackPlayer != NULL) {
                SetPlaybackSpeed(g_currentTrackPlayer, speed);
            }
        }
    #endif
    // /WH:Query
    } else if (wcsncmp(command, L"/WH:Query:", 10) == 0) {
        if (g_hPipe == INVALID_HANDLE_VALUE) {
            return;
        }

        int queryId;
        if (swscanf(command + 10, L"%d", &queryId) != 1) {
            Wh_Log(L"Query ID missing!");
            return;
        }

        OVERLAPPED overlapped = {};
        overlapped.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
        if (!overlapped.hEvent) {
            Wh_Log(L"CreateEvent failed, GLE=%d", GetLastError());
            return;
        }
        HANDLE waits[] = {overlapped.hEvent, g_stopEvent};

        wchar_t queryResponse[256];
        swprintf(queryResponse, 256, L"/WH:QueryResponse:%d:%d:%d:%d:%d:%d:%d:%d:%d:%d:%d:%d:%d:%d:%d:%d:%d:%d:%d:%d:%d:%d:%d:%d:%lf:%d",
            /* id */                   queryId,
            /* showframe */            cte_settings.showframe,
            /* showframeonothers */    cte_settings.showframeonothers,
            /* showmenu */             cte_settings.showmenu,
            /* showcontrols */         cte_settings.showcontrols,
            /* transparentcontrols */  cte_settings.transparentcontrols,
            /* transparentrendering */ cte_settings.transparentrendering,
            /* ignoreminsize */        cte_settings.ignoreminsize,
            /* noforceddarkmode */     cte_settings.noforceddarkmode,
            /* forceextensions */      cte_settings.forceextensions,
            /* blockupdates */         cte_settings.blockupdates,
            /* allowuntested */        cte_settings.allowuntested,
            /* isMaximized */          IsZoomed(g_mainHwnd),
            /* isTopMost */            GetWindowLong(g_mainHwnd, GWL_EXSTYLE) & WS_EX_TOPMOST,
            /* isLayered */            GetWindowLong(g_mainHwnd, GWL_EXSTYLE) & WS_EX_LAYERED,
            /* isTransparent */        g_transparentMode,
            /* isThemingEnabled */     IsAppThemed() && IsThemeActive(),
            /* isDwmEnabled */         IsDwmEnabled(),
            /* hwAccelerated */        FindWindowExW(g_mainHwnd, NULL, L"Intermediate D3D Window", NULL) != NULL,
            /* minWidth */             g_minWidth,
            /* minHeight */            g_minHeight,
            /* titleLocked */          g_titleLocked,
            /* dpi */                  GetDpiForWindowWithFallback(g_mainHwnd),
            /* speedModSupported */    CreateTrackPlayer_original != NULL,
            /* playbackSpeed */        g_playbackSpeed,
            /* immediateSpeedChange */ SetPlaybackSpeed != NULL
        );
        DWORD bytesWritten;
        BOOL result = WriteFile(g_hPipe, queryResponse, wcslen(queryResponse) * sizeof(wchar_t), &bytesWritten, &overlapped);
        if (!result) {
            int error = GetLastError();
            if (error != ERROR_IO_PENDING) {
                Wh_Log(L"WriteFile failed, GLE=%d", error);
                CloseHandle(overlapped.hEvent);
                return;
            }

            // Wait for the write operation to complete
            DWORD waitResult = WaitForMultipleObjects(2, waits, FALSE, INFINITE);
            if (waitResult != WAIT_OBJECT_0) {
                if (waitResult == WAIT_OBJECT_0 + 1) {
                    Wh_Log(L"Stop event received");
                } else {
                    Wh_Log(L"Wait failed, GLE=%d", GetLastError());
                }
                CancelIoEx(g_hPipe, &overlapped);
                GetOverlappedResult(g_hPipe, &overlapped, &bytesWritten, TRUE); // let the cancel complete
                CloseHandle(overlapped.hEvent);
                return;
            }

            if (!GetOverlappedResult(g_hPipe, &overlapped, &bytesWritten, FALSE)) {
                error = GetLastError();
                Wh_Log(L"GetOverlappedResult failed, GLE=%d", error);
                CloseHandle(overlapped.hEvent);
                return;
            }
        }
        Wh_Log(L"QueryResponse send OK");
        CloseHandle(overlapped.hEvent);
    }
}

// Copy-pasted from https://source.chromium.org/chromium/chromium/src/+/main:third_party/crashpad/crashpad/util/win/registration_protocol_win.cc;drc=f39c57f31413abcb41d3068cfb2c7a1718003cc5;l=253
// Same logic as in crashpad to allow processes with untrusted integrity level to connect to the named pipe
void* GetSecurityDescriptorWithUser(const wchar_t* sddl_string, size_t* size) {
    if (size)
        *size = 0;

    PSECURITY_DESCRIPTOR base_sec_desc;
    if (!ConvertStringSecurityDescriptorToSecurityDescriptor(
            sddl_string, SDDL_REVISION_1, &base_sec_desc, nullptr)) {
        Wh_Log(L"ConvertStringSecurityDescriptorToSecurityDescriptor failed");
        return nullptr;
    }

    EXPLICIT_ACCESS access;
    wchar_t username[] = L"CURRENT_USER";
    BuildExplicitAccessWithName(
        &access, username, GENERIC_ALL, GRANT_ACCESS, NO_INHERITANCE);

    PSECURITY_DESCRIPTOR user_sec_desc;
    ULONG user_sec_desc_size;
    DWORD error = BuildSecurityDescriptor(nullptr,
                                          nullptr,
                                          1,
                                          &access,
                                          0,
                                          nullptr,
                                          base_sec_desc,
                                          &user_sec_desc_size,
                                          &user_sec_desc);
    LocalFree(base_sec_desc);
    if (error != ERROR_SUCCESS) {
        SetLastError(error);
        Wh_Log(L"BuildSecurityDescriptor failed");
        return nullptr;
    }

    *size = user_sec_desc_size;
    return user_sec_desc;
}

// Note: VxKex somehow passes this, but sandboxed pipe connection won't work at all (even with hardcoded Win7 SDDL)
// --no-sandbox is still necessary for Windows 7 users with VxKex
bool SupportsWin10SIDs() {
    const wchar_t* testSddl = L"D:(A;;GA;;;SY)(A;;GA;;;S-1-15-2-1)"; // AppContainer
    PSECURITY_DESCRIPTOR psd = nullptr;
    if (ConvertStringSecurityDescriptorToSecurityDescriptorW(testSddl, SDDL_REVISION_1, &psd, nullptr)) {
        LocalFree(psd);
        return true;
    }
    return false;
}

const void* GetSecurityDescriptorForNamedPipeInstance(size_t* size) {
    // Get a security descriptor which grants the current user and SYSTEM full
    // access to the named pipe. Also grant AppContainer RW access through the ALL
    // APPLICATION PACKAGES SID (S-1-15-2-1). Finally add an Untrusted Mandatory
    // Label for non-AppContainer sandboxed users.
    static size_t sd_size;
    const wchar_t* sddl = SupportsWin10SIDs() ?
        L"D:(A;;GA;;;SY)(A;;GWGR;;;S-1-15-2-1)(A;;GA;;;LW)S:(ML;;;;;S-1-16-0)" :
        L"D:(A;;GA;;;SY)(A;;GRGW;;;WD)S:(ML;;NW;;;LW)"; // Lacks some SIDs such as AppContainer
    static void* sec_desc = GetSecurityDescriptorWithUser(sddl, &sd_size);

    if (size)
        *size = sd_size;
    return sec_desc;
}

void CreateNamedPipeServer() {
    void* pSecurityDescriptor = const_cast<void*>(GetSecurityDescriptorForNamedPipeInstance(NULL));
    if (!pSecurityDescriptor) {
        Wh_Log(L"GetSecurityDescriptorForNamedPipeInstance failed. Pipe won't be accessible to sandboxed CEF renderers.");
    }

    SECURITY_ATTRIBUTES securityAttributes = {};
    securityAttributes.nLength = sizeof(SECURITY_ATTRIBUTES);
    securityAttributes.lpSecurityDescriptor = pSecurityDescriptor;
    securityAttributes.bInheritHandle = TRUE;

    while (!g_shouldClosePipe.load()) {
        OVERLAPPED overlapped = {};
        overlapped.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
        if (!overlapped.hEvent) {
            Wh_Log(L"CreateEvent failed, GLE=%d", GetLastError());
            return;
        }
        HANDLE waits[] = {overlapped.hEvent, g_stopEvent};

        g_hPipe = CreateNamedPipe(
            PIPE_NAME,                                       // Pipe name
            PIPE_ACCESS_DUPLEX | FILE_FLAG_OVERLAPPED,       // Read/Write access with overlapped I/O
            PIPE_TYPE_MESSAGE |                              // Message type pipe
            PIPE_READMODE_MESSAGE |                          // Message-read mode
            PIPE_WAIT,                                       // Blocking mode
            PIPE_UNLIMITED_INSTANCES,                        // Max instances
            512,                                             // Output buffer size
            512,                                             // Input buffer size
            0,                                               // Client time-out
            pSecurityDescriptor ? &securityAttributes : NULL // Security attributes
        );

        if (g_hPipe == INVALID_HANDLE_VALUE) {
            Wh_Log(L"CreateNamedPipe failed, GLE=%d", GetLastError());
            return;
        }

        Wh_Log(L"Waiting for client to connect...");
        BOOL connected = ConnectNamedPipe(g_hPipe, &overlapped);// ? TRUE : (GetLastError() == ERROR_PIPE_CONNECTED);

        if (!connected) {
            int error = GetLastError();
            if (error == ERROR_IO_PENDING) {
                DWORD bytes;
                DWORD waitResult = WaitForMultipleObjects(2, waits, FALSE, INFINITE);
                if (waitResult != WAIT_OBJECT_0) {
                    if (waitResult == WAIT_OBJECT_0 + 1) {
                        Wh_Log(L"Stop event received");
                    } else {
                        Wh_Log(L"Wait failed, GLE=%d", GetLastError());
                    }
                    CancelIoEx(g_hPipe, &overlapped);
                    GetOverlappedResult(g_hPipe, &overlapped, &bytes, TRUE);
                }

                if (GetOverlappedResult(g_hPipe, &overlapped, &bytes, FALSE)) {
                    connected = true;
                } else {
                    Wh_Log(L"GetOverlappedResult failed, GLE=%d", GetLastError());
                }
            } else if (error == ERROR_PIPE_CONNECTED) {
                connected = true;
            } else {
                Wh_Log(L"ConnectNamedPipe failed, GLE=%d", GetLastError());
            }
        }

        if (connected) {
            DWORD clientPid = 0;
            if (GetNamedPipeClientProcessId(g_hPipe, &clientPid)) {
                DWORD expectedPid = g_lastRendererPid.load();
                if (clientPid != expectedPid) {
                    Wh_Log(L"Rejected pipe connection from unexpected PID: %lu (expected %lu)", clientPid, expectedPid);
                    CloseHandle(overlapped.hEvent);
                    CloseHandle(g_hPipe);
                    continue;
                }
            }

            Wh_Log(L"Client connected, waiting for message...");
            wchar_t buffer[512];
            DWORD bytesRead;
            while (!g_shouldClosePipe.load()) {
                BOOL result = ReadFile(g_hPipe, buffer, sizeof(buffer) - sizeof(wchar_t), &bytesRead, &overlapped);
                if (!result) {
                    DWORD error = GetLastError();
                    if (error != ERROR_IO_PENDING) {
                        if (error == ERROR_BROKEN_PIPE || error == ERROR_PIPE_NOT_CONNECTED) {
                            Wh_Log(L"Client disconnected, GLE=%d", error);
                        } else {
                            Wh_Log(L"Unknown IPC error, GLE=%d", error);
                        }
                        break;
                    }

                    DWORD waitResult = WaitForMultipleObjects(2, waits, FALSE, INFINITE);
                    if (waitResult != WAIT_OBJECT_0) {
                        if (waitResult == WAIT_OBJECT_0 + 1) {
                            Wh_Log(L"Stop event received");
                        } else {
                            Wh_Log(L"Wait failed, GLE=%d", GetLastError());
                        }
                        CancelIoEx(g_hPipe, &overlapped);
                        GetOverlappedResult(g_hPipe, &overlapped, &bytesRead, TRUE); // let the cancel complete
                        break;
                    }

                    if (!GetOverlappedResult(g_hPipe, &overlapped, &bytesRead, FALSE)) {
                        Wh_Log(L"GetOverlappedResult failed, GLE=%d", GetLastError());
                        break;
                    }
                }

                if (bytesRead >= sizeof(buffer) - sizeof(wchar_t)) {
                    Wh_Log(L"Buffer overflow detected");
                    continue;
                }
                buffer[bytesRead / sizeof(wchar_t)] = L'\0';
                Wh_Log(L"Received message: %s", buffer);
                HandleWindhawkComm(buffer);
            }
        }

        Wh_Log(L"Closing pipe...");
        CloseHandle(overlapped.hEvent);
        CloseHandle(g_hPipe);
        g_hPipe = INVALID_HANDLE_VALUE;
    }

    LocalFree(pSecurityDescriptor);
}

int ConnectToNamedPipe() {
    g_stopEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
    if (!g_stopEvent) {
        int gle = GetLastError();
        Wh_Log(L"CreateEvent failed, GLE=%d", gle);
        return gle;
    }

    HANDLE hPipe = CreateFile(
        PIPE_NAME,
        GENERIC_READ | GENERIC_WRITE,
        0,
        NULL,
        OPEN_EXISTING,
        FILE_FLAG_OVERLAPPED,
        NULL
    );

    if (hPipe == INVALID_HANDLE_VALUE) {
        int gle = GetLastError();
        Wh_Log(L"CreateFile failed, GLE=%d", gle);
        CloseHandle(g_stopEvent);
        return gle;
    }

    g_hClientPipe.store(hPipe);

    g_pipeThread = std::thread([]() {
        wchar_t buffer[512];
        DWORD bytesRead;
        OVERLAPPED overlapped = {};
        overlapped.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
        if (!overlapped.hEvent) {
            Wh_Log(L"CreateEvent failed, GLE=%d", GetLastError());
            return;
        }
        HANDLE waits[] = {overlapped.hEvent, g_stopEvent};

        while (!g_shouldClosePipe.load()) {
            HANDLE hPipe = g_hClientPipe.load();
            BOOL result = ReadFile(hPipe, buffer, sizeof(buffer) - sizeof(wchar_t), &bytesRead, &overlapped);
            if (!result) {
                int error = GetLastError();
                if (error == ERROR_IO_PENDING) {
                    DWORD waitResult = WaitForMultipleObjects(2, waits, FALSE, INFINITE);
                    if (waitResult != WAIT_OBJECT_0) {
                        if (waitResult == WAIT_OBJECT_0 + 1) {
                            Wh_Log(L"Stop event received");
                        } else {
                            Wh_Log(L"Wait failed, GLE=%d", GetLastError());
                        }
                        CancelIoEx(hPipe, &overlapped);
                        GetOverlappedResult(hPipe, &overlapped, &bytesRead, TRUE); // let the cancel complete
                        break;
                    }

                    if (!GetOverlappedResult(hPipe, &overlapped, &bytesRead, FALSE)) {
                        Wh_Log(L"GetOverlappedResult failed, GLE=%d", GetLastError());
                        break;
                    }
                } else {
                    if (error == ERROR_BROKEN_PIPE || error == ERROR_PIPE_NOT_CONNECTED) {
                        Wh_Log(L"Server disconnected, GLE=%d", error);
                    } else {
                        Wh_Log(L"Unknown IPC error, GLE=%d", error);
                    }
                    break;
                }
            }

            buffer[bytesRead / sizeof(wchar_t)] = L'\0';
            Wh_Log(L"Received message: %s", buffer);
            if (wcsncmp(buffer, L"/WH:QueryResponse:", 18) == 0) {
                cte_queryResponse_t response = {};
                if (swscanf(buffer + 18, L"%d:%d:%d:%d:%d:%d:%d:%d:%d:%d:%d:%d:%d:%d:%d:%d:%d:%d:%d:%d:%d:%d:%d:%d:%lf:%d",
                    &response.queryId,
                    &response.showframe,
                    &response.showframeonothers,
                    &response.showmenu,
                    &response.showcontrols,
                    &response.transparentcontrols,
                    &response.transparentrendering,
                    &response.ignoreminsize,
                    &response.noforceddarkmode,
                    &response.forceextensions,
                    &response.blockupdates,
                    &response.allowuntested,
                    &response.isMaximized,
                    &response.isTopMost,
                    &response.isLayered,
                    &response.isTransparent,
                    &response.isThemingEnabled,
                    &response.isDwmEnabled,
                    &response.hwAccelerated,
                    &response.minWidth,
                    &response.minHeight,
                    &response.titleLocked,
                    &response.dpi,
                    &response.speedModSupported,
                    &response.playbackSpeed,
                    &response.immediateSpeedChange) == 26
                ) {
                    response.success = TRUE;
                    // Notify the condition variable
                    {
                        std::lock_guard<std::mutex> lock(g_ipcMutex);
                        g_queryResponse = response;
                        g_queryResponseId = g_queryResponse.queryId;
                    }
                    g_queryResponseCv.notify_one();
                }
            }
        }

        {
            std::lock_guard<std::mutex> lock(g_ipcMutex);
            g_pipeDisconnected = true;
        }
        g_queryResponseCv.notify_all();

        CloseHandle(overlapped.hEvent);
        {
            std::lock_guard lock(g_pipeMutex);
            HANDLE hPipe = g_hClientPipe.exchange(INVALID_HANDLE_VALUE);
            if (hPipe != INVALID_HANDLE_VALUE) {
                CloseHandle(hPipe);
            }
        }
    });

    return 0;
}

int SendNamedPipeMessage(LPCWSTR message, cte_queryResponse_t* response = NULL) {
    {
        std::unique_lock lock(g_pipeMutex);

        HANDLE hPipe = g_hClientPipe.load();
        if (hPipe == INVALID_HANDLE_VALUE) {
            Wh_Log(L"SendNamedPipeMessage failed: pipe is not connected");
            return ERROR_PIPE_NOT_CONNECTED;
        }

        DWORD bytesWritten;
        size_t messageLength = wcslen(message) * sizeof(wchar_t);
        Wh_Log(L"Sending message: %s", message);

        OVERLAPPED overlapped = {};
        overlapped.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
        if (!overlapped.hEvent) {
            int gle = GetLastError();
            Wh_Log(L"CreateEvent failed, GLE=%d", gle);
            return gle;
        }
        HANDLE waits[] = {overlapped.hEvent, g_stopEvent};

        BOOL result = WriteFile(hPipe, message, messageLength, &bytesWritten, &overlapped);
        if (!result) {
            int error = GetLastError();
            if (error != ERROR_IO_PENDING) {
                Wh_Log(L"WriteFile failed, GLE=%d", error);
                CloseHandle(overlapped.hEvent);
                return error;
            }

            // Wait for the write operation to complete
            DWORD waitResult = WaitForMultipleObjects(2, waits, FALSE, 2000);
            if (waitResult != WAIT_OBJECT_0) { // stop event
                int error = GetLastError();
                if (waitResult == WAIT_OBJECT_0 + 1) {
                    Wh_Log(L"Stop event received");
                    error = ERROR_OPERATION_ABORTED;
                } else if (waitResult == WAIT_TIMEOUT) {
                    Wh_Log(L"Query wait timed out");
                    error = ERROR_TIMEOUT;
                } else {
                    Wh_Log(L"Wait failed, GLE=%d", error);
                }
                CancelIoEx(hPipe, &overlapped);
                GetOverlappedResult(hPipe, &overlapped, &bytesWritten, TRUE); // let the cancel complete

                CloseHandle(overlapped.hEvent);
                return error;
            }

            if (!GetOverlappedResult(hPipe, &overlapped, &bytesWritten, FALSE)) {
                error = GetLastError();
                Wh_Log(L"GetOverlappedResult failed, GLE=%d", error);
                CloseHandle(overlapped.hEvent);
                return error;
            }
        }

        Wh_Log(L"Message sent successfully");
        CloseHandle(overlapped.hEvent);
    }

    if (wcsncmp(message, L"/WH:Query:", 10) == 0) {
        // Wait for the query response
        std::unique_lock<std::mutex> lock(g_ipcMutex);

        int queryId;
        if (swscanf(message + 10, L"%d", &queryId) != 1) {
            Wh_Log(L"Query ID missing!");
            return ERROR_OPERATION_ABORTED;
        }

        g_queryResponseCv.wait_for(lock, std::chrono::seconds(2), [queryId] { return g_queryResponseId == queryId || g_pipeDisconnected; });
        if (g_queryResponseId != queryId) {
            if (g_pipeDisconnected) {
                return ERROR_PIPE_NOT_CONNECTED;
            }
            return ERROR_TIMEOUT;
        } else if (response) {
            *response = g_queryResponse;
        }
        g_queryResponseId = -1;
    }

    return 0;
}

int CEF_CALLBACK WindhawkCommV8Handler(cef_v8handler_t* self, const cef_string_t* name, cef_v8value_t* object, size_t argumentsCount, cef_v8value_t* const* arguments, cef_v8value_t** retval, cef_string_t* exception) {
    Wh_Log(L"WindhawkCommV8Handler called with name: %s", name->str);
    std::u16string nameStr(name->str, name->length);
    if (g_hClientPipe.load() == INVALID_HANDLE_VALUE) {
        cef_string_t* msg = GenerateCefString(u"Disconnected from the Windhawk mod running in the main process. Is the mod unloaded?");
        *exception = *msg;
        free(msg->str);
        free(msg);
        return TRUE;
    }

    int ipcRes = -1;
    if (nameStr == u"extendFrame") {
        if (argumentsCount == 4 && arguments[0]->is_int(arguments[0]) && arguments[1]->is_int(arguments[1]) && arguments[2]->is_int(arguments[2]) && arguments[3]->is_int(arguments[3])) {
            int left = arguments[0]->get_int_value(arguments[0]);
            int right = arguments[1]->get_int_value(arguments[1]);
            int top = arguments[2]->get_int_value(arguments[2]);
            int bottom = arguments[3]->get_int_value(arguments[3]);
            ipcRes = SendNamedPipeMessage((L"/WH:ExtendFrame:" + std::to_wstring(left) + L":" + std::to_wstring(right) + L":" + std::to_wstring(top) + L":" + std::to_wstring(bottom)).c_str());
        } else {
            cef_string_t* msg = GenerateCefString(u"Invalid argument types, expected (int, int, int, int)");
            *exception = *msg;
            free(msg->str);
            free(msg);
            return TRUE;
        }
    } else if (nameStr == u"minimize") {
        ipcRes = SendNamedPipeMessage(L"/WH:Minimize");
    } else if (nameStr == u"maximizeRestore") {
        ipcRes = SendNamedPipeMessage(L"/WH:MaximizeRestore");
    } else if (nameStr == u"close") {
        ipcRes = SendNamedPipeMessage(L"/WH:Close");
    } else if (nameStr == u"focus") {
        ipcRes = SendNamedPipeMessage(L"/WH:Focus");
    } else if (nameStr == u"setLayered") {
        if (argumentsCount >= 1 && arguments[0]->is_bool(arguments[0])) {
            bool layered = arguments[0]->get_bool_value(arguments[0]);
            if (argumentsCount >= 2) {
                if (!arguments[1]->is_int(arguments[1])) {
                    cef_string_t* msg = GenerateCefString(u"Invalid argument types, expected (bool, optional int, optional string)");
                    *exception = *msg;
                    free(msg->str);
                    free(msg);
                    return TRUE;
                }
                int alpha = arguments[1]->get_int_value(arguments[1]);
                if (argumentsCount >= 3) {
                    if (!arguments[2]->is_string(arguments[2])) {
                        cef_string_t* msg = GenerateCefString(u"Invalid argument types, expected (bool, optional int, optional string)");
                        *exception = *msg;
                        free(msg->str);
                        free(msg);
                        return TRUE;
                    }
                    cef_string_t* colorArg = arguments[2]->get_string_value(arguments[2]);
                    std::wstring colorStr(colorArg->str, colorArg->str + colorArg->length);
                    int color = 0; // only for format validation
                    if (swscanf(colorStr.c_str(), L"%x", &color) == 1) {
                        ipcRes = SendNamedPipeMessage((L"/WH:SetLayered:" + std::to_wstring(layered) + L":" + std::to_wstring(alpha) + L":" + colorStr).c_str());
                    } else {
                        cef_string_t* msg = GenerateCefString(u"Invalid color format, expected six-digit hex string");
                        *exception = *msg;
                        free(msg->str);
                        free(msg);
                        return TRUE;
                    }
                } else {
                    ipcRes = SendNamedPipeMessage((L"/WH:SetLayered:" + std::to_wstring(layered) + L":" + std::to_wstring(alpha)).c_str());
                }
            } else {
                ipcRes = SendNamedPipeMessage((L"/WH:SetLayered:" + std::to_wstring(layered)).c_str());
            }
        } else {
            cef_string_t* msg = GenerateCefString(u"Invalid argument types, expected (bool, optional int, optional string)");
            *exception = *msg;
            free(msg->str);
            free(msg);
            return TRUE;
        }
    } else if (nameStr == u"setTransparent") {
        if (argumentsCount >= 1 && arguments[0]->is_bool(arguments[0])) {
            bool transparent = arguments[0]->get_bool_value(arguments[0]);
            ipcRes = SendNamedPipeMessage((L"/WH:SetTransparent:" + std::to_wstring(transparent)).c_str());
        } else {
            cef_string_t* msg = GenerateCefString(u"Invalid argument types, expected (bool)");
            *exception = *msg;
            free(msg->str);
            free(msg);
            return TRUE;
        }
    } else if (nameStr == u"setBackdrop") {
        if (argumentsCount == 1 && arguments[0]->is_string(arguments[0])) {
            cef_string_t* backdropArg = arguments[0]->get_string_value(arguments[0]);
            std::wstring backdropStr(backdropArg->str, backdropArg->str + backdropArg->length);
            if (backdropStr == L"none" || backdropStr == L"mica" || backdropStr == L"acrylic" || backdropStr == L"tabbed") {
                ipcRes = SendNamedPipeMessage((L"/WH:SetBackdrop:" + backdropStr).c_str());
            } else {
                cef_string_t* msg = GenerateCefString(u"Invalid backdrop type, expected 'none', 'mica', 'acrylic', or 'tabbed'");
                *exception = *msg;
                free(msg->str);
                free(msg);
                return TRUE;
            }
        } else {
            cef_string_t* msg = GenerateCefString(u"Invalid argument types, expected (string)");
            *exception = *msg;
            free(msg->str);
            free(msg);
            return TRUE;
        }
    } else if (nameStr == u"resizeTo") {
        if (argumentsCount == 2 && arguments[0]->is_int(arguments[0]) && arguments[1]->is_int(arguments[1])) {
            int width = arguments[0]->get_int_value(arguments[0]);
            int height = arguments[1]->get_int_value(arguments[1]);
            ipcRes = SendNamedPipeMessage((L"/WH:ResizeTo:" + std::to_wstring(width) + L":" + std::to_wstring(height)).c_str());
        } else {
            cef_string_t* msg = GenerateCefString(u"Invalid argument types, expected (int, int)");
            *exception = *msg;
            free(msg->str);
            free(msg);
            return TRUE;
        }
    } else if (nameStr == u"setMinSize") {
        if (argumentsCount == 2 && arguments[0]->is_int(arguments[0]) && arguments[1]->is_int(arguments[1])) {
            int width = arguments[0]->get_int_value(arguments[0]);
            int height = arguments[1]->get_int_value(arguments[1]);
            ipcRes = SendNamedPipeMessage((L"/WH:SetMinSize:" + std::to_wstring(width) + L":" + std::to_wstring(height)).c_str());
        } else {
            cef_string_t* msg = GenerateCefString(u"Invalid argument types, expected (int, int)");
            *exception = *msg;
            free(msg->str);
            free(msg);
            return TRUE;
        }
    } else if (nameStr == u"setTopMost") {
        if (argumentsCount >= 1 && arguments[0]->is_bool(arguments[0])) {
            bool topmost = arguments[0]->get_bool_value(arguments[0]);
            ipcRes = SendNamedPipeMessage((L"/WH:SetTopMost:" + std::to_wstring(topmost)).c_str());
        } else {
            cef_string_t* msg = GenerateCefString(u"Invalid argument types, expected (bool)");
            *exception = *msg;
            free(msg->str);
            free(msg);
            return TRUE;
        }
    } else if (nameStr == u"setTitle") {
        if (argumentsCount == 1 && arguments[0]->is_string(arguments[0])) {
            cef_string_t* titleArg = arguments[0]->get_string_value(arguments[0]);
            std::wstring titleStr(titleArg->str, titleArg->str + titleArg->length);
            if (titleStr.length() > 255) {
                cef_string_t* msg = GenerateCefString(u"Title is too long, max is 255 characters");
                *exception = *msg;
                free(msg->str);
                free(msg);
                return TRUE;
            }
            ipcRes = SendNamedPipeMessage((L"/WH:SetTitle:" + titleStr).c_str());
        } else {
            cef_string_t* msg = GenerateCefString(u"Invalid argument types, expected (string)");
            *exception = *msg;
            free(msg->str);
            free(msg);
            return TRUE;
        }
    } else if (nameStr == u"lockTitle") {
        if (argumentsCount >= 1 && arguments[0]->is_bool(arguments[0])) {
            bool lock = arguments[0]->get_bool_value(arguments[0]);
            ipcRes = SendNamedPipeMessage((L"/WH:LockTitle:" + std::to_wstring(lock)).c_str());
        } else {
            cef_string_t* msg = GenerateCefString(u"Invalid argument types, expected (bool)");
            *exception = *msg;
            free(msg->str);
            free(msg);
            return TRUE;
        }
    } else if (nameStr == u"openSpotifyMenu") {
        ipcRes = SendNamedPipeMessage(L"/WH:OpenSpotifyMenu");
    #ifdef _M_X64
    } else if (nameStr == u"setPlaybackSpeed") {
        if (argumentsCount == 1 && arguments[0]->is_double(arguments[0])) {
            double speed = arguments[0]->get_double_value(arguments[0]);
            if (speed <= 0 || speed > 5.0) {
                // Prevent potential ban risk by limiting the playback speed
                // Note: setting to zero or negative values will be ignored by SetPlaybackSpeed and causes crashes in CreateTrackPlayer
                cef_string_t* msg = GenerateCefString(u"Playback speed must be faster than 0 and less than or equal to 5.0");
                *exception = *msg;
                free(msg->str);
                free(msg);
                return TRUE;
            }
            ipcRes = SendNamedPipeMessage((L"/WH:SetPlaybackSpeed:" + std::to_wstring(speed)).c_str());
        } else {
            cef_string_t* msg = GenerateCefString(u"Invalid argument types, expected (double)");
            *exception = *msg;
            free(msg->str);
            free(msg);
            return TRUE;
        }
    #endif
    } else if (nameStr == u"query") {
        cte_queryResponse_t response = {};
        ipcRes = SendNamedPipeMessage((L"/WH:Query:" + std::to_wstring(g_lastQueryId++)).c_str(), &response);
        if (ipcRes == 0 && response.success) {
            cef_v8value_t* retobj = cef_v8value_create_object(NULL, NULL);
            cef_v8value_t* configObj = cef_v8value_create_object(NULL, NULL);
            AddValueToObj(configObj, u"showframe", cef_v8value_create_bool(response.showframe));
            AddValueToObj(configObj, u"showframeonothers", cef_v8value_create_bool(response.showframeonothers));
            AddValueToObj(configObj, u"showmenu", cef_v8value_create_bool(response.showmenu));
            AddValueToObj(configObj, u"showcontrols", cef_v8value_create_bool(response.showcontrols));
            AddValueToObj(configObj, u"transparentcontrols", cef_v8value_create_bool(response.transparentcontrols));
            AddValueToObj(configObj, u"transparentrendering", cef_v8value_create_bool(response.transparentrendering));
            AddValueToObj(configObj, u"ignoreminsize", cef_v8value_create_bool(response.ignoreminsize));
            AddValueToObj(configObj, u"noforceddarkmode", cef_v8value_create_bool(response.noforceddarkmode));
            AddValueToObj(configObj, u"forceextensions", cef_v8value_create_bool(response.forceextensions));
            AddValueToObj(configObj, u"blockupdates", cef_v8value_create_bool(response.blockupdates));
            AddValueToObj(configObj, u"allowuntested", cef_v8value_create_bool(response.allowuntested));
            AddValueToObj(retobj, u"options", configObj);
            AddValueToObj(retobj, u"isMaximized", cef_v8value_create_bool(response.isMaximized));
            AddValueToObj(retobj, u"isTopMost", cef_v8value_create_bool(response.isTopMost));
            AddValueToObj(retobj, u"isLayered", cef_v8value_create_bool(response.isLayered));
            AddValueToObj(retobj, u"isTransparent", cef_v8value_create_bool(response.isTransparent));
            AddValueToObj(retobj, u"isThemingEnabled", cef_v8value_create_bool(response.isThemingEnabled));
            AddValueToObj(retobj, u"isDwmEnabled", cef_v8value_create_bool(response.isDwmEnabled));
            AddValueToObj(retobj, u"hwAccelerated", cef_v8value_create_bool(response.hwAccelerated));
            AddValueToObj(retobj, u"minWidth", cef_v8value_create_int(response.minWidth));
            AddValueToObj(retobj, u"minHeight", cef_v8value_create_int(response.minHeight));
            AddValueToObj(retobj, u"titleLocked", cef_v8value_create_bool(response.titleLocked));
            AddValueToObj(retobj, u"dpi", cef_v8value_create_int(response.dpi));
            AddValueToObj(retobj, u"speedModSupported", cef_v8value_create_bool(response.speedModSupported));
            #ifdef _M_X64
            AddValueToObj(retobj, u"playbackSpeed", cef_v8value_create_double(response.playbackSpeed));
            AddValueToObj(retobj, u"immediateSpeedChange", cef_v8value_create_bool(response.immediateSpeedChange));
            #endif
            *retval = retobj;
        } else {
            cef_string_t* msg = GenerateCefString(u"Error: Query response not received");
            *exception = *msg;
            free(msg->str);
            free(msg);
            return TRUE;
        }
    }

    if (ipcRes != 0) {
        cef_string_t* msg = FormatCefString(L"IPC Error: %d", ipcRes);
        *exception = *msg;
        free(msg->str);
        free(msg);
    }
    return TRUE;
}

std::vector<cef_v8handler_t*> cancelCosmosRequest_v8handlers;
std::vector<cef_v8handler_t*> cancelEsperantoCall_v8handlers;
std::vector<cef_v8handler_t*> _getSpotifyModule_v8handlers;
cef_v8handler_t* last_cancelCosmosRequest_v8handler;
typedef int CEF_CALLBACK (*v8func_exec_t)(cef_v8handler_t* self, const cef_string_t* name, cef_v8value_t* object, size_t argumentsCount, cef_v8value_t* const* arguments, cef_v8value_t** retval, cef_string_t* exception);
v8func_exec_t CEF_CALLBACK cancelCosmosRequest_original; // These addresses are static (consistent on multiple function creations)
v8func_exec_t CEF_CALLBACK cancelEsperantoCall_original;
v8func_exec_t CEF_CALLBACK _getSpotifyModule_original;

int InjectCTEV8Handler(cef_v8value_t* const* arguments, cef_v8value_t** retval) {
    cef_string_t* arg = arguments[0]->get_string_value(arguments[0]); // NULL when it's an empty string
    if (arg != NULL && last_cancelCosmosRequest_v8handler != NULL && u"ctewh" == std::u16string(arg->str, arg->length)) {
        Wh_Log(L"CTEWH is being requested");
        cef_v8value_t* retobj = cef_v8value_create_object(NULL, NULL);
        AddFunctionToObj(retobj, u"query", last_cancelCosmosRequest_v8handler);
        AddFunctionToObj(retobj, u"extendFrame", last_cancelCosmosRequest_v8handler);
        AddFunctionToObj(retobj, u"minimize", last_cancelCosmosRequest_v8handler);
        AddFunctionToObj(retobj, u"maximizeRestore", last_cancelCosmosRequest_v8handler);
        AddFunctionToObj(retobj, u"close", last_cancelCosmosRequest_v8handler);
        AddFunctionToObj(retobj, u"focus", last_cancelCosmosRequest_v8handler);
        AddFunctionToObj(retobj, u"setLayered", last_cancelCosmosRequest_v8handler);
        AddFunctionToObj(retobj, u"setTransparent", last_cancelCosmosRequest_v8handler);
        AddFunctionToObj(retobj, u"setBackdrop", last_cancelCosmosRequest_v8handler);
        AddFunctionToObj(retobj, u"resizeTo", last_cancelCosmosRequest_v8handler);
        AddFunctionToObj(retobj, u"setMinSize", last_cancelCosmosRequest_v8handler);
        AddFunctionToObj(retobj, u"setTopMost", last_cancelCosmosRequest_v8handler);
        AddFunctionToObj(retobj, u"setTitle", last_cancelCosmosRequest_v8handler);
        AddFunctionToObj(retobj, u"lockTitle", last_cancelCosmosRequest_v8handler);
        AddFunctionToObj(retobj, u"openSpotifyMenu", last_cancelCosmosRequest_v8handler);
        #ifdef _M_X64
        AddFunctionToObj(retobj, u"setPlaybackSpeed", last_cancelCosmosRequest_v8handler);
        #endif
        cef_v8value_t* initialConfigObj = cef_v8value_create_object(NULL, NULL);
        AddValueToObj(initialConfigObj, u"showframe", cef_v8value_create_bool(cte_settings.showframe));
        AddValueToObj(initialConfigObj, u"showframeonothers", cef_v8value_create_bool(cte_settings.showframeonothers));
        AddValueToObj(initialConfigObj, u"showmenu", cef_v8value_create_bool(cte_settings.showmenu));
        AddValueToObj(initialConfigObj, u"showcontrols", cef_v8value_create_bool(cte_settings.showcontrols));
        AddValueToObj(initialConfigObj, u"transparentcontrols", cef_v8value_create_bool(cte_settings.transparentcontrols));
        AddValueToObj(initialConfigObj, u"transparentrendering", cef_v8value_create_bool(cte_settings.transparentrendering));
        AddValueToObj(initialConfigObj, u"ignoreminsize", cef_v8value_create_bool(cte_settings.ignoreminsize));
        AddValueToObj(initialConfigObj, u"noforceddarkmode", cef_v8value_create_bool(cte_settings.noforceddarkmode));
        AddValueToObj(initialConfigObj, u"forceextensions", cef_v8value_create_bool(cte_settings.forceextensions));
        AddValueToObj(initialConfigObj, u"blockupdates", cef_v8value_create_bool(cte_settings.blockupdates));
        AddValueToObj(initialConfigObj, u"allowuntested", cef_v8value_create_bool(cte_settings.allowuntested));
        AddValueToObj(retobj, u"initialOptions", initialConfigObj);
        std::wstring stdModVer(WH_MOD_VERSION);
        AddValueToObj(retobj, u"version", std::u16string(stdModVer.begin(), stdModVer.end()));

        *retval = retobj;
        return TRUE;
    }
    return FALSE;
}

int CEF_CALLBACK cancelCosmosRequest_hook(cef_v8handler_t* self, const cef_string_t* name, cef_v8value_t* object, size_t argumentsCount, cef_v8value_t* const* arguments, cef_v8value_t** retval, cef_string_t* exception) {
    Wh_Log(L"cancelCosmosRequest_hook called with name: %s", name->str);
    std::u16string nameStr(name->str, name->length);
    if (nameStr != u"cancelCosmosRequest") {
        return WindhawkCommV8Handler(self, name, object, argumentsCount, arguments, retval, exception);
    }
    if (argumentsCount == 1) {
        if (InjectCTEV8Handler(arguments, retval)) { // why not?
            return TRUE;
        }
    }
    return cancelCosmosRequest_original(self, name, object, argumentsCount, arguments, retval, exception);
}

int CEF_CALLBACK cancelEsperantoCall_hook(cef_v8handler_t* self, const cef_string_t* name, cef_v8value_t* object, size_t argumentsCount, cef_v8value_t* const* arguments, cef_v8value_t** retval, cef_string_t* exception) {
    Wh_Log(L"cancelEsperantoCall_hook called with name: %s", name->str);
    if (argumentsCount == 1) {
        if (InjectCTEV8Handler(arguments, retval)) {
            return TRUE;
        }
    }
    return cancelEsperantoCall_original(self, name, object, argumentsCount, arguments, retval, exception);
}

int CEF_CALLBACK _getSpotifyModule_hook(cef_v8handler_t* self, const cef_string_t* name, cef_v8value_t* object, size_t argumentsCount, cef_v8value_t* const* arguments, cef_v8value_t** retval, cef_string_t* exception) {
    Wh_Log(L"_getSpotifyModule_hook called with name: %s", name->str);
    if (argumentsCount == 1) {
        if (InjectCTEV8Handler(arguments, retval)) {
            return TRUE;
        }
    }
    return _getSpotifyModule_original(self, name, object, argumentsCount, arguments, retval, exception);
}

void PruneV8Handlers(std::vector<cef_v8handler_t*>& handlers, v8func_exec_t original) {
    std::erase_if(handlers, [original](cef_v8handler_t* h) {
        if (!h->base.has_one_ref(&h->base)) {
            return false;
        }
        h->execute = original;
        h->base.release(&h->base);
        return true;
    });
}

cef_v8value_create_function_t CEF_EXPORT cef_v8value_create_function_hook = [](const cef_string_t* name, cef_v8handler_t* handler) -> cef_v8value_t* {
    Wh_Log(L"cef_v8value_create_function called with name: %s", name->str);
    // This function exists on all Spotify versions supported by this mod
    // Reuse this function as a mod JS API's handler instead of allocating a new cef_v8handler_t* everytime
    // As this function's memory allocation is internally managed by Spotify
    // And libcef.dll does not expose a function to create an internally managed V8 handlers

    // ... Yes, I should've used this function for API access from the beginning, obviously
    HANDLE hPipe = g_hClientPipe.load();
    if (u"cancelCosmosRequest" == std::u16string(name->str, name->length)) {
        Wh_Log(L"cancelCosmosRequest is being created");
        if (hPipe == INVALID_HANDLE_VALUE) {
            // API won't be available if the pipe is not connected
            return cef_v8value_create_function_original(name, handler);
        }
        if (handler->execute != cancelCosmosRequest_hook) {
            cancelCosmosRequest_original = handler->execute;
            handler->execute = cancelCosmosRequest_hook;
            // Release handlers that only this mod hold reference
            PruneV8Handlers(cancelCosmosRequest_v8handlers, cancelCosmosRequest_original);
            // These V8 functions are created twice on page load (seems the first one is only used)
            // And it gets called twice whenever the page reloads
            // So save it in a vector and restore all on uninit
            cancelCosmosRequest_v8handlers.push_back(handler);
            handler->base.add_ref(&handler->base);
            last_cancelCosmosRequest_v8handler = handler;
        }
        return cef_v8value_create_function_original(name, handler);
    }
    // Originally _getSpotifyModule was hooked but that function was removed in Spotify 1.2.56, which was released while this mod was in development
    // So, we're hooking cancelEsperantoCall instead. The function choice and arguments are odd, as it was originally intended for _getSpotifyModule. Deal with it.
    if (u"cancelEsperantoCall" == std::u16string(name->str, name->length)) {
        Wh_Log(L"cancelEsperantoCall is being created");
        if (hPipe == INVALID_HANDLE_VALUE) {
            // API won't be available if the pipe is not connected
            return cef_v8value_create_function_original(name, handler);
        }
        if (handler->execute != cancelEsperantoCall_hook) {
            cancelEsperantoCall_original = handler->execute;
            handler->execute = cancelEsperantoCall_hook;
            PruneV8Handlers(cancelEsperantoCall_v8handlers, cancelEsperantoCall_original);
            cancelEsperantoCall_v8handlers.push_back(handler);
            handler->base.add_ref(&handler->base);
        }
        return cef_v8value_create_function_original(name, handler);
    }
    // And hook _getSpotifyModule too for 1.2.4-1.2.32 which lack cancelEsperantoCall
    // I'd better just hook cancelCosmosRequest from the beginning as it's exists on all XPUI Spotify versions
    // But it's too late, 0.6 is already released without realizing that cancelEsperantoCall is only available on 1.2.33+
    if (u"_getSpotifyModule" == std::u16string(name->str, name->length)) {
        Wh_Log(L"_getSpotifyModule is being created");
        if (hPipe == INVALID_HANDLE_VALUE) {
            // API won't be available if the pipe is not connected
            return cef_v8value_create_function_original(name, handler);
        }
        if (handler->execute != _getSpotifyModule_hook) {
            _getSpotifyModule_original = handler->execute;
            handler->execute = _getSpotifyModule_hook;
            PruneV8Handlers(_getSpotifyModule_v8handlers, _getSpotifyModule_original);
            _getSpotifyModule_v8handlers.push_back(handler);
            handler->base.add_ref(&handler->base);
        }
    }
    return cef_v8value_create_function_original(name, handler);
};

BOOL InitSpotifyRendererHooks(int major) {
    g_isSpotifyRenderer = TRUE;
    Wh_Log(L"Initializing Spotify renderer hooks");

    // CEF 134 / Spotify 1.2.62 changed the names of these exported functions for some reason
    std::string v8FuncPrefix = "cef_v8value_";
    if (major >= 134) {
        v8FuncPrefix = "cef_v8_value_";
    }
    cef_v8value_create_function_t cef_v8value_create_function = (cef_v8value_create_function_t)GetProcAddress(g_cefModule, (v8FuncPrefix + "create_function").c_str());
    if (!cef_v8value_create_function) {
        v8FuncPrefix = "cef_v8_value_";
        cef_v8value_create_function = (cef_v8value_create_function_t)GetProcAddress(g_cefModule, (v8FuncPrefix + "create_function").c_str());
    }
    cef_v8value_create_bool = (cef_v8value_create_bool_t)GetProcAddress(g_cefModule, (v8FuncPrefix + "create_bool").c_str());
    cef_v8value_create_int = (cef_v8value_create_int_t)GetProcAddress(g_cefModule, (v8FuncPrefix + "create_int").c_str());
    cef_v8value_create_double = (cef_v8value_create_double_t)GetProcAddress(g_cefModule, (v8FuncPrefix + "create_double").c_str());
    cef_v8value_create_string = (cef_v8value_create_string_t)GetProcAddress(g_cefModule, (v8FuncPrefix + "create_string").c_str());
    cef_v8value_create_object = (cef_v8value_create_object_t)GetProcAddress(g_cefModule, (v8FuncPrefix + "create_object").c_str());
    cef_v8value_create_array = (cef_v8value_create_array_t)GetProcAddress(g_cefModule, (v8FuncPrefix + "create_array").c_str());

    // Returning after connecting to the pipe crashes the renderer, so get these functions first
    if (!cef_v8value_create_function || !cef_v8value_create_bool || !cef_v8value_create_int || !cef_v8value_create_double || !cef_v8value_create_string || !cef_v8value_create_object || !cef_v8value_create_array) {
        Wh_Log(L"Failed to get CEF functions");
        return FALSE;
    }

    if (ConnectToNamedPipe() == 0) {
        Wh_Log(L"Connected to named pipe");
    } else {
        Wh_Log(L"Unable to connect to named pipe");
        return FALSE;
    }

    WindhawkUtils::SetFunctionHook(cef_v8value_create_function, cef_v8value_create_function_hook, &cef_v8value_create_function_original);

    return TRUE;
}
#pragma endregion

void LoadSettings() {
    cte_settings.showframe = Wh_GetIntSetting(L"spotify.showframe");
    cte_settings.showframeonothers = Wh_GetIntSetting(L"spotify.showframeonothers");
    cte_settings.showmenu = Wh_GetIntSetting(L"spotify.showmenu");
    cte_settings.showcontrols = Wh_GetIntSetting(L"spotify.showcontrols");
    cte_settings.transparentcontrols = Wh_GetIntSetting(L"spotify.transparentcontrols");
    cte_settings.ignoreminsize = Wh_GetIntSetting(L"spotify.ignoreminsize");
    cte_settings.transparentrendering = Wh_GetIntSetting(L"spotify.transparentrendering");
    cte_settings.noforceddarkmode = Wh_GetIntSetting(L"spotify.noforceddarkmode");
    cte_settings.forceextensions = Wh_GetIntSetting(L"spotify.forceextensions");
    cte_settings.blockupdates = Wh_GetIntSetting(L"spotify.blockupdates");
    cte_settings.allowuntested = Wh_GetIntSetting(L"spotify.allowuntested");
}

void ApplySpeedFromSettings(BOOL notifyInvalid = FALSE) {
    auto newSpeedStr = WindhawkUtils::StringSetting::make(L"spotify.playbackspeed");
    Wh_Log(L"ApplySpeedFromSettings: %s", newSpeedStr.get());
    if (!*newSpeedStr) {
        g_playbackSpeed = 1;
        #ifdef _M_X64
            if (SetPlaybackSpeed != NULL && g_currentTrackPlayer != NULL) {
                SetPlaybackSpeed(g_currentTrackPlayer, 1);
            }
        #endif
        return;
    }
    try {
        double newSpeed = std::stod(std::wstring(newSpeedStr));
        if (fabs(newSpeed - g_playbackSpeed) > 1e-6) {
            #ifdef _M_X64
                if (CreateTrackPlayer_original == NULL) {
                    if (notifyInvalid) {
                        MessageBoxW(NULL, L"Changing the playback speed is not supported in this version of Spotify client", L"CEF/Spotify Tweaks", MB_OK);
                    }
                    return;
                }
                if (newSpeed <= 0 || newSpeed > 5.0) {
                    if (notifyInvalid) {
                        MessageBoxW(NULL, L"Playback speed must be faster than 0 and less than or equal to 5.0", L"CEF/Spotify Tweaks", MB_OK);
                    }
                    return;
                }
                g_playbackSpeed = newSpeed;
                if (SetPlaybackSpeed != NULL && g_currentTrackPlayer != NULL) {
                    SetPlaybackSpeed(g_currentTrackPlayer, newSpeed);
                }
            #else
                if (notifyInvalid) {
                    MessageBoxW(NULL, L"Changing the playback speed requires a x86-64 version of Spotify", L"CEF/Spotify Tweaks", MB_OK);
                }
            #endif
        }
    } catch (const std::invalid_argument& e) {
        if (notifyInvalid) {
            MessageBoxW(NULL, L"Playback speed must be entered as a decimal number like 0.25, 1.0, or 1.5", L"CEF/Spotify Tweaks", MB_OK);
        }
    } catch (const std::out_of_range& e) {
        if (notifyInvalid) {
            MessageBoxW(NULL, L"Playback speed must be faster than 0 and less than or equal to 5.0", L"CEF/Spotify Tweaks", MB_OK);
        }
    }
}

int FindOffset(int major, int minor, cte_offset_t offsets[], int offsets_size, BOOL allow_untested = TRUE) {
    int prev_major = offsets[0].ver_major;
    for (int i = 0; i < offsets_size; i++) {
        if (major <= offsets[i].ver_major && major >= prev_major) {
            if (offsets[i].ver_minor == ANY_MINOR ||
                (minor == offsets[i].ver_minor && major == offsets[i].ver_major) // mandate exact major match here
            ) {
                #ifdef _WIN64
                    return offsets[i].offset_x64;
                #else
                    return offsets[i].offset_x86;
                #endif
            }
        }
        prev_major = offsets[i].ver_major;
    }
    if (allow_untested && major >= offsets[offsets_size - 1].ver_major) {
        #ifdef _WIN64
            return offsets[offsets_size - 1].offset_x64;
        #else
            return offsets[offsets_size - 1].offset_x86;
        #endif
    }
    return NULL;
}

// The mod is being initialized, load settings, hook functions, and do other
// initialization stuff if required.
BOOL Sec_ModInit() {
    #ifdef _M_X64
        Wh_Log(L"Init - x86_64");
    #elif defined(_M_ARM64)
        Wh_Log(L"Init - ARM64");
    #else
        Wh_Log(L"Init - x86");
    #endif

    LoadSettings();

    #ifdef _WIN64
        const size_t OFFSET_SAME_TEB_FLAGS = 0x17EE;
    #else
        const size_t OFFSET_SAME_TEB_FLAGS = 0x0FCA;
    #endif
    BOOL isInitialThread = *(USHORT*)((BYTE*)NtCurrentTeb() + OFFSET_SAME_TEB_FLAGS) & 0x0400;

    g_cefModule = LoadLibrary(L"libcef.dll");
    if (!g_cefModule) {
        Wh_Log(L"Failed to load CEF!");
        return FALSE;
    }

    // Check if the app is Spotify
    wchar_t exeName[MAX_PATH];
    GetModuleFileName(NULL, exeName, MAX_PATH);
    g_isSpotify = wcsstr(_wcsupr(exeName), L"SPOTIFY.EXE") != NULL;
    if (g_isSpotify) {
        Wh_Log(L"Spotify detected");
    }

    cef_version_info_t cef_version_info = (cef_version_info_t)GetProcAddress(g_cefModule, "cef_version_info");

    // Get CEF version
    int major = cef_version_info(0);
    int minor = cef_version_info(1);
    Wh_Log(L"CEF v%d.%d.%d.%d (Chromium v%d.%d.%d.%d) Loaded",
        major,
        minor,
        cef_version_info(2),
        cef_version_info(3),
        cef_version_info(4),
        cef_version_info(5),
        cef_version_info(6),
        cef_version_info(7)
    );

    if (major <= 89 || (major == 90 && minor <= 3)) {
        Wh_Log(L"Unsupported CEF version!");
        return FALSE;
    }

    BOOL isTestedVersion = cte_settings.allowuntested || major <= LAST_TESTED_CEF_VERSION;

    // Check if this process is auxilliary process by checking if the arguments contain --type=
    LPWSTR args = GetCommandLineW();
    if (wcsstr(args, L"--type=") != NULL) {
        if (g_isSpotify && isInitialThread &&
            major >= 108 && isTestedVersion && !NO_RENDERER_INJECTION &&
            wcsstr(args, L"--type=renderer") != NULL &&
            wcsstr(args, L"--extension-process") == NULL &&
            wcsstr(args, L"--top-chrome-webui") == NULL
        ) {
            return InitSpotifyRendererHooks(major);
        }
        Wh_Log(L"Auxilliary process detected, skipping.");
        return FALSE;
    }

    // Get appropriate offsets for current CEF version
    is_frameless_offset = FindOffset(major, minor, is_frameless_offsets, ARRAYSIZE(is_frameless_offsets));
    Wh_Log(L"is_frameless offset: %#x", is_frameless_offset);
    get_window_handle_offset = FindOffset(major, minor, get_window_handle_offsets, ARRAYSIZE(get_window_handle_offsets), cte_settings.allowuntested);
    Wh_Log(L"get_window_handle offset: %#x", get_window_handle_offset);
    if (g_isSpotify) {
        add_child_view_offset = FindOffset(major, minor, add_child_view_offsets, ARRAYSIZE(add_child_view_offsets));
        Wh_Log(L"add_child_view offset: %#x", add_child_view_offset);
        set_background_color_offset = FindOffset(major, minor, set_background_color_offsets, ARRAYSIZE(set_background_color_offsets));
        Wh_Log(L"set_background_color offset: %#x", set_background_color_offset);
    }

    cef_window_create_top_level_t cef_window_create_top_level = (cef_window_create_top_level_t)GetProcAddress(g_cefModule, "cef_window_create_top_level");
    cef_panel_create_t cef_panel_create = (cef_panel_create_t)GetProcAddress(g_cefModule, "cef_panel_create");
    cef_urlrequest_create_t cef_urlrequest_create = (cef_urlrequest_create_t)GetProcAddress(g_cefModule, "cef_urlrequest_create");

    WindhawkUtils::SetFunctionHook(cef_window_create_top_level, cef_window_create_top_level_hook, &cef_window_create_top_level_original);
    WindhawkUtils::SetFunctionHook(CreateWindowExW, CreateWindowExW_hook, &CreateWindowExW_original);
    if (g_isSpotify) {
        WindhawkUtils::SetFunctionHook(cef_panel_create, cef_panel_create_hook, &cef_panel_create_original);
        WindhawkUtils::SetFunctionHook(cef_urlrequest_create, cef_urlrequest_create_hook, &cef_urlrequest_create_original);
        WindhawkUtils::SetFunctionHook(SetWindowThemeAttribute, SetWindowThemeAttribute_hook, &SetWindowThemeAttribute_original);
        WindhawkUtils::SetFunctionHook(DwmExtendFrameIntoClientArea, DwmExtendFrameIntoClientArea_hook, &DwmExtendFrameIntoClientArea_original);
        WindhawkUtils::SetFunctionHook(SetWindowTextW, SetWindowTextW_hook, &SetWindowTextW_original);
        WindhawkUtils::SetFunctionHook(CreateProcessW, CreateProcessW_hook, &CreateProcessW_original);
        WindhawkUtils::SetFunctionHook(CreateProcessAsUserW, CreateProcessAsUserW_hook, &CreateProcessAsUserW_original);

        char* pbExecutable = NULL;
        // Spotify 1.2.70 (CEF 138) introduced a separate Spotify.dll which contains the core logic
        // All the existing patch matches exist in this DLL
        // Limit the Spotify.dll use only to 1.2.70 and above, as downgrading to older versions
        //   from 1.2.70 does not remove the redundant Spotify.dll in the installation directory
        if (major >= 138) {
            pbExecutable = (char*)LoadLibrary(L"Spotify.dll");
        }
        if (pbExecutable == NULL) {
            pbExecutable = (char*)GetModuleHandle(NULL);
        }

        int spMajor = 0;
        int spMinor = 0;
        int spBuild = 0;
        int spRevision = 0;
        HRSRC hRes = FindResourceW((HMODULE)pbExecutable, MAKEINTRESOURCE(1), RT_VERSION);
        if (hRes) {
            HGLOBAL hGlobal = LoadResource((HMODULE)pbExecutable, hRes);
            if (hGlobal) {
                LPVOID lpData = LockResource(hGlobal);
                if (lpData) {
                    UINT uLen = SizeofResource((HMODULE)pbExecutable, hRes);
                    if (uLen) {
                        VS_FIXEDFILEINFO* pFileInfo;
                        UINT uFileInfoLen;
                        if (VerQueryValueW(lpData, L"\\", (LPVOID*)&pFileInfo, &uFileInfoLen)) {
                            if (pFileInfo && pFileInfo->dwSignature == 0xfeef04bd) {
                                spMajor = HIWORD(pFileInfo->dwFileVersionMS);
                                spMinor = LOWORD(pFileInfo->dwFileVersionMS);
                                spBuild = HIWORD(pFileInfo->dwFileVersionLS);
                                spRevision = LOWORD(pFileInfo->dwFileVersionLS);
                            }
                        }
                    }
                }
            }
        }
        Wh_Log(L"Spotify version: %d.%d.%d.%d", spMajor, spMinor, spBuild, spRevision);

        // Patch the executable in memory to enable transparent rendering, disable forced dark mode, or force enable extensions
        // (Pointless if done after CEF initialization though)
        if (cte_settings.transparentrendering && major >= CR_RT_1ST_VERSION) {
            if (EnableTransparentRendering(pbExecutable)) {
                Wh_Log(L"Enabled transparent rendering");
            }
        }
        // Spotify 1.1.68+ (patch is not needed before that)
        if (cte_settings.noforceddarkmode && (major > 91 || (major == 91 && minor >= 3))) {
            if (DisableForcedDarkMode(pbExecutable, major)) {
                Wh_Log(L"Disabled forced dark mode");
            }
        }
        if (cte_settings.forceextensions && major >= CR_RT_1ST_VERSION) {
            if (ForceEnableExtensions(pbExecutable)) {
                Wh_Log(L"Enabled extensions");
            }
        }

        #ifdef _M_X64
        // Spotify 1.2.67+ hard blocked my way of changing the playback speed by calling the internal functions
        if (major >= 122 && major < 138 && isTestedVersion &&
            spMajor == 1 && spMinor == 2 && spBuild < 67
        ) {
            HookCreateTrackPlayer(pbExecutable, major >= 127);
            ApplySpeedFromSettings(FALSE);
        }
        #endif
    }

    EnumWindows(InitEnumWindowsProc, 1);
    return TRUE;
}

void Sec_ModBeforeUninit() {
    Wh_Log(L"BeforeUninit");
    
    g_shouldClosePipe.store(TRUE);

    if (g_stopEvent) {
        SetEvent(g_stopEvent);
    }

    if (g_pipeThread && g_pipeThread->joinable()) {
        g_pipeThread->join();
    }
    g_pipeThread.reset();

    if (g_stopEvent) {
        CloseHandle(g_stopEvent);
        g_stopEvent = NULL;
    }
}

// The mod is being unloaded, free all allocated resources.
void Sec_ModUninit() {
    Wh_Log(L"Uninit");

    if (g_isSpotifyRenderer) {
        // Note: sandboxed renderers won't even respond to the uninit request and keep loaded until the renderer exits
        // Unhook JS native functions
        // (JS API functions will now just do nothing because the cosmos handler doesn't handle them)
        for (auto& handler : cancelCosmosRequest_v8handlers) {
            handler->execute = cancelCosmosRequest_original;
            handler->base.release(&handler->base);
        }
        for (auto& handler : cancelEsperantoCall_v8handlers) {
            handler->execute = cancelEsperantoCall_original;
            handler->base.release(&handler->base);
        }
        for (auto& handler : _getSpotifyModule_v8handlers) {
            handler->execute = _getSpotifyModule_original;
            handler->base.release(&handler->base);
        }
        return;
    }

    EnumWindows(UninitEnumWindowsProc, 1);

    if (IsWindow(g_mainHwnd)) {
        // Restore the original set_background_color functions to prevent crashes
        // (Control colors hooks will no longer work till the app is restarted)
        for (int i = 0; i < 3; i++) {
            if (cte_controls[i].set_background_color_addr != NULL) {
                *((set_background_color_t*)cte_controls[i].set_background_color_addr) = cte_controls[i].set_background_color_original;
            }
        }
        // This too
        if (get_minimum_size_addr != NULL) {
            *get_minimum_size_addr = get_minimum_size_original;
        }
    }
}

// The mod setting were changed, reload them.
void Sec_ModSettingsChanged() {
    if (g_isSpotifyRenderer) {
        // Won't work in a sandboxed renderer process
        // Up-to-date settings will be fetched through this mod's custom IPC
        return;
    }
    BOOL prev_transparentcontrols = cte_settings.transparentcontrols;
    LoadSettings();
    ApplySpeedFromSettings(TRUE);
    EnumWindows(UpdateEnumWindowsProc, prev_transparentcontrols != cte_settings.transparentcontrols);
}
}  // namespace cef

// ==========================================================================
//  Basic frames (caption text colours)
// ==========================================================================
namespace basic {
#ifdef _WIN64
#   define SSTDCALL L"__cdecl"
#   define STHISCALL L"__cdecl"
#else
#   define SSTDCALL L"__stdcall"
#   define STHISCALL L"__thiscall"
#endif

bool g_bSmallIcons = true;

void LoadSettings() {
    g_bSmallIcons = Wh_GetIntSetting(L"basicFrames.smallIcons") != 0;
}

typedef int WINDOWPARTS, CLOSEBUTTONSTATES;

enum FRAMESTATES
{
    FS_ACTIVE = 0x1,
    FS_INACTIVE = 0x2
};

typedef struct _NCWNDMET
{
    BOOL fValid;
    BOOL fFrame;
    BOOL fSmallFrame;
    BOOL fMin;
    BOOL fMaxed;
    BOOL fFullMaxed;
    BOOL fDirtyRects;
    BOOL fCustomFrame;
    BOOL fCustom;
    DWORD dwStyle;
    DWORD dwExStyle;
    DWORD dwWindowStatus;
    DWORD dwStyleClass;
    WINDOWPARTS rgframeparts[4];
    WINDOWPARTS rgsizehitparts[4];
    FRAMESTATES framestate;
    HFONT hfCaption;
    COLORREF rgbCaption;
    SIZE sizeCaptionText;
    MARGINS CaptionMargins;
    int iMinButtonPart;
    int iMaxButtonPart;
    CLOSEBUTTONSTATES rawCloseBtnState;
    CLOSEBUTTONSTATES rawMinBtnState;
    CLOSEBUTTONSTATES rawMaxBtnState;
    CLOSEBUTTONSTATES rawHelpBtnState;
    int cyMenu;
    int cnMenuOffsetLeft;
    int cnMenuOffsetRight;
    int cnMenuOffsetTop;
    int cnBorders;
    RECT rcS0[26];
    RECT rcW0[26];
} NCWNDMET;

DWORD (__thiscall *_NCWNDMET__GetCaptionColor_orig)(NCWNDMET *, bool);
DWORD __thiscall _NCWNDMET__GetCaptionColor_hook(NCWNDMET *pThis, bool bDarkText)
{
    bool fInactive = (pThis->framestate == FS_INACTIVE);
    // When composition was active, Windows 7 always displayed active color on
    // ribbon.
    if (IsCompositionActive() && pThis->fCustomFrame)
        fInactive = false;
    return GetSysColor(
        fInactive ? COLOR_INACTIVECAPTIONTEXT : COLOR_CAPTIONTEXT
    );
}

/* Always use small icon */
typedef HICON (__fastcall *_GetWindowIcon_t)(HWND, BOOL);
_GetWindowIcon_t _GetWindowIcon_orig;
HICON __fastcall _GetWindowIcon_hook(HWND hWnd, BOOL bLarge)
{
    if (g_bSmallIcons)
        bLarge = FALSE;
    return _GetWindowIcon_orig(hWnd, bLarge);
}

const WindhawkUtils::SYMBOL_HOOK uxthemeDllHooks[] = { 
    {
        {
            L"public: unsigned long "
            STHISCALL
            L" _NCWNDMET::GetCaptionColor(bool)"
        },
        &_NCWNDMET__GetCaptionColor_orig,
        _NCWNDMET__GetCaptionColor_hook,
        false
    },
    {
        {
            L"struct HICON__ * "
            SSTDCALL
            L" _GetWindowIcon(struct HWND__ *,int)"
        },
        &_GetWindowIcon_orig,
        _GetWindowIcon_hook,
        false
    }
};

BOOL Sec_ModInit(void)
{
    LoadSettings();
    HMODULE hUxTheme = LoadLibraryW(L"uxtheme.dll");
    if (!hUxTheme)
    {
        Wh_Log(L"Failed to load uxtheme.dll");
        return FALSE;
    }

    if (!WindhawkUtils::HookSymbols(
        hUxTheme,
        uxthemeDllHooks,
        ARRAYSIZE(uxthemeDllHooks)
    ))
    {
        Wh_Log(L"Failed to hook one or more symbol functions in uxtheme.dll");
        return FALSE;
    }
    
    return TRUE;
}
}  // namespace basic

// ==========================================================================
//  Colours (Windows 11 Custom Title Bar Colours)
// ==========================================================================
namespace colours {

volatile LONG g_darkMode = 1;
volatile LONG g_active = RGB(0x1E, 0x1E, 0x2E);
volatile LONG g_inactive = RGB(0x1E, 0x1E, 0x2E);

// "#RRGGBB" or "RRGGBB" to a COLORREF; fallback when the text is not a colour.
COLORREF ParseHex(PCWSTR text, COLORREF fallback) {
    if (!text) return fallback;
    while (*text == L' ') text++;
    if (*text == L'#') text++;
    int v[6];
    for (int i = 0; i < 6; i++) {
        wchar_t c = text[i];
        if (c >= L'0' && c <= L'9') v[i] = c - L'0';
        else if (c >= L'a' && c <= L'f') v[i] = c - L'a' + 10;
        else if (c >= L'A' && c <= L'F') v[i] = c - L'A' + 10;
        else return fallback;
    }
    return RGB(v[0] * 16 + v[1], v[2] * 16 + v[3], v[4] * 16 + v[5]);
}

COLORREF ReadColour(PCWSTR name) {
    PCWSTR s = Wh_GetStringSetting(name);
    COLORREF c = ParseHex(s, RGB(0x1E, 0x1E, 0x2E));
    Wh_FreeStringSetting(s);
    return c;
}

void LoadSettings() {
    InterlockedExchange(&g_darkMode, Wh_GetIntSetting(L"colours.useImmersiveDarkMode") ? 1 : 0);
    InterlockedExchange(&g_active, (LONG)ReadColour(L"colours.activeColor"));
    InterlockedExchange(&g_inactive, (LONG)ReadColour(L"colours.inactiveColor"));
}

BOOL IsValidWindow(HWND hWnd) {
    // Better exclude context menus
    DWORD dwStyle = GetWindowLongPtr(hWnd, GWL_STYLE);
    return (dwStyle & WS_THICKFRAME) == WS_THICKFRAME || (dwStyle & WS_CAPTION) == WS_CAPTION;
}

void SetTitleBarColour(HWND hWnd, BOOL activate) {
    if (!IsValidWindow(hWnd)) {
        return;
    }
    BOOL useDarkMode = g_darkMode ? TRUE : FALSE;
    DwmSetWindowAttribute(hWnd, DWMWA_USE_IMMERSIVE_DARK_MODE, &useDarkMode, sizeof(useDarkMode));
    COLORREF caption = (COLORREF)(activate ? g_active : g_inactive);
    DwmSetWindowAttribute(hWnd, DWMWA_CAPTION_COLOR, &caption, sizeof(caption));
}

typedef LRESULT (WINAPI *WndProc_t)(HWND, UINT, WPARAM, LPARAM);

WndProc_t DefWindowProcA_orig;
LRESULT WINAPI DefWindowProcA_hook(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    LRESULT result = DefWindowProcA_orig(hWnd, uMsg, wParam, lParam);
    switch (uMsg) {
        case WM_ACTIVATE:
        case WM_NCACTIVATE:
            SetTitleBarColour(hWnd, (BOOL)wParam);
            break;
        case WM_DWMCOLORIZATIONCOLORCHANGED:
            SetTitleBarColour(hWnd, GetForegroundWindow() == hWnd);
            break;
    }
    return result;
}

WndProc_t DefWindowProcW_orig;
LRESULT WINAPI DefWindowProcW_hook(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    LRESULT result = DefWindowProcW_orig(hWnd, uMsg, wParam, lParam);
    switch (uMsg) {
        case WM_ACTIVATE:
        case WM_NCACTIVATE:
            SetTitleBarColour(hWnd, (BOOL)wParam);
            break;
        case WM_DWMCOLORIZATIONCOLORCHANGED:
            SetTitleBarColour(hWnd, GetForegroundWindow() == hWnd);
            break;
    }
    return result;
}

WndProc_t DefDlgProcA_orig;
LRESULT WINAPI DefDlgProcA_hook(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    LRESULT result = DefDlgProcA_orig(hWnd, uMsg, wParam, lParam);
    if (uMsg == WM_NCACTIVATE) SetTitleBarColour(hWnd, (BOOL)wParam);
    return result;
}

WndProc_t DefDlgProcW_orig;
LRESULT WINAPI DefDlgProcW_hook(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    LRESULT result = DefDlgProcW_orig(hWnd, uMsg, wParam, lParam);
    if (uMsg == WM_NCACTIVATE) SetTitleBarColour(hWnd, (BOOL)wParam);
    return result;
}

BOOL CALLBACK ApplyEnumProc(HWND hWnd, LPARAM lParam) {
    DWORD wPid = 0;
    GetWindowThreadProcessId(hWnd, &wPid);
    if ((DWORD)lParam == wPid) {
        SetTitleBarColour(hWnd, GetForegroundWindow() == hWnd);
    }
    return TRUE;
}

BOOL CALLBACK RestoreEnumProc(HWND hWnd, LPARAM lParam) {
    const COLORREF colorDefault = DWMWA_COLOR_DEFAULT;
    DWORD wPid = 0;
    GetWindowThreadProcessId(hWnd, &wPid);
    if ((DWORD)lParam == wPid && IsValidWindow(hWnd)) {
        DwmSetWindowAttribute(hWnd, DWMWA_CAPTION_COLOR, &colorDefault, sizeof(colorDefault));
    }
    return TRUE;
}

BOOL Sec_ModInit() {
    LoadSettings();
    HMODULE user32 = GetModuleHandleW(L"user32.dll");
    if (!user32) user32 = LoadLibraryW(L"user32.dll");
    if (!user32) return FALSE;
    struct { const char* name; void* hook; void** orig; } hooks[] = {
        {"DefWindowProcW", (void*)DefWindowProcW_hook, (void**)&DefWindowProcW_orig},
        {"DefWindowProcA", (void*)DefWindowProcA_hook, (void**)&DefWindowProcA_orig},
        {"DefDlgProcW", (void*)DefDlgProcW_hook, (void**)&DefDlgProcW_orig},
        {"DefDlgProcA", (void*)DefDlgProcA_hook, (void**)&DefDlgProcA_orig},
    };
    for (auto& h : hooks) {
        void* target = (void*)GetProcAddress(user32, h.name);
        if (!target || !Wh_SetFunctionHook(target, h.hook, h.orig)) {
            Wh_Log(L"Colours: hooking %S failed", h.name);
            return FALSE;
        }
    }
    return TRUE;
}

void Sec_ModAfterInit() {
    EnumWindows(ApplyEnumProc, GetCurrentProcessId());
}

void Sec_ModSettingsChanged() {
    LoadSettings();
    EnumWindows(ApplyEnumProc, GetCurrentProcessId());
}

void Sec_ModUninit() {
    EnumWindows(RestoreEnumProc, GetCurrentProcessId());
}

}  // namespace colours

// ==========================================================================
//  Terminal bar (runs in the Windhawk tool process)
// ==========================================================================
namespace term {
namespace {

constexpr wchar_t kMainClass[] = L"TerminalTitlebarBlurHost";
constexpr UINT kReloadMsg = WM_APP + 0x1B;
constexpr UINT_PTR kResyncTimer = 1;
constexpr DWORD kResyncMs = 500;

struct Config {
    BYTE r = 0x1E, g = 0x1E, b = 0x2E, a = 0xB2;
} g_cfg;

HINSTANCE g_instance;
HWND g_main;
HANDLE g_thread;
HANDLE g_ready;
std::set<HWND> g_touched;

typedef struct _ACCENT_POLICY {
    INT AccentState;
    INT AccentFlags;
    UINT GradientColor;
    INT AnimationId;
} ACCENT_POLICY;

typedef struct _WINDOWCOMPOSITIONATTRIBDATA {
    INT Attrib;
    PVOID pvData;
    SIZE_T cbData;
} WINDOWCOMPOSITIONATTRIBDATA;

typedef BOOL(WINAPI* PFN_SetWindowCompositionAttribute)(HWND, const WINDOWCOMPOSITIONATTRIBDATA*);

PFN_SetWindowCompositionAttribute GetSetWindowCompositionAttribute() {
    static PFN_SetWindowCompositionAttribute fn = []() {
        return (PFN_SetWindowCompositionAttribute)GetProcAddress(
            GetModuleHandleW(L"user32.dll"), "SetWindowCompositionAttribute");
    }();
    return fn;
}

int HexDigit(wchar_t c) {
    if (c >= L'0' && c <= L'9') return c - L'0';
    if (c >= L'a' && c <= L'f') return c - L'a' + 10;
    if (c >= L'A' && c <= L'F') return c - L'A' + 10;
    return -1;
}

void LoadConfig() {
    PCWSTR tint = Wh_GetStringSetting(L"terminalBar.tint", nullptr);
    BYTE r = 0x1E, g = 0x1E, b = 0x2E;
    if (tint) {
        const wchar_t* p = tint;
        if (*p == L'#') ++p;
        int vals[3] = {0, 0, 0};
        bool ok = true;
        for (int i = 0; i < 3; ++i) {
            int hi = HexDigit(*p++);
            int lo = HexDigit(*p++);
            if (hi < 0 || lo < 0) {
                ok = false;
                break;
            }
            vals[i] = hi * 16 + lo;
        }
        if (ok) {
            r = (BYTE)vals[0];
            g = (BYTE)vals[1];
            b = (BYTE)vals[2];
        }
        Wh_FreeStringSetting(tint);
    }
    int opacity = Wh_GetIntSetting(L"terminalBar.opacity", nullptr);
    if (opacity < 0) opacity = 0;
    if (opacity > 100) opacity = 100;
    g_cfg.r = r;
    g_cfg.g = g;
    g_cfg.b = b;
    g_cfg.a = (BYTE)(255 * opacity / 100);
}

bool IsTerminalWindow(HWND hwnd) {
    if (!IsWindowVisible(hwnd)) return false;
    if (GetWindowLongPtrW(hwnd, GWL_STYLE) & WS_CHILD) return false;
    wchar_t cls[64];
    if (!GetClassNameW(hwnd, cls, 64)) return false;
    return wcscmp(cls, L"CASCADIA_HOSTING_WINDOW_CLASS") == 0;
}

void ApplyRecipe(HWND hwnd) {
    // FreeDictate-proven order: frame sheet, blur-behind with an empty region
    // so the accent reaches the caption, then the tinted acrylic accent.
    MARGINS margins = {-1, -1, -1, -1};
    DwmExtendFrameIntoClientArea(hwnd, &margins);

    HRGN rgn = CreateRectRgn(0, 0, -1, -1);
    if (rgn) {
        DWM_BLURBEHIND bb = {};
        bb.dwFlags = DWM_BB_ENABLE | DWM_BB_BLURREGION | DWM_BB_TRANSITIONONMAXIMIZED;
        bb.fEnable = TRUE;
        bb.hRgnBlur = rgn;
        bb.fTransitionOnMaximized = TRUE;
        DwmEnableBlurBehindWindow(hwnd, &bb);
        DeleteObject(rgn);
    }

    ACCENT_POLICY accent = {};
    accent.AccentState = 4;  // ACCENT_ENABLE_ACRYLICBLURBEHIND
    accent.GradientColor = ((UINT)g_cfg.a << 24) | ((UINT)g_cfg.b << 16) | ((UINT)g_cfg.g << 8) | g_cfg.r;
    WINDOWCOMPOSITIONATTRIBDATA data = {};
    data.Attrib = 19;  // WCA_ACCENT_POLICY
    data.pvData = &accent;
    data.cbData = sizeof(accent);
    if (auto fn = GetSetWindowCompositionAttribute()) {
        fn(hwnd, &data);
    }
    g_touched.insert(hwnd);
}

void RevertWindow(HWND hwnd) {
    ACCENT_POLICY accent = {};
    accent.AccentState = 0;  // ACCENT_DISABLED
    WINDOWCOMPOSITIONATTRIBDATA data = {};
    data.Attrib = 19;
    data.pvData = &accent;
    data.cbData = sizeof(accent);
    if (auto fn = GetSetWindowCompositionAttribute()) {
        fn(hwnd, &data);
    }
    DWM_BLURBEHIND bb = {};
    bb.fEnable = FALSE;
    DwmEnableBlurBehindWindow(hwnd, &bb);
    MARGINS margins = {0, 0, 0, 0};
    DwmExtendFrameIntoClientArea(hwnd, &margins);
}

BOOL CALLBACK EnumProc(HWND hwnd, LPARAM) {
    if (IsTerminalWindow(hwnd)) {
        ApplyRecipe(hwnd);
    }
    return TRUE;
}

void ResyncAll() {
    EnumWindows(EnumProc, 0);
}

void CALLBACK WinEventProc(HWINEVENTHOOK, DWORD event, HWND hwnd, LONG idObject, LONG idChild,
                           DWORD, DWORD) {
    if (event == EVENT_SYSTEM_FOREGROUND) {
        ResyncAll();
        return;
    }
    if (event == EVENT_OBJECT_DESTROY) {
        if (hwnd && idObject == OBJID_WINDOW && idChild == CHILDID_SELF) {
            g_touched.erase(hwnd);
        }
        return;
    }
    if (hwnd && idObject == OBJID_WINDOW && idChild == CHILDID_SELF &&
        (event == EVENT_OBJECT_SHOW || event == EVENT_OBJECT_CREATE)) {
        if (IsTerminalWindow(hwnd)) {
            ApplyRecipe(hwnd);
        }
    }
}

LRESULT CALLBACK MainProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) {
    switch (msg) {
        case WM_TIMER:
            if (wp == kResyncTimer) {
                ResyncAll();
            }
            return 0;
        case kReloadMsg:
            LoadConfig();
            ResyncAll();
            return 0;
        case WM_CLOSE:
            for (HWND hwnd2 : g_touched) {
                if (IsWindow(hwnd2)) {
                    RevertWindow(hwnd2);
                }
            }
            g_touched.clear();
            DestroyWindow(hwnd);
            return 0;
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
    }
    return DefWindowProcW(hwnd, msg, wp, lp);
}

DWORD WINAPI HostThread(LPVOID) {
    SetThreadDpiAwarenessContext(DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2);
    LoadConfig();

    WNDCLASSEXW wc = {sizeof(wc)};
    wc.lpfnWndProc = MainProc;
    wc.hInstance = g_instance;
    wc.lpszClassName = kMainClass;
    RegisterClassExW(&wc);

    g_main = CreateWindowExW(0, kMainClass, L"", WS_POPUP, 0, 0, 0, 0, nullptr, nullptr,
                             g_instance, nullptr);
    SetEvent(g_ready);
    if (!g_main) {
        Wh_Log(L"CreateWindowExW failed: %u", GetLastError());
        return 1;
    }

    HWINEVENTHOOK hooks[4];
    hooks[0] = SetWinEventHook(EVENT_SYSTEM_FOREGROUND, EVENT_SYSTEM_FOREGROUND, nullptr,
                               WinEventProc, 0, 0, WINEVENT_OUTOFCONTEXT | WINEVENT_SKIPOWNPROCESS);
    hooks[1] = SetWinEventHook(EVENT_OBJECT_SHOW, EVENT_OBJECT_SHOW, nullptr, WinEventProc, 0, 0,
                               WINEVENT_OUTOFCONTEXT | WINEVENT_SKIPOWNPROCESS);
    hooks[2] = SetWinEventHook(EVENT_OBJECT_CREATE, EVENT_OBJECT_CREATE, nullptr, WinEventProc, 0, 0,
                               WINEVENT_OUTOFCONTEXT | WINEVENT_SKIPOWNPROCESS);
    hooks[3] = SetWinEventHook(EVENT_OBJECT_DESTROY, EVENT_OBJECT_DESTROY, nullptr, WinEventProc, 0, 0,
                               WINEVENT_OUTOFCONTEXT | WINEVENT_SKIPOWNPROCESS);

    SetTimer(g_main, kResyncTimer, kResyncMs, nullptr);
    ResyncAll();

    MSG msg;
    while (GetMessageW(&msg, nullptr, 0, 0) > 0) {
        TranslateMessage(&msg);
        DispatchMessageW(&msg);
    }

    KillTimer(g_main, kResyncTimer);
    for (HWINEVENTHOOK hook : hooks) {
        if (hook) {
            UnhookWinEvent(hook);
        }
    }
    return 0;
}

}  // namespace

// The host thread can stop and start again inside the same tool process when
// the section is turned off and on. The window class stays registered.
bool Start() {
    if (g_thread) return true;
    if (!g_instance &&
        !GetModuleHandleExW(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS |
                                GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT,
                            (LPCWSTR)&ApplyRecipe, &g_instance)) {
        return false;
    }
    g_main = nullptr;
    g_ready = CreateEventW(nullptr, TRUE, FALSE, nullptr);
    g_thread = CreateThread(nullptr, 0, HostThread, nullptr, 0, nullptr);
    if (!g_thread) {
        Wh_Log(L"Terminal bar: CreateThread failed: %u", GetLastError());
        CloseHandle(g_ready);
        g_ready = nullptr;
        return false;
    }
    WaitForSingleObject(g_ready, 5000);
    return g_main != nullptr;
}

void Reload() {
    if (g_main) {
        PostMessageW(g_main, kReloadMsg, 0, 0);
    }
}

void Stop() {
    if (g_main) {
        PostMessageW(g_main, WM_CLOSE, 0, 0);
    }
    if (g_thread) {
        WaitForSingleObject(g_thread, 5000);
        CloseHandle(g_thread);
        g_thread = nullptr;
    }
    if (g_ready) {
        CloseHandle(g_ready);
        g_ready = nullptr;
    }
    g_main = nullptr;
}
}  // namespace term


// ==========================================================================
//  Dispatcher: which sections run in this process
// ==========================================================================
// Each process runs only the sections meant for it, so two sections never
// hook the same function in one process:
//   dwm.exe                 caption buttons
//   explorer.exe            caption buttons (tab bar), colours, basic frames
//   ApplicationFrameHost    Store apps, colours, basic frames
//   spotify / cefclient     Spotify, colours, basic frames
//   apps in the list        native frames, colours, basic frames
//   everything else         colours, basic frames
//   windhawk.exe            starts the tool process for the Terminal bar
namespace dispatch {

enum : int {
    kColours = 1,
    kButtons = 2,
    kUwp = 4,
    kNative = 8,
    kCef = 16,
    kBasic = 32,
};

// A failed init in these may leave some hooks set, so the whole mod unloads
// from the process, as the original mods did. Basic frames is not strict: its
// symbols are missing on some Windows builds, and its two hooks are independent.
constexpr int kStrict = kColours | kButtons | kUwp;

int g_requested = 0;
int g_active = 0;
wchar_t g_exe[MAX_PATH] = L"";

bool IsExe(PCWSTR name) {
    return _wcsicmp(g_exe, name) == 0;
}

// Comma separated list of process names; * and ? work as wildcards.
bool MatchList(PCWSTR setting) {
    PCWSTR list = Wh_GetStringSetting(setting);
    bool hit = false;
    if (list) {
        wchar_t token[MAX_PATH];
        PCWSTR p = list;
        while (*p && !hit) {
            while (*p == L' ' || *p == L',' || *p == L';' || *p == L'|') p++;
            int n = 0;
            while (*p && *p != L',' && *p != L';' && *p != L'|') {
                if (n < MAX_PATH - 1) token[n++] = *p;
                p++;
            }
            while (n > 0 && token[n - 1] == L' ') n--;
            token[n] = 0;
            if (n > 0 && PathMatchSpecW(g_exe, token)) hit = true;
        }
    }
    Wh_FreeStringSetting(list);
    return hit;
}

bool On(PCWSTR setting) {
    return Wh_GetIntSetting(setting) != 0;
}

int Wanted() {
    static const PCWSTR kNever[] = {
        L"csrss.exe", L"smss.exe", L"wininit.exe", L"winlogon.exe",
        L"lsass.exe", L"services.exe", L"fontdrvhost.exe", L"LogonUI.exe",
        L"windhawk.exe", L"windhawk-mod.exe", L"windhawk-mod-uiaccess.exe",
    };
    for (PCWSTR n : kNever) {
        if (IsExe(n)) return 0;
    }
    if (IsExe(L"dwm.exe")) {
        return On(L"buttons.enabled") ? kButtons : 0;
    }

    int mask = 0;
    if (On(L"basicFrames.enabled")) mask |= kBasic;
    if (On(L"colours.enabled") && !MatchList(L"colours.excludedApps")) mask |= kColours;

    if (IsExe(L"explorer.exe")) {
        if (On(L"buttons.enabled")) mask |= kButtons;
    } else if (IsExe(L"ApplicationFrameHost.exe")) {
        if (On(L"uwp.enabled")) mask |= kUwp;
    } else if (IsExe(L"spotify.exe") || IsExe(L"cefclient.exe")) {
        if (On(L"spotify.enabled")) mask |= kCef;
    } else if (On(L"nativeFrames.enabled") && MatchList(L"nativeFrames.apps")) {
        mask |= kNative;
    }
    return mask;
}

void LoadExeName() {
    wchar_t path[MAX_PATH] = L"";
    GetModuleFileNameW(nullptr, path, MAX_PATH);
    PCWSTR name = wcsrchr(path, L'\\');
    name = name ? name + 1 : path;
    wcsncpy_s(g_exe, name, _TRUNCATE);
}

BOOL Init() {
    g_requested = Wanted();
    g_active = 0;
    struct { int bit; BOOL (*init)(); const wchar_t* name; } list[] = {
        {kBasic, basic::Sec_ModInit, L"basic frames"},
        {kColours, colours::Sec_ModInit, L"colours"},
        {kButtons, caption::Sec_ModInit, L"caption buttons"},
        {kUwp, uwp::Sec_ModInit, L"Store apps"},
        {kCef, cef::Sec_ModInit, L"Spotify"},
        {kNative, native::Sec_ModInit, L"native frames"},
    };
    for (auto& s : list) {
        if (!(g_requested & s.bit)) continue;
        if (s.init()) {
            g_active |= s.bit;
        } else {
            Wh_Log(L"%s: section did not start in %s", s.name, g_exe);
            if (s.bit & kStrict) return FALSE;
        }
    }
    Wh_Log(L"%s: requested %d, active %d", g_exe, g_requested, g_active);
    return TRUE;
}

void AfterInit() {
    if (g_active & kColours) colours::Sec_ModAfterInit();
    if (g_active & kButtons) caption::Sec_ModAfterInit();
}

void BeforeUninit() {
    if (g_active & kButtons) caption::Sec_ModBeforeUninit();
    if (g_active & kUwp) uwp::Sec_ModBeforeUninit();
    if (g_active & kCef) cef::Sec_ModBeforeUninit();
}

void Uninit() {
    if (g_active & kNative) native::Sec_ModUninit();
    if (g_active & kCef) cef::Sec_ModUninit();
    if (g_active & kUwp) uwp::Sec_ModUninit();
    if (g_active & kButtons) caption::Sec_ModUninit();
    if (g_active & kColours) colours::Sec_ModUninit();
    g_active = 0;
}

// Returns true when the process needs a full reload (a section turned on or off).
bool SettingsChanged() {
    if (Wanted() != g_requested) return true;
    if (g_active & kBasic) basic::LoadSettings();
    if (g_active & kColours) colours::Sec_ModSettingsChanged();
    if (g_active & kButtons) caption::Sec_ModSettingsChanged();
    if (g_active & kUwp) uwp::Sec_ModSettingsChanged();
    if (g_active & kCef) cef::Sec_ModSettingsChanged();
    if (g_active & kNative) native::Sec_ModSettingsChanged();
    return false;
}

}  // namespace dispatch

// ==========================================================================
//  Windhawk entry points
// ==========================================================================
// In windhawk.exe the mod only starts the tool process (Terminal bar). The
// tool process stays running and starts or stops the host when the setting
// changes.

BOOL WhToolLauncher_ModInit(BOOL* launch) {
    dispatch::LoadExeName();
    if (dispatch::IsExe(L"windhawk.exe")) {
        *launch = TRUE;
        return TRUE;
    }
    *launch = FALSE;
    return dispatch::Init();
}

void WhToolLauncher_ModAfterInit() {
    dispatch::AfterInit();
}

void WhToolLauncher_ModBeforeUninit() {
    dispatch::BeforeUninit();
}

void WhToolLauncher_ModUninit() {
    dispatch::Uninit();
}

void WhToolLauncher_ModSettingsChanged(BOOL* reload) {
    if (dispatch::IsExe(L"windhawk.exe")) {
        *reload = FALSE;
        return;
    }
    *reload = dispatch::SettingsChanged() ? TRUE : FALSE;
}

bool WhTool_ModInit() {
    if (Wh_GetIntSetting(L"terminalBar.enabled")) {
        term::Start();
    }
    return true;
}

void WhTool_ModSettingsChanged() {
    if (Wh_GetIntSetting(L"terminalBar.enabled")) {
        if (!term::Start()) return;
        term::Reload();
    } else {
        term::Stop();
    }
}

void WhTool_ModUninit() {
    term::Stop();
}

#include <windhawk_tool_mod.h>
