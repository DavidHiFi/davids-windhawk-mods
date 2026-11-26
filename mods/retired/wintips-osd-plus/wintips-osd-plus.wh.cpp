// ==WindhawkMod==
// @id              wintips-osd-plus
// @name            WinTips OSD Plus
// @description     Pop-up cards for Caps, Num and Scroll Lock, Insert, copy, paste and cut, with a Catppuccin Mocha look
// @version         1.4.1
// @author          DavidHiFi, DoYouNatureQ
// @github          https://github.com/DavidHiFi
// @homepage        https://github.com/DavidHiFi/davids-windhawk-mods
// @donateUrl       https://ko-fi.com/DavidHiFi
// @license         MIT
// @include         windhawk.exe
// @compilerOptions -lgdiplus -lgdi32 -ladvapi32 -lshell32 -lshcore -ldwmapi -ld2d1 -ldwrite -ld3d11 -ldcomp
// ==/WindhawkMod==

// ==WindhawkModReadme==
/*
# WinTips OSD Plus

A small card slides in whenever you toggle Caps Lock, Num Lock or Scroll Lock,
press Insert, or copy, paste and cut. This version dresses the card in
Catppuccin Mocha, with a blue and mauve border that slowly shifts colour.

![WinTips OSD Plus preview](https://raw.githubusercontent.com/DavidHiFi/davids-windhawk-mods/main/media/previews/wintips-osd-plus.png)

## Features

- **Mocha look.** Dark Mocha card, Mocha text and a blue accent. Switch the
  palette to Windows to follow your system theme instead.
- **Drawn on the GPU.** The card is composited with DirectComposition, and its
  fade and slide run on the Windows compositor instead of repainting every
  frame. If the GPU path cannot start, the mod switches back to the classic
  renderer on its own, and you can pick the renderer in settings.
- **Morphing border.** The border blends blue into mauve and keeps flowing.
  Pick the colours, the width, the speed, or turn it into a plain line.
- **Soft glow.** A soft glow on the border line, from off to strong.
- **Your shape and strength.** Corner roundness and how see-through the card is.
- **Real blur.** The card blurs whatever is behind it, or you can make it solid.
- **Clipboard counter.** Copy, paste and cut show a check or scissors with a
  count when you repeat them.
- **Stays out of the way.** Click-through, never takes focus, fades on its own.

## Notes

- It runs on its own as a Windhawk tool mod and never loads into other programs.
- The Renderer setting picks GPU (DirectComposition, the default) or the legacy
  GDI painter. If DirectComposition cannot start, the card falls back to GDI
  for the session and a log line says which renderer armed.
- If the standalone WinTips app is already running, this mod stays quiet.
- Behind an administrator window the blur can come out black, so the card turns
  solid for that tip.
- Insert has no on or off state in Windows, so it only reacts when pressed.

## Credits

Based on [WinTips](https://github.com/DoYouNatureQ/WinTips) by DoYouNatureQ.
MIT license.
*/
// ==/WindhawkModReadme==

// ==WindhawkModSettings==
/*
- notifyCapsLock: true
  $name: Caps Lock
  $description: Show a card when Caps Lock is toggled.
- notifyNumLock: true
  $name: Num Lock
  $description: Show a card when Num Lock is toggled.
- notifyScrollLock: true
  $name: Scroll Lock
  $description: Show a card when Scroll Lock is toggled.
- notifyInsert: true
  $name: Insert
  $description: Show a card when Insert is pressed.
- notifyCopy: true
  $name: Copy
  $description: Show a card when you copy with Ctrl+C.
- notifyPaste: true
  $name: Paste
  $description: Show a card when you paste with Ctrl+V.
- notifyCut: true
  $name: Cut
  $description: Show a card when you cut with Ctrl+X.
- notifyAnyCopy: true
  $name: Also show for other copies
  $description: >-
    Also show the Copy card for right-click copies and Copy buttons inside apps.
    Needs the Copy option above.
- vertical: bottom
  $name: Vertical position
  $options:
  - bottom: Above the taskbar
  - top: Below the top edge
- horizontal: center
  $name: Horizontal position
  $options:
  - left: Left
  - center: Center
  - right: Right
- monitor: cursor
  $name: Show on
  $description: >-
    The card can follow the mouse to whichever screen you are using, or always
    use the main screen.
  $options:
  - cursor: The screen with the mouse
  - primary: The main screen
- offsetX: 0
  $name: Horizontal offset
  $description: "-4000 to 4000 pixels (Suggested: 0). Positive moves the card right."
- offsetY: 0
  $name: Vertical offset
  $description: "-4000 to 4000 pixels (Suggested: 0). Positive moves the card down."
- palette: mocha
  $name: Colour palette
  $description: Mocha uses the Catppuccin Mocha colours. Windows follows your system theme.
  $options:
  - mocha: Catppuccin Mocha
  - windows: Follow Windows
- theme: system
  $name: Light or dark
  $description: Only used by the Windows palette. Mocha is always dark.
  $options:
  - system: Follow Windows
  - dark: Dark
  - light: Light
- accentColor: "#89B4FA"
  $name: Accent colour
  $description: >-
    Hex colour such as #89B4FA (Mocha blue, suggested). It starts the border
    gradient and colours the bar and the count badge. Leave empty for the
    Windows accent colour.
- accentColor2: "#CBA6F7"
  $name: Second border colour
  $description: >-
    Hex colour the border blends into (Suggested: #CBA6F7, Mocha mauve). Leave
    empty to use only the accent colour.
- fontFamily: "FiraCode Nerd Font"
  $name: Font
  $description: Enter the name of an installed font.
- fontWeight: medium
  $name: Font weight
  $description: Choose how thick the notification text looks.
  $options:
  - light: Light
  - regular: Regular
  - medium: Medium
  - semibold: Semibold
  - bold: Bold
- textColor: ""
  $name: Text colour
  $description: Hex colour such as #CDD6F4. Leave empty to use the palette's text colour.
- material: acrylic
  $name: Card material
  $description: Acrylic blurs whatever is behind the card. Solid paints an opaque card.
  $options:
  - acrylic: Acrylic (blurred background)
  - solid: Solid colour
- blurRadius: 12
  $name: Blur strength
  $description: "0 to 40 pixels (Suggested: 12). Only used by acrylic."
- surfaceOpacity: 88
  $name: Card opacity
  $description: "30 to 100 percent (Suggested: 88). Lower shows more of the blurred background."
- cornerRadius: 12
  $name: Corner roundness
  $description: "0 to 24 pixels (Suggested: 12)."
- borderStyle: gradient
  $name: Border
  $options:
  - gradient: Morphing gradient
  - solid: Plain line in the accent colour
  - none: No border
- borderWidth: 2
  $name: Border width
  $description: "1 to 4 pixels (Suggested: 2)."
- morphSeconds: 5
  $name: Border morph time
  $description: >-
    0 to 30 seconds for one full colour cycle (Suggested: 5). 0 keeps the
    gradient still. Smaller is faster.
- glow: 35
  $name: Border glow
  $description: "0 to 100 (Suggested: 35). 0 turns the glow off."
- displayMs: 2000
  $name: How long it stays
  $description: "500 to 10000 milliseconds (Suggested: 2000)."
- animationPercent: 100
  $name: Animation speed
  $description: >-
    0 to 300 (Suggested: 100). A card animates for 300 ms times this percent, so
    50 is twice as fast and 200 twice as slow. 0 turns animation off.
- pollElevated: true
  $name: Catch toggles in administrator windows
  $description: >-
    The keyboard hook cannot see keys sent to administrator windows. When on,
    the lock keys are checked every 250 ms to cover that.
- suppressFullscreen: false
  $name: Hide while a fullscreen app is open
  $description: Skips cards during games, fullscreen video and presentations.
- renderer: gpu
  $name: Renderer
  $description: >-
    GPU composites the card with DirectComposition and animates fades and
    slides on the compositor (Suggested: GPU). GDI is the legacy per-frame
    painter, kept for troubleshooting. If the GPU path cannot start, the card
    falls back to GDI by itself.
  $options:
  - gpu: GPU (DirectComposition)
  - gdi: GDI (legacy)
*/
// ==/WindhawkModSettings==

#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <shellapi.h>
#include <shellscalingapi.h>
#include <dwmapi.h>

#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cwchar>
#include <cwctype>
#include <string>
#include <vector>

#ifdef __MINGW32__
#include <algorithm>
using std::max;
using std::min;
#endif

#include <objidl.h>
#include <gdiplus.h>

#include <d2d1_1.h>
#include <d2d1helper.h>
#include <dwrite_3.h>
#include <d3d11.h>
#include <dxgi.h>
#include <dcomp.h>
#include <dcompanimation.h>

using namespace Gdiplus;

// =============================================================================
// Constants and types
// =============================================================================

namespace {

// Design units are DIPs (96 DPI); everything is scaled to physical pixels by
// the DPI of the monitor the card is about to appear on.
constexpr float kBaseWidth = 160.0f;
constexpr float kBaseHeight = 50.0f;
constexpr float kGap = 16.0f;         // distance to the taskbar / work area
constexpr float kSlideDistance = 20.0f;
constexpr float kZoneRatio = 0.15f;   // edge zone that picks the slide direction
constexpr int kBaseAnimationMs = 300;
constexpr int kClipIntentMs = 800;    // wait this long for the clipboard to change
constexpr int kClipMergeMs = 250;     // coalesce clipboard manager write-backs
constexpr int kPollQuietMs = 1200;    // let a hook-reported toggle settle first
constexpr int kPollMs = 250;          // elevated-window fallback

enum TipKind {
    kCapsLock = 0,
    kNumLock,
    kScrollLock,
    kInsert,
    kCopy,
    kPaste,
    kCut,
    kKindCount,
};

constexpr UINT WM_APP_TIP = WM_APP + 1;
constexpr UINT WM_APP_QUIT = WM_APP + 2;

constexpr UINT_PTR kTimerAnim = 1;
constexpr UINT_PTR kTimerHold = 2;
constexpr UINT_PTR kTimerPoll = 4;

// =============================================================================
// Settings
// =============================================================================

enum Material {
    kMaterialAcrylic = 0,
    kMaterialSolid = 1,
};

enum MonitorMode {
    kMonitorCursor = 0,  // the display the pointer is on
    kMonitorPrimary = 1, // always the main display
};

struct Settings {
    bool notify[kKindCount] = {true, true, true, true, true, true, true};
    bool notifyAnyCopy = true;
    int displayMs = 2000;
    int animationPercent = 100;
    int vertical = 1;   // 0 = top, 1 = bottom
    int horizontal = 1; // 0 = left, 1 = center, 2 = right
    int offsetX = 0;
    int offsetY = 0;
    int monitor = kMonitorCursor;
    int theme = 0;      // 0 = system, 1 = dark, 2 = light
    int material = kMaterialAcrylic;
    int blurRadius = 12;
    std::wstring accentColor;
    std::wstring accentColor2;
    std::wstring textColor;
    std::wstring fontFamily;
    int fontWeight = 500;
    int palette = 0;          // 0 = Catppuccin Mocha, 1 = follow Windows
    int surfaceOpacity = 88;  // percent
    int cornerRadius = 12;    // DIP
    int borderStyle = 0;      // 0 = gradient, 1 = solid, 2 = none
    int borderWidth = 2;      // DIP
    int morphSeconds = 5;     // 0 = still
    int glow = 35;            // 0 to 100
    int renderer = 0;         // 0 = GPU (DirectComposition), 1 = GDI legacy
    bool pollElevated = true;
    bool suppressFullscreen = false;

