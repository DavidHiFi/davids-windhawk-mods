// ==WindhawkMod==
// @id              seamless-crosshair
// @name            Seamless Crosshair
// @description     A crosshair over any game: presets or your own design, any color and size, shortcuts and a tray icon
// @version         1.2.6
// @author          DavidHiFi
// @github          https://github.com/DavidHiFi
// @homepage        https://github.com/DavidHiFi/davids-windhawk-mods
// @include         windhawk.exe
// @architecture    x86-64
// @compilerOptions -lgdi32 -luser32 -lshell32 -lshlwapi -lole32 -loleaut32 -luuid -ld2d1 -ldwrite -lwindowscodecs -ldwmapi -lcomctl32 -luxtheme -lcomdlg32 -limm32 -ladvapi32 -lruntimeobject
// @license         MIT
// @donateUrl       https://ko-fi.com/DavidHiFi
// ==/WindhawkMod==

// ==WindhawkModReadme==
/*
# Seamless Crosshair

Puts a crosshair in the middle of your screen, over any game. Pick a ready-made
one or build your own, in any color and size. No separate app, no installer and
nothing injected into the game: the crosshair is a see-through window that
clicks pass straight through.

![Seamless Crosshair settings](https://raw.githubusercontent.com/DavidHiFi/davids-windhawk-mods/main/media/previews/seamless-crosshair.png)

## What it does

- Ready-made crosshairs, your own design, or any PNG as the crosshair.
- Your own design: center dot, inner and outer lines, a ring, a T shape and any
  rotation, each with its own size, gap and opacity.
- Any color, opacity and size, with an outline so it stays visible on bright and
  dark scenes.
- Pixel sharp: lines land on whole screen pixels, and the crosshair sits on the
  exact middle of the screen at any display scaling.
- Centers on your main screen, a screen you pick, or the game window, and moves
  by the pixel if your game's aim point is off center.
- Shows always, only in the games you list, or only in fullscreen apps. Hides
  while you aim down sights if you like, or shows only then.
- Shortcuts: show or hide (Ctrl+Alt+X), next style (Ctrl+Alt+Z), and optional
  keys for the previous style, next color, size and moving it.
- A look per game: keep the crosshair as it is for the game in front, and that
  game gets it back every time. Other games keep the normal one.
- A tray icon: click it for settings, right-click it to pick a style, color or
  size.
- A small pop-up says "Crosshair enabled" or "Crosshair disabled" when you switch it,
  with blurred glass. Pick where it shows, how long, how big, or turn it off.
- The crosshair fades in and out instead of popping, at the speed you pick.
- Can stay out of screenshots, recordings and streams.

## Ready-made crosshairs

- Cross with a dot
- Cross
- Small cross
- Dot
- T shape
- X
- Circle with a dot
- Circle
- Cross in a ring
- Chevron
- Your own design
- An image file

## Good to know

It works in windowed and borderless fullscreen games. Games in exclusive
fullscreen draw over every other window, so switch those to borderless (the tray
icon tells you once when a game looks like it's in that mode). Some
competitive games don't allow crosshair overlays: check your game's rules first.

## Credits

Inspired by OpenCrosshair by Tu2525 (https://github.com/Tu2525/OpenCrosshair)
and CrossOver by Lacy Morrow (https://github.com/lacymorrow/crossover). This mod
is its own code.
*/
// ==/WindhawkModReadme==

// ==WindhawkModSettings==
/*
- style: "crossDot"
  $name: "Style"
  $description: "The crosshair to draw. Pick \"Your own design\" to build one on the Shape page."
  $options:
  - crossDot: "Cross with a dot"
  - cross: "Cross"
  - smallCross: "Small cross"
  - dot: "Dot"
  - tShape: "T shape"
  - xShape: "X"
  - circleDot: "Circle with a dot"
  - circle: "Circle"
  - tactical: "Cross in a ring"
  - chevron: "Chevron"
  - custom: "Your own design (Shape page)"
  - image: "An image file (below)"
- color: "#00FF00"
  $name: "Color"
  $description: "In hexadecimal, like #00FF00. Bright green, cyan, yellow and magenta stand out in most games."
- opacity: 100
  $name: "Opacity (%)"
  $description: "10 to 100 (Suggested: 100). Lower lets the game show through."
- scale: 100
  $name: "Size (%)"
  $description: "50 to 400 (Suggested: 100). Makes the whole crosshair bigger or smaller."
- followScaling: false
  $name: "Follow display scaling"
  $description: "On, the crosshair grows with your Windows display scaling. Off, sizes are real screen pixels, the way games draw their own."
- outline: true
  $name: "Outline"
  $description: "A dark edge around every line, so the crosshair stays visible on bright and dark scenes alike."
- outlineThickness: 1
  $name: "Outline thickness"
  $description: "1 to 4 (Suggested: 1). Pixels."
- outlineColor: "#000000"
  $name: "Outline color"
  $description: "In hexadecimal, like #000000."
- outlineOpacity: 80
  $name: "Outline opacity (%)"
  $description: "0 to 100 (Suggested: 80)."
- imagePath: ""
  $name: "Image file"
  $description: "Used when the style is \"An image file\". The full path of a PNG (transparency works), BMP, JPG or GIF."
- imageSize: 32
  $name: "Image size"
  $description: "8 to 512 (Suggested: 32). Pixels across. The image keeps its shape."
- imageRecolor: false
  $name: "Paint the image in the color above"
  $description: "Keeps the image's shape and transparency, but fills it with the crosshair color."
- dotOn: true
  $name: "Center dot"
- dotSize: 2
  $name: "Dot size"
  $description: "1 to 20 (Suggested: 2). Pixels."
- dotRound: false
  $name: "Round dot"
  $description: "Off, the dot is a sharp square."
- dotOpacity: 100
  $name: "Dot opacity (%)"
  $description: "10 to 100 (Suggested: 100)."
- innerOn: true
  $name: "Inner lines"
  $description: "The four lines around the center."
- innerLength: 6
  $name: "Length"
  $description: "0 to 60 (Suggested: 6). Pixels."
- innerThickness: 2
  $name: "Thickness"
  $description: "1 to 20 (Suggested: 2). Pixels."
- innerGap: 3
  $name: "Gap"
  $description: "0 to 60 (Suggested: 3). Space between the center and each line."
- innerOpacity: 100
  $name: "Opacity (%)"
  $description: "10 to 100 (Suggested: 100)."
- outerOn: false
  $name: "Outer lines"
  $description: "A second set of lines further out."
- outerLength: 2
  $name: "Length"
  $description: "0 to 60 (Suggested: 2). Pixels."
- outerThickness: 2
  $name: "Thickness"
  $description: "1 to 20 (Suggested: 2). Pixels."
- outerGap: 10
  $name: "Gap"
  $description: "0 to 100 (Suggested: 10). Space between the center and each line."
- outerOpacity: 50
  $name: "Opacity (%)"
  $description: "10 to 100 (Suggested: 50)."
- circleOn: false
  $name: "Ring"
  $description: "A circle around the center."
- circleRadius: 10
  $name: "Radius"
  $description: "2 to 100 (Suggested: 10). Pixels."
- circleThickness: 1
  $name: "Thickness"
  $description: "1 to 20 (Suggested: 1). Pixels."
- circleOpacity: 100
  $name: "Opacity (%)"
  $description: "10 to 100 (Suggested: 100)."
- tStyle: false
  $name: "T shape"
  $description: "Leaves out the top lines."
- rotation: 0
  $name: "Rotation (degrees)"
  $description: "0 to 359 (Suggested: 0). 45 turns a cross into an X."
- smoothEdges: false
  $name: "Smooth edges"
  $description: "Off, straight lines are pixel sharp. On, their edges are softened. Circles and turned lines are always smooth."
- centerOn: "primary"
  $name: "Center on"
  $description: "Pick the game window if your game runs in a window that is not centered on the screen."
  $options:
  - primary: "The main screen"
  - monitor: "The screen picked below"
  - window: "The window in front (your game)"
- monitorNumber: 1
  $name: "Screen"
  $description: "1 to 8 (Suggested: 1). Screens are counted left to right. Used when \"Center on\" is the picked screen."
- offsetX: 0
  $name: "Move right"
  $description: "-2000 to 2000 (Suggested: 0). Pixels from the center. Less than 0 moves it left."
- offsetY: 0
  $name: "Move down"
  $description: "-2000 to 2000 (Suggested: 0). Pixels from the center. Less than 0 moves it up."
- nudgeStep: 1
  $name: "Move step"
  $description: "1 to 50 (Suggested: 1). Pixels per press of a move shortcut."
- showMode: "always"
  $name: "Show"
  $description: "The crosshair always shows while the settings window is open, so you can see your changes. Games in true fullscreen cover everything, so set them to borderless or windowed."
  $options:
  - always: "Always"
  - apps: "Only while one of the games below is in front"
  - fullscreen: "Only while a fullscreen app is in front"
- games: ""
  $name: "Games"
  $description: "Program names split with \";\", such as cs2.exe; VALORANT-Win64-Shipping.exe. * and ? work as wildcards."
- neverApps: ""
  $name: "Never in"
  $description: "Apps the crosshair always hides in, such as explorer.exe; chrome.exe."
- aimButton: "none"
  $name: "Aim button"
  $description: "The button you aim with, for games that show their own scope or sights when you aim."
  $options:
  - none: "None (aiming changes nothing)"
  - right: "Right mouse button"
  - middle: "Middle mouse button"
  - x1: "Back side button"
  - x2: "Forward side button"
  - key: "The key below"
- aimKey: ""
  $name: "Aim key"
  $description: "Used when the aim button is \"The key below\"."
- aimAction: "hide"
  $name: "While aiming"
  $options:
  - hide: "Hide the crosshair"
  - show: "Show the crosshair only while aiming"
- aimMode: "hold"
  $name: "How aiming works"
  $options:
  - hold: "While the button is held"
  - toggle: "Each press starts or stops aiming"
- excludeFromCapture: false
  $name: "Hide from recordings"
  $description: "On, screenshots, recordings and streams don't show the crosshair. Only you see it."
- toggleHotkey: "Ctrl+Alt+X"
  $name: "Show or hide the crosshair"
  $description: "Press the keys in the box. Backspace clears it."
- nextStyleHotkey: "Ctrl+Alt+Z"
  $name: "Next style"
- prevStyleHotkey: ""
  $name: "Previous style"
- nextColorHotkey: ""
  $name: "Next color"
  $description: "Walks the colors listed below."
- sizeUpHotkey: ""
  $name: "Bigger"
- sizeDownHotkey: ""
  $name: "Smaller"
- moveUpHotkey: ""
  $name: "Move up"
  $description: "Hold a move key to keep moving."
- moveDownHotkey: ""
  $name: "Move down"
- moveLeftHotkey: ""
  $name: "Move left"
- moveRightHotkey: ""
  $name: "Move right"
- recenterHotkey: ""
  $name: "Back to the center"
  $description: "Undoes every move."
- settingsHotkey: ""
  $name: "Open settings"
- lookHotkey: ""
  $name: "Keep this look for the game in front"
  $description: "The game gets the crosshair as it is now, every time it comes to the front. Shortcuts pressed in that game then change only its look. Press again to give it the normal look back. The tray menu does the same."
- colorCycle: "#00FF00; #00FFFF; #FFFF00; #FF00FF; #FFFFFF; #FF0000"
  $name: "Colors for \"Next color\""
  $description: "Hexadecimal colors split with \";\". They also fill the tray menu's Color list."
- settingsGlass: true
  $name: "Blurred settings window"
  $description: "On, the settings window is see-through glass with Windows acrylic behind it. Off, it is solid. Applies when you save."
- nativeSettingsTitleBar: false
  $name: "Native Windows title bar"
  $description: "Use the Windows title bar and window buttons for this settings window. Applies when you save."
- settingsTrayIcon: true
  $name: "Tray icon"
  $description: "Click it to open these settings. Right-click it to show or hide the crosshair, or pick a style, color or size. When off, change settings in Windhawk."
- popupOn: true
  $name: "On and off pop-up"
  $description: "A small dock says \"Crosshair enabled\" or \"Crosshair disabled\" each time you switch it."
- popupWhen: "both"
  $name: "Show it for"
  $options:
  - both: "The shortcut and the tray menu"
  - shortcut: "Only the shortcut"
  - tray: "Only the tray menu"
- popupDetail: "style"
  $name: "Second line"
  $description: "The smaller line under \"Crosshair enabled\"."
  $options:
  - style: "The crosshair style"
  - shortcut: "The shortcut that switches it"
  - none: "Nothing"
- popupIcon: true
  $name: "Crosshair icon"
  $description: "The crosshair mark on the left of the pop-up."
- popupDuration: 1500
  $name: "How long it stays (milliseconds)"
  $description: "500 to 10000 (Suggested: 1500). 1000 is one second."
- popupInFullscreen: true
  $name: "Show over fullscreen games"
  $description: "Off, the pop-up stays away while a game or video fills the screen."
- popupPosition: "bottom"
  $name: "Where"
  $options:
  - top: "Top middle"
  - topLeft: "Top left"
  - topRight: "Top right"
  - center: "Middle of the screen"
  - bottom: "Bottom middle"
  - bottomLeft: "Bottom left"
  - bottomRight: "Bottom right"
  - belowCrosshair: "Just below the crosshair"
  - aboveCrosshair: "Just above the crosshair"
- popupScreen: "crosshair"
  $name: "Screen"
  $options:
  - crosshair: "The screen the crosshair is on"
  - primary: "The main screen"
  - pointer: "The screen with the mouse pointer"
  - focused: "The screen of the window in front"
- popupMargin: 48
  $name: "Distance from the edge"
  $description: "0 to 600 (Suggested: 48). Pixels from the screen edge, or from the crosshair when it sits next to it."
- popupOffsetX: 0
  $name: "Move right"
  $description: "-2000 to 2000 (Suggested: 0). Pixels. Less than 0 moves it left."
- popupOffsetY: 0
  $name: "Move down"
  $description: "-2000 to 2000 (Suggested: 0). Pixels. Less than 0 moves it up."
- popupSize: "normal"
  $name: "Size"
  $options:
  - compact: "Compact"
  - normal: "Normal"
  - large: "Large"
- popupGlass: true
  $name: "Blurred glass"
  $description: "On, the pop-up blurs what is behind it. Off, it is solid. The blur needs Windows transparency effects on."
- popupStrength: 85
  $name: "Background strength (%)"
  $description: "80 to 100 (Suggested: 85). How much of the dark background covers the blur."
- popupAnimate: true
  $name: "Slide and fade"
  $description: "On, the pop-up slides and fades in and out. Off, it appears and goes at once."
- fadeOn: true
  $name: "Fade the crosshair"
  $description: "On, the crosshair fades in and out when you show or hide it, instead of popping."
- fadeInTime: 150
  $name: "Fade in time (milliseconds)"
  $description: "0 to 2000 (Suggested: 150)."
- fadeOutTime: 150
  $name: "Fade out time (milliseconds)"
  $description: "0 to 2000 (Suggested: 150)."
- fadeCurve: "smooth"
  $name: "Fade style"
  $options:
  - smooth: "Smooth: starts and ends gently"
  - linear: "Even all the way"
- fadeWhen: "toggle"
  $name: "Fade when"
  $description: "Aiming fades too with the second choice, so leave it on the first for the fastest aim."
  $options:
  - toggle: "You show or hide it"
  - all: "It shows or hides for any reason"
*/
// ==/WindhawkModSettings==

#include <windows.h>
#include <windowsx.h>
#include <shellapi.h>
#include <shlobj.h>
#include <shlwapi.h>
#include <commctrl.h>
#include <dwmapi.h>
#include <uxtheme.h>
#include <d2d1.h>
#include <d2d1_1.h>
#include <d2d1helper.h>
#include <dwrite.h>
#include <wincodec.h>
#include <imm.h>
#include <dispatcherqueue.h>
#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.System.h>
#include <winrt/Windows.Graphics.Effects.h>
#include <winrt/Windows.UI.Composition.h>
#include <winrt/Windows.UI.Composition.Desktop.h>

#include <algorithm>
#include <atomic>
#include <cmath>
#include <cstdint>
#include <cstring>
#include <cwchar>
#include <cwctype>
#include <map>
#include <memory>
#include <mutex>
#include <random>
#include <set>
#include <string>
#include <vector>

#include <windhawk_tool_mod.h>

namespace sgcset {
void OpenSettingsWindow();
void CloseSettingsWindow();
extern std::atomic<HWND> g_settingsWnd;
}  // namespace sgcset

// Generated by gen.py from spec.STYLES: value, label.
struct StyleInfo {
    PCWSTR key, label;
};
static const StyleInfo kStyles[] = {
    {L"crossDot", L"Cross with a dot"},
    {L"cross", L"Cross"},
    {L"smallCross", L"Small cross"},
    {L"dot", L"Dot"},
    {L"tShape", L"T shape"},
    {L"xShape", L"X"},
    {L"circleDot", L"Circle with a dot"},
    {L"circle", L"Circle"},
    {L"tactical", L"Cross in a ring"},
    {L"chevron", L"Chevron"},
    {L"custom", L"Your own design (Shape page)"},
    {L"image", L"An image file (below)"},
};

void WhTool_ModUninit();

// ---------------------------------------------------------------------------
// Small helpers
// ---------------------------------------------------------------------------

static std::wstring ReadStr(PCWSTR name) {
    PCWSTR p = Wh_GetStringSetting(name);
    std::wstring s = p ? p : L"";
    if (p) Wh_FreeStringSetting(p);
    return s;
}

static std::wstring Trim(const std::wstring& s) {
    size_t a = s.find_first_not_of(L" \t\r\n");
    if (a == std::wstring::npos) return {};
    return s.substr(a, s.find_last_not_of(L" \t\r\n") - a + 1);
}

static bool FileExists(const std::wstring& p) {
    DWORD a = GetFileAttributesW(p.c_str());
    return a != INVALID_FILE_ATTRIBUTES && !(a & FILE_ATTRIBUTE_DIRECTORY);
}

static int Clamp(int v, int lo, int hi) { return v < lo ? lo : v > hi ? hi : v; }

static std::wstring OneOf(const std::wstring& v, std::initializer_list<PCWSTR> allowed) {
    for (PCWSTR a : allowed)
        if (v == a) return v;
    return *allowed.begin();
}

static bool ParseHex(const std::wstring& text, COLORREF& out) {
    std::wstring hex = Trim(text);
    if (!hex.empty() && hex[0] == L'#') hex = hex.substr(1);
    if (hex.size() != 6 || hex.find_first_not_of(L"0123456789abcdefABCDEF") != std::wstring::npos) return false;
    UINT rgb = wcstoul(hex.c_str(), nullptr, 16);
    out = RGB(rgb >> 16, (rgb >> 8) & 0xFF, rgb & 0xFF);
    return true;
}

static std::wstring HexOf(COLORREF c) {
    WCHAR buf[8];
    swprintf_s(buf, L"#%02X%02X%02X", GetRValue(c), GetGValue(c), GetBValue(c));
    return buf;
}

static std::vector<std::wstring> SplitList(const std::wstring& s) {
    std::vector<std::wstring> out;
    std::wstring cur;
    for (wchar_t c : s + L";") {
        if (c == L';' || c == L'|' || c == L',' || c == L'\n') {
            std::wstring t = Trim(cur);
            while (t.size() >= 2 && t.front() == L'"' && t.back() == L'"') t = t.substr(1, t.size() - 2);
            if (!t.empty()) out.push_back(t);
            cur.clear();
        } else {
            cur += c;
        }
    }
    return out;
}

template <class T>
struct Ptr {
    T* p = nullptr;
    Ptr() = default;
    Ptr(const Ptr&) = delete;
    Ptr& operator=(const Ptr&) = delete;
    ~Ptr() {
        if (p) p->Release();
    }
    T** put() { return &p; }
    T* operator->() const { return p; }
    explicit operator bool() const { return p != nullptr; }
};

// ---------------------------------------------------------------------------
// Hotkeys: "Ctrl+Alt+X" text, the same the settings window's key boxes write.
// ---------------------------------------------------------------------------

