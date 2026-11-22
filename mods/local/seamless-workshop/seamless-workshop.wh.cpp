// ==WindhawkMod==
// @id              seamless-workshop
// @name            Seamless Workshop
// @description     One window to install, update, turn on and off, and set up DavidHiFi's Windhawk mods
// @version         1.4.1
// @author          DavidHiFi
// @github          https://github.com/DavidHiFi
// @homepage        https://github.com/DavidHiFi/seamless-workshop
// @include         windhawk.exe
// @architecture    x86-64
// @compilerOptions -lole32 -loleaut32 -luuid -luser32 -lshell32 -lgdi32 -lwindowscodecs -ldwmapi -lshcore -ld2d1 -ldwrite -ld3d11 -ldxgi -ldxguid -ladvapi32 -lcomctl32 -luxtheme -lcomdlg32 -limm32 -lbcrypt -lwinhttp
// @license         MIT
// @donateUrl       https://ko-fi.com/DavidHiFi
// ==/WindhawkMod==

// ==WindhawkModReadme==
/*
# Seamless Workshop

One place for DavidHiFi's Windhawk mods. Install them, keep them up to date,
turn them on and off, and change their settings, all from one window that
lives in the tray.

![Seamless Workshop](https://raw.githubusercontent.com/DavidHiFi/seamless-workshop/main/media/previews/seamless-workshop.png)

Needs the latest Windhawk alpha.

## What it does

- Lists every mod you have, grouped so the ones that belong together sit
  together.
- Shows when one of DavidHiFi's mods has a new version, and installs it after
  checking that the download is exactly the one he published.
- Saves your settings as presets, so you can try something and go back.
- Use DavidHiFi's settings for one mod, or copy his whole setup in one go:
  every mod he runs, with or without his settings, on a clean slate if you
  like. Your current mods are backed up first, so you can always go back.

## What's new in 1.4.1

- DavidHiFi's settings now bring his keyboard shortcuts and his look
  settings along. Before, anything with "key" in its name was left out, so
  every shortcut was missing.
- Settings are fitted to each mod before they are saved. Old settings a mod
  no longer has are left out, and anything missing gets the mod's default, so
  newer Windhawk versions take them on the first try.

## What's new in 1.4.0

- DavidHiFi's whole setup in one go: every mod he runs, his own and the ones
  from the Windhawk library. Copy it with his settings, or install everything
  turned off with default settings.
- "Clean slate first" takes your current mods off before the setup goes in.
  A backup of them is saved first.
- One mod that fails no longer stops the rest. The window shows which step it
  is on and names any mod that did not work.

## Nothing private is shared

Presets never carry keys, tokens, passwords or account ids. When you use
DavidHiFi's settings, any setting like that keeps your own value.
*/
// ==/WindhawkModReadme==

// ==WindhawkModSettings==
/*
- settingsGlass: true
  $name: "Blurred window"
  $description: "On, the settings window is see-through glass with Windows acrylic behind it. Off, it is solid. Applies when you save."
- nativeSettingsTitleBar: false
  $name: "Native Windows title bar"
  $description: "Use the Windows title bar and window buttons for this settings window. Applies when you save."
- settingsTrayIcon: true
  $name: "Tray icon"
  $description: "Keeps Seamless Workshop in the system tray. Click the icon to open it, right-click it for a menu."
- animations: true
  $name: "Animations"
  $description: "Off, everything snaps instantly: page changes, hover fades and switches."
- feedCheck: true
  $name: "Check for updates from DavidHiFi"
  $description: "Once a day, look for new versions of his mods and of Seamless Workshop. Nothing installs without you."
- discordPresence: false
  $name: "Discord Rich Presence"
  $description: "Show on your Discord profile that you are using Seamless Workshop. Off by default."
*/
// ==/WindhawkModSettings==

#define HUB_MOD 1

// Seamless Workshop: every Windhawk mod in one window, on the Seamless Launchpad settings engine.
// Windhawk itself (engine, compiler, mod store) stays stock; this app reads and changes mods
// through windhawk-cli. Changes need admin rights, so they run in a hidden, elevated copy of
// this exe ("--apply <job file>") that only ever starts windhawk-cli.
//
// Build: build.py (engine-hub.inc comes from gen_hub.py, cut from the live Launchpad source).

#include <windows.h>
#include <windowsx.h>
#include <commctrl.h>
#include <shellapi.h>
#include <shlobj.h>
#include <shobjidl.h>
#include <knownfolders.h>
#include <shellscalingapi.h>
#include <commdlg.h>
#include <uxtheme.h>
#include <dwmapi.h>
#include <propsys.h>
#include <powrprof.h>
#include <bcrypt.h>
#include <tlhelp32.h>
#include <winhttp.h>
#include <functional>
#include <d2d1_1.h>
#include <d2d1effects.h>
#include <d3d11.h>
#include <dwrite.h>
#include <wincodec.h>
#include <wrl/client.h>

#include <algorithm>
#include <atomic>
#include <cmath>
#include <map>
#include <memory>
#include <set>
#include <string>
#include <vector>
#include <thread>
#include <mutex>
#include <regex>
#include <fstream>

#ifdef HUB_MOD
#include <windhawk_tool_mod.h>
#endif

extern "C" IMAGE_DOS_HEADER __ImageBase;

#ifndef HUB_MOD
#define WH_MOD_VERSION L"1.1.0"
#define Wh_Log(...) ((void)0)
#endif
constexpr WCHAR kHubSelfId[] = L"local@seamless-workshop";  // How Windhawk lists this mod.

constexpr UINT WM_HUB_OPEN = WM_APP + 10, WM_HUB_LINK = WM_APP + 11, WM_HUB_REBUILD = WM_APP + 12,
               WM_HUB_TRAY = WM_APP + 13, WM_HUB_REGROUP = WM_APP + 17, WM_HUB_WINDHAWK = WM_APP + 18,
               WM_HUB_MODCHANGED = WM_APP + 19;
constexpr UINT_PTR kHubSyncTimer = 0x4858;  // Settles a burst of Windhawk changes into one refresh.
constexpr UINT_PTR kHubArmTimer = 0x4855;  // Ends the five-second "click again to remove" window.

// ---- Settings store: HKCU\Software\SeamlessWorkshop ------------------------------

constexpr WCHAR kHubKey[] = L"Software\\SeamlessWorkshop";

// One-time copy from the old Seamless Hub key. The old key is left in place.
static void Hub_MigrateStore() {
    HKEY key;
    if (RegOpenKeyExW(HKEY_CURRENT_USER, kHubKey, 0, KEY_READ, &key) == ERROR_SUCCESS) { RegCloseKey(key); return; }
    HKEY old;
    if (RegOpenKeyExW(HKEY_CURRENT_USER, L"Software\\SeamlessHub", 0, KEY_READ, &old) != ERROR_SUCCESS) return;
    if (RegCreateKeyExW(HKEY_CURRENT_USER, kHubKey, 0, nullptr, 0, KEY_ALL_ACCESS, nullptr, &key, nullptr) == ERROR_SUCCESS) {
        RegCopyTreeW(old, nullptr, key);
        RegCloseKey(key);
    }
    RegCloseKey(old);
}

static int Hub_RegGet(const std::wstring& name, int fallback) {
    DWORD v = 0, n = sizeof(v);
    if (RegGetValueW(HKEY_CURRENT_USER, kHubKey, name.c_str(), RRF_RT_REG_DWORD, nullptr, &v, &n) == ERROR_SUCCESS)
        return (int)v;
    return fallback;
}

static void Hub_RegSet(const std::wstring& name, int value) {
    HKEY key;
    if (RegCreateKeyExW(HKEY_CURRENT_USER, kHubKey, 0, nullptr, 0, KEY_SET_VALUE, nullptr, &key, nullptr) != ERROR_SUCCESS)
        return;
    DWORD v = (DWORD)value;
    RegSetValueExW(key, name.c_str(), 0, REG_DWORD, (const BYTE*)&v, sizeof(v));
    RegCloseKey(key);
}

#ifdef HUB_MOD
// The mod reads its window settings from Windhawk and keeps its window state in Windhawk's storage.
static int Hub_AppInt(PCWSTR name, int) { return Wh_GetIntSetting(name); }
#else
static int Wh_GetIntValue(PCWSTR key, int fallback) { return Hub_RegGet(key, fallback); }
static void Wh_SetIntValue(PCWSTR key, int value) { Hub_RegSet(key, value); }
static int Wh_GetIntSetting(PCWSTR name) {
    int def = wcscmp(name, L"nativeSettingsTitleBar") == 0 || wcscmp(name, L"discordPresence") == 0 ? 0 : 1;
    return Hub_RegGet(std::wstring(L"Set.") + name, def);
}
static int Hub_AppInt(PCWSTR name, int def) { return Hub_RegGet(std::wstring(L"Set.") + name, def); }
#endif
static std::wstring GetStringSetting(PCWSTR) { return std::wstring(); }

struct {
    bool animations = true;
} g_settings;

static void ForceForeground(HWND hwnd) {
    INPUT input{};
    SendInput(1, &input, sizeof(INPUT));
    SetForegroundWindow(hwnd);
    SetFocus(hwnd);
}

struct SetWindow;
struct SetField;
static std::wstring Hub_PageIntro(SetWindow& w);
static std::wstring Hub_PageTitle(SetWindow& w);
static std::wstring Hub_Banner(SetWindow& w);
static void Hub_ItemsTop(SetWindow& w, float& y);
static void Hub_ItemsBottom(SetWindow& w, float& y);
static bool Hub_Show(SetWindow& w, const SetField& f);
static WCHAR Hub_LinkGlyph(const std::wstring& url);
static bool Hub_Resettable(SetWindow& w, SetField& f);
static bool Hub_LeaveDetail(SetWindow& w, bool& left);
static bool Hub_Link(PCWSTR url);
static void Hub_Cancel(SetWindow& w);
static void Hub_Escape(SetWindow& w);
static void Hub_InitFields(SetWindow& w);
static void Hub_PageChanged(SetWindow& w);
static void Hub_FeatureFields(SetWindow& w);
static void Hub_FeatureItems(SetWindow& w, float& y);
static void Hub_Action(SetWindow& w, const std::wstring& action);
static void Hub_Presence();
static std::wstring Hub_RegText(const std::wstring& key);
static bool Hub_SetText(const std::wstring& key, const std::wstring& value);
static bool Hub_Backup(const std::vector<std::wstring>& ids, std::wstring& err);
struct SetPaint;
struct SetItem;
struct SetHit;
static float Hub_MaxW(const SetWindow& w);
static bool Hub_DrawRow(SetPaint& p, SetWindow& w, const SetItem& it);
static bool Hub_DrawLink(SetPaint& p, SetWindow& w, const SetItem& it, int idx);
static bool Hub_BarBox(const SetField& f, const D2D1_RECT_F& row, D2D1_RECT_F& box);
static bool Hub_HitRow(SetWindow& w, const SetItem& it, const D2D1_RECT_F& row, float x, float cy, SetHit& h);
static void Hub_HitLink(SetWindow& w, int i, const D2D1_RECT_F& row, float x, float cy, SetHit& h);
static void Hub_CardClick(SetWindow& w, int a, int b);
static void Hub_Chose(SetWindow& w, int k);
static void Hub_Reflow(SetWindow& w, float& y);
constexpr UINT WM_HUB_ACTION = WM_APP + 14, WM_HUB_RESULT = WM_APP + 15, WM_HUB_FEED = WM_APP + 16;

// ---- engine-hub.inc (inlined) ----
// The settings window, from the "..." menu. It shows the same settings as
// Windhawk's page for this mod and saves them through windhawk-cli, so the two
// stay in step. Writing a mod's settings takes admin rights, so the save runs
// the CLI elevated (silently where UAC prompts are off).

constexpr WCHAR kSettingsClass[] = L"SeamlessWorkshopWindow";
constexpr UINT WM_APP_SETTINGS_RELOAD = WM_APP + 1, WM_APP_SETTINGS_ACTIVATE = WM_APP + 2;
HANDLE g_settingsThread = nullptr;
std::atomic<HWND> g_settingsWnd;
std::atomic<bool> g_settingsStop;
void Settings_Close();
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
    int hub = 0;         // Hub: 0 app setting, 1 mod switch, 2 search box, 3 a mod's own setting.
    int mod = -1;        // Hub: which mod a switch belongs to.
    int vtype = 0;       // Hub: 0 number, 1 text (how a mod setting is written back).
    int grp = 0;         // Hub: a new list entry; its fields are written together.
    PCWSTR arr = nullptr;  // Hub: the list this plain entry belongs to.
    float fitW = 0;      // Box width that fits the text (Set_FitBoxes); 0 until measured.
    float fitText = -1;  // Measured text width behind fitW.
    std::wstring fitFor; // The text that was measured.
};

// Names, descriptions and option labels match the ==WindhawkModSettings== block word for word.
// Generated by test-settings\gen_table.py from src\00-header.cpp.
static std::vector<SetField> Set_MakeFields() {
    using K = SetField;
    return {
{K::Check, L"settingsGlass", L"Blurred settings window", L"On, the settings window is see-through glass with Windows acrylic behind it. Off, it is solid. Applies when you save.", L"1", {}, 0, 100, 6, L"Settings window"},
{K::Check, L"nativeSettingsTitleBar", L"Native Windows title bar", L"Use the Windows title bar and window buttons for this settings window. Applies when you save.", L"0", {}, 0, 100, 6, L"Settings window"},
{K::Check, L"animations", L"Animations", L"Off, everything snaps instantly: page changes, hover fades and switches.", L"1", {}, 0, 100, 6, L"Settings window"},
{K::Check, L"settingsTrayIcon", L"Tray icon", L"Keeps Seamless Workshop in the system tray. Closing the window then hides it there. Click the icon to open it, right-click it to quit.", L"1", {}, 0, 100, 6, L"Settings window"}
    };
}

struct SetPageInfo {
    PCWSTR name, intro;
    WCHAR glyph;
};
static const SetPageInfo kSetPages[] = {
{L"Mods", L"Every mod you have installed. Flip a switch to turn one on or off, or open a card for its settings.", 0xEA86},
{L"Marketplace", L"Find mods in the Windhawk library. New installs stay off until you turn them on.", 0xE719},
{L"Updates", L"Check the library, then choose each mod to update.", 0xE895},
{L"Presets", L"Save selected mods and their settings, then restore them together.", 0xE8F1},
{L"Developer", L"Inspect source, check metadata and compile a disabled mod.", 0xE943},
{L"Settings", L"How Seamless Workshop checks, saves and backs up.", 0xE713},
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
// Middle-click autoscroll: no movement inside kSetAutoDead, then speed grows with distance.
constexpr float kSetAutoDead = 10, kSetAutoR = 18, kSetAutoGain = 0.14f, kSetAutoMax = 56;
constexpr PCWSTR kSetAutoProp = L"SeamlessOwnAutoscroll";  // Seamless Autoscroll skips this window.
constexpr PCWSTR kSetKofiUrl = L"https://ko-fi.com/DavidHiFi";
constexpr PCWSTR kSetAuthorUrl = L"https://github.com/DavidHiFi";
constexpr PCWSTR kSetDittoUrl = L"https://windhawk.net/mods/fullscreen-start";
constexpr PCWSTR kSetRepoUrl = L"https://github.com/DavidHiFi/seamless-workshop";
constexpr PCWSTR kSetBugUrl =
    L"https://github.com/DavidHiFi/seamless-workshop/issues/new?title=%5BSeamless%20Workshop%5D%20";
constexpr PCWSTR kSetTitle = L"Seamless Workshop";
// The self-drawn title bar. Everything below it is laid out as before, in "content" DIPs.
static float kSetCapH = 40;
constexpr float kSetCapBtnW = 46, kSetHoverMs = 120;
constexpr float kSetMenuPad = 6, kSetMenuIconW = 22, kSetMenuSepH = 9, kSetMenuOverlap = 3, kSetMenuMinW = 190, kSetMenuMaxW = 640, kSetMenuBorderW = 2;
constexpr UINT kSetMenuSubDelayMs = 200, kSetMenuFadeMs = 90, kSetMenuTimerSub = 0x5E71, kSetMenuTimerFade = 0x5E72, kSetMenuTimerPoll = 0x5E73;

struct SetItem {
    enum Type { Group, Row, Banner, About, Link, Support } type = Row;
    int field = -1;  // Row: index into fields.
    float y = 0, h = 0;
    float x = 0, w = 0;  // Hub: a card cell; 0 means the full content width.
    std::wstring text, sub, url;
};

// What the pointer is over. id picks the hover glow.
struct SetHit {
    enum Kind { None, Rail, Row, Control, Slider, Clear, Chip, Footer, Drop, Link, Scroll, Popup, Caption, RailToggle, RailEdge, Open, Card } kind = None;
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
    // Middle-click autoscroll: the anchor in content DIPs; autoA eases the indicator in and out.
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
// ---- Tray menu (since Launchpad 2.6.0) --------------------------------------------------------
// Every mod's tray menu: Clipboard's Direct2D menu, one acrylic popup per level, a glyph column,
// measured labels, submenus, keyboard and click-away. Build a std::vector<SetMenuItem> and call
// Set_TrayMenu(owner, items); it returns the picked id, or 0.

// The live window corner radius: the custom-corner-radius mod's value, 8 when it is off.
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

// Row heights and a width that fits the longest label and hint, so nothing is cut off.
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

// The next enabled row from `from` in direction dir (+1 or -1), wrapping. -1 when there is none.
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

// Closes every level from n down; n == 0 closes the whole menu.
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

// Clipboard's popup material: dark, round corners, no system border, the accent acrylic blur.
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

// Makes the popup at `at`, reads its monitor's scale, then sizes it to the rows. A root menu flips
// to the left of or above the point near a monitor edge; a submenu sits beside its parent row.
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

// Arrows move, Right or Enter opens a submenu, Left or Esc closes one level, Enter or Space picks.
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

// Shows a tray menu at `at` (the pointer when null) and returns the picked id, or 0. Runs its own
// message loop on the calling thread, like TrackPopupMenu with TPM_RETURNCMD.
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
        if (w.fRailName && Set_TextW(w.fRailName.get(), L"Workshop") <= railW) break;
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
        if (f.hub) continue;
        bool isInt = f.kind == SetField::Number || f.kind == SetField::Check;
        Set_PutValue(f, isInt ? std::to_wstring(Wh_GetIntSetting(f.key)) : GetStringSetting(f.key));
        f.value = Set_FieldValue(f);  // What the window shows, so an untouched field never saves.
    }
}

static int Set_ChangedCount(const SetWindow& w) {
    int n = 0;
    for (auto& f : w.fields)
        if (f.hub != 2 && f.hub != 5 && Set_FieldValue(f) != f.value) n++;
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
    return !w.render && g_settings.animations && on;
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
        case SetField::Check: return f.hub == 1 ? 40 + 30 : 40;
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
    if (Hub_BarBox(f, row, p.box)) return p;
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
    if (it.w > 0) return {it.x, it.y, it.x + it.w, it.y + it.h};  // Hub card cell.
    return {w.contentX, it.y, w.contentX + w.contentW, it.y + it.h};  // Content y (not scrolled).
}

