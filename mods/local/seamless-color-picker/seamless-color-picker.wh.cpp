// ==WindhawkMod==
// @id              seamless-color-picker
// @name            Seamless Color Picker
// @description     A full color picker on a hotkey, with a screen magnifier, recent colors and one-click copy
// @version         1.0.0
// @author          DavidHiFi, Jaex, ShareX contributors
// @github          https://github.com/DavidHiFi
// @homepage        https://github.com/DavidHiFi/davids-windhawk-mods
// @donateUrl       https://ko-fi.com/DavidHiFi
// @include         windhawk-mod.exe
// @compilerOptions -ld2d1 -ldwrite -lwindowscodecs -lole32 -loleaut32 -luuid -lgdi32 -luser32 -lshell32 -lshlwapi -ladvapi32 -ldwmapi -lcomctl32 -luxtheme -lcomdlg32 -limm32
// ==/WindhawkMod==

// ==WindhawkModReadme==
/*
# Seamless Color Picker

Press a hotkey and a color picker opens, laid out like the one in ShareX: a
color box, a slider, every color value you need, and a magnifier that picks any
pixel on your screen. It runs on its own, so ShareX doesn't need to be open.

![Seamless Color Picker preview](https://raw.githubusercontent.com/DavidHiFi/davids-windhawk-mods/main/media/previews/seamless-color-picker.png)

## Features
- **The ShareX layout.** Color box and slider on the left, new and old color,
  then hue, saturation, brightness, red, green, blue, alpha, CMYK, hex and
  decimal. Pick which value the slider controls.
- **Pick from the screen.** A frozen copy of the screen with a zoomed
  magnifier, a pixel grid and the color under the cross. Arrow keys move one
  pixel at a time.
- **Live sampling.** Hold Ctrl while the picker is open to follow the color
  under the mouse.
- **One-click copy.** Copy as hex, RGB, CSS, HSV, HSL, CMYK, decimal or your own
  pattern. A small card shows what was copied.
- **Recent colors.** The last colors you copied stay one click away, with the
  Catppuccin palette beside them.
- **Frosted glass look.** Catppuccin Mocha with blue to mauve gradients, and you
  can change the colors, the glass and the corners.

## Default shortcuts
| Key | What it does |
|---|---|
| Alt + Win + C | Open the color picker |
| Ctrl + C or Enter | Copy the color |
| Ctrl + V | Take a color from the clipboard |
| P | Pick from the screen |
| Hold Ctrl | Follow the color under the mouse |
| Esc | Close |

In the screen picker: click or Enter picks, right click or Esc cancels, the
arrow keys move one pixel (ten with Shift), the mouse wheel zooms.

## Notes
- Turn off the color picker hotkey in ShareX (or any other app) first. Two
  apps can't use the same hotkey.
- Write hotkeys like `Alt+Win+C` or `Ctrl+Shift+P`. Leave one empty to turn it
  off.
- 8-digit hex codes read as `#AARRGGBB`, the Windows order.

## Credits
Based on the color picker in [ShareX](https://github.com/ShareX/ShareX) by
Jaex and the ShareX contributors (GPL-3.0). Written again in C++ for Windhawk.
*/
// ==/WindhawkModReadme==

// ==WindhawkModSettings==
/*
- Keys:
  - hotkey: Alt+Win+C
    $name: Open the picker
    $description: The hotkey that opens the color picker. Press it again to close it. Leave empty to turn it off.
  - screenHotkey: ""
    $name: Pick from the screen
    $description: A hotkey that goes straight to the screen magnifier, like Ctrl+Shift+C. Leave empty to turn it off.
  - screenPickAction: copy
    $name: After a screen pick
    $description: What the screen hotkey does with the color you pick.
    $options:
    - copy: Copy it
    - copyopen: Copy it and open the picker
    - open: Open the picker with it
  $name: Keys
- Picker:
  - startColor: last
    $name: Starting color
    $description: The color the picker shows when it opens.
    $options:
    - last: The last color you used
    - clipboard: A color on the clipboard, else the last one
    - custom: The color below
  - customStartColor: "#89B4FA"
    $name: Custom starting color
    $description: 'Used when Starting color is "The color below". As #RRGGBB.'
  - sliderMode: hue
    $name: Slider controls
    $description: Which value the tall slider changes. The box shows the other two.
    $options:
    - hue: Hue
    - saturation: Saturation
    - brightness: Brightness
    - red: Red
    - green: Green
    - blue: Blue
  - recentCount: 16
    $name: Recent colors
    $description: 'How many recent colors to keep. 0 to 24 (Suggested: 16). 0 hides the row.'
  - showPalette: true
    $name: Show the Mocha palette
    $description: A row of Catppuccin Mocha colors under the recent ones.
  - livePick: true
    $name: Hold Ctrl to sample
    $description: While the picker is in front, holding Ctrl follows the color under the mouse.
  - alwaysOnTop: true
    $name: Always on top
    $description: Keep the picker above other windows.
  - rememberPosition: true
    $name: Remember where it was
    $description: Open where you left it. Off, it opens beside the mouse.
  $name: Picker
- Screen:
  - magnifierShape: circle
    $name: Magnifier shape
    $description: The shape of the zoomed view.
    $options:
    - circle: Circle
    - square: Rounded square
  - magnifierPixels: 15
    $name: Pixels across
    $description: 'How many screen pixels the magnifier shows across. 7 to 31 (Suggested: 15). Even numbers go up by one.'
  - magnifierZoom: 10
    $name: Zoom
    $description: 'How big each pixel is drawn. 4 to 24 (Suggested: 10). The mouse wheel changes it while picking.'
  - showGrid: true
    $name: Pixel grid
    $description: Thin lines between the zoomed pixels.
  - showCrosshair: true
    $name: Crosshair
    $description: Faint lines across the whole screen through the mouse.
  - showInfo: true
    $name: Color and position card
    $description: Shows the hex code and the X and Y position under the magnifier.
  $name: Screen picker
- Copying:
  - copyFormat: hex
    $name: Copy as
    $description: The format the Copy button, Enter and Ctrl+C use.
    $options:
    - hex: "#89B4FA"
    - hexplain: 89B4FA
    - hexalpha: "#FF89B4FA (with opacity)"
    - rgb: 137, 180, 250
    - cssrgb: rgb(137, 180, 250)
    - cssrgba: rgba(137, 180, 250, 1)
    - hsv: hsv(217, 45%, 98%)
    - hsl: hsl(217, 92%, 76%)
    - cmyk: 45%, 28%, 0%, 2%
    - decimal: "9024762"
    - custom: My own pattern
  - customFormat: "{hex}"
    $name: My own pattern
    $description: Used when Copy as is "My own pattern". Words in braces are filled in, {hex} {r} {g} {b} {a} {h} {s} {v} {c} {m} {y} {k} {dec}, and {px} {py} for the screen position. {y} is yellow.
  - upperCase: true
    $name: Capital hex letters
    $description: "On, #89B4FA. Off, #89b4fa."
  - closeAfterCopy: false
    $name: Close after copying
    $description: Close the picker once you copy with the Copy button, Enter or Ctrl+C.
  - showToast: true
    $name: Show what was copied
    $description: A small card near the mouse with the copied color.
  $name: Copying
- Look:
  - accent: "#89B4FA"
    $name: Accent color
    $description: "Where the gradients start. Suggested Mocha blue, #89B4FA."
  - accent2: "#CBA6F7"
    $name: Second accent color
    $description: "Where the gradients end. Suggested Mocha mauve, #CBA6F7."
  - glass: true
    $name: Frosted glass
    $description: On, the picker is blurred glass. Off, it is solid Mocha.
  - glassTint: 85
    $name: Glass tint
    $description: 'How dark the glass is. 60 to 100 (Suggested: 85). Higher hides more of what is behind.'
  - cornerRadius: 8
    $name: Corner roundness
    $description: 'For boxes, buttons and swatches. 2 to 14 (Suggested: 8).'
  - glow: true
    $name: Hover glow
    $description: A soft blue to mauve glow around the box you point at.
  - animations: true
    $name: Animations
    $description: Short fades on hover. Off, changes are instant.
  - font: FiraCode Nerd Font
    $name: Font
    $description: Any installed font. Falls back to Segoe UI.
  $name: Look
- SettingsWindow:
  - settingsGlass: true
    $name: Blurred settings window
    $description: On, the settings window is see-through glass with Windows acrylic behind it. Off, it is solid. Save, then reopen settings to apply.
  - nativeSettingsTitleBar: true
    $name: Native Windows title bar
    $description: Use the Windows title bar and window buttons for this settings window. Save, then reopen settings to apply.
  - settingsTitleButtons: native
    $name: Title bar buttons
    $description: Who draws minimize, maximize and close on the window's own title bar. Save, then reopen settings to apply.
    $options:
    - native: Windows buttons (like other apps)
    - builtin: Built-in buttons
  $name: Settings window
*/
// ==/WindhawkModSettings==

#include <windhawk_tool_mod.h>

#include <windows.h>
#include <windowsx.h>
#include <commctrl.h>
#include <shellapi.h>
#include <dwmapi.h>
#include <uxtheme.h>
#include <d2d1_1.h>
#include <dwrite.h>
#include <wincodec.h>
#include <wrl/client.h>

#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cwchar>
#include <cwctype>
#include <string>
#include <vector>

// ===========================================================================
// Settings window: the Seamless Launchpad settings GUI, the standard for every
// DavidHiFi mod. Generated by work\2026-11-10-color-picker\gen.py.
// ===========================================================================
#include <map>
#include <atomic>
#include <memory>
#include <set>
#ifndef SCP_SETTINGS_NO_IMAGEBASE
extern "C" IMAGE_DOS_HEADER __ImageBase;
#endif
namespace scpset {
// The settings window, from the gear in the picker. It shows the same settings as
// Windhawk's page for this mod and saves them through windhawk-cli, so the two
// stay in step. Writing a mod's settings takes admin rights, so the save runs
// the CLI elevated (silently where UAC prompts are off).

constexpr WCHAR kSettingsClass[] = L"WindhawkSeamlessColorPickerSettings";
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
};

// Names, descriptions and option labels match the ==WindhawkModSettings== block word for word.
// Generated by test-settings\gen_table.py from src\00-header.cpp.
static std::vector<SetField> Set_MakeFields() {
    using K = SetField;
    return {
{K::Hotkey, L"Keys.hotkey", L"Open the picker", L"The hotkey that opens the color picker. Press it again to close it. Leave empty to turn it off.", L"Alt+Win+C", {}, 0, 100, 0, L"Keys"},
{K::Hotkey, L"Keys.screenHotkey", L"Pick from the screen", L"A hotkey that goes straight to the screen magnifier, like Ctrl+Shift+C. Leave empty to turn it off.", L"", {}, 0, 100, 0, L"Keys"},
{K::Choice, L"Keys.screenPickAction", L"After a screen pick", L"What the screen hotkey does with the color you pick.", L"copy", {{L"copy", L"Copy it"}, {L"copyopen", L"Copy it and open the picker"}, {L"open", L"Open the picker with it"}}, 0, 100, 0, L"Keys"},
{K::Choice, L"Picker.startColor", L"Starting color", L"The color the picker shows when it opens.", L"last", {{L"last", L"The last color you used"}, {L"clipboard", L"A color on the clipboard, else the last one"}, {L"custom", L"The color below"}}, 0, 100, 1, L"Picker"},
{K::Color, L"Picker.customStartColor", L"Custom starting color", L"Used when Starting color is \"The color below\". As #RRGGBB.", L"#89B4FA", {}, 0, 100, 1, L"Picker"},
{K::Choice, L"Picker.sliderMode", L"Slider controls", L"Which value the tall slider changes. The box shows the other two.", L"hue", {{L"hue", L"Hue"}, {L"saturation", L"Saturation"}, {L"brightness", L"Brightness"}, {L"red", L"Red"}, {L"green", L"Green"}, {L"blue", L"Blue"}}, 0, 100, 1, L"Picker"},
{K::Number, L"Picker.recentCount", L"Recent colors", L"How many recent colors to keep. 0 to 24 (Suggested: 16). 0 hides the row.", L"16", {}, 0, 24, 1, L"Picker"},
{K::Check, L"Picker.showPalette", L"Show the Mocha palette", L"A row of Catppuccin Mocha colors under the recent ones.", L"1", {}, 0, 100, 1, L"Picker"},
{K::Check, L"Picker.livePick", L"Hold Ctrl to sample", L"While the picker is in front, holding Ctrl follows the color under the mouse.", L"1", {}, 0, 100, 1, L"Picker"},
{K::Check, L"Picker.alwaysOnTop", L"Always on top", L"Keep the picker above other windows.", L"1", {}, 0, 100, 1, L"Picker"},
{K::Check, L"Picker.rememberPosition", L"Remember where it was", L"Open where you left it. Off, it opens beside the mouse.", L"1", {}, 0, 100, 1, L"Picker"},
{K::Choice, L"Screen.magnifierShape", L"Magnifier shape", L"The shape of the zoomed view.", L"circle", {{L"circle", L"Circle"}, {L"square", L"Rounded square"}}, 0, 100, 2, L"Screen picker"},
{K::Number, L"Screen.magnifierPixels", L"Pixels across", L"How many screen pixels the magnifier shows across. 7 to 31 (Suggested: 15). Even numbers go up by one.", L"15", {}, 7, 31, 2, L"Screen picker"},
{K::Number, L"Screen.magnifierZoom", L"Zoom", L"How big each pixel is drawn. 4 to 24 (Suggested: 10). The mouse wheel changes it while picking.", L"10", {}, 4, 24, 2, L"Screen picker"},
{K::Check, L"Screen.showGrid", L"Pixel grid", L"Thin lines between the zoomed pixels.", L"1", {}, 0, 100, 2, L"Screen picker"},
{K::Check, L"Screen.showCrosshair", L"Crosshair", L"Faint lines across the whole screen through the mouse.", L"1", {}, 0, 100, 2, L"Screen picker"},
{K::Check, L"Screen.showInfo", L"Color and position card", L"Shows the hex code and the X and Y position under the magnifier.", L"1", {}, 0, 100, 2, L"Screen picker"},
{K::Choice, L"Copying.copyFormat", L"Copy as", L"The format the Copy button, Enter and Ctrl+C use.", L"hex", {{L"hex", L"#89B4FA"}, {L"hexplain", L"89B4FA"}, {L"hexalpha", L"#FF89B4FA (with opacity)"}, {L"rgb", L"137, 180, 250"}, {L"cssrgb", L"rgb(137, 180, 250)"}, {L"cssrgba", L"rgba(137, 180, 250, 1)"}, {L"hsv", L"hsv(217, 45%, 98%)"}, {L"hsl", L"hsl(217, 92%, 76%)"}, {L"cmyk", L"45%, 28%, 0%, 2%"}, {L"decimal", L"9024762"}, {L"custom", L"My own pattern"}}, 0, 100, 3, L"Copying"},
{K::Text, L"Copying.customFormat", L"My own pattern", L"Used when Copy as is \"My own pattern\". Words in braces are filled in, {hex} {r} {g} {b} {a} {h} {s} {v} {c} {m} {y} {k} {dec}, and {px} {py} for the screen position. {y} is yellow.", L"{hex}", {}, 0, 100, 3, L"Copying"},
{K::Check, L"Copying.upperCase", L"Capital hex letters", L"On, #89B4FA. Off, #89b4fa.", L"1", {}, 0, 100, 3, L"Copying"},
{K::Check, L"Copying.closeAfterCopy", L"Close after copying", L"Close the picker once you copy with the Copy button, Enter or Ctrl+C.", L"0", {}, 0, 100, 3, L"Copying"},
{K::Check, L"Copying.showToast", L"Show what was copied", L"A small card near the mouse with the copied color.", L"1", {}, 0, 100, 3, L"Copying"},
{K::Color, L"Look.accent", L"Accent color", L"Where the gradients start. Suggested Mocha blue, #89B4FA.", L"#89B4FA", {}, 0, 100, 4, L"Look"},
{K::Color, L"Look.accent2", L"Second accent color", L"Where the gradients end. Suggested Mocha mauve, #CBA6F7.", L"#CBA6F7", {}, 0, 100, 4, L"Look"},
{K::Check, L"Look.glass", L"Frosted glass", L"On, the picker is blurred glass. Off, it is solid Mocha.", L"1", {}, 0, 100, 4, L"Look"},
{K::Number, L"Look.glassTint", L"Glass tint", L"How dark the glass is. 60 to 100 (Suggested: 85). Higher hides more of what is behind.", L"85", {}, 60, 100, 4, L"Look"},
{K::Number, L"Look.cornerRadius", L"Corner roundness", L"For boxes, buttons and swatches. 2 to 14 (Suggested: 8).", L"8", {}, 2, 14, 4, L"Look"},
{K::Check, L"Look.glow", L"Hover glow", L"A soft blue to mauve glow around the box you point at.", L"1", {}, 0, 100, 4, L"Look"},
{K::Check, L"Look.animations", L"Animations", L"Short fades on hover. Off, changes are instant.", L"1", {}, 0, 100, 4, L"Look"},
{K::Text, L"Look.font", L"Font", L"Any installed font. Falls back to Segoe UI.", L"FiraCode Nerd Font", {}, 0, 100, 4, L"Look"},
{K::Check, L"SettingsWindow.settingsGlass", L"Blurred settings window", L"On, the settings window is see-through glass with Windows acrylic behind it. Off, it is solid. Save, then reopen settings to apply.", L"1", {}, 0, 100, 4, L"Settings window"},
{K::Check, L"SettingsWindow.nativeSettingsTitleBar", L"Native Windows title bar", L"Use the Windows title bar and window buttons for this settings window. Save, then reopen settings to apply.", L"1", {}, 0, 100, 4, L"Settings window"},
{K::Choice, L"SettingsWindow.settingsTitleButtons", L"Title bar buttons", L"Who draws minimize, maximize and close on the window's own title bar. Save, then reopen settings to apply.", L"native", {{L"native", L"Windows buttons (like other apps)"}, {L"builtin", L"Built-in buttons"}}, 0, 100, 4, L"Settings window"}
    };
}

struct SetPageInfo {
    PCWSTR name, intro;
    WCHAR glyph;
};
static const SetPageInfo kSetPages[] = {
{L"Keys", L"The hotkeys that open the picker and the screen magnifier.", 0xE765},
{L"Picker", L"Starting color, the slider, recent colors and the window.", 0xE790},
{L"Screen picker", L"The magnifier you pick screen pixels with.", 0xE71E},
{L"Copying", L"What a copy puts on the clipboard.", 0xE8C8},
{L"Look", L"Accent colors, glass, corners, glow and this window.", 0xE771},
{L"About", L"Version, credits, support and links.", 0xE946},
};
constexpr int kSetPageCount = (int)(sizeof(kSetPages) / sizeof(kSetPages[0]));
// About sits apart at the end of the sidebar, as in Seamless Dictate.
constexpr int kSetAboutPage = kSetPageCount - 1;
constexpr float kSetAboutGap = 17;

// All sizes are DIPs; the render target does the scaling.
constexpr float kSetPadX = 40, kSetMaxW = 720, kSetRowMin = 56, kSetRowGap = 8, kSetBoxH = 32, kSetRowPad = 16,
                kSetDropItem = 32, kSetRailTop = 76, kSetRailItem = 36, kSetRailPitch = 40;
// The sidebar is a floating dock: dragged between min and max, or collapsed to an icon rail.
constexpr float kSetDockGap = 10, kSetRailDef = 232, kSetRailMin = 200, kSetRailMax = 380, kSetRailMini = 60,
                kSetRailSnap = 130, kSetEdgeGrab = 5;
// The footer is a floating pill dock at the bottom right of the page.
constexpr float kSetFootBtnH = 36, kSetFootPad = 8, kSetFootH = kSetFootBtnH + 2 * kSetFootPad, kSetFootGap = 14;
// The glass tint is one layer over the whole window, title bar included, so the two always match.
constexpr float kSetGlassTint = 0.42f, kSetNativeFade = 56;
constexpr int kSetChipCount = 10;
constexpr UINT32 kSetChips[kSetChipCount] = {mocha::blue,   mocha::sapphire, mocha::teal, mocha::green, mocha::yellow,
                                             mocha::peach,  mocha::red,      mocha::pink, mocha::mauve, mocha::lavender};
