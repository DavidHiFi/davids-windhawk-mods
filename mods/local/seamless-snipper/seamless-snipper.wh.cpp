// ==WindhawkMod==
// @id              seamless-snipper
// @name            Seamless Snipper
// @description     Snip a region, a window or the whole screen: frozen screen, window snapping, a pixel magnifier, straight to the clipboard and your folder. Plus Magic Pointer: shake the mouse, point at anything and ask AI about it
// @version         0.2.1
// @author          DavidHiFi, Jaex, ShareX contributors, Rono
// @github          https://github.com/DavidHiFi
// @homepage        https://github.com/DavidHiFi/davids-windhawk-mods
// @include         windhawk.exe
// @architecture    x86-64
// @compilerOptions -lgdi32 -luser32 -lshell32 -lshlwapi -lole32 -loleaut32 -luuid -ld2d1 -ldwrite -lwindowscodecs -ldwmapi -lcomctl32 -luxtheme -lcomdlg32 -limm32 -ladvapi32 -lshcore -lversion -lwinmm -lwinhttp -lcrypt32
// @license         GPL-3.0
// @donateUrl       https://ko-fi.com/DavidHiFi
// ==/WindhawkMod==

// ==WindhawkModReadme==
/*
# Seamless Snipper

The screenshot tool, built into Windhawk. Press Print Screen and the screen
freezes: drag a region, or hover a window and click to take all of it. The snip
goes to your clipboard and your pictures folder at once, with a name you can
read later, like "Discord 4.05 pm.png".

![Seamless Snipper preview](https://raw.githubusercontent.com/DavidHiFi/davids-windhawk-mods/main/media/previews/seamless-snipper.png)

## What it does

- Region snips on a frozen screen. The outside dims, the region stays bright,
  and its size shows beside it.
- Hover to snap to a window, or to a button, panel or list inside it, then
  click once.
- A magnifier with a pixel grid follows the pointer. Press C to copy the color
  under it.
- Snip the active window, the screen you are on, or every screen at once.
- Every snip is copied and saved, in a folder per day, as PNG or JPG.
- A small preview card after each snip: click it to open the picture,
  right-click it to open the folder.
- A tray icon: click it for settings, right-click it to snip from a menu.
- Magic Pointer: shake the mouse and point at anything on screen to ask AI
  about it, search it with Google Lens or copy its text. See below.

## Keys

| Key | What it does |
|---|---|
| Print Screen | Snip a region |
| Shift + Print Screen | Snip every screen |
| Alt + Print Screen | Snip the active window |
| Ctrl + Print Screen | Snip the screen the mouse is on |

On the frozen screen: drag to snip a region, click a highlighted window to snip
it, Enter takes what is highlighted, arrow keys move the pointer one pixel (ten
with Shift), the mouse wheel zooms the magnifier, C copies the color, right
click or Esc backs out.

## Magic Pointer

1. Shake the mouse, or press Win + Shift + G.
2. Hover a button, picture or paragraph to outline it and click to pick it,
   or drag over any area.
3. A card opens beside it. Type a question and press Enter, or pick a
   suggestion. While the pointer is out you can also just start typing.

Esc or a right click puts it away. It also leaves when the mouse stays still.

With an AI key (Gemini, ChatGPT or Claude) answers come right in the card.
The key moves into encrypted storage only your Windows account can read, so
you can clear the box after saving. Type none to remove it. Without a key,
the card hands your question and picks to Gemini in your browser and never
presses send for you.

Every pick is read for text by Windows itself, on your PC.

Privacy: summoning, picking and copying stay on your PC. With a key, Send, a
suggestion or Translate sends the picks (as pictures, up to 1536 pixels), their
text and your question to the service whose key you use, over HTTPS. Smart
suggestions (off by default) sends each pick as soon as you make it. Google
Lens uploads the pick to Google. Free Gemini keys may be used by Google to
improve its products, so keep private content off the free tier. Temporary
pictures go to %LOCALAPPDATA%\MagicPointerPlus\Temp, which only your account
can open, and they are deleted within 30 minutes.

Shakes are ignored while a game, video or presentation fills the screen, and in
the apps you list in the settings.

## Good to know

If ShareX is running, Snipper leaves these keys to it until it closes (you can
turn that off). Windows' own "Print Screen opens Snipping Tool" switch must be
off for Print Screen to reach Snipper.

## Credits

Based on [ShareX](https://github.com/ShareX/ShareX) by Jaex and the ShareX
contributors (GPL-3.0). Written again in C++ for Windhawk.

Magic Pointer is based on
[Magic Pointer by Rono](https://github.com/rono-zeroseven/magic-pointer),
restyled to match the rest of Snipper.
*/
// ==/WindhawkModReadme==

// ==WindhawkModSettings==
/*
- regionHotkey: "PrintScreen"
  $name: "Snip a region"
  $description: "Freezes the screen so you can drag a region or click a window. Click the box and press the keys. Leave it empty to turn it off."
- fullscreenHotkey: "Shift+PrintScreen"
  $name: "Snip every screen"
  $description: "All your screens in one picture. Click the box and press the keys. Leave it empty to turn it off."
- windowHotkey: "Alt+PrintScreen"
  $name: "Snip the active window"
  $description: "The window you are using, without the desktop around it. Click the box and press the keys. Leave it empty to turn it off."
- monitorHotkey: "Ctrl+PrintScreen"
  $name: "Snip the active screen"
  $description: "The screen the mouse is on. Click the box and press the keys. Leave it empty to turn it off."
- stepAside: true
  $name: "Let ShareX keep its keys"
  $description: "While ShareX is running, Snipper leaves these keys to it and takes them over once ShareX closes. The tray menu always works."
- copyToClipboard: true
  $name: "Copy to the clipboard"
  $description: "Every snip is ready to paste."
- saveToFile: true
  $name: "Save to a file"
  $description: "Every snip is also saved as a picture."
- showToast: true
  $name: "Show a preview card"
  $description: "A small card with the snip. Click it to open the picture, right-click it to open its folder."
- toastSeconds: 3
  $name: "Card time (seconds)"
  $description: "1 to 10 (Suggested: 3)."
- captureCursor: true
  $name: "Include the mouse pointer"
  $description: "Draws the pointer into full screen, screen and window snips, as ShareX did."
- playSound: false
  $name: "Play a sound"
  $description: "A short camera click after each snip."
- saveFolder: "G:\\Gallery"
  $name: "Folder"
  $description: "Where pictures are saved. The folder is made if it is missing."
- subfolder: "day"
  $name: "Subfolders"
  $description: "Keeps the folder tidy."
  $options:
  - day: "One per day, like 12-11-26"
  - app: "One per app, like Discord"
  - none: "None"
- fileFormat: "png"
  $name: "Picture format"
  $description: "PNG is sharp and lossless. JPG files are smaller."
  $options:
  - png: "PNG"
  - jpg: "JPG"
- jpgQuality: 92
  $name: "JPG quality"
  $description: "50 to 100 (Suggested: 92)."
- dimOpacity: 45
  $name: "Dim outside (%)"
  $description: "0 to 85 (Suggested: 45). How dark the screen gets around the region."
- snapWindows: true
  $name: "Snap to windows"
  $description: "Hover a window and click to snip all of it, without dragging."
- snapControls: true
  $name: "Snap to parts of windows"
  $description: "Hovering also finds buttons, panels and lists inside windows."
- showSize: true
  $name: "Show the size"
  $description: "The size of the region, next to it."
- crosshairLines: false
  $name: "Crosshair lines"
  $description: "Thin lines across the screen through the pointer, for lining up edges."
- magnifier: true
  $name: "Magnifier"
  $description: "A zoomed view of the pixels under the pointer."
- magnifierPixels: 15
  $name: "Pixels across"
  $description: "7 to 31 (Suggested: 15). How many screen pixels the magnifier shows."
- magnifierZoom: 10
  $name: "Zoom"
  $description: "4 to 24 (Suggested: 10). The mouse wheel changes it too."
- magnifierGrid: true
  $name: "Pixel grid"
  $description: "Lines between the zoomed pixels."
- accentFrom: "#89B4FA"
  $name: "Selection color"
  $description: "In hexadecimal. The gradient starts with this color."
- accentTo: "#CBA6F7"
  $name: "Selection color 2"
  $description: "In hexadecimal. The gradient ends with this color."
- settingsGlass: true
  $name: "Blurred settings window"
  $description: "On, the settings window is see-through glass with Windows acrylic behind it. Off, it is solid. Applies when you save."
- nativeSettingsTitleBar: false
  $name: "Native Windows title bar"
  $description: "Use the Windows title bar and window buttons for this settings window. Applies when you save."
- settingsTrayIcon: true
  $name: "Tray icon"
  $description: "A Snipper icon in the system tray. Click it to open these settings, right-click it for a menu."
- pointerOn: true
  $name: "Magic Pointer"
  $description: "Shake the mouse or press its key, then point at anything on screen and ask about it. Off, nothing summons it."
- pointerHotkey: "Win+Shift+G"
  $name: "Key"
  $description: "Summons the pointer. Press it again to put it away. Click the box and press the keys. Leave it empty to turn it off."
- pointerShake: true
  $name: "Shake to summon"
  $description: "Wiggle the mouse, or swipe back and forth on the touchpad."
- pointerSensitivity: 5
  $name: "Shake sensitivity"
  $description: "1 to 10 (Suggested: 5). 1 needs a big, fast shake. 10 takes a small wiggle."
- pointerFullscreen: true
  $name: "Ignore shakes in fullscreen"
  $description: "Games, videos and presentations that fill the screen, borderless ones too."
- pointerSkipApps: ""
  $name: "Skip these apps"
  $description: "Shakes do nothing in them. Names like game.exe or window titles, split by semicolons."
- pointerTypeToAsk: true
  $name: "Start typing to ask"
  $description: "With the pointer showing, just type to ask without picking anything. Off, your typing stays in the app."
- pointerTimeout: 15
  $name: "Put away after (seconds)"
  $description: "0 to 3600 (Suggested: 15). When the mouse stays still this long. 0 keeps it until you press Esc."
- pointerGlow: "gradient"
  $name: "Glow"
  $description: "The glow around the pointer and what you pick."
  $options:
  - gradient: "Blue to mauve, your selection colors"
  - accent: "Windows accent color"
  - rainbow: "Google colors"
  - "#89B4FA": "Blue"
  - "#CBA6F7": "Mauve"
- pointerGlass: true
  $name: "Glass"
  $description: "The card and the hint get frosted glass. Off, they are solid."
- pointerRipple: true
  $name: "Ripple"
  $description: "The screen gently ripples when the pointer appears."
- pointerSize: 100
  $name: "Pointer size (%)"
  $description: "50 to 300 (Suggested: 100)."
- pointerCursorFile: ""
  $name: "Pointer file"
  $description: "Optional. A .cur or .ani file shown while the pointer is out."
- pointerDim: 50
  $name: "Dim outside (%)"
  $description: "0 to 80 (Suggested: 50). How dark the screen gets around the area you drag."
- pointerHint: true
  $name: "Show the hint"
  $description: "A small bubble that says what to do when the pointer appears."
- pointerHighlight: true
  $name: "Outline what you point at"
  $description: "Buttons, pictures and text get an outline, so one click picks them."
- pointerApiKey: ""
  $name: "AI key"
  $description: "Optional. A Gemini, ChatGPT or Claude key for answers in the card. It is kept encrypted. Type none to remove it."
- pointerModel: "fast"
  $name: "Model"
  $description: "If the one you pick is busy, a faster one answers."
  $options:
  - fast: "Fast, answers in a second or two"
  - balanced: "Balanced, better answers, costs more"
  - smart: "Smartest, slowest and costs the most"
- pointerSuggestions: false
  $name: "Smart suggestions"
  $description: "Up to three ideas for each pick. Needs a key, and every pick is sent to the AI as soon as you make it."
- pointerTranslateTo: "auto"
  $name: "Translate to"
  $description: "For the Translate button on the card. Needs a key."
  $options:
  - auto: "Your Windows language"
  - Arabic: "Arabic"
  - Bengali: "Bengali"
  - "Chinese (Simplified)": "Chinese (Simplified)"
  - "Chinese (Traditional)": "Chinese (Traditional)"
  - Croatian: "Croatian"
  - Czech: "Czech"
  - Danish: "Danish"
  - Dutch: "Dutch"
  - English: "English"
  - Finnish: "Finnish"
  - French: "French"
  - German: "German"
  - Greek: "Greek"
  - Hebrew: "Hebrew"
  - Hindi: "Hindi"
  - Hungarian: "Hungarian"
  - Indonesian: "Indonesian"
  - Italian: "Italian"
  - Japanese: "Japanese"
  - Korean: "Korean"
  - Norwegian: "Norwegian"
  - Persian: "Persian"
  - Polish: "Polish"
  - Portuguese: "Portuguese"
  - Romanian: "Romanian"
  - Russian: "Russian"
  - Spanish: "Spanish"
  - Swedish: "Swedish"
  - Tamil: "Tamil"
  - Thai: "Thai"
  - Turkish: "Turkish"
  - Ukrainian: "Ukrainian"
  - Vietnamese: "Vietnamese"
- pointerOcr: true
  $name: "Read text in pictures"
  $description: "Windows reads the text in each pick on your PC, so you can copy it and the AI gets it too."
- pointerBrowser: "default"
  $name: "Browser"
  $description: "Opens Gemini and Google Lens. If it is missing, your default opens."
  $options:
  - default: "Windows default browser"
  - chrome: "Google Chrome"
  - edge: "Microsoft Edge"
  - firefox: "Mozilla Firefox"
  - brave: "Brave"
  - zen: "Zen Browser"
  - opera: "Opera"
  - vivaldi: "Vivaldi"
  - librewolf: "LibreWolf"
  - waterfox: "Waterfox"
  - floorp: "Floorp"
  - custom: "Other (set its program below)"
- pointerBrowserPath: ""
  $name: "Other browser program"
  $description: "Only for Other: the full path of the browser program."
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
#include <shellscalingapi.h>
#include <mmsystem.h>
#include <tlhelp32.h>

#include <algorithm>
#include <atomic>
#include <cmath>
#include <cstdint>
#include <cstring>
#include <cwchar>
#include <cwctype>
#include <functional>
#include <map>
#include <memory>
#include <mutex>
#include <set>
#include <string>
#include <unordered_map>
#include <vector>

#include <windhawk_tool_mod.h>

namespace snpset {
void OpenSettingsWindow();
void CloseSettingsWindow();
extern std::atomic<HWND> g_settingsWnd;
HWND RecordingKeyWindow();
}  // namespace snpset

// Magic Pointer, the point-and-ask tool (magic-pointer.cpp, inlined after this file).
namespace magicptr {
BOOL ToolInit();
void ToolSettingsChanged();
void ToolUninit();
void Summon();
std::wstring HotkeyLabel();
bool Enabled();
}  // namespace magicptr

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

template <class T>
struct Ptr {
    T* p = nullptr;
    Ptr() = default;
    Ptr(const Ptr&) = delete;
    Ptr& operator=(const Ptr&) = delete;
    ~Ptr() { Reset(); }
    void Reset() {
        if (p) p->Release();
        p = nullptr;
    }
    T** put() {
        Reset();
        return &p;
    }
    T* operator->() const { return p; }
    explicit operator bool() const { return p != nullptr; }
};

static bool IsShellWindow(HWND hwnd) {
    WCHAR cls[64]{};
    GetClassNameW(hwnd, cls, 64);
    return !wcscmp(cls, L"Progman") || !wcscmp(cls, L"WorkerW") || !wcscmp(cls, L"Shell_TrayWnd") ||
           !wcscmp(cls, L"Shell_SecondaryTrayWnd");
}

static bool IsDesktopWindow(HWND hwnd) {
    WCHAR cls[64]{};
    GetClassNameW(hwnd, cls, 64);
    return !wcscmp(cls, L"Progman") || !wcscmp(cls, L"WorkerW");
}

static bool IsOwnWindow(HWND hwnd) {
    DWORD pid = 0;
    GetWindowThreadProcessId(hwnd, &pid);
    return pid == GetCurrentProcessId();
}

static bool IsCloaked(HWND hwnd) {
    DWORD c = 0;
    return SUCCEEDED(DwmGetWindowAttribute(hwnd, DWMWA_CLOAKED, &c, sizeof(c))) && c;
}

// The window's visible frame, without the invisible resize borders.
static RECT FrameRect(HWND hwnd) {
    RECT r{};
    if (FAILED(DwmGetWindowAttribute(hwnd, DWMWA_EXTENDED_FRAME_BOUNDS, &r, sizeof(r))) || IsRectEmpty(&r))
        GetWindowRect(hwnd, &r);
    return r;
}

static RECT VirtualScreen() {
    int x = GetSystemMetrics(SM_XVIRTUALSCREEN), y = GetSystemMetrics(SM_YVIRTUALSCREEN);
    return RECT{x, y, x + GetSystemMetrics(SM_CXVIRTUALSCREEN), y + GetSystemMetrics(SM_CYVIRTUALSCREEN)};
}

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
    {VK_PRIOR, L"PgUp"},    {VK_NEXT, L"PgDn"},       {VK_SNAPSHOT, L"PrtSc"}, {VK_SNAPSHOT, L"PrintScr"},
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
// Settings
// ---------------------------------------------------------------------------

enum { HK_REGION, HK_FULL, HK_WINDOW, HK_MONITOR, HK_COUNT };
static const PCWSTR kHotkeyKeys[HK_COUNT] = {L"regionHotkey", L"fullscreenHotkey", L"windowHotkey",
                                             L"monitorHotkey"};

struct Config {
    std::wstring hotkeys[HK_COUNT];
    bool stepAside = true;
    bool copy = true, save = true, toast = true, cursor = true, sound = false;
    int toastSeconds = 3;
    std::wstring folder = L"G:\\Gallery", subfolder = L"day", format = L"png";
    int jpgQuality = 92;
    int dim = 45;
    bool snapWindows = true, snapControls = true, showSize = true, crossLines = false;
    bool magnifier = true, magGrid = true;
    int magPixels = 15, magZoom = 10;
    COLORREF accent1 = RGB(0x89, 0xB4, 0xFA), accent2 = RGB(0xCB, 0xA6, 0xF7);
    bool trayIcon = true;
};

static Config g_cfg;

static void LoadSettings() {
    Config c;
    for (int i = 0; i < HK_COUNT; i++) c.hotkeys[i] = Trim(ReadStr(kHotkeyKeys[i]));
    c.stepAside = Wh_GetIntSetting(L"stepAside") != 0;
    c.copy = Wh_GetIntSetting(L"copyToClipboard") != 0;
    c.save = Wh_GetIntSetting(L"saveToFile") != 0;
    c.toast = Wh_GetIntSetting(L"showToast") != 0;
    c.toastSeconds = Clamp(Wh_GetIntSetting(L"toastSeconds"), 1, 10);
    c.cursor = Wh_GetIntSetting(L"captureCursor") != 0;
    c.sound = Wh_GetIntSetting(L"playSound") != 0;
    c.folder = Trim(ReadStr(L"saveFolder"));
    while (c.folder.size() >= 2 && c.folder.front() == L'"' && c.folder.back() == L'"')
        c.folder = c.folder.substr(1, c.folder.size() - 2);
    while (c.folder.size() > 3 && (c.folder.back() == L'\\' || c.folder.back() == L'/')) c.folder.pop_back();
    if (c.folder.empty()) c.folder = L"G:\\Gallery";
    c.subfolder = OneOf(ReadStr(L"subfolder"), {L"day", L"app", L"none"});
    c.format = OneOf(ReadStr(L"fileFormat"), {L"png", L"jpg"});
    c.jpgQuality = Clamp(Wh_GetIntSetting(L"jpgQuality"), 50, 100);
    c.dim = Clamp(Wh_GetIntSetting(L"dimOpacity"), 0, 85);
    c.snapWindows = Wh_GetIntSetting(L"snapWindows") != 0;
    c.snapControls = Wh_GetIntSetting(L"snapControls") != 0;
    c.showSize = Wh_GetIntSetting(L"showSize") != 0;
    c.crossLines = Wh_GetIntSetting(L"crosshairLines") != 0;
    c.magnifier = Wh_GetIntSetting(L"magnifier") != 0;
    c.magPixels = Clamp(Wh_GetIntSetting(L"magnifierPixels"), 7, 31) | 1;  // Odd, so one pixel is the middle.
    c.magZoom = Clamp(Wh_GetIntSetting(L"magnifierZoom"), 4, 24);
    c.magGrid = Wh_GetIntSetting(L"magnifierGrid") != 0;
    COLORREF col;
    if (ParseHex(ReadStr(L"accentFrom"), col)) c.accent1 = col;
    if (ParseHex(ReadStr(L"accentTo"), col)) c.accent2 = col;
    c.trayIcon = Wh_GetIntSetting(L"settingsTrayIcon") != 0;
    g_cfg = c;
}

// ---------------------------------------------------------------------------
// Pictures: BGRA pixels, top-down, alpha always 255.
// ---------------------------------------------------------------------------

struct Shot {
    int x = 0, y = 0, w = 0, h = 0;  // Screen position and size.
    std::vector<uint32_t> px;
};

static bool CaptureRect(const RECT& r, bool cursor, Shot& out) {
    int w = r.right - r.left, h = r.bottom - r.top;
    if (w <= 0 || h <= 0) return false;
    HDC sdc = GetDC(nullptr);
    HDC mdc = CreateCompatibleDC(sdc);
    BITMAPINFO bi{};
    bi.bmiHeader.biSize = sizeof(bi.bmiHeader);
    bi.bmiHeader.biWidth = w;
    bi.bmiHeader.biHeight = -h;
    bi.bmiHeader.biPlanes = 1;
    bi.bmiHeader.biBitCount = 32;
    bi.bmiHeader.biCompression = BI_RGB;
    void* bits = nullptr;
    HBITMAP hb = CreateDIBSection(mdc, &bi, DIB_RGB_COLORS, &bits, nullptr, 0);
    bool ok = false;
    if (hb) {
        HGDIOBJ old = SelectObject(mdc, hb);
        ok = BitBlt(mdc, 0, 0, w, h, sdc, r.left, r.top, SRCCOPY | CAPTUREBLT) != 0;
        if (ok && cursor) {
            CURSORINFO ci{sizeof(ci)};
            if (GetCursorInfo(&ci) && (ci.flags & CURSOR_SHOWING) && ci.hCursor) {
                ICONINFO ii{};
                if (GetIconInfo(ci.hCursor, &ii)) {
                    DrawIconEx(mdc, ci.ptScreenPos.x - (int)ii.xHotspot - r.left,
                               ci.ptScreenPos.y - (int)ii.yHotspot - r.top, ci.hCursor, 0, 0, 0, nullptr, DI_NORMAL);
                    if (ii.hbmMask) DeleteObject(ii.hbmMask);
                    if (ii.hbmColor) DeleteObject(ii.hbmColor);
                }
            }
        }
        GdiFlush();
        if (ok) {
            out.x = r.left;
            out.y = r.top;
            out.w = w;
            out.h = h;
            out.px.assign((uint32_t*)bits, (uint32_t*)bits + (size_t)w * h);
            for (auto& v : out.px) v |= 0xFF000000;
        }
        SelectObject(mdc, old);
        DeleteObject(hb);
    }
    DeleteDC(mdc);
    ReleaseDC(nullptr, sdc);
    return ok;
}

static Shot Crop(const Shot& s, RECT r) {
    Shot o;
    r.left = std::max(r.left, 0L);
    r.top = std::max(r.top, 0L);
    r.right = std::min(r.right, (LONG)s.w);
    r.bottom = std::min(r.bottom, (LONG)s.h);
    if (r.right <= r.left || r.bottom <= r.top) return o;
    o.x = s.x + r.left;
    o.y = s.y + r.top;
    o.w = r.right - r.left;
    o.h = r.bottom - r.top;
    o.px.resize((size_t)o.w * o.h);
    for (int y = 0; y < o.h; y++)
        memcpy(&o.px[(size_t)y * o.w], &s.px[(size_t)(r.top + y) * s.w + r.left], (size_t)o.w * 4);
    return o;
}

// Box filter, for the preview card.
static Shot Downscale(const Shot& s, int maxW, int maxH) {
    double k = std::min({1.0, (double)maxW / s.w, (double)maxH / s.h});
    if (k >= 1.0) return s;
    Shot o;
    o.w = std::max(1, (int)std::lround(s.w * k));
    o.h = std::max(1, (int)std::lround(s.h * k));
    o.px.resize((size_t)o.w * o.h);
    for (int y = 0; y < o.h; y++) {
        int y0 = (int)((int64_t)y * s.h / o.h), y1 = std::max(y0 + 1, (int)((int64_t)(y + 1) * s.h / o.h));
        for (int x = 0; x < o.w; x++) {
            int x0 = (int)((int64_t)x * s.w / o.w), x1 = std::max(x0 + 1, (int)((int64_t)(x + 1) * s.w / o.w));
            uint64_t r = 0, g = 0, b = 0, n = (uint64_t)(x1 - x0) * (y1 - y0);
            for (int yy = y0; yy < y1; yy++) {
                const uint32_t* row = &s.px[(size_t)yy * s.w];
                for (int xx = x0; xx < x1; xx++) {
                    uint32_t v = row[xx];
                    r += (v >> 16) & 0xFF;
                    g += (v >> 8) & 0xFF;
                    b += v & 0xFF;
                }
            }
            o.px[(size_t)y * o.w + x] = 0xFF000000 | (uint32_t)(r / n) << 16 | (uint32_t)(g / n) << 8 | (uint32_t)(b / n);
        }
    }
    return o;
}

static HRESULT EncodeFile(const Shot& s, const std::wstring& path, bool jpg, int quality) {
    Ptr<IWICImagingFactory> f;
    Ptr<IWICBitmap> bmp;
    Ptr<IWICFormatConverter> conv;
    Ptr<IWICStream> st;
    Ptr<IWICBitmapEncoder> enc;
    Ptr<IWICBitmapFrameEncode> fr;
    Ptr<IPropertyBag2> bag;
    HRESULT hr = CoCreateInstance(CLSID_WICImagingFactory, nullptr, CLSCTX_INPROC_SERVER, IID_IWICImagingFactory,
                                  (void**)f.put());
    if (SUCCEEDED(hr))
        hr = f->CreateBitmapFromMemory(s.w, s.h, GUID_WICPixelFormat32bppBGR, s.w * 4, (UINT)(s.px.size() * 4),
                                       (BYTE*)s.px.data(), bmp.put());
    if (SUCCEEDED(hr)) hr = f->CreateFormatConverter(conv.put());
    if (SUCCEEDED(hr))
        hr = conv->Initialize(bmp.p, GUID_WICPixelFormat24bppBGR, WICBitmapDitherTypeNone, nullptr, 0,
                              WICBitmapPaletteTypeCustom);
    if (SUCCEEDED(hr)) hr = f->CreateStream(st.put());
    if (SUCCEEDED(hr)) hr = st->InitializeFromFilename(path.c_str(), GENERIC_WRITE);
    if (FAILED(hr)) return hr;
    hr = f->CreateEncoder(jpg ? GUID_ContainerFormatJpeg : GUID_ContainerFormatPng, nullptr, enc.put());
    if (SUCCEEDED(hr)) hr = enc->Initialize(st.p, WICBitmapEncoderNoCache);
    if (SUCCEEDED(hr)) hr = enc->CreateNewFrame(fr.put(), bag.put());
    if (SUCCEEDED(hr) && jpg && bag) {
        PROPBAG2 opt{};
        opt.pstrName = (LPOLESTR)L"ImageQuality";
        VARIANT v;
        VariantInit(&v);
        v.vt = VT_R4;
        v.fltVal = quality / 100.0f;
        bag->Write(1, &opt, &v);
    }
    if (SUCCEEDED(hr)) hr = fr->Initialize(bag.p);
    if (SUCCEEDED(hr)) hr = fr->SetSize(s.w, s.h);
    WICPixelFormatGUID pf = GUID_WICPixelFormat24bppBGR;
    if (SUCCEEDED(hr)) hr = fr->SetPixelFormat(&pf);
    if (SUCCEEDED(hr)) hr = fr->WriteSource(conv.p, nullptr);
    if (SUCCEEDED(hr)) hr = fr->Commit();
    if (SUCCEEDED(hr)) hr = enc->Commit();
    st.Reset();
    if (FAILED(hr)) DeleteFileW(path.c_str());
    return hr;
}

// ---------------------------------------------------------------------------
// Names: "Discord 4.05 pm.png"
// ---------------------------------------------------------------------------

static std::wstring CleanName(std::wstring s) {
    for (auto& c : s)
        if (c < 32 || wcschr(L"<>:\"/\\|?*", c)) c = L' ';
    s = Trim(s);
    std::wstring o;
    for (wchar_t c : s)
        if (!(c == L' ' && !o.empty() && o.back() == L' ')) o += c;
    while (!o.empty() && (o.back() == L'.' || o.back() == L' ')) o.pop_back();
    if (o.size() > 40) o = Trim(o.substr(0, 40));
    return o;
}

static std::wstring FileDescription(const std::wstring& path) {
    DWORD dummy = 0, size = GetFileVersionInfoSizeW(path.c_str(), &dummy);
    if (!size) return {};
    std::vector<BYTE> data(size);
    if (!GetFileVersionInfoW(path.c_str(), 0, size, data.data())) return {};
    struct Lang {
        WORD lang, cp;
    }* langs = nullptr;
    UINT len = 0;
    std::vector<std::wstring> keys;
    if (VerQueryValueW(data.data(), L"\\VarFileInfo\\Translation", (void**)&langs, &len) && len >= sizeof(Lang)) {
        WCHAR k[64];
        swprintf_s(k, L"\\StringFileInfo\\%04x%04x\\FileDescription", langs[0].lang, langs[0].cp);
        keys.push_back(k);
    }
    keys.push_back(L"\\StringFileInfo\\040904b0\\FileDescription");
    keys.push_back(L"\\StringFileInfo\\040904e4\\FileDescription");
    for (auto& k : keys) {
        WCHAR* text = nullptr;
        if (VerQueryValueW(data.data(), k.c_str(), (void**)&text, &len) && text && len > 1) return Trim(text);
    }
    return {};
}

// The app a window belongs to, as people call it: the exe's description, or the exe name.
static std::wstring AppName(HWND hwnd) {
    static std::mutex lock;
    static std::unordered_map<std::wstring, std::wstring> cache;
    if (!hwnd) return L"Screenshot";
    hwnd = GetAncestor(hwnd, GA_ROOT);
    if (!hwnd || IsShellWindow(hwnd)) return L"Screenshot";
    DWORD pid = 0;
    GetWindowThreadProcessId(hwnd, &pid);
    std::wstring path;
    if (HANDLE h = OpenProcess(PROCESS_QUERY_LIMITED_INFORMATION, FALSE, pid)) {
        WCHAR buf[MAX_PATH * 2];
        DWORD n = ARRAYSIZE(buf);
        if (QueryFullProcessImageNameW(h, 0, buf, &n)) path.assign(buf, n);
        CloseHandle(h);
    }
    std::wstring exe = path.substr(path.find_last_of(L'\\') == std::wstring::npos ? 0 : path.find_last_of(L'\\') + 1);
    // Store apps all run in one frame host: their title is the useful name.
    if (!_wcsicmp(exe.c_str(), L"ApplicationFrameHost.exe")) {
        WCHAR title[128]{};
        GetWindowTextW(hwnd, title, 128);
        std::wstring t = CleanName(title);
        return t.empty() ? L"Screenshot" : t;
    }
    if (!_wcsicmp(exe.c_str(), L"explorer.exe")) return L"File Explorer";
    std::lock_guard<std::mutex> g(lock);
    auto it = cache.find(path);
    if (it != cache.end()) return it->second;
    std::wstring name = path.empty() ? L"" : CleanName(FileDescription(path));
    if (name.empty()) {
        name = exe;
        if (name.size() > 4 && !_wcsicmp(name.c_str() + name.size() - 4, L".exe")) name.resize(name.size() - 4);
        name = CleanName(name);
    }
    if (name.empty()) name = L"Screenshot";
    cache[path] = name;
    return name;
}

static std::wstring TimeStamp(const SYSTEMTIME& t) {
    int h = t.wHour % 12 == 0 ? 12 : t.wHour % 12;
    WCHAR buf[32];
    swprintf_s(buf, L"%d.%02d %s", h, t.wMinute, t.wHour < 12 ? L"am" : L"pm");
    return buf;
}

static std::wstring ExpandPath(const std::wstring& p) {
    WCHAR buf[MAX_PATH * 2]{};
    DWORD n = ExpandEnvironmentStringsW(p.c_str(), buf, ARRAYSIZE(buf));
    return n && n <= ARRAYSIZE(buf) ? std::wstring(buf) : p;
}

// ---------------------------------------------------------------------------
// Windows and threads
// ---------------------------------------------------------------------------

enum : UINT {
    WM_SNP_TRAY = WM_APP + 45,
    WM_SNP_SETTINGS,
    WM_SNP_SAVED,
};

constexpr UINT kTrayId = 1;
constexpr UINT_PTR kTimerKeys = 1, kTimerDeferred = 2, kTimerToast = 3;

static HWND g_msgWnd;
static DWORD g_uiTid;
static HANDLE g_uiThread, g_uiReady;
static HINSTANCE g_inst;
static UINT g_taskbarCreated;
static bool g_trayAdded;
static HICON g_trayIcon;
static bool g_hotkeyOn[HK_COUNT];
static bool g_steppedAside;
static int g_deferredMode = -1;
static std::atomic<int> g_saveThreads{0};
static std::atomic<bool> g_uiOk{false};  // The UI thread started fully (window, D2D, DirectWrite).

static ID2D1Factory* g_d2d;
static IDWriteFactory* g_dw;

static const wchar_t kOverlayClass[] = L"SeamlessSnipperScreen";
static const wchar_t kToastClass[] = L"SeamlessSnipperCard";

namespace mocha {
constexpr UINT32 base = 0x1E1E2E, mantle = 0x181825, crust = 0x11111B, surface0 = 0x313244, surface1 = 0x45475A,
                 surface2 = 0x585B70, overlay0 = 0x6C7086, text = 0xCDD6F4, subtext0 = 0xA6ADC8, red = 0xF38BA8;
}

static D2D1_COLOR_F Rgb(UINT32 rgb, float a = 1.0f) {
    return D2D1::ColorF(((rgb >> 16) & 0xFF) / 255.0f, ((rgb >> 8) & 0xFF) / 255.0f, (rgb & 0xFF) / 255.0f, a);
}

static D2D1_COLOR_F Ref(COLORREF c, float a = 1.0f) {
    return D2D1::ColorF(GetRValue(c) / 255.0f, GetGValue(c) / 255.0f, GetBValue(c) / 255.0f, a);
}

// Text formats by size and weight, made on first use.
static IDWriteTextFormat* Font(float size, bool bold) {
    static std::map<int, IDWriteTextFormat*> cache;
    int key = (int)std::lround(size * 10) * 2 + (bold ? 1 : 0);
    auto it = cache.find(key);
    if (it != cache.end()) return it->second;
    IDWriteTextFormat* f = nullptr;
    if (g_dw)
        g_dw->CreateTextFormat(L"Segoe UI Variable Text", nullptr, bold ? DWRITE_FONT_WEIGHT_SEMI_BOLD : DWRITE_FONT_WEIGHT_NORMAL,
                               DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, size, L"", &f);
    if (f) {
        f->SetWordWrapping(DWRITE_WORD_WRAPPING_NO_WRAP);
        f->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
        Ptr<IDWriteInlineObject> dots;
        if (SUCCEEDED(g_dw->CreateEllipsisTrimmingSign(f, dots.put()))) {
            DWRITE_TRIMMING trim{DWRITE_TRIMMING_GRANULARITY_CHARACTER, 0, 0};
            f->SetTrimming(&trim, dots.p);
        }
    }
    cache[key] = f;
    return f;
}

static float TextWidth(const std::wstring& s, IDWriteTextFormat* f) {
    if (!f || !g_dw) return 0;
    Ptr<IDWriteTextLayout> lay;
    if (FAILED(g_dw->CreateTextLayout(s.c_str(), (UINT32)s.size(), f, 4000, 100, lay.put()))) return 0;
    DWRITE_TEXT_METRICS m;
    lay->GetMetrics(&m);
    return m.widthIncludingTrailingWhitespace;
}

// A gradient brush from accent 1 to accent 2 across a rectangle.
static void GradientBrush(ID2D1RenderTarget* rt, const D2D1_RECT_F& r, float alpha, Ptr<ID2D1LinearGradientBrush>& out) {
    D2D1_GRADIENT_STOP stops[2] = {{0, Ref(g_cfg.accent1, alpha)}, {1, Ref(g_cfg.accent2, alpha)}};
    Ptr<ID2D1GradientStopCollection> coll;
    if (FAILED(rt->CreateGradientStopCollection(stops, 2, coll.put()))) return;
    rt->CreateLinearGradientBrush(D2D1::LinearGradientBrushProperties(D2D1::Point2F(r.left, r.top), D2D1::Point2F(r.right, r.bottom)),
                                  coll.p, out.put());
}

static void BringToFront(HWND h) {
    if (!SetForegroundWindow(h) || GetForegroundWindow() != h) {
        INPUT input{};
        SendInput(1, &input, sizeof(INPUT));
        SetForegroundWindow(h);
    }
    SetFocus(h);
}

static void Deliver(Shot&& shot, const std::wstring& app);

// ---------------------------------------------------------------------------
// Snap targets: every visible window, top first, and the controls inside it.
// ---------------------------------------------------------------------------

struct SnapWin {
    HWND hwnd;
    RECT r;  // Overlay coordinates.
    bool desktop;
    std::vector<RECT> kids;
};

struct MonInfo {
    RECT r;  // Overlay coordinates.
    float ui;
};

struct Overlay {
    HWND hwnd = nullptr;
    Shot shot;  // The frozen screen.
    ID2D1HwndRenderTarget* rt = nullptr;
    ID2D1Bitmap* bmp = nullptr;
    ID2D1SolidColorBrush* brush = nullptr;
    std::vector<SnapWin> wins;
    std::vector<MonInfo> mons;
    POINT cur{};
    bool pressed = false, dragging = false;
    POINT down{};
    RECT sel{};
    bool haveHover = false;
    RECT hover{};
    HWND hoverWin = nullptr;
    std::wstring hoverApp;
    int zoom = 10;
    DWORD copiedAt = 0;
    std::wstring copiedHex;
};
static Overlay g_ov;

static BOOL CALLBACK CollectKid(HWND h, LPARAM lp) {
    auto* w = (SnapWin*)lp;
    if (w->kids.size() >= 800 || !IsWindowVisible(h)) return TRUE;
    RECT r;
    if (!GetWindowRect(h, &r)) return TRUE;
    r.left -= g_ov.shot.x, r.right -= g_ov.shot.x, r.top -= g_ov.shot.y, r.bottom -= g_ov.shot.y;
    RECT c;
    if (!IntersectRect(&c, &r, &w->r) || c.right - c.left < 4 || c.bottom - c.top < 4 || EqualRect(&c, &w->r))
        return TRUE;
    w->kids.push_back(c);
    return TRUE;
}

static BOOL CALLBACK CollectWin(HWND h, LPARAM) {
    Overlay& o = g_ov;
    if (o.wins.size() >= 400 || !IsWindowVisible(h) || IsIconic(h) || IsCloaked(h) || IsOwnWindow(h)) return TRUE;
    LONG ex = GetWindowLongW(h, GWL_EXSTYLE);
    if (ex & WS_EX_TRANSPARENT) return TRUE;  // Click-through overlays.
    if (ex & WS_EX_LAYERED) {
        BYTE a = 255;
        DWORD flags = 0;
        if (GetLayeredWindowAttributes(h, nullptr, &a, &flags) && (flags & LWA_ALPHA) && a == 0) return TRUE;
    }
    RECT r = FrameRect(h);
    r.left -= o.shot.x, r.right -= o.shot.x, r.top -= o.shot.y, r.bottom -= o.shot.y;
    RECT screen{0, 0, o.shot.w, o.shot.h}, c;
    if (!IntersectRect(&c, &r, &screen) || c.right - c.left < 2 || c.bottom - c.top < 2) return TRUE;
    SnapWin w{h, c, IsDesktopWindow(h), {}};
    if (g_cfg.snapControls && !w.desktop) EnumChildWindows(h, CollectKid, (LPARAM)&w);
    o.wins.push_back(std::move(w));
    return TRUE;
}

static BOOL CALLBACK CollectMon(HMONITOR m, HDC, LPRECT, LPARAM) {
    Overlay& o = g_ov;
    MONITORINFO mi{sizeof(mi)};
    GetMonitorInfoW(m, &mi);
    UINT dx = 96, dy = 96;
    GetDpiForMonitor(m, MDT_EFFECTIVE_DPI, &dx, &dy);
    RECT r = mi.rcMonitor;
    r.left -= o.shot.x, r.right -= o.shot.x, r.top -= o.shot.y, r.bottom -= o.shot.y;
    o.mons.push_back({r, dx / 96.0f});
    return TRUE;
}

static const MonInfo& MonAt(POINT p) {
    Overlay& o = g_ov;
    for (auto& m : o.mons)
        if (PtInRect(&m.r, p)) return m;
    static MonInfo fallback{{0, 0, 1, 1}, 1.0f};
    if (o.mons.empty()) {
        fallback.r = {0, 0, o.shot.w, o.shot.h};
        return fallback;
    }
    return o.mons[0];
}

// The window under a point and the smallest control inside it that holds the point.
static const SnapWin* WinAt(POINT p) {
    for (auto& w : g_ov.wins)
        if (PtInRect(&w.r, p)) return &w;
    return nullptr;
}

static bool SnapAt(POINT p, RECT& out, HWND& win) {
    const SnapWin* w = WinAt(p);
    if (!w) return false;
    win = w->hwnd;
    if (w->desktop) {
        out = MonAt(p).r;
        return true;
    }
    out = w->r;
    long best = (long)(w->r.right - w->r.left) * (w->r.bottom - w->r.top);
    if (g_cfg.snapControls)
        for (auto& k : w->kids)
            if (PtInRect(&k, p)) {
                long a = (long)(k.right - k.left) * (k.bottom - k.top);
                if (a < best) best = a, out = k;
            }
    return true;
}

// ---------------------------------------------------------------------------
// The region screen
// ---------------------------------------------------------------------------

static void OvReleaseTarget() {
    Overlay& o = g_ov;
    if (o.brush) o.brush->Release();
    if (o.bmp) o.bmp->Release();
    if (o.rt) o.rt->Release();
    o.brush = nullptr;
    o.bmp = nullptr;
    o.rt = nullptr;
}

static bool OvEnsureTarget() {
    Overlay& o = g_ov;
    if (o.rt) return true;
    if (!g_d2d) return false;
    auto props = D2D1::RenderTargetProperties(D2D1_RENDER_TARGET_TYPE_DEFAULT,
                                              D2D1::PixelFormat(DXGI_FORMAT_B8G8R8A8_UNORM, D2D1_ALPHA_MODE_IGNORE), 96, 96);
    if (FAILED(g_d2d->CreateHwndRenderTarget(props, D2D1::HwndRenderTargetProperties(o.hwnd, D2D1::SizeU(o.shot.w, o.shot.h)),
                                             &o.rt)))
        return false;
    o.rt->SetTextAntialiasMode(D2D1_TEXT_ANTIALIAS_MODE_GRAYSCALE);
    auto bp = D2D1::BitmapProperties(D2D1::PixelFormat(DXGI_FORMAT_B8G8R8A8_UNORM, D2D1_ALPHA_MODE_IGNORE), 96, 96);
    if (FAILED(o.rt->CreateBitmap(D2D1::SizeU(o.shot.w, o.shot.h), o.shot.px.data(), o.shot.w * 4, bp, &o.bmp)) ||
        FAILED(o.rt->CreateSolidColorBrush(Rgb(mocha::crust), &o.brush))) {
        Wh_Log(L"Couldn't make the frozen screen (%d x %d)", o.shot.w, o.shot.h);
        OvReleaseTarget();
        return false;
    }
    return true;
}

static bool OvHighlight(RECT& r, bool& isDrag) {
    Overlay& o = g_ov;
    isDrag = o.dragging;
    if (o.dragging) {
        r = o.sel;
        return true;
    }
    if (o.haveHover) {
        r = o.hover;
        return true;
    }
    return false;
}

static void FillRound(ID2D1RenderTarget* rt, ID2D1SolidColorBrush* b, const D2D1_RECT_F& r, float rad, D2D1_COLOR_F c) {
    b->SetColor(c);
    rt->FillRoundedRectangle(D2D1::RoundedRect(r, rad, rad), b);
}

// A rounded pill with one line of text; returns its rectangle.
static D2D1_RECT_F DrawPill(ID2D1RenderTarget* rt, ID2D1SolidColorBrush* b, float x, float y, const std::wstring& text,
                            float ui, const RECT& bounds, bool above) {
    IDWriteTextFormat* f = Font(12.0f * ui, false);
    float pad = 9 * ui, h = 24 * ui, w = TextWidth(text, f) + pad * 2;
    if (above) y -= h;
    x = std::clamp(x, (float)bounds.left + 4, std::max((float)bounds.left + 4, (float)bounds.right - w - 4));
    y = std::clamp(y, (float)bounds.top + 4, std::max((float)bounds.top + 4, (float)bounds.bottom - h - 4));
    D2D1_RECT_F r{std::floor(x), std::floor(y), std::floor(x) + w, std::floor(y) + h};
    FillRound(rt, b, r, h / 2, Rgb(mocha::mantle, 0.94f));
    b->SetColor(Rgb(mocha::surface2, 0.9f));
    rt->DrawRoundedRectangle(D2D1::RoundedRect(D2D1::RectF(r.left + 0.5f, r.top + 0.5f, r.right - 0.5f, r.bottom - 0.5f), h / 2, h / 2), b, 1);
    b->SetColor(Rgb(mocha::text));
    rt->DrawText(text.c_str(), (UINT32)text.size(), f, D2D1::RectF(r.left + pad, r.top, r.right - pad + 2, r.bottom), b,
                 D2D1_DRAW_TEXT_OPTIONS_CLIP);
    return r;
}

static void OvDrawMagnifier(ID2D1RenderTarget* rt, ID2D1SolidColorBrush* b) {
    Overlay& o = g_ov;
    const MonInfo& mon = MonAt(o.cur);
    float ui = mon.ui;
    int n = g_cfg.magPixels, half = n / 2;
    int cell = std::max(2, (int)std::lround(o.zoom * ui));
    int box = n * cell;
    int gap = (int)std::lround(22 * ui), infoH = (int)std::lround(26 * ui), infoGap = (int)std::lround(6 * ui);
    int mx = o.cur.x + gap, my = o.cur.y + gap;
    if (mx + box > mon.r.right - 4) mx = o.cur.x - gap - box;
    if (my + box + infoGap + infoH > mon.r.bottom - 4) my = o.cur.y - gap - box - infoGap - infoH;
    mx = std::max(mx, (int)mon.r.left + 4);
    my = std::max(my, (int)mon.r.top + 4);
    float rad = 10 * ui;
    D2D1_RECT_F frame{(float)mx, (float)my, (float)(mx + box), (float)(my + box)};

    Ptr<ID2D1RoundedRectangleGeometry> geo;
    Ptr<ID2D1Layer> layer;
    g_d2d->CreateRoundedRectangleGeometry(D2D1::RoundedRect(frame, rad, rad), geo.put());
    rt->CreateLayer(nullptr, layer.put());
    if (geo && layer) rt->PushLayer(D2D1::LayerParameters(frame, geo.p), layer.p);
    b->SetColor(Rgb(mocha::crust));
    rt->FillRectangle(frame, b);
    // The source square, clipped to the screen; the part off the screen stays dark.
    int sx0 = o.cur.x - half, sy0 = o.cur.y - half;
    int cx0 = std::max(sx0, 0), cy0 = std::max(sy0, 0);
    int cx1 = std::min(sx0 + n, o.shot.w), cy1 = std::min(sy0 + n, o.shot.h);
    if (cx1 > cx0 && cy1 > cy0) {
        D2D1_RECT_F src{(float)cx0, (float)cy0, (float)cx1, (float)cy1};
        D2D1_RECT_F dst{(float)(mx + (cx0 - sx0) * cell), (float)(my + (cy0 - sy0) * cell),
                        (float)(mx + (cx1 - sx0) * cell), (float)(my + (cy1 - sy0) * cell)};
        rt->DrawBitmap(o.bmp, dst, 1.0f, D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR, src);
    }
    if (g_cfg.magGrid && cell >= 5) {
        b->SetColor(Rgb(mocha::crust, 0.28f));
        for (int i = 1; i < n; i++) {
            float x = (float)(mx + i * cell) + 0.5f, y = (float)(my + i * cell) + 0.5f;
            rt->DrawLine(D2D1::Point2F(x, (float)my), D2D1::Point2F(x, (float)(my + box)), b, 1);
            rt->DrawLine(D2D1::Point2F((float)mx, y), D2D1::Point2F((float)(mx + box), y), b, 1);
        }
    }
    D2D1_RECT_F mid{(float)(mx + half * cell), (float)(my + half * cell), (float)(mx + (half + 1) * cell),
                    (float)(my + (half + 1) * cell)};
    b->SetColor(Rgb(mocha::crust, 0.9f));
    rt->DrawRectangle(D2D1::RectF(mid.left - 0.5f, mid.top - 0.5f, mid.right + 0.5f, mid.bottom + 0.5f), b, 1);
    b->SetColor(D2D1::ColorF(1, 1, 1, 0.95f));
    rt->DrawRectangle(D2D1::RectF(mid.left + 0.5f, mid.top + 0.5f, mid.right - 0.5f, mid.bottom - 0.5f), b, 1);
    if (geo && layer) rt->PopLayer();
    Ptr<ID2D1LinearGradientBrush> grad;
    GradientBrush(rt, frame, 1.0f, grad);
    D2D1_RECT_F edge{frame.left + 0.75f, frame.top + 0.75f, frame.right - 0.75f, frame.bottom - 0.75f};
    if (grad) rt->DrawRoundedRectangle(D2D1::RoundedRect(edge, rad, rad), grad.p, 1.5f);

    // The color and position under the pointer.
    uint32_t v = 0;
    if (o.cur.x >= 0 && o.cur.y >= 0 && o.cur.x < o.shot.w && o.cur.y < o.shot.h)
        v = o.shot.px[(size_t)o.cur.y * o.shot.w + o.cur.x];
    WCHAR hex[16];
    swprintf_s(hex, L"#%02X%02X%02X", (v >> 16) & 0xFF, (v >> 8) & 0xFF, v & 0xFF);
    bool copied = o.copiedAt && GetTickCount() - o.copiedAt < 1500;
    WCHAR line[96];
    if (copied) swprintf_s(line, L"Copied %s", o.copiedHex.c_str());
    else swprintf_s(line, L"%s    %d, %d", hex, o.cur.x + o.shot.x, o.cur.y + o.shot.y);
    D2D1_RECT_F info{(float)mx, (float)(my + box + infoGap), (float)(mx + box), (float)(my + box + infoGap + infoH)};
    FillRound(rt, b, info, infoH / 2.0f, Rgb(mocha::mantle, 0.94f));
    b->SetColor(Rgb(mocha::surface2, 0.9f));
    rt->DrawRoundedRectangle(D2D1::RoundedRect(D2D1::RectF(info.left + 0.5f, info.top + 0.5f, info.right - 0.5f, info.bottom - 0.5f),
                                               infoH / 2.0f, infoH / 2.0f), b, 1);
    float sw = 12 * ui, sx = info.left + 8 * ui, sy = (info.top + info.bottom - sw) / 2;
    D2D1_RECT_F swatch{sx, sy, sx + sw, sy + sw};
    FillRound(rt, b, swatch, 3 * ui, Rgb(v & 0xFFFFFF));
    b->SetColor(Rgb(mocha::overlay0));
    rt->DrawRoundedRectangle(D2D1::RoundedRect(swatch, 3 * ui, 3 * ui), b, 1);
    b->SetColor(Rgb(copied ? 0xA6E3A1 : mocha::text));
    rt->DrawText(line, (UINT32)wcslen(line), Font(11.5f * ui, false),
                 D2D1::RectF(swatch.right + 7 * ui, info.top, info.right - 6 * ui, info.bottom), b, D2D1_DRAW_TEXT_OPTIONS_CLIP);
}

static void OvRender() {
    Overlay& o = g_ov;
    if (!o.hwnd || !OvEnsureTarget()) return;
    ID2D1HwndRenderTarget* rt = o.rt;
    ID2D1SolidColorBrush* b = o.brush;
    const Config& c = g_cfg;
    rt->BeginDraw();
    rt->SetTransform(D2D1::Matrix3x2F::Identity());
    D2D1_RECT_F all{0, 0, (float)o.shot.w, (float)o.shot.h};
    rt->DrawBitmap(o.bmp, all, 1.0f, D2D1_BITMAP_INTERPOLATION_MODE_NEAREST_NEIGHBOR, nullptr);

    RECT h;
    bool drag;
    bool have = OvHighlight(h, drag);
    float dim = c.dim / 100.0f;
    if (dim > 0) {
        b->SetColor(Rgb(mocha::crust, dim));
        if (have) {
            float L = (float)h.left, T = (float)h.top, R = (float)h.right, B = (float)h.bottom;
            rt->FillRectangle(D2D1::RectF(0, 0, all.right, T), b);
            rt->FillRectangle(D2D1::RectF(0, B, all.right, all.bottom), b);
            rt->FillRectangle(D2D1::RectF(0, T, L, B), b);
            rt->FillRectangle(D2D1::RectF(R, T, all.right, B), b);
        } else {
            rt->FillRectangle(all, b);
        }
    }
    const MonInfo& mon = MonAt(o.cur);
    float ui = mon.ui;
    if (c.crossLines) {
        b->SetColor(Ref(c.accent1, 0.55f));
        float x = o.cur.x + 0.5f, y = o.cur.y + 0.5f;
        rt->DrawLine(D2D1::Point2F(x, 0), D2D1::Point2F(x, all.bottom), b, 1);
        rt->DrawLine(D2D1::Point2F(0, y), D2D1::Point2F(all.right, y), b, 1);
    }
    if (have) {
        D2D1_RECT_F r{(float)h.left, (float)h.top, (float)h.right, (float)h.bottom};
        Ptr<ID2D1LinearGradientBrush> grad;
        GradientBrush(rt, r, 1.0f, grad);
        float t = std::max(1.0f, std::round(2 * ui));
        D2D1_RECT_F edge{r.left - t / 2, r.top - t / 2, r.right + t / 2, r.bottom + t / 2};
        if (grad) rt->DrawRectangle(edge, grad.p, t);
        if (c.showSize) {
            int w = h.right - h.left, hh = h.bottom - h.top;
            WCHAR size[48];
            swprintf_s(size, L"%d \u00D7 %d", w, hh);
            std::wstring text = !drag && !o.hoverApp.empty() ? o.hoverApp + L"   " + size : std::wstring(size);
            const MonInfo& hm = MonAt(POINT{h.left + 1, h.top + 1});
            float gapPx = 8 * ui;
            bool above = h.top - gapPx - 24 * ui > hm.r.top;
            float y = above ? h.top - gapPx : h.bottom + gapPx;
            if (!above && y + 24 * ui > hm.r.bottom) y = h.top + gapPx;  // No room either side: inside.
            DrawPill(rt, b, (float)h.left, y, text, ui, hm.r, above);
        }
    }
    if (c.magnifier) OvDrawMagnifier(rt, b);
    if (rt->EndDraw() == (HRESULT)D2DERR_RECREATE_TARGET) {
        OvReleaseTarget();
        InvalidateRect(g_ov.hwnd, nullptr, FALSE);
    }
}

static void OvUpdateHover() {
    Overlay& o = g_ov;
    if (!g_cfg.snapWindows) {
        o.haveHover = false;
        return;
    }
    RECT r;
    HWND win = nullptr;
    o.haveHover = SnapAt(o.cur, r, win);
    if (!o.haveHover) return;
    o.hover = r;
    if (win != o.hoverWin) {
        o.hoverWin = win;
        const SnapWin* w = WinAt(o.cur);
        o.hoverApp = w && w->desktop ? L"" : AppName(win);
    }
}

static void OvClose() {
    Overlay& o = g_ov;
    if (!o.hwnd) return;
    HWND h = o.hwnd;
    o.hwnd = nullptr;
    if (GetCapture() == h) ReleaseCapture();
    OvReleaseTarget();
    DestroyWindow(h);
    o.shot.px.clear();
    o.shot.px.shrink_to_fit();
    o.wins.clear();
    o.mons.clear();
}

static void OvFinish(RECT r) {
    Overlay& o = g_ov;
    Shot out = Crop(o.shot, r);
    if (out.w < 1 || out.h < 1) return;
    POINT mid{(r.left + r.right) / 2, (r.top + r.bottom) / 2};
    const SnapWin* w = WinAt(mid);
    std::wstring app = w && !w->desktop ? AppName(w->hwnd) : L"Screenshot";
    OvClose();
    Deliver(std::move(out), app);
}

static void OvSetCursor(POINT p) {
    Overlay& o = g_ov;
    o.cur = p;
    if (o.pressed && !o.dragging && (std::abs(p.x - o.down.x) > 3 || std::abs(p.y - o.down.y) > 3)) o.dragging = true;
    if (o.dragging)
        o.sel = {std::min(o.down.x, p.x), std::min(o.down.y, p.y), std::max(o.down.x, p.x) + 1, std::max(o.down.y, p.y) + 1};
    else OvUpdateHover();
    InvalidateRect(o.hwnd, nullptr, FALSE);
}

static void OvCopyColor() {
    Overlay& o = g_ov;
    if (o.cur.x < 0 || o.cur.y < 0 || o.cur.x >= o.shot.w || o.cur.y >= o.shot.h) return;
    uint32_t v = o.shot.px[(size_t)o.cur.y * o.shot.w + o.cur.x];
    WCHAR hex[16];
    swprintf_s(hex, L"#%02X%02X%02X", (v >> 16) & 0xFF, (v >> 8) & 0xFF, v & 0xFF);
    for (int i = 0; i < 10 && !OpenClipboard(o.hwnd); i++) Sleep(15);
    if (GetOpenClipboardWindow() != o.hwnd) return;
    EmptyClipboard();
    size_t bytes = (wcslen(hex) + 1) * sizeof(WCHAR);
    if (HGLOBAL g = GlobalAlloc(GMEM_MOVEABLE, bytes)) {
        memcpy(GlobalLock(g), hex, bytes);
        GlobalUnlock(g);
        if (!SetClipboardData(CF_UNICODETEXT, g)) GlobalFree(g);
    }
    CloseClipboard();
    o.copiedAt = GetTickCount();
    o.copiedHex = hex;
    SetTimer(o.hwnd, 1, 1600, nullptr);
    InvalidateRect(o.hwnd, nullptr, FALSE);
}

static LRESULT CALLBACK OverlayProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) {
    Overlay& o = g_ov;
    if (hwnd != o.hwnd) return DefWindowProcW(hwnd, msg, wp, lp);
    switch (msg) {
        case WM_PAINT:
            OvRender();
            ValidateRect(hwnd, nullptr);
            return 0;
        case WM_ERASEBKGND: return 1;
        case WM_SETCURSOR:
            SetCursor(LoadCursorW(nullptr, IDC_CROSS));
            return TRUE;
        case WM_MOUSEMOVE: OvSetCursor(POINT{GET_X_LPARAM(lp), GET_Y_LPARAM(lp)}); return 0;
        case WM_LBUTTONDOWN:
            o.pressed = true;
            o.dragging = false;
            o.down = POINT{GET_X_LPARAM(lp), GET_Y_LPARAM(lp)};
            SetCapture(hwnd);
            OvSetCursor(o.down);
            return 0;
        case WM_LBUTTONUP: {
            if (!o.pressed) return 0;
            o.pressed = false;
            if (GetCapture() == hwnd) ReleaseCapture();
            OvSetCursor(POINT{GET_X_LPARAM(lp), GET_Y_LPARAM(lp)});
            if (o.dragging) {
                RECT r = o.sel;
                o.dragging = false;
                OvFinish(r);
            } else if (o.haveHover) {
                OvFinish(o.hover);
            }
            return 0;
        }
        case WM_RBUTTONDOWN: return 0;
        case WM_RBUTTONUP:
            if (o.pressed || o.dragging) {
                o.pressed = o.dragging = false;
                if (GetCapture() == hwnd) ReleaseCapture();
                OvSetCursor(POINT{GET_X_LPARAM(lp), GET_Y_LPARAM(lp)});
            } else {
                OvClose();
            }
            return 0;
        case WM_MOUSEWHEEL:
            o.zoom = Clamp(o.zoom + (GET_WHEEL_DELTA_WPARAM(wp) > 0 ? 1 : -1), 4, 24);
            InvalidateRect(hwnd, nullptr, FALSE);
            return 0;
        case WM_KEYDOWN:
            switch (wp) {
                case VK_ESCAPE: OvClose(); return 0;
                case VK_RETURN:
                    if (o.dragging) {
                        RECT r = o.sel;
                        o.pressed = o.dragging = false;
                        OvFinish(r);
                    } else if (o.haveHover) {
                        OvFinish(o.hover);
                    }
                    return 0;
                case VK_LEFT:
                case VK_RIGHT:
                case VK_UP:
                case VK_DOWN: {
                    int step = (GetKeyState(VK_SHIFT) & 0x8000) ? 10 : 1;
                    int dx = wp == VK_LEFT ? -step : wp == VK_RIGHT ? step : 0;
                    int dy = wp == VK_UP ? -step : wp == VK_DOWN ? step : 0;
                    POINT p{Clamp(o.cur.x + dx, 0, o.shot.w - 1), Clamp(o.cur.y + dy, 0, o.shot.h - 1)};
                    SetCursorPos(p.x + o.shot.x, p.y + o.shot.y);
                    OvSetCursor(p);
                    return 0;
                }
                case 'C': OvCopyColor(); return 0;
            }
            return 0;
        case WM_TIMER:
            KillTimer(hwnd, wp);
            InvalidateRect(hwnd, nullptr, FALSE);
            return 0;
        case WM_DISPLAYCHANGE: OvClose(); return 0;
        case WM_DPICHANGED: return 0;  // The screen never moves or resizes.
        case WM_CLOSE: OvClose(); return 0;
    }
    return DefWindowProcW(hwnd, msg, wp, lp);
}

static void StartRegion() {
    Overlay& o = g_ov;
    if (o.hwnd) return;
    RECT vs = VirtualScreen();
    if (!CaptureRect(vs, false, o.shot)) {
        Wh_Log(L"Couldn't capture the screen");
        return;
    }
    o.wins.clear();
    o.mons.clear();
    EnumWindows(CollectWin, 0);
    EnumDisplayMonitors(nullptr, nullptr, CollectMon, 0);
    POINT c;
    GetCursorPos(&c);
    o.cur = {c.x - o.shot.x, c.y - o.shot.y};
    o.pressed = o.dragging = false;
    o.haveHover = false;
    o.hoverWin = nullptr;
    o.hoverApp.clear();
    o.zoom = g_cfg.magZoom;
    o.copiedAt = 0;
    o.hwnd = CreateWindowExW(WS_EX_TOPMOST | WS_EX_TOOLWINDOW, kOverlayClass, L"Seamless Snipper", WS_POPUP, o.shot.x,
                             o.shot.y, o.shot.w, o.shot.h, nullptr, nullptr, g_inst, nullptr);
    if (!o.hwnd) {
        o.shot.px.clear();
        return;
    }
    BOOL on = TRUE;
    DwmSetWindowAttribute(o.hwnd, DWMWA_TRANSITIONS_FORCEDISABLED, &on, sizeof(on));
    int corner = 1;  // DWMWCP_DONOTROUND
    DwmSetWindowAttribute(o.hwnd, DWMWA_WINDOW_CORNER_PREFERENCE, &corner, sizeof(corner));
    // Cloaked until the first frame is drawn, so the screen never flashes.
    DwmSetWindowAttribute(o.hwnd, DWMWA_CLOAK, &on, sizeof(on));
    ShowWindow(o.hwnd, SW_SHOW);
    OvUpdateHover();
    OvRender();
    if (!o.rt) {  // No drawing surface (GPU lost, or a desktop wider than D2D allows): no dead overlay.
        Wh_Log(L"Couldn't draw the region screen");
        OvClose();
        return;
    }
    ValidateRect(o.hwnd, nullptr);
    BOOL off = FALSE;
    DwmSetWindowAttribute(o.hwnd, DWMWA_CLOAK, &off, sizeof(off));
    BringToFront(o.hwnd);
}

// ---------------------------------------------------------------------------
// After a snip: clipboard now, file and card from a worker thread.
// ---------------------------------------------------------------------------

static bool PutClipboardImage(const Shot& s) {
    size_t bytes = (size_t)s.w * s.h * 4;
    HGLOBAL g = GlobalAlloc(GMEM_MOVEABLE, sizeof(BITMAPINFOHEADER) + bytes);
    if (!g) return false;
    auto* bh = (BITMAPINFOHEADER*)GlobalLock(g);
    *bh = {};
    bh->biSize = sizeof(*bh);
    bh->biWidth = s.w;
    bh->biHeight = s.h;  // Bottom-up, the form every app reads.
    bh->biPlanes = 1;
    bh->biBitCount = 32;
    bh->biCompression = BI_RGB;
    bh->biSizeImage = (DWORD)bytes;
    BYTE* dst = (BYTE*)(bh + 1);
    for (int y = 0; y < s.h; y++) memcpy(dst + (size_t)(s.h - 1 - y) * s.w * 4, &s.px[(size_t)y * s.w], (size_t)s.w * 4);
    GlobalUnlock(g);
    bool open = false;
    for (int i = 0; i < 20 && !(open = OpenClipboard(g_msgWnd)); i++) Sleep(15);
    if (!open) {
        GlobalFree(g);
        Wh_Log(L"The clipboard is busy; the snip wasn't copied");
        return false;
    }
    EmptyClipboard();
    bool ok = SetClipboardData(CF_DIB, g) != nullptr;
    if (!ok) GlobalFree(g);
    CloseClipboard();
    return ok;
}

struct SaveJob {
    Shot shot, thumb;
    std::wstring app, folder, subfolder, format, path, error;
    int quality = 92;
    bool save = false, toast = false, copied = false;
    SYSTEMTIME when{};
};

static DWORD WINAPI SaveThread(LPVOID param) {
    std::unique_ptr<SaveJob> job((SaveJob*)param);
    HRESULT com = CoInitializeEx(nullptr, COINIT_MULTITHREADED);
    if (job->save) {
        std::wstring dir = ExpandPath(job->folder);
        if (job->subfolder == L"day") {
            WCHAR d[16];
            swprintf_s(d, L"%02d-%02d-%02d", job->when.wDay, job->when.wMonth, job->when.wYear % 100);
            dir += L"\\" + std::wstring(d);
        } else if (job->subfolder == L"app") {
            dir += L"\\" + job->app;
        }
        int made = SHCreateDirectoryExW(nullptr, dir.c_str(), nullptr);
        if (made != ERROR_SUCCESS && made != ERROR_ALREADY_EXISTS && made != ERROR_FILE_EXISTS) {
            job->error = L"Couldn't make the folder";
            Wh_Log(L"Couldn't make %s (error %d)", dir.c_str(), made);
        } else {
            bool jpg = job->format == L"jpg";
            std::wstring stem = dir + L"\\" + job->app + L" " + TimeStamp(job->when), ext = jpg ? L".jpg" : L".png";
            // Reserve the name: two saves in the same minute must never pick the same file.
            std::wstring path = stem + ext;
            {
                static std::mutex nameLock;
                std::lock_guard<std::mutex> hold(nameLock);
                for (int i = 2; i < 1000; i++) {
                    HANDLE h = CreateFileW(path.c_str(), GENERIC_WRITE, 0, nullptr, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, nullptr);
                    if (h != INVALID_HANDLE_VALUE) {
                        CloseHandle(h);
                        break;
                    }
                    if (GetLastError() != ERROR_FILE_EXISTS) break;
                    path = stem + L" (" + std::to_wstring(i) + L")" + ext;
                }
            }
            HRESULT hr = EncodeFile(job->shot, path, jpg, job->quality);
            if (SUCCEEDED(hr)) job->path = path;
            else {
                DeleteFileW(path.c_str());  // The empty reserved file.
                job->error = L"Couldn't save the picture";
                Wh_Log(L"Couldn't save %s (0x%08X)", path.c_str(), (unsigned)hr);
            }
        }
    }
    if (job->toast) job->thumb = Downscale(job->shot, 640, 360);
    job->shot.px.clear();
    job->shot.px.shrink_to_fit();
    if (SUCCEEDED(com)) CoUninitialize();
    HWND msg = g_msgWnd;
    if (job->toast && msg && PostMessageW(msg, WM_SNP_SAVED, 0, (LPARAM)job.get())) job.release();
    g_saveThreads--;
    return 0;
}

static void PlayClick() {
    std::wstring wav = ExpandPath(L"%SystemRoot%\\Media\\Windows Navigation Start.wav");
    PlaySoundW(wav.c_str(), nullptr, SND_FILENAME | SND_ASYNC | SND_NODEFAULT);
}

static void Deliver(Shot&& shot, const std::wstring& app) {
    const Config& c = g_cfg;
    bool copied = c.copy && PutClipboardImage(shot);
    if (c.sound) PlayClick();
    if (!c.save && !c.toast) return;
    auto* job = new SaveJob;
    job->shot = std::move(shot);
    job->app = app.empty() ? L"Screenshot" : app;
    job->folder = c.folder;
    job->subfolder = c.subfolder;
    job->format = c.format;
    job->quality = c.jpgQuality;
    job->save = c.save;
    job->toast = c.toast;
    job->copied = copied;
    GetLocalTime(&job->when);
    g_saveThreads++;
    HANDLE t = CreateThread(nullptr, 0, SaveThread, job, 0, nullptr);
    if (t) CloseHandle(t);
    else {
        g_saveThreads--;
        delete job;
    }
}

// ---------------------------------------------------------------------------
// The preview card, bottom right
// ---------------------------------------------------------------------------

struct Toast {
    HWND hwnd = nullptr;
    ID2D1HwndRenderTarget* rt = nullptr;
    ID2D1Bitmap* bmp = nullptr;
    ID2D1SolidColorBrush* brush = nullptr;
    std::unique_ptr<SaveJob> job;
    UINT dpi = 96;
    float w = 300, h = 220, thumbW = 0, thumbH = 0;
    bool acrylic = false, hot = false;
};
static Toast g_toast;

static bool TransparencyOn() {
    DWORD v = 1, cb = sizeof(v);
    RegGetValueW(HKEY_CURRENT_USER, L"Software\\Microsoft\\Windows\\CurrentVersion\\Themes\\Personalize",
                 L"EnableTransparency", RRF_RT_REG_DWORD, nullptr, &v, &cb);
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
    ACCENT_POLICY ap{on ? 4 : 0, 2, 0xE01B1111u, 0};  // Mocha crust tint, as AABBGGRR.
    WINCOMPATTRDATA d{19, &ap, sizeof(ap)};
    return fn(hwnd, &d) != FALSE;
}

static void ToastRelease() {
    Toast& t = g_toast;
    if (t.brush) t.brush->Release();
    if (t.bmp) t.bmp->Release();
    if (t.rt) t.rt->Release();
    t.brush = nullptr;
    t.bmp = nullptr;
    t.rt = nullptr;
}

static void ToastHide() {
    Toast& t = g_toast;
    if (!t.hwnd) return;
    KillTimer(t.hwnd, kTimerToast);
    bool shown = IsWindowVisible(t.hwnd);
    ShowWindow(t.hwnd, SW_HIDE);
    if (shown) DwmFlush();  // Let the screen drop the card before the next capture.
    if (t.bmp) t.bmp->Release();
    t.bmp = nullptr;
    t.job.reset();
}

static void ToastPaint() {
    Toast& t = g_toast;
    if (!t.job) return;
    if (!t.rt) {
        RECT rc;
        GetClientRect(t.hwnd, &rc);
        auto props = D2D1::RenderTargetProperties(D2D1_RENDER_TARGET_TYPE_DEFAULT,
                                                  D2D1::PixelFormat(DXGI_FORMAT_B8G8R8A8_UNORM, D2D1_ALPHA_MODE_PREMULTIPLIED));
        if (FAILED(g_d2d->CreateHwndRenderTarget(props, D2D1::HwndRenderTargetProperties(t.hwnd, D2D1::SizeU(rc.right, rc.bottom)),
                                                 &t.rt)))
            return;
        t.rt->CreateSolidColorBrush(Rgb(mocha::text), &t.brush);
    }
    const Shot& th = t.job->thumb;
    if (!t.bmp && th.w > 0) {
        auto bp = D2D1::BitmapProperties(D2D1::PixelFormat(DXGI_FORMAT_B8G8R8A8_UNORM, D2D1_ALPHA_MODE_PREMULTIPLIED));
        t.rt->CreateBitmap(D2D1::SizeU(th.w, th.h), th.px.data(), th.w * 4, bp, &t.bmp);
    }
    ID2D1HwndRenderTarget* rt = t.rt;
    ID2D1SolidColorBrush* b = t.brush;
    rt->SetDpi((float)t.dpi, (float)t.dpi);
    rt->BeginDraw();
    rt->Clear(D2D1::ColorF(0, 0, 0, 0));
    D2D1_RECT_F r{0, 0, t.w, t.h};
    FillRound(rt, b, r, 8, Rgb(mocha::crust, t.acrylic ? 0.5f : 0.97f));
    Ptr<ID2D1LinearGradientBrush> grad;
    GradientBrush(rt, r, t.hot ? 1.0f : 0.75f, grad);
    if (grad) rt->DrawRoundedRectangle(D2D1::RoundedRect(D2D1::RectF(0.75f, 0.75f, t.w - 0.75f, t.h - 0.75f), 8, 8), grad.p, 1.5f);
    float pad = 12;
    D2D1_RECT_F box{pad, pad, t.w - pad, pad + t.thumbH};
    float dx = (box.right - box.left - t.thumbW) / 2;
    D2D1_RECT_F img{box.left + dx, box.top, box.left + dx + t.thumbW, box.top + t.thumbH};
    if (t.bmp) {
        Ptr<ID2D1RoundedRectangleGeometry> geo;
        Ptr<ID2D1Layer> layer;
        g_d2d->CreateRoundedRectangleGeometry(D2D1::RoundedRect(img, 6, 6), geo.put());
        rt->CreateLayer(nullptr, layer.put());
        if (geo && layer) rt->PushLayer(D2D1::LayerParameters(img, geo.p), layer.p);
        rt->DrawBitmap(t.bmp, img, 1.0f, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, nullptr);
        if (geo && layer) rt->PopLayer();
        b->SetColor(Rgb(mocha::surface2, 0.9f));
        rt->DrawRoundedRectangle(D2D1::RoundedRect(D2D1::RectF(img.left + 0.5f, img.top + 0.5f, img.right - 0.5f, img.bottom - 0.5f), 6, 6), b, 1);
    }
    std::wstring title, sub;
    const SaveJob& j = *t.job;
    if (!j.path.empty()) {
        title = j.path.substr(j.path.find_last_of(L'\\') + 1);
        sub = j.copied ? L"Saved and copied. Click to open it." : L"Saved. Click to open it.";
    } else if (!j.error.empty()) {
        title = j.error;
        sub = j.copied ? L"It was copied to the clipboard." : L"Check the folder in Snipper's settings.";
    } else {
        title = L"Snip copied";
        sub = L"Ready to paste.";
    }
    float ty = box.bottom + 8;
    b->SetColor(Rgb(j.error.empty() ? mocha::text : mocha::red));
    rt->DrawText(title.c_str(), (UINT32)title.size(), Font(13.0f, true), D2D1::RectF(pad, ty, t.w - pad, ty + 20), b,
                 D2D1_DRAW_TEXT_OPTIONS_CLIP);
    b->SetColor(Rgb(mocha::subtext0));
    rt->DrawText(sub.c_str(), (UINT32)sub.size(), Font(11.5f, false), D2D1::RectF(pad, ty + 20, t.w - pad, ty + 38), b,
                 D2D1_DRAW_TEXT_OPTIONS_CLIP);
    if (rt->EndDraw() == (HRESULT)D2DERR_RECREATE_TARGET) {
        ToastRelease();
        InvalidateRect(t.hwnd, nullptr, FALSE);
    }
}

static void OpenWithShell(const std::wstring& file) {
    ShellExecuteW(nullptr, L"open", file.c_str(), nullptr, nullptr, SW_SHOWNORMAL);
}

static void ShowInFolder(const std::wstring& file) {
    PIDLIST_ABSOLUTE pidl = ILCreateFromPathW(file.c_str());
    if (pidl) {
        SHOpenFolderAndSelectItems(pidl, 0, nullptr, 0);
        ILFree(pidl);
    }
}

static LRESULT CALLBACK ToastProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) {
    Toast& t = g_toast;
    switch (msg) {
        case WM_PAINT: {
            PAINTSTRUCT ps;
            BeginPaint(hwnd, &ps);
            ToastPaint();
            EndPaint(hwnd, &ps);
            return 0;
        }
        case WM_ERASEBKGND: return 1;
        case WM_SIZE:
            if (t.rt) t.rt->Resize(D2D1::SizeU(LOWORD(lp), HIWORD(lp)));
            return 0;
        case WM_MOUSEACTIVATE: return MA_NOACTIVATE;
        case WM_SETCURSOR:
            SetCursor(LoadCursorW(nullptr, IDC_HAND));
            return TRUE;
        case WM_MOUSEMOVE:
            if (!t.hot) {
                t.hot = true;
                TRACKMOUSEEVENT tme{sizeof(tme), TME_LEAVE, hwnd, 0};
                TrackMouseEvent(&tme);
                KillTimer(hwnd, kTimerToast);
                InvalidateRect(hwnd, nullptr, FALSE);
            }
            return 0;
        case WM_MOUSELEAVE:
            t.hot = false;
            if (t.job && IsWindowVisible(hwnd)) SetTimer(hwnd, kTimerToast, 1500, nullptr);
            InvalidateRect(hwnd, nullptr, FALSE);
            return 0;
        case WM_LBUTTONUP: {
            std::wstring path = t.job ? t.job->path : L"";
            ToastHide();
            if (!path.empty()) OpenWithShell(path);
            return 0;
        }
        case WM_RBUTTONUP: {
            std::wstring path = t.job ? t.job->path : L"";
            ToastHide();
            if (!path.empty()) ShowInFolder(path);
            else OpenWithShell(ExpandPath(g_cfg.folder));
            return 0;
        }
        case WM_TIMER:
            if (wp == kTimerToast) ToastHide();
            return 0;
        case WM_DESTROY:
            ToastRelease();
            t.job.reset();
            t.hwnd = nullptr;
            return 0;
    }
    return DefWindowProcW(hwnd, msg, wp, lp);
}

static void ShowToast(SaveJob* raw) {
    std::unique_ptr<SaveJob> job(raw);
    Toast& t = g_toast;
    if (!g_cfg.toast) return;
    if (!t.hwnd) {
        t.hwnd = CreateWindowExW(WS_EX_TOPMOST | WS_EX_TOOLWINDOW | WS_EX_NOACTIVATE, kToastClass, L"Seamless Snipper",
                                 WS_POPUP, 0, 0, 10, 10, nullptr, nullptr, g_inst, nullptr);
        if (!t.hwnd) return;
        int corner = 2;  // DWMWCP_ROUND
        DwmSetWindowAttribute(t.hwnd, DWMWA_WINDOW_CORNER_PREFERENCE, &corner, sizeof(corner));
        BOOL noFade = TRUE;  // Hides at once, so a quick next snip never catches it mid-fade.
        DwmSetWindowAttribute(t.hwnd, DWMWA_TRANSITIONS_FORCEDISABLED, &noFade, sizeof(noFade));
    }
    ToastHide();
    t.acrylic = TransparencyOn() && SetAcrylic(t.hwnd, true);
    if (!t.acrylic) SetAcrylic(t.hwnd, false);
    t.job = std::move(job);
    t.hot = false;
    POINT pt;
    GetCursorPos(&pt);
    HMONITOR mon = MonitorFromPoint(pt, MONITOR_DEFAULTTONEAREST);
    MONITORINFO mi{sizeof(mi)};
    GetMonitorInfoW(mon, &mi);
    UINT dx = 96, dy = 96;
    GetDpiForMonitor(mon, MDT_EFFECTIVE_DPI, &dx, &dy);
    t.dpi = dx;
    t.w = 300;
    float boxW = t.w - 24, boxH = 158;
    const Shot& th = t.job->thumb;
    if (th.w > 0 && th.h > 0) {
        float k = std::min(boxW / th.w, boxH / th.h);
        k = std::min(k, 1.0f);  // Never blow tiny snips up past 1:1.
        t.thumbW = std::max(24.0f, th.w * k);
        t.thumbH = std::max(24.0f, th.h * k);
    } else {
        t.thumbW = t.thumbH = 0;
    }
    t.h = 12 + t.thumbH + 8 + 38 + 10;
    int pw = MulDiv((int)std::ceil(t.w), t.dpi, 96), ph = MulDiv((int)std::ceil(t.h), t.dpi, 96);
    int margin = MulDiv(16, t.dpi, 96);
    int x = mi.rcWork.right - pw - margin, y = mi.rcWork.bottom - ph - margin;
    SetWindowPos(t.hwnd, HWND_TOPMOST, x, y, pw, ph, SWP_NOACTIVATE | SWP_SHOWWINDOW);
    InvalidateRect(t.hwnd, nullptr, FALSE);
    SetTimer(t.hwnd, kTimerToast, g_cfg.toastSeconds * 1000, nullptr);
}

// ---------------------------------------------------------------------------
// Snips
// ---------------------------------------------------------------------------

enum { MODE_REGION, MODE_FULL, MODE_WINDOW, MODE_MONITOR };

static BOOL CALLBACK FindAppWindow(HWND h, LPARAM lp) {
    if (!IsWindowVisible(h) || IsIconic(h) || IsCloaked(h) || IsOwnWindow(h) || IsShellWindow(h)) return TRUE;
    LONG ex = GetWindowLongW(h, GWL_EXSTYLE);
    if ((ex & (WS_EX_TOOLWINDOW | WS_EX_TRANSPARENT)) || GetWindow(h, GW_OWNER)) return TRUE;
    RECT r = FrameRect(h);
    if (r.right - r.left < 50 || r.bottom - r.top < 50) return TRUE;
    *(HWND*)lp = h;
    return FALSE;
}

// The window being used; from the tray menu that is the top app window, not the taskbar.
static HWND ActiveAppWindow() {
    HWND fg = GetForegroundWindow();
    if (fg) fg = GetAncestor(fg, GA_ROOT);
    if (fg && !IsShellWindow(fg) && !IsOwnWindow(fg) && !IsIconic(fg)) return fg;
    HWND found = nullptr;
    EnumWindows(FindAppWindow, (LPARAM)&found);
    return found;
}

static void Snip(int mode) {
    if (g_ov.hwnd) return;
    ToastHide();  // Never freeze the last card into the next snip.
    if (mode == MODE_REGION) {
        StartRegion();
        return;
    }
    RECT r = VirtualScreen();
    std::wstring app = L"Screenshot";
    if (mode == MODE_MONITOR) {
        POINT pt;
        GetCursorPos(&pt);
        MONITORINFO mi{sizeof(mi)};
        GetMonitorInfoW(MonitorFromPoint(pt, MONITOR_DEFAULTTONEAREST), &mi);
        r = mi.rcMonitor;
    } else if (mode == MODE_WINDOW) {
        HWND w = ActiveAppWindow();
        if (!w) return;
        RECT vs = VirtualScreen(), f = FrameRect(w);
        if (!IntersectRect(&r, &f, &vs)) return;
        app = AppName(w);
    }
    Shot s;
    if (!CaptureRect(r, g_cfg.cursor, s)) {
        Wh_Log(L"Couldn't capture the screen");
        return;
    }
    Deliver(std::move(s), app);
}

// ---------------------------------------------------------------------------
// Tray icon, menu and keys
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

// A rounded square in the blue to mauve gradient with the snip glyph, drawn with GDI.
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
    HFONT font = CreateFontW(-(int)(size * 0.66f), 0, 0, 0, FW_NORMAL, 0, 0, 0, DEFAULT_CHARSET, 0, 0,
                             ANTIALIASED_QUALITY, 0, L"Segoe Fluent Icons");
    HGDIOBJ oldFont = SelectObject(dc, font);
    SetBkMode(dc, TRANSPARENT);
    SetTextColor(dc, RGB(255, 255, 255));
    RECT r{0, 0, size, size};
    WCHAR g[2] = {(WCHAR)0xF406, 0};
    DrawTextW(dc, g, 1, &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE | DT_NOPREFIX);
    GdiFlush();
    SelectObject(dc, oldFont);
    DeleteObject(font);
    SelectObject(dc, old);
    DeleteDC(dc);

    const float c0[3] = {GetRValue(g_cfg.accent1) / 255.f, GetGValue(g_cfg.accent1) / 255.f, GetBValue(g_cfg.accent1) / 255.f};
    const float c1[3] = {GetRValue(g_cfg.accent2) / 255.f, GetGValue(g_cfg.accent2) / 255.f, GetBValue(g_cfg.accent2) / 255.f};
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
    const Config& c = g_cfg;
    NOTIFYICONDATAW nid{sizeof(nid)};
    nid.hWnd = g_msgWnd;
    nid.uID = kTrayId;
    if (!c.trayIcon) {
        if (g_trayAdded) Shell_NotifyIconW(NIM_DELETE, &nid);
        g_trayAdded = false;
        return;
    }
    HICON icon = MakeTrayIcon();
    nid.uFlags = NIF_MESSAGE | NIF_ICON | NIF_TIP | NIF_SHOWTIP;
    nid.uCallbackMessage = WM_SNP_TRAY;
    nid.hIcon = icon ? icon : LoadIconW(nullptr, IDI_APPLICATION);
    std::wstring tip = g_steppedAside ? L"Seamless Snipper: keys left to ShareX" : L"Seamless Snipper";
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

static bool ShareXRunning() {
    HANDLE snap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (snap == INVALID_HANDLE_VALUE) return false;
    PROCESSENTRY32W pe{sizeof(pe)};
    bool found = false;
    for (BOOL ok = Process32FirstW(snap, &pe); ok && !found; ok = Process32NextW(snap, &pe))
        found = !_wcsicmp(pe.szExeFile, L"ShareX.exe");
    CloseHandle(snap);
    return found;
}

static bool HotkeyMissing() {
    for (int i = 0; i < HK_COUNT; i++) {
        UINT mods, vk;
        if (!g_hotkeyOn[i] && Hotkey_Parse(g_cfg.hotkeys[i], mods, vk)) return true;
    }
    return false;
}

static void RegisterHotkeys() {
    const Config& c = g_cfg;
    bool aside = c.stepAside && ShareXRunning();
    bool trayChange = aside != g_steppedAside;
    g_steppedAside = aside;
    for (int i = 0; i < HK_COUNT; i++) {
        if (g_hotkeyOn[i]) UnregisterHotKey(g_msgWnd, i + 1);
        g_hotkeyOn[i] = false;
        UINT mods, vk;
        if (aside || c.hotkeys[i].empty()) continue;
        if (!Hotkey_Parse(c.hotkeys[i], mods, vk)) {
            Wh_Log(L"Key \"%s\" isn't one the mod understands", c.hotkeys[i].c_str());
            continue;
        }
        g_hotkeyOn[i] = RegisterHotKey(g_msgWnd, i + 1, mods | MOD_NOREPEAT, vk) != FALSE;
        if (!g_hotkeyOn[i]) Wh_Log(L"Key %s is taken by another app (error %lu)", c.hotkeys[i].c_str(), GetLastError());
    }
    // Watch for ShareX closing, or for a key another app let go of.
    if (c.stepAside || (!aside && HotkeyMissing())) SetTimer(g_msgWnd, kTimerKeys, 3000, nullptr);
    else KillTimer(g_msgWnd, kTimerKeys);
    if (trayChange) UpdateTray(false);
}

// Timer: take back only the keys another app has let go of, without dropping the working ones.
static void RetryMissingHotkeys() {
    for (int i = 0; i < HK_COUNT; i++) {
        UINT mods, vk;
        if (g_hotkeyOn[i] || !Hotkey_Parse(g_cfg.hotkeys[i], mods, vk)) continue;
        g_hotkeyOn[i] = RegisterHotKey(g_msgWnd, i + 1, mods | MOD_NOREPEAT, vk) != FALSE;
        if (g_hotkeyOn[i]) Wh_Log(L"Key %s is free again", g_cfg.hotkeys[i].c_str());
    }
}

static void ApplyConfig() {
    RegisterHotkeys();
    UpdateTray(false);
}

static void OpenSettings() { snpset::OpenSettingsWindow(); }

enum : UINT { IDM_REGION = 100, IDM_WINDOW, IDM_MONITOR, IDM_FULL, IDM_FOLDER, IDM_SETTINGS, IDM_POINTER };

static std::wstring MenuLabel(PCWSTR text, int hk) {
    std::wstring s = text;
    if (hk >= 0 && !g_cfg.hotkeys[hk].empty()) s += L"\t" + g_cfg.hotkeys[hk];
    return s;
}

static void ShowTrayMenu(POINT pt) {
    HMENU menu = CreatePopupMenu();
    AppendMenuW(menu, MF_STRING, IDM_REGION, MenuLabel(L"Snip a region", HK_REGION).c_str());
    AppendMenuW(menu, MF_STRING, IDM_WINDOW, MenuLabel(L"Snip the active window", HK_WINDOW).c_str());
    AppendMenuW(menu, MF_STRING, IDM_MONITOR, MenuLabel(L"Snip the active screen", HK_MONITOR).c_str());
    AppendMenuW(menu, MF_STRING, IDM_FULL, MenuLabel(L"Snip every screen", HK_FULL).c_str());
    if (magicptr::Enabled()) {
        std::wstring label = L"Ask about something on screen";
        std::wstring key = magicptr::HotkeyLabel();
        if (!key.empty()) label += L"\t" + key;
        AppendMenuW(menu, MF_SEPARATOR, 0, nullptr);
        AppendMenuW(menu, MF_STRING, IDM_POINTER, label.c_str());
    }
    AppendMenuW(menu, MF_SEPARATOR, 0, nullptr);
    AppendMenuW(menu, MF_STRING, IDM_FOLDER, L"Open the snips folder");
    AppendMenuW(menu, MF_STRING, IDM_SETTINGS, L"Settings");
    SetForegroundWindow(g_msgWnd);
    UINT cmd = TrackPopupMenuEx(menu, TPM_RETURNCMD | TPM_NONOTIFY | TPM_RIGHTBUTTON |
                                          (GetSystemMetrics(SM_MENUDROPALIGNMENT) ? TPM_RIGHTALIGN : TPM_LEFTALIGN),
                                pt.x, pt.y, g_msgWnd, nullptr);
    PostMessageW(g_msgWnd, WM_NULL, 0, 0);
    DestroyMenu(menu);
    int mode = cmd == IDM_REGION ? MODE_REGION : cmd == IDM_WINDOW ? MODE_WINDOW : cmd == IDM_MONITOR ? MODE_MONITOR
               : cmd == IDM_FULL ? MODE_FULL : -1;
    if (mode >= 0) {
        // Let the menu fade out first, so it isn't in the picture.
        g_deferredMode = mode;
        SetTimer(g_msgWnd, kTimerDeferred, 250, nullptr);
    } else if (cmd == IDM_FOLDER) {
        std::wstring dir = ExpandPath(g_cfg.folder);
        SHCreateDirectoryExW(nullptr, dir.c_str(), nullptr);
        OpenWithShell(dir);
    } else if (cmd == IDM_SETTINGS) {
        OpenSettings();
    } else if (cmd == IDM_POINTER) {
        magicptr::Summon();
    }
}

static void OnHotkey(int which) {
    switch (which) {
        case HK_REGION: Snip(MODE_REGION); break;
        case HK_FULL: Snip(MODE_FULL); break;
        case HK_WINDOW: Snip(MODE_WINDOW); break;
        case HK_MONITOR: Snip(MODE_MONITOR); break;
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
            if (HWND s = snpset::RecordingKeyWindow()) {
                // A key box is listening: give it the key (PrintScreen included) instead of snipping.
                PostMessageW(s, WM_KEYDOWN, HIWORD(lp), 1);
                return 0;
            }
            if (wp >= 1 && wp <= HK_COUNT) OnHotkey((int)wp - 1);
            return 0;
        case WM_TIMER:
            if (wp == kTimerKeys) {
                bool aside = g_cfg.stepAside && ShareXRunning();
                if (aside != g_steppedAside) RegisterHotkeys();
                else if (!aside && HotkeyMissing()) RetryMissingHotkeys();
            } else if (wp == kTimerDeferred) {
                KillTimer(hwnd, kTimerDeferred);
                int mode = g_deferredMode;
                g_deferredMode = -1;
                if (mode >= 0) Snip(mode);
            }
            return 0;
        case WM_SNP_TRAY:
            switch (LOWORD(lp)) {
                case NIN_SELECT:
                case NIN_KEYSELECT: OpenSettings(); break;
                case WM_CONTEXTMENU: ShowTrayMenu(POINT{GET_X_LPARAM(wp), GET_Y_LPARAM(wp)}); break;
            }
            return 0;
        case WM_SNP_SETTINGS:
            LoadSettings();
            ApplyConfig();
            if (HWND s = snpset::g_settingsWnd) PostMessageW(s, WM_APP + 1 /* WM_APP_SETTINGS_RELOAD */, 0, 0);
            return 0;
        case WM_SNP_SAVED:
            ShowToast((SaveJob*)lp);
            return 0;
    }
    return DefWindowProcW(hwnd, msg, wp, lp);
}

static DWORD WINAPI UiThread(LPVOID) {
    MSG msg;
    PeekMessageW(&msg, nullptr, WM_USER, WM_USER, PM_NOREMOVE);
    // Physical pixels everywhere, so every snip is sharp at any scaling.
    SetThreadDpiAwarenessContext(DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2);
    HRESULT com = CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED);
    EnableDarkMenus();
    D2D1_FACTORY_OPTIONS fo{};
    D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, __uuidof(ID2D1Factory), &fo, (void**)&g_d2d);
    DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory), (IUnknown**)&g_dw);
    g_inst = (HINSTANCE)windhawk_tool_mod::GetCurrentModuleHandle();
    WNDCLASSW wc{};
    wc.lpfnWndProc = MsgWndProc;
    wc.hInstance = g_inst;
    wc.lpszClassName = L"SeamlessSnipperMsg";
    RegisterClassW(&wc);
    WNDCLASSW oc{};
    oc.lpfnWndProc = OverlayProc;
    oc.hInstance = g_inst;
    oc.hCursor = LoadCursorW(nullptr, IDC_CROSS);
    oc.lpszClassName = kOverlayClass;
    RegisterClassW(&oc);
    WNDCLASSW tc{};
    tc.lpfnWndProc = ToastProc;
    tc.hInstance = g_inst;
    tc.hCursor = LoadCursorW(nullptr, IDC_HAND);
    tc.lpszClassName = kToastClass;
    RegisterClassW(&tc);
    g_msgWnd = CreateWindowExW(WS_EX_TOOLWINDOW, wc.lpszClassName, L"Seamless Snipper", WS_POPUP, 0, 0, 0, 0, nullptr,
                               nullptr, g_inst, nullptr);
    g_uiOk = g_msgWnd && g_d2d && g_dw;
    if (g_uiOk) {
        g_taskbarCreated = RegisterWindowMessageW(L"TaskbarCreated");
        ChangeWindowMessageFilterEx(g_msgWnd, g_taskbarCreated, MSGFLT_ALLOW, nullptr);
        LoadSettings();
        ApplyConfig();
        UpdateTray(true);
    }
    SetEvent(g_uiReady);
    if (g_uiOk)
        while (GetMessageW(&msg, nullptr, 0, 0) > 0) {
            TranslateMessage(&msg);
            DispatchMessageW(&msg);
        }
    OvClose();
    if (g_toast.hwnd) DestroyWindow(g_toast.hwnd);
    if (g_msgWnd) {
        KillTimer(g_msgWnd, kTimerKeys);
        KillTimer(g_msgWnd, kTimerDeferred);
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
    // Let running saves finish (their files matter), then drop the cards they posted.
    for (int i = 0; i < 150 && g_saveThreads > 0; i++) Sleep(100);
    HWND m = g_msgWnd;
    g_msgWnd = nullptr;  // Save threads finishing now drop their card.
    while (PeekMessageW(&msg, nullptr, WM_SNP_SAVED, WM_SNP_SAVED, PM_REMOVE)) delete (SaveJob*)msg.lParam;
    if (m) DestroyWindow(m);
    UnregisterClassW(wc.lpszClassName, g_inst);
    UnregisterClassW(oc.lpszClassName, g_inst);
    UnregisterClassW(tc.lpszClassName, g_inst);
    if (g_dw) g_dw->Release();
    if (g_d2d) g_d2d->Release();
    g_dw = nullptr;
    g_d2d = nullptr;
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
static bool g_pointerOk;

BOOL WhTool_ModInit() {
    g_singleInstance = CreateMutexW(nullptr, FALSE, L"Local\\SeamlessSnipperRunning");
    if (!g_singleInstance || GetLastError() == ERROR_ALREADY_EXISTS) {
        if (g_singleInstance) CloseHandle(g_singleInstance);
        g_singleInstance = nullptr;
        Wh_Log(L"Already running");
        return FALSE;
    }
    // Same menu look as Launchpad's. Hooks are applied when init returns, so this runs here.
    SeamlessMenuSkin::Init();
    g_uiReady = CreateEventW(nullptr, TRUE, FALSE, nullptr);
    g_uiThread = CreateThread(nullptr, 0, UiThread, nullptr, 0, &g_uiTid);
    if (g_uiThread) WaitForSingleObject(g_uiReady, 10000);
    CloseHandle(g_uiReady);
    g_uiReady = nullptr;
    if (!g_uiThread || !g_uiOk) {
        Wh_Log(L"Couldn't start");
        WhTool_ModUninit();
        return FALSE;
    }
    // Snipping still works if the pointer can't start.
    g_pointerOk = magicptr::ToolInit() != FALSE;
    if (!g_pointerOk) Wh_Log(L"Magic Pointer couldn't start");
    return TRUE;
}

void WhTool_ModSettingsChanged() {
    if (g_msgWnd) PostMessageW(g_msgWnd, WM_SNP_SETTINGS, 0, 0);
    if (g_pointerOk) magicptr::ToolSettingsChanged();
}

void WhTool_ModUninit() {
    if (g_pointerOk) magicptr::ToolUninit();
    g_pointerOk = false;
    snpset::CloseSettingsWindow();
    if (g_uiThread) {
        PostThreadMessageW(g_uiTid, WM_QUIT, 0, 0);
        if (WaitForSingleObject(g_uiThread, 15000) != WAIT_OBJECT_0) Wh_Log(L"UI thread did not stop in 15 s");
        CloseHandle(g_uiThread);
        g_uiThread = nullptr;
    }
    for (int i = 0; i < 150 && g_saveThreads > 0; i++) Sleep(100);
    Sleep(50);  // A save thread that just counted itself out is still returning from module code.
    SeamlessMenuSkin::Uninit();
    if (g_singleInstance) CloseHandle(g_singleInstance);
    g_singleInstance = nullptr;
}

// ===========================================================================
// Magic Pointer: the AI pointer, a tool inside Snipper. Based on Magic Pointer by
// Rono (github.com/rono-zeroseven). Generated by magic_pointer.py.
// ===========================================================================
#include <windowsx.h>
#include <shellapi.h>
#include <objbase.h>
#include <oleauto.h>
#include <exdisp.h>
#include <shldisp.h>
#include <shlobj.h>
#include <shobjidl.h>
#include <servprov.h>
#include <uiautomation.h>
#include <wincodec.h>
#include <winhttp.h>
#include <wincrypt.h>
#include <sddl.h>
#include <aclapi.h>
#include <imm.h>
#include <inspectable.h>
#include <winstring.h>
#include <algorithm>
#include <atomic>
#include <cmath>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <deque>
#include <functional>
#include <memory>
#include <mutex>
#include <string>
#include <utility>
#include <vector>

namespace magicptr {

////////////////////////////////////////////////////////////////////////////////
// Basics

constexpr float kPi = 3.14159265358979f;

constexpr UINT WM_APP_SETTINGS = WM_APP + 1;
constexpr UINT WM_APP_PICK = WM_APP + 2;
constexpr UINT WM_APP_AI = WM_APP + 3;
constexpr UINT WM_APP_OCR = WM_APP + 4;
constexpr UINT WM_APP_BROWSER = WM_APP + 5;
constexpr UINT WM_APP_TEMP_FILE = WM_APP + 6;
constexpr UINT WM_APP_FOREGROUND = WM_APP + 7;
constexpr UINT WM_APP_RIPPLE = WM_APP + 8;
constexpr UINT WM_APP_SUMMON = WM_APP + 40;

constexpr int kHotkeyActivate = 1;
constexpr int kHotkeyEscape = 2;

template <typename T>
void PostOwned(HWND hwnd, UINT message, std::unique_ptr<T> object) {
    T* raw = object.release();
    if (!hwnd ||
        !PostMessageW(hwnd, message, 0, reinterpret_cast<LPARAM>(raw))) {
        delete raw;
    }
}

template <typename T>
T GetProc(PCWSTR module, const char* name) {
    HMODULE handle = GetModuleHandleW(module);
    if (!handle) {
        handle = LoadLibraryExW(module, nullptr, LOAD_LIBRARY_SEARCH_SYSTEM32);
    }
    if (!handle) {
        return nullptr;
    }
    return reinterpret_cast<T>(
        reinterpret_cast<void*>(GetProcAddress(handle, name)));
}

struct OsVersion {
    DWORD major;
    DWORD minor;
    DWORD build;
};

const OsVersion& GetOsVersion() {
    static const OsVersion version = [] {
        OsVersion result{6, 1, 7601};
        using RtlGetVersion_t = LONG(WINAPI*)(OSVERSIONINFOW*);
        if (auto rtlGetVersion =
                GetProc<RtlGetVersion_t>(L"ntdll.dll", "RtlGetVersion")) {
            OSVERSIONINFOW info{};
            info.dwOSVersionInfoSize = sizeof(info);
            if (rtlGetVersion(&info) == 0) {
                result = {info.dwMajorVersion, info.dwMinorVersion,
                          info.dwBuildNumber};
            }
        }
        return result;
    }();
    return version;
}

bool IsWindows81OrLater() {
    const OsVersion& v = GetOsVersion();
    return v.major > 6 || (v.major == 6 && v.minor >= 3);
}

bool IsWindows10Build(DWORD build) {
    const OsVersion& v = GetOsVersion();
    return v.major > 10 || (v.major == 10 && v.build >= build);
}

bool IsWindows11() {
    return IsWindows10Build(22000);
}

template <typename T>
class ComPtr {
  public:
    ComPtr() = default;
    ~ComPtr() { Reset(); }
    ComPtr(const ComPtr&) = delete;
    ComPtr& operator=(const ComPtr&) = delete;
    ComPtr(ComPtr&& other) noexcept : ptr_(std::exchange(other.ptr_, nullptr)) {}
    ComPtr& operator=(ComPtr&& other) noexcept {
        if (this != &other) {
            Reset();
            ptr_ = std::exchange(other.ptr_, nullptr);
        }
        return *this;
    }

    T* Get() const { return ptr_; }
    T* operator->() const { return ptr_; }
    explicit operator bool() const { return ptr_ != nullptr; }
    T** Put() {
        Reset();
        return &ptr_;
    }
    void** PutVoid() { return reinterpret_cast<void**>(Put()); }
    void Reset() {
        if (ptr_) {
            ptr_->Release();
            ptr_ = nullptr;
        }
    }

  private:
    T* ptr_ = nullptr;
};

constexpr GUID kClsidCUIAutomation = {
    0xff48dba4, 0x60ef, 0x4201, {0xaa, 0x87, 0x54, 0x10, 0x3e, 0xef, 0x59, 0x4e}};
constexpr GUID kClsidCUIAutomation8 = {
    0xe22ad333, 0xb25f, 0x460c, {0x83, 0xd0, 0x05, 0x81, 0x10, 0x73, 0x95, 0xc9}};
constexpr GUID kIidIUIAutomation = {
    0x30cbe57d, 0xd9d0, 0x452a, {0xab, 0x13, 0x7a, 0xc5, 0xac, 0x48, 0x25, 0xee}};
constexpr GUID kIidIUIAutomation2 = {
    0x34723aff, 0x0c9d, 0x49d0, {0x98, 0x96, 0x7a, 0xb5, 0x2d, 0xf8, 0xcd, 0x8a}};
constexpr GUID kIidIUIAutomationValuePattern = {
    0xa94cd8b1, 0x0844, 0x4cd6, {0x9d, 0x2d, 0x64, 0x05, 0x37, 0xab, 0x39, 0xe9}};
constexpr GUID kClsidWICImagingFactory1 = {
    0xcacaf262, 0x9370, 0x4615, {0xa1, 0x3b, 0x9f, 0x55, 0x39, 0xda, 0x4c, 0x0a}};
constexpr GUID kIidIWICImagingFactory = {
    0xec5ec8a9, 0xc395, 0x4314, {0x9c, 0x77, 0x54, 0xd7, 0xa9, 0x35, 0xff, 0x70}};
constexpr GUID kGuidContainerFormatPng = {
    0x1b7cfaf4, 0x713f, 0x473c, {0xbb, 0xcd, 0x61, 0x37, 0x42, 0x5f, 0xae, 0xaf}};
constexpr GUID kGuidWICPixelFormat24bppBGR = {
    0x6fddc324, 0x4e03, 0x4bfe, {0xb1, 0x85, 0x3d, 0x77, 0x76, 0x8d, 0xc9, 0x0c}};
constexpr GUID kClsidShellWindows = {
    0x9ba05972, 0xf6a8, 0x11cf, {0xa4, 0x42, 0x00, 0xa0, 0xc9, 0x0a, 0x8f, 0x39}};
constexpr GUID kIidIShellWindows = {
    0x85cb6900, 0x4d95, 0x11cf, {0x96, 0x0c, 0x00, 0x80, 0xc7, 0xf4, 0xee, 0x85}};
constexpr GUID kSidSTopLevelBrowser = {
    0x4c96be40, 0x915c, 0x11cf, {0x99, 0xd3, 0x00, 0xaa, 0x00, 0x4a, 0xe8, 0x37}};
constexpr GUID kIidIShellBrowser = {
    0x000214e2, 0x0000, 0x0000, {0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x46}};
constexpr GUID kIidIServiceProvider = {
    0x6d5140c1, 0x7436, 0x11ce, {0x80, 0x34, 0x00, 0xaa, 0x00, 0x60, 0x09, 0xfa}};
constexpr GUID kIidIDispatch = {
    0x00020400, 0x0000, 0x0000, {0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x46}};
constexpr GUID kIidIShellFolderViewDual = {
    0xe7a1af80, 0x4d96, 0x11cf, {0x96, 0x0c, 0x00, 0x80, 0xc7, 0xf4, 0xee, 0x85}};
constexpr GUID kIidIShellDispatch2 = {
    0xa4c6892c, 0x3ba9, 0x11d2, {0x9d, 0xea, 0x00, 0xc0, 0x4f, 0xb1, 0x61, 0x62}};
constexpr GUID kGuidContainerFormatJpeg = {
    0x19e4a5aa, 0x5662, 0x4fc5, {0xa0, 0xc0, 0x17, 0x58, 0x02, 0x8e, 0x10, 0x57}};
constexpr GUID kIidIOcrEngineStatics = {
    0x5bffa85a, 0x3384, 0x3540, {0x99, 0x40, 0x69, 0x91, 0x20, 0xd4, 0x28, 0xa8}};
constexpr GUID kIidISoftwareBitmapStatics = {
    0xdf0385db, 0x672f, 0x4a9d, {0x80, 0x6e, 0xc2, 0x44, 0x2f, 0x34, 0x3e, 0x86}};
constexpr GUID kIidICryptographicBufferStatics = {
    0x320b7e22, 0x3cb0, 0x4cdf, {0x86, 0x63, 0x1d, 0x28, 0x91, 0x00, 0x65, 0xeb}};
constexpr GUID kIidIAsyncInfo = {
    0x00000036, 0x0000, 0x0000, {0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x46}};

double NowMs() {
    static const double msPerTick = [] {
        LARGE_INTEGER frequency;
        QueryPerformanceFrequency(&frequency);
        return 1000.0 / static_cast<double>(frequency.QuadPart);
    }();
    LARGE_INTEGER counter;
    QueryPerformanceCounter(&counter);
    return static_cast<double>(counter.QuadPart) * msPerTick;
}

inline float Clamp01(float v) {
    return v < 0.0f ? 0.0f : (v > 1.0f ? 1.0f : v);
}

inline double EaseOutCubic(double t) {
    t = std::clamp(t, 0.0, 1.0);
    const double u = 1.0 - t;
    return 1.0 - u * u * u;
}

inline double EaseOutBack(double t) {
    t = std::clamp(t, 0.0, 1.0);
    const double c1 = 1.70158;
    const double c3 = c1 + 1.0;
    const double u = t - 1.0;
    return 1.0 + c3 * u * u * u + c1 * u * u;
}

////////////////////////////////////////////////////////////////////////////////
// Monitors and DPI

UINT GetMonitorDpi(HMONITOR monitor) {
    using GetDpiForMonitor_t = HRESULT(WINAPI*)(HMONITOR, int, UINT*, UINT*);
    static auto getDpiForMonitor =
        GetProc<GetDpiForMonitor_t>(L"shcore.dll", "GetDpiForMonitor");
    UINT dpiX = 0;
    UINT dpiY = 0;
    if (getDpiForMonitor && monitor &&
        SUCCEEDED(getDpiForMonitor(monitor, 0 /* MDT_EFFECTIVE_DPI */, &dpiX,
                                   &dpiY)) &&
        dpiX) {
        return dpiX;
    }
    HDC dc = GetDC(nullptr);
    const int dpi = dc ? GetDeviceCaps(dc, LOGPIXELSX) : 96;
    if (dc) {
        ReleaseDC(nullptr, dc);
    }
    return dpi > 0 ? static_cast<UINT>(dpi) : 96;
}

float DpiScaleAt(POINT pt) {
    return GetMonitorDpi(MonitorFromPoint(pt, MONITOR_DEFAULTTONEAREST)) /
           96.0f;
}

RECT MonitorRectAt(POINT pt, bool workArea) {
    MONITORINFO info{};
    info.cbSize = sizeof(info);
    if (GetMonitorInfoW(MonitorFromPoint(pt, MONITOR_DEFAULTTONEAREST),
                        &info)) {
        return workArea ? info.rcWork : info.rcMonitor;
    }
    return {0, 0, GetSystemMetrics(SM_CXSCREEN),
            GetSystemMetrics(SM_CYSCREEN)};
}

RECT VirtualScreenRect() {
    const int x = GetSystemMetrics(SM_XVIRTUALSCREEN);
    const int y = GetSystemMetrics(SM_YVIRTUALSCREEN);
    return {x, y, x + GetSystemMetrics(SM_CXVIRTUALSCREEN),
            y + GetSystemMetrics(SM_CYVIRTUALSCREEN)};
}

POINT RectCenter(const RECT& rc) {
    return {rc.left + (rc.right - rc.left) / 2,
            rc.top + (rc.bottom - rc.top) / 2};
}

////////////////////////////////////////////////////////////////////////////////
// Strings

std::string ToUtf8(const wchar_t* text, size_t length) {
    if (!length) {
        return {};
    }
    const int size = WideCharToMultiByte(CP_UTF8, 0, text,
                                         static_cast<int>(length), nullptr, 0,
                                         nullptr, nullptr);
    std::string result(size > 0 ? size : 0, '\0');
    if (size > 0) {
        WideCharToMultiByte(CP_UTF8, 0, text, static_cast<int>(length),
                            result.data(), size, nullptr, nullptr);
    }
    return result;
}

std::string ToUtf8(const std::wstring& text) {
    return ToUtf8(text.data(), text.size());
}

std::wstring FromUtf8(const std::string& text) {
    if (text.empty()) {
        return {};
    }
    const int size = MultiByteToWideChar(CP_UTF8, 0, text.data(),
                                         static_cast<int>(text.size()),
                                         nullptr, 0);
    std::wstring result(size > 0 ? size : 0, L'\0');
    if (size > 0) {
        MultiByteToWideChar(CP_UTF8, 0, text.data(),
                            static_cast<int>(text.size()), result.data(),
                            size);
    }
    return result;
}

std::wstring Trim(const std::wstring& text) {
    size_t begin = 0;
    size_t end = text.size();
    while (begin < end && iswspace(text[begin])) {
        begin++;
    }
    while (end > begin && iswspace(text[end - 1])) {
        end--;
    }
    return text.substr(begin, end - begin);
}

bool ContainsNoCase(const std::string& haystack, const char* needle) {
    const size_t needleLength = strlen(needle);
    if (needleLength > haystack.size()) {
        return false;
    }
    for (size_t i = 0; i + needleLength <= haystack.size(); i++) {
        size_t j = 0;
        while (j < needleLength &&
               tolower(static_cast<unsigned char>(haystack[i + j])) ==
                   tolower(static_cast<unsigned char>(needle[j]))) {
            j++;
        }
        if (j == needleLength) {
            return true;
        }
    }
    return false;
}

void AppendJsonString(std::string& out, const std::string& text) {
    out += '"';
    for (unsigned char c : text) {
        switch (c) {
            case '"':
                out += "\\\"";
                break;
            case '\\':
                out += "\\\\";
                break;
            case '\n':
                out += "\\n";
                break;
            case '\r':
                out += "\\r";
                break;
            case '\t':
                out += "\\t";
                break;
            default:
                if (c < 0x20) {
                    char escaped[8];
                    snprintf(escaped, sizeof(escaped), "\\u%04x", c);
                    out += escaped;
                } else {
                    out += static_cast<char>(c);
                }
        }
    }
    out += '"';
}

std::string Base64Encode(const uint8_t* data, size_t size) {
    static const char kTable[] =
        "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    std::string out;
    out.reserve((size + 2) / 3 * 4);
    size_t i = 0;
    for (; i + 2 < size; i += 3) {
        const uint32_t v = (uint32_t(data[i]) << 16) |
                           (uint32_t(data[i + 1]) << 8) | data[i + 2];
        out += kTable[v >> 18];
        out += kTable[(v >> 12) & 63];
        out += kTable[(v >> 6) & 63];
        out += kTable[v & 63];
    }
    if (i < size) {
        uint32_t v = uint32_t(data[i]) << 16;
        if (i + 1 < size) {
            v |= uint32_t(data[i + 1]) << 8;
        }
        out += kTable[v >> 18];
        out += kTable[(v >> 12) & 63];
        out += i + 1 < size ? kTable[(v >> 6) & 63] : '=';
        out += '=';
    }
    return out;
}

////////////////////////////////////////////////////////////////////////////////
// JSON reader

struct Json;
struct JsonField;

struct Json {
    enum class Type { Null, Bool, Number, String, Array, Object };

    Type type = Type::Null;
    bool boolean = false;
    double number = 0;
    std::string string;
    std::vector<Json> items;
    std::vector<JsonField> fields;

    const Json* Get(const char* key) const;
    const Json* At(size_t index) const {
        return type == Type::Array && index < items.size() ? &items[index]
                                                           : nullptr;
    }
    bool IsString() const { return type == Type::String; }
};

struct JsonField {
    std::string key;
    Json value;
};

const Json* Json::Get(const char* key) const {
    if (type != Type::Object) {
        return nullptr;
    }
    for (const JsonField& field : fields) {
        if (field.key == key) {
            return &field.value;
        }
    }
    return nullptr;
}

class JsonReader {
  public:
    JsonReader(const char* begin, const char* end) : p_(begin), end_(end) {}

    bool ReadDocument(Json& out) {
        if (!ReadValue(out, 0)) {
            return false;
        }
        SkipSpace();
        return p_ == end_;
    }

  private:
    void SkipSpace() {
        while (p_ < end_ &&
               (*p_ == ' ' || *p_ == '\t' || *p_ == '\n' || *p_ == '\r')) {
            p_++;
        }
    }

    bool Literal(const char* word) {
        const size_t length = strlen(word);
        if (static_cast<size_t>(end_ - p_) < length ||
            memcmp(p_, word, length) != 0) {
            return false;
        }
        p_ += length;
        return true;
    }

    bool ReadHex4(uint32_t& out) {
        if (end_ - p_ < 4) {
            return false;
        }
        out = 0;
        for (int i = 0; i < 4; i++) {
            const char c = *p_++;
            out <<= 4;
            if (c >= '0' && c <= '9') {
                out |= c - '0';
            } else if (c >= 'a' && c <= 'f') {
                out |= c - 'a' + 10;
            } else if (c >= 'A' && c <= 'F') {
                out |= c - 'A' + 10;
            } else {
                return false;
            }
        }
        return true;
    }

    static void AppendUtf8(std::string& out, uint32_t cp) {
        if (cp < 0x80) {
            out += static_cast<char>(cp);
        } else if (cp < 0x800) {
            out += static_cast<char>(0xC0 | (cp >> 6));
            out += static_cast<char>(0x80 | (cp & 0x3F));
        } else if (cp < 0x10000) {
            out += static_cast<char>(0xE0 | (cp >> 12));
            out += static_cast<char>(0x80 | ((cp >> 6) & 0x3F));
            out += static_cast<char>(0x80 | (cp & 0x3F));
        } else {
            out += static_cast<char>(0xF0 | (cp >> 18));
            out += static_cast<char>(0x80 | ((cp >> 12) & 0x3F));
            out += static_cast<char>(0x80 | ((cp >> 6) & 0x3F));
            out += static_cast<char>(0x80 | (cp & 0x3F));
        }
    }

    bool ReadString(std::string& out) {
        p_++;  // Opening quote.
        while (p_ < end_) {
            const char c = *p_++;
            if (c == '"') {
                return true;
            }
            if (c != '\\') {
                out += c;
                continue;
            }
            if (p_ >= end_) {
                return false;
            }
            const char escaped = *p_++;
            switch (escaped) {
                case '"':
                case '\\':
                case '/':
                    out += escaped;
                    break;
                case 'b':
                    out += '\b';
                    break;
                case 'f':
                    out += '\f';
                    break;
                case 'n':
                    out += '\n';
                    break;
                case 'r':
                    out += '\r';
                    break;
                case 't':
                    out += '\t';
                    break;
                case 'u': {
                    uint32_t cp;
                    if (!ReadHex4(cp)) {
                        return false;
                    }
                    if (cp >= 0xD800 && cp <= 0xDBFF && end_ - p_ >= 6 &&
                        p_[0] == '\\' && p_[1] == 'u') {
                        const char* save = p_;
                        p_ += 2;
                        uint32_t low;
                        if (ReadHex4(low) && low >= 0xDC00 && low <= 0xDFFF) {
                            cp = 0x10000 + ((cp - 0xD800) << 10) +
                                 (low - 0xDC00);
                        } else {
                            p_ = save;
                        }
                    }
                    AppendUtf8(out, cp);
                    break;
                }
                default:
                    return false;
            }
        }
        return false;
    }

    bool ReadNumber(double& out) {
        char buffer[64];
        size_t length = 0;
        while (p_ < end_ && length < sizeof(buffer) - 1 &&
               ((*p_ >= '0' && *p_ <= '9') || *p_ == '-' || *p_ == '+' ||
                *p_ == '.' || *p_ == 'e' || *p_ == 'E')) {
            buffer[length++] = *p_++;
        }
        if (!length) {
            return false;
        }
        buffer[length] = '\0';
        out = strtod(buffer, nullptr);
        return true;
    }

    bool ReadValue(Json& out, int depth) {
        if (depth > 64) {
            return false;
        }
        SkipSpace();
        if (p_ >= end_) {
            return false;
        }
        const char c = *p_;
        if (c == '{') {
            p_++;
            out.type = Json::Type::Object;
            SkipSpace();
            if (p_ < end_ && *p_ == '}') {
                p_++;
                return true;
            }
            for (;;) {
                SkipSpace();
                JsonField field;
                if (p_ >= end_ || *p_ != '"' || !ReadString(field.key)) {
                    return false;
                }
                SkipSpace();
                if (p_ >= end_ || *p_ != ':') {
                    return false;
                }
                p_++;
                if (!ReadValue(field.value, depth + 1)) {
                    return false;
                }
                out.fields.push_back(std::move(field));
                SkipSpace();
                if (p_ < end_ && *p_ == ',') {
                    p_++;
                    continue;
                }
                if (p_ < end_ && *p_ == '}') {
                    p_++;
                    return true;
                }
                return false;
            }
        }
        if (c == '[') {
            p_++;
            out.type = Json::Type::Array;
            SkipSpace();
            if (p_ < end_ && *p_ == ']') {
                p_++;
                return true;
            }
            for (;;) {
                Json item;
                if (!ReadValue(item, depth + 1)) {
                    return false;
                }
                out.items.push_back(std::move(item));
                SkipSpace();
                if (p_ < end_ && *p_ == ',') {
                    p_++;
                    continue;
                }
                if (p_ < end_ && *p_ == ']') {
                    p_++;
                    return true;
                }
                return false;
            }
        }
        if (c == '"') {
            out.type = Json::Type::String;
            return ReadString(out.string);
        }
        if (c == 't') {
            out.type = Json::Type::Bool;
            out.boolean = true;
            return Literal("true");
        }
        if (c == 'f') {
            out.type = Json::Type::Bool;
            return Literal("false");
        }
        if (c == 'n') {
            return Literal("null");
        }
        out.type = Json::Type::Number;
        return ReadNumber(out.number);
    }

    const char* p_;
    const char* end_;
};

bool ParseJson(const std::string& text, Json& out) {
    return JsonReader(text.data(), text.data() + text.size()).ReadDocument(out);
}

////////////////////////////////////////////////////////////////////////////////
// Settings

enum class ThemeMode { Auto, Light, Dark };

struct Settings {
    bool shake = true;
    int sensitivity = 5;
    std::wstring hotkey;
    bool typeToAsk = true;
    std::vector<std::wstring> excludedApps;
    bool disableInFullscreen = true;
    std::wstring glowColor;
    bool glass = true;
    bool ripple = true;
    ThemeMode theme = ThemeMode::Auto;
    std::wstring language;
    int pointerSize = 100;
    std::wstring customCursor;
    int dim = 50;
    bool hint = true;
    int timeoutSec = 15;
    bool highlight = true;
    bool ocr = true;
    std::wstring browser;
    std::wstring browserPath;
    std::wstring apiKey;
    std::wstring model;
    bool suggestions = false;
    std::wstring translateTo;
};

std::wstring GetStringSetting(PCWSTR name) {
    PCWSTR value = Wh_GetStringSetting(name);
    std::wstring result = value;
    Wh_FreeStringSetting(value);
    return Trim(result);
}

std::wstring GetApiKeySetting(PCWSTR name) {
    std::wstring key;
    for (wchar_t c : GetStringSetting(name)) {
        if (c > L' ' && c < 0x7F) {
            key += c;
        }
    }
    return key;
}

// Windhawk's settings can be read by every account and sandboxed app on the
// PC, so the key is kept encrypted for this Windows account instead. A key
// typed into the setting is saved here and the box can then be cleared.
// "none" removes the saved key. Mod storage gets a non-secret status value.
constexpr PCWSTR kSavedKeyValue = L"apiKeyProtected";
constexpr char kSavedKeyEntropy[] = "magic-pointer-plus/api-key";

std::wstring LoadSavedApiKey() {
    BYTE blob[4096];
    const size_t size = Wh_GetBinaryValue(kSavedKeyValue, blob, sizeof(blob));
    if (!size || size > sizeof(blob)) {
        return {};
    }
    DATA_BLOB in{(DWORD)size, blob};
    DATA_BLOB entropy{(DWORD)(sizeof(kSavedKeyEntropy) - 1),
                      (BYTE*)kSavedKeyEntropy};
    DATA_BLOB out{};
    if (!CryptUnprotectData(&in, nullptr, &entropy, nullptr, nullptr,
                            CRYPTPROTECT_UI_FORBIDDEN, &out)) {
        return {};
    }
    std::wstring key;
    for (DWORD i = 0; i < out.cbData; i++) {
        const char c = (char)out.pbData[i];
        if (c > ' ' && c < 0x7F) {
            key += (wchar_t)c;
        }
    }
    SecureZeroMemory(out.pbData, out.cbData);
    LocalFree(out.pbData);
    return key;
}

bool SaveApiKey(const std::wstring& key) {
    std::string bytes;
    for (wchar_t c : key) {
        bytes += (char)c;
    }
    DATA_BLOB in{(DWORD)bytes.size(), (BYTE*)bytes.data()};
    DATA_BLOB entropy{(DWORD)(sizeof(kSavedKeyEntropy) - 1),
                      (BYTE*)kSavedKeyEntropy};
    DATA_BLOB out{};
    const BOOL ok = CryptProtectData(&in, nullptr, &entropy, nullptr, nullptr,
                                     CRYPTPROTECT_UI_FORBIDDEN, &out);
    SecureZeroMemory(bytes.data(), bytes.size());
    if (!ok) {
        return false;
    }
    const BOOL saved = Wh_SetBinaryValue(kSavedKeyValue, out.pbData, out.cbData);
    LocalFree(out.pbData);
    return saved;
}

std::wstring ResolveApiKey(const std::wstring& typed) {
    if (typed == L"none") {
        Wh_DeleteValue(kSavedKeyValue);
        Wh_SetStringValue(L"apiKeyStorage", L"removed");
        return {};
    }
    if (typed.empty()) {
        std::wstring saved = LoadSavedApiKey();
        Wh_SetStringValue(L"apiKeyStorage", saved.empty() ? L"empty" : L"encrypted-only");
        return saved;
    }
    if (LoadSavedApiKey() != typed &&
        (!SaveApiKey(typed) || LoadSavedApiKey() != typed)) {
        Wh_SetStringValue(L"apiKeyStorage", L"save-failed");
        return typed;
    }
    Wh_SetStringValue(L"apiKeyStorage", L"encrypted");
    return typed;
}

bool Enabled();

Settings LoadSettings() {
    Settings s;
    s.shake = Wh_GetIntSetting(L"pointerShake") != 0;
    const int sensitivity = Wh_GetIntSetting(L"pointerSensitivity");
    s.sensitivity = sensitivity <= 0 ? 5 : std::min(sensitivity, 10);
    s.hotkey = GetStringSetting(L"pointerHotkey");
    s.typeToAsk = Wh_GetIntSetting(L"pointerTypeToAsk") != 0;
    // One box in Snipper's settings: names separated by semicolons.
    const std::wstring apps = GetStringSetting(L"pointerSkipApps");
    for (size_t at = 0; at <= apps.size();) {
        size_t end = apps.find(L';', at);
        if (end == std::wstring::npos) end = apps.size();
        const std::wstring app = Trim(apps.substr(at, end - at));
        if (!app.empty()) s.excludedApps.push_back(app);
        at = end + 1;
    }
    s.disableInFullscreen = Wh_GetIntSetting(L"pointerFullscreen") != 0;
    s.glowColor = GetStringSetting(L"pointerGlow");
    s.glass = Wh_GetIntSetting(L"pointerGlass") != 0;
    s.ripple = Wh_GetIntSetting(L"pointerRipple") != 0;

    s.theme = ThemeMode::Dark;  // Mocha, always.
    s.language = L"auto";

    const int pointerSize = Wh_GetIntSetting(L"pointerSize");
    s.pointerSize = pointerSize <= 0 ? 100 : std::clamp(pointerSize, 50, 300);
    s.customCursor = GetStringSetting(L"pointerCursorFile");
    s.dim = std::clamp(Wh_GetIntSetting(L"pointerDim"), 0, 80);
    s.hint = Wh_GetIntSetting(L"pointerHint") != 0;
    s.timeoutSec = std::clamp(Wh_GetIntSetting(L"pointerTimeout"), 0, 3600);
    s.highlight = Wh_GetIntSetting(L"pointerHighlight") != 0;
    s.ocr = Wh_GetIntSetting(L"pointerOcr") != 0;
    s.browser = GetStringSetting(L"pointerBrowser");
    s.browserPath = GetStringSetting(L"pointerBrowserPath");
    s.apiKey = ResolveApiKey(GetApiKeySetting(L"pointerApiKey"));
    s.model = GetStringSetting(L"pointerModel");
    s.suggestions = Wh_GetIntSetting(L"pointerSuggestions") != 0;
    s.translateTo = GetStringSetting(L"pointerTranslateTo");
    if (!Enabled()) {  // Off in Snipper: nothing summons it.
        s.shake = false;
        s.hotkey.clear();
    }
    return s;
}

Settings g_settings;

enum class Provider { Gemini, OpenAi, Anthropic };

PCWSTR ProviderName(Provider provider) {
    switch (provider) {
        case Provider::OpenAi:
            return L"ChatGPT";
        case Provider::Anthropic:
            return L"Claude";
        case Provider::Gemini:
            break;
    }
    return L"Gemini";
}

Provider ProviderOfKey(const std::wstring& key) {
    if (_wcsnicmp(key.c_str(), L"sk-ant-", 7) == 0) {
        return Provider::Anthropic;
    }
    if (_wcsnicmp(key.c_str(), L"sk-", 3) == 0) {
        return Provider::OpenAi;
    }
    return Provider::Gemini;
}

bool ActiveProvider(const Settings& settings, Provider& provider) {
    if (settings.apiKey.empty()) {
        return false;
    }
    provider = ProviderOfKey(settings.apiKey);
    return true;
}

bool HasAiKey() {
    return !g_settings.apiKey.empty();
}

std::wstring AssistantName() {
    return ProviderName(ProviderOfKey(g_settings.apiKey));
}

bool SystemUsesDarkTheme() {
    DWORD value = 1;
    DWORD size = sizeof(value);
    if (RegGetValueW(
            HKEY_CURRENT_USER,
            L"Software\\Microsoft\\Windows\\CurrentVersion\\Themes\\Personalize",
            L"AppsUseLightTheme", RRF_RT_REG_DWORD, nullptr, &value,
            &size) != ERROR_SUCCESS) {
        return false;
    }
    return value == 0;
}

bool UseDarkTheme() { return true; }

////////////////////////////////////////////////////////////////////////////////
// Languages

#define MAGIC_POINTER_TEXTS(X) \
    X(HintText, L"Select anything to ask {0}") \
    X(HintTextTyping, L"Select anything or start typing to ask {0}") \
    X(Close, L"Close") \
    X(AskInGemini, L"Ask in Gemini") \
    X(SearchWithLens, L"Search with Google Lens") \
    X(TranslateTo, L"Translate to {0}") \
    X(CopyImage, L"Copy image") \
    X(CopyText, L"Copy text") \
    X(AddSelection, L"Add another selection") \
    X(WhatIsThis, L"What is this?") \
    X(ExplainThis, L"Explain this to me") \
    X(SummarizeThis, L"Summarize this for me") \
    X(AskPlaceholder, L"Ask about your selection…") \
    X(AskAnythingPlaceholder, L"Ask anything…") \
    X(FollowUpPlaceholder, L"Ask a follow-up…") \
    X(Thinking, L"Thinking…") \
    X(Copy, L"Copy") \
    X(SelectAll, L"Select all") \
    X(NoApiKeyHint, L"Add a Gemini, ChatGPT or Claude API key in the mod's settings to get answers right here.") \
    X(ImageCopied, L"Image copied") \
    X(ImageCopyFailed, L"Couldn't copy the image") \
    X(ImageCopyRetry, L"Couldn't copy the image. Try again.") \
    X(ReadingText, L"Still reading the text…") \
    X(NoTextFound, L"No text found in the selection") \
    X(TextCopied, L"Text copied") \
    X(TextCopyFailed, L"Couldn't copy the text") \
    X(AnswerCopied, L"Answer copied") \
    X(AnswerCopyFailed, L"Couldn't copy the answer") \
    X(OpeningLens, L"Opening Google Lens in your browser…") \
    X(OpeningGeminiOne, L"Opening Gemini and attaching your image…") \
    X(OpeningGeminiMany, L"Opening Gemini and attaching your images…") \
    X(OpeningGeminiText, L"Opening Gemini and adding your question…") \
    X(ClickBoxToAttach, L"Click Gemini's message box, then press Ctrl+V to attach the image.") \
    X(Stopped, L"Stopped.") \
    X(StoppedEarly, L"Stopped before the answer finished.") \
    X(RequestFailed, L"Couldn't start the request.") \
    X(DraftAddedOne, L"The image was added. Type your question in Gemini.") \
    X(DraftAddedMany, L"The images were added. Type your question in Gemini.") \
    X(QuestionInGemini, L"Your question is in Gemini.") \
    X(DraftPartial, L"Only {0} of {1} images could be confirmed. Check Gemini, and add the rest with Ctrl+V in its message box.") \
    X(ClipboardChangedOne, L"The clipboard changed before the image could be pasted: use Copy image, then press Ctrl+V in Gemini.") \
    X(ClipboardChangedMany, L"The clipboard changed before the images could be pasted. Ask in Gemini again to retry.") \
    X(IfNotAttachedOne, L"If the image isn't attached, click Gemini's message box and press Ctrl+V.") \
    X(IfNotAttachedMany, L"If the images aren't attached, click Gemini's message box and press Ctrl+V.") \
    X(ClickBoxOne, L"Click Gemini's message box and press Ctrl+V to attach the image. Your question is kept here.") \
    X(ClickBoxMany, L"Click Gemini's message box and press Ctrl+V to attach the images. Your question is kept here.") \
    X(ClickBoxText, L"Click Gemini's message box and type your question. Your question is kept here.") \
    X(BrowserFailedOne, L"Couldn't open the browser. The image is copied; paste it into Gemini with Ctrl+V.") \
    X(BrowserFailedMany, L"Couldn't open the browser. The images are copied; paste them into Gemini with Ctrl+V.") \
    X(BrowserFailedText, L"Couldn't open the browser.") \
    X(PageUnreadable, L"Magic Pointer couldn't read the page in your browser. If a notice is open over it, close it and click Ask in Gemini again.") \
    X(ErrKeyInvalid, L"Your {0} API key isn't valid. Check it in the mod's settings.") \
    X(ErrKeyForbidden, L"This API key can't use {0} (403). Check the key in the mod's settings.") \
    X(ErrModelMissing, L"The model \"{0}\" isn't available to your key. Pick another model in the mod's settings.") \
    X(ErrNoFreeQuota, L"Your Gemini plan has no free quota for \"{0}\". Choose the Fast model in the mod's settings, or add billing to your key.") \
    X(ErrNoCredit, L"Your {0} account has run out of credit. Add credit or a payment method to it, then try again.") \
    X(ErrTimeout, L"{0} didn't answer in time. Try again in a moment.") \
    X(ModelBusy, L"Your chosen model isn't available right now. A faster one is answering instead.") \
    X(ErrRateLimit, L"You've reached {0}'s rate limit for now. Try again in a moment.") \
    X(ErrServer, L"{0} is having trouble right now ({1}). Try again in a moment.") \
    X(ErrGeneric, L"{0} returned an error ({1}).") \
    X(ErrNoConnection, L"Couldn't receive {0}'s answer. Check your internet connection (error {1}). Try asking again.") \
    X(ErrInterrupted, L"The connection to {0} was interrupted. This answer is incomplete (error {1}). Try asking again.") \
    X(ErrInterruptedBy, L"{0} interrupted this answer: {1}") \
    X(ErrUnreadable, L"{0} returned an unreadable response. Try asking again.") \
    X(ErrOutputLimit, L"{0} reached its output limit. This answer is incomplete. Try asking for a shorter answer.") \
    X(ErrStoppedBecause, L"{0} stopped this answer ({1}). Try asking another way.") \
    X(ErrUnconfirmed, L"{0} stopped before confirming that the answer was complete. Try asking again.") \
    X(ErrNoAnswer, L"{0} didn't return an answer. Try asking another way.") \
    X(ErrCouldntReach, L"Couldn't reach {0}. Check your internet connection (error {1}).") \
    X(ErrStreaming, L"{0} returned a streaming error.") \
    X(LensSearching, L"Searching with Google Lens…") \
    X(LensUploadFailed, L"Couldn't upload automatically. The image is on your clipboard: paste it at lens.google.com.")

enum class Str : uint16_t {
#define X(id, text) id,
    MAGIC_POINTER_TEXTS(X)
#undef X
    Count
};

const PCWSTR kEnglishTexts[] = {
#define X(id, text) text,
    MAGIC_POINTER_TEXTS(X)
#undef X
};

static_assert(ARRAYSIZE(kEnglishTexts) == static_cast<size_t>(Str::Count));

struct TextEntry {
    Str id;
    PCWSTR text;
};

struct LanguageInfo {
    PCWSTR code;
    PCWSTR english;
    PCWSTR native;
    bool rtl;
    bool spaceless;
    const TextEntry* texts;
    size_t textCount;
};

const LanguageInfo* GetLanguages(size_t& count);

struct ActiveLanguage {
    const LanguageInfo* info;
    std::vector<PCWSTR> texts;
};

std::mutex g_languageMutex;
std::vector<std::unique_ptr<ActiveLanguage>> g_languageCache;
std::atomic<const ActiveLanguage*> g_language{nullptr};
std::atomic<bool> g_languageChosen{false};

const LanguageInfo* FindLanguage(const std::wstring& code) {
    size_t count = 0;
    const LanguageInfo* languages = GetLanguages(count);
    for (size_t i = 0; i < count; i++) {
        if (_wcsicmp(languages[i].code, code.c_str()) == 0) {
            return &languages[i];
        }
    }
    return nullptr;
}

const LanguageInfo* FindLanguageByEnglishName(const std::wstring& name) {
    size_t count = 0;
    const LanguageInfo* languages = GetLanguages(count);
    for (size_t i = 0; i < count; i++) {
        if (_wcsicmp(languages[i].english, name.c_str()) == 0) {
            return &languages[i];
        }
    }
    return nullptr;
}

const LanguageInfo* LanguageFromTag(std::wstring tag) {
    for (wchar_t& c : tag) {
        c = c >= L'A' && c <= L'Z' ? static_cast<wchar_t>(c + (L'a' - L'A')) : c;
    }
    const size_t dash = tag.find(L'-');
    const std::wstring primary = tag.substr(0, dash);
    const std::wstring region =
        dash == std::wstring::npos ? std::wstring() : tag.substr(dash);
    if (primary == L"zh") {
        const bool traditional = region.find(L"hant") != std::wstring::npos ||
                                 region.find(L"-tw") != std::wstring::npos ||
                                 region.find(L"-hk") != std::wstring::npos ||
                                 region.find(L"-mo") != std::wstring::npos;
        return FindLanguage(traditional ? L"zh-TW" : L"zh-CN");
    }
    if (primary == L"pt") {
        return FindLanguage(L"pt-BR");
    }
    if (primary == L"no" || primary == L"nn") {
        return FindLanguage(L"nb");
    }
    if (primary == L"iw") {
        return FindLanguage(L"he");
    }
    return FindLanguage(primary);
}

const LanguageInfo* WindowsLanguage() {
    ULONG count = 0;
    ULONG size = 0;
    if (GetUserPreferredUILanguages(MUI_LANGUAGE_NAME, &count, nullptr, &size) &&
        size > 0) {
        std::vector<WCHAR> names(size);
        if (GetUserPreferredUILanguages(MUI_LANGUAGE_NAME, &count, names.data(),
                                        &size)) {
            for (const WCHAR* name = names.data(); *name; name += wcslen(name) + 1) {
                if (const LanguageInfo* info = LanguageFromTag(name)) {
                    return info;
                }
            }
        }
    }
    WCHAR name[LOCALE_NAME_MAX_LENGTH]{};
    if (LCIDToLocaleName(MAKELCID(GetUserDefaultUILanguage(), SORT_DEFAULT), name,
                         ARRAYSIZE(name), 0)) {
        if (const LanguageInfo* info = LanguageFromTag(name)) {
            return info;
        }
    }
    return FindLanguage(L"en");
}

const ActiveLanguage* ActivateLanguage(const LanguageInfo* info) {
    std::lock_guard<std::mutex> lock(g_languageMutex);
    for (const auto& cached : g_languageCache) {
        if (cached->info == info) {
            return cached.get();
        }
    }
    auto language = std::make_unique<ActiveLanguage>();
    language->info = info;
    language->texts.assign(static_cast<size_t>(Str::Count), nullptr);
    for (size_t i = 0; i < info->textCount; i++) {
        language->texts[static_cast<size_t>(info->texts[i].id)] = info->texts[i].text;
    }
    g_languageCache.push_back(std::move(language));
    return g_languageCache.back().get();
}

void SetLanguage(const std::wstring& setting) {
    const LanguageInfo* info = nullptr;
    if (!setting.empty() && _wcsicmp(setting.c_str(), L"auto") != 0) {
        info = FindLanguage(setting);
    }
    g_languageChosen = info != nullptr;
    if (!info) {
        info = WindowsLanguage();
    }
    if (info) {
        g_language.store(ActivateLanguage(info), std::memory_order_release);
    }
}

PCWSTR Tr(Str id) {
    const ActiveLanguage* language = g_language.load(std::memory_order_acquire);
    const size_t index = static_cast<size_t>(id);
    if (language && language->texts[index]) {
        return language->texts[index];
    }
    return kEnglishTexts[index];
}

std::wstring TrFormat(Str id,
                      const std::wstring& first,
                      const std::wstring& second = {}) {
    const std::wstring text = Tr(id);
    std::wstring result;
    for (size_t i = 0; i < text.size(); i++) {
        if (text[i] == L'{' && i + 2 < text.size() && text[i + 2] == L'}' &&
            (text[i + 1] == L'0' || text[i + 1] == L'1')) {
            result += text[i + 1] == L'0' ? first : second;
            i += 2;
        } else {
            result += text[i];
        }
    }
    return result;
}

std::wstring JoinSentences(const std::wstring& first, const std::wstring& second) {
    const ActiveLanguage* language = g_language.load(std::memory_order_acquire);
    return language && language->info->spaceless ? first + second
                                                 : first + L" " + second;
}

const LanguageInfo* CurrentLanguage() {
    const ActiveLanguage* language = g_language.load(std::memory_order_acquire);
    return language ? language->info : nullptr;
}

bool UiIsRtl() {
    const LanguageInfo* language = CurrentLanguage();
    return language && language->rtl;
}

bool UiIsEnglish() {
    const LanguageInfo* language = CurrentLanguage();
    return !language || _wcsicmp(language->code, L"en") == 0;
}

bool StartsWithRtl(const std::wstring& text) {
    constexpr size_t kLimit = 64;
    WORD types[kLimit];
    const size_t length = std::min(text.size(), kLimit);
    if (length == 0 ||
        !GetStringTypeW(CT_CTYPE2, text.c_str(), static_cast<int>(length), types)) {
        return false;
    }
    for (size_t i = 0; i < length; i++) {
        if (types[i] == C2_LEFTTORIGHT) {
            return false;
        }
        if (types[i] == C2_RIGHTTOLEFT) {
            return true;
        }
    }
    return false;
}

////////////////////////////////////////////////////////////////////////////////
// Colors

struct Color {
    float r, g, b, a;
};

constexpr Color Rgb(int r, int g, int b, float a = 1.0f) {
    return {r / 255.0f, g / 255.0f, b / 255.0f, a};
}

inline Color WithAlpha(Color c, float a) {
    c.a = a;
    return c;
}

inline Color Mix(const Color& x, const Color& y, float t) {
    return {x.r + (y.r - x.r) * t, x.g + (y.g - x.g) * t,
            x.b + (y.b - x.b) * t, x.a + (y.a - x.a) * t};
}

constexpr Color kWhite = Rgb(255, 255, 255);
constexpr Color kBlack = Rgb(0, 0, 0);
constexpr Color kGoogleBlue = Rgb(66, 133, 244);
constexpr Color kGoogleRed = Rgb(234, 67, 53);
constexpr Color kGoogleYellow = Rgb(251, 188, 4);
constexpr Color kGoogleGreen = Rgb(52, 168, 83);

Color GoogleGradient(float t) {
    static const Color kStops[] = {kGoogleBlue, kGoogleRed, kGoogleYellow,
                                   kGoogleGreen};
    t -= floorf(t);
    const float x = t * 4.0f;
    const int i = static_cast<int>(x);
    float f = x - i;
    f = f * f * (3.0f - 2.0f * f);
    return Mix(kStops[i & 3], kStops[(i + 1) & 3], f);
}

struct Hsl {
    float h, s, l;  // Hue in degrees, saturation and lightness 0..1.
};

Hsl ToHsl(const Color& c) {
    const float mx = std::max({c.r, c.g, c.b});
    const float mn = std::min({c.r, c.g, c.b});
    Hsl out{0, 0, (mx + mn) * 0.5f};
    const float d = mx - mn;
    if (d > 1e-5f) {
        out.s = out.l > 0.5f ? d / (2.0f - mx - mn) : d / (mx + mn);
        if (mx == c.r) {
            out.h = (c.g - c.b) / d + (c.g < c.b ? 6.0f : 0.0f);
        } else if (mx == c.g) {
            out.h = (c.b - c.r) / d + 2.0f;
        } else {
            out.h = (c.r - c.g) / d + 4.0f;
        }
        out.h *= 60.0f;
    }
    return out;
}

Color FromHsl(Hsl hsl, float alpha = 1.0f) {
    hsl.h = fmodf(hsl.h, 360.0f);
    if (hsl.h < 0) {
        hsl.h += 360.0f;
    }
    hsl.s = Clamp01(hsl.s);
    hsl.l = Clamp01(hsl.l);
    const float q = hsl.l < 0.5f ? hsl.l * (1 + hsl.s) : hsl.l + hsl.s - hsl.l * hsl.s;
    const float p = 2 * hsl.l - q;
    auto channel = [&](float t) {
        t -= floorf(t);
        if (t < 1.0f / 6) return p + (q - p) * 6 * t;
        if (t < 0.5f) return q;
        if (t < 2.0f / 3) return p + (q - p) * (2.0f / 3 - t) * 6;
        return p;
    };
    const float h = hsl.h / 360.0f;
    return {channel(h + 1.0f / 3), channel(h), channel(h - 1.0f / 3), alpha};
}

struct GlowPalette {
    bool rainbow = false;  // The hue moves along the glow.
    bool duo = false;      // ...between from and to, instead of Google's four colors.
    Color color = kGoogleBlue;
    Color from = kGoogleBlue, to = kGoogleBlue;

    Color At(float t) const {
        if (duo) {
            return Mix(from, to, 0.5f - 0.5f * cosf(6.2831853f * t));
        }
        if (rainbow) {
            return GoogleGradient(t);
        }
        return color;
    }

    Color Base() const { return duo ? from : rainbow ? kGoogleBlue : color; }

    Color Accent(bool dark) const {
        Hsl hsl = ToHsl(Base());
        if (dark) {
            hsl.l = std::max(hsl.l, 0.68f);
        } else {
            hsl.l = std::min(hsl.l, 0.42f);
        }
        return FromHsl(hsl);
    }
};

GlowPalette MakeGlowPalette(Color base) {
    GlowPalette palette;
    palette.color = base;
    return palette;
}

GlowPalette ParseGlowColor(std::wstring text);

// "gradient": Snipper's selection colors, blue to mauve, sweeping back and forth.
GlowPalette SnipperGradient() {
    auto hex = [](PCWSTR name, Color fallback) {
        PCWSTR value = Wh_GetStringSetting(name);
        std::wstring text = value ? value : L"";
        if (value) Wh_FreeStringSetting(value);
        if (text.empty() || text[0] != L'#') return fallback;
        return ParseGlowColor(text).color;
    };
    GlowPalette palette;
    palette.rainbow = true;
    palette.duo = true;
    palette.from = hex(L"accentFrom", Rgb(0x89, 0xB4, 0xFA));
    palette.to = hex(L"accentTo", Rgb(0xCB, 0xA6, 0xF7));
    palette.color = palette.from;
    return palette;
}

GlowPalette ParseGlowColor(std::wstring text) {
    for (wchar_t& c : text) {
        c = towlower(c);
    }
    text = Trim(text);
    if (text.empty() || text == L"gradient") {
        return SnipperGradient();
    }
    const Color fallback = kGoogleBlue;
    if (text == L"rainbow" || text == L"google") {
        GlowPalette palette;
        palette.rainbow = true;
        return palette;
    }
    if (text.empty()) {
        return MakeGlowPalette(fallback);
    }
    if (text == L"accent" || text == L"system" || text == L"windows") {
        DWORD value = 0;
        DWORD size = sizeof(value);
        if (RegGetValueW(HKEY_CURRENT_USER, L"Software\\Microsoft\\Windows\\DWM",
                         L"AccentColor", RRF_RT_REG_DWORD, nullptr, &value,
                         &size) == ERROR_SUCCESS) {
            return MakeGlowPalette(Rgb(value & 0xFF, (value >> 8) & 0xFF,
                                       (value >> 16) & 0xFF));
        }
        return MakeGlowPalette(fallback);
    }
    static const struct {
        PCWSTR name;
        Color color;
    } kNames[] = {
        {L"blue", Rgb(66, 133, 244)},    {L"red", Rgb(234, 67, 53)},
        {L"green", Rgb(52, 168, 83)},    {L"yellow", Rgb(251, 188, 4)},
        {L"orange", Rgb(255, 128, 32)},  {L"purple", Rgb(150, 92, 255)},
        {L"violet", Rgb(150, 92, 255)},  {L"pink", Rgb(255, 92, 170)},
        {L"magenta", Rgb(232, 64, 220)}, {L"cyan", Rgb(0, 200, 230)},
        {L"teal", Rgb(0, 168, 150)},     {L"white", Rgb(240, 244, 255)},
        {L"gold", Rgb(240, 180, 40)},    {L"mint", Rgb(64, 220, 160)},
    };
    for (const auto& entry : kNames) {
        if (text == entry.name) {
            return MakeGlowPalette(entry.color);
        }
    }

    std::wstring hex = text;
    if (!hex.empty() && hex[0] == L'#') {
        hex.erase(0, 1);
    }
    const bool isHex =
        (hex.size() == 3 || hex.size() == 6) &&
        hex.find_first_not_of(L"0123456789abcdef") == std::wstring::npos;
    if (isHex) {
        const unsigned long v = wcstoul(hex.c_str(), nullptr, 16);
        if (hex.size() == 3) {
            return MakeGlowPalette(Rgb(((v >> 8) & 0xF) * 17, ((v >> 4) & 0xF) * 17,
                                       (v & 0xF) * 17));
        }
        return MakeGlowPalette(Rgb((v >> 16) & 0xFF, (v >> 8) & 0xFF, v & 0xFF));
    }

    int values[3];
    int count = 0;
    for (size_t i = 0; i < text.size() && count < 3;) {
        if (iswdigit(text[i])) {
            values[count++] = std::min(255, _wtoi(text.c_str() + i));
            while (i < text.size() && iswdigit(text[i])) {
                i++;
            }
        } else {
            i++;
        }
    }
    if (count == 3) {
        return MakeGlowPalette(Rgb(values[0], values[1], values[2]));
    }
    return MakeGlowPalette(fallback);
}

GlowPalette g_glow = MakeGlowPalette(kGoogleBlue);

constexpr double kGlowPeriodMs = 3200.0;

float GlowBreath(double now) {
    return 0.62f + 0.38f * sinf(static_cast<float>(
                               fmod(now, kGlowPeriodMs) / kGlowPeriodMs) * 2.0f * kPi);
}

inline uint32_t PackPremultiplied(const Color& c, float coverage) {
    const float a = Clamp01(c.a * coverage);
    if (a <= 0.0f) {
        return 0;
    }
    const uint32_t alpha = static_cast<uint32_t>(a * 255.0f + 0.5f);
    auto channel = [&](float v) {
        return std::min(alpha,
                        static_cast<uint32_t>(Clamp01(v) * a * 255.0f + 0.5f));
    };
    return (alpha << 24) | (channel(c.r) << 16) | (channel(c.g) << 8) |
           channel(c.b);
}

inline void BlendOver(uint32_t& dst, uint32_t src) {
    const uint32_t sa = src >> 24;
    if (sa == 0) {
        return;
    }
    if (sa == 255) {
        dst = src;
        return;
    }
    const uint32_t inv = 255 - sa;
    const uint32_t d = dst;
    uint32_t rb = (d & 0x00FF00FF) * inv + 0x00800080;
    rb = ((rb + ((rb >> 8) & 0x00FF00FF)) >> 8) & 0x00FF00FF;
    uint32_t ag = ((d >> 8) & 0x00FF00FF) * inv + 0x00800080;
    ag = (ag + ((ag >> 8) & 0x00FF00FF)) & 0xFF00FF00;
    dst = src + (rb | ag);
}

inline void BlendColor(uint32_t& dst, const Color& c, float coverage) {
    BlendOver(dst, PackPremultiplied(c, coverage));
}

////////////////////////////////////////////////////////////////////////////////
// Surfaces

class Surface {
  public:
    Surface() = default;
    ~Surface() { Reset(); }
    Surface(const Surface&) = delete;
    Surface& operator=(const Surface&) = delete;

    bool Resize(int width, int height) {
        width = std::max(width, 1);
        height = std::max(height, 1);
        if (!bits_ || width > stride_ || height > capacityHeight_) {
            Reset();
            const int capacityWidth = (width + 63) & ~63;
            const int capacityHeight = (height + 63) & ~63;

            BITMAPINFO info{};
            info.bmiHeader.biSize = sizeof(info.bmiHeader);
            info.bmiHeader.biWidth = capacityWidth;
            info.bmiHeader.biHeight = -capacityHeight;  // Top-down.
            info.bmiHeader.biPlanes = 1;
            info.bmiHeader.biBitCount = 32;
            info.bmiHeader.biCompression = BI_RGB;

            dc_ = CreateCompatibleDC(nullptr);
            if (!dc_) {
                return false;
            }
            void* bits = nullptr;
            bitmap_ = CreateDIBSection(dc_, &info, DIB_RGB_COLORS, &bits,
                                       nullptr, 0);
            if (!bitmap_ || !bits) {
                Reset();
                return false;
            }
            oldBitmap_ = SelectObject(dc_, bitmap_);
            bits_ = static_cast<uint32_t*>(bits);
            stride_ = capacityWidth;
            capacityHeight_ = capacityHeight;
        }
        width_ = width;
        height_ = height;
        Clear();
        return true;
    }

    void Reset() {
        if (dc_) {
            if (oldBitmap_) {
                SelectObject(dc_, oldBitmap_);
            }
            DeleteDC(dc_);
        }
        if (bitmap_) {
            DeleteObject(bitmap_);
        }
        dc_ = nullptr;
        bitmap_ = nullptr;
        oldBitmap_ = nullptr;
        bits_ = nullptr;
        width_ = height_ = stride_ = capacityHeight_ = 0;
    }

    void Clear() {
        for (int y = 0; y < height_; y++) {
            memset(Row(y), 0, static_cast<size_t>(width_) * 4);
        }
    }

    void Swap(Surface& other) {
        std::swap(dc_, other.dc_);
        std::swap(bitmap_, other.bitmap_);
        std::swap(oldBitmap_, other.oldBitmap_);
        std::swap(bits_, other.bits_);
        std::swap(width_, other.width_);
        std::swap(height_, other.height_);
        std::swap(stride_, other.stride_);
        std::swap(capacityHeight_, other.capacityHeight_);
    }

    bool Valid() const { return bits_ != nullptr; }
    int Width() const { return width_; }
    int Height() const { return height_; }
    int Stride() const { return stride_; }
    HDC Dc() const { return dc_; }
    uint32_t* Row(int y) { return bits_ + static_cast<size_t>(y) * stride_; }
    const uint32_t* Row(int y) const {
        return bits_ + static_cast<size_t>(y) * stride_;
    }

  private:
    HDC dc_ = nullptr;
    HBITMAP bitmap_ = nullptr;
    HGDIOBJ oldBitmap_ = nullptr;
    uint32_t* bits_ = nullptr;
    int width_ = 0;
    int height_ = 0;
    int stride_ = 0;
    int capacityHeight_ = 0;
};

////////////////////////////////////////////////////////////////////////////////
// Signed distance shapes

struct Vec2 {
    float x, y;
};

inline float SdRoundRect(float px,
                         float py,
                         float left,
                         float top,
                         float right,
                         float bottom,
                         float radius) {
    const float hw = (right - left) * 0.5f;
    const float hh = (bottom - top) * 0.5f;
    const float r = std::max(0.0f, std::min(radius, std::min(hw, hh)));
    const float qx = fabsf(px - (left + hw)) - hw + r;
    const float qy = fabsf(py - (top + hh)) - hh + r;
    const float ox = std::max(qx, 0.0f);
    const float oy = std::max(qy, 0.0f);
    return sqrtf(ox * ox + oy * oy) + std::min(std::max(qx, qy), 0.0f) - r;
}

float SdPolygon(const Vec2* v, int n, Vec2 p) {
    float d = (p.x - v[0].x) * (p.x - v[0].x) + (p.y - v[0].y) * (p.y - v[0].y);
    float sign = 1.0f;
    for (int i = 0, j = n - 1; i < n; j = i, i++) {
        const Vec2 e{v[j].x - v[i].x, v[j].y - v[i].y};
        const Vec2 w{p.x - v[i].x, p.y - v[i].y};
        const float t =
            Clamp01((w.x * e.x + w.y * e.y) / (e.x * e.x + e.y * e.y));
        const Vec2 b{w.x - e.x * t, w.y - e.y * t};
        d = std::min(d, b.x * b.x + b.y * b.y);
        const bool c1 = p.y >= v[i].y;
        const bool c2 = p.y < v[j].y;
        const bool c3 = e.x * w.y > e.y * w.x;
        if ((c1 && c2 && c3) || (!c1 && !c2 && !c3)) {
            sign = -sign;
        }
    }
    return sign * sqrtf(d);
}

inline float SdSegment(Vec2 p, Vec2 a, Vec2 b) {
    const Vec2 pa{p.x - a.x, p.y - a.y};
    const Vec2 ba{b.x - a.x, b.y - a.y};
    const float lengthSq = ba.x * ba.x + ba.y * ba.y;
    const float h =
        lengthSq > 0 ? Clamp01((pa.x * ba.x + pa.y * ba.y) / lengthSq) : 0.0f;
    const float dx = pa.x - ba.x * h;
    const float dy = pa.y - ba.y * h;
    return sqrtf(dx * dx + dy * dy);
}

inline float Erfc(float x) {
    const float z = fabsf(x);
    const float t = 1.0f / (1.0f + 0.3275911f * z);
    const float y =
        t *
        (0.254829592f +
         t * (-0.284496736f +
              t * (1.421413741f + t * (-1.453152027f + t * 1.061405429f)))) *
        expf(-z * z);
    return x >= 0 ? y : 2.0f - y;
}

inline float SoftCoverage(float distance, float sigma) {
    return 0.5f * Erfc(distance / (sigma * 1.41421356f));
}

inline float FastAtan2(float y, float x) {
    const float ax = fabsf(x);
    const float ay = fabsf(y);
    const float mx = std::max(ax, ay);
    const float mn = std::min(ax, ay);
    const float a = mx > 0 ? mn / mx : 0.0f;
    const float s = a * a;
    float r = ((-0.0464964749f * s + 0.15931422f) * s - 0.327622764f) * s * a +
              a;
    if (ay > ax) {
        r = 1.57079637f - r;
    }
    if (x < 0) {
        r = 3.14159274f - r;
    }
    return y < 0 ? -r : r;
}

template <typename DistanceFn, typename ColorFn>
void FillShape(Surface& s,
               float x0,
               float y0,
               float x1,
               float y1,
               DistanceFn distance,
               ColorFn color) {
    const int ix0 = std::max(0, static_cast<int>(floorf(x0)));
    const int iy0 = std::max(0, static_cast<int>(floorf(y0)));
    const int ix1 = std::min(s.Width(), static_cast<int>(ceilf(x1)));
    const int iy1 = std::min(s.Height(), static_cast<int>(ceilf(y1)));
    for (int y = iy0; y < iy1; y++) {
        uint32_t* row = s.Row(y);
        const float py = y + 0.5f;
        for (int x = ix0; x < ix1; x++) {
            const float px = x + 0.5f;
            const float coverage = Clamp01(0.5f - distance(px, py));
            if (coverage > 0.0f) {
                BlendColor(row[x], color(px, py), coverage);
            }
        }
    }
}

void FillRoundRect(Surface& s,
                   float l,
                   float t,
                   float r,
                   float b,
                   float radius,
                   Color c) {
    FillShape(
        s, l - 1, t - 1, r + 1, b + 1,
        [&](float x, float y) { return SdRoundRect(x, y, l, t, r, b, radius); },
        [&](float, float) { return c; });
}

void FillRoundRectGradient(Surface& s,
                           float l,
                           float t,
                           float r,
                           float b,
                           float radius,
                           Color top,
                           Color bottom) {
    const float height = std::max(1.0f, b - t);
    FillShape(
        s, l - 1, t - 1, r + 1, b + 1,
        [&](float x, float y) { return SdRoundRect(x, y, l, t, r, b, radius); },
        [&](float, float y) { return Mix(top, bottom, Clamp01((y - t) / height)); });
}

void StrokeRoundRect(Surface& s,
                     float l,
                     float t,
                     float r,
                     float b,
                     float radius,
                     float width,
                     Color c) {
    FillShape(
        s, l - width, t - width, r + width, b + width,
        [&](float x, float y) {
            return fabsf(SdRoundRect(x, y, l, t, r, b, radius)) - width * 0.5f;
        },
        [&](float, float) { return c; });
}

void StrokeRoundRectDashed(Surface& s,
                           float l,
                           float t,
                           float r,
                           float b,
                           float radius,
                           float width,
                           float dash,
                           Color c) {
    const float cx = (l + r) * 0.5f;
    const float cy = (t + b) * 0.5f;
    const float perimeter = 2.0f * ((r - l) + (b - t));
    const int dashes = std::max(4, static_cast<int>(perimeter / (dash * 2.0f)));
    FillShape(
        s, l - width, t - width, r + width, b + width,
        [&](float x, float y) {
            return fabsf(SdRoundRect(x, y, l, t, r, b, radius)) - width * 0.5f;
        },
        [&](float x, float y) {
            const float angle = FastAtan2(y - cy, x - cx) / (2.0f * kPi) + 0.5f;
            const float phase = angle * dashes;
            return (phase - floorf(phase)) < 0.5f ? c : WithAlpha(c, 0.0f);
        });
}

void StrokeCircle(Surface& s,
                  float cx,
                  float cy,
                  float radius,
                  float width,
                  Color c) {
    FillShape(
        s, cx - radius - width, cy - radius - width, cx + radius + width,
        cy + radius + width,
        [&](float x, float y) {
            return fabsf(sqrtf((x - cx) * (x - cx) + (y - cy) * (y - cy)) -
                         radius) -
                   width * 0.5f;
        },
        [&](float, float) { return c; });
}

void StrokeLine(Surface& s, Vec2 a, Vec2 b, float width, Color c) {
    const float half = width * 0.5f;
    FillShape(
        s, std::min(a.x, b.x) - width, std::min(a.y, b.y) - width,
        std::max(a.x, b.x) + width, std::max(a.y, b.y) + width,
        [&](float x, float y) { return SdSegment({x, y}, a, b) - half; },
        [&](float, float) { return c; });
}

void FillPolygon(Surface& s, const Vec2* points, int count, float round, Color c) {
    float x0 = points[0].x, y0 = points[0].y, x1 = x0, y1 = y0;
    for (int i = 1; i < count; i++) {
        x0 = std::min(x0, points[i].x);
        y0 = std::min(y0, points[i].y);
        x1 = std::max(x1, points[i].x);
        y1 = std::max(y1, points[i].y);
    }
    FillShape(
        s, x0 - round - 1, y0 - round - 1, x1 + round + 1, y1 + round + 1,
        [&](float x, float y) {
            return SdPolygon(points, count, {x, y}) - round;
        },
        [&](float, float) { return c; });
}

void DrawShadow(Surface& s,
                float l,
                float t,
                float r,
                float b,
                float radius,
                float sigma,
                Color c) {
    const float reach = sigma * 3.0f;
    const int ix0 = std::max(0, static_cast<int>(floorf(l - reach)));
    const int iy0 = std::max(0, static_cast<int>(floorf(t - reach)));
    const int ix1 = std::min(s.Width(), static_cast<int>(ceilf(r + reach)));
    const int iy1 = std::min(s.Height(), static_cast<int>(ceilf(b + reach)));
    for (int y = iy0; y < iy1; y++) {
        uint32_t* row = s.Row(y);
        for (int x = ix0; x < ix1; x++) {
            const float d = SdRoundRect(x + 0.5f, y + 0.5f, l, t, r, b, radius);
            const float coverage = SoftCoverage(d, sigma);
            if (coverage > 0.002f) {
                BlendColor(row[x], c, coverage);
            }
        }
    }
}

////////////////////////////////////////////////////////////////////////////////
// The Gemini sparkle

const Vec2* SparklePolygon(int* count) {
    constexpr int kPoints = 64;
    struct Shape {
        Vec2 points[kPoints];
        Shape() {
            const float exponent = 2.0f / 0.56f;
            for (int i = 0; i < kPoints; i++) {
                const float t = 2.0f * kPi * i / kPoints;
                const float c = cosf(t);
                const float s = sinf(t);
                points[i] = {copysignf(powf(fabsf(c), exponent), c),
                             copysignf(powf(fabsf(s), exponent), s)};
            }
        }
    };
    static const Shape shape;
    *count = kPoints;
    return shape.points;
}

inline float SdSparkle(Vec2 p, float cx, float cy, float radius, float angle) {
    struct Quadrant {
        Vec2 points[16];
        Vec2 edges[16];
        float inverseLength[16];
        Quadrant() {
            int count;
            const Vec2* polygon = SparklePolygon(&count);
            for (int i = 0; i < 16; i++) {
                points[i] = polygon[i];
                edges[i] = {polygon[i + 1].x - polygon[i].x,
                             polygon[i + 1].y - polygon[i].y};
                inverseLength[i] = 1.0f /
                    (edges[i].x * edges[i].x + edges[i].y * edges[i].y);
            }
        }
    };
    static const Quadrant quadrant;
    const float c = cosf(-angle);
    const float s = sinf(-angle);
    const float x = (p.x - cx) / radius;
    const float y = (p.y - cy) / radius;
    const Vec2 q{fabsf(x * c - y * s), fabsf(x * s + y * c)};
    float distanceSq = 1e9f;
    bool inside = false;
    for (int i = 0; i < 16; i++) {
        const Vec2 a = quadrant.points[i];
        const Vec2 e = quadrant.edges[i];
        const Vec2 w{q.x - a.x, q.y - a.y};
        const float t = Clamp01((w.x * e.x + w.y * e.y) * quadrant.inverseLength[i]);
        const Vec2 d{w.x - e.x * t, w.y - e.y * t};
        distanceSq = std::min(distanceSq, d.x * d.x + d.y * d.y);
        if (q.y >= a.y && q.y < a.y + e.y && e.x * w.y > e.y * w.x) {
            inside = true;
        }
    }
    return (inside ? -1.0f : 1.0f) * sqrtf(distanceSq) * radius;
}

void FillSparkleGradient(Surface& s,
                         float cx,
                         float cy,
                         float radius,
                         float angle,
                         float phase) {
    FillShape(
        s, cx - radius - 1, cy - radius - 1, cx + radius + 1, cy + radius + 1,
        [&](float x, float y) {
            return SdSparkle({x, y}, cx, cy, radius, angle);
        },
        [&](float x, float y) {
            const Color color =
                g_glow.At(phase + 0.5f * (x - cx + y - cy) / (radius * 2.0f));
            const float d = sqrtf((x - cx) * (x - cx) + (y - cy) * (y - cy));
            return Mix(color, kWhite, 0.55f * Clamp01(1.0f - d / (radius * 0.5f)));
        });
}

////////////////////////////////////////////////////////////////////////////////
// Images

struct Image {
    int width = 0;
    int height = 0;
    std::vector<uint32_t> pixels;  // Opaque BGRA, top-down.

    bool Empty() const { return pixels.empty(); }
};

Image DownscaleImage(const Image& src, int maxSide) {
    if (src.Empty()) {
        return {};
    }
    const int longest = std::max(src.width, src.height);
    if (longest <= maxSide) {
        return src;
    }
    Image dst;
    dst.width = std::max(1, static_cast<int>(int64_t(src.width) * maxSide / longest));
    dst.height = std::max(1, static_cast<int>(int64_t(src.height) * maxSide / longest));
    dst.pixels.resize(static_cast<size_t>(dst.width) * dst.height);
    for (int y = 0; y < dst.height; y++) {
        const int sy0 = static_cast<int>(int64_t(y) * src.height / dst.height);
        const int sy1 = std::max(
            sy0 + 1, static_cast<int>(int64_t(y + 1) * src.height / dst.height));
        for (int x = 0; x < dst.width; x++) {
            const int sx0 = static_cast<int>(int64_t(x) * src.width / dst.width);
            const int sx1 = std::max(
                sx0 + 1, static_cast<int>(int64_t(x + 1) * src.width / dst.width));
            uint32_t sumR = 0, sumG = 0, sumB = 0, count = 0;
            for (int sy = sy0; sy < sy1; sy++) {
                const uint32_t* row =
                    &src.pixels[static_cast<size_t>(sy) * src.width];
                for (int sx = sx0; sx < sx1; sx++) {
                    const uint32_t p = row[sx];
                    sumR += (p >> 16) & 0xFF;
                    sumG += (p >> 8) & 0xFF;
                    sumB += p & 0xFF;
                    count++;
                }
            }
            dst.pixels[static_cast<size_t>(y) * dst.width + x] =
                0xFF000000 | ((sumR / count) << 16) | ((sumG / count) << 8) |
                (sumB / count);
        }
    }
    return dst;
}

void DrawImageRounded(Surface& s,
                      const Image& image,
                      float l,
                      float t,
                      float r,
                      float b,
                      float radius,
                      Color letterbox) {
    if (image.Empty()) {
        return;
    }
    const float aspect = static_cast<float>(image.width) / image.height;
    const float boxAspect = (r - l) / (b - t);
    if (aspect > boxAspect * 2.0f || aspect < boxAspect * 0.5f) {
        FillRoundRect(s, l, t, r, b, radius, letterbox);
        const float scale = std::min((r - l) / image.width, (b - t) / image.height);
        const float w = image.width * scale;
        const float h = image.height * scale;
        const float x = l + ((r - l) - w) * 0.5f;
        const float y = t + ((b - t) - h) * 0.5f;
        l = x;
        t = y;
        r = x + w;
        b = y + h;
        radius = std::min(radius * 0.35f, std::min(w, h) * 0.5f);
    }
    const float scale = std::max((r - l) / image.width, (b - t) / image.height);
    const float sourceX = (image.width - (r - l) / scale) * 0.5f;
    const float sourceY = (image.height - (b - t) / scale) * 0.5f;
    auto sample = [&](float u, float v) {
        u = std::clamp(u, 0.0f, image.width - 1.0f);
        v = std::clamp(v, 0.0f, image.height - 1.0f);
        const int x0 = static_cast<int>(u);
        const int y0 = static_cast<int>(v);
        const int x1 = std::min(x0 + 1, image.width - 1);
        const int y1 = std::min(y0 + 1, image.height - 1);
        const float fx = u - x0;
        const float fy = v - y0;
        auto px = [&](int x, int y) {
            return image.pixels[static_cast<size_t>(y) * image.width + x];
        };
        auto channel = [&](int shift) {
            const float top = ((px(x0, y0) >> shift) & 0xFF) * (1 - fx) +
                              ((px(x1, y0) >> shift) & 0xFF) * fx;
            const float bottom = ((px(x0, y1) >> shift) & 0xFF) * (1 - fx) +
                                 ((px(x1, y1) >> shift) & 0xFF) * fx;
            return (top * (1 - fy) + bottom * fy) / 255.0f;
        };
        return Color{channel(16), channel(8), channel(0), 1.0f};
    };
    FillShape(
        s, l, t, r, b,
        [&](float x, float y) { return SdRoundRect(x, y, l, t, r, b, radius); },
        [&](float x, float y) {
            return sample(sourceX + (x - l) / scale - 0.5f,
                          sourceY + (y - t) / scale - 0.5f);
        });
}

////////////////////////////////////////////////////////////////////////////////
// Text

class FontCache {
  public:
    void Init() {
        static const PCWSTR kUiFaces[] = {L"FiraCode Nerd Font", L"Segoe UI Variable Text",
                                          L"Segoe UI", L"Tahoma"};
        static const PCWSTR kMonoFaces[] = {L"FiraCode Nerd Font Mono", L"Cascadia Mono", L"Consolas",
                                            L"Courier New"};
        static const PCWSTR kIconFaces[] = {L"Segoe Fluent Icons",
                                            L"Segoe MDL2 Assets"};
        face_ = PickFace(kUiFaces, ARRAYSIZE(kUiFaces), true);
        monoFace_ = PickFace(kMonoFaces, ARRAYSIZE(kMonoFaces), true);
        iconFace_ = PickFace(kIconFaces, ARRAYSIZE(kIconFaces), false);
        iconGlyphs_.clear();
    }

    HFONT Get(int px, int weight, bool mono = false) {
        return Find(px, weight, mono ? 1 : 0);
    }

    HFONT Icons(int px) {
        return iconFace_.empty() ? nullptr : Find(px, FW_NORMAL, 2);
    }

    bool HasIcon(wchar_t glyph) {
        if (iconFace_.empty()) {
            return false;
        }
        for (const auto& known : iconGlyphs_) {
            if (known.first == glyph) {
                return known.second;
            }
        }
        bool has = false;
        if (HDC dc = CreateCompatibleDC(nullptr)) {
            HGDIOBJ old = SelectObject(dc, Icons(16));
            WORD index = 0xFFFF;
            has = GetGlyphIndicesW(dc, &glyph, 1, &index,
                                   GGI_MARK_NONEXISTING_GLYPHS) != GDI_ERROR &&
                  index != 0xFFFF;
            SelectObject(dc, old);
            DeleteDC(dc);
        }
        iconGlyphs_.push_back({glyph, has});
        return has;
    }

    void Clear() {
        for (const Entry& entry : entries_) {
            DeleteObject(entry.font);
        }
        entries_.clear();
    }

  private:
    struct Entry {
        int px;
        int weight;
        int kind;  // 0 = text, 1 = monospace, 2 = icons.
        HFONT font;
    };

    HFONT Find(int px, int weight, int kind) {
        px = std::max(px, 6);
        for (const Entry& entry : entries_) {
            if (entry.px == px && entry.weight == weight && entry.kind == kind) {
                return entry.font;
            }
        }
        const std::wstring& face = kind == 2 ? iconFace_ : kind == 1 ? monoFace_ : face_;
        HFONT font = CreateFontW(-px, 0, 0, 0, weight, FALSE, FALSE, FALSE,
                                 DEFAULT_CHARSET, OUT_TT_PRECIS,
                                 CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY,
                                 DEFAULT_PITCH | FF_DONTCARE, face.c_str());
        if (font) {
            entries_.push_back({px, weight, kind, font});
        }
        return font ? font : static_cast<HFONT>(GetStockObject(DEFAULT_GUI_FONT));
    }

    static int CALLBACK EnumFontProc(const LOGFONTW*,
                                     const TEXTMETRICW*,
                                     DWORD,
                                     LPARAM param) {
        *reinterpret_cast<bool*>(param) = true;
        return 0;
    }

    static std::wstring PickFace(const PCWSTR* faces, size_t count, bool fallbackToLast) {
        HDC dc = GetDC(nullptr);
        for (size_t i = 0; i < count; i++) {
            LOGFONTW lf{};
            lf.lfCharSet = DEFAULT_CHARSET;
            wcsncpy_s(lf.lfFaceName, faces[i], _TRUNCATE);
            bool found = false;
            EnumFontFamiliesExW(dc, &lf, EnumFontProc,
                                reinterpret_cast<LPARAM>(&found), 0);
            if (found) {
                ReleaseDC(nullptr, dc);
                return faces[i];
            }
        }
        ReleaseDC(nullptr, dc);
        return fallbackToLast ? faces[count - 1] : L"";
    }

    std::vector<Entry> entries_;
    std::vector<std::pair<wchar_t, bool>> iconGlyphs_;  // Which glyphs exist.
    std::wstring face_ = L"Segoe UI";
    std::wstring monoFace_ = L"Consolas";
    std::wstring iconFace_;
};

FontCache g_fonts;

struct WrappedTextLine {
    size_t start;
    size_t length;
    std::vector<int> extents;
};

class TextPainter {
  public:
    SIZE Measure(HFONT font, const std::wstring& text, int maxWidth, UINT flags) {
        EnsureMeasureDc();
        HGDIOBJ old = SelectObject(measureDc_, font);
        RECT rc{0, 0, std::max(maxWidth, 1), 0};
        DrawTextW(measureDc_, text.empty() ? L" " : text.c_str(),
                  text.empty() ? 1 : static_cast<int>(text.size()), &rc,
                  flags | DT_CALCRECT | DT_NOPREFIX | ReadingOrder(text));
        SelectObject(measureDc_, old);
        return {rc.right - rc.left, rc.bottom - rc.top};
    }

    int Width(HFONT font, const wchar_t* text, int length) {
        if (length <= 0) {
            return 0;
        }
        EnsureMeasureDc();
        HGDIOBJ old = SelectObject(measureDc_, font);
        SIZE size{};
        GetTextExtentPoint32W(measureDc_, text, length, &size);
        SelectObject(measureDc_, old);
        return size.cx;
    }

    void Extents(HFONT font, const std::wstring& text, std::vector<int>& out) {
        out.assign(text.size(), 0);
        if (text.empty()) {
            return;
        }
        EnsureMeasureDc();
        HGDIOBJ old = SelectObject(measureDc_, font);
        SIZE size{};
        GetTextExtentExPointW(measureDc_, text.c_str(),
                              static_cast<int>(text.size()), 0, nullptr,
                              out.data(), &size);
        SelectObject(measureDc_, old);
    }

    std::vector<WrappedTextLine> Wrap(HFONT font, const std::wstring& text, int width) {
        std::vector<WrappedTextLine> lines;
        size_t start = 0;
        while (start < text.size()) {
            const size_t newline = text.find(L'\n', start);
            const size_t end = newline == std::wstring::npos ? text.size() : newline;
            if (start == end) {
                lines.push_back({start, 0, {}});
                start++;
                continue;
            }
            std::vector<int> extents;
            Extents(font, text.substr(start, end - start), extents);
            size_t fit = 0;
            while (fit < extents.size() && extents[fit] <= std::max(width, 1)) {
                fit++;
            }
            if (fit < extents.size()) {
                if (fit > 0 && IS_HIGH_SURROGATE(text[start + fit - 1]) &&
                    IS_LOW_SURROGATE(text[start + fit])) {
                    fit--;
                }
                size_t word = fit;
                while (word > 0 && !iswspace(text[start + word - 1])) {
                    word--;
                }
                if (word > 0) {
                    fit = word;
                }
            }
            if (fit == 0) {
                fit = IS_HIGH_SURROGATE(text[start]) && start + 1 < end &&
                              IS_LOW_SURROGATE(text[start + 1]) ? 2 : 1;
            }
            fit = std::min(fit, end - start);
            extents.resize(fit);
            lines.push_back({start, fit, std::move(extents)});
            start += fit;
            if (start == end && newline != std::wstring::npos) {
                start++;
            }
        }
        return lines;
    }

    void Draw(Surface& dst,
              HFONT font,
              const std::wstring& text,
              RECT layout,
              RECT clip,
              UINT flags,
              Color color) {
        RECT bounds{0, 0, dst.Width(), dst.Height()};
        IntersectRect(&clip, &clip, &bounds);
        const int w = clip.right - clip.left;
        const int h = clip.bottom - clip.top;
        if (w <= 0 || h <= 0 || text.empty() || !mask_.Resize(w, h)) {
            return;
        }
        HDC dc = mask_.Dc();
        HGDIOBJ old = SelectObject(dc, font);
        SetTextColor(dc, RGB(255, 255, 255));
        SetBkMode(dc, TRANSPARENT);
        OffsetRect(&layout, -clip.left, -clip.top);
        DrawTextW(dc, text.c_str(), static_cast<int>(text.size()), &layout,
                  flags | DT_NOPREFIX | ReadingOrder(text));
        SelectObject(dc, old);
        GdiFlush();

        const float luminance = color.r * 0.3f + color.g * 0.59f + color.b * 0.11f;
        const float gamma = luminance < 0.5f ? 0.8f : 1.0f;
        float lut[256];
        for (int i = 0; i < 256; i++) {
            lut[i] = powf(i / 255.0f, gamma);
        }
        for (int y = 0; y < h; y++) {
            const uint32_t* src = mask_.Row(y);
            uint32_t* row = dst.Row(clip.top + y) + clip.left;
            for (int x = 0; x < w; x++) {
                const uint32_t m = src[x] & 0xFF;
                if (m) {
                    BlendColor(row[x], color, lut[m]);
                }
            }
        }
    }

    void Draw(Surface& dst,
              HFONT font,
              const std::wstring& text,
              RECT layout,
              UINT flags,
              Color color) {
        Draw(dst, font, text, layout, layout, flags, color);
    }

    ~TextPainter() {
        if (measureDc_) {
            DeleteDC(measureDc_);
        }
    }

  private:
    static UINT ReadingOrder(const std::wstring& text) {
        return UiIsRtl() && StartsWithRtl(text) ? DT_RTLREADING : 0;
    }

    void EnsureMeasureDc() {
        if (!measureDc_) {
            measureDc_ = CreateCompatibleDC(nullptr);
        }
    }

    Surface mask_;
    HDC measureDc_ = nullptr;
};

////////////////////////////////////////////////////////////////////////////////
// Icons, drawn on a 16x16 design grid centered at (cx, cy)

enum class Icon { Close, Copy, Search, External, Send, Plus, Translate };

void DrawIcon(Surface& s, Icon icon, float cx, float cy, float scale, Color c) {
    const float u = scale;  // One design unit.
    auto P = [&](float x, float y) { return Vec2{cx + (x - 8) * u, cy + (y - 8) * u}; };
    const float w = 1.6f * u;
    switch (icon) {
        case Icon::Close:
            StrokeLine(s, P(4, 4), P(12, 12), w, c);
            StrokeLine(s, P(12, 4), P(4, 12), w, c);
            break;
        case Icon::Copy: {
            Vec2 a = P(5.5f, 5.5f);
            Vec2 b = P(14, 14);
            StrokeRoundRect(s, a.x, a.y, b.x, b.y, 2.0f * u, w * 0.9f, c);
            StrokeLine(s, P(2, 10.5f), P(2, 4), w * 0.9f, c);
            StrokeLine(s, P(4, 2), P(10.5f, 2), w * 0.9f, c);
            StrokeLine(s, P(2, 4), P(4, 2), w * 0.9f, c);
            break;
        }
        case Icon::Search: {
            Vec2 center = P(7, 7);
            StrokeCircle(s, center.x, center.y, 4.6f * u, w, c);
            StrokeLine(s, P(10.4f, 10.4f), P(14, 14), w * 1.1f, c);
            break;
        }
        case Icon::External:
            StrokeLine(s, P(4, 12), P(12, 4), w, c);
            StrokeLine(s, P(6, 4), P(12, 4), w, c);
            StrokeLine(s, P(12, 4), P(12, 10), w, c);
            break;
        case Icon::Send: {
            const Vec2 points[] = {P(2.5f, 2.5f), P(14.5f, 8), P(2.5f, 13.5f),
                                   P(5.2f, 8)};
            FillPolygon(s, points, 4, 0.6f * u, c);
            break;
        }
        case Icon::Plus:
            StrokeLine(s, P(8, 2.5f), P(8, 13.5f), w, c);
            StrokeLine(s, P(2.5f, 8), P(13.5f, 8), w, c);
            break;
        case Icon::Translate:
            StrokeLine(s, P(1, 14), P(4.5f, 6), w * 0.85f, c);
            StrokeLine(s, P(4.5f, 6), P(8, 14), w * 0.85f, c);
            StrokeLine(s, P(2.5f, 11), P(6.5f, 11), w * 0.85f, c);
            StrokeLine(s, P(12, 1.8f), P(12, 3.4f), w * 0.85f, c);
            StrokeLine(s, P(9.2f, 4.4f), P(14.8f, 4.4f), w * 0.85f, c);
            StrokeLine(s, P(10.6f, 4.4f), P(13.8f, 9), w * 0.85f, c);
            StrokeLine(s, P(13.4f, 4.4f), P(10.2f, 9), w * 0.85f, c);
            break;
    }
}

enum class Glyph : wchar_t {
    Close = 0xE711,
    Copy = 0xE8C8,
    Search = 0xE721,
    OpenInNew = 0xE8A7,
    Send = 0xE725,
    Add = 0xE710,
    Camera = 0xE722,
    Text = 0xE8D2,
    Translate = 0xE8C1,
};

void DrawGlyph(Surface& s,
               TextPainter& text,
               Glyph glyph,
               float cx,
               float cy,
               float scale,
               Color c) {
    const int px = static_cast<int>(lroundf(16 * scale));
    if (g_fonts.HasIcon(static_cast<wchar_t>(glyph))) {
        HFONT font = g_fonts.Icons(px);
        const LONG x = lroundf(cx);
        const LONG y = lroundf(cy);
        const RECT rc{x - px, y - px, x + px, y + px};
        text.Draw(s, font, std::wstring(1, static_cast<wchar_t>(glyph)), rc,
                  DT_CENTER | DT_VCENTER | DT_SINGLELINE, c);
        return;
    }
    Icon icon = Icon::Copy;
    switch (glyph) {
        case Glyph::Close:
            icon = Icon::Close;
            break;
        case Glyph::Search:
        case Glyph::Camera:
            icon = Icon::Search;
            break;
        case Glyph::OpenInNew:
            icon = Icon::External;
            break;
        case Glyph::Send:
            icon = Icon::Send;
            break;
        case Glyph::Add:
            icon = Icon::Plus;
            break;
        case Glyph::Translate:
            icon = Icon::Translate;
            break;
        case Glyph::Copy:
        case Glyph::Text:
            icon = Icon::Copy;
            break;
    }
    DrawIcon(s, icon, cx, cy, scale, c);
}

////////////////////////////////////////////////////////////////////////////////
// Layered windows

HINSTANCE g_instance;

constexpr WCHAR kMessageWindowClass[] = L"MagicPointerMessages_" WH_MOD_ID;
constexpr WCHAR kLayerWindowClass[] = L"MagicPointerLayer_" WH_MOD_ID;
constexpr WCHAR kOverlayWindowClass[] = L"MagicPointerOverlay_" WH_MOD_ID;
constexpr WCHAR kCardWindowClass[] = L"MagicPointerCard_" WH_MOD_ID;

bool g_layersChanged;

int g_styleVersion = 1;

void ConfigurePixelWindow(HWND hwnd, const Color* glass = nullptr);

class LayeredWindow {
  public:
    bool Create(bool clickThrough,
                bool activatable,
                PCWSTR className,
                void* param) {
        DWORD exStyle = WS_EX_LAYERED | WS_EX_TOPMOST | WS_EX_TOOLWINDOW;
        if (!activatable) {
            exStyle |= WS_EX_NOACTIVATE;
        }
        if (clickThrough) {
            exStyle |= WS_EX_TRANSPARENT;
        }
        hwnd_ = CreateWindowExW(exStyle, className, L"Magic Pointer", WS_POPUP,
                                0, 0, 1, 1, nullptr, nullptr, g_instance,
                                param);
        if (hwnd_) ConfigurePixelWindow(hwnd_);
        return hwnd_ != nullptr;
    }

    void Destroy() {
        if (hwnd_) {
            DestroyWindow(hwnd_);
            hwnd_ = nullptr;
        }
        visible_ = false;
    }

    bool Present(Surface& surface, int x, int y, BYTE alpha, const RECT* dirty = nullptr) {
        if (!hwnd_ || !surface.Valid()) {
            return false;
        }
        POINT dst{x, y};
        SIZE size{surface.Width(), surface.Height()};
        POINT src{0, 0};
        BLENDFUNCTION blend{AC_SRC_OVER, 0, alpha, AC_SRC_ALPHA};
        GdiFlush();  // Finish GDI text/drawing before uploading the DIB pixels.
        const bool partial = dirty && x == x_ && y == y_ && size.cx == width_ &&
                             size.cy == height_ && alpha == alpha_;
        UPDATELAYEREDWINDOWINFO info{sizeof(info), nullptr, &dst, &size, surface.Dc(),
                                     &src, 0, &blend, ULW_ALPHA, dirty};
        if (!(partial ? UpdateLayeredWindowIndirect(hwnd_, &info)
                      : UpdateLayeredWindow(hwnd_, nullptr, &dst, &size, surface.Dc(),
                                            &src, 0, &blend, ULW_ALPHA))) {
            return false;
        }
        x_ = x;
        y_ = y;
        width_ = size.cx;
        height_ = size.cy;
        alpha_ = alpha;
        return true;
    }

    void Move(int x, int y) {
        if (hwnd_ && (x != x_ || y != y_)) {
            SetWindowPos(hwnd_, nullptr, x, y, 0, 0,
                         SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE |
                             SWP_NOOWNERZORDER);
            x_ = x;
            y_ = y;
        }
    }

    void SetAlpha(BYTE alpha) {
        if (hwnd_ && alpha != alpha_) {
            BLENDFUNCTION blend{AC_SRC_OVER, 0, alpha, AC_SRC_ALPHA};
            UpdateLayeredWindow(hwnd_, nullptr, nullptr, nullptr, nullptr,
                                nullptr, 0, &blend, ULW_ALPHA);
            alpha_ = alpha;
        }
    }

    void Show(bool activate = false) {
        if (hwnd_ && !visible_) {
            SetWindowPos(hwnd_, HWND_TOPMOST, 0, 0, 0, 0,
                         SWP_NOMOVE | SWP_NOSIZE | SWP_SHOWWINDOW |
                             (activate ? 0 : SWP_NOACTIVATE));
            visible_ = true;
            g_layersChanged = true;
        }
    }

    void Hide() {
        if (hwnd_ && visible_) {
            ShowWindow(hwnd_, SW_HIDE);
            visible_ = false;
        }
    }

    HWND Hwnd() const { return hwnd_; }
    bool Visible() const { return visible_; }
    int X() const { return x_; }
    int Y() const { return y_; }
    int Width() const { return width_; }
    int Height() const { return height_; }
    BYTE Alpha() const { return alpha_; }
    void SetPosition(int x, int y) {
        x_ = x;
        y_ = y;
    }
    void AdoptPresented(int x, int y, int width, int height, BYTE alpha) {
        x_ = x;
        y_ = y;
        width_ = width;
        height_ = height;
        alpha_ = alpha;
    }

  private:
    HWND hwnd_ = nullptr;
    bool visible_ = false;
    int x_ = 0;
    int y_ = 0;
    int width_ = 0;
    int height_ = 0;
    BYTE alpha_ = 255;
};

void WaitForComposition() {
    using DwmFlush_t = HRESULT(WINAPI*)();
    static auto dwmFlush = GetProc<DwmFlush_t>(L"dwmapi.dll", "DwmFlush");
    if (dwmFlush && SUCCEEDED(dwmFlush())) {
        dwmFlush();
    } else {
        Sleep(30);
    }
}

inline uint32_t ScalePremultiplied(uint32_t pixel, uint32_t alpha) {
    uint32_t rb = (pixel & 0x00FF00FF) * alpha + 0x00800080;
    rb = ((rb + ((rb >> 8) & 0x00FF00FF)) >> 8) & 0x00FF00FF;
    uint32_t ag = ((pixel >> 8) & 0x00FF00FF) * alpha + 0x00800080;
    ag = (ag + ((ag >> 8) & 0x00FF00FF)) & 0xFF00FF00;
    return rb | ag;
}

////////////////////////////////////////////////////////////////////////////////
// Glass

enum class Backdrop { None, Blur };

struct AccentPolicy {
    int state;
    int flags;
    DWORD gradientColor;  // 0xAABBGGRR.
    int animationId;
};

struct WindowCompositionAttributeData {
    int attribute;
    PVOID data;
    SIZE_T size;
};

using SetWindowCompositionAttribute_t =
    BOOL(WINAPI*)(HWND, WindowCompositionAttributeData*);

SetWindowCompositionAttribute_t GetSetWindowCompositionAttribute() {
    static auto function = GetProc<SetWindowCompositionAttribute_t>(
        L"user32.dll", "SetWindowCompositionAttribute");
    return function;
}

bool TransparencyEnabled() {
    DWORD value = 1;
    DWORD size = sizeof(value);
    RegGetValueW(
        HKEY_CURRENT_USER,
        L"Software\\Microsoft\\Windows\\CurrentVersion\\Themes\\Personalize",
        L"EnableTransparency", RRF_RT_REG_DWORD, nullptr, &value, &size);
    return value != 0;
}

Backdrop ChooseBackdrop() {
    return g_settings.glass && IsWindows10Build(17134) && TransparencyEnabled()
               ? Backdrop::Blur : Backdrop::None;
}

void SetDwmAttribute(HWND hwnd, DWORD attribute, const void* value, DWORD size) {
    using DwmSetWindowAttribute_t = HRESULT(WINAPI*)(HWND, DWORD, LPCVOID, DWORD);
    static auto setAttribute = GetProc<DwmSetWindowAttribute_t>(
        L"dwmapi.dll", "DwmSetWindowAttribute");
    if (setAttribute) {
        setAttribute(hwnd, attribute, value, size);
    }
}

void ConfigurePixelWindow(HWND hwnd, const Color* glass) {
    const DWORD nonClient = 1;  // DWMNCRP_DISABLED.
    SetDwmAttribute(hwnd, 2 /* DWMWA_NCRENDERING_POLICY */, &nonClient, sizeof(nonClient));
    const BOOL noTransitions = TRUE;
    SetDwmAttribute(hwnd, 3 /* DWMWA_TRANSITIONS_FORCEDISABLED */, &noTransitions, sizeof(noTransitions));
    if (IsWindows11()) {
        const COLORREF border = 0xFFFFFFFE;  // DWMWA_COLOR_NONE.
        SetDwmAttribute(hwnd, 34 /* DWMWA_BORDER_COLOR */, &border, sizeof(border));
    }
    if (IsWindows10Build(22621)) {
        const DWORD backdrop = 1;  // DWMSBT_NONE.
        SetDwmAttribute(hwnd, 38 /* DWMWA_SYSTEMBACKDROP_TYPE */, &backdrop, sizeof(backdrop));
    }
    if (auto setAttribute = GetSetWindowCompositionAttribute()) {
        auto channel = [](float v) { return static_cast<DWORD>(v * 255.0f + 0.5f); };
        AccentPolicy policy{glass ? 4 /* ACCENT_ENABLE_ACRYLICBLURBEHIND */ : 0, 0,
                            glass ? 0x01000000 | channel(glass->b) << 16 |
                                        channel(glass->g) << 8 | channel(glass->r)
                                  : 0,
                            0};
        WindowCompositionAttributeData data{19 /* WCA_ACCENT_POLICY */, &policy,
                                            sizeof(policy)};
        setAttribute(hwnd, &data);
    }
    if (IsWindows11()) {
        const DWORD corners = glass ? 2 : 1;  // DWMWCP_ROUND, DWMWCP_DONOTROUND.
        SetDwmAttribute(hwnd, 33 /* DWMWA_WINDOW_CORNER_PREFERENCE */, &corners, sizeof(corners));
    }
}

struct OpaquePixels {
    const uint32_t* pixels;
    int width;
    int height;
    int stride;
};

inline uint32_t SampleOpaquePixels(const OpaquePixels& image, float x, float y) {
    x = std::clamp(x, 0.0f, static_cast<float>(image.width - 1));
    y = std::clamp(y, 0.0f, static_cast<float>(image.height - 1));
    const int x0 = static_cast<int>(x), y0 = static_cast<int>(y);
    const int x1 = std::min(x0 + 1, image.width - 1);
    const int y1 = std::min(y0 + 1, image.height - 1);
    const uint32_t fx = static_cast<uint32_t>((x - x0) * 256.0f + 0.5f);
    const uint32_t fy = static_cast<uint32_t>((y - y0) * 256.0f + 0.5f);
    auto lerp = [](uint32_t a, uint32_t b, uint32_t weight) {
        const uint32_t rb = (((a & 0x00FF00FF) * (256 - weight) +
                              (b & 0x00FF00FF) * weight) >> 8) & 0x00FF00FF;
        const uint32_t g = (((a & 0x0000FF00) * (256 - weight) +
                             (b & 0x0000FF00) * weight) >> 8) & 0x0000FF00;
        return 0xFF000000 | rb | g;
    };
    const uint32_t* row0 = image.pixels + static_cast<size_t>(y0) * image.stride;
    const uint32_t* row1 = image.pixels + static_cast<size_t>(y1) * image.stride;
    return lerp(lerp(row0[x0], row0[x1], fx), lerp(row1[x0], row1[x1], fx), fy);
}

// Panel corners sit on the live corner radius (the custom-corner-radius mod, 8 when it is off),
// the same radius DWM gives the glass underneath. Read again whenever settings change.
float g_cornerRadius = 8.0f;

void ReadCornerRadius() {
    float radius = 8.0f;
    HKEY key;
    if (RegOpenKeyExW(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Windhawk\\Engine\\Mods\\custom-corner-radius", 0,
                      KEY_READ, &key) == ERROR_SUCCESS) {
        DWORD disabled = 0, size = sizeof(disabled);
        const bool off = RegQueryValueExW(key, L"Disabled", nullptr, nullptr, (BYTE*)&disabled, &size) ==
                             ERROR_SUCCESS && disabled != 0;
        DWORD value = 0;
        size = sizeof(value);
        if (!off && RegGetValueW(key, L"Settings", L"radius", RRF_RT_REG_DWORD, nullptr, &value, &size) ==
                        ERROR_SUCCESS && value > 0 && value <= 64) {
            radius = (float)value;
        }
        RegCloseKey(key);
    }
    g_cornerRadius = radius;
}

Color GlassTint(bool dark) {
    return dark ? Rgb(30, 30, 46, 0.85f) : Rgb(249, 249, 252, 0.82f);
}

class GlassPanel {
  public:
    bool Create(bool activatable, bool clickThrough, PCWSTR className, void* param) {
        if (panel_.Hwnd()) {
            return true;
        }
        if (!underlay_.Hwnd() &&
            !underlay_.Create(true, false, kLayerWindowClass, nullptr)) {
            return false;
        }
        if (!panel_.Create(clickThrough, activatable, className, param)) {
            return false;
        }
        StyleWindow();
        return true;
    }

    void Destroy() {
        panel_.Destroy();
        underlay_.Destroy();
    }

    void Configure(bool dark) {
        backdrop_ = ChooseBackdrop();
        dark_ = dark;
        if (panel_.Hwnd()) {
            StyleWindow();
        }
    }

    Backdrop Material() const { return backdrop_; }
    bool Dark() const { return dark_; }

    float Radius(float scale) const { return g_cornerRadius * scale; }
    BYTE Alpha() const { return panel_.Alpha(); }

    void Present(Surface& content, int x, int y, BYTE alpha = 255) {
        x_ = x;
        y_ = y;
        panel_.Present(content, x, y, alpha);
        underlay_.Move(x - margin_, y - margin_);
    }

    void PresentUnderlay(Surface& underlay, int margin, BYTE alpha) {
        margin_ = margin;
        underlay_.Present(underlay, x_ - margin, y_ - margin, alpha);
    }

    void SetAlpha(BYTE alpha) { panel_.SetAlpha(alpha); }
    void SetUnderlayAlpha(BYTE alpha) { underlay_.SetAlpha(alpha); }

    void Move(int x, int y) {
        if (x == x_ && y == y_) {
            return;
        }
        x_ = x;
        y_ = y;
        constexpr UINT kFlags = SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE;
        HDWP defer = BeginDeferWindowPos(2);
        if (defer) {
            defer = DeferWindowPos(defer, panel_.Hwnd(), nullptr, x, y, 0, 0, kFlags);
        }
        if (defer) {
            defer = DeferWindowPos(defer, underlay_.Hwnd(), nullptr, x - margin_,
                                   y - margin_, 0, 0, kFlags);
        }
        if (defer) {
            EndDeferWindowPos(defer);
        }
        panel_.SetPosition(x, y);
        underlay_.SetPosition(x - margin_, y - margin_);
    }

    void FollowPanel(int x, int y) {
        x_ = x;
        y_ = y;
        panel_.SetPosition(x, y);
        underlay_.Move(x - margin_, y - margin_);
    }

    void Show(bool activate) {
        panel_.Show(activate);
        underlay_.Show();
        SetWindowPos(underlay_.Hwnd(), panel_.Hwnd(), 0, 0, 0, 0,
                     SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
    }

    void Hide() {
        panel_.Hide();
        underlay_.Hide();
    }

    bool Visible() const { return panel_.Visible(); }
    HWND Hwnd() const { return panel_.Hwnd(); }
    HWND UnderlayHwnd() const { return underlay_.Hwnd(); }
    int X() const { return x_; }
    int Y() const { return y_; }

  private:
    void StyleWindow() {
        const Color tint = GlassTint(dark_);
        ConfigurePixelWindow(panel_.Hwnd(), backdrop_ == Backdrop::Blur ? &tint : nullptr);
    }

    LayeredWindow panel_;
    LayeredWindow underlay_;
    Backdrop backdrop_ = Backdrop::None;
    bool dark_ = false;
    int x_ = 0;
    int y_ = 0;
    int margin_ = 0;
};

void PaintPanelBase(Surface& s, const GlassPanel& panel, float scale) {
    const float w = static_cast<float>(s.Width());
    const float h = static_cast<float>(s.Height());
    const bool dark = panel.Dark();
    const float radius = panel.Radius(scale);
    if (panel.Material() == Backdrop::Blur) {
        FillRoundRect(s, 0, 0, w, h, radius, GlassTint(dark));
    } else {
        FillRoundRectGradient(s, 0, 0, w, h, radius,
                              dark ? Rgb(30, 30, 46, 0.985f) : Rgb(252, 252, 253, 0.985f),
                              dark ? Rgb(24, 24, 37, 0.985f) : Rgb(244, 245, 248, 0.985f));
    }
    StrokeRoundRect(s, 0.5f, 0.5f, w - 0.5f, h - 0.5f, radius - 0.5f, 1.0f,
                    dark ? Rgb(108, 112, 134, 0.4f) : WithAlpha(kBlack, 0.10f));
}

std::vector<float> BlurCoverage(std::vector<float> mask, int width, int height, float sigma);

void PaintPanelUnderlay(Surface& s,
                        int w,
                        int h,
                        int margin,
                        float radius,
                        float scale,
                        bool dark,
                        float glow,
                        float phase) {
    if (!s.Resize(w + margin * 2, h + margin * 2)) return;
    const float l = static_cast<float>(margin);
    const float t = static_cast<float>(margin);
    const float r = l + w;
    const float b = t + h;
    const int width = s.Width(), height = s.Height();
    std::vector<float> body(static_cast<size_t>(width) * height, 0);
    std::vector<float> emission(body.size(), 0);
    const float emitterWidth = 1.8f * scale;
    for (int y = margin; y < margin + h; y++) {
        const float v = Clamp01((y + 0.5f - t) / h);
        const float weight = 0.12f + 0.88f * v * v * (3.0f - 2.0f * v);
        for (int x = margin; x < margin + w; x++) {
            const float distance = SdRoundRect(x + 0.5f, y + 0.5f, l, t, r, b, radius);
            const float coverage = Clamp01(0.5f - distance);
            const size_t index = static_cast<size_t>(y) * width + x;
            body[index] = coverage;
            emission[index] = coverage * Clamp01(emitterWidth + distance + 0.5f) * weight;
        }
    }
    const float tightSigma = 3.8f * scale, softSigma = 9.0f * scale, wideSigma = 17.0f * scale;
    const auto tight = BlurCoverage(emission, width, height, tightSigma);
    const auto soft = BlurCoverage(emission, width, height, softSigma);
    const auto wide = BlurCoverage(emission, width, height, wideSigma);
    const float normalize = 2.506628f / emitterWidth;
    const auto shadow = BlurCoverage(body, width, height, 16.0f * scale);
    const auto contact = BlurCoverage(body, width, height, 2.0f * scale);
    const int shadowOffset = static_cast<int>(lroundf(6 * scale));
    const int contactOffset = static_cast<int>(lroundf(2 * scale));
    const float cx = (l + r) * 0.5f;
    const float cy = (t + b) * 0.5f;
    for (int y = 0; y < height; y++) {
        uint32_t* row = s.Row(y);
        const float py = y + 0.5f;
        for (int x = 0; x < width; x++) {
            const float px = x + 0.5f;
            const size_t index = static_cast<size_t>(y) * width + x;
            const float outside = 1.0f - body[index];
            if (outside <= 0) continue;
            const float light = Clamp01(glow * normalize * (
                0.46f * tightSigma * tight[index] + 0.18f * softSigma * soft[index] +
                0.07f * wideSigma * wide[index]));
            const float shadowAlpha = Clamp01(
                (y >= shadowOffset ? shadow[static_cast<size_t>(y - shadowOffset) * width + x] : 0) *
                    (dark ? 0.26f : 0.16f) +
                (y >= contactOffset ? contact[static_cast<size_t>(y - contactOffset) * width + x] : 0) *
                    (dark ? 0.16f : 0.10f));
            const float a = (light + shadowAlpha * (1 - light)) * outside;
            if (a <= 0) continue;
            const float hue = g_glow.rainbow
                ? FastAtan2(py - cy, (px - cx) * (b - t) / (r - l)) / (2 * kPi) + phase : 0;
            const Color color = g_glow.At(hue);
            uint32_t noise = static_cast<uint32_t>(x) * 0x9E3779B9u ^ static_cast<uint32_t>(y) * 0x85EBCA6Bu;
            noise ^= noise >> 16;
            noise *= 0x7FEB352Du;
            noise ^= noise >> 15;
            const float threshold = ((noise & 65535) + 0.5f) / 65536.0f;
            const uint32_t alpha = static_cast<uint32_t>(a * 255 + threshold);
            auto channel = [&](float c) {
                return std::min(alpha, static_cast<uint32_t>(Clamp01(c * light * outside) * 255 + threshold));
            };
            row[x] = (alpha << 24) | (channel(color.r) << 16) | (channel(color.g) << 8) | channel(color.b);
        }
    }
}

////////////////////////////////////////////////////////////////////////////////
// The Magic Pointer

struct PointerFrame {
    float scale;    // Pixels per design unit.
    float phase;    // Drift of the glow colors, 0..1.
    float pop;      // Entrance of the sparkle, 0..1.
    float glow;     // Strength of the glow, 0..1.
    float breathe;  // Gentle pulse, 0..1, wraps.
};

struct ArrowGeometry {
    Vec2 points[4];  // Tip, right wing, notch, left wing.
    Vec2 center;
    Vec2 axis;
    float length;
};

const ArrowGeometry& GetArrow() {
    static const ArrowGeometry arrow = [] {
        const float angle = 36.0f * kPi / 180.0f;
        const Vec2 along{sinf(angle), cosf(angle)};
        const Vec2 across{cosf(angle), -sinf(angle)};
        const float length = 22.0f;
        const float halfWidth = 9.6f;
        const float notch = 0.72f;
        ArrowGeometry g;
        g.points[0] = {0, 0};
        g.points[1] = {along.x * length + across.x * halfWidth,
                       along.y * length + across.y * halfWidth};
        g.points[2] = {along.x * length * notch, along.y * length * notch};
        g.points[3] = {along.x * length - across.x * halfWidth,
                       along.y * length - across.y * halfWidth};
        g.center = {along.x * length * 0.55f, along.y * length * 0.55f};
        g.axis = along;
        g.length = length;
        return g;
    }();
    return arrow;
}

constexpr float kArrowRound = 2.3f;
constexpr float kGlowTight = 2.8f;
constexpr float kGlowWide = 8.5f;
constexpr Vec2 kSparkleCenter{11.5f, -9.5f};
constexpr float kSparkleRadius = 7.2f;
constexpr float kSparkleGlowSigma = 4.6f;

std::vector<float> BlurCoverage(std::vector<float> mask, int width, int height, float sigma) {
    int lower = std::max(1, static_cast<int>(floorf(sqrtf(4.0f * sigma * sigma + 1.0f))));
    if (!(lower & 1)) {
        lower--;
    }
    const int lowerPasses = std::clamp(static_cast<int>(lroundf(
        (12.0f * sigma * sigma - 3.0f * lower * lower - 12.0f * lower - 9.0f) /
        (-4.0f * lower - 4.0f))), 0, 3);
    std::vector<float> horizontal(mask.size());
    std::vector<float> columnSums(width);
    for (int pass = 0; pass < 3; pass++) {
        const int diameter = pass < lowerPasses ? lower : lower + 2;
        const int radius = diameter / 2;
        for (int y = 0; y < height; y++) {
            const size_t row = static_cast<size_t>(y) * width;
            float sum = 0;
            for (int x = 0; x <= std::min(radius, width - 1); x++) {
                sum += mask[row + x];
            }
            for (int x = 0; x < width; x++) {
                horizontal[row + x] = std::max(0.0f, sum / diameter);
                if (x - radius >= 0) sum -= mask[row + x - radius];
                if (x + radius + 1 < width) sum += mask[row + x + radius + 1];
            }
        }
        std::fill(columnSums.begin(), columnSums.end(), 0.0f);
        for (int y = 0; y <= std::min(radius, height - 1); y++) {
            const float* row = horizontal.data() + static_cast<size_t>(y) * width;
            for (int x = 0; x < width; x++) columnSums[x] += row[x];
        }
        for (int y = 0; y < height; y++) {
            float* row = mask.data() + static_cast<size_t>(y) * width;
            const float* leaving = y >= radius
                ? horizontal.data() + static_cast<size_t>(y - radius) * width : nullptr;
            const float* entering = y + radius + 1 < height
                ? horizontal.data() + static_cast<size_t>(y + radius + 1) * width : nullptr;
            for (int x = 0; x < width; x++) {
                row[x] = std::max(0.0f, columnSums[x] / diameter);
                if (leaving) columnSums[x] -= leaving[x];
                if (entering) columnSums[x] += entering[x];
            }
        }
    }
    return mask;
}

void RenderPointer(const PointerFrame& f,
                   std::vector<uint32_t>& pixels,
                   int& width,
                   int& height,
                   int& hotX,
                   int& hotY) {
    const ArrowGeometry& arrow = GetArrow();
    const float glowReach = kGlowWide * 3.2f;
    const float sparkleReach = kSparkleRadius * 1.25f + kSparkleGlowSigma * 3.2f;

    float minX = 0, minY = 0, maxX = 0, maxY = 0;
    for (const Vec2& p : arrow.points) {
        minX = std::min(minX, p.x);
        minY = std::min(minY, p.y);
        maxX = std::max(maxX, p.x);
        maxY = std::max(maxY, p.y);
    }
    minX -= kArrowRound + glowReach;
    minY -= kArrowRound + glowReach;
    maxX += kArrowRound + glowReach;
    maxY += kArrowRound + glowReach;
    minX = std::min(minX, kSparkleCenter.x - sparkleReach);
    minY = std::min(minY, kSparkleCenter.y - sparkleReach);
    maxX = std::max(maxX, kSparkleCenter.x + sparkleReach);
    maxY = std::max(maxY, kSparkleCenter.y + sparkleReach);

    const float s = std::min(f.scale, 253.0f / std::max(maxX - minX, maxY - minY));
    hotX = static_cast<int>(ceilf(-minX * s));
    hotY = static_cast<int>(ceilf(-minY * s));
    width = hotX + static_cast<int>(ceilf(maxX * s)) + 1;
    height = hotY + static_cast<int>(ceilf(maxY * s)) + 1;
    pixels.assign(static_cast<size_t>(width) * height, 0);

    const float pulse = sinf(2.0f * kPi * f.breathe);
    const float pop = static_cast<float>(EaseOutBack(f.pop));
    const float sparkleRadius = kSparkleRadius * pop * (1.0f + 0.025f * pulse);
    const float sparkleAngle =
        (1.0f - static_cast<float>(EaseOutCubic(f.pop))) * kPi * 0.5f +
        0.035f * sinf(2.0f * kPi * f.breathe);
    const float sparkleOpacity = Clamp01(f.pop * 2.5f);
    const float glow = f.glow * (0.62f + 0.38f * pulse);
    const float spread = 1.0f + 0.07f * pulse;
    const float tight = kGlowTight * spread;
    const float wide = kGlowWide * spread;
    const float sparkleSigma = kSparkleGlowSigma * spread;
    const Vec2 shadowOffset{0.65f, 1.7f};
    const Color shadow = WithAlpha(kBlack, 0.24f);
    const Color rim = WithAlpha(Mix(g_glow.Base(), kBlack, 0.60f), 0.28f);
    const Color bodyBottom = Rgb(242, 244, 248);

    auto coverage = [&](Vec2 p, float d, auto distance) {
        if (fabsf(d * s) >= 1.0f) {
            return Clamp01(0.5f - d * s);
        }
        float sum = 0;
        for (float oy : {-0.25f, 0.25f}) {
            for (float ox : {-0.25f, 0.25f}) {
                sum += Clamp01(0.5f - distance({p.x + ox / s, p.y + oy / s}) * s * 2.0f);
            }
        }
        return sum * 0.25f;
    };

    std::vector<float> sparkleMask(pixels.size(), 0);
    if (sparkleRadius > 0.05f) {
        const float reach = sparkleRadius * 1.25f + 1.0f / s;
        const int firstX = std::max(0, static_cast<int>(floorf(hotX + (kSparkleCenter.x - reach) * s)));
        const int lastX = std::min(width, static_cast<int>(ceilf(hotX + (kSparkleCenter.x + reach) * s)));
        const int firstY = std::max(0, static_cast<int>(floorf(hotY + (kSparkleCenter.y - reach) * s)));
        const int lastY = std::min(height, static_cast<int>(ceilf(hotY + (kSparkleCenter.y + reach) * s)));
        for (int y = firstY; y < lastY; y++) {
            for (int x = firstX; x < lastX; x++) {
                const Vec2 p{(x + 0.5f - hotX) / s, (y + 0.5f - hotY) / s};
                const float d = SdSparkle(p, kSparkleCenter.x, kSparkleCenter.y,
                                          sparkleRadius, sparkleAngle);
                sparkleMask[static_cast<size_t>(y) * width + x] = sparkleOpacity * coverage(p, d, [&](Vec2 q) {
                    return SdSparkle(q, kSparkleCenter.x, kSparkleCenter.y, sparkleRadius, sparkleAngle);
                });
            }
        }
    }
    const auto sparkleTight = BlurCoverage(sparkleMask, width, height, 1.1f * s);
    const auto sparkleWide = BlurCoverage(sparkleMask, width, height, sparkleSigma * s);
    const auto sparkleShadow = BlurCoverage(sparkleMask, width, height, 1.3f * s);

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            const Vec2 p{(x + 0.5f - hotX) / s, (y + 0.5f - hotY) / s};
            uint32_t px = 0;

            const float dArrow = SdPolygon(arrow.points, 4, p) - kArrowRound;
            const float dShadow =
                SdPolygon(arrow.points, 4,
                          {p.x - shadowOffset.x, p.y - shadowOffset.y}) - kArrowRound;
            BlendColor(px, shadow, SoftCoverage(dShadow, 1.8f));

            const size_t index = static_cast<size_t>(y) * width + x;
            const int shadowX = x - static_cast<int>(lroundf(0.4f * s));
            const int shadowY = y - static_cast<int>(lroundf(s));
            if (shadowX >= 0 && shadowY >= 0) {
                BlendColor(px, WithAlpha(kBlack, 0.19f),
                           sparkleShadow[static_cast<size_t>(shadowY) * width + shadowX]);
            }

            if (glow > 0.0f && dArrow < glowReach) {
                const float d = std::max(dArrow, 0.0f);
                const float a = glow *
                    (0.38f * expf(-0.5f * d * d / (tight * tight)) +
                     0.68f * SoftCoverage(dArrow, wide));
                const Color color = g_glow.rainbow
                    ? g_glow.At(FastAtan2(p.y - arrow.center.y, p.x - arrow.center.x) /
                                    (2.0f * kPi) + f.phase) : g_glow.Base();
                BlendColor(px, color, a);
            }

            const float starGlow = glow * (0.95f * sparkleTight[index] + 1.45f * sparkleWide[index]);
            if (starGlow > 0.001f) {
                const Color color = g_glow.rainbow
                    ? g_glow.At(FastAtan2(p.y - kSparkleCenter.y, p.x - kSparkleCenter.x) /
                                    (2.0f * kPi) + f.phase + 0.33f) : g_glow.Base();
                BlendColor(px, color, starGlow);
            }

            const float body = coverage(p, dArrow, [&](Vec2 q) {
                return SdPolygon(arrow.points, 4, q) - kArrowRound;
            });
            if (body > 0.0f) {
                const float along = Clamp01((p.x * arrow.axis.x + p.y * arrow.axis.y) /
                                            arrow.length);
                BlendColor(px, Mix(kWhite, bodyBottom, along), body);
                const float inner = coverage(p, dArrow + 0.55f, [&](Vec2 q) {
                    return SdPolygon(arrow.points, 4, q) - kArrowRound + 0.55f;
                });
                BlendColor(px, rim, std::max(0.0f, body - inner));
            }
            if (sparkleMask[index] > 0) {
                const float starCoverage = sparkleMask[index];
                if (starCoverage > 0.0f) {
                    const float r = sqrtf((p.x - kSparkleCenter.x) * (p.x - kSparkleCenter.x) +
                                          (p.y - kSparkleCenter.y) * (p.y - kSparkleCenter.y));
                    const float highlight = expf(-r * r /
                                                  (sparkleRadius * sparkleRadius * 0.23f));
                    const Color tint = Mix(g_glow.At(f.phase), kWhite,
                                           0.80f + 0.16f * highlight);
                    BlendColor(px, tint, starCoverage);
                }
            }
            pixels[static_cast<size_t>(y) * width + x] = px;
        }
    }
}

std::wstring ExpandVariables(const std::wstring& text);

struct CursorImage {
    int width = 0;
    int height = 0;
    int hotX = 0;
    int hotY = 0;
    std::vector<uint32_t> pixels;
};

struct CursorEntry {
    int width;
    int height;
    int bits;
    int hotX;
    int hotY;
    size_t offset;
    size_t size;
};

struct CursorStep {
    size_t frame;
    double end;
};

struct CursorFile {
    std::vector<uint8_t> bytes;
    std::vector<std::vector<CursorEntry>> frames;
    std::vector<CursorStep> steps;
};

struct PreparedCursor {
    int width = 0;
    int height = 0;
    int hotX = 0;
    int hotY = 0;
    std::vector<uint32_t> pixels;
    std::vector<uint8_t> glow;
    std::vector<uint8_t> hue;
    RECT reach = {};
};

uint32_t ReadLe(const uint8_t* data, int count) {
    uint32_t value = 0;
    for (int i = 0; i < count; i++) {
        value |= static_cast<uint32_t>(data[i]) << (8 * i);
    }
    return value;
}

bool ReadCursorEntries(const std::vector<uint8_t>& bytes,
                       size_t begin,
                       size_t end,
                       std::vector<CursorEntry>& entries) {
    static const uint8_t kPng[8] = {0x89, 'P', 'N', 'G', '\r', '\n', 0x1A, '\n'};
    if (end > bytes.size() || begin >= end || end - begin < 6) {
        return false;
    }
    const uint8_t* base = bytes.data() + begin;
    const size_t length = end - begin;
    const uint32_t type = ReadLe(base + 2, 2);
    const size_t count = ReadLe(base + 4, 2);
    if (ReadLe(base, 2) != 0 || (type != 1 && type != 2) || count == 0 ||
        count > 64 || 6 + 16 * count > length) {
        return false;
    }
    for (size_t i = 0; i < count; i++) {
        const uint8_t* record = base + 6 + 16 * i;
        const size_t size = ReadLe(record + 8, 4);
        const size_t offset = ReadLe(record + 12, 4);
        if (size < 26 || offset > length || size > length - offset) {
            continue;
        }
        const uint8_t* data = base + offset;
        int64_t width;
        int64_t height;
        int bits = 32;
        if (memcmp(data, kPng, sizeof(kPng)) == 0) {
            width = (static_cast<int64_t>(data[16]) << 24) | (data[17] << 16) |
                    (data[18] << 8) | data[19];
            height = (static_cast<int64_t>(data[20]) << 24) | (data[21] << 16) |
                     (data[22] << 8) | data[23];
        } else if (ReadLe(data, 4) >= 40 && ReadLe(data, 4) <= 124 && ReadLe(data + 12, 2) == 1 &&
                   (ReadLe(data + 16, 4) == BI_RGB || ReadLe(data + 16, 4) == BI_BITFIELDS)) {
            int64_t rows = static_cast<int32_t>(ReadLe(data + 8, 4));
            width = static_cast<int32_t>(ReadLe(data + 4, 4));
            height = (rows < 0 ? -rows : rows) / 2;
            bits = static_cast<int>(ReadLe(data + 14, 2));
            if (bits != 1 && bits != 4 && bits != 8 && bits != 16 && bits != 24 && bits != 32) {
                continue;
            }
        } else {
            continue;
        }
        if (width < 1 || width > 512 || height < 1 || height > 512) {
            continue;
        }
        const int w = static_cast<int>(width);
        const int h = static_cast<int>(height);
        const int hotX = type == 2 ? static_cast<int>(ReadLe(record + 4, 2)) : w / 2;
        const int hotY = type == 2 ? static_cast<int>(ReadLe(record + 6, 2)) : h / 2;
        entries.push_back({w, h, bits, std::min(hotX, w - 1), std::min(hotY, h - 1),
                           begin + offset, size});
    }
    return !entries.empty();
}

bool ReadAnimatedCursor(CursorFile& file) {
    const std::vector<uint8_t>& bytes = file.bytes;
    uint32_t defaultRate = 6;
    std::vector<uint32_t> rates;
    std::vector<uint32_t> sequence;
    size_t position = 12;
    while (position + 8 <= bytes.size()) {
        const uint8_t* chunk = bytes.data() + position;
        const size_t body = position + 8;
        const size_t size = std::min<size_t>(ReadLe(chunk + 4, 4), bytes.size() - body);
        if (memcmp(chunk, "anih", 4) == 0 && size >= 36) {
            defaultRate = ReadLe(bytes.data() + body + 28, 4);
        } else if (memcmp(chunk, "rate", 4) == 0 || memcmp(chunk, "seq ", 4) == 0) {
            std::vector<uint32_t>& list = chunk[0] == 'r' ? rates : sequence;
            for (size_t i = 0; i + 4 <= size && list.size() < 4096; i += 4) {
                list.push_back(ReadLe(bytes.data() + body + i, 4));
            }
        } else if (memcmp(chunk, "LIST", 4) == 0 && size >= 4 &&
                   memcmp(bytes.data() + body, "fram", 4) == 0) {
            const size_t listEnd = body + size;
            for (size_t sub = body + 4; sub + 8 <= listEnd && file.frames.size() < 512;) {
                const size_t subSize =
                    std::min<size_t>(ReadLe(bytes.data() + sub + 4, 4), listEnd - sub - 8);
                if (memcmp(bytes.data() + sub, "icon", 4) == 0) {
                    std::vector<CursorEntry> entries;
                    ReadCursorEntries(bytes, sub + 8, sub + 8 + subSize, entries);
                    file.frames.push_back(std::move(entries));
                }
                sub += 8 + subSize + (subSize & 1);
            }
        }
        position = body + size + (size & 1);
    }
    const size_t count = sequence.empty() ? file.frames.size() : sequence.size();
    double end = 0;
    for (size_t i = 0; i < count; i++) {
        const size_t frame = sequence.empty() ? i : sequence[i];
        if (frame >= file.frames.size() || file.frames[frame].empty()) {
            continue;
        }
        end += std::clamp<uint32_t>(i < rates.size() ? rates[i] : defaultRate, 1, 600) *
               (1000.0 / 60.0);
        file.steps.push_back({frame, end});
    }
    return !file.steps.empty();
}

bool ReadCursorFile(CursorFile& file) {
    const std::vector<uint8_t>& bytes = file.bytes;
    if (bytes.size() > 12 && memcmp(bytes.data(), "RIFF", 4) == 0 &&
        memcmp(bytes.data() + 8, "ACON", 4) == 0) {
        return ReadAnimatedCursor(file);
    }
    std::vector<CursorEntry> entries;
    if (!ReadCursorEntries(bytes, 0, bytes.size(), entries)) {
        return false;
    }
    file.frames.push_back(std::move(entries));
    file.steps.push_back({0, 1000.0});
    return true;
}

std::shared_ptr<const CursorFile> LoadCustomCursor(const std::wstring& setting) {
    std::wstring path = Trim(setting);
    if (path.size() > 1 && path.front() == L'"' && path.back() == L'"') {
        path = Trim(path.substr(1, path.size() - 2));
    }
    if (path.empty()) {
        return nullptr;
    }
    path = ExpandVariables(path);
    HANDLE handle = CreateFileW(path.c_str(), GENERIC_READ,
                                FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
                                nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
    if (handle == INVALID_HANDLE_VALUE) {
        Wh_Log(L"Couldn't open the custom cursor %s (error %u)", path.c_str(), GetLastError());
        return nullptr;
    }
    auto file = std::make_shared<CursorFile>();
    LARGE_INTEGER size{};
    bool loaded = GetFileSizeEx(handle, &size) && size.QuadPart >= 22 &&
                  size.QuadPart <= 16 * 1024 * 1024;
    if (loaded) {
        DWORD read = 0;
        file->bytes.resize(static_cast<size_t>(size.QuadPart));
        loaded = ReadFile(handle, file->bytes.data(), static_cast<DWORD>(size.QuadPart), &read,
                          nullptr) &&
                 read == size.QuadPart;
    }
    CloseHandle(handle);
    if (!loaded) {
        Wh_Log(L"Couldn't read the custom cursor %s", path.c_str());
        return nullptr;
    }
    if (!ReadCursorFile(*file)) {
        Wh_Log(L"%s isn't a cursor file Magic Pointer can use", path.c_str());
        return nullptr;
    }
    Wh_Log(L"Custom cursor %s: %d frame(s), %d step(s)", path.c_str(),
           static_cast<int>(file->frames.size()), static_cast<int>(file->steps.size()));
    return file;
}

bool DecodeCursorEntry(const CursorFile& file, const CursorEntry& entry, CursorImage& image) {
    HICON icon = CreateIconFromResourceEx(
        const_cast<PBYTE>(file.bytes.data() + entry.offset), static_cast<DWORD>(entry.size), TRUE,
        0x00030000, entry.width, entry.height, LR_DEFAULTCOLOR);
    if (!icon) {
        return false;
    }
    ICONINFO info{};
    BITMAP bitmap{};
    bool ok = GetIconInfo(icon, &info) &&
              GetObjectW(info.hbmColor ? info.hbmColor : info.hbmMask, sizeof(bitmap), &bitmap);
    const int width = bitmap.bmWidth;
    const int height = info.hbmColor ? bitmap.bmHeight : bitmap.bmHeight / 2;
    ok = ok && width > 0 && height > 0 && width <= 1024 && height <= 1024;
    HDC dc = ok ? GetDC(nullptr) : nullptr;
    ok = ok && dc;
    auto read = [&](HBITMAP source, int rows, std::vector<uint32_t>& out) {
        BITMAPINFO format{};
        format.bmiHeader.biSize = sizeof(format.bmiHeader);
        format.bmiHeader.biWidth = width;
        format.bmiHeader.biHeight = -rows;
        format.bmiHeader.biPlanes = 1;
        format.bmiHeader.biBitCount = 32;
        format.bmiHeader.biCompression = BI_RGB;
        out.assign(static_cast<size_t>(width) * rows, 0);
        return GetDIBits(dc, source, 0, rows, out.data(), &format, DIB_RGB_COLORS) == rows;
    };
    std::vector<uint32_t> color;
    std::vector<uint32_t> mask;
    if (ok) {
        ok = info.hbmColor ? read(info.hbmColor, height, color) && read(info.hbmMask, height, mask)
                           : read(info.hbmMask, height * 2, mask);
    }
    if (ok) {
        image.width = width;
        image.height = height;
        image.hotX = std::clamp(entry.hotX * width / entry.width, 0, width - 1);
        image.hotY = std::clamp(entry.hotY * height / entry.height, 0, height - 1);
        image.pixels.assign(static_cast<size_t>(width) * height, 0);
        const bool alpha = info.hbmColor && entry.bits == 32 && bitmap.bmBitsPixel == 32 &&
                           std::any_of(color.begin(), color.end(),
                                       [](uint32_t pixel) { return (pixel >> 24) != 0; });
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                const size_t i = static_cast<size_t>(y) * width + x;
                uint32_t pixel;
                if (!info.hbmColor) {
                    const bool andBit = (mask[i] & 0xFFFFFF) != 0;
                    const bool xorBit = (mask[i + static_cast<size_t>(height) * width] & 0xFFFFFF) != 0;
                    pixel = andBit && !xorBit ? 0 : xorBit ? 0xFFFFFFFFu : 0xFF000000u;
                } else if (alpha) {
                    pixel = color[i];
                } else {
                    const uint32_t rgb = color[i] & 0xFFFFFF;
                    pixel = (mask[i] & 0xFFFFFF) && !rgb ? 0 : 0xFF000000u | rgb;
                }
                image.pixels[i] = pixel;
            }
        }
    }
    if (dc) {
        ReleaseDC(nullptr, dc);
    }
    if (info.hbmColor) {
        DeleteObject(info.hbmColor);
    }
    if (info.hbmMask) {
        DeleteObject(info.hbmMask);
    }
    DestroyIcon(icon);
    return ok;
}

std::vector<std::vector<std::pair<int, float>>> ResizeTaps(int from, int to) {
    std::vector<std::vector<std::pair<int, float>>> taps(to);
    const double ratio = static_cast<double>(from) / to;
    for (int i = 0; i < to; i++) {
        if (ratio > 1.0) {
            const double low = i * ratio;
            const double high = (i + 1) * ratio;
            for (int j = static_cast<int>(low); j < from && j < high; j++) {
                taps[i].push_back(
                    {j, static_cast<float>(std::min<double>(high, j + 1) - std::max<double>(low, j))});
            }
        } else {
            const double center = (i + 0.5) * ratio - 0.5;
            const int first = static_cast<int>(floor(center));
            const float fraction = static_cast<float>(center - first);
            taps[i].push_back({std::clamp(first, 0, from - 1), 1.0f - fraction});
            taps[i].push_back({std::clamp(first + 1, 0, from - 1), fraction});
        }
    }
    return taps;
}

std::vector<uint32_t> ResampleCursorImage(const CursorImage& image, int width, int height) {
    std::vector<float> source(image.pixels.size() * 4);
    for (size_t i = 0; i < image.pixels.size(); i++) {
        const uint32_t pixel = image.pixels[i];
        const float alpha = static_cast<float>(pixel >> 24);
        source[i * 4] = ((pixel >> 16) & 255) * alpha / 255.0f;
        source[i * 4 + 1] = ((pixel >> 8) & 255) * alpha / 255.0f;
        source[i * 4 + 2] = (pixel & 255) * alpha / 255.0f;
        source[i * 4 + 3] = alpha;
    }
    const auto columns = ResizeTaps(image.width, width);
    const auto rows = ResizeTaps(image.height, height);
    std::vector<float> across(static_cast<size_t>(width) * image.height * 4);
    for (int y = 0; y < image.height; y++) {
        for (int x = 0; x < width; x++) {
            float sum[4] = {};
            float total = 0;
            for (const auto& tap : columns[x]) {
                const float* from = &source[(static_cast<size_t>(y) * image.width + tap.first) * 4];
                for (int c = 0; c < 4; c++) {
                    sum[c] += from[c] * tap.second;
                }
                total += tap.second;
            }
            for (int c = 0; c < 4; c++) {
                across[(static_cast<size_t>(y) * width + x) * 4 + c] = sum[c] / total;
            }
        }
    }
    std::vector<uint32_t> out(static_cast<size_t>(width) * height);
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            float sum[4] = {};
            float total = 0;
            for (const auto& tap : rows[y]) {
                const float* from = &across[(static_cast<size_t>(tap.first) * width + x) * 4];
                for (int c = 0; c < 4; c++) {
                    sum[c] += from[c] * tap.second;
                }
                total += tap.second;
            }
            const uint32_t alpha = static_cast<uint32_t>(std::clamp(sum[3] / total, 0.0f, 255.0f) + 0.5f);
            auto channel = [&](int c) {
                return std::min(alpha, static_cast<uint32_t>(std::clamp(sum[c] / total, 0.0f, 255.0f) + 0.5f));
            };
            out[static_cast<size_t>(y) * width + x] =
                (alpha << 24) | (channel(0) << 16) | (channel(1) << 8) | channel(2);
        }
    }
    return out;
}

std::vector<float> SquaredDistanceToMask(const std::vector<uint8_t>& inside, int width, int height) {
    constexpr float kFar = 1e20f;
    const int longest = std::max(width, height);
    std::vector<float> squared(static_cast<size_t>(width) * height);
    std::vector<float> line(longest);
    std::vector<float> result(longest);
    std::vector<float> bounds(longest + 1);
    std::vector<int> vertex(longest);
    auto transform = [&](int count) {
        int k = 0;
        vertex[0] = 0;
        bounds[0] = -kFar;
        bounds[1] = kFar;
        for (int q = 1; q < count; q++) {
            float cross;
            for (;;) {
                const int p = vertex[k];
                cross = ((line[q] + static_cast<float>(q) * q) - (line[p] + static_cast<float>(p) * p)) /
                        (2.0f * (q - p));
                if (k == 0 || cross > bounds[k]) {
                    break;
                }
                k--;
            }
            k++;
            vertex[k] = q;
            bounds[k] = cross;
            bounds[k + 1] = kFar;
        }
        k = 0;
        for (int q = 0; q < count; q++) {
            while (bounds[k + 1] < q) {
                k++;
            }
            result[q] = static_cast<float>(q - vertex[k]) * (q - vertex[k]) + line[vertex[k]];
        }
    };
    for (int x = 0; x < width; x++) {
        for (int y = 0; y < height; y++) {
            line[y] = inside[static_cast<size_t>(y) * width + x] ? 0.0f : kFar;
        }
        transform(height);
        for (int y = 0; y < height; y++) {
            squared[static_cast<size_t>(y) * width + x] = result[y];
        }
    }
    for (int y = 0; y < height; y++) {
        std::copy_n(&squared[static_cast<size_t>(y) * width], width, line.begin());
        transform(width);
        std::copy_n(result.begin(), width, &squared[static_cast<size_t>(y) * width]);
    }
    return squared;
}

bool PrepareCursor(const CursorFile& file, size_t frame, float scale, PreparedCursor& out) {
    const std::vector<CursorEntry>& entries = file.frames[frame];
    if (entries.empty()) {
        return false;
    }
    auto longest = [](const CursorEntry& entry) { return std::max(entry.width, entry.height); };
    const CursorEntry& nominal = *std::min_element(
        entries.begin(), entries.end(),
        [&](const CursorEntry& a, const CursorEntry& b) { return longest(a) < longest(b); });
    const float s = std::min(scale, 221.0f / longest(nominal));
    const int width = std::max(1, static_cast<int>(lroundf(nominal.width * s)));
    const int height = std::max(1, static_cast<int>(lroundf(nominal.height * s)));
    const int wanted = std::max(width, height);
    std::vector<const CursorEntry*> order;
    for (const CursorEntry& entry : entries) {
        order.push_back(&entry);
    }
    std::stable_sort(order.begin(), order.end(), [&](const CursorEntry* a, const CursorEntry* b) {
        const bool aFits = longest(*a) >= wanted;
        const bool bFits = longest(*b) >= wanted;
        if (aFits != bFits) {
            return aFits;
        }
        if (longest(*a) != longest(*b)) {
            return aFits == (longest(*a) < longest(*b));
        }
        return a->bits > b->bits;
    });
    CursorImage image;
    bool decoded = false;
    for (size_t i = 0; i < order.size() && !decoded; i++) {
        decoded = DecodeCursorEntry(file, *order[i], image);
    }
    if (!decoded) {
        return false;
    }

    const int fullMargin = static_cast<int>(ceilf(kGlowWide * 3.2f * s));
    const int margin = std::max(0, std::min(fullMargin, (253 - wanted) / 2));
    out.width = width + margin * 2;
    out.height = height + margin * 2;
    out.hotX = margin + std::clamp(static_cast<int>(lroundf(image.hotX * static_cast<float>(width) / image.width)),
                                   0, width - 1);
    out.hotY = margin + std::clamp(static_cast<int>(lroundf(image.hotY * static_cast<float>(height) / image.height)),
                                   0, height - 1);
    const std::vector<uint32_t> picture = ResampleCursorImage(image, width, height);
    const size_t total = static_cast<size_t>(out.width) * out.height;
    out.pixels.assign(total, 0);
    for (int y = 0; y < height; y++) {
        std::copy_n(&picture[static_cast<size_t>(y) * width], width,
                    &out.pixels[static_cast<size_t>(y + margin) * out.width + margin]);
    }

    uint32_t strongest = 0;
    double sumX = 0;
    double sumY = 0;
    double sumAlpha = 0;
    RECT bounds = {out.width, out.height, 0, 0};
    for (int y = 0; y < out.height; y++) {
        for (int x = 0; x < out.width; x++) {
            const uint32_t alpha = out.pixels[static_cast<size_t>(y) * out.width + x] >> 24;
            strongest = std::max(strongest, alpha);
            sumAlpha += alpha;
            sumX += alpha * (x + 0.5);
            sumY += alpha * (y + 0.5);
            if (alpha) {
                bounds = {std::min<LONG>(bounds.left, x), std::min<LONG>(bounds.top, y),
                          std::max<LONG>(bounds.right, x + 1), std::max<LONG>(bounds.bottom, y + 1)};
            }
        }
    }
    if (sumAlpha > 0) {
        out.reach = {std::max(0, out.hotX - static_cast<int>(bounds.left)),
                     std::max(0, out.hotY - static_cast<int>(bounds.top)),
                     std::max(0, static_cast<int>(bounds.right) - out.hotX),
                     std::max(0, static_cast<int>(bounds.bottom) - out.hotY)};
    }
    const float centerX = sumAlpha > 0 ? static_cast<float>(sumX / sumAlpha) : out.width * 0.5f;
    const float centerY = sumAlpha > 0 ? static_cast<float>(sumY / sumAlpha) : out.height * 0.5f;
    const uint32_t threshold = std::clamp<uint32_t>(strongest / 2, 1, 128);
    std::vector<uint8_t> inside(total);
    for (size_t i = 0; i < total; i++) {
        inside[i] = (out.pixels[i] >> 24) >= threshold;
    }
    const std::vector<float> squared = SquaredDistanceToMask(inside, out.width, out.height);

    const float tight = kGlowTight * s;
    const float wide = kGlowWide * s;
    const int levels = static_cast<int>(ceilf(wide * 13.6f)) + 2;
    std::vector<float> falloff(levels);
    for (int i = 0; i < levels; i++) {
        const float d = i * 0.25f;
        falloff[i] =
            Clamp01(0.38f * expf(-0.5f * d * d / (tight * tight)) + 0.68f * SoftCoverage(d, wide)) * 255.0f;
    }
    const float limit = (levels - 1) / 4.0f + 0.5f;
    out.glow.assign(total, 0);
    out.hue.assign(total, 0);
    for (int y = 0; y < out.height; y++) {
        for (int x = 0; x < out.width; x++) {
            const size_t i = static_cast<size_t>(y) * out.width + x;
            if (squared[i] < limit * limit) {
                const float position = std::max(0.0f, sqrtf(squared[i]) - 0.5f) * 4.0f;
                const int index = std::min(levels - 2, static_cast<int>(position));
                float value = falloff[index] + (falloff[index + 1] - falloff[index]) * std::min(1.0f, position - index);
                if (margin < fullMargin) {
                    const float edge = std::min(std::min(x + 0.5f, out.width - x - 0.5f),
                                                std::min(y + 0.5f, out.height - y - 0.5f));
                    const float u = Clamp01(edge / std::max(margin, 1));
                    value *= u * u * (3.0f - 2.0f * u);
                }
                out.glow[i] = static_cast<uint8_t>(value + 0.5f);
            }
            const float turn = FastAtan2(y + 0.5f - centerY, x + 0.5f - centerX) / (2.0f * kPi);
            out.hue[i] = static_cast<uint8_t>(static_cast<int>((turn + 1.0f) * 256.0f) & 255);
        }
    }
    return true;
}

HCURSOR CursorFromPixels(const uint32_t* pixels,
                         int width,
                         int height,
                         int hotX,
                         int hotY) {
    BITMAPINFO info{};
    info.bmiHeader.biSize = sizeof(info.bmiHeader);
    info.bmiHeader.biWidth = width;
    info.bmiHeader.biHeight = -height;
    info.bmiHeader.biPlanes = 1;
    info.bmiHeader.biBitCount = 32;
    info.bmiHeader.biCompression = BI_RGB;
    void* bits = nullptr;
    HBITMAP color =
        CreateDIBSection(nullptr, &info, DIB_RGB_COLORS, &bits, nullptr, 0);
    if (!color || !bits) {
        if (color) {
            DeleteObject(color);
        }
        return nullptr;
    }

    uint32_t* out = static_cast<uint32_t*>(bits);
    for (size_t i = 0; i < static_cast<size_t>(width) * height; i++) {
        const uint32_t p = pixels[i];
        const uint32_t a = p >> 24;
        if (!a) {
            out[i] = 0;
            continue;
        }
        auto channel = [&](int shift) {
            return std::min<uint32_t>(255, (((p >> shift) & 255) * 255 + a / 2) / a);
        };
        out[i] = (a << 24) | (channel(16) << 16) | (channel(8) << 8) | channel(0);
    }
    GdiFlush();

    const int maskStride = ((width + 15) / 16) * 2;
    std::vector<uint8_t> maskBits(static_cast<size_t>(maskStride) * height, 0);
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if (!(pixels[static_cast<size_t>(y) * width + x] >> 24)) {
                maskBits[static_cast<size_t>(y) * maskStride + x / 8] |= 0x80 >> (x & 7);
            }
        }
    }
    HBITMAP mask = CreateBitmap(width, height, 1, 1, maskBits.data());
    ICONINFO iconInfo{};
    iconInfo.fIcon = FALSE;
    iconInfo.xHotspot = static_cast<DWORD>(hotX);
    iconInfo.yHotspot = static_cast<DWORD>(hotY);
    iconInfo.hbmMask = mask;
    iconInfo.hbmColor = color;
    HCURSOR cursor = mask ? CreateIconIndirect(&iconInfo) : nullptr;
    DeleteObject(color);
    if (mask) {
        DeleteObject(mask);
    }
    return cursor;
}

HCURSOR CreatePointerCursor(const PointerFrame& frame) {
    std::vector<uint32_t> pixels;
    int width, height, hotX, hotY;
    RenderPointer(frame, pixels, width, height, hotX, hotY);
    return CursorFromPixels(pixels.data(), width, height, hotX, hotY);
}

HCURSOR RenderCustomCursor(const PreparedCursor& frame, float glow, float phase) {
    uint32_t colors[256];
    for (int i = 0; i < 256; i++) {
        colors[i] = PackPremultiplied(g_glow.At(i / 256.0f), 1.0f);
    }
    const int shift = static_cast<int>(lroundf(phase * 256.0f));
    const uint32_t strength = static_cast<uint32_t>(Clamp01(glow) * 256.0f + 0.5f);
    std::vector<uint32_t> pixels(frame.pixels.size());
    for (size_t i = 0; i < pixels.size(); i++) {
        uint32_t pixel = 0;
        const uint32_t alpha = (frame.glow[i] * strength + 128) >> 8;
        if (alpha) {
            pixel = ScalePremultiplied(colors[g_glow.rainbow ? (frame.hue[i] + shift) & 255 : 0], alpha);
        }
        BlendOver(pixel, frame.pixels[i]);
        pixels[i] = pixel;
    }
    return CursorFromPixels(pixels.data(), frame.width, frame.height, frame.hotX, frame.hotY);
}

class PointerCursors {
  public:
    ~PointerCursors() { Clear(); }

    void SetCustom(std::shared_ptr<const CursorFile> file) {
        Invalidate();
        custom_ = std::move(file);
    }

    RECT Reach() const {
        RECT reach{};
        for (const auto& frame : prepared_) {
            if (frame) {
                reach = {std::max(reach.left, frame->reach.left), std::max(reach.top, frame->reach.top),
                         std::max(reach.right, frame->reach.right),
                         std::max(reach.bottom, frame->reach.bottom)};
            }
        }
        return reach;
    }

    void SetScale(float scale) {
        if (fabsf(scale - scale_) < 0.01f) {
            return;
        }
        Invalidate();
        scale_ = scale;
    }

    void Invalidate() {
        for (HCURSOR& cursor : loop_) {
            if (cursor) {
                retired_.push_back(cursor);
                cursor = nullptr;
            }
        }
        if (customCursor_) {
            retired_.push_back(customCursor_);
            customCursor_ = nullptr;
        }
        prepared_.clear();
        customKey_ = -1;
    }

    void StartPop(double now) {
        popStart_ = now;
        popFrameAt_ = -1e9;
        animationStart_ = now;
    }

    void ReleaseRetired(HCURSOR onScreen) {
        for (HCURSOR cursor : retired_) {
            if (cursor != onScreen) {
                DestroyCursor(cursor);
            }
        }
        retired_.clear();
    }

    HCURSOR Current(double now) {
        if (custom_) {
            if (HCURSOR cursor = CurrentCustom(now)) {
                return cursor;
            }
        }
        const double loopT = fmod(now, kLoopMs) / kLoopMs;
        const double sincePop = now - popStart_;
        if (sincePop >= 0 && sincePop < kPopMs) {
            if (transient_ && now - popFrameAt_ < popCostMs_ * 2.0) {
                return transient_;
            }
            PointerFrame frame{scale_, static_cast<float>(loopT),
                               static_cast<float>(sincePop / kPopMs),
                               static_cast<float>(EaseOutCubic(sincePop / 260.0)),
                               static_cast<float>(loopT)};
            const double started = NowMs();
            if (HCURSOR cursor = CreatePointerCursor(frame)) {
                popCostMs_ = NowMs() - started;
                popFrameAt_ = now;
                if (transient_) {
                    retired_.push_back(transient_);
                }
                transient_ = cursor;
                return cursor;
            }
        }

        if (transient_) {
            retired_.push_back(transient_);
            transient_ = nullptr;
        }
        const int index = static_cast<int>(loopT * kLoopFrames) % kLoopFrames;
        if (!loop_[index]) {
            const float t = static_cast<float>(index) / kLoopFrames;
            loop_[index] = CreatePointerCursor({scale_, t, 1.0f, 1.0f, t});
        }
        return loop_[index] ? loop_[index] : LoadCursorW(nullptr, IDC_ARROW);
    }

    double NextChange(double now) const {
        if (now - popStart_ < kPopMs) {
            return 15.0;
        }
        const double frameMs = kLoopMs / kLoopFrames;
        return frameMs - fmod(now, frameMs) + 0.5;
    }

    void Clear() {
        for (HCURSOR& cursor : loop_) {
            if (cursor) {
                DestroyCursor(cursor);
                cursor = nullptr;
            }
        }
        if (transient_) {
            DestroyCursor(transient_);
            transient_ = nullptr;
        }
        if (customCursor_) {
            DestroyCursor(customCursor_);
            customCursor_ = nullptr;
        }
        prepared_.clear();
        customKey_ = -1;
        for (HCURSOR cursor : retired_) {
            DestroyCursor(cursor);
        }
        retired_.clear();
    }

  private:
    static constexpr int kLoopFrames = 192;
    static constexpr double kLoopMs = kGlowPeriodMs;
    static constexpr double kPopMs = 420.0;

    HCURSOR CurrentCustom(double now) {
        const CursorFile& file = *custom_;
        const double loopT = fmod(now, kLoopMs) / kLoopMs;
        const double sincePop = now - popStart_;
        const bool popping = sincePop >= 0 && sincePop < kPopMs;
        const int glowIndex = static_cast<int>(loopT * kLoopFrames) % kLoopFrames;
        const double position = fmod(std::max(0.0, now - animationStart_), file.steps.back().end);
        const size_t step = std::min<size_t>(
            std::upper_bound(file.steps.begin(), file.steps.end(), position,
                             [](double time, const CursorStep& candidate) { return time < candidate.end; }) -
                file.steps.begin(),
            file.steps.size() - 1);
        const int64_t key = ((static_cast<int64_t>(step) * kLoopFrames + glowIndex) << 6) +
                            (popping ? 1 + static_cast<int>(sincePop / 16.0) : 0);
        if (customCursor_ && key == customKey_) {
            return customCursor_;
        }
        const size_t frame = file.steps[step].frame;
        if (prepared_.size() != file.frames.size()) {
            prepared_.resize(file.frames.size());
        }
        if (!prepared_[frame]) {
            size_t bytes = 0;
            for (const auto& other : prepared_) {
                bytes += other ? other->pixels.size() * 6 : 0;
            }
            if (bytes > 96 * 1024 * 1024) {
                prepared_.clear();
                prepared_.resize(file.frames.size());
            }
            auto prepared = std::make_unique<PreparedCursor>();
            if (!PrepareCursor(file, frame, scale_, *prepared)) {
                Wh_Log(L"Couldn't prepare the custom cursor");
                custom_.reset();
                return nullptr;
            }
            prepared_[frame] = std::move(prepared);
        }
        const float t = static_cast<float>(glowIndex) / kLoopFrames;
        const float reveal = popping ? static_cast<float>(EaseOutCubic(sincePop / 260.0)) : 1.0f;
        HCURSOR cursor = RenderCustomCursor(*prepared_[frame],
                                            reveal * (0.62f + 0.38f * sinf(2.0f * kPi * t)), t);
        if (!cursor) {
            return nullptr;
        }
        if (customCursor_) {
            retired_.push_back(customCursor_);
        }
        customCursor_ = cursor;
        customKey_ = key;
        return cursor;
    }

    HCURSOR loop_[kLoopFrames] = {};
    HCURSOR transient_ = nullptr;
    std::vector<HCURSOR> retired_;
    float scale_ = 1.0f;
    double popStart_ = -1e9;
    double popFrameAt_ = -1e9;
    double popCostMs_ = 0;
    std::shared_ptr<const CursorFile> custom_;
    std::vector<std::unique_ptr<PreparedCursor>> prepared_;
    HCURSOR customCursor_ = nullptr;
    int64_t customKey_ = -1;
    double animationStart_ = 0;
};

////////////////////////////////////////////////////////////////////////////////
// The hint next to the pointer

class HintPill {
  public:
    void Show(POINT cursor, float scale, bool dark, double now) {
        if (!panel_.Create(false, true, kLayerWindowClass, nullptr)) {
            return;
        }
        if (fabsf(scale - scale_) > 0.01f || dark != panel_.Dark() ||
            styleVersion_ != g_styleVersion || !content_.Valid()) {
            scale_ = scale;
            styleVersion_ = g_styleVersion;
            panel_.Configure(dark);
            Render();
        }
        shownAt_ = now;
        state_ = State::In;
        const POINT pos = Placement(cursor);
        panel_.Present(content_, pos.x, pos.y, 0);
        panel_.PresentUnderlay(underlay_, margin_, 0);
        panel_.Show(false);
    }

    void SetReach(const RECT& reach) { reach_ = reach; }

    void Follow(POINT cursor) {
        if (state_ != State::Hidden) {
            const POINT pos = Placement(cursor);
            panel_.Move(pos.x, pos.y);
        }
    }

    void FadeOut(double now) {
        if (state_ == State::In || state_ == State::Shown) {
            state_ = State::Out;
            fadeOutAt_ = now;
        }
    }

    void HideNow() {
        state_ = State::Hidden;
        panel_.Hide();
    }

    double Tick(double now) {
        switch (state_) {
            case State::In: {
                const double t = (now - shownAt_) / 180.0;
                const BYTE alpha = static_cast<BYTE>(EaseOutCubic(t) * 255);
                panel_.SetUnderlayAlpha(static_cast<BYTE>(alpha * GlowBreath(now)));
                panel_.SetAlpha(alpha);
                if (t >= 1.0) {
                    state_ = State::Shown;
                    return 1000.0 / 60.0;
                }
                return 0;
            }
            case State::Out: {
                const double t = (now - fadeOutAt_) / 200.0;
                if (t >= 1.0) {
                    HideNow();
                    return 1e9;
                }
                const BYTE alpha = static_cast<BYTE>((1.0 - t) * 255);
                panel_.SetAlpha(alpha);
                panel_.SetUnderlayAlpha(alpha);
                return 0;
            }
            case State::Shown:
                panel_.SetUnderlayAlpha(static_cast<BYTE>(255.0f * GlowBreath(now) + 0.5f));
                return 1000.0 / 60.0;
            default:
                return 1e9;
        }
    }

    bool Visible() const { return state_ != State::Hidden; }
    double ShownAt() const { return shownAt_; }
    HWND Hwnd() const { return panel_.Hwnd(); }
    HWND UnderlayHwnd() const { return panel_.UnderlayHwnd(); }
    void Destroy() { panel_.Destroy(); }

  private:
    enum class State { Hidden, In, Shown, Out };

    void Render() {
        const float s = scale_;
        const bool dark = panel_.Dark();
        HFONT font = g_fonts.Get(static_cast<int>(lroundf(13.5f * s)), FW_SEMIBOLD);
        const std::wstring hint = TrFormat(
            g_settings.typeToAsk ? Str::HintTextTyping : Str::HintText, AssistantName());
        const int textWidth =
            text_.Width(font, hint.c_str(), static_cast<int>(hint.size()));
        width_ = static_cast<int>(ceilf((10 + 18 + 8 + 14) * s)) + textWidth;
        height_ = static_cast<int>(ceilf(34 * s));
        margin_ = static_cast<int>(ceilf(84 * s));

        Surface foreground;
        if (!foreground.Resize(width_, height_) || !content_.Resize(width_, height_)) {
            return;
        }
        FillSparkleGradient(foreground, (10 + 9) * s, height_ * 0.5f, 7.5f * s,
                            0.0f, 0.05f);
        const RECT textRect{static_cast<LONG>((10 + 18 + 8) * s), 0, width_, height_};
        text_.Draw(foreground, font, hint, textRect,
                   DT_SINGLELINE | DT_VCENTER | DT_LEFT,
                   dark ? WithAlpha(kWhite, 0.96f) : WithAlpha(kBlack, 0.88f));
        PaintPanelBase(content_, panel_, s);
        for (int y = 0; y < height_; y++) {
            for (int x = 0; x < width_; x++) {
                BlendOver(content_.Row(y)[x], foreground.Row(y)[x]);
            }
        }
        PaintPanelUnderlay(underlay_, width_, height_, margin_, panel_.Radius(s), s,
                           dark, dark ? 0.85f : 0.65f, 0.0f);
    }

    POINT Placement(POINT cursor) const {
        const RECT monitor = MonitorRectAt(cursor, false);
        const auto clear = [&](int least, LONG reach) {
            return std::max(static_cast<int>(least * scale_), static_cast<int>(reach + 6 * scale_));
        };
        int x = cursor.x + clear(26, reach_.right);
        int y = cursor.y + clear(26, reach_.bottom);
        if (x + width_ > monitor.right) {
            x = cursor.x - clear(12, reach_.left) - width_;
        }
        if (y + height_ > monitor.bottom) {
            y = cursor.y - clear(20, reach_.top) - height_;
        }
        return {x, y};
    }

    GlassPanel panel_;
    Surface content_;
    Surface underlay_;
    TextPainter text_;
    float scale_ = 0;
    int styleVersion_ = 0;
    int width_ = 0;
    int height_ = 0;
    int margin_ = 0;
    double shownAt_ = 0;
    double fadeOutAt_ = 0;
    RECT reach_{};
    State state_ = State::Hidden;
};

////////////////////////////////////////////////////////////////////////////////
// Raster workers and the selection outline
class RasterWorkers {
  public:
    ~RasterWorkers() { Reset(); }
    void Reset() {
        if (work_) {
            WaitForThreadpoolWorkCallbacks(work_, TRUE);
            CloseThreadpoolWork(work_);
            work_ = nullptr;
        }
        if (pool_) {
            DestroyThreadpoolEnvironment(&environment_);
            CloseThreadpool(pool_);
            pool_ = nullptr;
        }
        renderRow_ = {};
        attempted_ = false;
    }

    void ForRows(int first, int last, const std::function<void(int)>& renderRow, bool parallel,
                 int batchSize = 16) {
        if (parallel && !attempted_) {
            attempted_ = true;
            SYSTEM_INFO system;
            GetSystemInfo(&system);
            workerCount_ = std::min<DWORD>(2, system.dwNumberOfProcessors > 1
                                           ? system.dwNumberOfProcessors - 1 : 0u);
            if (workerCount_) {
                pool_ = CreateThreadpool(nullptr);
                if (pool_) {
                    InitializeThreadpoolEnvironment(&environment_);
                    SetThreadpoolCallbackPool(&environment_, pool_);
                    SetThreadpoolThreadMaximum(pool_, workerCount_);
                    if (SetThreadpoolThreadMinimum(pool_, workerCount_)) {
                        work_ = CreateThreadpoolWork(Callback, this, &environment_);
                    }
                }
            }
        }
        if (!parallel || !work_) {
            for (int y = first; y < last; y++) renderRow(y);
            return;
        }
        renderRow_ = renderRow;
        nextRow_ = first;
        lastRow_ = last;
        batchSize_ = std::max(1, batchSize);
        for (unsigned i = 0; i < workerCount_; i++) SubmitThreadpoolWork(work_);
        Run();
        WaitForThreadpoolWorkCallbacks(work_, FALSE);
        renderRow_ = {};
    }

  private:
    static void CALLBACK Callback(PTP_CALLBACK_INSTANCE, void* context, PTP_WORK) {
        static_cast<RasterWorkers*>(context)->Run();
    }
    void Run() {
        for (;;) {
            const int first = nextRow_.fetch_add(batchSize_, std::memory_order_relaxed);
            if (first >= lastRow_) return;
            for (int y = first; y < std::min(first + batchSize_, lastRow_); y++) renderRow_(y);
        }
    }
    PTP_POOL pool_ = nullptr;
    PTP_WORK work_ = nullptr;
    TP_CALLBACK_ENVIRON environment_{};
    std::function<void(int)> renderRow_;
    std::atomic<int> nextRow_{0};
    int lastRow_ = 0;
    int batchSize_ = 16;
    unsigned workerCount_ = 0;
    bool attempted_ = false;
};

enum class FrameStyle { Hover, Drag, Selected };

float OutlineCoverage(float x, float y, float l, float t, float r, float b,
                      float radius, float border) {
    auto distance = [&](float px, float py) {
        return fabsf(SdRoundRect(px, py, l, t, r, b, radius)) - border * 0.5f;
    };
    const float d = distance(x, y);
    if (fabsf(d) >= 1.0f) return Clamp01(0.5f - d);
    float coverage = 0;
    for (float dy : {-0.25f, 0.25f}) {
        for (float dx : {-0.25f, 0.25f}) {
            coverage += Clamp01(0.5f - distance(x + dx, y + dy) * 2.0f);
        }
    }
    return coverage * 0.25f;
}

class GlowFrame {
  public:
    void Show(const RECT& rect, FrameStyle style, float scale, double now, bool animate) {
        if (!window_.Hwnd() && !window_.Create(true, false, kLayerWindowClass, nullptr)) return;
        const float target[4] = {static_cast<float>(rect.left),
                                 static_cast<float>(rect.top),
                                 static_cast<float>(rect.right),
                                 static_cast<float>(rect.bottom)};
        const bool wasVisible = visible_ && opacityTo_ > 0;
        if (animate && wasVisible && style == style_) {
            for (int i = 0; i < 4; i++) {
                from_[i] = current_[i];
                to_[i] = target[i];
            }
            moveStart_ = now;
            moveDuration_ = 150.0;
        } else {
            for (int i = 0; i < 4; i++) {
                from_[i] = to_[i] = current_[i] = target[i];
            }
            moveDuration_ = 0;
        }
        const bool restyle =
            !visible_ || style != style_ || fabsf(scale - scale_) > 0.01f;
        if (style == FrameStyle::Selected && style_ != FrameStyle::Selected) {
            flashStart_ = now;
        }
        style_ = style;
        scale_ = scale;
        if (!wasVisible) {
            StartFade(now, 1.0f, style == FrameStyle::Hover ? 140.0 : 0.0);
        }
        visible_ = true;
        if (restyle) {
            Render(now);
        }
    }

    void FadeOut(double now) {
        if (visible_ && opacityTo_ > 0) {
            StartFade(now, 0.0f, style_ == FrameStyle::Hover ? 140.0 : 380.0);
        }
    }

    void HideNow() {
        visible_ = false;
        opacity_ = opacityTo_ = 0;
        window_.Hide();
    }

    void Conceal() { window_.Hide(); }

    double Tick(double now) {
        if (!visible_) {
            return 1e9;
        }
        if (moveDuration_ > 0) {
            const double t = (now - moveStart_) / moveDuration_;
            const float eased = static_cast<float>(EaseOutCubic(t));
            for (int i = 0; i < 4; i++) {
                current_[i] = from_[i] + (to_[i] - from_[i]) * eased;
            }
            if (t >= 1.0) {
                moveDuration_ = 0;
            }
        }
        if (fadeDuration_ > 0) {
            const double t = (now - fadeStart_) / fadeDuration_;
            opacity_ = opacityFrom_ +
                       (opacityTo_ - opacityFrom_) *
                           static_cast<float>(EaseOutCubic(t));
            if (t >= 1.0) {
                fadeDuration_ = 0;
                opacity_ = opacityTo_;
                if (opacityTo_ <= 0) {
                    HideNow();
                    return 1e9;
                }
            }
        }
        Render(now);
        return 1000.0 / 60.0;
    }

    bool Visible() const { return visible_; }
    FrameStyle Style() const { return style_; }
    HWND Hwnd() const { return window_.Hwnd(); }

    void Destroy() {
        window_.Destroy();
        composite_.Reset();
        workers_.Reset();
        for (Bloom& bloom : blooms_) bloom = {};
        masksReady_ = false;
        visible_ = false;
    }

  private:
    struct Look {
        float border;
        float tightSigma, tightAlpha;
        float wideSigma, wideAlpha;
    };

    Look CurrentLook(double now) const {
        Look look;
        switch (style_) {
            case FrameStyle::Hover:
                look = {1.1f, 3.0f, 0.34f, 12.0f, 0.16f};
                break;
            case FrameStyle::Drag:
                look = {1.3f, 3.6f, 0.42f, 14.0f, 0.20f};
                break;
            case FrameStyle::Selected:
            default:
                look = {1.4f, 4.0f, 0.46f, 16.0f, 0.22f};
                break;
        }
        const double sinceFlash = now - flashStart_;
        if (style_ == FrameStyle::Selected && sinceFlash < 500.0) {
            const float flash = static_cast<float>(1.0 - EaseOutCubic(sinceFlash / 500.0));
            look.tightAlpha = std::min(1.0f, look.tightAlpha + 0.35f * flash);
            look.wideAlpha = std::min(1.0f, look.wideAlpha + 0.30f * flash);
        }
        const float pulse = GlowBreath(now);
        look.tightAlpha *= pulse;
        look.wideAlpha *= pulse;
        return look;
    }

    void StartFade(double now, float to, double duration) {
        opacityFrom_ = opacity_;
        opacityTo_ = to;
        fadeStart_ = now;
        fadeDuration_ = duration;
        if (duration <= 0) {
            opacity_ = to;
        }
    }

    BYTE AlphaByte() const {
        return static_cast<BYTE>(Clamp01(opacity_) * 255.0f + 0.5f);
    }

    struct Bloom {
        std::vector<float> core, tight, wide;
    };

    static void BuildBloom(Bloom& bloom, RECT part, float l, float t, float r, float b,
                    float radius, float border, float tight, float wide) {
        const int padding = static_cast<int>(ceilf(wide * 3.0f)) + 6;
        const int width = part.right - part.left, height = part.bottom - part.top;
        const int workWidth = width + padding * 2, workHeight = height + padding * 2;
        const int left = part.left - padding, top = part.top - padding;
        std::vector<float> outline(static_cast<size_t>(workWidth) * workHeight, 0);
        const float reach = border * 0.5f + 1.0f;
        const int firstX = std::max(0, static_cast<int>(floorf(l - reach)) - left);
        const int lastX = std::min(workWidth, static_cast<int>(ceilf(r + reach)) - left);
        for (int y = 0; y < workHeight; y++) {
            const float py = top + y + 0.5f;
            if (py < t - reach || py > b + reach) continue;
            auto span = [&](int first, int last) {
                for (int x = first; x < last; x++) {
                    outline[static_cast<size_t>(y) * workWidth + x] = OutlineCoverage(
                        left + x + 0.5f, py, l, t, r, b, radius, border);
                }
            };
            if (py > t + radius + reach && py < b - radius - reach) {
                span(firstX, std::min(lastX, static_cast<int>(ceilf(l + reach)) - left));
                span(std::max(firstX, static_cast<int>(floorf(r - reach)) - left), lastX);
            } else {
                span(firstX, lastX);
            }
        }
        const auto tightBlur = BlurCoverage(outline, workWidth, workHeight, tight);
        const auto wideBlur = BlurCoverage(outline, workWidth, workHeight, wide);
        const size_t pixels = static_cast<size_t>(width) * height;
        bloom.core.resize(pixels);
        bloom.tight.resize(pixels);
        bloom.wide.resize(pixels);
        const float tightGain = 2.506628f * tight / border;
        const float wideGain = 2.506628f * wide / border;
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                const size_t src = static_cast<size_t>(y + padding) * workWidth + x + padding;
                const size_t dst = static_cast<size_t>(y) * width + x;
                bloom.core[dst] = outline[src];
                bloom.tight[dst] = tightBlur[src] * tightGain;
                bloom.wide[dst] = wideBlur[src] * wideGain;
            }
        }
    }

    void Render(double now) {
        const float l = current_[0];
        const float t = current_[1];
        const float r = std::max(current_[2], l + 1);
        const float b = std::max(current_[3], t + 1);
        const float s = scale_;
        const Look look = CurrentLook(now);

        const float radius = std::min(12.0f * s, std::min(r - l, b - t) * 0.5f);
        const float border = look.border * s;
        const float tight = look.tightSigma * s;
        const float wide = look.wideSigma * s;
        const float phase = style_ == FrameStyle::Hover
                                ? 0.0f
                                : static_cast<float>(fmod(now / 2800.0, 1.0));

        const int outer = static_cast<int>(ceilf(wide * 4.0f + border));
        const int inner = outer;
        const bool rebuild = !masksReady_ || maskScale_ != s || maskStyle_ != style_ ||
                             !std::equal(std::begin(current_), std::end(current_), std::begin(maskRect_));

        const RECT outerRect{static_cast<LONG>(floorf(l)) - outer,
                             static_cast<LONG>(floorf(t)) - outer,
                             static_cast<LONG>(ceilf(r)) + outer,
                             static_cast<LONG>(ceilf(b)) + outer};
        const RECT innerRect{static_cast<LONG>(ceilf(l)) + inner,
                             static_cast<LONG>(ceilf(t)) + inner,
                             static_cast<LONG>(floorf(r)) - inner,
                             static_cast<LONG>(floorf(b)) - inner};
        RECT parts[4];
        int count;
        if (innerRect.right <= innerRect.left || innerRect.bottom <= innerRect.top) {
            parts[0] = outerRect;
            count = 1;
        } else {
            parts[0] = {outerRect.left, outerRect.top, outerRect.right, innerRect.top};
            parts[1] = {outerRect.left, innerRect.bottom, outerRect.right, outerRect.bottom};
            parts[2] = {outerRect.left, innerRect.top, innerRect.left, innerRect.bottom};
            parts[3] = {innerRect.right, innerRect.top, outerRect.right, innerRect.bottom};
            count = 4;
        }

        uint32_t colors[64];
        uint32_t lines[64];
        for (int i = 0; i < 64; i++) {
            const Color c = g_glow.At(i / 64.0f);
            colors[i] = PackPremultiplied(c, 1.0f);
            lines[i] = PackPremultiplied(Mix(c, kWhite, 0.65f), 1.0f);
        }

        const float cx = (l + r) * 0.5f;
        const float cy = (t + b) * 0.5f;
        if (rebuild) {
            workers_.ForRows(0, count, [&](int i) {
                BuildBloom(blooms_[i], parts[i], l, t, r, b, radius, border, tight, wide);
            }, count > 1 &&
               static_cast<uint64_t>(outerRect.right - outerRect.left) *
                   (outerRect.bottom - outerRect.top) >= 300000, 1);
        }
        for (int i = 0; i < 4; i++) {
            if (i >= count) {
                stripUsed_[i] = false;
                continue;
            }
            const RECT& part = parts[i];
            Surface& surface = surfaces_[i];
            stripUsed_[i] = false;
            if (!surface.Resize(part.right - part.left, part.bottom - part.top)) {
                masksReady_ = false;
                continue;
            }
            Bloom& bloom = blooms_[i];
            for (int y = 0; y < surface.Height(); y++) {
                uint32_t* row = surface.Row(y);
                const float py = part.top + y + 0.5f;
                for (int x = 0; x < surface.Width(); x++) {
                    const float px = part.left + x + 0.5f;
                    const size_t index = static_cast<size_t>(y) * surface.Width() + x;
                    const float glow = Clamp01(look.tightAlpha * bloom.tight[index] +
                                               look.wideAlpha * bloom.wide[index]);
                    const float edge = bloom.core[index];
                    if (glow < 0.5f / 255.0f && edge <= 0.0f) {
                        continue;
                    }
                    int c = 0;
                    if (g_glow.rainbow) {
                        float hue = FastAtan2(py - cy, px - cx) / (2.0f * kPi) + phase;
                        hue -= floorf(hue);
                        c = static_cast<int>(hue * 64.0f) & 63;
                    }
                    uint32_t pixel = ScalePremultiplied(
                        colors[c], static_cast<uint32_t>(glow * 255.0f + 0.5f));
                    if (edge > 0.0f) {
                        BlendOver(pixel, ScalePremultiplied(
                                             lines[c], static_cast<uint32_t>(
                                                           edge * 222.0f + 0.5f)));
                    }
                    row[x] = pixel;
                }
            }
            stripUsed_[i] = true;
            partRects_[i] = part;
        }
        masksReady_ = std::all_of(stripUsed_, stripUsed_ + count, [](bool used) { return used; });
        if (masksReady_) {
            std::copy_n(current_, 4, maskRect_);
            maskScale_ = s;
            maskStyle_ = style_;
        }
        if (!composite_.Resize(outerRect.right - outerRect.left, outerRect.bottom - outerRect.top)) return;
        for (int i = 0; i < count; i++) {
            if (!stripUsed_[i]) continue;
            const Surface& source = surfaces_[i];
            const int offsetX = partRects_[i].left - outerRect.left;
            const int offsetY = partRects_[i].top - outerRect.top;
            for (int y = 0; y < source.Height(); y++) {
                memcpy(composite_.Row(offsetY + y) + offsetX, source.Row(y),
                       static_cast<size_t>(source.Width()) * sizeof(uint32_t));
            }
        }
        window_.Present(composite_, outerRect.left, outerRect.top, AlphaByte());
        window_.Show();
    }

    LayeredWindow window_;
    Surface composite_;
    Surface surfaces_[4];
    RECT partRects_[4] = {};
    bool stripUsed_[4] = {};
    Bloom blooms_[4];
    RasterWorkers workers_;
    float maskRect_[4]{};
    float maskScale_ = 0;
    FrameStyle maskStyle_ = FrameStyle::Hover;
    bool masksReady_ = false;
    float from_[4] = {};
    float to_[4] = {};
    float current_[4] = {};
    double moveStart_ = 0;
    double moveDuration_ = 0;
    float opacity_ = 0;
    float opacityFrom_ = 0;
    float opacityTo_ = 0;
    double fadeStart_ = 0;
    double fadeDuration_ = 0;
    double flashStart_ = -1e9;
    FrameStyle style_ = FrameStyle::Hover;
    float scale_ = 1.0f;
    bool visible_ = false;
};

////////////////////////////////////////////////////////////////////////////////
// The ripple

struct RippleWave {
    float displacement;
    float opacity;
    float light;
};

RippleWave EvaluateRippleWave(float distance, float sigma, float strength) {
    const float u = distance / sigma;
    const float envelope = expf(-0.5f * u * u);
    return {-strength * u * envelope,
            Clamp01(envelope * 4.0f),
            0.055f * envelope};
}

extern std::atomic<bool> g_stopping;
extern std::atomic<int> g_helperThreads;

float MonitorFrameMs(const RECT& monitor) {
    const POINT center{(monitor.left + monitor.right) / 2, (monitor.top + monitor.bottom) / 2};
    MONITORINFOEXW info{};
    info.cbSize = sizeof(info);
    DEVMODEW mode{};
    mode.dmSize = sizeof(mode);
    if (GetMonitorInfoW(MonitorFromPoint(center, MONITOR_DEFAULTTONEAREST), &info) &&
        EnumDisplaySettingsW(info.szDevice, ENUM_CURRENT_SETTINGS, &mode) &&
        mode.dmDisplayFrequency > 1) {
        return 1000.0f / static_cast<float>(std::clamp<DWORD>(mode.dmDisplayFrequency, 60, 144));
    }
    return 1000.0f / 60.0f;
}

struct RippleCapture {
    Surface snapshot;
    Surface canvas;
    RECT monitor{};
    int centerY = 0;
    HWND window = nullptr;
    HWND notify = nullptr;
    std::atomic<float> frameMs{1000.0f / 60.0f};
    std::atomic<bool> canceled{false};
    std::atomic<bool> warming{false};
    std::atomic<bool> warmed{false};
    std::atomic<int> top{0};
    std::atomic<int> bottom{0};
};

struct RippleCaptureMessage {
    std::shared_ptr<RippleCapture> capture;
    bool first = false;
    bool complete = false;
    bool failed = false;
};

std::vector<std::pair<int, int>> PlanRippleStripes(int width, int height, int centerY) {
    std::vector<std::pair<int, int>> stripes;
    const int rows = std::max(64, 2200000 / std::max(width, 1));
    if (height <= rows) {
        stripes.push_back({0, height});
        return stripes;
    }
    int top = std::clamp(centerY - rows / 2, 0, height - rows);
    int bottom = top + rows;
    stripes.push_back({top, bottom});
    while (top > 0 || bottom < height) {
        if (top > 0) {
            const int count = std::min(rows, top);
            stripes.push_back({top - count, top});
            top -= count;
        }
        if (bottom < height) {
            const int count = std::min(rows, height - bottom);
            stripes.push_back({bottom, bottom + count});
            bottom += count;
        }
    }
    return stripes;
}

DWORD WINAPI RippleCaptureThreadProc(LPVOID param) {
    std::unique_ptr<std::shared_ptr<RippleCapture>> holder(
        static_cast<std::shared_ptr<RippleCapture>*>(param));
    const std::shared_ptr<RippleCapture> capture = *holder;
    const int width = capture->monitor.right - capture->monitor.left;
    const int height = capture->monitor.bottom - capture->monitor.top;
    auto stopped = [&] { return capture->canceled.load() || g_stopping.load(); };
    auto post = [&](bool first, bool complete, bool failed) {
        auto message = std::make_unique<RippleCaptureMessage>();
        message->capture = capture;
        message->first = first;
        message->complete = complete;
        message->failed = failed;
        PostOwned(capture->notify, WM_APP_RIPPLE, std::move(message));
    };

    capture->frameMs = MonitorFrameMs(capture->monitor);
    bool ok = capture->snapshot.Resize(width, height) && capture->canvas.Resize(width, height);
    HDC screen = ok ? GetDC(nullptr) : nullptr;
    ok = ok && screen;
    if (ok) {
        capture->warming = true;
        if (!stopped()) {
            POINT destination{capture->monitor.left, capture->monitor.top};
            SIZE size{width, height};
            POINT source{0, 0};
            BLENDFUNCTION blend{AC_SRC_OVER, 0, 255, AC_SRC_ALPHA};
            capture->warmed = UpdateLayeredWindow(capture->window, nullptr, &destination, &size,
                                                  capture->canvas.Dc(), &source, 0, &blend,
                                                  ULW_ALPHA) != FALSE;
        }
        capture->warming = false;
    }
    const auto stripes = PlanRippleStripes(width, height, capture->centerY);
    int top = 0;
    int bottom = 0;
    for (size_t i = 0; ok && i < stripes.size() && !stopped(); i++) {
        const int begin = stripes[i].first;
        const int end = stripes[i].second;
        if (!BitBlt(capture->snapshot.Dc(), 0, begin, width, end - begin, screen,
                    capture->monitor.left, capture->monitor.top + begin,
                    SRCCOPY | CAPTUREBLT)) {
            ok = false;
            break;
        }
        GdiFlush();
        if (i == 0) {
            top = begin;
            bottom = end;
        } else if (end == top) {
            top = begin;
        } else {
            bottom = end;
        }
        capture->top.store(top, std::memory_order_release);
        capture->bottom.store(bottom, std::memory_order_release);
        const bool last = i + 1 == stripes.size();
        if (i == 0 || last) {
            post(i == 0, last, false);
        }
    }
    if (screen) {
        ReleaseDC(nullptr, screen);
    }
    if (!ok && !stopped()) {
        post(false, true, true);
    }
    g_helperThreads--;
    return 0;
}

class Ripple {
  public:
    static constexpr double kDurationMs = 1650.0;

    bool Prepare(POINT center, float scale, HWND notify) {
        Stop();
        if (!window_.Hwnd() && !window_.Create(true, false, kLayerWindowClass, nullptr)) {
            return false;
        }
        monitor_ = MonitorRectAt(center, false);
        const int w = monitor_.right - monitor_.left;
        const int h = monitor_.bottom - monitor_.top;
        if (w <= 0 || h <= 0) {
            return false;
        }
        center_ = {static_cast<float>(center.x - monitor_.left),
                   static_cast<float>(center.y - monitor_.top)};
        scale_ = scale;
        float farthest = 0;
        for (const Vec2 corner : {Vec2{0, 0}, Vec2{static_cast<float>(w), 0},
                                  Vec2{0, static_cast<float>(h)},
                                  Vec2{static_cast<float>(w), static_cast<float>(h)}}) {
            farthest = std::max(farthest, hypotf(corner.x - center_.x, corner.y - center_.y));
        }
        maxRadius_ = farthest + 100.0f * scale;

        auto capture = std::make_shared<RippleCapture>();
        capture->monitor = monitor_;
        capture->centerY = static_cast<int>(center_.y);
        capture->window = window_.Hwnd();
        capture->notify = notify;
        auto* holder = new std::shared_ptr<RippleCapture>(capture);
        g_helperThreads++;
        HANDLE thread = CreateThread(nullptr, 0, RippleCaptureThreadProc, holder, 0, nullptr);
        if (!thread) {
            g_helperThreads--;
            delete holder;
            return false;
        }
        CloseHandle(thread);
        capture_ = std::move(capture);
        return true;
    }

    bool Owns(const std::shared_ptr<RippleCapture>& capture) const {
        return capture_ && capture_ == capture;
    }

    bool Capturing() const { return capture_ != nullptr; }

    double FrameMs() const { return frameMs_; }

    void Launch(double now, double fastestFrameMs) {
        if (!capture_ || active_) {
            return;
        }
        frameMs_ = std::max<double>(capture_->frameMs.load(), fastestFrameMs);
        surface_.Swap(capture_->canvas);
        if (!surface_.Valid() || !capture_->snapshot.Valid()) {
            Stop();
            return;
        }
        ResetFrames(surface_.Height());
        if (capture_->warmed) {
            window_.AdoptPresented(monitor_.left, monitor_.top, surface_.Width(),
                                   surface_.Height(), 255);
            firstFrame_ = false;
        }
        start_ = std::max(now, NowMs());
        active_ = true;
        Render(start_);
        window_.Show();
    }

    double Tick(double now) {
        if (!active_) {
            return 1e9;
        }
        if (now - start_ >= kDurationMs) {
            Stop();
            return 1e9;
        }
        Render(now);
        return frameMs_;
    }

    void Stop() {
        workers_.Reset();
        active_ = false;
        window_.Hide();
        if (capture_) {
            capture_->canceled = true;
            for (int i = 0; i < 100 && capture_->warming; i++) {
                Sleep(1);
            }
            capture_.reset();
        }
        surface_.Reset();
        wave_.clear();
        rows_.clear();
    }

    bool Active() const { return active_; }
    HWND Hwnd() const { return window_.Hwnd(); }
    void Destroy() {
        Stop();
        window_.Destroy();
    }

  private:
    struct RasterWave {
        float displacement;
        uint32_t opacity;
        uint32_t lightAlpha;
        uint32_t light;
    };

    struct RowSpans {
        int begin[2] = {0, 0};
        int end[2] = {0, 0};
    };

    void ResetFrames(int height) {
        rows_.assign(static_cast<size_t>(height), RowSpans{});
        drawnFirst_ = drawnLast_ = 0;
        drawnX0_ = drawnX1_ = 0;
        firstFrame_ = true;
        step_ = 1;
        averageMs_ = -1;
    }

    void ClearRow(int y) {
        RowSpans& spans = rows_[y];
        uint32_t* row = surface_.Row(y);
        for (int i = 0; i < 2; i++) {
            if (spans.end[i] > spans.begin[i]) {
                memset(row + spans.begin[i], 0,
                       static_cast<size_t>(spans.end[i] - spans.begin[i]) * sizeof(uint32_t));
            }
        }
        spans = {};
    }

    void AdaptQuality(double frameMs) {
        const double limit = std::clamp(frameMs_ * 1.5, 14.0, 20.0);
        averageMs_ = averageMs_ < 0 ? frameMs : averageMs_ * 0.5 + frameMs * 0.5;
        if (step_ < 3 && averageMs_ > limit) {
            step_++;
            averageMs_ = -1;
        } else if (step_ > 1 &&
                   averageMs_ * step_ * step_ / ((step_ - 1) * (step_ - 1)) * 0.8 < limit * 0.6) {
            step_--;
            averageMs_ = -1;
        }
    }

    void Render(double now) {
        const double frameStart = NowMs();
        const float t = static_cast<float>(std::clamp((now - start_) / kDurationMs, 0.0, 1.0));
        const float elapsed = static_cast<float>(now - start_);
        const int w = surface_.Width();
        const int h = surface_.Height();
        if (!capture_ || rows_.size() != static_cast<size_t>(h)) {
            return;
        }

        const float travel = t * t * (3.0f - 2.0f * t);
        const float radius = travel * maxRadius_;
        const float sigma = (40.0f + 38.0f * travel) * scale_;
        const float in = Clamp01(elapsed / 180.0f);
        const float out = Clamp01((t - 0.55f) / 0.45f);
        const float fadeIn = in * in * (3.0f - 2.0f * in);
        const float fadeOut = 1.0f - out * out * (3.0f - 2.0f * out);
        const float strength = 14.0f * scale_ * fadeIn * fadeOut;
        const float alpha = fadeIn * fadeOut;

        uint32_t colors[64];
        for (int i = 0; i < 64; i++) {
            colors[i] = PackPremultiplied(g_glow.At(i / 64.0f + t * 0.2f), 1.0f);
        }

        const float reach = sigma * 3.8f;
        const int offset = static_cast<int>(ceilf(reach * 4.0f));
        wave_.resize(static_cast<size_t>(offset) * 2 + 2);
        size_t firstWave = wave_.size();
        size_t lastWave = 0;
        for (size_t i = 0; i < wave_.size(); i++) {
            const RippleWave wave = EvaluateRippleWave((static_cast<int>(i) - offset) / 4.0f,
                                                        sigma, strength);
            RasterWave& entry = wave_[i];
            entry.displacement = wave.displacement;
            entry.opacity = static_cast<uint32_t>(wave.opacity * alpha * 255.0f + 0.5f);
            entry.lightAlpha = static_cast<uint32_t>(wave.light * alpha * 255.0f + 0.5f);
            entry.light = g_glow.rainbow ? 0 : ScalePremultiplied(colors[0], entry.lightAlpha);
            if (entry.lightAlpha > 0 ||
                (entry.opacity > 1 &&
                 fabsf(entry.displacement) * entry.opacity >= 0.03f * 255.0f)) {
                firstWave = std::min(firstWave, i);
                lastWave = i;
            }
        }

        float inner = 0;
        float outer = 0;
        int firstY = 0;
        int lastY = 0;
        if (firstWave <= lastWave) {
            inner = std::max(0.0f, radius + (static_cast<int>(firstWave) - offset) * 0.25f - 1.0f);
            outer = radius + (static_cast<int>(lastWave) + 1 - offset) * 0.25f + 1.0f;
            const int capturedTop = capture_->top.load(std::memory_order_acquire);
            const int capturedBottom = capture_->bottom.load(std::memory_order_acquire);
            const int margin = static_cast<int>(ceilf(9.0f * scale_)) + 2;
            firstY = std::max(capturedTop > 0 ? capturedTop + margin : 0,
                              static_cast<int>(floorf(center_.y - outer)));
            lastY = std::min(capturedBottom < h ? capturedBottom - margin : h,
                             static_cast<int>(ceilf(center_.y + outer)));
        }
        const bool drawing = firstY < lastY;
        const float cx = center_.x;
        const float cy = center_.y;
        int firstX = 0;
        int lastX = 0;
        if (drawing) {
            firstX = std::max(0, static_cast<int>(floorf(cx - outer)));
            lastX = std::min(w, static_cast<int>(ceilf(cx + outer)) + 1);
        }

        const int step = step_;
        int rowsFirst = firstY;
        int rowsLast = lastY;
        int changedX0 = firstX;
        int changedX1 = lastX;
        if (drawnFirst_ < drawnLast_) {
            rowsFirst = drawing ? std::min(rowsFirst, drawnFirst_) : drawnFirst_;
            rowsLast = drawing ? std::max(rowsLast, drawnLast_) : drawnLast_;
            changedX0 = drawing ? std::min(changedX0, drawnX0_) : drawnX0_;
            changedX1 = drawing ? std::max(changedX1, drawnX1_) : drawnX1_;
        }
        drawnFirst_ = drawing ? firstY / step * step : 0;
        drawnLast_ = drawing ? std::min(h, (lastY + step - 1) / step * step) : 0;
        drawnX0_ = firstX;
        drawnX1_ = lastX;

        const Surface& snapshotSurface = capture_->snapshot;
        const OpaquePixels snapshot{snapshotSurface.Valid() ? snapshotSurface.Row(0) : nullptr,
                                    snapshotSurface.Width(), snapshotSurface.Height(),
                                    snapshotSurface.Stride()};
        const RasterWave* waves = wave_.data();
        const int waveCount = static_cast<int>(wave_.size());
        const float edgeWidth = 24.0f * scale_;
        const bool rainbow = g_glow.rainbow;

        auto shade = [&](float x, float y) -> uint32_t {
            const float dx = x - cx;
            const float dy = y - cy;
            const float distance = sqrtf(dx * dx + dy * dy);
            const int index = static_cast<int>((distance - radius) * 4.0f) + offset;
            if (index < 0 || index >= waveCount) {
                return 0;
            }
            const RasterWave& wave = waves[index];
            uint32_t pixel = 0;
            if (snapshot.pixels && wave.opacity > 1) {
                float edge = Clamp01(std::min(y, h - 1 - y) / edgeWidth);
                if (x < edgeWidth || w - 1 - x < edgeWidth) {
                    edge = std::min(edge, Clamp01(std::min(x, w - 1 - x) / edgeWidth));
                }
                const float displacement = wave.displacement * edge * edge *
                    (3.0f - 2.0f * edge) / std::max(distance, 1.0f);
                pixel = SampleOpaquePixels(snapshot, x + dx * displacement, y + dy * displacement);
                if (wave.opacity < 255) {
                    pixel = ScalePremultiplied(pixel, wave.opacity);
                }
            }
            if (wave.lightAlpha) {
                uint32_t light = wave.light;
                if (rainbow) {
                    const float phase = FastAtan2(dy, dx) / (2.0f * kPi);
                    light = ScalePremultiplied(
                        colors[static_cast<int>((phase - floorf(phase)) * 64.0f) & 63],
                        wave.lightAlpha);
                }
                BlendOver(pixel, light);
            }
            return pixel;
        };

        auto renderBlock = [&](int block) {
            const int y0 = block * step;
            const int y1 = std::min(h, y0 + step);
            RowSpans spans[4];
            RowSpans leader;
            bool any = false;
            for (int y = y0; y < y1; y++) {
                ClearRow(y);
                const float dy = y - cy;
                if (y < firstY || y >= lastY || fabsf(dy) >= outer) {
                    continue;
                }
                const float xo = sqrtf(std::max(0.0f, outer * outer - dy * dy));
                const float xi = fabsf(dy) < inner
                                     ? sqrtf(std::max(0.0f, inner * inner - dy * dy)) : 0.0f;
                const float edges[2][2] = {{cx - xo, cx - xi}, {cx + xi, cx + xo}};
                for (int i = 0; i < 2; i++) {
                    const int begin = std::max(0, static_cast<int>(ceilf(edges[i][0])));
                    const int end = std::min(w, static_cast<int>(ceilf(edges[i][1])));
                    if (end <= begin) {
                        continue;
                    }
                    spans[y - y0].begin[i] = begin;
                    spans[y - y0].end[i] = end;
                    if (leader.end[i] <= leader.begin[i]) {
                        leader.begin[i] = begin;
                        leader.end[i] = end;
                    } else {
                        leader.begin[i] = std::min(leader.begin[i], begin);
                        leader.end[i] = std::max(leader.end[i], end);
                    }
                    any = true;
                }
            }
            if (!any) {
                return;
            }
            uint32_t* leaderRow = surface_.Row(y0);
            const float blockCenter = (step - 1) * 0.5f;
            for (int i = 0; i < 2; i++) {
                for (int bx = leader.begin[i] / step * step; bx < leader.end[i]; bx += step) {
                    const uint32_t pixel = shade(bx + blockCenter, y0 + blockCenter);
                    if (!pixel) {
                        continue;
                    }
                    const int to = std::min(bx + step, leader.end[i]);
                    for (int x = std::max(bx, leader.begin[i]); x < to; x++) {
                        leaderRow[x] = pixel;
                    }
                }
            }
            for (int y = y0 + 1; y < y1; y++) {
                uint32_t* row = surface_.Row(y);
                for (int i = 0; i < 2; i++) {
                    const int begin = spans[y - y0].begin[i];
                    const int end = spans[y - y0].end[i];
                    if (end > begin) {
                        memcpy(row + begin, leaderRow + begin,
                               static_cast<size_t>(end - begin) * sizeof(uint32_t));
                    }
                }
                rows_[y] = spans[y - y0];
            }
            rows_[y0] = leader;
        };

        workers_.ForRows(rowsFirst / step, (rowsLast + step - 1) / step, renderBlock,
                         static_cast<uint64_t>(w) * h >= 500000, std::max(1, 16 / step));
        const RECT changed{changedX0, rowsFirst / step * step, changedX1,
                           std::min(h, (rowsLast + step - 1) / step * step)};
        if (firstFrame_) {
            window_.Present(surface_, monitor_.left, monitor_.top, 255);
            firstFrame_ = false;
        } else if (changed.right > changed.left && changed.bottom > changed.top) {
            window_.Present(surface_, monitor_.left, monitor_.top, 255, &changed);
        }
        AdaptQuality(NowMs() - frameStart);
    }

    LayeredWindow window_;
    Surface surface_;
    std::shared_ptr<RippleCapture> capture_;
    RECT monitor_{};
    Vec2 center_{};
    float scale_ = 1.0f;
    float maxRadius_ = 0;
    double start_ = 0;
    bool active_ = false;
    std::vector<RasterWave> wave_;
    std::vector<RowSpans> rows_;
    int drawnFirst_ = 0;
    int drawnLast_ = 0;
    int drawnX0_ = 0;
    int drawnX1_ = 0;
    bool firstFrame_ = true;
    int step_ = 1;
    double averageMs_ = -1;
    double frameMs_ = 1000.0 / 60.0;
    RasterWorkers workers_;
};

////////////////////////////////////////////////////////////////////////////////
// The input overlay

void OnOverlayMouse(UINT message, POINT screenPoint);
HCURSOR OverlayCursor();
void OnDisplayChanged();

void OutsideRectangles(RECT screen, RECT opening, RECT (&parts)[4]) {
    RECT hole;
    if (!IntersectRect(&hole, &screen, &opening)) {
        parts[0] = screen;
        parts[1] = parts[2] = parts[3] = {};
        return;
    }
    parts[0] = {screen.left, screen.top, screen.right, hole.top};
    parts[1] = {screen.left, hole.bottom, screen.right, screen.bottom};
    parts[2] = {screen.left, hole.top, hole.left, hole.bottom};
    parts[3] = {hole.right, hole.top, screen.right, hole.bottom};
}

bool RenderSelectionDimMask(Surface& mask, RECT screen, RECT opening, float feather) {
    if (!mask.Resize(screen.right - screen.left, screen.bottom - screen.top)) return false;
    for (int y = 0; y < mask.Height(); y++) {
        std::fill_n(mask.Row(y), mask.Width(), 0xFF000000u);
    }
    RECT hole;
    if (IntersectRect(&hole, &screen, &opening)) {
        for (int y = hole.top; y < hole.bottom; y++) {
            std::fill_n(mask.Row(y - screen.top) + hole.left - screen.left,
                        hole.right - hole.left, 0u);
        }
    }
    feather = std::max(feather, 1.0f);
    const LONG padding = static_cast<LONG>(ceilf(feather)) + 1;
    RECT bounds{opening.left - padding, opening.top - padding,
                opening.right + padding, opening.bottom + padding};
    if (IntersectRect(&bounds, &bounds, &screen)) {
        RECT parts[4];
        OutsideRectangles(bounds, opening, parts);
        for (RECT part : parts) {
            for (int y = part.top; y < part.bottom; y++) {
                uint32_t* row = mask.Row(y - screen.top);
                for (int x = part.left; x < part.right; x++) {
                    const float distance = SdRoundRect(x + 0.5f, y + 0.5f,
                        opening.left, opening.top, opening.right, opening.bottom, 0);
                    const float t = Clamp01(distance / feather);
                    const uint32_t alpha = static_cast<uint32_t>(t * t * (3 - 2 * t) * 255 + 0.5f);
                    row[x - screen.left] = alpha << 24;
                }
            }
        }
    }
    return true;
}

class InputOverlay {
  public:
    bool Create() {
        hwnd_ = CreateWindowExW(
            WS_EX_LAYERED | WS_EX_TOPMOST | WS_EX_TOOLWINDOW | WS_EX_NOACTIVATE,
            kOverlayWindowClass, L"Magic Pointer", WS_POPUP, 0, 0, 1, 1,
            nullptr, nullptr, g_instance, nullptr);
        if (hwnd_) {
            SetLayeredWindowAttributes(hwnd_, 0, 1, LWA_ALPHA);
            if (!dimWindow_.Create(true, false, kLayerWindowClass, nullptr)) {
                Destroy();
                return false;
            }
        }
        return hwnd_ != nullptr;
    }

    void Show(int dimPercent) {
        if (!hwnd_) {
            return;
        }
        const RECT screen = VirtualScreenRect();
        ClearSelection();
        dimPercent_ = std::clamp(dimPercent, 0, 80);
        SetLayeredWindowAttributes(hwnd_, 0, 1, LWA_ALPHA);
        SetWindowPos(hwnd_, HWND_TOPMOST, screen.left, screen.top,
                     screen.right - screen.left, screen.bottom - screen.top,
                     SWP_SHOWWINDOW | SWP_NOACTIVATE);
        visible_ = true;
        g_layersChanged = true;
    }

    void SetSelection(RECT rect, double now) {
        opening_ = rect;
        dimDirty_ = true;
        if (!dimming_ && dimPercent_ > 0) {
            dimming_ = true;
            dimStart_ = now;
        }
    }

    void ClearSelection() {
        dimming_ = false;
        dimDirty_ = false;
        dimAlpha_ = 0;
        dimWindow_.Hide();
        dimMask_.Reset();
    }

    void Hide() {
        ClearSelection();
        if (hwnd_ && visible_) {
            ShowWindow(hwnd_, SW_HIDE);
        }
        visible_ = false;
    }

    double Tick(double now) {
        if (!visible_ || !dimming_) {
            return 1e9;
        }
        const double t = (now - dimStart_) / 160.0;
        const BYTE alpha = static_cast<BYTE>(dimPercent_ * 255.0 / 100.0 * EaseOutCubic(t) + 0.5);
        if (alpha != dimAlpha_ || dimDirty_) {
            if (dimDirty_) {
                const RECT screen = VirtualScreenRect();
                if (RenderSelectionDimMask(dimMask_, screen, opening_,
                        6.0f * DpiScaleAt(RectCenter(opening_)))) {
                    dimWindow_.Present(dimMask_, screen.left, screen.top, alpha);
                    dimDirty_ = false;
                }
            } else {
                dimWindow_.SetAlpha(alpha);
            }
            if (alpha) dimWindow_.Show();
            else dimWindow_.Hide();
            dimAlpha_ = alpha;
        }
        return t >= 1.0 ? 1e9 : 0;
    }

    bool Visible() const { return visible_; }
    HWND Hwnd() const { return hwnd_; }
    HWND DimHwnd() const { return dimWindow_.Hwnd(); }

    void Destroy() {
        dimWindow_.Destroy();
        dimMask_.Reset();
        if (hwnd_) {
            DestroyWindow(hwnd_);
            hwnd_ = nullptr;
        }
        visible_ = false;
    }

    static LRESULT CALLBACK WndProc(HWND hwnd,
                                    UINT message,
                                    WPARAM wParam,
                                    LPARAM lParam) {
        switch (message) {
            case WM_MOUSEACTIVATE:
                return MA_NOACTIVATE;

            case WM_SETCURSOR:
                SetCursor(OverlayCursor());
                return TRUE;

            case WM_ERASEBKGND: {
                RECT rc;
                GetClientRect(hwnd, &rc);
                FillRect(reinterpret_cast<HDC>(wParam), &rc,
                         static_cast<HBRUSH>(GetStockObject(BLACK_BRUSH)));
                return 1;
            }

            case WM_MOUSEMOVE:
            case WM_LBUTTONDOWN:
            case WM_LBUTTONUP:
            case WM_RBUTTONDOWN:
            case WM_RBUTTONUP:
            case WM_MBUTTONUP:
            case WM_CAPTURECHANGED: {
                POINT pt{GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam)};
                if (message == WM_CAPTURECHANGED) {
                    GetCursorPos(&pt);
                } else {
                    ClientToScreen(hwnd, &pt);
                }
                OnOverlayMouse(message, pt);
                return 0;
            }

            case WM_DISPLAYCHANGE:
                OnDisplayChanged();
                break;
        }
        return DefWindowProcW(hwnd, message, wParam, lParam);
    }

  private:
    HWND hwnd_ = nullptr;
    bool visible_ = false;
    LayeredWindow dimWindow_;
    Surface dimMask_;
    RECT opening_{};
    int dimPercent_ = 0;
    BYTE dimAlpha_ = 0;
    bool dimming_ = false;
    bool dimDirty_ = false;
    double dimStart_ = 0;
};

////////////////////////////////////////////////////////////////////////////////
// Shake detection

class ShakeDetector {
  public:
    void Configure(int sensitivity) {
        minDistance_ = 1300.0 - 100.0 * sensitivity;
        minRatio_ = 5.0 - 0.3 * sensitivity;
        Clear();
    }

    void Clear() {
        samples_.clear();
        pathLength_ = 0;
    }

    bool AddPoint(double now, POINT pt, float dpiScale) {
        if (!samples_.empty() && samples_.back().x == pt.x &&
            samples_.back().y == pt.y) {
            return false;
        }

        if (samples_.size() >= 2 && now - samples_.back().time < 4.0) {
            Sample& last = samples_.back();
            const Sample& previous = samples_[samples_.size() - 2];
            pathLength_ -= last.segment;
            last.x = pt.x;
            last.y = pt.y;
            last.segment = Distance(previous.x, previous.y, pt.x, pt.y);
            pathLength_ += last.segment;
        } else {
            const double segment =
                samples_.empty() ? 0.0
                                 : Distance(samples_.back().x,
                                            samples_.back().y, pt.x, pt.y);
            samples_.push_back({now, pt.x, pt.y, segment});
            pathLength_ += segment;
        }

        while (samples_.size() > 1 && now - samples_.front().time > kWindowMs) {
            samples_.pop_front();
            pathLength_ -= samples_.front().segment;
            samples_.front().segment = 0;
        }
        if (samples_.size() <= 1) {
            pathLength_ = 0;
        }

        if (samples_.size() < 6 || pathLength_ < minDistance_ * dpiScale) {
            return false;
        }

        LONG minX = samples_.front().x, maxX = minX;
        LONG minY = samples_.front().y, maxY = minY;
        for (const Sample& sample : samples_) {
            minX = std::min(minX, sample.x);
            maxX = std::max(maxX, sample.x);
            minY = std::min(minY, sample.y);
            maxY = std::max(maxY, sample.y);
        }
        const double diagonal = Distance(minX, minY, maxX, maxY);
        return diagonal >= 1.0 && pathLength_ >= diagonal * minRatio_;
    }

  private:
    struct Sample {
        double time;
        LONG x;
        LONG y;
        double segment;  // Distance from the previous sample.
    };

    static double Distance(LONG x1, LONG y1, LONG x2, LONG y2) {
        return std::hypot(static_cast<double>(x2 - x1),
                          static_cast<double>(y2 - y1));
    }

    static constexpr double kWindowMs = 1000.0;
    std::deque<Sample> samples_;
    double pathLength_ = 0;
    double minDistance_ = 800.0;
    double minRatio_ = 3.5;
};

bool AnyMouseButtonDown() {
    return (GetAsyncKeyState(VK_LBUTTON) | GetAsyncKeyState(VK_RBUTTON) |
            GetAsyncKeyState(VK_MBUTTON) | GetAsyncKeyState(VK_XBUTTON1) |
            GetAsyncKeyState(VK_XBUTTON2)) &
           0x8000;
}

bool ForegroundIsFullscreen();

bool CanSummonNow() {
    CURSORINFO cursorInfo{};
    cursorInfo.cbSize = sizeof(cursorInfo);
    if (!GetCursorInfo(&cursorInfo) || !(cursorInfo.flags & CURSOR_SHOWING) ||
        (cursorInfo.flags & CURSOR_SUPPRESSED)) {
        return false;
    }

    RECT clip;
    if (GetClipCursor(&clip)) {
        const RECT monitor = MonitorRectAt(cursorInfo.ptScreenPos, false);
        if (clip.left > monitor.left || clip.top > monitor.top ||
            clip.right < monitor.right || clip.bottom < monitor.bottom) {
            return false;
        }
    }

    if (g_settings.disableInFullscreen) {
        QUERY_USER_NOTIFICATION_STATE state;
        if (SUCCEEDED(SHQueryUserNotificationState(&state)) &&
            (state == QUNS_BUSY || state == QUNS_RUNNING_D3D_FULL_SCREEN ||
             state == QUNS_PRESENTATION_MODE)) {
            return false;
        }
        if (ForegroundIsFullscreen()) {
            return false;
        }
    }
    return true;
}

////////////////////////////////////////////////////////////////////////////////
// Apps where shaking the mouse is part of using them

bool WildcardMatch(const wchar_t* pattern, const wchar_t* text) {
    const wchar_t* star = nullptr;
    const wchar_t* resume = nullptr;
    while (*text) {
        if (*pattern == L'*') {
            star = pattern++;
            resume = text;
        } else if (*pattern == L'?' || towlower(*pattern) == towlower(*text)) {
            pattern++;
            text++;
        } else if (star) {
            pattern = star + 1;
            text = ++resume;
        } else {
            return false;
        }
    }
    while (*pattern == L'*') {
        pattern++;
    }
    return !*pattern;
}

std::wstring ProcessPathOfWindow(HWND hwnd) {
    DWORD processId = 0;
    GetWindowThreadProcessId(hwnd, &processId);
    if (!processId) {
        return {};
    }
    HANDLE process =
        OpenProcess(PROCESS_QUERY_LIMITED_INFORMATION, FALSE, processId);
    if (!process) {
        return {};
    }
    WCHAR path[MAX_PATH * 2];
    DWORD size = ARRAYSIZE(path);
    std::wstring result;
    if (QueryFullProcessImageNameW(process, 0, path, &size)) {
        result.assign(path, size);
    }
    CloseHandle(process);
    return result;
}

bool IsAppExcluded(HWND hwnd) {
    if (!hwnd || g_settings.excludedApps.empty()) {
        return false;
    }
    hwnd = GetAncestor(hwnd, GA_ROOT);
    if (!hwnd) {
        return false;
    }
    const std::wstring path = ProcessPathOfWindow(hwnd);
    const size_t slash = path.find_last_of(L"\\/");
    const std::wstring name =
        slash == std::wstring::npos ? path : path.substr(slash + 1);
    WCHAR title[256] = L"";
    GetWindowTextW(hwnd, title, ARRAYSIZE(title));
    for (const std::wstring& pattern : g_settings.excludedApps) {
        if (pattern.find_first_of(L"\\/:") != std::wstring::npos) {
            if (!path.empty() && WildcardMatch(pattern.c_str(), path.c_str())) {
                return true;
            }
        } else if (!name.empty() &&
                   (WildcardMatch(pattern.c_str(), name.c_str()) ||
                    (pattern.find(L'.') == std::wstring::npos &&
                     WildcardMatch((pattern + L".exe").c_str(), name.c_str())))) {
            return true;
        }
        if (title[0] && WildcardMatch(pattern.c_str(), title)) {
            return true;
        }
    }
    return false;
}

bool IsWindowCloaked(HWND hwnd);

bool ForegroundIsFullscreen() {
    HWND hwnd = GetForegroundWindow();
    if (!hwnd || !IsWindowVisible(hwnd) || IsWindowCloaked(hwnd)) {
        return false;
    }
    WCHAR className[64] = L"";
    GetClassNameW(hwnd, className, ARRAYSIZE(className));
    for (PCWSTR shell : {L"Progman", L"WorkerW", L"Shell_TrayWnd",
                         L"Shell_SecondaryTrayWnd"}) {
        if (wcscmp(className, shell) == 0) {
            return false;
        }
    }
    const LONG style = GetWindowLongW(hwnd, GWL_STYLE);
    if ((style & WS_CAPTION) == WS_CAPTION) {
        return false;
    }
    RECT rect;
    MONITORINFO monitor{};
    monitor.cbSize = sizeof(monitor);
    if (!GetWindowRect(hwnd, &rect) ||
        !GetMonitorInfoW(MonitorFromWindow(hwnd, MONITOR_DEFAULTTONEAREST),
                         &monitor)) {
        return false;
    }
    return rect.left <= monitor.rcMonitor.left &&
           rect.top <= monitor.rcMonitor.top &&
           rect.right >= monitor.rcMonitor.right &&
           rect.bottom >= monitor.rcMonitor.bottom;
}

bool ShakeExcludedAt(POINT pt) {
    if (g_settings.excludedApps.empty()) {
        return false;
    }
    return IsAppExcluded(GetForegroundWindow()) || IsAppExcluded(WindowFromPoint(pt));
}

////////////////////////////////////////////////////////////////////////////////
// Keyboard shortcut parsing, for strings like "Win+Shift+G"

bool ParseHotkey(const std::wstring& text, UINT& modifiers, UINT& key) {
    modifiers = 0;
    key = 0;
    size_t start = 0;
    while (start <= text.size()) {
        size_t end = text.find(L'+', start);
        if (end == std::wstring::npos) {
            end = text.size();
        }
        std::wstring token = Trim(text.substr(start, end - start));
        start = end + 1;
        if (token.empty()) {
            if (end == text.size()) {
                break;
            }
            continue;
        }
        for (wchar_t& c : token) {
            c = towlower(c);
        }

        if (token == L"ctrl" || token == L"control") {
            modifiers |= MOD_CONTROL;
        } else if (token == L"alt") {
            modifiers |= MOD_ALT;
        } else if (token == L"shift") {
            modifiers |= MOD_SHIFT;
        } else if (token == L"win" || token == L"windows" ||
                   token == L"meta" || token == L"super") {
            modifiers |= MOD_WIN;
        } else if (token.size() == 1 &&
                   ((token[0] >= L'a' && token[0] <= L'z') ||
                    (token[0] >= L'0' && token[0] <= L'9'))) {
            key = towupper(token[0]);
        } else if (token.size() >= 2 && token.size() <= 3 && token[0] == L'f' &&
                   iswdigit(token[1])) {
            const int number = _wtoi(token.c_str() + 1);
            if (number >= 1 && number <= 24) {
                key = VK_F1 + number - 1;
            }
        } else {
            static const struct {
                PCWSTR name;
                UINT vk;
            } kKeys[] = {
                {L"space", VK_SPACE},     {L"enter", VK_RETURN},
                {L"return", VK_RETURN},   {L"tab", VK_TAB},
                {L"backspace", VK_BACK},  {L"insert", VK_INSERT},
                {L"ins", VK_INSERT},      {L"delete", VK_DELETE},
                {L"del", VK_DELETE},      {L"home", VK_HOME},
                {L"end", VK_END},         {L"pageup", VK_PRIOR},
                {L"pgup", VK_PRIOR},      {L"pagedown", VK_NEXT},
                {L"pgdn", VK_NEXT},       {L"up", VK_UP},
                {L"down", VK_DOWN},       {L"left", VK_LEFT},
                {L"right", VK_RIGHT},     {L"printscreen", VK_SNAPSHOT},
                {L"prtsc", VK_SNAPSHOT},  {L"pause", VK_PAUSE},
                {L"`", VK_OEM_3},         {L"-", VK_OEM_MINUS},
                {L"=", VK_OEM_PLUS},      {L"[", VK_OEM_4},
                {L"]", VK_OEM_6},         {L"\\", VK_OEM_5},
                {L";", VK_OEM_1},         {L"'", VK_OEM_7},
                {L",", VK_OEM_COMMA},     {L".", VK_OEM_PERIOD},
                {L"/", VK_OEM_2},
            };
            for (const auto& entry : kKeys) {
                if (token == entry.name) {
                    key = entry.vk;
                    break;
                }
            }
            if (!key) {
                return false;
            }
        }
    }
    return key != 0;
}

////////////////////////////////////////////////////////////////////////////////
// Finding what's under the pointer with UI Automation

struct PickResult {
    uint32_t id = 0;
    bool found = false;
    RECT rect{};
    std::wstring text;
};

bool IsWindowCloaked(HWND hwnd) {
    using DwmGetWindowAttribute_t = HRESULT(WINAPI*)(HWND, DWORD, PVOID, DWORD);
    static auto getAttribute = GetProc<DwmGetWindowAttribute_t>(
        L"dwmapi.dll", "DwmGetWindowAttribute");
    DWORD cloaked = 0;
    return getAttribute &&
           SUCCEEDED(getAttribute(hwnd, 14 /* DWMWA_CLOAKED */, &cloaked,
                                  sizeof(cloaked))) &&
           cloaked;
}

HWND TopLevelWindowAt(POINT pt) {
    const DWORD self = GetCurrentProcessId();
    for (HWND hwnd = GetTopWindow(nullptr); hwnd;
         hwnd = GetWindow(hwnd, GW_HWNDNEXT)) {
        if (!IsWindowVisible(hwnd) || IsIconic(hwnd)) {
            continue;
        }
        DWORD pid = 0;
        GetWindowThreadProcessId(hwnd, &pid);
        if (pid == self) {
            continue;
        }
        const LONG_PTR exStyle = GetWindowLongPtrW(hwnd, GWL_EXSTYLE);
        if (exStyle & WS_EX_TRANSPARENT) {
            continue;
        }
        RECT rc;
        if (!GetWindowRect(hwnd, &rc) || !PtInRect(&rc, pt)) {
            continue;
        }
        if (exStyle & WS_EX_LAYERED) {
            BYTE alpha = 255;
            DWORD flags = 0;
            COLORREF key;
            if (GetLayeredWindowAttributes(hwnd, &key, &alpha, &flags) &&
                (flags & LWA_ALPHA) && alpha == 0) {
                continue;
            }
        }
        if (IsWindowCloaked(hwnd)) {
            continue;
        }
        HRGN region = CreateRectRgn(0, 0, 0, 0);
        const int regionType = region ? GetWindowRgn(hwnd, region) : ERROR;
        const bool inRegion =
            regionType == ERROR ||
            (regionType != NULLREGION &&
             PtInRegion(region, pt.x - rc.left, pt.y - rc.top));
        if (region) {
            DeleteObject(region);
        }
        if (inRegion) {
            return hwnd;
        }
    }
    return nullptr;
}

HWND DeepestChildAt(HWND hwnd, POINT pt) {
    for (int depth = 0; depth < 32; depth++) {
        POINT client = pt;
        ScreenToClient(hwnd, &client);
        HWND child = ChildWindowFromPointEx(
            hwnd, client, CWP_SKIPINVISIBLE | CWP_SKIPTRANSPARENT);
        if (!child || child == hwnd) {
            break;
        }
        hwnd = child;
    }
    return hwnd;
}

class ElementPicker {
  public:
    bool Start(HWND notify) {
        if (thread_) {
            return true;
        }
        notify_ = notify;
        stop_ = false;
        event_ = CreateEventW(nullptr, FALSE, FALSE, nullptr);
        if (!event_) {
            return false;
        }
        thread_ = CreateThread(nullptr, 0, ThreadProc, this, 0, nullptr);
        if (!thread_) {
            CloseHandle(event_);
            event_ = nullptr;
            return false;
        }
        return true;
    }

    void Stop() {
        if (!thread_) {
            return;
        }
        stop_ = true;
        SetEvent(event_);
        if (WaitForSingleObject(thread_, 3000) == WAIT_OBJECT_0) {
            CloseHandle(thread_);
            CloseHandle(event_);
        }
        thread_ = nullptr;
        event_ = nullptr;
    }

    uint32_t Request(POINT pt) {
        if (!thread_) {
            return 0;
        }
        std::lock_guard<std::mutex> lock(mutex_);
        pendingPoint_ = pt;
        pendingId_ = ++lastId_;
        hasPending_ = true;
        SetEvent(event_);
        return pendingId_;
    }

    uint32_t LatestId() {
        std::lock_guard<std::mutex> lock(mutex_);
        return lastId_;
    }

  private:
    static DWORD WINAPI ThreadProc(LPVOID param) {
        static_cast<ElementPicker*>(param)->Run();
        return 0;
    }

    void Run() {
        const HRESULT coInit = CoInitializeEx(nullptr, COINIT_MULTITHREADED);

        ComPtr<IUIAutomation> automation;
        if (FAILED(CoCreateInstance(kClsidCUIAutomation8, nullptr,
                                    CLSCTX_INPROC_SERVER, kIidIUIAutomation,
                                    automation.PutVoid()))) {
            CoCreateInstance(kClsidCUIAutomation, nullptr, CLSCTX_INPROC_SERVER,
                             kIidIUIAutomation, automation.PutVoid());
        }

        ComPtr<IUIAutomationCacheRequest> cache;
        ComPtr<IUIAutomationCondition> condition;
        if (automation) {
            ComPtr<IUIAutomation2> automation2;
            if (SUCCEEDED(automation->QueryInterface(kIidIUIAutomation2,
                                                     automation2.PutVoid()))) {
                automation2->put_ConnectionTimeout(1500);
                automation2->put_TransactionTimeout(1500);
            }
            if (SUCCEEDED(automation->CreateCacheRequest(cache.Put()))) {
                cache->AddProperty(UIA_BoundingRectanglePropertyId);
                cache->AddProperty(UIA_ControlTypePropertyId);
                cache->AddProperty(UIA_IsOffscreenPropertyId);
                cache->AddProperty(UIA_NamePropertyId);
            }
            automation->get_ControlViewCondition(condition.Put());
        }
        if (!automation || !cache || !condition) {
            Wh_Log(L"UI Automation is unavailable, outlining windows only");
        }

        while (!stop_) {
            WaitForSingleObject(event_, INFINITE);
            if (stop_) {
                break;
            }
            POINT pt;
            uint32_t id;
            {
                std::lock_guard<std::mutex> lock(mutex_);
                if (!hasPending_) {
                    continue;
                }
                pt = pendingPoint_;
                id = pendingId_;
                hasPending_ = false;
            }

            auto result = std::make_unique<PickResult>();
            result->id = id;
            Pick(automation.Get(), cache.Get(), condition.Get(), pt, *result);
            if (stop_) {
                break;
            }
            PostOwned(notify_, WM_APP_PICK, std::move(result));
        }

        condition.Reset();
        cache.Reset();
        automation.Reset();
        if (SUCCEEDED(coInit)) {
            CoUninitialize();
        }
    }

    static bool IsMeaningfulType(CONTROLTYPEID type) {
        switch (type) {
            case UIA_ButtonControlTypeId:
            case UIA_CheckBoxControlTypeId:
            case UIA_ComboBoxControlTypeId:
            case UIA_EditControlTypeId:
            case UIA_HyperlinkControlTypeId:
            case UIA_ImageControlTypeId:
            case UIA_ListItemControlTypeId:
            case UIA_MenuItemControlTypeId:
            case UIA_RadioButtonControlTypeId:
            case UIA_SliderControlTypeId:
            case UIA_SplitButtonControlTypeId:
            case UIA_TabItemControlTypeId:
            case UIA_TreeItemControlTypeId:
            case UIA_DataItemControlTypeId:
            case UIA_HeaderItemControlTypeId:
                return true;
        }
        return false;
    }

    static bool IsLabelContainer(CONTROLTYPEID type) {
        return type == UIA_ButtonControlTypeId ||
               type == UIA_HyperlinkControlTypeId ||
               type == UIA_ListItemControlTypeId ||
               type == UIA_MenuItemControlTypeId ||
               type == UIA_TabItemControlTypeId ||
               type == UIA_TreeItemControlTypeId ||
               type == UIA_DataItemControlTypeId ||
               type == UIA_HeaderItemControlTypeId ||
               type == UIA_SplitButtonControlTypeId;
    }

    void Pick(IUIAutomation* automation,
              IUIAutomationCacheRequest* cache,
              IUIAutomationCondition* condition,
              POINT pt,
              PickResult& out) {
        HWND top = TopLevelWindowAt(pt);
        if (!top) {
            return;
        }
        HWND target = DeepestChildAt(top, pt);

        const RECT monitor = MonitorRectAt(pt, false);
        const double monitorArea =
            double(monitor.right - monitor.left) * (monitor.bottom - monitor.top);
        auto area = [](const RECT& rc) {
            return double(rc.right - rc.left) * (rc.bottom - rc.top);
        };
        auto reasonable = [&](const RECT& rc, double maxShare) {
            const LONG w = rc.right - rc.left;
            const LONG h = rc.bottom - rc.top;
            return w >= 6 && h >= 6 && area(rc) <= monitorArea * maxShare;
        };

        auto fallbackToWindow = [&] {
            RECT rc;
            if (target != top && GetWindowRect(target, &rc) &&
                reasonable(rc, 0.6) && PtInRect(&rc, pt)) {
                out.found = true;
                out.rect = rc;
            }
        };

        if (!automation || !cache || !condition) {
            fallbackToWindow();
            return;
        }

        struct Node {
            IUIAutomationElement* element;
            RECT rect;
            CONTROLTYPEID type;
        };
        std::vector<Node> path;
        auto release = [&] {
            for (Node& node : path) {
                node.element->Release();
            }
            path.clear();
        };

        IUIAutomationElement* element = nullptr;
        if (FAILED(automation->ElementFromHandleBuildCache(target, cache,
                                                           &element)) ||
            !element) {
            fallbackToWindow();
            return;
        }
        Node root{element, {}, 0};
        element->get_CachedBoundingRectangle(&root.rect);
        element->get_CachedControlType(&root.type);
        path.push_back(root);

        for (int depth = 0; depth < 40 && !stop_; depth++) {
            IUIAutomationElementArray* children = nullptr;
            if (FAILED(path.back().element->FindAllBuildCache(
                    TreeScope_Children, condition, cache, &children)) ||
                !children) {
                break;
            }
            int length = 0;
            children->get_Length(&length);
            Node best{nullptr, {}, 0};
            double bestArea = 0;
            for (int i = 0; i < length && i < 2000; i++) {
                IUIAutomationElement* child = nullptr;
                if (FAILED(children->GetElement(i, &child)) || !child) {
                    continue;
                }
                RECT rc{};
                BOOL offscreen = FALSE;
                CONTROLTYPEID type = 0;
                child->get_CachedBoundingRectangle(&rc);
                child->get_CachedIsOffscreen(&offscreen);
                child->get_CachedControlType(&type);
                const double childArea = area(rc);
                if (!offscreen && childArea > 0 && PtInRect(&rc, pt) &&
                    (!best.element || childArea <= bestArea)) {
                    if (best.element) {
                        best.element->Release();
                    }
                    best = {child, rc, type};
                    bestArea = childArea;
                } else {
                    child->Release();
                }
            }
            children->Release();
            if (!best.element) {
                break;
            }
            path.push_back(best);
        }

        int chosen = -1;
        int fallback = -1;
        for (int i = static_cast<int>(path.size()) - 1; i >= 0; i--) {
            const Node& node = path[i];
            if (!reasonable(node.rect, 0.85)) {
                if (area(node.rect) > monitorArea * 0.85) {
                    break;
                }
                continue;
            }
            if (node.type == UIA_TextControlTypeId) {
                if (i > 0 && IsLabelContainer(path[i - 1].type) &&
                    reasonable(path[i - 1].rect, 0.85)) {
                    continue;
                }
                chosen = i;
                break;
            }
            if (IsMeaningfulType(node.type)) {
                chosen = i;
                break;
            }
            if (fallback < 0 && i > 0 && reasonable(node.rect, 0.6) &&
                node.rect.right - node.rect.left >= 24 &&
                node.rect.bottom - node.rect.top >= 16) {
                fallback = i;
            }
        }
        if (chosen < 0) {
            chosen = fallback;
        }

        if (chosen >= 0) {
            out.found = true;
            out.rect = path[chosen].rect;
            BSTR name = nullptr;
            if (SUCCEEDED(path[chosen].element->get_CachedName(&name)) && name) {
                out.text = Trim(std::wstring(name, SysStringLen(name)));
                SysFreeString(name);
            }
            if (out.text.size() > 4000) {
                out.text.resize(4000);
            }
        } else {
            fallbackToWindow();
        }
        release();
    }

    HANDLE thread_ = nullptr;
    HANDLE event_ = nullptr;
    HWND notify_ = nullptr;
    std::atomic<bool> stop_{false};
    std::mutex mutex_;
    POINT pendingPoint_{};
    uint32_t pendingId_ = 0;
    uint32_t lastId_ = 0;
    bool hasPending_ = false;
};

////////////////////////////////////////////////////////////////////////////////
// Screen capture, PNG and the clipboard

bool CaptureScreen(const RECT& rect, Image& out) {
    const int width = rect.right - rect.left;
    const int height = rect.bottom - rect.top;
    if (width <= 0 || height <= 0) {
        return false;
    }
    HDC screen = GetDC(nullptr);
    if (!screen) {
        return false;
    }
    HDC memory = CreateCompatibleDC(screen);
    BITMAPINFO info{};
    info.bmiHeader.biSize = sizeof(info.bmiHeader);
    info.bmiHeader.biWidth = width;
    info.bmiHeader.biHeight = -height;
    info.bmiHeader.biPlanes = 1;
    info.bmiHeader.biBitCount = 32;
    info.bmiHeader.biCompression = BI_RGB;
    void* bits = nullptr;
    HBITMAP bitmap =
        CreateDIBSection(screen, &info, DIB_RGB_COLORS, &bits, nullptr, 0);
    bool ok = false;
    if (memory && bitmap && bits) {
        HGDIOBJ old = SelectObject(memory, bitmap);
        ok = BitBlt(memory, 0, 0, width, height, screen, rect.left, rect.top,
                    SRCCOPY | CAPTUREBLT);
        GdiFlush();
        SelectObject(memory, old);
        if (ok) {
            const uint32_t* pixels = static_cast<const uint32_t*>(bits);
            out.width = width;
            out.height = height;
            out.pixels.assign(pixels, pixels + static_cast<size_t>(width) * height);
            for (uint32_t& pixel : out.pixels) {
                pixel |= 0xFF000000;
            }
        }
    }
    if (bitmap) {
        DeleteObject(bitmap);
    }
    if (memory) {
        DeleteDC(memory);
    }
    ReleaseDC(nullptr, screen);
    return ok;
}

bool EncodeImage(const Image& image,
                 std::vector<uint8_t>& out,
                 bool jpeg,
                 float quality = 0.9f) {
    if (image.Empty()) {
        return false;
    }
    ComPtr<IWICImagingFactory> factory;
    ComPtr<IStream> stream;
    ComPtr<IWICBitmapEncoder> encoder;
    ComPtr<IWICBitmapFrameEncode> frame;
    ComPtr<IPropertyBag2> properties;
    if (FAILED(CoCreateInstance(kClsidWICImagingFactory1, nullptr,
                                CLSCTX_INPROC_SERVER, kIidIWICImagingFactory,
                                factory.PutVoid())) ||
        FAILED(CreateStreamOnHGlobal(nullptr, TRUE, stream.Put())) ||
        FAILED(factory->CreateEncoder(
            jpeg ? kGuidContainerFormatJpeg : kGuidContainerFormatPng, nullptr,
            encoder.Put())) ||
        FAILED(encoder->Initialize(stream.Get(), WICBitmapEncoderNoCache)) ||
        FAILED(encoder->CreateNewFrame(frame.Put(), properties.Put()))) {
        return false;
    }
    if (jpeg && properties) {
        PROPBAG2 option{};
        option.pstrName = const_cast<LPOLESTR>(L"ImageQuality");
        VARIANT value;
        VariantInit(&value);
        value.vt = VT_R4;
        value.fltVal = quality;
        properties->Write(1, &option, &value);
    }
    if (FAILED(frame->Initialize(properties.Get())) ||
        FAILED(frame->SetSize(image.width, image.height))) {
        return false;
    }
    WICPixelFormatGUID format = kGuidWICPixelFormat24bppBGR;
    if (FAILED(frame->SetPixelFormat(&format)) ||
        !IsEqualGUID(format, kGuidWICPixelFormat24bppBGR)) {
        return false;
    }
    const UINT stride = (static_cast<UINT>(image.width) * 3 + 3) & ~3u;
    std::vector<BYTE> rows(static_cast<size_t>(stride) * image.height);
    for (int y = 0; y < image.height; y++) {
        BYTE* dst = &rows[static_cast<size_t>(y) * stride];
        const uint32_t* src = &image.pixels[static_cast<size_t>(y) * image.width];
        for (int x = 0; x < image.width; x++) {
            dst[x * 3] = src[x] & 0xFF;
            dst[x * 3 + 1] = (src[x] >> 8) & 0xFF;
            dst[x * 3 + 2] = (src[x] >> 16) & 0xFF;
        }
    }
    if (FAILED(frame->WritePixels(image.height, stride,
                                  static_cast<UINT>(rows.size()), rows.data())) ||
        FAILED(frame->Commit()) || FAILED(encoder->Commit())) {
        return false;
    }

    HGLOBAL global = nullptr;
    STATSTG stat{};
    if (FAILED(GetHGlobalFromStream(stream.Get(), &global)) ||
        FAILED(stream->Stat(&stat, STATFLAG_NONAME))) {
        return false;
    }
    const size_t size = static_cast<size_t>(stat.cbSize.QuadPart);
    const void* data = GlobalLock(global);
    if (!data) {
        return false;
    }
    out.assign(static_cast<const uint8_t*>(data),
               static_cast<const uint8_t*>(data) + size);
    GlobalUnlock(global);
    return !out.empty();
}

bool EncodePng(const Image& image, std::vector<uint8_t>& out) {
    return EncodeImage(image, out, false);
}

bool OpenClipboardWithRetry(HWND owner) {
    for (int attempt = 0; attempt < 10; attempt++) {
        if (OpenClipboard(owner)) {
            return true;
        }
        Sleep(15);
    }
    return false;
}

HGLOBAL GlobalFromBytes(const void* data, size_t size) {
    HGLOBAL global = GlobalAlloc(GMEM_MOVEABLE, size);
    if (global) {
        void* dst = GlobalLock(global);
        if (dst) {
            memcpy(dst, data, size);
            GlobalUnlock(global);
        } else {
            GlobalFree(global);
            global = nullptr;
        }
    }
    return global;
}

struct ClipboardImageData {
    std::vector<BYTE> dib, dibV5;
    std::vector<uint8_t> png;
};

bool BuildClipboardImageData(const Image& image, ClipboardImageData& data) {
    data = {};
    if (image.width <= 0 || image.height <= 0 ||
        static_cast<uint64_t>(image.width) * image.height > UINT_MAX / 4 ||
        image.pixels.size() < static_cast<uint64_t>(image.width) * image.height) return false;
    const UINT stride = (static_cast<UINT>(image.width) * 3 + 3) & ~3u;
    data.dib.resize(sizeof(BITMAPINFOHEADER) + static_cast<size_t>(stride) * image.height);
    BITMAPINFOHEADER* header = reinterpret_cast<BITMAPINFOHEADER*>(data.dib.data());
    header->biSize = sizeof(BITMAPINFOHEADER);
    header->biWidth = image.width;
    header->biHeight = image.height;
    header->biPlanes = 1;
    header->biBitCount = 24;
    header->biCompression = BI_RGB;
    header->biSizeImage = stride * image.height;
    BYTE* pixels = data.dib.data() + sizeof(BITMAPINFOHEADER);
    for (int y = 0; y < image.height; y++) {
        BYTE* dst = pixels + static_cast<size_t>(image.height - 1 - y) * stride;
        const uint32_t* src = &image.pixels[static_cast<size_t>(y) * image.width];
        for (int x = 0; x < image.width; x++) {
            dst[x * 3] = src[x] & 0xFF;
            dst[x * 3 + 1] = (src[x] >> 8) & 0xFF;
            dst[x * 3 + 2] = (src[x] >> 16) & 0xFF;
        }
    }

    const size_t pixelBytes = static_cast<size_t>(image.width) * image.height * 4;
    data.dibV5.resize(sizeof(BITMAPV5HEADER) + pixelBytes);
    auto* v5 = reinterpret_cast<BITMAPV5HEADER*>(data.dibV5.data());
    v5->bV5Size = sizeof(BITMAPV5HEADER);
    v5->bV5Width = image.width;
    v5->bV5Height = -image.height;
    v5->bV5Planes = 1;
    v5->bV5BitCount = 32;
    v5->bV5Compression = BI_BITFIELDS;
    v5->bV5SizeImage = static_cast<DWORD>(pixelBytes);
    v5->bV5RedMask = 0x00FF0000;
    v5->bV5GreenMask = 0x0000FF00;
    v5->bV5BlueMask = 0x000000FF;
    v5->bV5AlphaMask = 0xFF000000;
    v5->bV5CSType = LCS_sRGB;
    v5->bV5Intent = LCS_GM_IMAGES;
    auto* opaquePixels = reinterpret_cast<uint32_t*>(data.dibV5.data() + sizeof(BITMAPV5HEADER));
    for (size_t i = 0; i < pixelBytes / 4; i++) opaquePixels[i] = image.pixels[i] | 0xFF000000u;
    EncodePng(image, data.png);
    return true;
}

bool CopyImageToClipboard(HWND owner, const Image& image) {
    ClipboardImageData data;
    if (!BuildClipboardImageData(image, data)) return false;
    struct Format {
        UINT type;
        HGLOBAL memory;
    } formats[]{
        {RegisterClipboardFormatW(L"PNG"), data.png.empty() ? nullptr : GlobalFromBytes(data.png.data(), data.png.size())},
        {CF_DIBV5, GlobalFromBytes(data.dibV5.data(), data.dibV5.size())},
        {CF_DIB, GlobalFromBytes(data.dib.data(), data.dib.size())},
    };
    bool ok = false;
    if (OpenClipboardWithRetry(owner)) {
        if (EmptyClipboard()) {
            for (Format& format : formats) {
                if (format.type && format.memory && SetClipboardData(format.type, format.memory)) {
                    format.memory = nullptr;  // Ownership passed to Windows.
                    ok = true;
                }
            }
        }
        CloseClipboard();
    }
    for (Format& format : formats) if (format.memory) GlobalFree(format.memory);
    return ok;
}

std::vector<BYTE> BuildClipboardFileDrop(const std::vector<std::wstring>& paths) {
    size_t characters = 1;  // The list ends with one more terminator.
    for (const std::wstring& path : paths) {
        if (path.empty() || path.find(L'\0') != std::wstring::npos) return {};
        characters += path.size() + 1;
    }
    if (paths.empty()) return {};
    std::vector<BYTE> bytes(sizeof(DROPFILES) + characters * sizeof(wchar_t), 0);
    auto* drop = reinterpret_cast<DROPFILES*>(bytes.data());
    drop->pFiles = sizeof(DROPFILES);
    drop->fWide = TRUE;
    auto* names = reinterpret_cast<wchar_t*>(bytes.data() + sizeof(DROPFILES));
    for (const std::wstring& path : paths) {
        memcpy(names, path.data(), path.size() * sizeof(wchar_t));
        names += path.size() + 1;  // Its terminator is already zero.
    }
    return bytes;
}

bool CopyImageFileToClipboard(HWND owner, const std::vector<std::wstring>& paths,
                              DWORD expectedSequence = 0) {
    for (const std::wstring& path : paths) {
        const DWORD attributes = GetFileAttributesW(path.c_str());
        if (attributes == INVALID_FILE_ATTRIBUTES || (attributes & FILE_ATTRIBUTE_DIRECTORY)) return false;
    }
    const auto bytes = BuildClipboardFileDrop(paths);
    HGLOBAL drop = bytes.empty() ? nullptr : GlobalFromBytes(bytes.data(), bytes.size());
    const DWORD effect = DROPEFFECT_COPY;
    HGLOBAL copyEffect = GlobalFromBytes(&effect, sizeof(effect));
    const UINT effectFormat = RegisterClipboardFormatW(L"Preferred DropEffect");
    bool ok = false;
    if (drop && OpenClipboardWithRetry(owner)) {
        if ((!expectedSequence || GetClipboardSequenceNumber() == expectedSequence) &&
            EmptyClipboard() && SetClipboardData(CF_HDROP, drop)) {
            drop = nullptr;
            ok = true;
            if (effectFormat && copyEffect && SetClipboardData(effectFormat, copyEffect)) copyEffect = nullptr;
        }
        CloseClipboard();
    }
    if (drop) GlobalFree(drop);
    if (copyEffect) GlobalFree(copyEffect);
    return ok;
}

std::wstring g_storageDir;

// Screen captures must not sit in Windhawk's mod storage: under ProgramData it
// grants Everyone and app containers full control. Use a per-user folder whose
// DACL is protected and lists only this account and SYSTEM, and refuse a
// folder that is a junction or link.
bool IsPlainDirectory(const std::wstring& path) {
    const DWORD attributes = GetFileAttributesW(path.c_str());
    return attributes != INVALID_FILE_ATTRIBUTES && (attributes & FILE_ATTRIBUTE_DIRECTORY) &&
           !(attributes & FILE_ATTRIBUTE_REPARSE_POINT);
}

bool ProtectDirectoryForCurrentUser(const std::wstring& path) {
    HANDLE token = nullptr;
    if (!OpenProcessToken(GetCurrentProcess(), TOKEN_QUERY, &token)) return false;
    DWORD size = 0;
    GetTokenInformation(token, TokenUser, nullptr, 0, &size);
    std::vector<BYTE> buffer(size ? size : 1);
    const bool gotUser = size && GetTokenInformation(token, TokenUser, buffer.data(), size, &size);
    CloseHandle(token);
    if (!gotUser) return false;
    LPWSTR sid = nullptr;
    if (!ConvertSidToStringSidW(reinterpret_cast<TOKEN_USER*>(buffer.data())->User.Sid, &sid)) return false;
    const std::wstring sddl = std::wstring(L"D:P(A;OICI;FA;;;SY)(A;OICI;FA;;;") + sid + L")";
    LocalFree(sid);
    PSECURITY_DESCRIPTOR descriptor = nullptr;
    if (!ConvertStringSecurityDescriptorToSecurityDescriptorW(sddl.c_str(), SDDL_REVISION_1, &descriptor, nullptr)) {
        return false;
    }
    bool ok = false;
    BOOL present = FALSE, defaulted = FALSE;
    PACL dacl = nullptr;
    if (GetSecurityDescriptorDacl(descriptor, &present, &dacl, &defaulted) && present) {
        SECURITY_ATTRIBUTES attributes{sizeof(attributes), descriptor, FALSE};
        if (CreateDirectoryW(path.c_str(), &attributes) || GetLastError() == ERROR_ALREADY_EXISTS) {
            ok = IsPlainDirectory(path) &&
                 SetNamedSecurityInfoW(const_cast<LPWSTR>(path.c_str()), SE_FILE_OBJECT,
                                       DACL_SECURITY_INFORMATION | PROTECTED_DACL_SECURITY_INFORMATION,
                                       nullptr, nullptr, dacl, nullptr) == ERROR_SUCCESS;
        }
    }
    LocalFree(descriptor);
    return ok;
}

std::wstring PrivateCaptureDirectory() {
    WCHAR local[MAX_PATH]{};
    if (FAILED(SHGetFolderPathW(nullptr, CSIDL_LOCAL_APPDATA | CSIDL_FLAG_DONT_VERIFY, nullptr,
                                SHGFP_TYPE_CURRENT, local)) || !local[0]) {
        return {};
    }
    const std::wstring base = std::wstring(local) + L"\\MagicPointerPlus";
    const std::wstring temp = base + L"\\Temp";
    if (!ProtectDirectoryForCurrentUser(base) || !ProtectDirectoryForCurrentUser(temp)) return {};
    return temp;
}
extern std::atomic<bool> g_stopping;
constexpr double kGeminiFileLifetimeMs = 30.0 * 60 * 1000;
struct TemporaryGeminiFile { std::wstring path; double expires; };
std::mutex g_geminiFilesMutex;
std::vector<TemporaryGeminiFile> g_geminiFiles;

double CleanupGeminiFiles(double now) {
    double next = 1e9;
    std::lock_guard<std::mutex> lock(g_geminiFilesMutex);
    for (auto it = g_geminiFiles.begin(); it != g_geminiFiles.end();) {
        if (now >= it->expires) {
            if (DeleteFileW(it->path.c_str()) || GetLastError() == ERROR_FILE_NOT_FOUND) {
                it = g_geminiFiles.erase(it);
                continue;
            }
            it->expires = now + 60000;  // An upload may still have the file open.
        }
        next = std::min(next, it->expires - now);
        ++it;
    }
    return next;
}

void DeleteExpiredGeminiFiles(bool all = false) {
    std::lock_guard<std::mutex> lock(g_geminiFilesMutex);
    if (g_storageDir.empty()) return;
    WIN32_FIND_DATAW data{};
    HANDLE find = FindFirstFileW((g_storageDir + L"\\gemini-selection-*.png").c_str(), &data);
    if (find == INVALID_HANDLE_VALUE) return;
    FILETIME current{};
    GetSystemTimeAsFileTime(&current);
    auto ticks = [](FILETIME time) { return (static_cast<uint64_t>(time.dwHighDateTime) << 32) | time.dwLowDateTime; };
    do {
        if (!(data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) &&
            (all || (ticks(current) >= ticks(data.ftLastWriteTime) &&
             ticks(current) - ticks(data.ftLastWriteTime) >= static_cast<uint64_t>(kGeminiFileLifetimeMs * 10000)))) {
            DeleteFileW((g_storageDir + L"\\" + data.cFileName).c_str());
        }
    } while (FindNextFileW(find, &data));
    FindClose(find);
}

std::wstring WriteGeminiImageFile(const Image& image, HWND notify) {
    if (g_storageDir.empty() || image.width <= 0 || image.height <= 0 ||
        image.pixels.size() != static_cast<size_t>(image.width) * image.height) return {};
    std::vector<uint8_t> png;
    if (!EncodePng(image, png) || png.size() > MAXDWORD) return {};
    // Serialize file creation with shutdown cleanup so an in-flight handoff
    // cannot leave a new screenshot behind after the mod is disabled.
    std::lock_guard<std::mutex> lock(g_geminiFilesMutex);
    if (g_stopping) return {};
    static std::atomic<unsigned> sequence{0};
    const std::wstring path = g_storageDir + L"\\gemini-selection-" +
        std::to_wstring(GetCurrentProcessId()) + L"-" + std::to_wstring(GetTickCount64()) +
        L"-" + std::to_wstring(++sequence) + L".png";
    HANDLE file = CreateFileW(path.c_str(), GENERIC_WRITE, FILE_SHARE_READ, nullptr,
                              CREATE_NEW, FILE_ATTRIBUTE_TEMPORARY, nullptr);
    if (file == INVALID_HANDLE_VALUE) return {};
    DWORD written = 0;
    const bool ok = WriteFile(file, png.data(), static_cast<DWORD>(png.size()), &written, nullptr) && written == png.size();
    CloseHandle(file);  // Close before Chrome opens the file.
    if (!ok) { DeleteFileW(path.c_str()); return {}; }
    g_geminiFiles.push_back({path, NowMs() + kGeminiFileLifetimeMs});
    if (notify) PostMessageW(notify, WM_APP_TEMP_FILE, 0, 0);
    return path;
}

bool CopyTextToClipboard(HWND owner, const std::wstring& text) {
    HGLOBAL global =
        GlobalFromBytes(text.c_str(), (text.size() + 1) * sizeof(wchar_t));
    if (!global) {
        return false;
    }
    if (!OpenClipboardWithRetry(owner)) {
        GlobalFree(global);
        return false;
    }
    EmptyClipboard();
    const bool ok = SetClipboardData(CF_UNICODETEXT, global) != nullptr;
    if (!ok) {
        GlobalFree(global);
    }
    CloseClipboard();
    return ok;
}

std::wstring ReadClipboardText(HWND owner) {
    std::wstring text;
    if (!IsClipboardFormatAvailable(CF_UNICODETEXT) ||
        !OpenClipboardWithRetry(owner)) {
        return text;
    }
    if (HANDLE data = GetClipboardData(CF_UNICODETEXT)) {
        if (const wchar_t* chars = static_cast<const wchar_t*>(GlobalLock(data))) {
            text = chars;
            GlobalUnlock(data);
        }
    }
    CloseClipboard();
    return text;
}

////////////////////////////////////////////////////////////////////////////////
// Opening the browser

std::atomic<int> g_helperThreads{0};

std::wstring Lowercase(std::wstring text) {
    for (wchar_t& c : text) c = towlower(c);
    return text;
}

std::wstring FileNameOf(const std::wstring& path) {
    const size_t slash = path.find_last_of(L"\\/");
    return Lowercase(slash == std::wstring::npos ? path : path.substr(slash + 1));
}

bool IsProcessElevated() {
    static const bool elevated = [] {
        HANDLE token;
        if (!OpenProcessToken(GetCurrentProcess(), TOKEN_QUERY, &token)) {
            return false;
        }
        TOKEN_ELEVATION elevation{};
        DWORD size = sizeof(elevation);
        const bool result = GetTokenInformation(token, TokenElevation,
                                                &elevation, sizeof(elevation),
                                                &size) &&
                            elevation.TokenIsElevated;
        CloseHandle(token);
        return result;
    }();
    return elevated;
}

bool ShellExecuteThroughExplorer(const std::wstring& target,
                                 const std::wstring& parameters = {}) {
    ComPtr<IShellWindows> shellWindows;
    if (FAILED(CoCreateInstance(kClsidShellWindows, nullptr,
                                CLSCTX_LOCAL_SERVER, kIidIShellWindows,
                                shellWindows.PutVoid()))) {
        return false;
    }
    VARIANT empty;
    VariantInit(&empty);
    long hwnd = 0;
    ComPtr<IDispatch> dispatch;
    if (shellWindows->FindWindowSW(&empty, &empty, SWC_DESKTOP, &hwnd,
                                   SWFO_NEEDDISPATCH, dispatch.Put()) != S_OK ||
        !dispatch) {
        return false;
    }
    ComPtr<IServiceProvider> provider;
    ComPtr<IShellBrowser> browser;
    ComPtr<IShellView> view;
    ComPtr<IDispatch> background;
    ComPtr<IShellFolderViewDual> folderView;
    ComPtr<IDispatch> application;
    ComPtr<IShellDispatch2> shell;
    if (FAILED(dispatch->QueryInterface(kIidIServiceProvider,
                                        provider.PutVoid())) ||
        FAILED(provider->QueryService(kSidSTopLevelBrowser, kIidIShellBrowser,
                                      browser.PutVoid())) ||
        FAILED(browser->QueryActiveShellView(view.Put())) ||
        FAILED(view->GetItemObject(SVGIO_BACKGROUND, kIidIDispatch,
                                   background.PutVoid())) ||
        FAILED(background->QueryInterface(kIidIShellFolderViewDual,
                                          folderView.PutVoid())) ||
        FAILED(folderView->get_Application(application.Put())) ||
        FAILED(application->QueryInterface(kIidIShellDispatch2,
                                           shell.PutVoid()))) {
        return false;
    }
    BSTR file = SysAllocString(target.c_str());
    VARIANT none;
    VariantInit(&none);
    VARIANT arguments;
    VariantInit(&arguments);
    if (!parameters.empty()) {
        arguments.vt = VT_BSTR;
        arguments.bstrVal = SysAllocString(parameters.c_str());
    }
    VARIANT show;
    VariantInit(&show);
    show.vt = VT_I4;
    show.lVal = SW_SHOWNORMAL;
    const HRESULT hr = shell->ShellExecute(file, arguments, none, none, show);
    SysFreeString(file);
    VariantClear(&arguments);
    return SUCCEEDED(hr);
}

////////////////////////////////////////////////////////////////////////////////
// Choosing the browser

struct KnownBrowser {
    PCWSTR id;         // The value of the Browser setting.
    PCWSTR process;    // The program whose windows are the browser's.
    PCWSTR program;    // What gets started; differs when a launcher starts it.
    PCWSTR places[4];  // Where it installs when Windows has no record of it.
};

constexpr KnownBrowser kBrowsers[] = {
    {L"chrome", L"chrome.exe", L"chrome.exe",
     {L"%ProgramFiles%\\Google\\Chrome\\Application",
      L"%ProgramFiles(x86)%\\Google\\Chrome\\Application",
      L"%LOCALAPPDATA%\\Google\\Chrome\\Application",
      L"%ProgramW6432%\\Google\\Chrome\\Application"}},
    {L"edge", L"msedge.exe", L"msedge.exe",
     {L"%ProgramFiles(x86)%\\Microsoft\\Edge\\Application",
      L"%ProgramFiles%\\Microsoft\\Edge\\Application",
      L"%ProgramW6432%\\Microsoft\\Edge\\Application", nullptr}},
    {L"firefox", L"firefox.exe", L"firefox.exe",
     {L"%ProgramFiles%\\Mozilla Firefox", L"%ProgramFiles(x86)%\\Mozilla Firefox",
      L"%ProgramW6432%\\Mozilla Firefox", nullptr}},
    {L"brave", L"brave.exe", L"brave.exe",
     {L"%ProgramFiles%\\BraveSoftware\\Brave-Browser\\Application",
      L"%LOCALAPPDATA%\\BraveSoftware\\Brave-Browser\\Application",
      L"%ProgramFiles(x86)%\\BraveSoftware\\Brave-Browser\\Application",
      L"%ProgramW6432%\\BraveSoftware\\Brave-Browser\\Application"}},
    {L"zen", L"zen.exe", L"zen.exe",
     {L"%ProgramFiles%\\Zen Browser", L"%LOCALAPPDATA%\\Zen Browser",
      L"%LOCALAPPDATA%\\Programs\\Zen Browser", L"%ProgramW6432%\\Zen Browser"}},
    {L"opera", L"opera.exe", L"launcher.exe",
     {L"%LOCALAPPDATA%\\Programs\\Opera", L"%ProgramFiles%\\Opera",
      L"%ProgramW6432%\\Opera", nullptr}},
    {L"vivaldi", L"vivaldi.exe", L"vivaldi.exe",
     {L"%LOCALAPPDATA%\\Vivaldi\\Application", L"%ProgramFiles%\\Vivaldi\\Application",
      L"%ProgramW6432%\\Vivaldi\\Application", nullptr}},
    {L"librewolf", L"librewolf.exe", L"librewolf.exe",
     {L"%ProgramFiles%\\LibreWolf", L"%LOCALAPPDATA%\\LibreWolf",
      L"%ProgramW6432%\\LibreWolf", nullptr}},
    {L"waterfox", L"waterfox.exe", L"waterfox.exe",
     {L"%ProgramFiles%\\Waterfox", L"%LOCALAPPDATA%\\Waterfox",
      L"%ProgramW6432%\\Waterfox", nullptr}},
    {L"floorp", L"floorp.exe", L"floorp.exe",
     {L"%ProgramFiles%\\Ablaze Floorp", L"%LOCALAPPDATA%\\Ablaze Floorp",
      L"%ProgramW6432%\\Ablaze Floorp", nullptr}},
};

bool IsKnownBrowserName(const std::wstring& name) {
    for (const KnownBrowser& browser : kBrowsers) {
        if (name == browser.process) return true;
    }
    for (PCWSTR other : {L"browser.exe", L"chromium.exe", L"thorium.exe"}) {
        if (name == other) return true;
    }
    return false;
}

struct BrowserTarget {
    std::wstring file;       // What to start. Empty: the Windows default browser.
    std::wstring process;    // Name of the program whose windows are the browser's.
    bool anyKnown = false;   // Windows of well-known browsers count as well.
};

bool BrowserOwnsProcess(const std::wstring& name, const BrowserTarget& browser) {
    if (!browser.process.empty() && name == browser.process) return true;
    return (browser.process.empty() || browser.anyKnown) && IsKnownBrowserName(name);
}

std::wstring ProgramOfCommand(const std::wstring& line) {
    const std::wstring command = Trim(line);
    if (command.empty()) return {};
    if (command[0] == L'"') {
        const size_t close = command.find(L'"', 1);
        return close == std::wstring::npos ? command.substr(1) : command.substr(1, close - 1);
    }
    const size_t exe = Lowercase(command).find(L".exe");
    return exe != std::wstring::npos ? command.substr(0, exe + 4)
                                     : command.substr(0, command.find(L' '));
}

bool IsFile(const std::wstring& path) {
    const DWORD attributes = GetFileAttributesW(path.c_str());
    return attributes != INVALID_FILE_ATTRIBUTES && !(attributes & FILE_ATTRIBUTE_DIRECTORY);
}

std::wstring ExpandVariables(const std::wstring& text) {
    WCHAR expanded[MAX_PATH * 2];
    const DWORD size = ExpandEnvironmentStringsW(text.c_str(), expanded, ARRAYSIZE(expanded));
    return size > 0 && size <= ARRAYSIZE(expanded) ? std::wstring(expanded) : text;
}

bool ReadRegistryString(HKEY root, const std::wstring& subkey, PCWSTR name, REGSAM view,
                        std::wstring& value) {
    HKEY key = nullptr;
    if (RegOpenKeyExW(root, subkey.c_str(), 0, KEY_READ | view, &key) != ERROR_SUCCESS) {
        return false;
    }
    WCHAR buffer[1024];
    DWORD size = sizeof(buffer);
    const LSTATUS status = RegGetValueW(key, nullptr, name, RRF_RT_REG_SZ | RRF_RT_REG_EXPAND_SZ,
                                        nullptr, buffer, &size);
    RegCloseKey(key);
    value = status == ERROR_SUCCESS ? buffer : L"";
    return !value.empty();
}

std::wstring FindBrowserProgram(const KnownBrowser& browser) {
    struct Hive {
        HKEY root;
        REGSAM view;
    };
    const Hive hives[] = {{HKEY_CURRENT_USER, 0},
                          {HKEY_LOCAL_MACHINE, KEY_WOW64_64KEY},
                          {HKEY_LOCAL_MACHINE, KEY_WOW64_32KEY}};
    for (PCWSTR exe : {browser.process, browser.program}) {
        for (const Hive& hive : hives) {
            std::wstring path;
            if (ReadRegistryString(
                    hive.root,
                    std::wstring(L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\App Paths\\") + exe,
                    nullptr, hive.view, path)) {
                path = ProgramOfCommand(path);
                if (IsFile(path)) return path;
            }
        }
    }
    for (const Hive& hive : hives) {
        HKEY clients = nullptr;
        if (RegOpenKeyExW(hive.root, L"SOFTWARE\\Clients\\StartMenuInternet", 0,
                          KEY_READ | hive.view, &clients) != ERROR_SUCCESS) {
            continue;
        }
        WCHAR name[256];
        for (DWORD i = 0;; i++) {
            DWORD length = ARRAYSIZE(name);
            if (RegEnumKeyExW(clients, i, name, &length, nullptr, nullptr, nullptr, nullptr) !=
                ERROR_SUCCESS) {
                break;
            }
            std::wstring command;
            if (!ReadRegistryString(
                    hive.root,
                    std::wstring(L"SOFTWARE\\Clients\\StartMenuInternet\\") + name +
                        L"\\shell\\open\\command",
                    nullptr, hive.view, command)) {
                continue;
            }
            const std::wstring path = ProgramOfCommand(command);
            const std::wstring file = FileNameOf(path);
            if ((file == browser.process || file == browser.program) && IsFile(path)) {
                RegCloseKey(clients);
                return path;
            }
        }
        RegCloseKey(clients);
    }
    for (PCWSTR place : browser.places) {
        if (!place) continue;
        for (PCWSTR exe : {browser.program, browser.process}) {
            const std::wstring path = ExpandVariables(place) + L"\\" + exe;
            if (IsFile(path)) return path;
        }
    }
    return {};
}

std::wstring DefaultBrowserProcess() {
    std::wstring progId;
    std::wstring command;
    if (!ReadRegistryString(HKEY_CURRENT_USER,
                            L"Software\\Microsoft\\Windows\\Shell\\Associations\\UrlAssociations\\https\\UserChoice",
                            L"ProgId", 0, progId) ||
        !ReadRegistryString(HKEY_CLASSES_ROOT, progId + L"\\shell\\open\\command", nullptr, 0,
                            command)) {
        return {};
    }
    const std::wstring program = FileNameOf(ProgramOfCommand(command));
    return program == L"launcher.exe" ? std::wstring(L"opera.exe") : program;
}

BrowserTarget DefaultBrowser() {
    BrowserTarget browser;
    browser.process = DefaultBrowserProcess();
    browser.anyKnown = !browser.process.empty() && !IsKnownBrowserName(browser.process);
    return browser;
}

BrowserTarget ResolveBrowser(const std::wstring& choice, const std::wstring& customPath) {
    const std::wstring id = Lowercase(Trim(choice));
    if (id == L"custom") {
        std::wstring path = Trim(customPath);
        if (path.size() > 1 && path.front() == L'"' && path.back() == L'"') {
            path = Trim(path.substr(1, path.size() - 2));
        }
        path = ExpandVariables(path);
        if (IsFile(path)) {
            BrowserTarget browser;
            browser.file = path;
            browser.process = FileNameOf(path);
            browser.anyKnown = true;
            return browser;
        }
        return DefaultBrowser();
    }
    for (const KnownBrowser& known : kBrowsers) {
        if (id == known.id) {
            const std::wstring file = FindBrowserProgram(known);
            if (file.empty()) break;
            BrowserTarget browser;
            browser.file = file;
            browser.process = known.process;
            return browser;
        }
    }
    return DefaultBrowser();  // "default", or a browser that isn't installed.
}

BrowserTarget SelectedBrowser() {
    return ResolveBrowser(g_settings.browser, g_settings.browserPath);
}

bool OpenWithBrowser(const std::wstring& target, BrowserTarget& browser) {
    if (!browser.file.empty()) {
        const std::wstring parameters = L'"' + target + L'"';
        if ((IsProcessElevated() && ShellExecuteThroughExplorer(browser.file, parameters)) ||
            reinterpret_cast<INT_PTR>(ShellExecuteW(nullptr, L"open", browser.file.c_str(),
                                                    parameters.c_str(), nullptr,
                                                    SW_SHOWNORMAL)) > 32) {
            return true;
        }
        Wh_Log(L"Couldn't start %s", browser.file.c_str());
        browser = DefaultBrowser();
    }
    return (IsProcessElevated() && ShellExecuteThroughExplorer(target)) ||
           reinterpret_cast<INT_PTR>(ShellExecuteW(nullptr, L"open", target.c_str(), nullptr,
                                                   nullptr, SW_SHOWNORMAL)) > 32;
}

struct OpenJob {
    std::wstring target;
    BrowserTarget browser;
};

DWORD WINAPI OpenThreadProc(LPVOID param) {
    std::unique_ptr<OpenJob> job(static_cast<OpenJob*>(param));
    const HRESULT coInit =
        CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);
    if (!OpenWithBrowser(job->target, job->browser)) {
        Wh_Log(L"Couldn't open %s", job->target.c_str());
    }
    if (SUCCEEDED(coInit)) {
        CoUninitialize();
    }
    g_helperThreads--;
    return 0;
}

void OpenInBrowser(const std::wstring& target, const BrowserTarget& browser) {
    auto* param = new OpenJob{target, browser};
    g_helperThreads++;
    HANDLE thread = CreateThread(nullptr, 0, OpenThreadProc, param, 0, nullptr);
    if (thread) {
        CloseHandle(thread);
    } else {
        g_helperThreads--;
        delete param;
    }
}

extern std::atomic<bool> g_stopping;

struct BrowserHandoffJob {
    uint32_t id = 0;
    HWND notify = nullptr;
    DWORD clipboardSequence = 0;
    std::wstring prompt;
    std::vector<std::shared_ptr<const Image>> images;  // Everything the user selected.
    std::vector<std::wstring> imagePaths;              // The PNG files made from them.
    std::vector<std::wstring> onClipboard;             // The files the clipboard should hold right now.
    BrowserTarget browser;  // Where Gemini opens, and whose windows get the draft.
    std::atomic<bool> canceled{false};
};

struct BrowserHandoffMessage {
    uint32_t id = 0;
    bool pasted = false;
    std::wstring status;
};

bool IsGeminiChatUrl(std::wstring value) {
    value = Lowercase(Trim(value));
    if (value.rfind(L"https://", 0) == 0) value.erase(0, 8);
    constexpr PCWSTR host = L"gemini.google.com/";
    if (value.rfind(host, 0) != 0) return false;
    size_t i = wcslen(host);
    if (value.compare(i, 2, L"u/") == 0) {
        i += 2;
        const size_t digits = i;
        while (i < value.size() && iswdigit(value[i])) i++;
        if (i == digits || i >= value.size() || value[i] != L'/') return false;
        i++;
    }
    if (value.compare(i, 3, L"app") != 0) return false;
    i += 3;
    return i == value.size() || value[i] == L'/' || value[i] == L'?' || value[i] == L'#';
}

bool PastesSeveralFiles(const std::wstring& process) {
    for (PCWSTR name : {L"chrome.exe", L"msedge.exe", L"brave.exe", L"opera.exe", L"vivaldi.exe",
                        L"browser.exe", L"chromium.exe", L"thorium.exe"}) {
        if (process == name) return true;
    }
    return false;
}

bool IsTargetBrowserWindow(HWND hwnd, const BrowserTarget& browser) {
    return BrowserOwnsProcess(FileNameOf(ProcessPathOfWindow(hwnd)), browser);
}

std::wstring CachedElementString(IUIAutomationElement* element, PROPERTYID property) {
    VARIANT value;
    VariantInit(&value);
    std::wstring text;
    if (SUCCEEDED(element->GetCachedPropertyValue(property, &value)) && value.vt == VT_BSTR && value.bstrVal) {
        text.assign(value.bstrVal, SysStringLen(value.bstrVal));
    }
    VariantClear(&value);
    return text;
}

std::wstring CurrentElementString(IUIAutomationElement* element, PROPERTYID property) {
    VARIANT value;
    VariantInit(&value);
    std::wstring text;
    if (SUCCEEDED(element->GetCurrentPropertyValue(property, &value)) && value.vt == VT_BSTR && value.bstrVal) {
        text.assign(value.bstrVal, SysStringLen(value.bstrVal));
    }
    VariantClear(&value);
    return text;
}

ComPtr<IUIAutomationElement> ContainingDocument(IUIAutomationTreeWalker* walker,
                                               IUIAutomationElement* element) {
    ComPtr<IUIAutomationElement> current;
    element->AddRef();
    *current.Put() = element;
    for (int depth = 0; depth < 32 && current; depth++) {
        CONTROLTYPEID type = 0;
        if (SUCCEEDED(current->get_CurrentControlType(&type)) && type == UIA_DocumentControlTypeId) {
            return current;
        }
        ComPtr<IUIAutomationElement> parent;
        if (FAILED(walker->GetParentElement(current.Get(), parent.Put()))) break;
        current = std::move(parent);
    }
    return {};
}

ComPtr<IUIAutomationElement> FindGeminiComposer(IUIAutomation* automation,
                                               HWND browser, bool& verifiedPage,
                                               bool* sawDocument = nullptr) {
    verifiedPage = false;
    if (sawDocument) *sawDocument = false;
    ComPtr<IUIAutomationElement> root;
    ComPtr<IUIAutomationTreeWalker> walker;
    ComPtr<IUIAutomationCondition> editCondition, documentCondition;
    ComPtr<IUIAutomationCacheRequest> cache;
    VARIANT type;
    VariantInit(&type);
    type.vt = VT_I4;
    if (FAILED(automation->ElementFromHandle(browser, root.Put())) || !root ||
        FAILED(automation->get_ControlViewWalker(walker.Put())) || !walker ||
        FAILED(automation->CreateCacheRequest(cache.Put()))) return {};
    type.lVal = UIA_EditControlTypeId;
    if (FAILED(automation->CreatePropertyCondition(UIA_ControlTypePropertyId, type, editCondition.Put()))) return {};
    type.lVal = UIA_DocumentControlTypeId;
    if (FAILED(automation->CreatePropertyCondition(UIA_ControlTypePropertyId, type, documentCondition.Put()))) return {};
    for (PROPERTYID property : {UIA_NamePropertyId, UIA_ClassNamePropertyId,
                                UIA_ValueValuePropertyId, UIA_IsOffscreenPropertyId,
                                UIA_IsEnabledPropertyId, UIA_IsKeyboardFocusablePropertyId}) {
        cache->AddProperty(property);
    }

    ComPtr<IUIAutomationElementArray> documents;
    if (SUCCEEDED(root->FindAllBuildCache(TreeScope_Descendants, documentCondition.Get(), cache.Get(), documents.Put())) &&
        documents) {
        int count = 0;
        documents->get_Length(&count);
        if (sawDocument) *sawDocument = count > 0;
        for (int i = 0; i < std::min(count, 64); i++) {
            ComPtr<IUIAutomationElement> document;
            BOOL offscreen = TRUE;
            if (SUCCEEDED(documents->GetElement(i, document.Put())) && document &&
                SUCCEEDED(document->get_CachedIsOffscreen(&offscreen)) && !offscreen &&
                IsGeminiChatUrl(CachedElementString(document.Get(), UIA_ValueValuePropertyId))) {
                verifiedPage = true;
            }
        }
    }

    ComPtr<IUIAutomationElementArray> edits;
    if (FAILED(root->FindAllBuildCache(TreeScope_Descendants, editCondition.Get(), cache.Get(), edits.Put())) || !edits) {
        return {};
    }
    int count = 0;
    edits->get_Length(&count);
    struct Candidate {
        ComPtr<IUIAutomationElement> edit;
        int score;
    };
    std::vector<Candidate> candidates;
    bool addressBar = false;
    for (int i = 0; i < std::min(count, 128); i++) {
        ComPtr<IUIAutomationElement> edit;
        if (FAILED(edits->GetElement(i, edit.Put())) || !edit) continue;
        BOOL offscreen = TRUE, enabled = FALSE, focusable = FALSE;
        edit->get_CachedIsOffscreen(&offscreen);
        edit->get_CachedIsEnabled(&enabled);
        edit->get_CachedIsKeyboardFocusable(&focusable);
        if (offscreen || !enabled) continue;
        if (IsGeminiChatUrl(CachedElementString(edit.Get(), UIA_ValueValuePropertyId)) &&
            !ContainingDocument(walker.Get(), edit.Get())) {
            addressBar = true;
            continue;
        }
        if (!focusable) continue;
        const std::wstring name = Lowercase(CachedElementString(edit.Get(), UIA_NamePropertyId));
        const std::wstring className = Lowercase(CachedElementString(edit.Get(), UIA_ClassNamePropertyId));
        if (name.find(L"search") != std::wstring::npos) continue;
        const int score = name.find(L"gemini") != std::wstring::npos ? 30
                          : name.find(L"prompt") != std::wstring::npos ? 20
                          : className.find(L"ql-editor") != std::wstring::npos ? 20 : 0;
        if (score) candidates.push_back({std::move(edit), score});
    }
    if (addressBar) verifiedPage = true;

    ComPtr<IUIAutomationElement> best;
    int bestScore = -1;
    bool tied = false;
    for (Candidate& candidate : candidates) {
        const auto document = ContainingDocument(walker.Get(), candidate.edit.Get());
        if (!document) continue;  // Not in a web page.
        const std::wstring address = CurrentElementString(document.Get(), UIA_ValueValuePropertyId);
        if (address.empty() ? !addressBar : !IsGeminiChatUrl(address)) continue;
        if (!address.empty()) verifiedPage = true;
        if (candidate.score > bestScore) {
            bestScore = candidate.score;
            best = std::move(candidate.edit);
            tied = false;
        } else if (candidate.score == bestScore) {
            tied = true;
        }
    }
    if (tied) return {};
    return best;
}

struct BrowserAttachmentSnapshot {
    bool readable = false;
    std::vector<std::wstring> items;
};

std::wstring ElementRuntimeKey(IUIAutomationElement* element) {
    SAFEARRAY* id = nullptr;
    if (FAILED(element->GetRuntimeId(&id)) || !id) return {};
    LONG first = 0, last = -1;
    LONG* values = nullptr;
    std::wstring key;
    if (SUCCEEDED(SafeArrayGetLBound(id, 1, &first)) &&
        SUCCEEDED(SafeArrayGetUBound(id, 1, &last)) && last >= first && last - first < 64 &&
        SUCCEEDED(SafeArrayAccessData(id, reinterpret_cast<void**>(&values)))) {
        for (LONG i = 0; i <= last - first; i++) key += std::to_wstring(values[i]) + L":";
        SafeArrayUnaccessData(id);
    }
    SafeArrayDestroy(id);
    return key;
}

BrowserAttachmentSnapshot ReadBrowserAttachments(IUIAutomation* automation, HWND browser,
                                                 const RECT& editor) {
    BrowserAttachmentSnapshot result;
    ComPtr<IUIAutomationElement> root;
    ComPtr<IUIAutomationCondition> condition;
    ComPtr<IUIAutomationCacheRequest> cache;
    ComPtr<IUIAutomationElementArray> elements;
    VARIANT type;
    VariantInit(&type);
    type.vt = VT_I4;
    type.lVal = UIA_ImageControlTypeId;
    int count = 0;
    if (FAILED(automation->ElementFromHandle(browser, root.Put())) || !root ||
        FAILED(automation->CreatePropertyCondition(UIA_ControlTypePropertyId, type, condition.Put())) ||
        FAILED(automation->CreateCacheRequest(cache.Put()))) return result;
    cache->AddProperty(UIA_IsOffscreenPropertyId);
    cache->AddProperty(UIA_BoundingRectanglePropertyId);
    if (FAILED(root->FindAllBuildCache(TreeScope_Descendants, condition.Get(), cache.Get(), elements.Put())) ||
        !elements || FAILED(elements->get_Length(&count))) return result;
    result.readable = true;
    const float scale = DpiScaleAt(RectCenter(editor));
    const RECT around{editor.left - static_cast<LONG>(140 * scale), editor.top - static_cast<LONG>(360 * scale),
                      editor.right + static_cast<LONG>(440 * scale), editor.bottom + static_cast<LONG>(60 * scale)};
    for (int i = 0; i < std::min(count, 256); i++) {
        ComPtr<IUIAutomationElement> element;
        BOOL offscreen = TRUE;
        RECT bounds{}, overlap;
        if (FAILED(elements->GetElement(i, element.Put())) || !element ||
            FAILED(element->get_CachedIsOffscreen(&offscreen)) || offscreen ||
            FAILED(element->get_CachedBoundingRectangle(&bounds)) ||
            !IntersectRect(&overlap, &bounds, &around)) continue;
        const auto key = ElementRuntimeKey(element.Get());
        if (!key.empty()) result.items.push_back(key);
    }
    return result;
}

size_t CountNewBrowserAttachments(const BrowserAttachmentSnapshot& before,
                                  const BrowserAttachmentSnapshot& after) {
    if (!before.readable || !after.readable) return 0;
    return static_cast<size_t>(std::count_if(after.items.begin(), after.items.end(), [&](const std::wstring& item) {
        return std::find(before.items.begin(), before.items.end(), item) == before.items.end();
    }));
}

std::vector<INPUT> BrowserImagePasteInputs() {
    std::vector<INPUT> inputs(4);
    for (INPUT& input : inputs) input.type = INPUT_KEYBOARD;
    inputs[0].ki.wVk = VK_CONTROL;
    inputs[1].ki.wVk = 'V';
    inputs[2].ki.wVk = 'V';
    inputs[2].ki.dwFlags = KEYEVENTF_KEYUP;
    inputs[3].ki.wVk = VK_CONTROL;
    inputs[3].ki.dwFlags = KEYEVENTF_KEYUP;
    return inputs;
}

std::wstring BrowserDraftText(const std::wstring& prompt) {
    std::wstring text = prompt.substr(0, 4000);
    for (wchar_t& c : text) {
        if (c < L' ' || c == 0x7F) c = L' ';
    }
    return text;
}

std::vector<INPUT> BrowserDraftInputs(const std::wstring& prompt) {
    std::vector<INPUT> inputs;
    const std::wstring text = BrowserDraftText(prompt);
    inputs.reserve(text.size() * 2);
    for (wchar_t c : text) {
        INPUT down{};
        down.type = INPUT_KEYBOARD;
        down.ki.wScan = c;
        down.ki.dwFlags = KEYEVENTF_UNICODE;
        inputs.push_back(down);
        down.ki.dwFlags |= KEYEVENTF_KEYUP;
        inputs.push_back(down);
    }
    return inputs;
}

std::wstring CollapseSpacing(const std::wstring& text) {
    std::wstring out;
    bool pending = false;
    for (wchar_t c : text) {
        if (c == 0x200B) continue;
        if (iswspace(c) || c == 0xA0) {
            pending = !out.empty();
            continue;
        }
        if (pending) out += L' ';
        pending = false;
        out += c;
    }
    return out;
}

bool ContainsIgnoringSpacing(const std::wstring& text, const std::wstring& part) {
    const std::wstring needle = CollapseSpacing(part);
    return needle.empty() || CollapseSpacing(text).find(needle) != std::wstring::npos;
}

bool BrowserStillTarget(HWND expectedBrowser, const BrowserHandoffJob& job) {
    return !g_stopping && !job.canceled && expectedBrowser &&
           GetForegroundWindow() == expectedBrowser;
}

bool BrowserKeysAllowed(HWND expectedBrowser, const BrowserHandoffJob& job) {
    return BrowserStillTarget(expectedBrowser, job) &&
           !(GetAsyncKeyState(VK_CONTROL) & 0x8000) &&
           !(GetAsyncKeyState(VK_SHIFT) & 0x8000) &&
           !(GetAsyncKeyState(VK_MENU) & 0x8000) &&
           !(GetAsyncKeyState(VK_LWIN) & 0x8000) &&
           !(GetAsyncKeyState(VK_RWIN) & 0x8000);
}

bool BrowserPasteStillValid(HWND expectedBrowser, DWORD clipboardSequence,
                            const BrowserHandoffJob& job) {
    return BrowserKeysAllowed(expectedBrowser, job) &&
           GetClipboardSequenceNumber() == clipboardSequence;
}

bool ClipboardHoldsFiles(HWND owner, const std::vector<std::wstring>& paths) {
    bool holds = false;
    if (paths.empty() || !OpenClipboardWithRetry(owner)) return false;
    if (HANDLE drop = GetClipboardData(CF_HDROP)) {
        const HDROP files = static_cast<HDROP>(drop);
        holds = DragQueryFileW(files, 0xFFFFFFFF, nullptr, 0) == paths.size();
        for (UINT i = 0; holds && i < paths.size(); i++) {
            WCHAR name[MAX_PATH * 2]{};
            holds = DragQueryFileW(files, i, name, ARRAYSIZE(name)) &&
                    _wcsicmp(name, paths[i].c_str()) == 0;
        }
    }
    CloseClipboard();
    return holds;
}

bool ClipboardStillOurs(BrowserHandoffJob& job) {
    const DWORD sequence = GetClipboardSequenceNumber();
    if (sequence == job.clipboardSequence) return true;
    if (!ClipboardHoldsFiles(job.notify, job.onClipboard)) return false;
    job.clipboardSequence = sequence;
    return true;
}

bool BrowserComposerStillCurrent(IUIAutomation* automation, IUIAutomationElement* composer,
                                 HWND browser, const BrowserHandoffJob& job, bool forPaste,
                                 bool requireFocus) {
    auto allowed = [&] {
        return forPaste ? BrowserPasteStillValid(browser, job.clipboardSequence, job)
                        : BrowserKeysAllowed(browser, job);
    };
    if (!allowed()) return false;
    bool verified = false;
    auto current = FindGeminiComposer(automation, browser, verified);
    BOOL same = FALSE;
    if (!verified || !current ||
        FAILED(automation->CompareElements(composer, current.Get(), &same)) || !same) return false;
    if (requireFocus) {
        ComPtr<IUIAutomationElement> focused;
        same = FALSE;
        if (FAILED(automation->GetFocusedElement(focused.Put())) || !focused ||
            FAILED(automation->CompareElements(composer, focused.Get(), &same)) || !same) return false;
    }
    return allowed();
}

bool FocusBrowserComposer(IUIAutomation* automation, IUIAutomationElement* composer,
                          HWND browser, const BrowserHandoffJob& job, bool forPaste) {
    auto allowed = [&] {
        return forPaste ? BrowserPasteStillValid(browser, job.clipboardSequence, job)
                        : BrowserKeysAllowed(browser, job);
    };
    if (!BrowserComposerStillCurrent(automation, composer, browser, job, forPaste, false) ||
        FAILED(composer->SetFocus())) return false;
    for (int attempt = 0; attempt < 8; attempt++) {
        ComPtr<IUIAutomationElement> focused;
        BOOL same = FALSE;
        if (SUCCEEDED(automation->GetFocusedElement(focused.Put())) && focused &&
            SUCCEEDED(automation->CompareElements(composer, focused.Get(), &same)) && same) {
            return allowed();
        }
        if (!BrowserStillTarget(browser, job)) return false;
        Sleep(50);
    }
    return false;
}

bool ReadElementText(IUIAutomationElement* element, std::wstring& text) {
    ComPtr<IUIAutomationValuePattern> value;
    BSTR raw = nullptr;
    if (FAILED(element->GetCurrentPatternAs(UIA_ValuePatternId, kIidIUIAutomationValuePattern,
                                            value.PutVoid())) || !value ||
        FAILED(value->get_CurrentValue(&raw)) || !raw) return false;
    text.assign(raw, SysStringLen(raw));
    SysFreeString(raw);
    return true;
}

class SteadyCandidate {
  public:
    static constexpr double kSteadyMs = 800.0;

    bool Update(const std::wstring& key, double now) {
        if (key.empty() || key != key_) {
            key_ = key;
            since_ = now;
            return false;
        }
        return now - since_ >= kSteadyMs;
    }

  private:
    std::wstring key_;
    double since_ = 0;
};

struct BrowserWindowSearch {
    const BrowserTarget* browser;
    std::vector<HWND> windows;
    bool minimized = false;  // Minimized windows count too.
};

BOOL CALLBACK CollectBrowserWindow(HWND hwnd, LPARAM param) {
    auto* search = reinterpret_cast<BrowserWindowSearch*>(param);
    if (IsWindowVisible(hwnd) && (search->minimized || !IsIconic(hwnd)) &&
        IsTargetBrowserWindow(hwnd, *search->browser)) {
        search->windows.push_back(hwnd);
    }
    return TRUE;
}

void PointerBringToFront(HWND window) {
    if (IsIconic(window)) ShowWindow(window, SW_RESTORE);
    BringWindowToTop(window);
    SetForegroundWindow(window);
}

std::vector<std::wstring> OpenGeminiComposerKeys(IUIAutomation* automation,
                                                 const BrowserTarget& browser) {
    BrowserWindowSearch search{&browser, {}};
    EnumWindows(CollectBrowserWindow, reinterpret_cast<LPARAM>(&search));
    const std::vector<HWND>& windows = search.windows;
    std::vector<std::wstring> keys;
    for (int attempt = 0; attempt < 6; attempt++) {
        keys.clear();
        bool waiting = false;
        for (HWND window : windows) {
            bool verified = false;
            if (auto composer = FindGeminiComposer(automation, window, verified)) {
                const std::wstring key = ElementRuntimeKey(composer.Get());
                if (!key.empty()) keys.push_back(key);
            } else if (verified) {
                waiting = true;
            }
        }
        if (!waiting) break;
        Sleep(150);
    }
    return keys;
}

HWND FindNewGeminiWindow(IUIAutomation* automation, const BrowserTarget& browser,
                         const std::vector<std::wstring>& alreadyOpen) {
    BrowserWindowSearch search{&browser, {}, true};
    EnumWindows(CollectBrowserWindow, reinterpret_cast<LPARAM>(&search));
    HWND minimized = nullptr;
    for (HWND window : search.windows) {
        if (IsIconic(window)) {  // Its page can't be looked into: the title has to do.
            WCHAR title[256]{};
            GetWindowTextW(window, title, ARRAYSIZE(title));
            if (!minimized && Lowercase(title).find(L"gemini") != std::wstring::npos) minimized = window;
            continue;
        }
        bool verified = false;
        auto composer = FindGeminiComposer(automation, window, verified);
        if (!composer) continue;
        const std::wstring key = ElementRuntimeKey(composer.Get());
        if (!key.empty() && std::find(alreadyOpen.begin(), alreadyOpen.end(), key) == alreadyOpen.end()) {
            return window;
        }
    }
    return minimized;
}

std::wstring BrowserDraftStatus(size_t total, size_t added, bool questionTyped, bool clipboardOurs) {
    if (total == 0) return Tr(questionTyped ? Str::QuestionInGemini : Str::ClickBoxText);
    const bool several = total > 1;
    if (added >= total) return Tr(several ? Str::DraftAddedMany : Str::DraftAddedOne);
    auto typed = [&](const std::wstring& status) {
        return questionTyped ? JoinSentences(Tr(Str::QuestionInGemini), status) : status;
    };
    if (added > 0) {
        return typed(TrFormat(Str::DraftPartial, std::to_wstring(added), std::to_wstring(total)));
    }
    if (!clipboardOurs) {
        return typed(Tr(several ? Str::ClipboardChangedMany : Str::ClipboardChangedOne));
    }
    if (questionTyped) {
        return typed(Tr(several ? Str::IfNotAttachedMany : Str::IfNotAttachedOne));
    }
    return Tr(several ? Str::ClickBoxMany : Str::ClickBoxOne);
}

struct BrowserDraftState {
    std::wstring composer;
    bool keysSent = false;
    bool everTyped = false;
    int attempts = 0;
    int pastes = 0;
    RECT editor{};
    BrowserAttachmentSnapshot baseline;
};

enum class DraftOutcome { Added, Partial, Retry };

std::vector<INPUT> BrowserSelectAllInputs() {
    std::vector<INPUT> inputs = BrowserImagePasteInputs();
    inputs[1].ki.wVk = 'A';
    inputs[2].ki.wVk = 'A';
    return inputs;
}

bool ReadSteadyText(IUIAutomationElement* element, std::wstring& text, HWND browser,
                    const BrowserHandoffJob& job) {
    bool readable = ReadElementText(element, text);
    for (int steady = 0, tries = 0; readable && steady < 2 && tries < 50 && BrowserStillTarget(browser, job); tries++) {
        Sleep(150);
        std::wstring again;
        readable = ReadElementText(element, again);
        steady = readable && again == text ? steady + 1 : 0;
        text = std::move(again);
    }
    return readable;
}

DraftOutcome FillBrowserDraft(IUIAutomation* automation, IUIAutomationElement* composer,
                              HWND browser, BrowserHandoffJob& job, BrowserDraftState& state,
                              double deadline, std::wstring& status) {
    state.attempts++;
    if (state.pastes == 0) composer->get_CurrentBoundingRectangle(&state.editor);
    const std::wstring question = BrowserDraftText(job.prompt);
    const size_t total = job.images.size();
    const bool oneByOne = job.imagePaths.size() > 1 &&
                          !PastesSeveralFiles(FileNameOf(ProcessPathOfWindow(browser)));
    const size_t pastes = total == 0 ? 0 : oneByOne ? job.imagePaths.size() : 1;
    const int maxPastes = static_cast<int>(pastes) + 2;
    bool questionAdded = question.empty();
    bool clipboardOurs = true;
    size_t confirmed = 0;
    auto attached = [&] {
        return std::min(CountNewBrowserAttachments(state.baseline,
                                                   ReadBrowserAttachments(automation, browser, state.editor)),
                        pastes);
    };
    auto imagesAdded = [&] {
        return confirmed < pastes ? (oneByOne ? confirmed : 0)
               : oneByOne ? job.imagePaths.size()
               : job.imagePaths.empty() ? std::min<size_t>(1, total) : total;
    };
    auto fail = [&](bool retryable) {
        status = BrowserDraftStatus(total, imagesAdded(), questionAdded && !question.empty(), clipboardOurs);
        const bool again = retryable && clipboardOurs && state.attempts < 6 && NowMs() < deadline &&
                           BrowserStillTarget(browser, job);
        return again ? DraftOutcome::Retry : DraftOutcome::Partial;
    };
    auto focusComposer = [&](bool forPaste) {
        for (int attempt = 0; attempt < 20 && BrowserStillTarget(browser, job); attempt++) {
            if (!BrowserKeysAllowed(browser, job)) {
                Sleep(100);
                continue;
            }
            if (BrowserComposerStillCurrent(automation, composer, browser, job, forPaste, true)) return true;
            if (!FocusBrowserComposer(automation, composer, browser, job, forPaste)) return false;
        }
        return false;
    };

    bool overwrite = false;
    if (!questionAdded) {
        std::wstring shown;
        const bool readable = state.everTyped ? ReadSteadyText(composer, shown, browser, job)
                                              : ReadElementText(composer, shown);
        if (readable ? ContainsIgnoringSpacing(shown, question) : state.keysSent) {
            questionAdded = state.keysSent = true;
        } else if (readable && state.everTyped) {
            state.keysSent = false;
            overwrite = !CollapseSpacing(shown).empty();
        }
    }
    if (!questionAdded && !state.keysSent) {
        if (!focusComposer(false)) return fail(true);
        auto keys = BrowserDraftInputs(question);
        if (overwrite) {
            const std::vector<INPUT> selectAll = BrowserSelectAllInputs();
            keys.insert(keys.begin(), selectAll.begin(), selectAll.end());
        }
        state.everTyped = true;
        if (SendInput(static_cast<UINT>(keys.size()), keys.data(), sizeof(INPUT)) == keys.size()) {
            state.keysSent = true;
            const double typedAt = NowMs();
            const double typingMs = std::min(15000.0, 3000.0 + 5.0 * static_cast<double>(question.size()));
            while (!questionAdded && NowMs() - typedAt < typingMs && BrowserStillTarget(browser, job)) {
                Sleep(50);
                std::wstring shown;
                const bool readable = ReadElementText(composer, shown);
                if (!BrowserComposerStillCurrent(automation, composer, browser, job, false, true)) break;
                questionAdded = readable ? ContainsIgnoringSpacing(shown, question)
                                         : NowMs() - typedAt > 300;
            }
        }
    }

    while (true) {
        if (state.pastes > 0 && BrowserComposerStillCurrent(automation, composer, browser, job, false, false)) {
            confirmed = std::max(confirmed, attached());
        }
        if (confirmed >= pastes || state.pastes >= maxPastes || NowMs() >= deadline ||
            (state.pastes > 0 && !state.baseline.readable) || !BrowserStillTarget(browser, job)) {
            break;
        }
        if (!ClipboardStillOurs(job)) {
            clipboardOurs = false;
            break;
        }
        if (!focusComposer(true)) break;
        const size_t index = oneByOne ? confirmed : 0;
        if (oneByOne) {
            const std::vector<std::wstring> next{job.imagePaths[index]};
            if (!CopyImageFileToClipboard(job.notify, next, job.clipboardSequence)) {
                clipboardOurs = false;
                break;
            }
            job.clipboardSequence = GetClipboardSequenceNumber();
            job.onClipboard = next;
        }
        if (state.pastes == 0) {
            state.baseline = ReadBrowserAttachments(automation, browser, state.editor);
            for (int retry = 0; retry < 3 && !state.baseline.readable &&
                 BrowserPasteStillValid(browser, job.clipboardSequence, job); retry++) {
                Sleep(100);
                state.baseline = ReadBrowserAttachments(automation, browser, state.editor);
            }
        }
        auto keys = BrowserImagePasteInputs();
        if (!BrowserComposerStillCurrent(automation, composer, browser, job, true, true)) {
            clipboardOurs = GetClipboardSequenceNumber() == job.clipboardSequence;
            break;
        }
        if (SendInput(static_cast<UINT>(keys.size()), keys.data(), sizeof(INPUT)) != keys.size()) {
            INPUT release[2]{};
            for (INPUT& input : release) { input.type = INPUT_KEYBOARD; input.ki.dwFlags = KEYEVENTF_KEYUP; }
            release[0].ki.wVk = 'V';
            release[1].ki.wVk = VK_CONTROL;
            SendInput(2, release, sizeof(INPUT));
            break;
        }
        state.pastes++;
        const size_t wanted = oneByOne ? index + 1 : 1;
        const double sentAt = NowMs();
        const double giveUp = std::min(sentAt + 20000, deadline + 5000);
        double waitUntil = sentAt + (state.baseline.readable ? 5000 : 1500);
        while (confirmed < wanted && NowMs() < waitUntil && NowMs() < giveUp && BrowserStillTarget(browser, job)) {
            Sleep(150);
            if (!BrowserComposerStillCurrent(automation, composer, browser, job, false, true)) break;
            confirmed = std::max(confirmed, attached());
            if (!questionAdded && state.keysSent) {
                std::wstring shown;
                if (ReadElementText(composer, shown) && ContainsIgnoringSpacing(shown, question)) {
                    questionAdded = true;
                    waitUntil = std::max(waitUntil, NowMs() + 4000);
                } else {
                    waitUntil = std::max(waitUntil, NowMs() + 1500);
                }
            }
        }
    }
    if (confirmed < pastes) {
        return fail(state.pastes == 0 || (state.baseline.readable && state.pastes < maxPastes));
    }
    if (state.keysSent && !questionAdded &&
        BrowserComposerStillCurrent(automation, composer, browser, job, false, true)) {
        std::wstring shown;
        questionAdded = ReadElementText(composer, shown) &&
                        ContainsIgnoringSpacing(shown, question) &&
                        BrowserComposerStillCurrent(automation, composer, browser, job, false, true);
    }
    if (!questionAdded) return fail(true);
    if (imagesAdded() < total) return fail(false);
    const double settledAt = NowMs() + 700;
    while (NowMs() < settledAt && BrowserStillTarget(browser, job)) Sleep(50);
    std::wstring shown;
    if (!BrowserComposerStillCurrent(automation, composer, browser, job, false, false) ||
        (!question.empty() && ReadElementText(composer, shown) && !ContainsIgnoringSpacing(shown, question)) ||
        attached() < pastes) {
        return fail(true);
    }
    return DraftOutcome::Added;
}

ComPtr<IUIAutomation> CreateAutomation() {
    ComPtr<IUIAutomation> automation;
    if (FAILED(CoCreateInstance(kClsidCUIAutomation8, nullptr, CLSCTX_INPROC_SERVER,
                                kIidIUIAutomation, automation.PutVoid()))) {
        CoCreateInstance(kClsidCUIAutomation, nullptr, CLSCTX_INPROC_SERVER,
                         kIidIUIAutomation, automation.PutVoid());
    }
    if (automation) {
        ComPtr<IUIAutomation2> automation2;
        if (SUCCEEDED(automation->QueryInterface(kIidIUIAutomation2, automation2.PutVoid()))) {
            automation2->put_ConnectionTimeout(700);
            automation2->put_TransactionTimeout(700);
        }
    }
    return automation;
}

DWORD WINAPI BrowserHandoffThreadProc(LPVOID param) {
    std::unique_ptr<std::shared_ptr<BrowserHandoffJob>> holder(
        static_cast<std::shared_ptr<BrowserHandoffJob>*>(param));
    const std::shared_ptr<BrowserHandoffJob> job = *holder;
    auto result = std::make_unique<BrowserHandoffMessage>();
    result->id = job->id;
    const HRESULT coInit = CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);
    if (!job->images.empty() && SUCCEEDED(coInit) && !job->canceled && !g_stopping) {
        for (const auto& image : job->images) {
            const std::wstring path = WriteGeminiImageFile(*image, job->notify);
            if (path.empty()) {  // All of them or none: a part of the pictures would mislead.
                job->imagePaths.clear();
                break;
            }
            job->imagePaths.push_back(path);
        }
        if (!job->canceled && !g_stopping && GetClipboardSequenceNumber() == job->clipboardSequence && !job->imagePaths.empty() &&
            CopyImageFileToClipboard(job->notify, job->imagePaths, job->clipboardSequence)) {
            job->clipboardSequence = GetClipboardSequenceNumber();
            job->onClipboard = job->imagePaths;
        }
    }
    ComPtr<IUIAutomation> automation;
    if (SUCCEEDED(coInit)) automation = CreateAutomation();
    const std::vector<std::wstring> alreadyOpen =
        automation && !job->canceled ? OpenGeminiComposerKeys(automation.Get(), job->browser)
                                     : std::vector<std::wstring>();
    const std::wstring url = L"https://gemini.google.com/app";
    const bool launched = !job->canceled && !g_stopping && OpenWithBrowser(url, job->browser);
    HWND verifiedBrowser = nullptr;
    SteadyCandidate steady;
    BrowserDraftState draft;
    double blankSince = -1;  // When the window began to show no page.
    double lastRestart = 0;  // When the UI Automation client last started over.
    double leftAt = -1;
    bool everSawDocument = false;
    const double launchedAt = NowMs();
    double lastPush = launchedAt;
    int pushes = 0;
    const double deadline = launchedAt + 30000;
    auto pushForward = [&] {
        const double now = NowMs();
        if (verifiedBrowser || pushes >= 6 || now - launchedAt < 1200 || now - lastPush < 700) return;
        lastPush = now;
        pushes++;
        if (HWND window = FindNewGeminiWindow(automation.Get(), job->browser, alreadyOpen)) PointerBringToFront(window);
    };
    while (launched && automation && !job->canceled && !g_stopping && NowMs() < deadline) {
        const HWND foreground = GetForegroundWindow();
        const bool inBrowser = IsWindowVisible(foreground) && IsTargetBrowserWindow(foreground, job->browser);
        if (verifiedBrowser && !inBrowser) {
            if (leftAt < 0) leftAt = NowMs();
            if (NowMs() - leftAt > 1500) break;
        } else {
            leftAt = -1;
        }
        if (!inBrowser) {
            steady.Update(L"", NowMs());
            pushForward();
            Sleep(100);
            continue;
        }
        bool verifiedPage = false;
        bool sawDocument = false;
        auto composer = FindGeminiComposer(automation.Get(), foreground, verifiedPage, &sawDocument);
        if (!verifiedPage) pushForward();  // This window isn't the one with Gemini.
        if (sawDocument) {
            blankSince = -1;
            everSawDocument = true;
        } else {
            const double now = NowMs();
            if (blankSince < 0) {
                blankSince = now;
                lastRestart = now;
            }
            if (now - lastRestart > 1200) {
                if (ComPtr<IUIAutomation> fresh = CreateAutomation()) automation = std::move(fresh);
                lastRestart = now;
            }
        }
        if (verifiedPage) verifiedBrowser = foreground;
        std::wstring key = composer ? ElementRuntimeKey(composer.Get()) : std::wstring();
        if (std::find(alreadyOpen.begin(), alreadyOpen.end(), key) != alreadyOpen.end()) key.clear();
        if (!key.empty() && key != draft.composer) {
            draft.composer = key;
            draft.keysSent = false;
            draft.attempts = 0;
        }
        if (steady.Update(key, NowMs()) &&
            FocusBrowserComposer(automation.Get(), composer.Get(), foreground, *job, false)) {
            const DraftOutcome outcome = FillBrowserDraft(automation.Get(), composer.Get(), foreground,
                                                         *job, draft, deadline, result->status);
            if (outcome != DraftOutcome::Retry) {
                result->pasted = outcome == DraftOutcome::Added;
                break;
            }
            steady.Update(L"", NowMs());
        }
        Sleep(100);
    }
    if (!launched) {
        result->status = Tr(job->images.empty()      ? Str::BrowserFailedText
                            : job->images.size() > 1 ? Str::BrowserFailedMany
                                                     : Str::BrowserFailedOne);
    }
    if (!result->pasted && result->status.empty()) {
        result->status = everSawDocument
            ? BrowserDraftStatus(job->images.size(), 0, false, true)
            : std::wstring(Tr(Str::PageUnreadable));
    }
    automation.Reset();
    if (SUCCEEDED(coInit)) CoUninitialize();
    if (!job->canceled && !g_stopping) PostOwned(job->notify, WM_APP_BROWSER, std::move(result));
    g_helperThreads--;
    return 0;
}

bool StartBrowserHandoff(const std::shared_ptr<BrowserHandoffJob>& job) {
    auto* holder = new std::shared_ptr<BrowserHandoffJob>(job);
    g_helperThreads++;
    HANDLE thread = CreateThread(nullptr, 0, BrowserHandoffThreadProc, holder, 0, nullptr);
    if (!thread) {
        delete holder;
        g_helperThreads--;
        return false;
    }
    CloseHandle(thread);
    return true;
}

std::wstring UiLanguage() {
    WCHAR locale[LOCALE_NAME_MAX_LENGTH] = L"en";
    GetUserDefaultLocaleName(locale, LOCALE_NAME_MAX_LENGTH);
    std::wstring language = locale;
    const size_t dash = language.find(L'-');
    if (dash != std::wstring::npos) {
        language.resize(dash);
    }
    return language.empty() ? L"en" : language;
}

std::wstring GoogleLanguage() {
    const LanguageInfo* language = CurrentLanguage();
    if (!g_languageChosen || !language) {
        return UiLanguage();
    }
    return _wcsicmp(language->code, L"nb") == 0 ? L"no" : language->code;
}

constexpr double kLensPageLifetimeMs = 10.0 * 60 * 1000;
extern HWND g_messageWindow;
struct TemporaryLensPage { std::wstring path; double expires; };
std::mutex g_lensPagesMutex;
std::vector<TemporaryLensPage> g_lensPages;

void TrackLensPage(const std::wstring& path, double expires) {
    std::lock_guard<std::mutex> lock(g_lensPagesMutex);
    const auto found = std::find_if(g_lensPages.begin(), g_lensPages.end(),
        [&](const TemporaryLensPage& page) { return page.path == path; });
    if (found == g_lensPages.end()) {
        g_lensPages.push_back({path, expires});
    } else {
        found->expires = expires;
    }
}

double CleanupLensPages(double now) {
    double next = 1e9;
    std::lock_guard<std::mutex> lock(g_lensPagesMutex);
    for (auto it = g_lensPages.begin(); it != g_lensPages.end();) {
        if (now >= it->expires) {
            if (DeleteFileW(it->path.c_str()) || GetLastError() == ERROR_FILE_NOT_FOUND ||
                GetLastError() == ERROR_PATH_NOT_FOUND) {
                it = g_lensPages.erase(it);
                continue;
            }
            it->expires = now + 60000;  // A browser may still have the page open.
        }
        next = std::min(next, it->expires - now);
        ++it;
    }
    return next;
}

void DeleteOldLensPages(bool all) {
    if (g_storageDir.empty()) {
        return;
    }
    WIN32_FIND_DATAW data{};
    HANDLE find = FindFirstFileW((g_storageDir + L"\\lens-*.html").c_str(), &data);
    if (find == INVALID_HANDLE_VALUE) {
        return;
    }
    FILETIME current{};
    GetSystemTimeAsFileTime(&current);
    const ULONGLONG nowTicks = (ULONGLONG(current.dwHighDateTime) << 32) | current.dwLowDateTime;
    const double now = NowMs();
    do {
        if (data.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) continue;
        const std::wstring path = g_storageDir + L"\\" + data.cFileName;
        const ULONGLONG written = (ULONGLONG(data.ftLastWriteTime.dwHighDateTime) << 32) |
                                  data.ftLastWriteTime.dwLowDateTime;
        const double age = nowTicks >= written ? (nowTicks - written) / 10000.0 : 0.0;
        if (all || age >= kLensPageLifetimeMs) {
            if (!DeleteFileW(path.c_str()) && GetLastError() != ERROR_FILE_NOT_FOUND &&
                GetLastError() != ERROR_PATH_NOT_FOUND) {
                TrackLensPage(path, now + 60000);
            }
        } else {
            TrackLensPage(path, now + kLensPageLifetimeMs - age);
        }
    } while (FindNextFileW(find, &data));
    FindClose(find);
}

struct LensJob {
    std::shared_ptr<const Image> image;
    std::wstring language;
    BrowserTarget browser;
    HWND notify = nullptr;
};

std::string HtmlEscape(const std::wstring& text) {
    std::string out;
    for (const char c : ToUtf8(text)) {
        switch (c) {
            case '&':
                out += "&amp;";
                break;
            case '<':
                out += "&lt;";
                break;
            case '>':
                out += "&gt;";
                break;
            case '"':
                out += "&quot;";
                break;
            default:
                out += c;
        }
    }
    return out;
}

std::string ScriptString(const std::wstring& text) {
    std::string quoted;
    AppendJsonString(quoted, ToUtf8(text));
    std::string out;
    for (const char c : quoted) {
        if (c == '<') {
            out += "\\u003c";
        } else {
            out += c;
        }
    }
    return out;
}

std::string BuildLensPage(const std::vector<uint8_t>& png,
                          const std::wstring& language) {
    std::string page = "<!DOCTYPE html>\n<html lang=\"" + HtmlEscape(language) + "\"";
    if (UiIsRtl()) {
        page += " dir=\"rtl\"";
    }
    page +=
        "><head><meta charset=\"utf-8\">"
        "<meta name=\"referrer\" content=\"no-referrer\">"
        "<title>Google Lens</title><style>"
        "html,body{height:100%;margin:0;background:#1e1e2e;color:#cdd6f4;"
        "font:15px 'FiraCode Nerd Font','Segoe UI',system-ui,sans-serif}"
        "body{display:flex;flex-direction:column;align-items:center;"
        "justify-content:center;gap:14px}"
        "img{max-width:360px;max-height:220px;border-radius:14px}"
        "button{font:inherit;padding:9px 20px;border:0;border-radius:20px;"
        "background:linear-gradient(90deg,#89b4fa,#cba6f7);color:#11111b;cursor:pointer}"
        "</style></head><body><img id=\"p\" alt=\"\">"
        "<div id=\"s\">";
    page += HtmlEscape(Tr(Str::LensSearching));
    page += "</div><button id=\"b\" hidden>";
    page += HtmlEscape(Tr(Str::SearchWithLens));
    page +=
        "</button>"
        "<form id=\"f\" method=\"POST\" enctype=\"multipart/form-data\" "
        "action=\"https://lens.google.com/v3/upload?hl=";
    page += ToUtf8(language);
    page += "&amp;st=";
    page += std::to_string(GetTickCount64());
    page +=
        "\"><input type=\"file\" name=\"encoded_image\" id=\"i\" hidden>"
        "</form><script>\nconst data=\"";
    page += Base64Encode(png.data(), png.size());
    page +=
        "\";\n"
        "document.getElementById('p').src='data:image/png;base64,'+data;\n"
        "const button=document.getElementById('b');\n"
        "function go(){try{\n"
        "const bytes=Uint8Array.from(atob(data),c=>c.charCodeAt(0));\n"
        "const transfer=new DataTransfer();\n"
        "transfer.items.add(new File([bytes],'selection.png',{type:'image/png'}));\n"
        "document.getElementById('i').files=transfer.files;\n"
        "try{sessionStorage.setItem('sent','1');}catch(e){}\n"
        "document.getElementById('f').submit();\n"
        "}catch(e){document.getElementById('s').textContent=";
    page += ScriptString(Tr(Str::LensUploadFailed));
    page +=
        ";button.hidden=false;}}\n"
        "button.onclick=go;\n"
        "let sent=false;try{sent=sessionStorage.getItem('sent')==='1';}catch(e){}\n"
        "if(sent){document.getElementById('s').textContent='';button.hidden=false;}"
        "else{setTimeout(()=>{button.hidden=false;},5000);go();}\n"
        "</script></body></html>\n";
    return page;
}

DWORD WINAPI LensThreadProc(LPVOID param) {
    std::unique_ptr<LensJob> job(static_cast<LensJob*>(param));
    const HRESULT coInit = CoInitializeEx(nullptr, COINIT_MULTITHREADED);
    std::vector<uint8_t> png;
    const bool encoded = EncodePng(DownscaleImage(*job->image, 1000), png);
    if (SUCCEEDED(coInit)) {
        CoUninitialize();
    }
    if (encoded && !g_storageDir.empty() && !g_stopping) {
        const std::string page = BuildLensPage(png, job->language);
        static std::atomic<unsigned> sequence{0};
        const std::wstring path = g_storageDir + L"\\lens-" +
            std::to_wstring(GetCurrentProcessId()) + L"-" + std::to_wstring(GetTickCount64()) +
            L"-" + std::to_wstring(++sequence) + L".html";
        HANDLE file = page.size() <= MAXDWORD ?
            CreateFileW(path.c_str(), GENERIC_WRITE, FILE_SHARE_READ, nullptr,
                        CREATE_NEW, FILE_ATTRIBUTE_TEMPORARY, nullptr) : INVALID_HANDLE_VALUE;
        if (file != INVALID_HANDLE_VALUE) {
            DWORD written = 0;
            const BOOL ok = WriteFile(file, page.data(),
                                      static_cast<DWORD>(page.size()), &written,
                                      nullptr);
            CloseHandle(file);
            if (ok && written == page.size()) {
                TrackLensPage(path, NowMs() + kLensPageLifetimeMs);
                if (!g_stopping && job->notify) PostMessageW(job->notify, WM_APP_TEMP_FILE, 0, 0);
                if (!g_stopping) OpenInBrowser(path, job->browser);
            } else if (!DeleteFileW(path.c_str())) {
                TrackLensPage(path, NowMs() + 60000);
                if (!g_stopping && job->notify) PostMessageW(job->notify, WM_APP_TEMP_FILE, 0, 0);
            }
        }
    }
    g_helperThreads--;
    return 0;
}

void SearchWithLens(std::shared_ptr<const Image> image, const BrowserTarget& browser) {
    auto* job = new LensJob{std::move(image), GoogleLanguage(), browser, g_messageWindow};
    g_helperThreads++;
    HANDLE thread = CreateThread(nullptr, 0, LensThreadProc, job, 0, nullptr);
    if (thread) {
        CloseHandle(thread);
    } else {
        g_helperThreads--;
        delete job;
    }
}

////////////////////////////////////////////////////////////////////////////////
// Text recognition with the OCR engine built into Windows 10 and later

namespace abi {

struct IAsyncInfo : IInspectable {
    virtual HRESULT STDMETHODCALLTYPE get_Id(UINT32* id) = 0;
    virtual HRESULT STDMETHODCALLTYPE get_Status(int* status) = 0;
    virtual HRESULT STDMETHODCALLTYPE get_ErrorCode(HRESULT* error) = 0;
    virtual HRESULT STDMETHODCALLTYPE Cancel() = 0;
    virtual HRESULT STDMETHODCALLTYPE Close() = 0;
};

struct IOcrLine : IInspectable {
    virtual HRESULT STDMETHODCALLTYPE get_Words(IInspectable** words) = 0;
    virtual HRESULT STDMETHODCALLTYPE get_Text(HSTRING* text) = 0;
};

struct IOcrLineList : IInspectable {  // IVectorView<OcrLine>
    virtual HRESULT STDMETHODCALLTYPE GetAt(UINT32 index, IOcrLine** line) = 0;
    virtual HRESULT STDMETHODCALLTYPE get_Size(UINT32* size) = 0;
};

struct IOcrResult : IInspectable {
    virtual HRESULT STDMETHODCALLTYPE get_Lines(IOcrLineList** lines) = 0;
    virtual HRESULT STDMETHODCALLTYPE get_TextAngle(IInspectable** angle) = 0;
    virtual HRESULT STDMETHODCALLTYPE get_Text(HSTRING* text) = 0;
};

struct IOcrOperation : IInspectable {  // IAsyncOperation<OcrResult>
    virtual HRESULT STDMETHODCALLTYPE put_Completed(IUnknown* handler) = 0;
    virtual HRESULT STDMETHODCALLTYPE get_Completed(IUnknown** handler) = 0;
    virtual HRESULT STDMETHODCALLTYPE GetResults(IOcrResult** result) = 0;
};

struct IOcrEngine : IInspectable {
    virtual HRESULT STDMETHODCALLTYPE RecognizeAsync(IInspectable* bitmap,
                                                     IOcrOperation** operation) = 0;
    virtual HRESULT STDMETHODCALLTYPE get_RecognizerLanguage(
        IInspectable** language) = 0;
};

struct IOcrEngineStatics : IInspectable {
    virtual HRESULT STDMETHODCALLTYPE get_MaxImageDimension(UINT32* value) = 0;
    virtual HRESULT STDMETHODCALLTYPE get_AvailableRecognizerLanguages(
        IInspectable** languages) = 0;
    virtual HRESULT STDMETHODCALLTYPE IsLanguageSupported(IInspectable* language,
                                                          boolean* supported) = 0;
    virtual HRESULT STDMETHODCALLTYPE TryCreateFromLanguage(IInspectable* language,
                                                            IOcrEngine** engine) = 0;
    virtual HRESULT STDMETHODCALLTYPE TryCreateFromUserProfileLanguages(
        IOcrEngine** engine) = 0;
};

struct ISoftwareBitmapStatics : IInspectable {
    virtual HRESULT STDMETHODCALLTYPE Copy(IInspectable* source,
                                           IInspectable** copy) = 0;
    virtual HRESULT STDMETHODCALLTYPE Convert(IInspectable* source,
                                              int format,
                                              IInspectable** converted) = 0;
    virtual HRESULT STDMETHODCALLTYPE ConvertWithAlpha(IInspectable* source,
                                                       int format,
                                                       int alpha,
                                                       IInspectable** converted) = 0;
    virtual HRESULT STDMETHODCALLTYPE CreateCopyFromBuffer(IInspectable* buffer,
                                                           int format,
                                                           INT32 width,
                                                           INT32 height,
                                                           IInspectable** bitmap) = 0;
};

struct ICryptographicBufferStatics : IInspectable {
    virtual HRESULT STDMETHODCALLTYPE Compare(IInspectable* a,
                                              IInspectable* b,
                                              boolean* equal) = 0;
    virtual HRESULT STDMETHODCALLTYPE GenerateRandom(UINT32 length,
                                                     IInspectable** buffer) = 0;
    virtual HRESULT STDMETHODCALLTYPE GenerateRandomNumber(UINT32* value) = 0;
    virtual HRESULT STDMETHODCALLTYPE CreateFromByteArray(UINT32 size,
                                                          BYTE* bytes,
                                                          IInspectable** buffer) = 0;
};

constexpr int kBitmapPixelFormatBgra8 = 87;
constexpr int kAsyncStarted = 0;
constexpr int kAsyncCompleted = 1;

}  // namespace abi

class WinRt {
  public:
    static const WinRt& Get() {
        static const WinRt instance;
        return instance;
    }

    bool Available() const {
        return getActivationFactory_ && createString_ && deleteString_ &&
               rawBuffer_;
    }

    template <typename T>
    bool Factory(PCWSTR className, const GUID& iid, ComPtr<T>& out) const {
        HSTRING name = nullptr;
        if (!Available() ||
            FAILED(createString_(className,
                                 static_cast<UINT32>(wcslen(className)), &name))) {
            return false;
        }
        const HRESULT hr = getActivationFactory_(name, iid, out.PutVoid());
        deleteString_(name);
        return SUCCEEDED(hr) && out;
    }

    std::wstring Take(HSTRING text) const {
        if (!text) {
            return {};
        }
        UINT32 length = 0;
        PCWSTR raw = rawBuffer_(text, &length);
        std::wstring result(raw ? raw : L"", raw ? length : 0);
        deleteString_(text);
        return result;
    }

  private:
    using RoGetActivationFactory_t = HRESULT(WINAPI*)(HSTRING, REFIID, void**);
    using WindowsCreateString_t = HRESULT(WINAPI*)(PCWSTR, UINT32, HSTRING*);
    using WindowsDeleteString_t = HRESULT(WINAPI*)(HSTRING);
    using WindowsGetStringRawBuffer_t = PCWSTR(WINAPI*)(HSTRING, UINT32*);

    WinRt() {
        if (!IsWindows10Build(10240)) {
            return;
        }
        getActivationFactory_ = GetProc<RoGetActivationFactory_t>(
            L"combase.dll", "RoGetActivationFactory");
        createString_ = GetProc<WindowsCreateString_t>(L"combase.dll",
                                                       "WindowsCreateString");
        deleteString_ = GetProc<WindowsDeleteString_t>(L"combase.dll",
                                                       "WindowsDeleteString");
        rawBuffer_ = GetProc<WindowsGetStringRawBuffer_t>(
            L"combase.dll", "WindowsGetStringRawBuffer");
    }

    RoGetActivationFactory_t getActivationFactory_ = nullptr;
    WindowsCreateString_t createString_ = nullptr;
    WindowsDeleteString_t deleteString_ = nullptr;
    WindowsGetStringRawBuffer_t rawBuffer_ = nullptr;
};

Image UpscaleImage2x(const Image& src) {
    Image dst;
    dst.width = src.width * 2;
    dst.height = src.height * 2;
    dst.pixels.resize(static_cast<size_t>(dst.width) * dst.height);
    auto channel = [](uint32_t p, int shift) {
        return static_cast<float>((p >> shift) & 0xFF);
    };
    for (int y = 0; y < dst.height; y++) {
        const float sy = std::max(0.0f, (y + 0.5f) * 0.5f - 0.5f);
        const int y0 = std::min(static_cast<int>(sy), src.height - 1);
        const int y1 = std::min(y0 + 1, src.height - 1);
        const float fy = sy - y0;
        const uint32_t* row0 = &src.pixels[static_cast<size_t>(y0) * src.width];
        const uint32_t* row1 = &src.pixels[static_cast<size_t>(y1) * src.width];
        for (int x = 0; x < dst.width; x++) {
            const float sx = std::max(0.0f, (x + 0.5f) * 0.5f - 0.5f);
            const int x0 = std::min(static_cast<int>(sx), src.width - 1);
            const int x1 = std::min(x0 + 1, src.width - 1);
            const float fx = sx - x0;
            uint32_t out = 0xFF000000;
            for (int shift = 0; shift < 24; shift += 8) {
                const float top = channel(row0[x0], shift) +
                                  (channel(row0[x1], shift) - channel(row0[x0], shift)) * fx;
                const float bottom = channel(row1[x0], shift) +
                                     (channel(row1[x1], shift) - channel(row1[x0], shift)) * fx;
                out |= static_cast<uint32_t>(top + (bottom - top) * fy + 0.5f) << shift;
            }
            dst.pixels[static_cast<size_t>(y) * dst.width + x] = out;
        }
    }
    return dst;
}

std::atomic<bool> g_stopping{false};

std::wstring RecognizeText(const Image& source) {
    const WinRt& winrt = WinRt::Get();
    ComPtr<abi::IOcrEngineStatics> ocrStatics;
    ComPtr<abi::ISoftwareBitmapStatics> bitmapStatics;
    ComPtr<abi::ICryptographicBufferStatics> bufferStatics;
    if (source.Empty() ||
        !winrt.Factory(L"Windows.Media.Ocr.OcrEngine", kIidIOcrEngineStatics,
                       ocrStatics) ||
        !winrt.Factory(L"Windows.Graphics.Imaging.SoftwareBitmap",
                       kIidISoftwareBitmapStatics, bitmapStatics) ||
        !winrt.Factory(L"Windows.Security.Cryptography.CryptographicBuffer",
                       kIidICryptographicBufferStatics, bufferStatics)) {
        return {};
    }
    ComPtr<abi::IOcrEngine> engine;
    if (FAILED(ocrStatics->TryCreateFromUserProfileLanguages(engine.Put())) ||
        !engine) {
        Wh_Log(L"No OCR language is installed");
        return {};
    }

    UINT32 maxDimension = 0;
    if (FAILED(ocrStatics->get_MaxImageDimension(&maxDimension)) ||
        !maxDimension) {
        maxDimension = 2600;
    }
    const int maxSide = static_cast<int>(maxDimension);
    const Image* image = &source;
    Image scaled;
    const int longest = std::max(source.width, source.height);
    if (longest * 2 <= maxSide &&
        static_cast<int64_t>(source.width) * source.height <= 1500 * 1000) {
        scaled = UpscaleImage2x(source);
        image = &scaled;
    } else if (longest > maxSide) {
        scaled = DownscaleImage(source, maxSide);
        image = &scaled;
    }
    if (image->width < 40 || image->height < 40) {
        Image padded;
        padded.width = std::max(image->width, 40);
        padded.height = std::max(image->height, 40);
        padded.pixels.assign(static_cast<size_t>(padded.width) * padded.height,
                             image->pixels[0]);
        for (int y = 0; y < image->height; y++) {
            std::copy_n(&image->pixels[static_cast<size_t>(y) * image->width],
                        image->width,
                        &padded.pixels[static_cast<size_t>(y) * padded.width]);
        }
        scaled = std::move(padded);
        image = &scaled;
    }

    ComPtr<IInspectable> buffer;
    ComPtr<IInspectable> bitmap;
    ComPtr<abi::IOcrOperation> operation;
    ComPtr<abi::IAsyncInfo> info;
    if (FAILED(bufferStatics->CreateFromByteArray(
            static_cast<UINT32>(image->pixels.size() * 4),
            reinterpret_cast<BYTE*>(const_cast<uint32_t*>(image->pixels.data())),
            buffer.Put())) ||
        FAILED(bitmapStatics->CreateCopyFromBuffer(
            buffer.Get(), abi::kBitmapPixelFormatBgra8, image->width,
            image->height, bitmap.Put())) ||
        FAILED(engine->RecognizeAsync(bitmap.Get(), operation.Put())) ||
        FAILED(operation->QueryInterface(kIidIAsyncInfo, info.PutVoid()))) {
        return {};
    }
    int status = abi::kAsyncStarted;
    const double deadline = NowMs() + 15000;
    while (SUCCEEDED(info->get_Status(&status)) &&
           status == abi::kAsyncStarted) {
        if (g_stopping || NowMs() > deadline) {
            info->Cancel();
            return {};
        }
        Sleep(10);
    }
    ComPtr<abi::IOcrResult> result;
    ComPtr<abi::IOcrLineList> lines;
    UINT32 count = 0;
    if (status != abi::kAsyncCompleted ||
        FAILED(operation->GetResults(result.Put())) || !result ||
        FAILED(result->get_Lines(lines.Put())) || !lines ||
        FAILED(lines->get_Size(&count))) {
        return {};
    }
    std::wstring text;
    for (UINT32 i = 0; i < count; i++) {
        ComPtr<abi::IOcrLine> line;
        HSTRING lineText = nullptr;
        if (SUCCEEDED(lines->GetAt(i, line.Put())) && line &&
            SUCCEEDED(line->get_Text(&lineText))) {
            const std::wstring value = winrt.Take(lineText);
            if (!value.empty()) {
                if (!text.empty()) {
                    text += L'\n';
                }
                text += value;
            }
        }
    }
    return text;
}

bool OcrAvailable() {
    return WinRt::Get().Available();
}

struct OcrJob {
    HWND notify;
    uint32_t attachmentId;
    std::shared_ptr<const Image> image;
};

struct OcrResultMessage {
    uint32_t attachmentId;
    std::wstring text;
};

DWORD WINAPI OcrThreadProc(LPVOID param) {
    std::unique_ptr<OcrJob> job(static_cast<OcrJob*>(param));
    const HRESULT coInit = CoInitializeEx(nullptr, COINIT_MULTITHREADED);
    const double start = NowMs();
    auto message = std::make_unique<OcrResultMessage>();
    message->attachmentId = job->attachmentId;
    message->text = RecognizeText(*job->image);
    Wh_Log(L"OCR: %d characters in %d ms",
           static_cast<int>(message->text.size()),
           static_cast<int>(NowMs() - start));
    if (SUCCEEDED(coInit)) {
        CoUninitialize();
    }
    if (!g_stopping) {
        PostOwned(job->notify, WM_APP_OCR, std::move(message));
    }
    g_helperThreads--;
    return 0;
}

bool StartOcr(HWND notify,
              uint32_t attachmentId,
              std::shared_ptr<const Image> image) {
    if (!OcrAvailable() || !image || image->Empty()) {
        return false;
    }
    auto* job = new OcrJob{notify, attachmentId, std::move(image)};
    g_helperThreads++;
    HANDLE thread = CreateThread(nullptr, 0, OcrThreadProc, job, 0, nullptr);
    if (thread) {
        CloseHandle(thread);
        return true;
    }
    g_helperThreads--;
    delete job;
    return false;
}

////////////////////////////////////////////////////////////////////////////////
// AI API client

#ifndef WINHTTP_ACCESS_TYPE_AUTOMATIC_PROXY
#define WINHTTP_ACCESS_TYPE_AUTOMATIC_PROXY 4
#endif
#ifndef WINHTTP_FLAG_SECURE_PROTOCOL_TLS1_3
#define WINHTTP_FLAG_SECURE_PROTOCOL_TLS1_3 0x00002000
#endif
#ifndef WINHTTP_OPTION_ENABLE_HTTP_PROTOCOL
#define WINHTTP_OPTION_ENABLE_HTTP_PROTOCOL 133
#endif
#ifndef WINHTTP_PROTOCOL_FLAG_HTTP2
#define WINHTTP_PROTOCOL_FLAG_HTTP2 0x1
#endif

enum class AiEvent { Chunk, Done, Error, Suggestions, Note };

struct AiMessage {
    uint32_t requestId = 0;
    AiEvent event = AiEvent::Done;
    bool partial = false;  // More suggestions are on the way.
    std::wstring text;
    std::vector<std::wstring> suggestions;
};

struct ChatTurn {
    bool fromUser;
    std::string text;  // UTF-8.
};

struct AiJob {
    uint32_t id = 0;
    bool suggestions = false;
    Provider provider = Provider::Gemini;
    std::wstring apiKey;
    std::wstring model;
    std::vector<std::wstring> fallbackModels;  // Tried when `model` isn't available.
    std::vector<std::shared_ptr<const Image>> images;
    std::string context;  // Text of the selection, UTF-8.
    std::string language;
    std::vector<ChatTurn> history;  // Ends with the new question.
    HWND notify = nullptr;
    std::atomic<bool> canceled{false};
    std::atomic<HINTERNET> request{nullptr};

    void Cancel() {
        canceled = true;
        if (HINTERNET handle = request.exchange(nullptr)) {
            WinHttpCloseHandle(handle);  // Aborts a blocking read.
        }
    }
};

PCWSTR TierModel(Provider provider, int tier) {
    static const PCWSTR kModels[3][3] = {
        {L"gemini-flash-lite-latest", L"gemini-3.6-flash", L"gemini-pro-latest"},
        {L"gpt-6-luna", L"gpt-6.1-terra", L"gpt-6.1-sol"},
        {L"claude-haiku-5-5", L"claude-sonnet-5-5", L"claude-opus-5-5"},
    };
    const int row = provider == Provider::OpenAi      ? 1
                    : provider == Provider::Anthropic ? 2
                                                      : 0;
    return kModels[row][std::clamp(tier, 0, 2)];
}

PCWSTR DefaultModel(Provider provider) {
    return TierModel(provider, 0);
}

int SelectedTier(const Settings& settings) {
    return settings.model == L"smart" ? 2 : settings.model == L"balanced" ? 1 : 0;
}

bool UsesModelId(const Settings& settings, Provider provider) {
    return provider == Provider::Gemini && settings.model.rfind(L"gemini", 0) == 0;
}

std::wstring SelectedModel(const Settings& settings, Provider provider) {
    return UsesModelId(settings, provider)
               ? settings.model
               : std::wstring(TierModel(provider, SelectedTier(settings)));
}

std::vector<std::wstring> FallbackModels(const Settings& settings, Provider provider) {
    std::vector<std::wstring> models;
    for (int tier = UsesModelId(settings, provider) ? 0 : SelectedTier(settings) - 1;
         tier >= 0; tier--) {
        models.push_back(TierModel(provider, tier));
    }
    return models;
}

std::wstring SanitizeModel(std::wstring model) {
    if (model.rfind(L"models/", 0) == 0) {
        model.erase(0, 7);
    }
    std::wstring result;
    for (wchar_t c : model) {
        if (iswalnum(c) || c == L'-' || c == L'.' || c == L'_') {
            result += c;
        }
    }
    return result;
}

struct ModelQuirks {
    std::wstring model;
    bool suggestions;
    int step;
};

std::mutex g_quirksMutex;
std::vector<ModelQuirks> g_quirks;

struct UnavailableModel {
    std::wstring model;
    double until;
};

std::vector<UnavailableModel> g_unavailable;

int LastStep(Provider provider) {
    return provider == Provider::OpenAi ? 2 : 3;
}

int FirstStep(Provider provider, const std::wstring& model, bool suggestions) {
    switch (provider) {
        case Provider::OpenAi:
            return suggestions &&
                           (model == L"gpt-6-luna" || model == L"gpt-6.1-terra")
                       ? 0
                       : 1;
        case Provider::Anthropic:
            if (!suggestions) {
                return 2;
            }
            return model == L"claude-haiku-5-5"    ? 0
                   : model == L"claude-sonnet-5-5" ? 1
                                                   : 2;
        case Provider::Gemini:
            break;
    }
    // Gemini 3.8 Flash and Pro reject "minimal". Latest aliases can also
    // move to a model with different thinking support, so prefer "low".
    const bool supportsMinimal =
        model == L"gemini-flash-lite-latest" ||
        model == L"gemini-3.5-flash-lite" ||
        model == L"gemini-3.1-flash-lite" ||
        model == L"gemini-3.6-flash" ||
        model == L"gemini-3-flash-preview";
    return suggestions && supportsMinimal ? 0 : 1;
}

int GetStep(Provider provider, const std::wstring& model, bool suggestions) {
    std::lock_guard<std::mutex> lock(g_quirksMutex);
    for (const ModelQuirks& quirks : g_quirks) {
        if (quirks.model == model && quirks.suggestions == suggestions) {
            return quirks.step;
        }
    }
    return FirstStep(provider, model, suggestions);
}

void SetStep(const std::wstring& model, bool suggestions, int step) {
    std::lock_guard<std::mutex> lock(g_quirksMutex);
    for (ModelQuirks& quirks : g_quirks) {
        if (quirks.model == model && quirks.suggestions == suggestions) {
            quirks.step = step;
            return;
        }
    }
    g_quirks.push_back({model, suggestions, step});
}

bool IsModelUnavailable(const std::wstring& model) {
    std::lock_guard<std::mutex> lock(g_quirksMutex);
    const double now = NowMs();
    for (const UnavailableModel& entry : g_unavailable) {
        if (entry.model == model && entry.until > now) {
            return true;
        }
    }
    return false;
}

void SetModelUnavailable(const std::wstring& model, double milliseconds) {
    if (milliseconds <= 0) {
        return;
    }
    std::lock_guard<std::mutex> lock(g_quirksMutex);
    for (UnavailableModel& entry : g_unavailable) {
        if (entry.model == model) {
            entry.until = NowMs() + milliseconds;
            return;
        }
    }
    g_unavailable.push_back({model, NowMs() + milliseconds});
}

void ClearUnavailableModels() {
    std::lock_guard<std::mutex> lock(g_quirksMutex);
    g_unavailable.clear();
}

std::string SystemInstruction(const AiJob& job) {
    std::string text;
    if (job.suggestions) {
        text =
            "You suggest what someone might want to ask or do with a part of "
            "their screen they just selected.";
    } else if (job.images.empty()) {
        text =
            "You are Magic Pointer, the " + ToUtf8(ProviderName(job.provider)) +
            " assistant built into the "
            "user's Windows PC. The user opened Magic Pointer and typed a "
            "question without selecting anything on their screen, so there is "
            "no image. Answer directly and concisely, in the language they "
            "write in. Prefer short paragraphs and bullet points, use bold "
            "sparingly and no tables. When asked to translate, reply with only "
            "the translation, written in the language they name, keeping its "
            "line breaks.";
    } else {
        text =
            "You are Magic Pointer, the " + ToUtf8(ProviderName(job.provider)) +
            " assistant built into the "
            "user's Windows PC. The user pointed at part of their screen and "
            "selected it; the attached image is exactly what they selected. "
            "Answer their request about it directly and concisely, in the "
            "language they write in. Prefer short paragraphs and bullet "
            "points, use bold sparingly and no tables. If the request is "
            "vague, briefly say what the selection shows and the most useful "
            "thing you can tell them about it. When asked to translate, "
            "translate all the text in the selection into the language they "
            "name and reply with only that translation, written in that "
            "language whatever language the request is in, keeping its line "
            "breaks.";
    }
    if (!job.context.empty()) {
        text += "\n\nText in the selection, from the app and from text "
                "recognition (it may contain recognition errors):\n\"\"\"\n";
        text += job.context;
        text += "\n\"\"\"";
    }
    return text;
}

constexpr char kSuggestionPrompt[] =
    "Suggest exactly three short, specific things I might want to ask or do "
    "with this selection next. Rules: each at most 45 characters; written "
    "from my point of view (use I or me); cover different intents such as "
    "understanding it, transforming it, getting ideas from it or acting on "
    "it; nothing generic like \"Tell me more\" or \"Explain this\"; no "
    "emojis; nothing that needs other software. Reply with only a JSON array "
    "of three strings.";

std::string SuggestionPrompt(const AiJob& job) {
    std::string prompt = kSuggestionPrompt;
    if (!job.language.empty()) {
        prompt += " Write them in " + job.language + ".";
    }
    return prompt;
}

std::string BuildGeminiBody(const AiJob& job,
                            const std::vector<std::string>& images,
                            int step) {
    std::string body = "{\"systemInstruction\":{\"parts\":[{\"text\":";
    AppendJsonString(body, SystemInstruction(job));
    body += "}]},\"contents\":[";

    auto appendImages = [&] {
        for (const std::string& image : images) {
            body += "{\"inlineData\":{\"mimeType\":\"image/jpeg\",\"data\":\"";
            body += image;
            body += "\"}},";
        }
    };

    if (job.suggestions) {
        body += "{\"role\":\"user\",\"parts\":[";
        appendImages();
        body += "{\"text\":";
        AppendJsonString(body, SuggestionPrompt(job));
        body += "}]}";
    } else {
        for (size_t i = 0; i < job.history.size(); i++) {
            const ChatTurn& turn = job.history[i];
            if (i > 0) {
                body += ',';
            }
            body += turn.fromUser ? "{\"role\":\"user\",\"parts\":["
                                  : "{\"role\":\"model\",\"parts\":[";
            if (i == 0) {
                appendImages();
            }
            body += "{\"text\":";
            AppendJsonString(body,
                             turn.text.empty() ? std::string(" ") : turn.text);
            body += "}]}";
        }
    }
    body += "],\"generationConfig\":{";
    switch (step) {
        case 0:
            body += "\"thinkingConfig\":{\"thinkingLevel\":\"minimal\"},";
            break;
        case 1:
            body += "\"thinkingConfig\":{\"thinkingLevel\":\"low\"},";
            break;
        case 2:
            // Positive budgets also work with models that cannot turn off
            // thinking; never retry a Gemini 3 request with a zero budget.
            body += "\"thinkingConfig\":{\"thinkingBudget\":1024},";
            break;
        default:
            break;
    }
    if (job.suggestions) {
        body += "\"responseMimeType\":\"application/json\",";
        // This limit includes thought tokens as well as the three chips.
        body += "\"maxOutputTokens\":2048,";
    }
    if (body.back() == ',') {
        body.pop_back();
    }
    body += "}}";
    return body;
}

std::string BuildOpenAiBody(const AiJob& job,
                            const std::wstring& model,
                            const std::vector<std::string>& images,
                            int step) {
    std::string body = "{\"model\":";
    AppendJsonString(body, ToUtf8(model));
    body += ",\"stream\":true,\"store\":false,\"instructions\":";
    AppendJsonString(body, SystemInstruction(job));
    body += ",\"input\":[";

    auto appendImages = [&] {
        for (const std::string& image : images) {
            body += "{\"type\":\"input_image\",\"image_url\":\"data:image/jpeg;base64,";
            body += image;
            body += "\"},";
        }
    };

    if (job.suggestions) {
        body += "{\"role\":\"user\",\"content\":[";
        appendImages();
        body += "{\"type\":\"input_text\",\"text\":";
        AppendJsonString(body, SuggestionPrompt(job));
        body += "}]}";
    } else {
        for (size_t i = 0; i < job.history.size(); i++) {
            const ChatTurn& turn = job.history[i];
            if (i > 0) {
                body += ',';
            }
            const std::string text = turn.text.empty() ? std::string(".") : turn.text;
            if (turn.fromUser) {
                body += "{\"role\":\"user\",\"content\":[";
                if (i == 0) {
                    appendImages();
                }
                body += "{\"type\":\"input_text\",\"text\":";
                AppendJsonString(body, text);
                body += "}]}";
            } else {
                body += "{\"role\":\"assistant\",\"content\":";
                AppendJsonString(body, text);
                body += '}';
            }
        }
    }
    body += ']';
    switch (step) {
        case 0:
            body += ",\"reasoning\":{\"effort\":\"none\"}";
            break;
        case 1:
            body += ",\"reasoning\":{\"effort\":\"low\"}";
            break;
        default:
            break;
    }
    if (job.suggestions) {
        body += ",\"max_output_tokens\":2048";
    }
    body += '}';
    return body;
}

std::string BuildAnthropicBody(const AiJob& job,
                               const std::wstring& model,
                               const std::vector<std::string>& images,
                               int step) {
    std::string body = "{\"model\":";
    AppendJsonString(body, ToUtf8(model));
    body += job.suggestions ? ",\"max_tokens\":2048" : ",\"max_tokens\":8192";
    body += ",\"stream\":true,\"system\":";
    AppendJsonString(body, SystemInstruction(job));
    body += ",\"messages\":[";

    auto appendImages = [&] {
        for (const std::string& image : images) {
            body += "{\"type\":\"image\",\"source\":{\"type\":\"base64\","
                    "\"media_type\":\"image/jpeg\",\"data\":\"";
            body += image;
            body += "\"}},";
        }
    };

    if (job.suggestions) {
        body += "{\"role\":\"user\",\"content\":[";
        appendImages();
        body += "{\"type\":\"text\",\"text\":";
        AppendJsonString(body, SuggestionPrompt(job));
        body += "}]}";
    } else {
        for (size_t i = 0; i < job.history.size(); i++) {
            const ChatTurn& turn = job.history[i];
            if (i > 0) {
                body += ',';
            }
            const std::string text = turn.text.empty() ? std::string(".") : turn.text;
            if (turn.fromUser) {
                body += "{\"role\":\"user\",\"content\":[";
                if (i == 0) {
                    appendImages();
                }
                body += "{\"type\":\"text\",\"text\":";
                AppendJsonString(body, text);
                body += "}]}";
            } else {
                body += "{\"role\":\"assistant\",\"content\":";
                AppendJsonString(body, text);
                body += '}';
            }
        }
    }
    body += ']';
    switch (step) {
        case 0:
            body += ",\"thinking\":{\"type\":\"disabled\"},"
                    "\"output_config\":{\"effort\":\"low\"}";
            break;
        case 1:
            body += ",\"thinking\":{\"type\":\"between_tools\"},"
                    "\"output_config\":{\"effort\":\"low\"}";
            break;
        case 2:
            body += ",\"output_config\":{\"effort\":\"low\"}";
            break;
        default:
            break;
    }
    body += '}';
    return body;
}

std::string BuildRequestBody(const AiJob& job,
                             const std::wstring& model,
                             const std::vector<std::string>& images,
                             int step) {
    switch (job.provider) {
        case Provider::OpenAi:
            return BuildOpenAiBody(job, model, images, step);
        case Provider::Anthropic:
            return BuildAnthropicBody(job, model, images, step);
        case Provider::Gemini:
            break;
    }
    return BuildGeminiBody(job, images, step);
}

void ExtractResponseText(const Json& root,
                         std::string& text,
                         std::string& finishReason) {
    if (const Json* candidates = root.Get("candidates")) {
        if (const Json* candidate = candidates->At(0)) {
            if (const Json* content = candidate->Get("content")) {
                if (const Json* parts = content->Get("parts")) {
                    for (const Json& part : parts->items) {
                        const Json* thought = part.Get("thought");
                        if (thought && thought->boolean) {
                            continue;
                        }
                        if (const Json* partText = part.Get("text")) {
                            text += partText->string;
                        }
                    }
                }
            }
            if (const Json* reason = candidate->Get("finishReason")) {
                finishReason = reason->string;
            }
        }
    }
    if (const Json* feedback = root.Get("promptFeedback")) {
        if (const Json* reason = feedback->Get("blockReason")) {
            finishReason = reason->string;
        }
    }
}

std::string ApiErrorMessage(const std::string& body) {
    Json root;
    if (ParseJson(body, root)) {
        if (const Json* error = root.Get("error")) {
            if (const Json* message = error->Get("message")) {
                return message->string;
            }
        }
        if (const Json* first = root.At(0)) {  // Streamed errors are arrays.
            if (const Json* error = first->Get("error")) {
                if (const Json* message = error->Get("message")) {
                    return message->string;
                }
            }
        }
    }
    return {};
}

std::string ApiErrorCode(const std::string& body) {
    Json root;
    if (ParseJson(body, root)) {
        if (const Json* error = root.Get("error")) {
            for (const char* key : {"code", "type"}) {
                if (const Json* value = error->Get(key)) {
                    if (value->IsString() && !value->string.empty()) {
                        return value->string;
                    }
                }
            }
        }
    }
    return {};
}

bool IsBillingError(const std::string& apiMessage, const std::string& apiCode) {
    return ContainsNoCase(apiCode, "quota") || ContainsNoCase(apiCode, "credit") ||
           ContainsNoCase(apiCode, "billing") || ContainsNoCase(apiCode, "spend_limit") ||
           ContainsNoCase(apiMessage, "credit balance") ||
           ContainsNoCase(apiMessage, "current quota");
}

bool IsInvalidKey(Provider provider, DWORD status, const std::string& apiMessage) {
    return provider == Provider::Gemini
               ? status == 400 && ContainsNoCase(apiMessage, "API key")
               : status == 401;
}

struct ModelTrouble {
    bool tryOther = false;
    double blockMs = 0;
};

ModelTrouble DiagnoseModel(Provider provider,
                           DWORD status,
                           bool timedOut,
                           const std::string& apiMessage,
                           const std::string& apiCode) {
    constexpr double kMinute = 60000.0;
    if (status == 0) {
        return timedOut ? ModelTrouble{true, 2 * kMinute} : ModelTrouble{};
    }
    if (IsInvalidKey(provider, status, apiMessage) || status == 401 || status == 402) {
        return {};
    }
    if (provider != Provider::Gemini && (status == 400 || status == 429) &&
        IsBillingError(apiMessage, apiCode)) {
        return {};
    }
    if (status == 404) {
        return {true, 5 * kMinute};
    }
    if (status == 403) {
        return ContainsNoCase(apiMessage, "model") || ContainsNoCase(apiCode, "model")
                   ? ModelTrouble{true, 5 * kMinute}
                   : ModelTrouble{};
    }
    if (status == 429) {
        return {true, provider == Provider::Gemini && ContainsNoCase(apiMessage, "limit: 0")
                          ? 5 * kMinute
                          : kMinute};
    }
    if (status == 400) {
        return {true, 0};
    }
    return status >= 500 ? ModelTrouble{true, 2 * kMinute} : ModelTrouble{};
}

std::wstring FriendlyError(Provider provider,
                           DWORD status,
                           const std::string& apiMessage,
                           const std::string& apiCode,
                           const std::wstring& model) {
    const std::wstring name = ProviderName(provider);
    if (IsInvalidKey(provider, status, apiMessage)) {
        return TrFormat(Str::ErrKeyInvalid, name);
    }
    if (status == 403) {
        return TrFormat(Str::ErrKeyForbidden, name);
    }
    if (status == 404) {
        return TrFormat(Str::ErrModelMissing, model);
    }
    if (provider != Provider::Gemini &&
        (status == 402 ||
         ((status == 400 || status == 429) && IsBillingError(apiMessage, apiCode)))) {
        return TrFormat(Str::ErrNoCredit, name);
    }
    if (status == 429) {
        if (provider == Provider::Gemini && ContainsNoCase(apiMessage, "limit: 0")) {
            return TrFormat(Str::ErrNoFreeQuota, model);
        }
        return TrFormat(Str::ErrRateLimit, name);
    }
    if (status >= 500) {
        return TrFormat(Str::ErrServer, name, std::to_wstring(status));
    }
    if (!apiMessage.empty()) {
        return FromUtf8(apiMessage);
    }
    return TrFormat(Str::ErrGeneric, name, std::to_wstring(status));
}

bool NeedsOtherTuning(Provider provider, DWORD status, const std::string& apiMessage) {
    if (status != 400) {
        return false;
    }
    switch (provider) {
        case Provider::OpenAi:
            return ContainsNoCase(apiMessage, "reasoning") ||
                   ContainsNoCase(apiMessage, "effort");
        case Provider::Anthropic:
            return ContainsNoCase(apiMessage, "thinking") ||
                   ContainsNoCase(apiMessage, "effort") ||
                   ContainsNoCase(apiMessage, "output_config");
        case Provider::Gemini:
            break;
    }
    return ContainsNoCase(apiMessage, "thinking") ||
           ContainsNoCase(apiMessage, "budget");
}

const Json* JsonPath(const Json& root, std::initializer_list<const char*> keys) {
    const Json* value = &root;
    for (const char* key : keys) {
        value = value ? value->Get(key) : nullptr;
    }
    return value;
}

std::string JsonText(const Json* value) {
    return value && value->IsString() ? value->string : std::string();
}

void ReadOpenAiEvent(const Json& root,
                     std::string& text,
                     std::string& finishReason,
                     std::string& streamError) {
    const std::string type = JsonText(root.Get("type"));
    if (type == "response.output_text.delta" || type == "response.refusal.delta") {
        text += JsonText(root.Get("delta"));
    } else if (type == "response.completed") {
        finishReason = "STOP";
    } else if (type == "response.incomplete") {
        const std::string reason =
            JsonText(JsonPath(root, {"response", "incomplete_details", "reason"}));
        finishReason = reason == "max_output_tokens" ? "MAX_TOKENS"
                       : reason.empty()              ? "INCOMPLETE"
                                                     : reason;
    } else if (type == "response.failed") {
        streamError = JsonText(JsonPath(root, {"response", "error", "message"}));
        if (streamError.empty()) {
            streamError = JsonText(JsonPath(root, {"response", "error", "code"}));
        }
        if (streamError.empty()) {
            streamError = ToUtf8(TrFormat(Str::ErrStreaming, ProviderName(Provider::OpenAi)));
        }
    } else if (type == "error") {
        streamError = JsonText(root.Get("message"));
        if (streamError.empty()) {
            streamError = ToUtf8(TrFormat(Str::ErrStreaming, ProviderName(Provider::OpenAi)));
        }
    }
}

void ReadAnthropicEvent(const Json& root,
                        std::string& text,
                        std::string& finishReason,
                        std::string& streamError) {
    const std::string type = JsonText(root.Get("type"));
    if (type == "content_block_delta") {
        const Json* delta = root.Get("delta");
        if (delta && JsonText(delta->Get("type")) == "text_delta") {
            text += JsonText(delta->Get("text"));
        }
    } else if (type == "message_delta") {
        const std::string reason = JsonText(JsonPath(root, {"delta", "stop_reason"}));
        if (!reason.empty()) {
            finishReason = reason == "end_turn" || reason == "stop_sequence" ? "STOP"
                           : reason == "max_tokens"                         ? "MAX_TOKENS"
                                                                            : reason;
        }
    } else if (type == "error") {
        streamError = JsonText(JsonPath(root, {"error", "message"}));
        if (streamError.empty()) {
            streamError = ToUtf8(TrFormat(Str::ErrStreaming, ProviderName(Provider::Anthropic)));
        }
    }
}

void ReadStreamEvent(Provider provider,
                     const Json& root,
                     std::string& text,
                     std::string& finishReason,
                     std::string& streamError) {
    switch (provider) {
        case Provider::OpenAi:
            ReadOpenAiEvent(root, text, finishReason, streamError);
            return;
        case Provider::Anthropic:
            ReadAnthropicEvent(root, text, finishReason, streamError);
            return;
        case Provider::Gemini:
            break;
    }
    if (const Json* error = root.Get("error")) {
        if (const Json* message = error->Get("message")) {
            streamError = message->string;
        }
        if (streamError.empty()) {
            streamError = ToUtf8(TrFormat(Str::ErrStreaming, ProviderName(provider)));
        }
        return;
    }
    ExtractResponseText(root, text, finishReason);
}

class SseParser {
  public:
    template <typename OnEvent>
    void Feed(const char* data, size_t size, OnEvent onEvent) {
        buffer_.append(data, size);
        for (;;) {
            size_t separator = std::string::npos;
            size_t separatorLength = 0;
            const size_t lf = buffer_.find("\n\n");
            const size_t crlf = buffer_.find("\r\n\r\n");
            if (lf != std::string::npos &&
                (crlf == std::string::npos || lf < crlf)) {
                separator = lf;
                separatorLength = 2;
            } else if (crlf != std::string::npos) {
                separator = crlf;
                separatorLength = 4;
            }
            if (separator == std::string::npos) {
                break;
            }
            Emit(buffer_.substr(0, separator), onEvent);
            buffer_.erase(0, separator + separatorLength);
        }
    }

    template <typename OnEvent>
    void Finish(OnEvent onEvent) {
        if (!buffer_.empty()) {
            Emit(buffer_, onEvent);
            buffer_.clear();
        }
    }

  private:
    template <typename OnEvent>
    static void Emit(const std::string& event, OnEvent onEvent) {
        std::string data;
        size_t start = 0;
        while (start < event.size()) {
            size_t end = event.find('\n', start);
            if (end == std::string::npos) {
                end = event.size();
            }
            std::string line = event.substr(start, end - start);
            if (!line.empty() && line.back() == '\r') {
                line.pop_back();
            }
            if (line.rfind("data:", 0) == 0) {
                if (!data.empty()) {
                    data += '\n';
                }
                data += line.substr(line.size() > 5 && line[5] == ' ' ? 6 : 5);
            }
            start = end + 1;
        }
        if (!data.empty()) {
            onEvent(data);
        }
    }

    std::string buffer_;
};

std::mutex g_sessionMutex;
HINTERNET g_session;

HINTERNET ApiSession() {
    std::lock_guard<std::mutex> lock(g_sessionMutex);
    if (g_session) {
        return g_session;
    }
    HINTERNET session = WinHttpOpen(
        L"MagicPointer/1.1 (Windhawk)",
        IsWindows81OrLater() ? WINHTTP_ACCESS_TYPE_AUTOMATIC_PROXY
                             : WINHTTP_ACCESS_TYPE_DEFAULT_PROXY,
        WINHTTP_NO_PROXY_NAME, WINHTTP_NO_PROXY_BYPASS, 0);
    if (!session) {
        session = WinHttpOpen(L"MagicPointer/1.1 (Windhawk)",
                              WINHTTP_ACCESS_TYPE_DEFAULT_PROXY,
                              WINHTTP_NO_PROXY_NAME, WINHTTP_NO_PROXY_BYPASS, 0);
    }
    if (!session) {
        return nullptr;
    }
    DWORD protocols = WINHTTP_FLAG_SECURE_PROTOCOL_TLS1_2 |
                      WINHTTP_FLAG_SECURE_PROTOCOL_TLS1_3;
    if (!WinHttpSetOption(session, WINHTTP_OPTION_SECURE_PROTOCOLS, &protocols,
                          sizeof(protocols))) {
        protocols = WINHTTP_FLAG_SECURE_PROTOCOL_TLS1_2;
        WinHttpSetOption(session, WINHTTP_OPTION_SECURE_PROTOCOLS, &protocols,
                         sizeof(protocols));
    }
    DWORD http2 = WINHTTP_PROTOCOL_FLAG_HTTP2;
    WinHttpSetOption(session, WINHTTP_OPTION_ENABLE_HTTP_PROTOCOL, &http2,
                     sizeof(http2));
    WinHttpSetTimeouts(session, 15000, 15000, 30000, 90000);
    g_session = session;
    return session;
}

void CloseApiSession() {
    std::lock_guard<std::mutex> lock(g_sessionMutex);
    if (g_session) {
        WinHttpCloseHandle(g_session);
        g_session = nullptr;
    }
}

struct HttpResult {
    DWORD status = 0;
    DWORD error = 0;
    bool awaitedResponse = false;
    std::string body;  // Only kept for error responses.
};

struct ApiEndpoint {
    PCWSTR host;
    std::wstring path;
    std::wstring headers;
};

ApiEndpoint EndpointFor(const AiJob& job, const std::wstring& model) {
    switch (job.provider) {
        case Provider::OpenAi:
            return {L"api.openai.com", L"/v1/responses",
                    L"Content-Type: application/json\r\n"
                    L"Authorization: Bearer " +
                        job.apiKey + L"\r\n"};
        case Provider::Anthropic:
            return {L"api.anthropic.com", L"/v1/messages",
                    L"Content-Type: application/json\r\n"
                    L"anthropic-version: 2023-06-01\r\n"
                    L"x-api-key: " +
                        job.apiKey + L"\r\n"};
        case Provider::Gemini:
            break;
    }
    return {L"generativelanguage.googleapis.com",
            L"/v1beta/models/" + model + L":streamGenerateContent?alt=sse",
            L"Content-Type: application/json\r\n"
            L"x-goog-api-key: " +
                job.apiKey + L"\r\n"};
}

template <typename OnData>
HttpResult SendToApi(const ApiEndpoint& endpoint,
                     const std::string& body,
                     std::atomic<bool>* canceled,
                     std::atomic<HINTERNET>* requestSlot,
                     DWORD firstByteTimeout,
                     DWORD receiveTimeout,
                     OnData onData) {
    HttpResult result;
    HINTERNET session = ApiSession();
    if (!session) {
        result.error = GetLastError();
        return result;
    }
    HINTERNET connection = WinHttpConnect(
        session, endpoint.host, INTERNET_DEFAULT_HTTPS_PORT, 0);
    HINTERNET request =
        connection
            ? WinHttpOpenRequest(connection, L"POST", endpoint.path.c_str(), nullptr,
                                 WINHTTP_NO_REFERER,
                                 WINHTTP_DEFAULT_ACCEPT_TYPES,
                                 WINHTTP_FLAG_SECURE)
            : nullptr;
    if (!request) {
        result.error = GetLastError();
        if (connection) {
            WinHttpCloseHandle(connection);
        }
        return result;
    }
    WinHttpSetTimeouts(request, 15000, 15000, 30000,
                       static_cast<int>(firstByteTimeout));

    if (requestSlot) {
        requestSlot->store(request);
        if (*canceled) {
            if (HINTERNET handle = requestSlot->exchange(nullptr)) {
                WinHttpCloseHandle(handle);
            }
        }
    }

    result.awaitedResponse =
        !(canceled && *canceled) &&
        WinHttpSendRequest(request, endpoint.headers.c_str(), static_cast<DWORD>(-1),
                           const_cast<char*>(body.data()), static_cast<DWORD>(body.size()),
                           static_cast<DWORD>(body.size()), 0);
    bool ok = result.awaitedResponse && WinHttpReceiveResponse(request, nullptr);
    if (ok) {
        WinHttpSetTimeouts(request, 15000, 15000, 30000,
                           static_cast<int>(receiveTimeout));
        DWORD status = 0;
        DWORD size = sizeof(status);
        ok = WinHttpQueryHeaders(
                 request,
                 WINHTTP_QUERY_STATUS_CODE | WINHTTP_QUERY_FLAG_NUMBER,
                 WINHTTP_HEADER_NAME_BY_INDEX, &status, &size,
                 WINHTTP_NO_HEADER_INDEX) != FALSE;
        result.status = status;
        char buffer[8192];
        while (ok) {
            DWORD available = 0;
            DWORD read = 0;
            if ((canceled && *canceled) ||
                !WinHttpQueryDataAvailable(request, &available) ||
                (available > 0 &&
                 !WinHttpReadData(request, buffer,
                                  std::min<DWORD>(available, sizeof(buffer)),
                                  &read))) {
                ok = false;
                break;
            }
            if (read == 0) {
                break;
            }
            if (status == 200) {
                onData(buffer, static_cast<size_t>(read));
            } else if (result.body.size() < 65536) {
                result.body.append(buffer, read);
            }
        }
    }
    if (!ok && !result.error) {
        result.error = GetLastError();
        if (!result.error) {
            result.error = ERROR_WINHTTP_CONNECTION_ERROR;
        }
    }

    if (requestSlot) {
        if (HINTERNET handle = requestSlot->exchange(nullptr)) {
            WinHttpCloseHandle(handle);
        }
    } else {
        WinHttpCloseHandle(request);
    }
    WinHttpCloseHandle(connection);
    return result;
}

void PostAiMessage(AiJob& job,
                       AiEvent event,
                       std::wstring text,
                       std::vector<std::wstring> suggestions = {},
                       bool partial = false) {
    if (job.canceled) {
        return;
    }
    auto message = std::make_unique<AiMessage>();
    message->requestId = job.id;
    message->event = event;
    message->partial = partial;
    message->text = std::move(text);
    message->suggestions = std::move(suggestions);
    PostOwned(job.notify, WM_APP_AI, std::move(message));
}

std::wstring CleanSuggestion(std::string item) {
    while (!item.empty() && (item.back() == ' ' || item.back() == ',' ||
                             item.back() == '"' || item.back() == '.')) {
        item.pop_back();
    }
    size_t start = 0;
    while (start < item.size() &&
           (item[start] == ' ' || item[start] == '"' || item[start] == '-' ||
            item[start] == '*' || item[start] == '[')) {
        start++;
    }
    size_t digits = start;
    while (digits < item.size() &&
           isdigit(static_cast<unsigned char>(item[digits]))) {
        digits++;
    }
    if (digits > start && digits + 1 < item.size() &&
        (item[digits] == '.' || item[digits] == ')') && item[digits + 1] == ' ') {
        start = digits + 2;
    }
    item.erase(0, start);
    std::wstring wide = Trim(FromUtf8(item));
    return wide.size() <= 80 ? wide : std::wstring();
}

std::vector<std::wstring> ParsePartialSuggestions(const std::string& text) {
    std::vector<std::wstring> result;
    size_t i = text.find('[');
    if (i == std::string::npos) {
        return result;
    }
    for (i++; i < text.size() && result.size() < 3; i++) {
        if (text[i] == ']') {
            break;
        }
        if (text[i] != '"') {
            continue;
        }
        size_t end = i + 1;
        while (end < text.size() && text[end] != '"') {
            end += text[end] == '\\' ? 2 : 1;
        }
        if (end >= text.size()) {
            break;
        }
        Json value;
        if (ParseJson(text.substr(i, end - i + 1), value) && value.IsString()) {
            std::wstring item = CleanSuggestion(value.string);
            if (!item.empty()) {
                result.push_back(std::move(item));
            }
        }
        i = end;
    }
    return result;
}

std::vector<std::wstring> ParseSuggestions(const std::string& text) {
    std::vector<std::wstring> result;
    auto add = [&](const std::string& item) {
        std::wstring wide = CleanSuggestion(item);
        if (!wide.empty() && result.size() < 3) {
            result.push_back(std::move(wide));
        }
    };

    std::string json = text;
    const size_t open = json.find('[');
    const size_t close = json.rfind(']');
    if (open != std::string::npos && close != std::string::npos && close > open) {
        json = json.substr(open, close - open + 1);
    }
    Json root;
    if (ParseJson(json, root) && root.type == Json::Type::Array) {
        for (const Json& item : root.items) {
            if (item.IsString()) {
                add(item.string);
            }
        }
        return result;
    }
    size_t start = 0;
    while (start < text.size()) {
        size_t end = text.find('\n', start);
        if (end == std::string::npos) {
            end = text.size();
        }
        add(text.substr(start, end - start));
        start = end + 1;
    }
    return result;
}

constexpr int kSuggestionImageSize = 768;
constexpr int kAnswerImageSize = 1536;

DWORD WINAPI AiThreadProc(LPVOID param) {
    std::unique_ptr<std::shared_ptr<AiJob>> holder(
        static_cast<std::shared_ptr<AiJob>*>(param));
    AiJob& job = **holder;

    std::vector<std::string> images;
    const HRESULT coInit = CoInitializeEx(nullptr, COINIT_MULTITHREADED);
    for (const auto& image : job.images) {
        std::vector<uint8_t> jpeg;
        const Image scaled = DownscaleImage(
            *image, job.suggestions ? kSuggestionImageSize : kAnswerImageSize);
        if (!job.canceled &&
            EncodeImage(scaled, jpeg, true, job.suggestions ? 0.8f : 0.9f)) {
            images.push_back(Base64Encode(jpeg.data(), jpeg.size()));
        }
    }
    if (SUCCEEDED(coInit)) {
        CoUninitialize();
    }

    const std::wstring name = ProviderName(job.provider);
    std::vector<std::wstring> models;
    auto addModel = [&](const std::wstring& candidate) {
        const std::wstring clean = SanitizeModel(candidate);
        if (!clean.empty() && std::find(models.begin(), models.end(), clean) == models.end()) {
            models.push_back(clean);
        }
    };
    addModel(job.model);
    for (const std::wstring& candidate : job.fallbackModels) {
        addModel(candidate);
    }
    if (models.empty()) {
        models.push_back(DefaultModel(job.provider));
    }
    auto skipUnavailable = [&](size_t from) {
        while (from + 1 < models.size() && IsModelUnavailable(models[from])) {
            from++;
        }
        return from;
    };
    bool noted = false;
    auto noteFallback = [&] {
        if (!noted && !job.suggestions) {
            noted = true;
            PostAiMessage(job, AiEvent::Note, Tr(Str::ModelBusy));
        }
    };
    size_t index = skipUnavailable(0);
    if (index > 0) {
        noteFallback();
    }
    std::wstring model = models[index];
    int step = GetStep(job.provider, model, job.suggestions);
    auto switchModel = [&](double blockMs) {
        SetModelUnavailable(model, blockMs);
        index = skipUnavailable(index + 1);
        model = models[index];
        step = GetStep(job.provider, model, job.suggestions);
        noteFallback();
    };

    // At most four thinking settings for each of up to three models.
    constexpr int kMaxAttempts = 12;
    for (int attempt = 0; attempt < kMaxAttempts && !job.canceled; attempt++) {
        const ApiEndpoint endpoint = EndpointFor(job, model);
        const std::string body = BuildRequestBody(job, model, images, step);
        std::string answer;
        std::string finishReason;
        std::string streamError;
        bool invalidEvent = false;
        size_t shownSuggestions = 0;
        const double start = NowMs();
        double firstText = -1;
        SseParser sse;
        auto onEvent = [&](const std::string& data) {
            if (data == "[DONE]") {
                return;
            }
            Json root;
            if (!ParseJson(data, root) || root.type != Json::Type::Object) {
                const std::string error = ApiErrorMessage(data);
                if (!error.empty()) {
                    streamError = error;
                }
                invalidEvent = true;
                return;
            }
            std::string text;
            ReadStreamEvent(job.provider, root, text, finishReason, streamError);
            if (text.empty()) {
                return;
            }
            if (firstText < 0) {
                firstText = NowMs() - start;
            }
            answer += text;
            if (!job.suggestions) {
                PostAiMessage(job, AiEvent::Chunk, FromUtf8(text));
                return;
            }
            std::vector<std::wstring> partial = ParsePartialSuggestions(answer);
            if (partial.size() > shownSuggestions && partial.size() < 3) {
                shownSuggestions = partial.size();
                PostAiMessage(job, AiEvent::Suggestions, L"",
                              std::move(partial), true);
            }
        };

        const DWORD receiveTimeout = job.suggestions ? 20000 : 90000;
        HttpResult result = SendToApi(
            endpoint, body, &job.canceled, &job.request,
            index + 1 < models.size() ? std::min<DWORD>(receiveTimeout, 30000)
                                      : receiveTimeout,
            receiveTimeout,
            [&](const char* data, size_t size) { sse.Feed(data, size, onEvent); });
        if (job.canceled) {
            break;
        }

        if (result.status == 200) {
            SetStep(model, job.suggestions, step);
            sse.Finish(onEvent);
            Wh_Log(L"%s %s: first text after %d ms, done after %d ms",
                   model.c_str(), job.suggestions ? L"suggestions" : L"answer",
                   static_cast<int>(firstText), static_cast<int>(NowMs() - start));
            if (!job.suggestions && answer.empty() && !streamError.empty() && !result.error &&
                attempt + 1 < kMaxAttempts && index + 1 < models.size()) {
                Wh_Log(L"%s failed before answering (%S), trying %s", model.c_str(),
                       streamError.c_str(), models[index + 1].c_str());
                switchModel(60000);
                continue;
            }
            std::wstring note;
            if (result.error) {
                note = TrFormat(answer.empty() ? Str::ErrNoConnection
                                               : Str::ErrInterrupted,
                                name, std::to_wstring(result.error));
            } else if (!streamError.empty()) {
                note = answer.empty() ? FromUtf8(streamError)
                                      : TrFormat(Str::ErrInterruptedBy, name,
                                                 FromUtf8(streamError));
            } else if (invalidEvent) {
                note = TrFormat(Str::ErrUnreadable, name);
            } else if (finishReason == "MAX_TOKENS") {
                note = TrFormat(Str::ErrOutputLimit, name);
            } else if (!finishReason.empty() && finishReason != "STOP") {
                note = TrFormat(Str::ErrStoppedBecause, name, FromUtf8(finishReason));
            } else if (finishReason.empty()) {
                note = TrFormat(Str::ErrUnconfirmed, name);
            } else if (answer.empty()) {
                note = TrFormat(Str::ErrNoAnswer, name);
            }
            if (job.suggestions) {
                PostAiMessage(job, AiEvent::Suggestions, note,
                              note.empty() ? ParseSuggestions(answer)
                                           : ParsePartialSuggestions(answer));
                break;
            }
            PostAiMessage(job,
                          note.empty() ? AiEvent::Done : AiEvent::Error,
                          note);
            break;
        }

        const std::string apiMessage = ApiErrorMessage(result.body);
        const std::string apiCode = ApiErrorCode(result.body);
        if (attempt + 1 < kMaxAttempts && step < LastStep(job.provider) &&
            NeedsOtherTuning(job.provider, result.status, apiMessage)) {
            step++;
            Wh_Log(L"%s: trying another thinking setting (%d)", model.c_str(), step);
            continue;
        }
        const bool timedOut = result.status == 0 && result.awaitedResponse &&
                              result.error == ERROR_WINHTTP_TIMEOUT;
        const ModelTrouble trouble =
            DiagnoseModel(job.provider, result.status, timedOut, apiMessage, apiCode);
        if (attempt + 1 < kMaxAttempts && index + 1 < models.size() && trouble.tryOther &&
            (!job.suggestions || result.status == 404)) {
            Wh_Log(L"%s isn't available (%u %u), trying %s", model.c_str(), result.status,
                   result.error, models[index + 1].c_str());
            switchModel(trouble.blockMs);
            continue;
        }

        std::wstring error;
        if (timedOut) {
            error = TrFormat(Str::ErrTimeout, name);
        } else if (result.status == 0) {
            error = TrFormat(Str::ErrCouldntReach, name, std::to_wstring(result.error));
        } else {
            error = FriendlyError(job.provider, result.status, apiMessage, apiCode, model);
        }
        Wh_Log(L"%s request failed: %u %u %S", name.c_str(), result.status,
               result.error, apiMessage.c_str());
        PostAiMessage(job,
                      job.suggestions ? AiEvent::Suggestions
                                      : AiEvent::Error,
                      error);
        break;
    }

    g_helperThreads--;
    return 0;
}

std::shared_ptr<AiJob> StartAiJob(std::shared_ptr<AiJob> job) {
    auto* param = new std::shared_ptr<AiJob>(job);
    g_helperThreads++;
    HANDLE thread = CreateThread(nullptr, 0, AiThreadProc, param, 0, nullptr);
    if (!thread) {
        g_helperThreads--;
        delete param;
        return nullptr;
    }
    CloseHandle(thread);
    return job;
}

////////////////////////////////////////////////////////////////////////////////
// The card that opens next to a selection

HWND g_messageWindow;
uint32_t g_lastRequestId;
uint32_t g_lastAttachmentId;

std::shared_ptr<AiJob> NewAiJob(bool suggestions) {
    Provider provider;
    if (!ActiveProvider(g_settings, provider)) {
        return nullptr;
    }
    auto job = std::make_shared<AiJob>();
    job->id = ++g_lastRequestId;
    job->suggestions = suggestions;
    job->provider = provider;
    job->apiKey = g_settings.apiKey;
    if (suggestions) {
        job->model = DefaultModel(provider);
        job->fallbackModels.push_back(SelectedModel(g_settings, provider));
    } else {
        job->model = SelectedModel(g_settings, provider);
        job->fallbackModels = FallbackModels(g_settings, provider);
    }
    job->notify = g_messageWindow;
    return job;
}

void BeginAddSelection();
void OnCardClosed();
void RequestTick();

struct Attachment {
    std::shared_ptr<const Image> image;  // As captured.
    Image thumb;                         // Downscaled for the card.
    std::wstring text;     // The element's own text, when one was selected.
    std::wstring ocrText;  // Text recognized in the image.
    uint32_t id = 0;
    bool ocrPending = false;
};

struct Palette {
    bool dark;
    Color text, secondary, tertiary, divider, controlFill, controlFillHover,
        controlFillFocus, controlBorder, controlStrong, subtleHover,
        subtlePressed, accent, onAccent, selection, error, userBubble, codeBg,
        tooltipBg, tooltipBorder;
};

Palette MakePalette(bool dark) {
    Palette p{};
    p.dark = dark;
    const Color ink = dark ? Rgb(205, 214, 244) : kBlack;  // Mocha text
    p.text = WithAlpha(ink, dark ? 1.0f : 0.894f);
    p.secondary = dark ? Rgb(186, 194, 222) : WithAlpha(ink, 0.606f);  // subtext1
    p.tertiary = dark ? Rgb(166, 173, 200) : WithAlpha(ink, 0.446f);   // subtext0
    p.divider = WithAlpha(ink, dark ? 0.0837f : 0.0803f);
    p.controlFill = dark ? Rgb(49, 50, 68, 0.70f) : WithAlpha(kWhite, 0.70f);
    p.controlFillHover =
        dark ? Rgb(69, 71, 90, 0.75f) : Rgb(249, 249, 249, 0.50f);
    p.controlFillFocus = dark ? Rgb(24, 24, 37, 0.80f) : kWhite;
    p.controlBorder = dark ? Rgb(108, 112, 134, 0.4f) : WithAlpha(ink, 0.0578f);
    p.controlStrong = WithAlpha(ink, dark ? 0.544f : 0.446f);
    p.subtleHover = WithAlpha(ink, dark ? 0.0605f : 0.0373f);
    p.subtlePressed = WithAlpha(ink, dark ? 0.0419f : 0.0241f);
    p.accent = g_glow.Accent(dark);
    const float luminance =
        p.accent.r * 0.2126f + p.accent.g * 0.7152f + p.accent.b * 0.0722f;
    p.onAccent = luminance > 0.45f ? Rgb(17, 17, 27) : kWhite;
    p.selection = WithAlpha(p.accent, 0.38f);
    p.error = dark ? Rgb(243, 139, 168) : Rgb(196, 43, 28);
    p.userBubble = WithAlpha(p.accent, dark ? 0.22f : 0.14f);
    p.codeBg = dark ? Rgb(17, 17, 27, 0.55f) : WithAlpha(kBlack, 0.045f);
    p.tooltipBg = dark ? Rgb(30, 30, 46, 0.98f) : Rgb(249, 249, 249, 0.98f);
    p.tooltipBorder = dark ? Rgb(108, 112, 134, 0.4f) : WithAlpha(kBlack, 0.10f);
    return p;
}

std::wstring WindowsLanguageName() {
    WCHAR locale[LOCALE_NAME_MAX_LENGTH]{};
    if (!LCIDToLocaleName(MAKELCID(GetUserDefaultUILanguage(), SORT_DEFAULT),
                          locale, ARRAYSIZE(locale), 0)) {
        return L"English";
    }
    if (_wcsnicmp(locale, L"zh", 2) == 0) {  // Chinese comes in two scripts.
        const bool traditional = wcsstr(locale, L"TW") || wcsstr(locale, L"HK") ||
                                 wcsstr(locale, L"MO") || wcsstr(locale, L"Hant");
        return traditional ? L"Chinese (Traditional)" : L"Chinese (Simplified)";
    }
    WCHAR name[80]{};
    return GetLocaleInfoEx(locale, LOCALE_SENGLISHLANGUAGENAME, name,
                           ARRAYSIZE(name)) > 0
               ? std::wstring(name)
               : std::wstring(L"English");
}

std::wstring TranslationLanguage() {
    if (!g_settings.translateTo.empty() && g_settings.translateTo != L"auto") {
        return g_settings.translateTo;
    }
    const LanguageInfo* language = CurrentLanguage();
    return g_languageChosen && language ? std::wstring(language->english)
                                        : WindowsLanguageName();
}

std::wstring TranslationLanguageName() {
    const std::wstring language = TranslationLanguage();
    if (!UiIsEnglish()) {
        if (const LanguageInfo* info = FindLanguageByEnglishName(language)) {
            return info->native;
        }
    }
    return language;
}

std::wstring TranslatePrompt(const std::wstring& language) {
    return L"Translate all the text in this selection into " + language +
           L". Reply with only the translation in " + language +
           L", keeping its line breaks. Don't describe the picture or explain "
           L"anything.";
}

struct CardTurn {
    bool fromUser = false;
    std::wstring text;
    bool streaming = false;
    bool error = false;
    std::wstring errorText = {};  // Status after a preserved partial answer.
};

enum class ChipAction { Ask, AskInBrowser, Lens, CopyImage, CopyText };

struct Chip {
    std::wstring label;
    ChipAction action;
};

struct TextBlock {
    enum class Kind { Paragraph, Heading, Bullet, Code };
    Kind kind;
    std::wstring bullet;
    std::wstring text;
};

std::wstring StripInlineMarkdown(const std::wstring& line) {
    std::wstring out;
    out.reserve(line.size());
    for (size_t i = 0; i < line.size(); i++) {
        const wchar_t c = line[i];
        if ((c == L'*' || c == L'_') && i + 1 < line.size() && line[i + 1] == c) {
            i++;
            continue;
        }
        if (c == L'`') {
            continue;
        }
        if (c == L']' && i + 1 < line.size() && line[i + 1] == L'(') {
            const size_t close = line.find(L')', i + 2);
            const size_t open = out.rfind(L'[');
            if (close != std::wstring::npos && open != std::wstring::npos) {
                out.erase(open, 1);
                i = close;
                continue;
            }
        }
        out += c;
    }
    return out;
}

std::vector<TextBlock> ParseMarkdown(const std::wstring& text) {
    std::vector<TextBlock> blocks;
    bool inCode = false;
    std::wstring code;
    size_t start = 0;
    for (;;) {
        size_t end = text.find(L'\n', start);
        const bool last = end == std::wstring::npos;
        if (last) {
            end = text.size();
        }
        std::wstring line = text.substr(start, end - start);
        start = end + 1;
        if (!line.empty() && line.back() == L'\r') {
            line.pop_back();
        }
        const std::wstring trimmed = Trim(line);

        if (trimmed.rfind(L"```", 0) == 0) {
            if (inCode) {
                if (!code.empty() && code.back() == L'\n') {
                    code.pop_back();
                }
                blocks.push_back({TextBlock::Kind::Code, L"", code});
                code.clear();
            }
            inCode = !inCode;
        } else if (inCode) {
            code += line + L"\n";
        } else if (trimmed.empty()) {
            // Blank lines only separate blocks.
        } else if (trimmed[0] == L'#') {
            size_t level = 0;
            while (level < trimmed.size() && trimmed[level] == L'#') {
                level++;
            }
            blocks.push_back({TextBlock::Kind::Heading, L"",
                              StripInlineMarkdown(Trim(trimmed.substr(level)))});
        } else if (trimmed.size() > 2 &&
                   (trimmed[0] == L'-' || trimmed[0] == L'*' ||
                    trimmed[0] == L'\x2022') &&
                   trimmed[1] == L' ') {
            blocks.push_back({TextBlock::Kind::Bullet, L"\x2022",
                              StripInlineMarkdown(Trim(trimmed.substr(2)))});
        } else {
            size_t digits = 0;
            while (digits < trimmed.size() && iswdigit(trimmed[digits])) {
                digits++;
            }
            if (digits > 0 && digits < 4 && digits + 1 < trimmed.size() &&
                (trimmed[digits] == L'.' || trimmed[digits] == L')') &&
                trimmed[digits + 1] == L' ') {
                blocks.push_back(
                    {TextBlock::Kind::Bullet, trimmed.substr(0, digits + 1),
                     StripInlineMarkdown(Trim(trimmed.substr(digits + 2)))});
            } else {
                std::wstring paragraph = trimmed;
                if (paragraph.rfind(L"> ", 0) == 0) {
                    paragraph.erase(0, 2);
                }
                blocks.push_back({TextBlock::Kind::Paragraph, L"",
                                  StripInlineMarkdown(paragraph)});
            }
        }
        if (last) {
            break;
        }
    }
    if (inCode && !code.empty()) {
        if (code.back() == L'\n') {
            code.pop_back();
        }
        blocks.push_back({TextBlock::Kind::Code, L"", code});
    }
    return blocks;
}

class AskCard {
  public:
    bool Create() { return panel_.Create(true, false, kCardWindowClass, this); }

    void Destroy() {
        Close();
        panel_.Destroy();
        chrome_.Reset();
        surface_.Reset();
        convo_.Reset();
        underlay_.Reset();
    }

    bool Begin(const RECT& selection, double now) {
        Close();
        if (!Create()) {
            return false;
        }
        open_ = true;
        suspended_ = false;
        dragged_ = false;
        selection_ = selection;
        placed_ = false;
        openTime_ = now;
        scale_ = DpiScaleAt(RectCenter(selection));
        Restyle();
        return true;
    }

    void Reveal() {
        panel_.Show(true);
        SetForegroundWindow(panel_.Hwnd());
        SetFocus(panel_.Hwnd());
    }

    void Open(Attachment attachment, const RECT& selection, double now) {
        if (!Begin(selection, now)) {
            return;
        }
        Attach(std::move(attachment));
        ResetChips();
        StartSuggestions(now);
        Update(now);
        Reveal();
    }

    bool OpenTyped(const RECT& anchor, const std::wstring& text, double now) {
        if (!Begin(anchor, now)) {
            return false;
        }
        ResetChips();
        InsertText(text);
        Update(now);
        Reveal();
        return GetForegroundWindow() == panel_.Hwnd();
    }

    void AppendTyped(const std::wstring& text, double now) {
        if (!open_ || text.empty()) {
            return;
        }
        InsertText(text);
        caretStart_ = now;
        caretOn_ = true;
        Update(now);
    }

    void AddAttachment(Attachment attachment, double now) {
        if (!open_) {
            return;
        }
        Attach(std::move(attachment));
        ResetChips();
        StartSuggestions(now);
        Resume(now);
    }

    void Suspend() {
        if (open_ && !suspended_) {
            suspended_ = true;
            panel_.Hide();
        }
    }

    void Resume(double now, bool activate = true) {
        if (open_ && suspended_) {
            suspended_ = false;
            openTime_ = now;
            Update(now);
            panel_.Show(activate);
            if (activate) {
                SetForegroundWindow(panel_.Hwnd());
                SetFocus(panel_.Hwnd());
            }
        }
    }

    void Close() {
        if (!open_) {
            return;
        }
        CancelChat();
        CancelSuggestions();
        if (browserJob_) {
            browserJob_->canceled = true;
            browserJob_.reset();
        }
        open_ = false;
        suspended_ = false;
        if (GetCapture() == panel_.Hwnd()) {
            ReleaseCapture();
        }
        panel_.Hide();
        attachments_.clear();
        turns_.clear();
        chips_.clear();
        convoItems_.clear();
        answerLines_.clear();
        answerText_.clear();
        answerAnchor_ = answerCaret_ = 0;
        answerFocused_ = selectingAnswer_ = false;
        input_.clear();
        caret_ = anchor_ = 0;
        inputScroll_ = 0;
        scroll_ = 0;
        status_.clear();
        hover_ = pressed_ = kHitNone;
        OnCardClosed();
    }

    bool IsOpen() const { return open_; }
    bool CanAddMore() const {
        return open_ && turns_.empty() && attachments_.size() < 3;
    }
    bool IsWaiting() const {
        return chipsLoading_ || (!turns_.empty() && turns_.back().streaming &&
                                 turns_.back().text.empty());
    }
    HWND Hwnd() const { return panel_.Hwnd(); }
    HWND UnderlayHwnd() const { return panel_.UnderlayHwnd(); }

    void OnSettingsChanged(double now) {
        if (!open_) {
            return;
        }
        Restyle();
        if (turns_.empty() && !chipsLoading_) {
            ResetChips();
        }
        Update(now);
    }

    double Tick(double now) {
        if (!open_ || suspended_) {
            return 1e9;
        }
        double next = 1e9;
        bool render = false;

        if (now - openTime_ < kAppearMs + 20) {
            render = true;
            next = 0;
        }
        if (!status_.empty()) {
            if (now >= statusUntil_) {
                status_.clear();
                Update(now);
            } else {
                next = std::min(next, statusUntil_ - now);
            }
        }
        if (focused_ && !answerFocused_) {
            const double blink = std::max<double>(GetCaretBlinkTime(), 200);
            const double phase = fmod(now - caretStart_, blink * 2);
            const bool on = phase < blink;
            if (on != caretOn_) {
                caretOn_ = on;
                render = true;
            }
            next = std::min(next, blink - fmod(phase, blink) + 1);
        }
        if (chipsLoading_) {
            const double waited = now - suggestionsStart_;
            if ((chips_.empty() && waited > kSuggestionsPatienceMs) ||
                waited > kSuggestionsLimitMs) {
                Wh_Log(L"Suggestions took too long");
                CancelSuggestions();
                if (chips_.empty()) {
                    ResetChips();
                }
                Update(now);
            }
        }
        if (IsWaiting() || HasPendingOcr() ||
            (!turns_.empty() && turns_.back().streaming)) {
            render = true;
            next = std::min(next, 33.0);
        }
        panel_.SetUnderlayAlpha(static_cast<BYTE>(
            EaseOutCubic((now - openTime_) / kAppearMs) * GlowBreath(now) * 255.0f + 0.5f));
        next = std::min(next, 1000.0 / 60.0);
        if (selectingAnswer_ && (answerDragPoint_.y < convoRect_.top ||
                                answerDragPoint_.y >= convoRect_.bottom)) {
            ScrollBy(answerDragPoint_.y < convoRect_.top ? -SI(8) : SI(8));
            answerCaret_ = AnswerIndexAt(answerDragPoint_);
            render = true;
        }
        if (hover_ != kHitNone && hover_ <= kHitAdd && !tooltipShown_) {
            const double wait = kTooltipDelayMs - (now - hoverStart_);
            if (wait <= 0) {
                tooltipShown_ = true;
                render = true;
            } else {
                next = std::min(next, wait);
            }
        }
        if (render) {
            Present(now);
        }
        return next;
    }

    void OnAiMessage(std::unique_ptr<AiMessage> message, double now) {
        if (!open_) {
            return;
        }
        if (message->requestId == chatId_ && chatId_ && !turns_.empty()) {
            CardTurn& turn = turns_.back();
            switch (message->event) {
                case AiEvent::Chunk:
                    turn.text += message->text;
                    break;
                case AiEvent::Done:
                    turn.streaming = false;
                    chatJob_.reset();
                    break;
                case AiEvent::Error:
                    turn.streaming = false;
                    turn.error = true;
                    if (turn.text.empty()) {
                        turn.text = message->text;
                    } else {
                        turn.errorText = message->text;
                    }
                    chatJob_.reset();
                    break;
                case AiEvent::Note:
                    SetStatus(message->text, now);
                    break;
                case AiEvent::Suggestions:
                    break;
            }
            convoDirty_ = true;
            Update(now);
        } else if (message->requestId == suggestionsId_ && suggestionsId_ &&
                   message->event == AiEvent::Suggestions) {
            if (turns_.empty()) {
                if (!message->suggestions.empty()) {
                    chips_.clear();
                    for (const std::wstring& suggestion : message->suggestions) {
                        chips_.push_back({suggestion, ChipAction::Ask});
                    }
                } else if (!message->partial) {
                    ResetChips();  // Nothing came back: the usual questions.
                }
            }
            if (!message->partial) {
                chipsLoading_ = false;
                suggestionsJob_.reset();
                suggestionsId_ = 0;
            }
            Update(now);
        }
    }

    void OnBrowserHandoff(std::unique_ptr<BrowserHandoffMessage> message, double now) {
        if (!open_ || !browserJob_ || message->id != browserJob_->id) return;
        browserJob_.reset();
        if (message->pasted) {
            Close();
        } else {
            SetStatus(message->status, now);
            Resume(now, false);  // Keep focus in Gemini or its upload dialog.
            Update(now);
        }
    }

    void OnOcrResult(uint32_t attachmentId, std::wstring text, double now) {
        bool found = false;
        for (Attachment& attachment : attachments_) {
            if (attachment.id == attachmentId) {
                attachment.ocrPending = false;
                attachment.ocrText = Trim(text);
                found = true;
            }
        }
        if (!found || !open_) {
            return;
        }
        if (turns_.empty() && !chipsLoading_ && !HasAiKey()) {
            ResetChips();  // Offers to copy the text.
        }
        Update(now);
    }

    static LRESULT CALLBACK WndProc(HWND hwnd,
                                    UINT message,
                                    WPARAM wParam,
                                    LPARAM lParam) {
        if (message == WM_NCCREATE) {
            auto* create = reinterpret_cast<CREATESTRUCTW*>(lParam);
            SetWindowLongPtrW(hwnd, GWLP_USERDATA,
                              reinterpret_cast<LONG_PTR>(create->lpCreateParams));
        }
        auto* card =
            reinterpret_cast<AskCard*>(GetWindowLongPtrW(hwnd, GWLP_USERDATA));
        if (card) {
            LRESULT result = 0;
            if (card->HandleMessage(hwnd, message, wParam, lParam, result)) {
                return result;
            }
        }
        return DefWindowProcW(hwnd, message, wParam, lParam);
    }

  private:
    static constexpr double kAppearMs = 220.0;
    static constexpr double kTooltipDelayMs = 450.0;
    static constexpr double kSuggestionsPatienceMs = 8000.0;
    static constexpr double kSuggestionsLimitMs = 15000.0;

    enum Hit {
        kHitNone = 0,
        kHitClose,
        kHitCopy,
        kHitCopyText,
        kHitLens,
        kHitGemini,
        kHitTranslate,
        kHitAdd,
        kHitSend,
        kHitInput,
        kHitConvo,
        kHitChip = 100,        // + chip index.
        kHitCopyAnswer = 200,  // + turn index.
    };

    struct HitRect {
        RECT rect;
        int id;
    };

    struct PanelKey {
        int width = 0;
        int height = 0;
        bool dark = false;
        Backdrop material = Backdrop::None;
        int style = 0;
        int scale = 0;
        bool operator==(const PanelKey&) const = default;
    };

    struct ConvoItem {
        enum class Kind { UserBubble, Text, Thinking, CopyButton, Sparkle };
        Kind kind;
        RECT rect;  // In conversation coordinates.
        RECT textRect;
        std::wstring text;
        std::wstring bullet;
        HFONT font;
        Color color;
        int turn;
        bool code;
    };

    struct AnswerLine {
        RECT rect;  // Conversation coordinates, independent of scrolling.
        size_t start;
        size_t length;
        std::vector<int> extents;
        HFONT font;
        Color color;
        int turn;
    };

    float S(float v) const { return v * scale_; }
    int SI(float v) const { return static_cast<int>(lroundf(v * scale_)); }

    HFONT BodyFont() { return g_fonts.Get(SI(14), FW_NORMAL); }
    HFONT HeadingFont() { return g_fonts.Get(SI(15), FW_SEMIBOLD); }
    HFONT SmallFont() { return g_fonts.Get(SI(12), FW_NORMAL); }
    HFONT CodeFont() { return g_fonts.Get(SI(13), FW_NORMAL, true); }
    HFONT InputFont() { return g_fonts.Get(SI(14), FW_NORMAL); }
    HFONT ChipFont() { return g_fonts.Get(SI(14), FW_NORMAL); }

    void Restyle() {
        palette_ = MakePalette(UseDarkTheme());
        panel_.Configure(palette_.dark);
        chromeKey_ = {};
        underlayKey_ = {};
        convoDirty_ = true;
    }

    void Attach(Attachment attachment) {
        attachment.id = ++g_lastAttachmentId;
        attachment.ocrPending =
            g_settings.ocr && StartOcr(g_messageWindow, attachment.id, attachment.image);
        attachments_.push_back(std::move(attachment));
    }

    bool HasPendingOcr() const {
        for (const Attachment& attachment : attachments_) {
            if (attachment.ocrPending) {
                return true;
            }
        }
        return false;
    }

    ////////////////////////////////////////////////////////////////////////
    // Actions

    void SetStatus(const std::wstring& text, double now) {
        status_ = text;
        statusUntil_ = now + 4500;
    }

    const Attachment* MainAttachment() const {
        return attachments_.empty() ? nullptr : &attachments_.front();
    }

    std::wstring CopyableText() const {
        std::wstring text;
        for (const Attachment& attachment : attachments_) {
            const std::wstring& part =
                attachment.text.empty() ? attachment.ocrText : attachment.text;
            if (!part.empty()) {
                if (!text.empty()) {
                    text += L"\n\n";
                }
                text += part;
            }
        }
        return text;
    }

    std::wstring ContextText() const {
        std::wstring text;
        auto add = [&](const std::wstring& part) {
            if (part.empty() || text.find(part) != std::wstring::npos) {
                return;
            }
            if (!text.empty()) {
                text += L"\n\n";
            }
            text += part;
        };
        for (const Attachment& attachment : attachments_) {
            add(attachment.text);
            add(attachment.ocrText);
        }
        if (text.size() > 8000) {
            text.resize(8000);
        }
        return text;
    }

    void CopyImage(double now) {
        if (const Attachment* a = MainAttachment()) {
            SetStatus(CopyImageToClipboard(panel_.Hwnd(), *a->image)
                          ? Tr(Str::ImageCopied)
                          : Tr(Str::ImageCopyFailed),
                      now);
        }
    }

    void CopyText(double now) {
        const std::wstring text = CopyableText();
        if (text.empty()) {
            SetStatus(HasPendingOcr() ? Tr(Str::ReadingText)
                                      : Tr(Str::NoTextFound),
                      now);
            return;
        }
        SetStatus(CopyTextToClipboard(panel_.Hwnd(), text)
                      ? Tr(Str::TextCopied)
                      : Tr(Str::TextCopyFailed),
                  now);
    }

    void OpenLens(double now) {
        if (const Attachment* a = MainAttachment()) {
            CopyImageToClipboard(panel_.Hwnd(), *a->image);
            SearchWithLens(a->image, SelectedBrowser());
            SetStatus(Tr(Str::OpeningLens), now);
        }
    }

    std::wstring BrowserQuestion() const {
        const std::wstring typed = Trim(input_);
        if (!typed.empty()) {
            return typed;
        }
        for (size_t i = turns_.size(); i-- > 0;) {
            if (turns_[i].fromUser) {
                return Trim(turns_[i].text);
            }
        }
        return {};
    }

    void AskInBrowser(double now, const std::wstring& prompt) {
        const Attachment* first = MainAttachment();
        if (first && !CopyImageToClipboard(panel_.Hwnd(), *first->image)) {
            SetStatus(Tr(Str::ImageCopyRetry), now);
            return;
        }
        if (browserJob_) browserJob_->canceled = true;
        auto job = std::make_shared<BrowserHandoffJob>();
        job->id = ++g_lastRequestId;
        job->notify = g_messageWindow;
        job->clipboardSequence = GetClipboardSequenceNumber();
        job->prompt = prompt;
        for (const Attachment& attachment : attachments_) {
            job->images.push_back(attachment.image);
        }
        job->browser = SelectedBrowser();
        browserJob_ = job;
        CancelSuggestions();
        const bool several = attachments_.size() > 1;
        if (StartBrowserHandoff(job)) {
            SetStatus(Tr(!first ? Str::OpeningGeminiText
                         : several ? Str::OpeningGeminiMany
                                   : Str::OpeningGeminiOne),
                      now);
            Suspend();  // Let the browser receive focus and the paste.
        } else {
            browserJob_.reset();
            OpenInBrowser(L"https://gemini.google.com/app", job->browser);
            if (first) {
                SetStatus(Tr(Str::ClickBoxToAttach), now);
            }
        }
    }

    void ResetChips() {
        chips_.clear();
        if (attachments_.empty()) {
            return;
        }
        if (!HasAiKey()) {
            chips_.push_back({Tr(Str::AskInGemini), ChipAction::AskInBrowser});
            chips_.push_back({Tr(Str::SearchWithLens), ChipAction::Lens});
            if (!CopyableText().empty()) {
                chips_.push_back({Tr(Str::CopyText), ChipAction::CopyText});
            }
            chips_.push_back({Tr(Str::CopyImage), ChipAction::CopyImage});
        } else {
            chips_.push_back({Tr(Str::WhatIsThis), ChipAction::Ask});
            chips_.push_back({Tr(Str::ExplainThis), ChipAction::Ask});
            chips_.push_back({Tr(Str::SummarizeThis), ChipAction::Ask});
        }
    }

    void StartSuggestions(double now) {
        CancelSuggestions();
        if (!g_settings.suggestions || attachments_.empty()) {
            return;
        }
        auto job = NewAiJob(true);
        if (!job) {
            return;
        }
        for (const Attachment& attachment : attachments_) {
            job->images.push_back(attachment.image);
        }
        job->context = ToUtf8(ContextText());
        if (!UiIsEnglish()) {
            job->language = ToUtf8(CurrentLanguage()->english);
        }
        suggestionsJob_ = StartAiJob(job);
        if (suggestionsJob_) {
            suggestionsId_ = job->id;
            suggestionsStart_ = now;
            chipsLoading_ = true;
            chips_.clear();
        }
    }

    void CancelSuggestions() {
        if (suggestionsJob_) {
            suggestionsJob_->Cancel();
            suggestionsJob_.reset();
        }
        suggestionsId_ = 0;
        chipsLoading_ = false;
    }

    void CancelChat() {
        if (chatJob_) {
            chatJob_->Cancel();
            chatJob_.reset();
        }
        chatId_ = 0;
        if (!turns_.empty() && turns_.back().streaming) {
            turns_.back().streaming = false;
            turns_.back().error = true;
            if (turns_.back().text.empty()) {
                turns_.back().text = Tr(Str::Stopped);
            } else {
                turns_.back().errorText = Tr(Str::StoppedEarly);
            }
            convoDirty_ = true;
        }
    }

    void Submit(std::wstring question, double now, bool keepInput = false,
                std::wstring prompt = {}) {
        question = Trim(question);
        if (question.empty() || !open_) {
            return;
        }
        if (prompt.empty()) {
            prompt = question;
        }
        auto job = NewAiJob(false);
        if (!job) {
            AskInBrowser(now, prompt);
            Update(now);
            return;
        }
        CancelChat();
        CancelSuggestions();
        chips_.clear();

        for (const Attachment& attachment : attachments_) {
            job->images.push_back(attachment.image);
        }
        job->context = ToUtf8(ContextText());
        for (size_t i = 0; i + 1 < turns_.size(); i += 2) {
            if (turns_[i].fromUser && !turns_[i + 1].error) {
                job->history.push_back({true, ToUtf8(turns_[i].text)});
                job->history.push_back({false, ToUtf8(turns_[i + 1].text)});
            }
        }
        job->history.push_back({true, ToUtf8(prompt)});

        turns_.push_back({true, question, false, false});
        turns_.push_back({false, L"", true, false});
        if (!keepInput) {
            input_.clear();
            caret_ = anchor_ = 0;
            inputScroll_ = 0;
        }
        stickToBottom_ = true;
        convoDirty_ = true;

        chatJob_ = StartAiJob(job);
        if (chatJob_) {
            chatId_ = job->id;
        } else {
            turns_.back().streaming = false;
            turns_.back().error = true;
            turns_.back().text = Tr(Str::RequestFailed);
        }
        Update(now);
    }

    void Translate(double now) {
        Submit(TrFormat(Str::TranslateTo, TranslationLanguageName()), now, true,
               TranslatePrompt(TranslationLanguage()));
    }

    void Activate(int hit, double now) {
        if (hit >= kHitCopyAnswer) {
            const size_t turn = static_cast<size_t>(hit - kHitCopyAnswer);
            if (turn < turns_.size()) {
                SetStatus(CopyTextToClipboard(panel_.Hwnd(), turns_[turn].text)
                              ? Tr(Str::AnswerCopied)
                              : Tr(Str::AnswerCopyFailed),
                          now);
            }
        } else if (hit >= kHitChip) {
            const size_t index = static_cast<size_t>(hit - kHitChip);
            if (index >= chips_.size()) {
                return;
            }
            const Chip chip = chips_[index];
            switch (chip.action) {
                case ChipAction::Ask:
                    Submit(chip.label, now);
                    return;
                case ChipAction::AskInBrowser:
                    AskInBrowser(now, BrowserQuestion());
                    break;
                case ChipAction::Lens:
                    OpenLens(now);
                    break;
                case ChipAction::CopyImage:
                    CopyImage(now);
                    break;
                case ChipAction::CopyText:
                    CopyText(now);
                    break;
            }
        } else {
            switch (hit) {
                case kHitClose:
                    Close();
                    return;
                case kHitCopy:
                    CopyImage(now);
                    break;
                case kHitCopyText:
                    CopyText(now);
                    break;
                case kHitLens:
                    OpenLens(now);
                    break;
                case kHitGemini:
                    AskInBrowser(now, BrowserQuestion());
                    break;
                case kHitTranslate:
                    Translate(now);
                    return;
                case kHitAdd:
                    if (CanAddMore()) {
                        BeginAddSelection();
                    }
                    return;
                case kHitSend:
                    Submit(input_, now);
                    return;
                default:
                    return;
            }
        }
        Update(now);
    }

    ////////////////////////////////////////////////////////////////////////
    // Text input

    const std::vector<int>& InputExtents() {
        if (extentsText_ != input_ || extentsFont_ != InputFont()) {
            extentsText_ = input_;
            extentsFont_ = InputFont();
            text_.Extents(extentsFont_, input_, extents_);
        }
        return extents_;
    }

    int CaretX(int index) {
        const std::vector<int>& extents = InputExtents();
        index = std::clamp(index, 0, static_cast<int>(extents.size()));
        return index == 0 ? 0 : extents[index - 1];
    }

    int PrevChar(int i) const {
        if (i <= 0) {
            return 0;
        }
        i--;
        if (i > 0 && IS_LOW_SURROGATE(input_[i]) &&
            IS_HIGH_SURROGATE(input_[i - 1])) {
            i--;
        }
        return i;
    }

    int NextChar(int i) const {
        const int size = static_cast<int>(input_.size());
        if (i >= size) {
            return size;
        }
        i++;
        if (i < size && IS_LOW_SURROGATE(input_[i]) &&
            IS_HIGH_SURROGATE(input_[i - 1])) {
            i++;
        }
        return i;
    }

    int PrevWord(int i) const {
        while (i > 0 && iswspace(input_[i - 1])) {
            i--;
        }
        while (i > 0 && !iswspace(input_[i - 1])) {
            i--;
        }
        return i;
    }

    int NextWord(int i) const {
        const int size = static_cast<int>(input_.size());
        while (i < size && !iswspace(input_[i])) {
            i++;
        }
        while (i < size && iswspace(input_[i])) {
            i++;
        }
        return i;
    }

    void DeleteSelection() {
        if (anchor_ != caret_) {
            const int a = std::min(anchor_, caret_);
            const int b = std::max(anchor_, caret_);
            input_.erase(a, b - a);
            caret_ = anchor_ = a;
        }
    }

    void InsertText(std::wstring text) {
        for (wchar_t& c : text) {
            if (c == L'\r' || c == L'\n' || c == L'\t') {
                c = L' ';
            }
        }
        DeleteSelection();
        const size_t room = input_.size() < 4000 ? 4000 - input_.size() : 0;
        if (text.size() > room) {
            text.resize(room);
        }
        input_.insert(caret_, text);
        caret_ += static_cast<int>(text.size());
        anchor_ = caret_;
    }

    void MoveCaret(int position, bool extend) {
        caret_ = std::clamp(position, 0, static_cast<int>(input_.size()));
        if (!extend) {
            anchor_ = caret_;
        }
    }

    int InputIndexAt(int x) {
        const std::vector<int>& extents = InputExtents();
        const int offset = x - (inputText_.left - inputScroll_);
        int previous = 0;
        for (int i = 0; i < static_cast<int>(extents.size()); i = NextChar(i)) {
            const int next = NextChar(i);
            const int width = extents[next - 1];
            if (offset < (previous + width) / 2) {
                return i;
            }
            previous = width;
        }
        return static_cast<int>(input_.size());
    }

    bool HandleKey(WPARAM key, double now) {
        const bool ctrl = GetKeyState(VK_CONTROL) & 0x8000;
        const bool shift = GetKeyState(VK_SHIFT) & 0x8000;
        if (answerFocused_) {
            if (ctrl && key == 'A') {
                answerAnchor_ = 0;
                answerCaret_ = answerText_.size();
                Present(now);
                return true;
            }
            if (ctrl && (key == 'C' || key == 'X')) {
                CopyAnswerSelection(now);
                return true;
            }
            if (key == VK_ESCAPE) {
                Close();
                return true;
            }
            if (key == VK_UP || key == VK_DOWN || key == VK_PRIOR || key == VK_NEXT) {
                const int step = key == VK_UP || key == VK_DOWN ? SI(48)
                    : std::max(SI(48), static_cast<int>(convoRect_.bottom - convoRect_.top) - SI(40));
                ScrollBy(key == VK_UP || key == VK_PRIOR ? -step : step);
                Present(now);
                return true;
            }
            if (key == VK_LEFT || key == VK_RIGHT || key == VK_HOME || key == VK_END) {
                const size_t size = answerText_.size();
                if (!shift && answerAnchor_ != answerCaret_ && (key == VK_LEFT || key == VK_RIGHT)) {
                    answerCaret_ = key == VK_LEFT ? std::min(answerAnchor_, answerCaret_)
                                                  : std::max(answerAnchor_, answerCaret_);
                } else if (key == VK_HOME) {
                    answerCaret_ = 0;
                } else if (key == VK_END) {
                    answerCaret_ = size;
                } else if (key == VK_LEFT && answerCaret_ > 0) {
                    answerCaret_--;
                    if (answerCaret_ > 0 && IS_LOW_SURROGATE(answerText_[answerCaret_])) {
                        answerCaret_--;
                    }
                } else if (key == VK_RIGHT && answerCaret_ < size) {
                    answerCaret_++;
                    if (answerCaret_ < size && IS_LOW_SURROGATE(answerText_[answerCaret_])) {
                        answerCaret_++;
                    }
                }
                if (!shift) {
                    answerAnchor_ = answerCaret_;
                }
                Present(now);
                return true;
            }
            if (key == VK_RETURN || (ctrl && key == 'V')) {
                ClearAnswerSelection();
            } else {
                return false;
            }
        }
        switch (key) {
            case VK_ESCAPE:
                Close();
                return true;
            case VK_RETURN:
                Submit(input_, now);
                return true;
            case VK_LEFT:
                if (!shift && anchor_ != caret_) {
                    MoveCaret(std::min(anchor_, caret_), false);
                } else {
                    MoveCaret(ctrl ? PrevWord(caret_) : PrevChar(caret_), shift);
                }
                break;
            case VK_RIGHT:
                if (!shift && anchor_ != caret_) {
                    MoveCaret(std::max(anchor_, caret_), false);
                } else {
                    MoveCaret(ctrl ? NextWord(caret_) : NextChar(caret_), shift);
                }
                break;
            case VK_HOME:
                MoveCaret(0, shift);
                break;
            case VK_END:
                MoveCaret(static_cast<int>(input_.size()), shift);
                break;
            case VK_BACK:
                if (anchor_ == caret_) {
                    anchor_ = ctrl ? PrevWord(caret_) : PrevChar(caret_);
                }
                DeleteSelection();
                break;
            case VK_DELETE:
                if (anchor_ == caret_) {
                    anchor_ = ctrl ? NextWord(caret_) : NextChar(caret_);
                }
                DeleteSelection();
                break;
            case VK_UP:
            case VK_DOWN:
            case VK_PRIOR:
            case VK_NEXT: {
                const int page = std::max(SI(48), static_cast<int>(convoRect_.bottom - convoRect_.top) - SI(40));
                const int step = (key == VK_UP || key == VK_DOWN) ? SI(48) : page;
                ScrollBy((key == VK_UP || key == VK_PRIOR) ? -step : step);
                Present(now);
                return true;
            }
            case 'A':
                if (!ctrl) {
                    return false;
                }
                anchor_ = 0;
                caret_ = static_cast<int>(input_.size());
                break;
            case 'C':
            case 'X':
                if (!ctrl) {
                    return false;
                }
                if (anchor_ != caret_) {
                    const int a = std::min(anchor_, caret_);
                    const int b = std::max(anchor_, caret_);
                    CopyTextToClipboard(panel_.Hwnd(), input_.substr(a, b - a));
                    if (key == 'X') {
                        DeleteSelection();
                    }
                }
                break;
            case 'V':
                if (!ctrl) {
                    return false;
                }
                InsertText(ReadClipboardText(panel_.Hwnd()));
                break;
            default:
                return false;
        }
        caretStart_ = now;
        caretOn_ = true;
        Update(now);
        return true;
    }

    void ScrollBy(int delta) {
        const int viewport = convoRect_.bottom - convoRect_.top;
        const int maxScroll = std::max(0, contentHeight_ - viewport);
        scroll_ = std::clamp(scroll_ + delta, 0, maxScroll);
        stickToBottom_ = !answerFocused_ && scroll_ >= maxScroll;
        UpdateCopyHits();
    }

    void ClearAnswerSelection() {
        answerFocused_ = selectingAnswer_ = false;
        answerAnchor_ = answerCaret_ = 0;
    }

    void CopyAnswerSelection(double now) {
        const size_t a = std::min(answerAnchor_, answerCaret_);
        const size_t b = std::max(answerAnchor_, answerCaret_);
        if (a < b && b <= answerText_.size()) {
            SetStatus(CopyTextToClipboard(panel_.Hwnd(), answerText_.substr(a, b - a))
                          ? Tr(Str::TextCopied) : Tr(Str::TextCopyFailed), now);
            Update(now);
        }
    }

    size_t AnswerIndexAt(POINT pt) const {
        if (answerLines_.empty()) {
            return 0;
        }
        const int y = pt.y - convoRect_.top + scroll_;
        const int x = pt.x - convoRect_.left;
        const AnswerLine* nearest = &answerLines_.front();
        int best = INT_MAX;
        for (const AnswerLine& line : answerLines_) {
            const int gap = y < line.rect.top ? line.rect.top - y
                           : y >= line.rect.bottom ? y - line.rect.bottom + 1 : 0;
            if (gap < best) {
                nearest = &line;
                best = gap;
            }
        }
        int previous = 0;
        for (size_t i = 0; i < nearest->length;) {
            size_t next = i + 1;
            if (next < nearest->length && IS_HIGH_SURROGATE(answerText_[nearest->start + i]) &&
                IS_LOW_SURROGATE(answerText_[nearest->start + next])) {
                next++;
            }
            const int end = nearest->extents[next - 1];
            if (x - nearest->rect.left < (previous + end) / 2) {
                return nearest->start + i;
            }
            previous = end;
            i = next;
        }
        return nearest->start + nearest->length;
    }

    void SelectAnswerAt(POINT pt, bool extend, bool word) {
        answerFocused_ = true;
        stickToBottom_ = false;
        answerCaret_ = AnswerIndexAt(pt);
        if (!extend) {
            answerAnchor_ = answerCaret_;
        }
        if (word && !answerText_.empty()) {
            size_t start = std::min(answerCaret_, answerText_.size() - 1);
            size_t end = start;
            while (start > 0 && !iswspace(answerText_[start - 1])) {
                start--;
            }
            while (end < answerText_.size() && !iswspace(answerText_[end])) {
                end++;
            }
            answerAnchor_ = start;
            answerCaret_ = end;
        }
    }


    ////////////////////////////////////////////////////////////////////////
    // Layout

    void LayoutConversation() {
        convoItems_.clear();
        const int width = convoWidth_;
        const int textLeft = SI(26);
        int y = 0;
        for (size_t t = 0; t < turns_.size(); t++) {
            const CardTurn& turn = turns_[t];
            const int turnIndex = static_cast<int>(t);
            if (turn.fromUser) {
                HFONT font = BodyFont();
                const int maxWidth = static_cast<int>(width * 0.82f) - SI(24);
                const SIZE size =
                    text_.Measure(font, turn.text, maxWidth, DT_WORDBREAK);
                const int bubbleWidth =
                    std::min(maxWidth, static_cast<int>(size.cx) + SI(3)) + SI(24);
                const int bubbleHeight = size.cy + SI(16);
                convoItems_.push_back(
                    {ConvoItem::Kind::UserBubble,
                     {width - bubbleWidth, y, width, y + bubbleHeight},
                     {width - bubbleWidth + SI(12), y + SI(8), width - SI(12),
                      y + SI(8) + size.cy},
                     turn.text, L"", font, palette_.text, turnIndex, false});
                y += bubbleHeight + SI(14);
                continue;
            }

            convoItems_.push_back({ConvoItem::Kind::Sparkle,
                                   {0, y + SI(1), SI(18), y + SI(19)},
                                   {}, L"", L"", nullptr, palette_.text,
                                   turnIndex, false});
            if (turn.streaming && turn.text.empty()) {
                const RECT rc{textLeft, y - SI(1), width, y + SI(21)};
                convoItems_.push_back({ConvoItem::Kind::Thinking, rc, rc,
                                       Tr(Str::Thinking), L"", BodyFont(),
                                       palette_.secondary, turnIndex, false});
                y += SI(20) + SI(14);
                continue;
            }
            if (turn.error && turn.errorText.empty()) {
                HFONT font = BodyFont();
                const auto lines = text_.Wrap(font, turn.text, width - textLeft);
                const SIZE size{width - textLeft, static_cast<LONG>(lines.size()) *
                    text_.Measure(font, L"Mg", width - textLeft, DT_SINGLELINE).cy};
                const RECT rc{textLeft, y, width, y + size.cy};
                convoItems_.push_back({ConvoItem::Kind::Text, rc, rc, turn.text,
                                       L"", font, palette_.error, turnIndex,
                                       false});
                y += size.cy + SI(14);
                continue;
            }

            bool first = true;
            for (const TextBlock& block : ParseMarkdown(turn.text)) {
                if (block.text.empty()) {
                    continue;
                }
                if (!first) {
                    y += block.kind == TextBlock::Kind::Heading ? SI(10) : SI(6);
                }
                first = false;
                const bool code = block.kind == TextBlock::Kind::Code;
                HFONT font = block.kind == TextBlock::Kind::Heading ? HeadingFont()
                             : code                                  ? CodeFont()
                                                                     : BodyFont();
                int left = textLeft;
                int right = width;
                if (block.kind == TextBlock::Kind::Bullet) {
                    left += SI(block.bullet.size() > 1 ? 24 : 16);
                } else if (code) {
                    left += SI(10);
                    right -= SI(10);
                }
                std::wstring display;
                int column = 0;
                for (wchar_t c : block.text) {
                    if (c == L'\t') {
                        const int spaces = 4 - column % 4;
                        display.append(spaces, L' ');
                        column += spaces;
                    } else {
                        display += c;
                        column = c == L'\n' ? 0 : column + 1;
                    }
                }
                const auto lines = text_.Wrap(font, display, right - left);
                const SIZE size{right - left, static_cast<LONG>(lines.size()) *
                    text_.Measure(font, L"Mg", right - left, DT_SINGLELINE).cy};
                ConvoItem item{ConvoItem::Kind::Text,
                               {textLeft, y, width, y + size.cy},
                               {left, y, right, y + size.cy},
                               display, block.bullet, font, palette_.text,
                               turnIndex, code};
                if (code) {
                    item.rect.bottom += SI(16);
                    OffsetRect(&item.textRect, 0, SI(8));
                    y += SI(16);
                }
                convoItems_.push_back(item);
                y += size.cy;
            }
            y += SI(8);
            if (turn.error && !turn.errorText.empty()) {
                HFONT font = BodyFont();
                const auto lines = text_.Wrap(font, turn.errorText, width - textLeft);
                const int height = static_cast<int>(lines.size()) *
                    text_.Measure(font, L"Mg", width - textLeft, DT_SINGLELINE).cy;
                const RECT rc{textLeft, y, width, y + height};
                convoItems_.push_back({ConvoItem::Kind::Text, rc, rc, turn.errorText,
                                       L"", font, palette_.error, turnIndex, false});
                y += height + SI(8);
            }
            const std::wstring copyLabel = Tr(Str::Copy);
            const int copyWidth = std::max(
                SI(72), SI(32) + text_.Width(SmallFont(), copyLabel.c_str(),
                                             static_cast<int>(copyLabel.size())) + SI(10));
            convoItems_.push_back({ConvoItem::Kind::CopyButton,
                                   {textLeft - SI(8), y, textLeft - SI(8) + copyWidth, y + SI(28)},
                                   {}, copyLabel, L"", SmallFont(), palette_.secondary,
                                   turnIndex, false});
            y += SI(28) + SI(14);
        }
        contentHeight_ = std::max(0, y - SI(14));
        BuildAnswerLines();
    }

    void BuildAnswerLines() {
        answerLines_.clear();
        answerText_.clear();
        for (const ConvoItem& item : convoItems_) {
            if (item.kind != ConvoItem::Kind::Text) {
                continue;
            }
            if (!answerText_.empty()) {
                answerText_ += L"\n\n";
            }
            if (!item.bullet.empty()) {
                answerText_ += item.bullet + L" ";
            }
            const size_t base = answerText_.size();
            answerText_ += item.text;
            const int height = text_.Measure(item.font, L"Mg", 1, DT_SINGLELINE).cy;
            int y = item.textRect.top;
            for (WrappedTextLine& line : text_.Wrap(item.font, item.text,
                                                   item.textRect.right - item.textRect.left)) {
                answerLines_.push_back({{item.textRect.left, y, item.textRect.right, y + height},
                                         base + line.start, line.length, std::move(line.extents),
                                         item.font, item.color, item.turn});
                y += height;
            }
        }
        answerAnchor_ = std::min(answerAnchor_, answerText_.size());
        answerCaret_ = std::min(answerCaret_, answerText_.size());
    }

    bool ConversationCacheCoversViewport() const {
        const int viewport = std::max(1, static_cast<int>(convoRect_.bottom - convoRect_.top));
        return convo_.Valid() && convo_.Width() == std::max(1, convoWidth_) &&
               scroll_ >= convoCacheTop_ &&
               scroll_ + viewport <= convoCacheTop_ + convo_.Height();
    }

    void RenderConversation() {
        const int viewport = std::max(1, static_cast<int>(convoRect_.bottom - convoRect_.top));
        const int cacheHeight = std::min(std::max(1, contentHeight_), viewport * 3);
        convoCacheTop_ = std::clamp(scroll_ - viewport, 0,
                                   std::max(0, contentHeight_ - cacheHeight));
        if (!convo_.Resize(std::max(1, convoWidth_), cacheHeight)) {
            return;
        }
        const int cacheBottom = convoCacheTop_ + cacheHeight;
        for (const ConvoItem& item : convoItems_) {
            if (item.rect.bottom <= convoCacheTop_ || item.rect.top >= cacheBottom) {
                continue;
            }
            RECT textRect = item.textRect;
            OffsetRect(&textRect, 0, -convoCacheTop_);
            const float l = static_cast<float>(item.rect.left);
            const float t = static_cast<float>(item.rect.top - convoCacheTop_);
            const float r = static_cast<float>(item.rect.right);
            const float b = static_cast<float>(item.rect.bottom - convoCacheTop_);
            switch (item.kind) {
                case ConvoItem::Kind::UserBubble:
                    FillRoundRect(convo_, l, t, r, b, S(8), palette_.userBubble);
                    text_.Draw(convo_, item.font, item.text, textRect,
                               DT_WORDBREAK, item.color);
                    break;
                case ConvoItem::Kind::Text:
                    if (item.code) {
                        FillRoundRect(convo_, l, t, r, b, S(6), palette_.codeBg);
                    }
                    if (!item.bullet.empty()) {
                        const RECT bulletRect{item.rect.left, textRect.top,
                                              textRect.left, textRect.bottom};
                        text_.Draw(convo_, item.font, item.bullet, bulletRect,
                                   DT_LEFT | DT_SINGLELINE, palette_.secondary);
                    }
                    break;
                default:
                    break;
            }
        }
        for (const AnswerLine& line : answerLines_) {
            if (line.rect.bottom <= convoCacheTop_ || line.rect.top >= cacheBottom) {
                continue;
            }
            RECT rc = line.rect;
            OffsetRect(&rc, 0, -convoCacheTop_);
            text_.Draw(convo_, line.font, answerText_.substr(line.start, line.length),
                       rc, DT_SINGLELINE | DT_LEFT, line.color);
        }
        convoDirty_ = false;
    }

    void UpdateCopyHits() {
        hits_.erase(std::remove_if(hits_.begin(), hits_.end(),
                                   [](const HitRect& hit) {
                                       return hit.id >= kHitCopyAnswer;
                                   }),
                    hits_.end());
        for (const ConvoItem& item : convoItems_) {
            if (item.kind != ConvoItem::Kind::CopyButton) {
                continue;
            }
            RECT rc = item.rect;
            OffsetRect(&rc, convoRect_.left, convoRect_.top - scroll_);
            RECT visible;
            if (IntersectRect(&visible, &rc, &convoRect_)) {
                hits_.insert(hits_.begin(), HitRect{visible, kHitCopyAnswer + item.turn});
            }
        }
    }

    void Layout() {
        width_ = SI(400);
        const int pad = SI(12);
        hits_.clear();

        int x = pad;
        const int headerTop = pad;
        const int thumbSize = SI(56);
        thumbRects_.clear();
        for (size_t i = 0; i < attachments_.size(); i++) {
            thumbRects_.push_back({x, headerTop, x + thumbSize, headerTop + thumbSize});
            x += thumbSize + SI(8);
        }
        addRect_ = {};
        if (CanAddMore()) {
            addRect_ = {x, headerTop, x + thumbSize, headerTop + thumbSize};
            hits_.push_back({addRect_, kHitAdd});
        }
        const bool hasKey = HasAiKey();
        const bool hasImage = !attachments_.empty();
        std::vector<int> buttons{kHitClose};
        if (hasKey) {
            buttons.push_back(kHitGemini);
        }
        if (hasImage) {
            buttons.push_back(kHitLens);
        }
        if (hasKey && hasImage) {
            buttons.push_back(kHitTranslate);
        }
        if (hasImage) {
            buttons.push_back(kHitCopy);
        }
        if (!CopyableText().empty()) {
            buttons.push_back(kHitCopyText);
        }
        const int count = static_cast<int>(buttons.size());
        const int right = width_ - pad + SI(4);
        const int used = std::max<int>(x - SI(8), addRect_.right);
        const int gaps = SI(6) + SI(2) * (count - 2);
        const int buttonSize =
            std::clamp((right - used - SI(6) - gaps) / count, SI(26), SI(32));
        int bx = right - buttonSize;
        const int by = headerTop - SI(4);
        for (RECT& rc : buttonRects_) {
            rc = {};
        }
        for (int id : buttons) {
            buttonRects_[id] = {bx, by, bx + buttonSize, by + buttonSize};
            hits_.push_back({buttonRects_[id], id});
            bx -= buttonSize + (id == kHitClose ? SI(6) : SI(2));
        }
        const bool emptyHeader = attachments_.empty() && addRect_.right <= addRect_.left;
        int y = emptyHeader ? by + buttonSize : headerTop + thumbSize;

        convoWidth_ = width_ - pad * 2;
        convoRect_ = {};
        if (!turns_.empty()) {
            if (convoDirty_ || convoLayoutWidth_ != convoWidth_) {
                LayoutConversation();
                convoLayoutWidth_ = convoWidth_;
                convoDirty_ = true;
            }
            y += SI(14);
            const RECT work = MonitorRectAt(RectCenter(selection_), true);
            const int maxHeight = std::clamp(
                static_cast<int>((work.bottom - work.top) * 0.5f), SI(140), SI(560));
            const int height = std::min(contentHeight_, maxHeight);
            convoRect_ = {pad, y, width_ - pad, y + height};
            const int maxScroll = std::max(0, contentHeight_ - height);
            if (stickToBottom_) {
                scroll_ = maxScroll;
            }
            scroll_ = std::clamp(scroll_, 0, maxScroll);
            y += height;
        }

        statusText_ = status_;
        statusIsHint_ = false;
        if (statusText_.empty() && !HasAiKey() && turns_.empty()) {
            statusText_ = Tr(Str::NoApiKeyHint);
            statusIsHint_ = true;
        }
        statusRect_ = {};
        if (!statusText_.empty()) {
            const SIZE size = text_.Measure(SmallFont(), statusText_,
                                            width_ - pad * 2, DT_WORDBREAK);
            y += SI(10);
            statusRect_ = {pad, y, width_ - pad, y + size.cy};
            y += size.cy;
        }

        y += SI(12);
        inputRect_ = {pad, y, width_ - pad, y + SI(40)};
        const int sendSize = SI(30);
        sendRect_ = {inputRect_.right - SI(5) - sendSize, inputRect_.top + SI(5),
                     inputRect_.right - SI(5), inputRect_.top + SI(5) + sendSize};
        inputText_ = {inputRect_.left + SI(12), inputRect_.top,
                      sendRect_.left - SI(8), inputRect_.bottom};
        hits_.push_back({sendRect_, kHitSend});
        hits_.push_back({inputRect_, kHitInput});
        if (convoRect_.bottom > convoRect_.top) {
            hits_.push_back({convoRect_, kHitConvo});
        }
        y = inputRect_.bottom;

        chipRects_.clear();
        dividerY_ = -1;
        if (turns_.empty() && (chipsLoading_ || !chips_.empty())) {
            y += SI(10);
            dividerY_ = y;
            y += SI(5);
            const size_t count = chipsLoading_ ? std::max<size_t>(3, chips_.size())
                                               : chips_.size();
            for (size_t i = 0; i < count; i++) {
                const RECT rc{SI(5), y, width_ - SI(5), y + SI(36)};
                chipRects_.push_back(rc);
                if (i < chips_.size()) {
                    hits_.push_back({rc, kHitChip + static_cast<int>(i)});
                }
                y += SI(36);
            }
            y += SI(5);
        } else {
            y += pad;
        }
        height_ = y;
        UpdateCopyHits();

        const int caretX = CaretX(caret_);
        const int visibleWidth =
            std::max(1, static_cast<int>(inputText_.right - inputText_.left) - SI(2));
        if (caretX - inputScroll_ > visibleWidth) {
            inputScroll_ = caretX - visibleWidth;
        } else if (caretX < inputScroll_) {
            inputScroll_ = caretX;
        }
        inputScroll_ = std::max(0, inputScroll_);
    }

    void Position() {
        const POINT anchor = dragged_ ? POINT{cardPos_.x + width_ / 2, cardPos_.y + SI(24)}
                                      : RectCenter(selection_);
        const RECT work = MonitorRectAt(anchor, true);
        const int gap = SI(12);
        const int edge = SI(8);
        if (!placed_) {
            const POINT candidates[] = {
                {selection_.left, selection_.bottom + gap},
                {selection_.left, selection_.top - gap - height_},
                {selection_.right + gap, selection_.top},
                {selection_.left - gap - width_, selection_.top},
                {selection_.right - gap - width_, selection_.bottom - gap - height_},
            };
            cardPos_ = candidates[0];
            for (const POINT& candidate : candidates) {
                if (candidate.y >= work.top + edge &&
                    candidate.y + height_ <= work.bottom - edge &&
                    candidate.x + width_ / 2 >= work.left &&
                    candidate.x + width_ / 2 <= work.right) {
                    cardPos_ = candidate;
                    break;
                }
            }
            placed_ = true;
        }
        const int minX = work.left + edge;
        const int maxX = std::max(minX, static_cast<int>(work.right) - edge - width_);
        const int x = std::clamp(static_cast<int>(cardPos_.x), minX, maxX);
        int y = std::min(static_cast<int>(cardPos_.y),
                         static_cast<int>(work.bottom) - edge - height_);
        y = std::max(y, static_cast<int>(work.top) + edge);
        windowPos_ = {x, y};
    }

    void Update(double now) {
        if (!open_) {
            return;
        }
        Layout();
        if (convoDirty_) {
            RenderConversation();
        }
        Position();
        Present(now);
    }

    ////////////////////////////////////////////////////////////////////////
    // Rendering

    PanelKey Key() const {
        return {width_, height_, palette_.dark, panel_.Material(), g_styleVersion, SI(100)};
    }

    void RenderBase() {
        if (chrome_.Valid() && Key() == chromeKey_) {
            return;
        }
        chromeKey_ = Key();
        chrome_.Resize(width_, height_);
        PaintPanelBase(chrome_, panel_, scale_);
    }

    bool RenderUnderlay() {
        const PanelKey key = Key();
        if (underlay_.Valid() && key == underlayKey_) {
            return false;
        }
        underlayKey_ = key;
        underlayMargin_ = SI(84);
        PaintPanelUnderlay(underlay_, width_, height_, underlayMargin_,
                           panel_.Radius(scale_), scale_, palette_.dark,
                           palette_.dark ? 0.95f : 0.70f, 0.0f);
        return true;
    }

    void DrawButton(int id, Glyph glyph) {
        const RECT& rc = buttonRects_[id];
        if (rc.right <= rc.left) {
            return;
        }
        const bool hovered = hover_ == id;
        if (hovered) {
            FillRoundRect(surface_, static_cast<float>(rc.left),
                          static_cast<float>(rc.top), static_cast<float>(rc.right),
                          static_cast<float>(rc.bottom), S(4),
                          pressed_ == id ? palette_.subtlePressed : palette_.subtleHover);
        }
        DrawGlyph(surface_, text_, glyph, (rc.left + rc.right) * 0.5f,
                  (rc.top + rc.bottom) * 0.5f, scale_,
                  hovered ? palette_.text : palette_.secondary);
    }

    void DrawThumbnails(double now) {
        for (size_t i = 0; i < attachments_.size() && i < thumbRects_.size(); i++) {
            const RECT& rc = thumbRects_[i];
            Attachment& attachment = attachments_[i];
            const int wanted =
                std::min(static_cast<int>(rc.right - rc.left) * 2,
                         std::max(attachment.image->width, attachment.image->height));
            if (attachment.thumb.Empty() ||
                std::max(attachment.thumb.width, attachment.thumb.height) < wanted) {
                attachment.thumb = DownscaleImage(*attachment.image, std::max(1, wanted));
            }
            const float l = static_cast<float>(rc.left);
            const float t = static_cast<float>(rc.top);
            const float r = static_cast<float>(rc.right);
            const float b = static_cast<float>(rc.bottom);
            DrawImageRounded(surface_, attachment.thumb, l, t, r, b, S(6),
                             palette_.controlFill);
            StrokeRoundRect(surface_, l + 0.5f, t + 0.5f, r - 0.5f, b - 0.5f, S(6),
                            1.0f, palette_.controlBorder);
            if (attachment.ocrPending) {
                const float sweep = static_cast<float>(fmod(now / 1300.0, 1.0));
                const float lineY = t - S(8) + (b - t + S(16)) * sweep;
                const float sigma = S(5);
                const Color glow = Mix(g_glow.At(static_cast<float>(now / 3000.0)),
                                       kWhite, 0.35f);
                FillShape(
                    surface_, l, std::max(t, lineY - sigma * 3), r,
                    std::min(b, lineY + sigma * 3),
                    [&](float x, float y) {
                        return SdRoundRect(x, y, l, t, r, b, S(6));
                    },
                    [&](float, float y) {
                        const float d = (y - lineY) / sigma;
                        return WithAlpha(glow, 0.75f * expf(-d * d));
                    });
            }
        }
        if (addRect_.right > addRect_.left) {
            const bool hovered = hover_ == kHitAdd;
            const Color color = hovered ? palette_.text : palette_.secondary;
            const float l = static_cast<float>(addRect_.left);
            const float t = static_cast<float>(addRect_.top);
            const float r = static_cast<float>(addRect_.right);
            const float b = static_cast<float>(addRect_.bottom);
            if (hovered) {
                FillRoundRect(surface_, l, t, r, b, S(6), palette_.subtleHover);
            }
            StrokeRoundRectDashed(surface_, l + S(1), t + S(1), r - S(1), b - S(1),
                                  S(6), S(1.2f), S(4), WithAlpha(color, 0.75f));
            DrawGlyph(surface_, text_, Glyph::Add, (l + r) * 0.5f, (t + b) * 0.5f,
                      scale_, color);
        }
    }

    void DrawConversation(double now) {
        if (!ConversationCacheCoversViewport()) {
            RenderConversation();
        }
        const int viewport = convoRect_.bottom - convoRect_.top;
        const int fade = SI(18);
        const bool fadeTop = scroll_ > 0;
        const bool fadeBottom = scroll_ + viewport < contentHeight_;
        for (int y = 0; y < viewport; y++) {
            const int sourceY = y + scroll_ - convoCacheTop_;
            if (sourceY < 0 || sourceY >= convo_.Height()) {
                continue;
            }
            float factor = 1.0f;
            if (fadeTop && y < fade) {
                factor = std::min(factor, static_cast<float>(y) / fade);
            }
            if (fadeBottom && viewport - y < fade) {
                factor = std::min(factor, static_cast<float>(viewport - y) / fade);
            }
            const uint32_t* src = convo_.Row(sourceY);
            uint32_t* dst = surface_.Row(convoRect_.top + y) + convoRect_.left;
            const uint32_t k = static_cast<uint32_t>(factor * 255.0f + 0.5f);
            for (int x = 0; x < convoWidth_ && x < convo_.Width(); x++) {
                uint32_t pixel = src[x];
                if (!pixel) {
                    continue;
                }
                if (k < 255) {
                    pixel = ScalePremultiplied(pixel, k);
                }
                BlendOver(dst[x], pixel);
            }
        }

        const size_t selectionStart = std::min(answerAnchor_, answerCaret_);
        const size_t selectionEnd = std::max(answerAnchor_, answerCaret_);
        if (selectionStart < selectionEnd) {
            for (const AnswerLine& line : answerLines_) {
                const size_t a = std::max(selectionStart, line.start);
                const size_t b = std::min(selectionEnd, line.start + line.length);
                if (a >= b) {
                    continue;
                }
                const size_t first = a - line.start;
                const size_t last = b - line.start;
                RECT layout = line.rect;
                OffsetRect(&layout, convoRect_.left, convoRect_.top - scroll_);
                RECT highlight = layout;
                highlight.left += first ? line.extents[first - 1] : 0;
                highlight.right = layout.left + (last ? line.extents[last - 1] : 0);
                RECT clip;
                if (IntersectRect(&clip, &highlight, &convoRect_)) {
                    FillRoundRect(surface_, static_cast<float>(clip.left),
                                  static_cast<float>(clip.top), static_cast<float>(clip.right),
                                  static_cast<float>(clip.bottom), S(2),
                                  WithAlpha(palette_.accent, focused_ ? 0.28f : 0.15f));
                    text_.Draw(surface_, line.font, answerText_.substr(line.start, line.length),
                               layout, clip, DT_SINGLELINE | DT_LEFT, line.color);
                }
            }
        }

        for (const ConvoItem& item : convoItems_) {
            RECT rc = item.rect;
            OffsetRect(&rc, convoRect_.left, convoRect_.top - scroll_);
            RECT visible;
            if (!IntersectRect(&visible, &rc, &convoRect_)) {
                continue;
            }
            switch (item.kind) {
                case ConvoItem::Kind::Sparkle: {
                    const bool working = item.turn == static_cast<int>(turns_.size()) - 1 &&
                                         turns_.back().streaming;
                    const float angle =
                        working ? static_cast<float>(fmod(now / 900.0, 1.0)) * 2.0f * kPi
                                : 0.0f;
                    FillSparkleGradient(surface_, (rc.left + rc.right) * 0.5f,
                                        (rc.top + rc.bottom) * 0.5f, S(8.5f), angle,
                                        working ? static_cast<float>(now / 2000.0) : 0.1f);
                    break;
                }
                case ConvoItem::Kind::Thinking: {
                    text_.Draw(surface_, item.font, item.text, rc, convoRect_,
                               DT_SINGLELINE | DT_VCENTER | DT_LEFT, palette_.secondary);
                    const int width = text_.Width(item.font, item.text.c_str(),
                                                  static_cast<int>(item.text.size()));
                    const float sweep = static_cast<float>(fmod(now / 1300.0, 1.0));
                    const float center = rc.left + (width + S(60)) * sweep - S(30);
                    const RECT shine{static_cast<LONG>(center - S(22)), rc.top,
                                     static_cast<LONG>(center + S(22)), rc.bottom};
                    RECT clip;
                    if (IntersectRect(&clip, &shine, &visible)) {
                        text_.Draw(surface_, item.font, item.text, rc, clip,
                                   DT_SINGLELINE | DT_VCENTER | DT_LEFT, palette_.accent);
                    }
                    break;
                }
                case ConvoItem::Kind::CopyButton: {
                    const bool hovered = hover_ == kHitCopyAnswer + item.turn;
                    if (hovered) {
                        FillRoundRect(surface_, static_cast<float>(visible.left),
                                      static_cast<float>(visible.top),
                                      static_cast<float>(visible.right),
                                      static_cast<float>(visible.bottom), S(4),
                                      palette_.subtleHover);
                    }
                    const Color color = hovered ? palette_.text : palette_.secondary;
                    const float cy = (rc.top + rc.bottom) * 0.5f;
                    if (cy > convoRect_.top && cy < convoRect_.bottom) {
                        DrawGlyph(surface_, text_, Glyph::Copy, rc.left + S(18), cy,
                                  scale_ * 0.875f, color);
                    }
                    const RECT label{rc.left + SI(32), rc.top, rc.right, rc.bottom};
                    text_.Draw(surface_, item.font, item.text, label, convoRect_,
                               DT_SINGLELINE | DT_VCENTER | DT_LEFT, color);
                    break;
                }
                default:
                    break;
            }
        }
    }

    void DrawInput() {
        const bool inputFocused = focused_ && !answerFocused_;
        const float l = static_cast<float>(inputRect_.left);
        const float t = static_cast<float>(inputRect_.top);
        const float r = static_cast<float>(inputRect_.right);
        const float b = static_cast<float>(inputRect_.bottom);
        const float radius = S(4);
        const bool hovered = hover_ == kHitInput || hover_ == kHitSend;
        FillRoundRect(surface_, l, t, r, b, radius,
                      inputFocused ? palette_.controlFillFocus
                      : hovered ? palette_.controlFillHover
                                : palette_.controlFill);
        StrokeRoundRect(surface_, l + 0.5f, t + 0.5f, r - 0.5f, b - 0.5f, radius,
                        1.0f, palette_.controlBorder);
        const float line = inputFocused ? std::max(2.0f, S(2)) : 1.0f;
        const Color lineColor = inputFocused ? palette_.accent : palette_.controlStrong;
        FillShape(
            surface_, l, b - line - 1, r, b,
            [&](float x, float y) {
                return std::max(SdRoundRect(x, y, l, t, r, b, radius), b - line - y);
            },
            [&](float, float) { return lineColor; });

        HFONT font = InputFont();
        const int textX = inputText_.left - inputScroll_;
        if (anchor_ != caret_) {
            const int x0 = textX + CaretX(std::min(anchor_, caret_));
            const int x1 = textX + CaretX(std::max(anchor_, caret_));
            const float left = static_cast<float>(std::max(x0, static_cast<int>(inputText_.left)));
            const float right = static_cast<float>(std::min(x1, static_cast<int>(inputText_.right)));
            if (right > left) {
                FillRoundRect(surface_, left, t + S(10), right, b - S(10), S(2),
                              palette_.selection);
            }
        }
        if (input_.empty()) {
            text_.Draw(surface_, font,
                       !turns_.empty()         ? Tr(Str::FollowUpPlaceholder)
                       : attachments_.empty() ? Tr(Str::AskAnythingPlaceholder)
                                              : Tr(Str::AskPlaceholder),
                       inputText_, DT_SINGLELINE | DT_VCENTER | DT_LEFT | DT_END_ELLIPSIS,
                       palette_.secondary);
        } else {
            const RECT layout{textX, inputText_.top, textX + 100000, inputText_.bottom};
            text_.Draw(surface_, font, input_, layout, inputText_,
                       DT_SINGLELINE | DT_VCENTER | DT_LEFT, palette_.text);
        }
        if (inputFocused && caretOn_) {
            const float x = textX + CaretX(caret_) + 0.5f;
            if (x >= inputText_.left - 1 && x <= inputText_.right + 1) {
                StrokeLine(surface_, {x, t + S(11)}, {x, b - S(11)}, std::max(1.0f, S(1)),
                           palette_.text);
            }
        }

        const float sl = static_cast<float>(sendRect_.left);
        const float st = static_cast<float>(sendRect_.top);
        const float sr = static_cast<float>(sendRect_.right);
        const float sb = static_cast<float>(sendRect_.bottom);
        const bool enabled = !Trim(input_).empty();
        if (enabled) {
            FillRoundRect(surface_, sl, st, sr, sb, S(4),
                          hover_ == kHitSend ? WithAlpha(palette_.accent, 0.9f)
                                             : palette_.accent);
        } else if (hover_ == kHitSend) {
            FillRoundRect(surface_, sl, st, sr, sb, S(4), palette_.subtleHover);
        }
        DrawGlyph(surface_, text_, Glyph::Send, (sl + sr) * 0.5f, (st + sb) * 0.5f,
                  scale_ * 0.875f, enabled ? palette_.onAccent : palette_.tertiary);
    }

    void DrawChips(double now) {
        if (chipRects_.empty()) {
            return;
        }
        if (dividerY_ >= 0) {
            FillRoundRect(surface_, static_cast<float>(SI(12)),
                          static_cast<float>(dividerY_),
                          static_cast<float>(width_ - SI(12)),
                          static_cast<float>(dividerY_) + std::max(1.0f, S(1)), 0,
                          palette_.divider);
        }
        for (size_t i = 0; i < chipRects_.size(); i++) {
            const RECT& rc = chipRects_[i];
            const float l = static_cast<float>(rc.left);
            const float t = static_cast<float>(rc.top);
            const float r = static_cast<float>(rc.right);
            const float b = static_cast<float>(rc.bottom);
            const float cy = (t + b) * 0.5f;
            const float iconX = l + S(21);
            if (i >= chips_.size()) {
                FillSparkleGradient(surface_, iconX, cy, S(6.5f),
                                    static_cast<float>(fmod(now / 1100.0, 1.0)) * 2.0f * kPi,
                                    static_cast<float>(now / 2000.0));
                const float sweep = static_cast<float>(fmod(now / 1200.0 + i * 0.15, 1.0));
                const float barL = l + S(41);
                const float barR = barL + (r - S(16) - barL) * (i % 3 == 0   ? 0.62f
                                                                 : i % 3 == 1 ? 0.80f
                                                                              : 0.52f);
                const float barT = cy - S(5);
                const float barB = cy + S(5);
                const float center = barL + (barR - barL + S(80)) * sweep - S(40);
                FillShape(
                    surface_, barL, barT, barR, barB,
                    [&](float x, float y) {
                        return SdRoundRect(x, y, barL, barT, barR, barB, S(5));
                    },
                    [&](float x, float) {
                        const float k = Clamp01(1.0f - fabsf(x - center) / S(48));
                        return Mix(WithAlpha(palette_.text, 0.08f),
                                   WithAlpha(palette_.accent, 0.45f), k);
                    });
                continue;
            }
            const int id = kHitChip + static_cast<int>(i);
            const bool hovered = hover_ == id;
            if (hovered) {
                FillRoundRect(surface_, l, t, r, b, S(4),
                              pressed_ == id ? palette_.subtlePressed : palette_.subtleHover);
            }
            const Chip& chip = chips_[i];
            const Color iconColor = hovered ? palette_.text : palette_.secondary;
            switch (chip.action) {
                case ChipAction::Ask:
                    FillSparkleGradient(surface_, iconX, cy, S(6.5f), 0.0f,
                                        0.1f + 0.2f * static_cast<float>(i));
                    break;
                case ChipAction::AskInBrowser:
                    DrawGlyph(surface_, text_, Glyph::OpenInNew, iconX, cy, scale_, iconColor);
                    break;
                case ChipAction::Lens:
                    DrawGlyph(surface_, text_, Glyph::Camera, iconX, cy, scale_, iconColor);
                    break;
                case ChipAction::CopyImage:
                    DrawGlyph(surface_, text_, Glyph::Copy, iconX, cy, scale_, iconColor);
                    break;
                case ChipAction::CopyText:
                    DrawGlyph(surface_, text_, Glyph::Text, iconX, cy, scale_, iconColor);
                    break;
            }
            const RECT label{static_cast<LONG>(l + S(41)), rc.top,
                             static_cast<LONG>(r - S(12)), rc.bottom};
            text_.Draw(surface_, ChipFont(), chip.label, label,
                       DT_SINGLELINE | DT_VCENTER | DT_LEFT | DT_END_ELLIPSIS,
                       palette_.text);
        }
    }

    void DrawTooltip() {
        std::wstring tooltip;
        switch (hover_) {
            case kHitClose:
                tooltip = Tr(Str::Close);
                break;
            case kHitGemini:
                tooltip = Tr(Str::AskInGemini);
                break;
            case kHitLens:
                tooltip = Tr(Str::SearchWithLens);
                break;
            case kHitTranslate:
                tooltip = TrFormat(Str::TranslateTo, TranslationLanguageName());
                break;
            case kHitCopy:
                tooltip = Tr(Str::CopyImage);
                break;
            case kHitCopyText:
                tooltip = Tr(Str::CopyText);
                break;
            case kHitAdd:
                tooltip = Tr(Str::AddSelection);
                break;
        }
        if (tooltip.empty() || !tooltipShown_) {
            return;
        }
        const RECT& target = hover_ == kHitAdd ? addRect_ : buttonRects_[hover_];
        HFONT font = SmallFont();
        const int width =
            text_.Width(font, tooltip.c_str(), static_cast<int>(tooltip.size())) + SI(18);
        const int height = SI(28);
        const int minLeft = SI(4);
        const int maxLeft = std::max(minLeft, width_ - SI(4) - width);
        const int left = std::clamp(
            static_cast<int>((target.left + target.right) / 2 - width / 2), minLeft, maxLeft);
        const int top = target.bottom + SI(6);
        const float l = static_cast<float>(left);
        const float t = static_cast<float>(top);
        const float r = static_cast<float>(left + width);
        const float b = static_cast<float>(top + height);
        DrawShadow(surface_, l, t + S(2), r, b + S(2), S(4), S(4),
                   WithAlpha(kBlack, palette_.dark ? 0.35f : 0.12f));
        FillRoundRect(surface_, l, t, r, b, S(4), palette_.tooltipBg);
        StrokeRoundRect(surface_, l + 0.5f, t + 0.5f, r - 0.5f, b - 0.5f, S(4), 1.0f,
                        palette_.tooltipBorder);
        const RECT rc{left, top, left + width, top + height};
        text_.Draw(surface_, font, tooltip, rc, DT_SINGLELINE | DT_VCENTER | DT_CENTER,
                   palette_.text);
    }

    void Present(double now) {
        if (!open_ || suspended_ || width_ <= 0) {
            return;
        }
        const double eased = EaseOutCubic((now - openTime_) / kAppearMs);
        const int rise = static_cast<int>((1.0 - eased) * S(8));
        RenderBase();
        if (!surface_.Resize(width_, height_)) {
            return;
        }
        for (int y = 0; y < height_; y++) {
            memcpy(surface_.Row(y), chrome_.Row(y), static_cast<size_t>(width_) * 4);
        }

        DrawThumbnails(now);
        DrawButton(kHitClose, Glyph::Close);
        DrawButton(kHitGemini, Glyph::OpenInNew);
        DrawButton(kHitLens, Glyph::Camera);
        DrawButton(kHitTranslate, Glyph::Translate);
        DrawButton(kHitCopy, Glyph::Copy);
        DrawButton(kHitCopyText, Glyph::Text);

        if (!turns_.empty() && convo_.Valid()) {
            DrawConversation(now);
        }
        if (!statusText_.empty()) {
            text_.Draw(surface_, SmallFont(), statusText_, statusRect_, DT_WORDBREAK,
                       statusIsHint_ ? palette_.secondary : palette_.text);
        }
        DrawInput();
        DrawChips(now);
        DrawTooltip();

        panel_.Present(surface_, windowPos_.x, windowPos_.y + rise,
                       static_cast<BYTE>(eased * 255.0 + 0.5));

        const float glow = static_cast<float>(eased) * GlowBreath(now);
        const BYTE underlayAlpha = static_cast<BYTE>(glow * 255.0f + 0.5f);
        if (RenderUnderlay()) {
            panel_.PresentUnderlay(underlay_, underlayMargin_, underlayAlpha);
        } else {
            panel_.SetUnderlayAlpha(underlayAlpha);
        }
    }

    ////////////////////////////////////////////////////////////////////////
    // Window messages

    int HitTest(POINT pt) const {
        for (const HitRect& hit : hits_) {
            if (PtInRect(&hit.rect, pt)) {
                return hit.id;
            }
        }
        return kHitNone;
    }

    void SetHover(int hit, double now) {
        if (hit != hover_) {
            hover_ = hit;
            hoverStart_ = now;
            tooltipShown_ = false;
            Present(now);
        }
    }

    bool HandleMessage(HWND hwnd,
                       UINT message,
                       WPARAM wParam,
                       LPARAM lParam,
                       LRESULT& result) {
        const double now = NowMs();
        switch (message) {
            case WM_NCHITTEST: {
                POINT pt{GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam)};
                ScreenToClient(hwnd, &pt);
                result = HitTest(pt) != kHitNone ? HTCLIENT : HTCAPTION;
                return true;
            }

            case WM_NCRBUTTONDOWN:
            case WM_NCRBUTTONUP:
            case WM_NCLBUTTONDBLCLK:
                result = 0;
                return true;

            case WM_CONTEXTMENU: {
                POINT screen{GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam)};
                if (screen.x == -1 && screen.y == -1) {
                    screen = {convoRect_.left + SI(32), convoRect_.top + SI(16)};
                    ClientToScreen(hwnd, &screen);
                }
                POINT pt = screen;
                ScreenToClient(hwnd, &pt);
                if (PtInRect(&convoRect_, pt) && !answerText_.empty()) {
                    SetFocus(hwnd);
                    if (!answerFocused_ || answerAnchor_ == answerCaret_) {
                        SelectAnswerAt(pt, false, true);
                        Present(now);
                    }
                    HMENU menu = CreatePopupMenu();
                    if (menu) {
                        AppendMenuW(menu, MF_STRING, 1,
                                    (std::wstring(Tr(Str::Copy)) + L"\tCtrl+C").c_str());
                        AppendMenuW(menu, MF_STRING, 2,
                                    (std::wstring(Tr(Str::SelectAll)) + L"\tCtrl+A").c_str());
                        const UINT action = TrackPopupMenu(menu,
                            TPM_RETURNCMD | TPM_NONOTIFY | TPM_RIGHTBUTTON |
                                (UiIsRtl() ? TPM_LAYOUTRTL : 0),
                            screen.x, screen.y, 0, hwnd, nullptr);
                        DestroyMenu(menu);
                        if (action == 1) {
                            CopyAnswerSelection(now);
                        } else if (action == 2) {
                            answerAnchor_ = 0;
                            answerCaret_ = answerText_.size();
                            Present(now);
                        }
                    }
                }
                result = 0;
                return true;
            }

            case WM_SETCURSOR:
                if (LOWORD(lParam) == HTCLIENT) {
                    POINT pt;
                    GetCursorPos(&pt);
                    ScreenToClient(hwnd, &pt);
                    const int hit = HitTest(pt);
                    PCWSTR cursor = IDC_ARROW;
                    if (hit == kHitInput || (hit == kHitConvo && !answerLines_.empty())) {
                        cursor = IDC_IBEAM;
                    } else if (hit != kHitNone && hit != kHitConvo) {
                        cursor = IDC_HAND;
                    }
                    SetCursor(LoadCursorW(nullptr, cursor));
                    result = TRUE;
                    return true;
                }
                return false;

            case WM_MOUSEMOVE: {
                const POINT pt{GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam)};
                if (!trackingMouse_) {
                    TRACKMOUSEEVENT track{sizeof(track), TME_LEAVE, hwnd, 0};
                    trackingMouse_ = TrackMouseEvent(&track);
                }
                if (selectingAnswer_) {
                    answerDragPoint_ = pt;
                    if (pt.y < convoRect_.top || pt.y >= convoRect_.bottom) {
                        ScrollBy(pt.y < convoRect_.top ? -SI(12) : SI(12));
                    }
                    answerCaret_ = AnswerIndexAt(pt);
                    Present(now);
                    RequestTick();
                } else if (selectingText_) {
                    MoveCaret(InputIndexAt(pt.x), true);
                    Update(now);
                } else {
                    SetHover(HitTest(pt), now);
                }
                result = 0;
                return true;
            }

            case WM_NCMOUSEMOVE:
                SetHover(kHitNone, now);
                return false;

            case WM_MOUSELEAVE:
                trackingMouse_ = false;
                SetHover(kHitNone, now);
                result = 0;
                return true;

            case WM_LBUTTONDOWN:
            case WM_LBUTTONDBLCLK: {
                const POINT pt{GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam)};
                SetFocus(hwnd);
                pressed_ = HitTest(pt);
                if (pressed_ == kHitInput) {
                    ClearAnswerSelection();
                    const bool shift = GetKeyState(VK_SHIFT) & 0x8000;
                    MoveCaret(InputIndexAt(pt.x), shift);
                    if (message == WM_LBUTTONDBLCLK && !input_.empty()) {
                        int begin = caret_;
                        int end = caret_;
                        while (begin > 0 && !iswspace(input_[begin - 1])) {
                            begin--;
                        }
                        while (end < static_cast<int>(input_.size()) &&
                               !iswspace(input_[end])) {
                            end++;
                        }
                        anchor_ = begin;
                        caret_ = end;
                    } else {
                        selectingText_ = true;
                        SetCapture(hwnd);
                    }
                    caretStart_ = now;
                    caretOn_ = true;
                    Update(now);
                } else if (pressed_ == kHitConvo && !answerLines_.empty()) {
                    SelectAnswerAt(pt, GetKeyState(VK_SHIFT) & 0x8000,
                                   message == WM_LBUTTONDBLCLK);
                    answerDragPoint_ = pt;
                    selectingAnswer_ = message != WM_LBUTTONDBLCLK;
                    if (selectingAnswer_) {
                        SetCapture(hwnd);
                    }
                    Present(now);
                    RequestTick();
                } else if (pressed_ != kHitNone) {
                    Present(now);
                }
                result = 0;
                return true;
            }

            case WM_LBUTTONUP: {
                const POINT pt{GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam)};
                if (selectingAnswer_) {
                    answerCaret_ = AnswerIndexAt(pt);
                    selectingAnswer_ = false;
                    ReleaseCapture();
                    Present(now);
                } else if (selectingText_) {
                    selectingText_ = false;
                    ReleaseCapture();
                } else if (pressed_ != kHitNone && pressed_ != kHitInput &&
                           pressed_ == HitTest(pt)) {
                    const int hit = pressed_;
                    pressed_ = kHitNone;
                    Activate(hit, now);
                }
                if (pressed_ != kHitNone) {
                    pressed_ = kHitNone;
                    Present(now);
                }
                result = 0;
                return true;
            }

            case WM_CAPTURECHANGED:
                selectingText_ = false;
                selectingAnswer_ = false;
                return false;

            case WM_MOUSEWHEEL:
                if (!turns_.empty()) {
                    ScrollBy(-GET_WHEEL_DELTA_WPARAM(wParam) * SI(48) / WHEEL_DELTA);
                    Present(now);
                }
                result = 0;
                return true;

            case WM_KEYDOWN:
                if (HandleKey(wParam, now)) {
                    result = 0;
                    return true;
                }
                return false;

            case WM_CHAR:
                if (wParam >= 0x20 && wParam != 0x7F) {
                    ClearAnswerSelection();
                    InsertText(std::wstring(1, static_cast<wchar_t>(wParam)));
                    caretStart_ = now;
                    caretOn_ = true;
                    Update(now);
                }
                result = 0;
                return true;

            case WM_SETFOCUS:
                focused_ = true;
                caretStart_ = now;
                caretOn_ = true;
                Present(now);
                return false;

            case WM_KILLFOCUS:
                focused_ = false;
                Present(now);
                return false;

            case WM_IME_STARTCOMPOSITION:
                if (HIMC context = ImmGetContext(hwnd)) {
                    COMPOSITIONFORM form{};
                    form.dwStyle = CFS_POINT;
                    form.ptCurrentPos.x = inputText_.left - inputScroll_ + CaretX(caret_);
                    form.ptCurrentPos.y = inputRect_.top + SI(10);
                    ImmSetCompositionWindow(context, &form);
                    ImmReleaseContext(hwnd, context);
                }
                return false;

            case WM_WINDOWPOSCHANGED: {
                const WINDOWPOS* pos = reinterpret_cast<const WINDOWPOS*>(lParam);
                if (!(pos->flags & SWP_NOMOVE) && open_ &&
                    (pos->x != panel_.X() || pos->y != panel_.Y())) {
                    panel_.FollowPanel(pos->x, pos->y);
                    cardPos_ = {pos->x, pos->y};
                    windowPos_ = cardPos_;
                    dragged_ = true;
                    openTime_ = std::min(openTime_, now - kAppearMs - 1);
                    Present(now);
                }
                return false;
            }

            case WM_DPICHANGED:
                scale_ = HIWORD(wParam) / 96.0f;
                chromeKey_ = {};
                underlayKey_ = {};
                convoDirty_ = true;
                Update(now);
                result = 0;
                return true;

            case WM_CLOSE:
                Close();
                result = 0;
                return true;
        }
        return false;
    }

    GlassPanel panel_;
    Surface surface_;
    Surface chrome_;
    Surface convo_;
    Surface underlay_;
    TextPainter text_;
    Palette palette_ = MakePalette(false);
    float scale_ = 1.0f;

    bool open_ = false;
    bool suspended_ = false;
    bool placed_ = false;
    bool dragged_ = false;
    double openTime_ = 0;
    RECT selection_{};
    POINT cardPos_{};
    POINT windowPos_{};

    std::vector<Attachment> attachments_;
    std::vector<CardTurn> turns_;
    std::vector<Chip> chips_;
    bool chipsLoading_ = false;
    double suggestionsStart_ = 0;
    std::shared_ptr<AiJob> chatJob_;
    std::shared_ptr<AiJob> suggestionsJob_;
    std::shared_ptr<BrowserHandoffJob> browserJob_;
    uint32_t chatId_ = 0;
    uint32_t suggestionsId_ = 0;

    std::wstring input_;
    int caret_ = 0;
    int anchor_ = 0;  // The other end of the text selection.
    int inputScroll_ = 0;
    bool selectingText_ = false;
    std::wstring extentsText_;
    HFONT extentsFont_ = nullptr;
    std::vector<int> extents_;

    std::wstring status_;
    double statusUntil_ = 0;
    std::wstring statusText_;
    bool statusIsHint_ = false;

    int width_ = 0;
    int height_ = 0;
    std::vector<RECT> thumbRects_;
    RECT addRect_{};
    RECT buttonRects_[kHitTranslate + 1] = {};
    RECT convoRect_{};
    RECT statusRect_{};
    RECT inputRect_{};
    RECT inputText_{};
    RECT sendRect_{};
    int dividerY_ = -1;
    std::vector<RECT> chipRects_;
    std::vector<HitRect> hits_;

    PanelKey chromeKey_, underlayKey_;
    int underlayMargin_ = 0;

    std::vector<ConvoItem> convoItems_;
    std::vector<AnswerLine> answerLines_;
    std::wstring answerText_;
    size_t answerAnchor_ = 0;
    size_t answerCaret_ = 0;
    bool answerFocused_ = false;
    bool selectingAnswer_ = false;
    POINT answerDragPoint_{};
    int convoWidth_ = 0;
    int convoLayoutWidth_ = 0;
    int convoCacheTop_ = 0;
    int contentHeight_ = 0;
    bool convoDirty_ = true;
    int scroll_ = 0;
    bool stickToBottom_ = true;

    int hover_ = kHitNone;
    int pressed_ = kHitNone;
    double hoverStart_ = 0;
    bool tooltipShown_ = false;
    bool trackingMouse_ = false;
    bool focused_ = false;
    bool caretOn_ = true;
    double caretStart_ = 0;
};

////////////////////////////////////////////////////////////////////////////////
// The Magic Pointer's state, input and animation

enum class PointerState { Off, Pointing, Pressed, Dragging };

InputOverlay g_overlay;
PointerCursors g_cursors;
HintPill g_pill;
GlowFrame g_frame;
Ripple g_ripple;
AskCard g_card;
ElementPicker g_picker;
ShakeDetector g_shake;

PointerState g_state = PointerState::Off;
HCURSOR g_currentCursor;
bool g_addingToCard;
bool g_revealPending;
bool g_releasingCapture;
bool g_escapeRegistered;
bool g_hotkeyRegistered;
POINT g_pressPoint;
double g_lastActivity;
double g_selectedAt;
float g_pointerScale = 1.0f;
HMONITOR g_pointerMonitor;
PickResult g_hover;
bool g_hoverValid;

POINT g_lastRawPoint{LONG_MIN, LONG_MIN};
HMONITOR g_shakeMonitor;
float g_shakeDpiScale = 1.0f;
HWINEVENTHOOK g_foregroundHook;
HWND g_shakePollingWindow;
std::wstring g_windhawkExecutable;
std::wstring g_windhawkUiDirectory;
constexpr UINT_PTR kShakePollingTimer = 1;

HANDLE g_timer;
HANDLE g_rippleTimer;
bool g_highResolutionTimer;
bool g_rippleTimerArmed;
bool g_timerArmed;
double g_timerDue;
double g_lastTick = -1e9;
constexpr double kFrameMs = 1000.0 / 60.0;
constexpr double kHintMs = 4500.0;

float PointerScaleAt(POINT pt) {
    DWORD baseSize = 32;
    DWORD size = sizeof(baseSize);
    if (RegGetValueW(HKEY_CURRENT_USER, L"Control Panel\\Cursors",
                     L"CursorBaseSize", RRF_RT_REG_DWORD, nullptr, &baseSize,
                     &size) != ERROR_SUCCESS ||
        baseSize < 32 || baseSize > 256) {
        baseSize = 32;
    }
    const float scale =
        DpiScaleAt(pt) * (baseSize / 32.0f) * g_settings.pointerSize / 100.0f;
    return std::clamp(scale, 0.75f, 3.5f);
}

HCURSOR OverlayCursor() {
    return g_currentCursor ? g_currentCursor : LoadCursorW(nullptr, IDC_ARROW);
}

void UpdatePointerCursor(double now) {
    HCURSOR cursor = g_cursors.Current(now);
    if (cursor != g_currentCursor) {
        g_currentCursor = cursor;
        SetCursor(cursor);
    }
    g_cursors.ReleaseRetired(g_currentCursor);
}

void ArmTimer(double due, double now) {
    LARGE_INTEGER dueTime;
    dueTime.QuadPart = -std::max<LONGLONG>(1, static_cast<LONGLONG>((due - now) * 10000.0));
    SetWaitableTimer(g_timer, &dueTime, 0, nullptr, nullptr, FALSE);
    g_timerArmed = true;
    g_timerDue = due;
}

void RequestTick() {
    const double now = NowMs();
    const double due = std::max(now, g_lastTick + kFrameMs);
    if (g_timerArmed && g_timerDue <= due) {
        return;
    }
    ArmTimer(due, now);
}

void ArmRippleTimer(double due, double now) {
    LARGE_INTEGER dueTime;
    dueTime.QuadPart = -std::max<LONGLONG>(1, static_cast<LONGLONG>((due - now) * 10000.0));
    SetWaitableTimer(g_rippleTimer, &dueTime, 0, nullptr, nullptr, FALSE);
    g_rippleTimerArmed = true;
}

void RequestRippleTick() {
    if (!g_rippleTimer) {
        RequestTick();
        return;
    }
    if (!g_rippleTimerArmed) {
        const double now = NowMs();
        ArmRippleTimer(now + g_ripple.FrameMs(), now);
    }
}

bool AnythingActive() {
    return g_state != PointerState::Off || g_card.IsOpen() ||
           g_frame.Visible() || g_pill.Visible() || g_overlay.Visible() ||
           g_ripple.Active();
}

void ArrangeLayers() {
    if (!g_layersChanged) {
        return;
    }
    g_layersChanged = false;
    const HWND order[] = {
        g_overlay.Hwnd(),     g_overlay.DimHwnd(), g_ripple.Hwnd(), g_frame.Hwnd(),
        g_pill.UnderlayHwnd(), g_pill.Hwnd(),       g_card.UnderlayHwnd(),
        g_card.Hwnd(),
    };
    for (HWND hwnd : order) {
        if (hwnd && IsWindowVisible(hwnd)) {
            SetWindowPos(hwnd, HWND_TOPMOST, 0, 0, 0, 0,
                         SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE |
                             SWP_NOOWNERZORDER);
        }
    }
}

void ShowHint(POINT pt, double now) {
    if (g_settings.hint) {
        g_pill.SetReach(g_cursors.Reach());
        g_pill.Show(pt, DpiScaleAt(pt), UseDarkTheme(), now);
    }
}

void RevealPointerHelpers(POINT pt, double now) {
    if (!g_revealPending) {
        return;
    }
    g_revealPending = false;
    if (g_state != PointerState::Pointing) {
        return;
    }
    ShowHint(pt, now);
    if (g_settings.highlight && g_picker.Start(g_messageWindow)) {
        g_picker.Request(pt);
    }
}

constexpr int kHotkeyTypeFirst = 64;

std::vector<int> g_typingHotkeys;
bool g_typingRegistered;
HKL g_typingLayout;

bool IsTypingKey(UINT vk) {
    return (vk >= '0' && vk <= '9') || (vk >= 'A' && vk <= 'Z') ||
           (vk >= VK_NUMPAD0 && vk <= VK_DIVIDE) ||
           (vk >= VK_OEM_1 && vk <= VK_OEM_3) ||
           (vk >= VK_OEM_4 && vk <= VK_OEM_8) || vk == VK_OEM_102;
}

std::wstring TypedText(UINT vk, UINT modifiers, HKL layout, bool capsLock) {
    BYTE state[256] = {};
    state[vk] = 0x80;
    if (modifiers & MOD_SHIFT) {
        state[VK_SHIFT] = 0x80;
    }
    if (capsLock) {
        state[VK_CAPITAL] = 1;
    }
    WCHAR buffer[8] = {};
    const UINT scan = MapVirtualKeyExW(vk, MAPVK_VK_TO_VSC, layout);
    const int count =
        ToUnicodeEx(vk, scan, state, buffer, ARRAYSIZE(buffer), 0x4, layout);
    std::wstring text;
    for (int i = 0; i < count; i++) {
        if (buffer[i] >= 0x20 && buffer[i] != 0x7F) {
            text += buffer[i];
        }
    }
    return text;
}

void UnregisterTypingKeys() {
    for (int id : g_typingHotkeys) {
        UnregisterHotKey(g_messageWindow, id);
    }
    g_typingHotkeys.clear();
    g_typingRegistered = false;
}

void RegisterTypingKeys() {
    g_typingRegistered = true;
    int id = kHotkeyTypeFirst;
    for (UINT vk = '0'; vk <= VK_OEM_102; vk++) {
        if (!IsTypingKey(vk)) {
            continue;
        }
        for (const UINT modifiers : {0u, static_cast<UINT>(MOD_SHIFT)}) {
            if (RegisterHotKey(g_messageWindow, id, modifiers, vk)) {
                g_typingHotkeys.push_back(id);
            }
            id++;
        }
    }
}

void UpdateTypingCapture() {
    const bool wanted = g_settings.typeToAsk && g_state == PointerState::Pointing &&
                        !g_addingToCard && g_messageWindow;
    if (wanted && !g_typingRegistered) {
        RegisterTypingKeys();
    } else if (!wanted && g_typingRegistered) {
        UnregisterTypingKeys();
    }
}

void ActivatePointer(POINT pt, double now) {
    if (g_state != PointerState::Off) {
        g_cursors.StartPop(now);
        if (!g_pill.Visible() && !g_revealPending) {
            ShowHint(pt, now);
        }
        g_lastActivity = now;
        RequestTick();
        return;
    }
    if (g_card.IsOpen() && !g_addingToCard) {
        g_card.Close();
    }
    g_frame.HideNow();
    g_pointerScale = PointerScaleAt(pt);
    g_pointerMonitor = MonitorFromPoint(pt, MONITOR_DEFAULTTONEAREST);
    g_cursors.SetScale(g_pointerScale);
    const bool capturing =
        g_settings.ripple && g_ripple.Prepare(pt, DpiScaleAt(pt), g_messageWindow);
    now = NowMs();
    g_cursors.StartPop(now);
    g_overlay.Show(g_settings.dim);
    g_state = PointerState::Pointing;
    UpdatePointerCursor(now);
    g_escapeRegistered =
        RegisterHotKey(g_messageWindow, kHotkeyEscape, MOD_NOREPEAT, VK_ESCAPE);
    g_lastActivity = now;
    g_hoverValid = false;
    g_revealPending = true;
    if (g_settings.highlight) {
        g_picker.Start(g_messageWindow);
    }
    if (!capturing) {
        RevealPointerHelpers(pt, now);
    }
    UpdateTypingCapture();
    RequestTick();
}

void DeactivatePointer(double now, bool keepFrame) {
    if (g_state == PointerState::Off) {
        return;
    }
    g_state = PointerState::Off;
    UpdateTypingCapture();
    g_revealPending = false;
    if (GetCapture() == g_overlay.Hwnd()) {
        g_releasingCapture = true;
        ReleaseCapture();
        g_releasingCapture = false;
    }
    if (g_escapeRegistered) {
        UnregisterHotKey(g_messageWindow, kHotkeyEscape);
        g_escapeRegistered = false;
    }
    g_pill.FadeOut(now);
    g_ripple.Stop();
    if (!keepFrame) {
        g_frame.FadeOut(now);
    }
    SetCursor(LoadCursorW(nullptr, IDC_ARROW));
    g_overlay.Hide();
    g_currentCursor = nullptr;
    g_cursors.Clear();
    POINT pt;
    if (GetCursorPos(&pt)) {
        SetCursorPos(pt.x, pt.y);
    }
    g_hoverValid = false;
    if (g_addingToCard) {
        g_addingToCard = false;
        g_card.Resume(now);
    }
    RequestTick();
}

void OnCardClosed() {
    if (g_frame.Visible() && g_frame.Style() == FrameStyle::Selected) {
        g_frame.FadeOut(NowMs());
        RequestTick();
    }
}

void BeginAddSelection() {
    if (!g_card.CanAddMore()) {
        return;
    }
    POINT pt;
    if (!GetCursorPos(&pt)) {
        return;
    }
    g_card.Suspend();
    g_addingToCard = true;
    ActivatePointer(pt, NowMs());
}

void CompleteSelection(RECT rect, const std::wstring& text, double now) {
    const POINT center = RectCenter(rect);
    const RECT monitor = MonitorRectAt(center, false);
    IntersectRect(&rect, &rect, &monitor);
    const bool adding = g_addingToCard && g_card.IsOpen();
    g_addingToCard = false;
    if (IsRectEmpty(&rect)) {
        DeactivatePointer(now, false);
        if (adding) {
            g_card.Resume(now);
        }
        return;
    }

    g_frame.Conceal();
    g_pill.HideNow();
    g_ripple.Stop();
    DeactivatePointer(now, true);
    WaitForComposition();

    auto image = std::make_shared<Image>();
    if (!CaptureScreen(rect, *image)) {
        Wh_Log(L"Screen capture failed");
        g_frame.HideNow();
        if (adding) {
            g_card.Resume(now);
        }
        return;
    }
    now = NowMs();
    g_frame.Show(rect, FrameStyle::Selected, DpiScaleAt(center), now, false);
    g_selectedAt = now;

    Attachment attachment;
    attachment.image = std::move(image);
    attachment.text = text;
    if (adding) {
        g_card.AddAttachment(std::move(attachment), now);
    } else {
        g_card.Open(std::move(attachment), rect, now);
    }
    RequestTick();
}

RECT DragRect(POINT pt) {
    return {std::min(g_pressPoint.x, pt.x), std::min(g_pressPoint.y, pt.y),
            std::max(g_pressPoint.x, pt.x) + 1, std::max(g_pressPoint.y, pt.y) + 1};
}

void OnOverlayMouse(UINT message, POINT pt) {
    if (g_state == PointerState::Off) {
        return;
    }
    const double now = NowMs();
    g_lastActivity = now;
    switch (message) {
        case WM_MOUSEMOVE: {
            HMONITOR monitor = MonitorFromPoint(pt, MONITOR_DEFAULTTONEAREST);
            if (monitor != g_pointerMonitor) {
                g_pointerMonitor = monitor;
                const float scale = PointerScaleAt(pt);
                if (fabsf(scale - g_pointerScale) > 0.01f) {
                    g_pointerScale = scale;
                    g_cursors.SetScale(scale);
                    UpdatePointerCursor(now);
                }
            }
            g_pill.Follow(pt);
            if (g_state == PointerState::Pressed) {
                const LONG threshold = static_cast<LONG>(5 * DpiScaleAt(pt));
                if (labs(pt.x - g_pressPoint.x) > threshold ||
                    labs(pt.y - g_pressPoint.y) > threshold) {
                    g_state = PointerState::Dragging;
                    g_ripple.Stop();
                    g_pill.FadeOut(now);
                    g_hoverValid = false;
                }
            }
            if (g_state == PointerState::Dragging) {
                const RECT rect = DragRect(pt);
                g_overlay.SetSelection(rect, now);
                g_frame.Show(rect, FrameStyle::Drag, DpiScaleAt(pt), now, false);
            } else if (g_state == PointerState::Pointing && g_settings.highlight) {
                g_picker.Request(pt);
            }
            break;
        }

        case WM_LBUTTONDOWN:
            if (g_state == PointerState::Pointing) {
                g_state = PointerState::Pressed;
                g_pressPoint = pt;
                SetCapture(g_overlay.Hwnd());
            }
            break;

        case WM_LBUTTONUP: {
            const PointerState state = g_state;
            if (GetCapture() == g_overlay.Hwnd()) {
                g_releasingCapture = true;
                ReleaseCapture();
                g_releasingCapture = false;
            }
            if (state == PointerState::Dragging) {
                const RECT rect = DragRect(pt);
                if (rect.right - rect.left >= 8 && rect.bottom - rect.top >= 8) {
                    CompleteSelection(rect, L"", now);
                } else {
                    g_state = PointerState::Pointing;
                    g_overlay.ClearSelection();
                    g_frame.FadeOut(now);
                }
            } else if (state == PointerState::Pressed) {
                if (g_hoverValid && PtInRect(&g_hover.rect, pt)) {
                    const PickResult hover = g_hover;
                    CompleteSelection(hover.rect, hover.text, now);
                } else {
                    DeactivatePointer(now, false);
                }
            }
            break;
        }

        case WM_RBUTTONUP:
        case WM_MBUTTONUP:
            DeactivatePointer(now, false);
            break;

        case WM_CAPTURECHANGED:
            if (!g_releasingCapture && (g_state == PointerState::Pressed ||
                                        g_state == PointerState::Dragging)) {
                g_state = PointerState::Pointing;
                g_overlay.ClearSelection();
                g_frame.FadeOut(now);
            }
            break;
    }
    UpdateTypingCapture();
}

void OnRippleCapture(std::unique_ptr<RippleCaptureMessage> message) {
    if (!g_ripple.Owns(message->capture)) {
        return;
    }
    const double now = NowMs();
    bool reveal = message->complete;
    if (message->failed && !g_ripple.Active()) {
        g_ripple.Stop();
        reveal = true;
    } else if (message->first && g_state != PointerState::Off) {
        g_ripple.Launch(now, g_highResolutionTimer ? 0.0 : kFrameMs);
        reveal = reveal || !g_ripple.Active();
        RequestRippleTick();
        RequestTick();
    }
    if (reveal) {
        POINT pt;
        if (GetCursorPos(&pt)) {
            RevealPointerHelpers(pt, now);
        }
    }
}

void OnPickResult(std::unique_ptr<PickResult> result) {
    if (g_state != PointerState::Pointing) {
        return;
    }
    const double now = NowMs();
    POINT pt;
    GetCursorPos(&pt);
    if (result->found && PtInRect(&result->rect, pt)) {
        RECT rect = result->rect;
        const RECT monitor = MonitorRectAt(pt, false);
        IntersectRect(&rect, &rect, &monitor);
        if (IsRectEmpty(&rect)) {
            return;
        }
        const bool same = g_hoverValid && EqualRect(&rect, &g_hover.rect);
        g_hover = *result;
        g_hover.rect = rect;
        g_hoverValid = true;
        if (!same || !g_frame.Visible()) {
            g_frame.Show(rect, FrameStyle::Hover, DpiScaleAt(pt), now, true);
        }
    } else if (result->id == g_picker.LatestId()) {
        g_hoverValid = false;
        g_frame.FadeOut(now);
    }
}

void OnTypedKey(UINT modifiers, UINT vk, double now) {
    if (!g_card.IsOpen()) {
        if (g_state != PointerState::Pointing || !g_settings.typeToAsk) {
            return;
        }
        const HWND foreground = GetForegroundWindow();
        g_typingLayout = GetKeyboardLayout(
            foreground ? GetWindowThreadProcessId(foreground, nullptr) : 0);
    }
    const std::wstring text =
        TypedText(vk, modifiers, g_typingLayout, (GetKeyState(VK_CAPITAL) & 1) != 0);
    if (g_card.IsOpen()) {
        g_card.AppendTyped(text, now);
        return;
    }
    POINT pt;
    if (!GetCursorPos(&pt)) {
        return;
    }
    g_frame.HideNow();
    g_pill.HideNow();
    g_ripple.Stop();
    int spaceId = kHotkeyTypeFirst + 256;
    for (const UINT spaceModifiers : {0u, static_cast<UINT>(MOD_SHIFT)}) {
        if (RegisterHotKey(g_messageWindow, spaceId, spaceModifiers, VK_SPACE)) {
            g_typingHotkeys.push_back(spaceId);
        }
        spaceId++;
    }
    const RECT anchor{pt.x, pt.y, pt.x + 1, pt.y + 1};
    g_card.OpenTyped(anchor, text, now);
    DeactivatePointer(now, false);
    RequestTick();
}

void OnShake(POINT pt) {
    const double now = NowMs();
    if (g_state == PointerState::Off) {
        if (!CanSummonNow()) {
            return;
        }
        if (ShakeExcludedAt(pt)) {
            Wh_Log(L"Shake ignored: excluded app");
            return;
        }
    }
    Wh_Log(L"Shake at %d,%d", pt.x, pt.y);
    ActivatePointer(pt, now);
}

void OnRawMouseInput() {
    if (!g_settings.shake) {
        return;
    }
    POINT pt;
    if (!GetCursorPos(&pt) ||
        (pt.x == g_lastRawPoint.x && pt.y == g_lastRawPoint.y)) {
        return;  // Clicks, the wheel, and movement that didn't move the cursor.
    }
    g_lastRawPoint = pt;
    if (AnyMouseButtonDown()) {
        g_shake.Clear();
        return;
    }
    HMONITOR monitor = MonitorFromPoint(pt, MONITOR_DEFAULTTONEAREST);
    if (monitor != g_shakeMonitor) {
        g_shakeMonitor = monitor;
        g_shakeDpiScale = GetMonitorDpi(monitor) / 96.0f;
    }
    if (g_shake.AddPoint(NowMs(), pt, g_shakeDpiScale)) {
        g_shake.Clear();
        OnShake(pt);
    }
}

void OnHotkey(int id, LPARAM lParam) {
    const double now = NowMs();
    if (id >= kHotkeyTypeFirst) {
        OnTypedKey(LOWORD(lParam), HIWORD(lParam), now);
        return;
    }
    if (id == kHotkeyEscape) {
        DeactivatePointer(now, false);
        return;
    }
    if (id != kHotkeyActivate) {
        return;
    }
    if (g_state != PointerState::Off) {
        DeactivatePointer(now, false);
        return;
    }
    CURSORINFO cursorInfo{};
    cursorInfo.cbSize = sizeof(cursorInfo);
    if (GetCursorInfo(&cursorInfo) && (cursorInfo.flags & CURSOR_SHOWING)) {
        ActivatePointer(cursorInfo.ptScreenPos, now);
    }
}

bool IsWindhawkUiWindow(HWND hwnd) {
    if (!hwnd || g_windhawkExecutable.empty()) {
        return false;
    }
    DWORD processId = 0;
    GetWindowThreadProcessId(hwnd, &processId);
    if (!processId || processId == GetCurrentProcessId()) {
        return false;
    }
    const std::wstring path = ProcessPathOfWindow(hwnd);
    return !path.empty() &&
           (_wcsicmp(path.c_str(), g_windhawkExecutable.c_str()) == 0 ||
            (!g_windhawkUiDirectory.empty() &&
             path.size() > g_windhawkUiDirectory.size() &&
             _wcsnicmp(path.c_str(), g_windhawkUiDirectory.c_str(),
                       g_windhawkUiDirectory.size()) == 0));
}

void RefreshShakePolling() {
    const HWND foreground = GetForegroundWindow();
    const HWND target = g_settings.shake && !g_stopping &&
                                IsWindhawkUiWindow(foreground)
                            ? foreground
                            : nullptr;
    if (target == g_shakePollingWindow) {
        return;
    }
    if (g_shakePollingWindow) {
        KillTimer(g_messageWindow, kShakePollingTimer);
        g_shakePollingWindow = nullptr;
    }
    g_shake.Clear();
    g_lastRawPoint = {LONG_MIN, LONG_MIN};
    if (target && g_messageWindow) {
        // Sample only while Windhawk's UI is foreground, providing a fallback
        // if background raw mouse input is unavailable. The normal handler
        // deduplicates raw and sampled positions and keeps all safety checks.
        if (SetTimer(g_messageWindow, kShakePollingTimer, 16, nullptr)) {
            g_shakePollingWindow = target;
        } else {
            Wh_Log(L"Windhawk UI shake timer failed: %u", GetLastError());
        }
    }
}

void CALLBACK ForegroundChanged(HWINEVENTHOOK, DWORD event, HWND, LONG, LONG,
                                DWORD, DWORD) {
    if (event == EVENT_SYSTEM_FOREGROUND && g_messageWindow && !g_stopping) {
        PostMessageW(g_messageWindow, WM_APP_FOREGROUND, 0, 0);
    }
}

void StopShakeMonitoring() {
    if (g_foregroundHook) {
        UnhookWinEvent(g_foregroundHook);
        g_foregroundHook = nullptr;
    }
    if (g_shakePollingWindow) {
        KillTimer(g_messageWindow, kShakePollingTimer);
        g_shakePollingWindow = nullptr;
    }
    g_shake.Clear();
    g_lastRawPoint = {LONG_MIN, LONG_MIN};
}

void ConfigureShakeMonitoring() {
    if (!g_settings.shake || g_stopping) {
        StopShakeMonitoring();
        return;
    }
    if (g_windhawkExecutable.empty()) {
        WCHAR executable[MAX_PATH];
        const DWORD length = GetModuleFileNameW(nullptr, executable, ARRAYSIZE(executable));
        if (length && length < ARRAYSIZE(executable)) {
            g_windhawkExecutable.assign(executable, length);
            const size_t slash = g_windhawkExecutable.find_last_of(L"\\/");
            if (slash != std::wstring::npos) {
                g_windhawkUiDirectory = g_windhawkExecutable.substr(0, slash + 1) + L"UI\\";
            }
        }
    }
    if (!g_foregroundHook) {
        g_foregroundHook = SetWinEventHook(
            EVENT_SYSTEM_FOREGROUND, EVENT_SYSTEM_FOREGROUND, nullptr,
            ForegroundChanged, 0, 0, WINEVENT_OUTOFCONTEXT);
        if (!g_foregroundHook) {
            Wh_Log(L"Foreground monitoring failed: %u", GetLastError());
        }
    }
    RefreshShakePolling();
}

void OnDisplayChanged() {
    const double now = NowMs();
    DeactivatePointer(now, false);
    g_frame.HideNow();
}

void RegisterActivationHotkey() {
    if (g_hotkeyRegistered) {
        UnregisterHotKey(g_messageWindow, kHotkeyActivate);
        g_hotkeyRegistered = false;
    }
    if (g_settings.hotkey.empty()) {
        return;
    }
    UINT modifiers;
    UINT key;
    if (!::Hotkey_Parse(g_settings.hotkey, modifiers, key) &&
        !ParseHotkey(g_settings.hotkey, modifiers, key)) {
        Wh_Log(L"Couldn't understand the shortcut \"%s\"", g_settings.hotkey.c_str());
        return;
    }
    g_hotkeyRegistered = RegisterHotKey(g_messageWindow, kHotkeyActivate,
                                        modifiers | MOD_NOREPEAT, key);
    if (!g_hotkeyRegistered) {
        Wh_Log(L"The shortcut %s is taken by another app (error %u)",
               g_settings.hotkey.c_str(), GetLastError());
    }
}

void ApplySettings(const Settings& settings) {
    const double now = NowMs();
    DeactivatePointer(now, false);
    g_ripple.Stop();
    g_settings = settings;
    ClearUnavailableModels();
    SetLanguage(g_settings.language);
    g_glow = ParseGlowColor(g_settings.glowColor);
    ReadCornerRadius();
    g_styleVersion++;
    g_cursors.Clear();
    g_cursors.SetCustom(LoadCustomCursor(g_settings.customCursor));
    g_shake.Configure(g_settings.sensitivity);
    ConfigureShakeMonitoring();
    RegisterActivationHotkey();
    g_card.OnSettingsChanged(now);
}

double TickAll(double now) {
    double next = std::min(CleanupGeminiFiles(now), CleanupLensPages(now));
    if (g_state != PointerState::Off) {
        UpdatePointerCursor(now);
        next = std::min(next, g_cursors.NextChange(now));
        POINT cursorPosition;
        if (g_revealPending && !g_ripple.Capturing() && GetCursorPos(&cursorPosition)) {
            RevealPointerHelpers(cursorPosition, now);
        }
        if (g_pill.Visible() && now - g_pill.ShownAt() >= kHintMs) {
            g_pill.FadeOut(now);
        } else if (g_pill.Visible()) {
            next = std::min(next, kHintMs - (now - g_pill.ShownAt()));
        }
        if (g_settings.timeoutSec > 0 && g_state == PointerState::Pointing) {
            const double timeout = g_settings.timeoutSec * 1000.0;
            const double idle = now - g_lastActivity;
            if (idle >= timeout) {
                DeactivatePointer(now, false);
            } else {
                next = std::min(next, timeout - idle);
            }
        }
    }

    if (g_state == PointerState::Off && g_frame.Visible() &&
        g_frame.Style() == FrameStyle::Selected) {
        const double age = now - g_selectedAt;
        const bool working = g_card.IsOpen() && g_card.IsWaiting();
        if (age > 1200.0 && (!working || age > 12000.0)) {
            g_frame.FadeOut(now);
        }
    }

    next = std::min(next, g_overlay.Tick(now));
    if (!g_rippleTimer) {
        next = std::min(next, g_ripple.Tick(now));
    }
    next = std::min(next, g_pill.Tick(now));
    next = std::min(next, g_frame.Tick(now));
    next = std::min(next, g_card.Tick(now));
    return next;
}

void OnTimer() {
    g_timerArmed = false;
    const double now = NowMs();
    g_lastTick = now;
    const double next = TickAll(now);
    ArrangeLayers();
    if (next < 1e8) {
        const double finished = NowMs();
        ArmTimer(std::max(now + std::max(next, kFrameMs), finished), finished);
    }
}

void OnRippleTimer() {
    g_rippleTimerArmed = false;
    const double now = NowMs();
    const double next = g_ripple.Tick(now);
    if (next < 1e8) {
        const double finished = NowMs();
        ArmRippleTimer(std::max(now + next, finished), finished);
    }
}

////////////////////////////////////////////////////////////////////////////////
// Worker thread

HANDLE g_workerThread;
HANDLE g_workerReadyEvent;

LRESULT CALLBACK LayerWndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
    if (message == WM_MOUSEACTIVATE) {
        return MA_NOACTIVATE;
    }
    return DefWindowProcW(hwnd, message, wParam, lParam);
}

void Shutdown() {
    StopShakeMonitoring();
    const double now = NowMs();
    DeactivatePointer(now, false);
    UnregisterTypingKeys();
    g_card.Destroy();
    g_frame.Destroy();
    g_ripple.Destroy();
    g_pill.Destroy();
    g_overlay.Destroy();
    g_picker.Stop();
    g_cursors.Clear();
    if (g_hotkeyRegistered) {
        UnregisterHotKey(g_messageWindow, kHotkeyActivate);
        g_hotkeyRegistered = false;
    }
    RAWINPUTDEVICE device{};
    device.usUsagePage = 0x01;  // HID_USAGE_PAGE_GENERIC
    device.usUsage = 0x02;      // HID_USAGE_GENERIC_MOUSE
    device.dwFlags = RIDEV_REMOVE;
    device.hwndTarget = nullptr;
    RegisterRawInputDevices(&device, 1, sizeof(device));
}

LRESULT CALLBACK MessageWndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
        case WM_INPUT:
            OnRawMouseInput();
            break;  // DefWindowProc still has to clean up the input.

        case WM_HOTKEY:
            if (HWND listening = ::snpset::RecordingKeyWindow()) {
                PostMessageW(listening, WM_KEYDOWN, HIWORD(lParam), 1);
                return 0;
            }
            OnHotkey(static_cast<int>(wParam), lParam);
            return 0;

        case WM_APP_SUMMON:
            OnHotkey(kHotkeyActivate, 0);
            return 0;

        case WM_TIMER:
            if (wParam == kShakePollingTimer && g_shakePollingWindow) {
                if (GetForegroundWindow() != g_shakePollingWindow) {
                    RefreshShakePolling();
                } else {
                    OnRawMouseInput();
                }
            }
            return 0;

        case WM_APP_FOREGROUND:
            RefreshShakePolling();
            return 0;

        case WM_APP_SETTINGS: {
            std::unique_ptr<Settings> settings(reinterpret_cast<Settings*>(lParam));
            ApplySettings(*settings);
            return 0;
        }

        case WM_APP_PICK:
            OnPickResult(std::unique_ptr<PickResult>(reinterpret_cast<PickResult*>(lParam)));
            return 0;

        case WM_APP_RIPPLE:
            OnRippleCapture(std::unique_ptr<RippleCaptureMessage>(
                reinterpret_cast<RippleCaptureMessage*>(lParam)));
            return 0;

        case WM_APP_AI:
            g_card.OnAiMessage(
                std::unique_ptr<AiMessage>(reinterpret_cast<AiMessage*>(lParam)),
                NowMs());
            return 0;

        case WM_APP_BROWSER:
            g_card.OnBrowserHandoff(
                std::unique_ptr<BrowserHandoffMessage>(reinterpret_cast<BrowserHandoffMessage*>(lParam)),
                NowMs());
            return 0;

        case WM_APP_TEMP_FILE:
            RequestTick();
            return 0;

        case WM_APP_OCR: {
            std::unique_ptr<OcrResultMessage> result(
                reinterpret_cast<OcrResultMessage*>(lParam));
            g_card.OnOcrResult(result->attachmentId, std::move(result->text), NowMs());
            return 0;
        }

        case WM_CLOSE:
            DestroyWindow(hwnd);
            return 0;

        case WM_DESTROY:
            Shutdown();
            PostQuitMessage(0);
            return 0;
    }
    return DefWindowProcW(hwnd, message, wParam, lParam);
}

bool RegisterWindowClasses() {
    WNDCLASSEXW wc{};
    wc.cbSize = sizeof(wc);
    wc.hInstance = g_instance;

    wc.lpfnWndProc = MessageWndProc;
    wc.lpszClassName = kMessageWindowClass;
    if (!RegisterClassExW(&wc)) {
        return false;
    }

    wc.lpfnWndProc = LayerWndProc;
    wc.lpszClassName = kLayerWindowClass;
    if (!RegisterClassExW(&wc)) {
        return false;
    }

    wc.lpfnWndProc = InputOverlay::WndProc;
    wc.lpszClassName = kOverlayWindowClass;
    wc.hbrBackground = static_cast<HBRUSH>(GetStockObject(BLACK_BRUSH));
    if (!RegisterClassExW(&wc)) {
        return false;
    }

    wc.lpfnWndProc = AskCard::WndProc;
    wc.lpszClassName = kCardWindowClass;
    wc.style = CS_DBLCLKS;
    wc.hbrBackground = nullptr;
    wc.hCursor = LoadCursorW(nullptr, IDC_ARROW);
    return RegisterClassExW(&wc) != 0;
}

void UnregisterWindowClasses() {
    UnregisterClassW(kMessageWindowClass, g_instance);
    UnregisterClassW(kLayerWindowClass, g_instance);
    UnregisterClassW(kOverlayWindowClass, g_instance);
    UnregisterClassW(kCardWindowClass, g_instance);
}

#ifndef CREATE_WAITABLE_TIMER_HIGH_RESOLUTION
#define CREATE_WAITABLE_TIMER_HIGH_RESOLUTION 0x00000002
#endif

DWORD WINAPI WorkerThreadProc(LPVOID) {
    const HRESULT coInit = CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED);
    g_fonts.Init();
    g_glow = ParseGlowColor(g_settings.glowColor);

    auto fail = [&](PCWSTR what) {
        Wh_Log(L"%s failed: %u", what, GetLastError());
        StopShakeMonitoring();
        if (g_messageWindow) {
            DestroyWindow(g_messageWindow);
            g_messageWindow = nullptr;
        }
        UnregisterWindowClasses();
        if (SUCCEEDED(coInit)) {
            CoUninitialize();
        }
        SetEvent(g_workerReadyEvent);
        return 1;
    };

    if (!RegisterWindowClasses()) {
        return fail(L"RegisterClassExW");
    }
    g_messageWindow = CreateWindowExW(0, kMessageWindowClass, L"", 0, 0, 0, 0, 0,
                                      HWND_MESSAGE, nullptr, g_instance, nullptr);
    if (!g_messageWindow) {
        return fail(L"CreateWindowExW");
    }

    g_timer = CreateWaitableTimerExW(nullptr, nullptr,
                                     CREATE_WAITABLE_TIMER_HIGH_RESOLUTION,
                                     TIMER_ALL_ACCESS);
    g_highResolutionTimer = g_timer != nullptr;
    if (!g_timer) {
        g_timer = CreateWaitableTimerExW(nullptr, nullptr, 0, TIMER_ALL_ACCESS);
    }
    if (!g_timer) {
        return fail(L"CreateWaitableTimerExW");
    }
    g_rippleTimer = CreateWaitableTimerExW(
        nullptr, nullptr, g_highResolutionTimer ? CREATE_WAITABLE_TIMER_HIGH_RESOLUTION : 0,
        TIMER_ALL_ACCESS);

    RAWINPUTDEVICE device{};
    device.usUsagePage = 0x01;  // HID_USAGE_PAGE_GENERIC
    device.usUsage = 0x02;      // HID_USAGE_GENERIC_MOUSE
    device.dwFlags = RIDEV_INPUTSINK;
    device.hwndTarget = g_messageWindow;
    if (!RegisterRawInputDevices(&device, 1, sizeof(device))) {
        CloseHandle(g_timer);
        g_timer = nullptr;
        if (g_rippleTimer) {
            CloseHandle(g_rippleTimer);
            g_rippleTimer = nullptr;
        }
        return fail(L"RegisterRawInputDevices");
    }

    if (!g_overlay.Create()) {
        Wh_Log(L"Couldn't create the overlay: %u", GetLastError());
    }
    g_shake.Configure(g_settings.sensitivity);
    ConfigureShakeMonitoring();
    RegisterActivationHotkey();
    SetEvent(g_workerReadyEvent);
    g_cursors.SetCustom(LoadCustomCursor(g_settings.customCursor));

    const HANDLE timers[2] = {g_timer, g_rippleTimer};
    const DWORD timerCount = g_rippleTimer ? 2 : 1;
    bool running = true;
    while (running) {
        const DWORD result = MsgWaitForMultipleObjectsEx(
            timerCount, timers, INFINITE, QS_ALLINPUT, MWMO_INPUTAVAILABLE);
        if (result > WAIT_OBJECT_0 + timerCount) {
            Wh_Log(L"MsgWaitForMultipleObjectsEx failed: %u", GetLastError());
            break;
        }
        const bool timerDue =
            result == WAIT_OBJECT_0 || WaitForSingleObject(g_timer, 0) == WAIT_OBJECT_0;
        const bool rippleDue =
            g_rippleTimer && (result == WAIT_OBJECT_0 + 1 ||
                              WaitForSingleObject(g_rippleTimer, 0) == WAIT_OBJECT_0);
        if (timerDue) {
            OnTimer();
        }
        if (rippleDue) {
            OnRippleTimer();
        }
        bool tick = false;
        MSG msg;
        while (PeekMessageW(&msg, nullptr, 0, 0, PM_REMOVE)) {
            if (msg.message == WM_QUIT) {
                running = false;
                break;
            }
            if (msg.message != WM_INPUT) {
                tick = true;
            }
            TranslateMessage(&msg);
            DispatchMessageW(&msg);
        }
        if (running && tick && AnythingActive()) {
            RequestTick();
        }
        if (running) {
            ArrangeLayers();
        }
    }

    if (g_messageWindow && IsWindow(g_messageWindow)) {
        DestroyWindow(g_messageWindow);  // Only if the loop failed.
    }
    g_messageWindow = nullptr;
    g_fonts.Clear();
    CloseHandle(g_timer);
    g_timer = nullptr;
    if (g_rippleTimer) {
        CloseHandle(g_rippleTimer);
        g_rippleTimer = nullptr;
    }
    UnregisterWindowClasses();
    if (SUCCEEDED(coInit)) {
        CoUninitialize();
    }
    return 0;
}




// --- Seamless Snipper hooks -----------------------------------------------------------------

bool Enabled() { return Wh_GetIntSetting(L"pointerOn") != 0; }

std::wstring HotkeyLabel() {
    PCWSTR value = Wh_GetStringSetting(L"pointerHotkey");
    std::wstring text = value ? value : L"";
    if (value) Wh_FreeStringSetting(value);
    return Trim(text);
}

// From Snipper's tray menu: the same as pressing the key.
void Summon() {
    if (g_messageWindow) PostMessageW(g_messageWindow, WM_APP_SUMMON, 0, 0);
}

BOOL ToolInit() {
    ReadCornerRadius();
    Wh_Log(L">");
    g_instance = GetModuleHandleW(nullptr);
    g_settings = LoadSettings();
    SetLanguage(g_settings.language);

    // Remove captures that 1.0.10 and older left in the shared mod storage.
    WCHAR storage[MAX_PATH];
    if (Wh_GetModStoragePath(storage, ARRAYSIZE(storage)) && IsPlainDirectory(storage)) {
        g_storageDir = storage;
        DeleteExpiredGeminiFiles(true);
        DeleteOldLensPages(true);
    }
    g_storageDir = PrivateCaptureDirectory();
    if (g_storageDir.empty()) {
        Wh_Log(L"Private capture folder unavailable; browser handoff and Lens are off");
    } else {
        DeleteExpiredGeminiFiles();
        DeleteOldLensPages(false);
    }

    g_workerReadyEvent = CreateEventW(nullptr, TRUE, FALSE, nullptr);
    if (!g_workerReadyEvent) {
        return FALSE;
    }
    g_workerThread = CreateThread(nullptr, 0, WorkerThreadProc, nullptr, 0, nullptr);
    if (!g_workerThread) {
        return FALSE;
    }
    HANDLE handles[] = {g_workerReadyEvent, g_workerThread};
    WaitForMultipleObjects(ARRAYSIZE(handles), handles, FALSE, INFINITE);
    if (g_messageWindow) PostMessageW(g_messageWindow, WM_APP_TEMP_FILE, 0, 0);
    return g_messageWindow != nullptr;
}

void ToolSettingsChanged() {
    Wh_Log(L">");
    PostOwned(g_messageWindow, WM_APP_SETTINGS,
              std::make_unique<Settings>(LoadSettings()));
}

void ToolUninit() {
    Wh_Log(L">");
    g_stopping = true;
    if (g_messageWindow) {
        PostMessageW(g_messageWindow, WM_CLOSE, 0, 0);
    }
    if (g_workerThread) {
        WaitForSingleObject(g_workerThread, 5000);
        CloseHandle(g_workerThread);
        g_workerThread = nullptr;
    }
    for (int i = 0; i < 40 && g_helperThreads > 0; i++) {
        Sleep(50);
    }
    if (g_helperThreads == 0) {
        CloseApiSession();
    }
    DeleteExpiredGeminiFiles(true);
    DeleteOldLensPages(true);
}

////////////////////////////////////////////////////////////////////////////////
// Translations

const TextEntry kTexts_ar[] = {
    {Str::HintText, L"حدد أي شيء لتسأل {0} عنه"},
    {Str::HintTextTyping, L"حدد أي شيء أو ابدأ الكتابة لتسأل {0}"},
    {Str::Close, L"إغلاق"},
    {Str::AskInGemini, L"اسأل Gemini"},
    {Str::SearchWithLens, L"البحث باستخدام Google Lens"},
    {Str::TranslateTo, L"الترجمة إلى: {0}"},
    {Str::CopyImage, L"نسخ الصورة"},
    {Str::CopyText, L"نسخ النص"},
    {Str::AddSelection, L"إضافة تحديد آخر"},
    {Str::WhatIsThis, L"ما هذا؟"},
    {Str::ExplainThis, L"اشرح لي هذا"},
    {Str::SummarizeThis, L"لخص لي هذا"},
    {Str::AskPlaceholder, L"اسأل عن العنصر المحدد…"},
    {Str::AskAnythingPlaceholder, L"اسأل أي شيء…"},
    {Str::FollowUpPlaceholder, L"اطرح سؤالا آخر…"},
    {Str::Thinking, L"جارٍ التفكير…"},
    {Str::Copy, L"نسخ"},
    {Str::SelectAll, L"تحديد الكل"},
    {Str::NoApiKeyHint, L"أضف مفتاح API لـ Gemini أو ChatGPT أو Claude في إعدادات المود لتظهر الإجابات هنا مباشرة."},
    {Str::ImageCopied, L"تم نسخ الصورة"},
    {Str::ImageCopyFailed, L"تعذر نسخ الصورة"},
    {Str::ImageCopyRetry, L"تعذر نسخ الصورة. حاول مرة أخرى."},
    {Str::ReadingText, L"جارٍ قراءة النص…"},
    {Str::NoTextFound, L"لم يتم العثور على نص في التحديد"},
    {Str::TextCopied, L"تم نسخ النص"},
    {Str::TextCopyFailed, L"تعذر نسخ النص"},
    {Str::AnswerCopied, L"تم نسخ الإجابة"},
    {Str::AnswerCopyFailed, L"تعذر نسخ الإجابة"},
    {Str::OpeningLens, L"جارٍ فتح Google Lens في المتصفح…"},
    {Str::OpeningGeminiOne, L"جارٍ فتح Gemini وإرفاق صورتك…"},
    {Str::OpeningGeminiMany, L"جارٍ فتح Gemini وإرفاق صورك…"},
    {Str::OpeningGeminiText, L"جارٍ فتح Gemini وإضافة سؤالك…"},
    {Str::ClickBoxToAttach, L"انقر على حقل الرسالة في Gemini ثم اضغط Ctrl+V لإرفاق الصورة."},
    {Str::Stopped, L"تم الإيقاف."},
    {Str::StoppedEarly, L"تم الإيقاف قبل اكتمال الإجابة."},
    {Str::RequestFailed, L"تعذر بدء الطلب."},
    {Str::DraftAddedOne, L"تمت إضافة الصورة. اكتب سؤالك في Gemini."},
    {Str::DraftAddedMany, L"تمت إضافة الصور. اكتب سؤالك في Gemini."},
    {Str::QuestionInGemini, L"تم إدخال سؤالك في Gemini."},
    {Str::DraftPartial, L"الصور المؤكدة: {0} من {1}. تحقق من Gemini وأضف الباقي بالضغط على Ctrl+V في حقل الرسالة."},
    {Str::ClipboardChangedOne, L"تغيرت الحافظة قبل لصق الصورة: استخدم «نسخ الصورة» ثم اضغط Ctrl+V في Gemini."},
    {Str::ClipboardChangedMany, L"تغيرت الحافظة قبل لصق الصور. اسأل Gemini مرة أخرى لإعادة المحاولة."},
    {Str::IfNotAttachedOne, L"إذا لم يتم إرفاق الصورة، فانقر على حقل الرسالة في Gemini ثم اضغط Ctrl+V."},
    {Str::IfNotAttachedMany, L"إذا لم يتم إرفاق الصور، فانقر على حقل الرسالة في Gemini ثم اضغط Ctrl+V."},
    {Str::ClickBoxOne, L"انقر على حقل الرسالة في Gemini ثم اضغط Ctrl+V لإرفاق الصورة. سيبقى سؤالك هنا."},
    {Str::ClickBoxMany, L"انقر على حقل الرسالة في Gemini ثم اضغط Ctrl+V لإرفاق الصور. سيبقى سؤالك هنا."},
    {Str::ClickBoxText, L"انقر على حقل الرسالة في Gemini ثم اكتب سؤالك. سيبقى سؤالك هنا."},
    {Str::BrowserFailedOne, L"تعذر فتح المتصفح. تم نسخ الصورة؛ الصقها في Gemini بالضغط على Ctrl+V."},
    {Str::BrowserFailedMany, L"تعذر فتح المتصفح. تم نسخ الصور؛ الصقها في Gemini بالضغط على Ctrl+V."},
    {Str::BrowserFailedText, L"تعذر فتح المتصفح."},
    {Str::PageUnreadable, L"لم يتمكن Magic Pointer من قراءة الصفحة في متصفحك. إذا كان هناك إشعار مفتوح فوقها، فأغلقه ثم انقر على «اسأل Gemini» مرة أخرى."},
    {Str::ErrKeyInvalid, L"مفتاح {0} API غير صالح. تحقق منه في إعدادات المود."},
    {Str::ErrKeyForbidden, L"لا يمكن لمفتاح API هذا استخدام {0} (403). تحقق من المفتاح في إعدادات المود."},
    {Str::ErrModelMissing, L"النموذج «{0}» غير متاح لمفتاحك. اختر نموذجا آخر في إعدادات المود."},
    {Str::ErrNoFreeQuota, L"لا تتضمن خطة Gemini الخاصة بك حصة مجانية للنموذج «{0}». اختر النموذج «سريع» في إعدادات المود، أو أضف الفوترة إلى مفتاحك."},
    {Str::ErrNoCredit, L"نفد رصيد حسابك في {0}. أضف رصيدا أو طريقة دفع ثم حاول مرة أخرى."},
    {Str::ErrTimeout, L"لم يرد {0} في الوقت المناسب. حاول مرة أخرى بعد قليل."},
    {Str::ModelBusy, L"النموذج الذي اخترته غير متاح حاليا. يجيب نموذج أسرع بدلا منه."},
    {Str::ErrRateLimit, L"وصلت إلى حد طلبات {0} حاليا. حاول مرة أخرى بعد قليل."},
    {Str::ErrServer, L"يواجه {0} مشكلة حاليا ({1}). حاول مرة أخرى بعد قليل."},
    {Str::ErrGeneric, L"أعاد {0} خطأ ({1})."},
    {Str::ErrNoConnection, L"تعذر استلام رد {0}. تحقق من اتصالك بالإنترنت (الخطأ {1}) ثم حاول السؤال مرة أخرى."},
    {Str::ErrInterrupted, L"انقطع الاتصال بـ {0}، والإجابة غير مكتملة (الخطأ {1}). حاول السؤال مرة أخرى."},
    {Str::ErrInterruptedBy, L"قاطع {0} هذه الإجابة: {1}"},
    {Str::ErrUnreadable, L"أعاد {0} ردا غير قابل للقراءة. حاول السؤال مرة أخرى."},
    {Str::ErrOutputLimit, L"بلغ {0} الحد الأقصى للإجابة، والإجابة غير مكتملة. حاول طلب إجابة أقصر."},
    {Str::ErrStoppedBecause, L"أوقف {0} هذه الإجابة ({1}). حاول صياغة السؤال بطريقة أخرى."},
    {Str::ErrUnconfirmed, L"توقف {0} قبل التأكد من اكتمال الإجابة. حاول السؤال مرة أخرى."},
    {Str::ErrNoAnswer, L"لم يقدم {0} أي إجابة. حاول صياغة السؤال بطريقة أخرى."},
    {Str::ErrCouldntReach, L"تعذر الاتصال بـ {0}. تحقق من اتصالك بالإنترنت (الخطأ {1})."},
    {Str::ErrStreaming, L"أعاد {0} خطأ في البث."},
    {Str::LensSearching, L"جارٍ البحث باستخدام Google Lens…"},
    {Str::LensUploadFailed, L"تعذر التحميل تلقائيا. الصورة موجودة في الحافظة: الصقها في lens.google.com."},
};

const TextEntry kTexts_bn[] = {
    {Str::HintText, L"এআই-কে জিজ্ঞাসা করতে যেকোনো কিছু বেছে নিন ({0})"},
    {Str::HintTextTyping, L"এআই-কে জিজ্ঞাসা করতে যেকোনো কিছু বেছে নিন বা টাইপ শুরু করুন ({0})"},
    {Str::Close, L"বন্ধ করুন"},
    {Str::AskInGemini, L"Gemini-তে জিজ্ঞাসা করুন"},
    {Str::SearchWithLens, L"Google Lens দিয়ে খুঁজুন"},
    {Str::TranslateTo, L"অনুবাদের ভাষা: {0}"},
    {Str::CopyImage, L"ছবি কপি করুন"},
    {Str::CopyText, L"টেক্সট কপি করুন"},
    {Str::AddSelection, L"আরেকটি নির্বাচন যোগ করুন"},
    {Str::WhatIsThis, L"এটা কী?"},
    {Str::ExplainThis, L"এটা আমাকে বুঝিয়ে দিন"},
    {Str::SummarizeThis, L"এটার সারসংক্ষেপ দিন"},
    {Str::AskPlaceholder, L"আপনার নির্বাচিত অংশ সম্পর্কে জিজ্ঞাসা করুন…"},
    {Str::AskAnythingPlaceholder, L"যেকোনো কিছু জিজ্ঞাসা করুন…"},
    {Str::FollowUpPlaceholder, L"আরও কিছু জিজ্ঞাসা করুন…"},
    {Str::Thinking, L"ভাবছি…"},
    {Str::Copy, L"কপি করুন"},
    {Str::SelectAll, L"সব নির্বাচন করুন"},
    {Str::NoApiKeyHint, L"এখানেই উত্তর পেতে মডের সেটিংসে Gemini, ChatGPT বা Claude-এর একটি API কী যোগ করুন।"},
    {Str::ImageCopied, L"ছবি কপি হয়েছে"},
    {Str::ImageCopyFailed, L"ছবি কপি করা যায়নি"},
    {Str::ImageCopyRetry, L"ছবি কপি করা যায়নি। আবার চেষ্টা করুন।"},
    {Str::ReadingText, L"টেক্সট এখনও পড়া হচ্ছে…"},
    {Str::NoTextFound, L"নির্বাচিত অংশে কোনো টেক্সট পাওয়া যায়নি"},
    {Str::TextCopied, L"টেক্সট কপি হয়েছে"},
    {Str::TextCopyFailed, L"টেক্সট কপি করা যায়নি"},
    {Str::AnswerCopied, L"উত্তর কপি হয়েছে"},
    {Str::AnswerCopyFailed, L"উত্তর কপি করা যায়নি"},
    {Str::OpeningLens, L"আপনার ব্রাউজারে Google Lens খুলছে…"},
    {Str::OpeningGeminiOne, L"Gemini খুলে ছবিটি অ্যাটাচ করা হচ্ছে…"},
    {Str::OpeningGeminiMany, L"Gemini খুলে ছবিগুলো অ্যাটাচ করা হচ্ছে…"},
    {Str::OpeningGeminiText, L"Gemini খুলে আপনার প্রশ্ন যোগ করা হচ্ছে…"},
    {Str::ClickBoxToAttach, L"Gemini-র মেসেজ বক্সে ক্লিক করুন, তারপর ছবিটি অ্যাটাচ করতে Ctrl+V চাপুন।"},
    {Str::Stopped, L"থামানো হয়েছে।"},
    {Str::StoppedEarly, L"উত্তর শেষ হওয়ার আগেই থামানো হয়েছে।"},
    {Str::RequestFailed, L"অনুরোধ শুরু করা যায়নি।"},
    {Str::DraftAddedOne, L"ছবি যোগ হয়েছে। এবার Gemini-তে আপনার প্রশ্ন লিখুন।"},
    {Str::DraftAddedMany, L"ছবিগুলো যোগ হয়েছে। এবার Gemini-তে আপনার প্রশ্ন লিখুন।"},
    {Str::QuestionInGemini, L"আপনার প্রশ্ন Gemini-তে লেখা হয়ে গেছে।"},
    {Str::DraftPartial, L"{1}টির মধ্যে {0}টি ছবি নিশ্চিত হয়েছে। Gemini দেখে নিন এবং বাকিগুলো তার মেসেজ বক্সে Ctrl+V দিয়ে পেস্ট করুন।"},
    {Str::ClipboardChangedOne, L"ছবি পেস্ট করার আগেই ক্লিপবোর্ড বদলে গেছে: \"ছবি কপি করুন\" ব্যবহার করে Gemini-তে Ctrl+V চাপুন।"},
    {Str::ClipboardChangedMany, L"ছবিগুলো পেস্ট করার আগেই ক্লিপবোর্ড বদলে গেছে। আবার চেষ্টা করতে Gemini-তে নতুন করে জিজ্ঞাসা করুন।"},
    {Str::IfNotAttachedOne, L"ছবি অ্যাটাচ না হলে Gemini-র মেসেজ বক্সে ক্লিক করে Ctrl+V চাপুন।"},
    {Str::IfNotAttachedMany, L"ছবিগুলো অ্যাটাচ না হলে Gemini-র মেসেজ বক্সে ক্লিক করে Ctrl+V চাপুন।"},
    {Str::ClickBoxOne, L"Gemini-র মেসেজ বক্সে ক্লিক করে ছবিটি অ্যাটাচ করতে Ctrl+V চাপুন। আপনার প্রশ্ন এখানেই থাকবে।"},
    {Str::ClickBoxMany, L"Gemini-র মেসেজ বক্সে ক্লিক করে ছবিগুলো অ্যাটাচ করতে Ctrl+V চাপুন। আপনার প্রশ্ন এখানেই থাকবে।"},
    {Str::ClickBoxText, L"Gemini-র মেসেজ বক্সে ক্লিক করে আপনার প্রশ্ন টাইপ করুন। আপনার প্রশ্ন এখানেই থাকবে।"},
    {Str::BrowserFailedOne, L"ব্রাউজার খোলা যায়নি। ছবি কপি করা আছে; Ctrl+V দিয়ে Gemini-তে পেস্ট করুন।"},
    {Str::BrowserFailedMany, L"ব্রাউজার খোলা যায়নি। ছবিগুলো কপি করা আছে; Ctrl+V দিয়ে Gemini-তে পেস্ট করুন।"},
    {Str::BrowserFailedText, L"ব্রাউজার খোলা যায়নি।"},
    {Str::PageUnreadable, L"Magic Pointer আপনার ব্রাউজারের পেজটি পড়তে পারেনি। পেজের ওপর কোনো নোটিফিকেশন খোলা থাকলে সেটি বন্ধ করুন এবং আবার \"Gemini-তে জিজ্ঞাসা করুন\"-এ ক্লিক করুন।"},
    {Str::ErrKeyInvalid, L"আপনার {0} API কী সঠিক নয়। মডের সেটিংসে গিয়ে এটি দেখে নিন।"},
    {Str::ErrKeyForbidden, L"এই API কী দিয়ে {0} পরিষেবা ব্যবহার করা যাচ্ছে না (403)। মডের সেটিংসে কী-টি দেখে নিন।"},
    {Str::ErrModelMissing, L"\"{0}\" মডেলটি আপনার কী দিয়ে ব্যবহার করা যাচ্ছে না। মডের সেটিংসে অন্য একটি মডেল বেছে নিন।"},
    {Str::ErrNoFreeQuota, L"আপনার Gemini প্ল্যানে \"{0}\"-এর জন্য বিনামূল্যে ব্যবহারের সীমা নেই। মডের সেটিংসে \"দ্রুত\" মডেল বেছে নিন, অথবা কী-তে বিলিং চালু করুন।"},
    {Str::ErrNoCredit, L"আপনার {0} অ্যাকাউন্টের ক্রেডিট শেষ হয়ে গেছে। ক্রেডিট বা পেমেন্ট পদ্ধতি যোগ করে আবার চেষ্টা করুন।"},
    {Str::ErrTimeout, L"{0} পরিষেবা সময়মতো সাড়া দেয়নি। কিছুক্ষণ পর আবার চেষ্টা করুন।"},
    {Str::ModelBusy, L"আপনার বেছে নেওয়া মডেলটি এখন পাওয়া যাচ্ছে না। তার বদলে একটি দ্রুত মডেল উত্তর দিচ্ছে।"},
    {Str::ErrRateLimit, L"আপাতত {0} পরিষেবার অনুরোধের সীমা শেষ হয়ে গেছে। কিছুক্ষণ পর আবার চেষ্টা করুন।"},
    {Str::ErrServer, L"{0} পরিষেবায় এখন সমস্যা হচ্ছে ({1})। কিছুক্ষণ পর আবার চেষ্টা করুন।"},
    {Str::ErrGeneric, L"{0} পরিষেবা একটি ত্রুটি দেখিয়েছে ({1})।"},
    {Str::ErrNoConnection, L"{0} পরিষেবার উত্তর পাওয়া যায়নি। ইন্টারনেট সংযোগ দেখে নিন (ত্রুটি {1}) এবং আবার জিজ্ঞাসা করুন।"},
    {Str::ErrInterrupted, L"{0} পরিষেবার সঙ্গে সংযোগ বিচ্ছিন্ন হওয়ায় উত্তরটি অসম্পূর্ণ (ত্রুটি {1})। আবার জিজ্ঞাসা করুন।"},
    {Str::ErrInterruptedBy, L"{0} পরিষেবা উত্তরটি মাঝপথে থামিয়ে দিয়েছে: {1}"},
    {Str::ErrUnreadable, L"{0} পরিষেবা এমন উত্তর পাঠিয়েছে যা পড়া যাচ্ছে না। আবার জিজ্ঞাসা করুন।"},
    {Str::ErrOutputLimit, L"{0} পরিষেবার আউটপুটের সীমা শেষ হওয়ায় উত্তরটি অসম্পূর্ণ। ছোট উত্তর চেয়ে দেখুন।"},
    {Str::ErrStoppedBecause, L"{0} পরিষেবা উত্তরটি থামিয়ে দিয়েছে ({1})। অন্যভাবে প্রশ্ন করে দেখুন।"},
    {Str::ErrUnconfirmed, L"উত্তর সম্পূর্ণ হয়েছে কি না নিশ্চিত করার আগেই {0} পরিষেবা থেমে গেছে। আবার জিজ্ঞাসা করুন।"},
    {Str::ErrNoAnswer, L"{0} পরিষেবা কোনো উত্তর দেয়নি। অন্যভাবে প্রশ্ন করে দেখুন।"},
    {Str::ErrCouldntReach, L"{0} পরিষেবার সঙ্গে যোগাযোগ করা যায়নি। ইন্টারনেট সংযোগ দেখে নিন (ত্রুটি {1})।"},
    {Str::ErrStreaming, L"{0} পরিষেবায় স্ট্রিমিং ত্রুটি হয়েছে।"},
    {Str::LensSearching, L"Google Lens দিয়ে খোঁজা হচ্ছে…"},
    {Str::LensUploadFailed, L"নিজে থেকে আপলোড করা যায়নি। ছবিটি ক্লিপবোর্ডে আছে: lens.google.com-এ গিয়ে পেস্ট করুন।"},
};

const TextEntry kTexts_zh_CN[] = {
    {Str::HintText, L"选择任意内容，向 {0} 提问"},
    {Str::HintTextTyping, L"选择任意内容或直接开始输入，向 {0} 提问"},
    {Str::Close, L"关闭"},
    {Str::AskInGemini, L"在 Gemini 中提问"},
    {Str::SearchWithLens, L"使用 Google Lens 搜索"},
    {Str::TranslateTo, L"翻译为：{0}"},
    {Str::CopyImage, L"复制图片"},
    {Str::CopyText, L"复制文本"},
    {Str::AddSelection, L"添加另一个选区"},
    {Str::WhatIsThis, L"这是什么？"},
    {Str::ExplainThis, L"帮我解释一下"},
    {Str::SummarizeThis, L"帮我总结一下"},
    {Str::AskPlaceholder, L"询问有关所选内容的问题…"},
    {Str::AskAnythingPlaceholder, L"询问任何问题…"},
    {Str::FollowUpPlaceholder, L"继续追问…"},
    {Str::Thinking, L"正在思考…"},
    {Str::Copy, L"复制"},
    {Str::SelectAll, L"全选"},
    {Str::NoApiKeyHint, L"在 Mod 设置中添加 Gemini、ChatGPT 或 Claude 的 API 密钥，即可直接在此处获得回答。"},
    {Str::ImageCopied, L"图片已复制"},
    {Str::ImageCopyFailed, L"无法复制图片"},
    {Str::ImageCopyRetry, L"无法复制图片，请重试。"},
    {Str::ReadingText, L"仍在识别文本…"},
    {Str::NoTextFound, L"所选内容中未找到文本"},
    {Str::TextCopied, L"文本已复制"},
    {Str::TextCopyFailed, L"无法复制文本"},
    {Str::AnswerCopied, L"回答已复制"},
    {Str::AnswerCopyFailed, L"无法复制回答"},
    {Str::OpeningLens, L"正在浏览器中打开 Google Lens…"},
    {Str::OpeningGeminiOne, L"正在打开 Gemini 并附加图片…"},
    {Str::OpeningGeminiMany, L"正在打开 Gemini 并附加所有图片…"},
    {Str::OpeningGeminiText, L"正在打开 Gemini 并添加你的问题…"},
    {Str::ClickBoxToAttach, L"请单击 Gemini 的消息框，然后按 Ctrl+V 附加图片。"},
    {Str::Stopped, L"已停止。"},
    {Str::StoppedEarly, L"回答未完成就已停止。"},
    {Str::RequestFailed, L"无法启动请求。"},
    {Str::DraftAddedOne, L"图片已添加。请在 Gemini 中输入你的问题。"},
    {Str::DraftAddedMany, L"图片已全部添加。请在 Gemini 中输入你的问题。"},
    {Str::QuestionInGemini, L"你的问题已在 Gemini 中。"},
    {Str::DraftPartial, L"已确认图片：{0}/{1}。请检查 Gemini，并在其消息框中按 Ctrl+V 添加其余图片。"},
    {Str::ClipboardChangedOne, L"在粘贴图片之前剪贴板内容已更改：请使用“复制图片”，然后在 Gemini 中按 Ctrl+V。"},
    {Str::ClipboardChangedMany, L"在粘贴图片之前剪贴板内容已更改。请在 Gemini 中重新提问以重试。"},
    {Str::IfNotAttachedOne, L"如果图片未附加，请单击 Gemini 的消息框并按 Ctrl+V。"},
    {Str::IfNotAttachedMany, L"如果这些图片未附加，请单击 Gemini 的消息框并按 Ctrl+V。"},
    {Str::ClickBoxOne, L"请单击 Gemini 的消息框并按 Ctrl+V 附加图片。你的问题会保留在这里。"},
    {Str::ClickBoxMany, L"请单击 Gemini 的消息框并按 Ctrl+V 附加这些图片。你的问题会保留在这里。"},
    {Str::ClickBoxText, L"请单击 Gemini 的消息框并输入你的问题。你的问题会保留在这里。"},
    {Str::BrowserFailedOne, L"无法打开浏览器。图片已复制；请用 Ctrl+V 粘贴到 Gemini。"},
    {Str::BrowserFailedMany, L"无法打开浏览器。图片已复制；请用 Ctrl+V 将它们粘贴到 Gemini。"},
    {Str::BrowserFailedText, L"无法打开浏览器。"},
    {Str::PageUnreadable, L"Magic Pointer 无法读取浏览器中的页面。如果其上方打开了通知，请将其关闭，然后再次单击“在 Gemini 中提问”。"},
    {Str::ErrKeyInvalid, L"你的 {0} API 密钥无效。请在 Mod 设置中检查。"},
    {Str::ErrKeyForbidden, L"此 API 密钥无法使用 {0}（403）。请在 Mod 设置中检查该密钥。"},
    {Str::ErrModelMissing, L"模型“{0}”不适用于你的密钥。请在 Mod 设置中选择其他模型。"},
    {Str::ErrNoFreeQuota, L"你的 Gemini 方案没有“{0}”的免费配额。请在 Mod 设置中选择“快速”模型，或为你的密钥添加结算信息。"},
    {Str::ErrNoCredit, L"你的 {0} 账户余额已用完。请充值或添加付款方式，然后重试。"},
    {Str::ErrTimeout, L"{0} 未能及时响应。请稍后再试。"},
    {Str::ModelBusy, L"你选择的模型目前不可用，已改由更快的模型作答。"},
    {Str::ErrRateLimit, L"你暂时达到了 {0} 的请求上限。请稍后再试。"},
    {Str::ErrServer, L"{0} 目前出现问题（{1}）。请稍后再试。"},
    {Str::ErrGeneric, L"{0} 返回了错误（{1}）。"},
    {Str::ErrNoConnection, L"无法接收 {0} 的回答。请检查你的网络连接（错误 {1}）。请尝试重新提问。"},
    {Str::ErrInterrupted, L"与 {0} 的连接已中断。此回答不完整（错误 {1}）。请尝试重新提问。"},
    {Str::ErrInterruptedBy, L"{0} 中断了此回答：{1}"},
    {Str::ErrUnreadable, L"{0} 返回了无法读取的响应。请尝试重新提问。"},
    {Str::ErrOutputLimit, L"{0} 已达到输出上限。此回答不完整。请尝试要求更简短的回答。"},
    {Str::ErrStoppedBecause, L"{0} 停止了此回答（{1}）。请尝试换一种方式提问。"},
    {Str::ErrUnconfirmed, L"{0} 在确认回答完整之前就停止了。请尝试重新提问。"},
    {Str::ErrNoAnswer, L"{0} 没有返回回答。请尝试换一种方式提问。"},
    {Str::ErrCouldntReach, L"无法连接到 {0}。请检查你的网络连接（错误 {1}）。"},
    {Str::ErrStreaming, L"{0} 返回了流式传输错误。"},
    {Str::LensSearching, L"正在使用 Google Lens 搜索…"},
    {Str::LensUploadFailed, L"无法自动上传。图片已在剪贴板中：请将其粘贴到 lens.google.com。"},
};

const TextEntry kTexts_zh_TW[] = {
    {Str::HintText, L"選取任何內容即可詢問 {0}"},
    {Str::HintTextTyping, L"選取任何內容或直接開始輸入，即可詢問 {0}"},
    {Str::Close, L"關閉"},
    {Str::AskInGemini, L"在 Gemini 中詢問"},
    {Str::SearchWithLens, L"使用 Google Lens 搜尋"},
    {Str::TranslateTo, L"翻譯成：{0}"},
    {Str::CopyImage, L"複製圖片"},
    {Str::CopyText, L"複製文字"},
    {Str::AddSelection, L"新增另一個選取範圍"},
    {Str::WhatIsThis, L"這是什麼？"},
    {Str::ExplainThis, L"請幫我說明"},
    {Str::SummarizeThis, L"請幫我摘要"},
    {Str::AskPlaceholder, L"詢問有關所選內容的問題…"},
    {Str::AskAnythingPlaceholder, L"詢問任何問題…"},
    {Str::FollowUpPlaceholder, L"繼續追問…"},
    {Str::Thinking, L"思考中…"},
    {Str::Copy, L"複製"},
    {Str::SelectAll, L"全選"},
    {Str::NoApiKeyHint, L"在模組設定中新增 Gemini、ChatGPT 或 Claude 的 API 金鑰，即可直接在此取得回答。"},
    {Str::ImageCopied, L"已複製圖片"},
    {Str::ImageCopyFailed, L"無法複製圖片"},
    {Str::ImageCopyRetry, L"無法複製圖片，請再試一次。"},
    {Str::ReadingText, L"仍在辨識文字…"},
    {Str::NoTextFound, L"在所選內容中找不到文字"},
    {Str::TextCopied, L"已複製文字"},
    {Str::TextCopyFailed, L"無法複製文字"},
    {Str::AnswerCopied, L"已複製回答"},
    {Str::AnswerCopyFailed, L"無法複製回答"},
    {Str::OpeningLens, L"正在瀏覽器中開啟 Google Lens…"},
    {Str::OpeningGeminiOne, L"正在開啟 Gemini 並附加圖片…"},
    {Str::OpeningGeminiMany, L"正在開啟 Gemini 並附加所有圖片…"},
    {Str::OpeningGeminiText, L"正在開啟 Gemini 並加入您的問題…"},
    {Str::ClickBoxToAttach, L"請按一下 Gemini 的訊息方塊，然後按 Ctrl+V 以附加圖片。"},
    {Str::Stopped, L"已停止。"},
    {Str::StoppedEarly, L"回答尚未完成就已停止。"},
    {Str::RequestFailed, L"無法啟動要求。"},
    {Str::DraftAddedOne, L"已新增圖片。請在 Gemini 中輸入您的問題。"},
    {Str::DraftAddedMany, L"已新增所有圖片。請在 Gemini 中輸入您的問題。"},
    {Str::QuestionInGemini, L"您的問題已在 Gemini 中。"},
    {Str::DraftPartial, L"已確認的圖片：{0}/{1}。請檢查 Gemini，並在其訊息方塊中按 Ctrl+V 新增其餘圖片。"},
    {Str::ClipboardChangedOne, L"在貼上圖片之前，剪貼簿內容已變更：請使用「複製圖片」，然後在 Gemini 中按 Ctrl+V。"},
    {Str::ClipboardChangedMany, L"在貼上圖片之前，剪貼簿內容已變更。請在 Gemini 中重新詢問以再試一次。"},
    {Str::IfNotAttachedOne, L"如果圖片未附加，請按一下 Gemini 的訊息方塊並按 Ctrl+V。"},
    {Str::IfNotAttachedMany, L"如果這些圖片未附加，請按一下 Gemini 的訊息方塊並按 Ctrl+V。"},
    {Str::ClickBoxOne, L"請按一下 Gemini 的訊息方塊並按 Ctrl+V 以附加圖片。您的問題會保留在這裡。"},
    {Str::ClickBoxMany, L"請按一下 Gemini 的訊息方塊並按 Ctrl+V 以附加這些圖片。您的問題會保留在這裡。"},
    {Str::ClickBoxText, L"請按一下 Gemini 的訊息方塊並輸入您的問題。您的問題會保留在這裡。"},
    {Str::BrowserFailedOne, L"無法開啟瀏覽器。圖片已複製，請用 Ctrl+V 貼到 Gemini。"},
    {Str::BrowserFailedMany, L"無法開啟瀏覽器。圖片已複製，請用 Ctrl+V 將它們貼到 Gemini。"},
    {Str::BrowserFailedText, L"無法開啟瀏覽器。"},
    {Str::PageUnreadable, L"Magic Pointer 無法讀取瀏覽器中的頁面。如果上方開啟了通知，請將其關閉，然後再次按一下「在 Gemini 中詢問」。"},
    {Str::ErrKeyInvalid, L"您的 {0} API 金鑰無效。請在模組設定中檢查。"},
    {Str::ErrKeyForbidden, L"此 API 金鑰無法使用 {0}（403）。請在模組設定中檢查該金鑰。"},
    {Str::ErrModelMissing, L"模型「{0}」不適用於您的金鑰。請在模組設定中選擇其他模型。"},
    {Str::ErrNoFreeQuota, L"您的 Gemini 方案沒有「{0}」的免費配額。請在模組設定中選擇「快速」模型，或為您的金鑰新增計費資訊。"},
    {Str::ErrNoCredit, L"您的 {0} 帳戶餘額已用完。請儲值或新增付款方式，然後再試一次。"},
    {Str::ErrTimeout, L"{0} 未能及時回應。請稍後再試。"},
    {Str::ModelBusy, L"您選擇的模型目前無法使用，已改由較快的模型回答。"},
    {Str::ErrRateLimit, L"您暫時達到了 {0} 的要求上限。請稍後再試。"},
    {Str::ErrServer, L"{0} 目前發生問題（{1}）。請稍後再試。"},
    {Str::ErrGeneric, L"{0} 傳回了錯誤（{1}）。"},
    {Str::ErrNoConnection, L"無法接收 {0} 的回答。請檢查您的網際網路連線（錯誤 {1}）。請嘗試重新詢問。"},
    {Str::ErrInterrupted, L"與 {0} 的連線已中斷。此回答不完整（錯誤 {1}）。請嘗試重新詢問。"},
    {Str::ErrInterruptedBy, L"{0} 中斷了此回答：{1}"},
    {Str::ErrUnreadable, L"{0} 傳回了無法讀取的回應。請嘗試重新詢問。"},
    {Str::ErrOutputLimit, L"{0} 已達到輸出上限。此回答不完整。請嘗試要求較簡短的回答。"},
    {Str::ErrStoppedBecause, L"{0} 停止了此回答（{1}）。請嘗試換個方式詢問。"},
    {Str::ErrUnconfirmed, L"{0} 在確認回答完整之前就停止了。請嘗試重新詢問。"},
    {Str::ErrNoAnswer, L"{0} 沒有傳回回答。請嘗試換個方式詢問。"},
    {Str::ErrCouldntReach, L"無法連線到 {0}。請檢查您的網際網路連線（錯誤 {1}）。"},
    {Str::ErrStreaming, L"{0} 傳回了串流錯誤。"},
    {Str::LensSearching, L"正在使用 Google Lens 搜尋…"},
    {Str::LensUploadFailed, L"無法自動上傳。圖片已在剪貼簿中：請將其貼到 lens.google.com。"},
};

const TextEntry kTexts_hr[] = {
    {Str::HintText, L"Odaberi bilo što da pitaš {0}"},
    {Str::HintTextTyping, L"Odaberi bilo što ili počni tipkati da pitaš {0}"},
    {Str::Close, L"Zatvori"},
    {Str::AskInGemini, L"Pitaj Gemini"},
    {Str::SearchWithLens, L"Pretraži s Google Lensom"},
    {Str::TranslateTo, L"Prevedi na: {0}"},
    {Str::CopyImage, L"Kopiraj sliku"},
    {Str::CopyText, L"Kopiraj tekst"},
    {Str::AddSelection, L"Dodaj još jedan odabir"},
    {Str::WhatIsThis, L"Što je ovo?"},
    {Str::ExplainThis, L"Objasni mi ovo"},
    {Str::SummarizeThis, L"Sažmi mi ovo"},
    {Str::AskPlaceholder, L"Pitaj nešto o odabiru…"},
    {Str::AskAnythingPlaceholder, L"Pitaj bilo što…"},
    {Str::FollowUpPlaceholder, L"Postavi dodatno pitanje…"},
    {Str::Thinking, L"Razmišljam…"},
    {Str::Copy, L"Kopiraj"},
    {Str::SelectAll, L"Odaberi sve"},
    {Str::NoApiKeyHint, L"Dodaj API ključ za Gemini, ChatGPT ili Claude u postavkama dodatka kako bi odgovore dobivao ovdje."},
    {Str::ImageCopied, L"Slika je kopirana"},
    {Str::ImageCopyFailed, L"Slika se nije mogla kopirati"},
    {Str::ImageCopyRetry, L"Slika se nije mogla kopirati. Pokušaj ponovno."},
    {Str::ReadingText, L"Tekst se još čita…"},
    {Str::NoTextFound, L"U odabiru nije pronađen tekst"},
    {Str::TextCopied, L"Tekst je kopiran"},
    {Str::TextCopyFailed, L"Tekst se nije mogao kopirati"},
    {Str::AnswerCopied, L"Odgovor je kopiran"},
    {Str::AnswerCopyFailed, L"Odgovor se nije mogao kopirati"},
    {Str::OpeningLens, L"Otvaranje Google Lensa u pregledniku…"},
    {Str::OpeningGeminiOne, L"Otvaranje Geminija i prilaganje slike…"},
    {Str::OpeningGeminiMany, L"Otvaranje Geminija i prilaganje slika…"},
    {Str::OpeningGeminiText, L"Otvaranje Geminija i dodavanje tvog pitanja…"},
    {Str::ClickBoxToAttach, L"Klikni okvir za poruke u Geminiju i pritisni Ctrl+V da priložiš sliku."},
    {Str::Stopped, L"Zaustavljeno."},
    {Str::StoppedEarly, L"Zaustavljeno prije nego što je odgovor završio."},
    {Str::RequestFailed, L"Zahtjev se nije mogao pokrenuti."},
    {Str::DraftAddedOne, L"Slika je dodana. Upiši svoje pitanje u Gemini."},
    {Str::DraftAddedMany, L"Slike su dodane. Upiši svoje pitanje u Gemini."},
    {Str::QuestionInGemini, L"Tvoje pitanje je već u Geminiju."},
    {Str::DraftPartial, L"Potvrđene slike: {0} od {1}. Provjeri Gemini i dodaj ostale pomoću Ctrl+V u njegovu okviru za poruke."},
    {Str::ClipboardChangedOne, L"Međuspremnik se promijenio prije nego što se slika mogla zalijepiti: upotrijebi Kopiraj sliku, a zatim pritisni Ctrl+V u Geminiju."},
    {Str::ClipboardChangedMany, L"Međuspremnik se promijenio prije nego što su se slike mogle zalijepiti. Pitaj ponovno u Geminiju da pokušaš opet."},
    {Str::IfNotAttachedOne, L"Ako slika nije priložena, klikni okvir za poruke u Geminiju i pritisni Ctrl+V."},
    {Str::IfNotAttachedMany, L"Ako slike nisu priložene, klikni okvir za poruke u Geminiju i pritisni Ctrl+V."},
    {Str::ClickBoxOne, L"Klikni okvir za poruke u Geminiju i pritisni Ctrl+V da priložiš sliku. Tvoje pitanje ostaje ovdje."},
    {Str::ClickBoxMany, L"Klikni okvir za poruke u Geminiju i pritisni Ctrl+V da priložiš slike. Tvoje pitanje ostaje ovdje."},
    {Str::ClickBoxText, L"Klikni okvir za poruke u Geminiju i upiši svoje pitanje. Tvoje pitanje ostaje ovdje."},
    {Str::BrowserFailedOne, L"Preglednik se nije mogao otvoriti. Slika je kopirana; zalijepi je u Gemini pomoću Ctrl+V."},
    {Str::BrowserFailedMany, L"Preglednik se nije mogao otvoriti. Slike su kopirane; zalijepi ih u Gemini pomoću Ctrl+V."},
    {Str::BrowserFailedText, L"Preglednik se nije mogao otvoriti."},
    {Str::PageUnreadable, L"Magic Pointer nije mogao pročitati stranicu u tvom pregledniku. Ako je iznad nje otvorena obavijest, zatvori je i ponovno klikni Pitaj Gemini."},
    {Str::ErrKeyInvalid, L"Tvoj API ključ za {0} nije valjan. Provjeri ga u postavkama dodatka."},
    {Str::ErrKeyForbidden, L"Ovaj API ključ ne može koristiti uslugu {0} (403). Provjeri ključ u postavkama dodatka."},
    {Str::ErrModelMissing, L"Model „{0}” nije dostupan za tvoj ključ. Odaberi drugi model u postavkama dodatka."},
    {Str::ErrNoFreeQuota, L"Tvoj Gemini paket nema besplatnu kvotu za „{0}”. Odaberi model „Brzo” u postavkama dodatka ili dodaj naplatu svom ključu."},
    {Str::ErrNoCredit, L"Na tvom računu za uslugu {0} nema više sredstava. Dodaj sredstva ili način plaćanja pa pokušaj ponovno."},
    {Str::ErrTimeout, L"Usluga {0} nije odgovorila na vrijeme. Pokušaj ponovno za trenutak."},
    {Str::ModelBusy, L"Model koji si odabrao trenutačno nije dostupan. Umjesto njega odgovara brži model."},
    {Str::ErrRateLimit, L"Dosegnuto je ograničenje zahtjeva za uslugu {0}. Pokušaj ponovno za trenutak."},
    {Str::ErrServer, L"Usluga {0} trenutačno ima problema ({1}). Pokušaj ponovno za trenutak."},
    {Str::ErrGeneric, L"Usluga {0} vratila je pogrešku ({1})."},
    {Str::ErrNoConnection, L"Odgovor usluge {0} nije se mogao primiti. Provjeri internetsku vezu (pogreška {1}). Pokušaj ponovno postaviti pitanje."},
    {Str::ErrInterrupted, L"Veza s uslugom {0} prekinuta je. Ovaj je odgovor nepotpun (pogreška {1}). Pokušaj ponovno postaviti pitanje."},
    {Str::ErrInterruptedBy, L"Usluga {0} prekinula je ovaj odgovor: {1}"},
    {Str::ErrUnreadable, L"Usluga {0} vratila je nečitljiv odgovor. Pokušaj ponovno postaviti pitanje."},
    {Str::ErrOutputLimit, L"Usluga {0} dosegnula je ograničenje izlaza. Ovaj je odgovor nepotpun. Pokušaj zatražiti kraći odgovor."},
    {Str::ErrStoppedBecause, L"Usluga {0} zaustavila je ovaj odgovor ({1}). Pokušaj pitati na drugi način."},
    {Str::ErrUnconfirmed, L"Usluga {0} zaustavila se prije nego što je potvrdila da je odgovor potpun. Pokušaj ponovno postaviti pitanje."},
    {Str::ErrNoAnswer, L"Usluga {0} nije vratila odgovor. Pokušaj pitati na drugi način."},
    {Str::ErrCouldntReach, L"Usluga {0} nije dostupna. Provjeri internetsku vezu (pogreška {1})."},
    {Str::ErrStreaming, L"Usluga {0} vratila je pogrešku strujanja."},
    {Str::LensSearching, L"Pretraživanje s Google Lensom…"},
    {Str::LensUploadFailed, L"Automatsko učitavanje nije uspjelo. Slika je u međuspremniku: zalijepi je na lens.google.com."},
};

const TextEntry kTexts_cs[] = {
    {Str::HintText, L"Vyberte cokoli a zeptejte se {0}"},
    {Str::HintTextTyping, L"Vyberte cokoli nebo začněte psát a zeptejte se {0}"},
    {Str::Close, L"Zavřít"},
    {Str::AskInGemini, L"Zeptat se Gemini"},
    {Str::SearchWithLens, L"Hledat pomocí Google Lens"},
    {Str::TranslateTo, L"Přeložit do jazyka: {0}"},
    {Str::CopyImage, L"Kopírovat obrázek"},
    {Str::CopyText, L"Kopírovat text"},
    {Str::AddSelection, L"Přidat další výběr"},
    {Str::WhatIsThis, L"Co je to?"},
    {Str::ExplainThis, L"Vysvětli mi to"},
    {Str::SummarizeThis, L"Shrň mi to"},
    {Str::AskPlaceholder, L"Zeptejte se na svůj výběr…"},
    {Str::AskAnythingPlaceholder, L"Zeptejte se na cokoli…"},
    {Str::FollowUpPlaceholder, L"Položte doplňující dotaz…"},
    {Str::Thinking, L"Přemýšlím…"},
    {Str::Copy, L"Kopírovat"},
    {Str::SelectAll, L"Vybrat vše"},
    {Str::NoApiKeyHint, L"Přidejte do nastavení této úpravy klíč API služby Gemini, ChatGPT nebo Claude, abyste dostávali odpovědi přímo zde."},
    {Str::ImageCopied, L"Obrázek byl zkopírován"},
    {Str::ImageCopyFailed, L"Obrázek se nepodařilo zkopírovat"},
    {Str::ImageCopyRetry, L"Obrázek se nepodařilo zkopírovat. Zkuste to znovu."},
    {Str::ReadingText, L"Text se stále čte…"},
    {Str::NoTextFound, L"Ve výběru nebyl nalezen žádný text"},
    {Str::TextCopied, L"Text byl zkopírován"},
    {Str::TextCopyFailed, L"Text se nepodařilo zkopírovat"},
    {Str::AnswerCopied, L"Odpověď byla zkopírována"},
    {Str::AnswerCopyFailed, L"Odpověď se nepodařilo zkopírovat"},
    {Str::OpeningLens, L"Otevírá se Google Lens v prohlížeči…"},
    {Str::OpeningGeminiOne, L"Otevírá se Gemini a připojuje se váš obrázek…"},
    {Str::OpeningGeminiMany, L"Otevírá se Gemini a připojují se vaše obrázky…"},
    {Str::OpeningGeminiText, L"Otevírá se Gemini a přidává se vaše otázka…"},
    {Str::ClickBoxToAttach, L"Klikněte do pole zprávy v Gemini a stisknutím Ctrl+V připojte obrázek."},
    {Str::Stopped, L"Zastaveno."},
    {Str::StoppedEarly, L"Zastaveno dříve, než byla odpověď dokončena."},
    {Str::RequestFailed, L"Požadavek se nepodařilo spustit."},
    {Str::DraftAddedOne, L"Obrázek byl přidán. Napište svou otázku do Gemini."},
    {Str::DraftAddedMany, L"Obrázky byly přidány. Napište svou otázku do Gemini."},
    {Str::QuestionInGemini, L"Vaše otázka už je v Gemini."},
    {Str::DraftPartial, L"Potvrzené obrázky: {0} z {1}. Zkontrolujte Gemini a zbylé přidejte pomocí Ctrl+V v jeho poli zprávy."},
    {Str::ClipboardChangedOne, L"Schránka se změnila dříve, než šlo obrázek vložit: použijte Kopírovat obrázek a poté stiskněte Ctrl+V v Gemini."},
    {Str::ClipboardChangedMany, L"Schránka se změnila dříve, než šlo obrázky vložit. Zeptejte se v Gemini znovu a zkuste to ještě jednou."},
    {Str::IfNotAttachedOne, L"Pokud obrázek není připojen, klikněte do pole zprávy v Gemini a stiskněte Ctrl+V."},
    {Str::IfNotAttachedMany, L"Pokud obrázky nejsou připojeny, klikněte do pole zprávy v Gemini a stiskněte Ctrl+V."},
    {Str::ClickBoxOne, L"Klikněte do pole zprávy v Gemini a stisknutím Ctrl+V připojte obrázek. Vaše otázka zde zůstává."},
    {Str::ClickBoxMany, L"Klikněte do pole zprávy v Gemini a stisknutím Ctrl+V připojte obrázky. Vaše otázka zde zůstává."},
    {Str::ClickBoxText, L"Klikněte do pole zprávy v Gemini a napište svou otázku. Vaše otázka zde zůstává."},
    {Str::BrowserFailedOne, L"Prohlížeč se nepodařilo otevřít. Obrázek je zkopírován; vložte jej do Gemini pomocí Ctrl+V."},
    {Str::BrowserFailedMany, L"Prohlížeč se nepodařilo otevřít. Obrázky jsou zkopírovány; vložte je do Gemini pomocí Ctrl+V."},
    {Str::BrowserFailedText, L"Prohlížeč se nepodařilo otevřít."},
    {Str::PageUnreadable, L"Magic Pointer nemohl přečíst stránku ve vašem prohlížeči. Pokud je nad ní otevřeno oznámení, zavřete je a znovu klikněte na Zeptat se Gemini."},
    {Str::ErrKeyInvalid, L"Váš klíč API pro {0} není platný. Zkontrolujte jej v nastavení této úpravy."},
    {Str::ErrKeyForbidden, L"Tento klíč API nemůže používat službu {0} (403). Zkontrolujte klíč v nastavení této úpravy."},
    {Str::ErrModelMissing, L"Model „{0}“ není pro váš klíč dostupný. Vyberte v nastavení této úpravy jiný model."},
    {Str::ErrNoFreeQuota, L"Váš plán Gemini nemá bezplatnou kvótu pro „{0}“. Vyberte v nastavení této úpravy model Rychlý, nebo ke svému klíči přidejte fakturaci."},
    {Str::ErrNoCredit, L"Váš účet u služby {0} nemá žádný zbývající kredit. Dobijte kredit nebo přidejte platební metodu a zkuste to znovu."},
    {Str::ErrTimeout, L"Služba {0} neodpověděla včas. Zkuste to znovu za chvíli."},
    {Str::ModelBusy, L"Vybraný model není právě dostupný. Místo něj odpovídá rychlejší."},
    {Str::ErrRateLimit, L"Dosáhli jste prozatím limitu požadavků služby {0}. Zkuste to znovu za chvíli."},
    {Str::ErrServer, L"Služba {0} má právě potíže ({1}). Zkuste to znovu za chvíli."},
    {Str::ErrGeneric, L"Služba {0} vrátila chybu ({1})."},
    {Str::ErrNoConnection, L"Odpověď služby {0} se nepodařilo přijmout. Zkontrolujte připojení k internetu (chyba {1}). Zkuste se zeptat znovu."},
    {Str::ErrInterrupted, L"Připojení ke službě {0} bylo přerušeno. Tato odpověď je neúplná (chyba {1}). Zkuste se zeptat znovu."},
    {Str::ErrInterruptedBy, L"Služba {0} tuto odpověď přerušila: {1}"},
    {Str::ErrUnreadable, L"Služba {0} vrátila nečitelnou odpověď. Zkuste se zeptat znovu."},
    {Str::ErrOutputLimit, L"Služba {0} dosáhla limitu výstupu. Tato odpověď je neúplná. Zkuste požádat o kratší odpověď."},
    {Str::ErrStoppedBecause, L"Služba {0} tuto odpověď zastavila ({1}). Zkuste se zeptat jinak."},
    {Str::ErrUnconfirmed, L"Služba {0} se zastavila dříve, než potvrdila, že odpověď je úplná. Zkuste se zeptat znovu."},
    {Str::ErrNoAnswer, L"Služba {0} nevrátila žádnou odpověď. Zkuste se zeptat jinak."},
    {Str::ErrCouldntReach, L"Službu {0} se nepodařilo kontaktovat. Zkontrolujte připojení k internetu (chyba {1})."},
    {Str::ErrStreaming, L"Služba {0} vrátila chybu streamování."},
    {Str::LensSearching, L"Hledání pomocí Google Lens…"},
    {Str::LensUploadFailed, L"Automatické nahrání se nezdařilo. Obrázek je ve schránce: vložte jej na lens.google.com."},
};

const TextEntry kTexts_da[] = {
    {Str::HintText, L"Vælg noget for at spørge {0}"},
    {Str::HintTextTyping, L"Vælg noget eller begynd at skrive for at spørge {0}"},
    {Str::Close, L"Luk"},
    {Str::AskInGemini, L"Spørg Gemini"},
    {Str::SearchWithLens, L"Søg med Google Lens"},
    {Str::TranslateTo, L"Oversæt til: {0}"},
    {Str::CopyImage, L"Kopiér billede"},
    {Str::CopyText, L"Kopiér tekst"},
    {Str::AddSelection, L"Tilføj endnu et valg"},
    {Str::WhatIsThis, L"Hvad er det her?"},
    {Str::ExplainThis, L"Forklar det her"},
    {Str::SummarizeThis, L"Opsummér det her"},
    {Str::AskPlaceholder, L"Spørg om dit valg…"},
    {Str::AskAnythingPlaceholder, L"Spørg om hvad som helst…"},
    {Str::FollowUpPlaceholder, L"Stil et opfølgende spørgsmål…"},
    {Str::Thinking, L"Tænker…"},
    {Str::Copy, L"Kopiér"},
    {Str::SelectAll, L"Markér alt"},
    {Str::NoApiKeyHint, L"Tilføj en API-nøgle til Gemini, ChatGPT eller Claude i indstillingerne for modifikationen for at få svar lige her."},
    {Str::ImageCopied, L"Billedet er kopieret"},
    {Str::ImageCopyFailed, L"Billedet kunne ikke kopieres"},
    {Str::ImageCopyRetry, L"Billedet kunne ikke kopieres. Prøv igen."},
    {Str::ReadingText, L"Læser stadig teksten…"},
    {Str::NoTextFound, L"Der blev ikke fundet tekst i det valgte"},
    {Str::TextCopied, L"Teksten er kopieret"},
    {Str::TextCopyFailed, L"Teksten kunne ikke kopieres"},
    {Str::AnswerCopied, L"Svaret er kopieret"},
    {Str::AnswerCopyFailed, L"Svaret kunne ikke kopieres"},
    {Str::OpeningLens, L"Åbner Google Lens i din browser…"},
    {Str::OpeningGeminiOne, L"Åbner Gemini og vedhæfter dit billede…"},
    {Str::OpeningGeminiMany, L"Åbner Gemini og vedhæfter dine billeder…"},
    {Str::OpeningGeminiText, L"Åbner Gemini og tilføjer dit spørgsmål…"},
    {Str::ClickBoxToAttach, L"Klik i Geminis tekstfelt, og tryk på Ctrl+V for at vedhæfte billedet."},
    {Str::Stopped, L"Stoppet."},
    {Str::StoppedEarly, L"Stoppet, før svaret var færdigt."},
    {Str::RequestFailed, L"Anmodningen kunne ikke startes."},
    {Str::DraftAddedOne, L"Billedet blev tilføjet. Skriv dit spørgsmål i Gemini."},
    {Str::DraftAddedMany, L"Billederne blev tilføjet. Skriv dit spørgsmål i Gemini."},
    {Str::QuestionInGemini, L"Dit spørgsmål er skrevet ind i Gemini."},
    {Str::DraftPartial, L"Bekræftede billeder: {0} af {1}. Tjek Gemini, og tilføj resten med Ctrl+V i dets tekstfelt."},
    {Str::ClipboardChangedOne, L"Udklipsholderen blev ændret, før billedet kunne indsættes: brug Kopiér billede, og tryk derefter på Ctrl+V i Gemini."},
    {Str::ClipboardChangedMany, L"Udklipsholderen blev ændret, før billederne kunne indsættes. Spørg igen i Gemini for at prøve igen."},
    {Str::IfNotAttachedOne, L"Hvis billedet ikke er vedhæftet, skal du klikke i Geminis tekstfelt og trykke på Ctrl+V."},
    {Str::IfNotAttachedMany, L"Hvis billederne ikke er vedhæftet, skal du klikke i Geminis tekstfelt og trykke på Ctrl+V."},
    {Str::ClickBoxOne, L"Klik i Geminis tekstfelt, og tryk på Ctrl+V for at vedhæfte billedet. Dit spørgsmål bliver her."},
    {Str::ClickBoxMany, L"Klik i Geminis tekstfelt, og tryk på Ctrl+V for at vedhæfte billederne. Dit spørgsmål bliver her."},
    {Str::ClickBoxText, L"Klik i Geminis tekstfelt, og skriv dit spørgsmål. Dit spørgsmål bliver her."},
    {Str::BrowserFailedOne, L"Browseren kunne ikke åbnes. Billedet er kopieret; indsæt det i Gemini med Ctrl+V."},
    {Str::BrowserFailedMany, L"Browseren kunne ikke åbnes. Billederne er kopieret; indsæt dem i Gemini med Ctrl+V."},
    {Str::BrowserFailedText, L"Browseren kunne ikke åbnes."},
    {Str::PageUnreadable, L"Magic Pointer kunne ikke læse siden i din browser. Hvis en meddelelse er åben oven på den, skal du lukke den og klikke på Spørg Gemini igen."},
    {Str::ErrKeyInvalid, L"Din {0} API-nøgle er ugyldig. Tjek den i indstillingerne for modifikationen."},
    {Str::ErrKeyForbidden, L"Denne API-nøgle kan ikke bruge {0} (403). Tjek nøglen i indstillingerne for modifikationen."},
    {Str::ErrModelMissing, L"Modellen \"{0}\" er ikke tilgængelig for din nøgle. Vælg en anden model i indstillingerne for modifikationen."},
    {Str::ErrNoFreeQuota, L"Dit Gemini-abonnement har ingen gratis kvote til \"{0}\". Vælg modellen Hurtig i indstillingerne for modifikationen, eller tilføj fakturering til din nøgle."},
    {Str::ErrNoCredit, L"Din {0}-konto er løbet tør for kredit. Tilføj kredit eller en betalingsmetode, og prøv igen."},
    {Str::ErrTimeout, L"{0} svarede ikke i tide. Prøv igen om lidt."},
    {Str::ModelBusy, L"Den model, du valgte, er ikke tilgængelig lige nu. En hurtigere model svarer i stedet."},
    {Str::ErrRateLimit, L"Du har nået grænsen for anmodninger hos {0} for nu. Prøv igen om lidt."},
    {Str::ErrServer, L"{0} har problemer lige nu ({1}). Prøv igen om lidt."},
    {Str::ErrGeneric, L"{0} returnerede en fejl ({1})."},
    {Str::ErrNoConnection, L"Svaret fra {0} kunne ikke modtages. Tjek din internetforbindelse (fejl {1}), og prøv at spørge igen."},
    {Str::ErrInterrupted, L"Forbindelsen til {0} blev afbrudt, og svaret er ufuldstændigt (fejl {1}). Prøv at spørge igen."},
    {Str::ErrInterruptedBy, L"{0} afbrød dette svar: {1}"},
    {Str::ErrUnreadable, L"{0} returnerede et ulæseligt svar. Prøv at spørge igen."},
    {Str::ErrOutputLimit, L"{0} nåede sin outputgrænse. Svaret er ufuldstændigt. Prøv at bede om et kortere svar."},
    {Str::ErrStoppedBecause, L"{0} stoppede dette svar ({1}). Prøv at spørge på en anden måde."},
    {Str::ErrUnconfirmed, L"{0} stoppede, før det blev bekræftet, at svaret var komplet. Prøv at spørge igen."},
    {Str::ErrNoAnswer, L"{0} returnerede ikke noget svar. Prøv at spørge på en anden måde."},
    {Str::ErrCouldntReach, L"{0} kunne ikke nås. Tjek din internetforbindelse (fejl {1})."},
    {Str::ErrStreaming, L"{0} returnerede en streamingfejl."},
    {Str::LensSearching, L"Søger med Google Lens…"},
    {Str::LensUploadFailed, L"Automatisk upload mislykkedes. Billedet ligger i udklipsholderen: indsæt det på lens.google.com."},
};

const TextEntry kTexts_nl[] = {
    {Str::HintText, L"Selecteer iets om het aan {0} te vragen"},
    {Str::HintTextTyping, L"Selecteer iets of begin te typen om {0} iets te vragen"},
    {Str::Close, L"Sluiten"},
    {Str::AskInGemini, L"Vraag het aan Gemini"},
    {Str::SearchWithLens, L"Zoeken met Google Lens"},
    {Str::TranslateTo, L"Vertalen naar: {0}"},
    {Str::CopyImage, L"Afbeelding kopiëren"},
    {Str::CopyText, L"Tekst kopiëren"},
    {Str::AddSelection, L"Nog een selectie toevoegen"},
    {Str::WhatIsThis, L"Wat is dit?"},
    {Str::ExplainThis, L"Leg dit uit"},
    {Str::SummarizeThis, L"Vat dit samen"},
    {Str::AskPlaceholder, L"Stel een vraag over je selectie…"},
    {Str::AskAnythingPlaceholder, L"Stel een vraag…"},
    {Str::FollowUpPlaceholder, L"Stel een vervolgvraag…"},
    {Str::Thinking, L"Aan het nadenken…"},
    {Str::Copy, L"Kopiëren"},
    {Str::SelectAll, L"Alles selecteren"},
    {Str::NoApiKeyHint, L"Voeg in de instellingen van de mod een API-sleutel voor Gemini, ChatGPT of Claude toe om hier direct antwoorden te krijgen."},
    {Str::ImageCopied, L"Afbeelding gekopieerd"},
    {Str::ImageCopyFailed, L"De afbeelding kon niet worden gekopieerd"},
    {Str::ImageCopyRetry, L"De afbeelding kon niet worden gekopieerd. Probeer het opnieuw."},
    {Str::ReadingText, L"De tekst wordt nog gelezen…"},
    {Str::NoTextFound, L"Geen tekst gevonden in de selectie"},
    {Str::TextCopied, L"Tekst gekopieerd"},
    {Str::TextCopyFailed, L"De tekst kon niet worden gekopieerd"},
    {Str::AnswerCopied, L"Antwoord gekopieerd"},
    {Str::AnswerCopyFailed, L"Het antwoord kon niet worden gekopieerd"},
    {Str::OpeningLens, L"Google Lens wordt geopend in je browser…"},
    {Str::OpeningGeminiOne, L"Gemini wordt geopend en je afbeelding wordt toegevoegd…"},
    {Str::OpeningGeminiMany, L"Gemini wordt geopend en je afbeeldingen worden toegevoegd…"},
    {Str::OpeningGeminiText, L"Gemini wordt geopend en je vraag wordt toegevoegd…"},
    {Str::ClickBoxToAttach, L"Klik in het berichtvak van Gemini en druk op Ctrl+V om de afbeelding toe te voegen."},
    {Str::Stopped, L"Gestopt."},
    {Str::StoppedEarly, L"Gestopt voordat het antwoord klaar was."},
    {Str::RequestFailed, L"De aanvraag kon niet worden gestart."},
    {Str::DraftAddedOne, L"De afbeelding is toegevoegd. Typ je vraag in Gemini."},
    {Str::DraftAddedMany, L"De afbeeldingen zijn toegevoegd. Typ je vraag in Gemini."},
    {Str::QuestionInGemini, L"Je vraag staat al in Gemini."},
    {Str::DraftPartial, L"Bevestigde afbeeldingen: {0} van {1}. Controleer Gemini en voeg de rest toe met Ctrl+V in het berichtvak."},
    {Str::ClipboardChangedOne, L"Het klembord is gewijzigd voordat de afbeelding kon worden geplakt: gebruik Afbeelding kopiëren en druk daarna op Ctrl+V in Gemini."},
    {Str::ClipboardChangedMany, L"Het klembord is gewijzigd voordat de afbeeldingen konden worden geplakt. Vraag het opnieuw in Gemini om het nog eens te proberen."},
    {Str::IfNotAttachedOne, L"Als de afbeelding niet is toegevoegd, klik je in het berichtvak van Gemini en druk je op Ctrl+V."},
    {Str::IfNotAttachedMany, L"Als de afbeeldingen niet zijn toegevoegd, klik je in het berichtvak van Gemini en druk je op Ctrl+V."},
    {Str::ClickBoxOne, L"Klik in het berichtvak van Gemini en druk op Ctrl+V om de afbeelding toe te voegen. Je vraag blijft hier bewaard."},
    {Str::ClickBoxMany, L"Klik in het berichtvak van Gemini en druk op Ctrl+V om de afbeeldingen toe te voegen. Je vraag blijft hier bewaard."},
    {Str::ClickBoxText, L"Klik in het berichtvak van Gemini en typ je vraag. Je vraag blijft hier bewaard."},
    {Str::BrowserFailedOne, L"De browser kon niet worden geopend. De afbeelding is gekopieerd; plak deze in Gemini met Ctrl+V."},
    {Str::BrowserFailedMany, L"De browser kon niet worden geopend. De afbeeldingen zijn gekopieerd; plak ze in Gemini met Ctrl+V."},
    {Str::BrowserFailedText, L"De browser kon niet worden geopend."},
    {Str::PageUnreadable, L"Magic Pointer kon de pagina in je browser niet lezen. Als er een melding overheen open staat, sluit je die en klik je opnieuw op Vraag het aan Gemini."},
    {Str::ErrKeyInvalid, L"Je {0}-API-sleutel is ongeldig. Controleer hem in de instellingen van de mod."},
    {Str::ErrKeyForbidden, L"Deze API-sleutel kan {0} niet gebruiken (403). Controleer de sleutel in de instellingen van de mod."},
    {Str::ErrModelMissing, L"Het model \"{0}\" is niet beschikbaar voor je sleutel. Kies een ander model in de instellingen van de mod."},
    {Str::ErrNoFreeQuota, L"Je Gemini-abonnement heeft geen gratis quotum voor \"{0}\". Kies het model Snel in de instellingen van de mod of voeg facturering toe aan je sleutel."},
    {Str::ErrNoCredit, L"Het tegoed van je {0}-account is op. Voeg tegoed of een betaalmethode toe en probeer het opnieuw."},
    {Str::ErrTimeout, L"{0} antwoordde niet op tijd. Probeer het zo meteen opnieuw."},
    {Str::ModelBusy, L"Het model dat je koos is nu niet beschikbaar. Een sneller model antwoordt in plaats daarvan."},
    {Str::ErrRateLimit, L"Je hebt de aanvraaglimiet van {0} voorlopig bereikt. Probeer het zo meteen opnieuw."},
    {Str::ErrServer, L"{0} heeft op dit moment problemen ({1}). Probeer het zo meteen opnieuw."},
    {Str::ErrGeneric, L"{0} gaf een fout terug ({1})."},
    {Str::ErrNoConnection, L"Het antwoord van {0} kon niet worden ontvangen. Controleer je internetverbinding (fout {1}) en stel je vraag opnieuw."},
    {Str::ErrInterrupted, L"De verbinding met {0} is verbroken en het antwoord is onvolledig (fout {1}). Stel je vraag opnieuw."},
    {Str::ErrInterruptedBy, L"{0} heeft dit antwoord onderbroken: {1}"},
    {Str::ErrUnreadable, L"{0} gaf een onleesbaar antwoord. Stel je vraag opnieuw."},
    {Str::ErrOutputLimit, L"{0} heeft zijn uitvoerlimiet bereikt. Dit antwoord is onvolledig. Vraag om een korter antwoord."},
    {Str::ErrStoppedBecause, L"{0} heeft dit antwoord gestopt ({1}). Probeer de vraag anders te stellen."},
    {Str::ErrUnconfirmed, L"{0} stopte voordat het antwoord als volledig was bevestigd. Stel je vraag opnieuw."},
    {Str::ErrNoAnswer, L"{0} gaf geen antwoord terug. Probeer de vraag anders te stellen."},
    {Str::ErrCouldntReach, L"{0} kon niet worden bereikt. Controleer je internetverbinding (fout {1})."},
    {Str::ErrStreaming, L"{0} gaf een streamingfout terug."},
    {Str::LensSearching, L"Zoeken met Google Lens…"},
    {Str::LensUploadFailed, L"Automatisch uploaden is mislukt. De afbeelding staat op je klembord: plak hem op lens.google.com."},
};

const TextEntry kTexts_fi[] = {
    {Str::HintText, L"Valitse mitä tahansa ja kysy tekoälyltä ({0})"},
    {Str::HintTextTyping, L"Valitse mitä tahansa tai aloita kirjoittaminen ja kysy tekoälyltä ({0})"},
    {Str::Close, L"Sulje"},
    {Str::AskInGemini, L"Kysy Geminiltä"},
    {Str::SearchWithLens, L"Hae Google Lensillä"},
    {Str::TranslateTo, L"Käännä kielelle: {0}"},
    {Str::CopyImage, L"Kopioi kuva"},
    {Str::CopyText, L"Kopioi teksti"},
    {Str::AddSelection, L"Lisää toinen valinta"},
    {Str::WhatIsThis, L"Mikä tämä on?"},
    {Str::ExplainThis, L"Selitä tämä minulle"},
    {Str::SummarizeThis, L"Tiivistä tämä minulle"},
    {Str::AskPlaceholder, L"Kysy valinnastasi…"},
    {Str::AskAnythingPlaceholder, L"Kysy mitä tahansa…"},
    {Str::FollowUpPlaceholder, L"Kysy jatkokysymys…"},
    {Str::Thinking, L"Mietitään…"},
    {Str::Copy, L"Kopioi"},
    {Str::SelectAll, L"Valitse kaikki"},
    {Str::NoApiKeyHint, L"Lisää Gemini-, ChatGPT- tai Claude-API-avain modin asetuksiin, niin saat vastaukset suoraan tähän."},
    {Str::ImageCopied, L"Kuva kopioitu"},
    {Str::ImageCopyFailed, L"Kuvaa ei voitu kopioida"},
    {Str::ImageCopyRetry, L"Kuvaa ei voitu kopioida. Yritä uudelleen."},
    {Str::ReadingText, L"Tekstiä luetaan vielä…"},
    {Str::NoTextFound, L"Valinnasta ei löytynyt tekstiä"},
    {Str::TextCopied, L"Teksti kopioitu"},
    {Str::TextCopyFailed, L"Tekstiä ei voitu kopioida"},
    {Str::AnswerCopied, L"Vastaus kopioitu"},
    {Str::AnswerCopyFailed, L"Vastausta ei voitu kopioida"},
    {Str::OpeningLens, L"Avataan Google Lens selaimessa…"},
    {Str::OpeningGeminiOne, L"Avataan Gemini ja liitetään kuva liitteeksi…"},
    {Str::OpeningGeminiMany, L"Avataan Gemini ja liitetään kuvat liitteiksi…"},
    {Str::OpeningGeminiText, L"Avataan Gemini ja lisätään kysymyksesi…"},
    {Str::ClickBoxToAttach, L"Napsauta Geminin viestikenttää ja liitä kuva painamalla Ctrl+V."},
    {Str::Stopped, L"Pysäytetty."},
    {Str::StoppedEarly, L"Pysäytetty ennen kuin vastaus valmistui."},
    {Str::RequestFailed, L"Pyyntöä ei voitu käynnistää."},
    {Str::DraftAddedOne, L"Kuva lisättiin. Kirjoita kysymyksesi Geminiin."},
    {Str::DraftAddedMany, L"Kuvat lisättiin. Kirjoita kysymyksesi Geminiin."},
    {Str::QuestionInGemini, L"Kysymyksesi on Geminissä."},
    {Str::DraftPartial, L"Vahvistetut kuvat: {0} / {1}. Tarkista Gemini ja lisää loput painamalla Ctrl+V sen viestikentässä."},
    {Str::ClipboardChangedOne, L"Leikepöytä muuttui ennen kuin kuva ehdittiin liittää: käytä Kopioi kuva -toimintoa ja paina sitten Ctrl+V Geminissä."},
    {Str::ClipboardChangedMany, L"Leikepöytä muuttui ennen kuin kuvat ehdittiin liittää. Kysy Geminiltä uudelleen yrittääksesi uudestaan."},
    {Str::IfNotAttachedOne, L"Jos kuvaa ei ole liitetty, napsauta Geminin viestikenttää ja paina Ctrl+V."},
    {Str::IfNotAttachedMany, L"Jos kuvia ei ole liitetty, napsauta Geminin viestikenttää ja paina Ctrl+V."},
    {Str::ClickBoxOne, L"Napsauta Geminin viestikenttää ja liitä kuva painamalla Ctrl+V. Kysymyksesi säilyy tässä."},
    {Str::ClickBoxMany, L"Napsauta Geminin viestikenttää ja liitä kuvat painamalla Ctrl+V. Kysymyksesi säilyy tässä."},
    {Str::ClickBoxText, L"Napsauta Geminin viestikenttää ja kirjoita kysymyksesi. Kysymyksesi säilyy tässä."},
    {Str::BrowserFailedOne, L"Selainta ei voitu avata. Kuva on kopioitu; liitä se Geminiin painamalla Ctrl+V."},
    {Str::BrowserFailedMany, L"Selainta ei voitu avata. Kuvat on kopioitu; liitä ne Geminiin painamalla Ctrl+V."},
    {Str::BrowserFailedText, L"Selainta ei voitu avata."},
    {Str::PageUnreadable, L"Magic Pointer ei voinut lukea sivua selaimessasi. Jos sen päällä on avoin ilmoitus, sulje se ja napsauta Kysy Geminiltä uudelleen."},
    {Str::ErrKeyInvalid, L"{0}-API-avaimesi ei kelpaa. Tarkista se modin asetuksista."},
    {Str::ErrKeyForbidden, L"Tällä API-avaimella ei voi käyttää {0}-palvelua (403). Tarkista avain modin asetuksista."},
    {Str::ErrModelMissing, L"Malli \"{0}\" ei ole avaimesi käytettävissä. Valitse toinen malli modin asetuksista."},
    {Str::ErrNoFreeQuota, L"Gemini-tilauksellasi ei ole ilmaista kiintiötä mallille \"{0}\". Valitse modin asetuksista malli \"Nopea\" tai lisää avaimeesi laskutus."},
    {Str::ErrNoCredit, L"{0}-tilisi saldo on loppu. Lisää tilille saldoa tai maksutapa ja yritä uudelleen."},
    {Str::ErrTimeout, L"{0}-palvelu ei vastannut ajoissa. Yritä hetken kuluttua uudelleen."},
    {Str::ModelBusy, L"Valitsemasi malli ei ole nyt käytettävissä. Sen sijaan vastaa nopeampi malli."},
    {Str::ErrRateLimit, L"Olet saavuttanut {0}-palvelun pyyntörajan toistaiseksi. Yritä hetken kuluttua uudelleen."},
    {Str::ErrServer, L"{0}-palvelulla on tällä hetkellä ongelmia ({1}). Yritä hetken kuluttua uudelleen."},
    {Str::ErrGeneric, L"{0}-palvelu palautti virheen ({1})."},
    {Str::ErrNoConnection, L"{0}-palvelun vastausta ei voitu vastaanottaa. Tarkista internetyhteytesi (virhe {1}). Yritä kysyä uudelleen."},
    {Str::ErrInterrupted, L"Yhteys {0}-palveluun katkesi. Tämä vastaus on keskeneräinen (virhe {1}). Yritä kysyä uudelleen."},
    {Str::ErrInterruptedBy, L"{0}-palvelu keskeytti tämän vastauksen: {1}"},
    {Str::ErrUnreadable, L"{0}-palvelu palautti lukukelvottoman vastauksen. Yritä kysyä uudelleen."},
    {Str::ErrOutputLimit, L"{0}-palvelu saavutti tulostusrajansa. Tämä vastaus on keskeneräinen. Yritä pyytää lyhyempää vastausta."},
    {Str::ErrStoppedBecause, L"{0}-palvelu pysäytti tämän vastauksen ({1}). Yritä kysyä toisella tavalla."},
    {Str::ErrUnconfirmed, L"{0}-palvelu pysähtyi ennen kuin vahvisti vastauksen olevan valmis. Yritä kysyä uudelleen."},
    {Str::ErrNoAnswer, L"{0}-palvelu ei palauttanut vastausta. Yritä kysyä toisella tavalla."},
    {Str::ErrCouldntReach, L"{0}-palveluun ei saatu yhteyttä. Tarkista internetyhteytesi (virhe {1})."},
    {Str::ErrStreaming, L"{0}-palvelu palautti suoratoistovirheen."},
    {Str::LensSearching, L"Haetaan Google Lensillä…"},
    {Str::LensUploadFailed, L"Automaattinen lataus epäonnistui. Kuva on leikepöydällä: liitä se osoitteessa lens.google.com."},
};

const TextEntry kTexts_fr[] = {
    {Str::HintText, L"Sélectionnez un élément pour interroger {0}"},
    {Str::HintTextTyping, L"Sélectionnez un élément ou commencez à écrire pour interroger {0}"},
    {Str::Close, L"Fermer"},
    {Str::AskInGemini, L"Demander à Gemini"},
    {Str::SearchWithLens, L"Rechercher avec Google Lens"},
    {Str::TranslateTo, L"Traduire en : {0}"},
    {Str::CopyImage, L"Copier l'image"},
    {Str::CopyText, L"Copier le texte"},
    {Str::AddSelection, L"Ajouter une autre sélection"},
    {Str::WhatIsThis, L"Qu'est-ce que c'est ?"},
    {Str::ExplainThis, L"Explique-moi ça"},
    {Str::SummarizeThis, L"Résume-moi ça"},
    {Str::AskPlaceholder, L"Posez une question sur votre sélection…"},
    {Str::AskAnythingPlaceholder, L"Posez n'importe quelle question…"},
    {Str::FollowUpPlaceholder, L"Posez une autre question…"},
    {Str::Thinking, L"Réflexion en cours…"},
    {Str::Copy, L"Copier"},
    {Str::SelectAll, L"Tout sélectionner"},
    {Str::NoApiKeyHint, L"Ajoutez une clé API Gemini, ChatGPT ou Claude dans les paramètres du mod pour obtenir les réponses directement ici."},
    {Str::ImageCopied, L"Image copiée"},
    {Str::ImageCopyFailed, L"Impossible de copier l'image"},
    {Str::ImageCopyRetry, L"Impossible de copier l'image. Réessayez."},
    {Str::ReadingText, L"Lecture du texte en cours…"},
    {Str::NoTextFound, L"Aucun texte trouvé dans la sélection"},
    {Str::TextCopied, L"Texte copié"},
    {Str::TextCopyFailed, L"Impossible de copier le texte"},
    {Str::AnswerCopied, L"Réponse copiée"},
    {Str::AnswerCopyFailed, L"Impossible de copier la réponse"},
    {Str::OpeningLens, L"Ouverture de Google Lens dans votre navigateur…"},
    {Str::OpeningGeminiOne, L"Ouverture de Gemini et ajout de votre image…"},
    {Str::OpeningGeminiMany, L"Ouverture de Gemini et ajout de vos images…"},
    {Str::OpeningGeminiText, L"Ouverture de Gemini et ajout de votre question…"},
    {Str::ClickBoxToAttach, L"Cliquez dans le champ de saisie de Gemini, puis appuyez sur Ctrl+V pour joindre l'image."},
    {Str::Stopped, L"Arrêté."},
    {Str::StoppedEarly, L"Arrêté avant la fin de la réponse."},
    {Str::RequestFailed, L"Impossible de lancer la requête."},
    {Str::DraftAddedOne, L"L'image a été ajoutée. Saisissez votre question dans Gemini."},
    {Str::DraftAddedMany, L"Les images ont été ajoutées. Saisissez votre question dans Gemini."},
    {Str::QuestionInGemini, L"Votre question a été saisie dans Gemini."},
    {Str::DraftPartial, L"Images confirmées : {0} sur {1}. Vérifiez Gemini et ajoutez les autres avec Ctrl+V dans son champ de saisie."},
    {Str::ClipboardChangedOne, L"Le presse-papiers a changé avant que l'image puisse être collée : utilisez Copier l'image, puis appuyez sur Ctrl+V dans Gemini."},
    {Str::ClipboardChangedMany, L"Le presse-papiers a changé avant que les images puissent être collées. Redemandez dans Gemini pour réessayer."},
    {Str::IfNotAttachedOne, L"Si l'image n'est pas jointe, cliquez dans le champ de saisie de Gemini et appuyez sur Ctrl+V."},
    {Str::IfNotAttachedMany, L"Si les images ne sont pas jointes, cliquez dans le champ de saisie de Gemini et appuyez sur Ctrl+V."},
    {Str::ClickBoxOne, L"Cliquez dans le champ de saisie de Gemini et appuyez sur Ctrl+V pour joindre l'image. Votre question est conservée ici."},
    {Str::ClickBoxMany, L"Cliquez dans le champ de saisie de Gemini et appuyez sur Ctrl+V pour joindre les images. Votre question est conservée ici."},
    {Str::ClickBoxText, L"Cliquez dans le champ de saisie de Gemini et tapez votre question. Votre question est conservée ici."},
    {Str::BrowserFailedOne, L"Impossible d'ouvrir le navigateur. L'image est copiée ; collez-la dans Gemini avec Ctrl+V."},
    {Str::BrowserFailedMany, L"Impossible d'ouvrir le navigateur. Les images sont copiées ; collez-les dans Gemini avec Ctrl+V."},
    {Str::BrowserFailedText, L"Impossible d'ouvrir le navigateur."},
    {Str::PageUnreadable, L"Magic Pointer n'a pas pu lire la page dans votre navigateur. Si une notification est ouverte par-dessus, fermez-la et cliquez à nouveau sur Demander à Gemini."},
    {Str::ErrKeyInvalid, L"Votre clé API {0} n'est pas valide. Vérifiez-la dans les paramètres du mod."},
    {Str::ErrKeyForbidden, L"Cette clé API ne peut pas utiliser {0} (403). Vérifiez la clé dans les paramètres du mod."},
    {Str::ErrModelMissing, L"Le modèle « {0} » n'est pas disponible pour votre clé. Choisissez un autre modèle dans les paramètres du mod."},
    {Str::ErrNoFreeQuota, L"Votre forfait Gemini n'a pas de quota gratuit pour « {0} ». Choisissez le modèle « Rapide » dans les paramètres du mod, ou ajoutez la facturation à votre clé."},
    {Str::ErrNoCredit, L"Le crédit de votre compte {0} est épuisé. Ajoutez du crédit ou un moyen de paiement, puis réessayez."},
    {Str::ErrTimeout, L"{0} n'a pas répondu à temps. Réessayez dans quelques instants."},
    {Str::ModelBusy, L"Le modèle que vous avez choisi n'est pas disponible pour le moment. Un modèle plus rapide répond à sa place."},
    {Str::ErrRateLimit, L"Vous avez atteint la limite de requêtes de {0} pour le moment. Réessayez dans quelques instants."},
    {Str::ErrServer, L"{0} rencontre des difficultés en ce moment ({1}). Réessayez dans quelques instants."},
    {Str::ErrGeneric, L"{0} a renvoyé une erreur ({1})."},
    {Str::ErrNoConnection, L"Impossible de recevoir la réponse de {0}. Vérifiez votre connexion Internet (erreur {1}), puis réessayez."},
    {Str::ErrInterrupted, L"La connexion à {0} a été interrompue et la réponse est incomplète (erreur {1}). Réessayez."},
    {Str::ErrInterruptedBy, L"{0} a interrompu cette réponse : {1}"},
    {Str::ErrUnreadable, L"{0} a renvoyé une réponse illisible. Réessayez."},
    {Str::ErrOutputLimit, L"{0} a atteint sa limite de longueur et la réponse est incomplète. Essayez de demander une réponse plus courte."},
    {Str::ErrStoppedBecause, L"{0} a interrompu la réponse ({1}). Essayez de reformuler votre question."},
    {Str::ErrUnconfirmed, L"{0} s'est arrêté avant de confirmer que la réponse était complète. Réessayez."},
    {Str::ErrNoAnswer, L"{0} n'a donné aucune réponse. Essayez de reformuler votre question."},
    {Str::ErrCouldntReach, L"Impossible de joindre {0}. Vérifiez votre connexion Internet (erreur {1})."},
    {Str::ErrStreaming, L"{0} a renvoyé une erreur de diffusion."},
    {Str::LensSearching, L"Recherche avec Google Lens…"},
    {Str::LensUploadFailed, L"L'envoi automatique a échoué. L'image est dans le presse-papiers : collez-la sur lens.google.com."},
};

const TextEntry kTexts_de[] = {
    {Str::HintText, L"Wähle etwas aus, um {0} zu fragen"},
    {Str::HintTextTyping, L"Wähle etwas aus oder beginne zu tippen, um {0} zu fragen"},
    {Str::Close, L"Schließen"},
    {Str::AskInGemini, L"Gemini fragen"},
    {Str::SearchWithLens, L"Mit Google Lens suchen"},
    {Str::TranslateTo, L"Übersetzen in: {0}"},
    {Str::CopyImage, L"Bild kopieren"},
    {Str::CopyText, L"Text kopieren"},
    {Str::AddSelection, L"Weitere Auswahl hinzufügen"},
    {Str::WhatIsThis, L"Was ist das?"},
    {Str::ExplainThis, L"Erkläre mir das"},
    {Str::SummarizeThis, L"Fasse das für mich zusammen"},
    {Str::AskPlaceholder, L"Frag etwas zu deiner Auswahl…"},
    {Str::AskAnythingPlaceholder, L"Frag, was du willst…"},
    {Str::FollowUpPlaceholder, L"Stelle eine Folgefrage…"},
    {Str::Thinking, L"Denke nach…"},
    {Str::Copy, L"Kopieren"},
    {Str::SelectAll, L"Alles auswählen"},
    {Str::NoApiKeyHint, L"Füge in den Einstellungen des Mods einen API-Schlüssel für Gemini, ChatGPT oder Claude hinzu, um Antworten direkt hier zu erhalten."},
    {Str::ImageCopied, L"Bild kopiert"},
    {Str::ImageCopyFailed, L"Das Bild konnte nicht kopiert werden"},
    {Str::ImageCopyRetry, L"Das Bild konnte nicht kopiert werden. Versuche es erneut."},
    {Str::ReadingText, L"Text wird erkannt…"},
    {Str::NoTextFound, L"Kein Text in der Auswahl gefunden"},
    {Str::TextCopied, L"Text kopiert"},
    {Str::TextCopyFailed, L"Der Text konnte nicht kopiert werden"},
    {Str::AnswerCopied, L"Antwort kopiert"},
    {Str::AnswerCopyFailed, L"Die Antwort konnte nicht kopiert werden"},
    {Str::OpeningLens, L"Google Lens wird in deinem Browser geöffnet…"},
    {Str::OpeningGeminiOne, L"Gemini wird geöffnet und dein Bild angehängt…"},
    {Str::OpeningGeminiMany, L"Gemini wird geöffnet und deine Bilder werden angehängt…"},
    {Str::OpeningGeminiText, L"Gemini wird geöffnet und deine Frage hinzugefügt…"},
    {Str::ClickBoxToAttach, L"Klicke in das Eingabefeld von Gemini und drücke Strg+V, um das Bild anzuhängen."},
    {Str::Stopped, L"Angehalten."},
    {Str::StoppedEarly, L"Angehalten, bevor die Antwort fertig war."},
    {Str::RequestFailed, L"Die Anfrage konnte nicht gestartet werden."},
    {Str::DraftAddedOne, L"Das Bild wurde hinzugefügt. Gib deine Frage in Gemini ein."},
    {Str::DraftAddedMany, L"Die Bilder wurden hinzugefügt. Gib deine Frage in Gemini ein."},
    {Str::QuestionInGemini, L"Deine Frage wurde in Gemini eingegeben."},
    {Str::DraftPartial, L"Nur {0} von {1} Bildern konnten bestätigt werden. Prüfe Gemini und füge den Rest mit Strg+V im Eingabefeld hinzu."},
    {Str::ClipboardChangedOne, L"Die Zwischenablage hat sich geändert, bevor das Bild eingefügt werden konnte: Verwende „Bild kopieren“ und drücke dann in Gemini Strg+V."},
    {Str::ClipboardChangedMany, L"Die Zwischenablage hat sich geändert, bevor die Bilder eingefügt werden konnten. Frage erneut in Gemini, um es noch einmal zu versuchen."},
    {Str::IfNotAttachedOne, L"Falls das Bild nicht angehängt ist, klicke in das Eingabefeld von Gemini und drücke Strg+V."},
    {Str::IfNotAttachedMany, L"Falls die Bilder nicht angehängt sind, klicke in das Eingabefeld von Gemini und drücke Strg+V."},
    {Str::ClickBoxOne, L"Klicke in das Eingabefeld von Gemini und drücke Strg+V, um das Bild anzuhängen. Deine Frage bleibt hier erhalten."},
    {Str::ClickBoxMany, L"Klicke in das Eingabefeld von Gemini und drücke Strg+V, um die Bilder anzuhängen. Deine Frage bleibt hier erhalten."},
    {Str::ClickBoxText, L"Klicke in das Eingabefeld von Gemini und tippe deine Frage ein. Deine Frage bleibt hier erhalten."},
    {Str::BrowserFailedOne, L"Der Browser konnte nicht geöffnet werden. Das Bild ist kopiert; füge es mit Strg+V in Gemini ein."},
    {Str::BrowserFailedMany, L"Der Browser konnte nicht geöffnet werden. Die Bilder sind kopiert; füge sie mit Strg+V in Gemini ein."},
    {Str::BrowserFailedText, L"Der Browser konnte nicht geöffnet werden."},
    {Str::PageUnreadable, L"Magic Pointer konnte die Seite in deinem Browser nicht lesen. Falls darüber ein Hinweis geöffnet ist, schließe ihn und klicke erneut auf „Gemini fragen“."},
    {Str::ErrKeyInvalid, L"Dein {0}-API-Schlüssel ist ungültig. Prüfe ihn in den Einstellungen des Mods."},
    {Str::ErrKeyForbidden, L"Dieser API-Schlüssel kann {0} nicht verwenden (403). Prüfe den Schlüssel in den Einstellungen des Mods."},
    {Str::ErrModelMissing, L"Das Modell „{0}“ ist für deinen Schlüssel nicht verfügbar. Wähle in den Einstellungen des Mods ein anderes Modell."},
    {Str::ErrNoFreeQuota, L"Dein Gemini-Tarif hat kein kostenloses Kontingent für „{0}“. Wähle in den Einstellungen des Mods das Modell „Schnell“ oder füge deinem Schlüssel eine Abrechnung hinzu."},
    {Str::ErrNoCredit, L"Das Guthaben deines {0}-Kontos ist aufgebraucht. Füge Guthaben oder eine Zahlungsmethode hinzu und versuche es dann erneut."},
    {Str::ErrTimeout, L"{0} hat nicht rechtzeitig geantwortet. Versuche es gleich noch einmal."},
    {Str::ModelBusy, L"Das gewählte Modell ist gerade nicht verfügbar. Stattdessen antwortet ein schnelleres."},
    {Str::ErrRateLimit, L"Du hast das Anfragelimit von {0} vorerst erreicht. Versuche es gleich noch einmal."},
    {Str::ErrServer, L"{0} hat gerade Probleme ({1}). Versuche es gleich noch einmal."},
    {Str::ErrGeneric, L"{0} hat einen Fehler zurückgegeben ({1})."},
    {Str::ErrNoConnection, L"Die Antwort von {0} konnte nicht empfangen werden. Prüfe deine Internetverbindung (Fehler {1}) und frage erneut."},
    {Str::ErrInterrupted, L"Die Verbindung zu {0} wurde unterbrochen, die Antwort ist unvollständig (Fehler {1}). Frage erneut."},
    {Str::ErrInterruptedBy, L"{0} hat diese Antwort unterbrochen: {1}"},
    {Str::ErrUnreadable, L"{0} hat eine unlesbare Antwort zurückgegeben. Frage erneut."},
    {Str::ErrOutputLimit, L"{0} hat sein Längenlimit erreicht, die Antwort ist unvollständig. Bitte um eine kürzere Antwort."},
    {Str::ErrStoppedBecause, L"{0} hat diese Antwort beendet ({1}). Versuche es mit einer anderen Formulierung."},
    {Str::ErrUnconfirmed, L"{0} hat angehalten, bevor bestätigt war, dass die Antwort vollständig ist. Frage erneut."},
    {Str::ErrNoAnswer, L"{0} hat keine Antwort zurückgegeben. Versuche es mit einer anderen Formulierung."},
    {Str::ErrCouldntReach, L"{0} ist nicht erreichbar. Prüfe deine Internetverbindung (Fehler {1})."},
    {Str::ErrStreaming, L"{0} hat einen Streaming-Fehler zurückgegeben."},
    {Str::LensSearching, L"Suche mit Google Lens…"},
    {Str::LensUploadFailed, L"Das automatische Hochladen ist fehlgeschlagen. Das Bild liegt in der Zwischenablage: Füge es auf lens.google.com ein."},
};

const TextEntry kTexts_el[] = {
    {Str::HintText, L"Επιλέξτε οτιδήποτε για να ρωτήσετε την υπηρεσία {0}"},
    {Str::HintTextTyping, L"Επιλέξτε οτιδήποτε ή ξεκινήστε να πληκτρολογείτε για να ρωτήσετε την υπηρεσία {0}"},
    {Str::Close, L"Κλείσιμο"},
    {Str::AskInGemini, L"Ρωτήστε το Gemini"},
    {Str::SearchWithLens, L"Αναζήτηση με το Google Lens"},
    {Str::TranslateTo, L"Μετάφραση σε: {0}"},
    {Str::CopyImage, L"Αντιγραφή εικόνας"},
    {Str::CopyText, L"Αντιγραφή κειμένου"},
    {Str::AddSelection, L"Προσθήκη άλλης επιλογής"},
    {Str::WhatIsThis, L"Τι είναι αυτό;"},
    {Str::ExplainThis, L"Εξήγησέ μου αυτό"},
    {Str::SummarizeThis, L"Κάνε μου μια περίληψη αυτού"},
    {Str::AskPlaceholder, L"Ρωτήστε για την επιλογή σας…"},
    {Str::AskAnythingPlaceholder, L"Ρωτήστε ό,τι θέλετε…"},
    {Str::FollowUpPlaceholder, L"Κάντε μια συμπληρωματική ερώτηση…"},
    {Str::Thinking, L"Σκέφτομαι…"},
    {Str::Copy, L"Αντιγραφή"},
    {Str::SelectAll, L"Επιλογή όλων"},
    {Str::NoApiKeyHint, L"Προσθέστε ένα κλειδί API για το Gemini, το ChatGPT ή το Claude στις ρυθμίσεις του mod για να λαμβάνετε απαντήσεις εδώ."},
    {Str::ImageCopied, L"Η εικόνα αντιγράφηκε"},
    {Str::ImageCopyFailed, L"Δεν ήταν δυνατή η αντιγραφή της εικόνας"},
    {Str::ImageCopyRetry, L"Δεν ήταν δυνατή η αντιγραφή της εικόνας. Δοκιμάστε ξανά."},
    {Str::ReadingText, L"Το κείμενο διαβάζεται ακόμη…"},
    {Str::NoTextFound, L"Δεν βρέθηκε κείμενο στην επιλογή"},
    {Str::TextCopied, L"Το κείμενο αντιγράφηκε"},
    {Str::TextCopyFailed, L"Δεν ήταν δυνατή η αντιγραφή του κειμένου"},
    {Str::AnswerCopied, L"Η απάντηση αντιγράφηκε"},
    {Str::AnswerCopyFailed, L"Δεν ήταν δυνατή η αντιγραφή της απάντησης"},
    {Str::OpeningLens, L"Άνοιγμα του Google Lens στο πρόγραμμα περιήγησης…"},
    {Str::OpeningGeminiOne, L"Άνοιγμα του Gemini και επισύναψη της εικόνας σας…"},
    {Str::OpeningGeminiMany, L"Άνοιγμα του Gemini και επισύναψη των εικόνων σας…"},
    {Str::OpeningGeminiText, L"Άνοιγμα του Gemini και προσθήκη της ερώτησής σας…"},
    {Str::ClickBoxToAttach, L"Κάντε κλικ στο πλαίσιο μηνύματος του Gemini και πατήστε Ctrl+V για να επισυνάψετε την εικόνα."},
    {Str::Stopped, L"Διακόπηκε."},
    {Str::StoppedEarly, L"Διακόπηκε πριν ολοκληρωθεί η απάντηση."},
    {Str::RequestFailed, L"Δεν ήταν δυνατή η έναρξη του αιτήματος."},
    {Str::DraftAddedOne, L"Η εικόνα προστέθηκε. Πληκτρολογήστε την ερώτησή σας στο Gemini."},
    {Str::DraftAddedMany, L"Οι εικόνες προστέθηκαν. Πληκτρολογήστε την ερώτησή σας στο Gemini."},
    {Str::QuestionInGemini, L"Η ερώτησή σας έχει ήδη γραφτεί στο Gemini."},
    {Str::DraftPartial, L"Επιβεβαιωμένες εικόνες: {0} από {1}. Ελέγξτε το Gemini και προσθέστε τις υπόλοιπες με Ctrl+V στο πλαίσιο μηνύματός του."},
    {Str::ClipboardChangedOne, L"Το πρόχειρο άλλαξε πριν επικολληθεί η εικόνα: χρησιμοποιήστε την Αντιγραφή εικόνας και μετά πατήστε Ctrl+V στο Gemini."},
    {Str::ClipboardChangedMany, L"Το πρόχειρο άλλαξε πριν επικολληθούν οι εικόνες. Ρωτήστε ξανά στο Gemini για να δοκιμάσετε πάλι."},
    {Str::IfNotAttachedOne, L"Αν η εικόνα δεν έχει επισυναφθεί, κάντε κλικ στο πλαίσιο μηνύματος του Gemini και πατήστε Ctrl+V."},
    {Str::IfNotAttachedMany, L"Αν οι εικόνες δεν έχουν επισυναφθεί, κάντε κλικ στο πλαίσιο μηνύματος του Gemini και πατήστε Ctrl+V."},
    {Str::ClickBoxOne, L"Κάντε κλικ στο πλαίσιο μηνύματος του Gemini και πατήστε Ctrl+V για να επισυνάψετε την εικόνα. Η ερώτησή σας διατηρείται εδώ."},
    {Str::ClickBoxMany, L"Κάντε κλικ στο πλαίσιο μηνύματος του Gemini και πατήστε Ctrl+V για να επισυνάψετε τις εικόνες. Η ερώτησή σας διατηρείται εδώ."},
    {Str::ClickBoxText, L"Κάντε κλικ στο πλαίσιο μηνύματος του Gemini και πληκτρολογήστε την ερώτησή σας. Η ερώτησή σας διατηρείται εδώ."},
    {Str::BrowserFailedOne, L"Δεν ήταν δυνατό το άνοιγμα του προγράμματος περιήγησης. Η εικόνα έχει αντιγραφεί· επικολλήστε την στο Gemini με Ctrl+V."},
    {Str::BrowserFailedMany, L"Δεν ήταν δυνατό το άνοιγμα του προγράμματος περιήγησης. Οι εικόνες έχουν αντιγραφεί· επικολλήστε τις στο Gemini με Ctrl+V."},
    {Str::BrowserFailedText, L"Δεν ήταν δυνατό το άνοιγμα του προγράμματος περιήγησης."},
    {Str::PageUnreadable, L"Το Magic Pointer δεν μπόρεσε να διαβάσει τη σελίδα στο πρόγραμμα περιήγησής σας. Αν υπάρχει ανοιχτή ειδοποίηση πάνω της, κλείστε την και κάντε ξανά κλικ στο «Ρωτήστε το Gemini»."},
    {Str::ErrKeyInvalid, L"Το κλειδί API για την υπηρεσία {0} δεν είναι έγκυρο. Ελέγξτε το στις ρυθμίσεις του mod."},
    {Str::ErrKeyForbidden, L"Αυτό το κλειδί API δεν μπορεί να χρησιμοποιήσει την υπηρεσία {0} (403). Ελέγξτε το κλειδί στις ρυθμίσεις του mod."},
    {Str::ErrModelMissing, L"Το μοντέλο «{0}» δεν είναι διαθέσιμο για το κλειδί σας. Επιλέξτε άλλο μοντέλο στις ρυθμίσεις του mod."},
    {Str::ErrNoFreeQuota, L"Το πακέτο σας στο Gemini δεν έχει δωρεάν όριο χρήσης για το «{0}». Επιλέξτε το μοντέλο «Γρήγορο» στις ρυθμίσεις του mod ή προσθέστε χρέωση στο κλειδί σας."},
    {Str::ErrNoCredit, L"Ο λογαριασμός σας στην υπηρεσία {0} δεν έχει πια υπόλοιπο. Προσθέστε υπόλοιπο ή τρόπο πληρωμής και δοκιμάστε ξανά."},
    {Str::ErrTimeout, L"Η υπηρεσία {0} δεν απάντησε εγκαίρως. Δοκιμάστε ξανά σε λίγο."},
    {Str::ModelBusy, L"Το μοντέλο που επιλέξατε δεν είναι διαθέσιμο αυτή τη στιγμή. Απαντά ένα ταχύτερο στη θέση του."},
    {Str::ErrRateLimit, L"Φτάσατε προς το παρόν στο όριο αιτημάτων της υπηρεσίας {0}. Δοκιμάστε ξανά σε λίγο."},
    {Str::ErrServer, L"Η υπηρεσία {0} αντιμετωπίζει προβλήματα αυτή τη στιγμή ({1}). Δοκιμάστε ξανά σε λίγο."},
    {Str::ErrGeneric, L"Η υπηρεσία {0} επέστρεψε σφάλμα ({1})."},
    {Str::ErrNoConnection, L"Δεν ήταν δυνατή η λήψη της απάντησης της υπηρεσίας {0}. Ελέγξτε τη σύνδεσή σας στο διαδίκτυο (σφάλμα {1}). Δοκιμάστε να ρωτήσετε ξανά."},
    {Str::ErrInterrupted, L"Η σύνδεση με την υπηρεσία {0} διακόπηκε. Αυτή η απάντηση είναι ελλιπής (σφάλμα {1}). Δοκιμάστε να ρωτήσετε ξανά."},
    {Str::ErrInterruptedBy, L"Η υπηρεσία {0} διέκοψε αυτή την απάντηση: {1}"},
    {Str::ErrUnreadable, L"Η υπηρεσία {0} επέστρεψε μη αναγνώσιμη απάντηση. Δοκιμάστε να ρωτήσετε ξανά."},
    {Str::ErrOutputLimit, L"Η υπηρεσία {0} έφτασε στο όριο εξόδου της. Αυτή η απάντηση είναι ελλιπής. Δοκιμάστε να ζητήσετε πιο σύντομη απάντηση."},
    {Str::ErrStoppedBecause, L"Η υπηρεσία {0} σταμάτησε αυτή την απάντηση ({1}). Δοκιμάστε να ρωτήσετε με άλλον τρόπο."},
    {Str::ErrUnconfirmed, L"Η υπηρεσία {0} σταμάτησε πριν επιβεβαιώσει ότι η απάντηση ήταν πλήρης. Δοκιμάστε να ρωτήσετε ξανά."},
    {Str::ErrNoAnswer, L"Η υπηρεσία {0} δεν επέστρεψε απάντηση. Δοκιμάστε να ρωτήσετε με άλλον τρόπο."},
    {Str::ErrCouldntReach, L"Δεν ήταν δυνατή η σύνδεση με την υπηρεσία {0}. Ελέγξτε τη σύνδεσή σας στο διαδίκτυο (σφάλμα {1})."},
    {Str::ErrStreaming, L"Η υπηρεσία {0} επέστρεψε σφάλμα ροής."},
    {Str::LensSearching, L"Αναζήτηση με το Google Lens…"},
    {Str::LensUploadFailed, L"Η αυτόματη μεταφόρτωση απέτυχε. Η εικόνα βρίσκεται στο πρόχειρο: επικολλήστε την στο lens.google.com."},
};

const TextEntry kTexts_he[] = {
    {Str::HintText, L"בחרו כל דבר כדי לשאול את {0}"},
    {Str::HintTextTyping, L"בחרו כל דבר או התחילו להקליד כדי לשאול את {0}"},
    {Str::Close, L"סגירה"},
    {Str::AskInGemini, L"שאלו את Gemini"},
    {Str::SearchWithLens, L"חיפוש באמצעות Google Lens"},
    {Str::TranslateTo, L"תרגום לשפה: {0}"},
    {Str::CopyImage, L"העתקת תמונה"},
    {Str::CopyText, L"העתקת טקסט"},
    {Str::AddSelection, L"הוספת בחירה נוספת"},
    {Str::WhatIsThis, L"מה זה?"},
    {Str::ExplainThis, L"הסבר לי את זה"},
    {Str::SummarizeThis, L"סכם לי את זה"},
    {Str::AskPlaceholder, L"שאלו על הבחירה שלכם…"},
    {Str::AskAnythingPlaceholder, L"שאלו כל דבר…"},
    {Str::FollowUpPlaceholder, L"שאלו שאלת המשך…"},
    {Str::Thinking, L"חושב…"},
    {Str::Copy, L"העתקה"},
    {Str::SelectAll, L"בחירת הכול"},
    {Str::NoApiKeyHint, L"הוסיפו מפתח API של Gemini, ChatGPT או Claude בהגדרות המוד כדי לקבל תשובות ישירות כאן."},
    {Str::ImageCopied, L"התמונה הועתקה"},
    {Str::ImageCopyFailed, L"לא ניתן להעתיק את התמונה"},
    {Str::ImageCopyRetry, L"לא ניתן להעתיק את התמונה. נסו שוב."},
    {Str::ReadingText, L"הטקסט עדיין נקרא…"},
    {Str::NoTextFound, L"לא נמצא טקסט בבחירה"},
    {Str::TextCopied, L"הטקסט הועתק"},
    {Str::TextCopyFailed, L"לא ניתן להעתיק את הטקסט"},
    {Str::AnswerCopied, L"התשובה הועתקה"},
    {Str::AnswerCopyFailed, L"לא ניתן להעתיק את התשובה"},
    {Str::OpeningLens, L"פותח את Google Lens בדפדפן…"},
    {Str::OpeningGeminiOne, L"פותח את Gemini ומצרף את התמונה…"},
    {Str::OpeningGeminiMany, L"פותח את Gemini ומצרף את התמונות…"},
    {Str::OpeningGeminiText, L"פותח את Gemini ומוסיף את השאלה שלכם…"},
    {Str::ClickBoxToAttach, L"לחצו על תיבת ההודעה של Gemini ואז הקישו Ctrl+V כדי לצרף את התמונה."},
    {Str::Stopped, L"נעצר."},
    {Str::StoppedEarly, L"נעצר לפני שהתשובה הסתיימה."},
    {Str::RequestFailed, L"לא ניתן היה להתחיל את הבקשה."},
    {Str::DraftAddedOne, L"התמונה נוספה. הקלידו את השאלה שלכם ב-Gemini."},
    {Str::DraftAddedMany, L"התמונות נוספו. הקלידו את השאלה שלכם ב-Gemini."},
    {Str::QuestionInGemini, L"השאלה שלכם נמצאת ב-Gemini."},
    {Str::DraftPartial, L"תמונות שאושרו: {0} מתוך {1}. בדקו את Gemini והוסיפו את השאר באמצעות Ctrl+V בתיבת ההודעה שלו."},
    {Str::ClipboardChangedOne, L"הלוח השתנה לפני שניתן היה להדביק את התמונה: השתמשו בהעתקת תמונה ואז הקישו Ctrl+V ב-Gemini."},
    {Str::ClipboardChangedMany, L"הלוח השתנה לפני שניתן היה להדביק את התמונות. שאלו שוב ב-Gemini כדי לנסות שוב."},
    {Str::IfNotAttachedOne, L"אם התמונה לא צורפה, לחצו על תיבת ההודעה של Gemini והקישו Ctrl+V."},
    {Str::IfNotAttachedMany, L"אם התמונות לא צורפו, לחצו על תיבת ההודעה של Gemini והקישו Ctrl+V."},
    {Str::ClickBoxOne, L"לחצו על תיבת ההודעה של Gemini והקישו Ctrl+V כדי לצרף את התמונה. השאלה שלכם נשמרת כאן."},
    {Str::ClickBoxMany, L"לחצו על תיבת ההודעה של Gemini והקישו Ctrl+V כדי לצרף את התמונות. השאלה שלכם נשמרת כאן."},
    {Str::ClickBoxText, L"לחצו על תיבת ההודעה של Gemini והקלידו את השאלה שלכם. השאלה שלכם נשמרת כאן."},
    {Str::BrowserFailedOne, L"לא ניתן היה לפתוח את הדפדפן. התמונה הועתקה; הדביקו אותה ב-Gemini באמצעות Ctrl+V."},
    {Str::BrowserFailedMany, L"לא ניתן היה לפתוח את הדפדפן. התמונות הועתקו; הדביקו אותן ב-Gemini באמצעות Ctrl+V."},
    {Str::BrowserFailedText, L"לא ניתן היה לפתוח את הדפדפן."},
    {Str::PageUnreadable, L"ה-Magic Pointer לא הצליח לקרוא את הדף בדפדפן שלכם. אם מעליו פתוחה התראה, סגרו אותה ולחצו שוב על 'שאלו את Gemini'."},
    {Str::ErrKeyInvalid, L"מפתח ה-API של {0} שלכם אינו תקין. בדקו אותו בהגדרות המוד."},
    {Str::ErrKeyForbidden, L"מפתח API זה אינו יכול להשתמש ב-{0} (403). בדקו את המפתח בהגדרות המוד."},
    {Str::ErrModelMissing, L"המודל \"{0}\" אינו זמין עבור המפתח שלכם. בחרו מודל אחר בהגדרות המוד."},
    {Str::ErrNoFreeQuota, L"בתוכנית Gemini שלכם אין מכסה חינמית עבור \"{0}\". בחרו בהגדרות המוד את המודל \"מהיר\", או הוסיפו חיוב למפתח שלכם."},
    {Str::ErrNoCredit, L"היתרה בחשבון ה-{0} שלכם אזלה. הוסיפו יתרה או אמצעי תשלום ונסו שוב."},
    {Str::ErrTimeout, L"{0} לא ענה בזמן. נסו שוב בעוד רגע."},
    {Str::ModelBusy, L"המודל שבחרתם אינו זמין כרגע. מודל מהיר יותר עונה במקומו."},
    {Str::ErrRateLimit, L"הגעתם זמנית למגבלת הבקשות של {0}. נסו שוב בעוד רגע."},
    {Str::ErrServer, L"ל-{0} יש כרגע בעיות ({1}). נסו שוב בעוד רגע."},
    {Str::ErrGeneric, L"שגיאה הוחזרה מ-{0} ({1})."},
    {Str::ErrNoConnection, L"לא ניתן היה לקבל את התשובה של {0}. בדקו את חיבור האינטרנט שלכם (שגיאה {1}). נסו לשאול שוב."},
    {Str::ErrInterrupted, L"החיבור ל-{0} נותק. התשובה הזו לא שלמה (שגיאה {1}). נסו לשאול שוב."},
    {Str::ErrInterruptedBy, L"התשובה הזו נקטעה על ידי {0}: {1}"},
    {Str::ErrUnreadable, L"התקבלה מ-{0} תגובה שאינה ניתנת לקריאה. נסו לשאול שוב."},
    {Str::ErrOutputLimit, L"הפלט של {0} הגיע למגבלה. התשובה הזו לא שלמה. נסו לבקש תשובה קצרה יותר."},
    {Str::ErrStoppedBecause, L"התשובה הזו נעצרה על ידי {0} ({1}). נסו לשאול בדרך אחרת."},
    {Str::ErrUnconfirmed, L"העצירה של {0} התרחשה לפני שאושר שהתשובה שלמה. נסו לשאול שוב."},
    {Str::ErrNoAnswer, L"לא התקבלה תשובה מ-{0}. נסו לשאול בדרך אחרת."},
    {Str::ErrCouldntReach, L"לא ניתן היה להתחבר ל-{0}. בדקו את חיבור האינטרנט שלכם (שגיאה {1})."},
    {Str::ErrStreaming, L"התקבלה שגיאת הזרמה מ-{0}."},
    {Str::LensSearching, L"מחפש באמצעות Google Lens…"},
    {Str::LensUploadFailed, L"ההעלאה האוטומטית נכשלה. התמונה נמצאת בלוח: הדביקו אותה ב-lens.google.com."},
};

const TextEntry kTexts_hi[] = {
    {Str::HintText, L"{0} से पूछने के लिए कुछ भी चुनें"},
    {Str::HintTextTyping, L"{0} से पूछने के लिए कुछ भी चुनें या टाइप करना शुरू करें"},
    {Str::Close, L"बंद करें"},
    {Str::AskInGemini, L"Gemini से पूछें"},
    {Str::SearchWithLens, L"Google Lens से खोजें"},
    {Str::TranslateTo, L"अनुवाद की भाषा: {0}"},
    {Str::CopyImage, L"इमेज कॉपी करें"},
    {Str::CopyText, L"टेक्स्ट कॉपी करें"},
    {Str::AddSelection, L"एक और चयन जोड़ें"},
    {Str::WhatIsThis, L"यह क्या है?"},
    {Str::ExplainThis, L"मुझे इसके बारे में समझाएँ"},
    {Str::SummarizeThis, L"इसका सारांश दें"},
    {Str::AskPlaceholder, L"अपने चयन के बारे में पूछें…"},
    {Str::AskAnythingPlaceholder, L"कुछ भी पूछें…"},
    {Str::FollowUpPlaceholder, L"आगे कुछ और पूछें…"},
    {Str::Thinking, L"सोच रहा हूँ…"},
    {Str::Copy, L"कॉपी करें"},
    {Str::SelectAll, L"सभी चुनें"},
    {Str::NoApiKeyHint, L"जवाब यहीं पाने के लिए मॉड की सेटिंग में Gemini, ChatGPT या Claude की API कुंजी जोड़ें।"},
    {Str::ImageCopied, L"इमेज कॉपी हो गई"},
    {Str::ImageCopyFailed, L"इमेज कॉपी नहीं हो सकी"},
    {Str::ImageCopyRetry, L"इमेज कॉपी नहीं हो सकी। फिर से कोशिश करें।"},
    {Str::ReadingText, L"टेक्स्ट अब भी पढ़ा जा रहा है…"},
    {Str::NoTextFound, L"चयन में कोई टेक्स्ट नहीं मिला"},
    {Str::TextCopied, L"टेक्स्ट कॉपी हो गया"},
    {Str::TextCopyFailed, L"टेक्स्ट कॉपी नहीं हो सका"},
    {Str::AnswerCopied, L"जवाब कॉपी हो गया"},
    {Str::AnswerCopyFailed, L"जवाब कॉपी नहीं हो सका"},
    {Str::OpeningLens, L"आपके ब्राउज़र में Google Lens खोला जा रहा है…"},
    {Str::OpeningGeminiOne, L"Gemini खोलकर आपकी इमेज अटैच की जा रही है…"},
    {Str::OpeningGeminiMany, L"Gemini खोलकर आपकी इमेज अटैच की जा रही हैं…"},
    {Str::OpeningGeminiText, L"Gemini खोलकर आपका सवाल जोड़ा जा रहा है…"},
    {Str::ClickBoxToAttach, L"Gemini के मैसेज बॉक्स पर क्लिक करें, फिर इमेज अटैच करने के लिए Ctrl+V दबाएँ।"},
    {Str::Stopped, L"रोक दिया गया।"},
    {Str::StoppedEarly, L"जवाब पूरा होने से पहले ही रोक दिया गया।"},
    {Str::RequestFailed, L"अनुरोध शुरू नहीं हो सका।"},
    {Str::DraftAddedOne, L"इमेज जुड़ गई है। अब Gemini में अपना सवाल लिखें।"},
    {Str::DraftAddedMany, L"इमेज जुड़ गई हैं। अब Gemini में अपना सवाल लिखें।"},
    {Str::QuestionInGemini, L"आपका सवाल Gemini में लिख दिया गया है।"},
    {Str::DraftPartial, L"{1} में से {0} इमेज की पुष्टि हो सकी। Gemini देखें और बाकी इमेज उसके मैसेज बॉक्स में Ctrl+V से पेस्ट करें।"},
    {Str::ClipboardChangedOne, L"इमेज पेस्ट होने से पहले क्लिपबोर्ड बदल गया: \"इमेज कॉपी करें\" का इस्तेमाल करें, फिर Gemini में Ctrl+V दबाएँ।"},
    {Str::ClipboardChangedMany, L"इमेज पेस्ट होने से पहले क्लिपबोर्ड बदल गया। दोबारा कोशिश करने के लिए Gemini में फिर से पूछें।"},
    {Str::IfNotAttachedOne, L"अगर इमेज अटैच नहीं हुई है, तो Gemini के मैसेज बॉक्स पर क्लिक करें और Ctrl+V दबाएँ।"},
    {Str::IfNotAttachedMany, L"अगर इमेज अटैच नहीं हुई हैं, तो Gemini के मैसेज बॉक्स पर क्लिक करें और Ctrl+V दबाएँ।"},
    {Str::ClickBoxOne, L"Gemini के मैसेज बॉक्स पर क्लिक करें और इमेज अटैच करने के लिए Ctrl+V दबाएँ। आपका सवाल यहाँ सुरक्षित है।"},
    {Str::ClickBoxMany, L"Gemini के मैसेज बॉक्स पर क्लिक करें और सभी इमेज अटैच करने के लिए Ctrl+V दबाएँ। आपका सवाल यहाँ सुरक्षित है।"},
    {Str::ClickBoxText, L"Gemini के मैसेज बॉक्स पर क्लिक करें और अपना सवाल टाइप करें। आपका सवाल यहाँ सुरक्षित है।"},
    {Str::BrowserFailedOne, L"ब्राउज़र नहीं खुल सका। इमेज कॉपी हो चुकी है; उसे Ctrl+V से Gemini में पेस्ट करें।"},
    {Str::BrowserFailedMany, L"ब्राउज़र नहीं खुल सका। इमेज कॉपी हो चुकी हैं; उन्हें Ctrl+V से Gemini में पेस्ट करें।"},
    {Str::BrowserFailedText, L"ब्राउज़र नहीं खुल सका।"},
    {Str::PageUnreadable, L"Magic Pointer आपके ब्राउज़र का पेज नहीं पढ़ सका। अगर पेज के ऊपर कोई नोटिफ़िकेशन खुला है, तो उसे बंद करें और \"Gemini से पूछें\" पर फिर से क्लिक करें।"},
    {Str::ErrKeyInvalid, L"आपकी {0} API कुंजी मान्य नहीं है। मॉड की सेटिंग में जाकर इसे जाँचें।"},
    {Str::ErrKeyForbidden, L"यह API कुंजी {0} का इस्तेमाल नहीं कर सकती (403)। मॉड की सेटिंग में कुंजी जाँचें।"},
    {Str::ErrModelMissing, L"\"{0}\" मॉडल आपकी कुंजी के लिए उपलब्ध नहीं है। मॉड की सेटिंग में कोई दूसरा मॉडल चुनें।"},
    {Str::ErrNoFreeQuota, L"आपके Gemini प्लान में \"{0}\" के लिए मुफ़्त कोटा नहीं है। मॉड की सेटिंग में \"तेज़\" मॉडल चुनें, या अपनी कुंजी के लिए बिलिंग चालू करें।"},
    {Str::ErrNoCredit, L"आपके {0} खाते का क्रेडिट खत्म हो गया है। क्रेडिट या भुगतान का तरीका जोड़ें, फिर दोबारा कोशिश करें।"},
    {Str::ErrTimeout, L"{0} ने समय पर जवाब नहीं दिया। थोड़ी देर बाद फिर कोशिश करें।"},
    {Str::ModelBusy, L"आपका चुना हुआ मॉडल अभी उपलब्ध नहीं है। उसकी जगह एक तेज़ मॉडल जवाब दे रहा है।"},
    {Str::ErrRateLimit, L"फ़िलहाल {0} की अनुरोध सीमा पूरी हो गई है। थोड़ी देर बाद फिर कोशिश करें।"},
    {Str::ErrServer, L"{0} में अभी कोई समस्या आ रही है ({1})। थोड़ी देर बाद फिर कोशिश करें।"},
    {Str::ErrGeneric, L"{0} से त्रुटि मिली ({1})।"},
    {Str::ErrNoConnection, L"{0} का जवाब नहीं मिल सका। अपना इंटरनेट कनेक्शन जाँचें (त्रुटि {1}) और फिर से पूछें।"},
    {Str::ErrInterrupted, L"{0} से कनेक्शन टूट गया, इसलिए यह जवाब अधूरा है (त्रुटि {1})। फिर से पूछें।"},
    {Str::ErrInterruptedBy, L"{0} ने यह जवाब बीच में रोक दिया: {1}"},
    {Str::ErrUnreadable, L"{0} से ऐसा जवाब मिला जिसे पढ़ा नहीं जा सकता। फिर से पूछें।"},
    {Str::ErrOutputLimit, L"{0} अपनी आउटपुट सीमा तक पहुँच गया, इसलिए यह जवाब अधूरा है। छोटा जवाब माँगकर देखें।"},
    {Str::ErrStoppedBecause, L"{0} ने यह जवाब रोक दिया ({1})। सवाल को दूसरे तरीके से पूछकर देखें।"},
    {Str::ErrUnconfirmed, L"जवाब पूरा होने की पुष्टि से पहले ही {0} रुक गया। फिर से पूछें।"},
    {Str::ErrNoAnswer, L"{0} ने कोई जवाब नहीं दिया। सवाल को दूसरे तरीके से पूछकर देखें।"},
    {Str::ErrCouldntReach, L"{0} से संपर्क नहीं हो सका। अपना इंटरनेट कनेक्शन जाँचें (त्रुटि {1})।"},
    {Str::ErrStreaming, L"{0} में स्ट्रीमिंग त्रुटि हुई।"},
    {Str::LensSearching, L"Google Lens से खोजा जा रहा है…"},
    {Str::LensUploadFailed, L"अपने-आप अपलोड नहीं हो सका। इमेज आपके क्लिपबोर्ड में है: उसे lens.google.com पर पेस्ट करें।"},
};

const TextEntry kTexts_hu[] = {
    {Str::HintText, L"Válassz ki bármit, és kérdezd meg az MI-t ({0})"},
    {Str::HintTextTyping, L"Válassz ki bármit, vagy kezdj el gépelni, és kérdezd meg az MI-t ({0})"},
    {Str::Close, L"Bezárás"},
    {Str::AskInGemini, L"Kérdés a Geminitől"},
    {Str::SearchWithLens, L"Keresés a Google Lensszel"},
    {Str::TranslateTo, L"Fordítás erre: {0}"},
    {Str::CopyImage, L"Kép másolása"},
    {Str::CopyText, L"Szöveg másolása"},
    {Str::AddSelection, L"Újabb kijelölés hozzáadása"},
    {Str::WhatIsThis, L"Mi ez?"},
    {Str::ExplainThis, L"Magyarázd el ezt"},
    {Str::SummarizeThis, L"Foglald ezt össze"},
    {Str::AskPlaceholder, L"Kérdezz a kijelölésről…"},
    {Str::AskAnythingPlaceholder, L"Kérdezz bármit…"},
    {Str::FollowUpPlaceholder, L"Tegyél fel egy követő kérdést…"},
    {Str::Thinking, L"Gondolkodom…"},
    {Str::Copy, L"Másolás"},
    {Str::SelectAll, L"Az összes kijelölése"},
    {Str::NoApiKeyHint, L"Adj hozzá egy Gemini-, ChatGPT- vagy Claude-API-kulcsot a mod beállításaiban, hogy a válaszokat itt kapd meg."},
    {Str::ImageCopied, L"Kép kimásolva"},
    {Str::ImageCopyFailed, L"A kép másolása nem sikerült"},
    {Str::ImageCopyRetry, L"A kép másolása nem sikerült. Próbáld újra."},
    {Str::ReadingText, L"A szöveg beolvasása még folyamatban van…"},
    {Str::NoTextFound, L"Nem található szöveg a kijelölésben"},
    {Str::TextCopied, L"Szöveg kimásolva"},
    {Str::TextCopyFailed, L"A szöveg másolása nem sikerült"},
    {Str::AnswerCopied, L"Válasz kimásolva"},
    {Str::AnswerCopyFailed, L"A válasz másolása nem sikerült"},
    {Str::OpeningLens, L"A Google Lens megnyitása a böngészőben…"},
    {Str::OpeningGeminiOne, L"A Gemini megnyitása és a kép csatolása…"},
    {Str::OpeningGeminiMany, L"A Gemini megnyitása és a képek csatolása…"},
    {Str::OpeningGeminiText, L"A Gemini megnyitása és a kérdésed hozzáadása…"},
    {Str::ClickBoxToAttach, L"Kattints a Gemini üzenetmezőjére, majd nyomd meg a Ctrl+V billentyűkombinációt a kép csatolásához."},
    {Str::Stopped, L"Leállítva."},
    {Str::StoppedEarly, L"Leállítva, mielőtt a válasz elkészült volna."},
    {Str::RequestFailed, L"A kérést nem sikerült elindítani."},
    {Str::DraftAddedOne, L"A kép hozzáadva. Írd be a kérdésedet a Geminibe."},
    {Str::DraftAddedMany, L"A képek hozzáadva. Írd be a kérdésedet a Geminibe."},
    {Str::QuestionInGemini, L"A kérdésed már a Geminiben van."},
    {Str::DraftPartial, L"Megerősített képek: {0} / {1}. Ellenőrizd a Geminit, és add hozzá a többit a Ctrl+V megnyomásával az üzenetmezőben."},
    {Str::ClipboardChangedOne, L"A vágólap tartalma megváltozott, mielőtt a képet be lehetett volna illeszteni: használd a Kép másolása parancsot, majd nyomd meg a Ctrl+V billentyűkombinációt a Geminiben."},
    {Str::ClipboardChangedMany, L"A vágólap tartalma megváltozott, mielőtt a képeket be lehetett volna illeszteni. Kérdezz újra a Geminiben az újrapróbálkozáshoz."},
    {Str::IfNotAttachedOne, L"Ha a kép nincs csatolva, kattints a Gemini üzenetmezőjére, és nyomd meg a Ctrl+V billentyűkombinációt."},
    {Str::IfNotAttachedMany, L"Ha a képek nincsenek csatolva, kattints a Gemini üzenetmezőjére, és nyomd meg a Ctrl+V billentyűkombinációt."},
    {Str::ClickBoxOne, L"Kattints a Gemini üzenetmezőjére, majd nyomd meg a Ctrl+V billentyűkombinációt a kép csatolásához. A kérdésed itt megmarad."},
    {Str::ClickBoxMany, L"Kattints a Gemini üzenetmezőjére, majd nyomd meg a Ctrl+V billentyűkombinációt a képek csatolásához. A kérdésed itt megmarad."},
    {Str::ClickBoxText, L"Kattints a Gemini üzenetmezőjére, és írd be a kérdésed. A kérdésed itt megmarad."},
    {Str::BrowserFailedOne, L"A böngészőt nem sikerült megnyitni. A kép ki van másolva; illeszd be a Geminibe a Ctrl+V billentyűkombinációval."},
    {Str::BrowserFailedMany, L"A böngészőt nem sikerült megnyitni. A képek ki vannak másolva; illeszd be őket a Geminibe a Ctrl+V billentyűkombinációval."},
    {Str::BrowserFailedText, L"A böngészőt nem sikerült megnyitni."},
    {Str::PageUnreadable, L"A Magic Pointer nem tudta elolvasni az oldalt a böngészőben. Ha fölötte értesítés van nyitva, zárd be, és kattints újra a Kérdés a Geminitől gombra."},
    {Str::ErrKeyInvalid, L"A(z) {0} API-kulcsod érvénytelen. Ellenőrizd a mod beállításaiban."},
    {Str::ErrKeyForbidden, L"Ez az API-kulcs nem használhatja a(z) {0} szolgáltatást (403). Ellenőrizd a kulcsot a mod beállításaiban."},
    {Str::ErrModelMissing, L"A(z) „{0}” modell nem érhető el a kulcsoddal. Válassz másik modellt a mod beállításaiban."},
    {Str::ErrNoFreeQuota, L"A Gemini-csomagodban nincs ingyenes kvóta a(z) „{0}” modellhez. Válaszd a „Gyors” modellt a mod beállításaiban, vagy add hozzá a számlázást a kulcsodhoz."},
    {Str::ErrNoCredit, L"A(z) {0}-fiókodban elfogyott a kredit. Tölts fel kreditet, vagy adj meg fizetési módot, majd próbáld újra."},
    {Str::ErrTimeout, L"A(z) {0} szolgáltatás nem válaszolt időben. Próbáld újra egy kis idő múlva."},
    {Str::ModelBusy, L"A kiválasztott modell most nem érhető el. Helyette egy gyorsabb válaszol."},
    {Str::ErrRateLimit, L"Egyelőre elérted a(z) {0} kérési korlátját. Próbáld újra egy kis idő múlva."},
    {Str::ErrServer, L"A(z) {0} szolgáltatással jelenleg probléma van ({1}). Próbáld újra egy kis idő múlva."},
    {Str::ErrGeneric, L"A(z) {0} szolgáltatás hibát adott vissza ({1})."},
    {Str::ErrNoConnection, L"A(z) {0} válaszát nem sikerült fogadni. Ellenőrizd az internetkapcsolatot (hibakód: {1}). Próbálj újra kérdezni."},
    {Str::ErrInterrupted, L"A(z) {0} szolgáltatással való kapcsolat megszakadt. Ez a válasz hiányos (hibakód: {1}). Próbálj újra kérdezni."},
    {Str::ErrInterruptedBy, L"A(z) {0} szolgáltatás megszakította ezt a választ: {1}"},
    {Str::ErrUnreadable, L"A(z) {0} szolgáltatás olvashatatlan választ adott vissza. Próbálj újra kérdezni."},
    {Str::ErrOutputLimit, L"A(z) {0} szolgáltatás elérte a kimeneti korlátját. Ez a válasz hiányos. Próbálj rövidebb választ kérni."},
    {Str::ErrStoppedBecause, L"A(z) {0} szolgáltatás leállította ezt a választ ({1}). Próbáld másképp megfogalmazni a kérdést."},
    {Str::ErrUnconfirmed, L"A(z) {0} szolgáltatás leállt, mielőtt megerősítette volna, hogy a válasz teljes. Próbálj újra kérdezni."},
    {Str::ErrNoAnswer, L"A(z) {0} szolgáltatás nem adott vissza választ. Próbáld másképp megfogalmazni a kérdést."},
    {Str::ErrCouldntReach, L"A(z) {0} szolgáltatás nem érhető el. Ellenőrizd az internetkapcsolatot (hibakód: {1})."},
    {Str::ErrStreaming, L"A(z) {0} szolgáltatás streamelési hibát adott vissza."},
    {Str::LensSearching, L"Keresés a Google Lensszel…"},
    {Str::LensUploadFailed, L"Az automatikus feltöltés nem sikerült. A kép a vágólapon van: illeszd be a lens.google.com oldalon."},
};

const TextEntry kTexts_id[] = {
    {Str::HintText, L"Pilih apa saja untuk bertanya kepada {0}"},
    {Str::HintTextTyping, L"Pilih apa saja atau mulai mengetik untuk bertanya kepada {0}"},
    {Str::Close, L"Tutup"},
    {Str::AskInGemini, L"Tanya Gemini"},
    {Str::SearchWithLens, L"Cari dengan Google Lens"},
    {Str::TranslateTo, L"Terjemahkan ke: {0}"},
    {Str::CopyImage, L"Salin gambar"},
    {Str::CopyText, L"Salin teks"},
    {Str::AddSelection, L"Tambahkan pilihan lain"},
    {Str::WhatIsThis, L"Apa ini?"},
    {Str::ExplainThis, L"Jelaskan ini"},
    {Str::SummarizeThis, L"Ringkas ini"},
    {Str::AskPlaceholder, L"Tanyakan tentang pilihan Anda…"},
    {Str::AskAnythingPlaceholder, L"Tanyakan apa saja…"},
    {Str::FollowUpPlaceholder, L"Ajukan pertanyaan lanjutan…"},
    {Str::Thinking, L"Sedang berpikir…"},
    {Str::Copy, L"Salin"},
    {Str::SelectAll, L"Pilih semua"},
    {Str::NoApiKeyHint, L"Tambahkan kunci API Gemini, ChatGPT, atau Claude di pengaturan mod untuk mendapatkan jawaban langsung di sini."},
    {Str::ImageCopied, L"Gambar disalin"},
    {Str::ImageCopyFailed, L"Tidak dapat menyalin gambar"},
    {Str::ImageCopyRetry, L"Tidak dapat menyalin gambar. Coba lagi."},
    {Str::ReadingText, L"Teks masih dibaca…"},
    {Str::NoTextFound, L"Tidak ada teks yang ditemukan dalam pilihan"},
    {Str::TextCopied, L"Teks disalin"},
    {Str::TextCopyFailed, L"Tidak dapat menyalin teks"},
    {Str::AnswerCopied, L"Jawaban disalin"},
    {Str::AnswerCopyFailed, L"Tidak dapat menyalin jawaban"},
    {Str::OpeningLens, L"Membuka Google Lens di browser Anda…"},
    {Str::OpeningGeminiOne, L"Membuka Gemini dan melampirkan gambar Anda…"},
    {Str::OpeningGeminiMany, L"Membuka Gemini dan melampirkan gambar-gambar Anda…"},
    {Str::OpeningGeminiText, L"Membuka Gemini dan menambahkan pertanyaan Anda…"},
    {Str::ClickBoxToAttach, L"Klik kotak pesan Gemini, lalu tekan Ctrl+V untuk melampirkan gambar."},
    {Str::Stopped, L"Dihentikan."},
    {Str::StoppedEarly, L"Dihentikan sebelum jawaban selesai."},
    {Str::RequestFailed, L"Tidak dapat memulai permintaan."},
    {Str::DraftAddedOne, L"Gambar telah ditambahkan. Ketik pertanyaan Anda di Gemini."},
    {Str::DraftAddedMany, L"Gambar-gambar telah ditambahkan. Ketik pertanyaan Anda di Gemini."},
    {Str::QuestionInGemini, L"Pertanyaan Anda sudah dimasukkan ke Gemini."},
    {Str::DraftPartial, L"Gambar yang terkonfirmasi: {0} dari {1}. Periksa Gemini dan tambahkan sisanya dengan Ctrl+V di kotak pesannya."},
    {Str::ClipboardChangedOne, L"Papan klip berubah sebelum gambar dapat ditempel: gunakan Salin gambar, lalu tekan Ctrl+V di Gemini."},
    {Str::ClipboardChangedMany, L"Papan klip berubah sebelum gambar-gambar dapat ditempel. Tanya lagi di Gemini untuk mencoba kembali."},
    {Str::IfNotAttachedOne, L"Jika gambar tidak terlampir, klik kotak pesan Gemini dan tekan Ctrl+V."},
    {Str::IfNotAttachedMany, L"Jika gambar-gambar tidak terlampir, klik kotak pesan Gemini dan tekan Ctrl+V."},
    {Str::ClickBoxOne, L"Klik kotak pesan Gemini dan tekan Ctrl+V untuk melampirkan gambar. Pertanyaan Anda tetap tersimpan di sini."},
    {Str::ClickBoxMany, L"Klik kotak pesan Gemini dan tekan Ctrl+V untuk melampirkan gambar-gambar. Pertanyaan Anda tetap tersimpan di sini."},
    {Str::ClickBoxText, L"Klik kotak pesan Gemini lalu ketik pertanyaan Anda. Pertanyaan Anda tetap tersimpan di sini."},
    {Str::BrowserFailedOne, L"Tidak dapat membuka browser. Gambar sudah disalin; tempelkan ke Gemini dengan Ctrl+V."},
    {Str::BrowserFailedMany, L"Tidak dapat membuka browser. Gambar-gambar sudah disalin; tempelkan ke Gemini dengan Ctrl+V."},
    {Str::BrowserFailedText, L"Tidak dapat membuka browser."},
    {Str::PageUnreadable, L"Magic Pointer tidak dapat membaca halaman di browser Anda. Jika ada pemberitahuan terbuka di atasnya, tutup dan klik Tanya Gemini lagi."},
    {Str::ErrKeyInvalid, L"Kunci API {0} Anda tidak valid. Periksa di pengaturan mod."},
    {Str::ErrKeyForbidden, L"Kunci API ini tidak dapat menggunakan {0} (403). Periksa kunci di pengaturan mod."},
    {Str::ErrModelMissing, L"Model \"{0}\" tidak tersedia untuk kunci Anda. Pilih model lain di pengaturan mod."},
    {Str::ErrNoFreeQuota, L"Paket Gemini Anda tidak memiliki kuota gratis untuk \"{0}\". Pilih model Cepat di pengaturan mod, atau tambahkan penagihan ke kunci Anda."},
    {Str::ErrNoCredit, L"Kredit akun {0} Anda habis. Tambahkan kredit atau metode pembayaran, lalu coba lagi."},
    {Str::ErrTimeout, L"{0} tidak menjawab tepat waktu. Coba lagi sebentar lagi."},
    {Str::ModelBusy, L"Model yang Anda pilih sedang tidak tersedia. Model yang lebih cepat menjawab sebagai gantinya."},
    {Str::ErrRateLimit, L"Anda telah mencapai batas permintaan {0} untuk saat ini. Coba lagi sebentar lagi."},
    {Str::ErrServer, L"{0} sedang mengalami masalah ({1}). Coba lagi sebentar lagi."},
    {Str::ErrGeneric, L"{0} mengembalikan kesalahan ({1})."},
    {Str::ErrNoConnection, L"Tidak dapat menerima jawaban {0}. Periksa koneksi internet Anda (kesalahan {1}). Coba tanyakan lagi."},
    {Str::ErrInterrupted, L"Koneksi ke {0} terputus. Jawaban ini tidak lengkap (kesalahan {1}). Coba tanyakan lagi."},
    {Str::ErrInterruptedBy, L"{0} menghentikan jawaban ini: {1}"},
    {Str::ErrUnreadable, L"{0} mengembalikan respons yang tidak terbaca. Coba tanyakan lagi."},
    {Str::ErrOutputLimit, L"{0} mencapai batas keluarannya. Jawaban ini tidak lengkap. Coba minta jawaban yang lebih singkat."},
    {Str::ErrStoppedBecause, L"{0} menghentikan jawaban ini ({1}). Coba tanyakan dengan cara lain."},
    {Str::ErrUnconfirmed, L"{0} berhenti sebelum memastikan bahwa jawabannya sudah lengkap. Coba tanyakan lagi."},
    {Str::ErrNoAnswer, L"{0} tidak mengembalikan jawaban. Coba tanyakan dengan cara lain."},
    {Str::ErrCouldntReach, L"Tidak dapat menjangkau {0}. Periksa koneksi internet Anda (kesalahan {1})."},
    {Str::ErrStreaming, L"{0} mengembalikan kesalahan streaming."},
    {Str::LensSearching, L"Mencari dengan Google Lens…"},
    {Str::LensUploadFailed, L"Tidak dapat mengunggah secara otomatis. Gambar ada di papan klip: tempelkan di lens.google.com."},
};

const TextEntry kTexts_it[] = {
    {Str::HintText, L"Seleziona qualcosa per chiedere a {0}"},
    {Str::HintTextTyping, L"Seleziona qualcosa o inizia a scrivere per chiedere a {0}"},
    {Str::Close, L"Chiudi"},
    {Str::AskInGemini, L"Chiedi a Gemini"},
    {Str::SearchWithLens, L"Cerca con Google Lens"},
    {Str::TranslateTo, L"Traduci in: {0}"},
    {Str::CopyImage, L"Copia immagine"},
    {Str::CopyText, L"Copia testo"},
    {Str::AddSelection, L"Aggiungi un'altra selezione"},
    {Str::WhatIsThis, L"Che cos'è?"},
    {Str::ExplainThis, L"Spiegamelo"},
    {Str::SummarizeThis, L"Riassumilo per me"},
    {Str::AskPlaceholder, L"Fai una domanda sulla selezione…"},
    {Str::AskAnythingPlaceholder, L"Chiedi qualsiasi cosa…"},
    {Str::FollowUpPlaceholder, L"Fai un'altra domanda…"},
    {Str::Thinking, L"Sto pensando…"},
    {Str::Copy, L"Copia"},
    {Str::SelectAll, L"Seleziona tutto"},
    {Str::NoApiKeyHint, L"Aggiungi una chiave API di Gemini, ChatGPT o Claude nelle impostazioni della mod per ricevere le risposte direttamente qui."},
    {Str::ImageCopied, L"Immagine copiata"},
    {Str::ImageCopyFailed, L"Impossibile copiare l'immagine"},
    {Str::ImageCopyRetry, L"Impossibile copiare l'immagine. Riprova."},
    {Str::ReadingText, L"Lettura del testo in corso…"},
    {Str::NoTextFound, L"Nessun testo trovato nella selezione"},
    {Str::TextCopied, L"Testo copiato"},
    {Str::TextCopyFailed, L"Impossibile copiare il testo"},
    {Str::AnswerCopied, L"Risposta copiata"},
    {Str::AnswerCopyFailed, L"Impossibile copiare la risposta"},
    {Str::OpeningLens, L"Apertura di Google Lens nel browser…"},
    {Str::OpeningGeminiOne, L"Apro Gemini e allego l'immagine…"},
    {Str::OpeningGeminiMany, L"Apro Gemini e allego le immagini…"},
    {Str::OpeningGeminiText, L"Apro Gemini e aggiungo la tua domanda…"},
    {Str::ClickBoxToAttach, L"Fai clic nel campo di testo di Gemini, poi premi Ctrl+V per allegare l'immagine."},
    {Str::Stopped, L"Interrotto."},
    {Str::StoppedEarly, L"Interrotto prima della fine della risposta."},
    {Str::RequestFailed, L"Impossibile avviare la richiesta."},
    {Str::DraftAddedOne, L"Immagine aggiunta. Scrivi la tua domanda in Gemini."},
    {Str::DraftAddedMany, L"Immagini aggiunte. Scrivi la tua domanda in Gemini."},
    {Str::QuestionInGemini, L"La tua domanda è già in Gemini."},
    {Str::DraftPartial, L"Immagini confermate: {0} su {1}. Controlla Gemini e aggiungi le altre con Ctrl+V nel campo di testo."},
    {Str::ClipboardChangedOne, L"Gli appunti sono cambiati prima che l'immagine fosse incollata: usa «Copia immagine», poi premi Ctrl+V in Gemini."},
    {Str::ClipboardChangedMany, L"Gli appunti sono cambiati prima che le immagini fossero incollate. Chiedi di nuovo in Gemini per riprovare."},
    {Str::IfNotAttachedOne, L"Se l'immagine non è allegata, fai clic nel campo di testo di Gemini e premi Ctrl+V."},
    {Str::IfNotAttachedMany, L"Se le immagini non sono allegate, fai clic nel campo di testo di Gemini e premi Ctrl+V."},
    {Str::ClickBoxOne, L"Fai clic nel campo di testo di Gemini e premi Ctrl+V per allegare l'immagine. La tua domanda resta qui."},
    {Str::ClickBoxMany, L"Fai clic nel campo di testo di Gemini e premi Ctrl+V per allegare le immagini. La tua domanda resta qui."},
    {Str::ClickBoxText, L"Fai clic nel campo di testo di Gemini e scrivi la tua domanda. La tua domanda resta qui."},
    {Str::BrowserFailedOne, L"Impossibile aprire il browser. L'immagine è stata copiata: incollala in Gemini con Ctrl+V."},
    {Str::BrowserFailedMany, L"Impossibile aprire il browser. Le immagini sono state copiate: incollale in Gemini con Ctrl+V."},
    {Str::BrowserFailedText, L"Impossibile aprire il browser."},
    {Str::PageUnreadable, L"Magic Pointer non è riuscito a leggere la pagina nel browser. Se sopra la pagina c'è una notifica aperta, chiudila e fai di nuovo clic su «Chiedi a Gemini»."},
    {Str::ErrKeyInvalid, L"La chiave API di {0} non è valida. Controllala nelle impostazioni della mod."},
    {Str::ErrKeyForbidden, L"Questa chiave API non può usare {0} (403). Controllala nelle impostazioni della mod."},
    {Str::ErrModelMissing, L"Il modello «{0}» non è disponibile con la tua chiave. Scegli un altro modello nelle impostazioni della mod."},
    {Str::ErrNoFreeQuota, L"Il tuo piano di Gemini non include quota gratuita per «{0}». Scegli il modello «Veloce» nelle impostazioni della mod oppure attiva la fatturazione per la tua chiave."},
    {Str::ErrNoCredit, L"Il credito del tuo account {0} è esaurito. Aggiungi credito o un metodo di pagamento e riprova."},
    {Str::ErrTimeout, L"{0} non ha risposto in tempo. Riprova tra poco."},
    {Str::ModelBusy, L"Il modello scelto non è disponibile al momento. Risponde invece uno più veloce."},
    {Str::ErrRateLimit, L"Hai raggiunto per ora il limite di richieste di {0}. Riprova tra poco."},
    {Str::ErrServer, L"{0} ha dei problemi al momento ({1}). Riprova tra poco."},
    {Str::ErrGeneric, L"{0} ha restituito un errore ({1})."},
    {Str::ErrNoConnection, L"Impossibile ricevere la risposta di {0}. Controlla la connessione a Internet (errore {1}) e riprova a chiedere."},
    {Str::ErrInterrupted, L"La connessione a {0} si è interrotta e la risposta è incompleta (errore {1}). Riprova a chiedere."},
    {Str::ErrInterruptedBy, L"{0} ha interrotto la risposta: {1}"},
    {Str::ErrUnreadable, L"{0} ha restituito una risposta illeggibile. Riprova a chiedere."},
    {Str::ErrOutputLimit, L"{0} ha raggiunto il limite di lunghezza e la risposta è incompleta. Prova a chiedere una risposta più breve."},
    {Str::ErrStoppedBecause, L"{0} ha interrotto la risposta ({1}). Prova a formulare la domanda in un altro modo."},
    {Str::ErrUnconfirmed, L"{0} si è fermato prima di confermare che la risposta fosse completa. Riprova a chiedere."},
    {Str::ErrNoAnswer, L"{0} non ha dato alcuna risposta. Prova a formulare la domanda in un altro modo."},
    {Str::ErrCouldntReach, L"Impossibile contattare {0}. Controlla la connessione a Internet (errore {1})."},
    {Str::ErrStreaming, L"{0} ha restituito un errore di streaming."},
    {Str::LensSearching, L"Ricerca con Google Lens…"},
    {Str::LensUploadFailed, L"Impossibile caricare l'immagine automaticamente. È negli appunti: incollala su lens.google.com."},
};

const TextEntry kTexts_ja[] = {
    {Str::HintText, L"何かを選択して {0} に質問"},
    {Str::HintTextTyping, L"何かを選択するか、入力を始めて {0} に質問"},
    {Str::Close, L"閉じる"},
    {Str::AskInGemini, L"Gemini で質問"},
    {Str::SearchWithLens, L"Google レンズで検索"},
    {Str::TranslateTo, L"翻訳先: {0}"},
    {Str::CopyImage, L"画像をコピー"},
    {Str::CopyText, L"テキストをコピー"},
    {Str::AddSelection, L"別の選択範囲を追加"},
    {Str::WhatIsThis, L"これは何ですか？"},
    {Str::ExplainThis, L"これを説明してください"},
    {Str::SummarizeThis, L"これを要約してください"},
    {Str::AskPlaceholder, L"選択範囲について質問…"},
    {Str::AskAnythingPlaceholder, L"何でも質問…"},
    {Str::FollowUpPlaceholder, L"追加で質問…"},
    {Str::Thinking, L"考え中…"},
    {Str::Copy, L"コピー"},
    {Str::SelectAll, L"すべて選択"},
    {Str::NoApiKeyHint, L"ここで直接回答を受け取るには、Mod の設定で Gemini、ChatGPT、または Claude の API キーを追加してください。"},
    {Str::ImageCopied, L"画像をコピーしました"},
    {Str::ImageCopyFailed, L"画像をコピーできませんでした"},
    {Str::ImageCopyRetry, L"画像をコピーできませんでした。もう一度お試しください。"},
    {Str::ReadingText, L"テキストをまだ読み取っています…"},
    {Str::NoTextFound, L"選択範囲にテキストが見つかりません"},
    {Str::TextCopied, L"テキストをコピーしました"},
    {Str::TextCopyFailed, L"テキストをコピーできませんでした"},
    {Str::AnswerCopied, L"回答をコピーしました"},
    {Str::AnswerCopyFailed, L"回答をコピーできませんでした"},
    {Str::OpeningLens, L"ブラウザーで Google レンズを開いています…"},
    {Str::OpeningGeminiOne, L"Gemini を開いて画像を添付しています…"},
    {Str::OpeningGeminiMany, L"Gemini を開いてすべての画像を添付しています…"},
    {Str::OpeningGeminiText, L"Gemini を開いて質問を追加しています…"},
    {Str::ClickBoxToAttach, L"Gemini のメッセージ ボックスをクリックし、Ctrl+V キーを押して画像を添付してください。"},
    {Str::Stopped, L"停止しました。"},
    {Str::StoppedEarly, L"回答が完了する前に停止しました。"},
    {Str::RequestFailed, L"リクエストを開始できませんでした。"},
    {Str::DraftAddedOne, L"画像を追加しました。Gemini に質問を入力してください。"},
    {Str::DraftAddedMany, L"画像をすべて追加しました。Gemini に質問を入力してください。"},
    {Str::QuestionInGemini, L"質問は Gemini に入力済みです。"},
    {Str::DraftPartial, L"確認できた画像: {0}/{1}。Gemini を確認し、残りはメッセージ ボックスで Ctrl+V キーを押して追加してください。"},
    {Str::ClipboardChangedOne, L"画像を貼り付ける前にクリップボードの内容が変わりました。「画像をコピー」を使ってから、Gemini で Ctrl+V キーを押してください。"},
    {Str::ClipboardChangedMany, L"画像を貼り付ける前にクリップボードの内容が変わりました。もう一度 Gemini で質問して再試行してください。"},
    {Str::IfNotAttachedOne, L"画像が添付されていない場合は、Gemini のメッセージ ボックスをクリックして Ctrl+V キーを押してください。"},
    {Str::IfNotAttachedMany, L"画像が添付されていない場合は、Gemini のメッセージ ボックスをクリックして Ctrl+V キーを押してください。"},
    {Str::ClickBoxOne, L"Gemini のメッセージ ボックスをクリックし、Ctrl+V キーを押して画像を添付してください。質問はここに保持されています。"},
    {Str::ClickBoxMany, L"Gemini のメッセージ ボックスをクリックし、Ctrl+V キーを押してすべての画像を添付してください。質問はここに保持されています。"},
    {Str::ClickBoxText, L"Gemini のメッセージ ボックスをクリックして、質問を入力してください。質問はここに保持されています。"},
    {Str::BrowserFailedOne, L"ブラウザーを開けませんでした。画像はコピー済みです。Ctrl+V キーで Gemini に貼り付けてください。"},
    {Str::BrowserFailedMany, L"ブラウザーを開けませんでした。画像はコピー済みです。Ctrl+V キーで Gemini に貼り付けてください。"},
    {Str::BrowserFailedText, L"ブラウザーを開けませんでした。"},
    {Str::PageUnreadable, L"Magic Pointer はブラウザー内のページを読み取れませんでした。上に通知が開いている場合は閉じてから、もう一度「Gemini で質問」をクリックしてください。"},
    {Str::ErrKeyInvalid, L"{0} API キーが無効です。Mod の設定で確認してください。"},
    {Str::ErrKeyForbidden, L"この API キーでは {0} を使用できません (403)。Mod の設定でキーを確認してください。"},
    {Str::ErrModelMissing, L"モデル「{0}」はこのキーでは利用できません。Mod の設定で別のモデルを選択してください。"},
    {Str::ErrNoFreeQuota, L"ご利用の Gemini プランには「{0}」の無料枠がありません。Mod の設定でモデル「高速」を選択するか、キーに課金情報を追加してください。"},
    {Str::ErrNoCredit, L"{0} アカウントのクレジットがなくなりました。クレジットまたは支払い方法を追加してから、もう一度お試しください。"},
    {Str::ErrTimeout, L"{0} から時間内に応答がありませんでした。しばらくしてからもう一度お試しください。"},
    {Str::ModelBusy, L"選択したモデルは現在利用できません。代わりに、より高速なモデルが回答しています。"},
    {Str::ErrRateLimit, L"{0} のリクエスト上限に一時的に達しました。しばらくしてからもう一度お試しください。"},
    {Str::ErrServer, L"{0} で現在問題が発生しています ({1})。しばらくしてからもう一度お試しください。"},
    {Str::ErrGeneric, L"{0} からエラーが返されました ({1})。"},
    {Str::ErrNoConnection, L"{0} の回答を受信できませんでした。インターネット接続を確認してください (エラー {1})。もう一度質問してみてください。"},
    {Str::ErrInterrupted, L"{0} との接続が中断されました。この回答は不完全です (エラー {1})。もう一度質問してみてください。"},
    {Str::ErrInterruptedBy, L"{0} がこの回答を中断しました: {1}"},
    {Str::ErrUnreadable, L"{0} から読み取れない応答が返されました。もう一度質問してみてください。"},
    {Str::ErrOutputLimit, L"{0} が出力の上限に達しました。この回答は不完全です。もっと短い回答を求めてみてください。"},
    {Str::ErrStoppedBecause, L"{0} がこの回答を停止しました ({1})。別の聞き方をお試しください。"},
    {Str::ErrUnconfirmed, L"{0} は回答が完了したことを確認する前に停止しました。もう一度質問してみてください。"},
    {Str::ErrNoAnswer, L"{0} から回答が返されませんでした。別の聞き方をお試しください。"},
    {Str::ErrCouldntReach, L"{0} に接続できませんでした。インターネット接続を確認してください (エラー {1})。"},
    {Str::ErrStreaming, L"{0} からストリーミング エラーが返されました。"},
    {Str::LensSearching, L"Google レンズで検索しています…"},
    {Str::LensUploadFailed, L"自動的にアップロードできませんでした。画像はクリップボードにあります。lens.google.com に貼り付けてください。"},
};

const TextEntry kTexts_ko[] = {
    {Str::HintText, L"무엇이든 선택하여 {0}에게 질문하세요"},
    {Str::HintTextTyping, L"무엇이든 선택하거나 입력을 시작하여 {0}에게 질문하세요"},
    {Str::Close, L"닫기"},
    {Str::AskInGemini, L"Gemini에 질문"},
    {Str::SearchWithLens, L"Google 렌즈로 검색"},
    {Str::TranslateTo, L"번역 대상: {0}"},
    {Str::CopyImage, L"이미지 복사"},
    {Str::CopyText, L"텍스트 복사"},
    {Str::AddSelection, L"다른 선택 영역 추가"},
    {Str::WhatIsThis, L"이게 뭐예요?"},
    {Str::ExplainThis, L"이것을 설명해 주세요"},
    {Str::SummarizeThis, L"이것을 요약해 주세요"},
    {Str::AskPlaceholder, L"선택한 내용에 대해 질문하세요…"},
    {Str::AskAnythingPlaceholder, L"무엇이든 질문하세요…"},
    {Str::FollowUpPlaceholder, L"추가 질문을 입력하세요…"},
    {Str::Thinking, L"생각하는 중…"},
    {Str::Copy, L"복사"},
    {Str::SelectAll, L"모두 선택"},
    {Str::NoApiKeyHint, L"여기에서 바로 답변을 받으려면 모드 설정에 Gemini, ChatGPT 또는 Claude API 키를 추가하세요."},
    {Str::ImageCopied, L"이미지를 복사했습니다"},
    {Str::ImageCopyFailed, L"이미지를 복사할 수 없습니다"},
    {Str::ImageCopyRetry, L"이미지를 복사할 수 없습니다. 다시 시도하세요."},
    {Str::ReadingText, L"텍스트를 아직 읽는 중입니다…"},
    {Str::NoTextFound, L"선택 영역에서 텍스트를 찾을 수 없습니다"},
    {Str::TextCopied, L"텍스트를 복사했습니다"},
    {Str::TextCopyFailed, L"텍스트를 복사할 수 없습니다"},
    {Str::AnswerCopied, L"답변을 복사했습니다"},
    {Str::AnswerCopyFailed, L"답변을 복사할 수 없습니다"},
    {Str::OpeningLens, L"브라우저에서 Google 렌즈를 여는 중…"},
    {Str::OpeningGeminiOne, L"Gemini를 열고 이미지를 첨부하는 중…"},
    {Str::OpeningGeminiMany, L"Gemini를 열고 이미지를 모두 첨부하는 중…"},
    {Str::OpeningGeminiText, L"Gemini를 열고 질문을 추가하는 중…"},
    {Str::ClickBoxToAttach, L"Gemini의 메시지 상자를 클릭한 다음 Ctrl+V를 눌러 이미지를 첨부하세요."},
    {Str::Stopped, L"중지되었습니다."},
    {Str::StoppedEarly, L"답변이 끝나기 전에 중지되었습니다."},
    {Str::RequestFailed, L"요청을 시작할 수 없습니다."},
    {Str::DraftAddedOne, L"이미지가 추가되었습니다. Gemini에 질문을 입력하세요."},
    {Str::DraftAddedMany, L"이미지가 모두 추가되었습니다. Gemini에 질문을 입력하세요."},
    {Str::QuestionInGemini, L"질문이 Gemini에 입력되어 있습니다."},
    {Str::DraftPartial, L"확인된 이미지: {0}/{1}. Gemini를 확인하고 나머지는 메시지 상자에서 Ctrl+V를 눌러 추가하세요."},
    {Str::ClipboardChangedOne, L"이미지를 붙여넣기 전에 클립보드가 변경되었습니다. '이미지 복사'를 사용한 다음 Gemini에서 Ctrl+V를 누르세요."},
    {Str::ClipboardChangedMany, L"이미지를 붙여넣기 전에 클립보드가 변경되었습니다. 다시 시도하려면 Gemini에서 다시 질문하세요."},
    {Str::IfNotAttachedOne, L"이미지가 첨부되지 않았다면 Gemini의 메시지 상자를 클릭하고 Ctrl+V를 누르세요."},
    {Str::IfNotAttachedMany, L"이미지가 첨부되지 않았다면 Gemini의 메시지 상자를 클릭하고 Ctrl+V를 누르세요."},
    {Str::ClickBoxOne, L"Gemini의 메시지 상자를 클릭하고 Ctrl+V를 눌러 이미지를 첨부하세요. 질문은 여기에 보관됩니다."},
    {Str::ClickBoxMany, L"Gemini의 메시지 상자를 클릭하고 Ctrl+V를 눌러 이미지를 모두 첨부하세요. 질문은 여기에 보관됩니다."},
    {Str::ClickBoxText, L"Gemini의 메시지 상자를 클릭하고 질문을 입력하세요. 질문은 여기에 보관됩니다."},
    {Str::BrowserFailedOne, L"브라우저를 열 수 없습니다. 이미지가 복사되었으니 Ctrl+V로 Gemini에 붙여넣으세요."},
    {Str::BrowserFailedMany, L"브라우저를 열 수 없습니다. 이미지가 복사되었으니 Ctrl+V로 Gemini에 붙여넣으세요."},
    {Str::BrowserFailedText, L"브라우저를 열 수 없습니다."},
    {Str::PageUnreadable, L"Magic Pointer가 브라우저의 페이지를 읽을 수 없습니다. 그 위에 알림이 열려 있으면 닫은 후 'Gemini에 질문'을 다시 클릭하세요."},
    {Str::ErrKeyInvalid, L"{0} API 키가 올바르지 않습니다. 모드 설정에서 확인하세요."},
    {Str::ErrKeyForbidden, L"이 API 키로는 {0}를 사용할 수 없습니다(403). 모드 설정에서 키를 확인하세요."},
    {Str::ErrModelMissing, L"'{0}' 모델은 이 키로 사용할 수 없습니다. 모드 설정에서 다른 모델을 선택하세요."},
    {Str::ErrNoFreeQuota, L"Gemini 요금제에 '{0}'의 무료 할당량이 없습니다. 모드 설정에서 '빠름' 모델을 선택하거나 키에 결제 정보를 추가하세요."},
    {Str::ErrNoCredit, L"{0} 계정의 크레딧이 모두 소진되었습니다. 크레딧이나 결제 수단을 추가한 후 다시 시도하세요."},
    {Str::ErrTimeout, L"{0}에서 제때 응답하지 않았습니다. 잠시 후 다시 시도하세요."},
    {Str::ModelBusy, L"선택한 모델을 지금은 사용할 수 없습니다. 대신 더 빠른 모델이 답변하고 있습니다."},
    {Str::ErrRateLimit, L"일시적으로 {0} 요청 한도에 도달했습니다. 잠시 후 다시 시도하세요."},
    {Str::ErrServer, L"{0}에 현재 문제가 있습니다({1}). 잠시 후 다시 시도하세요."},
    {Str::ErrGeneric, L"{0}에서 오류를 반환했습니다({1})."},
    {Str::ErrNoConnection, L"{0}의 답변을 받을 수 없습니다. 인터넷 연결을 확인하세요(오류 {1}). 다시 질문해 보세요."},
    {Str::ErrInterrupted, L"{0}와의 연결이 끊어졌습니다. 이 답변은 불완전합니다(오류 {1}). 다시 질문해 보세요."},
    {Str::ErrInterruptedBy, L"{0}가 이 답변을 중단했습니다: {1}"},
    {Str::ErrUnreadable, L"{0}가 읽을 수 없는 응답을 반환했습니다. 다시 질문해 보세요."},
    {Str::ErrOutputLimit, L"{0}가 출력 한도에 도달했습니다. 이 답변은 불완전합니다. 더 짧은 답변을 요청해 보세요."},
    {Str::ErrStoppedBecause, L"{0}가 이 답변을 중지했습니다({1}). 다른 방식으로 질문해 보세요."},
    {Str::ErrUnconfirmed, L"{0}가 답변이 완료되었음을 확인하기 전에 중지했습니다. 다시 질문해 보세요."},
    {Str::ErrNoAnswer, L"{0}가 답변을 반환하지 않았습니다. 다른 방식으로 질문해 보세요."},
    {Str::ErrCouldntReach, L"{0}에 연결할 수 없습니다. 인터넷 연결을 확인하세요(오류 {1})."},
    {Str::ErrStreaming, L"{0}가 스트리밍 오류를 반환했습니다."},
    {Str::LensSearching, L"Google 렌즈로 검색하는 중…"},
    {Str::LensUploadFailed, L"자동으로 업로드할 수 없습니다. 이미지가 클립보드에 있습니다. lens.google.com에 붙여넣으세요."},
};

const TextEntry kTexts_nb[] = {
    {Str::HintText, L"Velg noe for å spørre {0}"},
    {Str::HintTextTyping, L"Velg noe eller begynn å skrive for å spørre {0}"},
    {Str::Close, L"Lukk"},
    {Str::AskInGemini, L"Spør Gemini"},
    {Str::SearchWithLens, L"Søk med Google Lens"},
    {Str::TranslateTo, L"Oversett til: {0}"},
    {Str::CopyImage, L"Kopier bilde"},
    {Str::CopyText, L"Kopier tekst"},
    {Str::AddSelection, L"Legg til et nytt utvalg"},
    {Str::WhatIsThis, L"Hva er dette?"},
    {Str::ExplainThis, L"Forklar dette"},
    {Str::SummarizeThis, L"Oppsummer dette"},
    {Str::AskPlaceholder, L"Spør om utvalget ditt…"},
    {Str::AskAnythingPlaceholder, L"Spør om hva som helst…"},
    {Str::FollowUpPlaceholder, L"Still et oppfølgingsspørsmål…"},
    {Str::Thinking, L"Tenker…"},
    {Str::Copy, L"Kopier"},
    {Str::SelectAll, L"Merk alt"},
    {Str::NoApiKeyHint, L"Legg til en API-nøkkel for Gemini, ChatGPT eller Claude i innstillingene for modden for å få svar rett her."},
    {Str::ImageCopied, L"Bildet er kopiert"},
    {Str::ImageCopyFailed, L"Kunne ikke kopiere bildet"},
    {Str::ImageCopyRetry, L"Kunne ikke kopiere bildet. Prøv igjen."},
    {Str::ReadingText, L"Leser fortsatt teksten…"},
    {Str::NoTextFound, L"Fant ingen tekst i utvalget"},
    {Str::TextCopied, L"Teksten er kopiert"},
    {Str::TextCopyFailed, L"Kunne ikke kopiere teksten"},
    {Str::AnswerCopied, L"Svaret er kopiert"},
    {Str::AnswerCopyFailed, L"Kunne ikke kopiere svaret"},
    {Str::OpeningLens, L"Åpner Google Lens i nettleseren din…"},
    {Str::OpeningGeminiOne, L"Åpner Gemini og legger ved bildet ditt…"},
    {Str::OpeningGeminiMany, L"Åpner Gemini og legger ved bildene dine…"},
    {Str::OpeningGeminiText, L"Åpner Gemini og legger til spørsmålet ditt…"},
    {Str::ClickBoxToAttach, L"Klikk i tekstfeltet i Gemini og trykk Ctrl+V for å legge ved bildet."},
    {Str::Stopped, L"Stoppet."},
    {Str::StoppedEarly, L"Stoppet før svaret var ferdig."},
    {Str::RequestFailed, L"Kunne ikke starte forespørselen."},
    {Str::DraftAddedOne, L"Bildet ble lagt til. Skriv spørsmålet ditt i Gemini."},
    {Str::DraftAddedMany, L"Bildene ble lagt til. Skriv spørsmålet ditt i Gemini."},
    {Str::QuestionInGemini, L"Spørsmålet ditt er skrevet inn i Gemini."},
    {Str::DraftPartial, L"Bekreftede bilder: {0} av {1}. Sjekk Gemini og legg til resten med Ctrl+V i tekstfeltet."},
    {Str::ClipboardChangedOne, L"Utklippstavlen ble endret før bildet kunne limes inn: bruk Kopier bilde og trykk deretter Ctrl+V i Gemini."},
    {Str::ClipboardChangedMany, L"Utklippstavlen ble endret før bildene kunne limes inn. Spør Gemini på nytt for å prøve igjen."},
    {Str::IfNotAttachedOne, L"Hvis bildet ikke er lagt ved, klikker du i tekstfeltet i Gemini og trykker Ctrl+V."},
    {Str::IfNotAttachedMany, L"Hvis bildene ikke er lagt ved, klikker du i tekstfeltet i Gemini og trykker Ctrl+V."},
    {Str::ClickBoxOne, L"Klikk i tekstfeltet i Gemini og trykk Ctrl+V for å legge ved bildet. Spørsmålet ditt beholdes her."},
    {Str::ClickBoxMany, L"Klikk i tekstfeltet i Gemini og trykk Ctrl+V for å legge ved bildene. Spørsmålet ditt beholdes her."},
    {Str::ClickBoxText, L"Klikk i tekstfeltet i Gemini og skriv spørsmålet ditt. Spørsmålet ditt beholdes her."},
    {Str::BrowserFailedOne, L"Kunne ikke åpne nettleseren. Bildet er kopiert; lim det inn i Gemini med Ctrl+V."},
    {Str::BrowserFailedMany, L"Kunne ikke åpne nettleseren. Bildene er kopiert; lim dem inn i Gemini med Ctrl+V."},
    {Str::BrowserFailedText, L"Kunne ikke åpne nettleseren."},
    {Str::PageUnreadable, L"Magic Pointer kunne ikke lese siden i nettleseren din. Hvis et varsel er åpent over den, lukker du det og klikker på Spør Gemini igjen."},
    {Str::ErrKeyInvalid, L"{0} API-nøkkelen din er ugyldig. Sjekk den i innstillingene for modden."},
    {Str::ErrKeyForbidden, L"Denne API-nøkkelen kan ikke bruke {0} (403). Sjekk nøkkelen i innstillingene for modden."},
    {Str::ErrModelMissing, L"Modellen «{0}» er ikke tilgjengelig for nøkkelen din. Velg en annen modell i innstillingene for modden."},
    {Str::ErrNoFreeQuota, L"Gemini-abonnementet ditt har ingen gratis kvote for «{0}». Velg modellen «Rask» i innstillingene for modden, eller legg til fakturering for nøkkelen din."},
    {Str::ErrNoCredit, L"{0}-kontoen din er tom for kreditt. Legg til kreditt eller en betalingsmetode, og prøv igjen."},
    {Str::ErrTimeout, L"{0} svarte ikke i tide. Prøv igjen om litt."},
    {Str::ModelBusy, L"Modellen du valgte er ikke tilgjengelig akkurat nå. En raskere modell svarer i stedet."},
    {Str::ErrRateLimit, L"Du har nådd grensen for forespørsler hos {0} for nå. Prøv igjen om litt."},
    {Str::ErrServer, L"{0} har problemer akkurat nå ({1}). Prøv igjen om litt."},
    {Str::ErrGeneric, L"{0} returnerte en feil ({1})."},
    {Str::ErrNoConnection, L"Kunne ikke motta svaret fra {0}. Sjekk internettforbindelsen din (feil {1}) og prøv å spørre på nytt."},
    {Str::ErrInterrupted, L"Forbindelsen til {0} ble brutt, og svaret er ufullstendig (feil {1}). Prøv å spørre på nytt."},
    {Str::ErrInterruptedBy, L"{0} avbrøt dette svaret: {1}"},
    {Str::ErrUnreadable, L"{0} returnerte et uleselig svar. Prøv å spørre på nytt."},
    {Str::ErrOutputLimit, L"{0} nådde grensen for utdata. Svaret er ufullstendig. Prøv å be om et kortere svar."},
    {Str::ErrStoppedBecause, L"{0} stoppet dette svaret ({1}). Prøv å spørre på en annen måte."},
    {Str::ErrUnconfirmed, L"{0} stoppet før det ble bekreftet at svaret var komplett. Prøv å spørre på nytt."},
    {Str::ErrNoAnswer, L"{0} returnerte ikke noe svar. Prøv å spørre på en annen måte."},
    {Str::ErrCouldntReach, L"Kunne ikke nå {0}. Sjekk internettforbindelsen din (feil {1})."},
    {Str::ErrStreaming, L"{0} returnerte en strømmefeil."},
    {Str::LensSearching, L"Søker med Google Lens…"},
    {Str::LensUploadFailed, L"Kunne ikke laste opp automatisk. Bildet ligger på utklippstavlen: lim det inn på lens.google.com."},
};

const TextEntry kTexts_fa[] = {
    {Str::HintText, L"هر چیزی را انتخاب کنید تا از {0} بپرسید"},
    {Str::HintTextTyping, L"هر چیزی را انتخاب کنید یا شروع به تایپ کنید تا از {0} بپرسید"},
    {Str::Close, L"بستن"},
    {Str::AskInGemini, L"پرسیدن از Gemini"},
    {Str::SearchWithLens, L"جستجو با Google Lens"},
    {Str::TranslateTo, L"ترجمه به: {0}"},
    {Str::CopyImage, L"کپی تصویر"},
    {Str::CopyText, L"کپی متن"},
    {Str::AddSelection, L"افزودن انتخاب دیگر"},
    {Str::WhatIsThis, L"این چیست؟"},
    {Str::ExplainThis, L"این را برایم توضیح بده"},
    {Str::SummarizeThis, L"این را برایم خلاصه کن"},
    {Str::AskPlaceholder, L"درباره انتخاب خود بپرسید…"},
    {Str::AskAnythingPlaceholder, L"هر چیزی بپرسید…"},
    {Str::FollowUpPlaceholder, L"یک سؤال پیگیری بپرسید…"},
    {Str::Thinking, L"در حال فکر کردن…"},
    {Str::Copy, L"کپی"},
    {Str::SelectAll, L"انتخاب همه"},
    {Str::NoApiKeyHint, L"کلید API مربوط به Gemini، ChatGPT یا Claude را در تنظیمات مود اضافه کنید تا پاسخ\u200cها را همین\u200cجا دریافت کنید."},
    {Str::ImageCopied, L"تصویر کپی شد"},
    {Str::ImageCopyFailed, L"تصویر کپی نشد"},
    {Str::ImageCopyRetry, L"تصویر کپی نشد. دوباره تلاش کنید."},
    {Str::ReadingText, L"متن هنوز در حال خواندن است…"},
    {Str::NoTextFound, L"متنی در انتخاب پیدا نشد"},
    {Str::TextCopied, L"متن کپی شد"},
    {Str::TextCopyFailed, L"متن کپی نشد"},
    {Str::AnswerCopied, L"پاسخ کپی شد"},
    {Str::AnswerCopyFailed, L"پاسخ کپی نشد"},
    {Str::OpeningLens, L"در حال باز کردن Google Lens در مرورگر…"},
    {Str::OpeningGeminiOne, L"در حال باز کردن Gemini و پیوست کردن تصویر شما…"},
    {Str::OpeningGeminiMany, L"در حال باز کردن Gemini و پیوست کردن تصاویر شما…"},
    {Str::OpeningGeminiText, L"در حال باز کردن Gemini و افزودن سؤال شما…"},
    {Str::ClickBoxToAttach, L"روی کادر پیام Gemini کلیک کنید و سپس برای پیوست کردن تصویر Ctrl+V را فشار دهید."},
    {Str::Stopped, L"متوقف شد."},
    {Str::StoppedEarly, L"پیش از پایان پاسخ متوقف شد."},
    {Str::RequestFailed, L"درخواست شروع نشد."},
    {Str::DraftAddedOne, L"تصویر اضافه شد. سؤال خود را در Gemini بنویسید."},
    {Str::DraftAddedMany, L"تصاویر اضافه شدند. سؤال خود را در Gemini بنویسید."},
    {Str::QuestionInGemini, L"سؤال شما در Gemini است."},
    {Str::DraftPartial, L"تصاویر تأیید شده: {0} از {1}. Gemini را بررسی کنید و بقیه را با Ctrl+V در کادر پیام آن اضافه کنید."},
    {Str::ClipboardChangedOne, L"پیش از چسباندن تصویر، کلیپ\u200cبورد تغییر کرد: از «کپی تصویر» استفاده کنید و سپس در Gemini کلیدهای Ctrl+V را فشار دهید."},
    {Str::ClipboardChangedMany, L"پیش از چسباندن تصاویر، کلیپ\u200cبورد تغییر کرد. برای تلاش دوباره، در Gemini دوباره بپرسید."},
    {Str::IfNotAttachedOne, L"اگر تصویر پیوست نشده است، روی کادر پیام Gemini کلیک کنید و Ctrl+V را فشار دهید."},
    {Str::IfNotAttachedMany, L"اگر تصاویر پیوست نشده\u200cاند، روی کادر پیام Gemini کلیک کنید و Ctrl+V را فشار دهید."},
    {Str::ClickBoxOne, L"روی کادر پیام Gemini کلیک کنید و برای پیوست کردن تصویر Ctrl+V را فشار دهید. سؤال شما اینجا نگه داشته می\u200cشود."},
    {Str::ClickBoxMany, L"روی کادر پیام Gemini کلیک کنید و برای پیوست کردن تصاویر Ctrl+V را فشار دهید. سؤال شما اینجا نگه داشته می\u200cشود."},
    {Str::ClickBoxText, L"روی کادر پیام Gemini کلیک کنید و سؤال خود را تایپ کنید. سؤال شما اینجا نگه داشته می\u200cشود."},
    {Str::BrowserFailedOne, L"مرورگر باز نشد. تصویر کپی شده است؛ آن را با Ctrl+V در Gemini بچسبانید."},
    {Str::BrowserFailedMany, L"مرورگر باز نشد. تصاویر کپی شده\u200cاند؛ آن\u200cها را با Ctrl+V در Gemini بچسبانید."},
    {Str::BrowserFailedText, L"مرورگر باز نشد."},
    {Str::PageUnreadable, L"مود Magic Pointer نتوانست صفحه را در مرورگر شما بخواند. اگر اعلانی روی آن باز است، آن را ببندید و دوباره روی «پرسیدن از Gemini» کلیک کنید."},
    {Str::ErrKeyInvalid, L"کلید API {0} شما معتبر نیست. آن را در تنظیمات مود بررسی کنید."},
    {Str::ErrKeyForbidden, L"این کلید API نمی\u200cتواند از {0} استفاده کند (403). کلید را در تنظیمات مود بررسی کنید."},
    {Str::ErrModelMissing, L"مدل «{0}» برای کلید شما در دسترس نیست. مدل دیگری را در تنظیمات مود انتخاب کنید."},
    {Str::ErrNoFreeQuota, L"طرح Gemini شما سهمیه رایگان برای «{0}» ندارد. در تنظیمات مود مدل «سریع» را انتخاب کنید یا برای کلید خود صورت\u200cحساب اضافه کنید."},
    {Str::ErrNoCredit, L"اعتبار حساب {0} شما تمام شده است. اعتبار یا روش پرداخت اضافه کنید و دوباره تلاش کنید."},
    {Str::ErrTimeout, L"{0} به موقع پاسخ نداد. کمی بعد دوباره تلاش کنید."},
    {Str::ModelBusy, L"مدلی که انتخاب کرده\u200cاید اکنون در دسترس نیست. به جای آن یک مدل سریع\u200cتر پاسخ می\u200cدهد."},
    {Str::ErrRateLimit, L"فعلاً به محدودیت درخواست {0} رسیده\u200cاید. کمی بعد دوباره تلاش کنید."},
    {Str::ErrServer, L"در حال حاضر {0} مشکل دارد ({1}). کمی بعد دوباره تلاش کنید."},
    {Str::ErrGeneric, L"خطایی از {0} برگشت ({1})."},
    {Str::ErrNoConnection, L"دریافت پاسخ {0} ممکن نشد. اتصال اینترنت خود را بررسی کنید (خطای {1}). دوباره بپرسید."},
    {Str::ErrInterrupted, L"اتصال به {0} قطع شد. این پاسخ ناقص است (خطای {1}). دوباره بپرسید."},
    {Str::ErrInterruptedBy, L"این پاسخ توسط {0} قطع شد: {1}"},
    {Str::ErrUnreadable, L"پاسخی ناخوانا از {0} برگشت. دوباره بپرسید."},
    {Str::ErrOutputLimit, L"حد خروجی {0} تمام شد. این پاسخ ناقص است. پاسخ کوتاه\u200cتری بخواهید."},
    {Str::ErrStoppedBecause, L"این پاسخ توسط {0} متوقف شد ({1}). به روش دیگری بپرسید."},
    {Str::ErrUnconfirmed, L"پیش از آنکه {0} کامل بودن پاسخ را تأیید کند، متوقف شد. دوباره بپرسید."},
    {Str::ErrNoAnswer, L"پاسخی از {0} برنگشت. به روش دیگری بپرسید."},
    {Str::ErrCouldntReach, L"اتصال به {0} ممکن نشد. اتصال اینترنت خود را بررسی کنید (خطای {1})."},
    {Str::ErrStreaming, L"خطای پخش جریانی از {0} برگشت."},
    {Str::LensSearching, L"در حال جستجو با Google Lens…"},
    {Str::LensUploadFailed, L"بارگذاری خودکار انجام نشد. تصویر در کلیپ\u200cبورد است: آن را در lens.google.com بچسبانید."},
};

const TextEntry kTexts_pl[] = {
    {Str::HintText, L"Zaznacz cokolwiek, aby zapytać {0}"},
    {Str::HintTextTyping, L"Zaznacz cokolwiek lub zacznij pisać, aby zapytać {0}"},
    {Str::Close, L"Zamknij"},
    {Str::AskInGemini, L"Zapytaj Gemini"},
    {Str::SearchWithLens, L"Szukaj w Google Lens"},
    {Str::TranslateTo, L"Przetłumacz na: {0}"},
    {Str::CopyImage, L"Kopiuj obraz"},
    {Str::CopyText, L"Kopiuj tekst"},
    {Str::AddSelection, L"Dodaj kolejne zaznaczenie"},
    {Str::WhatIsThis, L"Co to jest?"},
    {Str::ExplainThis, L"Wyjaśnij mi to"},
    {Str::SummarizeThis, L"Streść mi to"},
    {Str::AskPlaceholder, L"Zadaj pytanie o zaznaczenie…"},
    {Str::AskAnythingPlaceholder, L"Zapytaj o cokolwiek…"},
    {Str::FollowUpPlaceholder, L"Zadaj pytanie uzupełniające…"},
    {Str::Thinking, L"Myślę…"},
    {Str::Copy, L"Kopiuj"},
    {Str::SelectAll, L"Zaznacz wszystko"},
    {Str::NoApiKeyHint, L"Dodaj klucz API usługi Gemini, ChatGPT lub Claude w ustawieniach moda, aby otrzymywać odpowiedzi tutaj."},
    {Str::ImageCopied, L"Skopiowano obraz"},
    {Str::ImageCopyFailed, L"Nie udało się skopiować obrazu"},
    {Str::ImageCopyRetry, L"Nie udało się skopiować obrazu. Spróbuj ponownie."},
    {Str::ReadingText, L"Tekst jest nadal odczytywany…"},
    {Str::NoTextFound, L"Nie znaleziono tekstu w zaznaczeniu"},
    {Str::TextCopied, L"Skopiowano tekst"},
    {Str::TextCopyFailed, L"Nie udało się skopiować tekstu"},
    {Str::AnswerCopied, L"Skopiowano odpowiedź"},
    {Str::AnswerCopyFailed, L"Nie udało się skopiować odpowiedzi"},
    {Str::OpeningLens, L"Otwieranie Google Lens w przeglądarce…"},
    {Str::OpeningGeminiOne, L"Otwieranie Gemini i dołączanie obrazu…"},
    {Str::OpeningGeminiMany, L"Otwieranie Gemini i dołączanie obrazów…"},
    {Str::OpeningGeminiText, L"Otwieranie Gemini i dodawanie pytania…"},
    {Str::ClickBoxToAttach, L"Kliknij pole wiadomości w Gemini i naciśnij Ctrl+V, aby dołączyć obraz."},
    {Str::Stopped, L"Zatrzymano."},
    {Str::StoppedEarly, L"Zatrzymano przed zakończeniem odpowiedzi."},
    {Str::RequestFailed, L"Nie udało się rozpocząć żądania."},
    {Str::DraftAddedOne, L"Obraz został dodany. Wpisz pytanie w Gemini."},
    {Str::DraftAddedMany, L"Obrazy zostały dodane. Wpisz pytanie w Gemini."},
    {Str::QuestionInGemini, L"Twoje pytanie jest już w Gemini."},
    {Str::DraftPartial, L"Potwierdzone obrazy: {0} z {1}. Sprawdź Gemini i dodaj pozostałe, naciskając Ctrl+V w jego polu wiadomości."},
    {Str::ClipboardChangedOne, L"Schowek zmienił się, zanim obraz udało się wkleić: użyj opcji Kopiuj obraz, a następnie naciśnij Ctrl+V w Gemini."},
    {Str::ClipboardChangedMany, L"Schowek zmienił się, zanim obrazy udało się wkleić. Zapytaj ponownie w Gemini, aby spróbować jeszcze raz."},
    {Str::IfNotAttachedOne, L"Jeśli obraz nie został dołączony, kliknij pole wiadomości w Gemini i naciśnij Ctrl+V."},
    {Str::IfNotAttachedMany, L"Jeśli obrazy nie zostały dołączone, kliknij pole wiadomości w Gemini i naciśnij Ctrl+V."},
    {Str::ClickBoxOne, L"Kliknij pole wiadomości w Gemini i naciśnij Ctrl+V, aby dołączyć obraz. Twoje pytanie pozostaje tutaj."},
    {Str::ClickBoxMany, L"Kliknij pole wiadomości w Gemini i naciśnij Ctrl+V, aby dołączyć obrazy. Twoje pytanie pozostaje tutaj."},
    {Str::ClickBoxText, L"Kliknij pole wiadomości w Gemini i wpisz swoje pytanie. Twoje pytanie pozostaje tutaj."},
    {Str::BrowserFailedOne, L"Nie udało się otworzyć przeglądarki. Obraz jest skopiowany; wklej go do Gemini za pomocą Ctrl+V."},
    {Str::BrowserFailedMany, L"Nie udało się otworzyć przeglądarki. Obrazy są skopiowane; wklej je do Gemini za pomocą Ctrl+V."},
    {Str::BrowserFailedText, L"Nie udało się otworzyć przeglądarki."},
    {Str::PageUnreadable, L"Magic Pointer nie mógł odczytać strony w przeglądarce. Jeśli nad nią jest otwarte powiadomienie, zamknij je i ponownie kliknij Zapytaj Gemini."},
    {Str::ErrKeyInvalid, L"Twój klucz API usługi {0} jest nieprawidłowy. Sprawdź go w ustawieniach moda."},
    {Str::ErrKeyForbidden, L"Ten klucz API nie może korzystać z usługi {0} (403). Sprawdź klucz w ustawieniach moda."},
    {Str::ErrModelMissing, L"Model „{0}” jest niedostępny dla Twojego klucza. Wybierz inny model w ustawieniach moda."},
    {Str::ErrNoFreeQuota, L"Twój plan Gemini nie ma bezpłatnego limitu dla modelu „{0}”. Wybierz model „Szybki” w ustawieniach moda albo dodaj płatności do swojego klucza."},
    {Str::ErrNoCredit, L"Na koncie w usłudze {0} skończyły się środki. Doładuj konto lub dodaj metodę płatności, a potem spróbuj ponownie."},
    {Str::ErrTimeout, L"Usługa {0} nie odpowiedziała na czas. Spróbuj ponownie za chwilę."},
    {Str::ModelBusy, L"Wybrany model jest teraz niedostępny. Zamiast niego odpowiada szybszy."},
    {Str::ErrRateLimit, L"Osiągnięto na razie limit żądań usługi {0}. Spróbuj ponownie za chwilę."},
    {Str::ErrServer, L"Usługa {0} ma w tej chwili problemy ({1}). Spróbuj ponownie za chwilę."},
    {Str::ErrGeneric, L"Usługa {0} zwróciła błąd ({1})."},
    {Str::ErrNoConnection, L"Nie udało się odebrać odpowiedzi usługi {0}. Sprawdź połączenie z internetem (błąd {1}) i zadaj pytanie jeszcze raz."},
    {Str::ErrInterrupted, L"Połączenie z usługą {0} zostało przerwane, a odpowiedź jest niepełna (błąd {1}). Zadaj pytanie jeszcze raz."},
    {Str::ErrInterruptedBy, L"Usługa {0} przerwała tę odpowiedź: {1}"},
    {Str::ErrUnreadable, L"Usługa {0} zwróciła nieczytelną odpowiedź. Zadaj pytanie jeszcze raz."},
    {Str::ErrOutputLimit, L"Usługa {0} osiągnęła limit wyniku. Ta odpowiedź jest niepełna. Spróbuj poprosić o krótszą odpowiedź."},
    {Str::ErrStoppedBecause, L"Usługa {0} zatrzymała tę odpowiedź ({1}). Spróbuj zapytać w inny sposób."},
    {Str::ErrUnconfirmed, L"Usługa {0} zatrzymała się, zanim potwierdziła, że odpowiedź jest kompletna. Zadaj pytanie jeszcze raz."},
    {Str::ErrNoAnswer, L"Usługa {0} nie zwróciła odpowiedzi. Spróbuj zapytać w inny sposób."},
    {Str::ErrCouldntReach, L"Nie udało się połączyć z usługą {0}. Sprawdź połączenie z internetem (błąd {1})."},
    {Str::ErrStreaming, L"Usługa {0} zwróciła błąd strumieniowania."},
    {Str::LensSearching, L"Wyszukiwanie w Google Lens…"},
    {Str::LensUploadFailed, L"Nie udało się przesłać automatycznie. Obraz jest w schowku: wklej go na lens.google.com."},
};

const TextEntry kTexts_pt_BR[] = {
    {Str::HintText, L"Selecione qualquer coisa para perguntar ao {0}"},
    {Str::HintTextTyping, L"Selecione qualquer coisa ou comece a digitar para perguntar ao {0}"},
    {Str::Close, L"Fechar"},
    {Str::AskInGemini, L"Perguntar ao Gemini"},
    {Str::SearchWithLens, L"Pesquisar com o Google Lens"},
    {Str::TranslateTo, L"Traduzir para: {0}"},
    {Str::CopyImage, L"Copiar imagem"},
    {Str::CopyText, L"Copiar texto"},
    {Str::AddSelection, L"Adicionar outra seleção"},
    {Str::WhatIsThis, L"O que é isto?"},
    {Str::ExplainThis, L"Explique isto"},
    {Str::SummarizeThis, L"Resuma isto"},
    {Str::AskPlaceholder, L"Pergunte sobre sua seleção…"},
    {Str::AskAnythingPlaceholder, L"Pergunte qualquer coisa…"},
    {Str::FollowUpPlaceholder, L"Faça outra pergunta…"},
    {Str::Thinking, L"Pensando…"},
    {Str::Copy, L"Copiar"},
    {Str::SelectAll, L"Selecionar tudo"},
    {Str::NoApiKeyHint, L"Adicione uma chave de API do Gemini, do ChatGPT ou do Claude nas configurações do mod para receber respostas aqui mesmo."},
    {Str::ImageCopied, L"Imagem copiada"},
    {Str::ImageCopyFailed, L"Não foi possível copiar a imagem"},
    {Str::ImageCopyRetry, L"Não foi possível copiar a imagem. Tente novamente."},
    {Str::ReadingText, L"Ainda lendo o texto…"},
    {Str::NoTextFound, L"Nenhum texto encontrado na seleção"},
    {Str::TextCopied, L"Texto copiado"},
    {Str::TextCopyFailed, L"Não foi possível copiar o texto"},
    {Str::AnswerCopied, L"Resposta copiada"},
    {Str::AnswerCopyFailed, L"Não foi possível copiar a resposta"},
    {Str::OpeningLens, L"Abrindo o Google Lens no seu navegador…"},
    {Str::OpeningGeminiOne, L"Abrindo o Gemini e anexando sua imagem…"},
    {Str::OpeningGeminiMany, L"Abrindo o Gemini e anexando suas imagens…"},
    {Str::OpeningGeminiText, L"Abrindo o Gemini e adicionando sua pergunta…"},
    {Str::ClickBoxToAttach, L"Clique na caixa de mensagem do Gemini e pressione Ctrl+V para anexar a imagem."},
    {Str::Stopped, L"Interrompido."},
    {Str::StoppedEarly, L"Interrompido antes de a resposta terminar."},
    {Str::RequestFailed, L"Não foi possível iniciar a solicitação."},
    {Str::DraftAddedOne, L"A imagem foi adicionada. Digite sua pergunta no Gemini."},
    {Str::DraftAddedMany, L"As imagens foram adicionadas. Digite sua pergunta no Gemini."},
    {Str::QuestionInGemini, L"Sua pergunta já está no Gemini."},
    {Str::DraftPartial, L"Imagens confirmadas: {0} de {1}. Confira o Gemini e adicione as demais com Ctrl+V na caixa de mensagem dele."},
    {Str::ClipboardChangedOne, L"A área de transferência mudou antes de a imagem poder ser colada: use Copiar imagem e depois pressione Ctrl+V no Gemini."},
    {Str::ClipboardChangedMany, L"A área de transferência mudou antes de as imagens poderem ser coladas. Pergunte novamente no Gemini para tentar de novo."},
    {Str::IfNotAttachedOne, L"Se a imagem não estiver anexada, clique na caixa de mensagem do Gemini e pressione Ctrl+V."},
    {Str::IfNotAttachedMany, L"Se as imagens não estiverem anexadas, clique na caixa de mensagem do Gemini e pressione Ctrl+V."},
    {Str::ClickBoxOne, L"Clique na caixa de mensagem do Gemini e pressione Ctrl+V para anexar a imagem. Sua pergunta é mantida aqui."},
    {Str::ClickBoxMany, L"Clique na caixa de mensagem do Gemini e pressione Ctrl+V para anexar as imagens. Sua pergunta é mantida aqui."},
    {Str::ClickBoxText, L"Clique na caixa de mensagem do Gemini e digite sua pergunta. Sua pergunta é mantida aqui."},
    {Str::BrowserFailedOne, L"Não foi possível abrir o navegador. A imagem foi copiada; cole-a no Gemini com Ctrl+V."},
    {Str::BrowserFailedMany, L"Não foi possível abrir o navegador. As imagens foram copiadas; cole-as no Gemini com Ctrl+V."},
    {Str::BrowserFailedText, L"Não foi possível abrir o navegador."},
    {Str::PageUnreadable, L"O Magic Pointer não conseguiu ler a página no seu navegador. Se houver um aviso aberto sobre ela, feche-o e clique em Perguntar ao Gemini novamente."},
    {Str::ErrKeyInvalid, L"Sua chave de API do {0} não é válida. Verifique-a nas configurações do mod."},
    {Str::ErrKeyForbidden, L"Esta chave de API não pode usar o {0} (403). Verifique a chave nas configurações do mod."},
    {Str::ErrModelMissing, L"O modelo \"{0}\" não está disponível para sua chave. Escolha outro modelo nas configurações do mod."},
    {Str::ErrNoFreeQuota, L"Seu plano do Gemini não tem cota gratuita para \"{0}\". Escolha o modelo Rápido nas configurações do mod ou adicione faturamento à sua chave."},
    {Str::ErrNoCredit, L"O crédito da sua conta do {0} acabou. Adicione crédito ou uma forma de pagamento e tente novamente."},
    {Str::ErrTimeout, L"O {0} não respondeu a tempo. Tente novamente daqui a pouco."},
    {Str::ModelBusy, L"O modelo escolhido não está disponível no momento. Um modelo mais rápido está respondendo no lugar dele."},
    {Str::ErrRateLimit, L"Você atingiu o limite de solicitações do {0} por enquanto. Tente novamente daqui a pouco."},
    {Str::ErrServer, L"O {0} está com problemas no momento ({1}). Tente novamente daqui a pouco."},
    {Str::ErrGeneric, L"O {0} retornou um erro ({1})."},
    {Str::ErrNoConnection, L"Não foi possível receber a resposta do {0}. Verifique sua conexão com a Internet (erro {1}) e tente novamente."},
    {Str::ErrInterrupted, L"A conexão com o {0} foi interrompida e a resposta ficou incompleta (erro {1}). Tente novamente."},
    {Str::ErrInterruptedBy, L"O {0} interrompeu esta resposta: {1}"},
    {Str::ErrUnreadable, L"O {0} retornou uma resposta ilegível. Tente novamente."},
    {Str::ErrOutputLimit, L"O {0} atingiu o limite de tamanho e a resposta ficou incompleta. Tente pedir uma resposta mais curta."},
    {Str::ErrStoppedBecause, L"O {0} interrompeu a resposta ({1}). Tente reformular a pergunta."},
    {Str::ErrUnconfirmed, L"O {0} parou antes de confirmar que a resposta estava completa. Tente novamente."},
    {Str::ErrNoAnswer, L"O {0} não retornou nenhuma resposta. Tente reformular a pergunta."},
    {Str::ErrCouldntReach, L"Não foi possível acessar o {0}. Verifique sua conexão com a Internet (erro {1})."},
    {Str::ErrStreaming, L"O {0} retornou um erro de streaming."},
    {Str::LensSearching, L"Pesquisando com o Google Lens…"},
    {Str::LensUploadFailed, L"Não foi possível enviar automaticamente. A imagem está na área de transferência: cole-a em lens.google.com."},
};

const TextEntry kTexts_ro[] = {
    {Str::HintText, L"Selectează orice ca să întrebi {0}"},
    {Str::HintTextTyping, L"Selectează orice sau începe să scrii ca să întrebi {0}"},
    {Str::Close, L"Închide"},
    {Str::AskInGemini, L"Întreabă Gemini"},
    {Str::SearchWithLens, L"Caută cu Google Lens"},
    {Str::TranslateTo, L"Tradu în: {0}"},
    {Str::CopyImage, L"Copiază imaginea"},
    {Str::CopyText, L"Copiază textul"},
    {Str::AddSelection, L"Adaugă o altă selecție"},
    {Str::WhatIsThis, L"Ce este asta?"},
    {Str::ExplainThis, L"Explică-mi asta"},
    {Str::SummarizeThis, L"Rezumă-mi asta"},
    {Str::AskPlaceholder, L"Întreabă despre selecția ta…"},
    {Str::AskAnythingPlaceholder, L"Întreabă orice…"},
    {Str::FollowUpPlaceholder, L"Pune o întrebare suplimentară…"},
    {Str::Thinking, L"Mă gândesc…"},
    {Str::Copy, L"Copiază"},
    {Str::SelectAll, L"Selectează tot"},
    {Str::NoApiKeyHint, L"Adaugă o cheie API pentru Gemini, ChatGPT sau Claude în setările modului pentru a primi răspunsuri chiar aici."},
    {Str::ImageCopied, L"Imagine copiată"},
    {Str::ImageCopyFailed, L"Imaginea nu a putut fi copiată"},
    {Str::ImageCopyRetry, L"Imaginea nu a putut fi copiată. Încearcă din nou."},
    {Str::ReadingText, L"Textul este încă în curs de citire…"},
    {Str::NoTextFound, L"Nu s-a găsit text în selecție"},
    {Str::TextCopied, L"Text copiat"},
    {Str::TextCopyFailed, L"Textul nu a putut fi copiat"},
    {Str::AnswerCopied, L"Răspuns copiat"},
    {Str::AnswerCopyFailed, L"Răspunsul nu a putut fi copiat"},
    {Str::OpeningLens, L"Se deschide Google Lens în browser…"},
    {Str::OpeningGeminiOne, L"Se deschide Gemini și se atașează imaginea ta…"},
    {Str::OpeningGeminiMany, L"Se deschide Gemini și se atașează imaginile tale…"},
    {Str::OpeningGeminiText, L"Se deschide Gemini și se adaugă întrebarea ta…"},
    {Str::ClickBoxToAttach, L"Dă clic în caseta de mesaj din Gemini, apoi apasă Ctrl+V pentru a atașa imaginea."},
    {Str::Stopped, L"Oprit."},
    {Str::StoppedEarly, L"Oprit înainte ca răspunsul să se termine."},
    {Str::RequestFailed, L"Cererea nu a putut fi pornită."},
    {Str::DraftAddedOne, L"Imaginea a fost adăugată. Scrie-ți întrebarea în Gemini."},
    {Str::DraftAddedMany, L"Imaginile au fost adăugate. Scrie-ți întrebarea în Gemini."},
    {Str::QuestionInGemini, L"Întrebarea ta este deja în Gemini."},
    {Str::DraftPartial, L"Imagini confirmate: {0} din {1}. Verifică Gemini și adaugă-le pe celelalte cu Ctrl+V în caseta de mesaj."},
    {Str::ClipboardChangedOne, L"Clipboardul s-a schimbat înainte ca imaginea să poată fi lipită: folosește Copiază imaginea, apoi apasă Ctrl+V în Gemini."},
    {Str::ClipboardChangedMany, L"Clipboardul s-a schimbat înainte ca imaginile să poată fi lipite. Întreabă din nou în Gemini pentru a încerca iar."},
    {Str::IfNotAttachedOne, L"Dacă imaginea nu este atașată, dă clic în caseta de mesaj din Gemini și apasă Ctrl+V."},
    {Str::IfNotAttachedMany, L"Dacă imaginile nu sunt atașate, dă clic în caseta de mesaj din Gemini și apasă Ctrl+V."},
    {Str::ClickBoxOne, L"Dă clic în caseta de mesaj din Gemini și apasă Ctrl+V pentru a atașa imaginea. Întrebarea ta rămâne aici."},
    {Str::ClickBoxMany, L"Dă clic în caseta de mesaj din Gemini și apasă Ctrl+V pentru a atașa imaginile. Întrebarea ta rămâne aici."},
    {Str::ClickBoxText, L"Dă clic în caseta de mesaj din Gemini și scrie întrebarea ta. Întrebarea ta rămâne aici."},
    {Str::BrowserFailedOne, L"Browserul nu a putut fi deschis. Imaginea este copiată; lipește-o în Gemini cu Ctrl+V."},
    {Str::BrowserFailedMany, L"Browserul nu a putut fi deschis. Imaginile sunt copiate; lipește-le în Gemini cu Ctrl+V."},
    {Str::BrowserFailedText, L"Browserul nu a putut fi deschis."},
    {Str::PageUnreadable, L"Magic Pointer nu a putut citi pagina din browser. Dacă deasupra ei este deschisă o notificare, închide-o și dă clic din nou pe Întreabă Gemini."},
    {Str::ErrKeyInvalid, L"Cheia ta API {0} nu este validă. Verifică-o în setările modului."},
    {Str::ErrKeyForbidden, L"Această cheie API nu poate folosi {0} (403). Verifică cheia în setările modului."},
    {Str::ErrModelMissing, L"Modelul „{0}” nu este disponibil pentru cheia ta. Alege alt model în setările modului."},
    {Str::ErrNoFreeQuota, L"Planul tău Gemini nu are cotă gratuită pentru „{0}”. Alege modelul „Rapid” în setările modului sau adaugă facturare la cheia ta."},
    {Str::ErrNoCredit, L"Creditul contului tău {0} s-a epuizat. Adaugă credit sau o metodă de plată și încearcă din nou."},
    {Str::ErrTimeout, L"{0} nu a răspuns la timp. Încearcă din nou peste puțin timp."},
    {Str::ModelBusy, L"Modelul ales nu este disponibil acum. Răspunde în locul lui unul mai rapid."},
    {Str::ErrRateLimit, L"Ai atins deocamdată limita de solicitări {0}. Încearcă din nou peste puțin timp."},
    {Str::ErrServer, L"{0} are probleme în acest moment ({1}). Încearcă din nou peste puțin timp."},
    {Str::ErrGeneric, L"{0} a returnat o eroare ({1})."},
    {Str::ErrNoConnection, L"Răspunsul {0} nu a putut fi primit. Verifică conexiunea la internet (eroare {1}). Încearcă să întrebi din nou."},
    {Str::ErrInterrupted, L"Conexiunea la {0} a fost întreruptă. Acest răspuns este incomplet (eroare {1}). Încearcă să întrebi din nou."},
    {Str::ErrInterruptedBy, L"{0} a întrerupt acest răspuns: {1}"},
    {Str::ErrUnreadable, L"{0} a returnat un răspuns ilizibil. Încearcă să întrebi din nou."},
    {Str::ErrOutputLimit, L"{0} a atins limita de ieșire. Acest răspuns este incomplet. Încearcă să ceri un răspuns mai scurt."},
    {Str::ErrStoppedBecause, L"{0} a oprit acest răspuns ({1}). Încearcă să întrebi altfel."},
    {Str::ErrUnconfirmed, L"{0} s-a oprit înainte de a confirma că răspunsul era complet. Încearcă să întrebi din nou."},
    {Str::ErrNoAnswer, L"{0} nu a returnat niciun răspuns. Încearcă să întrebi altfel."},
    {Str::ErrCouldntReach, L"{0} nu a putut fi contactat. Verifică conexiunea la internet (eroare {1})."},
    {Str::ErrStreaming, L"{0} a returnat o eroare de streaming."},
    {Str::LensSearching, L"Se caută cu Google Lens…"},
    {Str::LensUploadFailed, L"Încărcarea automată a eșuat. Imaginea este în clipboard: lipește-o pe lens.google.com."},
};

const TextEntry kTexts_ru[] = {
    {Str::HintText, L"Выберите что угодно, чтобы спросить {0}"},
    {Str::HintTextTyping, L"Выберите что угодно или начните вводить текст, чтобы спросить {0}"},
    {Str::Close, L"Закрыть"},
    {Str::AskInGemini, L"Спросить Gemini"},
    {Str::SearchWithLens, L"Искать с помощью Google Lens"},
    {Str::TranslateTo, L"Перевести на: {0}"},
    {Str::CopyImage, L"Копировать изображение"},
    {Str::CopyText, L"Копировать текст"},
    {Str::AddSelection, L"Добавить ещё одно выделение"},
    {Str::WhatIsThis, L"Что это?"},
    {Str::ExplainThis, L"Объясни"},
    {Str::SummarizeThis, L"Кратко перескажи"},
    {Str::AskPlaceholder, L"Задайте вопрос о выделенном…"},
    {Str::AskAnythingPlaceholder, L"Спросите что угодно…"},
    {Str::FollowUpPlaceholder, L"Задайте уточняющий вопрос…"},
    {Str::Thinking, L"Думаю…"},
    {Str::Copy, L"Копировать"},
    {Str::SelectAll, L"Выбрать всё"},
    {Str::NoApiKeyHint, L"Добавьте ключ API Gemini, ChatGPT или Claude в настройках модификации, чтобы получать ответы прямо здесь."},
    {Str::ImageCopied, L"Изображение скопировано"},
    {Str::ImageCopyFailed, L"Не удалось скопировать изображение"},
    {Str::ImageCopyRetry, L"Не удалось скопировать изображение. Повторите попытку."},
    {Str::ReadingText, L"Текст ещё распознаётся…"},
    {Str::NoTextFound, L"В выделенном фрагменте текст не найден"},
    {Str::TextCopied, L"Текст скопирован"},
    {Str::TextCopyFailed, L"Не удалось скопировать текст"},
    {Str::AnswerCopied, L"Ответ скопирован"},
    {Str::AnswerCopyFailed, L"Не удалось скопировать ответ"},
    {Str::OpeningLens, L"Открываем Google Lens в браузере…"},
    {Str::OpeningGeminiOne, L"Открываем Gemini и прикрепляем изображение…"},
    {Str::OpeningGeminiMany, L"Открываем Gemini и прикрепляем изображения…"},
    {Str::OpeningGeminiText, L"Открываем Gemini и добавляем ваш вопрос…"},
    {Str::ClickBoxToAttach, L"Щёлкните поле сообщения в Gemini и нажмите Ctrl+V, чтобы прикрепить изображение."},
    {Str::Stopped, L"Остановлено."},
    {Str::StoppedEarly, L"Остановлено до завершения ответа."},
    {Str::RequestFailed, L"Не удалось выполнить запрос."},
    {Str::DraftAddedOne, L"Изображение добавлено. Введите вопрос в Gemini."},
    {Str::DraftAddedMany, L"Изображения добавлены. Введите вопрос в Gemini."},
    {Str::QuestionInGemini, L"Ваш вопрос уже введён в Gemini."},
    {Str::DraftPartial, L"Подтверждено изображений: {0} из {1}. Проверьте Gemini и добавьте остальные с помощью Ctrl+V в его поле сообщения."},
    {Str::ClipboardChangedOne, L"Буфер обмена изменился, прежде чем изображение удалось вставить: используйте «Копировать изображение», а затем нажмите Ctrl+V в Gemini."},
    {Str::ClipboardChangedMany, L"Буфер обмена изменился, прежде чем изображения удалось вставить. Спросите в Gemini ещё раз, чтобы повторить попытку."},
    {Str::IfNotAttachedOne, L"Если изображение не прикреплено, щёлкните поле сообщения в Gemini и нажмите Ctrl+V."},
    {Str::IfNotAttachedMany, L"Если изображения не прикреплены, щёлкните поле сообщения в Gemini и нажмите Ctrl+V."},
    {Str::ClickBoxOne, L"Щёлкните поле сообщения в Gemini и нажмите Ctrl+V, чтобы прикрепить изображение. Ваш вопрос сохранён здесь."},
    {Str::ClickBoxMany, L"Щёлкните поле сообщения в Gemini и нажмите Ctrl+V, чтобы прикрепить изображения. Ваш вопрос сохранён здесь."},
    {Str::ClickBoxText, L"Щёлкните поле сообщения в Gemini и введите свой вопрос. Ваш вопрос сохранён здесь."},
    {Str::BrowserFailedOne, L"Не удалось открыть браузер. Изображение скопировано — вставьте его в Gemini с помощью Ctrl+V."},
    {Str::BrowserFailedMany, L"Не удалось открыть браузер. Изображения скопированы — вставьте их в Gemini с помощью Ctrl+V."},
    {Str::BrowserFailedText, L"Не удалось открыть браузер."},
    {Str::PageUnreadable, L"Magic Pointer не удалось прочитать страницу в вашем браузере. Если поверх неё открыто уведомление, закройте его и снова нажмите «Спросить Gemini»."},
    {Str::ErrKeyInvalid, L"Ваш ключ API {0} недействителен. Проверьте его в настройках модификации."},
    {Str::ErrKeyForbidden, L"Этот ключ API не может использовать {0} (403). Проверьте ключ в настройках модификации."},
    {Str::ErrModelMissing, L"Модель «{0}» недоступна для вашего ключа. Выберите другую модель в настройках модификации."},
    {Str::ErrNoFreeQuota, L"В вашем тарифе Gemini нет бесплатной квоты для «{0}». Выберите модель «Быстрая» в настройках модификации либо подключите оплату для своего ключа."},
    {Str::ErrNoCredit, L"На вашем аккаунте {0} закончились средства. Пополните баланс или добавьте способ оплаты и повторите попытку."},
    {Str::ErrTimeout, L"{0} не ответил вовремя. Повторите попытку чуть позже."},
    {Str::ModelBusy, L"Выбранная модель сейчас недоступна. Вместо неё отвечает более быстрая."},
    {Str::ErrRateLimit, L"Вы временно достигли лимита запросов {0}. Повторите попытку чуть позже."},
    {Str::ErrServer, L"У {0} сейчас неполадки ({1}). Повторите попытку чуть позже."},
    {Str::ErrGeneric, L"{0} вернул ошибку ({1})."},
    {Str::ErrNoConnection, L"Не удалось получить ответ {0}. Проверьте подключение к интернету (ошибка {1}). Попробуйте спросить ещё раз."},
    {Str::ErrInterrupted, L"Соединение с {0} прервано. Этот ответ неполный (ошибка {1}). Попробуйте спросить ещё раз."},
    {Str::ErrInterruptedBy, L"{0} прервал этот ответ: {1}"},
    {Str::ErrUnreadable, L"{0} вернул нечитаемый ответ. Попробуйте спросить ещё раз."},
    {Str::ErrOutputLimit, L"{0} достиг лимита вывода. Этот ответ неполный. Попробуйте попросить более короткий ответ."},
    {Str::ErrStoppedBecause, L"{0} остановил этот ответ ({1}). Попробуйте задать вопрос иначе."},
    {Str::ErrUnconfirmed, L"{0} остановился, не подтвердив, что ответ завершён. Попробуйте спросить ещё раз."},
    {Str::ErrNoAnswer, L"{0} не вернул ответ. Попробуйте задать вопрос иначе."},
    {Str::ErrCouldntReach, L"Не удалось связаться с {0}. Проверьте подключение к интернету (ошибка {1})."},
    {Str::ErrStreaming, L"{0} вернул ошибку потоковой передачи."},
    {Str::LensSearching, L"Поиск с помощью Google Lens…"},
    {Str::LensUploadFailed, L"Не удалось загрузить автоматически. Изображение находится в буфере обмена — вставьте его на lens.google.com."},
};

const TextEntry kTexts_es[] = {
    {Str::HintText, L"Selecciona algo para preguntarle a {0}"},
    {Str::HintTextTyping, L"Selecciona algo o empieza a escribir para preguntarle a {0}"},
    {Str::Close, L"Cerrar"},
    {Str::AskInGemini, L"Preguntar a Gemini"},
    {Str::SearchWithLens, L"Buscar con Google Lens"},
    {Str::TranslateTo, L"Traducir a: {0}"},
    {Str::CopyImage, L"Copiar imagen"},
    {Str::CopyText, L"Copiar texto"},
    {Str::AddSelection, L"Agregar otra selección"},
    {Str::WhatIsThis, L"¿Qué es esto?"},
    {Str::ExplainThis, L"Explícamelo"},
    {Str::SummarizeThis, L"Resúmelo"},
    {Str::AskPlaceholder, L"Pregunta sobre tu selección…"},
    {Str::AskAnythingPlaceholder, L"Pregunta lo que quieras…"},
    {Str::FollowUpPlaceholder, L"Haz otra pregunta…"},
    {Str::Thinking, L"Pensando…"},
    {Str::Copy, L"Copiar"},
    {Str::SelectAll, L"Seleccionar todo"},
    {Str::NoApiKeyHint, L"Agrega una clave de API de Gemini, ChatGPT o Claude en la configuración del mod para recibir respuestas aquí mismo."},
    {Str::ImageCopied, L"Imagen copiada"},
    {Str::ImageCopyFailed, L"No se pudo copiar la imagen"},
    {Str::ImageCopyRetry, L"No se pudo copiar la imagen. Inténtalo de nuevo."},
    {Str::ReadingText, L"Leyendo el texto…"},
    {Str::NoTextFound, L"No se encontró texto en la selección"},
    {Str::TextCopied, L"Texto copiado"},
    {Str::TextCopyFailed, L"No se pudo copiar el texto"},
    {Str::AnswerCopied, L"Respuesta copiada"},
    {Str::AnswerCopyFailed, L"No se pudo copiar la respuesta"},
    {Str::OpeningLens, L"Abriendo Google Lens en tu navegador…"},
    {Str::OpeningGeminiOne, L"Abriendo Gemini y adjuntando tu imagen…"},
    {Str::OpeningGeminiMany, L"Abriendo Gemini y adjuntando tus imágenes…"},
    {Str::OpeningGeminiText, L"Abriendo Gemini y agregando tu pregunta…"},
    {Str::ClickBoxToAttach, L"Haz clic en el cuadro de mensaje de Gemini y presiona Ctrl+V para adjuntar la imagen."},
    {Str::Stopped, L"Detenido."},
    {Str::StoppedEarly, L"Se detuvo antes de que terminara la respuesta."},
    {Str::RequestFailed, L"No se pudo iniciar la solicitud."},
    {Str::DraftAddedOne, L"Se agregó la imagen. Escribe tu pregunta en Gemini."},
    {Str::DraftAddedMany, L"Se agregaron las imágenes. Escribe tu pregunta en Gemini."},
    {Str::QuestionInGemini, L"Tu pregunta ya está en Gemini."},
    {Str::DraftPartial, L"Imágenes confirmadas: {0} de {1}. Revisa Gemini y agrega el resto con Ctrl+V en su cuadro de mensaje."},
    {Str::ClipboardChangedOne, L"El portapapeles cambió antes de poder pegar la imagen: usa Copiar imagen y luego presiona Ctrl+V en Gemini."},
    {Str::ClipboardChangedMany, L"El portapapeles cambió antes de poder pegar las imágenes. Vuelve a preguntar en Gemini para reintentarlo."},
    {Str::IfNotAttachedOne, L"Si la imagen no está adjunta, haz clic en el cuadro de mensaje de Gemini y presiona Ctrl+V."},
    {Str::IfNotAttachedMany, L"Si las imágenes no están adjuntas, haz clic en el cuadro de mensaje de Gemini y presiona Ctrl+V."},
    {Str::ClickBoxOne, L"Haz clic en el cuadro de mensaje de Gemini y presiona Ctrl+V para adjuntar la imagen. Tu pregunta se conserva aquí."},
    {Str::ClickBoxMany, L"Haz clic en el cuadro de mensaje de Gemini y presiona Ctrl+V para adjuntar las imágenes. Tu pregunta se conserva aquí."},
    {Str::ClickBoxText, L"Haz clic en el cuadro de mensaje de Gemini y escribe tu pregunta. Tu pregunta se conserva aquí."},
    {Str::BrowserFailedOne, L"No se pudo abrir el navegador. La imagen está copiada; pégala en Gemini con Ctrl+V."},
    {Str::BrowserFailedMany, L"No se pudo abrir el navegador. Las imágenes están copiadas; pégalas en Gemini con Ctrl+V."},
    {Str::BrowserFailedText, L"No se pudo abrir el navegador."},
    {Str::PageUnreadable, L"Magic Pointer no pudo leer la página en tu navegador. Si hay un aviso abierto sobre ella, ciérralo y vuelve a hacer clic en Preguntar a Gemini."},
    {Str::ErrKeyInvalid, L"Tu clave de API de {0} no es válida. Revísala en la configuración del mod."},
    {Str::ErrKeyForbidden, L"Esta clave de API no puede usar {0} (403). Revisa la clave en la configuración del mod."},
    {Str::ErrModelMissing, L"El modelo \"{0}\" no está disponible para tu clave. Elige otro modelo en la configuración del mod."},
    {Str::ErrNoFreeQuota, L"Tu plan de Gemini no tiene cuota gratuita para \"{0}\". Elige el modelo Rápido en la configuración del mod, o agrega facturación a tu clave."},
    {Str::ErrNoCredit, L"Tu cuenta de {0} se ha quedado sin crédito. Agrega crédito o un método de pago y vuelve a intentarlo."},
    {Str::ErrTimeout, L"{0} no respondió a tiempo. Inténtalo de nuevo en un momento."},
    {Str::ModelBusy, L"El modelo que elegiste no está disponible en este momento. Uno más rápido responde en su lugar."},
    {Str::ErrRateLimit, L"Has alcanzado el límite de solicitudes de {0} por ahora. Inténtalo de nuevo en un momento."},
    {Str::ErrServer, L"{0} tiene problemas en este momento ({1}). Inténtalo de nuevo en un momento."},
    {Str::ErrGeneric, L"{0} devolvió un error ({1})."},
    {Str::ErrNoConnection, L"No se pudo recibir la respuesta de {0}. Revisa tu conexión a Internet (error {1}) e inténtalo de nuevo."},
    {Str::ErrInterrupted, L"Se perdió la conexión con {0} y la respuesta quedó incompleta (error {1}). Inténtalo de nuevo."},
    {Str::ErrInterruptedBy, L"{0} interrumpió esta respuesta: {1}"},
    {Str::ErrUnreadable, L"{0} devolvió una respuesta ilegible. Inténtalo de nuevo."},
    {Str::ErrOutputLimit, L"{0} alcanzó su límite de longitud y la respuesta quedó incompleta. Prueba a pedir una más corta."},
    {Str::ErrStoppedBecause, L"{0} detuvo la respuesta ({1}). Prueba a formular la pregunta de otra forma."},
    {Str::ErrUnconfirmed, L"{0} se detuvo antes de confirmar que la respuesta estaba completa. Inténtalo de nuevo."},
    {Str::ErrNoAnswer, L"{0} no devolvió ninguna respuesta. Prueba a formular la pregunta de otra forma."},
    {Str::ErrCouldntReach, L"No se pudo conectar con {0}. Revisa tu conexión a Internet (error {1})."},
    {Str::ErrStreaming, L"{0} devolvió un error de transmisión."},
    {Str::LensSearching, L"Buscando con Google Lens…"},
    {Str::LensUploadFailed, L"No se pudo subir la imagen automáticamente. Está en tu portapapeles: pégala en lens.google.com."},
};

const TextEntry kTexts_sv[] = {
    {Str::HintText, L"Markera något för att fråga {0}"},
    {Str::HintTextTyping, L"Markera något eller börja skriva för att fråga {0}"},
    {Str::Close, L"Stäng"},
    {Str::AskInGemini, L"Fråga Gemini"},
    {Str::SearchWithLens, L"Sök med Google Lens"},
    {Str::TranslateTo, L"Översätt till: {0}"},
    {Str::CopyImage, L"Kopiera bild"},
    {Str::CopyText, L"Kopiera text"},
    {Str::AddSelection, L"Lägg till en markering till"},
    {Str::WhatIsThis, L"Vad är det här?"},
    {Str::ExplainThis, L"Förklara det här"},
    {Str::SummarizeThis, L"Sammanfatta det här"},
    {Str::AskPlaceholder, L"Fråga om din markering…"},
    {Str::AskAnythingPlaceholder, L"Fråga vad som helst…"},
    {Str::FollowUpPlaceholder, L"Ställ en följdfråga…"},
    {Str::Thinking, L"Tänker…"},
    {Str::Copy, L"Kopiera"},
    {Str::SelectAll, L"Markera allt"},
    {Str::NoApiKeyHint, L"Lägg till en API-nyckel för Gemini, ChatGPT eller Claude i moddens inställningar för att få svar direkt här."},
    {Str::ImageCopied, L"Bilden kopierades"},
    {Str::ImageCopyFailed, L"Det gick inte att kopiera bilden"},
    {Str::ImageCopyRetry, L"Det gick inte att kopiera bilden. Försök igen."},
    {Str::ReadingText, L"Läser fortfarande texten…"},
    {Str::NoTextFound, L"Ingen text hittades i markeringen"},
    {Str::TextCopied, L"Texten kopierades"},
    {Str::TextCopyFailed, L"Det gick inte att kopiera texten"},
    {Str::AnswerCopied, L"Svaret kopierades"},
    {Str::AnswerCopyFailed, L"Det gick inte att kopiera svaret"},
    {Str::OpeningLens, L"Öppnar Google Lens i webbläsaren…"},
    {Str::OpeningGeminiOne, L"Öppnar Gemini och bifogar din bild…"},
    {Str::OpeningGeminiMany, L"Öppnar Gemini och bifogar dina bilder…"},
    {Str::OpeningGeminiText, L"Öppnar Gemini och lägger till din fråga…"},
    {Str::ClickBoxToAttach, L"Klicka i Geminis textruta och tryck på Ctrl+V för att bifoga bilden."},
    {Str::Stopped, L"Stoppad."},
    {Str::StoppedEarly, L"Stoppades innan svaret var klart."},
    {Str::RequestFailed, L"Det gick inte att starta förfrågan."},
    {Str::DraftAddedOne, L"Bilden lades till. Skriv din fråga i Gemini."},
    {Str::DraftAddedMany, L"Bilderna lades till. Skriv din fråga i Gemini."},
    {Str::QuestionInGemini, L"Din fråga har skrivits in i Gemini."},
    {Str::DraftPartial, L"Bekräftade bilder: {0} av {1}. Kontrollera Gemini och lägg till resten med Ctrl+V i dess textruta."},
    {Str::ClipboardChangedOne, L"Urklippet ändrades innan bilden hann klistras in: använd Kopiera bild och tryck sedan på Ctrl+V i Gemini."},
    {Str::ClipboardChangedMany, L"Urklippet ändrades innan bilderna hann klistras in. Fråga Gemini igen för att försöka på nytt."},
    {Str::IfNotAttachedOne, L"Om bilden inte är bifogad klickar du i Geminis textruta och trycker på Ctrl+V."},
    {Str::IfNotAttachedMany, L"Om bilderna inte är bifogade klickar du i Geminis textruta och trycker på Ctrl+V."},
    {Str::ClickBoxOne, L"Klicka i Geminis textruta och tryck på Ctrl+V för att bifoga bilden. Din fråga finns kvar här."},
    {Str::ClickBoxMany, L"Klicka i Geminis textruta och tryck på Ctrl+V för att bifoga bilderna. Din fråga finns kvar här."},
    {Str::ClickBoxText, L"Klicka i Geminis textruta och skriv din fråga. Din fråga finns kvar här."},
    {Str::BrowserFailedOne, L"Det gick inte att öppna webbläsaren. Bilden är kopierad; klistra in den i Gemini med Ctrl+V."},
    {Str::BrowserFailedMany, L"Det gick inte att öppna webbläsaren. Bilderna är kopierade; klistra in dem i Gemini med Ctrl+V."},
    {Str::BrowserFailedText, L"Det gick inte att öppna webbläsaren."},
    {Str::PageUnreadable, L"Magic Pointer kunde inte läsa sidan i webbläsaren. Om en avisering är öppen ovanpå den stänger du den och klickar på Fråga Gemini igen."},
    {Str::ErrKeyInvalid, L"Din {0}-API-nyckel är ogiltig. Kontrollera den i moddens inställningar."},
    {Str::ErrKeyForbidden, L"Den här API-nyckeln kan inte använda {0} (403). Kontrollera nyckeln i moddens inställningar."},
    {Str::ErrModelMissing, L"Modellen \"{0}\" är inte tillgänglig för din nyckel. Välj en annan modell i moddens inställningar."},
    {Str::ErrNoFreeQuota, L"Din Gemini-plan har ingen gratis kvot för \"{0}\". Välj modellen Snabb i moddens inställningar, eller lägg till fakturering för din nyckel."},
    {Str::ErrNoCredit, L"Krediten på ditt {0}-konto är slut. Lägg till kredit eller en betalningsmetod och försök igen."},
    {Str::ErrTimeout, L"{0} svarade inte i tid. Försök igen om en stund."},
    {Str::ModelBusy, L"Modellen du valde är inte tillgänglig just nu. En snabbare modell svarar i stället."},
    {Str::ErrRateLimit, L"Du har nått gränsen för förfrågningar hos {0} för tillfället. Försök igen om en stund."},
    {Str::ErrServer, L"{0} har problem just nu ({1}). Försök igen om en stund."},
    {Str::ErrGeneric, L"{0} returnerade ett fel ({1})."},
    {Str::ErrNoConnection, L"Det gick inte att ta emot svaret från {0}. Kontrollera din internetanslutning (fel {1}) och fråga igen."},
    {Str::ErrInterrupted, L"Anslutningen till {0} avbröts och svaret är ofullständigt (fel {1}). Fråga igen."},
    {Str::ErrInterruptedBy, L"{0} avbröt svaret: {1}"},
    {Str::ErrUnreadable, L"{0} returnerade ett oläsligt svar. Försök fråga igen."},
    {Str::ErrOutputLimit, L"{0} nådde sin utdatagräns. Svaret är ofullständigt. Försök be om ett kortare svar."},
    {Str::ErrStoppedBecause, L"{0} avbröt svaret ({1}). Försök fråga på ett annat sätt."},
    {Str::ErrUnconfirmed, L"{0} stannade innan det bekräftades att svaret var komplett. Försök fråga igen."},
    {Str::ErrNoAnswer, L"{0} returnerade inget svar. Försök fråga på ett annat sätt."},
    {Str::ErrCouldntReach, L"Det gick inte att nå {0}. Kontrollera din internetanslutning (fel {1})."},
    {Str::ErrStreaming, L"{0} returnerade ett strömningsfel."},
    {Str::LensSearching, L"Söker med Google Lens…"},
    {Str::LensUploadFailed, L"Det gick inte att ladda upp automatiskt. Bilden finns i urklipp: klistra in den på lens.google.com."},
};

const TextEntry kTexts_ta[] = {
    {Str::HintText, L"AI-யிடம் கேட்க எதையாவது தேர்ந்தெடுக்கவும் ({0})"},
    {Str::HintTextTyping, L"AI-யிடம் கேட்க எதையாவது தேர்ந்தெடுக்கவும் அல்லது தட்டச்சு செய்யத் தொடங்கவும் ({0})"},
    {Str::Close, L"மூடு"},
    {Str::AskInGemini, L"Gemini-யிடம் கேள்"},
    {Str::SearchWithLens, L"Google Lens மூலம் தேடு"},
    {Str::TranslateTo, L"மொழிபெயர்க்கும் மொழி: {0}"},
    {Str::CopyImage, L"படத்தை நகலெடு"},
    {Str::CopyText, L"உரையை நகலெடு"},
    {Str::AddSelection, L"மற்றொரு தேர்வைச் சேர்"},
    {Str::WhatIsThis, L"இது என்ன?"},
    {Str::ExplainThis, L"இதை விளக்கிச் சொல்"},
    {Str::SummarizeThis, L"இதைச் சுருக்கிச் சொல்"},
    {Str::AskPlaceholder, L"தேர்ந்தெடுத்தது பற்றிக் கேளுங்கள்…"},
    {Str::AskAnythingPlaceholder, L"எதையும் கேளுங்கள்…"},
    {Str::FollowUpPlaceholder, L"இன்னொரு கேள்வி கேளுங்கள்…"},
    {Str::Thinking, L"யோசிக்கிறேன்…"},
    {Str::Copy, L"நகலெடு"},
    {Str::SelectAll, L"அனைத்தையும் தேர்ந்தெடு"},
    {Str::NoApiKeyHint, L"பதில்களை இங்கேயே பெற, மாற்றத்தின் அமைப்புகளில் Gemini, ChatGPT அல்லது Claude API விசையைச் சேர்க்கவும்."},
    {Str::ImageCopied, L"படம் நகலெடுக்கப்பட்டது"},
    {Str::ImageCopyFailed, L"படத்தை நகலெடுக்க முடியவில்லை"},
    {Str::ImageCopyRetry, L"படத்தை நகலெடுக்க முடியவில்லை. மீண்டும் முயலவும்."},
    {Str::ReadingText, L"உரை இன்னும் படிக்கப்படுகிறது…"},
    {Str::NoTextFound, L"தேர்வில் உரை எதுவும் இல்லை"},
    {Str::TextCopied, L"உரை நகலெடுக்கப்பட்டது"},
    {Str::TextCopyFailed, L"உரையை நகலெடுக்க முடியவில்லை"},
    {Str::AnswerCopied, L"பதில் நகலெடுக்கப்பட்டது"},
    {Str::AnswerCopyFailed, L"பதிலை நகலெடுக்க முடியவில்லை"},
    {Str::OpeningLens, L"உங்கள் உலாவியில் Google Lens திறக்கிறது…"},
    {Str::OpeningGeminiOne, L"Gemini-ஐத் திறந்து உங்கள் படத்தை இணைக்கிறது…"},
    {Str::OpeningGeminiMany, L"Gemini-ஐத் திறந்து உங்கள் படங்களை இணைக்கிறது…"},
    {Str::OpeningGeminiText, L"Gemini-ஐத் திறந்து உங்கள் கேள்வியைச் சேர்க்கிறது…"},
    {Str::ClickBoxToAttach, L"Gemini-யின் செய்திப் பெட்டியைக் கிளிக் செய்து, படத்தை இணைக்க Ctrl+V அழுத்தவும்."},
    {Str::Stopped, L"நிறுத்தப்பட்டது."},
    {Str::StoppedEarly, L"பதில் முடிவதற்கு முன்பே நிறுத்தப்பட்டது."},
    {Str::RequestFailed, L"கோரிக்கையைத் தொடங்க முடியவில்லை."},
    {Str::DraftAddedOne, L"படம் சேர்க்கப்பட்டது. இப்போது Gemini-யில் உங்கள் கேள்வியைத் தட்டச்சு செய்யுங்கள்."},
    {Str::DraftAddedMany, L"படங்கள் சேர்க்கப்பட்டன. இப்போது Gemini-யில் உங்கள் கேள்வியைத் தட்டச்சு செய்யுங்கள்."},
    {Str::QuestionInGemini, L"உங்கள் கேள்வி Gemini-யில் உள்ளிடப்பட்டுள்ளது."},
    {Str::DraftPartial, L"{1} படங்களில் {0} உறுதிசெய்யப்பட்டன. Gemini-யைப் பார்த்து, மீதமுள்ளவற்றை அதன் செய்திப் பெட்டியில் Ctrl+V மூலம் ஒட்டுங்கள்."},
    {Str::ClipboardChangedOne, L"படத்தை ஒட்டுவதற்குள் கிளிப்போர்டு மாறிவிட்டது: \"படத்தை நகலெடு\" என்பதைப் பயன்படுத்தி, Gemini-யில் Ctrl+V அழுத்துங்கள்."},
    {Str::ClipboardChangedMany, L"படங்களை ஒட்டுவதற்குள் கிளிப்போர்டு மாறிவிட்டது. மீண்டும் முயல Gemini-யில் மறுபடி கேளுங்கள்."},
    {Str::IfNotAttachedOne, L"படம் இணைக்கப்படவில்லை என்றால், Gemini-யின் செய்திப் பெட்டியைக் கிளிக் செய்து Ctrl+V அழுத்துங்கள்."},
    {Str::IfNotAttachedMany, L"படங்கள் இணைக்கப்படவில்லை என்றால், Gemini-யின் செய்திப் பெட்டியைக் கிளிக் செய்து Ctrl+V அழுத்துங்கள்."},
    {Str::ClickBoxOne, L"Gemini-யின் செய்திப் பெட்டியைக் கிளிக் செய்து, படத்தை இணைக்க Ctrl+V அழுத்துங்கள். உங்கள் கேள்வி இங்கேயே இருக்கும்."},
    {Str::ClickBoxMany, L"Gemini-யின் செய்திப் பெட்டியைக் கிளிக் செய்து, படங்களை இணைக்க Ctrl+V அழுத்துங்கள். உங்கள் கேள்வி இங்கேயே இருக்கும்."},
    {Str::ClickBoxText, L"Gemini-யின் செய்திப் பெட்டியைக் கிளிக் செய்து உங்கள் கேள்வியைத் தட்டச்சு செய்யுங்கள். உங்கள் கேள்வி இங்கேயே இருக்கும்."},
    {Str::BrowserFailedOne, L"உலாவியைத் திறக்க முடியவில்லை. படம் நகலெடுக்கப்பட்டுள்ளது; Ctrl+V மூலம் Gemini-யில் ஒட்டுங்கள்."},
    {Str::BrowserFailedMany, L"உலாவியைத் திறக்க முடியவில்லை. படங்கள் நகலெடுக்கப்பட்டுள்ளன; Ctrl+V மூலம் Gemini-யில் ஒட்டுங்கள்."},
    {Str::BrowserFailedText, L"உலாவியைத் திறக்க முடியவில்லை."},
    {Str::PageUnreadable, L"உங்கள் உலாவியில் உள்ள பக்கத்தை Magic Pointer-ஆல் படிக்க முடியவில்லை. அதன் மேல் ஏதேனும் அறிவிப்பு திறந்திருந்தால் மூடிவிட்டு, மீண்டும் \"Gemini-யிடம் கேள்\" என்பதைக் கிளிக் செய்யுங்கள்."},
    {Str::ErrKeyInvalid, L"உங்கள் {0} API விசை செல்லாது. மாற்றத்தின் அமைப்புகளில் அதைச் சரிபாருங்கள்."},
    {Str::ErrKeyForbidden, L"இந்த API விசையால் {0} சேவையைப் பயன்படுத்த முடியாது (403). மாற்றத்தின் அமைப்புகளில் விசையைச் சரிபாருங்கள்."},
    {Str::ErrModelMissing, L"\"{0}\" மாதிரி உங்கள் விசையுடன் கிடைக்கவில்லை. மாற்றத்தின் அமைப்புகளில் வேறு மாதிரியைத் தேர்ந்தெடுங்கள்."},
    {Str::ErrNoFreeQuota, L"உங்கள் Gemini திட்டத்தில் \"{0}\" மாதிரிக்கு இலவச வரம்பு இல்லை. மாற்றத்தின் அமைப்புகளில் \"வேகமானது\" மாதிரியைத் தேர்ந்தெடுங்கள், அல்லது உங்கள் விசைக்குக் கட்டணத்தைச் சேருங்கள்."},
    {Str::ErrNoCredit, L"உங்கள் {0} கணக்கில் கிரெடிட் தீர்ந்துவிட்டது. கிரெடிட் அல்லது கட்டண முறையைச் சேர்த்து மீண்டும் முயலுங்கள்."},
    {Str::ErrTimeout, L"{0} சேவை உரிய நேரத்தில் பதிலளிக்கவில்லை. சிறிது நேரம் கழித்து மீண்டும் முயலுங்கள்."},
    {Str::ModelBusy, L"நீங்கள் தேர்ந்தெடுத்த மாதிரி இப்போது கிடைக்கவில்லை. அதற்குப் பதிலாக வேகமான ஒரு மாதிரி பதிலளிக்கிறது."},
    {Str::ErrRateLimit, L"{0} சேவையின் கோரிக்கை வரம்பை இப்போதைக்கு எட்டிவிட்டீர்கள். சிறிது நேரம் கழித்து மீண்டும் முயலுங்கள்."},
    {Str::ErrServer, L"{0} சேவையில் இப்போது சிக்கல் உள்ளது ({1}). சிறிது நேரம் கழித்து மீண்டும் முயலுங்கள்."},
    {Str::ErrGeneric, L"{0} சேவை பிழையைத் தந்தது ({1})."},
    {Str::ErrNoConnection, L"{0} சேவையின் பதிலைப் பெற முடியவில்லை. இணைய இணைப்பைச் சரிபார்த்து (பிழை {1}) மீண்டும் கேளுங்கள்."},
    {Str::ErrInterrupted, L"{0} சேவையுடனான இணைப்பு துண்டிக்கப்பட்டதால் பதில் முழுமையாக இல்லை (பிழை {1}). மீண்டும் கேளுங்கள்."},
    {Str::ErrInterruptedBy, L"{0} சேவை இந்தப் பதிலை இடையில் நிறுத்தியது: {1}"},
    {Str::ErrUnreadable, L"{0} சேவை படிக்க முடியாத பதிலைத் தந்தது. மீண்டும் கேளுங்கள்."},
    {Str::ErrOutputLimit, L"{0} சேவையின் வெளியீட்டு வரம்பு முடிந்ததால் பதில் முழுமையாக இல்லை. சுருக்கமான பதிலைக் கேட்டுப் பாருங்கள்."},
    {Str::ErrStoppedBecause, L"{0} சேவை இந்தப் பதிலை நிறுத்தியது ({1}). வேறு விதமாகக் கேட்டுப் பாருங்கள்."},
    {Str::ErrUnconfirmed, L"பதில் முழுமையானது என்று உறுதிசெய்வதற்கு முன்பே {0} சேவை நின்றுவிட்டது. மீண்டும் கேளுங்கள்."},
    {Str::ErrNoAnswer, L"{0} சேவை எந்தப் பதிலும் தரவில்லை. வேறு விதமாகக் கேட்டுப் பாருங்கள்."},
    {Str::ErrCouldntReach, L"{0} சேவையைத் தொடர்புகொள்ள முடியவில்லை. இணைய இணைப்பைச் சரிபாருங்கள் (பிழை {1})."},
    {Str::ErrStreaming, L"{0} சேவையில் ஸ்ட்ரீமிங் பிழை ஏற்பட்டது."},
    {Str::LensSearching, L"Google Lens மூலம் தேடப்படுகிறது…"},
    {Str::LensUploadFailed, L"தானாகப் பதிவேற்ற முடியவில்லை. படம் கிளிப்போர்டில் உள்ளது: lens.google.com இல் ஒட்டுங்கள்."},
};

const TextEntry kTexts_th[] = {
    {Str::HintText, L"เลือกอะไรก็ได้เพื่อถาม {0}"},
    {Str::HintTextTyping, L"เลือกอะไรก็ได้หรือเริ่มพิมพ์เพื่อถาม {0}"},
    {Str::Close, L"ปิด"},
    {Str::AskInGemini, L"ถามใน Gemini"},
    {Str::SearchWithLens, L"ค้นหาด้วย Google Lens"},
    {Str::TranslateTo, L"แปลเป็น: {0}"},
    {Str::CopyImage, L"คัดลอกรูปภาพ"},
    {Str::CopyText, L"คัดลอกข้อความ"},
    {Str::AddSelection, L"เพิ่มส่วนที่เลือกอีกรายการ"},
    {Str::WhatIsThis, L"นี่คืออะไร"},
    {Str::ExplainThis, L"อธิบายสิ่งนี้ให้ฉันฟัง"},
    {Str::SummarizeThis, L"สรุปสิ่งนี้ให้ฉัน"},
    {Str::AskPlaceholder, L"ถามเกี่ยวกับส่วนที่คุณเลือก…"},
    {Str::AskAnythingPlaceholder, L"ถามอะไรก็ได้…"},
    {Str::FollowUpPlaceholder, L"ถามคำถามต่อเนื่อง…"},
    {Str::Thinking, L"กำลังคิด…"},
    {Str::Copy, L"คัดลอก"},
    {Str::SelectAll, L"เลือกทั้งหมด"},
    {Str::NoApiKeyHint, L"เพิ่มคีย์ API ของ Gemini, ChatGPT หรือ Claude ในการตั้งค่าของม็อดเพื่อรับคำตอบที่นี่โดยตรง"},
    {Str::ImageCopied, L"คัดลอกรูปภาพแล้ว"},
    {Str::ImageCopyFailed, L"ไม่สามารถคัดลอกรูปภาพได้"},
    {Str::ImageCopyRetry, L"ไม่สามารถคัดลอกรูปภาพได้ ลองอีกครั้ง"},
    {Str::ReadingText, L"ยังคงอ่านข้อความอยู่…"},
    {Str::NoTextFound, L"ไม่พบข้อความในส่วนที่เลือก"},
    {Str::TextCopied, L"คัดลอกข้อความแล้ว"},
    {Str::TextCopyFailed, L"ไม่สามารถคัดลอกข้อความได้"},
    {Str::AnswerCopied, L"คัดลอกคำตอบแล้ว"},
    {Str::AnswerCopyFailed, L"ไม่สามารถคัดลอกคำตอบได้"},
    {Str::OpeningLens, L"กำลังเปิด Google Lens ในเบราว์เซอร์ของคุณ…"},
    {Str::OpeningGeminiOne, L"กำลังเปิด Gemini และแนบรูปภาพของคุณ…"},
    {Str::OpeningGeminiMany, L"กำลังเปิด Gemini และแนบรูปภาพทั้งหมดของคุณ…"},
    {Str::OpeningGeminiText, L"กำลังเปิด Gemini และเพิ่มคำถามของคุณ…"},
    {Str::ClickBoxToAttach, L"คลิกช่องข้อความของ Gemini แล้วกด Ctrl+V เพื่อแนบรูปภาพ"},
    {Str::Stopped, L"หยุดแล้ว"},
    {Str::StoppedEarly, L"หยุดก่อนที่คำตอบจะเสร็จสมบูรณ์"},
    {Str::RequestFailed, L"ไม่สามารถเริ่มคำขอได้"},
    {Str::DraftAddedOne, L"เพิ่มรูปภาพแล้ว พิมพ์คำถามของคุณใน Gemini"},
    {Str::DraftAddedMany, L"เพิ่มรูปภาพทั้งหมดแล้ว พิมพ์คำถามของคุณใน Gemini"},
    {Str::QuestionInGemini, L"คำถามของคุณอยู่ใน Gemini แล้ว"},
    {Str::DraftPartial, L"ยืนยันรูปภาพแล้ว {0} จาก {1} รูป ตรวจสอบ Gemini แล้ววางรูปที่เหลือด้วย Ctrl+V ในช่องข้อความ"},
    {Str::ClipboardChangedOne, L"คลิปบอร์ดเปลี่ยนไปก่อนที่จะวางรูปภาพได้ ให้ใช้ \"คัดลอกรูปภาพ\" แล้วกด Ctrl+V ใน Gemini"},
    {Str::ClipboardChangedMany, L"คลิปบอร์ดเปลี่ยนไปก่อนที่จะวางรูปภาพได้ ถามใน Gemini อีกครั้งเพื่อลองใหม่"},
    {Str::IfNotAttachedOne, L"หากรูปภาพไม่ได้แนบ ให้คลิกช่องข้อความของ Gemini แล้วกด Ctrl+V"},
    {Str::IfNotAttachedMany, L"หากรูปภาพไม่ได้แนบ ให้คลิกช่องข้อความของ Gemini แล้วกด Ctrl+V"},
    {Str::ClickBoxOne, L"คลิกช่องข้อความของ Gemini แล้วกด Ctrl+V เพื่อแนบรูปภาพ คำถามของคุณจะยังอยู่ที่นี่"},
    {Str::ClickBoxMany, L"คลิกช่องข้อความของ Gemini แล้วกด Ctrl+V เพื่อแนบรูปภาพทั้งหมด คำถามของคุณจะยังอยู่ที่นี่"},
    {Str::ClickBoxText, L"คลิกช่องข้อความของ Gemini แล้วพิมพ์คำถามของคุณ คำถามของคุณจะยังอยู่ที่นี่"},
    {Str::BrowserFailedOne, L"ไม่สามารถเปิดเบราว์เซอร์ได้ คัดลอกรูปภาพแล้ว วางลงใน Gemini ด้วย Ctrl+V"},
    {Str::BrowserFailedMany, L"ไม่สามารถเปิดเบราว์เซอร์ได้ คัดลอกรูปภาพแล้ว วางลงใน Gemini ด้วย Ctrl+V"},
    {Str::BrowserFailedText, L"ไม่สามารถเปิดเบราว์เซอร์ได้"},
    {Str::PageUnreadable, L"Magic Pointer ไม่สามารถอ่านหน้าเว็บในเบราว์เซอร์ของคุณได้ หากมีการแจ้งเตือนเปิดอยู่ด้านบน ให้ปิดแล้วคลิก \"ถามใน Gemini\" อีกครั้ง"},
    {Str::ErrKeyInvalid, L"คีย์ API ของ {0} ของคุณไม่ถูกต้อง ตรวจสอบในการตั้งค่าของม็อด"},
    {Str::ErrKeyForbidden, L"คีย์ API นี้ไม่สามารถใช้ {0} ได้ (403) ตรวจสอบคีย์ในการตั้งค่าของม็อด"},
    {Str::ErrModelMissing, L"โมเดล \"{0}\" ไม่พร้อมใช้งานสำหรับคีย์ของคุณ เลือกโมเดลอื่นในการตั้งค่าของม็อด"},
    {Str::ErrNoFreeQuota, L"แพ็กเกจ Gemini ของคุณไม่มีโควตาฟรีสำหรับ \"{0}\" เลือกโมเดล \"เร็ว\" ในการตั้งค่าของม็อด หรือเพิ่มการเรียกเก็บเงินให้กับคีย์ของคุณ"},
    {Str::ErrNoCredit, L"บัญชี {0} ของคุณเครดิตหมดแล้ว เพิ่มเครดิตหรือวิธีการชำระเงิน แล้วลองอีกครั้ง"},
    {Str::ErrTimeout, L"{0} ไม่ตอบกลับภายในเวลาที่กำหนด ลองอีกครั้งในอีกสักครู่"},
    {Str::ModelBusy, L"โมเดลที่คุณเลือกไม่พร้อมใช้งานในขณะนี้ โมเดลที่เร็วกว่าจะตอบแทน"},
    {Str::ErrRateLimit, L"คุณถึงขีดจำกัดคำขอของ {0} ชั่วคราว ลองอีกครั้งในอีกสักครู่"},
    {Str::ErrServer, L"{0} กำลังมีปัญหาในขณะนี้ ({1}) ลองอีกครั้งในอีกสักครู่"},
    {Str::ErrGeneric, L"{0} ส่งข้อผิดพลาดกลับมา ({1})"},
    {Str::ErrNoConnection, L"ไม่สามารถรับคำตอบจาก {0} ได้ ตรวจสอบการเชื่อมต่ออินเทอร์เน็ตของคุณ (ข้อผิดพลาด {1}) ลองถามอีกครั้ง"},
    {Str::ErrInterrupted, L"การเชื่อมต่อกับ {0} ถูกขัดจังหวะ คำตอบนี้ไม่สมบูรณ์ (ข้อผิดพลาด {1}) ลองถามอีกครั้ง"},
    {Str::ErrInterruptedBy, L"{0} ขัดจังหวะคำตอบนี้: {1}"},
    {Str::ErrUnreadable, L"{0} ส่งการตอบกลับที่อ่านไม่ได้กลับมา ลองถามอีกครั้ง"},
    {Str::ErrOutputLimit, L"{0} ถึงขีดจำกัดเอาต์พุตแล้ว คำตอบนี้ไม่สมบูรณ์ ลองขอคำตอบที่สั้นลง"},
    {Str::ErrStoppedBecause, L"{0} หยุดคำตอบนี้ ({1}) ลองถามด้วยวิธีอื่น"},
    {Str::ErrUnconfirmed, L"{0} หยุดก่อนที่จะยืนยันว่าคำตอบสมบูรณ์ ลองถามอีกครั้ง"},
    {Str::ErrNoAnswer, L"{0} ไม่ได้ส่งคำตอบกลับมา ลองถามด้วยวิธีอื่น"},
    {Str::ErrCouldntReach, L"ไม่สามารถเชื่อมต่อกับ {0} ได้ ตรวจสอบการเชื่อมต่ออินเทอร์เน็ตของคุณ (ข้อผิดพลาด {1})"},
    {Str::ErrStreaming, L"{0} ส่งข้อผิดพลาดการสตรีมกลับมา"},
    {Str::LensSearching, L"กำลังค้นหาด้วย Google Lens…"},
    {Str::LensUploadFailed, L"ไม่สามารถอัปโหลดอัตโนมัติได้ รูปภาพอยู่ในคลิปบอร์ดของคุณ: วางที่ lens.google.com"},
};

const TextEntry kTexts_tr[] = {
    {Str::HintText, L"Yapay zekâya sormak için herhangi bir şey seçin ({0})"},
    {Str::HintTextTyping, L"Yapay zekâya sormak için herhangi bir şey seçin veya yazmaya başlayın ({0})"},
    {Str::Close, L"Kapat"},
    {Str::AskInGemini, L"Gemini'ye sor"},
    {Str::SearchWithLens, L"Google Lens ile ara"},
    {Str::TranslateTo, L"Şu dile çevir: {0}"},
    {Str::CopyImage, L"Görüntüyü kopyala"},
    {Str::CopyText, L"Metni kopyala"},
    {Str::AddSelection, L"Başka bir seçim ekle"},
    {Str::WhatIsThis, L"Bu nedir?"},
    {Str::ExplainThis, L"Bunu bana açıkla"},
    {Str::SummarizeThis, L"Bunu benim için özetle"},
    {Str::AskPlaceholder, L"Seçiminiz hakkında soru sorun…"},
    {Str::AskAnythingPlaceholder, L"Her şeyi sorun…"},
    {Str::FollowUpPlaceholder, L"Devam sorusu sorun…"},
    {Str::Thinking, L"Düşünüyorum…"},
    {Str::Copy, L"Kopyala"},
    {Str::SelectAll, L"Tümünü seç"},
    {Str::NoApiKeyHint, L"Yanıtları doğrudan burada almak için modun ayarlarına bir Gemini, ChatGPT veya Claude API anahtarı ekleyin."},
    {Str::ImageCopied, L"Görüntü kopyalandı"},
    {Str::ImageCopyFailed, L"Görüntü kopyalanamadı"},
    {Str::ImageCopyRetry, L"Görüntü kopyalanamadı. Tekrar deneyin."},
    {Str::ReadingText, L"Metin hâlâ okunuyor…"},
    {Str::NoTextFound, L"Seçimde metin bulunamadı"},
    {Str::TextCopied, L"Metin kopyalandı"},
    {Str::TextCopyFailed, L"Metin kopyalanamadı"},
    {Str::AnswerCopied, L"Yanıt kopyalandı"},
    {Str::AnswerCopyFailed, L"Yanıt kopyalanamadı"},
    {Str::OpeningLens, L"Google Lens tarayıcınızda açılıyor…"},
    {Str::OpeningGeminiOne, L"Gemini açılıyor ve görüntünüz ekleniyor…"},
    {Str::OpeningGeminiMany, L"Gemini açılıyor ve görüntüleriniz ekleniyor…"},
    {Str::OpeningGeminiText, L"Gemini açılıyor ve sorunuz ekleniyor…"},
    {Str::ClickBoxToAttach, L"Gemini'nin ileti kutusuna tıklayın, ardından görüntüyü eklemek için Ctrl+V tuşlarına basın."},
    {Str::Stopped, L"Durduruldu."},
    {Str::StoppedEarly, L"Yanıt bitmeden durduruldu."},
    {Str::RequestFailed, L"İstek başlatılamadı."},
    {Str::DraftAddedOne, L"Görüntü eklendi. Sorunuzu Gemini'ye yazın."},
    {Str::DraftAddedMany, L"Görüntüler eklendi. Sorunuzu Gemini'ye yazın."},
    {Str::QuestionInGemini, L"Sorunuz Gemini'ye yazıldı."},
    {Str::DraftPartial, L"Doğrulanan görüntü sayısı: {0} / {1}. Gemini'yi kontrol edin ve kalanları ileti kutusunda Ctrl+V ile ekleyin."},
    {Str::ClipboardChangedOne, L"Pano, görüntü yapıştırılamadan önce değişti: Görüntüyü kopyala komutunu kullanın, ardından Gemini'de Ctrl+V tuşlarına basın."},
    {Str::ClipboardChangedMany, L"Pano, görüntüler yapıştırılamadan önce değişti. Yeniden denemek için Gemini'ye tekrar sorun."},
    {Str::IfNotAttachedOne, L"Görüntü eklenmediyse Gemini'nin ileti kutusuna tıklayın ve Ctrl+V tuşlarına basın."},
    {Str::IfNotAttachedMany, L"Görüntüler eklenmediyse Gemini'nin ileti kutusuna tıklayın ve Ctrl+V tuşlarına basın."},
    {Str::ClickBoxOne, L"Gemini'nin ileti kutusuna tıklayın ve görüntüyü eklemek için Ctrl+V tuşlarına basın. Sorunuz burada saklanır."},
    {Str::ClickBoxMany, L"Gemini'nin ileti kutusuna tıklayın ve görüntüleri eklemek için Ctrl+V tuşlarına basın. Sorunuz burada saklanır."},
    {Str::ClickBoxText, L"Gemini'nin ileti kutusuna tıklayın ve sorunuzu yazın. Sorunuz burada saklanır."},
    {Str::BrowserFailedOne, L"Tarayıcı açılamadı. Görüntü kopyalandı; Ctrl+V ile Gemini'ye yapıştırın."},
    {Str::BrowserFailedMany, L"Tarayıcı açılamadı. Görüntüler kopyalandı; Ctrl+V ile Gemini'ye yapıştırın."},
    {Str::BrowserFailedText, L"Tarayıcı açılamadı."},
    {Str::PageUnreadable, L"Magic Pointer tarayıcınızdaki sayfayı okuyamadı. Üzerinde açık bir bildirim varsa kapatın ve Gemini'ye sor düğmesine yeniden tıklayın."},
    {Str::ErrKeyInvalid, L"{0} API anahtarınız geçerli değil. Modun ayarlarından kontrol edin."},
    {Str::ErrKeyForbidden, L"Bu API anahtarı {0} hizmetini kullanamıyor (403). Anahtarı modun ayarlarından kontrol edin."},
    {Str::ErrModelMissing, L"\"{0}\" modeli anahtarınız için kullanılamıyor. Modun ayarlarından başka bir model seçin."},
    {Str::ErrNoFreeQuota, L"Gemini planınızın \"{0}\" için ücretsiz kotası yok. Modun ayarlarından \"Hızlı\" modelini seçin ya da anahtarınıza faturalandırma ekleyin."},
    {Str::ErrNoCredit, L"{0} hesabınızın kredisi tükendi. Hesabınıza kredi ya da ödeme yöntemi ekleyin ve yeniden deneyin."},
    {Str::ErrTimeout, L"{0} hizmeti zamanında yanıt vermedi. Biraz sonra tekrar deneyin."},
    {Str::ModelBusy, L"Seçtiğiniz model şu anda kullanılamıyor. Onun yerine daha hızlı bir model yanıt veriyor."},
    {Str::ErrRateLimit, L"{0} hizmetinin istek sınırına şimdilik ulaştınız. Biraz sonra tekrar deneyin."},
    {Str::ErrServer, L"{0} hizmeti şu anda sorun yaşıyor ({1}). Biraz sonra tekrar deneyin."},
    {Str::ErrGeneric, L"{0} hizmeti bir hata döndürdü ({1})."},
    {Str::ErrNoConnection, L"{0} hizmetinin yanıtı alınamadı. İnternet bağlantınızı kontrol edin (hata {1}). Yeniden sormayı deneyin."},
    {Str::ErrInterrupted, L"{0} hizmetiyle bağlantı kesildi. Bu yanıt eksik (hata {1}). Yeniden sormayı deneyin."},
    {Str::ErrInterruptedBy, L"{0} hizmeti bu yanıtı yarıda kesti: {1}"},
    {Str::ErrUnreadable, L"{0} hizmeti okunamayan bir yanıt döndürdü. Yeniden sormayı deneyin."},
    {Str::ErrOutputLimit, L"{0} hizmeti çıktı sınırına ulaştı. Bu yanıt eksik. Daha kısa bir yanıt istemeyi deneyin."},
    {Str::ErrStoppedBecause, L"{0} hizmeti bu yanıtı durdurdu ({1}). Soruyu başka bir şekilde sormayı deneyin."},
    {Str::ErrUnconfirmed, L"{0} hizmeti, yanıtın tamamlandığını doğrulamadan durdu. Yeniden sormayı deneyin."},
    {Str::ErrNoAnswer, L"{0} hizmeti yanıt döndürmedi. Soruyu başka bir şekilde sormayı deneyin."},
    {Str::ErrCouldntReach, L"{0} hizmetine ulaşılamadı. İnternet bağlantınızı kontrol edin (hata {1})."},
    {Str::ErrStreaming, L"{0} hizmeti bir akış hatası döndürdü."},
    {Str::LensSearching, L"Google Lens ile aranıyor…"},
    {Str::LensUploadFailed, L"Otomatik yükleme başarısız oldu. Görüntü panonuzda: lens.google.com adresine yapıştırın."},
};

const TextEntry kTexts_uk[] = {
    {Str::HintText, L"Виберіть будь-що, щоб запитати {0}"},
    {Str::HintTextTyping, L"Виберіть будь-що або почніть вводити текст, щоб запитати {0}"},
    {Str::Close, L"Закрити"},
    {Str::AskInGemini, L"Запитати Gemini"},
    {Str::SearchWithLens, L"Шукати за допомогою Google Lens"},
    {Str::TranslateTo, L"Перекласти на: {0}"},
    {Str::CopyImage, L"Копіювати зображення"},
    {Str::CopyText, L"Копіювати текст"},
    {Str::AddSelection, L"Додати ще одне виділення"},
    {Str::WhatIsThis, L"Що це?"},
    {Str::ExplainThis, L"Поясни"},
    {Str::SummarizeThis, L"Коротко перекажи"},
    {Str::AskPlaceholder, L"Поставте запитання про виділене…"},
    {Str::AskAnythingPlaceholder, L"Запитайте що завгодно…"},
    {Str::FollowUpPlaceholder, L"Поставте уточнювальне запитання…"},
    {Str::Thinking, L"Думаю…"},
    {Str::Copy, L"Копіювати"},
    {Str::SelectAll, L"Вибрати все"},
    {Str::NoApiKeyHint, L"Додайте ключ API Gemini, ChatGPT або Claude в налаштуваннях моду, щоб отримувати відповіді прямо тут."},
    {Str::ImageCopied, L"Зображення скопійовано"},
    {Str::ImageCopyFailed, L"Не вдалося скопіювати зображення"},
    {Str::ImageCopyRetry, L"Не вдалося скопіювати зображення. Спробуйте ще раз."},
    {Str::ReadingText, L"Текст ще розпізнається…"},
    {Str::NoTextFound, L"У виділеному фрагменті тексту не знайдено"},
    {Str::TextCopied, L"Текст скопійовано"},
    {Str::TextCopyFailed, L"Не вдалося скопіювати текст"},
    {Str::AnswerCopied, L"Відповідь скопійовано"},
    {Str::AnswerCopyFailed, L"Не вдалося скопіювати відповідь"},
    {Str::OpeningLens, L"Відкриваємо Google Lens у браузері…"},
    {Str::OpeningGeminiOne, L"Відкриваємо Gemini і прикріплюємо ваше зображення…"},
    {Str::OpeningGeminiMany, L"Відкриваємо Gemini і прикріплюємо ваші зображення…"},
    {Str::OpeningGeminiText, L"Відкриваємо Gemini і додаємо ваше запитання…"},
    {Str::ClickBoxToAttach, L"Клацніть поле повідомлення в Gemini і натисніть Ctrl+V, щоб прикріпити зображення."},
    {Str::Stopped, L"Зупинено."},
    {Str::StoppedEarly, L"Зупинено до завершення відповіді."},
    {Str::RequestFailed, L"Не вдалося виконати запит."},
    {Str::DraftAddedOne, L"Зображення додано. Введіть запитання в Gemini."},
    {Str::DraftAddedMany, L"Усі зображення додано. Введіть запитання в Gemini."},
    {Str::QuestionInGemini, L"Ваше запитання вже введено в Gemini."},
    {Str::DraftPartial, L"Підтверджено зображень: {0} із {1}. Перевірте Gemini і додайте решту за допомогою Ctrl+V у його полі повідомлення."},
    {Str::ClipboardChangedOne, L"Буфер обміну змінився, перш ніж зображення вдалося вставити: скористайтеся командою «Копіювати зображення», а потім натисніть Ctrl+V у Gemini."},
    {Str::ClipboardChangedMany, L"Буфер обміну змінився, перш ніж зображення вдалося вставити. Запитайте в Gemini ще раз, щоб повторити спробу."},
    {Str::IfNotAttachedOne, L"Якщо зображення не прикріплено, клацніть поле повідомлення в Gemini і натисніть Ctrl+V."},
    {Str::IfNotAttachedMany, L"Якщо зображення не прикріплені, клацніть поле повідомлення в Gemini і натисніть Ctrl+V."},
    {Str::ClickBoxOne, L"Клацніть поле повідомлення в Gemini і натисніть Ctrl+V, щоб прикріпити зображення. Ваше запитання збережено тут."},
    {Str::ClickBoxMany, L"Клацніть поле повідомлення в Gemini і натисніть Ctrl+V, щоб прикріпити зображення. Ваше запитання збережено тут."},
    {Str::ClickBoxText, L"Клацніть поле повідомлення в Gemini і введіть своє запитання. Ваше запитання збережено тут."},
    {Str::BrowserFailedOne, L"Не вдалося відкрити браузер. Зображення скопійовано — вставте його в Gemini за допомогою Ctrl+V."},
    {Str::BrowserFailedMany, L"Не вдалося відкрити браузер. Зображення скопійовано — вставте їх у Gemini за допомогою Ctrl+V."},
    {Str::BrowserFailedText, L"Не вдалося відкрити браузер."},
    {Str::PageUnreadable, L"Magic Pointer не вдалося прочитати сторінку у вашому браузері. Якщо поверх неї відкрито сповіщення, закрийте його й знову натисніть «Запитати Gemini»."},
    {Str::ErrKeyInvalid, L"Ваш ключ API {0} недійсний. Перевірте його в налаштуваннях моду."},
    {Str::ErrKeyForbidden, L"Цей ключ API не може використовувати {0} (403). Перевірте ключ у налаштуваннях моду."},
    {Str::ErrModelMissing, L"Модель «{0}» недоступна для вашого ключа. Виберіть іншу модель у налаштуваннях моду."},
    {Str::ErrNoFreeQuota, L"У вашому тарифі Gemini немає безкоштовної квоти для «{0}». Виберіть модель «Швидка» у налаштуваннях моду або підключіть оплату для свого ключа."},
    {Str::ErrNoCredit, L"На вашому акаунті {0} закінчилися кошти. Поповніть баланс або додайте спосіб оплати й повторіть спробу."},
    {Str::ErrTimeout, L"{0} не відповів вчасно. Спробуйте ще раз трохи пізніше."},
    {Str::ModelBusy, L"Вибрана модель зараз недоступна. Натомість відповідає швидша."},
    {Str::ErrRateLimit, L"Ви тимчасово досягли ліміту запитів {0}. Спробуйте ще раз трохи пізніше."},
    {Str::ErrServer, L"У {0} зараз збої ({1}). Спробуйте ще раз трохи пізніше."},
    {Str::ErrGeneric, L"{0} повернув помилку ({1})."},
    {Str::ErrNoConnection, L"Не вдалося отримати відповідь {0}. Перевірте підключення до інтернету (помилка {1}). Спробуйте запитати ще раз."},
    {Str::ErrInterrupted, L"З'єднання з {0} перервано. Ця відповідь неповна (помилка {1}). Спробуйте запитати ще раз."},
    {Str::ErrInterruptedBy, L"{0} перервав цю відповідь: {1}"},
    {Str::ErrUnreadable, L"{0} повернув нечитабельну відповідь. Спробуйте запитати ще раз."},
    {Str::ErrOutputLimit, L"{0} досяг ліміту виводу. Ця відповідь неповна. Спробуйте попросити коротшу відповідь."},
    {Str::ErrStoppedBecause, L"{0} зупинив цю відповідь ({1}). Спробуйте сформулювати запитання інакше."},
    {Str::ErrUnconfirmed, L"{0} зупинився, не підтвердивши, що відповідь завершена. Спробуйте запитати ще раз."},
    {Str::ErrNoAnswer, L"{0} не повернув відповіді. Спробуйте сформулювати запитання інакше."},
    {Str::ErrCouldntReach, L"Не вдалося зв'язатися з {0}. Перевірте підключення до інтернету (помилка {1})."},
    {Str::ErrStreaming, L"{0} повернув помилку потокової передачі."},
    {Str::LensSearching, L"Пошук за допомогою Google Lens…"},
    {Str::LensUploadFailed, L"Не вдалося завантажити автоматично. Зображення в буфері обміну — вставте його на lens.google.com."},
};

const TextEntry kTexts_vi[] = {
    {Str::HintText, L"Chọn bất kỳ thứ gì để hỏi {0}"},
    {Str::HintTextTyping, L"Chọn bất kỳ thứ gì hoặc bắt đầu nhập để hỏi {0}"},
    {Str::Close, L"Đóng"},
    {Str::AskInGemini, L"Hỏi Gemini"},
    {Str::SearchWithLens, L"Tìm bằng Google Lens"},
    {Str::TranslateTo, L"Dịch sang: {0}"},
    {Str::CopyImage, L"Sao chép ảnh"},
    {Str::CopyText, L"Sao chép văn bản"},
    {Str::AddSelection, L"Thêm vùng chọn khác"},
    {Str::WhatIsThis, L"Đây là gì?"},
    {Str::ExplainThis, L"Giải thích giúp tôi"},
    {Str::SummarizeThis, L"Tóm tắt giúp tôi"},
    {Str::AskPlaceholder, L"Hỏi về vùng chọn của bạn…"},
    {Str::AskAnythingPlaceholder, L"Hỏi bất cứ điều gì…"},
    {Str::FollowUpPlaceholder, L"Hỏi thêm câu tiếp theo…"},
    {Str::Thinking, L"Đang suy nghĩ…"},
    {Str::Copy, L"Sao chép"},
    {Str::SelectAll, L"Chọn tất cả"},
    {Str::NoApiKeyHint, L"Thêm khóa API Gemini, ChatGPT hoặc Claude trong phần cài đặt của mod để nhận câu trả lời ngay tại đây."},
    {Str::ImageCopied, L"Đã sao chép ảnh"},
    {Str::ImageCopyFailed, L"Không thể sao chép ảnh"},
    {Str::ImageCopyRetry, L"Không thể sao chép ảnh. Hãy thử lại."},
    {Str::ReadingText, L"Vẫn đang đọc văn bản…"},
    {Str::NoTextFound, L"Không tìm thấy văn bản trong vùng chọn"},
    {Str::TextCopied, L"Đã sao chép văn bản"},
    {Str::TextCopyFailed, L"Không thể sao chép văn bản"},
    {Str::AnswerCopied, L"Đã sao chép câu trả lời"},
    {Str::AnswerCopyFailed, L"Không thể sao chép câu trả lời"},
    {Str::OpeningLens, L"Đang mở Google Lens trong trình duyệt của bạn…"},
    {Str::OpeningGeminiOne, L"Đang mở Gemini và đính kèm ảnh của bạn…"},
    {Str::OpeningGeminiMany, L"Đang mở Gemini và đính kèm các ảnh của bạn…"},
    {Str::OpeningGeminiText, L"Đang mở Gemini và thêm câu hỏi của bạn…"},
    {Str::ClickBoxToAttach, L"Nhấp vào ô tin nhắn của Gemini, rồi nhấn Ctrl+V để đính kèm ảnh."},
    {Str::Stopped, L"Đã dừng."},
    {Str::StoppedEarly, L"Đã dừng trước khi câu trả lời hoàn tất."},
    {Str::RequestFailed, L"Không thể bắt đầu yêu cầu."},
    {Str::DraftAddedOne, L"Đã thêm ảnh. Hãy nhập câu hỏi của bạn vào Gemini."},
    {Str::DraftAddedMany, L"Đã thêm các ảnh. Hãy nhập câu hỏi của bạn vào Gemini."},
    {Str::QuestionInGemini, L"Câu hỏi của bạn đã được nhập vào Gemini."},
    {Str::DraftPartial, L"Ảnh đã xác nhận: {0}/{1}. Hãy kiểm tra Gemini và thêm phần còn lại bằng Ctrl+V trong ô tin nhắn của nó."},
    {Str::ClipboardChangedOne, L"Bảng nhớ tạm đã thay đổi trước khi dán được ảnh: hãy dùng Sao chép ảnh, rồi nhấn Ctrl+V trong Gemini."},
    {Str::ClipboardChangedMany, L"Bảng nhớ tạm đã thay đổi trước khi dán được các ảnh. Hãy hỏi lại trong Gemini để thử lại."},
    {Str::IfNotAttachedOne, L"Nếu ảnh chưa được đính kèm, hãy nhấp vào ô tin nhắn của Gemini và nhấn Ctrl+V."},
    {Str::IfNotAttachedMany, L"Nếu các ảnh chưa được đính kèm, hãy nhấp vào ô tin nhắn của Gemini và nhấn Ctrl+V."},
    {Str::ClickBoxOne, L"Nhấp vào ô tin nhắn của Gemini và nhấn Ctrl+V để đính kèm ảnh. Câu hỏi của bạn vẫn được giữ ở đây."},
    {Str::ClickBoxMany, L"Nhấp vào ô tin nhắn của Gemini và nhấn Ctrl+V để đính kèm các ảnh. Câu hỏi của bạn vẫn được giữ ở đây."},
    {Str::ClickBoxText, L"Nhấp vào ô tin nhắn của Gemini và nhập câu hỏi của bạn. Câu hỏi của bạn vẫn được giữ ở đây."},
    {Str::BrowserFailedOne, L"Không thể mở trình duyệt. Ảnh đã được sao chép; hãy dán vào Gemini bằng Ctrl+V."},
    {Str::BrowserFailedMany, L"Không thể mở trình duyệt. Các ảnh đã được sao chép; hãy dán vào Gemini bằng Ctrl+V."},
    {Str::BrowserFailedText, L"Không thể mở trình duyệt."},
    {Str::PageUnreadable, L"Magic Pointer không đọc được trang trong trình duyệt của bạn. Nếu có thông báo đang mở phía trên, hãy đóng nó rồi nhấp lại vào Hỏi Gemini."},
    {Str::ErrKeyInvalid, L"Khóa API {0} của bạn không hợp lệ. Hãy kiểm tra trong phần cài đặt của mod."},
    {Str::ErrKeyForbidden, L"Khóa API này không thể dùng {0} (403). Hãy kiểm tra khóa trong phần cài đặt của mod."},
    {Str::ErrModelMissing, L"Mô hình \"{0}\" không khả dụng cho khóa của bạn. Hãy chọn mô hình khác trong phần cài đặt của mod."},
    {Str::ErrNoFreeQuota, L"Gói Gemini của bạn không có hạn mức miễn phí cho \"{0}\". Hãy chọn mô hình \"Nhanh\" trong phần cài đặt của mod, hoặc thêm thanh toán cho khóa của bạn."},
    {Str::ErrNoCredit, L"Tài khoản {0} của bạn đã hết tín dụng. Hãy thêm tín dụng hoặc phương thức thanh toán rồi thử lại."},
    {Str::ErrTimeout, L"{0} không phản hồi kịp thời. Hãy thử lại sau giây lát."},
    {Str::ModelBusy, L"Mô hình bạn chọn hiện không khả dụng. Một mô hình nhanh hơn đang trả lời thay."},
    {Str::ErrRateLimit, L"Bạn đã đạt giới hạn yêu cầu của {0} tạm thời. Hãy thử lại sau giây lát."},
    {Str::ErrServer, L"{0} đang gặp sự cố ({1}). Hãy thử lại sau giây lát."},
    {Str::ErrGeneric, L"{0} đã trả về lỗi ({1})."},
    {Str::ErrNoConnection, L"Không thể nhận câu trả lời của {0}. Hãy kiểm tra kết nối Internet của bạn (lỗi {1}). Hãy thử hỏi lại."},
    {Str::ErrInterrupted, L"Kết nối tới {0} đã bị gián đoạn. Câu trả lời này chưa đầy đủ (lỗi {1}). Hãy thử hỏi lại."},
    {Str::ErrInterruptedBy, L"{0} đã ngắt câu trả lời này: {1}"},
    {Str::ErrUnreadable, L"{0} đã trả về phản hồi không đọc được. Hãy thử hỏi lại."},
    {Str::ErrOutputLimit, L"{0} đã đạt giới hạn đầu ra. Câu trả lời này chưa đầy đủ. Hãy thử yêu cầu câu trả lời ngắn hơn."},
    {Str::ErrStoppedBecause, L"{0} đã dừng câu trả lời này ({1}). Hãy thử hỏi theo cách khác."},
    {Str::ErrUnconfirmed, L"{0} đã dừng trước khi xác nhận câu trả lời đã hoàn tất. Hãy thử hỏi lại."},
    {Str::ErrNoAnswer, L"{0} không trả về câu trả lời. Hãy thử hỏi theo cách khác."},
    {Str::ErrCouldntReach, L"Không thể kết nối tới {0}. Hãy kiểm tra kết nối Internet của bạn (lỗi {1})."},
    {Str::ErrStreaming, L"{0} đã trả về lỗi phát trực tuyến."},
    {Str::LensSearching, L"Đang tìm kiếm bằng Google Lens…"},
    {Str::LensUploadFailed, L"Không thể tải lên tự động. Ảnh đang ở trong bảng nhớ tạm: hãy dán vào lens.google.com."},
};

const LanguageInfo kLanguageTable[] = {
    {L"ar", L"Arabic", L"العربية", true, false, kTexts_ar, ARRAYSIZE(kTexts_ar)},
    {L"bn", L"Bengali", L"বাংলা", false, false, kTexts_bn, ARRAYSIZE(kTexts_bn)},
    {L"zh-CN", L"Chinese (Simplified)", L"简体中文", false, true, kTexts_zh_CN, ARRAYSIZE(kTexts_zh_CN)},
    {L"zh-TW", L"Chinese (Traditional)", L"繁體中文", false, true, kTexts_zh_TW, ARRAYSIZE(kTexts_zh_TW)},
    {L"hr", L"Croatian", L"Hrvatski", false, false, kTexts_hr, ARRAYSIZE(kTexts_hr)},
    {L"cs", L"Czech", L"Čeština", false, false, kTexts_cs, ARRAYSIZE(kTexts_cs)},
    {L"da", L"Danish", L"Dansk", false, false, kTexts_da, ARRAYSIZE(kTexts_da)},
    {L"nl", L"Dutch", L"Nederlands", false, false, kTexts_nl, ARRAYSIZE(kTexts_nl)},
    {L"en", L"English", L"English", false, false, nullptr, 0},
    {L"fi", L"Finnish", L"Suomi", false, false, kTexts_fi, ARRAYSIZE(kTexts_fi)},
    {L"fr", L"French", L"Français", false, false, kTexts_fr, ARRAYSIZE(kTexts_fr)},
    {L"de", L"German", L"Deutsch", false, false, kTexts_de, ARRAYSIZE(kTexts_de)},
    {L"el", L"Greek", L"Ελληνικά", false, false, kTexts_el, ARRAYSIZE(kTexts_el)},
    {L"he", L"Hebrew", L"עברית", true, false, kTexts_he, ARRAYSIZE(kTexts_he)},
    {L"hi", L"Hindi", L"हिन्दी", false, false, kTexts_hi, ARRAYSIZE(kTexts_hi)},
    {L"hu", L"Hungarian", L"Magyar", false, false, kTexts_hu, ARRAYSIZE(kTexts_hu)},
    {L"id", L"Indonesian", L"Bahasa Indonesia", false, false, kTexts_id, ARRAYSIZE(kTexts_id)},
    {L"it", L"Italian", L"Italiano", false, false, kTexts_it, ARRAYSIZE(kTexts_it)},
    {L"ja", L"Japanese", L"日本語", false, true, kTexts_ja, ARRAYSIZE(kTexts_ja)},
    {L"ko", L"Korean", L"한국어", false, false, kTexts_ko, ARRAYSIZE(kTexts_ko)},
    {L"nb", L"Norwegian", L"Norsk bokmål", false, false, kTexts_nb, ARRAYSIZE(kTexts_nb)},
    {L"fa", L"Persian", L"فارسی", true, false, kTexts_fa, ARRAYSIZE(kTexts_fa)},
    {L"pl", L"Polish", L"Polski", false, false, kTexts_pl, ARRAYSIZE(kTexts_pl)},
    {L"pt-BR", L"Portuguese", L"Português", false, false, kTexts_pt_BR, ARRAYSIZE(kTexts_pt_BR)},
    {L"ro", L"Romanian", L"Română", false, false, kTexts_ro, ARRAYSIZE(kTexts_ro)},
    {L"ru", L"Russian", L"Русский", false, false, kTexts_ru, ARRAYSIZE(kTexts_ru)},
    {L"es", L"Spanish", L"Español", false, false, kTexts_es, ARRAYSIZE(kTexts_es)},
    {L"sv", L"Swedish", L"Svenska", false, false, kTexts_sv, ARRAYSIZE(kTexts_sv)},
    {L"ta", L"Tamil", L"தமிழ்", false, false, kTexts_ta, ARRAYSIZE(kTexts_ta)},
    {L"th", L"Thai", L"ไทย", false, false, kTexts_th, ARRAYSIZE(kTexts_th)},
    {L"tr", L"Turkish", L"Türkçe", false, false, kTexts_tr, ARRAYSIZE(kTexts_tr)},
    {L"uk", L"Ukrainian", L"Українська", false, false, kTexts_uk, ARRAYSIZE(kTexts_uk)},
    {L"vi", L"Vietnamese", L"Tiếng Việt", false, false, kTexts_vi, ARRAYSIZE(kTexts_vi)},
};

const LanguageInfo* GetLanguages(size_t& count) {
    count = ARRAYSIZE(kLanguageTable);
    return kLanguageTable;
}

}  // namespace magicptr

// ===========================================================================
// Settings window: the Seamless Launchpad settings GUI, the standard for every
// DavidHiFi mod. Generated by work\2026-11-12-seamless-snipper\gen.py.
// ===========================================================================
extern "C" IMAGE_DOS_HEADER __ImageBase;
namespace snpset {
// The settings window, from the tray icon. It shows the same settings as
// Windhawk's page for this mod and saves them through windhawk-cli, so the two
// stay in step. Writing a mod's settings takes admin rights, so the save runs
// the CLI elevated (silently where UAC prompts are off).

constexpr WCHAR kSettingsClass[] = L"WindhawkSeamlessSnipperSettings";
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
// Generated by work\2026-11-12-seamless-snipper\gen.py from spec.py.
static std::vector<SetField> Set_MakeFields() {
    using K = SetField;
    return {
{K::Hotkey, L"regionHotkey", L"Snip a region", L"Freezes the screen so you can drag a region or click a window. Click the box and press the keys. Leave it empty to turn it off.", L"PrintScreen", {}, 0, 100, 0, L"Snip keys"},
{K::Hotkey, L"fullscreenHotkey", L"Snip every screen", L"All your screens in one picture. Click the box and press the keys. Leave it empty to turn it off.", L"Shift+PrintScreen", {}, 0, 100, 0, L"Snip keys"},
{K::Hotkey, L"windowHotkey", L"Snip the active window", L"The window you are using, without the desktop around it. Click the box and press the keys. Leave it empty to turn it off.", L"Alt+PrintScreen", {}, 0, 100, 0, L"Snip keys"},
{K::Hotkey, L"monitorHotkey", L"Snip the active screen", L"The screen the mouse is on. Click the box and press the keys. Leave it empty to turn it off.", L"Ctrl+PrintScreen", {}, 0, 100, 0, L"Snip keys"},
{K::Check, L"stepAside", L"Let ShareX keep its keys", L"While ShareX is running, Snipper leaves these keys to it and takes them over once ShareX closes. The tray menu always works.", L"1", {}, 0, 100, 0, L"ShareX"},
{K::Check, L"copyToClipboard", L"Copy to the clipboard", L"Every snip is ready to paste.", L"1", {}, 0, 100, 1, L"After a snip"},
{K::Check, L"saveToFile", L"Save to a file", L"Every snip is also saved as a picture.", L"1", {}, 0, 100, 1, L"After a snip"},
{K::Check, L"showToast", L"Show a preview card", L"A small card with the snip. Click it to open the picture, right-click it to open its folder.", L"1", {}, 0, 100, 1, L"After a snip"},
{K::Number, L"toastSeconds", L"Card time (seconds)", L"1 to 10 (Suggested: 3).", L"3", {}, 1, 10, 1, L"After a snip"},
{K::Check, L"captureCursor", L"Include the mouse pointer", L"Draws the pointer into full screen, screen and window snips, as ShareX did.", L"1", {}, 0, 100, 1, L"After a snip"},
{K::Check, L"playSound", L"Play a sound", L"A short camera click after each snip.", L"0", {}, 0, 100, 1, L"After a snip"},
{K::Text, L"saveFolder", L"Folder", L"Where pictures are saved. The folder is made if it is missing.", L"G:\\Gallery", {}, 0, 100, 1, L"Files"},
{K::Choice, L"subfolder", L"Subfolders", L"Keeps the folder tidy.", L"day", {{L"day", L"One per day, like 12-11-26"}, {L"app", L"One per app, like Discord"}, {L"none", L"None"}}, 0, 100, 1, L"Files"},
{K::Choice, L"fileFormat", L"Picture format", L"PNG is sharp and lossless. JPG files are smaller.", L"png", {{L"png", L"PNG"}, {L"jpg", L"JPG"}}, 0, 100, 1, L"Files"},
{K::Number, L"jpgQuality", L"JPG quality", L"50 to 100 (Suggested: 92).", L"92", {}, 50, 100, 1, L"Files"},
{K::Number, L"dimOpacity", L"Dim outside (%)", L"0 to 85 (Suggested: 45). How dark the screen gets around the region.", L"45", {}, 0, 85, 2, L"Screen"},
{K::Check, L"snapWindows", L"Snap to windows", L"Hover a window and click to snip all of it, without dragging.", L"1", {}, 0, 100, 2, L"Screen"},
{K::Check, L"snapControls", L"Snap to parts of windows", L"Hovering also finds buttons, panels and lists inside windows.", L"1", {}, 0, 100, 2, L"Screen"},
{K::Check, L"showSize", L"Show the size", L"The size of the region, next to it.", L"1", {}, 0, 100, 2, L"Screen"},
{K::Check, L"crosshairLines", L"Crosshair lines", L"Thin lines across the screen through the pointer, for lining up edges.", L"0", {}, 0, 100, 2, L"Screen"},
{K::Check, L"magnifier", L"Magnifier", L"A zoomed view of the pixels under the pointer.", L"1", {}, 0, 100, 2, L"Magnifier"},
{K::Number, L"magnifierPixels", L"Pixels across", L"7 to 31 (Suggested: 15). How many screen pixels the magnifier shows.", L"15", {}, 7, 31, 2, L"Magnifier"},
{K::Number, L"magnifierZoom", L"Zoom", L"4 to 24 (Suggested: 10). The mouse wheel changes it too.", L"10", {}, 4, 24, 2, L"Magnifier"},
{K::Check, L"magnifierGrid", L"Pixel grid", L"Lines between the zoomed pixels.", L"1", {}, 0, 100, 2, L"Magnifier"},
{K::Color, L"accentFrom", L"Selection color", L"In hexadecimal. The gradient starts with this color.", L"#89B4FA", {}, 0, 100, 3, L"Selection"},
{K::Color, L"accentTo", L"Selection color 2", L"In hexadecimal. The gradient ends with this color.", L"#CBA6F7", {}, 0, 100, 3, L"Selection"},
{K::Check, L"settingsGlass", L"Blurred settings window", L"On, the settings window is see-through glass with Windows acrylic behind it. Off, it is solid. Applies when you save.", L"1", {}, 0, 100, 3, L"Settings window"},
{K::Check, L"nativeSettingsTitleBar", L"Native Windows title bar", L"Use the Windows title bar and window buttons for this settings window. Applies when you save.", L"0", {}, 0, 100, 3, L"Settings window"},
{K::Check, L"settingsTrayIcon", L"Tray icon", L"A Snipper icon in the system tray. Click it to open these settings, right-click it for a menu.", L"1", {}, 0, 100, 3, L"Settings window"},
{K::Check, L"pointerOn", L"Magic Pointer", L"Shake the mouse or press its key, then point at anything on screen and ask about it. Off, nothing summons it.", L"1", {}, 0, 100, 4, L"Summon"},
{K::Hotkey, L"pointerHotkey", L"Key", L"Summons the pointer. Press it again to put it away. Click the box and press the keys. Leave it empty to turn it off.", L"Win+Shift+G", {}, 0, 100, 4, L"Summon"},
{K::Check, L"pointerShake", L"Shake to summon", L"Wiggle the mouse, or swipe back and forth on the touchpad.", L"1", {}, 0, 100, 4, L"Summon"},
{K::Number, L"pointerSensitivity", L"Shake sensitivity", L"1 to 10 (Suggested: 5). 1 needs a big, fast shake. 10 takes a small wiggle.", L"5", {}, 1, 10, 4, L"Summon"},
{K::Check, L"pointerFullscreen", L"Ignore shakes in fullscreen", L"Games, videos and presentations that fill the screen, borderless ones too.", L"1", {}, 0, 100, 4, L"Summon"},
{K::Text, L"pointerSkipApps", L"Skip these apps", L"Shakes do nothing in them. Names like game.exe or window titles, split by semicolons.", L"", {}, 0, 100, 4, L"Summon"},
{K::Check, L"pointerTypeToAsk", L"Start typing to ask", L"With the pointer showing, just type to ask without picking anything. Off, your typing stays in the app.", L"1", {}, 0, 100, 4, L"Summon"},
{K::Number, L"pointerTimeout", L"Put away after (seconds)", L"0 to 3600 (Suggested: 15). When the mouse stays still this long. 0 keeps it until you press Esc.", L"15", {}, 0, 3600, 4, L"Summon"},
{K::Choice, L"pointerGlow", L"Glow", L"The glow around the pointer and what you pick.", L"gradient", {{L"gradient", L"Blue to mauve, your selection colors"}, {L"accent", L"Windows accent color"}, {L"rainbow", L"Google colors"}, {L"#89B4FA", L"Blue"}, {L"#CBA6F7", L"Mauve"}}, 0, 100, 4, L"Look"},
{K::Check, L"pointerGlass", L"Glass", L"The card and the hint get frosted glass. Off, they are solid.", L"1", {}, 0, 100, 4, L"Look"},
{K::Check, L"pointerRipple", L"Ripple", L"The screen gently ripples when the pointer appears.", L"1", {}, 0, 100, 4, L"Look"},
{K::Number, L"pointerSize", L"Pointer size (%)", L"50 to 300 (Suggested: 100).", L"100", {}, 50, 300, 4, L"Look"},
{K::Text, L"pointerCursorFile", L"Pointer file", L"Optional. A .cur or .ani file shown while the pointer is out.", L"", {}, 0, 100, 4, L"Look"},
{K::Number, L"pointerDim", L"Dim outside (%)", L"0 to 80 (Suggested: 50). How dark the screen gets around the area you drag.", L"50", {}, 0, 80, 4, L"Look"},
{K::Check, L"pointerHint", L"Show the hint", L"A small bubble that says what to do when the pointer appears.", L"1", {}, 0, 100, 4, L"Look"},
{K::Check, L"pointerHighlight", L"Outline what you point at", L"Buttons, pictures and text get an outline, so one click picks them.", L"1", {}, 0, 100, 4, L"Look"},
{K::Text, L"pointerApiKey", L"AI key", L"Optional. A Gemini, ChatGPT or Claude key for answers in the card. It is kept encrypted. Type none to remove it.", L"", {}, 0, 100, 4, L"AI"},
{K::Choice, L"pointerModel", L"Model", L"If the one you pick is busy, a faster one answers.", L"fast", {{L"fast", L"Fast, answers in a second or two"}, {L"balanced", L"Balanced, better answers, costs more"}, {L"smart", L"Smartest, slowest and costs the most"}}, 0, 100, 4, L"AI"},
{K::Check, L"pointerSuggestions", L"Smart suggestions", L"Up to three ideas for each pick. Needs a key, and every pick is sent to the AI as soon as you make it.", L"0", {}, 0, 100, 4, L"AI"},
{K::Choice, L"pointerTranslateTo", L"Translate to", L"For the Translate button on the card. Needs a key.", L"auto", {{L"auto", L"Your Windows language"}, {L"Arabic", L"Arabic"}, {L"Bengali", L"Bengali"}, {L"Chinese (Simplified)", L"Chinese (Simplified)"}, {L"Chinese (Traditional)", L"Chinese (Traditional)"}, {L"Croatian", L"Croatian"}, {L"Czech", L"Czech"}, {L"Danish", L"Danish"}, {L"Dutch", L"Dutch"}, {L"English", L"English"}, {L"Finnish", L"Finnish"}, {L"French", L"French"}, {L"German", L"German"}, {L"Greek", L"Greek"}, {L"Hebrew", L"Hebrew"}, {L"Hindi", L"Hindi"}, {L"Hungarian", L"Hungarian"}, {L"Indonesian", L"Indonesian"}, {L"Italian", L"Italian"}, {L"Japanese", L"Japanese"}, {L"Korean", L"Korean"}, {L"Norwegian", L"Norwegian"}, {L"Persian", L"Persian"}, {L"Polish", L"Polish"}, {L"Portuguese", L"Portuguese"}, {L"Romanian", L"Romanian"}, {L"Russian", L"Russian"}, {L"Spanish", L"Spanish"}, {L"Swedish", L"Swedish"}, {L"Tamil", L"Tamil"}, {L"Thai", L"Thai"}, {L"Turkish", L"Turkish"}, {L"Ukrainian", L"Ukrainian"}, {L"Vietnamese", L"Vietnamese"}}, 0, 100, 4, L"AI"},
{K::Check, L"pointerOcr", L"Read text in pictures", L"Windows reads the text in each pick on your PC, so you can copy it and the AI gets it too.", L"1", {}, 0, 100, 4, L"AI"},
{K::Choice, L"pointerBrowser", L"Browser", L"Opens Gemini and Google Lens. If it is missing, your default opens.", L"default", {{L"default", L"Windows default browser"}, {L"chrome", L"Google Chrome"}, {L"edge", L"Microsoft Edge"}, {L"firefox", L"Mozilla Firefox"}, {L"brave", L"Brave"}, {L"zen", L"Zen Browser"}, {L"opera", L"Opera"}, {L"vivaldi", L"Vivaldi"}, {L"librewolf", L"LibreWolf"}, {L"waterfox", L"Waterfox"}, {L"floorp", L"Floorp"}, {L"custom", L"Other (set its program below)"}}, 0, 100, 4, L"Browser"},
{K::Text, L"pointerBrowserPath", L"Other browser program", L"Only for Other: the full path of the browser program.", L"", {}, 0, 100, 4, L"Browser"}
    };
}

struct SetPageInfo {
    PCWSTR name, intro;
    WCHAR glyph;
};
static const SetPageInfo kSetPages[] = {
{L"Keys", L"The keys that take a snip. They are the same keys ShareX used.", 0xE765},
{L"Saving", L"Where snips go: the clipboard, the Gallery folder, and how files are named.", 0xE74E},
{L"Region snip", L"The frozen screen you drag a region on.", 0xEF20},
{L"Look", L"Selection colors and this window.", 0xE771},
{L"Magic Pointer", L"Point at anything on screen and ask AI about it, search it or copy its text.", 0xE7C9},
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
constexpr PCWSTR kSetKofiUrl = L"https://ko-fi.com/DavidHiFi";
constexpr PCWSTR kSetAuthorUrl = L"https://github.com/DavidHiFi";
constexpr PCWSTR kSetDittoUrl = L"https://github.com/ShareX/ShareX";
constexpr PCWSTR kSetRepoUrl = L"https://github.com/DavidHiFi/davids-windhawk-mods";
constexpr PCWSTR kSetBugUrl =
    L"https://github.com/DavidHiFi/davids-windhawk-mods/issues/new?title=%5BSeamless%20Snipper%5D%20";
constexpr PCWSTR kSetTitle = L"Seamless Snipper";
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
        if (w.fRailName && Set_TextW(w.fRailName.get(), L"Snipper") <= railW) break;
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
        add(SetItem::Link, 56, L"Based on ShareX", L"By Jaex and the ShareX contributors, GPL-3.0", kSetDittoUrl);
        add(SetItem::Link, 56, L"Magic Pointer by Rono", L"The original mod, on GitHub", L"https://github.com/rono-zeroseven/magic-pointer");
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
    p.Glyph(w.fIconL.get(), 0xF406, mark, mocha::crust);
    float x = mark.right + 20;
    p.Text(w.fBig.get(), L"Seamless Snipper", {x, row.top + 18, row.right - 16, row.top + 46}, mocha::text);
#ifdef WH_MOD_VERSION
    std::wstring ver = std::wstring(L"Version ") + WH_MOD_VERSION + L"  \u00B7  MIT license  \u00B7  A Windhawk mod";
#else
    std::wstring ver = L"MIT license  \u00B7  A Windhawk mod";
#endif
    p.Text(w.fHint.get(), ver, {x, row.top + 48, row.right - 16, row.top + 68}, mocha::subtext0);
    p.Text(w.fHint.get(), L"Snip a region, a window or the whole screen, straight to the clipboard and Gallery.",
           {x, row.top + 72, row.right - 16, row.top + 110}, mocha::subtext1);
    p.Text(w.fHint.get(), L"Made by DavidHiFi, based on ShareX by Jaex and the ShareX contributors, with Magic Pointer by Rono.",
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
    p.Text(w.fRailName.get(), L"Snipper", {d.left + 90, d.top + 32, d.left + w.railW - 10, d.top + 56}, mocha::text, textA);
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
    p.Glyph(glyph, 0xF406, r, mocha::crust);
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
            if (!w->dragRail) w->mouseX = w->mouseY = -1;
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
    HWND hwnd = CreateWindowExW(0, kSettingsClass, L"Seamless Snipper settings", style,
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

// The settings window when one of its key boxes is listening, else nullptr.
HWND RecordingKeyWindow() {
    SetWindow* w = g_setWin.get();
    return w && w->recording >= 0 ? w->hwnd : nullptr;
}
}  // namespace snpset
