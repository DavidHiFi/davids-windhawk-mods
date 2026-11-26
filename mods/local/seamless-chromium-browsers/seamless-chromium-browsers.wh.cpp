// ==WindhawkMod==
// @id              seamless-chromium-browsers
// @name            Seamless Chromium Browsers
// @description     See-through Helium and Brave with Catppuccin colors, your own accent, font and pop-up edges
// @version         1.1.1
// @author          DavidHiFi, bardelyne
// @github          https://github.com/DavidHiFi/davids-windhawk-mods
// @homepage        https://github.com/DavidHiFi/davids-windhawk-mods
// @donateUrl       https://ko-fi.com/DavidHiFi
// @license         MIT
// @include         chrome.exe
// @include         brave.exe
// @include         msedge.exe
// @include         vivaldi.exe
// @include         thorium.exe
// @architecture    x86-64
// @compilerOptions -ldwmapi -ladvapi32 -lcomctl32 -lshell32 -luser32 -lgdi32 -lole32 -loleaut32 -lruntimeobject -luuid
// ==/WindhawkMod==

// ==WindhawkModReadme==
/*
One mod that rices Chromium browsers: a see-through window, Catppuccin
colors, your own accent pair, your own font and clean pop-up edges. Helium and
Brave each get their full look. Chrome, Edge, Vivaldi and Thorium get the font
and pop-up settings.

![Seamless Chromium Browsers preview](https://raw.githubusercontent.com/DavidHiFi/davids-windhawk-mods/main/media/previews/seamless-chromium-browsers.png)

## What's new in 1.1.0
- Pick the font weight too: light, regular, medium, semi-bold or bold.
- Sharper tray icon.
- The note about square frames round pop-ups now names the real cause:
  Helium's "Blur behind popups and menus" option. Leave it off.

## What's new in 1.0.0
- Helium Acrylic and Brave Acrylic are now this one mod. Every setting from
  both is here, in a Helium group and a Brave group.
- Pick your own accent pair. Helium's icon and its gradient pieces follow it.
- Pick the browser's font and size. Tabs, menus, the address bar and dialogs
  follow after a browser restart.
- Pick the corners and edge color of pop-ups that Windows draws.
- Your Helium Acrylic and Brave Acrylic settings carry over.

## Helium
- Keeps Helium see-through so the window blur shows, even after a browser
  update washes the look out.
- Every color is a setting: base, toolbar, address bar, suggestions, tabs,
  text and the focus outline. Changes show at once.
- Windows draws the title bar and keeps the resize borders.
- Helium's logo repainted in your accent pair, on the title bar, the taskbar
  and your shortcuts.
- Nothing in the browser's files is changed. If an update moves the code the
  mod looks for, that part does nothing and says why in the log.

## Brave
- Shows the Windows backdrop through the tab area, toolbar, address bar and
  the page background, with blurred menus, pop-ups and search suggestions.
- Needs the [Translucent Windows](https://windhawk.net/mods/translucent-windows)
  mod set up for `brave.exe`, and Windows transparency effects on. This mod
  opens the background; Translucent Windows adds the blur.
- Restart Brave after turning the mod on or changing a Brave setting.
- It finds its way around each Brave build with small files from a cache run
  by bardelyne, the author of Brave Acrylic. Downloading Brave's full symbols
  instead is off by default (about 1.2 GB). The tray icon tells you when
  Brave needs a restart. Turn both download settings off to stay offline.
- Website backgrounds stay as the site draws them. A styling extension such as
  Zen Internet or Stylus can clear those.

## Every Chromium browser
- Browser font, size and weight, read when the browser starts.
- Pop-up corners and edge color, for the pop-ups Windows draws whole.

## Notes
- A square grey frame round menus and extension pop-ups comes from Helium's
  "Blur behind popups and menus" option. It is off by default; keep it off
  for clean rounded pop-ups.
- Light theme stays stock in Helium.

## Credits
- Helium part and the shared layer: DavidHiFi.
- Brave part: [Brave Acrylic](https://github.com/bardelyne/brave-acrylic) 4.0
  by [bardelyne](https://github.com/bardelyne), MIT license. Thank you.
*/
// ==/WindhawkModReadme==

// ==WindhawkModSettings==
/*
- accentStart: "#89B4FA"
  $name: Accent start color
  $description: "Where the accent gradient starts (Mocha Blue). Helium's icon and its gradient pieces use it."
- accentEnd: "#CBA6F7"
  $name: Accent end color
  $description: "Where the accent gradient ends (Mocha Mauve)."
- uiFont: FiraCode Nerd Font
  $name: Browser font
  $description: "The font for tabs, menus, the address bar and dialogs. Leave empty to keep the browser's own. Needs a browser restart."
- uiFontSize: 0
  $name: Browser font size (pt)
  $description: "1 to 32. 0 keeps the browser's own size. Needs a browser restart."
- uiFontWeight: medium
  $name: Browser font weight
  $description: "How thick the browser font is drawn. Needs a browser restart."
  $options:
  - stock: Keep the browser's own
  - light: Light
  - regular: Regular
  - medium: Medium
  - semibold: Semi-bold
  - bold: Bold
- popupCorners: stock
  $name: Pop-up corners
  $description: "For pop-ups Windows draws whole, like some menus and dialogs. Pop-ups the browser draws with a soft shadow keep their own shape."
  $options:
  - stock: Keep the browser's own
  - round: Round
  - small: Slightly round
  - square: Square
- popupEdge: stock
  $name: Pop-up edge
  $description: "The thin line Windows draws round those same pop-ups."
  $options:
  - stock: Keep the browser's own
  - none: No edge
  - custom: The color below
- popupEdgeColor: "#45475A"
  $name: Pop-up edge color
  $description: "Used when the pop-up edge is set to the color below (Mocha Surface1)."
- helium:
  - acrylicEnabled: true
    $name: Keep the acrylic surface
    $description: "Keeps the browser see-through so the window blur shows. Applies at once."
  - colorsEnabled: true
    $name: Keep the Catppuccin colors
    $description: "Resolves the browser's dark colors to the palette below. Applies at once."
  - colorBase: "#1E1E2E"
    $name: Base color
    $description: "Window frame and toolbar background (Mocha Base)."
  - colorToolbarIcon: "#A6ADC8"
    $name: Toolbar icon color
    $description: "Toolbar buttons at rest (Mocha Subtext)."
  - colorToolbarIconHover: "#CDD6F4"
    $name: Toolbar icon hover color
    $description: "Toolbar buttons under the mouse (Mocha Text)."
  - colorLocationBar: "#313244"
    $name: Address bar color
    $description: "Address bar background (Mocha Surface0)."
  - locationBarOpacity: 85
    $name: Address bar strength (%)
    $description: "0 to 100. Lower shows more of the page behind."
  - colorLocationBarHover: "#45475A"
    $name: Address bar hover color
    $description: "Address bar background with the mouse in it (Mocha Surface1)."
  - colorLocationBarBorder: "#585B70"
    $name: Address bar edge color
    $description: "The line around the address bar (Mocha Surface2)."
  - colorOmniboxResults: "#181825"
    $name: Suggestions background
    $description: "The drop-down under the address bar (Mocha Mantle)."
  - colorOmniboxResultsHover: "#313244"
    $name: Suggestions hover background
    $description: "The highlighted suggestion (Mocha Surface0)."
  - colorOmniboxText: "#CDD6F4"
    $name: Address bar text color
    $description: "What you type and the suggestions (Mocha Text)."
  - colorOmniboxTextDim: "#7F849C"
    $name: Address bar dim text color
    $description: "The dimmed part, like the search hint (Mocha Overlay)."
  - colorTabActive: "#313244"
    $name: Active tab color
    $description: "The tab of the page you are on (Mocha Surface0)."
  - tabActiveOpacity: 85
    $name: Active tab strength (%)
    $description: "0 to 100. Lower shows more of the page behind."
  - colorTabSelected: "#313244"
    $name: Selected tab color
    $description: "Tabs picked in the tab strip (Mocha Surface0)."
  - tabSelectedOpacity: 69
    $name: Selected tab strength (%)
    $description: "0 to 100. Lower shows more of the page behind."
  - colorTabHover: "#313244"
    $name: Tab hover color
    $description: "A tab under the mouse (Mocha Surface0)."
  - tabInactiveHoverOpacity: 60
    $name: Tab hover strength (%)
    $description: "0 to 100. Lower shows more of the page behind."
  - colorTabTextActive: "#CDD6F4"
    $name: Active tab text color
    $description: "The title on the current tab (Mocha Text)."
  - colorTabTextInactive: "#A6ADC8"
    $name: Background tab text color
    $description: "Titles on the other tabs (Mocha Subtext)."
  - colorTabStroke: "#585B70"
    $name: Tab edge color
    $description: "The line between tabs (Mocha Surface2)."
  - colorFocusBorder: "#B4BEFE"
    $name: Focus outline color
    $description: "The outline on a focused control (Mocha Lavender)."
  - nativeFrameEnabled: true
    $name: Keep the system title bar
    $description: "Windows draws the title bar and keeps the resize borders. Applies at once."
  - popupAcrylic: false
    $name: Blur behind popups and menus
    $description: "Off keeps rounded popups clean. On also blurs menus and extension popups, but Windows then draws a square frosted frame around them. Applies at once."
  - appIcon: gradient
    $name: App icon
    $description: "The icon in the title bar, on the taskbar and on your Start menu, desktop and taskbar shortcuts."
    $options:
    - gradient: Helium logo, blue to mauve
    - default: Helium's own icon
  $name: Helium
  $description: "Everything the Helium browser gets: see-through surface, colors, the system title bar and the icon."
- brave:
  - transparentBackground: true
    $name: Vertical tabs background
    $description: Reveal the backdrop behind the vertical tab area and browser frame.
  - transparentToolbar: true
    $name: Toolbar
    $description: Reveal the backdrop behind the toolbar and bookmarks bar.
  - transparentAddressBar: true
    $name: Address bar
    $description: Clear the unfocused address field and, where supported, its hover shadow. The focused field keeps its native appearance.
  - transparentPageBackground: true
    $name: Webpage background
    $description: Clear Chromium's webpage backing, including its default white fallback and the fill behind rounded content. The rounded outline and website content stay intact. Use Zen Internet or custom CSS with Stylus for website backgrounds.
  - blurMenus: true
    $name: Acrylic menus
    $description: Blur native context menus and submenus while preserving their theme, rounded corners, text and input.
  - blurPopups: true
    $name: Acrylic popups
    $description: Blur supported native browser bubbles such as Site information, Recent downloads and Media controls. Extension and website HTML popups keep their own styling.
  - blurSuggestions: true
    $name: Blur search suggestions
    $description: Blur address-bar suggestions below the input field. Typed text, result text and selection stay sharp.
  - popupOpacity: 62
    $name: Popup background opacity (%)
    #! $min: 0
    #! $max: 100
    $description: "Background tint for menus, native popups and search suggestions. 0 is transparent and 100 is opaque; text, icons and controls stay fully visible."
  - hideNativeCaptionButtons: true
    $name: Hide duplicate Windows buttons
    $description: Hide the extra Windows minimize, maximize and close buttons while keeping Brave’s controls. This removes the Windows system-menu style and can affect Alt+Space, taskbar menus, accessibility tools and window managers. Applies immediately.
  - useOnlineSymbolCache: true
    $name: Use online symbol cache
    $description: Download small compatibility files from the author-controlled symbol cache. GitHub sees your IP and requested build URLs. Restart Brave after applying changes.
  - allowBraveSymbolServerFallback: false
    $name: Download symbols from Brave as a fallback
    $description: If the cache cannot resolve symbols, let Windhawk download the full PDB from Brave’s official symbol server. Brave continues after five seconds if symbols are still loading. The tray icon tells you when to restart. One tested build downloaded about 1.2 GB and used 6.2 GB on disk.
  $name: Brave
  $description: "Everything Brave gets. Needs the Translucent Windows mod set up for brave.exe. Restart Brave after changes."
*/
// ==/WindhawkModSettings==

#include <windows.h>
#include <commctrl.h>
#include <dwmapi.h>
#include <memory>
#include <unordered_map>
#include <winrt/Windows.System.h>
#include <winrt/Windows.UI.Composition.h>
#include <winrt/Windows.UI.Composition.Desktop.h>
#include <windhawk_api.h>
#include <shellapi.h>
#include <atomic>
#include <cwchar>
#include <cstring>
#include <windhawk_utils.h>
#include <roapi.h>
#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.Foundation.Collections.h>
#include <algorithm>
#include <array>
#include <cmath>
#include <vector>
#include <chrono>
#include <cstddef>
#include <string>
#include <string_view>
#include <shlobj.h>
#include <shobjidl.h>
#include <propsys.h>
#include <map>
#include <cstdarg>
#include <cstdio>
#include <cwctype>

// Crisp icons (2026-11-26): tray icons are drawn at 4x the size the taskbar shows them and shrunk
// here with a box filter, so curves and glyph edges are smooth instead of stretched and stepped.
// The result carries straight alpha, which is what Windows expects in an icon.
static HICON Crisp_ShrinkIcon(HICON big, int factor) {
    if (!big || factor <= 1) return big;
    ICONINFO ii{};
    if (!GetIconInfo(big, &ii)) return big;
    HICON out = nullptr;
    BITMAP bm{};
    if (ii.hbmColor && GetObjectW(ii.hbmColor, sizeof(bm), &bm) && bm.bmWidth == bm.bmHeight &&
        bm.bmWidth >= factor && bm.bmWidth % factor == 0) {
        const int src = bm.bmWidth, n = src / factor;
        BITMAPINFO bi{};
        bi.bmiHeader.biSize = sizeof(bi.bmiHeader);
        bi.bmiHeader.biWidth = src;
        bi.bmiHeader.biHeight = -src;
        bi.bmiHeader.biPlanes = 1;
        bi.bmiHeader.biBitCount = 32;
        bi.bmiHeader.biCompression = BI_RGB;
        unsigned int* in = new unsigned int[(size_t)src * src];
        HDC screen = GetDC(nullptr);
        if (GetDIBits(screen, ii.hbmColor, 0, src, in, &bi, DIB_RGB_COLORS) == src) {
            bool premul = true, anyAlpha = false;
            for (size_t i = 0; i < (size_t)src * src; i++) {
                unsigned int p = in[i], a = p >> 24;
                if (a) anyAlpha = true;
                if (((p >> 16) & 0xFF) > a || ((p >> 8) & 0xFF) > a || (p & 0xFF) > a) premul = false;
            }
            void* bits = nullptr;
            bi.bmiHeader.biWidth = n;
            bi.bmiHeader.biHeight = -n;
            HBITMAP color = anyAlpha ? CreateDIBSection(screen, &bi, DIB_RGB_COLORS, &bits, nullptr, 0) : nullptr;
            if (color && bits) {
                unsigned int* px = (unsigned int*)bits;
                const unsigned int cnt = (unsigned int)(factor * factor);
                for (int y = 0; y < n; y++)
                    for (int x = 0; x < n; x++) {
                        unsigned int sa = 0, sr = 0, sg = 0, sb = 0;
                        for (int dy = 0; dy < factor; dy++)
                            for (int dx = 0; dx < factor; dx++) {
                                unsigned int p = in[(size_t)(y * factor + dy) * src + x * factor + dx], a = p >> 24;
                                unsigned int r = (p >> 16) & 0xFF, g = (p >> 8) & 0xFF, b = p & 0xFF;
                                if (!premul) {
                                    r = (r * a + 127) / 255;
                                    g = (g * a + 127) / 255;
                                    b = (b * a + 127) / 255;
                                }
                                sa += a; sr += r; sg += g; sb += b;
                            }
                        unsigned int a = (sa + cnt / 2) / cnt, r = 0, g = 0, b = 0;
                        if (a && sa) {
                            r = (sr * 255 + sa / 2) / sa; if (r > 255) r = 255;
                            g = (sg * 255 + sa / 2) / sa; if (g > 255) g = 255;
                            b = (sb * 255 + sa / 2) / sa; if (b > 255) b = 255;
                        }
                        px[(size_t)y * n + x] = a ? ((a << 24) | (r << 16) | (g << 8) | b) : 0;
                    }
                // A zero mask: with 32-bit colour Windows draws from the alpha channel.
                unsigned char* maskBits = new unsigned char[(size_t)((n + 15) / 16) * 2 * n]();
                HBITMAP mask = CreateBitmap(n, n, 1, 1, maskBits);
                delete[] maskBits;
                if (mask) {
                    ICONINFO o{TRUE, 0, 0, mask, color};
                    out = CreateIconIndirect(&o);
                    DeleteObject(mask);
                }
            }
            if (color) DeleteObject(color);
        }
        ReleaseDC(nullptr, screen);
        delete[] in;
    }
    if (ii.hbmColor) DeleteObject(ii.hbmColor);
    if (ii.hbmMask) DeleteObject(ii.hbmMask);
    if (!out) return big;
    DestroyIcon(big);
    return out;
}


// ---------------------------------------------------------------------------
// Shared layer, every Chromium browser this mod loads into (browser process).
// Pop-up corners and edge, the UI font, and the accent pair the Helium engine
// reads. Written by DavidHiFi.
// ---------------------------------------------------------------------------
namespace Common {

enum class Corners { Stock, Round, Small, Square };
enum class Edge { Stock, None, Custom };

struct Settings {
    Corners corners = Corners::Stock;
    Edge edge = Edge::Stock;
    COLORREF edgeColor = RGB(0x45, 0x47, 0x5A);
    std::wstring font;
    int fontSize = 0;
    int fontWeight = 0;
};
static Settings g_set;
static SRWLOCK g_lock = SRWLOCK_INIT;

static bool ParseHex(PCWSTR s, unsigned int* out) {
    if (!s) return false;
    while (*s == L' ' || *s == L'#') s++;
    if (wcslen(s) != 6) return false;
    for (int i = 0; i < 6; i++)
        if (!iswxdigit(s[i])) return false;
    *out = (unsigned int)wcstoul(s, nullptr, 16);
    return true;
}

static std::wstring ReadString(PCWSTR name) {
    PCWSTR v = Wh_GetStringSetting(name);
    std::wstring s = v ? v : L"";
    Wh_FreeStringSetting(v);
    return s;
}

static void Load() {
    Settings s;
    std::wstring c = ReadString(L"popupCorners");
    s.corners = c == L"round" ? Corners::Round : c == L"small" ? Corners::Small
              : c == L"square" ? Corners::Square : Corners::Stock;
    std::wstring e = ReadString(L"popupEdge");
    s.edge = e == L"custom" ? Edge::Custom : e == L"none" ? Edge::None : Edge::Stock;
    unsigned int rgb;
    if (ParseHex(ReadString(L"popupEdgeColor").c_str(), &rgb))
        s.edgeColor = RGB((rgb >> 16) & 0xFF, (rgb >> 8) & 0xFF, rgb & 0xFF);
    s.font = ReadString(L"uiFont");
    while (!s.font.empty() && s.font.back() == L' ') s.font.pop_back();
    s.fontSize = Wh_GetIntSetting(L"uiFontSize");
    std::wstring w = ReadString(L"uiFontWeight");
    s.fontWeight = w == L"light" ? 300 : w == L"regular" ? 400 : w == L"medium" ? 500
                 : w == L"semibold" ? 600 : w == L"bold" ? 700 : 0;
    if (s.fontSize < 0 || s.fontSize > 32) s.fontSize = 0;
    AcquireSRWLockExclusive(&g_lock);
    g_set = s;
    ReleaseSRWLockExclusive(&g_lock);
}

static Settings Snapshot() {
    AcquireSRWLockShared(&g_lock);
    Settings s = g_set;
    ReleaseSRWLockShared(&g_lock);
    return s;
}

// --- UI font -----------------------------------------------------------------
// Chromium builds its default UI font from the system message font, read once
// at start. Swapping the face (and size) there changes tabs, menus, the
// address bar and dialogs together. Needs a browser restart.
static std::wstring g_fontAtInit;
static int g_fontSizeAtInit = 0;
static int g_fontWeightAtInit = 0;

static void PatchLogFont(LOGFONTW& lf, int dpi) {
    if (!g_fontAtInit.empty()) {
        wcsncpy_s(lf.lfFaceName, g_fontAtInit.c_str(), _TRUNCATE);
    }
    if (g_fontSizeAtInit > 0) {
        lf.lfHeight = -MulDiv(g_fontSizeAtInit, dpi, 72);
        lf.lfWidth = 0;
    }
    if (g_fontWeightAtInit > 0) lf.lfWeight = g_fontWeightAtInit;
}

static void PatchMetrics(PVOID p, UINT cb, int dpi) {
    if (!p || cb < offsetof(NONCLIENTMETRICSW, lfMessageFont) + sizeof(LOGFONTW)) return;
    auto* m = (NONCLIENTMETRICSW*)p;
    PatchLogFont(m->lfMessageFont, dpi);
    PatchLogFont(m->lfMenuFont, dpi);
    PatchLogFont(m->lfStatusFont, dpi);
    PatchLogFont(m->lfCaptionFont, dpi);
    PatchLogFont(m->lfSmCaptionFont, dpi);
}

using SPI_t = BOOL(WINAPI*)(UINT, UINT, PVOID, UINT);
using SPIForDpi_t = BOOL(WINAPI*)(UINT, UINT, PVOID, UINT, UINT);
static SPI_t SPI_orig;
static SPIForDpi_t SPIForDpi_orig;

static BOOL WINAPI SPI_hook(UINT action, UINT param, PVOID pv, UINT ini) {
    BOOL ok = SPI_orig(action, param, pv, ini);
    if (ok && pv) {
        if (action == SPI_GETNONCLIENTMETRICS) PatchMetrics(pv, param, 96);
        else if (action == SPI_GETICONTITLELOGFONT) PatchLogFont(*(LOGFONTW*)pv, 96);
    }
    return ok;
}

static BOOL WINAPI SPIForDpi_hook(UINT action, UINT param, PVOID pv, UINT ini, UINT dpi) {
    BOOL ok = SPIForDpi_orig(action, param, pv, ini, dpi);
    if (ok && pv) {
        if (action == SPI_GETNONCLIENTMETRICS) PatchMetrics(pv, param, (int)dpi);
        else if (action == SPI_GETICONTITLELOGFONT) PatchLogFont(*(LOGFONTW*)pv, (int)dpi);
    }
    return ok;
}

static void InstallFontHooks() {
    Settings s = Snapshot();
    g_fontAtInit = s.font;
    g_fontSizeAtInit = s.fontSize;
    g_fontWeightAtInit = s.fontWeight;
    if (g_fontAtInit.empty() && g_fontSizeAtInit == 0 && g_fontWeightAtInit == 0) return;
    HMODULE user32 = GetModuleHandleW(L"user32.dll");
    if (!user32) return;
    if (auto f = (SPI_t)GetProcAddress(user32, "SystemParametersInfoW"))
        Wh_SetFunctionHook((void*)f, (void*)SPI_hook, (void**)&SPI_orig);
    if (auto f = (SPIForDpi_t)GetProcAddress(user32, "SystemParametersInfoForDpi"))
        Wh_SetFunctionHook((void*)f, (void*)SPIForDpi_hook, (void**)&SPIForDpi_orig);
    Wh_Log(L"UI font: '%s' size %d weight %d", g_fontAtInit.c_str(), g_fontSizeAtInit,
           g_fontWeightAtInit);
}

// --- Pop-up corners and edge --------------------------------------------------
// Only pop-ups Windows draws whole (no see-through shadow margin): their window
// edge is the edge you see, so Windows' rounding and edge line land on it. A
// pop-up with a soft shadow margin is drawn by the browser itself and left alone.
static constexpr DWORD kCornerAttr = 33;   // DWMWA_WINDOW_CORNER_PREFERENCE
static constexpr DWORD kBorderAttr = 34;   // DWMWA_BORDER_COLOR
static std::vector<HWND> g_touched;
static HANDLE g_thread = nullptr;
static DWORD g_threadId = 0;
static HWINEVENTHOOK g_hook = nullptr;
static std::atomic<bool> g_stop{false};

static bool IsBrowserPopup(HWND h) {
    wchar_t cls[64];
    if (!GetClassNameW(h, cls, 64) || wcsncmp(cls, L"Chrome_WidgetWin_", 17) != 0) return false;
    LONG st = GetWindowLongW(h, GWL_STYLE);
    LONG ex = GetWindowLongW(h, GWL_EXSTYLE);
    if (!(st & WS_POPUP) || (st & (WS_CAPTION | WS_THICKFRAME))) return false;
    if (ex & (WS_EX_APPWINDOW | WS_EX_NOREDIRECTIONBITMAP)) return false;
    RECT r;
    if (!GetWindowRect(h, &r) || r.right - r.left < 24 || r.bottom - r.top < 16) return false;
    return true;
}

static void Restore(HWND h) {
    if (!IsWindow(h)) return;
    DWORD corner = 0;  // DWMWCP_DEFAULT
    COLORREF border = 0xFFFFFFFF;  // DWMWA_COLOR_DEFAULT
    DwmSetWindowAttribute(h, kCornerAttr, &corner, sizeof(corner));
    DwmSetWindowAttribute(h, kBorderAttr, &border, sizeof(border));
}

static void Apply(HWND h, const Settings& s) {
    if (!IsBrowserPopup(h)) return;
    bool touched = false;
    if (s.corners != Corners::Stock) {
        DWORD v = s.corners == Corners::Round ? 2 : s.corners == Corners::Small ? 3 : 1;
        DwmSetWindowAttribute(h, kCornerAttr, &v, sizeof(v));
        touched = true;
    }
    if (s.edge != Edge::Stock) {
        COLORREF c = s.edge == Edge::None ? 0xFFFFFFFE : s.edgeColor;
        DwmSetWindowAttribute(h, kBorderAttr, &c, sizeof(c));
        touched = true;
    }
    if (touched && std::find(g_touched.begin(), g_touched.end(), h) == g_touched.end()) {
        g_touched.erase(std::remove_if(g_touched.begin(), g_touched.end(),
                                       [](HWND w) { return !IsWindow(w); }), g_touched.end());
        g_touched.push_back(h);
    }
}

static BOOL CALLBACK ApplyEnum(HWND h, LPARAM lp) {
    DWORD pid = 0;
    GetWindowThreadProcessId(h, &pid);
    if (pid == GetCurrentProcessId()) Apply(h, *(const Settings*)lp);
    return TRUE;
}

static void CALLBACK OnShow(HWINEVENTHOOK, DWORD, HWND h, LONG obj, LONG child, DWORD, DWORD) {
    if (g_stop || obj != OBJID_WINDOW || child != CHILDID_SELF || !h) return;
    Settings s = Snapshot();
    if (s.corners == Corners::Stock && s.edge == Edge::Stock) return;
    Apply(h, s);
}

static constexpr UINT kReapply = WM_APP + 41;

static DWORD WINAPI PopupThread(LPVOID) {
    MSG msg;
    PeekMessageW(&msg, nullptr, 0, 0, PM_NOREMOVE);  // make the queue
    g_hook = SetWinEventHook(EVENT_OBJECT_SHOW, EVENT_OBJECT_SHOW, nullptr, OnShow,
                             GetCurrentProcessId(), 0, WINEVENT_OUTOFCONTEXT);
    Settings s = Snapshot();
    EnumWindows(ApplyEnum, (LPARAM)&s);
    while (GetMessageW(&msg, nullptr, 0, 0) > 0) {
        if (msg.message == kReapply) {
            Settings now = Snapshot();
            for (HWND h : g_touched) Restore(h);
            g_touched.clear();
            EnumWindows(ApplyEnum, (LPARAM)&now);
            continue;
        }
        DispatchMessageW(&msg);
    }
    if (g_hook) UnhookWinEvent(g_hook);
    g_hook = nullptr;
    for (HWND h : g_touched) Restore(h);
    g_touched.clear();
    return 0;
}

static void Init() {
    Load();
    InstallFontHooks();
    g_thread = CreateThread(nullptr, 0, PopupThread, nullptr, 0, &g_threadId);
}

static void SettingsChanged() {
    Load();
    if (g_threadId) PostThreadMessageW(g_threadId, kReapply, 0, 0);
}

static void Stop() {
    g_stop = true;
    if (!g_thread) return;
    PostThreadMessageW(g_threadId, WM_QUIT, 0, 0);
    WaitForSingleObject(g_thread, 3000);
    CloseHandle(g_thread);
    g_thread = nullptr;
    g_threadId = 0;
}

}  // namespace Common