    int AnimationMs() const {
        if (animationPercent <= 0) {
            return 0;
        }
        return kBaseAnimationMs * animationPercent / 100;
    }
};

Settings g_settings;

bool EqualsNoCase(const std::wstring& a, const wchar_t* b) {
    return _wcsicmp(a.c_str(), b) == 0;
}

int Clamp(int v, int lo, int hi) {
    return v < lo ? lo : (v > hi ? hi : v);
}

void LoadSettings() {
    Settings s;

    s.notify[kCapsLock] = Wh_GetIntSetting(L"notifyCapsLock") != 0;
    s.notify[kNumLock] = Wh_GetIntSetting(L"notifyNumLock") != 0;
    s.notify[kScrollLock] = Wh_GetIntSetting(L"notifyScrollLock") != 0;
    s.notify[kInsert] = Wh_GetIntSetting(L"notifyInsert") != 0;
    s.notify[kCopy] = Wh_GetIntSetting(L"notifyCopy") != 0;
    s.notify[kPaste] = Wh_GetIntSetting(L"notifyPaste") != 0;
    s.notify[kCut] = Wh_GetIntSetting(L"notifyCut") != 0;
    s.notifyAnyCopy = Wh_GetIntSetting(L"notifyAnyCopy") != 0;

    s.displayMs = Clamp(Wh_GetIntSetting(L"displayMs"), 500, 10000);
    s.animationPercent = Clamp(Wh_GetIntSetting(L"animationPercent"), 0, 300);
    s.offsetX = Clamp(Wh_GetIntSetting(L"offsetX"), -4000, 4000);
    s.offsetY = Clamp(Wh_GetIntSetting(L"offsetY"), -4000, 4000);
    s.pollElevated = Wh_GetIntSetting(L"pollElevated") != 0;
    s.suppressFullscreen = Wh_GetIntSetting(L"suppressFullscreen") != 0;

    const wchar_t* str = Wh_GetStringSetting(L"vertical");
    s.vertical = (str && EqualsNoCase(str, L"top")) ? 0 : 1;
    Wh_FreeStringSetting(str);

    str = Wh_GetStringSetting(L"horizontal");
    if (str && EqualsNoCase(str, L"left")) {
        s.horizontal = 0;
    } else if (str && EqualsNoCase(str, L"right")) {
        s.horizontal = 2;
    } else {
        s.horizontal = 1;
    }
    Wh_FreeStringSetting(str);

    str = Wh_GetStringSetting(L"theme");
    if (str && EqualsNoCase(str, L"dark")) {
        s.theme = 1;
    } else if (str && EqualsNoCase(str, L"light")) {
        s.theme = 2;
    } else {
        s.theme = 0;
    }
    Wh_FreeStringSetting(str);

    str = Wh_GetStringSetting(L"monitor");
    s.monitor = (str && EqualsNoCase(str, L"primary")) ? kMonitorPrimary
                                                       : kMonitorCursor;
    Wh_FreeStringSetting(str);

    str = Wh_GetStringSetting(L"accentColor");
    s.accentColor = str ? str : L"";
    Wh_FreeStringSetting(str);

    str = Wh_GetStringSetting(L"material");
    s.material = (str && EqualsNoCase(str, L"solid")) ? kMaterialSolid
                                                      : kMaterialAcrylic;
    Wh_FreeStringSetting(str);

    int blur = Wh_GetIntSetting(L"blurRadius");
    s.blurRadius = Clamp(blur, 0, 40);

    str = Wh_GetStringSetting(L"accentColor2");
    s.accentColor2 = str ? str : L"";
    Wh_FreeStringSetting(str);

    str = Wh_GetStringSetting(L"fontFamily");
    s.fontFamily = (str && *str) ? str : L"FiraCode Nerd Font";
    Wh_FreeStringSetting(str);

    str = Wh_GetStringSetting(L"fontWeight");
    if (str && EqualsNoCase(str, L"light")) s.fontWeight = 300;
    else if (str && EqualsNoCase(str, L"regular")) s.fontWeight = 400;
    else if (str && EqualsNoCase(str, L"semibold")) s.fontWeight = 600;
    else if (str && EqualsNoCase(str, L"bold")) s.fontWeight = 700;
    Wh_FreeStringSetting(str);

    str = Wh_GetStringSetting(L"textColor");
    s.textColor = str ? str : L"";
    Wh_FreeStringSetting(str);

    str = Wh_GetStringSetting(L"palette");
    s.palette = (str && EqualsNoCase(str, L"windows")) ? 1 : 0;
    Wh_FreeStringSetting(str);

    str = Wh_GetStringSetting(L"borderStyle");
    if (str && EqualsNoCase(str, L"solid")) {
        s.borderStyle = 1;
    } else if (str && EqualsNoCase(str, L"none")) {
        s.borderStyle = 2;
    } else {
        s.borderStyle = 0;
    }
    Wh_FreeStringSetting(str);

    s.surfaceOpacity = Clamp(Wh_GetIntSetting(L"surfaceOpacity"), 30, 100);
    s.cornerRadius = Clamp(Wh_GetIntSetting(L"cornerRadius"), 0, 24);
    s.borderWidth = Clamp(Wh_GetIntSetting(L"borderWidth"), 1, 4);
    s.morphSeconds = Clamp(Wh_GetIntSetting(L"morphSeconds"), 0, 30);
    s.glow = Clamp(Wh_GetIntSetting(L"glow"), 0, 100);

    str = Wh_GetStringSetting(L"renderer");
    s.renderer = (str && EqualsNoCase(str, L"gdi")) ? 1 : 0;
    Wh_FreeStringSetting(str);

    g_settings = s;
}

// =============================================================================
// Localization
// =============================================================================

bool g_chinese = true;

void DetectLanguage() {
    LANGID lang = GetUserDefaultUILanguage();
    switch (PRIMARYLANGID(lang)) {
        case LANG_CHINESE:
            g_chinese = true;
            break;
        default:
            g_chinese = false;
            break;
    }
}

const wchar_t* KeyName(TipKind kind) {
    static const wchar_t* zh[] = {L"大写锁定", L"数字锁定", L"滚动锁定",
                                  L"Insert",   L"已复制",   L"已粘贴",
                                  L"已剪切"};
    static const wchar_t* en[] = {L"Caps Lock", L"Num Lock",  L"Scroll Lock",
                                  L"Insert",    L"Copied",    L"Pasted",
                                  L"Cut"};
    return g_chinese ? zh[kind] : en[kind];
}

void FormatTip(TipKind kind, bool on, std::wstring& out) {
    switch (kind) {
        case kCapsLock:
        case kNumLock:
        case kScrollLock:
            if (g_chinese) {
                out = std::wstring(KeyName(kind)) + (on ? L" 开启" : L" 关闭");
            } else {
                out = std::wstring(KeyName(kind)) + (on ? L" On" : L" Off");
            }
            break;
        case kInsert:
            out = g_chinese ? L"已按下 Insert" : L"Insert pressed";
            break;
        default:
            out = KeyName(kind);
            break;
    }
}

// =============================================================================
// Theme
// =============================================================================

struct Theme {
    bool dark;
    bool highContrast;
    Color surface;
    Color tint;  // overlay painted on top of the blurred backdrop
    Color text;
    Color accent;
    Color accent2;
    Color onAccent;
    Color border;
};

bool IsDarkTheme() {
    HKEY key;
    if (RegOpenKeyExW(HKEY_CURRENT_USER,
                      L"Software\\Microsoft\\Windows\\CurrentVersion\\Themes\\"
                      L"Personalize",
                      0, KEY_READ, &key) == ERROR_SUCCESS) {
        DWORD value = 1;
        DWORD size = sizeof(value);
        DWORD type = 0;
        LONG r = RegQueryValueExW(key, L"AppsUseLightTheme", nullptr, &type,
                                  (LPBYTE)&value, &size);
        RegCloseKey(key);
        if (r == ERROR_SUCCESS && type == REG_DWORD) {
            return value == 0;
        }
    }
    return false;
}

Color SystemAccent() {
    HKEY key;
    if (RegOpenKeyExW(HKEY_CURRENT_USER, L"Software\\Microsoft\\Windows\\DWM", 0,
                      KEY_READ, &key) == ERROR_SUCCESS) {
        DWORD value = 0;
        DWORD size = sizeof(value);
        DWORD type = 0;
        LONG r = RegQueryValueExW(key, L"AccentColor", nullptr, &type,
                                  (LPBYTE)&value, &size);
        RegCloseKey(key);
        if (r == ERROR_SUCCESS && type == REG_DWORD) {
            return Color(255, GetRValue(value), GetGValue(value),
                         GetBValue(value));
        }
    }
    return Color(255, 0x00, 0x67, 0xC0);
}

bool ParseHexColor(const std::wstring& text, Color& out) {
    if (text.size() != 7 || text[0] != L'#') {
        return false;
    }
    for (int i = 1; i < 7; i++) {
        if (!iswxdigit(text[i])) {
            return false;
        }
    }
    unsigned int r = wcstoul(text.substr(1, 2).c_str(), nullptr, 16);
    unsigned int g = wcstoul(text.substr(3, 2).c_str(), nullptr, 16);
    unsigned int b = wcstoul(text.substr(5, 2).c_str(), nullptr, 16);
    out = Color(255, (BYTE)r, (BYTE)g, (BYTE)b);
    return true;
}

Theme CurrentTheme() {
    Theme t{};
    HIGHCONTRAST hc{sizeof(HIGHCONTRAST)};
    t.highContrast =
        SystemParametersInfoW(SPI_GETHIGHCONTRAST, sizeof(hc), &hc, 0) &&
        (hc.dwFlags & HCF_HIGHCONTRASTON);
    t.dark = t.highContrast ? false
                            : (g_settings.theme == 1 ? true
                                                     : (g_settings.theme == 2
                                                            ? false
                                                            : IsDarkTheme()));

    if (t.highContrast) {
        t.surface = Color(255, GetRValue(GetSysColor(COLOR_WINDOW)),
                          GetGValue(GetSysColor(COLOR_WINDOW)),
                          GetBValue(GetSysColor(COLOR_WINDOW)));
        t.text = Color(255, GetRValue(GetSysColor(COLOR_WINDOWTEXT)),
                       GetGValue(GetSysColor(COLOR_WINDOWTEXT)),
                       GetBValue(GetSysColor(COLOR_WINDOWTEXT)));
        t.accent = Color(255, GetRValue(GetSysColor(COLOR_HIGHLIGHT)),
                         GetGValue(GetSysColor(COLOR_HIGHLIGHT)),
                         GetBValue(GetSysColor(COLOR_HIGHLIGHT)));
        t.onAccent = Color(255, GetRValue(GetSysColor(COLOR_HIGHLIGHTTEXT)),
                           GetGValue(GetSysColor(COLOR_HIGHLIGHTTEXT)),
                           GetBValue(GetSysColor(COLOR_HIGHLIGHTTEXT)));
        t.accent2 = t.accent;
        t.border = t.text;
        t.tint = t.surface;
        return t;
    }

    const BYTE tintAlpha =
        (BYTE)std::lround(255.0f * (float)g_settings.surfaceOpacity / 100.0f);

    if (g_settings.palette == 0) {
        // Catppuccin Mocha: base 1E1E2E, text CDD6F4, blue 89B4FA, mauve CBA6F7.
        t.dark = true;
        t.surface = Color(250, 0x1E, 0x1E, 0x2E);
        t.tint = Color(tintAlpha, 0x1E, 0x1E, 0x2E);
        t.text = Color(255, 0xCD, 0xD6, 0xF4);
        t.accent = Color(255, 0x89, 0xB4, 0xFA);
        t.onAccent = Color(255, 0x1E, 0x1E, 0x2E);
        t.border = Color(255, 0x58, 0x5B, 0x70);
    } else {
        t.surface = t.dark ? Color(250, 0x2B, 0x2B, 0x2B)
                           : Color(250, 0xFB, 0xFB, 0xFB);
        t.tint = t.dark ? Color(tintAlpha, 0x1F, 0x1F, 0x1F)
                        : Color(tintAlpha, 0xF2, 0xF2, 0xF2);
        t.text = t.dark ? Color(255, 0xFF, 0xFF, 0xFF)
                        : Color(255, 0x19, 0x19, 0x19);
        t.accent = SystemAccent();
        t.onAccent = Color(255, 255, 255, 255);
        t.border = t.dark ? Color(0x14, 0xFF, 0xFF, 0xFF)
                          : Color(0x1A, 0x00, 0x00, 0x00);
    }

    Color parsed;
    if (ParseHexColor(g_settings.accentColor, parsed)) {
        t.accent = parsed;
    }
    t.accent2 = t.accent;
    if (ParseHexColor(g_settings.accentColor2, parsed)) {
        t.accent2 = parsed;
    }
    if (ParseHexColor(g_settings.textColor, parsed)) {
        t.text = parsed;
    }
    return t;
}

// =============================================================================
// Small math helpers
// =============================================================================

float Clamp01(float v) {
    return v < 0.0f ? 0.0f : (v > 1.0f ? 1.0f : v);
}

float EaseOutCubic(float t) {
    t = Clamp01(t);
    float inv = 1.0f - t;
    return 1.0f - inv * inv * inv;
}

float EaseInCubic(float t) {
    t = Clamp01(t);
    return t * t * t;
}

float EaseOutQuad(float t) {
    t = Clamp01(t);
    return 1.0f - (1.0f - t) * (1.0f - t);
}

float EaseInOutCubic(float t) {
    t = Clamp01(t);
    if (t < 0.5f) {
        return 4.0f * t * t * t;
    }
    float f = (2.0f * t) - 2.0f;
    return 0.5f * f * f * f + 1.0f;
}

float Lerp(float a, float b, float t) {
    return a + (b - a) * t;
}

// =============================================================================
// Monitors and DPI
// =============================================================================

using SetThreadDpiAwarenessContext_t = DPI_AWARENESS_CONTEXT(WINAPI*)(DPI_AWARENESS_CONTEXT);
using GetDpiForMonitor_t = HRESULT(WINAPI*)(HMONITOR, MONITOR_DPI_TYPE, UINT*, UINT*);

float ScaleForMonitor(HMONITOR monitor) {
    if (!monitor) {
        return 1.0f;
    }
    HMODULE shcore = LoadLibraryW(L"shcore.dll");
    if (shcore) {
        float scale = 0.0f;
        auto getDpi = (GetDpiForMonitor_t)GetProcAddress(shcore, "GetDpiForMonitor");
        if (getDpi) {
            UINT dpiX = 0, dpiY = 0;
            if (SUCCEEDED(getDpi(monitor, MDT_EFFECTIVE_DPI, &dpiX, &dpiY)) &&
                dpiX > 0) {
                scale = (float)dpiX / 96.0f;
            }
        }
        FreeLibrary(shcore);
        if (scale > 0.0f) {
            return scale;
        }
    }
    HDC dc = GetDC(nullptr);
    int dpi = dc ? GetDeviceCaps(dc, LOGPIXELSX) : 96;
    if (dc) {
        ReleaseDC(nullptr, dc);
    }
    return dpi > 0 ? (float)dpi / 96.0f : 1.0f;
}

// The display the card is drawn on. Resolved once per tip so the card lands on
// the monitor the user is actually looking at, with that monitor's own scale.
struct MonitorTarget {
    HMONITOR handle = nullptr;
    RECT bounds{0, 0, 0, 0}; // whole monitor, in virtual-screen coordinates
    RECT work{0, 0, 0, 0};   // same, minus the taskbar
    float scale = 1.0f;
    bool valid = false;

