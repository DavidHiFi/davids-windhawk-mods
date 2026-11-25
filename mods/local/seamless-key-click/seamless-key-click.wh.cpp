// ==WindhawkMod==
// @id              seamless-key-click
// @name            Seamless Key Click
// @description     Mechanical keyboard and mouse sounds as you type and click, with every Keyboard Sounds pack, shortcuts and a tray icon
// @version         1.1.8
// @author          DavidHiFi, Anixx
// @github          https://github.com/DavidHiFi
// @homepage        https://github.com/DavidHiFi/davids-windhawk-mods
// @include         windhawk.exe
// @architecture    x86-64
// @compilerOptions -lgdi32 -luser32 -lshell32 -lshlwapi -lole32 -loleaut32 -luuid -ld2d1 -ldwrite -lwindowscodecs -ldwmapi -lcomctl32 -luxtheme -lcomdlg32 -limm32 -ladvapi32 -lxaudio2_9 -lmfplat -lmfreadwrite -lmfuuid -lurlmon -lwininet -lruntimeobject
// @license         GPL-3.0
// @donateUrl       https://ko-fi.com/DavidHiFi
// ==/WindhawkMod==

// ==WindhawkModReadme==
/*
# Seamless Key Click

Plays the sound of a real mechanical keyboard as you type, and a mouse click as
you click. It runs in the background on its own, so it doesn't touch Explorer or
any app you type in.

![Seamless Key Click settings](https://raw.githubusercontent.com/DavidHiFi/davids-windhawk-mods/main/media/previews/seamless-key-click.png)

## What it does

- Each key has its own sound in packs that record them, so Space, Enter and
  Backspace sound like the real thing.
- Packs with release sounds play the key coming back up as well.
- Random pitch, so fast typing sounds less like a loop.
- Mouse clicks get their own pack and their own volume.
- Sounds overlap like a real keyboard. Pick how many can play at once.
- A held key clicks once, or with every repeat if you prefer.
- Turn sounds off in some apps, or play them only in a few.
- Shortcuts turn all sounds, keyboard sounds or mouse sounds on and off, and
  change the volume. The default is Ctrl+Alt+K for all sounds.
- Switches for all sounds, keyboard sounds and mouse sounds, in the settings
  window, the tray menu and the shortcuts, always in step.
- A small glass notifier dock says what a shortcut or the tray menu changed:
  sounds on or off, the new volume with a level bar, or the pack you picked.
  Pick its corner, screen, size, look and how long it stays on the Look page.
- A tray icon: click it for settings, right-click it to mute or pick a pack.
- Follows your default speakers or headphones when you switch them.

## Sound packs

- Alpaca (kbsim)
- SteelSeries Apex Pro TKL (Akira)
- Banana Split switches (Akira)
- Gateron Black Ink (kbsim)
- Gateron Red Ink (kbsim)
- Holy Panda (kbsim)
- iPhone keyboard
- Logitech G915 TKL, brown switches
- Cherry MX Black (kbsim)
- Cherry MX Blue (kbsim)
- Cherry MX Brown (kbsim)
- Cherry MX Speed Silver (Mechvibes)
- NovelKeys Cream (Mechvibes)
- Opera GX browser (Mechvibes)
- Telios V2 linear (Mechvibes)
- Antique typewriter (Mechvibes)
- Classic tick (the original Key Click)
- Logitech G502 X Wireless

The Keyboard Sounds packs download from GitHub the first time you pick one, and
stay in the sound packs folder after that. Open the folder from the tray menu.

## Your own packs

Any Keyboard Sounds profile works: a folder with a profile.yaml and its sound
files (wav or mp3). Put the folder in the sound packs folder and pick "My own
pack", then type the folder name. A full path to a folder anywhere else works
too. Packs made in the Keyboard Sounds app, including ones cut from a single
recording, load as they are.

## Credits

Based on Key Click by Anixx, the original Windhawk mod, whose tick is kept here
as the Classic pack.

Sound packs and the profile format come from Keyboard Sounds by Nathan
Fiscaletti (https://github.com/nathan-fiscaletti/keyboardsounds), GPL-3.0. Each
pack keeps the credit its author gave it.
*/
// ==/WindhawkModReadme==