struct KeyName {
    UINT vk;
    const wchar_t* name;
};
// Canonical names first; later entries for the same key are accepted aliases.
static const KeyName kKeyNames[] = {
    {VK_SPACE, L"Space"},   {VK_TAB, L"Tab"},         {VK_RETURN, L"Enter"},   {VK_ESCAPE, L"Esc"},
    {VK_INSERT, L"Insert"}, {VK_DELETE, L"Delete"},   {VK_HOME, L"Home"},      {VK_END, L"End"},
    {VK_PRIOR, L"PageUp"},  {VK_NEXT, L"PageDown"},   {VK_UP, L"Up"},          {VK_DOWN, L"Down"},
    {VK_LEFT, L"Left"},     {VK_RIGHT, L"Right"},     {VK_OEM_3, L"`"},        {VK_OEM_MINUS, L"-"},
    {VK_OEM_PLUS, L"="},    {VK_OEM_4, L"["},         {VK_OEM_6, L"]"},        {VK_OEM_5, L"\\"},
    {VK_OEM_1, L";"},       {VK_OEM_7, L"'"},         {VK_OEM_COMMA, L","},    {VK_OEM_PERIOD, L"."},
    {VK_OEM_2, L"/"},       {VK_PAUSE, L"Pause"},     {VK_SNAPSHOT, L"PrintScreen"},
    {VK_CAPITAL, L"CapsLock"}, {VK_ADD, L"NumpadPlus"}, {VK_SUBTRACT, L"NumpadMinus"},
    {VK_MULTIPLY, L"NumpadStar"}, {VK_DIVIDE, L"NumpadSlash"}, {VK_DECIMAL, L"NumpadDot"},
    {VK_RETURN, L"Return"}, {VK_ESCAPE, L"Escape"},   {VK_INSERT, L"Ins"},     {VK_DELETE, L"Del"},
    {VK_PRIOR, L"PgUp"},    {VK_NEXT, L"PgDn"},
};

static UINT KeyFromName(const std::wstring& n) {
    if (n.size() == 1) {
        wchar_t c = (wchar_t)towupper(n[0]);
        if ((c >= L'A' && c <= L'Z') || (c >= L'0' && c <= L'9')) return c;
    }
    if (n.size() >= 2 && (n[0] == L'F' || n[0] == L'f') && iswdigit(n[1])) {
        int f = _wtoi(n.c_str() + 1);
        if (f >= 1 && f <= 24 && std::to_wstring(f) == n.substr(1)) return VK_F1 + f - 1;
        return 0;
    }
    if (n.size() == 7 && !_wcsnicmp(n.c_str(), L"Numpad", 6) && iswdigit(n[6])) return VK_NUMPAD0 + (n[6] - L'0');
    for (const auto& k : kKeyNames)
        if (!_wcsicmp(n.c_str(), k.name)) return k.vk;
    return 0;
}

bool Hotkey_Parse(const std::wstring& text, UINT& mods, UINT& vk) {
    mods = 0;
    vk = 0;
    std::vector<std::wstring> parts;
    size_t start = 0;
    while (true) {
        size_t plus = text.find(L'+', start);
        parts.push_back(Trim(text.substr(start, plus == std::wstring::npos ? std::wstring::npos : plus - start)));
        if (plus == std::wstring::npos) break;
        start = plus + 1;
    }
    for (size_t i = 0; i + 1 < parts.size(); i++) {
        const wchar_t* p = parts[i].c_str();
        if (!_wcsicmp(p, L"Ctrl") || !_wcsicmp(p, L"Control")) mods |= MOD_CONTROL;
        else if (!_wcsicmp(p, L"Alt")) mods |= MOD_ALT;
        else if (!_wcsicmp(p, L"Shift")) mods |= MOD_SHIFT;
        else if (!_wcsicmp(p, L"Win") || !_wcsicmp(p, L"Windows")) mods |= MOD_WIN;
        else return (mods = 0), false;
    }
    vk = parts.back().empty() ? 0 : KeyFromName(parts.back());
    if (!vk) mods = 0;
    return vk != 0;
}

std::wstring Hotkey_Format(UINT mods, UINT vk) {
    std::wstring key;
    if ((vk >= 'A' && vk <= 'Z') || (vk >= '0' && vk <= '9')) key = std::wstring(1, (wchar_t)vk);
    else if (vk >= VK_F1 && vk <= VK_F24) key = L"F" + std::to_wstring(vk - VK_F1 + 1);
    else if (vk >= VK_NUMPAD0 && vk <= VK_NUMPAD9) key = L"Numpad" + std::to_wstring(vk - VK_NUMPAD0);
    else
        for (const auto& k : kKeyNames)
            if (k.vk == vk) {
                key = k.name;
                break;
            }
    if (key.empty()) return {};
    std::wstring out;
    if (mods & MOD_CONTROL) out += L"Ctrl+";
    if (mods & MOD_ALT) out += L"Alt+";
    if (mods & MOD_SHIFT) out += L"Shift+";
    if (mods & MOD_WIN) out += L"Win+";
    return out + key;
}

// ---------------------------------------------------------------------------
// Settings. Everything below runs on the UI thread, except the save threads.
// ---------------------------------------------------------------------------

enum {
    HK_TOGGLE, HK_NEXT, HK_PREV, HK_COLOR, HK_BIGGER, HK_SMALLER,
    HK_UP, HK_DOWN, HK_LEFT, HK_RIGHT, HK_CENTER, HK_SETTINGS, HK_LOOK, HK_COUNT
};
static const PCWSTR kHotkeyKeys[HK_COUNT] = {
    L"toggleHotkey", L"nextStyleHotkey", L"prevStyleHotkey", L"nextColorHotkey", L"sizeUpHotkey",
    L"sizeDownHotkey", L"moveUpHotkey", L"moveDownHotkey", L"moveLeftHotkey", L"moveRightHotkey",
    L"recenterHotkey", L"settingsHotkey", L"lookHotkey"};
// Size and move keys repeat while held; the rest fire once per press.
static bool HotkeyRepeats(int i) { return i >= HK_BIGGER && i <= HK_RIGHT; }

struct Config {
    std::wstring style = L"crossDot";
    COLORREF color = RGB(0, 255, 0), outlineColor = RGB(0, 0, 0);
    int opacity = 100, scale = 100, outlineTh = 1, outlineOpacity = 80, imageSize = 32;
    bool followScaling = false, outline = true, imageRecolor = false;
    std::wstring imagePath;
    bool dotOn = true, dotRound = false, innerOn = true, outerOn = false, circleOn = false, tStyle = false,
         smooth = false;
    int dotSize = 2, dotOpacity = 100;
    int innerLen = 6, innerTh = 2, innerGap = 3, innerOpacity = 100;
    int outerLen = 2, outerTh = 2, outerGap = 10, outerOpacity = 50;
    int circleR = 10, circleTh = 1, circleOpacity = 100, rotation = 0;
    std::wstring centerOn = L"primary";
    int monitor = 1, offsetX = 0, offsetY = 0, nudge = 1;
    std::wstring showMode = L"always", games, neverApps;
    std::wstring aimButton = L"none", aimKey, aimAction = L"hide", aimMode = L"hold";
    bool excludeCapture = false, trayIcon = true;
    std::wstring hotkeys[HK_COUNT];
    std::vector<COLORREF> colorCycle;
    // The on and off pop-up.
    bool popupOn = true, popupIcon = true, popupInFullscreen = true, popupGlass = true, popupAnimate = true;
    std::wstring popupWhen = L"both", popupDetail = L"style", popupPosition = L"bottom", popupScreen = L"crosshair",
                 popupSize = L"normal";
    int popupDuration = 1500, popupMargin = 48, popupOffsetX = 0, popupOffsetY = 0, popupStrength = 85;
    // The crosshair's own fade.
    bool fadeOn = true, fadeAll = false, fadeLinear = false;
    int fadeIn = 150, fadeOut = 150;
};

static Config g_cfg;

// Values changed by a shortcut or the tray menu that windhawk-cli hasn't saved yet. They win
// over Windhawk's copy, so a reload in between never flips them back.
static std::mutex g_pendLock;
static std::map<std::wstring, std::wstring> g_pending;

// A game's own look ("Keep this look for this game"), kept in the mod's storage as
// look:<program name>. While that game is in front its values win for the look keys, and
// shortcut changes go into it instead of the settings. UI thread only.
static std::wstring g_lookExe;
static std::map<std::wstring, std::wstring> g_look;
static const PCWSTR kLookKeys[] = {
    L"style", L"color", L"opacity", L"scale", L"followScaling", L"outline", L"outlineThickness", L"outlineColor",
    L"outlineOpacity", L"imagePath", L"imageSize", L"imageRecolor", L"dotOn", L"dotSize", L"dotRound", L"dotOpacity",
    L"innerOn", L"innerLength", L"innerThickness", L"innerGap", L"innerOpacity", L"outerOn", L"outerLength",
    L"outerThickness", L"outerGap", L"outerOpacity", L"circleOn", L"circleRadius", L"circleThickness",
    L"circleOpacity", L"tStyle", L"rotation", L"smoothEdges", L"offsetX", L"offsetY"};
static bool IsLookKey(const std::wstring& k) {
    for (PCWSTR l : kLookKeys)
        if (k == l) return true;
    return false;
}
static bool IsLookText(const std::wstring& k) {
    return k == L"style" || k == L"color" || k == L"outlineColor" || k == L"imagePath";
}

static std::wstring SettingStr(PCWSTR key) {
    if (!g_lookExe.empty())
        if (auto it = g_look.find(key); it != g_look.end()) return it->second;
    {
        std::lock_guard<std::mutex> lock(g_pendLock);
        auto it = g_pending.find(key);
        if (it != g_pending.end()) return it->second;
    }
    return ReadStr(key);
}

static int SettingInt(PCWSTR key) {
    if (!g_lookExe.empty())
        if (auto it = g_look.find(key); it != g_look.end()) return _wtoi(it->second.c_str());
    {
        std::lock_guard<std::mutex> lock(g_pendLock);
        auto it = g_pending.find(key);
        if (it != g_pending.end()) return _wtoi(it->second.c_str());
    }
    return Wh_GetIntSetting(key);
}

static bool SettingBool(PCWSTR key) { return SettingInt(key) != 0; }

static COLORREF SettingColor(PCWSTR key, COLORREF fallback) {
    COLORREF c;
    return ParseHex(SettingStr(key), c) ? c : fallback;
}

static void LoadSettings() {
    Config c;
    c.style = SettingStr(L"style");
    bool known = false;
    for (const auto& s : kStyles)
        if (c.style == s.key) known = true;
    if (!known) c.style = L"crossDot";
    c.color = SettingColor(L"color", RGB(0, 255, 0));
    c.opacity = Clamp(SettingInt(L"opacity"), 10, 100);
    c.scale = Clamp(SettingInt(L"scale"), 50, 400);
    c.followScaling = SettingBool(L"followScaling");
    c.outline = SettingBool(L"outline");
    c.outlineTh = Clamp(SettingInt(L"outlineThickness"), 1, 4);
    c.outlineColor = SettingColor(L"outlineColor", RGB(0, 0, 0));
    c.outlineOpacity = Clamp(SettingInt(L"outlineOpacity"), 0, 100);
    c.imagePath = Trim(SettingStr(L"imagePath"));
    while (c.imagePath.size() >= 2 && c.imagePath.front() == L'"' && c.imagePath.back() == L'"')
        c.imagePath = c.imagePath.substr(1, c.imagePath.size() - 2);
    c.imageSize = Clamp(SettingInt(L"imageSize"), 8, 512);
    c.imageRecolor = SettingBool(L"imageRecolor");
    c.dotOn = SettingBool(L"dotOn");
    c.dotSize = Clamp(SettingInt(L"dotSize"), 1, 20);
    c.dotRound = SettingBool(L"dotRound");
    c.dotOpacity = Clamp(SettingInt(L"dotOpacity"), 10, 100);
    c.innerOn = SettingBool(L"innerOn");
    c.innerLen = Clamp(SettingInt(L"innerLength"), 0, 60);
    c.innerTh = Clamp(SettingInt(L"innerThickness"), 1, 20);
    c.innerGap = Clamp(SettingInt(L"innerGap"), 0, 60);
    c.innerOpacity = Clamp(SettingInt(L"innerOpacity"), 10, 100);
    c.outerOn = SettingBool(L"outerOn");
    c.outerLen = Clamp(SettingInt(L"outerLength"), 0, 60);
    c.outerTh = Clamp(SettingInt(L"outerThickness"), 1, 20);
    c.outerGap = Clamp(SettingInt(L"outerGap"), 0, 100);
    c.outerOpacity = Clamp(SettingInt(L"outerOpacity"), 10, 100);
    c.circleOn = SettingBool(L"circleOn");
    c.circleR = Clamp(SettingInt(L"circleRadius"), 2, 100);
    c.circleTh = Clamp(SettingInt(L"circleThickness"), 1, 20);
    c.circleOpacity = Clamp(SettingInt(L"circleOpacity"), 10, 100);
    c.tStyle = SettingBool(L"tStyle");
    c.rotation = Clamp(SettingInt(L"rotation"), 0, 359);
    c.smooth = SettingBool(L"smoothEdges");
    c.centerOn = OneOf(SettingStr(L"centerOn"), {L"primary", L"monitor", L"window"});
    c.monitor = Clamp(SettingInt(L"monitorNumber"), 1, 8);
    c.offsetX = Clamp(SettingInt(L"offsetX"), -2000, 2000);
    c.offsetY = Clamp(SettingInt(L"offsetY"), -2000, 2000);
    c.nudge = Clamp(SettingInt(L"nudgeStep"), 1, 50);
    c.showMode = OneOf(SettingStr(L"showMode"), {L"always", L"apps", L"fullscreen"});
    c.games = SettingStr(L"games");
    c.neverApps = SettingStr(L"neverApps");
    c.aimButton = OneOf(SettingStr(L"aimButton"), {L"none", L"right", L"middle", L"x1", L"x2", L"key"});
    c.aimKey = Trim(SettingStr(L"aimKey"));
    c.aimAction = OneOf(SettingStr(L"aimAction"), {L"hide", L"show"});
    c.aimMode = OneOf(SettingStr(L"aimMode"), {L"hold", L"toggle"});
    c.excludeCapture = SettingBool(L"excludeFromCapture");
    for (int i = 0; i < HK_COUNT; i++) c.hotkeys[i] = Trim(SettingStr(kHotkeyKeys[i]));
    for (auto& s : SplitList(SettingStr(L"colorCycle"))) {
        COLORREF col;
        if (ParseHex(s, col)) c.colorCycle.push_back(col);
    }
    if (c.colorCycle.empty()) c.colorCycle = {RGB(0, 255, 0), RGB(0, 255, 255), RGB(255, 255, 0), RGB(255, 0, 255)};
    c.trayIcon = SettingBool(L"settingsTrayIcon");
    c.popupOn = SettingBool(L"popupOn");
    c.popupWhen = OneOf(SettingStr(L"popupWhen"), {L"both", L"shortcut", L"tray"});
    c.popupDetail = OneOf(SettingStr(L"popupDetail"), {L"style", L"shortcut", L"none"});
    c.popupIcon = SettingBool(L"popupIcon");
    c.popupDuration = Clamp(SettingInt(L"popupDuration"), 500, 10000);
    c.popupInFullscreen = SettingBool(L"popupInFullscreen");
    c.popupPosition = OneOf(SettingStr(L"popupPosition"), {L"bottom", L"top", L"topLeft", L"topRight", L"center",
                                                           L"bottomLeft", L"bottomRight", L"belowCrosshair",
                                                           L"aboveCrosshair"});
    c.popupScreen = OneOf(SettingStr(L"popupScreen"), {L"crosshair", L"primary", L"pointer", L"focused"});
    c.popupMargin = Clamp(SettingInt(L"popupMargin"), 0, 600);
    c.popupOffsetX = Clamp(SettingInt(L"popupOffsetX"), -2000, 2000);
    c.popupOffsetY = Clamp(SettingInt(L"popupOffsetY"), -2000, 2000);
    c.popupSize = OneOf(SettingStr(L"popupSize"), {L"normal", L"compact", L"large"});
    c.popupGlass = SettingBool(L"popupGlass");
    c.popupStrength = Clamp(SettingInt(L"popupStrength"), 80, 100);
    c.popupAnimate = SettingBool(L"popupAnimate");
    c.fadeOn = SettingBool(L"fadeOn");
    c.fadeIn = Clamp(SettingInt(L"fadeInTime"), 0, 2000);
    c.fadeOut = Clamp(SettingInt(L"fadeOutTime"), 0, 2000);
    c.fadeLinear = SettingStr(L"fadeCurve") == L"linear";
    c.fadeAll = SettingStr(L"fadeWhen") == L"all";
    g_cfg = c;
}

// ---------------------------------------------------------------------------
// Saving settings: one elevated windhawk-cli call, off the UI thread.
// ---------------------------------------------------------------------------

static std::wstring CliPath() {
    WCHAR path[MAX_PATH];
    if (HMODULE engine = GetModuleHandleW(L"windhawk.dll"); engine && GetModuleFileNameW(engine, path, MAX_PATH)) {
        std::wstring dir = path;
        for (int i = 0; i < 4 && dir.find_last_of(L'\\') != std::wstring::npos; i++) dir.resize(dir.find_last_of(L'\\'));
        dir += L"\\windhawk-cli.exe";
        if (FileExists(dir)) return dir;
    }
    if (GetModuleFileNameW(nullptr, path, MAX_PATH)) {
        std::wstring dir = path;
        dir.resize(dir.find_last_of(L'\\'));
        dir += L"\\windhawk-cli.exe";
        if (FileExists(dir)) return dir;
    }
    WCHAR pf[MAX_PATH]{};
    ExpandEnvironmentStringsW(L"%ProgramFiles%\\Windhawk\\windhawk-cli.exe", pf, MAX_PATH);
    return FileExists(pf) ? std::wstring(pf) : std::wstring();
}