namespace HeliumEngine {

// Settings for this engine live in the "helium" group.
static int Wh_GetIntSetting(PCWSTR name, ...) {
    wchar_t buf[256];
    va_list a;
    va_start(a, name);
    _vsnwprintf_s(buf, 256, _TRUNCATE, name, a);
    va_end(a);
    return ::Wh_GetIntSetting(L"helium.%s", buf);
}

static PCWSTR Wh_GetStringSetting(PCWSTR name, ...) {
    wchar_t buf[256];
    va_list a;
    va_start(a, name);
    _vsnwprintf_s(buf, 256, _TRUNCATE, name, a);
    va_end(a);
    return ::Wh_GetStringSetting(L"helium.%s", buf);
}

// The accent pair, Mocha Blue 0x89B4FA to Mauve 0xCBA6F7 unless set.
static std::atomic<unsigned int> g_accentA{0x89B4FA};
static std::atomic<unsigned int> g_accentB{0xCBA6F7};

static void AccentFloats(float* c0, float* c1, float div) {
    unsigned int a = g_accentA.load(), b = g_accentB.load();
    for (int i = 0; i < 3; i++) {
        c0[i] = ((a >> (16 - 8 * i)) & 0xFF) / div;
        c1[i] = ((b >> (16 - 8 * i)) & 0xFF) / div;
    }
}

// ---------------------------------------------------------------------------
// Part 1: the acrylic patch.
//
// Helium's ShouldWindowContentsBeTransparent on a stock release build:
//   cmp qword ptr [rcx+0x2C8], 0   ; browser_view_ (CHECK)
//   je  +3                         ; -> ud2 abort block
//   xor eax, eax                   ; return false
//   ret
// Verified 2026-11-08 against the stock 0.21.1.1 chrome.dll (exactly one
// match, address present in the class vtable, abort lands on ud2).
// Patched to  mov al,1 ; ret  so the compositor keeps an alpha channel.
// If a future Helium moves the member offset, update the C8 02 00 00 bytes.
static const char kAcrylicPattern[] =
    "48 83 B9 C8 02 00 00 00 74 03 31 C0 C3";

static std::atomic<bool> g_stop{false};
// v3.9.0: every loop waits on this instead of a bare Sleep, so a disable
// wakes them at once, and unload waits for them before the DLL goes away.
static HANDLE g_stopEvent = nullptr;
static HANDLE g_threads[16];
static std::atomic<int> g_threadCount{0};

static void StartModThread(LPTHREAD_START_ROUTINE fn) {
    HANDLE h = CreateThread(nullptr, 0, fn, nullptr, 0, nullptr);
    if (!h) return;
    int i = g_threadCount.fetch_add(1);
    if (i < 16) g_threads[i] = h;
    else CloseHandle(h);
}

// True when the mod is stopping.
static bool WaitOrStop(DWORD ms) {
    if (g_stopEvent) return WaitForSingleObject(g_stopEvent, ms) == WAIT_OBJECT_0 || g_stop;
    Sleep(ms);
    return g_stop;
}

static std::atomic<bool> g_acrylicApplied{false};
static BYTE g_acrylicOriginal[3];
static BYTE* g_acrylicTarget = nullptr;

// ---------------------------------------------------------------------------
// Part 2: the Catppuccin color layer.
//
// ui::ColorProvider::GetColor resolves every UI color. On the stock static
// build it compiles to this shape (verified 2026-11-08, exactly one match):
static const char kGetColorPattern[] =
    "41 57 41 56 41 54 56 57 55 53 48 83 EC 20 89 D7 48 89 CE 4C 8D 71 18 48 8B 41 18";
// We displace the first seven bytes (push r15; push r14; push r12; push rsi),
// detour the entry to a generated hook, and on a cache-miss replay those
// seven bytes and jump back. The stock dark default is returned untouched.

// The rice's mixer table, extracted 2026-11-08 from the riced 0.21.1.1 build's
// inlined AddHeliumCatppuccinMochaMixer (id, color) pairs - ground truth.
struct ColorEntry { unsigned int id; unsigned int color; };
static const ColorEntry kColors[] = {
    {321,  0xFF1E1E2Eu},   // kColorFrameActive -> base
    {326,  0xFF1E1E2Eu},   // kColorFrameInactive -> base
    {1597, 0xFF1E1E2Eu},   // kColorToolbar -> base
    {1602, 0xFFA6ADC8u},   // kColorToolbarButtonIcon -> subtext0
    {1605, 0xFFCDD6F4u},   // kColorToolbarButtonIconHovered -> text
    {801,  0xD9313244u},   // kColorLocationBarBackground -> surface0 85%
    {802,  0xD945475Au},   // kColorLocationBarBackgroundHovered -> surface1 85%
    {803,  0xFF585B70u},   // kColorLocationBarBorder -> surface2
    {1020, 0xFF181825u},   // kColorOmniboxResultsBackground -> mantle
    {1021, 0xFF313244u},   // kColorOmniboxResultsBackgroundHovered -> surface0
    {1062, 0xFFCDD6F4u},   // kColorOmniboxText -> text
    {1063, 0xFF7F849Cu},   // kColorOmniboxTextDimmed -> overlay1
    {1466, 0xD9313244u},   // kColorTabBackgroundActiveFrameActive
    {1468, 0xD9313244u},   // kColorTabBackgroundActiveFrameInactive
    {1473, 0xB0313244u},   // kColorTabBackgroundSelectedFrameActive
    {1474, 0xB0313244u},   // kColorTabBackgroundSelectedFrameInactive
    {1471, 0x99313244u},   // kColorTabBackgroundInactiveHoverFrameActive
    {1472, 0x99313244u},   // kColorTabBackgroundInactiveHoverFrameInactive
    {1483, 0xFFCDD6F4u},   // kColorTabForegroundActiveFrameActive
    {1484, 0xFFCDD6F4u},   // kColorTabForegroundActiveFrameInactive
    {1485, 0xFFA6ADC8u},   // kColorTabForegroundInactiveFrameActive
    {1486, 0xFFA6ADC8u},   // kColorTabForegroundInactiveFrameInactive
    {1538, 0xFF585B70u},   // kColorTabStrokeFrameActive
    {1539, 0xFF585B70u},   // kColorTabStrokeFrameInactive
    {319,  0xFFB4BEFEu},   // kColorFocusableBorderFocused -> lavender
};
static const int kColorCount = sizeof(kColors) / sizeof(kColors[0]);

// ---------------------------------------------------------------------------
// Settings. Every layer can be switched, the palette is the owner's copy of
// the rice's mixer table, and the app icon can become the Seamless badge.
struct Settings {
    bool acrylic = true;
    bool colors = true;
    bool nativeFrame = true;
    bool gradientIcon = true;
    bool popupAcrylic = false;
};
static Settings g_set;
static std::vector<ColorEntry> g_liveColors;

static unsigned int ParseHexColor(PCWSTR s, unsigned int fallback, BYTE alpha) {
    if (!s) return fallback;
    while (*s == L' ' || *s == L'#') s++;
    if (wcslen(s) != 6) return fallback;
    for (int i = 0; i < 6; i++) {
        wchar_t c = s[i];
        if (!((c >= L'0' && c <= L'9') || (c >= L'a' && c <= L'f') ||
              (c >= L'A' && c <= L'F')))
            return fallback;
    }
    unsigned long v = wcstoul(s, nullptr, 16);
    return ((unsigned int)alpha << 24) | (unsigned int)v;
}

static BYTE OpacityByte(int pct) {
    if (pct < 0) pct = 0;
    if (pct > 100) pct = 100;
    return (BYTE)(pct * 255 / 100);
}

static void LoadSettings() {
    Settings s;
    s.acrylic = Wh_GetIntSetting(L"acrylicEnabled") != 0;
    s.colors = Wh_GetIntSetting(L"colorsEnabled") != 0;
    s.nativeFrame = Wh_GetIntSetting(L"nativeFrameEnabled") != 0;
    s.popupAcrylic = Wh_GetIntSetting(L"popupAcrylic") != 0;
    PCWSTR icon = Wh_GetStringSetting(L"appIcon");
    s.gradientIcon = !icon || wcscmp(icon, L"default") != 0;
    if (icon) Wh_FreeStringSetting(icon);
    g_set = s;

    auto colorOf = [](PCWSTR name, unsigned int fallback, BYTE alpha) -> unsigned int {
        PCWSTR v = Wh_GetStringSetting(name);
        unsigned int out = ParseHexColor(v, fallback, alpha);
        Wh_FreeStringSetting(v);
        return out;
    };
    BYTE aLoc  = OpacityByte(Wh_GetIntSetting(L"locationBarOpacity"));
    BYTE aTabA = OpacityByte(Wh_GetIntSetting(L"tabActiveOpacity"));
    BYTE aTabS = OpacityByte(Wh_GetIntSetting(L"tabSelectedOpacity"));
    BYTE aTabH = OpacityByte(Wh_GetIntSetting(L"tabInactiveHoverOpacity"));
    unsigned int base = colorOf(L"colorBase", 0xFF1E1E2Eu, 0xFF);
    unsigned int tabSel = colorOf(L"colorTabSelected", 0xFF313244u, aTabS);
    unsigned int tabHov = colorOf(L"colorTabHover", 0xFF313244u, aTabH);
    unsigned int tabTxtA = colorOf(L"colorTabTextActive", 0xFFCDD6F4u, 0xFF);
    unsigned int tabTxtI = colorOf(L"colorTabTextInactive", 0xFFA6ADC8u, 0xFF);
    unsigned int tabStrk = colorOf(L"colorTabStroke", 0xFF585B70u, 0xFF);
    std::vector<ColorEntry> c;
    c.push_back({321,  base});
    c.push_back({326,  base});
    c.push_back({1597, base});
    c.push_back({1602, colorOf(L"colorToolbarIcon", 0xFFA6ADC8u, 0xFF)});
    c.push_back({1605, colorOf(L"colorToolbarIconHover", 0xFFCDD6F4u, 0xFF)});
    c.push_back({801,  colorOf(L"colorLocationBar", 0xFF313244u, aLoc)});
    c.push_back({802,  colorOf(L"colorLocationBarHover", 0xFF45475Au, aLoc)});
    c.push_back({803,  colorOf(L"colorLocationBarBorder", 0xFF585B70u, 0xFF)});
    c.push_back({1020, colorOf(L"colorOmniboxResults", 0xFF181825u, 0xFF)});
    c.push_back({1021, colorOf(L"colorOmniboxResultsHover", 0xFF313244u, 0xFF)});
    c.push_back({1062, colorOf(L"colorOmniboxText", 0xFFCDD6F4u, 0xFF)});
    c.push_back({1063, colorOf(L"colorOmniboxTextDim", 0xFF7F849Cu, 0xFF)});
    c.push_back({1466, colorOf(L"colorTabActive", 0xFF313244u, aTabA)});
    c.push_back({1468, colorOf(L"colorTabActive", 0xFF313244u, aTabA)});
    c.push_back({1473, tabSel});
    c.push_back({1474, tabSel});
    c.push_back({1471, tabHov});
    c.push_back({1472, tabHov});
    c.push_back({1483, tabTxtA});
    c.push_back({1484, tabTxtA});
    c.push_back({1485, tabTxtI});
    c.push_back({1486, tabTxtI});
    c.push_back({1538, tabStrk});
    c.push_back({1539, tabStrk});
    c.push_back({319,  colorOf(L"colorFocusBorder", 0xFFB4BEFEu, 0xFF)});
    if (PCWSTR pr = wcsstr(GetCommandLineW(), L"--scb-color-probe=")) {
        int start = _wtoi(pr + 18);
        c.clear();
        for (int i = 0; i < 64 && start > 0; i++) {
            int id = start + i;
            c.push_back({(unsigned int)id, 0xFF00A500u | ((unsigned int)(id & 0xFF) << 16) |
                                               (unsigned int)((id >> 8) & 0xFF)});
        }
        Wh_Log(L"colour probe from %d", start);
    }
    g_liveColors = std::move(c);
    // Shared accent pair (top-level settings, not the Helium group).
    PCWSTR a = ::Wh_GetStringSetting(L"accentStart");
    PCWSTR b = ::Wh_GetStringSetting(L"accentEnd");
    g_accentA.store(ParseHexColor(a, 0x89B4FA, 0) & 0xFFFFFF);
    g_accentB.store(ParseHexColor(b, 0xCBA6F7, 0) & 0xFFFFFF);
    Wh_FreeStringSetting(a);
    Wh_FreeStringSetting(b);
}

static std::atomic<bool> g_colorsApplied{false};
static BYTE* g_gcTarget = nullptr;
static BYTE g_gcOriginal[7];
static BYTE* g_hookMem = nullptr;
static volatile BYTE g_dark = 0;  // written by the theme thread, read by the hook

static bool HexNibble(char c, BYTE* out) {
    if (c >= '0' && c <= '9') { *out = (BYTE)(c - '0'); return true; }
    if (c >= 'A' && c <= 'F') { *out = (BYTE)(c - 'A' + 10); return true; }
    if (c >= 'a' && c <= 'f') { *out = (BYTE)(c - 'a' + 10); return true; }
    return false;
}

struct Patch {
    std::vector<BYTE> bytes;
    std::vector<bool> wild;
};

static bool ParsePattern(const char* s, Patch* p) {
    int i = 0;
    while (s[i]) {
        while (s[i] == ' ') i++;
        if (!s[i]) break;
        if (s[i] == '?' && s[i + 1] == '?') {
            p->bytes.push_back(0);
            p->wild.push_back(true);
            i += 2;
            continue;
        }
        BYTE hi, lo;
        if (!HexNibble(s[i], &hi) || !HexNibble(s[i + 1], &lo)) return false;
        p->bytes.push_back((BYTE)((hi << 4) | lo));
        p->wild.push_back(false);
        i += 2;
    }
    return !p->bytes.empty();
}

static void ForEachExecutableSection(HMODULE mod, void* ctx,
                                     void (*fn)(void*, BYTE*, SIZE_T, SIZE_T)) {
    auto dos = (IMAGE_DOS_HEADER*)mod;
    auto nt = (IMAGE_NT_HEADERS*)((BYTE*)mod + dos->e_lfanew);
    auto sec = IMAGE_FIRST_SECTION(nt);
    for (WORD i = 0; i < nt->FileHeader.NumberOfSections; i++) {
        if (sec[i].Characteristics & IMAGE_SCN_MEM_EXECUTE) {
            BYTE* start = (BYTE*)mod + sec[i].VirtualAddress;
            SIZE_T size = sec[i].Misc.VirtualSize;
            fn(ctx, start, size, sec[i].VirtualAddress);
        }
    }
}

struct ScanCtx {
    const Patch* pat;
    BYTE* matches[8];
    int count;
};

static void ScanSection(void* ctx, BYTE* start, SIZE_T size, SIZE_T rva) {
    ScanCtx* c = (ScanCtx*)ctx;
    const Patch* p = c->pat;
    if (size < p->bytes.size()) return;
    for (SIZE_T i = 0; i + p->bytes.size() <= size; i++) {
        bool ok = true;
        for (SIZE_T j = 0; j < p->bytes.size(); j++) {
            if (!p->wild[j] && start[i + j] != p->bytes[j]) { ok = false; break; }
        }
        if (ok) {
            if (c->count < 8) c->matches[c->count++] = start + i;
            else return;
        }
    }
}

static bool VaReferencedInImage(HMODULE mod, BYTE* target) {
    auto dos = (IMAGE_DOS_HEADER*)mod;
    auto nt = (IMAGE_NT_HEADERS*)((BYTE*)mod + dos->e_lfanew);
    BYTE* base = (BYTE*)mod;
    SIZE_T n = nt->OptionalHeader.SizeOfImage - 8;
    BYTE needle[8];
    UINT64 va = (UINT64)target;
    for (int i = 0; i < 8; i++) needle[i] = (BYTE)(va >> (8 * i));
    for (SIZE_T i = 0; i < n; i++) {
        if (base[i] == needle[0] && memcmp(base + i, needle, 8) == 0) return true;
    }
    return false;
}

static bool ApplyAcrylicPatch() {
    if (g_acrylicApplied) return true;
    HMODULE chrome = GetModuleHandleW(L"chrome.dll");
    if (!chrome) {
        Wh_Log(L"chrome.dll not loaded yet");
        return false;
    }

    Patch pat;
    if (!ParsePattern(kAcrylicPattern, &pat)) {
        Wh_Log(L"bad acrylic pattern string");
        return false;
    }

    ScanCtx ctx = {};
    ctx.pat = &pat;
    ForEachExecutableSection(chrome, &ctx, ScanSection);
    if (ctx.count == 0) {
        Wh_Log(L"acrylic: pattern not found (already patched build?) - untouched");
        return false;
    }

    BYTE* target = nullptr;
    for (int i = 0; i < ctx.count; i++) {
        if (VaReferencedInImage(chrome, ctx.matches[i])) {
            if (target) {
                Wh_Log(L"acrylic: more than one vtable-backed match - untouched");
                return false;
            }
            target = ctx.matches[i];
        }
    }
    if (!target) {
        Wh_Log(L"acrylic: no vtable-backed match - untouched");
        return false;
    }

    DWORD oldProtect;
    if (!VirtualProtect(target, sizeof(g_acrylicOriginal), PAGE_EXECUTE_READWRITE, &oldProtect)) {
        Wh_Log(L"acrylic: VirtualProtect failed");
        return false;
    }
    memcpy(g_acrylicOriginal, target, sizeof(g_acrylicOriginal));
    const BYTE patchBytes[3] = {0xB0, 0x01, 0xC3};  // mov al,1; ret
    memcpy(target, patchBytes, sizeof(patchBytes));
    DWORD tmp;
    VirtualProtect(target, sizeof(g_acrylicOriginal), oldProtect, &tmp);
    if (memcmp(target, patchBytes, sizeof(patchBytes)) != 0) {
        Wh_Log(L"acrylic: read-back mismatch");
        return false;
    }
    g_acrylicTarget = target;
    g_acrylicApplied = true;
    Wh_Log(L"Helium acrylic: patched at RVA 0x%zX", (size_t)(target - (BYTE*)chrome));
    return true;
}

// ---- generated hook -------------------------------------------------------
// Layout: [dark check][compare chain -> 25 hits][miss stub]
// Stack-free, register-safe: only eax/eflags are touched on hits, and the
// miss path replays the displaced pushes and jumps back into GetColor.

static bool EmitAndInstallColors(const ColorEntry* colors, int count) {
    if (count < 1 || count > 64) {
        Wh_Log(L"colors: bad table size %d", count);
        return false;
    }
    HMODULE chrome = GetModuleHandleW(L"chrome.dll");
    if (!chrome) {
        Wh_Log(L"chrome.dll not loaded yet");
        return false;
    }

    Patch pat;
    if (!ParsePattern(kGetColorPattern, &pat)) {
        Wh_Log(L"colors: bad pattern string");
        return false;
    }

    ScanCtx ctx = {};
    ctx.pat = &pat;
    ForEachExecutableSection(chrome, &ctx, ScanSection);
    if (ctx.count != 1) {
        Wh_Log(L"colors: pattern matched %d times (need exactly 1) - untouched", ctx.count);
        return false;
    }
    BYTE* entry = ctx.matches[0];

    // The displaced bytes must be the expected pushes.
    const BYTE expect[7] = {0x41, 0x57, 0x41, 0x56, 0x41, 0x54, 0x56};
    if (memcmp(entry, expect, 7) != 0) {
        Wh_Log(L"colors: unexpected prologue - untouched");
        return false;
    }

    // Allocate RWX near the entry so a 5-byte relative jmp reaches.
    BYTE* bases[6] = {
        (BYTE*)chrome - 0x10000000, (BYTE*)chrome + 0x10000000,
        (BYTE*)chrome - 0x40000000, (BYTE*)chrome + 0x40000000,
        (BYTE*)chrome - 0x70000000, (BYTE*)chrome + 0x70000000,
    };
    BYTE* mem = nullptr;
    for (int i = 0; i < 6 && !mem; i++) {
        mem = (BYTE*)VirtualAlloc(bases[i], 0x1000, MEM_RESERVE | MEM_COMMIT,
                                  PAGE_EXECUTE_READWRITE);
    }
    if (!mem) {
        mem = (BYTE*)VirtualAlloc(nullptr, 0x1000, MEM_RESERVE | MEM_COMMIT,
                                  PAGE_EXECUTE_READWRITE);
        if (!mem) {
            Wh_Log(L"colors: VirtualAlloc failed");
            return false;
        }
    }
    g_hookMem = mem;

    // --- generate the hook ---
    BYTE* p = mem;
    BYTE* flagAddr = (BYTE*)&g_dark;
    auto emit32 = [&](DWORD v) { memcpy(p, &v, 4); p += 4; };
    // mov rax, &g_dark ; cmp byte ptr [rax], 0 ; je miss
    // x64 has no absolute-addressed cmp, and a rip-relative disp32 cannot
    // reach the mod's own data: it can sit more than 2 GB away from this
    // page (this exact bug crashed the first paint of every stock test
    // instance on 2026-11-08 - the hook read rip + low32 of the flag).
    *p++ = 0x48; *p++ = 0xB8; memcpy(p, &flagAddr, 8); p += 8;
    *p++ = 0x80; *p++ = 0x38; *p++ = 0x00;
    BYTE* jeMiss = p; *p++ = 0x0F; *p++ = 0x84; p += 4;  // rel32 patched later

    // compare chain
    BYTE* hits[64];
    for (int i = 0; i < count; i++) {
        *p++ = 0x81; *p++ = 0xFA; emit32(colors[i].id);  // cmp edx, id
        *p++ = 0x0F; *p++ = 0x84; hits[i] = p; p += 4;    // je hit_i (rel32 later)
    }
    // miss: replay displaced bytes and jump back
    BYTE* miss = p;
    *p++ = 0x41; *p++ = 0x57;  // push r15
    *p++ = 0x41; *p++ = 0x56;  // push r14
    *p++ = 0x41; *p++ = 0x54;  // push r12
    *p++ = 0x56;               // push rsi
    INT64 back = (INT64)(entry + 7) - (INT64)(p + 5);
    *p++ = 0xE9; emit32((DWORD)back);
    *(DWORD*)(jeMiss + 2) = (DWORD)(INT64)(miss - (jeMiss + 6));
    // hits
    for (int i = 0; i < count; i++) {
        *(DWORD*)(hits[i]) = (DWORD)(INT64)(p - (hits[i] + 4));
        *p++ = 0xB8; emit32(colors[i].color);  // mov eax, color
        *p++ = 0xC3;                            // ret
    }

    // --- patch GetColor's entry ---
    DWORD oldProtect;
    DWORD tmp;
    if (!VirtualProtect(entry, sizeof(g_gcOriginal), PAGE_EXECUTE_READWRITE, &oldProtect)) {
        Wh_Log(L"colors: VirtualProtect failed");
        return false;
    }
    memcpy(g_gcOriginal, entry, sizeof(g_gcOriginal));
    INT64 rel = (INT64)mem - (INT64)(entry + 5);
    if (rel > 0x7FFFFFFF || rel < -0x7FFFFFFF) {
        VirtualProtect(entry, sizeof(g_gcOriginal), oldProtect, &tmp);
        Wh_Log(L"colors: hook out of jump range");
        return false;
    }
    BYTE jmp[5] = {0xE9, 0, 0, 0, 0};
    *(DWORD*)(jmp + 1) = (DWORD)rel;
    memcpy(entry, jmp, 5);
    if (entry[0] != 0xE9) {
        Wh_Log(L"colors: read-back mismatch");
        return false;
    }
    VirtualProtect(entry, sizeof(g_gcOriginal), oldProtect, &tmp);
    g_gcTarget = entry;
    g_colorsApplied = true;
    Wh_Log(L"Helium acrylic: color hook live at RVA 0x%zX (%d colors)",
           (size_t)(entry - (BYTE*)chrome), count);
    return true;
}

static bool InstallColorHook() {
    if (g_colorsApplied) return true;
    return EmitAndInstallColors(kColors, kColorCount);
}

static bool ReadDarkTheme() {
    HKEY key;
    if (RegOpenKeyExW(HKEY_CURRENT_USER,
                      L"Software\\Microsoft\\Windows\\CurrentVersion\\Themes\\Personalize",
                      0, KEY_READ, &key) != ERROR_SUCCESS) {
        return true;  // assume dark (the rice is dark-only) if unreadable
    }
    DWORD v = 0, size = sizeof(v), type = 0;
    LONG r = RegQueryValueExW(key, L"AppsUseLightTheme", nullptr, &type,
                              (LPBYTE)&v, &size);
    RegCloseKey(key);
    if (r != ERROR_SUCCESS || type != REG_DWORD) return true;
    return v == 0;
}

static DWORD WINAPI ThemeThread(LPVOID) {
    while (!g_stop) {
        g_dark = ReadDarkTheme() ? 1 : 0;
        if (WaitOrStop(5000)) break;
    }
    return 0;
}

// ---------------------------------------------------------------------------
// Part 3: the acrylic backdrop.
//
// The riced build set DWMSBT_TRANSIENTWINDOW on every translucent browser
// window inside DesktopWindowTreeHostWin::Init; stock Helium never does, so a
// modded stock window shows the flat desktop through its strip instead of the
// blurred acrylic. Rather than patch that init path, this layer watches the
// process's own top-level windows and applies the backdrop plus the dark
// backdrop tint directly - idempotent, and it covers windows opened later.
//
// On Helium 0.22.1.1, DWMSBT isn't taking effect because DWM attributes are
// overridden by Chromium's frame painting. Instead use SetWindowCompositionAttribute
// with WCA_ACCENT_POLICY (accent acrylic) which works on this build.
//
struct BackdropCtx { DWORD pid; };

typedef LONG (WINAPI *PFN_DwmSetWindowAttribute)(HWND, DWORD, LPCVOID, DWORD);
typedef BOOL (WINAPI *PFN_SetWindowCompositionAttribute)(HWND, const void*);

static PFN_DwmSetWindowAttribute GetDwmSetWindowAttribute() {
    static PFN_DwmSetWindowAttribute fn = nullptr;
    if (!fn) {
        HMODULE m = GetModuleHandleW(L"dwmapi.dll");
        if (!m) m = LoadLibraryW(L"dwmapi.dll");
        if (m) fn = (PFN_DwmSetWindowAttribute)GetProcAddress(m, "DwmSetWindowAttribute");
    }
    return fn;
}

static PFN_SetWindowCompositionAttribute GetSetWindowCompositionAttribute() {
    static PFN_SetWindowCompositionAttribute fn = nullptr;
    if (!fn) {
        HMODULE m = GetModuleHandleW(L"user32.dll");
        if (!m) m = LoadLibraryW(L"user32.dll");
        if (m) fn = (PFN_SetWindowCompositionAttribute)GetProcAddress(m, "SetWindowCompositionAttribute");
    }
    return fn;
}

struct ACCENTPOLICY {
    DWORD AccentState;
    DWORD AccentFlags;
    DWORD GradientColor;
    DWORD AnimationId;
};

struct WINDOWCOMPOSITIONATTRDATA {
    DWORD Attribute;
    LPVOID Data;
    DWORD SizeOfData;
};

// v1.0.2: keep Helium's native Windows title bar strip even when Seamless Title Bars
// is off. Chromium strips the system caption via WM_NCCALCSIZE, which puts the
// toolbar right underneath the native caption buttons at the top right. Passing
// WM_NCCALCSIZE / WM_NCACTIVATE / WM_NCHITTEST / WM_NCLBUTTONDOWN to DefWindowProcW
// on captioned top-level Helium windows keeps the real title bar above the toolbar
// while leaving fullscreen (no WS_CAPTION) and popups untouched.
static SRWLOCK g_nfLock = SRWLOCK_INIT;
static std::vector<HWND> g_nfHwnds;

static LRESULT CALLBACK HeliumNativeFrameSubclassProc(
    HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, DWORD_PTR dwRefData) {
    if (g_set.nativeFrame && (GetWindowLongW(hWnd, GWL_STYLE) & WS_CAPTION)) {
        switch (uMsg) {
            case WM_NCCALCSIZE:
            case WM_NCACTIVATE:
            case WM_NCHITTEST:
            case WM_NCLBUTTONDOWN:
                return DefWindowProcW(hWnd, uMsg, wParam, lParam);
            case WM_DWMNCRENDERINGCHANGED: {
                RECT rect;
                if (GetWindowRect(hWnd, &rect)) {
                    SetWindowPos(hWnd, nullptr, rect.left, rect.top + 1, 0, 0,
                                 SWP_NOZORDER | SWP_NOOWNERZORDER | SWP_NOACTIVATE | SWP_NOSIZE);
                    SetWindowPos(hWnd, nullptr, rect.left, rect.top, 0, 0,
                                 SWP_FRAMECHANGED | SWP_NOZORDER | SWP_NOOWNERZORDER | SWP_NOACTIVATE | SWP_NOSIZE);
                }
                break;
            }
            default:
                break;
        }
    }
    return DefSubclassProc(hWnd, uMsg, wParam, lParam);
}

static void EnsureHeliumNativeFrameSubclass(HWND hwnd, bool want) {
    if (!IsWindow(hwnd)) return;
    bool tracked = false;
    AcquireSRWLockExclusive(&g_nfLock);
    g_nfHwnds.erase(
        std::remove_if(g_nfHwnds.begin(), g_nfHwnds.end(),
                       [](HWND h) { return !IsWindow(h); }),
        g_nfHwnds.end());
    auto it = std::find(g_nfHwnds.begin(), g_nfHwnds.end(), hwnd);
    tracked = (it != g_nfHwnds.end());
    if (want && !tracked) {
        g_nfHwnds.push_back(hwnd);
    } else if (!want && tracked) {
        g_nfHwnds.erase(it);
    }
    ReleaseSRWLockExclusive(&g_nfLock);

    if (want && !tracked) {
        if (WindhawkUtils::SetWindowSubclassFromAnyThread(hwnd, HeliumNativeFrameSubclassProc, 0)) {
            SetWindowPos(hwnd, nullptr, 0, 0, 0, 0,
                         SWP_FRAMECHANGED | SWP_NOMOVE | SWP_NOSIZE |
                             SWP_NOZORDER | SWP_NOOWNERZORDER | SWP_NOACTIVATE);
        }
    } else if (!want && tracked) {
        WindhawkUtils::RemoveWindowSubclassFromAnyThread(hwnd, HeliumNativeFrameSubclassProc);
        SetWindowPos(hwnd, nullptr, 0, 0, 0, 0,
                     SWP_FRAMECHANGED | SWP_NOMOVE | SWP_NOSIZE |
                         SWP_NOZORDER | SWP_NOOWNERZORDER | SWP_NOACTIVATE);
    }
}

static void RemoveAllHeliumNativeFrameSubclasses() {
    std::vector<HWND> list;
    AcquireSRWLockExclusive(&g_nfLock);
    list.swap(g_nfHwnds);
    ReleaseSRWLockExclusive(&g_nfLock);
    for (HWND h : list) {
        if (!IsWindow(h)) continue;
        WindhawkUtils::RemoveWindowSubclassFromAnyThread(h, HeliumNativeFrameSubclassProc);
        SetWindowPos(h, nullptr, 0, 0, 0, 0,
                     SWP_FRAMECHANGED | SWP_NOMOVE | SWP_NOSIZE |
                         SWP_NOZORDER | SWP_NOOWNERZORDER | SWP_NOACTIVATE);
    }
}

static BOOL CALLBACK BackdropEnumProc(HWND hwnd, LPARAM lp) {
    DWORD pid = 0;
    GetWindowThreadProcessId(hwnd, &pid);
    if (pid != ((BackdropCtx*)lp)->pid) return TRUE;
    if (!IsWindowVisible(hwnd)) return TRUE;
    wchar_t cls[64];
    if (!GetClassNameW(hwnd, cls, 64) || wcscmp(cls, L"Chrome_WidgetWin_1") != 0) {
        return TRUE;
    }
    // Bubbles, menus and extension popups are rounded inside a square window
    // with a see-through shadow margin. Acrylic fills the whole square, so the
    // margin shows as a frosted square frame. Skip them unless asked, and
    // clear it once from any popup that got it earlier.
    LONG_PTR style = GetWindowLongPtrW(hwnd, GWL_STYLE);
    LONG_PTR exStyle = GetWindowLongPtrW(hwnd, GWL_EXSTYLE);
    bool bubble = (style & WS_POPUP) && !(style & (WS_CAPTION | WS_THICKFRAME)) &&
                  !(exStyle & WS_EX_APPWINDOW);
    if (bubble && !g_set.popupAcrylic) {
        if (!GetPropW(hwnd, L"HeliumAcrylicPopupClear")) {
            PFN_SetWindowCompositionAttribute clear = GetSetWindowCompositionAttribute();
            if (clear) {
                ACCENTPOLICY off = { 0, 0, 0, 0 }; // ACCENT_DISABLED
                WINDOWCOMPOSITIONATTRDATA d = { 19, &off, sizeof(off) };
                clear(hwnd, &d);
            }
            SetPropW(hwnd, L"HeliumAcrylicPopupClear", (HANDLE)1);
        }
        return TRUE;
    }
    if (bubble) RemovePropW(hwnd, L"HeliumAcrylicPopupClear");
    // Use SetWindowCompositionAttribute with accent acrylic (WCA_ACCENT_POLICY)
    // instead of DWMSBT because DWM attributes are overridden on Helium 0.22.1.1
    PFN_SetWindowCompositionAttribute wca = GetSetWindowCompositionAttribute();
    if (wca) {
        ACCENTPOLICY policy = { 3, 0x20|0x40, 0x00FFFFFF, 0 }; // ACCENT_ENABLE_ACRYLICBLURBEHIND
        WINDOWCOMPOSITIONATTRDATA data = { 19, &policy, sizeof(policy) }; // WCA_ACCENT_POLICY
        wca(hwnd, &data);
    }
    // v1.0.2: keep the real Windows title bar strip on top-level Helium windows.
    if (!bubble && !(exStyle & WS_EX_TOOLWINDOW) && GetAncestor(hwnd, GA_ROOT) == hwnd &&
        (style & WS_CAPTION)) {
        EnsureHeliumNativeFrameSubclass(hwnd, g_set.nativeFrame);
    }
    // Keep DWMWA_USE_IMMERSIVE_DARK_MODE setting via DwmSetWindowAttribute
    PFN_DwmSetWindowAttribute dwm = GetDwmSetWindowAttribute();
    if (dwm) {
        BOOL dark = g_dark ? TRUE : FALSE;
        dwm(hwnd, 20 /*DWMWA_USE_IMMERSIVE_DARK_MODE*/, &dark, sizeof(dark));
    }
    return TRUE;
}

static DWORD WINAPI BackdropThread(LPVOID) {
    int fastTicks = 20;
    while (!g_stop) {
        BackdropCtx ctx = { GetCurrentProcessId() };
        EnumWindows(BackdropEnumProc, (LPARAM)&ctx);
        DWORD waitMs = fastTicks > 0 ? (fastTicks--, 250) : 2000;
        if (WaitOrStop(waitMs)) break;
    }
    return 0;
}

// ---------------------------------------------------------------------------
// Part 4: the native-frame structural patches.
//
// A reverse-engineering pass of the riced 0.21.1.1 build produced four code
// sites that make a stock chrome.dll draw the window frame the way the riced
// build does: BrowserFrameViewWin::OnPaint stops painting the titlebar,
// BrowserDesktopWindowTreeHostWin::GetFrameMode answers FrameMode::SYSTEM_DRAWN,
// GetDwmFrameInsetsInPixels answers Insets(-1) so Windows keeps the resize
// borders, and the caption-button hide path keeps the Chromium glyph buttons
// from rendering beside the title-bar mod's dots.
//
// v3.3.1 runtime truth (live side-by-side, 2026-11-18): the riced build
// renders its custom caption dots with NO Chromium glyph buttons and full
// acrylic. SUNE-true everywhere (v3.0.0) killed the dots (system frame drew
// glyphs instead); SUNE-false everywhere (v3.1.0) left duplicate glyph
// buttons beside the dots; the byte-twin site at 0xe8295b (v3.3.0's cave A)
// sits in a different function whose rsi is an out-param, so its browser-view
// test read garbage and changed nothing. The real caption decision lives in
// the function that calls CommandLine::HasSwitch("hide-window-buttons")
// directly (found by xref to the switch string at RVA 0x10405c40): its
// switch branch calls the same virtual with the mode argument zeroed, and a
// second sizing function branches on the same switch. Running the stock with
// that switch was proven live today to match the riced caption exactly
// (dots, no glyphs). So the caption hide is now two in-place branch flips
// that make those switch branches unconditional - the stock's own switch
// path does the work. Frame mode and insets caves stay routed but inert
// (SUNE hardwired false), and the OnPaint site stays unpatched.
//
// Verified 2026-11-08 against the stock 0.21.1.1 chrome.dll: every site's
// original bytes are checked before anything is written, the OnPaint skip
// target was pinned by disassembly, and every resume address was read back
// from the binary. All displaced bytes are restored in Wh_ModUninit.
static const DWORD kRvaLCBSwitch = 0x18031e6;  // caption fn HasSwitch jne
static const DWORD kRvaLCBSizing = 0xa0e27aa;  // sizing fn HasSwitch jne
static const DWORD kRvaGFMHead = 0x374a180;    // GetFrameMode head
static const DWORD kRvaGDFIWrite = 0x374a159;  // GetDwmFrameInsetsInPixels
static const DWORD kRvaOnPaintPT = 0x29f8158;  // OnPaint PaintTitlebar head

static const BYTE kOrigLCBSwitch[6] = {0x0F, 0x85, 0xFE, 0x00, 0x00, 0x00};
static const BYTE kOrigLCBSizing[2] = {0x75, 0x25};
static const BYTE kOrigGFM[12] = {0x56, 0x48, 0x83, 0xEC, 0x20, 0x48, 0x8B,
                                  0x81, 0x30, 0x01, 0x00, 0x00};
static const BYTE kOrigGDFI[5] = {0x0F, 0x57, 0xC0, 0x0F, 0x11};
static const BYTE kOrigOnPaint[7] = {0x48, 0x8B, 0x87, 0x28, 0x03, 0x00, 0x00};

// Stock addresses the caves branch to (each read back from the binary).
// Cave branch targets re-derived for stock Helium 0.21.3.1 chrome.dll.
// Each is the 0.21.1.1 address minus the per-function build delta, verified
// by disassembly: GFM/GDFI shift -0x72D0, OnPaint shifts -0xE13D734. The
// internal offsets within every function are preserved.
static const DWORD kRvaGFMNull = 0x374a255;     // xor eax,eax; jmp epilogue
static const DWORD kRvaGFMResume = 0x374a195;   // mov rsi,rcx (reads [rax+..])
static const DWORD kRvaGFMEpilogue = 0x374a24f; // add rsp,0x20; pop rsi; ret
static const DWORD kRvaGDFIResume = 0x374a15f;  // mov al,1
static const DWORD kRvaOnPaintResume = 0x29f815f;
// Pinned skip target: first instruction after the inlined PaintTitlebar body.
// The riced build runs nothing between its skipped PaintTitlebar call and
// this exit trace store, so the cave lands exactly there.
// GATED for 0.21.3.1: the derived 0x29f87d0 is a backward short jmp
// (EB 8F -> 0x29f8761), not the exit trace store, so the skip branch is
// never installed. SUNE is hardwired false, so cave D's replay is a no-op
// anyway; the OnPaint site is left unpatched for this build.
static const DWORD kRvaOnPaintSkip = 0x29f87d0;  // unverified - do not route

struct FrameSite {
    BYTE* target;
    BYTE original[12];
    int size;
    bool applied;
};
static FrameSite g_frameSites[4];
static BYTE* g_cavePage = nullptr;
static std::atomic<bool> g_frameApplied{false};

static void EmitJmpRel32(BYTE*& p, BYTE* to) {
    *p = 0xE9;
    *(DWORD*)(p + 1) = (DWORD)((INT64)to - (INT64)(p + 5));
    p += 5;
}

static void EmitJccRel32(BYTE*& p, BYTE cc, BYTE* to) {  // 0F 8x rel32
    *p = 0x0F;
    p[1] = cc;
    *(DWORD*)(p + 2) = (DWORD)((INT64)to - (INT64)(p + 6));
    p += 6;
}

static void EmitCallRel32(BYTE*& p, BYTE* to) {
    *p = 0xE8;
    *(DWORD*)(p + 1) = (DWORD)((INT64)to - (INT64)(p + 5));
    p += 5;
}

static void EmitBytes(BYTE*& p, const BYTE* bytes, size_t n) {
    memcpy(p, bytes, n);
    p += n;
}

// WM_THEMECHANGED nudge: windows created before this mod finished patching
// keep whatever caption layout they computed at creation. The message routes
// into Chromium's frame re-layout, so the caption function runs again - now
// under the patch - and the glyph buttons hide on already-open windows. It
// also re-runs the omnibox's RefreshBackground for the held-back gradient
// layer. Collect every main-window-class HWND of this process and post to
// each.
struct NudgeCtx { DWORD pid; HWND hwnds[8]; int n; };
static BOOL CALLBACK NudgeEnum(HWND h, LPARAM lp) {
    NudgeCtx* c = (NudgeCtx*)lp;
    DWORD pid = 0;
    GetWindowThreadProcessId(h, &pid);
    if (pid != c->pid) return TRUE;
    WCHAR cls[32];
    if (!GetClassNameW(h, cls, 32) || wcscmp(cls, L"Chrome_WidgetWin_1") != 0)
        return TRUE;
    if (c->n < 8) c->hwnds[c->n++] = h;
    return TRUE;
}

static bool ApplyStructuralPatches() {
    if (g_frameApplied) return true;
    HMODULE chrome = GetModuleHandleW(L"chrome.dll");
    if (!chrome) {
        Wh_Log(L"chrome.dll not loaded yet");
        return false;
    }

    // One mismatch at any site means a different build: nothing is written.
    // The OnPaint site is a canary only: verified, never written.
    struct SiteSpec { DWORD rva; const BYTE* orig; int len; };
    const SiteSpec specs[5] = {
        {kRvaLCBSwitch, kOrigLCBSwitch, sizeof(kOrigLCBSwitch)},
        {kRvaLCBSizing, kOrigLCBSizing, sizeof(kOrigLCBSizing)},
        {kRvaGFMHead, kOrigGFM, sizeof(kOrigGFM)},
        {kRvaGDFIWrite, kOrigGDFI, sizeof(kOrigGDFI)},
        {kRvaOnPaintPT, kOrigOnPaint, sizeof(kOrigOnPaint)},
    };
    for (int i = 0; i < 5; i++) {
        BYTE* at = (BYTE*)chrome + specs[i].rva;
        if (memcmp(at, specs[i].orig, specs[i].len) != 0) {
            Wh_Log(L"native frame: site %d (RVA 0x%zX) has unexpected bytes"
                   L" - untouched", i, (size_t)specs[i].rva);
            return false;
        }
    }

    // One RWX page for the helper and all four caves, near the module like
    // the color hook's page. rel32 covers the whole 300 MB image from there.
    BYTE* bases[5] = {
        (BYTE*)chrome - 0x10000000 + 0x100000,
        (BYTE*)chrome - 0x10000000 - 0x100000,
        (BYTE*)chrome + 0x10000000,
        (BYTE*)chrome - 0x40000000,
        (BYTE*)chrome + 0x40000000,
    };
    BYTE* mem = nullptr;
    for (int i = 0; i < 5 && !mem; i++) {
        mem = (BYTE*)VirtualAlloc(bases[i], 0x1000, MEM_RESERVE | MEM_COMMIT,
                                  PAGE_EXECUTE_READWRITE);
    }
    if (!mem) {
        mem = (BYTE*)VirtualAlloc(nullptr, 0x1000, MEM_RESERVE | MEM_COMMIT,
                                  PAGE_EXECUTE_READWRITE);
    }
    if (!mem) {
        Wh_Log(L"native frame: VirtualAlloc failed");
        return false;
    }
    g_cavePage = mem;

    // SUNE helper: always false so Chromium caption buttons stay visible and
    // system-drawn frame materials are not installed. This matches the riced
    // build's runtime behavior while keeping the acrylic/transparency patches active.
    BYTE* p = mem;
    BYTE* sune = mem;
    const BYTE suneImpl[] = { 0x31, 0xC0, 0xC3 }; // xor eax,eax; ret
    EmitBytes(p, suneImpl, sizeof(suneImpl));

    // v3.3.1: the old cave A (and the byte-twin site 0xe8295b it detoured)
    // is gone. The caption hide is two in-place branch flips written below;
    // see Part 4's header for how the real switch-gated function was found.

    // Cave C (offset 96): GetFrameMode. Native frame answers 0
    // (FrameMode::SYSTEM_DRAWN); otherwise the stock flow continues with
    // rax = browser_view_ reloaded, because the resumed instruction reads it.
    p = mem + 96;
    BYTE* caveC = p;
    const BYTE cPush[] = {0x56};
    const BYTE cSub[] = {0x48, 0x83, 0xEC, 0x20};
    const BYTE cMovRsi[] = {0x48, 0x89, 0xCE};
    const BYTE cMovRax[] = {0x48, 0x8B, 0x81, 0x30, 0x01, 0x00, 0x00};
    const BYTE cTest[] = {0x48, 0x85, 0xC0};
    const BYTE cMovRcxRax[] = {0x48, 0x89, 0xC1};
    const BYTE cTestJne[] = {0x84, 0xC0, 0x75, 0x0F};
    const BYTE cMovRcxRsi[] = {0x48, 0x89, 0xF1};
    const BYTE cReload[] = {0x48, 0x8B, 0x86, 0x30, 0x01, 0x00, 0x00};
    const BYTE cZero[] = {0x31, 0xC0};
    EmitBytes(p, cPush, 1);
    EmitBytes(p, cSub, 4);
    EmitBytes(p, cMovRsi, 3);     // mov rsi,rcx (replay)
    EmitBytes(p, cMovRax, 7);     // mov rax,[rcx+0x130] (replay)
    EmitBytes(p, cTest, 3);
    EmitJccRel32(p, 0x84, (BYTE*)chrome + kRvaGFMNull);  // je null path
    EmitBytes(p, cMovRcxRax, 3);  // mov rcx,rax
    EmitCallRel32(p, sune);
    EmitBytes(p, cTestJne, 4);    // test al,al; jne .zero
    EmitBytes(p, cMovRcxRsi, 3);  // mov rcx,rsi
    EmitBytes(p, cReload, 7);     // mov rax,[rsi+0x130] (resume needs rax)
    EmitJmpRel32(p, (BYTE*)chrome + kRvaGFMResume);
    // .zero:
    EmitBytes(p, cZero, 2);
    EmitJmpRel32(p, (BYTE*)chrome + kRvaGFMEpilogue);

    // Cave B (offset 160): GetDwmFrameInsetsInPixels write-out. Native frame
    // answers all-ones (Insets(-1)); otherwise zeros. Both resume at the
    // stock's mov al,1. rdi (this) and rsi (Insets*) come from the stock.
    p = mem + 160;
    BYTE* caveB = p;
    const BYTE bMovRcx[] = {0x48, 0x8B, 0x8F, 0x30, 0x01, 0x00, 0x00};
    const BYTE bTestJne[] = {0x84, 0xC0, 0x75, 0x05};
    const BYTE bZero[] = {0x0F, 0x57, 0xC0, 0xEB, 0x04};
    const BYTE bNeg1[] = {0x66, 0x0F, 0x76, 0xC0};
    const BYTE bStore[] = {0xF3, 0x0F, 0x7F, 0x06};
    EmitBytes(p, bMovRcx, 7);     // mov rcx,[rdi+0x130]
    EmitCallRel32(p, sune);
    EmitBytes(p, bTestJne, 4);    // test al,al; jne .neg1
    EmitBytes(p, bZero, 5);       // xorps xmm0,xmm0; jmp .store
    EmitBytes(p, bNeg1, 4);       // .neg1: pcmpeqd xmm0,xmm0
    EmitBytes(p, bStore, 4);      // .store: movdqu [rsi],xmm0
    EmitJmpRel32(p, (BYTE*)chrome + kRvaGDFIResume);

    // Cave D (offset 224): OnPaint's inlined PaintTitlebar. Native frame
    // jumps past the whole body to the pinned skip target; otherwise the
    // displaced instruction is replayed. bv via the stock's own inlined
    // GetBrowserView ([rdi+0x338] - 0x1f0, cf. 0x1abc16b).
    // Gated for 0.21.3.1: the skip target is unverified, so the body is
    // emitted but never routed to any site.
    p = mem + 224;
    BYTE* caveD = p;
    const BYTE dField[] = {0x48, 0x8B, 0x87, 0x38, 0x03, 0x00, 0x00};
    const BYTE dBv[] = {0x48, 0x8D, 0x88, 0x10, 0xFE, 0xFF, 0xFF};
    const BYTE dTestCmove[] = {0x48, 0x85, 0xC0, 0x48, 0x0F, 0x44, 0xC8};
    const BYTE dTestAl[] = {0x84, 0xC0};
    const BYTE dReplay[] = {0x48, 0x8B, 0x87, 0x28, 0x03, 0x00, 0x00};
    EmitBytes(p, dField, 7);      // mov rax,[rdi+0x338]
    EmitBytes(p, dBv, 7);         // lea rcx,[rax-0x1f0]
    EmitBytes(p, dTestCmove, 7);  // test rax,rax; cmove rcx,rax
    EmitCallRel32(p, sune);
    EmitBytes(p, dTestAl, 2);     // test al,al
    EmitJccRel32(p, 0x85, (BYTE*)chrome + kRvaOnPaintSkip);  // jne SKIP
    EmitBytes(p, dReplay, 7);     // mov rax,[rdi+0x328] (replay)
    EmitJmpRel32(p, (BYTE*)chrome + kRvaOnPaintResume);

    // Caption hide: two direct in-place branch flips (slots 0 and 1).
    // Site 1 (0x18031e6): the caption function's jne over its switch path
    // becomes an unconditional jmp, so every window runs the stock
    // --hide-window-buttons path (virtual called with the mode argument 0).
    // Site 2 (0xa0e27aa): the sizing function's switch branch likewise
    // always taken. Both replicate the live-proven switch behavior.
    static const BYTE lcbSwitchNew[6] = {0xE9, 0xFF, 0x00, 0x00, 0x00, 0x90};
    static const BYTE lcbSizingNew[2] = {0xEB, 0x25};
    struct RawPatch { DWORD rva; int slot; int len; const BYTE* neu; };
    const RawPatch raws[2] = {
        {kRvaLCBSwitch, 0, 6, lcbSwitchNew},
        {kRvaLCBSizing, 1, 2, lcbSizingNew},
    };
    for (int i = 0; i < 2; i++) {
        BYTE* at = (BYTE*)chrome + raws[i].rva;
        DWORD oldProtect, tmp;
        if (!VirtualProtect(at, raws[i].len, PAGE_EXECUTE_READWRITE,
                            &oldProtect)) {
            Wh_Log(L"native frame: VirtualProtect failed at raw %d", i);
            return false;
        }
        memcpy(g_frameSites[raws[i].slot].original, at, raws[i].len);
        memcpy(at, raws[i].neu, raws[i].len);
        VirtualProtect(at, raws[i].len, oldProtect, &tmp);
        if (memcmp(at, raws[i].neu, raws[i].len) != 0) {
            memcpy(at, g_frameSites[raws[i].slot].original, raws[i].len);
            Wh_Log(L"native frame: raw %d read-back mismatch - restored", i);
            return false;
        }
        g_frameSites[raws[i].slot].target = at;
        g_frameSites[raws[i].slot].size = raws[i].len;
        g_frameSites[raws[i].slot].applied = true;
        Wh_Log(L"Helium acrylic: caption switch patch %d live at RVA 0x%zX",
               i, (size_t)raws[i].rva);
    }

    // Route the frame-mode sites into their caves, saving the displaced
    // bytes (slots 2 and 3). OnPaint (cave D) is gated for 0.21.3.1: skip
    // target unverified.
    struct Write { DWORD rva; int len; BYTE* cave; };
    const Write writes[2] = {
        {kRvaGFMHead, 12, caveC},
        {kRvaGDFIWrite, 5, caveB},
    };
    for (int i = 0; i < 2; i++) {
        BYTE* at = (BYTE*)chrome + writes[i].rva;
        INT64 rel = (INT64)writes[i].cave - (INT64)(at + 5);
        if (rel > 0x7FFFFFFF || rel < -0x7FFFFFFF) {
            Wh_Log(L"native frame: cave out of jump range - untouched");
            return false;
        }
        DWORD oldProtect, tmp;
        if (!VirtualProtect(at, writes[i].len, PAGE_EXECUTE_READWRITE,
                            &oldProtect)) {
            Wh_Log(L"native frame: VirtualProtect failed");
            return false;
        }
        memcpy(g_frameSites[i + 2].original, at, writes[i].len);
        BYTE jmp[5] = {0xE9, 0, 0, 0, 0};
        *(DWORD*)(jmp + 1) = (DWORD)rel;
        memcpy(at, jmp, 5);
        for (int j = 5; j < writes[i].len; j++) at[j] = 0x90;
        VirtualProtect(at, writes[i].len, oldProtect, &tmp);
        if (at[0] != 0xE9) {
            Wh_Log(L"native frame: site %d read-back mismatch", i);
            return false;
        }
        g_frameSites[i + 2].target = at;
        g_frameSites[i + 2].size = writes[i].len;
        g_frameSites[i + 2].applied = true;
        Wh_Log(L"Helium acrylic: native-frame cave %d live at RVA 0x%zX",
               i, (size_t)writes[i].rva);
    }
    g_frameApplied = true;
    Wh_Log(L"Helium acrylic: native frame live (caption switch always on,"
           L" frame-mode caves routed but inert)");
    // Re-layout windows that existed before the patches landed.
    NudgeCtx nc;
    nc.pid = GetCurrentProcessId();
    nc.n = 0;
    EnumWindows(NudgeEnum, (LPARAM)&nc);
    for (int i = 0; i < nc.n; i++)
        PostMessageW(nc.hwnds[i], WM_THEMECHANGED, 0, 0);
    Wh_Log(L"Helium acrylic: theme nudge posted to %d windows", nc.n);
    return true;
}

// ---------------------------------------------------------------------------
// Part 5 (v3.2.0): the remaining riced mechanisms, ported from the riced
// build's GradientBorderRoundRectPainter (its full Paint body was disassembled
// and is mirrored step by step below) plus the fullscreen guard and the
// sidebar new-tab hide. Same contract as the native-frame layer: original
// bytes verified before any write, every write read back, everything
// restored in Wh_ModUninit.
//
// - Fullscreen guard: ShouldWindowContentsBeTransparent (the site the acrylic
//   patch used) now answers false while the window is fullscreen, so the
//   material strip does not float over fullscreen video. The stock null
//   check is re-emitted in the cave; g_fsActive records the state. This
//   replaces the old unconditional mov al,1;ret - the site check accepts
//   both the stock body and that patch so a live mod update re-applies.
// - Sidebar new-tab button: the sidebar stores the button then hides it via
//   its own View::SetVisible(false) virtual, the riced sidebar look.
// - Tab-pill gradient: at PaintTabBackgroundFill's DrawPath the stroke flags
//   gain a blue->mauve linear gradient shader whose alpha follows the stroke
//   color, the riced tab pill's gradient stroke.
// - Omnibox gradient: the resting omnibox (not caret-visible, no input in
//   progress, not high contrast, not popup mode) is the only state that
//   reaches RefreshBackground's inline solid-painter build (0x1707AAA on
//   0.21.3.1); the cave there installs the riced gradient painter instead. A
//   caret-visible omnibox gets the stock-shaped painter with a solid lavender
//   stroke (kColorFocusableBorderFocused, fetched live). Every other state
//   (input in progress, high contrast) keeps the stock's own factory call
//   later in the function untouched.

static const DWORD kRvaFsGuard = 0x374a290;     // ShouldWindowContentsBeTransparent
static const DWORD kRvaNtHide = 0x37479f3;      // sidebar new-tab store
static const DWORD kRvaPillDraw = 0xaac9d2b;    // vertical-tab pill stroke DrawPath
                                                // (stock PaintTabBackgroundFill
                                                // 0xAAC9970: rcx=canvas, rdx=path,
                                                // r8=stroke flags; fill flags stay
                                                // at [rsp+0xA0], xmm6=scale)
static const BYTE kOrigPill[5] = {0xE8, 0x70, 0x82, 0xC9, 0xF8};
static const DWORD kRvaPillResume = 0xaac9d30;  // instruction after the stroke DrawPath
static const DWORD kRvaOmniB = 0x1707aaa;       // RefreshBackground inline painter
static const BYTE kOrigOmniB[5] = {0xB9, 0x38, 0x00, 0x00, 0x00};
static const DWORD kRvaOmniConv = 0x1707af0;    // the wrapper alloc after the site
static const DWORD kRvaGetColor = 0x4311790;    // ui::ColorProvider::GetColor
static const DWORD kRvaProvider = 0x4909f60;    // view color-provider getter

static const BYTE kOrigFsGuard[13] = {
    0x48, 0x83, 0xB9, 0xC8, 0x02, 0x00, 0x00, 0x00, 0x74, 0x03, 0x31, 0xC0, 0xC3};
static const BYTE kOrigNtHide[7] = {0x4C, 0x89, 0xB6, 0x50, 0x03, 0x00, 0x00};
static const BYTE kOldAcrylic[3] = {0xB0, 0x01, 0xC3};  // the v3.1.0 patch

static const DWORD kRvaNtResume = 0x37479fa;

// Stock routine pins, re-verified on the 0.21.3.1 image 2026-11-18 (disasm
// cross-checked against the 0.21.1.1 bodies; see the note in ApplyV320).
static const DWORD kRvaSave = 0x3761c40;        // gfx::Canvas::Save
static const DWORD kRvaRestore = 0x3761c90;     // gfx::Canvas::Restore
static const DWORD kRvaUndoScale = 0x3761c00;   // Canvas::UndoDeviceScaleFactor
static const DWORD kRvaDrawPath = 0x3761fa0;    // gfx::Canvas::DrawPath
static const DWORD kRvaClipPath = 0x3761d20;    // gfx::Canvas::ClipPath
static const DWORD kRvaSkPathRRect = 0x48f46c0; // SkPath::RRect (real entry)
static const DWORD kRvaRRToSkRRect = 0x3105540; // gfx::RoundedRectFToSkRRect
static const DWORD kRvaFromColor = 0x5a08e80;   // SkRGBA4f::FromColor
static const DWORD kRvaFlagsCtor = 0x5c7fd60;   // cc::PaintFlags ctor
static const DWORD kRvaFlagsDtor = 0x4599610;   // cc::PaintFlags dtor
static const DWORD kRvaSkPathDtor = 0xac1880;   // SkPath::~SkPath
static const DWORD kRvaMlg = 0x96fea0;          // SkGradientShader::MakeLinear

static std::atomic<bool> g_gradApplied{false};
static BYTE* g_gradPage = nullptr;
static BYTE* g_chromeBase = nullptr;
static BYTE* g_fsGuardSite = nullptr;
static BYTE* g_ntSite = nullptr;
static BYTE* g_pillSite = nullptr;
static BYTE* g_omniSite = nullptr;
static BYTE g_fsGuardOrig[13];
static BYTE g_ntOrig[7];
static BYTE g_pillOrig[5];
static BYTE g_omniOrig[5];
static volatile BYTE g_fsActive = 0;
static BYTE g_painterVft[24];
static BYTE g_omniPainter[0x18];
static void (*g_mlgThunk)(void*, void*, void*, const void*);

static void* GradRva(DWORD rva) { return g_chromeBase + rva; }

// The mod DLL can load far outside a 32-bit call's reach from the cave, so
// calls into this mod's own code go through an absolute register call.
static void EmitCallAbs64(BYTE*& p, void* target) {
    *p++ = 0x48; *p++ = 0xB8;
    memcpy(p, &target, 8); p += 8;  // movabs rax, target
    *p++ = 0xFF; *p++ = 0xD0;       // call rax
}

// The linear gradient needs six stack arguments after the four register ones;
// this thunk stages them and calls SkGradientShader::MakeLinearGradient with
// a local frame so the caller's stack stays untouched.

typedef void (*CanvasSaveFn)(void*);
typedef void (*CanvasRestoreFn)(void*);
typedef float (*UndoScaleFn)(void*);
typedef void (*DrawPathFn)(void*, void*, void*);
typedef void (*FlagsCtorFn)(void*);
typedef void (*FlagsDtorFn)(void*);
typedef void (*FromColorFn)(void*, unsigned);
typedef void (*RRToSkRRectFn)(void*, const void*, const void*);
// 0.21.3.1 moved the corner-direction into the 4th argument (the 0.21.1.1
// body computed it from a bool in r8b: 0 -> 6). Stock callers pass 6.
typedef void (*SkPathRRectFn)(void*, const void*, unsigned, unsigned);
typedef void (*SkPathDtorFn)(void*);
typedef void (*MlgCallFn)(void*, void*, void*, const void*);
typedef void (*ClipPathFn)(void*, const void*, unsigned);

static void MlgCall(void* sret, void* pts, void* colors) {
    ((MlgCallFn)g_mlgThunk)(sret, pts, colors, nullptr);
}

// PillStrokeC: replaces the stock solid stroke on the vertical-tab pill with
// the riced gradient edge. Runs at the stock stroke DrawPath site inside
// PaintTabBackgroundFill, where the canvas is already clipped to the pill and
// xmm6 holds the UndoDeviceScaleFactor return. Mirrors vertical_tab_style_
// views.cc PaintTabBackgroundFill: alpha = stroke_a x bg_a / 255, width
// 2*scale (the active clip shows it as 1px inside), blue->mauve gradient
// across the pill's own bounds.
static void PillStrokeC(void* canvas, void* path, void* fillFlags,
                        void* strokeFlags, float scale) {
    void* ref = *(void**)path;
    const float* bounds = (const float*)((const BYTE*)ref + 0x60);
    const float fa = *(const float*)((const BYTE*)fillFlags + 0x0C);
    const float sa = *(const float*)((const BYTE*)strokeFlags + 0x0C);
    float a = fa * sa;
    if (a > 1.0f) a = 1.0f;
    const unsigned bgA = (unsigned)(a * 255.0f + 0.5f);
    BYTE flags2[0x50];
    ((FlagsCtorFn)GradRva(kRvaFlagsCtor))(flags2);
    unsigned bf = *(unsigned*)(flags2 + 0x18);
    bf = (bf & 0xFFFFE03Fu) | (3u << 8) | 1u;  // blend kSrcOver, antialias
    bf = (bf & 0xFFFFFF3Fu) | 0x40u;           // style kStroke
    *(unsigned*)(flags2 + 0x18) = bf;
    *(float*)(flags2 + 0x10) = 2.0f * scale;   // clipped to 1px inside
    alignas(16) BYTE c0[16], c1[16], colors[32];
    ((FromColorFn)GradRva(kRvaFromColor))(c0, (bgA << 24) | g_accentA.load());
    ((FromColorFn)GradRva(kRvaFromColor))(c1, (bgA << 24) | g_accentB.load());
    memcpy(colors, c0, 16);
    memcpy(colors + 16, c1, 16);
    const float pts[4] = {bounds[0], 0.0f, bounds[2], 0.0f};
    void* shader = nullptr;
    MlgCall(&shader, (void*)pts, colors);
    *(void**)((BYTE*)flags2 + 0x28) = shader;
    ((CanvasSaveFn)GradRva(kRvaSave))(canvas);
    ((ClipPathFn)GradRva(kRvaClipPath))(canvas, path, 1);
    ((DrawPathFn)GradRva(kRvaDrawPath))(canvas, path, flags2);
    ((CanvasRestoreFn)GradRva(kRvaRestore))(canvas);
    ((FlagsDtorFn)GradRva(kRvaFlagsDtor))(flags2);
}

// GradPainterPaint: the riced GradientBorderRoundRectPainter::Paint, mirrored
// instruction for instruction from the riced build (0x33ED390 there).
// Self is the 0x18-byte blob {vft, bg +8, stroke mode +0xC (0 = blue->mauve
// gradient, 1 = solid color at +0x10)}; size is the gfx::Size the stock
// wrapper derived from the view.
static void GradPainterPaint(void* self, void* canvas, void* sizePtr) {
    if (g_gradPage) g_gradPage[0x2F4] += 1;  // paint counter (spare0)
    const unsigned bg = *(const unsigned*)((const BYTE*)self + 8);
    const int w = ((const int*)sizePtr)[0];
    const int h = ((const int*)sizePtr)[1];
    // The riced painter computed the radius from the view size
    // (ComputeBorderRadius = GetCornerRadiusMetric(kHigh, size) = height/2,
    // the pill shape). The blob's radius field is unused now.
    float radius = (float)h * 0.5f;

    ((CanvasSaveFn)GradRva(kRvaSave))(canvas);
    const float scale = ((UndoScaleFn)GradRva(kRvaUndoScale))(canvas);
    const float r = radius * scale;

    // Fill: the whole view-sized rect, bg color, rounded by the radius.
    float rect[4] = {0.0f, 0.0f, (float)w * scale, (float)h * scale};
    float corners[4] = {r, r, r, r};
    BYTE flags1[0x50];
    ((FlagsCtorFn)GradRva(kRvaFlagsCtor))(flags1);
    unsigned bf = *(unsigned*)(flags1 + 0x18);
    bf = (bf & 0xFFFFE03Fu) | (3u << 8) | 1u;  // blend kSrcOver, antialias
    *(unsigned*)(flags1 + 0x18) = bf;
    alignas(16) BYTE bg4f[16];
    ((FromColorFn)GradRva(kRvaFromColor))(bg4f, bg);
    memcpy(flags1, bg4f, 16);
    BYTE rr1[64];
    memset(rr1, 0, sizeof(rr1));
    ((RRToSkRRectFn)GradRva(kRvaRRToSkRRect))(rr1, rect, corners);
    BYTE path1[16];
    memset(path1, 0, sizeof(path1));
    ((SkPathRRectFn)GradRva(kRvaSkPathRRect))(path1, rr1, 0, 6);
    ((DrawPathFn)GradRva(kRvaDrawPath))(canvas, path1, flags1);
    ((SkPathDtorFn)GradRva(kRvaSkPathDtor))(path1);
    ((FlagsDtorFn)GradRva(kRvaFlagsDtor))(flags1);

    // Stroke: the fill rect inset by half the stroke width (0.5 * scale per
    // side, the riced build's own numbers), corners reduced the same way and
    // clamped at zero, a one-device-pixel-wide gradient ring.
    const float inset = 0.5f * scale;
    for (int i = 0; i < 4; i++) {
        corners[i] = r - inset;
        if (corners[i] < 0.0f) corners[i] = 0.0f;
    }
    rect[0] += inset;
    rect[1] += inset;
    rect[2] -= 2.0f * inset;
    rect[3] -= 2.0f * inset;
    BYTE flags2[0x50];
    ((FlagsCtorFn)GradRva(kRvaFlagsCtor))(flags2);
    bf = *(unsigned*)(flags2 + 0x18);
    bf = (bf & 0xFFFFE03Fu) | (3u << 8) | 1u;
    bf = (bf & 0xFFFFFF3Fu) | 0x40u;  // style kStroke
    *(unsigned*)(flags2 + 0x18) = bf;
    *(float*)(flags2 + 0x10) = scale;
    alignas(16) BYTE colors[32];
    if (*(const unsigned*)((const BYTE*)self + 0xC) == 1u) {
        // Solid stroke: the focused omnibox keeps its lavender focus ring.
        alignas(16) BYTE solid[16];
        ((FromColorFn)GradRva(kRvaFromColor))(
            solid, *(const unsigned*)((const BYTE*)self + 0x10));
        memcpy(colors, solid, 16);
    } else {
        const float pts[4] = {(float)(int)rect[0], 0.0f,
                              (float)(int)(rect[0] + rect[2]), 0.0f};
        alignas(16) BYTE c0[16], c1[16];
        ((FromColorFn)GradRva(kRvaFromColor))(c0, 0xFF000000u | g_accentA.load());
        ((FromColorFn)GradRva(kRvaFromColor))(c1, 0xFF000000u | g_accentB.load());
        memcpy(colors, c0, 16);
        memcpy(colors + 16, c1, 16);
        void* shader = nullptr;
        MlgCall(&shader, (void*)pts, colors);
        *(void**)(flags2 + 0x28) = shader;
    }
    BYTE rr2[64];
    memset(rr2, 0, sizeof(rr2));
    ((RRToSkRRectFn)GradRva(kRvaRRToSkRRect))(rr2, rect, corners);
    BYTE path2[16];
    memset(path2, 0, sizeof(path2));
    ((SkPathRRectFn)GradRva(kRvaSkPathRRect))(path2, rr2, 0, 6);
    ((DrawPathFn)GradRva(kRvaDrawPath))(canvas, path2, flags2);
    ((SkPathDtorFn)GradRva(kRvaSkPathDtor))(path2);
    ((FlagsDtorFn)GradRva(kRvaFlagsDtor))(flags2);

    ((CanvasRestoreFn)GradRva(kRvaRestore))(canvas);
}

// Session diagnostic: append-only trace so a silent init failure is visible
// without the Windhawk log window (DBWIN is banned on this machine).
static void ModTrace(const char* s, size_t n) {
    HANDLE f = CreateFileA("F:\\hb-build\\mod-work\\agentB\\final\\modlog.txt",
                           FILE_APPEND_DATA, FILE_SHARE_READ | FILE_SHARE_WRITE,
                           nullptr, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);
    if (f == INVALID_HANDLE_VALUE) return;
    DWORD w = 0;
    WriteFile(f, s, (DWORD)n, &w, nullptr);
    CloseHandle(f);
}
#define MTRACE(s) ModTrace(s "\r\n", sizeof(s "\r\n") - 1)

// omnibox's own pass arms on its border-color fetch and consumes the arm in
// the same call. The helper itself moved above ApplyStructuralPatches so the
// structural layer can nudge newly patched windows too.

static bool ApplyV320() {
    MTRACE("v320: enter");
    // v3.5.0 (2026-11-18): the full re-pin onto 0.21.3.1 is done and every
    // anchor was resolved by disassembly cross-checked against the 0.21.1.1
    // body, not by fuzzy size matching alone:
    //   Sites: FsGuard 0x374A290 (unique pattern, bytes identical),
    //   NtHide 0x37479F3 (store bytes identical, two methods agree),
    //   PillDraw 0xAAC9D2B (the only DrawPath call in the matched
    //   PaintTabBackgroundFill 0xAAC9970, context matches instruction for
    //   instruction), OmniB 0x1707AAA (found via the painter's unique
    //   mov dword [rax+8],0xFFFF0000 wrapper construction; convergence
    //   wrapper alloc sits at site+0x46, same distance as 0.21.1.1).
    //   Routines: GetColor 0x4311790 (pattern), Provider 0x4909F60 (the pill
    //   function calls it exactly where 0.21.1.1 called 0x4F728E0; body is
    //   the same getter, devirtualized to 97 bytes), Canvas cluster
    //   Save/Restore/UndoScale/ClipPath/DrawPath 0x3761C40/0x3761C90/
    //   0x3761C00/0x3761D20/0x3761FA0, FromColor 0x5A08E80 (called by the
    //   new pill function), Mlg 0x96FEA0 (body sim 0.89), SkPathDtor
    //   0xAC1880 (pdata 1.000), RoundedRectFToSkRRect 0x3105540 (pdata 0.96,
    //   body is the float copy), SkPath::RRect 0x48F46C0 (prologue, type
    //   switch, dispatch and tail all match; signature now takes the corner
    //   direction in r9d - stock callers pass 6, so the mod does too),
    //   PaintFlags ctor 0x5C7FD60 and dtor 0x4599610 (both taken from the
    //   new pill function's own call sites; the dtor is also the top
    //   mnemonic match for the 0.21.1.1 dtor).
    if (g_gradApplied) return true;
    HMODULE chrome = GetModuleHandleW(L"chrome.dll");
    if (!chrome) {
        Wh_Log(L"chrome.dll not loaded yet");
        MTRACE("v320: fail - no chrome.dll");
        return false;
    }
    g_chromeBase = (BYTE*)chrome;

    // The fullscreen guard replaces the old acrylic patch on the same site,
    // so both the stock body and the v3.1.0 patch mean "this is our site".
    BYTE* fsAt = (BYTE*)chrome + kRvaFsGuard;
    bool fsStock = memcmp(fsAt, kOrigFsGuard, sizeof(kOrigFsGuard)) == 0;
    bool fsOld = memcmp(fsAt, kOldAcrylic, sizeof(kOldAcrylic)) == 0;
    if (!fsStock && !fsOld) {
        Wh_Log(L"v3.2.0: fullscreen guard site has unexpected bytes - untouched");
        MTRACE("v320: fail gate fs");
        return false;
    }
    BYTE* ntAt = (BYTE*)chrome + kRvaNtHide;
    if (memcmp(ntAt, kOrigNtHide, sizeof(kOrigNtHide)) != 0) {
        Wh_Log(L"v3.2.0: new-tab site has unexpected bytes - untouched");
        MTRACE("v320: fail gate nt");
        return false;
    }
    BYTE* pillAt = (BYTE*)chrome + kRvaPillDraw;
    if (memcmp(pillAt, kOrigPill, sizeof(kOrigPill)) != 0) {
        Wh_Log(L"v3.2.0: tab-pill site has unexpected bytes - untouched");
        MTRACE("v320: fail gate pill");
        return false;
    }
    BYTE* omniAt = (BYTE*)chrome + kRvaOmniB;
    if (memcmp(omniAt, kOrigOmniB, sizeof(kOrigOmniB)) != 0) {
        Wh_Log(L"v3.4.0: omnibox painter site has unexpected bytes - untouched");
        MTRACE("v320: fail gate omni");
        return false;
    }

    // One RWX page for the caves, the gradient thunk and the painter tables,
    // near the module like the other layers' pages.
    BYTE* bases[5] = {
        (BYTE*)chrome - 0x10000000 - 0x200000,
        (BYTE*)chrome - 0x10000000 + 0x100000,
        (BYTE*)chrome + 0x10000000,
        (BYTE*)chrome - 0x40000000,
        (BYTE*)chrome + 0x40000000,
    };
    BYTE* mem = nullptr;
    for (int i = 0; i < 5 && !mem; i++) {
        mem = (BYTE*)VirtualAlloc(bases[i], 0x1000, MEM_RESERVE | MEM_COMMIT,
                                  PAGE_EXECUTE_READWRITE);
    }
    if (!mem) {
        mem = (BYTE*)VirtualAlloc(nullptr, 0x1000, MEM_RESERVE | MEM_COMMIT,
                                  PAGE_EXECUTE_READWRITE);
    }
    if (!mem) {
        Wh_Log(L"v3.2.0: VirtualAlloc failed");
        return false;
    }
    g_gradPage = mem;
    BYTE* p = mem;

    // 0x00: a fresh copy of the native-frame helper body (rcx only, no
    // dependency on the other layer's page). v3.1.0: always false, matching
    // the riced build's runtime behavior.
    BYTE* sune = p;
    const BYTE suneImpl[] = { 0x31, 0xC0, 0xC3 }; // xor eax,eax; ret
    EmitBytes(p, suneImpl, sizeof(suneImpl));

    // 0x20: the fullscreen guard. The riced build's own guard (found at
    // 0x4919F35 in its image) gates the answer on a Host virtual chain that
    // would need several more stock re-pins to port safely; until then the
    // answer stays the v3.1.0 one (transparent, recorded in g_fsActive) with
    // the stock's null check replayed. No dereferences beyond the stock's.
    p = mem + 0x20;
    BYTE* guard = p;
    BYTE* hitsBase = mem + 0x2F0;   // per-cave execution counters, read back live
    auto emitMark = [&](int idx) {
        *p++ = 0x48; *p++ = 0xB8;
        BYTE* h = hitsBase + idx; memcpy(p, &h, 8); p += 8;  // movabs rax,&hits[idx]
        *p++ = 0xFE; *p++ = 0x00;                            // inc byte [rax]
    };
    // v3.1.0 parity: the site always answers transparent, with the state
    // recorded. The stock's own deref is replayed by nothing - the old patch
    // (B0 01 C3) never dereferenced either, and returning 0 on the null path
    // turned the acrylic off in practice.
    BYTE* fsPtr = (BYTE*)&g_fsActive;
    emitMark(0);
    *p++ = 0x48; *p++ = 0xB8;
    memcpy(p, &fsPtr, 8); p += 8;           // movabs rax,&g_fsActive
    *p++ = 0xC6; *p++ = 0x00; *p++ = 0x00;  // mov byte [rax],0
    *p++ = 0xB0; *p++ = 0x01;               // mov al,1
    *p++ = 0xC3;                            // ret

    // 0xC0: the sidebar new-tab hide. Replays the store, hides the button
    // through its own vtable, resumes at the stock's next instruction.
    p = mem + 0xC0;
    BYTE* nt = p;
    emitMark(1);
    const BYTE ntReplay[] = {0x4C, 0x89, 0xB6, 0x50, 0x03, 0x00, 0x00};
    EmitBytes(p, ntReplay, 7);                // mov [rsi+0x350],r14 (replay)
    *p++ = 0x49; *p++ = 0x8B; *p++ = 0x06;    // mov rax,[r14]
    BYTE* vtSlot = hitsBase + 0x10;
    *p++ = 0x48; *p++ = 0xBA;                 // movabs rdx,&vtable capture
    memcpy(p, &vtSlot, 8); p += 8;
    *p++ = 0x48; *p++ = 0x89; *p++ = 0x02;    // mov [rdx],rax
    const BYTE ntHide[] = {0x4C, 0x89, 0xF1,             // mov rcx,r14 (button)
                           0x31, 0xD2,                   // xor edx,edx (false)
                           0xFF, 0x90, 0x90, 0x00, 0x00, 0x00}; // call [rax+0x90]
                           // rax was loaded from [r14] above: the button's
                           // live vptr; slot 18 = View::SetVisible (read at
                           // runtime, no pinned vtable address needed). The
                           // old FF 50 90 encoded [rax-0x70] - signed disp8
                           // trap.
    EmitBytes(p, ntHide, sizeof(ntHide));
    EmitJmpRel32(p, (BYTE*)chrome + kRvaNtResume);

    // 0x100: the tab-pill stub on the stock stroke DrawPath site inside
    // PaintTabBackgroundFill (0xAAC9970 on 0.21.3.1). This is a mid-function
    // patch, so the stub ends with a jmp back to 0xAAC9D30, not a ret. rsp
    // is 16-byte aligned at the site (7 pushes + sub 0x2D0 + call), so sub
    // 0x50 keeps every call inside the stub aligned too. xmm6 still holds
    // the scale UndoDeviceScaleFactor returned at 0xAAC9B82; it rides in
    // the arg5 slot.
    p = mem + 0x100;
    BYTE* pill = p;
    emitMark(2);
    const BYTE pillFrame[] = {0x48, 0x83, 0xEC, 0x50,              // sub rsp,0x50
                              0x48, 0x89, 0x4C, 0x24, 0x28,        // mov [rsp+0x28],rcx
                              0x48, 0x89, 0x54, 0x24, 0x30,        // mov [rsp+0x30],rdx
                              0x4C, 0x89, 0x44, 0x24, 0x38,        // mov [rsp+0x38],r8
                              0x66, 0x48, 0x0F, 0x7E, 0xF0,        // movq rax,xmm6
                              0x48, 0x89, 0x44, 0x24, 0x20};       // mov [rsp+0x20],rax
    EmitBytes(p, pillFrame, sizeof(pillFrame));
    // PillStrokeC(canvas, path, fillFlags, strokeFlags, scale). The caller's
    // fill flags ([rsp+0xA0] before the patch, still alive here) sit at
    // [rsp+0xF0] inside this frame.
    const BYTE pillArg[] = {0x48, 0x8B, 0x4C, 0x24, 0x28,          // mov rcx,[rsp+0x28]
                            0x48, 0x8B, 0x54, 0x24, 0x30,          // mov rdx,[rsp+0x30]
                            0x4C, 0x8D, 0x84, 0x24, 0xF0, 0x00,
                            0x00, 0x00,                            // lea r8,[rsp+0xF0]
                            0x4C, 0x8B, 0x4C, 0x24, 0x38};         // mov r9,[rsp+0x38]
    EmitBytes(p, pillArg, sizeof(pillArg));
    EmitCallAbs64(p, (void*)&PillStrokeC);                 // gradient edge
    const BYTE pillEpi[] = {0x48, 0x83, 0xC4, 0x50};       // add rsp,0x50
    EmitBytes(p, pillEpi, sizeof(pillEpi));
    EmitJmpRel32(p, (BYTE*)chrome + kRvaPillResume);

    // 0x180: the omnibox stub on the inline solid-painter build (0x1707AAA),
    // reached only for the resting omnibox and the caret-visible one. The
    // resting case installs the gradient blob with the current background
    // color (ebx); the caret case fetches the focus ring color live and
    // installs the blob with a solid stroke. All other states never reach
    // here, so the stock factory call later in RefreshBackground stays
    // untouched.
    p = mem + 0x180;
    BYTE* omni = p;
    emitMark(3);
    *p++ = 0x41; *p++ = 0x83; *p++ = 0xFC; *p++ = 0x01;    // cmp r12d,1 (caret)
    BYTE* jeCaret = p; *p++ = 0x74; p += 1;                // je .caret
    emitMark(5);                                           // resting branch ran
    void* blob = g_omniPainter;
    *p++ = 0x48; *p++ = 0xB8;
    memcpy(p, &blob, 8); p += 8;                           // movabs rax,blob
    *p++ = 0x89; *p++ = 0x58; *p++ = 0x08;                 // mov [rax+8],ebx (bg)
    *p++ = 0xC7; *p++ = 0x40; *p++ = 0x0C;                 // mov dword [rax+0xC],0
    *p++ = 0; *p++ = 0; *p++ = 0; *p++ = 0;                //   (gradient stroke)
    *p++ = 0x49; *p++ = 0x89; *p++ = 0xC6;                 // mov r14,rax
    EmitJmpRel32(p, (BYTE*)chrome + kRvaOmniConv);           // to the convergence
    *jeCaret = 0x74;
    *(signed char*)(jeCaret + 1) = (signed char)(p - (jeCaret + 2));
    emitMark(6);                                           // caret branch ran
    *p++ = 0x48; *p++ = 0x89; *p++ = 0xF1;                 // .caret: mov rcx,rsi
    EmitCallRel32(p, (BYTE*)chrome + kRvaProvider);        // color provider
    *p++ = 0x48; *p++ = 0x89; *p++ = 0xC1;                 // mov rcx,rax
    *p++ = 0xBA; *p++ = 0x3F; *p++ = 0x01; *p++ = 0x00; *p++ = 0x00;  // mov edx,0x13F
    EmitCallRel32(p, (BYTE*)chrome + kRvaGetColor);        // focus ring color
    *p++ = 0x48; *p++ = 0xB8;
    memcpy(p, &blob, 8); p += 8;                           // movabs rax,blob
    *p++ = 0x89; *p++ = 0x58; *p++ = 0x08;                 // mov [rax+8],ebx (bg)
    *p++ = 0xC7; *p++ = 0x40; *p++ = 0x0C;                 // mov dword [rax+0xC],1
    *p++ = 1; *p++ = 0; *p++ = 0; *p++ = 0;                //   (solid stroke)
    *p++ = 0x89; *p++ = 0x40; *p++ = 0x10;                 // mov [rax+0x10],eax
    *p++ = 0x49; *p++ = 0x89; *p++ = 0xC6;                 // mov r14,rax
    EmitJmpRel32(p, (BYTE*)chrome + kRvaOmniConv);           // to the convergence

    // 0x200: the MakeLinearGradient thunk plus its zeroed argument blobs.
    p = mem + 0x200;
    BYTE* mlg = p;
    const BYTE mlgFrame[] = {0x48, 0x83, 0xEC, 0x58};
    EmitBytes(p, mlgFrame, 4);                    // sub rsp,0x58
    const BYTE mlgCount[] = {0x48, 0xC7, 0x44, 0x24, 0x20, 0x02, 0, 0, 0};
    EmitBytes(p, mlgCount, 9);                    // mov qword [rsp+0x20],2
    const BYTE mlgTile[] = {0x48, 0xC7, 0x44, 0x24, 0x28, 0, 0, 0, 0};
    EmitBytes(p, mlgTile, 9);                     // mov qword [rsp+0x28],0
    *p++ = 0x48; *p++ = 0x8D; *p++ = 0x05;        // lea rax,[rip+interp]
    BYTE* lea1 = p; p += 4;
    const BYTE mlgSt1[] = {0x48, 0x89, 0x44, 0x24, 0x30};
    EmitBytes(p, mlgSt1, 5);                      // mov [rsp+0x30],rax
    const BYTE mlgZ38[] = {0x48, 0xC7, 0x44, 0x24, 0x38, 0, 0, 0, 0};
    EmitBytes(p, mlgZ38, 9);                      // mov qword [rsp+0x38],0
    const BYTE mlgZ40[] = {0x48, 0xC7, 0x44, 0x24, 0x40, 0, 0, 0, 0};
    EmitBytes(p, mlgZ40, 9);                      // mov qword [rsp+0x40],0
    *p++ = 0x48; *p++ = 0x8D; *p++ = 0x05;        // lea rax,[rip+z16]
    BYTE* lea2 = p; p += 4;
    const BYTE mlgSt2[] = {0x48, 0x89, 0x44, 0x24, 0x48};
    EmitBytes(p, mlgSt2, 5);                      // mov [rsp+0x48],rax
    EmitCallRel32(p, (BYTE*)chrome + kRvaMlg);
    const BYTE mlgEpi[] = {0x48, 0x83, 0xC4, 0x58, 0xC3};
    EmitBytes(p, mlgEpi, 5);                      // add rsp,0x58; ret
    p = (BYTE*)(((SIZE_T)p + 15) & ~(SIZE_T)15);
    BYTE* interp = p;
    memset(p, 0, 19); p += 19;
    p = (BYTE*)(((SIZE_T)p + 15) & ~(SIZE_T)15);
    BYTE* z16 = p;
    memset(p, 0, 16); p += 16;
    *(DWORD*)lea1 = (DWORD)(INT64)(interp - (lea1 + 4));
    *(DWORD*)lea2 = (DWORD)(INT64)(z16 - (lea2 + 4));
    g_mlgThunk = (void (*)(void*, void*, void*, const void*))mlg;

    // The stock-shaped painter and its three-slot vtable: a no-op deleting
    // destructor (the object is static and must survive SetBackground), the
    // stock's own second slot body, and the riced painter's Paint.
    p = (BYTE*)(((SIZE_T)p + 15) & ~(SIZE_T)15);
    BYTE* noopRet = p;
    *p++ = 0xC3;
    p = (BYTE*)(((SIZE_T)p + 15) & ~(SIZE_T)15);
    BYTE* zeroSlot = p;
    const BYTE zeroBody[] = {0x48, 0x89, 0xD0, 0x48, 0xC7, 0x02, 0, 0, 0, 0, 0xC3};
    EmitBytes(p, zeroBody, sizeof(zeroBody));
    void* vft[3] = {noopRet, zeroSlot, (void*)&GradPainterPaint};
    memcpy(g_painterVft, vft, sizeof(vft));
    memset(g_omniPainter, 0, sizeof(g_omniPainter));
    *(void**)g_omniPainter = g_painterVft;

    // Route the four sites into the caves.
    struct Write { DWORD rva; int len; BYTE* cave; bool isCall;
                   const BYTE* raw; };
    const Write writes[4] = {
        {kRvaFsGuard, 13, guard, false, nullptr},
        {kRvaNtHide, 7, nt, false, nullptr},
        {kRvaPillDraw, 5, pill, false, nullptr},
        {kRvaOmniB, 5, omni, false, nullptr},
    };
    for (int i = 0; i < 4; i++) {
        BYTE* at = (BYTE*)chrome + writes[i].rva;
        if (writes[i].raw) {
            DWORD oldProtect, tmp;
            if (!VirtualProtect(at, writes[i].len, PAGE_EXECUTE_READWRITE,
                                &oldProtect)) {
                Wh_Log(L"v3.3.0: VirtualProtect failed at raw %d", i);
                return false;
            }
            memcpy(at, writes[i].raw, writes[i].len);
            VirtualProtect(at, writes[i].len, oldProtect, &tmp);
            if (memcmp(at, writes[i].raw, writes[i].len) != 0) {
                Wh_Log(L"v3.3.0: raw %d read-back mismatch", i);
                return false;
            }
            Wh_Log(L"Helium acrylic: v3.3.0 raw patch %d live at RVA 0x%zX",
                   i, (size_t)writes[i].rva);
            continue;
        }
        INT64 rel = (INT64)writes[i].cave - (INT64)(at + 5);
        if (rel > 0x7FFFFFFF || rel < -0x7FFFFFFF) {
            Wh_Log(L"v3.2.0: cave %d out of jump range - untouched", i);
            return false;
        }
        DWORD oldProtect, tmp;
        if (!VirtualProtect(at, writes[i].len, PAGE_EXECUTE_READWRITE,
                            &oldProtect)) {
            Wh_Log(L"v3.2.0: VirtualProtect failed at cave %d", i);
            return false;
        }
        BYTE* saved = nullptr;
        int savedLen = writes[i].len;
        switch (i) {
            case 0: saved = g_fsGuardOrig; break;
            case 1: saved = g_ntOrig; break;
            case 2: saved = g_pillOrig; break;
            case 3: saved = g_omniOrig; break;
        }
        memcpy(saved, at, savedLen);
        BYTE jmp[5] = {(BYTE)(writes[i].isCall ? 0xE8 : 0xE9), 0, 0, 0, 0};
        *(DWORD*)(jmp + 1) = (DWORD)rel;
        memcpy(at, jmp, 5);
        for (int j = 5; j < writes[i].len; j++) at[j] = 0x90;
        if (memcmp(at, jmp, sizeof(jmp)) != 0) {
            // Never leave a half-written branch live: restore and fail.
            memcpy(at, saved, savedLen);
            Wh_Log(L"v3.2.0: cave %d read-back mismatch - restored", i);
        }
        VirtualProtect(at, writes[i].len, oldProtect, &tmp);
        if (memcmp(at, jmp, sizeof(jmp)) != 0) {
            return false;
        }
        switch (i) {
            case 0: g_fsGuardSite = at; break;
            case 1: g_ntSite = at; break;
            case 2: g_pillSite = at; break;
            case 3: g_omniSite = at; break;
        }
        Wh_Log(L"Helium acrylic: v3.2.0 cave %d live at RVA 0x%zX", i,
               (size_t)writes[i].rva);
    }
    g_gradApplied = true;
    Wh_Log(L"Helium acrylic: v3.2.0 live (fullscreen guard, sidebar new-tab"
           L" hidden, tab-pill gradient, omnibox gradient)");
    NudgeCtx nc;
    nc.pid = GetCurrentProcessId();
    nc.n = 0;
    EnumWindows(NudgeEnum, (LPARAM)&nc);
    for (int i = 0; i < nc.n; i++)
        PostMessageW(nc.hwnds[i], WM_THEMECHANGED, 0, 0);
    MTRACE("v320: theme nudge posted");
    return true;
}

// v3.9.0: make changes show on windows that are already open. Enabling the
// mod or saving a setting used to wait for the next browser start for the
// see-through and frame layers, and up to two seconds for the blur.
// WM_DWMCOMPOSITIONCHANGED makes Chromium ask again whether the window is
// see-through and which frame it uses, so a patch written just now is
// answered on open windows too; WM_THEMECHANGED re-lays the caption. Only
// posts, so it is safe from any thread.
static void LiveRefresh(bool backdrop) {
    if (!GetModuleHandleW(L"chrome.dll")) return;
    if (backdrop) {
        BackdropCtx ctx = { GetCurrentProcessId() };
        EnumWindows(BackdropEnumProc, (LPARAM)&ctx);
    }
    NudgeCtx nc;
    nc.pid = GetCurrentProcessId();
    nc.n = 0;
    EnumWindows(NudgeEnum, (LPARAM)&nc);
    for (int i = 0; i < nc.n; i++) {
        PostMessageW(nc.hwnds[i], WM_DWMCOMPOSITIONCHANGED, 0, 0);
        PostMessageW(nc.hwnds[i], WM_THEMECHANGED, 0, 0);
    }
    MTRACE("live: refresh posted");
}

// Takes every open window back to stock blur: no accent, so Windows draws
// the window the way the browser asked for it.
static BOOL CALLBACK ClearAccentEnumProc(HWND hwnd, LPARAM lp) {
    DWORD pid = 0;
    GetWindowThreadProcessId(hwnd, &pid);
    if (pid != (DWORD)lp) return TRUE;
    wchar_t cls[64];
    if (!GetClassNameW(hwnd, cls, 64) || wcscmp(cls, L"Chrome_WidgetWin_1") != 0)
        return TRUE;
    PFN_SetWindowCompositionAttribute wca = GetSetWindowCompositionAttribute();
    if (wca) {
        ACCENTPOLICY off = { 0, 0, 0, 0 };
        WINDOWCOMPOSITIONATTRDATA d = { 19, &off, sizeof(off) };
        wca(hwnd, &d);
    }
    RemovePropW(hwnd, L"HeliumAcrylicPopupClear");
    return TRUE;
}

static void RestoreAcrylic() {
    if (!g_acrylicApplied || !g_acrylicTarget) return;
    DWORD oldProtect, tmp;
    if (VirtualProtect(g_acrylicTarget, sizeof(g_acrylicOriginal), PAGE_EXECUTE_READWRITE, &oldProtect)) {
        memcpy(g_acrylicTarget, g_acrylicOriginal, sizeof(g_acrylicOriginal));
        VirtualProtect(g_acrylicTarget, sizeof(g_acrylicOriginal), oldProtect, &tmp);
    }
    g_acrylicApplied = false;
}

static void RestoreFrame() {
    for (int i = 0; i < 4; i++) {
        if (g_frameSites[i].applied && g_frameSites[i].target) {
            DWORD oldProtect, tmp;
            if (VirtualProtect(g_frameSites[i].target, g_frameSites[i].size,
                               PAGE_EXECUTE_READWRITE, &oldProtect)) {
                memcpy(g_frameSites[i].target, g_frameSites[i].original,
                       g_frameSites[i].size);
                VirtualProtect(g_frameSites[i].target, g_frameSites[i].size,
                               oldProtect, &tmp);
            }
            g_frameSites[i].applied = false;
        }
    }
    g_frameApplied = false;
}

static void ApplyOnePass() {
    ApplyV320();
    MTRACE("pass: v320 returned");
    if (g_set.acrylic) {
        ApplyAcrylicPatch();
        MTRACE("pass: acrylic returned");
    }
    if (g_set.colors) {
        InstallColorHook();
        MTRACE("pass: colors returned");
    }
    if (g_set.nativeFrame) {
        ApplyStructuralPatches();
        MTRACE("pass: frame returned");
    }
}

// v3.1.0: a browser that starts while Windhawk is still delivering the mod
// used to keep whatever a single early scan managed to do for the rest of
// its life. One deferred re-pass (guards make the layers idempotent) closes
// that window; a build where nothing matched at all is left alone, so the
// riced install's processes never rescan.
static DWORD WINAPI RetryOnceThread(LPVOID) {
    if (WaitOrStop(10000)) return 0;
    if (g_acrylicApplied && g_colorsApplied && g_frameApplied &&
        g_gradApplied) return 0;
    if (!GetModuleHandleW(L"chrome.dll")) return 0;
    if (!g_acrylicApplied && !g_colorsApplied && !g_frameApplied &&
        !g_gradApplied) return 0;
    ApplyOnePass();
    LiveRefresh(false);
    Wh_Log(L"apply state after retry: acrylic=%d colors=%d frame=%d",
           (int)g_acrylicApplied, (int)g_colorsApplied,
           (int)g_frameApplied);
    return 0;
}

static void ApplyAllLayers() {
    ApplyOnePass();
    StartModThread(RetryOnceThread);
}

static DWORD WINAPI InitThread(LPVOID) {
    for (int i = 0; i < 300 && !g_stop; i++) {
        if (GetModuleHandleW(L"chrome.dll")) break;
        if (WaitOrStop(200)) return 0;
    }
    if (g_stop) return 0;
    ApplyAllLayers();
    StartModThread(ThemeThread);
    return 0;
}

// v3.3.3: Helium's web toolbar draws its own window buttons whenever its
// code does not see --hide-window-buttons, in places the two branch flips
// cannot reach (renderer-side toolbar state; proven live 2026-11-18: the
// patched browser still showed them while a real switch on the command line
// did not). So the switch must hold globally: append it to this process's
// command line before Chromium parses it. Runs in the browser process only
// (children get their state from the browser); the buffer append is bounded
// by the owning memory region so it can never overrun.
static void EnsureHideWindowButtonsSwitch() {
    MTRACE("hwb: enter");
    LPWSTR cmd = GetCommandLineW();
    if (!cmd) { MTRACE("hwb: no command line"); return; }
    if (wcsstr(cmd, L" --hide-window-buttons")) { MTRACE("hwb: already present"); return; }
    if (wcsstr(cmd, L"--type=")) { MTRACE("hwb: child process, skip"); return; }
    size_t len = wcslen(cmd);
    const wchar_t add[] = L" --hide-window-buttons";
    const size_t addWchars = (sizeof(add) / sizeof(wchar_t));  // incl. NUL
    // v3.9.3: insert right after the program name, never at the end. Links
    // open as `chrome.exe --single-argument <url>`, and Chromium reads
    // everything after --single-argument as the address, so an appended
    // switch became part of every link ("/%20--hide-window-buttons", a 404).
    size_t pos = 0;
    if (cmd[0] == L'"') {
        const wchar_t* q = wcschr(cmd + 1, L'"');
        pos = q ? (size_t)(q - cmd) + 1 : len;
    } else {
        while (pos < len && cmd[pos] != L' ' && cmd[pos] != L'\t') pos++;
    }
    MEMORY_BASIC_INFORMATION mbi;
    if (!VirtualQuery(cmd, &mbi, sizeof(mbi))) {
        MTRACE("hwb: VirtualQuery failed");
        return;
    }
    SIZE_T avail = ((BYTE*)mbi.BaseAddress + mbi.RegionSize) - (BYTE*)cmd;
    Wh_Log(L"hide-window-buttons: len=%zu need=%zu avail=%zu protect=0x%zX",
           len, addWchars, (size_t)avail, (size_t)mbi.Protect);
    if ((len + addWchars) * sizeof(wchar_t) > avail) {
        MTRACE("hwb: buffer too small");
        return;
    }
    const size_t addLen = addWchars - 1;
    memmove(cmd + pos + addLen, cmd + pos, (len - pos + 1) * sizeof(wchar_t));
    memcpy(cmd + pos, add, addLen * sizeof(wchar_t));
    Wh_Log(L"hide-window-buttons: inserted at %zu", pos);
    MTRACE("hwb: appended to command line");
}

// ---------------------------------------------------------------------------
// Part 5: the app icon.
//
// Helium's own logo (the IDR_MAINFRAME icon in chrome.exe) repainted in the
// rice: the plate runs blue #89B4FA to mauve #CBA6F7 on the diagonal and the
// white star turns #11111B, the look of the Mocha Windhawk icon. The same
// pixels go to the windows (re-applied when Chromium puts its own icon back)
// and to an .ico file the user's Helium shortcuts point at. A chrome.exe whose
// logo is not Helium's blue plate gets the Seamless globe badge instead.
static std::atomic<bool> g_iconWant{false};
static HICON g_badgeSmall = nullptr;
static HICON g_badgeBig = nullptr;
static UINT g_badgeDpi = 0;
static HICON g_origClassIcon = nullptr;
static HICON g_origClassIconSm = nullptr;
static bool g_classIconReplaced = false;

static HICON MakeBadgeIcon(int size, WCHAR glyph) {
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
    HBITMAP glyphBm = CreateDIBSection(screen, &bi, DIB_RGB_COLORS, &glyphBits, nullptr, 0);
    ReleaseDC(nullptr, screen);
    if (!color || !glyphBm) {
        if (color) DeleteObject(color);
        if (glyphBm) DeleteObject(glyphBm);
        return nullptr;
    }
    HDC dc = CreateCompatibleDC(nullptr);
    HGDIOBJ old = SelectObject(dc, glyphBm);
    memset(glyphBits, 0, (size_t)size * size * 4);
    HFONT font = CreateFontW(-(int)(size * 0.84f), 0, 0, 0, FW_NORMAL, 0, 0, 0,
                             DEFAULT_CHARSET, 0, 0, ANTIALIASED_QUALITY, 0,
                             L"Segoe Fluent Icons");
    HGDIOBJ oldFont = SelectObject(dc, font);
    SetBkMode(dc, TRANSPARENT);
    SetTextColor(dc, RGB(255, 255, 255));
    RECT r{0, 0, size, size};
    WCHAR g[2] = {glyph, 0};
    DrawTextW(dc, g, 1, &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE | DT_NOPREFIX);
    GdiFlush();
    SelectObject(dc, oldFont);
    DeleteObject(font);
    SelectObject(dc, old);
    DeleteDC(dc);

    float c0[3], c1[3];
    AccentFloats(c0, c1, 255.f);
    uint32_t* px = (uint32_t*)bits;
    const uint32_t* gp = (const uint32_t*)glyphBits;
    for (int y = 0; y < size; y++)
        for (int x = 0; x < size; x++) {
            float t = std::clamp((x + y) / (2.0f * (size - 1)), 0.0f, 1.0f);
            float cov = ((gp[y * size + x] >> 8) & 0xFF) / 255.0f;
            float rgb[3];
            for (int i = 0; i < 3; i++) {
                float base = c0[i] + (c1[i] - c0[i]) * t;
                rgb[i] = base * cov;
            }
            px[y * size + x] = ((uint32_t)(cov * 255 + 0.5f) << 24) |
                               ((uint32_t)(rgb[0] * 255 + 0.5f) << 16) |
                               ((uint32_t)(rgb[1] * 255 + 0.5f) << 8) |
                               (uint32_t)(rgb[2] * 255 + 0.5f);
        }
    HBITMAP mask = CreateBitmap(size, size, 1, 1, nullptr);
    ICONINFO ii{TRUE, 0, 0, mask, color};
    HICON icon = CreateIconIndirect(&ii);
    DeleteObject(mask);
    DeleteObject(color);
    DeleteObject(glyphBm);
    return icon;
}

// Helium's logo at one size as top-down BGRA with straight alpha, repainted.
// False when the icon is missing or is not Helium's blue plate.
static bool RicedLogoPixels(int size, std::vector<uint32_t>& px) {
    // Scale-down loading picks the next larger image and shrinks it cleanly.
    // Looked up at run time so a comctl32 without it only costs quality.
    typedef HRESULT(WINAPI * ScaleDownFn)(HINSTANCE, PCWSTR, int, int, HICON*);
    static ScaleDownFn scaleDown = [] {
        HMODULE cc = GetModuleHandleW(L"comctl32.dll");
        if (!cc) cc = LoadLibraryW(L"comctl32.dll");
        return cc ? (ScaleDownFn)GetProcAddress(cc, "LoadIconWithScaleDown") : nullptr;
    }();
    HINSTANCE exe = GetModuleHandleW(nullptr);
    HICON src = nullptr;
    if (!scaleDown || FAILED(scaleDown(exe, L"IDR_MAINFRAME", size, size, &src)))
        src = (HICON)LoadImageW(exe, L"IDR_MAINFRAME", IMAGE_ICON, size, size, 0);
    if (!src) return false;
    ICONINFO ii{};
    bool ok = GetIconInfo(src, &ii) && ii.hbmColor;
    if (ok) {
        BITMAP bm{};
        ok = GetObjectW(ii.hbmColor, sizeof(bm), &bm) && bm.bmWidth == size &&
             bm.bmHeight == size;
    }
    if (ok) {
        BITMAPINFO bi{};
        bi.bmiHeader.biSize = sizeof(bi.bmiHeader);
        bi.bmiHeader.biWidth = size;
        bi.bmiHeader.biHeight = -size;
        bi.bmiHeader.biPlanes = 1;
        bi.bmiHeader.biBitCount = 32;
        px.assign((size_t)size * size, 0);
        HDC dc = GetDC(nullptr);
        ok = GetDIBits(dc, ii.hbmColor, 0, size, px.data(), &bi, DIB_RGB_COLORS) == size;
        ReleaseDC(nullptr, dc);
    }
    if (ii.hbmColor) DeleteObject(ii.hbmColor);
    if (ii.hbmMask) DeleteObject(ii.hbmMask);
    DestroyIcon(src);
    if (!ok) return false;

    // The plate's colour, read just inside its left edge at mid height.
    uint32_t ref = px[(size_t)(size / 2) * size + size / 8];
    int pr = (ref >> 16) & 0xFF, pg = (ref >> 8) & 0xFF, pb = ref & 0xFF;
    if ((ref >> 24) < 0xF0 || pb < pr + 80 || pb < pg + 60) return false;
    float plate = (float)std::min({pr, pg, pb});

    float c0[3], c1[3];
    AccentFloats(c0, c1, 1.f);
    const float ink[3] = {0x11, 0x11, 0x1B};
    for (int y = 0; y < size; y++)
        for (int x = 0; x < size; x++) {
            uint32_t p = px[(size_t)y * size + x];
            uint32_t a = p >> 24;
            if (!a) continue;
            int m = std::min({(int)((p >> 16) & 0xFF), (int)((p >> 8) & 0xFF), (int)(p & 0xFF)});
            float cov = std::clamp((m - plate) / (255.0f - plate), 0.0f, 1.0f);
            float t = std::clamp((x + y) / (2.0f * (size - 1)), 0.0f, 1.0f);
            uint32_t rgb[3];
            for (int i = 0; i < 3; i++) {
                float base = c0[i] + (c1[i] - c0[i]) * t;
                rgb[i] = (uint32_t)(base + (ink[i] - base) * cov + 0.5f);
            }
            px[(size_t)y * size + x] = (a << 24) | (rgb[0] << 16) | (rgb[1] << 8) | rgb[2];
        }
    return true;
}

static HICON MakeRicedAppIcon(int size) {
    std::vector<uint32_t> px;
    if (!RicedLogoPixels(size, px)) return nullptr;
    BITMAPINFO bi{};
    bi.bmiHeader.biSize = sizeof(bi.bmiHeader);
    bi.bmiHeader.biWidth = size;
    bi.bmiHeader.biHeight = -size;
    bi.bmiHeader.biPlanes = 1;
    bi.bmiHeader.biBitCount = 32;
    void* bits = nullptr;
    HBITMAP color = CreateDIBSection(nullptr, &bi, DIB_RGB_COLORS, &bits, nullptr, 0);
    if (!color) return nullptr;
    memcpy(bits, px.data(), px.size() * 4);
    HBITMAP mask = CreateBitmap(size, size, 1, 1, nullptr);
    ICONINFO ii{TRUE, 0, 0, mask, color};
    HICON icon = CreateIconIndirect(&ii);
    DeleteObject(mask);
    DeleteObject(color);
    return icon;
}

static HICON MakeAppIcon(int size) {
    HICON icon = MakeRicedAppIcon(size);
    return icon ? icon : MakeBadgeIcon(size, 0xE774);
}

static void RefreshBadges(UINT dpi) {
    if (g_badgeSmall && g_badgeBig && dpi == g_badgeDpi) return;
    if (g_badgeSmall) DestroyIcon(g_badgeSmall);
    if (g_badgeBig) DestroyIcon(g_badgeBig);
    g_badgeSmall = MakeAppIcon(GetSystemMetricsForDpi(SM_CXSMICON, dpi));
    g_badgeBig = MakeAppIcon(GetSystemMetricsForDpi(SM_CXICON, dpi));
    g_badgeDpi = dpi;
    Wh_Log(L"icon: app icons drawn for dpi %u", dpi);
}

// ---- shortcuts ------------------------------------------------------------
// Only the browser process (no --type=) touches files. The .ico lives beside
// the Mocha Windhawk icon; a shortcut is changed only when it starts this
// very chrome.exe, and turning the icon off points it back at chrome.exe,0,
// the icon Helium's installer gives it.

static bool IsBrowserProcess() {
    PCWSTR cmd = GetCommandLineW();
    return cmd && !wcsstr(cmd, L"--type=");
}

static std::wstring RicedIconFile() {
    wchar_t folder[MAX_PATH];
    if (FAILED(SHGetFolderPathW(nullptr, CSIDL_LOCAL_APPDATA, nullptr, SHGFP_TYPE_CURRENT, folder)))
        return {};
    std::wstring dir = std::wstring(folder) + L"\\Windhawk";
    CreateDirectoryW(dir.c_str(), nullptr);
    return dir + L"\\Helium-Mocha.ico";
}

// Every size as a 32-bit bitmap entry. Written only when the bytes changed,
// so Explorer's icon cache is not churned on every browser start.
static bool WriteRicedIcon(const std::wstring& path) {
    static const int kSizes[] = {16, 20, 24, 32, 40, 48, 64, 96, 128, 256};
    const int n = (int)(sizeof(kSizes) / sizeof(kSizes[0]));
    std::vector<BYTE> dir(6 + 16 * n), body;
    *(WORD*)&dir[2] = 1;
    *(WORD*)&dir[4] = (WORD)n;
    for (int i = 0; i < n; i++) {
        int s = kSizes[i];
        std::vector<uint32_t> px;
        if (!RicedLogoPixels(s, px)) return false;
        DWORD maskRow = ((s + 31) / 32) * 4;
        DWORD bytes = sizeof(BITMAPINFOHEADER) + s * s * 4 + maskRow * s;
        BYTE* e = &dir[6 + 16 * i];
        e[0] = (BYTE)(s & 0xFF);
        e[1] = (BYTE)(s & 0xFF);
        *(WORD*)&e[4] = 1;
        *(WORD*)&e[6] = 32;
        *(DWORD*)&e[8] = bytes;
        *(DWORD*)&e[12] = (DWORD)(dir.size() + body.size());
        BITMAPINFOHEADER h{};
        h.biSize = sizeof(h);
        h.biWidth = s;
        h.biHeight = s * 2;
        h.biPlanes = 1;
        h.biBitCount = 32;
        h.biSizeImage = s * s * 4 + maskRow * s;
        const BYTE* hp = (const BYTE*)&h;
        body.insert(body.end(), hp, hp + sizeof(h));
        for (int y = s - 1; y >= 0; y--) {
            const BYTE* row = (const BYTE*)&px[(size_t)y * s];
            body.insert(body.end(), row, row + s * 4);
        }
        body.insert(body.end(), (size_t)maskRow * s, 0);
    }
    dir.insert(dir.end(), body.begin(), body.end());

    HANDLE f = CreateFileW(path.c_str(), GENERIC_READ, FILE_SHARE_READ, nullptr,
                           OPEN_EXISTING, 0, nullptr);
    if (f != INVALID_HANDLE_VALUE) {
        LARGE_INTEGER len{};
        bool same = false;
        if (GetFileSizeEx(f, &len) && len.QuadPart == (LONGLONG)dir.size()) {
            std::vector<BYTE> old(dir.size());
            DWORD got = 0;
            same = ReadFile(f, old.data(), (DWORD)old.size(), &got, nullptr) &&
                   got == old.size() && old == dir;
        }
        CloseHandle(f);
        if (same) return true;
    }
    std::wstring tmp = path + L".tmp";
    f = CreateFileW(tmp.c_str(), GENERIC_WRITE, 0, nullptr, CREATE_ALWAYS, 0, nullptr);
    if (f == INVALID_HANDLE_VALUE) return false;
    DWORD wrote = 0;
    bool ok = WriteFile(f, dir.data(), (DWORD)dir.size(), &wrote, nullptr) && wrote == dir.size();
    CloseHandle(f);
    if (!ok || !MoveFileExW(tmp.c_str(), path.c_str(), MOVEFILE_REPLACE_EXISTING)) {
        DeleteFileW(tmp.c_str());
        return false;
    }
    Wh_Log(L"icon: wrote %s", path.c_str());
    return true;
}

static int RetargetShortcut(IShellLinkW* link, IPersistFile* file, const std::wstring& path,
                            PCWSTR exe, const std::wstring& icon, bool riced) {
    if (FAILED(file->Load(path.c_str(), STGM_READ))) return 0;
    wchar_t target[MAX_PATH], expanded[MAX_PATH], image[MAX_PATH];
    int index = 0;
    if (FAILED(link->GetPath(target, MAX_PATH, nullptr, SLGP_RAWPATH)) ||
        FAILED(link->GetIconLocation(image, MAX_PATH, &index)))
        return 0;
    DWORD n = ExpandEnvironmentStringsW(target, expanded, MAX_PATH);
    if (!n || n > MAX_PATH || _wcsicmp(expanded, exe) != 0) return 0;
    bool isRiced = _wcsicmp(image, icon.c_str()) == 0;
    if (riced == isRiced) return 0;
    if (FAILED(link->SetIconLocation(riced ? icon.c_str() : exe, 0)) ||
        FAILED(file->Save(path.c_str(), TRUE)))
        return 0;
    SHChangeNotify(SHCNE_UPDATEITEM, SHCNF_PATHW, path.c_str(), nullptr);
    Wh_Log(L"icon: %s -> %s", path.c_str(), riced ? L"riced" : L"stock");
    return 1;
}

static int RetargetFolder(IShellLinkW* link, IPersistFile* file, const std::wstring& folder,
                          PCWSTR exe, const std::wstring& icon, bool riced, bool subfolders) {
    int changed = 0;
    WIN32_FIND_DATAW fd;
    HANDLE h = FindFirstFileW((folder + L"\\*").c_str(), &fd);
    if (h == INVALID_HANDLE_VALUE) return 0;
    do {
        std::wstring name = fd.cFileName;
        if (name == L"." || name == L"..") continue;
        std::wstring full = folder + L"\\" + name;
        if (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
            if (subfolders && !(fd.dwFileAttributes & FILE_ATTRIBUTE_REPARSE_POINT))
                changed += RetargetFolder(link, file, full, exe, icon, riced, false);
        } else if (name.size() > 4 && _wcsicmp(name.c_str() + name.size() - 4, L".lnk") == 0) {
            changed += RetargetShortcut(link, file, full, exe, icon, riced);
        }
    } while (FindNextFileW(h, &fd));
    FindClose(h);
    return changed;
}

// Start menu (one folder deep), desktop and taskbar pins of this user.
static void UpdateShortcutIcons(bool riced) {
    std::wstring icon = RicedIconFile();
    if (icon.empty()) return;
    if (riced && !WriteRicedIcon(icon)) {
        Wh_Log(L"icon: no riced .ico (logo not Helium's), shortcuts left alone");
        return;
    }
    wchar_t exe[MAX_PATH];
    if (!GetModuleFileNameW(nullptr, exe, MAX_PATH)) return;
    HRESULT init = CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED);
    IShellLinkW* link = nullptr;
    if (SUCCEEDED(CoCreateInstance(CLSID_ShellLink, nullptr, CLSCTX_INPROC_SERVER,
                                   IID_IShellLinkW, (void**)&link))) {
        IPersistFile* file = nullptr;
        if (SUCCEEDED(link->QueryInterface(IID_IPersistFile, (void**)&file))) {
            int changed = 0;
            wchar_t folder[MAX_PATH];
            if (SUCCEEDED(SHGetFolderPathW(nullptr, CSIDL_PROGRAMS, nullptr, 0, folder)))
                changed += RetargetFolder(link, file, folder, exe, icon, riced, true);
            if (SUCCEEDED(SHGetFolderPathW(nullptr, CSIDL_DESKTOPDIRECTORY, nullptr, 0, folder)))
                changed += RetargetFolder(link, file, folder, exe, icon, riced, false);
            if (SUCCEEDED(SHGetFolderPathW(nullptr, CSIDL_APPDATA, nullptr, 0, folder)))
                changed += RetargetFolder(link, file,
                    std::wstring(folder) + L"\\Microsoft\\Internet Explorer\\Quick Launch\\User Pinned\\TaskBar",
                    exe, icon, riced, false);
            // A signed-in profile gets its own taskbar shortcut here, one folder per app.
            if (SUCCEEDED(SHGetFolderPathW(nullptr, CSIDL_APPDATA, nullptr, 0, folder)))
                changed += RetargetFolder(link, file,
                    std::wstring(folder) + L"\\Microsoft\\Internet Explorer\\Quick Launch\\User Pinned\\ImplicitAppShortcuts",
                    exe, icon, riced, true);
            file->Release();
            Wh_Log(L"icon: %d shortcut(s) set to %s", changed, riced ? L"riced" : L"stock");
        }
        link->Release();
    }
    if (SUCCEEDED(init)) CoUninitialize();
}

