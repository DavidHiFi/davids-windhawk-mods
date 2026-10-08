// ==WindhawkMod==
// @id              windhawk-styler
// @name            Windhawk Styler
// @description     Theme Windhawk itself with your own colors, font, transparency and blur
// @version         2.0.33
// @author          DavidHiFi
// @github          https://github.com/DavidHiFi
// @homepage        https://github.com/DavidHiFi/davids-windhawk-mods
// @license         MIT
// @include         windhawk-ui.exe
// @architecture    x86-64
// @compilerOptions -DWIN32_LEAN_AND_MEAN -luser32 -lgdi32 -ldwmapi -lws2_32 -ladvapi32 -lcomctl32 -luxtheme
// ==/WindhawkMod==

// ==WindhawkModReadme==
/*
# Windhawk Styler

Choose Windhawk's colors, font, transparency and background blur.

![Windhawk Styler preview](https://raw.githubusercontent.com/DavidHiFi/davids-windhawk-mods/main/media/previews/windhawk-styler.png)

## Features

- **Background.** Pick a color and opacity, with Acrylic or no background effect.
- **Cards and dialogs.** Set their color and opacity. Translucent dialogs and pop-up menus blur the content behind them.
- **Controls.** Choose colors for buttons and inputs, plus an accent for selections and links.
- **Text and font.** Use an installed font and a text color. Icons keep their own font.
- **Title bar.** Match the background or choose a solid color. The app icon keeps its normal size, and Windows handles dragging and window buttons.
- **Removal.** Disable the mod and reopen the interface to return to Windhawk's appearance. The mod changes no application files.

## How to use

This edition requires Windows 11 and the 64-bit Windhawk 2.0 Tauri interface. It was tested with Windhawk 2.0.0-alpha.6.

Open the mod's Settings tab, choose your appearance and save. Saving briefly closes and reopens the Windhawk interface to apply the settings.

Colors use `#RRGGBB`. Opacity runs from 0 for transparent to 100 for solid. Leave an optional color or font blank to use Windhawk's choice. The title bar keeps the Windows caption font.

## Notes

Windows transparency and animation settings can affect the background material. Other mods that style this window can conflict with its appearance.

For the older Windhawk interface, use the [legacy 1.4.0 edition](legacy/). It has a separate source and settings.

## Credits

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
  $description: "0 is transparent, 100 is solid. Translucent dialogs and menus blur what is behind them"
- controlColor: "#313244"
  $name: Button and input color
  $description: "Buttons, text boxes and drop-down controls. Leave blank for Windhawk's colors"
- accentColor: "#89b4fa"
  $name: Accent color
  $description: "Selected buttons, switches, tabs and links. Leave blank for Windhawk's colors"
- textColor: "#cdd6f4"
  $name: Text color
  $description: "Body and title bar text. Leave blank for Windhawk's colors"
- fontFamily: "Segoe UI"
  $name: Font
  $description: "Use an installed font for the interface. Leave blank for Windhawk's font. The title bar keeps the Windows font"
- nativeTitleBar: true
  $name: Style the title bar
  $description: "Apply the theme to the title bar and keep the normal Windows buttons"
- titleBarAcrylic: true
  $name: Match the title bar to the background
  $description: "Use the same color and transparency as the background. Turn off for a solid title bar"
- titleBarColor: "#403a45"
  $name: Solid title bar color
  $description: "Used when Match the title bar to the background is off. Enter a color in #RRGGBB format"
*/
// ==/WindhawkModSettings==

