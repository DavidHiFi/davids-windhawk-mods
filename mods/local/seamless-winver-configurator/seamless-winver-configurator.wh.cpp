// ==WindhawkMod==
// @id              seamless-winver-configurator
// @name            Seamless Winver Configurator
// @description     Customize About Windows with themes, logos, classic dialogs, text rules and redirection
// @version         1.1.1
// @author          DavidHiFi, ItsTauTvyDas, aubymori, Thomas Shrader, winui64, m417z
// @github          https://github.com/DavidHiFi
// @homepage        https://github.com/DavidHiFi/seamless-workshop
// @license         GPL-3.0-or-later
// @donateUrl       https://ko-fi.com/DavidHiFi
// @include         winver.exe
// @include         windhawk.exe
// @architecture    x86-64
// @compilerOptions -ld2d1 -ldwrite -lwindowscodecs -lole32 -loleaut32 -luuid -lgdi32 -lgdiplus -luser32 -lshell32 -lshlwapi -ladvapi32 -ldwmapi -lcomctl32 -luxtheme -lcomdlg32 -limm32 -lversion -lntdll -Wl,--delayload=d2d1.dll -Wl,--delayload=dwrite.dll -Wl,--delayload=windowscodecs.dll -Wl,--delayload=comdlg32.dll -Wl,--delayload=imm32.dll -Wl,--delayload=gdiplus.dll -ldelayimp
// ==/WindhawkMod==

// ==WindhawkModReadme==
/*
# Seamless Winver Configurator

Six About Windows mods in one. Theme the About box, put your own picture in it,
bring back the About box of an older Windows, change its words, or open
something else instead. It all lives in one settings window that matches the
rest of the Seamless mods, with a tray icon to open About Windows in one click.

![Seamless Winver Configurator settings](https://raw.githubusercontent.com/DavidHiFi/seamless-workshop/main/media/previews/seamless-winver-configurator.png)

## What it does

- A Mocha box out of the box: dark glass, our own banner and the FiraCode font. Or a solid
  Mocha box, stock Windows, or your own colors.
- Your own picture or animated GIF in place of the Windows banner.
- Where About Windows opens, its size, its icon, its title, and each line of text in it.
- The About box from Windows 95 up to Windows 10, with your own version, build and memory lines.
- Opens another app, a folder or a settings page instead of About Windows.
- Swaps any text you choose, in About Windows or in other apps you pick.
- Opens and closes with a short fade that follows your shared Seamless speed.

## Good to know

- Turn off the six original mods first, or two of them will fight over the same window.
- The classic box and text swapping stay inside About Windows unless you turn on
  "Include other apps". Each other app also has to be added under this mod's
  Advanced tab in Windhawk ("Custom process inclusion list"), because the mod only
  loads into About Windows by default.
- The classic boxes need the matching shell32.dll (and for some, its language
  files) from the Windows version you want back.

## Credits

Built from [Fully Customizable WinVer](https://windhawk.net/mods/fully-customizable-winver) by ItsTauTvyDas,
[Classic Winver](https://windhawk.net/mods/classic-winver) and
[Winver Text Customizer](https://windhawk.net/mods/winver-text-customizer) by aubymori,
[Winver Custom Text](https://windhawk.net/mods/winver-custom-text) by Thomas Shrader,
[Winver Redirector](https://windhawk.net/mods/replace-winver-with-exe) by winui64, and
[Text Replace](https://windhawk.net/mods/text-replace) by m417z. GPL-3.0 or later, like the originals.
*/
// ==/WindhawkModReadme==

// ==WindhawkModSettings==
/*
- themePreset: mochaDark
  $name: Theme preset
  $description: "Choose how About Windows looks right away. Pick Custom colors to use the color boxes below."
  $options:
  - mochaDark: Catppuccin Mocha dark glass
  - mochaSolid: Catppuccin Mocha solid, no glass
  - stock: Stock Windows
  - custom: Custom colors
- windowColors:
  - title: "#CDD6F4"
    $name: Title text color
    $description: "Hex (#CDD6F4) or RGB (205, 214, 244). Leave blank for default."
  - bar: "#181825"
    $name: Title bar color
    $description: "Hex (#181825) or RGB (24, 24, 37). Leave blank for default."
  - border: "#89B4FA"
    $name: Border color
    $description: "Hex (#89B4FA) or RGB (137, 180, 250). Leave blank for default."
  - background: "#1E1E2E"
    $name: Background color
    $description: "Hex (#1E1E2E) or RGB (30, 30, 46). The Windows banner is redrawn on it too."
  - textColor: "#CDD6F4"
    $name: Default text color
    $description: "Hex (#CDD6F4) or RGB (205, 214, 244)."
  - separator: "#45475A"
    $name: Separator color
    $description: "Hex (#45475A) or RGB (69, 71, 90). Leave blank for default."
  $name: Custom colors
- ownBanner: true
  $name: Mocha banner
  $description: "Draws our own banner: the Windows logo and name in the blue to mauve gradient, in place of the stock picture."
- bannerText: ""
  $name: Banner name
  $description: "Leave blank to show your Windows name (Windows 11 or Windows 10)."
- textFont: "FiraCode Nerd Font"
  $name: Text font
  $description: "The font for every line in About Windows. Leave blank to keep the Windows font."
- flyoutAnimation: true
  $name: Open and close animation
  $description: "About Windows fades in with a short slide when it opens and fades out when it closes. Off snaps it. Stays still when Windows animations are off."
- animationSpeed: global
  $name: Animation speed
  $description: "How fast the open animation runs. Global follows your shared Seamless motion speed."
  $options:
  - global: Follow the global speed
  - veryQuick: Very quick
  - quick: Quick
  - normal: Normal
  - relaxed: Relaxed
  - slow: Slow
- launchOnSave: false
  $name: Open About Windows after saving
  $description: "Opens About Windows when you save, if it is not open already, so you see the change right away."
- logo:
  - enabled: false
    $name: Custom logo
    $description: "Show a custom PNG, JPG, BMP, ICO, or animated GIF in the logo area."
  - path: ""
    $name: Logo image path
    $description: "Full path to a PNG, JPG, BMP, ICO, TIFF, or animated GIF file."
  - center: true
    $name: Center logo
    $description: "Horizontally center the logo inside About Windows."
  - x: 0
    $name: Logo X
    $description: "-500 to 1000 (Suggested: 0). Horizontal position or offset when centered."
  - y: 10
    $name: Logo Y
    $description: "-500 to 1000 (Suggested: 10). Vertical position in pixels."
  - width: 0
    $name: Logo width
    $description: "0 to 1000 (Suggested: 0). Set to 0 to scale automatically from height or original width."
  - height: -1
    $name: Logo height
    $description: "-1 to 500 (Suggested: -1). -1 fits the standard 72 px banner height; 0 uses original height."
  $name: Custom logo
- startPosition:
  - enabled: true
    $name: Custom open position
    $description: "Position About Windows automatically when it opens."
  - center: true
    $name: Center on screen
    $description: "Center the dialog on the chosen monitor. X and Y act as offsets when on."
  - monitor: 0
    $name: Monitor
    $description: "0 to 8 (Suggested: 0). 0 uses the monitor where the window appeared; 1 to 8 picks a specific screen."
  - x: 0
    $name: Position X
    $description: "-3000 to 3000 (Suggested: 0). Horizontal position or offset from center."
  - y: 0
    $name: Position Y
    $description: "-3000 to 3000 (Suggested: 0). Vertical position or offset from center."
  $name: Window open position
- windowSize:
  - enabled: false
    $name: Custom window size
    $description: "Resize About Windows when it opens."
  - width: 0
    $name: Width
    $description: "0 to 2000 (Suggested: 0). Set to 0 to keep the default width."
  - height: 0
    $name: Height
    $description: "0 to 2000 (Suggested: 0). Set to 0 to keep the default height."
  - expandControls: true
    $name: Expand controls to fit
    $description: "Widen text labels when the window is wider."
  - exceptionalOkButton: true
    $name: Realign OK button vertically
    $description: "Move the OK button down when the window height increases."
  $name: Window size
- alwaysOnTop: false
  $name: Always on top
  $description: "Keep About Windows above other windows."
- removeFirstFocus: false
  $name: Remove initial focus
  $description: "Clear focus from the OK button when the dialog opens."
- customIcon: ""
  $name: Custom window icon
  $description: "Either DLL and index (shell32.dll;23) or a full path to an .ico file. Leave blank for default."
- removeTitleIcon: false
  $name: Hide title bar icon
  $description: "Remove the small icon from the top-left of the title bar."
- restoreCloseButton: true
  $name: Keep close button
  $description: "Keep the close button visible when hiding the title bar icon."
- titleText: ""
  $name: Custom window title
  $description: "Overrides the title bar text directly. Leave blank to keep default or ShellAbout title."
- shellText:
  - enabled: false
    $name: Override ShellAbout text
    $description: "Replace the title, first line, and middle text sent to ShellAbout."
  - title: "About Windows"
    $name: ShellAbout title
    $description: "Shown in the title bar. You may also enter Title#FirstLine here. Leave empty for the default."
  - firstLine: "Microsoft Windows"
    $name: First line
    $description: "Shown on the first line below the logo. Leave empty for the default, or type a space to hide it."
  - otherStuff: ""
    $name: Middle text (Other stuff)
    $description: "Extra text displayed in the middle of the dialog, such as an evaluation notice."
  $name: ShellAbout text overrides
- quickControls:
  - productName: ""
    $name: Product name label
    $description: "Replaces the Product Name text. Supports {default.ProductName} placeholders. Leave blank to keep."
  - version: ""
    $name: Version label
    $description: "Replaces the Version line. Supports {default.Version} placeholders. Leave blank to keep."
  - copyright: ""
    $name: Copyright label
    $description: "Replaces the Copyright line, e.g. {default.Copyright::0/1} Custom {default.Copyright::12}."
  - legalNotice: ""
    $name: Legal notice label
    $description: "Replaces the legal notice paragraph. Leave blank to keep."
  - licenseInfo: ""
    $name: License link text
    $description: "Replaces the license line. Use <A>link</A> tags to keep the clickable link."
  - registeredUser1: ""
    $name: Registered user line 1
    $description: "Replaces the registered owner name. Leave blank to keep."
  - registeredUser2: ""
    $name: Registered user line 2
    $description: "Replaces the registered organization name. Leave blank to keep."
  - okButton: ""
    $name: OK button text
    $description: "Replaces the OK button label. Leave blank to keep."
  $name: Quick control overrides
- modifyWindows:
  - - id: Copyright
      $name: Control
      $options:
      - LeftIcon: Left icon
      - Separator: Separator
      - ProductName: Product name
      - Version: Version
      - Copyright: Copyright
      - Spacer1: Spacer 1
      - LegalNotice: Legal notice
      - Spacer2: Spacer 2
      - LicenseInfo: License info
      - RegisteredUser1: Registered user 1
      - RegisteredUser2: Registered user 2
      - OkButton: OK button
    - label: ""
      $name: New text
      $description: "Supports {default.<id>}, {default.<id>::start}, and {default.<id>::start/len}."
    - hidden: false
      $name: Hidden
    - relativePosition: false
      $name: Position relative to original
    - position: ""
      $name: Position (x;y;w;h)
      $description: "Use d for any default value, e.g. d;d;400;d. Leave blank for original."
    - zIndex: Default
      $name: Insert on top of
      $options:
      - Default: Default
      - Bottom: Bottom
      - Top: Top
      - LogoImage: Logo Image
      - LeftIcon: Left icon
      - Separator: Separator
      - ProductName: Product name
      - Version: Version
      - Copyright: Copyright
      - Spacer1: Spacer 1
      - LegalNotice: Legal notice
      - Spacer2: Spacer 2
      - LicenseInfo: License info
      - RegisteredUser1: Registered user 1
      - RegisteredUser2: Registered user 2
      - OkButton: OK button
    - textColor: ""
      $name: Text color
      $description: "Hex (#89B4FA) or RGB (137, 180, 250). Leave blank for default."
  $name: Advanced per-control rules
- classic:
  - enabled: false
    $name: Enable Classic Winver
    $description: "Replace the modern About dialog with one loaded from a classic Windows shell32.dll."
  - allApps: false
    $name: Classic dialog in other apps
    $description: "When Include other apps is on, also replace ShellAbout in Notepad, Explorer, and other programs."
  - shell_dll_path: ""
    $name: Path to shell32.dll
    $description: "Full path to shell32.dll from the Windows version to restore. Leave blank to use System32."
  - xpsp1res_dll_path: ""
    $name: Path to xpsp1res.dll
    $description: "Only for Windows XP SP1+ layout. Leave blank otherwise."
  - msgina_dll_path: ""
    $name: Path to msgina.dll
    $description: "Required for Windows Server 2003 / XP x64 branding bitmaps."
  - branding: professional
    $name: XP / Server 2003 branding
    $description: "Which branding bitmap to use on XP and Server 2003 dialogs."
    $options:
    - professional: Professional
    - home: Home
    - embedded: Embedded
    - server: Server Standard Edition
    - srv_enterprise: Server Enterprise Edition
    - srv_datacenter: Server Datacenter Edition
    - sbs: Small Business Server
    - srv_web: Server Web Edition
  - top_line_text: ""
    $name: Top line text (Vista+)
    $description: "Overrides the top line on Vista and newer classic dialogs. Leave blank for default."
  - version_text: "Windows 95"
    $name: Version text (9x / Me)
    $description: "Version string displayed on Windows 9x and Me classic dialogs. Leave empty for the default."
  - copyright_years: "1981-2001"
    $name: Copyright years (XP / 2003)
    $description: "Copyright year range shown on Windows XP and Server 2003 dialogs. Leave empty for the default, or type a space to hide it."
  - display_version: ""
    $name: Display version (Win 10)
    $description: "Display version such as 22H2. Leave blank for the actual Windows value."
  - major_version: -1
    $name: Major version
    $description: "-1 to 99 (Suggested: -1). -1 uses the actual OS value."
  - minor_version: -1
    $name: Minor version
    $description: "-1 to 99 (Suggested: -1). -1 uses the actual OS value."
  - build_number: -1
    $name: Build number
    $description: "-1 to 999999 (Suggested: -1). -1 uses the actual OS value."
  - ubr: -1
    $name: Sub-build number (UBR)
    $description: "-1 to 999999 (Suggested: -1). -1 uses the actual value (Windows 10 style)."
  - build_lab: ""
    $name: Build lab
    $description: "Custom build lab string, e.g. xpclient.010817-1148. Leave blank for actual value."
  - use_build_lab_ex: false
    $name: Use BuildLabEx
    $description: "Use BuildLabEx instead of BuildLab and show it on any classic dialog style."
  - csd_version: "USE_DEFAULT"
    $name: CSD version (Service Pack)
    $description: "Service pack string. Use USE_DEFAULT for the actual value."
  - debug_string: "USE_DEFAULT"
    $name: Debug string
    $description: "Debug string suffix. Use USE_DEFAULT for the actual value."
  - physical_memory: -1
    $name: Physical memory (KB)
    $description: "-1 to 2000000000 (Suggested: -1). -1 reads actual RAM (Vista and earlier)."
  - system_resources_free: -1
    $name: System resources free (%)
    $description: "-1 to 100 (Suggested: -1). -1 reads actual free memory percent (9x / Me)."
  - show_confidential_text: false
    $name: Show Microsoft Confidential text
    $description: "Show red confidential text on beta Windows 7/8 shell32.dll builds."
  $name: Classic Winver
- redirector:
  - enabled: false
    $name: Redirect Winver to another app
    $description: "When on, running winver.exe launches the command below instead of About Windows."
  - command: ""
    $name: Replacement command or target
    $description: "Executable path with optional arguments, shell:AppsFolder target, shortcut, or URI like ms-settings:about."
  $name: Winver redirector
- includeOtherApps: false
  $name: Include other apps
  $description: "Off keeps the classic box and text swapping inside About Windows. On lets them work in other apps too, once you add each app under this mod's Advanced tab in Windhawk."
- textReplace:
  - enabled: false
    $name: Enable text replacement
    $description: "Replace matching text strings rendered in Winver (and other apps when Include other apps is on)."
  - find1: ""
    $name: Quick find 1 (Winver)
    $description: "Text to find inside About Windows."
  - replace1: ""
    $name: Quick replace 1 (Winver)
    $description: "Replacement text for Quick find 1."
  - find2: ""
    $name: Quick find 2 (Winver)
    $description: "Second text to find inside About Windows."
  - replace2: ""
    $name: Quick replace 2 (Winver)
    $description: "Replacement text for Quick find 2."
  - find3: ""
    $name: Quick find 3 (Winver)
    $description: "Third text to find inside About Windows."
  - replace3: ""
    $name: Quick replace 3 (Winver)
    $description: "Replacement text for Quick find 3."
  $name: Text replace
- PerProgramConfig:
  - - Name: "winver.exe"
      $name: Program name
      $description: "File name or full path with * and ? wildcards."
    - Search: ""
      $name: Text to replace
    - Replace: ""
      $name: Replacement text
  $name: Per-program text replace rules
- settingsGlass: true
  $name: Blurred settings window
  $description: "On, the settings window is see-through glass with Windows acrylic behind it. Off, it is solid. Applies when you save."
- nativeSettingsTitleBar: false
  $name: Native Windows title bar
  $description: "Use the Windows title bar and window buttons for this settings window. Applies when you save."
- settingsTrayIcon: true
  $name: Tray icon
  $description: "An icon in the tray. Click it to open these settings. Right-click it to open About Windows or these settings."
*/
// ==/WindhawkModSettings==

#include <windows.h>
#include <windowsx.h>
#include <commctrl.h>
#include <commdlg.h>
#include <dwmapi.h>
#include <gdiplus.h>
#include <objbase.h>
#include <richedit.h>
#include <shellapi.h>
#include <shlwapi.h>
#include <uxtheme.h>
#include <d2d1.h>
#include <dwrite.h>
#include <wincodec.h>
#include <windhawk_utils.h>
#include <cstring>
#include <random>
#include <map>
#include <imm.h>
#include <d2d1helper.h>
#include <d2d1_1.h>
#include <shlobj.h>

#include <algorithm>
#include <atomic>
#include <cmath>
#include <cstdint>
#include <cstdio>
#include <cwchar>
#include <cwctype>
#include <format>
#include <memory>
#include <mutex>
#include <set>
#include <string>
#include <string_view>
#include <unordered_map>
#include <utility>
#include <vector>

extern "C" IMAGE_DOS_HEADER __ImageBase;
EXTERN_C NTSYSAPI NTSTATUS NTAPI RtlGetVersion(PRTL_OSVERSIONINFOW lpVersionInformation);

// ============================================================================
// 10-settings-data.cpp : Shared settings, color parsing, theme presets, motion
// ============================================================================

namespace swc {

// Catppuccin Mocha palette (RGB COLORREF values)
constexpr COLORREF kMochaBase      = RGB(0x1E, 0x1E, 0x2E);
constexpr COLORREF kMochaMantle    = RGB(0x18, 0x18, 0x25);
constexpr COLORREF kMochaCrust     = RGB(0x11, 0x11, 0x1B);
constexpr COLORREF kMochaSurface0  = RGB(0x31, 0x32, 0x44);
constexpr COLORREF kMochaSurface1  = RGB(0x45, 0x47, 0x5A);
constexpr COLORREF kMochaText      = RGB(0xCD, 0xD6, 0xF4);
constexpr COLORREF kMochaBlue      = RGB(0x89, 0xB4, 0xFA);
constexpr COLORREF kMochaMauve     = RGB(0xCB, 0xA6, 0xF7);

enum class ThemePreset { MochaDark, MochaSolid, Stock, Custom };

struct ControlOverride {
    std::wstring id;
    std::wstring label;
    bool hidden = false;
    bool relativePosition = false;
    std::wstring position;
    std::wstring insertAfter = L"Default";
    bool hasTextColor = false;
    COLORREF textColor = kMochaText;
    // Resolved geometry
    int x = 0, y = 0, width = 0, height = 0;
    HWND hWnd = nullptr;
};

struct TextReplaceRule {
    std::string searchA;
    std::string replaceA;
    std::wstring searchW;
    std::wstring replaceW;
};

enum WinverVersion {
    WVV_UNKNOWN = 0,
    WVV_WIN9X,
    WVV_WINNT4,
    WVV_WINME,
    WVV_WIN2K,
    WVV_WINXP,
    WVV_WINSRV03,
    WVV_WINVISTA,
    WVV_WIN7_8_TH1,
    WVV_WIN10,
};

enum WinverBrand {
    WVB_PROFESSIONAL = 0,
    WVB_SERVER,
    WVB_HOME,
    WVB_EMBEDDED,
    WVB_SRV_ENTERPRISE,
    WVB_SRV_DATACENTER,
    WVB_SBS,
    WVB_SRV_WEB,
};

struct ModConfig {
    // Theme & look
    ThemePreset themePreset = ThemePreset::MochaDark;
    bool hasTitleColor = false;
    COLORREF titleColor = kMochaText;
    bool hasBarColor = false;
    COLORREF barColor = kMochaMantle;
    bool hasBorderColor = false;
    COLORREF borderColor = kMochaBlue;
    bool hasBgColor = false;
    COLORREF bgColor = kMochaBase;
    bool hasTextColor = false;
    COLORREF textColor = kMochaText;
    bool hasSepColor = false;
    COLORREF sepColor = kMochaSurface1;
    bool darkMode = true;
    bool glassBackdrop = false;
    bool ownBanner = false;
    std::wstring bannerText;
    std::wstring textFont;

    // Motion
    bool flyoutAnimation = true;
    std::wstring animationSpeed = L"global";
    bool launchOnSave = false;

    // Logo
    bool logoEnabled = false;
    std::wstring logoPath;
    bool logoCenter = true;
    int logoX = 0, logoY = 10, logoWidth = 0, logoHeight = -1;

    // Start position
    bool posEnabled = true;
    bool posCenter = true;
    int posMonitor = 0, posX = 0, posY = 0;

    // Window size
    bool sizeEnabled = false;
    int sizeWidth = 0, sizeHeight = 0;
    bool expandControls = true;
    bool realignOkButton = true;

    // Window behavior
    bool alwaysOnTop = false;
    bool removeFirstFocus = false;
    std::wstring customIcon;
    bool removeTitleIcon = false;
    bool restoreCloseButton = true;
    std::wstring titleText;

    // ShellAbout text overrides
    bool shellTextEnabled = false;
    std::wstring shellTitle;
    std::wstring shellFirstLine;
    std::wstring shellOtherStuff;

    // Controls
    std::unordered_map<std::wstring, ControlOverride> controls;

    // Classic Winver
    bool classicEnabled = false;
    bool classicAllApps = false;
    std::wstring shellDllPath;
    std::wstring xpsp1ResDllPath;
    std::wstring msginaDllPath;
    WinverBrand branding = WVB_PROFESSIONAL;
    std::wstring topLineText;
    std::wstring versionText = L"Windows 95";
    std::wstring copyrightYears = L"1981-2001";
    std::wstring displayVersion;
    DWORD majorVersion = (DWORD)-1;
    DWORD minorVersion = (DWORD)-1;
    DWORD buildNumber = (DWORD)-1;
    DWORD ubr = (DWORD)-1;
    std::wstring buildLab;
    bool useBuildLabEx = false;
    std::wstring csdVersion = L"USE_DEFAULT";
    std::wstring debugString = L"USE_DEFAULT";
    DWORD physicalMemory = (DWORD)-1;
    DWORD systemResourcesFree = (DWORD)-1;
    bool showConfidentialText = false;

    // Redirector
    bool redirectorEnabled = false;
    std::wstring redirectorCommand;

    // Scope & Text replace
    bool includeOtherApps = false;
    bool textReplaceEnabled = false;
    std::vector<TextReplaceRule> textRules;