static bool ModDisabledInWindhawk() {
    std::wstring key = L"SOFTWARE\\Windhawk\\Engine\\Mods\\";
    key += WH_MOD_ID;
    DWORD disabled = 0, size = sizeof(disabled);
    return RegGetValueW(HKEY_LOCAL_MACHINE, key.c_str(), L"Disabled", RRF_RT_REG_DWORD,
                        nullptr, &disabled, &size) == ERROR_SUCCESS && disabled;
}

struct IconCtx { DWORD pid; };

// A window of a signed-in profile tells the taskbar which icon file to show
// (the profile's own .ico). Point that at the riced icon, and remember what it
// was so turning the icon off hands it back. A window without one is left alone:
// the taskbar already uses its window icon.
static const PROPERTYKEY kPkeyRelaunchIcon =
    {{0x9F4C2855, 0x9F79, 0x4B39, {0xA8, 0xD0, 0xE1, 0xD4, 0x2D, 0xE1, 0xD5, 0xF3}}, 3};
static std::map<HWND, std::wstring> g_relaunchOrig;

static void SetRelaunchIcon(HWND hwnd, const std::wstring& value, bool remember) {
    HRESULT init = CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED);
    IPropertyStore* store = nullptr;
    if (SUCCEEDED(SHGetPropertyStoreForWindow(hwnd, IID_IPropertyStore, (void**)&store)) && store) {
        PROPVARIANT cur;
        PropVariantInit(&cur);
        bool has = SUCCEEDED(store->GetValue(kPkeyRelaunchIcon, &cur)) && cur.vt == VT_LPWSTR &&
                   cur.pwszVal && *cur.pwszVal;
        if (has && _wcsicmp(cur.pwszVal, value.c_str()) != 0) {
            if (remember) g_relaunchOrig[hwnd] = cur.pwszVal;
            PROPVARIANT pv;
            PropVariantInit(&pv);
            size_t bytes = (value.size() + 1) * sizeof(wchar_t);
            pv.pwszVal = (PWSTR)CoTaskMemAlloc(bytes);
            if (pv.pwszVal) {
                memcpy(pv.pwszVal, value.c_str(), bytes);
                pv.vt = VT_LPWSTR;
                if (SUCCEEDED(store->SetValue(kPkeyRelaunchIcon, pv))) store->Commit();
                PropVariantClear(&pv);
            }
        }
        PropVariantClear(&cur);
        store->Release();
    }
    if (SUCCEEDED(init)) CoUninitialize();
}

