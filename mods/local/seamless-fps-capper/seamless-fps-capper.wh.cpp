// ==WindhawkMod==
// @id              seamless-fps-capper
// @name            Seamless FPS Capper
// @description     An open frame rate cap for every game: in the game itself or through the NVIDIA driver, with per-game caps, a tray switch and shortcuts
// @version         1.0.1
// @author          DavidHiFi
// @github          https://github.com/DavidHiFi
// @homepage        https://github.com/DavidHiFi/davids-windhawk-mods
// @include         windhawk.exe
// @include         windhawk-mod.exe
// @include         windhawk-mod-elevated.exe
// @compilerOptions -lgdi32 -luser32 -lshell32 -lshlwapi -lole32 -loleaut32 -luuid -ld2d1 -ldwrite -lwindowscodecs -ldwmapi -lcomctl32 -luxtheme -lcomdlg32 -limm32 -ladvapi32 -lurlmon -lwininet
// @license         GPL-3.0
// @donateUrl       https://ko-fi.com/DavidHiFi
// ==/WindhawkMod==

// Source code is published under The GNU General Public License v3.0.
//
// For bug reports and feature requests, please open an issue here:
// https://github.com/DavidHiFi/davids-windhawk-mods/issues

// ==WindhawkModReadme==
/*
# Seamless FPS Capper

Caps the frame rate of your games, the job RivaTuner does, as a Windhawk mod.
One cap for every game, or a cap of its own for each game, with a tray switch
and keyboard shortcuts.

![Seamless FPS Capper settings](https://raw.githubusercontent.com/DavidHiFi/davids-windhawk-mods/main/media/previews/seamless-fps-capper.png)

## Two ways to cap

- **Driver cap.** The NVIDIA driver holds the frame rate. It works in every
  game, anti-cheat games too, because nothing is loaded into the game. It
  takes effect the next time the game starts. Needs an NVIDIA card.
- **In-game cap.** The mod loads into the games you list and waits between
  frames itself, like RivaTuner. It works on any graphics card and changes
  at once, so the tray switch and shortcuts apply mid-game. Pick how it waits:
  smooth (async), front edge sync, back edge sync, or NVIDIA Reflex (falls
  back to smooth where Reflex is missing).

The in-game cap covers DirectX 9, 10, 11 and 12, OpenGL and Vulkan, in 32-bit
and 64-bit games.

## Anti-cheat games

The mod never loads into Plutonium or games with anti-cheat (Easy Anti-Cheat,
BattlEye, Vanguard, Ricochet, FACEIT and others), even when a folder you list
holds them. Those games always get the driver cap.

## How to use

1. Right-click the tray icon and open **Settings**.
2. On **Frame cap**, set one cap for every game and how it caps.
3. On **Games**, give a game its own cap and way, or list folders where every
   game gets the in-game cap.
4. Save. Click the tray icon, or press the shortcut, to turn the in-game cap
   on or off.

Turning the mod off or removing it puts every driver value it changed back
exactly as it was.

## What's new

- 1.0.1: the game list now saves on Windhawk 1.7 too. A new install leaves the
  NVIDIA driver cap alone until you turn it on.
- 1.0.0: first release.

## Credits

Original work by DavidHiFi, released under GPL-3.0. Frame pacing ideas from
RivaTuner Statistics Server and Special K. NVIDIA driver settings through
NVAPI. Colours from Catppuccin Mocha (https://github.com/catppuccin/catppuccin).
*/
// ==/WindhawkModReadme==