    // Settings window / tray
    bool settingsTrayIcon = true;
};

static SRWLOCK g_cfgLock = SRWLOCK_INIT;
static ModConfig g_cfg;
static bool g_isWinverProcess = false;
static bool g_isWindhawkHost = false;

static std::wstring ReadStrSetting(PCWSTR key, PCWSTR fallback = L"") {
    PCWSTR raw = Wh_GetStringSetting(key);
    std::wstring out = (raw && *raw) ? raw : (fallback ? fallback : L"");
    if (raw) Wh_FreeStringSetting(raw);
    return out;
}

// Accepts "#RRGGBB", "RRGGBB", or "R, G, B" (compatible with Fully Customizable WinVer)
static bool ParseFlexibleColor(const std::wstring& s, COLORREF& out) {
    size_t a = s.find_first_not_of(L" \t\r\n");
    if (a == std::wstring::npos) return false;
    size_t b = s.find_last_not_of(L" \t\r\n");
    std::wstring t = s.substr(a, b - a + 1);
    if (t.empty()) return false;

    if (t[0] == L'#' || (t.size() == 6 && t.find(L',') == std::wstring::npos)) {
        std::wstring hex = (t[0] == L'#') ? t.substr(1) : t;
        if (hex.size() == 6 &&
            hex.find_first_not_of(L"0123456789abcdefABCDEF") == std::wstring::npos) {
            UINT rgb = wcstoul(hex.c_str(), nullptr, 16);
            out = RGB((rgb >> 16) & 0xFF, (rgb >> 8) & 0xFF, rgb & 0xFF);
            return true;
        }
    }

    int r = 0, g = 0, bl = 0;
    if (swscanf_s(t.c_str(), L"%d%*[, ]%d%*[, ]%d", &r, &g, &bl) == 3) {
        r = std::clamp(r, 0, 255);
        g = std::clamp(g, 0, 255);
        bl = std::clamp(bl, 0, 255);
        out = RGB(r, g, bl);
        return true;
    }
    return false;
}

static bool LoadColorSetting(PCWSTR key, COLORREF& out) {
    return ParseFlexibleColor(ReadStrSetting(key), out);
}

// Wildcard matcher from text-replace (tidwall/match.c)
template <typename T>
static bool WildcardMatch(const T* pat, size_t plen, const T* str, size_t slen) {
    while (plen > 0) {
        if (pat[0] == '*') {
            if (plen == 1) return true;
            if (pat[1] == '*') { pat++; plen--; continue; }
            if (WildcardMatch(pat + 1, plen - 1, str, slen)) return true;
            if (slen == 0) return false;
            str++; slen--;
            continue;
        }
        if (slen == 0) return false;
        if (pat[0] != '?' && str[0] != pat[0]) return false;
        pat++; plen--; str++; slen--;
    }
    return slen == 0 && plen == 0;
}

static std::string WideToAnsi(const std::wstring& w) {
    if (w.empty()) return {};
    int n = WideCharToMultiByte(CP_ACP, 0, w.data(), (int)w.size(), nullptr, 0, nullptr, nullptr);
    if (n <= 0) return {};
    std::string out(n, '\0');
    WideCharToMultiByte(CP_ACP, 0, w.data(), (int)w.size(), out.data(), n, nullptr, nullptr);
    return out;
}

static std::wstring GetCurrentProcessUpperPath(std::wstring& outFileName) {
    WCHAR path[1024]{};
    DWORD sz = ARRAYSIZE(path);
    if (!QueryFullProcessImageNameW(GetCurrentProcess(), 0, path, &sz)) {
        sz = GetModuleFileNameW(nullptr, path, ARRAYSIZE(path));
    }
    if (sz > 0) {
        LCMapStringEx(LOCALE_NAME_USER_DEFAULT, LCMAP_UPPERCASE, path, (int)sz, path, (int)sz, nullptr, nullptr, 0);
    }
    std::wstring full(path, sz);
    size_t slash = full.find_last_of(L'\\');
    outFileName = (slash != std::wstring::npos) ? full.substr(slash + 1) : full;
    return full;
}

static DWORD GetMotionDurationMs(bool open, const std::wstring& speedSetting) {
    BOOL sysAnim = TRUE;
    SystemParametersInfoW(SPI_GETCLIENTAREAANIMATION, 0, &sysAnim, 0);
    if (!sysAnim) return 0;

    std::wstring spd = speedSetting;
    if (spd.empty() || spd == L"global") {
        HKEY hk = nullptr;
        if (RegOpenKeyExW(HKEY_CURRENT_USER, L"Software\\DavidHiFi\\Motion", 0, KEY_READ, &hk) == ERROR_SUCCESS) {
            DWORD en = 1, cb = sizeof(en);
            if (RegQueryValueExW(hk, L"Enabled", nullptr, nullptr, (BYTE*)&en, &cb) == ERROR_SUCCESS && en == 0) {
                RegCloseKey(hk);
                return 0;
            }
            WCHAR buf[64]{};
            DWORD cbb = sizeof(buf);
            if (RegQueryValueExW(hk, L"Speed", nullptr, nullptr, (BYTE*)buf, &cbb) == ERROR_SUCCESS && buf[0]) {
                spd = buf;
            }
            RegCloseKey(hk);
        }
    }
    if (spd == L"veryQuick") return open ? 90 : 70;
    if (spd == L"quick")     return open ? 130 : 95;
    if (spd == L"relaxed")   return open ? 240 : 170;
    if (spd == L"slow")      return open ? 320 : 220;
    return open ? 180 : 125;  // normal
}

static void LoadAllSettings() {
    ModConfig c;

    // Theme preset
    std::wstring preset = ReadStrSetting(L"themePreset", L"mochaDark");
    // mochaGlass was the light system acrylic before 1.1.0; it is the dark glass now, same as mochaDark.
    if (preset == L"mochaSolid")      c.themePreset = ThemePreset::MochaSolid;
    else if (preset == L"stock")      c.themePreset = ThemePreset::Stock;
    else if (preset == L"custom")     c.themePreset = ThemePreset::Custom;
    else                              c.themePreset = ThemePreset::MochaDark;

    if (c.themePreset == ThemePreset::MochaDark || c.themePreset == ThemePreset::MochaSolid) {
        c.darkMode = true;
        c.glassBackdrop = (c.themePreset == ThemePreset::MochaDark);
        c.hasTitleColor = true;  c.titleColor = kMochaText;
        c.hasBarColor   = true;  c.barColor   = kMochaMantle;
        c.hasBorderColor= true;  c.borderColor= kMochaBlue;
        c.hasBgColor    = true;  c.bgColor    = kMochaBase;
        c.hasTextColor  = true;  c.textColor  = kMochaText;
        c.hasSepColor   = true;  c.sepColor   = kMochaSurface1;
    } else if (c.themePreset == ThemePreset::Custom) {
        c.hasTitleColor  = LoadColorSetting(L"windowColors.title", c.titleColor);
        c.hasBarColor    = LoadColorSetting(L"windowColors.bar", c.barColor);
        c.hasBorderColor = LoadColorSetting(L"windowColors.border", c.borderColor);
        c.hasBgColor     = LoadColorSetting(L"windowColors.background", c.bgColor);
        c.hasTextColor   = LoadColorSetting(L"windowColors.textColor", c.textColor);
        c.hasSepColor    = LoadColorSetting(L"windowColors.separator", c.sepColor);
        // Auto-enable dark title/controls if custom background is dark
        if (c.hasBgColor) {
            int luma = (GetRValue(c.bgColor) * 299 + GetGValue(c.bgColor) * 587 + GetBValue(c.bgColor) * 114) / 1000;
            c.darkMode = (luma < 128);
        } else {
            c.darkMode = false;
        }
        c.glassBackdrop = false;
    } else {
        // Stock Windows
        c.darkMode = false;
        c.glassBackdrop = false;
    }

    // Banner and font (not for the stock look)
    if (c.themePreset != ThemePreset::Stock) {
        c.ownBanner  = Wh_GetIntSetting(L"ownBanner") != 0;
        c.bannerText = ReadStrSetting(L"bannerText");
        c.textFont   = ReadStrSetting(L"textFont");
    }

    // Motion & quick actions
    c.flyoutAnimation = Wh_GetIntSetting(L"flyoutAnimation") != 0;
    c.animationSpeed  = ReadStrSetting(L"animationSpeed", L"global");
    c.launchOnSave    = Wh_GetIntSetting(L"launchOnSave") != 0;

    // Logo
    c.logoEnabled = Wh_GetIntSetting(L"logo.enabled") != 0;
    c.logoPath    = ReadStrSetting(L"logo.path");
    c.logoCenter  = Wh_GetIntSetting(L"logo.center") != 0;
    c.logoX       = std::clamp(Wh_GetIntSetting(L"logo.x"), -500, 1000);
    c.logoY       = std::clamp(Wh_GetIntSetting(L"logo.y"), -500, 1000);
    c.logoWidth   = std::clamp(Wh_GetIntSetting(L"logo.width"), 0, 1000);
    c.logoHeight  = std::clamp(Wh_GetIntSetting(L"logo.height"), -1, 500);

    // Position
    c.posEnabled = Wh_GetIntSetting(L"startPosition.enabled") != 0;
    c.posCenter  = Wh_GetIntSetting(L"startPosition.center") != 0;
    c.posMonitor = std::clamp(Wh_GetIntSetting(L"startPosition.monitor"), 0, 8);
    c.posX       = std::clamp(Wh_GetIntSetting(L"startPosition.x"), -3000, 3000);
    c.posY       = std::clamp(Wh_GetIntSetting(L"startPosition.y"), -3000, 3000);

    // Window size
    c.sizeEnabled     = Wh_GetIntSetting(L"windowSize.enabled") != 0;
    c.sizeWidth       = std::clamp(Wh_GetIntSetting(L"windowSize.width"), 0, 2000);
    c.sizeHeight      = std::clamp(Wh_GetIntSetting(L"windowSize.height"), 0, 2000);
    c.expandControls  = Wh_GetIntSetting(L"windowSize.expandControls") != 0;
    c.realignOkButton = Wh_GetIntSetting(L"windowSize.exceptionalOkButton") != 0;

    // Behavior
    c.alwaysOnTop        = Wh_GetIntSetting(L"alwaysOnTop") != 0;
    c.removeFirstFocus   = Wh_GetIntSetting(L"removeFirstFocus") != 0;
    c.customIcon         = ReadStrSetting(L"customIcon");
    c.removeTitleIcon    = Wh_GetIntSetting(L"removeTitleIcon") != 0;
    c.restoreCloseButton = Wh_GetIntSetting(L"restoreCloseButton") != 0;
    c.titleText          = ReadStrSetting(L"titleText");

    // ShellAbout text overrides
    c.shellTextEnabled = Wh_GetIntSetting(L"shellText.enabled") != 0;
    c.shellTitle       = ReadStrSetting(L"shellText.title", L"About Windows");
    c.shellFirstLine   = ReadStrSetting(L"shellText.firstLine", L"Microsoft Windows");
    c.shellOtherStuff  = ReadStrSetting(L"shellText.otherStuff");

    // Advanced modifyWindows[] rules
    for (int i = 0; i < 64; i++) {
        PCWSTR rawId = Wh_GetStringSetting(L"modifyWindows[%d].id", i);
        if (!rawId || !*rawId) {
            if (rawId) Wh_FreeStringSetting(rawId);
            break;
        }
        ControlOverride co;
        co.id = rawId;
        Wh_FreeStringSetting(rawId);

        auto getArrStr = [&](PCWSTR fmt) {
            PCWSTR p = Wh_GetStringSetting(fmt, i);
            std::wstring r = (p && *p) ? p : L"";
            if (p) Wh_FreeStringSetting(p);
            return r;
        };
        co.label            = getArrStr(L"modifyWindows[%d].label");
        co.position         = getArrStr(L"modifyWindows[%d].position");
        co.insertAfter      = getArrStr(L"modifyWindows[%d].zIndex");
        if (co.insertAfter.empty()) co.insertAfter = L"Default";
        co.hidden           = Wh_GetIntSetting(L"modifyWindows[%d].hidden", i) != 0;
        co.relativePosition = Wh_GetIntSetting(L"modifyWindows[%d].relativePosition", i) != 0;
        std::wstring tc     = getArrStr(L"modifyWindows[%d].textColor");
        co.hasTextColor     = ParseFlexibleColor(tc, co.textColor);

        // Skip completely empty placeholder entry
        if (!co.label.empty() || co.hidden || !co.position.empty() ||
            co.insertAfter != L"Default" || co.hasTextColor) {
            c.controls[co.id] = std::move(co);
        }
    }

    // Quick GUI control overrides (merge onto controls map if non-empty)
    struct QuickMap { PCWSTR key; PCWSTR id; };
    const QuickMap kQuick[] = {
        {L"quickControls.productName",     L"ProductName"},
        {L"quickControls.version",         L"Version"},
        {L"quickControls.copyright",       L"Copyright"},
        {L"quickControls.legalNotice",     L"LegalNotice"},
        {L"quickControls.licenseInfo",     L"LicenseInfo"},
        {L"quickControls.registeredUser1", L"RegisteredUser1"},
        {L"quickControls.registeredUser2", L"RegisteredUser2"},
        {L"quickControls.okButton",        L"OkButton"},
    };
    for (const auto& q : kQuick) {
        std::wstring val = ReadStrSetting(q.key);
        if (!val.empty()) {
            auto& co = c.controls[q.id];
            co.id = q.id;
            co.label = std::move(val);
        }
    }

    // Classic Winver
    c.classicEnabled       = Wh_GetIntSetting(L"classic.enabled") != 0;
    c.classicAllApps       = Wh_GetIntSetting(L"classic.allApps") != 0;
    c.shellDllPath         = ReadStrSetting(L"classic.shell_dll_path");
    c.xpsp1ResDllPath      = ReadStrSetting(L"classic.xpsp1res_dll_path");
    c.msginaDllPath        = ReadStrSetting(L"classic.msgina_dll_path");
    c.topLineText          = ReadStrSetting(L"classic.top_line_text");
    c.versionText          = ReadStrSetting(L"classic.version_text", L"Windows 95");
    c.copyrightYears       = ReadStrSetting(L"classic.copyright_years", L"1981-2001");
    c.displayVersion       = ReadStrSetting(L"classic.display_version");
    c.majorVersion         = (DWORD)Wh_GetIntSetting(L"classic.major_version");
    c.minorVersion         = (DWORD)Wh_GetIntSetting(L"classic.minor_version");
    c.buildNumber          = (DWORD)Wh_GetIntSetting(L"classic.build_number");
    c.ubr                  = (DWORD)Wh_GetIntSetting(L"classic.ubr");
    c.buildLab             = ReadStrSetting(L"classic.build_lab");
    c.useBuildLabEx        = Wh_GetIntSetting(L"classic.use_build_lab_ex") != 0;
    c.csdVersion           = ReadStrSetting(L"classic.csd_version", L"USE_DEFAULT");
    c.debugString          = ReadStrSetting(L"classic.debug_string", L"USE_DEFAULT");
    c.physicalMemory       = (DWORD)Wh_GetIntSetting(L"classic.physical_memory");
    c.systemResourcesFree  = (DWORD)Wh_GetIntSetting(L"classic.system_resources_free");
    c.showConfidentialText = Wh_GetIntSetting(L"classic.show_confidential_text") != 0;

    std::wstring br = ReadStrSetting(L"classic.branding", L"professional");
    if      (br == L"home")           c.branding = WVB_HOME;
    else if (br == L"embedded")       c.branding = WVB_EMBEDDED;
    else if (br == L"server")         c.branding = WVB_SERVER;
    else if (br == L"srv_enterprise") c.branding = WVB_SRV_ENTERPRISE;
    else if (br == L"srv_datacenter") c.branding = WVB_SRV_DATACENTER;
    else if (br == L"sbs")            c.branding = WVB_SBS;
    else if (br == L"srv_web")        c.branding = WVB_SRV_WEB;
    else                              c.branding = WVB_PROFESSIONAL;

    // Redirector
    c.redirectorEnabled = Wh_GetIntSetting(L"redirector.enabled") != 0;
    c.redirectorCommand = ReadStrSetting(L"redirector.command");

    // Scope & Text replace
    c.includeOtherApps   = Wh_GetIntSetting(L"includeOtherApps") != 0;
    c.textReplaceEnabled = Wh_GetIntSetting(L"textReplace.enabled") != 0;

    if (c.textReplaceEnabled && (g_isWinverProcess || c.includeOtherApps)) {
        std::wstring fileName;
        std::wstring fullPath = GetCurrentProcessUpperPath(fileName);

        // Quick Winver find/replace pairs (apply to winver.exe)
        if (g_isWinverProcess) {
            const PCWSTR kFinds[3] = {L"textReplace.find1", L"textReplace.find2", L"textReplace.find3"};
            const PCWSTR kRepls[3] = {L"textReplace.replace1", L"textReplace.replace2", L"textReplace.replace3"};
            for (int i = 0; i < 3; i++) {
                std::wstring f = ReadStrSetting(kFinds[i]);
                if (!f.empty()) {
                    std::wstring r = ReadStrSetting(kRepls[i]);
                    c.textRules.push_back({WideToAnsi(f), WideToAnsi(r), std::move(f), std::move(r)});
                }
            }
        }

        // PerProgramConfig array
        for (int i = 0; i < 128; i++) {
            PCWSTR rawName = Wh_GetStringSetting(L"PerProgramConfig[%d].Name", i);
            bool hasName = rawName && *rawName;
            bool matched = false;
            if (hasName) {
                std::wstring pat(rawName);
                LCMapStringEx(LOCALE_NAME_USER_DEFAULT, LCMAP_UPPERCASE,
                              pat.data(), (int)pat.size(), pat.data(), (int)pat.size(), nullptr, nullptr, 0);
                if (!fileName.empty() && WildcardMatch(pat.c_str(), pat.size(), fileName.c_str(), fileName.size())) {
                    matched = true;
                } else if (WildcardMatch(pat.c_str(), pat.size(), fullPath.c_str(), fullPath.size())) {
                    matched = true;
                }
            }
            if (rawName) Wh_FreeStringSetting(rawName);
            if (!hasName) break;

            if (matched) {
                PCWSTR rawSearch = Wh_GetStringSetting(L"PerProgramConfig[%d].Search", i);
                PCWSTR rawReplace = Wh_GetStringSetting(L"PerProgramConfig[%d].Replace", i);
                if (rawSearch && *rawSearch) {
                    std::wstring sw(rawSearch);
                    std::wstring rw(rawReplace ? rawReplace : L"");
                    c.textRules.push_back({WideToAnsi(sw), WideToAnsi(rw), std::move(sw), std::move(rw)});
                }
                if (rawSearch) Wh_FreeStringSetting(rawSearch);
                if (rawReplace) Wh_FreeStringSetting(rawReplace);
            }
        }
    }

    c.settingsTrayIcon = Wh_GetIntSetting(L"settingsTrayIcon") != 0;

    AcquireSRWLockExclusive(&g_cfgLock);
    g_cfg = std::move(c);
    ReleaseSRWLockExclusive(&g_cfgLock);
}

static ModConfig SnapshotConfig() {
    AcquireSRWLockShared(&g_cfgLock);
    ModConfig copy = g_cfg;
    ReleaseSRWLockShared(&g_cfgLock);
    return copy;
}

}  // namespace swc

// ============================================================================
// 20-redirector-and-shelltext.cpp : Winver Redirector & ShellAbout text layer
// ============================================================================

namespace swc {

// Attempts to launch the configured replacement command for winver.exe.
// Returns true if redirected successfully (caller should return TRUE from ShellAboutW).
// Returns false if disabled, empty, or failed (after showing error; caller falls back).
static bool TryRedirectWinver(HWND hWnd, const ModConfig& cfg) {
    if (!g_isWinverProcess || !cfg.redirectorEnabled || cfg.redirectorCommand.empty()) {
        return false;
    }

    std::wstring command = cfg.redirectorCommand;
    DWORD launchError = ERROR_SUCCESS;

    const DWORD expandedLen = ExpandEnvironmentStringsW(command.c_str(), nullptr, 0);
    if (expandedLen > 0) {
        std::wstring expanded(expandedLen, L'\0');
        const DWORD written = ExpandEnvironmentStringsW(command.c_str(), expanded.data(), expandedLen);
        if (written == 0) {
            launchError = GetLastError();
        } else if (written > expandedLen) {
            launchError = ERROR_INSUFFICIENT_BUFFER;
        } else {
            expanded.resize(written - 1);
            command = std::move(expanded);
        }
    } else {
        launchError = GetLastError();
    }

    const auto firstChar = command.find_first_not_of(L" \t\r\n");
    if (firstChar == std::wstring::npos) {
        return false;
    }
    command = command.substr(firstChar, command.find_last_not_of(L" \t\r\n") - firstChar + 1);

    std::wstring target, arguments;
    if (command.front() == L'"') {
        const auto closeQuote = command.find(L'"', 1);
        if (closeQuote == std::wstring::npos || closeQuote == 1 ||
            (closeQuote + 1 < command.size() &&
             command.find_first_of(L" \t\r\n", closeQuote + 1) != closeQuote + 1)) {
            launchError = ERROR_INVALID_PARAMETER;
        } else {
            target = command.substr(1, closeQuote - 1);
            arguments = command.substr(closeQuote + 1);
        }
    } else if (_wcsnicmp(command.c_str(), L"shell:", 6) == 0 ||
               GetFileAttributesW(command.c_str()) != INVALID_FILE_ATTRIBUTES) {
        target = command;
    } else {
        const auto sep = command.find_first_of(L" \t\r\n");
        target = command.substr(0, sep);
        if (sep != std::wstring::npos) {
            arguments = command.substr(sep);
        }
    }

    const auto firstArg = arguments.find_first_not_of(L" \t\r\n");
    arguments = (firstArg == std::wstring::npos) ? L"" : arguments.substr(firstArg);

    if (launchError == ERROR_SUCCESS) {
        // Pointing the redirect at winver itself would start winver again and again.
        std::wstring stem = target.substr(target.find_last_of(L"\\/") == std::wstring::npos ? 0 : target.find_last_of(L"\\/") + 1);
        if (stem.size() > 4 && !_wcsicmp(stem.c_str() + stem.size() - 4, L".exe")) stem.resize(stem.size() - 4);
        if (!_wcsicmp(stem.c_str(), L"winver")) {
            Wh_Log(L"Redirect points at winver itself; showing the normal box instead");
            return false;
        }
    }

    if (launchError == ERROR_SUCCESS) {
        const HRESULT comHr = CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);
        if (FAILED(comHr) && comHr != RPC_E_CHANGED_MODE) {
            launchError = static_cast<DWORD>(comHr);
        } else {
            SHELLEXECUTEINFOW sei{};
            sei.cbSize = sizeof(sei);
            sei.fMask = SEE_MASK_NOASYNC | SEE_MASK_FLAG_NO_UI;
            if (_wcsnicmp(target.c_str(), L"shell:", 6) == 0) {
                sei.fMask |= SEE_MASK_INVOKEIDLIST;
            }
            sei.hwnd = hWnd;
            sei.lpFile = target.c_str();
            sei.lpParameters = arguments.empty() ? nullptr : arguments.c_str();
            sei.nShow = SW_SHOWNORMAL;

            if (!ShellExecuteExW(&sei)) {
                launchError = GetLastError();
                if (launchError == ERROR_SUCCESS) launchError = ERROR_GEN_FAILURE;
            }
        }
        if (SUCCEEDED(comHr)) {
            CoUninitialize();
        }
    }

    if (launchError != ERROR_SUCCESS) {
        WCHAR errMsg[512]{};
        if (!FormatMessageW(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
                            nullptr, launchError, 0, errMsg, ARRAYSIZE(errMsg), nullptr)) {
            _snwprintf_s(errMsg, ARRAYSIZE(errMsg), _TRUNCATE,
                         L"Unable to launch the replacement (error 0x%08lX).", launchError);
        }
        MessageBoxW(hWnd, errMsg, L"Seamless Winver Configurator", MB_OK | MB_ICONERROR);
        return false;
    }

    return true;
}

// Builds effective szApp and szOtherStuff when ShellAbout text overrides are enabled.
static void ApplyShellAboutTextOverrides(const ModConfig& cfg,
                                         LPCWSTR origApp, LPCWSTR origOther,
                                         std::wstring& outApp, std::wstring& outOther,
                                         LPCWSTR& effApp, LPCWSTR& effOther) {
    effApp = origApp;
    effOther = origOther;
    if (!g_isWinverProcess || !cfg.shellTextEnabled) return;

    if (!cfg.shellTitle.empty()) {
        if (cfg.shellTitle.find(L'#') != std::wstring::npos) {
            outApp = cfg.shellTitle;
        } else if (!cfg.shellFirstLine.empty()) {
            outApp = cfg.shellTitle + L"#" + cfg.shellFirstLine;
        } else {
            outApp = cfg.shellTitle;
        }
        effApp = outApp.c_str();
    } else if (!cfg.shellFirstLine.empty()) {
        outApp = std::wstring(L"About Windows#") + cfg.shellFirstLine;
        effApp = outApp.c_str();
    }

    if (!cfg.shellOtherStuff.empty()) {
        outOther = cfg.shellOtherStuff;
        effOther = outOther.c_str();
    }
}

}  // namespace swc

// ============================================================================
// 30-classic-winver.cpp : Classic Winver dialog engine (Win95 through Win10)
// Fixed upstream refcount bug (never FreeLibrary on GetModuleHandleW), fixed
// SelectObject(hdcMem, hbmOld), safe string formatting, per-call state.
// ============================================================================