static BOOL CALLBACK IconEnumProc(HWND hwnd, LPARAM lp) {
    DWORD pid = 0;
    GetWindowThreadProcessId(hwnd, &pid);
    if (pid != ((IconCtx*)lp)->pid) return TRUE;
    if (!IsWindowVisible(hwnd)) return TRUE;
    wchar_t cls[64];
    if (!GetClassNameW(hwnd, cls, 64) || wcscmp(cls, L"Chrome_WidgetWin_1") != 0)
        return TRUE;
    DWORD_PTR smallIcon = 0, bigIcon = 0;
    SendMessageTimeoutW(hwnd, WM_GETICON, ICON_SMALL, 0, SMTO_ABORTIFHUNG, 500, &smallIcon);
    SendMessageTimeoutW(hwnd, WM_GETICON, ICON_BIG, 0, SMTO_ABORTIFHUNG, 500, &bigIcon);
    if ((HICON)smallIcon == g_badgeSmall && (HICON)bigIcon == g_badgeBig) return TRUE;
    // First takeover: remember Helium's class icons so a disable or unload
    // can hand them back.
    if (!g_classIconReplaced) {
        g_origClassIcon = (HICON)GetClassLongPtrW(hwnd, GCLP_HICON);
        g_origClassIconSm = (HICON)GetClassLongPtrW(hwnd, GCLP_HICONSM);
        if (g_origClassIcon) SetClassLongPtrW(hwnd, GCLP_HICON, (LONG_PTR)g_badgeBig);
        if (g_origClassIconSm) SetClassLongPtrW(hwnd, GCLP_HICONSM, (LONG_PTR)g_badgeSmall);
        g_classIconReplaced = true;
    }
    SendMessageTimeoutW(hwnd, WM_SETICON, ICON_SMALL, (LPARAM)g_badgeSmall,
                        SMTO_ABORTIFHUNG, 500, nullptr);
    SendMessageTimeoutW(hwnd, WM_SETICON, ICON_BIG, (LPARAM)g_badgeBig,
                        SMTO_ABORTIFHUNG, 500, nullptr);
    std::wstring file = RicedIconFile();
    if (!file.empty() && GetFileAttributesW(file.c_str()) != INVALID_FILE_ATTRIBUTES)
        SetRelaunchIcon(hwnd, file + L",0", true);
    return TRUE;
}