static std::wstring QuoteArg(const std::wstring& arg) {
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

struct SaveJob {
    std::vector<std::pair<std::wstring, std::wstring>> kv;
};

static std::atomic<int> g_saveThreads{0};

// Saving a shortcut's change needs admin rights, and a shortcut must never raise a Windows prompt.
// Direct: this process already has the rights (or may write the settings key), so windhawk-cli
// just starts. Silent: an admin account where Windows grants the rights without asking, so the
// cli starts as admin with no prompt. None: the change lasts until the mod restarts.
// Worked out once at start.
enum class SaveRoute { None, Direct, Silent };
static SaveRoute g_saveRoute = SaveRoute::None;

static DWORD PolicyValue(PCWSTR name, DWORD fallback) {
    DWORD v = 0, n = sizeof(v);
    if (RegGetValueW(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Policies\\System", name,
                     RRF_RT_REG_DWORD, nullptr, &v, &n) != ERROR_SUCCESS)
        return fallback;
    return v;
}

static SaveRoute PickSaveRoute() {
    bool elevated = false, limitedAdmin = false;
    HANDLE tok;
    if (OpenProcessToken(GetCurrentProcess(), TOKEN_QUERY, &tok)) {
        TOKEN_ELEVATION e{};
        TOKEN_ELEVATION_TYPE type{};
        DWORD n = 0;
        if (GetTokenInformation(tok, TokenElevation, &e, sizeof(e), &n)) elevated = e.TokenIsElevated != 0;
        if (GetTokenInformation(tok, TokenElevationType, &type, sizeof(type), &n))
            limitedAdmin = type == TokenElevationTypeLimited;
        CloseHandle(tok);
    }
    if (elevated) return SaveRoute::Direct;
    std::wstring path = std::wstring(L"SOFTWARE\\Windhawk\\Engine\\Mods\\") + WH_MOD_ID + L"\\Settings";
    HKEY key;
    if (RegOpenKeyExW(HKEY_LOCAL_MACHINE, path.c_str(), 0, KEY_SET_VALUE, &key) == ERROR_SUCCESS) {
        RegCloseKey(key);
        return SaveRoute::Direct;
    }
    // 0 = "Elevate without prompting" for admins.
    if (limitedAdmin && PolicyValue(L"EnableLUA", 1) && PolicyValue(L"ConsentPromptBehaviorAdmin", 5) == 0)
        return SaveRoute::Silent;
    return SaveRoute::None;
}

static void Balloon(PCWSTR title, PCWSTR text);  // Tray note; defined with the tray icon.

static DWORD WINAPI SaveThread(LPVOID param) {
    std::unique_ptr<SaveJob> job((SaveJob*)param);
    std::wstring cli = CliPath();
    if (cli.empty()) {
        Wh_Log(L"windhawk-cli.exe not found, setting not saved");
    } else {
        std::wstring params = L"--quiet mod settings set " + QuoteArg(WH_MOD_ID);
        for (auto& [k, v] : job->kv) params += L" " + QuoteArg(k + L"=" + v);
        HANDLE proc = nullptr;
        if (g_saveRoute == SaveRoute::Direct) {
            std::wstring cmd = QuoteArg(cli) + L" " + params;
            STARTUPINFOW si{sizeof(si)};
            PROCESS_INFORMATION pi{};
            if (CreateProcessW(cli.c_str(), cmd.data(), nullptr, nullptr, FALSE, CREATE_NO_WINDOW, nullptr,
                               nullptr, &si, &pi)) {
                CloseHandle(pi.hThread);
                proc = pi.hProcess;
            }
        } else {
            // Silent route only: Windows grants admin here without a prompt (checked at start).
            SHELLEXECUTEINFOW sei{sizeof(sei)};
            sei.fMask = SEE_MASK_NOCLOSEPROCESS | SEE_MASK_FLAG_NO_UI | SEE_MASK_NOASYNC | SEE_MASK_NO_CONSOLE;
            sei.lpVerb = L"runas";
            sei.lpFile = cli.c_str();
            sei.lpParameters = params.c_str();
            sei.nShow = SW_HIDE;
            if (ShellExecuteExW(&sei)) proc = sei.hProcess;
        }
        if (proc) {
            if (WaitForSingleObject(proc, 15000) == WAIT_TIMEOUT) {
                TerminateProcess(proc, 1);
                Wh_Log(L"windhawk-cli timed out and was stopped");
            }
            CloseHandle(proc);
        } else {
            Wh_Log(L"Couldn't start windhawk-cli (error %lu)", GetLastError());
        }
    }
    {
        // Saved (or given up): Windhawk's copy is the truth again for these keys.
        std::lock_guard<std::mutex> lock(g_pendLock);
        for (auto& [k, v] : job->kv) {
            auto it = g_pending.find(k);
            if (it != g_pending.end() && it->second == v) g_pending.erase(it);
        }
    }
    g_saveThreads--;
    return 0;
}

static void SavePendingAsync() {
    if (g_saveRoute == SaveRoute::None) {
        // The pending values keep winning, so the change still shows until the mod restarts.
        static bool told;
        if (!told) {
            Wh_Log(L"No admin rights without a prompt here, so shortcut changes last until restart");
            Balloon(L"Shortcut changes aren't kept",
                    L"They last until Windhawk restarts. To keep a change, set it in the crosshair's settings.");
        }
        told = true;
        return;
    }
    auto* job = new SaveJob;
    {
        std::lock_guard<std::mutex> lock(g_pendLock);
        for (auto& kv : g_pending) job->kv.push_back(kv);
    }
    if (job->kv.empty()) {
        delete job;
        return;
    }
    g_saveThreads++;
    HANDLE t = CreateThread(nullptr, 0, SaveThread, job, 0, nullptr);
    if (t) CloseHandle(t);
    else {
        g_saveThreads--;
        delete job;
    }
}

// ---------------------------------------------------------------------------
// Drawing. The crosshair is a few parts (boxes, disks, rings, strokes), each
// with a signed distance. A pixel's coverage comes from the distance at its
// center: sharp (inside or not) for straight lines on whole pixels, soft
// (0.5 - distance) for curves, turned lines and "Smooth edges". The outline is
// the same parts grown by the outline thickness, drawn under the fill.
// ---------------------------------------------------------------------------

struct Part {
    enum Type { Box, Disk, Ring, Stroke } type;
    float x0 = 0, y0 = 0, x1 = 0, y1 = 0;  // Box corners, or Stroke ends.
    float cx = 0, cy = 0, r = 0;           // Disk and Ring center and radius; Stroke and Ring half width in r/hw.
    float hw = 0;
    float op = 1;
    bool soft = false;
};

static float PartDistance(const Part& p, float x, float y) {
    switch (p.type) {
        case Part::Box: {
            float hx = (p.x1 - p.x0) / 2, hy = (p.y1 - p.y0) / 2;
            float dx = std::fabs(x - (p.x0 + p.x1) / 2) - hx, dy = std::fabs(y - (p.y0 + p.y1) / 2) - hy;
            float ox = std::max(dx, 0.0f), oy = std::max(dy, 0.0f);
            return std::sqrt(ox * ox + oy * oy) + std::min(std::max(dx, dy), 0.0f);
        }
        case Part::Disk: return std::hypot(x - p.cx, y - p.cy) - p.r;
        case Part::Ring: return std::fabs(std::hypot(x - p.cx, y - p.cy) - p.r) - p.hw;
        case Part::Stroke: {
            float vx = p.x1 - p.x0, vy = p.y1 - p.y0, wx = x - p.x0, wy = y - p.y0;
            float len2 = vx * vx + vy * vy;
            float t = len2 > 0 ? std::clamp((wx * vx + wy * vy) / len2, 0.0f, 1.0f) : 0.0f;
            return std::hypot(wx - vx * t, wy - vy * t) - p.hw;
        }
    }
    return 1e9f;
}

// Farthest point of a part from (px, py), for the canvas size.
static float PartReach(const Part& p, float px, float py) {
    auto d = [&](float x, float y) { return std::hypot(x - px, y - py); };
    switch (p.type) {
        case Part::Box: return std::max({d(p.x0, p.y0), d(p.x1, p.y0), d(p.x0, p.y1), d(p.x1, p.y1)});
        case Part::Disk: return d(p.cx, p.cy) + p.r;
        case Part::Ring: return d(p.cx, p.cy) + p.r + p.hw;
        case Part::Stroke: return std::max(d(p.x0, p.y0), d(p.x1, p.y1)) + p.hw;
    }
    return 0;
}

struct Design {
    bool dot = false, dotRound = false, inner = false, outer = false, ring = false, chevron = false, t = false,
         smooth = false;
    int dotSize = 2, innerLen = 6, innerTh = 2, innerGap = 3, outerLen = 2, outerTh = 2, outerGap = 10;
    float dotOp = 1, innerOp = 1, outerOp = 0.5f, ringOp = 1;
    float ringR = 10, ringTh = 1;
    int chevLen = 9, chevTh = 2;
    int rot = 0;
};

static Design DesignFor(const Config& c) {
    Design d;
    const std::wstring& s = c.style;
    auto lines = [&](int len, int th, int gap) {
        d.inner = true;
        d.innerLen = len;
        d.innerTh = th;
        d.innerGap = gap;
    };
    if (s == L"custom") {
        d.dot = c.dotOn;
        d.dotSize = c.dotSize;
        d.dotRound = c.dotRound;
        d.dotOp = c.dotOpacity / 100.0f;
        d.inner = c.innerOn;
        d.innerLen = c.innerLen;
        d.innerTh = c.innerTh;
        d.innerGap = c.innerGap;
        d.innerOp = c.innerOpacity / 100.0f;
        d.outer = c.outerOn;
        d.outerLen = c.outerLen;
        d.outerTh = c.outerTh;
        d.outerGap = c.outerGap;
        d.outerOp = c.outerOpacity / 100.0f;
        d.ring = c.circleOn;
        d.ringR = (float)c.circleR;
        d.ringTh = (float)c.circleTh;
        d.ringOp = c.circleOpacity / 100.0f;
        d.t = c.tStyle;
        d.rot = c.rotation;
        d.smooth = c.smooth;
    } else if (s == L"cross") {
        lines(7, 2, 3);
    } else if (s == L"smallCross") {
        lines(4, 1, 2);
    } else if (s == L"dot") {
        d.dot = true;
        d.dotSize = 4;
        d.dotRound = true;
    } else if (s == L"tShape") {
        lines(7, 2, 3);
        d.t = true;
        d.dot = true;
    } else if (s == L"xShape") {
        lines(7, 2, 3);
        d.rot = 45;
    } else if (s == L"circleDot") {
        d.ring = true;
        d.ringR = 10;
        d.ringTh = 2;
        d.dot = true;
        d.dotRound = true;
    } else if (s == L"circle") {
        d.ring = true;
        d.ringR = 8;
        d.ringTh = 2;
    } else if (s == L"tactical") {
        lines(6, 2, 7);
        d.ring = true;
        d.ringR = 17;
        d.ringTh = 1.5f;
        d.dot = true;
    } else if (s == L"chevron") {
        d.chevron = true;
    } else {  // crossDot
        lines(6, 2, 3);
        d.dot = true;
    }
    return d;
}

struct Bitmap {
    std::vector<uint32_t> px;  // Premultiplied BGRA, top-down.
    int w = 0, h = 0;
    int ax = 0, ay = 0;  // The pixel that sits on the aim point.
};

static Bitmap DrawDesign(const Config& c, const Design& d, float k) {
    auto sz = [&](int v, int lo) { return std::max(lo, (int)std::lround(v * k)); };
    // A run of th pixels centered on the aim point: [-th/2, -th/2 + th). Even widths sit on the
    // screen's true middle line, odd ones on the pixel just right of it.
    auto lo = [](int th) { return -(th / 2); };
    std::vector<Part> parts;
    bool softBoxes = d.smooth || d.rot % 90 != 0;
    int primary = d.inner ? sz(d.innerTh, 1) : d.dot ? sz(d.dotSize, 1) : d.outer ? sz(d.outerTh, 1) : 2;
    float vc = lo(primary) + primary / 2.0f;  // The visual center: rings, round dots and turning use it.

    auto box = [&](float x0, float y0, float x1, float y1, float op) {
        Part p{Part::Box};
        p.x0 = x0, p.y0 = y0, p.x1 = x1, p.y1 = y1, p.op = op, p.soft = softBoxes;
        parts.push_back(p);
    };
    auto arms = [&](int len, int th, int gap, float op) {
        len = sz(len, 0);
        th = sz(th, 1);
        gap = (int)std::lround(gap * k);
        if (len <= 0) return;
        float b0 = (float)lo(th), b1 = b0 + th;
        box(b1 + gap, b0, b1 + gap + len, b1, op);                // Right.
        box(b0 - gap - len, b0, b0 - gap, b1, op);                // Left.
        box(b0, b1 + gap, b1, b1 + gap + len, op);                // Down.
        if (!d.t) box(b0, b0 - gap - len, b1, b0 - gap, op);      // Up.
        if (gap == 0) box(b0, b0, b1, b1, op);                    // A gapless cross has no hole.
    };
    if (d.outer) arms(d.outerLen, d.outerTh, d.outerGap, d.outerOp);
    if (d.inner) arms(d.innerLen, d.innerTh, d.innerGap, d.innerOp);
    if (d.ring) {
        Part p{Part::Ring};
        p.cx = p.cy = vc;
        p.r = d.ringR * k;
        p.hw = std::max(1.0f, d.ringTh * k) / 2;
        p.op = d.ringOp;
        p.soft = true;
        parts.push_back(p);
    }
    if (d.chevron) {
        float len = d.chevLen * k, hw = std::max(1.0f, d.chevTh * k) / 2, s = len * 0.7071f;
        for (int side : {-1, 1}) {
            Part p{Part::Stroke};
            p.x0 = vc, p.y0 = vc, p.x1 = vc + side * s, p.y1 = vc + s;
            p.hw = hw;
            p.soft = true;
            parts.push_back(p);
        }
    }
    if (d.dot) {
        int ds = sz(d.dotSize, 1);
        if (d.dotRound) {
            Part p{Part::Disk};
            p.cx = p.cy = vc;
            p.r = std::max(0.75f, ds / 2.0f);
            p.op = d.dotOp;
            p.soft = true;
            parts.push_back(p);
        } else {
            float b0 = (float)lo(ds);
            box(b0, b0, b0 + ds, b0 + ds, d.dotOp);
        }
    }

    float ot = c.outline ? (float)std::max(1, (int)std::lround(c.outlineTh * std::max(1.0f, k * 0.75f))) : 0.0f;
    float reach = 1;
    for (auto& p : parts) reach = std::max(reach, PartReach(p, vc, vc));
    int half = (int)std::ceil(reach + ot + 2);
    Bitmap bm;
    bm.w = bm.h = half * 2 + 2;
    bm.ax = bm.ay = half;
    bm.px.assign((size_t)bm.w * bm.h, 0);
    if (parts.empty()) return bm;

    float ang = d.rot * 3.14159265f / 180.0f, cs = std::cos(ang), sn = std::sin(ang);
    if (d.rot % 90 == 0) {  // Exact, so turned sharp lines stay on whole pixels.
        int q = (d.rot / 90) % 4;
        cs = q == 0 ? 1.0f : q == 2 ? -1.0f : 0.0f;
        sn = q == 1 ? 1.0f : q == 3 ? -1.0f : 0.0f;
    }
    float gop = c.opacity / 100.0f, oop = c.outlineOpacity / 100.0f;
    float fr = GetRValue(c.color) / 255.0f, fg = GetGValue(c.color) / 255.0f, fb = GetBValue(c.color) / 255.0f;
    float orr = GetRValue(c.outlineColor) / 255.0f, og = GetGValue(c.outlineColor) / 255.0f,
          ob = GetBValue(c.outlineColor) / 255.0f;
    for (int y = 0; y < bm.h; y++)
        for (int x = 0; x < bm.w; x++) {
            // Pixel center in design space (aim pixel at 0), turned back by the rotation about vc.
            float px = x - half + 0.5f - vc, py = y - half + 0.5f - vc;
            float qx = px * cs + py * sn + vc, qy = -px * sn + py * cs + vc;
            float fill = 0, geom = 0, edge = 0;
            for (auto& p : parts) {
                float dist = PartDistance(p, qx, qy);
                if (dist > ot + 1) continue;
                float cov = p.soft ? std::clamp(0.5f - dist, 0.0f, 1.0f) : (dist <= 0 ? 1.0f : 0.0f);
                fill = std::max(fill, cov * p.op);
                geom = std::max(geom, cov);
                if (ot > 0) {
                    float od = dist - ot;
                    edge = std::max(edge, p.soft ? std::clamp(0.5f - od, 0.0f, 1.0f) : (od <= 0 ? 1.0f : 0.0f));
                }
            }
            float fa = fill * gop, oa = edge * (1 - geom) * oop * gop;
            float a = fa + oa;
            if (a <= 0) continue;
            auto ch = [](float v) { return (uint32_t)std::clamp((int)std::lround(v * 255), 0, 255); };
            bm.px[(size_t)y * bm.w + x] = (ch(a) << 24) | (ch(fr * fa + orr * oa) << 16) |
                                          (ch(fg * fa + og * oa) << 8) | ch(fb * fa + ob * oa);
        }
    return bm;
}

static bool DrawImage(const Config& c, float k, Bitmap& bm) {
    if (c.imagePath.empty()) return false;
    WCHAR full[MAX_PATH * 2]{};
    ExpandEnvironmentStringsW(c.imagePath.c_str(), full, ARRAYSIZE(full));
    Ptr<IWICImagingFactory> f;
    Ptr<IWICBitmapDecoder> dec;
    Ptr<IWICBitmapFrameDecode> frame;
    Ptr<IWICBitmapScaler> scaler;
    Ptr<IWICFormatConverter> conv;
    if (FAILED(CoCreateInstance(CLSID_WICImagingFactory, nullptr, CLSCTX_INPROC_SERVER, IID_IWICImagingFactory,
                                (void**)f.put())))
        return false;
    if (FAILED(f->CreateDecoderFromFilename(full, nullptr, GENERIC_READ, WICDecodeMetadataCacheOnDemand, dec.put())) ||
        FAILED(dec->GetFrame(0, frame.put()))) {
        Wh_Log(L"Couldn't read the image %s", full);
        return false;
    }
    UINT iw = 0, ih = 0;
    frame->GetSize(&iw, &ih);
    if (!iw || !ih) return false;
    int box = std::clamp((int)std::lround(c.imageSize * k), 2, 2048);
    int w = iw >= ih ? box : std::max(1, (int)std::lround((double)box * iw / ih));
    int h = ih >= iw ? box : std::max(1, (int)std::lround((double)box * ih / iw));
    if (FAILED(f->CreateBitmapScaler(scaler.put())) ||
        FAILED(scaler->Initialize(frame.p, w, h, WICBitmapInterpolationModeFant)) ||
        FAILED(f->CreateFormatConverter(conv.put())) ||
        FAILED(conv->Initialize(scaler.p, GUID_WICPixelFormat32bppPBGRA, WICBitmapDitherTypeNone, nullptr, 0,
                                WICBitmapPaletteTypeCustom)))
        return false;
    bm.w = w;
    bm.h = h;
    bm.ax = w / 2;
    bm.ay = h / 2;
    bm.px.assign((size_t)w * h, 0);
    if (FAILED(conv->CopyPixels(nullptr, w * 4, w * h * 4, (BYTE*)bm.px.data()))) return false;
    float gop = c.opacity / 100.0f;
    for (auto& v : bm.px) {
        float a = (v >> 24) / 255.0f;
        float r = ((v >> 16) & 0xFF) / 255.0f, g = ((v >> 8) & 0xFF) / 255.0f, b = (v & 0xFF) / 255.0f;
        if (c.imageRecolor) {
            r = GetRValue(c.color) / 255.0f * a;
            g = GetGValue(c.color) / 255.0f * a;
            b = GetBValue(c.color) / 255.0f * a;
        }
        auto ch = [](float x) { return (uint32_t)std::clamp((int)std::lround(x * 255), 0, 255); };
        v = (ch(a * gop) << 24) | (ch(r * gop) << 16) | (ch(g * gop) << 8) | ch(b * gop);
    }
    return true;
}

// ---------------------------------------------------------------------------
// The overlay window: layered, click-through, topmost, never activated.
// ---------------------------------------------------------------------------

enum : UINT {
    WM_SGC_TRAY = WM_APP + 45,
    WM_SGC_SETTINGS,
};

constexpr UINT kTrayId = 1;
constexpr UINT_PTR kTimerTrack = 1, kTimerAim = 2, kTimerTopmost = 3, kTimerSave = 4, kTimerBlink = 5,
                   kTimerFullscreen = 6, kTimerFade = 7;

static HWND g_msgWnd, g_overlay;
static DWORD g_uiTid;
static HANDLE g_uiThread, g_uiReady;
static HWINEVENTHOOK g_fgHook;
static UINT g_taskbarCreated;
static bool g_trayAdded;
static HICON g_trayIcon;
static bool g_hotkeyOn[HK_COUNT];

static Bitmap g_bitmap;
static POINT g_target{};       // The screen pixel the crosshair aims at.
static HMONITOR g_targetMon;
static bool g_haveTarget;
static POINT g_winPos{INT_MIN, INT_MIN};
static SIZE g_winSize{};
static bool g_visible;
// The crosshair's fade: how far in it is (0 gone, 1 full), and which way it is going.
static float g_fadeP = 1;
static int g_fadeDir;
static ULONGLONG g_fadeLast;
static bool g_fadeNext;  // The next show or hide comes from the shortcut or the tray.
static bool g_fadeSkip;  // The next show is the end of a blink: no fade.

static std::atomic<bool> g_shown{true};  // The show or hide shortcut, kept across restarts.
static bool g_appOk = true;              // The app in front passes the "Show" rules.
static bool g_aiming;
static bool g_aimKeyWasDown;
static bool g_watchSettings;  // The settings window was asked for; keep checking until it closes.
static DWORD g_watchSince;
static std::wstring g_lastApp;          // Program name of the last real app in front, lower case.
static std::set<std::wstring> g_fullscreenTold;  // Games already given the "true fullscreen" hint.

static BOOL CALLBACK CollectMonitor(HMONITOR m, HDC, LPRECT, LPARAM lp) {
    ((std::vector<HMONITOR>*)lp)->push_back(m);
    return TRUE;
}

static RECT MonitorRect(HMONITOR m) {
    MONITORINFO mi{sizeof(mi)};
    GetMonitorInfoW(m, &mi);
    return mi.rcMonitor;
}

static bool IsShellWindow(HWND hwnd) {
    WCHAR cls[64]{};
    GetClassNameW(hwnd, cls, 64);
    return !wcscmp(cls, L"Progman") || !wcscmp(cls, L"WorkerW") || !wcscmp(cls, L"Shell_TrayWnd") ||
           !wcscmp(cls, L"Shell_SecondaryTrayWnd");
}

static bool IsOwnWindow(HWND hwnd) {
    DWORD pid = 0;
    GetWindowThreadProcessId(hwnd, &pid);
    return pid == GetCurrentProcessId();
}

// The front window that a game would be: not the desktop, the taskbar, or this mod's own windows.
static HWND GameWindow() {
    HWND fg = GetForegroundWindow();
    if (!fg || IsIconic(fg) || IsShellWindow(fg) || IsOwnWindow(fg)) return nullptr;
    return fg;
}

static void ComputeTarget() {
    const Config& c = g_cfg;
    POINT pt{};
    HMONITOR mon = nullptr;
    bool ok = false;
    if (c.centerOn == L"window") {
        if (HWND fg = GameWindow()) {
            RECT rc;
            if (GetClientRect(fg, &rc) && rc.right > 0 && rc.bottom > 0) {
                POINT tl{0, 0};
                ClientToScreen(fg, &tl);
                pt = {tl.x + rc.right / 2, tl.y + rc.bottom / 2};
                mon = MonitorFromWindow(fg, MONITOR_DEFAULTTONEAREST);
                ok = true;
            }
        } else if (g_haveTarget && g_cfg.centerOn == L"window") {
            return;  // Desktop or this mod in front: stay where the game was.
        }
    }
    if (!ok) {
        if (c.centerOn == L"monitor") {
            std::vector<HMONITOR> mons;
            EnumDisplayMonitors(nullptr, nullptr, CollectMonitor, (LPARAM)&mons);
            std::sort(mons.begin(), mons.end(), [](HMONITOR a, HMONITOR b) {
                RECT ra = MonitorRect(a), rb = MonitorRect(b);
                return ra.left != rb.left ? ra.left < rb.left : ra.top < rb.top;
            });
            if (c.monitor - 1 < (int)mons.size()) mon = mons[c.monitor - 1];
        }
        if (!mon) mon = MonitorFromPoint(POINT{0, 0}, MONITOR_DEFAULTTOPRIMARY);
        RECT r = MonitorRect(mon);
        pt = {r.left + (r.right - r.left) / 2, r.top + (r.bottom - r.top) / 2};
    }
    g_target = {pt.x + c.offsetX, pt.y + c.offsetY};
    g_targetMon = mon;
    g_haveTarget = true;
}

static float ScaleFactor() {
    float k = g_cfg.scale / 100.0f;
    if (g_cfg.followScaling && g_targetMon) {
        using Fn = HRESULT(WINAPI*)(HMONITOR, int, UINT*, UINT*);
        static Fn get = (Fn)GetProcAddress(LoadLibraryExW(L"shcore.dll", nullptr, LOAD_LIBRARY_SEARCH_SYSTEM32),
                                           "GetDpiForMonitor");
        UINT dx = 96, dy = 96;
        if (get && SUCCEEDED(get(g_targetMon, 0 /* MDT_EFFECTIVE_DPI */, &dx, &dy))) k *= dx / 96.0f;
    }
    return k;
}

static float g_drawnScale;

static void RenderBitmap() {
    const Config& c = g_cfg;
    float k = ScaleFactor();
    g_drawnScale = k;
    Bitmap bm;
    if (c.style == L"image" && DrawImage(c, k, bm)) {
        g_bitmap = std::move(bm);
        return;
    }
    Design d = c.style == L"image" ? DesignFor(Config{}) : DesignFor(c);  // A missing image falls back.
    g_bitmap = DrawDesign(c, d, k);
}

static BYTE FadeAlpha() {
    float p = std::clamp(g_fadeP, 0.0f, 1.0f);
    if (!g_cfg.fadeLinear) p = p * p * (3 - 2 * p);  // Starts and ends gently.
    return (BYTE)std::lround(p * 255);
}

// Only the opacity changes: the drawn crosshair stays as it is.
static void PushAlpha() {
    if (!g_overlay) return;
    BLENDFUNCTION bf{AC_SRC_OVER, 0, FadeAlpha(), AC_SRC_ALPHA};
    UpdateLayeredWindow(g_overlay, nullptr, nullptr, nullptr, nullptr, nullptr, 0, &bf, ULW_ALPHA);
}

static void PushBitmap() {
    if (!g_overlay || g_bitmap.w <= 0) return;
    POINT pos{g_target.x - g_bitmap.ax, g_target.y - g_bitmap.ay};
    SIZE size{g_bitmap.w, g_bitmap.h};
    BITMAPINFO bi{};
    bi.bmiHeader.biSize = sizeof(bi.bmiHeader);
    bi.bmiHeader.biWidth = size.cx;
    bi.bmiHeader.biHeight = -size.cy;
    bi.bmiHeader.biPlanes = 1;
    bi.bmiHeader.biBitCount = 32;
    HDC screen = GetDC(nullptr);
    void* bits = nullptr;
    HBITMAP dib = CreateDIBSection(screen, &bi, DIB_RGB_COLORS, &bits, nullptr, 0);
    if (dib) {
        memcpy(bits, g_bitmap.px.data(), g_bitmap.px.size() * 4);
        HDC mem = CreateCompatibleDC(screen);
        HGDIOBJ old = SelectObject(mem, dib);
        POINT src{0, 0};
        BLENDFUNCTION bf{AC_SRC_OVER, 0, FadeAlpha(), AC_SRC_ALPHA};
        if (!UpdateLayeredWindow(g_overlay, screen, &pos, &size, mem, &src, 0, &bf, ULW_ALPHA))
            Wh_Log(L"UpdateLayeredWindow failed (error %lu)", GetLastError());
        SelectObject(mem, old);
        DeleteDC(mem);
        DeleteObject(dib);
        g_winPos = pos;
        g_winSize = size;
    }
    ReleaseDC(nullptr, screen);
}

static void MoveOverlay() {
    POINT pos{g_target.x - g_bitmap.ax, g_target.y - g_bitmap.ay};
    if (pos.x == g_winPos.x && pos.y == g_winPos.y) return;
    SetWindowPos(g_overlay, nullptr, pos.x, pos.y, 0, 0, SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE);
    g_winPos = pos;
}

static void KeepOnTop() {
    if (g_overlay && g_visible)
        SetWindowPos(g_overlay, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE | SWP_NOOWNERZORDER);
}

// ---------------------------------------------------------------------------
// When to show
// ---------------------------------------------------------------------------

static std::wstring ProcessName(HWND hwnd) {
    static HWND lastHwnd;
    static DWORD lastPid;
    static std::wstring lastName;
    DWORD pid = 0;
    GetWindowThreadProcessId(hwnd, &pid);
    if (hwnd == lastHwnd && pid == lastPid) return lastName;
    std::wstring path;
    if (HANDLE h = OpenProcess(PROCESS_QUERY_LIMITED_INFORMATION, FALSE, pid)) {
        WCHAR buf[MAX_PATH * 2];
        DWORD n = ARRAYSIZE(buf);
        if (QueryFullProcessImageNameW(h, 0, buf, &n)) path.assign(buf, n);
        CloseHandle(h);
    }
    lastHwnd = hwnd;
    lastPid = pid;
    lastName = path.substr(path.find_last_of(L'\\') == std::wstring::npos ? 0 : path.find_last_of(L'\\') + 1);
    return lastName;
}

static bool MatchAny(const std::wstring& list, const std::wstring& name) {
    if (name.empty()) return false;
    for (auto& pat : SplitList(list))
        if (PathMatchSpecW(name.c_str(), pat.c_str())) return true;
    return false;
}

static bool IsFullscreen(HWND hwnd) {
    RECT wr;
    if (!GetWindowRect(hwnd, &wr)) return false;
    RECT mr = MonitorRect(MonitorFromWindow(hwnd, MONITOR_DEFAULTTONEAREST));
    return wr.left <= mr.left && wr.top <= mr.top && wr.right >= mr.right && wr.bottom >= mr.bottom;
}

// ---------------------------------------------------------------------------
// A look per game: key=value lines in the mod's storage, one value per program.
// ---------------------------------------------------------------------------

static std::wstring LowerName(std::wstring s) {
    for (auto& ch : s) ch = (wchar_t)towlower(ch);
    return s;
}

static std::map<std::wstring, std::wstring> ReadLook(const std::wstring& exe) {
    std::map<std::wstring, std::wstring> look;
    std::vector<WCHAR> buf(16384);
    Wh_GetStringValue((L"look:" + exe).c_str(), buf.data(), buf.size());
    std::wstring all = buf.data();
    size_t at = 0;
    while (at < all.size()) {
        size_t end = all.find(L'\n', at);
        if (end == std::wstring::npos) end = all.size();
        std::wstring line = all.substr(at, end - at);
        size_t eq = line.find(L'=');
        if (eq != std::wstring::npos && IsLookKey(line.substr(0, eq))) look[line.substr(0, eq)] = line.substr(eq + 1);
        at = end + 1;
    }
    return look;
}

static void WriteLook(const std::wstring& exe, const std::map<std::wstring, std::wstring>& look) {
    std::wstring all;
    for (auto& [k, v] : look) all += k + L"=" + v + L"\n";
    Wh_SetStringValue((L"look:" + exe).c_str(), all.c_str());
}

// The buffer must hold the whole value: a read into a smaller one fails and returns nothing.
static bool HasLook(const std::wstring& exe) {
    std::vector<WCHAR> buf(16384);
    Wh_GetStringValue((L"look:" + exe).c_str(), buf.data(), buf.size());
    return buf[0] != 0;
}

// Follows the app in front. True when the look in use changed, so the settings need a reload.
static bool UpdateLook() {
    HWND fg = GameWindow();
    if (!fg) return false;  // The desktop, the taskbar or our own windows keep the current look.
    std::wstring exe = LowerName(ProcessName(fg));
    if (exe.empty()) return false;
    g_lastApp = exe;
    std::wstring want = HasLook(exe) ? exe : std::wstring();
    Wh_Log(L"Front app %s, look in use [%s], its own look [%s]", exe.c_str(), g_lookExe.c_str(), want.c_str());
    if (want == g_lookExe) return false;
    g_lookExe = want;
    g_look = want.empty() ? std::map<std::wstring, std::wstring>() : ReadLook(want);
    return true;
}

static void EvaluateApp() {
    const Config& c = g_cfg;
    HWND fg = GetForegroundWindow();
    if (!fg || IsOwnWindow(fg)) return;  // Our own windows keep the last answer.
    std::wstring name = ProcessName(fg);
    bool ok;
    if (MatchAny(c.neverApps, name)) ok = false;
    else if (c.showMode == L"apps") ok = MatchAny(c.games, name);
    else if (c.showMode == L"fullscreen") ok = !IsShellWindow(fg) && IsFullscreen(fg);
    else ok = true;
    g_appOk = ok;
}

static bool SettingsOpen() { return sgcset::g_settingsWnd.load() != nullptr; }

static void UpdateVisibility() {
    const Config& c = g_cfg;
    bool aimOk = c.aimButton == L"none" || (c.aimAction == L"hide" ? !g_aiming : g_aiming);
    bool want = SettingsOpen() || (g_shown && g_appOk && aimOk);
    const bool fade = !g_fadeSkip && c.fadeOn && (c.fadeAll || g_fadeNext);
    g_fadeNext = g_fadeSkip = false;
    if (want == g_visible) return;
    g_visible = want;
    const bool onScreen = IsWindowVisible(g_overlay) != FALSE;
    if (want) {
        if (fade && c.fadeIn > 0) {
            if (!onScreen) g_fadeP = 0;  // A hide halfway through turns round from where it is.
            g_fadeDir = 1;
        } else {
            g_fadeP = 1;
            g_fadeDir = 0;
        }
        PushAlpha();
        ShowWindow(g_overlay, SW_SHOWNOACTIVATE);
        KeepOnTop();
        SetTimer(g_msgWnd, kTimerTopmost, 2000, nullptr);
    } else {
        if (fade && c.fadeOut > 0 && onScreen) {
            g_fadeDir = -1;
        } else {
            g_fadeDir = 0;
            g_fadeP = 0;
            ShowWindow(g_overlay, SW_HIDE);
        }
        KillTimer(g_msgWnd, kTimerTopmost);
    }
    if (g_fadeDir) {
        g_fadeLast = GetTickCount64();
        SetTimer(g_msgWnd, kTimerFade, 15, nullptr);
    } else {
        KillTimer(g_msgWnd, kTimerFade);
    }
}

static void FadeTick() {
    const ULONGLONG now = GetTickCount64();
    const float dt = (float)(now - g_fadeLast);
    g_fadeLast = now;
    const int ms = g_fadeDir > 0 ? g_cfg.fadeIn : g_cfg.fadeOut;
    g_fadeP += g_fadeDir * (ms > 0 ? dt / ms : 1.0f);
    if (g_fadeP >= 1) {
        g_fadeP = 1;
        g_fadeDir = 0;
    } else if (g_fadeP <= 0) {
        g_fadeP = 0;
        g_fadeDir = 0;
        ShowWindow(g_overlay, SW_HIDE);
    }
    PushAlpha();
    if (!g_fadeDir) KillTimer(g_msgWnd, kTimerFade);
}

static UINT AimVk(UINT& mods) {
    const Config& c = g_cfg;
    mods = 0;
    if (c.aimButton == L"right") return GetSystemMetrics(SM_SWAPBUTTON) ? VK_LBUTTON : VK_RBUTTON;
    if (c.aimButton == L"middle") return VK_MBUTTON;
    if (c.aimButton == L"x1") return VK_XBUTTON1;
    if (c.aimButton == L"x2") return VK_XBUTTON2;
    UINT vk = 0;
    if (c.aimButton == L"key" && Hotkey_Parse(c.aimKey, mods, vk)) return vk;
    return 0;
}

static bool KeyDown(UINT vk) { return (GetAsyncKeyState((int)vk) & 0x8000) != 0; }

static void PollAim() {
    UINT mods;
    UINT vk = AimVk(mods);
    if (!vk) return;
    bool down = KeyDown(vk) && (!(mods & MOD_CONTROL) || KeyDown(VK_CONTROL)) &&
                (!(mods & MOD_ALT) || KeyDown(VK_MENU)) && (!(mods & MOD_SHIFT) || KeyDown(VK_SHIFT)) &&
                (!(mods & MOD_WIN) || KeyDown(VK_LWIN) || KeyDown(VK_RWIN));
    bool aiming = g_aiming;
    if (g_cfg.aimMode == L"toggle") {
        if (down && !g_aimKeyWasDown) aiming = !aiming;
    } else {
        aiming = down;
    }
    g_aimKeyWasDown = down;
    if (aiming != g_aiming) {
        g_aiming = aiming;
        UpdateVisibility();
    }
}

// Only the timers the settings need: nothing runs while the crosshair just sits there.
static void UpdateTimers() {
    const Config& c = g_cfg;
    bool track = c.centerOn == L"window" || c.showMode == L"fullscreen" || g_watchSettings;
    if (track) SetTimer(g_msgWnd, kTimerTrack, 250, nullptr);
    else KillTimer(g_msgWnd, kTimerTrack);
    if (c.aimButton != L"none" && g_shown) SetTimer(g_msgWnd, kTimerAim, 15, nullptr);
    else {
        KillTimer(g_msgWnd, kTimerAim);
        g_aiming = false;
        g_aimKeyWasDown = false;
    }
}

static void Refresh(bool redraw) {
    ComputeTarget();
    if (redraw || std::fabs(ScaleFactor() - g_drawnScale) > 0.001f) {
        RenderBitmap();
        PushBitmap();
    } else {
        MoveOverlay();
    }
    EvaluateApp();
    UpdateVisibility();
}

static void ApplyConfig();

static void CALLBACK ForegroundProc(HWINEVENTHOOK, DWORD, HWND, LONG, LONG, DWORD, DWORD) {
    if (UpdateLook()) {
        LoadSettings();
        ApplyConfig();
    } else {
        Refresh(false);
    }
    KeepOnTop();
    // Games switch to fullscreen a moment after they come to the front.
    SetTimer(g_msgWnd, kTimerFullscreen, 4000, nullptr);
}

// Games in true (exclusive) fullscreen own the screen, so no window can draw over them. Windows
// reports that state; say so once per game, since the fix is a setting in the game.
static void CheckTrueFullscreen() {
    QUERY_USER_NOTIFICATION_STATE state;
    if (FAILED(SHQueryUserNotificationState(&state)) || state != QUNS_RUNNING_D3D_FULL_SCREEN) return;
    if (!g_shown || !g_appOk) return;
    HWND fg = GameWindow();
    if (!fg) return;
    std::wstring exe = LowerName(ProcessName(fg));
    if (exe.empty() || !g_fullscreenTold.insert(exe).second) return;
    Wh_Log(L"%s runs in true fullscreen; the crosshair may not show over it", exe.c_str());
    WCHAR text[256];
    swprintf_s(text, L"%s may be in true fullscreen, which covers everything. Pick borderless or windowed "
                     L"in its video settings.", exe.c_str());
    Balloon(L"Can't see the crosshair?", text);
}

static void Balloon(PCWSTR title, PCWSTR text) {
    if (!g_trayAdded) return;
    NOTIFYICONDATAW nid{sizeof(nid)};
    nid.hWnd = g_msgWnd;
    nid.uID = kTrayId;
    nid.uFlags = NIF_INFO;
    nid.dwInfoFlags = NIIF_INFO;
    wcsncpy_s(nid.szInfoTitle, title, _TRUNCATE);
    wcsncpy_s(nid.szInfo, text, _TRUNCATE);
    Shell_NotifyIconW(NIM_MODIFY, &nid);
}

// ---------------------------------------------------------------------------
// Tray icon, menu and shortcuts
// ---------------------------------------------------------------------------

static void EnableDarkMenus() {
    HMODULE ux = GetModuleHandleW(L"uxtheme.dll");
    if (!ux) ux = LoadLibraryExW(L"uxtheme.dll", nullptr, LOAD_LIBRARY_SEARCH_SYSTEM32);
    if (!ux) return;
    using SetMode = int(WINAPI*)(int);
    using Flush = void(WINAPI*)();
    if (auto set = (SetMode)GetProcAddress(ux, MAKEINTRESOURCEA(135))) set(2 /* ForceDark */);
    if (auto flush = (Flush)GetProcAddress(ux, MAKEINTRESOURCEA(136))) flush();
}

// A rounded square in the blue to mauve gradient with the target glyph, drawn with GDI so the
// tray never shares the settings window's Direct2D factories. Grey while the crosshair is hidden.
static HICON MakeTrayIcon(bool off) {
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
    HFONT font = CreateFontW(-(int)(size * 0.66f), 0, 0, 0, FW_NORMAL, 0, 0, 0, DEFAULT_CHARSET, 0, 0,
                             ANTIALIASED_QUALITY, 0, L"Segoe Fluent Icons");
    HGDIOBJ oldFont = SelectObject(dc, font);
    SetBkMode(dc, TRANSPARENT);
    SetTextColor(dc, RGB(255, 255, 255));
    RECT r{0, 0, size, size};
    WCHAR g[2] = {(WCHAR)0xF272, 0};
    DrawTextW(dc, g, 1, &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE | DT_NOPREFIX);
    GdiFlush();
    SelectObject(dc, oldFont);
    DeleteObject(font);
    SelectObject(dc, old);
    DeleteDC(dc);

    const float c0[3] = {off ? 0x6C / 255.f : 0x89 / 255.f, off ? 0x70 / 255.f : 0xB4 / 255.f, off ? 0x86 / 255.f : 0xFA / 255.f};
    const float c1[3] = {off ? 0x58 / 255.f : 0xCB / 255.f, off ? 0x5B / 255.f : 0xA6 / 255.f, off ? 0x70 / 255.f : 0xF7 / 255.f};
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

static PCWSTR StyleLabel(const std::wstring& key) {
    for (const auto& s : kStyles)
        if (key == s.key) return s.label;
    return L"";
}

static void UpdateTray(bool add) {
    const Config& c = g_cfg;
    NOTIFYICONDATAW nid{sizeof(nid)};
    nid.hWnd = g_msgWnd;
    nid.uID = kTrayId;
    if (!c.trayIcon) {
        if (g_trayAdded) Shell_NotifyIconW(NIM_DELETE, &nid);
        g_trayAdded = false;
        return;
    }
    HICON icon = MakeTrayIcon(!g_shown);
    nid.uFlags = NIF_MESSAGE | NIF_ICON | NIF_TIP | NIF_SHOWTIP;
    nid.uCallbackMessage = WM_SGC_TRAY;
    nid.hIcon = icon ? icon : LoadIconW(nullptr, IDI_APPLICATION);
    std::wstring tip = std::wstring(L"Seamless Crosshair: ") + (g_shown ? L"on, " : L"hidden, ") + StyleLabel(c.style);
    if (!g_lookExe.empty()) tip += L" (" + g_lookExe + L"'s own look)";
    wcsncpy_s(nid.szTip, tip.c_str(), _TRUNCATE);
    if (!g_trayAdded || add) {
        if (g_trayAdded) Shell_NotifyIconW(NIM_DELETE, &nid);
        g_trayAdded = Shell_NotifyIconW(NIM_ADD, &nid) != FALSE;
        if (g_trayAdded) {
            nid.uVersion = NOTIFYICON_VERSION_4;
            Shell_NotifyIconW(NIM_SETVERSION, &nid);
        }
    } else {
        Shell_NotifyIconW(NIM_MODIFY, &nid);
    }
    if (g_trayIcon) DestroyIcon(g_trayIcon);
    g_trayIcon = icon;
}

static void RegisterHotkeys() {
    const Config& c = g_cfg;
    // Every shortcut press reloads the settings: leave the keys alone unless they changed.
    static std::wstring registered[HK_COUNT];
    static bool once;
    if (once && std::equal(c.hotkeys, c.hotkeys + HK_COUNT, registered)) return;
    once = true;
    std::copy(c.hotkeys, c.hotkeys + HK_COUNT, registered);
    for (int i = 0; i < HK_COUNT; i++) {
        if (g_hotkeyOn[i]) UnregisterHotKey(g_msgWnd, i + 1);
        g_hotkeyOn[i] = false;
        UINT mods, vk;
        if (c.hotkeys[i].empty()) continue;
        if (!Hotkey_Parse(c.hotkeys[i], mods, vk)) {
            Wh_Log(L"Shortcut \"%s\" isn't one the mod understands", c.hotkeys[i].c_str());
            continue;
        }
        g_hotkeyOn[i] = RegisterHotKey(g_msgWnd, i + 1, mods | (HotkeyRepeats(i) ? 0 : MOD_NOREPEAT), vk) != FALSE;
        if (!g_hotkeyOn[i]) Wh_Log(L"Shortcut %s is taken by another app (error %lu)", c.hotkeys[i].c_str(), GetLastError());
    }
}

static void SetDockAffinity(DWORD a);  // The pop-up; defined with it below.
static void DestroyDock();

static void ApplyConfig() {
    RegisterHotkeys();
    const DWORD affinity = g_cfg.excludeCapture ? 0x11 /* WDA_EXCLUDEFROMCAPTURE */ : WDA_NONE;
    if (g_overlay) SetWindowDisplayAffinity(g_overlay, affinity);
    SetDockAffinity(affinity);
    UpdateTimers();
    Refresh(true);
    UpdateTray(false);
}

// A change from a shortcut or the menu: shown at once, saved a moment later in one go.
static void Change(std::initializer_list<std::pair<PCWSTR, std::wstring>> kv) {
    bool lookOnly = !g_lookExe.empty();
    for (auto& [k, v] : kv)
        if (!IsLookKey(k)) lookOnly = false;
    if (lookOnly) {
        // The game in front has its own look: the change is that game's, the settings stay put.
        for (auto& [k, v] : kv) g_look[k] = v;
        WriteLook(g_lookExe, g_look);
        LoadSettings();
        ApplyConfig();
        return;
    }
    {
        std::lock_guard<std::mutex> lock(g_pendLock);
        for (auto& [k, v] : kv) g_pending[k] = v;
    }
    SetTimer(g_msgWnd, kTimerSave, 1200, nullptr);
    LoadSettings();
    ApplyConfig();
}

// ---------------------------------------------------------------------------
// The on and off pop-up: a small Mocha dock with Windows' own blur under it, the same look as
// Key Click's and Dictate's. It is a layered, click-through window that never takes focus, so it
// can sit over a game without catching a single click. It is drawn once per show; the slide and
// fade only move it and change its opacity.
// ---------------------------------------------------------------------------

struct SgcCompositorDesktopInterop : ::IUnknown {
    virtual HRESULT __stdcall CreateDesktopWindowTarget(HWND window, BOOL isTopmost, void** target) = 0;
    virtual HRESULT __stdcall EnsureOnThread(DWORD threadId) = 0;
};
template <>
inline constexpr winrt::guid winrt::impl::guid_v<SgcCompositorDesktopInterop>{
    0x29E691FA, 0x4567, 0x4DCA, {0xB3, 0x19, 0xD0, 0xF2, 0x07, 0xEB, 0x68, 0x07}};

struct SgcEffectD2D1Interop : ::IUnknown {
    virtual HRESULT __stdcall GetEffectId(GUID* id) = 0;
    virtual HRESULT __stdcall GetNamedPropertyMapping(LPCWSTR name, UINT* index, int* mapping) = 0;
    virtual HRESULT __stdcall GetPropertyCount(UINT* count) = 0;
    virtual HRESULT __stdcall GetProperty(UINT index, void** value) = 0;
    virtual HRESULT __stdcall GetSource(UINT index, void** source) = 0;
    virtual HRESULT __stdcall GetSourceCount(UINT* count) = 0;
};
template <>
inline constexpr winrt::guid winrt::impl::guid_v<SgcEffectD2D1Interop>{
    0x2FC57384, 0xA068, 0x44D7, {0xA3, 0x31, 0x30, 0x98, 0x2F, 0xCF, 0x71, 0x77}};

// A Gaussian blur over the host backdrop, so text behind the pop-up melts into colour.
struct SgcGlassBlur : winrt::implements<SgcGlassBlur, winrt::Windows::Graphics::Effects::IGraphicsEffect,
                                        winrt::Windows::Graphics::Effects::IGraphicsEffectSource,
                                        SgcEffectD2D1Interop> {
    SgcGlassBlur(float sigma, winrt::Windows::Graphics::Effects::IGraphicsEffectSource source)
        : m_sigma(sigma), m_source(std::move(source)) {}
    winrt::hstring Name() { return m_name; }
    void Name(winrt::hstring const& name) { m_name = name; }
    HRESULT __stdcall GetEffectId(GUID* id) override {
        *id = {0x1FEB6D69, 0x2FE6, 0x4AC9, {0x8C, 0x58, 0x1D, 0x7F, 0x93, 0xE7, 0xA6, 0xA5}};  // Gaussian blur
        return S_OK;
    }
    HRESULT __stdcall GetNamedPropertyMapping(LPCWSTR, UINT*, int*) override { return E_INVALIDARG; }
    HRESULT __stdcall GetPropertyCount(UINT* count) override {
        *count = 3;
        return S_OK;
    }
    HRESULT __stdcall GetProperty(UINT index, void** value) override {
        using winrt::Windows::Foundation::PropertyValue;
        winrt::Windows::Foundation::IInspectable v;
        switch (index) {
            case 0: v = PropertyValue::CreateSingle(m_sigma); break;
            case 1: v = PropertyValue::CreateUInt32(1 /* BALANCED */); break;
            case 2: v = PropertyValue::CreateUInt32(1 /* BORDER_MODE_HARD */); break;
            default: return E_INVALIDARG;
        }
        *value = winrt::detach_abi(v.as<winrt::Windows::Foundation::IPropertyValue>());
        return S_OK;
    }
    HRESULT __stdcall GetSource(UINT index, void** source) override {
        if (index != 0) return E_INVALIDARG;
        winrt::Windows::Graphics::Effects::IGraphicsEffectSource copy = m_source;
        *source = winrt::detach_abi(copy);
        return S_OK;
    }
    HRESULT __stdcall GetSourceCount(UINT* count) override {
        *count = 1;
        return S_OK;
    }

   private:
    winrt::hstring m_name = L"GlassBlur";
    float m_sigma;
    winrt::Windows::Graphics::Effects::IGraphicsEffectSource m_source;
};

namespace sgcdock {

constexpr WCHAR kGlassClass[] = L"SeamlessCrosshairGlass", kClass[] = L"SeamlessCrosshairPopup";

static bool GlassAvailable() {
    DWORD transparency = 1, size = sizeof(transparency);
    RegGetValueW(HKEY_CURRENT_USER, L"Software\\Microsoft\\Windows\\CurrentVersion\\Themes\\Personalize",
                 L"EnableTransparency", RRF_RT_REG_DWORD, nullptr, &transparency, &size);
    SYSTEM_POWER_STATUS power{};
    const bool saver = GetSystemPowerStatus(&power) && power.SystemStatusFlag == 1;
    return transparency != 0 && !saver;
}

static LRESULT CALLBACK GlassWndProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) {
    if (msg == WM_NCHITTEST) return HTTRANSPARENT;
    return DefWindowProcW(hwnd, msg, wp, lp);
}

class Glass {
   public:
    // The blur under the pop-up (pixels), with rounded corners of `radius` pixels.
    // False: Windows can't show it, and the pop-up paints itself solid.
    bool Show(HWND owner, int x, int y, int w, int h, float radius, float opacity) {
        if (m_failed) return false;
        try {
            if (!Ensure()) {
                m_failed = true;
                return false;
            }
            if (!m_visible || x != m_x || y != m_y || w != m_w || h != m_h || GetWindow(owner, GW_HWNDNEXT) != m_hwnd) {
                SetWindowPos(m_hwnd, owner, x, y, w, h, SWP_NOACTIVATE | SWP_SHOWWINDOW);
                m_x = x, m_y = y, m_w = w, m_h = h;
            }
            const winrt::Windows::Foundation::Numerics::float2 extent{(float)w, (float)h};
            m_visual.Size(extent);
            m_shape.Size(extent);
            const float r = std::clamp(radius, 0.0f, std::min(extent.x, extent.y) / 2);
            m_shape.CornerRadius({r, r});
            m_visual.Opacity(std::clamp(opacity, 0.0f, 1.0f));
            m_visible = true;
            return true;
        } catch (winrt::hresult_error const& e) {
            Wh_Log(L"Pop-up glass unavailable: %08X", (unsigned)e.code());
            m_failed = true;
            Hide();
            return false;
        }
    }
    void Hide() {
        if (m_hwnd && m_visible) ShowWindow(m_hwnd, SW_HIDE);
        m_visible = false;
    }
    void Affinity(DWORD a) {
        m_affinity = a;
        if (m_hwnd) SetWindowDisplayAffinity(m_hwnd, a);
    }
    // On the UI thread, before it ends.
    void Destroy() {
        m_visual = nullptr;
        m_shape = nullptr;
        m_target = nullptr;
        if (m_hwnd) DestroyWindow(m_hwnd);
        m_hwnd = nullptr;
        m_visible = false;
        m_compositor = nullptr;
        if (m_queue) {
            auto queue = std::move(m_queue);
            try {
                const auto shutdown = queue.ShutdownQueueAsync();
                for (int i = 0; i < 100 && shutdown.Status() == winrt::Windows::Foundation::AsyncStatus::Started; i++) {
                    MsgWaitForMultipleObjects(0, nullptr, FALSE, 10, QS_ALLINPUT);
                    MSG msg;
                    while (PeekMessageW(&msg, nullptr, 0, 0, PM_REMOVE)) DispatchMessageW(&msg);
                }
            } catch (winrt::hresult_error const& e) {
                Wh_Log(L"Ending the pop-up glass queue failed: %08X", (unsigned)e.code());
            }
        }
        if (m_registered) UnregisterClassW(kGlassClass, (HINSTANCE)windhawk_tool_mod::GetCurrentModuleHandle());
        m_registered = false;
        m_failed = false;
    }

   private:
    bool Ensure() {
        namespace Composition = winrt::Windows::UI::Composition;
        if (m_visual) return true;
        if (!m_queue) {
            using CreateController_t = HRESULT(WINAPI*)(DispatcherQueueOptions, void**);
            static const HMODULE messaging = LoadLibraryExW(L"CoreMessaging.dll", nullptr, LOAD_LIBRARY_SEARCH_SYSTEM32);
            const auto create =
                messaging ? (CreateController_t)(void*)GetProcAddress(messaging, "CreateDispatcherQueueController")
                          : nullptr;
            if (!create) return false;
            const DispatcherQueueOptions options{sizeof(options), DQTYPE_THREAD_CURRENT, DQTAT_COM_STA};
            winrt::check_hresult(create(options, winrt::put_abi(m_queue)));
        }
        if (!m_compositor) m_compositor = Composition::Compositor();
        const HINSTANCE inst = (HINSTANCE)windhawk_tool_mod::GetCurrentModuleHandle();
        if (!m_registered) {
            WNDCLASSW wc{};
            wc.lpfnWndProc = GlassWndProc;
            wc.hInstance = inst;
            wc.lpszClassName = kGlassClass;
            m_registered = RegisterClassW(&wc) != 0;
        }
        m_hwnd = CreateWindowExW(WS_EX_NOREDIRECTIONBITMAP | WS_EX_LAYERED | WS_EX_TRANSPARENT | WS_EX_TOPMOST |
                                     WS_EX_TOOLWINDOW | WS_EX_NOACTIVATE,
                                 kGlassClass, L"", WS_POPUP, 0, 0, 0, 0, nullptr, nullptr, inst, nullptr);
        if (!m_hwnd) return false;
        SetLayeredWindowAttributes(m_hwnd, 0, 255, LWA_ALPHA);
        SetWindowDisplayAffinity(m_hwnd, m_affinity);
        const BOOL hostBackdrop = TRUE;  // DWMWA_USE_HOSTBACKDROPBRUSH: a desktop app's window shows the blur only with this.
        winrt::check_hresult(DwmSetWindowAttribute(m_hwnd, 17, &hostBackdrop, sizeof(hostBackdrop)));
        auto interop = m_compositor.as<SgcCompositorDesktopInterop>();
        winrt::check_hresult(interop->CreateDesktopWindowTarget(m_hwnd, TRUE, winrt::put_abi(m_target)));
        const Composition::ContainerVisual root = m_compositor.CreateContainerVisual();
        root.RelativeSizeAdjustment({1, 1});
        m_target.Root(root);
        m_visual = m_compositor.CreateSpriteVisual();
        try {
            const auto effect =
                winrt::make<SgcGlassBlur>(18.0f, Composition::CompositionEffectSourceParameter(L"Backdrop"));
            const auto brush = m_compositor.CreateEffectFactory(effect).CreateBrush();
            brush.SetSourceParameter(L"Backdrop", m_compositor.CreateHostBackdropBrush());
            m_visual.Brush(brush);
        } catch (winrt::hresult_error const& e) {
            Wh_Log(L"Extra pop-up blur unavailable: %08X", (unsigned)e.code());
            m_visual.Brush(m_compositor.CreateHostBackdropBrush());
        }
        m_shape = m_compositor.CreateRoundedRectangleGeometry();
        m_visual.Clip(m_compositor.CreateGeometricClip(m_shape));
        root.Children().InsertAtTop(m_visual);
        return true;
    }

    HWND m_hwnd = nullptr;
    DWORD m_affinity = WDA_NONE;
    bool m_failed = false, m_visible = false, m_registered = false;
    int m_x = 0, m_y = 0, m_w = 0, m_h = 0;
    winrt::Windows::System::DispatcherQueueController m_queue{nullptr};
    winrt::Windows::UI::Composition::Compositor m_compositor{nullptr};
    winrt::Windows::UI::Composition::Desktop::DesktopWindowTarget m_target{nullptr};
    winrt::Windows::UI::Composition::SpriteVisual m_visual{nullptr};
    winrt::Windows::UI::Composition::CompositionRoundedRectangleGeometry m_shape{nullptr};
};

template <class T>
struct Com {
    T* p = nullptr;
    Com() = default;
    Com(const Com&) = delete;
    Com& operator=(const Com&) = delete;
    ~Com() { reset(); }
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

namespace col {
constexpr UINT32 crust = 0x11111B, base = 0x1E1E2E, surface1 = 0x45475A, overlay0 = 0x6C7086, overlay1 = 0x7F849C,
                 subtext0 = 0xA6ADC8, subtext1 = 0xBAC2DE, text = 0xCDD6F4, blue = 0x89B4FA, mauve = 0xCBA6F7;
}

constexpr UINT_PTR kAnimTimer = 1, kHideTimer = 2;
constexpr float kH = 60, kMinW = 250, kMaxW = 480, kSlide = 12;
constexpr DWORD kInMs = 170, kOutMs = 140;

enum class Phase { Hidden, In, Shown, Out };

struct Dock {
    HWND hwnd = nullptr;
    Com<ID2D1Factory> d2d;
    Com<IDWriteFactory> dw;
    Com<ID2D1DCRenderTarget> rt;
    Com<IDWriteTextFormat> fTitle, fDetail, fPill;
    HDC mem = nullptr;
    HBITMAP dib = nullptr;
    HGDIOBJ oldBmp = nullptr;
    int dibW = 0, dibH = 0;
    std::wstring title, detail;
    bool on = true, icon = true, animate = true;
    float tint = 0.85f, wDip = kMinW, scale = 1, ringRad = 16, edge = 2, fade = 1;
    int x = 0, y = 0, slideY = 0, pw = 0, ph = 0, duration = 1500;
    Phase phase = Phase::Hidden;
    DWORD phaseStart = 0;
    bool glass = true, glassOn = false;
    DWORD affinity = WDA_NONE;
};
static Dock g;
static Glass s_glass;

static UINT MonitorDpi(HMONITOR m) {
    using Fn = HRESULT(WINAPI*)(HMONITOR, int, UINT*, UINT*);
    static Fn fn = (Fn)(void*)GetProcAddress(LoadLibraryExW(L"shcore.dll", nullptr, LOAD_LIBRARY_SEARCH_SYSTEM32),
                                             "GetDpiForMonitor");
    UINT x = 0, y = 0;
    if (fn && SUCCEEDED(fn(m, 0 /* MDT_EFFECTIVE_DPI */, &x, &y)) && x) return x;
    UINT d = GetDpiForSystem();
    return d ? d : 96;
}

// The corner every window on this PC has (the corner radius mod's value), so the pop-up matches.
static float LiveRadius() {
    DWORD r = 0, size = sizeof(r);
    if (RegGetValueW(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Windhawk\\Engine\\Mods\\custom-corner-radius\\Settings", L"radius",
                     RRF_RT_REG_DWORD, nullptr, &r, &size) == ERROR_SUCCESS &&
        r >= 2 && r <= 40)
        return (float)r;
    return 8;
}

static float Ease(float t) {
    t = std::clamp(t, 0.0f, 1.0f);
    return 1 - (1 - t) * (1 - t) * (1 - t);
}

static D2D1_COLOR_F Color(UINT32 rgb, float a) {
    return D2D1::ColorF(((rgb >> 16) & 0xFF) / 255.0f, ((rgb >> 8) & 0xFF) / 255.0f, (rgb & 0xFF) / 255.0f, a);
}

static bool FamilyExists(const wchar_t* name) {
    Com<IDWriteFontCollection> sys;
    if (FAILED(g.dw->GetSystemFontCollection(sys.put(), FALSE))) return false;
    UINT32 index = 0;
    BOOL exists = FALSE;
    return SUCCEEDED(sys->FindFamilyName(name, &index, &exists)) && exists;
}

static void MakeFormat(Com<IDWriteTextFormat>& f, const wchar_t* family, float size, int weight, bool center) {
    if (FAILED(g.dw->CreateTextFormat(family, nullptr, (DWRITE_FONT_WEIGHT)weight, DWRITE_FONT_STYLE_NORMAL,
                                      DWRITE_FONT_STRETCH_NORMAL, size, L"en-us", f.put())))
        return;
    f->SetWordWrapping(DWRITE_WORD_WRAPPING_NO_WRAP);
    f->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
    f->SetTextAlignment(center ? DWRITE_TEXT_ALIGNMENT_CENTER : DWRITE_TEXT_ALIGNMENT_LEADING);
    Com<IDWriteInlineObject> sign;
    g.dw->CreateEllipsisTrimmingSign(f.get(), sign.put());
    DWRITE_TRIMMING t{DWRITE_TRIMMING_GRANULARITY_CHARACTER, 0, 0};
    f->SetTrimming(&t, sign.get());
}

static bool EnsureFactories() {
    if (!g.d2d && FAILED(D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, __uuidof(ID2D1Factory), nullptr,
                                           (void**)g.d2d.put())))
        return false;
    if (!g.dw && FAILED(DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory),
                                            (IUnknown**)g.dw.put())))
        return false;
    if (!g.fTitle) {
        // FiraCode Nerd Font, as everywhere else; Segoe UI only when it is missing.
        const wchar_t* family = L"Segoe UI";
        for (const wchar_t* f : {L"FiraCode Nerd Font", L"FiraCode Nerd Font Med", L"Fira Code"})
            if (FamilyExists(f)) {
                family = f;
                break;
            }
        MakeFormat(g.fTitle, family, 14.5f, 600, false);
        MakeFormat(g.fDetail, family, 12.5f, 500, false);
        MakeFormat(g.fPill, family, 12, 700, true);
    }
    return g.fTitle && g.fDetail && g.fPill;
}