namespace swc {

using BrandingFormatString_t = LPWSTR (WINAPI *)(LPCWSTR pszFormat);
using BrandingLoadImage_t    = HANDLE (WINAPI *)(LPCWSTR pszBrand, UINT uID, UINT type, int cx, int cy, UINT fuLoad);

static HMODULE g_hmWinBrand = nullptr;
static BrandingFormatString_t g_pBrandingFormatString = nullptr;
static BrandingLoadImage_t    g_pBrandingLoadImage    = nullptr;

static bool EnsureWinBrandLoaded() {
    if (g_pBrandingFormatString && g_pBrandingLoadImage) return true;
    if (!g_hmWinBrand) {
        g_hmWinBrand = LoadLibraryExW(L"winbrand.dll", nullptr, LOAD_LIBRARY_SEARCH_SYSTEM32);
    }
    if (!g_hmWinBrand) return false;
    g_pBrandingFormatString = (BrandingFormatString_t)GetProcAddress(g_hmWinBrand, "BrandingFormatString");
    g_pBrandingLoadImage    = (BrandingLoadImage_t)GetProcAddress(g_hmWinBrand, "BrandingLoadImage");
    return g_pBrandingFormatString && g_pBrandingLoadImage;
}

namespace classic_ids {
constexpr UINT DLG_ABOUT        = 0x3810;
constexpr UINT DLG_EULA         = 0x3815;
constexpr UINT IDS_VERSIONMSG   = 60;
constexpr UINT IDS_DEBUG        = 61;
constexpr UINT IDS_LDK          = 62;
constexpr UINT IDS_PERCENTFREE  = 63;
constexpr UINT IDS_CONFIDENTIAL = 62000;

constexpr int IDB_WINDOWS          = 130;
constexpr int IDB_ABOUT256         = 131;
constexpr int IDB_ABOUTBAND256     = 138;
constexpr int IDB_ABOUTPERSONAL256 = 147;
constexpr int IDB_ABOUTEMBEDDED256 = 149;
constexpr int IDB_ABOUTBLADE256    = 151;
constexpr int IDB_ABOUTSBS256      = 153;
constexpr int IDB_ABOUTSRV256      = 155;
constexpr int IDB_ABOUTENT256      = 157;
constexpr int IDB_ABOUTDCS256      = 159;

constexpr int IDB_SMALL_PRO_8 = 101;
constexpr int IDB_SMALL_SRV_8 = 130;
constexpr int IDB_SMALL_ADV_8 = 132;
constexpr int IDB_SMALL_DCS_8 = 134;
constexpr int IDB_SMALL_SBS_8 = 146;
constexpr int IDB_SMALL_BLA_8 = 147;

constexpr int IDB_BASEBRD_ABOUT     = 101;
constexpr int IDB_BASEBRD_BAND      = 111;
constexpr int IDB_BASEBRD_ABOUT_NEW = 121;

constexpr int IDD_ICON            = 0x3009;
constexpr int IDD_LINE_1          = 0x3327;
constexpr int IDD_APPNAME         = 0x3500;
constexpr int IDD_CONVENTIONAL    = 0x3503;
constexpr int IDD_EMSFREE         = 0x3504;
constexpr int IDD_USERNAME        = 0x3507;
constexpr int IDD_COMPANYNAME     = 0x3508;
constexpr int IDD_COPYRIGHTSTRING = 0x350A;
constexpr int IDD_VERSION         = 0x350B;
constexpr int IDD_OTHERSTUFF      = 0x350D;
constexpr int IDD_EULA            = 0x3512;
constexpr int IDD_TRADEMARKS      = 0x3513;
constexpr int IDD_CONFIDENTIAL    = 0x3514;
constexpr int IDD_EULABOX         = 101;
}  // namespace classic_ids

struct ClassicAboutParams {
    HICON hIcon = nullptr;
    LPCWSTR szApp = nullptr;
    LPCWSTR szOtherStuff = nullptr;
    int dpiWindow = 96;
    HBITMAP hbmAbout = nullptr;
    HBITMAP hbmBand = nullptr;
    SIZE sizeAbout{};
    SIZE sizeScaled{};
    SIZE sizeOffsetOld{};
    HMODULE hmShell = nullptr;
    HMODULE hmMSGina = nullptr;
    WinverVersion ver = WVV_UNKNOWN;
    const ModConfig* cfg = nullptr;
    RTL_OSVERSIONINFOW osvi{};
};

static WinverVersion DetermineWinverVersion(const VS_FIXEDFILEINFO* pVerInfo) {
    WORD wMajor = HIWORD(pVerInfo->dwFileVersionMS);
    WORD wMinor = LOWORD(pVerInfo->dwFileVersionMS);
    switch (wMajor) {
        case 4:
            if (wMinor == 0) return (pVerInfo->dwFileOS & VOS_NT) ? WVV_WINNT4 : WVV_WIN9X;
            return WVV_WIN9X;
        case 5:
            return (wMinor == 0) ? WVV_WIN2K : WVV_WINME;
        case 6:
            if (wMinor == 0) {
                WORD build = HIWORD(pVerInfo->dwFileVersionLS);
                if (build >= 6000) return WVV_WINVISTA;
                if (build <= 2900) return WVV_WINXP;
                return WVV_WINSRV03;
            }
            return WVV_WIN7_8_TH1;
        case 10:
            return (HIWORD(pVerInfo->dwFileVersionLS) < 10563) ? WVV_WIN7_8_TH1 : WVV_WIN10;
        default:
            return WVV_UNKNOWN;
    }
}

static DWORD ClassicRegGetString(HKEY hkey, LPCWSTR valName, std::wstring& out) {
    DWORD type = 0, cb = 0;
    DWORD err = SHQueryValueExW(hkey, valName, nullptr, &type, nullptr, &cb);
    if (err != ERROR_SUCCESS || cb < sizeof(WCHAR)) return err ? err : ERROR_FILE_NOT_FOUND;
    std::wstring buf(cb / sizeof(WCHAR) + 1, L'\0');
    err = SHQueryValueExW(hkey, valName, nullptr, &type, (LPBYTE)buf.data(), &cb);
    if (err == ERROR_SUCCESS) {
        size_t nul = buf.find(L'\0');
        if (nul != std::wstring::npos) buf.resize(nul);
        out = std::move(buf);
    }
    return err;
}

static UINT ClassicGetNLSGrouping() {
    WCHAR szGrouping[32]{};
    if (!GetLocaleInfoW(LOCALE_USER_DEFAULT, LOCALE_SGROUPING, szGrouping, ARRAYSIZE(szGrouping))) return 3;
    UINT grouping = 0;
    for (LPCWSTR psz = szGrouping; ; psz++) {
        if (*psz == L'0') break;
        else if ((UINT)(*psz - L'0') < 10) grouping = grouping * 10 + (UINT)(*psz - L'0');
        else if (!*psz) { grouping *= 10; break; }
    }
    return grouping;
}

static void ClassicFormatCommas64(LONGLONG n, LPWSTR out, UINT cch) {
    WCHAR raw[40]{}, sep[8]{};
    _snwprintf_s(raw, ARRAYSIZE(raw), _TRUNCATE, L"%lld", n);
    GetLocaleInfoW(LOCALE_USER_DEFAULT, LOCALE_STHOUSAND, sep, ARRAYSIZE(sep));
    NUMBERFMTW nf{};
    nf.Grouping = ClassicGetNLSGrouping();
    nf.lpDecimalSep = nf.lpThousandSep = sep;
    if (GetNumberFormatW(LOCALE_USER_DEFAULT, 0, raw, &nf, out, cch) == 0) {
        wcsncpy_s(out, cch, raw, _TRUNCATE);
    }
}

static int ClassicGetBrandingIDB(const ClassicAboutParams* ap, HMODULE* phm) {
    using namespace classic_ids;
    if (ap->ver == WVV_WINSRV03) {
        *phm = ap->hmMSGina;
        int id = IDB_SMALL_PRO_8;
        switch (ap->cfg->branding) {
            case WVB_SERVER:         id = IDB_SMALL_SRV_8; break;
            case WVB_SRV_ENTERPRISE: id = IDB_SMALL_ADV_8; break;
            case WVB_SRV_DATACENTER: id = IDB_SMALL_DCS_8; break;
            case WVB_SBS:            id = IDB_SMALL_SBS_8; break;
            case WVB_SRV_WEB:        id = IDB_SMALL_BLA_8; break;
            default:                 id = IDB_SMALL_PRO_8; break;
        }
        if (!FindResourceW(ap->hmMSGina, MAKEINTRESOURCEW(id), RT_BITMAP)) return IDB_SMALL_PRO_8;
        return id;
    }
    *phm = ap->hmShell;
    int id = IDB_ABOUT256;
    switch (ap->cfg->branding) {
        case WVB_SERVER:         id = IDB_ABOUTSRV256; break;
        case WVB_HOME:           id = IDB_ABOUTPERSONAL256; break;
        case WVB_EMBEDDED:       id = IDB_ABOUTEMBEDDED256; break;
        case WVB_SRV_ENTERPRISE: id = IDB_ABOUTENT256; break;
        case WVB_SRV_DATACENTER: id = IDB_ABOUTDCS256; break;
        default:                 id = IDB_ABOUT256; break;
    }
    if (!FindResourceW(ap->hmShell, MAKEINTRESOURCEW(id), RT_BITMAP)) return IDB_ABOUT256;
    return id;
}

static void ClassicFreeBitmaps(ClassicAboutParams* ap) {
    if (ap->hbmAbout) { DeleteObject(ap->hbmAbout); ap->hbmAbout = nullptr; }
    if (ap->hbmBand)  { DeleteObject(ap->hbmBand);  ap->hbmBand  = nullptr; }
}

static void ClassicLoadBitmaps(ClassicAboutParams* ap) {
    using namespace classic_ids;
    ClassicFreeBitmaps(ap);
    switch (ap->ver) {
        case WVV_WIN9X:
        case WVV_WINNT4:
            if (!ap->hIcon) {
                ap->hbmAbout = (HBITMAP)LoadImageW(ap->hmShell, MAKEINTRESOURCEW(IDB_WINDOWS),
                                                   IMAGE_BITMAP, 0, 0, LR_LOADMAP3DCOLORS);
            }
            break;
        case WVV_WINME:
        case WVV_WIN2K:
            ap->hbmAbout = (HBITMAP)LoadImageW(ap->hmShell, MAKEINTRESOURCEW(IDB_ABOUT256), IMAGE_BITMAP, 0, 0, LR_LOADMAP3DCOLORS);
            ap->hbmBand  = (HBITMAP)LoadImageW(ap->hmShell, MAKEINTRESOURCEW(IDB_ABOUTBAND256), IMAGE_BITMAP, 0, 0, LR_LOADMAP3DCOLORS);
            break;
        case WVV_WINXP:
        case WVV_WINSRV03: {
            HMODULE hmBrand = nullptr;
            int idBrand = ClassicGetBrandingIDB(ap, &hmBrand);
            ap->hbmAbout = (HBITMAP)LoadImageW(hmBrand, MAKEINTRESOURCEW(idBrand), IMAGE_BITMAP, 0, 0, LR_LOADMAP3DCOLORS);
            ap->hbmBand  = (HBITMAP)LoadImageW(ap->hmShell, MAKEINTRESOURCEW(IDB_ABOUTBAND256), IMAGE_BITMAP, 0, 0, LR_LOADMAP3DCOLORS);
            break;
        }
        case WVV_WINVISTA:
            if (g_pBrandingLoadImage) {
                HBITMAP hb = (HBITMAP)g_pBrandingLoadImage(L"Basebrd", IDB_BASEBRD_ABOUT, IMAGE_BITMAP, 0, 0, LR_DEFAULTCOLOR);
                if (!hb) hb = (HBITMAP)g_pBrandingLoadImage(L"Basebrd", IDB_BASEBRD_ABOUT_NEW, IMAGE_BITMAP, 0, 0, LR_DEFAULTCOLOR);
                ap->hbmAbout = hb;
                ap->hbmBand  = (HBITMAP)g_pBrandingLoadImage(L"Basebrd", IDB_BASEBRD_BAND, IMAGE_BITMAP, 0, 0, LR_DEFAULTCOLOR);
            }
            break;
        case WVV_WIN7_8_TH1:
        case WVV_WIN10:
            if (g_pBrandingLoadImage) {
                HBITMAP hb = (HBITMAP)g_pBrandingLoadImage(L"Basebrd", IDB_BASEBRD_ABOUT_NEW, IMAGE_BITMAP, 0, 0, LR_DEFAULTCOLOR);
                if (hb) {
                    ap->hbmAbout = hb;
                    BITMAP bm{};
                    GetObjectW(hb, sizeof(bm), &bm);
                    ap->sizeAbout = {bm.bmWidth, bm.bmHeight};
                    int dpiSys = GetDpiForSystem();
                    if (dpiSys == ap->dpiWindow || !dpiSys) {
                        ap->sizeScaled = ap->sizeAbout;
                    } else {
                        ap->sizeScaled.cx = MulDiv(ap->sizeAbout.cx, ap->dpiWindow, dpiSys);
                        ap->sizeScaled.cy = MulDiv(ap->sizeAbout.cy, ap->dpiWindow, dpiSys);
                    }
                }
            }
            break;
        default:
            break;
    }
}

static void ClassicMoveChildren(HWND hWnd, int dx, int dy) {
    RECT rc{};
    for (HWND child = GetWindow(hWnd, GW_CHILD); child; child = GetWindow(child, GW_HWNDNEXT)) {
        GetWindowRect(child, &rc);
        MapWindowPoints(nullptr, GetParent(child), (LPPOINT)&rc, 2);
        OffsetRect(&rc, dx, dy);
        SetWindowPos(child, nullptr, rc.left, rc.top, 0, 0, SWP_NOZORDER | SWP_NOSIZE);
    }
    GetWindowRect(hWnd, &rc);
    SetWindowPos(hWnd, nullptr, 0, 0, (rc.right - rc.left) + dx, (rc.bottom - rc.top) + dy,
                 SWP_NOZORDER | SWP_NOMOVE);
}

static void ClassicApplyLayout(HWND hwnd, ClassicAboutParams* ap) {
    RECT rcWin{};
    GetWindowRect(hwnd, &rcWin);
    int wWin = rcWin.right - rcWin.left;
    int dx = (ap->sizeScaled.cx > wWin) ? (ap->sizeScaled.cx - wWin) : 0;
    int dy = ap->sizeScaled.cy;
    ClassicMoveChildren(hwnd, dx - ap->sizeOffsetOld.cx, dy - ap->sizeOffsetOld.cy);
    ap->sizeOffsetOld = {dx, dy};
    ShowWindow(GetDlgItem(hwnd, classic_ids::IDD_LINE_1), ap->hbmAbout ? SW_NORMAL : SW_HIDE);
}

static INT_PTR CALLBACK ClassicLicenseDlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM) {
    switch (uMsg) {
        case WM_INITDIALOG: {
            WCHAR szFile[MAX_PATH]{};
            ExpandEnvironmentStringsW(L"%SystemRoot%\\System32\\license.rtf", szFile, ARRAYSIZE(szFile));
            BOOL ok = FALSE;
            HANDLE hf = CreateFileW(szFile, GENERIC_READ, FILE_SHARE_READ, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
            if (hf != INVALID_HANDLE_VALUE) {
                LARGE_INTEGER sz{};
                if (GetFileSizeEx(hf, &sz) && sz.QuadPart > 0 && sz.QuadPart < 16 * 1024 * 1024) {
                    std::vector<char> buf((size_t)sz.QuadPart + 2, 0);
                    DWORD rd = 0;
                    if (ReadFile(hf, buf.data(), (DWORD)sz.QuadPart, &rd, nullptr) && rd == (DWORD)sz.QuadPart) {
                        HWND ht = GetDlgItem(hwnd, classic_ids::IDD_EULABOX);
                        SETTEXTEX ste{ST_SELECTION, CP_ACP};
                        SendMessageW(ht, EM_EXLIMITTEXT, 0, 0);
                        SendMessageW(ht, EM_SETTEXTEX, (WPARAM)&ste, (LPARAM)buf.data());
                        SendMessageW(ht, EM_SETSEL, 0, 0);
                        ok = TRUE;
                    }
                }
                CloseHandle(hf);
            }
            if (!ok) PostMessageW(hwnd, WM_COMMAND, IDCANCEL, 0);
            return TRUE;
        }
        case WM_COMMAND:
            if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL) EndDialog(hwnd, 0);
            break;
    }
    return FALSE;
}

