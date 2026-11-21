// ==WindhawkMod==
// @id              seamless-title-bars
// @name            Seamless Title Bars
// @description     One title bar look everywhere: colours, caption buttons, a glass title dock and native frames in every kind of app
// @version         1.3.11
// @author          DavidHiFi, Th3Fanbus, grn15RenS, Ingan121, Anixx, aubymori
// @homepage        https://github.com/DavidHiFi/davids-windhawk-mods
// @donateUrl       https://ko-fi.com/DavidHiFi
// @license         MIT
// @include         *
// @include         dwm.exe
// @include         windhawk.exe
// @architecture    x86-64
// @compilerOptions -lcomctl32 -luxtheme -lgdi32 -lshlwapi -ldwmapi -luser32 -lole32 -lshell32 -loleaut32 -lruntimeobject -lversion -ld2d1 -ldwrite -lwindowscodecs -luuid -lcomdlg32 -limm32 -ladvapi32 -Wl,--delayload=d2d1.dll -Wl,--delayload=dwrite.dll -Wl,--delayload=windowscodecs.dll -Wl,--delayload=comdlg32.dll -Wl,--delayload=imm32.dll -ldelayimp
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
- **Title dock.** A rounded glass box around the window icon and title, a
  dark Catppuccin Mocha tint with a soft shine over the blurred title bar.
  Turn the glass off for a solid fill. The
  grey edge turns into a blue to mauve gradient on hover and the fill brightens
  with it. Right-click it for a menu with the app name, copy title, copy all
  (title and uptime) and the usual window commands. Middle-click it to close
  the window.
- **Title font.** Any installed font and weight for title text (FiraCode
  Nerd Font Medium by default).
- **Settings window and tray icon.** Click the tray icon for a settings
  window with every option; right-click it for quick switches.
- **Window uptime.** After the title, a dot and how long that window has been
  open, counted per window. Pick days, hours, minutes and seconds.
- **Button exclusions.** Apps and window classes that keep the normal layout.
- **Per-app settings.** Rules that turn the dock or the uptime off for one
  app, or pin its title alignment left, center or right.
- **File Explorer tabs.** Keeps the tab bar from covering moved buttons.
- **Store apps.** A normal Windows title bar in Settings, Calculator, Photos
  and other Store apps, with an optional blur.
- **Native frames.** The standard title bar in Chromium browsers, Office,
  Visual Studio, Teams, Discord and similar apps.
- **Spotify.** Native frames and a set of Spotify tweaks.
- **Terminal bar.** Gives the Windows Terminal title bar the same blur as its
  window.
- **Basic frames.** Correct caption text colours on classic and basic frames.
- **System boxes.** The Windows "is not responding" box and system error
  boxes get a dark title and the system blur. Windows draws them from
  dwm.exe and csrss.exe, which no other mod can reach.

## Setup
- The caption buttons part runs inside dwm.exe. Windhawk loads it there
  because the mod names dwm.exe directly.
- The Terminal bar needs Terminal's own title bar (turn off "Show tabs in
  the title bar" in Terminal).

## Notes
- The title dock and uptime are drawn by DWM, so they show on every window
  with a standard Windows title bar. File Explorer draws its own title, so
  they do not show there.
- Uptime for windows that were already open when the mod loaded starts at
  the time their app started.
- Switching the button style back to Windows takes effect after dwm.exe
  restarts (sign out and back in).
- Spotify options marked with * need a Spotify restart.
- Changing the native frames app list needs those apps restarted.

## What's new in 1.3.11
- The title dock is frosted glass now: the blurred title bar shows through a
  dark Mocha base tint. "Glass fill" turns it off for a solid colour, and
  "Glass tint" sets how dark the glass is.
- The dock's fill colour defaults to Mocha base (#1E1E2E).

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
- titleFont:
  - family: "FiraCode Nerd Font"
    $name: Font
    $description: "Font name for title text, as Windows lists it. Empty = the Windows title font. Suggested: FiraCode Nerd Font."
  - weight: "500"
    $name: Font weight
    $description: "Suggested: Medium."
    $options:
    - default: Windows default
    - "300": Light
    - "400": Regular
    - "500": Medium
    - "600": Semibold
    - "700": Bold
  $name: Title font
  $description: The font and weight of title text in every title bar.
- titleDock:
  - enabled: true
    $name: Dock behind the icon and title
    $description: A rounded box around the window icon and title, styled like the taskbar docks.
  - paddingX: 8
    $name: Side padding (px)
    $description: "Space between the dock edge and the icon or text. 0 to 30 (Suggested: 8)."
  - paddingY: 4
    $name: Top and bottom padding (px)
    $description: "Gets smaller by itself in low title bars. 0 to 12 (Suggested: 4)."
  - radius: 8
    $name: Corner radius (px)
    $description: "0 to 20 (Suggested: 8)."
  - edgeWidth: 2
    $name: Edge thickness (px)
    $description: "Scales with the display. 1 to 4 (Suggested: 2)."
  - fillColor: "#1E1E2E"
    $name: Fill colour
    $description: "Hex colour. Suggested: #1E1E2E (Mocha base)."
  - glassFill: true
    $name: Glass fill
    $description: "On = frosted glass, the blurred title bar shows through the fill colour. Off = a solid fill at the opacity below."
  - glassTint: 60
    $name: Glass tint (%)
    $description: "How dark the glass is. 30 to 90 (Suggested: 60). Lower shows more blur."
  - fillOpacity: 100
    $name: Fill opacity (%)
    $description: "Used when Glass fill is off. 0 to 100 (Suggested: 100)."
  - glassShine: true
    $name: Glass shine
    $description: A soft light along the top half of the dock, like the taskbar docks.
  - edgeColor: "#45475A"
    $name: Edge colour
    $description: "Hex colour. Suggested: #45475A (Mocha surface 1)."
  - hover: true
    $name: Gradient edge on hover
    $description: The edge fades into a gradient while the pointer is over the dock.
  - hoverStart: "#89B4FA"
    $name: Hover gradient start
    $description: "Hex colour, top left. Suggested: #89B4FA (Mocha blue)."
  - hoverEnd: "#CBA6F7"
    $name: Hover gradient end
    $description: "Hex colour, bottom right. Suggested: #CBA6F7 (Mocha mauve)."
  - middleClickClose: true
    $name: Middle-click closes the window
    $description: Middle-click the dock to close the window.
  - hoverFill: true
    $name: Fill brightens on hover
    $description: On = the dock's fill brightens while the pointer is over it.
  - rightClickMenu: true
    $name: Right-click menu
    $description: "Right-click the dock for a menu: the app name, restore, minimize, maximize, always on top, copy title, copy all (title and uptime), the window menu, these settings and close."
  $name: Title dock
  $description: A dock around the icon and title of every standard title bar.
- uptime:
  - enabled: true
    $name: Show how long each window has been open
    $description: "Adds a dot and the window's uptime after the title, for example: Notepad • 1h 05m 12s."
  - showDays: true
    $name: Days
  - showHours: true
    $name: Hours
  - showMinutes: true
    $name: Minutes
  - showSeconds: true
    $name: Seconds
    $description: A unit that is off rolls into the next smaller one that is on, for example 50h instead of 2d 2h.
  - style: compact
    $name: Style
    $options:
    - compact: "Compact: 2d 03h 05m 12s"
    - clock: "Clock: 2d 3:05:12"
  - separator: "•"
    $name: Separator
    $description: "Text between the title and the uptime (Suggested: •). Empty = a space only."
  - color: "#A6ADC8"
    $name: Uptime colour
    $description: "Hex colour for the separator and uptime. Suggested: #A6ADC8 (Mocha subtext 0). Empty = same as the title."
  - dialogs: true
    $name: Also in dialogs
    $description: Turn off to hide uptime on windows with only a close button.
  $name: Window uptime
  $description: How long each window has been open, after its title.
- exclusions:
  - excludedApps: ""
    $name: Apps that keep normal buttons
    $description: "Process names separated by commas. Every window of these apps keeps the Windows button layout."
  - excludedClasses: "CabinetWClass"
    $name: Window classes that keep normal buttons
    $description: "Window class names separated by commas. CabinetWClass is File Explorer; remove it to move File Explorer's buttons too."
  $name: Button exclusions
  $description: Apps and windows that keep the normal button layout.
- perApp:
  - enabled: false
    $name: Turn on per-app settings
    $description: "Rules below override the dock, title alignment and uptime for matching apps."
  - list: ""
    $name: Rules
    $description: "Each rule: app.exe dock=off align=left uptime=off. Separate rules with a semicolon. The first matching rule wins; * matches any app; skip a part to keep the general setting."
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
- hungDialog:
  - enabled: true
    $name: Turn on system boxes
    $description: "Gives the Windows \"is not responding\" box and system error boxes a dark title and the system blur."
  $name: System boxes
  $description: Blur and a dark title for the boxes Windows draws itself, like "is not responding" and system errors.
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
- settingsGlass: true
  $name: Blurred settings window
  $description: "On, the settings window is see-through glass with Windows acrylic behind it. Off, it is solid. Applies when you save."
- nativeSettingsTitleBar: false
  $name: Native Windows title bar
  $description: "Use the Windows title bar and window buttons for this settings window. Applies when you save."
- settingsTrayIcon: true
  $name: Tray icon
  $description: "Click it to open these settings. Right-click it to turn the dock, uptime or buttons on or off. When off, change settings in Windhawk."
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
#include <d2d1_1.h>
#include <d3d11.h>
#include <dwrite.h>
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
#include <dwrite_3.h>
#include <d2d1helper.h>
#include <imm.h>
#include <shellapi.h>
#include <map>
#include <memory>
#include <random>
#include <cwctype>
#include <vssym32.h>

// ==========================================================================
//  Shared by dwm.exe and the tool process: which dock the pointer is on (for
//  the right-click menu) and a counter that says the title font file changed.
// ==========================================================================
namespace stbshared {
struct Block {
    volatile LONG seq;       // odd while the dock fields are being written
    volatile LONG fontSeq;   // bumped by the tool when titleFontFile changes
    ULONGLONG hwnd;          // window whose dock the pointer is on, or 0
    LONG dockL, dockR, band, pad;   // dock in window coordinates (x from the window's left edge, y 0..band)
    ULONGLONG tick;          // GetTickCount64 of the last write
    wchar_t suf[48];         // the hot window's uptime suffix (" \u2022 1h 05m 12s"), empty when none
};
static HANDLE g_map;
static Block* volatile g_blk;

static bool Open() {
    if (g_blk) return true;
    SECURITY_ATTRIBUTES sa = {sizeof(sa)};
    PSECURITY_DESCRIPTOR sd = nullptr;
    // Everyone and SYSTEM, any integrity level: dwm.exe (DWM-1) and the tool process both open it.
    if (ConvertStringSecurityDescriptorToSecurityDescriptorW(L"D:(A;;GA;;;WD)(A;;GA;;;SY)S:(ML;;NW;;;LW)",
                                                             SDDL_REVISION_1, &sd, nullptr))
        sa.lpSecurityDescriptor = sd;
    HANDLE m = CreateFileMappingW(INVALID_HANDLE_VALUE, &sa, PAGE_READWRITE, 0, 4096,
                                  L"Local\\SeamlessTitleBarsHotDock");
    if (sd) LocalFree(sd);
    if (!m) return false;
    void* v = MapViewOfFile(m, FILE_MAP_READ | FILE_MAP_WRITE, 0, 0, sizeof(Block));
    if (!v) {
        CloseHandle(m);
        return false;
    }
    g_map = m;
    g_blk = (Block*)v;
    return true;
}

static void Close() {
    Block* b = g_blk;
    g_blk = nullptr;
    if (b) UnmapViewOfFile(b);
    if (g_map) CloseHandle(g_map);
    g_map = nullptr;
}

static void Write(HWND h, LONG l, LONG r, LONG band, PCWSTR suf = nullptr) {
    Block* b = g_blk;
    if (!b) return;
    InterlockedIncrement(&b->seq);
    b->hwnd = (ULONGLONG)(ULONG_PTR)h;
    b->dockL = l;
    b->dockR = r;
    b->band = band;
    if (suf) wcsncpy_s(b->suf, suf, _TRUNCATE);
    else b->suf[0] = 0;
    b->tick = GetTickCount64();
    InterlockedIncrement(&b->seq);
}

// Refresh only the suffix of the hot window (uptime tick while the pointer rests on the dock).
static void WriteSuffix(HWND h, PCWSTR suf) {
    Block* b = g_blk;
    if (!b || (HWND)(ULONG_PTR)b->hwnd != h) return;
    InterlockedIncrement(&b->seq);
    b->suf[0] = 0;
    if (suf) wcsncpy_s(b->suf, suf, _TRUNCATE);
    InterlockedIncrement(&b->seq);
}

static HWND HotHwnd() {
    Block* b = g_blk;
    return b ? (HWND)(ULONG_PTR)b->hwnd : nullptr;
}

struct Snap {
    HWND hwnd;
    LONG l, r, band;
    ULONGLONG tick;
    wchar_t suf[48];
};

static bool Read(Snap& s) {
    Block* b = g_blk;
    if (!b) return false;
    for (int i = 0; i < 4; i++) {
        LONG a = b->seq;
        if (a & 1) {
            YieldProcessor();
            continue;
        }
        MemoryBarrier();
        s.hwnd = (HWND)(ULONG_PTR)b->hwnd;
        s.l = b->dockL;
        s.r = b->dockR;
        s.band = b->band;
        s.tick = b->tick;
        wcsncpy_s(s.suf, b->suf, _TRUNCATE);
        MemoryBarrier();
        if (b->seq == a) return true;
    }
    return false;
}

static LONG FontSeq() {
    Block* b = g_blk;
    return b ? b->fontSeq : 0;
}

static void BumpFont() {
    if (Block* b = g_blk) InterlockedIncrement(&b->fontSeq);
}

// The title font settings, read the same way in both processes.
struct FontPick {
    wchar_t family[LF_FACESIZE * 2];
    int weight;   // 100..950, or 0 to keep the Windows weight
    wchar_t key[LF_FACESIZE * 2 + 16];   // "family|weight": which pick titleFontFile was made for
};

static void ReadFontPick(FontPick& p) {
    p.family[0] = 0;
    p.weight = 0;
    PCWSTR fam = Wh_GetStringSetting(L"titleFont.family");
    if (fam) {
        const wchar_t* a = fam;
        while (*a == L' ' || *a == L'\t') a++;
        wcsncpy_s(p.family, a, _TRUNCATE);
        size_t n = wcslen(p.family);
        while (n && (p.family[n - 1] == L' ' || p.family[n - 1] == L'\t')) p.family[--n] = 0;
        Wh_FreeStringSetting(fam);
    }
    PCWSTR w = Wh_GetStringSetting(L"titleFont.weight");
    if (w) {
        int v = _wtoi(w);
        p.weight = (v >= 100 && v <= 950) ? v : 0;
        Wh_FreeStringSetting(w);
    }
    swprintf_s(p.key, L"%s|%d", p.family, p.weight);
}
}  // namespace stbshared


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
    // Title dock
    bool dockOn, dockHover, dockHoverFill, dockShine, dockMenu, dockGlass;
    int dockPadX, dockPadY, dockRadius, dockEdge, dockFillA, dockGlassA;
    DWORD dockFill, dockEdgeC, dockHov1, dockHov2;   // 0xRRGGBB
    // Window uptime
    bool upOn, upD, upH, upM, upS, upClock, upDialogs, upColorSet;
    DWORD upColor;
    wchar_t upSep[8];
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
// (centered/right title, the icon placed to the right of the title, or a
// per-app rule pinning an alignment). PappAnyAlign is defined further down.
static bool PappAnyAlign();
static bool TitleWidthMatters() {
    return g_settings.titleAlign != 0 || g_settings.dialogAlign >= 2 ||
           (g_settings.iconPosition == 0 && g_settings.iconSide == 1) ||
           PappAnyAlign();
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
static void LoadPerApp();

// Reads a "#RRGGBB" setting. Empty or invalid -> def; *set says whether a colour was given.
static DWORD ReadRgbSetting(const wchar_t* name, DWORD def, bool* set) {
    PCWSTR v = Wh_GetStringSetting(name);
    DWORD out = def;
    bool ok = false;
    if (v) {
        const wchar_t* p = v;
        while (*p == L' ') p++;
        if (*p == L'#') p++;
        DWORD c = 0;
        int n = 0;
        for (; *p && n < 6; p++, n++) {
            wchar_t ch = *p;
            int d = (ch >= L'0' && ch <= L'9') ? ch - L'0'
                  : (ch >= L'a' && ch <= L'f') ? ch - L'a' + 10
                  : (ch >= L'A' && ch <= L'F') ? ch - L'A' + 10 : -1;
            if (d < 0) break;
            c = (c << 4) | (DWORD)d;
        }
        if (n == 6) { out = c; ok = true; }
    }
    Wh_FreeStringSetting(v);
    if (set) *set = ok;
    return out;
}

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

    g_settings.dockOn = Wh_GetIntSetting(L"titleDock.enabled") != 0;
    g_settings.dockHover = Wh_GetIntSetting(L"titleDock.hover") != 0;
    g_settings.dockShine = Wh_GetIntSetting(L"titleDock.glassShine") != 0;
    g_settings.dockMenu = Wh_GetIntSetting(L"titleDock.rightClickMenu") != 0;
    g_settings.dockHoverFill = Wh_GetIntSetting(L"titleDock.hoverFill") != 0;
    g_settings.dockPadX = Clamp(Wh_GetIntSetting(L"titleDock.paddingX"), 0, 30);
    g_settings.dockPadY = Clamp(Wh_GetIntSetting(L"titleDock.paddingY"), 0, 12);
    g_settings.dockRadius = Clamp(Wh_GetIntSetting(L"titleDock.radius"), 0, 20);
    g_settings.dockEdge = Clamp(Wh_GetIntSetting(L"titleDock.edgeWidth"), 1, 4);
    g_settings.dockFillA = Clamp(Wh_GetIntSetting(L"titleDock.fillOpacity"), 0, 100);
    g_settings.dockGlass = Wh_GetIntSetting(L"titleDock.glassFill") != 0;
    g_settings.dockGlassA = Clamp(Wh_GetIntSetting(L"titleDock.glassTint"), 30, 90);
    g_settings.dockFill = ReadRgbSetting(L"titleDock.fillColor", 0x1E1E2E, nullptr);
    g_settings.dockEdgeC = ReadRgbSetting(L"titleDock.edgeColor", 0x45475A, nullptr);
    g_settings.dockHov1 = ReadRgbSetting(L"titleDock.hoverStart", 0x89B4FA, nullptr);
    g_settings.dockHov2 = ReadRgbSetting(L"titleDock.hoverEnd", 0xCBA6F7, nullptr);

    g_settings.upOn = Wh_GetIntSetting(L"uptime.enabled") != 0;
    g_settings.upD = Wh_GetIntSetting(L"uptime.showDays") != 0;
    g_settings.upH = Wh_GetIntSetting(L"uptime.showHours") != 0;
    g_settings.upM = Wh_GetIntSetting(L"uptime.showMinutes") != 0;
    g_settings.upS = Wh_GetIntSetting(L"uptime.showSeconds") != 0;
    if (!g_settings.upD && !g_settings.upH && !g_settings.upM && !g_settings.upS) g_settings.upM = true;
    {
        PCWSTR st = Wh_GetStringSetting(L"uptime.style");
        g_settings.upClock = st && wcscmp(st, L"clock") == 0;
        Wh_FreeStringSetting(st);
        PCWSTR sep = Wh_GetStringSetting(L"uptime.separator");
        wcsncpy(g_settings.upSep, sep ? sep : L"", 7);
        g_settings.upSep[7] = 0;
        Wh_FreeStringSetting(sep);
    }
    g_settings.upDialogs = Wh_GetIntSetting(L"uptime.dialogs") != 0;
    bool colorSet = false;
    g_settings.upColor = ReadRgbSetting(L"uptime.color", 0xA6ADC8, &colorSet);
    g_settings.upColorSet = colorSet;

    LoadExclusions();
    LoadPerApp();
}

// ---------------- logging ----------------
static int g_logCount = 0;
static int g_hitLogCount = 0;
static wchar_t g_lastLog[800] = L"";
static wchar_t g_lastHitLog[300] = L"";

// The debug log also goes to mod storage ("debugRing"), newest at the end, so it can be
// read without an OutputDebugString listener. DWM only, and only with the debug log on.
static SRWLOCK g_ringLock = SRWLOCK_INIT;
static wchar_t g_ring[12000];
static size_t g_ringLen = 0;
static int g_ringInDwm = -1;

static void RingAppend(const wchar_t* line) {
    if (wcsncmp(line, L"[IconChk]", 9) == 0 || wcsncmp(line, L"[IconHit]", 9) == 0 ||
        wcsncmp(line, L"[HitRaw]", 8) == 0)
        return;
    if (g_ringInDwm < 0) g_ringInDwm = GetModuleHandleW(L"udwm.dll") ? 1 : 0;
    if (!g_ringInDwm) return;
    wchar_t head[40];
    swprintf(head, 40, L"%llu t%lu ", (unsigned long long)(GetTickCount64() % 100000000ull), GetCurrentThreadId());
    size_t hn = wcslen(head);
    size_t n = wcsnlen(line, 700);
    const size_t cap = sizeof(g_ring) / sizeof(g_ring[0]);
    AcquireSRWLockExclusive(&g_ringLock);
    if (g_ringLen + hn + n + 2 >= cap) {
        // Drop the oldest half, at a line start.
        size_t cut = g_ringLen / 2;
        while (cut < g_ringLen && g_ring[cut] != L'\n') cut++;
        if (cut < g_ringLen) cut++;
        wmemmove(g_ring, g_ring + cut, g_ringLen - cut);
        g_ringLen -= cut;
    }
    if (g_ringLen + hn + n + 2 < cap) {
        wmemcpy(g_ring + g_ringLen, head, hn); g_ringLen += hn;
        wmemcpy(g_ring + g_ringLen, line, n); g_ringLen += n;
        g_ring[g_ringLen++] = L'\n';
        g_ring[g_ringLen] = 0;
        Wh_SetStringValue(L"debugRing", g_ring);
    }
    ReleaseSRWLockExclusive(&g_ringLock);
}

static void WriteLogLine(const wchar_t* line) {
    Wh_Log(L"%s", line);
    RingAppend(line);
}

// Status lines of the dock: always to the log, and to the ring while the debug log is on.
#define DockLog(...) do { \
        Wh_Log(__VA_ARGS__); \
        if (g_settings.debugLog) { \
            wchar_t dockLogBuf_[800]; \
            _snwprintf(dockLogBuf_, 799, __VA_ARGS__); \
            dockLogBuf_[799] = 0; \
            RingAppend(dockLogBuf_); \
        } \
    } while (0)

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

// ---------------- per-app overrides ----------------
// Rules from perApp.list, separated by ; or new lines:
// "notepad.exe dock=off align=left uptime=off". The first matching rule wins;
// "*" matches every app. dock=on keeps the general setting (the master switch
// still decides); align is 0 left, 1 center, 2 right; -1 = keep the general setting.
struct PerAppRule { wchar_t exe[128]; int dock, align, uptime; };
static SRWLOCK g_paLock = SRWLOCK_INIT;
static PerAppRule g_paRules[32];
static int g_paRulesN = 0;
static bool g_paOn = true;
static std::wstring g_paListRaw;          // raw list text, hashed by LayoutSignature
static volatile LONG g_paAnyUpOn = 0;     // a rule forces uptime on: the uptime timer must run
static volatile LONG g_paAnyAlign = 0;    // a rule pins an alignment: title width matters

// Per-HWND resolve cache, same shape as the exclusion cache
struct PaCache { HWND hwnd; DWORD pid; int dock, align, uptime; bool done; };
static PaCache g_paCache[128];
static int g_paCacheNext = 0;

