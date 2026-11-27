// ==WindhawkMod==
// @id              seamless-windows-optimizer
// @name            Seamless Windows Optimizer
// @description     Free up space, turn off tracking and ads, remove apps you never use and speed Windows up, from one window
// @version         1.0.1
// @author          DavidHiFi
// @github          https://github.com/DavidHiFi
// @homepage        https://github.com/DavidHiFi/seamless-workshop
// @donateUrl       https://ko-fi.com/DavidHiFi
// @include         windhawk.exe
// @include         windhawk-mod.exe
// @include         windhawk-mod-elevated.exe
// @architecture    x86-64
// @compilerOptions -lole32 -loleaut32 -luuid -luser32 -lshell32 -lgdi32 -lwindowscodecs -ldwmapi -lshcore -ld2d1 -ldwrite -ld3d11 -ldxgi -ldxguid -ladvapi32 -lcomctl32 -luxtheme -lcomdlg32 -limm32 -lbcrypt -lwinhttp -lpowrprof -lurlmon
// ==/WindhawkMod==

// ==WindhawkModReadme==
/*
# Seamless Windows Optimizer

One window to look after Windows. Free up space, turn off tracking and ads, remove the
built-in apps you never use, speed up games and fix a Windows that misbehaves. It lives in
the tray and opens the same settings window as every other Seamless mod.

![Seamless Windows Optimizer](https://raw.githubusercontent.com/DavidHiFi/seamless-workshop/main/media/previews/seamless-windows-optimizer.png)

## What it does

- **Clean up**: finds the files Windows, your browsers, games and apps leave behind and
  shows how much each one holds. Nothing is deleted until you tick it and press Clean.
- **Privacy**: switches for tracking, ads, suggestions, activity history and the AI features.
- **Performance**: game and power settings, background services, and what starts with
  Windows.
- **Apps**: remove the built-in apps you never use, or uninstall any program.
- **Updates**: choose how Windows Update behaves, and hide an update you do not want.
- **Windows**: small fixes for File Explorer, the taskbar and Start.
- **Repair**: check system files, repair Windows, reset the network and rebuild icons.

Every switch says what it changes and what you lose. Settings changes can be undone: turn
the switch off and press Save. By default a Windows restore point is made before each change.

## How it works

The first time it opens, the mod downloads its small helper program from this project's
GitHub releases and checks it against a fixed fingerprint before it ever runs. The helper
does the cleaning and the changes, and never shows a window.

The mod needs admin rights, because most of what it changes belongs to Windows.

## Credits

- The cleaners are a Rust port of [BleachBit](https://github.com/bleachbit/bleachbit) by
  Andrew Ziem, under the GNU General Public License 3.0. The helper's source is in this
  project's `swo-engine` folder under the same license.
- Which settings and tools to offer took ideas from
  [Winhance](https://github.com/memstechtips/Winhance) and WTools. Everything here is written
  fresh. No code or text was copied from either.
*/
// ==/WindhawkModReadme==

// ==WindhawkModSettings==
/*
- settingsGlass: true
  $name: "Blurred settings window"
  $description: "On, the settings window is see-through glass with Windows acrylic behind it. Off, it is solid. Applies when you save."
- nativeSettingsTitleBar: false
  $name: "Native Windows title bar"
  $description: "Use the Windows title bar and window buttons for this settings window. Applies when you save."
- animations: true
  $name: "Animations"
  $description: "Off, everything snaps instantly: page changes, hover fades and switches."
- settingsTrayIcon: true
  $name: "Tray icon"
  $description: "Keeps Seamless Windows Optimizer in the system tray. Closing the window then hides it there. Click the icon to open it, right-click it to quit."
- motionEnabled: true
  $name: "Window animations for all mods"
  $description: "Off, every DavidHiFi mod opens and closes its windows instantly."
- motionSpeed: normal
  $name: "Animation speed for all mods"
  $description: "Mods set to Follow the global speed use this one."
  $options:
  - veryQuick: "Very quick"
  - quick: "Quick"
  - normal: "Normal"
  - relaxed: "Relaxed"
  - slow: "Slow"
- restorePoint: true
  $name: "Make a restore point first"
  $description: "Before a change to Windows settings or apps, save a Windows restore point so you can go back."
*/
// ==/WindhawkModSettings==

// Seamless Windows Optimizer: a Windhawk tool mod. It runs in its own elevated windhawk-mod
// process, keeps a tray icon and opens the shared Seamless settings window. The cleaning and the
// Windows changes happen in a small helper program (swo.exe, written in Rust) that the mod
// downloads once, checks against a fixed SHA-256 and runs hidden, reading its JSON lines.
//
// Build: assemble.py (the settings window is cut from the live Seamless Workshop source).

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
#include <urlmon.h>
#include <sddl.h>
#include <aclapi.h>
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
#include <condition_variable>
#include <deque>
#include <map>
#include <memory>
#include <set>
#include <string>
#include <vector>
#include <thread>
#include <mutex>
#include <regex>
#include <fstream>

#include <windhawk_tool_mod.h>

extern "C" IMAGE_DOS_HEADER __ImageBase;

constexpr UINT WM_HUB_OPEN = WM_APP + 10, WM_HUB_LINK = WM_APP + 11, WM_HUB_REBUILD = WM_APP + 12,
               WM_HUB_TRAY = WM_APP + 13, WM_HUB_MODCHANGED = WM_APP + 19;
constexpr UINT_PTR kHubArmTimer = 0x4855;  // Ends the five-second "click again" window.

static std::wstring GetStringSetting(PCWSTR name) {
    PCWSTR raw = Wh_GetStringSetting(name);
    std::wstring value = raw ? raw : L"";
    if (raw) Wh_FreeStringSetting(raw);
    return value;
}

// The global animation switch and speed every DavidHiFi mod reads. A mod that finds no key
// treats it as on and Normal.
static void Hub_WriteMotion() {
    static const PCWSTR kSpeeds[] = {L"veryQuick", L"quick", L"normal", L"relaxed", L"slow"};
    const DWORD enabled = Wh_GetIntSetting(L"motionEnabled") != 0 ? 1 : 0;
    std::wstring speed = GetStringSetting(L"motionSpeed");
    bool known = false;
    for (PCWSTR s : kSpeeds) known = known || speed == s;
    if (!known) speed = L"normal";
    HKEY key;
    if (RegCreateKeyExW(HKEY_CURRENT_USER, L"Software\\DavidHiFi\\Motion", 0, nullptr, 0, KEY_SET_VALUE, nullptr,
                        &key, nullptr) != ERROR_SUCCESS)
        return;
    RegSetValueExW(key, L"Enabled", 0, REG_DWORD, (const BYTE*)&enabled, sizeof(enabled));
    RegSetValueExW(key, L"Speed", 0, REG_SZ, (const BYTE*)speed.c_str(), (DWORD)((speed.size() + 1) * sizeof(WCHAR)));
    RegCloseKey(key);
}

struct {
    bool animations = true;
} g_settings;

// Only reached from the tray icon or a second launch, both of which the owner started.
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
struct SetPaint;
struct SetItem;
struct SetHit;
static float Hub_MaxW(const SetWindow& w);
static bool Hub_TwoCol(const SetWindow& w);
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

constexpr WCHAR kSettingsClass[] = L"SeamlessWindowsOptimizerWindow";
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
// The sidebar pages, in order. Every page number in the code is one of these names.
enum { kPgOverview, kPgClean, kPgPrivacy, kPgPerf, kPgApps, kPgUpdates, kPgWindows, kPgRepair, kPgLook, kPgAbout };
static std::vector<SetField> Set_MakeFields() {
    using K = SetField;
    return {
{K::Check, L"settingsGlass", L"Blurred settings window", L"On, the settings window is see-through glass with Windows acrylic behind it. Off, it is solid. Applies when you save.", L"1", {}, 0, 100, kPgLook, L"Settings window"},
{K::Check, L"nativeSettingsTitleBar", L"Native Windows title bar", L"Use the Windows title bar and window buttons for this settings window. Applies when you save.", L"0", {}, 0, 100, kPgLook, L"Settings window"},
{K::Check, L"animations", L"Animations", L"Off, everything snaps instantly: page changes, hover fades and switches.", L"1", {}, 0, 100, kPgLook, L"Settings window"},
{K::Check, L"settingsTrayIcon", L"Tray icon", L"Keeps Seamless Windows Optimizer in the system tray. Closing the window then hides it there. Click the icon to open it, right-click it to quit.", L"1", {}, 0, 100, kPgLook, L"Settings window"},
{K::Check, L"motionEnabled", L"Window animations for all mods", L"Off, every DavidHiFi mod opens and closes its windows instantly.", L"1", {}, 0, 100, kPgLook, L"All mods"},
{K::Choice, L"motionSpeed", L"Animation speed for all mods", L"Mods set to Follow the global speed use this one.", L"normal", {{L"veryQuick", L"Very quick"}, {L"quick", L"Quick"}, {L"normal", L"Normal"}, {L"relaxed", L"Relaxed"}, {L"slow", L"Slow"}}, 0, 100, kPgLook, L"All mods"},
{K::Check, L"restorePoint", L"Make a restore point first", L"Before a change to Windows settings or apps, save a Windows restore point so you can go back.", L"1", {}, 0, 100, kPgOverview, L"Safety"}
    };
}

struct SetPageInfo {
    PCWSTR name, intro;
    WCHAR glyph;
};
static const SetPageInfo kSetPages[] = {
{L"Overview", L"How your PC is doing right now, and the quick jobs: find junk, make a restore point.", 0xE80F},
{L"Clean up", L"Find the files Windows and your apps leave behind, then clear the ones you tick. Nothing goes until you press Clean.", 0xEA99},
{L"Privacy", L"Turn off tracking, ads and the AI features. Each switch shows what it does; Save applies them and can always be undone.", 0xE72E},
{L"Performance", L"Faster start, smoother games and less going on in the background. Turn off what starts with Windows here too.", 0xEC4A},
{L"Apps", L"Remove the built-in apps you never use, or uninstall any program.", 0xE71D},
{L"Updates", L"Choose how Windows Update behaves, and hide an update you do not want.", 0xE895},
{L"Windows", L"Small fixes for File Explorer, the taskbar and Start.", 0xE770},
{L"Repair", L"Fix a Windows that misbehaves: check system files, reset the network, rebuild icons.", 0xE90F},
{L"Look", L"How this window looks, and whether it keeps a tray icon.", 0xE790},
{L"About", L"Version, credits and links.", 0xE946},
};
constexpr int kSetPageCount = (int)(sizeof(kSetPages) / sizeof(kSetPages[0]));
static_assert(kSetPageCount == kPgAbout + 1, "one name per page");
// About sits apart at the end of the sidebar, as in Seamless Dictate.
constexpr int kSetAboutPage = kSetPageCount - 1;
constexpr float kSetAboutGap = 17;

// All sizes are DIPs; the render target does the scaling.
constexpr float kSetPadX = 40, kSetMaxW = 720, kSetRowMin = 56, kSetRowGap = 8, kSetBoxH = 32, kSetRowPad = 16,
                kSetColGap = 24, kSetColMin = 430,
                kSetDropItem = 32, kSetRailTop = 76, kSetRailItem = 36, kSetRailPitch = 40;
constexpr int kSetDropMax = 9;  // A dropdown with more options than this scrolls.
// The sidebar is a floating dock: dragged between min and max, or collapsed to an icon rail.
constexpr float kSetDockGap = 10, kSetRailDef = 232, kSetRailMin = 200, kSetRailMax = 380, kSetRailMini = 60,
                kSetRailSnap = 130, kSetEdgeGrab = 5;
// The footer is a floating pill dock at the bottom right of the page.
constexpr float kSetFootBtnH = 36, kSetFootPad = 8, kSetFootH = kSetFootBtnH + 2 * kSetFootPad, kSetFootGap = 14;
// The glass tint is one layer over the whole window, title bar included, so the two always match.
constexpr float kSetGlassTint = 0.55f, kSetNativeFade = 56;
constexpr float kSetEdgeW = 2, kSetRadius = 16;
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
    L"https://github.com/DavidHiFi/seamless-workshop/issues/new?title=%5BSeamless%20Windows%20Optimizer%5D%20";
constexpr PCWSTR kSetTitle = L"Seamless Windows Optimizer";
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
    float colW = 0;  // Width of one column when the page is laid out in two; 0 on a one-column page.
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