// ==WindhawkModSettings==
/*
- soundsOn: true
  $name: "Sounds on"
  $description: "Turns every sound on or off. The shortcut and the tray menu switch this too."
- keyboardSounds: true
  $name: "Keyboard sounds"
  $description: "A sound for each key you press."
- mouseSounds: true
  $name: "Mouse sounds"
  $description: "A sound for each click. Pick a mouse pack below too."
- keyboardPack: "alpaca"
  $name: "Keyboard sound pack"
  $description: "The keyboard each key press sounds like. Every pack from Keyboard Sounds is here."
  $options:
  - alpaca: "Alpaca (kbsim)"
  - apex-pro-tkl-v2: "SteelSeries Apex Pro TKL (Akira)"
  - banana-split: "Banana Split switches (Akira)"
  - gateron-black-ink: "Gateron Black Ink (kbsim)"
  - gateron-red-ink: "Gateron Red Ink (kbsim)"
  - holy-panda: "Holy Panda (kbsim)"
  - ios: "iPhone keyboard"
  - logitech-g915-tkl-brown: "Logitech G915 TKL, brown switches"
  - mx-black: "Cherry MX Black (kbsim)"
  - mx-blue: "Cherry MX Blue (kbsim)"
  - mx-brown: "Cherry MX Brown (kbsim)"
  - mx-speed-silver: "Cherry MX Speed Silver (Mechvibes)"
  - nk-cream: "NovelKeys Cream (Mechvibes)"
  - opera-gx: "Opera GX browser (Mechvibes)"
  - telios-v2: "Telios V2 linear (Mechvibes)"
  - typewriter: "Antique typewriter (Mechvibes)"
  - classic: "Classic tick (the original Key Click)"
  - custom: "My own pack (named below)"
  - none: "No keyboard sounds"
- keyboardCustomPack: ""
  $name: "Your own keyboard pack"
  $description: "Used when the pack above is \"My own pack\". The name of a folder in the sound packs folder, or the full path of any Keyboard Sounds profile folder (one with a profile.yaml in it)."
- mousePack: "none"
  $name: "Mouse sound pack"
  $description: "The mouse each click sounds like."
  $options:
  - g502x-wireless: "Logitech G502 X Wireless"
  - custom: "My own pack (named below)"
  - none: "No mouse sounds"
- mouseCustomPack: ""
  $name: "Your own mouse pack"
  $description: "Used when the mouse pack is \"My own pack\". A folder name or a full path, as above."
- packsFolder: ""
  $name: "Sound packs folder"
  $description: "Where the packs are kept. Leave it empty to use the mod's own folder. Open it from the tray icon's menu."
- downloadPacks: true
  $name: "Download missing packs"
  $description: "When a pack you pick is not in the folder, fetch it from the Keyboard Sounds project on GitHub."
- volume: 70
  $name: "Volume"
  $description: "0 to 100 (Suggested: 70). The volume shortcuts change this too."
- mouseVolume: 100
  $name: "Mouse volume (% of the volume)"
  $description: "0 to 100 (Suggested: 100). Mouse clicks play at this share of the volume above."
- pitchShift: false
  $name: "Random pitch"
  $description: "Each sound plays a little higher or lower, so fast typing sounds less repetitive."
- pitchLow: -2
  $name: "Lowest pitch (semitones)"
  $description: "-12 to 12 (Suggested: -2)."
- pitchHigh: 2
  $name: "Highest pitch (semitones)"
  $description: "-12 to 12 (Suggested: 2)."
- pitchApplies: "both"
  $name: "Random pitch for"
  $description: "Which sounds get the random pitch."
  $options:
  - both: "Keyboard and mouse"
  - keyboard: "Keyboard only"
  - mouse: "Mouse only"
- releaseSounds: true
  $name: "Release sounds"
  $description: "Play the sound of a key or button coming back up, for packs that have one."
- repeatHeldKeys: false
  $name: "Click while a key is held"
  $description: "Off, a held key sounds once. On, it clicks again with every repeat, like the original Key Click. Shift, Ctrl, Alt and Windows never repeat."
- ignoreInjected: true
  $name: "Skip typing from other programs"
  $description: "No sound for keys and clicks sent by macro tools, on-screen keyboards and remote desktop apps."
- sideButtons: false
  $name: "Side mouse buttons"
  $description: "Also click for the back and forward buttons, with the pack's main click."
- maxOverlap: 32
  $name: "Sounds at once"
  $description: "1 to 64 (Suggested: 32). How many sounds can overlap. The oldest stops when a new one needs room."
- appMode: "enable"
  $name: "Apps"
  $description: "Where sounds play when an app is in none of the lists below."
  $options:
  - enable: "Play in every app"
  - disable: "Play only in the \"Play in\" apps"
- playApps: ""
  $name: "Play in"
  $description: "Apps that always make sounds. Program names or full paths, split with \";\", such as notepad.exe; code.exe. * and ? work as wildcards."
- silentApps: ""
  $name: "Silent in"
  $description: "Apps that never make sounds, such as a game or a video call app."
- onlyApps: ""
  $name: "Only in"
  $description: "When set, sounds play only while one of these apps is in front, and the lists above are ignored."
- toggleHotkey: "Ctrl+Alt+K"
  $name: "Turn all sounds on or off"
  $description: "Press the keys in the box. Backspace clears it."
- keyboardHotkey: ""
  $name: "Turn keyboard sounds on or off"
- mouseHotkey: ""
  $name: "Turn mouse sounds on or off"
- volumeUpHotkey: ""
  $name: "Volume up"
- volumeDownHotkey: ""
  $name: "Volume down"
- volumeStep: 10
  $name: "Volume step"
  $description: "1 to 50 (Suggested: 10). How much each volume shortcut changes the volume."
- toggleCue: true
  $name: "Click when sounds come back on"
  $description: "A shortcut or the tray menu plays one click when it turns sounds on, so you hear that it worked."
- notifierOn: true
  $name: "Notifier dock"
  $description: "A small dock pops up when a shortcut or the tray menu turns sounds on or off, changes the volume or picks a pack."
- notifierSounds: true
  $name: "Show it for sounds on or off"
- notifierVolume: true
  $name: "Show it for volume changes"
  $description: "With a level bar for the new volume."
- notifierPacks: true
  $name: "Show it for pack changes"
- notifierPosition: "bottomCenter"
  $name: "Where it shows"
  $description: "The corner or edge of the screen. The taskbar is never covered."
  $options:
  - topLeft: "Top left"
  - topCenter: "Top middle"
  - topRight: "Top right"
  - center: "Middle of the screen"
  - bottomLeft: "Bottom left"
  - bottomCenter: "Bottom middle"
  - bottomRight: "Bottom right"
- notifierDisplay: "focused"
  $name: "Which screen"
  $description: "With more than one monitor, the one the dock shows on."
  $options:
  - focused: "The screen with the window in front"
  - cursor: "The screen with the pointer"
  - primary: "The main screen"
- notifierMargin: 48
  $name: "Distance from the edge"
  $description: "0 to 400 (Suggested: 48). Pixels between the dock and the screen edge."
- notifierDuration: 1800
  $name: "How long it stays (ms)"
  $description: "500 to 10000 (Suggested: 1800). Moving the pointer onto it hides it at once."
- notifierSize: "normal"
  $name: "Size"
  $description: "How big the dock and its text are."
  $options:
  - compact: "Compact"
  - normal: "Normal"
  - large: "Large"
- notifierLook: "glass"
  $name: "Look"
  $description: "Glass is blurred and see-through with a Mocha tint, like the settings window. Solid is plain Mocha."
  $options:
  - glass: "Glass"
  - solid: "Solid"
- notifierTint: 62
  $name: "Glass tint (%)"
  $description: "30 to 100 (Suggested: 62). How much Mocha colour lies over the blur. Higher is darker and easier to read."
- notifierFullscreen: false
  $name: "Show over full-screen apps"
  $description: "Off, the dock stays hidden while a game or a presentation fills the screen."
- settingsGlass: true
  $name: "Blurred settings window"
  $description: "On, the settings window is see-through glass with Windows acrylic behind it. Off, it is solid. Applies when you save."
- nativeSettingsTitleBar: false
  $name: "Native Windows title bar"
  $description: "Use the Windows title bar and window buttons for this settings window. Applies when you save."
- settingsTrayIcon: true
  $name: "Tray icon"
  $description: "Click it to open these settings. Right-click it to turn sounds on or off or pick a pack. When off, change settings in Windhawk."
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
#include <urlmon.h>
#include <wininet.h>
#include <mmdeviceapi.h>
#include <mfapi.h>
#include <mfidl.h>
#include <mfreadwrite.h>
#include <mferror.h>
#include <xaudio2.h>
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

namespace skcset {
void OpenSettingsWindow();
void CloseSettingsWindow();
// One row for the tray menu; ShowTrayMenu draws them with the engine menu (Set_TrayMenu).
struct TrayRow {
    int id = 0;
    std::wstring glyph, label, hint;
    bool checked = false, disabled = false, separator = false;
    std::vector<TrayRow> sub;
};
int ShowTrayMenu(HWND owner, const POINT* at, const std::vector<TrayRow>& rows);
extern std::atomic<HWND> g_settingsWnd;
}  // namespace skcset

// Generated by gen.py from spec.PACKS: folder, label, is a mouse pack.
struct BuiltinPack {
    PCWSTR name, label;
    bool mouse;
};
static const BuiltinPack kBuiltinPacks[] = {
    {L"alpaca", L"Alpaca (kbsim)", false},
    {L"apex-pro-tkl-v2", L"SteelSeries Apex Pro TKL (Akira)", false},
    {L"banana-split", L"Banana Split switches (Akira)", false},
    {L"gateron-black-ink", L"Gateron Black Ink (kbsim)", false},
    {L"gateron-red-ink", L"Gateron Red Ink (kbsim)", false},
    {L"holy-panda", L"Holy Panda (kbsim)", false},
    {L"ios", L"iPhone keyboard", false},
    {L"logitech-g915-tkl-brown", L"Logitech G915 TKL, brown switches", false},
    {L"mx-black", L"Cherry MX Black (kbsim)", false},
    {L"mx-blue", L"Cherry MX Blue (kbsim)", false},
    {L"mx-brown", L"Cherry MX Brown (kbsim)", false},
    {L"mx-speed-silver", L"Cherry MX Speed Silver (Mechvibes)", false},
    {L"nk-cream", L"NovelKeys Cream (Mechvibes)", false},
    {L"opera-gx", L"Opera GX browser (Mechvibes)", false},
    {L"telios-v2", L"Telios V2 linear (Mechvibes)", false},
    {L"typewriter", L"Antique typewriter (Mechvibes)", false},
    {L"classic", L"Classic tick (the original Key Click)", false},
    {L"g502x-wireless", L"Logitech G502 X Wireless", true},
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

static std::string TrimA(const std::string& s) {
    size_t a = s.find_first_not_of(" \t\r\n");
    if (a == std::string::npos) return {};
    return s.substr(a, s.find_last_not_of(" \t\r\n") - a + 1);
}

static std::string LowerA(std::string s) {
    for (char& c : s)
        if (c >= 'A' && c <= 'Z') c = (char)(c - 'A' + 'a');
    return s;
}

static std::wstring Widen(const std::string& s) {
    if (s.empty()) return {};
    int n = MultiByteToWideChar(CP_UTF8, 0, s.data(), (int)s.size(), nullptr, 0);
    std::wstring w(n, L'\0');
    MultiByteToWideChar(CP_UTF8, 0, s.data(), (int)s.size(), w.data(), n);
    return w;
}

static std::string Narrow(const std::wstring& w) {
    if (w.empty()) return {};
    int n = WideCharToMultiByte(CP_UTF8, 0, w.data(), (int)w.size(), nullptr, 0, nullptr, nullptr);
    std::string s(n, '\0');
    WideCharToMultiByte(CP_UTF8, 0, w.data(), (int)w.size(), s.data(), n, nullptr, nullptr);
    return s;
}

static bool FileExists(const std::wstring& p) {
    DWORD a = GetFileAttributesW(p.c_str());
    return a != INVALID_FILE_ATTRIBUTES && !(a & FILE_ATTRIBUTE_DIRECTORY);
}

static bool DirExists(const std::wstring& p) {
    DWORD a = GetFileAttributesW(p.c_str());
    return a != INVALID_FILE_ATTRIBUTES && (a & FILE_ATTRIBUTE_DIRECTORY);
}

static bool IsAbsolutePath(const std::wstring& p) {
    return (p.size() >= 2 && p[1] == L':') || (p.size() >= 2 && p[0] == L'\\' && p[1] == L'\\');
}

static std::wstring StoragePath() {
    WCHAR path[MAX_PATH]{};
    if (!Wh_GetModStoragePath(path, MAX_PATH)) return {};
    SHCreateDirectoryExW(nullptr, path, nullptr);
    return path;
}

static void RemoveTree(const std::wstring& dir) {
    WIN32_FIND_DATAW fd;
    HANDLE h = FindFirstFileW((dir + L"\\*").c_str(), &fd);
    if (h != INVALID_HANDLE_VALUE) {
        do {
            std::wstring n = fd.cFileName;
            if (n == L"." || n == L"..") continue;
            std::wstring p = dir + L"\\" + n;
            if (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) RemoveTree(p);
            else {
                SetFileAttributesW(p.c_str(), FILE_ATTRIBUTE_NORMAL);
                DeleteFileW(p.c_str());
            }
        } while (FindNextFileW(h, &fd));
        FindClose(h);
    }
    RemoveDirectoryW(dir.c_str());
}

// ---------------------------------------------------------------------------
// Hotkeys: "Ctrl+Alt+K" text, the same the settings window's key boxes write.
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
// Settings
// ---------------------------------------------------------------------------

enum { HK_ALL, HK_KEYBOARD, HK_MOUSE, HK_VOLUP, HK_VOLDOWN, HK_COUNT };
static const PCWSTR kHotkeyKeys[HK_COUNT] = {L"toggleHotkey", L"keyboardHotkey", L"mouseHotkey", L"volumeUpHotkey",
                                             L"volumeDownHotkey"};

struct Config {
    std::wstring kbPack, kbCustom, mousePack, mouseCustom, packsFolder;
    bool download = true, pitchShift = false, release = true, repeat = false, ignoreInjected = true,
         side = false, toggleCue = true, trayIcon = true;
    int volume = 70, mouseVolume = 100, pitchLow = -2, pitchHigh = 2, maxOverlap = 32, volumeStep = 10;
    std::wstring pitchApplies = L"both", appMode = L"enable", playApps, silentApps, onlyApps;
    std::wstring hotkeys[HK_COUNT];
    // The notifier dock.
    bool ntOn = true, ntSounds = true, ntVolume = true, ntPacks = true, ntFullscreen = false;
    std::wstring ntPos = L"bottomCenter", ntDisplay = L"focused", ntSize = L"normal", ntLook = L"glass";
    int ntMargin = 48, ntDuration = 1800, ntTint = 62;
    bool SameNotifier(const Config& o) const {
        return ntOn == o.ntOn && ntPos == o.ntPos && ntDisplay == o.ntDisplay && ntSize == o.ntSize &&
               ntLook == o.ntLook && ntMargin == o.ntMargin && ntDuration == o.ntDuration && ntTint == o.ntTint;
    }
};

static std::mutex g_cfgLock;
static Config g_cfg;

// Read by the hooks without a lock.
static std::atomic<bool> g_ignoreInjected{true}, g_repeat{false}, g_release{true}, g_side{false};
static std::atomic<bool> g_onAll{true}, g_onKeyboard{true}, g_onMouse{true}, g_appAllowed{true};
static std::atomic<int> g_volume{70};
static std::atomic<bool> g_volumeSavePending{false};
// Saves of the three switches still on their way: until they land, a reload keeps what the
// shortcut or the tray menu just set.
static std::atomic<int> g_togglesSavePending{0};
static bool g_migrateToggles = false;
static std::atomic<bool> g_stop{false};

static int Clamp(int v, int lo, int hi) { return v < lo ? lo : v > hi ? hi : v; }

static std::wstring OneOf(const std::wstring& v, std::initializer_list<PCWSTR> allowed) {
    for (PCWSTR a : allowed)
        if (v == a) return v;
    return *allowed.begin();
}

static void LoadSettings() {
    Config c;
    c.kbPack = Trim(ReadStr(L"keyboardPack"));
    c.kbCustom = Trim(ReadStr(L"keyboardCustomPack"));
    c.mousePack = Trim(ReadStr(L"mousePack"));
    c.mouseCustom = Trim(ReadStr(L"mouseCustomPack"));
    c.packsFolder = Trim(ReadStr(L"packsFolder"));
    if (c.kbPack.empty()) c.kbPack = L"alpaca";
    if (c.mousePack.empty()) c.mousePack = L"none";
    c.download = Wh_GetIntSetting(L"downloadPacks") != 0;
    c.volume = Clamp(Wh_GetIntSetting(L"volume"), 0, 100);
    c.mouseVolume = Clamp(Wh_GetIntSetting(L"mouseVolume"), 0, 100);
    c.pitchShift = Wh_GetIntSetting(L"pitchShift") != 0;
    c.pitchLow = Clamp(Wh_GetIntSetting(L"pitchLow"), -12, 12);
    c.pitchHigh = Clamp(Wh_GetIntSetting(L"pitchHigh"), -12, 12);
    if (c.pitchLow > c.pitchHigh) std::swap(c.pitchLow, c.pitchHigh);
    c.pitchApplies = OneOf(ReadStr(L"pitchApplies"), {L"both", L"keyboard", L"mouse"});
    c.release = Wh_GetIntSetting(L"releaseSounds") != 0;
    c.repeat = Wh_GetIntSetting(L"repeatHeldKeys") != 0;
    c.ignoreInjected = Wh_GetIntSetting(L"ignoreInjected") != 0;
    c.side = Wh_GetIntSetting(L"sideButtons") != 0;
    c.maxOverlap = Clamp(Wh_GetIntSetting(L"maxOverlap"), 1, 64);
    c.appMode = OneOf(ReadStr(L"appMode"), {L"enable", L"disable"});
    c.playApps = ReadStr(L"playApps");
    c.silentApps = ReadStr(L"silentApps");
    c.onlyApps = ReadStr(L"onlyApps");
    for (int i = 0; i < HK_COUNT; i++) c.hotkeys[i] = Trim(ReadStr(kHotkeyKeys[i]));
    c.volumeStep = Clamp(Wh_GetIntSetting(L"volumeStep"), 1, 50);
    c.toggleCue = Wh_GetIntSetting(L"toggleCue") != 0;
    c.trayIcon = Wh_GetIntSetting(L"settingsTrayIcon") != 0;
    c.ntOn = Wh_GetIntSetting(L"notifierOn") != 0;
    c.ntSounds = Wh_GetIntSetting(L"notifierSounds") != 0;
    c.ntVolume = Wh_GetIntSetting(L"notifierVolume") != 0;
    c.ntPacks = Wh_GetIntSetting(L"notifierPacks") != 0;
    c.ntFullscreen = Wh_GetIntSetting(L"notifierFullscreen") != 0;
    c.ntPos = OneOf(ReadStr(L"notifierPosition"), {L"bottomCenter", L"topLeft", L"topCenter", L"topRight", L"center",
                                                   L"bottomLeft", L"bottomRight"});
    c.ntDisplay = OneOf(ReadStr(L"notifierDisplay"), {L"focused", L"cursor", L"primary"});
    c.ntSize = OneOf(ReadStr(L"notifierSize"), {L"normal", L"compact", L"large"});
    c.ntLook = OneOf(ReadStr(L"notifierLook"), {L"glass", L"solid"});
    c.ntMargin = Clamp(Wh_GetIntSetting(L"notifierMargin"), 0, 400);
    c.ntDuration = Clamp(Wh_GetIntSetting(L"notifierDuration"), 500, 10000);
    c.ntTint = Clamp(Wh_GetIntSetting(L"notifierTint"), 30, 100);

    g_ignoreInjected = c.ignoreInjected;
    g_repeat = c.repeat;
    g_release = c.release;
    g_side = c.side;
    if (!g_volumeSavePending) g_volume = c.volume;
    if (g_togglesSavePending == 0) {
        g_onAll = Wh_GetIntSetting(L"soundsOn") != 0;
        g_onKeyboard = Wh_GetIntSetting(L"keyboardSounds") != 0;
        g_onMouse = Wh_GetIntSetting(L"mouseSounds") != 0;
    }
    std::lock_guard<std::mutex> lock(g_cfgLock);
    g_cfg = c;
}

static Config GetConfig() {
    std::lock_guard<std::mutex> lock(g_cfgLock);
    return g_cfg;
}

static std::wstring PacksRoot(const Config& c) {
    if (!c.packsFolder.empty()) {
        WCHAR out[MAX_PATH * 2]{};
        ExpandEnvironmentStringsW(c.packsFolder.c_str(), out, ARRAYSIZE(out));
        std::wstring r = out;
        while (!r.empty() && (r.back() == L'\\' || r.back() == L'/')) r.pop_back();
        if (!r.empty()) return r;
    }
    std::wstring s = StoragePath();
    return s.empty() ? std::wstring() : s + L"\\packs";
}

static bool IsBuiltinPack(const std::wstring& name, bool mouse) {
    for (const auto& p : kBuiltinPacks)
        if (p.mouse == mouse && name == p.name) return true;
    return false;
}

// The folder a pack choice points at, or empty for none. "classic" needs no folder.
static std::wstring PackDir(const Config& c, bool mouse) {
    std::wstring choice = mouse ? c.mousePack : c.kbPack;
    if (choice == L"none" || choice.empty()) return {};
    std::wstring root = PacksRoot(c);
    if (choice == L"custom") {
        std::wstring custom = mouse ? c.mouseCustom : c.kbCustom;
        if (custom.empty()) return {};
        if (IsAbsolutePath(custom)) return custom;
        return root + L"\\" + custom;
    }
    if (choice == L"classic") return L"classic";
    return root + L"\\" + choice;
}

// ---------------------------------------------------------------------------
// Saving settings: one elevated windhawk-cli call, off the calling thread.
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
    std::wstring params;
    bool volume = false;
    std::atomic<int>* pending = nullptr;  // Counted down when the save is done.
};

static std::atomic<int> g_saveThreads{0};

static DWORD WINAPI SaveThread(LPVOID param) {
    std::unique_ptr<SaveJob> job((SaveJob*)param);
    std::wstring cli = CliPath();
    if (cli.empty()) {
        Wh_Log(L"windhawk-cli.exe not found, setting not saved");
    } else {
        SHELLEXECUTEINFOW sei{sizeof(sei)};
        sei.fMask = SEE_MASK_NOCLOSEPROCESS | SEE_MASK_FLAG_NO_UI | SEE_MASK_NOASYNC;
        sei.lpVerb = L"runas";
        sei.lpFile = cli.c_str();
        sei.lpParameters = job->params.c_str();
        sei.nShow = SW_HIDE;
        if (ShellExecuteExW(&sei) && sei.hProcess) {
            if (WaitForSingleObject(sei.hProcess, 15000) == WAIT_TIMEOUT) {
                TerminateProcess(sei.hProcess, 1);
                Wh_Log(L"windhawk-cli timed out and was stopped");
            }
            CloseHandle(sei.hProcess);
        } else {
            Wh_Log(L"Couldn't start windhawk-cli (error %lu)", GetLastError());
        }
    }
    if (job->volume) g_volumeSavePending = false;
    if (job->pending) (*job->pending)--;
    g_saveThreads--;
    return 0;
}

static void SaveSettingsAsync(const std::vector<std::pair<std::wstring, std::wstring>>& kv, bool volume = false,
                              std::atomic<int>* pending = nullptr) {
    auto* job = new SaveJob;
    job->params = L"--quiet mod settings set " + QuoteArg(WH_MOD_ID);
    for (auto& [k, v] : kv) job->params += L" " + QuoteArg(k + L"=" + v);
    job->volume = volume;
    job->pending = pending;
    if (pending) (*pending)++;
    g_saveThreads++;
    HANDLE t = CreateThread(nullptr, 0, SaveThread, job, 0, nullptr);
    if (t) CloseHandle(t);
    else {
        g_saveThreads--;
        if (volume) g_volumeSavePending = false;
        if (pending) (*pending)--;
        delete job;
    }
}

// ---------------------------------------------------------------------------
// profile.yaml: the subset of YAML that Keyboard Sounds profiles use. Block maps
// and lists, "- key: value" list items, flow lists that may span lines, quoted
// and plain scalars, comments.
// ---------------------------------------------------------------------------

struct YNode {
    enum Type { Null, Str, Map, List } t = Null;
    std::string s;
    std::vector<std::pair<std::string, YNode>> m;
    std::vector<YNode> l;
    const YNode* get(const char* key) const {
        if (t != Map) return nullptr;
        for (auto& kv : m)
            if (kv.first == key) return &kv.second;
        return nullptr;
    }
    std::string str(const char* key, const std::string& def = {}) const {
        const YNode* n = get(key);
        return n && n->t == Str ? n->s : def;
    }
    // A scalar or a list of scalars, as a list.
    std::vector<std::string> strs() const {
        std::vector<std::string> out;
        if (t == Str) out.push_back(s);
        else if (t == List)
            for (auto& x : l)
                if (x.t == Str) out.push_back(x.s);
        return out;
    }
};

struct YLine {
    int indent;
    std::string text;
};

static std::string YStripComment(const std::string& s) {
    char q = 0;
    for (size_t i = 0; i < s.size(); i++) {
        char c = s[i];
        if (q) {
            if (c == q) q = 0;
        } else if (c == '"' || c == '\'') {
            q = c;
        } else if (c == '#' && (i == 0 || s[i - 1] == ' ' || s[i - 1] == '\t')) {
            return s.substr(0, i);
        }
    }
    return s;
}

static std::string YUnquote(std::string s) {
    s = TrimA(s);
    if (s.size() >= 2 && ((s.front() == '"' && s.back() == '"') || (s.front() == '\'' && s.back() == '\''))) {
        char q = s.front();
        s = s.substr(1, s.size() - 2);
        if (q == '"') {
            std::string out;
            for (size_t i = 0; i < s.size(); i++) {
                if (s[i] == '\\' && i + 1 < s.size()) {
                    char n = s[++i];
                    out += n == 'n' ? '\n' : n == 't' ? '\t' : n;
                } else {
                    out += s[i];
                }
            }
            return out;
        }
        std::string out;
        for (size_t i = 0; i < s.size(); i++) {
            out += s[i];
            if (s[i] == '\'' && i + 1 < s.size() && s[i + 1] == '\'') i++;
        }
        return out;
    }
    return s;
}

static int YBracketDepth(const std::string& s) {
    int d = 0;
    char q = 0;
    for (char c : s) {
        if (q) {
            if (c == q) q = 0;
        } else if (c == '"' || c == '\'') q = c;
        else if (c == '[' || c == '{') d++;
        else if (c == ']' || c == '}') d--;
    }
    return d;
}

static YNode YScalar(const std::string& raw) {
    YNode n;
    std::string s = TrimA(raw);
    if (s.empty() || s == "~" || s == "null") return n;
    if (s.front() == '[' && s.back() == ']') {
        n.t = YNode::List;
        std::string inner = s.substr(1, s.size() - 2);
        std::string cur;
        char q = 0;
        for (char c : inner) {
            if (q) {
                cur += c;
                if (c == q) q = 0;
            } else if (c == '"' || c == '\'') {
                q = c;
                cur += c;
            } else if (c == ',') {
                if (!TrimA(cur).empty()) n.l.push_back(YScalar(cur));
                cur.clear();
            } else {
                cur += c;
            }
        }
        if (!TrimA(cur).empty()) n.l.push_back(YScalar(cur));
        return n;
    }
    n.t = YNode::Str;
    n.s = YUnquote(s);
    return n;
}

// Finds "key:" at the top level of a line, returning the colon position or npos.
static size_t YKeyColon(const std::string& s) {
    char q = 0;
    int depth = 0;
    for (size_t i = 0; i < s.size(); i++) {
        char c = s[i];
        if (q) {
            if (c == q) q = 0;
            continue;
        }
        if (c == '"' || c == '\'') {
            if (i == 0) q = c;
            continue;
        }
        if (c == '[' || c == '{') depth++;
        else if (c == ']' || c == '}') depth--;
        else if (c == ':' && depth == 0 && (i + 1 == s.size() || s[i + 1] == ' ' || s[i + 1] == '\t')) return i;
    }
    return std::string::npos;
}

static bool YIsItem(const std::string& t) { return t == "-" || (t.size() >= 2 && t[0] == '-' && (t[1] == ' ' || t[1] == '\t')); }

static YNode YParseBlock(std::vector<YLine>& L, size_t& i, int indent);

static YNode YParseList(std::vector<YLine>& L, size_t& i, int indent) {
    YNode n;
    n.t = YNode::List;
    while (i < L.size() && L[i].indent == indent && YIsItem(L[i].text)) {
        std::string rest = L[i].text.substr(1);
        size_t off = rest.find_first_not_of(" \t");
        if (off == std::string::npos) {
            i++;
            if (i < L.size() && L[i].indent > indent) n.l.push_back(YParseBlock(L, i, L[i].indent));
            else n.l.push_back(YNode());
            continue;
        }
        rest = rest.substr(off);
        if (YIsItem(rest) || YKeyColon(rest) != std::string::npos) {
            // "- key: value": the item is a map (or list) that starts on this line.
            L[i].indent = indent + 1 + (int)off;
            L[i].text = rest;
            n.l.push_back(YParseBlock(L, i, L[i].indent));
        } else {
            n.l.push_back(YScalar(rest));
            i++;
        }
    }
    return n;
}

static YNode YParseMap(std::vector<YLine>& L, size_t& i, int indent) {
    YNode n;
    n.t = YNode::Map;
    while (i < L.size() && L[i].indent == indent && !YIsItem(L[i].text)) {
        const std::string& t = L[i].text;
        size_t c = YKeyColon(t);
        if (c == std::string::npos) {
            i++;  // Not a mapping line; skip it.
            continue;
        }
        std::string key = YUnquote(t.substr(0, c));
        std::string val = TrimA(t.substr(c + 1));
        i++;
        if (val.empty()) {
            if (i < L.size() && (L[i].indent > indent || (L[i].indent == indent && YIsItem(L[i].text))))
                n.m.emplace_back(key, YParseBlock(L, i, L[i].indent));
            else
                n.m.emplace_back(key, YNode());
        } else {
            n.m.emplace_back(key, YScalar(val));
        }
    }
    return n;
}

static YNode YParseBlock(std::vector<YLine>& L, size_t& i, int indent) {
    if (i >= L.size()) return YNode();
    if (YIsItem(L[i].text)) return YParseList(L, i, indent);
    if (YKeyColon(L[i].text) == std::string::npos) return YScalar(L[i++].text);
    return YParseMap(L, i, indent);
}

static YNode YParse(const std::string& text) {
    std::vector<YLine> L;
    size_t p = 0;
    std::string pending;
    int pendingIndent = 0;
    while (p <= text.size()) {
        size_t e = text.find('\n', p);
        if (e == std::string::npos) e = text.size();
        std::string line = text.substr(p, e - p);
        p = e + 1;
        if (!line.empty() && line.back() == '\r') line.pop_back();
        for (char& ch : line)
            if (ch == '\t') ch = ' ';
        line = YStripComment(line);
        if (TrimA(line).empty()) {
            if (p > text.size()) break;
            continue;
        }
        if (line == "---" || line == "...") continue;
        int ind = (int)line.find_first_not_of(' ');
        std::string body = TrimA(line);
        if (!pending.empty()) {
            pending += " " + body;
            if (YBracketDepth(pending) <= 0) {
                L.push_back({pendingIndent, pending});
                pending.clear();
            }
        } else if (YBracketDepth(body) > 0) {
            pending = body;
            pendingIndent = ind;
        } else {
            L.push_back({ind, body});
        }
        if (p > text.size()) break;
    }
    if (!pending.empty()) L.push_back({pendingIndent, pending});
    size_t i = 0;
    if (L.empty()) return YNode();
    return YParseBlock(L, i, L[0].indent);
}

static bool ReadFileUtf8(const std::wstring& path, std::string& out) {
    HANDLE h = CreateFileW(path.c_str(), GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_DELETE, nullptr, OPEN_EXISTING, 0,
                           nullptr);
    if (h == INVALID_HANDLE_VALUE) return false;
    LARGE_INTEGER size{};
    GetFileSizeEx(h, &size);
    if (size.QuadPart > 4 * 1024 * 1024) {
        CloseHandle(h);
        return false;
    }
    out.resize((size_t)size.QuadPart);
    DWORD read = 0;
    BOOL ok = out.empty() || ReadFile(h, out.data(), (DWORD)out.size(), &read, nullptr);
    CloseHandle(h);
    out.resize(read);
    if (out.size() >= 3 && (unsigned char)out[0] == 0xEF && (unsigned char)out[1] == 0xBB &&
        (unsigned char)out[2] == 0xBF)
        out.erase(0, 3);
    return ok;
}

// A file name from a profile, made safe: no going up, no drive, no absolute path.
static bool SafeRelative(std::string f, std::wstring& out) {
    f = TrimA(f);
    while (f.rfind("./", 0) == 0 || f.rfind(".\\", 0) == 0) f = f.substr(2);
    if (f.empty() || f.find("..") != std::string::npos || f.find(':') != std::string::npos || f[0] == '/' ||
        f[0] == '\\')
        return false;
    out = Widen(f);
    for (auto& c : out)
        if (c == L'/') c = L'\\';
    return true;
}

// ---------------------------------------------------------------------------
// Decoding: Media Foundation reads mp3, wav, ogg (with the codec) and the
// audio track of a video, to 48 kHz stereo float.
// ---------------------------------------------------------------------------

constexpr UINT32 kRate = 48000;
constexpr double kMaxClipSeconds = 20.0, kMaxVideoSeconds = 600.0;

struct Clip {
    std::vector<float> pcm;  // Interleaved stereo.
};

static void ToStereo48k(const std::vector<float>& in, UINT32 ch, UINT32 rate, std::vector<float>& out) {
    out.clear();
    if (!ch || !rate || in.size() < ch) return;
    size_t frames = in.size() / ch;
    if (rate == kRate) {
        out.resize(frames * 2);
        for (size_t f = 0; f < frames; f++) {
            float l = in[f * ch], r = ch > 1 ? in[f * ch + 1] : l;
            out[f * 2] = l;
            out[f * 2 + 1] = r;
        }
        return;
    }
    double step = (double)rate / kRate;
    size_t outFrames = (size_t)((double)frames / step);
    out.resize(outFrames * 2);
    for (size_t o = 0; o < outFrames; o++) {
        double pos = o * step;
        size_t a = (size_t)pos;
        size_t b = std::min(a + 1, frames - 1);
        float t = (float)(pos - a);
        for (int c = 0; c < 2; c++) {
            UINT32 src = ch > 1 ? (UINT32)c : 0;
            float va = in[a * ch + src], vb = in[b * ch + src];
            out[o * 2 + c] = va + (vb - va) * t;
        }
    }
}

static bool DecodeFile(const std::wstring& path, double maxSeconds, std::vector<float>& out) {
    out.clear();
    IMFSourceReader* reader = nullptr;
    if (FAILED(MFCreateSourceReaderFromURL(path.c_str(), nullptr, &reader)) || !reader) return false;
    bool ok = false;
    IMFMediaType* want = nullptr;
    IMFMediaType* cur = nullptr;
    std::vector<float> raw;
    UINT32 ch = 0, rate = 0;
    do {
        reader->SetStreamSelection((DWORD)MF_SOURCE_READER_ALL_STREAMS, FALSE);
        if (FAILED(reader->SetStreamSelection((DWORD)MF_SOURCE_READER_FIRST_AUDIO_STREAM, TRUE))) break;
        if (FAILED(MFCreateMediaType(&want))) break;
        want->SetGUID(MF_MT_MAJOR_TYPE, MFMediaType_Audio);
        want->SetGUID(MF_MT_SUBTYPE, MFAudioFormat_Float);
        if (FAILED(reader->SetCurrentMediaType((DWORD)MF_SOURCE_READER_FIRST_AUDIO_STREAM, nullptr, want))) break;
        if (FAILED(reader->GetCurrentMediaType((DWORD)MF_SOURCE_READER_FIRST_AUDIO_STREAM, &cur))) break;
        cur->GetUINT32(MF_MT_AUDIO_NUM_CHANNELS, &ch);
        cur->GetUINT32(MF_MT_AUDIO_SAMPLES_PER_SECOND, &rate);
        if (!ch || !rate) break;
        size_t cap = (size_t)(maxSeconds * rate) * ch;
        while (!g_stop) {
            DWORD idx = 0, flags = 0;
            LONGLONG ts = 0;
            IMFSample* sample = nullptr;
            if (FAILED(reader->ReadSample((DWORD)MF_SOURCE_READER_FIRST_AUDIO_STREAM, 0, &idx, &flags, &ts, &sample)))
                break;
            if (sample) {
                IMFMediaBuffer* buf = nullptr;
                if (SUCCEEDED(sample->ConvertToContiguousBuffer(&buf)) && buf) {
                    BYTE* data = nullptr;
                    DWORD len = 0;
                    if (SUCCEEDED(buf->Lock(&data, nullptr, &len))) {
                        size_t n = len / sizeof(float);
                        size_t at = raw.size();
                        raw.resize(at + n);
                        memcpy(raw.data() + at, data, n * sizeof(float));
                        buf->Unlock();
                    }
                    buf->Release();
                }
                sample->Release();
            }
            if (flags & (MF_SOURCE_READERF_ENDOFSTREAM | MF_SOURCE_READERF_ERROR)) break;
            if (raw.size() >= cap) {
                raw.resize(cap);
                break;
            }
        }
        ok = !raw.empty();
    } while (false);
    if (cur) cur->Release();
    if (want) want->Release();
    reader->Release();
    if (ok) ToStereo48k(raw, ch, rate, out);
    return ok && !out.empty();
}

// ---------------------------------------------------------------------------
// Profiles: the Keyboard Sounds model. Sources are clips (or press/release
// pairs); "keys" / "buttons" map names to sources with a default for the rest.
// ---------------------------------------------------------------------------

struct SoundSrc {
    int press = -1, release = -1;
    bool dual = false;  // A press/release pair. A single file plays on press only.
};

struct Mapping {
    std::vector<int> srcs;
    std::vector<std::string> names;  // Lowercased.
};

struct Profile {
    std::string name, device = "keyboard", type = "files";
    std::wstring dir;
    std::vector<Clip> clips;
    std::vector<SoundSrc> srcs;
    std::map<std::string, int> ids;
    std::vector<int> defaults;
    std::vector<Mapping> other;
    int oneShotPress = -1, oneShotRelease = -1;
};

static int AddClip(Profile& p, std::vector<float>&& pcm) {
    p.clips.push_back(Clip{std::move(pcm)});
    return (int)p.clips.size() - 1;
}

static int LoadClipFile(Profile& p, const std::string& rel) {
    std::wstring w;
    if (!SafeRelative(rel, w)) return -1;
    std::vector<float> pcm;
    if (!DecodeFile(p.dir + L"\\" + w, kMaxClipSeconds, pcm)) {
        Wh_Log(L"Couldn't decode %s\\%s", p.dir.c_str(), w.c_str());
        return -1;
    }
    return AddClip(p, std::move(pcm));
}

static double ParseSeconds(const YNode* n, double def) {
    if (!n || n->t != YNode::Str || n->s.empty()) return def;
    return atof(n->s.c_str());
}

// Ids to source indexes, skipping ids no source defines.
static std::vector<int> ResolveIds(const Profile& p, const YNode* n) {
    std::vector<int> out;
    if (!n) return out;
    for (auto& id : n->strs()) {
        auto it = p.ids.find(id);
        if (it != p.ids.end()) out.push_back(it->second);
    }
    return out;
}

static std::unique_ptr<Profile> MakeClassicProfile() {
    // The original Key Click sound: eight 8-bit samples at 8 kHz.
    static const unsigned char kTick[] = {128, 255, 0, 255, 0, 200, 80, 128};
    std::vector<float> mono;
    for (unsigned char b : kTick) mono.push_back(((float)b - 128.0f) / 128.0f * 0.8f);
    std::vector<float> st;
    ToStereo48k(mono, 1, 8000, st);
    auto p = std::make_unique<Profile>();
    p->name = "classic";
    p->srcs.push_back(SoundSrc{AddClip(*p, std::move(st)), -1, false});
    p->ids["tick"] = 0;
    p->defaults.push_back(0);
    return p;
}

static std::unique_ptr<Profile> LoadProfile(const std::wstring& dir) {
    if (dir == L"classic") return MakeClassicProfile();
    std::string text;
    if (!ReadFileUtf8(dir + L"\\profile.yaml", text)) {
        Wh_Log(L"No profile.yaml in %s", dir.c_str());
        return nullptr;
    }
    YNode root = YParse(text);
    if (root.t != YNode::Map) {
        Wh_Log(L"Couldn't read %s\\profile.yaml", dir.c_str());
        return nullptr;
    }
    auto p = std::make_unique<Profile>();
    p->dir = dir;
    const YNode* info = root.get("profile");
    if (info) {
        p->name = info->str("name");
        std::string dev = LowerA(info->str("device", "keyboard"));
        p->device = dev == "mouse" ? "mouse" : "keyboard";
        std::string type = LowerA(info->str("type", "files"));
        p->type = (type == "video-extract" || type == "one-shot") ? type : "files";
    }

    if (p->type == "one-shot") {
        if (info) {
            std::string press = info->str("press"), release = info->str("release");
            if (!press.empty()) p->oneShotPress = LoadClipFile(*p, press);
            if (!release.empty()) p->oneShotRelease = LoadClipFile(*p, release);
        }
        if (p->oneShotPress < 0 && p->oneShotRelease < 0) return nullptr;
        return p;
    }

    const YNode* sources = root.get("sources");
    if (!sources || sources->t != YNode::List) {
        Wh_Log(L"%s has no sources", dir.c_str());
        return nullptr;
    }

    std::vector<float> video;
    if (p->type == "video-extract") {
        double maxEnd = 0;
        for (auto& s : sources->l) maxEnd = std::max(maxEnd, ParseSeconds(s.get("end"), 0));
        std::wstring rel;
        if (!info || !SafeRelative(info->str("video"), rel) ||
            !DecodeFile(dir + L"\\" + rel, std::min(kMaxVideoSeconds, maxEnd > 0 ? maxEnd + 1 : kMaxVideoSeconds),
                        video)) {
            Wh_Log(L"Couldn't decode the video of %s", dir.c_str());
            return nullptr;
        }
    }

    for (auto& s : sources->l) {
        if (s.t != YNode::Map) continue;
        std::string id = s.str("id");
        if (id.empty()) continue;
        SoundSrc src;
        if (p->type == "video-extract") {
            double start = ParseSeconds(s.get("start"), 0), end = ParseSeconds(s.get("end"), 0);
            size_t a = (size_t)std::max(0.0, start * kRate) * 2, b = end > start ? (size_t)(end * kRate) * 2 : video.size();
            a = std::min(a, video.size());
            b = std::min(b, video.size());
            if (b > a) src.press = AddClip(*p, std::vector<float>(video.begin() + a, video.begin() + b));
        } else if (const YNode* so = s.get("source")) {
            if (so->t == YNode::Str) {
                src.press = LoadClipFile(*p, so->s);
            } else if (so->t == YNode::Map) {
                src.dual = true;
                std::string press = so->str("press"), release = so->str("release");
                if (!press.empty()) src.press = LoadClipFile(*p, press);
                if (!release.empty()) src.release = LoadClipFile(*p, release);
            }
        }
        if (src.press < 0 && src.release < 0) continue;
        p->ids[id] = (int)p->srcs.size();
        p->srcs.push_back(src);
    }
    if (p->srcs.empty()) {
        Wh_Log(L"%s has no sounds that could be read", dir.c_str());
        return nullptr;
    }

    const YNode* map = root.get(p->device == "mouse" ? "buttons" : "keys");
    if (map && map->t == YNode::Map) {
        p->defaults = ResolveIds(*p, map->get("default"));
        if (const YNode* other = map->get("other"); other && other->t == YNode::List) {
            for (auto& o : other->l) {
                if (o.t != YNode::Map) continue;
                Mapping m;
                m.srcs = ResolveIds(*p, o.get("sound"));
                if (const YNode* names = o.get(p->device == "mouse" ? "buttons" : "keys"))
                    for (auto& n : names->strs()) m.names.push_back(LowerA(TrimA(n)));
                if (!m.srcs.empty() && !m.names.empty()) p->other.push_back(std::move(m));
            }
        }
    }
    return p;
}

static std::mt19937& Rng() {
    static thread_local std::mt19937 rng(GetTickCount() ^ GetCurrentThreadId());
    return rng;
}

static int PickOne(const std::vector<int>& v) {
    if (v.empty()) return -1;
    return v[std::uniform_int_distribution<size_t>(0, v.size() - 1)(Rng())];
}

static int PickKeyboardSource(const Profile& p, const std::vector<std::string>& names) {
    std::vector<int> cand;
    for (auto& m : p.other) {
        bool hit = false;
        for (auto& n : names)
            if (std::find(m.names.begin(), m.names.end(), n) != m.names.end()) hit = true;
        if (hit) cand.insert(cand.end(), m.srcs.begin(), m.srcs.end());
    }
    if (cand.empty()) cand = p.defaults;
    if (cand.empty())
        for (int i = 0; i < (int)p.srcs.size(); i++) cand.push_back(i);
    return PickOne(cand);
}

static int PickMouseSource(const Profile& p, const std::vector<std::string>& names, bool useMappings) {
    if (useMappings)
        for (auto& m : p.other)
            for (auto& n : names)
                if (std::find(m.names.begin(), m.names.end(), n) != m.names.end()) return PickOne(m.srcs);
    std::vector<int> cand = p.defaults;
    if (cand.empty())
        for (int i = 0; i < (int)p.srcs.size(); i++) cand.push_back(i);
    return PickOne(cand);
}

// ---------------------------------------------------------------------------
// Key names, as Keyboard Sounds (pynput) spells them. Every key gets both its
// plain name and its left/right name, so "shift" and "shift_l" both match.
// ---------------------------------------------------------------------------

static void AddNames(std::vector<std::string>& v, std::initializer_list<const char*> names) {
    for (auto n : names) v.push_back(n);
}

static std::vector<std::string> KeyNames(UINT vk, bool ext, UINT scan) {
    std::vector<std::string> v;
    switch (vk) {
        case VK_SPACE: AddNames(v, {"space"}); break;
        case VK_RETURN: AddNames(v, {"enter", "return"}); break;
        case VK_BACK: AddNames(v, {"backspace"}); break;
        case VK_DELETE: AddNames(v, {"delete"}); break;
        case VK_TAB: AddNames(v, {"tab"}); break;
        case VK_ESCAPE: AddNames(v, {"esc", "escape"}); break;
        case VK_SHIFT: case VK_LSHIFT: AddNames(v, {"shift", "shift_l"}); break;
        case VK_RSHIFT: AddNames(v, {"shift", "shift_r"}); break;
        case VK_CONTROL: case VK_LCONTROL: AddNames(v, {"ctrl", "ctrl_l"}); break;
        case VK_RCONTROL: AddNames(v, {"ctrl", "ctrl_r"}); break;
        case VK_MENU: case VK_LMENU: AddNames(v, {"alt", "alt_l"}); break;
        case VK_RMENU: AddNames(v, {"alt", "alt_r", "alt_gr"}); break;
        case VK_LWIN: AddNames(v, {"cmd", "cmd_l", "win"}); break;
        case VK_RWIN: AddNames(v, {"cmd", "cmd_r", "win"}); break;
        case VK_APPS: AddNames(v, {"menu"}); break;
        case VK_CAPITAL: AddNames(v, {"caps_lock", "capslock"}); break;
        case VK_INSERT: AddNames(v, {"insert"}); break;
        case VK_HOME: AddNames(v, {"home"}); break;
        case VK_END: AddNames(v, {"end"}); break;
        case VK_PRIOR: AddNames(v, {"page_up"}); break;
        case VK_NEXT: AddNames(v, {"page_down"}); break;
        case VK_UP: AddNames(v, {"up"}); break;
        case VK_DOWN: AddNames(v, {"down"}); break;
        case VK_LEFT: AddNames(v, {"left"}); break;
        case VK_RIGHT: AddNames(v, {"right"}); break;
        case VK_NUMLOCK: AddNames(v, {"num_lock"}); break;
        case VK_SCROLL: AddNames(v, {"scroll_lock"}); break;
        case VK_PAUSE: AddNames(v, {"pause"}); break;
        case VK_SNAPSHOT: AddNames(v, {"print_screen"}); break;
        case VK_VOLUME_MUTE: AddNames(v, {"media_volume_mute"}); break;
        case VK_VOLUME_DOWN: AddNames(v, {"media_volume_down"}); break;
        case VK_VOLUME_UP: AddNames(v, {"media_volume_up"}); break;
        case VK_MEDIA_NEXT_TRACK: AddNames(v, {"media_next"}); break;
        case VK_MEDIA_PREV_TRACK: AddNames(v, {"media_previous"}); break;
        case VK_MEDIA_PLAY_PAUSE: AddNames(v, {"media_play_pause"}); break;
        default: break;
    }
    if (vk >= VK_F1 && vk <= VK_F24) v.push_back("f" + std::to_string(vk - VK_F1 + 1));
    if (v.empty() || (vk >= VK_NUMPAD0 && vk <= VK_DIVIDE)) {
        HWND fg = GetForegroundWindow();
        HKL hkl = GetKeyboardLayout(fg ? GetWindowThreadProcessId(fg, nullptr) : 0);
        UINT ch = MapVirtualKeyExW(vk, MAPVK_VK_TO_CHAR, hkl) & 0x7FFFFFFF;
        if (ch) {
            WCHAR c[2] = {(WCHAR)towlower((wint_t)ch), 0};
            v.push_back(Narrow(c));
        }
    }
    v.push_back("<" + std::to_string(vk) + ">");
    (void)ext;
    (void)scan;
    return v;
}

// ---------------------------------------------------------------------------
// Audio thread: XAudio2 voices playing the decoded clips.
// ---------------------------------------------------------------------------

enum : UINT {
    WM_SKC_PLAY = WM_APP + 40,  // wParam: device | release << 1 | cue << 2. lParam: vk | ext << 8 | scan << 16, or button.
    WM_SKC_CONFIG,              // Settings changed: reload packs if they moved.
    WM_SKC_RELOAD,              // A download finished: reload packs.
    WM_SKC_REBUILD,             // Audio device changed or failed.
    WM_SKC_RULES,               // Input thread: app lists changed.
    WM_SKC_TRAY,                // UI thread: tray callback.
    WM_SKC_SETTINGS,            // UI thread: Windhawk settings changed.
    WM_SKC_REFRESH,             // UI thread: redraw the tray after a change.
};
enum : WPARAM { DEV_KEYBOARD = 0, DEV_MOUSE = 1, FLAG_RELEASE = 2, FLAG_CUE = 4 };

static DWORD g_audioTid, g_inputTid, g_uiTid;
static HANDLE g_audioThread, g_inputThread, g_uiThread;
static HWND g_msgWnd;

class EngineCallback : public IXAudio2EngineCallback {
   public:
    void STDMETHODCALLTYPE OnProcessingPassStart() override {}
    void STDMETHODCALLTYPE OnProcessingPassEnd() override {}
    void STDMETHODCALLTYPE OnCriticalError(HRESULT error) override {
        Wh_Log(L"Audio engine error 0x%08X, rebuilding", (unsigned)error);
        PostThreadMessageW(g_audioTid, WM_SKC_REBUILD, 0, 0);
    }
};

static const GUID kClsidMMDeviceEnumerator = {0xBCDE0395, 0xE52F, 0x467C, {0x8E, 0x3D, 0xC4, 0x57, 0x92, 0x91, 0x69, 0x2E}};
static const GUID kIidIMMDeviceEnumerator = {0xA95664D2, 0x9614, 0x4F35, {0xA7, 0x46, 0xDE, 0x8D, 0xB6, 0x36, 0x17, 0xE6}};
static const GUID kIidIMMNotificationClient = {0x7991EEC9, 0x7E89, 0x4D85, {0x83, 0x90, 0x6C, 0x70, 0x3C, 0xEC, 0x60, 0xC0}};

class DeviceWatcher : public IMMNotificationClient {
   public:
    ULONG STDMETHODCALLTYPE AddRef() override { return 2; }
    ULONG STDMETHODCALLTYPE Release() override { return 1; }
    HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, void** out) override {
        if (IsEqualIID(riid, IID_IUnknown) || IsEqualIID(riid, kIidIMMNotificationClient)) {
            *out = static_cast<IMMNotificationClient*>(this);
            return S_OK;
        }
        *out = nullptr;
        return E_NOINTERFACE;
    }
    HRESULT STDMETHODCALLTYPE OnDeviceStateChanged(LPCWSTR, DWORD) override { return S_OK; }
    HRESULT STDMETHODCALLTYPE OnDeviceAdded(LPCWSTR) override { return S_OK; }
    HRESULT STDMETHODCALLTYPE OnDeviceRemoved(LPCWSTR) override { return S_OK; }
    HRESULT STDMETHODCALLTYPE OnDefaultDeviceChanged(EDataFlow flow, ERole role, LPCWSTR) override {
        if (flow == eRender && role == eConsole) PostThreadMessageW(g_audioTid, WM_SKC_REBUILD, 0, 0);
        return S_OK;
    }
    HRESULT STDMETHODCALLTYPE OnPropertyValueChanged(LPCWSTR, const PROPERTYKEY) override { return S_OK; }
};

struct Engine {
    IXAudio2* xa = nullptr;
    IXAudio2MasteringVoice* master = nullptr;
    std::vector<IXAudio2SourceVoice*> voices;
    std::vector<UINT64> started;
    UINT64 counter = 0;
    EngineCallback cb;

    void Destroy() {
        for (auto* v : voices)
            if (v) v->DestroyVoice();
        voices.clear();
        started.clear();
        if (master) master->DestroyVoice();
        master = nullptr;
        if (xa) {
            xa->UnregisterForCallbacks(&cb);
            xa->StopEngine();
            xa->Release();
        }
        xa = nullptr;
    }

    bool Create(int count) {
        Destroy();
        if (FAILED(XAudio2Create(&xa, 0, XAUDIO2_DEFAULT_PROCESSOR)) || !xa) {
            Wh_Log(L"XAudio2Create failed");
            xa = nullptr;
            return false;
        }
        xa->RegisterForCallbacks(&cb);
        if (FAILED(xa->CreateMasteringVoice(&master))) {
            Wh_Log(L"No audio output device");
            master = nullptr;
            Destroy();
            return false;
        }
        WAVEFORMATEX wfx{};
        wfx.wFormatTag = WAVE_FORMAT_IEEE_FLOAT;
        wfx.nChannels = 2;
        wfx.nSamplesPerSec = kRate;
        wfx.wBitsPerSample = 32;
        wfx.nBlockAlign = 8;
        wfx.nAvgBytesPerSec = kRate * 8;
        for (int i = 0; i < count; i++) {
            IXAudio2SourceVoice* v = nullptr;
            if (FAILED(xa->CreateSourceVoice(&v, &wfx, 0, 4.0f)) || !v) break;
            voices.push_back(v);
            started.push_back(0);
        }
        return !voices.empty();
    }

    void Play(const Clip& clip, float volume, float ratio) {
        if (voices.empty() || clip.pcm.empty() || volume <= 0) return;
        int pick = -1;
        for (size_t i = 0; i < voices.size(); i++) {
            XAUDIO2_VOICE_STATE st{};
            voices[i]->GetState(&st, XAUDIO2_VOICE_NOSAMPLESPLAYED);
            if (st.BuffersQueued == 0) {
                pick = (int)i;
                break;
            }
        }
        if (pick < 0) {
            pick = 0;
            for (size_t i = 1; i < voices.size(); i++)
                if (started[i] < started[pick]) pick = (int)i;
            voices[pick]->Stop(0);
            voices[pick]->FlushSourceBuffers();
        }
        IXAudio2SourceVoice* v = voices[pick];
        v->SetVolume(volume);
        v->SetFrequencyRatio(ratio);
        XAUDIO2_BUFFER buf{};
        buf.Flags = XAUDIO2_END_OF_STREAM;
        buf.AudioBytes = (UINT32)(clip.pcm.size() * sizeof(float));
        buf.pAudioData = (const BYTE*)clip.pcm.data();
        if (SUCCEEDED(v->SubmitSourceBuffer(&buf))) {
            v->Start(0);
            started[pick] = ++counter;
        }
    }
};

// ---------------------------------------------------------------------------
// Pack downloads from the Keyboard Sounds repository, pinned to one commit.
// ---------------------------------------------------------------------------

static const wchar_t kPackBaseUrl[] =
    L"https://raw.githubusercontent.com/nathan-fiscaletti/keyboardsounds/"
    L"6785c7ac17b9f4db1f3d7f3d1d87a23067944517/keyboardsounds/profiles/";

class AbortCallback : public IBindStatusCallback {
   public:
    ULONG STDMETHODCALLTYPE AddRef() override { return 2; }
    ULONG STDMETHODCALLTYPE Release() override { return 1; }
    HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, void** out) override {
        if (IsEqualIID(riid, IID_IUnknown) || IsEqualIID(riid, IID_IBindStatusCallback)) {
            *out = static_cast<IBindStatusCallback*>(this);
            return S_OK;
        }
        *out = nullptr;
        return E_NOINTERFACE;
    }
    HRESULT STDMETHODCALLTYPE OnStartBinding(DWORD, IBinding*) override { return S_OK; }
    HRESULT STDMETHODCALLTYPE GetPriority(LONG*) override { return E_NOTIMPL; }
    HRESULT STDMETHODCALLTYPE OnLowResource(DWORD) override { return S_OK; }
    HRESULT STDMETHODCALLTYPE OnProgress(ULONG, ULONG, ULONG, LPCWSTR) override {
        return g_stop ? E_ABORT : S_OK;
    }
    HRESULT STDMETHODCALLTYPE OnStopBinding(HRESULT, LPCWSTR) override { return S_OK; }
    HRESULT STDMETHODCALLTYPE GetBindInfo(DWORD*, BINDINFO*) override { return S_OK; }
    HRESULT STDMETHODCALLTYPE OnDataAvailable(DWORD, DWORD, FORMATETC*, STGMEDIUM*) override { return S_OK; }
    HRESULT STDMETHODCALLTYPE OnObjectAvailable(REFIID, IUnknown*) override { return S_OK; }
};

static std::wstring UrlEncodePath(const std::wstring& rel) {
    std::string s = Narrow(rel);
    std::wstring out;
    for (unsigned char c : s) {
        if (isalnum(c) || c == '-' || c == '_' || c == '.' || c == '~') out += (wchar_t)c;
        else if (c == '\\' || c == '/') out += L'/';
        else {
            WCHAR hex[4];
            swprintf_s(hex, L"%%%02X", c);
            out += hex;
        }
    }
    return out;
}

static std::mutex g_dlLock;
static std::set<std::wstring> g_dlTried;
static std::vector<HANDLE> g_dlThreads;

struct DownloadJob {
    std::wstring name, root;
};

static bool Fetch(const std::wstring& url, const std::wstring& file) {
    AbortCallback cb;
    // Never a cached copy, so a broken earlier fetch is not reused.
    DeleteUrlCacheEntryW(url.c_str());
    return SUCCEEDED(URLDownloadToFileW(nullptr, url.c_str(), file.c_str(), 0, &cb)) && FileExists(file);
}

static DWORD WINAPI DownloadThread(LPVOID param) {
    std::unique_ptr<DownloadJob> job((DownloadJob*)param);
    CoInitializeEx(nullptr, COINIT_MULTITHREADED);
    std::wstring tmp = job->root + L"\\.download-" + job->name, final = job->root + L"\\" + job->name;
    RemoveTree(tmp);
    SHCreateDirectoryExW(nullptr, tmp.c_str(), nullptr);
    std::wstring base = kPackBaseUrl + job->name + L"/";
    bool ok = Fetch(base + L"profile.yaml", tmp + L"\\profile.yaml");
    std::vector<std::wstring> files;
    if (ok) {
        std::string text;
        YNode root;
        if (ReadFileUtf8(tmp + L"\\profile.yaml", text)) root = YParse(text);
        auto add = [&](const std::string& f) {
            std::wstring w;
            if (!f.empty() && SafeRelative(f, w) && std::find(files.begin(), files.end(), w) == files.end())
                files.push_back(w);
        };
        if (const YNode* info = root.get("profile")) {
            add(info->str("video"));
            add(info->str("press"));
            add(info->str("release"));
        }
        if (const YNode* src = root.get("sources"); src && src->t == YNode::List)
            for (auto& s : src->l)
                if (const YNode* so = s.get("source")) {
                    if (so->t == YNode::Str) add(so->s);
                    else {
                        add(so->str("press"));
                        add(so->str("release"));
                    }
                }
        ok = !files.empty();
    }
    for (auto& f : files) {
        if (!ok || g_stop) break;
        std::wstring dest = tmp + L"\\" + f;
        size_t slash = dest.find_last_of(L'\\');
        SHCreateDirectoryExW(nullptr, dest.substr(0, slash).c_str(), nullptr);
        if (!Fetch(base + UrlEncodePath(f), dest)) {
            Wh_Log(L"Couldn't download %s/%s", job->name.c_str(), f.c_str());
            ok = false;
        }
    }
    if (ok && !g_stop) Fetch(base + L"LICENSE", tmp + L"\\LICENSE");  // kbsim packs have one; others don't.
    if (ok && !g_stop && !DirExists(final) && MoveFileExW(tmp.c_str(), final.c_str(), 0)) {
        Wh_Log(L"Downloaded the %s pack", job->name.c_str());
        PostThreadMessageW(g_audioTid, WM_SKC_RELOAD, 0, 0);
    } else {
        if (!g_stop) Wh_Log(L"The %s pack download failed", job->name.c_str());
        RemoveTree(tmp);
    }
    CoUninitialize();
    return 0;
}

static void StartDownload(const std::wstring& name, const std::wstring& root) {
    std::lock_guard<std::mutex> lock(g_dlLock);
    if (g_stop || g_dlTried.count(name)) return;
    g_dlTried.insert(name);
    SHCreateDirectoryExW(nullptr, root.c_str(), nullptr);
    auto* job = new DownloadJob{name, root};
    HANDLE t = CreateThread(nullptr, 0, DownloadThread, job, 0, nullptr);
    if (t) g_dlThreads.push_back(t);
    else delete job;
}

// ---------------------------------------------------------------------------
// The audio thread itself.
// ---------------------------------------------------------------------------

struct AudioState {
    Engine engine;
    std::unique_ptr<Profile> kb, mouse;
    std::wstring kbDir, mouseDir;
    int voices = 0;
    Config cfg;
    int kbLast[256];
    int mouseLast[5];
};

static void LoadPacks(AudioState& a, bool force) {
    Config c = GetConfig();
    std::wstring kbDir = PackDir(c, false), mouseDir = PackDir(c, true);
    bool packsMoved = force || kbDir != a.kbDir || mouseDir != a.mouseDir;
    bool poolChanged = c.maxOverlap != a.voices;
    a.cfg = c;
    if (!packsMoved && !poolChanged && a.engine.xa) return;
    // Voices may still read the old clips: stop them before the clips go.
    a.engine.Destroy();
    if (packsMoved) {
        a.kb.reset();
        a.mouse.reset();
        a.kbDir = kbDir;
        a.mouseDir = mouseDir;
        std::fill(std::begin(a.kbLast), std::end(a.kbLast), -1);
        std::fill(std::begin(a.mouseLast), std::end(a.mouseLast), -1);
        std::wstring root = PacksRoot(c);
        for (int m = 0; m < 2; m++) {
            const std::wstring& dir = m ? mouseDir : kbDir;
            if (dir.empty()) continue;
            std::wstring choice = m ? c.mousePack : c.kbPack;
            if (dir != L"classic" && !FileExists(dir + L"\\profile.yaml")) {
                if (c.download && IsBuiltinPack(choice, m == 1)) {
                    Wh_Log(L"Pack %s is missing, downloading it", choice.c_str());
                    StartDownload(choice, root);
                } else {
                    Wh_Log(L"Pack folder %s has no profile.yaml", dir.c_str());
                }
                continue;
            }
            auto p = LoadProfile(dir);
            if (!p) continue;
            Wh_Log(L"Loaded %s pack %s: %d sounds, %d mappings", m ? L"mouse" : L"keyboard", dir.c_str(),
                   (int)p->srcs.size(), (int)p->other.size());
            (m ? a.mouse : a.kb) = std::move(p);
        }
    }
    a.voices = c.maxOverlap;
    if (a.kb || a.mouse) a.engine.Create(c.maxOverlap);
}

static float PitchRatio(const Config& c, bool mouse) {
    if (!c.pitchShift) return 1.0f;
    if (c.pitchApplies != L"both" && c.pitchApplies != (mouse ? L"mouse" : L"keyboard")) return 1.0f;
    int s = std::uniform_int_distribution<int>(c.pitchLow, c.pitchHigh)(Rng());
    return (float)std::pow(2.0, s / 12.0);
}

static void HandlePlay(AudioState& a, WPARAM wp, LPARAM lp) {
    bool mouse = (wp & DEV_MOUSE) != 0, release = (wp & FLAG_RELEASE) != 0, cue = (wp & FLAG_CUE) != 0;
    if (!a.engine.xa) return;
    float vol = g_volume / 100.0f;
    if (cue) {
        // One sound from whichever pack is loaded, preferring the one the shortcut is about.
        Profile* p = mouse ? (a.mouse ? a.mouse.get() : a.kb.get()) : (a.kb ? a.kb.get() : a.mouse.get());
        if (!p) return;
        int clip = p->oneShotPress;
        if (clip < 0) {
            int s = PickOne(p->defaults.empty() ? std::vector<int>{0} : p->defaults);
            if (s >= 0 && s < (int)p->srcs.size()) clip = p->srcs[s].press >= 0 ? p->srcs[s].press : p->srcs[s].release;
        }
        if (p == a.mouse.get()) vol *= a.cfg.mouseVolume / 100.0f;
        if (clip >= 0) a.engine.Play(p->clips[clip], vol, 1.0f);
        return;
    }
    Profile* p = mouse ? a.mouse.get() : a.kb.get();
    if (!p) return;
    if (mouse) vol *= a.cfg.mouseVolume / 100.0f;
    int clip = -1;
    if (p->oneShotPress >= 0 || p->oneShotRelease >= 0) {
        clip = release ? p->oneShotRelease : p->oneShotPress;
    } else if (!mouse) {
        UINT vk = (UINT)(lp & 0xFF);
        int& last = a.kbLast[vk];
        int s = -1;
        if (release) s = last >= 0 ? last : PickKeyboardSource(*p, KeyNames(vk, (lp >> 8) & 1, (UINT)(lp >> 16)));
        else s = last = PickKeyboardSource(*p, KeyNames(vk, (lp >> 8) & 1, (UINT)(lp >> 16)));
        if (release) last = -1;
        if (s >= 0) clip = release ? (p->srcs[s].dual ? p->srcs[s].release : -1) : p->srcs[s].press;
    } else {
        int b = (int)lp;
        if (b < 0 || b > 4) return;
        static const char* kNames[5][2] = {{"left", "left"}, {"right", "right"}, {"middle", "middle"},
                                           {"x1", "back"}, {"x2", "forward"}};
        std::vector<std::string> names = {kNames[b][0], kNames[b][1]};
        int& last = a.mouseLast[b];
        int s = release && last >= 0 ? last : PickMouseSource(*p, names, true);
        last = release ? -1 : s;
        if (s >= 0) clip = release ? (p->srcs[s].dual ? p->srcs[s].release : -1) : p->srcs[s].press;
    }
    if (clip >= 0) a.engine.Play(p->clips[clip], vol, PitchRatio(a.cfg, mouse));
}

static HANDLE g_audioReady, g_inputReady, g_uiReady;

static DWORD WINAPI AudioThread(LPVOID) {
    MSG msg;
    PeekMessageW(&msg, nullptr, WM_USER, WM_USER, PM_NOREMOVE);
    HRESULT co = CoInitializeEx(nullptr, COINIT_MULTITHREADED);
    bool mf = SUCCEEDED(MFStartup(MF_VERSION, MFSTARTUP_LITE));
    if (!mf) Wh_Log(L"Media Foundation didn't start; packs can't be decoded");
    SetEvent(g_audioReady);
    auto a = std::make_unique<AudioState>();
    std::fill(std::begin(a->kbLast), std::end(a->kbLast), -1);
    std::fill(std::begin(a->mouseLast), std::end(a->mouseLast), -1);
    IMMDeviceEnumerator* devices = nullptr;
    DeviceWatcher watcher;
    if (SUCCEEDED(CoCreateInstance(kClsidMMDeviceEnumerator, nullptr, CLSCTX_ALL, kIidIMMDeviceEnumerator,
                                   (void**)&devices)) &&
        devices)
        devices->RegisterEndpointNotificationCallback(&watcher);
    if (mf) LoadPacks(*a, true);
    while (GetMessageW(&msg, nullptr, 0, 0) > 0) {
        switch (msg.message) {
            case WM_SKC_PLAY: HandlePlay(*a, msg.wParam, msg.lParam); break;
            case WM_SKC_CONFIG: if (mf) LoadPacks(*a, false); break;
            case WM_SKC_RELOAD: if (mf) LoadPacks(*a, true); break;
            case WM_SKC_REBUILD: {
                // Several notices come at once; act on the last.
                MSG more;
                while (PeekMessageW(&more, nullptr, WM_SKC_REBUILD, WM_SKC_REBUILD, PM_REMOVE)) {
                }
                Sleep(200);
                a->engine.Destroy();
                if (a->kb || a->mouse) a->engine.Create(a->voices);
                break;
            }
        }
    }
    if (devices) {
        devices->UnregisterEndpointNotificationCallback(&watcher);
        devices->Release();
    }
    a->engine.Destroy();
    a.reset();
    if (mf) MFShutdown();
    if (SUCCEEDED(co)) CoUninitialize();
    return 0;
}

// ---------------------------------------------------------------------------
// Input thread: low-level hooks that only post, and the app the sounds follow.
// ---------------------------------------------------------------------------

static HHOOK g_kbHook, g_mouseHook;
static HWINEVENTHOOK g_fgHook;
static bool g_keyDown[256];
static bool g_buttonDown[5];

struct AppRules {
    bool playByDefault = true;
    std::vector<std::wstring> play, silent, only;
};
static AppRules g_rules;  // Input thread only.

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

static bool MatchAny(const std::vector<std::wstring>& list, const std::wstring& name, const std::wstring& path) {
    for (auto& pat : list) {
        if (PathMatchSpecW(name.c_str(), pat.c_str())) return true;
        if (!path.empty() && PathMatchSpecW(path.c_str(), pat.c_str())) return true;
    }
    return false;
}

static void EvaluateForeground(HWND hwnd) {
    if (g_rules.only.empty() && g_rules.play.empty() && g_rules.silent.empty()) {
        g_appAllowed = g_rules.playByDefault;
        return;
    }
    std::wstring path, name;
    DWORD pid = 0;
    if (hwnd) GetWindowThreadProcessId(hwnd, &pid);
    if (pid) {
        if (HANDLE h = OpenProcess(PROCESS_QUERY_LIMITED_INFORMATION, FALSE, pid)) {
            WCHAR buf[MAX_PATH * 2];
            DWORD n = ARRAYSIZE(buf);
            if (QueryFullProcessImageNameW(h, 0, buf, &n)) path.assign(buf, n);
            CloseHandle(h);
        }
    }
    name = path.substr(path.find_last_of(L'\\') == std::wstring::npos ? 0 : path.find_last_of(L'\\') + 1);
    bool allowed;
    if (!g_rules.only.empty()) allowed = !name.empty() && MatchAny(g_rules.only, name, path);
    else if (!name.empty() && MatchAny(g_rules.play, name, path)) allowed = true;
    else if (!name.empty() && MatchAny(g_rules.silent, name, path)) allowed = false;
    else allowed = g_rules.playByDefault;
    g_appAllowed = allowed;
}

static void RefreshRules() {
    Config c = GetConfig();
    g_rules.playByDefault = c.appMode != L"disable";
    g_rules.play = SplitList(c.playApps);
    g_rules.silent = SplitList(c.silentApps);
    g_rules.only = SplitList(c.onlyApps);
    EvaluateForeground(GetForegroundWindow());
}

static bool IsModifierVk(UINT vk) {
    switch (vk) {
        case VK_SHIFT: case VK_LSHIFT: case VK_RSHIFT:
        case VK_CONTROL: case VK_LCONTROL: case VK_RCONTROL:
        case VK_MENU: case VK_LMENU: case VK_RMENU:
        case VK_LWIN: case VK_RWIN:
            return true;
    }
    return false;
}

static LRESULT CALLBACK KeyboardProc(int code, WPARAM wp, LPARAM lp) {
    if (code == HC_ACTION) {
        const KBDLLHOOKSTRUCT* k = (const KBDLLHOOKSTRUCT*)lp;
        UINT vk = k->vkCode & 0xFF;
        bool up = wp == WM_KEYUP || wp == WM_SYSKEYUP;
        bool down = wp == WM_KEYDOWN || wp == WM_SYSKEYDOWN;
        bool injected = (k->flags & (LLKHF_INJECTED | LLKHF_LOWER_IL_INJECTED)) != 0;
        // AltGr sends a fake left Ctrl first (scan code with the 0x200 bit); it is not a key.
        bool fakeCtrl = vk == VK_LCONTROL && (k->scanCode & 0x200);
        if ((down || up) && !fakeCtrl && !(injected && g_ignoreInjected)) {
            bool play = g_onAll && g_onKeyboard && g_appAllowed;
            LPARAM data = (LPARAM)(vk | ((k->flags & LLKHF_EXTENDED) ? 0x100 : 0) | ((k->scanCode & 0xFFFF) << 16));
            if (down) {
                // A key already down is a repeat only if Windows still sees it held; otherwise its
                // key-up was lost (a lock screen, a UAC prompt) and this is a new press.
                bool repeat = g_keyDown[vk] && (GetAsyncKeyState((int)vk) & 0x8000);
                g_keyDown[vk] = true;
                if (play && (!repeat || (g_repeat && !IsModifierVk(vk))))
                    PostThreadMessageW(g_audioTid, WM_SKC_PLAY, DEV_KEYBOARD, data);
            } else {
                bool was = g_keyDown[vk];
                g_keyDown[vk] = false;
                if (play && was && g_release) PostThreadMessageW(g_audioTid, WM_SKC_PLAY, DEV_KEYBOARD | FLAG_RELEASE, data);
            }
        }
    }
    return CallNextHookEx(g_kbHook, code, wp, lp);
}

static LRESULT CALLBACK MouseProc(int code, WPARAM wp, LPARAM lp) {
    if (code == HC_ACTION) {
        const MSLLHOOKSTRUCT* m = (const MSLLHOOKSTRUCT*)lp;
        int b = -1;
        bool up = false;
        switch (wp) {
            case WM_LBUTTONDOWN: b = 0; break;
            case WM_LBUTTONUP: b = 0, up = true; break;
            case WM_RBUTTONDOWN: b = 1; break;
            case WM_RBUTTONUP: b = 1, up = true; break;
            case WM_MBUTTONDOWN: b = 2; break;
            case WM_MBUTTONUP: b = 2, up = true; break;
            case WM_XBUTTONDOWN: case WM_XBUTTONUP:
                b = HIWORD(m->mouseData) == XBUTTON2 ? 4 : 3;
                up = wp == WM_XBUTTONUP;
                break;
        }
        bool injected = (m->flags & (LLMHF_INJECTED | LLMHF_LOWER_IL_INJECTED)) != 0;
        if (b >= 0 && !(injected && g_ignoreInjected) && (b < 3 || g_side)) {
            bool play = g_onAll && g_onMouse && g_appAllowed;
            if (!up) {
                g_buttonDown[b] = true;
                if (play) PostThreadMessageW(g_audioTid, WM_SKC_PLAY, DEV_MOUSE, b);
            } else {
                bool was = g_buttonDown[b];
                g_buttonDown[b] = false;
                if (play && was && g_release) PostThreadMessageW(g_audioTid, WM_SKC_PLAY, DEV_MOUSE | FLAG_RELEASE, b);
            }
        }
    }
    return CallNextHookEx(g_mouseHook, code, wp, lp);
}

static void CALLBACK ForegroundProc(HWINEVENTHOOK, DWORD, HWND hwnd, LONG, LONG, DWORD, DWORD) {
    EvaluateForeground(hwnd);
}

static DWORD WINAPI InputThread(LPVOID) {
    MSG msg;
    PeekMessageW(&msg, nullptr, WM_USER, WM_USER, PM_NOREMOVE);
    RefreshRules();
    g_kbHook = SetWindowsHookExW(WH_KEYBOARD_LL, KeyboardProc, nullptr, 0);
    g_mouseHook = SetWindowsHookExW(WH_MOUSE_LL, MouseProc, nullptr, 0);
    if (!g_kbHook || !g_mouseHook) Wh_Log(L"Input hook failed (error %lu)", GetLastError());
    g_fgHook = SetWinEventHook(EVENT_SYSTEM_FOREGROUND, EVENT_SYSTEM_FOREGROUND, nullptr, ForegroundProc, 0, 0,
                               WINEVENT_OUTOFCONTEXT);
    SetEvent(g_inputReady);
    while (GetMessageW(&msg, nullptr, 0, 0) > 0) {
        if (msg.message == WM_SKC_RULES) RefreshRules();
        DispatchMessageW(&msg);
    }
    if (g_fgHook) UnhookWinEvent(g_fgHook);
    if (g_mouseHook) UnhookWindowsHookEx(g_mouseHook);
    if (g_kbHook) UnhookWindowsHookEx(g_kbHook);
    g_fgHook = nullptr;
    g_mouseHook = g_kbHook = nullptr;
    return 0;
}

// ---------------------------------------------------------------------------
// UI thread: tray icon, menu, shortcuts.
// ---------------------------------------------------------------------------

constexpr UINT TrayIconId() {
    UINT hash = 2166136261u;
    for (PCWSTR p = WH_MOD_ID; *p; p++) hash = (hash ^ (UINT)*p) * 16777619u;
    return hash | 0x80000000u;
}
constexpr UINT kTrayId = TrayIconId();
constexpr UINT_PTR kVolumeTimer = 7;
static UINT g_taskbarCreated;
static bool g_trayAdded;
static HICON g_trayIcon;
static bool g_hotkeyOn[HK_COUNT];

static void EnableDarkMenus() {
    HMODULE ux = GetModuleHandleW(L"uxtheme.dll");
    if (!ux) ux = LoadLibraryExW(L"uxtheme.dll", nullptr, LOAD_LIBRARY_SEARCH_SYSTEM32);
    if (!ux) return;
    using SetMode = int(WINAPI*)(int);
    using Flush = void(WINAPI*)();
    if (auto set = (SetMode)GetProcAddress(ux, MAKEINTRESOURCEA(135))) set(2 /* ForceDark */);
    if (auto flush = (Flush)GetProcAddress(ux, MAKEINTRESOURCEA(136))) flush();
}