#include <winsock2.h>
#include <ws2tcpip.h>
#include <windhawk_utils.h>
#include <windows.h>
#include <dwmapi.h>
#include <uxtheme.h>
#include <vssym32.h>
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
    std::string control;
    std::string accent;
    std::string text;
    std::uint32_t textRgb = 0;            // RRGGBB; s.text records whether a color is set
    std::wstring font;
    bool nativeTitleBar = true;
    std::uint32_t titleBarRgb = 0x403a45;  // RRGGBB
    bool titleBarColorSet = true;
    bool titleBarAcrylic = true;
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
static bool g_pageReady;

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

    s->control.clear();
    std::uint32_t controlRgb;
    PCWSTR control = Wh_GetStringSetting(L"controlColor");
    if (HexColorToRgb(control, &controlRgb)) s->control = RgbToCss(controlRgb);
    Wh_FreeStringSetting(control);

    s->accent.clear();
    std::uint32_t accentRgb;
    PCWSTR accent = Wh_GetStringSetting(L"accentColor");
    if (HexColorToRgb(accent, &accentRgb)) s->accent = RgbToCss(accentRgb);
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

    s->nativeTitleBar = Wh_GetIntSetting(L"nativeTitleBar") != 0;
    s->titleBarAcrylic = Wh_GetIntSetting(L"titleBarAcrylic") != 0;

    s->titleBarColorSet = false;
    std::uint32_t titleBarRgb;
    PCWSTR titleBar = Wh_GetStringSetting(L"titleBarColor");
    if (HexColorToRgb(titleBar, &titleBarRgb)) {
        s->titleBarRgb = titleBarRgb;
        s->titleBarColorSet = true;
    }
    Wh_FreeStringSetting(titleBar);

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