static float Set_Rad(const D2D1_RECT_F& r, float most = kSetRadius) {
    return std::min(most, std::min(r.right - r.left, r.bottom - r.top) / 2);
}

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
            // The hover look of every card: a faint blue to mauve wash and the 2 px gradient ring.
            float ringW = kSetEdgeW, rad = std::min(12.0f, (r.bottom - r.top) / 2);
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
            rt->DrawText(L"\uEAB6", 1, s.fGlyphS.get(), {slotLeft, r.top, slotRight, r.bottom}, solid(col, 1));  // chevron_right
        } else if (m.checked) {
            rt->DrawText(L"\uEAB2", 1, s.fGlyph.get(), {slotLeft, r.top, slotRight, r.bottom},  // check
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
        if (w.fRailName && Set_TextW(w.fRailName.get(), L"Optimizer") <= railW) break;
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
    const float cap = std::floor((w.colW > 0 ? w.colW : w.contentW) * 0.5f);
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

// A wide page in two columns. The page was built one column wide, so every height is already
// right. Status lines and the About card at the top stay page-wide. After them each heading
// starts a section; whole sections go left until the two sides are about even, the rest go
// right. A page with one section puts its rows two across instead.
static void Set_Columns(SetWindow& w, float fullW, float& y) {
    auto& v = w.items;
    size_t s = 0;
    while (s < v.size() && (v[s].type == SetItem::Banner || v[s].type == SetItem::About || v[s].type == SetItem::Support)) {
        v[s].x = w.contentX; v[s].w = fullW; s++;
    }
    if (s == v.size()) return;
    struct Sec { size_t a, b; float h; };
    std::vector<Sec> secs;
    for (size_t i = s; i < v.size();) {
        size_t j = i + 1;
        while (j < v.size() && v[j].type != SetItem::Group) j++;
        secs.push_back({i, j, v[j - 1].y + v[j - 1].h - v[i].y});
        i = j;
    }
    const float top = v[s].y, left = w.contentX, right = w.contentX + w.colW + kSetColGap, secGap = 22;
    if (secs.size() == 1) {
        size_t a = secs[0].a;
        float cy = top;
        if (v[a].type == SetItem::Group) { v[a].x = left; v[a].w = fullW; v[a].y = cy; cy += v[a].h + 6; a++; }
        for (size_t i = a; i < secs[0].b; i += 2) {
            const bool pair = i + 1 < secs[0].b;
            const float h = pair ? std::max(v[i].h, v[i + 1].h) : v[i].h;
            v[i].x = left; v[i].w = w.colW; v[i].y = cy; v[i].h = h;
            if (pair) { v[i + 1].x = right; v[i + 1].w = w.colW; v[i + 1].y = cy; v[i + 1].h = h; }
            cy += h + kSetRowGap;
        }
        y = cy;
        return;
    }
    float total = 0;
    for (auto& sec : secs) total += sec.h + secGap;
    size_t split = 1;
    float best = total, run = 0;
    for (size_t k = 1; k < secs.size(); k++) {
        run += secs[k - 1].h + secGap;
        const float tall = std::max(run, total - run);
        if (tall < best) { best = tall; split = k; }
    }
    float cy[2] = {top, top};
    for (size_t n = 0; n < secs.size(); n++) {
        const int c = n < split ? 0 : 1;
        const float dy = cy[c] - v[secs[n].a].y;
        for (size_t i = secs[n].a; i < secs[n].b; i++) { v[i].y += dy; v[i].x = c ? right : left; v[i].w = w.colW; }
        cy[c] += secs[n].h + secGap;
    }
    y = std::max(cy[0], cy[1]) - secGap + kSetRowGap;
}

// Lays out the current page's items for the current width.
static void Set_BuildPage(SetWindow& w) {
    w.items.clear();
    const float space = Set_RailSpace(w), avail = w.cw - space;
    w.contentW = std::clamp(avail - 2 * kSetPadX, 420.0f, std::max(420.0f, Hub_MaxW(w)));
    w.contentX = space + std::max(kSetPadX, (avail - w.contentW) / 2);
    float introH = Set_TextH(w.fIntro.get(), Hub_PageIntro(w), w.contentW);
    float y = 36 + 36 + 4 + introH + 24;
    const float fullW = w.contentW;
    w.colW = 0;
    if (Hub_TwoCol(w) && fullW >= 2 * kSetColMin + kSetColGap) {
        w.colW = std::floor((fullW - kSetColGap) / 2);
        w.contentW = w.colW;  // Everything below measures against one column.
    }
    if (w.page != kSetAboutPage) {
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
        add(SetItem::Link, 56, L"BleachBit by Andrew Ziem", L"The cleaners are a Rust port of BleachBit's, under the GNU GPL", L"https://github.com/bleachbit/bleachbit");
        add(SetItem::Link, 56, L"Ideas from Winhance and WTools", L"Which settings and tools to offer. Written fresh, no code taken", L"https://github.com/memstechtips/Winhance");
        group(L"Project");
        add(SetItem::Link, 56, L"Project page on GitHub", L"github.com/DavidHiFi/seamless-workshop", kSetRepoUrl);
        add(SetItem::Link, 56, L"Report a problem", L"Opens a new issue on GitHub, with the app's name filled in", kSetBugUrl);
    }
    if (w.colW > 0) {
        Set_Columns(w, fullW, y);
        w.contentW = fullW;
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
    const float rad = Set_Rad(box);
    p.Round(box, rad, kSetBoxFill);
    float g = std::max(Set_GlowOf(w, 6000 + k), active ? 1.0f : 0.0f);
    p.Edge(box, rad, mocha::overlay0, 0.7f * (1 - g));
    p.GradRing(box, rad, g);
}

static void Set_DrawRow(SetPaint& p, SetWindow& w, const SetItem& it) {
    if (Hub_DrawRow(p, w, it)) return;
    const SetField& f = w.fields[it.field];
    int k = it.field;
    D2D1_RECT_F row = Set_RowRect(w, it);
    p.Round(row, kSetRadius, mocha::base);
    p.Round(row, kSetRadius, mocha::surface0, 0.32f);
    float hov = Set_GlowOf(w, 1000 + k);
    p.Edge(row, kSetRadius, mocha::surface2, 0.55f * (1 - hov));
    p.GradFill(row, kSetRadius, 0.13f * hov);
    p.GradRing(row, kSetRadius, hov);
    if (w.kbd && w.focus == k) p.GradRing(row, kSetRadius, 1.0f);

    float textW = (w.colW > 0 ? row.right - row.left : w.contentW) - 2 * kSetRowPad - Set_ControlW(f) - 24;
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
    const D2D1_RECT_F r = Set_RowRect(w, it);
    p.Text(w.fSection.get(), up, {r.left + 4, r.top, r.right, r.bottom}, mocha::overlay2);
}

// The resting card every row uses: base, a light lift and a soft gray edge that hands over to
// the hover ring.
static void Set_DrawCard(SetPaint& p, const D2D1_RECT_F& row, float hov) {
    p.Round(row, kSetRadius, mocha::base);
    p.Round(row, kSetRadius, mocha::surface0, 0.32f);
    p.Edge(row, kSetRadius, mocha::surface2, 0.55f * (1 - hov));
}

static void Set_DrawLinkRow(SetPaint& p, SetWindow& w, const SetItem& it, int idx) {
    if (Hub_DrawLink(p, w, it, idx)) return;
    D2D1_RECT_F row = Set_RowRect(w, it);
    float hov = Set_GlowOf(w, 3000 + idx);
    Set_DrawCard(p, row, hov);
    p.GradFill(row, kSetRadius, 0.13f * hov);
    p.GradRing(row, kSetRadius, hov);
    p.Text(w.fLabel.get(), it.text, {row.left + kSetRowPad, row.top + 9, row.right - 50, row.top + 30}, mocha::text);
    p.Text(w.fHint.get(), it.sub, {row.left + kSetRowPad, row.top + 30, row.right - 50, row.bottom - 4}, mocha::subtext0);
    p.Glyph(w.fIcon.get(), Hub_LinkGlyph(it.url), {row.right - 46, row.top, row.right - 12, row.bottom},
            it.url == L"hub:remove" ? mocha::red : mocha::subtext1);
}

static void Set_DrawSupport(SetPaint& p, SetWindow& w, const SetItem& it, int idx) {
    D2D1_RECT_F row = Set_RowRect(w, it);
    float card = std::max(Set_GlowOf(w, 3700 + idx), Set_GlowOf(w, 3500 + idx));
    Set_DrawCard(p, row, card);
    p.GradFill(row, kSetRadius, 0.13f * card);
    p.GradRing(row, kSetRadius, card);
    p.Text(w.fLabel.get(), it.text, {row.left + kSetRowPad, row.top + 14, row.right - 180, row.top + 36}, mocha::text);
    p.Text(w.fHint.get(), it.sub, {row.left + kSetRowPad, row.top + 38, row.right - 180, row.bottom - 6}, mocha::subtext0);
    D2D1_RECT_F b = Set_SupportButton(w, it);
    float hov = Set_GlowOf(w, 3500 + idx);
    p.GradFill(b, Set_Rad(b), 0.85f + 0.15f * hov);
    p.GradRing(b, Set_Rad(b), hov);
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
        const WCHAR glyph = 0xEC4A;
        auto br = p.G({mc.x - 19, mc.y - 19, mc.x + 19, mc.y + 19});
        if (br) p.rt->DrawText(&glyph, 1, w.fIconL.get(), mark, br.get());
        p.rt->SetTransform(old);
    }
    float x = mark.right + 20;
    p.Text(w.fBig.get(), L"Seamless Windows Optimizer", {x, row.top + 18, row.right - 16, row.top + 46}, mocha::text);
#ifdef WH_MOD_VERSION
    std::wstring ver = std::wstring(L"Version ") + WH_MOD_VERSION + L"  \u00B7  Open source  \u00B7  Runs on Windhawk";
#else
    std::wstring ver = L"MIT license  \u00B7  A Windhawk mod";
#endif
    p.Text(w.fHint.get(), ver, {x, row.top + 48, row.right - 16, row.top + 68}, mocha::subtext0);
    p.Text(w.fHint.get(), L"Clean up, private and quick: one window to look after Windows.",
           {x, row.top + 72, row.right - 16, row.top + 110}, mocha::subtext1);
    p.Text(w.fHint.get(), L"Made by DavidHiFi. Windhawk itself is made by Ramen Software.",
           {x, row.top + 112, row.right - 16, row.bottom - 8}, mocha::overlay2);
}

static void Hub_PlaceCode(SetWindow& w);  // features.inc: the Editor's code box.
static bool Hub_CodeFocused();

static void Set_DrawBanner(SetPaint& p, SetWindow& w, const SetItem& it) {
    D2D1_RECT_F r = Set_RowRect(w, it);
    if (it.url == L"hub:code") {  // The code box's frame, drawn like a text box.
        const float g = Hub_CodeFocused() ? 1.0f : 0.0f;
        p.Round(r, kSetRadius, kSetBoxFill);
        p.Edge(r, kSetRadius, mocha::overlay0, 0.7f * (1 - g));
        p.GradRing(r, kSetRadius, g);
        if (!it.text.empty()) p.Text(w.fHint.get(), it.text, {r.left + 14, r.top + 12, r.right - 14, r.bottom - 10}, mocha::text);
        return;
    }
    p.Round(r, kSetRadius, mocha::peach, 0.14f);
    p.Text(w.fHint.get(), it.text, {r.left + 16, r.top + 14, r.right - 16, r.bottom - 8}, mocha::peach);
}

// A floating dock: soft shadow, mantle fill, a quiet 1px edge at rest and the blue to mauve
// edge as the pointer comes over it.
static void Set_DrawDock(SetPaint& p, SetWindow& w, const D2D1_RECT_F& d, float rad, float fill, float glow) {
    p.Round({d.left, d.top + 3, d.right, d.bottom + 5}, rad + 2, mocha::crust, w.glass ? 0.28f : 0.5f);
    p.Round(d, rad, mocha::mantle, fill);  // Hover lights only the edge: a wash showed as a blue blob down the left.
    p.Edge(d, rad, mocha::surface1, 0.75f * (1 - glow));
    p.GradRing(d, rad, glow);
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
    Set_DrawDock(p, w, d, kSetRadius, w.glass ? 0.58f : 1.0f, std::max(w.railGlow * 0.85f, edge));

    D2D1_RECT_F tb = Set_RailToggleRect(w);
    float th = Set_GlowOf(w, 42);
    const float tr = Set_Rad(tb);
    p.Round(tb, tr, mocha::surface0, 0.45f + 0.25f * th);
    p.GradFill(tb, tr, 0.16f * th);
    p.GradRing(tb, tr, 0.9f * th);
    if (w.kbd && w.focus == -20) p.GradRing(tb, tr, 1);
    Set_DrawPanelIcon(p, tb, open, th > 0.5f ? mocha::text : mocha::subtext1);

    p.rt->PushAxisAlignedClip(D2D1::RectF(d.left, d.top, d.right - 6, d.bottom), D2D1_ANTIALIAS_MODE_ALIASED);
    if (textA > 0.003f) {
        float my = (tb.top + tb.bottom) / 2;
        Set_DrawMark(p, w.fIcon.get(), {d.left + 56, my - 13, d.left + 82, my + 13}, textA);
    }
    p.Text(w.fRailName.get(), L"Seamless", {d.left + 90, d.top + 9, d.left + w.railW - 10, d.top + 33}, mocha::text, textA);
    p.Text(w.fRailName.get(), L"Optimizer", {d.left + 90, d.top + 32, d.left + w.railW - 10, d.top + 56}, mocha::text, textA);
    for (int i = 0; i < kSetPageCount; i++) {
        D2D1_RECT_F r = Set_RailRect(w, i);
        if (i == kSetAboutPage) {
            float ly = std::round(r.top - (kSetAboutGap + kSetRailPitch - kSetRailItem) / 2);
            p.Fill({r.left + 6, ly, r.right - 6, ly + 1}, mocha::surface1, 0.7f);
        }
        float hov = Set_GlowOf(w, 100 + i);
        bool act = i == w.page;
        const float rr = Set_Rad(r);
        if (act) {
            p.GradFill(r, rr, 0.22f);
            p.GradRing(r, rr, 0.5f);
            D2D1_RECT_F bar{r.left, r.top + 8, r.left + 3, r.bottom - 8};
            p.GradFill({bar.left, bar.top, bar.left + 3, bar.bottom}, 1.5f, 1);
        } else {
            p.Round(r, rr, mocha::surface0, 0.28f);
            p.Edge(r, rr, mocha::surface2, 0.5f * (1 - hov));
            p.GradFill(r, rr, 0.10f * hov);
            p.GradRing(r, rr, 0.8f * hov);
        }
        if (w.kbd && w.focus == -10 - i) p.GradRing(r, rr, 1);
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
    p.Edge(d, rad, mocha::overlay0, 0.9f * (1 - w.footGlow));
    p.GradRing(d, rad, w.footGlow);
    UINT32 sc;
    std::wstring status = Set_FooterStatus(w, &sc);
    float sw = Set_FooterStatusW(w);
    if (sw > 0) p.Text(w.fStatusLine.get(), status, {d.left + 18, d.top, d.left + 18 + sw, d.bottom}, sc);
    static const PCWSTR names[3] = {L"Reset to suggested", L"Cancel", L"Save"};
    for (int i = 0; i < 3; i++) {
        D2D1_RECT_F b = Set_FooterButton(w, i);
        float hov = Set_GlowOf(w, 10 + i);
        p.Round(b, brad, mocha::base, 0.98f);
        p.Edge(b, brad, mocha::overlay0, 0.78f * (1 - hov));
        p.GradRing(b, brad, hov);
        p.Text(w.fButton.get(), names[i], b, mocha::text, w.saving ? 0.5f : 1.0f);
        if (w.kbd && w.focus == -1 - i) p.GradRing(b, brad, 1);
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
    p.Round(shadow, kSetRadius + 2, mocha::crust, 0.6f);
    p.Round(r, kSetRadius, mocha::mantle);
    p.GradRing(r, kSetRadius, 0.9f);
    const float right = r.right - (scrolls ? 12 : 4);
    for (int v = 0; v < vis; v++) {
        int i = w.dropTop + v;
        if (i >= n) break;
        D2D1_RECT_F it{r.left + 4, r.top + 4 + v * kSetDropItem, right, r.top + 4 + (v + 1) * kSetDropItem};
        bool sel = f.cur == f.options[i].first;
        if (i == w.dropHover) {
            p.GradFill(it, Set_Rad(it, kSetRadius - 4), 0.28f);  // Inset 4 in a 16 corner: 12.
            p.GradRing(it, Set_Rad(it, kSetRadius - 4), 0.6f);
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
    const WCHAR mark = 0xEC4A;
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
            // The window's acrylic already carries the tint (Set_ApplyFrame), title bar included.
        } else if (false) {
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
    Hub_PlaceCode(w);
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
    if (!first && native == w.nativeTitle && glass == w.glass) return;  // A title bar switch re-runs the accent below.
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
            // Same as the launcher grid. With the Windows title bar the tint is in here instead of
            // on the page, so the title bar gets it too: crust at the page's 55%.
            const int tint = native ? (int)(((DWORD)(kSetGlassTint * 255 + 0.5f) << 24) | (mocha::crust & 0xFF) << 16 |
                                            (mocha::crust & 0xFF00) | (mocha::crust >> 16 & 0xFF))
                                    : (int)0x012E1E1E;
            SetAccentPolicy policy{4 /* ACCENT_ENABLE_ACRYLICBLURBEHIND */, 2, tint, 0};
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
    HWND hwnd = CreateWindowExW(0, kSettingsClass, L"Seamless Windows Optimizer", style,
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

// ---- Seamless Windows Optimizer ----------------------------------------------------------
// Everything below this line is the optimizer itself: the catalog, the helper program, the
// pages, the tray icon and the mod's life cycle.

#ifndef NT_SUCCESS
#define NT_SUCCESS(s) (((NTSTATUS)(s)) >= 0)
#endif

constexpr PCWSTR kOptEngineSha = L"ace07a04408307adf96e11c350899f0b9c0f37ed62dc05e9e967b96ce950ce48";
constexpr PCWSTR kOptEngineUrl = L"https://github.com/DavidHiFi/seamless-workshop/releases/download/swo-engine-v1.0.1/swo.exe";
constexpr PCWSTR kOptEngineVersion = L"1.0.1";
constexpr PCWSTR kOptName = L"Seamless Windows Optimizer";
constexpr UINT_PTR kOptFeedTimer = 0x4857;  // Batches progress lines into one rebuild.
constexpr ULONGLONG kOptArmMs = 5000;
constexpr DWORD kOptEngineMax = 8u * 1024 * 1024;
constexpr size_t kOptOutputMax = 32u * 1024 * 1024;

// One row of the catalog the helper program knows. Generated from its catalog by assemble.py.
struct OptItem {
    PCWSTR id;
    int page;
    PCWSTR group, name, desc, warn, kind, risk;
    bool admin, pick, reboot, undo;
};

static const OptItem kOptItems[] = {
    {L"clean.windows-temp", kPgClean, L"Windows", L"Windows temp files", L"Leftovers from installers and updates in the Windows temp folder.", L"", L"clean", L"safe", true, true, false, false},
    {L"clean.user-temp", kPgClean, L"Windows", L"Your temp files", L"Leftovers programs put in your own temp folder.", L"", L"clean", L"safe", false, true, false, false},
    {L"clean.update-downloads", kPgClean, L"Windows", L"Windows Update downloads", L"Update files Windows already installed and no longer needs.", L"", L"clean", L"safe", true, true, false, false},
    {L"clean.delivery-optimization", kPgClean, L"Windows", L"Update sharing cache", L"Update pieces Windows kept to share with other PCs.", L"", L"clean", L"safe", true, true, false, false},
    {L"clean.error-reports", kPgClean, L"Windows", L"Error reports", L"Problem reports Windows already sent or no longer needs.", L"", L"clean", L"safe", true, true, false, false},
    {L"clean.windows-logs", kPgClean, L"Windows", L"Old Windows logs", L"Setup and repair logs older than a week.", L"", L"clean", L"safe", true, true, false, false},
    {L"clean.system-dumps", kPgClean, L"Windows", L"System crash dumps", L"Memory dumps Windows saved after a blue screen. One can be many gigabytes.", L"These explain a blue screen. Keep them while you are chasing one.", L"clean", L"moderate", true, false, false, false},
    {L"clean.app-dumps", kPgClean, L"Windows", L"App crash dumps", L"Dumps programs left when they crashed.", L"These name the app or mod that crashed. Keep them while you are chasing a crash.", L"clean", L"moderate", false, false, false, false},
    {L"clean.thumbnails", kPgClean, L"Windows", L"Picture previews", L"Small previews of your pictures and videos. Explorer makes them again when needed.", L"", L"clean", L"safe", false, false, false, false},
    {L"clean.recycle-bin", kPgClean, L"Windows", L"Recycle Bin", L"Everything in the Recycle Bin on every drive.", L"Files in the Recycle Bin are gone for good after this.", L"clean", L"moderate", false, true, false, false},
    {L"clean.directx-shaders", kPgClean, L"Games", L"DirectX shader cache", L"Shaders Windows saved for games and apps.", L"Games rebuild these, so each game may stutter for a minute the first time you play it.", L"clean", L"moderate", false, false, false, false},
    {L"clean.nvidia-shaders", kPgClean, L"Games", L"NVIDIA shader cache", L"Shaders the NVIDIA driver saved for games.", L"Games rebuild these, so each game may stutter for a minute the first time you play it.", L"clean", L"moderate", false, false, false, false},
    {L"clean.amd-shaders", kPgClean, L"Games", L"AMD shader cache", L"Shaders the AMD driver saved for games.", L"Games rebuild these, so each game may stutter for a minute the first time you play it.", L"clean", L"moderate", false, false, false, false},
    {L"clean.steam-web", kPgClean, L"Games", L"Steam web cache", L"Store and community pages Steam saved.", L"", L"clean", L"safe", false, true, false, false},
    {L"clean.edge-cache", kPgClean, L"Browsers", L"Edge cache", L"Pages and pictures Edge saved to load sites faster.", L"", L"clean", L"safe", false, true, false, false},
    {L"clean.edge-history", kPgClean, L"Browsers", L"Edge history", L"The list of sites you visited in Edge.", L"", L"clean", L"advanced", false, false, false, false},
    {L"clean.edge-cookies", kPgClean, L"Browsers", L"Edge cookies", L"Site cookies Edge keeps.", L"Signs you out of every website.", L"clean", L"advanced", false, false, false, false},
    {L"clean.chrome-cache", kPgClean, L"Browsers", L"Chrome cache", L"Pages and pictures Chrome saved to load sites faster.", L"", L"clean", L"safe", false, true, false, false},
    {L"clean.chrome-history", kPgClean, L"Browsers", L"Chrome history", L"The list of sites you visited in Chrome.", L"", L"clean", L"advanced", false, false, false, false},
    {L"clean.chrome-cookies", kPgClean, L"Browsers", L"Chrome cookies", L"Site cookies Chrome keeps.", L"Signs you out of every website.", L"clean", L"advanced", false, false, false, false},
    {L"clean.brave-cache", kPgClean, L"Browsers", L"Brave cache", L"Pages and pictures Brave saved to load sites faster.", L"", L"clean", L"safe", false, true, false, false},
    {L"clean.brave-history", kPgClean, L"Browsers", L"Brave history", L"The list of sites you visited in Brave.", L"", L"clean", L"advanced", false, false, false, false},
    {L"clean.brave-cookies", kPgClean, L"Browsers", L"Brave cookies", L"Site cookies Brave keeps.", L"Signs you out of every website.", L"clean", L"advanced", false, false, false, false},
    {L"clean.vivaldi-cache", kPgClean, L"Browsers", L"Vivaldi cache", L"Pages and pictures Vivaldi saved to load sites faster.", L"", L"clean", L"safe", false, true, false, false},
    {L"clean.vivaldi-history", kPgClean, L"Browsers", L"Vivaldi history", L"The list of sites you visited in Vivaldi.", L"", L"clean", L"advanced", false, false, false, false},
    {L"clean.vivaldi-cookies", kPgClean, L"Browsers", L"Vivaldi cookies", L"Site cookies Vivaldi keeps.", L"Signs you out of every website.", L"clean", L"advanced", false, false, false, false},
    {L"clean.firefox-cache", kPgClean, L"Browsers", L"Firefox cache", L"Pages and pictures Firefox saved to load sites faster.", L"", L"clean", L"safe", false, true, false, false},
    {L"clean.firefox-cookies", kPgClean, L"Browsers", L"Firefox cookies", L"Site cookies Firefox keeps.", L"Signs you out of every website.", L"clean", L"advanced", false, false, false, false},
    {L"clean.discord-cache", kPgClean, L"Apps", L"Discord cache", L"Pictures and code Discord saved to start faster.", L"", L"clean", L"safe", false, true, false, false},
    {L"clean.vscode-cache", kPgClean, L"Apps", L"VS Code cache", L"Pictures and code VS Code saved to start faster.", L"", L"clean", L"safe", false, true, false, false},
    {L"clean.teams-cache", kPgClean, L"Apps", L"Teams (classic) cache", L"Pictures and code Teams (classic) saved to start faster.", L"", L"clean", L"safe", false, true, false, false},
    {L"clean.spotify-cache", kPgClean, L"Apps", L"Spotify cache", L"Songs Spotify saved while streaming.", L"", L"clean", L"safe", false, true, false, false},
    {L"clean.recent-files", kPgClean, L"Traces", L"Recent files list", L"The list of files you opened lately, shown in Explorer and Start.", L"", L"clean", L"moderate", false, false, false, false},
    {L"clean.office-recent", kPgClean, L"Traces", L"Office recent files", L"The list of documents you opened lately in Office.", L"", L"clean", L"moderate", false, false, false, false},
    {L"clean.reg-startup", kPgClean, L"Registry", L"Start-up entries for removed apps", L"Removes start-up entries that point to apps that are gone.", L"", L"clean", L"safe", true, false, false, true},
    {L"clean.reg-uninstall", kPgClean, L"Registry", L"Installed apps entries for removed apps", L"Removes entries from the installed apps list for apps whose files are gone.", L"", L"clean", L"moderate", true, false, false, true},
    {L"clean.reg-app-paths", kPgClean, L"Registry", L"Run box shortcuts for removed apps", L"Removes Run box shortcuts that point to apps that are gone.", L"", L"clean", L"safe", true, false, false, true},
    {L"privacy.telemetry", kPgPrivacy, L"Diagnostics", L"Send only required diagnostic data", L"Windows sends the least usage data your edition allows and stops fetching extra data rules.", L"", L"toggle", L"safe", true, true, false, true},
    {L"privacy.diagtrack", kPgPrivacy, L"Diagnostics", L"Stop the usage data service", L"Turns off the background service that gathers and uploads usage data.", L"", L"toggle", L"moderate", true, true, false, true},
    {L"privacy.feedback", kPgPrivacy, L"Diagnostics", L"No feedback questions", L"Windows stops popping up questions asking how it is doing.", L"", L"toggle", L"safe", true, true, false, true},
    {L"privacy.data-tasks", kPgPrivacy, L"Diagnostics", L"Turn off data collection tasks", L"Switches off the scheduled jobs that collect app, disk and device usage for Microsoft.", L"", L"toggle", L"moderate", true, true, false, true},
    {L"privacy.tailored", kPgPrivacy, L"Diagnostics", L"No tailored experiences", L"Microsoft stops using your diagnostic data to pick tips and offers for you.", L"", L"toggle", L"safe", false, true, false, true},
    {L"privacy.error-reporting", kPgPrivacy, L"Diagnostics", L"Turn off error reporting", L"Crashes are no longer reported to Microsoft.", L"Can also stop the crash files that show which mod or app crashed.", L"toggle", L"moderate", true, false, false, true},
    {L"privacy.advertising-id", kPgPrivacy, L"Ads and suggestions", L"Turn off the advertising ID", L"Apps can no longer use a shared ID to show you targeted ads.", L"", L"toggle", L"safe", true, true, false, true},
    {L"privacy.suggested-apps", kPgPrivacy, L"Ads and suggestions", L"Stop suggested apps installing", L"Windows stops quietly adding promoted apps and games to Start.", L"", L"toggle", L"safe", true, true, false, true},
    {L"privacy.start-suggestions", kPgPrivacy, L"Ads and suggestions", L"No suggestions in Start and Settings", L"Removes promoted apps, account nags and suggested content from Start and Settings.", L"", L"toggle", L"safe", false, true, false, true},
    {L"privacy.tips", kPgPrivacy, L"Ads and suggestions", L"No tips and set-up nags", L"Stops the tips, the welcome tour after updates and the finish setting up your device screen.", L"", L"toggle", L"safe", true, true, false, true},
    {L"privacy.lock-screen-ads", kPgPrivacy, L"Ads and suggestions", L"No ads on the lock screen", L"Removes the fun facts and promotions drawn over the lock screen picture.", L"", L"toggle", L"safe", false, true, false, true},
    {L"privacy.explorer-ads", kPgPrivacy, L"Ads and suggestions", L"No ads in File Explorer", L"Stops File Explorer showing offers for OneDrive and Microsoft 365.", L"", L"toggle", L"safe", false, true, false, true},
    {L"privacy.suggestion-toasts", kPgPrivacy, L"Ads and suggestions", L"No suggestion notifications", L"Windows stops sending notifications that suggest ways to use it.", L"", L"toggle", L"safe", false, true, false, true},
    {L"privacy.activity-history", kPgPrivacy, L"Activity and search", L"Turn off activity history", L"Windows stops keeping and uploading a timeline of the apps and files you used.", L"", L"toggle", L"safe", true, true, false, true},
    {L"privacy.web-search", kPgPrivacy, L"Activity and search", L"No web results in search", L"Start and taskbar search look only at this PC and stop sending what you type to Bing.", L"File Explorer's search box also stops listing your past searches.", L"toggle", L"moderate", true, true, false, true},
    {L"privacy.search-highlights", kPgPrivacy, L"Activity and search", L"No search highlights", L"Removes the daily pictures and trending topics from the search box.", L"", L"toggle", L"safe", true, true, false, true},
    {L"privacy.cloud-search", kPgPrivacy, L"Activity and search", L"Don't search your online accounts", L"Search stops including OneDrive, Outlook and other cloud content.", L"", L"toggle", L"safe", true, false, false, true},
    {L"privacy.typing-data", kPgPrivacy, L"Activity and search", L"Keep typing and handwriting private", L"Windows stops learning from what you type and write to build a personal dictionary.", L"", L"toggle", L"moderate", false, true, false, true},
    {L"privacy.app-tracking", kPgPrivacy, L"Activity and search", L"Don't track app launches", L"Windows stops counting which apps you open.", L"Start stops showing your most used apps.", L"toggle", L"moderate", false, false, false, true},
    {L"privacy.location", kPgPrivacy, L"Activity and search", L"Turn off location", L"No app or Windows feature can ask where this PC is.", L"Weather, maps and Find my device stop knowing where you are.", L"toggle", L"moderate", true, false, false, true},
    {L"privacy.clipboard-sync", kPgPrivacy, L"Activity and search", L"Keep the clipboard on this PC", L"What you copy is never synced to your other devices.", L"", L"toggle", L"moderate", true, false, false, true},
    {L"privacy.recall", kPgPrivacy, L"AI features", L"Turn off Recall", L"Windows never takes snapshots of your screen to search later.", L"", L"toggle", L"safe", true, true, true, true},
    {L"privacy.click-to-do", kPgPrivacy, L"AI features", L"Turn off Click to Do", L"Removes the AI actions that read what is on your screen.", L"", L"toggle", L"safe", true, true, false, true},
    {L"privacy.copilot", kPgPrivacy, L"AI features", L"Turn off Copilot in Windows", L"Hides Copilot from the taskbar and turns off the built-in Copilot.", L"", L"toggle", L"moderate", true, true, false, true},
    {L"performance.game-mode", kPgPerf, L"Gaming", L"Game Mode on", L"Windows gives the game you are playing first call on the processor and holds back updates.", L"", L"toggle", L"safe", false, true, false, true},
    {L"performance.background-recording", kPgPerf, L"Gaming", L"No background game recording", L"Stops Game Bar recording the last minutes of play in the background.", L"Game Bar's record button stops working too.", L"toggle", L"moderate", true, true, false, true},
    {L"performance.sticky-keys", kPgPerf, L"Gaming", L"No Sticky Keys pop-up", L"Pressing Shift five times in a game no longer throws up the Sticky Keys box.", L"", L"toggle", L"safe", false, true, false, true},
    {L"performance.mouse-acceleration", kPgPerf, L"Gaming", L"Turn off mouse acceleration", L"The pointer moves the same distance however fast you move the mouse. Applies after you sign in again.", L"", L"toggle", L"moderate", false, false, false, true},
    {L"performance.gpu-scheduling", kPgPerf, L"Gaming", L"Graphics card schedules its own work", L"Lets the graphics card manage its own memory queue, which can cut input delay.", L"", L"toggle", L"moderate", true, false, true, true},
    {L"performance.high-plan", kPgPerf, L"Power", L"High performance power plan", L"The processor stays at full speed instead of slowing down to save power.", L"Uses more power and runs a little warmer.", L"toggle", L"moderate", true, false, false, true},
    {L"performance.hibernate-off", kPgPerf, L"Power", L"Turn off hibernation", L"Deletes the hibernation file, which frees space about a third the size of your memory.", L"Fast startup and the Hibernate option go away too.", L"toggle", L"moderate", true, false, false, true},
    {L"performance.fast-startup-off", kPgPerf, L"Power", L"Turn off fast startup", L"Shut down fully restarts Windows, which clears stuck drivers and lets updates finish.", L"", L"toggle", L"safe", true, false, false, true},
    {L"performance.power-throttling-off", kPgPerf, L"Power", L"Turn off power throttling", L"Background apps keep full speed instead of being slowed down to save power.", L"Laptops run down their battery faster.", L"toggle", L"moderate", true, false, true, true},
    {L"performance.startup-delay", kPgPerf, L"Responsiveness", L"Start apps at sign-in without waiting", L"Apps set to start with Windows open at once instead of after a pause.", L"", L"toggle", L"safe", false, false, false, true},
    {L"performance.menu-delay", kPgPerf, L"Responsiveness", L"Faster menus", L"Sub-menus open after a tenth of a second instead of almost half a second.", L"", L"toggle", L"safe", false, false, false, true},
    {L"performance.global-timer", kPgPerf, L"Responsiveness", L"Shared high-precision timer", L"When a game asks for a finer timer, the whole PC gets it, as it did before Windows 10 2004.", L"Uses a little more power while a game runs.", L"toggle", L"advanced", true, false, true, true},
    {L"performance.sysmain-off", kPgPerf, L"Background services", L"Stop app preloading", L"Turns off the service that loads apps into memory before you open them. Helps on hard disks.", L"", L"toggle", L"moderate", true, false, false, true},
    {L"performance.search-index-off", kPgPerf, L"Background services", L"Stop the search index", L"Turns off the service that keeps an index of your files for search.", L"Start and File Explorer search get slow and stop looking inside files.", L"toggle", L"advanced", true, false, false, true},
    {L"performance.background-apps-off", kPgPerf, L"Background services", L"Stop Store apps running in the background", L"Store apps only run while their window is open.", L"Apps like Phone Link and Mail stop sending notifications.", L"toggle", L"advanced", true, false, false, true},
    {L"performance.print-spooler-off", kPgPerf, L"Background services", L"Stop the print service", L"Turns off printing support for PCs that never print.", L"Printing and Print to PDF stop working.", L"toggle", L"moderate", true, false, false, true},
    {L"apps.clipchamp", kPgApps, L"Extras", L"Clipchamp", L"Microsoft's online video editor.", L"Comes back only by installing it again from the Microsoft Store.", L"action", L"safe", true, true, false, false},
    {L"apps.news", kPgApps, L"Extras", L"Microsoft News", L"The news reader app.", L"Comes back only by installing it again from the Microsoft Store.", L"action", L"safe", true, true, false, false},
    {L"apps.weather", kPgApps, L"Extras", L"Weather", L"Microsoft's weather app.", L"Comes back only by installing it again from the Microsoft Store.", L"action", L"safe", true, false, false, false},
    {L"apps.solitaire", kPgApps, L"Extras", L"Solitaire Collection", L"Card games with ads.", L"Comes back only by installing it again from the Microsoft Store.", L"action", L"safe", true, true, false, false},
    {L"apps.tips", kPgApps, L"Extras", L"Tips", L"Tips on using Windows.", L"Comes back only by installing it again from the Microsoft Store.", L"action", L"safe", true, true, false, false},
    {L"apps.get-help", kPgApps, L"Extras", L"Get Help", L"Microsoft's support chat app.", L"Comes back only by installing it again from the Microsoft Store.", L"action", L"safe", true, true, false, false},
    {L"apps.feedback-hub", kPgApps, L"Extras", L"Feedback Hub", L"Sends feedback to Microsoft.", L"Comes back only by installing it again from the Microsoft Store.", L"action", L"safe", true, true, false, false},
    {L"apps.maps", kPgApps, L"Extras", L"Maps", L"Offline maps.", L"Comes back only by installing it again from the Microsoft Store.", L"action", L"safe", true, false, false, false},
    {L"apps.power-automate", kPgApps, L"Extras", L"Power Automate", L"Desktop automation for office work.", L"Comes back only by installing it again from the Microsoft Store.", L"action", L"safe", true, true, false, false},
    {L"apps.bing-search", kPgApps, L"Extras", L"Bing Search", L"The Bing search app.", L"Comes back only by installing it again from the Microsoft Store.", L"action", L"safe", true, true, false, false},
    {L"apps.dev-home", kPgApps, L"Extras", L"Dev Home", L"Microsoft's retired developer dashboard.", L"Comes back only by installing it again from the Microsoft Store.", L"action", L"safe", true, true, false, false},
    {L"apps.family", kPgApps, L"Extras", L"Microsoft Family", L"Parental controls app.", L"Comes back only by installing it again from the Microsoft Store.", L"action", L"safe", true, true, false, false},
    {L"apps.cortana", kPgApps, L"Extras", L"Cortana", L"Microsoft's retired voice assistant.", L"Comes back only by installing it again from the Microsoft Store.", L"action", L"safe", true, true, false, false},
    {L"apps.office-hub", kPgApps, L"Microsoft apps", L"Microsoft 365 Copilot", L"The hub that advertises Microsoft 365.", L"Comes back only by installing it again from the Microsoft Store.", L"action", L"safe", true, true, false, false},
    {L"apps.copilot", kPgApps, L"Microsoft apps", L"Copilot", L"Microsoft's AI chat app.", L"Comes back only by installing it again from the Microsoft Store.", L"action", L"moderate", true, false, false, false},
    {L"apps.outlook", kPgApps, L"Microsoft apps", L"Outlook (new)", L"The new Outlook mail app.", L"Comes back only by installing it again from the Microsoft Store.", L"action", L"moderate", true, false, false, false},
    {L"apps.mail-calendar", kPgApps, L"Microsoft apps", L"Mail and Calendar", L"The old mail app Microsoft retired.", L"Comes back only by installing it again from the Microsoft Store.", L"action", L"safe", true, true, false, false},
    {L"apps.teams", kPgApps, L"Microsoft apps", L"Microsoft Teams", L"The free Teams chat app.", L"Comes back only by installing it again from the Microsoft Store.", L"action", L"moderate", true, false, false, false},
    {L"apps.todo", kPgApps, L"Microsoft apps", L"Microsoft To Do", L"Lists and reminders.", L"Comes back only by installing it again from the Microsoft Store.", L"action", L"moderate", true, false, false, false},
    {L"apps.sticky-notes", kPgApps, L"Microsoft apps", L"Sticky Notes", L"Notes on the desktop.", L"Comes back only by installing it again from the Microsoft Store.", L"action", L"moderate", true, false, false, false},
    {L"apps.sound-recorder", kPgApps, L"Microsoft apps", L"Sound Recorder", L"Records audio.", L"Comes back only by installing it again from the Microsoft Store.", L"action", L"moderate", true, false, false, false},
    {L"apps.clock", kPgApps, L"Microsoft apps", L"Clock", L"Alarms, timers and focus sessions.", L"Comes back only by installing it again from the Microsoft Store.", L"action", L"moderate", true, false, false, false},
    {L"apps.movies-tv", kPgApps, L"Microsoft apps", L"Movies & TV", L"The old video player.", L"Comes back only by installing it again from the Microsoft Store.", L"action", L"safe", true, false, false, false},
    {L"apps.phone-link", kPgApps, L"Online services", L"Phone Link", L"Links an Android phone or iPhone to this PC.", L"Comes back only by installing it again from the Microsoft Store.", L"action", L"moderate", true, false, false, false},
    {L"apps.quick-assist", kPgApps, L"Online services", L"Quick Assist", L"Lets someone control this PC to help you.", L"Comes back only by installing it again from the Microsoft Store.", L"action", L"moderate", true, false, false, false},
    {L"apps.onedrive", kPgApps, L"Online services", L"OneDrive", L"Microsoft's cloud storage sync. Files already on this PC stay in your OneDrive folder.", L"Comes back only by installing it again from microsoft.com.", L"action", L"moderate", true, false, false, false},
    {L"updates.no-restart", kPgUpdates, L"Windows Update", L"Never restart while you are signed in", L"Updates wait for you to restart, so a game or a stream is never cut off.", L"", L"toggle", L"safe", true, true, false, true},
    {L"updates.no-drivers", kPgUpdates, L"Windows Update", L"No drivers from Windows Update", L"Windows Update stops replacing your drivers, so the graphics driver you chose stays put.", L"", L"toggle", L"safe", true, true, false, true},
    {L"updates.notify-download", kPgUpdates, L"Windows Update", L"Ask before downloading updates", L"Windows tells you when updates are ready and waits for you to start them.", L"Security fixes wait until you install them.", L"toggle", L"moderate", true, false, false, true},
    {L"updates.defer-features", kPgUpdates, L"Windows Update", L"Hold big updates for a year", L"The yearly Windows version update arrives a year after release, once it has settled.", L"Insider builds ignore this.", L"toggle", L"moderate", true, false, false, true},
    {L"updates.defer-quality", kPgUpdates, L"Windows Update", L"Hold monthly updates for a week", L"Monthly updates install a week late, after early problems are found.", L"", L"toggle", L"moderate", true, false, false, true},
    {L"updates.no-msrt", kPgUpdates, L"Windows Update", L"Skip the monthly removal tool", L"Windows Update stops downloading the Malicious Software Removal Tool each month.", L"", L"toggle", L"moderate", true, false, false, true},
    {L"updates.no-sharing", kPgUpdates, L"Downloads", L"Don't share updates over the internet", L"Updates download only from Microsoft and are never uploaded to other people's PCs.", L"", L"toggle", L"safe", true, true, false, true},
    {L"updates.store-auto-off", kPgUpdates, L"Downloads", L"Store apps update only when you ask", L"The Microsoft Store stops updating apps by itself.", L"Store apps fall behind until you update them.", L"toggle", L"moderate", true, false, false, true},
    {L"updates.reserved-storage-off", kPgUpdates, L"Downloads", L"Give back the space kept for updates", L"Frees the space, about 7 GB, that Windows keeps aside for installing updates.", L"A big update may then ask you to free space first.", L"toggle", L"moderate", true, false, false, true},
    {L"windows.file-extensions", kPgWindows, L"File Explorer", L"Show file extensions", L"File names show their type, like .exe or .pdf, so a fake document is easy to spot.", L"", L"toggle", L"safe", false, true, false, true},
    {L"windows.hidden-files", kPgWindows, L"File Explorer", L"Show hidden files", L"File Explorer shows files and folders marked hidden.", L"", L"toggle", L"safe", false, false, false, true},
    {L"windows.open-this-pc", kPgWindows, L"File Explorer", L"Open File Explorer on This PC", L"File Explorer opens on your drives instead of Home.", L"", L"toggle", L"safe", false, false, false, true},
    {L"windows.no-recent", kPgWindows, L"File Explorer", L"Don't list recent files in Home", L"Home stops showing the files and folders you opened lately.", L"", L"toggle", L"moderate", false, false, false, true},
    {L"windows.classic-menu", kPgWindows, L"File Explorer", L"Classic right-click menu", L"Right-click shows the full old menu straight away. Applies after you sign in again.", L"Menu mods that style the new menu don't style this one.", L"toggle", L"moderate", false, false, false, true},
    {L"windows.widgets-off", kPgWindows, L"Taskbar and Start", L"Turn off Widgets", L"Removes the news and weather board and stops it running in the background.", L"", L"toggle", L"safe", true, true, false, true},
    {L"windows.end-task", kPgWindows, L"Taskbar and Start", L"End task on the taskbar", L"Adds End task to a taskbar button's right-click menu, to close a stuck app.", L"", L"toggle", L"safe", false, false, false, true},
    {L"windows.search-box-off", kPgWindows, L"Taskbar and Start", L"Hide the taskbar search box", L"Removes the search box from the taskbar. Start search still works.", L"", L"toggle", L"safe", false, false, false, true},
    {L"windows.task-view-off", kPgWindows, L"Taskbar and Start", L"Hide the Task View button", L"Removes the Task View button. Win+Tab still opens it.", L"", L"toggle", L"safe", false, false, false, true},
    {L"windows.spotlight-icon-off", kPgWindows, L"Taskbar and Start", L"Hide the Learn about this picture icon", L"Removes the Spotlight icon from the desktop.", L"", L"toggle", L"safe", false, false, false, true},
    {L"windows.long-paths", kPgWindows, L"System", L"Allow long file paths", L"Apps that support it can use paths longer than 260 characters, which deep project folders need.", L"", L"toggle", L"safe", true, true, false, true},
    {L"windows.verbose-status", kPgWindows, L"System", L"Say what Windows is doing at start and shut down", L"Start-up and shut-down screens name the step they are on, so a hang is easy to spot.", L"", L"toggle", L"safe", true, false, false, true},
    {L"windows.crash-details", kPgWindows, L"System", L"Show details on the crash screen", L"The blue crash screen shows the error codes, not just a sad face.", L"", L"toggle", L"safe", true, false, false, true},
    {L"repair.restore-point", kPgRepair, L"Safety", L"Make a restore point", L"Saves a point you can roll Windows back to if something goes wrong.", L"", L"action", L"safe", true, false, false, false},
    {L"repair.sfc", kPgRepair, L"Repair Windows", L"Check and fix system files", L"Finds damaged Windows files and puts good copies back. Takes about ten minutes.", L"", L"action", L"safe", true, false, false, false},
    {L"repair.dism-scan", kPgRepair, L"Repair Windows", L"Check the Windows repair store", L"Checks the store Windows repairs itself from. Takes a few minutes.", L"", L"action", L"safe", true, false, false, false},
    {L"repair.dism-repair", kPgRepair, L"Repair Windows", L"Repair the Windows repair store", L"Downloads good copies of damaged parts from Windows Update. Run it before checking system files again.", L"Needs the internet and can take twenty minutes.", L"action", L"safe", true, false, false, false},
    {L"repair.component-cleanup", kPgRepair, L"Repair Windows", L"Shrink the store of old Windows parts", L"Removes old copies of Windows parts that updates replaced. Takes a few minutes.", L"", L"action", L"safe", true, false, false, false},
    {L"repair.update-reset", kPgRepair, L"Repair Windows", L"Fix stuck Windows updates", L"Stops the update services, sets the download folders aside and starts them fresh.", L"The update history list starts empty.", L"action", L"moderate", true, false, false, false},
    {L"repair.disk-scan", kPgRepair, L"Drives", L"Check the C: drive for errors", L"Scans the drive while you keep working and says if it found problems.", L"", L"action", L"safe", true, false, false, false},
    {L"repair.flush-dns", kPgRepair, L"Network", L"Clear the saved website addresses", L"Fixes sites that moved and still won't load.", L"", L"action", L"safe", false, false, false, false},
    {L"repair.time-sync", kPgRepair, L"Network", L"Set the clock from the internet", L"Syncs the clock with the Windows time servers, which fixes sign-in and certificate errors.", L"", L"action", L"safe", true, false, false, false},
    {L"repair.icon-cache", kPgRepair, L"Desktop", L"Refresh icons", L"Redraws icons that show blank or the wrong picture.", L"", L"action", L"safe", false, false, false, false},
};

// What the window knows about one field beyond SetField: its catalog row, the last scan, and
// the strings the field points at (a deque keeps them in place as rows are added).
struct OptMeta {
    const OptItem* item = nullptr;
    bool known = false, avail = false;
    double bytes = 0;
    long long files = 0;
    std::wstring key, label, desc, base, scope, name;
};

struct OptJob {
    std::wstring tag, args;
    bool longRun = false;
};

struct OptOut {
    std::wstring tag;
    std::vector<Js> lines;
    DWORD code = 0;
    bool ran = false;
    std::wstring err;
};

struct OptFeed {
    std::wstring tag, msg;
    long long done = 0, total = 0;
};

static struct {
    std::deque<OptMeta> meta;
    std::map<std::wstring, int> byId;
    size_t baseCount = 0;  // Fields before the "Starts with Windows" list.
    bool ready = false, engineFailed = false, restart = false;
    std::wstring engineErr;
    std::deque<std::wstring> tags;  // Jobs sent to the worker, oldest first.
    std::set<std::wstring> loaded;  // Read jobs that ran (or are queued) at least once.
    std::wstring progMsg;
    long long progDone = 0, progTotal = 0;
    bool feedTimer = false;
    std::wstring armUrl;
    ULONGLONG armAt = 0;
    bool infoOk = false, infoFailed = false;
    Js info;
    bool programsOk = false, updatesOk = false, spaceOk = false, startupOk = false;
    std::vector<Js> programs, updates, space;
    bool trayOn = false, noTray = false, quitting = false;
    UINT taskbarCreated = 0;
} g_opt;

static struct {
    std::mutex m;
    std::condition_variable cv;
    std::deque<OptJob> jobs;
    bool stop = false;
    std::atomic<bool> halt{false};
    HANDLE thread = nullptr;
    HANDLE engine = INVALID_HANDLE_VALUE;  // Held open with no write sharing, so the file cannot change.
    std::wstring exe, dir;
    std::atomic<bool> ready{false};
} g_work;

static HANDLE g_modThread, g_modReady, g_modMutex, g_falseFailureThread;
static DWORD g_modThreadId;
static std::atomic<bool> g_modStartupOk{false};
static std::atomic<bool> g_closeFalseFailure{true};

static void Hub_TrayUpdate(SetWindow& w);

// ---- Small helpers ---------------------------------------------------------------------

static bool Opt_Starts(const std::wstring& s, PCWSTR prefix) { return s.rfind(prefix, 0) == 0; }

static std::wstring Opt_Str(const Js& row, PCWSTR key) { return Js_Text(row.get(key)); }

static double Opt_Num(const Js& row, PCWSTR key) {
    const std::wstring s = Js_Text(row.get(key));
    return s.empty() ? 0 : _wtof(s.c_str());
}

static bool Opt_Bool(const Js& row, PCWSTR key) {
    const Js* v = row.get(key);
    return v && ((v->t == Js::Bool && v->b) || (v->t == Js::Num && _wtof(v->s.c_str()) != 0));
}

static std::wstring Opt_Size(double b) {
    static const PCWSTR kUnits[] = {L"bytes", L"KB", L"MB", L"GB", L"TB"};
    int u = 0;
    while (b >= 1024 && u < 4) b /= 1024, u++;
    WCHAR buf[48];
    if (u == 0) swprintf_s(buf, L"%.0f bytes", b);
    else swprintf_s(buf, b < 10 ? L"%.1f %s" : L"%.0f %s", b, kUnits[u]);
    return buf;
}

static std::wstring Opt_Count(long long n) {
    std::wstring s = std::to_wstring(n < 0 ? 0 : n);
    for (int i = (int)s.size() - 3; i > 0; i -= 3) s.insert((size_t)i, L",");
    return s;
}

static std::wstring Opt_Files(long long n) { return Opt_Count(n) + (n == 1 ? L" file" : L" files"); }

static std::wstring Opt_Uptime(double seconds) {
    const long long m = (long long)(seconds / 60), h = m / 60, d = h / 24;
    auto unit = [](long long v, PCWSTR one, PCWSTR many) { return std::to_wstring(v) + L" " + (v == 1 ? one : many); };
    if (d > 0) return unit(d, L"day", L"days") + L", " + unit(h % 24, L"hour", L"hours");
    if (h > 0) return unit(h, L"hour", L"hours") + L", " + unit(m % 60, L"minute", L"minutes");
    return unit(m, L"minute", L"minutes");
}

static std::wstring Opt_Cut(const std::wstring& s, size_t n) {
    return s.size() <= n ? s : s.substr(0, n - 1) + L"\u2026";
}

static PCWSTR Opt_PageName(int page) {
    switch (page) {
        case kPgClean: return L"clean";
        case kPgPrivacy: return L"privacy";
        case kPgPerf: return L"performance";
        case kPgApps: return L"apps";
        case kPgUpdates: return L"updates";
        case kPgWindows: return L"windows";
        case kPgRepair: return L"repair";
    }
    return L"";
}

static const OptItem* Opt_Item(const std::wstring& id) {
    for (const OptItem& it : kOptItems)
        if (id == it.id) return &it;
    return nullptr;
}

static OptMeta* Opt_MetaOf(const SetWindow& w, const SetField& f) {
    const size_t k = (size_t)(&f - w.fields.data());
    return k < g_opt.meta.size() && k < w.fields.size() ? &g_opt.meta[k] : nullptr;
}

static bool Opt_IsClean(const OptMeta* m) { return m && m->item && wcscmp(m->item->kind, L"clean") == 0; }

static bool Opt_IsApp(const OptMeta* m) { return m && m->item && m->item->page == kPgApps && wcscmp(m->item->kind, L"toggle") != 0; }

static bool Opt_RestoreOn(const SetWindow& w) { return Set_FieldOn(w, L"restorePoint", true); }

static std::wstring Opt_Join(const std::vector<std::wstring>& ids) {
    std::wstring out;
    for (auto& id : ids) out += (out.empty() ? L"" : L",") + id;
    return out;
}

// ---- The helper program ----------------------------------------------------------------

static bool Opt_HashFile(HANDLE file, std::wstring& hex) {
    BCRYPT_ALG_HANDLE alg = nullptr;
    BCRYPT_HASH_HANDLE hash = nullptr;
    if (!NT_SUCCESS(BCryptOpenAlgorithmProvider(&alg, BCRYPT_SHA256_ALGORITHM, nullptr, 0))) return false;
    bool ok = NT_SUCCESS(BCryptCreateHash(alg, &hash, nullptr, 0, nullptr, 0, 0));
    LARGE_INTEGER zero{};
    ok = ok && SetFilePointerEx(file, zero, nullptr, FILE_BEGIN);
    std::vector<BYTE> buf(1 << 16);
    DWORD got = 0, total = 0;
    while (ok && ReadFile(file, buf.data(), (DWORD)buf.size(), &got, nullptr) && got) {
        total += got;
        if (total > kOptEngineMax) ok = false;
        else ok = NT_SUCCESS(BCryptHashData(hash, buf.data(), got, 0));
    }
    BYTE digest[32]{};
    ok = ok && total > 0 && NT_SUCCESS(BCryptFinishHash(hash, digest, sizeof(digest), 0));
    if (hash) BCryptDestroyHash(hash);
    BCryptCloseAlgorithmProvider(alg, 0);
    if (!ok) return false;
    hex.clear();
    for (BYTE b : digest) {
        WCHAR two[3];
        swprintf_s(two, L"%02x", b);
        hex += two;
    }
    return true;
}

// Opens swo.exe and keeps it open when its fingerprint matches the one this mod was built with.
static bool Opt_OpenEngine() {
    HANDLE h = CreateFileW(g_work.exe.c_str(), GENERIC_READ, FILE_SHARE_READ, nullptr, OPEN_EXISTING,
                           FILE_ATTRIBUTE_NORMAL, nullptr);
    if (h == INVALID_HANDLE_VALUE) return false;
    std::wstring hex;
    if (Opt_HashFile(h, hex) && _wcsicmp(hex.c_str(), kOptEngineSha) == 0) {
        g_work.engine = h;
        return true;
    }
    CloseHandle(h);
    return false;
}

static bool Opt_Download(const std::wstring& to, std::wstring& err) {
    URL_COMPONENTS uc{sizeof(uc)};
    WCHAR host[256]{}, path[2048]{};
    uc.lpszHostName = host;
    uc.dwHostNameLength = 256;
    uc.lpszUrlPath = path;
    uc.dwUrlPathLength = 2048;
    if (!WinHttpCrackUrl(kOptEngineUrl, 0, 0, &uc)) {
        err = L"its web address is wrong";
        return false;
    }
    HINTERNET s = WinHttpOpen(L"SeamlessWindowsOptimizer/1.0", WINHTTP_ACCESS_TYPE_AUTOMATIC_PROXY,
                              WINHTTP_NO_PROXY_NAME, WINHTTP_NO_PROXY_BYPASS, 0);
    HINTERNET c = s ? WinHttpConnect(s, host, uc.nPort, 0) : nullptr;
    HINTERNET r = c ? WinHttpOpenRequest(c, L"GET", path, nullptr, WINHTTP_NO_REFERER, WINHTTP_DEFAULT_ACCEPT_TYPES,
                                         WINHTTP_FLAG_SECURE)
                    : nullptr;
    bool ok = false;
    if (r) {
        WinHttpSetTimeouts(s, 10000, 10000, 15000, 30000);
        DWORD status = 0, size = sizeof(status);
        if (WinHttpSendRequest(r, WINHTTP_NO_ADDITIONAL_HEADERS, 0, WINHTTP_NO_REQUEST_DATA, 0, 0, 0) &&
            WinHttpReceiveResponse(r, nullptr) &&
            WinHttpQueryHeaders(r, WINHTTP_QUERY_STATUS_CODE | WINHTTP_QUERY_FLAG_NUMBER, WINHTTP_HEADER_NAME_BY_INDEX,
                                &status, &size, WINHTTP_NO_HEADER_INDEX) &&
            status == 200) {
            HANDLE f = CreateFileW(to.c_str(), GENERIC_WRITE, 0, nullptr, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, nullptr);
            if (f != INVALID_HANDLE_VALUE) {
                std::vector<char> buf(1 << 16);
                DWORD total = 0;
                ok = true;
                for (;;) {
                    DWORD avail = 0, got = 0, wrote = 0;
                    if (g_work.halt) { ok = false; err = L"stopped"; break; }
                    if (!WinHttpQueryDataAvailable(r, &avail)) { ok = false; break; }
                    if (!avail) break;
                    if (!WinHttpReadData(r, buf.data(), std::min<DWORD>(avail, (DWORD)buf.size()), &got) || !got) {
                        ok = false;
                        break;
                    }
                    total += got;
                    if (total > kOptEngineMax || !WriteFile(f, buf.data(), got, &wrote, nullptr) || wrote != got) {
                        ok = false;
                        break;
                    }
                }
                CloseHandle(f);
                if (!ok) DeleteFileW(to.c_str());
                if (!ok && err.empty()) err = L"the download broke off";
            } else {
                err = L"it could not be saved";
            }
        } else {
            err = status ? L"GitHub answered " + std::to_wstring(status) : L"no internet connection";
        }
    } else {
        err = L"no internet connection";
    }
    if (r) WinHttpCloseHandle(r);
    if (c) WinHttpCloseHandle(c);
    if (s) WinHttpCloseHandle(s);
    return ok;
}

// Finds swo.exe in its Program Files folder (only admins can change it there), and fetches it
// once from the project's release when it is missing or not the build this mod expects.
static bool Opt_FetchEngine(std::wstring& err) {
    if (g_work.engine != INVALID_HANDLE_VALUE) return true;
    PWSTR pf = nullptr;
    if (FAILED(SHGetKnownFolderPath(FOLDERID_ProgramFiles, 0, nullptr, &pf))) {
        err = L"Program Files was not found";
        return false;
    }
    g_work.dir = std::wstring(pf) + L"\\Seamless Windows Optimizer";
    CoTaskMemFree(pf);
    g_work.exe = g_work.dir + L"\\swo.exe";
    if (Opt_OpenEngine()) return true;
    CreateDirectoryW(g_work.dir.c_str(), nullptr);
    const std::wstring part = g_work.exe + L".part";
    if (!Opt_Download(part, err)) return false;
    HANDLE h = CreateFileW(part.c_str(), GENERIC_READ, FILE_SHARE_READ, nullptr, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, nullptr);
    std::wstring hex;
    const bool match = h != INVALID_HANDLE_VALUE && Opt_HashFile(h, hex) && _wcsicmp(hex.c_str(), kOptEngineSha) == 0;
    if (h != INVALID_HANDLE_VALUE) CloseHandle(h);
    if (!match) {
        DeleteFileW(part.c_str());
        err = L"the download did not match its fingerprint";
        return false;
    }
    if (!MoveFileExW(part.c_str(), g_work.exe.c_str(), MOVEFILE_REPLACE_EXISTING | MOVEFILE_WRITE_THROUGH)) {
        DeleteFileW(part.c_str());
        err = L"it could not be saved";
        return false;
    }
    if (!Opt_OpenEngine()) {
        err = L"it changed after it was saved";
        return false;
    }
    return true;
}

static void Opt_Post(UINT msg, void* payload) {
    HWND hwnd = g_settingsWnd;
    if (!hwnd || !PostMessageW(hwnd, msg, 0, (LPARAM)payload)) {
        if (msg == WM_HUB_RESULT) delete (OptOut*)payload;
        else delete (OptFeed*)payload;
    }
}

static void Opt_Line(const std::wstring& tag, const std::string& raw, OptOut& out) {
    std::string line = raw;
    while (!line.empty() && (line.back() == '\r' || line.back() == '\n')) line.pop_back();
    if (line.empty()) return;
    Js v;
    if (!Js_Parse(Hub_Wide(line), v) || v.t != Js::Obj) return;
    const std::wstring t = Opt_Str(v, L"t");
    if (t == L"progress") {
        auto feed = new OptFeed;
        feed->tag = tag;
        feed->msg = Opt_Str(v, L"msg");
        feed->done = (long long)Opt_Num(v, L"done");
        feed->total = (long long)Opt_Num(v, L"total");
        Opt_Post(WM_HUB_FEED, feed);
        return;
    }
    if (t == L"log") return;
    out.lines.push_back(std::move(v));
}

// Runs swo.exe hidden with one command and reads its JSON lines until it ends.
static void Opt_RunEngine(const OptJob& job, OptOut& out) {
    SECURITY_ATTRIBUTES sa{sizeof(sa), nullptr, TRUE};
    HANDLE rd = nullptr, wr = nullptr;
    if (!CreatePipe(&rd, &wr, &sa, 0)) {
        out.err = L"could not start the helper program";
        return;
    }
    SetHandleInformation(rd, HANDLE_FLAG_INHERIT, 0);
    HANDLE nul = CreateFileW(L"NUL", GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, &sa, OPEN_EXISTING, 0, nullptr);
    SIZE_T size = 0;
    InitializeProcThreadAttributeList(nullptr, 1, 0, &size);
    std::vector<BYTE> attr(size);
    auto list = (LPPROC_THREAD_ATTRIBUTE_LIST)attr.data();
    HANDLE inherit[2] = {wr, nul};
    bool ok = nul != INVALID_HANDLE_VALUE && InitializeProcThreadAttributeList(list, 1, 0, &size) &&
              UpdateProcThreadAttribute(list, 0, PROC_THREAD_ATTRIBUTE_HANDLE_LIST, inherit, sizeof(inherit), nullptr, nullptr);
    PROCESS_INFORMATION pi{};
    if (ok) {
        STARTUPINFOEXW si{};
        si.StartupInfo.cb = sizeof(si);
        si.StartupInfo.dwFlags = STARTF_USESTDHANDLES | STARTF_USESHOWWINDOW;
        si.StartupInfo.wShowWindow = SW_HIDE;
        si.StartupInfo.hStdInput = nul;
        si.StartupInfo.hStdOutput = wr;
        si.StartupInfo.hStdError = nul;
        si.lpAttributeList = list;
        std::wstring cmd = Set_QuoteArg(g_work.exe) + L" " + job.args;
        ok = CreateProcessW(g_work.exe.c_str(), cmd.data(), nullptr, nullptr, TRUE,
                            CREATE_NO_WINDOW | EXTENDED_STARTUPINFO_PRESENT | BELOW_NORMAL_PRIORITY_CLASS, nullptr,
                            g_work.dir.c_str(), &si.StartupInfo, &pi);
        DeleteProcThreadAttributeList(list);
    }
    CloseHandle(wr);
    if (nul != INVALID_HANDLE_VALUE) CloseHandle(nul);
    if (!ok) {
        CloseHandle(rd);
        out.err = L"could not start the helper program";
        return;
    }
    CloseHandle(pi.hThread);
    const ULONGLONG deadline = GetTickCount64() + (job.longRun ? 3ull * 60 * 60 * 1000 : 30ull * 60 * 1000);
    std::string data;
    size_t seen = 0;
    char chunk[8192];
    auto take = [&](DWORD got) {
        data.append(chunk, got);
        size_t nl;
        while ((nl = data.find('\n', seen)) != std::string::npos) {
            Opt_Line(job.tag, data.substr(seen, nl - seen), out);
            seen = nl + 1;
        }
        if (seen > 65536) data.erase(0, seen), seen = 0;
    };
    size_t total = 0;
    bool killed = false;
    for (;;) {
        DWORD avail = 0, got = 0;
        if (PeekNamedPipe(rd, nullptr, 0, nullptr, &avail, nullptr) && avail) {
            if (ReadFile(rd, chunk, std::min<DWORD>(avail, sizeof(chunk)), &got, nullptr) && got) {
                total += got;
                take(got);
                if (total > kOptOutputMax) {
                    TerminateProcess(pi.hProcess, 1);
                    out.err = L"the helper program wrote too much";
                    killed = true;
                    break;
                }
                continue;
            }
        }
        if (WaitForSingleObject(pi.hProcess, 0) == WAIT_OBJECT_0) {
            while (total <= kOptOutputMax && PeekNamedPipe(rd, nullptr, 0, nullptr, &avail, nullptr) && avail) {
                if (!ReadFile(rd, chunk, std::min<DWORD>(avail, sizeof(chunk)), &got, nullptr) || !got) break;
                total += got;
                take(got);
            }
            if (total > kOptOutputMax) {
                out.err = L"the helper program wrote too much";
                killed = true;
            }
            break;
        }
        if (g_work.halt || GetTickCount64() > deadline) {
            TerminateProcess(pi.hProcess, 1);
            out.err = g_work.halt ? L"stopped" : L"it took too long";
            killed = true;
            break;
        }
        WaitForSingleObject(pi.hProcess, 50);
    }
    if (seen < data.size()) Opt_Line(job.tag, data.substr(seen), out);
    WaitForSingleObject(pi.hProcess, 5000);
    GetExitCodeProcess(pi.hProcess, &out.code);
    CloseHandle(pi.hProcess);
    CloseHandle(rd);
    out.ran = !killed;
}

static DWORD WINAPI Opt_Worker(void*) {
    CoInitializeEx(nullptr, COINIT_MULTITHREADED);
    for (;;) {
        OptJob job;
        {
            std::unique_lock<std::mutex> lock(g_work.m);
            g_work.cv.wait(lock, [] { return g_work.stop || !g_work.jobs.empty(); });
            if (g_work.stop) break;
            job = std::move(g_work.jobs.front());
            g_work.jobs.pop_front();
        }
        auto out = new OptOut;
        out->tag = job.tag;
        if (job.tag == L"engine") {
            out->ran = Opt_FetchEngine(out->err);
            g_work.ready = out->ran;
        } else if (!g_work.ready) {
            out->err = L"the helper program is not ready";
        } else {
            Opt_RunEngine(job, *out);
        }
        Opt_Post(WM_HUB_RESULT, out);
    }
    CoUninitialize();
    return 0;
}

// ---- The job queue (window thread) -------------------------------------------------------

static bool Opt_IsRead(const std::wstring& tag) {
    return tag == L"info" || tag == L"startup" || tag == L"programs" || tag == L"updates" || tag == L"space" ||
           Opt_Starts(tag, L"scan:");
}

// Queues one helper run. A read that is already waiting behind every change is not queued twice.
static bool Opt_Queue(const std::wstring& tag, const std::wstring& args, bool longRun = false) {
    if (!g_work.thread) {
        if (g_setWin) Set_SetStatus(*g_setWin, L"Could not start the helper worker", true);
        return false;
    }
    if (tag != L"engine" && !g_opt.ready) return false;
    if (Opt_IsRead(tag)) {
        for (auto it = g_opt.tags.rbegin(); it != g_opt.tags.rend(); ++it) {
            if (*it == tag) return true;
            if (!Opt_IsRead(*it)) break;
        }
    }
    g_opt.tags.push_back(tag);
    {
        std::lock_guard<std::mutex> lock(g_work.m);
        g_work.jobs.push_back({tag, args, longRun});
    }
    g_work.cv.notify_one();
    return true;
}

static bool Opt_Pending(PCWSTR tag) { return std::find(g_opt.tags.begin(), g_opt.tags.end(), tag) != g_opt.tags.end(); }

static void Opt_Read(const std::wstring& tag) {
    std::wstring args;
    if (tag == L"info") args = L"tool info";
    else if (tag == L"startup") args = L"tool startup list";
    else if (tag == L"programs") args = L"tool programs list";
    else if (tag == L"updates") args = L"tool updates list";
    else if (Opt_Starts(tag, L"scan:")) args = L"scan --page " + Set_QuoteArg(tag.substr(5));
    else if (tag == L"space") {
        WCHAR drive[8] = L"C:";
        GetEnvironmentVariableW(L"SystemDrive", drive, 8);
        args = L"tool space " + Set_QuoteArg(std::wstring(drive) + L"\\");
    }
    if (args.empty()) return;
    if (Opt_Queue(tag, args, tag == L"space")) g_opt.loaded.insert(tag);
}

static void Opt_Need(PCWSTR tag) {
    if (!g_opt.loaded.count(tag)) Opt_Read(tag);
}

// Loads what the open page shows, the first time it opens.
static void Opt_LoadPage(SetWindow& w) {
    if (!g_opt.ready || !w.hwnd || !IsWindowVisible(w.hwnd)) return;
    switch (w.page) {
        case kPgOverview: Opt_Need(L"info"); break;
        case kPgClean: Opt_Need(L"scan:clean"); break;
        case kPgPrivacy: Opt_Need(L"scan:privacy"); break;
        case kPgPerf: Opt_Need(L"scan:performance"); Opt_Need(L"startup"); break;
        case kPgApps: Opt_Need(L"scan:apps"); Opt_Need(L"programs"); break;
        case kPgUpdates: Opt_Need(L"scan:updates"); Opt_Need(L"updates"); break;
        case kPgWindows: Opt_Need(L"scan:windows"); break;
    }
}

static std::wstring Opt_TagText(const std::wstring& tag) {
    if (tag == L"engine") return L"Getting the helper program ready. This happens once.";
    if (tag == L"info") return L"Reading your PC";
    if (tag == L"scan:clean") return L"Looking for files to clean";
    if (Opt_Starts(tag, L"scan:")) return L"Reading your settings";
    if (tag == L"startup") return L"Reading what starts with Windows";
    if (tag == L"programs") return L"Reading installed programs";
    if (tag == L"updates") return L"Asking Windows Update what is waiting";
    if (tag == L"space") return L"Measuring what fills the drive. This can take a few minutes.";
    if (tag == L"apply:clean") return L"Cleaning";
    if (tag == L"apply:apps") return L"Removing apps";
    if (tag == L"apply:tweaks") return L"Applying changes";
    if (tag == L"revert:tweaks") return L"Undoing changes";
    if (Opt_Starts(tag, L"run:")) {
        const OptItem* it = Opt_Item(tag.substr(4));
        return std::wstring(L"Running ") + (it ? it->name : L"the repair");
    }
    if (tag == L"startup-set") return L"Changing what starts with Windows";
    if (Opt_Starts(tag, L"uninstall:")) return L"Uninstalling";
    if (tag == L"hide") return L"Updating the list";
    return L"Working";
}

static std::wstring Opt_Busy() {
    if (g_opt.tags.empty()) return {};
    std::wstring text = Opt_TagText(g_opt.tags.front());
    if (!g_opt.progMsg.empty()) {
        text = g_opt.progMsg;
        if (g_opt.progTotal == 100) text += L" (" + std::to_wstring(std::clamp(g_opt.progDone, 0ll, 100ll)) + L"%)";
        else if (g_opt.progTotal > 1)
            text += L" (" + std::to_wstring(std::min(g_opt.progDone + 1, g_opt.progTotal)) + L" of " +
                    std::to_wstring(g_opt.progTotal) + L")";
    }
    if (text.back() != L'.') text += L"\u2026";
    return text;
}

// ---- Arming: a click that deletes or removes asks for a second click -------------------

static void Opt_Disarm(SetWindow& w) {
    g_opt.armUrl.clear();
    if (w.hwnd) KillTimer(w.hwnd, kHubArmTimer);
}

static bool Opt_Armed(SetWindow& w, const std::wstring& url) {
    if (g_opt.armUrl == url && GetTickCount64() - g_opt.armAt < kOptArmMs) {
        Opt_Disarm(w);
        return true;
    }
    g_opt.armUrl = url;
    g_opt.armAt = GetTickCount64();
    SetTimer(w.hwnd, kHubArmTimer, (UINT)kOptArmMs + 50, nullptr);
    Set_BuildAndClamp(w);
    return false;
}

static bool Opt_IsArmed(const std::wstring& url) { return !g_opt.armUrl.empty() && g_opt.armUrl == url; }

// ---- Fields --------------------------------------------------------------------------

static void Opt_SetDesc(SetWindow& w, size_t k) {
    OptMeta& m = g_opt.meta[k];
    if (Opt_IsClean(&m) && m.known) {
        m.desc = (m.bytes > 0 || m.files > 0) ? L"Found " + Opt_Size(m.bytes) + L" in " + Opt_Files(m.files) + L". " + m.base
                                              : L"Nothing to clean right now. " + m.base;
    } else {
        m.desc = m.base;
    }
    w.fields[k].desc = m.desc.c_str();
}

static void Hub_InitFields(SetWindow& w) {
    g_opt.meta.clear();
    g_opt.byId.clear();
    g_opt.meta.resize(w.fields.size());
    for (const OptItem& it : kOptItems) {
        if (it.page == kPgRepair) continue;
        OptMeta& m = g_opt.meta.emplace_back();
        m.item = &it;
        m.base = it.desc;
        if (it.reboot) m.base += L" Needs a restart.";
        if (*it.warn) m.base += std::wstring(L" ") + it.warn;
        else if (wcscmp(it.risk, L"advanced") == 0) m.base += L" Change it only if you know you need it.";
        m.desc = m.base;
        SetField f;
        f.kind = SetField::Check;
        f.key = it.id;
        f.label = it.name;
        f.desc = m.desc.c_str();
        f.page = it.page;
        f.group = it.group;
        f.def = it.pick ? L"1" : L"0";
        const bool toggle = wcscmp(it.kind, L"toggle") == 0;
        f.hub = toggle ? 8 : 5;
        f.value = f.cur = toggle || !Opt_IsClean(&m) ? L"0" : f.def;
        g_opt.byId[it.id] = (int)w.fields.size();
        w.fields.push_back(f);
    }
    g_opt.baseCount = w.fields.size();
}

// Replaces the "Starts with Windows" switches with a fresh list, keeping unsaved flips.
static void Opt_SetStartup(SetWindow& w, const std::vector<Js>& rows) {
    std::map<std::wstring, std::wstring> pending;
    for (size_t k = g_opt.baseCount; k < w.fields.size(); k++)
        if (w.fields[k].cur != w.fields[k].value) pending[w.fields[k].key] = w.fields[k].cur;
    w.fields.resize(g_opt.baseCount);
    g_opt.meta.resize(g_opt.baseCount);
    for (const Js& row : rows) {
        const std::wstring name = Opt_Str(row, L"name"), scope = Opt_Str(row, L"scope");
        if (name.empty() || scope.empty()) continue;
        OptMeta& m = g_opt.meta.emplace_back();
        m.scope = scope;
        m.name = name;
        m.key = L"startup:" + scope + L":" + name;
        m.label = name;
        std::wstring cmd = Opt_Cut(Opt_Str(row, L"command"), 120);
        m.base = cmd.empty() ? L"Starts when you sign in." : cmd;
        if (Opt_Bool(row, L"missing")) m.base += L" The program it starts is gone, so this entry does nothing.";
        m.desc = m.base;
        SetField f;
        f.kind = SetField::Check;
        f.key = m.key.c_str();
        f.label = m.label.c_str();
        f.desc = m.desc.c_str();
        f.page = kPgPerf;
        f.group = L"Starts with Windows";
        f.hub = 9;
        f.value = Opt_Bool(row, L"enabled") ? L"1" : L"0";
        f.def = f.value == L"1" ? L"1" : L"0";
        auto p = pending.find(m.key);
        f.cur = p != pending.end() ? p->second : f.value;
        w.fields.push_back(f);
    }
    w.hover = SetHit{};
    if (w.focus >= (int)g_opt.baseCount) w.focus = -1;
    for (auto it = w.knob.begin(); it != w.knob.end();)
        it = it->first >= (int)g_opt.baseCount ? w.knob.erase(it) : std::next(it);
}

// ---- Page items ---------------------------------------------------------------------

static bool Opt_HasGroup(const SetWindow& w) {
    for (auto& it : w.items)
        if (it.type == SetItem::Group) return true;
    return false;
}

static void Opt_AddGroup(SetWindow& w, float& y, const std::wstring& text) {
    SetItem g;
    g.type = SetItem::Group;
    g.text = text;
    y += Opt_HasGroup(w) ? 14 : 0;
    g.y = y;
    g.h = 22;
    y += g.h + 6;
    w.items.push_back(g);
}

static void Opt_AddLink(SetWindow& w, float& y, const std::wstring& text, const std::wstring& sub, const std::wstring& url) {
    SetItem it;
    it.type = SetItem::Link;
    it.text = text;
    it.sub = sub;
    it.url = url;
    it.y = y;
    it.h = std::max(kSetRowMin, 30 + Set_TextH(w.fHint.get(), sub, w.contentW - kSetRowPad - 50) + 8);
    y += it.h + kSetRowGap;
    w.items.push_back(it);
}

static int g_optInfoRow;

static void Opt_AddInfo(SetWindow& w, float& y, const std::wstring& text, const std::wstring& sub) {
    Opt_AddLink(w, y, text, sub, L"info:" + std::to_wstring(g_optInfoRow++));
}

static void Opt_OverviewItems(SetWindow& w, float& y) {
    Opt_AddGroup(w, y, L"This PC");
    if (g_opt.infoOk) {
        const Js& r = g_opt.info;
        std::wstring win = Opt_Str(r, L"windows");
        const std::wstring build = Opt_Str(r, L"build"), rev = Opt_Str(r, L"revision");
        if (!build.empty()) win += L", build " + build + (rev.empty() || rev == L"0" ? L"" : L"." + rev);
        Opt_AddInfo(w, y, L"Windows", win);
        std::wstring cpu = Opt_Str(r, L"cpu");
        if (Opt_Num(r, L"threads") > 0) cpu += L", " + Opt_Str(r, L"threads") + L" threads";
        Opt_AddInfo(w, y, L"Processor", cpu);
        Opt_AddInfo(w, y, L"Memory", Opt_Size(Opt_Num(r, L"ram_free")) + L" free of " + Opt_Size(Opt_Num(r, L"ram_total")));
        if (const Js* drives = r.get(L"drives"); drives && drives->t == Js::Arr) {
            for (const Js& d : drives->a)
                Opt_AddInfo(w, y, L"Drive " + Opt_Str(d, L"drive"),
                            Opt_Size(Opt_Num(d, L"free")) + L" free of " + Opt_Size(Opt_Num(d, L"total")));
        }
        if (const Js* gpus = r.get(L"gpus"); gpus && gpus->t == Js::Arr && !gpus->a.empty()) {
            std::wstring all;
            for (const Js& g : gpus->a) all += (all.empty() ? L"" : L", ") + Js_Text(&g);
            Opt_AddInfo(w, y, L"Graphics", all);
        }
        Opt_AddInfo(w, y, L"Running for", Opt_Uptime(Opt_Num(r, L"uptime")));
        const long long undo = (long long)Opt_Num(r, L"undo_entries");
        Opt_AddInfo(w, y, L"Changes you can undo",
                    undo ? Opt_Count(undo) + L" saved. Turn a switch off and press Save to undo it." : L"None yet");
        Opt_AddInfo(w, y, L"Helper version", kOptEngineVersion);
    } else {
        Opt_AddInfo(w, y, g_opt.infoFailed ? L"Could not read this PC" : L"Reading your PC\u2026",
                    g_opt.ready ? L"Press Read again below to try once more." : L"Waiting for the helper program.");
    }
    Opt_AddGroup(w, y, L"Quick jobs");
    Opt_AddLink(w, y, L"Find junk to clean", L"Opens Clean up and looks for files you can clear.", L"opt:go-clean");
    Opt_AddLink(w, y, L"Make a restore point now", L"A safe point you can go back to if a change goes wrong.",
                L"opt:run:repair.restore-point");
    Opt_AddLink(w, y, L"Read again", L"Reads this PC and every page's settings once more.", L"opt:refresh");
    if (g_opt.engineFailed)
        Opt_AddLink(w, y, L"Try again", L"Fetch the helper program again.", L"opt:retry-engine");
}

static void Opt_CleanTop(SetWindow& w, float& y) {
    Opt_AddGroup(w, y, L"Scan and clean");
    const bool scanning = Opt_Pending(L"scan:clean");
    Opt_AddLink(w, y, scanning ? L"Scanning\u2026" : L"Scan again",
                L"Looks through everything below and shows how much each one holds.", L"opt:scan-clean");
    int n = 0;
    double bytes = 0;
    for (size_t k = 0; k < w.fields.size() && k < g_opt.meta.size(); k++) {
        const OptMeta& m = g_opt.meta[k];
        if (!Opt_IsClean(&m) || w.fields[k].cur != L"1" || (m.known && !m.avail)) continue;
        n++;
        bytes += m.bytes;
    }
    std::wstring sub = n == 0 ? L"Tick at least one item below first."
                              : L"Ticked: " + std::to_wstring(n) + (n == 1 ? L" item" : L" items") +
                                    (bytes > 0 ? L", about " + Opt_Size(bytes) : L"") +
                                    L". Deleted files do not go to the Recycle Bin.";
    const bool armed = Opt_IsArmed(L"opt:clean");
    Opt_AddLink(w, y, armed ? L"Click again to delete them for good" : L"Clean the ticked items", sub, L"opt:clean");
}

static void Opt_CleanBottom(SetWindow& w, float& y) {
    WCHAR drive[8] = L"C:";
    GetEnvironmentVariableW(L"SystemDrive", drive, 8);
    Opt_AddGroup(w, y, std::wstring(L"What fills ") + drive);
    if (Opt_Pending(L"space")) {
        Opt_AddInfo(w, y, L"Measuring\u2026", L"Going through every folder. This can take a few minutes.");
        return;
    }
    if (!g_opt.spaceOk) {
        Opt_AddLink(w, y, L"Measure the drive", L"Lists the biggest folders and files. This can take a few minutes.",
                    L"opt:space");
        return;
    }
    int folders = 0, files = 0;
    for (const Js& r : g_opt.space) {
        const std::wstring kind = Opt_Str(r, L"kind"), path = Opt_Str(r, L"path");
        if (kind == L"total") {
            Opt_AddInfo(w, y, Opt_Size(Opt_Num(r, L"bytes")) + L" in use",
                        Opt_Files((long long)Opt_Num(r, L"files")) + L" counted on " + drive + L".");
        } else if (kind == L"folder" && folders < 15) {
            folders++;
            Opt_AddLink(w, y, path, Opt_Size(Opt_Num(r, L"bytes")) + L" in " + Opt_Files((long long)Opt_Num(r, L"files")) +
                                        L". Click to show it in File Explorer.", L"open:" + path);
        } else if (kind == L"file" && files < 10) {
            files++;
            Opt_AddLink(w, y, path, Opt_Size(Opt_Num(r, L"bytes")) + L". One big file. Click to show it in File Explorer.",
                        L"open:" + path);
        }
    }
    Opt_AddLink(w, y, L"Measure again", L"Counts the drive once more.", L"opt:space");
}

static void Opt_AppsTop(SetWindow& w, float& y) {
    Opt_AddGroup(w, y, L"Remove apps");
    int n = 0;
    for (size_t k = 0; k < w.fields.size() && k < g_opt.meta.size(); k++)
        if (Opt_IsApp(&g_opt.meta[k]) && g_opt.meta[k].avail && w.fields[k].cur == L"1") n++;
    std::wstring sub = !Opt_Pending(L"scan:apps") && !g_opt.loaded.count(L"scan:apps")
                           ? L"Waiting for the helper program."
                       : Opt_Pending(L"scan:apps") ? L"Looking for the built-in apps on this PC\u2026"
                       : n == 0 ? L"Tick the apps below that you want gone."
                                : L"Ticked: " + std::to_wstring(n) + (n == 1 ? L" app." : L" apps.") +
                                      L" Most can be installed again from the Microsoft Store.";
    const bool armed = Opt_IsArmed(L"opt:remove-apps");
    Opt_AddLink(w, y, armed ? L"Click again to remove them" : L"Remove the ticked apps", sub, L"opt:remove-apps");
}

static void Opt_AppsBottom(SetWindow& w, float& y) {
    Opt_AddGroup(w, y, L"Installed programs");
    if (!g_opt.programsOk) {
        Opt_AddInfo(w, y, L"Reading the list\u2026", L"Every program Windows knows about, with its size.");
        return;
    }
    if (g_opt.programs.empty()) {
        Opt_AddInfo(w, y, L"No programs found", L"Windows lists nothing to uninstall.");
        return;
    }
    for (const Js& r : g_opt.programs) {
        const std::wstring name = Opt_Str(r, L"name"), key = Opt_Str(r, L"key");
        if (name.empty()) continue;
        std::wstring sub = Opt_Str(r, L"publisher");
        const std::wstring ver = Opt_Str(r, L"version");
        if (!ver.empty()) sub += (sub.empty() ? L"Version " : L", version ") + ver;
        if (Opt_Num(r, L"bytes") > 0) sub += (sub.empty() ? L"" : L", ") + Opt_Size(Opt_Num(r, L"bytes"));
        if (sub.empty()) sub = L"No details";
        if (Opt_Bool(r, L"removable") && !key.empty()) {
            const std::wstring url = L"opt:uninstall:" + key;
            const bool armed = Opt_IsArmed(url);
            Opt_AddLink(w, y, armed ? L"Click again to uninstall " + name : name,
                        sub + (armed ? L". Its own uninstaller may ask you a question." : L""), url);
        } else {
            Opt_AddInfo(w, y, name, sub + L". Windows keeps this one.");
        }
    }
}

static void Opt_UpdatesBottom(SetWindow& w, float& y) {
    Opt_AddGroup(w, y, L"Waiting updates");
    if (!g_opt.updatesOk) {
        Opt_AddInfo(w, y, L"Checking Windows Update\u2026", L"This can take a minute.");
        return;
    }
    if (g_opt.updates.empty()) {
        Opt_AddInfo(w, y, L"Nothing waiting", L"Windows Update has nothing new for this PC right now.");
    }
    for (const Js& r : g_opt.updates) {
        const std::wstring id = Opt_Str(r, L"id"), title = Opt_Str(r, L"title");
        if (id.empty()) continue;
        std::wstring sub;
        const std::wstring kb = Opt_Str(r, L"kb");
        if (!kb.empty()) sub = (Opt_Starts(kb, L"KB") ? L"" : L"KB") + kb;
        if (Opt_Num(r, L"bytes") > 0) sub += (sub.empty() ? L"" : L", ") + Opt_Size(Opt_Num(r, L"bytes"));
        if (Opt_Bool(r, L"driver")) sub += (sub.empty() ? L"A driver" : L", a driver");
        const bool hidden = Opt_Bool(r, L"hidden");
        sub += hidden ? (sub.empty() ? L"Hidden. Click to let Windows install it again." : L". Hidden. Click to let Windows install it again.")
                      : (sub.empty() ? L"Click to hide it, so Windows does not install it." : L". Click to hide it, so Windows does not install it.");
        Opt_AddLink(w, y, title.empty() ? id : title, sub, (hidden ? L"opt:unhide:" : L"opt:hide:") + id);
    }
    Opt_AddLink(w, y, L"Check again", L"Asks Windows Update once more.", L"opt:updates");
}

static void Opt_RepairTop(SetWindow& w, float& y) {
    PCWSTR last = nullptr;
    for (const OptItem& it : kOptItems) {
        if (it.page != kPgRepair) continue;
        if (!last || wcscmp(last, it.group) != 0) {
            Opt_AddGroup(w, y, it.group);
            last = it.group;
        }
        std::wstring sub = it.desc;
        if (it.reboot) sub += L" Needs a restart.";
        if (*it.warn) sub += std::wstring(L" ") + it.warn;
        const std::wstring url = std::wstring(L"opt:run:") + it.id;
        const bool running = Opt_Pending((L"run:" + std::wstring(it.id)).c_str());
        Opt_AddLink(w, y, running ? std::wstring(it.name) + L": running\u2026" : Opt_IsArmed(url) ? L"Click again to run it" : it.name,
                    sub, url);
    }
}

static void Hub_ItemsTop(SetWindow& w, float& y) {
    g_optInfoRow = 0;
    const size_t before = w.items.size();
    if (w.page == kPgOverview) Opt_OverviewItems(w, y);
    else if (w.page == kPgClean) Opt_CleanTop(w, y);
    else if (w.page == kPgApps) Opt_AppsTop(w, y);
    else if (w.page == kPgRepair) Opt_RepairTop(w, y);
    if (w.items.size() > before) y += 14;
}

static void Hub_ItemsBottom(SetWindow& w, float& y) {
    if (w.page == kPgClean) Opt_CleanBottom(w, y);
    else if (w.page == kPgApps) Opt_AppsBottom(w, y);
    else if (w.page == kPgUpdates) Opt_UpdatesBottom(w, y);
    else if (w.page == kPgPerf && !g_opt.startupOk) {
        Opt_AddGroup(w, y, L"Starts with Windows");
        Opt_AddInfo(w, y, L"Reading what starts with Windows\u2026", L"Programs that open by themselves when you sign in.");
    } else if (w.page == kPgPerf && w.fields.size() == g_opt.baseCount) {
        Opt_AddGroup(w, y, L"Starts with Windows");
        Opt_AddInfo(w, y, L"Nothing extra starts with Windows", L"No programs open by themselves when you sign in.");
    }
}

// ---- Window hooks -------------------------------------------------------------------

static std::wstring Hub_PageTitle(SetWindow& w) { return kSetPages[std::clamp(w.page, 0, kSetPageCount - 1)].name; }

static std::wstring Hub_PageIntro(SetWindow& w) { return kSetPages[std::clamp(w.page, 0, kSetPageCount - 1)].intro; }

static std::wstring Hub_Banner(SetWindow& w) {
    std::wstring s;
    if (g_opt.engineFailed) s = L"The helper program could not be fetched (" + g_opt.engineErr + L"). Open Overview and press Try again.";
    else s = Opt_Busy();
    if (g_opt.restart) s += (s.empty() ? L"" : L"\n") + std::wstring(L"Restart Windows to finish some changes.");
    return s;
}

static bool Hub_Show(SetWindow& w, const SetField& f) {
    if (f.page != w.page) return false;
    if (f.hub != 5 && f.hub != 8) return true;
    const OptMeta* m = Opt_MetaOf(w, f);
    if (!m) return true;
    if (f.hub == 8) return m->known && m->avail;
    if (Opt_IsClean(m)) return !m->known || m->avail;
    return m->known && m->avail;
}

static WCHAR Hub_LinkGlyph(const std::wstring& url) {
    if (url == L"opt:scan-clean" || url == L"opt:space") return 0xE721;
    if (url == L"opt:clean" || url == L"opt:remove-apps" || Opt_Starts(url, L"opt:uninstall:")) return 0xE74D;
    if (Opt_Starts(url, L"opt:run:")) return 0xE768;
    if (url == L"opt:refresh" || url == L"opt:retry-engine" || url == L"opt:updates") return 0xE72C;
    if (url == L"opt:go-clean") return 0xE72A;
    if (Opt_Starts(url, L"opt:hide:")) return 0xED1A;
    if (Opt_Starts(url, L"opt:unhide:")) return 0xE7B3;
    if (Opt_Starts(url, L"open:")) return 0xE838;
    return 0xE8A7;
}

static bool Hub_Resettable(SetWindow& w, SetField& f) {
    return (f.hub == 0 || f.hub == 5 || f.hub == 8) && Hub_Show(w, f);
}

static bool Hub_LeaveDetail(SetWindow& w, bool& left) {
    left = false;
    return true;
}

static bool Hub_Link(PCWSTR url) {
    const std::wstring u = url ? url : L"";
    if (Opt_Starts(u, L"info:")) return true;
    if (!Opt_Starts(u, L"opt:") && !Opt_Starts(u, L"open:")) return false;
    if (g_setWin && g_setWin->hwnd) {
        auto action = new std::wstring(u);
        if (!PostMessageW(g_setWin->hwnd, WM_HUB_ACTION, 0, (LPARAM)action)) delete action;
    }
    return true;
}

static void Hub_Cancel(SetWindow& w) {
    Set_CommitEdit(w, false);
    Set_StopRecording(w);
    Set_ClosePopup(w);
    Opt_Disarm(w);
    if (Set_ChangedCount(w) > 0) {
        for (auto& f : w.fields)
            if (f.hub != 5) f.cur = f.value;
        Set_SetStatus(w, L"Changes discarded");
        return;
    }
    PostMessageW(w.hwnd, WM_CLOSE, 0, 0);
}

static void Hub_Escape(SetWindow& w) {
    if (g_opt.armUrl.empty()) return;
    Opt_Disarm(w);
    Set_BuildAndClamp(w);
}

static void Hub_PageChanged(SetWindow& w) {
    Opt_Disarm(w);
    Opt_LoadPage(w);
}

static float Hub_MaxW(const SetWindow& w) { return Hub_TwoCol(w) ? 1480.0f : kSetMaxW; }

static bool Hub_TwoCol(const SetWindow& w) { return w.page != kPgLook && w.page != kSetAboutPage; }

static bool Hub_DrawRow(SetPaint& p, SetWindow& w, const SetItem& it) { return false; }

static bool Hub_DrawLink(SetPaint& p, SetWindow& w, const SetItem& it, int idx) {
    const bool info = Opt_Starts(it.url, L"info:");
    const bool armed = Opt_IsArmed(it.url);
    if (!info && !armed) return false;
    D2D1_RECT_F row = Set_RowRect(w, it);
    if (info) {
        Set_DrawCard(p, row, 0);
        p.Text(w.fLabel.get(), it.text, {row.left + kSetRowPad, row.top + 9, row.right - kSetRowPad, row.top + 30}, mocha::text);
        p.Text(w.fHint.get(), it.sub, {row.left + kSetRowPad, row.top + 30, row.right - kSetRowPad, row.bottom - 4}, mocha::subtext0);
        return true;
    }
    float hov = Set_GlowOf(w, 3000 + idx);
    Set_DrawCard(p, row, hov);
    p.GradFill(row, 10, 0.13f * hov);
    p.GradRing(row, 10, hov, 1.5f);
    p.Text(w.fLabel.get(), it.text, {row.left + kSetRowPad, row.top + 9, row.right - 50, row.top + 30}, mocha::red);
    p.Text(w.fHint.get(), it.sub, {row.left + kSetRowPad, row.top + 30, row.right - 50, row.bottom - 4}, mocha::subtext0);
    p.Glyph(w.fIcon.get(), (WCHAR)0xE7BA, {row.right - 46, row.top, row.right - 12, row.bottom}, mocha::red);
    return true;
}

static bool Hub_BarBox(const SetField& f, const D2D1_RECT_F& row, D2D1_RECT_F& box) { return false; }

static bool Hub_HitRow(SetWindow& w, const SetItem& it, const D2D1_RECT_F& row, float x, float cy, SetHit& h) {
    return false;
}

static void Hub_HitLink(SetWindow& w, int i, const D2D1_RECT_F& row, float x, float cy, SetHit& h) {
    if (i >= 0 && i < (int)w.items.size() && Opt_Starts(w.items[i].url, L"info:")) {
        h.kind = SetHit::None;
        h.id = -1;
    }
}

static void Hub_CardClick(SetWindow& w, int a, int b) {}

static void Hub_Chose(SetWindow& w, int k) {
    if (k < 0 || k >= (int)w.fields.size()) return;
    SetField& f = w.fields[k];
    if (f.hub == 5) {
        f.value = f.cur;
        Set_BuildAndClamp(w);
        return;
    }
    Set_Invalidate(w);
}

static void Hub_Reflow(SetWindow& w, float& y) {}

static void Hub_PlaceCode(SetWindow& w) {}

static bool Hub_CodeFocused() { return false; }

// ---- Actions --------------------------------------------------------------------------

static void Opt_OpenPath(const std::wstring& path) {
    PIDLIST_ABSOLUTE pidl = ILCreateFromPathW(path.c_str());
    if (!pidl) return;
    SHOpenFolderAndSelectItems(pidl, 0, nullptr, 0);
    ILFree(pidl);
}

static void Opt_Clean(SetWindow& w) {
    if (Opt_Pending(L"scan:clean")) {
        Set_SetStatus(w, L"Wait for the scan to finish first.", true);
        return;
    }
    if (Opt_Pending(L"apply:clean")) {
        Set_SetStatus(w, L"Cleaning is already running.", true);
        return;
    }
    std::vector<std::wstring> ids;
    bool undo = false;
    for (size_t k = 0; k < w.fields.size() && k < g_opt.meta.size(); k++) {
        const OptMeta& m = g_opt.meta[k];
        if (!Opt_IsClean(&m) || w.fields[k].cur != L"1" || (m.known && !m.avail)) continue;
        ids.push_back(m.item->id);
        undo = undo || m.item->undo;
    }
    if (ids.empty()) {
        Set_SetStatus(w, L"Tick at least one item to clean.", true);
        return;
    }
    std::wstring args = L"apply --ids " + Set_QuoteArg(Opt_Join(ids));
    if (undo && Opt_RestoreOn(w)) args += L" --restore-point";
    if (!Opt_Queue(L"apply:clean", args, true)) Set_SetStatus(w, L"The helper program is not ready yet.", true);
    else Set_SetStatus(w, L"");
}

static void Opt_RemoveApps(SetWindow& w) {
    if (Opt_Pending(L"apply:apps")) {
        Set_SetStatus(w, L"Apps are already being removed.", true);
        return;
    }
    std::vector<std::wstring> ids;
    for (size_t k = 0; k < w.fields.size() && k < g_opt.meta.size(); k++)
        if (Opt_IsApp(&g_opt.meta[k]) && g_opt.meta[k].avail && w.fields[k].cur == L"1") ids.push_back(g_opt.meta[k].item->id);
    if (ids.empty()) {
        Set_SetStatus(w, L"Tick at least one app to remove.", true);
        return;
    }
    std::wstring args = L"apply --ids " + Set_QuoteArg(Opt_Join(ids));
    if (Opt_RestoreOn(w)) args += L" --restore-point";
    if (!Opt_Queue(L"apply:apps", args, true)) Set_SetStatus(w, L"The helper program is not ready yet.", true);
    else Set_SetStatus(w, L"");
}

static void Opt_Action(SetWindow& w, const std::wstring& url) {
    if (Opt_Starts(url, L"open:")) {
        Opt_OpenPath(url.substr(5));
        return;
    }
    if (!Opt_Starts(url, L"opt:")) return;
    const std::wstring a = url.substr(4);
    if (a == L"retry-engine") {
        g_opt.engineFailed = false;
        g_opt.engineErr.clear();
        Opt_Queue(L"engine", L"");
        Set_BuildAndClamp(w);
        return;
    }
    if (!g_opt.ready) {
        Set_SetStatus(w, L"The helper program is not ready yet.", true);
        return;
    }
    if (a == L"go-clean") {
        Set_GoPage(w, kPgClean);
        Opt_Read(L"scan:clean");
    } else if (a == L"scan-clean") {
        Opt_Read(L"scan:clean");
    } else if (a == L"clean") {
        if (Opt_Armed(w, url)) Opt_Clean(w);
        return;
    } else if (a == L"remove-apps") {
        if (Opt_Armed(w, url)) Opt_RemoveApps(w);
        return;
    } else if (a == L"refresh") {
        const std::set<std::wstring> again = g_opt.loaded;
        for (auto& tag : again)
            if (tag != L"space") Opt_Read(tag);
        Opt_Read(L"info");
    } else if (a == L"space") {
        Opt_Read(L"space");
    } else if (a == L"updates") {
        Opt_Read(L"updates");
    } else if (Opt_Starts(a, L"run:")) {
        const std::wstring id = a.substr(4);
        const OptItem* it = Opt_Item(id);
        if (!it) return;
        if (wcscmp(it->risk, L"safe") != 0 && !Opt_Armed(w, url)) return;
        Opt_Disarm(w);
        if (Opt_Pending((L"run:" + id).c_str())) {
            Set_SetStatus(w, L"That is already running.", true);
            return;
        }
        Opt_Queue(L"run:" + id, L"apply --ids " + Set_QuoteArg(id), true);
    } else if (Opt_Starts(a, L"uninstall:")) {
        if (!Opt_Armed(w, url)) return;
        const std::wstring key = a.substr(10);
        Opt_Queue(L"uninstall:" + key, L"tool programs uninstall " + Set_QuoteArg(key), true);
    } else if (Opt_Starts(a, L"hide:")) {
        Opt_Queue(L"hide", L"tool updates hide " + Set_QuoteArg(a.substr(5)));
        Opt_Read(L"updates");
    } else if (Opt_Starts(a, L"unhide:")) {
        Opt_Queue(L"hide", L"tool updates unhide " + Set_QuoteArg(a.substr(7)));
        Opt_Read(L"updates");
    }
    Set_BuildAndClamp(w);
}

// ---- Results ---------------------------------------------------------------------------

static void Opt_ReadStates(SetWindow& w, const OptOut& out) {
    for (const Js& v : out.lines) {
        if (Opt_Str(v, L"t") != L"state") continue;
        auto found = g_opt.byId.find(Opt_Str(v, L"id"));
        if (found == g_opt.byId.end() || found->second >= (int)w.fields.size()) continue;
        const size_t k = (size_t)found->second;
        SetField& f = w.fields[k];
        OptMeta& m = g_opt.meta[k];
        m.known = true;
        m.avail = Opt_Bool(v, L"available");
        if (f.hub == 8) {
            const bool pending = f.cur != f.value;
            f.value = Opt_Bool(v, L"applied") ? L"1" : L"0";
            if (!pending) f.cur = f.value;
        } else if (Opt_IsClean(&m)) {
            m.bytes = Opt_Num(v, L"bytes");
            m.files = (long long)Opt_Num(v, L"files");
            Opt_SetDesc(w, k);
        }
    }
}

struct OptTally {
    int ok = 0, failed = 0;
    double bytes = 0;
    bool reboot = false;
    std::wstring firstError;
};

static OptTally Opt_Tally(const OptOut& out) {
    OptTally t;
    for (const Js& v : out.lines) {
        if (Opt_Str(v, L"t") != L"result") continue;
        if (Opt_Bool(v, L"ok")) t.ok++;
        else {
            t.failed++;
            if (t.firstError.empty()) t.firstError = Opt_Str(v, L"error");
        }
        t.bytes += Opt_Num(v, L"bytes");
        t.reboot = t.reboot || Opt_Bool(v, L"reboot");
    }
    return t;
}

static std::vector<Js> Opt_Rows(const OptOut& out) {
    std::vector<Js> rows;
    for (const Js& v : out.lines)
        if (Opt_Str(v, L"t") == L"row") rows.push_back(v);
    return rows;
}

static std::wstring Opt_Failed(const OptTally& t) {
    if (!t.failed) return {};
    std::wstring s = std::to_wstring(t.failed) + (t.failed == 1 ? L" did not work" : L" did not work");
    if (!t.firstError.empty()) s += L": " + Opt_Cut(t.firstError, 90);
    return s + L".";
}

static void Opt_OnResult(SetWindow& w, OptOut& out) {
    auto at = std::find(g_opt.tags.begin(), g_opt.tags.end(), out.tag);
    if (at != g_opt.tags.end()) g_opt.tags.erase(at);
    g_opt.progMsg.clear();
    g_opt.progDone = g_opt.progTotal = 0;
    const std::wstring& tag = out.tag;
    if (tag == L"engine") {
        g_opt.ready = out.ran;
        g_opt.engineFailed = !out.ran;
        g_opt.engineErr = out.err.empty() ? L"unknown problem" : out.err;
        if (out.ran) Opt_LoadPage(w);
        Set_BuildAndClamp(w);
        return;
    }
    if (!out.ran) {
        if (tag == L"info") g_opt.infoFailed = true;
        if (tag == L"programs") g_opt.programsOk = true;
        if (tag == L"updates") g_opt.updatesOk = true;
        if (tag == L"startup") g_opt.startupOk = true;
        if (Opt_IsRead(tag)) g_opt.loaded.erase(tag);
        Set_SetStatus(w, (Opt_TagText(tag) + L" did not finish: " + out.err + L".").c_str(), true);
        Set_BuildAndClamp(w);
        return;
    }
    if (out.code == 3) {
        Set_SetStatus(w, L"The helper program needs admin rights for that.", true);
    }
    const OptTally t = Opt_Tally(out);
    g_opt.restart = g_opt.restart || t.reboot;
    const std::wstring failed = Opt_Failed(t);
    if (Opt_Starts(tag, L"scan:")) {
        Opt_ReadStates(w, out);
    } else if (tag == L"info") {
        const std::vector<Js> rows = Opt_Rows(out);
        g_opt.infoOk = !rows.empty();
        g_opt.infoFailed = rows.empty();
        if (!rows.empty()) g_opt.info = rows.front();
    } else if (tag == L"startup") {
        Opt_SetStartup(w, Opt_Rows(out));
        g_opt.startupOk = true;
    } else if (tag == L"programs") {
        g_opt.programs = Opt_Rows(out);
        std::stable_sort(g_opt.programs.begin(), g_opt.programs.end(), [](const Js& a, const Js& b) {
            return _wcsicmp(Opt_Str(a, L"name").c_str(), Opt_Str(b, L"name").c_str()) < 0;
        });
        g_opt.programsOk = true;
    } else if (tag == L"updates") {
        g_opt.updates = Opt_Rows(out);
        g_opt.updatesOk = true;
    } else if (tag == L"space") {
        g_opt.space = Opt_Rows(out);
        g_opt.spaceOk = true;
    } else if (tag == L"apply:clean") {
        std::wstring s = L"Freed " + Opt_Size(t.bytes) + L".";
        if (!failed.empty()) s += L" " + failed;
        Set_SetStatus(w, s.c_str(), t.failed > 0);
        Opt_Read(L"scan:clean");
    } else if (tag == L"apply:apps") {
        for (const Js& v : out.lines) {
            if (Opt_Str(v, L"t") != L"result" || !Opt_Bool(v, L"ok")) continue;
            auto found = g_opt.byId.find(Opt_Str(v, L"id"));
            if (found != g_opt.byId.end() && found->second < (int)w.fields.size())
                w.fields[found->second].cur = w.fields[found->second].value = L"0";
        }
        std::wstring s = t.ok ? L"Removed " + std::to_wstring(t.ok) + (t.ok == 1 ? L" app." : L" apps.") : L"";
        if (!failed.empty()) s += (s.empty() ? L"" : L" ") + failed;
        Set_SetStatus(w, s.empty() ? L"Nothing was removed." : s.c_str(), t.failed > 0);
        Opt_Read(L"scan:apps");
    } else if (tag == L"apply:tweaks" || tag == L"revert:tweaks") {
        if (t.failed) Set_SetStatus(w, failed.c_str(), true);
        else if (g_opt.tags.empty() || !Opt_Starts(g_opt.tags.front(), L"apply:") && !Opt_Starts(g_opt.tags.front(), L"revert:"))
            Set_SetStatus(w, L"Saved");
    } else if (Opt_Starts(tag, L"run:")) {
        const OptItem* it = Opt_Item(tag.substr(4));
        if (t.failed) Set_SetStatus(w, failed.c_str(), true);
        else if (tag == L"run:repair.restore-point") Set_SetStatus(w, L"Restore point made.");
        else Set_SetStatus(w, (std::wstring(L"Done: ") + (it ? it->name : L"the repair") + L".").c_str());
        if (tag == L"run:repair.restore-point") Opt_Read(L"info");
    } else if (tag == L"startup-set") {
        if (t.failed) Set_SetStatus(w, failed.c_str(), true);
        Opt_Read(L"startup");
    } else if (Opt_Starts(tag, L"uninstall:")) {
        bool removed = false;
        for (const Js& r : Opt_Rows(out)) removed = removed || Opt_Bool(r, L"removed");
        Set_SetStatus(w, removed ? L"Uninstalled." : L"The program is still there. Its uninstaller may have been stopped.", !removed);
        Opt_Read(L"programs");
    } else if (tag == L"hide") {
        if (out.code != 0 || t.failed) Set_SetStatus(w, L"Windows Update did not take that change.", true);
    }
    Set_BuildAndClamp(w);
}

static void Opt_OnFeed(SetWindow& w, const OptFeed& feed) {
    if (g_opt.tags.empty() || g_opt.tags.front() != feed.tag) return;
    g_opt.progMsg = feed.msg;
    g_opt.progDone = feed.done;
    g_opt.progTotal = feed.total;
    if (!g_opt.feedTimer) g_opt.feedTimer = SetTimer(w.hwnd, kOptFeedTimer, 150, nullptr) != 0;
}

// ---- Saving ---------------------------------------------------------------------------

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
    if (!keep || !keep->hwnd || keep->saving) return;
    SetWindow& w = *keep;
    Set_CommitEdit(w, true);
    Set_StopRecording(w);
    Set_ClosePopup(w);
    Opt_Disarm(w);
    // The helper's switches go to the helper. Their value is set to what was asked; the rescan
    // that follows puts back the truth if a change did not take.
    std::vector<std::wstring> on, off;
    std::set<int> pages;
    int jobs = 0;
    for (size_t k = 0; k < w.fields.size(); k++) {
        SetField& f = w.fields[k];
        if (f.hub == 5) f.value = f.cur;
        if (f.hub != 8 && f.hub != 9) continue;
        const std::wstring now = Set_FieldValue(f);
        if (now == f.value) continue;
        if (f.hub == 8) {
            (now == L"1" ? on : off).push_back(f.key);
            pages.insert(f.page);
        } else if (k < g_opt.meta.size()) {
            const OptMeta& m = g_opt.meta[k];
            if (Opt_Queue(L"startup-set", L"tool startup set " + Set_QuoteArg(m.scope) + L" " + Set_QuoteArg(m.name) +
                                              (now == L"1" ? L" on" : L" off")))
                jobs++;
        }
        f.value = now;
    }
    if (!on.empty() &&
        Opt_Queue(L"apply:tweaks", L"apply --ids " + Set_QuoteArg(Opt_Join(on)) + (Opt_RestoreOn(w) ? L" --restore-point" : L"")))
        jobs += (int)on.size();
    if (!off.empty() && Opt_Queue(L"revert:tweaks", L"revert --ids " + Set_QuoteArg(Opt_Join(off)))) jobs += (int)off.size();
    for (int page : pages) Opt_Read(std::wstring(L"scan:") + Opt_PageName(page));
    if (Opt_Pending(L"startup-set")) Opt_Read(L"startup");
    // What is left is this mod's own settings, written by Windhawk's command line tool.
    int changed = 0;
    const std::wstring params = Set_ChangedParams(w, changed);
    bool savedOwn = false, failed = false;
    if (changed > 0) {
        const std::wstring cli = Set_CliPath();
        if (cli.empty()) {
            Set_SetStatus(w, L"Windhawk's command line tool was not found, so the window settings were not saved.", true);
            failed = true;
        } else {
            std::wstring cmd = Set_QuoteArg(cli) + L" " + params;
            STARTUPINFOW si{sizeof(si)};
            si.dwFlags = STARTF_USESHOWWINDOW;
            si.wShowWindow = SW_HIDE;
            PROCESS_INFORMATION pi{};
            if (CreateProcessW(cli.c_str(), cmd.data(), nullptr, nullptr, FALSE, CREATE_NO_WINDOW, nullptr, nullptr, &si, &pi)) {
                CloseHandle(pi.hThread);
                w.saving = true;
                Set_SetStatus(w, L"Saving\u2026");
                const ULONGLONG until = GetTickCount64() + 60000;
                bool quit = false, done = false;
                WPARAM quitCode = 0;
                while (!quit) {
                    const ULONGLONG now = GetTickCount64();
                    if (now >= until) break;
                    const DWORD r = MsgWaitForMultipleObjects(1, &pi.hProcess, FALSE, (DWORD)(until - now), QS_ALLINPUT);
                    if (r == WAIT_OBJECT_0) {
                        done = true;
                        break;
                    }
                    if (r != WAIT_OBJECT_0 + 1) break;
                    MSG m;
                    while (PeekMessageW(&m, nullptr, 0, 0, PM_REMOVE)) {
                        if (m.message == WM_QUIT) {
                            quit = true;
                            quitCode = m.wParam;
                            break;
                        }
                        TranslateMessage(&m);
                        DispatchMessageW(&m);
                    }
                    if (keep->destroyed) break;
                }
                DWORD code = 1;
                if (done) GetExitCodeProcess(pi.hProcess, &code);
                CloseHandle(pi.hProcess);
                w.saving = false;
                if (quit) PostQuitMessage((int)quitCode);
                if (keep->destroyed || !w.hwnd) return;
                if (done && code == 0) {
                    for (auto& f : w.fields)
                        if (f.hub == 0) f.value = Set_FieldValue(f);
                    savedOwn = true;
                } else {
                    Set_SetStatus(w, L"Windhawk did not take the window settings. Try Save again.", true);
                    failed = true;
                }
            } else {
                Set_SetStatus(w, L"Windhawk's command line tool did not start, so the window settings were not saved.", true);
                failed = true;
            }
        }
    }
    g_settings.animations = Set_FieldOn(w, L"animations", true);
    Set_ApplyFrame(w);
    Hub_TrayUpdate(w);
    if (!failed) {
        if (jobs > 0) Set_SetStatus(w, (L"Applying " + std::to_wstring(jobs) + (jobs == 1 ? L" change" : L" changes") + L"\u2026").c_str());
        else Set_SetStatus(w, savedOwn ? L"Saved" : L"Nothing changed");
    }
    Set_BuildAndClamp(w);
}

// ---- Tray icon --------------------------------------------------------------------------

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

static UINT TrayIconId() {
    UINT hash = 2166136261u;
    for (PCWSTR p = WH_MOD_ID; *p; p++) hash = (hash ^ (UINT)*p) * 16777619u;
    return hash | 0x80000000u;
}

// The mark: a gradient glyph on a clear background, drawn at four times the size and shrunk.
static HICON Hub_MakeTrayIcon() {
    int size = 4 * GetSystemMetricsForDpi(SM_CXICON, GetDpiForSystem());
    if (size < 64) size = 64;
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
    WCHAR g[2] = {(WCHAR)0xEC4A, 0};
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
    return icon ? Crisp_ShrinkIcon(icon, 4) : nullptr;
}

static void Hub_TrayUpdate(SetWindow& w) {
    static HICON badge = Hub_MakeTrayIcon();
    NOTIFYICONDATAW nid{};
    nid.cbSize = sizeof(nid);
    nid.hWnd = w.hwnd;
    nid.uID = TrayIconId();
    const bool want = !g_opt.noTray && Set_FieldOn(w, L"settingsTrayIcon", true) && w.hwnd;
    if (!want) {
        if (g_opt.trayOn) Shell_NotifyIconW(NIM_DELETE, &nid);
        g_opt.trayOn = false;
        return;
    }
    nid.uFlags = NIF_MESSAGE | NIF_ICON | NIF_TIP | NIF_SHOWTIP;
    nid.uCallbackMessage = WM_HUB_TRAY;
    nid.hIcon = badge ? badge : w.iconSmall;
    wcscpy_s(nid.szTip, kOptName);
    if (g_opt.trayOn) {
        Shell_NotifyIconW(NIM_MODIFY, &nid);
        return;
    }
    if (Shell_NotifyIconW(NIM_ADD, &nid)) {
        nid.uVersion = NOTIFYICON_VERSION_4;
        Shell_NotifyIconW(NIM_SETVERSION, &nid);
        g_opt.trayOn = true;
    }
}

static void Hub_TrayMenu(SetWindow& w, int x, int y) {
    const POINT at{x, y};
    const int cmd = Set_TrayMenu(w.hwnd, {Set_MenuRow(1, L"\uF2D0", L"Open Seamless Windows Optimizer"),
                                          Set_MenuSep(),
                                          Set_MenuRow(3, L"\uF011", L"Quit")}, &at);
    if (cmd == 1) {
        PostMessageW(w.hwnd, WM_APP_SETTINGS_ACTIVATE, 0, 0);
    } else if (cmd == 3) {
        // The mod stays on in Windhawk: Quit hides the window and the tray icon until the mod is
        // turned on again or one of its settings changes.
        Set_CommitEdit(w, true);
        g_opt.noTray = true;
        Hub_TrayUpdate(w);
        ShowWindow(w.hwnd, SW_HIDE);
    }
}

static LRESULT CALLBACK Hub_SubProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp, UINT_PTR, DWORD_PTR) {
    if (msg == WM_NCDESTROY) {
        RemoveWindowSubclass(hwnd, Hub_SubProc, 7);
        return DefSubclassProc(hwnd, msg, wp, lp);
    }
    std::shared_ptr<SetWindow> keep = g_setWin;
    SetWindow* w = keep && keep->hwnd == hwnd ? keep.get() : nullptr;
    if (!w) {
        if (msg == WM_HUB_RESULT) delete (OptOut*)lp;
        else if (msg == WM_HUB_FEED) delete (OptFeed*)lp;
        else if (msg == WM_HUB_ACTION) delete (std::wstring*)lp;
        return DefSubclassProc(hwnd, msg, wp, lp);
    }
    if (g_opt.taskbarCreated && msg == g_opt.taskbarCreated) {
        g_opt.trayOn = false;
        Hub_TrayUpdate(*w);
        return 0;
    }
    switch (msg) {
        case WM_HUB_ACTION: {
            std::unique_ptr<std::wstring> action((std::wstring*)lp);
            if (!w->saving && action) Opt_Action(*w, *action);
            return 0;
        }
        case WM_HUB_RESULT: {
            std::unique_ptr<OptOut> out((OptOut*)lp);
            if (out) Opt_OnResult(*w, *out);
            return 0;
        }
        case WM_HUB_FEED: {
            std::unique_ptr<OptFeed> feed((OptFeed*)lp);
            if (feed) Opt_OnFeed(*w, *feed);
            return 0;
        }
        case WM_HUB_REBUILD:
            Set_BuildAndClamp(*w);
            return 0;
        case WM_HUB_MODCHANGED:
            g_opt.noTray = false;
            if (!w->saving) {
                g_settings.animations = Set_FieldOn(*w, L"animations", true);
                Hub_TrayUpdate(*w);
                if (!g_opt.trayOn && !IsWindowVisible(hwnd)) PostMessageW(hwnd, WM_APP_SETTINGS_ACTIVATE, 0, 0);
            }
            return 0;
        case WM_TIMER:
            if (wp == kHubArmTimer) {
                KillTimer(hwnd, kHubArmTimer);
                if (!g_opt.armUrl.empty() && GetTickCount64() - g_opt.armAt >= kOptArmMs) {
                    g_opt.armUrl.clear();
                    Set_BuildAndClamp(*w);
                }
                return 0;
            }
            if (wp == kOptFeedTimer) {
                KillTimer(hwnd, kOptFeedTimer);
                g_opt.feedTimer = false;
                Set_BuildAndClamp(*w);
                return 0;
            }
            break;
        case WM_HUB_TRAY:
            switch (LOWORD(lp)) {
                case NIN_SELECT:
                case NIN_KEYSELECT:
                    PostMessageW(hwnd, WM_APP_SETTINGS_ACTIVATE, 0, 0);
                    break;
                case WM_CONTEXTMENU:
                    Hub_TrayMenu(*w, GET_X_LPARAM(wp), GET_Y_LPARAM(wp));
                    break;
            }
            return 0;
        case WM_CLOSE:
            if (w->saving && !g_opt.quitting) return 0;
            if (!g_opt.quitting) {
                Set_CommitEdit(*w, true);
                Opt_Disarm(*w);
                ShowWindow(hwnd, SW_HIDE);
                return 0;
            }
            break;
        case WM_SHOWWINDOW:
            if (!wp) {
                KillTimer(hwnd, kSetTimerId);
                w->timer = false;
            } else {
                w->timer = SetTimer(hwnd, kSetTimerId, 15, nullptr) != 0;
                PostMessageW(hwnd, WM_HUB_REBUILD, 0, 0);
                Opt_LoadPage(*w);
            }
            break;
        case WM_DESTROY:
            g_opt.quitting = g_opt.noTray = true;
            Hub_TrayUpdate(*w);
            break;
    }
    return DefSubclassProc(hwnd, msg, wp, lp);
}

// ---- Life cycle ---------------------------------------------------------------------------

static void Hub_DarkMenus() {
    HMODULE ux = LoadLibraryExW(L"uxtheme.dll", nullptr, LOAD_LIBRARY_SEARCH_SYSTEM32);
    if (!ux) return;
    using Mode_t = int(WINAPI*)(int);
    using Flush_t = void(WINAPI*)();
    if (auto mode = (Mode_t)(void*)GetProcAddress(ux, MAKEINTRESOURCEA(135))) mode(2 /* ForceDark */);
    if (auto flush = (Flush_t)(void*)GetProcAddress(ux, MAKEINTRESOURCEA(136))) flush();
}

static void Opt_StopWorker() {
    g_work.halt = true;
    {
        std::lock_guard<std::mutex> lock(g_work.m);
        g_work.stop = true;
        g_work.jobs.clear();
    }
    g_work.cv.notify_all();
    if (g_work.thread) {
        WaitForSingleObject(g_work.thread, INFINITE);
        CloseHandle(g_work.thread);
        g_work.thread = nullptr;
    }
    if (g_work.engine != INVALID_HANDLE_VALUE) {
        CloseHandle(g_work.engine);
        g_work.engine = INVALID_HANDLE_VALUE;
    }
}

static DWORD WINAPI Hub_ModThread(void*) {
    SetThreadDpiAwarenessContext(DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2);
    MSG peek;
    PeekMessageW(&peek, nullptr, WM_USER, WM_USER, PM_NOREMOVE);  // Give the thread its queue now.
    if (FAILED(CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED))) { SetEvent(g_modReady); return 1; }
    g_settings.animations = Wh_GetIntSetting(L"animations") != 0;
    Hub_WriteMotion();
    Hub_DarkMenus();
    if (!Set_Create(false)) { SetEvent(g_modReady); CoUninitialize(); return 1; }
    HWND hwnd = g_setWin->hwnd;
    g_settingsWnd = hwnd;
    SetWindowSubclass(hwnd, Hub_SubProc, 7, 0);
    g_opt.taskbarCreated = RegisterWindowMessageW(L"TaskbarCreated");
    ChangeWindowMessageFilterEx(hwnd, g_opt.taskbarCreated, MSGFLT_ALLOW, nullptr);
    Hub_TrayUpdate(*g_setWin);
    g_work.thread = CreateThread(nullptr, 0, Opt_Worker, nullptr, 0, nullptr);
    Opt_Queue(L"engine", L"");
    // First run (or no tray icon to come back to): show the window, but never take focus from
    // what the owner is doing, and stay hidden while a game or presentation is up.
    const bool firstRun = Wh_GetIntValue(L"shownFirst", 0) == 0;
    QUERY_USER_NOTIFICATION_STATE quns = QUNS_ACCEPTS_NOTIFICATIONS;
    SHQueryUserNotificationState(&quns);
    if ((firstRun || !g_opt.trayOn) && quns == QUNS_ACCEPTS_NOTIFICATIONS) {
        if (firstRun) Wh_SetIntValue(L"shownFirst", 1);
        ShowWindow(hwnd, SW_SHOWNOACTIVATE);
    } else {
        KillTimer(hwnd, kSetTimerId);
        g_setWin->timer = false;
    }
    g_modStartupOk = true;
    SetEvent(g_modReady);
    MSG msg;
    while (GetMessageW(&msg, nullptr, 0, 0) > 0) {
        TranslateMessage(&msg);
        DispatchMessageW(&msg);
    }
    Opt_StopWorker();
    if (g_settingsWnd && IsWindow(g_settingsWnd)) DestroyWindow(g_settingsWnd);
    g_settingsWnd = nullptr;
    // Results still in the queue carry heap payloads.
    while (PeekMessageW(&msg, nullptr, WM_HUB_ACTION, WM_HUB_FEED, PM_REMOVE)) {
        if (msg.message == WM_HUB_RESULT) delete (OptOut*)msg.lParam;
        else if (msg.message == WM_HUB_FEED) delete (OptFeed*)msg.lParam;
        else if (msg.message == WM_HUB_ACTION) delete (std::wstring*)msg.lParam;
    }
    g_setWin.reset();
    UnregisterClassW(kSettingsClass, (HINSTANCE)&__ImageBase);
    CoUninitialize();
    return 0;
}

// Windhawk's own install box says "failed" when the first copy hands over to an elevated one;
// this closes that box in this process only, for a few seconds after the handover.
static DWORD WINAPI Hub_CloseFalseFailure(void*) {
    const DWORD pid = GetCurrentProcessId();
    for (int i = 0; i < 60 && g_closeFalseFailure.load(); i++) {
        if (!EnumWindows([](HWND hwnd, LPARAM lp) -> BOOL {
            DWORD owner = 0;
            GetWindowThreadProcessId(hwnd, &owner);
            if (owner != (DWORD)lp) return TRUE;
            WCHAR cls[16]{}, title[32]{};
            GetClassNameW(hwnd, cls, 16);
            GetWindowTextW(hwnd, title, 32);
            if (wcscmp(cls, L"#32770") == 0 && wcscmp(title, L"Windhawk") == 0) {
                PostMessageW(hwnd, WM_CLOSE, 0, 0);
                return FALSE;
            }
            return TRUE;
        }, (LPARAM)pid)) return 0;
        if (i < 59 && g_closeFalseFailure.load()) Sleep(250);
    }
    return 0;
}

static void Hub_JoinFalseFailure() {
    if (g_falseFailureThread) {
        WaitForSingleObject(g_falseFailureThread, INFINITE);
        CloseHandle(g_falseFailureThread);
        g_falseFailureThread = nullptr;
    }
}

BOOL WhTool_ModInit() {
    // Cleaning system folders and changing Windows settings needs admin rights, so the tool
    // process hands over to an elevated copy of itself once.
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
        Wh_Log(L"Seamless Windows Optimizer needs admin rights and Windows did not give them.");
        return FALSE;
    }
    g_closeFalseFailure = true;
    g_falseFailureThread = CreateThread(nullptr, 0, Hub_CloseFalseFailure, nullptr, 0, nullptr);
    g_modMutex = CreateMutexW(nullptr, FALSE, L"Local\\SeamlessWindowsOptimizer.Instance");
    if (!g_modMutex) {
        Hub_JoinFalseFailure();
        return FALSE;
    }
    if (GetLastError() == ERROR_ALREADY_EXISTS) {
        CloseHandle(g_modMutex);
        g_modMutex = nullptr;
        Wh_Log(L"Another copy of Seamless Windows Optimizer is already running.");
        Hub_JoinFalseFailure();
        return FALSE;
    }
    g_modReady = CreateEventW(nullptr, TRUE, FALSE, nullptr);
    if (!g_modReady) {
        CloseHandle(g_modMutex);
        g_modMutex = nullptr;
        Hub_JoinFalseFailure();
        return FALSE;
    }
    g_modThread = CreateThread(nullptr, 0, Hub_ModThread, nullptr, 0, &g_modThreadId);
    if (!g_modThread) {
        CloseHandle(g_modReady);
        g_modReady = nullptr;
        CloseHandle(g_modMutex);
        g_modMutex = nullptr;
        Hub_JoinFalseFailure();
        return FALSE;
    }
    DWORD ready = WaitForSingleObject(g_modReady, 10000);
    if (ready == WAIT_OBJECT_0 && !g_modStartupOk) {
        WaitForSingleObject(g_modThread, INFINITE);
        CloseHandle(g_modThread);
        g_modThread = nullptr;
        CloseHandle(g_modReady);
        g_modReady = nullptr;
        CloseHandle(g_modMutex);
        g_modMutex = nullptr;
        Hub_JoinFalseFailure();
        return FALSE;
    }
    return TRUE;
}

void WhTool_ModSettingsChanged() {
    Hub_WriteMotion();
    if (HWND hwnd = g_settingsWnd) {
        PostMessageW(hwnd, WM_APP_SETTINGS_RELOAD, 0, 0);
        PostMessageW(hwnd, WM_HUB_MODCHANGED, 0, 0);
    }
}

void WhTool_ModUninit() {
    g_opt.quitting = true;
    g_work.halt = true;
    g_closeFalseFailure = false;
    Hub_JoinFalseFailure();
    if (g_modThread) {
        if (HWND hwnd = g_settingsWnd) PostMessageW(hwnd, WM_CLOSE, 0, 0);
        // A destroyed window leaves the thread waiting in GetMessage, so it is told to quit too.
        while (WaitForSingleObject(g_modThread, 0) == WAIT_TIMEOUT) {
            if (PostThreadMessageW(g_modThreadId, WM_QUIT, 0, 0)) break;
            Sleep(10);
        }
        WaitForSingleObject(g_modThread, INFINITE);
        CloseHandle(g_modThread);
        g_modThread = nullptr;
    }
    if (g_modReady) { CloseHandle(g_modReady); g_modReady = nullptr; }
    if (g_modMutex) { CloseHandle(g_modMutex); g_modMutex = nullptr; }
}