static void RestoreHeliumIcons() {
    if (!g_classIconReplaced) return;
    for (auto& [wnd, old] : g_relaunchOrig)
        if (IsWindow(wnd)) SetRelaunchIcon(wnd, old, false);
    g_relaunchOrig.clear();
    HWND hwnd = nullptr;
    do {
        hwnd = FindWindowExW(nullptr, hwnd, L"Chrome_WidgetWin_1", nullptr);
        if (!hwnd) break;
        DWORD pid = 0;
        GetWindowThreadProcessId(hwnd, &pid);
        if (pid != GetCurrentProcessId()) continue;
        if (g_origClassIcon) SetClassLongPtrW(hwnd, GCLP_HICON, (LONG_PTR)g_origClassIcon);
        if (g_origClassIconSm) SetClassLongPtrW(hwnd, GCLP_HICONSM, (LONG_PTR)g_origClassIconSm);
        SendMessageTimeoutW(hwnd, WM_SETICON, ICON_SMALL, 0, SMTO_ABORTIFHUNG, 500, nullptr);
        SendMessageTimeoutW(hwnd, WM_SETICON, ICON_BIG, 0, SMTO_ABORTIFHUNG, 500, nullptr);
    } while (hwnd);
    g_classIconReplaced = false;
    Wh_Log(L"icon: Helium's own icons restored");
}

static DWORD WINAPI IconThread(LPVOID) {
    const bool browser = IsBrowserProcess();
    int shortcuts = -1;  // what the shortcuts were last set to this process
    while (!g_stop) {
        bool want = g_iconWant.load(std::memory_order_relaxed);
        if (browser && GetModuleHandleW(L"chrome.dll") && shortcuts != (int)want) {
            UpdateShortcutIcons(want);
            shortcuts = (int)want;
        }
        if (want && GetModuleHandleW(L"chrome.dll")) {
            RefreshBadges(GetDpiForSystem());
            IconCtx ctx = { GetCurrentProcessId() };
            EnumWindows(IconEnumProc, (LPARAM)&ctx);
        } else if (g_classIconReplaced) {
            RestoreHeliumIcons();
        }
        if (WaitOrStop(2000)) break;
    }
    return 0;
}

// Only Helium. Google Chrome and other browsers are also named chrome.exe.
static bool IsHeliumExe() {
    wchar_t exe[MAX_PATH];
    if (!GetModuleFileNameW(nullptr, exe, MAX_PATH)) return false;
    CharLowerW(exe);
    return wcsstr(exe, L"helium") != nullptr;
}

BOOL ModInit() {
    Wh_Log(L">");
    if (!IsHeliumExe()) {
        Wh_Log(L"not Helium, leaving this browser alone");
        return FALSE;
    }
    LoadSettings();
    g_iconWant.store(g_set.gradientIcon, std::memory_order_relaxed);
    if (g_set.nativeFrame) EnsureHideWindowButtonsSwitch();
    MTRACE(GetModuleHandleW(L"chrome.dll") ? "init: chrome already loaded"
                                           : "init: chrome not loaded yet");
    g_dark = ReadDarkTheme() ? 1 : 0;
    g_stopEvent = CreateEventW(nullptr, TRUE, FALSE, nullptr);
    StartModThread(BackdropThread);
    StartModThread(IconThread);
    if (GetModuleHandleW(L"chrome.dll")) {
        // Enabled while the browser is open: patch, then make the open
        // windows pick it up now instead of at the next start.
        ApplyAllLayers();
        LiveRefresh(true);
        StartModThread(ThemeThread);
    } else {
        StartModThread(InitThread);
    }
    return TRUE;
}

void ModSettingsChanged() {
    LoadSettings();
    // Colors rebuild live: restore the entry, re-emit the hook with the new
    // table. The old code page stays allocated: a thread may still be inside
    // it, and one page per settings save is nothing.
    if (g_colorsApplied && g_gcTarget) {
        DWORD oldProtect, tmp;
        if (VirtualProtect(g_gcTarget, sizeof(g_gcOriginal), PAGE_EXECUTE_READWRITE, &oldProtect)) {
            memcpy(g_gcTarget, g_gcOriginal, sizeof(g_gcOriginal));
            VirtualProtect(g_gcTarget, sizeof(g_gcOriginal), oldProtect, &tmp);
        }
        g_colorsApplied = false;
    }
    if (g_set.colors && !g_colorsApplied && GetModuleHandleW(L"chrome.dll")) {
        EmitAndInstallColors(g_liveColors.data(), (int)g_liveColors.size());
    }
    g_iconWant.store(g_set.gradientIcon, std::memory_order_relaxed);
    // v3.9.0: the see-through and frame switches apply live too.
    if (GetModuleHandleW(L"chrome.dll")) {
        if (g_set.acrylic) ApplyAcrylicPatch();
        else RestoreAcrylic();
        if (g_set.nativeFrame) ApplyStructuralPatches();
        else {
            RemoveAllHeliumNativeFrameSubclasses();
            RestoreFrame();
        }
        BackdropCtx bctx = { GetCurrentProcessId() };
        EnumWindows(BackdropEnumProc, (LPARAM)&bctx);
        LiveRefresh(true);
    }
    Wh_Log(L"settings changed: acrylic=%d colors=%d frame=%d icon=%d (applied live)",
           (int)g_set.acrylic, (int)g_set.colors, (int)g_set.nativeFrame,
           (int)g_set.gradientIcon);
}

void ModUninit() {
    g_stop = true;
    // Wake every loop and wait for it to leave this DLL before anything it
    // uses is torn down. Bounded, so a stuck call can never hang the browser.
    if (g_stopEvent) SetEvent(g_stopEvent);
    for (int pass = 0; pass < 2; pass++) {
        int n = std::min(g_threadCount.load(), 16);
        if (n > 0) WaitForMultipleObjects((DWORD)n, g_threads, TRUE, 3000);
    }
    RestoreHeliumIcons();
    // Closing Helium also unloads the mod; only a real disable in Windhawk
    // hands the shortcuts back their stock icon.
    if (IsBrowserProcess() && ModDisabledInWindhawk()) UpdateShortcutIcons(false);
    if (g_badgeSmall) DestroyIcon(g_badgeSmall);
    if (g_badgeBig) DestroyIcon(g_badgeBig);
    g_badgeSmall = nullptr;
    g_badgeBig = nullptr;
    RestoreAcrylic();
    if (g_colorsApplied && g_gcTarget) {
        DWORD oldProtect;
        if (VirtualProtect(g_gcTarget, sizeof(g_gcOriginal), PAGE_EXECUTE_READWRITE, &oldProtect)) {
            memcpy(g_gcTarget, g_gcOriginal, sizeof(g_gcOriginal));
            DWORD tmp;
            VirtualProtect(g_gcTarget, sizeof(g_gcOriginal), oldProtect, &tmp);
        }
        g_colorsApplied = false;
    }
    RemoveAllHeliumNativeFrameSubclasses();
    RestoreFrame();
    if (g_fsGuardSite) {
        DWORD oldProtect, tmp;
        if (VirtualProtect(g_fsGuardSite, sizeof(g_fsGuardOrig), PAGE_EXECUTE_READWRITE, &oldProtect)) {
            memcpy(g_fsGuardSite, g_fsGuardOrig, sizeof(g_fsGuardOrig));
            VirtualProtect(g_fsGuardSite, sizeof(g_fsGuardOrig), oldProtect, &tmp);
        }
        g_fsGuardSite = nullptr;
    }
    if (g_ntSite) {
        DWORD oldProtect, tmp;
        if (VirtualProtect(g_ntSite, sizeof(g_ntOrig), PAGE_EXECUTE_READWRITE, &oldProtect)) {
            memcpy(g_ntSite, g_ntOrig, sizeof(g_ntOrig));
            VirtualProtect(g_ntSite, sizeof(g_ntOrig), oldProtect, &tmp);
        }
        g_ntSite = nullptr;
    }
    if (g_pillSite) {
        DWORD oldProtect, tmp;
        if (VirtualProtect(g_pillSite, sizeof(g_pillOrig), PAGE_EXECUTE_READWRITE, &oldProtect)) {
            memcpy(g_pillSite, g_pillOrig, sizeof(g_pillOrig));
            VirtualProtect(g_pillSite, sizeof(g_pillOrig), oldProtect, &tmp);
        }
        g_pillSite = nullptr;
    }
    if (g_omniSite) {
        DWORD oldProtect, tmp;
        if (VirtualProtect(g_omniSite, sizeof(g_omniOrig), PAGE_EXECUTE_READWRITE, &oldProtect)) {
            memcpy(g_omniSite, g_omniOrig, sizeof(g_omniOrig));
            VirtualProtect(g_omniSite, sizeof(g_omniOrig), oldProtect, &tmp);
        }
        g_omniSite = nullptr;
    }
    // The generated code pages stay allocated on purpose. A browser thread
    // can still be inside one when its entry jump is put back, and freeing it
    // under that thread crashes the browser. A few pages is nothing.
    g_gradPage = nullptr;
    g_cavePage = nullptr;
    g_hookMem = nullptr;
    // Back to stock on the windows that are open now, without a restart.
    if (GetModuleHandleW(L"chrome.dll")) {
        EnumWindows(ClearAccentEnumProc, (LPARAM)GetCurrentProcessId());
        LiveRefresh(false);
    }
    for (int i = 0; i < std::min(g_threadCount.load(), 16); i++) {
        if (g_threads[i]) CloseHandle(g_threads[i]);
        g_threads[i] = nullptr;
    }
    if (g_stopEvent) {
        CloseHandle(g_stopEvent);
        g_stopEvent = nullptr;
    }
}

}  // namespace HeliumEngine

// Brave part: Brave Acrylic 4.0 by bardelyne, MIT license.
namespace BraveEngine {

// Settings for this engine live in the "brave" group.
static int Wh_GetIntSetting(PCWSTR name, ...) {
    wchar_t buf[256];
    va_list a;
    va_start(a, name);
    _vsnwprintf_s(buf, 256, _TRUNCATE, name, a);
    va_end(a);
    return ::Wh_GetIntSetting(L"brave.%s", buf);
}

static PCWSTR Wh_GetStringSetting(PCWSTR name, ...) {
    wchar_t buf[256];
    va_list a;
    va_start(a, name);
    _vsnwprintf_s(buf, 256, _TRUNCATE, name, a);
    va_end(a);
    return ::Wh_GetStringSetting(L"brave.%s", buf);
}

namespace BraveBackground {
struct ClassName {
    const char *data;
    size_t length;
};
using Paint = void (*)(void *, void *);
using Clear = void (*)(void *, unsigned int, int);
using GetClass = ClassName *(*)(const void *, ClassName *);
using Transparent = bool (*)(const void *);
using Construct = void *(*)(void *, void *, void *);
// The native nontrivial unique_ptr parameter is passed indirectly on x64.
// Only an empty native unique_ptr is supplied; Brave destroys its old object.
using SetBackground = void (*)(void *, void **);
enum Area : unsigned {
    Background = 1,
    Toolbar = 2,
    Page = 4,
    AddressBar = 128,
    All = Background | Toolbar | Page | AddressBar,
};

struct Context {
    std::atomic<bool> ready{false};
    std::atomic<unsigned> areas{All};
    Paint originalPaint = nullptr;
    Clear clear = nullptr;
    GetClass getClass = nullptr;
    Transparent originalTransparent = nullptr;
    Construct originalConstruct = nullptr;
    SetBackground setBackground = nullptr;

    bool Complete() const {
        return originalPaint && clear && getClass && originalTransparent && originalConstruct &&
               setBackground;
    }
};

inline bool IsBackgroundContainer(ClassName name, unsigned areas) {
    if (!name.data || !name.length || name.length >= 128 || !areas)
        return false;
    struct Role {
        const char *name;
        unsigned areas;
    };
    static constexpr Role roles[] = {
        // A transparent shared root is required for either child area. An
        // unselected child still paints its own original opaque background.
        {"BrowserView", All},
        {"BraveBrowserView", All},
        {"TopContainerView", Toolbar},
        {"ToolbarView", Toolbar},
        {"BraveToolbarView", Toolbar},
        {"BookmarkBarView", Toolbar},
        {"BraveBookmarkBarView", Toolbar},
        {"VerticalTabStripRegionView", Background},
        {"BraveVerticalTabStripRegionView", Background},
        {"VerticalTabStripContainerView", Background},
        {"BraveVerticalTabStripContainerView", Background},
        {"ContentsContainerView", Page},
        {"MainBackgroundRegionView", Page},
        {"BraveContentsContainerView", Page}};
    for (const auto &role : roles) {
        const size_t length = std::strlen(role.name);
        if ((areas & role.areas) && length == name.length &&
            !std::memcmp(name.data, role.name, length))
            return true;
    }
    return false;
}

inline void PaintBackground(Context &context, void *view, void *canvas) {
    if (view && canvas && context.ready.load(std::memory_order_acquire)) {
        ClassName name{};
        context.getClass(view, &name);
        if (IsBackgroundContainer(name, context.areas.load(std::memory_order_relaxed)) &&
            context.ready.load(std::memory_order_acquire)) {
            // The caller's native clip covers only this background. Borders,
            // foreground content, and children paint afterward as usual.
            context.clear(canvas, 0, 0 /* SkBlendMode::kClear */);
            return;
        }
    }
    if (context.originalPaint)
        context.originalPaint(view, canvas);
}

inline bool WindowContentsTransparent(Context &context, const void *host) {
    if (context.ready.load(std::memory_order_acquire) &&
        context.areas.load(std::memory_order_relaxed))
        return true;
    return context.originalTransparent ? context.originalTransparent(host) : false;
}

inline void *ConstructSidebar(Context &context, void *self, void *browser, void *backingView) {
    void *result = context.originalConstruct(self, browser, backingView);
    if (backingView && context.ready.load(std::memory_order_acquire) &&
        (context.areas.load(std::memory_order_relaxed) & Background)) {
        // Brave passes this otherwise anonymous View to the constructor. No
        // object-layout offsets, geometry guesses, or retained View pointers.
        void *empty = nullptr;
        context.setBackground(backingView, &empty);
    }
    return result;
}
} // namespace BraveBackground

static BraveBackground::Context s_background;
static auto &s_transparencyReady = s_background.ready;
static std::atomic<unsigned> s_availableAreas{BraveBackground::All};
static std::atomic<unsigned> s_requestedUi{8 | 16 | 32};
static std::atomic<unsigned> s_popupOpacity{62};
static std::atomic<bool> s_chromeAttempted{false}, s_useOnlineSymbolCache{true};
static std::atomic<bool> s_allowBraveSymbolServerFallback{false};
static SRWLOCK s_initLock = SRWLOCK_INIT;
static bool s_stopping = false, s_activateAfterInit = false, s_isBrowserProcess = false;
using LoadLibraryExW_t = decltype(&LoadLibraryExW);
static LoadLibraryExW_t pOrigLoadLibraryExW = nullptr;

// Native x64 SkColor4f is passed indirectly as a 16-byte aggregate.
struct NativeColor {
    float r, g, b, a;
};
static_assert(sizeof(NativeColor) == 16);
using NativeFocus = bool (*)(const void *);
using NativeEvent = void (*)(void *);
using NativeLayerColor = void (*)(void *, const NativeColor *);
using NativeSetPageBase = void (*)(void *, uint64_t);
using NativeAttachContents = void (*)(void *, void *);
static NativeFocus s_locationFocus = nullptr, s_viewFocus = nullptr;
static NativeEvent s_originalTheme = nullptr, s_originalReady = nullptr;
static NativeLayerColor s_originalLayerColor = nullptr;
static NativeSetPageBase s_setPageBase = nullptr;
static NativeAttachContents s_originalAttachContents = nullptr;
static thread_local unsigned s_pageBackgroundScope = 0;

// Limit both color overrides to native content-view updates on this thread.
struct PageScope {
    unsigned old = s_pageBackgroundScope;
    PageScope() {
        if (s_transparencyReady.load(std::memory_order_acquire) &&
            (s_background.areas.load(std::memory_order_relaxed) & BraveBackground::Page))
            ++s_pageBackgroundScope;
    }
    ~PageScope() {
        s_pageBackgroundScope = old;
    }
};
static bool ClearPageFallback() {
    return s_pageBackgroundScope && s_transparencyReady.load(std::memory_order_acquire) &&
           (s_background.areas.load(std::memory_order_relaxed) & BraveBackground::Page);
}
// Brave retains the outline stroke, rounded clip and layout insets.
namespace RoundedContents {
using BorderPaint = void (*)(void *, void *);
using PathPaint = void (*)(void *, const void *, const void *, int);
static BorderPaint originalBorder = nullptr;
static PathPaint originalPath = nullptr;
static std::atomic<bool> available{false};
static thread_local bool clearBackingFill = false;
static bool Target(void *view) {
    if (!view || !available.load(std::memory_order_relaxed) ||
        !s_transparencyReady.load(std::memory_order_acquire) ||
        !(s_background.areas.load(std::memory_order_relaxed) & BraveBackground::Page))
        return false;
    BraveBackground::ClassName name{};
    s_background.getClass(view, &name);
    constexpr std::string_view role = "BraveContentsContainerView";
    return name.data && name.length == role.size() &&
           !memcmp(name.data, role.data(), role.size());
}
static void BorderHook(void *view, void *canvas) {
    const bool previous = clearBackingFill;
    clearBackingFill = canvas && Target(view);
    originalBorder(view, canvas);
    clearBackingFill = previous;
}
static bool IsBackingFill(const void *flags) {
    if (!flags)
        return false;
    // Chromium x64 CorePaintFlags stores its packed paint options after
    // SkColor4f, stroke_width and miter_limit. Brave's rounded outline painter
    // uses kSrc. Match only its fill style, regardless of path draw order.
    constexpr size_t kPaintOptionsOffset = 24;
    constexpr uint32_t kStyleMask = 0xC0, kBlendModeMask = 0x1F00, kSourceBlend = 0x100;
    uint32_t options = 0;
    memcpy(&options, static_cast<const unsigned char *>(flags) + kPaintOptionsOffset,
           sizeof(options));
    return (options & (kStyleMask | kBlendModeMask)) == kSourceBlend;
}
static void PathHook(void *canvas, const void *path, const void *flags, int cache) {
    if (clearBackingFill && IsBackingFill(flags)) {
        clearBackingFill = false;
        return;
    }
    originalPath(canvas, path, flags, cache);
}
} // namespace RoundedContents
static void PageThemeHook(void *self) {
    PageScope scope;
    s_originalTheme(self);
}
static void PageReadyHook(void *self) {
    PageScope scope;
    s_originalReady(self);
}
static void PageLayerColorHook(void *self, const NativeColor *color) {
    const NativeColor transparent{};
    s_originalLayerColor(self, ClearPageFallback() ? &transparent : color);
}
// The native optional<SkColor> argument occupies RDX: color in the low
// DWORD, has-value in byte 4. Set an explicit transparent base, not nullopt.
// Chromium stores it on WebContents and sends it to current and future renderers.
static void AttachContentsHook(void *self, void *contents) {
    if (contents && s_transparencyReady.load(std::memory_order_acquire) &&
        (s_background.areas.load(std::memory_order_relaxed) & BraveBackground::Page)) {
        s_setPageBase(contents, uint64_t(1) << 32);
    }
    // Use the supplied canonical WebContents pointer before attach notifications.
    // No retained objects, member offsets, reloads or selection polling.
    s_originalAttachContents(self, contents);
}
static bool AddressBarActive() {
    return s_transparencyReady.load(std::memory_order_acquire) &&
           (s_background.areas.load(std::memory_order_relaxed) & BraveBackground::AddressBar);
}

static bool AddressShouldClear(void *view) {
    if (!view || !AddressBarActive())
        return false;
    BraveBackground::ClassName name{};
    s_background.getClass(view, &name);
    if (!name.data || name.length > 127)
        return false;
    auto is = [&](const char *target) {
        return strlen(target) == name.length && !memcmp(name.data, target, name.length);
    };
    const bool location = is("LocationBarView") || is("BraveLocationBarView");
    const bool input = is("OmniboxViewViews") || is("BraveOmniboxViewViews");
    if (!location && !input)
        return false;
    return !(location ? s_locationFocus(view) : s_viewFocus(view));
}

// Brave passes this value by const reference and copies it into its shadow
// cache. Leave the original argument, geometry and native layer lifetime alone.
struct ShadowParameters {
    int offsetX;
    int offsetY;
    int blurRadius;
    uint32_t color;
};
static_assert(sizeof(ShadowParameters) == 16 && offsetof(ShadowParameters, color) == 12);
using ConstructShadow = void *(*)(void *, void *, const void *, const ShadowParameters *);
static ConstructShadow s_originalShadow = nullptr;

static void *ConstructShadowHook(void *self, void *view, const void *corners,
                                 const ShadowParameters *params) {
    if (view && params && AddressBarActive()) {
        BraveBackground::ClassName role{};
        s_background.getClass(view, &role);
        if (role.data && std::string_view(role.data, role.length) == "BraveLocationBarView") {
            auto transparent = *params;
            transparent.color = 0;
            return s_originalShadow(self, view, corners, &transparent);
        }
    }
    return s_originalShadow(self, view, corners, params);
}

static bool HasCompleteTransparencyPath() {
    const unsigned areas = s_availableAreas.load(std::memory_order_acquire);
    return areas && s_background.originalPaint && s_background.clear && s_background.getClass &&
           s_background.originalTransparent &&
           (!(areas & BraveBackground::Background) ||
            (s_background.originalConstruct && s_background.setBackground)) &&
           (!(areas & BraveBackground::AddressBar) || (s_locationFocus && s_viewFocus)) &&
           (!(areas & BraveBackground::Page) ||
            (s_originalTheme && s_originalReady && s_originalLayerColor && s_setPageBase &&
             s_originalAttachContents));
}
namespace NativeUi {
static bool SuppressPopupBackground(void *view);
}
static void ViewOnPaintBackground_Hook(void *view, void *canvas) {
    if (canvas && NativeUi::SuppressPopupBackground(view)) {
        BraveBackground::ClassName role{};
        s_background.getClass(view, &role);
        if (role.data && std::string_view(role.data, role.length) != "FooterView" &&
            std::string_view(role.data, role.length) != "FadeLabel")
            s_background.clear(canvas, 0, 0);
        return;
    }
    if (canvas && AddressShouldClear(view)) {
        s_background.clear(canvas, 0, 0);
        return;
    }
    BraveBackground::PaintBackground(s_background, view, canvas);
}
static bool WindowContentsTransparent_Hook(const void *host) {
    return BraveBackground::WindowContentsTransparent(s_background, host);
}
static void *SidebarConstructor_Hook(void *self, void *browser, void *host) {
    return BraveBackground::ConstructSidebar(s_background, self, browser, host);
}

// Windows still draws its caption buttons underneath Chromium's transparent
// custom frame. Hide only WS_SYSMENU, retaining the resize/caption/min/max bits.
// Chromium reads its original logical style, including when saving fullscreen
// state; DWM sees the real style without the native buttons.
static constexpr wchar_t kNativeCaptionProperty[] = L"Windhawk.BraveAcrylic.NativeCaption";
static std::atomic<bool> s_hideNativeCaptionButtons{false};
static std::atomic<bool> s_captionFixActive{false};
static std::atomic<bool> s_captionStopping{false};
// Stay conservative after the option has been used: a concurrent style write
// may still need its ownership property while settings or shutdown restore it.
static std::atomic<bool> s_captionPropertyUsed{false};
static bool s_captionHooksInstalled = false;
static decltype(&CreateWindowExW) pOrigCreateWindowExW = nullptr;
static decltype(&GetWindowLongPtrW) pOrigGetWindowLongPtrW = nullptr;
static decltype(&SetWindowLongPtrW) pOrigSetWindowLongPtrW = nullptr;
static decltype(&GetWindowLongW) pOrigGetWindowLongW = nullptr;
static decltype(&SetWindowLongW) pOrigSetWindowLongW = nullptr;
static thread_local HWND s_captionStyleWrite = nullptr;

static bool IsBrowserCaptionFrame(HWND window, LONG_PTR style) {
    constexpr LONG_PTR required = WS_CAPTION | WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX;
    if (!window || (style & required) != required || (style & WS_CHILD))
        return false;
    DWORD process = 0;
    GetWindowThreadProcessId(window, &process);
    if (process != GetCurrentProcessId() || GetAncestor(window, GA_ROOT) != window ||
        GetWindow(window, GW_OWNER))
        return false;
    const auto exStyle = pOrigGetWindowLongPtrW(window, GWL_EXSTYLE);
    if (exStyle & (WS_EX_TOOLWINDOW | WS_EX_NOACTIVATE | WS_EX_DLGMODALFRAME))
        return false;
    wchar_t name[32]{};
    return GetClassNameW(window, name, ARRAYSIZE(name)) && !wcscmp(name, L"Chrome_WidgetWin_1");
}

static void RefreshNativeCaption(HWND window) {
    SetWindowPos(window, nullptr, 0, 0, 0, 0,
                 SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE | SWP_FRAMECHANGED);
}

static void RestoreNativeCaption(HWND window) {
    if (!GetPropW(window, kNativeCaptionProperty))
        return;
    RemovePropW(window, kNativeCaptionProperty);
    // Restore before hooks are removed; the ownership property is already gone.
    const auto style = GetWindowLongPtrW(window, GWL_STYLE);
    SetWindowLongPtrW(window, GWL_STYLE, style | WS_SYSMENU);
    RefreshNativeCaption(window);
}

template <typename Value>
static Value ReadCaptionStyle(HWND window, int index, Value(WINAPI *original)(HWND, int)) {
    if (index != GWL_STYLE ||
        (!s_captionFixActive.load(std::memory_order_acquire) &&
         !s_captionPropertyUsed.load(std::memory_order_relaxed)))
        return original(window, index);
    auto value = original(window, index);
    const DWORD error = GetLastError();
    if (index == GWL_STYLE && GetPropW(window, kNativeCaptionProperty))
        value |= WS_SYSMENU;
    SetLastError(error);
    return value;
}

static LONG_PTR WINAPI GetWindowLongPtrW_Hook(HWND window, int index) {
    return ReadCaptionStyle(window, index, pOrigGetWindowLongPtrW);
}

static LONG WINAPI GetWindowLongW_Hook(HWND window, int index) {
    return ReadCaptionStyle(window, index, pOrigGetWindowLongW);
}

template <typename Value>
static Value WriteCaptionStyle(HWND window, int index, Value value,
                               Value(WINAPI *original)(HWND, int, Value)) {
    // Windows may forward one API to the other. Translate the style only once.
    if (index != GWL_STYLE || s_captionStyleWrite == window ||
        (!s_captionFixActive.load(std::memory_order_acquire) &&
         !s_captionPropertyUsed.load(std::memory_order_relaxed)))
        return original(window, index, value);
    const bool owned = GetPropW(window, kNativeCaptionProperty) != nullptr;
    const bool hide = s_captionFixActive.load(std::memory_order_acquire) && (value & WS_SYSMENU) &&
                      (owned || IsBrowserCaptionFrame(window, value));
    bool marked = owned;
    if (hide && !owned) {
        s_captionPropertyUsed.store(true, std::memory_order_relaxed);
        marked = SetPropW(window, kNativeCaptionProperty, reinterpret_cast<HANDLE>(1)) != FALSE;
    } else if (!hide && owned) {
        RemovePropW(window, kNativeCaptionProperty);
        marked = false;
    }
    const HWND previousWrite = s_captionStyleWrite;
    s_captionStyleWrite = window;
    // Zero is also a valid previous style. Clear stale errors before testing
    // whether the native setter failed, as required by SetWindowLong.
    SetLastError(ERROR_SUCCESS);
    const auto previous =
        original(window, index, hide && marked ? value & ~static_cast<Value>(WS_SYSMENU) : value);
    const DWORD error = GetLastError();
    s_captionStyleWrite = previousWrite;
    if (!previous && error) {
        if (owned)
            SetPropW(window, kNativeCaptionProperty, reinterpret_cast<HANDLE>(1));
        else
            RemovePropW(window, kNativeCaptionProperty);
    } else if (hide && marked && !s_captionFixActive.load(std::memory_order_acquire)) {
        // A setting can change while SetWindowLong dispatches style messages.
        RestoreNativeCaption(window);
    }
    SetLastError(error);
    return previous && owned ? previous | WS_SYSMENU : previous;
}

static LONG_PTR WINAPI SetWindowLongPtrW_Hook(HWND window, int index, LONG_PTR value) {
    return WriteCaptionStyle(window, index, value, pOrigSetWindowLongPtrW);
}

static LONG WINAPI SetWindowLongW_Hook(HWND window, int index, LONG value) {
    return WriteCaptionStyle(window, index, value, pOrigSetWindowLongW);
}

static void ApplyNativeCaption(HWND window) {
    if (!s_captionFixActive.load(std::memory_order_acquire) ||
        GetPropW(window, kNativeCaptionProperty))
        return;
    const auto style = pOrigGetWindowLongPtrW(window, GWL_STYLE);
    if (!(style & WS_SYSMENU) || !IsBrowserCaptionFrame(window, style))
        return;
    SetWindowLongPtrW_Hook(window, GWL_STYLE, style);
    if (GetPropW(window, kNativeCaptionProperty))
        RefreshNativeCaption(window);
}

static HWND WINAPI CreateWindowExW_Hook(DWORD exStyle, LPCWSTR className, LPCWSTR name, DWORD style,
                                        int x, int y, int width, int height, HWND parent,
                                        HMENU menu, HINSTANCE instance, LPVOID param) {
    const auto window = pOrigCreateWindowExW(exStyle, className, name, style, x, y, width, height,
                                             parent, menu, instance, param);
    const DWORD error = GetLastError();
    if (window)
        ApplyNativeCaption(window);
    SetLastError(error);
    return window;
}

static BOOL CALLBACK SyncNativeCaptionWindow(HWND window, LPARAM) {
    DWORD process = 0;
    GetWindowThreadProcessId(window, &process);
    if (process == GetCurrentProcessId()) {
        if (s_captionFixActive.load(std::memory_order_acquire))
            ApplyNativeCaption(window);
        else
            RestoreNativeCaption(window);
    }
    return TRUE;
}

static void SyncNativeCaptions() {
    const bool active = s_captionHooksInstalled &&
                        !s_captionStopping.load(std::memory_order_acquire) &&
                        s_transparencyReady.load(std::memory_order_acquire) &&
                        s_background.areas.load(std::memory_order_relaxed) &&
                        s_hideNativeCaptionButtons.load(std::memory_order_relaxed);
    s_captionFixActive.store(active, std::memory_order_release);
    if (s_captionHooksInstalled)
        EnumWindows(SyncNativeCaptionWindow, 0);
}

static void InstallNativeCaptionHooks() {
    s_captionHooksInstalled =
        WindhawkUtils::SetFunctionHook(CreateWindowExW, CreateWindowExW_Hook,
                                       &pOrigCreateWindowExW) &&
        WindhawkUtils::SetFunctionHook(GetWindowLongPtrW, GetWindowLongPtrW_Hook,
                                       &pOrigGetWindowLongPtrW) &&
        WindhawkUtils::SetFunctionHook(SetWindowLongPtrW, SetWindowLongPtrW_Hook,
                                       &pOrigSetWindowLongPtrW) &&
        WindhawkUtils::SetFunctionHook(GetWindowLongW, GetWindowLongW_Hook, &pOrigGetWindowLongW) &&
        WindhawkUtils::SetFunctionHook(SetWindowLongW, SetWindowLongW_Hook, &pOrigSetWindowLongW);
    if (!s_captionHooksInstalled)
        Wh_Log(L"Native caption fix unavailable; acrylic is unchanged");
}

static void LoadModSettings() {
    unsigned areas = 0;
    if (Wh_GetIntSetting(L"transparentBackground"))
        areas |= BraveBackground::Background;
    if (Wh_GetIntSetting(L"transparentToolbar"))
        areas |= BraveBackground::Toolbar;
    if (Wh_GetIntSetting(L"transparentAddressBar"))
        areas |= BraveBackground::AddressBar;
    if (Wh_GetIntSetting(L"transparentPageBackground"))
        areas |= BraveBackground::Page;
    s_background.areas.store(areas & s_availableAreas.load(), std::memory_order_relaxed);
    unsigned ui = 0;
    if (Wh_GetIntSetting(L"blurMenus"))
        ui |= 8;
    if (Wh_GetIntSetting(L"blurPopups"))
        ui |= 16;
    if (Wh_GetIntSetting(L"blurSuggestions"))
        ui |= 32;
    s_requestedUi = ui;
    s_popupOpacity.store(static_cast<unsigned>(std::clamp(Wh_GetIntSetting(L"popupOpacity"), 0, 100)),
                         std::memory_order_relaxed);
    s_hideNativeCaptionButtons.store(Wh_GetIntSetting(L"hideNativeCaptionButtons") != 0,
                                     std::memory_order_relaxed);
    s_useOnlineSymbolCache.store(Wh_GetIntSetting(L"useOnlineSymbolCache") != 0,
                                 std::memory_order_release);
    s_allowBraveSymbolServerFallback.store(
        Wh_GetIntSetting(L"allowBraveSymbolServerFallback") != 0, std::memory_order_release);
}

struct ReadOnlyImage {
    const unsigned char *base;
    size_t size;
    const IMAGE_SECTION_HEADER *sections;
    unsigned count;