static float TextW(IDWriteTextFormat* f, const std::wstring& s) {
    if (!f || s.empty()) return 0;
    Com<IDWriteTextLayout> layout;
    if (FAILED(g.dw->CreateTextLayout(s.c_str(), (UINT32)s.size(), f, 4000, 100, layout.put()))) return 0;
    DWRITE_TEXT_METRICS m{};
    layout->GetMetrics(&m);
    return m.widthIncludingTrailingWhitespace;
}

static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp);

static bool EnsureWindow() {
    if (g.hwnd) return true;
    WNDCLASSW wc{};
    wc.lpfnWndProc = WndProc;
    wc.hInstance = (HINSTANCE)windhawk_tool_mod::GetCurrentModuleHandle();
    wc.lpszClassName = kClass;
    wc.hCursor = LoadCursorW(nullptr, IDC_ARROW);
    RegisterClassW(&wc);
    g.hwnd = CreateWindowExW(WS_EX_LAYERED | WS_EX_TRANSPARENT | WS_EX_TOPMOST | WS_EX_TOOLWINDOW | WS_EX_NOACTIVATE,
                             kClass, L"Seamless Game Crosshair", WS_POPUP, 0, 0, 1, 1, nullptr, nullptr, wc.hInstance,
                             nullptr);
    if (g.hwnd) SetWindowDisplayAffinity(g.hwnd, g.affinity);
    return g.hwnd != nullptr;
}