// ==WindhawkModSettings==
/*
- capEnabled: true
  $name: "Cap frame rates"
  $description: "Off, nothing is capped: in-game caps stop and the driver caps this mod manages go to none."
- fps: "157"
  $name: "Frame rate cap"
  $description: "Frames per second for every game without its own cap. In game, decimals work, like 141.5. The driver cap rounds to a whole number."
- mode: "async"
  $name: "How it caps"
  $description: "Driver works in every game, anti-cheat ones too, from the next time the game starts. The in-game ways cap only the games on the Games page."
  $options:
  - driver: "Driver cap (NVIDIA, every game)"
  - async: "In game, smooth (async)"
  - front: "In game, front edge sync"
  - back: "In game, back edge sync"
  - reflex: "In game, NVIDIA Reflex"
- bgFps: 0
  $name: "Background cap"
  $description: "Frames per second while the game is not the window in front. 0 is off."
- waitMode: "passive"
  $name: "Waiting between frames"
  $description: "Passive lets the processor rest between frames. Busy spins for the steadiest frame times and keeps one core busy."
  $options:
  - passive: "Passive (light)"
  - busy: "Busy (steadiest)"
- lowLatency: "leave"
  $name: "Driver low latency"
  $description: "NVIDIA Low Latency Mode for every game. Leave keeps what the NVIDIA app or control panel set."
  $options:
  - leave: "Leave as it is"
  - off: "Off"
  - on: "On"
  - ultra: "Ultra"
- driverCap: false
  $name: "Let this mod set the NVIDIA driver cap"
  $description: "Off puts every driver value this mod changed back exactly as it was, and the driver cap is left alone."
- gameFolders: ""
  $name: "Cap every game in these folders"
  $description: "Folders separated by ;, like D:\\Games;E:\\SteamLibrary. Every game under them gets the in-game cap and way from the Frame cap page. Anti-cheat games are skipped."
- game1Exe: "plutonium-bootstrapper-win32.exe"
  $name: "Game"
  $description: "The game's exe name, like game.exe. Empty frees this slot."
- game1On: true
  $name: "Cap this game"
  $description: "Off, this game is left alone."
- game1Fps: "120"
  $name: "Frame rate cap"
  $description: "Empty uses the cap on the Frame cap page."
- game1Mode: "driver"
  $name: "How it caps"
  $description: "Anti-cheat games always use the driver cap."
  $options:
  - global: "Same as the Frame cap page"
  - driver: "Driver cap (NVIDIA, every game)"
  - async: "In game, smooth (async)"
  - front: "In game, front edge sync"
  - back: "In game, back edge sync"
  - reflex: "In game, NVIDIA Reflex"
- game1Bg: ""
  $name: "Background cap"
  $description: "Empty uses the Frame cap page. 0 is off."
- game2Exe: ""
  $name: "Game"
  $description: "The game's exe name, like game.exe. Empty frees this slot."
- game2On: true
  $name: "Cap this game"
  $description: "Off, this game is left alone."
- game2Fps: ""
  $name: "Frame rate cap"
  $description: "Empty uses the cap on the Frame cap page."
- game2Mode: "global"
  $name: "How it caps"
  $description: "Anti-cheat games always use the driver cap."
  $options:
  - global: "Same as the Frame cap page"
  - driver: "Driver cap (NVIDIA, every game)"
  - async: "In game, smooth (async)"
  - front: "In game, front edge sync"
  - back: "In game, back edge sync"
  - reflex: "In game, NVIDIA Reflex"
- game2Bg: ""
  $name: "Background cap"
  $description: "Empty uses the Frame cap page. 0 is off."
- game3Exe: ""
  $name: "Game"
  $description: "The game's exe name, like game.exe. Empty frees this slot."
- game3On: true
  $name: "Cap this game"
  $description: "Off, this game is left alone."
- game3Fps: ""
  $name: "Frame rate cap"
  $description: "Empty uses the cap on the Frame cap page."
- game3Mode: "global"
  $name: "How it caps"
  $description: "Anti-cheat games always use the driver cap."
  $options:
  - global: "Same as the Frame cap page"
  - driver: "Driver cap (NVIDIA, every game)"
  - async: "In game, smooth (async)"
  - front: "In game, front edge sync"
  - back: "In game, back edge sync"
  - reflex: "In game, NVIDIA Reflex"
- game3Bg: ""
  $name: "Background cap"
  $description: "Empty uses the Frame cap page. 0 is off."
- game4Exe: ""
  $name: "Game"
  $description: "The game's exe name, like game.exe. Empty frees this slot."
- game4On: true
  $name: "Cap this game"
  $description: "Off, this game is left alone."
- game4Fps: ""
  $name: "Frame rate cap"
  $description: "Empty uses the cap on the Frame cap page."
- game4Mode: "global"
  $name: "How it caps"
  $description: "Anti-cheat games always use the driver cap."
  $options:
  - global: "Same as the Frame cap page"
  - driver: "Driver cap (NVIDIA, every game)"
  - async: "In game, smooth (async)"
  - front: "In game, front edge sync"
  - back: "In game, back edge sync"
  - reflex: "In game, NVIDIA Reflex"
- game4Bg: ""
  $name: "Background cap"
  $description: "Empty uses the Frame cap page. 0 is off."
- game5Exe: ""
  $name: "Game"
  $description: "The game's exe name, like game.exe. Empty frees this slot."
- game5On: true
  $name: "Cap this game"
  $description: "Off, this game is left alone."
- game5Fps: ""
  $name: "Frame rate cap"
  $description: "Empty uses the cap on the Frame cap page."
- game5Mode: "global"
  $name: "How it caps"
  $description: "Anti-cheat games always use the driver cap."
  $options:
  - global: "Same as the Frame cap page"
  - driver: "Driver cap (NVIDIA, every game)"
  - async: "In game, smooth (async)"
  - front: "In game, front edge sync"
  - back: "In game, back edge sync"
  - reflex: "In game, NVIDIA Reflex"
- game5Bg: ""
  $name: "Background cap"
  $description: "Empty uses the Frame cap page. 0 is off."
- game6Exe: ""
  $name: "Game"
  $description: "The game's exe name, like game.exe. Empty frees this slot."
- game6On: true
  $name: "Cap this game"
  $description: "Off, this game is left alone."
- game6Fps: ""
  $name: "Frame rate cap"
  $description: "Empty uses the cap on the Frame cap page."
- game6Mode: "global"
  $name: "How it caps"
  $description: "Anti-cheat games always use the driver cap."
  $options:
  - global: "Same as the Frame cap page"
  - driver: "Driver cap (NVIDIA, every game)"
  - async: "In game, smooth (async)"
  - front: "In game, front edge sync"
  - back: "In game, back edge sync"
  - reflex: "In game, NVIDIA Reflex"
- game6Bg: ""
  $name: "Background cap"
  $description: "Empty uses the Frame cap page. 0 is off."
- game7Exe: ""
  $name: "Game"
  $description: "The game's exe name, like game.exe. Empty frees this slot."
- game7On: true
  $name: "Cap this game"
  $description: "Off, this game is left alone."
- game7Fps: ""
  $name: "Frame rate cap"
  $description: "Empty uses the cap on the Frame cap page."
- game7Mode: "global"
  $name: "How it caps"
  $description: "Anti-cheat games always use the driver cap."
  $options:
  - global: "Same as the Frame cap page"
  - driver: "Driver cap (NVIDIA, every game)"
  - async: "In game, smooth (async)"
  - front: "In game, front edge sync"
  - back: "In game, back edge sync"
  - reflex: "In game, NVIDIA Reflex"
- game7Bg: ""
  $name: "Background cap"
  $description: "Empty uses the Frame cap page. 0 is off."
- game8Exe: ""
  $name: "Game"
  $description: "The game's exe name, like game.exe. Empty frees this slot."
- game8On: true
  $name: "Cap this game"
  $description: "Off, this game is left alone."
- game8Fps: ""
  $name: "Frame rate cap"
  $description: "Empty uses the cap on the Frame cap page."
- game8Mode: "global"
  $name: "How it caps"
  $description: "Anti-cheat games always use the driver cap."
  $options:
  - global: "Same as the Frame cap page"
  - driver: "Driver cap (NVIDIA, every game)"
  - async: "In game, smooth (async)"
  - front: "In game, front edge sync"
  - back: "In game, back edge sync"
  - reflex: "In game, NVIDIA Reflex"
- game8Bg: ""
  $name: "Background cap"
  $description: "Empty uses the Frame cap page. 0 is off."
- toggleHotkey: "Ctrl+Alt+Shift+/"
  $name: "Turn the in-game cap on or off"
  $description: "Press the keys in the box. Backspace clears it. It starts as MSI Afterburner's limiter key. The tray icon does the same."
- capUpHotkey: ""
  $name: "Raise the cap"
  $description: "Adds the step below to the in-game cap until Windhawk restarts or you save new settings."
- capDownHotkey: ""
  $name: "Lower the cap"
  $description: "Takes the step below off the in-game cap."
- capStep: 5
  $name: "Step (frames per second)"
  $description: "How much one press of raise or lower changes the cap."
- cycleHotkey: ""
  $name: "Next preset cap"
  $description: "Moves the in-game cap to the next frame rate in the list below."
- presetCaps: "60, 120, 144, 157"
  $name: "Preset caps"
  $description: "Frame rates separated by commas."
- settingsGlass: true
  $name: "Blurred settings window"
  $description: "On, the settings window is see-through glass with Windows acrylic behind it. Off, it is solid. Applies when you save."
- nativeSettingsTitleBar: false
  $name: "Native Windows title bar"
  $description: "Use the Windows title bar and window buttons for this settings window. Applies when you save."
- settingsTrayIcon: true
  $name: "Tray icon"
  $description: "Click it to turn the in-game cap on or off. Right-click it for these settings. When off, change settings in Windhawk."
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
#include <d2d1effects.h>
#include <d2d1helper.h>
#include <dwrite.h>
#include <wincodec.h>

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
#include <set>
#include <string>
#include <vector>

#include <d3d9.h>
#include <d3d11.h>
#include <d3d12.h>
#include <dxgi1_4.h>
#include <sddl.h>
#include <tlhelp32.h>

#include <windhawk_tool_mod.h>

namespace acset {
void OpenSettingsWindow();
void CloseSettingsWindow();
int ShowTrayMenu(HWND owner, const POINT* at, bool on, PCWSTR hotkey);
extern std::atomic<HWND> g_settingsWnd;
}  // namespace acset

void WhTool_ModUninit();

// ---------------------------------------------------------------------------
// Shortcuts: "Ctrl+Alt+K" text, the same the settings window's key box writes.
// ---------------------------------------------------------------------------

static std::wstring Trim(const std::wstring& s) {
    size_t a = s.find_first_not_of(L" \t\r\n");
    if (a == std::wstring::npos) return {};
    return s.substr(a, s.find_last_not_of(L" \t\r\n") - a + 1);
}

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

namespace {

std::atomic<bool> g_stop{false};

// ---------------------------------------------------------------------------
// Settings, read the same way in games and in the tool.
// ---------------------------------------------------------------------------

constexpr int kSlots = 8;
enum : int { kModeNone = 0, kModeAsync = 1, kModeFront = 2, kModeBack = 3, kModeReflex = 4, kModeDriver = 5 };
enum : int { kApiNone = 0, kApiDxgi = 1, kApiD3d9 = 2, kApiGl = 3, kApiVulkan = 4 };

std::wstring Lower(std::wstring s) {
    for (auto& c : s) c = (wchar_t)towlower(c);
    return s;
}

std::wstring BaseName(const std::wstring& path) {
    size_t p = path.find_last_of(L"\\/");
    return p == std::wstring::npos ? path : path.substr(p + 1);
}

std::wstring SettingText(PCWSTR name, int n = 0) {
    PCWSTR v = Wh_GetStringSetting(name, n);
    std::wstring s = v ? v : L"";
    if (v) Wh_FreeStringSetting(v);
    return Trim(s);
}

// Empty or not a number gives def. Caps run 0 to 1000; 0 or less is off.
double ParseFps(const std::wstring& s, double def) {
    if (s.empty()) return def;
    wchar_t* end = nullptr;
    double v = wcstod(s.c_str(), &end);
    if (end == s.c_str()) return def;
    if (!(v > 0)) return 0;
    return std::min(v, 1000.0);
}

int ModeFromText(const std::wstring& s) {
    if (s == L"driver") return kModeDriver;
    if (s == L"async") return kModeAsync;
    if (s == L"front") return kModeFront;
    if (s == L"back") return kModeBack;
    if (s == L"reflex") return kModeReflex;
    if (s == L"global") return kModeNone;
    return -1;
}

PCWSTR ModeName(int m) {
    switch (m) {
        case kModeAsync: return L"in game, smooth";
        case kModeFront: return L"in game, front edge sync";
        case kModeBack: return L"in game, back edge sync";
        case kModeReflex: return L"in game, NVIDIA Reflex";
        case kModeDriver: return L"driver";
    }
    return L"off";
}

// Games the mod never loads into: Plutonium (its anti-cheat checks loaded
// code) and games with kernel anti-cheat. They always get the driver cap.
const PCWSTR kNeverInject[] = {
    L"plutonium-bootstrapper-win32.exe", L"plutonium.exe", L"plutonium-launcher-win32.exe", L"t6zm.exe", L"t6mp.exe",
    L"valorant-win64-shipping.exe", L"valorant.exe", L"leagueclient.exe", L"league of legends.exe",
    L"fortniteclient-win64-shipping.exe", L"r5apex.exe", L"r5apex_dx12.exe", L"cod.exe", L"cod26-cod.exe",
    L"sp26-cod.exe", L"blackopscoldwar.exe", L"modernwarfare.exe", L"cod24-cod.exe", L"cod23-cod.exe",
    L"rainbowsix.exe", L"rainbowsix_be.exe", L"tslgame.exe", L"destiny2.exe", L"eldenring.exe",
    L"deadbydaylight-win64-shipping.exe", L"rustclient.exe", L"escapefromtarkov.exe", L"thefinals.exe",
    L"marvel-win64-shipping.exe", L"delta force.exe", L"start_protected_game.exe", L"easyanticheat_eos.exe",
    L"beservice.exe", L"vgc.exe", L"faceit.exe", L"gta5.exe", L"gta5_enhanced.exe", L"rdr2.exe",
};

bool NeverInject(const std::wstring& exeLower) {
    for (PCWSTR n : kNeverInject)
        if (exeLower == n) return true;
    return false;
}

bool PathExists(const std::wstring& p) {
    return GetFileAttributesW(p.c_str()) != INVALID_FILE_ATTRIBUTES;
}

// Anti-cheat files next to the game, or up to two folders above it (Unreal
// games keep the exe in Binaries\Win64).
bool HasAntiCheatFiles(const std::wstring& exePath) {
    std::wstring dir = exePath;
    for (int up = 0; up < 3; up++) {
        size_t p = dir.find_last_of(L"\\/");
        if (p == std::wstring::npos) break;
        dir = dir.substr(0, p);
        for (PCWSTR f : {L"\\EasyAntiCheat", L"\\BattlEye", L"\\EasyAntiCheat_EOS_Setup.exe",
                         L"\\start_protected_game.exe", L"\\BEService_x64.exe", L"\\vgc.exe"})
            if (PathExists(dir + f)) return true;
    }
    return false;
}

struct GameEntry {
    std::wstring exe;  // lower case, empty = free slot
    bool on = false;
    double fps = -1;  // -1 = the Frame cap page
    int mode = kModeNone;  // kModeNone = the Frame cap page
    double bg = -1;
};

struct Config {
    bool configured = false;
    bool enabled = true;
    double fps = 0;
    int mode = kModeDriver;
    double bg = 0;
    bool busy = false;
    int lowLatency = 0;  // 0 leave, 1 off, 2 on, 3 ultra
    GameEntry games[kSlots];
    std::wstring toggleKey, upKey, downKey, cycleKey;
    double step = 5;
    std::vector<double> presets;
    bool tray = true;
    bool driver = true;  // off: every driver value this mod changed goes back
    std::vector<std::wstring> folders;  // lower case, no trailing slash
};

// True when exePath (lower case) sits anywhere under one of the folders.
bool InFolders(const Config& c, const std::wstring& exePathLower) {
    for (const auto& f : c.folders)
        if (exePathLower.size() > f.size() + 1 && exePathLower.compare(0, f.size(), f) == 0 &&
            exePathLower[f.size()] == L'\\')
            return true;
    return false;
}

Config ReadConfig() {
    Config c;
    std::wstring mode = SettingText(L"mode");
    c.configured = !mode.empty();
    c.mode = ModeFromText(mode);
    if (c.mode <= 0) c.mode = kModeAsync;
    c.enabled = Wh_GetIntSetting(L"capEnabled") != 0;
    c.fps = ParseFps(SettingText(L"fps"), 0);
    c.bg = std::clamp(Wh_GetIntSetting(L"bgFps"), 0, 1000);
    c.busy = SettingText(L"waitMode") == L"busy";
    std::wstring ll = SettingText(L"lowLatency");
    c.lowLatency = ll == L"off" ? 1 : ll == L"on" ? 2 : ll == L"ultra" ? 3 : 0;
    for (int n = 1; n <= kSlots; n++) {
        GameEntry& g = c.games[n - 1];
        g.exe = Lower(BaseName(SettingText(L"game%dExe", n)));
        g.on = Wh_GetIntSetting(L"game%dOn", n) != 0;
        g.fps = ParseFps(SettingText(L"game%dFps", n), -1);
        g.mode = std::max(ModeFromText(SettingText(L"game%dMode", n)), (int)kModeNone);
        g.bg = ParseFps(SettingText(L"game%dBg", n), -1);
    }
    c.toggleKey = SettingText(L"toggleHotkey");
    c.upKey = SettingText(L"capUpHotkey");
    c.downKey = SettingText(L"capDownHotkey");
    c.cycleKey = SettingText(L"cycleHotkey");
    c.step = std::clamp(Wh_GetIntSetting(L"capStep"), 1, 100);
    std::wstring presets = SettingText(L"presetCaps");
    size_t start = 0;
    while (start <= presets.size()) {
        size_t comma = presets.find(L',', start);
        if (comma == std::wstring::npos) comma = presets.size();
        double v = ParseFps(Trim(presets.substr(start, comma - start)), 0);
        if (v > 0) c.presets.push_back(v);
        start = comma + 1;
    }
    std::sort(c.presets.begin(), c.presets.end());
    c.tray = Wh_GetIntSetting(L"settingsTrayIcon") != 0;
    c.driver = Wh_GetIntSetting(L"driverCap") != 0;
    std::wstring folders = SettingText(L"gameFolders");
    start = 0;
    while (start <= folders.size()) {
        size_t semi = folders.find(L';', start);
        if (semi == std::wstring::npos) semi = folders.size();
        std::wstring f = Lower(Trim(folders.substr(start, semi - start)));
        for (auto& ch : f)
            if (ch == L'/') ch = L'\\';
        while (!f.empty() && f.back() == L'\\') f.pop_back();
        if (f.size() >= 3) c.folders.push_back(f);  // at least "c:\x"
        start = semi + 1;
    }
    return c;
}

int FindSlot(const Config& c, const std::wstring& exeLower) {
    for (int i = 0; i < kSlots; i++)
        if (!c.games[i].exe.empty() && c.games[i].exe == exeLower) return i;
    return -1;
}

int EffectiveMode(const Config& c, int slot) {
    const GameEntry& g = c.games[slot];
    if (NeverInject(g.exe)) return kModeDriver;
    return g.mode == kModeNone ? c.mode : g.mode;
}
double EffectiveFps(const Config& c, int slot) {
    return c.games[slot].fps < 0 ? c.fps : c.games[slot].fps;
}
double EffectiveBg(const Config& c, int slot) {
    return c.games[slot].bg < 0 ? c.bg : c.games[slot].bg;
}

// ---------------------------------------------------------------------------
// Shared state: Local\SeamlessFpsCapper.state. Read by the FPS overlay too.
// Header of 8 LONGs, then 16 game slots of 40 bytes.
// ---------------------------------------------------------------------------

constexpr LONG kStateMagic = 0x43504653;  // "SFPC"
constexpr int kStateSlots = 16;
struct CapSlot {
    volatile LONG pid, capX100, mode, enabled, api, pad;
    volatile LONG64 lastPresentQpc, frames;
};
struct CapState {
    volatile LONG magic, version, toolDisabled, capOverrideX100, generation, toolPid, reserved[2];
    CapSlot slots[kStateSlots];
};
static_assert(sizeof(CapSlot) == 40, "slot layout");
static_assert(sizeof(CapState) == 672, "state layout");

HANDLE g_stateMap = nullptr;
CapState* g_state = nullptr;

bool OpenState() {
    if (g_state) return true;
    PSECURITY_DESCRIPTOR sd = nullptr;
    // Everyone and app containers may read and write; low integrity too.
    ConvertStringSecurityDescriptorToSecurityDescriptorW(L"D:(A;;GA;;;WD)(A;;GA;;;AC)S:(ML;;NW;;;LW)",
                                                         SDDL_REVISION_1, &sd, nullptr);
    SECURITY_ATTRIBUTES sa{sizeof(sa), sd, FALSE};
    g_stateMap = CreateFileMappingW(INVALID_HANDLE_VALUE, sd ? &sa : nullptr, PAGE_READWRITE, 0, sizeof(CapState),
                                    L"Local\\SeamlessFpsCapper.state");
    if (sd) LocalFree(sd);
    if (!g_stateMap)
        g_stateMap = OpenFileMappingW(FILE_MAP_READ | FILE_MAP_WRITE, FALSE, L"Local\\SeamlessFpsCapper.state");
    if (!g_stateMap) {
        Wh_Log(L"Shared state: no mapping, error %lu", GetLastError());
        return false;
    }
    g_state = (CapState*)MapViewOfFile(g_stateMap, FILE_MAP_READ | FILE_MAP_WRITE, 0, 0, sizeof(CapState));
    if (!g_state) {
        CloseHandle(g_stateMap);
        g_stateMap = nullptr;
        return false;
    }
    if (InterlockedCompareExchange(&g_state->magic, kStateMagic, 0) == 0) g_state->version = 1;
    return true;
}

void CloseState() {
    if (g_state) UnmapViewOfFile(g_state);
    if (g_stateMap) CloseHandle(g_stateMap);
    g_state = nullptr;
    g_stateMap = nullptr;
}

bool PidAlive(DWORD pid) {
    HANDLE h = OpenProcess(SYNCHRONIZE, FALSE, pid);
    if (!h) return GetLastError() == ERROR_ACCESS_DENIED;
    bool alive = WaitForSingleObject(h, 0) == WAIT_TIMEOUT;
    CloseHandle(h);
    return alive;
}

LONG64 Qpc() {
    LARGE_INTEGER t;
    QueryPerformanceCounter(&t);
    return t.QuadPart;
}
LONG64 QpcFreq() {
    static LONG64 f = [] {
        LARGE_INTEGER q;
        QueryPerformanceFrequency(&q);
        return q.QuadPart;
    }();
    return f;
}

// ---------------------------------------------------------------------------
// NVAPI, loaded by name (no import library).
// ---------------------------------------------------------------------------

typedef unsigned int NvU32;
typedef unsigned short NvU16;
typedef unsigned char NvU8;
typedef int NvAPI_Status;
typedef void* NvDRSSessionHandle;
typedef void* NvDRSProfileHandle;
typedef NvU16 NvAPI_UnicodeString[2048];
#define CAP_NV_VER(t, v) ((NvU32)(sizeof(t) | ((v) << 16)))

struct NV_SET_SLEEP_MODE_PARAMS {
    NvU32 version;
    NvU8 bLowLatencyMode;
    NvU8 bLowLatencyBoost;
    NvU32 minimumIntervalUs;
    NvU8 rsvd[32];
};

using NvQI_t = void*(__cdecl*)(NvU32);
using NvInit_t = NvAPI_Status(__cdecl*)();
using NvSetSleepMode_t = NvAPI_Status(__cdecl*)(IUnknown*, NV_SET_SLEEP_MODE_PARAMS*);
using NvSleep_t = NvAPI_Status(__cdecl*)(IUnknown*);

NvQI_t NvApiQI() {
    static NvQI_t qi = [] () -> NvQI_t {
#ifdef _WIN64
        HMODULE m = LoadLibraryExW(L"nvapi64.dll", nullptr, LOAD_LIBRARY_SEARCH_SYSTEM32);
#else
        HMODULE m = LoadLibraryExW(L"nvapi.dll", nullptr, LOAD_LIBRARY_SEARCH_SYSTEM32);
#endif
        if (!m) return nullptr;
        auto q = (NvQI_t)GetProcAddress(m, "nvapi_QueryInterface");
        if (!q) return nullptr;
        auto init = (NvInit_t)q(0x0150E828);
        if (!init || init() != 0) return nullptr;
        return q;
    }();
    return qi;
}

}  // namespace

namespace {

// ===========================================================================
// Game side: loaded only into games on the Games page that use an in-game
// mode. Hooks the present calls and waits there so frames come out evenly.
// ===========================================================================

std::atomic<bool> g_inGame{false};
std::atomic<bool> g_unloading{false};
std::atomic<int> g_inFlight{0};
DWORD g_tls = TLS_OUT_OF_INDEXES;
HANDLE g_hookThread = nullptr;
std::wstring g_exeLower;

// Live settings for this game, swapped whole on a settings change.
std::atomic<bool> g_gameOn{false};
std::atomic<double> g_capFg{0}, g_capBg{0};
std::atomic<int> g_gameMode{kModeAsync};
std::atomic<bool> g_busyWait{false};
int g_stateSlot = -1;

struct ThreadData {
    int depth = 0;
    HANDLE timer = nullptr;
};
std::mutex g_threadsLock;
std::vector<ThreadData*> g_threads;

ThreadData* Td() {
    if (g_tls == TLS_OUT_OF_INDEXES) return nullptr;
    auto* t = (ThreadData*)TlsGetValue(g_tls);
    if (!t) {
        t = new (std::nothrow) ThreadData();
        if (!t) return nullptr;
        TlsSetValue(g_tls, t);
        std::lock_guard<std::mutex> lock(g_threadsLock);
        g_threads.push_back(t);
    }
    return t;
}

bool IsForeground() {
    static std::atomic<ULONGLONG> lastCheck{0};
    static std::atomic<bool> lastResult{true};
    ULONGLONG now = GetTickCount64();
    if (now - lastCheck.load(std::memory_order_relaxed) < 100) return lastResult.load(std::memory_order_relaxed);
    DWORD pid = 0;
    if (HWND fg = GetForegroundWindow()) GetWindowThreadProcessId(fg, &pid);
    bool r = pid == GetCurrentProcessId();
    lastResult.store(r, std::memory_order_relaxed);
    lastCheck.store(now, std::memory_order_relaxed);
    return r;
}

// Frames per second this game should run at right now. 0 = no cap.
double CurrentCap() {
    if (!g_gameOn.load(std::memory_order_relaxed) || g_unloading.load(std::memory_order_relaxed)) return 0;
    if (g_state && g_state->toolDisabled) return 0;
    bool fg = IsForeground();
    if (!fg) {
        double bg = g_capBg.load(std::memory_order_relaxed);
        if (bg > 0) return bg;
    }
    if (g_state) {
        LONG ov = g_state->capOverrideX100;
        if (ov > 0) return ov / 100.0;
    }
    return g_capFg.load(std::memory_order_relaxed);
}

void PublishSlot(double cap, int mode, int api) {
    if (!g_state || g_stateSlot < 0) return;
    CapSlot& s = g_state->slots[g_stateSlot];
    s.capX100 = (LONG)(cap * 100 + 0.5);
    s.mode = mode;
    s.enabled = cap > 0;
    s.api = api;
    s.lastPresentQpc = Qpc();
    InterlockedIncrement64(&s.frames);
}

void ClaimSlot() {
    if (!g_state) return;
    LONG me = (LONG)GetCurrentProcessId();
    for (int pass = 0; pass < 2 && g_stateSlot < 0; pass++) {
        for (int i = 0; i < kStateSlots; i++) {
            LONG pid = g_state->slots[i].pid;
            if (pid == me) {
                g_stateSlot = i;
                break;
            }
            // Second pass: take a slot whose game has quit.
            LONG expect = pass == 0 ? 0 : pid;
            if (pass == 1 && (pid == 0 || PidAlive((DWORD)pid))) continue;
            if (InterlockedCompareExchange(&g_state->slots[i].pid, me, expect) == expect) {
                CapSlot& s = g_state->slots[i];
                s.frames = 0;
                s.lastPresentQpc = 0;
                s.capX100 = 0;
                s.mode = g_gameMode.load();
                s.enabled = 0;
                s.api = 0;
                g_stateSlot = i;
                break;
            }
        }
    }
}

void ReleaseSlot() {
    if (!g_state || g_stateSlot < 0) return;
    CapSlot& s = g_state->slots[g_stateSlot];
    s.enabled = 0;
    s.capX100 = 0;
    InterlockedExchange(&s.pid, 0);
    g_stateSlot = -1;
}

// Waits until the performance counter reaches target. A high resolution
// timer sleeps in slices of up to 2 ms and the last stretch spins. Every slice
// rechecks the cap, so turning it off ends the wait at once, and no wait is
// ever longer than one frame at the cap it started with.
void WaitUntil(LONG64 target, LONG64 interval, double capAtStart) {
    const LONG64 f = QpcFreq();
    LONG64 now = Qpc();
    if (target - now > interval) target = now + interval;
    const bool busy = g_busyWait.load(std::memory_order_relaxed);
    ThreadData* td = Td();
    if (td && !td->timer && !busy) {
        td->timer = CreateWaitableTimerExW(nullptr, nullptr, 0x00000002 /* HIGH_RESOLUTION */, TIMER_ALL_ACCESS);
        if (!td->timer) td->timer = CreateWaitableTimerExW(nullptr, nullptr, 0, TIMER_ALL_ACCESS);
    }
    const LONG64 spin = f / 1000;  // the last millisecond spins
    int checks = 0;
    while ((now = Qpc()) < target) {
        if (CurrentCap() != capAtStart) return;
        LONG64 left = target - now;
        if (!busy && left > spin + f / 4000) {
            LONG64 sleepTicks = std::min(left - spin, f / 500);  // at most 2 ms a slice
            LONG64 hundredNs = sleepTicks * 10000000 / f;
            if (td && td->timer && hundredNs > 0) {
                LARGE_INTEGER due;
                due.QuadPart = -hundredNs;
                if (SetWaitableTimerEx(td->timer, &due, 0, nullptr, nullptr, nullptr, 0))
                    WaitForSingleObject(td->timer, 5);
                else
                    Sleep(1);
            } else {
                Sleep(hundredNs >= 10000 ? 1 : 0);
            }
        } else {
            YieldProcessor();
            // A busy spin still lets the cap switch off: check now and then.
            if (++checks < 64) continue;
            checks = 0;
        }
    }
}

// One main swap chain gets paced. A second one (a launcher overlay, a
// preview window) passes straight through, so two chains never halve the
// frame rate. The main one moves to a bigger chain, or to any chain once the
// main one has not presented for half a second.
struct Pacer {
    SRWLOCK lock = SRWLOCK_INIT;
    void* mainKey = nullptr;
    LONG64 mainArea = 0;
    LONG64 mainLast = 0;
    double cap = 0;
    LONG64 next = 0;    // async: the next frame's time
    LONG64 origin = 0;  // edge sync: the grid start
    LONG64 lastK = 0;
};
Pacer g_pacer;

// Reflex state, for the main chain only.
struct ReflexState {
    IUnknown* device = nullptr;  // held with a reference while Reflex is active
    void* key = nullptr;
    NvU32 intervalUs = 0;
    bool failed = false;
} g_reflex;
std::mutex g_reflexLock;