static void ClassicInitDialog(HWND hwnd, ClassicAboutParams* ap) {
    using namespace classic_ids;
    const ModConfig& cfg = *ap->cfg;
    WCHAR szBuf[256]{}, szTemp[256]{}, szTitle[256]{}, szMsg[512]{}, szNum[64]{};

    if (ap->ver == WVV_WIN9X && !GetDlgItem(hwnd, IDD_EMSFREE)) {
        ap->ver = WVV_WINNT4;
    }
    ap->dpiWindow = GetDpiForWindow(hwnd);

    LPCWSTR safeApp = ap->szApp ? ap->szApp : L"Windows";
    LPCWSTR pszApp = safeApp;
    LPCWSTR hash = wcschr(safeApp, L'#');
    if (hash) {
        std::wstring titlePart(safeApp, (size_t)(hash - safeApp));
        SetWindowTextW(hwnd, titlePart.c_str());
        pszApp = hash + 1;
    } else {
        GetWindowTextW(hwnd, szBuf, ARRAYSIZE(szBuf));
        _snwprintf_s(szTitle, ARRAYSIZE(szTitle), _TRUNCATE, szBuf, safeApp);
        SetWindowTextW(hwnd, szTitle);
    }

    if (ap->ver <= WVV_WINSRV03) {
        GetDlgItemTextW(hwnd, IDD_APPNAME, szBuf, ARRAYSIZE(szBuf));
        _snwprintf_s(szTitle, ARRAYSIZE(szTitle), _TRUNCATE, szBuf, pszApp);
        SetDlgItemTextW(hwnd, IDD_APPNAME, szTitle);
    } else if (safeApp != pszApp) {
        SetDlgItemTextW(hwnd, IDD_APPNAME, pszApp);
    }

    if (ap->szOtherStuff) SetDlgItemTextW(hwnd, IDD_OTHERSTUFF, ap->szOtherStuff);

    SendDlgItemMessageW(hwnd, IDD_ICON, STM_SETICON, (WPARAM)ap->hIcon, 0);
    if (!ap->hIcon) ShowWindow(GetDlgItem(hwnd, IDD_ICON), SW_HIDE);

    if (ap->ver >= WVV_WINVISTA && g_pBrandingFormatString) {
        if (safeApp == pszApp) {
            if (!cfg.topLineText.empty()) {
                SetDlgItemTextW(hwnd, IDD_APPNAME, cfg.topLineText.c_str());
            } else if (LPWSTR f = g_pBrandingFormatString(L"%MICROSOFT_COMPANYNAME% %WINDOWS_GENERIC%")) {
                SetDlgItemTextW(hwnd, IDD_APPNAME, f);
                GlobalFree(f);
            }
        }
        if (LPWSTR f = g_pBrandingFormatString(L"%WINDOWS_COPYRIGHT%")) {
            SetDlgItemTextW(hwnd, IDD_COPYRIGHTSTRING, f);
            GlobalFree(f);
        }
        WCHAR szTm[512]{};
        GetDlgItemTextW(hwnd, IDD_TRADEMARKS, szTm, ARRAYSIZE(szTm));
        if (LPWSTR f = g_pBrandingFormatString(szTm)) {
            SetDlgItemTextW(hwnd, IDD_TRADEMARKS, f);
            GlobalFree(f);
        }
    }

    if (ap->ver == WVV_WIN9X || ap->ver == WVV_WINME) {
        SetDlgItemTextW(hwnd, IDD_VERSION, cfg.versionText.c_str());
    }

    if ((ap->ver == WVV_WINNT4 || ap->ver >= WVV_WIN2K) && ap->ver < WVV_WIN10) {
        LoadStringW(ap->hmShell, IDS_VERSIONMSG, szBuf, ARRAYSIZE(szBuf));
        szTitle[0] = L'\0';
        if (ap->osvi.szCSDVersion[0]) {
            _snwprintf_s(szTitle, ARRAYSIZE(szTitle), _TRUNCATE, L": %s", ap->osvi.szCSDVersion);
        }
        if (cfg.useBuildLabEx || ap->ver == WVV_WINXP || ap->ver == WVV_WINSRV03) {
            std::wstring lab = cfg.buildLab;
            if (lab.empty()) {
                HKEY hk = nullptr;
                if (RegOpenKeyExW(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion", 0, KEY_READ, &hk) == ERROR_SUCCESS) {
                    std::wstring raw;
                    if (ClassicRegGetString(hk, cfg.useBuildLabEx ? L"BuildLabEx" : L"BuildLab", raw) == ERROR_SUCCESS) {
                        size_t dot = raw.find(L'.');
                        if (dot != std::wstring::npos) lab = raw.substr(dot + 1);
                    }
                    RegCloseKey(hk);
                }
            }
            if (!lab.empty()) {
                wcsncpy_s(szTemp, szTitle, _TRUNCATE);
                _snwprintf_s(szTitle, ARRAYSIZE(szTitle), _TRUNCATE,
                             szTemp[0] ? L".%s %s" : L".%s", lab.c_str(), szTemp);
            }
        }
        szNum[0] = L'\0';
        if (cfg.debugString != L"USE_DEFAULT") {
            wcsncpy_s(szNum, cfg.debugString.c_str(), _TRUNCATE);
        } else if (GetSystemMetrics(SM_DEBUG)) {
            szNum[0] = L' ';
            LoadStringW(ap->hmShell, IDS_DEBUG, &szNum[1], ARRAYSIZE(szNum) - 1);
        }
        _snwprintf_s(szMsg, ARRAYSIZE(szMsg), _TRUNCATE, szBuf,
                     ap->osvi.dwMajorVersion, ap->osvi.dwMinorVersion, ap->osvi.dwBuildNumber, szTitle, szNum);
        SetDlgItemTextW(hwnd, IDD_VERSION, szMsg);
    } else if (ap->ver == WVV_WIN10) {
        LoadStringW(ap->hmShell, IDS_VERSIONMSG, szBuf, ARRAYSIZE(szBuf));
        DWORD dwUBR = cfg.ubr;
        szTitle[0] = L'\0';
        HKEY hk = nullptr;
        if (RegOpenKeyExW(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion", 0, KEY_READ, &hk) == ERROR_SUCCESS) {
            if (dwUBR == (DWORD)-1) {
                DWORD cb = sizeof(dwUBR);
                RegQueryValueExW(hk, L"UBR", nullptr, nullptr, (LPBYTE)&dwUBR, &cb);
            }
            if (!cfg.displayVersion.empty()) {
                wcsncpy_s(szTitle, cfg.displayVersion.c_str(), _TRUNCATE);
            } else {
                std::wstring dv;
                if (ClassicRegGetString(hk, L"DisplayVersion", dv) != ERROR_SUCCESS) {
                    ClassicRegGetString(hk, L"ReleaseID", dv);
                }
                wcsncpy_s(szTitle, dv.c_str(), _TRUNCATE);
            }
            RegCloseKey(hk);
        }
        _snwprintf_s(szTemp, ARRAYSIZE(szTemp), _TRUNCATE, L"%lu", ap->osvi.dwBuildNumber);
        szNum[0] = L'\0';
        if (GetSystemMetrics(SM_DEBUG)) {
            szNum[0] = L' ';
            LoadStringW(ap->hmShell, IDS_DEBUG, &szNum[1], ARRAYSIZE(szNum) - 1);
        }
        _snwprintf_s(szMsg, ARRAYSIZE(szMsg), _TRUNCATE, szBuf, szTitle, szTemp, dwUBR, szNum);
        SetDlgItemTextW(hwnd, IDD_VERSION, szMsg);
    }

    if (ap->ver == WVV_WINXP || ap->ver == WVV_WINSRV03) {
        GetDlgItemTextW(hwnd, IDD_COPYRIGHTSTRING, szTemp, ARRAYSIZE(szTemp));
        _snwprintf_s(szBuf, ARRAYSIZE(szBuf), _TRUNCATE, szTemp, cfg.copyrightYears.c_str());
        SetDlgItemTextW(hwnd, IDD_COPYRIGHTSTRING, szBuf);
    }

    HKEY hk = nullptr;
    if (RegOpenKeyExW(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\Windows NT\\CurrentVersion", 0, KEY_READ, &hk) == ERROR_SUCCESS) {
        std::wstring owner, org;
        if (ClassicRegGetString(hk, L"RegisteredOwner", owner) == ERROR_SUCCESS) SetDlgItemTextW(hwnd, IDD_USERNAME, owner.c_str());
        if (ClassicRegGetString(hk, L"RegisteredOrganization", org) == ERROR_SUCCESS) SetDlgItemTextW(hwnd, IDD_COMPANYNAME, org.c_str());
        RegCloseKey(hk);
    }

    if (ap->ver <= WVV_WINVISTA) {
        DWORDLONG physKB = cfg.physicalMemory;
        if (cfg.physicalMemory == (DWORD)-1) {
            MEMORYSTATUSEX ms{sizeof(ms)};
            GlobalMemoryStatusEx(&ms);
            physKB = (ms.ullTotalPhys + 512) / 1024;
        }
        ClassicFormatCommas64((LONGLONG)physKB, szNum, ARRAYSIZE(szNum));
        if (ap->ver == WVV_WINVISTA && g_pBrandingFormatString) {
            if (LPWSTR pw = g_pBrandingFormatString(L"%WINDOWS_GENERIC%")) {
                WCHAR fmt[256]{};
                GetDlgItemTextW(hwnd, IDD_CONVENTIONAL, fmt, ARRAYSIZE(fmt));
                _snwprintf_s(szBuf, ARRAYSIZE(szBuf), _TRUNCATE, fmt, pw, szNum);
                SetDlgItemTextW(hwnd, IDD_CONVENTIONAL, szBuf);
                GlobalFree(pw);
            }
        } else {
            WCHAR szLdk[64]{};
            LoadStringW(ap->hmShell, IDS_LDK, szLdk, ARRAYSIZE(szLdk));
            _snwprintf_s(szBuf, ARRAYSIZE(szBuf), _TRUNCATE, szLdk, szNum);
            SetDlgItemTextW(hwnd, IDD_CONVENTIONAL, szBuf);
        }
    }

    if (ap->ver <= WVV_WINME && ap->ver != WVV_WINNT4) {
        DWORD freePct = cfg.systemResourcesFree;
        if (cfg.systemResourcesFree == (DWORD)-1) {
            MEMORYSTATUSEX ms{sizeof(ms)};
            GlobalMemoryStatusEx(&ms);
            freePct = 100 - ms.dwMemoryLoad;
        }
        LoadStringW(ap->hmShell, IDS_PERCENTFREE, szBuf, ARRAYSIZE(szBuf));
        _snwprintf_s(szMsg, ARRAYSIZE(szMsg), _TRUNCATE, szBuf, freePct);
        SetDlgItemTextW(hwnd, IDD_EMSFREE, szMsg);
    }

    if (cfg.showConfidentialText && ap->ver == WVV_WIN7_8_TH1) {
        WCHAR szConf[450]{};
        LoadStringW(ap->hmShell, IDS_CONFIDENTIAL, szConf, ARRAYSIZE(szConf));
        SetDlgItemTextW(hwnd, IDD_CONFIDENTIAL, szConf);
    }

    ClassicLoadBitmaps(ap);
    if (ap->ver >= WVV_WIN7_8_TH1) ClassicApplyLayout(hwnd, ap);
}

static INT_PTR CALLBACK ClassicAboutDlgProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    using namespace classic_ids;
    switch (uMsg) {
        case WM_INITDIALOG: {
            auto* ap = (ClassicAboutParams*)lParam;
            SetWindowLongPtrW(hwnd, GWLP_USERDATA, (LONG_PTR)ap);
            ClassicInitDialog(hwnd, ap);
            return TRUE;
        }
        case WM_COMMAND:
            EndDialog(hwnd, TRUE);
            return TRUE;
        case WM_PAINT: {
            PAINTSTRUCT ps{};
            HDC hdc = BeginPaint(hwnd, &ps);
            auto* ap = (ClassicAboutParams*)GetWindowLongPtrW(hwnd, GWLP_USERDATA);
            if (ap && ap->hbmAbout) {
                HDC hdcMem = CreateCompatibleDC(hdc);
                if (hdcMem) {
                    if (ap->ver <= WVV_WINNT4) {
                        HGDIOBJ old = SelectObject(hdcMem, ap->hbmAbout);
                        int x = (ap->ver == WVV_WINNT4) ? 8 : 10, y = 10;
                        int cx = (ap->ver == WVV_WINNT4) ? 68 : 64, cy = (ap->ver == WVV_WINNT4) ? 78 : 64;
                        int dpi = GetDeviceCaps(hdc, LOGPIXELSX);
                        StretchBlt(hdc, MulDiv(x, dpi, 96), MulDiv(y, dpi, 96),
                                   MulDiv(cx, dpi, 96), MulDiv(cy, dpi, 96),
                                   hdcMem, 0, 0, cx, cy, SRCCOPY);
                        SelectObject(hdcMem, old);
                    } else if (ap->ver >= WVV_WINME && ap->ver <= WVV_WINVISTA) {
                        RECT rc{};
                        GetClientRect(hwnd, &rc);
                        int cxDest = rc.right;
                        int cyDest = MulDiv(72, cxDest, 413);
                        HGDIOBJ old = SelectObject(hdcMem, ap->hbmAbout);
                        StretchBlt(hdc, 0, 0, cxDest, cyDest, hdcMem, 0, 0, 413, 72, SRCCOPY);
                        SelectObject(hdcMem, old);
                        if (ap->hbmBand) {
                            old = SelectObject(hdcMem, ap->hbmBand);
                            StretchBlt(hdc, 0, cyDest, cxDest, MulDiv(5, cxDest, 413), hdcMem, 0, 0, 413, 5, SRCCOPY);
                            SelectObject(hdcMem, old);
                        }
                    } else {
                        HGDIOBJ old = SelectObject(hdcMem, ap->hbmAbout);
                        RECT rcClient{};
                        GetClientRect(hwnd, &rcClient);
                        int xDest = (rcClient.right > ap->sizeScaled.cx) ? (rcClient.right - ap->sizeScaled.cx) / 2 : 0;
                        HIGHCONTRASTW hc{sizeof(hc)};
                        SystemParametersInfoW(SPI_GETHIGHCONTRAST, 0, &hc, FALSE);
                        if (hc.dwFlags & HCF_HIGHCONTRASTON) {
                            StretchBlt(hdc, xDest, 0, ap->sizeScaled.cx, ap->sizeScaled.cy,
                                       hdcMem, 0, 0, ap->sizeAbout.cx, ap->sizeAbout.cy, SRCCOPY);
                        } else {
                            GdiTransparentBlt(hdc, xDest, 0, ap->sizeScaled.cx, ap->sizeScaled.cy,
                                              hdcMem, 0, 0, ap->sizeAbout.cx, ap->sizeAbout.cy, RGB(255, 255, 255));
                        }
                        SelectObject(hdcMem, old);  // Fixed: restored on hdcMem, not hdc
                    }
                    DeleteDC(hdcMem);
                }
            }
            EndPaint(hwnd, &ps);
            return TRUE;
        }
        case WM_CTLCOLORSTATIC:
            if ((HWND)lParam == GetDlgItem(hwnd, IDD_CONFIDENTIAL)) {
                SetTextColor((HDC)wParam, RGB(255, 0, 0));
                SetBkMode((HDC)wParam, TRANSPARENT);
                return (INT_PTR)GetSysColorBrush(COLOR_BTNFACE);
            }
            break;
        case WM_NOTIFY:
            if ((int)wParam == IDD_EULA && ((LPNMHDR)lParam)->code == NM_CLICK) {
                auto* ap = (ClassicAboutParams*)GetWindowLongPtrW(hwnd, GWLP_USERDATA);
                if (ap && ap->ver <= WVV_WINSRV03) {
                    SHELLEXECUTEINFOW sei{sizeof(sei)};
                    sei.fMask = SEE_MASK_DOENVSUBST;
                    sei.hwnd = hwnd;
                    sei.nShow = SW_SHOWNORMAL;
                    sei.lpFile = L"%windir%\\system32\\eula.txt";
                    ShellExecuteExW(&sei);
                } else if (ap) {
                    HMODULE hmEdit = LoadLibraryExW(L"msftedit.dll", nullptr, LOAD_LIBRARY_SEARCH_SYSTEM32);
                    if (hmEdit) {
                        DialogBoxParamW(ap->hmShell, MAKEINTRESOURCEW(DLG_EULA), hwnd, ClassicLicenseDlgProc, 0);
                        FreeLibrary(hmEdit);
                    }
                }
                return TRUE;
            }
            break;
        case WM_DPICHANGED: {
            auto* ap = (ClassicAboutParams*)GetWindowLongPtrW(hwnd, GWLP_USERDATA);
            if (ap && ap->ver >= WVV_WIN7_8_TH1) {
                ap->dpiWindow = GetDpiForWindow(hwnd);
                ClassicLoadBitmaps(ap);
                ClassicApplyLayout(hwnd, ap);
            }
            return TRUE;
        }
        case WM_SHOWWINDOW: {
            auto* ap = (ClassicAboutParams*)GetWindowLongPtrW(hwnd, GWLP_USERDATA);
            if (ap && ap->ver >= WVV_WINVISTA && wParam) {
                SetFocus(GetDlgItem(hwnd, IDOK));
            }
            return TRUE;
        }
        case WM_DESTROY: {
            auto* ap = (ClassicAboutParams*)GetWindowLongPtrW(hwnd, GWLP_USERDATA);
            if (ap) ClassicFreeBitmaps(ap);
            return TRUE;
        }
    }
    return FALSE;
}

static VS_FIXEDFILEINFO* ClassicGetVersionInfo(HMODULE hm) {
    HRSRC hr = FindResourceW(hm, MAKEINTRESOURCEW(VS_VERSION_INFO), RT_VERSION);
    if (!hr) return nullptr;
    HGLOBAL hg = LoadResource(hm, hr);
    if (!hg) return nullptr;
    void* data = LockResource(hg);
    if (!data) return nullptr;
    void* ffi = nullptr;
    UINT len = 0;
    if (!VerQueryValueW(data, L"\\", &ffi, &len) || len == 0) return nullptr;
    return (VS_FIXEDFILEINFO*)ffi;
}

static INT ShowClassicWinverDialog(HWND hWnd, LPCWSTR szApp, LPCWSTR szOtherStuff, HICON hIcon, const ModConfig& cfg) {
    using namespace classic_ids;
    EnsureWinBrandLoaded();

    bool ownShell = false;
    HMODULE hmShell = nullptr;
    HMODULE hmXpsp1 = nullptr;
    HMODULE hmMSGina = nullptr;
    INT ret = FALSE;

    if (!cfg.shellDllPath.empty()) {
        hmShell = LoadLibraryExW(cfg.shellDllPath.c_str(), nullptr, LOAD_LIBRARY_AS_DATAFILE);
        ownShell = (hmShell != nullptr);
    } else {
        hmShell = GetModuleHandleW(L"shell32.dll");
    }
    if (!hmShell) {
        MessageBoxW(hWnd, L"Could not load the chosen shell32.dll. Check the path in Classic Winver settings.",
                    L"Seamless Winver Configurator", MB_ICONERROR);
        goto cleanup;
    }

    {
        VS_FIXEDFILEINFO* vi = ClassicGetVersionInfo(hmShell);
        if (!vi) {
            MessageBoxW(hWnd, L"Could not read version info from shell32.dll.", L"Seamless Winver Configurator", MB_ICONERROR);
            goto cleanup;
        }
        WinverVersion ver = DetermineWinverVersion(vi);
        if (ver == WVV_UNKNOWN) {
            MessageBoxW(hWnd, L"Unsupported shell32.dll version for Classic Winver.", L"Seamless Winver Configurator", MB_ICONERROR);
            goto cleanup;
        }

        if (ver == WVV_WINXP && !cfg.xpsp1ResDllPath.empty()) {
            hmXpsp1 = LoadLibraryExW(cfg.xpsp1ResDllPath.c_str(), nullptr, LOAD_LIBRARY_AS_DATAFILE);
        }
        HMODULE hmDialog = (ver == WVV_WINXP && hmXpsp1) ? hmXpsp1 : hmShell;

        if (ver == WVV_WINSRV03) {
            hmMSGina = LoadLibraryExW(cfg.msginaDllPath.c_str(), nullptr, LOAD_LIBRARY_AS_DATAFILE);
            if (!hmMSGina) {
                MessageBoxW(hWnd, L"Could not load msgina.dll for Server 2003 branding.", L"Seamless Winver Configurator", MB_ICONERROR);
                goto cleanup;
            }
        }
        if (!FindResourceW(hmDialog, MAKEINTRESOURCEW(DLG_ABOUT), RT_DIALOG)) {
            MessageBoxW(hWnd, L"About dialog resource was not found in the chosen DLL.", L"Seamless Winver Configurator", MB_ICONERROR);
            goto cleanup;
        }

        ClassicAboutParams ap;
        ap.hIcon = hIcon;
        ap.szApp = szApp;
        ap.szOtherStuff = szOtherStuff;
        ap.hmShell = hmShell;
        ap.hmMSGina = hmMSGina;
        ap.ver = ver;
        ap.cfg = &cfg;
        ap.osvi.dwOSVersionInfoSize = sizeof(ap.osvi);
        RtlGetVersion(&ap.osvi);
        if (cfg.majorVersion != (DWORD)-1) ap.osvi.dwMajorVersion = cfg.majorVersion;
        if (cfg.minorVersion != (DWORD)-1) ap.osvi.dwMinorVersion = cfg.minorVersion;
        if (cfg.buildNumber  != (DWORD)-1) ap.osvi.dwBuildNumber  = cfg.buildNumber;
        if (cfg.csdVersion != L"USE_DEFAULT") wcsncpy_s(ap.osvi.szCSDVersion, cfg.csdVersion.c_str(), _TRUNCATE);

        ACTCTXW actCtx{};
        actCtx.cbSize = sizeof(actCtx);
        actCtx.dwFlags = ACTCTX_FLAG_RESOURCE_NAME_VALID | ACTCTX_FLAG_HMODULE_VALID;
        actCtx.lpResourceName = MAKEINTRESOURCEW(124);
        actCtx.hModule = GetModuleHandleW(L"shell32.dll");
        HANDLE hActCtx = CreateActCtxW(&actCtx);
        ULONG_PTR cookie = 0;
        HMODULE hComCtl = nullptr;
        if (hActCtx != INVALID_HANDLE_VALUE) {
            ActivateActCtx(hActCtx, &cookie);
            hComCtl = LoadLibraryExW(L"comctl32.dll", nullptr, LOAD_LIBRARY_SEARCH_SYSTEM32);
        }

        DPI_AWARENESS_CONTEXT oldDpi = SetThreadDpiAwarenessContext(DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2);
        ret = (INT)DialogBoxParamW(hmDialog, MAKEINTRESOURCEW(DLG_ABOUT), hWnd, ClassicAboutDlgProc, (LPARAM)&ap);
        SetThreadDpiAwarenessContext(oldDpi);

        if (hActCtx != INVALID_HANDLE_VALUE) {
            DeactivateActCtx(0, cookie);
            ReleaseActCtx(hActCtx);
            if (hComCtl) FreeLibrary(hComCtl);
        }
    }

cleanup:
    if (ownShell && hmShell) FreeLibrary(hmShell);
    if (hmXpsp1) FreeLibrary(hmXpsp1);
    if (hmMSGina) FreeLibrary(hmMSGina);
    return ret;
}

}  // namespace swc

// ============================================================================
// 40-custom-dialog.cpp : the themed About Windows box (from Fully Customizable WinVer)
// Rewritten on the shared settings snapshot. Every change to the dialog runs on the dialog's own thread: the
// WinEvent callback for a new box, a registered message for a settings change or for teardown. Fixes over upstream:
// inverted z-order check, leaked brushes and icons, GDI+ never shut down, relative positions applied twice, a logo
// child that shared the OK button's id, and a paint loop while the animated logo waited for its background.
// ============================================================================

namespace swc {

struct WinverControlId {
    PCWSTR name;
    int id;
};
static constexpr WinverControlId kWinverControls[] = {
    {L"LeftIcon", 0x3009},        {L"Separator", 0x3327},       {L"ProductName", 0x3500},
    {L"Version", 0x350B},         {L"Copyright", 0x350A},       {L"Spacer1", 0xCA03},
    {L"LegalNotice", 0x3513},     {L"Spacer2", 0x350D},         {L"LicenseInfo", 0x3512},
    {L"RegisteredUser1", 0x3507}, {L"RegisteredUser2", 0x3508}, {L"OkButton", IDOK},
};
constexpr int kWinverControlCount = ARRAYSIZE(kWinverControls);
constexpr int kIdxLeftIcon = 0, kIdxSeparator = 1, kIdxOkButton = kWinverControlCount - 1;

constexpr int kLogoCtlId = 0x5C00;
constexpr DWORD_PTR kRefDialog = 0, kRefSeparator = 1, kRefLogo = 2;
constexpr UINT_PTR kTimerFade = 0x5C01, kTimerGif = 0x5C02;
constexpr int kSlidePx = 8;
constexpr int kMaxLogoHeight = 72;
constexpr int kMaxLogoSide = 1024;
constexpr PCWSTR kModTitle = L"Seamless Winver Configurator";

struct DefaultGeom {
    HWND hWnd = nullptr;
    int x = 0, y = 0, w = 0, h = 0;
    bool visible = true;
    std::wstring label;
};

struct DialogState {
    ModConfig cfg;
    DefaultGeom defaults[kWinverControlCount];
    bool hasCtlColor[kWinverControlCount] = {};
    COLORREF ctlColor[kWinverControlCount] = {};
    int origW = 0, origH = 0;
    LONG origStyle = 0;
    std::wstring origTitle;
    HBRUSH bgBrush = nullptr, sepBrush = nullptr;
    COLORREF bgBrushColor = 0, sepBrushColor = 0;
    bool glassOn = false;  // our own glass is on the window
    HFONT font = nullptr, origFont = nullptr;
    std::wstring fontName;
    HICON customIcon = nullptr, origBig = nullptr, origSmall = nullptr;
    std::wstring customIconSpec;
    // Logo
    HWND logo = nullptr;
    std::unique_ptr<Gdiplus::Bitmap> logoBitmap;
    std::unique_ptr<Gdiplus::Image> gif;
    GUID gifDim = {};
    std::vector<UINT> gifDelays;
    UINT gifFrame = 0;
    int logoW = 0, logoH = 0;
    HBITMAP logoBack = nullptr;
    std::vector<std::wstring> errors;
    // Motion
    enum class Fade { None, In, Out } fade = Fade::None;
    ULONGLONG fadeStart = 0;
    DWORD fadeMs = 0;
    int finalX = 0, finalY = 0;
    bool layered = false, closeReady = false;
    WPARAM closeW = 0;
    LPARAM closeL = 0;
};

static std::atomic<HWND> g_dlgWnd{nullptr};
static DialogState* g_dlg;  // touched only on the dialog's thread
static HWINEVENTHOOK g_winEventHook;
static HWND g_ctrlWnd;  // message-only window on the thread that owns the WinEvent hook
static UINT g_msgSetup, g_msgReload, g_msgTeardown, g_msgCapture, g_msgShown;
static ULONG_PTR g_gdipToken;

static LRESULT CALLBACK DialogSubclassProc(HWND, UINT, WPARAM, LPARAM, UINT_PTR, DWORD_PTR);

static int ControlIndexFromId(int id) {
    for (int i = 0; i < kWinverControlCount; i++)
        if (kWinverControls[i].id == id) return i;
    return -1;
}

static int ControlIndexFromName(const std::wstring& name) {
    for (int i = 0; i < kWinverControlCount; i++)
        if (name == kWinverControls[i].name) return i;
    return -1;
}

static bool EnsureGdiplus() {
    if (g_gdipToken) return true;
    Gdiplus::GdiplusStartupInput input;
    return Gdiplus::GdiplusStartup(&g_gdipToken, &input, nullptr) == Gdiplus::Ok;
}

static bool FileExists(const std::wstring& path) {
    DWORD a = path.empty() ? INVALID_FILE_ATTRIBUTES : GetFileAttributesW(path.c_str());
    return a != INVALID_FILE_ATTRIBUTES && !(a & FILE_ATTRIBUTE_DIRECTORY);
}

static std::wstring ExpandEnv(const std::wstring& s) {
    DWORD n = ExpandEnvironmentStringsW(s.c_str(), nullptr, 0);
    if (!n) return s;
    std::wstring out(n, L'\0');
    DWORD w = ExpandEnvironmentStringsW(s.c_str(), out.data(), n);
    if (!w || w > n) return s;
    out.resize(w - 1);
    return out;
}

// {default.<Id>} is the control's stock text; {default.<Id>::start} and {default.<Id>::start/length} take part of it.
static std::wstring ExpandPlaceholders(const std::wstring& in, const DialogState& s) {
    static constexpr std::wstring_view kOpen = L"{default.";
    std::wstring out;
    size_t pos = 0;
    while (pos < in.size()) {
        size_t at = in.find(kOpen.data(), pos, kOpen.size());
        size_t close = at == std::wstring::npos ? std::wstring::npos : in.find(L'}', at);
        if (close == std::wstring::npos) {
            out.append(in, pos, std::wstring::npos);
            break;
        }
        out.append(in, pos, at - pos);
        std::wstring body = in.substr(at + kOpen.size(), close - at - kOpen.size());
        std::wstring name = body;
        size_t start = 0, len = std::wstring::npos;
        size_t colons = body.find(L"::");
        bool valid = true;
        if (colons != std::wstring::npos) {
            name = body.substr(0, colons);
            std::wstring range = body.substr(colons + 2);
            size_t slash = range.find(L'/');
            std::wstring a = range.substr(0, slash);
            std::wstring b = slash == std::wstring::npos ? L"" : range.substr(slash + 1);
            auto digits = [](const std::wstring& t) {
                return !t.empty() && std::all_of(t.begin(), t.end(), [](wchar_t c) { return iswdigit(c) != 0; });
            };
            valid = digits(a) && (b.empty() || digits(b));
            if (valid) {
                start = wcstoul(a.c_str(), nullptr, 10);
                if (!b.empty()) len = wcstoul(b.c_str(), nullptr, 10);
            }
        }
        int idx = valid ? ControlIndexFromName(name) : -1;
        if (idx < 0) {
            out.append(in, at, close - at + 1);  // not ours: keep the text as typed
        } else {
            const std::wstring& label = s.defaults[idx].label;
            if (start < label.size()) out.append(label, start, len);
        }
        pos = close + 1;
    }
    return out;
}

// "x;y;w;h"; an empty part or "d" keeps the stock value. Relative moves the control by x and y from where it was.
static void ParseGeometry(const ControlOverride& co, const DefaultGeom& base, int& x, int& y, int& w, int& h) {
    x = base.x, y = base.y, w = base.w, h = base.h;
    if (co.position.empty()) return;
    int* out[4] = {&x, &y, &w, &h};
    size_t start = 0;
    for (int i = 0; i < 4 && start <= co.position.size(); i++) {
        size_t semi = co.position.find(L';', start);
        if (semi == std::wstring::npos) semi = co.position.size();
        std::wstring part = co.position.substr(start, semi - start);
        part.erase(0, part.find_first_not_of(L" \t"));
        part.erase(part.find_last_not_of(L" \t") + 1);
        if (!part.empty() && part != L"d") {
            int v = _wtoi(part.c_str());
            *out[i] = (co.relativePosition && i < 2) ? *out[i] + v : v;
        }
        start = semi + 1;
    }
    w = std::max(w, 0);
    h = std::max(h, 0);
}

static HICON LoadIconFromSpec(const std::wstring& spec) {
    size_t semi = spec.rfind(L';');
    if (semi != std::wstring::npos) {
        std::wstring file = ExpandEnv(spec.substr(0, semi));
        HICON icon = nullptr;
        ExtractIconExW(file.c_str(), _wtoi(spec.c_str() + semi + 1), &icon, nullptr, 1);
        return icon;
    }
    return (HICON)LoadImageW(nullptr, ExpandEnv(spec).c_str(), IMAGE_ICON, 0, 0, LR_LOADFROMFILE | LR_DEFAULTSIZE);
}

static void SetBrush(HBRUSH& brush, COLORREF& have, bool want, COLORREF color) {
    if (brush && (!want || have != color)) {
        DeleteObject(brush);
        brush = nullptr;
    }
    if (want && !brush) {
        brush = CreateSolidBrush(color);
        have = color;
    }
}

// ---- Apply steps ---------------------------------------------------------------------------------------------------

static void ApplyIcon(HWND hWnd, DialogState& s) {
    const std::wstring& spec = s.cfg.customIcon;
    if (spec == s.customIconSpec) return;
    s.customIconSpec = spec;
    HICON old = s.customIcon;
    s.customIcon = spec.empty() ? nullptr : LoadIconFromSpec(spec);
    if (!spec.empty() && !s.customIcon) s.errors.push_back(std::format(L"Couldn't load the window icon:\n\n{}", spec));
    if (s.customIcon) {
        SendMessageW(hWnd, WM_SETICON, ICON_BIG, (LPARAM)s.customIcon);
        SendMessageW(hWnd, WM_SETICON, ICON_SMALL, (LPARAM)s.customIcon);
    } else {
        SendMessageW(hWnd, WM_SETICON, ICON_BIG, (LPARAM)s.origBig);
        SendMessageW(hWnd, WM_SETICON, ICON_SMALL, (LPARAM)s.origSmall);
    }
    if (old) DestroyIcon(old);
}

static void ApplyFrame(HWND hWnd, DialogState& s) {
    const ModConfig& c = s.cfg;
    // Only the system-menu bit changes. The box was taken before it showed, so its saved style has no WS_VISIBLE.
    LONG curStyle = GetWindowLongW(hWnd, GWL_STYLE);
    LONG style = (curStyle & ~WS_SYSMENU) | (s.origStyle & WS_SYSMENU) | (c.restoreCloseButton ? WS_SYSMENU : 0);
    if (curStyle != style) SetWindowLongW(hWnd, GWL_STYLE, style);
    // Hides the title-bar icon and its menu while the close button stays.
    WTA_OPTIONS opt{};
    opt.dwMask = WTNCA_NODRAWICON | WTNCA_NOSYSMENU;
    opt.dwFlags = c.removeTitleIcon ? opt.dwMask : 0;
    SetWindowThemeAttribute(hWnd, WTA_NONCLIENT, &opt, sizeof(opt));

    const std::wstring& title = c.titleText.empty() ? s.origTitle : c.titleText;
    WCHAR cur[256];
    GetWindowTextW(hWnd, cur, ARRAYSIZE(cur));
    if (title != cur) SetWindowTextW(hWnd, title.c_str());
}

// The dark glass every Seamless window uses: no system backdrop (DWMSBT_TRANSIENTWINDOW and Mica read as a light
// grey frost), the accent acrylic with a Mocha crust tint, the frame pulled over the whole box and a black body.
// Black is the one fill DWM leaves clear; any other colour lands on top of the glass as a lighter slab.
constexpr int kGlassTint = (int)0x012E1E1E;  // ABGR, the same tint as the launcher grid and every settings window

static void ApplyGlass(HWND hWnd, DialogState& s, bool on) {
    struct AccentPolicy { int state, flags, abgr, animation; };
    struct CompositionData { DWORD attribute; void* data; SIZE_T size; };
    using SetComposition_t = BOOL(WINAPI*)(HWND, CompositionData*);
    static auto setComposition =
        (SetComposition_t)(void*)GetProcAddress(GetModuleHandleW(L"user32.dll"), "SetWindowCompositionAttribute");
    if (on) {
        int backdrop = 1;  // DWMSBT_NONE
        DwmSetWindowAttribute(hWnd, 38 /* DWMWA_SYSTEMBACKDROP_TYPE */, &backdrop, sizeof(backdrop));
        DWM_BLURBEHIND bb{};
        bb.dwFlags = DWM_BB_ENABLE | DWM_BB_BLURREGION;
        bb.fEnable = TRUE;
        bb.hRgnBlur = CreateRectRgn(0, 0, -1, -1);
        DwmEnableBlurBehindWindow(hWnd, &bb);
        if (bb.hRgnBlur) DeleteObject(bb.hRgnBlur);
        if (setComposition) {
            AccentPolicy policy{4 /* ACCENT_ENABLE_ACRYLICBLURBEHIND */, 2, kGlassTint, 0};
            CompositionData data{19 /* WCA_ACCENT_POLICY */, &policy, sizeof(policy)};
            setComposition(hWnd, &data);
        }
        MARGINS margins{-1, -1, -1, -1};
        DwmExtendFrameIntoClientArea(hWnd, &margins);
        COLORREF none = 0xFFFFFFFE;  // DWMWA_COLOR_NONE: the title bar is the same glass
        DwmSetWindowAttribute(hWnd, 35 /* DWMWA_CAPTION_COLOR */, &none, sizeof(none));
        s.glassOn = true;
        return;
    }
    if (s.glassOn) {
        if (setComposition) {
            AccentPolicy policy{0, 0, 0, 0};
            CompositionData data{19 /* WCA_ACCENT_POLICY */, &policy, sizeof(policy)};
            setComposition(hWnd, &data);
        }
        DWM_BLURBEHIND bb{};
        bb.dwFlags = DWM_BB_ENABLE;
        bb.fEnable = FALSE;
        DwmEnableBlurBehindWindow(hWnd, &bb);
        MARGINS margins{};
        DwmExtendFrameIntoClientArea(hWnd, &margins);
        s.glassOn = false;
    }
    int backdrop = 0;  // DWMSBT_AUTO
    DwmSetWindowAttribute(hWnd, 38 /* DWMWA_SYSTEMBACKDROP_TYPE */, &backdrop, sizeof(backdrop));
}

// Every line of text in the box in one font (FiraCode by default), at the size the box already uses.
static void ApplyFont(HWND hWnd, DialogState& s) {
    const std::wstring& name = s.cfg.textFont;
    if (!s.origFont) s.origFont = (HFONT)SendMessageW(hWnd, WM_GETFONT, 0, 0);
    if (name == s.fontName && (s.font || name.empty())) return;
    HFONT old = s.font;
    s.font = nullptr;
    s.fontName = name;
    if (!name.empty() && s.origFont) {
        LOGFONTW lf{};
        GetObjectW(s.origFont, sizeof(lf), &lf);
        wcsncpy_s(lf.lfFaceName, name.c_str(), _TRUNCATE);
        lf.lfQuality = CLEARTYPE_QUALITY;
        s.font = CreateFontIndirectW(&lf);
    }
    HFONT use = s.font ? s.font : s.origFont;
    for (int i = 0; i < kWinverControlCount; i++)
        if (HWND h = s.defaults[i].hWnd; h && i != kIdxLeftIcon && i != kIdxSeparator) SendMessageW(h, WM_SETFONT, (WPARAM)use, TRUE);
    if (old) DeleteObject(old);
}

static void ApplyColors(HWND hWnd, DialogState& s) {
    const ModConfig& c = s.cfg;
    constexpr COLORREF kDefault = 0xFFFFFFFF;  // DWMWA_COLOR_DEFAULT
    BOOL dark = c.darkMode;
    DwmSetWindowAttribute(hWnd, 20 /* DWMWA_USE_IMMERSIVE_DARK_MODE */, &dark, sizeof(dark));
    // With glass the caption keeps no colour of its own, so the backdrop shows through it.
    COLORREF caption = (c.hasBarColor && !c.glassBackdrop) ? c.barColor : kDefault;
    COLORREF text = c.hasTitleColor ? c.titleColor : kDefault;
    COLORREF border = c.hasBorderColor ? c.borderColor : kDefault;
    DwmSetWindowAttribute(hWnd, 35 /* DWMWA_CAPTION_COLOR */, &caption, sizeof(caption));
    DwmSetWindowAttribute(hWnd, 36 /* DWMWA_TEXT_COLOR */, &text, sizeof(text));
    DwmSetWindowAttribute(hWnd, 34 /* DWMWA_BORDER_COLOR */, &border, sizeof(border));
    ApplyGlass(hWnd, s, c.glassBackdrop);

    SetBrush(s.bgBrush, s.bgBrushColor, c.hasBgColor || c.glassBackdrop, c.glassBackdrop ? RGB(0, 0, 0) : c.bgColor);
    SetBrush(s.sepBrush, s.sepBrushColor, c.hasSepColor, c.sepColor);
    if (HWND ok = s.defaults[kIdxOkButton].hWnd) {
        if (c.darkMode) SetWindowTheme(ok, L"DarkMode_Explorer", nullptr);
        else SetWindowTheme(ok, nullptr, nullptr);
    }
}

static void ApplySize(HWND hWnd, DialogState& s) {
    const ModConfig& c = s.cfg;
    int w = s.origW, h = s.origH;
    if (c.sizeEnabled) {
        if (c.sizeWidth > 0) w = c.sizeWidth;
        if (c.sizeHeight > 0) h = c.sizeHeight;
    }
    RECT r;
    GetWindowRect(hWnd, &r);
    if (r.right - r.left != w || r.bottom - r.top != h)
        SetWindowPos(hWnd, nullptr, 0, 0, w, h, SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE);
}

struct MonitorList {
    std::vector<RECT> work;
};

static BOOL CALLBACK CollectMonitor(HMONITOR mon, HDC, LPRECT, LPARAM p) {
    MONITORINFO mi{sizeof(mi)};
    if (GetMonitorInfoW(mon, &mi)) reinterpret_cast<MonitorList*>(p)->work.push_back(mi.rcWork);
    return TRUE;
}

static void ApplyStartPosition(HWND hWnd, const ModConfig& c) {
    if (!c.posEnabled) return;
    RECT r;
    GetWindowRect(hWnd, &r);
    int x = c.posX, y = c.posY;
    if (c.posCenter) {
        RECT work{};
        MonitorList list;
        EnumDisplayMonitors(nullptr, nullptr, CollectMonitor, (LPARAM)&list);
        int index = c.posMonitor - 1;
        if (index >= 0 && index < (int)list.work.size()) {
            work = list.work[index];
        } else {
            MONITORINFO mi{sizeof(mi)};
            if (!GetMonitorInfoW(MonitorFromWindow(hWnd, MONITOR_DEFAULTTONEAREST), &mi)) return;
            work = mi.rcWork;
        }
        x += work.left + ((work.right - work.left) - (r.right - r.left)) / 2;
        y += work.top + ((work.bottom - work.top) - (r.bottom - r.top)) / 2;
    }
    SetWindowPos(hWnd, nullptr, x, y, 0, 0, SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE);
}

static void ApplyTopmost(HWND hWnd, const ModConfig& c) {
    bool topmost = (GetWindowLongW(hWnd, GWL_EXSTYLE) & WS_EX_TOPMOST) != 0;
    if (topmost != c.alwaysOnTop)
        SetWindowPos(hWnd, c.alwaysOnTop ? HWND_TOPMOST : HWND_NOTOPMOST, 0, 0, 0, 0,
                     SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
}

static void ApplyControls(HWND hWnd, DialogState& s) {
    const ModConfig& c = s.cfg;
    int diffX = 0, diffY = 0;
    if (c.sizeEnabled && c.expandControls) {
        RECT r;
        GetWindowRect(hWnd, &r);
        diffX = (r.right - r.left) - s.origW;
        diffY = (r.bottom - r.top) - s.origH;
    }
    for (int i = 0; i < kWinverControlCount; i++) {
        const DefaultGeom& d = s.defaults[i];
        if (!d.hWnd) continue;
        DefaultGeom base = d;
        if (i == kIdxOkButton) {
            base.x += diffX;
            if (c.realignOkButton) base.y += diffY;
        } else if (i != kIdxLeftIcon) {
            base.w += diffX;
        }
        auto it = c.controls.find(kWinverControls[i].name);
        const ControlOverride* co = it == c.controls.end() ? nullptr : &it->second;
        int x = base.x, y = base.y, w = base.w, h = base.h;
        if (co) ParseGeometry(*co, base, x, y, w, h);
        s.hasCtlColor[i] = co && co->hasTextColor;
        s.ctlColor[i] = co ? co->textColor : 0;

        std::wstring label = co && !co->label.empty() ? ExpandPlaceholders(co->label, s) : d.label;
        int len = GetWindowTextLengthW(d.hWnd);
        std::wstring cur(len + 1, L'\0');
        cur.resize(GetWindowTextW(d.hWnd, cur.data(), len + 1));
        if (cur != label) SetWindowTextW(d.hWnd, label.c_str());

        RECT r;
        GetWindowRect(d.hWnd, &r);
        MapWindowPoints(HWND_DESKTOP, hWnd, (POINT*)&r, 2);
        if (r.left != x || r.top != y || r.right - r.left != w || r.bottom - r.top != h)
            SetWindowPos(d.hWnd, nullptr, x, y, w, h, SWP_NOZORDER | SWP_NOACTIVATE);

        bool visible = co && co->hidden ? false : d.visible;
        if (((GetWindowLongW(d.hWnd, GWL_STYLE) & WS_VISIBLE) != 0) != visible)
            ShowWindow(d.hWnd, visible ? SW_SHOWNA : SW_HIDE);

        if (co && co->insertAfter != L"Default") {
            HWND after = nullptr;
            bool have = true;  // HWND_TOP is 0, so a null check would skip it
            if (co->insertAfter == L"Top") after = HWND_TOP;
            else if (co->insertAfter == L"Bottom") after = HWND_BOTTOM;
            else if (co->insertAfter == L"LogoImage") have = (after = s.logo) != nullptr;
            else if (int j = ControlIndexFromName(co->insertAfter); j >= 0 && j != i) have = (after = s.defaults[j].hWnd) != nullptr;
            else have = false;
            if (have) SetWindowPos(d.hWnd, after, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
        }
    }
}

static void ResetLogoImage(DialogState& s) {
    if (s.logo) KillTimer(s.logo, kTimerGif);
    s.logoBitmap.reset();
    s.gif.reset();
    s.gifDelays.clear();
    s.gifFrame = 0;
    if (s.logoBack) {
        DeleteObject(s.logoBack);
        s.logoBack = nullptr;
    }
}

static UINT GifDelayMs(const DialogState& s) {
    UINT d10 = s.gifDelays.empty() ? 0 : s.gifDelays[s.gifFrame % s.gifDelays.size()];
    return d10 ? std::max(d10 * 10U, 10U) : 100U;
}

static void ApplyLogo(HWND hWnd, DialogState& s) {
    const ModConfig& c = s.cfg;
    ResetLogoImage(s);
    if (!c.logoEnabled) {
        if (s.logo) ShowWindow(s.logo, SW_HIDE);
        return;
    }
    std::wstring path = ExpandEnv(c.logoPath);
    if (!FileExists(path)) {
        s.errors.push_back(std::format(L"The logo file is missing:\n\n{}", c.logoPath));
        if (s.logo) ShowWindow(s.logo, SW_HIDE);
        return;
    }
    if (!EnsureGdiplus()) return;
    std::unique_ptr<Gdiplus::Image> img(Gdiplus::Image::FromFile(path.c_str(), FALSE));
    if (!img || img->GetLastStatus() != Gdiplus::Ok || !img->GetWidth() || !img->GetHeight()) {
        s.errors.push_back(std::format(L"The logo file couldn't be read as a picture:\n\n{}", c.logoPath));
        if (s.logo) ShowWindow(s.logo, SW_HIDE);
        return;
    }
    const int iw = (int)img->GetWidth(), ih = (int)img->GetHeight();
    int w = c.logoWidth, h = c.logoHeight < 0 ? kMaxLogoHeight : c.logoHeight;
    if (w == 0 && h > 0) w = iw * h / ih;
    if (w == 0) w = iw;
    if (h == 0) h = ih * w / iw;
    if (w > kMaxLogoSide || h > kMaxLogoSide) {  // a huge picture at native size would swamp the box
        const double k = (double)kMaxLogoSide / std::max(w, h);
        w = (int)(w * k), h = (int)(h * k);
    }
    w = std::max(w, 1);
    h = std::max(h, 1);
    s.logoW = w, s.logoH = h;

    GUID dim = Gdiplus::FrameDimensionTime;
    UINT frames = img->GetFrameCount(&dim);
    UINT propSize = frames > 1 ? img->GetPropertyItemSize(PropertyTagFrameDelay) : 0;
    if (propSize >= sizeof(Gdiplus::PropertyItem)) {
        std::vector<BYTE> buf(propSize);
        auto* item = reinterpret_cast<Gdiplus::PropertyItem*>(buf.data());
        if (img->GetPropertyItem(PropertyTagFrameDelay, propSize, item) == Gdiplus::Ok) {
            UINT n = std::min<UINT>(frames, item->length / sizeof(UINT));
            auto* delays = reinterpret_cast<const UINT*>(item->value);
            s.gifDelays.assign(delays, delays + n);
        }
    }
    if (frames > 1 && !s.gifDelays.empty()) {
        s.gifDim = dim;
        s.gif = std::move(img);
        s.gif->SelectActiveFrame(&s.gifDim, 0);
    } else {
        // A still picture is scaled once, so painting is a plain copy.
        s.logoBitmap = std::make_unique<Gdiplus::Bitmap>(w, h, PixelFormat32bppPARGB);
        Gdiplus::Graphics g(s.logoBitmap.get());
        g.SetInterpolationMode(Gdiplus::InterpolationModeHighQualityBicubic);
        g.DrawImage(img.get(), Gdiplus::Rect(0, 0, w, h), 0, 0, iw, ih, Gdiplus::UnitPixel);
    }

    if (!s.logo) {
        s.logo = CreateWindowExW(0, WC_STATICW, L"", WS_CHILD, 0, 0, 0, 0, hWnd, (HMENU)(INT_PTR)kLogoCtlId,
                                 GetModuleHandleW(nullptr), nullptr);
        if (!s.logo) return;
        SetWindowSubclass(s.logo, DialogSubclassProc, kRefLogo, 0);
    }
    RECT client;
    GetClientRect(hWnd, &client);
    int x = c.logoCenter ? (client.right - w) / 2 + c.logoX : c.logoX;
    SetWindowPos(s.logo, nullptr, x, c.logoY, w, h, SWP_NOZORDER | SWP_NOACTIVATE);
    ShowWindow(s.logo, SW_SHOWNA);
    InvalidateRect(s.logo, nullptr, FALSE);
    if (s.gif) SetTimer(s.logo, kTimerGif, GifDelayMs(s), nullptr);
    // With no colour of its own behind it, the logo sits on a copy of what the box draws there.
    if (!c.hasBgColor) PostMessageW(hWnd, g_msgCapture, 0, 0);
}

static void CaptureLogoBackground(HWND hWnd, DialogState& s) {
    if (!s.logo || !IsWindowVisible(s.logo)) return;
    RECT lr;
    GetWindowRect(s.logo, &lr);
    MapWindowPoints(HWND_DESKTOP, hWnd, (POINT*)&lr, 2);
    RECT client;
    GetClientRect(hWnd, &client);
    if (client.right <= 0 || client.bottom <= 0) return;
    ShowWindow(s.logo, SW_HIDE);
    RedrawWindow(hWnd, &lr, nullptr, RDW_INVALIDATE | RDW_ERASE | RDW_UPDATENOW);
    HDC screen = GetDC(hWnd);
    HDC full = CreateCompatibleDC(screen);
    HBITMAP fullBmp = CreateCompatibleBitmap(screen, client.right, client.bottom);
    HGDIOBJ oldFull = SelectObject(full, fullBmp);
    if (!PrintWindow(hWnd, full, PW_CLIENTONLY | PW_RENDERFULLCONTENT))
        BitBlt(full, 0, 0, client.right, client.bottom, screen, 0, 0, SRCCOPY);
    HDC cut = CreateCompatibleDC(screen);
    HBITMAP cutBmp = CreateCompatibleBitmap(screen, lr.right - lr.left, lr.bottom - lr.top);
    HGDIOBJ oldCut = SelectObject(cut, cutBmp);
    BitBlt(cut, 0, 0, lr.right - lr.left, lr.bottom - lr.top, full, lr.left, lr.top, SRCCOPY);
    SelectObject(cut, oldCut);
    SelectObject(full, oldFull);
    DeleteDC(cut);
    DeleteDC(full);
    DeleteObject(fullBmp);
    ReleaseDC(hWnd, screen);
    if (s.logoBack) DeleteObject(s.logoBack);
    s.logoBack = cutBmp;
    ShowWindow(s.logo, SW_SHOWNA);
    InvalidateRect(s.logo, nullptr, FALSE);
}

static void PaintLogo(HWND logo, DialogState& s) {
    PAINTSTRUCT ps;
    HDC hdc = BeginPaint(logo, &ps);
    RECT rc;
    GetClientRect(logo, &rc);
    HDC mem = CreateCompatibleDC(hdc);
    HBITMAP bmp = CreateCompatibleBitmap(hdc, rc.right, rc.bottom);
    HGDIOBJ old = SelectObject(mem, bmp);
    if (s.bgBrush) {
        FillRect(mem, &rc, s.bgBrush);
    } else if (s.logoBack) {
        HDC src = CreateCompatibleDC(hdc);
        HGDIOBJ oldSrc = SelectObject(src, s.logoBack);
        BitBlt(mem, 0, 0, rc.right, rc.bottom, src, 0, 0, SRCCOPY);
        SelectObject(src, oldSrc);
        DeleteDC(src);
    } else {
        FillRect(mem, &rc, GetSysColorBrush(COLOR_WINDOW));
    }
    {
        Gdiplus::Graphics g(mem);
        if (s.gif) {
            g.SetInterpolationMode(Gdiplus::InterpolationModeHighQualityBicubic);
            g.DrawImage(s.gif.get(), 0, 0, s.logoW, s.logoH);
        } else if (s.logoBitmap) {
            g.DrawImage(s.logoBitmap.get(), 0, 0);
        }
    }
    BitBlt(hdc, 0, 0, rc.right, rc.bottom, mem, 0, 0, SRCCOPY);
    SelectObject(mem, old);
    DeleteObject(bmp);
    DeleteDC(mem);
    EndPaint(logo, &ps);
}

// The stock Windows banner above the separator is a light picture. With a colour of our own it is redrawn on that
// colour: each pixel is split into its paint and the white under it, dark text paint becomes the text colour, the
// coloured logo keeps its colour, and the white becomes the background.
static void RecolorBanner(HWND hWnd, DialogState& s, const RECT& painted) {
    int bandBottom = s.defaults[kIdxSeparator].hWnd ? s.defaults[kIdxSeparator].y : 0;
    RECT client, band;
    GetClientRect(hWnd, &client);
    RECT full{0, 0, client.right, std::min<LONG>(bandBottom, client.bottom)};
    if (!IntersectRect(&band, &full, &painted)) return;
    const int w = band.right - band.left, h = band.bottom - band.top;
    HDC hdc = GetDCEx(hWnd, nullptr, DCX_CACHE | DCX_CLIPCHILDREN);
    if (!hdc) return;
    BITMAPINFO bi{};
    bi.bmiHeader = {sizeof(BITMAPINFOHEADER), w, -h, 1, 32, BI_RGB};
    void* bits = nullptr;
    HBITMAP dib = CreateDIBSection(hdc, &bi, DIB_RGB_COLORS, &bits, nullptr, 0);
    if (dib && bits) {
        HDC mem = CreateCompatibleDC(hdc);
        HGDIOBJ old = SelectObject(mem, dib);
        BitBlt(mem, 0, 0, w, h, hdc, band.left, band.top, SRCCOPY);
        GdiFlush();
        const COLORREF bg = s.bgBrushColor;
        const COLORREF tx = s.cfg.hasTextColor ? s.cfg.textColor : (s.cfg.darkMode ? RGB(255, 255, 255) : RGB(0, 0, 0));
        const int bgc[3] = {GetBValue(bg), GetGValue(bg), GetRValue(bg)};
        const int txc[3] = {GetBValue(tx), GetGValue(tx), GetRValue(tx)};
        auto* px = static_cast<BYTE*>(bits);
        // Only a freshly drawn light banner is redrawn, never one that already took the colour.
        int light = 0;
        for (int i = 0; i < w * h; i++)
            if (std::min({px[i * 4], px[i * 4 + 1], px[i * 4 + 2]}) > 235) light++;
        if (light * 4 < w * h) px = nullptr;
        for (int i = 0; px && i < w * h; i++, px += 4) {
            if (px[0] == bgc[0] && px[1] == bgc[1] && px[2] == bgc[2]) continue;
            int lo = std::min({px[0], px[1], px[2]});
            int a = 255 - lo;  // how much paint sits on the white, 0..255
            int out[3];
            if (a < 16) {  // the banner's own off-white
                out[0] = bgc[0], out[1] = bgc[1], out[2] = bgc[2];
            } else {
                int paint[3], hi = 0;
                for (int k = 0; k < 3; k++) {
                    paint[k] = std::clamp((px[k] - lo) * 255 / a, 0, 255);
                    hi = std::max(hi, paint[k]);
                }
                const int* target = hi < 64 ? txc : paint;  // near-black paint is text
                for (int k = 0; k < 3; k++) out[k] = (target[k] * a + bgc[k] * (255 - a)) / 255;
            }
            px[0] = (BYTE)out[0], px[1] = (BYTE)out[1], px[2] = (BYTE)out[2], px[3] = 0;
        }
        BitBlt(hdc, band.left, band.top, w, h, mem, 0, 0, SRCCOPY);
        SelectObject(mem, old);
        DeleteDC(mem);
    }
    if (dib) DeleteObject(dib);
    ReleaseDC(hWnd, hdc);
}

// Our own banner in place of the stock light picture: the four-tile Windows logo and the Windows name, both in the
// blue to mauve gradient, centred in the band above the separator. Drawn premultiplied, so on the glass the clear
// parts stay glass and on a solid box they take its colour.
static std::wstring WindowsName() {
    RTL_OSVERSIONINFOW v{sizeof(v)};
    RtlGetVersion(&v);
    return v.dwBuildNumber >= 22000 ? L"Windows 11" : L"Windows 10";
}

static void PaintOwnBanner(HWND hWnd, DialogState& s, HDC hdc) {
    RECT client;
    GetClientRect(hWnd, &client);
    const int w = client.right, h = s.defaults[kIdxSeparator].hWnd ? s.defaults[kIdxSeparator].y : 0;
    if (w <= 0 || h <= 8 || !EnsureGdiplus()) return;
    BITMAPINFO bi{};
    bi.bmiHeader = {sizeof(BITMAPINFOHEADER), w, -h, 1, 32, BI_RGB};
    void* bits = nullptr;
    HBITMAP dib = CreateDIBSection(hdc, &bi, DIB_RGB_COLORS, &bits, nullptr, 0);
    if (!dib || !bits) {
        if (dib) DeleteObject(dib);
        return;
    }
    const COLORREF bg = s.glassOn ? RGB(0, 0, 0) : s.bgBrushColor;
    const DWORD fill = s.glassOn ? 0 : (0xFF000000u | (GetRValue(bg) << 16) | (GetGValue(bg) << 8) | GetBValue(bg));
    std::fill_n(static_cast<DWORD*>(bits), (size_t)w * h, fill);
    {
        Gdiplus::Bitmap canvas(w, h, w * 4, PixelFormat32bppPARGB, static_cast<BYTE*>(bits));
        Gdiplus::Graphics g(&canvas);
        g.SetSmoothingMode(Gdiplus::SmoothingModeAntiAlias);
        g.SetPixelOffsetMode(Gdiplus::PixelOffsetModeHalf);
        g.SetTextRenderingHint(Gdiplus::TextRenderingHintAntiAliasGridFit);

        std::wstring name = s.cfg.bannerText.empty() ? WindowsName() : s.cfg.bannerText;
        const float logo = std::round(h * 0.46f);
        const float gap = std::max(2.0f, std::round(logo * 0.06f));
        const float tile = (logo - gap) / 2;
        const std::wstring face = s.cfg.textFont.empty() ? L"Segoe UI" : s.cfg.textFont;
        Gdiplus::FontFamily family(face.c_str());
        Gdiplus::Font font(family.IsAvailable() ? &family : Gdiplus::FontFamily::GenericSansSerif(), logo * 0.62f,
                           Gdiplus::FontStyleRegular, Gdiplus::UnitPixel);
        Gdiplus::StringFormat fmt(Gdiplus::StringFormat::GenericTypographic());
        fmt.SetFormatFlags(fmt.GetFormatFlags() | Gdiplus::StringFormatFlagsNoWrap);
        Gdiplus::RectF ext;
        g.MeasureString(name.c_str(), (INT)name.size(), &font, Gdiplus::PointF(0, 0), &fmt, &ext);
        const float space = std::round(logo * 0.38f);
        const float total = logo + space + ext.Width;
        const float x0 = std::round((w - total) / 2), y0 = std::round((h - logo) / 2);

        auto blue = Gdiplus::Color(255, GetRValue(kMochaBlue), GetGValue(kMochaBlue), GetBValue(kMochaBlue));
        auto mauve = Gdiplus::Color(255, GetRValue(kMochaMauve), GetGValue(kMochaMauve), GetBValue(kMochaMauve));
        Gdiplus::LinearGradientBrush paint(Gdiplus::PointF(x0, y0), Gdiplus::PointF(x0 + total, y0 + logo), blue, mauve);
        const float r = std::max(1.5f, tile * 0.18f);
        for (int i = 0; i < 4; i++) {
            float tx = x0 + (i % 2) * (tile + gap), ty = y0 + (i / 2) * (tile + gap);
            Gdiplus::GraphicsPath path;
            path.AddArc(tx, ty, 2 * r, 2 * r, 180, 90);
            path.AddArc(tx + tile - 2 * r, ty, 2 * r, 2 * r, 270, 90);
            path.AddArc(tx + tile - 2 * r, ty + tile - 2 * r, 2 * r, 2 * r, 0, 90);
            path.AddArc(tx, ty + tile - 2 * r, 2 * r, 2 * r, 90, 90);
            path.CloseFigure();
            g.FillPath(&paint, &path);
        }
        const float ty = std::round(y0 + (logo - ext.Height) / 2);
        g.DrawString(name.c_str(), (INT)name.size(), &font, Gdiplus::PointF(x0 + logo + space, ty), &fmt, &paint);
    }
    HDC mem = CreateCompatibleDC(hdc);
    HGDIOBJ old = SelectObject(mem, dib);
    BitBlt(hdc, 0, 0, w, h, mem, 0, 0, SRCCOPY);
    SelectObject(mem, old);
    DeleteDC(mem);
    DeleteObject(dib);
}

static void ShowErrors(HWND hWnd, DialogState& s) {
    std::vector<std::wstring> errors = std::move(s.errors);
    s.errors.clear();
    for (const auto& e : errors) MessageBoxW(hWnd, e.c_str(), kModTitle, MB_OK | MB_ICONWARNING);
}

static void ApplyAll(HWND hWnd, DialogState& s, bool reposition) {
    ApplyIcon(hWnd, s);
    ApplyFrame(hWnd, s);
    ApplyColors(hWnd, s);
    ApplyFont(hWnd, s);
    ApplySize(hWnd, s);
    if (reposition) ApplyStartPosition(hWnd, s.cfg);
    ApplyTopmost(hWnd, s.cfg);
    ApplyLogo(hWnd, s);
    ApplyControls(hWnd, s);
    SetWindowPos(hWnd, nullptr, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE | SWP_FRAMECHANGED);
    RedrawWindow(hWnd, nullptr, nullptr, RDW_ERASE | RDW_INVALIDATE | RDW_FRAME | RDW_ALLCHILDREN);
}

// ---- Motion: fade plus a short slide on open and close ------------------------------------------------------------

static void SetLayered(HWND hWnd, DialogState& s, bool on, BYTE alpha) {
    LONG ex = GetWindowLongW(hWnd, GWL_EXSTYLE);
    if (on) {
        if (!(ex & WS_EX_LAYERED)) {
            SetWindowLongW(hWnd, GWL_EXSTYLE, ex | WS_EX_LAYERED);
            s.layered = true;
        }
        SetLayeredWindowAttributes(hWnd, 0, alpha, LWA_ALPHA);
    } else if (s.layered) {
        SetWindowLongW(hWnd, GWL_EXSTYLE, ex & ~WS_EX_LAYERED);
        s.layered = false;
        RedrawWindow(hWnd, nullptr, nullptr, RDW_ERASE | RDW_INVALIDATE | RDW_FRAME | RDW_ALLCHILDREN);
    }
}

static void StartFade(HWND hWnd, DialogState& s, DialogState::Fade kind, DWORD ms) {
    RECT r;
    GetWindowRect(hWnd, &r);
    if (s.fade == DialogState::Fade::None) s.finalX = r.left, s.finalY = r.top;
    s.fade = kind;
    s.fadeMs = ms;
    s.fadeStart = GetTickCount64();
    SetTimer(hWnd, kTimerFade, 10, nullptr);
}

static void StepFade(HWND hWnd, DialogState& s) {
    double t = s.fadeMs ? double(GetTickCount64() - s.fadeStart) / s.fadeMs : 1.0;
    t = std::clamp(t, 0.0, 1.0);
    double eased = 1.0 - (1.0 - t) * (1.0 - t) * (1.0 - t);
    bool opening = s.fade == DialogState::Fade::In;
    double shown = opening ? eased : 1.0 - eased;
    SetLayeredWindowAttributes(hWnd, 0, (BYTE)std::lround(255 * shown), LWA_ALPHA);
    int offset = (int)std::lround(kSlidePx * (1.0 - shown));
    SetWindowPos(hWnd, nullptr, s.finalX, s.finalY + offset, 0, 0, SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE);
    if (t < 1.0) return;
    KillTimer(hWnd, kTimerFade);
    s.fade = DialogState::Fade::None;
    if (opening) {
        SetLayered(hWnd, s, false, 255);
    } else {
        s.closeReady = true;
        SendMessageW(hWnd, WM_COMMAND, s.closeW, s.closeL);
    }
}

// ---- Take, release ------------------------------------------------------------------------------------------------

static BOOL CALLBACK CloseIfOwnedMessageBox(HWND h, LPARAM owner) {
    WCHAR cls[16];
    if (GetWindow(h, GW_OWNER) == (HWND)owner && GetClassNameW(h, cls, ARRAYSIZE(cls)) && !wcscmp(cls, L"#32770"))
        PostMessageW(h, WM_CLOSE, 0, 0);
    return TRUE;
}

static void CloseOwnedMessageBoxes(HWND owner) {
    EnumThreadWindows(GetWindowThreadProcessId(owner, nullptr), CloseIfOwnedMessageBox, (LPARAM)owner);
}

// Runs on the dialog thread. restore puts the stock box back (mod turned off); otherwise the box is closing.
static void ReleaseDialog(HWND hWnd, bool restore) {
    DialogState* s = g_dlg;
    if (!s) return;
    KillTimer(hWnd, kTimerFade);
    ResetLogoImage(*s);
    if (s->logo) {
        RemoveWindowSubclass(s->logo, DialogSubclassProc, kRefLogo);
        if (restore) DestroyWindow(s->logo);
    }
    if (HWND sep = s->defaults[kIdxSeparator].hWnd) RemoveWindowSubclass(sep, DialogSubclassProc, kRefSeparator);
    RemoveWindowSubclass(hWnd, DialogSubclassProc, kRefDialog);
    if (restore) {
        CloseOwnedMessageBoxes(hWnd);
        SetLayered(hWnd, *s, false, 255);
        if (s->fade != DialogState::Fade::None)
            SetWindowPos(hWnd, nullptr, s->finalX, s->finalY, 0, 0, SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE);
        s->cfg = ModConfig{};
        s->cfg.themePreset = ThemePreset::Stock;
        s->cfg.darkMode = false;
        s->cfg.restoreCloseButton = false;
        s->cfg.posEnabled = false;
        ApplyIcon(hWnd, *s);
        ApplyFrame(hWnd, *s);
        ApplyColors(hWnd, *s);
        ApplyFont(hWnd, *s);
        ApplySize(hWnd, *s);
        ApplyTopmost(hWnd, s->cfg);
        ApplyControls(hWnd, *s);
        if (HWND ok = s->defaults[kIdxOkButton].hWnd) SetWindowTheme(ok, nullptr, nullptr);
        SetWindowPos(hWnd, nullptr, 0, 0, 0, 0,
                     SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE | SWP_FRAMECHANGED);
        RedrawWindow(hWnd, nullptr, nullptr, RDW_ERASE | RDW_INVALIDATE | RDW_FRAME | RDW_ALLCHILDREN | RDW_UPDATENOW);
    }
    if (s->bgBrush) DeleteObject(s->bgBrush);
    if (s->sepBrush) DeleteObject(s->sepBrush);
    if (s->font) DeleteObject(s->font);  // restore already gave the controls their own font back
    if (s->customIcon) DestroyIcon(s->customIcon);
    delete s;
    g_dlg = nullptr;
    g_dlgWnd = nullptr;
}

// Runs on the dialog thread. created: the box is new and not shown yet, so it can be placed and faded in.
static bool TakeDialog(HWND hWnd, bool created) {
    if (g_dlg) return false;
    auto* s = new DialogState;
    s->cfg = SnapshotConfig();
    if (s->cfg.classicEnabled) {  // the classic box keeps its own look
        delete s;
        return false;
    }
    for (int i = 0; i < kWinverControlCount; i++) {
        HWND item = GetDlgItem(hWnd, kWinverControls[i].id);
        if (!item) continue;
        DefaultGeom& d = s->defaults[i];
        d.hWnd = item;
        RECT r;
        GetWindowRect(item, &r);
        MapWindowPoints(HWND_DESKTOP, hWnd, (POINT*)&r, 2);
        d.x = r.left, d.y = r.top, d.w = r.right - r.left, d.h = r.bottom - r.top;
        d.visible = (GetWindowLongW(item, GWL_STYLE) & WS_VISIBLE) != 0;
        int len = GetWindowTextLengthW(item);
        d.label.resize(len + 1);
        d.label.resize(GetWindowTextW(item, d.label.data(), len + 1));
    }
    RECT r;
    GetWindowRect(hWnd, &r);
    s->origW = r.right - r.left, s->origH = r.bottom - r.top;
    s->origStyle = GetWindowLongW(hWnd, GWL_STYLE);
    int len = GetWindowTextLengthW(hWnd);
    s->origTitle.resize(len + 1);
    s->origTitle.resize(GetWindowTextW(hWnd, s->origTitle.data(), len + 1));
    s->origBig = (HICON)SendMessageW(hWnd, WM_GETICON, ICON_BIG, 0);
    s->origSmall = (HICON)SendMessageW(hWnd, WM_GETICON, ICON_SMALL, 0);

    g_dlg = s;
    g_dlgWnd = hWnd;
    SetWindowSubclass(hWnd, DialogSubclassProc, kRefDialog, 0);
    if (HWND sep = s->defaults[kIdxSeparator].hWnd) SetWindowSubclass(sep, DialogSubclassProc, kRefSeparator, 0);

    ApplyAll(hWnd, *s, created);
    if (created && s->cfg.flyoutAnimation && GetMotionDurationMs(true, s->cfg.animationSpeed))
        SetLayered(hWnd, *s, true, 0);
    if (!created) ShowErrors(hWnd, *s);
    return true;
}

static void OnDialogShown(HWND hWnd, DialogState& s) {
    if (s.cfg.removeFirstFocus) SetFocus(nullptr);
    if (s.layered) {
        if (DWORD ms = GetMotionDurationMs(true, s.cfg.animationSpeed)) StartFade(hWnd, s, DialogState::Fade::In, ms);
        else SetLayered(hWnd, s, false, 255);
    }
    if (s.logo && !s.bgBrush) PostMessageW(hWnd, g_msgCapture, 0, 0);
    ShowErrors(hWnd, s);
}

static LRESULT CALLBACK DialogSubclassProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam, UINT_PTR ref,
                                           DWORD_PTR) {
    DialogState* s = g_dlg;
    if (!s) return DefSubclassProc(hWnd, msg, wParam, lParam);

    if (ref == kRefLogo) {
        if (msg == WM_ERASEBKGND) return 1;
        if (msg == WM_PAINT) {
            PaintLogo(hWnd, *s);
            return 0;
        }
        if (msg == WM_TIMER && wParam == kTimerGif && s->gif) {
            s->gifFrame = (s->gifFrame + 1) % (UINT)s->gifDelays.size();
            s->gif->SelectActiveFrame(&s->gifDim, s->gifFrame);
            SetTimer(hWnd, kTimerGif, GifDelayMs(*s), nullptr);
            InvalidateRect(hWnd, nullptr, FALSE);
            return 0;
        }
        return DefSubclassProc(hWnd, msg, wParam, lParam);
    }

    if (ref == kRefSeparator) {
        if (msg == WM_PAINT && s->sepBrush) {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            RECT rc;
            GetClientRect(hWnd, &rc);
            rc.left -= 1, rc.right += 1;  // the stock line leaves a light pixel at each end
            FrameRect(hdc, &rc, s->sepBrush);
            EndPaint(hWnd, &ps);
            return 0;
        }
        return DefSubclassProc(hWnd, msg, wParam, lParam);
    }

    // The dialog itself.
    if (msg == g_msgReload) {
        s->cfg = SnapshotConfig();
        if (!s->cfg.classicEnabled) {
            ApplyAll(hWnd, *s, false);
            ShowErrors(hWnd, *s);
        }
        return 0;
    }
    if (msg == g_msgTeardown) {
        ReleaseDialog(hWnd, true);
        return 1;
    }
    if (msg == g_msgCapture) {
        if (!s->bgBrush) CaptureLogoBackground(hWnd, *s);
        return 0;
    }
    if (msg == g_msgShown) {
        OnDialogShown(hWnd, *s);
        return 0;
    }
    switch (msg) {
        case WM_CTLCOLORDLG:
            if (s->bgBrush) return (LRESULT)s->bgBrush;
            break;
        case WM_ERASEBKGND:
            if (s->bgBrush && s->cfg.ownBanner) {
                RECT rc;
                GetClientRect(hWnd, &rc);
                FillRect((HDC)wParam, &rc, s->bgBrush);
                return 1;
            }
            break;
        case WM_PAINT: {
            if (s->bgBrush && s->cfg.ownBanner) {  // our banner replaces the stock picture entirely
                PAINTSTRUCT ps;
                HDC hdc = BeginPaint(hWnd, &ps);
                FillRect(hdc, &ps.rcPaint, s->bgBrush);
                if (!s->cfg.logoEnabled) PaintOwnBanner(hWnd, *s, hdc);
                EndPaint(hWnd, &ps);
                return 0;
            }
            RECT painted;
            if (!s->bgBrush || !GetUpdateRect(hWnd, &painted, FALSE)) break;
            LRESULT r = DefSubclassProc(hWnd, msg, wParam, lParam);
            RecolorBanner(hWnd, *s, painted);
            return r;
        }
        case WM_CTLCOLORSTATIC:
        case WM_CTLCOLORBTN: {
            LRESULT def = DefSubclassProc(hWnd, msg, wParam, lParam);
            HDC hdc = (HDC)wParam;
            int idx = ControlIndexFromId(GetDlgCtrlID((HWND)lParam));
            if (idx >= 0 && s->hasCtlColor[idx]) SetTextColor(hdc, s->ctlColor[idx]);
            else if (s->cfg.hasTextColor) SetTextColor(hdc, s->cfg.textColor);
            if (!s->bgBrush) return def;
            SetBkMode(hdc, TRANSPARENT);
            SetBkColor(hdc, s->bgBrushColor);
            return (LRESULT)s->bgBrush;
        }
        case WM_TIMER:
            if (wParam == kTimerFade) {
                StepFade(hWnd, *s);
                return 0;
            }
            break;
        case WM_COMMAND:
            if ((LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL) && HIWORD(wParam) == 0 && !s->closeReady) {
                if (s->fade == DialogState::Fade::Out) return 0;
                DWORD ms = s->cfg.flyoutAnimation ? GetMotionDurationMs(false, s->cfg.animationSpeed) : 0;
                if (ms) {
                    s->closeW = wParam, s->closeL = lParam;
                    SetLayered(hWnd, *s, true, 255);
                    StartFade(hWnd, *s, DialogState::Fade::Out, ms);
                    return 0;
                }
            }
            break;
        case WM_NCDESTROY: {
            LRESULT r = DefSubclassProc(hWnd, msg, wParam, lParam);
            ReleaseDialog(hWnd, false);
            return r;
        }
    }
    return DefSubclassProc(hWnd, msg, wParam, lParam);
}

static bool IsWinverDialog(HWND hWnd) {
    if (!hWnd || GetWindow(hWnd, GW_OWNER) || (GetWindowLongW(hWnd, GWL_STYLE) & WS_CHILD)) return false;
    DWORD pid = 0;
    GetWindowThreadProcessId(hWnd, &pid);
    WCHAR cls[16];
    return pid == GetCurrentProcessId() && GetClassNameW(hWnd, cls, ARRAYSIZE(cls)) && !wcscmp(cls, L"#32770") &&
           GetDlgItem(hWnd, kWinverControls[2].id);  // ProductName: tells the About box from other dialogs
}

// One-shot hand-off that runs TakeDialog on the box's own thread (wParam: the box is new and not shown yet).
static LRESULT CALLBACK SetupSubclassProc(HWND h, UINT msg, WPARAM w, LPARAM l, DWORD_PTR) {
    if (msg == g_msgSetup) {
        WindhawkUtils::RemoveWindowSubclassFromAnyThread(h, SetupSubclassProc);
        TakeDialog(h, w != 0);
        return 0;
    }
    return DefSubclassProc(h, msg, w, l);
}

static bool OnDialogThread(HWND hWnd) { return GetWindowThreadProcessId(hWnd, nullptr) == GetCurrentThreadId(); }

static void TakeDialogOnItsThread(HWND hWnd, bool created) {
    if (OnDialogThread(hWnd)) {
        TakeDialog(hWnd, created);
    } else if (WindhawkUtils::SetWindowSubclassFromAnyThread(hWnd, SetupSubclassProc, 0)) {
        DWORD_PTR r;
        if (!SendMessageTimeoutW(hWnd, g_msgSetup, created, 0, SMTO_ABORTIFHUNG, 2000, &r))
            WindhawkUtils::RemoveWindowSubclassFromAnyThread(hWnd, SetupSubclassProc);
    }
}

// Out-of-context events arrive on the thread that set the hook, which is the box's thread in winver; the
// hand-offs cover the case where it is not.
static void CALLBACK WinEventProc(HWINEVENTHOOK, DWORD event, HWND hWnd, LONG idObject, LONG, DWORD, DWORD) {
    if (idObject != OBJID_WINDOW || !hWnd || !IsWindow(hWnd)) return;
    if (event == EVENT_OBJECT_CREATE) {
        if (!g_dlgWnd.load() && IsWinverDialog(hWnd)) TakeDialogOnItsThread(hWnd, true);
    } else if (event == EVENT_OBJECT_SHOW && hWnd == g_dlgWnd.load()) {
        if (g_winEventHook) {
            UnhookWinEvent(g_winEventHook);
            g_winEventHook = nullptr;
        }
        if (!OnDialogThread(hWnd)) PostMessageW(hWnd, g_msgShown, 0, 0);
        else if (g_dlg) OnDialogShown(hWnd, *g_dlg);
    }
}

// The message-only window lets uninit reach the thread that owns the WinEvent hook.
static LRESULT CALLBACK CtrlSubclassProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam, UINT_PTR, DWORD_PTR) {
    if (msg == g_msgTeardown) {
        if (g_winEventHook) {
            UnhookWinEvent(g_winEventHook);
            g_winEventHook = nullptr;
        }
        RemoveWindowSubclass(hWnd, CtrlSubclassProc, 0);
        DestroyWindow(hWnd);
        return 1;
    }
    return DefSubclassProc(hWnd, msg, wParam, lParam);
}

static BOOL CALLBACK FindOpenWinverDialog(HWND h, LPARAM found) {
    if (!IsWinverDialog(h) || !IsWindowVisible(h)) return TRUE;
    *(HWND*)found = h;
    return FALSE;
}

static void CustomWinver_Init() {
    g_msgSetup = RegisterWindowMessageW(L"SeamlessWinverConfigurator.Setup");
    g_msgReload = RegisterWindowMessageW(L"SeamlessWinverConfigurator.Reload");
    g_msgTeardown = RegisterWindowMessageW(L"SeamlessWinverConfigurator.Teardown");
    g_msgCapture = RegisterWindowMessageW(L"SeamlessWinverConfigurator.Capture");
    g_msgShown = RegisterWindowMessageW(L"SeamlessWinverConfigurator.Shown");

    // The mod was turned on while About Windows was already open: theme the box that is there.
    HWND existing = nullptr;
    EnumWindows(FindOpenWinverDialog, (LPARAM)&existing);
    if (existing) TakeDialogOnItsThread(existing, false);

    g_ctrlWnd = CreateWindowExW(0, L"STATIC", nullptr, 0, 0, 0, 0, 0, HWND_MESSAGE, nullptr, nullptr, nullptr);
    if (g_ctrlWnd) SetWindowSubclass(g_ctrlWnd, CtrlSubclassProc, 0, 0);
    g_winEventHook = SetWinEventHook(EVENT_OBJECT_CREATE, EVENT_OBJECT_SHOW, nullptr, WinEventProc,
                                     GetCurrentProcessId(), 0, WINEVENT_OUTOFCONTEXT);
    if (!g_winEventHook) Wh_Log(L"Couldn't watch for the About Windows box (%lu)", GetLastError());
}

static void CustomWinver_Reload() {
    if (HWND h = g_dlgWnd.load()) PostMessageW(h, g_msgReload, 0, 0);
}

static void CustomWinver_Uninit() {
    DWORD_PTR r = 0;
    if (!g_ctrlWnd || !IsWindow(g_ctrlWnd) ||
        !SendMessageTimeoutW(g_ctrlWnd, g_msgTeardown, 0, 0, SMTO_ABORTIFHUNG, 3000, &r)) {
        if (g_winEventHook) UnhookWinEvent(g_winEventHook);
        g_winEventHook = nullptr;
    }
    g_ctrlWnd = nullptr;
    if (HWND h = g_dlgWnd.load()) SendMessageTimeoutW(h, g_msgTeardown, 0, 0, SMTO_ABORTIFHUNG, 3000, &r);
    // Only shut GDI+ down once nothing of the box still holds a picture.
    if (!g_dlgWnd.load() && g_gdipToken) {
        Gdiplus::GdiplusShutdown(g_gdipToken);
        g_gdipToken = 0;
    }
}

}  // namespace swc

// ============================================================================
// 50-text-replace.cpp : Text swapping in Win32, GDI, menus, Direct2D, DirectWrite and GDI+
// Ported from Text Replace by m417z (GPL-3.0). Rules swap atomically, so a settings change never races a paint,
// and a string with nothing to swap goes straight through with no copy.
// ============================================================================

namespace swc {

using RuleSet = std::vector<TextReplaceRule>;
static SRWLOCK g_rulesLock = SRWLOCK_INIT;
static std::shared_ptr<const RuleSet> g_rules;
static std::atomic<bool> g_rulesActive{false};

static void TextReplace_SetRules(const std::vector<TextReplaceRule>& rules) {
    std::shared_ptr<const RuleSet> next;
    bool any = false;
    for (const auto& r : rules) any = any || !r.searchW.empty();
    if (any) next = std::make_shared<const RuleSet>(rules);
    AcquireSRWLockExclusive(&g_rulesLock);
    g_rules.swap(next);
    g_rulesActive.store(any, std::memory_order_release);
    ReleaseSRWLockExclusive(&g_rulesLock);
}

static std::shared_ptr<const RuleSet> CurrentRules() {
    if (!g_rulesActive.load(std::memory_order_acquire)) return {};
    AcquireSRWLockShared(&g_rulesLock);
    auto r = g_rules;
    ReleaseSRWLockShared(&g_rulesLock);
    return r;
}

template <typename C>
static const std::basic_string<C>& RuleFrom(const TextReplaceRule& r) {
    if constexpr (sizeof(C) == 1) return r.searchA;
    else return r.searchW;
}

template <typename C>
static const std::basic_string<C>& RuleTo(const TextReplaceRule& r) {
    if constexpr (sizeof(C) == 1) return r.replaceA;
    else return r.replaceW;
}

template <typename C>
static size_t TextLen(const C* s, long long n) {
    if (n >= 0) return (size_t)n;
    if constexpr (sizeof(C) == 1) return strlen(s);
    else return wcslen(s);
}

// Fills `out` and returns true only when some rule matched. `n` < 0 means the text ends at its null.
template <typename C>
static bool ReplaceText(const C* s, long long n, std::basic_string<C>& out) {
    if (!s) return false;
    auto rules = CurrentRules();
    if (!rules) return false;
    std::basic_string_view<C> view(s, TextLen(s, n));
    bool changed = false;
    for (const auto& rule : *rules) {
        const auto& from = RuleFrom<C>(rule);
        const auto& to = RuleTo<C>(rule);
        if (from.empty()) continue;
        size_t pos;
        if (!changed) {
            pos = view.find(from);
            if (pos == std::basic_string_view<C>::npos) continue;
            out.assign(view);
            changed = true;
        } else {
            pos = out.find(from);
        }
        while (pos != std::basic_string<C>::npos) {
            out.replace(pos, from.size(), to);
            pos = out.find(from, pos + to.size());
        }
    }
    return changed;
}

// ---- Window text and menus -------------------------------------------------

#define SWC_ORIG(name) static decltype(&name) name##_Orig

SWC_ORIG(SetWindowTextA);
SWC_ORIG(SetWindowTextW);
static BOOL WINAPI SetWindowTextA_Hook(HWND h, LPCSTR s) {
    std::string t;
    return SetWindowTextA_Orig(h, ReplaceText(s, -1, t) ? t.c_str() : s);
}
static BOOL WINAPI SetWindowTextW_Hook(HWND h, LPCWSTR s) {
    std::wstring t;
    return SetWindowTextW_Orig(h, ReplaceText(s, -1, t) ? t.c_str() : s);
}

static bool MenuFlagsHaveText(UINT flags) { return !(flags & (MF_BITMAP | MF_OWNERDRAW)); }

SWC_ORIG(InsertMenuA);
SWC_ORIG(InsertMenuW);
SWC_ORIG(AppendMenuA);
SWC_ORIG(AppendMenuW);
SWC_ORIG(ModifyMenuA);
SWC_ORIG(ModifyMenuW);
static BOOL WINAPI InsertMenuA_Hook(HMENU m, UINT pos, UINT f, UINT_PTR id, LPCSTR s) {
    std::string t;
    bool ch = MenuFlagsHaveText(f) && ReplaceText(s, -1, t);
    return InsertMenuA_Orig(m, pos, f, id, ch ? t.c_str() : s);
}
static BOOL WINAPI InsertMenuW_Hook(HMENU m, UINT pos, UINT f, UINT_PTR id, LPCWSTR s) {
    std::wstring t;
    bool ch = MenuFlagsHaveText(f) && ReplaceText(s, -1, t);
    return InsertMenuW_Orig(m, pos, f, id, ch ? t.c_str() : s);
}
static BOOL WINAPI AppendMenuA_Hook(HMENU m, UINT f, UINT_PTR id, LPCSTR s) {
    std::string t;
    bool ch = MenuFlagsHaveText(f) && ReplaceText(s, -1, t);
    return AppendMenuA_Orig(m, f, id, ch ? t.c_str() : s);
}
static BOOL WINAPI AppendMenuW_Hook(HMENU m, UINT f, UINT_PTR id, LPCWSTR s) {
    std::wstring t;
    bool ch = MenuFlagsHaveText(f) && ReplaceText(s, -1, t);
    return AppendMenuW_Orig(m, f, id, ch ? t.c_str() : s);
}
static BOOL WINAPI ModifyMenuA_Hook(HMENU m, UINT pos, UINT f, UINT_PTR id, LPCSTR s) {
    std::string t;
    bool ch = MenuFlagsHaveText(f) && ReplaceText(s, -1, t);
    return ModifyMenuA_Orig(m, pos, f, id, ch ? t.c_str() : s);
}
static BOOL WINAPI ModifyMenuW_Hook(HMENU m, UINT pos, UINT f, UINT_PTR id, LPCWSTR s) {
    std::wstring t;
    bool ch = MenuFlagsHaveText(f) && ReplaceText(s, -1, t);
    return ModifyMenuW_Orig(m, pos, f, id, ch ? t.c_str() : s);
}

template <typename MII>
static bool MenuItemHasText(const MII* mi) {
    return mi && mi->dwTypeData &&
           ((mi->fMask & MIIM_STRING) ||
            ((mi->fMask & MIIM_TYPE) && !(mi->fType & (MFT_BITMAP | MFT_SEPARATOR | MFT_OWNERDRAW))));
}

SWC_ORIG(InsertMenuItemA);
SWC_ORIG(InsertMenuItemW);
SWC_ORIG(SetMenuItemInfoA);
SWC_ORIG(SetMenuItemInfoW);
static BOOL WINAPI InsertMenuItemA_Hook(HMENU m, UINT item, BOOL byPos, LPCMENUITEMINFOA mi) {
    std::string t;
    if (MenuItemHasText(mi) && ReplaceText((LPCSTR)mi->dwTypeData, -1, t)) {
        MENUITEMINFOA c = *mi;
        c.dwTypeData = t.data();
        return InsertMenuItemA_Orig(m, item, byPos, &c);
    }
    return InsertMenuItemA_Orig(m, item, byPos, mi);
}
static BOOL WINAPI InsertMenuItemW_Hook(HMENU m, UINT item, BOOL byPos, LPCMENUITEMINFOW mi) {
    std::wstring t;
    if (MenuItemHasText(mi) && ReplaceText((LPCWSTR)mi->dwTypeData, -1, t)) {
        MENUITEMINFOW c = *mi;
        c.dwTypeData = t.data();
        return InsertMenuItemW_Orig(m, item, byPos, &c);
    }
    return InsertMenuItemW_Orig(m, item, byPos, mi);
}
static BOOL WINAPI SetMenuItemInfoA_Hook(HMENU m, UINT item, BOOL byPos, LPCMENUITEMINFOA mi) {
    std::string t;
    if (MenuItemHasText(mi) && ReplaceText((LPCSTR)mi->dwTypeData, -1, t)) {
        MENUITEMINFOA c = *mi;
        c.dwTypeData = t.data();
        return SetMenuItemInfoA_Orig(m, item, byPos, &c);
    }
    return SetMenuItemInfoA_Orig(m, item, byPos, mi);
}
static BOOL WINAPI SetMenuItemInfoW_Hook(HMENU m, UINT item, BOOL byPos, LPCMENUITEMINFOW mi) {
    std::wstring t;
    if (MenuItemHasText(mi) && ReplaceText((LPCWSTR)mi->dwTypeData, -1, t)) {
        MENUITEMINFOW c = *mi;
        c.dwTypeData = t.data();
        return SetMenuItemInfoW_Orig(m, item, byPos, &c);
    }
    return SetMenuItemInfoW_Orig(m, item, byPos, mi);
}

// ---- GDI text --------------------------------------------------------------

SWC_ORIG(TextOutA);
SWC_ORIG(TextOutW);
static BOOL WINAPI TextOutA_Hook(HDC dc, int x, int y, LPCSTR s, int c) {
    std::string t;
    if (c > 0 && ReplaceText(s, c, t)) return TextOutA_Orig(dc, x, y, t.c_str(), (int)t.size());
    return TextOutA_Orig(dc, x, y, s, c);
}
static BOOL WINAPI TextOutW_Hook(HDC dc, int x, int y, LPCWSTR s, int c) {
    std::wstring t;
    if (c > 0 && ReplaceText(s, c, t)) return TextOutW_Orig(dc, x, y, t.c_str(), (int)t.size());
    return TextOutW_Orig(dc, x, y, s, c);
}

SWC_ORIG(ExtTextOutA);
SWC_ORIG(ExtTextOutW);
static BOOL WINAPI ExtTextOutA_Hook(HDC dc, int x, int y, UINT o, const RECT* rc, LPCSTR s, UINT c, const INT* dx) {
    std::string t;
    if (!(o & ETO_GLYPH_INDEX) && c && ReplaceText(s, c, t))
        return ExtTextOutA_Orig(dc, x, y, o, rc, t.c_str(), (UINT)t.size(), t.size() == c ? dx : nullptr);
    return ExtTextOutA_Orig(dc, x, y, o, rc, s, c, dx);
}
static BOOL WINAPI ExtTextOutW_Hook(HDC dc, int x, int y, UINT o, const RECT* rc, LPCWSTR s, UINT c, const INT* dx) {
    std::wstring t;
    if (!(o & ETO_GLYPH_INDEX) && c && ReplaceText(s, c, t))
        return ExtTextOutW_Orig(dc, x, y, o, rc, t.c_str(), (UINT)t.size(), t.size() == c ? dx : nullptr);
    return ExtTextOutW_Orig(dc, x, y, o, rc, s, c, dx);
}

template <typename PT, typename C, typename Fn>
static BOOL PolyTextOutCommon(HDC dc, const PT* items, int count, Fn orig) {
    if (!items || count <= 0 || !g_rulesActive.load(std::memory_order_acquire)) return orig(dc, items, count);
    std::vector<PT> copy;
    std::vector<std::basic_string<C>> strs;
    for (int i = 0; i < count; i++) {
        std::basic_string<C> t;
        if ((items[i].uiFlags & ETO_GLYPH_INDEX) || !items[i].n || !ReplaceText(items[i].lpstr, items[i].n, t))
            continue;
        if (copy.empty()) {
            copy.assign(items, items + count);
            strs.resize(count);
        }
        strs[i] = std::move(t);
        if (strs[i].size() != items[i].n) copy[i].pdx = nullptr;
        copy[i].lpstr = strs[i].c_str();
        copy[i].n = (UINT)strs[i].size();
    }
    return orig(dc, copy.empty() ? items : copy.data(), count);
}

SWC_ORIG(PolyTextOutA);
SWC_ORIG(PolyTextOutW);
static BOOL WINAPI PolyTextOutA_Hook(HDC dc, const POLYTEXTA* p, int n) {
    return PolyTextOutCommon<POLYTEXTA, char>(dc, p, n, PolyTextOutA_Orig);
}
static BOOL WINAPI PolyTextOutW_Hook(HDC dc, const POLYTEXTW* p, int n) {
    return PolyTextOutCommon<POLYTEXTW, wchar_t>(dc, p, n, PolyTextOutW_Orig);
}

// DT_MODIFYSTRING may write up to four extra characters (an ellipsis and a null) into the buffer it is given.
template <typename C>
static C* PrepareDrawBuffer(std::basic_string<C>& t, UINT format, int& len) {
    len = (int)t.size();
    if (format & DT_MODIFYSTRING) t.resize(t.size() + 4);
    return t.data();
}

SWC_ORIG(DrawTextA);
SWC_ORIG(DrawTextW);
SWC_ORIG(DrawTextExA);
SWC_ORIG(DrawTextExW);
static int WINAPI DrawTextA_Hook(HDC dc, LPCSTR s, int c, LPRECT rc, UINT f) {
    std::string t;
    if (c != 0 && ReplaceText(s, c, t)) {
        int len;
        char* buf = PrepareDrawBuffer(t, f, len);
        return DrawTextA_Orig(dc, buf, len, rc, f);
    }
    return DrawTextA_Orig(dc, s, c, rc, f);
}
static int WINAPI DrawTextW_Hook(HDC dc, LPCWSTR s, int c, LPRECT rc, UINT f) {
    std::wstring t;
    if (c != 0 && ReplaceText(s, c, t)) {
        int len;
        wchar_t* buf = PrepareDrawBuffer(t, f, len);
        return DrawTextW_Orig(dc, buf, len, rc, f);
    }
    return DrawTextW_Orig(dc, s, c, rc, f);
}
static int WINAPI DrawTextExA_Hook(HDC dc, LPSTR s, int c, LPRECT rc, UINT f, LPDRAWTEXTPARAMS p) {
    std::string t;
    if (c != 0 && ReplaceText((LPCSTR)s, c, t)) {
        int len;
        char* buf = PrepareDrawBuffer(t, f, len);
        return DrawTextExA_Orig(dc, buf, len, rc, f, p);
    }
    return DrawTextExA_Orig(dc, s, c, rc, f, p);
}
static int WINAPI DrawTextExW_Hook(HDC dc, LPWSTR s, int c, LPRECT rc, UINT f, LPDRAWTEXTPARAMS p) {
    std::wstring t;
    if (c != 0 && ReplaceText((LPCWSTR)s, c, t)) {
        int len;
        wchar_t* buf = PrepareDrawBuffer(t, f, len);
        return DrawTextExW_Orig(dc, buf, len, rc, f, p);
    }
    return DrawTextExW_Orig(dc, s, c, rc, f, p);
}

// ---- Window creation and WM_SETTEXT ----------------------------------------

SWC_ORIG(CreateWindowExA);
SWC_ORIG(CreateWindowExW);
static HWND WINAPI CreateWindowExA_Hook(DWORD ex, LPCSTR cls, LPCSTR name, DWORD st, int x, int y, int w, int h,
                                        HWND parent, HMENU menu, HINSTANCE inst, LPVOID param) {
    std::string t;
    // A window name can be a resource ordinal (0xFFFF prefix) for static image controls; leave those alone.
    bool ch = name && (BYTE)name[0] != 0xFF && ReplaceText(name, -1, t);
    return CreateWindowExA_Orig(ex, cls, ch ? t.c_str() : name, st, x, y, w, h, parent, menu, inst, param);
}
static HWND WINAPI CreateWindowExW_Hook(DWORD ex, LPCWSTR cls, LPCWSTR name, DWORD st, int x, int y, int w, int h,
                                        HWND parent, HMENU menu, HINSTANCE inst, LPVOID param) {
    std::wstring t;
    bool ch = name && name[0] != 0xFFFF && ReplaceText(name, -1, t);
    return CreateWindowExW_Orig(ex, cls, ch ? t.c_str() : name, st, x, y, w, h, parent, menu, inst, param);
}

SWC_ORIG(SendMessageA);
SWC_ORIG(SendMessageW);
static LRESULT WINAPI SendMessageA_Hook(HWND h, UINT msg, WPARAM wp, LPARAM lp) {
    std::string t;
    if (msg == WM_SETTEXT && lp && ReplaceText((LPCSTR)lp, -1, t)) return SendMessageA_Orig(h, msg, wp, (LPARAM)t.c_str());
    return SendMessageA_Orig(h, msg, wp, lp);
}
static LRESULT WINAPI SendMessageW_Hook(HWND h, UINT msg, WPARAM wp, LPARAM lp) {
    std::wstring t;
    if (msg == WM_SETTEXT && lp && ReplaceText((LPCWSTR)lp, -1, t)) return SendMessageW_Orig(h, msg, wp, (LPARAM)t.c_str());
    return SendMessageW_Orig(h, msg, wp, lp);
}

#undef SWC_ORIG

// ---- Direct2D, DirectWrite and GDI+ ----------------------------------------

using D2DDrawText_t = void(STDMETHODCALLTYPE*)(ID2D1RenderTarget*, const WCHAR*, UINT32, IDWriteTextFormat*,
                                               const D2D1_RECT_F*, ID2D1Brush*, D2D1_DRAW_TEXT_OPTIONS,
                                               DWRITE_MEASURING_MODE);
static D2DDrawText_t D2DDrawText_Orig;
static void STDMETHODCALLTYPE D2DDrawText_Hook(ID2D1RenderTarget* rt, const WCHAR* s, UINT32 n, IDWriteTextFormat* fmt,
                                               const D2D1_RECT_F* rc, ID2D1Brush* br, D2D1_DRAW_TEXT_OPTIONS o,
                                               DWRITE_MEASURING_MODE mm) {
    std::wstring t;
    if (n && ReplaceText(s, n, t)) return D2DDrawText_Orig(rt, t.c_str(), (UINT32)t.size(), fmt, rc, br, o, mm);
    D2DDrawText_Orig(rt, s, n, fmt, rc, br, o, mm);
}

using DWCreateTextLayout_t = HRESULT(STDMETHODCALLTYPE*)(IDWriteFactory*, const WCHAR*, UINT32, IDWriteTextFormat*,
                                                         FLOAT, FLOAT, IDWriteTextLayout**);
static DWCreateTextLayout_t DWCreateTextLayout_Orig;
static HRESULT STDMETHODCALLTYPE DWCreateTextLayout_Hook(IDWriteFactory* f, const WCHAR* s, UINT32 n,
                                                         IDWriteTextFormat* fmt, FLOAT w, FLOAT h,
                                                         IDWriteTextLayout** out) {
    std::wstring t;
    if (n && ReplaceText(s, n, t)) return DWCreateTextLayout_Orig(f, t.c_str(), (UINT32)t.size(), fmt, w, h, out);
    return DWCreateTextLayout_Orig(f, s, n, fmt, w, h, out);
}

using DWCreateGdiLayout_t = HRESULT(STDMETHODCALLTYPE*)(IDWriteFactory*, const WCHAR*, UINT32, IDWriteTextFormat*,
                                                        FLOAT, FLOAT, FLOAT, const DWRITE_MATRIX*, BOOL,
                                                        IDWriteTextLayout**);
static DWCreateGdiLayout_t DWCreateGdiLayout_Orig;
static HRESULT STDMETHODCALLTYPE DWCreateGdiLayout_Hook(IDWriteFactory* f, const WCHAR* s, UINT32 n,
                                                        IDWriteTextFormat* fmt, FLOAT w, FLOAT h, FLOAT dip,
                                                        const DWRITE_MATRIX* m, BOOL natural,
                                                        IDWriteTextLayout** out) {
    std::wstring t;
    if (n && ReplaceText(s, n, t))
        return DWCreateGdiLayout_Orig(f, t.c_str(), (UINT32)t.size(), fmt, w, h, dip, m, natural, out);
    return DWCreateGdiLayout_Orig(f, s, n, fmt, w, h, dip, m, natural, out);
}

using GdipDrawString_t = int(WINAPI*)(void*, const WCHAR*, INT, const void*, const void*, const void*, const void*);
static GdipDrawString_t GdipDrawString_Orig;
static int WINAPI GdipDrawString_Hook(void* g, const WCHAR* s, INT n, const void* font, const void* rc,
                                      const void* fmt, const void* br) {
    std::wstring t;
    if (n != 0 && ReplaceText(s, n, t)) return GdipDrawString_Orig(g, t.c_str(), (INT)t.size(), font, rc, fmt, br);
    return GdipDrawString_Orig(g, s, n, font, rc, fmt, br);
}

// Making a DC render target calls into win32k through DXGI, which fails fast in sandboxed processes
// (Chromium renderers and similar). DirectWrite doesn't need win32k, so it stays on there.
static bool Win32kCallsBlocked() {
    PROCESS_MITIGATION_SYSTEM_CALL_DISABLE_POLICY p{};
    return GetProcessMitigationPolicy(GetCurrentProcess(), ProcessSystemCallDisablePolicy, &p, sizeof(p)) &&
           p.DisallowWin32kSystemCalls;
}

static void HookD2DTextDraw() {
    if (Win32kCallsBlocked()) return;
    HMODULE d2d = LoadLibraryExW(L"d2d1.dll", nullptr, LOAD_LIBRARY_SEARCH_SYSTEM32);
    using Create_t = HRESULT(WINAPI*)(D2D1_FACTORY_TYPE, REFIID, const D2D1_FACTORY_OPTIONS*, void**);
    auto create = d2d ? (Create_t)GetProcAddress(d2d, "D2D1CreateFactory") : nullptr;
    ID2D1Factory* factory = nullptr;
    if (!create || FAILED(create(D2D1_FACTORY_TYPE_SINGLE_THREADED, __uuidof(ID2D1Factory), nullptr, (void**)&factory)))
        return;
    D2D1_RENDER_TARGET_PROPERTIES props{};
    props.pixelFormat.format = DXGI_FORMAT_B8G8R8A8_UNORM;
    props.pixelFormat.alphaMode = D2D1_ALPHA_MODE_PREMULTIPLIED;
    ID2D1DCRenderTarget* rt = nullptr;
    if (SUCCEEDED(factory->CreateDCRenderTarget(&props, &rt))) {
        void** vt = *(void***)rt;
        Wh_SetFunctionHook(vt[27], (void*)D2DDrawText_Hook, (void**)&D2DDrawText_Orig);
        rt->Release();
    }
    factory->Release();
}

static void HookDWriteLayouts() {
    HMODULE dw = LoadLibraryExW(L"dwrite.dll", nullptr, LOAD_LIBRARY_SEARCH_SYSTEM32);
    using Create_t = HRESULT(WINAPI*)(DWRITE_FACTORY_TYPE, REFIID, IUnknown**);
    auto create = dw ? (Create_t)GetProcAddress(dw, "DWriteCreateFactory") : nullptr;
    IDWriteFactory* factory = nullptr;
    if (!create || FAILED(create(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory), (IUnknown**)&factory))) return;
    void** vt = *(void***)factory;
    Wh_SetFunctionHook(vt[18], (void*)DWCreateTextLayout_Hook, (void**)&DWCreateTextLayout_Orig);
    Wh_SetFunctionHook(vt[19], (void*)DWCreateGdiLayout_Hook, (void**)&DWCreateGdiLayout_Orig);
    factory->Release();
}

static void HookGdiplusText() {
    HMODULE gp = LoadLibraryExW(L"gdiplus.dll", nullptr, LOAD_LIBRARY_SEARCH_SYSTEM32);
    void* fn = gp ? (void*)GetProcAddress(gp, "GdipDrawString") : nullptr;
    if (fn) Wh_SetFunctionHook(fn, (void*)GdipDrawString_Hook, (void**)&GdipDrawString_Orig);
}

static bool TextReplace_InstallHooks() {
    HMODULE user32 = GetModuleHandleW(L"user32.dll");
    HMODULE gdi32 = LoadLibraryExW(L"gdi32.dll", nullptr, LOAD_LIBRARY_SEARCH_SYSTEM32);
    if (!user32 || !gdi32) return false;

    struct HookDef { HMODULE mod; const char* name; void* hook; void** orig; };
#define SWC_HOOK(m, n) {m, #n, (void*)n##_Hook, (void**)&n##_Orig}
    const HookDef defs[] = {
        SWC_HOOK(user32, SetWindowTextA),   SWC_HOOK(user32, SetWindowTextW),
        SWC_HOOK(user32, InsertMenuA),      SWC_HOOK(user32, InsertMenuW),
        SWC_HOOK(user32, AppendMenuA),      SWC_HOOK(user32, AppendMenuW),
        SWC_HOOK(user32, ModifyMenuA),      SWC_HOOK(user32, ModifyMenuW),
        SWC_HOOK(user32, InsertMenuItemA),  SWC_HOOK(user32, InsertMenuItemW),
        SWC_HOOK(user32, SetMenuItemInfoA), SWC_HOOK(user32, SetMenuItemInfoW),
        SWC_HOOK(user32, DrawTextA),        SWC_HOOK(user32, DrawTextW),
        SWC_HOOK(user32, DrawTextExA),      SWC_HOOK(user32, DrawTextExW),
        SWC_HOOK(user32, CreateWindowExA),  SWC_HOOK(user32, CreateWindowExW),
        SWC_HOOK(user32, SendMessageA),     SWC_HOOK(user32, SendMessageW),
        SWC_HOOK(gdi32, TextOutA),          SWC_HOOK(gdi32, TextOutW),
        SWC_HOOK(gdi32, ExtTextOutA),       SWC_HOOK(gdi32, ExtTextOutW),
        SWC_HOOK(gdi32, PolyTextOutA),      SWC_HOOK(gdi32, PolyTextOutW),
    };
#undef SWC_HOOK
    int ok = 0;
    for (const auto& d : defs) {
        void* target = (void*)GetProcAddress(d.mod, d.name);
        if (target && Wh_SetFunctionHook(target, d.hook, d.orig)) ok++;
        else Wh_Log(L"Couldn't hook %S", d.name);
    }
    HookD2DTextDraw();
    HookDWriteLayouts();
    HookGdiplusText();
    return ok > 0;
}

static void TextReplace_Uninit() {
    TextReplace_SetRules({});
}

}  // namespace swc