    int Width() const {
        return (int)std::max<LONG>(1, bounds.right - bounds.left);
    }
    int Height() const {
        return (int)std::max<LONG>(1, bounds.bottom - bounds.top);
    }
};

MonitorTarget g_monitor;

bool LoadMonitor(HMONITOR handle, MonitorTarget& out) {
    MONITORINFO info{};
    info.cbSize = sizeof(info);
    if (!handle || !GetMonitorInfoW(handle, &info)) {
        return false;
    }
    out.handle = handle;
    out.bounds = info.rcMonitor;
    out.work = info.rcWork;
    out.scale = ScaleForMonitor(handle);
    out.valid = true;
    return true;
}

HMONITOR PickMonitor(int mode) {
    if (mode != kMonitorPrimary) {
        POINT cursor{};
        if (GetCursorPos(&cursor)) {
            HMONITOR monitor =
                MonitorFromPoint(cursor, MONITOR_DEFAULTTONEAREST);
            if (monitor) {
                return monitor;
            }
        }
    }
    return MonitorFromPoint(POINT{0, 0}, MONITOR_DEFAULTTOPRIMARY);
}

bool ResolveTargetMonitor() {
    MonitorTarget target;
    if (!LoadMonitor(PickMonitor(g_settings.monitor), target)) {
        return false;
    }
    g_monitor = target;
    return true;
}

// =============================================================================
// Placement (port of UI/OsdPlacement.cs, made monitor-aware)
// =============================================================================

struct Placement {
    int x;
    int y;
    float dx;  // slide-in offset, in physical pixels
    float dy;
};

enum PopSide { kPopNone, kPopLeft, kPopRight, kPopTop, kPopBottom };

PopSide ActiveSide(const MonitorTarget& mon, float left, float top, float w,
                   float h) {
    float screenW = (float)mon.Width();
    float screenH = (float)mon.Height();
    float centerX = left + w / 2.0f - (float)mon.bounds.left;
    float centerY = top + h / 2.0f - (float)mon.bounds.top;

    float zoneW = screenW * kZoneRatio;
    if (centerX < zoneW) {
        return kPopLeft;
    }
    if (centerX > screenW - zoneW) {
        return kPopRight;
    }
    float zoneH = screenH * kZoneRatio;
    if (centerY < zoneH) {
        return kPopTop;
    }
    if (centerY > screenH - zoneH) {
        return kPopBottom;
    }
    return kPopNone;
}

// Whether the card hangs off the top edge of its monitor. The accent bar then
// mirrors above the label, so it always sits on the edge the card is anchored
// to instead of being wedged between the text and the screen content. The
// split is the monitor's vertical middle — the same threshold the slide
// direction falls back to when the card sits away from every edge.
bool CardHangsTop(const MonitorTarget& mon, int x, int y, float w, float h) {
    // An unresolved monitor leaves bounds at zero, so fall back to the primary
    // screen height the settings were computed against.
    float height = mon.valid ? (float)mon.Height() : 0.0f;
    float originY = mon.valid ? (float)mon.bounds.top : 0.0f;
    if (height <= 1.0f) {
        height = (float)GetSystemMetrics(SM_CYSCREEN);
        originY = 0.0f;
    }
    float centerY = (float)y + h / 2.0f - originY;
    return centerY < height / 2.0f;
}

// Computes the card position for one monitor plus the slide offset that matches
// the nearest edge of that monitor. Kept free of globals so the standalone
// build can exercise it against made-up monitor layouts.
Placement ComputePlacement(const MonitorTarget& mon, int vertical, int horizontal,
                           int offsetX, int offsetY, float w, float h,
                           float scale) {
    float gap = kGap * scale;
    const RECT& bounds = mon.bounds;
    const RECT& work = mon.work;

    float left;
    if (horizontal == 0) {
        left = (float)work.left + gap;
    } else if (horizontal == 2) {
        left = (float)work.right - gap - w;
    } else {
        left = (float)bounds.left + ((float)mon.Width() - w) / 2.0f;
    }

    // rcWork already excludes the taskbar, wherever it happens to dock.
    float top = vertical == 0 ? (float)work.top + gap
                              : (float)work.bottom - gap - h;

    left += (float)offsetX;
    top += (float)offsetY;

    float maxLeft = std::max((float)bounds.left, (float)bounds.right - w);
    float maxTop = std::max((float)bounds.top, (float)bounds.bottom - h);
    left = std::min(std::max(left, (float)bounds.left), maxLeft);
    top = std::min(std::max(top, (float)bounds.top), maxTop);

    Placement p{};
    p.x = (int)std::lround(left);
    p.y = (int)std::lround(top);

    float distance = kSlideDistance * scale;
    switch (ActiveSide(mon, left, top, w, h)) {
        case kPopLeft:
            p.dx = -distance;
            break;
        case kPopRight:
            p.dx = distance;
            break;
        case kPopTop:
            p.dy = -distance;
            break;
        case kPopBottom:
            p.dy = distance;
            break;
        default:
            if (top + h / 2.0f < (float)(bounds.top + bounds.bottom) / 2.0f) {
                p.dy = -distance;
            } else {
                p.dy = distance;
            }
            break;
    }
    return p;
}

Placement ComputePlacement(float w, float h, float scale) {
    return ComputePlacement(g_monitor, g_settings.vertical,
                            g_settings.horizontal, g_settings.offsetX,
                            g_settings.offsetY, w, h, scale);
}

// =============================================================================
// Drawing primitives
// =============================================================================

void AddRoundRect(GraphicsPath& path, RectF rect, float radius) {
    if (radius <= 0.0f) {
        path.AddRectangle(rect);
        return;
    }
    float d = radius * 2.0f;
    if (d > rect.Width) {
        d = rect.Width;
    }
    if (d > rect.Height) {
        d = rect.Height;
    }
    path.AddArc(rect.X, rect.Y, d, d, 180.0f, 90.0f);
    path.AddArc(rect.X + rect.Width - d, rect.Y, d, d, 270.0f, 90.0f);
    path.AddArc(rect.X + rect.Width - d, rect.Y + rect.Height - d, d, d, 0.0f,
                90.0f);
    path.AddArc(rect.X, rect.Y + rect.Height - d, d, d, 90.0f, 90.0f);
    path.CloseFigure();
}

// Lock icon, ported from the XAML path data on a 24x24 canvas and scaled to
// `size`. `angle` opens the shackle (25 degrees when off), `bounce` is the
// small downward kick applied while the shackle settles.
void DrawLock(Graphics& g, RectF box, const Theme& theme, float angle,
              float bounce) {
    float s = box.Width / 24.0f;
    GraphicsState state = g.Save();
    g.TranslateTransform(box.X, box.Y);
    g.ScaleTransform(s, s);

    SolidBrush brush(theme.text);

    // Body: outer rounded rect minus an inner one, 1.5 units thick.
    GraphicsPath body(FillModeAlternate);
    AddRoundRect(body, RectF(4.0f, 7.0f, 16.0f, 14.0f), 3.25f);
    AddRoundRect(body, RectF(5.5f, 8.5f, 13.0f, 11.0f), 1.75f);
    g.FillPath(&brush, &body);

    // Keyhole.
    g.FillEllipse(&brush, RectF(10.5f, 12.5f, 3.0f, 3.0f));

    // Shackle: a 1.5-unit arch. The XAML version is a filled ring built from two
    // arcs; drawing it as a centred stroke is pixel-identical and avoids the
    // way GDI+ starts a new figure on every AddArc call.
    GraphicsState shackleState = g.Save();
    g.TranslateTransform(16.0f, 7.0f + bounce);
    g.RotateTransform(angle);
    g.TranslateTransform(-16.0f, -7.0f);

    GraphicsPath shackle;
    shackle.StartFigure();
    shackle.AddLine(PointF(8.75f, 7.0f), PointF(8.75f, 5.0f));
    // Semicircle of radius 3.25 approximated by two cubic Beziers; AddBezier
    // never splits the figure, unlike AddArc.
    const float k = 0.5523f * 3.25f;
    shackle.AddBezier(PointF(8.75f, 5.0f), PointF(8.75f, 5.0f - k),
                      PointF(12.0f - k, 1.75f), PointF(12.0f, 1.75f));
    shackle.AddBezier(PointF(12.0f, 1.75f), PointF(12.0f + k, 1.75f),
                      PointF(15.25f, 5.0f - k), PointF(15.25f, 5.0f));
    shackle.AddLine(PointF(15.25f, 5.0f), PointF(15.25f, 7.0f));

    Pen shacklePen(theme.text, 1.5f);
    shacklePen.SetStartCap(LineCapFlat);
    shacklePen.SetEndCap(LineCapFlat);
    g.DrawPath(&shacklePen, &shackle);

    g.Restore(shackleState);
    g.Restore(state);
}

// Check mark drawn on progressively: `progress` 0 draws nothing, 1 draws the
// whole stroke. Ported from the "M5,12.5 L10,17.5 L19,7" polyline.
void DrawCheck(Graphics& g, RectF box, const Theme& theme, float progress) {
    float s = box.Width / 24.0f;
    GraphicsState state = g.Save();
    g.TranslateTransform(box.X, box.Y);
    g.ScaleTransform(s, s);

    const PointF a(5.0f, 12.5f);
    const PointF b(10.0f, 17.5f);
    const PointF c(19.0f, 7.0f);
    float len1 = std::sqrt((b.X - a.X) * (b.X - a.X) + (b.Y - a.Y) * (b.Y - a.Y));
    float len2 = std::sqrt((c.X - b.X) * (c.X - b.X) + (c.Y - b.Y) * (c.Y - b.Y));
    float total = len1 + len2;
    float drawn = total * Clamp01(progress);

    if (drawn > 0.01f) {
        GraphicsPath path;
        path.StartFigure();
        path.AddLine(a, drawn <= len1
                            ? PointF(Lerp(a.X, b.X, drawn / len1),
                                     Lerp(a.Y, b.Y, drawn / len1))
                            : b);
        if (drawn > len1) {
            float t = (drawn - len1) / len2;
            path.AddLine(b, PointF(Lerp(b.X, c.X, t), Lerp(b.Y, c.Y, t)));
        }

        Pen pen(theme.text, 2.4f);
        pen.SetStartCap(LineCapRound);
        pen.SetEndCap(LineCapRound);
        pen.SetLineJoin(LineJoinRound);
        g.DrawPath(&pen, &path);
    }

    g.Restore(state);
}

// Scissors glyph from Segoe Fluent Icons (E8C6).
void DrawScissors(Graphics& g, RectF box, const Theme& theme, float alpha) {
    float s = box.Width / 24.0f;
    GraphicsState state = g.Save();
    g.TranslateTransform(box.X, box.Y);
    g.ScaleTransform(s, s);

    BYTE a = (BYTE)(255 * Clamp01(alpha));
    SolidBrush brush(Color(a, GetRValue(theme.text.ToCOLORREF()),
                           GetGValue(theme.text.ToCOLORREF()),
                           GetBValue(theme.text.ToCOLORREF())));

    FontFamily family(L"Segoe Fluent Icons");
    if (family.GetLastStatus() != Ok) {
        FontFamily fallback(L"Segoe MDL2 Assets");
        if (fallback.GetLastStatus() != Ok) {
            g.Restore(state);
            return;
        }
        Font font(&fallback, 16.0f, FontStyleRegular, UnitPixel);
        StringFormat format;
        format.SetAlignment(StringAlignmentCenter);
        format.SetLineAlignment(StringAlignmentCenter);
        g.DrawString(L"\xE8C6", -1, &font, RectF(0.0f, 3.0f, 24.0f, 18.0f),
                     &format, &brush);
        g.Restore(state);
        return;
    }

    Font font(&family, 16.0f, FontStyleRegular, UnitPixel);
    StringFormat format;
    format.SetAlignment(StringAlignmentCenter);
    format.SetLineAlignment(StringAlignmentCenter);
    g.DrawString(L"\xE8C6", -1, &font, RectF(0.0f, 3.0f, 24.0f, 18.0f), &format,
                 &brush);
    g.Restore(state);
}

// The same LOGFONT feeds both the HFONT used for measuring and the GDI+ Font
// used for drawing, so the two never disagree about metrics.
LOGFONTW MakeUiLogFont(float pixelSize, int weight) {
    LOGFONTW lf{};
    lf.lfHeight = -(LONG)std::lround(pixelSize);
    lf.lfWeight = weight;
    lf.lfQuality = ANTIALIASED_QUALITY;
    lf.lfCharSet = DEFAULT_CHARSET;
    wcsncpy_s(lf.lfFaceName, g_settings.fontFamily.c_str(), _TRUNCATE);
    return lf;
}

// GDI+ MeasureString pads its result by roughly a sixth of an em, which would
// inflate every card. GetTextExtentPoint32 reports the real advance width of
// the same font, so the card width matches the WPF original.
float MeasureTextWidth(HDC dc, const LOGFONTW& logFont, const std::wstring& text) {
    if (text.empty() || !dc) {
        return 0.0f;
    }
    HFONT font = CreateFontIndirectW(&logFont);
    if (!font) {
        return 0.0f;
    }
    HGDIOBJ previous = SelectObject(dc, font);
    SIZE size{};
    GetTextExtentPoint32W(dc, text.c_str(), (INT)text.size(), &size);
    SelectObject(dc, previous);
    DeleteObject(font);
    return (float)size.cx;
}

// GDI+ centres text by its line box, which rides the cap band high on coding
// fonts like FiraCode (3 px off at 14 px on this machine). The offset is not
// linear in the em size, so probe at the exact pixel size used for the draw:
// render an H into an offscreen square, scan the ink rows, and return cap
// centre minus rect centre. Cached per font size.
float CapBandBias(float emPx, HDC screenDc) {
    struct Entry {
        float em;
        float bias;
        std::wstring family;
        int weight;
    };
    static Entry s_cache[6] = {};
    static int s_count = 0;
    for (int i = 0; i < s_count; i++) {
        if (s_cache[i].em == emPx && s_cache[i].weight == g_settings.fontWeight &&
            s_cache[i].family == g_settings.fontFamily) {
            return s_cache[i].bias;
        }
    }

    const float probeSize = 96.0f;
    Bitmap probe((int)probeSize, (int)probeSize, PixelFormat32bppARGB);
    Graphics gp(&probe);
    gp.SetTextRenderingHint(TextRenderingHintAntiAliasGridFit);
    SolidBrush white(Color(255, 255, 255, 255));
    LOGFONTW lf = MakeUiLogFont(emPx, g_settings.fontWeight);
    Font font(screenDc, &lf);
    StringFormat fmt;
    fmt.SetFormatFlags(StringFormatFlagsNoWrap | StringFormatFlagsNoClip);
    fmt.SetLineAlignment(StringAlignmentCenter);
    RectF rect(0.0f, 0.0f, probeSize, probeSize);
    gp.DrawString(L"H", 1, &font, rect, &fmt, &white);

    int first = -1;
    int last = -1;
    for (int y = 0; y < (int)probeSize; y++) {
        for (int x = 0; x < (int)probeSize; x++) {
            Color c;
            probe.GetPixel(x, y, &c);
            if (c.GetAlpha() > 40) {
                if (first < 0) {
                    first = y;
                }
                last = y;
                break;
            }
        }
    }

    float bias = 0.0f;
    if (first >= 0) {
        bias = (first + last) / 2.0f - probeSize / 2.0f;
    }
    if (s_count < 6) {
        s_cache[s_count++] = {emPx, bias, g_settings.fontFamily,
                              g_settings.fontWeight};
    } else {
        s_cache[0] = {emPx, bias, g_settings.fontFamily, g_settings.fontWeight};
    }
    return bias;
}

// =============================================================================
// Frame rendering
// =============================================================================

struct FrameState {
    TipKind kind = kCapsLock;
    bool on = false;
    bool prevOn = false;   // pose the animation starts from
    float statusT = 1.0f;  // 0 = start pose, 1 = target pose
    float clipT = 1.0f;    // check mark draw progress
    float badgeScale = 1.0f;
    float badgeAlpha = 1.0f;
    int count = 0;
};

struct LayoutMetrics {
    float width;
    float height;
    float iconSize;
    float textX;
    float textY;
    float textWidth;
    float badgeX;
    float badgeWidth;
    float indicatorY;
};

bool IsToggleKind(TipKind kind) {
    return kind == kCapsLock || kind == kNumLock || kind == kScrollLock;
}

bool IsClipKind(TipKind kind) {
    return kind == kCopy || kind == kPaste || kind == kCut;
}

std::wstring CountText(int count) {
    wchar_t buf[16];
    swprintf(buf, 16, L"\u00D7%d", count);
    return buf;
}

// Fills the card shape: either the captured backdrop with a tint on top
// (acrylic) or a flat surface color. Defined after the Surface type below.
void PaintCardBackground(Graphics& g, const GraphicsPath& card, float width,
                         float height, const Theme& theme);

// Lays out and draws the card into a Graphics that is already offset so that
// (0,0) is the top-left corner of the window. `barOnTop` mirrors the accent bar
// above the label for a card that hangs off the top edge of its monitor (see
// CardHangsTop).
void RenderCard(Graphics& g, float scale, float width, float height,
                const FrameState& f, const Theme& theme, bool barOnTop) {
    std::wstring label;
    FormatTip(f.kind, f.on, label);

    // --- fonts -------------------------------------------------------------
    HDC screenDc = GetDC(nullptr);
    LOGFONTW textLogFont = MakeUiLogFont(14.0f * scale, g_settings.fontWeight);
    LOGFONTW badgeLogFont = MakeUiLogFont(12.5f * scale, g_settings.fontWeight);

    bool clip = IsClipKind(f.kind);
    float textWidth = MeasureTextWidth(screenDc, textLogFont, label);
    float badgeWidth = clip ? MeasureTextWidth(screenDc, badgeLogFont,
                                               CountText(f.count)) +
                                  14.0f * scale
                            : 0.0f;

    Font textFont(screenDc, &textLogFont);
    Font badgeFont(screenDc, &badgeLogFont);
    float capBias = CapBandBias(14.0f * scale, screenDc);
    float badgeCapBias = CapBandBias(12.5f * scale, screenDc);
    ReleaseDC(nullptr, screenDc);

    // Ink metrics: GDI advances carry side bearings, so place the label by its
    // measured ink instead of the advance. A tall probe rect never clips.
    float inkWidth = textWidth;
    float inkLSB = 0.0f;
    {
        CharacterRange all(0, (INT)label.size());
        StringFormat probeFormat;
        probeFormat.SetFormatFlags(StringFormatFlagsNoWrap |
                                   StringFormatFlagsNoClip);
        probeFormat.SetAlignment(StringAlignmentNear);
        probeFormat.SetMeasurableCharacterRanges(1, &all);
        Region regions[1];
        RectF probeRect(0.0f, 0.0f, width, 40.0f * scale);
        if (g.MeasureCharacterRanges(label.c_str(), (INT)label.size(), &textFont,
                                     probeRect, &probeFormat, 1,
                                     regions) == Ok) {
            RectF ink;
            if (regions[0].GetBounds(&ink, &g) == Ok && ink.Width > 0.0f) {
                inkWidth = ink.Width;
                inkLSB = ink.X - probeRect.X;
            }
        }
    }

    // --- card --------------------------------------------------------------
    g.SetSmoothingMode(SmoothingModeAntiAlias);
    g.SetPixelOffsetMode(PixelOffsetModeHalf);
    g.SetTextRenderingHint(TextRenderingHintAntiAliasGridFit);

    GraphicsPath card;
    AddRoundRect(card, RectF(0.0f, 0.0f, width, height),
                 (float)g_settings.cornerRadius * scale);
    PaintCardBackground(g, card, width, height, theme);

    // --- icon --------------------------------------------------------------
    // Lock-mode content grid is asymmetric: 6 DIP above the label and 10 DIP
    // below, because the accent bar owns the bottom 10 DIP. Mirroring the bar
    // swaps that to 10/6, which drops the region's centre 4 DIP — the icon and
    // label follow it. Clipboard cards have no bar and stay symmetric.
    float gridShift = (!clip && barOnTop) ? 4.0f * scale : 0.0f;

    float iconSize = 22.0f * scale;
    // Slot the icon by its drawn ink (the check spans 14 of the 24 glyph
    // units) so the visual gaps to the label match the badge gap exactly.
    const float iconInk = 14.0f / 24.0f * iconSize;
    const float clipGap = 12.0f * scale;
    const float clipGroupWidth =
        iconInk + clipGap + inkWidth + clipGap + badgeWidth;
    const float clipLeft = (width - clipGroupWidth) / 2.0f;
    // The ink is centred inside the icon box, so shift the box left by half
    // the slack to put the ink's left edge on clipLeft. Clipboard cards centre
    // the glyph on the midline; lock cards keep their 1 DIP optical lift.
    RectF iconBox(clip ? clipLeft - (iconSize - iconInk) / 2.0f
                       : 16.0f * scale,
                  (height - iconSize) / 2.0f - (clip ? 0.0f : 1.0f * scale) +
                      gridShift,
                  iconSize, iconSize);

    float poseT = EaseOutQuad(f.statusT);
    float pose = Lerp(f.prevOn ? 1.0f : 0.0f, f.on ? 1.0f : 0.0f, poseT);
    if (clip) {
        if (f.kind == kCut) {
            DrawScissors(g, iconBox, theme, EaseOutQuad(f.clipT));
        } else {
            DrawCheck(g, iconBox, theme, EaseOutQuad(f.clipT));
        }
    } else {
        float angle = Lerp(25.0f, 0.0f, pose);
        float t = Clamp01(f.statusT);
        float bounce = t < 0.1f ? EaseOutCubic(t / 0.1f)
                                : 1.0f - EaseInOutCubic((t - 0.1f) / 0.9f);
        DrawLock(g, iconBox, theme, angle, bounce);
    }

    // --- text --------------------------------------------------------------
    g.SetTextRenderingHint(TextRenderingHintAntiAliasGridFit);
    SolidBrush textBrush(theme.text);
    StringFormat textFormat;
    textFormat.SetFormatFlags(StringFormatFlagsNoWrap | StringFormatFlagsNoClip);
    textFormat.SetAlignment(StringAlignmentNear);
    textFormat.SetLineAlignment(StringAlignmentCenter);

    float textX;
    if (clip) {
        textX = clipLeft + iconInk + clipGap;
    } else {
        // Centered in the content grid, offset by the icon gutter.
        float contentLeft = 16.0f * scale;
        float contentRight = width - 12.0f * scale;
        textX = (contentLeft + contentRight) / 2.0f - inkWidth / 2.0f +
                18.0f * scale / 2.0f;
    }

    float textY = (clip ? height / 2.0f
                        : height / 2.0f - 2.0f * scale + gridShift);
    // Draw the cap band on the target line, not the line box, and start the
    // ink on textX instead of the layout origin.
    textY -= capBias;
    // NoWrap keeps a slightly narrower GDI+ measure from breaking the label
    // into two lines, so the rect only needs to be tall enough for one line.
    RectF textRect(textX - inkLSB, textY - 14.0f * scale,
                   width - (textX - inkLSB) + 8.0f * scale, 28.0f * scale);
    g.DrawString(label.c_str(), (INT)label.size(), &textFont, textRect,
                 &textFormat, &textBrush);

    // --- clipboard badge ---------------------------------------------------
    if (clip) {
        float badgeHeight = 18.0f * scale;
        float badgeX = clipLeft + iconInk + clipGap + inkWidth + clipGap;
        float badgeY = (height - badgeHeight) / 2.0f;

        GraphicsState badgeState = g.Save();
        g.TranslateTransform(badgeX + badgeWidth / 2.0f, badgeY + badgeHeight / 2.0f);
        g.ScaleTransform(f.badgeScale, f.badgeScale);
        g.TranslateTransform(-(badgeX + badgeWidth / 2.0f),
                             -(badgeY + badgeHeight / 2.0f));

        GraphicsPath badge;
        AddRoundRect(badge, RectF(badgeX, badgeY, badgeWidth, badgeHeight),
                     9.0f * scale);
        Color accent = theme.accent;
        accent = Color((BYTE)(accent.GetA() * Clamp01(f.badgeAlpha)),
                       accent.GetR(), accent.GetG(), accent.GetB());
        SolidBrush badgeBrush(accent);
        g.FillPath(&badgeBrush, &badge);

        Color onAccent = theme.onAccent;
        onAccent = Color((BYTE)(onAccent.GetA() * Clamp01(f.badgeAlpha)),
                         onAccent.GetR(), onAccent.GetG(), onAccent.GetB());
        SolidBrush badgeText(onAccent);
        StringFormat badgeFormat;
        badgeFormat.SetFormatFlags(StringFormatFlagsNoClip);
        badgeFormat.SetAlignment(StringAlignmentCenter);
        badgeFormat.SetLineAlignment(StringAlignmentCenter);
        std::wstring countText = CountText(f.count);
        g.DrawString(countText.c_str(), (INT)countText.size(), &badgeFont,
                     RectF(badgeX, badgeY - badgeCapBias, badgeWidth,
                           badgeHeight),
                     &badgeFormat, &badgeText);

        g.Restore(badgeState);
    }

    // --- accent bar ---------------------------------------------------------
    if (!clip) {
        float indicatorHeight = 3.0f * scale;
        float indicatorWidth = Lerp(36.0f, 60.0f, pose) * scale;
        // Default pose: 7 DIP above the bottom edge. Mirrored: the same 7 DIP
        // below the top edge, so the bar sits above the label.
        float indicatorY = barOnTop
                               ? 7.0f * scale
                               : height - 7.0f * scale - indicatorHeight;
        float indicatorX = (width - indicatorWidth) / 2.0f;
        BYTE alpha = (BYTE)std::lround(Lerp(0.2f, 1.0f, pose) * 255.0f);
        Color accent = theme.accent;
        SolidBrush indicator(
            Color(alpha, accent.GetR(), accent.GetG(), accent.GetB()));
        GraphicsPath bar;
        AddRoundRect(bar,
                     RectF(indicatorX, indicatorY, indicatorWidth,
                           indicatorHeight),
                     indicatorHeight / 2.0f);
        g.FillPath(&indicator, &bar);
    }
}

// Measures the card size for the current tip, in physical pixels.
void MeasureCard(float scale, const FrameState& f, int& outWidth,
                 int& outHeight) {
    std::wstring label;
    FormatTip(f.kind, f.on, label);

    HDC screenDc = GetDC(nullptr);
    LOGFONTW textLogFont = MakeUiLogFont(14.0f * scale, g_settings.fontWeight);
    LOGFONTW badgeLogFont = MakeUiLogFont(12.5f * scale, g_settings.fontWeight);

    bool clip = IsClipKind(f.kind);
    float textWidth = MeasureTextWidth(screenDc, textLogFont, label);
    float badgeWidth = clip ? MeasureTextWidth(screenDc, badgeLogFont,
                                               CountText(f.count)) +
                                  14.0f * scale
                            : 0.0f;

    float widthDip =
        16.0f + 22.0f + 18.0f + textWidth / scale + 12.0f +
        (clip ? badgeWidth / scale + 22.0f : 0.0f);
    outWidth = (int)std::lround(std::max(kBaseWidth * scale,
                                         std::ceil(widthDip) * scale));
    outHeight = (int)std::lround(kBaseHeight * scale);

    ReleaseDC(nullptr, screenDc);
}

}  // namespace

namespace {

constexpr UINT_PTR kTimerClip = 5;
constexpr UINT_PTR kTimerTop = 6;
constexpr UINT WM_APP_POLL = WM_APP + 4;
constexpr UINT WM_APP_SETTINGS = WM_APP + 5;

// =============================================================================
// Layered ARGB surface
// =============================================================================

struct Surface {
    HDC dc = nullptr;
    HBITMAP bitmap = nullptr;
    HGDIOBJ oldBitmap = nullptr;
    void* bits = nullptr;
    int width = 0;
    int height = 0;
    int stride = 0;

    ~Surface() {
        Release();
    }

    void Release() {
        if (dc) {
            if (oldBitmap) {
                SelectObject(dc, oldBitmap);
            }
            if (bitmap) {
                DeleteObject(bitmap);
            }
            DeleteDC(dc);
        }
        dc = nullptr;
        bitmap = nullptr;
        oldBitmap = nullptr;
        bits = nullptr;
        width = 0;
        height = 0;
        stride = 0;
    }

    bool Ensure(int w, int h) {
        if (dc && w == width && h == height) {
            return true;
        }
        Release();
        if (w <= 0 || h <= 0) {
            return false;
        }

        BITMAPINFO bi{};
        bi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
        bi.bmiHeader.biWidth = w;
        bi.bmiHeader.biHeight = -h;  // top-down
        bi.bmiHeader.biPlanes = 1;
        bi.bmiHeader.biBitCount = 32;
        bi.bmiHeader.biCompression = BI_RGB;

        HDC screen = GetDC(nullptr);
        dc = CreateCompatibleDC(screen);
        bitmap = CreateDIBSection(screen, &bi, DIB_RGB_COLORS, &bits, nullptr, 0);
        ReleaseDC(nullptr, screen);
        if (!dc || !bitmap || !bits) {
            Release();
            return false;
        }

        oldBitmap = SelectObject(dc, bitmap);
        width = w;
        height = h;
        stride = w * 4;
        return true;
    }