static bool EnsureSurface() {
    if (!g.mem) g.mem = CreateCompatibleDC(nullptr);
    if (!g.mem) return false;
    if (g.dib && (g.dibW != g.pw || g.dibH != g.ph)) {
        SelectObject(g.mem, g.oldBmp);
        DeleteObject(g.dib);
        g.dib = nullptr;
    }
    if (!g.dib) {
        BITMAPINFO bi{};
        bi.bmiHeader.biSize = sizeof(bi.bmiHeader);
        bi.bmiHeader.biWidth = g.pw;
        bi.bmiHeader.biHeight = -g.ph;
        bi.bmiHeader.biPlanes = 1;
        bi.bmiHeader.biBitCount = 32;
        void* bits = nullptr;
        g.dib = CreateDIBSection(g.mem, &bi, DIB_RGB_COLORS, &bits, nullptr, 0);
        if (!g.dib) return false;
        g.oldBmp = SelectObject(g.mem, g.dib);
        g.dibW = g.pw, g.dibH = g.ph;
    }
    if (!g.rt) {
        D2D1_RENDER_TARGET_PROPERTIES props = D2D1::RenderTargetProperties(
            D2D1_RENDER_TARGET_TYPE_DEFAULT, D2D1::PixelFormat(DXGI_FORMAT_B8G8R8A8_UNORM, D2D1_ALPHA_MODE_PREMULTIPLIED));
        if (FAILED(g.d2d->CreateDCRenderTarget(&props, g.rt.put()))) return false;
        g.rt->SetTextAntialiasMode(D2D1_TEXT_ANTIALIAS_MODE_GRAYSCALE);  // ClearType needs an opaque surface.
    }
    RECT rc{0, 0, g.pw, g.ph};
    return SUCCEEDED(g.rt->BindDC(g.mem, &rc));
}