std::wstring Hotkey_Format(UINT mods, UINT vk) {
    std::wstring key;
    if ((vk >= 'A' && vk <= 'Z') || (vk >= '0' && vk <= '9')) key = std::wstring(1, (wchar_t)vk);
    else if (vk >= VK_F1 && vk <= VK_F24) key = L"F" + std::to_wstring(vk - VK_F1 + 1);
    if (key.empty()) return {};
    std::wstring out;
    if (mods & MOD_CONTROL) out += L"Ctrl+";
    if (mods & MOD_ALT) out += L"Alt+";
    if (mods & MOD_SHIFT) out += L"Shift+";
    if (mods & MOD_WIN) out += L"Win+";
    return out + key;
}

// ===========================================================================
// Settings window: the Seamless Launchpad settings GUI, the standard for every
// DavidHiFi mod. Generated by work\2026-11-26-seamless-winver-configurator\gen.py.
// ===========================================================================
extern "C" IMAGE_DOS_HEADER __ImageBase;
namespace swcset {
// The settings window, from the tray icon. It shows the same settings as
// Windhawk's page for this mod and saves them through windhawk-cli, so the two
// stay in step. Writing a mod's settings takes admin rights, so the save runs
// the CLI elevated (silently where UAC prompts are off).

constexpr WCHAR kSettingsClass[] = L"WindhawkSeamlessWinverConfiguratorSettings";
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
// Generated by work\2026-11-26-seamless-winver-configurator\gen.py from the settings block.
static std::vector<SetField> Set_MakeFields() {
    using K = SetField;
    return {
{K::Choice, L"themePreset", L"Theme preset", L"Choose how About Windows looks right away. Pick Custom colors to use the color boxes below.", L"mochaDark", {{L"mochaDark", L"Catppuccin Mocha dark glass"}, {L"mochaSolid", L"Catppuccin Mocha solid, no glass"}, {L"stock", L"Stock Windows"}, {L"custom", L"Custom colors"}}, 0, 100, 0, L"Theme"},
{K::Color, L"windowColors.title", L"Title text color", L"Hex (#CDD6F4) or RGB (205, 214, 244). Leave blank for default.", L"#CDD6F4", {}, 0, 100, 0, L"Custom colors"},
{K::Color, L"windowColors.bar", L"Title bar color", L"Hex (#181825) or RGB (24, 24, 37). Leave blank for default.", L"#181825", {}, 0, 100, 0, L"Custom colors"},
{K::Color, L"windowColors.border", L"Border color", L"Hex (#89B4FA) or RGB (137, 180, 250). Leave blank for default.", L"#89B4FA", {}, 0, 100, 0, L"Custom colors"},
{K::Color, L"windowColors.background", L"Background color", L"Hex (#1E1E2E) or RGB (30, 30, 46). The Windows banner is redrawn on it too.", L"#1E1E2E", {}, 0, 100, 0, L"Custom colors"},
{K::Color, L"windowColors.textColor", L"Default text color", L"Hex (#CDD6F4) or RGB (205, 214, 244).", L"#CDD6F4", {}, 0, 100, 0, L"Custom colors"},
{K::Color, L"windowColors.separator", L"Separator color", L"Hex (#45475A) or RGB (69, 71, 90). Leave blank for default.", L"#45475A", {}, 0, 100, 0, L"Custom colors"},
{K::Check, L"ownBanner", L"Mocha banner", L"Draws our own banner: the Windows logo and name in the blue to mauve gradient, in place of the stock picture.", L"1", {}, 0, 100, 0, L"Banner and font"},
{K::Text, L"bannerText", L"Banner name", L"Leave blank to show your Windows name (Windows 11 or Windows 10).", L"", {}, 0, 100, 0, L"Banner and font"},
{K::Text, L"textFont", L"Text font", L"The font for every line in About Windows. Leave blank to keep the Windows font.", L"FiraCode Nerd Font", {}, 0, 100, 0, L"Banner and font"},
{K::Check, L"flyoutAnimation", L"Open and close animation", L"About Windows fades in with a short slide when it opens and fades out when it closes. Off snaps it. Stays still when Windows animations are off.", L"1", {}, 0, 100, 0, L"Motion"},
{K::Choice, L"animationSpeed", L"Animation speed", L"How fast the open animation runs. Global follows your shared Seamless motion speed.", L"global", {{L"global", L"Follow the global speed"}, {L"veryQuick", L"Very quick"}, {L"quick", L"Quick"}, {L"normal", L"Normal"}, {L"relaxed", L"Relaxed"}, {L"slow", L"Slow"}}, 0, 100, 0, L"Motion"},
{K::Check, L"launchOnSave", L"Open About Windows after saving", L"Opens About Windows when you save, if it is not open already, so you see the change right away.", L"0", {}, 0, 100, 0, L"Motion"},
{K::Check, L"logo.enabled", L"Custom logo", L"Show a custom PNG, JPG, BMP, ICO, or animated GIF in the logo area.", L"0", {}, 0, 100, 1, L"Custom logo"},
{K::Text, L"logo.path", L"Logo image path", L"Full path to a PNG, JPG, BMP, ICO, TIFF, or animated GIF file.", L"", {}, 0, 100, 1, L"Custom logo"},
{K::Check, L"logo.center", L"Center logo", L"Horizontally center the logo inside About Windows.", L"1", {}, 0, 100, 1, L"Custom logo"},
{K::Number, L"logo.x", L"Logo X", L"-500 to 1000 (Suggested: 0). Horizontal position or offset when centered.", L"0", {}, -500, 1000, 1, L"Custom logo"},
{K::Number, L"logo.y", L"Logo Y", L"-500 to 1000 (Suggested: 10). Vertical position in pixels.", L"10", {}, -500, 1000, 1, L"Custom logo"},
{K::Number, L"logo.width", L"Logo width", L"0 to 1000 (Suggested: 0). Set to 0 to scale automatically from height or original width.", L"0", {}, 0, 1000, 1, L"Custom logo"},
{K::Number, L"logo.height", L"Logo height", L"-1 to 500 (Suggested: -1). -1 fits the standard 72 px banner height; 0 uses original height.", L"-1", {}, -1, 500, 1, L"Custom logo"},
{K::Check, L"startPosition.enabled", L"Custom open position", L"Position About Windows automatically when it opens.", L"1", {}, 0, 100, 2, L"Window open position"},
{K::Check, L"startPosition.center", L"Center on screen", L"Center the dialog on the chosen monitor. X and Y act as offsets when on.", L"1", {}, 0, 100, 2, L"Window open position"},
{K::Number, L"startPosition.monitor", L"Monitor", L"0 to 8 (Suggested: 0). 0 uses the monitor where the window appeared; 1 to 8 picks a specific screen.", L"0", {}, 0, 8, 2, L"Window open position"},
{K::Number, L"startPosition.x", L"Position X", L"-3000 to 3000 (Suggested: 0). Horizontal position or offset from center.", L"0", {}, -3000, 3000, 2, L"Window open position"},
{K::Number, L"startPosition.y", L"Position Y", L"-3000 to 3000 (Suggested: 0). Vertical position or offset from center.", L"0", {}, -3000, 3000, 2, L"Window open position"},
{K::Check, L"windowSize.enabled", L"Custom window size", L"Resize About Windows when it opens.", L"0", {}, 0, 100, 2, L"Window size"},
{K::Number, L"windowSize.width", L"Width", L"0 to 2000 (Suggested: 0). Set to 0 to keep the default width.", L"0", {}, 0, 2000, 2, L"Window size"},
{K::Number, L"windowSize.height", L"Height", L"0 to 2000 (Suggested: 0). Set to 0 to keep the default height.", L"0", {}, 0, 2000, 2, L"Window size"},
{K::Check, L"windowSize.expandControls", L"Expand controls to fit", L"Widen text labels when the window is wider.", L"1", {}, 0, 100, 2, L"Window size"},
{K::Check, L"windowSize.exceptionalOkButton", L"Realign OK button vertically", L"Move the OK button down when the window height increases.", L"1", {}, 0, 100, 2, L"Window size"},
{K::Check, L"alwaysOnTop", L"Always on top", L"Keep About Windows above other windows.", L"0", {}, 0, 100, 2, L"Behavior"},
{K::Check, L"removeFirstFocus", L"Remove initial focus", L"Clear focus from the OK button when the dialog opens.", L"0", {}, 0, 100, 2, L"Behavior"},
{K::Text, L"customIcon", L"Custom window icon", L"Either DLL and index (shell32.dll;23) or a full path to an .ico file. Leave blank for default.", L"", {}, 0, 100, 2, L"Title bar"},
{K::Check, L"removeTitleIcon", L"Hide title bar icon", L"Remove the small icon from the top-left of the title bar.", L"0", {}, 0, 100, 2, L"Title bar"},
{K::Check, L"restoreCloseButton", L"Keep close button", L"Keep the close button visible when hiding the title bar icon.", L"1", {}, 0, 100, 2, L"Title bar"},
{K::Text, L"titleText", L"Custom window title", L"Overrides the title bar text directly. Leave blank to keep default or ShellAbout title.", L"", {}, 0, 100, 2, L"Title bar"},
{K::Check, L"shellText.enabled", L"Override ShellAbout text", L"Replace the title, first line, and middle text sent to ShellAbout.", L"0", {}, 0, 100, 3, L"ShellAbout text overrides"},
{K::Text, L"shellText.title", L"ShellAbout title", L"Shown in the title bar. You may also enter Title#FirstLine here. Leave empty for the default.", L"About Windows", {}, 0, 100, 3, L"ShellAbout text overrides"},
{K::Text, L"shellText.firstLine", L"First line", L"Shown on the first line below the logo. Leave empty for the default, or type a space to hide it.", L"Microsoft Windows", {}, 0, 100, 3, L"ShellAbout text overrides"},
{K::Text, L"shellText.otherStuff", L"Middle text (Other stuff)", L"Extra text displayed in the middle of the dialog, such as an evaluation notice.", L"", {}, 0, 100, 3, L"ShellAbout text overrides"},
{K::Text, L"quickControls.productName", L"Product name label", L"Replaces the Product Name text. Supports {default.ProductName} placeholders. Leave blank to keep.", L"", {}, 0, 100, 3, L"Quick control overrides"},
{K::Text, L"quickControls.version", L"Version label", L"Replaces the Version line. Supports {default.Version} placeholders. Leave blank to keep.", L"", {}, 0, 100, 3, L"Quick control overrides"},
{K::Text, L"quickControls.copyright", L"Copyright label", L"Replaces the Copyright line, e.g. {default.Copyright::0/1} Custom {default.Copyright::12}.", L"", {}, 0, 100, 3, L"Quick control overrides"},
{K::Text, L"quickControls.legalNotice", L"Legal notice label", L"Replaces the legal notice paragraph. Leave blank to keep.", L"", {}, 0, 100, 3, L"Quick control overrides"},
{K::Text, L"quickControls.licenseInfo", L"License link text", L"Replaces the license line. Use <A>link</A> tags to keep the clickable link.", L"", {}, 0, 100, 3, L"Quick control overrides"},
{K::Text, L"quickControls.registeredUser1", L"Registered user line 1", L"Replaces the registered owner name. Leave blank to keep.", L"", {}, 0, 100, 3, L"Quick control overrides"},
{K::Text, L"quickControls.registeredUser2", L"Registered user line 2", L"Replaces the registered organization name. Leave blank to keep.", L"", {}, 0, 100, 3, L"Quick control overrides"},
{K::Text, L"quickControls.okButton", L"OK button text", L"Replaces the OK button label. Leave blank to keep.", L"", {}, 0, 100, 3, L"Quick control overrides"},
{K::Check, L"classic.enabled", L"Enable Classic Winver", L"Replace the modern About dialog with one loaded from a classic Windows shell32.dll.", L"0", {}, 0, 100, 4, L"Classic Winver"},
{K::Check, L"classic.allApps", L"Classic dialog in other apps", L"When Include other apps is on, also replace ShellAbout in Notepad, Explorer, and other programs.", L"0", {}, 0, 100, 4, L"Classic Winver"},
{K::Text, L"classic.shell_dll_path", L"Path to shell32.dll", L"Full path to shell32.dll from the Windows version to restore. Leave blank to use System32.", L"", {}, 0, 100, 4, L"Classic Winver"},
{K::Text, L"classic.xpsp1res_dll_path", L"Path to xpsp1res.dll", L"Only for Windows XP SP1+ layout. Leave blank otherwise.", L"", {}, 0, 100, 4, L"Classic Winver"},
{K::Text, L"classic.msgina_dll_path", L"Path to msgina.dll", L"Required for Windows Server 2003 / XP x64 branding bitmaps.", L"", {}, 0, 100, 4, L"Classic Winver"},
{K::Choice, L"classic.branding", L"XP / Server 2003 branding", L"Which branding bitmap to use on XP and Server 2003 dialogs.", L"professional", {{L"professional", L"Professional"}, {L"home", L"Home"}, {L"embedded", L"Embedded"}, {L"server", L"Server Standard Edition"}, {L"srv_enterprise", L"Server Enterprise Edition"}, {L"srv_datacenter", L"Server Datacenter Edition"}, {L"sbs", L"Small Business Server"}, {L"srv_web", L"Server Web Edition"}}, 0, 100, 4, L"Classic Winver"},
{K::Text, L"classic.top_line_text", L"Top line text (Vista+)", L"Overrides the top line on Vista and newer classic dialogs. Leave blank for default.", L"", {}, 0, 100, 4, L"Classic Winver"},
{K::Text, L"classic.version_text", L"Version text (9x / Me)", L"Version string displayed on Windows 9x and Me classic dialogs. Leave empty for the default.", L"Windows 95", {}, 0, 100, 4, L"Classic Winver"},
{K::Text, L"classic.copyright_years", L"Copyright years (XP / 2003)", L"Copyright year range shown on Windows XP and Server 2003 dialogs. Leave empty for the default, or type a space to hide it.", L"1981-2001", {}, 0, 100, 4, L"Classic Winver"},
{K::Text, L"classic.display_version", L"Display version (Win 10)", L"Display version such as 22H2. Leave blank for the actual Windows value.", L"", {}, 0, 100, 4, L"Classic Winver"},
{K::Number, L"classic.major_version", L"Major version", L"-1 to 99 (Suggested: -1). -1 uses the actual OS value.", L"-1", {}, -1, 99, 4, L"Classic Winver"},
{K::Number, L"classic.minor_version", L"Minor version", L"-1 to 99 (Suggested: -1). -1 uses the actual OS value.", L"-1", {}, -1, 99, 4, L"Classic Winver"},
{K::Number, L"classic.build_number", L"Build number", L"-1 to 999999 (Suggested: -1). -1 uses the actual OS value.", L"-1", {}, -1, 999999, 4, L"Classic Winver"},
{K::Number, L"classic.ubr", L"Sub-build number (UBR)", L"-1 to 999999 (Suggested: -1). -1 uses the actual value (Windows 10 style).", L"-1", {}, -1, 999999, 4, L"Classic Winver"},
{K::Text, L"classic.build_lab", L"Build lab", L"Custom build lab string, e.g. xpclient.010817-1148. Leave blank for actual value.", L"", {}, 0, 100, 4, L"Classic Winver"},
{K::Check, L"classic.use_build_lab_ex", L"Use BuildLabEx", L"Use BuildLabEx instead of BuildLab and show it on any classic dialog style.", L"0", {}, 0, 100, 4, L"Classic Winver"},
{K::Text, L"classic.csd_version", L"CSD version (Service Pack)", L"Service pack string. Use USE_DEFAULT for the actual value.", L"USE_DEFAULT", {}, 0, 100, 4, L"Classic Winver"},
{K::Text, L"classic.debug_string", L"Debug string", L"Debug string suffix. Use USE_DEFAULT for the actual value.", L"USE_DEFAULT", {}, 0, 100, 4, L"Classic Winver"},
{K::Number, L"classic.physical_memory", L"Physical memory (KB)", L"-1 to 2000000000 (Suggested: -1). -1 reads actual RAM (Vista and earlier).", L"-1", {}, -1, 2000000000, 4, L"Classic Winver"},
{K::Number, L"classic.system_resources_free", L"System resources free (%)", L"-1 to 100 (Suggested: -1). -1 reads actual free memory percent (9x / Me).", L"-1", {}, -1, 100, 4, L"Classic Winver"},
{K::Check, L"classic.show_confidential_text", L"Show Microsoft Confidential text", L"Show red confidential text on beta Windows 7/8 shell32.dll builds.", L"0", {}, 0, 100, 4, L"Classic Winver"},
{K::Check, L"redirector.enabled", L"Redirect Winver to another app", L"When on, running winver.exe launches the command below instead of About Windows.", L"0", {}, 0, 100, 5, L"Winver redirector"},
{K::Text, L"redirector.command", L"Replacement command or target", L"Executable path with optional arguments, shell:AppsFolder target, shortcut, or URI like ms-settings:about.", L"", {}, 0, 100, 5, L"Winver redirector"},
{K::Check, L"includeOtherApps", L"Include other apps", L"Off keeps the classic box and text swapping inside About Windows. On lets them work in other apps too, once you add each app under this mod's Advanced tab in Windhawk.", L"0", {}, 0, 100, 5, L"Other apps"},
{K::Check, L"textReplace.enabled", L"Enable text replacement", L"Replace matching text strings rendered in Winver (and other apps when Include other apps is on).", L"0", {}, 0, 100, 5, L"Text replace"},
{K::Text, L"textReplace.find1", L"Quick find 1 (Winver)", L"Text to find inside About Windows.", L"", {}, 0, 100, 5, L"Text replace"},
{K::Text, L"textReplace.replace1", L"Quick replace 1 (Winver)", L"Replacement text for Quick find 1.", L"", {}, 0, 100, 5, L"Text replace"},
{K::Text, L"textReplace.find2", L"Quick find 2 (Winver)", L"Second text to find inside About Windows.", L"", {}, 0, 100, 5, L"Text replace"},
{K::Text, L"textReplace.replace2", L"Quick replace 2 (Winver)", L"Replacement text for Quick find 2.", L"", {}, 0, 100, 5, L"Text replace"},
{K::Text, L"textReplace.find3", L"Quick find 3 (Winver)", L"Third text to find inside About Windows.", L"", {}, 0, 100, 5, L"Text replace"},
{K::Text, L"textReplace.replace3", L"Quick replace 3 (Winver)", L"Replacement text for Quick find 3.", L"", {}, 0, 100, 5, L"Text replace"},
{K::Check, L"settingsGlass", L"Blurred settings window", L"On, the settings window is see-through glass with Windows acrylic behind it. Off, it is solid. Applies when you save.", L"1", {}, 0, 100, 6, L"Settings window"},
{K::Check, L"nativeSettingsTitleBar", L"Native Windows title bar", L"Use the Windows title bar and window buttons for this settings window. Applies when you save.", L"0", {}, 0, 100, 6, L"Settings window"},
{K::Check, L"settingsTrayIcon", L"Tray icon", L"An icon in the tray. Click it to open these settings. Right-click it to open About Windows or these settings.", L"1", {}, 0, 100, 6, L"Settings window"}
    };
}

struct SetPageInfo {
    PCWSTR name, intro;
    WCHAR glyph;
};
static const SetPageInfo kSetPages[] = {
{L"Theme", L"How About Windows looks: a ready theme or your own colors, and how it opens.", 0xE790},
{L"Logo", L"Put your own picture or animated GIF where the Windows banner sits.", 0xEB9F},
{L"Window", L"Where About Windows opens, its size, its icon and its title.", 0xE7C4},
{L"Text", L"Change the words About Windows shows, line by line.", 0xE8D2},
{L"Classic", L"Bring back the About dialog from an older Windows.", 0xE81C},
{L"Redirect and replace", L"Open something else instead, or swap any text that shows up.", 0xE8AB},
{L"Look", L"Choose how this settings window looks and whether its tray icon is shown.", 0xE771},
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
constexpr PCWSTR kSetCreditFcw = L"https://windhawk.net/mods/fully-customizable-winver";
constexpr PCWSTR kSetCreditClassic = L"https://windhawk.net/mods/classic-winver";
constexpr PCWSTR kSetCreditCustomizer = L"https://windhawk.net/mods/winver-text-customizer";
constexpr PCWSTR kSetCreditCustomText = L"https://windhawk.net/mods/winver-custom-text";
constexpr PCWSTR kSetCreditRedirect = L"https://windhawk.net/mods/replace-winver-with-exe";
constexpr PCWSTR kSetCreditReplace = L"https://windhawk.net/mods/text-replace";
constexpr PCWSTR kSetRepoUrl = L"https://github.com/DavidHiFi/seamless-workshop";
constexpr PCWSTR kSetBugUrl =
    L"https://github.com/DavidHiFi/seamless-workshop/issues/new?title=%5BSeamless%20Winver%20Configurator%5D%20";
constexpr PCWSTR kSetTitle = L"Seamless Winver Configurator";
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
        if (w.fRailName && Set_TextW(w.fRailName.get(), L"Winver") <= railW) break;
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

// A colour row needs 362 DIP for its hex box and chips; when that leaves the label under 200 DIP,
// the chips drop to a line of their own under the text.
constexpr float kSgcColorFullW = 362, kSgcLabelMinW = 200, kSgcChipLine = 30;
static bool ColorRowStacked(const SetField& f, float rowW) {
    return f.kind == SetField::Color && rowW - 2 * kSetRowPad - kSgcColorFullW - 24 < kSgcLabelMinW;
}
static float RowControlW(const SetField& f, float rowW) { return ColorRowStacked(f, rowW) ? 96 : Set_ControlW(f); }

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
        float textW = w.contentW - 2 * kSetRowPad - RowControlW(f, w.contentW) - 24;
        float lh = Set_TextH(w.fLabel.get(), f.label, textW);
        float dh = (f.desc && *f.desc) ? Set_TextH(w.fHint.get(), f.desc, textW) + 3 : 0;
        it.y = y;
        it.h = std::max(kSetRowMin, 28 + lh + dh) + (ColorRowStacked(f, w.contentW) ? kSgcChipLine : 0);
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
        add(SetItem::Link, 56, L"Based on Fully Customizable WinVer", L"By ItsTauTvyDas: themes, logos and every label", kSetCreditFcw);
        add(SetItem::Link, 56, L"And Classic Winver", L"By aubymori: the About dialogs of older Windows", kSetCreditClassic);
        add(SetItem::Link, 56, L"And Winver Text Customizer", L"By aubymori: the title and the lines below it", kSetCreditCustomizer);
        add(SetItem::Link, 56, L"And Winver Custom Text", L"By Thomas Shrader: your own About text", kSetCreditCustomText);
        add(SetItem::Link, 56, L"And Winver Redirector", L"By winui64: open another app instead", kSetCreditRedirect);
        add(SetItem::Link, 56, L"And Text Replace", L"By m417z: swap any text that shows up", kSetCreditReplace);
        group(L"Project");
        add(SetItem::Link, 56, L"Project page on GitHub", L"github.com/DavidHiFi/seamless-workshop", kSetRepoUrl);
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
    {  // The glyph alone in the gradient, no plate (owner, 2026-11-24).
        D2D1_MATRIX_3X2_F old;
        p.rt->GetTransform(&old);
        const D2D1_POINT_2F mc{(mark.left + mark.right) / 2, (mark.top + mark.bottom) / 2};
        p.rt->SetTransform(D2D1::Matrix3x2F::Scale(1.75f, 1.75f, mc) * old);
        const WCHAR glyph = 0xE946;
        auto br = p.G({mc.x - 19, mc.y - 19, mc.x + 19, mc.y + 19});
        if (br) p.rt->DrawText(&glyph, 1, w.fIconL.get(), mark, br.get());
        p.rt->SetTransform(old);
    }
    float x = mark.right + 20;
    p.Text(w.fBig.get(), L"Seamless Winver Configurator", {x, row.top + 18, row.right - 16, row.top + 46}, mocha::text);
#ifdef WH_MOD_VERSION
    std::wstring ver = std::wstring(L"Version ") + WH_MOD_VERSION + L"  \u00B7  GPL-3.0 or later  \u00B7  A Windhawk mod";
#else
    std::wstring ver = L"GPL-3.0 or later  \u00B7  A Windhawk mod";
#endif
    p.Text(w.fHint.get(), ver, {x, row.top + 48, row.right - 16, row.top + 68}, mocha::subtext0);
    p.Text(w.fHint.get(), L"Six About Windows mods in one: themes, logos, classic dialogs, text and redirects.",
           {x, row.top + 72, row.right - 16, row.top + 110}, mocha::subtext1);
    p.Text(w.fHint.get(), L"Made by DavidHiFi from the six mods credited below.",
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
    p.Text(w.fRailName.get(), L"Winver", {d.left + 90, d.top + 32, d.left + w.railW - 10, d.top + 56}, mocha::text, textA);
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
    const WCHAR mark = 0xE946;
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
    HWND hwnd = CreateWindowExW(0, kSettingsClass, L"Seamless Winver Configurator settings", style,
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
 if (g_settingsStop && g_settingsWnd) PostMessageW(g_settingsWnd,WM_CLOSE,0,0);  // closed while opening
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
// The tray icon's right-click menu. Returns 1 for About Windows, 2 for Settings, 0 for nothing.
int ShowTrayMenu(HWND owner, POINT pt) {
    std::vector<SetMenuItem> rows;
    rows.push_back(Set_MenuRow(1, L"\uE946", L"Open About Windows"));
    rows.push_back(Set_MenuSep());
    rows.push_back(Set_MenuRow(2, L"\uEB51", L"Settings"));
    return Set_TrayMenu(owner, rows, &pt);
}
}  // namespace swcset

// ---- Tray icon (tool process only) -------------------------------------------------------------------------------
// Click opens the settings window; right-click shows Open About Windows and Settings. The icon is the shared blue to
// mauve gradient glyph, drawn alone.

constexpr UINT TrayIconId() {
    UINT hash = 2166136261u;
    for (PCWSTR p = WH_MOD_ID; *p; p++) hash = (hash ^ (UINT)*p) * 16777619u;
    return hash | 0x80000000u;
}
constexpr UINT kTrayId = TrayIconId();
static constexpr UINT WM_APP_TRAY = WM_APP + 20, WM_APP_TRAY_REFRESH = WM_APP + 21;
static HANDLE g_trayThread;
static std::atomic<HWND> g_trayWnd;
static UINT g_taskbarCreated;
static bool g_trayShown;
static HICON g_trayIcon;

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
    HFONT font = CreateFontW(-(int)(size * 0.84f), 0, 0, 0, FW_NORMAL, 0, 0, 0, DEFAULT_CHARSET, 0, 0,
                             ANTIALIASED_QUALITY, 0, L"Segoe Fluent Icons");
    HGDIOBJ oldFont = SelectObject(dc, font);
    SetBkMode(dc, TRANSPARENT);
    SetTextColor(dc, RGB(255, 255, 255));
    RECT r{0, 0, size, size};
    WCHAR g[2] = {(WCHAR)0xE946, 0};
    DrawTextW(dc, g, 1, &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE | DT_NOPREFIX);
    GdiFlush();
    SelectObject(dc, oldFont);
    DeleteObject(font);
    SelectObject(dc, old);
    DeleteDC(dc);

    const float c0[3] = {0x89 / 255.f, 0xB4 / 255.f, 0xFA / 255.f};
    const float c1[3] = {0xCB / 255.f, 0xA6 / 255.f, 0xF7 / 255.f};
    uint32_t* px = (uint32_t*)bits;
    const uint32_t* gp = (const uint32_t*)glyphBits;
    for (int y = 0; y < size; y++)
        for (int x = 0; x < size; x++) {
            float t = std::clamp((x + y) / (2.0f * (size - 1)), 0.0f, 1.0f);
            float cov = ((gp[y * size + x] >> 8) & 0xFF) / 255.0f;
            float rgb[3];
            for (int i = 0; i < 3; i++) rgb[i] = (c0[i] + (c1[i] - c0[i]) * t) * cov;
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

static void UpdateTray(HWND hwnd, bool recreate) {
    NOTIFYICONDATAW nid{};
    nid.cbSize = sizeof(nid);
    nid.hWnd = hwnd;
    nid.uID = kTrayId;
    if (!Wh_GetIntSetting(L"settingsTrayIcon")) {
        if (g_trayShown) Shell_NotifyIconW(NIM_DELETE, &nid);
        g_trayShown = false;
        return;
    }
    HICON icon = g_trayIcon && !recreate ? g_trayIcon : MakeTrayIcon();
    nid.uFlags = NIF_ICON | NIF_TIP | NIF_MESSAGE | NIF_SHOWTIP;
    nid.uCallbackMessage = WM_APP_TRAY;
    nid.hIcon = icon;
    wcscpy_s(nid.szTip, L"Seamless Winver Configurator");
    if (recreate) g_trayShown = false;
    if (!g_trayShown) {
        Shell_NotifyIconW(NIM_DELETE, &nid);
        if (Shell_NotifyIconW(NIM_ADD, &nid)) {
            nid.uVersion = NOTIFYICON_VERSION_4;
            Shell_NotifyIconW(NIM_SETVERSION, &nid);
            g_trayShown = true;
        }
    } else {
        Shell_NotifyIconW(NIM_MODIFY, &nid);
    }
    if (g_trayIcon && g_trayIcon != icon) DestroyIcon(g_trayIcon);
    g_trayIcon = icon;
}

// Runs winver.exe from System32, the way the Start menu would.
static void LaunchWinver() {
    WCHAR path[MAX_PATH];
    UINT n = GetSystemDirectoryW(path, MAX_PATH);
    if (!n || n > MAX_PATH - 12) return;
    wcscat_s(path, L"\\winver.exe");
    SHELLEXECUTEINFOW sei{sizeof(sei)};
    sei.fMask = SEE_MASK_FLAG_NO_UI | SEE_MASK_NOASYNC;
    sei.lpFile = path;
    sei.nShow = SW_SHOWNORMAL;
    if (!ShellExecuteExW(&sei)) Wh_Log(L"Couldn't start winver.exe (%lu)", GetLastError());
}

static LRESULT CALLBACK TrayProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) {
    if (g_taskbarCreated && msg == g_taskbarCreated) {
        UpdateTray(hwnd, true);
        return 0;
    }
    switch (msg) {
        case WM_APP_TRAY:
            switch (LOWORD(lp)) {
                case NIN_SELECT:
                case NIN_KEYSELECT:
                    swcset::OpenSettingsWindow();
                    break;
                case WM_CONTEXTMENU: {
                    POINT pt{GET_X_LPARAM(wp), GET_Y_LPARAM(wp)};
                    SetForegroundWindow(hwnd);
                    int cmd = swcset::ShowTrayMenu(hwnd, pt);
                    if (cmd == 1) LaunchWinver();
                    else if (cmd == 2) swcset::OpenSettingsWindow();
                    break;
                }
            }
            return 0;
        case WM_APP_TRAY_REFRESH:
            UpdateTray(hwnd, false);
            return 0;
        case WM_CLOSE:
            DestroyWindow(hwnd);
            return 0;
        case WM_DESTROY: {
            NOTIFYICONDATAW nid{};
            nid.cbSize = sizeof(nid);
            nid.hWnd = hwnd;
            nid.uID = kTrayId;
            if (g_trayShown) Shell_NotifyIconW(NIM_DELETE, &nid);
            g_trayShown = false;
            PostQuitMessage(0);
            return 0;
        }
    }
    return DefWindowProcW(hwnd, msg, wp, lp);
}

static DWORD WINAPI TrayThread(void*) {
    SetThreadDpiAwarenessContext(DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2);
    HINSTANCE inst = (HINSTANCE)&__ImageBase;
    WNDCLASSW wc{};
    wc.lpfnWndProc = TrayProc;
    wc.hInstance = inst;
    wc.lpszClassName = L"SeamlessWinverConfiguratorTray";
    RegisterClassW(&wc);
    // A hidden top-level window, not a message-only one: only top-level windows hear TaskbarCreated.
    HWND hwnd = CreateWindowExW(WS_EX_TOOLWINDOW, wc.lpszClassName, L"Seamless Winver Configurator", WS_POPUP, 0, 0,
                                0, 0, nullptr, nullptr, inst, nullptr);
    if (!hwnd) {
        UnregisterClassW(wc.lpszClassName, inst);
        return 0;
    }
    g_taskbarCreated = RegisterWindowMessageW(L"TaskbarCreated");
    ChangeWindowMessageFilterEx(hwnd, g_taskbarCreated, MSGFLT_ALLOW, nullptr);
    g_trayWnd = hwnd;
    UpdateTray(hwnd, true);
    MSG m;
    while (GetMessageW(&m, nullptr, 0, 0) > 0) {
        TranslateMessage(&m);
        DispatchMessageW(&m);
    }
    g_trayWnd = nullptr;
    if (IsWindow(hwnd)) DestroyWindow(hwnd);
    if (g_trayIcon) DestroyIcon(g_trayIcon);
    g_trayIcon = nullptr;
    UnregisterClassW(wc.lpszClassName, inst);
    return 0;
}

static void StopTrayThread() {
    if (!g_trayThread) return;
    if (HWND hwnd = g_trayWnd) PostMessageW(hwnd, WM_CLOSE, 0, 0);
    if (WaitForSingleObject(g_trayThread, 5000) == WAIT_TIMEOUT) Wh_Log(L"The tray thread did not stop");
    CloseHandle(g_trayThread);
    g_trayThread = nullptr;
}

// ---- Lifecycle ---------------------------------------------------------------------------------------------------
// Three kinds of process load this mod:
//  * windhawk.exe -windhawk-tool-mod <id>: the tool process. It owns the settings window and the tray icon.
//  * plain windhawk.exe: only starts the tool process (the launcher), then stays idle.
//  * winver.exe, and any app the user added in Windhawk's Advanced tab: the hooks. winver gets every hook at start so a
//    change applies live. Other apps get only the hooks their settings need, and reload when that need changes.

#include <tlhelp32.h>
#include <windhawk_tool_mod.h>

namespace swc {

using ShellAboutW_t = INT(WINAPI*)(HWND, LPCWSTR, LPCWSTR, HICON);
static ShellAboutW_t ShellAboutW_Orig;

static INT WINAPI ShellAboutW_Hook(HWND hWnd, LPCWSTR szApp, LPCWSTR szOtherStuff, HICON hIcon) {
    ModConfig cfg = SnapshotConfig();
    if (TryRedirectWinver(hWnd, cfg)) return TRUE;
    std::wstring outApp, outOther;
    LPCWSTR effApp = szApp, effOther = szOtherStuff;
    ApplyShellAboutTextOverrides(cfg, szApp, szOtherStuff, outApp, outOther, effApp, effOther);
    if (cfg.classicEnabled && (g_isWinverProcess || (cfg.includeOtherApps && cfg.classicAllApps)))
        return ShowClassicWinverDialog(hWnd, effApp, effOther, hIcon, cfg);
    return ShellAboutW_Orig(hWnd, effApp, effOther, hIcon);
}

// What an app other than winver needs from the current settings. Bit 1: the classic dialog. Bit 2: text rules.
static int OtherAppNeeds(const ModConfig& c) {
    if (!c.includeOtherApps) return 0;
    return (c.classicEnabled && c.classicAllApps ? 1 : 0) | (!c.textRules.empty() ? 2 : 0);
}

static int g_hookedNeeds;
static bool g_textHooks;

static bool HookShellAbout() {
    HMODULE shell32 = LoadLibraryExW(L"shell32.dll", nullptr, LOAD_LIBRARY_SEARCH_SYSTEM32);
    void* target = shell32 ? (void*)GetProcAddress(shell32, "ShellAboutW") : nullptr;
    if (!target || !Wh_SetFunctionHook(target, (void*)ShellAboutW_Hook, (void**)&ShellAboutW_Orig)) {
        Wh_Log(L"Couldn't hook ShellAboutW");
        return false;
    }
    return true;
}

// Runs from Wh_ModInit in winver and in the apps the user added. Hooks set here are applied when init returns.
static BOOL HookProcessInit() {
    LoadAllSettings();
    ModConfig cfg = SnapshotConfig();
    if (g_isWinverProcess) {
        HookShellAbout();
        TextReplace_SetRules(cfg.textRules);
        g_textHooks = TextReplace_InstallHooks();
        CustomWinver_Init();
        return TRUE;
    }
    // Stays loaded with nothing hooked when nothing is needed, so turning a feature on later only needs a reload.
    g_hookedNeeds = OtherAppNeeds(cfg);
    if (g_hookedNeeds & 1) HookShellAbout();
    if (g_hookedNeeds & 2) {
        TextReplace_SetRules(cfg.textRules);
        g_textHooks = TextReplace_InstallHooks();
    }
    return TRUE;
}

static void HookProcessSettingsChanged(BOOL* bReload) {
    LoadAllSettings();
    ModConfig cfg = SnapshotConfig();
    if (!g_isWinverProcess && OtherAppNeeds(cfg) != g_hookedNeeds) {
        *bReload = TRUE;
        return;
    }
    if (g_textHooks) TextReplace_SetRules(cfg.textRules);
    if (g_isWinverProcess) CustomWinver_Reload();
}

static void HookProcessUninit() {
    if (g_isWinverProcess) CustomWinver_Uninit();
    if (g_textHooks) TextReplace_Uninit();
}

}  // namespace swc

// ---- Tool process callbacks --------------------------------------------------------------------------------------

BOOL WhTool_ModInit() {
    swc::g_isWindhawkHost = true;
    swc::LoadAllSettings();
    g_trayThread = CreateThread(nullptr, 0, TrayThread, nullptr, 0, nullptr);
    return TRUE;
}

static bool IsWinverRunning() {
    HANDLE snap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (snap == INVALID_HANDLE_VALUE) return false;
    PROCESSENTRY32W pe{sizeof(pe)};
    bool found = false;
    for (BOOL ok = Process32FirstW(snap, &pe); ok && !found; ok = Process32NextW(snap, &pe))
        found = _wcsicmp(pe.szExeFile, L"winver.exe") == 0;
    CloseHandle(snap);
    return found;
}

void WhTool_ModSettingsChanged() {
    swc::LoadAllSettings();
    if (HWND hwnd = swcset::g_settingsWnd) PostMessageW(hwnd, swcset::WM_APP_SETTINGS_RELOAD, 0, 0);
    if (HWND hwnd = g_trayWnd) PostMessageW(hwnd, WM_APP_TRAY_REFRESH, 0, 0);
    // An open About Windows picks the change up by itself; only start one when none is open.
    if (swc::SnapshotConfig().launchOnSave && !IsWinverRunning()) LaunchWinver();
}

void WhTool_ModUninit() {
    StopTrayThread();  // first, so a tray click cannot open a new settings window mid-unload
    swcset::CloseSettingsWindow();
}

// ---- Launcher and hook callbacks -----------------------------------------------------------------------------------
// Windhawk's windhawk_tool_mod.h runs the tool process. In every other process the mod is a "launcher": in plain
// windhawk.exe it only starts the tool process, and in winver and the added apps it sets the hooks instead.

static bool g_isHookProcess;

BOOL WhToolLauncher_ModInit(BOOL* bLaunch) {
    WCHAR path[MAX_PATH];
    DWORD n = GetModuleFileNameW(nullptr, path, ARRAYSIZE(path));
    if (!n || n == ARRAYSIZE(path)) return FALSE;
    PCWSTR name = PathFindFileNameW(path);
    if (_wcsicmp(name, L"windhawk.exe") == 0) {
        *bLaunch = TRUE;
        return TRUE;
    }
    *bLaunch = FALSE;
    g_isHookProcess = true;
    swc::g_isWinverProcess = _wcsicmp(name, L"winver.exe") == 0;
    return swc::HookProcessInit();
}

void WhToolLauncher_ModSettingsChanged(BOOL* bReload) {
    if (!g_isHookProcess) return;  // windhawk.exe reloads, which restarts the tool process if it stopped
    *bReload = FALSE;
    swc::HookProcessSettingsChanged(bReload);
}

// Windhawk finishes unloading only once ShellAboutW returns, which is when the box closes. So the box goes back to
// the stock look here, before that wait, and turning the mod off shows at once.
void WhToolLauncher_ModBeforeUninit() {
    if (g_isHookProcess) swc::HookProcessUninit();
}

void WhToolLauncher_ModUninit() {
    if (g_isHookProcess) swc::HookProcessUninit();
}