const GUID kIID_ID3D11Device = {0xdb6f6ddb, 0xac77, 0x4e88, {0x82, 0x53, 0x81, 0x9d, 0xf9, 0xbb, 0xf1, 0x40}};
const GUID kIID_ID3D12Device = {0x189819f1, 0x1db6, 0x4b57, {0xbe, 0x54, 0x18, 0x21, 0x33, 0x9b, 0x85, 0xf7}};
const GUID kIID_ID3D12CommandQueue = {0x0ec870a6, 0x5d7e, 0x4c22, {0x8c, 0xfc, 0x5b, 0xaa, 0xe0, 0x76, 0x16, 0xed}};
const GUID kIID_IDXGIFactory1 = {0x770aae78, 0xf26f, 0x4dba, {0xa8, 0x29, 0x25, 0x3c, 0x83, 0xd1, 0xb3, 0x87}};
const GUID kIID_IDXGIFactory2 = {0x50c83a1c, 0xe072, 0x4c48, {0x87, 0xb0, 0x36, 0x30, 0xfa, 0x36, 0xa6, 0xd0}};
const GUID kIID_IDXGIFactory4 = {0x1bc6ea02, 0xef36, 0x464f, {0xbf, 0x0c, 0x21, 0xca, 0x39, 0xe5, 0x16, 0x8a}};
const GUID kIID_IDXGIAdapter = {0x2411e7e1, 0x12ac, 0x4ccf, {0xbd, 0x14, 0x97, 0x98, 0xe8, 0x53, 0x4d, 0xc0}};
const GUID kIID_IDXGISwapChain = {0x310d36a0, 0xd2e7, 0x4c0a, {0xaa, 0x04, 0x6a, 0x9d, 0x23, 0xb8, 0x88, 0x6a}};

using NvSetSleepModeFn = NvAPI_Status(__cdecl*)(IUnknown*, NV_SET_SLEEP_MODE_PARAMS*);
using NvSleepFn = NvAPI_Status(__cdecl*)(IUnknown*);

bool ReflexSet(IUnknown* dev, NvU32 us) {
    NvQI_t qi = NvApiQI();
    if (!qi) return false;
    auto set = (NvSetSleepModeFn)qi(0xAC1CA9E0);
    if (!set) return false;
    NV_SET_SLEEP_MODE_PARAMS p{};
    p.version = CAP_NV_VER(NV_SET_SLEEP_MODE_PARAMS, 1);
    p.bLowLatencyMode = us ? 1 : 0;
    p.bLowLatencyBoost = 0;
    p.minimumIntervalUs = us;
    return set(dev, &p) == 0;
}

void ReflexRelease() {
    std::lock_guard<std::mutex> lock(g_reflexLock);
    if (g_reflex.device) {
        ReflexSet(g_reflex.device, 0);
        g_reflex.device->Release();
    }
    g_reflex.device = nullptr;
    g_reflex.key = nullptr;
    g_reflex.intervalUs = 0;
}

IUnknown* DeviceOfSwapChain(IUnknown* sc) {
    IDXGISwapChain* chain = (IDXGISwapChain*)sc;
    IUnknown* dev = nullptr;
    if (SUCCEEDED(chain->GetDevice(kIID_ID3D11Device, (void**)&dev)) && dev) return dev;
    IUnknown* queue = nullptr;
    if (SUCCEEDED(chain->GetDevice(kIID_ID3D12CommandQueue, (void**)&queue)) && queue) {
        ((ID3D12CommandQueue*)queue)->GetDevice(kIID_ID3D12Device, (void**)&dev);
        queue->Release();
        return dev;
    }
    return nullptr;
}

// Reflex on this chain's device. False means use the smooth wait instead.
bool ReflexReady(void* key, IUnknown* sc, double cap) {
    if (!sc || !NvApiQI()) return false;
    std::lock_guard<std::mutex> lock(g_reflexLock);
    if (g_reflex.failed && g_reflex.key == key) return false;
    NvU32 us = (NvU32)(1000000.0 / cap + 0.5);
    if (g_reflex.key != key || !g_reflex.device) {
        if (g_reflex.device) {
            ReflexSet(g_reflex.device, 0);
            g_reflex.device->Release();
            g_reflex.device = nullptr;
        }
        g_reflex.key = key;
        g_reflex.failed = false;
        g_reflex.intervalUs = 0;
        g_reflex.device = DeviceOfSwapChain(sc);  // keeps the reference
        if (!g_reflex.device) {
            g_reflex.failed = true;
            Wh_Log(L"Reflex: no D3D11 or D3D12 device behind this swap chain, using the smooth wait");
            return false;
        }
    }
    if (g_reflex.intervalUs != us) {
        if (!ReflexSet(g_reflex.device, us)) {
            g_reflex.failed = true;
            g_reflex.device->Release();
            g_reflex.device = nullptr;
            Wh_Log(L"Reflex: the driver refused sleep mode, using the smooth wait");
            return false;
        }
        g_reflex.intervalUs = us;
        Wh_Log(L"Reflex: frame interval %u us", us);
    }
    return true;
}

void ReflexSleep() {
    NvQI_t qi = NvApiQI();
    if (!qi) return;
    static auto sleep = (NvSleepFn)qi(0x852CD1D2);
    std::lock_guard<std::mutex> lock(g_reflexLock);
    if (sleep && g_reflex.device) sleep(g_reflex.device);
}

enum class Phase { Before, After };

// What a present hook does around the real call.
struct PaceTicket {
    bool paced = false;
    bool reflex = false;
    bool front = false;
    double cap = 0;
    LONG64 interval = 0;
};

PaceTicket PaceBefore(int api, void* key, LONG64 area, IUnknown* dxgiChain) {
    PaceTicket t;
    double cap = CurrentCap();
    int mode = g_gameMode.load(std::memory_order_relaxed);
    LONG64 now = Qpc();
    const LONG64 f = QpcFreq();
    AcquireSRWLockExclusive(&g_pacer.lock);
    bool isMain = false;
    if (!g_pacer.mainKey || g_pacer.mainKey == key || now - g_pacer.mainLast > f / 2 || area > g_pacer.mainArea) {
        if (g_pacer.mainKey != key) {
            g_pacer.next = 0;
            g_pacer.origin = 0;
        }
        g_pacer.mainKey = key;
        g_pacer.mainArea = area;
        g_pacer.mainLast = now;
        isMain = true;
    }
    if (!isMain) {
        ReleaseSRWLockExclusive(&g_pacer.lock);
        return t;
    }
    PublishSlot(cap, mode, api);
    if (cap <= 0) {
        g_pacer.cap = 0;
        ReleaseSRWLockExclusive(&g_pacer.lock);
        if (g_reflex.device) ReflexRelease();
        return t;
    }
    if (cap != g_pacer.cap) {
        g_pacer.cap = cap;
        g_pacer.next = 0;
        g_pacer.origin = 0;
    }
    t.cap = cap;
    t.interval = (LONG64)(f / cap);
    if (mode == kModeReflex) {
        if (api == kApiDxgi && ReflexReady(key, dxgiChain, cap)) {
            ReleaseSRWLockExclusive(&g_pacer.lock);
            t.reflex = true;
            return t;
        }
        // No Reflex here: the smooth wait does the job, and the shared state
        // says so, so the overlay shows the way really in use.
        mode = kModeAsync;
        if (g_state && g_stateSlot >= 0) g_state->slots[g_stateSlot].mode = mode;
    }
    if (g_reflex.device && mode != kModeReflex) {
        ReleaseSRWLockExclusive(&g_pacer.lock);
        ReflexRelease();
        AcquireSRWLockExclusive(&g_pacer.lock);
    }
    if (mode == kModeFront) {
        ReleaseSRWLockExclusive(&g_pacer.lock);
        t.front = true;
        t.paced = true;
        return t;
    }
    LONG64 target;
    if (mode == kModeBack) {
        if (!g_pacer.origin) {
            g_pacer.origin = now;
            g_pacer.lastK = -1;
        }
        LONG64 k = (now - g_pacer.origin + t.interval - 1) / t.interval;
        k = std::max(k, g_pacer.lastK + 1);
        g_pacer.lastK = k;
        target = g_pacer.origin + k * t.interval;
    } else {  // async, and Reflex where Reflex is not possible
        if (!g_pacer.next || now > g_pacer.next + t.interval) g_pacer.next = now;
        target = g_pacer.next;
        g_pacer.next += t.interval;
    }
    ReleaseSRWLockExclusive(&g_pacer.lock);
    WaitUntil(target, t.interval, cap);
    t.paced = true;
    return t;
}

void PaceAfter(const PaceTicket& t) {
    if (t.reflex) {
        ReflexSleep();
        return;
    }
    if (!t.front) return;
    LONG64 now = Qpc();
    AcquireSRWLockExclusive(&g_pacer.lock);
    if (!g_pacer.origin) {
        g_pacer.origin = now;
        g_pacer.lastK = -1;
    }
    LONG64 k = (now - g_pacer.origin + t.interval - 1) / t.interval;
    k = std::max(k, g_pacer.lastK + 1);
    g_pacer.lastK = k;
    LONG64 target = g_pacer.origin + k * t.interval;
    ReleaseSRWLockExclusive(&g_pacer.lock);
    WaitUntil(target, t.interval, t.cap);
}

// Counts a hook call as running, so unloading waits for it to leave.
struct HookScope {
    ThreadData* td;
    bool outer;
    HookScope() {
        g_inFlight.fetch_add(1);
        td = Td();
        outer = td && td->depth == 0 && !g_unloading.load(std::memory_order_relaxed);
        if (td) td->depth++;
    }
    ~HookScope() {
        if (td) td->depth--;
        g_inFlight.fetch_sub(1);
    }
};

LONG64 AreaOfHwnd(HWND hwnd) {
    RECT r{};
    if (!hwnd || !GetClientRect(hwnd, &r)) return 0;
    return (LONG64)(r.right - r.left) * (r.bottom - r.top);
}

LONG64 AreaOfDxgi(IUnknown* sc) {
    DXGI_SWAP_CHAIN_DESC d{};
    if (FAILED(((IDXGISwapChain*)sc)->GetDesc(&d))) return 0;
    return (LONG64)d.BufferDesc.Width * d.BufferDesc.Height;
}

// ---- DXGI ------------------------------------------------------------------
// Several swap chain classes can carry different Present code; each hooked
// address keeps its own original, up to four.
using Present_t = HRESULT(STDMETHODCALLTYPE*)(IDXGISwapChain*, UINT, UINT);
using Present1_t = HRESULT(STDMETHODCALLTYPE*)(IDXGISwapChain1*, UINT, UINT, const DXGI_PRESENT_PARAMETERS*);
constexpr int kMaxVariants = 4;
Present_t g_present[kMaxVariants];
Present1_t g_present1[kMaxVariants];
void* g_presentAt[kMaxVariants];
void* g_present1At[kMaxVariants];

template <int N>
HRESULT STDMETHODCALLTYPE Present_Hook(IDXGISwapChain* sc, UINT sync, UINT flags) {
    HookScope scope;
    if (!scope.outer || (flags & 0x1 /* DXGI_PRESENT_TEST */)) return g_present[N](sc, sync, flags);
    PaceTicket t = PaceBefore(kApiDxgi, sc, AreaOfDxgi(sc), sc);
    HRESULT hr = g_present[N](sc, sync, flags);
    if (t.paced || t.reflex) PaceAfter(t);
    return hr;
}

template <int N>
HRESULT STDMETHODCALLTYPE Present1_Hook(IDXGISwapChain1* sc, UINT sync, UINT flags, const DXGI_PRESENT_PARAMETERS* p) {
    HookScope scope;
    if (!scope.outer || (flags & 0x1)) return g_present1[N](sc, sync, flags, p);
    PaceTicket t = PaceBefore(kApiDxgi, sc, AreaOfDxgi(sc), sc);
    HRESULT hr = g_present1[N](sc, sync, flags, p);
    if (t.paced || t.reflex) PaceAfter(t);
    return hr;
}

void* const kPresentHooks[kMaxVariants] = {(void*)Present_Hook<0>, (void*)Present_Hook<1>, (void*)Present_Hook<2>,
                                           (void*)Present_Hook<3>};
void* const kPresent1Hooks[kMaxVariants] = {(void*)Present1_Hook<0>, (void*)Present1_Hook<1>, (void*)Present1_Hook<2>,
                                            (void*)Present1_Hook<3>};

// Hooks one function address once. Returns false when every variant is used.
bool HookVariant(void* target, void** at, void* const* hooks, void** originals, PCWSTR what) {
    if (!target) return false;
    for (int i = 0; i < kMaxVariants; i++)
        if (at[i] == target) return true;
    for (int i = 0; i < kMaxVariants; i++) {
        if (at[i]) continue;
        if (!Wh_SetFunctionHook(target, hooks[i], &originals[i])) {
            Wh_Log(L"Hook %s at %p failed", what, target);
            return false;
        }
        at[i] = target;
        Wh_Log(L"Hooked %s (%d) at %p", what, i, target);
        return true;
    }
    return false;
}

void HookDxgiChain(IUnknown* sc) {
    void** vt = *(void***)sc;
    HookVariant(vt[8], g_presentAt, kPresentHooks, (void**)g_present, L"DXGI Present");
    IUnknown* sc1 = nullptr;
    const GUID kIID_IDXGISwapChain1 = {0x790a45f7, 0x0d42, 0x4876, {0x98, 0x3a, 0x0a, 0x55, 0xcf, 0xe6, 0xf4, 0xaa}};
    if (SUCCEEDED(sc->QueryInterface(kIID_IDXGISwapChain1, (void**)&sc1)) && sc1) {
        void** vt1 = *(void***)sc1;
        HookVariant(vt1[22], g_present1At, kPresent1Hooks, (void**)g_present1, L"DXGI Present1");
        sc1->Release();
    }
}

HWND MakeDummyWindow() {
    // A plain static control never shown; good enough for a swap chain.
    return CreateWindowExW(WS_EX_TOOLWINDOW | WS_EX_NOACTIVATE, L"STATIC", L"SeamlessFpsCapperProbe", WS_POPUP, 0, 0, 64,
                           64, nullptr, nullptr, nullptr, nullptr);
}

using D3D11CreateDeviceAndSwapChain_t = HRESULT(WINAPI*)(IDXGIAdapter*, D3D_DRIVER_TYPE, HMODULE, UINT,
                                                          const D3D_FEATURE_LEVEL*, UINT, UINT,
                                                          const DXGI_SWAP_CHAIN_DESC*, IDXGISwapChain**,
                                                          ID3D11Device**, D3D_FEATURE_LEVEL*, ID3D11DeviceContext**);
using CreateDXGIFactory1_t = HRESULT(WINAPI*)(REFIID, void**);
using D3D12CreateDevice_t = HRESULT(WINAPI*)(IUnknown*, D3D_FEATURE_LEVEL, REFIID, void**);

bool HookDxgi() {
    HMODULE d3d11 = LoadLibraryExW(L"d3d11.dll", nullptr, LOAD_LIBRARY_SEARCH_SYSTEM32);
    if (!d3d11) return false;
    auto create = (D3D11CreateDeviceAndSwapChain_t)GetProcAddress(d3d11, "D3D11CreateDeviceAndSwapChain");
    if (!create) return false;
    HWND wnd = MakeDummyWindow();
    if (!wnd) return false;
    bool ok = false;
    // The old blit model chain.
    DXGI_SWAP_CHAIN_DESC d{};
    d.BufferDesc.Width = 64;
    d.BufferDesc.Height = 64;
    d.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    d.SampleDesc.Count = 1;
    d.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    d.BufferCount = 1;
    d.OutputWindow = wnd;
    d.Windowed = TRUE;
    d.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
    IDXGISwapChain* sc = nullptr;
    ID3D11Device* dev = nullptr;
    ID3D11DeviceContext* ctx = nullptr;
    HRESULT hr = create(nullptr, D3D_DRIVER_TYPE_WARP, nullptr, 0, nullptr, 0, D3D11_SDK_VERSION, &d, &sc, &dev, nullptr,
                        &ctx);
    if (SUCCEEDED(hr) && sc) {
        HookDxgiChain(sc);
        ok = true;
        // A flip model chain on a second window, made by the same device.
        IDXGIDevice* dxgiDev = nullptr;
        const GUID kIID_IDXGIDevice = {0x54ec77fa, 0x1377, 0x44e6, {0x8c, 0x32, 0x88, 0xfd, 0x5f, 0x44, 0xc8, 0x4c}};
        if (SUCCEEDED(dev->QueryInterface(kIID_IDXGIDevice, (void**)&dxgiDev)) && dxgiDev) {
            IDXGIAdapter* adapter = nullptr;
            if (SUCCEEDED(dxgiDev->GetAdapter(&adapter)) && adapter) {
                IDXGIFactory2* f2 = nullptr;
                if (SUCCEEDED(adapter->GetParent(kIID_IDXGIFactory2, (void**)&f2)) && f2) {
                    HWND wnd2 = MakeDummyWindow();
                    DXGI_SWAP_CHAIN_DESC1 d1{};
                    d1.Width = 64;
                    d1.Height = 64;
                    d1.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
                    d1.SampleDesc.Count = 1;
                    d1.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
                    d1.BufferCount = 2;
                    d1.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
                    IDXGISwapChain1* sc1 = nullptr;
                    if (wnd2 && SUCCEEDED(f2->CreateSwapChainForHwnd(dev, wnd2, &d1, nullptr, nullptr, &sc1)) && sc1) {
                        HookDxgiChain(sc1);
                        sc1->Release();
                    }
                    if (wnd2) DestroyWindow(wnd2);
                    f2->Release();
                }
                adapter->Release();
            }
            dxgiDev->Release();
        }
    } else {
        Wh_Log(L"DXGI probe device failed: 0x%08X", (unsigned)hr);
    }
    if (ctx) ctx->Release();
    if (sc) sc->Release();
    if (dev) dev->Release();
    DestroyWindow(wnd);
    return ok;
}