    bool Contains(size_t rva, size_t length) const {
        if (rva > size || length > size - rva)
            return false;
        for (unsigned i = 0; i < count; ++i) {
            const auto &s = sections[i];
            const DWORD flags = s.Characteristics;
            if (!(flags & IMAGE_SCN_MEM_READ) || !(flags & IMAGE_SCN_CNT_INITIALIZED_DATA) ||
                (flags & (IMAGE_SCN_MEM_WRITE | IMAGE_SCN_MEM_EXECUTE)) ||
                s.VirtualAddress > size || s.Misc.VirtualSize > size - s.VirtualAddress)
                continue;
            if (rva >= s.VirtualAddress && rva - s.VirtualAddress <= s.Misc.VirtualSize &&
                length <= s.Misc.VirtualSize - (rva - s.VirtualAddress))
                return true;
        }
        return false;
    }
};

static bool GetReadOnlyImage(HMODULE mod, ReadOnlyImage *out) {
    MEMORY_BASIC_INFORMATION memory{};
    if (!mod || !VirtualQuery(mod, &memory, sizeof(memory)) || memory.State != MEM_COMMIT ||
        (memory.Protect & (PAGE_GUARD | PAGE_NOACCESS)))
        return false;
    const auto *base = reinterpret_cast<const unsigned char *>(mod);
    const size_t headerBytes =
        memory.RegionSize - (base - static_cast<const unsigned char *>(memory.BaseAddress));
    if (headerBytes < sizeof(IMAGE_DOS_HEADER))
        return false;
    const auto *dos = reinterpret_cast<const IMAGE_DOS_HEADER *>(base);
    if (dos->e_magic != IMAGE_DOS_SIGNATURE || dos->e_lfanew < 0 ||
        static_cast<size_t>(dos->e_lfanew) > headerBytes ||
        sizeof(IMAGE_NT_HEADERS64) > headerBytes - dos->e_lfanew)
        return false;
    const auto *nt = reinterpret_cast<const IMAGE_NT_HEADERS64 *>(base + dos->e_lfanew);
    if (nt->Signature != IMAGE_NT_SIGNATURE ||
        nt->OptionalHeader.Magic != IMAGE_NT_OPTIONAL_HDR64_MAGIC ||
        nt->FileHeader.SizeOfOptionalHeader < sizeof(IMAGE_OPTIONAL_HEADER64) ||
        !nt->FileHeader.NumberOfSections || nt->FileHeader.NumberOfSections > 96)
        return false;
    const auto *sections = IMAGE_FIRST_SECTION(nt);
    const size_t sectionOffset = reinterpret_cast<const unsigned char *>(sections) - base;
    const size_t sectionBytes = nt->FileHeader.NumberOfSections * sizeof(*sections);
    const size_t imageSize = nt->OptionalHeader.SizeOfImage;
    if (sectionOffset > headerBytes || sectionBytes > headerBytes - sectionOffset ||
        sectionOffset > imageSize || sectionBytes > imageSize - sectionOffset)
        return false;
    *out = {base, imageSize, sections, nt->FileHeader.NumberOfSections};
    return true;
}

static bool GetFunctionTable(HMODULE mod, const RUNTIME_FUNCTION **table, size_t *count) {
    const auto *dos = reinterpret_cast<const IMAGE_DOS_HEADER *>(mod);
    const auto *nt = reinterpret_cast<const IMAGE_NT_HEADERS64 *>(
        reinterpret_cast<const unsigned char *>(mod) + dos->e_lfanew);
    const auto &dir = nt->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXCEPTION];
    const size_t imageSize = nt->OptionalHeader.SizeOfImage;
    if (!dir.VirtualAddress || dir.VirtualAddress > imageSize ||
        dir.Size > imageSize - dir.VirtualAddress || !dir.Size ||
        dir.Size % sizeof(RUNTIME_FUNCTION))
        return false;
    *table = reinterpret_cast<const RUNTIME_FUNCTION *>(
        reinterpret_cast<const unsigned char *>(mod) + dir.VirtualAddress);
    *count = dir.Size / sizeof(RUNTIME_FUNCTION);
    return true;
}

static bool FunctionContains(HMODULE mod, size_t rva, size_t length) {
    const RUNTIME_FUNCTION *table;
    size_t count;
    if (!GetFunctionTable(mod, &table, &count))
        return false;
    size_t lo = 0, hi = count;
    while (lo < hi) {
        const size_t mid = lo + (hi - lo) / 2;
        if (table[mid].BeginAddress < rva)
            lo = mid + 1;
        else
            hi = mid;
    }
    return lo < count && table[lo].BeginAddress == rva && table[lo].EndAddress > rva &&
           length <= table[lo].EndAddress - rva;
}

static bool FocusLeafLayout(const unsigned char *code) {
    const unsigned char lateFalse[] = {
        0x48, 0x83, 0xB9, 0,    0,    0,    0,    0, 0x74, 0x13, 0x48, 0x8B, 0x81, 0,    0,   0, 0,
        0x48, 0x8B, 0x40, 0x28, 0x83, 0x78, 0x18, 0, 0x0F, 0x95, 0xC0, 0xC3, 0x31, 0xC0, 0xC3};
    const unsigned char earlyFalse[] = {0x48, 0x83, 0xB9, 0,    0,    0,    0,    0,
                                        0x75, 3,    0x31, 0xC0, 0xC3, 0x48, 0x8B, 0x81,
                                        0,    0,    0,    0,    0x48, 0x8B, 0x40, 0x28,
                                        0x83, 0x78, 0x18, 0,    0x0F, 0x95, 0xC0, 0xC3};
    const auto matches = [&](const unsigned char *layout, unsigned member) {
        for (unsigned i = 0; i < 32; ++i) {
            const bool offset = (i >= 3 && i < 7) || (i >= member && i < member + 4);
            if (!offset && code[i] != layout[i])
                return false;
        }
        return true;
    };
    return matches(lateFalse, 13) || matches(earlyFalse, 16);
}
static bool LeafOutsideUnwind(HMODULE module, size_t rva, size_t length) {
    const RUNTIME_FUNCTION *table;
    size_t count;
    if (!GetFunctionTable(module, &table, &count))
        return false;
    // Inspect all preceding ranges, including optimized overlapping entries.
    // A nearest-predecessor lookup can miss an enclosing earlier function.
    for (size_t i = 0; i < count; ++i) {
        if (table[i].BeginAddress >= rva + length)
            break;
        if (table[i].BeginAddress >= rva || table[i].EndAddress > rva)
            return false;
    }
    return true;
}
// Windhawk retains standard named-symbol resolution and its own local cache.
// The author-hosted cache is trusted; local checks validate address structure.
// Windhawk handles the optional official PDB fallback when the cache misses.
static constexpr wchar_t kOnlineSymbolCache[] =
    L"https://raw.githubusercontent.com/bardelyne/brave-acrylic/symbol-cache/brave-acrylic-features-v9";
static constexpr wchar_t kBraveSymbolServer[] = L"https://brave-symbols.s3.brave.com";

// <feature-kernel>
static constexpr unsigned kFeatureSlots = 37;
static constexpr unsigned kVertical = 1, kToolbar = 2, kWebpage = 4, kMenus = 8, kPopups = 16,
                          kSuggestions = 32, kRoundedWebpage = 64,
                          kAddressBar = BraveBackground::AddressBar;
static constexpr unsigned kPopupFade = 256, kAddressShadow = 512;
static unsigned CompleteFeatures(const size_t *entries) {
    const auto all = [&](std::initializer_list<unsigned> slots) {
        for (unsigned i : slots)
            if (!entries[i])
                return false;
        return true;
    };
    return (all({0, 1, 2, 3, 4, 5}) ? kVertical : 0) | (all({0, 1, 2, 3}) ? kToolbar : 0) |
           (all({0, 1, 2, 3, 8, 9, 10, 11, 12}) ? kWebpage : 0) |
           (all({13, 14, 15, 17}) ? kMenus : 0) |
           (all({0, 1, 2, 13, 14, 16, 17, 25, 26, 27}) ? kPopups : 0) |
           (all({5, 13, 14, 18, 19, 20, 21, 22, 23, 24, 28, 29}) ? kSuggestions : 0) |
           (all({0, 1, 2, 3, 8, 9, 10, 11, 12, 30, 31}) ? kRoundedWebpage : 0) |
           (all({0, 1, 2, 3, 6, 7}) ? kAddressBar : 0);
}
static unsigned CompleteOptionalFeatures(const size_t *entries, unsigned features) {
    return ((features & kPopups) && entries[32] && entries[33] && entries[34] && entries[35]
                ? kPopupFade
                : 0) |
           ((features & kAddressBar) && entries[36] ? kAddressShadow : 0);
}
static bool MatchNativeLayout(const unsigned char *code, const unsigned char *pattern,
                              unsigned length, std::initializer_list<unsigned> displacements) {
    unsigned start = 0;
    for (unsigned offset : displacements) {
        if (memcmp(code + start, pattern + start, offset - start))
            return false;
        start = offset + 4;
    }
    return !memcmp(code + start, pattern + start, length - start);
}

static bool FeatureHelperLeaf(const unsigned char *code, unsigned slot, unsigned *length) {
    const auto match = [&](const auto &pattern, std::initializer_list<unsigned> displacements) {
        if (!MatchNativeLayout(code, pattern, sizeof(pattern), displacements))
            return false;
        *length = sizeof(pattern);
        return true;
    };
    constexpr unsigned char bounds[] = {
        0x48, 0x89, 0xD0, 0x48, 0xC7, 0x02, 0x00, 0x00, 0x00, 0x00, 0x48, 0x8B,
        0x89, 0x00, 0x00, 0x00, 0x00, 0x48, 0x89, 0x4A, 0x08, 0xC3,
    };
    constexpr unsigned char setter[] = {
        0x41, 0x89, 0xD0, 0x48, 0x81, 0xC1, 0x00, 0x00, 0x00, 0x00, 0x48, 0x8D,
        0x15, 0x00, 0x00, 0x00, 0x00, 0xE9, 0x00, 0x00, 0x00, 0x00,
    };
    // Both native HWND lookup layouts retain their exact control flow.
    constexpr unsigned char lookup0[] = {
        0x48, 0x85, 0xC9, 0x74, 0x19, 0x48, 0x89, 0xC8, 0x48, 0x83, 0xB8, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x75, 0x1B, 0x48, 0x8B, 0x80, 0x00, 0x00, 0x00,
        0x00, 0x48, 0x85, 0xC0, 0x75, 0xEA, 0x31, 0xC0, 0xC3, 0x48, 0x8B, 0x89,
        0x00, 0x00, 0x00, 0x00, 0x48, 0x85, 0xC9, 0x74, 0x0C, 0x48, 0x8B, 0x91,
        0x00, 0x00, 0x00, 0x00, 0x48, 0x85, 0xD2, 0x74, 0xE8, 0x48, 0x8B, 0x02,
        0x48, 0x8B, 0x40, 0x58, 0x48, 0x89, 0xD1, 0x48, 0xFF, 0x25, 0x00, 0x00,
        0x00, 0x00,
    };
    constexpr unsigned char lookup1[] = {
        0x48, 0x85, 0xC9, 0x74, 0x44, 0x48, 0x89, 0xC8, 0x48, 0x83, 0xB8, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x75, 0x1A, 0x48, 0x8B, 0x80, 0x00, 0x00, 0x00,
        0x00, 0x48, 0x85, 0xC0, 0x75, 0xEA, 0xEB, 0x29, 0x48, 0x8B, 0x89, 0x00,
        0x00, 0x00, 0x00, 0x48, 0x85, 0xC9, 0x74, 0x0C, 0x48, 0x8B, 0x91, 0x00,
        0x00, 0x00, 0x00, 0x48, 0x85, 0xD2, 0x74, 0xE8, 0x48, 0x8B, 0x02, 0x48,
        0x8B, 0x40, 0x58, 0x48, 0x89, 0xD1, 0x48, 0xFF, 0x25, 0x00, 0x00, 0x00,
        0x00, 0x31, 0xC0, 0xC3,
    };
    if (slot == 22)
        return match(bounds, {13});
    if (slot == 34)
        return match(setter, {6, 13, 18});
    if (slot == 33)
        return match(lookup0, {11, 21, 36, 48, 70}) || match(lookup1, {11, 21, 35, 47, 69});
    return false;
}
static bool ValidateFeatureAddresses(HMODULE module, void *const *addresses, size_t *result) {
    ReadOnlyImage image{};
    if (!GetReadOnlyImage(module, &image))
        return false;
    const IMAGE_SECTION_HEADER *text = nullptr;
    for (unsigned i = 0; i < image.count; ++i)
        if (!memcmp(image.sections[i].Name, ".text\0\0\0", 8) &&
            (image.sections[i].Characteristics & IMAGE_SCN_MEM_EXECUTE)) {
            if (text)
                return false;
            text = &image.sections[i];
        }
    if (!text || text->VirtualAddress > image.size ||
        text->Misc.VirtualSize > image.size - text->VirtualAddress)
        return false;
    const auto inText = [&](size_t start, size_t length) {
        return start >= text->VirtualAddress &&
               start - text->VirtualAddress <= text->Misc.VirtualSize &&
               length <= text->Misc.VirtualSize - (start - text->VirtualAddress);
    };
    struct Span {
        size_t start, length;
        unsigned slot;
    };
    std::vector<Span> spans;
    std::array<size_t, kFeatureSlots> normalized{};
    const auto base = reinterpret_cast<uintptr_t>(module);
    const auto validate = [&](unsigned i, size_t entry) -> size_t {
        if (i == 24) {
            bool immutable = false;
            for (unsigned n = 0; n < image.count; ++n) {
                const auto &section = image.sections[n];
                if (!memcmp(section.Name, ".rdata\0\0", 8) &&
                    !(section.Characteristics & (IMAGE_SCN_MEM_WRITE | IMAGE_SCN_MEM_EXECUTE)) &&
                    entry >= section.VirtualAddress &&
                    entry - section.VirtualAddress <= section.Misc.VirtualSize &&
                    16 <= section.Misc.VirtualSize - (entry - section.VirtualAddress))
                    immutable = true;
            }
            if (!immutable || entry % alignof(uintptr_t) || !image.Contains(entry, 16))
                return 0;
            for (unsigned p = 0; p < 16; p += 8) {
                uintptr_t method = 0;
                memcpy(&method, image.base + entry + p, 8);
                if (method < base || !inText(method - base, 1))
                    return 0;
            }
            spans.push_back({entry, 16, i});
            return entry;
        }
        if (!inText(entry, 32))
            return 0;
        size_t target = entry;
        bool thunk = false;
        if (!FunctionContains(module, entry, 1) && image.base[entry] == 0xE9) {
            int delta = 0;
            memcpy(&delta, image.base + entry + 1, 4);
            const int64_t destination = int64_t(entry) + 5 + delta;
            if (destination < 0 || uint64_t(destination) >= image.size ||
                !LeafOutsideUnwind(module, entry, 5))
                return 0;
            target = static_cast<size_t>(destination);
            thunk = true;
        }
        if (!inText(target, 32))
            return 0;
        unsigned length = 32;
        if (!FunctionContains(module, target, 32)) {
            if (i == 3) {
                const unsigned char first[] = {0x48, 0x83, 0xB9},
                                    last[] = {0, 0x74, 3, 0x31, 0xC0, 0xC3};
                if (memcmp(image.base + target, first, 3) ||
                    memcmp(image.base + target + 7, last, 6))
                    return 0;
                length = 13;
            } else if (i == 6 && FocusLeafLayout(image.base + target)) {
            } else if (!inText(target, i == 33 ? 80 : 32) ||
                       !FeatureHelperLeaf(image.base + target, i, &length))
                return 0;
            if (!LeafOutsideUnwind(module, target, length))
                return 0;
            if (i == 34) {
                int delta = 0;
                memcpy(&delta, image.base + target + 18, sizeof(delta));
                const int64_t destination = int64_t(target) + 22 + delta;
                if (destination < 0 || !inText(destination, 1) ||
                    !FunctionContains(module, destination, 1))
                    return 0;
            }
        }
        if (thunk)
            spans.push_back({entry, 5, i});
        spans.push_back({target, length, i});
        return target;
    };
    for (unsigned i = 0; i < kFeatureSlots; ++i) {
        const auto pointer = reinterpret_cast<uintptr_t>(addresses[i]);
        if (pointer >= base && pointer - base < image.size)
            normalized[i] = validate(i, pointer - base);
    }
    // Reject both roles if they resolve to overlapping code or data. Other
    // independently validated roles can still provide their features.
    for (size_t i = 0; i < spans.size(); ++i) {
        const auto &a = spans[i];
        for (size_t j = i + 1; j < spans.size(); ++j) {
            const auto &b = spans[j];
            if (a.start < b.start + b.length && b.start < a.start + a.length)
                normalized[a.slot] = normalized[b.slot] = 0;
        }
    }
    std::copy(normalized.begin(), normalized.end(), result);
    return true;
}
struct FeatureSymbol {
    std::wstring_view undecorated;
    std::wstring_view decorated;
    std::wstring_view alternate{};
};
static constexpr FeatureSymbol kFeatureSymbols[] = {
    {L"protected: virtual void __cdecl views::View::OnPaintBackground(class gfx::Canvas *)",
     LR"(?OnPaintBackground@View@views@@MEAAXPEAVCanvas@gfx@@@Z)"},
    {L"public: void __cdecl gfx::Canvas::DrawColor(unsigned int,enum SkBlendMode)",
     LR"(?DrawColor@Canvas@gfx@@QEAAXIW4SkBlendMode@@@Z)"},
    {L"public: class std::__Cr::basic_string_view<char,struct std::__Cr::char_traits<char> > __cdecl views::View::GetClassNameW(void)const",
     LR"(?GetClassNameW@View@views@@QEBA?AV?$basic_string_view@DU?$char_traits@D@__Cr@std@@@__Cr@std@@XZ)"},
    {L"private: virtual bool __cdecl BrowserDesktopWindowTreeHostWin_ChromiumImpl::ShouldWindowContentsBeTransparent(void)const",
     LR"(?ShouldWindowContentsBeTransparent@BrowserDesktopWindowTreeHostWin_ChromiumImpl@@EEBA_NXZ)"},
    {L"public: __cdecl BraveVerticalTabStripContainerView::BraveVerticalTabStripContainerView(class BrowserView *,class views::View *)",
     LR"(??0BraveVerticalTabStripContainerView@@QEAA@PEAVBrowserView@@PEAVView@views@@@Z)"},
    {L"public: void __cdecl views::View::SetBackground(class std::__Cr::unique_ptr<class views::Background,struct std::__Cr::default_delete<class views::Background> >)",
     LR"(?SetBackground@View@views@@QEAAXV?$unique_ptr@VBackground@views@@U?$default_delete@VBackground@views@@@__Cr@std@@@__Cr@std@@@Z)"},
    {L"public: virtual bool __cdecl LocationBarView::HasFocus(void)const",
     LR"(?HasFocus@LocationBarView@@UEBA_NXZ)"},
    {L"public: virtual bool __cdecl views::View::HasFocus(void)const",
     LR"(?HasFocus@View@views@@UEBA_NXZ)"},
    {L"public: virtual void __cdecl ContentsWebView::OnThemeChanged(void)",
     LR"(?OnThemeChanged@ContentsWebView@@UEAAXXZ)"},
    {L"public: virtual void __cdecl ContentsWebView::RenderViewReady(void)",
     LR"(?RenderViewReady@ContentsWebView@@UEAAXXZ)"},
    {L"public: virtual void __cdecl ui::LayerAnimator::SetColor(struct SkRGBA4f<3>)",
     LR"(?SetColor@LayerAnimator@ui@@UEAAXU?$SkRGBA4f@$02@@@Z)"},
    {L"public: virtual void __cdecl content::WebContentsImpl::SetPageBaseBackgroundColor(class std::__Cr::optional<unsigned int>)",
     LR"(?SetPageBaseBackgroundColor@WebContentsImpl@content@@UEAAXV?$optional@I@__Cr@std@@@Z)"},
    {L"public: virtual void __cdecl ContentsWebView::SetWebContents(class content::WebContents *)",
     LR"(?SetWebContents@ContentsWebView@@UEAAXPEAVWebContents@content@@@Z)"},
    {L"struct HWND__ * __cdecl views::HWNDForView(class views::View const *)",
     LR"(?HWNDForView@views@@YAPEAUHWND__@@PEBVView@1@@Z)"},
    {L"public: unsigned int __cdecl ui::ColorProvider::GetColor(int)const",
     LR"(?GetColor@ColorProvider@ui@@QEBAIH@Z)"},
    {L"public: virtual void __cdecl views::MenuScrollViewContainer::OnPaintBackground(class gfx::Canvas *)",
     LR"(?OnPaintBackground@MenuScrollViewContainer@views@@UEAAXPEAVCanvas@gfx@@@Z)"},
    {L"public: virtual void __cdecl views::BubbleBackground::Paint(class gfx::Canvas *,class views::View *)const",
     LR"(?Paint@BubbleBackground@views@@UEBAXPEAVCanvas@gfx@@PEAVView@2@@Z)"},
    {L"public: virtual void __cdecl cc::RecordPaintCanvas::drawRRect(class SkRRect const &,class cc::PaintFlags const &)",
     LR"(?drawRRect@RecordPaintCanvas@cc@@UEAAXAEBVSkRRect@@AEBVPaintFlags@2@@Z)"},
    {L"public: __cdecl RoundedOmniboxResultsFrame::RoundedOmniboxResultsFrame(class views::View *,class LocationBar *,bool)",
     LR"(??0RoundedOmniboxResultsFrame@@QEAA@PEAVView@views@@PEAVLocationBar@@_N@Z)"},
    {L"public: virtual __cdecl RoundedOmniboxResultsFrame::~RoundedOmniboxResultsFrame(void)",
     LR"(??1RoundedOmniboxResultsFrame@@UEAA@XZ)"},
    {L"private: virtual void __cdecl ui::Layer::SetRoundedCornersFromAnimation(class gfx::RoundedCornersF const &,enum ui::PropertyChangeReason)",
     LR"(?SetRoundedCornersFromAnimation@Layer@ui@@EEAAXAEBVRoundedCornersF@gfx@@W4PropertyChangeReason@2@@Z)"},
    {L"public: virtual void __cdecl views::SolidBackground::Paint(class gfx::Canvas *,class views::View *)const",
     LR"(?Paint@SolidBackground@views@@UEBAXPEAVCanvas@gfx@@PEAVView@2@@Z)"},
    {L"public: class gfx::Rect __cdecl views::View::GetLocalBounds(void)const",
     LR"(?GetLocalBounds@View@views@@QEBA?AVRect@gfx@@XZ)"},
    {L"public: static int __cdecl RoundedOmniboxResultsFrame::GetNonResultSectionHeight(bool)",
     LR"(?GetNonResultSectionHeight@RoundedOmniboxResultsFrame@@SAH_N@Z)"},
    {L"const views::SolidBackground::`vftable'",
     LR"(??_7SolidBackground@views@@6B@)"},
    {L"public: virtual void __cdecl views::BubbleFrameView::OnThemeChanged(void)",
     LR"(?OnThemeChanged@BubbleFrameView@views@@UEAAXXZ)"},
    {L"public: void __cdecl ui::Layer::SetFillsBoundsOpaquely(bool)",
     LR"(?SetFillsBoundsOpaquely@Layer@ui@@QEAAX_N@Z)",
     LR"(?SetFillsBoundsOpaquely@Layer@ui@@UEAAX_N@Z)"},
    {L"public: virtual void __cdecl FadeLabel::OnPaintBackground(class gfx::Canvas *)",
     LR"(?OnPaintBackground@FadeLabel@@UEAAXPEAVCanvas@gfx@@@Z)"},
    {L"public: class gfx::Rect __cdecl views::View::GetBoundsInScreen(void)const",
     LR"(?GetBoundsInScreen@View@views@@QEBA?AVRect@gfx@@XZ)"},
    {L"public: static void __cdecl RoundedOmniboxResultsFrame::OnBeforeWidgetInit(struct views::Widget::InitParams *,class views::Widget *)",
     LR"(?OnBeforeWidgetInit@RoundedOmniboxResultsFrame@@SAXPEAUInitParams@Widget@views@@PEAV34@@Z)"},
    {L"protected: virtual void __cdecl views::View::OnPaintBorder(class gfx::Canvas *)",
     LR"(?OnPaintBorder@View@views@@MEAAXPEAVCanvas@gfx@@@Z)"},
    {L"public: virtual void __cdecl cc::RecordPaintCanvas::drawPath(class SkPath const &,class cc::PaintFlags const &,enum cc::UsePaintCache)",
     LR"(?drawPath@RecordPaintCanvas@cc@@UEAAXAEBVSkPath@@AEBVPaintFlags@2@W4UsePaintCache@2@@Z)"},
    {L"bool __cdecl wm::AnimateOnChildWindowVisibilityChanged(class aura::Window *,bool)",
     LR"(?AnimateOnChildWindowVisibilityChanged@wm@@YA_NPEAVWindow@aura@@_N@Z)"},
    {L"struct HWND__ * __cdecl views::HWNDForNativeWindow(class aura::Window *const)",
     LR"(?HWNDForNativeWindow@views@@YAPEAUHWND__@@QEAVWindow@aura@@@Z)"},
    {L"void __cdecl wm::SetWindowVisibilityAnimationType(class aura::Window *,int)",
     LR"(?SetWindowVisibilityAnimationType@wm@@YAXPEAVWindow@aura@@H@Z)"},
    {L"void __cdecl wm::SetWindowVisibilityAnimationDuration(class aura::Window *,class base::TimeDelta const &)",
     LR"(?SetWindowVisibilityAnimationDuration@wm@@YAXPEAVWindow@aura@@AEBVTimeDelta@base@@@Z)"},
    {L"public: __cdecl ViewShadow::ViewShadow(class views::View *,class gfx::RoundedCornersF const &,struct ViewShadow::ShadowParameters const &)",
     LR"(??0ViewShadow@@QEAA@PEAVView@views@@AEBVRoundedCornersF@gfx@@AEBUShadowParameters@0@@Z)"},
};
static_assert(ARRAYSIZE(kFeatureSymbols) == kFeatureSlots);