constexpr UINT_PTR kSetTimerId = 1;
constexpr PCWSTR kSetKofiUrl = L"https://ko-fi.com/DavidHiFi";
constexpr PCWSTR kSetAuthorUrl = L"https://github.com/DavidHiFi";
constexpr PCWSTR kSetDittoUrl = L"https://github.com/ShareX/ShareX";
constexpr PCWSTR kSetRepoUrl = L"https://github.com/DavidHiFi/davids-windhawk-mods";
constexpr PCWSTR kSetBugUrl =
    L"https://github.com/DavidHiFi/davids-windhawk-mods/issues/new?title=%5BSeamless%20Color%20Picker%5D%20";
constexpr PCWSTR kSetTitle = L"Seamless Color Picker";
// The self-drawn title bar. Everything below it is laid out as before, in "content" DIPs.
static float kSetCapH = 40;
constexpr float kSetCapBtnW = 46, kSetHoverMs = 120;

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
    bool nativeButtons = false;  // Own title bar, but Windows draws minimize, maximize and close.
    bool glass = false;        // Acrylic behind the window; the page is drawn see-through.
    ULONGLONG lastTick = 0;
    int page = 0, recording = -1, editing = -1, focus = -1, openSel = -1;
    bool kbd = false;  // Show the focus ring (after a Tab).
    D2D1_RECT_F dropRect{};
    int dropHover = -1;
    float scrollY = 0, scrollTarget = 0, contentH = 0, contentX = 0, contentW = 720, pageT = 1;
    SetHit hover;
    int dragSlider = -1;
    bool dragScroll = false, tracking = false, timer = false;
    float dragOff = 0;
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
static void Set_MakeFormats(SetWindow& w) {
    w.family = Set_ResolveFamily();
    w.iconFamily = Set_FamilyExists(L"Segoe Fluent Icons") ? L"Segoe Fluent Icons" : L"Segoe MDL2 Assets";
    int base = std::clamp(500, 100, 900);
    int bold = std::max(base, std::min(700, base + 100));
    const auto L_ = DWRITE_TEXT_ALIGNMENT_LEADING, C_ = DWRITE_TEXT_ALIGNMENT_CENTER;
    w.fLabel = Set_Fmt(w.family, 14, base, true);
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
        if (w.fRailName && Set_TextW(w.fRailName.get(), L"Color Picker") <= railW) break;
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
    return !w.render && Wh_GetIntSetting(L"Look.animations") && on;
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

// ---- Layout -----------------------------------------------------------------

// The right-hand control's width, so the label column knows how much room it has.
static float Set_ControlW(const SetField& f) {
    switch (f.kind) {
        case SetField::Check: return 40;
        case SetField::Choice: return 200;
        case SetField::Number: return f.max - f.min <= 100 ? 150 + 12 + 64 : 96;
        case SetField::Text: return 280;
        case SetField::Hotkey: return 220;
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
            p.box = {r - 200, mid - h, r, mid + h};
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
            p.box = {r - 280, mid - h, r, mid + h};
            break;
        case SetField::Hotkey:
            p.box = {r - 220, mid - h, r, mid + h};
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
        add(SetItem::Link, 56, L"Based on the ShareX color picker", L"By Jaex and the ShareX contributors, GPL-3.0", kSetDittoUrl);
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

static void Set_DrawBox(SetPaint& p, SetWindow& w, int k, const D2D1_RECT_F& box, bool active) {
    p.Round(box, 8, mocha::crust);
    float g = std::max(Set_GlowOf(w, 6000 + k), active ? 1.0f : 0.0f);
    p.GradRing(box, 8, g);
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
    float dh = f.desc ? Set_TextH(w.fHint.get(), f.desc, textW) + 3 : 0;
    float top = row.top + (it.h - lh - dh) / 2;
    p.Text(w.fLabel.get(), f.label, {row.left + kSetRowPad, top, row.left + kSetRowPad + textW, top + lh + 2}, mocha::text);
    if (f.desc)
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
    Set_DrawCard(p, row, 0);
    p.Text(w.fLabel.get(), it.text, {row.left + kSetRowPad, row.top + 14, row.right - 180, row.top + 36}, mocha::text);
    p.Text(w.fHint.get(), it.sub, {row.left + kSetRowPad, row.top + 38, row.right - 180, row.bottom - 6}, mocha::subtext0);
    D2D1_RECT_F b = Set_SupportButton(w, it);
    float hov = Set_GlowOf(w, 3500 + idx);
    p.GradFill(b, 8, 0.85f + 0.15f * hov);
    p.GradRing(b, 8, hov, 2);
    p.Text(w.fButton.get(), L"Open Ko-fi", b, mocha::crust);
}

static void Set_DrawAbout(SetPaint& p, SetWindow& w, const SetItem& it) {
    D2D1_RECT_F row = Set_RowRect(w, it);
    Set_DrawCard(p, row, 0);
    D2D1_RECT_F mark{row.left + 20, row.top + 20, row.left + 92, row.top + 92};
    p.GradFill(mark, 18, 1);
    p.Glyph(w.fIconL.get(), 0xEF3C, mark, mocha::crust);
    float x = mark.right + 20;
    p.Text(w.fBig.get(), L"Seamless Color Picker", {x, row.top + 18, row.right - 16, row.top + 46}, mocha::text);
#ifdef WH_MOD_VERSION
    std::wstring ver = std::wstring(L"Version ") + WH_MOD_VERSION + L"  \u00B7  MIT license  \u00B7  A Windhawk mod";
#else
    std::wstring ver = L"MIT license  \u00B7  A Windhawk mod";
#endif
    p.Text(w.fHint.get(), ver, {x, row.top + 48, row.right - 16, row.top + 68}, mocha::subtext0);
    p.Text(w.fHint.get(), L"A full color picker on a hotkey, with a screen magnifier and one-click copy.",
           {x, row.top + 72, row.right - 16, row.top + 110}, mocha::subtext1);
    p.Text(w.fHint.get(), L"Made by DavidHiFi, based on the color picker in ShareX.",
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
    Set_DrawDock(p, w, d, 14, w.glass ? 0.58f : 1.0f, std::max(w.railGlow, w.dragRail ? 1.0f : 0.0f) * 0.85f);

    // Drag handle: a thin gradient line on the dock's right edge while it is grabbed or pointed at.
    float edge = std::max(Set_GlowOf(w, 41), w.dragRail ? 1.0f : 0.0f);
    if (edge > 0.003f) p.GradFill({d.right - 1.5f, d.top + 18, d.right + 1.5f, d.bottom - 18}, 1.5f, edge);

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
    p.Text(w.fRailName.get(), L"Color Picker", {d.left + 90, d.top + 32, d.left + w.railW - 10, d.top + 56}, mocha::text, textA);
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
        p.Text(w.fLabel.get(), kSetPages[i].name, {r.left + 50, r.top + 8, r.left + w.railW - 24, r.bottom}, c, textA);
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
    Set_DrawDock(p, w, d, rad, w.glass ? 0.9f : 1.0f, w.footGlow);
    UINT32 sc;
    std::wstring status = Set_FooterStatus(w, &sc);
    float sw = Set_FooterStatusW(w);
    if (sw > 0) p.Text(w.fStatusLine.get(), status, {d.left + 18, d.top, d.left + 18 + sw, d.bottom}, sc);
    static const PCWSTR names[3] = {L"Reset to suggested", L"Cancel", L"Save"};
    for (int i = 0; i < 3; i++) {
        D2D1_RECT_F b = Set_FooterButton(w, i);
        float hov = Set_GlowOf(w, 10 + i);
        if (i == 2) {
            p.GradFill(b, brad, 0.88f + 0.12f * hov);
            p.GradRing(b, brad, hov, 2);
            p.Text(w.fButton.get(), names[i], b, mocha::crust, w.saving ? 0.5f : 1.0f);
        } else {
            p.Round(b, brad, mocha::surface0, 0.6f);
            p.GradFill(b, brad, 0.12f * hov);
            p.GradRing(b, brad, 0.85f * hov);
            p.Text(w.fButton.get(), names[i], b, mocha::text);
        }
        if (w.kbd && w.focus == -1 - i) p.GradRing(b, brad, 1, 2);
    }
}

static void Set_DrawPopup(SetPaint& p, SetWindow& w) {
    if (w.openSel < 0) return;
    const SetField& f = w.fields[w.openSel];
    const D2D1_RECT_F& r = w.dropRect;
    D2D1_RECT_F shadow{r.left - 1, r.top + 3, r.right + 1, r.bottom + 5};
    p.Round(shadow, 12, mocha::crust, 0.6f);
    p.Round(r, 10, mocha::mantle);
    p.GradRing(r, 10, 0.9f);
    for (size_t i = 0; i < f.options.size(); i++) {
        D2D1_RECT_F it{r.left + 4, r.top + 4 + i * kSetDropItem, r.right - 4, r.top + 4 + (i + 1) * kSetDropItem};
        bool sel = f.cur == f.options[i].first;
        if ((int)i == w.dropHover) {
            p.GradFill(it, 6, 0.28f);
            p.GradRing(it, 6, 0.6f, 1);
        }
        p.Text(w.fValue.get(), f.options[i].second, {it.left + 10, it.top, it.right - 28, it.bottom}, sel ? mocha::blue : mocha::text);
        if (sel) p.Glyph(w.fIconS.get(), 0xE73E, {it.right - 28, it.top, it.right - 6, it.bottom}, mocha::blue);
    }
}

// Title bar buttons, in title bar DIPs: 0 minimize, 1 maximize or restore, 2 close.
static D2D1_RECT_F Set_CapButton(const SetWindow& w, int i) {
    float right = w.cw - (2 - i) * kSetCapBtnW;
    return {right - kSetCapBtnW, 0, right, kSetCapH};
}

// y is in content DIPs, so the title bar is y < 0.
static int Set_CapButtonAt(const SetWindow& w, float x, float y) {
    if (w.nativeTitle || w.nativeButtons) return -1;
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
    p.Glyph(glyph, 0xEF3C, r, mocha::crust);
}

static void Set_DrawCaption(SetPaint& p, SetWindow& w) {
    if (!w.glass) p.Fill({0, 0, w.cw, kSetCapH}, mocha::crust);  // Glass: the window tint already covers it.
    D2D1_RECT_F t = Set_CapTitleRect(w);
    float mid = kSetCapH / 2;
    Set_DrawMark(p, w.fCapGlyph.get(), {t.left, mid - 8, t.left + 16, mid + 8}, w.active ? 1.0f : 0.6f);
    p.Text(w.fCap.get(), kSetTitle, {t.left + 24, 0, t.right, kSetCapH}, w.active ? mocha::text : mocha::overlay1);
    if (w.nativeButtons) return;  // DWM draws them over this title bar.
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
static void Set_Draw(SetWindow& w, ID2D1RenderTarget* rt) {
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
            D2D1_GRADIENT_STOP stops[2] = {{0, D2DColor(mocha::crust, 0)}, {1, D2DColor(mocha::crust, kSetGlassTint)}};
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

    rt->PushAxisAlignedClip(D2D1::RectF(Set_RailSpace(w) + 4, 0, w.cw, viewH), D2D1_ANTIALIAS_MODE_ALIASED);
    auto place = [&](int index, float& rise) {
        float t = w.pageT >= 1 ? 1.0f : Set_Ease(w.pageT * 1.7f - std::min(index, 9) * 0.07f);
        p.fade = t;
        rise = (1 - t) * 10;
        rt->SetTransform(D2D1::Matrix3x2F::Translation(0, -w.scrollY + rise) * base);
    };
    float rise = 0;
    place(0, rise);
    p.Text(w.fTitle.get(), kSetPages[w.page].name, {w.contentX, 36, w.contentX + w.contentW, 72}, mocha::text);
    place(1, rise);
    p.Text(w.fIntro.get(), kSetPages[w.page].intro, {w.contentX, 76, w.contentX + w.contentW, 76 + 40}, mocha::subtext0);
    for (size_t i = 0; i < w.items.size(); i++) {
        const SetItem& it = w.items[i];
        if (it.y + it.h < w.scrollY - 20 || it.y > w.scrollY + viewH + 20) continue;
        place((int)i + 2, rise);
        switch (it.type) {
            case SetItem::Group: Set_DrawGroup(p, w, it); break;
            case SetItem::Row: Set_DrawRow(p, w, it); break;
            case SetItem::Banner: Set_DrawBanner(p, w, it); break;
            case SetItem::About: Set_DrawAbout(p, w, it); break;
            case SetItem::Link: Set_DrawLinkRow(p, w, it, (int)i); break;
            case SetItem::Support: Set_DrawSupport(p, w, it, (int)i); break;
        }
    }
    p.fade = 1;
    rt->SetTransform(base);
    rt->PopAxisAlignedClip();

    D2D1_RECT_F th = Set_ScrollThumb(w);
    if (th.bottom > th.top) p.Round(th, 3, w.dragScroll ? mocha::overlay1 : mocha::surface2, 0.9f);

    Set_DrawFooter(p, w);
    Set_DrawRail(p, w);
    Set_DrawPopup(p, w);
    rt->SetTransform(D2D1::Matrix3x2F::Identity());
    if (false) p.GradRing({0, 0, w.cw, w.ch + kSetCapH}, SystemCornerRadius(false), 1, 1);
    HRESULT hr = rt->EndDraw();
    if (hr == D2DERR_RECREATE_TARGET) w.rt.reset();
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
            int i = (int)((y - w.dropRect.top - 4) / kSetDropItem);
            if (i >= 0 && i < (int)w.fields[w.openSel].options.size() && y >= w.dropRect.top + 4) {
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
            if (Set_In(Set_SupportButton(w, it), x, cy)) {
                h.kind = SetHit::Link;
                h.a = (int)i;
                h.id = 3500 + (int)i;
            }
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

static std::wstring Set_FormatHotkey(UINT mods, UINT vk) {
    std::wstring text;
    if (mods & MOD_CONTROL) text += L"Ctrl+";
    if (mods & MOD_ALT) text += L"Alt+";
    if (mods & MOD_SHIFT) text += L"Shift+";
    if (mods & MOD_WIN) text += L"Win+";
    // Names the mod's hotkey reader understands.
    if ((vk >= 'A' && vk <= 'Z') || (vk >= '0' && vk <= '9')) return text + (WCHAR)vk;
    if (vk >= VK_F1 && vk <= VK_F24) return text + L"F" + std::to_wstring(vk - VK_F1 + 1);
    if (vk >= VK_NUMPAD0 && vk <= VK_NUMPAD9) return text + L"Numpad" + std::to_wstring(vk - VK_NUMPAD0);
    static const struct { UINT vk; PCWSTR name; } names[] = {
        {VK_SPACE, L"Space"}, {VK_TAB, L"Tab"}, {VK_RETURN, L"Enter"}, {VK_ESCAPE, L"Esc"},
        {VK_BACK, L"Backspace"}, {VK_INSERT, L"Insert"}, {VK_DELETE, L"Delete"}, {VK_HOME, L"Home"},
        {VK_END, L"End"}, {VK_PRIOR, L"PageUp"}, {VK_NEXT, L"PageDown"}, {VK_UP, L"Up"},
        {VK_DOWN, L"Down"}, {VK_LEFT, L"Left"}, {VK_RIGHT, L"Right"}, {VK_SNAPSHOT, L"PrintScreen"},
        {VK_PAUSE, L"Pause"}, {VK_OEM_PLUS, L"Plus"}, {VK_OEM_MINUS, L"Minus"}, {VK_OEM_COMMA, L"Comma"},
        {VK_OEM_PERIOD, L"Period"},
    };
    for (auto& n : names)
        if (n.vk == vk) return text + n.name;
    WCHAR ch = (WCHAR)MapVirtualKeyW(vk, MAPVK_VK_TO_CHAR);
    if (ch > L' ') return text + ch;
    return text + std::to_wstring(vk);
}

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
    Set_Invalidate(w);
}

static void Set_OpenPopup(SetWindow& w, int k) {
    const SetItem* it = Set_ItemOfField(w, k);
    if (!it) return;
    const SetField& f = w.fields[k];
    SetParts pt = Set_Parts(f, Set_RowRect(w, *it));
    float boxTop = pt.box.top - w.scrollY, boxBottom = pt.box.bottom - w.scrollY;
    float h = (float)f.options.size() * kSetDropItem + 8;
    float top = boxBottom + 4;
    if (top + h > Set_ViewH(w) + 20 && boxTop - 4 - h > 0) top = boxTop - 4 - h;  // No room below: open upward.
    w.dropRect = {pt.box.left, top, pt.box.right, top + h};
    w.openSel = k;
    w.dropHover = -1;
    for (size_t i = 0; i < f.options.size(); i++)
        if (f.cur == f.options[i].first) w.dropHover = (int)i;
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
        else if (vk == VK_UP) w.dropHover = (w.dropHover - 1 + n) % n;
        else if (vk == VK_DOWN) w.dropHover = (w.dropHover + 1) % n;
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

static void Set_RememberRect(SetWindow& w) {
    if (w.render || IsIconic(w.hwnd) || IsZoomed(w.hwnd)) return;
    GetWindowRect(w.hwnd, &w.normalRect);
}

static LRESULT CALLBACK Set_WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    SetWindow* w = g_setWin && g_setWin->hwnd == hwnd ? g_setWin.get() : nullptr;
    if (!w) return DefWindowProcW(hwnd, msg, wParam, lParam);
    if (w->nativeButtons) {
        LRESULT r = 0;
        if (DwmDefWindowProc(hwnd, msg, wParam, lParam, &r)) return r;  // Hover and clicks on DWM's buttons.
    }
    auto dipX = [&](LPARAM l) { return (float)(short)LOWORD(l) * 96.0f / w->dpi; };
    auto dipY = [&](LPARAM l) { return (float)(short)HIWORD(l) * 96.0f / w->dpi - kSetCapH; };
    switch (msg) {
        case WM_APP_SETTINGS_RELOAD: if (!w->saving) Set_LoadFields(*w); return 0;
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
            SetBkColor(dc, RefFromRgb(mocha::crust));
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
        case WM_MOUSELEAVE:
            w->tracking = false;
            w->hover = SetHit();
            if (!w->dragRail) w->mouseX = w->mouseY = -1;
            Set_Invalidate(*w);
            return 0;
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
        case WM_MOUSEWHEEL: {
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
    w->editBrush = CreateSolidBrush(RefFromRgb(mocha::crust));
    g_setWin = w;
    if (render) {
        // An owned window gets no taskbar button.
        w->owner = CreateWindowExW(WS_EX_TOOLWINDOW, L"STATIC", L"", WS_POPUP, 0, 0, 0, 0, nullptr, nullptr,
                                   GetModuleHandleW(nullptr), nullptr);
    }
    const int offX = GetSystemMetrics(SM_XVIRTUALSCREEN) - 6000, offY = GetSystemMetrics(SM_YVIRTUALSCREEN);
    w->nativeTitle = !render && Wh_GetIntSetting(L"SettingsWindow.nativeSettingsTitleBar") != 0;
    w->nativeButtons = !render && !w->nativeTitle && GetStringSetting(L"SettingsWindow.settingsTitleButtons") != L"builtin";
    w->glass = !render && Wh_GetIntSetting(L"SettingsWindow.settingsGlass") != 0;
    kSetCapH = w->nativeTitle ? 0.0f : 40.0f;
    const DWORD style = WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN;
    HWND hwnd = CreateWindowExW(0, kSettingsClass, L"Seamless Color Picker settings", style,
                                render ? offX : CW_USEDEFAULT, render ? offY : CW_USEDEFAULT, 800, 600, w->owner,
                                nullptr, (HINSTANCE)&__ImageBase, nullptr);
    if (!hwnd) {
        g_setWin.reset();
        return false;
    }
    w->hwnd = hwnd;
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
        if (w->glass) {
            // Windows acrylic as one sheet over the whole window, the way T3 (Electron
            // backgroundMaterial "acrylic") does it: the system backdrop with the frame extended
            // into the full client area, and no caption color, so the title bar and the page are
            // the same material and turn solid together when the window loses focus.
            int backdrop = 3;  // DWMSBT_TRANSIENTWINDOW
            DwmSetWindowAttribute(hwnd, 38 /* DWMWA_SYSTEMBACKDROP_TYPE */, &backdrop, sizeof(backdrop));
            MARGINS margins{-1, -1, -1, -1};
            DwmExtendFrameIntoClientArea(hwnd, &margins);
            COLORREF none = 0xFFFFFFFE;  // DWMWA_COLOR_NONE
            DwmSetWindowAttribute(hwnd, 35 /* DWMWA_CAPTION_COLOR */, &none, sizeof(none));
        } else if (w->nativeButtons) {
            // Solid window: DWM draws its buttons only where the frame reaches, so extend it
            // over the title bar strip.
            MARGINS margins{0, 0, MulDiv((int)kSetCapH, w->dpi, 96), 0};
            DwmExtendFrameIntoClientArea(hwnd, &margins);
        }
        // With the frame extended, DWM draws its own minimize, maximize and close buttons in the
        // corner. "Windows buttons" keeps them (Set_WndProc passes their hover and clicks to
        // DwmDefWindowProc); "Built-in buttons" drops the system menu so DWM draws none and the
        // window draws its own. Minimize, maximize and close still work from the taskbar.
        if (!w->nativeTitle && !w->nativeButtons)
            SetWindowLongPtrW(hwnd, GWL_STYLE, GetWindowLongPtrW(hwnd, GWL_STYLE) & ~WS_SYSMENU);
        // The first WM_NCCALCSIZE ran before w->hwnd was set; drop the system title bar now.
        SetWindowPos(hwnd, nullptr, 0, 0, 0, 0, SWP_FRAMECHANGED | SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE);
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
}  // namespace scpset


// ===========================================================================
// Seamless Color Picker. One background thread owns everything: a message-only
// window for the hotkeys, the picker window, the screen magnifier and the
// "Copied" card. The layout follows ShareX's ColorPickerForm.
// ===========================================================================
namespace scp {
using Microsoft::WRL::ComPtr;
namespace m = scpset::mocha;
using scpset::D2DColor;

constexpr UINT WM_APP_SETTINGS = WM_APP + 10, WM_APP_PICKED = WM_APP + 11;
constexpr int kHotkeyOpen = 1, kHotkeyScreen = 2;
constexpr UINT_PTR kTimerRetry = 1, kTimerAnim = 2, kTimerToast = 3;
constexpr WCHAR kMsgClass[] = L"SeamlessColorPickerMsg", kPickerClass[] = L"SeamlessColorPicker",
                kOverlayClass[] = L"SeamlessColorPickerScreen", kToastClass[] = L"SeamlessColorPickerToast";

// ---- Settings -------------------------------------------------------------

struct Settings {
    std::wstring hotkey = L"Alt+Win+C", screenHotkey;
    int screenAction = 0;  // copy, copy and open, open
    int startColor = 0;    // last, clipboard, custom
    UINT32 customStart = m::blue;
    int sliderMode = 0, recentCount = 16;
    bool showPalette = true, livePick = true, onTop = true, rememberPos = true;
    bool magCircle = true;
    int magPixels = 15, magZoom = 10;
    bool grid = true, crosshair = true, info = true;
    int copyFormat = 0;
    std::wstring customFormat = L"{hex}";
    bool upper = true, closeAfterCopy = false, toast = true;
    UINT32 accent = m::blue, accent2 = m::mauve;
    bool glass = true;
    int tint = 85;
    float radius = 8;
    bool glow = true, anim = true;
    std::wstring font = L"FiraCode Nerd Font";
};
Settings g_set;

static std::wstring Str(PCWSTR key) {
    PCWSTR p = Wh_GetStringSetting(key);
    std::wstring s = p ? p : L"";
    if (p) Wh_FreeStringSetting(p);
    return s;
}

static int PickOf(const std::wstring& v, std::initializer_list<PCWSTR> options) {
    int i = 0;
    for (PCWSTR o : options) {
        if (v == o) return i;
        i++;
    }
    return 0;
}

static std::wstring Trim(const std::wstring& s) {
    size_t a = s.find_first_not_of(L" \t\r\n");
    if (a == std::wstring::npos) return L"";
    size_t b = s.find_last_not_of(L" \t\r\n");
    return s.substr(a, b - a + 1);
}

static std::wstring Lower(std::wstring s) {
    for (auto& c : s) c = (wchar_t)towlower(c);
    return s;
}

static bool ParseHexDigits(const std::wstring& s, UINT32& v) {
    if (s.empty() || s.size() > 8) return false;
    v = 0;
    for (wchar_t c : s) {
        int d = c >= L'0' && c <= L'9' ? c - L'0' : c >= L'a' && c <= L'f' ? c - L'a' + 10
              : c >= L'A' && c <= L'F' ? c - L'A' + 10 : -1;
        if (d < 0) return false;
        v = v * 16 + d;
    }
    return true;
}

static bool ParseRgbSetting(const std::wstring& text, UINT32& rgb) {
    std::wstring s = Trim(text);
    if (!s.empty() && s[0] == L'#') s = s.substr(1);
    UINT32 v;
    if (s.size() != 6 || !ParseHexDigits(s, v)) return false;
    rgb = v;
    return true;
}

static void LoadSettings() {
    Settings s;
    s.hotkey = Trim(Str(L"Keys.hotkey"));
    s.screenHotkey = Trim(Str(L"Keys.screenHotkey"));
    s.screenAction = PickOf(Str(L"Keys.screenPickAction"), {L"copy", L"copyopen", L"open"});
    s.startColor = PickOf(Str(L"Picker.startColor"), {L"last", L"clipboard", L"custom"});
    if (!ParseRgbSetting(Str(L"Picker.customStartColor"), s.customStart)) s.customStart = m::blue;
    s.sliderMode = PickOf(Str(L"Picker.sliderMode"), {L"hue", L"saturation", L"brightness", L"red", L"green", L"blue"});
    s.recentCount = std::clamp(Wh_GetIntSetting(L"Picker.recentCount"), 0, 24);
    s.showPalette = Wh_GetIntSetting(L"Picker.showPalette") != 0;
    s.livePick = Wh_GetIntSetting(L"Picker.livePick") != 0;
    s.onTop = Wh_GetIntSetting(L"Picker.alwaysOnTop") != 0;
    s.rememberPos = Wh_GetIntSetting(L"Picker.rememberPosition") != 0;
    s.magCircle = Str(L"Screen.magnifierShape") != L"square";
    s.magPixels = std::clamp(Wh_GetIntSetting(L"Screen.magnifierPixels"), 7, 31) | 1;
    s.magZoom = std::clamp(Wh_GetIntSetting(L"Screen.magnifierZoom"), 4, 24);
    s.grid = Wh_GetIntSetting(L"Screen.showGrid") != 0;
    s.crosshair = Wh_GetIntSetting(L"Screen.showCrosshair") != 0;
    s.info = Wh_GetIntSetting(L"Screen.showInfo") != 0;
    s.copyFormat = PickOf(Str(L"Copying.copyFormat"), {L"hex", L"hexplain", L"hexalpha", L"rgb", L"cssrgb", L"cssrgba",
                                                        L"hsv", L"hsl", L"cmyk", L"decimal", L"custom"});
    s.customFormat = Str(L"Copying.customFormat");
    if (Trim(s.customFormat).empty()) s.customFormat = L"{hex}";
    s.upper = Wh_GetIntSetting(L"Copying.upperCase") != 0;
    s.closeAfterCopy = Wh_GetIntSetting(L"Copying.closeAfterCopy") != 0;
    s.toast = Wh_GetIntSetting(L"Copying.showToast") != 0;
    if (!ParseRgbSetting(Str(L"Look.accent"), s.accent)) s.accent = m::blue;
    if (!ParseRgbSetting(Str(L"Look.accent2"), s.accent2)) s.accent2 = m::mauve;
    s.glass = Wh_GetIntSetting(L"Look.glass") != 0;
    s.tint = std::clamp(Wh_GetIntSetting(L"Look.glassTint"), 60, 100);
    s.radius = (float)std::clamp(Wh_GetIntSetting(L"Look.cornerRadius"), 2, 14);
    s.glow = Wh_GetIntSetting(L"Look.glow") != 0;
    s.anim = Wh_GetIntSetting(L"Look.animations") != 0;
    s.font = Trim(Str(L"Look.font"));
    if (s.font.empty()) s.font = L"Segoe UI";
    g_set = s;
}

// ---- Hotkey text ----------------------------------------------------------

static UINT KeyNameToVk(const std::wstring& name) {
    std::wstring k = Lower(name);
    if (k.size() == 1) {
        wchar_t c = (wchar_t)towupper(k[0]);
        if ((c >= L'A' && c <= L'Z') || (c >= L'0' && c <= L'9')) return c;
        SHORT scan = VkKeyScanW(k[0]);
        return scan == -1 ? 0 : (scan & 0xFF);
    }
    if (k[0] == L'f' && k.size() <= 3 && iswdigit(k[1])) {
        int n = _wtoi(k.c_str() + 1);
        if (n >= 1 && n <= 24) return VK_F1 + n - 1;
    }
    if (k.rfind(L"numpad", 0) == 0 && k.size() == 7 && iswdigit(k[6])) return VK_NUMPAD0 + (k[6] - L'0');
    static const struct {
        PCWSTR name;
        UINT vk;
    } names[] = {
        {L"space", VK_SPACE},     {L"tab", VK_TAB},          {L"enter", VK_RETURN},    {L"return", VK_RETURN},
        {L"esc", VK_ESCAPE},      {L"escape", VK_ESCAPE},    {L"backspace", VK_BACK},  {L"insert", VK_INSERT},
        {L"ins", VK_INSERT},      {L"delete", VK_DELETE},    {L"del", VK_DELETE},      {L"home", VK_HOME},
        {L"end", VK_END},         {L"pageup", VK_PRIOR},     {L"pgup", VK_PRIOR},      {L"pagedown", VK_NEXT},
        {L"pgdn", VK_NEXT},       {L"up", VK_UP},            {L"down", VK_DOWN},       {L"left", VK_LEFT},
        {L"right", VK_RIGHT},     {L"printscreen", VK_SNAPSHOT}, {L"prtsc", VK_SNAPSHOT}, {L"print", VK_SNAPSHOT},
        {L"pause", VK_PAUSE},     {L"plus", VK_OEM_PLUS},    {L"minus", VK_OEM_MINUS}, {L"comma", VK_OEM_COMMA},
        {L"period", VK_OEM_PERIOD},
    };
    for (auto& n : names)
        if (k == n.name) return n.vk;
    return 0;
}

static bool ParseHotkey(const std::wstring& text, UINT* mods, UINT* vk) {
    *mods = 0;
    *vk = 0;
    std::wstring s = Trim(text);
    if (s.empty()) return false;
    size_t start = 0;
    while (start <= s.size()) {
        size_t plus = s.find(L'+', start);
        if (plus == start && plus + 1 == s.size()) plus = std::wstring::npos;  // "Ctrl++"
        std::wstring part = Trim(s.substr(start, plus == std::wstring::npos ? std::wstring::npos : plus - start));
        std::wstring k = Lower(part);
        if (k == L"ctrl" || k == L"control") *mods |= MOD_CONTROL;
        else if (k == L"alt") *mods |= MOD_ALT;
        else if (k == L"shift") *mods |= MOD_SHIFT;
        else if (k == L"win" || k == L"windows") *mods |= MOD_WIN;
        else if (!part.empty()) {
            *vk = KeyNameToVk(part);
            if (!*vk) return false;
        }
        if (plus == std::wstring::npos) break;
        start = plus + 1;
    }
    return *vk != 0;
}

// ---- Color model ----------------------------------------------------------

static void HsvToRgb(double h, double s, double v, int& r, int& g, int& b) {
    h = std::fmod(h, 360.0);
    if (h < 0) h += 360;
    double c = v * s, x = c * (1 - std::fabs(std::fmod(h / 60.0, 2.0) - 1)), mm = v - c, rr, gg, bb;
    switch ((int)(h / 60.0)) {
        case 0: rr = c, gg = x, bb = 0; break;
        case 1: rr = x, gg = c, bb = 0; break;
        case 2: rr = 0, gg = c, bb = x; break;
        case 3: rr = 0, gg = x, bb = c; break;
        case 4: rr = x, gg = 0, bb = c; break;
        default: rr = c, gg = 0, bb = x; break;
    }
    r = std::clamp((int)std::lround((rr + mm) * 255), 0, 255);
    g = std::clamp((int)std::lround((gg + mm) * 255), 0, 255);
    b = std::clamp((int)std::lround((bb + mm) * 255), 0, 255);
}

// HSV is kept beside RGB so hue and saturation survive grays and black.
struct Color {
    double h = 217, s = 0.452, v = 0.98;
    int r = 137, g = 180, b = 250, a = 255;
    void SetRgb(int R, int G, int B) {
        r = std::clamp(R, 0, 255), g = std::clamp(G, 0, 255), b = std::clamp(B, 0, 255);
        int mx = std::max({r, g, b}), mn = std::min({r, g, b});
        double d = mx - mn;
        v = mx / 255.0;
        if (mx > 0) {
            s = d / mx;
            if (d > 0) {
                double hh = mx == r ? std::fmod((g - b) / d, 6.0) : mx == g ? (b - r) / d + 2 : (r - g) / d + 4;
                hh *= 60;
                if (hh < 0) hh += 360;
                h = hh;
            }
        }
    }
    void SetHsv(double H, double S, double V) {
        h = std::clamp(H, 0.0, 360.0), s = std::clamp(S, 0.0, 1.0), v = std::clamp(V, 0.0, 1.0);
        HsvToRgb(h, s, v, r, g, b);
    }
    UINT32 Rgb() const { return (UINT32)(r << 16 | g << 8 | b); }
    UINT32 Argb() const { return (UINT32)a << 24 | Rgb(); }
    void SetArgb(UINT32 c) {
        a = (c >> 24) & 0xFF;
        SetRgb((c >> 16) & 0xFF, (c >> 8) & 0xFF, c & 0xFF);
    }
};

static Color FromArgb(UINT32 c) {
    Color col;
    col.SetArgb(c);
    return col;
}

static void ToCmyk(const Color& c, double& C, double& M, double& Y, double& K) {
    double R = c.r / 255.0, G = c.g / 255.0, B = c.b / 255.0;
    K = 1 - std::max({R, G, B});
    if (K >= 1) {
        C = M = Y = 0;
        return;
    }
    C = (1 - R - K) / (1 - K), M = (1 - G - K) / (1 - K), Y = (1 - B - K) / (1 - K);
}

static void ToHsl(const Color& c, double& s, double& l) {
    double R = c.r / 255.0, G = c.g / 255.0, B = c.b / 255.0;
    double mx = std::max({R, G, B}), mn = std::min({R, G, B}), d = mx - mn;
    l = (mx + mn) / 2;
    s = d == 0 ? 0 : d / (1 - std::fabs(2 * l - 1));
}

static int Pct(double x) { return (int)std::lround(x * 100); }

static std::wstring Hex6(UINT32 rgb) {
    WCHAR t[16];
    swprintf_s(t, g_set.upper ? L"%06X" : L"%06x", rgb & 0xFFFFFF);
    return t;
}

static std::wstring Hex8(UINT32 argb) {
    WCHAR t[16];
    swprintf_s(t, g_set.upper ? L"%08X" : L"%08x", argb);
    return t;
}

static std::wstring AlphaText(int a) {
    WCHAR t[16];
    swprintf_s(t, L"%.2f", a / 255.0);
    std::wstring s = t;
    while (!s.empty() && s.back() == L'0') s.pop_back();
    if (!s.empty() && s.back() == L'.') s.pop_back();
    return s;
}

static std::wstring Fmt(PCWSTR f, ...) {
    WCHAR t[256];
    va_list args;
    va_start(args, f);
    vswprintf_s(t, f, args);
    va_end(args);
    return t;
}

static std::wstring FormatColor(const Color& c, int format, POINT pos, bool hasPos) {
    double C, M, Y, K, hs, hl;
    ToCmyk(c, C, M, Y, K);
    ToHsl(c, hs, hl);
    int h = (int)std::lround(c.h) % 360;
    switch (format) {
        case 0: return L"#" + Hex6(c.Rgb());
        case 1: return Hex6(c.Rgb());
        case 2: return L"#" + Hex8(c.Argb());
        case 3: return Fmt(L"%d, %d, %d", c.r, c.g, c.b);
        case 4: return Fmt(L"rgb(%d, %d, %d)", c.r, c.g, c.b);
        case 5: return Fmt(L"rgba(%d, %d, %d, %s)", c.r, c.g, c.b, AlphaText(c.a).c_str());
        case 6: return Fmt(L"hsv(%d, %d%%, %d%%)", h, Pct(c.s), Pct(c.v));
        case 7: return Fmt(L"hsl(%d, %d%%, %d%%)", h, Pct(hs), Pct(hl));
        case 8: return Fmt(L"%d%%, %d%%, %d%%, %d%%", Pct(C), Pct(M), Pct(Y), Pct(K));
        case 9: return std::to_wstring(c.Rgb());
        default: break;
    }
    std::wstring out, src = g_set.customFormat;
    for (size_t i = 0; i < src.size(); i++) {
        if (src[i] == L'{') {
            size_t e = src.find(L'}', i);
            if (e != std::wstring::npos) {
                std::wstring k = Lower(src.substr(i + 1, e - i - 1)), v;
                bool known = true;
                if (k == L"hex") v = L"#" + Hex6(c.Rgb());
                else if (k == L"hex8") v = L"#" + Hex8(c.Argb());
                else if (k == L"r") v = std::to_wstring(c.r);
                else if (k == L"g") v = std::to_wstring(c.g);
                else if (k == L"b") v = std::to_wstring(c.b);
                else if (k == L"a") v = std::to_wstring(c.a);
                else if (k == L"h") v = std::to_wstring(h);
                else if (k == L"s") v = std::to_wstring(Pct(c.s));
                else if (k == L"v") v = std::to_wstring(Pct(c.v));
                else if (k == L"c") v = std::to_wstring(Pct(C));
                else if (k == L"m") v = std::to_wstring(Pct(M));
                else if (k == L"y") v = std::to_wstring(Pct(Y));
                else if (k == L"k") v = std::to_wstring(Pct(K));
                else if (k == L"dec") v = std::to_wstring(c.Rgb());
                else if (k == L"x" || k == L"px") v = hasPos ? std::to_wstring(pos.x) : L"";
                else if (k == L"py" || k == L"posy") v = hasPos ? std::to_wstring(pos.y) : L"";
                else known = false;
                if (known) {
                    out += v;
                    i = e;
                    continue;
                }
            }
        }
        out += src[i];
    }
    return out;
}

// Reads #RGB, #RRGGBB, #AARRGGBB, 0x..., rgb(), rgba() and "r, g, b[, a]".
static bool ParseColorText(const std::wstring& text, Color& out, bool* hadAlpha = nullptr) {
    std::wstring s = Lower(Trim(text));
    if (hadAlpha) *hadAlpha = false;
    if (s.empty() || s.size() > 64) return false;
    std::wstring hex = s;
    if (hex[0] == L'#') hex = hex.substr(1);
    else if (hex.rfind(L"0x", 0) == 0) hex = hex.substr(2);
    UINT32 v;
    if ((hex.size() == 3 || hex.size() == 6 || hex.size() == 8) && ParseHexDigits(hex, v) &&
        (s[0] == L'#' || s.rfind(L"0x", 0) == 0 || hex.find_first_of(L"abcdef") != std::wstring::npos || hex.size() != 3)) {
        if (hex.size() == 3) {
            UINT32 r = (v >> 8) & 0xF, g = (v >> 4) & 0xF, b = v & 0xF;
            v = (r * 17) << 16 | (g * 17) << 8 | (b * 17);
        }
        int a = 255;
        if (hex.size() == 8) {
            a = (v >> 24) & 0xFF;
            if (hadAlpha) *hadAlpha = true;
        }
        out.a = a;
        out.SetRgb((v >> 16) & 0xFF, (v >> 8) & 0xFF, v & 0xFF);
        return true;
    }
    std::vector<double> nums;
    std::wstring cur;
    for (size_t i = 0; i <= s.size(); i++) {
        wchar_t c = i < s.size() ? s[i] : L' ';
        if (iswdigit(c) || c == L'.') {
            cur += c;
        } else {
            if (!cur.empty()) nums.push_back(_wtof(cur.c_str()));
            cur.clear();
            if (iswalpha(c) && s.rfind(L"rgb", 0) != 0) return false;
        }
    }
    if (nums.size() != 3 && nums.size() != 4) return false;
    for (int i = 0; i < 3; i++)
        if (nums[i] < 0 || nums[i] > 255) return false;
    int a = 255;
    if (nums.size() == 4) {
        a = nums[3] <= 1.0 ? (int)std::lround(nums[3] * 255) : (int)std::clamp(nums[3], 0.0, 255.0);
        if (hadAlpha) *hadAlpha = true;
    }
    out.a = a;
    out.SetRgb((int)nums[0], (int)nums[1], (int)nums[2]);
    return true;
}

// ---- Shared Direct2D ------------------------------------------------------

ComPtr<ID2D1Factory> g_d2d;
ComPtr<IDWriteFactory> g_dw;
ComPtr<IWICImagingFactory> g_wic;
ComPtr<IDWriteTextFormat> g_fLabel, g_fValue, g_fBig, g_fSmall, g_fBtn, g_fIcon, g_fIconS, g_fIconXS, g_fTitle;
std::wstring g_family, g_iconFamily;

static bool EnsureFactories() {
    if (!g_d2d && FAILED(D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, g_d2d.GetAddressOf()))) return false;
    if (!g_dw && FAILED(DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory),
                                            (IUnknown**)g_dw.GetAddressOf())))
        return false;
    if (!g_wic && FAILED(CoCreateInstance(CLSID_WICImagingFactory, nullptr, CLSCTX_INPROC_SERVER,
                                          IID_PPV_ARGS(g_wic.GetAddressOf()))))
        return false;
    return true;
}

static bool FontExists(const std::wstring& family) {
    ComPtr<IDWriteFontCollection> fc;
    if (FAILED(g_dw->GetSystemFontCollection(fc.GetAddressOf(), FALSE))) return false;
    UINT32 idx;
    BOOL exists = FALSE;
    fc->FindFamilyName(family.c_str(), &idx, &exists);
    return exists;
}

static ComPtr<IDWriteTextFormat> MakeFormat(const std::wstring& family, float size, DWRITE_FONT_WEIGHT weight) {
    ComPtr<IDWriteTextFormat> f;
    g_dw->CreateTextFormat(family.c_str(), nullptr, weight, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, size,
                           L"en-us", f.GetAddressOf());
    if (f) f->SetWordWrapping(DWRITE_WORD_WRAPPING_NO_WRAP);
    return f;
}

static void MakeFormats() {
    g_family = FontExists(g_set.font) ? g_set.font : L"Segoe UI";
    g_iconFamily = FontExists(L"Segoe Fluent Icons") ? L"Segoe Fluent Icons" : L"Segoe MDL2 Assets";
    g_fLabel = MakeFormat(g_family, 12.5f, DWRITE_FONT_WEIGHT_NORMAL);
    g_fValue = MakeFormat(g_family, 13, DWRITE_FONT_WEIGHT_NORMAL);
    g_fBig = MakeFormat(g_family, 26, DWRITE_FONT_WEIGHT_SEMI_BOLD);
    g_fTitle = MakeFormat(g_family, 13, DWRITE_FONT_WEIGHT_SEMI_BOLD);
    g_fSmall = MakeFormat(g_family, 11.5f, DWRITE_FONT_WEIGHT_NORMAL);
    g_fBtn = MakeFormat(g_family, 13, DWRITE_FONT_WEIGHT_SEMI_BOLD);
    g_fIcon = MakeFormat(g_iconFamily, 15, DWRITE_FONT_WEIGHT_NORMAL);
    g_fIconS = MakeFormat(g_iconFamily, 12, DWRITE_FONT_WEIGHT_NORMAL);
    g_fIconXS = MakeFormat(g_iconFamily, 8, DWRITE_FONT_WEIGHT_NORMAL);
}

// Device resources tied to one render target.
struct Res {
    ID2D1RenderTarget* owner = nullptr;
    ComPtr<ID2D1SolidColorBrush> brush;
    ComPtr<ID2D1GradientStopCollection> grad;
    UINT32 gradA = 0, gradB = 0;
    ComPtr<ID2D1BitmapBrush> checker;
    ComPtr<ID2D1Bitmap> boxBmp, sliderBmp;
    ComPtr<ID2D1BitmapBrush> boxBrush, sliderBrush;
    int boxMode = -1;
    double boxKey = -1;
    void Reset() { *this = Res(); }
    bool Ensure(ID2D1RenderTarget* rt) {
        if (owner == rt && brush) return true;
        Reset();
        owner = rt;
        if (FAILED(rt->CreateSolidColorBrush(D2DColor(m::text), brush.GetAddressOf()))) return false;
        UINT32 cells[4] = {0xFF000000 | m::surface1, 0xFF000000 | m::overlay0, 0xFF000000 | m::overlay0,
                           0xFF000000 | m::surface1};
        auto props = D2D1::BitmapProperties(D2D1::PixelFormat(DXGI_FORMAT_B8G8R8A8_UNORM, D2D1_ALPHA_MODE_PREMULTIPLIED));
        ComPtr<ID2D1Bitmap> cb;
        if (SUCCEEDED(rt->CreateBitmap(D2D1::SizeU(2, 2), cells, 8, props, cb.GetAddressOf())))
            rt->CreateBitmapBrush(cb.Get(),
                                  D2D1::BitmapBrushProperties(D2D1_EXTEND_MODE_WRAP, D2D1_EXTEND_MODE_WRAP,
                                                              D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR),
                                  checker.GetAddressOf());
        rt->CreateBitmap(D2D1::SizeU(256, 256), props, boxBmp.GetAddressOf());
        rt->CreateBitmap(D2D1::SizeU(1, 256), props, sliderBmp.GetAddressOf());
        auto lin = D2D1::BitmapBrushProperties(D2D1_EXTEND_MODE_CLAMP, D2D1_EXTEND_MODE_CLAMP,
                                               D2D1_BITMAP_INTERPOLATION_MODE_LINEAR);
        if (boxBmp) rt->CreateBitmapBrush(boxBmp.Get(), lin, boxBrush.GetAddressOf());
        if (sliderBmp) rt->CreateBitmapBrush(sliderBmp.Get(), lin, sliderBrush.GetAddressOf());
        return true;
    }
};

static D2D1_RECT_F Inflate(D2D1_RECT_F r, float d) { return {r.left - d, r.top - d, r.right + d, r.bottom + d}; }
static bool InRect(const D2D1_RECT_F& r, float x, float y) { return x >= r.left && x < r.right && y >= r.top && y < r.bottom; }

struct Painter {
    ID2D1RenderTarget* rt;
    Res& res;
    void Fill(D2D1_RECT_F r, UINT32 rgb, float a, float rad) {
        res.brush->SetColor(D2DColor(rgb, a));
        if (rad > 0) rt->FillRoundedRectangle(D2D1::RoundedRect(r, rad, rad), res.brush.Get());
        else rt->FillRectangle(r, res.brush.Get());
    }
    void Stroke(D2D1_RECT_F r, UINT32 rgb, float a, float rad, float w) {
        res.brush->SetColor(D2DColor(rgb, a));
        D2D1_RECT_F i = Inflate(r, -w / 2);
        float rr = std::max(0.0f, rad - w / 2);
        if (rad > 0) rt->DrawRoundedRectangle(D2D1::RoundedRect(i, rr, rr), res.brush.Get(), w);
        else rt->DrawRectangle(i, res.brush.Get(), w);
    }
    ComPtr<ID2D1LinearGradientBrush> Grad(D2D1_RECT_F r, float a) {
        if (!res.grad || res.gradA != g_set.accent || res.gradB != g_set.accent2) {
            D2D1_GRADIENT_STOP st[2] = {{0, D2DColor(g_set.accent)}, {1, D2DColor(g_set.accent2)}};
            res.grad.Reset();
            rt->CreateGradientStopCollection(st, 2, res.grad.GetAddressOf());
            res.gradA = g_set.accent, res.gradB = g_set.accent2;
        }
        ComPtr<ID2D1LinearGradientBrush> br;
        rt->CreateLinearGradientBrush(D2D1::LinearGradientBrushProperties({r.left, r.top}, {r.right, r.bottom}),
                                      D2D1::BrushProperties(a), res.grad.Get(), br.GetAddressOf());
        return br;
    }
    void GradFill(D2D1_RECT_F r, float rad, float a) {
        auto br = Grad(r, a);
        if (br) rt->FillRoundedRectangle(D2D1::RoundedRect(r, rad, rad), br.Get());
    }
    void GradStroke(D2D1_RECT_F r, float rad, float w, float a) {
        if (a <= 0.01f) return;
        auto br = Grad(r, a);
        D2D1_RECT_F i = Inflate(r, -w / 2);
        float rr = std::max(0.0f, rad - w / 2);
        if (br) rt->DrawRoundedRectangle(D2D1::RoundedRect(i, rr, rr), br.Get(), w);
    }
    void Checker(D2D1_RECT_F r, float rad) {
        if (!res.checker) return;
        res.checker->SetTransform(D2D1::Matrix3x2F::Scale(5, 5) * D2D1::Matrix3x2F::Translation(r.left, r.top));
        rt->FillRoundedRectangle(D2D1::RoundedRect(r, rad, rad), res.checker.Get());
    }
    void Text(IDWriteTextFormat* f, const std::wstring& s, D2D1_RECT_F r, UINT32 rgb, float a = 1,
              DWRITE_TEXT_ALIGNMENT al = DWRITE_TEXT_ALIGNMENT_LEADING) {
        if (!f || s.empty()) return;
        f->SetTextAlignment(al);
        f->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
        res.brush->SetColor(D2DColor(rgb, a));
        rt->DrawText(s.c_str(), (UINT32)s.size(), f, r, res.brush.Get(), D2D1_DRAW_TEXT_OPTIONS_CLIP);
    }
    void Glyph(IDWriteTextFormat* f, UINT cp, D2D1_RECT_F r, UINT32 rgb, float a = 1) {
        WCHAR s[2] = {(WCHAR)cp, 0};
        Text(f, s, r, rgb, a, DWRITE_TEXT_ALIGNMENT_CENTER);
    }
};

static float Luma(UINT32 rgb) {
    return (0.299f * ((rgb >> 16) & 0xFF) + 0.587f * ((rgb >> 8) & 0xFF) + 0.114f * (rgb & 0xFF)) / 255.0f;
}

// ---- Saved state ----------------------------------------------------------

std::vector<UINT32> g_recent;
UINT32 g_lastColor = 0xFF000000 | m::blue;

static void LoadState() {
    WCHAR buf[512] = {};
    g_recent.clear();
    Wh_GetStringValue(L"Recent", buf, ARRAYSIZE(buf));
    std::wstring s = buf;
    size_t start = 0;
    while (start < s.size()) {
        size_t comma = s.find(L',', start);
        std::wstring item = s.substr(start, comma == std::wstring::npos ? std::wstring::npos : comma - start);
        UINT32 v;
        if (item.size() == 8 && ParseHexDigits(item, v)) g_recent.push_back(v);
        if (comma == std::wstring::npos) break;
        start = comma + 1;
    }
    buf[0] = 0;
    Wh_GetStringValue(L"LastColor", buf, ARRAYSIZE(buf));
    UINT32 v;
    if (wcslen(buf) == 8 && ParseHexDigits(buf, v)) g_lastColor = v;
}

static void SaveRecent() {
    std::wstring s;
    for (UINT32 c : g_recent) {
        if (!s.empty()) s += L',';
        s += Fmt(L"%08X", c);
    }
    Wh_SetStringValue(L"Recent", s.c_str());
}

static void AddRecent(UINT32 argb) {
    g_recent.erase(std::remove(g_recent.begin(), g_recent.end(), argb), g_recent.end());
    g_recent.insert(g_recent.begin(), argb);
    if ((int)g_recent.size() > 24) g_recent.resize(24);
    SaveRecent();
}

static void SaveLast(UINT32 argb) {
    g_lastColor = argb;
    Wh_SetStringValue(L"LastColor", Fmt(L"%08X", argb).c_str());
}

// ---- Clipboard ------------------------------------------------------------

static bool OpenClip(HWND hwnd) {
    for (int i = 0; i < 10; i++) {
        if (OpenClipboard(hwnd)) return true;
        Sleep(15);
    }
    return false;
}

static bool SetClipText(HWND hwnd, const std::wstring& s) {
    if (!OpenClip(hwnd)) return false;
    EmptyClipboard();
    size_t bytes = (s.size() + 1) * sizeof(WCHAR);
    HGLOBAL mem = GlobalAlloc(GMEM_MOVEABLE, bytes);
    bool ok = false;
    if (mem) {
        memcpy(GlobalLock(mem), s.c_str(), bytes);
        GlobalUnlock(mem);
        ok = SetClipboardData(CF_UNICODETEXT, mem) != nullptr;
        if (!ok) GlobalFree(mem);
    }
    CloseClipboard();
    return ok;
}

static std::wstring GetClipText(HWND hwnd) {
    std::wstring s;
    if (!IsClipboardFormatAvailable(CF_UNICODETEXT) || !OpenClip(hwnd)) return s;
    if (HANDLE h = GetClipboardData(CF_UNICODETEXT)) {
        if (auto p = (PCWSTR)GlobalLock(h)) {
            s.assign(p, wcsnlen(p, 256));
            GlobalUnlock(h);
        }
    }
    CloseClipboard();
    return s;
}

// ---- The picker window ----------------------------------------------------

enum HotKind { K_None, K_Box, K_Slider, K_Radio, K_Num, K_Up, K_Down, K_Copy, K_Recent, K_Palette, K_Btn, K_Old };
enum Field { F_H, F_S, F_V, F_R, F_G, F_B, F_A, F_C, F_M, F_Y, F_K, F_HEX, F_DEC, F_POS, F_COUNT };
enum Button { B_PICK, B_CLIP, B_GEAR, B_COPY, B_CLOSE };
enum CopyGroup { G_HSB, G_RGB, G_CMYK, G_HEX, G_DEC, G_POS };

struct FieldDef {
    PCWSTR label, unit;
    int col, row, mode, lo, hi, group;
};
static const FieldDef kFields[F_COUNT] = {
    {L"Hue", L"°", 0, 0, 0, 0, 360, G_HSB},      {L"Saturation", L"%", 0, 1, 1, 0, 100, -1},
    {L"Brightness", L"%", 0, 2, 2, 0, 100, -1},       {L"Red", L"", 0, 3, 3, 0, 255, G_RGB},
    {L"Green", L"", 0, 4, 4, 0, 255, -1},             {L"Blue", L"", 0, 5, 5, 0, 255, -1},
    {L"Alpha", L"", 0, 6, -1, 0, 255, -1},            {L"Cyan", L"%", 1, 0, -1, 0, 100, G_CMYK},
    {L"Magenta", L"%", 1, 1, -1, 0, 100, -1},         {L"Yellow", L"%", 1, 2, -1, 0, 100, -1},
    {L"Key", L"%", 1, 3, -1, 0, 100, -1},             {L"Hex", L"", 1, 4, -1, 0, 0, G_HEX},
    {L"Decimal", L"", 1, 5, -1, 0, 0xFFFFFF, G_DEC},  {L"Position", L"", 1, 6, -1, 0, 0, G_POS},
};

struct MochaName {
    UINT32 rgb;
    PCWSTR name;
};
static const MochaName kMocha[] = {
    {m::rosewater, L"Rosewater"}, {m::flamingo, L"Flamingo"}, {m::pink, L"Pink"},       {m::mauve, L"Mauve"},
    {m::red, L"Red"},             {m::maroon, L"Maroon"},     {m::peach, L"Peach"},     {m::yellow, L"Yellow"},
    {m::green, L"Green"},         {m::teal, L"Teal"},         {m::sky, L"Sky"},         {m::sapphire, L"Sapphire"},
    {m::blue, L"Blue"},           {m::lavender, L"Lavender"}, {m::text, L"Text"},       {m::subtext1, L"Subtext 1"},
    {m::subtext0, L"Subtext 0"},  {m::overlay2, L"Overlay 2"}, {m::overlay1, L"Overlay 1"}, {m::overlay0, L"Overlay 0"},
    {m::surface2, L"Surface 2"},  {m::surface1, L"Surface 1"}, {m::surface0, L"Surface 0"}, {m::base, L"Base"},
    {m::mantle, L"Mantle"},       {m::crust, L"Crust"},
};
constexpr int kMochaCount = (int)(sizeof(kMocha) / sizeof(kMocha[0]));

struct Hot {
    int kind, arg;
    D2D1_RECT_F r;
};
static int HotId(int kind, int arg) { return kind * 64 + arg; }

constexpr float kW = 848, kPad = 16, kRow0 = 108, kRowPitch = 30, kRowH = 26, kX0 = 368, kX1 = 612;

struct Picker {
    HWND hwnd = nullptr, edit = nullptr;
    HFONT editFont = nullptr;
    HBRUSH editBrush = nullptr;
    ComPtr<ID2D1HwndRenderTarget> rt;
    Res res;
    UINT dpi = 96;
    float w = kW, h = 456;
    Color cur, old;
    POINT pos{0, 0};
    bool hasPos = false;
    int mode = 0;
    std::vector<Hot> hots;
    D2D1_RECT_F box{}, slider{}, swNew{}, swOld{}, bar{}, hint{};
    float recentY = -1, paletteY = -1;
    int hover = -1, press = -1, drag = 0, editing = -1;
    std::map<int, float> glow;
    bool tracking = false, sampling = false, glassOn = false, hiddenForPick = false;
    int tick = 0;
    HICON iconSmall = nullptr, iconBig = nullptr;
};
Picker g_pk;
HWND g_msg = nullptr;
HINSTANCE g_inst = nullptr;
int g_modeOverride = -1;

static int Mode() { return g_modeOverride >= 0 ? g_modeOverride : g_set.sliderMode; }

static void Layout() {
    Picker& p = g_pk;
    p.mode = Mode();
    p.hots.clear();
    auto add = [&](int kind, int arg, D2D1_RECT_F r) { p.hots.push_back({kind, arg, r}); };
    p.box = {kPad, kPad, kPad + 300, kPad + 300};
    p.slider = {328, kPad, 352, kPad + 300};
    add(K_Box, 0, p.box);
    add(K_Slider, 0, p.slider);
    p.swNew = {kX0, kPad, kX0 + 120, kPad + 38};
    p.swOld = {kX0, kPad + 38, kX0 + 120, kPad + 76};
    add(K_Old, 0, p.swOld);
    for (int f = 0; f < F_COUNT; f++) {
        const FieldDef& d = kFields[f];
        float y = kRow0 + d.row * kRowPitch;
        D2D1_RECT_F bx = d.col == 0 ? D2D1_RECT_F{kX0 + 112, y, kX0 + 184, y + kRowH}
                                    : D2D1_RECT_F{kX1 + 78, y, kX1 + 174, y + kRowH};
        if (d.mode >= 0) add(K_Radio, d.mode, {kX0, y, kX0 + 110, y + kRowH});
        if (f != F_POS) add(K_Num, f, bx);
        if (f != F_HEX && f != F_POS) {
            add(K_Up, f, {bx.right - 17, bx.top + 1, bx.right - 1, bx.top + 13});
            add(K_Down, f, {bx.right - 17, bx.top + 13, bx.right - 1, bx.bottom - 1});
        }
        if (d.group >= 0) {
            float cx = d.col == 0 ? kX0 + 208 : kX1 + 194;
            add(K_Copy, d.group, {cx, y + 1, cx + 24, y + kRowH - 1});
        }
    }
    float y = kPad + 300 + 16;
    p.recentY = p.paletteY = -1;
    if (g_set.recentCount > 0) {
        p.recentY = y;
        for (int i = 0; i < g_set.recentCount && i < (int)g_recent.size(); i++)
            add(K_Recent, i, {kPad + 72 + i * 26.0f, y, kPad + 94 + i * 26.0f, y + 22});
        y += 30;
    }
    if (g_set.showPalette) {
        p.paletteY = y;
        for (int i = 0; i < kMochaCount; i++)
            add(K_Palette, i, {kPad + 72 + i * 26.0f, y, kPad + 94 + i * 26.0f, y + 22});
        y += 30;
    }
    y += 4;
    p.bar = {kPad, y, kW - kPad, y + 48};
    float by = y + 7, bh = 34, r = p.bar.right - 7;
    D2D1_RECT_F close{r - 88, by, r, by + bh};
    D2D1_RECT_F copy{close.left - 8 - 108, by, close.left - 8, by + bh};
    D2D1_RECT_F gear{copy.left - 8 - 34, by, copy.left - 8, by + bh};
    D2D1_RECT_F pick{p.bar.left + 7, by, p.bar.left + 7 + 176, by + bh};
    D2D1_RECT_F clip{pick.right + 8, by, pick.right + 8 + 156, by + bh};
    add(K_Btn, B_PICK, pick);
    add(K_Btn, B_CLIP, clip);
    add(K_Btn, B_GEAR, gear);
    add(K_Btn, B_COPY, copy);
    add(K_Btn, B_CLOSE, close);
    p.hint = {clip.right + 14, by, gear.left - 10, by + bh};
    p.w = kW;
    p.h = p.bar.bottom + kPad;
}

static std::wstring FieldText(int f) {
    const Color& c = g_pk.cur;
    double C, M, Y, K;
    ToCmyk(c, C, M, Y, K);
    switch (f) {
        case F_H: return std::to_wstring((int)std::lround(c.h));
        case F_S: return std::to_wstring(Pct(c.s));
        case F_V: return std::to_wstring(Pct(c.v));
        case F_R: return std::to_wstring(c.r);
        case F_G: return std::to_wstring(c.g);
        case F_B: return std::to_wstring(c.b);
        case F_A: return std::to_wstring(c.a);
        case F_C: return std::to_wstring(Pct(C));
        case F_M: return std::to_wstring(Pct(M));
        case F_Y: return std::to_wstring(Pct(Y));
        case F_K: return std::to_wstring(Pct(K));
        case F_HEX: return L"#" + Hex6(c.Rgb());
        case F_DEC: return std::to_wstring(c.Rgb());
        case F_POS: return g_pk.hasPos ? Fmt(L"%d, %d", g_pk.pos.x, g_pk.pos.y) : L"–";
    }
    return L"";
}

static void SetFieldValue(int f, long v) {
    Color& c = g_pk.cur;
    const FieldDef& d = kFields[f];
    v = std::clamp(v, (long)d.lo, (long)d.hi);
    double C, M, Y, K;
    ToCmyk(c, C, M, Y, K);
    switch (f) {
        case F_H: c.SetHsv(v, c.s, c.v); break;
        case F_S: c.SetHsv(c.h, v / 100.0, c.v); break;
        case F_V: c.SetHsv(c.h, c.s, v / 100.0); break;
        case F_R: c.SetRgb(v, c.g, c.b); break;
        case F_G: c.SetRgb(c.r, v, c.b); break;
        case F_B: c.SetRgb(c.r, c.g, v); break;
        case F_A: c.a = v; break;
        case F_C: case F_M: case F_Y: case F_K: {
            (f == F_C ? C : f == F_M ? M : f == F_Y ? Y : K) = v / 100.0;
            c.SetRgb((int)std::lround(255 * (1 - C) * (1 - K)), (int)std::lround(255 * (1 - M) * (1 - K)),
                     (int)std::lround(255 * (1 - Y) * (1 - K)));
            break;
        }
        case F_DEC: c.SetRgb((v >> 16) & 0xFF, (v >> 8) & 0xFF, v & 0xFF); break;
    }
}

static void ApplyFieldText(int f, const std::wstring& t) {
    if (f == F_HEX) {
        Color c = g_pk.cur;
        bool hadAlpha;
        std::wstring s = Trim(t);
        if (!s.empty() && s[0] != L'#' && s.rfind(L"0x", 0) != 0) s = L"#" + s;
        if (ParseColorText(s, c, &hadAlpha)) {
            if (!hadAlpha) c.a = g_pk.cur.a;
            g_pk.cur = c;
        }
        return;
    }
    std::wstring s = Trim(t);
    if (s.empty()) return;
    wchar_t* end = nullptr;
    long v = wcstol(s.c_str(), &end, 10);
    if (end == s.c_str()) return;
    SetFieldValue(f, v);
}

static void StepField(int f, int delta) {
    if (f == F_HEX || f == F_POS) return;
    SetFieldValue(f, _wtol(FieldText(f).c_str()) + delta);
}

// Slider value from 0 (bottom) to 1 (top) for the current mode, and back.
static double SliderT() {
    const Color& c = g_pk.cur;
    switch (g_pk.mode) {
        case 0: return c.h / 360.0;
        case 1: return c.s;
        case 2: return c.v;
        case 3: return c.r / 255.0;
        case 4: return c.g / 255.0;
        default: return c.b / 255.0;
    }
}

static void SetSliderT(double t) {
    Color& c = g_pk.cur;
    t = std::clamp(t, 0.0, 1.0);
    int v = (int)std::lround(t * 255);
    switch (g_pk.mode) {
        case 0: c.SetHsv(t * 360, c.s, c.v); break;
        case 1: c.SetHsv(c.h, t, c.v); break;
        case 2: c.SetHsv(c.h, c.s, t); break;
        case 3: c.SetRgb(v, c.g, c.b); break;
        case 4: c.SetRgb(c.r, v, c.b); break;
        default: c.SetRgb(c.r, c.g, v); break;
    }
}

// Box position (0..1 each, y from the top) for the current mode, and back.
static void BoxXY(double& x, double& y) {
    const Color& c = g_pk.cur;
    switch (g_pk.mode) {
        case 0: x = c.s, y = 1 - c.v; break;
        case 1: x = c.h / 360.0, y = 1 - c.v; break;
        case 2: x = c.h / 360.0, y = 1 - c.s; break;
        case 3: x = c.b / 255.0, y = 1 - c.g / 255.0; break;
        case 4: x = c.b / 255.0, y = 1 - c.r / 255.0; break;
        default: x = c.r / 255.0, y = 1 - c.g / 255.0; break;
    }
}

static void SetBoxXY(double x, double y) {
    Color& c = g_pk.cur;
    x = std::clamp(x, 0.0, 1.0), y = std::clamp(y, 0.0, 1.0);
    int X = (int)std::lround(x * 255), Y = (int)std::lround((1 - y) * 255);
    switch (g_pk.mode) {
        case 0: c.SetHsv(c.h, x, 1 - y); break;
        case 1: c.SetHsv(x * 360, c.s, 1 - y); break;
        case 2: c.SetHsv(x * 360, 1 - y, c.v); break;
        case 3: c.SetRgb(c.r, Y, X); break;
        case 4: c.SetRgb(Y, c.g, X); break;
        default: c.SetRgb(X, Y, c.b); break;
    }
}

static UINT32 BoxPixel(int mode, double sv, int x, int y) {
    int r, g, b;
    double fx = x / 255.0, fy = 1 - y / 255.0;
    int X = x, Y = 255 - y, S = (int)std::lround(sv * 255);
    switch (mode) {
        case 0: HsvToRgb(sv * 360, fx, fy, r, g, b); break;
        case 1: HsvToRgb(fx * 360, sv, fy, r, g, b); break;
        case 2: HsvToRgb(fx * 360, fy, sv, r, g, b); break;
        case 3: r = S, g = Y, b = X; break;
        case 4: r = Y, g = S, b = X; break;
        default: r = X, g = Y, b = S; break;
    }
    return 0xFF000000u | (UINT32)(r << 16 | g << 8 | b);
}

static void UpdateBitmaps(Res& res) {
    const Color& c = g_pk.cur;
    double key = SliderT();
    if (res.boxBmp && (res.boxMode != g_pk.mode || std::fabs(res.boxKey - key) > 1e-9)) {
        static std::vector<UINT32> px(256 * 256);
        for (int y = 0; y < 256; y++)
            for (int x = 0; x < 256; x++) px[y * 256 + x] = BoxPixel(g_pk.mode, key, x, y);
        res.boxBmp->CopyFromMemory(nullptr, px.data(), 256 * 4);
        res.boxMode = g_pk.mode, res.boxKey = key;
    }
    if (res.sliderBmp) {
        UINT32 col[256];
        for (int i = 0; i < 256; i++) {
            double t = 1 - i / 255.0;
            int r = c.r, g = c.g, b = c.b, v = (int)std::lround(t * 255);
            switch (g_pk.mode) {
                case 0: HsvToRgb(t * 360, 1, 1, r, g, b); break;
                case 1: HsvToRgb(c.h, t, c.v, r, g, b); break;
                case 2: HsvToRgb(c.h, c.s, t, r, g, b); break;
                case 3: r = v; break;
                case 4: g = v; break;
                default: b = v; break;
            }
            col[i] = 0xFF000000u | (UINT32)(r << 16 | g << 8 | b);
        }
        res.sliderBmp->CopyFromMemory(nullptr, col, 4);
    }
}

static float Glow(int id) {
    auto it = g_pk.glow.find(id);
    return it == g_pk.glow.end() ? 0.0f : it->second;
}

static PCWSTR MochaNameOf(UINT32 rgb) {
    for (auto& n : kMocha)
        if (n.rgb == rgb) return n.name;
    return nullptr;
}

static void DrawButton(Painter& P, const Hot& h) {
    Picker& p = g_pk;
    int id = HotId(K_Btn, h.arg);
    float gl = Glow(id), rad = g_set.radius;
    bool pressed = p.press == id && p.hover == id;
    static const UINT glyphs[] = {0xEF3C, 0xE77F, 0xE713, 0xE8C8, 0xE711};
    static const PCWSTR labels[] = {L"Pick from screen", L"From clipboard", L"", L"Copy", L"Close"};
    D2D1_RECT_F r = h.r;
    if (h.arg == B_COPY) {
        P.GradFill(r, rad, 1);
        if (gl > 0) P.Fill(r, 0xFFFFFF, 0.14f * gl, rad);
        if (pressed) P.Fill(r, m::mauve, 0.45f, rad);
    } else {
        P.Fill(r, m::surface0, 0.62f + 0.18f * gl, rad);
        P.Stroke(r, m::surface1, 0.55f * (1 - gl), rad, 1);
        if (pressed) P.Fill(r, m::mauve, 0.22f, rad);
        if (g_set.glow) P.GradStroke(r, rad, 1.5f, gl);
        else P.Stroke(r, g_set.accent, gl, rad, 1.5f);
    }
    UINT32 fg = h.arg == B_COPY ? m::crust : m::text;
    if (h.arg == B_GEAR) {
        P.Glyph(g_fIcon.Get(), glyphs[h.arg], r, gl > 0.5f ? m::text : m::subtext1);
        return;
    }
    IDWriteTextFormat* f = g_fBtn.Get();
    std::wstring label = labels[h.arg];
    ComPtr<IDWriteTextLayout> lay;
    float tw = 0;
    if (SUCCEEDED(g_dw->CreateTextLayout(label.c_str(), (UINT32)label.size(), f, 400, 40, lay.GetAddressOf()))) {
        DWRITE_TEXT_METRICS mt;
        lay->GetMetrics(&mt);
        tw = mt.widthIncludingTrailingWhitespace;
    }
    float total = 16 + 8 + tw, x = (r.left + r.right - total) / 2;
    P.Glyph(g_fIcon.Get(), glyphs[h.arg], {x, r.top, x + 16, r.bottom}, h.arg == B_COPY ? m::crust : g_set.accent);
    P.Text(f, label, {x + 24, r.top, x + 24 + tw + 2, r.bottom}, fg);
}

static void DrawPicker(ID2D1RenderTarget* rt, Res& res, bool glass) {
    Picker& p = g_pk;
    if (!res.Ensure(rt)) return;
    Painter P{rt, res};
    float rad = g_set.radius, small = std::min(rad, 7.0f);
    D2D1_RECT_F all{0, 0, p.w, p.h};
    if (glass) {
        rt->Clear(D2D1::ColorF(0, 0, 0, 0));
        // One tint over the page; it fades in under the native title bar so the two meet without a seam.
        float t = g_set.tint / 100.0f * 0.62f;
        D2D1_GRADIENT_STOP st[2] = {{0, D2DColor(m::crust, 0)}, {1, D2DColor(m::crust, t)}};
        ComPtr<ID2D1GradientStopCollection> sc;
        ComPtr<ID2D1LinearGradientBrush> br;
        rt->CreateGradientStopCollection(st, 2, sc.GetAddressOf());
        if (sc) rt->CreateLinearGradientBrush(D2D1::LinearGradientBrushProperties({0, 0}, {0, 56}), sc.Get(),
                                              br.GetAddressOf());
        if (br) rt->FillRectangle(all, br.Get());
    } else {
        rt->Clear(D2DColor(m::base));
    }
    UpdateBitmaps(res);

    // Color box.
    float boxGlow = std::max(Glow(HotId(K_Box, 0)), p.drag == 1 ? 1.0f : 0.0f);
    if (res.boxBrush) {
        float s = (p.box.right - p.box.left) / 256.0f;
        res.boxBrush->SetTransform(D2D1::Matrix3x2F::Scale(s, s) * D2D1::Matrix3x2F::Translation(p.box.left, p.box.top));
        rt->FillRoundedRectangle(D2D1::RoundedRect(p.box, rad, rad), res.boxBrush.Get());
    }
    P.Stroke(Inflate(p.box, 1), m::surface1, 0.8f, rad + 1, 1);
    if (g_set.glow) P.GradStroke(Inflate(p.box, 2), rad + 2, 1.5f, boxGlow);
    {
        double x, y;
        BoxXY(x, y);
        D2D1_POINT_2F c{p.box.left + (float)x * (p.box.right - p.box.left), p.box.top + (float)y * (p.box.bottom - p.box.top)};
        res.brush->SetColor(D2DColor(m::crust, 0.85f));
        rt->DrawEllipse(D2D1::Ellipse(c, 8.5f, 8.5f), res.brush.Get(), 1.2f);
        res.brush->SetColor(D2DColor(0xFFFFFF));
        rt->DrawEllipse(D2D1::Ellipse(c, 7, 7), res.brush.Get(), 2);
        res.brush->SetColor(D2DColor(p.cur.Rgb()));
        rt->FillEllipse(D2D1::Ellipse(c, 5.5f, 5.5f), res.brush.Get());
    }

    // Slider.
    float slGlow = std::max(Glow(HotId(K_Slider, 0)), p.drag == 2 ? 1.0f : 0.0f);
    if (res.sliderBrush) {
        res.sliderBrush->SetTransform(D2D1::Matrix3x2F::Scale(p.slider.right - p.slider.left, (p.slider.bottom - p.slider.top) / 256.0f) *
                                      D2D1::Matrix3x2F::Translation(p.slider.left, p.slider.top));
        rt->FillRoundedRectangle(D2D1::RoundedRect(p.slider, small, small), res.sliderBrush.Get());
    }
    P.Stroke(Inflate(p.slider, 1), m::surface1, 0.8f, small + 1, 1);
    if (g_set.glow) P.GradStroke(Inflate(p.slider, 2), small + 2, 1.5f, slGlow);
    {
        float y = p.slider.top + (float)(1 - SliderT()) * (p.slider.bottom - p.slider.top);
        D2D1_RECT_F hnd{p.slider.left - 4, y - 4.5f, p.slider.right + 4, y + 4.5f};
        P.Fill(Inflate(hnd, 1), m::crust, 0.85f, 5.5f);
        P.Fill(hnd, 0xFFFFFF, 1, 4.5f);
        if (slGlow > 0) P.GradStroke(Inflate(hnd, 2), 6.5f, 1.5f, slGlow);
    }

    // New and old color.
    {
        D2D1_RECT_F sw{p.swNew.left, p.swNew.top, p.swNew.right, p.swOld.bottom};
        P.Checker(sw, rad);
        rt->PushAxisAlignedClip(p.swNew, D2D1_ANTIALIAS_MODE_ALIASED);
        P.Fill(sw, p.cur.Rgb(), p.cur.a / 255.0f, rad);
        rt->PopAxisAlignedClip();
        rt->PushAxisAlignedClip(p.swOld, D2D1_ANTIALIAS_MODE_ALIASED);
        P.Fill(sw, p.old.Rgb(), p.old.a / 255.0f, rad);
        rt->PopAxisAlignedClip();
        P.Stroke(Inflate(sw, 1), m::surface1, 0.8f, rad + 1, 1);
        float og = Glow(HotId(K_Old, 0));
        if (g_set.glow && og > 0) P.GradStroke(Inflate(p.swOld, 1), small, 1.5f, og);
        UINT32 tn = Luma(p.cur.Rgb()) > 0.55f && p.cur.a > 120 ? m::crust : m::text;
        UINT32 to = Luma(p.old.Rgb()) > 0.55f && p.old.a > 120 ? m::crust : m::text;
        P.Text(g_fSmall.Get(), L"New", {p.swNew.left + 10, p.swNew.top, p.swNew.right, p.swNew.bottom}, tn, 0.85f);
        P.Text(g_fSmall.Get(), L"Old", {p.swOld.left + 10, p.swOld.top, p.swOld.right, p.swOld.bottom}, to, 0.85f);
    }

    // Big readout.
    {
        float x = kX0 + 136;
        P.Text(g_fBig.Get(), L"#" + Hex6(p.cur.Rgb()), {x, kPad - 2, p.w - kPad, kPad + 36}, m::text);
        std::wstring as = FormatColor(p.cur, g_set.copyFormat, p.pos, p.hasPos);
        P.Text(g_fSmall.Get(), L"Copies as", {x, kPad + 38, x + 80, kPad + 56}, m::subtext0);
        P.Text(g_fSmall.Get(), as, {x + 78, kPad + 38, p.w - kPad, kPad + 56}, m::text);
        PCWSTR name = MochaNameOf(p.cur.Rgb());
        std::wstring line = name ? std::wstring(L"Mocha ") + name : (p.cur.a < 255 ? L"Opacity " + std::to_wstring(Pct(p.cur.a / 255.0)) + L"%" : L"");
        if (!line.empty()) {
            auto br = P.Grad({x, kPad + 58, x + 160, kPad + 76}, 1);
            g_fSmall->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
            g_fSmall->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
            if (br) rt->DrawText(line.c_str(), (UINT32)line.size(), g_fSmall.Get(), {x, kPad + 58, p.w - kPad, kPad + 76}, br.Get());
        }
    }

    // Value rows.
    for (int f = 0; f < F_COUNT; f++) {
        const FieldDef& d = kFields[f];
        float y = kRow0 + d.row * kRowPitch;
        float lx = d.col == 0 ? kX0 + 22 : kX1;
        if (d.mode >= 0) {
            D2D1_POINT_2F c{kX0 + 8, y + kRowH / 2};
            bool on = p.mode == d.mode;
            float gl = Glow(HotId(K_Radio, d.mode));
            if (on) {
                auto br = P.Grad({c.x - 7, c.y - 7, c.x + 7, c.y + 7}, 1);
                if (br) {
                    rt->DrawEllipse(D2D1::Ellipse(c, 6.5f, 6.5f), br.Get(), 1.6f);
                    rt->FillEllipse(D2D1::Ellipse(c, 3.5f, 3.5f), br.Get());
                }
            } else {
                res.brush->SetColor(D2DColor(gl > 0 ? m::overlay2 : m::surface2, 0.7f + 0.3f * gl));
                rt->DrawEllipse(D2D1::Ellipse(c, 6.5f, 6.5f), res.brush.Get(), 1.4f);
            }
        }
        bool radioHot = d.mode >= 0 && (p.mode == d.mode || Glow(HotId(K_Radio, d.mode)) > 0.5f);
        P.Text(g_fLabel.Get(), d.label, {lx, y, lx + 90, y + kRowH}, radioHot ? m::text : m::subtext1);
        D2D1_RECT_F bx = d.col == 0 ? D2D1_RECT_F{kX0 + 112, y, kX0 + 184, y + kRowH}
                                    : D2D1_RECT_F{kX1 + 78, y, kX1 + 174, y + kRowH};
        bool ro = f == F_POS;
        float gl = ro ? 0 : Glow(HotId(K_Num, f));
        bool editing = p.editing == f;
        P.Fill(bx, ro ? m::mantle : m::surface0, ro ? 0.5f : 0.6f + 0.15f * gl, small);
        P.Stroke(bx, m::surface1, (ro ? 0.4f : 0.7f) * (1 - gl), small, 1);
        if (editing) P.GradStroke(bx, small, 1.5f, 1);
        else if (g_set.glow) P.GradStroke(bx, small, 1.5f, gl);
        else if (gl > 0) P.Stroke(bx, g_set.accent, gl, small, 1.5f);
        bool spins = f != F_HEX && f != F_POS;
        if (!editing) {
            D2D1_RECT_F tr{bx.left + 6, bx.top, bx.right - (spins ? 18 : 6), bx.bottom};
            P.Text(g_fValue.Get(), FieldText(f), tr, ro ? m::subtext0 : m::text, 1, DWRITE_TEXT_ALIGNMENT_CENTER);
        }
        if (spins && !editing) {
            float gu = Glow(HotId(K_Up, f)), gd = Glow(HotId(K_Down, f));
            P.Glyph(g_fIconXS.Get(), 0xE70E, {bx.right - 17, bx.top + 2, bx.right - 3, bx.top + 13}, gu > 0.5f ? g_set.accent : m::overlay1);
            P.Glyph(g_fIconXS.Get(), 0xE70D, {bx.right - 17, bx.top + 13, bx.right - 3, bx.bottom - 2}, gd > 0.5f ? g_set.accent2 : m::overlay1);
        }
        float ux = d.col == 0 ? kX0 + 187 : kX1 + 177;
        P.Text(g_fLabel.Get(), d.unit, {ux, y, ux + 18, y + kRowH}, m::overlay1);
        if (d.group >= 0) {
            float cx = d.col == 0 ? kX0 + 208 : kX1 + 194;
            D2D1_RECT_F cr{cx, y + 1, cx + 24, y + kRowH - 1};
            float cg = Glow(HotId(K_Copy, d.group));
            bool pr = p.press == HotId(K_Copy, d.group) && p.hover == p.press;
            P.Fill(cr, pr ? m::mauve : m::surface0, pr ? 0.3f : 0.35f + 0.35f * cg, small);
            if (g_set.glow) P.GradStroke(cr, small, 1.2f, cg);
            P.Glyph(g_fIconS.Get(), 0xE8C8, cr, cg > 0.5f ? m::text : m::overlay2);
        }
    }

    // Recent colors and the palette.
    auto swatch = [&](D2D1_RECT_F r, UINT32 argb, int id) {
        float gl = Glow(id);
        D2D1_RECT_F rr = Inflate(r, 1.5f * gl);
        float sr = std::min(rad, 6.0f);
        if ((argb >> 24) < 255) P.Checker(rr, sr);
        P.Fill(rr, argb & 0xFFFFFF, (argb >> 24) / 255.0f, sr);
        P.Stroke(rr, m::crust, 0.5f, sr, 1);
        if (gl > 0) P.GradStroke(Inflate(rr, 2), sr + 2, 1.5f, gl);
    };
    if (p.recentY >= 0) {
        P.Text(g_fSmall.Get(), L"Recent", {kPad, p.recentY, kPad + 70, p.recentY + 22}, m::subtext0);
        for (int i = 0; i < g_set.recentCount; i++) {
            D2D1_RECT_F r{kPad + 72 + i * 26.0f, p.recentY, kPad + 94 + i * 26.0f, p.recentY + 22};
            if (i < (int)g_recent.size()) swatch(r, g_recent[i], HotId(K_Recent, i));
            else P.Stroke(r, m::surface1, 0.45f, std::min(rad, 6.0f), 1);
        }
    }
    if (p.paletteY >= 0) {
        P.Text(g_fSmall.Get(), L"Mocha", {kPad, p.paletteY, kPad + 70, p.paletteY + 22}, m::subtext0);
        for (int i = 0; i < kMochaCount; i++)
            swatch({kPad + 72 + i * 26.0f, p.paletteY, kPad + 94 + i * 26.0f, p.paletteY + 22}, 0xFF000000 | kMocha[i].rgb,
                   HotId(K_Palette, i));
    }

    // Bottom dock.
    P.Fill(p.bar, m::mantle, glass ? 0.55f : 1.0f, rad + 4);
    P.Stroke(p.bar, m::surface0, 0.9f, rad + 4, 1);
    for (const Hot& h : p.hots)
        if (h.kind == K_Btn) DrawButton(P, h);
    std::wstring hint = p.sampling ? L"Sampling under the mouse" : g_set.livePick ? L"Hold Ctrl to sample" : L"P picks from the screen";
    P.Text(g_fSmall.Get(), hint, p.hint, p.sampling ? g_set.accent : m::overlay1);
}

// ---- Window icon ----------------------------------------------------------

static HICON MakeIcon(int px) {
    if (px <= 0 || !EnsureFactories()) return nullptr;
    ComPtr<IWICBitmap> bmp;
    ComPtr<ID2D1RenderTarget> rt;
    if (FAILED(g_wic->CreateBitmap(px, px, GUID_WICPixelFormat32bppPBGRA, WICBitmapCacheOnLoad, bmp.GetAddressOf()))) return nullptr;
    auto props = D2D1::RenderTargetProperties(D2D1_RENDER_TARGET_TYPE_SOFTWARE,
                                              D2D1::PixelFormat(DXGI_FORMAT_B8G8R8A8_UNORM, D2D1_ALPHA_MODE_PREMULTIPLIED), 96, 96);
    if (FAILED(g_d2d->CreateWicBitmapRenderTarget(bmp.Get(), props, rt.GetAddressOf()))) return nullptr;
    Res res;
    rt->BeginDraw();
    rt->Clear(D2D1::ColorF(0, 0, 0, 0));
    if (res.Ensure(rt.Get())) {
        Painter P{rt.Get(), res};
        float in = px * 0.06f;
        D2D1_RECT_F r{in, in, px - in, px - in};
        P.GradFill(r, px * 0.24f, 1);
        auto f = MakeFormat(g_iconFamily.empty() ? L"Segoe MDL2 Assets" : g_iconFamily, px * 0.56f, DWRITE_FONT_WEIGHT_NORMAL);
        P.Glyph(f.Get(), 0xEF3C, r, m::crust);
    }
    rt->EndDraw();
    std::vector<BYTE> buf(px * px * 4);
    WICRect wr{0, 0, px, px};
    bmp->CopyPixels(&wr, px * 4, (UINT)buf.size(), buf.data());
    BITMAPV5HEADER bi{};
    bi.bV5Size = sizeof(bi);
    bi.bV5Width = px;
    bi.bV5Height = -px;
    bi.bV5Planes = 1;
    bi.bV5BitCount = 32;
    bi.bV5Compression = BI_RGB;
    void* bits = nullptr;
    HDC dc = GetDC(nullptr);
    HBITMAP color = CreateDIBSection(dc, (BITMAPINFO*)&bi, DIB_RGB_COLORS, &bits, nullptr, 0);
    ReleaseDC(nullptr, dc);
    if (!color) return nullptr;
    BYTE* out = (BYTE*)bits;
    for (int i = 0; i < px * px; i++) {
        BYTE a = buf[i * 4 + 3];
        for (int c = 0; c < 3; c++) out[i * 4 + c] = a ? (BYTE)std::min(255, buf[i * 4 + c] * 255 / a) : 0;
        out[i * 4 + 3] = a;
    }
    HBITMAP mask = CreateBitmap(px, px, 1, 1, nullptr);
    ICONINFO ii{TRUE, 0, 0, mask, color};
    HICON icon = CreateIconIndirect(&ii);
    DeleteObject(mask);
    DeleteObject(color);
    return icon;
}

// ---- Picker window behaviour ---------------------------------------------

static void StartScreenPick(int origin);
static void ShowToast(UINT32 argb, const std::wstring& text);

static int PxOf(float dip) { return MulDiv((int)std::lround(dip * 16), g_pk.dpi, 96 * 16); }

static void Invalidate() {
    if (g_pk.hwnd) InvalidateRect(g_pk.hwnd, nullptr, FALSE);
}

static void ApplyGlass(HWND hwnd, bool glass) {
    BOOL dark = TRUE;
    DwmSetWindowAttribute(hwnd, 20, &dark, sizeof(dark));
    if (glass) {
        int backdrop = 3;  // DWMSBT_TRANSIENTWINDOW
        DwmSetWindowAttribute(hwnd, 38, &backdrop, sizeof(backdrop));
        MARGINS mg{-1, -1, -1, -1};
        DwmExtendFrameIntoClientArea(hwnd, &mg);
        COLORREF none = 0xFFFFFFFE;
        DwmSetWindowAttribute(hwnd, 35, &none, sizeof(none));
    } else {
        int backdrop = 1;  // DWMSBT_NONE
        DwmSetWindowAttribute(hwnd, 38, &backdrop, sizeof(backdrop));
        MARGINS mg{0, 0, 0, 0};
        DwmExtendFrameIntoClientArea(hwnd, &mg);
        COLORREF cap = scpset::RefFromRgb(m::crust);
        DwmSetWindowAttribute(hwnd, 35, &cap, sizeof(cap));
    }
    COLORREF text = scpset::RefFromRgb(m::text);
    DwmSetWindowAttribute(hwnd, 36, &text, sizeof(text));
}

static void ResizeToLayout() {
    Picker& p = g_pk;
    if (!p.hwnd) return;
    RECT r{0, 0, PxOf(p.w), PxOf(p.h)};
    DWORD style = (DWORD)GetWindowLongPtrW(p.hwnd, GWL_STYLE), ex = (DWORD)GetWindowLongPtrW(p.hwnd, GWL_EXSTYLE);
    AdjustWindowRectExForDpi(&r, style, FALSE, ex, p.dpi);
    SetWindowPos(p.hwnd, nullptr, 0, 0, r.right - r.left, r.bottom - r.top, SWP_NOMOVE | SWP_NOZORDER | SWP_NOACTIVATE);
}

static void MakeEditFont() {
    Picker& p = g_pk;
    if (p.editFont) DeleteObject(p.editFont);
    p.editFont = CreateFontW(-MulDiv(13, p.dpi, 72) * 72 / 96, 0, 0, 0, FW_NORMAL, 0, 0, 0, DEFAULT_CHARSET, 0, 0,
                             CLEARTYPE_QUALITY, 0, g_family.c_str());
    if (p.edit) SendMessageW(p.edit, WM_SETFONT, (WPARAM)p.editFont, TRUE);
}

static void EndEdit(bool commit) {
    Picker& p = g_pk;
    if (p.editing < 0) return;
    int f = p.editing;
    p.editing = -1;
    if (commit) {
        WCHAR t[64] = {};
        GetWindowTextW(p.edit, t, ARRAYSIZE(t));
        ApplyFieldText(f, t);
    }
    ShowWindow(p.edit, SW_HIDE);
    SetFocus(p.hwnd);
    Invalidate();
}

static void BeginEdit(int f) {
    Picker& p = g_pk;
    if (!p.edit) return;
    EndEdit(true);
    for (const Hot& h : p.hots) {
        if (h.kind != K_Num || h.arg != f) continue;
        p.editing = f;
        bool spins = f != F_HEX;
        RECT r{PxOf(h.r.left + 5), PxOf(h.r.top + 4), PxOf(h.r.right - (spins ? 18 : 5)), PxOf(h.r.bottom - 4)};
        SetWindowTextW(p.edit, FieldText(f).c_str());
        SetWindowPos(p.edit, HWND_TOP, r.left, r.top, r.right - r.left, r.bottom - r.top, SWP_SHOWWINDOW);
        SetFocus(p.edit);
        SendMessageW(p.edit, EM_SETSEL, 0, -1);
        Invalidate();
        return;
    }
}

static LRESULT CALLBACK EditProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp, UINT_PTR, DWORD_PTR) {
    if (msg == WM_KEYDOWN) {
        if (wp == VK_RETURN) {
            EndEdit(true);
            return 0;
        }
        if (wp == VK_ESCAPE) {
            EndEdit(false);
            return 0;
        }
        if (wp == VK_TAB) {
            int f = g_pk.editing;
            bool back = GetKeyState(VK_SHIFT) & 0x8000;
            EndEdit(true);
            int n = (f + (back ? F_POS - 1 : 1)) % F_POS;
            BeginEdit(n);
            return 0;
        }
        if (wp == VK_UP || wp == VK_DOWN) {
            int f = g_pk.editing;
            WCHAR t[64] = {};
            GetWindowTextW(hwnd, t, ARRAYSIZE(t));
            ApplyFieldText(f, t);
            StepField(f, (wp == VK_UP ? 1 : -1) * ((GetKeyState(VK_SHIFT) & 0x8000) ? 10 : 1));
            SetWindowTextW(hwnd, FieldText(f).c_str());
            SendMessageW(hwnd, EM_SETSEL, 0, -1);
            Invalidate();
            return 0;
        }
    } else if (msg == WM_CHAR && (wp == VK_RETURN || wp == VK_ESCAPE || wp == VK_TAB)) {
        return 0;
    } else if (msg == WM_KILLFOCUS) {
        LRESULT r = DefSubclassProc(hwnd, msg, wp, lp);
        if (g_pk.editing >= 0) EndEdit(true);
        return r;
    }
    return DefSubclassProc(hwnd, msg, wp, lp);
}

static void DoCopyText(const std::wstring& text, UINT32 argb) {
    HWND owner = g_pk.hwnd ? g_pk.hwnd : g_msg;
    if (!SetClipText(owner, text)) return;
    AddRecent(argb);
    SaveLast(argb);
    if (g_set.toast) ShowToast(argb, text);
    if (g_pk.hwnd) {
        Layout();
        Invalidate();
    }
}

static void CopyMain() {
    Picker& p = g_pk;
    DoCopyText(FormatColor(p.cur, g_set.copyFormat, p.pos, p.hasPos), p.cur.Argb());
    if (g_set.closeAfterCopy && p.hwnd) PostMessageW(p.hwnd, WM_CLOSE, 0, 0);
}

static void CopyGroup(int g) {
    Picker& p = g_pk;
    const Color& c = p.cur;
    double C, M, Y, K;
    ToCmyk(c, C, M, Y, K);
    std::wstring t;
    switch (g) {
        case G_HSB: t = Fmt(L"%d, %d%%, %d%%", (int)std::lround(c.h) % 360, Pct(c.s), Pct(c.v)); break;
        case G_RGB: t = Fmt(L"%d, %d, %d", c.r, c.g, c.b); break;
        case G_CMYK: t = Fmt(L"%d%%, %d%%, %d%%, %d%%", Pct(C), Pct(M), Pct(Y), Pct(K)); break;
        case G_HEX: t = L"#" + Hex6(c.Rgb()); break;
        case G_DEC: t = std::to_wstring(c.Rgb()); break;
        case G_POS:
            if (!p.hasPos) return;
            t = Fmt(L"%d, %d", p.pos.x, p.pos.y);
            break;
    }
    DoCopyText(t, c.Argb());
}

static void PasteColor() {
    Color c = g_pk.cur;
    bool hadAlpha;
    if (ParseColorText(GetClipText(g_pk.hwnd), c, &hadAlpha)) {
        if (!hadAlpha) c.a = g_pk.cur.a;
        g_pk.cur = c;
        Invalidate();
    } else {
        ShowToast(g_pk.cur.Argb(), L"No color on the clipboard");
    }
}

static void SavePickerState() {
    Picker& p = g_pk;
    if (!p.hwnd) return;
    SaveLast(p.cur.Argb());
    WINDOWPLACEMENT wp{sizeof(wp)};
    if (GetWindowPlacement(p.hwnd, &wp)) {
        Wh_SetIntValue(L"WinX", wp.rcNormalPosition.left);
        Wh_SetIntValue(L"WinY", wp.rcNormalPosition.top);
        Wh_SetIntValue(L"WinSaved", 1);
    }
}

static const Hot* HitTest(float x, float y) {
    const Hot* best = nullptr;
    for (const Hot& h : g_pk.hots)
        if (InRect(h.r, x, y)) best = &h;  // Later entries (spins) sit on top of earlier ones.
    return best;
}

static void DragTo(float x, float y) {
    Picker& p = g_pk;
    if (p.drag == 1) {
        SetBoxXY((x - p.box.left) / (p.box.right - p.box.left), (y - p.box.top) / (p.box.bottom - p.box.top));
    } else if (p.drag == 2) {
        SetSliderT(1 - (y - p.slider.top) / (p.slider.bottom - p.slider.top));
    }
    Invalidate();
}

static void Activate(const Hot& h) {
    Picker& p = g_pk;
    switch (h.kind) {
        case K_Radio:
            g_modeOverride = h.arg;
            p.mode = h.arg;
            break;
        case K_Up: StepField(h.arg, (GetKeyState(VK_SHIFT) & 0x8000) ? 10 : 1); break;
        case K_Down: StepField(h.arg, (GetKeyState(VK_SHIFT) & 0x8000) ? -10 : -1); break;
        case K_Copy: CopyGroup(h.arg); break;
        case K_Recent:
            if (h.arg < (int)g_recent.size()) p.cur = FromArgb(g_recent[h.arg]);
            break;
        case K_Palette: {
            int a = p.cur.a;
            p.cur = FromArgb(0xFF000000 | kMocha[h.arg].rgb);
            p.cur.a = a;
            break;
        }
        case K_Old: p.cur = p.old; break;
        case K_Btn:
            switch (h.arg) {
                case B_PICK: StartScreenPick(0); break;
                case B_CLIP: PasteColor(); break;
                case B_GEAR: scpset::OpenSettingsWindow(); break;
                case B_COPY: CopyMain(); break;
                case B_CLOSE: PostMessageW(p.hwnd, WM_CLOSE, 0, 0); break;
            }
            break;
    }
    Invalidate();
}

static void Tick() {
    Picker& p = g_pk;
    bool changed = false;
    float step = g_set.anim ? 0.28f : 1.0f;
    std::set<int> ids;
    for (auto& [id, v] : p.glow) ids.insert(id);
    if (p.hover >= 0) ids.insert(p.hover);
    for (int id : ids) {
        float target = id == p.hover ? 1.0f : 0.0f, &v = p.glow[id];
        float nv = v + (target - v) * step;
        if (std::fabs(nv - target) < 0.02f) nv = target;
        if (nv != v) changed = true;
        v = nv;
        if (v == 0 && target == 0) p.glow.erase(id);
    }
    // Hold Ctrl to follow the color under the mouse, while the picker is in front.
    bool wasSampling = p.sampling;
    p.sampling = false;
    if (g_set.livePick && p.editing < 0 && GetForegroundWindow() == p.hwnd && (GetAsyncKeyState(VK_CONTROL) & 0x8000) &&
        !(GetAsyncKeyState(VK_LBUTTON) & 0x8000)) {
        POINT pt;
        RECT wr;
        GetCursorPos(&pt);
        GetWindowRect(p.hwnd, &wr);
        if (!PtInRect(&wr, pt)) {
            p.sampling = true;
            if (++p.tick % 2 == 0) {
                HDC dc = GetDC(nullptr);
                COLORREF c = GetPixel(dc, pt.x, pt.y);
                ReleaseDC(nullptr, dc);
                if (c != CLR_INVALID && (c != scpset::RefFromRgb(p.cur.Rgb()) || pt.x != p.pos.x || pt.y != p.pos.y)) {
                    p.cur.SetRgb(GetRValue(c), GetGValue(c), GetBValue(c));
                    p.pos = pt;
                    p.hasPos = true;
                    changed = true;
                }
            }
        }
    }
    if (changed || wasSampling != p.sampling) Invalidate();
}

static void Paint() {
    Picker& p = g_pk;
    if (!p.rt) {
        RECT rc;
        GetClientRect(p.hwnd, &rc);
        auto props = D2D1::RenderTargetProperties(D2D1_RENDER_TARGET_TYPE_DEFAULT,
                                                  D2D1::PixelFormat(DXGI_FORMAT_B8G8R8A8_UNORM, D2D1_ALPHA_MODE_PREMULTIPLIED));
        if (FAILED(g_d2d->CreateHwndRenderTarget(props, D2D1::HwndRenderTargetProperties(p.hwnd, D2D1::SizeU(rc.right, rc.bottom)),
                                                 p.rt.GetAddressOf())))
            return;
        p.res.Reset();
    }
    p.rt->SetDpi((float)p.dpi, (float)p.dpi);
    p.rt->BeginDraw();
    DrawPicker(p.rt.Get(), p.res, p.glassOn);
    if (p.rt->EndDraw() == D2DERR_RECREATE_TARGET) {
        p.rt.Reset();
        p.res.Reset();
    }
}

static LRESULT CALLBACK PickerProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) {
    Picker& p = g_pk;
    auto dipX = [&](LPARAM l) { return GET_X_LPARAM(l) * 96.0f / p.dpi; };
    auto dipY = [&](LPARAM l) { return GET_Y_LPARAM(l) * 96.0f / p.dpi; };
    switch (msg) {
        case WM_PAINT: {
            PAINTSTRUCT ps;
            BeginPaint(hwnd, &ps);
            Paint();
            EndPaint(hwnd, &ps);
            return 0;
        }
        case WM_ERASEBKGND: return 1;
        case WM_SIZE:
            if (p.rt) p.rt->Resize(D2D1::SizeU(LOWORD(lp), HIWORD(lp)));
            Invalidate();
            return 0;
        case WM_DPICHANGED: {
            p.dpi = HIWORD(wp);
            RECT* s = (RECT*)lp;
            SetWindowPos(hwnd, nullptr, s->left, s->top, 0, 0, SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE);
            ResizeToLayout();
            MakeEditFont();
            EndEdit(true);
            Invalidate();
            return 0;
        }
        case WM_CTLCOLOREDIT: {
            HDC dc = (HDC)wp;
            SetTextColor(dc, scpset::RefFromRgb(m::text));
            SetBkColor(dc, scpset::RefFromRgb(m::surface0));
            return (LRESULT)p.editBrush;
        }
        case WM_MOUSEMOVE: {
            float x = dipX(lp), y = dipY(lp);
            if (!p.tracking) {
                TRACKMOUSEEVENT t{sizeof(t), TME_LEAVE, hwnd, 0};
                p.tracking = TrackMouseEvent(&t);
            }
            if (p.drag) {
                DragTo(x, y);
                return 0;
            }
            const Hot* h = HitTest(x, y);
            int id = h ? HotId(h->kind, h->arg) : -1;
            if (id != p.hover) {
                p.hover = id;
                Invalidate();
            }
            return 0;
        }
        case WM_MOUSELEAVE:
            p.tracking = false;
            if (!p.drag) {
                p.hover = -1;
                Invalidate();
            }
            return 0;
        case WM_SETCURSOR:
            if (LOWORD(lp) == HTCLIENT) {
                bool hand = p.hover >= 0 && p.hover / 64 != K_Box && p.hover / 64 != K_Slider && p.hover / 64 != K_Num;
                bool cross = p.hover / 64 == K_Box && p.hover >= 0;
                bool ibeam = p.hover >= 0 && p.hover / 64 == K_Num;
                SetCursor(LoadCursorW(nullptr, cross ? IDC_CROSS : ibeam ? IDC_IBEAM : hand ? IDC_HAND : IDC_ARROW));
                return TRUE;
            }
            break;
        case WM_LBUTTONDOWN: {
            float x = dipX(lp), y = dipY(lp);
            if (p.editing >= 0) EndEdit(true);
            SetFocus(hwnd);
            const Hot* h = HitTest(x, y);
            if (!h) return 0;
            if (h->kind == K_Box || h->kind == K_Slider) {
                p.drag = h->kind == K_Box ? 1 : 2;
                SetCapture(hwnd);
                DragTo(x, y);
            } else if (h->kind == K_Num) {
                BeginEdit(h->arg);
            } else {
                p.press = HotId(h->kind, h->arg);
                SetCapture(hwnd);
                Invalidate();
            }
            return 0;
        }
        case WM_LBUTTONUP: {
            if (GetCapture() == hwnd) ReleaseCapture();
            if (p.drag) {
                p.drag = 0;
                Invalidate();
                return 0;
            }
            int pressed = p.press;
            p.press = -1;
            const Hot* h = HitTest(dipX(lp), dipY(lp));
            if (h && pressed == HotId(h->kind, h->arg)) {
                Hot copy = *h;
                Activate(copy);
            }
            Invalidate();
            return 0;
        }
        case WM_CAPTURECHANGED:
            p.drag = 0;
            return 0;
        case WM_MOUSEWHEEL: {
            POINT pt{GET_X_LPARAM(lp), GET_Y_LPARAM(lp)};
            ScreenToClient(hwnd, &pt);
            float x = pt.x * 96.0f / p.dpi, y = pt.y * 96.0f / p.dpi;
            int dir = GET_WHEEL_DELTA_WPARAM(wp) > 0 ? 1 : -1, mul = (GET_KEYSTATE_WPARAM(wp) & MK_SHIFT) ? 10 : 1;
            const Hot* h = HitTest(x, y);
            if (!h) return 0;
            if (h->kind == K_Num || h->kind == K_Up || h->kind == K_Down) {
                if (p.editing == h->arg) EndEdit(true);
                StepField(h->arg, dir * mul);
            } else if (h->kind == K_Slider || h->kind == K_Box) {
                double unit = p.mode == 0 ? 1 / 360.0 : p.mode <= 2 ? 0.01 : 1 / 255.0;
                SetSliderT(SliderT() + dir * mul * unit);
            }
            Invalidate();
            return 0;
        }
        case WM_KEYDOWN: {
            bool ctrl = GetKeyState(VK_CONTROL) & 0x8000;
            if (wp == VK_ESCAPE) PostMessageW(hwnd, WM_CLOSE, 0, 0);
            else if (wp == VK_RETURN || (ctrl && wp == 'C')) CopyMain();
            else if (ctrl && wp == 'V') PasteColor();
            else if (!ctrl && wp == 'P') StartScreenPick(0);
            else if (wp == VK_UP || wp == VK_DOWN) {
                double unit = p.mode == 0 ? 1 / 360.0 : p.mode <= 2 ? 0.01 : 1 / 255.0;
                int mul = (GetKeyState(VK_SHIFT) & 0x8000) ? 10 : 1;
                SetSliderT(SliderT() + (wp == VK_UP ? 1 : -1) * mul * unit);
                Invalidate();
            }
            return 0;
        }
        case WM_TIMER:
            if (wp == kTimerAnim) Tick();
            return 0;
        case WM_ACTIVATE:
            Invalidate();
            break;
        case WM_CLOSE:
            EndEdit(true);
            SavePickerState();
            DestroyWindow(hwnd);
            return 0;
        case WM_DESTROY:
            KillTimer(hwnd, kTimerAnim);
            p.rt.Reset();
            p.res.Reset();
            if (p.editFont) DeleteObject(p.editFont), p.editFont = nullptr;
            if (p.editBrush) DeleteObject(p.editBrush), p.editBrush = nullptr;
            if (p.iconSmall) DestroyIcon(p.iconSmall), p.iconSmall = nullptr;
            if (p.iconBig) DestroyIcon(p.iconBig), p.iconBig = nullptr;
            p.hwnd = nullptr;
            p.edit = nullptr;
            p.editing = -1;
            p.glow.clear();
            p.hover = p.press = -1;
            p.drag = 0;
            p.tracking = false;
            return 0;
    }
    return DefWindowProcW(hwnd, msg, wp, lp);
}

static Color StartColor() {
    Color c = FromArgb(g_lastColor);
    if (g_set.startColor == 2) {
        c = FromArgb(0xFF000000 | g_set.customStart);
    } else if (g_set.startColor == 1) {
        Color k = c;
        bool hadAlpha;
        if (ParseColorText(GetClipText(g_msg), k, &hadAlpha)) c = k;
    }
    return c;
}

static void OpenPicker(const Color* start, const POINT* pos = nullptr) {
    Picker& p = g_pk;
    if (p.hwnd) {
        if (start) {
            p.cur = *start;
            if (pos) p.pos = *pos, p.hasPos = true;
        }
        ShowWindow(p.hwnd, IsIconic(p.hwnd) ? SW_RESTORE : SW_SHOW);
        SetForegroundWindow(p.hwnd);
        Invalidate();
        return;
    }
    p.cur = start ? *start : StartColor();
    p.old = p.cur;
    p.hasPos = false;
    if (pos) p.pos = *pos, p.hasPos = true;
    p.glassOn = g_set.glass;
    Layout();
    DWORD ex = g_set.onTop ? WS_EX_TOPMOST : 0;
    DWORD style = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_CLIPCHILDREN;
    HWND hwnd = CreateWindowExW(ex, kPickerClass, L"Seamless Color Picker", style, CW_USEDEFAULT, CW_USEDEFAULT, 200, 200,
                                nullptr, nullptr, g_inst, nullptr);
    if (!hwnd) return;
    p.hwnd = hwnd;
    p.dpi = GetDpiForWindow(hwnd);
    ApplyGlass(hwnd, p.glassOn);
    p.editBrush = CreateSolidBrush(scpset::RefFromRgb(m::surface0));
    p.edit = CreateWindowExW(WS_EX_LAYERED, L"EDIT", L"", WS_CHILD | ES_CENTER | ES_AUTOHSCROLL, 0, 0, 10, 10, hwnd, nullptr, g_inst, nullptr);
    if (p.edit) SetLayeredWindowAttributes(p.edit, 0, 255, LWA_ALPHA);
    else p.edit = CreateWindowExW(0, L"EDIT", L"", WS_CHILD | ES_CENTER | ES_AUTOHSCROLL, 0, 0, 10, 10, hwnd, nullptr, g_inst, nullptr);
    if (p.edit) {
        SendMessageW(p.edit, EM_SETLIMITTEXT, 32, 0);
        SetWindowSubclass(p.edit, EditProc, 1, 0);
        SetWindowTheme(p.edit, L"DarkMode_Explorer", nullptr);
    }
    MakeEditFont();
    p.iconSmall = MakeIcon(GetSystemMetricsForDpi(SM_CXSMICON, p.dpi));
    p.iconBig = MakeIcon(GetSystemMetricsForDpi(SM_CXICON, p.dpi));
    if (p.iconSmall) SendMessageW(hwnd, WM_SETICON, ICON_SMALL, (LPARAM)p.iconSmall);
    if (p.iconBig) SendMessageW(hwnd, WM_SETICON, ICON_BIG, (LPARAM)p.iconBig);

    // Where it opens: where it was left, else beside the mouse.
    POINT cursor;
    GetCursorPos(&cursor);
    POINT at{cursor.x + 24, cursor.y + 24};
    bool saved = false;
    if (g_set.rememberPos && Wh_GetIntValue(L"WinSaved", 0)) {
        POINT s{Wh_GetIntValue(L"WinX", 0), Wh_GetIntValue(L"WinY", 0)};
        POINT probe{s.x + 60, s.y + 16};
        if (MonitorFromPoint(probe, MONITOR_DEFAULTTONULL)) at = s, saved = true;
    }
    SetWindowPos(hwnd, nullptr, at.x, at.y, 0, 0, SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE);
    p.dpi = GetDpiForWindow(hwnd);
    MakeEditFont();
    ResizeToLayout();
    if (!saved) {
        RECT wr;
        GetWindowRect(hwnd, &wr);
        MONITORINFO mi{sizeof(mi)};
        GetMonitorInfoW(MonitorFromPoint(cursor, MONITOR_DEFAULTTONEAREST), &mi);
        int wdt = wr.right - wr.left, hgt = wr.bottom - wr.top;
        int x = std::clamp((int)at.x, (int)mi.rcWork.left, std::max((int)mi.rcWork.left, (int)mi.rcWork.right - wdt));
        int y = std::clamp((int)at.y, (int)mi.rcWork.top, std::max((int)mi.rcWork.top, (int)mi.rcWork.bottom - hgt));
        if (cursor.x + 24 + wdt > mi.rcWork.right) x = std::max((int)mi.rcWork.left, (int)cursor.x - 24 - wdt);
        SetWindowPos(hwnd, nullptr, x, y, 0, 0, SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE);
    }
    ShowWindow(hwnd, SW_SHOW);
    SetForegroundWindow(hwnd);
    SetFocus(hwnd);
    SetTimer(hwnd, kTimerAnim, 16, nullptr);
}

static void TogglePicker() {
    Picker& p = g_pk;
    if (p.hwnd && IsWindowVisible(p.hwnd) && !IsIconic(p.hwnd) && GetForegroundWindow() == p.hwnd) {
        PostMessageW(p.hwnd, WM_CLOSE, 0, 0);
        return;
    }
    OpenPicker(nullptr);
}

// ---- Screen magnifier ------------------------------------------------------

struct Overlay {
    HWND hwnd = nullptr;
    ComPtr<ID2D1HwndRenderTarget> rt;
    ComPtr<ID2D1Bitmap> shot;
    Res res;
    std::vector<UINT32> px;
    int vx = 0, vy = 0, vw = 0, vh = 0;
    POINT cur{0, 0};
    int zoom = 10, origin = 0;
    float scale = 1;
    bool finishing = false;
};
Overlay g_ov;

static UINT32 ShotPixel(int x, int y) {
    x = std::clamp(x, 0, g_ov.vw - 1), y = std::clamp(y, 0, g_ov.vh - 1);
    return g_ov.px.empty() ? 0 : g_ov.px[(size_t)y * g_ov.vw + x] & 0xFFFFFF;
}

static void DrawOverlay(ID2D1RenderTarget* rt, Res& res, ID2D1Bitmap* shot, RECT mon) {
    Overlay& o = g_ov;
    if (!res.Ensure(rt)) return;
    Painter P{rt, res};
    rt->Clear(D2D1::ColorF(0, 0, 0, 1));
    if (shot) rt->DrawBitmap(shot, D2D1::RectF(0, 0, (float)o.vw, (float)o.vh), 1, D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR);
    float cx = o.cur.x + 0.5f, cy = o.cur.y + 0.5f, sc = o.scale;
    if (g_set.crosshair) {
        res.brush->SetColor(D2DColor(m::crust, 0.45f));
        rt->DrawLine({0, cy}, {(float)o.vw, cy}, res.brush.Get(), 3);
        rt->DrawLine({cx, 0}, {cx, (float)o.vh}, res.brush.Get(), 3);
        res.brush->SetColor(D2DColor(g_set.accent, 0.8f));
        rt->DrawLine({0, cy}, {(float)o.vw, cy}, res.brush.Get(), 1);
        rt->DrawLine({cx, 0}, {cx, (float)o.vh}, res.brush.Get(), 1);
    }
    int n = g_set.magPixels;
    float z = std::round(o.zoom * sc), M = n * z, gap = 24 * sc, infoH = g_set.info ? 34 * sc : 0, infoGap = g_set.info ? 8 * sc : 0;
    float infoW = std::max(M, 176 * sc), blockH = M + infoGap + infoH;
    float left = cx + gap, top = cy + gap;
    if (left + std::max(M, infoW) > mon.right) left = cx - gap - M;
    if (top + blockH > mon.bottom) top = cy - gap - blockH;
    left = std::clamp(left, (float)mon.left + (infoW - M) / 2, std::max((float)mon.left, mon.right - M - (infoW - M) / 2));
    top = std::clamp(top, (float)mon.top, std::max((float)mon.top, mon.bottom - blockH));
    D2D1_RECT_F mr{left, top, left + M, top + M};
    float mrad = g_set.magCircle ? M / 2 : 18 * sc;

    ComPtr<ID2D1RoundedRectangleGeometry> geo;
    g_d2d->CreateRoundedRectangleGeometry(D2D1::RoundedRect(mr, mrad, mrad), geo.GetAddressOf());
    P.Fill(Inflate(mr, 7 * sc), m::crust, 0.18f, mrad + 7 * sc);
    P.Fill(Inflate(mr, 3.5f * sc), m::crust, 0.35f, mrad + 3.5f * sc);
    if (geo) rt->PushLayer(D2D1::LayerParameters(D2D1::InfiniteRect(), geo.Get()), nullptr);
    P.Fill(mr, m::crust, 1, 0);
    int sx = o.cur.x - n / 2, sy = o.cur.y - n / 2;
    int x0 = std::max(0, sx), y0 = std::max(0, sy), x1 = std::min(o.vw, sx + n), y1 = std::min(o.vh, sy + n);
    if (shot && x1 > x0 && y1 > y0) {
        D2D1_RECT_F dst{left + (x0 - sx) * z, top + (y0 - sy) * z, left + (x1 - sx) * z, top + (y1 - sy) * z};
        rt->DrawBitmap(shot, dst, 1, D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR,
                       D2D1::RectF((float)x0, (float)y0, (float)x1, (float)y1));
    }
    if (g_set.grid && z >= 5) {
        res.brush->SetColor(D2DColor(m::crust, 0.28f));
        for (int i = 1; i < n; i++) {
            rt->DrawLine({left + i * z, top}, {left + i * z, top + M}, res.brush.Get(), 1);
            rt->DrawLine({left, top + i * z}, {left + M, top + i * z}, res.brush.Get(), 1);
        }
    }
    D2D1_RECT_F px{left + (n / 2) * z, top + (n / 2) * z, left + (n / 2 + 1) * z, top + (n / 2 + 1) * z};
    res.brush->SetColor(D2DColor(m::crust, 0.9f));
    rt->DrawRectangle(Inflate(px, 1), res.brush.Get(), 1.5f);
    res.brush->SetColor(D2DColor(0xFFFFFF));
    rt->DrawRectangle(px, res.brush.Get(), 1.5f);
    if (geo) rt->PopLayer();
    P.Stroke(Inflate(mr, 1), m::crust, 0.9f, mrad + 1, 1);
    P.GradStroke(Inflate(mr, 0.5f), mrad + 0.5f, 2.5f * sc, 1);

    if (g_set.info) {
        UINT32 c = ShotPixel(o.cur.x, o.cur.y);
        float il = left + M / 2 - infoW / 2;
        D2D1_RECT_F ir{il, top + M + infoGap, il + infoW, top + M + infoGap + infoH};
        P.Fill(ir, m::crust, 0.94f, infoH / 2);
        P.GradStroke(ir, infoH / 2, 1.2f * sc, 0.9f);
        D2D1_RECT_F sw{ir.left + 8 * sc, ir.top + 8 * sc, ir.left + 26 * sc, ir.bottom - 8 * sc};
        P.Fill(sw, c, 1, 5 * sc);
        P.Stroke(sw, m::surface2, 0.8f, 5 * sc, 1);
        auto fb = MakeFormat(g_family, 13 * sc, DWRITE_FONT_WEIGHT_SEMI_BOLD);
        auto fs = MakeFormat(g_family, 11 * sc, DWRITE_FONT_WEIGHT_NORMAL);
        P.Text(fb.Get(), L"#" + Hex6(c), {sw.right + 8 * sc, ir.top, ir.right - 8 * sc, ir.bottom}, m::text);
        P.Text(fs.Get(), Fmt(L"%d, %d", o.cur.x + o.vx, o.cur.y + o.vy), {sw.right, ir.top, ir.right - 14 * sc, ir.bottom},
               m::subtext0, 1, DWRITE_TEXT_ALIGNMENT_TRAILING);
    }
}

static RECT MonitorClientRect() {
    POINT pt{g_ov.cur.x + g_ov.vx, g_ov.cur.y + g_ov.vy};
    MONITORINFO mi{sizeof(mi)};
    GetMonitorInfoW(MonitorFromPoint(pt, MONITOR_DEFAULTTONEAREST), &mi);
    RECT r = mi.rcMonitor;
    OffsetRect(&r, -g_ov.vx, -g_ov.vy);
    return r;
}

static void PaintOverlay() {
    Overlay& o = g_ov;
    if (!o.rt) {
        auto props = D2D1::RenderTargetProperties(D2D1_RENDER_TARGET_TYPE_DEFAULT,
                                                  D2D1::PixelFormat(DXGI_FORMAT_B8G8R8A8_UNORM, D2D1_ALPHA_MODE_IGNORE), 96, 96);
        if (FAILED(g_d2d->CreateHwndRenderTarget(props, D2D1::HwndRenderTargetProperties(o.hwnd, D2D1::SizeU(o.vw, o.vh)),
                                                 o.rt.GetAddressOf())))
            return;
        o.res.Reset();
        o.shot.Reset();
    }
    if (!o.shot && !o.px.empty()) {
        auto bp = D2D1::BitmapProperties(D2D1::PixelFormat(DXGI_FORMAT_B8G8R8A8_UNORM, D2D1_ALPHA_MODE_IGNORE));
        o.rt->CreateBitmap(D2D1::SizeU(o.vw, o.vh), o.px.data(), o.vw * 4, bp, o.shot.GetAddressOf());
    }
    o.rt->BeginDraw();
    DrawOverlay(o.rt.Get(), o.res, o.shot.Get(), MonitorClientRect());
    if (o.rt->EndDraw() == D2DERR_RECREATE_TARGET) {
        o.rt.Reset();
        o.res.Reset();
        o.shot.Reset();
    }
}

static void FinishPick(bool picked) {
    Overlay& o = g_ov;
    if (o.finishing || !o.hwnd) return;
    o.finishing = true;
    PostMessageW(g_msg, WM_APP_PICKED, picked, 0);
}

static LRESULT CALLBACK OverlayProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) {
    Overlay& o = g_ov;
    switch (msg) {
        case WM_PAINT: {
            PAINTSTRUCT ps;
            BeginPaint(hwnd, &ps);
            PaintOverlay();
            EndPaint(hwnd, &ps);
            return 0;
        }
        case WM_ERASEBKGND: return 1;
        case WM_SETCURSOR:
            SetCursor(LoadCursorW(nullptr, IDC_CROSS));
            return TRUE;
        case WM_MOUSEMOVE: {
            POINT c{GET_X_LPARAM(lp), GET_Y_LPARAM(lp)};
            if (c.x != o.cur.x || c.y != o.cur.y) {
                o.cur = c;
                InvalidateRect(hwnd, nullptr, FALSE);
            }
            return 0;
        }
        case WM_LBUTTONUP: FinishPick(true); return 0;
        case WM_RBUTTONUP: FinishPick(false); return 0;
        case WM_MOUSEWHEEL:
            o.zoom = std::clamp(o.zoom + (GET_WHEEL_DELTA_WPARAM(wp) > 0 ? 1 : -1), 4, 24);
            InvalidateRect(hwnd, nullptr, FALSE);
            return 0;
        case WM_KEYDOWN: {
            int step = (GetKeyState(VK_SHIFT) & 0x8000) ? 10 : 1, dx = 0, dy = 0;
            if (wp == VK_ESCAPE) FinishPick(false);
            else if (wp == VK_RETURN || wp == VK_SPACE) FinishPick(true);
            else if (wp == VK_LEFT) dx = -step;
            else if (wp == VK_RIGHT) dx = step;
            else if (wp == VK_UP) dy = -step;
            else if (wp == VK_DOWN) dy = step;
            if (dx || dy) {
                o.cur.x = std::clamp((int)o.cur.x + dx, 0, o.vw - 1);
                o.cur.y = std::clamp((int)o.cur.y + dy, 0, o.vh - 1);
                SetCursorPos(o.cur.x + o.vx, o.cur.y + o.vy);
                InvalidateRect(hwnd, nullptr, FALSE);
            }
            return 0;
        }
        case WM_ACTIVATE:
            if (LOWORD(wp) == WA_INACTIVE) FinishPick(false);
            return 0;
        case WM_DESTROY:
            o.rt.Reset();
            o.res.Reset();
            o.shot.Reset();
            return 0;
    }
    return DefWindowProcW(hwnd, msg, wp, lp);
}

static bool CaptureScreen() {
    Overlay& o = g_ov;
    o.vx = GetSystemMetrics(SM_XVIRTUALSCREEN), o.vy = GetSystemMetrics(SM_YVIRTUALSCREEN);
    o.vw = GetSystemMetrics(SM_CXVIRTUALSCREEN), o.vh = GetSystemMetrics(SM_CYVIRTUALSCREEN);
    if (o.vw <= 0 || o.vh <= 0) return false;
    HDC sdc = GetDC(nullptr);
    HDC mdc = CreateCompatibleDC(sdc);
    BITMAPINFO bi{};
    bi.bmiHeader.biSize = sizeof(bi.bmiHeader);
    bi.bmiHeader.biWidth = o.vw;
    bi.bmiHeader.biHeight = -o.vh;
    bi.bmiHeader.biPlanes = 1;
    bi.bmiHeader.biBitCount = 32;
    bi.bmiHeader.biCompression = BI_RGB;
    void* bits = nullptr;
    HBITMAP hb = CreateDIBSection(mdc, &bi, DIB_RGB_COLORS, &bits, nullptr, 0);
    bool ok = false;
    if (hb) {
        HGDIOBJ old = SelectObject(mdc, hb);
        ok = BitBlt(mdc, 0, 0, o.vw, o.vh, sdc, o.vx, o.vy, SRCCOPY | CAPTUREBLT) != 0;
        GdiFlush();
        if (ok) {
            o.px.assign((UINT32*)bits, (UINT32*)bits + (size_t)o.vw * o.vh);
            for (auto& v : o.px) v |= 0xFF000000;
        }
        SelectObject(mdc, old);
        DeleteObject(hb);
    }
    DeleteDC(mdc);
    ReleaseDC(nullptr, sdc);
    return ok;
}

static void StartScreenPick(int origin) {
    Overlay& o = g_ov;
    if (o.hwnd) return;
    Picker& p = g_pk;
    if (p.editing >= 0) EndEdit(true);
    p.hiddenForPick = false;
    if (p.hwnd && IsWindowVisible(p.hwnd)) {
        ShowWindow(p.hwnd, SW_HIDE);
        p.hiddenForPick = true;
        DwmFlush();
        DwmFlush();
    }
    if (g_pk.hwnd == nullptr) p.hiddenForPick = false;
    if (!CaptureScreen()) {
        if (p.hiddenForPick) ShowWindow(p.hwnd, SW_SHOW);
        return;
    }
    o.origin = origin;
    o.zoom = g_set.magZoom;
    o.scale = GetDpiForSystem() / 96.0f;
    o.finishing = false;
    POINT c;
    GetCursorPos(&c);
    o.cur = {c.x - o.vx, c.y - o.vy};
    o.hwnd = CreateWindowExW(WS_EX_TOPMOST | WS_EX_TOOLWINDOW, kOverlayClass, L"Seamless Color Picker screen", WS_POPUP,
                             o.vx, o.vy, o.vw, o.vh, nullptr, nullptr, g_inst, nullptr);
    if (!o.hwnd) {
        o.px.clear();
        if (p.hiddenForPick) ShowWindow(p.hwnd, SW_SHOW);
        return;
    }
    ShowWindow(o.hwnd, SW_SHOW);
    SetForegroundWindow(o.hwnd);
    SetFocus(o.hwnd);
    UpdateWindow(o.hwnd);
}

static void OnPicked(bool picked) {
    Overlay& o = g_ov;
    if (!o.hwnd) return;
    UINT32 rgb = ShotPixel(o.cur.x, o.cur.y);
    POINT pos{o.cur.x + o.vx, o.cur.y + o.vy};
    HWND h = o.hwnd;
    o.hwnd = nullptr;
    DestroyWindow(h);
    o.px.clear();
    o.px.shrink_to_fit();
    Picker& p = g_pk;
    if (o.origin == 0) {
        if (picked && p.hwnd) {
            p.cur.SetRgb((rgb >> 16) & 0xFF, (rgb >> 8) & 0xFF, rgb & 0xFF);
            p.pos = pos;
            p.hasPos = true;
        }
        if (p.hwnd) {
            ShowWindow(p.hwnd, SW_SHOW);
            SetForegroundWindow(p.hwnd);
            Invalidate();
        }
        return;
    }
    if (p.hiddenForPick && p.hwnd) ShowWindow(p.hwnd, SW_SHOWNA);
    if (!picked) return;
    Color c = FromArgb(0xFF000000 | rgb);
    if (g_set.screenAction != 2) DoCopyText(FormatColor(c, g_set.copyFormat, pos, true), c.Argb());
    if (g_set.screenAction != 0) OpenPicker(&c, &pos);
}

// ---- "Copied" card --------------------------------------------------------

struct Toast {
    HWND hwnd = nullptr;
    ComPtr<ID2D1HwndRenderTarget> rt;
    Res res;
    std::wstring text;
    UINT32 argb = 0;
    UINT dpi = 96;
    float w = 240, h = 52;
    bool acrylic = false;
};
Toast g_toast;

static bool TransparencyOn() {
    DWORD v = 1, cb = sizeof(v);
    RegGetValueW(HKEY_CURRENT_USER, L"Software\\Microsoft\\Windows\\CurrentVersion\\Themes\\Personalize", L"EnableTransparency",
                 RRF_RT_REG_DWORD, nullptr, &v, &cb);
    return v != 0;
}

static bool SetAcrylic(HWND hwnd, bool on) {
    struct ACCENT_POLICY {
        int AccentState, AccentFlags;
        DWORD GradientColor;
        int AnimationId;
    };
    struct WINCOMPATTRDATA {
        int Attrib;
        PVOID pvData;
        SIZE_T cbData;
    };
    using Fn = BOOL(WINAPI*)(HWND, WINCOMPATTRDATA*);
    static Fn fn = (Fn)GetProcAddress(GetModuleHandleW(L"user32.dll"), "SetWindowCompositionAttribute");
    if (!fn) return false;
    // Tint as AABBGGRR: Mocha crust at about 88%.
    ACCENT_POLICY ap{on ? 4 : 0, 2, 0xE01B1111u, 0};
    WINCOMPATTRDATA d{19, &ap, sizeof(ap)};
    return fn(hwnd, &d) != FALSE;
}

static void DrawToast(ID2D1RenderTarget* rt, Res& res, float w, float h, bool acrylic) {
    if (!res.Ensure(rt)) return;
    Painter P{rt, res};
    rt->Clear(D2D1::ColorF(0, 0, 0, 0));
    D2D1_RECT_F r{0, 0, w, h};
    P.Fill(r, m::crust, acrylic ? 0.45f : 0.97f, 8);
    P.GradStroke(r, 8, 1.5f, 0.95f);
    D2D1_RECT_F sw{12, 12, 40, h - 12};
    if ((g_toast.argb >> 24) < 255) P.Checker(sw, 6);
    P.Fill(sw, g_toast.argb & 0xFFFFFF, (g_toast.argb >> 24) / 255.0f, 6);
    P.Stroke(sw, m::surface2, 0.8f, 6, 1);
    bool error = g_toast.text.rfind(L"No color", 0) == 0;
    P.Text(g_fSmall.Get(), error ? L"Clipboard" : L"Copied", {52, 7, w - 12, 24}, error ? m::peach : m::subtext0);
    P.Text(g_fTitle.Get(), g_toast.text, {52, 23, w - 12, h - 7}, m::text);
}

static LRESULT CALLBACK ToastProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) {
    Toast& t = g_toast;
    switch (msg) {
        case WM_PAINT: {
            PAINTSTRUCT ps;
            BeginPaint(hwnd, &ps);
            if (!t.rt) {
                RECT rc;
                GetClientRect(hwnd, &rc);
                auto props = D2D1::RenderTargetProperties(D2D1_RENDER_TARGET_TYPE_DEFAULT,
                                                          D2D1::PixelFormat(DXGI_FORMAT_B8G8R8A8_UNORM, D2D1_ALPHA_MODE_PREMULTIPLIED));
                g_d2d->CreateHwndRenderTarget(props, D2D1::HwndRenderTargetProperties(hwnd, D2D1::SizeU(rc.right, rc.bottom)),
                                              t.rt.GetAddressOf());
                t.res.Reset();
            }
            if (t.rt) {
                t.rt->SetDpi((float)t.dpi, (float)t.dpi);
                t.rt->BeginDraw();
                DrawToast(t.rt.Get(), t.res, t.w, t.h, t.acrylic);
                if (t.rt->EndDraw() == D2DERR_RECREATE_TARGET) t.rt.Reset(), t.res.Reset();
            }
            EndPaint(hwnd, &ps);
            return 0;
        }
        case WM_ERASEBKGND: return 1;
        case WM_SIZE:
            if (t.rt) t.rt->Resize(D2D1::SizeU(LOWORD(lp), HIWORD(lp)));
            return 0;
        case WM_MOUSEACTIVATE: return MA_NOACTIVATE;
        case WM_NCHITTEST: return HTTRANSPARENT;
        case WM_TIMER:
            if (wp == kTimerToast) {
                KillTimer(hwnd, kTimerToast);
                ShowWindow(hwnd, SW_HIDE);
            }
            return 0;
        case WM_DESTROY:
            t.rt.Reset();
            t.res.Reset();
            t.hwnd = nullptr;
            return 0;
    }
    return DefWindowProcW(hwnd, msg, wp, lp);
}

static void ShowToast(UINT32 argb, const std::wstring& text) {
    Toast& t = g_toast;
    if (!t.hwnd) {
        t.hwnd = CreateWindowExW(WS_EX_TOPMOST | WS_EX_TOOLWINDOW | WS_EX_NOACTIVATE, kToastClass, L"", WS_POPUP, 0, 0, 10, 10,
                                 nullptr, nullptr, g_inst, nullptr);
        if (!t.hwnd) return;
        int corner = 2;  // DWMWCP_ROUND
        DwmSetWindowAttribute(t.hwnd, 33, &corner, sizeof(corner));
    }
    t.acrylic = g_set.glass && TransparencyOn() && SetAcrylic(t.hwnd, true);
    if (!t.acrylic) SetAcrylic(t.hwnd, false);
    t.argb = argb;
    t.text = text.size() > 60 ? text.substr(0, 57) + L"..." : text;
    POINT pt;
    GetCursorPos(&pt);
    SetWindowPos(t.hwnd, HWND_TOPMOST, pt.x + 18, pt.y + 22, 10, 10, SWP_NOACTIVATE);
    t.dpi = GetDpiForWindow(t.hwnd);
    float tw = 0;
    ComPtr<IDWriteTextLayout> lay;
    if (g_fTitle && SUCCEEDED(g_dw->CreateTextLayout(t.text.c_str(), (UINT32)t.text.size(), g_fTitle.Get(), 2000, 40, lay.GetAddressOf()))) {
        DWRITE_TEXT_METRICS mt;
        lay->GetMetrics(&mt);
        tw = mt.widthIncludingTrailingWhitespace;
    }
    t.w = std::clamp(tw + 70, 170.0f, 560.0f);
    t.h = 52;
    int pw = MulDiv((int)t.w, t.dpi, 96), ph = MulDiv((int)t.h, t.dpi, 96);
    MONITORINFO mi{sizeof(mi)};
    GetMonitorInfoW(MonitorFromPoint(pt, MONITOR_DEFAULTTONEAREST), &mi);
    int x = std::min((int)pt.x + 18, (int)mi.rcWork.right - pw - 8), y = std::min((int)pt.y + 22, (int)mi.rcWork.bottom - ph - 8);
    SetWindowPos(t.hwnd, HWND_TOPMOST, x, y, pw, ph, SWP_NOACTIVATE | SWP_SHOWWINDOW);
    InvalidateRect(t.hwnd, nullptr, FALSE);
    SetTimer(t.hwnd, kTimerToast, 1500, nullptr);
}

// ---- Hotkeys and the message window --------------------------------------

static void RegisterHotkeys() {
    UnregisterHotKey(g_msg, kHotkeyOpen);
    UnregisterHotKey(g_msg, kHotkeyScreen);
    KillTimer(g_msg, kTimerRetry);
    bool retry = false;
    UINT mods, vk;
    if (ParseHotkey(g_set.hotkey, &mods, &vk)) {
        if (!RegisterHotKey(g_msg, kHotkeyOpen, mods | MOD_NOREPEAT, vk)) {
            Wh_Log(L"hotkey %s is taken, retrying", g_set.hotkey.c_str());
            retry = true;
        }
    } else if (!g_set.hotkey.empty()) {
        Wh_Log(L"hotkey %s not understood", g_set.hotkey.c_str());
    }
    if (ParseHotkey(g_set.screenHotkey, &mods, &vk)) {
        if (!RegisterHotKey(g_msg, kHotkeyScreen, mods | MOD_NOREPEAT, vk)) {
            Wh_Log(L"screen hotkey %s is taken, retrying", g_set.screenHotkey.c_str());
            retry = true;
        }
    }
    if (retry) SetTimer(g_msg, kTimerRetry, 3000, nullptr);
}

static void ApplySettingsLive() {
    LoadSettings();
    MakeFormats();
    g_modeOverride = -1;
    RegisterHotkeys();
    Picker& p = g_pk;
    if (p.hwnd) {
        SetWindowPos(p.hwnd, g_set.onTop ? HWND_TOPMOST : HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
        p.glassOn = g_set.glass;
        ApplyGlass(p.hwnd, p.glassOn);
        MakeEditFont();
        Layout();
        ResizeToLayout();
        p.res.Reset();
        p.rt.Reset();
        Invalidate();
    }
}

static LRESULT CALLBACK MsgProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) {
    switch (msg) {
        case WM_HOTKEY:
            if (wp == kHotkeyOpen) {
                if (!g_ov.hwnd) TogglePicker();
            } else if (wp == kHotkeyScreen) {
                StartScreenPick(1);
            }
            return 0;
        case WM_TIMER:
            if (wp == kTimerRetry) RegisterHotkeys();
            return 0;
        case WM_APP_SETTINGS:
            ApplySettingsLive();
            return 0;
        case WM_APP_PICKED:
            OnPicked(wp != 0);
            return 0;
        case WM_CLOSE:
            if (g_ov.hwnd) {
                HWND h = g_ov.hwnd;
                g_ov.hwnd = nullptr;
                DestroyWindow(h);
            }
            if (g_pk.hwnd) SendMessageW(g_pk.hwnd, WM_CLOSE, 0, 0);
            if (g_toast.hwnd) DestroyWindow(g_toast.hwnd);
            UnregisterHotKey(hwnd, kHotkeyOpen);
            UnregisterHotKey(hwnd, kHotkeyScreen);
            DestroyWindow(hwnd);
            return 0;
        case WM_DESTROY:
            g_msg = nullptr;
            PostQuitMessage(0);
            return 0;
    }
    return DefWindowProcW(hwnd, msg, wp, lp);
}

HANDLE g_thread = nullptr, g_ready = nullptr;

static void RegisterClasses() {
    WNDCLASSEXW wc{sizeof(wc)};
    wc.hInstance = g_inst;
    wc.hCursor = LoadCursorW(nullptr, IDC_ARROW);
    wc.lpfnWndProc = MsgProc;
    wc.lpszClassName = kMsgClass;
    RegisterClassExW(&wc);
    wc.lpfnWndProc = PickerProc;
    wc.lpszClassName = kPickerClass;
    wc.hbrBackground = nullptr;
    RegisterClassExW(&wc);
    wc.lpfnWndProc = OverlayProc;
    wc.lpszClassName = kOverlayClass;
    wc.hCursor = LoadCursorW(nullptr, IDC_CROSS);
    RegisterClassExW(&wc);
    wc.lpfnWndProc = ToastProc;
    wc.lpszClassName = kToastClass;
    wc.hCursor = LoadCursorW(nullptr, IDC_ARROW);
    RegisterClassExW(&wc);
}

static void UnregisterClasses() {
    for (PCWSTR c : {kMsgClass, kPickerClass, kOverlayClass, kToastClass}) UnregisterClassW(c, g_inst);
}

static DWORD WINAPI ThreadProc(void*) {
    SetThreadDpiAwarenessContext(DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2);
    CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED);
    g_inst = (HINSTANCE)&__ImageBase;
    if (!EnsureFactories()) {
        SetEvent(g_ready);
        CoUninitialize();
        return 1;
    }
    LoadSettings();
    LoadState();
    MakeFormats();
    RegisterClasses();
    g_msg = CreateWindowExW(0, kMsgClass, L"", 0, 0, 0, 0, 0, HWND_MESSAGE, nullptr, g_inst, nullptr);
    if (g_msg) RegisterHotkeys();
    SetEvent(g_ready);
    MSG msg;
    while (g_msg && GetMessageW(&msg, nullptr, 0, 0) > 0) {
        TranslateMessage(&msg);
        DispatchMessageW(&msg);
    }
    UnregisterClasses();
    g_fLabel.Reset(), g_fValue.Reset(), g_fBig.Reset(), g_fSmall.Reset(), g_fBtn.Reset(), g_fIcon.Reset(), g_fIconS.Reset(),
        g_fIconXS.Reset(), g_fTitle.Reset();
    g_wic.Reset(), g_dw.Reset(), g_d2d.Reset();
    CoUninitialize();
    return 0;
}

}  // namespace scp

BOOL WhTool_ModInit() {
    Wh_Log(L">");
    scp::g_ready = CreateEventW(nullptr, TRUE, FALSE, nullptr);
    scp::g_thread = CreateThread(nullptr, 0, scp::ThreadProc, nullptr, 0, nullptr);
    if (!scp::g_thread) return FALSE;
    WaitForSingleObject(scp::g_ready, 10000);
    return TRUE;
}

void WhTool_ModSettingsChanged() {
    Wh_Log(L">");
    if (scp::g_msg) PostMessageW(scp::g_msg, scp::WM_APP_SETTINGS, 0, 0);
}

void WhTool_ModUninit() {
    Wh_Log(L">");
    scpset::CloseSettingsWindow();
    if (scp::g_msg) PostMessageW(scp::g_msg, WM_CLOSE, 0, 0);
    if (scp::g_thread) {
        WaitForSingleObject(scp::g_thread, 5000);
        CloseHandle(scp::g_thread);
        scp::g_thread = nullptr;
    }
    if (scp::g_ready) CloseHandle(scp::g_ready), scp::g_ready = nullptr;
}