bool HookD3d12() {
    HMODULE d3d12 = GetModuleHandleW(L"d3d12.dll");
    HMODULE dxgi = LoadLibraryExW(L"dxgi.dll", nullptr, LOAD_LIBRARY_SEARCH_SYSTEM32);
    if (!d3d12 || !dxgi) return false;
    auto createDev = (D3D12CreateDevice_t)GetProcAddress(d3d12, "D3D12CreateDevice");
    auto createFactory = (CreateDXGIFactory1_t)GetProcAddress(dxgi, "CreateDXGIFactory1");
    if (!createDev || !createFactory) return false;
    IDXGIFactory4* f4 = nullptr;
    if (FAILED(createFactory(kIID_IDXGIFactory4, (void**)&f4)) || !f4) return false;
    bool ok = false;
    IDXGIAdapter* warp = nullptr;
    ID3D12Device* dev = nullptr;
    ID3D12CommandQueue* queue = nullptr;
    if (SUCCEEDED(f4->EnumWarpAdapter(kIID_IDXGIAdapter, (void**)&warp)) && warp &&
        SUCCEEDED(createDev(warp, D3D_FEATURE_LEVEL_11_0, kIID_ID3D12Device, (void**)&dev)) && dev) {
        D3D12_COMMAND_QUEUE_DESC qd{};
        qd.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
        if (SUCCEEDED(dev->CreateCommandQueue(&qd, kIID_ID3D12CommandQueue, (void**)&queue)) && queue) {
            HWND wnd = MakeDummyWindow();
            DXGI_SWAP_CHAIN_DESC1 d1{};
            d1.Width = 64;
            d1.Height = 64;
            d1.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
            d1.SampleDesc.Count = 1;
            d1.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
            d1.BufferCount = 2;
            d1.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
            IDXGISwapChain1* sc1 = nullptr;
            if (wnd && SUCCEEDED(f4->CreateSwapChainForHwnd(queue, wnd, &d1, nullptr, nullptr, &sc1)) && sc1) {
                HookDxgiChain(sc1);
                sc1->Release();
                ok = true;
            }
            if (wnd) DestroyWindow(wnd);
        }
    }
    if (queue) queue->Release();
    if (dev) dev->Release();
    if (warp) warp->Release();
    f4->Release();
    return ok;
}

// ---- Direct3D 9 --------------------------------------------------------------
using D9Present_t = HRESULT(STDMETHODCALLTYPE*)(IDirect3DDevice9*, const RECT*, const RECT*, HWND, const RGNDATA*);
using D9PresentEx_t = HRESULT(STDMETHODCALLTYPE*)(IDirect3DDevice9Ex*, const RECT*, const RECT*, HWND, const RGNDATA*,
                                                  DWORD);
using D9ScPresent_t = HRESULT(STDMETHODCALLTYPE*)(IDirect3DSwapChain9*, const RECT*, const RECT*, HWND, const RGNDATA*,
                                                  DWORD);
D9Present_t g_d9Present[kMaxVariants];
D9PresentEx_t g_d9PresentEx[kMaxVariants];
D9ScPresent_t g_d9ScPresent[kMaxVariants];
void* g_d9PresentAt[kMaxVariants];
void* g_d9PresentExAt[kMaxVariants];
void* g_d9ScPresentAt[kMaxVariants];

LONG64 AreaOfD9Device(IDirect3DDevice9* dev, HWND over) {
    if (over) return AreaOfHwnd(over);
    D3DDEVICE_CREATION_PARAMETERS cp{};
    if (SUCCEEDED(dev->GetCreationParameters(&cp))) return AreaOfHwnd(cp.hFocusWindow);
    return 0;
}

template <int N>
HRESULT STDMETHODCALLTYPE D9Present_Hook(IDirect3DDevice9* dev, const RECT* a, const RECT* b, HWND w, const RGNDATA* r) {
    HookScope scope;
    if (!scope.outer) return g_d9Present[N](dev, a, b, w, r);
    PaceTicket t = PaceBefore(kApiD3d9, dev, AreaOfD9Device(dev, w), nullptr);
    HRESULT hr = g_d9Present[N](dev, a, b, w, r);
    if (t.paced) PaceAfter(t);
    return hr;
}
template <int N>
HRESULT STDMETHODCALLTYPE D9PresentEx_Hook(IDirect3DDevice9Ex* dev, const RECT* a, const RECT* b, HWND w,
                                           const RGNDATA* r, DWORD fl) {
    HookScope scope;
    if (!scope.outer || (fl & 0x00000008 /* D3DPRESENT_DONOTWAIT */)) return g_d9PresentEx[N](dev, a, b, w, r, fl);
    PaceTicket t = PaceBefore(kApiD3d9, dev, AreaOfD9Device(dev, w), nullptr);
    HRESULT hr = g_d9PresentEx[N](dev, a, b, w, r, fl);
    if (t.paced) PaceAfter(t);
    return hr;
}
template <int N>
HRESULT STDMETHODCALLTYPE D9ScPresent_Hook(IDirect3DSwapChain9* sc, const RECT* a, const RECT* b, HWND w,
                                           const RGNDATA* r, DWORD fl) {
    HookScope scope;
    if (!scope.outer || (fl & 0x00000008)) return g_d9ScPresent[N](sc, a, b, w, r, fl);
    D3DPRESENT_PARAMETERS pp{};
    LONG64 area = 0;
    if (SUCCEEDED(sc->GetPresentParameters(&pp))) area = (LONG64)pp.BackBufferWidth * pp.BackBufferHeight;
    PaceTicket t = PaceBefore(kApiD3d9, sc, area, nullptr);
    HRESULT hr = g_d9ScPresent[N](sc, a, b, w, r, fl);
    if (t.paced) PaceAfter(t);
    return hr;
}
void* const kD9PresentHooks[kMaxVariants] = {(void*)D9Present_Hook<0>, (void*)D9Present_Hook<1>,
                                             (void*)D9Present_Hook<2>, (void*)D9Present_Hook<3>};
void* const kD9PresentExHooks[kMaxVariants] = {(void*)D9PresentEx_Hook<0>, (void*)D9PresentEx_Hook<1>,
                                               (void*)D9PresentEx_Hook<2>, (void*)D9PresentEx_Hook<3>};
void* const kD9ScPresentHooks[kMaxVariants] = {(void*)D9ScPresent_Hook<0>, (void*)D9ScPresent_Hook<1>,
                                               (void*)D9ScPresent_Hook<2>, (void*)D9ScPresent_Hook<3>};

using Direct3DCreate9_t = IDirect3D9*(WINAPI*)(UINT);
using Direct3DCreate9Ex_t = HRESULT(WINAPI*)(UINT, IDirect3D9Ex**);

void HookD9Device(IDirect3DDevice9* dev, bool ex) {
    void** vt = *(void***)dev;
    HookVariant(vt[17], g_d9PresentAt, kD9PresentHooks, (void**)g_d9Present, L"D3D9 Present");
    if (ex) HookVariant(vt[121], g_d9PresentExAt, kD9PresentExHooks, (void**)g_d9PresentEx, L"D3D9 PresentEx");
    IDirect3DSwapChain9* sc = nullptr;
    if (SUCCEEDED(dev->GetSwapChain(0, &sc)) && sc) {
        void** svt = *(void***)sc;
        HookVariant(svt[3], g_d9ScPresentAt, kD9ScPresentHooks, (void**)g_d9ScPresent, L"D3D9 swap chain Present");
        sc->Release();
    }
}

bool HookD3d9() {
    HMODULE d9 = GetModuleHandleW(L"d3d9.dll");
    if (!d9) return false;
    HWND wnd = MakeDummyWindow();
    if (!wnd) return false;
    bool ok = false;
    D3DPRESENT_PARAMETERS pp{};
    pp.Windowed = TRUE;
    pp.SwapEffect = D3DSWAPEFFECT_DISCARD;
    pp.BackBufferFormat = D3DFMT_UNKNOWN;
    pp.BackBufferWidth = 64;
    pp.BackBufferHeight = 64;
    pp.hDeviceWindow = wnd;
    const DWORD flags = D3DCREATE_SOFTWARE_VERTEXPROCESSING | D3DCREATE_DISABLE_DRIVER_MANAGEMENT | D3DCREATE_FPU_PRESERVE;
    if (auto createEx = (Direct3DCreate9Ex_t)GetProcAddress(d9, "Direct3DCreate9Ex")) {
        IDirect3D9Ex* d3d = nullptr;
        if (SUCCEEDED(createEx(D3D_SDK_VERSION, &d3d)) && d3d) {
            IDirect3DDevice9Ex* dev = nullptr;
            if (SUCCEEDED(d3d->CreateDeviceEx(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, wnd, flags, &pp, nullptr, &dev)) && dev) {
                HookD9Device(dev, true);
                dev->Release();
                ok = true;
            }
            d3d->Release();
        }
    }
    if (auto create = (Direct3DCreate9_t)GetProcAddress(d9, "Direct3DCreate9")) {
        if (IDirect3D9* d3d = create(D3D_SDK_VERSION)) {
            IDirect3DDevice9* dev = nullptr;
            HRESULT hr = d3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, wnd, flags, &pp, &dev);
            if (FAILED(hr)) hr = d3d->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_NULLREF, wnd, flags, &pp, &dev);
            if (SUCCEEDED(hr) && dev) {
                HookD9Device(dev, false);
                dev->Release();
                ok = true;
            }
            d3d->Release();
        }
    }
    DestroyWindow(wnd);
    if (!ok) Wh_Log(L"D3D9 probe device failed");
    return ok;
}

// ---- OpenGL ------------------------------------------------------------------
using wglSwapBuffers_t = BOOL(WINAPI*)(HDC);
wglSwapBuffers_t g_wglSwap;

BOOL WINAPI wglSwapBuffers_Hook(HDC dc) {
    HookScope scope;
    if (!scope.outer) return g_wglSwap(dc);
    PaceTicket t = PaceBefore(kApiGl, dc, AreaOfHwnd(WindowFromDC(dc)), nullptr);
    BOOL r = g_wglSwap(dc);
    if (t.paced) PaceAfter(t);
    return r;
}

bool HookGl() {
    HMODULE gl = GetModuleHandleW(L"opengl32.dll");
    if (!gl) return false;
    void* p = (void*)GetProcAddress(gl, "wglSwapBuffers");
    if (!p) return false;
    if (!Wh_SetFunctionHook(p, (void*)wglSwapBuffers_Hook, (void**)&g_wglSwap)) return false;
    Wh_Log(L"Hooked wglSwapBuffers at %p", p);
    return true;
}

// ---- Vulkan ------------------------------------------------------------------
// The export, plus vkGetDeviceProcAddr so games that fetch the function per
// device get our wrapper. Each device's real function is kept by its dispatch
// key, which its queues share.
#ifdef _WIN64
#define CAP_VKAPI
#else
#define CAP_VKAPI __stdcall
#endif
using VkFn = void(CAP_VKAPI*)();
using vkQueuePresentKHR_t = int(CAP_VKAPI*)(void*, const void*);
using vkGetDeviceProcAddr_t = VkFn(CAP_VKAPI*)(void*, const char*);
vkQueuePresentKHR_t g_vkPresentExport;
vkGetDeviceProcAddr_t g_vkGetDeviceProcAddr;
std::mutex g_vkLock;
std::map<void*, vkQueuePresentKHR_t> g_vkReal;

int CAP_VKAPI vkQueuePresentKHR_Wrap(void* queue, const void* info) {
    vkQueuePresentKHR_t real = g_vkPresentExport;
    {
        std::lock_guard<std::mutex> lock(g_vkLock);
        auto it = g_vkReal.find(*(void**)queue);
        if (it != g_vkReal.end()) real = it->second;
    }
    if (!real) return -3;  // VK_ERROR_INITIALIZATION_FAILED
    HookScope scope;
    if (!scope.outer) return real(queue, info);
    PaceTicket t = PaceBefore(kApiVulkan, *(void**)queue, 0, nullptr);
    int r = real(queue, info);
    if (t.paced) PaceAfter(t);
    return r;
}

VkFn CAP_VKAPI vkGetDeviceProcAddr_Hook(void* device, const char* name) {
    VkFn fn = g_vkGetDeviceProcAddr(device, name);
    if (fn && device && name && strcmp(name, "vkQueuePresentKHR") == 0 && !g_unloading.load()) {
        std::lock_guard<std::mutex> lock(g_vkLock);
        g_vkReal[*(void**)device] = (vkQueuePresentKHR_t)fn;
        return (VkFn)vkQueuePresentKHR_Wrap;
    }
    return fn;
}

int CAP_VKAPI vkQueuePresentKHR_Hook(void* queue, const void* info) {
    HookScope scope;
    if (!scope.outer) return g_vkPresentExport(queue, info);
    PaceTicket t = PaceBefore(kApiVulkan, *(void**)queue, 0, nullptr);
    int r = g_vkPresentExport(queue, info);
    if (t.paced) PaceAfter(t);
    return r;
}

bool HookVulkan() {
    HMODULE vk = GetModuleHandleW(L"vulkan-1.dll");
    if (!vk) return false;
    void* present = (void*)GetProcAddress(vk, "vkQueuePresentKHR");
    void* gdpa = (void*)GetProcAddress(vk, "vkGetDeviceProcAddr");
    bool ok = false;
    if (present && Wh_SetFunctionHook(present, (void*)vkQueuePresentKHR_Hook, (void**)&g_vkPresentExport)) ok = true;
    if (gdpa && Wh_SetFunctionHook(gdpa, (void*)vkGetDeviceProcAddr_Hook, (void**)&g_vkGetDeviceProcAddr)) ok = true;
    if (ok) Wh_Log(L"Hooked Vulkan present");
    return ok;
}

// ---- Finding the graphics modules ----------------------------------------------
// The game loads them when it likes: look every 100 ms for 10 s, then every
// second. Each API is hooked once.
DWORD WINAPI GameHookThread(LPVOID) {
    bool dxgi = false, d3d12 = false, d9 = false, gl = false, vk = false;
    for (int round = 0; !g_unloading.load(); round++) {
        bool any = false;
        if (!dxgi && GetModuleHandleW(L"dxgi.dll")) {
            dxgi = true;
            any |= HookDxgi();
        }
        if (!d3d12 && GetModuleHandleW(L"d3d12.dll") && GetModuleHandleW(L"dxgi.dll")) {
            d3d12 = true;
            any |= HookD3d12();
        }
        if (!d9 && GetModuleHandleW(L"d3d9.dll")) {
            d9 = true;
            any |= HookD3d9();
        }
        if (!gl && GetModuleHandleW(L"opengl32.dll")) {
            gl = true;
            any |= HookGl();
        }
        if (!vk && GetModuleHandleW(L"vulkan-1.dll")) {
            vk = true;
            any |= HookVulkan();
        }
        if (any && !g_unloading.load()) Wh_ApplyHookOperations();
        if (dxgi && d3d12 && d9 && gl && vk) break;
        for (int i = 0; i < (round < 100 ? 1 : 10) && !g_unloading.load(); i++) Sleep(100);
    }
    return 0;
}

std::wstring g_exePathLower;

// What the settings say for this game: false when it is not ours to cap.
// A Games page slot wins; otherwise a game under a listed folder takes the
// Frame cap page's cap and way.
bool ResolveGame(const Config& c, int& mode, double& fps, double& bg, bool& on) {
    int slot = FindSlot(c, g_exeLower);
    if (slot >= 0) {
        mode = EffectiveMode(c, slot);
        fps = EffectiveFps(c, slot);
        bg = EffectiveBg(c, slot);
        on = c.games[slot].on;
    } else if (InFolders(c, g_exePathLower) && !NeverInject(g_exeLower)) {
        mode = c.mode;
        fps = c.fps;
        bg = c.bg;
        on = true;
    } else {
        return false;
    }
    return mode != kModeDriver && mode != kModeNone;
}

void LoadGameSettings() {
    Config c = ReadConfig();
    int mode = kModeNone;
    double fps = 0, bg = 0;
    bool on = false;
    bool ours = c.configured && ResolveGame(c, mode, fps, bg, on);
    on = ours && on && c.enabled;
    g_gameMode.store(ours ? mode : kModeAsync);
    g_capFg.store(ours ? fps : 0);
    g_capBg.store(ours ? bg : 0);
    g_busyWait.store(c.busy);
    g_gameOn.store(on);
    Wh_Log(L"%s: cap %s, %.2f fps (background %.2f), %s wait", g_exeLower.c_str(), on ? ModeName(mode) : L"off",
           g_capFg.load(), g_capBg.load(), c.busy ? L"busy" : L"passive");
}

// True when this game should carry the in-game cap.
bool GameWanted(const std::wstring& exePath) {
    g_exeLower = Lower(BaseName(exePath));
    g_exePathLower = Lower(exePath);
    if (NeverInject(g_exeLower) || HasAntiCheatFiles(exePath)) return false;
    for (PCWSTR m : {L"EasyAntiCheat.dll", L"EasyAntiCheat_x64.dll", L"EasyAntiCheat_EOS.dll", L"BEClient_x64.dll",
                     L"BEClient.dll", L"vgk.sys"})
        if (GetModuleHandleW(m)) return false;
    Config c = ReadConfig();
    if (!c.configured) return false;
    int mode;
    double fps, bg;
    bool on;
    return ResolveGame(c, mode, fps, bg, on);
}

}  // namespace