static bool ResolveFeatureAddresses(HMODULE module, size_t *result, bool useOnlineCache,
                                    bool allowFallback) {
    void *addresses[kFeatureSlots]{};
    WindhawkUtils::SYMBOL_HOOK hooks[kFeatureSlots];
    for (unsigned i = 0; i < kFeatureSlots; ++i) {
        const auto &name = kFeatureSymbols[i];
        if (!allowFallback) {
            hooks[i] = {{name.undecorated}, &addresses[i], nullptr, true};
        } else if (name.alternate.empty()) {
            hooks[i] = {{name.undecorated, name.decorated}, &addresses[i], nullptr, true};
        } else {
            hooks[i] = {{name.undecorated, name.decorated, name.alternate},
                        &addresses[i], nullptr, true};
        }
    }

    // Keep the small cache names and avoid undecorating the full PDB.
    WH_HOOK_SYMBOLS_OPTIONS options{};
    options.optionsSize = sizeof(options);
    options.symbolServer = allowFallback ? kBraveSymbolServer : L"";
    options.onlineCacheUrl = useOnlineCache ? kOnlineSymbolCache : L"";
    options.noUndecoratedSymbols = allowFallback;
    if (!WindhawkUtils::HookSymbols(module, hooks, ARRAYSIZE(hooks), &options))
        return false;
    return ValidateFeatureAddresses(module, addresses, result);
}
// </feature-kernel>

// <native-ui>
// Native UI effects own their resources. No dispatcher belonging to Brave is
// stopped, and no callback from this DLL survives Wh_ModBeforeUninit.
namespace NativeUi {
enum Feature : unsigned {
    Vertical = 1,
    Toolbar = 2,
    Webpage = 4,
    Menus = 8,
    Popups = 16,
    Suggestions = 32
};
static std::atomic<unsigned> supported{0}, enabled{Menus | Popups | Suggestions};
static std::atomic<bool> ready{false};
using Paint = void (*)(void *, void *);
using BackgroundPaint = void (*)(const void *, void *, void *);
using GetColor = unsigned (*)(const void *, int);
using WindowForView = HWND (*)(const void *);
struct RoundRect {
    float left, top, right, bottom;
    float radii[8];
};
using DrawRoundRect = void (*)(void *, const RoundRect &, const void *);
static Paint originalMenu = nullptr;
static BackgroundPaint originalBubble = nullptr;
static GetColor originalColor = nullptr;
static WindowForView windowForView = nullptr;
static DrawRoundRect originalRoundRect = nullptr;
static thread_local unsigned backgroundScope = 0;
static thread_local HWND backgroundWindow = nullptr;
static bool Active(unsigned feature) {
    return ready.load(std::memory_order_acquire) &&
           (supported.load(std::memory_order_relaxed) & enabled.load(std::memory_order_relaxed) &
            feature);
}
static std::atomic<bool> transparencyAllowed{false};
static bool ReadTransparencyAllowed() {
    HIGHCONTRASTW contrast{sizeof(contrast)};
    if (!SystemParametersInfoW(SPI_GETHIGHCONTRAST, sizeof(contrast), &contrast, 0) ||
        (contrast.dwFlags & HCF_HIGHCONTRASTON))
        return false;
    DWORD enabled = 1, size = sizeof(enabled);
    RegGetValueW(HKEY_CURRENT_USER,
                 L"Software\\Microsoft\\Windows\\CurrentVersion\\Themes\\Personalize",
                 L"EnableTransparency", RRF_RT_REG_DWORD, nullptr, &enabled, &size);
    return enabled != 0;
}
static bool RefreshTransparencyAllowed() {
    const bool allowed = ReadTransparencyAllowed();
    return transparencyAllowed.exchange(allowed, std::memory_order_relaxed) != allowed;
}
static bool UserAllowsTransparency() {
    return transparencyAllowed.load(std::memory_order_relaxed);
}
static bool PopupWindow(HWND hwnd) {
    DWORD process = 0;
    if (!hwnd || !GetWindowThreadProcessId(hwnd, &process) || process != GetCurrentProcessId())
        return false;
    const LONG_PTR style = GetWindowLongPtrW(hwnd, GWL_STYLE);
    if (!(style & WS_POPUP) || (style & (WS_CHILD | WS_THICKFRAME | WS_CAPTION)))
        return false;
    wchar_t name[48]{};
    return GetClassNameW(hwnd, name, ARRAYSIZE(name)) &&
           (!wcscmp(name, L"Chrome_WidgetWin_0") || !wcscmp(name, L"Chrome_WidgetWin_1"));
}
// Bubble contents and their Windows backdrop use a short fade, without scale.
// Menus do not receive this marker or animation policy.
namespace PopupTransition {
using Animate = bool (*)(void *, bool);
using WindowForNative = HWND (*)(void *);
using SetType = void (*)(void *, int);
using SetDuration = void (*)(void *, const long long &);
static constexpr unsigned kFadeMs = 160;
static SetType setType = nullptr;
static SetDuration setDuration = nullptr;
static bool CanFade();
static unsigned long long Begin(HWND hwnd, bool visible);
static void Immediate(HWND hwnd, unsigned long long serial);
static Animate original = nullptr;
static WindowForNative windowForNative = nullptr;
static SRWLOCK lock = SRWLOCK_INIT;
static std::vector<HWND> windows;
static bool stopped = false;
static constexpr wchar_t kProperty[] = L"BraveAcrylic.PopupFade.4.0";
static HANDLE Owner() { return reinterpret_cast<HANDLE>(&lock); }
static void Mark(HWND hwnd) {
    if (!original || !PopupWindow(hwnd) || !Active(Popups) || !UserAllowsTransparency())
        return;
    AcquireSRWLockExclusive(&lock);
    if (!stopped && Active(Popups) && CanFade() && !GetPropW(hwnd, kProperty) &&
        SetPropW(hwnd, kProperty, Owner()))
        windows.push_back(hwnd);
    ReleaseSRWLockExclusive(&lock);
}
static void Forget(HWND hwnd) {
    AcquireSRWLockExclusive(&lock);
    windows.erase(std::remove(windows.begin(), windows.end(), hwnd), windows.end());
    ReleaseSRWLockExclusive(&lock);
}
static bool AnimateHook(void *window, bool visible) {
    if (Active(Popups) && UserAllowsTransparency()) {
        const HWND hwnd = windowForNative(window);
        if (PopupWindow(hwnd) && GetPropW(hwnd, kProperty) == Owner()) {
            const auto serial = Begin(hwnd, visible);
            if (!serial)
                return original(window, visible);
            // Chromium's FADE type; transient native properties, not saved preferences.
            setType(window, 3);
            const long long duration = kFadeMs * 1000ll; // base::TimeDelta microseconds
            setDuration(window, duration);
            const bool animated = original(window, visible);
            if (!animated)
                Immediate(hwnd, serial);
            return animated;
        }
    }
    return original(window, visible);
}
static void Clear(bool stop) {
    AcquireSRWLockExclusive(&lock);
    stopped |= stop;
    for (HWND hwnd : windows)
        if (GetPropW(hwnd, kProperty) == Owner())
            RemovePropW(hwnd, kProperty);
    windows.clear();
    ReleaseSRWLockExclusive(&lock);
}
} // namespace PopupTransition
struct Scope {
    bool enabled;
    HWND previous;
    Scope(bool value, HWND window = nullptr) : enabled(value), previous(backgroundWindow) {
        if (enabled)
            ++backgroundScope;
        backgroundWindow = window;
    }
    ~Scope() {
        if (enabled)
            --backgroundScope;
        backgroundWindow = previous;
    }
};
static unsigned Tint(unsigned color, bool scoped) {
    return !scoped ? color : (color & 0x00ffffffu) |
        ((((color >> 24) * s_popupOpacity.load(std::memory_order_relaxed) + 50u) / 100u) << 24);
}

static thread_local unsigned popupTint = 0;
static thread_local bool popupTintKnown = false;
namespace Material {
namespace composition = winrt::Windows::UI::Composition;
constexpr wchar_t kProperty[] = L"BraveAcrylic.PopupMaterial.3.8";
MIDL_INTERFACE("29E691FA-4567-4DCA-B319-D0F207EB6807") DesktopInterop : IUnknown {
    virtual HRESULT STDMETHODCALLTYPE CreateDesktopWindowTarget(HWND, BOOL, void **) = 0;
    virtual HRESULT STDMETHODCALLTYPE EnsureOnThread(DWORD) = 0;
};
struct Shape {
    float left, top, width, height, rx, ry, scale;
};
static bool Equal(const Shape &a, const Shape &b) {
    return !memcmp(&a, &b, sizeof(Shape));
}
struct Fade {
    unsigned long long serial = 0;
    ULONGLONG start = 0;
    float from = 1, to = 1;
    unsigned duration = 0;
};
static float FadeValue(const Fade &fade, ULONGLONG now) {
    const float t = fade.duration ? std::min(1.f, static_cast<float>(now - fade.start) / fade.duration) : 1;
    return fade.from + (fade.to - fade.from) * t;
}
struct Request {
    Shape shape{};
    Fade fade{};
    bool valid = false, applied = false, pending = false;
    unsigned feature = 0;
    bool hoverCard = false;
    unsigned tint = 0;
    bool extensionsMenu = false;
    bool pageInfo = false, downloads = false, media = false;
};
struct State {
    composition::Desktop::DesktopWindowTarget target{nullptr};
    composition::ContainerVisual root{nullptr};
    unsigned long long fadeSerial = 0;
    composition::SpriteVisual sprite{nullptr}, shade{nullptr};
    composition::CompositionColorBrush shadeBrush{nullptr};
    composition::CompositionRoundedRectangleGeometry geometry{nullptr};
    BOOL previous = FALSE;
    bool changed = false, previousKnown = false;
    DWORD previousBorder = 0;
    bool borderKnown = false, borderChanged = false;
};
static SRWLOCK lock = SRWLOCK_INIT;
static std::unordered_map<HWND, Request> requests;
static HANDLE thread = nullptr, startEvent = nullptr;
static DWORD threadId = 0;
static std::atomic<bool> stopping{false};
static bool workerReady = false, workerFinished = false; // protected by lock
static constexpr UINT kUpdate = WM_APP + 0x137, kStop = WM_APP + 0x138, kRecheck = WM_APP + 0x139;
static bool CanQueueLocked() {
    return !stopping.load() && thread && !workerFinished;
}
static void NotifyLocked() {
    if (workerReady)
        PostThreadMessageW(threadId, kUpdate, 0, 0);
}
static constexpr wchar_t kSettingsClass[] = L"Windhawk.BraveAcrylic.TransparencySettings";
static LRESULT CALLBACK SettingsWindowProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
    if ((message == WM_SETTINGCHANGE || message == WM_THEMECHANGED) &&
        RefreshTransparencyAllowed()) {
        PostThreadMessageW(GetCurrentThreadId(), kRecheck, 0, 0);
    }
    return DefWindowProcW(hwnd, message, wParam, lParam);
}
static std::unordered_map<HWND, State> *live = nullptr; // worker-thread only
static void Destroy(HWND hwnd) {
    if (!live)
        return;
    const auto found = live->find(hwnd);
    if (found == live->end())
        return;
    auto &state = found->second;
    if (GetPropW(hwnd, kProperty) == reinterpret_cast<HANDLE>(&state)) {
        RemovePropW(hwnd, kProperty);
        if (state.changed && state.previousKnown)
            DwmSetWindowAttribute(hwnd, 17, &state.previous, sizeof(BOOL));
        if (state.borderKnown && state.borderChanged)
            DwmSetWindowAttribute(hwnd, 34, &state.previousBorder, sizeof(DWORD));
    }
    try {
        if (state.target)
            state.target.Close();
    } catch (...) {
    }
    live->erase(found);
}
static void CALLBACK WindowEvent(HWINEVENTHOOK, DWORD, HWND hwnd, LONG object, LONG child, DWORD,
                                 DWORD) {
    if (object != OBJID_WINDOW || child != CHILDID_SELF || IsWindow(hwnd))
        return;
    Destroy(hwnd);
    PopupTransition::Forget(hwnd);
    AcquireSRWLockExclusive(&lock);
    requests.erase(hwnd);
    ReleaseSRWLockExclusive(&lock);
}
static DWORD WINAPI Run(void *) {
    HRESULT apartment = RoInitialize(RO_INIT_SINGLETHREADED);
    winrt::Windows::System::DispatcherQueueController queue{nullptr};
    composition::Compositor compositor{nullptr};
    std::unordered_map<HWND, State> states;
    HWINEVENTHOOK events = nullptr;
    HMODULE messaging = nullptr;
    HMODULE instance = nullptr;
    HWND settingsWindow = nullptr;
    ATOM settingsClass = 0;
    try {
        winrt::check_hresult(apartment);
        MSG ensure{};
        PeekMessageW(&ensure, nullptr, WM_USER, WM_USER, PM_NOREMOVE);
        struct Options {
            DWORD size, thread, apartment;
        } options{sizeof(Options), 2, 2};
        using CreateQueue = HRESULT(WINAPI *)(Options, void **);
        messaging = LoadLibraryExW(L"CoreMessaging.dll", nullptr, LOAD_LIBRARY_SEARCH_SYSTEM32);
        const auto create = messaging ? reinterpret_cast<CreateQueue>(GetProcAddress(
                                            messaging, "CreateDispatcherQueueController"))
                                      : nullptr;
        if (!create)
            throw winrt::hresult_error(HRESULT_FROM_WIN32(ERROR_PROC_NOT_FOUND));
        winrt::check_hresult(create(options, winrt::put_abi(queue)));
        compositor = composition::Compositor();
        live = &states;
        events = SetWinEventHook(EVENT_OBJECT_DESTROY, EVENT_OBJECT_DESTROY, nullptr, WindowEvent,
                                 GetCurrentProcessId(), 0, WINEVENT_OUTOFCONTEXT);
        if (!events)
            throw winrt::hresult_error(HRESULT_FROM_WIN32(GetLastError()));
        if (!GetModuleHandleExW(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS |
                                    GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT,
                                reinterpret_cast<LPCWSTR>(SettingsWindowProc), &instance)) {
            throw winrt::hresult_error(HRESULT_FROM_WIN32(GetLastError()));
        }
        WNDCLASSW windowClass{};
        windowClass.lpfnWndProc = SettingsWindowProc;
        windowClass.hInstance = instance;
        windowClass.lpszClassName = kSettingsClass;
        settingsClass = RegisterClassW(&windowClass);
        if (!settingsClass)
            throw winrt::hresult_error(HRESULT_FROM_WIN32(GetLastError()));
        // A hidden top-level window receives Windows setting broadcasts. A
        // message-only window does not. It never shows or handles browser input.
        settingsWindow = CreateWindowExW(0, kSettingsClass, L"", WS_POPUP, 0, 0, 0, 0, nullptr,
                                         nullptr, instance, nullptr);
        if (!settingsWindow)
            throw winrt::hresult_error(HRESULT_FROM_WIN32(GetLastError()));
        RefreshTransparencyAllowed();
        AcquireSRWLockExclusive(&lock);
        workerReady = true;
        ReleaseSRWLockExclusive(&lock);
        SetEvent(startEvent);
        PostThreadMessageW(GetCurrentThreadId(), kUpdate, 0, 0);
        MSG message{};
        while (GetMessageW(&message, nullptr, 0, 0) > 0) {
            if (message.message == kStop)
                break;
            if (message.message == kUpdate || message.message == kRecheck) {
                std::vector<std::pair<HWND, Request>> work;
                AcquireSRWLockExclusive(&lock);
                for (auto &[hwnd, request] : requests)
                    if (request.pending || message.message == kRecheck) {
                        request.pending = false;
                        work.emplace_back(hwnd, request);
                    }
                ReleaseSRWLockExclusive(&lock);
                const bool allowed = UserAllowsTransparency();
                for (const auto &[hwnd, request] : work) {
                    bool applied = false;
                    if (!stopping.load() && allowed && Active(request.feature) && request.valid &&
                        PopupWindow(hwnd))
                        try {
                            auto found = states.find(hwnd);
                            if (found == states.end()) {
                                auto [slot, inserted] = states.try_emplace(hwnd);
                                (void)inserted;
                                auto &state = slot->second;
                                if (!SetPropW(hwnd, kProperty, reinterpret_cast<HANDLE>(&state)))
                                    throw winrt::hresult_error(HRESULT_FROM_WIN32(GetLastError()));
                                // This attribute is set-only on some Windows builds.
                                // Closing our target removes its visual effect. Do
                                // not invent/restore a prior flag when it cannot be read.
                                state.previousKnown = SUCCEEDED(
                                    DwmGetWindowAttribute(hwnd, 17, &state.previous, sizeof(BOOL)));
                                state.borderKnown = SUCCEEDED(DwmGetWindowAttribute(
                                    hwnd, 34, &state.previousBorder, sizeof(DWORD)));
                                const DWORD noBorder = 0xfffffffeu; // DWMWA_COLOR_NONE
                                if (state.borderKnown)
                                    state.borderChanged = SUCCEEDED(DwmSetWindowAttribute(
                                        hwnd, 34, &noBorder, sizeof(noBorder)));
                                BOOL enable = TRUE;
                                winrt::check_hresult(
                                    DwmSetWindowAttribute(hwnd, 17, &enable, sizeof(enable)));
                                state.changed = true;
                                winrt::com_ptr<DesktopInterop> interop;
                                winrt::check_hresult(
                                    winrt::get_unknown(compositor)
                                        ->QueryInterface(
                                            GUID{0x29E691FA,
                                                 0x4567,
                                                 0x4DCA,
                                                 {0xB3, 0x19, 0xD0, 0xF2, 0x07, 0xEB, 0x68, 0x07}},
                                            interop.put_void()));
                                winrt::check_hresult(interop->CreateDesktopWindowTarget(
                                    hwnd, FALSE, winrt::put_abi(state.target)));
                                state.root = compositor.CreateContainerVisual();
                                state.sprite = compositor.CreateSpriteVisual();
                                state.geometry = compositor.CreateRoundedRectangleGeometry();
                                state.sprite.Brush(compositor.CreateHostBackdropBrush());
                                state.sprite.Clip(compositor.CreateGeometricClip(state.geometry));
                                state.root.Children().InsertAtBottom(state.sprite);
                                state.shade = compositor.CreateSpriteVisual();
                                state.shade.Clip(compositor.CreateGeometricClip(state.geometry));
                                state.shadeBrush = compositor.CreateColorBrush();
                                state.shade.Brush(state.shadeBrush);
                                state.root.Children().InsertAtTop(state.shade);
                                state.target.Root(state.root);
                                found = slot;
                            }
                            auto &state = found->second;
                            const auto &shape = request.shape;
                            if (request.feature == Popups && request.fade.serial != state.fadeSerial) {
                                const auto &fade = request.fade;
                                const ULONGLONG now = GetTickCount64();
                                const auto elapsed = now - fade.start;
                                state.root.StopAnimation(L"Opacity");
                                state.root.Opacity(fade.to);
                                if (fade.duration && elapsed < fade.duration) {
                                    auto animation = compositor.CreateScalarKeyFrameAnimation();
                                    auto linear = compositor.CreateLinearEasingFunction();
                                    animation.InsertKeyFrame(0, FadeValue(fade, now), linear);
                                    animation.InsertKeyFrame(1, fade.to, linear);
                                    animation.Duration(std::chrono::milliseconds(fade.duration - elapsed));
                                    state.root.StartAnimation(L"Opacity", animation);
                                }
                                state.fadeSerial = fade.serial;
                            }
                            state.sprite.Offset(
                                {shape.left * shape.scale, shape.top * shape.scale, 0});
                            state.sprite.Size(
                                {shape.width * shape.scale, shape.height * shape.scale});
                            state.shade.Offset(
                                {shape.left * shape.scale, shape.top * shape.scale, 0});
                            state.shade.Size(
                                {shape.width * shape.scale, shape.height * shape.scale});
                            const unsigned tint = request.tint;
                            state.shadeBrush.Color(winrt::Windows::UI::Color{
                                static_cast<BYTE>(tint >> 24), static_cast<BYTE>(tint >> 16),
                                static_cast<BYTE>(tint >> 8), static_cast<BYTE>(tint)});
                            state.geometry.Size(
                                {shape.width * shape.scale, shape.height * shape.scale});
                            state.geometry.CornerRadius(
                                {shape.rx * shape.scale, shape.ry * shape.scale});
                            applied = true;
                        } catch (const winrt::hresult_error &failure) {
                            Wh_Log(L"Popup backdrop unavailable: 0x%08X",
                                   static_cast<unsigned>(failure.code()));
                            Destroy(hwnd);
                        }
                    else
                        Destroy(hwnd);
                    AcquireSRWLockExclusive(&lock);
                    const auto current = requests.find(hwnd);
                    bool repaint = false;
                    if (current != requests.end() && Equal(current->second.shape, request.shape) &&
                        current->second.tint == request.tint) {
                        repaint = current->second.applied != applied;
                        current->second.applied = applied;
                    }
                    ReleaseSRWLockExclusive(&lock);
                    if (repaint)
                        InvalidateRect(hwnd, nullptr, FALSE);
                }
            } else {
                TranslateMessage(&message);
                DispatchMessageW(&message);
            }
        }
    } catch (const winrt::hresult_error &failure) {
        Wh_Log(L"Popup compositor unavailable: 0x%08X", static_cast<unsigned>(failure.code()));
    } catch (...) {
        Wh_Log(L"Popup compositor unavailable");
    }
    AcquireSRWLockExclusive(&lock);
    workerReady = false;
    workerFinished = true;
    requests.clear();
    ReleaseSRWLockExclusive(&lock);
    PopupTransition::Clear(false);
    SetEvent(startEvent);
    if (events)
        UnhookWinEvent(events);
    if (settingsWindow)
        DestroyWindow(settingsWindow);
    if (settingsClass)
        UnregisterClassW(kSettingsClass, instance);
    while (!states.empty())
        Destroy(states.begin()->first);
    live = nullptr;
    try {
        if (compositor)
            compositor.Close();
    } catch (...) {
    }
    compositor = nullptr;
    // This queue belongs only to this worker. Pump its asynchronous shutdown
    // to completion before releasing the callback or allowing DLL unload.
    if (queue)
        try {
            auto shutdown = queue.ShutdownQueueAsync();
            while (shutdown.Status() == winrt::Windows::Foundation::AsyncStatus::Started) {
                MSG message{};
                while (PeekMessageW(&message, nullptr, 0, 0, PM_REMOVE)) {
                    TranslateMessage(&message);
                    DispatchMessageW(&message);
                }
                MsgWaitForMultipleObjects(0, nullptr, FALSE, 10, QS_ALLINPUT);
            }
            shutdown.GetResults();
        } catch (...) {
        }
    queue = nullptr;
    if (messaging)
        FreeLibrary(messaging);
    if (SUCCEEDED(apartment))
        RoUninitialize();
    return 0;
}
static bool Start() {
    AcquireSRWLockExclusive(&lock);
    if (stopping.load()) {
        ReleaseSRWLockExclusive(&lock);
        return false;
    }
    if (!thread) {
        startEvent = CreateEventW(nullptr, TRUE, FALSE, nullptr);
        if (startEvent)
            thread = CreateThread(nullptr, 0, Run, nullptr, 0, &threadId);
        if (!thread && startEvent) {
            CloseHandle(startEvent);
            startEvent = nullptr;
        }
    }
    const bool started = CanQueueLocked();
    ReleaseSRWLockExclusive(&lock);
    return started;
}
static bool CanFade() {
    AcquireSRWLockShared(&lock);
    const bool result = workerReady && CanQueueLocked();
    ReleaseSRWLockShared(&lock);
    return result;
}
static bool Geometry(const RoundRect &input, HWND hwnd, Shape *out) {
    const float values[]{input.left,     input.top,      input.right,    input.bottom,
                         input.radii[0], input.radii[1], input.radii[2], input.radii[3],
                         input.radii[4], input.radii[5], input.radii[6], input.radii[7]};
    for (float value : values)
        if (!std::isfinite(value) || value < 0 || value > 32768)
            return false;
    for (unsigned i = 2; i < 8; ++i)
        if (input.radii[i] != input.radii[i % 2])
            return false;
    const float scale = GetDpiForWindow(hwnd) / 96.f;
    RECT bounds{};
    if (!GetClientRect(hwnd, &bounds) || scale <= 0)
        return false;
    const float width = input.right - input.left, height = input.bottom - input.top;
    if (width * scale < bounds.right * .6f || height * scale < bounds.bottom * .6f ||
        input.right * scale > bounds.right + 2 || input.bottom * scale > bounds.bottom + 2 ||
        input.radii[0] > width / 2 || input.radii[1] > height / 2)
        return false;
    *out = {input.left, input.top, width, height, input.radii[0], input.radii[1], scale};
    return true;
}
static void Update(HWND hwnd, const RoundRect &input, unsigned feature) {
    Shape shape{};
    if (!Geometry(input, hwnd, &shape) || !Start())
        return;
    // Initialization is asynchronous: the first paint stays fully native.
    // No UI thread waits for a compositor or a cross-thread window call.
    AcquireSRWLockExclusive(&lock);
    if (CanQueueLocked()) {
        auto &request = requests[hwnd];
        const unsigned tint = feature == Popups && popupTintKnown ? Tint(popupTint, true) : 0;
        if (!request.valid || !Equal(request.shape, shape) || request.feature != feature ||
            request.tint != tint) {
            request.shape = shape;
            request.feature = feature;
            request.tint = tint;
            request.valid = true;
            request.pending = true;
            NotifyLocked();
        }
    }
    ReleaseSRWLockExclusive(&lock);
}
static unsigned long long FadeBegin(HWND hwnd, bool visible) {
    unsigned long long serial = 0;
    AcquireSRWLockExclusive(&lock);
    if (workerReady && CanQueueLocked()) {
        auto &request = requests[hwnd];
        const auto now = GetTickCount64();
        const float from = request.fade.serial ? FadeValue(request.fade, now) : (visible ? 0.f : 1.f);
        serial = request.fade.serial + 1;
        request.fade = {serial, now, from, visible ? 1.f : 0.f, PopupTransition::kFadeMs};
        if (request.valid && !request.pending)
            NotifyLocked();
        request.pending = true;
    }
    ReleaseSRWLockExclusive(&lock);
    return serial;
}
static void FadeImmediate(HWND hwnd, unsigned long long serial) {
    AcquireSRWLockExclusive(&lock);
    const auto found = requests.find(hwnd);
    if (!stopping.load() && found != requests.end() && found->second.fade.serial == serial) {
        found->second.fade.duration = 0;
        ++found->second.fade.serial;
        if (!found->second.pending)
            NotifyLocked();
        found->second.pending = true;
    }
    ReleaseSRWLockExclusive(&lock);
}
static void Forget(HWND hwnd) {
    AcquireSRWLockExclusive(&lock);
    const auto found = requests.find(hwnd);
    if (found != requests.end()) {
        found->second.valid = false;
        found->second.pending = true;
        NotifyLocked();
    }
    ReleaseSRWLockExclusive(&lock);
}
static void Stop() {
    AcquireSRWLockExclusive(&lock);
    stopping = true;
    const HANDLE worker = thread;
    const DWORD id = threadId;
    ReleaseSRWLockExclusive(&lock);
    if (worker) {
        WaitForSingleObject(startEvent, INFINITE);
        PostThreadMessageW(id, kStop, 0, 0);
        WaitForSingleObject(worker, INFINITE);
        CloseHandle(worker);
    }
    AcquireSRWLockExclusive(&lock);
    requests.clear();
    thread = nullptr;
    threadId = 0;
    if (startEvent) {
        CloseHandle(startEvent);
        startEvent = nullptr;
    }
    ReleaseSRWLockExclusive(&lock);
}
} // namespace Material
namespace PopupTransition {
static bool CanFade() { return Material::CanFade(); }
static unsigned long long Begin(HWND hwnd, bool visible) { return Material::FadeBegin(hwnd, visible); }
static void Immediate(HWND hwnd, unsigned long long serial) { Material::FadeImmediate(hwnd, serial); }
} // namespace PopupTransition
static thread_local unsigned paintFeature = 0;
static void RoundRectHook(void *canvas, const RoundRect &shape, const void *flags) {
    if (backgroundWindow && Active(paintFeature))
        Material::Update(backgroundWindow, shape, paintFeature);
    Material::Shape bounds{};
    if (paintFeature == Popups && backgroundWindow && popupTintKnown && Active(Popups) &&
        Material::Geometry(shape, backgroundWindow, &bounds))
        return;
    originalRoundRect(canvas, shape, flags);
}
static unsigned ColorHook(const void *provider, int id) {
    const auto color = originalColor(provider, id);
    if (backgroundScope && paintFeature == Popups) {
        popupTint = color;
        popupTintKnown = true;
    }
    return Tint(color, ready.load(std::memory_order_relaxed) && backgroundScope != 0);
}
static HWND Candidate(const void *view, unsigned feature) {
    if (!view || !Active(feature))
        return nullptr;
    HWND hwnd = windowForView(view);
    return PopupWindow(hwnd) && UserAllowsTransparency() ? hwnd : nullptr;
}
// Suppress only known native backing roles inside a shaped popup. Foreground
// paint remains native, including cross-fading text and fading icon layers.
static bool SuppressPopupBackground(void *view) {
    if (!view || !Active(Popups) || !s_background.getClass)
        return false;
    BraveBackground::ClassName name{};
    s_background.getClass(view, &name);
    if (!name.data || name.length > 127)
        return false;
    const std::string_view cls(name.data, name.length);
    const bool hover = cls == "TabHoverCardBubbleView";
    const bool extensions = cls == "ExtensionsMenuView" || cls == "ExtensionsMenuMainPageView" ||
                            cls == "ExtensionsMenuSitePermissionsPageView";
    const bool pageInfo = cls == "BravePageInfoBubbleView" || cls == "PageInfoBubbleView" ||
                          cls == "InternalPageInfoBubbleView" || cls == "PageInfoMainView";
    const bool downloads = cls == "DownloadBubbleContentsView" || cls == "DownloadDialogView" ||
                           cls == "DownloadBubblePrimaryView" || cls == "DownloadBubblePartialView";
    const bool media = cls == "MediaDialogView" || cls == "MediaItemUIListView" ||
                       cls == "MediaItemUIUpdatedView" || cls == "MediaItemUIView";
    const bool scrollBacking = cls == "ScrollView" || cls == "ScrollView::Viewport";
    const bool pageSwitcher = cls == "PageSwitcherView";
    // ScrollView paints its own background, then repeats it on its viewport
    // and (with layered scrolling) its contents. These containers are cleared
    // only after this popup identifies itself as the native Extensions menu.
    // Extension HTML popups and generic containers in other bubbles stay native.
    const bool extensionBacking = cls == "ScrollView" || cls == "ScrollView::Viewport" ||
                                  cls == "View" || cls == "BoxLayoutView" ||
                                  cls == "FlexLayoutView" || cls == "SectionContainer";
    if (!hover && !extensions && !pageInfo && !downloads && !media && !pageSwitcher &&
        !extensionBacking && cls != "DialogClientView" &&
        cls != "FooterView" && cls != "ImageView" && cls != "FadeLabel")
        return false;
    const auto hwnd = NativeUi::Candidate(view, NativeUi::Popups);
    if (!hwnd)
        return false;
    AcquireSRWLockExclusive(&NativeUi::Material::lock);
    const auto found = NativeUi::Material::requests.find(hwnd);
    const bool shaped = found != NativeUi::Material::requests.end() && found->second.valid &&
                        found->second.feature == NativeUi::Popups;
    if (shaped && hover)
        found->second.hoverCard = true;
    if (shaped && extensions)
        found->second.extensionsMenu = true;
    if (shaped && pageInfo)
        found->second.pageInfo = true;
    if (shaped && downloads)
        found->second.downloads = true;
    if (shaped && media)
        found->second.media = true;
    const bool clear = shaped && !hover &&
                       (pageSwitcher ? found->second.pageInfo
                        : extensionBacking ? (found->second.extensionsMenu ||
                                              ((cls == "View" || cls == "FlexLayoutView") &&
                                               found->second.downloads) ||
                                              (scrollBacking && (found->second.downloads ||
                                                                 found->second.pageInfo ||
                                                                 found->second.media)))
                                         : ((cls != "ImageView" && cls != "FadeLabel") ||
                                            found->second.hoverCard));
    ReleaseSRWLockExclusive(&NativeUi::Material::lock);
    return clear;
}
static void (*originalBubbleTheme)(void *) = nullptr;
static void (*originalLayerOpaque)(void *, bool) = nullptr;
static void (*originalFadeBackground)(void *, void *) = nullptr;
static void FadeBackgroundHook(void *view, void *canvas) {
    if (canvas && SuppressPopupBackground(view))
        return;
    originalFadeBackground(view, canvas);
}
static thread_local bool bubbleThemeUpdating = false;
static void LayerOpaqueHook(void *layer, bool opaque) {
    originalLayerOpaque(layer, bubbleThemeUpdating ? false : opaque);
}
static void BubbleThemeHook(void *view) {
    const auto hwnd = NativeUi::Candidate(view, NativeUi::Popups);
    const bool previous = bubbleThemeUpdating;
    bubbleThemeUpdating = hwnd != nullptr;
    PopupTransition::Mark(hwnd);
    originalBubbleTheme(view);
    bubbleThemeUpdating = previous;
}

static void MenuHook(void *view, void *canvas) {
    HWND hwnd = Candidate(view, Menus);
    const auto previous = paintFeature;
    paintFeature = Menus;
    // Chromium retains the first display list and later repaints only damaged
    // rows. Its initial background must already carry alpha; HWND invalidation
    // after our asynchronous backdrop attaches cannot repaint retained Views.
    Scope scope(hwnd != nullptr, hwnd);
    originalMenu(view, canvas);
    paintFeature = previous;
}
static void BubbleHook(const void *background, void *canvas, void *view) {
    BraveBackground::ClassName role{};
    s_background.getClass(view, &role);
    if (!role.data || std::string_view(role.data, role.length) != "BubbleFrameView") {
        originalBubble(background, canvas, view);
        return;
    }
    HWND hwnd = Candidate(view, Popups);
    const auto previous = paintFeature;
    paintFeature = Popups;
    const auto previousTint = popupTint;
    const bool previousKnown = popupTintKnown;
    popupTintKnown = false;
    Scope scope(hwnd != nullptr, hwnd);
    originalBubble(background, canvas, view);
    paintFeature = previous;
    popupTint = previousTint;
    popupTintKnown = previousKnown;
}