    void Clear() {
        if (bits) {
            memset(bits, 0, (size_t)stride * height);
        }
    }

    // UpdateLayeredWindow expects premultiplied alpha.
    void Premultiply() {
        if (!bits) {
            return;
        }
        auto* base = (BYTE*)bits;
        for (int y = 0; y < height; y++) {
            BYTE* row = base + (size_t)y * stride;
            for (int x = 0; x < width; x++) {
                BYTE* px = row + x * 4;
                BYTE a = px[3];
                if (a == 255) {
                    continue;
                }
                if (a == 0) {
                    px[0] = px[1] = px[2] = 0;
                    continue;
                }
                px[0] = (BYTE)(px[0] * a / 255);
                px[1] = (BYTE)(px[1] * a / 255);
                px[2] = (BYTE)(px[2] * a / 255);
            }
        }
    }
};

// =============================================================================
// Blurred backdrop ("acrylic")
//
// A DWM acrylic backdrop needs a non-layered window, and a non-layered window
// can neither fade nor blend per pixel. Instead the area behind the card is
// copied once per tip and blurred - the result is composited into the same
// ARGB surface, so the card keeps real blur *and* full animation.
// =============================================================================

struct Backdrop {
    Surface image;
    int x = 0;
    int y = 0;
    int w = 0;
    int h = 0;
    int padLeft = 0;  // extra captured pixels around the card, so the blur
    int padTop = 0;   // near the edges averages real screen, not repeats
    int gen = 0;      // bumped on every successful capture (GPU bitmap cache)
    bool valid = false;

    void Invalidate() {
        valid = false;
    }

    bool Matches(int newX, int newY, int newW, int newH) const {
        return valid && x == newX && y == newY && w == newW && h == newH;
    }
};

Backdrop g_backdrop;

// Separable box blur. Running it twice per axis is close enough to a Gaussian
// at this size and stays well under a millisecond for a card-sized region.
void BlurAxis(BYTE* bits, int width, int height, int radius, bool horizontal) {
    if (!bits || radius <= 0) {
        return;
    }

    const int lineCount = horizontal ? height : width;
    const int lineLength = horizontal ? width : height;
    const int lineStride = horizontal ? width * 4 : 4;
    const int elemStride = horizontal ? 4 : width * 4;
    const int window = radius * 2 + 1;
    if (lineLength <= 1 || lineCount <= 0) {
        return;
    }

    std::vector<BYTE> line((size_t)lineLength * 4);
    for (int l = 0; l < lineCount; l++) {
        BYTE* base = bits + (size_t)l * lineStride;
        for (int i = 0; i < lineLength; i++) {
            memcpy(&line[(size_t)i * 4], base + (size_t)i * elemStride, 4);
        }

        int sum[3] = {0, 0, 0};
        for (int i = -radius; i <= radius; i++) {
            int idx = Clamp(i, 0, lineLength - 1);
            const BYTE* px = &line[(size_t)idx * 4];
            sum[0] += px[0];
            sum[1] += px[1];
            sum[2] += px[2];
        }

        for (int i = 0; i < lineLength; i++) {
            BYTE* dst = base + (size_t)i * elemStride;
            dst[0] = (BYTE)(sum[0] / window);
            dst[1] = (BYTE)(sum[1] / window);
            dst[2] = (BYTE)(sum[2] / window);

            int add = Clamp(i + radius + 1, 0, lineLength - 1);
            int sub = Clamp(i - radius, 0, lineLength - 1);
            const BYTE* addPx = &line[(size_t)add * 4];
            const BYTE* subPx = &line[(size_t)sub * 4];
            sum[0] += addPx[0] - subPx[0];
            sum[1] += addPx[1] - subPx[1];
            sum[2] += addPx[2] - subPx[2];
        }
    }
}

void BlurBackdrop(Surface& image, int radius) {
    if (!image.bits || radius <= 0) {
        return;
    }
    for (int pass = 0; pass < 2; pass++) {
        BlurAxis((BYTE*)image.bits, image.width, image.height, radius, true);
        BlurAxis((BYTE*)image.bits, image.width, image.height, radius, false);
    }
}

// A screen copy of an elevated window comes back black without an error code,
// so look at the pixels instead of the return value.
bool SurfaceIsBlank(const Surface& image) {
    if (!image.bits) {
        return true;
    }
    const BYTE* base = (const BYTE*)image.bits;
    for (int y = 0; y < image.height; y += 4) {
        const BYTE* row = base + (size_t)y * image.stride;
        for (int x = 0; x < image.width; x += 4) {
            const BYTE* px = row + x * 4;
            if (px[0] | px[1] | px[2]) {
                return false;
            }
        }
    }
    return true;
}

bool CaptureBackdrop(HDC source, int x, int y, int w, int h, int radius) {
    g_backdrop.Invalidate();
    if (!source || w <= 0 || h <= 0) {
        return false;
    }
    // Pad by the blur reach (two box passes), clamped to the desktop so no
    // black off-screen pixels get averaged in.
    int pad = std::min(radius * 2 + 2, 320);
    int vx = GetSystemMetrics(SM_XVIRTUALSCREEN);
    int vy = GetSystemMetrics(SM_YVIRTUALSCREEN);
    int vr = vx + GetSystemMetrics(SM_CXVIRTUALSCREEN);
    int vb = vy + GetSystemMetrics(SM_CYVIRTUALSCREEN);
    int left = std::max(vx, x - pad);
    int top = std::max(vy, y - pad);
    int right = std::max(left + 1, std::min(vr, x + w + pad));
    int bottom = std::max(top + 1, std::min(vb, y + h + pad));
    if (right - left < w || bottom - top < h) {
        left = x; top = y; right = x + w; bottom = y + h;
    }
    if (!g_backdrop.image.Ensure(right - left, bottom - top)) {
        return false;
    }
    if (!BitBlt(g_backdrop.image.dc, 0, 0, right - left, bottom - top, source,
                left, top, SRCCOPY | CAPTUREBLT)) {
        return false;
    }
    g_backdrop.padLeft = x - left;
    g_backdrop.padTop = y - top;
    g_backdrop.w = w;
    g_backdrop.h = h;
    if (SurfaceIsBlank(g_backdrop.image)) {
        return false;
    }

    BlurBackdrop(g_backdrop.image, radius);
    g_backdrop.x = x;
    g_backdrop.y = y;
    g_backdrop.gen++;
    g_backdrop.valid = true;
    return true;
}

// Position of the border colour flow, 0 to 1, repeating every morphSeconds.
float MorphPhase() {
    if (g_settings.morphSeconds <= 0) {
        return 0.0f;
    }
    double period = (double)g_settings.morphSeconds * 1000.0;
    return (float)(std::fmod((double)GetTickCount64(), period) / period);
}

bool BorderIsMorphing() {
    return g_settings.borderStyle == 0 && g_settings.morphSeconds > 0;
}

Color MixColor(const Color& a, const Color& b, float t, BYTE alpha) {
    return Color(alpha, (BYTE)std::lround(Lerp((float)a.GetR(), (float)b.GetR(), t)),
                 (BYTE)std::lround(Lerp((float)a.GetG(), (float)b.GetG(), t)),
                 (BYTE)std::lround(Lerp((float)a.GetB(), (float)b.GetB(), t)));
}

// Border ring plus a soft inner glow. The gradient runs accent -> second
// colour -> accent along a slanted vector and wraps, so sliding the start point
// by one full vector per cycle loops without a seam.
void DrawCardBorder(Graphics& g, const GraphicsPath& card, float width,
                    float height, const Theme& theme) {
    float scale = height / kBaseHeight;
    int style = theme.highContrast ? 1 : g_settings.borderStyle;
    if (style == 2) {
        return;
    }

    float bw = (float)g_settings.borderWidth * scale;
    float radius = std::max(0.0f, (float)g_settings.cornerRadius * scale - bw / 2.0f);
    GraphicsPath ring;
    AddRoundRect(ring, RectF(bw / 2.0f, bw / 2.0f, width - bw, height - bw), radius);

    if (style == 1) {
        Color c = theme.highContrast ? theme.border : theme.accent;
        Pen pen(c, bw);
        g.DrawPath(&pen, &ring);
        return;
    }

    float phase = MorphPhase();

    if (g_settings.glow > 0) {
        float wave = 0.5f + 0.5f * std::sin(phase * 6.2831853f);
        Color glowColor = MixColor(theme.accent, theme.accent2, wave, 255);
        // One soft halo hugging the border line only, so the card's inside
        // stays one even tone right up to the edge.
        GraphicsState state = g.Save();
        g.SetClip(&card);
        float a = (float)g_settings.glow / 100.0f * 0.45f;
        Pen glowPen(Color((BYTE)std::lround(255.0f * a), glowColor.GetR(),
                          glowColor.GetG(), glowColor.GetB()),
                    bw + 2.0f * scale);
        glowPen.SetLineJoin(LineJoinRound);
        g.DrawPath(&glowPen, &ring);
        g.Restore(state);
    }

    float vx = width * 1.2f;
    float vy = height * 0.4f;
    PointF p1(-vx + phase * vx, -vy + phase * vy);
    PointF p2(p1.X + vx, p1.Y + vy);
    LinearGradientBrush brush(p1, p2, theme.accent, theme.accent2);
    Color colors[3] = {theme.accent, theme.accent2, theme.accent};
    REAL stops[3] = {0.0f, 0.5f, 1.0f};
    brush.SetInterpolationColors(colors, stops, 3);
    brush.SetWrapMode(WrapModeTile);
    Pen pen(&brush, bw);
    pen.SetLineJoin(LineJoinRound);
    g.DrawPath(&pen, &ring);
}

void PaintCardBackground(Graphics& g, const GraphicsPath& card, float width,
                         float height, const Theme& theme) {
    bool acrylic = g_settings.material != kMaterialSolid && g_backdrop.valid;
    if (acrylic) {
        const Surface& image = g_backdrop.image;
        Bitmap bitmap(image.width, image.height, image.stride,
                      PixelFormat32bppRGB, (BYTE*)image.bits);
        GraphicsState state = g.Save();
        g.SetClip(&card);
        // 1:1 copy from inside the padded capture: no scaling, so no
        // resampling fringe at the card edge.
        g.SetInterpolationMode(InterpolationModeNearestNeighbor);
        g.DrawImage(&bitmap, RectF(0.0f, 0.0f, width, height),
                    (REAL)g_backdrop.padLeft, (REAL)g_backdrop.padTop,
                    (REAL)g_backdrop.w, (REAL)g_backdrop.h, UnitPixel);
        g.Restore(state);

        SolidBrush tint(theme.tint);
        g.FillPath(&tint, &card);
    } else {
        SolidBrush surface(theme.surface);
        g.FillPath(&surface, &card);
    }

    DrawCardBorder(g, card, width, height, theme);
}

enum Phase { kPhaseHidden, kPhaseIn, kPhaseHold, kPhaseOut };

// =============================================================================
// GPU renderer (DirectComposition + Direct2D)
//
// The card artwork is drawn with Direct2D into an IDCompositionSurface; show,
// hide and slide become IDCompositionAnimation keyframes on the visual, so the
// frames in between cost no CPU at all. Content redraws only when the tip
// state or the morphing border changes, never per animation frame. The GDI /
// UpdateLayeredWindow path above stays as the fallback (GpuFailToGdi).
// =============================================================================

// Defined in the runtime state block below.
extern HWND g_hwnd;
extern float g_scale;
extern int g_cardWidth;
extern int g_cardHeight;
extern Theme g_theme;
extern FrameState g_frame;
extern Placement g_placement;
extern int g_animMs;
extern Phase g_phase;

template <class T>
void GpuRelease(T*& p) {
    if (p) {
        p->Release();
        p = nullptr;
    }
}

D2D1_COLOR_F D2dColor(const Color& c) {
    return D2D1_COLOR_F{c.GetR() / 255.0f, c.GetG() / 255.0f,
                        c.GetB() / 255.0f, c.GetA() / 255.0f};
}

D2D1_COLOR_F D2dColorAlpha(const Color& c, BYTE alpha) {
    return D2D1_COLOR_F{c.GetR() / 255.0f, c.GetG() / 255.0f,
                        c.GetB() / 255.0f, alpha / 255.0f};
}

D2D1_ROUNDED_RECT D2dRoundRect(float x, float y, float w, float h, float r) {
    if (r * 2.0f > w) {
        r = w / 2.0f;
    }
    if (r * 2.0f > h) {
        r = h / 2.0f;
    }
    D2D1_ROUNDED_RECT rr;
    rr.rect = D2D1_RECT_F{x, y, x + w, y + h};
    rr.radiusX = r;
    rr.radiusY = r;
    return rr;
}

struct GpuRenderer {
    bool inited = false;   // the DComp pipeline was built
    bool failed = false;   // a runtime error pushed us back to GDI
    int armed = 0;         // 0 none, 1 show animation running, 2 hide
    ID2D1Factory1* factory = nullptr;
    ID3D11Device* d3d = nullptr;
    ID2D1Device* d2d = nullptr;
    IDCompositionDevice* device = nullptr;
    IDCompositionTarget* target = nullptr;
    IDCompositionVisual* visual = nullptr;
    IDCompositionEffectGroup* effect = nullptr;  // visual opacity lives here
    IDCompositionVirtualSurface* surface = nullptr;
    int surfW = 0;
    int surfH = 0;
    ID2D1StrokeStyle* roundStroke = nullptr;
    ID2D1StrokeStyle* flatStroke = nullptr;
    ID2D1PathGeometry* lockBody = nullptr;  // 24-unit outer/inner ring
    ID2D1PathGeometry* shackle = nullptr;   // 24-unit arch
    ID2D1RoundedRectangleGeometry* cardShape = nullptr;  // glow mask, px space
    int cardShapeW = 0;
    int cardShapeH = 0;
    int backdropGen = -1;
    ID2D1Bitmap* backdropBitmap = nullptr;
    IDWriteFactory* write = nullptr;
    IDWriteTextFormat* textFormat = nullptr;
    float textFormatEm = 0;
    int textFormatWeight = -1;
    float textCapRatio = 0.7f;
    IDWriteTextFormat* badgeFormat = nullptr;
    float badgeFormatEm = 0;
    int badgeFormatWeight = -1;
    float badgeCapRatio = 0.7f;
    IDWriteTextFormat* glyphFormat = nullptr;  // Segoe Fluent Icons, unit space
};

GpuRenderer g_gpu;

// A DirectWrite text layout with the ink metrics the card layout needs.
// Cached per string so morph-border redraws do not rebuild it.
struct DText {
    std::wstring text;
    float em = 0;
    int weight = -1;
    float maxWidth = 0;
    bool centered = false;
    IDWriteTextLayout* layout = nullptr;
    float inkWidth = 0;
    float inkLSB = 0;
    float capCenter = 0;  // cap band centre, from the layout top
};

bool GpuActive() {
    return g_settings.renderer == 0 && g_gpu.inited && !g_gpu.failed;
}

void UseLayeredStyle(bool layered) {
    if (!g_hwnd) {
        return;
    }
    LONG_PTR ex = GetWindowLongPtrW(g_hwnd, GWL_EXSTYLE);
    LONG_PTR want = layered
        ? ((ex | WS_EX_LAYERED) & ~WS_EX_NOREDIRECTIONBITMAP)
        : ((ex | WS_EX_NOREDIRECTIONBITMAP) & ~WS_EX_LAYERED);
    if (want != ex) {
        SetWindowLongPtrW(g_hwnd, GWL_EXSTYLE, want);
    }
}

void GpuShutdown() {
    GpuRelease(g_gpu.backdropBitmap);
    GpuRelease(g_gpu.cardShape);
    GpuRelease(g_gpu.shackle);
    GpuRelease(g_gpu.lockBody);
    GpuRelease(g_gpu.glyphFormat);
    GpuRelease(g_gpu.badgeFormat);
    GpuRelease(g_gpu.textFormat);
    GpuRelease(g_gpu.roundStroke);
    GpuRelease(g_gpu.flatStroke);
    GpuRelease(g_gpu.surface);
    GpuRelease(g_gpu.visual);
    GpuRelease(g_gpu.effect);
    GpuRelease(g_gpu.target);
    GpuRelease(g_gpu.device);
    GpuRelease(g_gpu.d2d);
    GpuRelease(g_gpu.write);
    GpuRelease(g_gpu.d3d);
    GpuRelease(g_gpu.factory);
    g_gpu.inited = false;
    g_gpu.armed = 0;
    g_gpu.surfW = 0;
    g_gpu.surfH = 0;
    g_gpu.backdropGen = -1;
}

void GpuFailToGdi(const wchar_t* why) {
    Wh_Log(L"WinTips OSD GPU renderer failed (%s), falling back to GDI", why);
    GpuShutdown();
    g_gpu.failed = true;
    UseLayeredStyle(true);
}

// Traces a GDI+ AddRoundRect as a closed D2D figure.
void SinkRoundRect(ID2D1GeometrySink* sink, const D2D1_RECT_F& r, float radius) {
    float w = r.right - r.left;
    float h = r.bottom - r.top;
    if (radius * 2.0f > w) {
        radius = w / 2.0f;
    }
    if (radius * 2.0f > h) {
        radius = h / 2.0f;
    }
    D2D1_POINT_2F tl{r.left + radius, r.top};
    D2D1_POINT_2F tr{r.right - radius, r.top};
    D2D1_POINT_2F br{r.right - radius, r.bottom};
    D2D1_POINT_2F bl{r.left + radius, r.bottom};
    D2D1_ARC_SEGMENT arc = {{}, {radius, radius}, 0.0f,
                            D2D1_SWEEP_DIRECTION_CLOCKWISE,
                            D2D1_ARC_SIZE_SMALL};
    sink->BeginFigure(tl, D2D1_FIGURE_BEGIN_FILLED);
    sink->AddLine(tr);
    arc.point = D2D1_POINT_2F{r.right, r.top + radius};
    sink->AddArc(arc);
    sink->AddLine(br);
    arc.point = D2D1_POINT_2F{r.right - radius, r.bottom};
    sink->AddArc(arc);
    sink->AddLine(bl);
    arc.point = D2D1_POINT_2F{r.left, r.bottom - radius};
    sink->AddArc(arc);
    sink->AddLine(D2D1_POINT_2F{r.left, r.top + radius});
    arc.point = tl;
    sink->AddArc(arc);
    sink->EndFigure(D2D1_FIGURE_END_CLOSED);
}

void BuildLockGeometries() {
    // Body: outer rounded rect minus an inner one, 1.5 units thick.
    if (SUCCEEDED(g_gpu.factory->CreatePathGeometry(&g_gpu.lockBody))) {
        ID2D1GeometrySink* sink = nullptr;
        if (SUCCEEDED(g_gpu.lockBody->Open(&sink)) && sink) {
            sink->SetFillMode(D2D1_FILL_MODE_ALTERNATE);
            SinkRoundRect(sink, D2D1_RECT_F{4.0f, 7.0f, 20.0f, 21.0f}, 3.25f);
            SinkRoundRect(sink, D2D1_RECT_F{5.5f, 8.5f, 18.5f, 19.5f}, 1.75f);
            sink->Close();
            sink->Release();
        }
    }
    // Shackle: the same two-cubic arch the GDI+ path strokes.
    if (SUCCEEDED(g_gpu.factory->CreatePathGeometry(&g_gpu.shackle))) {
        ID2D1GeometrySink* sink = nullptr;
        if (SUCCEEDED(g_gpu.shackle->Open(&sink)) && sink) {
            const float k = 0.5523f * 3.25f;
            sink->BeginFigure(D2D1_POINT_2F{8.75f, 7.0f},
                              D2D1_FIGURE_BEGIN_HOLLOW);
            sink->AddLine(D2D1_POINT_2F{8.75f, 5.0f});
            D2D1_BEZIER_SEGMENT seg = {{8.75f, 5.0f - k},
                                       {12.0f - k, 1.75f},
                                       {12.0f, 1.75f}};
            sink->AddBezier(seg);
            seg = D2D1_BEZIER_SEGMENT{{12.0f + k, 1.75f},
                                      {15.25f, 5.0f - k},
                                      {15.25f, 5.0f}};
            sink->AddBezier(seg);
            sink->AddLine(D2D1_POINT_2F{15.25f, 7.0f});
            sink->EndFigure(D2D1_FIGURE_END_OPEN);
            sink->Close();
            sink->Release();
        }
    }
}

bool MakeTextFormat(IDWriteTextFormat** out, const wchar_t* family, float em,
                    int weight) {
    return SUCCEEDED(g_gpu.write->CreateTextFormat(
        family, nullptr, (DWRITE_FONT_WEIGHT)weight, DWRITE_FONT_STYLE_NORMAL,
        DWRITE_FONT_STRETCH_NORMAL, em, L"en-US", out));
}

// Cap height as a fraction of the em, read from the same face DirectWrite's
// GDI-compatible matching picks for this family and weight. Used to land the
// cap band on the target line like the GDI+ probe does, without re-probing
// pixels.
float CapRatio(const wchar_t* family, int weight, float fallback) {
    float ratio = fallback;
    IDWriteFontCollection* coll = nullptr;
    if (FAILED(g_gpu.write->GetSystemFontCollection(&coll)) || !coll) {
        return ratio;
    }
    BOOL found = FALSE;
    UINT32 index = 0;
    if (SUCCEEDED(coll->FindFamilyName(family, &index, &found)) && found) {
        IDWriteFontFamily* fam = nullptr;
        if (SUCCEEDED(coll->GetFontFamily(index, &fam)) && fam) {
            IDWriteFont* font = nullptr;
            if (SUCCEEDED(fam->GetFirstMatchingFont(
                    (DWRITE_FONT_WEIGHT)weight, DWRITE_FONT_STRETCH_NORMAL,
                    DWRITE_FONT_STYLE_NORMAL, &font)) &&
                font) {
                IDWriteFontFace* face = nullptr;
                if (SUCCEEDED(font->CreateFontFace(&face)) && face) {
                    IDWriteFontFace1* face1 = nullptr;
                    if (SUCCEEDED(face->QueryInterface(
                            __uuidof(IDWriteFontFace1), (void**)&face1)) &&
                        face1) {
                        DWRITE_FONT_METRICS1 m{};
                        face1->GetMetrics(&m);
                        if (m.designUnitsPerEm) {
                            ratio =
                                (float)m.capHeight / (float)m.designUnitsPerEm;
                        }
                        face1->Release();
                    }
                    face->Release();
                }
                font->Release();
            }
            fam->Release();
        }
    }
    coll->Release();
    return ratio;
}

void EnsureLabelFormats(float textEm, float badgeEm) {
    if (!g_gpu.textFormat || g_gpu.textFormatEm != textEm ||
        g_gpu.textFormatWeight != g_settings.fontWeight) {
        GpuRelease(g_gpu.textFormat);
        MakeTextFormat(&g_gpu.textFormat, g_settings.fontFamily.c_str(),
                       textEm, g_settings.fontWeight);
        g_gpu.textFormatEm = textEm;
        g_gpu.textFormatWeight = g_settings.fontWeight;
        if (g_gpu.textFormat) {
            g_gpu.textCapRatio =
                CapRatio(g_settings.fontFamily.c_str(),
                         g_settings.fontWeight, g_gpu.textCapRatio);
        }
    }
    if (!g_gpu.badgeFormat || g_gpu.badgeFormatEm != badgeEm ||
        g_gpu.badgeFormatWeight != g_settings.fontWeight) {
        GpuRelease(g_gpu.badgeFormat);
        MakeTextFormat(&g_gpu.badgeFormat, g_settings.fontFamily.c_str(),
                       badgeEm, g_settings.fontWeight);
        g_gpu.badgeFormatEm = badgeEm;
        g_gpu.badgeFormatWeight = g_settings.fontWeight;
        if (g_gpu.badgeFormat) {
            g_gpu.badgeCapRatio =
                CapRatio(g_settings.fontFamily.c_str(),
                         g_settings.fontWeight, g_gpu.badgeCapRatio);
        }
    }
}

void EnsureGlyphFormat() {
    if (g_gpu.glyphFormat) {
        return;
    }
    IDWriteFontCollection* coll = nullptr;
    const wchar_t* family = nullptr;
    if (SUCCEEDED(g_gpu.write->GetSystemFontCollection(&coll)) && coll) {
        BOOL found = FALSE;
        UINT32 index = 0;
        coll->FindFamilyName(L"Segoe Fluent Icons", &index, &found);
        if (found) {
            family = L"Segoe Fluent Icons";
        } else {
            coll->FindFamilyName(L"Segoe MDL2 Assets", &index, &found);
            if (found) {
                family = L"Segoe MDL2 Assets";
            }
        }
        coll->Release();
    }
    if (family) {
        MakeTextFormat(&g_gpu.glyphFormat, family, 16.0f, 400);
    }
}

// (Re)builds a cached layout. `centered` centres the text in the layout box
// (badge, scissors); otherwise the ink starts at the drawn origin.
bool EnsureDText(DText& t, const std::wstring& text, float em, int weight,
                 IDWriteTextFormat* format, float capRatio, float maxWidth,
                 bool centered) {
    if (t.layout && t.text == text && t.em == em && t.weight == weight &&
        t.maxWidth == maxWidth && t.centered == centered) {
        return true;
    }
    GpuRelease(t.layout);
    t.text = text;
    t.em = em;
    t.weight = weight;
    t.maxWidth = maxWidth;
    t.centered = centered;
    if (!format) {
        return false;
    }
    if (FAILED(g_gpu.write->CreateTextLayout(text.c_str(), (UINT32)text.size(),
                                             format, maxWidth, 256.0f,
                                             &t.layout))) {
        return false;
    }
    t.layout->SetTextAlignment(centered ? DWRITE_TEXT_ALIGNMENT_CENTER
                                        : DWRITE_TEXT_ALIGNMENT_LEADING);
    DWRITE_TEXT_METRICS m{};
    t.layout->GetMetrics(&m);
    DWRITE_OVERHANG_METRICS oh{};
    t.layout->GetOverhangMetrics(&oh);
    t.inkWidth = std::max(0.0f, m.width - oh.left - oh.right);
    t.inkLSB = oh.left;
    DWRITE_LINE_METRICS lm[2]{};
    UINT32 count = 0;
    float baseline = 0.0f;
    if (SUCCEEDED(t.layout->GetLineMetrics(lm, 2, &count)) && count > 0) {
        baseline = lm[0].baseline;
    }
    t.capCenter = baseline - capRatio * em / 2.0f;
    return true;
}

bool GpuInit() {
    if (g_gpu.inited) {
        return true;
    }
    UseLayeredStyle(false);
    HRESULT hr;

    D3D_FEATURE_LEVEL level{};
    hr = D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr,
                           D3D11_CREATE_DEVICE_BGRA_SUPPORT, nullptr, 0,
                           D3D11_SDK_VERSION, &g_gpu.d3d, &level, nullptr);
    if (FAILED(hr)) {
        hr = D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_WARP, nullptr,
                               D3D11_CREATE_DEVICE_BGRA_SUPPORT, nullptr, 0,
                               D3D11_SDK_VERSION, &g_gpu.d3d, &level, nullptr);
    }
    if (FAILED(hr)) {
        Wh_Log(L"GpuInit: D3D11CreateDevice failed 0x%08lX", hr);
        return false;
    }

    IDXGIDevice* dxgi = nullptr;
    if (FAILED(g_gpu.d3d->QueryInterface(__uuidof(IDXGIDevice),
                                         (void**)&dxgi)) ||
        !dxgi) {
        Wh_Log(L"GpuInit: no IDXGIDevice");
        GpuShutdown();
        return false;
    }

    D2D1_FACTORY_OPTIONS opts{};
    hr = D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED,
                           __uuidof(ID2D1Factory1), &opts,
                           (void**)&g_gpu.factory);
    if (FAILED(hr) || !g_gpu.factory) {
        Wh_Log(L"GpuInit: D2D1CreateFactory failed 0x%08lX", hr);
        dxgi->Release();
        GpuShutdown();
        return false;
    }

    hr = g_gpu.factory->CreateDevice(dxgi, &g_gpu.d2d);
    dxgi->Release();
    if (FAILED(hr) || !g_gpu.d2d) {
        Wh_Log(L"GpuInit: D2D device failed 0x%08lX", hr);
        GpuShutdown();
        return false;
    }

    HMODULE dcomp = LoadLibraryW(L"dcomp.dll");
    using DCompCreateDevice2_t = HRESULT(WINAPI*)(IUnknown*, REFIID, void**);
    auto createDevice =
        (DCompCreateDevice2_t)GetProcAddress(dcomp, "DCompositionCreateDevice2");
    if (!createDevice) {
        Wh_Log(L"GpuInit: no DCompositionCreateDevice2");
        GpuShutdown();
        return false;
    }
    hr = createDevice(g_gpu.d2d, __uuidof(IDCompositionDevice),
                      (void**)&g_gpu.device);
    if (FAILED(hr) || !g_gpu.device) {
        Wh_Log(L"GpuInit: DCompositionCreateDevice2 failed 0x%08lX", hr);
        GpuShutdown();
        return false;
    }

    if (FAILED(g_gpu.device->CreateTargetForHwnd(g_hwnd, TRUE,
                                                 &g_gpu.target)) ||
        !g_gpu.target) {
        Wh_Log(L"GpuInit: CreateTargetForHwnd failed 0x%08lX", hr);
        GpuShutdown();
        return false;
    }
    if (FAILED(g_gpu.device->CreateVisual(&g_gpu.visual)) || !g_gpu.visual ||
        FAILED(g_gpu.device->CreateVirtualSurface(
            1, 1, DXGI_FORMAT_B8G8R8A8_UNORM, DXGI_ALPHA_MODE_PREMULTIPLIED,
            &g_gpu.surface)) ||
        !g_gpu.surface) {
        Wh_Log(L"GpuInit: visual/surface failed 0x%08lX", hr);
        GpuShutdown();
        return false;
    }
    g_gpu.visual->SetContent(g_gpu.surface);
    if (SUCCEEDED(g_gpu.device->CreateEffectGroup(&g_gpu.effect)) &&
        g_gpu.effect) {
        g_gpu.visual->SetEffect(g_gpu.effect);
    }
    g_gpu.target->SetRoot(g_gpu.visual);
    g_gpu.device->Commit();

    D2D1_STROKE_STYLE_PROPERTIES roundProps{};
    roundProps.startCap = D2D1_CAP_STYLE_ROUND;
    roundProps.endCap = D2D1_CAP_STYLE_ROUND;
    roundProps.lineJoin = D2D1_LINE_JOIN_ROUND;
    g_gpu.factory->CreateStrokeStyle(roundProps, nullptr, 0,
                                     &g_gpu.roundStroke);
    D2D1_STROKE_STYLE_PROPERTIES flatProps{};
    flatProps.startCap = D2D1_CAP_STYLE_FLAT;
    flatProps.endCap = D2D1_CAP_STYLE_FLAT;
    flatProps.lineJoin = D2D1_LINE_JOIN_MITER;
    g_gpu.factory->CreateStrokeStyle(flatProps, nullptr, 0,
                                     &g_gpu.flatStroke);

    BuildLockGeometries();

    hr = DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory),
                             (IUnknown**)&g_gpu.write);
    if (FAILED(hr) || !g_gpu.write) {
        Wh_Log(L"GpuInit: DWriteCreateFactory failed 0x%08lX", hr);
        GpuShutdown();
        return false;
    }

    g_gpu.inited = true;
    return true;
}

