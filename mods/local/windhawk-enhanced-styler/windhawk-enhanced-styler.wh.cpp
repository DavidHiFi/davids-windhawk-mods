// ==WindhawkMod==
// @id              windhawk-enhanced-styler
// @name            Windhawk Enhanced Styler
// @description     Theme Windhawk itself with your own colors, gradients, font, transparency and blur
// @version         2.2.15
// @author          DavidHiFi, Ingan121
// @github          https://github.com/DavidHiFi
// @homepage        https://github.com/DavidHiFi/davids-windhawk-mods
// @donateUrl       https://ko-fi.com/DavidHiFi
// @license         MIT
// @include         windhawk-ui.exe
// @include         windhawk.exe
// @architecture    x86-64
// @compilerOptions -DWIN32_LEAN_AND_MEAN -luser32 -lgdi32 -ldwmapi -lws2_32 -ladvapi32 -lcomctl32 -luxtheme -liphlpapi -lshell32 -lole32 -luuid -lcrypt32
// ==/WindhawkMod==

// ==WindhawkModReadme==
/*
# Windhawk Enhanced Styler

Choose Windhawk's colors, gradients, font, transparency and background blur.

![Windhawk Enhanced Styler preview](https://raw.githubusercontent.com/DavidHiFi/davids-windhawk-mods/main/media/previews/windhawk-enhanced-styler.png)

## What's new in 2.2.15

- The mod tasks window keeps its column names in view, sizes its columns to the text so mod names and status read in full, and no longer shows the resize dots.

## What's new in 2.2.14

- The "Mod tasks in progress" and "Loaded mods" windows now match the main window all the way: dark glass body, the list on a rounded card with the grey edge, FiraCode text, quiet column headings, and an "Open Windhawk" pill button that gets the blue to mauve edge on hover. The bright row bands, the boxy list border and the resize dots are gone.

## What's new in 2.2.13

- The "Mod tasks in progress" window now gets the centred title and uptime like the main window. It was missed because its title ends in "- Windhawk".

## What's new in 2.2.12

- Drop-down menus in Windhawk get the frosted glass, the scrollbar stays inside their rounded corners, and the top buttons rest on the Mocha base colour.

## What's new in 2.2.11

- The window buttons on the Windhawk title bar dim when the window is in the background and light up when you click back into it, like every other window. The glass behind them stays.
- Turning on Mocha Windhawk icons now also changes the shared Start menu and desktop shortcuts, not only the taskbar one.

## What's new in 2.2.10

- New switch, Mocha Windhawk icons: the Windhawk window, its tray icon and its shortcuts on the taskbar, Start menu and desktop use the blue and mauve icon. Turning it off puts the stock icons back.
- The mod tasks window at the bottom right and the Loaded mods window get rounded corners, the dark glass, and the centred title dock with its uptime.

## What's new in 2.2.6

- A long mod description on a mod's page wraps onto more lines instead of being cut off at the edge.

## What's new in 2.2.5

- The Windhawk window's title gets the same rounded dock as every other title bar when Seamless Title Bars is on: its fill, edge, glass shine, blue to mauve hover edge, title font and right-click menu, read from that mod's settings so the two always match.
- The same uptime Seamless Title Bars adds after every other window's title is added after this one's: how long the Windhawk window has been open, in that mod's units, style, separator and colour. It hides when that mod or its uptime is off.

## What's new in 2.2.4

- The collapse chevron on a setting row sits inside the row again and no longer covers the colored state bar beside it.
- Drop-down lists open instant and solid: no flicker while opening and nothing on the page reads through the popup sheet.
- The floating save dock keeps a 12px gap from the window edges in the normal and the expanded settings view.

## Features

- **Background.** Pick a color and opacity, with Acrylic or no background effect.
- **Cards and dialogs.** Set their color and opacity. Cards, tables, Advanced settings, dialogs and pop-up menus use that surface; pop-ups that float over the page take a solid card surface so text under them stays hidden. Every box has one outline, the same color all the way around its corners.
- **Controls.** Choose colors for buttons and inputs, plus a global accent for selections, hovers, badges, spinners, links and modified settings. Number spinners sit in a rounded pill. The save bar floats while the settings scroll, and mode and version switches join into single pills.
- **Header gradient.** The Windhawk logo, its name and section titles such as Installed mods take a two-color gradient, blue to mauve by default. An optional Enhanced badge sits beside the name.
- **Selected text.** Highlighted text uses the accent color, or a color of its own, instead of the stock blue.
- **Corners.** Round cards, tables, dialogs, pop-up menus, buttons and inputs with an adjustable radius, or keep Windhawk's squared look.
- **Tray pop-ups.** The Mod tasks in progress and Loaded mods windows from the taskbar icon use the same colors as the rest of the theme.
- **Text and font.** Use an installed font and a text color. Icons keep their own font and stay centered in their buttons.
- **Title bar.** Match the background or choose a solid color. Right-click the title bar, click the app icon or press Alt+Space for the Windows window menu. The app icon keeps its normal size, and Windows handles dragging and window buttons.
- **Removal.** Disable the mod to reopen the interface with Windhawk's appearance. The mod changes no application files.

## How to use

This edition requires Windows 11 and the 64-bit Windhawk 2.0 Tauri interface. It was tested with Windhawk 2.0.0-alpha.7.

Open the mod's Settings tab, choose your appearance and save. Saving settings or switching this mod on or off briefly closes and reopens the Windhawk interface.

Colors use `#RRGGBB`. Opacity runs from 0 for transparent to 100 for solid. Leave an optional color or font blank to use Windhawk's choice. The title bar keeps the Windows caption font.

## Notes

Windows transparency and animation settings can affect the background material. Other mods that style this window can conflict with its appearance.

For the older Windhawk interface, use the [legacy 1.4.0 edition](legacy/). It has a separate source and settings.

## Credits

This mod was called Windhawk Styler before 2.1.0.

The original window frame work was adapted from [Titlebar For Everyone](https://windhawk.net/mods/titlebar-for-everyone) by Ingan121, under the MIT license.
*/
// ==/WindhawkModReadme==

// ==WindhawkModSettings==
/*
- backgroundColor: "#1e1e2e"
  $name: Background color
  $description: "Use a color in #RRGGBB format for the background"
- backgroundOpacity: 60
  $name: Background opacity
  $description: "0 is transparent, 100 is a solid color. Text and controls stay clear"
- blur: acrylic
  $name: Background effect
  $description: "Choose the effect behind the background color"
  $options:
  - acrylic: Acrylic
  - none: None
- cardColor: "#181825"
  $name: Card and dialog color
  $description: "Mod cards, pages, dialogs and pop-up menus. Leave blank for Windhawk's colors"
- cardOpacity: 100
  $name: Card and dialog opacity
  $description: "0 is transparent, 100 is solid. Pop-ups that float over the page stay solid so text under them stays hidden"
- roundedCorners: true
  $name: Rounded element corners
  $description: "Round the corners of cards, tables, buttons, inputs and dialogs. Turn off for the stock squared look"
- cornerRadius: 8
  $name: Corner radius
  $description: "Corner roundness in pixels, used when Rounded element corners is on"
- controlColor: "#313244"
  $name: Button and input color
  $description: "Buttons, text boxes and drop-down controls. Leave blank for Windhawk's colors"
- accentColor: "#89b4fa"
  $name: Accent color
  $description: "Selected buttons, switches, tabs and links. Leave blank for Windhawk's colors"
- selectionColor: ""
  $name: Selected text color
  $description: "Highlight behind selected text, in #RRGGBB format. Leave blank to use the accent color"
- selectionOpacity: 40
  $name: Selected text opacity
  $description: "0 to 100 (Suggested: 40). Higher values make the highlight stronger"
- headerGradient: true
  $name: Gradient titles and icons
  $description: "Paint the Windhawk logo, its name and section titles such as Installed mods with the gradient below. When off, they keep Windhawk's colors"
- gradientStart: "#89b4fa"
  $name: Gradient start color
  $description: "Left side of the gradient, in #RRGGBB format (Suggested: #89b4fa, Mocha blue)"
- gradientEnd: "#cba6f7"
  $name: Gradient end color
  $description: "Right side of the gradient, in #RRGGBB format (Suggested: #cba6f7, Mocha mauve)"
- mochaIcons: false
  $name: Mocha Windhawk icons
  $description: "Use the blue and mauve icon for the Windhawk window, tray and shortcuts"
- enhancedBadge: true
  $name: Enhanced badge
  $description: "Show a small gradient badge beside the Windhawk name in the top left"
- badgeText: "Enhanced"
  $name: Badge text
  $description: "Words shown in the badge, up to 24 characters (Suggested: Enhanced)"
- textColor: "#cdd6f4"
  $name: Text color
  $description: "Body and title bar text. Leave blank for Windhawk's colors"
- fontFamily: "FiraCode Nerd Font"
  $name: Font
  $description: "Use an installed font for the interface. Leave blank for Windhawk's font. The title bar keeps the Windows font"
- fontWeight: 500
  $name: Font weight
  $description: "Weight of normal text: 300 Light, 400 Regular, 500 Medium, 600 Semibold, 700 Bold (Suggested: 500). Bold labels stay bolder. The font must include that weight"
- nativeTitleBar: true
  $name: Style the title bar
  $description: "Apply the theme to the title bar and keep the normal Windows buttons"
- titleBarAcrylic: true
  $name: Match the title bar to the background
  $description: "Use the same color and transparency as the background. Turn off for a solid title bar"
- centerTitle: false
  $name: Center the title
  $description: "Put the icon and window name in the middle of the title bar, like Caption Buttons Customizer does for other windows"
- titleBarColor: "#403a45"
  $name: Solid title bar color
  $description: "Used when Match the title bar to the background is off. Enter a color in #RRGGBB format"
*/
// ==/WindhawkModSettings==

#include <winsock2.h>
#include <shlobj.h>
#include <shellapi.h>
#include <commctrl.h>
#include <wincrypt.h>
#include <atomic>
#include <optional>
#include <ws2tcpip.h>
#include <windhawk_utils.h>
#include <windows.h>
#include <dwmapi.h>
#include <uxtheme.h>
#include <vssym32.h>
#include <iphlpapi.h>
#include <tlhelp32.h>
#include <string>
#include <set>
#include <map>
#include <vector>
#include <algorithm>
#include <cmath>
#include <mutex>
#include <cstdio>
#include <cstdint>
#include <cstdlib>
#include <cwchar>

// The local debugging port for reaching the interface's own WebView; not a
// user setting, so it stays out of the interface's settings page entirely.
static constexpr int kCdpPort = 9333;

// SetWindowCompositionAttribute (undocumented, stable since Windows 8/10)
struct ACCENT_POLICY {
    int AccentState;
    int AccentFlags;
    std::uint32_t GradientColor;
    int AnimationId;
};
struct WINCOMPATTRDATA {
    int Attribute;
    void* Data;
    SIZE_T Size;
};
static constexpr int WCA_ACCENT_POLICY = 19;
static constexpr int WCA_FORCE_ACTIVEWINDOW_APPEARANCE = 15;
static constexpr int ACCENT_ENABLE_TRANSPARENTGRADIENT = 2;
static constexpr int ACCENT_ENABLE_BLURBEHIND = 3;
static constexpr int ACCENT_ENABLE_ACRYLICBLURBEHIND = 4;
extern "C" WINUSERAPI BOOL WINAPI SetWindowCompositionAttribute(HWND, WINCOMPATTRDATA*);

struct Settings {
    std::uint32_t background = 0x1e1e2e;  // RRGGBB
    int backgroundOpacity = 60;           // 0..100
    int blur = 2;                         // 0 none, 1 blur, 2 acrylic
    std::string card;                     // "rgb(r,g,b)" or empty
    int cardOpacity = 100;
    bool roundedCorners = true;
    int cornerRadius = 8;                 // px, 0..32
    std::string control;
    std::string accent;
    std::uint32_t accentRgb = 0;
    std::string text;
    std::uint32_t textRgb = 0;            // RRGGBB; s.text records whether a color is set
    std::wstring font;
    int fontWeight = 400;
    bool nativeTitleBar = true;
    std::uint32_t titleBarRgb = 0x403a45;  // RRGGBB
    bool titleBarColorSet = true;
    bool titleBarAcrylic = true;
    bool centerTitle = false;
    std::uint32_t selectionRgb = 0x89b4fa;
    bool selectionColorSet = false;
    int selectionOpacity = 40;
    bool headerGradient = true;
    std::uint32_t gradientStart = 0x89b4fa;
    std::uint32_t gradientEnd = 0xcba6f7;
    bool mochaIcons = false;
    bool enhancedBadge = true;
    std::string badgeText = "Enhanced";
};

static Settings g_settings;
static std::mutex g_settingsMutex;
static HANDLE g_stopEvent;
static HANDLE g_workerThread;
static volatile long g_themeActive = 1;
static volatile long g_relaunchRequested = 0;
static volatile long g_relaunchDone = 0;        // at most one self-relaunch per process
static volatile long long g_seenChangeTime = -1;  // engine save marker, last seen
static unsigned long long g_startTick;
static volatile bool g_pageReady;
static volatile long g_frameReady = 0;  // the visible main window has its frame
static int g_cdpPort = kCdpPort;         // the port actually handed to the webview
static HANDLE g_cdpThread;

static void DebugNote(const char* what, long detail = 0) {
    Wh_Log(L"%S (%ld)", what, detail);
}

static bool HexColorToRgb(const std::wstring& hex, std::uint32_t* rgb) {
    if (hex.size() == 7 && hex[0] == L'#') {
        std::uint32_t value = 0;
        for (int i = 1; i <= 6; i++) {
            wchar_t c = hex[i];
            std::uint32_t d;
            if (c >= L'0' && c <= L'9') d = c - L'0';
            else if (c >= L'a' && c <= L'f') d = c - L'a' + 10;
            else if (c >= L'A' && c <= L'F') d = c - L'A' + 10;
            else return false;
            value = value * 16 + d;
        }
        *rgb = value;
        return true;
    }
    return false;
}

static std::string RgbToCss(std::uint32_t rgb) {
    char buf[32];
    snprintf(buf, sizeof(buf), "rgb(%u,%u,%u)", (rgb >> 16) & 0xff, (rgb >> 8) & 0xff, rgb & 0xff);
    return buf;
}

static void ReadSettings(Settings* s) {
    PCWSTR background = Wh_GetStringSetting(L"backgroundColor");
    if (!HexColorToRgb(background, &s->background)) s->background = 0x1e1e2e;
    Wh_FreeStringSetting(background);

    s->backgroundOpacity = Wh_GetIntSetting(L"backgroundOpacity");
    if (s->backgroundOpacity < 0) s->backgroundOpacity = 0;
    if (s->backgroundOpacity > 100) s->backgroundOpacity = 100;

    PCWSTR blur = Wh_GetStringSetting(L"blur");
    if (wcscmp(blur, L"none") == 0) s->blur = 0;
    else s->blur = 2;  // acrylic, the default
    Wh_FreeStringSetting(blur);

    s->card.clear();
    std::uint32_t cardRgb;
    PCWSTR card = Wh_GetStringSetting(L"cardColor");
    if (HexColorToRgb(card, &cardRgb)) s->card = RgbToCss(cardRgb);
    Wh_FreeStringSetting(card);

    s->cardOpacity = Wh_GetIntSetting(L"cardOpacity");
    if (s->cardOpacity < 0) s->cardOpacity = 0;
    if (s->cardOpacity > 100) s->cardOpacity = 100;

    s->roundedCorners = Wh_GetIntSetting(L"roundedCorners") != 0;
    s->cornerRadius = Wh_GetIntSetting(L"cornerRadius");
    if (s->cornerRadius < 0) s->cornerRadius = 0;
    if (s->cornerRadius > 32) s->cornerRadius = 32;

    s->control.clear();
    std::uint32_t controlRgb;
    PCWSTR control = Wh_GetStringSetting(L"controlColor");
    if (HexColorToRgb(control, &controlRgb)) s->control = RgbToCss(controlRgb);
    Wh_FreeStringSetting(control);

    s->accent.clear();
    s->accentRgb = 0;
    std::uint32_t accentRgb;
    PCWSTR accent = Wh_GetStringSetting(L"accentColor");
    if (HexColorToRgb(accent, &accentRgb)) {
        s->accent = RgbToCss(accentRgb);
        s->accentRgb = accentRgb;
    }
    Wh_FreeStringSetting(accent);

    s->text.clear();
    s->textRgb = 0;
    std::uint32_t textRgb;
    PCWSTR text = Wh_GetStringSetting(L"textColor");
    if (HexColorToRgb(text, &textRgb)) {
        s->text = RgbToCss(textRgb);
        s->textRgb = textRgb;
    }
    Wh_FreeStringSetting(text);

    s->font.clear();
    PCWSTR font = Wh_GetStringSetting(L"fontFamily");
    if (font && *font) s->font = font;
    Wh_FreeStringSetting(font);
    s->fontWeight = Wh_GetIntSetting(L"fontWeight");
    if (s->fontWeight < 100 || s->fontWeight > 900) s->fontWeight = 400;

    s->nativeTitleBar = Wh_GetIntSetting(L"nativeTitleBar") != 0;
    s->titleBarAcrylic = Wh_GetIntSetting(L"titleBarAcrylic") != 0;
    s->centerTitle = Wh_GetIntSetting(L"centerTitle") != 0;

    s->titleBarColorSet = false;
    std::uint32_t titleBarRgb;
    PCWSTR titleBar = Wh_GetStringSetting(L"titleBarColor");
    if (HexColorToRgb(titleBar, &titleBarRgb)) {
        s->titleBarRgb = titleBarRgb;
        s->titleBarColorSet = true;
    }
    Wh_FreeStringSetting(titleBar);

    s->selectionColorSet = false;
    std::uint32_t selectionRgb;
    PCWSTR selection = Wh_GetStringSetting(L"selectionColor");
    if (HexColorToRgb(selection, &selectionRgb)) {
        s->selectionRgb = selectionRgb;
        s->selectionColorSet = true;
    }
    Wh_FreeStringSetting(selection);
    s->selectionOpacity = Wh_GetIntSetting(L"selectionOpacity");
    if (s->selectionOpacity < 0) s->selectionOpacity = 0;
    if (s->selectionOpacity > 100) s->selectionOpacity = 100;

    s->mochaIcons = Wh_GetIntSetting(L"mochaIcons") != 0;
    s->headerGradient = Wh_GetIntSetting(L"headerGradient") != 0;
    PCWSTR gradStart = Wh_GetStringSetting(L"gradientStart");
    if (!HexColorToRgb(gradStart, &s->gradientStart)) s->gradientStart = 0x89b4fa;
    Wh_FreeStringSetting(gradStart);
    PCWSTR gradEnd = Wh_GetStringSetting(L"gradientEnd");
    if (!HexColorToRgb(gradEnd, &s->gradientEnd)) s->gradientEnd = 0xcba6f7;
    Wh_FreeStringSetting(gradEnd);

    s->enhancedBadge = Wh_GetIntSetting(L"enhancedBadge") != 0;
    // Badge text goes into a CSS string: keep printable ASCII only, drop
    // quotes and backslashes, cap the length.
    s->badgeText.clear();
    PCWSTR badge = Wh_GetStringSetting(L"badgeText");
    for (PCWSTR p = badge; p && *p && s->badgeText.size() < 24; p++) {
        if (*p >= 0x20 && *p < 0x7f && *p != L'"' && *p != L'\\' && *p != L'<' && *p != L'>')
            s->badgeText += (char)*p;
    }
    Wh_FreeStringSetting(badge);
    if (s->badgeText.find_first_not_of(' ') == std::string::npos) s->enhancedBadge = false;
}

static Settings SnapshotSettings() {
    std::lock_guard<std::mutex> lock(g_settingsMutex);
    return g_settings;
}

static std::string RgbaFromRgb(std::uint32_t rgb, int opacityPercent) {
    char buf[48];
    snprintf(buf, sizeof(buf), "rgba(%u,%u,%u,%.3f)", (rgb >> 16) & 0xff, (rgb >> 8) & 0xff, rgb & 0xff, opacityPercent / 100.0);
    return buf;
}

// In Acrylic mode DWM paints the background tint (see ApplyWindowStack), so
// the clear caption strip and the body show one sheet. The page stays clear.
static std::string CssVeil(const Settings& s) {
    if (s.blur == 2) return "transparent";
    return RgbaFromRgb(s.background, s.backgroundOpacity);
}

static std::string CssCardColor(const Settings& s) {
    if (s.card.empty()) return "";
    if (s.cardOpacity >= 100) return s.card;
    unsigned r = 0, g = 0, b = 0;
    if (sscanf_s(s.card.c_str(), "rgb(%u,%u,%u)", &r, &g, &b) == 3) {
        std::uint32_t rgb = (r << 16) | (g << 8) | b;
        return RgbaFromRgb(rgb, s.cardOpacity);
    }
    return s.card;
}

static std::string JsonEscape(const std::string& in) {
    std::string out;
    out.reserve(in.size() + 16);
    for (unsigned char c : in) {
        switch (c) {
            case '\\': out += "\\\\"; break;
            case '"': out += "\\\""; break;
            case '\n': out += "\\n"; break;
            case '\r': out += "\\r"; break;
            case '\t': out += "\\t"; break;
            default:
                if (c < 0x20) {
                    char buf[8];
                    snprintf(buf, sizeof(buf), "\\u%04x", c);
                    out += buf;
                } else {
                    out += (char)c;
                }
        }
    }
    return out;
}

// Every box that takes the card color. Rounded corners and the card surface
// apply to this list; the solid popup material applies to kFloatingSurfaces
// and kPopoverSurfaces only.
static const char kSurfaces[] =
    ".ant-card,[class*=\"SaveSettingsCard\"],.ant-table,.ant-collapse,.ant-modal-content,.ant-modal-container,"
    ".ant-drawer-content,.ant-drawer-section,.ant-popover-inner,.ant-popover-container,.ant-select-dropdown,.ant-picker-dropdown,"
    ".ant-dropdown-menu,.ant-tooltip-inner,.ant-tooltip-container,.ant-notification-notice,.ant-message-notice-content";

// The subset that is static inside its own container, so it can take
// position:relative for its ring. Pop-ups (select, picker) are already
// absolutely positioned by the interface and keep their own position. The
// save card is left out: the interface positions it sticky so it floats
// while the settings scroll, and forcing relative would pin it to the page.
// Surfaces that float over other page content. In-flow cards stay plain:
// CSS cannot reach the DWM backdrop behind the page, and a filtered card
// becomes the backdrop root of everything inside it, so the sticky save
// bar in the mod page card could only ever blur the card itself.
static const char kFloatingSurfaces[] =
    "[class*=\"SaveSettingsCard\"],.ant-modal-content,.ant-modal-container,.ant-drawer-content,.ant-drawer-section,"
    ".ant-tooltip-inner,.ant-tooltip-container,.ant-notification-notice,.ant-message-notice-content";

// Popovers (the Remove confirm, for one) match the mod cards as they appear
// on screen: the card tint over the window acrylic reads about 6% lighter
// than the card color. CSS blur cannot read the acrylic, so they stay solid
// to keep the page text under them hidden.
static const char kPopoverSurfaces[] = ".ant-popover-inner,.ant-popover-container";

// Menus that open over the page are solid, not tinted. In Acrylic mode there
// is no opaque backdrop for CSS blur to read, so the old tint only imitated one.
static const char kMenuSurfaces[] = ".ant-select-dropdown,.ant-picker-dropdown,.ant-dropdown-menu";

static const char kRelativeSurfaces[] =
    ".ant-card:not([class*=\"SaveSettingsCard\"]),.ant-table,.ant-collapse,.ant-modal-content,.ant-modal-container,"
    ".ant-drawer-content,.ant-drawer-section,.ant-popover-inner,.ant-popover-container,.ant-dropdown-menu,.ant-tooltip-inner,.ant-tooltip-container,"
    ".ant-notification-notice,.ant-message-notice-content";

// Motion and glow layer: one place for every transition and hover halo.
// Glow uses the accent when set, otherwise a soft white. Reduced-motion
// users get no transitions.
// Error and info pop-ups (top right) in Catppuccin Mocha: a solid base
// (measured 2026-11-06: backdrop-filter never blurs the page in this
// WebView, text behind showed sharp at 72% and 96%), Mocha text and status colors, and an accent
// glow on hover. The notice root carries no filter, so the blur reads the
// page under it.
static std::string BuildNoticeCss(const Settings&) {
    const std::string n = ".ant-notification .ant-notification-notice";
    const std::string m = ".ant-message .ant-message-notice-content";
    std::string css;
    css += ".ant-notification,.ant-notification-notice-wrapper,.ant-message,.ant-message-notice{filter:none !important;}";
    // antd paints its own box on the stack wrapper and clips it: that box
    // peeked out as a pill between stacked notices and cut the bottom border.
    css += ".ant-notification-notice-wrapper{background:transparent !important;box-shadow:none !important;border:none !important;overflow:visible !important;}";
    css += ".ant-notification-notice-wrapper::before,.ant-notification-notice-wrapper::after{display:none !important;}";
    // The stack places notices by measured height, which runs short with a
    // wider font, so they overlapped. List them in normal flow instead.
    // Measured 2026-11-06: notices are absolute at --notification-y, spaced by
    // a height read before the font loaded (177px apart, 207px tall), so each
    // covered the bottom of the one above. A flex column spaces them by real height.
    // Ant Design reserves ::after as a 16px stack spacer; it cannot carry our surface ring.
    css += ".ant-notification .ant-notification-notice::before,.ant-notification .ant-notification-notice::after{display:none !important;content:none !important;}";
    // Ant Design's stack mode clips every notice but the newest to its top
    // half until the stack is hovered (the collapsed deck look), which slices
    // our full-height cards mid-text with no bottom border. Measured 2026-11-06:
    // collapsed notices computed clip-path inset(-48px -48px 50%). Keep every
    // notice unclipped in all stack states; the deck never overlaps here anyway.
    css += ".ant-notification .ant-notification-notice{clip-path:none !important;}";
    css += ".ant-notification-list-content{height:auto !important;display:flex !important;flex-direction:column !important;gap:12px !important;}";
    css += ".ant-notification-list-content>.ant-notification-notice{position:relative !important;transform:none !important;inset:auto !important;opacity:1 !important;pointer-events:auto !important;margin:0 !important;}";
    // 2.1.2: 2px edge, grey at rest, blue to mauve on hover; the hover glow is gone.
    css += n + "," + m + "{--whb-a:#45475a;--whb-b:#45475a;border:2px solid transparent !important;"
           "background:linear-gradient(180deg,rgba(49,50,68,0.55),rgba(30,30,46,0) 60%) padding-box,linear-gradient(#1e1e2e,#1e1e2e) padding-box,"
           "linear-gradient(125deg,var(--whb-a),var(--whb-b)) border-box !important;backdrop-filter:blur(28px) saturate(160%) !important;"
           "box-shadow:0 10px 30px rgba(17,17,27,0.55) !important;color:#cdd6f4 !important;"
           "transition:--whb-a .2s cubic-bezier(0.2,0,0,1),--whb-b .2s cubic-bezier(0.2,0,0,1) !important;}";
    css += n + ":hover," + m + ":hover{--whb-a:#89b4fa;--whb-b:#cba6f7;}";
    css += n + " .ant-notification-notice-title," + n + " .ant-notification-notice-message{color:#cdd6f4 !important;}";
    css += n + " .ant-notification-notice-description{color:#bac2de !important;}";
    css += n + " .ant-notification-notice-close{color:#a6adc8 !important;border-radius:6px;}";
    css += n + " .ant-notification-notice-close:hover{color:#f38ba8 !important;background:rgba(243,139,168,0.12) !important;}";
    css += ".ant-notification-notice-icon-error,.ant-message-error .anticon{color:#f38ba8 !important;}";
    css += ".ant-notification-notice-icon-success,.ant-message-success .anticon{color:#a6e3a1 !important;}";
    css += ".ant-notification-notice-icon-warning,.ant-message-warning .anticon{color:#f9e2af !important;}";
    css += ".ant-notification-notice-icon-info,.ant-message-info .anticon{color:#89b4fa !important;}";
    css += "@media (prefers-reduced-motion:reduce){" + n + "," + m + "{transition:none !important;}}";
    return css;
}

static std::string BuildPolishCss(const Settings&) {
    const std::string ease = "cubic-bezier(0.2,0,0,1)";
    std::string css;
    // Table cells: the sticky Status column paints antd's own dark fill, which
    // showed as a dark block beside tall rows. Let the row color through.
    css += ".ant-table-tbody>tr>td.ant-table-cell-fix-right,.ant-table-tbody>tr>td.ant-table-cell-fix-left,"
           ".ant-table-tbody>tr>td.ant-table-cell-fix-right-first,.ant-table-tbody>tr>td.ant-table-cell-fix-left-last,"
           ".ant-table-tbody>tr>td[rowspan]{background-color:transparent !important;}";
    css += ".ant-table-tbody>tr.ant-table-row:hover>td.ant-table-cell-fix-right,.ant-table-tbody>tr.ant-table-row:hover>td.ant-table-cell-fix-left{background-color:rgba(255,255,255,0.04) !important;}";
    css += "@media (prefers-reduced-motion:no-preference){";
    css += ".ant-btn,.ant-input,.ant-input-affix-wrapper,.ant-select-selector,.ant-input-number,.ant-picker,.ant-segmented-item,"
           ".ant-card,.ant-table-tbody>tr>td,.ant-tabs-tab,.ant-menu-item,.ant-dropdown-menu-item,.ant-select-item,.ant-switch,"
           ".ant-checkbox-inner,.ant-radio-inner,.ant-radio-button-wrapper,[class*=\"CardTitleModId\"],.ant-ribbon"
           "{transition:background-color .18s " + ease + ",border-color .18s " + ease + ",box-shadow .22s " + ease + ",color .18s " + ease + ",transform .18s " + ease + " !important;}";
    css += ".ant-segmented-thumb{transition:transform .26s " + ease + ",width .26s " + ease + " !important;}";
    css += ".ant-tabs-ink-bar{transition:left .26s " + ease + ",width .26s " + ease + " !important;}";
    css += ".ant-modal-content,.ant-popover-container{animation:whs-pop .18s " + ease + ";}";
    css += "@keyframes whs-pop{from{opacity:0;transform:translateY(4px) scale(.985);}to{opacity:1;transform:none;}}";
    // 2.2.4: menus that open over the page open instant and solid. antd's own
    // motion selectors (.ant-slide-up-enter-active..., 4 classes) outrank any
    // animation shorthand on the surface, so the 2.1.12 fade never ran: the
    // open was antd's antSlideUpIn, whose transform re-rasterized the layered
    // padding-box/border-box fill every frame in WebView2 and whose opacity
    // ramp left the page readable through the sheet. When antd then dropped
    // its motion classes the shorthand took over and restarted whs-fade from
    // opacity 0, the dip after each open. Ending the animation 1 ms after it
    // starts finishes before the first paint and still fires the animationend
    // rc-motion waits for, so the wrapper unmounts cleanly on close. Fill
    // stays the solid card sheet; the 2.1.7 open ring below is untouched.
    css += ":root :is(.ant-select-dropdown,.ant-picker-dropdown,.ant-dropdown,.ant-dropdown-menu){animation-duration:.001s !important;animation-delay:0s !important;}";
    css += "}";
    // Hover glows were replaced by 2px resting and hover borders (2.1.2, BuildButtonBorderCss).
    css += ".ant-btn:not(:disabled):active{transform:scale(.97);}";
    // antd clips card meta and head titles to their boxes, which shears the
    // hover halos of buttons inside them. Measured 2026-11-06 on the mod
    // details page: the Disable halo was cut at the meta title's left edge
    // (button left 448 == meta title left 448) and at y 274 where all three
    // wrappers end. The app truncates titles with its own EllipsisText
    // component, so the antd-level clipping is redundant. Let halos breathe.
    // Scoped to the details card only: unscoped, it let the Explore cards'
    // process list run past the card edge (owner report 2026-11-07).
    css += "[class*=\"ModDetailsCard\"] .ant-card-meta-title,[class*=\"ModDetailsCard\"] .ant-card-meta-section,[class*=\"ModDetailsCard\"] .ant-card-head-title{overflow:visible !important;}";
    // With the clip above lifted, a long one-line description ran past the
    // details card and was cut mid-word with no ellipsis (owner report
    // 2026-11-14, Adaptive Windows page). Wrap it onto more lines instead.
    css += "[class*=\"ModDetailsCard\"] .ant-card-meta-title{white-space:normal !important;}";
    css += "[class*=\"CardTitleDescription\"]{white-space:normal !important;overflow:visible !important;text-overflow:clip !important;overflow-wrap:anywhere;}";
    return css;
}

// Selected text, the gradient header and the Enhanced badge.
// The page sets no ::selection rule of its own (measured 2026-11-07), so
// selections drew in Chromium's stock blue. The logo is a white mask on a
// span, the section icons are Font Awesome SVGs painted with currentColor;
// the SVG icons take their gradient from #wh-enh-grad, injected by the JS.
static std::string BuildEnhancedCss(const Settings& s) {
    std::string css;
    std::uint32_t selRgb = s.selectionColorSet ? s.selectionRgb : (s.accent.empty() ? 0x89b4fa : s.accentRgb);
    const std::string sel = RgbaFromRgb(selRgb, s.selectionOpacity);
    const std::string selDim = RgbaFromRgb(selRgb, s.selectionOpacity / 2);
    css += "::selection{background-color:" + sel + " !important;}";
    css += "input::selection,textarea::selection{background-color:" + sel + " !important;}";
    css += ".monaco-editor{--vscode-editor-selectionBackground:" + sel + " !important;--vscode-editor-inactiveSelectionBackground:" + selDim +
           " !important;--vscode-editor-selectionHighlightBackground:" + selDim + " !important;}";
    css += ".monaco-editor .selected-text{background-color:" + sel + " !important;}";

    const std::string a = RgbToCss(s.gradientStart);
    const std::string b = RgbToCss(s.gradientEnd);
    const std::string grad = "linear-gradient(90deg," + a + "," + b + ")";
    const std::string logoBtn = "[class*=\"AppHeader__HeaderLogoButton\"]";
    const std::string sectionH2 = "[class*=\"SectionHeader\"]>h2";
    if (s.headerGradient) {
        const std::string clipText = "background-image:" + grad + " !important;-webkit-background-clip:text !important;background-clip:text !important;"
                                     "color:transparent !important;-webkit-text-fill-color:transparent !important;";
        // The button box also holds the logo (and the badge), so the stops
        // are pulled in to run the whole gradient across the word itself.
        const std::string titleGrad = s.enhancedBadge ? "linear-gradient(90deg," + a + " 24%," + b + " 74%)"
                                                      : "linear-gradient(90deg," + a + " 30%," + b + " 100%)";
        css += logoBtn + "," + logoBtn + ":hover," + logoBtn + ":focus{" + clipText + "background-image:" + titleGrad + " !important;}";
        css += "[class*=\"AppHeader__LogoMark\"]{background-color:transparent !important;background-image:linear-gradient(135deg," + a + "," + b + ") !important;}";
        css += sectionH2 + "{width:fit-content !important;" + clipText + "}";
        css += sectionH2 + ">svg,[class*=\"SectionIcon\"]{color:" + a + " !important;}";
        css += sectionH2 + ">svg path,[class*=\"SectionIcon\"] path{fill:url(#wh-enh-grad) !important;}";
        css += logoBtn + "::selection," + sectionH2 + "::selection{-webkit-text-fill-color:" + RgbToCss(s.gradientEnd) + " !important;}";
    }
    if (s.enhancedBadge) {
        // Sized against the 40px title: a pill about a third of its height,
        // centered on the letters, like the T3 Code Enhanced badge.
        css += logoBtn + "{white-space:nowrap !important;}";
        css += logoBtn + "::after{content:\"" + s.badgeText + "\";display:inline-block;margin-left:14px;padding:3px 11px 4px;"
               "font-size:15px;line-height:1.25;font-weight:700;letter-spacing:0.02em;border-radius:999px;"
               "background:" + grad + ";-webkit-background-clip:border-box;background-clip:border-box;"
               "color:#11111b;-webkit-text-fill-color:#11111b;box-shadow:0 0 12px " + RgbaFromRgb(s.gradientEnd, 30) + ";"
               "vertical-align:middle;position:relative;top:-3px;}";
    }
    return css;
}