namespace {

// ===========================================================================
// Tool side: one elevated windhawk.exe process. Tray icon, shortcuts, the
// driver cap and the list of games the mod loads into.
// ===========================================================================

HWND g_msgWnd = nullptr;
HANDLE g_uiThread = nullptr, g_uiReady = nullptr, g_instanceMutex = nullptr;
DWORD g_uiThreadId = 0;
HANDLE g_workThread = nullptr, g_workEvent = nullptr;
bool g_trayIconOn = true;

std::mutex g_cfgLock;
Config g_cfg;  // under g_cfgLock

std::mutex g_statusLock;
std::wstring g_hotkeyProblem;  // under g_statusLock
std::atomic<int> g_nvidia{-1};  // -1 not checked, 0 no NVIDIA driver, 1 driver found

bool IsElevated() {
    HANDLE token = nullptr;
    if (!OpenProcessToken(GetCurrentProcess(), TOKEN_QUERY, &token)) return false;
    TOKEN_ELEVATION e{};
    DWORD len = 0;
    bool r = GetTokenInformation(token, TokenElevation, &e, sizeof(e), &len) && e.TokenIsElevated;
    CloseHandle(token);
    return r;
}

// After the elevated relaunch, Windhawk can load this mod a moment late when
// the PC is busy. windhawk-mod.exe then shows a false "Running the tool mod
// failed" box even though the mod loads and works. Close that box, only in
// this process, during the first seconds.
BOOL CALLBACK CloseFalseFailureBox(HWND hwnd, LPARAM) {
    DWORD pid = 0;
    GetWindowThreadProcessId(hwnd, &pid);
    if (pid != GetCurrentProcessId()) return TRUE;
    WCHAR cls[16]{};
    WCHAR title[32]{};
    GetClassNameW(hwnd, cls, ARRAYSIZE(cls));
    GetWindowTextW(hwnd, title, ARRAYSIZE(title));
    if (wcscmp(cls, L"#32770") == 0 && wcscmp(title, L"Windhawk") == 0) {
        PostMessageW(hwnd, WM_CLOSE, 0, 0);
        Wh_Log(L"Closed false tool-mod failure box");
    }
    return TRUE;
}

DWORD WINAPI FalseFailureBoxThreadProc(LPVOID) {
    for (int i = 0; i < 60 && !g_stop.load(std::memory_order_relaxed); i++) {
        EnumWindows(CloseFalseFailureBox, 0);
        Sleep(250);
    }
    return 0;
}

std::wstring FpsText(double v) {
    WCHAR b[32];
    if (std::fabs(v - std::round(v)) < 0.005) swprintf(b, 32, L"%.0f", v);
    else swprintf(b, 32, L"%.2f", v);
    std::wstring s = b;
    while (s.find(L'.') != std::wstring::npos && (s.back() == L'0' || s.back() == L'.')) {
        bool dot = s.back() == L'.';
        s.pop_back();
        if (dot) break;
    }
    return s;
}

// ---------------------------------------------------------------------------
// NVIDIA driver profiles (DRS). Every value this mod changes is written to an
// undo list first, so turning the mod off or removing it puts back exactly
// what was there.
// ---------------------------------------------------------------------------

struct NVDRS_BINARY_SETTING {
    NvU32 valueLength;
    NvU8 valueData[4096];
};
struct NVDRS_SETTING {
    NvU32 version;
    NvAPI_UnicodeString settingName;
    NvU32 settingId;
    NvU32 settingType;
    NvU32 settingLocation;
    NvU32 isCurrentPredefined;
    NvU32 isPredefinedValid;
    union {
        NvU32 u32PredefinedValue;
        NVDRS_BINARY_SETTING binaryPredefinedValue;
        NvAPI_UnicodeString wszPredefinedValue;
    };
    union {
        NvU32 u32CurrentValue;
        NVDRS_BINARY_SETTING binaryCurrentValue;
        NvAPI_UnicodeString wszCurrentValue;
    };
};
struct NVDRS_PROFILE {
    NvU32 version;
    NvAPI_UnicodeString profileName;
    NvU32 gpuSupport;
    NvU32 isPredefined;
    NvU32 numOfApps;
    NvU32 numOfSettings;
};
struct NVDRS_APPLICATION_V4 {
    NvU32 version;
    NvU32 isPredefined;
    NvAPI_UnicodeString appName;
    NvAPI_UnicodeString userFriendlyName;
    NvAPI_UnicodeString launcher;
    NvAPI_UnicodeString fileInFolder;
    NvU32 flags;
    NvAPI_UnicodeString commandLine;
};

constexpr NvU32 kFrl = 0x10835002, kFrlBg = 0x10835005, kUll = 0x10835000, kCpl = 0x0005F543, kPrerender = 0x007BA09E;
constexpr NvAPI_Status kNvNotFound = -160, kNvAppNotFound = -166;

using DrsSession_t = NvAPI_Status(__cdecl*)(NvDRSSessionHandle*);
using DrsSessionOnly_t = NvAPI_Status(__cdecl*)(NvDRSSessionHandle);
using DrsGetProfile_t = NvAPI_Status(__cdecl*)(NvDRSSessionHandle, NvDRSProfileHandle*);
using DrsEnumProfiles_t = NvAPI_Status(__cdecl*)(NvDRSSessionHandle, NvU32, NvDRSProfileHandle*);
using DrsGetSetting_t = NvAPI_Status(__cdecl*)(NvDRSSessionHandle, NvDRSProfileHandle, NvU32, NVDRS_SETTING*);
using DrsSetSetting_t = NvAPI_Status(__cdecl*)(NvDRSSessionHandle, NvDRSProfileHandle, NVDRS_SETTING*);
using DrsDeleteSetting_t = NvAPI_Status(__cdecl*)(NvDRSSessionHandle, NvDRSProfileHandle, NvU32);
using DrsEnumApps_t = NvAPI_Status(__cdecl*)(NvDRSSessionHandle, NvDRSProfileHandle, NvU32, NvU32*,
                                             NVDRS_APPLICATION_V4*);
using DrsFindApp_t = NvAPI_Status(__cdecl*)(NvDRSSessionHandle, const NvU16*, NvDRSProfileHandle*,
                                            NVDRS_APPLICATION_V4*);
using DrsFindProfile_t = NvAPI_Status(__cdecl*)(NvDRSSessionHandle, const NvU16*, NvDRSProfileHandle*);
using DrsCreateProfile_t = NvAPI_Status(__cdecl*)(NvDRSSessionHandle, NVDRS_PROFILE*, NvDRSProfileHandle*);
using DrsCreateApp_t = NvAPI_Status(__cdecl*)(NvDRSSessionHandle, NvDRSProfileHandle, NVDRS_APPLICATION_V4*);
using DrsDeleteProfile_t = NvAPI_Status(__cdecl*)(NvDRSSessionHandle, NvDRSProfileHandle);

struct Drs {
    NvDRSSessionHandle s = nullptr;
    DrsGetSetting_t get = nullptr;
    DrsSetSetting_t set = nullptr;
    DrsDeleteSetting_t del = nullptr;
    DrsEnumProfiles_t enumProfiles = nullptr;
    DrsEnumApps_t enumApps = nullptr;
    DrsFindApp_t findApp = nullptr;
    DrsFindProfile_t findProfile = nullptr;
    DrsCreateProfile_t createProfile = nullptr;
    DrsCreateApp_t createApp = nullptr;
    DrsDeleteProfile_t deleteProfile = nullptr;
    DrsSessionOnly_t save = nullptr;
    NvDRSProfileHandle base = nullptr;
    std::unique_ptr<NVDRS_SETTING> setting{new NVDRS_SETTING()};
    std::unique_ptr<NVDRS_APPLICATION_V4[]> apps{new NVDRS_APPLICATION_V4[32]()};

    bool Open() {
        NvQI_t qi = NvApiQI();
        if (!qi) return false;
        auto create = (DrsSession_t)qi(0x0694D52E);
        auto load = (DrsSessionOnly_t)qi(0x375DBD6B);
        auto getBase = (DrsGetProfile_t)qi(0xDA8466A0);
        get = (DrsGetSetting_t)qi(0x73BF8338);
        set = (DrsSetSetting_t)qi(0x577DD202);
        del = (DrsDeleteSetting_t)qi(0xE4A26362);
        enumProfiles = (DrsEnumProfiles_t)qi(0xBC371EE0);
        enumApps = (DrsEnumApps_t)qi(0x7FA2173A);
        findApp = (DrsFindApp_t)qi(0xEEE566B2);
        findProfile = (DrsFindProfile_t)qi(0x7E4A9A0B);
        createProfile = (DrsCreateProfile_t)qi(0xCC176068);
        createApp = (DrsCreateApp_t)qi(0x4347A9DE);
        deleteProfile = (DrsDeleteProfile_t)qi(0x17093206);
        save = (DrsSessionOnly_t)qi(0xFCBC7E14);
        if (!create || !load || !getBase || !get || !set || !del || !enumProfiles || !enumApps || !findApp ||
            !findProfile || !createProfile || !createApp || !deleteProfile || !save)
            return false;
        if (create(&s) != 0) return false;
        if (load(s) != 0 || getBase(s, &base) != 0) {
            Close();
            return false;
        }
        return true;
    }
    void Close() {
        if (!s) return;
        if (auto destroy = (DrsSessionOnly_t)NvApiQI()(0xDAD9CFF8)) destroy(s);
        s = nullptr;
    }
    ~Drs() { Close(); }

    // Reads a DWORD setting set on this profile itself. False: not set here.
    bool Read(NvDRSProfileHandle h, NvU32 id, NvU32& value) {
        memset(setting.get(), 0, sizeof(NVDRS_SETTING));
        setting->version = CAP_NV_VER(NVDRS_SETTING, 1);
        if (get(s, h, id, setting.get()) != 0) return false;
        value = setting->u32CurrentValue;
        return setting->settingLocation == 0;
    }
    bool Write(NvDRSProfileHandle h, NvU32 id, NvU32 value) {
        memset(setting.get(), 0, sizeof(NVDRS_SETTING));
        setting->version = CAP_NV_VER(NVDRS_SETTING, 1);
        setting->settingId = id;
        setting->settingType = 0;  // DWORD
        setting->u32CurrentValue = value;
        NvAPI_Status st = set(s, h, setting.get());
        if (st != 0) Wh_Log(L"Driver: writing setting 0x%08X failed, status %d", id, st);
        return st == 0;
    }

    // The profile that holds exe. The driver stores some apps with a full
    // path (Plutonium's bootstrapper), which a lookup by bare name misses, so
    // those are found by walking every profile's apps.
    NvDRSProfileHandle FindExe(const std::wstring& exeLower) {
        NvU16 name[2048]{};
        wcsncpy((wchar_t*)name, exeLower.c_str(), 2047);
        NvDRSProfileHandle h = nullptr;
        apps[0].version = CAP_NV_VER(NVDRS_APPLICATION_V4, 4);
        if (findApp(s, name, &h, &apps[0]) == 0 && h) return h;
        for (NvU32 i = 0;; i++) {
            NvDRSProfileHandle p = nullptr;
            if (enumProfiles(s, i, &p) != 0) break;
            for (NvU32 start = 0;;) {
                NvU32 count = 32;
                for (NvU32 k = 0; k < 32; k++) apps[k].version = CAP_NV_VER(NVDRS_APPLICATION_V4, 4);
                if (enumApps(s, p, start, &count, apps.get()) != 0 || count == 0) break;
                for (NvU32 k = 0; k < count; k++) {
                    std::wstring app = Lower((wchar_t*)apps[k].appName);
                    if (app.size() > exeLower.size() &&
                        app.compare(app.size() - exeLower.size(), exeLower.size(), exeLower) == 0) {
                        wchar_t sep = app[app.size() - exeLower.size() - 1];
                        if (sep == L'/' || sep == L'\\') return p;
                    }
                }
                start += count;
                if (count < 32) break;
            }
        }
        return nullptr;
    }

    std::wstring OwnProfileName(const std::wstring& exeLower) { return L"Seamless FPS Capper - " + exeLower; }