// --- drawing (mirrors the GDI+ RenderCard above, pixel for pixel) -----------

void EnsureBackdropBitmap(ID2D1DeviceContext* g) {
    if (g_gpu.backdropBitmap && g_gpu.backdropGen == g_backdrop.gen) {
        return;
    }
    GpuRelease(g_gpu.backdropBitmap);
    g_gpu.backdropGen = g_backdrop.gen;
    if (!g_backdrop.valid || !g_backdrop.image.bits) {
        return;
    }
    D2D1_BITMAP_PROPERTIES props =
        D2D1::BitmapProperties(D2D1_PIXEL_FORMAT{DXGI_FORMAT_B8G8R8A8_UNORM,
                                                 D2D1_ALPHA_MODE_IGNORE});
    g->CreateBitmap(
        D2D1_SIZE_U{(UINT)g_backdrop.image.width,
                    (UINT)g_backdrop.image.height},
        g_backdrop.image.bits, (UINT32)g_backdrop.image.stride, props,
        &g_gpu.backdropBitmap);
}

void EnsureCardShape(float width, float height) {
    int w = (int)std::lround(width);
    int h = (int)std::lround(height);
    if (g_gpu.cardShape && g_gpu.cardShapeW == w && g_gpu.cardShapeH == h) {
        return;
    }
    GpuRelease(g_gpu.cardShape);
    D2D1_ROUNDED_RECT rr =
        D2dRoundRect(0.0f, 0.0f, width, height,
                     (float)g_settings.cornerRadius * g_scale);
    g_gpu.factory->CreateRoundedRectangleGeometry(rr, &g_gpu.cardShape);
    g_gpu.cardShapeW = w;
    g_gpu.cardShapeH = h;
}

void DrawCardBorderD2d(ID2D1DeviceContext* g, float width, float height,
                       const Theme& theme) {
    float scale = height / kBaseHeight;
    int style = theme.highContrast ? 1 : g_settings.borderStyle;
    if (style == 2) {
        return;
    }

    float bw = (float)g_settings.borderWidth * scale;
    float radius =
        std::max(0.0f, (float)g_settings.cornerRadius * scale - bw / 2.0f);
    D2D1_ROUNDED_RECT ring = D2dRoundRect(bw / 2.0f, bw / 2.0f,
                                          width - bw, height - bw, radius);

    if (style == 1) {
        Color c = theme.highContrast ? theme.border : theme.accent;
        ID2D1SolidColorBrush* brush = nullptr;
        g->CreateSolidColorBrush(D2dColor(c), &brush);
        if (brush) {
            g->DrawRoundedRectangle(ring, brush, bw, g_gpu.flatStroke);
            brush->Release();
        }
        return;
    }

    float phase = MorphPhase();

    if (g_settings.glow > 0) {
        float wave = 0.5f + 0.5f * std::sin(phase * 6.2831853f);
        Color glowColor = MixColor(theme.accent, theme.accent2, wave, 255);
        float a = (float)g_settings.glow / 100.0f * 0.45f;
        // One soft halo hugging the border line only, clipped to the card so
        // the inside stays one even tone right up to the edge.
        EnsureCardShape(width, height);
        if (g_gpu.cardShape) {
            D2D1_LAYER_PARAMETERS lp = D2D1::LayerParameters();
            lp.contentBounds = D2D1_RECT_F{0.0f, 0.0f, width, height};
            lp.geometricMask = g_gpu.cardShape;
            lp.maskAntialiasMode = D2D1_ANTIALIAS_MODE_PER_PRIMITIVE;
            lp.maskTransform = D2D1::Matrix3x2F::Identity();
            lp.opacity = 1.0f;
            g->PushLayer(lp, nullptr);
            ID2D1SolidColorBrush* brush = nullptr;
            g->CreateSolidColorBrush(
                D2dColorAlpha(glowColor,
                              (BYTE)std::lround(255.0f * a)),
                &brush);
            if (brush) {
                g->DrawRoundedRectangle(ring, brush, bw + 2.0f * scale,
                                        g_gpu.roundStroke);
                brush->Release();
            }
            g->PopLayer();
        }
    }

    float vx = width * 1.2f;
    float vy = height * 0.4f;
    D2D1_POINT_2F p1{-vx + phase * vx, -vy + phase * vy};
    D2D1_POINT_2F p2{p1.x + vx, p1.y + vy};
    D2D1_GRADIENT_STOP stops[3] = {
        {0.0f, D2dColor(theme.accent)},
        {0.5f, D2dColor(theme.accent2)},
        {1.0f, D2dColor(theme.accent)},
    };
    ID2D1GradientStopCollection* stopCollection = nullptr;
    ID2D1LinearGradientBrush* brush = nullptr;
    if (SUCCEEDED(g->CreateGradientStopCollection(
            stops, 3, D2D1_GAMMA_2_2, D2D1_EXTEND_MODE_WRAP,
            &stopCollection)) &&
        stopCollection) {
        if (SUCCEEDED(g->CreateLinearGradientBrush(
                D2D1::LinearGradientBrushProperties(p1, p2), stopCollection,
                &brush)) &&
            brush) {
            g->DrawRoundedRectangle(ring, brush, bw, g_gpu.roundStroke);
            brush->Release();
        }
        stopCollection->Release();
    }
}