static void LoadPerApp() {
    PCWSTR raw = Wh_GetStringSetting(L"perApp.list");
    bool on = Wh_GetIntSetting(L"perApp.enabled") != 0;
    AcquireSRWLockExclusive(&g_paLock);
    g_paOn = on;
    g_paRulesN = 0;
    g_paListRaw = raw ? raw : L"";
    g_paAnyUpOn = 0;
    g_paAnyAlign = 0;
    memset(g_paCache, 0, sizeof(g_paCache));
    g_paCacheNext = 0;
    if (raw) {
        const wchar_t* p = raw;
        while (*p && g_paRulesN < 32) {
            while (*p == L'\n' || *p == L'\r' || *p == L';' || *p == L' ' || *p == L'\t') p++;
            if (!*p) break;
            const wchar_t* eol = p;
            while (*eol && *eol != L'\n' && *eol != L'\r' && *eol != L';') eol++;
            const wchar_t* en = eol;
            while (en > p && (en[-1] == L' ' || en[-1] == L'\t')) en--;
            if (en > p) {
                PerAppRule& r = g_paRules[g_paRulesN];
                int n = (int)(en - p);
                if (n > 120) n = 120;
                memcpy(r.exe, p, (size_t)n * sizeof(wchar_t));
                r.exe[n] = 0;
                r.dock = r.align = r.uptime = -1;
                { wchar_t* sp = wcspbrk(r.exe, L" \t"); if (sp) *sp = 0; }  // r.exe keeps only the app token
                bool wildcard = wcscmp(r.exe, L"*") == 0;
                if (!wildcard) {
                    wchar_t* b = wcsrchr(r.exe, L'\\');
                    if (b) memmove(r.exe, b + 1, (wcslen(b + 1) + 1) * sizeof(wchar_t));
                    if (!wcschr(r.exe, L'.')) wcscat_s(r.exe, L".exe");
                }
                const wchar_t* q = p;
                while (q < en && *q != L' ' && *q != L'\t') q++;
                while (q < en) {
                    while (q < en && (*q == L' ' || *q == L'\t')) q++;
                    const wchar_t* ks = q;
                    while (q < en && *q != L' ' && *q != L'\t') q++;
                    size_t klen = (size_t)(q - ks);
                    auto part = [&](PCWSTR key) -> PCWSTR {
                        size_t kl = wcslen(key);
                        if (klen > kl + 1 && _wcsnicmp(ks, key, kl) == 0 && ks[kl] == L'=') return ks + kl + 1;
                        return nullptr;
                    };
                    if (const wchar_t* v = part(L"dock")) {
                        size_t vl = klen - 5;
                        r.dock = (vl == 2 && _wcsnicmp(v, L"on", 2) == 0) ? 1
                               : (vl == 3 && _wcsnicmp(v, L"off", 3) == 0) ? 0 : -1;
                    } else if (const wchar_t* v = part(L"align")) {
                        size_t vl = klen - 6;
                        r.align = (vl == 4 && _wcsnicmp(v, L"left", 4) == 0) ? 0
                                : (vl == 6 && _wcsnicmp(v, L"center", 6) == 0) ? 1
                                : (vl == 5 && _wcsnicmp(v, L"right", 5) == 0) ? 2 : -1;
                    } else if (const wchar_t* v = part(L"uptime")) {
                        size_t vl = klen - 7;
                        r.uptime = (vl == 2 && _wcsnicmp(v, L"on", 2) == 0) ? 1
                                 : (vl == 3 && _wcsnicmp(v, L"off", 3) == 0) ? 0 : -1;
                    }
                }
                if (r.align >= 0) g_paAnyAlign = 1;
                if (r.uptime == 1) g_paAnyUpOn = 1;
                g_paRulesN++;
            }
            p = eol;
        }
    }
    Wh_FreeStringSetting(raw);
    ReleaseSRWLockExclusive(&g_paLock);
    DebugLog(L"[PerApp] on=%d rules=%d align=%d upOn=%d", on ? 1 : 0, g_paRulesN,
             (int)g_paAnyAlign, (int)g_paAnyUpOn);
}

// Overrides for a window's app: dock off, pinned alignment, uptime on/off.
// Cached per hwnd (pid checked too, so a reused handle is not misjudged).
static void ResolvePerApp(HWND hwnd, int& dock, int& align, int& uptime) {
    dock = align = uptime = -1;
    if (!hwnd) return;
    AcquireSRWLockShared(&g_paLock);
    bool on = g_paOn;
    int n = g_paRulesN;
    ReleaseSRWLockShared(&g_paLock);
    if (!on || !n) return;
    DWORD pid = 0;
    GetWindowThreadProcessId(hwnd, &pid);
    AcquireSRWLockShared(&g_paLock);
    for (int i = 0; i < 128; i++) {
        if (g_paCache[i].done && g_paCache[i].hwnd == hwnd && g_paCache[i].pid == pid) {
            dock = g_paCache[i].dock;
            align = g_paCache[i].align;
            uptime = g_paCache[i].uptime;
            ReleaseSRWLockShared(&g_paLock);
            return;
        }
    }
    ReleaseSRWLockShared(&g_paLock);

    wchar_t exe[128] = L"";
    if (pid) GetExeNameForPid(pid, exe, 128);
    AcquireSRWLockShared(&g_paLock);
    int d = -1, a = -1, u = -1;
    for (int i = 0; i < g_paRulesN; i++) {
        const PerAppRule& r = g_paRules[i];
        bool match = r.exe[0] == L'*' && r.exe[1] == 0;
        if (!match) match = exe[0] && _wcsicmp(r.exe, exe) == 0;
        if (match) {
            d = r.dock; a = r.align; u = r.uptime;
            break;
        }
    }
    ReleaseSRWLockShared(&g_paLock);

    AcquireSRWLockExclusive(&g_paLock);
    g_paCache[g_paCacheNext] = {hwnd, pid, d, a, u, true};
    g_paCacheNext = (g_paCacheNext + 1) % 128;
    ReleaseSRWLockExclusive(&g_paLock);
    dock = d; align = a; uptime = u;
}

static bool PappAnyAlign() { return g_paAnyAlign != 0; }
static bool PappAnyUpOn() { return g_paAnyUpOn != 0; }

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

// ---------------- title dock and window uptime: shared state ----------------
static ULONGLONG NowFt() {
    FILETIME f;
    GetSystemTimeAsFileTime(&f);
    return ((ULONGLONG)f.dwHighDateTime << 32) | f.dwLowDateTime;
}

// When each window was first seen (FILETIME). Kept across mod reloads in the mod storage.
struct BornEntry { ULONGLONG t; DWORD pid; };
static std::unordered_map<HWND, BornEntry> g_born;
static SRWLOCK g_titleLock = SRWLOCK_INIT;   // g_born, g_titles, g_textToWin
static ULONGLONG g_initTick = 0;
static ULONGLONG g_initFt = 0;

// Start time of a process; 0 for File Explorer (it hosts windows for days) and on failure.
static ULONGLONG ProcessStartFt(DWORD pid) {
    HANDLE h = OpenProcess(PROCESS_QUERY_LIMITED_INFORMATION, FALSE, pid);
    if (!h) return 0;
    ULONGLONG r = 0;
    wchar_t path[MAX_PATH];
    DWORD len = MAX_PATH;
    bool shell = false;
    if (QueryFullProcessImageNameW(h, 0, path, &len)) {
        const wchar_t* exe = wcsrchr(path, L'\\');
        shell = _wcsicmp(exe ? exe + 1 : path, L"explorer.exe") == 0;
    }
    FILETIME ct, et, kt, ut;
    if (!shell && GetProcessTimes(h, &ct, &et, &kt, &ut))
        r = ((ULONGLONG)ct.dwHighDateTime << 32) | ct.dwLowDateTime;
    CloseHandle(h);
    return r;
}

// Caller holds g_titleLock exclusive.
static ULONGLONG BornLocked(HWND hwnd) {
    DWORD pid = 0;
    GetWindowThreadProcessId(hwnd, &pid);
    auto it = g_born.find(hwnd);
    if (it != g_born.end() && it->second.pid == pid) return it->second.t;
    ULONGLONG t = NowFt();
    if (GetTickCount64() - g_initTick < 5000) {
        // Already open when the mod loaded: the best guess is when its app started.
        ULONGLONG ps = (pid == GetCurrentProcessId()) ? 0 : ProcessStartFt(pid);
        t = (ps && ps <= t) ? ps : g_initFt;
    }
    g_born[hwnd] = BornEntry{t, pid};
    return t;
}

// "2d 03h 05m 12s" or "2d 3:05:12". A unit that is off rolls into the next smaller one.
static void FormatUptime(ULONGLONG secs, wchar_t* out, size_t cap) {
    static const ULONGLONG kUnit[4] = {86400, 3600, 60, 1};
    static const wchar_t kName[4] = {L'd', L'h', L'm', L's'};
    bool on[4] = {g_settings.upD, g_settings.upH, g_settings.upM, g_settings.upS};
    int smallest = 3;
    while (smallest > 0 && !on[smallest]) smallest--;
    if (!on[smallest]) { on[2] = true; smallest = 2; }
    ULONGLONG val[4] = {};
    ULONGLONG rem = secs;
    for (int i = 0; i < 4; i++) {
        if (on[i]) { val[i] = rem / kUnit[i]; rem %= kUnit[i]; }
    }
    int first = smallest;
    for (int i = 0; i <= smallest; i++) {
        if (on[i] && val[i]) { first = i; break; }
    }
    size_t n = 0;
    out[0] = 0;
    if (!g_settings.upClock) {
        for (int i = first; i <= smallest && n < cap; i++) {
            if (!on[i]) continue;
            n += swprintf(out + n, cap - n, (i == first) ? L"%s%llu%lc" : L"%s%02llu%lc",
                          n ? L" " : L"", val[i], kName[i]);
        }
        return;
    }
    int i = first;
    if (i == 0) { n += swprintf(out, cap, L"%llud", val[0]); i = 1; }
    int clockUnits = 0, lastUnit = -1;
    for (; i <= smallest && n < cap; i++) {
        if (!on[i]) continue;
        n += swprintf(out + n, cap - n, clockUnits ? L":%02llu" : (n ? L" %llu" : L"%llu"), val[i]);
        clockUnits++;
        lastUnit = i;
    }
    // A single clock number needs its letter, or "5" would not say minutes or seconds.
    if (clockUnits == 1 && n < cap) swprintf(out + n, cap - n, L"%lc", kName[lastUnit]);
}

// " • 1h 05m 12s" for a window. Caller holds g_titleLock exclusive.
static void UptimeSuffixLocked(HWND hwnd, wchar_t* out, size_t cap) {
    ULONGLONG born = BornLocked(hwnd);
    ULONGLONG now = NowFt();
    ULONGLONG secs = now > born ? (now - born) / 10000000ull : 0;
    wchar_t t[48];
    FormatUptime(secs, t, 48);
    if (g_settings.upSep[0]) swprintf(out, cap, L" %s %s", g_settings.upSep, t);
    else swprintf(out, cap, L" %s", t);
}

static bool UptimeApplies(bool closeOnly, int upOvr = -1) {
    // upOvr: per-app rule for this window. -1 keep the general setting, 0 off, 1 on.
    if (upOvr == 0) return false;
    if (upOvr == 1) return !g_settings.hideTitle && !g_unloading && (!closeOnly || g_settings.upDialogs);
    return g_settings.upOn && !g_settings.hideTitle && !g_unloading &&
           (!closeOnly || g_settings.upDialogs);
}

static void RequestDwmRefresh();
// ---------------- title font (Settings > Title font) ----------------
// DWM makes each title's text format in CDWriteText::CreateTextFormat, which calls
// IDWriteFactory::CreateTextFormat. While a title is inside that call, the factory hook swaps in
// the chosen family and weight. A per-user font (FiraCode installs per user) is not in DWM's font
// list, so the tool process copies the font file to the mod storage and DWM loads it from there.
namespace tfont {
typedef HRESULT (WINAPI *DWriteCreateFactory_t)(DWRITE_FACTORY_TYPE, REFIID, IUnknown**);
typedef HRESULT (STDMETHODCALLTYPE *CreateTextFormat_t)(IDWriteFactory*, const WCHAR*, IDWriteFontCollection*,
                                                        DWRITE_FONT_WEIGHT, DWRITE_FONT_STYLE, DWRITE_FONT_STRETCH,
                                                        FLOAT, const WCHAR*, IDWriteTextFormat**);
typedef long (*TextFn_t)(void*);

static CreateTextFormat_t CreateTextFormat_Orig;
static TextFn_t TextCreateFormat_Orig;    // CDWriteText::CreateTextFormat
static TextFn_t TextCreateLayout_Orig;    // CDWriteText::CreateTextLayout
static void* g_textLayoutAddr;

static SRWLOCK g_lock = SRWLOCK_INIT;
static volatile bool g_on;                // a family or a weight is set
static wchar_t g_family[LF_FACESIZE * 2];
static wchar_t g_file[MAX_PATH];
static int g_weight;
static volatile LONG g_gen = 1;           // bumped when the font changes: titles make a new text format

struct Res {
    IDWriteFactory* f;
    IDWriteFontCollection* coll;   // null: the system collection
    wchar_t family[LF_FACESIZE * 2];
    bool ok;
};
static std::vector<Res> g_cache;          // per factory
static IDWriteFactory* g_measureF;
static thread_local int t_inTitle;

static SRWLOCK g_genLock = SRWLOCK_INIT;
static std::unordered_map<void*, LONG> g_textGen;   // CDWriteText* -> g_gen its format was made with
static bool g_layoutForceOk;              // CreateTextLayout looks as expected: its font cache may be reset
static volatile LONG g_logs;
static LONG g_seenSeq;
static ULONGLONG g_lastOpenTry;

static void ClearCacheLocked() {
    for (auto& r : g_cache) {
        if (r.coll) r.coll->Release();
        if (r.f) r.f->Release();
    }
    g_cache.clear();
}

// Reads the settings. True when the font changed.
static bool Load() {
    stbshared::FontPick p;
    stbshared::ReadFontPick(p);
    wchar_t file[MAX_PATH] = L"", forKey[LF_FACESIZE * 2 + 16] = L"";
    Wh_GetStringValue(L"titleFontFile", file, MAX_PATH);
    Wh_GetStringValue(L"titleFontFor", forKey, ARRAYSIZE(forKey));
    if (wcscmp(forKey, p.key) != 0) file[0] = 0;   // made for another pick: wait for the tool
    if (file[0] && GetFileAttributesW(file) == INVALID_FILE_ATTRIBUTES) file[0] = 0;
    AcquireSRWLockExclusive(&g_lock);
    bool changed = wcscmp(g_family, p.family) != 0 || wcscmp(g_file, file) != 0 || g_weight != p.weight;
    wcscpy_s(g_family, p.family);
    wcscpy_s(g_file, file);
    g_weight = p.weight;
    g_on = p.family[0] != 0 || p.weight != 0;
    if (changed) {
        ClearCacheLocked();
        InterlockedIncrement(&g_gen);
    }
    ReleaseSRWLockExclusive(&g_lock);
    if (changed)
        Wh_Log(L"[Font] title font \"%s\" weight %d%s%s", p.family[0] ? p.family : L"(Windows)", p.weight,
               file[0] ? L" from " : L"", file);
    return changed;
}

// The font file as a one-file collection; its family name comes from the file itself.
static void LoadFile(IDWriteFactory* f, const wchar_t* file, Res& r) {
    IDWriteFactory5* f5 = nullptr;
    if (FAILED(f->QueryInterface(__uuidof(IDWriteFactory5), (void**)&f5)) || !f5) return;
    IDWriteFontSetBuilder1* b = nullptr;
    IDWriteFontFile* ff = nullptr;
    IDWriteFontSet* set = nullptr;
    IDWriteFontCollection1* c = nullptr;
    if (SUCCEEDED(f5->CreateFontSetBuilder(&b)) && b && SUCCEEDED(f5->CreateFontFileReference(file, nullptr, &ff)) &&
        ff && SUCCEEDED(b->AddFontFile(ff)) && SUCCEEDED(b->CreateFontSet(&set)) && set &&
        SUCCEEDED(f5->CreateFontCollectionFromFontSet(set, &c)) && c && c->GetFontFamilyCount() > 0) {
        IDWriteFontFamily1* fam = nullptr;
        IDWriteLocalizedStrings* names = nullptr;
        if (SUCCEEDED(c->GetFontFamily(0, &fam)) && fam && SUCCEEDED(fam->GetFamilyNames(&names)) && names) {
            UINT32 i = 0, len = 0;
            BOOL ex = FALSE;
            if (FAILED(names->FindLocaleName(L"en-us", &i, &ex)) || !ex) i = 0;
            if (SUCCEEDED(names->GetStringLength(i, &len)) && len < ARRAYSIZE(r.family) &&
                SUCCEEDED(names->GetString(i, r.family, ARRAYSIZE(r.family)))) {
                r.ok = true;
                r.coll = c;
                c = nullptr;
            }
        }
        if (names) names->Release();
        if (fam) fam->Release();
    }
    if (c) c->Release();
    if (set) set->Release();
    if (ff) ff->Release();
    if (b) b->Release();
    f5->Release();
}

// The family name and collection to use with factory f. False: the family is not available.
static bool Resolve(IDWriteFactory* f, wchar_t* name, size_t cch, IDWriteFontCollection** coll) {
    *coll = nullptr;
    wchar_t fam[LF_FACESIZE * 2], file[MAX_PATH];
    AcquireSRWLockShared(&g_lock);
    for (auto& r : g_cache) {
        if (r.f != f) continue;
        bool ok = r.ok;
        if (ok) {
            wcscpy_s(name, cch, r.family);
            *coll = r.coll;
            if (r.coll) r.coll->AddRef();
        }
        ReleaseSRWLockShared(&g_lock);
        return ok;
    }
    wcscpy_s(fam, g_family);
    wcscpy_s(file, g_file);
    LONG gen = g_gen;
    ReleaseSRWLockShared(&g_lock);
    if (!fam[0]) return false;

    Res r = {};
    IDWriteFontCollection* sys = nullptr;
    if (SUCCEEDED(f->GetSystemFontCollection(&sys, FALSE)) && sys) {
        UINT32 idx = 0;
        BOOL ex = FALSE;
        if (SUCCEEDED(sys->FindFamilyName(fam, &idx, &ex)) && ex) {
            r.ok = true;
            wcscpy_s(r.family, fam);
        }
        sys->Release();
    }
    if (!r.ok && file[0]) LoadFile(f, file, r);
    if (InterlockedIncrement(&g_logs) <= 6)
        Wh_Log(L"[Font] \"%s\" in this DWrite factory: %s%s", fam, r.ok ? (r.coll ? L"loaded from file as " : L"installed as ") : L"not found",
               r.ok ? r.family : L"");

    AcquireSRWLockExclusive(&g_lock);
    bool have = false;
    for (auto& e : g_cache) have = have || e.f == f;
    if (gen == g_gen && !have && g_cache.size() < 8) {
        Res keep = r;
        f->AddRef();
        keep.f = f;
        if (keep.coll) keep.coll->AddRef();
        g_cache.push_back(keep);
    }
    ReleaseSRWLockExclusive(&g_lock);
    if (r.ok) {
        wcscpy_s(name, cch, r.family);
        *coll = r.coll;   // our creation reference goes to the caller
    } else if (r.coll) {
        r.coll->Release();
    }
    return r.ok;
}

static HRESULT STDMETHODCALLTYPE CreateTextFormat_Hook(IDWriteFactory* self, const WCHAR* family,
                                                       IDWriteFontCollection* coll, DWRITE_FONT_WEIGHT weight,
                                                       DWRITE_FONT_STYLE style, DWRITE_FONT_STRETCH stretch,
                                                       FLOAT size, const WCHAR* locale, IDWriteTextFormat** out) {
    if (t_inTitle > 0 && g_on && !g_unloading && out) {
        wchar_t name[LF_FACESIZE * 2];
        IDWriteFontCollection* c = nullptr;
        const WCHAR* useFam = family;
        IDWriteFontCollection* useColl = coll;
        if (Resolve(self, name, ARRAYSIZE(name), &c)) {
            useFam = name;
            useColl = c;
        }
        int w = g_weight;
        DWRITE_FONT_WEIGHT useW = w ? (DWRITE_FONT_WEIGHT)w : weight;
        if (useFam != family || useW != weight) {
            HRESULT hr = CreateTextFormat_Orig(self, useFam, useColl, useW, style, stretch, size, locale, out);
            if (c) c->Release();
            if (InterlockedIncrement(&g_logs) <= 9)
                Wh_Log(L"[Font] title format %s -> %s %d at %.1f: 0x%08lX", family ? family : L"?", useFam, (int)useW,
                       size, (unsigned long)hr);
            if (SUCCEEDED(hr)) return hr;
        } else if (c) {
            c->Release();
        }
    }
    return CreateTextFormat_Orig(self, family, coll, weight, style, stretch, size, locale, out);
}

static long TextCreateFormat_Hook(void* self) {
    t_inTitle++;
    long r = TextCreateFormat_Orig(self);
    t_inTitle--;
    return r;
}

// CreateTextLayout makes a new text format only when the window's LOGFONT (+0xE0) differs from
// its cached copy (+0x13C). A font change flips one byte of the cached copy once per title.
static long TextCreateLayout_Hook(void* self) {
    if (g_layoutForceOk && self) {
        LONG gen = g_gen;
        bool flip = false;
        AcquireSRWLockExclusive(&g_genLock);
        auto it = g_textGen.find(self);
        if (it == g_textGen.end()) {
            g_textGen.emplace(self, gen);
            flip = true;   // made before the mod loaded, or new (it makes a format anyway)
        } else if (it->second != gen) {
            it->second = gen;
            flip = true;
        }
        ReleaseSRWLockExclusive(&g_genLock);
        if (flip) ((BYTE*)self)[0x13C] ^= 1;
    }
    t_inTitle++;
    long r = TextCreateLayout_Orig(self);
    t_inTitle--;
    return r;
}

static void Forget(void* text) {
    AcquireSRWLockExclusive(&g_genLock);
    g_textGen.erase(text);
    ReleaseSRWLockExclusive(&g_genLock);
}

// Title width in the chosen font, or -1 to measure the usual way.
static int Measure(const wchar_t* text, int n, const LOGFONTW& lf) {
    IDWriteFactory* f = g_measureF;
    if (!g_on || !f || n <= 0) return -1;
    wchar_t name[LF_FACESIZE * 2];
    IDWriteFontCollection* c = nullptr;
    const wchar_t* fam = lf.lfFaceName;
    if (Resolve(f, name, ARRAYSIZE(name), &c)) fam = name;
    int w = g_weight ? g_weight : (lf.lfWeight ? (int)lf.lfWeight : 400);
    float px = (float)abs(lf.lfHeight);
    if (px < 1) px = 12;
    int result = -1;
    IDWriteTextFormat* fmt = nullptr;
    if (SUCCEEDED(f->CreateTextFormat(fam, c, (DWRITE_FONT_WEIGHT)w, DWRITE_FONT_STYLE_NORMAL,
                                      DWRITE_FONT_STRETCH_NORMAL, px, L"en-us", &fmt)) && fmt) {
        fmt->SetWordWrapping(DWRITE_WORD_WRAPPING_NO_WRAP);
        IDWriteTextLayout* lay = nullptr;
        if (SUCCEEDED(f->CreateTextLayout(text, (UINT32)n, fmt, 100000.0f, 1000.0f, &lay)) && lay) {
            DWRITE_TEXT_METRICS m = {};
            if (SUCCEEDED(lay->GetMetrics(&m))) result = (int)ceilf(m.widthIncludingTrailingWhitespace);
            lay->Release();
        }
        fmt->Release();
    }
    if (c) c->Release();
    return result;
}

// On the timer thread, once a second: the tool bumps fontSeq when it has copied a new font file.
static bool PollSeq() {
    if (!stbshared::g_blk) {
        ULONGLONG now = GetTickCount64();
        if (now - g_lastOpenTry < 10000) return false;
        g_lastOpenTry = now;
        if (!stbshared::Open()) return false;
    }
    LONG s = stbshared::FontSeq();
    if (s == g_seenSeq) return false;
    g_seenSeq = s;
    return Load();
}

static bool HasBytes(const BYTE* p, size_t n, const char* hex) {
    BYTE pat[16];
    size_t k = 0;
    for (const char* h = hex; h[0] && h[1] && k < sizeof(pat); h += 2) {
        if (*h == ' ') { h--; continue; }
        unsigned v = 0;
        sscanf(h, "%2x", &v);
        pat[k++] = (BYTE)v;
    }
    for (size_t i = 0; i + k <= n; i++)
        if (memcmp(p + i, pat, k) == 0) return true;
    return false;
}

// From Sec_ModInit (hooks set here are applied when init returns).
static void Setup() {
    Load();
    HMODULE dw = LoadLibraryExW(L"dwrite.dll", nullptr, LOAD_LIBRARY_SEARCH_SYSTEM32);
    auto pDW = dw ? (DWriteCreateFactory_t)GetProcAddress(dw, "DWriteCreateFactory") : nullptr;
    bool factoryHook = false;
    if (pDW && SUCCEEDED(pDW(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory), (IUnknown**)&g_measureF)) &&
        g_measureF) {
        void* ctf = (*(void***)g_measureF)[15];   // IDWriteFactory::CreateTextFormat
        factoryHook = Wh_SetFunctionHook(ctf, (void*)CreateTextFormat_Hook, (void**)&CreateTextFormat_Orig);
    }
    bool layoutHook = false;
    if (g_textLayoutAddr && factoryHook) {
        const BYTE* p = (const BYTE*)g_textLayoutAddr;
        g_layoutForceOk = HasBytes(p, 0x200, "488D993C010000") && HasBytes(p, 0x200, "488DB1E0000000") &&
                          HasBytes(p, 0x200, "41B85C000000");
        layoutHook = Wh_SetFunctionHook(g_textLayoutAddr, (void*)TextCreateLayout_Hook, (void**)&TextCreateLayout_Orig);
        if (!layoutHook) g_layoutForceOk = false;
    }
    stbshared::Open();
    g_seenSeq = stbshared::FontSeq();
    Wh_Log(L"[Font] factory hook %d, title format hook %d, layout hook %d (font reset %d), shared block %d",
           (int)factoryHook, (int)(TextCreateFormat_Orig != nullptr), (int)layoutHook, (int)g_layoutForceOk,
           (int)(stbshared::g_blk != nullptr));
}