// A rounded square in the blue to mauve gradient with the keyboard glyph, drawn with GDI so
// the tray never shares the settings window's Direct2D factories.
static HICON MakeTrayIcon(bool muted) {
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
    // Glyph coverage: white text on black, read back from one channel.
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
    WCHAR g[2] = {(WCHAR)(muted ? 0xE74F : 0xE765), 0};
    DrawTextW(dc, g, 1, &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE | DT_NOPREFIX);
    GdiFlush();
    SelectObject(dc, oldFont);
    DeleteObject(font);
    SelectObject(dc, old);
    DeleteDC(dc);

    // Mocha blue 89B4FA to mauve CBA6F7; grey overlay0 to surface2 when muted. Glyph in crust 11111B.
    const float c0[3] = {muted ? 0x6C / 255.f : 0x89 / 255.f, muted ? 0x70 / 255.f : 0xB4 / 255.f, muted ? 0x86 / 255.f : 0xFA / 255.f};
    const float c1[3] = {muted ? 0x58 / 255.f : 0xCB / 255.f, muted ? 0x5B / 255.f : 0xA6 / 255.f, muted ? 0x70 / 255.f : 0xF7 / 255.f};
    uint32_t* px = (uint32_t*)bits;
    const uint32_t* gp = (const uint32_t*)glyphBits;
    for (int y = 0; y < size; y++)
        for (int x = 0; x < size; x++) {
            float t = std::clamp((x + y) / (2.0f * (size - 1)), 0.0f, 1.0f);
            float cov = ((gp[y * size + x] >> 8) & 0xFF) / 255.0f;
            float rgb[3];
            for (int i = 0; i < 3; i++) {
                float base = c0[i] + (c1[i] - c0[i]) * t;
                rgb[i] = base * cov;  // Premultiplied; clear where there is no glyph.
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

static bool SoundsMuted() { return !g_onAll || (!g_onKeyboard && !g_onMouse); }

static void TrayTip(NOTIFYICONDATAW& nid) {
    std::wstring tip = L"Seamless Key Click: ";
    if (!g_onAll) tip += L"sounds off";
    else if (g_onKeyboard && g_onMouse) tip += L"keyboard and mouse on";
    else if (g_onKeyboard) tip += L"keyboard on, mouse off";
    else if (g_onMouse) tip += L"mouse on, keyboard off";
    else tip += L"sounds off";
    tip += L", volume " + std::to_wstring(g_volume.load());
    wcsncpy_s(nid.szTip, tip.c_str(), _TRUNCATE);
}

static void UpdateTray(bool add) {
    Config c = GetConfig();
    NOTIFYICONDATAW nid{sizeof(nid)};
    nid.hWnd = g_msgWnd;
    nid.uID = kTrayId;
    if (!c.trayIcon) {
        if (g_trayAdded) Shell_NotifyIconW(NIM_DELETE, &nid);
        g_trayAdded = false;
        return;
    }
    HICON icon = MakeTrayIcon(SoundsMuted());
    nid.uFlags = NIF_MESSAGE | NIF_ICON | NIF_TIP | NIF_SHOWTIP;
    nid.uCallbackMessage = WM_SKC_TRAY;
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

static void RegisterHotkeys() {
    Config c = GetConfig();
    for (int i = 0; i < HK_COUNT; i++) {
        if (g_hotkeyOn[i]) UnregisterHotKey(g_msgWnd, i + 1);
        g_hotkeyOn[i] = false;
        UINT mods, vk;
        if (c.hotkeys[i].empty()) continue;
        if (!Hotkey_Parse(c.hotkeys[i], mods, vk)) {
            Wh_Log(L"Shortcut \"%s\" isn't one the mod understands", c.hotkeys[i].c_str());
            continue;
        }
        g_hotkeyOn[i] = RegisterHotKey(g_msgWnd, i + 1, mods | MOD_NOREPEAT, vk) != FALSE;
        if (!g_hotkeyOn[i]) Wh_Log(L"Shortcut %s is taken by another app (error %lu)", c.hotkeys[i].c_str(), GetLastError());
    }
}

// ---------------------------------------------------------------------------
// Notifier dock: a small dock that says what a shortcut or the tray menu just
// changed. The settings window's material (the launcher grid's acrylic under a
// Mocha tint), one blue to mauve edge, FiraCode text. It lives on the UI
// thread, never takes focus, and steps aside when the pointer reaches it.
// ---------------------------------------------------------------------------
// The notifier dock's glass, as Seamless Dictate does it: Windows' own blur in a click-through
// window right under the dock, clipped to the dock's rounded box by a composition clip. The
// rounded shape is the dock's, not Windows' corner (which on newer builds is larger than the
// painted edge and cut it off at the corners).
struct SkcCompositorDesktopInterop : ::IUnknown {
    virtual HRESULT __stdcall CreateDesktopWindowTarget(HWND window, BOOL isTopmost, void** target) = 0;
    virtual HRESULT __stdcall EnsureOnThread(DWORD threadId) = 0;
};
template <>
inline constexpr winrt::guid winrt::impl::guid_v<SkcCompositorDesktopInterop>{
    0x29E691FA, 0x4567, 0x4DCA, {0xB3, 0x19, 0xD0, 0xF2, 0x07, 0xEB, 0x68, 0x07}};

struct SkcEffectD2D1Interop : ::IUnknown {
    virtual HRESULT __stdcall GetEffectId(GUID* id) = 0;
    virtual HRESULT __stdcall GetNamedPropertyMapping(LPCWSTR name, UINT* index, int* mapping) = 0;
    virtual HRESULT __stdcall GetPropertyCount(UINT* count) = 0;
    virtual HRESULT __stdcall GetProperty(UINT index, void** value) = 0;
    virtual HRESULT __stdcall GetSource(UINT index, void** source) = 0;
    virtual HRESULT __stdcall GetSourceCount(UINT* count) = 0;
};
template <>
inline constexpr winrt::guid winrt::impl::guid_v<SkcEffectD2D1Interop>{
    0x2FC57384, 0xA068, 0x44D7, {0xA3, 0x31, 0x30, 0x98, 0x2F, 0xCF, 0x71, 0x77}};

// A Gaussian blur over the host backdrop, so text behind the dock melts into colour.
struct SkcGlassBlur : winrt::implements<SkcGlassBlur, winrt::Windows::Graphics::Effects::IGraphicsEffect,
                                        winrt::Windows::Graphics::Effects::IGraphicsEffectSource,
                                        SkcEffectD2D1Interop> {
    SkcGlassBlur(float sigma, winrt::Windows::Graphics::Effects::IGraphicsEffectSource source)
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

namespace skcdock {

constexpr WCHAR kGlassClass[] = L"SeamlessKeyClickGlass";

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
    // The blur under the whole dock window (pixels), with rounded corners of `radius` pixels.
    // False: Windows can't show it, and the dock paints itself solid.
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
            Wh_Log(L"Dock glass unavailable: %08X", (unsigned)e.code());
            m_failed = true;
            Hide();
            return false;
        }
    }
    void Hide() {
        if (m_hwnd && m_visible) ShowWindow(m_hwnd, SW_HIDE);
        m_visible = false;
    }
    bool Visible() const { return m_visible; }
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
                Wh_Log(L"Ending the dock glass queue failed: %08X", (unsigned)e.code());
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
        const BOOL hostBackdrop = TRUE;  // DWMWA_USE_HOSTBACKDROPBRUSH: a desktop app's window shows the blur only with this.
        winrt::check_hresult(DwmSetWindowAttribute(m_hwnd, 17, &hostBackdrop, sizeof(hostBackdrop)));
        auto interop = m_compositor.as<SkcCompositorDesktopInterop>();
        winrt::check_hresult(interop->CreateDesktopWindowTarget(m_hwnd, TRUE, winrt::put_abi(m_target)));
        const Composition::ContainerVisual root = m_compositor.CreateContainerVisual();
        root.RelativeSizeAdjustment({1, 1});
        m_target.Root(root);
        m_visual = m_compositor.CreateSpriteVisual();
        try {
            const auto effect =
                winrt::make<SkcGlassBlur>(18.0f, Composition::CompositionEffectSourceParameter(L"Backdrop"));
            const auto brush = m_compositor.CreateEffectFactory(effect).CreateBrush();
            brush.SetSourceParameter(L"Backdrop", m_compositor.CreateHostBackdropBrush());
            m_visual.Brush(brush);
        } catch (winrt::hresult_error const& e) {
            Wh_Log(L"Extra dock blur unavailable: %08X", (unsigned)e.code());
            m_visual.Brush(m_compositor.CreateHostBackdropBrush());
        }
        m_shape = m_compositor.CreateRoundedRectangleGeometry();
        m_visual.Clip(m_compositor.CreateGeometricClip(m_shape));
        root.Children().InsertAtTop(m_visual);
        return true;
    }

    HWND m_hwnd = nullptr;
    bool m_failed = false, m_visible = false, m_registered = false;
    int m_x = 0, m_y = 0, m_w = 0, m_h = 0;
    winrt::Windows::System::DispatcherQueueController m_queue{nullptr};
    winrt::Windows::UI::Composition::Compositor m_compositor{nullptr};
    winrt::Windows::UI::Composition::Desktop::DesktopWindowTarget m_target{nullptr};
    winrt::Windows::UI::Composition::SpriteVisual m_visual{nullptr};
    winrt::Windows::UI::Composition::CompositionRoundedRectangleGeometry m_shape{nullptr};
};

constexpr WCHAR kGlyphKeyboard = 0xE765, kGlyphMouse = 0xE962, kGlyphSound = 0xE767, kGlyphMute = 0xE74F,
                kGlyphPack = 0xE8D6, kGlyphLook = 0xE790;

struct Message {
    WCHAR glyph = kGlyphSound;
    std::wstring title, detail;
    int state = -1;  // The pill on the right: 1 On, 0 Off, -1 none.
    int level = -1;  // 0 to 100: a level bar under the title and the number in the pill.
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

constexpr WCHAR kClass[] = L"SeamlessKeyClickNotifier";
constexpr UINT_PTR kAnimTimer = 1, kHideTimer = 2;
constexpr float kH = 60, kMinW = 250, kMaxW = 480, kSlide = 12;
constexpr DWORD kInMs = 170, kOutMs = 140;

enum class Phase { Hidden, In, Shown, Out };

struct Dock {
    HWND hwnd = nullptr;
    Com<ID2D1Factory> d2d;
    Com<IDWriteFactory> dw;
    Com<ID2D1HwndRenderTarget> rt;
    Com<IDWriteTextFormat> fTitle, fDetail, fPill, fIcon;
    Message msg;
    std::wstring look;  // The look applied to the window ("" until the first show).
    // The dock's own corner (DIPs); the glass under it is clipped to the same curve.
    float tint = 0.62f, wDip = kMinW, hDip = kH, scale = 1, ringRad = 12, fade = 1;
    UINT dpi = 96;
    int x = 0, y = 0, slideX = 0, slideY = 0, pw = 0, ph = 0;
    POINT showPt{};
    Phase phase = Phase::Hidden;
    DWORD phaseStart = 0;
    bool glass = true;      // The look asks for glass.
    bool wantGlass = true;  // ... and Windows' transparency effects are on (checked on each show).
    bool glassOn = false;   // The blur is under the dock now; otherwise the fill is solid.
};
static Dock g;
static Glass s_glass;

struct DpiScope {
    DPI_AWARENESS_CONTEXT old;
    DpiScope() : old(SetThreadDpiAwarenessContext(DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2)) {}
    ~DpiScope() {
        if (old) SetThreadDpiAwarenessContext(old);
    }
};

static UINT MonitorDpi(HMONITOR m) {
    using Fn = HRESULT(WINAPI*)(HMONITOR, int, UINT*, UINT*);
    static Fn fn = (Fn)(void*)GetProcAddress(LoadLibraryExW(L"shcore.dll", nullptr, LOAD_LIBRARY_SEARCH_SYSTEM32),
                                             "GetDpiForMonitor");
    UINT x = 0, y = 0;
    if (fn && SUCCEEDED(fn(m, 0 /* MDT_EFFECTIVE_DPI */, &x, &y)) && x) return x;
    UINT d = GetDpiForSystem();
    return d ? d : 96;
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
        const wchar_t* icons = FamilyExists(L"Segoe Fluent Icons") ? L"Segoe Fluent Icons" : L"Segoe MDL2 Assets";
        MakeFormat(g.fTitle, family, 14.5f, 600, false);
        MakeFormat(g.fDetail, family, 12.5f, 500, false);
        MakeFormat(g.fPill, family, 12, 700, true);
        MakeFormat(g.fIcon, icons, 18, 400, true);
    }
    return g.fTitle && g.fDetail && g.fPill && g.fIcon;
}

static float TextW(IDWriteTextFormat* f, const std::wstring& s) {
    if (!f || s.empty()) return 0;
    Com<IDWriteTextLayout> layout;
    if (FAILED(g.dw->CreateTextLayout(s.c_str(), (UINT32)s.size(), f, 4000, 100, layout.put()))) return 0;
    DWRITE_TEXT_METRICS m{};
    layout->GetMetrics(&m);
    return m.widthIncludingTrailingWhitespace;
}

static std::wstring PillText(const Message& m) {
    if (m.level >= 0) return m.level == 0 ? L"Muted" : std::to_wstring(m.level) + L"%";
    if (m.state == 1) return L"On";
    if (m.state == 0) return L"Off";
    return {};
}

static void ApplyLook(const Config& c) {
    std::wstring look = c.ntLook;
    g.tint = c.ntTint / 100.0f;
    if (look == g.look) return;
    g.look = look;
    g.glass = look == L"glass";
    const HWND hwnd = g.hwnd;
    BOOL dark = TRUE;
    DwmSetWindowAttribute(hwnd, 20 /* DWMWA_USE_IMMERSIVE_DARK_MODE */, &dark, sizeof(dark));
    // Windows doesn't round or edge the dock: its corner is larger than the painted gradient edge
    // on newer builds and cut that edge off. The dock paints its own rounded shape, and the
    // glass window under it is clipped to the same curve.
    int corner = 1;  // DWMWCP_DONOTROUND
    DwmSetWindowAttribute(hwnd, 33 /* DWMWA_WINDOW_CORNER_PREFERENCE */, &corner, sizeof(corner));
    COLORREF none = 0xFFFFFFFE;  // DWMWA_COLOR_NONE: the gradient edge is the only edge.
    DwmSetWindowAttribute(hwnd, 34 /* DWMWA_BORDER_COLOR */, &none, sizeof(none));
    // Per-pixel alpha (no blur from this): outside the rounded shape the dock is see-through.
    DWM_BLURBEHIND bb{};
    bb.dwFlags = DWM_BB_ENABLE | DWM_BB_BLURREGION;
    bb.fEnable = TRUE;
    bb.hRgnBlur = CreateRectRgn(0, 0, -1, -1);
    DwmEnableBlurBehindWindow(hwnd, &bb);
    if (bb.hRgnBlur) DeleteObject(bb.hRgnBlur);
}

static bool EnsureRt() {
    if (g.rt) return true;
    D2D1_RENDER_TARGET_PROPERTIES props = D2D1::RenderTargetProperties(
        D2D1_RENDER_TARGET_TYPE_DEFAULT, D2D1::PixelFormat(DXGI_FORMAT_B8G8R8A8_UNORM, D2D1_ALPHA_MODE_PREMULTIPLIED),
        96.0f * g.scale, 96.0f * g.scale);
    return SUCCEEDED(g.d2d->CreateHwndRenderTarget(
        props,
        D2D1::HwndRenderTargetProperties(g.hwnd, D2D1::SizeU(std::max(1, g.pw), std::max(1, g.ph)),
                                         D2D1_PRESENT_OPTIONS_IMMEDIATELY),
        g.rt.put()));
}

static void Paint() {
    if (!g.hwnd || !EnsureRt()) return;
    ID2D1HwndRenderTarget* rt = g.rt.get();
    Com<ID2D1SolidColorBrush> sb;
    rt->BeginDraw();
    rt->SetTransform(D2D1::Matrix3x2F::Identity());
    rt->Clear(D2D1::ColorF(0, 0, 0, 0));
    if (FAILED(rt->CreateSolidColorBrush(Color(0, 0), sb.put()))) {
        rt->EndDraw();
        return;
    }
    const float a = g.fade;
    auto solid = [&](UINT32 c, float alpha) {
        sb->SetColor(Color(c, alpha * a));
        return sb.get();
    };
    auto grad = [&](const D2D1_RECT_F& r, float alpha, Com<ID2D1LinearGradientBrush>& out) {
        D2D1_GRADIENT_STOP stops[2] = {{0, Color(col::blue, alpha * a)}, {1, Color(col::mauve, alpha * a)}};
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

    const Message& m = g.msg;
    const float W = g.wDip, H = g.hDip;
    const D2D1_RECT_F all{0, 0, W, H};
    // The Mocha fill over the blur (all of it when solid), then the one gradient edge.
    rt->FillRoundedRectangle(D2D1::RoundedRect(all, g.ringRad, g.ringRad), solid(col::base, g.glassOn ? g.tint : 1.0f));
    gradFill(all, g.ringRad, 0.05f);
    gradRing(all, g.ringRad, 0.95f, 1.5f);

    // The icon in a small well.
    const bool off = m.state == 0 || m.level == 0;
    const D2D1_RECT_F well{14, H / 2 - 18, 50, H / 2 + 18};
    gradFill(well, 10, off ? 0.08f : 0.2f);
    gradRing(well, 10, off ? 0.45f : 0.85f, 1.25f);
    text(g.fIcon.get(), std::wstring(1, m.glyph), well, off ? col::overlay1 : col::blue, 1);

    // The pill on the right: On, Off or the level.
    const std::wstring pill = PillText(m);
    float right = W - 16;
    if (!pill.empty()) {
        float pwid = TextW(g.fPill.get(), pill) + 24;
        D2D1_RECT_F p{W - 16 - pwid, H / 2 - 12, W - 16, H / 2 + 12};
        if (off) {
            rt->FillRoundedRectangle(D2D1::RoundedRect(p, 12, 12), solid(col::surface1, 0.85f));
            D2D1_RECT_F in{p.left + 0.5f, p.top + 0.5f, p.right - 0.5f, p.bottom - 0.5f};
            rt->DrawRoundedRectangle(D2D1::RoundedRect(in, 11.5f, 11.5f), solid(col::overlay0, 0.6f), 1);
            text(g.fPill.get(), pill, p, col::subtext1, 1);
        } else {
            gradFill(p, 12, 1);
            text(g.fPill.get(), pill, p, col::crust, 1);
        }
        right = p.left - 12;
    }

    // Title, then the detail line or the level bar.
    const float tx = 62;
    const bool second = m.level >= 0 || !m.detail.empty();
    text(g.fTitle.get(), m.title, second ? D2D1_RECT_F{tx, 9, right, 31} : D2D1_RECT_F{tx, 0, right, H}, col::text, 1);
    if (m.level >= 0) {
        D2D1_RECT_F track{tx, 37, right, 43};
        rt->FillRoundedRectangle(D2D1::RoundedRect(track, 3, 3), solid(col::surface1, 0.8f));
        if (m.level > 0) {
            D2D1_RECT_F fill{tx, 37, tx + std::max(6.0f, (right - tx) * m.level / 100.0f), 43};
            Com<ID2D1LinearGradientBrush> b;
            if (grad(track, 1, b)) rt->FillRoundedRectangle(D2D1::RoundedRect(fill, 3, 3), b.get());
        }
    } else if (!m.detail.empty()) {
        text(g.fDetail.get(), m.detail, {tx, 31, right, 51}, col::subtext0, 1);
    }
    if (rt->EndDraw() == D2DERR_RECREATE_TARGET) g.rt.reset();
}

static void Place(float off) {
    const int x = g.x + (int)lroundf(g.slideX * off), y = g.y + (int)lroundf(g.slideY * off);
    SetWindowPos(g.hwnd, HWND_TOPMOST, x, y, g.pw, g.ph, SWP_NOACTIVATE | SWP_SHOWWINDOW);
    // The glass follows the dock, fades with it and sits right under it.
    if (g.glass && g.wantGlass) {
        g.glassOn = s_glass.Show(g.hwnd, x, y, g.pw, g.ph, g.ringRad * g.scale, g.fade);
    } else {
        s_glass.Hide();
        g.glassOn = false;
    }
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
    g.phase = Phase::Out;
    g.phaseStart = GetTickCount();
    SetTimer(g.hwnd, kAnimTimer, 15, nullptr);
}

static void Tick() {
    float t = (GetTickCount() - g.phaseStart) / (float)(g.phase == Phase::In ? kInMs : kOutMs);
    if (g.phase == Phase::In) {
        g.fade = Ease(t * 1.4f);
        Place(1 - Ease(t));
        Paint();
        if (t >= 1) {
            g.phase = Phase::Shown;
            KillTimer(g.hwnd, kAnimTimer);
        }
    } else if (g.phase == Phase::Out) {
        if (t >= 1) return Hide();
        g.fade = 1 - Ease(t);
        Place(Ease(t));
        Paint();
    } else {
        KillTimer(g.hwnd, kAnimTimer);
    }
}

static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) {
    switch (msg) {
        case WM_MOUSEACTIVATE: return MA_NOACTIVATE;
        case WM_MOUSEMOVE: {
            // Windows sends one when the dock appears under a still pointer; only a real move counts.
            POINT pt{};
            GetCursorPos(&pt);
            if (pt.x != g.showPt.x || pt.y != g.showPt.y) StartOut();
            return 0;
        }
        case WM_LBUTTONDOWN:
        case WM_RBUTTONDOWN: StartOut(); return 0;
        case WM_TIMER:
            if (wp == kAnimTimer) Tick();
            else if (wp == kHideTimer) StartOut();
            return 0;
        case WM_ERASEBKGND: return 1;
        case WM_PAINT: {
            PAINTSTRUCT ps;
            BeginPaint(hwnd, &ps);
            Paint();
            EndPaint(hwnd, &ps);
            return 0;
        }
        case WM_DPICHANGED: return 0;  // Show sizes it for its monitor.
        case WM_DISPLAYCHANGE: Hide(); return 0;
    }
    return DefWindowProcW(hwnd, msg, wp, lp);
}

static bool EnsureWindow() {
    if (g.hwnd) return true;
    WNDCLASSW wc{};
    wc.lpfnWndProc = WndProc;
    wc.hInstance = (HINSTANCE)windhawk_tool_mod::GetCurrentModuleHandle();
    wc.lpszClassName = kClass;
    wc.hCursor = LoadCursorW(nullptr, IDC_ARROW);
    RegisterClassW(&wc);
    g.hwnd = CreateWindowExW(WS_EX_TOPMOST | WS_EX_TOOLWINDOW | WS_EX_NOACTIVATE, kClass, L"Seamless Key Click",
                             WS_POPUP, 0, 0, 1, 1, nullptr, nullptr, wc.hInstance, nullptr);
    g.look.clear();
    return g.hwnd != nullptr;
}

static HMONITOR TargetMonitor(const Config& c) {
    POINT pt{};
    GetCursorPos(&pt);
    if (c.ntDisplay == L"primary") return MonitorFromPoint({0, 0}, MONITOR_DEFAULTTOPRIMARY);
    if (c.ntDisplay == L"focused") {
        HWND fg = GetForegroundWindow();
        DWORD pid = 0;
        if (fg) GetWindowThreadProcessId(fg, &pid);
        // The tray menu makes this process the foreground; then the pointer's screen is the one.
        if (fg && pid != GetCurrentProcessId()) return MonitorFromWindow(fg, MONITOR_DEFAULTTOPRIMARY);
    }
    return MonitorFromPoint(pt, MONITOR_DEFAULTTOPRIMARY);
}

static void Show(const Message& m) {
    Config c = GetConfig();
    if (!c.ntOn) return;
    if (!c.ntFullscreen) {
        QUERY_USER_NOTIFICATION_STATE st{};
        if (SUCCEEDED(SHQueryUserNotificationState(&st)) &&
            (st == QUNS_RUNNING_D3D_FULL_SCREEN || st == QUNS_PRESENTATION_MODE || st == QUNS_BUSY))
            return;
    }
    DpiScope dpiScope;
    if (!EnsureWindow() || !EnsureFactories()) return;
    ApplyLook(c);
    g.msg = m;
    GetCursorPos(&g.showPt);

    // Width fits the words, within limits.
    float textW = TextW(g.fTitle.get(), m.title);
    if (m.level >= 0) textW = std::max(textW, 150.0f);
    else textW = std::max(textW, TextW(g.fDetail.get(), m.detail));
    std::wstring pill = PillText(m);
    float pillW = pill.empty() ? 0 : TextW(g.fPill.get(), pill) + 24 + 12;
    g.wDip = std::clamp(62 + textW + pillW + 18, kMinW, kMaxW);
    g.hDip = kH;

    HMONITOR mon = TargetMonitor(c);
    MONITORINFO mi{sizeof(mi)};
    GetMonitorInfoW(mon, &mi);
    const RECT wa = mi.rcWork;
    g.dpi = MonitorDpi(mon);
    const float size = c.ntSize == L"compact" ? 0.88f : c.ntSize == L"large" ? 1.2f : 1.0f;
    g.scale = g.dpi / 96.0f * size;
    g.wantGlass = GlassAvailable();
    g.pw = (int)lroundf(g.wDip * g.scale);
    g.ph = (int)lroundf(g.hDip * g.scale);
    const int margin = (int)lroundf(c.ntMargin * g.dpi / 96.0f), slide = (int)lroundf(kSlide * g.dpi / 96.0f);
    const std::wstring& pos = c.ntPos;
    const bool left = pos == L"topLeft" || pos == L"bottomLeft", right = pos == L"topRight" || pos == L"bottomRight";
    const bool top = pos.rfind(L"top", 0) == 0, middle = pos == L"center";
    g.x = left ? wa.left + margin : right ? wa.right - margin - g.pw : (wa.left + wa.right - g.pw) / 2;
    g.y = top ? wa.top + margin : middle ? (wa.top + wa.bottom - g.ph) / 2 : wa.bottom - margin - g.ph;
    g.slideX = 0;
    g.slideY = top ? -slide : slide;

    if (g.rt) {
        g.rt->SetDpi(96.0f * g.scale, 96.0f * g.scale);
        g.rt->Resize(D2D1::SizeU(std::max(1, g.pw), std::max(1, g.ph)));
    }
    const bool fresh = g.phase == Phase::Hidden || g.phase == Phase::Out;
    if (fresh) {
        g.phase = Phase::In;
        g.phaseStart = GetTickCount();
        g.fade = 0;
        Place(1);
        SetTimer(g.hwnd, kAnimTimer, 15, nullptr);
    } else {
        // Already showing: the new words replace the old in place.
        g.fade = 1;
        if (g.phase == Phase::Shown) Place(0);
    }
    Paint();
    SetTimer(g.hwnd, kHideTimer, (UINT)c.ntDuration, nullptr);
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
    g.glassOn = false;
    g.rt.reset();
    g.fTitle.reset();
    g.fDetail.reset();
    g.fPill.reset();
    g.fIcon.reset();
    g.dw.reset();
    g.d2d.reset();
    g.phase = Phase::Hidden;
    UnregisterClassW(kClass, (HINSTANCE)windhawk_tool_mod::GetCurrentModuleHandle());
}

}  // namespace skcdock

static std::wstring PackLabel(const Config& c, bool mouse) {
    const std::wstring& choice = mouse ? c.mousePack : c.kbPack;
    if (choice.empty() || choice == L"none") return mouse ? L"No mouse pack picked" : L"No keyboard pack picked";
    if (choice == L"custom") {
        const std::wstring& custom = mouse ? c.mouseCustom : c.kbCustom;
        return custom.empty() ? L"Your own pack" : custom;
    }
    for (const auto& p : kBuiltinPacks)
        if (choice == p.name) return p.label;
    return choice;
}

static void NotifyToggle(int which) {
    Config c = GetConfig();
    if (!c.ntSounds) return;
    skcdock::Message m;
    const bool on = which == HK_ALL ? g_onAll : which == HK_KEYBOARD ? g_onKeyboard : g_onMouse;
    m.state = on ? 1 : 0;
    if (which == HK_ALL) {
        m.title = L"Sounds";
        m.glyph = on ? skcdock::kGlyphSound : skcdock::kGlyphMute;
        m.detail = !on                         ? L"Nothing plays until you turn them back on"
                   : g_onKeyboard && g_onMouse ? L"Keyboard and mouse"
                   : g_onKeyboard              ? L"Keyboard only, mouse is off"
                   : g_onMouse                 ? L"Mouse only, keyboard is off"
                                               : L"Keyboard and mouse are both off";
    } else {
        const bool mouse = which == HK_MOUSE;
        m.title = mouse ? L"Mouse sounds" : L"Keyboard sounds";
        m.glyph = mouse ? skcdock::kGlyphMouse : skcdock::kGlyphKeyboard;
        m.detail = !g_onAll ? std::wstring(L"All sounds are off") : PackLabel(c, mouse);
    }
    skcdock::Show(m);
}

static void NotifyVolume(int v) {
    if (!GetConfig().ntVolume) return;
    skcdock::Message m;
    m.title = L"Volume";
    m.glyph = v == 0 ? skcdock::kGlyphMute : skcdock::kGlyphSound;
    m.level = v;
    skcdock::Show(m);
}

static void NotifyPack(bool mouse, const std::wstring& label) {
    if (!GetConfig().ntPacks) return;
    skcdock::Message m;
    m.title = mouse ? L"Mouse pack" : L"Keyboard pack";
    m.glyph = skcdock::kGlyphPack;
    m.detail = label;
    skcdock::Show(m);
}

static void Cue(bool mouse) {
    if (GetConfig().toggleCue) PostThreadMessageW(g_audioTid, WM_SKC_PLAY, (mouse ? DEV_MOUSE : DEV_KEYBOARD) | FLAG_CUE, 0);
}

// The three switches are settings now, so the settings window, the tray menu and the shortcuts
// all show the same thing. While a save is on its way, LoadSettings keeps the values in memory.
static void SaveToggles() {
    SaveSettingsAsync({{L"soundsOn", g_onAll ? L"1" : L"0"},
                       {L"keyboardSounds", g_onKeyboard ? L"1" : L"0"},
                       {L"mouseSounds", g_onMouse ? L"1" : L"0"}},
                      false, &g_togglesSavePending);
}

static void Toggle(int which) {
    std::atomic<bool>& flag = which == HK_ALL ? g_onAll : which == HK_KEYBOARD ? g_onKeyboard : g_onMouse;
    flag = !flag;
    if (flag && !SoundsMuted()) Cue(which == HK_MOUSE);
    SaveToggles();
    UpdateTray(false);
    NotifyToggle(which);
}

static void ChangeVolume(int dir) {
    int step = GetConfig().volumeStep;
    int v = Clamp(g_volume + dir * step, 0, 100);
    g_volume = v;
    g_volumeSavePending = true;
    if (!SoundsMuted() && v > 0) PostThreadMessageW(g_audioTid, WM_SKC_PLAY, DEV_KEYBOARD | FLAG_CUE, 0);
    SetTimer(g_msgWnd, kVolumeTimer, 1500, nullptr);
    UpdateTray(false);
    NotifyVolume(v);
}

static void ApplyConfigEverywhere() {
    PostThreadMessageW(g_audioTid, WM_SKC_CONFIG, 0, 0);
    PostThreadMessageW(g_inputTid, WM_SKC_RULES, 0, 0);
    RegisterHotkeys();
    UpdateTray(false);
}

struct MenuPack {
    std::wstring name, label;
    bool builtin;
};

// Built-in packs for that device, then any other folder in the packs folder whose profile says so.
static std::vector<MenuPack> ListPacks(const Config& c, bool mouse) {
    std::vector<MenuPack> out;
    for (const auto& p : kBuiltinPacks)
        if (p.mouse == mouse) out.push_back({p.name, p.label, true});
    std::wstring root = PacksRoot(c);
    WIN32_FIND_DATAW fd;
    HANDLE h = FindFirstFileW((root + L"\\*").c_str(), &fd);
    if (h == INVALID_HANDLE_VALUE) return out;
    do {
        std::wstring n = fd.cFileName;
        if (!(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) || n.empty() || n[0] == L'.') continue;
        bool known = false;
        for (const auto& p : kBuiltinPacks)
            if (n == p.name) known = true;
        if (known) continue;
        std::string text;
        if (!ReadFileUtf8(root + L"\\" + n + L"\\profile.yaml", text)) continue;
        YNode y = YParse(text);
        const YNode* info = y.get("profile");
        bool isMouse = info && LowerA(info->str("device", "keyboard")) == "mouse";
        if (isMouse != mouse) continue;
        std::string label = info ? info->str("name") : std::string();
        out.push_back({n, label.empty() ? n : Widen(label) + (Widen(label) == n ? L"" : L" (" + n + L")"), false});
    } while (FindNextFileW(h, &fd));
    FindClose(h);
    return out;
}

enum : UINT {
    IDM_ALL = 100, IDM_KEYBOARD, IDM_MOUSE, IDM_FOLDER, IDM_SETTINGS, IDM_KB_NONE, IDM_MOUSE_NONE,
    IDM_KB_PACK = 1000, IDM_MOUSE_PACK = 2000,
};

static std::wstring MenuHint(int hk, const Config& c) {
    return hk >= 0 ? c.hotkeys[hk] : std::wstring();
}

static void ChoosePack(bool mouse, const MenuPack* pack) {
    std::vector<std::pair<std::wstring, std::wstring>> kv;
    {
        std::lock_guard<std::mutex> lock(g_cfgLock);
        std::wstring& choice = mouse ? g_cfg.mousePack : g_cfg.kbPack;
        std::wstring& custom = mouse ? g_cfg.mouseCustom : g_cfg.kbCustom;
        if (!pack) choice = L"none";
        else if (pack->builtin) choice = pack->name;
        else {
            choice = L"custom";
            custom = pack->name;
            kv.push_back({mouse ? L"mouseCustomPack" : L"keyboardCustomPack", custom});
        }
        kv.insert(kv.begin(), {mouse ? L"mousePack" : L"keyboardPack", choice});
    }
    // Hear it now; Windhawk then confirms the same values.
    PostThreadMessageW(g_audioTid, WM_SKC_CONFIG, 0, 0);
    SaveSettingsAsync(kv);
    NotifyPack(mouse, pack ? pack->label : std::wstring(mouse ? L"No mouse sounds" : L"No keyboard sounds"));
}

static void ShowTrayMenu(POINT pt) {
    Config c = GetConfig();
    using skcset::TrayRow;
    std::vector<MenuPack> kbPacks = ListPacks(c, false), mousePacks = ListPacks(c, true);
    std::vector<TrayRow> kbMenu, mouseMenu;
    for (size_t i = 0; i < kbPacks.size() && i < 900; i++) {
        bool on = kbPacks[i].builtin ? c.kbPack == kbPacks[i].name : (c.kbPack == L"custom" && c.kbCustom == kbPacks[i].name);
        kbMenu.push_back({(int)(IDM_KB_PACK + i), L"", kbPacks[i].label, L"", on});
    }
    kbMenu.push_back({0, L"", L"", L"", false, false, true});
    kbMenu.push_back({(int)IDM_KB_NONE, L"", L"No keyboard sounds", L"", c.kbPack == L"none"});
    for (size_t i = 0; i < mousePacks.size() && i < 900; i++) {
        bool on = mousePacks[i].builtin ? c.mousePack == mousePacks[i].name
                                        : (c.mousePack == L"custom" && c.mouseCustom == mousePacks[i].name);
        mouseMenu.push_back({(int)(IDM_MOUSE_PACK + i), L"", mousePacks[i].label, L"", on});
    }
    mouseMenu.push_back({0, L"", L"", L"", false, false, true});
    mouseMenu.push_back({(int)IDM_MOUSE_NONE, L"", L"No mouse sounds", L"", c.mousePack == L"none"});
    std::vector<TrayRow> rows;
    rows.push_back({(int)IDM_ALL, L"", L"Sounds on", MenuHint(HK_ALL, c), g_onAll});
    rows.push_back({(int)IDM_KEYBOARD, L"", L"Keyboard sounds", MenuHint(HK_KEYBOARD, c), g_onKeyboard});
    rows.push_back({(int)IDM_MOUSE, L"", L"Mouse sounds", MenuHint(HK_MOUSE, c), g_onMouse});
    rows.push_back({0, L"", L"", L"", false, false, true});
    rows.push_back({0, L"", L"Keyboard pack", L"", false, false, false, std::move(kbMenu)});
    rows.push_back({0, L"", L"Mouse pack", L"", false, false, false, std::move(mouseMenu)});
    rows.push_back({0, L"", L"", L"", false, false, true});
    rows.push_back({(int)IDM_FOLDER, L"", L"Open sound packs folder"});
    rows.push_back({(int)IDM_SETTINGS, L"", L"Settings"});
    UINT cmd = (UINT)skcset::ShowTrayMenu(g_msgWnd, &pt, rows);
    if (cmd == IDM_ALL) Toggle(HK_ALL);
    else if (cmd == IDM_KEYBOARD) Toggle(HK_KEYBOARD);
    else if (cmd == IDM_MOUSE) Toggle(HK_MOUSE);
    else if (cmd == IDM_SETTINGS) skcset::OpenSettingsWindow();
    else if (cmd == IDM_FOLDER) {
        std::wstring root = PacksRoot(c);
        SHCreateDirectoryExW(nullptr, root.c_str(), nullptr);
        ShellExecuteW(nullptr, L"open", root.c_str(), nullptr, nullptr, SW_SHOWNORMAL);
    } else if (cmd == IDM_KB_NONE) ChoosePack(false, nullptr);
    else if (cmd == IDM_MOUSE_NONE) ChoosePack(true, nullptr);
    else if (cmd >= IDM_KB_PACK && cmd < IDM_KB_PACK + kbPacks.size()) ChoosePack(false, &kbPacks[cmd - IDM_KB_PACK]);
    else if (cmd >= IDM_MOUSE_PACK && cmd < IDM_MOUSE_PACK + mousePacks.size())
        ChoosePack(true, &mousePacks[cmd - IDM_MOUSE_PACK]);
}

static LRESULT CALLBACK MsgWndProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) {
    if (msg == g_taskbarCreated && g_taskbarCreated) {
        g_trayAdded = false;
        UpdateTray(true);
        return 0;
    }
    switch (msg) {
        case WM_HOTKEY:
            if (wp == HK_ALL + 1) Toggle(HK_ALL);
            else if (wp == HK_KEYBOARD + 1) Toggle(HK_KEYBOARD);
            else if (wp == HK_MOUSE + 1) Toggle(HK_MOUSE);
            else if (wp == HK_VOLUP + 1) ChangeVolume(1);
            else if (wp == HK_VOLDOWN + 1) ChangeVolume(-1);
            return 0;
        case WM_TIMER:
            if (wp == kVolumeTimer) {
                KillTimer(hwnd, kVolumeTimer);
                SaveSettingsAsync({{L"volume", std::to_wstring(g_volume.load())}}, true);
            }
            return 0;
        case WM_SKC_TRAY:
            switch (LOWORD(lp)) {
                case NIN_SELECT:
                case NIN_KEYSELECT: skcset::OpenSettingsWindow(); break;
                case WM_CONTEXTMENU: ShowTrayMenu(POINT{GET_X_LPARAM(wp), GET_Y_LPARAM(wp)}); break;
            }
            return 0;
        case WM_SKC_SETTINGS: {
            const Config before = GetConfig();
            LoadSettings();
            ApplyConfigEverywhere();
            const Config after = GetConfig();
            // Moved, resized or restyled the dock: show it once where it now sits.
            if (after.ntOn && !before.SameNotifier(after)) {
                skcdock::Message m;
                m.glyph = skcdock::kGlyphLook;
                m.title = L"Notifier dock";
                m.detail = L"This is where it shows up";
                skcdock::Show(m);
            } else if (!after.ntOn) {
                skcdock::Hide();
            }
            if (HWND s = skcset::g_settingsWnd) PostMessageW(s, WM_APP + 1 /* WM_APP_SETTINGS_RELOAD */, 0, 0);
            return 0;
        }
        case WM_SKC_REFRESH: UpdateTray(false); return 0;
    }
    return DefWindowProcW(hwnd, msg, wp, lp);
}