void DrawLockD2d(ID2D1DeviceContext* g, const D2D1_RECT_F& box,
                 const Theme& theme, float angle, float bounce) {
    if (!g_gpu.lockBody || !g_gpu.shackle) {
        return;
    }
    float s = (box.right - box.left) / 24.0f;
    D2D1::Matrix3x2F base =
        D2D1::Matrix3x2F::Translation(box.left, box.top) *
        D2D1::Matrix3x2F::Scale(D2D1_SIZE_F{s, s}, D2D1_POINT_2F{0.0f, 0.0f});

    ID2D1SolidColorBrush* brush = nullptr;
    g->CreateSolidColorBrush(D2dColor(theme.text), &brush);
    if (!brush) {
        return;
    }

    g->SetTransform(base);
    g->FillGeometry(g_gpu.lockBody, brush);
    // Keyhole: a 3-unit circle centred on (12, 14).
    g->FillEllipse(
        D2D1::Ellipse(D2D1_POINT_2F{12.0f, 14.0f}, 1.5f, 1.5f), brush);

    D2D1::Matrix3x2F shackle =
        base * D2D1::Matrix3x2F::Translation(16.0f, 7.0f + bounce) *
        D2D1::Matrix3x2F::Rotation(angle) *
        D2D1::Matrix3x2F::Translation(-16.0f, -7.0f);
    g->SetTransform(shackle);
    g->DrawGeometry(g_gpu.shackle, brush, 1.5f, g_gpu.flatStroke);

    g->SetTransform(D2D1::Matrix3x2F::Identity());
    brush->Release();
}

void DrawCheckD2d(ID2D1DeviceContext* g, const D2D1_RECT_F& box,
                  const Theme& theme, float progress) {
    float s = (box.right - box.left) / 24.0f;
    const D2D1_POINT_2F a{5.0f, 12.5f};
    const D2D1_POINT_2F b{10.0f, 17.5f};
    const D2D1_POINT_2F c{19.0f, 7.0f};
    float len1 = std::sqrt((b.x - a.x) * (b.x - a.x) +
                           (b.y - a.y) * (b.y - a.y));
    float len2 = std::sqrt((c.x - b.x) * (c.x - b.x) +
                           (c.y - b.y) * (c.y - b.y));
    float total = len1 + len2;
    float drawn = total * Clamp01(progress);
    if (drawn <= 0.01f) {
        return;
    }

    ID2D1PathGeometry* path = nullptr;
    if (FAILED(g_gpu.factory->CreatePathGeometry(&path)) || !path) {
        return;
    }
    ID2D1GeometrySink* sink = nullptr;
    if (FAILED(path->Open(&sink)) || !sink) {
        path->Release();
        return;
    }
    sink->BeginFigure(a, D2D1_FIGURE_BEGIN_HOLLOW);
    if (drawn <= len1) {
        float t = drawn / len1;
        sink->AddLine(D2D1_POINT_2F{Lerp(a.x, b.x, t), Lerp(a.y, b.y, t)});
    } else {
        sink->AddLine(b);
        float t = (drawn - len1) / len2;
        sink->AddLine(D2D1_POINT_2F{Lerp(b.x, c.x, t), Lerp(b.y, c.y, t)});
    }
    sink->EndFigure(D2D1_FIGURE_END_OPEN);
    sink->Close();
    sink->Release();

    D2D1::Matrix3x2F base =
        D2D1::Matrix3x2F::Translation(box.left, box.top) *
        D2D1::Matrix3x2F::Scale(D2D1_SIZE_F{s, s}, D2D1_POINT_2F{0.0f, 0.0f});
    ID2D1SolidColorBrush* brush = nullptr;
    g->CreateSolidColorBrush(D2dColor(theme.text), &brush);
    if (brush) {
        g->SetTransform(base);
        g->DrawGeometry(path, brush, 2.4f, g_gpu.roundStroke);
        g->SetTransform(D2D1::Matrix3x2F::Identity());
        brush->Release();
    }
    path->Release();
}

void DrawScissorsD2d(ID2D1DeviceContext* g, const D2D1_RECT_F& box,
                     const Theme& theme, float alpha) {
    EnsureGlyphFormat();
    if (!g_gpu.glyphFormat) {
        return;
    }
    static DText s_glyph;
    // The GDI+ path centres the glyph in a 24x18 box at y offset 3, in the
    // scaled unit space, so the layout gets the same box.
    if (!EnsureDText(s_glyph, L"\xE8C6", 16.0f, 400, g_gpu.glyphFormat, 0.7f,
                     24.0f, true)) {
        return;
    }
    s_glyph.layout->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);

    float s = (box.right - box.left) / 24.0f;
    D2D1::Matrix3x2F base =
        D2D1::Matrix3x2F::Translation(box.left, box.top) *
        D2D1::Matrix3x2F::Scale(D2D1_SIZE_F{s, s}, D2D1_POINT_2F{0.0f, 0.0f});
    ID2D1SolidColorBrush* brush = nullptr;
    g->CreateSolidColorBrush(
        D2dColorAlpha(theme.text, (BYTE)(255 * Clamp01(alpha))), &brush);
    if (brush) {
        g->SetTransform(base);
        g->DrawTextLayout(D2D1_POINT_2F{0.0f, 3.0f}, s_glyph.layout, brush,
                          D2D1_DRAW_TEXT_OPTIONS_NONE);
        g->SetTransform(D2D1::Matrix3x2F::Identity());
        brush->Release();
    }
}

// Lays out and draws the card into a DComp surface context that already has
// (0,0) at the window's top-left corner. Mirrors RenderCard exactly.
void RenderCardD2d(ID2D1DeviceContext* g, const FrameState& f,
                   const Theme& theme, bool barOnTop) {
    const float width = (float)g_cardWidth;
    const float height = (float)g_cardHeight;
    const float scale = g_scale;

    g->SetDpi(96.0f, 96.0f);
    g->SetAntialiasMode(D2D1_ANTIALIAS_MODE_PER_PRIMITIVE);
    g->SetTextAntialiasMode(D2D1_TEXT_ANTIALIAS_MODE_GRAYSCALE);
    g->SetTransform(D2D1::Matrix3x2F::Identity());

    std::wstring label;
    FormatTip(f.kind, f.on, label);

    // --- text metrics: GDI advances, so both renderers size the card alike --
    HDC screenDc = GetDC(nullptr);
    LOGFONTW textLogFont = MakeUiLogFont(14.0f * scale, g_settings.fontWeight);
    LOGFONTW badgeLogFont = MakeUiLogFont(12.5f * scale, g_settings.fontWeight);
    bool clip = IsClipKind(f.kind);
    float textWidth = MeasureTextWidth(screenDc, textLogFont, label);
    float badgeWidth = clip ? MeasureTextWidth(screenDc, badgeLogFont,
                                               CountText(f.count)) +
                                 14.0f * scale
                            : 0.0f;
    ReleaseDC(nullptr, screenDc);

    EnsureLabelFormats(14.0f * scale, 12.5f * scale);
    static DText s_label;
    static DText s_badge;
    bool haveLabel = EnsureDText(s_label, label, 14.0f * scale,
                                 g_settings.fontWeight, g_gpu.textFormat,
                                 g_gpu.textCapRatio, 4096.0f, false);
    float inkWidth = haveLabel && s_label.inkWidth > 0.0f ? s_label.inkWidth
                                                          : textWidth;
    float inkLSB = haveLabel ? s_label.inkLSB : 0.0f;

    // --- card ---------------------------------------------------------------
    D2D1_ROUNDED_RECT cardRect =
        D2dRoundRect(0.0f, 0.0f, width, height,
                     (float)g_settings.cornerRadius * scale);
    bool acrylic = g_settings.material != kMaterialSolid && g_backdrop.valid;
    if (acrylic) {
        EnsureBackdropBitmap(g);
        if (g_gpu.backdropBitmap) {
            // 1:1 copy from inside the padded capture: no scaling, so no
            // resampling fringe at the card edge.
            g->DrawBitmap(
                g_gpu.backdropBitmap, D2D1_RECT_F{0.0f, 0.0f, width, height},
                1.0f, D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR,
                D2D1_RECT_F{(float)g_backdrop.padLeft,
                            (float)g_backdrop.padTop,
                            (float)(g_backdrop.padLeft + g_backdrop.w),
                            (float)(g_backdrop.padTop + g_backdrop.h)});
        }
        ID2D1SolidColorBrush* tint = nullptr;
        g->CreateSolidColorBrush(D2dColor(theme.tint), &tint);
        if (tint) {
            g->FillRoundedRectangle(cardRect, tint);
            tint->Release();
        }
    } else {
        ID2D1SolidColorBrush* surface = nullptr;
        g->CreateSolidColorBrush(D2dColor(theme.surface), &surface);
        if (surface) {
            g->FillRoundedRectangle(cardRect, surface);
            surface->Release();
        }
    }

    // --- icon ---------------------------------------------------------------
    float gridShift = (!clip && barOnTop) ? 4.0f * scale : 0.0f;

    float iconSize = 22.0f * scale;
    const float iconInk = 14.0f / 24.0f * iconSize;
    const float clipGap = 12.0f * scale;
    const float clipGroupWidth =
        iconInk + clipGap + inkWidth + clipGap + badgeWidth;
    const float clipLeft = (width - clipGroupWidth) / 2.0f;
    D2D1_RECT_F iconBox(
        clip ? clipLeft - (iconSize - iconInk) / 2.0f : 16.0f * scale,
        (height - iconSize) / 2.0f - (clip ? 0.0f : 1.0f * scale) + gridShift,
        0.0f, 0.0f);
    iconBox.right = iconBox.left + iconSize;
    iconBox.bottom = iconBox.top + iconSize;

    float poseT = EaseOutQuad(f.statusT);
    float pose = Lerp(f.prevOn ? 1.0f : 0.0f, f.on ? 1.0f : 0.0f, poseT);
    if (clip) {
        if (f.kind == kCut) {
            DrawScissorsD2d(g, iconBox, theme, EaseOutQuad(f.clipT));
        } else {
            DrawCheckD2d(g, iconBox, theme, EaseOutQuad(f.clipT));
        }
    } else {
        float angle = Lerp(25.0f, 0.0f, pose);
        float t = Clamp01(f.statusT);
        float bounce = t < 0.1f ? EaseOutCubic(t / 0.1f)
                                : 1.0f - EaseInOutCubic((t - 0.1f) / 0.9f);
        DrawLockD2d(g, iconBox, theme, angle, bounce);
    }

    // --- text ---------------------------------------------------------------
    if (haveLabel) {
        float textX;
        if (clip) {
            textX = clipLeft + iconInk + clipGap;
        } else {
            float contentLeft = 16.0f * scale;
            float contentRight = width - 12.0f * scale;
            textX = (contentLeft + contentRight) / 2.0f - inkWidth / 2.0f +
                    18.0f * scale / 2.0f;
        }
        // The cap band centre rides at the target line, exactly where the
        // GDI+ path lands it (line box centre plus the probed cap bias).
        float capCenterY =
            clip ? height / 2.0f : height / 2.0f - 2.0f * scale + gridShift;
        ID2D1SolidColorBrush* brush = nullptr;
        g->CreateSolidColorBrush(D2dColor(theme.text), &brush);
        if (brush) {
            g->DrawTextLayout(
                D2D1_POINT_2F{textX - inkLSB, capCenterY - s_label.capCenter},
                s_label.layout, brush, D2D1_DRAW_TEXT_OPTIONS_NONE);
            brush->Release();
        }
    }

    // --- clipboard badge ----------------------------------------------------
    if (clip) {
        float badgeHeight = 18.0f * scale;
        float badgeX = clipLeft + iconInk + clipGap + inkWidth + clipGap;
        float badgeY = (height - badgeHeight) / 2.0f;
        float cx = badgeX + badgeWidth / 2.0f;
        float cy = badgeY + badgeHeight / 2.0f;

        D2D1::Matrix3x2F badgeTransform =
            D2D1::Matrix3x2F::Translation(cx, cy) *
            D2D1::Matrix3x2F::Scale(D2D1_SIZE_F{f.badgeScale, f.badgeScale},
                                    D2D1_POINT_2F{0.0f, 0.0f}) *
            D2D1::Matrix3x2F::Translation(-cx, -cy);
        g->SetTransform(badgeTransform);

        BYTE badgeAlpha = (BYTE)std::lround(255.0f * Clamp01(f.badgeAlpha));
        ID2D1SolidColorBrush* badgeBrush = nullptr;
        g->CreateSolidColorBrush(
            D2dColorAlpha(theme.accent, badgeAlpha), &badgeBrush);
        if (badgeBrush) {
            g->FillRoundedRectangle(
                D2dRoundRect(badgeX, badgeY, badgeWidth, badgeHeight,
                             9.0f * scale),
                badgeBrush);
            badgeBrush->Release();
        }

        if (EnsureDText(s_badge, CountText(f.count), 12.5f * scale,
                        g_settings.fontWeight, g_gpu.badgeFormat,
                        g_gpu.badgeCapRatio, badgeWidth, true)) {
            ID2D1SolidColorBrush* textBrush = nullptr;
            g->CreateSolidColorBrush(
                D2dColorAlpha(theme.onAccent, badgeAlpha), &textBrush);
            if (textBrush) {
                // The count's cap band sits at the badge's vertical middle.
                g->DrawTextLayout(
                    D2D1_POINT_2F{badgeX,
                                  badgeY + badgeHeight / 2.0f -
                                      s_badge.capCenter},
                    s_badge.layout, textBrush,
                    D2D1_DRAW_TEXT_OPTIONS_NONE);
                textBrush->Release();
            }
        }

        g->SetTransform(D2D1::Matrix3x2F::Identity());
    }

    // --- accent bar -----------------------------------------------------------
    if (!clip) {
        float indicatorHeight = 3.0f * scale;
        float indicatorWidth = Lerp(36.0f, 60.0f, pose) * scale;
        float indicatorY = barOnTop
                               ? 7.0f * scale
                               : height - 7.0f * scale - indicatorHeight;
        float indicatorX = (width - indicatorWidth) / 2.0f;
        BYTE alpha = (BYTE)std::lround(Lerp(0.2f, 1.0f, pose) * 255.0f);
        ID2D1SolidColorBrush* brush = nullptr;
        g->CreateSolidColorBrush(D2dColorAlpha(theme.accent, alpha), &brush);
        if (brush) {
            g->FillRoundedRectangle(
                D2dRoundRect(indicatorX, indicatorY, indicatorWidth,
                             indicatorHeight, indicatorHeight / 2.0f),
                brush);
            brush->Release();
        }
    }
}

// --- compositor plumbing -----------------------------------------------------

bool GpuEnsureSurface(int w, int h) {
    if (!g_gpu.device || w <= 0 || h <= 0) {
        return false;
    }
    if (g_gpu.surface && g_gpu.surfW == w && g_gpu.surfH == h) {
        return true;
    }
    if (!g_gpu.surface) {
        if (FAILED(g_gpu.device->CreateVirtualSurface(
                w, h, DXGI_FORMAT_B8G8R8A8_UNORM,
                DXGI_ALPHA_MODE_PREMULTIPLIED, &g_gpu.surface)) ||
            !g_gpu.surface) {
            return false;
        }
        g_gpu.visual->SetContent(g_gpu.surface);
    } else if (FAILED(g_gpu.surface->Resize(w, h))) {
        return false;
    }
    g_gpu.surfW = w;
    g_gpu.surfH = h;
    return true;
}

// Draws the current card state into the surface and commits. Called only when
// content actually changed; fades and slides never come through here.
bool GpuDrawFrame() {
    if (!GpuActive() || !g_hwnd) {
        return false;
    }
    if (!GpuEnsureSurface(g_cardWidth, g_cardHeight)) {
        GpuFailToGdi(L"Surface allocation failed");
        return false;
    }
    ID2D1DeviceContext* ctx = nullptr;
    HRESULT hr = g_gpu.surface->BeginDraw(nullptr, __uuidof(ID2D1DeviceContext),
                                          (void**)&ctx, nullptr);
    if (FAILED(hr) || !ctx) {
        GpuFailToGdi(L"BeginDraw failed");
        return false;
    }
    RenderCardD2d(ctx, g_frame, g_theme,
                  CardHangsTop(g_monitor, g_placement.x, g_placement.y,
                               (float)g_cardWidth, (float)g_cardHeight));
    ctx->Release();
    hr = g_gpu.surface->EndDraw();
    if (FAILED(hr)) {
        GpuFailToGdi(L"EndDraw failed");
        return false;
    }
    if (FAILED(g_gpu.device->Commit())) {
        GpuFailToGdi(L"Commit failed");
        return false;
    }
    return true;
}

// IDCompositionAnimation segments are cubic polynomials, so the exact ease
// curves from the GDI path encode as one segment each.
void GpuAddEase(IDCompositionAnimation* a, float seconds, float from, float to,
                bool easeOut) {
    float T = std::max(seconds, 0.001f);
    float dv = to - from;
    if (easeOut) {
        // v0 + dv * (3u - 3u^2 + u^3), u = t/T  (ease-out cubic)
        a->AddCubic(0.0, from, 3.0f * dv / T, -3.0f * dv / (T * T),
                    dv / (T * T * T));
    } else {
        // v0 + dv * u^3  (ease-in cubic)
        a->AddCubic(0.0, from, 0.0f, 0.0f, dv / (T * T * T));
    }
    a->End((double)T, to);
}

void GpuSnapStatic() {
    if (!g_gpu.device || !g_gpu.visual || !g_gpu.effect) {
        return;
    }
    g_gpu.effect->SetOpacity(1.0f);
    g_gpu.visual->SetOffsetX(0.0f);
    g_gpu.visual->SetOffsetY(0.0f);
    g_gpu.device->Commit();
}

void GpuStartShow(int animMs) {
    g_gpu.armed = 1;
    if (!g_gpu.device || !g_gpu.visual || !g_gpu.effect) {
        return;
    }
    if (animMs <= 0) {
        GpuSnapStatic();
        return;
    }
    float T = animMs / 1000.0f;
    IDCompositionAnimation* a = nullptr;
    if (SUCCEEDED(g_gpu.device->CreateAnimation(&a)) && a) {
        GpuAddEase(a, T, 0.0f, 1.0f, true);
        g_gpu.effect->SetOpacity(a);
        a->Release();
    }
    IDCompositionAnimation* b = nullptr;
    if (SUCCEEDED(g_gpu.device->CreateAnimation(&b)) && b) {
        GpuAddEase(b, T, (float)g_placement.dx, 0.0f, true);
        g_gpu.visual->SetOffsetX(b);
        b->Release();
    }
    IDCompositionAnimation* c = nullptr;
    if (SUCCEEDED(g_gpu.device->CreateAnimation(&c)) && c) {
        GpuAddEase(c, T, (float)g_placement.dy, 0.0f, true);
        g_gpu.visual->SetOffsetY(c);
        c->Release();
    }
    g_gpu.device->Commit();
}