// Lays out the current page's items for the current width.
static void Set_BuildPage(SetWindow& w) {
    w.items.clear();
    const float space = Set_RailSpace(w), avail = w.cw - space;
    w.contentW = std::clamp(avail - 2 * kSetPadX, 420.0f, std::max(420.0f, Hub_MaxW(w)));
    w.contentX = space + std::max(kSetPadX, (avail - w.contentW) / 2);
    float introH = Set_TextH(w.fIntro.get(), Hub_PageIntro(w), w.contentW);
    float y = 36 + 36 + 4 + introH + 24;
    if (w.page == 0) {
        std::wstring status = Hub_Banner(w);
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
    Hub_ItemsTop(w, y);
    PCWSTR lastGroup = nullptr;
    for (size_t k = 0; k < w.fields.size(); k++) {
        const SetField& f = w.fields[k];
        if (!Hub_Show(w, f)) continue;
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
        float dh = (f.desc && *f.desc) ? Set_TextH(w.fHint.get(), f.desc, textW) + 3 : 0;
        it.y = y;
        it.h = std::max(kSetRowMin, 28 + lh + dh);
        y += it.h + kSetRowGap;
        w.items.push_back(it);
    }
    Hub_ItemsBottom(w, y);
    Hub_Reflow(w, y);
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
        add(SetItem::Support, 84, L"Like it? Help the project keep going.",
            L"Free and open source. A tip on Ko-fi keeps it moving.", kSetKofiUrl);
        group(L"Author");
        add(SetItem::Link, 56, L"DavidHiFi on GitHub", L"github.com/DavidHiFi", kSetAuthorUrl);
        add(SetItem::Link, 56, L"Ko-fi", L"ko-fi.com/DavidHiFi", kSetKofiUrl);
        group(L"Credits");
        add(SetItem::Link, 56, L"Windhawk by Ramen Software", L"The engine that loads and runs every mod", L"https://windhawk.net");
        add(SetItem::Link, 56, L"Windhawk source code", L"github.com/ramensoftware/windhawk", L"https://github.com/ramensoftware/windhawk");
        group(L"Project");
        add(SetItem::Link, 56, L"Project page on GitHub", L"github.com/DavidHiFi/seamless-workshop", kSetRepoUrl);
        add(SetItem::Link, 56, L"Report a problem", L"Opens a new issue on GitHub, with the app's name filled in", kSetBugUrl);
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
    if (h.kind == SetHit::Card) ids[1] = h.a >= 0 ? 1000 + h.a : 3000 + (-h.a - 1);  // Light the card too.
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
    if (Hub_DrawRow(p, w, it)) return;
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
            if (f.hub == 1) p.Glyph(w.fIconS.get(), 0xE76C, {tr.left - 32, row.top, tr.left - 8, row.bottom}, mocha::overlay1);
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
    if (Hub_DrawLink(p, w, it, idx)) return;
    D2D1_RECT_F row = Set_RowRect(w, it);
    float hov = Set_GlowOf(w, 3000 + idx);
    Set_DrawCard(p, row, hov);
    p.GradFill(row, 10, 0.13f * hov);
    p.GradRing(row, 10, hov, 1.5f);
    p.Text(w.fLabel.get(), it.text, {row.left + kSetRowPad, row.top + 9, row.right - 50, row.top + 30}, mocha::text);
    p.Text(w.fHint.get(), it.sub, {row.left + kSetRowPad, row.top + 30, row.right - 50, row.bottom - 4}, mocha::subtext0);
    p.Glyph(w.fIcon.get(), Hub_LinkGlyph(it.url), {row.right - 46, row.top, row.right - 12, row.bottom},
            it.url == L"hub:remove" ? mocha::red : mocha::subtext1);
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
    p.Glyph(w.fIconL.get(), 0xEA86, mark, mocha::crust);
    float x = mark.right + 20;
    p.Text(w.fBig.get(), L"Seamless Workshop", {x, row.top + 18, row.right - 16, row.top + 46}, mocha::text);
#ifdef WH_MOD_VERSION
    std::wstring ver = std::wstring(L"Version ") + WH_MOD_VERSION + L"  \u00B7  Open source  \u00B7  Runs on Windhawk";
#else
    std::wstring ver = L"MIT license  \u00B7  A Windhawk mod";
#endif
    p.Text(w.fHint.get(), ver, {x, row.top + 48, row.right - 16, row.top + 68}, mocha::subtext0);
    p.Text(w.fHint.get(), L"One place to install, update, turn on and off and set up Windhawk mods.",
           {x, row.top + 72, row.right - 16, row.top + 110}, mocha::subtext1);
    p.Text(w.fHint.get(), L"Made by DavidHiFi. Windhawk itself is made by Ramen Software.",
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
    p.Text(w.fRailName.get(), L"Workshop", {d.left + 90, d.top + 32, d.left + w.railW - 10, d.top + 56}, mocha::text, textA);
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
    p.Glyph(glyph, 0xEA86, r, mocha::crust);
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

// The autoscroll anchor, in Seamless Autoscroll's look: a frosted Mocha disc with the 2px blue to
// mauve ring, an arrow that lights blue the way the page moves, and a mauve centre dot.
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
        cp.Text(w.fTitle.get(), Hub_PageTitle(w), {w.contentX, 36, w.contentX + w.contentW, 72}, mocha::text);
        place(1, rise);
        cp.Text(w.fIntro.get(), Hub_PageIntro(w), {w.contentX, 76, w.contentX + w.contentW, 76 + 40}, mocha::subtext0);
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
            Hub_HitLink(w, (int)i, row, x, cy, h);
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
            if (Hub_HitRow(w, it, row, x, cy, h)) return h;
            h.kind = f.kind == SetField::Check ? SetHit::Control : SetHit::Row;
            if (f.hub == 1 && !Set_In({pt.box.left - 10, row.top, row.right, row.bottom}, x, cy)) {
                h.kind = SetHit::Open;  // The row opens the mod; only the switch flips it.
                return h;
            }
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
           h.kind == SetHit::Scroll || h.kind == SetHit::RailToggle || h.kind == SetHit::Open || h.kind == SetHit::Card;
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
    std::wstring text = std::to_wstring(vk);
    if (!text.empty()) return text;
    // Fallback while the capture part is a stub.
    if (mods & MOD_CONTROL) text += L"Ctrl+";
    if (mods & MOD_ALT) text += L"Alt+";
    if (mods & MOD_SHIFT) text += L"Shift+";
    if (mods & MOD_WIN) text += L"Win+";
    WCHAR name[64] = {};
    LONG scan = (LONG)MapVirtualKeyW(vk, MAPVK_VK_TO_VSC) << 16;
    if (GetKeyNameTextW(scan, name, ARRAYSIZE(name)) > 0) {
        text += name;
    } else {
        text += std::to_wstring(vk);
    }
    return text;
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
    DWORD style = WS_CHILD | ES_AUTOHSCROLL | (f.kind == SetField::Number ? (f.min < 0 ? 0 : ES_NUMBER) | ES_CENTER : 0);
    // Over the extended frame GDI text would come out see-through; a layered child keeps it solid.
    w.edit = CreateWindowExW(w.glass ? WS_EX_LAYERED : 0, L"EDIT", L"", style, 0, 0, 10, 10, w.hwnd, nullptr,
                             GetModuleHandleW(nullptr), nullptr);
    if (!w.edit) return;
    if (w.glass) SetLayeredWindowAttributes(w.edit, 0, 255, LWA_ALPHA);
    int base = std::clamp(500, 100, 900);
    w.editFont = CreateFontW(-MulDiv(13, w.dpi, 96), 0, 0, 0, base, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS,
                             CLIP_DEFAULT_PRECIS, CLEARTYPE_QUALITY, DEFAULT_PITCH, w.family.c_str());
    SendMessageW(w.edit, WM_SETFONT, (WPARAM)w.editFont, TRUE);
    SendMessageW(w.edit, EM_SETLIMITTEXT, f.kind == SetField::Number ? 11 : f.kind == SetField::Color ? 7 : 8000, 0);
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
    Hub_Chose(w, k);
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
    for (auto& f : w.fields)
        if (Hub_Resettable(w, f)) Set_PutValue(f, f.def);
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
    bool left = false;
    if (!Hub_LeaveDetail(w, left)) return;
    if (page == w.page && !left) return;
    w.page = page;
    Hub_PageChanged(w);
    w.scrollY = w.scrollTarget = 0;
    w.focus = -1;
    w.pageT = Set_Anim(w) ? 0.0f : 1.0f;
    Set_BuildAndClamp(w);
}

static void Set_OpenLink(PCWSTR url) {
    if (Hub_Link(url)) return;
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
            Hub_Chose(w, k);
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
        Hub_Cancel(w);
    } else {
        Set_CommitEdit(w, true);
        if (g_setWin && g_setWin->hwnd == w.hwnd) Set_Save(g_setWin);
    }
}

// ---- Saving ---------------------------------------------------------------------

// ---- Middle-click autoscroll (every settings window, 2026-11-16) ----------------------
// Press the middle button and move: the page scrolls, faster the farther the pointer is from
// where it started. Press and release without moving: it keeps going until the next click, a
// key or the wheel. Press, move and release: it stops on release. Browser behaviour.

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

// The pointer moved while autoscrolling: keep the scroll cursor, and note a drag with the button held.
static void Set_AutoScrollMove(SetWindow& w, bool held) {
    if (held && fabsf(w.mouseY - w.autoY) > kSetAutoDead) w.autoMoved = true;
    SetCursor(LoadCursorW(nullptr, IDC_SIZENS));
}

// One timer tick of autoscroll. True when something on screen changed.
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
            if (w.focus >= 0 && vk == VK_RETURN && w.fields[w.focus].hub == 1) PostMessageW(w.hwnd, WM_HUB_OPEN, (WPARAM)w.focus, 0);
            else if (w.focus >= 0) Set_ActivateField(w, w.focus, nullptr);
            else if (w.focus <= -1 && w.focus >= -3) Set_FooterAction(w, -1 - w.focus);
            return true;
        case VK_LEFT:
        case VK_RIGHT:
            w.kbd = true;
            Set_Adjust(w, vk == VK_RIGHT ? 1 : -1);
            Hub_Chose(w, w.focus);
            return true;
        case VK_UP: w.scrollTarget = std::clamp(w.scrollTarget - 60, 0.0f, maxScroll); break;
        case VK_DOWN: w.scrollTarget = std::clamp(w.scrollTarget + 60, 0.0f, maxScroll); break;
        case VK_PRIOR: w.scrollTarget = std::clamp(w.scrollTarget - view * 0.9f, 0.0f, maxScroll); break;
        case VK_NEXT: w.scrollTarget = std::clamp(w.scrollTarget + view * 0.9f, 0.0f, maxScroll); break;
        case VK_HOME: w.scrollTarget = 0; break;
        case VK_END: w.scrollTarget = maxScroll; break;
        case VK_ESCAPE:
            Hub_Escape(w);
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
                case SetHit::Card:
                    Hub_CardClick(*w, h.a, h.b);
                    break;
                case SetHit::Open:
                    PostMessageW(hwnd, WM_HUB_OPEN, (WPARAM)h.a, 0);
                    break;
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
    HWND hwnd = CreateWindowExW(0, kSettingsClass, L"Seamless Workshop", style,
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
    Hub_InitFields(*w);
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
// ---- end of engine-hub.inc ----
static bool g_cardsGrid = true;  // Saved as Set.modsView: 1 grid, 0 list.

// ---- JSON ---------------------------------------------------------------------

struct Js {
    enum T { Null, Bool, Num, Str, Arr, Obj } t = Null;
    bool b = false;
    std::wstring s;  // A string, or a number's own text.
    std::vector<Js> a;
    std::vector<std::wstring> keys;  // Obj: keys[i] names a[i].
    const Js* get(PCWSTR k) const {
        if (t != Obj) return nullptr;
        for (size_t i = 0; i < keys.size(); i++)
            if (keys[i] == k) return &a[i];
        return nullptr;
    }
};

struct JsReader {
    const wchar_t *p, *e;
    void ws() {
        while (p < e && (*p == L' ' || *p == L'\t' || *p == L'\n' || *p == L'\r')) p++;
    }
    bool str(std::wstring& out) {
        if (p >= e || *p != L'"') return false;
        p++;
        while (p < e && *p != L'"') {
            if (*p != L'\\') {
                if (*p < 0x20) return false;
                out += *p++;
                continue;
            }
            if (++p >= e) return false;
            wchar_t c = *p++;
            switch (c) {
                case L'n': out += L'\n'; break;
                case L't': out += L'\t'; break;
                case L'r': out += L'\r'; break;
                case L'b': out += L'\b'; break;
                case L'f': out += L'\f'; break;
                case L'u':
                    if (e - p < 4) return false;
                    for (int i = 0; i < 4; ++i) if (!iswxdigit(p[i]) || p[i] > 127) return false;
                    out += (wchar_t)wcstoul(std::wstring(p, 4).c_str(), nullptr, 16);
                    p += 4;
                    break;
                case L'"': case L'\\': case L'/': out += c; break;
                default: return false;
            }
        }
        if (p >= e) return false;
        p++;
        return true;
    }
    bool lit(PCWSTR word) {
        size_t n = wcslen(word);
        if ((size_t)(e - p) < n || wcsncmp(p, word, n) != 0) return false;
        p += n;
        return true;
    }
    bool val(Js& v, int depth) {
        if (depth > 64) return false;
        ws();
        if (p >= e) return false;
        if (*p == L'{') {
            v.t = Js::Obj;
            p++;
            ws();
            if (p < e && *p == L'}') return ++p, true;
            for (;;) {
                ws();
                std::wstring k;
                if (!str(k)) return false;
                if (std::find(v.keys.begin(), v.keys.end(), k) != v.keys.end()) return false;
                ws();
                if (p >= e || *p != L':') return false;
                p++;
                v.keys.push_back(k);
                v.a.emplace_back();
                if (!val(v.a.back(), depth + 1)) return false;
                ws();
                if (p < e && *p == L',') { p++; continue; }
                if (p < e && *p == L'}') return ++p, true;
                return false;
            }
        }
        if (*p == L'[') {
            v.t = Js::Arr;
            p++;
            ws();
            if (p < e && *p == L']') return ++p, true;
            for (;;) {
                v.a.emplace_back();
                if (!val(v.a.back(), depth + 1)) return false;
                ws();
                if (p < e && *p == L',') { p++; continue; }
                if (p < e && *p == L']') return ++p, true;
                return false;
            }
        }
        if (*p == L'"') return v.t = Js::Str, str(v.s);
        if (lit(L"true")) return v.t = Js::Bool, v.b = true, true;
        if (lit(L"false")) return v.t = Js::Bool, true;
        if (lit(L"null")) return v.t = Js::Null, true;
        const wchar_t* s = p;
        auto digit = [&] { return p < e && *p >= L'0' && *p <= L'9'; };
        if (p < e && *p == L'-') ++p;
        if (!digit()) return false;
        if (*p == L'0') ++p;
        else while (digit()) ++p;
        if (p < e && *p == L'.') {
            ++p; if (!digit()) return false;
            while (digit()) ++p;
        }
        if (p < e && (*p == L'e' || *p == L'E')) {
            ++p; if (p < e && (*p == L'+' || *p == L'-')) ++p;
            if (!digit()) return false;
            while (digit()) ++p;
        }
        v.t = Js::Num;
        v.s.assign(s, p);
        return true;
    }
};

static std::wstring Hub_Wide(const std::string& s) {
    if (s.empty()) return std::wstring();
    int n = MultiByteToWideChar(CP_UTF8, 0, s.data(), (int)s.size(), nullptr, 0);
    std::wstring w(n, L'\0');
    MultiByteToWideChar(CP_UTF8, 0, s.data(), (int)s.size(), w.data(), n);
    return w;
}

static std::string Hub_Utf8(const std::wstring& w) {
    if (w.empty()) return std::string();
    int n = WideCharToMultiByte(CP_UTF8, 0, w.data(), (int)w.size(), nullptr, 0, nullptr, nullptr);
    std::string s(n, '\0');
    WideCharToMultiByte(CP_UTF8, 0, w.data(), (int)w.size(), s.data(), n, nullptr, nullptr);
    return s;
}

static bool Js_Parse(const std::wstring& text, Js& out) {
    JsReader r{text.data(), text.data() + text.size()};
    if (!r.val(out, 0)) return false;
    r.ws();
    return r.p == r.e;
}

static std::wstring Js_Text(const Js* v) {
    if (!v) return std::wstring();
    switch (v->t) {
        case Js::Str:
        case Js::Num: return v->s;
        case Js::Bool: return v->b ? L"1" : L"0";
        default: return std::wstring();
    }
}

static std::wstring Js_Quote(const std::wstring& s) {
    std::wstring out = L"\"";
    for (wchar_t c : s) {
        if (c == L'"' || c == L'\\') {
            out += L'\\';
            out += c;
        } else if (c < 0x20) {
            WCHAR buf[8];
            swprintf_s(buf, L"\\u%04X", (unsigned)c);
            out += buf;
        } else {
            out += c;
        }
    }
    return out + L"\"";
}

// ---- windhawk-cli ---------------------------------------------------------------

static std::wstring Hub_CliPath() {
    WCHAR buf[MAX_PATH];
    if (ExpandEnvironmentStringsW(L"%ProgramFiles%\\Windhawk\\windhawk-cli.exe", buf, MAX_PATH) &&
        GetFileAttributesW(buf) != INVALID_FILE_ATTRIBUTES)
        return buf;
    GetModuleFileNameW(nullptr, buf, MAX_PATH);
    std::wstring dir = buf;
    dir.resize(dir.find_last_of(L'\\') + 1);
    return dir + L"windhawk-cli.exe";
}

static std::wstring Hub_Sha256(const std::wstring& path);

static bool Hub_FileThere(const std::wstring& path) {
    const DWORD a = GetFileAttributesW(path.c_str());
    return a != INVALID_FILE_ATTRIBUTES && !(a & FILE_ATTRIBUTE_DIRECTORY);
}

// Optional developer tools, each a full path in HKCU\Software\SeamlessWorkshop (Tool.glassScript,
// Tool.loadGate, Tool.engineGuide). Without them the Workshop uses windhawk-cli directly.
static std::wstring Hub_Tool(PCWSTR name) { return Hub_RegText(name); }

// A real python.exe: the usual per-user install, else the first one on PATH that is not the
// Microsoft Store stub.
static std::wstring Hub_Python() {
    static std::wstring found = [] {
        WCHAR buf[MAX_PATH];
        if (ExpandEnvironmentStringsW(L"%LOCALAPPDATA%\\Programs\\Python\\Python313\\python.exe", buf, MAX_PATH) &&
            Hub_FileThere(buf))
            return std::wstring(buf);
        WCHAR path[32768];
        const DWORD n = GetEnvironmentVariableW(L"PATH", path, 32768);
        std::wstring all(path, n < 32768 ? n : 0);
        for (size_t at = 0; at <= all.size();) {
            size_t end = all.find(L';', at);
            if (end == std::wstring::npos) end = all.size();
            std::wstring dir = all.substr(at, end - at);
            at = end + 1;
            std::wstring low = dir;
            if (!low.empty()) CharLowerBuffW(low.data(), (DWORD)low.size());
            if (dir.empty() || low.find(L"\\windowsapps") != std::wstring::npos) continue;
            if (dir.back() != L'\\') dir += L'\\';
            if (Hub_FileThere(dir + L"python.exe")) return dir + L"python.exe";
        }
        return std::wstring();
    }();
    return found;
}

static std::wstring Hub_SelfDir() {
    WCHAR self[MAX_PATH];
    GetModuleFileNameW(nullptr, self, MAX_PATH);
    std::wstring dir = self;
    dir.resize(dir.find_last_of(L"\\/") + 1);
    return dir;
}

// The load-gated helper runs only where python, the helper and the tower's load gate all exist.
static bool Hub_HelperReady() {
    return !Hub_Python().empty() && Hub_FileThere(Hub_SelfDir() + L"guarded-compile.py") && Hub_FileThere(Hub_Tool(L"Tool.loadGate"));
}
static bool Hub_GlassReady() { return !Hub_Python().empty() && Hub_FileThere(Hub_Tool(L"Tool.glassScript")); }

// Commands that download, compile or move whole archives get five minutes, not fifteen seconds.
static bool Hub_LongCli(const std::wstring& args) {
    for (PCWSTR p : {L"mod install", L"mod update", L"mod compile", L"data import", L"data export", L"@"})
        if (args.find(p) == 0) return true;
    return false;
}

// Runs windhawk-cli hidden with stdout captured. Gives up (and ends it) after 15 seconds.
static bool Hub_RunCli(const std::wstring& args, std::string& out) {
    SECURITY_ATTRIBUTES sa{sizeof(sa), nullptr, TRUE};
    HANDLE rd = nullptr, wr = nullptr;
    if (!CreatePipe(&rd, &wr, &sa, 0)) return false;
    SetHandleInformation(rd, HANDLE_FLAG_INHERIT, 0);
    HANDLE nul = CreateFileW(L"NUL", GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, &sa,
                             OPEN_EXISTING, 0, nullptr);
    STARTUPINFOW si{sizeof(si)};
    si.dwFlags = STARTF_USESTDHANDLES | STARTF_USESHOWWINDOW;
    si.wShowWindow = SW_HIDE;
    si.hStdInput = nul;
    si.hStdOutput = wr;
    si.hStdError = nul;
    std::wstring cli = Hub_CliPath();
    std::wstring cmd = Set_QuoteArg(cli) + L" " + args;
    // "@compile <id>" and "@install <sha256> <file>" go through the load-gated helper beside the exe
    // when this PC has it; elsewhere they run straight through windhawk-cli (the fingerprint is
    // still checked first). "@glass" runs the workspace glass check, which only reads source.
    // "@selfinstall <sha256> <file>" is the Workshop updating itself: always straight through
    // windhawk-cli, fingerprint checked, and it stays turned on.
    const bool heavy = args.find(L"@compile ") == 0 || args.find(L"@install ") == 0 || Hub_LongCli(args);
    const bool glass = args == L"@glass";
    const bool self = args.find(L"@selfinstall ") == 0;
    if (args[0] == L'@' && !glass && (self || !Hub_HelperReady())) {
        std::wstring rest = args.substr(args.find(L' ') + 1);
        if (rest.size() > 7 && rest.compare(rest.size() - 7, 7, L" --json") == 0) rest.resize(rest.size() - 7);
        if (args.find(L"@compile ") == 0) {
            cmd = Set_QuoteArg(cli) + L" mod compile " + rest + L" --json";
        } else {
            const size_t sp = rest.find(L' ');
            std::wstring sha = rest.substr(0, sp), file = sp == std::wstring::npos ? L"" : rest.substr(sp + 1);
            if (file.size() >= 2 && file.front() == L'"' && file.back() == L'"') file = file.substr(1, file.size() - 2);
            if (file.empty() || Hub_Sha256(file) != sha) {
                out = "{\"success\":false,\"error\":{\"message\":\"The file changed after it was checked. Nothing was installed.\"}}";
                CloseHandle(rd); CloseHandle(wr);
                if (nul != INVALID_HANDLE_VALUE) CloseHandle(nul);
                return false;
            }
            cmd = Set_QuoteArg(cli) + L" mod install --file " + Set_QuoteArg(file) + (self ? L" --json" : L" --disabled --json");
        }
    } else if (heavy && args[0] == L'@' || glass) {
        if (glass && !Hub_GlassReady()) {
            CloseHandle(rd); CloseHandle(wr);
            if (nul != INVALID_HANDLE_VALUE) CloseHandle(nul);
            return false;
        }
        cli = Hub_Python();
        WCHAR self[MAX_PATH]; GetModuleFileNameW(nullptr, self, MAX_PATH);
        std::wstring helper = self; helper.resize(helper.find_last_of(L"\\/") + 1); helper += L"guarded-compile.py";
        if (glass) helper = Hub_Tool(L"Tool.glassScript");
        cmd = Set_QuoteArg(cli) + L" " + Set_QuoteArg(helper) + L" " + (glass ? L"check" : args.substr(1));
    }
    PROCESS_INFORMATION pi{};
    BOOL started = CreateProcessW(cli.c_str(), cmd.data(), nullptr, nullptr, TRUE, CREATE_NO_WINDOW, nullptr, nullptr,
                                  &si, &pi);
    CloseHandle(wr);
    if (nul != INVALID_HANDLE_VALUE) CloseHandle(nul);
    if (!started) {
        CloseHandle(rd);
        return false;
    }
    const ULONGLONG deadline = GetTickCount64() + (heavy ? 300000 : glass ? 60000 : 15000);
    bool done = false, ok = true;
    char buf[16384];
    for (;;) {
        if (GetTickCount64() > deadline || out.size() > (32u << 20)) {
            TerminateProcess(pi.hProcess, 1); ok = false; break;
        }
        DWORD avail = 0;
        if (PeekNamedPipe(rd, nullptr, 0, nullptr, &avail, nullptr) && avail) {
            DWORD got = 0;
            if (ReadFile(rd, buf, std::min<DWORD>(avail, sizeof(buf)), &got, nullptr) && got) out.append(buf, got);
            continue;
        }
        if (done) break;
        if (WaitForSingleObject(pi.hProcess, 10) == WAIT_OBJECT_0) {
            done = true;  // One more pass drains what is left in the pipe.
            continue;
        }
        if (GetTickCount64() > deadline) {
            TerminateProcess(pi.hProcess, 1);
            ok = false;
            break;
        }
    }
    DWORD exitCode = 1;
    GetExitCodeProcess(pi.hProcess, &exitCode);
    ok = ok && exitCode == 0;
    CloseHandle(rd);
    CloseHandle(pi.hThread);
    CloseHandle(pi.hProcess);
    return ok;
}

// One CLI command with --json. On success data holds the reply's "data"; else err says why.
static bool Hub_Cli(const std::wstring& args, Js& data, std::wstring& err) {
    std::string out;
    const bool ran = Hub_RunCli(args + L" --json", out);
    Js root;
    const bool parsed = Js_Parse(Hub_Wide(out), root) && root.t == Js::Obj;
    if (!parsed) {
        err = ran ? L"Windhawk's command line gave an answer this app cannot read." : L"Windhawk's command line did not answer.";
        return false;
    }
    // A failing command still prints its JSON reply, so its own message is used when there is one.
    const Js* ok = root.get(L"success");
    if (!ran || !ok || ok->t != Js::Bool || !ok->b) {
        const Js* e = root.get(L"error");
        err = Js_Text(e ? e->get(L"message") : nullptr);
        if (err.empty()) err = L"Windhawk refused the change.";
        return false;
    }
    if (const Js* d = root.get(L"data")) data = *d;
    return true;
}

// ---- Model ----------------------------------------------------------------------

static PCWSTR Hub_In(const std::wstring& s) {
    static std::set<std::wstring> pool;  // Set nodes never move, so the pointers stay good.
    return pool.insert(s).first->c_str();
}

static std::wstring Hub_Lower(std::wstring s) {
    if (!s.empty()) CharLowerBuffW(s.data(), (DWORD)s.size());
    return s;
}

struct HubMod {
    std::wstring id, name, version, author, desc, lower;
    bool enabled = false, update = false;
    // Its Windhawk config, which mod list carries with each mod.
    std::vector<std::wstring> include, exclude, incCustom, excCustom;
    bool logging = false, debugLog = false, customOnly = false, critical = false;
    std::wstring updatesOff, userScope, nuked;
    int src = 0, area = 0;  // Section on the Mods page: where it comes from, what it changes.
};

// Where a mod comes from. DavidHiFi first in the author line marks his mods, local or library.
constexpr PCWSTR kHubSrcName[] = {L"From DavidHiFi", L"From the Windhawk library", L"Your own local mods"};

static int Hub_ModSource(const HubMod& m) {
    std::wstring a = Hub_Lower(m.author);
    if (a.rfind(L"davidhifi", 0) == 0) return 0;
    return m.id.rfind(L"local@", 0) == 0 ? 2 : 1;
}

// What a mod changes, from the programs it loads into, then words in its name:
// 0 window look, 1 taskbar, Start and tray, 2 every app, 3 File Explorer and desktop,
// 4 tools that run on their own, 5 single apps, 6 set by hand. Hub_ModCat turns it into a group.

static int Hub_ModArea(const HubMod& m) {
    const std::wstring name = Hub_Lower(m.name);
    auto named = [&](std::initializer_list<PCWSTR> words) {
        for (PCWSTR w : words) if (name.find(w) != std::wstring::npos) return true;
        return false;
    };
    bool dwm = false, shell = false, all = false, explorer = false, tool = true;
    for (auto& raw : m.include) {
        const std::wstring p = Hub_Lower(raw);
        if (p == L"dwm.exe") dwm = true;
        else if (p == L"startmenuexperiencehost.exe" || p == L"searchhost.exe" || p == L"searchapp.exe" ||
                 p == L"shellexperiencehost.exe" || p == L"shellhost.exe") shell = true;
        else if (p == L"*") all = true;
        else if (p == L"explorer.exe") explorer = true;
        if (p.rfind(L"windhawk", 0) != 0) tool = false;
    }
    if (dwm || named({L"title bar", L"border", L"corner", L"shadow", L"wobbl"})) return 0;
    if (shell || named({L"taskbar", L"tray", L"start menu", L"start button", L"launchpad"})) return 1;
    if (all) return 2;
    if (explorer) return 3;
    if (m.include.empty()) return 6;
    return tool ? 4 : 5;
}

static void Hub_ReadConfig(HubMod& h, const Js& c) {
    auto list = [&](PCWSTR k) {
        std::vector<std::wstring> v;
        if (const Js* a = c.get(k); a && a->t == Js::Arr)
            for (const Js& e : a->a) v.push_back(Js_Text(&e));
        return v;
    };
    auto flag = [&](PCWSTR k) {
        const Js* b = c.get(k);
        return b && b->t == Js::Bool && b->b;
    };
    h.include = list(L"include");
    h.exclude = list(L"exclude");
    h.incCustom = list(L"includeCustom");
    h.excCustom = list(L"excludeCustom");
    h.logging = flag(L"loggingEnabled");
    h.debugLog = flag(L"debugLoggingEnabled");
    h.customOnly = flag(L"includeExcludeCustomOnly");
    h.critical = flag(L"patternsMatchCriticalSystemProcesses");
    h.updatesOff = Js_Text(c.get(L"updatesDisabledForVersion"));
    h.userScope = Js_Text(c.get(L"userScope"));
    h.nuked = Js_Text(c.get(L"nuked"));
}

static std::wstring Hub_JoinList(const std::vector<std::wstring>& v) {
    std::wstring s;
    for (auto& e : v) s += (s.empty() ? L"" : L"; ") + e;
    return s;
}

// "a; b" or one per line back into a list. Commas stay, since paths can hold them.
static std::vector<std::wstring> Hub_SplitList(std::wstring text) {
    std::vector<std::wstring> out;
    std::replace(text.begin(), text.end(), L';', L'\n');
    std::replace(text.begin(), text.end(), L'|', L'\n');
    size_t start = 0;
    while (start <= text.size()) {
        size_t end = text.find(L'\n', start);
        if (end == std::wstring::npos) end = text.size();
        std::wstring e = text.substr(start, end - start);
        start = end + 1;
        while (!e.empty() && (e.front() == L' ' || e.front() == L'\t' || e.front() == L'\r')) e.erase(0, 1);
        while (!e.empty() && (e.back() == L' ' || e.back() == L'\t' || e.back() == L'\r')) e.pop_back();
        if (!e.empty() && std::find(out.begin(), out.end(), e) == out.end()) out.push_back(e);
    }
    return out;
}

struct HubVal {
    bool str = false;
    std::wstring text;
};

constexpr size_t kHubMaxFields = 1200;  // Hover ids are 1000 + field; links start at 3000.

static struct {
    std::vector<HubMod> mods;
    std::wstring error;
    int searchField = -1, showField = -1, groupField = -1;
    std::wstring show = L"all";  // List filter: all, on, off, update, mine, library, local.
    int groupBy = -1;            // 0 where it's from, 1 what it changes, 2 on or off; -1 not read yet.
    bool stale = false;          // Windhawk changed while the list could not refresh.
    std::wstring sig;            // The list as last read, to tell a real change from an echo.
    int detail = -1;  // Open mod (index into mods), or -1 for the list.
    std::wstring detailId, detailError;
    size_t detailStart = 0;
    bool detailTrunc = false;
    std::map<std::wstring, HubVal> base;  // The open mod's stored settings, flat keys.
    std::wstring filter;
    ULONGLONG removeArmed = 0;
    float listScroll = 0;
    int grpSeq = 0;
    UINT taskbarCreated = 0;
    bool quitting = false, trayOn = false, noTray = false, shownOnce = false;
} g_hub;

static bool Hub_DetailDirty(const SetWindow& w, bool settingsOnly = false) {
    if (g_hub.detail < 0) return false;
    for (size_t i = g_hub.detailStart; i < w.fields.size(); i++)
        if ((!settingsOnly || w.fields[i].hub == 3) && Set_FieldValue(w.fields[i]) != w.fields[i].value) return true;
    return false;
}

static void Hub_ResetView(SetWindow& w) {
    w.focus = -1;
    w.hover = SetHit();
    w.knob.clear();
    w.glow.clear();
}

// Reads the installed mods from Windhawk. Fills err and returns false when the list could not be read.
static bool Hub_ReadMods(std::vector<HubMod>& out, std::wstring& err) {
    out.clear();
    Js data;
    if (!Hub_Cli(L"mod list", data, err)) return false;
    if (const Js* mods = data.get(L"mods"); mods && mods->t == Js::Arr) {
        for (const Js& m : mods->a) {
            HubMod h;
            h.id = Js_Text(m.get(L"id"));
            if (h.id.empty()) continue;
            h.name = Js_Text(m.get(L"name"));
            if (h.name.empty()) h.name = h.id;
            h.version = Js_Text(m.get(L"version"));
            h.author = Js_Text(m.get(L"author"));
            h.desc = Js_Text(m.get(L"description"));
            const Js* en = m.get(L"enabled");
            h.enabled = en && en->t == Js::Bool && en->b;
            const Js* up = m.get(L"updateAvailable");
            h.update = up && up->t == Js::Bool && up->b;
            if (const Js* c = m.get(L"config"); c && c->t == Js::Obj) Hub_ReadConfig(h, *c);
            h.lower = Hub_Lower(h.name + L"\n" + h.id + L"\n" + h.author + L"\n" + h.desc);
            h.src = Hub_ModSource(h);
            h.area = Hub_ModArea(h);
            out.push_back(std::move(h));
        }
    }
    return true;
}

// What the list shows, in one string: a change in Windhawk changes it, a settings-only save does not.
static std::wstring Hub_ModSig(const std::vector<HubMod>& mods) {
    std::vector<std::wstring> rows;
    for (auto& m : mods) rows.push_back(m.id + L"|" + m.version + L"|" + (m.enabled ? L"1" : L"0") + (m.update ? L"u" : L""));
    std::sort(rows.begin(), rows.end());
    std::wstring s;
    for (auto& r : rows) s += r + L"\n";
    return s;
}

// DavidHiFi's feed sorts his mods into a few groups, listed in the order they show. Until the
// feed is read, the groups it carries today. A missing or unknown group shows under "Other".
static const std::vector<std::wstring> kHubDefaultCats = {L"Taskbar", L"Explorer", L"Windows and menus", L"Tools", L"Fixes"};
static std::vector<std::wstring> g_feedCats;
static std::map<std::wstring, std::wstring> g_feedCatOf;  // Mod id to its group in the feed.

static const std::vector<std::wstring>& Hub_CatList() { return g_feedCats.empty() ? kHubDefaultCats : g_feedCats; }

static size_t Hub_CatIndex(const std::wstring& cat) {
    const auto& list = Hub_CatList();
    for (size_t i = 0; i < list.size(); i++)
        if (!cat.empty() && _wcsicmp(list[i].c_str(), cat.c_str()) == 0) return i;
    return list.size();
}

static std::wstring Hub_CatName(size_t i) {
    const auto& list = Hub_CatList();
    return i < list.size() ? list[i] : L"Other";
}

// A mod's group: the feed's word for his mods, a guess from what it loads into for the rest.
static int Hub_ModCat(const HubMod& m) {
    if (auto c = g_feedCatOf.find(m.id); c != g_feedCatOf.end()) return (int)Hub_CatIndex(c->second);
    static const PCWSTR kAreaCat[] = {L"Windows and menus", L"Taskbar", L"Windows and menus", L"Explorer", L"Tools", L"", L""};
    return (int)Hub_CatIndex(kAreaCat[std::clamp(m.area, 0, 6)]);
}

static int Hub_GroupKey(const HubMod& m) {
    if (g_hub.groupBy == 1) return Hub_ModCat(m);
    if (g_hub.groupBy == 2) return m.enabled ? 0 : 1;
    return m.src;
}

// Sorts the mods into their sections and lays out one switch row per mod.
static void Hub_PlaceMods(SetWindow& w) {
    std::map<std::wstring, std::pair<std::wstring, std::wstring>> pending;
    for (const auto& f : w.fields)
        if (f.hub == 1 && Set_FieldValue(f) != f.value)
            pending[f.key] = {f.value, Set_FieldValue(f)};
    size_t end = 0;
    while (end < w.fields.size() && w.fields[end].hub != 1) end++;
    w.fields.resize(end);
    std::stable_sort(g_hub.mods.begin(), g_hub.mods.end(), [](const HubMod& a, const HubMod& b) {
        const int ga = Hub_GroupKey(a), gb = Hub_GroupKey(b);
        if (ga != gb) return ga < gb;
        if (a.enabled != b.enabled) return a.enabled;
        return CompareStringEx(LOCALE_NAME_USER_DEFAULT, LINGUISTIC_IGNORECASE, a.name.c_str(), -1, b.name.c_str(), -1,
                               nullptr, nullptr, 0) == CSTR_LESS_THAN;
    });
    std::map<int, std::pair<int, int>> count;  // Section: mods, of them turned on.
    for (auto& m : g_hub.mods) {
        auto& c = count[Hub_GroupKey(m)];
        c.first++;
        c.second += m.enabled;
    }
    for (size_t i = 0; i < g_hub.mods.size(); i++) {
        const HubMod& m = g_hub.mods[i];
        const int key = Hub_GroupKey(m);
        const auto& c = count[key];
        std::wstring head;
        if (g_hub.groupBy == 2) head = (key == 0 ? L"Turned on (" : L"Turned off (") + std::to_wstring(c.first) + L")";
        else
            head = (g_hub.groupBy == 1 ? Hub_CatName(key) : std::wstring(kHubSrcName[key])) + L" (" +
                   std::to_wstring(c.first) + L", " + std::to_wstring(c.second) + L" on)";
        SetField f{};
        f.kind = SetField::Check;
        f.key = Hub_In(m.id);
        f.label = Hub_In(m.name);
        f.desc = m.desc.empty() ? nullptr : Hub_In(m.desc);
        f.def = L"1";
        f.group = Hub_In(head);
        f.hub = 1;
        f.mod = (int)i;
        f.value = f.cur = m.enabled ? L"1" : L"0";
        if (auto p = pending.find(m.id); p != pending.end()) {
            f.value = p->second.first;
            f.cur = p->second.second;
        }
        w.fields.push_back(f);
    }
}

// Group by changed: sort again without asking Windhawk.
static void Hub_Regroup(SetWindow& w) {
    if (g_hub.detail >= 0 || g_hub.groupField < 0 || g_hub.groupField >= (int)w.fields.size()) return;
    const int by = _wtoi(Set_FieldValue(w.fields[g_hub.groupField]).c_str());
    if (by == g_hub.groupBy) return;
    g_hub.groupBy = by;
    Hub_RegSet(L"Set.modsGroup", by);
    Hub_PlaceMods(w);
    Hub_ResetView(w);
    Set_BuildAndClamp(w);
}

// Test copies only (--new --fill key=value): text boxes of a background window cannot take focus.
static std::vector<std::pair<std::wstring, std::wstring>> g_fill;

static void Hub_LoadList(SetWindow& w, std::vector<HubMod>* fresh = nullptr) {
    Set_CommitEdit(w, false);
    Set_StopRecording(w);
    Set_ClosePopup(w);
    std::wstring search;
    if (g_hub.searchField >= 0 && g_hub.searchField < (int)w.fields.size()) search = w.fields[g_hub.searchField].cur;
    else
        for (auto& [k, v] : g_fill)
            if (k == L"hub.search") search = v;
    if (g_hub.showField >= 0 && g_hub.showField < (int)w.fields.size()) g_hub.show = Set_FieldValue(w.fields[g_hub.showField]);
    if (g_hub.groupField >= 0 && g_hub.groupField < (int)w.fields.size())
        g_hub.groupBy = _wtoi(Set_FieldValue(w.fields[g_hub.groupField]).c_str());
    if (g_hub.groupBy < 0 || g_hub.groupBy > 2) g_hub.groupBy = std::clamp(Hub_RegGet(L"Set.modsGroup", 1), 0, 2);
    size_t app = 0;
    while (app < w.fields.size() && w.fields[app].hub != 1 && w.fields[app].hub != 2) app++;
    w.fields.resize(app);
    g_hub.detail = -1;
    g_hub.detailId.clear();
    g_hub.removeArmed = 0;
    g_hub.error.clear();
    g_hub.stale = false;
    std::wstring err;
    if (fresh) g_hub.mods = std::move(*fresh);
    else if (!Hub_ReadMods(g_hub.mods, err)) g_hub.error = L"Could not read the mod list from Windhawk. " + err;
    g_hub.sig = Hub_ModSig(g_hub.mods);

    SetField s{};
    s.kind = SetField::Text;
    s.key = L"hub.search";
    s.label = L"Find a mod";
    s.desc = L"Type part of a name, an author or a word from the description.";
    s.group = L"Search";
    s.hub = 2;
    s.cur = search;
    g_hub.searchField = (int)w.fields.size();
    w.fields.push_back(s);
    SetField show{};
    show.kind = SetField::Choice;
    show.key = L"hub.show";
    show.label = L"Show";
    show.desc = L"Narrow the list to mods that are on, off, have an update, or come from one place.";
    show.group = L"Search";
    show.hub = 2;
    show.vtype = 1;
    show.def = L"all";
    show.options = {{L"all", L"All mods"},          {L"on", L"Turned on"},
                    {L"off", L"Turned off"},        {L"update", L"Has an update"},
                    {L"mine", L"From DavidHiFi"},   {L"library", L"From the Windhawk library"},
                    {L"local", L"Your own local mods"}};
    Set_PutValue(show, g_hub.show);
    show.value = show.cur;
    g_hub.showField = (int)w.fields.size();
    w.fields.push_back(show);
    SetField group{};
    group.kind = SetField::Choice;
    group.key = L"hub.group";
    group.label = L"Sort into";
    group.desc = L"Split the list by what each mod changes (taskbar, Explorer, windows and menus, tools, fixes), by where it comes from, or by on and off.";
    group.group = L"Search";
    group.hub = 2;
    group.def = L"1";
    group.options = {{L"0", L"Where it comes from"}, {L"1", L"What it changes"}, {L"2", L"On or off"}};
    Set_PutValue(group, std::to_wstring(g_hub.groupBy));
    group.value = group.cur;
    g_hub.groupField = (int)w.fields.size();
    w.fields.push_back(group);
    g_cardsGrid = Hub_RegGet(L"Set.modsView", 1) != 0;
    SetField view{};
    view.kind = SetField::Check;
    view.key = L"hub.view";
    view.label = L"View";
    view.group = L"Search";
    view.hub = 2;
    view.def = L"1";
    view.cur = view.value = g_cardsGrid ? L"1" : L"0";
    w.fields.push_back(view);
    Hub_PlaceMods(w);
    Hub_ResetView(w);
    Set_BuildAndClamp(w);
}

static void Hub_LoadBase(const std::wstring& id) {
    g_hub.base.clear();
    // Stored settings; a mod installed from the command line may have none yet, so fall back
    // to its defaults. A save then writes a complete set either way.
    for (PCWSTR cmd : {L"mod settings get ", L"mod settings defaults "}) {
        Js d;
        std::wstring err;
        if (!Hub_Cli(cmd + Set_QuoteArg(id), d, err)) continue;
        if (const Js* s = d.get(L"settings"); s && s->t == Js::Obj)
            for (size_t i = 0; i < s->keys.size(); i++)
                g_hub.base[s->keys[i]] = {s->a[i].t == Js::Str, Js_Text(&s->a[i])};
        if (!g_hub.base.empty()) break;
    }
}

static int Hub_StoredCount(const std::wstring& full) {
    const std::wstring pre = full + L"[";
    int n = 0;
    for (auto it = g_hub.base.lower_bound(pre); it != g_hub.base.end() && it->first.compare(0, pre.size(), pre) == 0;
         ++it)
        n = std::max(n, _wtoi(it->first.c_str() + pre.size()) + 1);
    return n;
}

static bool Hub_IsHex(const std::wstring& s) {
    UINT32 rgb;
    return Set_ParseHex(s, rgb);
}

static bool Hub_IsInt(const std::wstring& s, long long lo, long long hi) {
    if (s.empty()) return false;
    wchar_t* end = nullptr;
    long long v = wcstoll(s.c_str(), &end, 10);
    return end && *end == 0 && v >= lo && v <= hi;
}

static void Hub_AddField(SetWindow& w, SetField& f, const std::wstring& stored) {
    Set_PutValue(f, stored);
    f.value = Set_FieldValue(f);
    w.fields.push_back(f);
}

// One mod's settings schema (mod show's initialSettings) as rows.
static void Hub_AddSchema(SetWindow& w, const Js& items, const std::wstring& prefix, PCWSTR group, int grp, int depth) {
    if (items.t != Js::Arr || depth > 6) return;
    for (const Js& it : items.a) {
        if (w.fields.size() - g_hub.detailStart >= kHubMaxFields) {
            g_hub.detailTrunc = true;
            return;
        }
        if (it.t != Js::Obj) continue;
        const std::wstring key = Js_Text(it.get(L"key"));
        const Js* v = it.get(L"value");
        if (key.empty() || !v) continue;
        const std::wstring full = prefix + key;
        std::wstring name = Js_Text(it.get(L"name"));
        if (name.empty()) name = key;
        const std::wstring desc = Js_Text(it.get(L"description"));
        auto stored = [&](const std::wstring& k, const std::wstring& def) {
            auto b = g_hub.base.find(k);
            return b != g_hub.base.end() ? b->second.text : def;
        };
        SetField f{};
        f.page = 0;
        f.hub = 3;
        f.grp = grp;
        f.group = group;
        f.desc = desc.empty() ? nullptr : Hub_In(desc);

        if (v->t == Js::Arr) {
            bool objects = !v->a.empty();
            for (const Js& e : v->a)
                if (e.t != Js::Obj || !e.get(L"key")) objects = false;
            if (objects) {  // A nested group of settings.
                Hub_AddSchema(w, *v, full + L".", Hub_In(name), grp, depth + 1);
                continue;
            }
            const int n = Hub_StoredCount(full);
            if (!v->a.empty() && v->a[0].t == Js::Arr) {  // A list of entries, each a group of settings.
                for (int i = 0; i < n; i++)
                    Hub_AddSchema(w, v->a[std::min<size_t>(i, v->a.size() - 1)],
                                  full + L"[" + std::to_wstring(i) + L"].", Hub_In(name + L" " + std::to_wstring(i + 1)),
                                  grp, depth + 1);
                Hub_AddSchema(w, v->a[0], full + L"[" + std::to_wstring(n) + L"].", Hub_In(name + L" (add new)"),
                              ++g_hub.grpSeq, depth + 1);
                continue;
            }
            // A plain list of values.
            const bool numbers = !v->a.empty() && v->a[0].t == Js::Num;
            f.arr = Hub_In(full);
            f.group = Hub_In(name);
            f.vtype = numbers ? 0 : 1;
            f.kind = SetField::Text;
            for (int i = 0; i <= n; i++) {
                if (i == n && numbers) break;
                SetField e = f;
                const std::wstring k = full + L"[" + std::to_wstring(i) + L"]";
                e.key = Hub_In(k);
                e.label = Hub_In(i == n ? name + L" (add new)" : name + L" " + std::to_wstring(i + 1));
                if (i == n) e.desc = L"Type a value here to add one more. An emptied entry is removed on save.";
                else if (i > 0) e.desc = nullptr;
                Hub_AddField(w, e, i == n ? std::wstring() : stored(k, L""));
            }
            continue;
        }

        std::wstring def = Js_Text(v);
        const std::wstring cur = stored(full, def);
        f.key = Hub_In(full);
        f.label = Hub_In(name);
        if (const Js* o = it.get(L"options")) {
            auto add = [&](const Js& obj) {
                for (size_t i = 0; i < obj.keys.size(); i++)
                    f.options.push_back({Hub_In(obj.keys[i]), Hub_In(Js_Text(&obj.a[i]))});
            };
            if (o->t == Js::Obj) add(*o);
            if (o->t == Js::Arr)
                for (const Js& e : o->a)
                    if (e.t == Js::Obj) add(e);
        }
        if (v->t == Js::Bool) {
            f.kind = SetField::Check;
        } else if (!f.options.empty() && (v->t == Js::Str || v->t == Js::Num)) {
            f.kind = SetField::Choice;
            f.vtype = v->t == Js::Str ? 1 : 0;
        } else if (v->t == Js::Num) {
            f.vtype = 0;
            f.kind = SetField::Number;
            const Js *mn = it.get(L"min"), *mx = it.get(L"max");
            f.min = mn ? _wtoi(Js_Text(mn).c_str()) : -1000000000;
            f.max = mx ? _wtoi(Js_Text(mx).c_str()) : 1000000000;
            if (f.min > f.max || !Hub_IsInt(def, f.min, f.max) || !Hub_IsInt(cur, f.min, f.max)) f.kind = SetField::Text;
        } else if (v->t == Js::Str) {
            f.vtype = 1;
            f.kind = Hub_IsHex(def) && Hub_IsHex(cur) ? SetField::Color : SetField::Text;
        } else {
            continue;
        }
        f.def = Hub_In(def);
        Hub_AddField(w, f, cur);
    }
}

// Windhawk's per-mod "Advanced" controls: logging, where it runs, update hold, per-account settings.
static void Hub_AddAdvanced(SetWindow& w, int index) {
    const HubMod& m = g_hub.mods[index];
    auto mk = [&](SetField::Kind kind, PCWSTR key, PCWSTR label, PCWSTR desc, PCWSTR def) {
        SetField f{};
        f.kind = kind;
        f.key = key;
        f.label = label;
        f.desc = desc;
        f.def = def;
        f.group = L"Advanced";
        f.hub = 8;
        f.mod = index;
        f.vtype = 1;
        return f;
    };
    SetField log = mk(SetField::Choice, L"hub.logging", L"Logging",
                      L"Writes this mod's messages to Windhawk's log. Detailed adds its debug messages. Read them in "
                      L"stock Windhawk's log window.",
                      L"0");
    log.options = {{L"0", L"Off"}, {L"1", L"Mod messages"}, {L"2", L"Detailed"}};
    Hub_AddField(w, log, m.debugLog ? L"2" : m.logging ? L"1" : L"0");
    SetField inc = mk(SetField::Text, L"hub.include", L"Also run in",
                      L"Extra programs to load it into, beside its own list. Separate with semicolons, like "
                      L"notepad.exe; C:\\Tools\\*.exe",
                      L"");
    Hub_AddField(w, inc, Hub_JoinList(m.incCustom));
    SetField exc = mk(SetField::Text, L"hub.exclude", L"Never run in",
                      L"Programs it must skip, even when its own list names them. Separate with semicolons.", L"");
    Hub_AddField(w, exc, Hub_JoinList(m.excCustom));
    SetField only = mk(SetField::Check, L"hub.customOnly", L"Use only my lists",
                       L"Ignore the mod's own program list and use only the two lists above.", L"0");
    Hub_AddField(w, only, m.customOnly ? L"1" : L"0");
    SetField crit = mk(SetField::Check, L"hub.critical", L"Let my lists reach system programs",
                       L"Lets a pattern above match critical Windows processes. Leave off unless a mod's author says so.",
                       L"0");
    Hub_AddField(w, crit, m.critical ? L"1" : L"0");
    if (m.id.rfind(L"local@", 0) != 0 && !m.version.empty()) {
        SetField hold = mk(SetField::Check, L"hub.skipUpdate", Hub_In(L"Stay on version " + m.version),
                           L"Windhawk stops offering updates for this mod while this version is installed. Turn off "
                           L"to get updates again.",
                           L"0");
        Hub_AddField(w, hold, !m.updatesOff.empty() && m.updatesOff == m.version ? L"1" : L"0");
    }
    SetField own = mk(SetField::Check, L"hub.userScope", L"Own settings for this Windows account",
                      L"Gives your account its own copy of this mod's settings. Off goes back to the shared ones and "
                      L"keeps your copy for later.",
                      L"0");
    Hub_AddField(w, own, m.userScope == L"active" ? L"1" : L"0");
}

// The changed Advanced controls as windhawk-cli lines.
static void Hub_AdvancedJob(SetWindow& w, std::vector<std::wstring>& job) {
    if (g_hub.detail < 0) return;
    const std::wstring id = Set_QuoteArg(g_hub.detailId);
    auto set = [&](PCWSTR field, const std::vector<std::wstring>& values) {
        std::wstring line = L"mod config set " + id + L" " + field;
        for (auto& v : values) line += L" " + Set_QuoteArg(v);
        job.push_back(line);
    };
    auto tf = [](bool on) { return std::wstring(on ? L"true" : L"false"); };
    for (size_t i = g_hub.detailStart; i < w.fields.size(); i++) {
        const SetField& f = w.fields[i];
        if (f.hub != 8) continue;
        const std::wstring v = Set_FieldValue(f);
        if (v == f.value) continue;
        const std::wstring key = f.key;
        if (key == L"hub.logging") {
            set(L"loggingEnabled", {tf(v != L"0")});
            set(L"debugLoggingEnabled", {tf(v == L"2")});
        } else if (key == L"hub.include") set(L"includeCustom", Hub_SplitList(v));
        else if (key == L"hub.exclude") set(L"excludeCustom", Hub_SplitList(v));
        else if (key == L"hub.customOnly") set(L"includeExcludeCustomOnly", {tf(v == L"1")});
        else if (key == L"hub.critical") set(L"patternsMatchCriticalSystemProcesses", {tf(v == L"1")});
        else if (key == L"hub.skipUpdate")
            set(L"updatesDisabledForVersion", {v == L"1" ? g_hub.mods[g_hub.detail].version : L""});
        else if (key == L"hub.userScope")
            job.push_back(L"mod user-config " + std::wstring(v == L"1" ? L"enable " : L"disable ") + id + L" --yes");
    }
}

static void Hub_CloseDetail(SetWindow& w) {
    if (g_hub.detail < 0) return;
    Set_CommitEdit(w, false);
    Set_StopRecording(w);
    Set_ClosePopup(w);
    w.fields.resize(g_hub.detailStart);
    g_hub.detail = -1;
    g_hub.detailId.clear();
    g_hub.detailError.clear();
    g_hub.removeArmed = 0;
    Hub_ResetView(w);
    w.status.clear();
    w.statusError = false;
    w.pageT = Set_Anim(w) ? 0.0f : 1.0f;
    Set_BuildPage(w);
    w.scrollY = w.scrollTarget = std::clamp(g_hub.listScroll, 0.0f, std::max(0.0f, w.contentH - Set_ViewH(w)));
    Set_BuildAndClamp(w);
}

static bool Hub_OpenDetail(SetWindow& w, const std::wstring& id) {
    int index = -1;
    for (size_t i = 0; i < g_hub.mods.size(); i++)
        if (g_hub.mods[i].id == id) index = (int)i;
    if (index < 0) return false;
    Set_CommitEdit(w, false);
    Set_StopRecording(w);
    Set_ClosePopup(w);
    if (g_hub.detail < 0) g_hub.listScroll = w.scrollTarget;
    else w.fields.resize(g_hub.detailStart);
    w.page = 0;
    g_hub.detail = index;
    g_hub.detailId = id;
    g_hub.detailStart = w.fields.size();
    g_hub.detailError.clear();
    g_hub.detailTrunc = false;
    g_hub.removeArmed = 0;
    g_hub.base.clear();
    Js show;
    std::wstring err;
    if (!Hub_Cli(L"mod show " + Set_QuoteArg(id), show, err)) {
        g_hub.detailError = L"Windhawk could not read this mod's settings. " + err;
    } else {
        Hub_LoadBase(id);
        SetField on{};
        on.kind = SetField::Check;
        on.key = L"hub.enabled";
        on.label = L"Turned on";
        on.desc = L"Windhawk loads this mod while it is on. Off keeps it installed with its settings.";
        on.group = L"Mod";
        on.def = L"1";
        on.hub = 4;
        on.mod = index;
        on.value = on.cur = g_hub.mods[index].enabled ? L"1" : L"0";
        w.fields.push_back(on);
        if (const Js* items = show.get(L"initialSettings")) Hub_AddSchema(w, *items, L"", L"Options", 0, 0);
        Hub_AddAdvanced(w, index);
    }
    Hub_ResetView(w);
    w.status.clear();
    w.statusError = false;
    w.scrollY = w.scrollTarget = 0;
    w.pageT = Set_Anim(w) ? 0.0f : 1.0f;
    Set_BuildAndClamp(w);
    return true;
}

// ---- Engine hooks -----------------------------------------------------------------

static std::wstring Hub_PageTitle(SetWindow& w) {
    if (w.page == 0 && g_hub.detail >= 0) return g_hub.mods[g_hub.detail].name;
    return kSetPages[w.page].name;
}

static std::wstring Hub_PageIntro(SetWindow& w) {
    if (w.page == 0 && g_hub.detail >= 0) {
        const HubMod& m = g_hub.mods[g_hub.detail];
        std::wstring s = L"Version " + m.version;
        if (!m.author.empty()) s += L" by " + m.author;
        s += m.enabled ? L". Turned on." : L". Turned off.";
        if (!m.desc.empty()) s += L" " + m.desc;
        return s;
    }
    if (w.page == 0 && !g_hub.mods.empty())
        return std::to_wstring(g_hub.mods.size()) +
               L" mods installed in Windhawk. Flip a switch to turn one on or off, or click a mod for its settings.";
    return kSetPages[w.page].intro;
}

static std::wstring Hub_Banner(SetWindow& w) {
    if (w.page != 0) return std::wstring();
    if (g_hub.detail < 0) return g_hub.error;
    if (!g_hub.detailError.empty()) return g_hub.detailError;
    for (size_t i = g_hub.detailStart; i < w.fields.size(); i++)
        if (w.fields[i].hub == 3) return std::wstring();
    return L"This mod has no options of its own. Windhawk's controls for it are under Advanced.";
}

static void Hub_AddLink(SetWindow& w, float& y, const std::wstring& text, const std::wstring& sub, PCWSTR url) {
    SetItem it;
    it.type = SetItem::Link;
    it.y = y;
    // Grow with the description: in a narrow window it wraps, and a fixed 56 cut it mid-line.
    it.h = std::max(56.0f, 40 + Set_TextH(w.fHint.get(), sub, w.contentW - kSetRowPad - 50));
    it.text = text;
    it.sub = sub;
    it.url = url;
    y += it.h + kSetRowGap;
    w.items.push_back(it);
}

static void Hub_DetailExtras(SetWindow& w, float& y);   // features.inc
static std::wstring Hub_AppSettingLine(const SetField& f);  // features.inc
static void Hub_WelcomeItems(SetWindow& w, float& y);       // features.inc

static void Hub_ItemsTop(SetWindow& w, float& y) {
    if (w.page != 0) return;
    if (g_hub.detail >= 0) {
        Hub_AddLink(w, y, L"Back to the list", L"All installed mods", L"hub:back");
        y += 6;
        return;
    }
    Hub_WelcomeItems(w, y);
    std::wstring text;
    if (g_hub.searchField >= 0 && g_hub.searchField < (int)w.fields.size()) {
        text = w.editing == g_hub.searchField && w.edit ? Set_WindowText(w.edit) : w.fields[g_hub.searchField].cur;
    }
    while (!text.empty() && text.back() == L' ') text.pop_back();
    while (!text.empty() && text.front() == L' ') text.erase(0, 1);
    g_hub.filter = Hub_Lower(text);
    // "Sort into" changed: sort again once this layout pass is over.
    if (g_hub.groupField >= 0 && g_hub.groupField < (int)w.fields.size() && w.hwnd &&
        _wtoi(w.fields[g_hub.groupField].cur.c_str()) != g_hub.groupBy)
        PostMessageW(w.hwnd, WM_HUB_REGROUP, 0, 0);
}

static bool Hub_Show(SetWindow& w, const SetField& f) {
    if (f.hub == 8) return w.page == 0 && g_hub.detail >= 0;
    if (f.hub == 0 || f.hub >= 5) return f.page == w.page;
    if (w.page != 0) return false;
    if (g_hub.detail >= 0) return f.hub == 3 || f.hub == 4;
    if (f.hub == 2) return true;
    if (f.hub == 1) {
        const HubMod& m = g_hub.mods[f.mod];
        std::wstring show = L"all";
        if (g_hub.showField >= 0 && g_hub.showField < (int)w.fields.size()) show = w.fields[g_hub.showField].cur;
        if ((show == L"on" && !m.enabled) || (show == L"off" && m.enabled) || (show == L"update" && !m.update) ||
            (show == L"mine" && m.src != 0) || (show == L"library" && m.src != 1) || (show == L"local" && m.src != 2))
            return false;
        return g_hub.filter.empty() || m.lower.find(g_hub.filter) != std::wstring::npos;
    }
    return false;
}

static void Hub_ItemsBottom(SetWindow& w, float& y) {
    if (w.page != 0) { Hub_FeatureItems(w, y); return; }
    auto banner = [&](const std::wstring& text) {
        SetItem it;
        it.type = SetItem::Banner;
        it.text = text;
        it.y = y + 6;
        it.h = Set_TextH(w.fHint.get(), text, w.contentW - 32) + 28;
        y = it.y + it.h + kSetRowGap;
        w.items.push_back(it);
    };
    if (g_hub.detail < 0) {
        bool any = false;
        for (auto& f : w.fields) any = any || (f.hub == 1 && Hub_Show(w, f));
        if (!any && !g_hub.mods.empty())
            banner(g_hub.filter.empty() ? std::wstring(L"No mod fits this view. Set Show to All mods.")
                                        : L"No mod matches “" + g_hub.filter + L"”.");
        return;
    }
    if (g_hub.detailTrunc) banner(L"This mod has more settings than fit here. The rest keep their values.");
    Hub_DetailExtras(w, y);
    SetItem g;
    g.type = SetItem::Group;
    g.text = L"Remove";
    g.y = y + 14;
    g.h = 22;
    y = g.y + g.h + 6;
    w.items.push_back(g);
    const HubMod& m = g_hub.mods[g_hub.detail];
    if (g_hub.removeArmed && GetTickCount64() - g_hub.removeArmed < 5000)
        Hub_AddLink(w, y, L"Click again to remove " + m.name, L"This cannot be undone. Its settings go with it.",
                    L"hub:remove");
    else
        Hub_AddLink(w, y, L"Remove this mod", L"Uninstalls it from Windhawk. Its settings go with it.", L"hub:remove");
}

static WCHAR Hub_LinkGlyph(const std::wstring& url) {
    if (url == L"hub:back") return 0xE72B;
    if (url == L"hub:remove") return 0xE74D;
    return 0xE8A7;
}

// Windhawk's own settings (7) are left out: "reset" here means this app and the open mod.
static bool Hub_Resettable(SetWindow& w, SetField& f) {
    return (f.hub == 0 || f.hub == 3 || f.hub == 6 || f.hub == 8) && Hub_Show(w, f);
}

static bool Hub_LeaveDetail(SetWindow& w, bool& left) {
    if (g_hub.detail < 0) return true;
    if (Hub_DetailDirty(w)) {
        Set_SetStatus(w, L"Save or cancel this mod's changes first.", true);
        return false;
    }
    Hub_CloseDetail(w);
    left = true;
    return true;
}

static bool Hub_Link(PCWSTR url) {
    if (wcsncmp(url, L"hub:", 4) != 0) return false;
    if (g_setWin && g_setWin->hwnd) {
        auto action = new std::wstring(url);
        if (!PostMessageW(g_setWin->hwnd, WM_HUB_ACTION, 0, (LPARAM)action)) delete action;
    }
    return true;
}

static void Hub_Back(SetWindow& w) {
    Set_CommitEdit(w, true);
    bool left = false;
    Hub_LeaveDetail(w, left);
}

static void Hub_Cancel(SetWindow& w) {
    Set_CommitEdit(w, false);
    Set_StopRecording(w);
    Set_ClosePopup(w);
    if (Set_ChangedCount(w) > 0) {
        for (auto& f : w.fields)
            if (f.hub != 2) f.cur = f.value;
        Set_SetStatus(w, L"Changes discarded");
        return;
    }
    if (g_hub.detail >= 0) {
        Hub_CloseDetail(w);
        return;
    }
    PostMessageW(w.hwnd, WM_CLOSE, 0, 0);
}

static void Hub_Escape(SetWindow& w) {
    if (w.page == 0 && g_hub.detail >= 0) {
        Hub_Back(w);
        return;
    }
    if (w.page == 0 && g_hub.searchField >= 0 && !w.fields[g_hub.searchField].cur.empty()) {
        w.fields[g_hub.searchField].cur.clear();
        Set_BuildAndClamp(w);
    }
}

static void Hub_InitFields(SetWindow& w) { Hub_FeatureFields(w); Hub_LoadList(w); }

// ---- Applying changes (elevated helper) ----------------------------------------------

static std::wstring Hub_DataDir() {
    PWSTR p = nullptr;
    std::wstring dir;
    if (SUCCEEDED(SHGetKnownFolderPath(FOLDERID_LocalAppData, 0, nullptr, &p))) dir = p;
    CoTaskMemFree(p);
    const std::wstring old = dir + L"\\SeamlessHub";
    dir += L"\\SeamlessWorkshop";
    if (CreateDirectoryW(dir.c_str(), nullptr)) {  // First time: bring the old presets along.
        CreateDirectoryW((dir + L"\\presets").c_str(), nullptr);
        WIN32_FIND_DATAW fd;
        HANDLE f = FindFirstFileW((old + L"\\presets\\*.json").c_str(), &fd);
        if (f != INVALID_HANDLE_VALUE) {
            do {
                if (!(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
                    CopyFileW((old + L"\\presets\\" + fd.cFileName).c_str(),
                              (dir + L"\\presets\\" + fd.cFileName).c_str(), TRUE);
            } while (FindNextFileW(f, &fd));
            FindClose(f);
        }
    }
    return dir;
}

static bool Hub_WriteFile(const std::wstring& path, const std::string& data) {
    HANDLE h = CreateFileW(path.c_str(), GENERIC_WRITE, 0, nullptr, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);
    if (h == INVALID_HANDLE_VALUE) return false;
    DWORD put = 0;
    bool ok = WriteFile(h, data.data(), (DWORD)data.size(), &put, nullptr) && put == data.size();
    CloseHandle(h);
    return ok;
}

static bool Hub_ReadFile(const std::wstring& path, std::string& data) {
    HANDLE h = CreateFileW(path.c_str(), GENERIC_READ, FILE_SHARE_READ, nullptr, OPEN_EXISTING, 0, nullptr);
    if (h == INVALID_HANDLE_VALUE) return false;
    LARGE_INTEGER size{};
    if (!GetFileSizeEx(h, &size) || size.QuadPart < 0 || size.QuadPart > (64 << 20)) {
        CloseHandle(h); return false;
    }
    data.resize((size_t)size.QuadPart);
    DWORD got = 0;
    bool ok = data.empty() || (ReadFile(h, data.data(), (DWORD)data.size(), &got, nullptr) && got == data.size());
    CloseHandle(h);
    return ok;
}

static std::vector<std::wstring> Hub_Lines(const std::wstring& text) {
    std::vector<std::wstring> lines;
    size_t start = 0;
    while (start <= text.size()) {
        size_t end = text.find(L'\n', start);
        if (end == std::wstring::npos) end = text.size();
        std::wstring line = text.substr(start, end - start);
        if (!line.empty() && line.back() == L'\r') line.pop_back();
        if (!line.empty()) lines.push_back(line);
        start = end + 1;
    }
    return lines;
}

// The elevated side: runs each line of the job file through windhawk-cli, stops at the first
// failure, writes "<code><TAB><message>" per line to <job>.out.
static int Hub_Apply(const std::wstring& job) {
    std::string raw;
    if (!Hub_ReadFile(job, raw)) return 2;
    std::string out;
    for (const std::wstring& line : Hub_Lines(Hub_Wide(raw))) {
        Js data;
        std::wstring err;
        if (Hub_Cli(line, data, err)) {
            out += "0\t\n";
            continue;
        }
        std::replace(err.begin(), err.end(), L'\n', L' ');
        std::replace(err.begin(), err.end(), L'\r', L' ');
        out += "1\t" + Hub_Utf8(err) + "\n";
        break;
    }
    return Hub_WriteFile(job + L".out", out) ? 0 : 3;
}

static bool Hub_Elevated() {
    HANDLE token;
    TOKEN_ELEVATION e{};
    DWORD n = 0;
    bool elevated = false;
    if (OpenProcessToken(GetCurrentProcess(), TOKEN_QUERY, &token)) {
        if (GetTokenInformation(token, TokenElevation, &e, sizeof(e), &n)) elevated = e.TokenIsElevated != 0;
        CloseHandle(token);
    }
    return elevated;
}

// One mod's share of a long job, named for the progress line.
struct HubBlock {
    std::wstring name;
    std::vector<std::wstring> lines;
};

static void Hub_FitSettingsFile(const std::wstring& line);

#ifdef HUB_MOD
// A line that changes the Workshop itself (turn off, remove, update) would end this process,
// so those run last, after the window has shown the result. Its own settings are safe.
static bool Hub_SelfLine(const std::wstring& l) {
    if (l.find(L"@selfinstall ") == 0) return true;
    return l.find(kHubSelfId) != std::wstring::npos && l.find(L"mod settings set ") != 0 &&
           l.find(L"mod settings write ") != 0;
}

// The tool mod already runs with admin rights, so each line goes straight to windhawk-cli on
// a worker thread while the window keeps painting.
// Blocks: one per mod. Without "failed", the first refused line stops the whole job (the usual
// way). With it, a refused line skips only the rest of its block, the block's index is added to
// "failed", and the next block runs, so one bad mod never stops a setup of 180. A line holding a
// tab is a first choice and a fallback: the part after the tab runs when the first is refused.
static bool Hub_RunBlocks(SetWindow& w, const std::vector<HubBlock>& blocks, std::wstring& err,
                          std::vector<size_t>* failed = nullptr) {
    std::vector<HubBlock> now;
    std::vector<std::wstring> last;
    for (auto& b : blocks) {
        HubBlock keep{b.name, {}};
        for (auto& l : b.lines) (Hub_SelfLine(l) ? last : keep.lines).push_back(l);
        now.push_back(std::move(keep));
    }
    struct Run {
        HANDLE done = CreateEventW(nullptr, TRUE, FALSE, nullptr);
        std::mutex lock;
        std::wstring err, name;
        std::vector<size_t> failed;
        std::atomic<size_t> step = 0;
        bool ok = true;
        ~Run() { if (done) CloseHandle(done); }
    };
    auto run = std::make_shared<Run>();
    if (!run->done) { err = L"Could not start the change."; return false; }
    w.saving = true;
    Set_SetStatus(w, L"Saving…");
    ULONGLONG budget = 20000;
    for (auto& b : now)
        for (auto& l : b.lines)
            budget += (Hub_LongCli(l) ? 310000 : l.find(L"mod settings write ") == 0 ? 30000 : 15000) *
                      (l.find(L'\t') != std::wstring::npos ? 2 : 1);
    const bool keepGoing = failed != nullptr;
    std::thread worker([run, now, keepGoing] {
        for (size_t i = 0; i < now.size(); i++) {
            { std::lock_guard<std::mutex> g(run->lock); run->name = now[i].name; }
            run->step = i + 1;
            for (const std::wstring& line : now[i].lines) {
                Js data;
                std::wstring e;
                const size_t tab = line.find(L'\t');
                if (line.find(L"mod settings write ") == 0) Hub_FitSettingsFile(line.substr(0, tab));
                bool ok = Hub_Cli(line.substr(0, tab), data, e);
                if (!ok && tab != std::wstring::npos) { e.clear(); ok = Hub_Cli(line.substr(tab + 1), data, e); }
                if (!ok) {
                    std::lock_guard<std::mutex> g(run->lock);
                    if (run->err.empty())
                        run->err = (now[i].name.empty() ? L"" : now[i].name + L": ") + (e.empty() ? L"Windhawk refused the change." : e);
                    run->ok = false;
                    run->failed.push_back(i);
                    break;
                }
            }
            if (!run->ok && !keepGoing) break;
        }
        SetEvent(run->done);
    });
    const ULONGLONG deadline = GetTickCount64() + budget;
    bool quit = false, finished = false;
    int quitCode = 0;
    size_t shown = 0;
    for (;;) {
        DWORD r = MsgWaitForMultipleObjects(1, &run->done, FALSE, 100, QS_ALLINPUT);
        if (r == WAIT_OBJECT_0) { finished = true; break; }
        if (GetTickCount64() > deadline) break;
        // A long job says where it is: "Step 37 of 181: Taskbar Styler".
        if (now.size() > 3 && run->step != shown) {
            shown = run->step;
            std::wstring name;
            { std::lock_guard<std::mutex> g(run->lock); name = run->name; }
            const std::wstring text = L"Step " + std::to_wstring(shown) + L" of " + std::to_wstring(now.size()) +
                                      (name.empty() ? L"" : L": " + name) + L". You can keep using the window.";
            Set_SetStatus(w, text.c_str());
        }
        MSG m;
        while (PeekMessageW(&m, nullptr, 0, 0, PM_REMOVE)) {
            if (m.message == WM_QUIT) {
                quit = true;
                quitCode = (int)m.wParam;
                break;
            }
            TranslateMessage(&m);
            DispatchMessageW(&m);
        }
        if (quit) break;
    }
    if (finished) worker.join();
    else worker.detach();  // Each windhawk-cli call ends itself on its own deadline.
    w.saving = false;
    if (quit) PostQuitMessage(quitCode);
    if (!finished) {
        err = L"Windhawk did not finish in time. Some changes may have been applied.";
        return false;
    }
    if (!run->ok) {
        err = run->err;
        if (failed) *failed = run->failed;
        return false;
    }
    if (!last.empty())
        std::thread([last] {
            Sleep(1500);
            for (const std::wstring& line : last) {
                Js data;
                std::wstring e;
                if (!Hub_Cli(line, data, e)) break;
            }
        }).detach();
    return true;
}

static bool Hub_RunJob(SetWindow& w, const std::vector<std::wstring>& lines, std::wstring& err) {
    return Hub_RunBlocks(w, {HubBlock{L"", lines}}, err);
}
#else
// Runs CLI command lines through the elevated helper while the window keeps painting.
static bool Hub_RunJob(SetWindow& w, const std::vector<std::wstring>& lines, std::wstring& err) {
    const std::wstring job = Hub_DataDir() + L"\\job-" + std::to_wstring(GetCurrentProcessId()) + L"-" +
                             std::to_wstring(GetTickCount64()) + L".txt";
    const std::wstring out = job + L".out";
    std::wstring text;
    for (auto& l : lines) text += l + L"\n";
    if (!Hub_WriteFile(job, Hub_Utf8(text))) {
        err = L"Could not write the change list to disk.";
        return false;
    }
    WCHAR self[MAX_PATH];
    GetModuleFileNameW(nullptr, self, MAX_PATH);
    const std::wstring params = L"--apply " + Set_QuoteArg(job);
    SHELLEXECUTEINFOW sei{sizeof(sei)};
    sei.fMask = SEE_MASK_NOCLOSEPROCESS | SEE_MASK_FLAG_NO_UI;
    sei.hwnd = w.hwnd;
    sei.lpVerb = Hub_Elevated() ? L"open" : L"runas";
    sei.lpFile = self;
    sei.lpParameters = params.c_str();
    sei.nShow = SW_HIDE;
    if (!ShellExecuteExW(&sei) || !sei.hProcess) {
        DeleteFileW(job.c_str());
        err = L"Changing mods needs admin rights, and Windows did not give them.";
        return false;
    }
    w.saving = true;
    Set_SetStatus(w, L"Saving…");
    ULONGLONG budget = 20000;
    for (auto& l : lines) budget += Hub_LongCli(l) ? 310000 : 15000;
    const ULONGLONG deadline = GetTickCount64() + budget;
    bool quit = false;
    int quitCode = 0;
    for (;;) {
        DWORD r = MsgWaitForMultipleObjects(1, &sei.hProcess, FALSE, 100, QS_ALLINPUT);
        if (r == WAIT_OBJECT_0 || GetTickCount64() > deadline) break;
        MSG m;
        while (PeekMessageW(&m, nullptr, 0, 0, PM_REMOVE)) {
            if (m.message == WM_QUIT) {
                quit = true;
                quitCode = (int)m.wParam;
                break;
            }
            TranslateMessage(&m);
            DispatchMessageW(&m);
        }
        if (quit) break;
    }
    if (WaitForSingleObject(sei.hProcess, 0) != WAIT_OBJECT_0) {
        TerminateProcess(sei.hProcess, 1);
        WaitForSingleObject(sei.hProcess, 1000);
    }
    CloseHandle(sei.hProcess);
    w.saving = false;
    if (quit) PostQuitMessage(quitCode);
    std::string raw;
    bool read = Hub_ReadFile(out, raw);
    DeleteFileW(job.c_str());
    DeleteFileW(out.c_str());
    if (!read) {
        err = L"Windhawk did not finish in time. Some changes may have been applied.";
        return false;
    }
    std::vector<std::wstring> results = Hub_Lines(Hub_Wide(raw));
    for (auto& r : results) {
        if (r.size() >= 2 && r[0] == L'1') {
            err = r.substr(2);
            if (err.empty()) err = L"Windhawk refused the change.";
            return false;
        }
    }
    if (results.size() < lines.size()) {
        err = L"Windhawk stopped before every change was made.";
        return false;
    }
    return true;
}

// The standalone build runs every block in one admin run and stops at the first refusal. A
// fallback after a tab is dropped here: the elevated helper takes one command per line.
static bool Hub_RunBlocks(SetWindow& w, const std::vector<HubBlock>& blocks, std::wstring& err,
                          std::vector<size_t>* failed = nullptr) {
    std::vector<std::wstring> lines;
    for (auto& b : blocks)
        for (auto& l : b.lines) lines.push_back(l.substr(0, l.find(L'\t')));
    const bool ok = Hub_RunJob(w, lines, err);
    if (!ok && failed) failed->clear();
    return ok;
}
#endif

static bool Hub_IsNumber(const std::wstring& s) {
    Js value;
    return Js_Parse(s, value) && value.t == Js::Num;
}

// The open mod's whole settings set, edits laid over what is stored, as a flat-key JSON file.
static bool Hub_WriteSettingsFile(SetWindow& w, const std::wstring& path) {
    std::map<std::wstring, HubVal> out = g_hub.base;
    auto put = [&](const SetField& f, const std::wstring& key, const std::wstring& v) {
        out[key] = {f.vtype == 1 || (f.kind == SetField::Text && !Hub_IsNumber(v)), v};
    };
    std::set<int> grps;
    std::set<std::wstring> arrs;
    for (size_t i = g_hub.detailStart; i < w.fields.size(); i++) {
        const SetField& f = w.fields[i];
        if (f.hub != 3 || Set_FieldValue(f) == f.value) continue;
        if (f.arr) arrs.insert(f.arr);
        else if (f.grp > 0) grps.insert(f.grp);
        else put(f, f.key, Set_FieldValue(f));
    }
    for (size_t i = g_hub.detailStart; i < w.fields.size(); i++) {  // A new entry is written whole.
        const SetField& f = w.fields[i];
        if (!f.arr && f.grp > 0 && grps.count(f.grp)) put(f, f.key, Set_FieldValue(f));
    }
    for (const std::wstring& arr : arrs) {  // A changed plain list is written again in order, gaps closed.
        const std::wstring pre = arr + L"[";
        for (auto it = out.lower_bound(pre); it != out.end() && it->first.compare(0, pre.size(), pre) == 0;)
            it = out.erase(it);
        int n = 0;
        for (size_t i = g_hub.detailStart; i < w.fields.size(); i++) {
            const SetField& f = w.fields[i];
            if (!f.arr || arr != f.arr) continue;
            std::wstring v = Set_FieldValue(f);
            if (v.empty()) continue;
            put(f, pre + std::to_wstring(n++) + L"]", v);
        }
    }
    std::wstring json = L"{";
    bool first = true;
    for (auto& [k, v] : out) {
        if (!first) json += L",";
        first = false;
        json += L"\n  " + Js_Quote(k) + L": " + (v.str || !Hub_IsNumber(v.text) ? Js_Quote(v.text) : v.text);
    }
    json += L"\n}\n";
    return Hub_WriteFile(path, Hub_Utf8(json));
}

static void Hub_TrayUpdate(SetWindow& w);

#ifdef HUB_MOD
// Kept in step with the shared settings template (settings-engine.py checks it). The Workshop's
// own Set_Save builds its "mod settings set" line itself.
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
#endif

static void Set_Save(std::shared_ptr<SetWindow> keep) {
    SetWindow& w = *keep;
    if (w.saving || !w.hwnd) return;
    Set_CommitEdit(w, true);
    Set_StopRecording(w);
    Set_ClosePopup(w);
    // 1. This window's own settings: no admin rights needed.
    bool app = false;
    std::wstring selfSet;  // Mod build: the window settings are the mod's own Windhawk settings.
    for (auto& f : w.fields) {
        if ((f.hub != 0 && f.hub != 6) || Set_FieldValue(f) == f.value) continue;
        if (f.hub == 6) {
            if (!Hub_SetText(std::wstring(L"Set.") + f.key, f.cur)) {
                Set_SetStatus(w, L"Could not save the app setting.", true); return;
            }
            f.value = f.cur; app = true; continue;
        }
        f.cur = f.value = Set_FieldValue(f);
#ifdef HUB_MOD
        selfSet += std::wstring(L" ") + f.key + L"=" + std::to_wstring(_wtoi(f.value.c_str()));
#else
        Hub_RegSet(std::wstring(L"Set.") + f.key, _wtoi(f.value.c_str()));
#endif
        app = true;
    }
    if (app) {
        g_settings.animations = Set_FieldOn(w, L"animations", true);
        Set_ApplyFrame(w);
        Hub_TrayUpdate(w);
        Hub_Presence();
    }
    // 2. Mods: switches, then the open mod's settings, in one elevated run.
    std::vector<std::wstring> job;
    if (!selfSet.empty()) job.push_back(std::wstring(L"mod settings set ") + kHubSelfId + selfSet);
    bool whApp = false;  // Windhawk's own settings (page 5): "wh.<key>", or "wh!<key>" when shown inverted.
    for (auto& f : w.fields) {
        if (f.hub != 7 || Set_FieldValue(f) == f.value) continue;
        job.push_back(Hub_AppSettingLine(f));
        whApp = true;
    }
    for (auto& f : w.fields)
        if ((f.hub == 1 || f.hub == 4) && Set_FieldValue(f) != f.value)
            job.push_back((f.cur == L"1" ? L"mod enable " : L"mod disable ") + Set_QuoteArg(g_hub.mods[f.mod].id));
    const size_t beforeAdvanced = job.size();
    Hub_AdvancedJob(w, job);
    const bool advanced = job.size() > beforeAdvanced;
    std::wstring settingsFile;
    if (Hub_DetailDirty(w, true)) {
        settingsFile = Hub_DataDir() + L"\\settings-" + std::to_wstring(GetTickCount64()) + L".json";
        if (!Hub_WriteSettingsFile(w, settingsFile)) {
            Set_SetStatus(w, L"Could not write the settings to disk.", true);
            return;
        }
        job.push_back(L"mod settings write " + Set_QuoteArg(g_hub.detailId) + L" " + Set_QuoteArg(settingsFile));
    }
    if (job.empty()) {
        Set_SetStatus(w, app ? L"Saved" : L"Nothing changed");
        return;
    }
    std::wstring err;
    std::vector<std::wstring> changed;
    for (auto& f : w.fields) if ((f.hub == 1 || f.hub == 4) && Set_FieldValue(f) != f.value)
        changed.push_back(g_hub.mods[f.mod].id);
    if (!settingsFile.empty() || advanced) changed.push_back(g_hub.detailId);
    if (!changed.empty() && !Hub_Backup(changed, err)) {
        if (!settingsFile.empty()) DeleteFileW(settingsFile.c_str());
        Set_SetStatus(w, err.c_str(), true); return;
    }
    bool ok = Hub_RunJob(w, job, err);
    if (!settingsFile.empty()) DeleteFileW(settingsFile.c_str());
    if (!keep->hwnd) return;
    if (!ok) {
        Set_SetStatus(w, err.c_str(), true);
        return;
    }
    if (whApp)
        for (auto& f : w.fields)
            if (f.hub == 7) f.cur = f.value = Set_FieldValue(f);
    const std::wstring id = g_hub.detailId;
    const float scroll = w.scrollTarget, listScroll = g_hub.listScroll;
    Hub_LoadList(w);
    if (!id.empty()) Hub_OpenDetail(w, id);
    g_hub.listScroll = listScroll;
    w.pageT = 1;
    Set_BuildPage(w);
    w.scrollY = w.scrollTarget = std::clamp(scroll, 0.0f, std::max(0.0f, w.contentH - Set_ViewH(w)));
    Set_BuildAndClamp(w);
    Set_SetStatus(w, L"Saved");
}

static void Hub_RemoveClick(SetWindow& w) {
    if (g_hub.detail < 0) return;
    const ULONGLONG now = GetTickCount64();
    const HubMod& m = g_hub.mods[g_hub.detail];
    if (!g_hub.removeArmed || now - g_hub.removeArmed > 5000) {
        g_hub.removeArmed = now;
        SetTimer(w.hwnd, kHubArmTimer, 5050, nullptr);
        Set_BuildAndClamp(w);
        return;
    }
    g_hub.removeArmed = 0;
    const std::wstring id = m.id, name = m.name;
    std::wstring err;
    if (!Hub_Backup({id}, err)) { Set_SetStatus(w, err.c_str(), true); return; }
    if (!Hub_RunJob(w, {L"mod remove " + Set_QuoteArg(id) + L" --yes"}, err)) {
        Set_BuildAndClamp(w);
        Set_SetStatus(w, err.c_str(), true);
        return;
    }
    const float listScroll = g_hub.listScroll;
    Hub_LoadList(w);
    w.pageT = Set_Anim(w) ? 0.0f : 1.0f;
    Set_BuildPage(w);
    w.scrollY = w.scrollTarget = std::clamp(listScroll, 0.0f, std::max(0.0f, w.contentH - Set_ViewH(w)));
    Set_BuildAndClamp(w);
    Set_SetStatus(w, (L"Removed " + name).c_str());
}

// Windows remembers a pinned tray icon by program path and icon id. Every tool mod runs
// as windhawk-mod.exe, so each one needs its own id or pinning one moves them all.
#ifndef WH_MOD_ID
#define WH_MOD_ID L"local@seamless-workshop"  // the test exe build
#endif
static UINT TrayIconId() {
    UINT hash = 2166136261u;
    for (PCWSTR p = WH_MOD_ID; *p; p++) hash = (hash ^ (UINT)*p) * 16777619u;
    return hash | 0x80000000u;
}

static std::wstring Hub_LiveText(SetWindow& w, PCWSTR key);
// ---- features.inc (inlined) ----
// App pages share the Launchpad controls and material.
static std::thread g_reader;
static std::atomic<bool> g_reading = false;
static Js g_readData;
static std::wstring g_readError, g_readKind, g_featureStatus, g_repoDetail;
static std::vector<HubMod> g_repo;
static std::wstring g_repoId, g_repoReadme, g_engineStatus;
static HANDLE g_discord = INVALID_HANDLE_VALUE;
// Public id of the "Seamless Workshop" Discord app. Not a secret: Discord shows it to everyone.
static constexpr PCWSTR kDiscordAppId = L"1573117909683798127";
static std::wstring g_discordId;
static std::string g_discordBuffer;
static bool g_discordReady = false;
static ULONGLONG g_discordSent = 0, g_discordRetry = 0;
static std::wstring Hub_JsDump(const Js& j);
// Staged install guard: the file's hash at the last passing Check. Install refuses a changed file.
static std::wstring g_checkedPath, g_checkedSha, g_checkedId, g_checkPendingPath, g_checkPendingSha;
// Mod page extras: published versions, the "click again" resets, and whose page the status belongs to.
static std::vector<std::pair<std::wstring, bool>> g_versions;
static std::wstring g_statusFor;
static ULONGLONG g_resetArmed = 0, g_restoreArmed = 0, g_setupArmed = 0, g_removeAllArmed = 0;
// Whole backups (Settings page).
static std::wstring g_exportFile, g_restorePending, g_restoreFile;
// DavidHiFi's update feed: his own mods and new versions of this app.
// A mod may carry DavidHiFi's own settings as a preset: on/off plus text or number values.
struct HubFeedMod {
    std::wstring id, name, version, desc, url, sha, changes;  // changes: what is new in this version, one line.
    std::wstring category;  // The group it shows under, such as "Taskbar". Empty: "Other".
    bool hasPreset = false, presetOn = false;
    Js preset;  // Flat object: setting name to text or number.
    // Optional custom app lists from the preset's "config": which apps the mod loads into.
    bool hasConfig = false, customOnly = false;
    std::vector<std::wstring> includeCustom, excludeCustom;
};
// The Windhawk library mods DavidHiFi runs (the feed's "library"), for the whole-setup copy.
// Same fields: no url or sha, the id is a library id, version pins what he has.
static std::vector<HubFeedMod> g_feedLib;
static ULONGLONG g_fullArmed = 0;
static bool g_fullArmedConfig = false;
constexpr WCHAR kHubFeedUrl[] = L"https://raw.githubusercontent.com/DavidHiFi/seamless-workshop/main/feed.json";
constexpr UINT_PTR kHubFeedTimer = 0x4857;
static std::thread g_feedThread;
static std::atomic<bool> g_feedBusy = false;
static std::string g_feedRaw;
static std::wstring g_feedErr, g_feedStatus, g_feedUrlOverride;
static std::vector<HubFeedMod> g_feed;
static HubFeedMod g_feedApp;
static bool g_feedChecked = false;

static std::wstring Hub_Sha256Data(const std::string& raw);
static std::wstring Hub_Sha256(const std::wstring& path) {
    std::string raw;
    if (!Hub_ReadFile(path, raw)) return {};
    return Hub_Sha256Data(raw);
}

static std::wstring Hub_Sha256Data(const std::string& raw) {
    BCRYPT_ALG_HANDLE alg = nullptr; BCRYPT_HASH_HANDLE h = nullptr;
    UCHAR digest[32]; std::wstring hex;
    if (BCryptOpenAlgorithmProvider(&alg, BCRYPT_SHA256_ALGORITHM, nullptr, 0) != 0) return {};
    if (BCryptCreateHash(alg, &h, nullptr, 0, nullptr, 0, 0) == 0) {
        if (BCryptHashData(h, (PUCHAR)raw.data(), (ULONG)raw.size(), 0) == 0 && BCryptFinishHash(h, digest, 32, 0) == 0)
            for (UCHAR b : digest) { wchar_t t[3]; swprintf(t, 3, L"%02x", b); hex += t; }
        BCryptDestroyHash(h);
    }
    BCryptCloseAlgorithmProvider(alg, 0);
    return hex;
}

// Lists same-user apps that hold the mod's engine DLL. Apps this account cannot read are counted, not named.
static bool Hub_WhereLoaded(const std::wstring& id, Js& data, std::wstring& err) {
    const std::wstring prefix = Hub_Lower(id) + L"_";
    HANDLE procs = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (procs == INVALID_HANDLE_VALUE) { err = L"Could not list running apps."; return false; }
    std::wstring apps; int found = 0, skipped = 0;
    const ULONGLONG deadline = GetTickCount64() + 20000;
    PROCESSENTRY32W pe{sizeof(pe)};
    for (BOOL more = Process32FirstW(procs, &pe); more && GetTickCount64() < deadline; more = Process32NextW(procs, &pe)) {
        if (pe.th32ProcessID <= 4) continue;
        HANDLE mods = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, pe.th32ProcessID);
        if (mods == INVALID_HANDLE_VALUE) { skipped++; continue; }
        MODULEENTRY32W me{sizeof(me)};
        for (BOOL m = Module32FirstW(mods, &me); m; m = Module32NextW(mods, &me)) {
            const auto name = Hub_Lower(me.szModule), path = Hub_Lower(me.szExePath);
            if (name.rfind(prefix, 0) == 0 && path.find(L"\\windhawk\\engine\\mods\\") != std::wstring::npos) {
                if (found++) apps += L",";
                apps += Js_Quote(std::wstring(pe.szExeFile) + L" (" + std::to_wstring(pe.th32ProcessID) + L")");
                break;
            }
        }
        CloseHandle(mods);
    }
    CloseHandle(procs);
    return Js_Parse(L"{\"id\":" + Js_Quote(id) + L",\"apps\":[" + apps + L"],\"unreadable\":" + std::to_wstring(skipped) + L"}", data);
}

// The workspace release checklist (AGENTS.md), read from the installed source.
static bool Hub_ReleaseCheck(const std::wstring& id, Js& data, std::wstring& err) {
    std::string raw;
    if (!Hub_ReadFile(L"C:\\ProgramData\\Windhawk\\ModsSource\\" + id + L".wh.cpp", raw)) { err = L"Installed source was not found."; return false; }
    const auto src = Hub_Wide(raw);
    auto line = [&](PCWSTR tag) {
        const auto at = src.find(std::wstring(L"// ") + tag + L" ");
        if (at == std::wstring::npos) return std::wstring();
        auto end = src.find(L'\n', at); auto v = src.substr(at + wcslen(tag) + 4, end - at - wcslen(tag) - 4);
        while (!v.empty() && (v.front() == L' ' || v.front() == L'\t')) v.erase(0, 1);
        while (!v.empty() && (v.back() == L'\r' || v.back() == L' ')) v.pop_back();
        return v;
    };
    const auto readme = src.find(L"==WindhawkModReadme==");
    const std::pair<PCWSTR, bool> checks[] = {
        {L"Author starts with DavidHiFi", line(L"@author").rfind(L"DavidHiFi", 0) == 0},
        {L"Ko-fi donate link", line(L"@donateUrl").find(L"ko-fi.com/DavidHiFi") != std::wstring::npos},
        {L"Id has no local@ prefix", !line(L"@id").empty() && line(L"@id").find(L"local@") == std::wstring::npos},
        {L"Name, description and version", !line(L"@name").empty() && !line(L"@description").empty() && !line(L"@version").empty()},
        {L"Readme present", readme != std::wstring::npos},
        {L"Preview image in readme", readme != std::wstring::npos && src.find(L"![", readme) != std::wstring::npos},
    };
    std::wstring list; bool first = true;
    for (auto& [name, ok] : checks) {
        if (!first) list += L","; first = false;
        list += L"{\"name\":" + Js_Quote(name) + L",\"ok\":" + (ok ? L"true" : L"false") + L"}";
    }
    return Js_Parse(L"{\"id\":" + Js_Quote(id) + L",\"checks\":[" + list + L"]}", data);
}

static bool Hub_GlassCheck(Js& data, std::wstring& err) {
    std::string out;
    if (!Hub_RunCli(L"@glass", out)) { err = L"The glass check did not finish."; return false; }
    std::wstring lines; bool first = true;
    for (auto& l : Hub_Lines(Hub_Wide(out))) { if (!first) lines += L","; first = false; lines += Js_Quote(l); }
    return Js_Parse(L"{\"lines\":[" + lines + L"]}", data);
}

static std::wstring Hub_RegText(const std::wstring& key) {
    DWORD bytes = 0;
    if (RegGetValueW(HKEY_CURRENT_USER, kHubKey, key.c_str(), RRF_RT_REG_SZ, nullptr, nullptr, &bytes) != ERROR_SUCCESS ||
        bytes > 65536 || bytes < sizeof(WCHAR)) return {};
    std::wstring s(bytes / sizeof(WCHAR), 0);
    if (RegGetValueW(HKEY_CURRENT_USER, kHubKey, key.c_str(), RRF_RT_REG_SZ, nullptr, s.data(), &bytes) != ERROR_SUCCESS)
        return {};
    s.resize(wcsnlen(s.c_str(), s.size()));
    return s;
}

static bool Hub_SetText(const std::wstring& name, const std::wstring& value) {
    HKEY key;
    if (RegCreateKeyExW(HKEY_CURRENT_USER, kHubKey, 0, nullptr, 0, KEY_SET_VALUE, nullptr, &key, nullptr) != ERROR_SUCCESS)
        return false;
    const LONG r = RegSetValueExW(key, name.c_str(), 0, REG_SZ, (const BYTE*)value.c_str(),
                                (DWORD)((value.size() + 1) * sizeof(WCHAR)));
    RegCloseKey(key);
    return r == ERROR_SUCCESS;
}

static SetField* Hub_Field(SetWindow& w, PCWSTR key) {
    for (auto& f : w.fields) if (wcscmp(f.key, key) == 0) return &f;
    return nullptr;
}

static std::wstring Hub_Input(SetWindow& w, PCWSTR key) {
    auto f = Hub_Field(w, key);
    return f ? f->cur : L"";
}

// Windhawk's own settings, as "app settings get" names them. "wh!" marks a switch shown the other
// way round from how Windhawk stores it (it stores "disable X", the window shows "X").
struct HubWhSetting {
    PCWSTR key, label, desc, group;
    SetField::Kind kind;
    int min = 0, max = 0;
    std::vector<std::pair<PCWSTR, PCWSTR>> options = {};
};

static const std::vector<HubWhSetting>& Hub_WhSettings() {
    static const std::vector<std::pair<PCWSTR, PCWSTR>> logs = {{L"0", L"None"}, {L"1", L"Errors"}, {L"2", L"Everything"}};
    static const std::vector<std::pair<PCWSTR, PCWSTR>> waits = {
        {L"0", L"Right away"}, {L"1000", L"1 second"}, {L"2000", L"2 seconds"}, {L"5000", L"5 seconds"}, {L"10000", L"10 seconds"}};
    static const std::vector<HubWhSetting> list = {
        {L"wh!disableUpdateCheck", L"Check for Windhawk updates", L"Windhawk looks for new versions of itself and your library mods.", L"Windhawk", SetField::Check},
        {L"wh.hideTrayIcon", L"Hide Windhawk's tray icon", L"Windhawk keeps running. This app keeps its own icon.", L"Windhawk", SetField::Check},
        {L"wh!disableRunUIScheduledTask", L"Open Windhawk without an admin prompt", nullptr, L"Windhawk", SetField::Check},
        {L"wh.theme", L"Windhawk's own window", nullptr, L"Windhawk", SetField::Choice, 0, 0, {{L"dark", L"Dark"}, {L"light", L"Light"}}},
        {L"wh.language", L"Windhawk language", L"A language code, like en, de or fr.", L"Windhawk", SetField::Text},
        {L"wh.modTasksDialogDelay", L"Show mod progress after", L"How long a mod has to be loading or compiling before its progress box shows.", L"Windhawk", SetField::Choice, 0, 0, waits},
        {L"wh!devModeOptOut", L"Developer tools in Windhawk", nullptr, L"Advanced", SetField::Check},
        {L"wh.alwaysCompileModsLocally", L"Always compile mods on this PC", L"Skips ready-made builds from the library.", L"Advanced", SetField::Check},
        {L"wh!dontAutoShowToolkit", L"Show the toolkit when something goes wrong", nullptr, L"Advanced", SetField::Check},
        {L"wh!disableToolkitHotkey", L"Toolkit shortcut", L"Ctrl+Win+Alt+W opens the Windhawk toolkit.", L"Advanced", SetField::Check},
        {L"wh.loggingVerbosity", L"Windhawk log detail", nullptr, L"Advanced", SetField::Choice, 0, 0, logs},
        {L"wh.engine.loggingVerbosity", L"Mod loader log detail", nullptr, L"Advanced", SetField::Choice, 0, 0, logs},
        {L"wh.engine.injectIntoGames", L"Load mods into games", L"Anti-cheat can flag this.", L"Advanced", SetField::Check},
        {L"wh.engine.injectIntoIncompatiblePrograms", L"Load mods into programs known to clash", nullptr, L"Advanced", SetField::Check},
        {L"wh.engine.injectIntoCriticalProcesses", L"Load mods into critical system processes", L"Risky. A broken mod there can stop Windows starting.", L"Advanced", SetField::Check},
        {L"wh.engine.include", L"Always load mods into", L"Program names, separated by semicolons.", L"Advanced", SetField::Text},
        {L"wh.engine.exclude", L"Never load mods into", L"Program names, separated by semicolons.", L"Advanced", SetField::Text},
    };
    return list;
}

static std::wstring Hub_AppSettingLine(const SetField& f) {
    const std::wstring key = f.key + 3;
    const bool invert = f.key[2] == L'!';
    std::wstring value = Set_FieldValue(f);
    if (f.kind == SetField::Check) {
        value = ((value == L"1") != invert) ? L"true" : L"false";
    } else if (key == L"engine.include" || key == L"engine.exclude") {
        std::wstring joined;
        for (auto& e : Hub_SplitList(value)) joined += (joined.empty() ? L"" : L",") + e;
        value = joined;
    }
    return L"app settings set " + key + L" " + Set_QuoteArg(value);
}

static void Hub_WhFields(SetWindow& w) {
    Js data; std::wstring err;
    if (!Hub_Cli(L"app settings get", data, err)) return;
    const Js* root = data.get(L"settings");
    if (!root || root->t != Js::Obj) return;
    for (auto& s : Hub_WhSettings()) {
        const Js* v = root;
        std::wstring path = s.key + 3;
        for (size_t at = 0; v && at <= path.size();) {
            size_t dot = path.find(L'.', at);
            if (dot == std::wstring::npos) dot = path.size();
            v = v->get(path.substr(at, dot - at).c_str());
            at = dot + 1;
        }
        if (!v) continue;
        SetField f{};
        f.kind = s.kind; f.key = s.key; f.label = s.label; f.desc = s.desc; f.group = s.group;
        f.page = 5; f.hub = 7; f.min = s.min; f.max = s.max; f.options = s.options; f.def = L"";
        std::wstring cur;
        if (v->t == Js::Arr) {
            std::vector<std::wstring> items;
            for (auto& e : v->a) items.push_back(Js_Text(&e));
            cur = Hub_JoinList(items);
        } else {
            cur = Js_Text(v);
        }
        if (s.kind == SetField::Check) cur = ((cur == L"1") != (s.key[2] == L'!')) ? L"1" : L"0";
        if (s.kind == SetField::Choice) {
            bool known = false;
            for (auto& o : f.options) known |= cur == o.first;
            if (!known) f.options.push_back({Hub_In(cur), Hub_In(cur)});
        }
        f.cur = f.value = cur;
        w.fields.push_back(f);
    }
}

static void Hub_FeatureFields(SetWindow& w) {
    auto add = [&](int page, PCWSTR key, PCWSTR name, PCWSTR desc, PCWSTR group, int kind = 5) {
        SetField f{};
        f.kind = SetField::Text; f.page = page; f.key = key; f.label = name; f.desc = desc;
        f.group = group; f.hub = kind; f.def = L"";
        f.cur = f.value = kind == 6 ? Hub_RegText(std::wstring(L"Set.") + key) : L"";
        for (auto& [k, v] : g_fill) if (k == key) f.cur = v;
        w.fields.push_back(f);
    };
    add(1, L"hub.marketSearch", L"Find a mod", nullptr, L"Library");
    SetField mshow{};
    mshow.kind = SetField::Choice; mshow.key = L"hub.marketShow"; mshow.label = L"Show"; mshow.group = L"Library";
    mshow.page = 1; mshow.hub = 5; mshow.vtype = 1; mshow.def = L"all";
    mshow.options = {{L"all", L"Everything"}, {L"new", L"Not installed"}, {L"mine", L"From DavidHiFi"}};
    mshow.cur = mshow.value = L"all";
    w.fields.push_back(mshow);
    SetField mview{};
    mview.kind = SetField::Check; mview.key = L"hub.marketView"; mview.label = L"View"; mview.group = L"Library";
    mview.page = 1; mview.hub = 5; mview.def = L"1";
    mview.cur = mview.value = Hub_RegGet(L"Set.modsView", 1) ? L"1" : L"0";
    w.fields.push_back(mview);
    add(3, L"hub.presetName", L"Preset name", L"Letters, numbers, spaces and hyphens. Saving never overwrites a preset.", L"Save a preset");
    add(3, L"hub.presetMods", L"Mods to save", L"Comma-separated mod ids. Only these mods are included. Copy an id from a mod's page.", L"Save a preset");
    add(4, L"hub.devId", L"Installed mod id", L"Use the id shown in the mod's source. Compile is available only while the mod is off.", L"Installed source");
    add(4, L"hub.devPath", L"Staged source file", L"Full path to a .wh.cpp source file. Check reads it without installing.", L"Staged source");
    SetField feed{};
    feed.kind = SetField::Check; feed.key = L"feedCheck"; feed.label = L"Check for updates every day";
    feed.desc = L"For DavidHiFi's mods and this app. Nothing installs without you.";
    feed.def = L"1"; feed.group = L"Seamless Workshop"; feed.page = 5;
    feed.cur = feed.value = Hub_AppInt(L"feedCheck", 1) ? L"1" : L"0";
    w.fields.push_back(feed);
    SetField presence{};
    presence.kind = SetField::Check; presence.key = L"discordPresence"; presence.label = L"Show on Discord";
    presence.desc = L"Your Discord profile shows that you are using Seamless Workshop.";
    presence.def = L"0"; presence.group = L"Seamless Workshop"; presence.page = 5;
    presence.cur = presence.value = Hub_AppInt(L"discordPresence", 0) ? L"1" : L"0";
    w.fields.push_back(presence);
    Hub_WhFields(w);
}

static void Hub_Notice(SetWindow& w, float& y, const std::wstring& text) {
    if (text.empty()) return;
    SetItem it; it.type = SetItem::Banner; it.text = text; it.y = y;
    it.h = Set_TextH(w.fHint.get(), text, w.contentW - 32) + 28;
    y += it.h + kSetRowGap; w.items.push_back(it);
}

static bool Hub_ValidId(const std::wstring& id) {
    return !id.empty() && id.size() < 200 && id.find_first_not_of(L"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789-_.@") == std::wstring::npos;
}

static bool Hub_PresetName(const std::wstring& name) {
    return !name.empty() && name.size() <= 60 && name.front() != L' ' && name.back() != L' ' &&
           name.find_first_not_of(L"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789 -_") == std::wstring::npos;
}

static bool Hub_Newer(const std::wstring& available, const std::wstring& installed) {
    auto parts = [](const std::wstring& version) {
        std::vector<unsigned> result;
        unsigned value = 0; bool digit = false;
        for (wchar_t c : version + L".") {
            if (c == L'.' && digit) { result.push_back(value); value = 0; digit = false; }
            else if (c >= L'0' && c <= L'9' && value < 1000000) { value = value * 10 + c - L'0'; digit = true; }
            else return std::vector<unsigned>{};
        }
        while (!result.empty() && result.back() == 0) result.pop_back();
        return result;
    };
    auto a = parts(available), b = parts(installed);
    if (a.empty() || b.empty()) return false;
    a.resize(std::max(a.size(), b.size())); b.resize(a.size());
    return a > b;
}

static std::wstring Hub_PresetDir() {
    auto dir = Hub_DataDir() + L"\\presets";
    CreateDirectoryW(dir.c_str(), nullptr); return dir;
}

static std::vector<std::wstring> Hub_Presets() {
    std::vector<std::wstring> names;
    WIN32_FIND_DATAW fd{};
    HANDLE h = FindFirstFileW((Hub_PresetDir() + L"\\*.json").c_str(), &fd);
    if (h == INVALID_HANDLE_VALUE) return names;
    do {
        if (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) continue;
        std::wstring n = fd.cFileName; n.resize(n.size() - 5);
        if (Hub_PresetName(n)) names.push_back(n);
    } while (FindNextFileW(h, &fd));
    FindClose(h); std::sort(names.begin(), names.end()); return names;
}

static void Hub_Group(SetWindow& w, float& y, const std::wstring& text) {
    SetItem g;
    g.type = SetItem::Group; g.text = text; g.y = y + 14; g.h = 22;
    y = g.y + g.h + 6;
    w.items.push_back(g);
}

static const HubMod* Hub_FindMod(const std::wstring& id) {
    for (auto& m : g_hub.mods) if (m.id == id) return &m;
    return nullptr;
}

// ---- DavidHiFi's update feed -----------------------------------------------------------

static std::wstring Hub_FeedUrl() {
    if (!g_feedUrlOverride.empty()) return g_feedUrlOverride;
    auto url = Hub_RegText(L"Set.feedUrl");
    return url.empty() ? std::wstring(kHubFeedUrl) : url;
}

// A feed on disk (a test, or a mirror) may point at files on disk. A web feed may only use https.
static bool Hub_FeedLocal() { return Hub_FeedUrl().rfind(L"https://", 0) != 0; }

static bool Hub_Download(const std::wstring& url, std::string& out, std::wstring& err, DWORD* status = nullptr) {
    out.clear();
    if (status) *status = 0;
    if (url.rfind(L"https://", 0) != 0) {
        if (!Hub_FeedLocal()) { err = L"The feed named an address that is not secure. Nothing was downloaded."; return false; }
        if (!Hub_ReadFile(url, out)) { err = L"Could not read " + url + L"."; return false; }
        return true;
    }
    URL_COMPONENTS uc{sizeof(uc)};
    WCHAR host[256]{}, path[2048]{}, extra[1024]{};
    uc.lpszHostName = host; uc.dwHostNameLength = 256;
    uc.lpszUrlPath = path; uc.dwUrlPathLength = 2048;
    uc.lpszExtraInfo = extra; uc.dwExtraInfoLength = 1024;
    if (url.size() > 3000 || !WinHttpCrackUrl(url.c_str(), 0, 0, &uc) || uc.nScheme != INTERNET_SCHEME_HTTPS) {
        err = L"The feed named an address that could not be read."; return false;
    }
    const std::wstring target = std::wstring(path) + extra;
    bool ok = false;
    HINTERNET s = WinHttpOpen(L"SeamlessWorkshop", WINHTTP_ACCESS_TYPE_AUTOMATIC_PROXY, WINHTTP_NO_PROXY_NAME, WINHTTP_NO_PROXY_BYPASS, 0);
    HINTERNET c = nullptr, r = nullptr;
    if (s) {
        WinHttpSetTimeouts(s, 10000, 10000, 15000, 30000);
        c = WinHttpConnect(s, host, uc.nPort, 0);
    }
    if (c) r = WinHttpOpenRequest(c, L"GET", target.c_str(), nullptr, WINHTTP_NO_REFERER, WINHTTP_DEFAULT_ACCEPT_TYPES, WINHTTP_FLAG_SECURE);
    if (r && WinHttpSendRequest(r, WINHTTP_NO_ADDITIONAL_HEADERS, 0, WINHTTP_NO_REQUEST_DATA, 0, 0, 0) &&
        WinHttpReceiveResponse(r, nullptr)) {
        DWORD code = 0, size = sizeof(code);
        WinHttpQueryHeaders(r, WINHTTP_QUERY_STATUS_CODE | WINHTTP_QUERY_FLAG_NUMBER, WINHTTP_HEADER_NAME_BY_INDEX, &code, &size, WINHTTP_NO_HEADER_INDEX);
        if (status) *status = code;
        if (code != 200) {
            err = L"GitHub answered with code " + std::to_wstring(code) + L".";
        } else {
            ok = true;
            for (;;) {
                DWORD avail = 0, got = 0;
                if (!WinHttpQueryDataAvailable(r, &avail)) { ok = false; break; }
                if (!avail) break;
                if (out.size() + avail > (64u << 20)) { ok = false; err = L"The download is too big."; break; }
                const size_t at = out.size();
                out.resize(at + avail);
                if (!WinHttpReadData(r, out.data() + at, avail, &got)) { ok = false; break; }
                out.resize(at + got);
            }
            if (!ok && err.empty()) err = L"The download stopped partway.";
        }
    } else {
        err = L"Could not reach GitHub. Check the internet connection.";
    }
    if (r) WinHttpCloseHandle(r);
    if (c) WinHttpCloseHandle(c);
    if (s) WinHttpCloseHandle(s);
    if (!ok) out.clear();
    return ok;
}

static bool Hub_FeedVersion(const std::wstring& v) {
    return !v.empty() && v.size() < 40 && v.front() != L'.' && v.find_first_not_of(L"0123456789.") == std::wstring::npos;
}

// Optional "preset": {"enabled": bool, "settings": {name: text|number}, "config": {...}}. A bad
// preset is dropped; the mod itself still counts. A bad config is dropped on its own.
static void Hub_FeedPreset(const Js& j, HubFeedMod& m) {
    const Js* p = j.get(L"preset");
    if (!p || p->t != Js::Obj) return;
    const Js *on = p->get(L"enabled"), *settings = p->get(L"settings");
    bool flat = settings && settings->t == Js::Obj && settings->a.size() <= 2000;
    if (flat)
        for (auto& v : settings->a) flat &= v.t == Js::Str || v.t == Js::Num;
    if (!on || on->t != Js::Bool || !flat) return;
    m.hasPreset = true;
    m.presetOn = on->b;
    m.preset = *settings;
    const Js* c = p->get(L"config");
    if (!c || c->t != Js::Obj) return;
    // Each entry is an app name or pattern such as "explorer.exe" or "*\\steam\\*". Quotes, line
    // breaks and the list separator never belong in one.
    auto list = [](const Js* a, std::vector<std::wstring>& out) {
        if (!a) return true;
        if (a->t != Js::Arr || a->a.size() > 200) return false;
        for (auto& e : a->a) {
            if (e.t != Js::Str || e.s.empty() || e.s.size() > 260 || e.s.find_first_of(L"\"|\r\n") != std::wstring::npos)
                return false;
            out.push_back(e.s);
        }
        return true;
    };
    HubFeedMod t;
    const Js* only = c->get(L"includeExcludeCustomOnly");
    if (!list(c->get(L"includeCustom"), t.includeCustom) || !list(c->get(L"excludeCustom"), t.excludeCustom) ||
        (only && only->t != Js::Bool))
        return;
    m.hasConfig = true;
    m.customOnly = only && only->b;
    m.includeCustom = std::move(t.includeCustom);
    m.excludeCustom = std::move(t.excludeCustom);
}

// One "library" entry: a Windhawk library id (never local@), a plain version and a preset.
static bool Hub_FeedLibEntry(const Js& j, HubFeedMod& m) {
    m.id = Js_Text(j.get(L"id")); m.name = Js_Text(j.get(L"name")); m.version = Js_Text(j.get(L"version"));
    if (m.id.empty() || m.id.size() > 100 || m.id.find(L'@') != std::wstring::npos || !Hub_ValidId(m.id)) return false;
    if (!m.version.empty() && !Hub_FeedVersion(m.version)) m.version.clear();
    if (m.name.empty()) m.name = m.id;
    if (m.name.size() > 80) m.name.resize(80);
    Hub_FeedPreset(j, m);
    return true;
}

static bool Hub_FeedEntry(const Js& j, HubFeedMod& m, bool app) {
    m.id = Js_Text(j.get(L"id")); m.name = Js_Text(j.get(L"name")); m.version = Js_Text(j.get(L"version"));
    m.desc = Js_Text(j.get(L"description")); m.url = Js_Text(j.get(L"url")); m.sha = Hub_Lower(Js_Text(j.get(L"sha256")));
    if (!app && (m.id.rfind(L"local@", 0) != 0 || m.id.size() < 7 || !Hub_ValidId(m.id))) return false;
    if (!Hub_FeedVersion(m.version) || m.sha.size() != 64 || m.sha.find_first_not_of(L"0123456789abcdef") != std::wstring::npos) return false;
    if (m.url.rfind(L"https://", 0) != 0 && !Hub_FeedLocal()) return false;
    if (m.url.empty() || m.url.size() > 2048) return false;
    if (m.name.empty()) m.name = app ? L"Seamless Workshop" : m.id.substr(6);
    if (m.name.size() > 80) m.name.resize(80);
    if (m.desc.size() > 300) m.desc.resize(300);
    m.changes = Js_Text(j.get(L"changes"));
    if (m.changes.size() > 300) m.changes.resize(300);
    m.category = Js_Text(j.get(L"category"));
    if (m.category.size() > 40) m.category.clear();
    if (!app) Hub_FeedPreset(j, m);
    return true;
}

static bool Hub_ParseFeed(std::string raw, std::vector<HubFeedMod>& mods, HubFeedMod& app, std::wstring& err,
                          std::vector<std::wstring>* cats = nullptr, std::vector<HubFeedMod>* lib = nullptr) {
    mods.clear(); app = {};
    if (cats) cats->clear();
    if (lib) lib->clear();
    if (raw.rfind("\xEF\xBB\xBF", 0) == 0) raw.erase(0, 3);
    Js j;
    const std::wstring format = Js_Parse(Hub_Wide(raw), j) && j.t == Js::Obj ? Js_Text(j.get(L"format")) : L"";
    if (format != L"seamless-workshop-feed-1" && format != L"seamless-hub-feed-1") {
        err = L"The update feed is in a format this version does not understand."; return false;
    }
    if (const Js* list = j.get(L"mods"); list && list->t == Js::Arr) {
        std::set<std::wstring> seen;
        for (auto& e : list->a) {
            HubFeedMod m;
            // The Workshop updates itself through "app", never as one of the mods.
            if (mods.size() < 300 && e.t == Js::Obj && Hub_FeedEntry(e, m, false) && m.id != kHubSelfId &&
                seen.insert(m.id).second)
                mods.push_back(m);
        }
    }
    if (const Js* a = j.get(L"app"); a && a->t == Js::Obj && !Hub_FeedEntry(*a, app, true)) app = {};
    if (const Js* list = j.get(L"library"); lib && list && list->t == Js::Arr) {
        std::set<std::wstring> seen;
        for (auto& e : list->a) {
            HubFeedMod m;
            if (lib->size() < 500 && e.t == Js::Obj && Hub_FeedLibEntry(e, m) && seen.insert(m.id).second)
                lib->push_back(m);
        }
    }
    // The groups, in the order the lists show them. Odd entries are skipped.
    if (const Js* list = j.get(L"categories"); cats && list && list->t == Js::Arr)
        for (auto& e : list->a) {
            const std::wstring c = e.t == Js::Str ? e.s : L"";
            if (c.empty() || c.size() > 40 || cats->size() >= 20 || _wcsicmp(c.c_str(), L"Other") == 0) continue;
            bool dup = false;
            for (auto& have : *cats) dup |= _wcsicmp(have.c_str(), c.c_str()) == 0;
            if (!dup) cats->push_back(c);
        }
    return true;
}

// Feed mods under one heading per group, in the feed's order, then "Other". Empty groups stay hidden.
template <class Want, class Emit>
static void Hub_FeedByCat(SetWindow& w, float& y, Want want, Emit emit) {
    std::vector<std::vector<const HubFeedMod*>> parts(Hub_CatList().size() + 1);
    for (auto& f : g_feed)
        if (want(f)) parts[Hub_CatIndex(f.category)].push_back(&f);
    for (size_t i = 0; i < parts.size(); i++) {
        if (parts[i].empty()) continue;
        Hub_Group(w, y, Hub_CatName(i) + L" (" + std::to_wstring(parts[i].size()) + L")");
        for (auto* f : parts[i]) emit(*f);
    }
}

static void Hub_TrayBalloon(SetWindow& w, const std::wstring& title, const std::wstring& text) {
    if (!g_hub.trayOn) return;
    NOTIFYICONDATAW nid{};
    nid.cbSize = sizeof(nid); nid.hWnd = w.hwnd; nid.uID = TrayIconId(); nid.uFlags = NIF_INFO;
    nid.dwInfoFlags = NIIF_INFO | NIIF_RESPECT_QUIET_TIME;
    wcsncpy_s(nid.szInfoTitle, title.c_str(), _TRUNCATE);
    wcsncpy_s(nid.szInfo, text.c_str(), _TRUNCATE);
    Shell_NotifyIconW(NIM_MODIFY, &nid);
}

static void Hub_FeedStart(HWND hwnd, bool manual) {
    if (g_feedBusy) return;
    if (g_feedThread.joinable()) g_feedThread.join();
    g_feedBusy = true;
    g_feedStatus = L"Checking DavidHiFi's feed...";
    const std::wstring url = Hub_FeedUrl();
    g_feedThread = std::thread([hwnd, manual, url] {
        std::string raw; std::wstring err; DWORD status = 0;
        if (!Hub_Download(url, raw, err, &status) && status == 404) err = L"The update feed is not online yet.";
        g_feedRaw = std::move(raw); g_feedErr = err;
        PostMessageW(hwnd, WM_HUB_FEED, manual ? 1 : 0, 0);
    });
}

static bool Hub_AppNewer() { return !g_feedApp.version.empty() && Hub_Newer(g_feedApp.version, WH_MOD_VERSION); }

static void Hub_FeedResult(SetWindow& w, bool manual) {
    if (g_feedThread.joinable()) g_feedThread.join();
    g_feedBusy = false;
    std::wstring err = g_feedErr;
    std::vector<HubFeedMod> mods; HubFeedMod app;
    std::vector<std::wstring> cats;
    std::vector<HubFeedMod> lib;
    if (err.empty()) Hub_ParseFeed(g_feedRaw, mods, app, err, &cats, &lib);
    g_feedRaw.clear();
    if (!err.empty()) {
        g_feedStatus = err;
    } else {
        g_feed = std::move(mods); g_feedApp = app; g_feedChecked = true;
        g_feedCats = std::move(cats);
        g_feedLib = std::move(lib);
        g_feedCatOf.clear();
        for (auto& f : g_feed) g_feedCatOf[f.id] = f.category;
        // The Mods page sorted by group before the feed's words were known: sort again.
        if (w.page == 0 && g_hub.detail < 0 && g_hub.groupBy == 1) Hub_PlaceMods(w);
        std::wstring keys, first, firstChanges;
        int updates = 0, missing = 0;
        for (auto& f : g_feed) {
            const HubMod* m = Hub_FindMod(f.id);
            if (!m) { missing++; continue; }
            if (!Hub_Newer(f.version, m->version)) continue;
            if (!updates++) { first = f.name + L" " + f.version; firstChanges = f.changes; }
            keys += f.id + L"=" + f.version + L";";
        }
        if (Hub_AppNewer()) keys += L"app=" + g_feedApp.version + L";";
        g_feedStatus = updates ? std::to_wstring(updates) + (updates == 1 ? L" update" : L" updates") + L" from DavidHiFi."
                               : L"Your mods from DavidHiFi are up to date.";
        if (missing) g_feedStatus += L" " + std::to_wstring(missing) + L" more of his mods are not installed yet.";
        const std::wstring seen = L";" + Hub_RegText(L"Set.feedSeen");
        bool fresh = false;
        for (size_t at = 0; at < keys.size();) {
            const size_t end = keys.find(L';', at);
            fresh |= seen.find(L";" + keys.substr(at, end - at + 1)) == std::wstring::npos;
            at = end + 1;
        }
        if (fresh && !manual) {
            std::wstring text = updates == 1 ? first + L" is ready."
                              : updates ? std::to_wstring(updates) + L" of your mods have new versions."
                                        : L"";
            if (Hub_AppNewer()) text += (text.empty() ? L"" : L" ") + std::wstring(L"Seamless Workshop ") + g_feedApp.version + L" is ready.";
            text += L" Open the Updates page to install.";
            // One update: say what changed, so the user can decide from the tray.
            const std::wstring& news = updates == 1 && !Hub_AppNewer() ? firstChanges
                                     : !updates && Hub_AppNewer() ? g_feedApp.changes : std::wstring();
            if (!news.empty()) text += L" New: " + news;
            Hub_TrayBalloon(w, L"Updates from DavidHiFi", text);
        }
        Hub_SetText(L"Set.feedSeen", keys);
    }
    // The lists that show feed cards rebuild when it lands; a detail view keeps its scroll.
    if (w.page == 2 || (w.page == 0 && g_hub.detail < 0) || (w.page == 1 && g_repoId.empty())) Set_BuildAndClamp(w);
}

// ---- DavidHiFi's settings ---------------------------------------------------------------
// Nothing private travels in a preset: a setting whose name looks like a key, token, password
// or account id is never written, and neither is a value that looks like one. The user's own
// value for such a setting stays as it is.

// A setting name in lower-case words. Dots, list marks, _ - / and spaces split it, and so does
// each capital that starts a word: "accounts[0].apiKey" is accounts, api, key. Matching whole
// words keeps shortcuts ("hotkeyCenter", "toggleKey", "keyboardSounds") out of the private list.
static std::vector<std::wstring> Hub_KeyWords(const std::wstring& key) {
    std::wstring s;
    for (size_t i = 0; i < key.size(); i++) {
        if (key[i] == L'[') {
            const size_t end = key.find(L']', i);
            if (end != std::wstring::npos && key.find_first_not_of(L"0123456789", i + 1) == end) { s += L' '; i = end; continue; }
        }
        const wchar_t c = key[i];
        if (iswupper(c) && i > 0) {
            const wchar_t p = key[i - 1];
            const bool nextLower = i + 1 < key.size() && iswlower(key[i + 1]);
            if (iswlower(p) || iswdigit(p) || (iswupper(p) && nextLower)) s += L' ';
        }
        s += c;
    }
    std::vector<std::wstring> words;
    std::wstring cur;
    for (wchar_t c : s) {
        if (c == L' ' || c == L'.' || c == L'_' || c == L'-' || c == L'/' || c == L'\t') {
            if (!cur.empty()) words.push_back(cur), cur.clear();
        } else {
            cur += (wchar_t)towlower(c);
        }
    }
    if (!cur.empty()) words.push_back(cur);
    return words;
}

// The same word lists the publisher scrubs presets with, so what he leaves out and what the
// Workshop keeps as yours line up. Plain "key" counts only as the whole last part of a name.
static bool Hub_SecretKey(const std::wstring& key) {
    static const std::set<std::wstring> words = {
        L"token", L"tokens", L"secret", L"secrets", L"password", L"passwords", L"passwd", L"pwd", L"passphrase",
        L"apikey", L"apikeys", L"webhook", L"webhooks", L"auth", L"oauth", L"bearer", L"cookie", L"cookies",
        L"credential", L"credentials", L"clientid", L"appsecret", L"privatekey", L"accesskey",
        L"location", L"city", L"latitude", L"longitude", L"lat", L"lon", L"lng", L"zip", L"zipcode", L"postcode",
        L"postal", L"address", L"email", L"username", L"phone", L"country", L"street", L"placename", L"geo"};
    static const std::set<std::pair<std::wstring, std::wstring>> pairs = {
        {L"api", L"key"}, {L"client", L"id"}, {L"client", L"secret"}, {L"application", L"id"}, {L"user", L"name"},
        {L"place", L"name"}, {L"access", L"key"}, {L"secret", L"key"}, {L"private", L"key"}, {L"license", L"key"},
        {L"subscription", L"key"}, {L"auth", L"key"}, {L"zip", L"code"}, {L"post", L"code"}, {L"e", L"mail"},
        {L"session", L"key"}, {L"refresh", L"token"}, {L"access", L"token"}, {L"sync", L"peers"}};
    static const std::set<std::pair<std::wstring, std::wstring>> safe = {
        {L"taskbar", L"location"}, {L"target", L"location"}, {L"detect", L"location"}, {L"address", L"bar"},
        {L"country", L"display"}, {L"password", L"screen"}, {L"location", L"secondary"}};
    const auto w = Hub_KeyWords(key);
    for (size_t i = 0; i + 1 < w.size(); i++)
        if (safe.count({w[i], w[i + 1]})) return false;
    bool discord = false;
    for (size_t i = 0; i < w.size(); i++) {
        if (words.count(w[i])) return true;
        if (i + 1 < w.size() && pairs.count({w[i], w[i + 1]})) return true;
        if (w[i] == L"discord") discord = true;
        else if (discord && w[i] == L"id") return true;  // A Discord account, server or app id.
    }
    std::wstring last = key;
    while (!last.empty() && last.back() == L']') last.pop_back();
    if (const size_t at = last.find_last_of(L".]"); at != std::wstring::npos) last = last.substr(at + 1);
    const auto lw = Hub_KeyWords(last.empty() ? key : last);
    return lw.size() == 1 && (lw[0] == L"key" || lw[0] == L"keys");
}

// A run that flips between capitals, small letters and digits all the time, as keys do. Names
// and styles flip once a word ("BackgroundSizing=InnerBorderEdge"), so they stay.
static bool Hub_LooksRandom(const std::wstring& run) {
    if (run.size() >= 32 && run.find_first_not_of(L"0123456789abcdefABCDEF") == std::wstring::npos) return true;
    bool lo = false, up = false;
    size_t digits = 0, flips = 0;
    for (size_t i = 0; i < run.size(); i++) {
        const wchar_t a = run[i];
        lo |= a >= L'a' && a <= L'z';
        up |= a >= L'A' && a <= L'Z';
        digits += a >= L'0' && a <= L'9';
        if (i + 1 < run.size()) {
            const wchar_t b = run[i + 1];
            const bool al = a >= L'a' && a <= L'z', au = a >= L'A' && a <= L'Z', ad = a >= L'0' && a <= L'9';
            const bool bl = b >= L'a' && b <= L'z', bu = b >= L'A' && b <= L'Z', bd = b >= L'0' && b <= L'9';
            flips += (al && bu) || (au && bl) || (ad != bd);
        }
    }
    return lo && up && digits >= 3 && flips * 100 >= run.size() * 35;
}

static bool Hub_SecretValue(const Js& v) {
    if (v.t != Js::Str) return false;
    for (PCWSTR prefix : {L"sk-", L"ghp_", L"github_pat_", L"xox", L"AIza", L"Bearer "})
        if (v.s.rfind(prefix, 0) == 0) return true;
    static const std::wregex token(
        L"\\b(sk-[A-Za-z0-9_\\-]{8,}|sk_(live|test)_[A-Za-z0-9]{10,}|gh[pousr]_[A-Za-z0-9]{10,}|github_pat_[A-Za-z0-9_]{20,}|"
        L"xox[abposr]-|AIza[0-9A-Za-z_\\-]{10,}|AKIA[0-9A-Z]{12,}|eyJ[A-Za-z0-9_\\-]{8,}\\.[A-Za-z0-9_\\-]{4,}|"
        L"bearer\\s+[A-Za-z0-9._~+/\\-]{12,})|discord(app)?\\.com/api/webhooks|hooks\\.slack\\.com/|-----BEGIN [A-Z ]*PRIVATE KEY",
        std::regex::icase);
    if (std::regex_search(v.s, token)) return true;
    static const std::wregex run(L"[A-Za-z0-9+/=_\\-]{32,}");
    for (std::wsregex_iterator it(v.s.begin(), v.s.end(), run), end; it != end; ++it)
        if (Hub_LooksRandom(it->str())) return true;
    static const std::wregex email(L"[A-Za-z0-9._%+\\-]+@[A-Za-z0-9\\-]+(\\.[A-Za-z0-9\\-]+)*\\.[A-Za-z]{2,24}\\b");
    for (std::wsregex_iterator it(v.s.begin(), v.s.end(), email), end; it != end; ++it) {
        std::wstring m = it->str();
        for (auto& c : m) c = (wchar_t)towlower(c);
        if (m.rfind(L"local@", 0) != 0) return true;
    }
    return false;
}

// A list item's shape: "rows[3].name" is "rows[].name".
static std::wstring Hub_KeyShape(const std::wstring& k) {
    std::wstring s;
    for (size_t i = 0; i < k.size(); i++) {
        s += k[i];
        if (k[i] != L'[') continue;
        size_t j = i + 1;
        while (j < k.size() && iswdigit(k[j])) j++;
        if (j > i + 1 && j < k.size() && k[j] == L']') i = j - 1;
    }
    return s;
}

// Fits a settings set to what the mod declares on this PC, so Windhawk takes it: names the mod
// no longer has are left out, a number saved as unsigned (4294967295) goes back to -1, a number
// where the mod wants text becomes text, and every declared setting the set lacks gets the
// mod's default. A list the set holds is kept whole; its default items are not added to it.
static std::wstring Hub_FitSettings(const Js& want, const Js& defs, int* dropped = nullptr) {
    std::map<std::wstring, const Js*> declared;
    std::set<std::wstring> tops;
    for (size_t i = 0; i < defs.keys.size(); i++) {
        declared[Hub_KeyShape(defs.keys[i])] = &defs.a[i];
        if (const size_t at = defs.keys[i].find(L'['); at != std::wstring::npos) tops.insert(defs.keys[i].substr(0, at));
    }
    std::vector<std::pair<std::wstring, std::wstring>> out;
    std::set<std::wstring> have, wantTops;
    int skipped = 0;
    for (size_t i = 0; i < want.keys.size(); i++) {
        const std::wstring& k = want.keys[i];
        const size_t at = k.find(L'[');
        const auto d = declared.find(Hub_KeyShape(k));
        if (d == declared.end() && !(at != std::wstring::npos && tops.count(k.substr(0, at)))) { skipped++; continue; }
        if (at != std::wstring::npos) wantTops.insert(k.substr(0, at));
        Js v = want.a[i];
        const Js* def = d == declared.end() ? nullptr : d->second;
        if (v.t == Js::Num && def && def->t == Js::Str) {
            v.t = Js::Str;
        } else if (v.t == Js::Num && v.s.find_first_not_of(L"0123456789") == std::wstring::npos && v.s.size() == 10) {
            const unsigned long long n = wcstoull(v.s.c_str(), nullptr, 10);
            if (n > 0x7FFFFFFFull && n <= 0xFFFFFFFFull) v.s = std::to_wstring((long long)n - 0x100000000ll);
        }
        have.insert(k);
        out.push_back({k, Hub_JsDump(v)});
    }
    for (size_t i = 0; i < defs.keys.size(); i++) {
        const std::wstring& k = defs.keys[i];
        if (have.count(k)) continue;
        if (const size_t at = k.find(L'['); at != std::wstring::npos && wantTops.count(k.substr(0, at))) continue;
        out.push_back({k, Hub_JsDump(defs.a[i])});
    }
    if (dropped) *dropped = skipped;
    std::wstring json = L"{";
    for (size_t i = 0; i < out.size(); i++) json += (i ? L",\n  " : L"\n  ") + Js_Quote(out[i].first) + L": " + out[i].second;
    return json + L"\n}\n";
}

// Run inside a job just before "mod settings write <id> <file>": the file is fitted to the mod
// as it is installed now. When the mod's defaults cannot be read the file is left as it is.
static void Hub_FitSettingsFile(const std::wstring& line) {
    int argc = 0;
    LPWSTR* argv = CommandLineToArgvW(line.c_str(), &argc);
    if (!argv) return;
    const std::wstring id = argc == 5 ? argv[3] : L"", file = argc == 5 ? argv[4] : L"";
    LocalFree(argv);
    if (id.empty() || file.empty()) return;
    Js defs, want;
    std::wstring err;
    std::string raw;
    if (!Hub_Cli(L"mod settings defaults " + Set_QuoteArg(id), defs, err) || !Hub_ReadFile(file, raw) ||
        !Js_Parse(Hub_Wide(raw), want) || want.t != Js::Obj)
        return;
    const Js* s = defs.get(L"settings");
    if (!s || s->t != Js::Obj) return;
    Hub_WriteFile(file, Hub_Utf8(Hub_FitSettings(want, *s)));
}

// The settings to write: the user's current settings with DavidHiFi's safe values laid over
// them. A list in the preset replaces the user's list of the same name whole.
static std::wstring Hub_PresetMerge(const Js& preset, const Js* current, int* dropped = nullptr) {
    std::map<std::wstring, std::wstring> out;  // name -> JSON value
    if (current && current->t == Js::Obj)
        for (size_t i = 0; i < current->keys.size(); i++) out[current->keys[i]] = Hub_JsDump(current->a[i]);
    std::set<std::wstring> lists;
    for (auto& k : preset.keys)
        if (const size_t at = k.find(L'['); at != std::wstring::npos && !Hub_SecretKey(k)) lists.insert(k.substr(0, at + 1));
    for (auto& pre : lists)
        for (auto it = out.lower_bound(pre); it != out.end() && it->first.compare(0, pre.size(), pre) == 0;) {
            if (Hub_SecretKey(it->first)) ++it;
            else it = out.erase(it);
        }
    int skipped = 0;
    for (size_t i = 0; i < preset.keys.size(); i++) {
        if (Hub_SecretKey(preset.keys[i]) || Hub_SecretValue(preset.a[i])) { skipped++; continue; }
        out[preset.keys[i]] = Hub_JsDump(preset.a[i]);
    }
    if (dropped) *dropped = skipped;
    std::wstring json = L"{";
    bool first = true;
    for (auto& [k, v] : out) {
        json += (first ? L"\n  " : L",\n  ") + Js_Quote(k) + L": " + v;
        first = false;
    }
    return json + L"\n}\n";
}

static const HubFeedMod* Hub_FeedFind(const std::wstring& id) {
    for (auto& f : g_feed) if (f.id == id) return &f;
    return nullptr;
}

// DavidHiFi's installed mods, without this app: in his feed, or his name first in the author line.
static std::vector<std::wstring> Hub_DavidIds() {
    std::vector<std::wstring> ids;
    for (auto& m : g_hub.mods)
        if (m.id != kHubSelfId && (Hub_FeedFind(m.id) || Hub_ModSource(m) == 0)) ids.push_back(m.id);
    return ids;
}

// First open: nobody has set anything up yet. Gone once a choice is made or his mods are there.
static bool Hub_ShowWelcome() {
    return !g_reading && !Hub_RegGet(L"Set.welcomed", 0) && Hub_DavidIds().empty();
}

// ---- Mod page extras (versions, settings as text, reset) ---------------------------------

static std::wstring Hub_EditFile(const std::wstring& id) {
    std::wstring safe = id;
    std::replace(safe.begin(), safe.end(), L'@', L'-');
    return Hub_DataDir() + L"\\edit-" + safe + L".json";
}

static void Hub_DetailExtras(SetWindow& w, float& y) {
    if (g_hub.detail < 0) return;
    const HubMod& m = g_hub.mods[g_hub.detail];
    if (g_statusFor != m.id) {
        g_statusFor = m.id; g_featureStatus.clear(); g_versions.clear(); g_resetArmed = 0;
    }
    if (m.nuked == L"1" || m.nuked == L"true")
        Hub_Notice(w, y, L"This mod was taken out of the Windhawk library. It still works, but it will not get updates.");
    Hub_Group(w, y, L"More");
    const bool local = m.id.rfind(L"local@", 0) == 0;
    if (!local) {
        Hub_AddLink(w, y, L"Older versions", L"List every published version. You can go back to one.", L"hub:versions");
        for (auto& [ver, pre] : g_versions) {
            const bool current = ver == m.version;
            Hub_AddLink(w, y, (current ? L"Version " + ver + L" (installed)" : L"Install version " + ver),
                        current ? std::wstring(L"Installs it again over the current copy. Settings stay.")
                                : (pre ? L"Pre-release. " : L"") + std::wstring(L"Backs up first. A turned-off mod stays off."),
                        Hub_In(L"hub:version:" + ver));
        }
        Hub_AddLink(w, y, L"Change history", L"Every change to this mod, on GitHub.",
                    Hub_In(L"https://github.com/ramensoftware/windhawk-mods/commits/main/mods/" + m.id + L".wh.cpp"));
        Hub_AddLink(w, y, L"Library page", L"Description, screenshots and credits on windhawk.net.",
                    Hub_In(L"https://windhawk.net/mods/" + m.id));
    }
    Hub_AddLink(w, y, L"Open source", L"Open the installed .wh.cpp file.", L"hub:detailSource");
    Hub_AddLink(w, y, L"Edit settings as text", L"Opens every setting in Notepad, one per line. Save it, then choose Load.", L"hub:settingsEdit");
    if (GetFileAttributesW(Hub_EditFile(m.id).c_str()) != INVALID_FILE_ATTRIBUTES)
        Hub_AddLink(w, y, L"Load edited settings", L"Backs up first, then replaces this mod's settings with the file.", L"hub:settingsLoad");
    if (const HubFeedMod* f = Hub_FeedFind(m.id); f && f->hasPreset)
        Hub_AddLink(w, y, L"Use DavidHiFi's settings",
                    L"Saves your current settings as a preset first. On or off stays as it is. Nothing private is copied.",
                    L"hub:davidPreset");
    if (g_resetArmed && GetTickCount64() - g_resetArmed < 5000)
        Hub_AddLink(w, y, L"Click again to reset", L"Every setting goes back to the mod's default. A backup is saved first.", L"hub:settingsReset");
    else
        Hub_AddLink(w, y, L"Back to default settings", L"Put every setting back to what the mod ships with.", L"hub:settingsReset");
    Hub_Notice(w, y, g_reading ? L"Reading Windhawk. You can keep using the window." : g_featureStatus);
}

// "DavidHiFi's whole setup": every mod he runs (his own and the library ones) in one go, with or
// without his settings, on top of what is there or after clearing it. The labels match the
// install steps in the Workshop readme.
static void Hub_FullSetupItems(SetWindow& w, float& y) {
    const size_t total = g_feed.size() + g_feedLib.size();
    if (!total) return;
    Hub_Group(w, y, L"DavidHiFi's whole setup");
    const bool clean = Hub_RegGet(L"Set.cleanSlate", 1) != 0;
    Hub_AddLink(w, y, clean ? L"Clean slate first: on" : L"Clean slate first: off",
                clean ? L"Every mod you have now comes off first, except this one. A backup is saved before anything is removed. Click to turn off."
                      : L"Your mods stay. Ones you already have are not installed again. Click to turn on.",
                L"hub:cleanSlate");
    const bool armed = g_fullArmed && GetTickCount64() - g_fullArmed < 5000;
    const std::wstring count = std::to_wstring(total) + L" mods";
    Hub_AddLink(w, y, armed && g_fullArmedConfig ? L"Click again to copy everything" : L"Copy everything, settings included",
                (L"Installs all " + count + L" with DavidHiFi's settings, each one on or off the way he has it. "
                 L"Nothing private is copied. Takes 15 to 30 minutes.").c_str(),
                L"hub:fullSetup:config");
    Hub_AddLink(w, y, armed && !g_fullArmedConfig ? L"Click again to install everything" : L"Install everything, default settings",
                (L"Installs all " + count + L" turned off, with each mod's own settings. Turn on the ones you want on the Mods page.").c_str(),
                L"hub:fullSetup:plain");
}

// First open, Mods page: a short welcome with the two ways in, above the list.
static void Hub_WelcomeItems(SetWindow& w, float& y) {
    if (!Hub_ShowWelcome()) return;
    static bool asked = false;  // One feed read for the welcome; a failed one waits for the Updates page.
    if (!asked && !g_feedChecked && !g_feedBusy && !w.render && w.hwnd) { asked = true; Hub_FeedStart(w.hwnd, true); }
    Hub_Group(w, y, L"Welcome to Seamless Workshop");
    Hub_Notice(w, y, L"This window installs, updates and removes DavidHiFi's Windhawk mods. "
                     L"Get his whole setup in one go, or pick the mods you want.");
    Hub_FullSetupItems(w, y);
    Hub_Group(w, y, L"Or choose yourself");
    Hub_AddLink(w, y, L"Pick from his mods", L"Opens Marketplace with only his mods, so you can install the ones you like.",
                L"hub:welcomePick");
    Hub_AddLink(w, y, L"Not now", L"Hide this. Every choice stays on the Updates and Marketplace pages.", L"hub:welcomeDone");
    if (g_feed.empty()) Hub_Notice(w, y, g_feedBusy ? std::wstring(L"Reading DavidHiFi's mods...") : g_feedStatus);
    y += 6;
}

static void Hub_FeatureItems(SetWindow& w, float& y) {
    auto link = [&](PCWSTR title, PCWSTR desc, const std::wstring& action) {
        Hub_AddLink(w, y, title, desc, Hub_In(action));
    };
    if (w.page == 1) {
        if (!g_repoId.empty()) {
            link(L"Back to results", L"Keep the current search.", L"hub:repoBack");
            Hub_Notice(w, y, g_repoDetail);
            bool installed = false;
            for (auto& m : g_hub.mods) installed |= m.id == g_repoId;
            if (!installed) link(L"Install turned off", L"Installs this mod without loading it into any app.", L"hub:install:" + g_repoId);
            else Hub_Notice(w, y, L"Already installed. Change its settings on the Mods page.");
            link(L"Full description and credits", L"Open this mod's page on the Windhawk website.", L"https://windhawk.net/mods/" + g_repoId);
        } else {
            auto query = Hub_Lower(Hub_LiveText(w, L"hub.marketSearch"));
            while (!query.empty() && query.back() == L' ') query.pop_back();
            const std::wstring show = Hub_Input(w, L"hub.marketShow");
            int n = 0, mine = 0, have = 0;
            bool head = false;
            // Search looks through every group, its name included ("taskbar" finds them all).
            auto wantMine = [&](const HubFeedMod& f) {
                if (show == L"new" && Hub_FindMod(f.id)) return false;
                return query.empty() ||
                       Hub_Lower(f.name + L" " + f.desc + L" " + f.id + L" " + Hub_CatName(Hub_CatIndex(f.category)))
                               .find(query) != std::wstring::npos;
            };
            for (auto& f : g_feed) head |= wantMine(f);
            if (head) {
                // His mods come first, with a count so it is clear how many there are, then one
                // heading per group in the feed's order.
                Hub_Group(w, y, L"From DavidHiFi");
                for (auto& g : g_feed) { mine++; have += Hub_FindMod(g.id) != nullptr; }
                Hub_Notice(w, y, std::to_wstring(mine) + L" mods made by DavidHiFi, " + std::to_wstring(have) +
                                     L" of them installed. Click one to install it or open it.");
                Hub_FeedByCat(w, y, wantMine, [&](const HubFeedMod& f) {
                    link(f.name.c_str(), f.desc.c_str(), L"hub:feed:" + f.id);
                    n++;
                });
            }
            if (g_feed.empty())
                Hub_Notice(w, y, g_feedBusy ? std::wstring(L"Reading DavidHiFi's mods...")
                                            : g_feedStatus.empty() ? std::wstring() : L"DavidHiFi's mods: " + g_feedStatus);
            if (show != L"mine") {
                head = false;
                int shown = 0;
                for (auto& m : g_repo) {
                    if (show == L"new" && Hub_FindMod(m.id)) continue;
                    if (!query.empty() && m.lower.find(query) == std::wstring::npos) continue;
                    if (Hub_FeedFind(m.id)) continue;
                    if (++shown > 90) break;
                    if (!head) { Hub_Group(w, y, L"From the Windhawk library"); head = true; }
                    link(m.name.c_str(), m.desc.c_str(), L"hub:repo:" + m.id);
                    n++;
                }
                if (shown > 90) Hub_Notice(w, y, L"More mods match. Type more of a name to narrow it down.");
            }
            if (g_repo.empty() && !g_reading) Hub_Notice(w, y, L"The library has not been read yet.");
            else if (n == 0) Hub_Notice(w, y, L"No matches. Try a shorter name or another word.");
            link(L"Reload the library", L"Reads the Windhawk library again. Installed mods stay as they are.", L"hub:market");
        }
    } else if (w.page == 2) {
        link(L"Check for updates", L"Read the library and compare it with your installed mods.", L"hub:updates");
        Hub_Notice(w, y, g_engineStatus);
        int n = 0;
        for (auto& m : g_hub.mods) if (m.update && m.id.find(L"local@") != 0) {
            link((L"Update " + m.name).c_str(), L"Back up first. A turned-off mod stays off.", L"hub:update:" + m.id); n++;
        }
        if (!g_repo.empty() && !n) Hub_Notice(w, y, L"No library updates found for your installed mods.");
        if (n >= 2) link((L"Update all " + std::to_wstring(n) + L" library mods").c_str(), L"Backs up every one first. Turned-off mods stay off.", L"hub:updateAll");
        if (Hub_FileThere(Hub_Tool(L"Tool.engineGuide")))
            link(L"Windhawk preview updates", L"Open the checked update helper's instructions. Engine restarts wait until T3 Code is closed.", L"hub:engineGuide");
        Hub_Group(w, y, L"From DavidHiFi");
        auto hasUpdate = [](const HubFeedMod& f) {
            const HubMod* m = Hub_FindMod(f.id);
            return m && Hub_Newer(f.version, m->version);
        };
        int updates = 0;
        for (auto& f : g_feed) updates += hasUpdate(f);
        link(L"Check the feed now", L"Look for new versions of DavidHiFi's mods and of this app.", L"hub:feedCheck");
        Hub_Notice(w, y, g_feedBusy ? L"Checking DavidHiFi's feed..." : g_feedStatus);
        if (updates >= 2) link(L"Update all from DavidHiFi", L"Every update below, one backup, one admin prompt.", L"hub:feedAll");
        // His updates, then his mods not installed yet, each under its group in the feed's order.
        Hub_FeedByCat(w, y, hasUpdate, [&](const HubFeedMod& f) {
            const HubMod* m = Hub_FindMod(f.id);
            const std::wstring news = f.changes.empty() ? std::wstring() : L"New: " + f.changes + L" ";
            link((L"Update " + f.name + L" to " + f.version).c_str(), (news + L"You have " + m->version + L". Backs up first. Stays on or off as it is now.").c_str(), L"hub:feed:" + f.id);
        });
        auto notHere = [](const HubFeedMod& f) { return !Hub_FindMod(f.id); };
        int missing = 0;
        for (auto& f : g_feed) missing += notHere(f);
        if (missing) {
            Hub_Group(w, y, L"More from DavidHiFi");
            Hub_Notice(w, y, std::to_wstring(missing) + (missing == 1 ? L" of his mods is" : L" of his mods are") +
                                 L" not installed yet. Each one installs turned off.");
            Hub_FeedByCat(w, y, notHere, [&](const HubFeedMod& f) {
                link((L"Install " + f.name).c_str(), (f.desc.empty() ? std::wstring(L"Installs turned off.") : f.desc + L" Installs turned off.").c_str(), L"hub:feed:" + f.id);
            });
        }
        Hub_FullSetupItems(w, y);
        bool anyPreset = false;
        for (auto& f : g_feed) anyPreset |= f.hasPreset;
        const size_t his = Hub_DavidIds().size();
        if (anyPreset || his) {
            Hub_Group(w, y, L"Only his own mods");
            if (anyPreset && g_setupArmed && GetTickCount64() - g_setupArmed < 5000)
                link(L"Click again to set up his own mods",
                     L"Your current settings are saved as a preset first. Mods that are not his stay as they are.",
                     L"hub:davidSetup");
            else if (anyPreset)
                link(L"Set up his own mods with his settings",
                     L"Only the mods he made: installs the missing ones, then sets each one up the way he uses it. Library mods are left alone.",
                     L"hub:davidSetup");
            // A clean way out: every one of his mods comes off in one go, with a backup first.
            const std::wstring count = std::to_wstring(his) + (his == 1 ? L" mod" : L" mods");
            if (his && g_removeAllArmed && GetTickCount64() - g_removeAllArmed < 5000)
                link((L"Click again to remove " + count).c_str(),
                     L"Their settings are saved as a preset first, so you can put them back from the Presets page.",
                     L"hub:removeAll");
            else if (his)
                link(L"Remove all of DavidHiFi's mods",
                     (L"Takes off his " + count + L". Your other mods and Seamless Workshop stay. A backup is saved first.").c_str(),
                     L"hub:removeAll");
        }
        Hub_Group(w, y, L"Seamless Workshop");
        const std::wstring appNews = g_feedApp.changes.empty() ? std::wstring() : L"New: " + g_feedApp.changes + L" ";
#ifdef HUB_MOD
        if (Hub_AppNewer())
            link((L"Update Seamless Workshop to " + g_feedApp.version).c_str(), (appNews + L"Downloads it, checks it and installs it through Windhawk. The window reopens by itself.").c_str(), L"hub:appUpdate");
#else
        if (Hub_AppNewer())
            link((L"Update Seamless Workshop to " + g_feedApp.version).c_str(), (appNews + L"Downloads it, checks it, swaps it in and opens the new version.").c_str(), L"hub:appUpdate");
#endif
        else
            Hub_Notice(w, y, std::wstring(L"Seamless Workshop ") + WH_MOD_VERSION + (g_feedChecked ? L". This is the newest version." : L"."));
    } else if (w.page == 3) {
        link(L"Save selected mods", L"Save on/off states and every stored setting. Installed source is unchanged.", L"hub:presetSave");
        link(L"Import a preset file", L"Choose a saved Seamless Workshop preset. Import only adds it to this list.", L"hub:presetImport");
        link(L"Open presets folder", L"Copy a preset file to export it or share it.", L"hub:presetFolder");
        for (auto& name : Hub_Presets()) {
            link((L"Apply " + name).c_str(), L"Back up the selected mods, then restore their settings and on/off states.", L"hub:presetApply:" + name);
        }
    } else if (w.page == 4) {
        link(L"Inspect installed mod", L"Read its source metadata and current configuration into a report.", L"hub:inspect");
        link(L"Where is it running", L"List the apps that have this mod loaded right now.", L"hub:where");
        link(L"Release checklist", L"Author, Ko-fi link, plain id, readme and preview image.", L"hub:release");
        link(L"Open installed source", L"Open the selected mod's .wh.cpp file with your default editor.", L"hub:source");
        link(L"Compile disabled mod", L"Backs up first. The mod must be off. Runs through the load gate.", L"hub:compile");
        link(L"Check staged source", L"Validate metadata and settings without installing or loading anything.", L"hub:check");
        link(L"Install checked source turned off", L"Only if the file is unchanged since Check. Backs up first.", L"hub:stagedInstall");
        if (Hub_GlassReady()) link(L"Glass check", L"Compare every mod's settings window glass with Seamless Launchpad.", L"hub:glass");
        link(L"Open reports and backups", L"Saved command results and preset rollback files.", L"hub:reports");
        link(L"Open stock Windhawk", L"Use Windhawk's own editor and log window.", L"hub:stock");
    } else if (w.page == 5) {
        Hub_Group(w, y, L"Backup");
        link(L"Back up everything", L"Every mod, its settings and Windhawk's settings, in one file you choose.", L"hub:export");
        link(L"Restore from a backup", L"Choose a backup file. It is read first; nothing changes yet.", L"hub:restorePick");
        if (!g_restoreFile.empty()) {
            if (g_restoreArmed && GetTickCount64() - g_restoreArmed < 5000)
                link(L"Click again to restore", L"Your current mods are saved first. Windhawk's own settings stay as they are.", L"hub:restore");
            else
                link(L"Restore now", L"Brings back the mods and settings in the chosen backup. Saves the current state first.", L"hub:restore");
        }
        Hub_Group(w, y, L"Windhawk itself");
        link(L"Open Windhawk", L"Some of its settings apply only after it restarts. This app never restarts it for you.", L"hub:stock");
    }
    if (w.page >= 1 && w.page <= 5) Hub_Notice(w, y, g_reading ? L"Reading Windhawk. You can keep using the window." : g_featureStatus);
}

static void Hub_StartTask(SetWindow& w, const std::wstring& kind, std::function<bool(Js&, std::wstring&)> task) {
    if (g_reading) { Set_SetStatus(w, L"A read is already running."); return; }
    if (g_reader.joinable()) g_reader.join();
    g_reading = true; g_readKind = kind; g_readError.clear(); g_readData = Js{};
    const HWND hwnd = w.hwnd;
    g_reader = std::thread([task, hwnd] {
        if (!task(g_readData, g_readError) && g_readError.empty()) g_readError = L"The read did not finish.";
        PostMessageW(hwnd, WM_HUB_RESULT, 0, 0);
    });
    Set_BuildAndClamp(w);
}

static void Hub_StartRead(SetWindow& w, const std::wstring& kind, const std::wstring& args) {
    Hub_StartTask(w, kind, [args](Js& data, std::wstring& err) { return Hub_Cli(args, data, err); });
}

static void Hub_ReadResult(SetWindow& w) {
    if (g_reader.joinable()) g_reader.join();
    g_reading = false;
    if (!g_readError.empty()) {
        if (g_readKind == L"check") g_checkedPath.clear(), g_checkedSha.clear(), g_checkedId.clear();
        if (g_readKind == L"archive") g_restoreFile.clear(), g_restorePending.clear();
        g_featureStatus = g_readError; Set_BuildAndClamp(w);
        for (auto& it : w.items)
            if (it.type == SetItem::Banner && it.text == g_featureStatus) { Set_EnsureVisible(w, it.y, it.y + it.h); break; }
        Set_SetStatus(w, g_readError.c_str(), true); return;
    }
    if (g_readKind == L"market" || g_readKind == L"updates") {
        g_repo.clear();
        if (const Js* mods = g_readData.get(L"mods"); mods && mods->t == Js::Arr) for (auto& j : mods->a) {
            const Js* meta = j.get(L"metadata"); if (!meta) continue;
            HubMod m; m.id = Js_Text(j.get(L"id"));
            if (!Hub_ValidId(m.id)) continue;
            m.name = Js_Text(meta->get(L"name")); m.version = Js_Text(meta->get(L"version"));
            m.author = Js_Text(meta->get(L"author")); m.desc = Js_Text(meta->get(L"description"));
            m.lower = Hub_Lower(m.name + L" " + m.author + L" " + m.desc + L" " + m.id);
            g_repo.push_back(std::move(m));
        }
        g_featureStatus = std::to_wstring(g_repo.size()) + L" library mods loaded.";
        if (g_readKind == L"updates") {
            for (auto& installed : g_hub.mods) for (auto& available : g_repo)
                if (installed.id == available.id && !available.version.empty())
                    installed.update = Hub_Newer(available.version, installed.version);
            Js status; std::wstring err;
            if (Hub_Cli(L"update status", status, err))
                g_engineStatus = L"Windhawk " + Js_Text(status.get(L"installedVersion")) +
                                 L". Latest known: " + Js_Text(status.get(L"latestVersion")) + L".";
        }
    } else if (g_readKind == L"detail") {
        const Js* meta = g_readData.get(L"metadata");
        g_repoDetail = meta ? Js_Text(meta->get(L"name")) + L" by " + Js_Text(meta->get(L"author")) + L"\n" +
                             Js_Text(meta->get(L"description")) : L"Details unavailable.";
        g_repoReadme = Js_Text(g_readData.get(L"readme"));
        g_featureStatus.clear();
    } else if (g_readKind == L"preset") {
        g_featureStatus = L"Preset saved. Its file is in the presets folder.";
    } else if (g_readKind == L"versions") {
        g_versions.clear();
        if (const Js* list = g_readData.get(L"versions"); list && list->t == Js::Arr)
            for (auto it = list->a.rbegin(); it != list->a.rend() && g_versions.size() < 12; ++it) {
                const auto ver = Js_Text(it->get(L"version"));
                const Js* pre = it->get(L"isPreRelease");
                if (!ver.empty() && ver.size() < 40 && ver.find_first_not_of(L"0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz.+-") == std::wstring::npos)
                    g_versions.push_back({ver, pre && pre->t == Js::Bool && pre->b});
            }
        g_featureStatus = g_versions.empty() ? L"No published versions were found." : L"Newest first. Pick one to install it.";
    } else if (g_readKind == L"export") {
        g_featureStatus = L"Backup saved: " + g_exportFile;
    } else if (g_readKind == L"archive") {
        const Js* manifest = g_readData.get(L"manifest");
        const Js* mods = manifest ? manifest->get(L"mods") : nullptr;
        const Js* app = manifest ? manifest->get(L"hasAppSettings") : nullptr;
        const size_t n = mods && mods->t == Js::Arr ? mods->a.size() : 0;
        g_restoreFile = g_restorePending; g_restoreArmed = 0;
        g_featureStatus = L"This backup holds " + std::to_wstring(n) + (n == 1 ? L" mod" : L" mods") +
                          (app && app->t == Js::Bool && app->b ? L" and Windhawk's settings" : L"") +
                          L". Choose Restore now to bring the mods back.";
    } else {
        const auto file = Hub_DataDir() + L"\\" + g_readKind + L"-" + std::to_wstring(GetTickCount64()) + L".json";
        if (!Hub_WriteFile(file, Hub_Utf8(Hub_JsDump(g_readData)))) {
            Set_SetStatus(w, L"The command succeeded, but its report could not be saved.", true); return;
        }
        std::wstring report = L"Read completed.";
        if (g_readKind == L"inspect") report = L"Installed mod metadata read successfully.";
        if (g_readKind == L"check") {
            const Js* meta = g_readData.get(L"metadata");
            g_checkedId = meta ? Js_Text(meta->get(L"id")) : L"";
            g_checkedPath = g_checkPendingPath; g_checkedSha = g_checkPendingSha;
            report = L"Source metadata and settings passed Windhawk's strict check. It can be installed turned off now.";
            if (!Hub_ValidId(g_checkedId) || g_checkedSha.empty()) {
                g_checkedPath.clear(); g_checkedSha.clear();
                report = L"The check passed, but the file has no usable id, so it cannot be installed from here.";
            }
        }
        if (g_readKind == L"where") {
            const Js* apps = g_readData.get(L"apps");
            const size_t n = apps && apps->t == Js::Arr ? apps->a.size() : 0;
            std::wstring names;
            for (size_t i = 0; i < n && i < 6; i++) names += (i ? L", " : L"") + Js_Text(&apps->a[i]);
            report = n ? L"Loaded in " + std::to_wstring(n) + (n == 1 ? L" app: " : L" apps: ") + names + (n > 6 ? L" and more." : L".")
                       : L"Not loaded in any app this account can read.";
            const auto hidden = Js_Text(g_readData.get(L"unreadable"));
            if (!hidden.empty() && hidden != L"0") report += L" " + hidden + L" admin or protected apps were not checked.";
        }
        if (g_readKind == L"release") {
            int pass = 0, total = 0; std::wstring missing;
            if (const Js* checks = g_readData.get(L"checks")) for (auto& c : checks->a) {
                total++;
                if (const Js* ok = c.get(L"ok"); ok && ok->b) pass++;
                else missing += (missing.empty() ? L"" : L", ") + Js_Text(c.get(L"name"));
            }
            report = L"Release checklist: " + std::to_wstring(pass) + L" of " + std::to_wstring(total) + L" pass." +
                     (missing.empty() ? L"" : L" Missing: " + missing + L".");
        }
        if (g_readKind == L"glass") {
            int ok = 0, off = 0;
            if (const Js* lines = g_readData.get(L"lines")) for (auto& l : lines->a) {
                const auto t = Js_Text(&l);
                if (t.find(L" OFF:") != std::wstring::npos) off++;
                else if (t.size() > 3 && t.substr(t.size() - 3) == L" ok") ok++;
            }
            report = L"Glass check: " + std::to_wstring(ok) + L" settings windows match Launchpad, " +
                     std::to_wstring(off) + L" do not. The full list is in reports.";
        }
        g_featureStatus = report;
    }
    Set_BuildAndClamp(w);
    // The result banner sits under the page's last link; bring it into view.
    for (auto& it : w.items)
        if (it.type == SetItem::Banner && it.text == g_featureStatus) { Set_EnsureVisible(w, it.y, it.y + it.h); break; }
    Set_Invalidate(w);
}

static void Hub_PageChanged(SetWindow& w) {
    g_featureStatus.clear();
    if (w.page == 1 && g_repo.empty() && !w.render) Hub_StartRead(w, L"market", L"repo list");
    const bool wantFeed = w.page == 1 || (w.page == 2 && Hub_AppInt(L"feedCheck", 1));
    if (wantFeed && !g_feedChecked && !g_feedBusy && !w.render) Hub_FeedStart(w.hwnd, true);
}

static std::wstring Hub_JsDump(const Js& j) {
    if (j.t == Js::Str) return Js_Quote(j.s);
    if (j.t == Js::Num) return j.s;
    if (j.t == Js::Bool) return j.b ? L"true" : L"false";
    if (j.t == Js::Null) return L"null";
    std::wstring s = j.t == Js::Obj ? L"{" : L"[";
    for (size_t i = 0; i < j.a.size(); i++) {
        if (i) s += L",";
        if (j.t == Js::Obj) s += Js_Quote(j.keys[i]) + L":";
        s += Hub_JsDump(j.a[i]);
    }
    return s + (j.t == Js::Obj ? L"}" : L"]");
}

static bool Hub_PresetFormat(const std::wstring& format) {
    return format == L"seamless-workshop-preset-1" || format == L"seamless-hub-preset-1";
}

// A picked list is capped at 32 mods; the whole-setup backup passes a larger limit.
static bool Hub_Snapshot(const std::vector<std::wstring>& ids, const std::wstring& path, std::wstring& err, size_t limit = 32) {
    if (ids.empty() || ids.size() > limit) {
        err = L"Choose between one and " + std::to_wstring(limit) + L" mods for a preset."; return false;
    }
    std::wstring json = L"{\"format\":\"seamless-workshop-preset-1\",\"mods\":[";
    bool first = true;
    const auto deadline = GetTickCount64() + 30000 + 1000 * (ULONGLONG)ids.size();
    for (auto& id : ids) {
        if (GetTickCount64() > deadline) { err = L"Reading the selected mods took too long. Try fewer mods."; return false; }
        Js settings, config;
        if (!Hub_ValidId(id) || !Hub_Cli(L"mod settings get " + Set_QuoteArg(id), settings, err) ||
            !Hub_Cli(L"mod config get " + Set_QuoteArg(id), config, err)) return false;
        const Js* values = settings.get(L"settings");
        const Js* cfg = config.get(L"config");
        if (!values || values->t != Js::Obj || !cfg) { err = L"Could not read every setting. Preset was not saved."; return false; }
        const Js* disabled = cfg->get(L"disabled");
        if (!first) json += L","; first = false;
        json += L"{\"id\":" + Js_Quote(id) + L",\"enabled\":" +
                (disabled && disabled->t == Js::Bool && disabled->b ? L"false" : L"true") +
                L",\"settings\":" + Hub_JsDump(*values) + L"}";
    }
    if (first) { err = L"Choose at least one installed mod."; return false; }
    if (!Hub_WriteFile(path, Hub_Utf8(json + L"]}"))) { err = L"Could not write the preset file."; return false; }
    return true;
}

static bool Hub_ReadPreset(const std::wstring& path, Js& data, std::wstring& err) {
    std::string raw;
    if (!Hub_ReadFile(path, raw) || !Js_Parse(Hub_Wide(raw), data) ||
        !Hub_PresetFormat(Js_Text(data.get(L"format")))) { err = L"This is not a Seamless Workshop preset."; return false; }
    const Js* mods = data.get(L"mods");
    if (!mods || mods->t != Js::Arr || mods->a.empty() || mods->a.size() > 300) { err = L"Presets must contain one to 300 mods."; return false; }
    std::set<std::wstring> seen;
    for (auto& m : mods->a) {
        const auto id = Js_Text(m.get(L"id"));
        const Js *settings = m.get(L"settings"), *enabled = m.get(L"enabled");
        if (!Hub_ValidId(id) || !seen.insert(id).second || !settings || settings->t != Js::Obj || !enabled || enabled->t != Js::Bool) {
            err = L"Preset contains an invalid mod entry."; return false;
        }
        for (auto& v : settings->a) if (v.t != Js::Str && v.t != Js::Num) { err = L"Preset settings must be text or numbers."; return false; }
    }
    return true;
}

template<class Operation> static bool Hub_WaitRead(SetWindow& w, Operation operation, PCWSTR text = L"Reading settings for backup...") {
    std::atomic<bool> finished = false;
    bool result = false;
    w.saving = true;
    Set_SetStatus(w, text);
    std::thread worker([&] { result = operation(); finished = true; });
    bool quit = false; int quitCode = 0;
    while (!finished) {
        MsgWaitForMultipleObjects(0, nullptr, FALSE, 100, QS_ALLINPUT);
        MSG message;
        while (PeekMessageW(&message, nullptr, 0, 0, PM_REMOVE)) {
            if (message.message == WM_QUIT) { quit = true; quitCode = (int)message.wParam; continue; }
            TranslateMessage(&message); DispatchMessageW(&message);
        }
    }
    worker.join(); w.saving = false;
    if (quit) PostQuitMessage(quitCode);
    return result;
}

static bool Hub_BackupFiles(const std::vector<std::wstring>& ids, std::wstring& err, std::wstring* restoreOut = nullptr) {
    std::set<std::wstring> unique(ids.begin(), ids.end());
    std::vector<std::wstring> selected(unique.begin(), unique.end());
    const auto stamp = std::to_wstring(GetTickCount64());
    const auto dir = Hub_DataDir() + L"\\backup-" + stamp;
    if (!CreateDirectoryW(dir.c_str(), nullptr)) { err = L"Could not create a backup. Nothing changed."; return false; }
    for (auto& id : selected) {
        if (!Hub_ValidId(id)) { err = L"Invalid mod id. Nothing changed."; return false; }
        const auto source = L"C:\\ProgramData\\Windhawk\\ModsSource\\" + id + L".wh.cpp";
        if (!CopyFileW(source.c_str(), (dir + L"\\" + id + L".wh.cpp").c_str(), TRUE)) {
            err = L"Could not back up the installed source. Nothing changed."; return false;
        }
    }
    // A backup covers every mod it was given; "update all" and "remove all" can pass more than 32.
    if (!Hub_Snapshot(selected, dir + L"\\restore.json", err, std::max<size_t>(32, selected.size()))) return false;
    if (restoreOut) *restoreOut = dir + L"\\restore.json";
    return Hub_WriteFile(dir + L"\\undo.txt", "Reinstall the saved source turned off if removed. Import restore.json on the Presets page, then apply it.\r\n");
}

static bool Hub_Backup(const std::vector<std::wstring>& ids, std::wstring& err) {
    if (g_setWin && g_setWin->hwnd)
        return Hub_WaitRead(*g_setWin, [&] { return Hub_BackupFiles(ids, err); });
    return Hub_BackupFiles(ids, err);
}

static std::vector<std::wstring> Hub_SplitIds(std::wstring text) {
    std::vector<std::wstring> ids;
    std::replace(text.begin(), text.end(), L',', L'\n');
    for (auto id : Hub_Lines(text)) {
        while (!id.empty() && id.front() == L' ') id.erase(0, 1);
        while (!id.empty() && id.back() == L' ') id.pop_back();
        if (std::find(ids.begin(), ids.end(), id) == ids.end()) ids.push_back(id);
    }
    return ids;
}

static void Hub_ApplyPreset(SetWindow& w, const std::wstring& name) {
    if (!Hub_PresetName(name)) return;
    Js preset; std::wstring err;
    if (!Hub_ReadPreset(Hub_PresetDir() + L"\\" + name + L".json", preset, err)) { Set_SetStatus(w, err.c_str(), true); return; }
    const Js& mods = *preset.get(L"mods");
    std::vector<std::wstring> ids;
    for (auto& m : mods.a) {
        const auto id = Js_Text(m.get(L"id")); bool found = false;
        for (auto& installed : g_hub.mods) if (installed.id == id) found = true;
        if (!found) { Set_SetStatus(w, (L"Install this preset's missing mod first: " + id).c_str(), true); return; }
        ids.push_back(id);
    }
    const auto backup = Hub_PresetDir() + L"\\Before " + name + L" " + std::to_wstring(GetTickCount64()) + L".json";
    if (!Hub_WaitRead(w, [&] { return Hub_Snapshot(ids, backup, err); })) { Set_SetStatus(w, err.c_str(), true); return; }
    std::vector<std::wstring> lines, files;
    for (size_t i = 0; i < mods.a.size(); i++) {
        const Js& m = mods.a[i];
        const auto id = Js_Text(m.get(L"id"));
        const auto file = Hub_DataDir() + L"\\preset-setting-" + std::to_wstring(GetTickCount64()) + L"-" + std::to_wstring(i) + L".json";
        if (!Hub_WriteFile(file, Hub_Utf8(Hub_JsDump(*m.get(L"settings"))))) {
            for (auto& p : files) DeleteFileW(p.c_str());
            Set_SetStatus(w, L"Could not prepare all preset settings. Nothing changed.", true); return;
        }
        files.push_back(file);
        lines.push_back(L"mod settings write " + Set_QuoteArg(id) + L" " + Set_QuoteArg(file));
        lines.push_back(std::wstring(m.get(L"enabled")->b ? L"mod enable " : L"mod disable ") + Set_QuoteArg(id));
    }
    const bool ok = Hub_RunJob(w, lines, err);
    for (auto& file : files) DeleteFileW(file.c_str());
    Hub_LoadList(w);
    Set_SetStatus(w, ok ? L"Preset applied. A Before preset is saved for undo." : (err + L" Use the Before preset to restore changed mods.").c_str(), !ok);
}

static void Hub_OpenFile(HWND hwnd, const std::wstring& file) {
    // A .wh.cpp often has no app set, and "open" then shows Windows' app picker. Use Notepad instead.
    const DWORD a = GetFileAttributesW(file.c_str());
    if (a != INVALID_FILE_ATTRIBUTES && !(a & FILE_ATTRIBUTE_DIRECTORY)) {
        wchar_t exe[MAX_PATH] = {};
        const bool found = (INT_PTR)FindExecutableW(file.c_str(), nullptr, exe) > 32;
        std::wstring name = exe;
        name = Hub_Lower(name.substr(name.find_last_of(L"\\/") + 1));
        if (!found || name == L"openwith.exe") {
            ShellExecuteW(hwnd, L"open", L"notepad.exe", Set_QuoteArg(file).c_str(), nullptr, SW_SHOWNORMAL);
            return;
        }
    }
    ShellExecuteW(hwnd, L"open", file.c_str(), nullptr, nullptr, SW_SHOWNORMAL);
}

// The "// @id" line of a mod source, or empty.
static std::wstring Hub_SourceId(const std::string& raw) {
    const auto at = raw.find("// @id");
    if (at == std::string::npos) return {};
    auto end = raw.find('\n', at);
    std::string v = raw.substr(at + 6, (end == std::string::npos ? raw.size() : end) - at - 6);
    while (!v.empty() && (v.front() == ' ' || v.front() == '\t')) v.erase(0, 1);
    while (!v.empty() && (v.back() == '\r' || v.back() == ' ' || v.back() == '\t')) v.pop_back();
    return Hub_Wide(v);
}

// Downloads each mod, checks it against the feed's fingerprint, then installs it in one admin run.
// A mod that was on is turned off for the swap and back on after, the same as Windhawk does.
// Downloads each feed mod and checks its fingerprint and @id. Runs off the UI thread.
static bool Hub_FeedFetch(const std::vector<HubFeedMod>& list, std::vector<std::wstring>& files, std::wstring& err) {
    const auto dir = Hub_DataDir() + L"\\feed";
    CreateDirectoryW(dir.c_str(), nullptr);
    files.assign(list.size(), std::wstring());
    for (size_t i = 0; i < list.size(); i++) {
        std::string raw;
        if (!Hub_Download(list[i].url, raw, err)) return false;
        if (Hub_Sha256Data(raw) != list[i].sha) {
            err = L"The download of " + list[i].name + L" does not match the feed. Nothing was installed."; return false;
        }
        if (L"local@" + Hub_SourceId(raw) != list[i].id) {
            err = L"The download of " + list[i].name + L" is a different mod than the feed says. Nothing was installed."; return false;
        }
        files[i] = dir + L"\\" + list[i].id.substr(6) + L".wh.cpp";
        if (!Hub_WriteFile(files[i], raw)) { err = L"Could not save the download. Nothing was installed."; return false; }
    }
    return true;
}

static void Hub_FeedInstall(SetWindow& w, const std::vector<HubFeedMod>& list) {
    if (list.empty()) return;
    std::vector<std::wstring> files;
    std::wstring err;
    auto cleanup = [&] { for (auto& f : files) if (!f.empty()) DeleteFileW(f.c_str()); };
    const bool fetched = Hub_WaitRead(w, [&] { return Hub_FeedFetch(list, files, err); }, L"Downloading from DavidHiFi...");
    if (!fetched) { cleanup(); Set_SetStatus(w, err.c_str(), true); return; }
    std::vector<std::wstring> installed, lines;
    for (size_t i = 0; i < list.size(); i++) {
        const HubMod* m = Hub_FindMod(list[i].id);
        const bool on = m && m->enabled;
        if (m) installed.push_back(m->id);
        if (on) lines.push_back(L"mod disable " + Set_QuoteArg(list[i].id));
        lines.push_back(L"@install " + list[i].sha + L" " + Set_QuoteArg(files[i]));
        if (on) lines.push_back(L"mod enable " + Set_QuoteArg(list[i].id));
    }
    if (!installed.empty() && !Hub_Backup(installed, err)) { cleanup(); Set_SetStatus(w, err.c_str(), true); return; }
    const bool ok = Hub_RunJob(w, lines, err);
    cleanup();
    Hub_LoadList(w);
    Set_BuildAndClamp(w);
    if (!ok) { Set_SetStatus(w, (err + L" The old copies are in backups.").c_str(), true); return; }
    g_feedStatus = list.size() == 1 ? list[0].name + L" is now " + list[0].version + L"."
                                    : std::to_wstring(list.size()) + L" mods from DavidHiFi are up to date.";
    Set_BuildAndClamp(w);
    Set_SetStatus(w, installed.empty() ? L"Installed turned off. Turn it on from the Mods page." : L"Updated. The old copies are in backups.");
}

// The config lines for one mod: which apps it loads into beyond its own list.
static void Hub_ConfigLines(const HubFeedMod& f, std::vector<std::wstring>& lines) {
    if (!f.hasConfig) return;
    const std::wstring head = L"mod config set " + Set_QuoteArg(f.id) + L" ";
    std::wstring inc = head + L"includeCustom", exc = head + L"excludeCustom";
    for (auto& v : f.includeCustom) inc += L" " + Set_QuoteArg(v);
    for (auto& v : f.excludeCustom) exc += L" " + Set_QuoteArg(v);
    lines.push_back(inc);
    lines.push_back(exc);
    lines.push_back(head + L"includeExcludeCustomOnly " + (f.customOnly ? L"true" : L"false"));
}

// DavidHiFi's whole setup: his own mods from the feed and the library mods he runs. With
// "Clean slate first" every mod here (not this app) is backed up and removed first. Everything
// installs turned off; with his settings, each mod then gets his settings and app lists, and
// the last step turns on the ones he has on. One mod that fails is skipped, not the whole job.
static void Hub_FullSetup(SetWindow& w, bool withConfig) {
    if (g_feed.empty() && g_feedLib.empty()) {
        Set_SetStatus(w, L"DavidHiFi's feed has not been read yet. Choose Check the feed now, then try again.", true); return;
    }
    if (!g_fullArmed || GetTickCount64() - g_fullArmed >= 5000 || g_fullArmedConfig != withConfig) {
        g_fullArmed = GetTickCount64();
        g_fullArmedConfig = withConfig;
        SetTimer(w.hwnd, kHubArmTimer, 5050, nullptr);
        Set_BuildAndClamp(w);
        return;
    }
    g_fullArmed = 0;
    const bool clean = Hub_RegGet(L"Set.cleanSlate", 1) != 0;
    // Copies, not pointers: the feed can land again while the window waits below.
    std::vector<std::pair<std::wstring, std::wstring>> have;  // id, name
    for (auto& m : g_hub.mods)
        if (m.id != kHubSelfId) have.push_back({m.id, m.name.empty() ? m.id : m.name});
    std::vector<HubFeedMod> local, lib, keep;
    for (auto& f : g_feed) (clean || !Hub_FindMod(f.id) ? local : keep).push_back(f);
    for (auto& f : g_feedLib) (clean || !Hub_FindMod(f.id) ? lib : keep).push_back(f);
    if (!withConfig) keep.clear();  // Default settings: mods already here are left alone.
    if (local.empty() && lib.empty() && keep.empty()) { Set_SetStatus(w, L"You already have every one of his mods."); return; }
    // A backup comes first whenever a mod that is here now will change or go.
    std::vector<std::wstring> backupIds;
    if (clean) for (auto& [id, name] : have) backupIds.push_back(id);
    else for (auto& f : keep) backupIds.push_back(f.id);
    std::vector<std::wstring> files;
    std::map<std::wstring, Js> current;
    std::wstring err, restore;
    const bool ready = Hub_WaitRead(w, [&] {
        if (!backupIds.empty() && !Hub_BackupFiles(backupIds, err, &restore)) return false;
        for (auto& f : keep) {
            if (!f.hasPreset) continue;
            Js data;
            if (!Hub_Cli(L"mod settings get " + Set_QuoteArg(f.id), data, err)) return false;
            if (const Js* s = data.get(L"settings")) current[f.id] = *s;
        }
        return Hub_FeedFetch(local, files, err);
    }, L"Saving a backup and downloading DavidHiFi's mods...");
    std::vector<std::wstring> temp = files;
    auto cleanup = [&] { for (auto& p : temp) if (!p.empty()) DeleteFileW(p.c_str()); };
    if (!ready) { cleanup(); Set_SetStatus(w, err.c_str(), true); return; }
    bool kept = false;
    if (!restore.empty()) {
        const auto before = Hub_PresetDir() + L"\\Before DavidHiFi's whole setup " + std::to_wstring(GetTickCount64()) + L".json";
        kept = CopyFileW(restore.c_str(), before.c_str(), TRUE) != FALSE;
    }
    std::vector<HubBlock> blocks;
    int dropped = 0;
    bool wrote = true;
    // His settings for one mod, laid over what it has now (nothing for a fresh install).
    auto settingsLine = [&](const HubFeedMod& f, std::vector<std::wstring>& lines) {
        if (!withConfig) return;
        if (!f.hasPreset) { Hub_ConfigLines(f, lines); return; }
        const auto it = current.find(f.id);
        int skipped = 0;
        const std::wstring merged = Hub_PresetMerge(f.preset, it == current.end() ? nullptr : &it->second, &skipped);
        dropped += skipped;
        const auto file = Hub_DataDir() + L"\\full-setting-" + std::to_wstring(GetTickCount64()) + L"-" + std::to_wstring(temp.size()) + L".json";
        if (!Hub_WriteFile(file, Hub_Utf8(merged))) { wrote = false; return; }
        temp.push_back(file);
        lines.push_back(L"mod settings write " + Set_QuoteArg(f.id) + L" " + Set_QuoteArg(file));
        Hub_ConfigLines(f, lines);
    };
    if (clean)
        for (auto& [id, name] : have) blocks.push_back({L"Removing " + name, {L"mod remove " + Set_QuoteArg(id) + L" --yes"}});
    for (size_t i = 0; i < local.size(); i++) {
        HubBlock b{local[i].name, {L"@install " + local[i].sha + L" " + Set_QuoteArg(files[i])}};
        settingsLine(local[i], b.lines);
        blocks.push_back(std::move(b));
    }
    for (auto& f : lib) {
        // His exact version first; if the library no longer has it, the newest one.
        const std::wstring base = L"mod install " + Set_QuoteArg(f.id);
        HubBlock b{f.name, {f.version.empty() ? base + L" --disabled"
                                              : base + L" " + Set_QuoteArg(f.version) + L" --disabled\t" + base + L" --disabled"}};
        settingsLine(f, b.lines);
        blocks.push_back(std::move(b));
    }
    for (auto& f : keep) {
        HubBlock b{f.name, {}};
        settingsLine(f, b.lines);
        if (!b.lines.empty()) blocks.push_back(std::move(b));
    }
    if (!wrote) { cleanup(); Set_SetStatus(w, L"Could not prepare the settings. Nothing changed.", true); return; }
    // On and off last, so a job that stops partway never leaves a half set-up mod running.
    if (withConfig) {
        for (auto* list : {&local, &lib, &keep})
            for (auto& f : *list)
                if (f.hasPreset && (f.presetOn || list == &keep))
                    blocks.push_back({f.name, {(f.presetOn ? L"mod enable " : L"mod disable ") + Set_QuoteArg(f.id)}});
    }
    std::vector<size_t> failed;
    const bool ok = Hub_RunBlocks(w, blocks, err, &failed);
    cleanup();
    Hub_RegSet(L"Set.welcomed", 1);
    Hub_LoadList(w);
    Set_BuildAndClamp(w);
    const size_t total = local.size() + lib.size() + keep.size();
    std::wstring done = withConfig ? L"DavidHiFi's whole setup is in place: " + std::to_wstring(total) + L" mods with his settings."
                                   : std::to_wstring(total) + L" mods installed turned off, with their own settings. Turn on the ones you want on the Mods page.";
    if (dropped) done += L" Private settings were left out.";
    if (!restore.empty()) done += kept ? L" Your old mods are saved as a Before preset and a backup." : L" A backup of your old mods is in the Workshop's data folder.";
    if (ok) { Set_SetStatus(w, done.c_str()); return; }
    if (failed.empty()) { Set_SetStatus(w, (err + L" A backup was saved first.").c_str(), true); return; }
    std::set<std::wstring> names;
    for (size_t i : failed) names.insert(blocks[i].name);
    std::wstring list;
    size_t n = 0;
    for (auto& name : names) {
        if (n++ == 5) { list += L" and " + std::to_wstring(names.size() - 5) + L" more"; break; }
        list += (n > 1 ? L", " : L"") + name;
    }
    Set_SetStatus(w, (L"Finished, but " + std::to_wstring(names.size()) + (names.size() == 1 ? L" step" : L" steps") +
                      L" did not work: " + list + L". First problem: " + err + L" Everything else is in place.").c_str(), true);
}

#ifdef HUB_MOD
// The mod build updates itself as a mod: the new .wh.cpp is downloaded, checked against the
// feed's fingerprint and @id, and then installed by Windhawk ("@selfinstall"), which restarts it.
static std::wstring g_selfFile;
static bool Hub_AppUpdate(const HubFeedMod& app, bool, std::wstring& err) {
    std::string raw;
    if (!Hub_Download(app.url, raw, err)) return false;
    if (Hub_Sha256Data(raw) != app.sha) { err = L"The download does not match the feed. Nothing changed."; return false; }
    if (L"local@" + Hub_SourceId(raw) != kHubSelfId) { err = L"The download is not Seamless Workshop. Nothing changed."; return false; }
    const auto dir = Hub_DataDir() + L"\\feed";
    CreateDirectoryW(dir.c_str(), nullptr);
    g_selfFile = dir + L"\\seamless-workshop.wh.cpp";
    if (!Hub_WriteFile(g_selfFile, raw)) { err = L"Could not save the download. Nothing changed."; return false; }
    return true;
}
#else
// Swaps in a new hub.exe. Windows lets a running program be renamed, so the old one moves aside
// and the new one takes its name; on any failure the old one moves back.
static bool Hub_AppUpdate(const HubFeedMod& app, bool relaunch, std::wstring& err) {
    std::string raw;
    if (!Hub_Download(app.url, raw, err)) return false;
    if (Hub_Sha256Data(raw) != app.sha) { err = L"The download does not match the feed. Nothing changed."; return false; }
    if (raw.size() < 4096 || raw[0] != 'M' || raw[1] != 'Z') { err = L"The download is not a program. Nothing changed."; return false; }
    WCHAR self[MAX_PATH]{};
    if (!GetModuleFileNameW(nullptr, self, MAX_PATH)) { err = L"Could not find this program's file."; return false; }
    const std::wstring me = self, old = me + L".old";
    const auto dir = Hub_DataDir() + L"\\feed";
    CreateDirectoryW(dir.c_str(), nullptr);
    const auto fresh = dir + L"\\hub-" + app.version + L".exe";
    if (!Hub_WriteFile(fresh, raw)) { err = L"Could not save the download. Nothing changed."; return false; }
    DeleteFileW(old.c_str());
    if (!MoveFileExW(me.c_str(), old.c_str(), MOVEFILE_REPLACE_EXISTING)) {
        DeleteFileW(fresh.c_str()); err = L"Could not move the current version aside. Nothing changed."; return false;
    }
    if (!CopyFileW(fresh.c_str(), me.c_str(), FALSE)) {
        MoveFileExW(old.c_str(), me.c_str(), MOVEFILE_REPLACE_EXISTING);
        DeleteFileW(fresh.c_str()); err = L"Could not put the new version in place. Nothing changed."; return false;
    }
    DeleteFileW(fresh.c_str());
    if (relaunch) {
        std::wstring cmd = Set_QuoteArg(me) + L" --wait-pid " + std::to_wstring(GetCurrentProcessId());
        STARTUPINFOW si{sizeof(si)};
        PROCESS_INFORMATION pi{};
        if (!CreateProcessW(me.c_str(), cmd.data(), nullptr, nullptr, FALSE, 0, nullptr, nullptr, &si, &pi)) {
            err = L"The new version is in place. Open Seamless Workshop again to use it."; return false;
        }
        CloseHandle(pi.hThread); CloseHandle(pi.hProcess);
    }
    return true;
}
#endif

static std::wstring Hub_PrettySettings(const Js& settings) {
    std::wstring json = L"{";
    for (size_t i = 0; i < settings.a.size(); i++)
        json += (i ? L",\n  " : L"\n  ") + Js_Quote(settings.keys[i]) + L": " + Hub_JsDump(settings.a[i]);
    return json + L"\n}\n";
}

// Writes a whole settings set for the open mod: backup, one admin run, then the page reloads.
static bool Hub_WriteAllSettings(SetWindow& w, const std::wstring& id, const Js& settings, PCWSTR done) {
    std::wstring err;
    const auto file = Hub_DataDir() + L"\\settings-" + std::to_wstring(GetTickCount64()) + L".json";
    if (!Hub_WriteFile(file, Hub_Utf8(Hub_JsDump(settings)))) { Set_SetStatus(w, L"Could not write the settings to disk.", true); return false; }
    if (!Hub_Backup({id}, err)) { DeleteFileW(file.c_str()); Set_SetStatus(w, err.c_str(), true); return false; }
    const bool ok = Hub_RunJob(w, {L"mod settings write " + Set_QuoteArg(id) + L" " + Set_QuoteArg(file)}, err);
    DeleteFileW(file.c_str());
    if (!ok) { Set_SetStatus(w, err.c_str(), true); return false; }
    Hub_LoadList(w);
    Hub_OpenDetail(w, id);
    Set_SetStatus(w, done);
    return true;
}

static bool Hub_FlatSettings(const Js& j) {
    if (j.t != Js::Obj) return false;
    for (auto& v : j.a) if (v.t != Js::Str && v.t != Js::Num) return false;
    return true;
}

static void Hub_Action(SetWindow& w, const std::wstring& action) {
    if (w.saving || g_reading) { Set_SetStatus(w, L"Wait for the current action to finish."); return; }
    Set_CommitEdit(w, true);
    if (Set_ChangedCount(w)) { Set_SetStatus(w, L"Save or cancel your changes before this action.", true); return; }
    if (action == L"hub:market" || action == L"hub:updates") {
        g_repoId.clear(); Hub_StartRead(w, action == L"hub:market" ? L"market" : L"updates", L"repo list");
    } else if (action == L"hub:repoBack") {
        g_repoId.clear(); Set_BuildAndClamp(w);
    } else if (action.find(L"hub:repo:") == 0) {
        g_repoId = action.substr(9); g_repoDetail = L"Reading mod details.";
        if (Hub_ValidId(g_repoId)) Hub_StartRead(w, L"detail", L"repo show " + Set_QuoteArg(g_repoId));
    } else if (action.find(L"hub:install:") == 0 || action.find(L"hub:update:") == 0) {
        const bool install = action.find(L"hub:install:") == 0;
        const auto id = action.substr(install ? 12 : 11);
        if (!Hub_ValidId(id)) return;
        std::wstring err;
        std::wstring args = install ? L"mod install " : L"mod update ";
        bool disabled = install;
        for (auto& m : g_hub.mods) if (m.id == id) disabled = !m.enabled;
        args += Set_QuoteArg(id) + (disabled ? L" --disabled" : L"");
        if (!install) {
            if (!Hub_Backup({id}, err)) { Set_SetStatus(w, err.c_str(), true); return; }
        }
        if (!Hub_RunJob(w, {args}, err)) Set_SetStatus(w, err.c_str(), true);
        else { Hub_LoadList(w); Set_SetStatus(w, install ? L"Installed turned off." : L"Updated. Previous source and settings are saved in backups."); }
    } else if (action == L"hub:presetSave") {
        const auto name = Hub_Input(w, L"hub.presetName");
        std::wstring err;
        if (!Hub_PresetName(name)) { Set_SetStatus(w, L"Use a short preset name with letters, numbers, spaces or hyphens.", true); return; }
        const auto file = Hub_PresetDir() + L"\\" + name + L".json";
        if (GetFileAttributesW(file.c_str()) != INVALID_FILE_ATTRIBUTES) { Set_SetStatus(w, L"That preset exists. Choose another name.", true); return; }
        const auto ids = Hub_SplitIds(Hub_Input(w, L"hub.presetMods"));
        if (g_reader.joinable()) g_reader.join();
        g_reading = true; g_readKind = L"preset"; g_readError.clear(); g_readData = Js{};
        const HWND hwnd = w.hwnd;
        g_reader = std::thread([ids, file, hwnd] {
            Hub_Snapshot(ids, file, g_readError);
            PostMessageW(hwnd, WM_HUB_RESULT, 0, 0);
        });
        Set_BuildAndClamp(w);
    } else if (action.find(L"hub:presetApply:") == 0) {
        Hub_ApplyPreset(w, action.substr(16));
    } else if (action == L"hub:presetFolder") Hub_OpenFile(w.hwnd, Hub_PresetDir());
    else if (action == L"hub:presetImport") {
        WCHAR file[32768]{};
        OPENFILENAMEW ofn{sizeof(ofn)}; ofn.hwndOwner = w.hwnd;
        ofn.lpstrFilter = L"Seamless Workshop presets\0*.json\0\0"; ofn.lpstrFile = file; ofn.nMaxFile = 32768;
        ofn.Flags = OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;
        if (!GetOpenFileNameW(&ofn)) return;
        Js data; std::wstring err;
        if (!Hub_ReadPreset(file, data, err)) { Set_SetStatus(w, err.c_str(), true); return; }
        const auto target = Hub_PresetDir() + L"\\Imported " + std::to_wstring(GetTickCount64()) + L".json";
        if (!CopyFileW(file, target.c_str(), TRUE)) Set_SetStatus(w, L"Could not copy the preset.", true);
        else { Set_BuildAndClamp(w); Set_SetStatus(w, L"Imported. Apply it when ready."); }
    } else if (action == L"hub:check") {
        const auto path = Hub_Input(w, L"hub.devPath");
        if (path.size() < 7 || path.substr(path.size() - 7) != L".wh.cpp") { Set_SetStatus(w, L"Choose a .wh.cpp file first.", true); return; }
        g_checkPendingPath = path; g_checkPendingSha = Hub_Sha256(path);
        Hub_StartRead(w, L"check", L"source meta " + Set_QuoteArg(path) + L" --strict");
    } else if (action == L"hub:stagedInstall") {
        const auto path = Hub_Input(w, L"hub.devPath");
        if (g_checkedSha.empty() || lstrcmpiW(path.c_str(), g_checkedPath.c_str()) != 0) {
            Set_SetStatus(w, L"Check this file first. Install uses the file that passed Check.", true); return;
        }
        if (Hub_Sha256(path) != g_checkedSha) {
            g_checkedPath.clear(); g_checkedSha.clear();
            Set_SetStatus(w, L"The file changed after Check. Check it again.", true); return;
        }
        // A file installed from disk lands as local@<id>, so look for both names.
        std::vector<std::wstring> installed;
        bool enabled = false;
        for (auto& m : g_hub.mods)
            if (m.id == g_checkedId || m.id == L"local@" + g_checkedId) installed.push_back(m.id), enabled |= m.enabled;
        if (enabled) { Set_SetStatus(w, L"Turn the installed copy off before installing over it.", true); return; }
        std::wstring err;
        if (!installed.empty() && !Hub_Backup(installed, err)) { Set_SetStatus(w, err.c_str(), true); return; }
        if (!Hub_RunJob(w, {L"@install " + g_checkedSha + L" " + Set_QuoteArg(path)}, err))
            Set_SetStatus(w, err.c_str(), true);
        else { Hub_LoadList(w); Set_SetStatus(w, L"Installed turned off. Turn it on from the Mods page when ready."); }
    } else if (action == L"hub:glass") {
        Hub_StartTask(w, L"glass", [](Js& data, std::wstring& err) { return Hub_GlassCheck(data, err); });
    } else if (action == L"hub:inspect" || action == L"hub:source" || action == L"hub:compile" ||
               action == L"hub:where" || action == L"hub:release") {
        const auto id = Hub_Input(w, L"hub.devId");
        if (!Hub_ValidId(id)) { Set_SetStatus(w, L"Enter a valid installed mod id.", true); return; }
        if (action == L"hub:inspect") Hub_StartRead(w, L"inspect", L"mod show " + Set_QuoteArg(id));
        else if (action == L"hub:where") Hub_StartTask(w, L"where", [id](Js& d, std::wstring& e) { return Hub_WhereLoaded(id, d, e); });
        else if (action == L"hub:release") Hub_StartTask(w, L"release", [id](Js& d, std::wstring& e) { return Hub_ReleaseCheck(id, d, e); });
        else if (action == L"hub:source") {
            const auto source = L"C:\\ProgramData\\Windhawk\\ModsSource\\" + id + L".wh.cpp";
            if (GetFileAttributesW(source.c_str()) == INVALID_FILE_ATTRIBUTES) Set_SetStatus(w, L"Installed source was not found.", true);
            else Hub_OpenFile(w.hwnd, source);
        } else {
            bool disabled = false;
            for (auto& m : g_hub.mods) if (m.id == id) disabled = !m.enabled;
            if (!disabled) { Set_SetStatus(w, L"Turn this mod off before compiling it.", true); return; }
            std::wstring err;
            if (!Hub_Backup({id}, err)) { Set_SetStatus(w, err.c_str(), true); return; }
            if (!Hub_RunJob(w, {L"@compile " + Set_QuoteArg(id)}, err))
                Set_SetStatus(w, L"Compile did not complete. The PC may be busy. Saved source is in backups.", true);
            else { Hub_LoadList(w); Set_SetStatus(w, L"Compiled. The mod remains turned off."); }
        }
    } else if (action == L"hub:reports") Hub_OpenFile(w.hwnd, Hub_DataDir());
    else if (action == L"hub:stock") Hub_OpenFile(w.hwnd, L"C:\\Program Files\\Windhawk\\windhawk.exe");
    else if (action == L"hub:engineGuide") Hub_OpenFile(w.hwnd, Hub_Tool(L"Tool.engineGuide"));
    else if (action == L"hub:updateAll") {
        std::vector<std::wstring> ids, lines;
        for (auto& m : g_hub.mods) if (m.update && m.id.find(L"local@") != 0 && Hub_ValidId(m.id)) {
            ids.push_back(m.id);
            lines.push_back(L"mod update " + Set_QuoteArg(m.id) + (m.enabled ? L"" : L" --disabled"));
        }
        if (ids.empty()) return;
        std::wstring err;
        if (!Hub_Backup(ids, err)) { Set_SetStatus(w, err.c_str(), true); return; }
        const bool ok = Hub_RunJob(w, lines, err);
        Hub_LoadList(w);
        Set_SetStatus(w, ok ? L"Updated. Previous sources and settings are saved in backups." : (err + L" Mods before the failed one are updated.").c_str(), !ok);
    } else if (action.find(L"hub:feed:") == 0) {
        const auto id = action.substr(9);
        for (auto& f : g_feed) if (f.id == id) { Hub_FeedInstall(w, {f}); return; }
    } else if (action == L"hub:feedAll") {
        std::vector<HubFeedMod> list;
        for (auto& f : g_feed) if (const HubMod* m = Hub_FindMod(f.id); m && Hub_Newer(f.version, m->version)) list.push_back(f);
        Hub_FeedInstall(w, list);
    } else if (action == L"hub:feedCheck") {
        if (!g_feedBusy) Hub_FeedStart(w.hwnd, true);
        Set_BuildAndClamp(w);
    } else if (action == L"hub:appUpdate") {
        if (!Hub_AppNewer()) return;
        std::wstring err;
        const HubFeedMod app = g_feedApp;
        if (!Hub_WaitRead(w, [&] { return Hub_AppUpdate(app, true, err); }, L"Downloading Seamless Workshop...")) {
            Set_SetStatus(w, err.c_str(), true); return;
        }
#ifdef HUB_MOD
        // Runs last, after this returns: Windhawk replaces the running mod and starts it again.
        if (!Hub_RunJob(w, {L"@selfinstall " + app.sha + L" " + Set_QuoteArg(g_selfFile)}, err)) {
            Set_SetStatus(w, err.c_str(), true); return;
        }
        Set_SetStatus(w, (L"Installing Seamless Workshop " + app.version + L". It restarts in a moment.").c_str());
#else
        g_hub.quitting = true;
        PostMessageW(w.hwnd, WM_CLOSE, 0, 0);
#endif
    } else if (action == L"hub:export") {
        WCHAR file[MAX_PATH] = L"Windhawk backup.zip";
        OPENFILENAMEW ofn{sizeof(ofn)}; ofn.hwndOwner = w.hwnd;
        ofn.lpstrFilter = L"Windhawk backups\0*.zip\0\0"; ofn.lpstrFile = file; ofn.nMaxFile = MAX_PATH;
        ofn.lpstrDefExt = L"zip"; ofn.Flags = OFN_OVERWRITEPROMPT | OFN_NOCHANGEDIR | OFN_PATHMUSTEXIST;
        if (!GetSaveFileNameW(&ofn)) return;
        g_exportFile = file;
        Hub_StartRead(w, L"export", L"data export --out " + Set_QuoteArg(file) + L" --force --mods all");
    } else if (action == L"hub:restorePick") {
        WCHAR file[MAX_PATH]{};
        OPENFILENAMEW ofn{sizeof(ofn)}; ofn.hwndOwner = w.hwnd;
        ofn.lpstrFilter = L"Windhawk backups\0*.zip\0\0"; ofn.lpstrFile = file; ofn.nMaxFile = MAX_PATH;
        ofn.Flags = OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;
        if (!GetOpenFileNameW(&ofn)) return;
        g_restorePending = file; g_restoreFile.clear(); g_restoreArmed = 0;
        Hub_StartRead(w, L"archive", L"data inspect " + Set_QuoteArg(file));
    } else if (action == L"hub:restore") {
        if (g_restoreFile.empty()) return;
        if (!g_restoreArmed || GetTickCount64() - g_restoreArmed >= 5000) {
            g_restoreArmed = GetTickCount64();
            SetTimer(w.hwnd, kHubArmTimer, 5050, nullptr);
            Set_BuildAndClamp(w);
            return;
        }
        g_restoreArmed = 0;
        std::wstring err;
        const auto safety = Hub_DataDir() + L"\\Before restore " + std::to_wstring(GetTickCount64()) + L".zip";
        Js ignored;
        if (!Hub_WaitRead(w, [&] { return Hub_Cli(L"data export --out " + Set_QuoteArg(safety) + L" --force --mods all", ignored, err); },
                          L"Saving the current mods first...")) {
            Set_SetStatus(w, (L"Could not save the current mods, so nothing was restored. " + err).c_str(), true); return;
        }
        const bool ok = Hub_RunJob(w, {L"data import " + Set_QuoteArg(g_restoreFile) + L" --mods all --no-app-settings --yes"}, err);
        Hub_LoadList(w);
        g_featureStatus = ok ? L"Restored. The state before it is saved in backups as " + safety.substr(safety.rfind(L'\\') + 1) + L"."
                             : L"Restore failed: " + err + L" The state before it is saved in backups.";
        g_restoreFile.clear();
        Set_BuildAndClamp(w);
        Set_SetStatus(w, ok ? L"Restored." : err.c_str(), !ok);
    } else if (action == L"hub:versions") {
        if (Hub_ValidId(g_hub.detailId)) Hub_StartRead(w, L"versions", L"repo versions " + Set_QuoteArg(g_hub.detailId));
    } else if (action.find(L"hub:version:") == 0) {
        const auto ver = action.substr(12), id = g_hub.detailId;
        bool listed = false;
        for (auto& v : g_versions) listed |= v.first == ver;
        if (!listed || !Hub_ValidId(id)) return;
        const HubMod* m = Hub_FindMod(id);
        if (!m) return;
        std::wstring err;
        if (!Hub_Backup({id}, err)) { Set_SetStatus(w, err.c_str(), true); return; }
        const bool ok = Hub_RunJob(w, {L"mod install " + Set_QuoteArg(id) + L" " + ver + (m->enabled ? L"" : L" --disabled")}, err);
        Hub_LoadList(w);
        Hub_OpenDetail(w, id);
        g_featureStatus = ok ? L"Version " + ver + L" is installed. The previous copy is in backups." : err;
        Set_BuildAndClamp(w);
    } else if (action == L"hub:detailSource") {
        const auto source = L"C:\\ProgramData\\Windhawk\\ModsSource\\" + g_hub.detailId + L".wh.cpp";
        if (!Hub_ValidId(g_hub.detailId) || !Hub_FileThere(source)) Set_SetStatus(w, L"Installed source was not found.", true);
        else Hub_OpenFile(w.hwnd, source);
    } else if (action == L"hub:settingsEdit") {
        const auto id = g_hub.detailId;
        if (!Hub_ValidId(id)) return;
        Js data; std::wstring err;
        if (!Hub_WaitRead(w, [&] { return Hub_Cli(L"mod settings get " + Set_QuoteArg(id), data, err); }, L"Reading settings...")) {
            Set_SetStatus(w, err.c_str(), true); return;
        }
        const Js* settings = data.get(L"settings");
        Js empty; empty.t = Js::Obj;
        const auto file = Hub_EditFile(id);
        if (!Hub_WriteFile(file, Hub_Utf8(Hub_PrettySettings(settings && settings->t == Js::Obj ? *settings : empty)))) {
            Set_SetStatus(w, L"Could not write the settings file.", true); return;
        }
        Hub_OpenFile(w.hwnd, file);
        Set_BuildAndClamp(w);
        Set_SetStatus(w, L"Opened in your editor. Save it, then choose Load edited settings.");
    } else if (action == L"hub:settingsLoad") {
        const auto id = g_hub.detailId;
        const auto file = Hub_EditFile(id);
        std::string raw; Js data;
        if (!Hub_ValidId(id) || !Hub_ReadFile(file, raw)) { Set_SetStatus(w, L"The edited file was not found.", true); return; }
        if (raw.rfind("\xEF\xBB\xBF", 0) == 0) raw.erase(0, 3);
        if (!Js_Parse(Hub_Wide(raw), data) || !Hub_FlatSettings(data)) {
            Set_SetStatus(w, L"The file is not valid. Each line needs \"name\": value, with commas between lines. Nothing changed.", true); return;
        }
        if (Hub_WriteAllSettings(w, id, data, L"Loaded. The previous settings are in backups.")) {
            DeleteFileW(file.c_str());
            Set_BuildAndClamp(w);
        }
    } else if (action == L"hub:davidPreset") {
        const auto id = g_hub.detailId;
        const HubFeedMod* f = Hub_FeedFind(id);
        if (!Hub_ValidId(id) || !f || !f->hasPreset || !Hub_FindMod(id)) return;
        const HubFeedMod feed = *f;
        Js data; std::wstring err;
        const auto before = Hub_PresetDir() + L"\\Before DavidHiFi " + std::to_wstring(GetTickCount64()) + L".json";
        if (!Hub_WaitRead(w, [&] {
                return Hub_Snapshot({id}, before, err) && Hub_Cli(L"mod settings get " + Set_QuoteArg(id), data, err);
            }, L"Saving your current settings first...")) {
            Set_SetStatus(w, err.c_str(), true); return;
        }
        int dropped = 0;
        const std::wstring merged = Hub_PresetMerge(feed.preset, data.get(L"settings"), &dropped);
        Js settings;
        if (!Js_Parse(merged, settings) || !Hub_FlatSettings(settings)) {
            Set_SetStatus(w, L"DavidHiFi's settings for this mod could not be read. Nothing changed.", true); return;
        }
        Hub_WriteAllSettings(w, id, settings, dropped
            ? L"Done. Private settings were left as yours. Your old settings are saved as a Before preset."
            : L"Done. Your old settings are saved as a Before preset.");
    } else if (action == L"hub:cleanSlate") {
        Hub_RegSet(L"Set.cleanSlate", Hub_RegGet(L"Set.cleanSlate", 1) ? 0 : 1);
        g_fullArmed = 0;
        Set_BuildAndClamp(w);
    } else if (action == L"hub:fullSetup:config" || action == L"hub:fullSetup:plain") {
        Hub_FullSetup(w, action == L"hub:fullSetup:config");
    } else if (action == L"hub:davidSetup") {
        if (!g_setupArmed || GetTickCount64() - g_setupArmed >= 5000) {
            g_setupArmed = GetTickCount64();
            SetTimer(w.hwnd, kHubArmTimer, 5050, nullptr);
            Set_BuildAndClamp(w);
            return;
        }
        g_setupArmed = 0;
        // Only DavidHiFi's feed mods are touched: missing ones are installed turned off, then each
        // one with a preset gets his settings and his on/off state.
        std::vector<HubFeedMod> missing, preset;
        std::vector<std::wstring> installed;
        for (auto& f : g_feed) {
            if (!Hub_FindMod(f.id)) missing.push_back(f);
            else installed.push_back(f.id);
            if (f.hasPreset) preset.push_back(f);
        }
        if (missing.empty() && preset.empty()) { Set_SetStatus(w, L"The feed has nothing to set up."); return; }
        std::vector<std::wstring> files;
        std::map<std::wstring, Js> current;
        std::wstring err;
        const auto before = Hub_PresetDir() + L"\\Before DavidHiFi setup " + std::to_wstring(GetTickCount64()) + L".json";
        const bool ready = Hub_WaitRead(w, [&] {
            if (!installed.empty() && !Hub_Snapshot(installed, before, err, installed.size())) return false;
            for (auto& f : preset) {
                if (!Hub_FindMod(f.id)) continue;
                Js data;
                if (!Hub_Cli(L"mod settings get " + Set_QuoteArg(f.id), data, err)) return false;
                if (const Js* s = data.get(L"settings")) current[f.id] = *s;
            }
            return Hub_FeedFetch(missing, files, err);
        }, L"Saving your current settings and downloading...");
        std::vector<std::wstring> temp = files;
        auto cleanup = [&] { for (auto& p : temp) if (!p.empty()) DeleteFileW(p.c_str()); };
        if (!ready) { cleanup(); Set_SetStatus(w, err.c_str(), true); return; }
        std::vector<std::wstring> lines;
        for (size_t i = 0; i < missing.size(); i++) lines.push_back(L"@install " + missing[i].sha + L" " + Set_QuoteArg(files[i]));
        int dropped = 0;
        for (size_t i = 0; i < preset.size(); i++) {
            const auto it = current.find(preset[i].id);
            int skipped = 0;
            const std::wstring merged = Hub_PresetMerge(preset[i].preset, it == current.end() ? nullptr : &it->second, &skipped);
            dropped += skipped;
            const auto file = Hub_DataDir() + L"\\david-setting-" + std::to_wstring(GetTickCount64()) + L"-" + std::to_wstring(i) + L".json";
            if (!Hub_WriteFile(file, Hub_Utf8(merged))) {
                cleanup(); Set_SetStatus(w, L"Could not prepare the settings. Nothing changed.", true); return;
            }
            temp.push_back(file);
            lines.push_back(L"mod settings write " + Set_QuoteArg(preset[i].id) + L" " + Set_QuoteArg(file));
            lines.push_back((preset[i].presetOn ? L"mod enable " : L"mod disable ") + Set_QuoteArg(preset[i].id));
        }
        const bool ok = Hub_RunJob(w, lines, err);
        cleanup();
        Hub_LoadList(w);
        Set_BuildAndClamp(w);
        std::wstring done = L"DavidHiFi's setup is in place.";
        if (dropped) done += L" Private settings were left as yours.";
        if (!installed.empty()) done += L" Your old settings are saved as a Before preset.";
        if (ok) Hub_RegSet(L"Set.welcomed", 1);
        Set_SetStatus(w, ok ? done.c_str() : (err + L" Use the Before preset to go back.").c_str(), !ok);
    } else if (action == L"hub:welcomePick") {
        // Welcome card: show only his mods in Marketplace, so they are easy to pick from.
        Hub_RegSet(L"Set.welcomed", 1);
        if (SetField* show = Hub_Field(w, L"hub.marketShow")) show->cur = show->value = L"mine";
        Set_GoPage(w, 1);
    } else if (action == L"hub:welcomeDone") {
        Hub_RegSet(L"Set.welcomed", 1);
        Set_BuildAndClamp(w);
    } else if (action == L"hub:removeAll") {
        const std::vector<std::wstring> ids = Hub_DavidIds();
        if (ids.empty()) { Set_SetStatus(w, L"None of DavidHiFi's mods are installed."); return; }
        if (!g_removeAllArmed || GetTickCount64() - g_removeAllArmed >= 5000) {
            g_removeAllArmed = GetTickCount64();
            SetTimer(w.hwnd, kHubArmTimer, 5050, nullptr);
            Set_BuildAndClamp(w);
            return;
        }
        g_removeAllArmed = 0;
        // Backup first: the installed source and every setting. The settings also go to the
        // Presets page as a Before preset, so putting them back is one click there.
        std::wstring err, restore;
        if (!Hub_WaitRead(w, [&] { return Hub_BackupFiles(ids, err, &restore); }, L"Saving a backup of his mods...")) {
            Set_SetStatus(w, err.c_str(), true); return;
        }
        const auto before = Hub_PresetDir() + L"\\Before removing DavidHiFi's mods " + std::to_wstring(GetTickCount64()) + L".json";
        const bool kept = CopyFileW(restore.c_str(), before.c_str(), TRUE);
        std::vector<std::wstring> lines;
        for (auto& id : ids) lines.push_back(L"mod remove " + Set_QuoteArg(id) + L" --yes");
        const bool ok = Hub_RunJob(w, lines, err);
        Hub_LoadList(w);
        Set_BuildAndClamp(w);
        std::wstring done = L"Removed " + std::to_wstring(ids.size()) + (ids.size() == 1 ? L" mod." : L" mods.");
        done += kept ? L" Their settings are saved as a Before preset on the Presets page." : L" A backup is in the Workshop's data folder.";
        Set_SetStatus(w, ok ? done.c_str() : (err + L" A backup was saved first.").c_str(), !ok);
    } else if (action == L"hub:settingsReset") {
        const auto id = g_hub.detailId;
        if (!Hub_ValidId(id)) return;
        if (!g_resetArmed || GetTickCount64() - g_resetArmed >= 5000) {
            g_resetArmed = GetTickCount64();
            SetTimer(w.hwnd, kHubArmTimer, 5050, nullptr);
            Set_BuildAndClamp(w);
            return;
        }
        g_resetArmed = 0;
        Js data; std::wstring err;
        if (!Hub_WaitRead(w, [&] { return Hub_Cli(L"mod settings defaults " + Set_QuoteArg(id), data, err); }, L"Reading defaults...")) {
            Set_SetStatus(w, err.c_str(), true); return;
        }
        const Js* settings = data.get(L"settings");
        if (!settings || !Hub_FlatSettings(*settings)) { Set_SetStatus(w, L"This mod's defaults could not be read. Nothing changed.", true); return; }
        Hub_WriteAllSettings(w, id, *settings, L"Every setting is back to its default. The previous settings are in backups.");
    }
}

static bool Hub_DiscordSend(DWORD opcode, const std::string& json) {
    if (g_discord == INVALID_HANDLE_VALUE) return false;
    DWORD header[2] = {opcode, (DWORD)json.size()}, done = 0;
    std::string frame((const char*)header, sizeof(header)); frame += json;
    return WriteFile(g_discord, frame.data(), (DWORD)frame.size(), &done, nullptr) && done == frame.size();
}

static void Hub_ClearPresence() {
    if (g_discord == INVALID_HANDLE_VALUE) return;
    Hub_DiscordSend(1, "{\"cmd\":\"SET_ACTIVITY\",\"args\":{\"pid\":" + std::to_string(GetCurrentProcessId()) +
                       ",\"activity\":null},\"nonce\":\"clear\"}");
    CloseHandle(g_discord); g_discord = INVALID_HANDLE_VALUE;
    g_discordId.clear();
    g_discordBuffer.clear(); g_discordReady = false; g_discordSent = 0;
}

static void Hub_Presence() {
    if (!Hub_AppInt(L"discordPresence", 0)) { Hub_ClearPresence(); return; }
    const std::wstring id = kDiscordAppId;
    static const long long since = [] {
        FILETIME ft; GetSystemTimeAsFileTime(&ft);
        ULARGE_INTEGER u{}; u.LowPart = ft.dwLowDateTime; u.HighPart = ft.dwHighDateTime;
        return (long long)((u.QuadPart - 116444736000000000ull) / 10000000ull);
    }();
    if (g_discord == INVALID_HANDLE_VALUE) {
        if (GetTickCount64() < g_discordRetry) return;
        g_discordRetry = GetTickCount64() + 15000;
        for (int i = 0; i < 10; i++) {
            auto pipe = L"\\\\.\\pipe\\discord-ipc-" + std::to_wstring(i);
            g_discord = CreateFileW(pipe.c_str(), GENERIC_READ | GENERIC_WRITE, 0, nullptr, OPEN_EXISTING, 0, nullptr);
            if (g_discord != INVALID_HANDLE_VALUE) break;
        }
        if (g_discord == INVALID_HANDLE_VALUE) return;
        DWORD mode = PIPE_READMODE_BYTE | PIPE_NOWAIT;
        if (!SetNamedPipeHandleState(g_discord, &mode, nullptr, nullptr)) { CloseHandle(g_discord); g_discord = INVALID_HANDLE_VALUE; return; }
        g_discordId = id;
        if (!Hub_DiscordSend(0, "{\"v\":1,\"client_id\":" + Hub_Utf8(Js_Quote(id)) + "}")) { Hub_ClearPresence(); return; }
    }
    char incoming[8192]; DWORD available = 0, read = 0;
    if (!PeekNamedPipe(g_discord, nullptr, 0, nullptr, &available, nullptr)) { Hub_ClearPresence(); return; }
    if (available && ReadFile(g_discord, incoming, std::min<DWORD>(available, sizeof(incoming)), &read, nullptr))
        g_discordBuffer.append(incoming, read);
    if (g_discordBuffer.size() > 65536) { Hub_ClearPresence(); return; }
    for (int count = 0; count < 8 && g_discordBuffer.size() >= 8; ++count) {
        DWORD header[2]; memcpy(header, g_discordBuffer.data(), 8);
        if (header[1] > 65528) { Hub_ClearPresence(); return; }
        if (g_discordBuffer.size() < 8 + header[1]) break;
        auto payload = g_discordBuffer.substr(8, header[1]);
        g_discordBuffer.erase(0, 8 + header[1]);
        if (header[0] == 2) { Hub_ClearPresence(); return; }
        if (header[0] == 3) Hub_DiscordSend(4, payload);
        if (header[0] == 1) {
            Js reply;
            if (Js_Parse(Hub_Wide(payload), reply) && Js_Text(reply.get(L"evt")) == L"READY") g_discordReady = true;
            if (Js_Text(reply.get(L"evt")) == L"ERROR") { Hub_ClearPresence(); return; }
        }
    }
    if (!g_discordReady || GetTickCount64() < g_discordSent + 30000) return;
    const std::string payload = "{\"cmd\":\"SET_ACTIVITY\",\"args\":{\"pid\":" + std::to_string(GetCurrentProcessId()) +
        ",\"activity\":{\"details\":\"Setting up Windhawk mods\",\"assets\":{\"large_image\":\"logo\",\"large_text\":\"Seamless Workshop\"},"
        "\"timestamps\":{\"start\":" + std::to_string(since) + "}}},\"nonce\":\"" + std::to_string(GetTickCount64()) + "\"}";
    if (!Hub_DiscordSend(1, payload)) Hub_ClearPresence();
    else g_discordSent = GetTickCount64();
}
// ---- end of features.inc ----
// ---- cards.inc (inlined) ----
// Seamless Workshop 1.1: the Mods and Marketplace pages as a full-width card grid or list,
// with one toolbar line (search, Show, Sort into, Grid or List). Toolbar choices apply at once.

static std::wstring g_cardArmId;         // The mod whose bin was clicked once.
static ULONGLONG g_cardArmAt = 0;
static std::wstring g_cfFamily;
static SetCom<IDWriteTextFormat> g_cfName, g_cfMeta, g_cfDesc, g_cfBtn;

constexpr float kCardMin = 300, kCardGap = 16, kCardH = 188, kListH = 68, kBarH = 40, kCardPad = 18;
enum { kBtnDetails, kBtnSettings, kBtnSource, kBtnRemove, kBtnUpdate, kBtnInstall };

static bool Hub_ListPage(const SetWindow& w) {
    return (w.page == 0 && g_hub.detail < 0) || (w.page == 1 && g_repoId.empty());
}

static float Hub_MaxW(const SetWindow& w) { return Hub_ListPage(w) ? 1680.0f : kSetMaxW; }

static bool Hub_KeyIs(const SetField& f, PCWSTR key) { return f.key && wcscmp(f.key, key) == 0; }

static bool Hub_IsBar(const SetField& f) {
    return f.hub == 2 || Hub_KeyIs(f, L"hub.marketSearch") || Hub_KeyIs(f, L"hub.marketShow") ||
           Hub_KeyIs(f, L"hub.marketView");
}

static bool Hub_IsView(const SetField& f) { return Hub_KeyIs(f, L"hub.view") || Hub_KeyIs(f, L"hub.marketView"); }

static bool Hub_BarBox(const SetField& f, const D2D1_RECT_F& row, D2D1_RECT_F& box) {
    if (!Hub_IsBar(f)) return false;
    box = row;
    if (f.kind == SetField::Text) box.left += 26;  // Room for the magnifier; the edit box starts after it.
    return true;
}

// A link that is a library or feed mod: drawn as a card.
static bool Hub_LinkCard(const SetItem& it) {
    return it.type == SetItem::Link && (it.url.rfind(L"hub:repo:", 0) == 0 || it.url.rfind(L"hub:feed:", 0) == 0);
}

static bool Hub_IsCard(const SetWindow& w, const SetItem& it) {
    if (it.type == SetItem::Row) return w.fields[it.field].hub == 1;
    return Hub_LinkCard(it);
}

static void Hub_CardFonts(const SetWindow& w) {
    if (g_cfFamily == w.family && g_cfName) return;
    g_cfFamily = w.family;
    g_cfName = Set_Fmt(w.family, 15.5f, 600, false, DWRITE_TEXT_ALIGNMENT_LEADING, true);
    g_cfMeta = Set_Fmt(w.family, 12, 500, false, DWRITE_TEXT_ALIGNMENT_LEADING, true);
    g_cfBtn = Set_Fmt(w.family, 12.5f, 600, false, DWRITE_TEXT_ALIGNMENT_CENTER, true);
    g_cfDesc = Set_Fmt(w.family, 12.5f, 500, true);
    if (g_cfDesc) {
        SetCom<IDWriteInlineObject> sign;
        g_setDw->CreateEllipsisTrimmingSign(g_cfDesc.get(), sign.put());
        DWRITE_TRIMMING t{DWRITE_TRIMMING_GRANULARITY_WORD, 0, 0};
        g_cfDesc->SetTrimming(&t, sign.get());
    }
}

// ---- Layout: the toolbar on one line, then cards in a fluid grid or a single list ----

static void Hub_Reflow(SetWindow& w, float& y) {
    if (!Hub_ListPage(w)) return;
    size_t s = 0;
    while (s < w.items.size() && !(w.items[s].type == SetItem::Row && Hub_IsBar(w.fields[w.items[s].field]))) s++;
    if (s == w.items.size()) return;
    float top = w.items[s].y;
    if (s > 0 && w.items[s - 1].type == SetItem::Group) {  // The toolbar needs no heading.
        top = w.items[s - 1].y;
        w.items.erase(w.items.begin() + (s - 1));
        s--;
    }
    const float X = w.contentX, W = w.contentW, gap = 10;
    size_t e = s;
    while (e < w.items.size() && w.items[e].type == SetItem::Row && Hub_IsBar(w.fields[w.items[e].field])) e++;
    // A drop-down is as wide as its label plus its longest option (the font is monospaced).
    auto want = [&](const SetField& f) {
        if (f.kind == SetField::Check) return 96.0f;
        if (f.kind != SetField::Choice) return 0.0f;
        size_t longest = 0;
        for (const auto& o : f.options) longest = std::max(longest, wcslen(o.second));
        return std::clamp((float)(wcslen(f.label) + longest) * 8.6f + 76.0f, 200.0f, 360.0f);
    };
    float fixed = 0;
    for (size_t i = s; i < e; i++) {
        const SetField& f = w.fields[w.items[i].field];
        if (f.kind != SetField::Text) fixed += want(f) + gap;
    }
    float cx = X, cy = top;
    const bool oneLine = W - fixed >= 260;
    for (size_t i = s; i < e; i++) {
        SetItem& it = w.items[i];
        const SetField& f = w.fields[it.field];
        float fw = f.kind == SetField::Text ? (oneLine ? W - fixed : W) : std::min(want(f), W);
        if (cx > X && cx + fw > X + W + 0.5f) { cx = X; cy += kBarH + gap; }
        it.x = cx; it.w = fw; it.y = cy; it.h = kBarH;
        cx += fw + gap;
    }
    y = cy + kBarH + 20;

    const bool grid = g_cardsGrid;
    const int cols = grid ? std::clamp((int)((W + kCardGap) / (kCardMin + kCardGap)), 1, 6) : 1;
    const float cw = (W - kCardGap * (cols - 1)) / cols, ch = grid ? kCardH : kListH, rowGap = grid ? kCardGap : kSetRowGap;
    int col = 0;
    bool first = true;
    auto flush = [&] {
        if (col) { y += ch + rowGap; col = 0; }
    };
    for (size_t i = e; i < w.items.size(); i++) {
        SetItem& it = w.items[i];
        if (Hub_IsCard(w, it)) {
            it.x = X + col * (cw + kCardGap); it.w = cw; it.y = y; it.h = ch;
            if (++col == cols) flush();
        } else {
            flush();
            it.x = X; it.w = W;
            if (it.type == SetItem::Group) {
                y += first ? 0 : 14;
                it.y = y;
                y += it.h + 8;
            } else {
                it.y = y;
                y += it.h + kSetRowGap;
            }
        }
        first = false;
    }
    flush();
}

// ---- Card parts, shared by drawing and hit testing ----

struct HubBtn { D2D1_RECT_F r; int id; PCWSTR label; WCHAR glyph; };
struct HubCardParts {
    D2D1_RECT_F sw{}, name{}, meta{}, desc{};
    bool hasSwitch = false;
    HubBtn btn[6];
    int n = 0;
};

static float Hub_BtnW(PCWSTR label) { return Set_TextW(g_cfBtn.get(), label) + 26; }

// Buttons are laid from the right edge leftwards; the ones that do not fit are dropped,
// Details first (a click on the card opens it too).
static HubCardParts Hub_CardParts(const SetWindow& w, const SetItem& it, const D2D1_RECT_F& r) {
    Hub_CardFonts(w);
    HubCardParts c;
    const bool grid = g_cardsGrid;
    std::vector<HubBtn> want;
    if (it.type == SetItem::Row) {
        const SetField& f = w.fields[it.field];
        const HubMod& m = g_hub.mods[f.mod];
        const HubFeedMod* feed = Hub_FeedFind(m.id);
        const bool upd = m.update || (feed && Hub_Newer(feed->version, m.version));
        c.hasSwitch = true;
        if (upd) want.push_back({{}, kBtnUpdate, L"Update", 0});
        want.push_back({{}, kBtnDetails, L"Details", 0});
        want.push_back({{}, kBtnSettings, L"Settings", 0});
        want.push_back({{}, kBtnSource, nullptr, 0xE943});
        want.push_back({{}, kBtnRemove, nullptr, 0xE74D});
    } else {
        const std::wstring id = it.url.substr(9);
        if (it.url.rfind(L"hub:feed:", 0) == 0) {
            const HubMod* m = Hub_FindMod(id);
            const HubFeedMod* f = Hub_FeedFind(id);
            if (!m) want.push_back({{}, kBtnInstall, L"Install", 0});
            else if (f && Hub_Newer(f->version, m->version)) want.push_back({{}, kBtnUpdate, L"Update", 0});
            else want.push_back({{}, kBtnDetails, L"Open", 0});
        } else if (!Hub_FindMod(id)) {
            want.push_back({{}, kBtnInstall, L"Install", 0});
        }
    }
    const float bh = 30;
    float right = r.right - kCardPad, left = r.left + kCardPad;
    float by = grid ? r.bottom - 16 - bh : (r.top + r.bottom) / 2 - bh / 2;
    if (c.hasSwitch) {
        c.sw = grid ? D2D1_RECT_F{right - 40, r.top + 18, right, r.top + 40}
                    : D2D1_RECT_F{right - 40, (r.top + r.bottom) / 2 - 11, right, (r.top + r.bottom) / 2 + 11};
        if (!grid) right = c.sw.left - 18;
    }
    // Widest set that fits: drop Details, then Settings, if the card is narrow.
    float limit = grid ? left : left + std::min(220.0f, (r.right - r.left) * 0.35f);
    auto total = [&](const std::vector<HubBtn>& v) {
        float t = 0;
        for (auto& b : v) t += (b.label ? Hub_BtnW(b.label) : bh) + 6;
        return t;
    };
    for (int drop : {kBtnDetails, kBtnSettings})
        if (right - total(want) < limit)
            for (size_t i = 0; i < want.size(); i++)
                if (want[i].id == drop) { want.erase(want.begin() + i); break; }
    // Text buttons sit on the left of a grid card, icon buttons on the right.
    float lx = left, rx = right;
    if (grid) {
        for (auto it2 = want.rbegin(); it2 != want.rend(); ++it2)
            if (!it2->label) { it2->r = {rx - bh, by, rx, by + bh}; rx -= bh + 6; }
        for (auto& b : want)
            if (b.label) { float bw = Hub_BtnW(b.label); b.r = {lx, by, lx + bw, by + bh}; lx += bw + 6; }
    } else {
        for (auto it2 = want.rbegin(); it2 != want.rend(); ++it2) {
            float bw = it2->label ? Hub_BtnW(it2->label) : bh;
            it2->r = {rx - bw, by, rx, by + bh};
            rx -= bw + 6;
        }
    }
    for (auto& b : want) if (c.n < 6) c.btn[c.n++] = b;
    const float textR = grid ? (c.hasSwitch ? c.sw.left - 12 : r.right - kCardPad) : rx - 12;
    if (grid) {
        c.name = {left, r.top + 15, textR, r.top + 39};
        c.meta = {left, r.top + 39, r.right - kCardPad, r.top + 57};
        c.desc = {left, r.top + 64, r.right - kCardPad, by - 10};
    } else {
        c.name = {left, r.top + 11, textR, r.top + 35};
        c.meta = {left, r.top + 35, textR, r.top + 55};
    }
    return c;
}

static int Hub_BtnHoverId(int k, int b) { return 20000 + k * 8 + b; }
static int Hub_LinkBtnHoverId(int i, int b) { return 40000 + i * 8 + b; }

static void Hub_DrawBtn(SetPaint& p, SetWindow& w, const HubBtn& b, int hoverId, bool armed) {
    const float g = Set_GlowOf(w, hoverId);
    const bool accent = b.id == kBtnUpdate || b.id == kBtnInstall;
    p.Round(b.r, 8, kSetBoxFill);
    if (accent) p.GradFill(b.r, 8, 0.22f + 0.2f * g);
    if (armed) p.Round(b.r, 8, mocha::red, 0.22f);
    p.Edge(b.r, 8, armed ? mocha::red : mocha::overlay0, (armed ? 0.9f : 0.6f) * (1 - g), 1.25f);
    p.GradRing(b.r, 8, g, 1.5f);
    const UINT32 c = armed ? mocha::red : accent ? mocha::text : mocha::subtext1;
    if (b.label) p.Text(g_cfBtn.get(), b.label, b.r, c);
    else p.Glyph(w.fIconS.get(), b.glyph, b.r, c);
}

static void Hub_DrawSwitch(SetPaint& p, SetWindow& w, int k, const D2D1_RECT_F& tr) {
    const bool on = w.fields[k].cur == L"1";
    const float kn = w.knob.count(k) ? w.knob.at(k) : (on ? 1.0f : 0.0f);
    p.Round(tr, 11, mocha::surface1);
    p.GradFill(tr, 11, kn);
    p.GradRing(tr, 11, Set_GlowOf(w, 6000 + k) * 0.8f, 1.25f);
    const float cx = tr.left + 11 + kn * 18, cy = (tr.top + tr.bottom) / 2;
    p.rt->FillEllipse(D2D1::Ellipse(D2D1::Point2F(cx, cy), 8, 8), p.B(on ? mocha::crust : mocha::text));
}

static void Hub_CardBack(SetPaint& p, const D2D1_RECT_F& r, float hov, bool focus) {
    p.Round(r, 12, mocha::base);
    p.Round(r, 12, mocha::surface0, 0.32f);
    p.Edge(r, 12, mocha::surface2, 0.55f * (1 - hov), 1.5f);
    p.GradFill(r, 12, 0.10f * hov);
    p.GradRing(r, 12, hov, 1.5f);
    if (focus) p.GradRing(r, 12, 1.0f, 2.0f);
}

static void Hub_DrawModCard(SetPaint& p, SetWindow& w, const SetItem& it) {
    const int k = it.field;
    const SetField& f = w.fields[k];
    const HubMod& m = g_hub.mods[f.mod];
    const D2D1_RECT_F r = Set_RowRect(w, it);
    float hov = Set_GlowOf(w, 1000 + k);
    for (int b = 0; b < 8; b++) hov = std::max(hov, Set_GlowOf(w, Hub_BtnHoverId(k, b)));
    hov = std::max(hov, Set_GlowOf(w, 6000 + k) * 0.6f);
    Hub_CardBack(p, r, hov, w.kbd && w.focus == k);
    const HubCardParts c = Hub_CardParts(w, it, r);
    const bool armed = g_cardArmId == m.id && GetTickCount64() - g_cardArmAt < 5000;
    p.Text(g_cfName.get(), m.name, c.name, mocha::text);
    std::wstring meta = m.author.empty() ? std::wstring() : m.author;
    if (!m.version.empty()) meta += (meta.empty() ? L"Version " : L"  \u00B7  ") + m.version;
    if (Set_FieldValue(f) != f.value) meta += f.cur == L"1" ? L"  \u00B7  Turns on when you save" : L"  \u00B7  Turns off when you save";
    if (armed) p.Text(g_cfMeta.get(), L"Click the bin again to remove it", c.meta, mocha::red);
    else p.Text(g_cfMeta.get(), meta, c.meta, mocha::overlay2);
    if (g_cardsGrid)
        p.Text(g_cfDesc.get(), m.desc.empty() ? std::wstring(L"No description.") : m.desc, c.desc,
               m.desc.empty() ? mocha::overlay0 : mocha::subtext0);
    for (int i = 0; i < c.n; i++)
        Hub_DrawBtn(p, w, c.btn[i], Hub_BtnHoverId(k, c.btn[i].id), armed && c.btn[i].id == kBtnRemove);
    Hub_DrawSwitch(p, w, k, c.sw);
}

// The toolbar: a search box, two drop-downs and the Grid or List switch.
static void Hub_DrawBar(SetPaint& p, SetWindow& w, const SetItem& it) {
    const int k = it.field;
    const SetField& f = w.fields[k];
    const D2D1_RECT_F r = Set_RowRect(w, it);
    const float g = std::max({Set_GlowOf(w, 6000 + k), Set_GlowOf(w, 1000 + k),
                              (w.editing == k || w.openSel == k) ? 1.0f : 0.0f});
    if (Hub_IsView(f)) {
        const bool grid = f.cur == L"1";
        p.Round(r, 10, kSetBoxFill);
        p.Edge(r, 10, mocha::overlay0, 0.7f * (1 - g), 1.25f);
        p.GradRing(r, 10, g, 1.5f);
        const float mid = (r.left + r.right) / 2;
        D2D1_RECT_F a{r.left + 4, r.top + 4, mid - 1, r.bottom - 4}, b{mid + 1, r.top + 4, r.right - 4, r.bottom - 4};
        p.GradFill(grid ? a : b, 7, 0.9f);
        p.Glyph(w.fIconS.get(), 0xF0E2, a, grid ? mocha::crust : mocha::subtext0);
        p.Glyph(w.fIconS.get(), 0xEA37, b, grid ? mocha::subtext0 : mocha::crust);
        return;
    }
    p.Round(r, 10, kSetBoxFill);
    p.Edge(r, 10, mocha::overlay0, 0.7f * (1 - g), 1.25f);
    p.GradRing(r, 10, g, 1.75f);
    if (f.kind == SetField::Text) {
        p.Glyph(w.fIconS.get(), 0xE721, {r.left + 10, r.top, r.left + 34, r.bottom}, mocha::overlay1);
        if (w.editing != k) {
            if (f.cur.empty()) p.Text(w.fValue.get(), Hub_KeyIs(f, L"hub.search") ? L"Search your mods" : L"Search the library",
                                      {r.left + 38, r.top, r.right - 12, r.bottom}, mocha::overlay0);
            else p.Text(w.fValue.get(), f.cur, {r.left + 38, r.top, r.right - 12, r.bottom}, mocha::text);
        }
        return;
    }
    const std::wstring lead = std::wstring(f.label) + L"  ";
    const float lw = Set_TextW(w.fValue.get(), lead);
    p.Text(w.fValue.get(), lead, {r.left + 14, r.top, r.left + 14 + lw, r.bottom}, mocha::overlay1);
    p.Text(w.fValue.get(), Set_ChoiceLabel(f), {r.left + 14 + lw, r.top, r.right - 32, r.bottom}, mocha::text);
    p.Glyph(w.fIconS.get(), 0xE70D, {r.right - 32, r.top, r.right - 8, r.bottom}, mocha::subtext0);
}

static bool Hub_DrawRow(SetPaint& p, SetWindow& w, const SetItem& it) {
    if (!Hub_ListPage(w)) return false;
    const SetField& f = w.fields[it.field];
    if (f.hub == 1) { Hub_DrawModCard(p, w, it); return true; }
    if (Hub_IsBar(f)) { Hub_DrawBar(p, w, it); return true; }
    return false;
}

static bool Hub_DrawLink(SetPaint& p, SetWindow& w, const SetItem& it, int idx) {
    if (!Hub_ListPage(w) || !Hub_LinkCard(it)) return false;
    const D2D1_RECT_F r = Set_RowRect(w, it);
    float hov = Set_GlowOf(w, 3000 + idx);
    for (int b = 0; b < 8; b++) hov = std::max(hov, Set_GlowOf(w, Hub_LinkBtnHoverId(idx, b)));
    Hub_CardBack(p, r, hov, false);
    const HubCardParts c = Hub_CardParts(w, it, r);
    const std::wstring id = it.url.substr(9);
    std::wstring name = it.text, meta, desc = it.sub;
    if (it.url.rfind(L"hub:feed:", 0) == 0) {
        if (const HubFeedMod* f = Hub_FeedFind(id)) {
            name = f->name; desc = f->desc; meta = L"DavidHiFi  \u00B7  " + f->version;
            // An update waiting: the card says what is new in it, before anyone clicks Update.
            const HubMod* m = Hub_FindMod(id);
            if (m && Hub_Newer(f->version, m->version)) {
                meta += L"  \u00B7  You have " + m->version;
                if (!f->changes.empty()) desc = L"New in " + f->version + L": " + f->changes;
            }
        }
    } else {
        for (auto& m : g_repo)
            if (m.id == id) { name = m.name; desc = m.desc; meta = m.author + (m.version.empty() ? L"" : L"  \u00B7  " + m.version); break; }
    }
    if (const HubMod* mine = Hub_FindMod(id)) meta += L"  \u00B7  Installed";
    D2D1_RECT_F nameR = c.name;
    if (g_cardsGrid) nameR.right = r.right - kCardPad;
    p.Text(g_cfName.get(), name, nameR, mocha::text);
    p.Text(g_cfMeta.get(), meta, c.meta, mocha::overlay2);
    if (g_cardsGrid) p.Text(g_cfDesc.get(), desc.empty() ? std::wstring(L"No description.") : desc, c.desc,
                            desc.empty() ? mocha::overlay0 : mocha::subtext0);
    for (int i = 0; i < c.n; i++) Hub_DrawBtn(p, w, c.btn[i], Hub_LinkBtnHoverId(idx, c.btn[i].id), false);
    if (!c.n) p.Glyph(w.fIcon.get(), 0xE8A7, {r.right - 46, r.bottom - 40, r.right - 12, r.bottom - 10}, mocha::subtext1);
    return true;
}

// ---- Hit testing and clicks ----

static bool Hub_HitRow(SetWindow& w, const SetItem& it, const D2D1_RECT_F& row, float x, float cy, SetHit& h) {
    if (!Hub_ListPage(w)) return false;
    const SetField& f = w.fields[it.field];
    if (Hub_IsView(f)) {
        const bool grid = f.cur == L"1", leftHalf = x < (row.left + row.right) / 2;
        h.kind = grid == leftHalf ? SetHit::None : SetHit::Control;  // The side already on does nothing.
        return true;
    }
    if (Hub_IsBar(f)) { h.kind = SetHit::Control; return true; }  // The whole box opens, magnifier included.
    if (f.hub != 1) return false;
    const HubCardParts c = Hub_CardParts(w, it, row);
    if (Set_In({c.sw.left - 6, c.sw.top - 6, c.sw.right + 6, c.sw.bottom + 6}, x, cy)) {
        h.kind = SetHit::Control;
        return true;
    }
    for (int i = 0; i < c.n; i++)
        if (Set_In(c.btn[i].r, x, cy)) {
            h.kind = SetHit::Card;
            h.b = c.btn[i].id;
            h.id = Hub_BtnHoverId(it.field, c.btn[i].id);
            return true;
        }
    h.kind = SetHit::Open;
    return true;
}

static void Hub_HitLink(SetWindow& w, int i, const D2D1_RECT_F& row, float x, float cy, SetHit& h) {
    if (!Hub_ListPage(w) || !Hub_LinkCard(w.items[i])) return;
    const HubCardParts c = Hub_CardParts(w, w.items[i], row);
    for (int b = 0; b < c.n; b++)
        if (Set_In(c.btn[b].r, x, cy)) {
            h.kind = SetHit::Card;
            h.a = -(i + 1);
            h.b = c.btn[b].id;
            h.id = Hub_LinkBtnHoverId(i, c.btn[b].id);
        }
}

static int Hub_HoverCard(const SetHit& h) { return h.a >= 0 ? 1000 + h.a : 3000 + (-h.a - 1); }

static void Hub_ScrollToGroup(SetWindow& w, PCWSTR name) {
    for (auto& it : w.items)
        if (it.type == SetItem::Group && it.text == name) {
            w.scrollTarget = std::clamp(it.y - 16, 0.0f, std::max(0.0f, w.contentH - Set_ViewH(w)));
            Set_Invalidate(w);
            return;
        }
}

static void Hub_CardRemove(SetWindow& w, const std::wstring& id, const std::wstring& name) {
    Set_CommitEdit(w, true);
    if (Set_ChangedCount(w) > 0) {
        Set_SetStatus(w, L"Save or cancel your changes before removing a mod.", true);
        return;
    }
    const ULONGLONG now = GetTickCount64();
    if (g_cardArmId != id || now - g_cardArmAt > 5000) {
        g_cardArmId = id;
        g_cardArmAt = now;
        SetTimer(w.hwnd, kHubArmTimer, 5050, nullptr);
        Set_Invalidate(w);
        return;
    }
    g_cardArmId.clear();
    std::wstring err;
    if (!Hub_Backup({id}, err)) { Set_SetStatus(w, err.c_str(), true); return; }
    if (!Hub_RunJob(w, {L"mod remove " + Set_QuoteArg(id) + L" --yes"}, err)) {
        Set_BuildAndClamp(w);
        Set_SetStatus(w, err.c_str(), true);
        return;
    }
    const float keep = w.scrollTarget;
    Hub_LoadList(w);
    w.scrollY = w.scrollTarget = std::clamp(keep, 0.0f, std::max(0.0f, w.contentH - Set_ViewH(w)));
    Set_BuildAndClamp(w);
    Set_SetStatus(w, (L"Removed " + name + L". A backup was saved first.").c_str());
}

static void Hub_CardClick(SetWindow& w, int a, int b) {
    if (w.saving) return;
    if (a < 0) {
        const int i = -a - 1;
        if (i >= (int)w.items.size()) return;
        const std::wstring url = w.items[i].url, id = url.substr(9);
        if (url.rfind(L"hub:feed:", 0) == 0) {
            // Installed and current: open it on the Mods page rather than installing it again.
            const HubMod* m = Hub_FindMod(id);
            const HubFeedMod* f = Hub_FeedFind(id);
            if (m && !(f && Hub_Newer(f->version, m->version))) Hub_OpenDetail(w, id);
            else Hub_Link(url.c_str());
        } else if (b == kBtnInstall) Hub_Link((L"hub:install:" + id).c_str());
        return;
    }
    if (a >= (int)w.fields.size() || w.fields[a].hub != 1) return;
    const HubMod m = g_hub.mods[w.fields[a].mod];
    switch (b) {
        case kBtnDetails:
            if (Hub_OpenDetail(w, m.id)) Hub_ScrollToGroup(w, L"More");
            break;
        case kBtnSettings:
            Hub_OpenDetail(w, m.id);
            break;
        case kBtnSource: {
            const auto source = L"C:\\ProgramData\\Windhawk\\ModsSource\\" + m.id + L".wh.cpp";
            if (GetFileAttributesW(source.c_str()) == INVALID_FILE_ATTRIBUTES) Set_SetStatus(w, L"This mod's source file was not found.", true);
            else Hub_OpenFile(w.hwnd, source);
            break;
        }
        case kBtnRemove:
            Hub_CardRemove(w, m.id, m.name);
            break;
        case kBtnUpdate: {
            const HubFeedMod* f = Hub_FeedFind(m.id);
            Hub_Link(((f && Hub_Newer(f->version, m.version) ? L"hub:feed:" : L"hub:update:") + m.id).c_str());
            break;
        }
    }
}

// A toolbar choice changed: apply it now, not at Save.
static void Hub_Chose(SetWindow& w, int k) {
    if (k < 0 || k >= (int)w.fields.size()) return;
    SetField& f = w.fields[k];
    if (!Hub_IsBar(f)) return;
    f.value = f.cur;
    if (Hub_IsView(f)) {
        g_cardsGrid = f.cur == L"1";
        Hub_RegSet(L"Set.modsView", g_cardsGrid ? 1 : 0);
        for (auto& o : w.fields)
            if (Hub_IsView(o)) o.cur = o.value = f.cur;
    }
    if (Hub_KeyIs(f, L"hub.group")) { Hub_Regroup(w); return; }
    w.scrollY = w.scrollTarget = 0;
    Hub_ResetView(w);
    Set_BuildAndClamp(w);
}

// Live search on the Marketplace too: the cards follow each key typed.
static bool Hub_LiveSearch(SetWindow& w) {
    if (w.editing < 0 || w.editing >= (int)w.fields.size()) return false;
    const SetField& f = w.fields[w.editing];
    return (w.editing == g_hub.searchField && g_hub.detail < 0) || Hub_KeyIs(f, L"hub.marketSearch");
}

static std::wstring Hub_LiveText(SetWindow& w, PCWSTR key) {
    for (size_t i = 0; i < w.fields.size(); i++)
        if (Hub_KeyIs(w.fields[i], key))
            return (int)i == w.editing && w.edit ? Set_WindowText(w.edit) : w.fields[i].cur;
    return L"";
}
// ---- end of cards.inc ----
// ---- Tray ---------------------------------------------------------------------------

// The shared tray badge (copied from Seamless Crosshair's MakeTrayIcon): a rounded square in the
// blue to mauve gradient with the puzzle glyph cut out, drawn with GDI.
static HICON Hub_MakeTrayIcon() {
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
    WCHAR g[2] = {(WCHAR)0xEA86, 0};
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

static void Hub_TrayUpdate(SetWindow& w) {
    static HICON badge = Hub_MakeTrayIcon();
    NOTIFYICONDATAW nid{};
    nid.cbSize = sizeof(nid);
    nid.hWnd = w.hwnd;
    nid.uID = TrayIconId();
    const bool want = !g_hub.noTray && Set_FieldOn(w, L"settingsTrayIcon", true) && w.hwnd;
    if (!want) {
        if (g_hub.trayOn) Shell_NotifyIconW(NIM_DELETE, &nid);
        g_hub.trayOn = false;
        return;
    }
    nid.uFlags = NIF_MESSAGE | NIF_ICON | NIF_TIP | NIF_SHOWTIP;
    nid.uCallbackMessage = WM_HUB_TRAY;
    nid.hIcon = badge ? badge : w.iconSmall;
    wcscpy_s(nid.szTip, L"Seamless Workshop");
    if (g_hub.trayOn) {
        Shell_NotifyIconW(NIM_MODIFY, &nid);
        return;
    }
    if (Shell_NotifyIconW(NIM_ADD, &nid)) {
        nid.uVersion = NOTIFYICON_VERSION_4;
        Shell_NotifyIconW(NIM_SETVERSION, &nid);
        g_hub.trayOn = true;
    }
}

// The tray menu, drawn by the shared Seamless menu renderer.
static void Hub_TrayMenu(SetWindow& w, int x, int y) {
    const POINT at{x, y};
    const int cmd = Set_TrayMenu(w.hwnd, {Set_MenuRow(1, L"\uF2D0", L"Open Seamless Workshop"),
                                          Set_MenuRow(2, L"\uF021", L"Check for updates", false, w.saving),
                                          Set_MenuSep(),
                                          Set_MenuRow(3, L"\uF011", L"Quit")}, &at);
    if (cmd == 1) {
        PostMessageW(w.hwnd, WM_APP_SETTINGS_ACTIVATE, 0, 0);
    } else if (cmd == 2) {
        if (!w.saving) Hub_FeedStart(w.hwnd, true);
    } else if (cmd == 3) {
#ifdef HUB_MOD
        // The mod stays on in Windhawk: Quit hides the window and the tray icon until the mod is
        // turned on again or one of its settings changes.
        Set_CommitEdit(w, true);
        g_hub.noTray = true;
        Hub_TrayUpdate(w);
        ShowWindow(w.hwnd, SW_HIDE);
#else
        g_hub.quitting = true;
        PostMessageW(w.hwnd, WM_CLOSE, 0, 0);
#endif
    }
}

// ---- Following stock Windhawk ----------------------------------------------------------
// Windhawk keeps every mod's on/off state, version and settings under one registry key. A
// thread waits on that key and tells the window when anything below it changes, so a mod
// turned on, installed or removed in Windhawk's own window shows up here without a click.

static std::thread g_whWatch;
static HANDLE g_whQuit;

static void Hub_WatchWindhawk(HWND hwnd) {
    g_whQuit = CreateEventW(nullptr, TRUE, FALSE, nullptr);
    if (!g_whQuit) return;
    g_whWatch = std::thread([hwnd] {
        HANDLE changed = CreateEventW(nullptr, FALSE, FALSE, nullptr);
        HKEY key = nullptr;
        while (changed) {
            if (!key && RegOpenKeyExW(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Windhawk\\Engine\\Mods", 0,
                                      KEY_NOTIFY | KEY_WOW64_64KEY, &key) != ERROR_SUCCESS) {
                key = nullptr;  // Windhawk missing or not set up yet: look again in a minute.
                if (WaitForSingleObject(g_whQuit, 60000) != WAIT_TIMEOUT) break;
                continue;
            }
            if (RegNotifyChangeKeyValue(key, TRUE, REG_NOTIFY_CHANGE_NAME | REG_NOTIFY_CHANGE_LAST_SET, changed, TRUE) !=
                ERROR_SUCCESS) {
                RegCloseKey(key);
                key = nullptr;
                if (WaitForSingleObject(g_whQuit, 60000) != WAIT_TIMEOUT) break;
                continue;
            }
            HANDLE wait[2] = {g_whQuit, changed};
            if (WaitForMultipleObjects(2, wait, FALSE, INFINITE) != WAIT_OBJECT_0 + 1) break;
            PostMessageW(hwnd, WM_HUB_WINDHAWK, 0, 0);
        }
        if (key) RegCloseKey(key);
        if (changed) CloseHandle(changed);
    });
}

static void Hub_StopWatch() {
    if (g_whQuit) SetEvent(g_whQuit);
    if (g_whWatch.joinable()) g_whWatch.join();
    if (g_whQuit) CloseHandle(g_whQuit);
    g_whQuit = nullptr;
}

// Refresh only when it cannot cost the user anything: list showing, nothing unsaved, no box
// being typed in, no menu open, no save running. Otherwise keep the timer and try again.
static bool Hub_SyncWait(SetWindow& w) {
    return w.saving || !IsWindowVisible(w.hwnd) || g_hub.detail >= 0 || w.editing >= 0 || w.openSel >= 0 ||
           w.recording >= 0 || w.dragSlider >= 0 || w.dragScroll || Set_ChangedCount(w) > 0;
}

static void Hub_SyncTick(SetWindow& w) {
    if (!IsWindowVisible(w.hwnd)) {  // In the tray: showing the window reloads the list anyway.
        KillTimer(w.hwnd, kHubSyncTimer);
        g_hub.stale = false;
        return;
    }
    if (Hub_SyncWait(w)) {
        g_hub.stale = true;
        SetTimer(w.hwnd, kHubSyncTimer, 1500, nullptr);
        return;
    }
    KillTimer(w.hwnd, kHubSyncTimer);
    g_hub.stale = false;
    std::vector<HubMod> fresh;
    std::wstring err;
    if (!Hub_ReadMods(fresh, err)) return;
    if (Hub_ModSig(fresh) == g_hub.sig) return;  // An echo of the Hub's own change, or settings only.
    const float scroll = w.scrollY;
    Hub_LoadList(w, &fresh);
    w.scrollY = w.scrollTarget = std::clamp(scroll, 0.0f, std::max(0.0f, w.contentH - Set_ViewH(w)));
    Set_BuildAndClamp(w);
    if (w.page == 0) Set_SetStatus(w, L"Picked up a change made in Windhawk.");
}

// ---- Main window additions -----------------------------------------------------------

static LRESULT CALLBACK Hub_SubProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp, UINT_PTR, DWORD_PTR) {
    if (msg == WM_NCDESTROY) {
        RemoveWindowSubclass(hwnd, Hub_SubProc, 7);
        return DefSubclassProc(hwnd, msg, wp, lp);
    }
    std::shared_ptr<SetWindow> keep = g_setWin;
    SetWindow* w = keep && keep->hwnd == hwnd ? keep.get() : nullptr;
    if (!w) return DefSubclassProc(hwnd, msg, wp, lp);
    if (g_hub.taskbarCreated && msg == g_hub.taskbarCreated) {
        g_hub.trayOn = false;
        Hub_TrayUpdate(*w);
        return 0;
    }
    switch (msg) {
        case WM_HUB_ACTION: {
            std::unique_ptr<std::wstring> action((std::wstring*)lp);
            if (!w->saving && action) {
                if (*action == L"hub:back") Hub_Back(*w);
                else if (*action == L"hub:remove") Hub_RemoveClick(*w);
                else Hub_Action(*w, *action);
            }
            return 0;
        }
        case WM_HUB_RESULT:
            Hub_ReadResult(*w);
            return 0;
        case WM_HUB_FEED:
            Hub_FeedResult(*w, wp != 0);
            return 0;
        case WM_COMMAND:
            // Live search: the list follows each key typed in the search box.
            if (w->edit && (HWND)lp == w->edit && HIWORD(wp) == EN_CHANGE && Hub_LiveSearch(*w)) {
                w->scrollY = w->scrollTarget = 0;
                Set_BuildAndClamp(*w);
            } else if (w->edit && (HWND)lp == w->edit && HIWORD(wp) == EN_KILLFOCUS) {
                PostMessageW(hwnd, WM_HUB_REBUILD, 0, 0);
            }
            break;
        case WM_HUB_OPEN:
            if (!w->saving && g_hub.detail < 0 && wp < w->fields.size() && w->fields[wp].hub == 1)
                Hub_OpenDetail(*w, g_hub.mods[w->fields[wp].mod].id);
            return 0;
        case WM_HUB_LINK:
            if (w->saving) return 0;
            if (wp == 1) Hub_Back(*w);
            else Hub_RemoveClick(*w);
            return 0;
        case WM_HUB_REBUILD:
            Set_BuildAndClamp(*w);
            return 0;
        case WM_HUB_MODCHANGED:
            // The mod's settings changed in Windhawk (or this window saved them): the tray icon
            // comes back after a Quit, and with no tray icon the window shows so it stays reachable.
            g_hub.noTray = false;
            if (!w->saving) {
                g_settings.animations = Set_FieldOn(*w, L"animations", true);
                Hub_TrayUpdate(*w);
                Hub_Presence();
                if (!g_hub.trayOn && !IsWindowVisible(hwnd)) PostMessageW(hwnd, WM_APP_SETTINGS_ACTIVATE, 0, 0);
            }
            return 0;
        case WM_HUB_REGROUP:
            Hub_Regroup(*w);
            return 0;
        case WM_HUB_WINDHAWK:
            // Windhawk writes several values per change: wait for the burst to settle.
            SetTimer(hwnd, kHubSyncTimer, 700, nullptr);
            return 0;
        case WM_TIMER:
            if (wp == 0x4856) { Hub_Presence(); return 0; }
            if (wp == kHubSyncTimer) { Hub_SyncTick(*w); return 0; }
            if (wp == kHubFeedTimer) {
                if (Hub_AppInt(L"feedCheck", 1) && !w->saving) Hub_FeedStart(hwnd, false);
                return 0;
            }
            if (wp != kHubArmTimer) break;
            KillTimer(hwnd, kHubArmTimer);  // The "click again" prompt lapses: show the plain row again.
            {
                const ULONGLONG now = GetTickCount64();
                bool lapsed = false;
                for (ULONGLONG* armed : {&g_hub.removeArmed, &g_resetArmed, &g_restoreArmed, &g_setupArmed, &g_removeAllArmed, &g_fullArmed})
                    if (*armed && now - *armed >= 5000) *armed = 0, lapsed = true;
                if (!g_cardArmId.empty() && now - g_cardArmAt >= 5000) g_cardArmId.clear(), lapsed = true;
                if (lapsed) Set_BuildAndClamp(*w);
            }
            return 0;
        case WM_HUB_TRAY:
            switch (LOWORD(lp)) {
                case NIN_SELECT:
                case NIN_KEYSELECT: PostMessageW(hwnd, WM_APP_SETTINGS_ACTIVATE, 0, 0); break;
                case NIN_BALLOONUSERCLICK:
                    PostMessageW(hwnd, WM_APP_SETTINGS_ACTIVATE, 0, 0);
                    if (!w->saving) Set_GoPage(*w, 2);
                    break;
                case WM_CONTEXTMENU: Hub_TrayMenu(*w, GET_X_LPARAM(wp), GET_Y_LPARAM(wp)); break;
            }
            return 0;
        case WM_CLOSE:
            if (w->saving && !g_hub.quitting) return 0;
#ifdef HUB_MOD
            // The tool mod keeps its window until Windhawk unloads it; closing only hides it.
            if (!g_hub.quitting) {
                Set_CommitEdit(*w, true);
                ShowWindow(hwnd, SW_HIDE);
                return 0;
            }
#endif
            if (g_hub.trayOn && !g_hub.quitting) {
                Set_CommitEdit(*w, true);
                ShowWindow(hwnd, SW_HIDE);
                return 0;
            }
            break;
        case WM_SHOWWINDOW:
            if (!wp) {
                if (w->timer) KillTimer(hwnd, kSetTimerId);
                w->timer = false;
            } else {
                w->timer = SetTimer(hwnd, kSetTimerId, 15, nullptr) != 0;
                // Back from the tray: pick up changes made in Windhawk meanwhile.
                if (g_hub.shownOnce && g_hub.detail < 0 && Set_ChangedCount(*w) == 0) Hub_LoadList(*w);
                g_hub.shownOnce = true;
            }
            break;
        case WM_DESTROY:
            g_hub.quitting = true;
            g_hub.noTray = true;
            Hub_TrayUpdate(*w);
            break;
    }
    return DefSubclassProc(hwnd, msg, wp, lp);
}

// Dark context menus for the tray (uxtheme's unnamed SetPreferredAppMode / FlushMenuThemes).
static void Hub_DarkMenus() {
    HMODULE ux = LoadLibraryExW(L"uxtheme.dll", nullptr, LOAD_LIBRARY_SEARCH_SYSTEM32);
    if (!ux) return;
    using Mode_t = int(WINAPI*)(int);
    using Flush_t = void(WINAPI*)();
    if (auto mode = (Mode_t)(void*)GetProcAddress(ux, MAKEINTRESOURCEA(135))) mode(2 /* ForceDark */);
    if (auto flush = (Flush_t)(void*)GetProcAddress(ux, MAKEINTRESOURCEA(136))) flush();
}

// ---- Off-screen render (--render <dir>) ------------------------------------------------

static bool Hub_SavePng(IWICBitmap* bmp, const std::wstring& path) {
    SetCom<IWICStream> st;
    SetCom<IWICBitmapEncoder> enc;
    SetCom<IWICBitmapFrameEncode> fr;
    return SUCCEEDED(g_setWic->CreateStream(st.put())) &&
           SUCCEEDED(st->InitializeFromFilename(path.c_str(), GENERIC_WRITE)) &&
           SUCCEEDED(g_setWic->CreateEncoder(GUID_ContainerFormatPng, nullptr, enc.put())) &&
           SUCCEEDED(enc->Initialize(st.get(), WICBitmapEncoderNoCache)) &&
           SUCCEEDED(enc->CreateNewFrame(fr.put(), nullptr)) && SUCCEEDED(fr->Initialize(nullptr)) &&
           SUCCEEDED(fr->WriteSource(bmp, nullptr)) && SUCCEEDED(fr->Commit()) && SUCCEEDED(enc->Commit());
}

static bool Hub_Shot(SetWindow& w, const std::wstring& path, bool full) {
    w.ch = 700;
    Set_BuildPage(w);
    const float h = full ? std::max(700.0f, w.contentH + 20) : 700.0f;
    w.ch = h;
    Set_BuildPage(w);
    const float scale = 1.0f;
    const int px = (int)(w.cw * scale), py = (int)((h + kSetCapH) * scale);
    SetCom<IWICBitmap> bmp;
    SetCom<ID2D1RenderTarget> rt;
    if (FAILED(g_setWic->CreateBitmap(px, py, GUID_WICPixelFormat32bppPBGRA, WICBitmapCacheOnLoad, bmp.put())))
        return false;
    auto props = D2D1::RenderTargetProperties(D2D1_RENDER_TARGET_TYPE_DEFAULT,
                                              D2D1::PixelFormat(DXGI_FORMAT_UNKNOWN, D2D1_ALPHA_MODE_PREMULTIPLIED),
                                              96 * scale, 96 * scale);
    if (FAILED(g_setD2d->CreateWicBitmapRenderTarget(bmp.get(), props, rt.put()))) return false;
    rt->SetTextAntialiasMode(D2D1_TEXT_ANTIALIAS_MODE_GRAYSCALE);
    Set_Draw(w, rt.get());
    return Hub_SavePng(bmp.get(), path);
}

static int Hub_Render(const std::wstring& dir, const std::wstring& mod) {
    g_setForceDpi = 96;
    CreateDirectoryW(dir.c_str(), nullptr);
    if (!Set_Create(true)) return 2;
    std::shared_ptr<SetWindow> keep = g_setWin;
    SetWindow& w = *keep;
    int failed = 0;
    w.pageT = 1;
    w.page = 0;
    const float normalW = w.cw;
    w.cw = 1440;  // A wide window: the cards fill the width.
    auto setView = [&](bool grid) {  // The switch draws from its field, the cards from g_cardsGrid.
        g_cardsGrid = grid;
        for (auto& f : w.fields)
            if (Hub_IsView(f)) f.cur = f.value = grid ? L"1" : L"0";
    };
    setView(true);
    failed += !Hub_Shot(w, dir + L"\\mods.png", false);
    setView(false);
    failed += !Hub_Shot(w, dir + L"\\mods-list.png", false);
    setView(true);
    w.cw = 760;  // Narrow: one column, the toolbar wraps.
    failed += !Hub_Shot(w, dir + L"\\mods-narrow.png", false);
    w.cw = 1440;
    w.page = 1;
    failed += !Hub_Shot(w, dir + L"\\marketplace-grid.png", false);
    w.page = 0;
    w.cw = normalW;
    if (g_hub.searchField >= 0) {
        w.fields[g_hub.searchField].cur = L"volume";
        failed += !Hub_Shot(w, dir + L"\\search.png", false);
        w.fields[g_hub.searchField].cur.clear();
    }
    if (!mod.empty()) {
        if (Hub_OpenDetail(w, mod)) {
            w.pageT = 1;
            failed += !Hub_Shot(w, dir + L"\\detail.png", true);
            Hub_CloseDetail(w);
        } else {
            failed++;
        }
    }
    w.pageT = 1;
    const PCWSTR names[] = {L"mods", L"marketplace", L"updates", L"presets", L"developer", L"settings", L"look", L"about"};
    static_assert(sizeof(names) / sizeof(names[0]) == kSetPageCount, "one shot name per page");
    for (int page = 1; page < kSetPageCount; ++page) {
        w.page = page;
        failed += !Hub_Shot(w, dir + L"\\" + names[page] + L".png", page == 5 || page == 6);
    }
    std::string log = "mods " + std::to_string(g_hub.mods.size()) + "\nfailed " + std::to_string(failed) + "\n";
    if (!g_hub.error.empty()) log += Hub_Utf8(g_hub.error) + "\n";
    Hub_WriteFile(dir + L"\\render.txt", log);
    if (w.hwnd) DestroyWindow(w.hwnd);
    return failed ? 4 : 0;
}

// ---- Entry ---------------------------------------------------------------------------

static int Hub_SelfTest(const std::wstring& report) {
    int failed = 0, checked = 0;
    auto check = [&](bool value) { ++checked; if (!value) ++failed; };
    for (PCWSTR s : {L"null", L"true", L"-1.25e+2", L"0", L"[1,2,\"hello\"]", L"{\"a\":1}"}) {
        Js j; check(Js_Parse(s, j));
    }
    for (PCWSTR s : {L"+1", L"01", L"1.", L"1e", L"--1", L"{\"x\":1,\"x\":2}", L"\"\\uZZZZ\"", L"\"\\q\"", L"\"line\nfeed\"", L"[1,]"}) {
        Js j; check(!Js_Parse(s, j));
    }
    check(Hub_ValidId(L"local@hub-test-dummy"));
    check(!Hub_ValidId(L"../other"));
    check(!Hub_ValidId(L"bad\" --enabled"));
    check(Hub_PresetName(L"My test"));
    check(!Hub_PresetName(L"../bad"));
    check(!Hub_PresetName(L" trailing "));
    check(Hub_Newer(L"1.10", L"1.9"));
    check(!Hub_Newer(L"1.9", L"1.10"));
    check(!Hub_Newer(L"1.0.0", L"1"));
    check(!Hub_Newer(L"2.0-beta", L"1"));
    check(Hub_SplitList(L"a; b|a\nc").size() == 3);
    check(Hub_Sha256Data("abc") == L"ba7816bf8f01cfea414140de5dae2223b00361a396177a9cb410ff61f20015ad");
    {
        auto mod = [](PCWSTR id, PCWSTR name, PCWSTR author, std::vector<std::wstring> inc) {
            HubMod m; m.id = id; m.name = name; m.author = author; m.include = std::move(inc); return m;
        };
        check(Hub_ModSource(mod(L"local@x", L"X", L"DavidHiFi, someone", {})) == 0);
        check(Hub_ModSource(mod(L"notepad-fix", L"X", L"DavidHiFi", {})) == 0);
        check(Hub_ModSource(mod(L"taskbar-styler", L"X", L"m417z", {})) == 1);
        check(Hub_ModSource(mod(L"local@mine", L"X", L"someone, DavidHiFi", {})) == 2);
        check(Hub_ModArea(mod(L"a", L"Corner Radius", L"", {L"dwm.exe"})) == 0);
        check(Hub_ModArea(mod(L"a", L"Seamless Taskbar", L"", {L"explorer.exe"})) == 1);
        check(Hub_ModArea(mod(L"a", L"Explorer Tags", L"", {L"explorer.exe"})) == 3);
        check(Hub_ModArea(mod(L"a", L"Snipper", L"", {L"windhawk.exe"})) == 4);
        check(Hub_ModArea(mod(L"a", L"Dark Paint", L"", {L"mspaint.exe"})) == 5);
        check(Hub_ModArea(mod(L"a", L"Flyouts", L"", {L"*"})) == 2);
        check(Hub_ModArea(mod(L"a", L"Blocker", L"", {})) == 6);
    }
    {
        auto savedMods = std::move(g_hub.mods);
        const int savedGroup = g_hub.groupBy;
        HubMod first, second;
        first.id = L"local@first"; first.name = L"First"; first.enabled = false;
        second.id = L"local@second"; second.name = L"Second"; second.enabled = true;
        first.src = 0; second.src = 1;
        g_hub.mods = {first, second};
        g_hub.groupBy = 0;
        SetWindow w{};
        w.fields.clear();
        Hub_PlaceMods(w);
        w.fields[0].cur = L"1";
        g_hub.groupBy = 2;
        Hub_PlaceMods(w);
        const auto pending = std::find_if(w.fields.begin(), w.fields.end(), [](const SetField& f) {
            return std::wstring(f.key) == L"local@first";
        });
        check(pending != w.fields.end() && pending->value == L"0" && pending->cur == L"1");
        check(Set_ChangedCount(w) == 1);
        check(w.fields.size() == 2 && std::wstring(w.fields[0].key) == L"local@second");
        g_hub.mods = std::move(savedMods);
        g_hub.groupBy = savedGroup;
    }
    {
        SetField f{}; f.kind = SetField::Check; f.key = L"wh!disableUpdateCheck"; f.cur = L"1";
        check(Hub_AppSettingLine(f) == L"app settings set disableUpdateCheck \"false\"");
        f.key = L"wh.hideTrayIcon";
        check(Hub_AppSettingLine(f) == L"app settings set hideTrayIcon \"true\"");
    }
    {
        const std::string sha(64, 'a');
        const std::string good = "{\"format\":\"seamless-hub-feed-1\",\"mods\":["
            "{\"id\":\"local@good-mod\",\"name\":\"Good\",\"version\":\"1.2.0\",\"url\":\"https://example.invalid/a.wh.cpp\",\"sha256\":\"" + sha + "\"},"
            "{\"id\":\"local@bad-sha\",\"version\":\"1.0\",\"url\":\"https://example.invalid/b\",\"sha256\":\"xyz\"},"
            "{\"id\":\"plain-id\",\"version\":\"1.0\",\"url\":\"https://example.invalid/c\",\"sha256\":\"" + sha + "\"},"
            "{\"id\":\"local@good-mod\",\"version\":\"9.0\",\"url\":\"https://example.invalid/d\",\"sha256\":\"" + sha + "\"}],"
            "\"app\":{\"version\":\"9.9.9\",\"url\":\"https://example.invalid/hub.exe\",\"sha256\":\"" + sha + "\"}}";
        std::vector<HubFeedMod> mods; HubFeedMod app; std::wstring err;
        const std::wstring saved = g_feedUrlOverride;
        g_feedUrlOverride = L"https://example.invalid/feed.json";
        check(Hub_ParseFeed(good, mods, app, err) && mods.size() == 1 && mods[0].version == L"1.2.0" && app.version == L"9.9.9");
        check(!Hub_ParseFeed("{\"format\":\"other\"}", mods, app, err));
        check(Hub_ParseFeed("\xEF\xBB\xBF{\"format\":\"seamless-hub-feed-1\",\"mods\":[{\"id\":\"local@x\",\"version\":\"1\",\"url\":\"http://plain.invalid/x\",\"sha256\":\"" + sha + "\"}]}", mods, app, err) && mods.empty());
        g_feedUrlOverride = saved;
    }
    {
        // Groups: the feed's order, then "Other" for a missing or unknown one.
        const std::string sha(64, 'c');
        const std::string feed = "{\"format\":\"seamless-workshop-feed-1\",\"categories\":[\"Tools\",\"Taskbar\",\"tools\",\"\",\"Other\",5],\"mods\":["
            "{\"id\":\"local@a\",\"version\":\"1\",\"url\":\"https://example.invalid/a\",\"sha256\":\"" + sha + "\",\"category\":\"Taskbar\"},"
            "{\"id\":\"local@b\",\"version\":\"1\",\"url\":\"https://example.invalid/b\",\"sha256\":\"" + sha + "\",\"category\":\"Nope\"}]}";
        std::vector<HubFeedMod> mods; HubFeedMod app; std::wstring err; std::vector<std::wstring> cats;
        check(Hub_ParseFeed(feed, mods, app, err, &cats) && cats.size() == 2 && cats[0] == L"Tools" && mods.size() == 2);
        const auto savedCats = g_feedCats;
        const auto savedOf = g_feedCatOf;
        g_feedCats = cats;
        check(Hub_CatIndex(mods[0].category) == 1 && Hub_CatIndex(mods[1].category) == 2 && Hub_CatName(2) == L"Other");
        g_feedCatOf = {{L"local@a", L"Taskbar"}};
        HubMod a; a.id = L"local@a"; a.area = 3;
        HubMod lib; lib.id = L"x"; lib.area = 4;  // Not in the feed: a tool, from what it loads into.
        HubMod odd; odd.id = L"y"; odd.area = 5;
        check(Hub_ModCat(a) == 1 && Hub_ModCat(lib) == 0 && Hub_ModCat(odd) == 2);
        g_feedCats.clear();
        check(Hub_CatIndex(L"Explorer") == 1 && Hub_CatIndex(L"") == 5 && Hub_CatName(5) == L"Other");
        g_feedCats = savedCats;
        g_feedCatOf = savedOf;
    }
    {
        // The Workshop feed: presets ride along, the Workshop itself never shows as a mod.
        const std::string sha(64, 'b');
        const std::string feed = "{\"format\":\"seamless-workshop-feed-1\",\"commit\":\"abc\",\"generatedAt\":\"2026-11-20\",\"mods\":["
            "{\"id\":\"local@good-mod\",\"version\":\"1.0\",\"url\":\"https://example.invalid/a\",\"sha256\":\"" + sha + "\","
            "\"preset\":{\"enabled\":true,\"settings\":{\"size\":8,\"look\":\"dark\"}}},"
            "{\"id\":\"local@odd-preset\",\"version\":\"1.0\",\"url\":\"https://example.invalid/b\",\"sha256\":\"" + sha + "\","
            "\"preset\":{\"enabled\":\"yes\",\"settings\":{}}},"
            "{\"id\":\"local@seamless-workshop\",\"version\":\"1.0\",\"url\":\"https://example.invalid/c\",\"sha256\":\"" + sha + "\"}]}";
        std::vector<HubFeedMod> mods; HubFeedMod app; std::wstring err;
        check(Hub_ParseFeed(feed, mods, app, err) && mods.size() == 2 && mods[0].hasPreset && mods[0].presetOn &&
              mods[0].preset.a.size() == 2 && !mods[1].hasPreset);
        check(Hub_SecretKey(L"discordClientId") && Hub_SecretKey(L"API_KEY") && Hub_SecretKey(L"webhookUrl") &&
              Hub_SecretKey(L"list[0].authToken") && !Hub_SecretKey(L"cornerSize") && !Hub_SecretKey(L"monitor"));
        // Shortcuts and look settings are not private; real keys still are.
        for (PCWSTR k : {L"hotkeyCenter", L"toggleHotkey", L"winKey", L"keyboardSounds", L"HotkeyActions[0].Hotkey",
                         L"shortcuts.keyCenter", L"taskbarLocation", L"addressBarHeight", L"monkey"})
            check(!Hub_SecretKey(k));
        for (PCWSTR k : {L"accounts[0].apiKey", L"key", L"server.keys", L"clock.weather.location", L"discordUserId",
                         L"refreshToken", L"userName", L"email"})
            check(Hub_SecretKey(k));
        Js v; v.t = Js::Str;
        for (PCWSTR s : {L"sk-abc", L"ghp_x", L"Bearer x", L"AIzaSy", L"0123456789abcdef0123456789abcdef",
                         L"aK3jQ9zX7mP2wL5vR8tY1uN4bC6dE0fG", L"mail me at someone@example.com"}) {
            v.s = s; check(Hub_SecretValue(v));
        }
        for (PCWSTR s : {L"Segoe UI Variable Display semibold", L"BackgroundSizing=InnerBorderEdge",
                         L"Background:=<AcrylicBrush TintColor=\"#1E1E2E\" TintOpacity=\"0.4\"/>",
                         L"TaskNeedsAttentionRunningIndicator=1", L"Ctrl+Alt+Shift+G", L"local@seamless-taskbar"}) {
            v.s = s; check(!Hub_SecretValue(v));
        }
        {
            // Fitting to what the mod declares: old names out, unsigned back to signed, text
            // where text is declared, missing defaults filled, a set list kept whole.
            Js defs, want, fit;
            check(Js_Parse(L"{\"gap\":4,\"count\":\"7\",\"weather.location\":\"\",\"rows[0].name\":\"\",\"rows[0].size\":1,\"on\":1}", defs));
            check(Js_Parse(L"{\"gap\":4294967295,\"count\":9,\"oldName\":1,\"rows[0].name\":\"a\",\"rows[1].name\":\"b\",\"on\":0}", want));
            int gone = 0;
            check(Js_Parse(Hub_FitSettings(want, defs, &gone), fit) && gone == 1 && !fit.get(L"oldName") &&
                  fit.get(L"gap") && fit.get(L"gap")->s == L"-1" && fit.get(L"count") && fit.get(L"count")->t == Js::Str &&
                  Js_Text(fit.get(L"count")) == L"9" && fit.get(L"weather.location") && Js_Text(fit.get(L"rows[1].name")) == L"b" &&
                  !fit.get(L"rows[0].size") && fit.get(L"on") && fit.get(L"on")->s == L"0");
        }
        Js cur, pre, out;
        check(Js_Parse(L"{\"size\":4,\"token\":\"mine\",\"rows[0].name\":\"a\",\"rows[1].name\":\"b\",\"other\":1}", cur));
        check(Js_Parse(L"{\"size\":8,\"token\":\"his\",\"rows[0].name\":\"c\",\"note\":\"ghp_leak\"}", pre));
        int dropped = 0;
        check(Js_Parse(Hub_PresetMerge(pre, &cur, &dropped), out) && dropped == 2 && out.a.size() == 4 &&
              Js_Text(out.get(L"token")) == L"mine" && Js_Text(out.get(L"rows[0].name")) == L"c" &&
              !out.get(L"rows[1].name") && !out.get(L"note") && out.get(L"other"));
        check(Hub_PresetFormat(L"seamless-hub-preset-1") && Hub_PresetFormat(L"seamless-workshop-preset-1") &&
              !Hub_PresetFormat(L"other"));
    }
    check(Hub_SourceId("// ==WindhawkMod==\n// @id           good-mod\r\n// @name x\n") == L"good-mod");
    Js j; check(Js_Parse(L"{\"name\":\"a\\nb\",\"value\":-2.5}", j));
    Js again; check(Js_Parse(Hub_JsDump(j), again) && Js_Text(again.get(L"name")) == L"a\nb");
    Hub_WriteFile(report, "{\"checks\":" + std::to_string(checked) + ",\"failed\":" + std::to_string(failed) + "}");
    return failed ? 1 : 0;
}

static int Hub_VerifyDummy(const std::wstring& report) {
    const std::wstring id = L"local@hub-test-dummy";  // Installed from a file, so it carries local@.
    Js original, config; std::wstring err;
    if (!Hub_Cli(L"mod config get " + id, config, err) || !config.get(L"config") ||
        !config.get(L"config")->get(L"disabled") || !config.get(L"config")->get(L"disabled")->b) {
        Hub_WriteFile(report, "{\"error\":\"The harmless test mod must be installed and off.\"}"); return 1;
    }
    if (!Set_Create(true)) return 2;
    auto keep = g_setWin; auto& w = *keep;
    int failed = 0, checked = 0;
    auto check = [&](bool value) { ++checked; if (!value) ++failed; };
    const auto name = L"Hub Verification " + std::to_wstring(GetTickCount64());
    const auto preset = Hub_PresetDir() + L"\\" + name + L".json";
    check(Hub_Backup({id}, err));
    check(Hub_Snapshot({id}, preset, err));
    Js saved; check(Hub_ReadPreset(preset, saved, err));
    const auto settings = Hub_DataDir() + L"\\verification-settings.json";
    check(Hub_WriteFile(settings, "{\"count\":17,\"label\":\"Preset round trip\",\"switch\":0,\"mode\":\"b\"}"));
    if (!failed) {
        check(Hub_RunJob(w, {L"mod settings write " + id + L" " + Set_QuoteArg(settings)}, err));
        Js changed;
        check(Hub_Cli(L"mod settings get " + id, changed, err) && changed.get(L"settings") &&
              Js_Text(changed.get(L"settings")->get(L"label")) == L"Preset round trip");
        Hub_ApplyPreset(w, name);
        Js restored;
        check(Hub_Cli(L"mod settings get " + id, restored, err) && restored.get(L"settings") &&
              Hub_JsDump(*restored.get(L"settings")) == Hub_JsDump(*saved.get(L"mods")->a[0].get(L"settings")));
        check(Hub_Cli(L"mod config get " + id, config, err) && config.get(L"config") &&
              config.get(L"config")->get(L"disabled")->b);
    }
    DeleteFileW(settings.c_str());
    Hub_WriteFile(report, "{\"checks\":" + std::to_string(checked) + ",\"failed\":" + std::to_string(failed) +
                  ",\"error\":" + Hub_Utf8(Js_Quote(err)) + "}");
    if (w.hwnd) DestroyWindow(w.hwnd);
    return failed ? 1 : 0;
}

// Test mode for self-update: reads a feed and, when it offers a newer app, swaps this exe in place.
static int Hub_UpdateAppTest(const std::wstring& feed, const std::wstring& report) {
    g_feedUrlOverride = feed;
    std::string raw; std::wstring err;
    std::vector<HubFeedMod> mods; HubFeedMod app;
    bool ok = Hub_Download(feed, raw, err) && Hub_ParseFeed(raw, mods, app, err);
    bool swapped = false;
    if (ok && !app.version.empty() && Hub_Newer(app.version, WH_MOD_VERSION)) ok = swapped = Hub_AppUpdate(app, false, err);
    Hub_WriteFile(report, "{\"ok\":" + std::string(ok ? "true" : "false") + ",\"mods\":" + std::to_string(mods.size()) +
                  ",\"swapped\":" + (swapped ? "true" : "false") + ",\"version\":" + Hub_Utf8(Js_Quote(app.version)) +
                  ",\"error\":" + Hub_Utf8(Js_Quote(err)) + "}");
    return ok ? 0 : 1;
}

#ifndef HUB_MOD
int WINAPI wWinMain(HINSTANCE, HINSTANCE, PWSTR, int) {
    int argc = 0;
    PWSTR* argv = CommandLineToArgvW(GetCommandLineW(), &argc);
    std::wstring apply, render, mod, selfTest, verifyDummy, updateFeed, updateReport;
    DWORD waitPid = 0;
    bool fresh = false, background = false, hidden = false;
    for (int i = 1; i < argc; i++) {
        std::wstring a = argv[i];
        bool more = i + 1 < argc;
        if (a == L"--apply" && more) apply = argv[++i];
        else if (a == L"--self-test" && more) selfTest = argv[++i];
        else if (a == L"--verify-dummy" && more) verifyDummy = argv[++i];
        else if (a == L"--render" && more) render = argv[++i];
        else if (a == L"--mod" && more) mod = argv[++i];
        else if (a == L"--wait-pid" && more) waitPid = wcstoul(argv[++i], nullptr, 10);
        else if (a == L"--update-app" && more) updateFeed = argv[++i];
        else if (a == L"--report" && more) updateReport = argv[++i];
        else if (a == L"--new") fresh = true;
        else if (a == L"--background") background = true;
        else if (a == L"--hidden") hidden = true;
        else if (a == L"--no-tray") g_hub.noTray = true;
        else if (a == L"--fill" && more) {
            std::wstring kv = argv[++i];
            const auto eq = kv.find(L'=');
            if (eq != std::wstring::npos && kv.rfind(L"hub.", 0) == 0) g_fill.emplace_back(kv.substr(0, eq), kv.substr(eq + 1));
        }
    }
    LocalFree(argv);
    if (!fresh) g_fill.clear();  // Only a separate test copy takes pre-filled boxes.
    if (!apply.empty()) return Hub_Apply(apply);
    if (!selfTest.empty()) return Hub_SelfTest(selfTest);
    if (!updateFeed.empty() && !updateReport.empty()) return Hub_UpdateAppTest(updateFeed, updateReport);
    if (waitPid) {
        // Started by a self-update: let the old copy exit, then tidy its renamed file.
        if (HANDLE old = OpenProcess(SYNCHRONIZE, FALSE, waitPid)) { WaitForSingleObject(old, 30000); CloseHandle(old); }
        WCHAR self[MAX_PATH]{};
        if (GetModuleFileNameW(nullptr, self, MAX_PATH)) {
            const std::wstring old = std::wstring(self) + L".old";
            for (int i = 0; i < 10 && GetFileAttributesW(old.c_str()) != INVALID_FILE_ATTRIBUTES && !DeleteFileW(old.c_str()); i++) Sleep(300);
        }
    }

    SetProcessDpiAwarenessContext(DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2);
    if (FAILED(CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED))) return 1;
    Hub_MigrateStore();
    g_settings.animations = Wh_GetIntSetting(L"animations") != 0;
    if (!verifyDummy.empty()) {
        int result = Hub_VerifyDummy(verifyDummy); CoUninitialize(); return result;
    }
    if (!render.empty()) {
        int r = Hub_Render(render, mod);
        CoUninitialize();
        return r;
    }

    HANDLE single = nullptr;
    if (!fresh) {
        single = CreateMutexW(nullptr, FALSE, L"Local\\SeamlessWorkshop.Instance");
        if (GetLastError() == ERROR_ALREADY_EXISTS) {
            if (HWND other = FindWindowW(kSettingsClass, nullptr)) {
                DWORD pid = 0;
                GetWindowThreadProcessId(other, &pid);
                AllowSetForegroundWindow(pid);
                PostMessageW(other, WM_APP_SETTINGS_ACTIVATE, 0, 0);
            }
            if (single) CloseHandle(single);
            CoUninitialize();
            return 0;
        }
    }
    Hub_DarkMenus();
    if (!Set_Create(false)) return 1;
    HWND hwnd = g_setWin->hwnd;
    g_settingsWnd = hwnd;
    SetWindowSubclass(hwnd, Hub_SubProc, 7, 0);
    g_hub.taskbarCreated = RegisterWindowMessageW(L"TaskbarCreated");
    ChangeWindowMessageFilterEx(hwnd, g_hub.taskbarCreated, MSGFLT_ALLOW, nullptr);
    Hub_TrayUpdate(*g_setWin);
    SetTimer(hwnd, 0x4856, 1000, nullptr);
    Hub_Presence();
    if (Hub_AppInt(L"feedCheck", 1)) Hub_FeedStart(hwnd, false);
    SetTimer(hwnd, kHubFeedTimer, 24u * 60 * 60 * 1000, nullptr);
    Hub_WatchWindhawk(hwnd);
    if (!mod.empty()) Hub_OpenDetail(*g_setWin, mod);
    if (hidden && g_hub.trayOn) {
        g_hub.shownOnce = true;
        KillTimer(hwnd, kSetTimerId);
        g_setWin->timer = false;
    } else if (background) {
        ShowWindow(hwnd, SW_SHOWNOACTIVATE);
    } else {
        ShowWindow(hwnd, SW_SHOW);
        ForceForeground(hwnd);
    }
    MSG msg;
    while (GetMessageW(&msg, nullptr, 0, 0) > 0) {
        TranslateMessage(&msg);
        DispatchMessageW(&msg);
    }
    if (g_reader.joinable()) g_reader.join();
    if (g_feedThread.joinable()) g_feedThread.join();
    Hub_StopWatch();
    Hub_ClearPresence();
    if (single) CloseHandle(single);
    CoUninitialize();
    return 0;
}
#else  // HUB_MOD

// ---- Windhawk tool mod -----------------------------------------------------------------
// Windhawk starts this in its own windhawk.exe process. The window lives on one UI thread,
// started hidden in the tray; it shows itself on the first run, or when the tray icon is off.

static HANDLE g_modThread, g_modReady, g_modMutex;
static DWORD g_modThreadId;
static std::atomic<bool> g_modStarted{false};

static DWORD WINAPI Hub_ModThread(void*) {
    SetThreadDpiAwarenessContext(DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2);
    MSG peek;
    PeekMessageW(&peek, nullptr, WM_USER, WM_USER, PM_NOREMOVE);  // Give the thread its queue now.
    if (FAILED(CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED))) { SetEvent(g_modReady); return 1; }
    Hub_MigrateStore();
    g_settings.animations = Wh_GetIntSetting(L"animations") != 0;
    Hub_DarkMenus();
    if (!Set_Create(false)) { SetEvent(g_modReady); CoUninitialize(); return 1; }
    HWND hwnd = g_setWin->hwnd;
    g_settingsWnd = hwnd;
    SetWindowSubclass(hwnd, Hub_SubProc, 7, 0);
    g_hub.taskbarCreated = RegisterWindowMessageW(L"TaskbarCreated");
    ChangeWindowMessageFilterEx(hwnd, g_hub.taskbarCreated, MSGFLT_ALLOW, nullptr);
    Hub_TrayUpdate(*g_setWin);
    SetTimer(hwnd, 0x4856, 1000, nullptr);
    Hub_Presence();
    if (Hub_AppInt(L"feedCheck", 1)) Hub_FeedStart(hwnd, false);
    SetTimer(hwnd, kHubFeedTimer, 24u * 60 * 60 * 1000, nullptr);
    Hub_WatchWindhawk(hwnd);
    const bool firstRun = Wh_GetIntValue(L"shownFirst", 0) == 0;
    if (firstRun || !g_hub.trayOn) {
        if (firstRun) Wh_SetIntValue(L"shownFirst", 1);
        ShowWindow(hwnd, SW_SHOW);
        ForceForeground(hwnd);
    } else {
        g_hub.shownOnce = true;
        KillTimer(hwnd, kSetTimerId);
        g_setWin->timer = false;
    }
    g_modStarted = true;
    SetEvent(g_modReady);
    MSG msg;
    while (GetMessageW(&msg, nullptr, 0, 0) > 0) {
        TranslateMessage(&msg);
        DispatchMessageW(&msg);
    }
    if (g_settingsWnd && IsWindow(g_settingsWnd)) DestroyWindow(g_settingsWnd);
    g_settingsWnd = nullptr;
    if (g_reader.joinable()) g_reader.join();
    if (g_feedThread.joinable()) g_feedThread.join();
    Hub_StopWatch();
    Hub_ClearPresence();
    g_setWin.reset();
    UnregisterClassW(kSettingsClass, (HINSTANCE)&__ImageBase);
    CoUninitialize();
    return 0;
}

// Windhawk's own install box says "failed" when the first copy hands over to an elevated one;
// this closes that box in this process only, for a few seconds after the handover.
static DWORD WINAPI Hub_CloseFalseFailure(void*) {
    const DWORD pid = GetCurrentProcessId();
    for (int i = 0; i < 60; i++) {
        EnumWindows([](HWND hwnd, LPARAM lp) -> BOOL {
            DWORD owner = 0;
            GetWindowThreadProcessId(hwnd, &owner);
            if (owner != (DWORD)lp) return TRUE;
            WCHAR cls[16]{}, title[32]{};
            GetClassNameW(hwnd, cls, 16);
            GetWindowTextW(hwnd, title, 32);
            if (wcscmp(cls, L"#32770") == 0 && wcscmp(title, L"Windhawk") == 0) PostMessageW(hwnd, WM_CLOSE, 0, 0);
            return TRUE;
        }, (LPARAM)pid);
        Sleep(250);
    }
    return 0;
}

BOOL WhTool_ModInit() {
    // Installing, updating and switching mods needs admin rights, so the tool process hands
    // over to an elevated copy of itself once, the same way Seamless Snipper does.
    if (!Hub_Elevated()) {
        WCHAR self[MAX_PATH]{};
        GetModuleFileNameW(nullptr, self, MAX_PATH);
        const std::wstring params = L"-windhawk-tool-mod \"" WH_MOD_ID L"\"";
        SHELLEXECUTEINFOW sei{sizeof(sei)};
        sei.fMask = SEE_MASK_FLAG_NO_UI;
        sei.lpVerb = L"runas";
        sei.lpFile = self;
        sei.lpParameters = params.c_str();
        sei.nShow = SW_HIDE;
        if (ShellExecuteExW(&sei)) ExitProcess(0);
        Wh_Log(L"Seamless Workshop needs admin rights and Windows did not give them.");
        return FALSE;
    }
    if (HANDLE closer = CreateThread(nullptr, 0, Hub_CloseFalseFailure, nullptr, 0, nullptr)) CloseHandle(closer);
    g_modMutex = CreateMutexW(nullptr, FALSE, L"Local\\SeamlessWorkshop.Instance");
    if (GetLastError() == ERROR_ALREADY_EXISTS) {
        if (g_modMutex) CloseHandle(g_modMutex);
        g_modMutex = nullptr;
        Wh_Log(L"Another copy of Seamless Workshop is already running.");
        return FALSE;
    }
    g_modReady = CreateEventW(nullptr, TRUE, FALSE, nullptr);
    g_modThread = CreateThread(nullptr, 0, Hub_ModThread, nullptr, 0, &g_modThreadId);
    if (!g_modThread || !g_modReady) return FALSE;
    WaitForSingleObject(g_modReady, 10000);
    return TRUE;
}

void WhTool_ModSettingsChanged() {
    if (HWND hwnd = g_settingsWnd) {
        PostMessageW(hwnd, WM_APP_SETTINGS_RELOAD, 0, 0);
        PostMessageW(hwnd, WM_HUB_MODCHANGED, 0, 0);
    }
}

void WhTool_ModUninit() {
    g_hub.quitting = true;
    if (HWND hwnd = g_settingsWnd) PostMessageW(hwnd, WM_CLOSE, 0, 0);
    if (g_modThread) {
        if (WaitForSingleObject(g_modThread, 5000) == WAIT_TIMEOUT) {
            PostThreadMessageW(g_modThreadId, WM_QUIT, 0, 0);
            WaitForSingleObject(g_modThread, 10000);
        }
        CloseHandle(g_modThread);
        g_modThread = nullptr;
    }
    if (g_modReady) { CloseHandle(g_modReady); g_modReady = nullptr; }
    if (g_modMutex) { CloseHandle(g_modMutex); g_modMutex = nullptr; }
}
#endif  // HUB_MOD