static DWORD WINAPI UiThread(LPVOID) {
    MSG msg;
    // A single-threaded apartment: the dock's glass (Windows.UI.Composition) lives on this thread.
    const HRESULT co = CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED);
    PeekMessageW(&msg, nullptr, WM_USER, WM_USER, PM_NOREMOVE);
    EnableDarkMenus();
    WNDCLASSW wc{};
    wc.lpfnWndProc = MsgWndProc;
    wc.hInstance = (HINSTANCE)windhawk_tool_mod::GetCurrentModuleHandle();
    wc.lpszClassName = L"SeamlessKeyClickMsg";
    RegisterClassW(&wc);
    g_msgWnd = CreateWindowExW(WS_EX_TOOLWINDOW, wc.lpszClassName, L"Seamless Key Click", WS_POPUP, 0, 0, 0, 0,
                               nullptr, nullptr, wc.hInstance, nullptr);
    if (g_msgWnd) {
        g_taskbarCreated = RegisterWindowMessageW(L"TaskbarCreated");
        ChangeWindowMessageFilterEx(g_msgWnd, g_taskbarCreated, MSGFLT_ALLOW, nullptr);
        RegisterHotkeys();
        UpdateTray(true);
        if (g_migrateToggles) {
            g_migrateToggles = false;
            SaveToggles();
        }
    }
    SetEvent(g_uiReady);
    if (!g_msgWnd) {
        if (SUCCEEDED(co)) CoUninitialize();
        return 1;
    }
    while (GetMessageW(&msg, nullptr, 0, 0) > 0) {
        TranslateMessage(&msg);
        DispatchMessageW(&msg);
    }
    KillTimer(g_msgWnd, kVolumeTimer);
    for (int i = 0; i < HK_COUNT; i++)
        if (g_hotkeyOn[i]) UnregisterHotKey(g_msgWnd, i + 1);
    if (g_trayAdded) {
        NOTIFYICONDATAW nid{sizeof(nid)};
        nid.hWnd = g_msgWnd;
        nid.uID = kTrayId;
        Shell_NotifyIconW(NIM_DELETE, &nid);
        g_trayAdded = false;
    }
    if (g_trayIcon) DestroyIcon(g_trayIcon);
    g_trayIcon = nullptr;
    skcdock::Destroy();
    DestroyWindow(g_msgWnd);
    g_msgWnd = nullptr;
    UnregisterClassW(wc.lpszClassName, wc.hInstance);
    if (SUCCEEDED(co)) CoUninitialize();
    return 0;
}