    NvDRSProfileHandle Profile(const std::wstring& target, bool create, bool* created) {
        if (created) *created = false;
        if (target == L"*base*") return base;
        if (NvDRSProfileHandle h = FindExe(target)) return h;
        NvU16 pname[2048]{};
        wcsncpy((wchar_t*)pname, OwnProfileName(target).c_str(), 2047);
        NvDRSProfileHandle h = nullptr;
        if (findProfile(s, pname, &h) == 0 && h) return h;
        if (!create) return nullptr;
        auto info = std::make_unique<NVDRS_PROFILE>();
        info->version = CAP_NV_VER(NVDRS_PROFILE, 1);
        memcpy(info->profileName, pname, sizeof(pname));
        NvAPI_Status st = createProfile(s, info.get(), &h);
        if (st != 0 || !h) {
            Wh_Log(L"Driver: creating a profile for %s failed, status %d", target.c_str(), st);
            return nullptr;
        }
        auto app = std::make_unique<NVDRS_APPLICATION_V4>();
        app->version = CAP_NV_VER(NVDRS_APPLICATION_V4, 4);
        wcsncpy((wchar_t*)app->appName, target.c_str(), 2047);
        st = createApp(s, h, app.get());
        if (st != 0) {
            Wh_Log(L"Driver: adding %s to its new profile failed, status %d", target.c_str(), st);
            deleteProfile(s, h);
            return nullptr;
        }
        if (created) *created = true;
        Wh_Log(L"Driver: made a profile for %s", target.c_str());
        return h;
    }
};

struct UndoEntry {
    bool had = false;
    NvU32 old = 0;
    bool created = false;
};
using UndoKey = std::pair<std::wstring, NvU32>;

// A copy of the undo list outside Windhawk, so removing the mod (which
// deletes its stored values) can still put the driver back.
std::wstring UndoFilePath() {
    WCHAR dir[MAX_PATH];
    if (!ExpandEnvironmentStringsW(L"%ProgramData%\\SeamlessFpsCapper", dir, MAX_PATH)) return L"";
    CreateDirectoryW(dir, nullptr);
    return std::wstring(dir) + L"\\driver-undo.txt";
}

std::wstring ReadUndoFile() {
    std::wstring path = UndoFilePath();
    HANDLE f = CreateFileW(path.c_str(), GENERIC_READ, FILE_SHARE_READ, nullptr, OPEN_EXISTING, 0, nullptr);
    if (f == INVALID_HANDLE_VALUE) return L"";
    std::wstring out;
    DWORD size = GetFileSize(f, nullptr), got = 0;
    if (size != INVALID_FILE_SIZE && size < 1 << 20 && size % 2 == 0) {
        out.resize(size / 2);
        if (!ReadFile(f, out.data(), size, &got, nullptr)) got = 0;
        out.resize(got / 2);
    }
    CloseHandle(f);
    return out;
}

void WriteUndoFile(const std::wstring& all) {
    std::wstring path = UndoFilePath();
    if (path.empty()) return;
    if (all.empty()) {
        DeleteFileW(path.c_str());
        return;
    }
    HANDLE f = CreateFileW(path.c_str(), GENERIC_WRITE, 0, nullptr, CREATE_ALWAYS, 0, nullptr);
    if (f == INVALID_HANDLE_VALUE) return;
    DWORD put = 0;
    WriteFile(f, all.data(), (DWORD)(all.size() * 2), &put, nullptr);
    CloseHandle(f);
}

std::map<UndoKey, UndoEntry> LoadUndo() {
    std::map<UndoKey, UndoEntry> out;
    std::vector<WCHAR> buf(32768);
    Wh_GetStringValue(L"driverUndo", buf.data(), buf.size());
    std::wstring all = buf.data();
    if (all.empty()) all = ReadUndoFile();
    size_t start = 0;
    while (start < all.size()) {
        size_t nl = all.find(L'\n', start);
        if (nl == std::wstring::npos) nl = all.size();
        std::wstring line = all.substr(start, nl - start);
        start = nl + 1;
        std::vector<std::wstring> f;
        size_t a = 0;
        while (true) {
            size_t b = line.find(L'|', a);
            f.push_back(line.substr(a, b == std::wstring::npos ? std::wstring::npos : b - a));
            if (b == std::wstring::npos) break;
            a = b + 1;
        }
        if (f.size() != 5 || f[0].empty()) continue;
        UndoEntry e;
        e.had = f[2] == L"1";
        e.old = (NvU32)wcstoul(f[3].c_str(), nullptr, 10);
        e.created = f[4] == L"1";
        out[{f[0], (NvU32)wcstoul(f[1].c_str(), nullptr, 16)}] = e;
    }
    return out;
}

void SaveUndo(const std::map<UndoKey, UndoEntry>& undo) {
    std::wstring all;
    for (auto& [k, e] : undo) {
        WCHAR line[600];
        swprintf(line, 600, L"%s|%08X|%d|%u|%d\n", k.first.c_str(), k.second, e.had ? 1 : 0, e.old, e.created ? 1 : 0);
        all += line;
    }
    if (all.empty()) Wh_DeleteValue(L"driverUndo");
    else Wh_SetStringValue(L"driverUndo", all.c_str());
    WriteUndoFile(all);
}

struct Want {
    std::wstring target;
    NvU32 id, value;
};

std::vector<Want> DriverWants(const Config& c) {
    std::vector<Want> w;
    if (!c.configured || !c.driver) return w;
    auto cap = [&](double fps) { return c.enabled ? (NvU32)std::clamp(std::lround(fps), 0L, 1000L) : 0u; };
    if (c.mode == kModeDriver) {
        w.push_back({L"*base*", kFrl, cap(c.fps)});
        if (c.bg > 0) w.push_back({L"*base*", kFrlBg, cap(c.bg)});
    }
    switch (c.lowLatency) {
        case 1:
            w.push_back({L"*base*", kCpl, 0});
            w.push_back({L"*base*", kUll, 0});
            break;
        case 2:
            w.push_back({L"*base*", kCpl, 1});
            w.push_back({L"*base*", kUll, 0});
            w.push_back({L"*base*", kPrerender, 1});
            break;
        case 3:
            w.push_back({L"*base*", kCpl, 2});
            w.push_back({L"*base*", kUll, 1});
            w.push_back({L"*base*", kPrerender, 1});
            break;
    }
    for (int i = 0; i < kSlots; i++) {
        const GameEntry& g = c.games[i];
        if (g.exe.empty() || !g.on || EffectiveMode(c, i) != kModeDriver) continue;
        w.push_back({g.exe, kFrl, cap(EffectiveFps(c, i))});
        double bg = EffectiveBg(c, i);
        if (bg > 0) w.push_back({g.exe, kFrlBg, cap(bg)});
    }
    return w;
}

std::mutex g_driverLock;

// Makes the driver match wants. Values not wanted any more go back to what
// the undo list says they were.
void ApplyDriver(const std::vector<Want>& wants) {
    std::lock_guard<std::mutex> lock(g_driverLock);
    Drs d;
    if (!d.Open()) {
        if (g_nvidia.load() != 0) Wh_Log(L"Driver: no NVIDIA driver session, the driver cap is off");
        g_nvidia.store(0);
        return;
    }
    g_nvidia.store(1);
    auto undo = LoadUndo();
    bool changed = false, undoChanged = false;
    std::set<UndoKey> wanted;
    for (const Want& w : wants) {
        UndoKey key{w.target, w.id};
        wanted.insert(key);
        bool created = false;
        NvDRSProfileHandle h = d.Profile(w.target, true, &created);
        if (!h) continue;
        NvU32 cur = 0;
        bool here = d.Read(h, w.id, cur);
        if (here && cur == w.value && !created) continue;
        if (!undo.count(key)) {
            UndoEntry e;
            e.had = here;
            e.old = cur;
            e.created = created;
            // A profile made earlier for another setting of this game.
            for (auto& [k, other] : undo)
                if (k.first == w.target && other.created) e.created = true;
            undo[key] = e;
            undoChanged = true;
        }
        if (d.Write(h, w.id, w.value)) {
            changed = true;
            Wh_Log(L"Driver: %s setting 0x%08X %u -> %u", w.target == L"*base*" ? L"global" : w.target.c_str(), w.id,
                   here ? cur : 0, w.value);
        }
    }
    std::set<std::wstring> emptied;
    for (auto it = undo.begin(); it != undo.end();) {
        if (wanted.count(it->first)) {
            ++it;
            continue;
        }
        NvDRSProfileHandle h = d.Profile(it->first.first, false, nullptr);
        if (h) {
            NvAPI_Status st = it->second.had ? (d.Write(h, it->first.second, it->second.old) ? 0 : -1)
                                             : d.del(d.s, h, it->first.second);
            if (st != 0 && st != kNvNotFound)
                Wh_Log(L"Driver: putting back 0x%08X on %s failed, status %d", it->first.second,
                       it->first.first.c_str(), st);
            changed = true;
            Wh_Log(L"Driver: put back 0x%08X on %s", it->first.second,
                   it->first.first == L"*base*" ? L"global" : it->first.first.c_str());
        }
        if (it->second.created) emptied.insert(it->first.first);
        it = undo.erase(it);
        undoChanged = true;
    }
    // Profiles this mod made, once none of their settings are wanted.
    for (const std::wstring& target : emptied) {
        bool still = false;
        for (auto& [k, e] : undo)
            if (k.first == target) still = true;
        if (still) continue;
        NvU16 pname[2048]{};
        wcsncpy((wchar_t*)pname, d.OwnProfileName(target).c_str(), 2047);
        NvDRSProfileHandle h = nullptr;
        if (d.findProfile(d.s, pname, &h) == 0 && h && d.deleteProfile(d.s, h) == 0) {
            changed = true;
            Wh_Log(L"Driver: removed the profile made for %s", target.c_str());
        }
    }
    if (changed) {
        NvAPI_Status st = d.save(d.s);
        if (st != 0) Wh_Log(L"Driver: saving failed, status %d", st);
    }
    if (undoChanged) SaveUndo(undo);
}

// ---------------------------------------------------------------------------
// Which games the mod loads into: Windhawk's custom include list for this mod.
// Only names this mod added are ever taken off it.
// ---------------------------------------------------------------------------

constexpr WCHAR kModKey[] = L"SOFTWARE\\Windhawk\\Engine\\Mods\\" WH_MOD_ID;

std::vector<std::wstring> SplitBar(const std::wstring& s) {
    std::vector<std::wstring> out;
    size_t a = 0;
    while (a <= s.size()) {
        size_t b = s.find(L'|', a);
        if (b == std::wstring::npos) b = s.size();
        std::wstring part = Trim(s.substr(a, b - a));
        if (!part.empty()) out.push_back(part);
        a = b + 1;
    }
    return out;
}

// Windhawk keeps its keys in the 64-bit registry view. Windhawk 1.7.3 runs
// tool mods in a 32-bit windhawk.exe, where a plain HKLM\SOFTWARE open lands
// in WOW6432Node and finds nothing, so every open here names the 64-bit view.
std::wstring ReadModString(PCWSTR value) {
    WCHAR buf[8192]{};
    DWORD size = sizeof(buf) - sizeof(WCHAR);
    if (RegGetValueW(HKEY_LOCAL_MACHINE, kModKey, value, RRF_RT_REG_SZ | RRF_SUBKEY_WOW6464KEY, nullptr, buf,
                     &size) != ERROR_SUCCESS)
        return L"";
    return buf;
}

LSTATUS SetModValue(PCWSTR name, DWORD type, const void* data, DWORD size) {
    HKEY k = nullptr;
    LSTATUS st = RegOpenKeyExW(HKEY_LOCAL_MACHINE, kModKey, 0, KEY_SET_VALUE | KEY_WOW64_64KEY, &k);
    if (st != ERROR_SUCCESS) return st;
    st = RegSetValueExW(k, name, 0, type, (const BYTE*)data, size);
    RegCloseKey(k);
    return st;
}

bool ModKeyExists(DWORD* disabled) {
    HKEY k = nullptr;
    if (RegOpenKeyExW(HKEY_LOCAL_MACHINE, kModKey, 0, KEY_READ | KEY_WOW64_64KEY, &k) != ERROR_SUCCESS) return false;
    DWORD v = 0, size = sizeof(v);
    if (RegQueryValueExW(k, L"Disabled", nullptr, nullptr, (BYTE*)&v, &size) != ERROR_SUCCESS) v = 0;
    RegCloseKey(k);
    if (disabled) *disabled = v;
    return true;
}

// Puts desired (lower case) on one of Windhawk's custom lists for this mod.
// Entries the owner added by hand stay; only names this mod added earlier
// (kept in managedValue) are taken off. True when the list was written.
bool SyncModList(PCWSTR regValue, PCWSTR managedValue, const std::vector<std::wstring>& desired) {
    WCHAR mbuf[4096]{};
    Wh_GetStringValue(managedValue, mbuf, ARRAYSIZE(mbuf));
    std::vector<std::wstring> managed = SplitBar(mbuf);
    std::vector<std::wstring> current = SplitBar(ReadModString(regValue));
    std::vector<std::wstring> next;
    for (auto& e : current) {
        std::wstring lo = Lower(e);
        if (std::find(managed.begin(), managed.end(), lo) != managed.end()) continue;
        next.push_back(e);
    }
    for (auto& d : desired) {
        bool have = false;
        for (auto& e : next)
            if (Lower(e) == d) have = true;
        if (!have) next.push_back(d);
    }
    std::wstring joined, oldJoined, managedJoined;
    for (auto& e : next) joined += (joined.empty() ? L"" : L"|") + e;
    for (auto& e : current) oldJoined += (oldJoined.empty() ? L"" : L"|") + e;
    for (auto& e : desired) managedJoined += (managedJoined.empty() ? L"" : L"|") + e;
    if (joined.size() > 3900) {
        Wh_Log(L"%s too long for Windhawk; not changed", regValue);
        return false;
    }
    if (joined == oldJoined) {
        if (managedJoined != std::wstring(mbuf)) {
            if (managedJoined.empty()) Wh_DeleteValue(managedValue);
            else Wh_SetStringValue(managedValue, managedJoined.c_str());
        }
        return false;
    }
    if (!ModKeyExists(nullptr)) return false;
    LSTATUS st = SetModValue(regValue, REG_SZ, joined.c_str(), (DWORD)((joined.size() + 1) * sizeof(WCHAR)));
    if (st != ERROR_SUCCESS) {
        Wh_Log(L"Writing %s failed, error %ld", regValue, st);
        return false;
    }
    // Recorded only once the list really holds them, so a failed write
    // never leaves names nobody would take off again.
    if (managedJoined.empty()) Wh_DeleteValue(managedValue);
    else Wh_SetStringValue(managedValue, managedJoined.c_str());
    Wh_Log(L"%s: \"%s\"", regValue, joined.c_str());
    return true;
}

void ApplyIncludes(const Config& c, bool clearAll) {
    std::vector<std::wstring> desired;
    if (!clearAll && c.configured) {
        for (int i = 0; i < kSlots; i++) {
            const GameEntry& g = c.games[i];
            if (g.exe.empty() || !g.on || NeverInject(g.exe)) continue;
            int m = EffectiveMode(c, i);
            if (m == kModeDriver || m == kModeNone) continue;
            if (std::find(desired.begin(), desired.end(), g.exe) == desired.end()) desired.push_back(g.exe);
        }
        // Whole folders, when the Frame cap page uses an in-game way.
        if (c.mode != kModeDriver && c.mode != kModeNone)
            for (const auto& f : c.folders) {
                std::wstring pat = f + L"\\*.exe";
                if (std::find(desired.begin(), desired.end(), pat) == desired.end()) desired.push_back(pat);
            }
    }
    bool wrote = SyncModList(L"IncludeCustom", L"managedIncludes", desired);
    // A folder pattern would load the mod into anti-cheat games there too:
    // the never-inject names go on the exclude list, which wins.
    std::vector<std::wstring> never;
    if (!clearAll && c.configured && !c.folders.empty())
        for (PCWSTR n : kNeverInject) never.push_back(n);
    wrote |= SyncModList(L"ExcludeCustom", L"managedExcludes", never);
    if (!wrote) return;
    // Tell the engine the mod's config changed, as the Windhawk app does.
    FILETIME ft;
    GetSystemTimeAsFileTime(&ft);
    ULONGLONG t = (((ULONGLONG)ft.dwHighDateTime << 32) | ft.dwLowDateTime) / 10000000ULL - 11644473600ULL;
    DWORD marker = (DWORD)t;
    SetModValue(L"SettingsChangeTime", REG_DWORD, &marker, sizeof(marker));
}

// ---------------------------------------------------------------------------
// The worker: driver and game list follow the settings, off the UI thread.
// ---------------------------------------------------------------------------

std::atomic<bool> g_restoreOnExit{false};

DWORD WINAPI WorkThreadProc(LPVOID) {
    while (!g_stop.load()) {
        WaitForSingleObject(g_workEvent, INFINITE);
        if (g_stop.load()) break;
        Config c;
        {
            std::lock_guard<std::mutex> lock(g_cfgLock);
            c = g_cfg;
        }
        if (!c.configured) {
            Wh_Log(L"Settings not saved yet: no driver or game list changes");
            continue;
        }
        ApplyIncludes(c, false);
        ApplyDriver(DriverWants(c));
    }
    return 0;
}

void KickWorker() {
    if (g_workEvent) SetEvent(g_workEvent);
}

// ---------------------------------------------------------------------------
// Status lines for the settings window (called on its thread).
// ---------------------------------------------------------------------------

std::wstring Capper_StatusText() {
    std::wstring out;
    if (g_nvidia.load() == 0)
        out = L"No NVIDIA driver found, so the driver cap and Reflex do nothing on this PC. The in-game caps still work.";
    std::lock_guard<std::mutex> lock(g_statusLock);
    if (!g_hotkeyProblem.empty()) out += (out.empty() ? L"" : L" ") + g_hotkeyProblem;
    return out;
}

std::wstring Capper_GamesBanner() {
    std::wstring s =
        L"The mod never loads into Plutonium or games with anti-cheat (Easy Anti-Cheat, BattlEye, Vanguard and others). "
        L"Those always get the driver cap.";
    if (g_nvidia.load() == 0) s += L" No NVIDIA driver here, so driver capped games are not capped.";
    return s;
}

// ---------------------------------------------------------------------------
// UI thread: tray icon, menu, shortcuts.
// ---------------------------------------------------------------------------

constexpr UINT WM_CAP_TRAY = WM_APP + 45;
constexpr UINT WM_CAP_SETTINGS = WM_APP + 46;
constexpr UINT TrayIconId() {
    UINT hash = 2166136261u;
    for (PCWSTR p = WH_MOD_ID; *p; p++) hash = (hash ^ (UINT)*p) * 16777619u;
    return hash | 0x80000000u;
}
constexpr UINT kTrayId = TrayIconId();
enum : int { kHkToggle = 1, kHkUp, kHkDown, kHkCycle };
constexpr UINT_PTR kRetryTimer = 7;
UINT g_taskbarCreated = 0;
bool g_trayAdded = false;
HICON g_trayIcon = nullptr;
bool g_hotkeyOn[5] = {};
std::wstring g_hotkeyText[5];

bool CapOn() { return !(g_state && g_state->toolDisabled); }

void EnableDarkMenus() {
    HMODULE ux = GetModuleHandleW(L"uxtheme.dll");
    if (!ux) ux = LoadLibraryExW(L"uxtheme.dll", nullptr, LOAD_LIBRARY_SEARCH_SYSTEM32);
    if (!ux) return;
    using SetMode = int(WINAPI*)(int);
    using Flush = void(WINAPI*)();
    if (auto set = (SetMode)GetProcAddress(ux, MAKEINTRESOURCEA(135))) set(2 /* ForceDark */);
    if (auto flush = (Flush)GetProcAddress(ux, MAKEINTRESOURCEA(136))) flush();
}

// A clean glyph drawn with GDI, so the tray never shares the settings
// window's Direct2D factories. On: a gauge on the blue to mauve gradient.
// Off: the slow gauge in grey. No plate behind it.
HICON MakeTrayIcon(bool on) {
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
    WCHAR face[64]{};
    GetTextFaceW(dc, 64, face);
    if (_wcsicmp(face, L"Segoe Fluent Icons") != 0) {
        SelectObject(dc, oldFont);
        DeleteObject(font);
        font = CreateFontW(-(int)(size * 0.84f), 0, 0, 0, FW_NORMAL, 0, 0, 0, DEFAULT_CHARSET, 0, 0,
                           ANTIALIASED_QUALITY, 0, L"Segoe MDL2 Assets");
        oldFont = SelectObject(dc, font);
    }
    SetBkMode(dc, TRANSPARENT);
    SetTextColor(dc, RGB(255, 255, 255));
    RECT r{0, 0, size, size};
    WCHAR g[2] = {(WCHAR)(on ? 0xEC4A : 0xEC48), 0};
    DrawTextW(dc, g, 1, &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE | DT_NOPREFIX);
    GdiFlush();
    SelectObject(dc, oldFont);
    DeleteObject(font);
    SelectObject(dc, old);
    DeleteDC(dc);

    // Mocha blue 89B4FA to mauve CBA6F7; grey overlay0 to surface2 when off.
    const float c0[3] = {on ? 0x89 / 255.f : 0x6C / 255.f, on ? 0xB4 / 255.f : 0x70 / 255.f, on ? 0xFA / 255.f : 0x86 / 255.f};
    const float c1[3] = {on ? 0xCB / 255.f : 0x58 / 255.f, on ? 0xA6 / 255.f : 0x5B / 255.f, on ? 0xF7 / 255.f : 0x70 / 255.f};
    uint32_t* px = (uint32_t*)bits;
    const uint32_t* gp = (const uint32_t*)glyphBits;
    for (int y = 0; y < size; y++)
        for (int x = 0; x < size; x++) {
            float t = std::clamp((x + y) / (2.0f * (size - 1)), 0.0f, 1.0f);
            float cov = ((gp[y * size + x] >> 8) & 0xFF) / 255.0f;
            float rgb[3];
            for (int i = 0; i < 3; i++) rgb[i] = (c0[i] + (c1[i] - c0[i]) * t) * cov;  // Premultiplied.
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

double GlobalFps() {
    std::lock_guard<std::mutex> lock(g_cfgLock);
    return g_cfg.fps;
}

void TrayTip(NOTIFYICONDATAW& nid) {
    std::wstring tip = L"Seamless FPS Capper: in-game cap ";
    if (!CapOn()) {
        tip += L"off. Click to turn it on.";
    } else {
        LONG ov = g_state ? g_state->capOverrideX100 : 0;
        tip += L"on";
        if (ov > 0) tip += L", " + FpsText(ov / 100.0) + L" fps for now";
        tip += L".";
    }
    wcsncpy_s(nid.szTip, tip.c_str(), _TRUNCATE);
}

void UpdateTray(bool add) {
    NOTIFYICONDATAW nid{sizeof(nid)};
    nid.hWnd = g_msgWnd;
    nid.uID = kTrayId;
    if (!g_trayIconOn) {
        if (g_trayAdded) Shell_NotifyIconW(NIM_DELETE, &nid);
        g_trayAdded = false;
        return;
    }
    HICON icon = MakeTrayIcon(CapOn());
    nid.uFlags = NIF_MESSAGE | NIF_ICON | NIF_TIP | NIF_SHOWTIP;
    nid.uCallbackMessage = WM_CAP_TRAY;
    nid.hIcon = icon ? icon : LoadIconW(nullptr, IDI_APPLICATION);
    TrayTip(nid);
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

// Registers every shortcut. One another app holds is retried every 10 s.
void RegisterHotkeys(bool all) {
    std::wstring problems;
    bool retry = false;
    for (int id = kHkToggle; id <= kHkCycle; id++) {
        if (!all && g_hotkeyOn[id]) continue;
        if (g_hotkeyOn[id]) UnregisterHotKey(g_msgWnd, id);
        g_hotkeyOn[id] = false;
        const std::wstring& text = g_hotkeyText[id];
        if (text.empty()) continue;
        UINT mods, vk;
        if (!Hotkey_Parse(text, mods, vk)) {
            Wh_Log(L"Shortcut \"%s\" isn't one the mod understands", text.c_str());
            continue;
        }
        g_hotkeyOn[id] = RegisterHotKey(g_msgWnd, id, mods | MOD_NOREPEAT, vk) != FALSE;
        if (!g_hotkeyOn[id]) {
            Wh_Log(L"Shortcut %s is taken by another app (error %lu)", text.c_str(), GetLastError());
            problems += (problems.empty() ? L"" : L", ") + text;
            retry = true;
        }
    }
    {
        std::lock_guard<std::mutex> lock(g_statusLock);
        g_hotkeyProblem = problems.empty() ? L"" : L"Another app holds " + problems + L". The mod keeps trying.";
    }
    if (retry) SetTimer(g_msgWnd, kRetryTimer, 10000, nullptr);
    else KillTimer(g_msgWnd, kRetryTimer);
}

void ReadToolConfig() {
    Config c = ReadConfig();
    {
        std::lock_guard<std::mutex> lock(g_cfgLock);
        g_cfg = c;
    }
    g_trayIconOn = c.tray;
    g_hotkeyText[kHkToggle] = c.toggleKey;
    g_hotkeyText[kHkUp] = c.upKey;
    g_hotkeyText[kHkDown] = c.downKey;
    g_hotkeyText[kHkCycle] = c.cycleKey;
    // With no tray icon and no shortcut nothing could turn the cap back on.
    if (!c.tray && c.toggleKey.empty() && g_state && g_state->toolDisabled) {
        g_state->toolDisabled = 0;
        Wh_SetIntValue(L"capOff", 0);
    }
    if (g_state) {
        g_state->capOverrideX100 = 0;
        InterlockedIncrement(&g_state->generation);
    }
    Wh_Log(L"Settings: %s, %s fps, %s, background %s", c.enabled ? L"on" : L"off", FpsText(c.fps).c_str(),
           ModeName(c.mode), FpsText(c.bg).c_str());
}

void SetCapOn(bool on, PCWSTR why) {
    if (g_state) {
        g_state->toolDisabled = on ? 0 : 1;
        InterlockedIncrement(&g_state->generation);
    }
    Wh_SetIntValue(L"capOff", on ? 0 : 1);
    Wh_Log(L"In-game cap %s (%s)", on ? L"on" : L"off", why);
    UpdateTray(false);
}

// The cap the shortcuts start from: the one set by them, else the game in
// front's own cap, else the Frame cap page.
double CurrentToolCap() {
    if (g_state && g_state->capOverrideX100 > 0) return g_state->capOverrideX100 / 100.0;
    DWORD pid = 0;
    if (HWND fg = GetForegroundWindow()) GetWindowThreadProcessId(fg, &pid);
    if (g_state && pid) {
        for (auto& s : g_state->slots)
            if ((DWORD)s.pid == pid && s.capX100 > 0) return s.capX100 / 100.0;
    }
    return GlobalFps();
}

void SetOverride(double fps, PCWSTR why) {
    fps = std::clamp(fps, 1.0, 1000.0);
    if (g_state) {
        g_state->capOverrideX100 = (LONG)(fps * 100 + 0.5);
        InterlockedIncrement(&g_state->generation);
    }
    Wh_Log(L"In-game cap now %s fps (%s)", FpsText(fps).c_str(), why);
    UpdateTray(false);
}

void StepCap(int dir) {
    double step;
    {
        std::lock_guard<std::mutex> lock(g_cfgLock);
        step = g_cfg.step;
    }
    SetOverride(CurrentToolCap() + dir * step, dir > 0 ? L"raise shortcut" : L"lower shortcut");
}

void CyclePreset() {
    std::vector<double> presets;
    {
        std::lock_guard<std::mutex> lock(g_cfgLock);
        presets = g_cfg.presets;
    }
    if (presets.empty()) return;
    double cur = CurrentToolCap();
    double next = presets.front();
    for (double p : presets)
        if (p > cur + 0.01) {
            next = p;
            break;
        }
    SetOverride(next, L"preset shortcut");
}

enum : UINT { IDM_TOGGLE = 100, IDM_SETTINGS, IDM_UP, IDM_DOWN };

void ShowTrayMenu(POINT pt) {
    int cmd = acset::ShowTrayMenu(g_msgWnd, &pt, CapOn(),
                                  g_hotkeyOn[kHkToggle] ? g_hotkeyText[kHkToggle].c_str() : L"");
    if (cmd == IDM_TOGGLE) SetCapOn(!CapOn(), L"tray menu");
    else if (cmd == IDM_SETTINGS) acset::OpenSettingsWindow();
    else if (cmd == IDM_UP) StepCap(1);
    else if (cmd == IDM_DOWN) StepCap(-1);
}

LRESULT CALLBACK MsgWndProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) {
    if (msg == g_taskbarCreated && g_taskbarCreated) {
        g_trayAdded = false;
        UpdateTray(true);
        return 0;
    }
    switch (msg) {
        case WM_HOTKEY:
            if (wp == kHkToggle) SetCapOn(!CapOn(), L"shortcut");
            else if (wp == kHkUp) StepCap(1);
            else if (wp == kHkDown) StepCap(-1);
            else if (wp == kHkCycle) CyclePreset();
            return 0;
        case WM_TIMER:
            if (wp == kRetryTimer) RegisterHotkeys(false);
            return 0;
        case WM_CAP_TRAY:
            switch (LOWORD(lp)) {
                case NIN_SELECT:
                case NIN_KEYSELECT: SetCapOn(!CapOn(), L"tray icon"); break;
                case WM_CONTEXTMENU: ShowTrayMenu(POINT{GET_X_LPARAM(wp), GET_Y_LPARAM(wp)}); break;
            }
            return 0;
        case WM_CAP_SETTINGS:
            ReadToolConfig();
            RegisterHotkeys(true);
            UpdateTray(false);
            KickWorker();
            if (HWND s = acset::g_settingsWnd) PostMessageW(s, WM_APP + 1 /* WM_APP_SETTINGS_RELOAD */, 0, 0);
            return 0;
    }
    return DefWindowProcW(hwnd, msg, wp, lp);
}

DWORD WINAPI UiThreadProc(LPVOID) {
    MSG msg;
    PeekMessageW(&msg, nullptr, WM_USER, WM_USER, PM_NOREMOVE);
    EnableDarkMenus();
    WNDCLASSW wc{};
    wc.lpfnWndProc = MsgWndProc;
    wc.hInstance = (HINSTANCE)windhawk_tool_mod::GetCurrentModuleHandle();
    wc.lpszClassName = L"SeamlessFpsCapperMsg";
    RegisterClassW(&wc);
    g_msgWnd = CreateWindowExW(WS_EX_TOOLWINDOW, wc.lpszClassName, L"Seamless FPS Capper", WS_POPUP, 0, 0, 0, 0,
                               nullptr, nullptr, wc.hInstance, nullptr);
    if (g_msgWnd) {
        // This copy runs as administrator; let Explorer's tray messages through.
        g_taskbarCreated = RegisterWindowMessageW(L"TaskbarCreated");
        ChangeWindowMessageFilterEx(g_msgWnd, g_taskbarCreated, MSGFLT_ALLOW, nullptr);
        ChangeWindowMessageFilterEx(g_msgWnd, WM_CAP_TRAY, MSGFLT_ALLOW, nullptr);
        RegisterHotkeys(true);
        UpdateTray(true);
    }
    SetEvent(g_uiReady);
    if (!g_msgWnd) return 1;
    while (GetMessageW(&msg, nullptr, 0, 0) > 0) {
        TranslateMessage(&msg);
        DispatchMessageW(&msg);
    }
    for (int id = kHkToggle; id <= kHkCycle; id++)
        if (g_hotkeyOn[id]) UnregisterHotKey(g_msgWnd, id);
    KillTimer(g_msgWnd, kRetryTimer);
    if (g_trayAdded) {
        NOTIFYICONDATAW nid{sizeof(nid)};
        nid.hWnd = g_msgWnd;
        nid.uID = kTrayId;
        Shell_NotifyIconW(NIM_DELETE, &nid);
        g_trayAdded = false;
    }
    if (g_trayIcon) DestroyIcon(g_trayIcon);
    g_trayIcon = nullptr;
    DestroyWindow(g_msgWnd);
    g_msgWnd = nullptr;
    UnregisterClassW(wc.lpszClassName, wc.hInstance);
    return 0;
}

void StopThread(HANDLE& t, DWORD tid) {
    if (!t) return;
    if (tid) PostThreadMessageW(tid, WM_QUIT, 0, 0);
    WaitForSingleObject(t, 5000);
    CloseHandle(t);
    t = nullptr;
}

}  // namespace

// ===========================================================================
// Settings window: the Seamless Launchpad settings GUI, the standard for every
// DavidHiFi mod. Generated by work\2026-11-12-seamless-autoclicker\gen.py.
// ===========================================================================
extern "C" IMAGE_DOS_HEADER __ImageBase;
namespace acset {
// The settings window, from the tray icon. It shows the same settings as
// Windhawk's page for this mod and saves them through windhawk-cli, so the two
// stay in step. Writing a mod's settings takes admin rights, so the save runs
// the CLI elevated (silently where UAC prompts are off).

constexpr WCHAR kSettingsClass[] = L"WindhawkSeamlessFpsCapperSettings";
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
// Generated by work\2026-11-26-fps-suite\capper\assemble.py from spec.py.
static std::vector<SetField> Set_MakeFields() {
    using K = SetField;
    return {
{K::Check, L"capEnabled", L"Cap frame rates", L"Off, nothing is capped: in-game caps stop and the driver caps this mod manages go to none.", L"1", {}, 0, 100, 0, L"Cap"},
{K::Text, L"fps", L"Frame rate cap", L"Frames per second for every game without its own cap. In game, decimals work, like 141.5. The driver cap rounds to a whole number.", L"157", {}, 0, 100, 0, L"Cap"},
{K::Choice, L"mode", L"How it caps", L"Driver works in every game, anti-cheat ones too, from the next time the game starts. The in-game ways cap only the games on the Games page.", L"async", {{L"driver", L"Driver cap (NVIDIA, every game)"}, {L"async", L"In game, smooth (async)"}, {L"front", L"In game, front edge sync"}, {L"back", L"In game, back edge sync"}, {L"reflex", L"In game, NVIDIA Reflex"}}, 0, 100, 0, L"Cap"},
{K::Number, L"bgFps", L"Background cap", L"Frames per second while the game is not the window in front. 0 is off.", L"0", {}, 0, 1000, 0, L"Cap"},
{K::Choice, L"waitMode", L"Waiting between frames", L"Passive lets the processor rest between frames. Busy spins for the steadiest frame times and keeps one core busy.", L"passive", {{L"passive", L"Passive (light)"}, {L"busy", L"Busy (steadiest)"}}, 0, 100, 0, L"Fine tuning"},
{K::Choice, L"lowLatency", L"Driver low latency", L"NVIDIA Low Latency Mode for every game. Leave keeps what the NVIDIA app or control panel set.", L"leave", {{L"leave", L"Leave as it is"}, {L"off", L"Off"}, {L"on", L"On"}, {L"ultra", L"Ultra"}}, 0, 100, 0, L"Fine tuning"},
{K::Check, L"driverCap", L"Let this mod set the NVIDIA driver cap", L"Off puts every driver value this mod changed back exactly as it was, and the driver cap is left alone.", L"0", {}, 0, 100, 0, L"Driver"},
{K::Text, L"gameFolders", L"Cap every game in these folders", L"Folders separated by ;, like D:\\Games;E:\\SteamLibrary. Every game under them gets the in-game cap and way from the Frame cap page. Anti-cheat games are skipped.", L"", {}, 0, 100, 1, L"Game folders"},
{K::Text, L"game1Exe", L"Game", L"The game's exe name, like game.exe. Empty frees this slot.", L"plutonium-bootstrapper-win32.exe", {}, 0, 100, 1, L"Game 1"},
{K::Check, L"game1On", L"Cap this game", L"Off, this game is left alone.", L"1", {}, 0, 100, 1, L"Game 1"},
{K::Text, L"game1Fps", L"Frame rate cap", L"Empty uses the cap on the Frame cap page.", L"120", {}, 0, 100, 1, L"Game 1"},
{K::Choice, L"game1Mode", L"How it caps", L"Anti-cheat games always use the driver cap.", L"driver", {{L"global", L"Same as the Frame cap page"}, {L"driver", L"Driver cap (NVIDIA, every game)"}, {L"async", L"In game, smooth (async)"}, {L"front", L"In game, front edge sync"}, {L"back", L"In game, back edge sync"}, {L"reflex", L"In game, NVIDIA Reflex"}}, 0, 100, 1, L"Game 1"},
{K::Text, L"game1Bg", L"Background cap", L"Empty uses the Frame cap page. 0 is off.", L"", {}, 0, 100, 1, L"Game 1"},
{K::Text, L"game2Exe", L"Game", L"The game's exe name, like game.exe. Empty frees this slot.", L"", {}, 0, 100, 1, L"Game 2"},
{K::Check, L"game2On", L"Cap this game", L"Off, this game is left alone.", L"1", {}, 0, 100, 1, L"Game 2"},
{K::Text, L"game2Fps", L"Frame rate cap", L"Empty uses the cap on the Frame cap page.", L"", {}, 0, 100, 1, L"Game 2"},
{K::Choice, L"game2Mode", L"How it caps", L"Anti-cheat games always use the driver cap.", L"global", {{L"global", L"Same as the Frame cap page"}, {L"driver", L"Driver cap (NVIDIA, every game)"}, {L"async", L"In game, smooth (async)"}, {L"front", L"In game, front edge sync"}, {L"back", L"In game, back edge sync"}, {L"reflex", L"In game, NVIDIA Reflex"}}, 0, 100, 1, L"Game 2"},
{K::Text, L"game2Bg", L"Background cap", L"Empty uses the Frame cap page. 0 is off.", L"", {}, 0, 100, 1, L"Game 2"},
{K::Text, L"game3Exe", L"Game", L"The game's exe name, like game.exe. Empty frees this slot.", L"", {}, 0, 100, 1, L"Game 3"},
{K::Check, L"game3On", L"Cap this game", L"Off, this game is left alone.", L"1", {}, 0, 100, 1, L"Game 3"},
{K::Text, L"game3Fps", L"Frame rate cap", L"Empty uses the cap on the Frame cap page.", L"", {}, 0, 100, 1, L"Game 3"},
{K::Choice, L"game3Mode", L"How it caps", L"Anti-cheat games always use the driver cap.", L"global", {{L"global", L"Same as the Frame cap page"}, {L"driver", L"Driver cap (NVIDIA, every game)"}, {L"async", L"In game, smooth (async)"}, {L"front", L"In game, front edge sync"}, {L"back", L"In game, back edge sync"}, {L"reflex", L"In game, NVIDIA Reflex"}}, 0, 100, 1, L"Game 3"},
{K::Text, L"game3Bg", L"Background cap", L"Empty uses the Frame cap page. 0 is off.", L"", {}, 0, 100, 1, L"Game 3"},
{K::Text, L"game4Exe", L"Game", L"The game's exe name, like game.exe. Empty frees this slot.", L"", {}, 0, 100, 1, L"Game 4"},
{K::Check, L"game4On", L"Cap this game", L"Off, this game is left alone.", L"1", {}, 0, 100, 1, L"Game 4"},
{K::Text, L"game4Fps", L"Frame rate cap", L"Empty uses the cap on the Frame cap page.", L"", {}, 0, 100, 1, L"Game 4"},
{K::Choice, L"game4Mode", L"How it caps", L"Anti-cheat games always use the driver cap.", L"global", {{L"global", L"Same as the Frame cap page"}, {L"driver", L"Driver cap (NVIDIA, every game)"}, {L"async", L"In game, smooth (async)"}, {L"front", L"In game, front edge sync"}, {L"back", L"In game, back edge sync"}, {L"reflex", L"In game, NVIDIA Reflex"}}, 0, 100, 1, L"Game 4"},
{K::Text, L"game4Bg", L"Background cap", L"Empty uses the Frame cap page. 0 is off.", L"", {}, 0, 100, 1, L"Game 4"},
{K::Text, L"game5Exe", L"Game", L"The game's exe name, like game.exe. Empty frees this slot.", L"", {}, 0, 100, 1, L"Game 5"},
{K::Check, L"game5On", L"Cap this game", L"Off, this game is left alone.", L"1", {}, 0, 100, 1, L"Game 5"},
{K::Text, L"game5Fps", L"Frame rate cap", L"Empty uses the cap on the Frame cap page.", L"", {}, 0, 100, 1, L"Game 5"},
{K::Choice, L"game5Mode", L"How it caps", L"Anti-cheat games always use the driver cap.", L"global", {{L"global", L"Same as the Frame cap page"}, {L"driver", L"Driver cap (NVIDIA, every game)"}, {L"async", L"In game, smooth (async)"}, {L"front", L"In game, front edge sync"}, {L"back", L"In game, back edge sync"}, {L"reflex", L"In game, NVIDIA Reflex"}}, 0, 100, 1, L"Game 5"},
{K::Text, L"game5Bg", L"Background cap", L"Empty uses the Frame cap page. 0 is off.", L"", {}, 0, 100, 1, L"Game 5"},
{K::Text, L"game6Exe", L"Game", L"The game's exe name, like game.exe. Empty frees this slot.", L"", {}, 0, 100, 1, L"Game 6"},
{K::Check, L"game6On", L"Cap this game", L"Off, this game is left alone.", L"1", {}, 0, 100, 1, L"Game 6"},
{K::Text, L"game6Fps", L"Frame rate cap", L"Empty uses the cap on the Frame cap page.", L"", {}, 0, 100, 1, L"Game 6"},
{K::Choice, L"game6Mode", L"How it caps", L"Anti-cheat games always use the driver cap.", L"global", {{L"global", L"Same as the Frame cap page"}, {L"driver", L"Driver cap (NVIDIA, every game)"}, {L"async", L"In game, smooth (async)"}, {L"front", L"In game, front edge sync"}, {L"back", L"In game, back edge sync"}, {L"reflex", L"In game, NVIDIA Reflex"}}, 0, 100, 1, L"Game 6"},
{K::Text, L"game6Bg", L"Background cap", L"Empty uses the Frame cap page. 0 is off.", L"", {}, 0, 100, 1, L"Game 6"},
{K::Text, L"game7Exe", L"Game", L"The game's exe name, like game.exe. Empty frees this slot.", L"", {}, 0, 100, 1, L"Game 7"},
{K::Check, L"game7On", L"Cap this game", L"Off, this game is left alone.", L"1", {}, 0, 100, 1, L"Game 7"},
{K::Text, L"game7Fps", L"Frame rate cap", L"Empty uses the cap on the Frame cap page.", L"", {}, 0, 100, 1, L"Game 7"},
{K::Choice, L"game7Mode", L"How it caps", L"Anti-cheat games always use the driver cap.", L"global", {{L"global", L"Same as the Frame cap page"}, {L"driver", L"Driver cap (NVIDIA, every game)"}, {L"async", L"In game, smooth (async)"}, {L"front", L"In game, front edge sync"}, {L"back", L"In game, back edge sync"}, {L"reflex", L"In game, NVIDIA Reflex"}}, 0, 100, 1, L"Game 7"},
{K::Text, L"game7Bg", L"Background cap", L"Empty uses the Frame cap page. 0 is off.", L"", {}, 0, 100, 1, L"Game 7"},
{K::Text, L"game8Exe", L"Game", L"The game's exe name, like game.exe. Empty frees this slot.", L"", {}, 0, 100, 1, L"Game 8"},
{K::Check, L"game8On", L"Cap this game", L"Off, this game is left alone.", L"1", {}, 0, 100, 1, L"Game 8"},
{K::Text, L"game8Fps", L"Frame rate cap", L"Empty uses the cap on the Frame cap page.", L"", {}, 0, 100, 1, L"Game 8"},
{K::Choice, L"game8Mode", L"How it caps", L"Anti-cheat games always use the driver cap.", L"global", {{L"global", L"Same as the Frame cap page"}, {L"driver", L"Driver cap (NVIDIA, every game)"}, {L"async", L"In game, smooth (async)"}, {L"front", L"In game, front edge sync"}, {L"back", L"In game, back edge sync"}, {L"reflex", L"In game, NVIDIA Reflex"}}, 0, 100, 1, L"Game 8"},
{K::Text, L"game8Bg", L"Background cap", L"Empty uses the Frame cap page. 0 is off.", L"", {}, 0, 100, 1, L"Game 8"},
{K::Hotkey, L"toggleHotkey", L"Turn the in-game cap on or off", L"Press the keys in the box. Backspace clears it. It starts as MSI Afterburner's limiter key. The tray icon does the same.", L"Ctrl+Alt+Shift+/", {}, 0, 100, 2, L"Shortcuts"},
{K::Hotkey, L"capUpHotkey", L"Raise the cap", L"Adds the step below to the in-game cap until Windhawk restarts or you save new settings.", L"", {}, 0, 100, 2, L"Shortcuts"},
{K::Hotkey, L"capDownHotkey", L"Lower the cap", L"Takes the step below off the in-game cap.", L"", {}, 0, 100, 2, L"Shortcuts"},
{K::Number, L"capStep", L"Step (frames per second)", L"How much one press of raise or lower changes the cap.", L"5", {}, 1, 100, 2, L"Shortcuts"},
{K::Hotkey, L"cycleHotkey", L"Next preset cap", L"Moves the in-game cap to the next frame rate in the list below.", L"", {}, 0, 100, 2, L"Presets"},
{K::Text, L"presetCaps", L"Preset caps", L"Frame rates separated by commas.", L"60, 120, 144, 157", {}, 0, 100, 2, L"Presets"},
{K::Check, L"settingsGlass", L"Blurred settings window", L"On, the settings window is see-through glass with Windows acrylic behind it. Off, it is solid. Applies when you save.", L"1", {}, 0, 100, 3, L"Settings window"},
{K::Check, L"nativeSettingsTitleBar", L"Native Windows title bar", L"Use the Windows title bar and window buttons for this settings window. Applies when you save.", L"0", {}, 0, 100, 3, L"Settings window"},
{K::Check, L"settingsTrayIcon", L"Tray icon", L"Click it to turn the in-game cap on or off. Right-click it for these settings. When off, change settings in Windhawk.", L"1", {}, 0, 100, 3, L"Settings window"}
    };
}

struct SetPageInfo {
    PCWSTR name, intro;
    WCHAR glyph;
};
static const SetPageInfo kSetPages[] = {
{L"Frame cap", L"One cap for every game, how it waits and what happens while a game is in the background.", 0xE916},
{L"Games", L"Games with their own cap, and folders where every game gets the cap. Type the exe name, then save.", 0xE7FC},
{L"Shortcuts", L"Keys that turn the in-game cap on or off, raise it, lower it or step through presets.", 0xE765},
{L"Look", L"Choose how this settings window looks and whether its tray icon is shown.", 0xE790},
{L"About", L"Version, credits, support and links.", 0xE946},
};
constexpr int kSetPageCount = (int)(sizeof(kSetPages) / sizeof(kSetPages[0]));
// About sits apart at the end of the sidebar, as in Seamless Dictate.
constexpr int kSetAboutPage = kSetPageCount - 1;
constexpr float kSetAboutGap = 17;
constexpr int kSetDropMax = 9;  // A dropdown with more options than this scrolls.

// All sizes are DIPs; the render target does the scaling.
constexpr float kSetPadX = 40, kSetMaxW = 720, kSetRowMin = 56, kSetRowGap = 8, kSetBoxH = 32, kSetRowPad = 16,
                kSetDropItem = 32, kSetRailTop = 76, kSetRailItem = 36, kSetRailPitch = 40;
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
constexpr PCWSTR kSetPaletteUrl = L"https://github.com/catppuccin/catppuccin";
constexpr PCWSTR kSetRepoUrl = L"https://github.com/DavidHiFi/davids-windhawk-mods";
constexpr PCWSTR kSetBugUrl =
    L"https://github.com/DavidHiFi/davids-windhawk-mods/issues/new?title=%5BSeamless%20FPS%20Capper%5D%20";
constexpr PCWSTR kSetTitle = L"Seamless FPS Capper";
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
    bool nativeButtons = false;  // Own title bar, but Windows draws minimize, maximize and close.
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
    return Capper_StatusText();
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
        if (w.fRailName && Set_TextW(w.fRailName.get(), L"FPS Capper") <= railW) break;
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

// ---- Layout -----------------------------------------------------------------

// The right-hand control's width, so the label column knows how much room it has.
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
    if (w.page == 0 || w.page == 1) {
        std::wstring status = w.page == 1 ? Capper_GamesBanner() : Set_KeyStatusText();
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
        add(SetItem::Link, 56, L"Colours from Catppuccin Mocha", L"By the Catppuccin team, MIT", kSetPaletteUrl);
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
        const WCHAR glyph = 0xE8B0;
        auto br = p.G({mc.x - 19, mc.y - 19, mc.x + 19, mc.y + 19});
        if (br) p.rt->DrawText(&glyph, 1, w.fIconL.get(), mark, br.get());
        p.rt->SetTransform(old);
    }
    float x = mark.right + 20;
    p.Text(w.fBig.get(), L"Seamless FPS Capper", {x, row.top + 18, row.right - 16, row.top + 46}, mocha::text);
#ifdef WH_MOD_VERSION
    std::wstring ver = std::wstring(L"Version ") + WH_MOD_VERSION + L"  \u00B7  GPL-3.0  \u00B7  A Windhawk mod";
#else
    std::wstring ver = L"GPL-3.0  \u00B7  A Windhawk mod";
#endif
    p.Text(w.fHint.get(), ver, {x, row.top + 48, row.right - 16, row.top + 68}, mocha::subtext0);
    p.Text(w.fHint.get(), L"Hold a mouse button and left click keeps clicking. Lock it on, or switch it off from the tray.",
           {x, row.top + 72, row.right - 16, row.top + 110}, mocha::subtext1);
    p.Text(w.fHint.get(), L"Made by DavidHiFi. Original work, free and open source.",
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
    p.Text(w.fRailName.get(), L"FPS Capper", {d.left + 90, d.top + 32, d.left + w.railW - 10, d.top + 56}, mocha::text, textA);
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
    const WCHAR mark = 0xE8B0;
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
    HWND hwnd = CreateWindowExW(0, kSettingsClass, L"Seamless FPS Capper settings", style,
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
// The tray menu: the engine's own menu (Set_TrayMenu), rows in the order they always had.
int ShowTrayMenu(HWND owner, const POINT* at, bool on, PCWSTR hotkey) {
    return Set_TrayMenu(owner, {Set_MenuRow(100, L"", L"In-game cap on", on, false, hotkey),
                                Set_MenuRow(102, L"", L"Raise cap"),
                                Set_MenuRow(103, L"", L"Lower cap"),
                                Set_MenuSep(),
                                Set_MenuRow(101, L"", L"Settings")}, at);
}
}  // namespace acset

// ===========================================================================
// Windhawk entry points. In windhawk.exe the launcher starts the tool. In a
// game on the list the game half starts and no tool is launched. Everywhere
// else the mod unloads at once.
// ===========================================================================

BOOL WhToolLauncher_ModInit(BOOL* bLaunch) {
    WCHAR path[MAX_PATH];
    DWORD n = GetModuleFileNameW(nullptr, path, MAX_PATH);
    if (!n || n == MAX_PATH) return FALSE;
    std::wstring exe = Lower(BaseName(path));
    // Windhawk 1.7.3 starts tool mods from windhawk.exe; 2.0 runs them in
    // its own helpers and starts the elevated one because the header lists it.
    if (exe == L"windhawk.exe" || exe == L"windhawk-mod.exe" || exe == L"windhawk-mod-elevated.exe")
        return TRUE;
    *bLaunch = FALSE;
    if (!GameWanted(path)) return FALSE;
    g_tls = TlsAlloc();
    if (g_tls == TLS_OUT_OF_INDEXES) return FALSE;
    OpenState();
    LoadGameSettings();
    ClaimSlot();
    g_inGame.store(true);
    g_hookThread = CreateThread(nullptr, 0, GameHookThread, nullptr, 0, nullptr);
    if (!g_hookThread) {
        ReleaseSlot();
        CloseState();
        TlsFree(g_tls);
        g_tls = TLS_OUT_OF_INDEXES;
        return FALSE;
    }
    Wh_Log(L"In-game cap loaded into %s", exe.c_str());
    return TRUE;
}

void WhToolLauncher_ModSettingsChanged(BOOL* bReload) {
    if (!g_inGame.load()) return;  // windhawk.exe keeps the default reload.
    *bReload = FALSE;  // A reload would hook the game again; read in place.
    LoadGameSettings();
}

void WhToolLauncher_ModBeforeUninit() {
    if (!g_inGame.load()) return;
    g_unloading.store(true);
    if (g_hookThread) {
        WaitForSingleObject(g_hookThread, 5000);
        CloseHandle(g_hookThread);
        g_hookThread = nullptr;
    }
}

void WhToolLauncher_ModUninit() {
    if (!g_inGame.load()) return;
    g_unloading.store(true);
    // Hooks are off now; wait for calls still inside our code.
    for (int i = 0; i < 200 && g_inFlight.load() > 0; i++) Sleep(10);
    ReflexRelease();
    ReleaseSlot();
    {
        std::lock_guard<std::mutex> lock(g_threadsLock);
        for (ThreadData* t : g_threads) {
            if (t->timer) CloseHandle(t->timer);
            t->timer = nullptr;
        }
        // The ThreadData blocks stay: another thread's TLS still points at
        // them and freeing would race a late call. A few bytes per thread.
    }
    if (g_tls != TLS_OUT_OF_INDEXES) TlsFree(g_tls);
    g_tls = TLS_OUT_OF_INDEXES;
    CloseState();
    g_inGame.store(false);
}

BOOL WhTool_ModInit() {
    // NVIDIA driver profiles and the mod's own Windhawk entry need
    // administrator rights. Windhawk 2.0 already runs this in its elevated
    // helper. 1.7.3 runs it from an unelevated windhawk.exe: relaunch that one
    // elevated (UAC prompts are off on this PC) and let this copy exit.
    WCHAR hostPath[MAX_PATH] = L"";
    GetModuleFileNameW(nullptr, hostPath, MAX_PATH);
    if (!IsElevated() && Lower(BaseName(hostPath)) == L"windhawk.exe") {
        WCHAR self[MAX_PATH];
        if (GetModuleFileNameW(nullptr, self, MAX_PATH)) {
            SHELLEXECUTEINFOW launch{sizeof(launch)};
            launch.fMask = SEE_MASK_FLAG_NO_UI;
            launch.lpVerb = L"runas";
            launch.lpFile = self;
            launch.lpParameters = L"-windhawk-tool-mod \"" WH_MOD_ID L"\"";
            // Not SW_HIDE: Windows applies the launch show state to the first
            // window the process shows, which would be the settings window.
            launch.nShow = SW_SHOWNORMAL;
            if (ShellExecuteExW(&launch)) ExitProcess(0);
        }
        Wh_Log(L"Elevated relaunch failed, running unelevated: no driver cap or game list");
    } else if (!IsElevated()) {
        Wh_Log(L"Running unelevated: no driver cap or game list");
    }

    g_instanceMutex = CreateMutexW(nullptr, FALSE, L"Global\\SeamlessFpsCapper");
    if (g_instanceMutex && GetLastError() == ERROR_ALREADY_EXISTS) {
        CloseHandle(g_instanceMutex);
        g_instanceMutex = nullptr;
        ExitProcess(0);
    }
    if (HANDLE boxThread = CreateThread(nullptr, 0, FalseFailureBoxThreadProc, nullptr, 0, nullptr))
        CloseHandle(boxThread);

    if (OpenState()) {
        g_state->toolPid = (LONG)GetCurrentProcessId();
        g_state->toolDisabled = Wh_GetIntValue(L"capOff", 0) ? 1 : 0;
        g_state->capOverrideX100 = 0;
    }
    ReadToolConfig();

    g_workEvent = CreateEventW(nullptr, FALSE, FALSE, nullptr);
    g_workThread = g_workEvent ? CreateThread(nullptr, 0, WorkThreadProc, nullptr, 0, nullptr) : nullptr;
    KickWorker();
    g_uiReady = CreateEventW(nullptr, TRUE, FALSE, nullptr);
    g_uiThread = CreateThread(nullptr, 0, UiThreadProc, nullptr, 0, &g_uiThreadId);
    if (g_uiThread && g_uiReady) WaitForSingleObject(g_uiReady, 10000);
    if (g_uiReady) CloseHandle(g_uiReady);
    g_uiReady = nullptr;
    if (!g_workThread || !g_uiThread) {
        Wh_Log(L"Couldn't start: %u", GetLastError());
        WhTool_ModUninit();
        return FALSE;
    }
    Wh_Log(L"Started, in-game cap %s", CapOn() ? L"on" : L"off");
    return TRUE;
}

void WhTool_ModSettingsChanged() {
    if (g_msgWnd) PostMessageW(g_msgWnd, WM_CAP_SETTINGS, 0, 0);
    else {
        ReadToolConfig();
        KickWorker();
    }
}

void WhTool_ModUninit() {
    g_stop.store(true, std::memory_order_relaxed);
    acset::CloseSettingsWindow();
    StopThread(g_uiThread, g_uiThreadId);
    if (g_workEvent) SetEvent(g_workEvent);
    StopThread(g_workThread, 0);
    // Turned off or removed in Windhawk: put the driver back and take the
    // games off the list. A plain Windhawk exit (shutdown) keeps both.
    DWORD disabled = 0;
    bool present = ModKeyExists(&disabled);
    if (!present || disabled) {
        Wh_Log(L"Mod %s: putting the driver back", present ? L"turned off" : L"removed");
        ApplyDriver({});
        if (present) {
            Config c;
            {
                std::lock_guard<std::mutex> lock(g_cfgLock);
                c = g_cfg;
            }
            ApplyIncludes(c, true);
        }
    }
    if (g_workEvent) CloseHandle(g_workEvent);
    g_workEvent = nullptr;
    if (g_state && g_state->toolPid == (LONG)GetCurrentProcessId()) {
        g_state->toolPid = 0;
        g_state->capOverrideX100 = 0;
    }
    CloseState();
    if (g_instanceMutex) {
        CloseHandle(g_instanceMutex);
        g_instanceMutex = nullptr;
    }
}