void GpuStartHide(int animMs) {
    g_gpu.armed = 2;
    if (!g_gpu.device || !g_gpu.visual || !g_gpu.effect) {
        return;
    }
    if (animMs <= 0) {
        return;  // HideNow fires the same tick; nothing to animate
    }
    float T = animMs / 1000.0f;
    IDCompositionAnimation* a = nullptr;
    if (SUCCEEDED(g_gpu.device->CreateAnimation(&a)) && a) {
        GpuAddEase(a, T, 1.0f, 0.0f, false);
        g_gpu.effect->SetOpacity(a);
        a->Release();
    }
    IDCompositionAnimation* b = nullptr;
    if (SUCCEEDED(g_gpu.device->CreateAnimation(&b)) && b) {
        GpuAddEase(b, T, 0.0f, (float)g_placement.dx, false);
        g_gpu.visual->SetOffsetX(b);
        b->Release();
    }
    IDCompositionAnimation* c = nullptr;
    if (SUCCEEDED(g_gpu.device->CreateAnimation(&c)) && c) {
        GpuAddEase(c, T, 0.0f, (float)g_placement.dy, false);
        g_gpu.visual->SetOffsetY(c);
        c->Release();
    }
    g_gpu.device->Commit();
}

// Runs on every animation timer tick while the GPU path is armed. The
// compositor owns opacity and offset; this only redraws the surface when the
// content itself moves (state tweens, morphing border).
void GpuStepAnimation(bool tweenBusy) {
    if (g_phase == kPhaseHidden) {
        return;
    }
    if (g_phase == kPhaseIn && g_gpu.armed != 1) {
        GpuStartShow(g_animMs);
    } else if (g_phase == kPhaseOut && g_gpu.armed != 2) {
        GpuStartHide(g_animMs);
    } else if (g_phase == kPhaseHold && g_gpu.armed != 0) {
        g_gpu.armed = 0;  // the finished animation pins its final value
    }
    if (tweenBusy || BorderIsMorphing()) {
        GpuDrawFrame();
    }
}

void GpuApplyRenderer() {
    if (g_settings.renderer == 0) {
        if (!g_gpu.inited && g_hwnd) {
            if (GpuInit()) {
                Wh_Log(L"WinTips OSD renderer armed: gpu (DirectComposition + Direct2D)");
            } else {
                UseLayeredStyle(true);
                Wh_Log(L"WinTips OSD renderer armed: gdi (legacy; DirectComposition init failed)");
            }
        }
    } else if (g_gpu.inited) {
        GpuShutdown();
        UseLayeredStyle(true);
        Wh_Log(L"WinTips OSD renderer armed: gdi (legacy; selected in settings)");
    }
}

// =============================================================================
// Runtime state
// =============================================================================

HWND g_hwnd;
HHOOK g_hook;
DWORD g_hookThreadId;
HANDLE g_uiThread;
HANDLE g_hookThread;
HANDLE g_readyEvent;
ULONG_PTR g_gdiplusToken;

Surface g_surface;
float g_scale = 1.0f;
Theme g_theme;
FrameState g_frame;
Placement g_placement;
int g_cardWidth;
int g_cardHeight;

Phase g_phase = kPhaseHidden;
ULONGLONG g_phaseStart;
int g_animMs;
int g_statusMs;
ULONGLONG g_statusStart;
int g_clipMs;
ULONGLONG g_clipStart;
ULONGLONG g_badgeStart;
bool g_badgePop;
bool g_badgeFade;
int g_count;
TipKind g_currentKind = kCapsLock;
ULONGLONG g_lastShowTick;
bool g_clipIntentActive;
TipKind g_clipIntentKind = kCopy;
volatile LONG g_pollEnabled = 1;

// Hook thread only.
bool g_vkDown[256];
bool g_toggleState[3];
ULONGLONG g_hookToggleTick[3]; // last press reported by the hook, per lock key
int g_pollMismatch[3];         // consecutive disagreeing polls, per lock key

// =============================================================================
// Keyboard helpers
// =============================================================================

int KindToVk(TipKind kind) {
    switch (kind) {
        case kCapsLock:
            return VK_CAPITAL;
        case kNumLock:
            return VK_NUMLOCK;
        case kScrollLock:
            return VK_SCROLL;
        case kInsert:
            return VK_INSERT;
        case kCopy:
            return 'C';
        case kPaste:
            return 'V';
        default:
            return 'X';
    }
}

int KindFromVk(DWORD vk) {
    switch (vk) {
        case VK_CAPITAL:
            return kCapsLock;
        case VK_NUMLOCK:
            return kNumLock;
        case VK_SCROLL:
            return kScrollLock;
        case VK_INSERT:
            return kInsert;
        default:
            return -1;
    }
}

int ClipKindFromVk(DWORD vk) {
    switch (vk) {
        case 'C':
            return kCopy;
        case 'V':
            return kPaste;
        case 'X':
            return kCut;
        default:
            return -1;
    }
}

// =============================================================================
// Environment checks
// =============================================================================

// The standalone WinTips.exe holds this mutex while it runs. When both are
// installed we stay quiet instead of drawing a second overlay on top of it.
bool OtherInstanceRunning() {
    HANDLE mutex = OpenMutexW(SYNCHRONIZE, FALSE, L"Local\\WinTips.SingleInstance");
    if (!mutex) {
        return false;
    }
    CloseHandle(mutex);
    return true;
}

bool FullscreenActive() {
    QUERY_USER_NOTIFICATION_STATE state;
    if (SUCCEEDED(SHQueryUserNotificationState(&state))) {
        if (state == QUNS_BUSY || state == QUNS_RUNNING_D3D_FULL_SCREEN ||
            state == QUNS_PRESENTATION_MODE) {
            return true;
        }
    }

    HWND foreground = GetForegroundWindow();
    if (!foreground) {
        return false;
    }
    RECT rect;
    if (!GetWindowRect(foreground, &rect)) {
        return false;
    }
    HMONITOR monitor = MonitorFromWindow(foreground, MONITOR_DEFAULTTONEAREST);
    MONITORINFO info{};
    info.cbSize = sizeof(info);
    if (!GetMonitorInfoW(monitor, &info)) {
        return false;
    }
    if (!EqualRect(&rect, &info.rcMonitor)) {
        return false;
    }
    wchar_t className[64]{};
    GetClassNameW(foreground, className, 64);
    return wcscmp(className, L"Progman") != 0 &&
           wcscmp(className, L"WorkerW") != 0;
}

bool ClipboardHasContent() {
    static const UINT formats[] = {CF_UNICODETEXT, CF_HDROP,     CF_BITMAP,
                                   CF_DIB,        CF_ENHMETAFILE, CF_METAFILEPICT};
    for (UINT format : formats) {
        if (IsClipboardFormatAvailable(format)) {
            return true;
        }
    }
    return false;
}

// =============================================================================
// Presentation
// =============================================================================

void UpdateGeometry() {
    // The pointer may have moved to another display since the last tip, so the
    // target monitor (and with it the DPI scale) is re-resolved every time.
    if (!ResolveTargetMonitor()) {
        LoadMonitor(MonitorFromPoint(POINT{0, 0}, MONITOR_DEFAULTTOPRIMARY),
                    g_monitor);
    }
    if (g_monitor.valid) {
        g_scale = g_monitor.scale;
    }
    MeasureCard(g_scale, g_frame, g_cardWidth, g_cardHeight);
    g_placement =
        ComputePlacement((float)g_cardWidth, (float)g_cardHeight, g_scale);
    g_surface.Ensure(g_cardWidth, g_cardHeight);
}

// Grabs the pixels behind the card and blurs them. The window has to be hidden
// while doing it, otherwise the copy would contain the previous card.
// Other always-on-top windows (settings panels, pinned windows) share the
// topmost band, and a plain show leaves the card wherever it last sat in that
// band. Lift it to the front of the band every time it appears, and keep it
// there while it shows, since some overlays re-raise themselves.
void ShowCardOnTop() {
    if (!g_hwnd) {
        return;
    }
    SetWindowPos(g_hwnd, HWND_TOPMOST, 0, 0, 0, 0,
                 SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE | SWP_SHOWWINDOW);
    SetTimer(g_hwnd, kTimerTop, 100, nullptr);
}

void KeepCardOnTop() {
    if (!g_hwnd || !IsWindowVisible(g_hwnd)) {
        if (g_hwnd) {
            KillTimer(g_hwnd, kTimerTop);
        }
        return;
    }
    SetWindowPos(g_hwnd, HWND_TOPMOST, 0, 0, 0, 0,
                 SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE | SWP_NOOWNERZORDER);
}

void RefreshBackdrop() {
    if (!g_hwnd || g_settings.material == kMaterialSolid) {
        g_backdrop.Invalidate();
        return;
    }
    if (g_backdrop.Matches(g_placement.x, g_placement.y, g_cardWidth,
                           g_cardHeight)) {
        return;
    }

    bool wasVisible = IsWindowVisible(g_hwnd) != FALSE;
    if (wasVisible) {
        ShowWindow(g_hwnd, SW_HIDE);
    }

    int radius = (int)std::lround((float)g_settings.blurRadius * g_scale);
    HDC screen = GetDC(nullptr);
    CaptureBackdrop(screen, g_placement.x, g_placement.y, g_cardWidth,
                    g_cardHeight, radius);
    ReleaseDC(nullptr, screen);

    if (wasVisible) {
        ShowCardOnTop();
    }
}

void Present(float dx, float dy, BYTE alpha) {
    if (!g_surface.dc || !g_hwnd) {
        return;
    }

    g_surface.Clear();
    {
        Graphics g(g_surface.dc);
        RenderCard(g, g_scale, (float)g_cardWidth, (float)g_cardHeight, g_frame,
                   g_theme,
                   CardHangsTop(g_monitor, g_placement.x, g_placement.y,
                                (float)g_cardWidth, (float)g_cardHeight));
    }
    g_surface.Premultiply();

    HDC screen = GetDC(nullptr);
    POINT src{0, 0};
    SIZE size{g_cardWidth, g_cardHeight};
    POINT dst{g_placement.x + (int)std::lround(dx),
              g_placement.y + (int)std::lround(dy)};

    BLENDFUNCTION blend{};
    blend.BlendOp = AC_SRC_OVER;
    blend.SourceConstantAlpha = alpha;
    blend.AlphaFormat = AC_SRC_ALPHA;

    UpdateLayeredWindow(g_hwnd, screen, &dst, &size, g_surface.dc, &src, 0,
                        &blend, ULW_ALPHA);
    ReleaseDC(nullptr, screen);
}

void HideNow() {
    if (g_hwnd) {
        ShowWindow(g_hwnd, SW_HIDE);
        KillTimer(g_hwnd, kTimerAnim);
        KillTimer(g_hwnd, kTimerTop);
    }
    g_phase = kPhaseHidden;
    g_gpu.armed = 0;
    g_count = 0;
    g_badgePop = false;
    // The desktop may have changed while the card was up; capture again next
    // time instead of replaying a stale snapshot.
    g_backdrop.Invalidate();
}

void StepAnimation() {
    if (!g_hwnd) {
        return;
    }

    ULONGLONG now = GetTickCount64();
    float alpha = 1.0f;
    float dx = 0.0f;
    float dy = 0.0f;

    if (g_phase == kPhaseIn) {
        float t = g_animMs > 0 ? (float)(now - g_phaseStart) / g_animMs : 1.0f;
        float e = EaseOutCubic(t);
        alpha = e;
        dx = g_placement.dx * (1.0f - e);
        dy = g_placement.dy * (1.0f - e);
        if (t >= 1.0f) {
            g_phase = kPhaseHold;
        }
    } else if (g_phase == kPhaseOut) {
        float t = g_animMs > 0 ? (float)(now - g_phaseStart) / g_animMs : 1.0f;
        float e = EaseInCubic(t);
        alpha = 1.0f - e;
        dx = g_placement.dx * e;
        dy = g_placement.dy * e;
        if (t >= 1.0f) {
            HideNow();
            return;
        }
    }

    bool busy = g_phase == kPhaseIn || g_phase == kPhaseOut;
    bool tweenBusy = false;

    if (g_statusMs > 0) {
        float t = (float)(now - g_statusStart) / g_statusMs;
        g_frame.statusT = Clamp01(t);
        busy = busy || t < 1.0f;
        tweenBusy = tweenBusy || t < 1.0f;
    } else {
        g_frame.statusT = 1.0f;
    }

    if (IsClipKind(g_frame.kind)) {
        if (g_clipMs > 0) {
            float t = (float)(now - g_clipStart) / g_clipMs;
            g_frame.clipT = Clamp01(t);
            busy = busy || t < 1.0f;
            tweenBusy = tweenBusy || t < 1.0f;
        } else {
            g_frame.clipT = 1.0f;
        }

        if (g_badgePop && g_animMs > 0) {
            float t = (float)(now - g_badgeStart) / g_animMs;
            if (t < 1.0f) {
                busy = true;
                tweenBusy = true;
                g_frame.badgeScale =
                    t < 0.3f ? Lerp(1.0f, 1.3f, EaseOutCubic(t / 0.3f))
                             : Lerp(1.3f, 1.0f, EaseInOutCubic((t - 0.3f) / 0.7f));
            } else {
                g_frame.badgeScale = 1.0f;
                g_badgePop = false;
            }
        }

        if (g_badgeFade && g_statusMs > 0) {
            float t = (float)(now - g_badgeStart) / g_statusMs;
            g_frame.badgeAlpha = Clamp01(t);
            busy = busy || t < 1.0f;
            tweenBusy = tweenBusy || t < 1.0f;
        } else if (!g_badgeFade) {
            g_frame.badgeAlpha = 1.0f;
        }
    }

    if (GpuActive()) {
        GpuStepAnimation(tweenBusy);
    } else {
        Present(dx, dy, (BYTE)std::lround(255.0f * Clamp01(alpha)));
    }

    if (g_phase == kPhaseHold && !busy && !BorderIsMorphing()) {
        KillTimer(g_hwnd, kTimerAnim);
    }
}

void StartStatusTween(bool fromOn) {
    ULONGLONG now = GetTickCount64();
    int animMs = g_settings.AnimationMs();
    g_statusMs = animMs > 0 ? std::max(1, (int)(animMs / 1.5f)) : 0;
    g_statusStart = now;
    g_clipMs = g_statusMs;
    g_clipStart = now;
    g_badgeStart = now;

    g_frame.prevOn = fromOn;
    g_frame.statusT = g_statusMs > 0 ? 0.0f : 1.0f;
    g_frame.clipT = g_clipMs > 0 ? 0.0f : 1.0f;
    g_frame.badgeAlpha = g_badgeFade ? 0.0f : 1.0f;
    g_frame.badgeScale = 1.0f;
}

void ShowTip(TipKind kind, bool on) {
    bool wasVisible = g_phase != kPhaseHidden;
    bool clip = IsClipKind(kind);

    bool fromOn = wasVisible ? g_frame.on : !on;

    if (clip) {
        bool same = wasVisible && g_currentKind == kind;
        g_count = same ? g_count + 1 : 1;
        g_badgePop = same;
        g_badgeFade = !same;
    } else {
        g_count = 0;
        g_badgePop = false;
        g_badgeFade = false;
    }

    g_currentKind = kind;
    g_lastShowTick = GetTickCount64();

    g_frame.kind = kind;
    g_frame.on = on;
    g_frame.count = g_count;

    g_theme = CurrentTheme();
    UpdateGeometry();
    RefreshBackdrop();

    int animMs = g_settings.AnimationMs();
    g_animMs = animMs;
    StartStatusTween(fromOn);

    if (GpuActive() && g_hwnd) {
        // Draw the first frame before the window shows, size the window for
        // the compositor (ULW does that per frame on the GDI path), and cancel
        // a pending fade-out if a new tip arrived while one was running.
        GpuDrawFrame();
        SetWindowPos(g_hwnd, HWND_TOPMOST, g_placement.x, g_placement.y,
                     g_cardWidth, g_cardHeight, SWP_NOACTIVATE);
        if (wasVisible && g_phase == kPhaseHold) {
            GpuSnapStatic();
        }
    }

    if (!wasVisible) {
        g_phase = animMs > 0 ? kPhaseIn : kPhaseHold;
        g_phaseStart = GetTickCount64();
        if (animMs <= 0) {
            g_frame.statusT = 1.0f;
            g_frame.clipT = 1.0f;
            g_frame.badgeAlpha = 1.0f;
        }
        ShowCardOnTop();
    } else if (g_phase == kPhaseOut) {
        // A tip arrived while the card was fading out: keep it on screen
        // instead of letting the pending hide finish.
        g_phase = kPhaseHold;
        g_phaseStart = GetTickCount64();
        ShowCardOnTop();
    } else {
        ShowCardOnTop();
    }

    if (g_hwnd) {
        SetTimer(g_hwnd, kTimerAnim, 16, nullptr);
        KillTimer(g_hwnd, kTimerHold);
        SetTimer(g_hwnd, kTimerHold,
                 (UINT)Clamp(g_settings.displayMs, 500, 10000), nullptr);
    }

    StepAnimation();
}

void BeginHide() {
    if (g_phase == kPhaseHidden) {
        return;
    }
    if (g_hwnd) {
        KillTimer(g_hwnd, kTimerHold);
    }
    int animMs = g_settings.AnimationMs();
    if (animMs <= 0) {
        HideNow();
        return;
    }
    g_animMs = animMs;
    g_phase = kPhaseOut;
    g_phaseStart = GetTickCount64();
    if (g_hwnd) {
        SetTimer(g_hwnd, kTimerAnim, 16, nullptr);
    }
}

// =============================================================================
// Tip handling
// =============================================================================

bool ShouldSkip(bool honorFullscreen) {
    if (OtherInstanceRunning()) {
        return true;
    }
    if (honorFullscreen && g_settings.suppressFullscreen && FullscreenActive()) {
        return true;
    }
    return false;
}

void HandleTip(TipKind kind, bool predictedOn) {
    if (!g_settings.notify[kind]) {
        return;
    }
    if (ShouldSkip(true)) {
        return;
    }

    if (IsToggleKind(kind)) {
        // The hook thread already predicted the post-toggle state from its own
        // (authoritative) key state; a key-up message corrects it if wrong.
        ShowTip(kind, predictedOn);
        return;
    }

    if (kind == kInsert || kind == kPaste) {
        ShowTip(kind, false);
        return;
    }

    // Copy and cut are only reported once the clipboard really changed; this is
    // what keeps Ctrl+C in a console window from showing a false "Copied".
    g_clipIntentActive = true;
    g_clipIntentKind = kind;
    if (g_hwnd) {
        KillTimer(g_hwnd, kTimerClip);
        SetTimer(g_hwnd, kTimerClip, kClipIntentMs, nullptr);
    }
}