// Draws the pop-up once into its bitmap, at full strength: the fade is the window's opacity.
static bool Render() {
    if (!EnsureSurface()) return false;
    ID2D1DCRenderTarget* rt = g.rt.get();
    rt->SetDpi(96.0f * g.scale, 96.0f * g.scale);
    Com<ID2D1SolidColorBrush> sb;
    rt->BeginDraw();
    rt->SetTransform(D2D1::Matrix3x2F::Identity());
    rt->Clear(D2D1::ColorF(0, 0, 0, 0));
    if (FAILED(rt->CreateSolidColorBrush(Color(0, 0), sb.put()))) {
        rt->EndDraw();
        return false;
    }
    auto solid = [&](UINT32 c, float alpha) {
        sb->SetColor(Color(c, alpha));
        return sb.get();
    };
    auto grad = [&](const D2D1_RECT_F& r, float alpha, Com<ID2D1LinearGradientBrush>& out) {
        D2D1_GRADIENT_STOP stops[2] = {{0, Color(col::blue, alpha)}, {1, Color(col::mauve, alpha)}};
        Com<ID2D1GradientStopCollection> stopColl;
        if (SUCCEEDED(rt->CreateGradientStopCollection(stops, 2, stopColl.put())))
            rt->CreateLinearGradientBrush(
                D2D1::LinearGradientBrushProperties(D2D1::Point2F(r.left, (r.top + r.bottom) / 2),
                                                    D2D1::Point2F(std::max(r.right, r.left + 1), (r.top + r.bottom) / 2)),
                stopColl.get(), out.put());
        return out.get() != nullptr;
    };
    auto gradFill = [&](const D2D1_RECT_F& r, float rad, float alpha) {
        Com<ID2D1LinearGradientBrush> b;
        if (grad(r, alpha, b)) rt->FillRoundedRectangle(D2D1::RoundedRect(r, rad, rad), b.get());
    };
    auto gradRing = [&](const D2D1_RECT_F& r, float rad, float alpha, float width) {
        Com<ID2D1LinearGradientBrush> b;
        // Inset by half the width with the radius cut to match: the ring follows the shape's curve.
        D2D1_RECT_F in{r.left + width / 2, r.top + width / 2, r.right - width / 2, r.bottom - width / 2};
        const float inRad = std::max(0.0f, rad - width / 2);
        if (grad(r, alpha, b)) rt->DrawRoundedRectangle(D2D1::RoundedRect(in, inRad, inRad), b.get(), width);
    };
    auto text = [&](IDWriteTextFormat* f, const std::wstring& s, const D2D1_RECT_F& r, UINT32 c, float alpha) {
        if (!s.empty()) rt->DrawText(s.c_str(), (UINT32)s.size(), f, r, solid(c, alpha), D2D1_DRAW_TEXT_OPTIONS_CLIP);
    };

    const float W = g.wDip, H = kH;
    const D2D1_RECT_F all{0, 0, W, H};
    // The Mocha fill over the blur (all of it when solid), then the one gradient edge.
    rt->FillRoundedRectangle(D2D1::RoundedRect(all, g.ringRad, g.ringRad), solid(col::base, g.glassOn ? g.tint : 1.0f));
    gradFill(all, g.ringRad, 0.05f);
    gradRing(all, g.ringRad, 0.95f, g.edge);

    const bool off = !g.on;
    float tx = 18;
    if (g.icon) {
        // A small crosshair in a well: blue to mauve when on, grey when off.
        const D2D1_RECT_F well{14, H / 2 - 18, 50, H / 2 + 18};
        gradFill(well, 10, off ? 0.08f : 0.2f);
        gradRing(well, 10, off ? 0.45f : 0.85f, 1.25f);
        Com<ID2D1LinearGradientBrush> mark;
        ID2D1Brush* brush = solid(col::overlay1, 1);
        if (!off && grad(well, 1, mark)) brush = mark.get();
        const float cx = 32, cy = H / 2, gap = 3.5f, len = 6.5f, th = 2.25f;
        rt->FillRectangle({cx + gap, cy - th / 2, cx + gap + len, cy + th / 2}, brush);
        rt->FillRectangle({cx - gap - len, cy - th / 2, cx - gap, cy + th / 2}, brush);
        rt->FillRectangle({cx - th / 2, cy + gap, cx + th / 2, cy + gap + len}, brush);
        rt->FillRectangle({cx - th / 2, cy - gap - len, cx + th / 2, cy - gap}, brush);
        rt->FillEllipse(D2D1::Ellipse({cx, cy}, 1.6f, 1.6f), brush);
        tx = 62;
    }

    // The pill on the right: On or Off.
    const std::wstring pill = off ? L"Off" : L"On";
    const float pwid = TextW(g.fPill.get(), pill) + 24;
    const D2D1_RECT_F p{W - 16 - pwid, H / 2 - 12, W - 16, H / 2 + 12};
    if (off) {
        rt->FillRoundedRectangle(D2D1::RoundedRect(p, 12, 12), solid(col::surface1, 0.85f));
        D2D1_RECT_F in{p.left + 0.5f, p.top + 0.5f, p.right - 0.5f, p.bottom - 0.5f};
        rt->DrawRoundedRectangle(D2D1::RoundedRect(in, 11.5f, 11.5f), solid(col::overlay0, 0.6f), 1);
        text(g.fPill.get(), pill, p, col::subtext1, 1);
    } else {
        gradFill(p, 12, 1);
        text(g.fPill.get(), pill, p, col::crust, 1);
    }
    const float right = p.left - 12;

    // Title, then the detail line.
    const bool second = !g.detail.empty();
    text(g.fTitle.get(), g.title, second ? D2D1_RECT_F{tx, 9, right, 31} : D2D1_RECT_F{tx, 0, right, H}, col::text, 1);
    if (second) text(g.fDetail.get(), g.detail, {tx, 31, right, 51}, col::subtext0, 1);
    if (rt->EndDraw() == D2DERR_RECREATE_TARGET) {
        g.rt.reset();
        return false;
    }
    return true;
}

// Puts the drawn pop-up on screen, `off` of the way along its slide, at the current fade.
static void Place(float off) {
    const int x = g.x, y = g.y + (int)lroundf(g.slideY * off);
    HDC screen = GetDC(nullptr);
    POINT pos{x, y}, src{0, 0};
    SIZE size{g.pw, g.ph};
    BLENDFUNCTION bf{AC_SRC_OVER, 0, (BYTE)lroundf(std::clamp(g.fade, 0.0f, 1.0f) * 255), AC_SRC_ALPHA};
    UpdateLayeredWindow(g.hwnd, screen, &pos, &size, g.mem, &src, 0, &bf, ULW_ALPHA);
    ReleaseDC(nullptr, screen);
    if (g.glassOn) g.glassOn = s_glass.Show(g.hwnd, x, y, g.pw, g.ph, g.ringRad * g.scale, g.fade);
}

static void Hide() {
    if (!g.hwnd) return;
    KillTimer(g.hwnd, kAnimTimer);
    KillTimer(g.hwnd, kHideTimer);
    ShowWindow(g.hwnd, SW_HIDE);
    s_glass.Hide();
    g.phase = Phase::Hidden;
}

static void StartOut() {
    if (g.phase == Phase::Hidden || g.phase == Phase::Out) return;
    KillTimer(g.hwnd, kHideTimer);
    if (!g.animate) return Hide();
    g.phase = Phase::Out;
    g.phaseStart = GetTickCount();
    SetTimer(g.hwnd, kAnimTimer, 15, nullptr);
}

static void Tick() {
    float t = (GetTickCount() - g.phaseStart) / (float)(g.phase == Phase::In ? kInMs : kOutMs);
    if (g.phase == Phase::In) {
        g.fade = std::max(g.fade, Ease(t * 1.4f));
        Place(1 - Ease(t));
        if (t >= 1) {
            g.phase = Phase::Shown;
            KillTimer(g.hwnd, kAnimTimer);
        }
    } else if (g.phase == Phase::Out) {
        if (t >= 1) return Hide();
        g.fade = 1 - Ease(t);
        Place(Ease(t));
    } else {
        KillTimer(g.hwnd, kAnimTimer);
    }
}

static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) {
    switch (msg) {
        case WM_NCHITTEST: return HTTRANSPARENT;
        case WM_MOUSEACTIVATE: return MA_NOACTIVATE;
        case WM_TIMER:
            if (wp == kAnimTimer) Tick();
            else if (wp == kHideTimer) StartOut();
            return 0;
        case WM_DPICHANGED: return 0;  // Show sizes it for its monitor.
        case WM_DISPLAYCHANGE: Hide(); return 0;
    }
    return DefWindowProcW(hwnd, msg, wp, lp);
}

static HMONITOR TargetMonitor(const Config& c) {
    if (c.popupScreen == L"primary") return MonitorFromPoint({0, 0}, MONITOR_DEFAULTTOPRIMARY);
    if (c.popupScreen == L"crosshair" && g_targetMon) return g_targetMon;
    if (c.popupScreen == L"focused") {
        HWND fg = GetForegroundWindow();
        DWORD pid = 0;
        if (fg) GetWindowThreadProcessId(fg, &pid);
        // The tray menu makes this process the foreground; then the pointer's screen is the one.
        if (fg && pid != GetCurrentProcessId()) return MonitorFromWindow(fg, MONITOR_DEFAULTTOPRIMARY);
    }
    POINT pt{};
    GetCursorPos(&pt);
    return MonitorFromPoint(pt, MONITOR_DEFAULTTOPRIMARY);
}

static std::wstring ShortStyle(const Config& c) {
    std::wstring s = StyleLabel(c.style);
    size_t cut = s.find(L" (");
    return cut == std::wstring::npos ? s : s.substr(0, cut);
}

static void Show(bool on) {
    const Config& c = g_cfg;
    if (!c.popupInFullscreen) {
        QUERY_USER_NOTIFICATION_STATE st{};
        if (SUCCEEDED(SHQueryUserNotificationState(&st)) &&
            (st == QUNS_RUNNING_D3D_FULL_SCREEN || st == QUNS_PRESENTATION_MODE || st == QUNS_BUSY))
            return;
    }
    if (!EnsureWindow() || !EnsureFactories()) return;
    g.on = on;
    g.icon = c.popupIcon;
    g.animate = c.popupAnimate;
    g.duration = c.popupDuration;
    g.title = on ? L"Crosshair enabled" : L"Crosshair disabled";
    g.detail.clear();
    const std::wstring& key = c.hotkeys[HK_TOGGLE];
    if (c.popupDetail == L"shortcut" && !key.empty()) g.detail = key + (on ? L" hides it" : L" shows it");
    else if (c.popupDetail != L"none") g.detail = ShortStyle(c);

    // Width fits the words, within limits.
    const float textW = std::max(TextW(g.fTitle.get(), g.title), TextW(g.fDetail.get(), g.detail));
    const float pillW = TextW(g.fPill.get(), on ? L"On" : L"Off") + 24 + 12;
    g.wDip = std::clamp((g.icon ? 62 : 18) + textW + pillW + 18, kMinW, kMaxW);

    HMONITOR mon = TargetMonitor(c);
    MONITORINFO mi{sizeof(mi)};
    GetMonitorInfoW(mon, &mi);
    const RECT wa = mi.rcWork, full = mi.rcMonitor;
    const UINT dpi = MonitorDpi(mon);
    const float size = c.popupSize == L"compact" ? 0.88f : c.popupSize == L"large" ? 1.2f : 1.0f;
    g.scale = dpi / 96.0f * size;
    // The corner and the edge match every other window: the live radius and 2 px, whatever the size.
    g.ringRad = LiveRadius() / size;
    g.edge = 2.0f / size;
    g.tint = c.popupStrength / 100.0f;
    g.glass = c.popupGlass && GlassAvailable();
    g.pw = (int)lroundf(g.wDip * g.scale);
    g.ph = (int)lroundf(kH * g.scale);
    const float k = dpi / 96.0f;
    const int margin = (int)lroundf(c.popupMargin * k), slide = c.popupAnimate ? (int)lroundf(kSlide * k) : 0;
    const std::wstring& pos = c.popupPosition;
    int x, y;
    if (pos == L"belowCrosshair" || pos == L"aboveCrosshair") {
        const bool below = pos == L"belowCrosshair";
        x = g_target.x - g.pw / 2;
        y = below ? g_target.y + margin : g_target.y - margin - g.ph;
        g.slideY = below ? -slide : slide;  // It grows out of the crosshair.
    } else {
        const bool left = pos == L"topLeft" || pos == L"bottomLeft", right = pos == L"topRight" || pos == L"bottomRight";
        const bool top = pos.rfind(L"top", 0) == 0, middle = pos == L"center";
        x = left ? wa.left + margin : right ? wa.right - margin - g.pw : (wa.left + wa.right - g.pw) / 2;
        y = top ? wa.top + margin : middle ? (wa.top + wa.bottom - g.ph) / 2 : wa.bottom - margin - g.ph;
        g.slideY = top ? -slide : slide;
    }
    x += (int)lroundf(c.popupOffsetX * k);
    y += (int)lroundf(c.popupOffsetY * k);
    // Never off the screen, whatever the offsets say.
    g.x = std::clamp(x, (int)full.left, std::max((int)full.left, (int)full.right - g.pw));
    g.y = std::clamp(y, (int)full.top, std::max((int)full.top, (int)full.bottom - g.ph));

    // The glass decides the fill, so it goes in place (still invisible) before the drawing.
    const bool coming = g.phase == Phase::Hidden || g.phase == Phase::Out;
    if (coming) g.fade = g.phase == Phase::Hidden ? 0.0f : g.fade;
    if (!g.animate) g.fade = 1;
    g.glassOn = g.glass && s_glass.Show(g.hwnd, g.x, g.y, g.pw, g.ph, g.ringRad * g.scale, 0);
    if (!g.glass) s_glass.Hide();
    if (!Render() && !Render()) {  // A lost drawing surface is made again once.
        Hide();
        return;
    }
    KillTimer(g.hwnd, kHideTimer);
    ShowWindow(g.hwnd, SW_SHOWNOACTIVATE);
    SetWindowPos(g.hwnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
    if (g.animate && coming) {
        g.phase = Phase::In;
        g.phaseStart = GetTickCount();
        Place(1);
        SetTimer(g.hwnd, kAnimTimer, 15, nullptr);
    } else {
        KillTimer(g.hwnd, kAnimTimer);
        g.phase = Phase::Shown;
        g.fade = 1;
        Place(0);
    }
    SetTimer(g.hwnd, kHideTimer, (UINT)g.duration, nullptr);
}

static void SetAffinity(DWORD a) {
    g.affinity = a;
    if (g.hwnd) SetWindowDisplayAffinity(g.hwnd, a);
    s_glass.Affinity(a);
}

// On the UI thread, before it ends.
static void Destroy() {
    if (g.hwnd) {
        KillTimer(g.hwnd, kAnimTimer);
        KillTimer(g.hwnd, kHideTimer);
        DestroyWindow(g.hwnd);
        g.hwnd = nullptr;
    }
    s_glass.Destroy();
    g.rt.reset();
    g.fTitle.reset();
    g.fDetail.reset();
    g.fPill.reset();
    g.dw.reset();
    g.d2d.reset();
    if (g.mem) {
        if (g.dib) SelectObject(g.mem, g.oldBmp);
        DeleteDC(g.mem);
        g.mem = nullptr;
    }
    if (g.dib) DeleteObject(g.dib);
    g.dib = nullptr;
    g.dibW = g.dibH = 0;
    g.phase = Phase::Hidden;
    UnregisterClassW(kClass, (HINSTANCE)windhawk_tool_mod::GetCurrentModuleHandle());
}

}  // namespace sgcdock