static void OnUnloading() {
    g_on = false;
    InterlockedIncrement(&g_gen);
}

static void Uninit() {
    AcquireSRWLockExclusive(&g_lock);
    ClearCacheLocked();
    ReleaseSRWLockExclusive(&g_lock);
    if (g_measureF) g_measureF->Release();
    g_measureF = nullptr;
    stbshared::Close();
}
}  // namespace tfont


// Per window, filled by RepositionTitle (layout) and the title text hook.
struct TitleInfo {
    void* text;          // CDWriteText of the title
    HWND hwnd;
    bool closeOnly;
    bool dock;           // the layout reserved room for a dock
    bool rightFromVisual;   // dock right edge = title visual right edge (icon right of the title)
    bool emptyTitle;
    bool hoverIn;
    int E, R;            // dock room left of the text and right of the text (px)
    int textMax;         // width the text may use (px)
    int visL, visW;      // title visual left edge and width in window coordinates
    int dpi, band;
    int dockL, dockR;    // last drawn dock, window x
    float hoverP;        // 0..1 hover animation progress
    wchar_t shown[64];   // uptime suffix currently in the title
    int shownLen, sufStart, sufLen;
    bool wantRelayout;
    bool tooLong;        // title too long for a suffix: the timer leaves it alone
    int ovrUp = -1;      // per-app uptime rule: -1 inherit, 0 off, 1 on
};
static std::unordered_map<void*, TitleInfo> g_titles;   // CTopLevelWindow* -> info
static std::unordered_map<void*, void*> g_textToWin;    // CDWriteText* (and its clones) -> CTopLevelWindow*
static volatile LONG g_dtorHooked = 0;    // both destructor hooks work: timers may call into windows
static volatile LONG g_textHooksOk = 0;   // every hook the dock needs is in place
static volatile LONG g_dockBroken = 0;    // self-check failed: no dock, text stays where Windows puts it
static volatile LONG g_dockOkCount = 0;
static volatile LONG g_dockMissCount = 0;   // odd draws in a row