// ---------------------------------------------------------------------------
// Start and stop
// ---------------------------------------------------------------------------

static HANDLE StartThread(LPTHREAD_START_ROUTINE fn, HANDLE& ready, DWORD& tid) {
    ready = CreateEventW(nullptr, TRUE, FALSE, nullptr);
    HANDLE t = CreateThread(nullptr, 0, fn, nullptr, 0, &tid);
    if (t) WaitForSingleObject(ready, 10000);
    CloseHandle(ready);
    ready = nullptr;
    return t;
}

static void StopThread(HANDLE& t, DWORD tid, PCWSTR name) {
    if (!t) return;
    PostThreadMessageW(tid, WM_QUIT, 0, 0);
    if (WaitForSingleObject(t, 15000) != WAIT_OBJECT_0) Wh_Log(L"%s thread did not stop in 15 s", name);
    CloseHandle(t);
    t = nullptr;
}

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
// Title bar menus are opened by DefWindowProc, never through TrackPopupMenu: wrap the
// messages that open one the same way, so the menu is skinned before its first paint.
static decltype(&DefWindowProcW) SysMenuDefProc_orig = nullptr;
static LRESULT WINAPI SysMenuDefProc_hook(HWND h, UINT msg, WPARAM w, LPARAM l)
{
    UINT sc = (UINT)(w & 0xFFF0);
    bool opens = (msg == WM_SYSCOMMAND && (sc == SC_KEYMENU || sc == SC_MOUSEMENU)) ||
                 msg == WM_CONTEXTMENU || msg == 0x0313 /* WM_POPUPSYSTEMMENU */;
    if (!opens) return SysMenuDefProc_orig(h, msg, w, l);
    SeamlessMenuRoom::BeginTrack();
    HHOOK cbt = InstallMenuCbtHook();
    LRESULT ret = SysMenuDefProc_orig(h, msg, w, l);
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
    Hook(u32, "DefWindowProcW", SysMenuDefProc_hook, &SysMenuDefProc_orig);
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
    g_singleInstance = CreateMutexW(nullptr, FALSE, L"Local\\SeamlessKeyClickRunning");
    if (!g_singleInstance || GetLastError() == ERROR_ALREADY_EXISTS) {
        if (g_singleInstance) CloseHandle(g_singleInstance);
        g_singleInstance = nullptr;
        Wh_Log(L"Already running");
        return FALSE;
    }
    // Same menu look as Launchpad's (Seamless Flyouts can't reach this process). Hooks are
    // applied when init returns, so this has to run here.
    SeamlessMenuSkin::Init();
    g_stop = false;
    LoadSettings();
    // Up to 1.0.5 the switches lived outside the settings. Carry them over once; the UI thread saves them.
    if (Wh_GetIntValue(L"togglesInSettings", 0) == 0) {
        bool all = Wh_GetIntValue(L"onAll", 1) != 0, kb = Wh_GetIntValue(L"onKeyboard", 1) != 0,
             mouse = Wh_GetIntValue(L"onMouse", 1) != 0;
        if (!all || !kb || !mouse) {
            g_onAll = all;
            g_onKeyboard = kb;
            g_onMouse = mouse;
            g_migrateToggles = true;
        }
        Wh_SetIntValue(L"togglesInSettings", 1);
    }
    g_audioThread = StartThread(AudioThread, g_audioReady, g_audioTid);
    g_inputThread = StartThread(InputThread, g_inputReady, g_inputTid);
    g_uiThread = StartThread(UiThread, g_uiReady, g_uiTid);
    if (!g_audioThread || !g_inputThread || !g_uiThread) {
        Wh_Log(L"Couldn't start");
        WhTool_ModUninit();
        return FALSE;
    }
    return TRUE;
}