static void SetDockAffinity(DWORD a) { sgcdock::SetAffinity(a); }
static void DestroyDock() { sgcdock::Destroy(); }

enum class ShowSource { Other, Shortcut, Tray };

static void SetShown(bool on, ShowSource from = ShowSource::Other) {
    g_shown = on;
    Wh_SetIntValue(L"shown", on ? 1 : 0);
    g_fadeNext = true;  // Showing or hiding on purpose is what the crosshair's fade is for.
    UpdateTimers();
    UpdateVisibility();
    UpdateTray(false);
    const Config& c = g_cfg;
    bool ask = (from == ShowSource::Shortcut && c.popupWhen != L"tray") ||
               (from == ShowSource::Tray && c.popupWhen != L"shortcut");
    if (c.popupOn && ask) sgcdock::Show(on);
}

static void StepStyle(int dir) {
    const Config& c = g_cfg;
    int n = (int)ARRAYSIZE(kStyles), at = 0;
    for (int i = 0; i < n; i++)
        if (c.style == kStyles[i].key) at = i;
    for (int step = 1; step <= n; step++) {
        int i = ((at + dir * step) % n + n) % n;
        if (!wcscmp(kStyles[i].key, L"image") && c.imagePath.empty()) continue;
        Change({{L"style", kStyles[i].key}});
        return;
    }
}

static void NextColor() {
    const Config& c = g_cfg;
    size_t at = c.colorCycle.size() - 1;
    for (size_t i = 0; i < c.colorCycle.size(); i++)
        if (c.colorCycle[i] == c.color) at = i;
    Change({{L"color", HexOf(c.colorCycle[(at + 1) % c.colorCycle.size()])}});
}

static void SetScale(int s) { Change({{L"scale", std::to_wstring(Clamp(s, 50, 400))}}); }

static void Nudge(int dx, int dy) {
    const Config& c = g_cfg;
    Change({{L"offsetX", std::to_wstring(Clamp(c.offsetX + dx * c.nudge, -2000, 2000))},
            {L"offsetY", std::to_wstring(Clamp(c.offsetY + dy * c.nudge, -2000, 2000))}});
}

// A short blink, so a shortcut that changes nothing on screen still shows it worked.
static void Blink() {
    if (!g_visible) return;
    KillTimer(g_msgWnd, kTimerFade);
    g_fadeDir = 0;
    g_fadeP = 0;
    ShowWindow(g_overlay, SW_HIDE);
    g_visible = false;
    SetTimer(g_msgWnd, kTimerBlink, 200, nullptr);
}

// Saves the crosshair as it is now for the last app in front, or forgets that app's look.
static void ToggleLook() {
    Wh_Log(L"Look key: last app [%s], look in use [%s]", g_lastApp.c_str(), g_lookExe.c_str());
    if (g_lastApp.empty()) return;
    if (g_lookExe == g_lastApp) {
        Wh_DeleteValue((L"look:" + g_lastApp).c_str());
        g_lookExe.clear();
        g_look.clear();
    } else {
        std::map<std::wstring, std::wstring> look;
        for (PCWSTR k : kLookKeys) look[k] = IsLookText(k) ? SettingStr(k) : std::to_wstring(SettingInt(k));
        WriteLook(g_lastApp, look);
        g_lookExe = g_lastApp;
        g_look = look;
    }
    LoadSettings();
    ApplyConfig();
    Blink();
}

static void OpenSettings() {
    sgcset::OpenSettingsWindow();
    g_watchSettings = true;
    g_watchSince = GetTickCount();
    UpdateTimers();
}

enum : UINT {
    IDM_SHOW = 100, IDM_CENTER, IDM_SETTINGS, IDM_LOOK,
    IDM_STYLE = 1000, IDM_COLOR = 2000, IDM_SIZE = 3000,
};
static const int kSizes[] = {50, 75, 100, 125, 150, 200, 300, 400};

static void ShowTrayMenu(POINT pt);  // Defined with the settings engine below; runs on its menu renderer.

static void OnHotkey(int which) {
    switch (which) {
        case HK_TOGGLE: SetShown(!g_shown, ShowSource::Shortcut); break;
        case HK_NEXT: StepStyle(1); break;
        case HK_PREV: StepStyle(-1); break;
        case HK_COLOR: NextColor(); break;
        case HK_BIGGER: SetScale(g_cfg.scale + 10); break;
        case HK_SMALLER: SetScale(g_cfg.scale - 10); break;
        case HK_UP: Nudge(0, -1); break;
        case HK_DOWN: Nudge(0, 1); break;
        case HK_LEFT: Nudge(-1, 0); break;
        case HK_RIGHT: Nudge(1, 0); break;
        case HK_CENTER: Change({{L"offsetX", L"0"}, {L"offsetY", L"0"}}); break;
        case HK_SETTINGS: OpenSettings(); break;
        case HK_LOOK: ToggleLook(); break;
    }
}

static LRESULT CALLBACK MsgWndProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) {
    if (msg == g_taskbarCreated && g_taskbarCreated) {
        g_trayAdded = false;
        UpdateTray(true);
        return 0;
    }
    switch (msg) {
        case WM_HOTKEY:
            if (wp >= 1 && wp <= HK_COUNT) OnHotkey((int)wp - 1);
            return 0;
        case WM_TIMER:
            if (wp == kTimerAim) PollAim();
            else if (wp == kTimerTopmost) KeepOnTop();
            else if (wp == kTimerBlink) {
                KillTimer(hwnd, kTimerBlink);
                g_fadeSkip = true;
                UpdateVisibility();
            } else if (wp == kTimerFade) {
                FadeTick();
            } else if (wp == kTimerFullscreen) {
                KillTimer(hwnd, kTimerFullscreen);
                CheckTrueFullscreen();
            }
            else if (wp == kTimerSave) {
                KillTimer(hwnd, kTimerSave);
                SavePendingAsync();
            } else if (wp == kTimerTrack) {
                if (g_watchSettings && !SettingsOpen() && GetTickCount() - g_watchSince > 5000) {
                    g_watchSettings = false;
                    UpdateTimers();
                }
                Refresh(false);
            }
            return 0;
        case WM_DISPLAYCHANGE:
        case WM_SETTINGCHANGE:
            Refresh(false);
            return 0;
        case WM_SGC_TRAY:
            switch (LOWORD(lp)) {
                case NIN_SELECT:
                case NIN_KEYSELECT: OpenSettings(); break;
                case WM_CONTEXTMENU: ShowTrayMenu(POINT{GET_X_LPARAM(wp), GET_Y_LPARAM(wp)}); break;
            }
            return 0;
        case WM_SGC_SETTINGS:
            if (g_saveRoute == SaveRoute::None) {
                // This mod never saves on its own then, so this is the owner's save: it wins.
                std::lock_guard<std::mutex> lock(g_pendLock);
                g_pending.clear();
            }
            LoadSettings();
            ApplyConfig();
            if (HWND s = sgcset::g_settingsWnd) PostMessageW(s, WM_APP + 1 /* WM_APP_SETTINGS_RELOAD */, 0, 0);
            return 0;
    }
    return DefWindowProcW(hwnd, msg, wp, lp);
}

static LRESULT CALLBACK OverlayProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) {
    switch (msg) {
        case WM_NCHITTEST: return HTTRANSPARENT;
        case WM_MOUSEACTIVATE: return MA_NOACTIVATE;
    }
    return DefWindowProcW(hwnd, msg, wp, lp);
}

static DWORD WINAPI UiThread(LPVOID) {
    MSG msg;
    PeekMessageW(&msg, nullptr, WM_USER, WM_USER, PM_NOREMOVE);
    // Physical pixels everywhere, so the crosshair lands on the exact middle at any scaling.
    SetThreadDpiAwarenessContext(DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2);
    HRESULT com = CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED);
    EnableDarkMenus();
    HINSTANCE inst = (HINSTANCE)windhawk_tool_mod::GetCurrentModuleHandle();
    WNDCLASSW wc{};
    wc.lpfnWndProc = MsgWndProc;
    wc.hInstance = inst;
    wc.lpszClassName = L"SeamlessCrosshairMsg";
    RegisterClassW(&wc);
    WNDCLASSW oc{};
    oc.lpfnWndProc = OverlayProc;
    oc.hInstance = inst;
    oc.hCursor = LoadCursorW(nullptr, IDC_ARROW);
    oc.lpszClassName = L"SeamlessCrosshairOverlay";
    RegisterClassW(&oc);
    g_msgWnd = CreateWindowExW(WS_EX_TOOLWINDOW, wc.lpszClassName, L"Seamless Game Crosshair", WS_POPUP, 0, 0, 0, 0,
                               nullptr, nullptr, inst, nullptr);
    g_overlay = CreateWindowExW(WS_EX_LAYERED | WS_EX_TRANSPARENT | WS_EX_TOPMOST | WS_EX_TOOLWINDOW | WS_EX_NOACTIVATE,
                                oc.lpszClassName, L"Seamless Game Crosshair", WS_POPUP, 0, 0, 1, 1, nullptr, nullptr,
                                inst, nullptr);
    if (g_msgWnd && g_overlay) {
        g_taskbarCreated = RegisterWindowMessageW(L"TaskbarCreated");
        ChangeWindowMessageFilterEx(g_msgWnd, g_taskbarCreated, MSGFLT_ALLOW, nullptr);
        g_fgHook = SetWinEventHook(EVENT_SYSTEM_FOREGROUND, EVENT_SYSTEM_FOREGROUND, nullptr, ForegroundProc, 0, 0,
                                   WINEVENT_OUTOFCONTEXT | WINEVENT_SKIPOWNPROCESS);
        UpdateLook();
        LoadSettings();
        ApplyConfig();
        UpdateTray(true);
    }
    SetEvent(g_uiReady);
    if (g_msgWnd && g_overlay)
        while (GetMessageW(&msg, nullptr, 0, 0) > 0) {
            TranslateMessage(&msg);
            DispatchMessageW(&msg);
        }
    if (g_fgHook) UnhookWinEvent(g_fgHook);
    g_fgHook = nullptr;
    if (g_msgWnd) {
        for (UINT_PTR t : {kTimerTrack, kTimerAim, kTimerTopmost, kTimerBlink, kTimerFullscreen, kTimerFade})
            KillTimer(g_msgWnd, t);
        if (KillTimer(g_msgWnd, kTimerSave)) SavePendingAsync();  // A change still waiting to be saved.
        for (int i = 0; i < HK_COUNT; i++)
            if (g_hotkeyOn[i]) UnregisterHotKey(g_msgWnd, i + 1);
        if (g_trayAdded) {
            NOTIFYICONDATAW nid{sizeof(nid)};
            nid.hWnd = g_msgWnd;
            nid.uID = kTrayId;
            Shell_NotifyIconW(NIM_DELETE, &nid);
            g_trayAdded = false;
        }
    }
    if (g_trayIcon) DestroyIcon(g_trayIcon);
    g_trayIcon = nullptr;
    DestroyDock();
    if (g_overlay) DestroyWindow(g_overlay);
    if (g_msgWnd) DestroyWindow(g_msgWnd);
    g_overlay = g_msgWnd = nullptr;
    UnregisterClassW(wc.lpszClassName, inst);
    UnregisterClassW(oc.lpszClassName, inst);
    if (SUCCEEDED(com)) CoUninitialize();
    return 0;
}

// ---------------------------------------------------------------------------
// Start and stop
// ---------------------------------------------------------------------------

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
constexpr INT kRowMargin = 6;                  // row top and bottom margin of the menu look
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

// Picks the largest row margin (6 down to 2) at which the whole menu fits its monitor.
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
        INT cut = px(2 * (kRowMargin - pick));   // rows measure 29 px and separators 17 px at margin 6
        if (rows * (px(29) - cut) + seps * (px(17) - cut) + px(10) <= avail) break;
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

static HANDLE g_singleInstance;

BOOL WhTool_ModInit() {
    g_singleInstance = CreateMutexW(nullptr, FALSE, L"Local\\SeamlessCrosshairRunning");
    if (!g_singleInstance || GetLastError() == ERROR_ALREADY_EXISTS) {
        if (g_singleInstance) CloseHandle(g_singleInstance);
        g_singleInstance = nullptr;
        Wh_Log(L"Already running");
        return FALSE;
    }
    // Same menu look as Launchpad's. Hooks are applied when init returns, so this runs here.
    SeamlessMenuSkin::Init();
    g_shown = Wh_GetIntValue(L"shown", 1) != 0;
    g_saveRoute = PickSaveRoute();
    Wh_Log(L"Save route: %d", (int)g_saveRoute);
    g_uiReady = CreateEventW(nullptr, TRUE, FALSE, nullptr);
    g_uiThread = CreateThread(nullptr, 0, UiThread, nullptr, 0, &g_uiTid);
    if (g_uiThread) WaitForSingleObject(g_uiReady, 10000);
    CloseHandle(g_uiReady);
    g_uiReady = nullptr;
    if (!g_uiThread || !g_msgWnd) {
        Wh_Log(L"Couldn't start");
        WhTool_ModUninit();
        return FALSE;
    }
    return TRUE;
}

void WhTool_ModSettingsChanged() {
    if (g_msgWnd) PostMessageW(g_msgWnd, WM_SGC_SETTINGS, 0, 0);
}

void WhTool_ModUninit() {
    sgcset::CloseSettingsWindow();
    if (g_uiThread) {
        PostThreadMessageW(g_uiTid, WM_QUIT, 0, 0);
        if (WaitForSingleObject(g_uiThread, 15000) != WAIT_OBJECT_0) Wh_Log(L"UI thread did not stop in 15 s");
        CloseHandle(g_uiThread);
        g_uiThread = nullptr;
    }
    for (int i = 0; i < 150 && g_saveThreads > 0; i++) Sleep(100);
    SeamlessMenuSkin::Uninit();
    if (g_singleInstance) CloseHandle(g_singleInstance);
    g_singleInstance = nullptr;
}