// A toggle seen only by the polling fallback (elevated window in front).
void HandlePoll(TipKind kind, bool state) {
    if (g_phase != kPhaseHidden && kind == g_currentKind &&
        g_frame.on == state) {
        return;
    }
    if (!g_settings.notify[kind]) {
        return;
    }
    if (ShouldSkip(true)) {
        return;
    }
    ShowTip(kind, state);
}

void HandleClipboardUpdate() {
    if (g_clipIntentActive) {
        g_clipIntentActive = false;
        if (g_hwnd) {
            KillTimer(g_hwnd, kTimerClip);
        }
        ShowTip(g_clipIntentKind, false);
        return;
    }

    if (!g_settings.notify[kCopy] || !g_settings.notifyAnyCopy) {
        return;
    }
    if (!ClipboardHasContent()) {
        return;
    }
    // Clipboard managers read and write the same data right after a copy; those
    // back-to-back updates must not show a second tip.
    if (GetTickCount64() - g_lastShowTick < kClipMergeMs) {
        return;
    }
    if (ShouldSkip(true)) {
        return;
    }
    ShowTip(kCopy, false);
}

void ApplySettings() {
    LoadSettings();
    DetectLanguage();
    InterlockedExchange(&g_pollEnabled, g_settings.pollElevated ? 1 : 0);
    GpuApplyRenderer();
    g_theme = CurrentTheme();
    g_backdrop.Invalidate();
    if (g_phase != kPhaseHidden) {
        UpdateGeometry();
        RefreshBackdrop();
        if (GpuActive()) {
            GpuDrawFrame();
        }
        StepAnimation();
    }
}

void OnTimer(UINT_PTR id) {
    switch (id) {
        case kTimerAnim:
            StepAnimation();
            break;
        case kTimerHold:
            BeginHide();
            break;
        case kTimerTop:
            KeepCardOnTop();
            break;
        case kTimerClip:
            if (g_hwnd) {
                KillTimer(g_hwnd, kTimerClip);
            }
            g_clipIntentActive = false;
            break;
        default:
            break;
    }
}

void OnDisplayChanged() {
    g_theme = CurrentTheme();
    if (g_phase != kPhaseHidden) {
        UpdateGeometry();
        StepAnimation();
    } else if (ResolveTargetMonitor()) {
        g_scale = g_monitor.scale;
    }
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
        case WM_APP_TIP:
            HandleTip((TipKind)wParam, lParam != 0);
            return 0;
        case WM_APP_POLL:
            HandlePoll((TipKind)wParam, lParam != 0);
            return 0;
        case WM_APP_SETTINGS:
            ApplySettings();
            return 0;
        case WM_APP_QUIT:
            PostQuitMessage(0);
            return 0;
        case WM_CLIPBOARDUPDATE:
            HandleClipboardUpdate();
            return 0;
        case WM_TIMER:
            OnTimer((UINT_PTR)wParam);
            return 0;
        case WM_DISPLAYCHANGE:
        case WM_DPICHANGED:
        case WM_SETTINGCHANGE:
            OnDisplayChanged();
            return 0;
        case WM_NCHITTEST:
            return HTTRANSPARENT;
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
        default:
            break;
    }
    return DefWindowProcW(hwnd, msg, wParam, lParam);
}

// =============================================================================
// Threads
// =============================================================================

constexpr wchar_t kWindowClass[] = L"WindhawkWinTipsOsd";

DWORD WINAPI UiThreadProc(LPVOID) {
    // Only this thread gets per-monitor DPI awareness; the host process
    // (windhawk.exe) must keep whatever mode it already has.
    HMODULE user32 = GetModuleHandleW(L"user32.dll");
    if (user32) {
        auto setContext = (SetThreadDpiAwarenessContext_t)GetProcAddress(
            user32, "SetThreadDpiAwarenessContext");
        if (setContext) {
            setContext(DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2);
        }
    }

    GdiplusStartupInput input;
    if (GdiplusStartup(&g_gdiplusToken, &input, nullptr) != Ok) {
        Wh_Log(L"GdiplusStartup failed");
        return 0;
    }

    if (ResolveTargetMonitor()) {
        g_scale = g_monitor.scale;
    }

    WNDCLASSEXW wc{};
    wc.cbSize = sizeof(wc);
    wc.lpfnWndProc = WndProc;
    wc.hInstance = GetModuleHandleW(nullptr);
    wc.lpszClassName = kWindowClass;
    wc.hCursor = LoadCursorW(nullptr, IDC_ARROW);
    RegisterClassExW(&wc);

    // The GPU path owns the window content through DirectComposition, which
    // cannot coexist with UpdateLayeredWindow, so the layered style is added
    // only when the GDI path is the one armed.
    g_hwnd = CreateWindowExW(
        WS_EX_TRANSPARENT | WS_EX_NOACTIVATE | WS_EX_TOOLWINDOW | WS_EX_TOPMOST,
        kWindowClass, L"WinTipsOSD", WS_POPUP, 0, 0, 1, 1, nullptr, nullptr,
        GetModuleHandleW(nullptr), nullptr);

    if (!g_hwnd) {
        Wh_Log(L"CreateWindowEx failed: %lu", GetLastError());
        GdiplusShutdown(g_gdiplusToken);
        return 0;
    }

    AddClipboardFormatListener(g_hwnd);

    if (g_settings.renderer == 0 && GpuInit()) {
        Wh_Log(L"WinTips OSD renderer armed: gpu (DirectComposition + Direct2D)");
    } else {
        UseLayeredStyle(true);
        if (g_settings.renderer == 0) {
            Wh_Log(L"WinTips OSD renderer armed: gdi (legacy; DirectComposition init failed)");
        } else {
            Wh_Log(L"WinTips OSD renderer armed: gdi (legacy; selected in settings)");
        }
        g_gpu.failed = g_settings.renderer == 0;
    }

    if (g_readyEvent) {
        SetEvent(g_readyEvent);
    }

    MSG msg;
    while (GetMessageW(&msg, nullptr, 0, 0) > 0) {
        TranslateMessage(&msg);
        DispatchMessageW(&msg);
    }

    RemoveClipboardFormatListener(g_hwnd);
    g_surface.Release();
    GpuShutdown();
    DestroyWindow(g_hwnd);
    g_hwnd = nullptr;
    GdiplusShutdown(g_gdiplusToken);
    return 0;
}

void PollTick() {
    if (InterlockedCompareExchange(&g_pollEnabled, 1, 1) == 0) {
        return;
    }
    ULONGLONG now = GetTickCount64();
    for (int kind = 0; kind <= kScrollLock; kind++) {
        // A toggle the hook just reported is already on its way to the screen.
        // Reading the state inside that window races the system and would make
        // the card flip back and forth, so corrections wait it out.
        if (now - g_hookToggleTick[kind] < kPollQuietMs) {
            g_pollMismatch[kind] = 0;
            continue;
        }
        bool actual =
            (GetKeyState(KindToVk((TipKind)kind)) & 1) != 0;
        if (actual == g_toggleState[kind]) {
            g_pollMismatch[kind] = 0;
            continue;
        }
        // A single odd sample is usually the thread's cached key state lagging
        // behind; only act once two polls in a row agree.
        if (++g_pollMismatch[kind] < 2) {
            continue;
        }
        g_pollMismatch[kind] = 0;
        g_toggleState[kind] = actual;
        if (g_hwnd) {
            PostMessageW(g_hwnd, WM_APP_POLL, (WPARAM)kind, actual ? 1 : 0);
        }
    }
}

LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) {
    if (nCode == HC_ACTION) {
        auto* info = (KBDLLHOOKSTRUCT*)lParam;
        DWORD vk = info->vkCode & 0xFF;
        bool down = wParam == WM_KEYDOWN || wParam == WM_SYSKEYDOWN;
        bool up = wParam == WM_KEYUP || wParam == WM_SYSKEYUP;

        if (down) {
            // Ignore auto-repeat so holding a key fires exactly once.
            if (!g_vkDown[vk]) {
                g_vkDown[vk] = true;

                int kind = KindFromVk(vk);
                if (kind < 0 &&
                    (g_vkDown[VK_LCONTROL] || g_vkDown[VK_RCONTROL] ||
                     g_vkDown[VK_CONTROL] ||
                     (GetAsyncKeyState(VK_CONTROL) & 0x8000) != 0)) {
                    kind = ClipKindFromVk(vk);
                }

                if (kind >= 0) {
                    bool predicted = false;
                    if (IsToggleKind((TipKind)kind)) {
                        // Flip our own copy of the state instead of reading the
                        // key here: a lock key toggles exactly once per press,
                        // so tracking it is exact even for rapid taps, while a
                        // read this early sometimes still returns the old value
                        // and would make the card flip back a moment later.
                        predicted = !g_toggleState[kind];
                        g_toggleState[kind] = predicted;
                        g_hookToggleTick[kind] = GetTickCount64();
                    }
                    if (g_hwnd) {
                        PostMessageW(g_hwnd, WM_APP_TIP, (WPARAM)kind,
                                     predicted ? 1 : 0);
                    }
                }
            }
        } else if (up) {
            g_vkDown[vk] = false;

            int kind = KindFromVk(vk);
            if (kind >= 0 && IsToggleKind((TipKind)kind)) {
                // The polling fallback must not fight the press we just
                // reported; give the system a moment to settle first.
                g_hookToggleTick[kind] = GetTickCount64();
            }
        }
    }

    return CallNextHookEx(g_hook, nCode, wParam, lParam);
}

DWORD WINAPI HookThreadProc(LPVOID) {
    g_hookThreadId = GetCurrentThreadId();

    // Seed the known state so the polling fallback doesn't report a bogus tip
    // for keys that are already on when the mod loads.
    for (int kind = 0; kind <= kScrollLock; kind++) {
        g_toggleState[kind] = (GetKeyState(KindToVk((TipKind)kind)) & 1) != 0;
    }

    HMODULE module = nullptr;
    GetModuleHandleExW(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS |
                           GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT,
                       (LPCWSTR)&LowLevelKeyboardProc, &module);

    g_hook = SetWindowsHookExW(WH_KEYBOARD_LL, LowLevelKeyboardProc, module, 0);
    if (!g_hook) {
        Wh_Log(L"SetWindowsHookExW failed: %lu", GetLastError());
    }

    // Thread timer drives the elevated-window fallback; the low-level hook only
    // runs while this thread pumps messages.
    SetTimer(nullptr, 0, kPollMs, nullptr);

    MSG msg;
    while (GetMessageW(&msg, nullptr, 0, 0) > 0) {
        if (msg.hwnd == nullptr && msg.message == WM_TIMER) {
            PollTick();
            continue;
        }
        TranslateMessage(&msg);
        DispatchMessageW(&msg);
    }

    if (g_hook) {
        UnhookWindowsHookEx(g_hook);
        g_hook = nullptr;
    }
    return 0;
}

}  // namespace

// =============================================================================
// Windhawk tool mod entry points
// =============================================================================

BOOL WhTool_ModInit() {
    DetectLanguage();
    LoadSettings();
    InterlockedExchange(&g_pollEnabled, g_settings.pollElevated ? 1 : 0);

    g_readyEvent = CreateEventW(nullptr, TRUE, FALSE, nullptr);
    g_uiThread = CreateThread(nullptr, 0, UiThreadProc, nullptr, 0, nullptr);
    if (!g_uiThread) {
        Wh_Log(L"Failed to start the UI thread");
        return FALSE;
    }

    if (g_readyEvent) {
        WaitForSingleObject(g_readyEvent, 5000);
    }

    g_hookThread = CreateThread(nullptr, 0, HookThreadProc, nullptr, 0, nullptr);
    if (!g_hookThread) {
        Wh_Log(L"Failed to start the hook thread");
    }

    Wh_Log(L"WinTips OSD started");
    return TRUE;
}

void WhTool_ModSettingsChanged() {
    if (g_hwnd) {
        PostMessageW(g_hwnd, WM_APP_SETTINGS, 0, 0);
    }
}

void WhTool_ModUninit() {
    if (g_hwnd) {
        PostMessageW(g_hwnd, WM_APP_QUIT, 0, 0);
    }
    if (g_uiThread) {
        WaitForSingleObject(g_uiThread, 3000);
        CloseHandle(g_uiThread);
        g_uiThread = nullptr;
    }
    if (g_hookThreadId) {
        PostThreadMessageW(g_hookThreadId, WM_QUIT, 0, 0);
    }
    if (g_hookThread) {
        WaitForSingleObject(g_hookThread, 3000);
        CloseHandle(g_hookThread);
        g_hookThread = nullptr;
    }
    if (g_readyEvent) {
        CloseHandle(g_readyEvent);
        g_readyEvent = nullptr;
    }
    Wh_Log(L"WinTips OSD stopped");
}

////////////////////////////////////////////////////////////////////////////////
// Windhawk tool mod implementation for mods which don't need to inject to other
// processes or hook other functions. Context:
// https://github.com/ramensoftware/windhawk/wiki/Mods-as-tools:-Running-mods-in-a-dedicated-process
//
// The mod will load and run in a dedicated windhawk.exe process.
//
// Paste the code below as part of the mod code, and use these callbacks:
// * WhTool_ModInit
// * WhTool_ModSettingsChanged
// * WhTool_ModUninit
//
// Currently, other callbacks are not supported.

bool g_isToolModProcessLauncher;
HANDLE g_toolModProcessMutex;

void WINAPI EntryPoint_Hook() {
    Wh_Log(L">");
    ExitThread(0);
}

BOOL Wh_ModInit() {
    DWORD sessionId;
    if (ProcessIdToSessionId(GetCurrentProcessId(), &sessionId) &&
        sessionId == 0) {
        return FALSE;
    }

    bool isExcluded = false;
    bool isToolModProcess = false;
    bool isCurrentToolModProcess = false;
    int argc;
    LPWSTR* argv = CommandLineToArgvW(GetCommandLine(), &argc);
    if (!argv) {
        Wh_Log(L"CommandLineToArgvW failed");
        return FALSE;
    }

    for (int i = 1; i < argc; i++) {
        if (wcscmp(argv[i], L"-service") == 0 ||
            wcscmp(argv[i], L"-service-start") == 0 ||
            wcscmp(argv[i], L"-service-stop") == 0) {
            isExcluded = true;
            break;
        }
    }

    for (int i = 1; i < argc - 1; i++) {
        if (wcscmp(argv[i], L"-tool-mod") == 0) {
            isToolModProcess = true;
            if (wcscmp(argv[i + 1], WH_MOD_ID) == 0) {
                isCurrentToolModProcess = true;
            }
            break;
        }
    }

    LocalFree(argv);

    if (isExcluded) {
        return FALSE;
    }

    if (isCurrentToolModProcess) {
        g_toolModProcessMutex =
            CreateMutex(nullptr, TRUE, L"windhawk-tool-mod_" WH_MOD_ID);
        if (!g_toolModProcessMutex) {
            Wh_Log(L"CreateMutex failed");
            ExitProcess(1);
        }

        if (GetLastError() == ERROR_ALREADY_EXISTS) {
            Wh_Log(L"Tool mod already running (%s)", WH_MOD_ID);
            ExitProcess(1);
        }

        if (!WhTool_ModInit()) {
            ExitProcess(1);
        }

        IMAGE_DOS_HEADER* dosHeader =
            (IMAGE_DOS_HEADER*)GetModuleHandle(nullptr);
        IMAGE_NT_HEADERS* ntHeaders =
            (IMAGE_NT_HEADERS*)((BYTE*)dosHeader + dosHeader->e_lfanew);

        DWORD entryPointRVA = ntHeaders->OptionalHeader.AddressOfEntryPoint;
        void* entryPoint = (BYTE*)dosHeader + entryPointRVA;

        Wh_SetFunctionHook(entryPoint, (void*)EntryPoint_Hook, nullptr);
        return TRUE;
    }

    if (isToolModProcess) {
        return FALSE;
    }

    g_isToolModProcessLauncher = true;
    return TRUE;
}

void Wh_ModAfterInit() {
    if (!g_isToolModProcessLauncher) {
        return;
    }

    WCHAR currentProcessPath[MAX_PATH];
    switch (GetModuleFileName(nullptr, currentProcessPath,
                              ARRAYSIZE(currentProcessPath))) {
        case 0:
        case ARRAYSIZE(currentProcessPath):
            Wh_Log(L"GetModuleFileName failed");
            return;
    }

    WCHAR
    commandLine[MAX_PATH + 2 +
                (sizeof(L" -tool-mod \"" WH_MOD_ID "\"") / sizeof(WCHAR)) - 1];
    swprintf_s(commandLine, L"\"%s\" -tool-mod \"%s\"", currentProcessPath,
               WH_MOD_ID);

    HMODULE kernelModule = GetModuleHandle(L"kernelbase.dll");
    if (!kernelModule) {
        kernelModule = GetModuleHandle(L"kernel32.dll");
        if (!kernelModule) {
            Wh_Log(L"No kernelbase.dll/kernel32.dll");
            return;
        }
    }

    using CreateProcessInternalW_t = BOOL(WINAPI*)(
        HANDLE hUserToken, LPCWSTR lpApplicationName, LPWSTR lpCommandLine,
        LPSECURITY_ATTRIBUTES lpProcessAttributes,
        LPSECURITY_ATTRIBUTES lpThreadAttributes, WINBOOL bInheritHandles,
        DWORD dwCreationFlags, LPVOID lpEnvironment, LPCWSTR lpCurrentDirectory,
        LPSTARTUPINFOW lpStartupInfo,
        LPPROCESS_INFORMATION lpProcessInformation,
        PHANDLE hRestrictedUserToken);
    CreateProcessInternalW_t pCreateProcessInternalW =
        (CreateProcessInternalW_t)GetProcAddress(kernelModule,
                                                 "CreateProcessInternalW");
    if (!pCreateProcessInternalW) {
        Wh_Log(L"No CreateProcessInternalW");
        return;
    }

    STARTUPINFO si{
        .cb = sizeof(STARTUPINFO),
        .dwFlags = STARTF_FORCEOFFFEEDBACK,
    };
    PROCESS_INFORMATION pi;
    if (!pCreateProcessInternalW(nullptr, currentProcessPath, commandLine,
                                 nullptr, nullptr, FALSE, NORMAL_PRIORITY_CLASS,
                                 nullptr, nullptr, &si, &pi, nullptr)) {
        Wh_Log(L"CreateProcess failed");
        return;
    }

    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
}

void Wh_ModSettingsChanged() {
    if (g_isToolModProcessLauncher) {
        return;
    }

    WhTool_ModSettingsChanged();
}

void Wh_ModUninit() {
    if (g_isToolModProcessLauncher) {
        return;
    }

    WhTool_ModUninit();
    ExitProcess(0);
}