static std::string BuildCss(const Settings& s) {
    std::string veil = CssVeil(s);
    const std::string focus = RgbaFromRgb(s.accentRgb, 20);
    std::string css;
    // The input starts at x 0 inside its box, so the caret was half clipped and
    // sat on the first placeholder letter. Give it room and push the placeholder back.
    css += ".ant-input-affix-wrapper>input.ant-input{padding-left:3px !important;}";
    css += ".ant-input-affix-wrapper>input.ant-input::placeholder{text-indent:3px;}";
    // Windhawk alpha 8 runs antd 6, which declares its tokens on every
    // component (the css-var class) and Windhawk's own on body, so values on
    // :root alone never reach the controls or the modified-setting bar.
    css += ":root,body,[class*=\"css-var-\"]{";
    css += "--whui-background-color:" + veil + " !important;";
    std::string cardColor = CssCardColor(s);
    if (!cardColor.empty()) {
        css += "--whui-card-background-color:" + cardColor + " !important;";
        css += "--whui-modal-background-color:" + cardColor + " !important;";
    }
    if (!s.accent.empty()) {
        css += "--whui-primary:" + s.accent + " !important;";
        css += "--ant-color-primary:" + s.accent + " !important;";
        css += "--ant-color-primary-hover:" + s.accent + " !important;";
        css += "--ant-color-primary-active:" + s.accent + " !important;";
        css += "--ant-color-link:" + s.accent + " !important;";
        css += "--ant-color-link-hover:" + s.accent + " !important;";
        css += "--ant-color-link-active:" + s.accent + " !important;";
        css += "--ant-control-outline:" + focus + " !important;";
        // The interface's own accent tokens: the modified-setting bar, links,
        // selected rows and moved rows otherwise keep its stock blue.
        css += "--whui-setting-non-default:" + s.accent + " !important;";
        css += "--whui-link:" + s.accent + " !important;";
        css += "--whui-link-hover:" + s.accent + " !important;";
        css += "--whui-selected-bg:" + RgbaFromRgb(s.accentRgb, 15) + " !important;";
        css += "--whui-setting-moved-bg:" + RgbaFromRgb(s.accentRgb, 20) + " !important;";
    }
    if (!s.text.empty()) {
        css += "--whui-text-secondary:" + s.text + " !important;";
        css += "--whui-editor-fg:" + s.text + " !important;";
        css += "--ant-color-text:" + s.text + " !important;";
        css += "--ant-color-text-heading:" + s.text + " !important;";
        css += "--ant-radio-button-color:" + s.text + " !important;";
        css += "--ant-segmented-item-color:" + s.text + " !important;";
        css += "--ant-segmented-item-hover-color:" + s.text + " !important;";
    }
    // antd 6 bakes its stock dark colors into per-component tokens (select,
    // radio buttons, segmented track, modal), so each one is mapped here.
    if (!s.control.empty()) {
        for (const char* token : {"--ant-color-bg-container", "--ant-color-border-bg", "--ant-select-selector-bg",
                                  "--ant-select-clear-bg", "--ant-input-hover-bg", "--ant-input-active-bg",
                                  "--ant-button-default-bg", "--ant-button-default-hover-bg", "--ant-button-default-active-bg",
                                  "--ant-radio-button-bg", "--ant-radio-button-checked-bg", "--ant-segmented-track-bg"}) {
            css += std::string(token) + ":" + s.control + " !important;";
        }
        css += "--ant-color-border:rgba(255,255,255,0.12) !important;";
        css += "--ant-button-default-border-color:rgba(255,255,255,0.12) !important;";
        css += "--ant-color-border-secondary:rgba(255,255,255,0.08) !important;";
    }
    if (!cardColor.empty()) {
        Settings solid = s;
        solid.cardOpacity = 100;
        const std::string elevated = CssCardColor(solid);
        css += "--ant-color-bg-elevated:" + elevated + " !important;";
        css += "--ant-color-bg-spotlight:" + elevated + " !important;";
        css += "--ant-modal-content-bg:" + elevated + " !important;";
        css += "--ant-card-actions-bg:" + cardColor + " !important;";
    }
    if (!s.accent.empty()) {
        for (const char* token : {"--ant-color-primary-text", "--ant-color-primary-text-hover", "--ant-color-primary-text-active",
                                  "--ant-color-info", "--ant-color-info-hover", "--ant-color-info-active",
                                  "--ant-color-info-text", "--ant-color-info-text-hover", "--ant-color-info-text-active",
                                  "--ant-select-hover-border-color", "--ant-select-active-border-color",
                                  "--ant-input-hover-border-color", "--ant-input-active-border-color",
                                  "--ant-button-default-hover-color", "--ant-button-default-hover-border-color",
                                  "--ant-button-default-active-color", "--ant-button-default-active-border-color",
                                  "--ant-button-group-border-color", "--ant-radio-radio-bg-color",
                                  "--ant-radio-button-solid-checked-bg", "--ant-radio-button-solid-checked-hover-bg",
                                  "--ant-radio-button-solid-checked-active-bg", "--ant-tabs-ink-bar-color",
                                  "--ant-tabs-item-selected-color", "--ant-tabs-item-hover-color",
                                  "--ant-tabs-item-active-color", "--ant-segmented-item-selected-bg"}) {
            css += std::string(token) + ":" + s.accent + " !important;";
        }
        for (const char* token : {"--ant-color-primary-bg", "--ant-color-info-bg", "--ant-control-item-bg-active",
                                  "--ant-select-option-selected-bg"}) {
            css += std::string(token) + ":" + RgbaFromRgb(s.accentRgb, 16) + " !important;";
        }
        for (const char* token : {"--ant-color-primary-bg-hover", "--ant-color-info-bg-hover", "--ant-control-item-bg-active-hover"}) {
            css += std::string(token) + ":" + RgbaFromRgb(s.accentRgb, 22) + " !important;";
        }
        css += "--ant-color-primary-border:" + RgbaFromRgb(s.accentRgb, 40) + " !important;";
        css += "--ant-color-info-border:" + RgbaFromRgb(s.accentRgb, 40) + " !important;";
        css += "--ant-color-primary-border-hover:" + RgbaFromRgb(s.accentRgb, 60) + " !important;";
        css += "--ant-color-info-border-hover:" + RgbaFromRgb(s.accentRgb, 60) + " !important;";
        css += "--ant-select-active-outline-color:" + focus + " !important;";
        // The underglow below primary buttons and the focus ring on inputs.
        css += "--ant-button-primary-shadow:0 2px 0 " + RgbaFromRgb(s.accentRgb, 31) + " !important;";
        css += "--ant-button-blue-shadow-color:0 2px 0 " + RgbaFromRgb(s.accentRgb, 31) + " !important;";
        css += "--ant-input-active-shadow:0 0 0 2px " + RgbaFromRgb(s.accentRgb, 31) + " !important;";
        css += "--ant-radio-button-solid-checked-color:#11111b !important;";
        css += "--ant-segmented-item-selected-color:#11111b !important;";
    }
    css += "}";
    css += "html{background-color:transparent !important;}";
    css += "body{background-color:" + veil + " !important;";
    if (!s.text.empty()) css += "color:" + s.text + " !important;";
    if (!s.font.empty()) {
        int length = WideCharToMultiByte(CP_UTF8, 0, s.font.data(), (int)s.font.size(), nullptr, 0, nullptr, nullptr);
        std::string utf8(length, '\0');
        WideCharToMultiByte(CP_UTF8, 0, s.font.data(), (int)s.font.size(), utf8.data(), length, nullptr, nullptr);
        std::string fontCss;
        for (char c : utf8) {
            if (c == '\\' || c == '\'') fontCss += '\\';
            fontCss += (unsigned char)c < 32 ? ' ' : c;
        }
        css += "font-family:'" + fontCss + "',monospace !important;";
    }
    css += "font-weight:" + std::to_string(s.fontWeight) + " !important;}";
    if (!s.font.empty()) {
        std::string fontCss;
        for (wchar_t c : s.font) fontCss += (c == L'\'' || c == L'\\' || c < 32 || c > 126) ? ' ' : (char)c;
        // Every text element takes the font, form controls and pop-ups
        // included (they do not inherit it). The code editor keeps its own
        // font so its cursor and column math stay right.
        css += ":root{--ant-font-family:'" + fontCss + "',monospace !important;--ant-font-family-code:'" + fontCss + "',monospace !important;}";
        css += "body *:not(.monaco-editor):not(.monaco-editor *):not(.anticon):not(svg):not(svg *){font-family:'" + fontCss + "',monospace !important;}";
    }
    // Controls hardcode the normal weight; give them the chosen one.
    css += "button,input,textarea,select,.ant-btn,.ant-input,.ant-select-selector,.ant-select-item-option-content,.ant-menu-item,.ant-tabs-tab-btn,"
           ".ant-card-meta-description,.ant-checkbox-wrapper,.ant-radio-wrapper,.ant-form-item-label>label,.ant-dropdown-menu-item,.ant-tooltip-inner,"
           ".ant-notification-notice-description,.ant-message-notice-content,.ant-segmented-item-label,.ant-empty-description,td,li,p"
           "{font-weight:" + std::to_string(s.fontWeight) + " !important;}";
    css += "[data-testid=mod-setting-reset]{margin-inline-start:0!important;}";
    // Buttons with an icon center it on both axes; the text font's line
    // height otherwise drops icons below center. The page buttons get a gap.
    css += ".ant-btn:has(>svg),.ant-btn-icon-only{display:inline-flex !important;align-items:center !important;justify-content:center !important;}";
    css += ".ant-btn-icon-only{padding:0 !important;}";
    css += ".ant-btn>svg{display:block !important;flex:none;}";
    css += ".ant-btn-icon-only>.anticon{display:block !important;margin:0 !important;}";
    // The tab overflow trigger is not an .ant-btn, so its icon aligns to the text line instead.
    css += ".ant-tabs-nav-more>span.anticon{vertical-align:middle !important;}";
    css += "[class*=\"ModPageButtonsWrapper\"]{gap:6px !important;}";
    // AntD paints a 1px separator before the ... trigger of the Load compact
    // group; in the accent color it reads as a stray line through the pill.
    // Remove it, the two buttons stay joined.
    css += ".ant-space-compact .ant-btn-compact-last-item::before{display:none !important;}";
    // Number spinners: flat handles with one divider instead of boxed buttons.
    css += ".ant-input-number-handler-wrap,.ant-input-number-actions{background-color:rgba(255,255,255,0.06) !important;border:0 !important;}";
    css += ".ant-input-number-handler,.ant-input-number-action{border:0 !important;}";
    css += ".ant-input-number-handler-up,.ant-input-number-action-up{border-bottom:1px solid rgba(255,255,255,0.08) !important;}";
    css += ".ant-input-number-handler:hover,.ant-input-number-action:hover{background-color:rgba(255,255,255,0.08) !important;}";
    if (!cardColor.empty()) {
        // Every box shares one surface: the card color, no border of its own,
        // and one 1px ring painted over its content. Headers and rows paint
        // translucent tints, so a plain border showed different colors on the
        // straight edges than around the rounded corners.
        css += std::string(kSurfaces) + "{background-color:" + cardColor + " !important;border:0 !important;}";
        css += std::string(kRelativeSurfaces) + "{position:relative;}";
        css += std::string(":is(") + kSurfaces + ")::after{content:'';position:absolute;inset:0;border:1px solid rgba(255,255,255,0.08);border-radius:inherit;pointer-events:none;z-index:2;}";
        css += ".ant-modal-header,.ant-modal-footer,.ant-drawer-header,.ant-drawer-body,.ant-drawer-footer,.ant-popover-title{background:transparent !important;}";
        css += ".ant-modal-title,.ant-popover-title{color:var(--whui-text-secondary) !important;}";
        // The interface paints fixed dark grays on tables; the shared surface above re-tints them.
        // The inner container draws its own straight 1px side borders, which
        // the rounded clip then notches at the corners. Drop them: the single
        // wrapper border above is the one consistent outline.
        css += ".ant-table-container{border-width:0 !important;}";
        css += ".ant-table-thead>tr>th{background-color:rgba(255,255,255,0.03) !important;border-color:rgba(255,255,255,0.08) !important;}";
        css += ".ant-table-tbody>tr>td{border-color:rgba(255,255,255,0.06) !important;}";
        css += ".ant-table-tbody>tr.ant-table-row:hover>td,.ant-table-tbody>tr>td.ant-table-cell-row-hover{background-color:rgba(255,255,255,0.04) !important;}";
        css += ".ant-table-tbody>tr.ant-table-expanded-row>td{background-color:rgba(255,255,255,0.02) !important;}";
        css += ".ant-table.ant-table-bordered>.ant-table-container,.ant-table.ant-table-bordered>.ant-table-content>table{border-color:rgba(255,255,255,0.08) !important;}";
        css += ".ant-table-cell-scrollbar:not([rowspan]){box-shadow:" + cardColor + " 0 1px 0 1px !important;}";
        css += ".ant-table-filter-trigger:hover,.ant-table .ant-table-filter-trigger-container-open{background-color:rgba(255,255,255,0.06) !important;}";
        css += ".ant-collapse{background-color:transparent !important;border-color:rgba(255,255,255,0.08) !important;}";
        css += ".ant-collapse>.ant-collapse-item{border-color:rgba(255,255,255,0.08) !important;}";
        css += ".ant-collapse-header{background-color:" + cardColor + " !important;border-radius:0 !important;}";
        css += ".ant-collapse-content{background-color:" + cardColor + " !important;border-color:rgba(255,255,255,0.08) !important;border-radius:0 !important;}";
        if (s.cardOpacity < 100) {
            // Measured 2026-11-02: on the acrylic page a backdrop filter behind a
            // floating box never hides the text under it. The page shows through
            // the last percent sharp on the icon tooltips, the mod author pop-up
            // and a plain test div alike, so every floating surface gets the
            // popover treatment: one solid card surface, no backdrop filter.
            css += std::string(kFloatingSurfaces) + "{background-color:color-mix(in srgb," + s.card + " 94%,#ffffff) !important;backdrop-filter:none !important;}";
            css += std::string(kPopoverSurfaces) + "{background-color:color-mix(in srgb," + s.card + " 94%,#ffffff) !important;backdrop-filter:none !important;}";
            // antd draws the popover shadow as a filter on the outer
            // .ant-popover. A filter makes that element the backdrop root, so
            // the blur inside it saw nothing and the page showed through sharp.
            css += ".ant-popover{filter:none !important;} .ant-popover-container{box-shadow:0 6px 16px rgba(0,0,0,0.32) !important;}";
            // The Mod author pop-up is an antd tooltip and hits the same trap:
            // the drop-shadow on the outer .ant-tooltip makes it the backdrop
            // root, so the container's blur saw nothing and the page showed
            // through sharp. Drop the filter and move the shadow onto the
            // container.
            css += ".ant-tooltip{filter:none !important;} .ant-tooltip-container{box-shadow:0 6px 16px rgba(0,0,0,0.32) !important;}";
            // The popover can paint its box on two nested elements. Two tinted
            // layers stack to a near-solid box, so whichever one wraps the other goes clear.
            css += ".ant-popover-container:has(.ant-popover-inner),.ant-popover-inner:has(.ant-popover-container){background-color:transparent !important;backdrop-filter:none !important;}";
            Settings menu = s;
            menu.cardOpacity = 100;
            css += std::string(kMenuSurfaces) + "{background-color:" + CssCardColor(menu) + " !important;backdrop-filter:none !important;}";
            // The save bar takes the popover color, so both match the mod cards.
            css += "[class*=\"SaveSettingsCard\"]{background-color:color-mix(in srgb," + s.card + " 94%,#ffffff) !important;backdrop-filter:none !important;}";
        }
    }
    if (!s.control.empty()) {
        css += ".ant-btn{background-color:" + s.control + " !important;border-color:rgba(255,255,255,0.12) !important;}";
        css += ".ant-input,.ant-input-affix-wrapper,.ant-select-selector,.ant-select:not(.ant-select-dropdown),.ant-input-number,.ant-picker{background-color:" + s.control + " !important;border-color:rgba(255,255,255,0.12) !important;}";
        if (cardColor.empty()) css += ".ant-dropdown-menu{background-color:" + s.control + " !important;}";
    }
    if (!s.text.empty()) {
        css += ".ant-table,.ant-table-thead>tr>th{color:" + s.text + " !important;}";
        css += ".ant-table-column-sorter{color:" + RgbaFromRgb(s.textRgb, 70) + " !important;}";
    }
    if (!s.accent.empty()) {
        std::string selected = RgbaFromRgb(s.accentRgb, 16);
        css += ".ant-btn-primary,.ant-btn-primary:hover,.ant-btn-primary:focus,.ant-btn-primary:active{background-color:" + s.accent + " !important;border-color:" + s.accent + " !important;color:#11111b !important;}";
        css += ".ant-switch-checked,.ant-switch-checked:hover{background-color:" + s.accent + " !important;}";
        css += ".ant-input:hover,.ant-input-affix-wrapper:hover,.ant-select-selector:hover,.ant-select:not(.ant-select-dropdown):not(.ant-select-disabled):hover,.ant-input-number:hover,.ant-picker:hover{border-color:" + s.accent + " !important;}";
        css += ".ant-input:focus,.ant-input-focused,.ant-input-affix-wrapper-focused,.ant-input-affix-wrapper:focus-within,.ant-input-number-focused,.ant-select-focused .ant-select-selector,.ant-select-focused:not(.ant-select-dropdown),.ant-picker-focused{border-color:" + s.accent + " !important;box-shadow:0 0 0 2px " + focus + " !important;}";
        // A -1px offset centres the 2px ring on the 1px control border, so it
        // hugs the rounded edge with no gap at the top, bottom or arcs.
        css += ".ant-btn:focus-visible,.ant-input:focus-visible,.ant-select-selector:focus-visible,.ant-input-number:focus-visible,.ant-picker:focus-visible,.ant-checkbox-input:focus-visible+.ant-checkbox-inner,.ant-radio-input:focus-visible+.ant-radio-inner{outline:2px solid " + s.accent + " !important;outline-offset:-1px;}";
        // The search input sits inside an affix wrapper, which owns the focus
        // ring, hover border and every other state. The nested input draws
        // none of it: a second box inside the search field read as a stray
        // selected rectangle, so it stays chrome-free in every state.
        css += ".ant-input-affix-wrapper>input.ant-input,.ant-input-affix-wrapper>input.ant-input:hover,"
               ".ant-input-affix-wrapper>input.ant-input:focus,.ant-input-affix-wrapper>input.ant-input:focus-visible,"
               ".ant-input-affix-wrapper>input.ant-input:active"
               "{background:transparent !important;border:none !important;box-shadow:none !important;outline:none !important;}";
        css += ".ant-tabs-tab-active .ant-tabs-tab-btn{color:" + s.accent + " !important;}";
        css += ".ant-tabs-ink-bar{background-color:" + s.accent + " !important;}";
        css += ".ant-menu-item-selected{color:" + s.accent + " !important;}";
        css += ".ant-menu-item-selected,.ant-dropdown-menu-item-selected,.ant-dropdown-menu-item-active,.ant-select-item-option-active:not(.ant-select-item-option-disabled),.ant-select-item-option-selected:not(.ant-select-item-option-disabled){background-color:" + selected + " !important;}";
        // The rows paint their own fill. The 4px top and bottom padding left a
        // band above a hovered first row, so the list runs to the panel edge.
        css += ".ant-select-dropdown,.ant-dropdown-menu{padding:0 !important;}";
        css += "a{color:" + s.accent + " !important;}";
        css += ".ant-btn-link{color:" + s.accent + " !important;}";
        css += ".ant-radio-checked .ant-radio-inner{border-color:" + s.accent + " !important;}";
        css += ".ant-radio-checked .ant-radio-inner::after{background-color:" + s.accent + " !important;}";
        css += ".ant-radio-button-wrapper-checked:not(.ant-radio-button-wrapper-disabled){color:" + s.accent + " !important;border-color:" + s.accent + " !important;}";
        css += ".ant-radio-button-wrapper-checked:not(.ant-radio-button-wrapper-disabled)::before{background-color:" + s.accent + " !important;}";
        css += ".ant-checkbox-checked .ant-checkbox-inner{background-color:" + s.accent + " !important;border-color:" + s.accent + " !important;}";
        css += ".ant-checkbox-wrapper:hover .ant-checkbox-inner,.ant-checkbox:hover .ant-checkbox-inner{border-color:" + s.accent + " !important;}";
        css += ".ant-segmented-item-selected,.ant-segmented-item-selected:hover{background-color:" + s.accent + " !important;color:#11111b !important;}";
        css += ".ant-pagination-item-active{border-color:" + s.accent + " !important;} .ant-pagination-item-active a{color:" + s.accent + " !important;}";
        css += ".ant-slider-track,.ant-slider:hover .ant-slider-track{background-color:" + s.accent + " !important;}";
        css += ".ant-slider-handle::after{box-shadow:0 0 0 2px " + s.accent + " !important;}";
        css += ".ant-picker-cell-selected .ant-picker-cell-inner{background-color:" + s.accent + " !important;color:#11111b !important;}";
        css += ".ant-alert-info{background-color:" + RgbaFromRgb(s.accentRgb, 8) + " !important;border-color:" + RgbaFromRgb(s.accentRgb, 28) + " !important;}";
        css += ".ant-alert-info .ant-alert-icon,.ant-alert-info .ant-alert-message{color:" + s.accent + " !important;}";
        css += ".ant-progress-bg,.ant-progress-track:not(.ant-progress-track-success){background-color:" + s.accent + " !important;} .ant-progress-circle-path{stroke:" + s.accent + " !important;}";
        css += ".ant-rate-star-full .ant-rate-star-second,.ant-rate-star-half .ant-rate-star-first{color:" + s.accent + " !important;}";
        css += ".ant-table-column-sorter-down.active,.ant-table-column-sorter-up.active,.ant-table-filter-trigger.active{color:" + s.accent + " !important;}";
        css += ".ant-table-tbody>tr.ant-table-row-selected>td{background-color:" + RgbaFromRgb(s.accentRgb, 15) + " !important;}";
        css += ".ant-table-tbody>tr.ant-table-row-selected:hover>td{background-color:" + RgbaFromRgb(s.accentRgb, 20) + " !important;}";
        css += ".wh-cscroll-host::-webkit-scrollbar-thumb:hover{background-color:" + s.accent + " !important;}";
        css += ".ant-input-number-handler:hover .ant-input-number-handler-up-inner,.ant-input-number-handler:hover .ant-input-number-handler-down-inner,.ant-input-number-action:hover .ant-input-number-action-up-inner,.ant-input-number-action:hover .ant-input-number-action-down-inner{color:" + s.accent + " !important;}";
        // Interface defaults that otherwise keep antd's built-in blue: the
        // mod-card ribbon, loading spinner, tab and default-button hovers,
        // the selected drop-down item and selected select option.
        css += ".ant-ribbon{background-color:" + s.accent + " !important;color:#11111b !important;}";
        css += ".ant-ribbon-corner{color:" + s.accent + " !important;}";
        css += ".ant-spin-dot-item{background-color:" + s.accent + " !important;}";
        css += ".ant-tabs-tab:hover .ant-tabs-tab-btn{color:" + s.accent + " !important;}";
        css += ".ant-dropdown-menu-item-selected,.ant-dropdown-menu-item-selected>a{color:" + s.accent + " !important;}";
        css += ".ant-select-item-option-selected:not(.ant-select-item-option-disabled),.ant-select-item-option-state{color:" + s.accent + " !important;}";
        // Focus and press keep the accent too; antd paints focused buttons its own blue.
        css += ".ant-btn:not(.ant-btn-primary):not(.ant-btn-dangerous):hover,.ant-btn:not(.ant-btn-primary):not(.ant-btn-dangerous):focus,.ant-btn:not(.ant-btn-primary):not(.ant-btn-dangerous):active{color:" + s.accent + " !important;border-color:" + s.accent + " !important;}";
    }
    std::string scrollbarColor = s.text.empty() ? "rgba(255,255,255,0.35)" : RgbaFromRgb(s.textRgb, 35);
    std::string scrollbarRadius = s.roundedCorners && s.cornerRadius > 0 ? "999px" : "0px";
    // scrollbar-width would make Chromium ignore the ::-webkit-scrollbar rules
    // below, so the custom rounded thumb and the hidden arrows need it unset.
    css += ".wh-cscroll-host::-webkit-scrollbar-button{display:none !important;}";
    // Windhawk hides the native bars and draws its own overlay thumb, square and
    // grey by default. Round it and use the same colour as the drop-down list bar.
    css += ":root{--wh-cscroll-thumb:" + scrollbarColor + " !important;}";
    css += ".wh-cscroll-thumb{border-radius:" + scrollbarRadius + " !important;}";
    css += ".wh-cscroll-host::-webkit-scrollbar{width:12px !important;height:12px !important;display:block !important;}";
    css += ".wh-cscroll-host::-webkit-scrollbar-track{background:transparent !important;}";
    css += ".wh-cscroll-host::-webkit-scrollbar-thumb{background-color:" + scrollbarColor + " !important;border:3px solid transparent !important;background-clip:content-box !important;border-radius:" + scrollbarRadius + " !important;}";
    if (s.roundedCorners && s.cornerRadius > 0) {
        // Rounded element corners: cards, tables, dialogs and controls share
        // one adjustable radius. Off (or 0) leaves Windhawk's stock corners.
        std::string r = std::to_string(s.cornerRadius) + "px";
        css += std::string(kSurfaces) + ",.ant-alert{border-radius:" + r + " !important;}";
        css += ".ant-btn,.ant-input,.ant-input-affix-wrapper,.ant-select-selector,.ant-select:not(.ant-select-dropdown),.ant-input-number,.ant-picker,.ant-segmented{border-radius:" + r + " !important;}";
        // The spinner handles become a small inset pill inside the rounded
        // input, so their square box no longer pokes past its corners.
        std::string inner = std::to_string(std::max(0, s.cornerRadius - 3)) + "px";
        css += ".ant-input-number-handler-wrap{top:3px !important;bottom:3px !important;right:3px !important;height:auto !important;width:20px !important;border-radius:" + inner + " !important;overflow:hidden !important;}";
        css += ".ant-input-number-handler{border-radius:0 !important;}";
        // The sticky save bar is its own rounded card; keep it clear of the
        // page card's edges instead of running into them. Its sticky
        // positioning comes from the interface, so it keeps floating. It
        // sticks 12px below the scroll top so its rounded top corners and
        // outline stay fully visible instead of touching the viewport edge.
        css += "[class*=\"SaveSettingsCard\"]{margin-inline:-12px !important;top:12px !important;}";
        // The page card ends flush with the scroll viewport, which slices its
        // bottom rounded corners; leave room so the curve stays visible.
        // Padding on the page container, not margin on the card: the
        // scroller leaves the card's bottom margin out of its scroll range.
        css += "[class*=\"ModDetailsContainer\"]{padding-bottom:12px !important;}";
        // Freeze the page card so its rounded frame never moves. The card keeps
        // its header and tabs at the top and its body scrolls below them, clear of
        // the card's top and bottom, so the scrollbar runs along the straight right
        // edge and never reaches the rounded corners. The 163px is the scroller top (131)
        // plus the card offset (20) plus the bottom clearance (12). Only when the
        // card is the last child, so pages with content below keep the page scroll.
        const std::string frozenCard = "[class*=\"ModDetailsContainer\"]>[class*=\"ModDetailsCard\"]:last-child";
        const std::string frozenBody = frozenCard + ">.ant-card-body";
        css += frozenCard + "{display:flex !important;flex-direction:column !important;max-height:calc(100vh - 163px) !important;overflow:hidden !important;}";
        css += frozenCard + ">.ant-card-head{flex:none !important;}";
        css += frozenBody + "{flex:1 1 auto !important;min-height:0 !important;overflow-y:auto !important;overflow-x:hidden !important;margin-bottom:16px !important;}";
        css += frozenBody + "::-webkit-scrollbar{width:12px !important;height:12px !important;}";
        css += frozenBody + "::-webkit-scrollbar-track{background:transparent !important;}";
        css += frozenBody + "::-webkit-scrollbar-thumb{background-color:" + scrollbarColor + " !important;border:3px solid transparent !important;background-clip:content-box !important;border-radius:" + scrollbarRadius + " !important;}";
        css += frozenBody + "::-webkit-scrollbar-button{display:none !important;}";
        // The settings tab starts its first row under the floating save bar.
        // Drop the body's top padding there so the bar sits 12px below the
        // tabs, and give the bar room below so the first setting clears it.
        css += frozenBody + ":has([class*=\"SaveSettingsCard\"]){padding-top:0 !important;}";
        css += "[class*=\"SaveSettingsCard\"]{margin-bottom:24px !important;}";
        // The ring above is a pseudo-element, so inside the scrolling card it
        // moves with the content and shows its bottom edge mid-box. The frozen
        // card paints its ring as an inset shadow instead, which stays put.
        css += "[class*=\"ModDetailsContainer\"]>[class*=\"ModDetailsCard\"]:last-child::after{display:none !important;}";
        css += "[class*=\"ModDetailsContainer\"]>[class*=\"ModDetailsCard\"]:last-child{box-shadow:inset 0 0 0 1px rgba(255,255,255,0.08) !important;}";
        // Joined pills: the mode switch, the version switch and the mod id
        // chip round only their outer ends so each reads as one pill.
        std::string segInner = std::to_string(std::max(0, s.cornerRadius - 2)) + "px";
        css += ".ant-segmented-item:first-child{border-radius:" + segInner + " 0 0 " + segInner + " !important;}";
        css += ".ant-segmented-item:last-child{border-radius:0 " + segInner + " " + segInner + " 0 !important;}";
        css += ".ant-segmented-thumb{border-radius:" + segInner + " !important;}";
        css += ".ant-radio-group .ant-radio-button-wrapper:first-child{border-radius:" + r + " 0 0 " + r + " !important;}";
        css += ".ant-radio-group .ant-radio-button-wrapper:last-child{border-radius:0 " + r + " " + r + " 0 !important;}";
        css += "[class*=\"CardTitleModId\"]{border-radius:" + r + " !important;}";
        // The process inclusion list and its info box below join as one
        // block: square corners at the seam, borders overlapping by 1px.
        css += "textarea[data-testid=\"engine-include\"]{border-bottom-left-radius:0 !important;border-bottom-right-radius:0 !important;}";
        css += "textarea[data-testid=\"engine-include\"]+.ant-alert{border-top-left-radius:0 !important;border-top-right-radius:0 !important;margin-top:-1px !important;}";
        // Match the table's inset header corners so the card-colored surface
        // cannot show through as a dark notch beside the rounded outer border.
        css += ".ant-table-thead>tr:first-child>th:first-child{border-top-left-radius:" + r + " !important;background-clip:padding-box !important;}";
        css += ".ant-table-thead>tr:first-child>th:last-child{border-top-right-radius:" + r + " !important;background-clip:padding-box !important;}";
        css += ".ant-table-tbody>tr:last-child>:first-child,.ant-table-tbody>tr:last-child>:last-child,.ant-collapse-header,.ant-collapse-content{border-radius:0 !important;}";
        // Clip inner painting to the rounded shape: without this, square
        // row/hover backgrounds poke past the table's rounded corners, and
        // square item hovers poke past rounded drop-down menus.
        css += ".ant-table,.ant-select-dropdown,.ant-picker-dropdown,.ant-dropdown-menu,.ant-collapse,.ant-modal-content,.ant-modal-container,.ant-drawer-content,.ant-drawer-section,.ant-popover-inner,.ant-popover-container{overflow:hidden !important;}";
        // The list scrollbar in a drop-down runs the menu's full height along its
        // edge, so its square ends stuck out past the curve. The clip keeps it
        // inside the straight edge and rounds its ends without moving antd's thumb.
        // The bar also sits 4px in from the menu's border, so it reads as inside
        // the menu rather than on its edge.
        css += ".rc-virtual-list-scrollbar{right:4px !important;clip-path:inset(" + r + " 0 " + r + " 0 round 4px) !important;}";
        css += ".rc-virtual-list-scrollbar-thumb{background:linear-gradient(180deg,#89b4fa,#cba6f7) !important;border-radius:999px !important;}";
        // Windhawk's own scrollbar overlay claims any scrollable box, drop-down lists
        // included, and draws a square bar over it that ignores the curve. Hiding the
        // native bar here makes the scan skip the list, so the rounded bar above is the
        // only one in a drop-down.
        css += ".ant-select-dropdown .rc-virtual-list-holder{scrollbar-width:none !important;}";
        // Windhawk's own overlay scrollbar can sit fixed over an open pop-up and run
        // straight past its rounded corners (2026-11-20 screenshot). Inside a pop-up the
        // clipped antd bar above is the one bar; the fixed case is cut to the pop-up's
        // rounded shape by the page script in BuildInjectJs.
        css += ".ant-select-dropdown :is(.wh-cscroll-track,.wh-cscroll-thumb),.ant-dropdown :is(.wh-cscroll-track,.wh-cscroll-thumb),.ant-picker-dropdown :is(.wh-cscroll-track,.wh-cscroll-thumb){display:none !important;}";
    }
    if (s.nativeTitleBar && s.titleBarAcrylic) {
        int caption = GetSystemMetricsForDpi(SM_CYCAPTION, 96) +
                      GetSystemMetricsForDpi(SM_CYFRAME, 96) +
                      GetSystemMetricsForDpi(SM_CXPADDEDBORDER, 96);
        std::string height = std::to_string(caption) + "px";
        css += "#root{position:fixed;inset:" + height + " 0 0 0;height:auto !important;margin:0 !important;overflow:hidden !important;}";
        css += "#root>[class*=\"Panel__PanelContainer\"],#root>[class*=\"Panel__PanelContainer\"]>[class*=\"Panel__MainArea\"]{height:100% !important;min-height:0 !important;}";
    }
    css += BuildPolishCss(s);
    css += BuildNoticeCss(s);
    css += BuildEnhancedCss(s);
    css += "\n[data-testid=\"mod-updates-modal\"] .ant-result-extra {background:transparent!important;padding:0!important;box-shadow:none!important;border:0!important;}\n[data-testid=\"mod-updates-modal\"] .ant-progress-bg,\n[data-testid=\"mod-updates-modal\"] .ant-progress-track {background:linear-gradient(100deg,#89b4fa,#b4befe 60%,#cba6f7)!important;}\n[data-testid=\"mod-updates-modal\"] .ant-progress-inner {background:#45475a!important;}\n";
    css += "\n.ant-dropdown:has([data-menu-id$=\"-clear-filters\"]) {\n --wh-filter-edge-blue:#89b4fa80;--wh-filter-edge-mauve:#cba6f770;\n filter:drop-shadow(-1px 0 0 var(--wh-filter-edge-blue)) drop-shadow(0 -1px 0 var(--wh-filter-edge-blue)) drop-shadow(1px 0 0 var(--wh-filter-edge-mauve)) drop-shadow(0 1px 0 var(--wh-filter-edge-mauve)) drop-shadow(0 8px 14px #0006)!important;\n transition:filter 150ms ease-out!important;\n}\n.ant-dropdown:has([data-menu-id$=\"-clear-filters\"]):hover,.ant-dropdown:has([data-menu-id$=\"-clear-filters\"]):focus-within {--wh-filter-edge-blue:#89b4fa;--wh-filter-edge-mauve:#cba6f7;}\n.ant-dropdown:has([data-menu-id$=\"-clear-filters\"])>.ant-dropdown-menu {background:#181825!important;color:#cdd6f4!important;border:0!important;box-shadow:none!important;border-radius:12px!important;padding:5px!important;}\n.ant-dropdown:has([data-menu-id$=\"-clear-filters\"])>.ant-dropdown-menu::after {display:none!important;}\n.ant-dropdown:has([data-menu-id$=\"-clear-filters\"])>.ant-dropdown-arrow::before {background:#181825!important;}\n.ant-dropdown:has([data-menu-id$=\"-clear-filters\"])>.ant-dropdown-arrow::after {display:none!important;}\n.ant-dropdown:has([data-menu-id$=\"-clear-filters\"]) .ant-dropdown-menu-item {color:#cdd6f4!important;border:1px solid transparent!important;border-radius:7px!important;margin:2px 0!important;padding:6px 9px!important;transition:background 150ms ease-out,border-color 150ms ease-out!important;}\n.ant-dropdown:has([data-menu-id$=\"-clear-filters\"]) .ant-dropdown-menu-item:hover,.ant-dropdown:has([data-menu-id$=\"-clear-filters\"]) .ant-dropdown-menu-item-active,.ant-dropdown:has([data-menu-id$=\"-clear-filters\"]) .ant-dropdown-menu-item:focus-visible {background:linear-gradient(110deg,#89b4fa20,#cba6f71a)!important;border-color:#89b4fa!important;color:#cdd6f4!important;outline:none!important;}\n.ant-dropdown:has([data-menu-id$=\"-clear-filters\"]) .ant-dropdown-menu-item-selected {background:#89b4fa18!important;border-color:#89b4fa70!important;color:#89b4fa!important;}\n.ant-dropdown:has([data-menu-id$=\"-clear-filters\"]) .ant-dropdown-menu-item-divider {background:#45475a!important;margin:5px 4px!important;}\n@media(prefers-reduced-motion:reduce){.ant-dropdown:has([data-menu-id$=\"-clear-filters\"]),.ant-dropdown:has([data-menu-id$=\"-clear-filters\"]) .ant-dropdown-menu-item {transition:none!important;}}\n";
    // 2.1.2: 2px borders everywhere (filter-button thickness), dark Mocha fills, grey at rest,
    // blue to mauve on hover, no glows. Also list view, selection bar, tooltips, right-click menu.
    css += R"WHB(@property --whb-a{syntax:'<color>';inherits:false;initial-value:#585b70}
@property --whb-b{syntax:'<color>';inherits:false;initial-value:#585b70}
@property --whb-f{syntax:'<color>';inherits:false;initial-value:#181825}
:root{--whb-ease:cubic-bezier(0.2,0,0,1);}
/* Buttons, close X, inputs, selects: 2px edge (filter-button thickness), dark Mocha fill, grey at rest, blue to mauve on hover. No glow. */
:root :is(.ant-btn:not(.ant-btn-link):not(.ant-btn-variant-link),.ant-modal-close,.ant-drawer-close,.ant-input-affix-wrapper,.ant-input:not(.ant-input-affix-wrapper *):not(.ant-input-number *):not(.ant-select *),textarea.ant-input,.ant-select-selector,.ant-select:not(.ant-select-dropdown):not(:has(.ant-select-selector)),.ant-input-number,.ant-picker){
 --whb-a:#585b70;--whb-b:#585b70;--whb-f:#181825;
 border:2px solid transparent !important;
 background:linear-gradient(var(--whb-f),var(--whb-f)) padding-box,linear-gradient(125deg,var(--whb-a),var(--whb-b)) border-box !important;
 box-shadow:none !important;
 transition:--whb-a .2s var(--whb-ease),--whb-b .2s var(--whb-ease),--whb-f .2s var(--whb-ease),color .18s var(--whb-ease),transform .18s var(--whb-ease) !important;
}
:root :is(.ant-btn:not(.ant-btn-link):not(.ant-btn-variant-link),.ant-modal-close,.ant-drawer-close){color:#cdd6f4 !important;}
:root :is(.ant-modal-close,.ant-drawer-close){border-radius:999px !important;color:#a6adc8 !important;}
:root .ant-btn.ant-btn-primary:not(.ant-btn-link){--whb-a:#89b4fa99;--whb-b:#cba6f799;--whb-f:#313244;color:#89b4fa !important;}
:root .ant-btn.ant-btn-dangerous:not(.ant-btn-link){color:#f38ba8 !important;}
:root :is(.ant-btn:not(.ant-btn-link):not(.ant-btn-variant-link):not(:disabled),.ant-modal-close,.ant-drawer-close):is(:hover,:focus-visible){
 --whb-a:#89b4fa;--whb-b:#cba6f7;--whb-f:#1e1e2e;color:#89b4fa !important;box-shadow:none !important;outline:none !important;
}
:root .ant-btn.ant-btn-primary:not(.ant-btn-link):not(:disabled):is(:hover,:focus-visible){--whb-f:#313244;}
:root .ant-btn.ant-btn-dangerous:not(.ant-btn-link):not(:disabled):is(:hover,:focus-visible){color:#f38ba8 !important;}
:root .ant-btn:not(.ant-btn-link):disabled{--whb-a:#45475a;--whb-b:#45475a;--whb-f:#181825;color:#6c7086 !important;}
:root :is(.ant-input-affix-wrapper,.ant-input:not(.ant-input-affix-wrapper *):not(.ant-input-number *):not(.ant-select *),.ant-select-selector,.ant-select:not(.ant-select-dropdown):not(:has(.ant-select-selector)),.ant-input-number,.ant-picker):not(.ant-input-affix-wrapper-disabled):not(.ant-select-disabled):not(.ant-input-number-disabled):not(.ant-picker-disabled):not(:disabled):is(:hover,:focus,:focus-within,.ant-input-affix-wrapper-focused,.ant-select-focused,.ant-input-number-focused,.ant-picker-focused){
 --whb-a:#89b4fa;--whb-b:#cba6f7;--whb-f:#1e1e2e;box-shadow:none !important;outline:none !important;
}
:root .ant-select-focused .ant-select-selector{--whb-a:#89b4fa;--whb-b:#cba6f7;--whb-f:#1e1e2e;box-shadow:none !important;}

/* Toggle: dark track, 2px ring, Mocha knob; checked gets the gradient knob. */
:root .ant-switch{position:relative;background:#181825 !important;box-shadow:none !important;overflow:visible !important;}
:root .ant-switch.ant-switch-checked{background:#313244 !important;}
:root .ant-switch::after{content:'' !important;position:absolute;inset:0;padding:2px;border-radius:inherit;pointer-events:none;
 --whb-a:#585b70;--whb-b:#585b70;background:linear-gradient(125deg,var(--whb-a),var(--whb-b));
 -webkit-mask:linear-gradient(#000 0 0) content-box,linear-gradient(#000 0 0);-webkit-mask-composite:xor;mask-composite:exclude;
 transition:--whb-a .2s var(--whb-ease),--whb-b .2s var(--whb-ease);}
:root .ant-switch.ant-switch-checked::after{--whb-a:#89b4fa99;--whb-b:#cba6f799;}
:root .ant-switch:not(.ant-switch-disabled):is(:hover,:focus-visible)::after{--whb-a:#89b4fa;--whb-b:#cba6f7;}
:root .ant-switch:is(:hover,:focus-visible){box-shadow:none !important;outline:none !important;}
:root .ant-switch .ant-switch-handle{top:4px !important;width:14px !important;height:14px !important;inset-inline-start:4px !important;}
:root .ant-switch.ant-switch-checked .ant-switch-handle{inset-inline-start:calc(100% - 18px) !important;}
:root .ant-switch .ant-switch-handle::before{background:#6c7086 !important;box-shadow:none !important;border-radius:999px !important;}
:root .ant-switch.ant-switch-checked .ant-switch-handle::before{background:linear-gradient(125deg,#89b4fa,#cba6f7) !important;}
:root .ant-switch-small .ant-switch-handle{top:3px !important;width:10px !important;height:10px !important;inset-inline-start:3px !important;}
:root .ant-switch-small.ant-switch-checked .ant-switch-handle{inset-inline-start:calc(100% - 13px) !important;}

/* Cards and every other surface: the ring goes 1px to 2px; in-page cards light up blue to mauve on hover instead of glowing. */
:root :is(.ant-card,[class*="SaveSettingsCard"],.ant-table,.ant-collapse,.ant-modal-content,.ant-modal-container,.ant-drawer-content,.ant-drawer-section,.ant-popover-inner,.ant-popover-container,.ant-select-dropdown,.ant-picker-dropdown,.ant-dropdown-menu,.ant-tooltip-inner,.ant-tooltip-container,.ant-notification-notice,.ant-message-notice-content)::after{
 border:0 !important;padding:2px;--whb-a:#45475a;--whb-b:#45475a;background:linear-gradient(125deg,var(--whb-a),var(--whb-b));
 -webkit-mask:linear-gradient(#000 0 0) content-box,linear-gradient(#000 0 0);-webkit-mask-composite:xor;mask-composite:exclude;
 transition:--whb-a .2s var(--whb-ease),--whb-b .2s var(--whb-ease);}
:root :is(.ant-card:not([class*="ModDetailsCard"]),.ant-collapse,.ant-table):hover::after{--whb-a:#89b4fa;--whb-b:#cba6f7;}
:root .ant-card:not([class*="SaveSettingsCard"]):hover{box-shadow:none !important;}
:root [class*="ModDetailsContainer"]>[class*="ModDetailsCard"]:last-child{box-shadow:inset 0 0 0 2px #45475a !important;}

/* Update dialog: no grey surround, the result list gets one clean 2px ring. */
[data-testid="mod-updates-modal"] :is(.ant-modal-content,.ant-modal-container):hover{box-shadow:none !important;}
[data-testid="mod-updates-modal"] .ant-result-body{background:transparent !important;padding:0 !important;border:0 !important;box-shadow:none !important;}
[data-testid="mod-updates-modal"] [class*="OutcomeList"]{
 --whb-a:#45475a;--whb-b:#45475a;
 border:2px solid transparent !important;border-radius:14px !important;overflow:hidden !important;
 background:linear-gradient(#181825,#181825) padding-box,linear-gradient(125deg,var(--whb-a),var(--whb-b)) border-box !important;
 transition:--whb-a .2s var(--whb-ease),--whb-b .2s var(--whb-ease) !important;}
[data-testid="mod-updates-modal"] [class*="OutcomeList"]:hover{--whb-a:#89b4fa;--whb-b:#cba6f7;}
[data-testid="mod-updates-modal"] [data-testid="mod-update-outcome"],[data-testid="mod-updates-modal"] [data-testid="mod-update-outcome"]:hover{box-shadow:none !important;background:transparent !important;}
[data-testid="mod-updates-modal"] .ant-listy-item{transition:background-color .18s var(--whb-ease) !important;}
[data-testid="mod-updates-modal"] .ant-listy-item:has([data-testid="mod-update-outcome"]):hover{background-color:#89b4fa12 !important;}

/* Right-click menu (replaces the stock WebView menu). */
:is(#wh-ctx,#wh-update-context){position:fixed;z-index:2147483647;min-width:200px;padding:5px;border:2px solid transparent;border-radius:12px;
 background:linear-gradient(#181825,#181825) padding-box,linear-gradient(125deg,#89b4fa99,#cba6f799) border-box;color:#cdd6f4;box-shadow:0 8px 24px #0008;
 font:13px/1.4 inherit;animation:whs-ctx .14s var(--whb-ease);}
@keyframes whs-ctx{from{opacity:0;transform:translateY(-3px) scale(.98)}to{opacity:1;transform:none}}
:is(#wh-ctx,#wh-update-context) button{display:flex;align-items:center;gap:24px;width:100%;margin:1px 0;border:2px solid transparent;border-radius:8px;
 background:transparent;color:inherit;padding:5px 10px;text-align:left;font:inherit;cursor:pointer;transition:background .15s var(--whb-ease);}
:is(#wh-ctx,#wh-update-context) button kbd{margin-left:auto;font:inherit;color:#7f849c;}
:is(#wh-ctx,#wh-update-context) button:not(:disabled):is(:hover,:focus-visible){outline:0;background:linear-gradient(#313244,#313244) padding-box,linear-gradient(125deg,#89b4fa,#cba6f7) border-box;}
:is(#wh-ctx,#wh-update-context) button:disabled{opacity:.4;cursor:default;}
#wh-ctx hr{border:0;height:2px;background:#313244;margin:4px 6px;}
@media (prefers-reduced-motion:reduce){:root :is(.ant-btn,.ant-modal-close,.ant-drawer-close,.ant-input-affix-wrapper,.ant-input,.ant-select,.ant-select-selector,.ant-input-number,.ant-picker,#wh-ctx){transition:none !important;animation:none !important;}:root .ant-switch::after{transition:none !important;}}

/* List view: Mocha header band with a blue to mauve rule, tinted hover and selected rows, gradient tick box. */
:root .ant-table-thead>tr>th{background:transparent !important;color:#bac2de !important;font-weight:700 !important;border-bottom:0 !important;transition:color .18s var(--whb-ease),background-color .18s var(--whb-ease) !important;}
:root .ant-table-thead>tr{background:linear-gradient(90deg,#89b4fa,#cba6f7) left bottom/100% 2px no-repeat,linear-gradient(90deg,#89b4fa14,#cba6f714) !important;}
:root .ant-table-thead>tr>th.ant-table-column-has-sorters:hover{background:#89b4fa10 !important;color:#cdd6f4 !important;}
:root .ant-table-thead>tr>th.ant-table-column-sort{color:#89b4fa !important;}
:root .ant-table-thead .ant-table-column-sorter{color:#6c7086 !important;}
:root .ant-table-thead .ant-table-column-sorter-up.active{color:#89b4fa !important;}
:root .ant-table-thead .ant-table-column-sorter-down.active{color:#cba6f7 !important;}
:root .ant-table-thead>tr>th:not(:last-child)::before{background:#45475a !important;}
:root td.ant-table-column-sort{background:transparent !important;}
:root .ant-table-tbody>tr.ant-table-row>td{background:transparent !important;transition:none !important;}
:root .ant-table-tbody>tr.ant-table-row{transition:background-color .18s var(--whb-ease);}
:root .ant-table-tbody>tr.ant-table-row:hover{background:linear-gradient(90deg,#89b4fa12,#cba6f712) !important;}
:root .ant-table-tbody>tr.ant-table-row:is([data-selected],.ant-table-row-selected){background:linear-gradient(90deg,#89b4fa,#cba6f7) left 2px top/calc(100% - 4px) 2px no-repeat,linear-gradient(90deg,#89b4fa,#cba6f7) left 2px bottom/calc(100% - 4px) 2px no-repeat,linear-gradient(#89b4fa,#89b4fa) left 2px top/2px 100% no-repeat,linear-gradient(#cba6f7,#cba6f7) right 2px top/2px 100% no-repeat,linear-gradient(90deg,#89b4fa1f,#cba6f71f) !important;}
:root .ant-table-tbody>tr.ant-table-row:is([data-selected],.ant-table-row-selected):hover{background:linear-gradient(90deg,#89b4fa,#cba6f7) left 2px top/calc(100% - 4px) 2px no-repeat,linear-gradient(90deg,#89b4fa,#cba6f7) left 2px bottom/calc(100% - 4px) 2px no-repeat,linear-gradient(#89b4fa,#89b4fa) left 2px top/2px 100% no-repeat,linear-gradient(#cba6f7,#cba6f7) right 2px top/2px 100% no-repeat,linear-gradient(90deg,#89b4fa2e,#cba6f72e) !important;}
/* Cell dividers would paint over the ring: hide them on selected rows and on the row just above one. */
:root .ant-table-tbody>tr.ant-table-row:is([data-selected],.ant-table-row-selected)>td,:root .ant-table-tbody>tr.ant-table-row:has(+tr:is([data-selected],.ant-table-row-selected))>td{border-bottom-color:transparent !important;}
:root .ant-table-tbody>tr.ant-table-row:is([data-selected],.ant-table-row-selected)>td{border-inline-end-color:#89b4fa1f !important;}
:root .ant-table-tbody>tr.ant-table-row>td:first-child{box-shadow:none !important;}
/* Tick box (antd v6 draws the box on .ant-checkbox itself) */
:root .ant-checkbox{--whb-a:#585b70;--whb-b:#585b70;--whb-f:#181825;border:2px solid transparent !important;border-radius:5px !important;
 background:linear-gradient(var(--whb-f),var(--whb-f)) padding-box,linear-gradient(125deg,var(--whb-a),var(--whb-b)) border-box !important;box-shadow:none !important;
 transition:--whb-a .2s var(--whb-ease),--whb-b .2s var(--whb-ease),--whb-f .2s var(--whb-ease) !important;}
:root :is(.ant-checkbox-wrapper:not(.ant-checkbox-wrapper-disabled):hover .ant-checkbox,.ant-checkbox:not(.ant-checkbox-disabled):hover,.ant-checkbox:has(.ant-checkbox-input:focus-visible)){--whb-a:#89b4fa;--whb-b:#cba6f7;--whb-f:#1e1e2e;}
:root :is(.ant-checkbox.ant-checkbox-checked,.ant-checkbox.ant-checkbox-indeterminate):not(.ant-checkbox-disabled){--whb-a:#89b4fa;--whb-b:#cba6f7;--whb-f:transparent;
 background:linear-gradient(125deg,#89b4fa,#cba6f7) padding-box,linear-gradient(125deg,#89b4fa,#cba6f7) border-box !important;}
:root .ant-checkbox-wrapper:not(.ant-checkbox-wrapper-disabled):hover .ant-checkbox.ant-checkbox-checked:not(.ant-checkbox-disabled),:root .ant-checkbox.ant-checkbox-checked:not(.ant-checkbox-disabled):hover{
 background:linear-gradient(125deg,#b4befe,#cba6f7) padding-box,linear-gradient(125deg,#89b4fa,#cba6f7) border-box !important;}
:root .ant-checkbox.ant-checkbox-checked::after{border-color:#11111b !important;inset-inline-start:2px !important;top:6px !important;}
:root .ant-checkbox.ant-checkbox-indeterminate::after{background:#11111b !important;}
:root .ant-checkbox-disabled{--whb-a:#45475a;--whb-b:#45475a;--whb-f:#181825;opacity:.6;}
/* "N mods selected" bar: dark Mocha surface, 2px grey edge at rest, blue to mauve when hovered. */
:root [class*="ModSelectionBar__Bar"]{--whb-a:#45475a;--whb-b:#45475a;border:2px solid transparent !important;border-radius:14px !important;
 background:linear-gradient(#181825,#181825) padding-box,linear-gradient(125deg,var(--whb-a),var(--whb-b)) border-box !important;box-shadow:0 6px 18px #11111b80 !important;
 transition:--whb-a .2s var(--whb-ease),--whb-b .2s var(--whb-ease) !important;}
:root [class*="ModSelectionBar__Bar"]:is(:hover,:focus-within){--whb-a:#89b4fa;--whb-b:#cba6f7;}
:root [class*="ModSelectionBar__Bar"]>span:first-child{color:#89b4fa !important;font-weight:700 !important;}
/* Tooltips: same look as the right-click menu (dark Mocha, 2px blue to mauve edge, no arrow). */
:root .ant-tooltip .ant-tooltip-arrow{display:none !important;}
:root .ant-tooltip .ant-tooltip-container,:root .ant-tooltip .ant-tooltip-inner{background:#181825 !important;color:#cdd6f4 !important;border-radius:12px !important;padding:7px 11px !important;
 font-size:13px !important;line-height:1.45 !important;box-shadow:0 8px 24px #0008 !important;}
:root .ant-tooltip :is(.ant-tooltip-container,.ant-tooltip-inner)::after{--whb-a:#89b4fa99;--whb-b:#cba6f799;border-radius:inherit !important;}
/* First row selected: the header rule would sit on the ring's top edge and double it, so the header drops its rule. */
:root .ant-table:has(.ant-table-tbody>tr:nth-child(1 of .ant-table-row):is([data-selected],.ant-table-row-selected)) .ant-table-thead>tr{background:linear-gradient(90deg,#89b4fa14,#cba6f714) !important;}
/* Ribbons sit above the card's decorative ring. */
:root .ant-ribbon{z-index:3 !important;}
:root .ant-ribbon-wrapper{overflow:visible !important;}
/* Move the hit area with the thumb; keep the rounded gradient clear of the edge. */
:root :is(.wh-cscroll-track,.wh-cscroll-thumb).wh-cscroll-v{translate:-6px 0;}
:root .wh-cscroll-thumb{background:linear-gradient(180deg,#89b4fa,#cba6f7) !important;border-radius:999px !important;}
:root .wh-cscroll-thumb.wh-cscroll-h{background:linear-gradient(90deg,#89b4fa,#cba6f7) !important;}
:root .wh-cscroll-host::-webkit-scrollbar-thumb{background:linear-gradient(180deg,#89b4fa,#cba6f7) content-box !important;}
:root [class*="SaveSettingsCard"]{
 background:#181825 !important;background-image:none !important;backdrop-filter:none !important;
 z-index:3 !important;isolation:isolate;box-shadow:none !important;
}
:root [class*="SaveSettingsCard"]:is(:hover,:focus-within)::after{--whb-a:#89b4fa;--whb-b:#cba6f7;}
:root [class*="SaveSettingsCard"] .ant-segmented{background:#11111b !important;border:2px solid #45475a !important;padding:2px !important;}
:root [class*="SaveSettingsCard"] :is(.ant-segmented-item-selected,.ant-segmented-thumb){background:#313244 !important;color:#89b4fa !important;box-shadow:none !important;}
:root [class*="SaveSettingsCard"] .ant-segmented-item:not(.ant-segmented-item-selected){color:#bac2de !important;}
:root [class*="SaveSettingsCard"] .ant-segmented:hover{border-color:transparent !important;background:linear-gradient(#11111b,#11111b) padding-box,linear-gradient(125deg,#89b4fa,#cba6f7) border-box !important;}
:root [class*="CreateNewModButton__ButtonContainer"]:has([data-testid="create-new-mod"]){display:block !important;position:fixed !important;left:var(--wh-create-x,-999px) !important;top:var(--wh-create-y,-999px) !important;width:var(--wh-create-w,1px) !important;height:var(--wh-create-h,1px) !important;margin:0 !important;padding:0 !important;opacity:0 !important;pointer-events:none !important;z-index:-1 !important;}
:root [class*="CreateNewModButton__ButtonContainer"] [data-testid="create-new-mod"]{width:100% !important;height:100% !important;min-width:0 !important;padding:0 !important;margin:0 !important;}
:root #wh-header-create{height:32px !important;position:relative !important;inset:auto !important;margin:0 !important;padding:4px 12px !important;white-space:nowrap;}
:root #wh-header-create svg{width:14px;height:14px;margin-right:0 !important;}
/* 2.1.5: mod id tag is a dark chip with a 2px edge, grey at rest, blue to mauve on hover. */
:root [class*="CardTitleModId"]{background:#181825 !important;color:#a6adc8 !important;border:2px solid #45475a !important;border-radius:999px !important;padding:0 9px !important;line-height:20px !important;transition:border-color .15s,color .15s;}
:root [class*="CardTitleModId"]:hover{color:#cdd6f4 !important;border-color:transparent !important;background:linear-gradient(#181825,#181825) padding-box,linear-gradient(125deg,#89b4fa,#cba6f7) border-box !important;}
/* Save dock: 12px gap from the window edges, still clear of the panel scrollbar. */
:root [class*="SaveSettingsCard"]{margin-inline:12px !important;}
/* Visual / Textual switch: one surface for both halves, a full-height divider, selected half in blue text, hover darkens the whole half. */
:root [class*="SaveSettingsCard"] .ant-segmented{background:#1e1e2e !important;border:2px solid #45475a !important;padding:0 !important;border-radius:999px !important;overflow:hidden !important;}
:root [class*="SaveSettingsCard"] .ant-segmented:hover{border-color:transparent !important;background:linear-gradient(#1e1e2e,#1e1e2e) padding-box,linear-gradient(125deg,#89b4fa,#cba6f7) border-box !important;}
:root [class*="SaveSettingsCard"] .ant-segmented-group{align-items:stretch !important;}
:root [class*="SaveSettingsCard"] .ant-segmented-thumb{display:none !important;}
:root [class*="SaveSettingsCard"] .ant-segmented-item{background:transparent !important;border-radius:0 !important;box-shadow:none !important;color:#a6adc8 !important;transition:background-color .15s,color .15s;}
:root [class*="SaveSettingsCard"] .ant-segmented-item::after{display:none !important;}
:root [class*="SaveSettingsCard"] .ant-segmented-item+.ant-segmented-item{border-inline-start:2px solid #45475a !important;}
:root [class*="SaveSettingsCard"] .ant-segmented:hover .ant-segmented-item+.ant-segmented-item{border-inline-start-color:#6c7086 !important;}
:root [class*="SaveSettingsCard"] .ant-segmented-item-selected{color:#89b4fa !important;font-weight:700 !important;}
:root [class*="SaveSettingsCard"] .ant-segmented-item:hover{background:#11111b !important;color:#cdd6f4 !important;}
:root [class*="SaveSettingsCard"] .ant-segmented-item-selected:hover{color:#89b4fa !important;}
:root [class*="SaveSettingsCard"] .ant-segmented-item-label{min-height:28px !important;line-height:28px !important;padding:0 14px !important;}
/* Expanded settings (F11): an opaque frosted page, content centred, dock clear of the scrollbar. */
:root #root:has(form[class*="SettingsForm"] button[aria-label="Collapse"]){visibility:hidden !important;}
:root form[class*="SettingsForm"]:has(button[aria-label="Collapse"]){visibility:visible !important;background:transparent !important;backdrop-filter:none !important;padding:0 max(28px,calc((100% - 1480px)/2)) 32px !important;}
:root form[class*="SettingsForm"]:has(button[aria-label="Collapse"]) [class*="SaveSettingsCard"]{margin-inline:12px !important;margin-top:0 !important;top:12px !important;}
/* Native title tooltips are replaced by this one, same look as the antd tooltips and the right-click menu. */
:root #wh-tip{position:fixed;z-index:2147483000;pointer-events:none;max-width:420px;padding:6px 11px;border-radius:12px;font-size:13px;line-height:1.45;color:#cdd6f4;white-space:pre-line;
 border:2px solid transparent;background:linear-gradient(#181825,#181825) padding-box,linear-gradient(125deg,#89b4fa99,#cba6f799) border-box;box-shadow:0 8px 24px #0008;opacity:0;transition:opacity .12s;}
:root #wh-tip.on{opacity:1;}
/* 2.2.4: collapse arrow keeps its small dark box inside the row. The unsaved
   state bar paints at -18px, 3px wide (ModDetailsSettingsView__SettingsListItem
   ::before, measured in the app bundle and on screen); the old margin -18px
   hung this box exactly over it. Grey 2px edge, blue to mauve on hover. */
:root [data-testid="mod-setting-collapse"]{width:20px !important;height:20px !important;min-width:20px !important;padding:0 !important;margin:0 8px 0 0 !important;display:inline-flex !important;align-items:center !important;justify-content:center !important;background:#181825 !important;border:2px solid #45475a !important;border-radius:999px !important;color:#a6adc8 !important;box-shadow:none !important;transition:border-color .15s,color .15s;}
:root [data-testid="mod-setting-collapse"] svg{width:10px !important;height:10px !important;display:block !important;margin:0 !important;transition:transform .2s ease;}
:root [data-testid="mod-setting-collapse"]:hover,:root [data-testid="mod-setting-collapse"]:focus-visible{color:#cdd6f4 !important;border-color:transparent !important;background:linear-gradient(#181825,#181825) padding-box,linear-gradient(125deg,#89b4fa,#cba6f7) border-box !important;}
/* "5 settings" badge on a collapsed section: dark chip, grey edge, blue to mauve edge on hover. */
:root [data-testid="mod-setting-summary"]{background:#181825 !important;color:#a6adc8 !important;border:2px solid #45475a !important;border-radius:999px !important;padding:0 10px !important;line-height:20px !important;font-size:12px !important;transition:border-color .15s,color .15s;}
:root [data-testid="mod-setting-summary"]:hover{color:#cdd6f4 !important;border-color:transparent !important;background:linear-gradient(#181825,#181825) padding-box,linear-gradient(125deg,#89b4fa,#cba6f7) border-box !important;}
/* Mod page tabs: one pill dock like the Visual / Textual switch, 2px dividers, no underline or grey rule. */
:root .ant-tabs-top>.ant-tabs-nav::before{display:none !important;border:0 !important;}
:root .ant-tabs-top>.ant-tabs-nav .ant-tabs-ink-bar{display:none !important;}
:root .ant-tabs-top>.ant-tabs-nav{margin-bottom:20px !important;}
:root .ant-tabs-top>.ant-tabs-nav .ant-tabs-nav-list{background:#1e1e2e !important;border:2px solid #45475a !important;border-radius:999px !important;overflow:hidden !important;transition:border-color .15s;}
:root .ant-tabs-top>.ant-tabs-nav .ant-tabs-nav-list:hover{border-color:transparent !important;background:linear-gradient(#1e1e2e,#1e1e2e) padding-box,linear-gradient(125deg,#89b4fa,#cba6f7) border-box !important;}
:root .ant-tabs-top>.ant-tabs-nav .ant-tabs-tab{margin:0 !important;padding:0 18px !important;height:36px !important;font-size:14px !important;color:#a6adc8 !important;background:transparent !important;transition:background-color .15s,color .15s;}
:root .ant-tabs-top>.ant-tabs-nav .ant-tabs-tab+.ant-tabs-tab{border-inline-start:2px solid #45475a !important;}
:root .ant-tabs-top>.ant-tabs-nav .ant-tabs-nav-list:hover .ant-tabs-tab+.ant-tabs-tab{border-inline-start-color:#6c7086 !important;}
:root .ant-tabs-top>.ant-tabs-nav .ant-tabs-tab .ant-tabs-tab-btn{color:inherit !important;}
:root .ant-tabs-top>.ant-tabs-nav .ant-tabs-tab:hover{background:linear-gradient(125deg,#89b4fa33,#cba6f733) !important;color:#cdd6f4 !important;}
:root .ant-tabs-top>.ant-tabs-nav .ant-tabs-tab-active{background:#181825 !important;}
:root .ant-tabs-top>.ant-tabs-nav .ant-tabs-tab-active .ant-tabs-tab-btn{color:#89b4fa !important;font-weight:700 !important;text-shadow:none !important;}
:root .ant-tabs-top>.ant-tabs-nav .ant-tabs-tab-active:hover{background:linear-gradient(125deg,#89b4fa33,#cba6f733) !important;}
/* 2.1.7: split buttons (Load + menu dots) keep the same 8px gap as the next button, all on one centre line. */
:root .ant-space-compact>.ant-btn+.ant-btn{margin-inline-start:8px !important;}
:root .ant-space-compact>.ant-btn:has(+.ant-btn){margin-inline-end:0 !important;}
:root .ant-space-compact:has(>.ant-btn+.ant-btn){align-items:center !important;}
/* Dialogs (Installing, Compiling, update, confirm): grey 2px frame at rest, blue to mauve on hover. */
:root :is(.ant-modal-content,.ant-modal-container):hover::after{--whb-a:#89b4fa;--whb-b:#cba6f7;}
:root :is(.ant-modal-content,.ant-modal-container):hover{box-shadow:0 12px 32px #0009 !important;}
/* Drop-down lists and menus: same grey frame at rest, blue to mauve on hover. */
:root :is(.ant-select-dropdown,.ant-picker-dropdown,.ant-dropdown-menu,.ant-popover-container,.ant-popover-inner):hover::after{--whb-a:#89b4fa;--whb-b:#cba6f7;}
/* Dialogs: frosted glass. Backdrop blur cannot read through this see-through window, so the page itself blurs while a dialog is open. Dialog is Mocha mantle, inner list one step lighter. */
body:has(.ant-modal-wrap:not([style*="display: none"]) .ant-modal)>#root{filter:blur(12px) saturate(120%) !important;}
body>#root{transition:filter .2s ease;}
:root .ant-modal-mask{backdrop-filter:none !important;background-color:rgba(17,17,27,.35) !important;}
:root :is(.ant-modal-content,.ant-modal-container){backdrop-filter:none !important;background-color:rgba(24,24,37,.86) !important;}
:root [data-testid="mod-updates-modal"] [class*="OutcomeList"]{background:linear-gradient(#232435,#232435) padding-box,linear-gradient(125deg,var(--whb-a),var(--whb-b)) border-box !important;}
:root [data-testid="mod-updates-modal"] .ant-progress-inner{background:#11111b !important;}
/* 2.1.7: mod page header: no grey rule under the tab pill. */
:root .ant-card-head:has(>.ant-card-head-wrapper .ant-tabs),:root .ant-card-head:has(.ant-card-head-tabs){border-bottom:0 !important;box-shadow:none !important;}
:root .ant-card-head-tabs>.ant-tabs-nav::before,:root .ant-card-head-tabs .ant-tabs-ink-bar{display:none !important;border:0 !important;}
/* 2.1.12: version chips: hover ring via ::after mask, zero layout shift; remove-confirm solid card with page blur behind. */
/* 2.1.11: version chips: mantle fill, 2px grey ring, chosen one surface0, blue to mauve on hover. */
:root [class*="ModVersionRadioGroup"] .ant-radio-button-wrapper{position:relative !important;background:#181825 !important;color:#a6adc8 !important;border:0 !important;box-shadow:inset 0 0 0 2px #45475a !important;border-radius:999px !important;margin-inline-end:6px !important;transition:box-shadow .15s ease,color .15s ease !important;}
:root [class*="ModVersionRadioGroup"] .ant-radio-button-wrapper::before{display:none !important;}
:root [class*="ModVersionRadioGroup"] .ant-radio-button-wrapper-checked{background:#313244 !important;color:#89b4fa !important;box-shadow:inset 0 0 0 2px #89b4fa !important;}
:root [class*="ModVersionRadioGroup"] .ant-radio-button-wrapper:hover{color:#cdd6f4 !important;background:#181825 !important;box-shadow:none !important;}
:root [class*="ModVersionRadioGroup"] .ant-radio-button-wrapper::after{content:"" !important;position:absolute !important;inset:0 !important;border-radius:inherit !important;padding:2px !important;background:linear-gradient(125deg,#89b4fa,#cba6f7) !important;-webkit-mask:linear-gradient(#000 0 0) content-box,linear-gradient(#000 0 0) !important;-webkit-mask-composite:xor !important;mask-composite:exclude !important;opacity:0 !important;transition:opacity .15s ease !important;pointer-events:none !important;display:block !important;box-sizing:border-box !important;}
:root [class*="ModVersionRadioGroup"] .ant-radio-button-wrapper:hover::after{opacity:1 !important;}
/* 2.1.7: open menus (sort, selects) wear the blue to mauve ring the whole time they are open. */
:root :is(.ant-select-dropdown,.ant-dropdown-menu,.ant-picker-dropdown)::after{--whb-a:#89b4fa !important;--whb-b:#cba6f7 !important;}
/* 2.1.7: dialogs: stronger glass so nothing behind reads through. */
body:has(.ant-modal-wrap:not([style*="display: none"]) .ant-modal)>#root{filter:blur(22px) saturate(115%) brightness(.8) !important;}
:root .ant-modal-mask{background-color:rgba(17,17,27,.5) !important;}
:root :is(.ant-modal-content,.ant-modal-container){background-color:rgba(24,24,37,.94) !important;}
:root :is(.ant-modal-content,.ant-modal-container).wh-hot::after{--whb-a:#89b4fa;--whb-b:#cba6f7;}
/* 2.1.7: progress bars: blue to mauve fill in a crust track with a 2px grey ring. */
:root :is(.ant-progress-bg,.ant-progress-track:not(.ant-progress-track-success)){background:linear-gradient(100deg,#89b4fa,#b4befe 60%,#cba6f7) !important;}
:root .ant-progress-inner,:root .ant-progress-rail{background:#11111b !important;box-shadow:inset 0 0 0 2px #45475a !important;padding:2px !important;box-sizing:content-box !important;}
/* 2.1.7: Create a new mod confirm: glass card, grey ring, blue to mauve on hover. */
:root .ant-popconfirm :is(.ant-popover-inner,.ant-popover-container){background-color:rgba(24,24,37,.86) !important;backdrop-filter:none !important;border-radius:14px !important;padding:16px 18px !important;}
body:has(.ant-popconfirm:not(.ant-popover-hidden))>#root{filter:blur(14px) saturate(115%) brightness(.8) !important;transition:filter .18s ease;}
:root .ant-popconfirm:hover :is(.ant-popover-inner,.ant-popover-container)::after{--whb-a:#89b4fa;--whb-b:#cba6f7;}
:root .ant-popconfirm .ant-popover-arrow{display:none !important;}
:root .ant-popconfirm :is(.ant-popconfirm-title,.ant-popconfirm-description,.ant-checkbox-label,.ant-checkbox-wrapper){color:#cdd6f4 !important;}
:root .ant-popconfirm .ant-checkbox-inner{background:#11111b !important;border:2px solid #45475a !important;border-radius:5px !important;}
:root .ant-popconfirm .ant-checkbox-checked .ant-checkbox-inner{background:linear-gradient(125deg,#89b4fa,#cba6f7) !important;border-color:transparent !important;}
:root .ant-popconfirm .ant-popconfirm-buttons{display:flex !important;gap:8px !important;justify-content:flex-end !important;margin-top:12px !important;}
/* 2.1.11: Reset to default pills and number arrows: mantle fill, 2px grey ring, blue to mauve on hover. Modified-setting bars are blue to mauve. */
:root [data-testid="mod-setting-reset"].ant-btn{height:24px !important;padding:0 9px !important;border-radius:999px !important;border:2px solid transparent !important;background:linear-gradient(#181825,#181825) padding-box,linear-gradient(#45475a,#45475a) border-box !important;color:#89b4fa !important;box-shadow:none !important;transition:background .15s ease,color .15s ease !important;}
:root [data-testid="mod-setting-reset"].ant-btn:hover,:root [data-testid="mod-setting-reset"].ant-btn:focus-visible{background:linear-gradient(#1e1e2e,#1e1e2e) padding-box,linear-gradient(125deg,#89b4fa,#cba6f7) border-box !important;color:#b4befe !important;}
:root [data-testid="mod-setting-reset"].ant-btn:active{background:linear-gradient(#313244,#313244) padding-box,linear-gradient(125deg,#89b4fa,#cba6f7) border-box !important;}
:root .ant-input-number .ant-input-number-actions{top:3px !important;bottom:3px !important;right:4px !important;height:auto !important;width:20px !important;border-radius:10px !important;overflow:hidden !important;border:2px solid transparent !important;background:linear-gradient(#181825,#181825) padding-box,linear-gradient(#45475a,#45475a) border-box !important;box-shadow:none !important;}
:root .ant-input-number .ant-input-number-actions:hover{background:linear-gradient(#1e1e2e,#1e1e2e) padding-box,linear-gradient(160deg,#89b4fa,#cba6f7) border-box !important;}
:root .ant-input-number .ant-input-number-action{border:0 !important;border-radius:0 !important;color:#a6adc8 !important;background:transparent !important;font-size:9px !important;transition:background .12s ease,color .12s ease !important;}
:root .ant-input-number .ant-input-number-action:hover{color:#cdd6f4 !important;background:rgba(137,180,250,.16) !important;}
:root .ant-input-number .ant-input-number-action:active{background:rgba(203,166,247,.24) !important;}
:root .ant-input-number .ant-input-number-action-disabled,:root .ant-input-number .ant-input-number-action[aria-disabled="true"]{color:#585b70 !important;background:transparent !important;}
:root [class*="ModDetailsSettingsView__SettingsListItem-"]::before{background:linear-gradient(180deg,#89b4fa,#cba6f7) !important;}
/* 2.1.9: every segmented switch (Theme: Dark, Light, System) is one pill dock like the mod tabs: base fill, 2px dividers, grey edge, blue to mauve on hover, chosen item blue on mantle. */
:root .ant-segmented:not([class*="SaveSettingsCard"] *){background:#1e1e2e !important;border:2px solid #45475a !important;padding:0 !important;border-radius:999px !important;overflow:hidden !important;box-shadow:none !important;transition:border-color .15s;}
:root .ant-segmented:not([class*="SaveSettingsCard"] *):hover{border-color:transparent !important;background:linear-gradient(#1e1e2e,#1e1e2e) padding-box,linear-gradient(125deg,#89b4fa,#cba6f7) border-box !important;}
:root .ant-segmented:not([class*="SaveSettingsCard"] *) .ant-segmented-group{align-items:stretch !important;}
:root .ant-segmented:not([class*="SaveSettingsCard"] *) .ant-segmented-thumb{display:none !important;}
:root .ant-segmented:not([class*="SaveSettingsCard"] *) .ant-segmented-item{margin:0 !important;background:transparent !important;border-radius:0 !important;box-shadow:none !important;color:#a6adc8 !important;transition:background .15s,color .15s;}
:root .ant-segmented:not([class*="SaveSettingsCard"] *) .ant-segmented-item::after{display:none !important;}
:root .ant-segmented:not([class*="SaveSettingsCard"] *) .ant-segmented-item+.ant-segmented-item{border-inline-start:2px solid #45475a !important;}
:root .ant-segmented:not([class*="SaveSettingsCard"] *):hover .ant-segmented-item+.ant-segmented-item{border-inline-start-color:#6c7086 !important;}
:root .ant-segmented:not([class*="SaveSettingsCard"] *) .ant-segmented-item:hover{background:linear-gradient(125deg,#89b4fa33,#cba6f733) !important;color:#cdd6f4 !important;}
:root .ant-segmented:not([class*="SaveSettingsCard"] *) .ant-segmented-item-selected,:root .ant-segmented:not([class*="SaveSettingsCard"] *) .ant-segmented-item-selected:hover{background:#181825 !important;color:#89b4fa !important;font-weight:700 !important;}
:root .ant-segmented:not([class*="SaveSettingsCard"] *) .ant-segmented-item-selected:hover{background:linear-gradient(125deg,#89b4fa33,#cba6f733) !important;}
:root .ant-segmented:not([class*="SaveSettingsCard"] *) .ant-segmented-item-label{min-height:32px !important;line-height:32px !important;padding:0 16px !important;}
/* 2.1.10: the open Advanced settings box is one glass card: its body takes the header's Mocha glass instead of antd's flat near-black, with one quiet line under the header. The header Create button matches the other docks: same padding, 18px icon, short label. */
:root .ant-collapse>.ant-collapse-item>.ant-collapse-panel{background:rgba(24,24,37,0.400) !important;border:0 !important;border-top:1px solid rgba(69,71,90,0.700) !important;border-radius:0 !important;}
:root #wh-header-create{padding:0 15px !important;}
:root #wh-header-create svg{width:18px !important;height:18px !important;}
:root #wh-header-create .ant-btn-icon{display:inline-flex;width:18px;height:18px;align-items:center;justify-content:center;}
/* 2.2.10: list items (per-program lists and the like). Both arrows are the same round dark bubble, chevron 10px in a 16px inside so it sits on whole pixels.
   The drag handle is a matching dark pill, and the item chip matches the "5 settings" chip. Grey 2px edge at rest, blue to mauve on hover. */
:root [data-testid="mod-setting-collapse"] svg,:root [data-testid="mod-setting-array-item-collapse"] svg{width:10px !important;height:10px !important;display:block !important;margin:0 !important;flex:none !important;}
:root [class*="ModDetailsSettingsView__ArraySettingsItemWrapper"]{--whui-settings-array-grip-offset:27px !important;--whui-settings-array-handle-width:14px !important;}
:root [data-testid="mod-setting-array-item-collapse"]{width:20px !important;min-width:20px !important;height:20px !important;top:6px !important;margin-inline-end:4px !important;padding:0 !important;display:inline-flex !important;align-items:center !important;justify-content:center !important;background:#181825 !important;border:2px solid #45475a !important;border-radius:999px !important;color:#a6adc8 !important;box-shadow:none !important;transition:opacity 120ms ease-out,border-color .15s,color .15s !important;}
:root [data-testid="mod-setting-array-item-collapse"]:hover,:root [data-testid="mod-setting-array-item-collapse"]:focus-visible{color:#cdd6f4 !important;border-color:transparent !important;background:linear-gradient(#181825,#181825) padding-box,linear-gradient(125deg,#89b4fa,#cba6f7) border-box !important;}
:root [class*="ModDetailsSettingsView__ArraySettingsItemDragHandle"],:root [class*="ModDetailsSettingsView__ArrayItemDragBadge"]{background:#181825 !important;border:2px solid #45475a !important;border-radius:999px !important;color:#a6adc8 !important;box-shadow:none !important;}
:root [class*="ModDetailsSettingsView__ArraySettingsItemDragHandle"]{top:6px !important;height:20px !important;box-sizing:border-box !important;transition:opacity 120ms ease-out,border-color .15s,color .15s !important;}
:root [class*="ModDetailsSettingsView__ArraySettingsItemDragHandle"] svg{height:10px !important;width:auto !important;display:block !important;}
:root [class*="ModDetailsSettingsView__ArraySettingsItemDragHandle"]:hover,:root [class*="ModDetailsSettingsView__ArraySettingsItemDragHandle"]:active,:root [class*="ModDetailsSettingsView__ArrayItemDragBadge"]{color:#cdd6f4 !important;border-color:transparent !important;background:linear-gradient(#181825,#181825) padding-box,linear-gradient(125deg,#89b4fa,#cba6f7) border-box !important;}
:root [class*="ModDetailsSettingsView__SettingSummary"]{background:#181825 !important;color:#a6adc8 !important;border:2px solid #45475a !important;border-radius:999px !important;padding:0 10px !important;line-height:20px !important;font-size:12px !important;transition:border-color .15s,color .15s;}
:root [class*="ModDetailsSettingsView__SettingSummary"]:hover,:root [data-testid="mod-setting-array-item-summary"]:hover [class*="ModDetailsSettingsView__SettingSummary"]{color:#cdd6f4 !important;border-color:transparent !important;background:linear-gradient(#181825,#181825) padding-box,linear-gradient(125deg,#89b4fa,#cba6f7) border-box !important;}
:root [class*="ModDetailsSettingsView__ArraySettingsItemWrapper"],:root [class*="ModDetailsSettingsView__ArraySettingsFooter"]{padding-inline-start:24px !important;}
/* 2.2.12: drop-downs wear the dialog glass. While a menu is open the page frosts behind
   it — the one real blur this WebView can do (measured 2026-11-06: a filtered element
   cannot read the page under it) — and the menu takes the frosted fill instead of a flat box. */
body:has(.ant-select-dropdown:not(.ant-select-dropdown-hidden)),body:has(.ant-dropdown:not(.ant-dropdown-hidden)),body:has(.ant-picker-dropdown:not(.ant-picker-dropdown-hidden))>#root{filter:blur(16px) saturate(120%) brightness(.85) !important;}
:root :is(.ant-select-dropdown,.ant-picker-dropdown,.ant-dropdown-menu){background-color:rgba(24,24,37,.9) !important;backdrop-filter:none !important;}
/* 2.2.12: header nav buttons rest on Mocha base instead of mantle, so they stop reading
   as black chips against the glass page (owner, 2026-11-20: like base, about rgb 30,30,46). */
:root :is([data-testid="nav-home"],[data-testid="nav-explore"],[data-testid="nav-settings"],[data-testid="nav-about"],#wh-header-create):not(.ant-btn-primary){--whb-f:#1e1e2e !important;}
)WHB";
    return css;
}

static std::string BuildInjectJs(const Settings& s) {
    std::string css = BuildCss(s);
    std::string js;
    // This runs when the page's document is created, before Windhawk's own
    // scripts and before the first paint, so the stylesheet goes in at once.
    // The page helpers need the body and the app root, so they wait for the
    // parser to finish.
    js += "(function(){";
    js += "if(location.hostname!=='tauri.localhost')return 'skip';";
    js += "var css=\"" + JsonEscape(css) + "\";";
    js += "var st=document.getElementById('wh-styler-style');";
    js += "if(!st){st=document.createElement('style');st.id='wh-styler-style';}";
    js += "if(st.textContent!==css)st.textContent=css;";
    // Keep the sheet last in <head>, as the old after-load push did, so it wins
    // ties with Windhawk's own CSS file that the parser adds after it.
    js += "var place=function(){var h=document.head;if(h){if(h.lastElementChild!==st)h.appendChild(st);return true;}"
          "if(document.documentElement&&!st.parentNode)document.documentElement.appendChild(st);return false;};";
    js += "if(!place()&&!window.whStyleWatch){window.whStyleWatch=new MutationObserver(function(){if(document.head){place();window.whStyleWatch.disconnect();}});"
          "window.whStyleWatch.observe(document,{childList:true,subtree:true});}";
    js += "var rest=function(){place();if(!document.body||!document.getElementById('root'))return;";
    {
        // Hidden SVG with the shared gradient. display:none would stop
        // Chromium from painting the gradient, so it is sized to zero instead.
        std::string defs;
        if (s.headerGradient) {
            defs = "<defs><linearGradient id='wh-enh-grad' x1='0' y1='0' x2='1' y2='1'><stop offset='0' stop-color='" +
                   RgbToCss(s.gradientStart) + "'/><stop offset='1' stop-color='" + RgbToCss(s.gradientEnd) + "'/></linearGradient></defs>";
        }
        js += "var dg=document.getElementById('wh-enh-defs');var dh=\"" + JsonEscape(defs) + "\";";
        js += "if(!dh){if(dg)dg.remove();}else{if(!dg){dg=document.createElementNS('http://www.w3.org/2000/svg','svg');dg.id='wh-enh-defs';"
              "dg.setAttribute('aria-hidden','true');dg.setAttribute('style','position:absolute;width:0;height:0;overflow:hidden;pointer-events:none');"
              "(document.body||document.documentElement).appendChild(dg);}if(dg.getAttribute('data-k')!==dh){dg.innerHTML=dh;dg.setAttribute('data-k',dh);}}";
    }
    js += R"WHB((()=>{
if(window.whCtxInstalled)return;window.whCtxInstalled=true;
let menu=null,origin=null;
const close=()=>{if(menu){menu.remove();menu=null;}};
const copy=t=>navigator.clipboard.writeText(t).catch(()=>{const a=document.createElement('textarea');a.value=t;document.body.appendChild(a);a.select();document.execCommand('copy');a.remove();});
window.addEventListener('contextmenu',e=>{
 if(e.defaultPrevented||e.target.closest('.monaco-editor'))return;
 e.preventDefault();close();
 origin=document.activeElement;
 const sel=window.getSelection().toString();
 const ed=e.target.closest('input:not([type=checkbox]):not([type=radio]):not([type=range]),textarea,[contenteditable=""],[contenteditable=true]');
 const link=e.target.closest('a[href]');
 const upd=e.target.closest('[data-testid="mod-updates-modal"]');
 menu=document.createElement('div');menu.id='wh-ctx';menu.setAttribute('role','menu');
 const add=(label,key,action,disabled)=>{const b=document.createElement('button');b.type='button';b.setAttribute('role','menuitem');b.disabled=!!disabled;
  b.append(label);if(key){const k=document.createElement('kbd');k.textContent=key;b.appendChild(k);}
  b.onclick=()=>{close();if(origin&&origin.isConnected)origin.focus({preventScroll:true});action();};menu.appendChild(b);};
 const sep=()=>{if(menu.lastChild&&menu.lastChild.tagName!=='HR')menu.appendChild(document.createElement('hr'));};
 if(ed){
  const ro=ed.readOnly||ed.disabled;
  const hasSel=ed.selectionStart!==undefined&&ed.selectionStart!==null?ed.selectionStart!==ed.selectionEnd:!!sel;
  ed.focus({preventScroll:true});origin=ed;
  add('Cut','Ctrl+X',()=>document.execCommand('cut'),ro||!hasSel);
  add('Copy','Ctrl+C',()=>document.execCommand('copy'),!hasSel);
  add('Paste','Ctrl+V',()=>navigator.clipboard.readText().then(t=>{ed.focus();document.execCommand('insertText',false,t);}).catch(()=>{}),ro);
  sep();add('Select all','Ctrl+A',()=>{ed.focus();ed.select?ed.select():document.execCommand('selectAll');});
 }else{
  const nav=window.navigation;
  add('Back','Alt+Left arrow',()=>history.back(),nav?!nav.canGoBack:history.length<2);
  add('Forward','Alt+Right arrow',()=>history.forward(),nav?!nav.canGoForward:false);
  add('Reload','F5',()=>location.reload());
  sep();
  if(link)add('Copy link','',()=>copy(link.href));
  add('Copy','Ctrl+C',()=>copy(sel),!sel);
  if(upd){add('Copy update details','',()=>copy(upd.innerText));
   add('Select all','Ctrl+A',()=>{const r=document.createRange();r.selectNodeContents(upd.querySelector('.ant-modal-body')||upd);const s=window.getSelection();s.removeAllRanges();s.addRange(r);});}
 }
 if(menu.lastChild&&menu.lastChild.tagName==='HR')menu.lastChild.remove();
 document.body.appendChild(menu);
 let x=e.clientX,y=e.clientY;
 if(!x&&!y){const r=e.target.getBoundingClientRect();x=r.left+8;y=r.bottom;}
 menu.style.left=Math.max(4,Math.min(x,innerWidth-menu.offsetWidth-8))+'px';
 menu.style.top=Math.max(4,Math.min(y,innerHeight-menu.offsetHeight-8))+'px';
 if(e.button!==2){const f=menu.querySelector('button:not(:disabled)');if(f)f.focus({preventScroll:true});}
});
document.addEventListener('pointerdown',e=>{if(menu&&!menu.contains(e.target))close();},true);
document.addEventListener('keydown',e=>{if(!menu)return;
 if(e.key==='Escape'){e.preventDefault();e.stopPropagation();close();if(origin&&origin.isConnected)origin.focus({preventScroll:true});}
 else if(e.key==='ArrowDown'||e.key==='ArrowUp'){e.preventDefault();const bs=[...menu.querySelectorAll('button:not(:disabled)')];if(!bs.length)return;const i=bs.indexOf(document.activeElement);bs[i<0?(e.key==='ArrowDown'?0:bs.length-1):(i+(e.key==='ArrowDown'?1:bs.length-1))%bs.length].focus();}
 else if(e.key==='Tab')close();},true);
window.addEventListener('blur',close);window.addEventListener('resize',close);document.addEventListener('scroll',close,true);
})();)WHB";
    js += R"WHH((()=>{if(window.whModalHot)return;window.whModalHot=1;let x=-1,y=-1;
 const upd=()=>document.querySelectorAll('.ant-modal-content,.ant-modal-container').forEach(c=>{const r=c.getBoundingClientRect();c.classList.toggle('wh-hot',x>=r.left&&x<=r.right&&y>=r.top&&y<=r.bottom);});
 addEventListener('pointermove',e=>{x=e.clientX;y=e.clientY;upd();},{passive:true,capture:true});
 document.addEventListener('pointerleave',()=>{x=y=-1;upd();});
 // A dialog that opens under a still cursor gets no :hover, so check the last pointer spot when it appears.
 new MutationObserver(()=>{requestAnimationFrame(upd);setTimeout(upd,250);}).observe(document.body,{childList:true});
})();
)WHH";
    js += R"WHH((()=>{
 const install=()=>{
  const original=document.querySelector('[data-testid="create-new-mod"]');
  const settings=document.querySelector('[data-testid="nav-settings"]');
  const anchor=settings?.closest('.ant-badge');
  if(!original||!anchor||document.getElementById('wh-header-create'))return;
  // Keep React's original node in place so route changes can unmount it safely.
  const button=original.cloneNode(true);
  button.id='wh-header-create';button.removeAttribute('data-testid');
  button.className=document.querySelector('[data-testid="nav-explore"]').className;
  // Park the hidden stock button under this copy so its confirm opens here, and stop this click
  // reaching antd's outside-click check, which closed the confirm the moment it opened.
  // Short label so this dock matches Home, Explore, Settings and About; the full name stays as the tooltip.
  const label=[...button.children].find(c=>c.tagName==='SPAN'&&!c.classList.contains('ant-btn-icon')&&c.textContent.trim());
  if(label)label.textContent='New mod';
  button.setAttribute('title','Create a new mod');button.setAttribute('aria-label','Create a new mod');
  let busy=0;
  button.onclick=async e=>{e.preventDefault();e.stopPropagation();if(busy)return;busy=1;setTimeout(()=>busy=0,1500);
   const find=()=>document.querySelector('[data-testid="create-new-mod"]');let stock=find();
   // Settings and About have no stock Create button, so go Home first and wait for it.
   if(!stock){document.querySelector('[data-testid="nav-home"]')?.click();for(let i=0;i<40&&!(stock=find());i++)await new Promise(r=>setTimeout(r,50));if(!stock)return;}
   const r=button.getBoundingClientRect(),s=document.documentElement.style;
   s.setProperty('--wh-create-x',r.left+'px');s.setProperty('--wh-create-y',r.top+'px');s.setProperty('--wh-create-w',r.width+'px');s.setProperty('--wh-create-h',r.height+'px');
   setTimeout(()=>find()?.click(),0);};
  anchor.before(button);
 };
 install();
 if(!window.whHeaderCreateObserver){
  window.whHeaderCreateObserver=new MutationObserver(install);
  window.whHeaderCreateObserver.observe(document.getElementById('root'),{childList:true,subtree:true});
 }
})();
)WHH";
    js += R"WHT((()=>{
if(window.whTipInstalled)return;window.whTipInstalled=true;
let tip=null,cur=null,timer=0;
const hide=()=>{clearTimeout(timer);if(cur&&cur.dataset.whTitle&&!cur.hasAttribute('title'))cur.setAttribute('title',cur.dataset.whTitle);cur=null;if(tip)tip.classList.remove('on');};
const show=el=>{if(!tip){tip=document.createElement('div');tip.id='wh-tip';document.body.appendChild(tip);}
 tip.textContent=el.dataset.whTitle;tip.style.left='0px';tip.style.top='0px';
 const r=el.getBoundingClientRect(),t=tip.getBoundingClientRect();
 let x=r.left+r.width/2-t.width/2,y=r.bottom+8;
 if(y+t.height>innerHeight-4)y=r.top-t.height-8;
 x=Math.max(6,Math.min(x,innerWidth-t.width-6));
 tip.style.left=x+'px';tip.style.top=y+'px';tip.classList.add('on');};
document.addEventListener('mouseover',e=>{const el=e.target.closest&&e.target.closest('[title]');
 if(!el||el===cur)return;hide();const t=el.getAttribute('title');if(!t||el.closest('.ant-select-dropdown,.ant-select-selector,.ant-dropdown')||t.trim()===el.textContent.trim())return;
 el.dataset.whTitle=t;el.removeAttribute('title');cur=el;timer=setTimeout(()=>{if(cur===el)show(el);},450);},true);
document.addEventListener('mouseout',e=>{if(cur&&(!e.relatedTarget||!cur.contains(e.relatedTarget)))hide();},true);
['mousedown','wheel','keydown'].forEach(n=>document.addEventListener(n,hide,true));
window.addEventListener('blur',hide);
})();
)WHT";
    // 2.2.12: Windhawk's own overlay scrollbar is fixed to the window, so it runs straight
    // past an open pop-up's rounded corners (2026-11-20 screenshot). While one is open,
    // clip it to that pop-up's live rect with its real radius, rounded on the corners.
    js += R"WHC((()=>{
 if(window.whcClip)return;window.whcClip=1;
 const style=document.createElement('style');style.id='whc-clip';document.head.appendChild(style);
 const upd=()=>{
  const open=document.querySelectorAll('.ant-select-dropdown:not(.ant-select-dropdown-hidden),.ant-dropdown:not(.ant-dropdown-hidden),.ant-picker-dropdown:not(.ant-picker-dropdown-hidden)');
  if(!open.length){if(style.textContent)style.textContent='';return;}
  let rule='';
  open.forEach(d=>{const r=d.getBoundingClientRect();if(r.width<8||r.height<8)return;
   const rad=Math.min(16,parseFloat(getComputedStyle(d).borderRadius)||16);
   rule+='.wh-cscroll-host{clip-path:inset('+r.top+'px -100vmax '+(innerHeight-r.bottom)+'px '+r.left+'px round '+rad+'px) !important;}';});
  style.textContent=rule;
 };
 const mo=new MutationObserver(()=>setTimeout(upd,0));
 mo.observe(document.body,{childList:true,subtree:true,attributes:true,attributeFilter:['class','style']});
 addEventListener('resize',upd);addEventListener('scroll',upd,true);
})();
)WHC";
    js += "};";
    js += "if(document.readyState==='loading')document.addEventListener('DOMContentLoaded',rest,{once:true});else rest();";
    js += "return 'ok len='+css.length;";
    js += "})()";
    return js;
}

static std::uint32_t Bgr(std::uint32_t rgb) {
    return ((rgb & 0xff) << 16) | (rgb & 0x00ff00) | ((rgb >> 16) & 0xff);
}

static COLORREF NativeBorderColor(HWND hwnd) {
    DWORD color = DWMWA_COLOR_DEFAULT;
    DWORD size = sizeof(color);
    if (GetForegroundWindow() == hwnd) {
        if (RegGetValueW(HKEY_CURRENT_USER,
                         L"Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Accent",
                         L"AccentColorMenu", RRF_RT_REG_DWORD, nullptr, &color, &size) == ERROR_SUCCESS) {
            color &= 0x00ffffff;
        }
    } else {
        if (RegGetValueW(HKEY_CURRENT_USER, L"Software\\Microsoft\\Windows\\DWM",
                         L"AccentColorInactive", RRF_RT_REG_DWORD, nullptr, &color, &size) == ERROR_SUCCESS) {
            color &= 0x00ffffff;
        }
    }
    return color;
}

static void ApplyWindowStack(HWND hWnd, const Settings& s) {
    // Never force the active look: Windows dims the title buttons on a background
    // window from the real focus state. The accent glass stays either way.
    BOOL activeLook = FALSE;
    WINCOMPATTRDATA appearance{WCA_FORCE_ACTIVEWINDOW_APPEARANCE, &activeLook, sizeof(activeLook)};
    SetWindowCompositionAttribute(hWnd, &appearance);
    // DWM draws the backdrop and border with the system's current corner radius.
    int intValue = 1;
    DwmSetWindowAttribute(hWnd, DWMWA_USE_IMMERSIVE_DARK_MODE, &intValue, sizeof(intValue));
    intValue = 1;  // DWMSBT_NONE: the accent policy below draws the material
    DwmSetWindowAttribute(hWnd, DWMWA_SYSTEMBACKDROP_TYPE, &intValue, sizeof(intValue));
    MARGINS margins = {-1, -1, -1, -1};
    DwmExtendFrameIntoClientArea(hWnd, &margins);
    if (s.nativeTitleBar) {
        // With the acrylic title bar the caption color stays NONE: the strip
        // then shows the same acrylic backdrop as the client, which is
        // the only way a DWM-drawn caption can match a blurred body. Without
        // it (legacy mode) the strip gets a solid color, because on this
        // build DWMWA_CAPTION_COLOR ignores alpha (0xAARRGGBB sets do not
        // render) and COLOR_NONE alone paints a flat dark fill.
        COLORREF caption = DWMWA_COLOR_NONE;
        if (!s.titleBarAcrylic && s.titleBarColorSet) caption = (COLORREF)Bgr(s.titleBarRgb);
        if (s.titleBarAcrylic && s.blur && s.backgroundOpacity == 100) caption = Bgr(s.background);
        DwmSetWindowAttribute(hWnd, DWMWA_CAPTION_COLOR, &caption, sizeof(caption));
        if (!s.text.empty()) {
            COLORREF text = Bgr(s.textRgb);
            DwmSetWindowAttribute(hWnd, DWMWA_TEXT_COLOR, &text, sizeof(text));
        }
    }
    COLORREF border = NativeBorderColor(hWnd);
    DwmSetWindowAttribute(hWnd, DWMWA_BORDER_COLOR, &border, sizeof(border));

    // An empty blur region composes the client's alpha. The accent policy
    // then draws the material under the whole window, caption strip
    // included, so strip and body are one sheet. Acrylic carries the
    // background tint in the accent color, because a CSS veil covers only the
    // body. On this build DWMSBT_TRANSIENTWINDOW, and an accent without the
    // blur region, render a flat fill (measured 2026-10-24).
    HRGN region = CreateRectRgn(0, 0, -1, -1);
    if (region) {
        DWM_BLURBEHIND blur{DWM_BB_ENABLE | DWM_BB_BLURREGION, TRUE, region, FALSE};
        DwmEnableBlurBehindWindow(hWnd, &blur);
        DeleteObject(region);
    }
    ACCENT_POLICY policy = {};
    if (s.blur) {
        policy.AccentState = s.blur == 2 ? ACCENT_ENABLE_ACRYLICBLURBEHIND : ACCENT_ENABLE_BLURBEHIND;
        policy.AccentFlags = 2;
        if (s.blur == 2)
            policy.GradientColor = ((std::uint32_t)(s.backgroundOpacity * 255 / 100) << 24) | Bgr(s.background);
    }
    WINCOMPATTRDATA data{WCA_ACCENT_POLICY, &policy, sizeof(policy)};
    SetWindowCompositionAttribute(hWnd, &data);
}

static void ClearWindowStack(HWND hWnd) {
    BOOL activeLook = FALSE;
    WINCOMPATTRDATA appearance{WCA_FORCE_ACTIVEWINDOW_APPEARANCE, &activeLook, sizeof(activeLook)};
    SetWindowCompositionAttribute(hWnd, &appearance);
    DWM_BLURBEHIND blur{DWM_BB_ENABLE, FALSE, nullptr, FALSE};
    DwmEnableBlurBehindWindow(hWnd, &blur);
    int intValue = 0;  // auto backdrop
    DwmSetWindowAttribute(hWnd, DWMWA_SYSTEMBACKDROP_TYPE, &intValue, sizeof(intValue));
    MARGINS margins = {0, 0, 0, 0};
    DwmExtendFrameIntoClientArea(hWnd, &margins);
    intValue = 0;
    DwmSetWindowAttribute(hWnd, DWMWA_USE_IMMERSIVE_DARK_MODE, &intValue, sizeof(intValue));
    COLORREF def = DWMWA_COLOR_DEFAULT;
    DwmSetWindowAttribute(hWnd, DWMWA_CAPTION_COLOR, &def, sizeof(def));
    DwmSetWindowAttribute(hWnd, DWMWA_TEXT_COLOR, &def, sizeof(def));
    DwmSetWindowAttribute(hWnd, DWMWA_BORDER_COLOR, &def, sizeof(def));
    ACCENT_POLICY policy = {};
    policy.AccentState = 0;  // none
    WINCOMPATTRDATA data = {};
    data.Attribute = WCA_ACCENT_POLICY;
    data.Size = sizeof(policy);
    data.Data = &policy;
    SetWindowCompositionAttribute(hWnd, &data);
}

// ---- Native tray pop-ups -------------------------------------------------
//
// The taskbar icon and its dialogs ("Mod tasks in progress", "Loaded mods")
// belong to windhawk.exe, not to the Tauri interface, so the mod loads there
// too and themes them in place: the frame from the same DWM pass the main
// window gets, the dialog background from its own erase and the list rows
// from ListView messages. Everything else - the webview theme, the save
// watch, the relaunch helper - stays with the interface process only.

static bool g_isUiProcess = false;

static std::wstring IconFile() {
    wchar_t folder[MAX_PATH];
    if (FAILED(SHGetFolderPathW(nullptr, CSIDL_LOCAL_APPDATA, nullptr, SHGFP_TYPE_CURRENT, folder))) return {};
    std::wstring dir = std::wstring(folder) + L"\\Windhawk";
    return dir + L"\\Windhawk-Mocha.ico";
}

static bool WriteMochaIcon(const std::wstring& path) {
    if (GetFileAttributesW(path.c_str()) != INVALID_FILE_ATTRIBUTES) return true;
    static constexpr char data[] =
        "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"
    ;
    DWORD size = 0;
    if (!CryptStringToBinaryA(data, 0, CRYPT_STRING_BASE64, nullptr, &size, nullptr, nullptr)) return false;
    std::vector<BYTE> bytes(size);
    if (!CryptStringToBinaryA(data, 0, CRYPT_STRING_BASE64, bytes.data(), &size, nullptr, nullptr)) return false;
    std::wstring dir = path.substr(0, path.rfind(L'\\'));
    CreateDirectoryW(dir.c_str(), nullptr);
    wchar_t temp[MAX_PATH];
    if (!GetTempFileNameW(dir.c_str(), L"whi", 0, temp)) return false;
    HANDLE file = CreateFileW(temp, GENERIC_WRITE, 0, nullptr, TRUNCATE_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
    DWORD written = 0;
    bool ok = file != INVALID_HANDLE_VALUE && WriteFile(file, bytes.data(), size, &written, nullptr) && written == size;
    if (file != INVALID_HANDLE_VALUE) CloseHandle(file);
    if (ok) ok = MoveFileExW(temp, path.c_str(), MOVEFILE_REPLACE_EXISTING);
    DeleteFileW(temp);
    return ok;
}

static std::mutex g_iconMutex;
static std::map<int, HICON> g_icons;

static HICON MochaIcon(int size) {
    std::lock_guard<std::mutex> lock(g_iconMutex);
    if (auto it = g_icons.find(size); it != g_icons.end()) return it->second;
    auto path = IconFile();
    if (path.empty() || !WriteMochaIcon(path)) return nullptr;
    auto icon = (HICON)LoadImageW(nullptr, path.c_str(), IMAGE_ICON, size, size, LR_LOADFROMFILE);
    if (icon) g_icons.emplace(size, icon);
    return icon;
}

static bool OwnTrayWindow(HWND hwnd) {
    DWORD pid = 0;
    GetWindowThreadProcessId(hwnd, &pid);
    wchar_t name[32];
    return pid == GetCurrentProcessId() && GetClassNameW(hwnd, name, ARRAYSIZE(name)) &&
           wcscmp(name, L"WindhawkDaemon") == 0;
}

static decltype(&Shell_NotifyIconW) g_notifyIcon;
static std::atomic_bool g_mochaIcons;
static std::atomic_bool g_trayAlert;
static std::atomic_bool g_themedTray;

static HICON MakeTrayIcon(int size) {
    static constexpr UINT64 glyph[] = {
    0x0000000000000000ULL, 0x0000000000000000ULL, 0x0000000000000000ULL, 0x0000000000000000ULL,
    0x0000000000000000ULL, 0x0000000000000000ULL, 0x0000000000000000ULL, 0x0000000000000000ULL,
    0x0000000000000000ULL, 0x0000000000000000ULL, 0x0000000000000000ULL, 0x0000000000000000ULL,
    0x0000000000000000ULL, 0x0000000000000000ULL, 0x000000ff80000000ULL, 0x000003fff0000000ULL,
    0x000007fffe000000ULL, 0x00001fffffe00000ULL, 0x00003fffffffe100ULL, 0x00007fffffffff00ULL,
    0x00007ffffffffc00ULL, 0x0000fffffffff800ULL, 0x0001fe7fffffe000ULL, 0x0007fa7fffff8000ULL,
    0x001fecfffff80000ULL, 0x003ff9fffffc0000ULL, 0x007fffffffff0000ULL, 0x00ffffffffff8000ULL,
    0x00ffffffffffc000ULL, 0x00ffffffffffe000ULL, 0x00ffffffff83e000ULL, 0x00fe03ffff807000ULL,
    0x00f80fffffc00800ULL, 0x00f01fffffc00000ULL, 0x00f03fffffe00000ULL, 0x00603fffffe00000ULL,
    0x0030700ffff00000ULL, 0x00004003fbf80000ULL, 0x00000001f9fc0000ULL, 0x00000000f87e0000ULL,
    0x00000000780f0000ULL, 0x000000007c000000ULL, 0x0000000038000000ULL, 0x0000000038000000ULL,
    0x0000000038000000ULL, 0x0000000018000000ULL, 0x0000000018000000ULL, 0x0000000018000000ULL,
    0x0000000010000000ULL, 0x0000000010000000ULL, 0x0000000000000000ULL, 0x0000000000000000ULL,
    0x0000000000000000ULL, 0x0000000000000000ULL, 0x0000000000000000ULL, 0x0000000000000000ULL,
    0x0000000000000000ULL, 0x0000000000000000ULL, 0x0000000000000000ULL, 0x0000000000000000ULL,
    0x0000000000000000ULL, 0x0000000000000000ULL, 0x0000000000000000ULL, 0x0000000000000000ULL,
    };
    BITMAPV5HEADER header{};
    header.bV5Size = sizeof(header);
    header.bV5Width = size;
    header.bV5Height = -size;
    header.bV5Planes = 1;
    header.bV5BitCount = 32;
    header.bV5Compression = BI_BITFIELDS;
    header.bV5RedMask = 0x00ff0000;
    header.bV5GreenMask = 0x0000ff00;
    header.bV5BlueMask = 0x000000ff;
    header.bV5AlphaMask = 0xff000000;
    void* bits = nullptr;
    HBITMAP color = CreateDIBSection(nullptr, reinterpret_cast<BITMAPINFO*>(&header),
                                     DIB_RGB_COLORS, &bits, nullptr, 0);
    if (!color) return nullptr;
    auto pixels = static_cast<UINT32*>(bits);
    const float extent = (float)size, radius = extent * 0.26f;
    constexpr UINT32 blue = 0x89B4FA, mauve = 0xCBA6F7, crust = 0x11111B;
    for (int y = 0; y < size; ++y) {
        for (int x = 0; x < size; ++x) {
            int cover = 0, mark = 0;
            for (int sy = 0; sy < 4; ++sy) {
                for (int sx = 0; sx < 4; ++sx) {
                    float fx = x + (sx + 0.5f) / 4, fy = y + (sy + 0.5f) / 4;
                    float dx = fx - std::clamp(fx, radius, extent - radius);
                    float dy = fy - std::clamp(fy, radius, extent - radius);
                    if (dx * dx + dy * dy > radius * radius) continue;
                    ++cover;
                    mark += (glyph[(int)(fy * 64 / extent)] >> (int)(fx * 64 / extent)) & 1;
                }
            }
            float mix = (x + y + 1) / (2 * extent);
            UINT32 pixel = (cover * 255 / 16u) << 24;
            for (int shift : {0, 8, 16}) {
                float a = (blue >> shift) & 255, b = (mauve >> shift) & 255;
                int ink = (crust >> shift) & 255;
                pixel |= (UINT32)((((a + (b - a) * mix) * (cover - mark)) + ink * mark) / 16) << shift;
            }
            pixels[y * size + x] = pixel;
        }
    }
    std::vector<BYTE> maskBits(((size + 15) / 16) * 2 * size, 0);
    HBITMAP mask = CreateBitmap(size, size, 1, 1, maskBits.data());
    ICONINFO info{TRUE, 0, 0, mask, color};
    HICON icon = mask ? CreateIconIndirect(&info) : nullptr;
    if (mask) DeleteObject(mask);
    DeleteObject(color);
    return icon;
}

static HICON MochaTrayIcon(HWND owner) {
    HWND taskbar = FindWindowW(L"Shell_TrayWnd", nullptr);
    UINT dpi = GetDpiForWindow(taskbar ? taskbar : owner);
    int size = GetSystemMetricsForDpi(SM_CXSMICON, dpi ? dpi : 96);
    std::lock_guard<std::mutex> lock(g_iconMutex);
    // Negative cache keys keep freshly drawn badges separate from file icons.
    if (auto it = g_icons.find(-size); it != g_icons.end()) return it->second;
    HICON icon = MakeTrayIcon(size);
    if (icon) g_icons.emplace(-size, icon);
    return icon;
}

static BOOL WINAPI NotifyIconHook(DWORD action, PNOTIFYICONDATAW data) {
    if ((action != NIM_ADD && action != NIM_MODIFY) || !data ||
        data->cbSize != sizeof(*data) || data->uID != 1 ||
        !(data->uFlags & NIF_ICON) || !OwnTrayWindow(data->hWnd)) {
        return g_notifyIcon(action, data);
    }
    if (data->uFlags & NIF_TIP) g_trayAlert = wcscmp(data->szTip, L"Windhawk") != 0;
    if (g_mochaIcons && !g_trayAlert) {
        if (HICON themed = MochaTrayIcon(data->hWnd)) {
            NOTIFYICONDATAW copy = *data;
            copy.hIcon = themed;
            BOOL ok = g_notifyIcon(action, &copy);
            if (ok) g_themedTray = true;
            return ok;
        }
    }
    BOOL ok = g_notifyIcon(action, data);
    if (ok) g_themedTray = false;
    return ok;
}

static void RefreshTrayIcon(HWND owner, bool enabled) {
    if (!g_notifyIcon || g_trayAlert || enabled == g_themedTray) return;
    NOTIFYICONDATAW data{sizeof(data)};
    data.hWnd = owner;
    data.uID = 1;
    data.uFlags = NIF_ICON;
    HICON stock = nullptr;
    if (enabled) {
        data.hIcon = MochaTrayIcon(owner);
    } else {
        HWND taskbar = FindWindowW(L"Shell_TrayWnd", nullptr);
        UINT dpi = GetDpiForWindow(taskbar ? taskbar : owner);
        int size = GetSystemMetricsForDpi(SM_CXSMICON, dpi ? dpi : 96);
        LoadIconWithScaleDown(GetModuleHandleW(nullptr), MAKEINTRESOURCEW(0x80), size, size, &stock);
        data.hIcon = stock;
    }
    if (data.hIcon && g_notifyIcon(NIM_MODIFY, &data)) g_themedTray = enabled;
    if (stock) DestroyIcon(stock);
}

// Shared shortcuts (all-users Start menu and desktop) need admin rights the
// daemon lacks. Their edited copies are saved beside the icon and copied in by
// one hidden elevated step after the loop.
struct ShortcutCopy {
    std::wstring from, to;
};

static void UpdateShortcutIcon(IShellLinkW* link, IPersistFile* file, const std::wstring& path,
                               const std::wstring& icon, const std::wstring& backup, bool enabled,
                               std::vector<ShortcutCopy>& pending) {
    if (FAILED(file->Load(path.c_str(), STGM_READ))) return;
    wchar_t target[MAX_PATH], image[MAX_PATH];
    int index = 0;
    if (FAILED(link->GetPath(target, ARRAYSIZE(target), nullptr, SLGP_RAWPATH)) ||
        FAILED(link->GetIconLocation(image, ARRAYSIZE(image), &index))) return;
    wchar_t expanded[MAX_PATH], installed[MAX_PATH];
    DWORD count = ExpandEnvironmentStringsW(target, expanded, ARRAYSIZE(expanded));
    if (!count || count > ARRAYSIZE(expanded) ||
        !GetModuleFileNameW(nullptr, installed, ARRAYSIZE(installed)) ||
        _wcsicmp(expanded, installed) != 0) return;

    bool themed = _wcsicmp(image, icon.c_str()) == 0;
    if (enabled == themed) return;
    std::wstring next = icon;
    int nextIndex = 0;
    if (enabled) {
        if (!CopyFileW(path.c_str(), backup.c_str(), FALSE)) return;
    } else {
        if (FAILED(file->Load(backup.c_str(), STGM_READ)) ||
            FAILED(link->GetIconLocation(image, ARRAYSIZE(image), &nextIndex)) ||
            FAILED(file->Load(path.c_str(), STGM_READ))) return;
        next = image;
    }
    if (FAILED(link->SetIconLocation(next.c_str(), nextIndex))) return;
    if (SUCCEEDED(file->Save(path.c_str(), TRUE))) {
        SHChangeNotify(SHCNE_UPDATEITEM, SHCNF_PATHW, path.c_str(), nullptr);
        if (!enabled) DeleteFileW(backup.c_str());
        return;
    }
    std::wstring staged = backup + L".new.lnk";
    if (SUCCEEDED(file->Save(staged.c_str(), FALSE))) pending.push_back({staged, path});
}

static void CopySharedShortcuts(const std::vector<ShortcutCopy>& pending) {
    if (pending.empty()) return;
    std::wstring args = L"/d /c";
    for (size_t i = 0; i < pending.size(); ++i) {
        args += i ? L" & copy /y \"" : L" copy /y \"";
        args += pending[i].from + L"\" \"" + pending[i].to + L"\" >nul";
    }
    wchar_t cmd[MAX_PATH];
    if (!GetSystemDirectoryW(cmd, ARRAYSIZE(cmd))) return;
    std::wstring exe = std::wstring(cmd) + L"\\cmd.exe";
    SHELLEXECUTEINFOW info{sizeof(info)};
    info.fMask = SEE_MASK_NOCLOSEPROCESS | SEE_MASK_FLAG_NO_UI | SEE_MASK_NOASYNC;
    info.lpVerb = L"runas";
    info.lpFile = exe.c_str();
    info.lpParameters = args.c_str();
    info.nShow = SW_HIDE;
    if (!ShellExecuteExW(&info)) return;
    if (info.hProcess) {
        WaitForSingleObject(info.hProcess, 15000);
        CloseHandle(info.hProcess);
    }
    for (const auto& item : pending) {
        DeleteFileW(item.from.c_str());
        SHChangeNotify(SHCNE_UPDATEITEM, SHCNF_PATHW, item.to.c_str(), nullptr);
    }
}

static void UpdateShortcutIcons(bool enabled) {
    auto icon = IconFile();
    if (icon.empty() || (enabled && !WriteMochaIcon(icon))) return;
    HRESULT init = CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED);
    if (FAILED(init)) return;
    IShellLinkW* link = nullptr;
    if (SUCCEEDED(CoCreateInstance(CLSID_ShellLink, nullptr, CLSCTX_INPROC_SERVER, IID_IShellLinkW,
                                   reinterpret_cast<void**>(&link)))) {
        IPersistFile* file = nullptr;
        if (SUCCEEDED(link->QueryInterface(IID_IPersistFile, reinterpret_cast<void**>(&file)))) {
            static constexpr struct {
                int folder;
                PCWSTR suffix;
                PCWSTR backupSuffix;
            } shortcuts[] = {
                {CSIDL_COMMON_PROGRAMS, L"\\Windhawk.lnk", L".common-programs.lnk"},
                {CSIDL_PROGRAMS, L"\\Windhawk.lnk", L".programs.lnk"},
                {CSIDL_COMMON_DESKTOPDIRECTORY, L"\\Windhawk.lnk", L".common-desktop.lnk"},
                {CSIDL_DESKTOPDIRECTORY, L"\\Windhawk.lnk", L".desktop.lnk"},
                {CSIDL_APPDATA, L"\\Microsoft\\Internet Explorer\\Quick Launch\\User Pinned\\TaskBar\\Windhawk.lnk", L".taskbar.lnk"},
            };
            std::vector<ShortcutCopy> pending;
            for (const auto& shortcut : shortcuts) {
                wchar_t folder[MAX_PATH];
                if (SUCCEEDED(SHGetFolderPathW(nullptr, shortcut.folder, nullptr, SHGFP_TYPE_CURRENT, folder))) {
                    UpdateShortcutIcon(link, file, std::wstring(folder) + shortcut.suffix,
                                       icon, icon + shortcut.backupSuffix, enabled, pending);
                }
            }
            file->Release();
            CopySharedShortcuts(pending);
        }
        link->Release();
    }
    CoUninitialize();
}

struct TrayDialogState {
    HWND list = nullptr;
    RECT progressListMargins{};
    RECT progressButtonMargins{};
    long long epoch = 0;  // settings generation the colors were pushed with
    LONG_PTR listExStyle = 0;  // the list's own border style, put back on unload
    bool partsSet = false;
};
static std::map<HWND, TrayDialogState> g_trayDialogs;
static std::mutex g_trayDialogsMutex;
static volatile long long g_trayEpoch = 1;

// The rectangle Windhawk gives the list (parent client coordinates). It becomes the
// rounded card, and the list itself sits inside it with room for the corners.
static std::map<HWND, RECT> g_trayCards;
static std::mutex g_trayCardsMutex;

static bool TrayCardRect(HWND list, RECT* out) {
    std::lock_guard<std::mutex> lock(g_trayCardsMutex);
    auto it = g_trayCards.find(list);
    if (it == g_trayCards.end()) return false;
    *out = it->second;
    return true;
}

static COLORREF CssColorToColorref(const std::string& css) {
    unsigned r = 0, g = 0, b = 0;
    if (sscanf_s(css.c_str(), "rgb(%u,%u,%u)", &r, &g, &b) == 3) return RGB(r, g, b);
    return 0;
}

// A pop-up is a transient solid surface: card when set, else the background.
static COLORREF TraySurfaceColor(const Settings& s) {
    if (!s.card.empty()) return CssColorToColorref(s.card);
    return Bgr(s.background);
}

static COLORREF TrayTextColor(const Settings& s) {
    return s.text.empty() ? 0 : Bgr(s.textRgb);
}

static std::mutex g_trayBrushMutex;
static COLORREF g_trayBrushColor = 0;
static HBRUSH g_trayBrush = nullptr;

static HBRUSH TrayBrush(COLORREF color) {
    std::lock_guard<std::mutex> lock(g_trayBrushMutex);
    if (!g_trayBrush || g_trayBrushColor != color) {
        if (g_trayBrush) DeleteObject(g_trayBrush);
        g_trayBrush = CreateSolidBrush(color);
        g_trayBrushColor = color;
    }
    return g_trayBrush;
}

static bool IsProgressDialog(HWND hwnd);
static HFONT TrayFont(HWND dialog, const Settings& s);
static void PaintTrayDialog(HWND hwnd);
static void SetupTrayDialogParts(HWND dialog);
static void HideSizeGrips(HWND dialog, bool hide);

static void ApplyTrayDialogLook(HWND dialog, HWND list, const Settings& s) {
    // The list is drawn as a text mask: white text on black, which the list's own
    // paint turns into Mocha text on the glass card (GDI has no alpha of its own).
    SendMessageW(list, LVM_SETBKCOLOR, 0, (LPARAM)RGB(0, 0, 0));
    SendMessageW(list, LVM_SETTEXTBKCOLOR, 0, (LPARAM)RGB(0, 0, 0));
    SendMessageW(list, LVM_SETTEXTCOLOR, 0, (LPARAM)RGB(255, 255, 255));
    SendMessageW(list, LVM_SETEXTENDEDLISTVIEWSTYLE, LVS_EX_GRIDLINES, 0);
    SetWindowTheme(list, L"DarkMode_Explorer", nullptr);  // dark scrollbar
    SendMessageW(list, WM_CHANGEUISTATE, MAKEWPARAM(UIS_SET, UISF_HIDEFOCUS), 0);
    if (HFONT font = TrayFont(dialog, s)) SendMessageW(list, WM_SETFONT, (WPARAM)font, TRUE);
    Settings frame = s;
    if (IsProgressDialog(dialog) && frame.blur) {
        frame.backgroundOpacity = std::clamp(frame.backgroundOpacity, 85, 99);
    }
    ApplyWindowStack(dialog, frame);
    RedrawWindow(dialog, nullptr, nullptr, RDW_INVALIDATE | RDW_ERASE | RDW_ALLCHILDREN | RDW_FRAME);
}

static LRESULT CALLBACK TrayDialogProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam,
                                       DWORD_PTR refData) {
    if (message == WM_NCDESTROY) {
        {
            std::lock_guard<std::mutex> lock(g_trayDialogsMutex);
            g_trayDialogs.erase(hWnd);
        }
        WindhawkUtils::RemoveWindowSubclassFromAnyThread(hWnd, TrayDialogProc);
        return DefSubclassProc(hWnd, message, wParam, lParam);
    }
    if (InterlockedExchangeAdd(&g_themeActive, 0)) {
        Settings s = SnapshotSettings();
        switch (message) {
            case WM_ERASEBKGND:
                return 1;  // WM_PAINT draws the glass body and the card
            case WM_PAINT:
                PaintTrayDialog(hWnd);
                return 0;
            case WM_SHOWWINDOW:
            case WM_SIZE: {
                LRESULT result = DefSubclassProc(hWnd, message, wParam, lParam);
                HideSizeGrips(hWnd, true);
                InvalidateRect(hWnd, nullptr, FALSE);
                return result;
            }
            case WM_NOTIFY: {
                // No selected rows: the list only reports, and a selection band would
                // be the one bright stripe left on the card.
                auto* hdr = reinterpret_cast<NMHDR*>(lParam);
                if (hdr && hdr->idFrom == 1001 && hdr->code == LVN_ITEMCHANGING) {
                    auto* nm = reinterpret_cast<NMLISTVIEW*>(lParam);
                    if ((nm->uChanged & LVIF_STATE) && (nm->uNewState & ~nm->uOldState & LVIS_SELECTED))
                        return TRUE;
                }
                break;
            }
            case WM_CTLCOLORDLG:
            case WM_CTLCOLORSTATIC:
            case WM_CTLCOLORBTN: {
                // Black is clear on the glass; any stray label keeps the theme text.
                HDC dc = (HDC)wParam;
                SetBkColor(dc, RGB(0, 0, 0));
                if (COLORREF text = TrayTextColor(s)) SetTextColor(dc, text);
                return (LRESULT)GetStockObject(BLACK_BRUSH);
            }
        }
    }
    return DefSubclassProc(hWnd, message, wParam, lParam);
}

static int CaptionHeight(UINT dpi);
static void PaintCaption(HWND hwnd, HDC dc, const Settings& s);
static LRESULT CALLBACK MainWindowProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam, DWORD_PTR);

static bool IsProgressDialog(HWND hwnd) {
    wchar_t title[128], expected[128];
    return GetWindowTextW(hwnd, title, ARRAYSIZE(title)) &&
           LoadStringW(GetModuleHandleW(nullptr), 0xbc, expected, ARRAYSIZE(expected)) &&
           // The window reads "Mod tasks in progress - Windhawk", so match the start.
           wcsncmp(title, expected, wcslen(expected)) == 0;
}

static LRESULT CALLBACK ProgressDialogProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam,
                                           DWORD_PTR) {
    UINT dpi = GetDpiForWindow(hwnd);
    int height = CaptionHeight(dpi);
    if (!InterlockedExchangeAdd(&g_themeActive, 0) && message != WM_NCDESTROY) {
        return DefSubclassProc(hwnd, message, wParam, lParam);
    }
    switch (message) {
        case WM_NCDESTROY:
            KillTimer(hwnd, 0x5EA7D0C);
            KillTimer(hwnd, 0x5EA7D0D);
            WindhawkUtils::RemoveWindowSubclassFromAnyThread(hwnd, ProgressDialogProc);
            break;
        case WM_NCCALCSIZE: {
            RECT* area = reinterpret_cast<RECT*>(lParam);
            LONG top = area->top;
            LRESULT result = DefSubclassProc(hwnd, message, wParam, lParam);
            area->top = std::max(top, area->top - height);
            return result;
        }
        case WM_SIZE: {
            if (wParam == SIZE_MINIMIZED) break;
            int clientHeight = std::max(0, (int)HIWORD(lParam) - height);
            LRESULT result = DefSubclassProc(hwnd, message, wParam, MAKELPARAM(LOWORD(lParam), clientHeight));
            RECT list, button;
            {
                std::lock_guard<std::mutex> lock(g_trayDialogsMutex);
                auto it = g_trayDialogs.find(hwnd);
                if (it == g_trayDialogs.end()) return result;
                list = it->second.progressListMargins;
                button = it->second.progressButtonMargins;
            }
            int width = LOWORD(lParam);
            int bottom = HIWORD(lParam);
            SetWindowPos(GetDlgItem(hwnd, 1001), nullptr, list.left, list.top + height,
                         std::max(0L, width - list.left - list.right),
                         std::max(0L, bottom - list.top - height - list.bottom),
                         SWP_NOZORDER | SWP_NOACTIVATE);
            SetWindowPos(GetDlgItem(hwnd, IDOK), nullptr, width - button.right - button.left,
                         bottom - button.bottom - button.top, button.left, button.top,
                         SWP_NOZORDER | SWP_NOACTIVATE);
            return result;
        }
        case WM_PAINT: {
            LRESULT result = DefSubclassProc(hwnd, message, wParam, lParam);
            HDC dc = GetDC(hwnd);
            if (dc) {
                Settings caption = SnapshotSettings();
                caption.centerTitle = true;
                PaintCaption(hwnd, dc, caption);
                ReleaseDC(hwnd, dc);
            }
            return result;
        }
        case WM_NCHITTEST: {
            LRESULT hit = DefSubclassProc(hwnd, message, wParam, lParam);
            if (hit != HTCLIENT) return hit;
            POINT point{(short)LOWORD(lParam), (short)HIWORD(lParam)};
            ScreenToClient(hwnd, &point);
            if (point.y >= height) return hit;
            if (DwmDefWindowProc(hwnd, message, wParam, lParam, &hit) &&
                (hit == HTMINBUTTON || hit == HTMAXBUTTON || hit == HTCLOSE)) return hit;
            return HTCAPTION;
        }
        case WM_NCMOUSEMOVE:
        case WM_NCMOUSELEAVE:
        case WM_NCMOUSEHOVER:
        case WM_NCLBUTTONDOWN:
        case WM_NCLBUTTONUP:
        case WM_NCRBUTTONUP:
        case WM_TIMER:
            return MainWindowProc(hwnd, message, wParam, lParam, 0);
    }
    return DefSubclassProc(hwnd, message, wParam, lParam);
}


static bool IsTrayTaskDialog(HWND hWnd) {
    DWORD pid = 0;
    GetWindowThreadProcessId(hWnd, &pid);
    if (pid != GetCurrentProcessId()) return false;
    wchar_t cls[64];
    if (!GetClassNameW(hWnd, cls, 64) || wcscmp(cls, L"#32770") != 0) return false;
    HWND list = GetDlgItem(hWnd, 1001);
    return list && GetClassNameW(list, cls, ARRAYSIZE(cls)) && wcscmp(cls, L"SysListView32") == 0;
}

static BOOL CALLBACK TrayDialogEnumProc(HWND hWnd, LPARAM lParam) {
    if (!IsTrayTaskDialog(hWnd)) return TRUE;
    bool fresh = false;
    {
        std::lock_guard<std::mutex> lock(g_trayDialogsMutex);
        fresh = !g_trayDialogs.contains(hWnd);
        if (fresh) g_trayDialogs[hWnd] = {GetDlgItem(hWnd, 1001)};
    }
    if (fresh && WindhawkUtils::SetWindowSubclassFromAnyThread(hWnd, TrayDialogProc, 0)) {
        RECT client, list, button;
        HWND listWindow = GetDlgItem(hWnd, 1001);
        HWND buttonWindow = GetDlgItem(hWnd, IDOK);
        bool progressLayout = IsProgressDialog(hWnd) && GetClientRect(hWnd, &client) &&
            GetWindowRect(listWindow, &list) && GetWindowRect(buttonWindow, &button);
        if (progressLayout) {
            MapWindowPoints(nullptr, hWnd, reinterpret_cast<POINT*>(&list), 2);
            MapWindowPoints(nullptr, hWnd, reinterpret_cast<POINT*>(&button), 2);
            {
                std::lock_guard<std::mutex> lock(g_trayDialogsMutex);
                auto& state = g_trayDialogs[hWnd];
                state.progressListMargins = {list.left, list.top, client.right - list.right, client.bottom - list.bottom};
                state.progressButtonMargins = {button.right - button.left, button.bottom - button.top,
                                               client.right - button.right, client.bottom - button.bottom};
            }
        }
        if (progressLayout &&
            WindhawkUtils::SetWindowSubclassFromAnyThread(hWnd, ProgressDialogProc, 0)) {
            DWM_WINDOW_CORNER_PREFERENCE corner = DWMWCP_ROUND;
            DwmSetWindowAttribute(hWnd, DWMWA_WINDOW_CORNER_PREFERENCE, &corner, sizeof(corner));
            SetWindowPos(hWnd, nullptr, 0, 0, 0, 0,
                         SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE | SWP_FRAMECHANGED);
        }
        SetupTrayDialogParts(hWnd);
        DebugNote("tray dialog themed");
    }
    return TRUE;
}

static void TrayDialogPass(const Settings& s) {
    {
        std::lock_guard<std::mutex> lock(g_trayDialogsMutex);
        for (auto it = g_trayDialogs.begin(); it != g_trayDialogs.end();) {
            if (!IsWindow(it->first)) it = g_trayDialogs.erase(it);
            else ++it;
        }
    }
    EnumWindows(TrayDialogEnumProc, 0);
    long long epoch = InterlockedExchangeAdd64(&g_trayEpoch, 0);
    // Copy the due dialogs out under the lock, then push the colors with no
    // lock held: the sends run on the dialog's own thread, which can be in
    // WM_NCDESTROY waiting for the same mutex.
    std::map<HWND, HWND> due;
    {
        std::lock_guard<std::mutex> lock(g_trayDialogsMutex);
        for (auto& [dialog, state] : g_trayDialogs) {
            if (IsWindow(dialog) && state.epoch != epoch) due[dialog] = state.list;
        }
    }
    for (auto& [dialog, list] : due) {
        if (!IsWindow(dialog)) continue;
        list = FindWindowExW(dialog, nullptr, L"SysListView32", nullptr);
        if (!list) continue;
        ApplyTrayDialogLook(dialog, list, s);
        std::lock_guard<std::mutex> lock(g_trayDialogsMutex);
        auto it = g_trayDialogs.find(dialog);
        if (it != g_trayDialogs.end()) it->second.epoch = epoch;
    }
}

static bool IsOurMainUiWindow(HWND hWnd) {
    DWORD pid = 0;
    GetWindowThreadProcessId(hWnd, &pid);
    if (pid != GetCurrentProcessId()) return false;
    wchar_t className[64];
    if (GetClassNameW(hWnd, className, 64) == 0) return false;
    return wcscmp(className, L"WindhawkTauriMainUI") == 0;
}

using BitBlt_t = decltype(&BitBlt);
static BitBlt_t BitBlt_orig;
static volatile long g_splashPaintSuppressed;

static BOOL WINAPI BitBlt_hook(HDC target, int x, int y, int width, int height,
                              HDC source, int sourceX, int sourceY, DWORD operation) {
    if (InterlockedExchangeAdd(&g_themeActive, 0)) {
        HWND hwnd = WindowFromDC(target);
        wchar_t className[64];
        if (hwnd && GetClassNameW(hwnd, className, 64) &&
            wcscmp(className, L"WindhawkTauriStartupLogo") == 0 &&
            IsOurMainUiWindow(GetParent(hwnd))) {
            // Transparent WebView2 exposes splash pixels left in the native surface.
            RECT rect{x, y, x + width, y + height};
            if (FillRect(target, &rect, (HBRUSH)GetStockObject(BLACK_BRUSH))) {
                if (!InterlockedExchange(&g_splashPaintSuppressed, 1)) {
                    DebugNote("startup splash painted transparent");
                }
                return TRUE;
            }
        }
    }
    return BitBlt_orig(target, x, y, width, height, source, sourceX, sourceY, operation);
}

static COLORREF ReadCaptionColor(HWND hWnd) {
    COLORREF color = 0;
    if (FAILED(DwmGetWindowAttribute(hWnd, DWMWA_CAPTION_COLOR, &color, sizeof(color)))) return 0;
    return color;
}

static BOOL CALLBACK ApplyEnumProc(HWND hWnd, LPARAM lParam) {
    if (!IsOurMainUiWindow(hWnd)) return TRUE;
    if (!IsWindowVisible(hWnd)) return TRUE;
    Settings* s = (Settings*)lParam;
    // Re-apply only when something else has changed the caption color since
    // we did; keeps the poll cheap and avoids disturbing animations.
    // (DwmGetWindowAttribute fails with E_INVALIDARG on this window while
    // the accent policy is active, so the read below returns 0 and the
    // re-apply simply runs every cycle; that is cheap and keeps the strip
    // pinned against shell re-puts.)
    COLORREF wantCaption = DWMWA_COLOR_NONE;
    if (!s->titleBarAcrylic && s->titleBarColorSet) wantCaption = (COLORREF)Bgr(s->titleBarRgb);
    // In acrylic mode the target is NONE (0): the same value the failing
    // read below returns, so the comparison cannot detect a lost strip.
    // Re-apply every cycle there instead of trusting the read.
    if (!s->nativeTitleBar || s->titleBarAcrylic || ReadCaptionColor(hWnd) != wantCaption) {
        ApplyWindowStack(hWnd, *s);
    }
    InterlockedExchange(&g_frameReady, 1);
    return TRUE;
}

static void ApplyToOurWindows(const Settings& s) {
    EnumWindows(ApplyEnumProc, (LPARAM)&s);
}

static bool IntegratedCaption(const Settings& s) {
    return s.nativeTitleBar && s.titleBarAcrylic;
}

static int CaptionHeight(UINT dpi) {
    return GetSystemMetricsForDpi(SM_CYCAPTION, dpi) +
           GetSystemMetricsForDpi(SM_CYFRAME, dpi) +
           GetSystemMetricsForDpi(SM_CXPADDEDBORDER, dpi);
}

// Where DWM draws the min/max/close buttons, in client coordinates.
static bool CaptionButtonRect(HWND hwnd, RECT* out) {
    RECT bounds, window;
    POINT origin{};
    if (FAILED(DwmGetWindowAttribute(hwnd, DWMWA_CAPTION_BUTTON_BOUNDS, &bounds, sizeof(bounds))) ||
        IsRectEmpty(&bounds) || !GetWindowRect(hwnd, &window) || !ClientToScreen(hwnd, &origin)) {
        return false;
    }
    OffsetRect(&bounds, window.left - origin.x, window.top - origin.y);
    *out = bounds;
    return true;
}

static std::map<HWND, RECT> g_captionChildren;
static std::mutex g_captionChildrenMutex;

static void CropCaptionChild(HWND child) {
    if (!InterlockedExchangeAdd(&g_themeActive, 0)) return;
    HWND owner = GetParent(child);
    if (!owner || !IsOurMainUiWindow(owner)) return;
    wchar_t cls[64];
    if (!GetClassNameW(child, cls, 64)) return;
    if (wcscmp(cls, L"WRY_WEBVIEW") != 0) return;
    Settings s = SnapshotSettings();
    if (!IntegratedCaption(s)) {
        bool restore;
        {
            std::lock_guard<std::mutex> lock(g_captionChildrenMutex);
            restore = g_captionChildren.erase(child) != 0;
        }
        if (restore) SetWindowRgn(child, nullptr, TRUE);
        return;
    }
    RECT rect;
    if (!GetClientRect(child, &rect)) return;
    rect.top = CaptionHeight(GetDpiForWindow(owner));
    {
        std::lock_guard<std::mutex> lock(g_captionChildrenMutex);
        auto it = g_captionChildren.find(child);
        if (it != g_captionChildren.end() && EqualRect(&it->second, &rect)) return;
        // Publish before SetWindowRgn, which can reenter the child's subclass.
        g_captionChildren[child] = rect;
    }
    HRGN region = CreateRectRgnIndirect(&rect);
    if (!region || !SetWindowRgn(child, region, TRUE)) {
        if (region) DeleteObject(region);
        std::lock_guard<std::mutex> lock(g_captionChildrenMutex);
        g_captionChildren.erase(child);
        return;
    }
    InvalidateRect(owner, nullptr, FALSE);
}

// ---- Title dock: the same dock Seamless Title Bars draws around every native title. ----
// This window paints its own caption (DWM never draws its title), so the dock is drawn here
// from that mod's own dock and title font settings, and the two always match.
struct TitleDockLook {
    bool on = false, hover = true, shine = true, live = false;
    int padX = 8, padY = 4, radius = 8, edge = 2, fillA = 45;
    std::uint32_t fill = 0x313244, edgeC = 0x45475A, h1 = 0x89B4FA, h2 = 0xCBA6F7;
    wchar_t family[64] = L"";
    int weight = 0;
    // Uptime after the title, as Seamless Title Bars writes it.
    bool upOn = false, upClock = false;
    bool upUnit[4] = {true, true, true, true};
    wchar_t upSep[8] = L"\x2022";
    std::uint32_t upColor = 0xA6ADC8;
    bool upColorSet = true;
};

static TitleDockLook g_dockLook;
static ULONGLONG g_dockLookTick;
static HWND g_dockHwnd;
static RECT g_dockRect;          // client coordinates of the last drawn dock, empty if none
static float g_dockHoverP;       // 0 rest .. 1 full gradient edge
static int g_dockHoverWant;
static const UINT_PTR kDockTimer = 0x5EA7D0C;
static const UINT_PTR kUptimeTimer = 0x5EA7D0D;
static HWND g_uptimeHwnd;

static const TitleDockLook& DockLook() {
    ULONGLONG now = GetTickCount64();
    if (g_dockLookTick && now - g_dockLookTick < 1000) return g_dockLook;
    g_dockLookTick = now;
    TitleDockLook d;
    const wchar_t* modKey = L"SOFTWARE\\Windhawk\\Engine\\Mods\\local@seamless-title-bars";
    const wchar_t* setKey = L"SOFTWARE\\Windhawk\\Engine\\Mods\\local@seamless-title-bars\\Settings";
    DWORD v = 0, size = sizeof(v);
    bool installed = RegGetValueW(HKEY_LOCAL_MACHINE, modKey, L"Version", RRF_RT_REG_SZ, nullptr, nullptr,
                                  nullptr) == ERROR_SUCCESS;
    bool disabled = RegGetValueW(HKEY_LOCAL_MACHINE, modKey, L"Disabled", RRF_RT_REG_DWORD, nullptr, &v,
                                 &size) == ERROR_SUCCESS && v;
    auto num = [&](const wchar_t* name, int def, int lo, int hi) {
        DWORD x = 0, sz = sizeof(x);
        if (RegGetValueW(HKEY_LOCAL_MACHINE, setKey, name, RRF_RT_REG_DWORD, nullptr, &x, &sz) != ERROR_SUCCESS)
            return def;
        int i = (int)x;
        return i < lo ? lo : (i > hi ? hi : i);
    };
    auto str = [&](const wchar_t* name, wchar_t* out, DWORD cch, const wchar_t* def) {
        DWORD sz = cch * sizeof(wchar_t);
        if (RegGetValueW(HKEY_LOCAL_MACHINE, setKey, name, RRF_RT_REG_SZ, nullptr, out, &sz) != ERROR_SUCCESS)
            wcsncpy_s(out, cch, def, _TRUNCATE);
    };
    auto col = [&](const wchar_t* name, std::uint32_t def) {
        wchar_t b[32];
        str(name, b, 32, L"");
        std::uint32_t rgb;
        return HexColorToRgb(b, &rgb) ? rgb : def;
    };
    d.live = installed && !disabled;
    d.on = d.live && num(L"titleDock.enabled", 1, 0, 1);
    d.hover = num(L"titleDock.hover", 1, 0, 1) != 0;
    d.shine = num(L"titleDock.glassShine", 1, 0, 1) != 0;
    d.padX = num(L"titleDock.paddingX", 8, 0, 30);
    d.padY = num(L"titleDock.paddingY", 4, 0, 12);
    d.radius = num(L"titleDock.radius", 8, 0, 20);
    d.edge = num(L"titleDock.edgeWidth", 2, 1, 4);
    d.fillA = num(L"titleDock.fillOpacity", 45, 0, 100);
    d.fill = col(L"titleDock.fillColor", d.fill);
    d.edgeC = col(L"titleDock.edgeColor", d.edgeC);
    d.h1 = col(L"titleDock.hoverStart", d.h1);
    d.h2 = col(L"titleDock.hoverEnd", d.h2);
    if (d.live) {
        wchar_t fam[64], w[16];
        str(L"titleFont.family", fam, 64, L"FiraCode Nerd Font");
        const wchar_t* a = fam;
        while (*a == L' ') a++;
        wcsncpy_s(d.family, a, _TRUNCATE);
        size_t n = wcslen(d.family);
        while (n && d.family[n - 1] == L' ') d.family[--n] = 0;
        str(L"titleFont.weight", w, 16, L"500");
        int wt = _wtoi(w);
        d.weight = (wt >= 100 && wt <= 950) ? wt : 0;

        wchar_t hide[16], style[16];
        str(L"title.hideMode", hide, 16, L"off");
        bool titleHidden = !wcscmp(hide, L"title") || !wcscmp(hide, L"both");
        d.upOn = num(L"uptime.enabled", 1, 0, 1) && !titleHidden;
        const wchar_t* units[4] = {L"uptime.showDays", L"uptime.showHours", L"uptime.showMinutes",
                                   L"uptime.showSeconds"};
        for (int i = 0; i < 4; ++i) d.upUnit[i] = num(units[i], 1, 0, 1) != 0;
        if (!d.upUnit[0] && !d.upUnit[1] && !d.upUnit[2] && !d.upUnit[3]) d.upUnit[2] = true;
        str(L"uptime.style", style, 16, L"compact");
        d.upClock = !wcscmp(style, L"clock");
        str(L"uptime.separator", d.upSep, 8, L"\x2022");   // a missing value is the mod's default dot
        // A missing value is the mod's default colour; an empty or unreadable one is the title's.
        wchar_t upc[32];
        str(L"uptime.color", upc, 32, L"#A6ADC8");
        std::uint32_t rgb;
        d.upColorSet = HexColorToRgb(upc, &rgb);
        if (d.upColorSet) d.upColor = rgb;
    }
    g_dockLook = d;
    return g_dockLook;
}

static int CALLBACK DockFontFound(const LOGFONTW*, const TEXTMETRICW*, DWORD, LPARAM found) {
    *(bool*)found = true;
    return 0;
}

static bool DockFontExists(HDC dc, const wchar_t* face) {
    LOGFONTW lf{};
    lf.lfCharSet = DEFAULT_CHARSET;
    wcsncpy_s(lf.lfFaceName, face, _TRUNCATE);
    bool found = false;
    EnumFontFamiliesExW(dc, &lf, DockFontFound, (LPARAM)&found, 0);
    return found;
}

// The title font Seamless Title Bars uses. GDI lists FiraCode's weights as their own
// families ("FiraCode Nerd Font Med"), so a matching style family is preferred.
static HFONT DockTitleFont(HDC dc, const LOGFONTW& base, const TitleDockLook& d) {
    LOGFONTW lf = base;
    if (!d.live || !d.family[0]) return CreateFontIndirectW(&lf);
    static const wchar_t* light[] = {L" Light", nullptr};
    static const wchar_t* medium[] = {L" Med", L" Medium", nullptr};
    static const wchar_t* semi[] = {L" SemBd", L" SemiBold", L" Semibold", nullptr};
    const wchar_t** tries = d.weight == 300 ? light : d.weight == 500 ? medium : d.weight == 600 ? semi : nullptr;
    for (int i = 0; tries && tries[i]; ++i) {
        wchar_t face[LF_FACESIZE];
        if (_snwprintf_s(face, _TRUNCATE, L"%s%s", d.family, tries[i]) < 0) continue;
        if (DockFontExists(dc, face)) {
            wcsncpy_s(lf.lfFaceName, face, _TRUNCATE);
            lf.lfWeight = FW_NORMAL;
            return CreateFontIndirectW(&lf);
        }
    }
    if (!DockFontExists(dc, d.family)) return CreateFontIndirectW(&lf);
    wcsncpy_s(lf.lfFaceName, d.family, _TRUNCATE);
    if (d.weight) lf.lfWeight = d.weight;
    return CreateFontIndirectW(&lf);
}

static float DockSdf(float px, float py, float l, float t, float r, float b, float rad) {
    float qx = std::fabs(px - (l + r) / 2) - ((r - l) / 2 - rad);
    float qy = std::fabs(py - (t + b) / 2) - ((b - t) / 2 - rad);
    float ox = std::max(qx, 0.0f), oy = std::max(qy, 0.0f);
    return std::sqrt(ox * ox + oy * oy) + std::min(std::max(qx, qy), 0.0f) - rad;
}

// Source-over of a straight colour onto premultiplied BGRA.
static void DockBlend(RGBQUAD& d, std::uint32_t rgb, float a) {
    if (a <= 0.0f) return;
    if (a > 1.0f) a = 1.0f;
    float ia = 1.0f - a;
    d.rgbRed = (BYTE)std::lround(((rgb >> 16) & 0xFF) * a + d.rgbRed * ia);
    d.rgbGreen = (BYTE)std::lround(((rgb >> 8) & 0xFF) * a + d.rgbGreen * ia);
    d.rgbBlue = (BYTE)std::lround((rgb & 0xFF) * a + d.rgbBlue * ia);
    d.rgbReserved = (BYTE)std::lround(255.0f * a + d.rgbReserved * ia);
}

static std::uint32_t DockMix(std::uint32_t a, std::uint32_t b, float t) {
    auto ch = [&](int s) {
        float x = ((a >> s) & 0xFF) + (((int)((b >> s) & 0xFF) - (int)((a >> s) & 0xFF)) * t);
        return (std::uint32_t)std::lround(x) << s;
    };
    return ch(16) | ch(8) | ch(0);
}

// Fill, top shine and edge (grey at rest, blue to mauve on hover), antialiased per pixel.
static void DrawDockPixels(RGBQUAD* px, int stride, int w, int h, const RECT& rc, const TitleDockLook& d,
                           float hoverP, UINT dpi) {
    float s = dpi / 96.0f;
    float l = (float)rc.left, t = (float)rc.top, r = (float)rc.right, b = (float)rc.bottom;
    float ew = std::max(1.0f, std::round(d.edge * s));
    float rad = std::min(d.radius * s, std::min(r - l, b - t) / 2.0f);
    float hoverA = d.hover ? 1.0f - (1.0f - hoverP) * (1.0f - hoverP) : 0.0f;   // ease-out
    float W = r - l, H = b - t, diag = W * W + H * H;
    float mid = (t + b) / 2;
    for (int y = std::max(0, (int)t - 1); y < std::min(h, (int)b + 1); ++y) {
        RGBQUAD* row = px + y * stride;
        for (int x = std::max(0, (int)l - 1); x < std::min(w, (int)r + 1); ++x) {
            float cx = x + 0.5f, cy = y + 0.5f;
            float sd = DockSdf(cx, cy, l, t, r, b, rad);
            float outer = std::clamp(0.5f - sd, 0.0f, 1.0f);
            if (outer <= 0.0f) continue;
            float inner = std::clamp(0.5f - (sd + ew), 0.0f, 1.0f);
            DockBlend(row[x], d.fill, outer * d.fillA / 100.0f);
            if (d.shine && cy < mid && mid > t)
                DockBlend(row[x], 0xFFFFFF, inner * 0.07f * (1.0f - (cy - t) / (mid - t)));
            float ec = outer - inner;
            if (ec > 0.0f) {
                if (hoverA < 0.999f) DockBlend(row[x], d.edgeC, ec * 0.9f * (1.0f - hoverA));
                if (hoverA > 0.003f) {
                    float g = diag > 0 ? std::clamp(((cx - l) * W + (cy - t) * H) / diag, 0.0f, 1.0f) : 0.0f;
                    DockBlend(row[x], DockMix(d.h1, d.h2, g), ec * hoverA);
                }
            }
        }
    }
}

// Seamless Title Bars' tool opens its dock menu on a right-click inside the dock its DWM
// part last reported. Reporting this dock the same way gives this window the same menu.
struct DockHotBlock {
    volatile LONG seq;
    volatile LONG fontSeq;
    ULONGLONG hwnd;
    LONG dockL, dockR, band, pad;
    ULONGLONG tick;
};
static HANDLE g_dockHotMap;
static DockHotBlock* g_dockHot;
static ULONGLONG g_dockHotTry;

static void DockReportHot(HWND hwnd) {
    if (!g_dockHot) {
        ULONGLONG now = GetTickCount64();
        if (g_dockHotTry && now - g_dockHotTry < 2000) return;
        g_dockHotTry = now;
        HANDLE m = OpenFileMappingW(FILE_MAP_READ | FILE_MAP_WRITE, FALSE, L"Local\\SeamlessTitleBarsHotDock");
        if (!m) return;
        void* v = MapViewOfFile(m, FILE_MAP_READ | FILE_MAP_WRITE, 0, 0, sizeof(DockHotBlock));
        if (!v) {
            CloseHandle(m);
            return;
        }
        g_dockHotMap = m;
        g_dockHot = (DockHotBlock*)v;
    }
    // Client and window origins are the same here (the caption is folded into the client).
    RECT wr;
    POINT origin{};
    if (!GetWindowRect(hwnd, &wr) || !ClientToScreen(hwnd, &origin)) return;
    LONG dx = origin.x - wr.left, dy = origin.y - wr.top;
    DockHotBlock* b = g_dockHot;
    InterlockedIncrement(&b->seq);
    b->hwnd = (ULONGLONG)(ULONG_PTR)hwnd;
    b->dockL = g_dockRect.left + dx;
    b->dockR = g_dockRect.right + dx;
    b->band = g_dockRect.bottom + dy;
    b->tick = GetTickCount64();
    InterlockedIncrement(&b->seq);
}

static void DockCloseHot() {
    if (g_dockHot) UnmapViewOfFile(g_dockHot);
    if (g_dockHotMap) CloseHandle(g_dockHotMap);
    g_dockHot = nullptr;
    g_dockHotMap = nullptr;
}

// Caption strip of the window, client coordinates.
static RECT DockCaptionRect(HWND hwnd) {
    RECT rc{};
    GetClientRect(hwnd, &rc);
    rc.bottom = CaptionHeight(GetDpiForWindow(hwnd));
    return rc;
}

static bool CursorOnDock(HWND hwnd) {
    POINT pt, client;
    if (IsRectEmpty(&g_dockRect) || hwnd != g_dockHwnd || !GetCursorPos(&pt)) return false;
    HWND under = WindowFromPoint(pt);
    if (!under || GetAncestor(under, GA_ROOT) != hwnd) return false;
    client = pt;
    return ScreenToClient(hwnd, &client) && PtInRect(&g_dockRect, client);
}

static void DockHoverTo(HWND hwnd, int want) {
    if (!DockLook().hover) want = 0;
    if (want == g_dockHoverWant && (want ? g_dockHoverP >= 1.0f : g_dockHoverP <= 0.0f)) return;
    g_dockHoverWant = want;
    SetTimer(hwnd, kDockTimer, 15, nullptr);
}

// 150 ms ease each way. While hovered the pointer is checked on each tick, so leaving is
// seen even when the next hit lands on the page below the caption.
static void DockTimerTick(HWND hwnd) {
    if (g_dockHoverWant && !CursorOnDock(hwnd)) g_dockHoverWant = 0;
    float p = std::clamp(g_dockHoverP + (g_dockHoverWant ? 0.1f : -0.1f), 0.0f, 1.0f);
    if (p != g_dockHoverP) {
        g_dockHoverP = p;
        RECT cap = DockCaptionRect(hwnd);
        InvalidateRect(hwnd, &cap, FALSE);
        return;
    }
    if (g_dockHoverWant) SetTimer(hwnd, kDockTimer, 100, nullptr);   // settled on: slow watch
    else KillTimer(hwnd, kDockTimer);
}

static void DockMouseMove(HWND hwnd, LPARAM lparam) {
    POINT pt{(short)LOWORD(lparam), (short)HIWORD(lparam)};
    bool on = hwnd == g_dockHwnd && !IsRectEmpty(&g_dockRect) && ScreenToClient(hwnd, &pt) &&
              PtInRect(&g_dockRect, pt);
    if (on) DockReportHot(hwnd);
    DockHoverTo(hwnd, on ? 1 : 0);
}

// "2d 03h 05m 12s" or "2d 3:05:12", exactly as Seamless Title Bars writes it. A unit
// that is off rolls into the next smaller one.
static void FormatUptime(const TitleDockLook& d, ULONGLONG secs, wchar_t* out, size_t cap) {
    static const ULONGLONG kUnit[4] = {86400, 3600, 60, 1};
    static const wchar_t kName[4] = {L'd', L'h', L'm', L's'};
    bool on[4] = {d.upUnit[0], d.upUnit[1], d.upUnit[2], d.upUnit[3]};
    int smallest = 3;
    while (smallest > 0 && !on[smallest]) smallest--;
    if (!on[smallest]) {
        on[2] = true;
        smallest = 2;
    }
    ULONGLONG val[4] = {}, rem = secs;
    for (int i = 0; i < 4; ++i) {
        if (on[i]) {
            val[i] = rem / kUnit[i];
            rem %= kUnit[i];
        }
    }
    int first = smallest;
    for (int i = 0; i <= smallest; ++i) {
        if (on[i] && val[i]) {
            first = i;
            break;
        }
    }
    size_t n = 0;
    out[0] = 0;
    if (!d.upClock) {
        for (int i = first; i <= smallest && n < cap; ++i) {
            if (!on[i]) continue;
            n += swprintf_s(out + n, cap - n, i == first ? L"%s%llu%lc" : L"%s%02llu%lc", n ? L" " : L"",
                            val[i], kName[i]);
        }
        return;
    }
    int i = first;
    if (i == 0) {
        n += swprintf_s(out, cap, L"%llud", val[0]);
        i = 1;
    }
    int clockUnits = 0, lastUnit = -1;
    for (; i <= smallest && n < cap; ++i) {
        if (!on[i]) continue;
        n += swprintf_s(out + n, cap - n, clockUnits ? L":%02llu" : (n ? L" %llu" : L"%llu"), val[i]);
        clockUnits++;
        lastUnit = i;
    }
    if (clockUnits == 1 && n < cap) swprintf_s(out + n, cap - n, L"%lc", kName[lastUnit]);
}

// " 1h 05m 12s" (or " \x2022 1h 05m 12s" with a separator) after the title. Each opening of
// the Windhawk window is its own process, so the window is as old as this process.
static void UptimeSuffix(const TitleDockLook& d, wchar_t* out, size_t cap) {
    out[0] = 0;
    if (!d.upOn) return;
    FILETIME created, exited, kernel, user, now;
    if (!GetProcessTimes(GetCurrentProcess(), &created, &exited, &kernel, &user)) return;
    GetSystemTimeAsFileTime(&now);
    ULONGLONG c = ((ULONGLONG)created.dwHighDateTime << 32) | created.dwLowDateTime;
    ULONGLONG t = ((ULONGLONG)now.dwHighDateTime << 32) | now.dwLowDateTime;
    wchar_t span[64];
    FormatUptime(d, t > c ? (t - c) / 10000000ULL : 0, span, 64);
    if (d.upSep[0]) swprintf_s(out, cap, L" %s %s", d.upSep, span);
    else swprintf_s(out, cap, L" %s", span);
}

// Repaint the caption just after each new second, so the seconds step evenly.
static void UptimeArm(HWND hwnd) {
    FILETIME now;
    GetSystemTimeAsFileTime(&now);
    ULONGLONG t = ((ULONGLONG)now.dwHighDateTime << 32) | now.dwLowDateTime;
    UINT wait = 1000 - (UINT)((t / 10000ULL) % 1000ULL) + 20;
    g_uptimeHwnd = hwnd;
    SetTimer(hwnd, kUptimeTimer, wait, nullptr);
}

// Dock rectangle around the icon and the title text, centred in the caption strip.
static void PaintDock(HWND hwnd, HDC paintDc, RGBQUAD* pixels, int stride, const RECT& client, int iconX, int icon,
                      const RECT& text, const wchar_t* title, UINT dpi) {
    const TitleDockLook& d = DockLook();
    g_dockHwnd = hwnd;
    SetRectEmpty(&g_dockRect);
    if (!d.on || !pixels) return;
    SIZE size{};
    TEXTMETRICW tm{};
    GetTextExtentPoint32W(paintDc, title, lstrlenW(title), &size);
    GetTextMetricsW(paintDc, &tm);
    int textEnd = std::min((int)text.left + (int)size.cx, (int)text.right);
    if (!title[0]) textEnd = iconX + icon;
    int padX = MulDiv(d.padX, dpi, 96), padY = MulDiv(d.padY, dpi, 96);
    int content = std::max(icon, (int)tm.tmHeight);
    int margin = std::max(1, MulDiv(2, dpi, 96));
    int height = std::min(content + 2 * padY, (int)client.bottom - 2 * margin);
    RECT rc{iconX - padX, (client.bottom - height) / 2, textEnd + padX, 0};
    rc.bottom = rc.top + height;
    rc.left = std::max(rc.left, (LONG)margin);
    if (rc.right <= rc.left || height <= 0) return;
    g_dockRect = rc;
    DrawDockPixels(pixels, stride, client.right, client.bottom, rc, d, g_dockHoverP, dpi);
}

static void PaintCaption(HWND hwnd, HDC dc, const Settings& s) {
    RECT client;
    GetClientRect(hwnd, &client);
    client.bottom = CaptionHeight(GetDpiForWindow(hwnd));
    BufferedPaintInit();
    HDC paintDc = nullptr;
    HPAINTBUFFER buffer = BeginBufferedPaint(dc, &client, BPBF_TOPDOWNDIB, nullptr, &paintDc);
    if (buffer) {
        RGBQUAD* pixels = nullptr;
        int stride = 0;
        bool bitsOk = SUCCEEDED(GetBufferedPaintBits(buffer, &pixels, &stride));
        if (bitsOk) {
            // The strip stays clear, like any Windows title bar over a backdrop:
            // DWM draws the caption buttons under the client, so a tint here
            // would dim them, and a hole cut for them would show as a box.
            for (int y = 0; y < client.bottom; ++y) {
                std::fill_n(pixels + y * stride, client.right, RGBQUAD{});
            }
        }
        UINT dpi = GetDpiForWindow(hwnd);
        NONCLIENTMETRICSW metrics{sizeof(metrics)};
        SystemParametersInfoForDpi(SPI_GETNONCLIENTMETRICS, sizeof(metrics), &metrics, 0, dpi);
        HFONT font = DockTitleFont(paintDc, metrics.lfCaptionFont, DockLook());
        HGDIOBJ oldFont = font ? SelectObject(paintDc, font) : nullptr;
        HTHEME theme = OpenThemeData(hwnd, L"WINDOW");
        int icon = GetSystemMetricsForDpi(SM_CXSMICON, dpi);
        int inset = MulDiv(12, dpi, 96);
        int iconX = inset;
        wchar_t title[512];
        GetWindowTextW(hwnd, title, 512);
        const TitleDockLook& look = DockLook();
        wchar_t suffix[96];
        UptimeSuffix(look, suffix, 96);
        wchar_t full[608];
        swprintf_s(full, 608, L"%s%s", title, suffix);
        if (suffix[0] && g_uptimeHwnd != hwnd) UptimeArm(hwnd);
        RECT buttons;
        LONG right = CaptionButtonRect(hwnd, &buttons) ? buttons.left - MulDiv(8, dpi, 96)
                                                      : client.right - MulDiv(160, dpi, 96);
        RECT text{inset + icon + MulDiv(8, dpi, 96), 0, right, client.bottom};
        if (s.centerTitle) {
            // Center the text on the window, icon just before it; stay clear of the buttons.
            SIZE size{};
            GetTextExtentPoint32W(paintDc, full, lstrlenW(full), &size);
            int gap = MulDiv(5, dpi, 96);
            int left = client.right / 2 - size.cx / 2;
            left = std::min(left, (int)(text.right - size.cx));
            left = std::max(left, inset + icon + gap);
            text.left = left;
            iconX = left - gap - icon;
        }
        PaintDock(hwnd, paintDc, bitsOk ? pixels : nullptr, stride, client, iconX, icon, text, full, dpi);
        if (theme) {
            DTTOPTS options{sizeof(options)};
            options.dwFlags = DTT_COMPOSITED | DTT_TEXTCOLOR;
            options.crText = s.text.empty() ? RGB(255,255,255) : Bgr(s.textRgb);
            SIZE titleSize{}, suffixSize{};
            GetTextExtentPoint32W(paintDc, title, lstrlenW(title), &titleSize);
            if (suffix[0]) GetTextExtentPoint32W(paintDc, suffix, lstrlenW(suffix), &suffixSize);
            RECT titleRect = text;
            if (suffix[0]) {
                titleRect.right = std::max(titleRect.left, titleRect.right - suffixSize.cx);
                titleRect.right = std::min(titleRect.right, (LONG)(titleRect.left + titleSize.cx));
            }
            DrawThemeTextEx(theme, paintDc, WP_CAPTION, CS_ACTIVE, title, -1,
                            DT_SINGLELINE | DT_VCENTER | DT_END_ELLIPSIS | DT_NOPREFIX, &titleRect, &options);
            if (suffix[0]) {
                RECT upRect = text;
                upRect.left = titleRect.right;
                if (look.upColorSet) options.crText = Bgr(look.upColor);
                DrawThemeTextEx(theme, paintDc, WP_CAPTION, CS_ACTIVE, suffix, -1,
                                DT_SINGLELINE | DT_VCENTER | DT_NOPREFIX, &upRect, &options);
            }
            CloseThemeData(theme);
        }
        HICON logo = (HICON)SendMessageW(hwnd, WM_GETICON, ICON_SMALL, 0);
        if (s.mochaIcons) {
            if (HICON themed = MochaIcon(icon)) logo = themed;
        }
        if (!logo) logo = (HICON)GetClassLongPtrW(hwnd, GCLP_HICONSM);
        if (logo) DrawIconEx(paintDc, iconX, (client.bottom-icon)/2, logo, icon, icon, 0, nullptr, DI_NORMAL);
        if (oldFont) SelectObject(paintDc, oldFont);
        if (font) DeleteObject(font);
        EndBufferedPaint(buffer, TRUE);
    }
    BufferedPaintUnInit();
}

// ---- Tray windows ("Mod tasks in progress", "Loaded mods"): the main window's look ----
// Every part paints straight alpha-correct pixels, so the glass shows through exactly
// where it should and nothing GDI drew comes out see-through or brightened.
static const std::uint32_t kTrayEdge = 0x45475A;     // surface1: card and button edge at rest
static const std::uint32_t kTraySubtext = 0xA6ADC8;  // column headings
static const std::uint32_t kTrayControl = 0x313244;  // button fill

static std::uint32_t TrayCssRgb(const std::string& css, std::uint32_t fallback) {
    unsigned r = 0, g = 0, b = 0;
    if (sscanf_s(css.c_str(), "rgb(%u,%u,%u)", &r, &g, &b) != 3) return fallback;
    return (r << 16) | (g << 8) | b;
}

static std::uint32_t TrayTextRgb(const Settings& s) {
    return s.text.empty() ? 0xCDD6F4 : s.textRgb;
}

// The rounded card behind the list: the theme's card colour and opacity, 2 px grey edge.
static TitleDockLook TrayCardLook(const Settings& s) {
    TitleDockLook d;
    d.hover = false;
    d.shine = false;
    d.radius = 12;
    d.edge = 2;
    d.fill = TrayCssRgb(s.card, 0x181825);
    d.fillA = s.card.empty() ? 40 : s.cardOpacity;
    d.edgeC = kTrayEdge;
    return d;
}

// FiraCode (or the theme font) at the dialog's own size, grey-scale smoothed so its
// coverage can be read back as alpha.
static HFONT TrayFont(HWND dialog, const Settings& s) {
    LOGFONTW lf{};
    HFONT base = (HFONT)SendMessageW(dialog, WM_GETFONT, 0, 0);
    if (!base || !GetObjectW(base, sizeof(lf), &lf)) {
        NONCLIENTMETRICSW metrics{sizeof(metrics)};
        SystemParametersInfoForDpi(SPI_GETNONCLIENTMETRICS, sizeof(metrics), &metrics, 0,
                                   GetDpiForWindow(dialog));
        lf = metrics.lfMessageFont;
    }
    lf.lfQuality = ANTIALIASED_QUALITY;
    TitleDockLook d;
    std::wstring family = s.font;
    size_t comma = family.find(L',');
    if (comma != std::wstring::npos) family.resize(comma);
    while (!family.empty() && (family.back() == L' ' || family.back() == L'"' || family.back() == L'\''))
        family.pop_back();
    size_t first = family.find_first_not_of(L" \"'");
    family = first == std::wstring::npos ? L"" : family.substr(first);
    d.live = !family.empty();
    wcsncpy_s(d.family, family.c_str(), _TRUNCATE);
    d.weight = s.fontWeight;
    wchar_t key[160];
    swprintf_s(key, L"%s|%d|%ld", d.family, d.weight, lf.lfHeight);
    static std::mutex mutex;
    static std::map<std::wstring, HFONT> cache;  // kept for the process: lists hold these
    std::lock_guard<std::mutex> lock(mutex);
    auto it = cache.find(key);
    if (it != cache.end()) return it->second;
    HDC dc = GetDC(nullptr);
    HFONT font = DockTitleFont(dc, lf, d);
    ReleaseDC(nullptr, dc);
    if (font) cache[key] = font;
    return font;
}

// Grey-scale text coverage from a white-on-black GDI draw, blended in as real alpha.
static void TrayBlendText(RGBQUAD* px, int stride, int w, int h, HFONT font, const wchar_t* text, RECT rc,
                          UINT flags, std::uint32_t rgb, float alpha) {
    RECT bounds{0, 0, w, h};
    IntersectRect(&rc, &rc, &bounds);
    int mw = rc.right - rc.left, mh = rc.bottom - rc.top;
    if (!text || !text[0] || mw <= 0 || mh <= 0) return;
    HDC dc = CreateCompatibleDC(nullptr);
    if (!dc) return;
    BITMAPINFO bi{};
    bi.bmiHeader = {sizeof(BITMAPINFOHEADER), mw, -mh, 1, 32, BI_RGB};
    void* bits = nullptr;
    HBITMAP bmp = CreateDIBSection(dc, &bi, DIB_RGB_COLORS, &bits, nullptr, 0);
    if (bmp) {
        HGDIOBJ oldBmp = SelectObject(dc, bmp);
        HGDIOBJ oldFont = font ? SelectObject(dc, font) : nullptr;
        SetBkMode(dc, TRANSPARENT);
        SetTextColor(dc, RGB(255, 255, 255));
        RECT local{0, 0, mw, mh};
        DrawTextW(dc, text, -1, &local, flags);
        GdiFlush();
        const RGBQUAD* m = (const RGBQUAD*)bits;
        for (int y = 0; y < mh; ++y) {
            for (int x = 0; x < mw; ++x) {
                const RGBQUAD& c = m[y * mw + x];
                int v = std::max({c.rgbRed, c.rgbGreen, c.rgbBlue});
                if (v) DockBlend(px[(rc.top + y) * stride + rc.left + x], rgb, alpha * v / 255.0f);
            }
        }
        if (oldFont) SelectObject(dc, oldFont);
        SelectObject(dc, oldBmp);
        DeleteObject(bmp);
    }
    DeleteDC(dc);
}

// One buffered, cleared, alpha-correct paint of a window's client area.
template <typename Draw>
static void TrayBufferedPaint(HWND hwnd, LONG top, Draw draw) {
    PAINTSTRUCT ps;
    HDC dc = BeginPaint(hwnd, &ps);
    if (!dc) return;
    RECT area;
    GetClientRect(hwnd, &area);
    area.top = std::min(top, area.bottom);
    if (area.right > 0 && area.bottom > area.top) {
        BufferedPaintInit();
        HDC paintDc = nullptr;
        HPAINTBUFFER buffer = BeginBufferedPaint(dc, &area, BPBF_TOPDOWNDIB, nullptr, &paintDc);
        if (buffer) {
            BufferedPaintClear(buffer, nullptr);
            RGBQUAD* pixels = nullptr;
            int stride = 0;
            if (SUCCEEDED(GetBufferedPaintBits(buffer, &pixels, &stride)))
                draw(dc, pixels, stride, (int)area.right, (int)(area.bottom - area.top));
            EndBufferedPaint(buffer, TRUE);
        }
        BufferedPaintUnInit();
    }
    EndPaint(hwnd, &ps);
}

// The dialog body is the window's own glass; the card is drawn where the list sits.
static void PaintTrayDialog(HWND hwnd) {
    UINT dpi = GetDpiForWindow(hwnd);
    LONG top = IsProgressDialog(hwnd) ? CaptionHeight(dpi) : 0;
    TrayBufferedPaint(hwnd, top, [&](HDC, RGBQUAD* px, int stride, int w, int h) {
        RECT card;
        if (!TrayCardRect(GetDlgItem(hwnd, 1001), &card)) return;
        OffsetRect(&card, 0, -top);
        DrawDockPixels(px, stride, w, h, card, TrayCardLook(SnapshotSettings()), 0.0f, dpi);
    });
}

static void PaintTrayList(HWND hwnd) {
    Settings s = SnapshotSettings();
    TitleDockLook card = TrayCardLook(s);
    std::uint32_t text = TrayTextRgb(s);
    // The header is a child of the list: paint only below it, or every list
    // repaint wipes the column names.
    LONG top = 0;
    HWND header = (HWND)SendMessageW(hwnd, LVM_GETHEADER, 0, 0);
    RECT hr;
    if (header && IsWindowVisible(header) && GetWindowRect(header, &hr)) {
        MapWindowPoints(nullptr, hwnd, reinterpret_cast<POINT*>(&hr), 2);
        top = std::max(0L, hr.bottom);
    }
    TrayBufferedPaint(hwnd, top, [&](HDC dc, RGBQUAD* px, int stride, int w, int h) {
        HDC maskDc = CreateCompatibleDC(dc);
        int fullH = h + top;
        BITMAPINFO bi{};
        bi.bmiHeader = {sizeof(BITMAPINFOHEADER), w, -fullH, 1, 32, BI_RGB};
        void* bits = nullptr;
        HBITMAP bmp = maskDc ? CreateDIBSection(maskDc, &bi, DIB_RGB_COLORS, &bits, nullptr, 0) : nullptr;
        HGDIOBJ old = bmp ? SelectObject(maskDc, bmp) : nullptr;
        if (bmp) {
            SendMessageW(hwnd, WM_PRINTCLIENT, (WPARAM)maskDc, PRF_CLIENT | PRF_ERASEBKGND);
            GdiFlush();
        }
        const RGBQUAD* m = (const RGBQUAD*)bits;
        float fillA = card.fillA / 100.0f;
        for (int y = 0; y < h; ++y) {
            for (int x = 0; x < w; ++x) {
                RGBQUAD& p = px[y * stride + x];
                DockBlend(p, card.fill, fillA);
                if (!m) continue;
                const RGBQUAD& c = m[(y + top) * w + x];
                // Faint theme bands (hover, selection) sit under the floor and stay off.
                int v = std::max({c.rgbRed, c.rgbGreen, c.rgbBlue});
                if (v > 64) DockBlend(p, text, (v - 64) / 191.0f);
            }
        }
        if (old) SelectObject(maskDc, old);
        if (bmp) DeleteObject(bmp);
        if (maskDc) DeleteDC(maskDc);
    });
}

static void PaintTrayHeader(HWND hwnd) {
    Settings s = SnapshotSettings();
    TitleDockLook card = TrayCardLook(s);
    HWND dialog = GetAncestor(hwnd, GA_ROOT);
    HFONT font = TrayFont(dialog, s);
    UINT dpi = GetDpiForWindow(hwnd);
    int hot = -1;
    POINT pt;
    if (GetCursorPos(&pt) && WindowFromPoint(pt) == hwnd && ScreenToClient(hwnd, &pt)) {
        HDHITTESTINFO hit{};
        hit.pt = pt;
        if (SendMessageW(hwnd, HDM_HITTEST, 0, (LPARAM)&hit) >= 0 && (hit.flags & HHT_ONHEADER)) hot = hit.iItem;
    }
    std::uint32_t accent = s.accent.empty() ? s.gradientStart : s.accentRgb;
    TrayBufferedPaint(hwnd, 0, [&](HDC, RGBQUAD* px, int stride, int w, int h) {
        float fillA = card.fillA / 100.0f;
        for (int y = 0; y < h; ++y)
            for (int x = 0; x < w; ++x) DockBlend(px[y * stride + x], card.fill, fillA);
        int count = (int)SendMessageW(hwnd, HDM_GETITEMCOUNT, 0, 0);
        int padX = MulDiv(8, dpi, 96);
        for (int i = 0; i < count; ++i) {
            RECT r{};
            if (!SendMessageW(hwnd, HDM_GETITEMRECT, i, (LPARAM)&r)) continue;
            wchar_t label[128] = L"";
            HDITEMW item{};
            item.mask = HDI_TEXT | HDI_FORMAT;
            item.pszText = label;
            item.cchTextMax = ARRAYSIZE(label);
            SendMessageW(hwnd, HDM_GETITEMW, i, (LPARAM)&item);
            UINT align = (item.fmt & HDF_JUSTIFYMASK) == HDF_RIGHT    ? DT_RIGHT
                         : (item.fmt & HDF_JUSTIFYMASK) == HDF_CENTER ? DT_CENTER
                                                                       : DT_LEFT;
            RECT tr{r.left + padX, r.top, r.right - padX, r.bottom};
            TrayBlendText(px, stride, w, h, font, label, tr,
                          align | DT_SINGLELINE | DT_VCENTER | DT_END_ELLIPSIS | DT_NOPREFIX,
                          i == hot ? accent : kTraySubtext, 1.0f);
            if (i < count - 1 && r.right - 1 >= 0 && r.right - 1 < w) {
                int inset = (r.bottom - r.top) / 4;
                for (int y = std::max(0, (int)r.top + inset); y < std::min(h, (int)r.bottom - inset); ++y)
                    DockBlend(px[y * stride + r.right - 1], kTrayEdge, 0.8f);
            }
        }
        if (h > 0)
            for (int x = 0; x < w; ++x) DockBlend(px[(h - 1) * stride + x], kTrayEdge, 0.6f);
    });
}

struct TrayButtonAnim {
    float p = 0.0f;
    int want = 0;
};
static std::map<HWND, TrayButtonAnim> g_trayButtons;
static std::mutex g_trayButtonsMutex;
static const UINT_PTR kTrayButtonTimer = 0x5EA7D0E;

static void PaintTrayButton(HWND hwnd) {
    Settings s = SnapshotSettings();
    float hoverP = 0.0f;
    {
        std::lock_guard<std::mutex> lock(g_trayButtonsMutex);
        hoverP = g_trayButtons[hwnd].p;
    }
    bool pressed = (SendMessageW(hwnd, BM_GETSTATE, 0, 0) & BST_PUSHED) != 0;
    bool enabled = IsWindowEnabled(hwnd);
    HFONT font = TrayFont(GetAncestor(hwnd, GA_ROOT), s);
    UINT dpi = GetDpiForWindow(hwnd);
    wchar_t label[128] = L"";
    GetWindowTextW(hwnd, label, ARRAYSIZE(label));
    TrayBufferedPaint(hwnd, 0, [&](HDC, RGBQUAD* px, int stride, int w, int h) {
        TitleDockLook d;
        d.shine = false;
        d.hover = enabled;
        d.radius = 100;  // a pill: half the height
        d.edge = 2;
        d.fill = TrayCssRgb(s.control, kTrayControl);
        d.fillA = 55;
        d.edgeC = kTrayEdge;
        d.h1 = s.gradientStart;
        d.h2 = s.gradientEnd;
        float p = enabled ? hoverP : 0.0f;
        if (pressed && enabled) {
            d.fill = DockMix(d.fill, d.h2, 0.3f);
            d.fillA = 70;
            d.h1 = d.h2;
            p = 1.0f;
        }
        RECT rc{0, 0, w, h};
        DrawDockPixels(px, stride, w, h, rc, d, p, dpi);
        TrayBlendText(px, stride, w, h, font, label, rc, DT_CENTER | DT_VCENTER | DT_SINGLELINE | DT_HIDEPREFIX,
                      enabled ? TrayTextRgb(s) : kTraySubtext, enabled ? 1.0f : 0.6f);
    });
}

// 150 ms ease each way, like the title dock.
static void TrayButtonHover(HWND hwnd, int want) {
    {
        std::lock_guard<std::mutex> lock(g_trayButtonsMutex);
        TrayButtonAnim& a = g_trayButtons[hwnd];
        if (a.want == want && (want ? a.p >= 1.0f : a.p <= 0.0f)) return;
        a.want = want;
    }
    SetTimer(hwnd, kTrayButtonTimer, 15, nullptr);
}

static LRESULT CALLBACK TrayButtonProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam, DWORD_PTR) {
    if (message == WM_NCDESTROY) {
        KillTimer(hwnd, kTrayButtonTimer);
        {
            std::lock_guard<std::mutex> lock(g_trayButtonsMutex);
            g_trayButtons.erase(hwnd);
        }
        WindhawkUtils::RemoveWindowSubclassFromAnyThread(hwnd, TrayButtonProc);
        return DefSubclassProc(hwnd, message, wParam, lParam);
    }
    if (!InterlockedExchangeAdd(&g_themeActive, 0)) return DefSubclassProc(hwnd, message, wParam, lParam);
    switch (message) {
        case WM_ERASEBKGND:
            return 1;
        case WM_PAINT:
            PaintTrayButton(hwnd);
            return 0;
        case WM_TIMER:
            if (wParam != kTrayButtonTimer) break;
            {
                bool settled;
                {
                    std::lock_guard<std::mutex> lock(g_trayButtonsMutex);
                    TrayButtonAnim& a = g_trayButtons[hwnd];
                    a.p = std::clamp(a.p + (a.want ? 0.1f : -0.1f), 0.0f, 1.0f);
                    settled = a.want ? a.p >= 1.0f : a.p <= 0.0f;
                }
                if (settled) KillTimer(hwnd, kTrayButtonTimer);
                InvalidateRect(hwnd, nullptr, FALSE);
            }
            return 0;
        case WM_MOUSEMOVE: {
            LRESULT result = DefSubclassProc(hwnd, message, wParam, lParam);
            TRACKMOUSEEVENT track{sizeof(track), TME_LEAVE, hwnd, 0};
            TrackMouseEvent(&track);
            TrayButtonHover(hwnd, 1);
            return result;
        }
        case WM_MOUSELEAVE: {
            LRESULT result = DefSubclassProc(hwnd, message, wParam, lParam);
            TrayButtonHover(hwnd, 0);
            return result;
        }
        case WM_LBUTTONDOWN:
        case WM_LBUTTONUP:
        case WM_LBUTTONDBLCLK:
        case WM_KEYDOWN:
        case WM_KEYUP:
        case WM_SETFOCUS:
        case WM_KILLFOCUS:
        case WM_ENABLE:
        case WM_CAPTURECHANGED:
        case WM_SETTEXT:
        case WM_UPDATEUISTATE:
        case BM_SETSTATE:
        case BM_SETSTYLE: {
            // The stock button paints some states straight away; paint ours over it at once.
            LRESULT result = DefSubclassProc(hwnd, message, wParam, lParam);
            RedrawWindow(hwnd, nullptr, nullptr, RDW_INVALIDATE | RDW_UPDATENOW);
            return result;
        }
    }
    return DefSubclassProc(hwnd, message, wParam, lParam);
}

static LRESULT CALLBACK TrayHeaderProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam, DWORD_PTR) {
    if (message == WM_NCDESTROY) {
        WindhawkUtils::RemoveWindowSubclassFromAnyThread(hwnd, TrayHeaderProc);
        return DefSubclassProc(hwnd, message, wParam, lParam);
    }
    if (!InterlockedExchangeAdd(&g_themeActive, 0)) return DefSubclassProc(hwnd, message, wParam, lParam);
    switch (message) {
        case WM_ERASEBKGND:
            return 1;
        case WM_PAINT:
            PaintTrayHeader(hwnd);
            return 0;
        case WM_MOUSEMOVE: {
            LRESULT result = DefSubclassProc(hwnd, message, wParam, lParam);
            TRACKMOUSEEVENT track{sizeof(track), TME_LEAVE, hwnd, 0};
            TrackMouseEvent(&track);
            InvalidateRect(hwnd, nullptr, FALSE);
            return result;
        }
        case WM_MOUSELEAVE: {
            LRESULT result = DefSubclassProc(hwnd, message, wParam, lParam);
            InvalidateRect(hwnd, nullptr, FALSE);
            return result;
        }
    }
    return DefSubclassProc(hwnd, message, wParam, lParam);
}

static int TrayCardPad(HWND list) {
    return MulDiv(6, GetDpiForWindow(list), 96);
}

static UINT TrayFitMessage() {
    static UINT msg = RegisterWindowMessageW(L"WindhawkEnhancedStyler.TrayFit");
    return msg;
}

static const wchar_t kTrayFitProp[] = L"WindhawkEnhancedStyler.TrayFitPending";

// Fira Code runs wider than the stock font, so Windhawk's fixed column widths cut
// every row short. Size columns to their text; when it all can't fit, short columns
// keep their full width and the long ones share what is left.
static void TrayFitColumns(HWND list) {
    HWND header = (HWND)SendMessageW(list, LVM_GETHEADER, 0, 0);
    int cols = header ? (int)SendMessageW(header, HDM_GETITEMCOUNT, 0, 0) : 0;
    RECT rc;
    if (cols <= 0 || cols > 16 || !GetClientRect(list, &rc)) return;
    int avail = rc.right - rc.left;
    if (avail <= 0) return;
    int pad = MulDiv(20, GetDpiForWindow(list), 96);
    int rows = (int)SendMessageW(list, LVM_GETITEMCOUNT, 0, 0);
    std::vector<int> need(cols, 0);
    wchar_t text[512];
    for (int c = 0; c < cols; ++c) {
        LVCOLUMNW col{};
        col.mask = LVCF_TEXT;
        col.pszText = text;
        col.cchTextMax = ARRAYSIZE(text);
        text[0] = 0;
        if (SendMessageW(list, LVM_GETCOLUMNW, c, (LPARAM)&col))
            need[c] = (int)SendMessageW(list, LVM_GETSTRINGWIDTHW, 0, (LPARAM)text);
        for (int r = 0; r < rows && r < 200; ++r) {
            LVITEMW item{};
            item.iSubItem = c;
            item.pszText = text;
            item.cchTextMax = ARRAYSIZE(text);
            text[0] = 0;
            SendMessageW(list, LVM_GETITEMTEXTW, r, (LPARAM)&item);
            need[c] = std::max(need[c], (int)SendMessageW(list, LVM_GETSTRINGWIDTHW, 0, (LPARAM)text));
        }
        need[c] += pad;
    }
    std::vector<int> width(cols, 0);
    std::vector<bool> done(cols, false);
    int left = avail, open = cols;
    // Water-fill: any column that fits in an even share of the space left gets
    // its full width; repeat until the rest are all too long for their share.
    for (bool changed = true; changed && open > 0;) {
        changed = false;
        for (int c = 0; c < cols; ++c) {
            if (done[c] || need[c] > left / open) continue;
            width[c] = need[c];
            left -= need[c];
            done[c] = true;
            --open;
            changed = true;
        }
    }
    if (open > 0) {
        long long sum = 0;
        for (int c = 0; c < cols; ++c)
            if (!done[c]) sum += need[c];
        int given = 0, last = -1;
        for (int c = 0; c < cols; ++c) {
            if (done[c]) continue;
            width[c] = sum > 0 ? (int)(left * (long long)need[c] / sum) : left / open;
            given += width[c];
            last = c;
        }
        if (last >= 0) width[last] += left - given;
    } else if (cols > 0) {
        width[cols - 1] += left;  // spare room goes to the last column
    }
    for (int c = 0; c < cols; ++c) {
        if (SendMessageW(list, LVM_GETCOLUMNWIDTH, c, 0) != width[c])
            SendMessageW(list, LVM_SETCOLUMNWIDTH, c, MAKELPARAM(width[c], 0));
    }
}

static void TrayQueueFit(HWND list) {
    if (GetPropW(list, kTrayFitProp)) return;
    SetPropW(list, kTrayFitProp, (HANDLE)1);
    PostMessageW(list, TrayFitMessage(), 0, 0);
}

static LRESULT CALLBACK TrayListProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam, DWORD_PTR) {
    if (message == WM_NCDESTROY) {
        {
            std::lock_guard<std::mutex> lock(g_trayCardsMutex);
            g_trayCards.erase(hwnd);
        }
        RemovePropW(hwnd, kTrayFitProp);
        WindhawkUtils::RemoveWindowSubclassFromAnyThread(hwnd, TrayListProc);
        return DefSubclassProc(hwnd, message, wParam, lParam);
    }
    if (message == TrayFitMessage()) {
        RemovePropW(hwnd, kTrayFitProp);
        if (InterlockedExchangeAdd(&g_themeActive, 0)) TrayFitColumns(hwnd);
        return 0;
    }
    if (!InterlockedExchangeAdd(&g_themeActive, 0)) return DefSubclassProc(hwnd, message, wParam, lParam);
    switch (message) {
        case LVM_INSERTITEMW:
        case LVM_INSERTITEMA:
        case LVM_SETITEMW:
        case LVM_SETITEMA:
        case LVM_SETITEMTEXTW:
        case LVM_SETITEMTEXTA:
        case LVM_DELETEITEM:
        case LVM_DELETEALLITEMS:
        case LVM_INSERTCOLUMNW:
        case LVM_INSERTCOLUMNA:
        case WM_SETFONT: {
            LRESULT result = DefSubclassProc(hwnd, message, wParam, lParam);
            TrayQueueFit(hwnd);
            return result;
        }
        case WM_ERASEBKGND:
            return 1;
        case WM_PAINT:
            PaintTrayList(hwnd);
            return 0;
        case WM_WINDOWPOSCHANGING: {
            // Whatever rectangle Windhawk gives the list becomes the card; the list
            // itself moves inside it, clear of the rounded corners.
            auto* wp = reinterpret_cast<WINDOWPOS*>(lParam);
            if ((wp->flags & SWP_NOMOVE) && (wp->flags & SWP_NOSIZE)) break;
            RECT card;
            if (!TrayCardRect(hwnd, &card)) break;
            int pad = TrayCardPad(hwnd);
            int x = (wp->flags & SWP_NOMOVE) ? card.left : wp->x;
            int y = (wp->flags & SWP_NOMOVE) ? card.top : wp->y;
            int cx = (wp->flags & SWP_NOSIZE) ? card.right - card.left : wp->cx;
            int cy = (wp->flags & SWP_NOSIZE) ? card.bottom - card.top : wp->cy;
            {
                std::lock_guard<std::mutex> lock(g_trayCardsMutex);
                g_trayCards[hwnd] = {x, y, x + cx, y + cy};
            }
            wp->x = x + pad;
            wp->y = y + pad;
            wp->cx = std::max(0, cx - 2 * pad);
            wp->cy = std::max(0, cy - 2 * pad);
            wp->flags &= ~(SWP_NOMOVE | SWP_NOSIZE);
            break;
        }
        case WM_WINDOWPOSCHANGED:
            if (HWND parent = GetParent(hwnd)) InvalidateRect(parent, nullptr, FALSE);
            if (!(reinterpret_cast<WINDOWPOS*>(lParam)->flags & SWP_NOSIZE)) TrayQueueFit(hwnd);
            break;
    }
    return DefSubclassProc(hwnd, message, wParam, lParam);
}

static BOOL CALLBACK HideGripProc(HWND child, LPARAM hide) {
    wchar_t cls[32];
    if (GetClassNameW(child, cls, ARRAYSIZE(cls)) && !wcscmp(cls, L"ScrollBar") &&
        (GetWindowLongPtrW(child, GWL_STYLE) & SBS_SIZEGRIP)) {
        // The style bit, not IsWindowVisible: the dialog is still hidden at setup.
        bool shown = (GetWindowLongPtrW(child, GWL_STYLE) & WS_VISIBLE) != 0;
        if (hide && shown) ShowWindow(child, SW_HIDE);
        else if (!hide && !shown) ShowWindow(child, SW_SHOWNA);
    }
    return TRUE;
}

// The resize dots: the window edges still resize, the dots would be the one stock part left.
static void HideSizeGrips(HWND dialog, bool hide) {
    EnumChildWindows(dialog, HideGripProc, hide);
}

static void SetupTrayDialogParts(HWND dialog) {
    HWND list = GetDlgItem(dialog, 1001);
    if (!list) return;
    HWND header = (HWND)SendMessageW(list, LVM_GETHEADER, 0, 0);
    HWND button = GetDlgItem(dialog, IDOK);
    RECT card;
    if (!GetWindowRect(list, &card)) return;
    MapWindowPoints(nullptr, dialog, reinterpret_cast<POINT*>(&card), 2);
    LONG_PTR ex = GetWindowLongPtrW(list, GWL_EXSTYLE);
    {
        std::lock_guard<std::mutex> lock(g_trayDialogsMutex);
        auto it = g_trayDialogs.find(dialog);
        if (it == g_trayDialogs.end() || it->second.partsSet) return;
        it->second.partsSet = true;
        it->second.listExStyle = ex;
    }
    {
        std::lock_guard<std::mutex> lock(g_trayCardsMutex);
        g_trayCards[list] = card;
    }
    WindhawkUtils::SetWindowSubclassFromAnyThread(list, TrayListProc, 0);
    if (header) WindhawkUtils::SetWindowSubclassFromAnyThread(header, TrayHeaderProc, 0);
    if (button) WindhawkUtils::SetWindowSubclassFromAnyThread(button, TrayButtonProc, 0);
    SetWindowLongPtrW(list, GWL_EXSTYLE, ex & ~(LONG_PTR)(WS_EX_CLIENTEDGE | WS_EX_STATICEDGE));
    SetWindowPos(list, nullptr, card.left, card.top, card.right - card.left, card.bottom - card.top,
                 SWP_NOZORDER | SWP_NOACTIVATE | SWP_FRAMECHANGED);
    HideSizeGrips(dialog, true);
    TrayQueueFit(list);
    RedrawWindow(dialog, nullptr, nullptr, RDW_INVALIDATE | RDW_ALLCHILDREN);
}

// With the side/bottom frame band folded into the client, the outer resize
// handle strip belongs to the WebView child. A tiny subclass gives the
// classic edge hit codes the old non-client border provided, keeping edge
// resize alive; only WM_NCHITTEST is touched, everything else forwards to
// the child untouched. Maximizing keeps the system geometry, so it opts out.
static std::set<HWND> g_edgeChildWindows;
static LRESULT CALLBACK WebViewEdgeProc(HWND hwnd, UINT message, WPARAM wparam,
                                        LPARAM lparam, DWORD_PTR) {
    if (message == WM_WINDOWPOSCHANGED) {
        LRESULT result = DefSubclassProc(hwnd, message, wparam, lparam);
        CropCaptionChild(hwnd);
        return result;
    }
    if (message == WM_NCHITTEST) {
        HWND main = GetAncestor(hwnd, GA_ROOT);
        RECT wr;
        if (main && IntegratedCaption(SnapshotSettings()) && GetWindowRect(main, &wr)) {
            int y = (short)HIWORD(lparam) - wr.top;
            if (y < CaptionHeight(GetDpiForWindow(main)) + MulDiv(8, GetDpiForWindow(main), 96)) return HTTRANSPARENT;
        }
        if (main && !IsZoomed(main) && GetWindowRect(main, &wr)) {
            int px = (short)LOWORD(lparam) - wr.left;
            int py = (short)HIWORD(lparam) - wr.top;
            int margin = std::max(4, 8 * int(GetDpiForWindow(main)) / 96);
            bool nearLeft = px <= margin;
            bool nearRight = px >= wr.right - 1 - margin - wr.left;
            bool nearBottom = py >= wr.bottom - margin - wr.top;
            bool inClientBand = py > margin;
            if (inClientBand && (nearLeft || nearRight || nearBottom)) {
                if (nearBottom && nearLeft) return HTBOTTOMLEFT;
                if (nearBottom && nearRight) return HTBOTTOMRIGHT;
                if (nearLeft) return HTLEFT;
                if (nearRight) return HTRIGHT;
                return HTBOTTOM;
            }
        }
    }
    return DefSubclassProc(hwnd, message, wparam, lparam);
}

// The drawn caption never reaches the default system menu, so open it here
// with the same enabled items Windows shows for a normal title bar.
static void ShowSystemMenu(HWND hwnd, POINT pt) {
    HMENU menu = GetSystemMenu(hwnd, FALSE);
    if (!menu) return;
    static bool darkMenus = false;
    if (!darkMenus) {
        darkMenus = true;
        if (HMODULE ux = GetModuleHandleW(L"uxtheme.dll")) {
            using SetPreferredAppMode = int(WINAPI*)(int);
            using FlushMenuThemes = void(WINAPI*)();
            auto setMode = (SetPreferredAppMode)GetProcAddress(ux, MAKEINTRESOURCEA(135));
            auto flush = (FlushMenuThemes)GetProcAddress(ux, MAKEINTRESOURCEA(136));
            if (setMode) setMode(1);
            if (flush) flush();
        }
    }
    bool zoomed = IsZoomed(hwnd), iconic = IsIconic(hwnd);
    auto enable = [menu](UINT id, bool on) {
        EnableMenuItem(menu, id, MF_BYCOMMAND | (on ? MF_ENABLED : MF_GRAYED));
    };
    enable(SC_RESTORE, zoomed || iconic);
    enable(SC_MOVE, !zoomed && !iconic);
    enable(SC_SIZE, !zoomed && !iconic);
    enable(SC_MINIMIZE, !iconic);
    enable(SC_MAXIMIZE, !zoomed);
    enable(SC_CLOSE, true);
    SetForegroundWindow(hwnd);
    UINT align = GetSystemMetrics(SM_MENUDROPALIGNMENT) ? TPM_RIGHTALIGN : TPM_LEFTALIGN;
    int command = TrackPopupMenu(menu, TPM_RETURNCMD | TPM_RIGHTBUTTON | align, pt.x, pt.y, 0, hwnd, nullptr);
    if (command) PostMessageW(hwnd, WM_SYSCOMMAND, command, 0);
}

// Keep activation visual only; keyboard focus and WM_ACTIVATE retain their real state.
static LRESULT CALLBACK MainWindowProc(HWND hwnd, UINT message, WPARAM wparam,
                                      LPARAM lparam, DWORD_PTR) {
    if (message == WM_TIMER && wparam == kDockTimer) {
        if (InterlockedExchangeAdd(&g_themeActive, 0)) DockTimerTick(hwnd);
        else KillTimer(hwnd, kDockTimer);
        return 0;
    }
    if (message == WM_TIMER && wparam == kUptimeTimer) {
        // Stops when the theme, the drawn caption or the uptime is off; a later paint re-arms it.
        if (InterlockedExchangeAdd(&g_themeActive, 0) && IntegratedCaption(SnapshotSettings()) &&
            DockLook().upOn) {
            RECT cap = DockCaptionRect(hwnd);
            InvalidateRect(hwnd, &cap, FALSE);
            UptimeArm(hwnd);
        } else {
            KillTimer(hwnd, kUptimeTimer);
            if (g_uptimeHwnd == hwnd) g_uptimeHwnd = nullptr;
            RECT cap = DockCaptionRect(hwnd);
            InvalidateRect(hwnd, &cap, FALSE);
        }
        return 0;
    }
    if (!InterlockedExchangeAdd(&g_themeActive, 0)) {
        return DefSubclassProc(hwnd, message, wparam, lparam);
    }
    Settings s = SnapshotSettings();
    if (IntegratedCaption(s) && message == WM_NCHITTEST) {
        LRESULT hit = 0;
        RECT wr;
        GetWindowRect(hwnd, &wr);
        int x = (short)LOWORD(lparam) - wr.left;
        int y = (short)HIWORD(lparam) - wr.top;
        UINT dpi = GetDpiForWindow(hwnd);
        int edge = std::max(4, MulDiv(8, dpi, 96));
        if (!IsZoomed(hwnd)) {
            if (y < edge) return x < edge ? HTTOPLEFT : x >= wr.right-wr.left-edge ? HTTOPRIGHT : HTTOP;
            if (x < edge) return y >= wr.bottom-wr.top-edge ? HTBOTTOMLEFT : HTLEFT;
            if (x >= wr.right-wr.left-edge) return y >= wr.bottom-wr.top-edge ? HTBOTTOMRIGHT : HTRIGHT;
            if (y >= wr.bottom-wr.top-edge) return HTBOTTOM;
        }
        if (y < CaptionHeight(dpi) + (IsZoomed(hwnd) ? edge : 0)) {
            if (x < MulDiv(32, dpi, 96)) return HTSYSMENU;
            // DwmDefWindowProc must see the hit first: it is what drives the
            // buttons' hover and pressed look, maximized or not.
            if (DwmDefWindowProc(hwnd, message, wparam, lparam, &hit) &&
                (hit == HTMINBUTTON || hit == HTMAXBUTTON || hit == HTCLOSE || !IsZoomed(hwnd))) {
                return hit;
            }
            // Maximized fallback when DWM reports only HTCAPTION for a button,
            // so the click still lands.
            RECT buttons;
            POINT pt{(short)LOWORD(lparam), (short)HIWORD(lparam)};
            if (IsZoomed(hwnd) && CaptionButtonRect(hwnd, &buttons) && ScreenToClient(hwnd, &pt) &&
                PtInRect(&buttons, pt)) {
                int button = (buttons.right - buttons.left) / 3;
                if (pt.x >= buttons.right - button) return HTCLOSE;
                if (pt.x >= buttons.right - 2 * button) return HTMAXBUTTON;
                return HTMINBUTTON;
            }
            return HTCAPTION;
        }
        if (DwmDefWindowProc(hwnd, message, wparam, lparam, &hit)) return hit;
        return DefSubclassProc(hwnd, message, wparam, lparam);
    }
    if (IntegratedCaption(s)) {
        // DWM animates the caption buttons' hover from these; the system
        // handling still runs afterwards (snap layouts on the max button).
        if (message == WM_NCMOUSEMOVE || message == WM_NCMOUSEHOVER || message == WM_NCMOUSELEAVE) {
            LRESULT ignored = 0;
            DwmDefWindowProc(hwnd, message, wparam, lparam, &ignored);
        }
        if (message == WM_NCMOUSEMOVE) DockMouseMove(hwnd, lparam);
        if (message == WM_NCMOUSELEAVE && !CursorOnDock(hwnd)) DockHoverTo(hwnd, 0);
        if (message == WM_NCRBUTTONUP && (wparam == HTCAPTION || wparam == HTSYSMENU)) {
            ShowSystemMenu(hwnd, POINT{(short)LOWORD(lparam), (short)HIWORD(lparam)});
            return 0;
        }
        // The drawn caption buttons act on release, as Windows buttons do. The
        // default tracking loop did not reliably reach minimize, so the press
        // is swallowed and the matching system command is posted instead.
        bool captionButton = wparam == HTMINBUTTON || wparam == HTMAXBUTTON || wparam == HTCLOSE;
        if (captionButton && (message == WM_NCLBUTTONDOWN || message == WM_NCLBUTTONDBLCLK)) return 0;
        if (captionButton && message == WM_NCLBUTTONUP) {
            UINT command = wparam == HTCLOSE ? SC_CLOSE :
                           wparam == HTMINBUTTON ? SC_MINIMIZE :
                           IsZoomed(hwnd) ? SC_RESTORE : SC_MAXIMIZE;
            PostMessageW(hwnd, WM_SYSCOMMAND, command, 0);
            return 0;
        }
        bool iconClick = message == WM_NCLBUTTONDOWN && wparam == HTSYSMENU;
        bool altSpace = message == WM_SYSCOMMAND && (wparam & 0xFFF0) == SC_KEYMENU && lparam == ' ';
        if (iconClick || altSpace) {
            RECT wr;
            GetWindowRect(hwnd, &wr);
            UINT dpi = GetDpiForWindow(hwnd);
            ShowSystemMenu(hwnd, POINT{wr.left + MulDiv(8, dpi, 96), wr.top + CaptionHeight(dpi)});
            return 0;
        }
    }
    if (message == WM_NCCALCSIZE && wparam) {
        RECT frameRect = *reinterpret_cast<const RECT*>(lparam);
        DefSubclassProc(hwnd, message, wparam, lparam);
        RECT* client = reinterpret_cast<RECT*>(lparam);
        if (IntegratedCaption(s)) {
            // No top inset even when maximized: with one, DwmDefWindowProc
            // stops recognizing the caption buttons and they lose hover.
            client->top = frameRect.top;
        }
        if (!IsZoomed(hwnd)) {
            client->left = frameRect.left;
            client->right = frameRect.right;
            client->bottom = frameRect.bottom;
        }
        return 0;
    }
    // Black is transparent inside the extended DWM frame; erase the old splash pixels.
    if (message == WM_ERASEBKGND) {
        RECT rect;
        GetClientRect(hwnd, &rect);
        FillRect((HDC)wparam, &rect, (HBRUSH)GetStockObject(BLACK_BRUSH));
        return 1;
    }
    if (message == WM_PAINT) {
        PAINTSTRUCT paint;
        HDC dc = BeginPaint(hwnd, &paint);
        FillRect(dc, &paint.rcPaint, (HBRUSH)GetStockObject(BLACK_BRUSH));
        if (IntegratedCaption(s)) PaintCaption(hwnd, dc, s);
        EndPaint(hwnd, &paint);
        return 0;
    }
    return DefSubclassProc(hwnd, message, wparam, lparam);
}

static std::set<HWND> g_mainWindows;
static std::map<HWND, std::pair<HICON, HICON>> g_originalWindowIcons;

static void UpdateWindowIcons(HWND hwnd, bool enabled) {
    auto originals = g_originalWindowIcons.find(hwnd);
    if (!enabled) {
        if (originals == g_originalWindowIcons.end()) return;
        SendMessageW(hwnd, WM_SETICON, ICON_SMALL, (LPARAM)originals->second.first);
        SendMessageW(hwnd, WM_SETICON, ICON_BIG, (LPARAM)originals->second.second);
        g_originalWindowIcons.erase(originals);
        return;
    }
    if (originals != g_originalWindowIcons.end()) return;
    UINT dpi = GetDpiForWindow(hwnd);
    HICON small = MochaIcon(GetSystemMetricsForDpi(SM_CXSMICON, dpi));
    HICON large = MochaIcon(GetSystemMetricsForDpi(SM_CXICON, dpi));
    if (!small || !large) return;
    HICON oldSmall = (HICON)SendMessageW(hwnd, WM_SETICON, ICON_SMALL, (LPARAM)small);
    HICON oldLarge = (HICON)SendMessageW(hwnd, WM_SETICON, ICON_BIG, (LPARAM)large);
    g_originalWindowIcons[hwnd] = {oldSmall, oldLarge};
}

static void PrepareMainWindow(HWND hwnd) {
    if (!g_mainWindows.contains(hwnd)) {
        RECT frame{}, client{};
        POINT origin{};
        bool preserveClient = !IsZoomed(hwnd) && GetWindowRect(hwnd, &frame) &&
                              GetClientRect(hwnd, &client) && ClientToScreen(hwnd, &origin);
        // Material first, so the window never shows the stock frame even if
        // it is shown before the next pass.
        ApplyWindowStack(hwnd, SnapshotSettings());
        if (!WindhawkUtils::SetWindowSubclassFromAnyThread(hwnd, MainWindowProc, 0)) return;
        g_mainWindows.insert(hwnd);
        // Preserve the saved client size when folding the old frame into it.
        // Otherwise every relaunch adds the old frame width and bottom gap.
        int width = preserveClient ? client.right : 0;
        int height = preserveClient ? client.bottom +
                     (IntegratedCaption(SnapshotSettings()) ? 0 : origin.y - frame.top) : 0;
        SetWindowPos(hwnd, nullptr, 0, 0, width, height,
                     SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE | SWP_FRAMECHANGED |
                     (preserveClient ? 0 : SWP_NOSIZE));
    }
    UpdateWindowIcons(hwnd, SnapshotSettings().mochaIcons);
    // Edge resize handles: subclass every live WebView child (the fold-in
    // moved the outside edges into it) and prune dead entries, because the
    // host can be recreated on project reloads.
    for (auto it = g_edgeChildWindows.begin(); it != g_edgeChildWindows.end();) {
        if (!IsWindow(*it)) it = g_edgeChildWindows.erase(it);
        else ++it;
    }
    if (g_pageReady && IsWindowVisible(hwnd) && !IsIconic(hwnd) &&
        !FindWindowExW(hwnd, nullptr, L"WindhawkTauriStartupLogo", nullptr)) {
        HWND webview = FindWindowExW(hwnd, nullptr, L"WRY_WEBVIEW", nullptr);
        if (webview && !g_edgeChildWindows.contains(webview) &&
            WindhawkUtils::SetWindowSubclassFromAnyThread(webview, WebViewEdgeProc, 0)) {
            g_edgeChildWindows.insert(webview);
        }
        if (webview && !IsWindowVisible(webview)) {
            // The splash handoff can leave a rendered page in a hidden native host.
            ShowWindowAsync(webview, SW_SHOWNOACTIVATE);
            DebugNote("restored hidden WebView");
        }
    }
}

static void MainWindowPass() {
    for (auto it = g_mainWindows.begin(); it != g_mainWindows.end();) {
        if (!IsWindow(*it)) it = g_mainWindows.erase(it);
        else ++it;
    }
    {
        std::lock_guard<std::mutex> lock(g_captionChildrenMutex);
        for (auto it = g_captionChildren.begin(); it != g_captionChildren.end();) {
            if (!IsWindow(it->first)) it = g_captionChildren.erase(it);
            else ++it;
        }
    }
    HWND hwnd = nullptr;
    while ((hwnd = FindWindowExW(nullptr, hwnd, L"WindhawkTauriMainUI", nullptr))) {
        if (IsOurMainUiWindow(hwnd)) {
            PrepareMainWindow(hwnd);
            HWND child = nullptr;
            while ((child = FindWindowExW(hwnd, child, L"WRY_WEBVIEW", nullptr))) CropCaptionChild(child);
        }
    }
}

// The shell re-pushes its own caption/text colors on every activation. A hook
// on DwmSetWindowAttribute corrects the values right back, in the same call,
// so no gray strip or border flashes between focus changes. Values that
// already match ours pass through untouched.
typedef HRESULT (WINAPI* DwmSetWindowAttribute_t)(HWND, DWORD, LPCVOID, DWORD);
static DwmSetWindowAttribute_t DwmSetWindowAttribute_orig = nullptr;

static HRESULT WINAPI DwmSetWindowAttribute_hook(HWND hwnd, DWORD attr, LPCVOID value, DWORD size) {
    HRESULT hr = DwmSetWindowAttribute_orig(hwnd, attr, value, size);
    if (InterlockedExchangeAdd(&g_themeActive, 0) == 0) return hr;
    Settings s;
    {
        std::lock_guard<std::mutex> lock(g_settingsMutex);
        s = g_settings;
    }
    if (attr == DWMWA_SYSTEMBACKDROP_TYPE) {
        // The shell clears the backdrop on focus changes and the next worker
        // cycle re-applies it up to a second later; the flat/acrylic
        // alternation reads as flicker. Correct the put in the same call.
        if (!IsOurMainUiWindow(hwnd)) return hr;
        int want = 1;  // DWMSBT_NONE: the accent policy draws the material
        int pushed = 0;
        if (size == 4 && value) memcpy(&pushed, value, 4);
        if (pushed != want) hr = DwmSetWindowAttribute_orig(hwnd, attr, &want, 4);
        return hr;
    }
    if (attr != DWMWA_CAPTION_COLOR && attr != DWMWA_TEXT_COLOR && attr != DWMWA_BORDER_COLOR) return hr;
    if (!s.nativeTitleBar) return hr;
    // Only correct the main UI window of this process.
    if (!IsOurMainUiWindow(hwnd)) return hr;
    std::uint32_t wantBgr;
    if (attr == DWMWA_CAPTION_COLOR) {
        // keep the configured strip fill; the shell's own re-puts are
        // corrected back in the same call. In acrylic mode the strip must
        // stay NONE so the system backdrop shows through it.
        wantBgr = (!s.titleBarAcrylic && s.titleBarColorSet)
                      ? (std::uint32_t)Bgr(s.titleBarRgb)
                      : (std::uint32_t)DWMWA_COLOR_NONE;
        if (s.titleBarAcrylic && s.blur && s.backgroundOpacity == 100) wantBgr = Bgr(s.background);
    } else if (attr == DWMWA_TEXT_COLOR) {
        if (s.text.empty()) return hr;  // unset -> let the app's color stand
        wantBgr = Bgr(s.textRgb);
    } else {
        wantBgr = NativeBorderColor(hwnd);
    }
    COLORREF pushed = 0;
    if (size == 4 && value) memcpy(&pushed, value, 4);
    if (pushed != wantBgr) {
        hr = DwmSetWindowAttribute_orig(hwnd, attr, &wantBgr, 4);
    }
    return hr;
}

typedef HRESULT (WINAPI* DwmExtendFrameIntoClientArea_t)(HWND, const MARGINS*);
static DwmExtendFrameIntoClientArea_t DwmExtendFrameIntoClientArea_orig = nullptr;

// The frame margins take the same in-call correction as the colors: the
// shell re-pushes its own margins on state changes, which un-extends the
// client until the next worker cycle and drops the acrylic from the body.
static HRESULT WINAPI DwmExtendFrameIntoClientArea_hook(HWND hwnd, const MARGINS* margins) {
    HRESULT hr = DwmExtendFrameIntoClientArea_orig(hwnd, margins);
    if (InterlockedExchangeAdd(&g_themeActive, 0) == 0) return hr;
    if (!IsOurMainUiWindow(hwnd)) return hr;
    static const MARGINS full = {-1, -1, -1, -1};
    if (!margins || memcmp(margins, &full, sizeof(MARGINS)) != 0) {
        hr = DwmExtendFrameIntoClientArea_orig(hwnd, &full);
    }
    return hr;
}

static void InitFrameWatch() {
    HMODULE dwm = GetModuleHandleW(L"dwmapi.dll");
    if (!dwm) dwm = LoadLibraryW(L"dwmapi.dll");
    if (!dwm) return;
    FARPROC p = GetProcAddress(dwm, "DwmSetWindowAttribute");
    if (p) Wh_SetFunctionHook((void*)p, (void*)DwmSetWindowAttribute_hook, (void**)&DwmSetWindowAttribute_orig);
    FARPROC e = GetProcAddress(dwm, "DwmExtendFrameIntoClientArea");
    if (e) Wh_SetFunctionHook((void*)e, (void*)DwmExtendFrameIntoClientArea_hook, (void**)&DwmExtendFrameIntoClientArea_orig);
}

// The WebView2 surface must carry an alpha-0 default background for the
// desktop to show through. The shell sets an opaque one at controller
// creation and on every theme change, through inlined vtable calls
// (put_DefaultBackgroundColor, slot 27: `call qword ptr [rax+0xD8]`, followed
// by the same test-and-jump error check every time). Each call site is
// patched to call a stub first: clear the alpha byte of the color argument
// (EDX), run the original put, then redo the original's own error check and
// fall back into the original flow. No COM objects, no thread freezing.
struct PatchRec {
    void* site;
    unsigned char orig[16];
    int origLen;
};
static PatchRec g_patches[16];
static volatile long g_patchCount = 0;

// Stubs live in the target's own .text padding (code caves): no new
// executable memory, so process policies that forbid allocating executable
// pages cannot interfere. Each cave holds one stub; the original cave bytes
// are kept for restore.
struct CaveRec {
    unsigned char* cave;
    unsigned char orig[32];  // one cave slot
};
static CaveRec g_caves[16];

static void RestorePatches() {
    long n = InterlockedExchangeAdd(&g_patchCount, 0);
    for (long i = 0; i < n && i < 16; i++) {
        void* site = g_patches[i].site;
        if (!site) continue;
        DWORD oldProtect = 0;
        if (VirtualProtect(site, (SIZE_T)g_patches[i].origLen, PAGE_EXECUTE_READWRITE, &oldProtect)) {
            memcpy(site, g_patches[i].orig, (SIZE_T)g_patches[i].origLen);
            FlushInstructionCache(GetCurrentProcess(), site, (SIZE_T)g_patches[i].origLen);
            VirtualProtect(site, (SIZE_T)g_patches[i].origLen, oldProtect, &oldProtect);
        }
        g_patches[i].site = nullptr;
        unsigned char* cave = g_caves[i].cave;
        if (cave) {
            DWORD oldProtect = 0;
            if (VirtualProtect(cave, sizeof(g_caves[i].orig), PAGE_EXECUTE_READWRITE, &oldProtect)) {
                memcpy(cave, g_caves[i].orig, sizeof(g_caves[i].orig));
                FlushInstructionCache(GetCurrentProcess(), cave, sizeof(g_caves[i].orig));
                VirtualProtect(cave, sizeof(g_caves[i].orig), oldProtect, &oldProtect);
            }
            g_caves[i].cave = nullptr;
        }
    }
    InterlockedExchange(&g_patchCount, 0);
}

// The first background put on a controller comes after the controller is
// made and before the shell navigates it, so the theme script is registered
// there, in-process: it then runs on document creation for the very first
// page, with no wait on the debugging port.
static const GUID kIidController = {0x4d00c0d1, 0x9434, 0x4eb6, {0x80, 0x78, 0x86, 0x97, 0xa5, 0x60, 0x33, 0x4f}};
static const GUID kIidAddScriptDone = {0xb99369f3, 0x9b11, 0x47b5, {0xbc, 0x6f, 0x8e, 0x78, 0x95, 0xfc, 0xea, 0x17}};
static const GUID kIidAgile = {0x94ea2b94, 0xe9cc, 0x49e0, {0xc0, 0xff, 0xee, 0x64, 0xca, 0x8f, 0x5b, 0x90}};

struct AddScriptDone;
struct AddScriptDoneVtbl {
    HRESULT(STDMETHODCALLTYPE* QueryInterface)(AddScriptDone*, REFIID, void**);
    ULONG(STDMETHODCALLTYPE* AddRef)(AddScriptDone*);
    ULONG(STDMETHODCALLTYPE* Release)(AddScriptDone*);
    HRESULT(STDMETHODCALLTYPE* Invoke)(AddScriptDone*, HRESULT, LPCWSTR);
};
struct AddScriptDone {
    const AddScriptDoneVtbl* vtbl;
};
static HRESULT STDMETHODCALLTYPE AddScriptDone_QueryInterface(AddScriptDone* self, REFIID iid, void** out) {
    if (!out) return E_POINTER;
    static const GUID kIidUnknown = {0x00000000, 0x0000, 0x0000, {0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x46}};
    if (IsEqualGUID(iid, kIidUnknown) ||IsEqualGUID(iid, kIidAddScriptDone) || IsEqualGUID(iid, kIidAgile)) {
        *out = self;
        return S_OK;
    }
    *out = nullptr;
    return E_NOINTERFACE;
}
static ULONG STDMETHODCALLTYPE AddScriptDone_AddRef(AddScriptDone*) { return 1; }
static ULONG STDMETHODCALLTYPE AddScriptDone_Release(AddScriptDone*) { return 1; }
static HRESULT STDMETHODCALLTYPE AddScriptDone_Invoke(AddScriptDone*, HRESULT hr, LPCWSTR) {
    DebugNote("early script registered, hr", (long)hr);
    return S_OK;
}
static const AddScriptDoneVtbl g_addScriptDoneVtbl = {AddScriptDone_QueryInterface, AddScriptDone_AddRef,
                                                      AddScriptDone_Release, AddScriptDone_Invoke};
static AddScriptDone g_addScriptDone = {&g_addScriptDoneVtbl};

static void* g_scriptedWebviews[8];
static int g_scriptedCount = 0;

typedef HRESULT(STDMETHODCALLTYPE* ComQi_t)(void*, REFIID, void**);
typedef ULONG(STDMETHODCALLTYPE* ComRelease_t)(void*);
typedef HRESULT(STDMETHODCALLTYPE* GetCoreWebView_t)(void*, void**);
typedef HRESULT(STDMETHODCALLTYPE* AddScript_t)(void*, LPCWSTR, AddScriptDone*);
typedef HRESULT(STDMETHODCALLTYPE* PutBackground_t)(void*, DWORD);

static void AddEarlyScript(void* object) {
    // Only a real webview controller: QueryInterface is slot 0 on any COM object.
    void* controller = nullptr;
    if (FAILED(((ComQi_t)(*(void***)object)[0])(object, kIidController, &controller)) || !controller) {
        DebugNote("early script: not a controller");
        return;
    }
    void* core = nullptr;
    // ICoreWebView2Controller::get_CoreWebView2, slot 25
    HRESULT hr = ((GetCoreWebView_t)(*(void***)controller)[25])(controller, &core);
    ((ComRelease_t)(*(void***)controller)[2])(controller);
    if (FAILED(hr) || !core) return;
    bool seen = false;
    for (int i = 0; i < g_scriptedCount; i++) seen = seen || g_scriptedWebviews[i] == core;
    if (!seen && g_scriptedCount < 8) {
        g_scriptedWebviews[g_scriptedCount++] = core;
        std::string js = "window.whEarlyAt=performance.now();" + BuildInjectJs(SnapshotSettings());
        int n = MultiByteToWideChar(CP_UTF8, 0, js.c_str(), (int)js.size(), nullptr, 0);
        std::wstring wjs((size_t)n, L'\0');
        MultiByteToWideChar(CP_UTF8, 0, js.c_str(), (int)js.size(), &wjs[0], n);
        // ICoreWebView2::AddScriptToExecuteOnDocumentCreated, slot 27
        hr = ((AddScript_t)(*(void***)core)[27])(core, wjs.c_str(), &g_addScriptDone);
        DebugNote("early script added, ms", (long)(GetTickCount64() - g_startTick));
        if (FAILED(hr)) DebugNote("early script failed, hr", (long)hr);
    }
    ((ComRelease_t)(*(void***)core)[2])(core);
}

// Reached by a tail jump from the call-site stub, so the stack is exactly the
// original call's. Runs on the interface thread, as the original put does.
static HRESULT STDMETHODCALLTYPE PutBackground_hook(void* self, DWORD color) {
    if (InterlockedExchangeAdd(&g_themeActive, 0)) AddEarlyScript(self);
    // COREWEBVIEW2_COLOR is {A, R, G, B} by value: alpha is the low byte.
    color &= ~(DWORD)0xFF;
    return ((PutBackground_t)(*(void***)self)[27])(self, color);
}

static void PatchPutSites() {
    HMODULE mainModule = GetModuleHandleW(nullptr);
    IMAGE_DOS_HEADER* dos = (IMAGE_DOS_HEADER*)mainModule;
    if (dos->e_magic != IMAGE_DOS_SIGNATURE) return;
    IMAGE_NT_HEADERS64* nt = (IMAGE_NT_HEADERS64*)((unsigned char*)mainModule + dos->e_lfanew);
    if (nt->Signature != IMAGE_NT_SIGNATURE) return;
    BYTE* codeLO = nullptr;
    SIZE_T codeSize = 0;
    for (int i = 0; i < (int)nt->FileHeader.NumberOfSections; i++) {
        IMAGE_SECTION_HEADER* s = IMAGE_FIRST_SECTION(nt) + i;
        if (memcmp(s->Name, ".text", 5) == 0) {
            codeLO = (BYTE*)mainModule + s->VirtualAddress;
            codeSize = s->Misc.VirtualSize;
        }
    }
    if (!codeLO || codeSize < 1024) {
        DebugNote("no .text");
        return;
    }

    // stub per site, written into the .text section's tail page padding (the
    // mapped region between VirtualSize and the section's page end: zero
    // padding, executable, unused). The stub TAIL-JUMPS to PutBackground_hook,
    // which clears the alpha and calls the real put: the stack state the hook
    // sees is then byte-for-byte the original direct call's, which keeps
    // stack alignment intact (an extra call frame shifts rsp by 8 and the
    // runtime's movaps stores fault on it).
    //   mov rax, PutBackground_hook   48 B8 imm64
    //   jmp rax                       FF E0
    const unsigned char pattern[8] = {0xFF, 0x90, 0xD8, 0x00, 0x00, 0x00, 0x85, 0xC0};
    // the tail padding starts after VirtualSize, 16-aligned
    unsigned char* tailBase = (unsigned char*)(((std::uintptr_t)(codeLO + codeSize) + 15) & ~15);
    unsigned char* tailEnd = (unsigned char*)(((std::uintptr_t)(codeLO + ((codeSize + 0xfff) & ~(std::size_t)0xfff))));
    const SIZE_T caveCapacity = (SIZE_T)(tailEnd - tailBase) / 32;
    if (caveCapacity == 0) {
        DebugNote("no tail padding", (long)(tailEnd - tailBase));
        return;
    }
    int patched = 0;
    for (SIZE_T o = 0; o + 16 <= codeSize && patched < 16; o++) {
        BYTE* p = codeLO + o;
        if (memcmp(p, pattern, 8) != 0) continue;
        int origLen = 0;
        std::int64_t failTarget = 0;
        if (p[8] == 0x78) {  // js rel8
            origLen = 10;
            failTarget = (std::int64_t)(p + 10) + (std::int8_t)p[9];
        } else if (p[8] == 0x0F && p[9] == 0x88) {  // js rel32
            origLen = 14;
            std::int32_t rel = 0;
            memcpy(&rel, p + 10, 4);
            failTarget = (std::int64_t)(p + 14) + rel;
        } else {
            continue;  // unexpected followup; not our call shape
        }
        // sanity: the fail target must land within the same image
        if (failTarget < (std::int64_t)codeLO || failTarget >= (std::int64_t)(codeLO + codeSize)) continue;
        // context check: the QI call pattern for controller2 sits close before
        // (the sites all share the same shape: a QueryInterface through vt[0])
        bool qiNear = false;
        for (SIZE_T back = 0x18; back <= 0x80 && !qiNear; back += 1) {
            if (o >= back + 1 && p[-(int)back] == 0xFF && (p[-(int)back + 1] == 0x10 || p[-(int)back + 1] == 0x50)) qiNear = true;  // call [rax] / call [rax+disp8]
        }
        if (!qiNear) continue;

        long idx = InterlockedExchangeAdd(&g_patchCount, 0);
        if (idx >= 16 || (SIZE_T)idx >= caveCapacity) break;
        unsigned char* cave = tailBase + (SIZE_T)idx * 32;

        // build the stub in the cave (32 bytes reserved each)
        DWORD tmp = 0;
        if (!VirtualProtect(cave, 32, PAGE_EXECUTE_READWRITE, &tmp)) {
            DebugNote("cave protect failed", GetLastError());
            continue;
        }
        unsigned char* stub = cave;
        std::uint64_t hookAddress = (std::uint64_t)(void*)PutBackground_hook;
        stub[0] = 0x48; stub[1] = 0xB8;                      // mov rax, imm64
        memcpy(stub + 2, &hookAddress, 8);
        stub[10] = 0xFF; stub[11] = 0xE0;                    // jmp rax
        FlushInstructionCache(GetCurrentProcess(), cave, 32);
        VirtualProtect(cave, 32, tmp, &tmp);

        // patch the site: call stub (E8 rel32) + NOP padding
        DWORD oldProtect = 0;
        if (!VirtualProtect(p, (SIZE_T)origLen, PAGE_EXECUTE_READWRITE, &oldProtect)) continue;
        for (int b = 0; b < origLen; b++) g_patches[idx].orig[b] = p[b];
        g_patches[idx].origLen = origLen;
        g_patches[idx].site = p;
        std::int32_t callRel = (std::int32_t)((std::int64_t)stub - ((std::int64_t)p + 5));
        p[0] = 0xE8;
        memcpy(p + 1, &callRel, 4);
        // The stub returns to p+5. Keep the original test and js after it, so a
        // failed put still takes the runtime's own error branch.
        p[5] = 0x90;
        // flush the instruction cache for the patched page
        FlushInstructionCache(GetCurrentProcess(), p, (SIZE_T)origLen);
        VirtualProtect(p, (SIZE_T)origLen, oldProtect, &oldProtect);
        g_caves[idx].cave = cave;
        memset(g_caves[idx].orig, 0, sizeof(g_caves[idx].orig));  // tail padding is zeros
        InterlockedExchange(&g_patchCount, idx + 1);
        patched++;
        o += (SIZE_T)origLen;
    }
    DebugNote("put sites patched", patched);
}

static bool ReadAll(SOCKET sock, void* buffer, int size) {
    char* p = (char*)buffer;
    int got = 0;
    while (got < size) {
        int n = recv(sock, p + got, size - got, 0);
        if (n <= 0) return false;
        got += n;
    }
    return true;
}

static bool SendAll(SOCKET sock, const void* buffer, int size) {
    const char* p = (const char*)buffer;
    int sent = 0;
    while (sent < size) {
        int n = send(sock, p + sent, size - sent, 0);
        if (n <= 0) return false;
        sent += n;
    }
    return true;
}

// Connects to the local debugging port without blocking. A refused loopback
// connect retries for about two seconds on Windows, which alone would hold
// the theme back that long while the webview is still starting, so a short
// timeout is used and the caller simply polls again.
static SOCKET ConnectLoopback(int port, int timeoutMs) {
    SOCKET sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sock == INVALID_SOCKET) return INVALID_SOCKET;
    u_long nonBlocking = 1;
    ioctlsocket(sock, FIONBIO, &nonBlocking);
    sockaddr_in addr = {};
    addr.sin_family = AF_INET;
    addr.sin_port = htons((u_short)port);
    addr.sin_addr.s_addr = htonl(0x7f000001);  // 127.0.0.1
    if (connect(sock, (sockaddr*)&addr, sizeof(addr)) != 0) {
        if (WSAGetLastError() != WSAEWOULDBLOCK) {
            closesocket(sock);
            return INVALID_SOCKET;
        }
        fd_set writable, failed;
        FD_ZERO(&writable);
        FD_ZERO(&failed);
        FD_SET(sock, &writable);
        FD_SET(sock, &failed);
        timeval tv{timeoutMs / 1000, (timeoutMs % 1000) * 1000};
        if (select(0, nullptr, &writable, &failed, &tv) != 1 || !FD_ISSET(sock, &writable)) {
            closesocket(sock);
            return INVALID_SOCKET;
        }
    }
    nonBlocking = 0;
    ioctlsocket(sock, FIONBIO, &nonBlocking);
    DWORD timeout = 3000;
    setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, (char*)&timeout, sizeof(timeout));
    setsockopt(sock, SOL_SOCKET, SO_SNDTIMEO, (char*)&timeout, sizeof(timeout));
    return sock;
}

static bool HttpGet(int port, const char* path, std::string* out) {
    SOCKET sock = ConnectLoopback(port, 60);
    if (sock == INVALID_SOCKET) return false;
    std::string request = std::string("GET ") + path + " HTTP/1.1\r\nHost: 127.0.0.1:" + std::to_string(port) + "\r\nConnection: close\r\n\r\n";
    if (!SendAll(sock, request.c_str(), (int)request.size())) {
        closesocket(sock);
        return false;
    }
    out->clear();
    char chunk[4096];
    for (;;) {
        int n = recv(sock, chunk, sizeof(chunk), 0);
        if (n <= 0) break;
        out->append(chunk, n);
        if (out->size() > (1 << 20)) break;
    }
    closesocket(sock);
    size_t bodyAt = out->find("\r\n\r\n");
    if (bodyAt == std::string::npos) return false;
    *out = out->substr(bodyAt + 4);
    return true;
}

static bool JsonStringValue(const std::string& json, const char* key, std::string* value) {
    size_t keyAt = json.find(key);
    if (keyAt == std::string::npos) return false;
    size_t colon = json.find(':', keyAt + strlen(key));
    if (colon == std::string::npos) return false;
    size_t quoteStart = json.find('"', colon + 1);
    if (quoteStart == std::string::npos) return false;
    size_t quoteEnd = json.find('"', quoteStart + 1);
    if (quoteEnd == std::string::npos) return false;
    *value = json.substr(quoteStart + 1, quoteEnd - quoteStart - 1);
    return true;
}

static void WsEncodeFrame(const std::string& payload, std::string* frame) {
    unsigned char mask[4];
    for (int i = 0; i < 4; i++) mask[i] = (unsigned char)(rand() & 0xff);
    std::string masked(payload.size(), '\0');
    for (size_t i = 0; i < payload.size(); i++) masked[i] = payload[i] ^ mask[i % 4];
    frame->clear();
    frame->push_back((char)0x81);  // FIN + text
    if (payload.size() < 126) {
        frame->push_back((char)(0x80 | payload.size()));
    } else if (payload.size() <= 0xffff) {
        frame->push_back((char)(0x80 | 126));
        frame->push_back((char)((payload.size() >> 8) & 0xff));
        frame->push_back((char)(payload.size() & 0xff));
    } else {
        frame->push_back((char)(0x80 | 127));
        std::uint64_t len = payload.size();
        for (int i = 7; i >= 0; i--) frame->push_back((char)((len >> (i * 8)) & 0xff));
    }
    frame->append((const char*)mask, 4);
    frame->append(masked);
}

static bool WsSendPong(SOCKET sock, const std::string& payload) {
    // Control frames carry at most 125 bytes (RFC 6455), and this frame has no extended length.
    if (payload.size() > 125) return false;
    unsigned char mask[4];
    for (int i = 0; i < 4; i++) mask[i] = (unsigned char)(rand() & 0xff);
    std::string masked(payload.size(), '\0');
    for (size_t i = 0; i < payload.size(); i++) masked[i] = payload[i] ^ mask[i % 4];
    std::string frame;
    frame.push_back((char)0x8A);  // FIN + pong
    frame.push_back((char)(0x80 | payload.size()));
    frame.append((const char*)mask, 4);
    frame.append(masked);
    return SendAll(sock, frame.c_str(), (int)frame.size());
}

// Reads one whole (assembled) message; answers pings. Returns false on close/error.
static bool WsReadMessage(SOCKET sock, std::string* out, int* opcode) {
    std::string assembled;
    int firstOpcode = 0;
    for (;;) {
        unsigned char header[2];
        if (!ReadAll(sock, header, 2)) return false;
        bool fin = (header[0] & 0x80) != 0;
        int op = header[0] & 0x0f;
        bool masked = (header[1] & 0x80) != 0;
        std::uint64_t len = header[1] & 0x7f;
        if (len == 126) {
            unsigned char ext[2];
            if (!ReadAll(sock, ext, 2)) return false;
            len = (ext[0] << 8) | ext[1];
        } else if (len == 127) {
            unsigned char ext[8];
            if (!ReadAll(sock, ext, 8)) return false;
            len = 0;
            for (int i = 0; i < 8; i++) len = (len << 8) | ext[i];
        }
        unsigned char mask[4] = {0, 0, 0, 0};
        if (masked && !ReadAll(sock, mask, 4)) return false;
        if (len > (1 << 23)) return false;
        std::string payload((size_t)len, '\0');
        if (len > 0 && !ReadAll(sock, &payload[0], (int)len)) return false;
        if (masked) for (size_t i = 0; i < payload.size(); i++) payload[i] ^= mask[i % 4];

        if (op == 0x9) {
            WsSendPong(sock, payload);
            continue;
        }
        if (op == 0x8) return false;  // close
        if (op == 0x1 || op == 0x2) {
            firstOpcode = op;
            assembled = payload;
        } else if (op == 0x0) {
            assembled += payload;
        }
        if (fin) {
            *out = assembled;
            *opcode = firstOpcode;
            return true;
        }
    }
}

static bool WsConnect(int port, const std::string& wsUrl, SOCKET* out) {
    // wsUrl looks like ws://127.0.0.1:9333/devtools/page/<ID>
    std::string prefix = "ws://127.0.0.1:" + std::to_string(port);
    if (wsUrl.compare(0, prefix.size(), prefix) != 0) return false;
    std::string path = wsUrl.substr(prefix.size());
    if (path.empty() || path[0] != '/') return false;

    SOCKET sock = ConnectLoopback(port, 1000);
    if (sock == INVALID_SOCKET) return false;

    unsigned char rawKey[16];
    for (int i = 0; i < 16; i++) rawKey[i] = (unsigned char)(rand() & 0xff);
    static const char alphabet[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    char key[32];
    int ko = 0;
    for (int i = 0; i < 16; i += 3) {
        int rem = 16 - i;
        std::uint32_t v = ((std::uint32_t)rawKey[i] << 16) | (rem > 1 ? (std::uint32_t)rawKey[i + 1] << 8 : 0) | (rem > 2 ? rawKey[i + 2] : 0);
        key[ko++] = alphabet[(v >> 18) & 63];
        key[ko++] = alphabet[(v >> 12) & 63];
        if (rem > 1) key[ko++] = alphabet[(v >> 6) & 63]; else key[ko++] = '=';
        if (rem > 2) key[ko++] = alphabet[v & 63]; else key[ko++] = '=';
    }
    key[ko] = '\0';

    std::string handshake =
        "GET " + path + " HTTP/1.1\r\n"
        "Host: 127.0.0.1:" + std::to_string(port) + "\r\n"
        "Upgrade: websocket\r\n"
        "Connection: Upgrade\r\n"
        "Sec-WebSocket-Key: " + std::string(key) + "\r\n"
        "Sec-WebSocket-Version: 13\r\n\r\n";
    if (!SendAll(sock, handshake.c_str(), (int)handshake.size())) {
        closesocket(sock);
        return false;
    }
    std::string response;
    char ch;
    while (response.find("\r\n\r\n") == std::string::npos && ReadAll(sock, &ch, 1)) response += ch;
    if (response.find(" 101") == std::string::npos) {
        closesocket(sock);
        return false;
    }
    *out = sock;
    return true;
}

// The theme rides on one debugger session that stays open for the life of the
// interface. It attaches to the webview's page as soon as the page exists,
// with the page held until the stylesheet is registered, and Chromium then
// runs the stylesheet script in every document of that page before any of
// Windhawk's own scripts and before the first paint, reloads included. The
// registration lasts only while the session is open, so it is never closed
// while the interface runs.
static bool StopRequested() {
    return !g_stopEvent || WaitForSingleObject(g_stopEvent, 0) == WAIT_OBJECT_0;
}

static bool WsSendText(SOCKET sock, const std::string& payload) {
    std::string frame;
    WsEncodeFrame(payload, &frame);
    return SendAll(sock, frame.c_str(), (int)frame.size());
}

static bool WaitReadable(SOCKET sock, int timeoutMs) {
    fd_set readable;
    FD_ZERO(&readable);
    FD_SET(sock, &readable);
    timeval tv{timeoutMs / 1000, (timeoutMs % 1000) * 1000};
    return select(0, &readable, nullptr, nullptr, &tv) == 1;
}

static long MsSinceStart() {
    return (long)(GetTickCount64() - g_startTick);
}

static void RunBrowserSession(SOCKET sock, const std::string& js) {
    static const char kProbe[] =
        "(()=>{const s=document.getElementById('wh-styler-style');"
        "return s&&s.isConnected&&document.querySelector('[data-testid=nav-home]')?'ok':'wait'})()";
    const std::string source = JsonEscape(js);
    int nextId = 1;
    auto send = [&](const std::string& session, const std::string& rest) {
        std::string msg = "{";
        if (!session.empty()) msg += "\"sessionId\":\"" + session + "\",";
        msg += "\"id\":" + std::to_string(nextId++) + "," + rest + "}";
        return WsSendText(sock, msg);
    };
    // Every target created from now on waits for us; pages that already exist
    // are attached as they run.
    if (!send("", "\"method\":\"Target.setAutoAttach\",\"params\":{\"autoAttach\":true,"
                  "\"waitForDebuggerOnStart\":true,\"flatten\":true}")) {
        return;
    }
    std::string pageSession;
    int probeId = 0;
    unsigned long long nextProbe = 0;
    while (!StopRequested()) {
        if (!g_pageReady && !pageSession.empty() && GetTickCount64() >= nextProbe) {
            probeId = nextId;
            if (!send(pageSession, "\"method\":\"Runtime.evaluate\",\"params\":{\"expression\":\"" +
                                       JsonEscape(kProbe) + "\",\"returnByValue\":true}")) {
                return;
            }
            nextProbe = GetTickCount64() + 100;
        }
        if (!WaitReadable(sock, 50)) continue;
        std::string msg;
        int opcode = 0;
        if (!WsReadMessage(sock, &msg, &opcode)) return;
        if (opcode != 0x1) continue;
        if (msg.find("\"method\":\"Target.attachedToTarget\"") != std::string::npos) {
            std::string session, type;
            if (!JsonStringValue(msg, "\"sessionId\"", &session)) continue;
            JsonStringValue(msg, "\"type\"", &type);
            if (type == "page") {
                // runImmediately also covers a document that is already up
                // (the mod loading into a running interface).
                send(session, "\"method\":\"Page.addScriptToEvaluateOnNewDocument\",\"params\":{\"source\":\"" +
                                  source + "\",\"runImmediately\":true}");
                pageSession = session;
                nextProbe = 0;
                DebugNote("page attached, ms", MsSinceStart());
            }
            // Always release the target, page or not, or it would stay frozen.
            send(session, "\"method\":\"Runtime.runIfWaitingForDebugger\"");
        } else if (msg.find("\"method\":\"Target.detachedFromTarget\"") != std::string::npos) {
            std::string session;
            if (JsonStringValue(msg, "\"sessionId\"", &session) && session == pageSession) pageSession.clear();
        } else if (probeId && msg.find("{\"id\":" + std::to_string(probeId) + ",") == 0) {
            if (msg.find("\"value\":\"ok\"") != std::string::npos && !g_pageReady) {
                g_pageReady = true;
                DebugNote("page styled and drawn, ms", MsSinceStart());
            }
        }
    }
}

// The process listening on a local port, or 0.
static DWORD PortOwnerPid(int port) {
    ULONG size = 0;
    GetExtendedTcpTable(nullptr, &size, FALSE, AF_INET, TCP_TABLE_OWNER_PID_LISTENER, 0);
    std::vector<char> buffer(size + 4096);
    size = (ULONG)buffer.size();
    if (GetExtendedTcpTable(buffer.data(), &size, FALSE, AF_INET, TCP_TABLE_OWNER_PID_LISTENER, 0) != NO_ERROR) {
        return 0;
    }
    auto* table = (MIB_TCPTABLE_OWNER_PID*)buffer.data();
    for (DWORD i = 0; i < table->dwNumEntries; i++) {
        if (ntohs((u_short)table->table[i].dwLocalPort) == port) return table->table[i].dwOwningPid;
    }
    return 0;
}

static bool IsChildOfThisProcess(DWORD pid) {
    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (snapshot == INVALID_HANDLE_VALUE) return false;
    PROCESSENTRY32W entry = {sizeof(entry)};
    bool child = false;
    for (BOOL more = Process32FirstW(snapshot, &entry); more; more = Process32NextW(snapshot, &entry)) {
        if (entry.th32ProcessID == pid) {
            child = entry.th32ParentProcessID == GetCurrentProcessId();
            break;
        }
    }
    CloseHandle(snapshot);
    return child;
}

static DWORD WINAPI CdpSessionThread(LPVOID) {
    WSADATA wsa;
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) return 1;
    // The look is fixed for the life of this process: a save reopens the
    // interface, and the new process builds its own script.
    const std::string js = BuildInjectJs(SnapshotSettings());
    DWORD checkedOwner = 0;
    bool ownerIsChild = false;
    while (!StopRequested()) {
        // Windhawk runs more than one interface process (a broker, a tray
        // companion), and the mod loads in each. Only the process whose child
        // is the webview's browser holds the session: several sessions each
        // holding new pages would leave the page waiting on the slowest one.
        DWORD owner = PortOwnerPid(g_cdpPort);
        if (owner != checkedOwner) {
            checkedOwner = owner;
            ownerIsChild = owner && IsChildOfThisProcess(owner);
        }
        std::string body, wsUrl;
        // Only the webview's own browser: its version string names Edge.
        if (ownerIsChild && HttpGet(g_cdpPort, "/json/version", &body) && body.find("Edg/") != std::string::npos &&
            JsonStringValue(body, "\"webSocketDebuggerUrl\"", &wsUrl) &&
            wsUrl.find("/devtools/browser/") != std::string::npos) {
            SOCKET sock;
            if (WsConnect(g_cdpPort, wsUrl, &sock)) {
                DebugNote("debugger session open, ms", MsSinceStart());
                RunBrowserSession(sock, js);
                shutdown(sock, SD_BOTH);
                closesocket(sock);
                DebugNote("debugger session closed, ms", MsSinceStart());
            }
        }
        // Poll tightly while the webview is starting, then gently.
        DWORD pause = GetTickCount64() - g_startTick < 30000 ? 10 : 1000;
        if (!g_stopEvent || WaitForSingleObject(g_stopEvent, pause) == WAIT_OBJECT_0) break;
    }
    WSACleanup();
    return 0;
}

// The webview takes this port only if it is free. Another app holding it
// (a music player was started with 9333 on 2026-11-12) would leave the
// interface unstyled, so a free one is picked instead.
static int PickCdpPort() {
    WSADATA wsa;
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) return kCdpPort;
    // A fixed short list first, so the port stays the same from one launch to
    // the next, then any free port.
    static const int kCandidates[] = {kCdpPort, 9341, 9342, 9343, 9344, 0};
    int chosen = 0;
    for (int candidate : kCandidates) {
        if (chosen) break;
        SOCKET s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        if (s == INVALID_SOCKET) break;
        BOOL exclusive = TRUE;
        setsockopt(s, SOL_SOCKET, SO_EXCLUSIVEADDRUSE, (char*)&exclusive, sizeof(exclusive));
        sockaddr_in addr = {};
        addr.sin_family = AF_INET;
        addr.sin_port = htons((u_short)candidate);
        addr.sin_addr.s_addr = htonl(0x7f000001);
        if (bind(s, (sockaddr*)&addr, sizeof(addr)) == 0) {
            int len = sizeof(addr);
            if (getsockname(s, (sockaddr*)&addr, &len) == 0) chosen = ntohs(addr.sin_port);
        }
        closesocket(s);
    }
    WSACleanup();
    return chosen ? chosen : kCdpPort;
}

// A settings save writes the values and bumps the engine's SettingsChangeTime
// marker on the mod key. Watching that marker directly makes the
// close-and-reopen-on-save independent of settings-changed event delivery,
// which has been unreliable under the 2.0 pre-alpha.
static long long ReadModChangeTime() {
    HKEY hkey = nullptr;
    std::wstring key = L"SOFTWARE\\Windhawk\\Engine\\Mods\\";
    key += WH_MOD_ID;
    if (RegOpenKeyExW(HKEY_LOCAL_MACHINE, key.c_str(),
                      0, KEY_READ, &hkey) != ERROR_SUCCESS) {
        return -1;
    }
    DWORD type = 0;
    DWORD value = 0;
    DWORD cb = sizeof(value);
    long long result = -1;
    if (RegQueryValueExW(hkey, L"SettingsChangeTime", nullptr, &type, (BYTE*)&value, &cb) == ERROR_SUCCESS &&
        type == REG_DWORD) {
        result = (long long)value;
    }
    RegCloseKey(hkey);
    return result;
}

static BOOL SpawnRelaunchHelper();
static DWORD WINAPI StylerWorkerThread(LPVOID) {
    WSADATA wsa;
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) return 1;
    srand(GetTickCount() ^ GetCurrentProcessId());
    unsigned long long lastFullCycle = 0;
    std::optional<bool> shortcutSetting;
    long long settingsMarker = g_seenChangeTime;  // Wh_ModInit read the settings at this marker

    // Late attach: the webview may already exist when the mod loads (mod
    // enabled while the interface is open). One self-relaunch fixes that by
    // starting a fresh process that takes over from the beginning. Checked
    // immediately: a fresh boot has no webview this early, so this only
    // fires for a real mid-flight attach.
    HWND topWnd = nullptr;
    for (;;) {
        topWnd = FindWindowExW(nullptr, topWnd, L"WindhawkTauriMainUI", nullptr);
        if (!topWnd) break;
        if (IsOurMainUiWindow(topWnd)) {
            HWND webviewChild = FindWindowExW(topWnd, nullptr, L"WRY_WEBVIEW", nullptr);
            if (webviewChild) {
                InterlockedExchange(&g_relaunchRequested, 1);
                DebugNote("late attach detected");
            }
            break;
        }
    }

    for (;;) {
        // The interface window frame (title bar, blur, borders) is set by this
        // loop. Poll quickly while the window is still coming up, so the stock
        // frame never shows, then settle to once a second.
        DWORD tick = 1000;
        if (g_isUiProcess && !InterlockedExchangeAdd(&g_frameReady, 0) &&
            GetTickCount64() - g_startTick < 20000) {
            tick = 15;
        }
        DWORD wait = MsgWaitForMultipleObjectsEx(1, &g_stopEvent, tick, QS_ALLINPUT, MWMO_INPUTAVAILABLE);
        if (wait == WAIT_OBJECT_0) break;
        MSG msg;
        while (PeekMessageW(&msg, nullptr, 0, 0, PM_REMOVE)) DispatchMessageW(&msg);
        if (wait == WAIT_OBJECT_0 + 1) continue;  // the events already ran their sync

        // Outside the interface process (engine, tray) the only job is the
        // native tray dialogs: the webview theme, the save watch and the
        // relaunch helper all belong to windhawk-ui.exe.
        // Settings are re-read only when the save marker moves: a full read is
        // about forty registry reads, each logged by the engine, in every
        // process the mod runs in.
        long long changeTime = ReadModChangeTime();
        if (changeTime != settingsMarker) {
            settingsMarker = changeTime;
            Settings fresh;
            ReadSettings(&fresh);
            std::lock_guard<std::mutex> lock(g_settingsMutex);
            g_settings = fresh;
        }

        if (!g_isUiProcess) {
            Settings current = SnapshotSettings();
            g_mochaIcons = current.mochaIcons;
            HWND owner = FindWindowW(L"WindhawkDaemon", nullptr);
            if (OwnTrayWindow(owner)) {
                RefreshTrayIcon(owner, current.mochaIcons);
                if (!shortcutSetting || *shortcutSetting != current.mochaIcons) {
                    UpdateShortcutIcons(current.mochaIcons);
                    shortcutSetting = current.mochaIcons;
                }
            }
            TrayDialogPass(current);
            continue;
        }

        // Fast startup ticks only dress the window; the full cycle below runs
        // once a second as before.
        if (tick != 1000 && GetTickCount64() - lastFullCycle < 1000) {
            MainWindowPass();
            ApplyToOurWindows(SnapshotSettings());
            continue;
        }
        lastFullCycle = GetTickCount64();

        MainWindowPass();
        ApplyToOurWindows(SnapshotSettings());

        // Save watch, on the marker read above. A save bumps the engine's
        // marker; both this path and the settings-changed event feed the same
        // request flag below, so a missed event cannot swallow the restart.
        if (g_seenChangeTime == -1 || changeTime < 0) {
            if (changeTime >= 0) g_seenChangeTime = changeTime;  // record, no trigger
        } else if (changeTime != g_seenChangeTime) {
            g_seenChangeTime = changeTime;
            DebugNote("save marker bump", (long)changeTime);
            InterlockedExchange(&g_relaunchRequested, 1);
        }

        if (InterlockedExchange(&g_relaunchRequested, 0) == 1) {
            // The visible owner restarts the interface. With no visible
            // window anywhere, the process holding the hidden window does,
            // so a save with the interface in the tray still applies. The
            // helper's own mutex keeps a race between the pair harmless.
            bool ownsVisible = false;
            bool ownsAny = false;
            bool otherVisible = false;
            HWND h = nullptr;
            for (;;) {
                h = FindWindowExW(nullptr, h, L"WindhawkTauriMainUI", nullptr);
                if (!h) break;
                bool mine = IsOurMainUiWindow(h);
                bool visible = IsWindowVisible(h) != 0;
                if (mine) {
                    ownsAny = true;
                    if (visible) ownsVisible = true;
                } else if (visible) {
                    otherVisible = true;
                }
            }
            if (!(ownsVisible || (ownsAny && !otherVisible))) continue;
            // a cooldown skip must not swallow the request: re-arm and retry
            if (!SpawnRelaunchHelper()) {
                InterlockedExchange(&g_relaunchRequested, 1);
                continue;
            }
            InterlockedExchange(&g_relaunchDone, 1);
            // the helper closes this process; nothing after this matters
            continue;
        }

        // Self-heal: a fresh process whose webview environment never comes up
        // (the previous webview's browser process can hold the profile
        // singleton for a while after a restart) leaves the window open with
        // no page in it. One relaunch per process recovers it without user
        // action; the helper waits for the old webviews before restarting.
        if (!g_relaunchDone && GetTickCount64() - g_startTick > 15000) {
            bool blankWindow = false;
            HWND h = nullptr;
            for (;;) {
                h = FindWindowExW(nullptr, h, L"WindhawkTauriMainUI", nullptr);
                if (!h) break;
                if (IsOurMainUiWindow(h) && IsWindowVisible(h) &&
                    !FindWindowExW(h, nullptr, L"WRY_WEBVIEW", nullptr)) {
                    blankWindow = true;
                }
            }
            if (blankWindow && SpawnRelaunchHelper()) {
                InterlockedExchange(&g_relaunchDone, 1);
            }
        }

        // The page theme comes from the debugger session thread, which hands
        // the stylesheet to every new document before it paints.
    }


    WSACleanup();
    return 0;
}

// A save (or a late mod attach) closes and reopens the interface, like the
// 1.x editions did after patching files. A detached helper does the closing
// and the reopening so it survives this process exiting.
static BOOL SpawnRelaunchHelper() {
    // cooldown: no relaunch within 4s of the last one
    static volatile long long lastRelaunchTick = 0;
    unsigned long long now = GetTickCount64();
    long long last = lastRelaunchTick;
    if (last != 0 && now - (unsigned long long)last < 4000) return FALSE;
    // Claim the slot in one step: a second caller that read the same old tick loses here.
    if (InterlockedCompareExchange64(&lastRelaunchTick, (long long)now, last) != last) return FALSE;

    wchar_t uiPath[MAX_PATH];
    DWORD pathLength = GetModuleFileNameW(nullptr, uiPath, MAX_PATH);
    if (!pathLength || pathLength >= MAX_PATH) return FALSE;
    std::wstring quotedPath;
    for (wchar_t c : std::wstring(uiPath, pathLength)) {
        quotedPath += c;
        if (c == L'\'') quotedPath += c;
    }
    wchar_t script[4096];
    int scriptLength = _snwprintf(script, 4096,
        L"$ErrorActionPreference='SilentlyContinue'\n"
        L"$m=New-Object System.Threading.Mutex($false,'WindhawkStylerRelaunch')\n"
        L"$ok=$m.WaitOne(300)\n"
        L"if(-not $ok){exit}\n"
        L"$ps=Get-Process windhawk-ui -ErrorAction SilentlyContinue\n"
        L"foreach($p in $ps){$p.CloseMainWindow() | Out-Null}\n"
        L"$dl=(Get-Date).AddSeconds(8)\n"
        L"while((Get-Process windhawk-ui -ErrorAction SilentlyContinue) -and ((Get-Date) -lt $dl)){Start-Sleep -Milliseconds 250}\n"
        L"$bpArr=((Get-CimInstance Win32_Process -Filter \"Name='msedgewebview2.exe'\" | Where-Object { $_.CommandLine -like '*UIMainData*' }) | ForEach-Object ProcessId)\n"
        L"Get-Process windhawk-ui -ErrorAction SilentlyContinue | Stop-Process -Force\n"
        L"$dl=(Get-Date).AddSeconds(12)\n"
        L"while((($bpArr | Measure-Object).Count -gt 0) -and (((Get-Process msedgewebview2 -ErrorAction SilentlyContinue | Where-Object { $bpArr -contains $_.Id }) | Measure-Object).Count -gt 0) -and ((Get-Date) -lt $dl)){Start-Sleep -Milliseconds 250}\n"
        L"try{& '%s'}catch{}\n"
        L"Start-Sleep -Seconds 2\n"
        L"$dl2=(Get-Date).AddSeconds(6)\n"
        L"while(((Get-Process windhawk-ui -ErrorAction SilentlyContinue | Where-Object {$_.MainWindowHandle -ne 0}).Count -gt 1) -and ((Get-Date) -lt $dl2)){"
        L"(Get-Process windhawk-ui -ErrorAction SilentlyContinue | Where-Object {$_.MainWindowHandle -ne 0} | Sort-Object StartTime -Descending | Select-Object -Skip 1) | Stop-Process -Force;Start-Sleep -Milliseconds 500}\n"
        L"if(-not (Get-Process windhawk-ui -ErrorAction SilentlyContinue)){try{& '%s'}catch{}}\n"
        L"$m.ReleaseMutex()\n",
        quotedPath.c_str(), quotedPath.c_str());
    if (scriptLength < 0 || scriptLength >= 4096) return FALSE;

    // encode as UTF-16LE base64 for -EncodedCommand (no quoting traps)
    int bytes = (int)(wcslen(script) * 2);
    char* b64 = (char*)LocalAlloc(LPTR, (SIZE_T)((bytes + 2) / 3 * 4 + 1));
    if (!b64) return FALSE;
    static const char alphabet[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    const unsigned char* src = (const unsigned char*)script;
    int o = 0;
    for (int i = 0; i < bytes; i += 3) {
        int rem = bytes - i;
        std::uint32_t v = ((std::uint32_t)src[i] << 16) | (rem > 1 ? (std::uint32_t)src[i + 1] << 8 : 0) | (rem > 2 ? src[i + 2] : 0);
        b64[o++] = alphabet[(v >> 18) & 63];
        b64[o++] = alphabet[(v >> 12) & 63];
        b64[o++] = rem > 1 ? alphabet[(v >> 6) & 63] : '=';
        b64[o++] = rem > 2 ? alphabet[v & 63] : '=';
    }
    b64[o] = '\0';
    DebugNote("helper b64 len", (long)o);

    wchar_t cmdLine[16384];
    int cmdLength = _snwprintf(cmdLine, 16384,
        L"\"C:\\Windows\\System32\\WindowsPowerShell\\v1.0\\powershell.exe\" -NoProfile -ExecutionPolicy Bypass -EncodedCommand %S", b64);
    if (cmdLength < 0 || cmdLength >= 16384) {
        LocalFree(b64);
        return FALSE;
    }

    STARTUPINFOW si = {};
    si.cb = sizeof(si);
    PROCESS_INFORMATION pi = {};
    BOOL ok = CreateProcessW(nullptr, cmdLine, nullptr, nullptr, FALSE,
                             CREATE_NO_WINDOW | CREATE_BREAKAWAY_FROM_JOB, nullptr, nullptr, &si, &pi);
    if (!ok) {
        // job may not allow breakaway; retry plain
        ok = CreateProcessW(nullptr, cmdLine, nullptr, nullptr, FALSE, CREATE_NO_WINDOW, nullptr, nullptr, &si, &pi);
    }
    if (ok) {
        CloseHandle(pi.hThread);
        CloseHandle(pi.hProcess);
        DebugNote("relaunch helper spawned");
    } else {
        DebugNote("relaunch helper failed", GetLastError());
    }
    LocalFree(b64);
    return ok ? TRUE : FALSE;
}

BOOL Wh_ModInit() {
    Wh_Log(L">");

    wchar_t image[MAX_PATH];
    if (GetModuleFileNameW(nullptr, image, MAX_PATH)) {
        PCWSTR name = wcsrchr(image, L'\\');
        name = name ? name + 1 : image;
        g_isUiProcess = _wcsicmp(name, L"windhawk-ui.exe") == 0;
    }

    g_startTick = GetTickCount64();
    ReadSettings(&g_settings);
    // Seed the save watch with the marker as it stands now: a fresh boot (or
    // a hot-swap after a compile) records it without triggering, and only a
    // later bump restarts the interface.
    g_seenChangeTime = ReadModChangeTime();

    g_mochaIcons = g_settings.mochaIcons;
    if (!g_isUiProcess) {
        Wh_SetFunctionHook((void*)Shell_NotifyIconW, (void*)NotifyIconHook, (void**)&g_notifyIcon);
    }

    if (g_isUiProcess) {
        // Ask the WebView2 loader for a local debugging port, so the mod can push
        // the theme tokens and the font into the interface's own page. Must be set
        // before the webview environment is created, which is why this runs in the
        // process's earliest startup.
        {
            g_cdpPort = PickCdpPort();
            if (g_cdpPort != kCdpPort) DebugNote("port 9333 busy, debugging port", g_cdpPort);
            wchar_t args[64];
            swprintf(args, 64, L"--remote-debugging-port=%u", g_cdpPort);
            SetEnvironmentVariableW(L"WEBVIEW2_ADDITIONAL_BROWSER_ARGUMENTS", args);
        }
    }

    g_stopEvent = CreateEvent(nullptr, TRUE, FALSE, nullptr);
    if (g_stopEvent) {
        g_workerThread = CreateThread(nullptr, 0, StylerWorkerThread, nullptr, 0, nullptr);
        if (g_isUiProcess) g_cdpThread = CreateThread(nullptr, 0, CdpSessionThread, nullptr, 0, nullptr);
    }

    if (g_isUiProcess) {
        InitFrameWatch();
        if (!Wh_SetFunctionHook((void*)BitBlt, (void*)BitBlt_hook, (void**)&BitBlt_orig)) {
            DebugNote("startup splash hook failed");
        }
        PatchPutSites();
    }

    return TRUE;
}

void Wh_ModUninit() {
    Wh_Log(L">");
    DWORD disabled = 0;
    DWORD disabledSize = sizeof(disabled);
    std::wstring key = L"SOFTWARE\\Windhawk\\Engine\\Mods\\";
    key += WH_MOD_ID;
    bool reopen = RegGetValueW(HKEY_LOCAL_MACHINE, key.c_str(), L"Disabled",
                              RRF_RT_REG_DWORD, nullptr, &disabled, &disabledSize) == ERROR_SUCCESS && disabled;
    bool ownsVisible = false;
    HWND visible = nullptr;
    while ((visible = FindWindowExW(nullptr, visible, L"WindhawkTauriMainUI", nullptr))) {
        if (IsOurMainUiWindow(visible) && IsWindowVisible(visible)) ownsVisible = true;
    }
    reopen = reopen && ownsVisible;
    g_mochaIcons = false;
    InterlockedExchange(&g_themeActive, 0);
    InterlockedExchange(&g_relaunchRequested, 0);
    if (g_stopEvent) {
        SetEvent(g_stopEvent);
        if (g_workerThread) {
            // The worker can sit in a socket read for several seconds. Wait for
            // it to finish before anything is unhooked or unmapped.
            if (WaitForSingleObject(g_workerThread, 30000) != WAIT_OBJECT_0) DebugNote("worker still running at unload");
            CloseHandle(g_workerThread);
            g_workerThread = nullptr;
        }
        if (g_cdpThread) {
            if (WaitForSingleObject(g_cdpThread, 30000) != WAIT_OBJECT_0) DebugNote("session thread still running at unload");
            CloseHandle(g_cdpThread);
            g_cdpThread = nullptr;
        }
        CloseHandle(g_stopEvent);
        g_stopEvent = nullptr;
    }
    g_mochaIcons = false;
    HWND tray = FindWindowW(L"WindhawkDaemon", nullptr);
    if (OwnTrayWindow(tray)) {
        RefreshTrayIcon(tray, false);
        if (disabled) UpdateShortcutIcons(false);
    }
    // The page's injected style goes with the interface process: a disable
    // relaunches it below, and a recompile re-injects over the same style tag.
    HWND hWnd = nullptr;
    for (;;) {
        hWnd = FindWindowExW(nullptr, hWnd, L"WindhawkTauriMainUI", nullptr);
        if (!hWnd) break;
        if (IsOurMainUiWindow(hWnd)) {
            UpdateWindowIcons(hWnd, false);
            ClearWindowStack(hWnd);
        }
    }
    std::lock_guard<std::mutex> captionLock(g_captionChildrenMutex);
    for (auto& [child, size] : g_captionChildren) {
        if (IsWindow(child)) SetWindowRgn(child, nullptr, TRUE);
    }
    g_captionChildren.clear();
    std::vector<std::pair<HWND, HWND>> trayDialogs;
    std::map<HWND, LONG_PTR> trayListStyles;
    std::map<HWND, RECT> trayCards;
    {
        std::lock_guard<std::mutex> lock(g_trayDialogsMutex);
        for (const auto& [dialog, state] : g_trayDialogs) {
            trayDialogs.emplace_back(dialog, state.list);
            if (state.partsSet) trayListStyles[state.list] = state.listExStyle;
        }
    }
    {
        std::lock_guard<std::mutex> lock(g_trayCardsMutex);
        trayCards = g_trayCards;
        g_trayCards.clear();
    }
    WindhawkUtils::RemoveAllWindowSubclasses();
    for (const auto& [dialog, list] : trayDialogs) {
        if (!IsTrayTaskDialog(dialog)) continue;
        ClearWindowStack(dialog);
        DWM_WINDOW_CORNER_PREFERENCE corner = DWMWCP_DEFAULT;
        DwmSetWindowAttribute(dialog, DWMWA_WINDOW_CORNER_PREFERENCE, &corner, sizeof(corner));
        if (IsWindow(list)) {
            SendMessageW(list, LVM_SETBKCOLOR, 0, GetSysColor(COLOR_WINDOW));
            SendMessageW(list, LVM_SETTEXTBKCOLOR, 0, GetSysColor(COLOR_WINDOW));
            SendMessageW(list, LVM_SETTEXTCOLOR, 0, GetSysColor(COLOR_WINDOWTEXT));
            SendMessageW(list, WM_SETFONT, SendMessageW(dialog, WM_GETFONT, 0, 0), TRUE);
            SetWindowTheme(list, L"Explorer", nullptr);
            auto style = trayListStyles.find(list);
            if (style != trayListStyles.end()) SetWindowLongPtrW(list, GWL_EXSTYLE, style->second);
            auto card = trayCards.find(list);
            if (card != trayCards.end()) {
                const RECT& r = card->second;
                SetWindowPos(list, nullptr, r.left, r.top, r.right - r.left, r.bottom - r.top,
                             SWP_NOZORDER | SWP_NOACTIVATE | SWP_FRAMECHANGED);
            }
        }
        HideSizeGrips(dialog, false);
        RedrawWindow(dialog, nullptr, nullptr, RDW_INVALIDATE | RDW_ERASE | RDW_ALLCHILDREN | RDW_FRAME);
        SetWindowPos(dialog, nullptr, 0, 0, 0, 0,
                     SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE | SWP_FRAMECHANGED);
        RECT client{};
        GetClientRect(dialog, &client);
        SendMessageW(dialog, WM_SIZE, SIZE_RESTORED, MAKELPARAM(client.right, client.bottom));
        InvalidateRect(dialog, nullptr, TRUE);
    }
    if (g_dockHwnd) KillTimer(g_dockHwnd, kDockTimer);
    if (g_uptimeHwnd) KillTimer(g_uptimeHwnd, kUptimeTimer);
    g_uptimeHwnd = nullptr;
    DockCloseHot();
    g_mainWindows.clear();
    {
        std::lock_guard<std::mutex> lock(g_trayDialogsMutex);
        g_trayDialogs.clear();
    }
    RestorePatches();
    {
        std::lock_guard<std::mutex> lock(g_iconMutex);
        for (const auto& [size, icon] : g_icons) DestroyIcon(icon);
        g_icons.clear();
    }
    // Only a real disable reopens the visible interface, not app exit or recompilation.
    if (reopen) SpawnRelaunchHelper();
}

void Wh_ModSettingsChanged() {
    Wh_Log(L">");
    Settings s;
    ReadSettings(&s);
    {
        std::lock_guard<std::mutex> lock(g_settingsMutex);
        g_settings = s;
    }
    ApplyToOurWindows(s);
    if (g_isUiProcess) {
        // Both save paths feed the same restart request.
        InterlockedExchange(&g_relaunchRequested, 1);
    } else {
        // The pop-up colors follow a save immediately, no restart needed.
        InterlockedExchangeAdd64(&g_trayEpoch, 1);
        TrayDialogPass(s);
    }
}