// ===========================================================================
// Settings window: the Seamless Launchpad settings GUI, the standard for every
// DavidHiFi mod. Generated by work\2026-11-12-seamless-crosshair\gen.py.
// ===========================================================================
extern "C" IMAGE_DOS_HEADER __ImageBase;
namespace sgcset {
// The settings window, from the tray icon. It shows the same settings as
// Windhawk's page for this mod and saves them through windhawk-cli, so the two
// stay in step. Writing a mod's settings takes admin rights, so the save runs
// the CLI elevated (silently where UAC prompts are off).

constexpr WCHAR kSettingsClass[] = L"WindhawkSeamlessCrosshairSettings";
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
// Generated by work\2026-11-12-seamless-crosshair\gen.py from spec.py.
static std::vector<SetField> Set_MakeFields() {
    using K = SetField;
    return {
{K::Choice, L"style", L"Style", L"The crosshair to draw. Pick \"Your own design\" to build one on the Shape page.", L"crossDot", {{L"crossDot", L"Cross with a dot"}, {L"cross", L"Cross"}, {L"smallCross", L"Small cross"}, {L"dot", L"Dot"}, {L"tShape", L"T shape"}, {L"xShape", L"X"}, {L"circleDot", L"Circle with a dot"}, {L"circle", L"Circle"}, {L"tactical", L"Cross in a ring"}, {L"chevron", L"Chevron"}, {L"custom", L"Your own design (Shape page)"}, {L"image", L"An image file (below)"}}, 0, 100, 0, L"Crosshair"},
{K::Color, L"color", L"Color", L"In hexadecimal, like #00FF00. Bright green, cyan, yellow and magenta stand out in most games.", L"#00FF00", {}, 0, 100, 0, L"Crosshair"},
{K::Number, L"opacity", L"Opacity (%)", L"10 to 100 (Suggested: 100). Lower lets the game show through.", L"100", {}, 10, 100, 0, L"Crosshair"},
{K::Number, L"scale", L"Size (%)", L"50 to 400 (Suggested: 100). Makes the whole crosshair bigger or smaller.", L"100", {}, 50, 400, 0, L"Crosshair"},
{K::Check, L"followScaling", L"Follow display scaling", L"On, the crosshair grows with your Windows display scaling. Off, sizes are real screen pixels, the way games draw their own.", L"0", {}, 0, 100, 0, L"Crosshair"},
{K::Check, L"outline", L"Outline", L"A dark edge around every line, so the crosshair stays visible on bright and dark scenes alike.", L"1", {}, 0, 100, 0, L"Outline"},
{K::Number, L"outlineThickness", L"Outline thickness", L"1 to 4 (Suggested: 1). Pixels.", L"1", {}, 1, 4, 0, L"Outline"},
{K::Color, L"outlineColor", L"Outline color", L"In hexadecimal, like #000000.", L"#000000", {}, 0, 100, 0, L"Outline"},
{K::Number, L"outlineOpacity", L"Outline opacity (%)", L"0 to 100 (Suggested: 80).", L"80", {}, 0, 100, 0, L"Outline"},
{K::Text, L"imagePath", L"Image file", L"Used when the style is \"An image file\". The full path of a PNG (transparency works), BMP, JPG or GIF.", L"", {}, 0, 100, 0, L"Image"},
{K::Number, L"imageSize", L"Image size", L"8 to 512 (Suggested: 32). Pixels across. The image keeps its shape.", L"32", {}, 8, 512, 0, L"Image"},
{K::Check, L"imageRecolor", L"Paint the image in the color above", L"Keeps the image's shape and transparency, but fills it with the crosshair color.", L"0", {}, 0, 100, 0, L"Image"},
{K::Check, L"dotOn", L"Center dot", L"", L"1", {}, 0, 100, 1, L"Center dot"},
{K::Number, L"dotSize", L"Dot size", L"1 to 20 (Suggested: 2). Pixels.", L"2", {}, 1, 20, 1, L"Center dot"},
{K::Check, L"dotRound", L"Round dot", L"Off, the dot is a sharp square.", L"0", {}, 0, 100, 1, L"Center dot"},
{K::Number, L"dotOpacity", L"Dot opacity (%)", L"10 to 100 (Suggested: 100).", L"100", {}, 10, 100, 1, L"Center dot"},
{K::Check, L"innerOn", L"Inner lines", L"The four lines around the center.", L"1", {}, 0, 100, 1, L"Inner lines"},
{K::Number, L"innerLength", L"Length", L"0 to 60 (Suggested: 6). Pixels.", L"6", {}, 0, 60, 1, L"Inner lines"},
{K::Number, L"innerThickness", L"Thickness", L"1 to 20 (Suggested: 2). Pixels.", L"2", {}, 1, 20, 1, L"Inner lines"},
{K::Number, L"innerGap", L"Gap", L"0 to 60 (Suggested: 3). Space between the center and each line.", L"3", {}, 0, 60, 1, L"Inner lines"},
{K::Number, L"innerOpacity", L"Opacity (%)", L"10 to 100 (Suggested: 100).", L"100", {}, 10, 100, 1, L"Inner lines"},
{K::Check, L"outerOn", L"Outer lines", L"A second set of lines further out.", L"0", {}, 0, 100, 1, L"Outer lines"},
{K::Number, L"outerLength", L"Length", L"0 to 60 (Suggested: 2). Pixels.", L"2", {}, 0, 60, 1, L"Outer lines"},
{K::Number, L"outerThickness", L"Thickness", L"1 to 20 (Suggested: 2). Pixels.", L"2", {}, 1, 20, 1, L"Outer lines"},
{K::Number, L"outerGap", L"Gap", L"0 to 100 (Suggested: 10). Space between the center and each line.", L"10", {}, 0, 100, 1, L"Outer lines"},
{K::Number, L"outerOpacity", L"Opacity (%)", L"10 to 100 (Suggested: 50).", L"50", {}, 10, 100, 1, L"Outer lines"},
{K::Check, L"circleOn", L"Ring", L"A circle around the center.", L"0", {}, 0, 100, 1, L"Ring"},
{K::Number, L"circleRadius", L"Radius", L"2 to 100 (Suggested: 10). Pixels.", L"10", {}, 2, 100, 1, L"Ring"},
{K::Number, L"circleThickness", L"Thickness", L"1 to 20 (Suggested: 1). Pixels.", L"1", {}, 1, 20, 1, L"Ring"},
{K::Number, L"circleOpacity", L"Opacity (%)", L"10 to 100 (Suggested: 100).", L"100", {}, 10, 100, 1, L"Ring"},
{K::Check, L"tStyle", L"T shape", L"Leaves out the top lines.", L"0", {}, 0, 100, 1, L"Lines"},
{K::Number, L"rotation", L"Rotation (degrees)", L"0 to 359 (Suggested: 0). 45 turns a cross into an X.", L"0", {}, 0, 359, 1, L"Lines"},
{K::Check, L"smoothEdges", L"Smooth edges", L"Off, straight lines are pixel sharp. On, their edges are softened. Circles and turned lines are always smooth.", L"0", {}, 0, 100, 1, L"Lines"},
{K::Choice, L"centerOn", L"Center on", L"Pick the game window if your game runs in a window that is not centered on the screen.", L"primary", {{L"primary", L"The main screen"}, {L"monitor", L"The screen picked below"}, {L"window", L"The window in front (your game)"}}, 0, 100, 2, L"Position"},
{K::Number, L"monitorNumber", L"Screen", L"1 to 8 (Suggested: 1). Screens are counted left to right. Used when \"Center on\" is the picked screen.", L"1", {}, 1, 8, 2, L"Position"},
{K::Number, L"offsetX", L"Move right", L"-2000 to 2000 (Suggested: 0). Pixels from the center. Less than 0 moves it left.", L"0", {}, -2000, 2000, 2, L"Position"},
{K::Number, L"offsetY", L"Move down", L"-2000 to 2000 (Suggested: 0). Pixels from the center. Less than 0 moves it up.", L"0", {}, -2000, 2000, 2, L"Position"},
{K::Number, L"nudgeStep", L"Move step", L"1 to 50 (Suggested: 1). Pixels per press of a move shortcut.", L"1", {}, 1, 50, 2, L"Position"},
{K::Choice, L"showMode", L"Show", L"The crosshair always shows while the settings window is open, so you can see your changes. Games in true fullscreen cover everything, so set them to borderless or windowed.", L"always", {{L"always", L"Always"}, {L"apps", L"Only while one of the games below is in front"}, {L"fullscreen", L"Only while a fullscreen app is in front"}}, 0, 100, 3, L"Apps"},
{K::Text, L"games", L"Games", L"Program names split with \";\", such as cs2.exe; VALORANT-Win64-Shipping.exe. * and ? work as wildcards.", L"", {}, 0, 100, 3, L"Apps"},
{K::Text, L"neverApps", L"Never in", L"Apps the crosshair always hides in, such as explorer.exe; chrome.exe.", L"", {}, 0, 100, 3, L"Apps"},
{K::Choice, L"aimButton", L"Aim button", L"The button you aim with, for games that show their own scope or sights when you aim.", L"none", {{L"none", L"None (aiming changes nothing)"}, {L"right", L"Right mouse button"}, {L"middle", L"Middle mouse button"}, {L"x1", L"Back side button"}, {L"x2", L"Forward side button"}, {L"key", L"The key below"}}, 0, 100, 3, L"While aiming"},
{K::Hotkey, L"aimKey", L"Aim key", L"Used when the aim button is \"The key below\".", L"", {}, 0, 100, 3, L"While aiming"},
{K::Choice, L"aimAction", L"While aiming", L"", L"hide", {{L"hide", L"Hide the crosshair"}, {L"show", L"Show the crosshair only while aiming"}}, 0, 100, 3, L"While aiming"},
{K::Choice, L"aimMode", L"How aiming works", L"", L"hold", {{L"hold", L"While the button is held"}, {L"toggle", L"Each press starts or stops aiming"}}, 0, 100, 3, L"While aiming"},
{K::Check, L"excludeFromCapture", L"Hide from recordings", L"On, screenshots, recordings and streams don't show the crosshair. Only you see it.", L"0", {}, 0, 100, 3, L"Other"},
{K::Hotkey, L"toggleHotkey", L"Show or hide the crosshair", L"Press the keys in the box. Backspace clears it.", L"Ctrl+Alt+X", {}, 0, 100, 4, L"Shortcuts"},
{K::Hotkey, L"nextStyleHotkey", L"Next style", L"", L"Ctrl+Alt+Z", {}, 0, 100, 4, L"Shortcuts"},
{K::Hotkey, L"prevStyleHotkey", L"Previous style", L"", L"", {}, 0, 100, 4, L"Shortcuts"},
{K::Hotkey, L"nextColorHotkey", L"Next color", L"Walks the colors listed below.", L"", {}, 0, 100, 4, L"Shortcuts"},
{K::Hotkey, L"sizeUpHotkey", L"Bigger", L"", L"", {}, 0, 100, 4, L"Shortcuts"},
{K::Hotkey, L"sizeDownHotkey", L"Smaller", L"", L"", {}, 0, 100, 4, L"Shortcuts"},
{K::Hotkey, L"moveUpHotkey", L"Move up", L"Hold a move key to keep moving.", L"", {}, 0, 100, 4, L"Shortcuts"},
{K::Hotkey, L"moveDownHotkey", L"Move down", L"", L"", {}, 0, 100, 4, L"Shortcuts"},
{K::Hotkey, L"moveLeftHotkey", L"Move left", L"", L"", {}, 0, 100, 4, L"Shortcuts"},
{K::Hotkey, L"moveRightHotkey", L"Move right", L"", L"", {}, 0, 100, 4, L"Shortcuts"},
{K::Hotkey, L"recenterHotkey", L"Back to the center", L"Undoes every move.", L"", {}, 0, 100, 4, L"Shortcuts"},
{K::Hotkey, L"settingsHotkey", L"Open settings", L"", L"", {}, 0, 100, 4, L"Shortcuts"},
{K::Hotkey, L"lookHotkey", L"Keep this look for the game in front", L"The game gets the crosshair as it is now, every time it comes to the front. Shortcuts pressed in that game then change only its look. Press again to give it the normal look back. The tray menu does the same.", L"", {}, 0, 100, 4, L"Shortcuts"},
{K::Text, L"colorCycle", L"Colors for \"Next color\"", L"Hexadecimal colors split with \";\". They also fill the tray menu's Color list.", L"#00FF00; #00FFFF; #FFFF00; #FF00FF; #FFFFFF; #FF0000", {}, 0, 100, 4, L"Shortcuts"},
{K::Check, L"settingsGlass", L"Blurred settings window", L"On, the settings window is see-through glass with Windows acrylic behind it. Off, it is solid. Applies when you save.", L"1", {}, 0, 100, 6, L"Settings window"},
{K::Check, L"nativeSettingsTitleBar", L"Native Windows title bar", L"Use the Windows title bar and window buttons for this settings window. Applies when you save.", L"0", {}, 0, 100, 6, L"Settings window"},
{K::Check, L"settingsTrayIcon", L"Tray icon", L"Click it to open these settings. Right-click it to show or hide the crosshair, or pick a style, color or size. When off, change settings in Windhawk.", L"1", {}, 0, 100, 6, L"Settings window"},
{K::Check, L"popupOn", L"On and off pop-up", L"A small dock says \"Crosshair enabled\" or \"Crosshair disabled\" each time you switch it.", L"1", {}, 0, 100, 5, L"Pop-up"},
{K::Choice, L"popupWhen", L"Show it for", L"", L"both", {{L"both", L"The shortcut and the tray menu"}, {L"shortcut", L"Only the shortcut"}, {L"tray", L"Only the tray menu"}}, 0, 100, 5, L"Pop-up"},
{K::Choice, L"popupDetail", L"Second line", L"The smaller line under \"Crosshair enabled\".", L"style", {{L"style", L"The crosshair style"}, {L"shortcut", L"The shortcut that switches it"}, {L"none", L"Nothing"}}, 0, 100, 5, L"Pop-up"},
{K::Check, L"popupIcon", L"Crosshair icon", L"The crosshair mark on the left of the pop-up.", L"1", {}, 0, 100, 5, L"Pop-up"},
{K::Number, L"popupDuration", L"How long it stays (milliseconds)", L"500 to 10000 (Suggested: 1500). 1000 is one second.", L"1500", {}, 500, 10000, 5, L"Pop-up"},
{K::Check, L"popupInFullscreen", L"Show over fullscreen games", L"Off, the pop-up stays away while a game or video fills the screen.", L"1", {}, 0, 100, 5, L"Pop-up"},
{K::Choice, L"popupPosition", L"Where", L"", L"bottom", {{L"top", L"Top middle"}, {L"topLeft", L"Top left"}, {L"topRight", L"Top right"}, {L"center", L"Middle of the screen"}, {L"bottom", L"Bottom middle"}, {L"bottomLeft", L"Bottom left"}, {L"bottomRight", L"Bottom right"}, {L"belowCrosshair", L"Just below the crosshair"}, {L"aboveCrosshair", L"Just above the crosshair"}}, 0, 100, 5, L"Place"},
{K::Choice, L"popupScreen", L"Screen", L"", L"crosshair", {{L"crosshair", L"The screen the crosshair is on"}, {L"primary", L"The main screen"}, {L"pointer", L"The screen with the mouse pointer"}, {L"focused", L"The screen of the window in front"}}, 0, 100, 5, L"Place"},
{K::Number, L"popupMargin", L"Distance from the edge", L"0 to 600 (Suggested: 48). Pixels from the screen edge, or from the crosshair when it sits next to it.", L"48", {}, 0, 600, 5, L"Place"},
{K::Number, L"popupOffsetX", L"Move right", L"-2000 to 2000 (Suggested: 0). Pixels. Less than 0 moves it left.", L"0", {}, -2000, 2000, 5, L"Place"},
{K::Number, L"popupOffsetY", L"Move down", L"-2000 to 2000 (Suggested: 0). Pixels. Less than 0 moves it up.", L"0", {}, -2000, 2000, 5, L"Place"},
{K::Choice, L"popupSize", L"Size", L"", L"normal", {{L"compact", L"Compact"}, {L"normal", L"Normal"}, {L"large", L"Large"}}, 0, 100, 5, L"Look"},
{K::Check, L"popupGlass", L"Blurred glass", L"On, the pop-up blurs what is behind it. Off, it is solid. The blur needs Windows transparency effects on.", L"1", {}, 0, 100, 5, L"Look"},
{K::Number, L"popupStrength", L"Background strength (%)", L"80 to 100 (Suggested: 85). How much of the dark background covers the blur.", L"85", {}, 80, 100, 5, L"Look"},
{K::Check, L"popupAnimate", L"Slide and fade", L"On, the pop-up slides and fades in and out. Off, it appears and goes at once.", L"1", {}, 0, 100, 5, L"Look"},
{K::Check, L"fadeOn", L"Fade the crosshair", L"On, the crosshair fades in and out when you show or hide it, instead of popping.", L"1", {}, 0, 100, 5, L"Crosshair fade"},
{K::Number, L"fadeInTime", L"Fade in time (milliseconds)", L"0 to 2000 (Suggested: 150).", L"150", {}, 0, 2000, 5, L"Crosshair fade"},
{K::Number, L"fadeOutTime", L"Fade out time (milliseconds)", L"0 to 2000 (Suggested: 150).", L"150", {}, 0, 2000, 5, L"Crosshair fade"},
{K::Choice, L"fadeCurve", L"Fade style", L"", L"smooth", {{L"smooth", L"Smooth: starts and ends gently"}, {L"linear", L"Even all the way"}}, 0, 100, 5, L"Crosshair fade"},
{K::Choice, L"fadeWhen", L"Fade when", L"Aiming fades too with the second choice, so leave it on the first for the fastest aim.", L"toggle", {{L"toggle", L"You show or hide it"}, {L"all", L"It shows or hides for any reason"}}, 0, 100, 5, L"Crosshair fade"}
    };
}

struct SetPageInfo {
    PCWSTR name, intro;
    WCHAR glyph;
};
static const SetPageInfo kSetPages[] = {
{L"Crosshair", L"Pick a crosshair, its color, size and outline.", 0xF272},
{L"Shape", L"Build your own crosshair. Used when the style is \"Your own design\".", 0xE70F},
{L"Position", L"Where the crosshair sits on the screen.", 0xE81D},
{L"When to show", L"When the crosshair shows, and when it gets out of the way.", 0xE7B3},
{L"Keys and tray", L"Shortcuts, the tray icon and this window.", 0xE765},
{L"Pop-up and fade", L"The pop-up that says the crosshair is on or off, and how the crosshair fades.", 0xE7E7},
{L"Look", L"Choose how this settings window looks and whether its tray icon is shown.", 0xE790},
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
constexpr PCWSTR kSetDittoUrl = L"https://github.com/Tu2525/OpenCrosshair";
constexpr PCWSTR kSetCrossOverUrl = L"https://github.com/lacymorrow/crossover";
constexpr PCWSTR kSetRepoUrl = L"https://github.com/DavidHiFi/davids-windhawk-mods";
constexpr PCWSTR kSetBugUrl =
    L"https://github.com/DavidHiFi/davids-windhawk-mods/issues/new?title=%5BSeamless%20Game%20Crosshair%5D%20";
constexpr PCWSTR kSetTitle = L"Seamless Crosshair";
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

// ---- Tray menu -------------------------------------------------------------

}  // namespace sgcset

static std::wstring HotkeyHint(int hk) {
    if (hk >= 0 && !g_cfg.hotkeys[hk].empty()) return g_cfg.hotkeys[hk];
    return L"";
}

// The tray menu runs on the engine's renderer, the same menu every mod's tray uses.
static void ShowTrayMenu(POINT pt) {
    Config c = g_cfg;
    std::vector<sgcset::SetMenuItem> styles, colors, sizes;
    for (int i = 0; i < (int)ARRAYSIZE(kStyles); i++) {
        bool image = !wcscmp(kStyles[i].key, L"image");
        styles.push_back(sgcset::Set_MenuRow(IDM_STYLE + i, nullptr,
                                             image ? L"An image file" : kStyles[i].label,
                                             c.style == kStyles[i].key, image && c.imagePath.empty()));
    }
    for (size_t i = 0; i < c.colorCycle.size() && i < 100; i++)
        colors.push_back(sgcset::Set_MenuRow(IDM_COLOR + (int)i, nullptr, HexOf(c.colorCycle[i]).c_str(),
                                             c.colorCycle[i] == c.color));
    for (int i = 0; i < (int)ARRAYSIZE(kSizes); i++)
        sizes.push_back(sgcset::Set_MenuRow(IDM_SIZE + i, nullptr,
                                            (std::to_wstring(kSizes[i]) + L"%").c_str(), c.scale == kSizes[i]));
    std::vector<sgcset::SetMenuItem> items;
    items.push_back(sgcset::Set_MenuRow(IDM_SHOW, nullptr, L"Show crosshair", g_shown, false, HotkeyHint(HK_TOGGLE).c_str()));
    items.push_back(sgcset::Set_MenuRow(IDM_CENTER, nullptr, L"Back to the center", false,
                                        !(c.offsetX || c.offsetY), HotkeyHint(HK_CENTER).c_str()));
    if (!g_lastApp.empty()) {
        std::wstring look = L"Keep this look for " + g_lastApp;
        items.push_back(sgcset::Set_MenuRow(IDM_LOOK, nullptr, look.c_str(), g_lookExe == g_lastApp, false,
                                            HotkeyHint(HK_LOOK).c_str()));
    }
    items.push_back(sgcset::Set_MenuSub(nullptr, L"Style", std::move(styles)));
    items.push_back(sgcset::Set_MenuSub(nullptr, L"Color", std::move(colors)));
    items.push_back(sgcset::Set_MenuSub(nullptr, L"Size", std::move(sizes)));
    sgcset::SetMenuItem sep;
    sep.separator = true;
    items.push_back(std::move(sep));
    items.push_back(sgcset::Set_MenuRow(IDM_SETTINGS, nullptr, L"Settings", false, false, HotkeyHint(HK_SETTINGS).c_str()));
    int cmd = sgcset::Set_TrayMenu(g_msgWnd, items, &pt);
    if (cmd == IDM_SHOW) SetShown(!g_shown, ShowSource::Tray);
    else if (cmd == IDM_CENTER) Change({{L"offsetX", L"0"}, {L"offsetY", L"0"}});
    else if (cmd == IDM_SETTINGS) OpenSettings();
    else if (cmd == IDM_LOOK) ToggleLook();
    else if (cmd >= IDM_STYLE && cmd < IDM_STYLE + (int)ARRAYSIZE(kStyles))
        Change({{L"style", kStyles[cmd - IDM_STYLE].key}});
    else if (cmd >= IDM_COLOR && cmd < IDM_COLOR + (int)c.colorCycle.size())
        Change({{L"color", HexOf(c.colorCycle[cmd - IDM_COLOR])}});
    else if (cmd >= IDM_SIZE && cmd < IDM_SIZE + (int)ARRAYSIZE(kSizes))
        SetScale(kSizes[cmd - IDM_SIZE]);
}

namespace sgcset {

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
        if (w.fRailName && Set_TextW(w.fRailName.get(), L"Crosshair") <= railW) break;
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
    const bool stacked = ColorRowStacked(f, row.right - row.left);
    float r = row.right - kSetRowPad, mid = (row.top + row.bottom - (stacked ? kSgcChipLine : 0)) / 2,
          h = kSetBoxH / 2;
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
            float x = stacked ? row.left + kSetRowPad : p.box.left - 12 - (kSetChipCount * 26 - 6);
            float cy = stacked ? row.bottom - 24 : mid;
            for (int i = 0; i < kSetChipCount; i++) p.chip[i] = {x + i * 26, cy - 10, x + i * 26 + 20, cy + 10};
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
        add(SetItem::Link, 56, L"Inspired by OpenCrosshair", L"The open source crosshair app", kSetDittoUrl);
        add(SetItem::Link, 56, L"And by CrossOver", L"By Lacy Morrow", kSetCrossOverUrl);
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

    float textW = w.contentW - 2 * kSetRowPad - RowControlW(f, w.contentW) - 24;
    float lh = Set_TextH(w.fLabel.get(), f.label, textW);
    float dh = (f.desc && *f.desc) ? Set_TextH(w.fHint.get(), f.desc, textW) + 3 : 0;
    float top = row.top + (it.h - (ColorRowStacked(f, w.contentW) ? kSgcChipLine : 0) - lh - dh) / 2;
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
    p.Glyph(w.fIconL.get(), 0xF272, mark, mocha::crust);
    float x = mark.right + 20;
    p.Text(w.fBig.get(), L"Seamless Crosshair", {x, row.top + 18, row.right - 16, row.top + 46}, mocha::text);
#ifdef WH_MOD_VERSION
    std::wstring ver = std::wstring(L"Version ") + WH_MOD_VERSION + L"  \u00B7  MIT license  \u00B7  A Windhawk mod";
#else
    std::wstring ver = L"MIT license  \u00B7  A Windhawk mod";
#endif
    p.Text(w.fHint.get(), ver, {x, row.top + 48, row.right - 16, row.top + 68}, mocha::subtext0);
    p.Text(w.fHint.get(), L"A crosshair over any game: your own design, color and size, with shortcuts.",
           {x, row.top + 72, row.right - 16, row.top + 110}, mocha::subtext1);
    p.Text(w.fHint.get(), L"Made by DavidHiFi, inspired by OpenCrosshair and CrossOver.",
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
    p.Text(w.fRailName.get(), L"Crosshair", {d.left + 90, d.top + 32, d.left + w.railW - 10, d.top + 56}, mocha::text, textA);
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
    p.Glyph(glyph, 0xF272, r, mocha::crust);
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
    HWND hwnd = CreateWindowExW(0, kSettingsClass, L"Seamless Game Crosshair settings", style,
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
}  // namespace sgcset