namespace Omnibox {
struct Rect {
    int x, y, width, height;
};
using Constructor = void *(*)(void *, void *, void *, bool);
using Destructor = void (*)(void *);
using SetBackground = void (*)(void *, void *);
using SetRounded = void (*)(void *, const float *, int);
using Bounds = Rect *(*)(const void *, Rect *);
using HeaderHeight = int (*)(bool);
using BeforeWidget = void (*)(void *, void *);
static Constructor originalConstructor = nullptr;
static Destructor originalDestructor = nullptr;
static SetBackground originalBackground = nullptr;
static SetRounded originalRounded = nullptr;
static BackgroundPaint originalSolid = nullptr;
static BeforeWidget originalBeforeWidget = nullptr;
static Bounds getBounds = nullptr, getScreenBounds = nullptr;
static HeaderHeight getHeader = nullptr;
static const void *solidVtable = nullptr;
struct Capture {
    void *frame;
    const void *background = nullptr;
    void *layer = nullptr;
    unsigned backgrounds = 0, layers = 0;
    float radius = 0;
};
struct Record {
    void *frame;
    void *layer;
    HWND window = nullptr;
    Rect sampling{};
    float radius = 0, scale = 0;
    HRGN originalRegion = nullptr;
    bool painted = false;
};
static thread_local Capture *constructing = nullptr;
static SRWLOCK lock = SRWLOCK_INIT;
static std::unordered_map<const void *, Record> backgrounds;
static std::vector<HWND> subclassedWindows;
static constexpr UINT_PTR kSubclass = 0xBA3901;
static UINT cleanupMessage = 0;
static bool SameRect(const Rect &a, const Rect &b) {
    return a.x == b.x && a.y == b.y && a.width == b.width && a.height == b.height;
}
static bool SamplingBounds(const Rect &frame, const Rect &host, int header, Rect *result) {
    if (frame.width <= 0 || frame.width > 32768 || frame.height <= 0 || frame.height > 32768 ||
        host.width <= 0 || host.width > 32768 || host.height <= 0 || host.height > 32768 ||
        header < 0 || header >= host.height)
        return false;
    const int64_t x = int64_t(host.x) - frame.x, y = int64_t(host.y) - frame.y + header;
    if (x < 0 || y < 0 || x + host.width > frame.width || y + host.height - header > frame.height)
        return false;
    *result = {int(x), int(y), host.width, host.height - header};
    return true;
}
static void Restore(const Record &record) {
    // Windows takes ownership of a successfully restored region.
    if (!record.window || !IsWindow(record.window) ||
        !SetWindowRgn(record.window, record.originalRegion, TRUE))
        if (record.originalRegion)
            DeleteObject(record.originalRegion);
    if (record.window)
        Material::Forget(record.window);
}
static void RestoreWindow(HWND hwnd) {
    std::vector<Record> records;
    AcquireSRWLockExclusive(&lock);
    for (auto it = backgrounds.begin(); it != backgrounds.end();)
        if (it->second.window == hwnd) {
            records.push_back(it->second);
            it = backgrounds.erase(it);
        } else
            ++it;
    ReleaseSRWLockExclusive(&lock);
    for (const auto &record : records)
        Restore(record);
}
static LRESULT CALLBACK WindowProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam, UINT_PTR,
                                   DWORD_PTR) {
    if (message == cleanupMessage || message == WM_NCDESTROY) {
        RestoreWindow(hwnd);
        RemoveWindowSubclass(hwnd, WindowProc, kSubclass);
        AcquireSRWLockExclusive(&lock);
        std::erase(subclassedWindows, hwnd);
        ReleaseSRWLockExclusive(&lock);
    }
    return DefSubclassProc(hwnd, message, wParam, lParam);
}
static void BeforeWidgetHook(void *params, void *widget) {
    if (!Active(Suggestions) || !UserAllowsTransparency())
        originalBeforeWidget(params, widget);
    // Otherwise leave Chromium's desktop-popup factory selected instead of its
    // in-window Aura override. Chromium owns the native popup and all its input.
}
static void BackgroundHook(void *view, void *value) {
    const void *background = nullptr;
    if (constructing && value) {
        memcpy(&background, value, sizeof(void *));
        const void *table = nullptr;
        if (background)
            memcpy(&table, background, sizeof(void *));
        if (table != solidVtable)
            background = nullptr;
    }
    originalBackground(view, value);
    if (background) {
        ++constructing->backgrounds;
        if (constructing->backgrounds == 1)
            constructing->background = background;
    }
}
static bool RoundedShape(const float *radii) {
    if (!radii)
        return false;
    for (unsigned i = 0; i < 4; ++i)
        if (!std::isfinite(radii[i]) || radii[i] < 0 || radii[i] > 128)
            return false;
    return true;
}
static void RoundedHook(void *layer, const float *radii, int reason) {
    originalRounded(layer, radii, reason);
    if (constructing && layer && RoundedShape(radii) && constructing->layer != layer) {
        ++constructing->layers;
        if (constructing->layers == 1) {
            constructing->layer = layer;
            constructing->radius = *std::min_element(radii, radii + 4);
        }
    }
}
static void *ConstructorHook(void *self, void *contents, void *location, bool forward) {
    Capture capture{self};
    Capture *previous = constructing;
    constructing = Active(Suggestions) && UserAllowsTransparency() ? &capture : nullptr;
    void *result = originalConstructor(self, contents, location, forward);
    constructing = previous;
    if (Active(Suggestions) && capture.backgrounds == 1 && capture.layers == 1 &&
        capture.background && capture.layer) {
        AcquireSRWLockExclusive(&lock);
        if (Active(Suggestions))
            backgrounds[capture.background] = {self, capture.layer, nullptr, {}, capture.radius};
        ReleaseSRWLockExclusive(&lock);
    }
    return result;
}
static void Forget(void *frame) {
    std::vector<Record> records;
    AcquireSRWLockExclusive(&lock);
    for (auto it = backgrounds.begin(); it != backgrounds.end();)
        if (it->second.frame == frame) {
            records.push_back(it->second);
            it = backgrounds.erase(it);
        } else
            ++it;
    ReleaseSRWLockExclusive(&lock);
    for (const auto &record : records)
        Restore(record);
}
static void DestructorHook(void *self) {
    Forget(self);
    originalDestructor(self);
}
static bool Blur(const void *background, void *view) {
    Record record{};
    AcquireSRWLockShared(&lock);
    const auto found = backgrounds.find(background);
    if (found != backgrounds.end())
        record = found->second;
    ReleaseSRWLockShared(&lock);
    if (!record.layer || !view || !Active(Suggestions) || !UserAllowsTransparency())
        return false;
    HWND hwnd = windowForView(view);
    if (!PopupWindow(hwnd) || GetWindowThreadProcessId(hwnd, nullptr) != GetCurrentThreadId())
        return false;
    Rect frame{}, host{}, local{}, sampling{};
    getBounds(view, &local);
    getScreenBounds(record.frame, &frame);
    getScreenBounds(view, &host);
    if (local.width != host.width || local.height != host.height ||
        !SamplingBounds(frame, host, getHeader(true), &sampling))
        return false;
    RECT client{};
    const float scale = GetDpiForWindow(hwnd) / 96.f;
    if (!GetClientRect(hwnd, &client) || scale <= 0 || scale > 8 ||
        (sampling.x + sampling.width) * scale > client.right + 2 ||
        (sampling.y + sampling.height) * scale > client.bottom + 2)
        return false;
    if (!record.window) {
        HRGN saved = CreateRectRgn(0, 0, 0, 0);
        if (!saved)
            return false;
        if (GetWindowRgn(hwnd, saved) == ERROR) {
            DeleteObject(saved);
            saved = nullptr;
        }
        if (!SetWindowSubclass(hwnd, WindowProc, kSubclass, 0)) {
            if (saved)
                DeleteObject(saved);
            return false;
        }
        AcquireSRWLockExclusive(&lock);
        const auto current = backgrounds.find(background);
        const bool keep = Active(Suggestions) && current != backgrounds.end() &&
                          current->second.frame == record.frame;
        if (keep) {
            current->second.window = hwnd;
            current->second.originalRegion = saved;
            if (std::find(subclassedWindows.begin(), subclassedWindows.end(), hwnd) ==
                subclassedWindows.end())
                subclassedWindows.push_back(hwnd);
        }
        ReleaseSRWLockExclusive(&lock);
        if (!keep) {
            RemoveWindowSubclass(hwnd, WindowProc, kSubclass);
            if (saved)
                DeleteObject(saved);
            return false;
        }
        record.window = hwnd;
        record.originalRegion = saved;
    }
    const float radius = std::min(record.radius, std::min(sampling.width, sampling.height) / 2.f);
    if (!record.painted || !SameRect(record.sampling, sampling) || record.scale != scale) {
        // Exclude the actual input field and shadow margins from the popup's
        // rounded OS region. Pointer input goes directly to the native controls.
        HRGN region = CreateRoundRectRgn(int(sampling.x * scale), int(sampling.y * scale),
                                         int((sampling.x + sampling.width) * scale) + 1,
                                         int((sampling.y + sampling.height) * scale) + 1,
                                         int(radius * scale * 2), int(radius * scale * 2));
        if (!region)
            return false;
        if (!SetWindowRgn(hwnd, region, TRUE)) {
            DeleteObject(region);
            return false;
        }
    }
    if (!Material::Start())
        return false;
    Material::Shape shape{float(sampling.x),
                          float(sampling.y),
                          float(sampling.width),
                          float(sampling.height),
                          radius,
                          radius,
                          scale};
    AcquireSRWLockExclusive(&Material::lock);
    if (Material::CanQueueLocked()) {
        auto &request = Material::requests[hwnd];
        if (!request.valid || !Material::Equal(request.shape, shape) ||
            request.feature != Suggestions) {
            request.shape = shape;
            request.feature = Suggestions;
            request.tint = 0;
            request.valid = true;
            request.pending = true;
            Material::NotifyLocked();
        }
    }
    ReleaseSRWLockExclusive(&Material::lock);
    AcquireSRWLockExclusive(&lock);
    const auto current = backgrounds.find(background);
    if (current != backgrounds.end()) {
        current->second.sampling = sampling;
        current->second.scale = scale;
        current->second.painted = true;
    }
    ReleaseSRWLockExclusive(&lock);
    return true;
}
static void SolidHook(const void *background, void *canvas, void *view) {
    Scope scope(Blur(background, view));
    originalSolid(background, canvas, view);
}
static void Stop() {
    std::vector<HWND> windows;
    AcquireSRWLockShared(&lock);
    windows = subclassedWindows;
    ReleaseSRWLockShared(&lock);
    // Do not hold a registry lock across dispatch to the owning UI thread.
    for (HWND hwnd : windows)
        SendMessageW(hwnd, cleanupMessage, 0, 0);
    AcquireSRWLockExclusive(&lock);
    backgrounds.clear();
    ReleaseSRWLockExclusive(&lock);
}
} // namespace Omnibox

static void Stop() {
    ready = false;
    Omnibox::Stop();
    PopupTransition::Clear(true);
    Material::Stop();
}
} // namespace NativeUi
// </native-ui>

static void InstallNativeBackgroundHooks(HMODULE module, const size_t *rva) {
    unsigned features = CompleteFeatures(rva);
    const unsigned optional = CompleteOptionalFeatures(rva, features);
    auto *base = reinterpret_cast<unsigned char *>(module);
    const auto address = [&](unsigned i) -> void * { return rva[i] ? base + rva[i] : nullptr; };
    const auto hook = [&]<typename Function>(unsigned slot, Function callback, Function *original) {
        return address(slot) && WindhawkUtils::SetFunctionHook(
                                    reinterpret_cast<Function>(address(slot)), callback, original);
    };
    s_background.clear = reinterpret_cast<BraveBackground::Clear>(address(1));
    s_background.getClass = reinterpret_cast<BraveBackground::GetClass>(address(2));
    s_background.setBackground = reinterpret_cast<BraveBackground::SetBackground>(address(5));
    s_locationFocus = reinterpret_cast<NativeFocus>(address(6));
    s_viewFocus = reinterpret_cast<NativeFocus>(address(7));
    s_setPageBase = reinterpret_cast<NativeSetPageBase>(address(11));
    constexpr unsigned windowFeatures = BraveBackground::All;
    if ((features & (windowFeatures | kPopups)) &&
        !hook(0, ViewOnPaintBackground_Hook, &s_background.originalPaint))
        features &= ~(windowFeatures | kPopups);
    if ((features & windowFeatures) &&
        !hook(3, WindowContentsTransparent_Hook, &s_background.originalTransparent))
        features &= ~windowFeatures;
    if ((features & kAddressBar) && (optional & kAddressShadow))
        hook(36, ConstructShadowHook, &s_originalShadow);
    if ((features & kVertical) &&
        !hook(4, SidebarConstructor_Hook, &s_background.originalConstruct))
        features &= ~kVertical;
    if ((features & kWebpage) &&
        (!hook(8, PageThemeHook, &s_originalTheme) || !hook(9, PageReadyHook, &s_originalReady) ||
         !hook(10, PageLayerColorHook, &s_originalLayerColor) ||
         !hook(12, AttachContentsHook, &s_originalAttachContents)))
        features &= ~kWebpage;
    if (!(features & kWebpage) ||
        ((features & kRoundedWebpage) &&
         (!hook(30, RoundedContents::BorderHook, &RoundedContents::originalBorder) ||
          !hook(31, RoundedContents::PathHook, &RoundedContents::originalPath))))
        features &= ~kRoundedWebpage;
    RoundedContents::available = (features & kRoundedWebpage) != 0;
    NativeUi::windowForView = reinterpret_cast<NativeUi::WindowForView>(address(13));
    if ((features & (kMenus | kPopups | kSuggestions)) &&
        !hook(14, NativeUi::ColorHook, &NativeUi::originalColor))
        features &= ~(kMenus | kPopups | kSuggestions);
    if ((features & (kMenus | kPopups)) &&
        !hook(17, NativeUi::RoundRectHook, &NativeUi::originalRoundRect))
        features &= ~(kMenus | kPopups);
    if ((features & kMenus) && !hook(15, NativeUi::MenuHook, &NativeUi::originalMenu))
        features &= ~kMenus;
    if ((features & kPopups) &&
        (!hook(16, NativeUi::BubbleHook, &NativeUi::originalBubble) ||
         !hook(25, NativeUi::BubbleThemeHook, &NativeUi::originalBubbleTheme) ||
         !hook(26, NativeUi::LayerOpaqueHook, &NativeUi::originalLayerOpaque) ||
         !hook(27, NativeUi::FadeBackgroundHook, &NativeUi::originalFadeBackground)))
        features &= ~kPopups;
    if ((features & kPopups) && (optional & kPopupFade)) {
        using namespace NativeUi::PopupTransition;
        windowForNative = reinterpret_cast<WindowForNative>(address(33));
        setType = reinterpret_cast<SetType>(address(34));
        setDuration = reinterpret_cast<SetDuration>(address(35));
        hook(32, AnimateHook, &original);
    }
    if (features & kSuggestions) {
        using namespace NativeUi::Omnibox;
        getBounds = reinterpret_cast<Bounds>(address(22));
        getHeader = reinterpret_cast<HeaderHeight>(address(23));
        solidVtable = address(24);
        getScreenBounds = reinterpret_cast<Bounds>(address(28));
        cleanupMessage = RegisterWindowMessageW(L"BraveAcrylic.OmniboxCleanup.3.9");
        if (!cleanupMessage || !hook(5, BackgroundHook, &originalBackground) ||
            !hook(18, ConstructorHook, &originalConstructor) ||
            !hook(19, DestructorHook, &originalDestructor) ||
            !hook(20, RoundedHook, &originalRounded) || !hook(21, SolidHook, &originalSolid) ||
            !hook(29, BeforeWidgetHook, &originalBeforeWidget))
            features &= ~kSuggestions;
    }
    NativeUi::supported = features;
    NativeUi::enabled = s_requestedUi.load();
    // Start the settings listener before the first popup, without waiting on
    // Brave's UI/loader thread. It receives setting changes even while idle.
    if (features & s_requestedUi.load())
        NativeUi::Material::Start();
    s_availableAreas = features & windowFeatures;
    s_background.areas.fetch_and(features & windowFeatures);
    const wchar_t *labels[] = {L"Vertical tabs", L"Toolbar", L"Webpage background",
                               L"Menus",         L"Popups",  L"Search suggestions",
                               L"Rounded webpage backing", L"Address bar"};
    for (unsigned i = 0; i < ARRAYSIZE(labels); ++i)
        Wh_Log(L"Seamless Chromium Browsers %s: %s %s", WH_MOD_VERSION, labels[i],
               (features & (1u << i)) ? L"available" : L"unavailable; left native");
}

static constexpr DWORD kBraveSymbolStartupWaitMs = 5000;
static CONDITION_VARIABLE s_symbolLookupChanged = CONDITION_VARIABLE_INIT;
static HANDLE s_symbolWorker = nullptr;
struct SymbolLookup {
    HMODULE module;
    bool useOnlineCache;
    bool finished;
    bool succeeded;
    ULONGLONG completedAt;
    size_t rva[kFeatureSlots];
};
static SymbolLookup s_symbolLookup{};

struct SymbolNotification {
    HANDLE resolver;
    HANDLE stop;
    HANDLE thread;
};
static SymbolNotification s_symbolNotification{};

static DWORD WaitForSymbolNotification(const HANDLE *handles, DWORD count) {
    for (;;) {
        DWORD result = MsgWaitForMultipleObjectsEx(count, handles, INFINITE, QS_ALLINPUT,
                                                   MWMO_INPUTAVAILABLE);
        if (result != WAIT_OBJECT_0 + count)
            return result;
        MSG message{};
        while (PeekMessageW(&message, nullptr, 0, 0, PM_REMOVE)) {
            if (message.message == WM_QUIT)
                return WAIT_FAILED;
            TranslateMessage(&message);
            DispatchMessageW(&message);
        }
    }
}

static void ShowSymbolNotification(NOTIFYICONDATAW &icon, PCWSTR status, PCWSTR message,
                                   DWORD kind) {
    icon.uFlags = NIF_TIP | NIF_SHOWTIP | NIF_INFO;
    icon.dwInfoFlags = kind | NIIF_NOSOUND | NIIF_RESPECT_QUIET_TIME;
    lstrcpynW(icon.szTip, status, ARRAYSIZE(icon.szTip));
    lstrcpynW(icon.szInfoTitle, L"Seamless Chromium Browsers", ARRAYSIZE(icon.szInfoTitle));
    lstrcpynW(icon.szInfo, message, ARRAYSIZE(icon.szInfo));
    if (!Shell_NotifyIconW(NIM_MODIFY, &icon))
        Wh_Log(L"Could not show the Seamless Chromium Browsers symbol notification");
}

// The shared tray icon: the glyph in the accent gradient on a clear background.
static HICON MakeTrayIcon_Big(bool off) {
    int size = GetSystemMetricsForDpi(SM_CXICON, GetDpiForSystem()) * 4;
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
    WCHAR g[2] = {(WCHAR)0xE774, 0};
    DrawTextW(dc, g, 1, &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE | DT_NOPREFIX);
    GdiFlush();
    SelectObject(dc, oldFont);
    DeleteObject(font);
    SelectObject(dc, old);
    DeleteDC(dc);

    const float c0[3] = {off ? 0x6C / 255.f : 0x89 / 255.f, off ? 0x70 / 255.f : 0xB4 / 255.f, off ? 0x86 / 255.f : 0xFA / 255.f};
    const float c1[3] = {off ? 0x58 / 255.f : 0xCB / 255.f, off ? 0x5B / 255.f : 0xA6 / 255.f, off ? 0x70 / 255.f : 0xF7 / 255.f};
    uint32_t* px = (uint32_t*)bits;
    const uint32_t* gp = (const uint32_t*)glyphBits;
    for (int y = 0; y < size; y++)
        for (int x = 0; x < size; x++) {
            float t = std::clamp((x + y) / (2.0f * (size - 1)), 0.0f, 1.0f);
            float cov = ((gp[y * size + x] >> 8) & 0xFF) / 255.0f;
            float rgb[3];
            for (int i = 0; i < 3; i++) {
                float base = c0[i] + (c1[i] - c0[i]) * t;
                rgb[i] = base * cov;
            }
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

// Drawn at 4x and shrunk, so the icon is smooth at the size it is shown.
static HICON MakeTrayIcon(bool off) { return Crisp_ShrinkIcon(MakeTrayIcon_Big(off), 4); }

static DWORD WINAPI RunSymbolNotifications(void *parameter) {
    const auto &notification = *static_cast<SymbolNotification *>(parameter);
    const HANDLE handles[] = {notification.stop, notification.resolver};
    if (WaitForSingleObject(handles[0], 0) == WAIT_OBJECT_0)
        return 0;
    HWND window = CreateWindowExW(0, L"STATIC", L"", WS_OVERLAPPED, 0, 0, 0, 0, nullptr,
                                  nullptr, nullptr, nullptr);
    if (!window)
        return 0;

    NOTIFYICONDATAW icon{};
    icon.cbSize = sizeof(icon);
    icon.hWnd = window;
    icon.uID = 1;
    icon.uFlags = NIF_ICON | NIF_TIP | NIF_SHOWTIP;
    HICON trayIcon = MakeTrayIcon(false);
    icon.hIcon = trayIcon ? trayIcon : LoadIcon(nullptr, IDI_INFORMATION);
    lstrcpynW(icon.szTip, L"Seamless Chromium Browsers: preparing symbols", ARRAYSIZE(icon.szTip));
    if (Shell_NotifyIconW(NIM_ADD, &icon)) {
        icon.uVersion = NOTIFYICON_VERSION_4;
        Shell_NotifyIconW(NIM_SETVERSION, &icon);
        if (WaitForSingleObject(handles[1], 0) == WAIT_TIMEOUT &&
            WaitForSingleObject(handles[0], 0) == WAIT_TIMEOUT) {
            ShowSymbolNotification(icon, L"Seamless Chromium Browsers: preparing symbols",
                                   L"Windhawk is preparing Brave symbols in the background. "
                                   L"You can keep using Brave.", NIIF_INFO);
        }

        if (WaitForSymbolNotification(handles, ARRAYSIZE(handles)) == WAIT_OBJECT_0 + 1) {
            AcquireSRWLockShared(&s_initLock);
            const bool stopping = s_stopping;
            const bool ready = s_symbolLookup.succeeded && CompleteFeatures(s_symbolLookup.rva);
            ReleaseSRWLockShared(&s_initLock);
            if (!stopping) {
                if (ready) {
                    ShowSymbolNotification(icon, L"Seamless Chromium Browsers: restart Brave",
                                           L"Brave symbols are ready. Restart Brave to apply "
                                           L"the available acrylic effects.", NIIF_INFO);
                } else {
                    ShowSymbolNotification(icon, L"Seamless Chromium Browsers: symbols unavailable",
                                           L"Windhawk could not prepare compatible Brave symbols. "
                                           L"See the mod log for details.", NIIF_WARNING);
                }
                // Keep the final tooltip available if Windows muted the banner.
                WaitForSymbolNotification(handles, 1);
            }
        }
        Shell_NotifyIconW(NIM_DELETE, &icon);
    } else {
        Wh_Log(L"Could not add the Seamless Chromium Browsers symbol status icon");
    }
    DestroyWindow(window);
    if (trayIcon) DestroyIcon(trayIcon);
    return 0;
}

// Called under s_initLock, only after the startup budget expires.
static void StartSymbolNotifications() {
    s_symbolNotification.resolver = s_symbolWorker;
    s_symbolNotification.stop = CreateEventW(nullptr, TRUE, FALSE, nullptr);
    if (!s_symbolNotification.stop)
        return;
    s_symbolNotification.thread =
        CreateThread(nullptr, 0, RunSymbolNotifications, &s_symbolNotification, 0, nullptr);
    if (!s_symbolNotification.thread) {
        CloseHandle(s_symbolNotification.stop);
        s_symbolNotification = {};
    }
}

static DWORD WINAPI ResolveBraveSymbolsOnWorker(void *) {
    size_t rva[kFeatureSlots]{};
    HMODULE retainedModule = nullptr;
    const HMODULE module = s_symbolLookup.module;
    bool succeeded = GetModuleHandleExW(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS,
                                       reinterpret_cast<LPCWSTR>(module), &retainedModule) &&
                     ResolveFeatureAddresses(module, rva, s_symbolLookup.useOnlineCache, true);
    if (retainedModule)
        FreeLibrary(retainedModule);

    // Publish data only. After a timeout this lookup merely fills Windhawk's
    // cache for the next launch, even if all addresses are valid.
    AcquireSRWLockExclusive(&s_initLock);
    std::copy_n(rva, kFeatureSlots, s_symbolLookup.rva);
    s_symbolLookup.succeeded = succeeded;
    s_symbolLookup.finished = true;
    s_symbolLookup.completedAt = GetTickCount64();
    WakeAllConditionVariable(&s_symbolLookupChanged);
    ReleaseSRWLockExclusive(&s_initLock);
    return 0;
}

// Called with s_initLock held. Waiting releases it so disabling the mod can
// close the activation gate before waiting for the uncancellable resolver.
static bool ResolveBraveSymbolsWithStartupBudget(HMODULE module, size_t *rva,
                                                bool useOnlineCache) {
    const ULONGLONG deadline = GetTickCount64() + kBraveSymbolStartupWaitMs;
    s_symbolLookup.module = module;
    s_symbolLookup.useOnlineCache = useOnlineCache;
    s_symbolWorker = CreateThread(nullptr, 0, ResolveBraveSymbolsOnWorker, nullptr, 0, nullptr);
    if (!s_symbolWorker) {
        Wh_Log(L"Could not start Brave symbol lookup; leaving Brave unmodified");
        return false;
    }

    while (!s_symbolLookup.finished && !s_stopping) {
        const ULONGLONG now = GetTickCount64();
        if (now >= deadline ||
            !SleepConditionVariableSRW(&s_symbolLookupChanged, &s_initLock,
                                       static_cast<DWORD>(deadline - now), 0)) {
            break;
        }
    }
    if (s_stopping)
        return false;
    if (!s_symbolLookup.finished || s_symbolLookup.completedAt > deadline) {
        Wh_Log(L"Brave continued without acrylic while symbols finish loading; restart afterward");
        StartSymbolNotifications();
        return false;
    }
    if (!s_symbolLookup.succeeded)
        return false;
    std::copy_n(s_symbolLookup.rva, kFeatureSlots, rva);
    return true;
}

// Installation and shutdown share a barrier. No hook can be registered/applied
// after Wh_ModBeforeUninit returns, including a loader call that finishes late.
static bool TryInstallChromeHooks(HMODULE module, bool applyNow) {
    if (!module || s_chromeAttempted.exchange(true, std::memory_order_acq_rel))
        return false;
    AcquireSRWLockExclusive(&s_initLock);
    bool installed = false;
    size_t rva[kFeatureSlots]{};
    const bool useOnlineCache = s_useOnlineSymbolCache.load();
    const bool allowFallback = s_allowBraveSymbolServerFallback.load();
    const bool resolved = !s_stopping &&
        (allowFallback ? ResolveBraveSymbolsWithStartupBudget(module, rva, useOnlineCache)
                       : ResolveFeatureAddresses(module, rva, useOnlineCache, false));
    if (resolved && !s_stopping) {
        InstallNativeBackgroundHooks(module, rva);
        if (applyNow) {
            installed = Wh_ApplyHookOperations() != FALSE;
            s_transparencyReady.store(installed && HasCompleteTransparencyPath(),
                                      std::memory_order_release);
            NativeUi::ready.store(installed, std::memory_order_release);
            if (!installed)
                Wh_Log(L"Could not activate paint hooks; transparency stays off");
        } else {
            // Windhawk applies these hooks after Wh_ModInit returns.
            s_activateAfterInit = true;
            installed = true;
        }
    }
    ReleaseSRWLockExclusive(&s_initLock);
    if (applyNow && installed)
        SyncNativeCaptions();
    return installed;
}

static bool IsExecutableLibraryLoad(DWORD flags) {
    return !(flags & (DONT_RESOLVE_DLL_REFERENCES | LOAD_LIBRARY_AS_DATAFILE |
                      LOAD_LIBRARY_AS_DATAFILE_EXCLUSIVE | LOAD_LIBRARY_AS_IMAGE_RESOURCE));
}

static HMODULE WINAPI LoadLibraryExW_Hook(LPCWSTR name, HANDLE file, DWORD flags) {
    const HMODULE module = pOrigLoadLibraryExW(name, file, flags);
    const DWORD error = GetLastError();
    if (!s_chromeAttempted.load(std::memory_order_acquire) && module &&
        IsExecutableLibraryLoad(flags) && module == GetModuleHandleW(L"chrome.dll")) {
        // Chrome's caller cannot use the new module until this hook returns.
        TryInstallChromeHooks(module, true);
    }
    SetLastError(error);
    return module;
}

enum class ProcessRole { Browser, Gpu, Other };

static ProcessRole GetProcessRole() {
    int count = 0;
    auto *arguments = CommandLineToArgvW(GetCommandLineW(), &count);
    if (!arguments)
        return ProcessRole::Other;
    ProcessRole role = ProcessRole::Browser;
    for (int i = 1; i < count; ++i) {
        if (!wcscmp(arguments[i], L"--") || !wcscmp(arguments[i], L"--single-argument"))
            break;
        if (!wcsncmp(arguments[i], L"--type=", 7)) {
            role =
                !wcscmp(arguments[i] + 7, L"gpu-process") ? ProcessRole::Gpu : ProcessRole::Other;
        }
    }
    LocalFree(arguments);
    return role;
}

BOOL ModInit() {
    const auto role = GetProcessRole();
    if (role != ProcessRole::Browser)
        return FALSE;
    s_isBrowserProcess = true;
    NativeUi::RefreshTransparencyAllowed();
    LoadModSettings();
    InstallNativeCaptionHooks();

    HMODULE chrome = GetModuleHandleW(L"chrome.dll");
    if (chrome) {
        // The opt-in PDB lookup belongs to AfterInit when chrome.dll is
        // already loaded. Do not hold Windhawk's initialization on it.
        return s_allowBraveSymbolServerFallback.load() || TryInstallChromeHooks(chrome, false);
    }

    const HMODULE kernelBase = GetModuleHandleW(L"kernelbase.dll");
    const auto loader =
        kernelBase
            ? reinterpret_cast<LoadLibraryExW_t>(GetProcAddress(kernelBase, "LoadLibraryExW"))
            : nullptr;
    if (!loader ||
        !WindhawkUtils::SetFunctionHook(loader, LoadLibraryExW_Hook, &pOrigLoadLibraryExW)) {
        return FALSE;
    }
    return TRUE;
}

void ModAfterInit() {
    if (!s_isBrowserProcess)
        return;
    AcquireSRWLockExclusive(&s_initLock);
    if (!s_stopping && s_activateAfterInit) {
        s_activateAfterInit = false;
        s_transparencyReady.store(HasCompleteTransparencyPath(), std::memory_order_release);
        NativeUi::ready.store(true, std::memory_order_release);
    }
    ReleaseSRWLockExclusive(&s_initLock);
    // Cover a load between ModInit's check and activation of the loader hook.
    if (const auto chrome = GetModuleHandleW(L"chrome.dll"))
        TryInstallChromeHooks(chrome, true);
    SyncNativeCaptions();
}

void ModSettingsChanged() {
    if (!s_isBrowserProcess)
        return;
    LoadModSettings();
    SyncNativeCaptions();
    Wh_Log(L"Settings updated; restart Brave normally to rebuild its cached UI brushes");
}

void ModBeforeUninit() {
    s_captionStopping.store(true, std::memory_order_release);
    s_captionFixActive.store(false, std::memory_order_release);
    AcquireSRWLockExclusive(&s_initLock);
    s_stopping = true;
    s_activateAfterInit = false;
    s_transparencyReady.store(false, std::memory_order_release);
    const HANDLE symbolWorker = s_symbolWorker;
    s_symbolWorker = nullptr;
    if (s_symbolNotification.stop)
        SetEvent(s_symbolNotification.stop);
    WakeAllConditionVariable(&s_symbolLookupChanged);
    ReleaseSRWLockExclusive(&s_initLock);
    NativeUi::Stop();
    // Restore the real WS_SYSMENU bit while the getter/setter hooks are still
    // installed, so Chromium cannot save a stripped style during teardown.
    if (s_isBrowserProcess)
        EnumWindows(SyncNativeCaptionWindow, 0);
    if (s_symbolNotification.thread) {
        WaitForSingleObject(s_symbolNotification.thread, INFINITE);
        CloseHandle(s_symbolNotification.thread);
        CloseHandle(s_symbolNotification.stop);
        s_symbolNotification = {};
    }
    // Windhawk's symbol lookup cannot be cancelled. The worker must return
    // before this mod's DLL can be unloaded.
    if (symbolWorker) {
        WaitForSingleObject(symbolWorker, INFINITE);
        CloseHandle(symbolWorker);
    }
}


}  // namespace BraveEngine


// ---------------------------------------------------------------------------
// Which engine runs where. Helium installs are named chrome.exe, so the path
// decides. The shared layer runs only in each browser's main process.
// ---------------------------------------------------------------------------
static bool g_heliumOn = false;
static bool g_braveOn = false;
static bool g_commonOn = false;

static bool ExePathHas(PCWSTR part) {
    wchar_t exe[MAX_PATH];
    if (!GetModuleFileNameW(nullptr, exe, MAX_PATH)) return false;
    CharLowerW(exe);
    return wcsstr(exe, part) != nullptr;
}

static bool IsMainBrowserProcess() {
    PCWSTR cmd = GetCommandLineW();
    return cmd && !wcsstr(cmd, L"--type=");
}

BOOL Wh_ModInit() {
    if (ExePathHas(L"helium")) {
        if (!HeliumEngine::ModInit()) return FALSE;
        g_heliumOn = true;
    } else if (ExePathHas(L"\\brave.exe")) {
        // If Brave's part cannot start, nothing of this mod runs in Brave, so
        // its window hooks never go live alone.
        if (!BraveEngine::ModInit()) return FALSE;
        g_braveOn = true;
    }
    if (IsMainBrowserProcess()) {
        Common::Init();
        g_commonOn = true;
    }
    return g_heliumOn || g_braveOn || g_commonOn;
}

void Wh_ModAfterInit() {
    if (g_braveOn) BraveEngine::ModAfterInit();
}

void Wh_ModSettingsChanged() {
    if (g_heliumOn) HeliumEngine::ModSettingsChanged();
    if (g_braveOn) BraveEngine::ModSettingsChanged();
    if (g_commonOn) Common::SettingsChanged();
}

void Wh_ModBeforeUninit() {
    if (g_braveOn) BraveEngine::ModBeforeUninit();
    if (g_commonOn) Common::Stop();
}

void Wh_ModUninit() {
    if (g_heliumOn) HeliumEngine::ModUninit();
}