static std::string CssVeil(const Settings& s) {
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

static std::string BuildCss(const Settings& s) {
    // One client surface tints the caption and body over the same acrylic.
    std::string veil = CssVeil(s);
    std::string css;
    css += ":root{";
    css += "--whui-background-color:" + veil + " !important;";
    std::string cardColor = CssCardColor(s);
    if (!cardColor.empty()) {
        css += "--whui-card-background-color:" + cardColor + " !important;";
        css += "--whui-modal-background-color:" + cardColor + " !important;";
    }
    if (!s.accent.empty()) css += "--whui-primary:" + s.accent + " !important;";
    if (!s.text.empty()) {
        css += "--whui-text-secondary:" + s.text + " !important;";
        css += "--whui-editor-fg:" + s.text + " !important;";
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
    css += "}";
    css += "[data-testid=mod-setting-reset]{margin-inline-start:0!important;}";
    if (!cardColor.empty()) {
        css += ".ant-card{background-color:" + cardColor + " !important;border-color:rgba(255,255,255,0.08) !important;}";
        css += ".ant-modal-content,.ant-drawer-content,.ant-popover-inner,.ant-select-dropdown,.ant-dropdown-menu{background-color:" + cardColor + " !important;backdrop-filter:blur(24px);}";
        css += ".ant-modal-header,.ant-modal-footer,.ant-drawer-header,.ant-drawer-body,.ant-drawer-footer,.ant-popover-title{background:transparent !important;}";
        css += ".ant-modal-title,.ant-popover-title{color:var(--whui-text-secondary) !important;}";
        if (s.cardOpacity < 100) {
            css += "[class*=\"SaveSettingsCard\"]{backdrop-filter:blur(16px);}";
        }
    }
    if (!s.control.empty()) {
        css += ".ant-btn{background-color:" + s.control + " !important;border-color:rgba(255,255,255,0.12) !important;}";
        css += ".ant-input,.ant-input-affix-wrapper,.ant-select-selector,.ant-input-number{background-color:" + s.control + " !important;}";
        if (cardColor.empty()) css += ".ant-dropdown-menu{background-color:" + s.control + " !important;}";
    }
    if (!s.accent.empty()) {
        css += ".ant-btn-primary{background-color:" + s.accent + " !important;border-color:" + s.accent + " !important;color:#11111b !important;}";
        css += ".ant-switch-checked{background-color:" + s.accent + " !important;}";
        css += ".ant-tabs-tab-active .ant-tabs-tab-btn{color:" + s.accent + " !important;}";
        css += ".ant-menu-item-selected{color:" + s.accent + " !important;}";
        css += "a{color:" + s.accent + " !important;}";
        css += ".ant-radio-checked .ant-radio-inner{border-color:" + s.accent + " !important;}";
        css += ".ant-checkbox-checked .ant-checkbox-inner{background-color:" + s.accent + " !important;border-color:" + s.accent + " !important;}";
    }
    if (s.nativeTitleBar && s.titleBarAcrylic) {
        int caption = GetSystemMetricsForDpi(SM_CYCAPTION, 96) +
                      GetSystemMetricsForDpi(SM_CYFRAME, 96) +
                      GetSystemMetricsForDpi(SM_CXPADDEDBORDER, 96);
        std::string height = std::to_string(caption) + "px";
        css += "#root{margin-top:" + height + ";height:calc(100% - " + height + ") !important;}";
    }
    return css;
}

static std::string BuildInjectJs(const Settings& s) {
    std::string css = BuildCss(s);
    std::string js;
    js += "(function(){";
    js += "if(location.hostname!=='tauri.localhost'||!document.querySelector('[data-testid=nav-home]')||!document.querySelector('[data-testid=nav-explore]'))return 'loading';";
    js += "var css=\"" + JsonEscape(css) + "\";";
    js += "var st=document.getElementById('wh-styler-style');";
    js += "if(!st){st=document.createElement('style');st.id='wh-styler-style';(document.head||document.documentElement).appendChild(st);}";
    js += "if(st.textContent!==css)st.textContent=css;";
    js += "return 'ok len='+css.length;";
    js += "})()";
    return js;
}

static std::string BuildCleanupJs() {
    return "(function(){var st=document.getElementById('wh-styler-style');if(st&&st.parentNode){st.parentNode.removeChild(st);}})()";
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
    BOOL activeLook = s.nativeTitleBar && s.titleBarAcrylic && s.blur;
    WINCOMPATTRDATA appearance{WCA_FORCE_ACTIVEWINDOW_APPEARANCE, &activeLook, sizeof(activeLook)};
    SetWindowCompositionAttribute(hWnd, &appearance);
    // DWM draws the backdrop and border with the system's current corner radius.
    int intValue = 1;
    DwmSetWindowAttribute(hWnd, DWMWA_USE_IMMERSIVE_DARK_MODE, &intValue, sizeof(intValue));
    intValue = s.blur == 2 ? 3 : 1;  // DWMSBT_TRANSIENTWINDOW or DWMSBT_NONE
    DwmSetWindowAttribute(hWnd, DWMWA_SYSTEMBACKDROP_TYPE, &intValue, sizeof(intValue));
    MARGINS margins = {-1, -1, -1, -1};
    DwmExtendFrameIntoClientArea(hWnd, &margins);
    if (s.nativeTitleBar) {
        // With the acrylic title bar the caption color stays NONE: the strip
        // then shows the same system acrylic backdrop as the client, which is
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

    // The accepted Acrylic mode uses DWM. Blur and None use the accent
    // policy so disabling Acrylic does not silently keep its material.
    if (!s.titleBarAcrylic || s.blur != 2) {
        ACCENT_POLICY policy = {};
        policy.AccentState = s.blur == 2 ? ACCENT_ENABLE_ACRYLICBLURBEHIND :
                             s.blur == 1 ? ACCENT_ENABLE_BLURBEHIND :
                                           ACCENT_ENABLE_TRANSPARENTGRADIENT;
        policy.AccentFlags = 2;
        policy.GradientColor = s.blur == 2 ? 0x10000000 | Bgr(s.background) : 0;
        WINCOMPATTRDATA data{WCA_ACCENT_POLICY, &policy, sizeof(policy)};
        SetWindowCompositionAttribute(hWnd, &data);
    }
    if (s.blur == 0) {
        ACCENT_POLICY policy = {};
        WINCOMPATTRDATA data{WCA_ACCENT_POLICY, &policy, sizeof(policy)};
        SetWindowCompositionAttribute(hWnd, &data);
        // An empty blur region enables alpha composition without blurring it.
        HRGN region = CreateRectRgn(0, 0, -1, -1);
        if (region) {
            DWM_BLURBEHIND blur{DWM_BB_ENABLE | DWM_BB_BLURREGION, TRUE, region, FALSE};
            DwmEnableBlurBehindWindow(hWnd, &blur);
            DeleteObject(region);
        }
    }
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

static std::map<HWND, RECT> g_captionChildren;
static std::mutex g_captionChildrenMutex;

static void CropCaptionChild(HWND child) {
    if (!InterlockedExchangeAdd(&g_themeActive, 0)) return;
    HWND owner = GetParent(child);
    if (!owner || !IsOurMainUiWindow(owner)) return;
    wchar_t cls[64];
    GetClassNameW(child, cls, 64);
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
        if (SUCCEEDED(GetBufferedPaintBits(buffer, &pixels, &stride))) {
            int alpha = std::clamp(s.backgroundOpacity, 0, 100) * 255 / 100;
            RGBQUAD tint{BYTE((s.background & 255) * alpha / 255),
                         BYTE(((s.background >> 8) & 255) * alpha / 255),
                         BYTE(((s.background >> 16) & 255) * alpha / 255), BYTE(alpha)};
            for (int y = 0; y < client.bottom; ++y) {
                std::fill_n(pixels + y * stride, client.right, tint);
            }
        }
        UINT dpi = GetDpiForWindow(hwnd);
        NONCLIENTMETRICSW metrics{sizeof(metrics)};
        SystemParametersInfoForDpi(SPI_GETNONCLIENTMETRICS, sizeof(metrics), &metrics, 0, dpi);
        HFONT font = CreateFontIndirectW(&metrics.lfCaptionFont);
        HGDIOBJ oldFont = font ? SelectObject(paintDc, font) : nullptr;
        HTHEME theme = OpenThemeData(hwnd, L"WINDOW");
        int icon = GetSystemMetricsForDpi(SM_CXSMICON, dpi);
        int inset = MulDiv(12, dpi, 96);
        if (theme) {
            wchar_t title[512];
            GetWindowTextW(hwnd, title, 512);
            RECT text{inset + icon + MulDiv(8, dpi, 96), 0, client.right - MulDiv(160, dpi, 96), client.bottom};
            DTTOPTS options{sizeof(options)};
            options.dwFlags = DTT_COMPOSITED | DTT_TEXTCOLOR;
            options.crText = s.text.empty() ? RGB(255,255,255) : Bgr(s.textRgb);
            DrawThemeTextEx(theme, paintDc, WP_CAPTION, CS_ACTIVE, title, -1,
                            DT_SINGLELINE | DT_VCENTER | DT_END_ELLIPSIS | DT_NOPREFIX, &text, &options);
            CloseThemeData(theme);
        }
        HICON logo = (HICON)SendMessageW(hwnd, WM_GETICON, ICON_SMALL, 0);
        if (!logo) logo = (HICON)GetClassLongPtrW(hwnd, GCLP_HICONSM);
        if (logo) DrawIconEx(paintDc, inset, (client.bottom-icon)/2, logo, icon, icon, 0, nullptr, DI_NORMAL);
        if (oldFont) SelectObject(paintDc, oldFont);
        if (font) DeleteObject(font);
        EndBufferedPaint(buffer, TRUE);
    }
    BufferedPaintUnInit();
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

// Keep activation visual only; keyboard focus and WM_ACTIVATE retain their real state.
static LRESULT CALLBACK MainWindowProc(HWND hwnd, UINT message, WPARAM wparam,
                                      LPARAM lparam, DWORD_PTR) {
    if (!InterlockedExchangeAdd(&g_themeActive, 0)) {
        return DefSubclassProc(hwnd, message, wparam, lparam);
    }
    Settings s = SnapshotSettings();
    if (IntegratedCaption(s) && message == WM_NCHITTEST) {
        LRESULT hit = 0;
        if (DwmDefWindowProc(hwnd, message, wparam, lparam, &hit)) return hit;
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
            return HTCAPTION;
        }
    }
    if (message == WM_NCCALCSIZE && wparam) {
        RECT frameRect = *reinterpret_cast<const RECT*>(lparam);
        DefSubclassProc(hwnd, message, wparam, lparam);
        RECT* client = reinterpret_cast<RECT*>(lparam);
        if (IntegratedCaption(s)) {
            int inset = IsZoomed(hwnd) ? GetSystemMetricsForDpi(SM_CYFRAME, GetDpiForWindow(hwnd)) +
                                        GetSystemMetricsForDpi(SM_CXPADDEDBORDER, GetDpiForWindow(hwnd)) : 0;
            client->top = frameRect.top + inset;
        }
        if (!IsZoomed(hwnd)) {
            client->left = frameRect.left;
            client->right = frameRect.right;
            client->bottom = frameRect.bottom;
        }
        return 0;
    }
    if (message == WM_NCACTIVATE && s.nativeTitleBar && s.titleBarAcrylic && s.blur) {
        return DefSubclassProc(hwnd, message, TRUE, lparam);
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

static void PrepareMainWindow(HWND hwnd) {
    if (!g_mainWindows.contains(hwnd)) {
        RECT frame{}, client{};
        POINT origin{};
        bool preserveClient = !IsZoomed(hwnd) && GetWindowRect(hwnd, &frame) &&
                              GetClientRect(hwnd, &client) && ClientToScreen(hwnd, &origin);
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
        int want = s.blur == 2 ? 3 : 1;  // DWMSBT_TRANSIENTWINDOW or DWMSBT_NONE
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
    unsigned char orig[36];
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
            VirtualProtect(site, (SIZE_T)g_patches[i].origLen, oldProtect, &oldProtect);
        }
        g_patches[i].site = nullptr;
        unsigned char* cave = g_caves[i].cave;
        if (cave) {
            DWORD oldProtect = 0;
            if (VirtualProtect(cave, sizeof(g_caves[i].orig), PAGE_EXECUTE_READWRITE, &oldProtect)) {
                memcpy(cave, g_caves[i].orig, sizeof(g_caves[i].orig));
                VirtualProtect(cave, sizeof(g_caves[i].orig), oldProtect, &oldProtect);
            }
            g_caves[i].cave = nullptr;
        }
    }
    InterlockedExchange(&g_patchCount, 0);
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
    // padding, executable, unused). The stub masks the alpha byte of the
    // by-value color argument (EDX, whose low byte is COREWEBVIEW2_COLOR.A)
    // and TAIL-JUMPS to the original target: the stack state the callee sees
    // is then byte-for-byte the original direct call's, which keeps the
    // callee's stack alignment intact (an extra call frame shifts rsp by 8
    // and the runtime's movaps stores fault on it).
    //   mov dl, 0                  B2 00
    //   jmp qword ptr [rax+0xD8]   FF A0 D8 00 00 00
    const unsigned char pattern[8] = {0xFF, 0x90, 0xD8, 0x00, 0x00, 0x00, 0x85, 0xC0};
    // the tail padding starts after VirtualSize, 16-aligned
    unsigned char* tailBase = (unsigned char*)(((std::uintptr_t)(codeLO + codeSize) + 15) & ~15);
    unsigned char* tailEnd = (unsigned char*)(((std::uintptr_t)(codeLO + ((codeSize + 0xfff) & ~(std::size_t)0xfff))));
    if (tailEnd - tailBase < 128) {
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
        if (idx >= 16) break;
        unsigned char* cave = tailBase + (SIZE_T)idx * 32;

        // build the stub in the cave (32 bytes reserved each)
        DWORD tmp = 0;
        if (!VirtualProtect(cave, 32, PAGE_EXECUTE_READWRITE, &tmp)) {
            DebugNote("cave protect failed", GetLastError());
            continue;
        }
        unsigned char* stub = cave;
        stub[0] = 0xB2; stub[1] = 0x00;                      // mov dl, 0
        stub[2] = 0xFF; stub[3] = 0xA0;                      // jmp qword ptr [rax+0xD8]
        memcpy(stub + 4, &pattern[2], 4);                    // D8 00 00 00
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
        for (int b = 5; b < origLen; b++) p[b] = 0x90;
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

static bool HttpGetJson(int port, const char* path, std::string* out) {
    SOCKET sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sock == INVALID_SOCKET) return false;
    sockaddr_in addr = {};
    addr.sin_family = AF_INET;
    addr.sin_port = htons((u_short)port);
    addr.sin_addr.s_addr = htonl(0x7f000001);  // 127.0.0.1
    if (connect(sock, (sockaddr*)&addr, sizeof(addr)) != 0) {
        closesocket(sock);
        return false;
    }
    DWORD timeout = 3000;
    setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, (char*)&timeout, sizeof(timeout));
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
        if (out->size() > (1 << 22)) break;
    }
    closesocket(sock);
    size_t bodyAt = out->find("\r\n\r\n");
    if (bodyAt == std::string::npos) return false;
    *out = out->substr(bodyAt + 4);
    return out->find("tauri.localhost") != std::string::npos &&
           out->find("webSocketDebuggerUrl") != std::string::npos;
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

    SOCKET sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sock == INVALID_SOCKET) return false;
    sockaddr_in addr = {};
    addr.sin_family = AF_INET;
    addr.sin_port = htons((u_short)port);
    addr.sin_addr.s_addr = htonl(0x7f000001);
    if (connect(sock, (sockaddr*)&addr, sizeof(addr)) != 0) {
        closesocket(sock);
        return false;
    }
    DWORD timeout = 4000;
    setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, (char*)&timeout, sizeof(timeout));
    setsockopt(sock, SOL_SOCKET, SO_SNDTIMEO, (char*)&timeout, sizeof(timeout));

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

// Push the theme CSS; the surface alpha is handled by the patched put sites.
static bool CdpPushTheme(int port, const std::string& wsUrl, const std::string& jsExpression) {
    SOCKET sock;
    if (!WsConnect(port, wsUrl, &sock)) return false;
    std::string req = "{\"id\":10,\"method\":\"Runtime.evaluate\",\"params\":{\"expression\":\"" + JsonEscape(jsExpression) + "\",\"returnByValue\":true}}";
    std::string f1;
    WsEncodeFrame(req, &f1);
    bool ok = false;
    if (SendAll(sock, f1.c_str(), (int)f1.size())) {
        std::string msg;
        int opcode;
        for (int i = 0; i < 20; i++) {
            if (!WsReadMessage(sock, &msg, &opcode)) break;
            if (opcode != 0x1) continue;
            if (msg.find("\"id\":10") != std::string::npos) {
                ok = msg.find("\"error\"") == std::string::npos && msg.find("\"value\":\"ok") != std::string::npos;
                break;
            }
        }
    }
    shutdown(sock, SD_BOTH);
    closesocket(sock);
    return ok;
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
    int failLogged = 0;

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
        DWORD wait = MsgWaitForMultipleObjectsEx(1, &g_stopEvent, 1000, QS_ALLINPUT, MWMO_INPUTAVAILABLE);
        if (wait == WAIT_OBJECT_0) break;
        MSG msg;
        while (PeekMessageW(&msg, nullptr, 0, 0, PM_REMOVE)) DispatchMessageW(&msg);
        if (wait == WAIT_OBJECT_0 + 1) continue;  // the events already ran their sync

        // re-read the registry every cycle: cheap, and it pins the live look
        // to the settings even if a settings-changed event is missed
        Settings s;
        ReadSettings(&s);
        {
            std::lock_guard<std::mutex> lock(g_settingsMutex);
            g_settings = s;
        }
        ApplyToOurWindows(s);
        MainWindowPass();

        // Save watch: one registry read per cycle. A save bumps the engine's
        // marker; both this path and the settings-changed event feed the same
        // request flag below, so a missed event cannot swallow the restart.
        long long changeTime = ReadModChangeTime();
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

        {
            std::string json;
            if (HttpGetJson(kCdpPort, "/json", &json)) {
                std::string wsUrl;
                if (JsonStringValue(json, "webSocketDebuggerUrl", &wsUrl)) {
                    std::string js = BuildInjectJs(s);
                    bool pushed = CdpPushTheme(kCdpPort, wsUrl, js);
                    if (pushed) g_pageReady = true;
                    if (!pushed && failLogged < 3) {
                        failLogged++;
                        DebugNote("push failed");
                    }
                }
            } else if (failLogged < 1) {
                failLogged++;
                DebugNote("http get failed");
            }
        }

        MainWindowPass();
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
    long long last = InterlockedExchange64(&lastRelaunchTick, 0);
    if (last != 0 && now - (unsigned long long)last < 4000) return FALSE;
    InterlockedExchange64(&lastRelaunchTick, (long long)now);

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
        L"$env:WEBVIEW2_ADDITIONAL_BROWSER_ARGUMENTS='--remote-debugging-port=9333'\n"
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

    wchar_t cmdLine[10240];
    _snwprintf(cmdLine, 10240,
        L"\"C:\\Windows\\System32\\WindowsPowerShell\\v1.0\\powershell.exe\" -NoProfile -ExecutionPolicy Bypass -EncodedCommand %S", b64);

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

static void* g_webview = nullptr;

BOOL Wh_ModInit() {
    Wh_Log(L">");

    g_startTick = GetTickCount64();
    ReadSettings(&g_settings);
    // Seed the save watch with the marker as it stands now: a fresh boot (or
    // a hot-swap after a compile) records it without triggering, and only a
    // later bump restarts the interface.
    g_seenChangeTime = ReadModChangeTime();

    // Ask the WebView2 loader for a local debugging port, so the mod can push
    // the theme tokens and the font into the interface's own page. Must be set
    // before the webview environment is created, which is why this runs in the
    // process's earliest startup.
    {
        wchar_t args[64];
        swprintf(args, 64, L"--remote-debugging-port=%u", kCdpPort);
        SetEnvironmentVariableW(L"WEBVIEW2_ADDITIONAL_BROWSER_ARGUMENTS", args);
    }

    g_stopEvent = CreateEvent(nullptr, TRUE, FALSE, nullptr);
    if (g_stopEvent) {
        g_workerThread = CreateThread(nullptr, 0, StylerWorkerThread, nullptr, 0, nullptr);
    }

    InitFrameWatch();
    if (!Wh_SetFunctionHook((void*)BitBlt, (void*)BitBlt_hook, (void**)&BitBlt_orig)) {
        DebugNote("startup splash hook failed");
    }
    PatchPutSites();

    return TRUE;
}

void Wh_ModUninit() {
    Wh_Log(L">");
    InterlockedExchange(&g_themeActive, 0);
    InterlockedExchange(&g_relaunchRequested, 0);
    if (g_stopEvent) {
        SetEvent(g_stopEvent);
        if (g_workerThread) {
            WaitForSingleObject(g_workerThread, 6000);
            CloseHandle(g_workerThread);
            g_workerThread = nullptr;
        }
        CloseHandle(g_stopEvent);
        g_stopEvent = nullptr;
    }
    // Best effort: drop the injected style from the page, restore the window's
    // stock frame and the runtime's put call sites, so the interface reverts
    // when the mod goes away.
    if (g_webview) {
        void** vtw = *(void***)g_webview;
        Settings s;
        {
            std::lock_guard<std::mutex> lock(g_settingsMutex);
            s = g_settings;
        }
        std::string js = BuildCleanupJs();
        int wlen = MultiByteToWideChar(CP_UTF8, 0, js.c_str(), -1, nullptr, 0);
        wchar_t* wjs = (wchar_t*)LocalAlloc(LPTR, (SIZE_T)wlen * 2);
        if (wjs) {
            MultiByteToWideChar(CP_UTF8, 0, js.c_str(), -1, wjs, wlen);
            // slot 29 = ExecuteScript
            typedef HRESULT (STDMETHODCALLTYPE* ExecScript_t)(void*, wchar_t*, void*);
            ((ExecScript_t)vtw[29])(g_webview, wjs, nullptr);
            LocalFree(wjs);
        }
    }
    HWND hWnd = nullptr;
    for (;;) {
        hWnd = FindWindowExW(nullptr, hWnd, L"WindhawkTauriMainUI", nullptr);
        if (!hWnd) break;
        if (IsOurMainUiWindow(hWnd)) ClearWindowStack(hWnd);
    }
    std::lock_guard<std::mutex> captionLock(g_captionChildrenMutex);
    for (auto& [child, size] : g_captionChildren) {
        if (IsWindow(child)) SetWindowRgn(child, nullptr, TRUE);
    }
    g_captionChildren.clear();
    WindhawkUtils::RemoveAllWindowSubclasses();
    g_mainWindows.clear();
    RestorePatches();
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
    // Both save paths feed the same restart request.
    InterlockedExchange(&g_relaunchRequested, 1);
}