void WhTool_ModSettingsChanged() {
    if (g_msgWnd) PostMessageW(g_msgWnd, WM_SKC_SETTINGS, 0, 0);
}

void WhTool_ModUninit() {
    g_stop = true;
    skcset::CloseSettingsWindow();
    StopThread(g_inputThread, g_inputTid, L"Input");
    StopThread(g_uiThread, g_uiTid, L"UI");
    StopThread(g_audioThread, g_audioTid, L"Audio");
    {
        std::lock_guard<std::mutex> lock(g_dlLock);
        for (HANDLE t : g_dlThreads) {
            if (WaitForSingleObject(t, 15000) != WAIT_OBJECT_0) Wh_Log(L"A pack download did not stop in 15 s");
            CloseHandle(t);
        }
        g_dlThreads.clear();
    }
    for (int i = 0; i < 150 && g_saveThreads > 0; i++) Sleep(100);
    SeamlessMenuSkin::Uninit();
    if (g_singleInstance) CloseHandle(g_singleInstance);
    g_singleInstance = nullptr;
}

// ===========================================================================
// Settings window: the Seamless Launchpad settings GUI, the standard for every
// DavidHiFi mod. Generated by work\2026-11-11-seamless-key-click\gen.py.
// ===========================================================================
extern "C" IMAGE_DOS_HEADER __ImageBase;
namespace skcset {
// The settings window, from the tray icon. It shows the same settings as
// Windhawk's page for this mod and saves them through windhawk-cli, so the two
// stay in step. Writing a mod's settings takes admin rights, so the save runs
// the CLI elevated (silently where UAC prompts are off).

constexpr WCHAR kSettingsClass[] = L"WindhawkSeamlessKeyClickSettings";
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
// Generated by work\2026-11-11-seamless-key-click\gen.py from spec.py.
static std::vector<SetField> Set_MakeFields() {
    using K = SetField;
    return {
{K::Check, L"soundsOn", L"Sounds on", L"Turns every sound on or off. The shortcut and the tray menu switch this too.", L"1", {}, 0, 100, 0, L"On or off"},
{K::Check, L"keyboardSounds", L"Keyboard sounds", L"A sound for each key you press.", L"1", {}, 0, 100, 0, L"On or off"},
{K::Check, L"mouseSounds", L"Mouse sounds", L"A sound for each click. Pick a mouse pack below too.", L"1", {}, 0, 100, 0, L"On or off"},
{K::Choice, L"keyboardPack", L"Keyboard sound pack", L"The keyboard each key press sounds like. Every pack from Keyboard Sounds is here.", L"alpaca", {{L"alpaca", L"Alpaca (kbsim)"}, {L"apex-pro-tkl-v2", L"SteelSeries Apex Pro TKL (Akira)"}, {L"banana-split", L"Banana Split switches (Akira)"}, {L"gateron-black-ink", L"Gateron Black Ink (kbsim)"}, {L"gateron-red-ink", L"Gateron Red Ink (kbsim)"}, {L"holy-panda", L"Holy Panda (kbsim)"}, {L"ios", L"iPhone keyboard"}, {L"logitech-g915-tkl-brown", L"Logitech G915 TKL, brown switches"}, {L"mx-black", L"Cherry MX Black (kbsim)"}, {L"mx-blue", L"Cherry MX Blue (kbsim)"}, {L"mx-brown", L"Cherry MX Brown (kbsim)"}, {L"mx-speed-silver", L"Cherry MX Speed Silver (Mechvibes)"}, {L"nk-cream", L"NovelKeys Cream (Mechvibes)"}, {L"opera-gx", L"Opera GX browser (Mechvibes)"}, {L"telios-v2", L"Telios V2 linear (Mechvibes)"}, {L"typewriter", L"Antique typewriter (Mechvibes)"}, {L"classic", L"Classic tick (the original Key Click)"}, {L"custom", L"My own pack (named below)"}, {L"none", L"No keyboard sounds"}}, 0, 100, 0, L"Sound packs"},
{K::Text, L"keyboardCustomPack", L"Your own keyboard pack", L"Used when the pack above is \"My own pack\". The name of a folder in the sound packs folder, or the full path of any Keyboard Sounds profile folder (one with a profile.yaml in it).", L"", {}, 0, 100, 0, L"Sound packs"},
{K::Choice, L"mousePack", L"Mouse sound pack", L"The mouse each click sounds like.", L"none", {{L"g502x-wireless", L"Logitech G502 X Wireless"}, {L"custom", L"My own pack (named below)"}, {L"none", L"No mouse sounds"}}, 0, 100, 0, L"Sound packs"},
{K::Text, L"mouseCustomPack", L"Your own mouse pack", L"Used when the mouse pack is \"My own pack\". A folder name or a full path, as above.", L"", {}, 0, 100, 0, L"Sound packs"},
{K::Text, L"packsFolder", L"Sound packs folder", L"Where the packs are kept. Leave it empty to use the mod's own folder. Open it from the tray icon's menu.", L"", {}, 0, 100, 0, L"Sound packs"},
{K::Check, L"downloadPacks", L"Download missing packs", L"When a pack you pick is not in the folder, fetch it from the Keyboard Sounds project on GitHub.", L"1", {}, 0, 100, 0, L"Sound packs"},
{K::Number, L"volume", L"Volume", L"0 to 100 (Suggested: 70). The volume shortcuts change this too.", L"70", {}, 0, 100, 0, L"Volume and pitch"},
{K::Number, L"mouseVolume", L"Mouse volume (% of the volume)", L"0 to 100 (Suggested: 100). Mouse clicks play at this share of the volume above.", L"100", {}, 0, 100, 0, L"Volume and pitch"},
{K::Check, L"pitchShift", L"Random pitch", L"Each sound plays a little higher or lower, so fast typing sounds less repetitive.", L"0", {}, 0, 100, 0, L"Volume and pitch"},
{K::Number, L"pitchLow", L"Lowest pitch (semitones)", L"-12 to 12 (Suggested: -2).", L"-2", {}, -12, 12, 0, L"Volume and pitch"},
{K::Number, L"pitchHigh", L"Highest pitch (semitones)", L"-12 to 12 (Suggested: 2).", L"2", {}, -12, 12, 0, L"Volume and pitch"},
{K::Choice, L"pitchApplies", L"Random pitch for", L"Which sounds get the random pitch.", L"both", {{L"both", L"Keyboard and mouse"}, {L"keyboard", L"Keyboard only"}, {L"mouse", L"Mouse only"}}, 0, 100, 0, L"Volume and pitch"},
{K::Check, L"releaseSounds", L"Release sounds", L"Play the sound of a key or button coming back up, for packs that have one.", L"1", {}, 0, 100, 1, L"Keys and buttons"},
{K::Check, L"repeatHeldKeys", L"Click while a key is held", L"Off, a held key sounds once. On, it clicks again with every repeat, like the original Key Click. Shift, Ctrl, Alt and Windows never repeat.", L"0", {}, 0, 100, 1, L"Keys and buttons"},
{K::Check, L"ignoreInjected", L"Skip typing from other programs", L"No sound for keys and clicks sent by macro tools, on-screen keyboards and remote desktop apps.", L"1", {}, 0, 100, 1, L"Keys and buttons"},
{K::Check, L"sideButtons", L"Side mouse buttons", L"Also click for the back and forward buttons, with the pack's main click.", L"0", {}, 0, 100, 1, L"Keys and buttons"},
{K::Number, L"maxOverlap", L"Sounds at once", L"1 to 64 (Suggested: 32). How many sounds can overlap. The oldest stops when a new one needs room.", L"32", {}, 1, 64, 1, L"Keys and buttons"},
{K::Choice, L"appMode", L"Apps", L"Where sounds play when an app is in none of the lists below.", L"enable", {{L"enable", L"Play in every app"}, {L"disable", L"Play only in the \"Play in\" apps"}}, 0, 100, 1, L"Apps"},
{K::Text, L"playApps", L"Play in", L"Apps that always make sounds. Program names or full paths, split with \";\", such as notepad.exe; code.exe. * and ? work as wildcards.", L"", {}, 0, 100, 1, L"Apps"},
{K::Text, L"silentApps", L"Silent in", L"Apps that never make sounds, such as a game or a video call app.", L"", {}, 0, 100, 1, L"Apps"},
{K::Text, L"onlyApps", L"Only in", L"When set, sounds play only while one of these apps is in front, and the lists above are ignored.", L"", {}, 0, 100, 1, L"Apps"},
{K::Hotkey, L"toggleHotkey", L"Turn all sounds on or off", L"Press the keys in the box. Backspace clears it.", L"Ctrl+Alt+K", {}, 0, 100, 2, L"Shortcuts"},
{K::Hotkey, L"keyboardHotkey", L"Turn keyboard sounds on or off", L"", L"", {}, 0, 100, 2, L"Shortcuts"},
{K::Hotkey, L"mouseHotkey", L"Turn mouse sounds on or off", L"", L"", {}, 0, 100, 2, L"Shortcuts"},
{K::Hotkey, L"volumeUpHotkey", L"Volume up", L"", L"", {}, 0, 100, 2, L"Shortcuts"},
{K::Hotkey, L"volumeDownHotkey", L"Volume down", L"", L"", {}, 0, 100, 2, L"Shortcuts"},
{K::Number, L"volumeStep", L"Volume step", L"1 to 50 (Suggested: 10). How much each volume shortcut changes the volume.", L"10", {}, 1, 50, 2, L"Shortcuts"},
{K::Check, L"toggleCue", L"Click when sounds come back on", L"A shortcut or the tray menu plays one click when it turns sounds on, so you hear that it worked.", L"1", {}, 0, 100, 2, L"Shortcuts"},
{K::Check, L"notifierOn", L"Notifier dock", L"A small dock pops up when a shortcut or the tray menu turns sounds on or off, changes the volume or picks a pack.", L"1", {}, 0, 100, 3, L"Notifier dock"},
{K::Check, L"notifierSounds", L"Show it for sounds on or off", L"", L"1", {}, 0, 100, 3, L"Notifier dock"},
{K::Check, L"notifierVolume", L"Show it for volume changes", L"With a level bar for the new volume.", L"1", {}, 0, 100, 3, L"Notifier dock"},
{K::Check, L"notifierPacks", L"Show it for pack changes", L"", L"1", {}, 0, 100, 3, L"Notifier dock"},
{K::Check, L"notifierFullscreen", L"Show over full-screen apps", L"Off, the dock stays hidden while a game or a presentation fills the screen.", L"0", {}, 0, 100, 3, L"Notifier dock"},
{K::Choice, L"notifierPosition", L"Where it shows", L"The corner or edge of the screen. The taskbar is never covered.", L"bottomCenter", {{L"topLeft", L"Top left"}, {L"topCenter", L"Top middle"}, {L"topRight", L"Top right"}, {L"center", L"Middle of the screen"}, {L"bottomLeft", L"Bottom left"}, {L"bottomCenter", L"Bottom middle"}, {L"bottomRight", L"Bottom right"}}, 0, 100, 3, L"Where it shows"},
{K::Choice, L"notifierDisplay", L"Which screen", L"With more than one monitor, the one the dock shows on.", L"focused", {{L"focused", L"The screen with the window in front"}, {L"cursor", L"The screen with the pointer"}, {L"primary", L"The main screen"}}, 0, 100, 3, L"Where it shows"},
{K::Number, L"notifierMargin", L"Distance from the edge", L"0 to 400 (Suggested: 48). Pixels between the dock and the screen edge.", L"48", {}, 0, 400, 3, L"Where it shows"},
{K::Number, L"notifierDuration", L"How long it stays (ms)", L"500 to 10000 (Suggested: 1800). Moving the pointer onto it hides it at once.", L"1800", {}, 500, 10000, 3, L"Where it shows"},
{K::Choice, L"notifierSize", L"Size", L"How big the dock and its text are.", L"normal", {{L"compact", L"Compact"}, {L"normal", L"Normal"}, {L"large", L"Large"}}, 0, 100, 3, L"How it looks"},
{K::Choice, L"notifierLook", L"Look", L"Glass is blurred and see-through with a Mocha tint, like the settings window. Solid is plain Mocha.", L"glass", {{L"glass", L"Glass"}, {L"solid", L"Solid"}}, 0, 100, 3, L"How it looks"},
{K::Number, L"notifierTint", L"Glass tint (%)", L"30 to 100 (Suggested: 62). How much Mocha colour lies over the blur. Higher is darker and easier to read.", L"62", {}, 30, 100, 3, L"How it looks"},
{K::Check, L"settingsGlass", L"Blurred settings window", L"On, the settings window is see-through glass with Windows acrylic behind it. Off, it is solid. Applies when you save.", L"1", {}, 0, 100, 3, L"Settings window"},
{K::Check, L"nativeSettingsTitleBar", L"Native Windows title bar", L"Use the Windows title bar and window buttons for this settings window. Applies when you save.", L"0", {}, 0, 100, 3, L"Settings window"},
{K::Check, L"settingsTrayIcon", L"Tray icon", L"Click it to open these settings. Right-click it to turn sounds on or off or pick a pack. When off, change settings in Windhawk.", L"1", {}, 0, 100, 3, L"Settings window"}
    };
}

struct SetPageInfo {
    PCWSTR name, intro;
    WCHAR glyph;
};
static const SetPageInfo kSetPages[] = {
{L"Sounds", L"Keyboard and mouse sounds on or off, sound packs, volume and pitch.", 0xE767},
{L"When to play", L"Which keys and clicks make a sound, and in which apps.", 0xE71D},
{L"Shortcuts", L"Keys that turn sounds on and off and change the volume.", 0xE765},
{L"Look", L"The notifier dock and this settings window.", 0xE790},
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
constexpr PCWSTR kSetDittoUrl = L"https://windhawk.net/mods/key-click";
constexpr PCWSTR kSetKsUrl = L"https://github.com/nathan-fiscaletti/keyboardsounds";
constexpr PCWSTR kSetRepoUrl = L"https://github.com/DavidHiFi/davids-windhawk-mods";
constexpr PCWSTR kSetBugUrl =
    L"https://github.com/DavidHiFi/davids-windhawk-mods/issues/new?title=%5BSeamless%20Key%20Click%5D%20";
constexpr PCWSTR kSetTitle = L"Seamless Key Click";
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
        if (w.fRailName && Set_TextW(w.fRailName.get(), L"Key Click") <= railW) break;
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
        add(SetItem::Link, 56, L"Based on Key Click by Anixx", L"The original Windhawk mod", kSetDittoUrl);
        add(SetItem::Link, 56, L"Sound packs from Keyboard Sounds", L"By Nathan Fiscaletti, GPL-3.0", kSetKsUrl);
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
        const WCHAR glyph = 0xE765;
        auto br = p.G({mc.x - 19, mc.y - 19, mc.x + 19, mc.y + 19});
        if (br) p.rt->DrawText(&glyph, 1, w.fIconL.get(), mark, br.get());
        p.rt->SetTransform(old);
    }
    float x = mark.right + 20;
    p.Text(w.fBig.get(), L"Seamless Key Click", {x, row.top + 18, row.right - 16, row.top + 46}, mocha::text);
#ifdef WH_MOD_VERSION
    std::wstring ver = std::wstring(L"Version ") + WH_MOD_VERSION + L"  \u00B7  MIT license  \u00B7  A Windhawk mod";
#else
    std::wstring ver = L"MIT license  \u00B7  A Windhawk mod";
#endif
    p.Text(w.fHint.get(), ver, {x, row.top + 48, row.right - 16, row.top + 68}, mocha::subtext0);
    p.Text(w.fHint.get(), L"Mechanical keyboard and mouse sounds as you type and click, with 17 sound packs.",
           {x, row.top + 72, row.right - 16, row.top + 110}, mocha::subtext1);
    p.Text(w.fHint.get(), L"Made by DavidHiFi, based on Key Click by Anixx and Keyboard Sounds.",
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
    p.Text(w.fRailName.get(), L"Key Click", {d.left + 90, d.top + 32, d.left + w.railW - 10, d.top + 56}, mocha::text, textA);
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
    const WCHAR mark = 0xE765;
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
    HWND hwnd = CreateWindowExW(0, kSettingsClass, L"Seamless Key Click settings", style,
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
static std::vector<SetMenuItem> TrayItems(const std::vector<TrayRow>& rows) {
    std::vector<SetMenuItem> out;
    for (const TrayRow& r : rows) {
        if (r.separator) out.push_back(Set_MenuSep());
        else if (!r.sub.empty()) out.push_back(Set_MenuSub(r.glyph.c_str(), r.label.c_str(), TrayItems(r.sub), r.disabled));
        else out.push_back(Set_MenuRow(r.id, r.glyph.c_str(), r.label.c_str(), r.checked, r.disabled, r.hint.c_str()));
    }
    return out;
}
int ShowTrayMenu(HWND owner, const POINT* at, const std::vector<TrayRow>& rows) {
    return Set_TrayMenu(owner, TrayItems(rows), at);
}
}  // namespace skcset