static int MeasureTitleWidth(HWND hwnd, int dpi, const wchar_t* suffix) {
    if (!hwnd || !g_pSPIForDpi) return -1;
    wchar_t text[400] = {};
    int n = SafeGetWindowText(hwnd, text, 300);
    if (n < 0) return -1;   // hung / unavailable: caller falls back to the safe left layout
    if (n == 0) return 0;
    if (suffix && *suffix) {
        int sl = (int)wcslen(suffix);
        if (n + sl < 399) { wcscpy(text + n, suffix); n += sl; }
    }
    NONCLIENTMETRICSW ncm = {};
    ncm.cbSize = sizeof(ncm);
    if (!g_pSPIForDpi(SPI_GETNONCLIENTMETRICS, sizeof(ncm), &ncm, 0, dpi)) return -1;
    { int fw = tfont::Measure(text, n, ncm.lfCaptionFont); if (fw >= 0) return fw; }
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

static void StoreTitleInfo(void* text, bool dock, bool rightFromVisual, int E, int R, int textMax,
                           int visL, int visW, int dpi) {
    void* win = t_seq.win;
    if (!win) return;
    int l[4] = {}, r[4] = {}, band = 0;
    GetWinLayout(win, l, r, &band);
    AcquireSRWLockExclusive(&g_titleLock);
    auto it = g_titles.find(win);
    if (it == g_titles.end()) {
        // A new window: forget windows that are gone (only matters without the destructor hook)
        for (auto p = g_titles.begin(); p != g_titles.end();) {
            if (p->second.hwnd && !IsWindow(p->second.hwnd)) {
                for (auto q = g_textToWin.begin(); q != g_textToWin.end();) {
                    if (q->second == p->first) q = g_textToWin.erase(q); else ++q;
                }
                p = g_titles.erase(p);
            } else {
                ++p;
            }
        }
        it = g_titles.emplace(win, TitleInfo{}).first;
    }
    TitleInfo& ti = it->second;
    ti.text = text;
    ti.hwnd = t_seq.hwnd;
    ti.closeOnly = t_seq.closeOnly;
    ti.dock = dock;
    ti.rightFromVisual = rightFromVisual;
    ti.E = E; ti.R = R; ti.textMax = textMax;
    ti.visL = visL; ti.visW = visW;
    ti.dpi = dpi; ti.band = band;
    {   // per-app rules for this window (cached resolve): dock off and uptime override
        int pd, pal;
        ResolvePerApp(t_seq.hwnd, pd, pal, ti.ovrUp);
        if (pd == 0) ti.dock = false;   // the pill brush reads ti.dock, so kill it here
    }
    if (text) g_textToWin[text] = win;
    HWND hwLog = ti.hwnd;
    bool coLog = ti.closeOnly;
    ReleaseSRWLockExclusive(&g_titleLock);
    DebugLog(L"[Store] win=%p text=%p hwnd=%p closeOnly=%d dock=%d E=%d", win, text, hwLog, (int)coLog,
             (int)dock, E);
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

    // Per-app overrides for this window's app (first matching rule in perApp.list).
    int paDock = -1, paAlign = -1, paUp = -1;
    if (t_seq.hwnd) ResolvePerApp(t_seq.hwnd, paDock, paAlign, paUp);

    // Very narrow window: no room next to the buttons -> hide icon and title
    bool noRoom = (aR - aL) < 24;
    bool showIcon = origHasIcon && !g_settings.hideIcon && !noRoom;
    bool showTitle = !g_settings.hideTitle && !noRoom;

    // Title dock: keep its padding inside the free area. A per-app rule can turn it off.
    bool dock = g_settings.dockOn && g_textHooksOk && !g_dockBroken && showTitle && !g_unloading;
    if (dock && paDock == 0) dock = false;
    int padX = dock ? MulDiv(g_settings.dockPadX, dpi, 96) : 0;
    if (dock && (aR - aL) - 2 * padX < 48) { dock = false; padX = 0; }
    aL += padX;
    aR -= padX;

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

    int align = paAlign >= 0 ? paAlign : EffTitleAlign();   // per-app alignment wins
    int side = iconInGroup ? g_settings.iconSide : 0;
    int textW = availText;
    bool measured = false;

    // Uptime text after the title: measured with the title.
    wchar_t suffix[64] = L"";
    if (showTitle && t_seq.hwnd && UptimeApplies(t_seq.closeOnly, paUp)) {
        AcquireSRWLockExclusive(&g_titleLock);
        UptimeSuffixLocked(t_seq.hwnd, suffix, 64);
        ReleaseSRWLockExclusive(&g_titleLock);
    }

    if (showTitle && (align != 0 || side == 1)) {
        int m = MeasureTitleWidth(t_seq.hwnd, dpi, suffix);
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

    // The dock is drawn inside the title text's own surface, so the text visual
    // grows by E on the left (icon side) and R on the right; the text hooks move
    // the text back by E, so it lands exactly where it would be without a dock.
    int E = 0, R = 0;
    if (dock && showTitle) {
        E = padX + ((iconInGroup && side == 0) ? iconW + gap : 0);
        R = padX + ((iconInGroup && side == 1) ? gap + iconW : 0);
    } else {
        dock = false;
    }
    int visL = titleX - E, visR = titleRightEdge + R;
    if (!showTitle) {
        SetInsetLeft_Orig(title->v, t_seq.winW + 100);
        SetInsetRight_Orig(title->v, -200);
    } else {
        SetInsetLeft_Orig(title->v, visL);
        SetInsetRight_Orig(title->v, t_seq.winW - visR);
    }
    StoreTitleInfo(title->v, dock, (iconInGroup && side == 1), E, R, titleRightEdge - titleX,
                   visL, visR - visL, dpi);

    DebugLog(L"[Title] vis=%p W=%d buttonEnd=%d aL=%d aR=%d iconW=%d textW=%d measured=%d hwnd=%p align=%d side=%d noRoom=%d cx=%d origIconLeft=%d origTitleLeft=%d -> iconX=%d titleX=%d titleRightEdge=%d showIcon=%d showTitle=%d dock=%d E=%d R=%d",
             title->v, t_seq.winW, t_seq.buttonEnd, aL, aR, iconW, textW, (int)measured, t_seq.hwnd, align, side,
             (int)noRoom, cx, icon ? icon->left : -1, title->left, iconX, titleX, titleRightEdge,
             (int)showIcon, (int)showTitle, (int)dock, E, R);
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

static void EnsureMsgWindow();

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


// ======================================================================
//  PART 1b: Title dock and window uptime
// ======================================================================
// Uptime: CTopLevelWindow::UpdateTitle(void) hands the window title to the
// title text (CDWriteText::SetText). While it runs, the SetText hook appends
// " • 1h 05m". A timer marks the title changed when the shown uptime is stale,
// exactly like a real title change.
//
// Dock: CDWriteText::CreateTextBrush draws the title into its own surface:
// GetMetrics, GetOverhangMetrics (sets the surface size and the text origin),
// then ID2D1DeviceContext::DrawTextLayout. While it runs for a title of ours:
//  - the overhang is widened by E on the left, so the text moves right by E
//    inside a visual that RepositionTitle moved left by E (net: no move),
//    and widened up/down/right so the dock fits in the surface;
//  - the dock is drawn just before the text. The text visual sits below the
//    icon visual, so the dock sits behind the icon too.
typedef long (*UpdateTitle_t)(void*);
static UpdateTitle_t UpdateTitle_Orig;
typedef long (*TextSetText_t)(void*, const wchar_t*);
static TextSetText_t TextSetText_Orig;
typedef long (*CreateTextBrush_t)(void*, void**);
static CreateTextBrush_t CreateTextBrush_Orig;
typedef long (*CloneInit_t)(void*, void*, int);
static CloneInit_t CloneInit_Orig;
typedef void (*Dtor_t)(void*);
static Dtor_t WinDtor_Orig, TextDtor_Orig;
typedef void (*SetDirtyFlags_t)(void*, unsigned long);
static SetDirtyFlags_t SetDirtyFlags_Func;

typedef HRESULT (STDMETHODCALLTYPE *LayoutGetMetrics_t)(IDWriteTextLayout*, DWRITE_TEXT_METRICS*);
typedef HRESULT (STDMETHODCALLTYPE *LayoutGetOverhang_t)(IDWriteTextLayout*, DWRITE_OVERHANG_METRICS*);
typedef void (STDMETHODCALLTYPE *DrawTextLayout_t)(ID2D1RenderTarget*, D2D1_POINT_2F, IDWriteTextLayout*,
                                                   ID2D1Brush*, D2D1_DRAW_TEXT_OPTIONS);
static LayoutGetMetrics_t LayoutGetMetrics_Orig;
static LayoutGetOverhang_t LayoutGetOverhang_Orig;
static DrawTextLayout_t DrawTextLayout_Orig;

static void RequestDwmRefresh();
static thread_local void* t_titleWin = nullptr;

struct DockCtx {
    bool on, dock, colorText, rightFromVisual;
    bool gotMetrics, gotOverhang, drew;
    void* layout;
    float E, R, padY, edge, radius, textMax, visW;
    int H, visL;
    float mleft, mtop, mw, mh, layoutW, layoutH;
    float padYeff;
    float ox;   // text origin, from the left edge of the title's slot (overhang left + E)
    float hoverA;
    UINT32 sufStart, sufLen;
    int dockL, dockR;   // window x of the drawn dock
    HWND hwnd;          // window the text belongs to, for the per-frame per-app check
};
static thread_local DockCtx t_dock;

static volatile LONG g_setTextLogs = 0;

static long TextSetText_Hook(void* text, const wchar_t* s) {
    if (!s || g_unloading) return TextSetText_Orig(text, s);
    void* win = t_titleWin;   // UpdateTitle on the stack: this is that window's title text
    bool viaMap = false, found = false, mismatch = false;
    void* tiText = nullptr;
    HWND hwLog = nullptr;
    bool coLog = false;
    wchar_t buf[400];
    bool use = false;
    AcquireSRWLockExclusive(&g_titleLock);
    if (!win) {
        // Otherwise only the text object the layout placed as the title.
        auto m = g_textToWin.find(text);
        if (m != g_textToWin.end()) {
            auto t2 = g_titles.find(m->second);
            if (t2 != g_titles.end() && t2->second.text == text) { win = m->second; viaMap = true; }
        }
    }
    auto it = win ? g_titles.find(win) : g_titles.end();
    if (it != g_titles.end()) {
        TitleInfo& ti = it->second;
        found = true;
        tiText = ti.text;
        mismatch = ti.text && ti.text != text;
        if (!ti.text) ti.text = text;
        g_textToWin[text] = win;
        hwLog = ti.hwnd;
        coLog = ti.closeOnly;
        int prevLen = ti.shownLen;
        ti.shown[0] = 0; ti.shownLen = 0; ti.sufStart = 0; ti.sufLen = 0;
        size_t n = wcslen(s);
        ti.emptyTitle = (n == 0);
        ti.tooLong = (n >= 320);
        if (n > 0 && n < 320 && ti.hwnd && UptimeApplies(ti.closeOnly, ti.ovrUp)) {
            wchar_t suf[64];
            UptimeSuffixLocked(ti.hwnd, suf, 64);
            swprintf(buf, 400, L"%s%s", s, suf);
            wcsncpy(ti.shown, suf, 63);
            ti.shown[63] = 0;
            ti.shownLen = (int)wcslen(ti.shown);
            ti.sufStart = (int)n;
            ti.sufLen = ti.shownLen;
            use = true;
        }
        if (ti.shownLen != prevLen) ti.wantRelayout = true;
    }
    ReleaseSRWLockExclusive(&g_titleLock);
    if (win) {
        DebugLog(L"[SetText] text=%p win=%p via=%s found=%d tiText=%p mismatch=%d hwnd=%p closeOnly=%d up=%d use=%d len=%zu",
                 text, win, viaMap ? L"map" : L"UpdateTitle", (int)found, tiText, (int)mismatch, hwLog, (int)coLog,
                 (int)UptimeApplies(coLog), (int)use, wcslen(s));
    } else if (g_settings.debugLog && InterlockedIncrement(&g_setTextLogs) <= 6) {
        DebugLog(L"[SetText] untracked text=%p len=%zu", text, wcslen(s));
    }
    return TextSetText_Orig(text, use ? buf : s);
}

static long UpdateTitle_Hook(void* win) {
    if (g_settings.debugLog) {
        void* t210 = *(void**)((BYTE*)win + 0x210);
        bool f = false;
        void* tt = nullptr;
        HWND hw = nullptr;
        AcquireSRWLockShared(&g_titleLock);
        auto d = g_titles.find(win);
        if (d != g_titles.end()) { f = true; tt = d->second.text; hw = d->second.hwnd; }
        ReleaseSRWLockShared(&g_titleLock);
        DebugLog(L"[UpdateTitle] win=%p +210=%p found=%d tiText=%p hwnd=%p", win, t210, (int)f, tt, hw);
    }
    void* prev = t_titleWin;
    t_titleWin = win;
    long r = UpdateTitle_Orig(win);
    t_titleWin = prev;
    bool relayout = false;
    AcquireSRWLockExclusive(&g_titleLock);
    auto it = g_titles.find(win);
    if (it != g_titles.end() && it->second.wantRelayout) {
        it->second.wantRelayout = false;
        relayout = true;
    }
    ReleaseSRWLockExclusive(&g_titleLock);
    // A wider or narrower uptime moves a centered title: lay it out again.
    if (relayout && TitleDependsOnText() && t_posDepth == 0 && !t_relayout) DoRelayout(win, L"Uptime");
    return r;
}

static long CreateTextBrush_Hook(void* text, void** out) {
    if (g_unloading || !g_textHooksOk) return CreateTextBrush_Orig(text, out);
    DockCtx c = {};
    bool primary = false;
    void* win = nullptr;
    AcquireSRWLockShared(&g_titleLock);
    auto m = g_textToWin.find(text);
    if (m != g_textToWin.end()) {
        win = m->second;
        auto it = g_titles.find(win);
        if (it != g_titles.end()) {
            const TitleInfo& ti = it->second;
            primary = (ti.text == text);
            float s = ti.dpi > 0 ? ti.dpi / 96.0f : 1.0f;
            c.dock = ti.dock && g_settings.dockOn && !g_dockBroken;
            c.colorText = ti.sufLen > 0 && g_settings.upColorSet;
            c.rightFromVisual = ti.rightFromVisual;
            c.E = (float)ti.E;
            c.R = (float)ti.R;
            c.textMax = (float)ti.textMax;
            c.visW = (float)ti.visW;
            c.visL = ti.visL;
            c.hwnd = ti.hwnd;
            c.padY = roundf(g_settings.dockPadY * s);
            c.edge = roundf(g_settings.dockEdge * s);
            if (c.edge < 1) c.edge = 1;
            c.radius = g_settings.dockRadius * s;
            float p = ti.hoverP < 0 ? 0 : (ti.hoverP > 1 ? 1 : ti.hoverP);
            c.hoverA = g_settings.dockHover ? 1.0f - (1.0f - p) * (1.0f - p) : 0.0f;   // ease-out
            c.sufStart = (UINT32)ti.sufStart;
            c.sufLen = (UINT32)ti.sufLen;
        }
    }
    ReleaseSRWLockShared(&g_titleLock);
    if (!c.dock && !c.colorText) return CreateTextBrush_Orig(text, out);

    // Height of the text visual (used to keep the dock inside it); 0 = unknown.
    // CDWriteText is far larger than 0x50 bytes; a bad value is caught by the range check.
    int H = *(int*)((BYTE*)text + 0x4c);
    c.H = (H >= 8 && H <= 400) ? H : 0;
    c.on = true;
    c.dockL = c.dockR = -1;
    t_dock = c;
    long r = CreateTextBrush_Orig(text, out);
    DockCtx done = t_dock;
    t_dock = DockCtx{};

    if (done.dock && r >= 0) {
        bool good = done.gotMetrics && done.gotOverhang && done.drew;
        bool hasText = !done.gotMetrics || done.mw > 0.5f;   // empty text may skip steps on purpose
        if (good) {
            InterlockedIncrement(&g_dockOkCount);
            InterlockedExchange(&g_dockMissCount, 0);
        } else if (hasText && InterlockedIncrement(&g_dockMissCount) >= 3) {
            // The text was not moved back by E, or the dock was not drawn: stop docking, lay out again.
            if (InterlockedExchange(&g_dockBroken, 1) == 0) {
                DockLog(L"[Dock] self-check failed 3x (metrics=%d overhang=%d drew=%d ok=%ld): dock off",
                       (int)done.gotMetrics, (int)done.gotOverhang, (int)done.drew, (long)g_dockOkCount);
                RequestDwmRefresh();
            }
        }
        if (primary && done.drew && done.dockR > done.dockL) {
            AcquireSRWLockExclusive(&g_titleLock);
            auto it = g_titles.find(win);
            if (it != g_titles.end()) { it->second.dockL = done.dockL; it->second.dockR = done.dockR; }
            ReleaseSRWLockExclusive(&g_titleLock);
        }
    }
    DebugLog(L"[Dock] brush text=%p win=%p hr=%ld dock=%d metrics=%d overhang=%d drew=%d H=%d mw=%.1f mh=%.1f padY=%.1f dockX=[%d,%d]",
             text, win, r, (int)done.dock, (int)done.gotMetrics, (int)done.gotOverhang, (int)done.drew, done.H,
             done.mw, done.mh, done.padYeff, done.dockL, done.dockR);
    return r;
}

static HRESULT STDMETHODCALLTYPE LayoutGetMetrics_Hook(IDWriteTextLayout* self, DWRITE_TEXT_METRICS* m) {
    if (t_dock.on && !t_dock.gotMetrics && (!t_dock.layout || t_dock.layout == self)) {
        t_dock.layout = self;
        if (t_dock.dock && t_dock.textMax > 1.0f && self->GetMaxWidth() > t_dock.textMax + 0.5f)
            self->SetMaxWidth(t_dock.textMax);   // the visual is wider now; trim the text where it was
    }
    HRESULT hr = LayoutGetMetrics_Orig(self, m);
    if (t_dock.on && self == t_dock.layout && SUCCEEDED(hr) && m) {
        t_dock.mleft = m->left;
        t_dock.mtop = m->top;
        t_dock.mw = m->width;
        t_dock.mh = m->height;
        t_dock.layoutW = m->layoutWidth;
        t_dock.layoutH = m->layoutHeight;
        t_dock.gotMetrics = true;
    }
    return hr;
}

static HRESULT STDMETHODCALLTYPE LayoutGetOverhang_Hook(IDWriteTextLayout* self, DWRITE_OVERHANG_METRICS* o) {
    HRESULT hr = LayoutGetOverhang_Orig(self, o);
    if (!t_dock.on || !t_dock.dock || self != t_dock.layout || !t_dock.gotMetrics || FAILED(hr) || !o ||
        t_dock.gotOverhang)
        return hr;
    DockCtx& c = t_dock;
    // Vertical padding that still fits inside the visual
    float pad = c.padY;
    float H = c.H > 0 ? (float)c.H : ((c.layoutH >= 8 && c.layoutH <= 400) ? c.layoutH : 0.0f);
    if (H > 0) {
        float room = floorf((H - c.mh) * 0.5f) - fabsf(c.mtop);
        if (pad > room) pad = room;
    } else if (pad > 2) {
        pad = 2;
    }
    if (pad < 0) pad = 0;
    c.padYeff = pad;

    o->left += c.E;   // text origin moves right by exactly E
    float ox = -(floorf(-o->left) - 1.0f);
    float origInset = ox - c.E;
    c.ox = ox;
    float need;
    need = pad - c.mtop + 1.0f;
    if (o->top < need) o->top = need;
    need = c.mtop + c.mh + pad + 1.0f - c.layoutH;
    if (o->bottom < need) o->bottom = need;
    float right = c.rightFromVisual ? (c.visW - ox) : (c.mleft + c.mw + c.R + origInset);
    need = right + 1.0f - c.layoutW;
    if (o->right < need) o->right = need;
    c.gotOverhang = true;
    return hr;
}

static D2D1_COLOR_F Rgb(DWORD rgb, float a) {
    return D2D1::ColorF(((rgb >> 16) & 0xFF) / 255.0f, ((rgb >> 8) & 0xFF) / 255.0f, (rgb & 0xFF) / 255.0f, a);
}

static void DrawDock(ID2D1RenderTarget* rt, D2D1_POINT_2F o) {
    DockCtx& c = t_dock;
    float w = c.edge;
    // The slot starts c.ox left of the text origin; RepositionTitle put the visual's (and so the slot's)
    // left edge at the dock's left edge.
    float oL = roundf(o.x - c.ox);
    float oT = roundf(o.y + c.mtop - c.padYeff);
    float oB = roundf(o.y + c.mtop + c.mh + c.padYeff);
    float oR = c.rightFromVisual ? oL + c.visW : roundf(o.x + c.mleft + c.mw + c.R);
    if (oR > oL + c.visW) oR = oL + c.visW;
    if (oT < 0) oT = 0;
    if (g_settings.debugLog) {
        D2D1_SIZE_F sz = rt->GetSize();
        DebugLog(L"[DockGeo] ox=%.1f o=(%.1f,%.1f) m=(%.1f,%.1f %.1fx%.1f) layout=%.1fx%.1f visW=%.1f visL=%d E=%.1f R=%.1f "
                 L"padY=%.1f rt=%.1fx%.1f -> L=%.0f T=%.0f R=%.0f B=%.0f fromVis=%d",
                 c.ox, o.x, o.y, c.mleft, c.mtop, c.mw, c.mh, c.layoutW, c.layoutH, c.visW, c.visL, c.E, c.R, c.padYeff,
                 sz.width, sz.height, oL, oT, oR, oB, (int)c.rightFromVisual);
    }
    if (oR - oL < 2 * w + 8 || oB - oT < 2 * w + 4) return;
    float rad = c.radius;
    if (rad > (oB - oT) / 2) rad = (oB - oT) / 2;
    float ri = rad - w / 2;
    if (ri < 0) ri = 0;
    // Stroke centred on whole or half pixels so a 2 px edge covers exactly 2 pixel rows.
    D2D1_ROUNDED_RECT rr = {D2D1::RectF(oL + w / 2, oT + w / 2, oR - w / 2, oB - w / 2), ri, ri};

    D2D1_ANTIALIAS_MODE oldAa = rt->GetAntialiasMode();
    rt->SetAntialiasMode(D2D1_ANTIALIAS_MODE_PER_PRIMITIVE);
    ID2D1SolidColorBrush* fill = nullptr;
    // Glass: the blurred title bar behind the text surface shows through a lighter tint.
    int fillA = g_settings.dockGlass ? g_settings.dockGlassA : g_settings.dockFillA;
    if (fillA > 0 &&
        SUCCEEDED(rt->CreateSolidColorBrush(Rgb(g_settings.dockFill, fillA / 100.0f), &fill))) {
        rt->FillRoundedRectangle(rr, fill);
        fill->Release();
        if (g_settings.dockHoverFill && c.hoverA > 0.003f) {
            // Hover lift: the fill brightens towards the hover colour while the pointer is on the dock.
            ID2D1SolidColorBrush* lift = nullptr;
            if (SUCCEEDED(rt->CreateSolidColorBrush(Rgb(g_settings.dockHov1, c.hoverA * 0.12f), &lift))) {
                rt->FillRoundedRectangle(rr, lift);
                lift->Release();
            }
        }
    }
    if (g_settings.dockShine) {
        // Glass shine: white fading out over the top half, as on the taskbar docks.
        D2D1_GRADIENT_STOP ss[2] = {{0.0f, D2D1::ColorF(1, 1, 1, 0.07f)}, {1.0f, D2D1::ColorF(1, 1, 1, 0.0f)}};
        ID2D1GradientStopCollection* sc = nullptr;
        if (SUCCEEDED(rt->CreateGradientStopCollection(ss, 2, &sc)) && sc) {
            ID2D1LinearGradientBrush* sb = nullptr;
            if (SUCCEEDED(rt->CreateLinearGradientBrush(
                    D2D1::LinearGradientBrushProperties(D2D1::Point2F(oL, oT), D2D1::Point2F(oL, (oT + oB) / 2)),
                    sc, &sb)) && sb) {
                rt->FillRoundedRectangle(rr, sb);
                sb->Release();
            }
            sc->Release();
        }
    }
    ID2D1SolidColorBrush* edge = nullptr;
    if (c.hoverA < 0.999f && SUCCEEDED(rt->CreateSolidColorBrush(Rgb(g_settings.dockEdgeC, 0.9f), &edge))) {
        rt->DrawRoundedRectangle(rr, edge, w);
        edge->Release();
    }
    if (c.hoverA > 0.003f) {
        D2D1_GRADIENT_STOP stops[2] = {{0.0f, Rgb(g_settings.dockHov1, 1.0f)}, {1.0f, Rgb(g_settings.dockHov2, 1.0f)}};
        ID2D1GradientStopCollection* coll = nullptr;
        if (SUCCEEDED(rt->CreateGradientStopCollection(stops, 2, &coll))) {
            ID2D1LinearGradientBrush* lg = nullptr;
            D2D1_LINEAR_GRADIENT_BRUSH_PROPERTIES lp = {D2D1::Point2F(oL, oT), D2D1::Point2F(oR, oB)};
            D2D1_BRUSH_PROPERTIES bp = {c.hoverA, D2D1::Matrix3x2F::Identity()};
            if (SUCCEEDED(rt->CreateLinearGradientBrush(&lp, &bp, coll, &lg))) {
                rt->DrawRoundedRectangle(rr, lg, w);
                lg->Release();
            }
            coll->Release();
        }
    }
    rt->SetAntialiasMode(oldAa);
    c.dockL = c.visL;
    c.dockR = c.visL + (int)(oR - oL);
}

static void STDMETHODCALLTYPE DrawTextLayout_Hook(ID2D1RenderTarget* rt, D2D1_POINT_2F o, IDWriteTextLayout* layout,
                                                  ID2D1Brush* brush, D2D1_DRAW_TEXT_OPTIONS opt) {
    if (!t_dock.on || layout != t_dock.layout || t_dock.drew || !rt) {
        DrawTextLayout_Orig(rt, o, layout, brush, opt);
        return;
    }
    t_dock.drew = true;
    if (t_dock.dock && t_dock.gotOverhang && t_dock.hwnd) {   // per-app dock=off, re-checked per frame
        int qd2 = -1, qa2 = -1, qu2 = -1;
        ResolvePerApp(t_dock.hwnd, qd2, qa2, qu2);
        if (qd2 == 0) t_dock.dock = false;
    }
    if (t_dock.dock && t_dock.gotOverhang) DrawDock(rt, o);
    ID2D1SolidColorBrush* sb = nullptr;
    DWRITE_TEXT_RANGE range = {t_dock.sufStart, t_dock.sufLen};
    if (t_dock.colorText && t_dock.sufLen > 0 &&
        SUCCEEDED(rt->CreateSolidColorBrush(Rgb(g_settings.upColor, 1.0f), &sb))) {
        if (FAILED(layout->SetDrawingEffect(sb, range))) { sb->Release(); sb = nullptr; }
    }
    DrawTextLayout_Orig(rt, o, layout, brush, opt);
    if (sb) {
        layout->SetDrawingEffect(nullptr, range);
        sb->Release();
    }
}

// Clones of the title (thumbnails, live previews) draw the same dock.
static long CloneInit_Hook(void* self, void* other, int options) {
    long r = CloneInit_Orig(self, other, options);
    if (other) {
        AcquireSRWLockExclusive(&g_titleLock);
        auto a = g_textToWin.find(self);
        auto b = g_textToWin.find(other);
        if (a != g_textToWin.end() && b == g_textToWin.end()) g_textToWin[other] = a->second;
        else if (b != g_textToWin.end() && a == g_textToWin.end()) g_textToWin[self] = b->second;
        ReleaseSRWLockExclusive(&g_titleLock);
    }
    return r;
}

static void* volatile g_hoverWin = nullptr;
static DWORD g_msgThread = 0;   // thread of the timer window
static volatile LONG g_crossThread = 0;   // a window was freed on another thread: timers stop touching windows

// CDesktopManager::s_csDwmInstance: DWM holds it while it changes a window's title
// (CWindowList::TextChange). The timers hold it too, so no window is freed under them.
static CRITICAL_SECTION* g_dwmCs = nullptr;
static void* g_textChangeAddr = nullptr;   // CWindowList::TextChange (address only)
static void* g_eventProcAddr = nullptr;    // CDesktopManager::DwmEventThreadProc (address only)
static volatile LONG g_dtorLogs = 0;

static bool OwnsDwmLock() {
    return g_dwmCs && (DWORD)(ULONG_PTR)g_dwmCs->OwningThread == GetCurrentThreadId();
}

// A tracked object freed on a thread that is neither the timer thread nor holding the DWM lock
// could be freed while a timer uses it: then the timers stop touching windows for good.
static bool UnsafeFree() {
    return g_msgThread && GetCurrentThreadId() != g_msgThread && !OwnsDwmLock();
}

static void LogFree(const wchar_t* what, void* p, bool tripped) {
    if (!g_settings.debugLog || InterlockedIncrement(&g_dtorLogs) > 12) return;
    wchar_t b[160];
    swprintf(b, 160, L"[Free] %s=%p ownsDwmLock=%d timers=t%lu%s", what, p, (int)OwnsDwmLock(), g_msgThread,
             tripped ? L" -> timers stop" : L"");
    RingAppend(b);
}

static void TextDtor_Hook(void* text) {
    tfont::Forget(text);
    bool tracked = false, tripped = false;
    AcquireSRWLockExclusive(&g_titleLock);
    auto m = g_textToWin.find(text);
    if (m != g_textToWin.end()) {
        tracked = true;
        if (UnsafeFree() && InterlockedExchange(&g_crossThread, 1) == 0) tripped = true;
        auto it = g_titles.find(m->second);
        if (it != g_titles.end() && it->second.text == text) it->second.text = nullptr;
        g_textToWin.erase(m);
    }
    ReleaseSRWLockExclusive(&g_titleLock);
    if (tracked) LogFree(L"text", text, tripped);
    if (tripped) DockLog(L"[Dock] title text freed on thread %lu without the DWM lock: timers stop", GetCurrentThreadId());
    TextDtor_Orig(text);
}

static void WinDtor_Hook(void* win) {
    bool crossNow = false, tracked = false;
    AcquireSRWLockExclusive(&g_titleLock);
    auto gone = g_titles.find(win);
    if (gone != g_titles.end()) {
        tracked = true;
        if (UnsafeFree() && InterlockedExchange(&g_crossThread, 1) == 0) crossNow = true;
        HWND h = gone->second.hwnd;
        if (h && !IsWindow(h)) g_born.erase(h);
        g_titles.erase(gone);
    }
    for (auto q = g_textToWin.begin(); q != g_textToWin.end();) {
        if (q->second == win) q = g_textToWin.erase(q); else ++q;
    }
    if (g_hoverWin == win) g_hoverWin = nullptr;
    ReleaseSRWLockExclusive(&g_titleLock);
    if (tracked) LogFree(L"win", win, crossNow);
    if (crossNow)
        DockLog(L"[Dock] window freed on thread %lu without the DWM lock, timers on %lu: timers stop",
                GetCurrentThreadId(), g_msgThread);
    WinDtor_Orig(win);
}

// ---------------- timers (on the DWM thread that lays out the titles) ----------------
static HWND volatile g_msgWnd = nullptr;
static ATOM g_msgClass = 0;
static const wchar_t kMsgClassName[] = L"SeamlessTitleBars_DockTimer";
static const UINT kMsgHover = WM_APP + 0x31;
static const UINT kMsgRefreshAll = WM_APP + 0x32;
static const UINT kMsgDestroy = WM_APP + 0x33;
static const UINT_PTR kTimerUptime = 1, kTimerHover = 2;
static ULONGLONG g_hoverLast = 0;
static int g_tickCount = 0;

static void UptimeTick() {
    if (g_unloading || g_crossThread || (!g_settings.upOn && !PappAnyUpOn()) || !OnTitleUpdated_Orig) return;
    std::vector<void*> todo;
    HWND hotUpd = nullptr;
    wchar_t hotSuf[48] = L"";
    AcquireSRWLockExclusive(&g_titleLock);
    if (++g_tickCount % 60 == 0) {
        for (auto p = g_born.begin(); p != g_born.end();) {
            if (!IsWindow(p->first)) p = g_born.erase(p); else ++p;
        }
    }
    for (auto& [win, ti] : g_titles) {
        if (!ti.text || !ti.hwnd || ti.emptyTitle || ti.tooLong || !UptimeApplies(ti.closeOnly, ti.ovrUp)) continue;
        if (!IsWindowVisible(ti.hwnd) || IsIconic(ti.hwnd)) continue;
        wchar_t suf[64];
        UptimeSuffixLocked(ti.hwnd, suf, 64);
        if (wcscmp(suf, ti.shown) != 0) todo.push_back(win);
        if (!hotUpd && ti.hwnd == stbshared::HotHwnd()) {
            hotUpd = ti.hwnd;
            wcsncpy_s(hotSuf, suf, _TRUNCATE);
        }
    }
    ReleaseSRWLockExclusive(&g_titleLock);
    if (hotUpd) stbshared::WriteSuffix(hotUpd, hotSuf);   // pointer resting on the dock: keep its menu copy fresh
    for (void* win : todo) OnTitleUpdated_Orig(win);   // same as a real title change
    if (g_tickCount <= 3) Wh_Log(L"[Uptime] tick %d: %zu title(s) updated", g_tickCount, todo.size());
    if (g_settings.debugLog && (g_tickCount <= 40 || g_tickCount % 60 == 0)) {
        wchar_t b[120];
        swprintf(b, 120, L"[Uptime] tick %d: %zu title(s) updated", g_tickCount, todo.size());
        RingAppend(b);
    }
}

static void HoverTick() {
    POINT cur = {};
    GetCursorPos(&cur);
    ULONGLONG now = GetTickCount64();
    ULONGLONG dt = now - g_hoverLast;
    g_hoverLast = now;
    if (dt > 50) dt = 50;
    float step = dt / 150.0f;   // 150 ms fade
    bool moving = false;
    std::vector<void*> dirty;
    HWND hotWnd = nullptr;
    int hotL = 0, hotR = 0, hotBand = 0;
    wchar_t hotSuf[48] = L"";
    AcquireSRWLockExclusive(&g_titleLock);
    for (auto& [win, ti] : g_titles) {
        bool in = false;
        if (ti.hoverIn && ti.hwnd && ti.dock && !g_unloading) {
            RECT wr;
            if (GetWindowRect(ti.hwnd, &wr)) {
                int x = cur.x - wr.left, y = cur.y - wr.top;
                in = x >= ti.dockL && x < ti.dockR && y >= 0 && y <= ti.band;
            }
            if (!in) ti.hoverIn = false;
        }
        if (in) {
            hotWnd = ti.hwnd; hotL = ti.dockL; hotR = ti.dockR; hotBand = ti.band;
            wcsncpy_s(hotSuf, ti.shown, _TRUNCATE);
        }
        float target = (in && g_settings.dockHover) ? 1.0f : 0.0f;
        if (ti.hoverP != target) {
            ti.hoverP += (target > ti.hoverP) ? step : -step;
            if ((target == 1.0f && ti.hoverP > 1.0f) || (target == 0.0f && ti.hoverP < 0.0f)) ti.hoverP = target;
            if (ti.text && ti.hwnd && IsWindow(ti.hwnd)) dirty.push_back(ti.text);
        }
        if (ti.hoverIn || ti.hoverP != target) moving = true;
        if (!in && win == g_hoverWin) g_hoverWin = nullptr;
    }
    ReleaseSRWLockExclusive(&g_titleLock);
    static bool s_hotShared = false;
    if (hotWnd) { stbshared::Write(hotWnd, hotL, hotR, hotBand, hotSuf); s_hotShared = true; }
    else if (s_hotShared) { stbshared::Write(nullptr, 0, 0, 0, L""); s_hotShared = false; }
    if (!g_crossThread)
        for (void* t : dirty) SetDirtyFlags_Func(t, 0x1000);   // redraw the title surface
    HWND mw = g_msgWnd;
    if ((!moving || g_crossThread) && mw) KillTimer(mw, kTimerHover);
}

static void HoverStart(void* win) {
    if (g_unloading || !SetDirtyFlags_Func) return;
    bool start = false;
    HWND hw = nullptr;
    int hl = 0, hr = 0, hb = 0;
    AcquireSRWLockExclusive(&g_titleLock);
    auto it = g_titles.find(win);
    if (it != g_titles.end() && it->second.dock) {
        it->second.hoverIn = true;
        g_hoverWin = win;
        start = true;
        hw = it->second.hwnd; hl = it->second.dockL; hr = it->second.dockR; hb = it->second.band;
    }
    ReleaseSRWLockExclusive(&g_titleLock);
    if (hw) stbshared::Write(hw, hl, hr, hb);
    HWND mw = g_msgWnd;
    if (start && mw) {
        g_hoverLast = GetTickCount64();
        SetTimer(mw, kTimerHover, 15, nullptr);
    }
}

// Every title redraws (settings changed, or the mod unloads and takes its text and dock away).
static void RefreshAllTitles() {
    if (g_crossThread) return;
    std::vector<std::pair<void*, void*>> list;
    AcquireSRWLockShared(&g_titleLock);
    for (auto& [win, ti] : g_titles) list.push_back({win, ti.text});
    ReleaseSRWLockShared(&g_titleLock);
    for (auto& [win, text] : list) {
        if (OnTitleUpdated_Orig) OnTitleUpdated_Orig(win);
        if (text && SetDirtyFlags_Func) SetDirtyFlags_Func(text, 0x1000);
    }
    DebugLog(L"[Dock] refreshed %zu title(s)", list.size());
}

// Held around every timer call into DWM's window objects, the way CWindowList::TextChange does.
struct DwmLockHold {
    bool ok;
    DwmLockHold() : ok(g_dwmCs != nullptr) { if (ok) EnterCriticalSection(g_dwmCs); }
    ~DwmLockHold() { if (ok) LeaveCriticalSection(g_dwmCs); }
};

static LRESULT CALLBACK TitleMsgProc(HWND h, UINT msg, WPARAM wp, LPARAM lp) {
    switch (msg) {
        case WM_TIMER: {
            DwmLockHold hold;
            if (!hold.ok) return 0;
            if (wp == kTimerUptime) { if (tfont::PollSeq()) { RefreshAllTitles(); RequestDwmRefresh(); } UptimeTick(); }
            else if (wp == kTimerHover) HoverTick();
            return 0;
        }
        case kMsgHover:
            HoverStart((void*)lp);
            return 0;
        case kMsgRefreshAll: {
            DwmLockHold hold;
            if (hold.ok) RefreshAllTitles();
            return 0;
        }
        case kMsgDestroy:
            KillTimer(h, kTimerUptime);
            KillTimer(h, kTimerHover);
            DestroyWindow(h);
            return 0;
        case WM_DESTROY:
            if (g_msgWnd == h) g_msgWnd = nullptr;
            return 0;
    }
    return DefWindowProcW(h, msg, wp, lp);
}

// Created on DWM's event thread (it pumps messages; the composition thread that lays out the
// titles does not). Needs both destructor hooks and the DWM lock: a timer must never touch a freed window.
static void EnsureMsgWindow() {
    static bool tried = false;
    if (tried || g_msgWnd || g_unloading || !g_dtorHooked || !g_dwmCs) return;
    tried = true;
    HMODULE self = nullptr;
    GetModuleHandleExW(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS | GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT,
                       (LPCWSTR)&TitleMsgProc, &self);
    WNDCLASSEXW wc = {sizeof(wc)};
    wc.lpfnWndProc = DefWindowProcW;
    wc.hInstance = self;
    wc.lpszClassName = kMsgClassName;
    g_msgClass = RegisterClassExW(&wc);
    if (!g_msgClass && GetLastError() != ERROR_CLASS_ALREADY_EXISTS) {
        DockLog(L"[Dock] timer window class failed (%lu): no uptime ticks or hover", GetLastError());
        return;
    }
    HWND w = CreateWindowExW(0, kMsgClassName, L"", 0, 0, 0, 0, 0, HWND_MESSAGE, nullptr, self, nullptr);
    if (!w) {
        DockLog(L"[Dock] timer window failed (%lu): no uptime ticks or hover", GetLastError());
        return;
    }
    SetWindowLongPtrW(w, GWLP_WNDPROC, (LONG_PTR)TitleMsgProc);
    g_msgThread = GetCurrentThreadId();
    g_msgWnd = w;
    SetTimer(w, kTimerUptime, 1000, nullptr);
    PostMessageW(w, kMsgRefreshAll, 0, 0);   // titles laid out before the window existed get their text again
    DockLog(L"[Dock] timer window %p on thread %lu", w, GetCurrentThreadId());
}

// The lock: TextChange starts with  lea r14,[s_csDwmInstance] / mov rcx,r14 / call [EnterCriticalSection].
// Accepted only when that import really is EnterCriticalSection.
static CRITICAL_SECTION* FindDwmLock(HMODULE udwm) {
    BYTE* f = (BYTE*)g_textChangeAddr;
    if (!f || !udwm) return nullptr;
    auto dos = (IMAGE_DOS_HEADER*)udwm;
    auto nt = (IMAGE_NT_HEADERS*)((BYTE*)udwm + dos->e_lfanew);
    BYTE* lo = (BYTE*)udwm;
    BYTE* hi = lo + nt->OptionalHeader.SizeOfImage;
    if (f < lo || f + 0x80 > hi) return nullptr;
    void* ecs1 = (void*)GetProcAddress(GetModuleHandleW(L"kernel32.dll"), "EnterCriticalSection");
    void* ecs2 = (void*)GetProcAddress(GetModuleHandleW(L"ntdll.dll"), "RtlEnterCriticalSection");
    for (int i = 0; i < 0x50; i++) {
        if (f[i] != 0x4C || f[i + 1] != 0x8D || f[i + 2] != 0x35) continue;   // lea r14,[rip+x]
        BYTE* cs = f + i + 7 + *(INT32*)(f + i + 3);
        if (cs < lo || cs + sizeof(CRITICAL_SECTION) > hi) return nullptr;
        bool movRcx = false;
        for (int j = i + 7; j < i + 7 + 20; j++) {
            if (f[j] == 0x49 && f[j + 1] == 0x8B && f[j + 2] == 0xCE) movRcx = true;   // mov rcx,r14
            if (f[j] == 0xFF && f[j + 1] == 0x15) {                                    // call [rip+y]
                if (!movRcx) return nullptr;
                void** slot = (void**)(f + j + 6 + *(INT32*)(f + j + 2));
                if ((BYTE*)slot < lo || (BYTE*)(slot + 1) > hi) return nullptr;
                void* target = *slot;
                return (target && (target == ecs1 || target == ecs2)) ? (CRITICAL_SECTION*)cs : nullptr;
            }
        }
        return nullptr;
    }
    return nullptr;
}

static DWORD FindEventThread() {
    if (!g_eventProcAddr) return 0;
    using NtQit_t = LONG(NTAPI*)(HANDLE, ULONG, PVOID, ULONG, PULONG);
    auto q = (NtQit_t)GetProcAddress(GetModuleHandleW(L"ntdll.dll"), "NtQueryInformationThread");
    if (!q) return 0;
    DWORD pid = GetCurrentProcessId(), found = 0;
    HANDLE snap = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0);
    if (snap == INVALID_HANDLE_VALUE) return 0;
    THREADENTRY32 te = {};
    te.dwSize = sizeof(te);
    for (BOOL more = Thread32First(snap, &te); more && !found; more = Thread32Next(snap, &te)) {
        if (te.th32OwnerProcessID != pid) continue;
        HANDLE h = OpenThread(THREAD_QUERY_INFORMATION, FALSE, te.th32ThreadID);
        if (!h) continue;
        void* start = nullptr;
        if (q(h, 9 /* ThreadQuerySetWin32StartAddress */, &start, sizeof(start), nullptr) >= 0 &&
            start == g_eventProcAddr)
            found = te.th32ThreadID;
        CloseHandle(h);
    }
    CloseHandle(snap);
    return found;
}

static volatile LONG g_apcPending = 0;

static VOID CALLBACK EventThreadApc(ULONG_PTR) {
    if (!g_unloading) EnsureMsgWindow();
    InterlockedExchange(&g_apcPending, 0);
}

// The event thread waits alertably, so the APC runs there within moments.
static void StartTimersOnEventThread() {
    if (!g_dwmCs || !g_dtorHooked || !g_textHooksOk) return;
    DWORD tid = FindEventThread();
    if (!tid) {
        DockLog(L"[Dock] DWM event thread not found: no uptime ticks or hover");
        return;
    }
    HANDLE h = OpenThread(THREAD_SET_CONTEXT, FALSE, tid);
    if (!h) {
        DockLog(L"[Dock] DWM event thread %lu not opened (%lu): no uptime ticks or hover", tid, GetLastError());
        return;
    }
    InterlockedExchange(&g_apcPending, 1);
    if (!QueueUserAPC(EventThreadApc, h, 0)) {
        InterlockedExchange(&g_apcPending, 0);
        DockLog(L"[Dock] APC to DWM event thread %lu failed (%lu): no uptime ticks or hover", tid, GetLastError());
    } else {
        DockLog(L"[Dock] timers go to DWM event thread %lu", tid);
    }
    CloseHandle(h);
}

static void NotifyDockHover(void* win, const POINT* pt) {
    HWND mw = g_msgWnd;
    if (!mw || g_unloading || !g_settings.dockOn || !(g_settings.dockHover || g_settings.dockMenu)) return;
    bool post = false;
    AcquireSRWLockShared(&g_titleLock);
    auto it = g_titles.find(win);
    if (it != g_titles.end()) {
        const TitleInfo& ti = it->second;
        post = ti.dock && !ti.hoverIn && ti.dockR > ti.dockL &&
               pt->x >= ti.dockL && pt->x < ti.dockR && pt->y >= 0 && pt->y <= ti.band;
    }
    ReleaseSRWLockShared(&g_titleLock);
    if (post) PostMessageW(mw, kMsgHover, 0, (LPARAM)win);
}

// ---------------- window first-seen times across mod reloads ----------------
struct BornRecord { unsigned long long hwnd; unsigned long long t; unsigned pid; unsigned pad; };

static bool g_bornActive = false;   // only the DWM copy of the mod keeps and saves window times

static void SaveBornTimes() {
    if (!g_bornActive) return;
    std::vector<BornRecord> recs;
    AcquireSRWLockShared(&g_titleLock);
    for (auto& [h, b] : g_born) {
        if (recs.size() >= 1024) break;
        if (IsWindow(h)) recs.push_back(BornRecord{(unsigned long long)(ULONG_PTR)h, b.t, b.pid, 0});
    }
    ReleaseSRWLockShared(&g_titleLock);
    Wh_SetBinaryValue(L"windowBornTimes", recs.data(), recs.size() * sizeof(BornRecord));
}

static void LoadBornTimes() {
    std::vector<BornRecord> recs(1024);
    size_t got = Wh_GetBinaryValue(L"windowBornTimes", recs.data(), recs.size() * sizeof(BornRecord));
    size_t n = got / sizeof(BornRecord);
    AcquireSRWLockExclusive(&g_titleLock);
    for (size_t i = 0; i < n && i < recs.size(); i++) {
        HWND h = (HWND)(ULONG_PTR)recs[i].hwnd;
        DWORD pid = 0;
        if (IsWindow(h) && GetWindowThreadProcessId(h, &pid) && pid == recs[i].pid)
            g_born[h] = BornEntry{recs[i].t, pid};
    }
    ReleaseSRWLockExclusive(&g_titleLock);
}

// ---------------- DirectWrite / Direct2D method addresses ----------------
// The text layout and device context methods DWM uses live in dwrite.dll and
// d2d1.dll; one throwaway object of each gives their addresses.
typedef HRESULT (WINAPI *DWriteCreateFactory_t)(DWRITE_FACTORY_TYPE, REFIID, IUnknown**);
typedef HRESULT (WINAPI *D3D11CreateDevice_t)(IDXGIAdapter*, D3D_DRIVER_TYPE, HMODULE, UINT, const D3D_FEATURE_LEVEL*,
                                              UINT, UINT, ID3D11Device**, D3D_FEATURE_LEVEL*, ID3D11DeviceContext**);
typedef HRESULT (WINAPI *D2D1CreateDevice_t)(IDXGIDevice*, const D2D1_CREATION_PROPERTIES*, ID2D1Device**);

static bool HookTextDrawing() {
    void* getMetrics = nullptr;
    void* getOverhang = nullptr;
    void* drawTextLayout = nullptr;

    HMODULE dw = LoadLibraryExW(L"dwrite.dll", nullptr, LOAD_LIBRARY_SEARCH_SYSTEM32);
    auto pDW = dw ? (DWriteCreateFactory_t)GetProcAddress(dw, "DWriteCreateFactory") : nullptr;
    IDWriteFactory* f = nullptr;
    if (pDW && SUCCEEDED(pDW(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory), (IUnknown**)&f)) && f) {
        IDWriteTextFormat* fmt = nullptr;
        if (SUCCEEDED(f->CreateTextFormat(L"Segoe UI", nullptr, DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL,
                                          DWRITE_FONT_STRETCH_NORMAL, 12.0f, L"en-us", &fmt)) && fmt) {
            IDWriteTextLayout* lay = nullptr;
            if (SUCCEEDED(f->CreateTextLayout(L"x", 1, fmt, 100.0f, 20.0f, &lay)) && lay) {
                void** vt = *(void***)lay;
                getMetrics = vt[60];    // IDWriteTextLayout::GetMetrics
                getOverhang = vt[61];   // IDWriteTextLayout::GetOverhangMetrics
                lay->Release();
            }
            fmt->Release();
        }
        f->Release();
    }

    HMODULE d3d = LoadLibraryExW(L"d3d11.dll", nullptr, LOAD_LIBRARY_SEARCH_SYSTEM32);
    HMODULE d2d = LoadLibraryExW(L"d2d1.dll", nullptr, LOAD_LIBRARY_SEARCH_SYSTEM32);
    auto pD3D = d3d ? (D3D11CreateDevice_t)GetProcAddress(d3d, "D3D11CreateDevice") : nullptr;
    auto pD2D = d2d ? (D2D1CreateDevice_t)GetProcAddress(d2d, "D2D1CreateDevice") : nullptr;
    ID3D11Device* dev = nullptr;
    if (pD3D && pD2D &&
        SUCCEEDED(pD3D(nullptr, D3D_DRIVER_TYPE_WARP, nullptr, D3D11_CREATE_DEVICE_BGRA_SUPPORT, nullptr, 0,
                       D3D11_SDK_VERSION, &dev, nullptr, nullptr)) && dev) {
        IDXGIDevice* dxgi = nullptr;
        if (SUCCEEDED(dev->QueryInterface(__uuidof(IDXGIDevice), (void**)&dxgi)) && dxgi) {
            ID2D1Device* d2dDev = nullptr;
            if (SUCCEEDED(pD2D(dxgi, nullptr, &d2dDev)) && d2dDev) {
                ID2D1DeviceContext* dc = nullptr;
                if (SUCCEEDED(d2dDev->CreateDeviceContext(D2D1_DEVICE_CONTEXT_OPTIONS_NONE, &dc)) && dc) {
                    drawTextLayout = (*(void***)dc)[28];   // ID2D1RenderTarget::DrawTextLayout
                    dc->Release();
                }
                d2dDev->Release();
            }
            dxgi->Release();
        }
        dev->Release();
    }

    if (!getMetrics || !getOverhang || !drawTextLayout) {
        DockLog(L"[Dock] text drawing methods not found (metrics=%p overhang=%p draw=%p): no dock",
               getMetrics, getOverhang, drawTextLayout);
        return false;
    }
    bool ok = Wh_SetFunctionHook(getMetrics, (void*)LayoutGetMetrics_Hook, (void**)&LayoutGetMetrics_Orig) &&
              Wh_SetFunctionHook(getOverhang, (void*)LayoutGetOverhang_Hook, (void**)&LayoutGetOverhang_Orig) &&
              Wh_SetFunctionHook(drawTextLayout, (void*)DrawTextLayout_Hook, (void**)&DrawTextLayout_Orig);
    DockLog(L"[Dock] text drawing hooks %s", ok ? L"set" : L"failed");
    return ok;
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
    if (pt) NotifyDockHover(pThis, pt);

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
    // The dock padding and the uptime text change where the icon and title go
    h = Fnv(h, (unsigned long long)(long long)g_settings.dockOn);
    h = Fnv(h, (unsigned long long)(long long)g_settings.dockPadX);
    h = Fnv(h, (unsigned long long)(long long)g_settings.upOn);
    h = Fnv(h, (unsigned long long)(long long)g_settings.upD);
    h = Fnv(h, (unsigned long long)(long long)g_settings.upH);
    h = Fnv(h, (unsigned long long)(long long)g_settings.upM);
    h = Fnv(h, (unsigned long long)(long long)g_settings.upS);
    h = Fnv(h, (unsigned long long)(long long)g_settings.upClock);
    h = Fnv(h, (unsigned long long)(long long)g_settings.upDialogs);
    for (const wchar_t* p = g_settings.upSep; *p; p++) h = Fnv(h, (unsigned long long)*p);

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

    // Per-app rules change where the icon and title go (dock, alignment, uptime).
    AcquireSRWLockShared(&g_paLock);
    h = Fnv(h, g_paOn ? 1ull : 0ull);
    for (const wchar_t* p = g_paListRaw.c_str(); *p; p++) h = Fnv(h, (unsigned long long)(unsigned short)*p);
    ReleaseSRWLockShared(&g_paLock);
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

    if (tfont::Load()) refresh = true;
    if (refresh) RequestDwmRefresh();
    // Uptime text, dock colours and sizes: every title redraws on the DWM thread.
    HWND mw = g_msgWnd;
    if (mw) PostMessageW(mw, kMsgRefreshAll, 0, 0);
}

// Called by Windhawk just before the mod is unloaded, while the hooks still work
void Sec_ModBeforeUninit() {
    if (g_isExplorer) return;
    InterlockedExchange(&g_unloading, 1);
    tfont::OnUnloading();
    // Titles drop the uptime text and the dock (g_unloading turns both off)
    if (HWND mw = g_msgWnd) {
        DWORD_PTR res = 0;
        SendMessageTimeoutW(mw, kMsgRefreshAll, 0, 0, SMTO_BLOCK | SMTO_ABORTIFHUNG, 1000, &res);
    }
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
        StartTimersOnEventThread();
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
    // The APC that creates the timer window must have run before this code goes away.
    for (int i = 0; i < 300 && g_apcPending; i++) Sleep(10);
    if (g_apcPending) {
        HMODULE pin = nullptr;
        GetModuleHandleExW(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS | GET_MODULE_HANDLE_EX_FLAG_PIN,
                           (LPCWSTR)&EventThreadApc, &pin);
        Wh_Log(L"[Dock] event thread APC still queued at unload: module kept loaded");
    }
    if (g_msgWnd) {
        DWORD_PTR res = 0;
        HWND w = g_msgWnd;
        if (!SendMessageTimeoutW(w, kMsgDestroy, 0, 0, SMTO_BLOCK | SMTO_ABORTIFHUNG, 2000, &res) && IsWindow(w)) {
            // The DWM thread did not answer: leave the window with no code of ours in it.
            SetWindowLongPtrW(w, GWLP_WNDPROC, (LONG_PTR)DefWindowProcW);
            DockLog(L"[Dock] timer window left behind without its handler");
        }
        g_msgWnd = nullptr;
    }
    if (g_msgClass) {
        HMODULE self = nullptr;
        GetModuleHandleExW(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS | GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT,
                           (LPCWSTR)&TitleMsgProc, &self);
        UnregisterClassW(kMsgClassName, self);
        g_msgClass = 0;
    }
    SaveBornTimes();
    if (g_everPainted && g_restartOnUnload) RestartDwm();
    tfont::Uninit();
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

    g_initTick = GetTickCount64();
    g_initFt = NowFt();
    LoadBornTimes();
    g_bornActive = true;

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

        // ---- Title dock and uptime ----
        { { LR"(private: long __cdecl CTopLevelWindow::UpdateTitle(void))" },
          (void**)&UpdateTitle_Orig, (void*)UpdateTitle_Hook, true },
        { { LR"(public: virtual long __cdecl CDWriteText::SetText(unsigned short const *))" },
          (void**)&TextSetText_Orig, (void*)TextSetText_Hook, true },
        { { LR"(protected: long __cdecl CDWriteText::CreateTextBrush(struct Windows::UI::Composition::ICompositionBrush * *))" },
          (void**)&CreateTextBrush_Orig, (void*)CreateTextBrush_Hook, true },
        { { LR"(protected: long __cdecl CDWriteText::InitializeVisualTreeClone(class CDWriteText *,enum CloneOptions))" },
          (void**)&CloneInit_Orig, (void*)CloneInit_Hook, true },
        { { LR"(private: virtual __cdecl CTopLevelWindow::~CTopLevelWindow(void))" },
          (void**)&WinDtor_Orig, (void*)WinDtor_Hook, true },
        { { LR"(public: virtual __cdecl CDWriteText::~CDWriteText(void))" },
          (void**)&TextDtor_Orig, (void*)TextDtor_Hook, true },
        { { LR"(public: virtual void __cdecl CVisual::SetDirtyFlags(unsigned long))" },
          (void**)&SetDirtyFlags_Func, nullptr, true },
        // Timers: the DWM lock (read from TextChange) and the event thread (address only)
        { { LR"(public: virtual long __cdecl CWindowList::TextChange(struct IDwmWindow *))" },
          (void**)&g_textChangeAddr, nullptr, true },
        { { LR"(private: static unsigned long __cdecl CDesktopManager::DwmEventThreadProc(void *))" },
          (void**)&g_eventProcAddr, nullptr, true },

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
        { { LR"(private: long __cdecl CDWriteText::CreateTextFormat(void))" },
          (void**)&tfont::TextCreateFormat_Orig, (void*)tfont::TextCreateFormat_Hook, true },
        { { LR"(private: long __cdecl CDWriteText::CreateTextLayout(void))" },
          (void**)&tfont::g_textLayoutAddr, nullptr, true },
    };

    BOOL ok = WindhawkUtils::HookSymbols(udwm, udwmDllHooks, ARRAYSIZE(udwmDllHooks));
    if (ok) g_menuTimer = CreateThreadpoolTimer(MenuTimerCallback, nullptr, nullptr);
    g_hasPosHook = (PosAndSizes_Orig != nullptr);
    DeriveHwndOffset();

    if (ok) {
        g_dtorHooked = (WinDtor_Orig && TextDtor_Orig) ? 1 : 0;
        bool textOk = UpdateTitle_Orig && TextSetText_Orig && CreateTextBrush_Orig && g_dtorHooked &&
                      SetDirtyFlags_Func && g_hwndOffset != SIZE_MAX;
        g_textHooksOk = (textOk && HookTextDrawing()) ? 1 : 0;
        tfont::Setup();
        g_dwmCs = FindDwmLock(udwm);
        DockLog(L"[Dock] TextChange=%d eventProc=%d dwmLock=%s", (int)(g_textChangeAddr != nullptr),
                (int)(g_eventProcAddr != nullptr), g_dwmCs ? L"found" : L"missing (no timers)");
        DockLog(L"[Dock] title=%d text=%d brush=%d clone=%d dtors=%d dirty=%d -> dock %s, uptime ticks %s",
               (int)(UpdateTitle_Orig != nullptr), (int)(TextSetText_Orig != nullptr),
               (int)(CreateTextBrush_Orig != nullptr), (int)(CloneInit_Orig != nullptr), (int)g_dtorHooked,
               (int)(SetDirtyFlags_Func != nullptr), g_textHooksOk ? L"on" : L"off",
               (g_dtorHooked && OnTitleUpdated_Orig) ? L"on" : L"off");
    }

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
    wchar_t windowClass[32]{};
    const bool explorerFrame = GetClassNameW(hWnd, windowClass, ARRAYSIZE(windowClass)) &&
                               wcscmp(windowClass, L"CabinetWClass") == 0;
    // Seamless Flyouts already supplies acrylic for the Explorer frame and body.
    const COLORREF caption = explorerFrame ? DWMWA_COLOR_DEFAULT
                                          : (COLORREF)(activate ? g_active : g_inactive);
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
// ==========================================================================
//  System boxes (dwm.exe)
// ==========================================================================
// Two kinds of Windows box are drawn by processes no mod can load into: the
// "is not responding" box (dwm.exe) and hard-error boxes such as
// "explorer.exe - System Error" (csrss.exe). Both stay flat black with a light
// title. Each gets a dark title and the system acrylic blur:
//  - dwm.exe boxes: a worker thread watches for them and sets the DWM attributes.
//    Every call that reaches the dialog's own thread is posted, never sent.
//  - csrss.exe boxes: DWM ignores attribute calls on another process's window, so
//    a hook on DWM's ShowHide sets the box's DWM record the way DWM's own
//    handlers do. Only top-level #32770 dialogs owned by csrss.exe are touched.
namespace hungdlg {

struct AccentPolicy {
    int state;
    int flags;
    DWORD color;
    int animation;
};
struct WcaData {
    int attrib;
    void* data;
    SIZE_T size;
};
using SetWca_t = BOOL(WINAPI*)(HWND, WcaData*);

HANDLE g_thread = nullptr;
DWORD g_tid = 0;
bool IsDialog(HWND h) {
    if (!h || GetAncestor(h, GA_ROOT) != h) return false;
    wchar_t cls[16] = L"";
    return GetClassNameW(h, cls, 16) && wcscmp(cls, L"#32770") == 0;
}

bool OwnedBy(HWND h, DWORD pid) {
    DWORD owner = 0;
    return pid && GetWindowThreadProcessId(h, &owner) && owner == pid;
}

// dwm.exe's own boxes; csrss.exe boxes go through sysbox below.
bool IsBox(HWND h) {
    return IsDialog(h) && OwnedBy(h, GetCurrentProcessId());
}

// ---- csrss.exe boxes, set from DWM's own data ----
namespace sysbox {
#if defined(_M_X64)
using ShowHide_t = long(WINAPI*)(void* list, void* window);
using Synced_t = void(WINAPI*)(void* list, void* window, bool sync, void** data);
using SetBackdrop_t = long(WINAPI*)(void* list, void* window, int type);
using SetDark_t = long(WINAPI*)(void* list, void* window, bool dark);
using Margins_t = long(WINAPI*)(void* list, void* window);
using OnMargins_t = void(WINAPI*)(void* list, void* data);
using BlurBehind_t = long(WINAPI*)(void* list, void* window, const DWM_BLURBEHIND* bb);

ShowHide_t ShowHide_Orig;
Synced_t Synced;
SetBackdrop_t SetBackdrop_Orig;
SetDark_t SetDark_Orig;
Margins_t Margins_Orig;
OnMargins_t OnMargins;
BlurBehind_t BlurBehind;
void* IsGhost;
CRITICAL_SECTION* g_cs;
size_t g_hwndOff = SIZE_MAX;
size_t g_marginsOff = SIZE_MAX;
DWORD g_csrss = 0;
DWORD g_csrssSnap = 0;
std::atomic<bool> g_ready{false};
std::atomic<long> g_calls{0};
std::atomic<long> g_foreign{0};
std::atomic<long> g_setters{0};

enum : WPARAM { kCalls = 1, kForeign, kApplied, kSetters };

// Readout for the owner's checks: posted to the worker, which writes LocalStorage.
void Note(WPARAM code, LPARAM v) {
    if (g_tid) PostThreadMessageW(g_tid, WM_APP + 2, code, v);
}

bool InModule(const void* p, HMODULE m) {
    auto nt = (IMAGE_NT_HEADERS*)((BYTE*)m + ((IMAGE_DOS_HEADER*)m)->e_lfanew);
    return (BYTE*)p >= (BYTE*)m && (BYTE*)p < (BYTE*)m + nt->OptionalHeader.SizeOfImage;
}

// ShowHide opens with  lea rcx,[s_csDwmInstance] ... call [EnterCriticalSection].
CRITICAL_SECTION* FindLock(BYTE* f, HMODULE m) {
    void* ecs1 = (void*)GetProcAddress(GetModuleHandleW(L"kernel32.dll"), "EnterCriticalSection");
    void* ecs2 = (void*)GetProcAddress(GetModuleHandleW(L"ntdll.dll"), "RtlEnterCriticalSection");
    for (int i = 0; i < 0x40; i++) {
        if (f[i] != 0x48 || f[i + 1] != 0x8D || f[i + 2] != 0x0D) continue;   // lea rcx,[rip+x]
        BYTE* cs = f + i + 7 + *(INT32*)(f + i + 3);
        for (int j = i + 7; j < i + 7 + 16; j++) {
            if (f[j] != 0xFF || f[j + 1] != 0x15) continue;                     // call [rip+y]
            void** slot = (void**)(f + j + 6 + *(INT32*)(f + j + 2));
            if (!InModule(slot, m) || !InModule(cs, m)) return nullptr;
            return (*slot == ecs1 || *slot == ecs2) ? (CRITICAL_SECTION*)cs : nullptr;
        }
        return nullptr;
    }
    return nullptr;
}

// ClientMarginsChange copies the new margins with  movdqu [reg+disp32], xmm0  and then
// calls OnClientMarginsChange; disp32 is where the margins live in CWindowData.
size_t FindMarginsOffset(BYTE* f) {
    for (int i = 0; i < 0x100; i++) {
        if (f[i] != 0xF3) continue;
        int k = i + 1;
        if ((f[k] & 0xF0) == 0x40) k++;                                         // REX
        if (f[k] != 0x0F || f[k + 1] != 0x7F) continue;
        BYTE modrm = f[k + 2];
        if ((modrm & 0xC0) != 0x80 || (modrm & 0x38) != 0 || (modrm & 7) == 4) continue;
        INT32 disp = *(INT32*)(f + k + 3);
        for (int j = k + 7; j < k + 7 + 12; j++) {
            if (f[j] == 0xE8 && f + j + 5 + *(INT32*)(f + j + 1) == (BYTE*)OnMargins) {
                return (disp >= 0x40 && disp < 0x800) ? (size_t)disp : SIZE_MAX;
            }
        }
    }
    return SIZE_MAX;
}

DWORD CsrssBySnapshot() {
    DWORD session = 0, found = 0;
    ProcessIdToSessionId(GetCurrentProcessId(), &session);
    HANDLE snap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (snap == INVALID_HANDLE_VALUE) return 0;
    PROCESSENTRY32W pe{sizeof(pe)};
    for (BOOL ok = Process32FirstW(snap, &pe); ok && !found; ok = Process32NextW(snap, &pe)) {
        DWORD s = 0;
        if (_wcsicmp(pe.szExeFile, L"csrss.exe") == 0 && ProcessIdToSessionId(pe.th32ProcessID, &s) &&
            s == session) {
            found = pe.th32ProcessID;
        }
    }
    CloseHandle(snap);
    return found;
}

HWND WindowOf(void* list, void* window, void** dataOut) {
    void* data = nullptr;
    HWND h = nullptr;
    EnterCriticalSection(g_cs);
    Synced(list, window, true, &data);
    if (data) h = *(HWND*)((BYTE*)data + g_hwndOff);
    LeaveCriticalSection(g_cs);
    if (dataOut) *dataOut = data;
    return h;
}

// Only calls that never send a message: DWM must never wait on the box's thread.
bool IsCsrssBox(void* list, void* window, bool note) {
    if (!g_ready || !window) return false;
    HWND h = WindowOf(list, window, nullptr);
    if (!h || !IsDialog(h)) return false;
    DWORD pid = 0;
    GetWindowThreadProcessId(h, &pid);
    if (!pid || pid == GetCurrentProcessId()) return false;
    if (note) {
        g_foreign++;
        Note(kForeign, pid);
    }
    return pid == g_csrss || pid == g_csrssSnap;
}

// Steps, from the mod's storage: 1 dark title on csrss boxes, 2 system backdrop on them,
// 4 see-through body on them, 8 dark title on every captioned window.
int Mode() { return Wh_GetIntValue(L"sysbox.mode", 15); }

// Any captioned top-level window, including apps no mod can load into. Same rule as
// IsCsrssBox: only calls that never send a message.
bool WantsDarkTitle(void* list, void* window, int mode) {
    if (!g_ready || !window || !(mode & 8)) return false;
    HWND h = WindowOf(list, window, nullptr);
    if (!h || GetAncestor(h, GA_ROOT) != h) return false;
    return (GetWindowLongPtrW(h, GWL_STYLE) & WS_CAPTION) == WS_CAPTION;
}

LPARAM Apply(void* list, void* window) {
    LPARAM r = 0;
    int mode = Mode();
    if ((mode & 1) && SUCCEEDED(SetDark_Orig(list, window, true))) r |= 1;
    if ((mode & 2) && SUCCEEDED(SetBackdrop_Orig(list, window, 3))) r |= 2;   // DWMSBT_TRANSIENTWINDOW
    // The box paints its body black. DWM's blur-behind marks the client area see-through,
    // so black shows the backdrop and the layout stays as it is.
    if ((mode & 4) && BlurBehind) {
        DWM_BLURBEHIND bb{DWM_BB_ENABLE, TRUE, nullptr, FALSE};
        if (SUCCEEDED(BlurBehind(list, window, &bb))) r |= 4;
    }
    return r | (mode << 8);
}

long WINAPI ShowHide_Hook(void* list, void* window) {
    long hr = ShowHide_Orig(list, window);
    if (!g_ready) return hr;
    long n = ++g_calls;
    if ((n & 63) == 1) Note(kCalls, n);
    if (IsCsrssBox(list, window, true)) {
        Note(kApplied, Apply(list, window));
    } else if (WantsDarkTitle(list, window, Mode())) {
        SetDark_Orig(list, window, true);
    }
    return hr;
}

long WINAPI SetDark_Hook(void* list, void* window, bool dark) {
    int mode = dark ? 0 : Mode();
    if (!dark && ((IsCsrssBox(list, window, false) && (mode & 1)) || WantsDarkTitle(list, window, mode))) {
        dark = true;
        Note(kSetters, ++g_setters);
    }
    return SetDark_Orig(list, window, dark);
}

long WINAPI SetBackdrop_Hook(void* list, void* window, int type) {
    if (type != 3 && IsCsrssBox(list, window, false) && (Mode() & 2)) {
        type = 3;
        Note(kSetters, ++g_setters);
    }
    return SetBackdrop_Orig(list, window, type);
}

long WINAPI Margins_Hook(void* list, void* window) {
    long hr = Margins_Orig(list, window);
    if (IsCsrssBox(list, window, false)) {
        LPARAM r = Apply(list, window);
        Note(kApplied, r);
        if (r & 4) Note(kSetters, ++g_setters);
    }
    return hr;
}

void Readout(WPARAM code, LPARAM v) {
    switch (code) {
        case kCalls: Wh_SetIntValue(L"sysbox.calls", (int)v); break;
        case kForeign:
            Wh_SetIntValue(L"sysbox.foreign", (int)v);
            Wh_SetIntValue(L"sysbox.foreignN", (int)g_foreign);
            break;
        case kApplied: Wh_SetIntValue(L"sysbox.applied", (int)v); break;
        case kSetters: Wh_SetIntValue(L"sysbox.setters", (int)v); break;
    }
}

void Setup() {
    HMODULE udwm = GetModuleHandleW(L"udwm.dll");
    auto csrPid = (HANDLE(NTAPI*)())GetProcAddress(GetModuleHandleW(L"ntdll.dll"), "CsrGetProcessId");
    g_csrss = csrPid ? (DWORD)(ULONG_PTR)csrPid() : 0;
    g_csrssSnap = CsrssBySnapshot();
    int bits = 0;
    if (udwm) {
        void* pShowHide = nullptr;
        void* pSetDark = nullptr;
        void* pSetBackdrop = nullptr;
        void* pMargins = nullptr;
        // Addresses only; the hooks are set below on these raw addresses, so the offset
        // scans read DWM's own code, never a hook trampoline.
        WindhawkUtils::SYMBOL_HOOK syms[] = {
            {{LR"(public: virtual long __cdecl CWindowList::ShowHide(struct IDwmWindow *))"},
             &pShowHide, nullptr, false},
            {{LR"(public: void __cdecl CWindowList::GetSyncedWindowData(struct IDwmWindow *,bool,class CWindowData * *))"},
             (void**)&Synced, nullptr, false},
            {{LR"(public: virtual long __cdecl CWindowList::SetSystemBackdropType(struct IDwmWindow *,enum SYSTEMBACKDROP_TYPE))"},
             &pSetBackdrop, nullptr, false},
            {{LR"(public: virtual long __cdecl CWindowList::SetUseDarkModeColors(struct IDwmWindow *,bool))"},
             &pSetDark, nullptr, false},
            {{LR"(public: virtual long __cdecl CWindowList::ClientMarginsChange(struct IDwmWindow *))"},
             &pMargins, nullptr, false},
            {{LR"(private: void __cdecl CWindowList::OnClientMarginsChange(class CWindowData *))"},
             (void**)&OnMargins, nullptr, false},
            {{LR"(public: virtual long __cdecl CWindowList::BlurBehindChange(struct IDwmWindow *,struct _DWM_BLURBEHIND const *))"},
             (void**)&BlurBehind, nullptr, true},
            {{LR"(public: bool __cdecl CWindowData::IsGhostWindow(struct HWND__ * *)const )"},
             (void**)&IsGhost, nullptr, false},
        };
        if (WindhawkUtils::HookSymbols(udwm, syms, ARRAYSIZE(syms))) {
            bits |= 1;
            g_cs = caption::g_dwmCs ? caption::g_dwmCs : FindLock((BYTE*)pShowHide, udwm);
            g_marginsOff = FindMarginsOffset((BYTE*)pMargins);
            g_hwndOff = caption::g_hwndOffset != SIZE_MAX
                            ? caption::g_hwndOffset
                            : caption::OffsetFromAssemblyRegex(
                                  IsGhost, SIZE_MAX,
                                  std::regex(R"(mov \w+, \[rcx\+0x([0-9a-f]+)\])", std::regex_constants::icase),
                                  10);
            bool readyToHook = g_cs && g_marginsOff != SIZE_MAX && g_hwndOff != SIZE_MAX &&
                               (g_csrss || g_csrssSnap);
            if (readyToHook &&
                Wh_SetFunctionHook(pShowHide, (void*)ShowHide_Hook, (void**)&ShowHide_Orig) &&
                Wh_SetFunctionHook(pSetDark, (void*)SetDark_Hook, (void**)&SetDark_Orig) &&
                Wh_SetFunctionHook(pSetBackdrop, (void*)SetBackdrop_Hook, (void**)&SetBackdrop_Orig) &&
                Wh_SetFunctionHook(pMargins, (void*)Margins_Hook, (void**)&Margins_Orig)) {
                bits |= 32;
            }
        }
    }
    if (g_cs) bits |= 2;
    if (g_marginsOff != SIZE_MAX) bits |= 4;
    if (g_hwndOff != SIZE_MAX) bits |= 8;
    if (g_csrss || g_csrssSnap) bits |= 16;
    g_ready = bits == 63;
    Wh_SetIntValue(L"sysbox.setup", bits);
    Wh_SetIntValue(L"sysbox.csrss", (int)g_csrss);
    Wh_SetIntValue(L"sysbox.csrssSnap", (int)g_csrssSnap);
    Wh_SetIntValue(L"sysbox.margins", g_marginsOff == SIZE_MAX ? -1 : (int)g_marginsOff);
    Wh_SetIntValue(L"sysbox.hwnd", g_hwndOff == SIZE_MAX ? -1 : (int)g_hwndOff);
    Wh_SetIntValue(L"sysbox.calls", 0);
    Wh_SetIntValue(L"sysbox.foreignN", 0);
    Wh_SetIntValue(L"sysbox.applied", -1);
    Wh_SetIntValue(L"sysbox.setters", 0);
    Wh_SetIntValue(L"sysbox.blurBehind", BlurBehind ? 1 : 0);
}

void Stop() { g_ready = false; }
#else
void Setup() {}
void Stop() {}
void Readout(WPARAM, LPARAM) {}
#endif
}  // namespace sysbox

void Style(HWND h) {
    BOOL dark = TRUE;
    DwmSetWindowAttribute(h, 20 /* DWMWA_USE_IMMERSIVE_DARK_MODE */, &dark, sizeof(dark));
    // The box paints its body black; over the extended frame black shows the backdrop.
    MARGINS m{-1, -1, -1, -1};
    DwmExtendFrameIntoClientArea(h, &m);
    // 3 transient acrylic, 2 Mica, 4 Mica Alt; LocalStorage hungdlg.backdrop, read per box.
    int backdrop = Wh_GetIntValue(L"hungdlg.backdrop", 3);
    if (backdrop < 1 || backdrop > 4) backdrop = 3;
    HRESULT hr = DwmSetWindowAttribute(h, 38 /* DWMWA_SYSTEMBACKDROP_TYPE */, &backdrop, sizeof(backdrop));
    SetWindowPos(h, nullptr, 0, 0, 0, 0,
                 SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE | SWP_FRAMECHANGED |
                     SWP_ASYNCWINDOWPOS);
    RedrawWindow(h, nullptr, nullptr, RDW_INVALIDATE | RDW_ERASE | RDW_FRAME | RDW_ALLCHILDREN);
    Wh_Log(L"[Box] styled %p, backdrop 0x%08X", h, (unsigned)hr);
}

BOOL CALLBACK StyleOpen(HWND h, LPARAM) {
    if (IsBox(h) && IsWindowVisible(h)) Style(h);
    return TRUE;
}

void CALLBACK OnShow(HWINEVENTHOOK, DWORD, HWND h, LONG obj, LONG, DWORD, DWORD) {
    if (obj == OBJID_WINDOW && IsBox(h)) Style(h);
}

DWORD WINAPI Worker(void*) {
    HWINEVENTHOOK hook = SetWinEventHook(EVENT_OBJECT_SHOW, EVENT_OBJECT_SHOW, nullptr, OnShow,
                                         0, 0, WINEVENT_OUTOFCONTEXT);
    Wh_Log(L"[Box] watching, hook %p", hook);
    EnumWindows(StyleOpen, 0);
    MSG msg;
    while (GetMessageW(&msg, nullptr, 0, 0) > 0) {
        if (msg.hwnd == nullptr && msg.message == WM_APP + 1) {
            EnumWindows(StyleOpen, 0);
            continue;
        }
        if (msg.hwnd == nullptr && msg.message == WM_APP + 2) {
            sysbox::Readout(msg.wParam, msg.lParam);
            continue;
        }
        DispatchMessageW(&msg);
    }
    if (hook) UnhookWinEvent(hook);
    return 0;
}

BOOL Sec_ModInit() {
    sysbox::Setup();
    g_thread = CreateThread(nullptr, 0, Worker, nullptr, 0, &g_tid);
    return g_thread != nullptr;
}

void SettingsChanged() {
    if (g_tid) PostThreadMessageW(g_tid, WM_APP + 1, 0, 0);
}

void Stop() {
    sysbox::Stop();
    if (!g_thread) return;
    PostThreadMessageW(g_tid, WM_QUIT, 0, 0);
    if (WaitForSingleObject(g_thread, 5000) != WAIT_OBJECT_0) {
        // Never unload code a thread may still run inside DWM: pin the module instead.
        HMODULE self = nullptr;
        GetModuleHandleExW(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS | GET_MODULE_HANDLE_EX_FLAG_PIN,
                           reinterpret_cast<LPCWSTR>(&Worker), &self);
        Wh_Log(L"[Box] worker did not stop in 5 s; module pinned");
    }
    CloseHandle(g_thread);
    g_thread = nullptr;
    g_tid = 0;
}

}  // namespace hungdlg

namespace dispatch {

enum : int {
    kColours = 1,
    kButtons = 2,
    kUwp = 4,
    kNative = 8,
    kCef = 16,
    kBasic = 32,
    kHung = 64,
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
        return (On(L"buttons.enabled") ? kButtons : 0) | (On(L"hungDialog.enabled") ? kHung : 0);
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
        {kHung, hungdlg::Sec_ModInit, L"system boxes"},
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
    if (g_active & kHung) hungdlg::Stop();
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
    if (g_active & kHung) hungdlg::SettingsChanged();
    return false;
}

}  // namespace dispatch

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

// ===========================================================================
// Settings window (tool process): the Seamless Launchpad settings GUI, the
// standard for every DavidHiFi mod. Generated by v12\gen12.py.
// ===========================================================================
std::wstring Hotkey_Format(UINT, UINT) { return {}; }   // no shortcut fields here
extern "C" IMAGE_DOS_HEADER __ImageBase;
namespace stbset {
// The settings window, from the tray icon. It shows the same settings as
// Windhawk's page for this mod and saves them through windhawk-cli, so the two
// stay in step. Writing a mod's settings takes admin rights, so the save runs
// the CLI elevated (silently where UAC prompts are off).

constexpr WCHAR kSettingsClass[] = L"WindhawkSeamlessTitleBarsSettings";
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
// Generated by work\2026-11-11-title-dock\v12\gen12.py from the settings block.
static std::vector<SetField> Set_MakeFields() {
    using K = SetField;
    return {
{K::Choice, L"title.titleAlign", L"Icon and title alignment", L"Where the icon and title sit. Left = right after the buttons.", L"center", {{L"left", L"Left"}, {L"center", L"Center"}, {L"right", L"Right"}}, 0, 100, 0, L"Icon and title"},
{K::Choice, L"title.dialogAlign", L"Alignment in dialogs", L"Same as above, for windows that only have a close button.", L"center", {{L"left", L"Left"}, {L"center", L"Center"}, {L"right", L"Right"}}, 0, 100, 0, L"Icon and title"},
{K::Check, L"title.centerOnText", L"Center the title text itself", L"On = the text is centered and the icon sits beside it. Off = the icon and text are centered as a group.", L"1", {}, 0, 100, 0, L"Icon and title"},
{K::Number, L"title.centerNudge", L"Center fine-tune (px)", L"Positive moves the centered title right, negative moves it left. -300 to 300 (Suggested: 0).", L"0", {}, -300, 300, 0, L"Icon and title"},
{K::Choice, L"title.iconPosition", L"Icon position", L"Where the window icon goes.", L"beforeTitle", {{L"beforeTitle", L"Left of the title"}, {L"afterTitle", L"Right of the title"}, {L"farLeft", L"Far left"}, {L"farRight", L"Far right"}}, 0, 100, 0, L"Icon and title"},
{K::Number, L"title.titleGap", L"Gap after buttons (px)", L"Space between the last button and the icon and title. 0 to 300 (Suggested: 8).", L"8", {}, 0, 300, 0, L"Icon and title"},
{K::Number, L"title.iconTitleGap", L"Gap between icon and title (px)", L"0 to 100 (Suggested: 5).", L"5", {}, 0, 100, 0, L"Icon and title"},
{K::Number, L"title.rightEdgeGap", L"Right edge gap (px)", L"Space between the right window edge and the icon and title. 0 to 100 (Suggested: 8).", L"8", {}, 0, 100, 0, L"Icon and title"},
{K::Choice, L"title.hideMode", L"Hide icon or title", L"Choose what to hide in the title bar.", L"off", {{L"off", L"Show both"}, {L"icon", L"Hide the icon"}, {L"title", L"Hide the title"}, {L"both", L"Hide both"}}, 0, 100, 0, L"Icon and title"},
{K::Check, L"title.iconClickable", L"Icon opens the window menu", L"On = click opens the window menu and double-click closes. Off = the icon acts like empty title bar space.", L"1", {}, 0, 100, 0, L"Icon and title"},
{K::Text, L"titleFont.family", L"Font", L"Font name for title text, as Windows lists it. Empty = the Windows title font. Suggested: FiraCode Nerd Font.", L"FiraCode Nerd Font", {}, 0, 100, 0, L"Title font"},
{K::Choice, L"titleFont.weight", L"Font weight", L"Suggested: Medium.", L"500", {{L"default", L"Windows default"}, {L"300", L"Light"}, {L"400", L"Regular"}, {L"500", L"Medium"}, {L"600", L"Semibold"}, {L"700", L"Bold"}}, 0, 100, 0, L"Title font"},
{K::Check, L"titleDock.enabled", L"Dock behind the icon and title", L"A rounded box around the window icon and title, styled like the taskbar docks.", L"1", {}, 0, 100, 0, L"Title dock"},
{K::Number, L"titleDock.paddingX", L"Side padding (px)", L"Space between the dock edge and the icon or text. 0 to 30 (Suggested: 8).", L"8", {}, 0, 30, 0, L"Title dock"},
{K::Number, L"titleDock.paddingY", L"Top and bottom padding (px)", L"Gets smaller by itself in low title bars. 0 to 12 (Suggested: 4).", L"4", {}, 0, 12, 0, L"Title dock"},
{K::Number, L"titleDock.radius", L"Corner radius (px)", L"0 to 20 (Suggested: 8).", L"8", {}, 0, 20, 0, L"Title dock"},
{K::Number, L"titleDock.edgeWidth", L"Edge thickness (px)", L"Scales with the display. 1 to 4 (Suggested: 2).", L"2", {}, 1, 4, 0, L"Title dock"},
{K::Color, L"titleDock.fillColor", L"Fill colour", L"Hex colour. Suggested: #1E1E2E (Mocha base).", L"#1E1E2E", {}, 0, 100, 0, L"Title dock"},
{K::Check, L"titleDock.glassFill", L"Glass fill", L"On = frosted glass, the blurred title bar shows through the fill colour. Off = a solid fill at the opacity below.", L"1", {}, 0, 100, 0, L"Title dock"},
{K::Number, L"titleDock.glassTint", L"Glass tint (%)", L"How dark the glass is. 30 to 90 (Suggested: 60). Lower shows more blur.", L"60", {}, 30, 90, 0, L"Title dock"},
{K::Number, L"titleDock.fillOpacity", L"Fill opacity (%)", L"Used when Glass fill is off. 0 to 100 (Suggested: 100).", L"100", {}, 0, 100, 0, L"Title dock"},
{K::Check, L"titleDock.glassShine", L"Glass shine", L"A soft light along the top half of the dock, like the taskbar docks.", L"1", {}, 0, 100, 0, L"Title dock"},
{K::Color, L"titleDock.edgeColor", L"Edge colour", L"Hex colour. Suggested: #45475A (Mocha surface 1).", L"#45475A", {}, 0, 100, 0, L"Title dock"},
{K::Check, L"titleDock.hover", L"Gradient edge on hover", L"The edge fades into a gradient while the pointer is over the dock.", L"1", {}, 0, 100, 0, L"Title dock"},
{K::Color, L"titleDock.hoverStart", L"Hover gradient start", L"Hex colour, top left. Suggested: #89B4FA (Mocha blue).", L"#89B4FA", {}, 0, 100, 0, L"Title dock"},
{K::Color, L"titleDock.hoverEnd", L"Hover gradient end", L"Hex colour, bottom right. Suggested: #CBA6F7 (Mocha mauve).", L"#CBA6F7", {}, 0, 100, 0, L"Title dock"},
{K::Check, L"titleDock.middleClickClose", L"Middle-click closes the window", L"Middle-click the dock to close the window.", L"1", {}, 0, 100, 0, L"Title dock"},
{K::Check, L"titleDock.hoverFill", L"Fill brightens on hover", L"On = the dock's fill brightens while the pointer is over it.", L"1", {}, 0, 100, 0, L"Title dock"},
{K::Check, L"titleDock.rightClickMenu", L"Right-click menu", L"Right-click the dock for a menu: the app name, restore, minimize, maximize, always on top, copy title, copy all (title and uptime), the window menu, these settings and close.", L"1", {}, 0, 100, 0, L"Title dock"},
{K::Check, L"settingsGlass", L"Blurred settings window", L"On, the settings window is see-through glass with Windows acrylic behind it. Off, it is solid. Applies when you save.", L"1", {}, 0, 100, 0, L"Settings window"},
{K::Check, L"nativeSettingsTitleBar", L"Native Windows title bar", L"Use the Windows title bar and window buttons for this settings window. Applies when you save.", L"0", {}, 0, 100, 0, L"Settings window"},
{K::Check, L"settingsTrayIcon", L"Tray icon", L"Click it to open these settings. Right-click it to turn the dock, uptime or buttons on or off. When off, change settings in Windhawk.", L"1", {}, 0, 100, 0, L"Settings window"},
{K::Check, L"uptime.enabled", L"Show how long each window has been open", L"Adds a dot and the window's uptime after the title, for example: Notepad \u2022 1h 05m 12s.", L"1", {}, 0, 100, 1, L"Window uptime"},
{K::Check, L"uptime.showDays", L"Days", L"", L"1", {}, 0, 100, 1, L"Window uptime"},
{K::Check, L"uptime.showHours", L"Hours", L"", L"1", {}, 0, 100, 1, L"Window uptime"},
{K::Check, L"uptime.showMinutes", L"Minutes", L"", L"1", {}, 0, 100, 1, L"Window uptime"},
{K::Check, L"uptime.showSeconds", L"Seconds", L"A unit that is off rolls into the next smaller one that is on, for example 50h instead of 2d 2h.", L"1", {}, 0, 100, 1, L"Window uptime"},
{K::Choice, L"uptime.style", L"Style", L"", L"compact", {{L"compact", L"Compact: 2d 03h 05m 12s"}, {L"clock", L"Clock: 2d 3:05:12"}}, 0, 100, 1, L"Window uptime"},
{K::Text, L"uptime.separator", L"Separator", L"Text between the title and the uptime (Suggested: \u2022). Empty = a space only.", L"\u2022", {}, 0, 100, 1, L"Window uptime"},
{K::Text, L"uptime.color", L"Uptime colour", L"Hex colour for the separator and uptime. Suggested: #A6ADC8 (Mocha subtext 0). Empty = same as the title.", L"#A6ADC8", {}, 0, 100, 1, L"Window uptime"},
{K::Check, L"uptime.dialogs", L"Also in dialogs", L"Turn off to hide uptime on windows with only a close button.", L"1", {}, 0, 100, 1, L"Window uptime"},
{K::Check, L"colours.enabled", L"Turn on colours", L"Sets the title bar colour in apps that use the Windows title bar. When off, apps keep their own colours.", L"1", {}, 0, 100, 2, L"Colours"},
{K::Check, L"colours.useImmersiveDarkMode", L"Dark mode title bars", L"When on, title bars use the dark caption style.", L"1", {}, 0, 100, 2, L"Colours"},
{K::Color, L"colours.activeColor", L"Focused colour", L"Title bar colour of the focused window, as a hex colour like #1E1E2E.", L"#1E1E2E", {}, 0, 100, 2, L"Colours"},
{K::Color, L"colours.inactiveColor", L"Unfocused colour", L"Title bar colour of other windows, as a hex colour.", L"#1E1E2E", {}, 0, 100, 2, L"Colours"},
{K::Text, L"colours.excludedApps", L"Apps to leave alone", L"Process names separated by commas; * works as a wildcard. These apps keep their own title bar (blur, custom bar) instead of a flat colour.", L"Discord*.exe, ESDDiscord.exe, FreeDictate.exe, chrome.exe, WindowsTerminal.exe, devenv.exe, windhawk-ui.exe", {}, 0, 100, 2, L"Colours"},
{K::Check, L"buttons.enabled", L"Turn on caption buttons", L"When off, the buttons, icon and title keep the Windows layout everywhere.", L"1", {}, 0, 100, 2, L"Caption buttons"},
{K::Check, L"buttons.moveButtons", L"Move caption buttons to the left", L"On = the buttons move to the left side. Off = they stay on the right.", L"0", {}, 0, 100, 2, L"Caption buttons"},
{K::Number, L"buttons.leftMargin", L"Left margin (px)", L"Gap between the left window edge and the first button. 0 to 300 (Suggested: 0).", L"0", {}, 0, 300, 2, L"Caption buttons"},
{K::Number, L"buttons.buttonTighten", L"Tighten button spacing (px)", L"0 = normal spacing. Higher = buttons closer together, up to about 20. Meant for the circle and image styles.", L"0", {}, 0, 1000, 2, L"Caption buttons"},
{K::Choice, L"buttons.order", L"Button order", L"Order of the three buttons, counted from the left.", L"minMaxClose", {{L"closeMinMax", L"Close, minimize, maximize (macOS)"}, {L"closeMaxMin", L"Close, maximize, minimize"}, {L"minMaxClose", L"Minimize, maximize, close"}}, 0, 100, 2, L"Caption buttons"},
{K::Check, L"buttons.showDialogClose", L"Show the close button on dialogs", L"For windows that only have a close button. Off = the button is hidden; Alt+F4 and Esc still close the window.", L"1", {}, 0, 100, 2, L"Caption buttons"},
{K::Choice, L"buttonStyle.style", L"Button style", L"Windows = the normal glyphs. macOS = coloured circles. Custom images = your own images. Going back to Windows needs a sign out and in.", L"windows", {{L"macos", L"macOS circles"}, {L"custom", L"Custom images"}, {L"windows", L"Windows default"}}, 0, 100, 2, L"Button style"},
{K::Color, L"buttonStyle.minimizeColor", L"Minimize colour", L"Hex colour of the minimize circle, like #FEBC2E.", L"#FEBC2E", {}, 0, 100, 2, L"Button style"},
{K::Color, L"buttonStyle.maximizeColor", L"Maximize colour", L"Hex colour of the maximize and restore circle, like #28C840.", L"#28C840", {}, 0, 100, 2, L"Button style"},
{K::Color, L"buttonStyle.closeColor", L"Close colour", L"Hex colour of the close circle, like #FF5F57.", L"#FF5F57", {}, 0, 100, 2, L"Button style"},
{K::Text, L"buttonStyle.iconFolder", L"Image folder", L"Custom images style only. A folder with minimize, restore, maximize and close images (.png, .jpg, .bmp). Optional extras: close_hover, close_pressed, close_disabled.", L"", {}, 0, 100, 2, L"Button style"},
{K::Text, L"buttonStyle.minimizeIcon", L"Minimize image", L"Optional full path to an image. Overrides the folder for this button.", L"", {}, 0, 100, 2, L"Button style"},
{K::Text, L"buttonStyle.maximizeIcon", L"Maximize image", L"Optional full path to an image. Overrides the folder for this button.", L"", {}, 0, 100, 2, L"Button style"},
{K::Text, L"buttonStyle.restoreIcon", L"Restore image", L"Optional full path to an image, used while the window is maximized.", L"", {}, 0, 100, 2, L"Button style"},
{K::Text, L"buttonStyle.closeIcon", L"Close image", L"Optional full path to an image. Overrides the folder for this button.", L"", {}, 0, 100, 2, L"Button style"},
{K::Check, L"buttonStyle.restartDwmOnUnload", L"Restart dwm.exe when the mod unloads", L"Off (suggested): painted buttons stay until dwm.exe restarts. On: dwm.exe restarts when the mod unloads; the screen flickers once and apps stay open.", L"0", {}, 0, 100, 2, L"Button style"},
{K::Check, L"perApp.enabled", L"Turn on per-app settings", L"Rules below override the dock, title alignment and uptime for matching apps.", L"0", {}, 0, 100, 3, L"Per app"},
{K::Text, L"perApp.list", L"Rules", L"Each rule: app.exe dock=off align=left uptime=off. Separate rules with a semicolon. The first matching rule wins; * matches any app; skip a part to keep the general setting.", L"", {}, 0, 100, 3, L"Per app"},
{K::Text, L"exclusions.excludedApps", L"Apps that keep normal buttons", L"Process names separated by commas. Every window of these apps keeps the Windows button layout.", L"", {}, 0, 100, 3, L"Button exclusions"},
{K::Text, L"exclusions.excludedClasses", L"Window classes that keep normal buttons", L"Window class names separated by commas. CabinetWClass is File Explorer; remove it to move File Explorer's buttons too.", L"CabinetWClass", {}, 0, 100, 3, L"Button exclusions"},
{K::Check, L"explorerTabs.enabled", L"Clickable buttons in File Explorer", L"On = moved buttons can be clicked in File Explorer. Needs buttons on the left and CabinetWClass not excluded.", L"1", {}, 0, 100, 3, L"File Explorer tabs"},
{K::Number, L"explorerTabs.buttonsExtraMargin", L"Extra button margin in File Explorer (px)", L"Moves the buttons right in File Explorer only. -50 to 300 (Suggested: 5).", L"5", {}, -50, 300, 3, L"File Explorer tabs"},
{K::Number, L"explorerTabs.extraPx", L"Shift tab bar and toolbar (px)", L"0 = leave them in place. About 145 clears the three buttons. -300 to 300.", L"0", {}, 0, 1000, 3, L"File Explorer tabs"},
{K::Check, L"uwp.enabled", L"Turn on Store apps", L"Normal Windows title bars in Store apps like Settings and Calculator. Turning off puts open windows back the way they were.", L"1", {}, 0, 100, 3, L"Store apps"},
{K::Check, L"uwp.blur", L"Blur", L"Frosted blur title bars instead of a flat colour.", L"1", {}, 0, 100, 3, L"Store apps"},
{K::Number, L"uwp.tint", L"Tint strength", L"How much dark tint covers the blur. 0 to 100 (Suggested: 60).", L"60", {}, 0, 100, 3, L"Store apps"},
{K::Check, L"nativeFrames.enabled", L"Turn on native frames", L"The standard Windows title bar in browsers, Office, Visual Studio, Discord and similar apps. Changes need those apps restarted.", L"1", {}, 0, 100, 3, L"Native frames"},
{K::Text, L"nativeFrames.apps", L"Apps", L"Process names separated by commas; * works as a wildcard. Add steamwebhelper.exe for Steam.", L"chrome.exe, brave.exe, msedge.exe, opera.exe, yandex.exe, whale.exe, supermium.exe, chromium.exe, devenv.exe, PowerToys.*.exe, olk.exe, WebViewHost.exe, winword.exe, excel.exe, powerpnt.exe, msaccess.exe, onenote.exe, outlook.exe, mspub.exe, hwp.exe, Photos.exe, MuseScore*.exe, ms-teams.exe, Discord.exe, DiscordPTB.exe, DiscordCanary.exe, DiscordDevelopment.exe", {}, 0, 100, 3, L"Native frames"},
{K::Check, L"nativeFrames.buttonFaceChrome", L"Chromium - classic button face colour", L"Paints the classic Windows button face colour behind the Chromium title and tab bar. Needs DWM frames, hardware acceleration and 'Windows 11 Mica titlebar' in chrome://flags.", L"1", {}, 0, 100, 3, L"Native frames"},
{K::Choice, L"nativeFrames.clientEdge", L"Client edge", L"The thin sunken border around the window content.", L"remove", {{L"keep", L"Keep the app's choice"}, {L"add", L"Always show"}, {L"remove", L"Always hide"}}, 0, 100, 3, L"Native frames"},
{K::Check, L"nativeFrames.steamToolFrames", L"Steam - hide tool window frames", L"Removes the frames of Steam's small tool windows.", L"1", {}, 0, 100, 3, L"Native frames"},
{K::Check, L"nativeFrames.steamNoScriptInject", L"Steam - turn off script injection", L"Only turn on for the Change Window Parameters Millennium extension. Needs a Steam restart.", L"1", {}, 0, 100, 3, L"Native frames"},
{K::Check, L"spotify.enabled", L"Turn on Spotify", L"Native frames and tweaks for Spotify. Options marked with * need a Spotify restart.", L"1", {}, 0, 100, 3, L"Spotify"},
{K::Check, L"spotify.showframe", L"Native frame on the main window*", L"Needs a Spotify restart.", L"1", {}, 0, 100, 3, L"Spotify"},
{K::Check, L"spotify.showframeonothers", L"Native frames on other windows", L"Miniplayer, DevTools and similar windows.", L"1", {}, 0, 100, 3, L"Spotify"},
{K::Check, L"spotify.showmenu", L"Show the menu button*", L"When off, the Alt key no longer opens the Spotify menu either.", L"1", {}, 0, 100, 3, L"Spotify"},
{K::Check, L"spotify.showcontrols", L"Show Spotify's own window buttons*", L"The buttons Spotify draws next to its title bar.", L"0", {}, 0, 100, 3, L"Spotify"},
{K::Check, L"spotify.transparentcontrols", L"Transparent Spotify window buttons", L"Makes Spotify's own window buttons see-through.", L"1", {}, 0, 100, 3, L"Spotify"},
{K::Check, L"spotify.transparentrendering", L"Transparent rendering*", L"Makes see-through parts of the page really see-through. Needs the Chrome runtime.", L"1", {}, 0, 100, 3, L"Spotify"},
{K::Check, L"spotify.noforceddarkmode", L"Turn off forced dark mode*", L"Stops Spotify from forcing dark mode.", L"0", {}, 0, 100, 3, L"Spotify"},
{K::Check, L"spotify.forceextensions", L"Force Chrome extensions*", L"Always turns on Chrome extensions. Needs the Chrome runtime.", L"1", {}, 0, 100, 3, L"Spotify"},
{K::Check, L"spotify.blockupdates", L"Block automatic updates*", L"Stops Spotify from updating itself.", L"0", {}, 0, 100, 3, L"Spotify"},
{K::Check, L"spotify.ignoreminsize", L"Ignore minimum window size", L"Lets the window shrink below Spotify's minimum size.", L"1", {}, 0, 100, 3, L"Spotify"},
{K::Text, L"spotify.playbackspeed", L"(Old) Playback speed", L"A number like 1.0. Only works on x64 Spotify 1.2.36 to 1.2.66.", L"1", {}, 0, 100, 3, L"Spotify"},
{K::Check, L"spotify.allowuntested", L"(Advanced) Unsafe methods on untested versions*", L"May crash Spotify. When off, a slower safe method is used.", L"0", {}, 0, 100, 3, L"Spotify"},
{K::Check, L"terminalBar.enabled", L"Turn on Terminal bar", L"Gives the Windows Terminal title bar the same blur as its window. Needs Terminal's own title bar (Show tabs in the title bar off).", L"1", {}, 0, 100, 3, L"Terminal bar"},
{K::Color, L"terminalBar.tint", L"Tint colour", L"Colour mixed into the blur, like #1e1e2e. Use your Terminal background colour.", L"#1e1e2e", {}, 0, 100, 3, L"Terminal bar"},
{K::Number, L"terminalBar.opacity", L"Tint opacity", L"How strong the tint is. 0 to 100 (Suggested: match Terminal's opacity).", L"85", {}, 0, 100, 3, L"Terminal bar"},
{K::Check, L"hungDialog.enabled", L"Turn on system boxes", L"Gives the Windows \"is not responding\" box and system error boxes a dark title and the system blur.", L"1", {}, 0, 100, 3, L"System boxes"},
{K::Check, L"basicFrames.enabled", L"Turn on basic frames", L"Fixes caption text colours on windows without DWM frames (classic themes, ribbon text). Off by default: on some Windows builds the parts it needs are missing, and then it simply stays inactive.", L"0", {}, 0, 100, 3, L"Basic frames"},
{K::Check, L"basicFrames.smallIcons", L"Small window icons", L"Uses the small icon on basic frames instead of shrinking the large one.", L"1", {}, 0, 100, 3, L"Basic frames"},
{K::Check, L"debugLog", L"Write debug log", L"Extra caption button messages in the Windhawk log. Turn on logging for this mod to see them.", L"0", {}, 0, 100, 3, L"Advanced"}
    };
}

struct SetPageInfo {
    PCWSTR name, intro;
    WCHAR glyph;
};
static const SetPageInfo kSetPages[] = {
{L"Look", L"Icon and title, title font, the dock and this window.", 0xE790},
{L"Uptime", L"How long each window has been open, after its title.", 0xE916},
{L"Colours and buttons", L"Title bar colours and the caption buttons.", 0xE771},
{L"Apps", L"Per-app settings, store apps, native frames, File Explorer, Spotify and Terminal.", 0xE71D},
{L"About", L"Version, credits, support and links.", 0xE946},
};
constexpr int kSetPageCount = (int)(sizeof(kSetPages) / sizeof(kSetPages[0]));
// About sits apart at the end of the sidebar, as in Seamless Dictate.
constexpr int kSetAboutPage = kSetPageCount - 1;
constexpr float kSetAboutGap = 17;

// All sizes are DIPs; the render target does the scaling.
constexpr float kSetPadX = 40, kSetMaxW = 720, kSetRowMin = 56, kSetRowGap = 8, kSetBoxH = 32, kSetRowPad = 16,
                kSetDropItem = 32, kSetRailTop = 76, kSetRailItem = 36, kSetRailPitch = 40;
constexpr int kSetDropMax = 9;  // A dropdown with more options than this scrolls.
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
constexpr PCWSTR kSetDittoUrl = L"https://github.com/DavidHiFi/davids-windhawk-mods";
constexpr PCWSTR kSetRepoUrl = L"https://github.com/DavidHiFi/davids-windhawk-mods";
constexpr PCWSTR kSetBugUrl =
    L"https://github.com/DavidHiFi/davids-windhawk-mods/issues/new?title=%5BSeamless%20Title%20Bars%5D%20";
constexpr PCWSTR kSetTitle = L"Seamless Title Bars";
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
        if (w.fRailName && Set_TextW(w.fRailName.get(), L"Title Bars") <= railW) break;
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

// Boxes grow to fit their text, so no option, hotkey or value is ever cut off: a choice box fits
// its longest option, a hotkey or text box its value. A box never takes more than half the row;
// past that the dropdown list still shows every option in full. Text is measured only when it
// changes. Returns true when a width changed, so the page is laid out again.
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

// ---- Layout -----------------------------------------------------------------

// The right-hand control's width, so the label column knows how much room it has.
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
        float textW = w.contentW - 2 * kSetRowPad - Set_ControlW(f) - 24;
        float lh = Set_TextH(w.fLabel.get(), f.label, textW);
        float dh = f.desc ? Set_TextH(w.fHint.get(), f.desc, textW) + 3 : 0;
        it.y = y;
        it.h = std::max(kSetRowMin, 28 + lh + dh);
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
        add(SetItem::About, 146, L"", L"", L"");
        add(SetItem::Support, 84, L"Like it? Help the mod keep going.",
            L"Free and open source. A tip on Ko-fi keeps it moving.", kSetKofiUrl);
        group(L"Author");
        add(SetItem::Link, 56, L"DavidHiFi on GitHub", L"github.com/DavidHiFi", kSetAuthorUrl);
        add(SetItem::Link, 56, L"Ko-fi", L"ko-fi.com/DavidHiFi", kSetKofiUrl);
        group(L"Credits");
        add(SetItem::Link, 56, L"Source and credits", L"The six mods this one merges, and their authors", kSetDittoUrl);
        group(L"Project");
        add(SetItem::Link, 56, L"Project page on GitHub", L"github.com/DavidHiFi/davids-windhawk-mods", kSetRepoUrl);
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
    p.GradFill(mark, 18, 1);
    p.Glyph(w.fIconL.get(), 0xE922, mark, mocha::crust);
    float x = mark.right + 20;
    p.Text(w.fBig.get(), L"Seamless Title Bars", {x, row.top + 18, row.right - 16, row.top + 46}, mocha::text);
#ifdef WH_MOD_VERSION
    std::wstring ver = std::wstring(L"Version ") + WH_MOD_VERSION + L"  \u00B7  MIT license  \u00B7  A Windhawk mod";
#else
    std::wstring ver = L"MIT license  \u00B7  A Windhawk mod";
#endif
    p.Text(w.fHint.get(), ver, {x, row.top + 48, row.right - 16, row.top + 68}, mocha::subtext0);
    p.Text(w.fHint.get(), L"One title bar look everywhere: colours, caption buttons, a glass dock and native frames.",
           {x, row.top + 72, row.right - 16, row.top + 110}, mocha::subtext1);
    p.Text(w.fHint.get(), L"Made by DavidHiFi, with code from Th3Fanbus, grn15RenS, Ingan121, Anixx and aubymori.",
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
    p.Text(w.fRailName.get(), L"Title Bars", {d.left + 90, d.top + 32, d.left + w.railW - 10, d.top + 56}, mocha::text, textA);
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


// Every scrollbar thumb in every mod: a top to bottom blue to mauve gradient, brighter while
// hovered or dragged. Never a flat grey thumb.
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

// Keeps option i inside the visible part of a scrolling dropdown.
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
    p.Glyph(glyph, 0xE922, r, mocha::crust);
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

// A switch's stored value, found by the end of its key so a "SettingsWindow." prefix still matches.
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

// "Native Windows title bar" and "Blurred settings window", applied to the live window: on first
// open and again whenever a save or a reload changes them, so neither needs a reopen.
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
    HWND hwnd = CreateWindowExW(0, kSettingsClass, L"Seamless Title Bars settings", style,
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
}  // namespace stbset

// ==========================================================================
//  Tool process (windhawk.exe): tray icon, the dock's right-click menu, and
//  the title font file that dwm.exe can read.
// ==========================================================================
// ==========================================================================
//  Dark titles and see-through system boxes, from the tool process
// ==========================================================================
// dwm.exe cannot change these for another process's window in a way that shows, but any
// normal process can ask DWM for them. Calls here never wait on the target window's thread.
namespace darkall {
DWORD g_csrss = 0;
HWINEVENTHOOK g_hook = nullptr;

int Mode() { return Wh_GetIntValue(L"sysbox.mode", 15); }

bool IsCsrssBox(HWND h, DWORD pid) {
    if (!g_csrss || pid != g_csrss) return false;
    wchar_t cls[16] = L"";
    return GetClassNameW(h, cls, 16) && wcscmp(cls, L"#32770") == 0;
}

void Apply(HWND h, int mode) {
    if (!h || GetAncestor(h, GA_ROOT) != h || !IsWindowVisible(h)) return;
    DWORD pid = 0;
    GetWindowThreadProcessId(h, &pid);
    if (!pid || pid == GetCurrentProcessId()) return;
    if (IsCsrssBox(h, pid)) {
        BOOL dark = TRUE;
        if (mode & 1) DwmSetWindowAttribute(h, 20 /* DWMWA_USE_IMMERSIVE_DARK_MODE */, &dark, sizeof(dark));
        if (mode & 4) {
            // The box paints its body black; with blur-behind black shows the backdrop.
            DWM_BLURBEHIND bb{DWM_BB_ENABLE, TRUE, nullptr, FALSE};
            DwmEnableBlurBehindWindow(h, &bb);
            RedrawWindow(h, nullptr, nullptr, RDW_INVALIDATE | RDW_ERASE | RDW_ALLCHILDREN);
        }
        return;
    }
    if (!(mode & 8)) return;
    if ((GetWindowLongPtrW(h, GWL_STYLE) & WS_CAPTION) != WS_CAPTION) return;
    BOOL dark = TRUE;
    DwmSetWindowAttribute(h, 20, &dark, sizeof(dark));
}

BOOL CALLBACK Sweep(HWND h, LPARAM mode) {
    Apply(h, (int)mode);
    return TRUE;
}

void CALLBACK OnShow(HWINEVENTHOOK, DWORD, HWND h, LONG obj, LONG child, DWORD, DWORD) {
    if (obj != OBJID_WINDOW || child != CHILDID_SELF || !h) return;
    if (GetAncestor(h, GA_ROOT) != h) return;
    Apply(h, Mode());
}

void Start() {
    if (g_hook) return;
    auto csrPid = (HANDLE(NTAPI*)())GetProcAddress(GetModuleHandleW(L"ntdll.dll"), "CsrGetProcessId");
    g_csrss = csrPid ? (DWORD)(ULONG_PTR)csrPid() : 0;
    g_hook = SetWinEventHook(EVENT_OBJECT_SHOW, EVENT_OBJECT_SHOW, nullptr, OnShow, 0, 0,
                             WINEVENT_OUTOFCONTEXT | WINEVENT_SKIPOWNPROCESS);
    EnumWindows(Sweep, Mode());
    Wh_Log(L"[DarkAll] hook %p, csrss %lu", g_hook, g_csrss);
}

void Stop() {
    if (g_hook) UnhookWinEvent(g_hook);
    g_hook = nullptr;
}
}  // namespace darkall

namespace stbtool {

constexpr UINT WM_STB_TRAY = WM_APP + 10;
constexpr UINT WM_STB_SETTINGS = WM_APP + 11;
constexpr UINT WM_STB_DOCKMENU = WM_APP + 12;   // wParam = window, lParam = screen point
constexpr UINT WM_STB_TESTMENU = WM_APP + 13;   // same, closes itself after 6 s (for checks)
constexpr UINT WM_STB_DOCKCLOSE = WM_APP + 14;  // wParam = window: close it (middle-click on the dock)
constexpr UINT WM_STB_TESTCLOSE = WM_APP + 15;  // wParam = window: close it (for checks)
constexpr UINT WM_STB_TESTCOPY = WM_APP + 16;   // wParam = window: copy title + uptime (for checks)
constexpr UINT kTrayId = 1;
constexpr UINT_PTR kTimerEndMenu = 3;

struct ToolSettings {
    bool tray = true, dock = true, dockMenu = true, midClose = true, buttons = true, uptime = true;
};
static ToolSettings g_ts;
static HWND g_wnd;
static HANDLE g_thread, g_ready;
static DWORD g_tid;
static UINT g_taskbarCreated;
static bool g_trayAdded;
static HICON g_trayIcon;
static HHOOK g_mouseHook;
static volatile LONG g_menuOpen;
static bool g_swallowUp;
static POINT g_downPt;
static HWND g_downWnd;
static bool g_midDown;
static HWND g_midWnd;
static std::atomic<int> g_saveThreads{0};
static HANDLE g_singleInstance;

static void LoadToolSettings() {
    ToolSettings s;
    s.tray = Wh_GetIntSetting(L"settingsTrayIcon") != 0;
    s.dock = Wh_GetIntSetting(L"titleDock.enabled") != 0;
    s.dockMenu = Wh_GetIntSetting(L"titleDock.rightClickMenu") != 0;
    s.midClose = Wh_GetIntSetting(L"titleDock.middleClickClose") != 0;
    s.buttons = Wh_GetIntSetting(L"buttons.enabled") != 0;
    s.uptime = Wh_GetIntSetting(L"uptime.enabled") != 0;
    g_ts = s;
}

static void EnableDarkMenus() {
    HMODULE ux = GetModuleHandleW(L"uxtheme.dll");
    if (!ux) ux = LoadLibraryExW(L"uxtheme.dll", nullptr, LOAD_LIBRARY_SEARCH_SYSTEM32);
    if (!ux) return;
    using SetMode = int(WINAPI*)(int);
    using Flush = void(WINAPI*)();
    if (auto set = (SetMode)GetProcAddress(ux, MAKEINTRESOURCEA(135))) set(2 /* ForceDark */);
    if (auto flush = (Flush)GetProcAddress(ux, MAKEINTRESOURCEA(136))) flush();
}

// ---- Saving one or two settings from the tray menu (same path as the settings window) ----
struct SaveJob {
    std::wstring params;
};

static DWORD WINAPI SaveThread(LPVOID param) {
    std::unique_ptr<SaveJob> job((SaveJob*)param);
    std::wstring cli = stbset::Set_CliPath();
    if (cli.empty()) {
        Wh_Log(L"windhawk-cli.exe not found, setting not saved");
    } else {
        SHELLEXECUTEINFOW sei{sizeof(sei)};
        sei.fMask = SEE_MASK_NOCLOSEPROCESS | SEE_MASK_FLAG_NO_UI | SEE_MASK_NOASYNC;
        sei.lpVerb = L"runas";
        sei.lpFile = cli.c_str();
        sei.lpParameters = job->params.c_str();
        sei.nShow = SW_HIDE;
        if (ShellExecuteExW(&sei) && sei.hProcess) {
            if (WaitForSingleObject(sei.hProcess, 15000) == WAIT_TIMEOUT) {
                TerminateProcess(sei.hProcess, 1);
                Wh_Log(L"windhawk-cli timed out and was stopped");
            }
            CloseHandle(sei.hProcess);
        } else {
            Wh_Log(L"Couldn't start windhawk-cli (error %lu)", GetLastError());
        }
    }
    g_saveThreads--;
    return 0;
}

static void SaveSettingsAsync(const std::vector<std::pair<std::wstring, std::wstring>>& kv) {
    auto* job = new SaveJob;
    job->params = L"--quiet mod settings set " + stbset::Set_QuoteArg(WH_MOD_ID);
    for (auto& [k, v] : kv) job->params += L" " + stbset::Set_QuoteArg(k + L"=" + v);
    g_saveThreads++;
    HANDLE t = CreateThread(nullptr, 0, SaveThread, job, 0, nullptr);
    if (t) CloseHandle(t);
    else {
        g_saveThreads--;
        delete job;
    }
}

// ---- Tray icon: the title bar glyph on the blue to mauve rounded square ----
static HICON MakeTrayIcon() {
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
    HFONT font = CreateFontW(-(int)(size * 0.62f), 0, 0, 0, FW_NORMAL, 0, 0, 0, DEFAULT_CHARSET, 0, 0,
                             ANTIALIASED_QUALITY, 0, L"Segoe Fluent Icons");
    HGDIOBJ oldFont = SelectObject(dc, font);
    WCHAR face[64]{};
    GetTextFaceW(dc, 64, face);
    if (_wcsicmp(face, L"Segoe Fluent Icons") != 0) {
        SelectObject(dc, oldFont);
        DeleteObject(font);
        font = CreateFontW(-(int)(size * 0.62f), 0, 0, 0, FW_NORMAL, 0, 0, 0, DEFAULT_CHARSET, 0, 0,
                           ANTIALIASED_QUALITY, 0, L"Segoe MDL2 Assets");
        oldFont = SelectObject(dc, font);
    }
    SetBkMode(dc, TRANSPARENT);
    SetTextColor(dc, RGB(255, 255, 255));
    RECT r{0, 0, size, size};
    WCHAR g[2] = {(WCHAR)0xE922, 0};   // Maximize: a window with its title bar
    DrawTextW(dc, g, 1, &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE | DT_NOPREFIX);
    GdiFlush();
    SelectObject(dc, oldFont);
    DeleteObject(font);
    SelectObject(dc, old);
    DeleteDC(dc);

    const float c0[3] = {0x89 / 255.f, 0xB4 / 255.f, 0xFA / 255.f};
    const float c1[3] = {0xCB / 255.f, 0xA6 / 255.f, 0xF7 / 255.f};
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
    NOTIFYICONDATAW nid{sizeof(nid)};
    nid.hWnd = g_wnd;
    nid.uID = kTrayId;
    if (!g_ts.tray) {
        if (g_trayAdded) Shell_NotifyIconW(NIM_DELETE, &nid);
        g_trayAdded = false;
        return;
    }
    if (g_trayAdded && !add) return;   // nothing in the icon changes with settings
    HICON icon = MakeTrayIcon();
    nid.uFlags = NIF_MESSAGE | NIF_ICON | NIF_TIP | NIF_SHOWTIP;
    nid.uCallbackMessage = WM_STB_TRAY;
    nid.hIcon = icon ? icon : LoadIconW(nullptr, IDI_APPLICATION);
    wcsncpy_s(nid.szTip, L"Seamless Title Bars", _TRUNCATE);
    if (g_trayAdded) Shell_NotifyIconW(NIM_DELETE, &nid);
    g_trayAdded = Shell_NotifyIconW(NIM_ADD, &nid) != FALSE;
    if (g_trayAdded) {
        nid.uVersion = NOTIFYICON_VERSION_4;
        Shell_NotifyIconW(NIM_SETVERSION, &nid);
    }
    if (g_trayIcon) DestroyIcon(g_trayIcon);
    g_trayIcon = icon;
}

enum : UINT { IDM_DOCK = 100, IDM_UPTIME, IDM_BUTTONS, IDM_SETTINGS };

static void ShowTrayMenu(POINT pt) {
    // The engine's own menu (Set_TrayMenu), rows in the order they always had.
    std::vector<stbset::SetMenuItem> rows;
    rows.push_back(stbset::Set_MenuRow(IDM_DOCK, L"\uE922", L"Title dock", g_ts.dock));
    rows.push_back(stbset::Set_MenuRow(IDM_UPTIME, L"\uE916", L"Window uptime", g_ts.uptime));
    rows.push_back(stbset::Set_MenuRow(IDM_BUTTONS, L"\uE771", L"Caption buttons", g_ts.buttons));
    rows.push_back(stbset::Set_MenuSep());
    rows.push_back(stbset::Set_MenuRow(IDM_SETTINGS, L"\uEB51", L"Settings"));
    InterlockedExchange(&g_menuOpen, 1);
    UINT cmd = (UINT)stbset::Set_TrayMenu(g_wnd, rows, &pt);
    InterlockedExchange(&g_menuOpen, 0);
    if (cmd == IDM_DOCK) {
        g_ts.dock = !g_ts.dock;
        SaveSettingsAsync({{L"titleDock.enabled", g_ts.dock ? L"1" : L"0"}});
    } else if (cmd == IDM_UPTIME) {
        g_ts.uptime = !g_ts.uptime;
        SaveSettingsAsync({{L"uptime.enabled", g_ts.uptime ? L"1" : L"0"}});
    } else if (cmd == IDM_BUTTONS) {
        g_ts.buttons = !g_ts.buttons;
        SaveSettingsAsync({{L"buttons.enabled", g_ts.buttons ? L"1" : L"0"}});
    } else if (cmd == IDM_SETTINGS) {
        stbset::OpenSettingsWindow();
    }
}

// ---- The dock's right-click menu ----
// dwm.exe writes which dock the pointer is on; a right click there opens this menu
// instead of the plain window menu (which stays one click away in it).
static HWND HitDockPt(POINT pt) {
    stbshared::Snap s;
    if (!stbshared::Read(s) || !s.hwnd) return nullptr;
    if (GetTickCount64() - s.tick > 1500) return nullptr;
    if (s.r <= s.l || s.band <= 0) return nullptr;
    if (!IsWindow(s.hwnd) || IsHungAppWindow(s.hwnd)) return nullptr;
    RECT wr;
    if (!GetWindowRect(s.hwnd, &wr)) return nullptr;
    int x = pt.x - wr.left, y = pt.y - wr.top;
    if (x < s.l || x >= s.r || y < 0 || y > s.band) return nullptr;
    HWND under = WindowFromPoint(pt);
    if (!under || GetAncestor(under, GA_ROOT) != s.hwnd) return nullptr;
    return s.hwnd;
}

static HWND HitDock(POINT pt) {
    if (!g_ts.dock || !g_ts.dockMenu || g_menuOpen) return nullptr;
    return HitDockPt(pt);
}

static HWND HitDockMid(POINT pt) {
    if (!g_ts.dock || !g_ts.midClose || g_menuOpen) return nullptr;
    return HitDockPt(pt);
}

static LRESULT CALLBACK MouseHook(int code, WPARAM wp, LPARAM lp) {
    if (code == HC_ACTION) {
        const MSLLHOOKSTRUCT* m = (const MSLLHOOKSTRUCT*)lp;
        if (!(m->flags & LLMHF_INJECTED)) {
            if (wp == WM_RBUTTONDOWN) {
                if (HWND h = HitDock(m->pt)) {
                    g_swallowUp = true;
                    g_downPt = m->pt;
                    g_downWnd = h;
                    return 1;
                }
            } else if (wp == WM_RBUTTONUP && g_swallowUp) {
                g_swallowUp = false;
                PostMessageW(g_wnd, WM_STB_DOCKMENU, (WPARAM)g_downWnd, MAKELPARAM(g_downPt.x, g_downPt.y));
                return 1;
            } else if (wp == WM_MBUTTONDOWN) {
                // Middle-click on the dock closes the window (on the release, like the right click).
                if (HWND h = HitDockMid(m->pt)) {
                    g_midDown = true;
                    g_midWnd = h;
                    return 1;
                }
            } else if (wp == WM_MBUTTONUP && g_midDown) {
                g_midDown = false;
                PostMessageW(g_wnd, WM_STB_DOCKCLOSE, (WPARAM)g_midWnd, 0);
                return 1;
            }
        }
    }
    return CallNextHookEx(nullptr, code, wp, lp);
}

static void UpdateMouseHook() {
    bool want = g_ts.dock && (g_ts.dockMenu || g_ts.midClose);
    if (want && !g_mouseHook) {
        g_mouseHook = SetWindowsHookExW(WH_MOUSE_LL, MouseHook, (HINSTANCE)&__ImageBase, 0);
        if (!g_mouseHook) Wh_Log(L"[Menu] mouse hook failed (%lu)", GetLastError());
    } else if (!want && g_mouseHook) {
        UnhookWindowsHookEx(g_mouseHook);
        g_mouseHook = nullptr;
        g_swallowUp = false;
        g_midDown = false;
    }
}

enum : UINT {
    IDM_RESTORE = 200, IDM_MINIMIZE, IDM_MAXIMIZE, IDM_TOPMOST, IDM_COPYTITLE, IDM_COPYALL, IDM_SYSMENU,
    IDM_TBSETTINGS, IDM_CLOSE,
};

static void CopyText(const std::wstring& text) {
    if (!OpenClipboard(g_wnd)) return;
    EmptyClipboard();
    size_t bytes = (text.size() + 1) * sizeof(wchar_t);
    if (HGLOBAL mem = GlobalAlloc(GMEM_MOVEABLE, bytes)) {
        if (void* p = GlobalLock(mem)) {
            memcpy(p, text.c_str(), bytes);
            GlobalUnlock(mem);
            if (!SetClipboardData(CF_UNICODETEXT, mem)) GlobalFree(mem);
        } else {
            GlobalFree(mem);
        }
    }
    CloseClipboard();
}

// Copy all: the title plus the uptime suffix DWM shows on this window's dock.
static void CopyAllText(HWND target) {
    if (!target || !IsWindow(target)) return;
    wchar_t title[512] = {};
    GetWindowTextW(target, title, 512);
    std::wstring text = title;
    stbshared::Snap s;
    if (stbshared::Read(s) && s.hwnd == target && s.suf[0]) text += s.suf;
    CopyText(text);
    SetForegroundWindow(target);
}

static void ShowDockMenu(HWND target, POINT pt, bool test) {
    if (!target || !IsWindow(target)) return;
    LONG style = GetWindowLongW(target, GWL_STYLE), ex = GetWindowLongW(target, GWL_EXSTYLE);
    bool iconic = IsIconic(target), zoomed = IsZoomed(target);
    bool canMin = (style & WS_MINIMIZEBOX) && !iconic, canMax = (style & WS_MAXIMIZEBOX) && !zoomed;
    bool topmost = (ex & WS_EX_TOPMOST) != 0;
    wchar_t title[512] = {};
    GetWindowTextW(target, title, 512);

    // Header: the app's name (exe basename); fall back to the window class.
    wchar_t header[128] = L"";
    {
        DWORD pid = 0;
        GetWindowThreadProcessId(target, &pid);
        wchar_t exe[128] = L"";
        if (pid && caption::GetExeNameForPid(pid, exe, 128)) {
            const wchar_t* base = wcsrchr(exe, L'\\');
            wcsncpy_s(header, base ? base + 1 : exe, _TRUNCATE);
        }
        if (!header[0]) GetClassNameW(target, header, 128);
    }
    bool canCopyAll = title[0] != 0;
    {
        stbshared::Snap s;
        if (stbshared::Read(s) && s.hwnd == target && s.suf[0]) canCopyAll = true;
    }

    HMENU menu = CreatePopupMenu();
    AppendMenuW(menu, MF_STRING | MF_GRAYED, 0, header[0] ? header : L"Window");
    AppendMenuW(menu, MF_SEPARATOR, 0, nullptr);
    AppendMenuW(menu, MF_STRING | ((iconic || zoomed) ? 0 : MF_GRAYED), IDM_RESTORE, L"Restore");
    AppendMenuW(menu, MF_STRING | (canMin ? 0 : MF_GRAYED), IDM_MINIMIZE, L"Minimize");
    AppendMenuW(menu, MF_STRING | (canMax ? 0 : MF_GRAYED), IDM_MAXIMIZE, L"Maximize");
    AppendMenuW(menu, MF_SEPARATOR, 0, nullptr);
    AppendMenuW(menu, MF_STRING | (topmost ? MF_CHECKED : 0), IDM_TOPMOST, L"Always on top");
    AppendMenuW(menu, MF_STRING | (title[0] ? 0 : MF_GRAYED), IDM_COPYTITLE, L"Copy title");
    AppendMenuW(menu, MF_STRING | (canCopyAll ? 0 : MF_GRAYED), IDM_COPYALL, L"Copy all");
    AppendMenuW(menu, MF_STRING, IDM_SYSMENU, L"Window menu");
    AppendMenuW(menu, MF_SEPARATOR, 0, nullptr);
    AppendMenuW(menu, MF_STRING, IDM_TBSETTINGS, L"Title bar settings");
    AppendMenuW(menu, MF_SEPARATOR, 0, nullptr);
    AppendMenuW(menu, MF_STRING, IDM_CLOSE, L"Close\tAlt+F4");

    InterlockedExchange(&g_menuOpen, 1);
    stbset::ForceForeground(g_wnd);
    if (test) SetTimer(g_wnd, kTimerEndMenu, 6000, nullptr);
    UINT cmd = TrackPopupMenuEx(menu, TPM_RETURNCMD | TPM_NONOTIFY | TPM_RIGHTBUTTON |
                                          (GetSystemMetrics(SM_MENUDROPALIGNMENT) ? TPM_RIGHTALIGN : TPM_LEFTALIGN),
                                pt.x, pt.y, g_wnd, nullptr);
    KillTimer(g_wnd, kTimerEndMenu);
    PostMessageW(g_wnd, WM_NULL, 0, 0);
    InterlockedExchange(&g_menuOpen, 0);
    DestroyMenu(menu);
    if (!IsWindow(target)) return;
    if (cmd != IDM_TBSETTINGS && cmd != IDM_COPYTITLE && cmd != IDM_COPYALL) SetForegroundWindow(target);
    switch (cmd) {
        case IDM_RESTORE: PostMessageW(target, WM_SYSCOMMAND, SC_RESTORE, 0); break;
        case IDM_MINIMIZE: PostMessageW(target, WM_SYSCOMMAND, SC_MINIMIZE, 0); break;
        case IDM_MAXIMIZE: PostMessageW(target, WM_SYSCOMMAND, SC_MAXIMIZE, 0); break;
        case IDM_TOPMOST:
            SetWindowPos(target, topmost ? HWND_NOTOPMOST : HWND_TOPMOST, 0, 0, 0, 0,
                         SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
            break;
        case IDM_COPYTITLE:
            CopyText(title);
            SetForegroundWindow(target);
            break;
        case IDM_COPYALL:
            CopyAllText(target);
            break;
        case IDM_SYSMENU: PostMessageW(target, 0x0313 /* WM_SYSMENU */, 0, MAKELPARAM(pt.x, pt.y)); break;
        case IDM_TBSETTINGS: stbset::OpenSettingsWindow(); break;
        case IDM_CLOSE: PostMessageW(target, WM_SYSCOMMAND, SC_CLOSE, 0); break;
        default: break;   // dismissed: the window got its focus back above
    }
}

// ---- Title font file: a copy dwm.exe can read ----
// DWM runs as its own user, so a font installed only for this user (in the user's
// AppData) is invisible to it. Fonts in the Windows Fonts folder are used in place;
// anything else is copied into the mod's storage folder, readable by everyone.
static std::wstring FontFilePath(const stbshared::FontPick& pick, bool& found) {
    found = false;
    std::wstring out;
    if (!pick.family[0]) return out;
    IDWriteFactory* f = nullptr;
    if (FAILED(DWriteCreateFactory(DWRITE_FACTORY_TYPE_ISOLATED, __uuidof(IDWriteFactory), (IUnknown**)&f)) || !f)
        return out;
    IDWriteFontCollection* coll = nullptr;
    IDWriteFontFamily* fam = nullptr;
    IDWriteFont* font = nullptr;
    IDWriteFontFace* face = nullptr;
    // Typographic families keep every weight together (Medium is not a family of its own).
    IDWriteFactory6* f6 = nullptr;
    if (SUCCEEDED(f->QueryInterface(__uuidof(IDWriteFactory6), (void**)&f6)) && f6) {
        IDWriteFontCollection2* c2 = nullptr;
        if (SUCCEEDED(f6->GetSystemFontCollection(FALSE, DWRITE_FONT_FAMILY_MODEL_TYPOGRAPHIC, &c2)) && c2) coll = c2;
        f6->Release();
    }
    UINT32 idx = 0;
    BOOL exists = FALSE;
    if (coll && (FAILED(coll->FindFamilyName(pick.family, &idx, &exists)) || !exists)) {
        coll->Release();
        coll = nullptr;
    }
    if (!coll) {
        if (FAILED(f->GetSystemFontCollection(&coll, TRUE)) || !coll ||
            FAILED(coll->FindFamilyName(pick.family, &idx, &exists)) || !exists) {
            if (coll) coll->Release();
            f->Release();
            return out;
        }
    }
    if (SUCCEEDED(coll->GetFontFamily(idx, &fam)) && fam &&
        SUCCEEDED(fam->GetFirstMatchingFont((DWRITE_FONT_WEIGHT)(pick.weight ? pick.weight : 400),
                                            DWRITE_FONT_STRETCH_NORMAL, DWRITE_FONT_STYLE_NORMAL, &font)) &&
        font && SUCCEEDED(font->CreateFontFace(&face)) && face) {
        UINT32 n = 1;
        IDWriteFontFile* file = nullptr;
        if (SUCCEEDED(face->GetFiles(&n, &file)) && file) {
            const void* key = nullptr;
            UINT32 keySize = 0;
            IDWriteFontFileLoader* loader = nullptr;
            IDWriteLocalFontFileLoader* local = nullptr;
            if (SUCCEEDED(file->GetReferenceKey(&key, &keySize)) && SUCCEEDED(file->GetLoader(&loader)) && loader &&
                SUCCEEDED(loader->QueryInterface(__uuidof(IDWriteLocalFontFileLoader), (void**)&local)) && local) {
                UINT32 len = 0;
                if (SUCCEEDED(local->GetFilePathLengthFromKey(key, keySize, &len)) && len < 4096) {
                    std::wstring path(len + 1, L'\0');
                    if (SUCCEEDED(local->GetFilePathFromKey(key, keySize, path.data(), len + 1))) {
                        path.resize(len);
                        out = path;
                        found = true;
                    }
                }
                local->Release();
            }
            if (loader) loader->Release();
            file->Release();
        }
    }
    if (face) face->Release();
    if (font) font->Release();
    if (fam) fam->Release();
    coll->Release();
    f->Release();
    return out;
}

static bool UnderWindowsFonts(const std::wstring& path) {
    wchar_t win[MAX_PATH] = {};
    if (!GetWindowsDirectoryW(win, MAX_PATH)) return false;
    std::wstring dir = std::wstring(win) + L"\\Fonts\\";
    return path.size() > dir.size() && _wcsnicmp(path.c_str(), dir.c_str(), dir.size()) == 0;
}

static void FontSync(bool force) {
    stbshared::FontPick pick;
    stbshared::ReadFontPick(pick);
    wchar_t forKey[256] = {}, file[1024] = {};
    Wh_GetStringValue(L"titleFontFor", forKey, 256);
    Wh_GetStringValue(L"titleFontFile", file, 1024);
    if (!force && wcscmp(forKey, pick.key) == 0 && (!file[0] || GetFileAttributesW(file) != INVALID_FILE_ATTRIBUTES))
        return;
    bool found = false;
    std::wstring src = FontFilePath(pick, found), use;
    if (found && UnderWindowsFonts(src)) {
        use = src;
    } else if (found) {
        wchar_t store[MAX_PATH] = {};
        if (Wh_GetModStoragePath(store, MAX_PATH)) {
            std::wstring dir = store;
            SHCreateDirectoryExW(nullptr, dir.c_str(), nullptr);
            UINT32 h = 2166136261u;   // FNV-1a over the source path and size, so a changed font gets a new name
            for (wchar_t c : src) h = (h ^ (UINT32)towlower(c)) * 16777619u;
            WIN32_FILE_ATTRIBUTE_DATA fad{};
            if (GetFileAttributesExW(src.c_str(), GetFileExInfoStandard, &fad)) h = (h ^ fad.nFileSizeLow) * 16777619u;
            wchar_t name[64];
            swprintf_s(name, L"title-font-%08x.ttf", h);
            std::wstring dst = dir + L"\\" + name;
            if (GetFileAttributesW(dst.c_str()) != INVALID_FILE_ATTRIBUTES || CopyFileW(src.c_str(), dst.c_str(), FALSE)) {
                PSECURITY_DESCRIPTOR sd = nullptr;
                // SYSTEM and admins full, everyone and DWM's Window Manager group read.
                if (ConvertStringSecurityDescriptorToSecurityDescriptorW(
                        L"D:P(A;;FA;;;SY)(A;;FA;;;BA)(A;;FR;;;WD)(A;;FR;;;S-1-5-90-0)", SDDL_REVISION_1, &sd, nullptr)) {
                    BOOL present = FALSE, defaulted = FALSE;
                    PACL dacl = nullptr;
                    if (GetSecurityDescriptorDacl(sd, &present, &dacl, &defaulted) && present)
                        SetNamedSecurityInfoW(dst.data(), SE_FILE_OBJECT,
                                              DACL_SECURITY_INFORMATION | PROTECTED_DACL_SECURITY_INFORMATION, nullptr,
                                              nullptr, dacl, nullptr);
                    LocalFree(sd);
                }
                use = dst;
                WIN32_FIND_DATAW fd;
                HANDLE fh = FindFirstFileW((dir + L"\\title-font-*.ttf").c_str(), &fd);
                if (fh != INVALID_HANDLE_VALUE) {
                    do {
                        if (_wcsicmp(fd.cFileName, name) != 0) DeleteFileW((dir + L"\\" + fd.cFileName).c_str());
                    } while (FindNextFileW(fh, &fd));
                    FindClose(fh);
                }
            } else {
                Wh_Log(L"[Font] couldn't copy %s (%lu)", src.c_str(), GetLastError());
            }
        }
    }
    Wh_SetStringValue(L"titleFontFile", use.c_str());
    Wh_SetStringValue(L"titleFontFor", pick.key);
    stbshared::BumpFont();
    Wh_Log(L"[Font] '%s' weight %d: %s", pick.family, pick.weight,
           use.empty() ? (found ? L"no file" : L"not installed, Windows font kept") : use.c_str());
}

// ---- UI thread ----
static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) {
    if (msg == g_taskbarCreated && g_taskbarCreated) {
        g_trayAdded = false;
        UpdateTray(true);
        return 0;
    }
    switch (msg) {
        case WM_STB_TRAY:
            switch (LOWORD(lp)) {
                case NIN_SELECT:
                case NIN_KEYSELECT: stbset::OpenSettingsWindow(); break;
                case WM_CONTEXTMENU: ShowTrayMenu(POINT{GET_X_LPARAM(wp), GET_Y_LPARAM(wp)}); break;
            }
            return 0;
        case WM_STB_SETTINGS:
            LoadToolSettings();
            UpdateTray(false);
            UpdateMouseHook();
            FontSync(false);
            if (HWND s = stbset::g_settingsWnd) PostMessageW(s, WM_APP + 1 /* WM_APP_SETTINGS_RELOAD */, 0, 0);
            return 0;
        case WM_STB_DOCKMENU:
        case WM_STB_TESTMENU:
            ShowDockMenu((HWND)wp, POINT{GET_X_LPARAM(lp), GET_Y_LPARAM(lp)}, msg == WM_STB_TESTMENU);
            return 0;
        case WM_STB_DOCKCLOSE:
        case WM_STB_TESTCLOSE:
            if (IsWindow((HWND)wp)) PostMessageW((HWND)wp, WM_SYSCOMMAND, SC_CLOSE, 0);
            return 0;
        case WM_STB_TESTCOPY:
            CopyAllText((HWND)wp);
            return 0;
        case WM_TIMER:
            if (wp == kTimerEndMenu) {
                KillTimer(hwnd, kTimerEndMenu);
                EndMenu();
            }
            return 0;
    }
    return DefWindowProcW(hwnd, msg, wp, lp);
}

static DWORD WINAPI UiThread(LPVOID) {
    MSG msg;
    PeekMessageW(&msg, nullptr, WM_USER, WM_USER, PM_NOREMOVE);
    SetThreadDpiAwarenessContext(DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2);
    EnableDarkMenus();
    WNDCLASSW wc{};
    wc.lpfnWndProc = WndProc;
    wc.hInstance = (HINSTANCE)&__ImageBase;
    wc.lpszClassName = L"SeamlessTitleBarsTool";
    RegisterClassW(&wc);
    g_wnd = CreateWindowExW(WS_EX_TOOLWINDOW, wc.lpszClassName, L"Seamless Title Bars", WS_POPUP, 0, 0, 0, 0,
                            nullptr, nullptr, wc.hInstance, nullptr);
    if (g_wnd) {
        g_taskbarCreated = RegisterWindowMessageW(L"TaskbarCreated");
        ChangeWindowMessageFilterEx(g_wnd, g_taskbarCreated, MSGFLT_ALLOW, nullptr);
        ChangeWindowMessageFilterEx(g_wnd, WM_STB_TESTMENU, MSGFLT_ALLOW, nullptr);
        ChangeWindowMessageFilterEx(g_wnd, WM_STB_DOCKCLOSE, MSGFLT_ALLOW, nullptr);
        ChangeWindowMessageFilterEx(g_wnd, WM_STB_TESTCLOSE, MSGFLT_ALLOW, nullptr);
        ChangeWindowMessageFilterEx(g_wnd, WM_STB_TESTCOPY, MSGFLT_ALLOW, nullptr);
        UpdateTray(true);
        UpdateMouseHook();
        darkall::Start();
    }
    SetEvent(g_ready);
    if (!g_wnd) return 1;
    FontSync(false);
    while (GetMessageW(&msg, nullptr, 0, 0) > 0) {
        TranslateMessage(&msg);
        DispatchMessageW(&msg);
    }
    darkall::Stop();
    if (g_mouseHook) UnhookWindowsHookEx(g_mouseHook);
    g_mouseHook = nullptr;
    g_midDown = false;
    g_swallowUp = false;
    if (g_trayAdded) {
        NOTIFYICONDATAW nid{sizeof(nid)};
        nid.hWnd = g_wnd;
        nid.uID = kTrayId;
        Shell_NotifyIconW(NIM_DELETE, &nid);
        g_trayAdded = false;
    }
    if (g_trayIcon) DestroyIcon(g_trayIcon);
    g_trayIcon = nullptr;
    DestroyWindow(g_wnd);
    g_wnd = nullptr;
    UnregisterClassW(wc.lpszClassName, wc.hInstance);
    return 0;
}

static bool Start() {
    g_singleInstance = CreateMutexW(nullptr, FALSE, L"Local\\SeamlessTitleBarsToolRunning");
    if (!g_singleInstance || GetLastError() == ERROR_ALREADY_EXISTS) {
        if (g_singleInstance) CloseHandle(g_singleInstance);
        g_singleInstance = nullptr;
        Wh_Log(L"[Tool] already running");
        return false;
    }
    stbshared::Open();
    LoadToolSettings();
    g_ready = CreateEventW(nullptr, TRUE, FALSE, nullptr);
    g_thread = CreateThread(nullptr, 0, UiThread, nullptr, 0, &g_tid);
    if (g_thread) WaitForSingleObject(g_ready, 10000);
    CloseHandle(g_ready);
    g_ready = nullptr;
    Wh_Log(L"[Tool] started: tray %d, dock menu %d", g_ts.tray, g_ts.dock && g_ts.dockMenu);
    return g_thread != nullptr;
}

static void SettingsChanged() {
    if (HWND w = g_wnd) PostMessageW(w, WM_STB_SETTINGS, 0, 0);
}

static void Stop() {
    stbset::CloseSettingsWindow();
    if (g_thread) {
        PostThreadMessageW(g_tid, WM_QUIT, 0, 0);
        if (WaitForSingleObject(g_thread, 15000) != WAIT_OBJECT_0) Wh_Log(L"[Tool] UI thread did not stop in 15 s");
        CloseHandle(g_thread);
        g_thread = nullptr;
    }
    for (int i = 0; i < 150 && g_saveThreads > 0; i++) Sleep(100);
    stbshared::Close();
    if (g_singleInstance) CloseHandle(g_singleInstance);
    g_singleInstance = nullptr;
}
}  // namespace stbtool

// ==========================================================================
//  Windhawk entry points
// ==========================================================================
// In windhawk.exe the mod only starts the tool process: tray icon, settings
// window, the dock's right-click menu, the title font file and the Terminal
// bar host (started or stopped when its setting changes).

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
    // Same menu look as Launchpad's. Hooks are applied when init returns, so it runs here.
    SeamlessMenuSkin::Init();
    stbtool::Start();
    if (Wh_GetIntSetting(L"terminalBar.enabled")) {
        term::Start();
    }
    return true;
}

void WhTool_ModSettingsChanged() {
    stbtool::SettingsChanged();
    if (Wh_GetIntSetting(L"terminalBar.enabled")) {
        if (!term::Start()) return;
        term::Reload();
    } else {
        term::Stop();
    }
}

void WhTool_ModUninit() {
    stbtool::Stop();
    term::Stop();
    SeamlessMenuSkin::Uninit();
}

#include <windhawk_tool_mod.h>
