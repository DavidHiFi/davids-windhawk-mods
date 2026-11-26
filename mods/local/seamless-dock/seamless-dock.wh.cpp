// ==WindhawkMod==
// @id              seamless-dock
// @name            Seamless Dock
// @description     A floating dock on any edge of the screen for your pinned and open apps
// @version         0.3.18
// @author          DavidHiFi
// @github          https://github.com/DavidHiFi
// @homepage        https://github.com/DavidHiFi/davids-windhawk-mods
// @donateUrl       https://ko-fi.com/DavidHiFi
// @license         GPL-3.0
// @include         windhawk.exe
// @compilerOptions -lole32 -loleaut32 -luuid -ld2d1 -ldwrite -ldwmapi -luser32 -lgdi32 -lshell32 -lshlwapi -lshcore -lversion -ladvapi32 -lwindowscodecs
// ==/WindhawkMod==

// Source code is published under The GNU General Public License v3.0.
//
// For bug reports and feature requests, please open an issue here:
// https://github.com/DavidHiFi/davids-windhawk-mods/issues

// ==WindhawkModReadme==
/*
# Seamless Dock

A floating dock with your pinned apps and the apps you have open. It sits on
the edge of the screen across from your taskbar, so you get a clean bar on one
side and a dock on the other, like a Linux desktop.

![Seamless Dock preview](https://raw.githubusercontent.com/DavidHiFi/davids-windhawk-mods/main/media/previews/seamless-dock.png)

## What's new in 0.3.17

- The title pill in the middle of the top bar comes back after it goes missing, and it
  has a dark fill with a soft grey edge like the other docks.

## What's new in 0.3.16

- The dock's glass no longer goes see-through after the PC has been on for hours. The blur
  is set fresh whenever the dock, its preview or its menu shows, and every two minutes.
- App tiles have a firmer dark fill, so nothing behind them shows through.

## What's new in 0.3.13

- Windows from your Windhawk mods each get their own icon on the dock, with the
  mod's own name and icon. Before, every mod's window shared one plain
  Windhawk icon called "Windhawk mod".
- The Windows Settings window shows the Catppuccin settings icon, the same one
  its title bar has, when Mocha App Icons is on.

## What's new in 0.3.12

- The title pill no longer creeps back over the taskbar's right-click menu
  while the menu stays open. It tucks under the menu and stays there.

## What's new in 0.3.11

- Right-click the Recycle Bin on the dock and Empty Recycle Bin is always
  there. It used to hide whenever the dock had not noticed the bin fill up.

## What's new in 0.3.10

- The taskbar's own right-click menu, and every submenu you hover open from
  it, now always sits on top of the title pill. The pill used to miss menus
  drawn by other mods on the taskbar.

## What's new in 0.3.9

- The taskbar's right-click menu opens on top of the title pill again. The
  pill steps under any menu or pop-up that covers it.

## What's new in 0.3.8

- The title pill now belongs to the taskbar, so Windows lifts the two together
  when you click the bar. The pill no longer dips under it for a frame.

## What's new in 0.3.7

- The title pill stays on top when you click or right-click the taskbar, even
  on the first click. A small helper of its own keeps it there, so a busy dock
  can no longer let it slip under the bar for a frame.

## What's new in 0.3.6

- The title pill blinks far less when you click or right-click the taskbar.

## What's new in 0.3.5

- The title pill on the top bar lights up with the blue to mauve edge when you
  point at it, the same as the other pills on the bar.

## What's new in 0.3.4

- Windows no longer dip under the dock when another app sends the "taskbar
  restarted" signal while Explorer is still the same. The dock only gives up and
  takes back its space when Explorer really restarted.

## What's new in 0.3.3

- An app that stops responding keeps one icon. Before, the stand-in window
  Windows shows for a frozen app turned up as an extra blank icon.
- Windows from Windhawk mods (a mod's settings or Startup Control) get their
  own icon instead of lighting up the Windhawk pin.
- An app whose program has no icon of its own shows its window's icon, not a
  blank page.
- The thin lines in the dock sit exactly in the middle between two icons.
- Add your own separators. Right-click a pinned app and pick "Add separator
  after". Right-click a separator to remove it. The lines before your open apps
  and before the Recycle Bin can be removed the same way, or switched in Dock
  options.

## What's new in 0.3.2

- Steadier. The dock no longer waits on a stuck Explorer, checks the Recycle
  Bin in the background, and stops retrying the reserved space every few
  seconds when another tool keeps taking it.
- Dragging an icon and dropping it back in its own place no longer opens or
  hides the app.
- A maximized window no longer counts as full screen, so the dock stays put.
- App names are looked up once instead of every time a window opens.
- An icon that failed to load (an app still starting, a drive not ready yet)
  is tried again a little later.
- Clicking the dock closes its menu.
- New settings: preview size, how far an icon lifts when you point at it, and
  the widest the top bar title may grow. Settings are grouped the way you
  would look for them.

## What's new in 0.3.1

- A pinned app shows once. Steam, Windhawk and other apps whose windows come
  from a helper program inside their own folder now light up their pinned icon
  instead of adding a second one.
- If Windows drops the space kept for the dock, the dock takes it back within
  a few seconds, so tiled and maximized windows always stop above it.
- Right-click an app for "Open file location".

## What's new in 0.3.0

- The dock can sit on any edge: bottom, top, left or right, always in the
  middle of that edge.
- By default it sits across from your taskbar, and moves when you move the
  taskbar.
- Pick a side from the dock's right-click menu or from the taskbar's. The side
  you pick stays until you pick "Across from the taskbar" again.
- When the dock and the taskbar share an edge, the dock sits just inside the
  taskbar and never covers it.
- The Recycle Bin can sit at the end of the dock. Its icon shows when it holds
  files. Click to open it, right-click to empty it.
- Right-click an empty part of the dock for its own options.

## What's new in 0.2.1

- After Explorer restarts, the dock takes its space back, so windows stop
  above it again.
- The title pill keeps showing while a tray menu or the hidden icons panel is
  open. It names the window underneath.

## What's new in 0.2.0

- The middle of a top taskbar now shows the app and title of the window you
  are using, in a pill that matches the other pills on the bar. Turn it off
  with "Window title on the top bar".
- The dock now redraws only when something it shows changes, so it stays
  quiet while you work.

## What's new in 0.1.0

- First release: pinned apps, open apps after a thin line, live window
  previews, its own right-click menu, and windows that stop above the dock.
- Works with Seamless Window Manager: tiled windows keep the same gap above
  the dock as they do on the other three sides of the screen.

## Features

- **Pinned apps first.** The dock starts with the apps pinned to your taskbar,
  in the same order. Drag an icon to move it. Pin or unpin from the right-click
  menu.
- **Separators.** Group your pinned apps with thin lines. Add one from an app's
  right-click menu, remove one by right-clicking it.
- **Open apps too.** Apps you have open but did not pin sit after a thin line.
  A dot under an icon means the app is open, and a wider dot marks the one you
  are using.
- **Click like a dock.** Click to open or switch to an app, click again to hide
  it, click an app with several windows to go through them. Middle-click opens
  a new window.
- **Live previews.** Rest the pointer on an open app to see its windows. Click
  one to go to it, or close it from there.
- **Any edge.** Bottom, top, left or right. By default it sits across from your
  taskbar and follows it.
- **Recycle Bin.** At the end of the dock, full or empty at a glance.
- **Windows stop short of it.** Maximized windows end at the dock, so it never
  covers anything. Turn this off to let the dock float over windows instead.
- **Out of the way for games.** The dock hides while a game or video fills the
  screen.
- **Window title on the top bar.** With your taskbar at the top of the screen,
  its middle shows the app and title of the window you are using.
- **Change it on the go.** Right-click the dock, or empty space on Seamless
  Taskbar, to move the dock or switch the Recycle Bin and the title on or off.
- **Frosted glass.** Catppuccin Mocha glass with a grey edge that turns blue to
  mauve when you point at it. Every color and size is in the settings.

## Setup

- Windows 11 and Windhawk 2.0 or newer.
- The dock shows on your main screen.

## Notes

- The dock runs in its own small Windhawk process, so a stuck app can't take it
  down, and it never loads into Explorer.
- The corners follow Custom Window Corner Radius when that mod is on.
- An app that a game launcher or updater starts may show up as its own icon
  until it is pinned.
*/
// ==/WindhawkModReadme==

// ==WindhawkModSettings==
/*
- position: auto
  $name: Dock position
  $description: 'Which edge of the screen the dock sits on, in the middle of it. Across from the taskbar moves the dock when you move the taskbar. The right-click menu on the dock or the taskbar changes this too (Suggested: Across from the taskbar).'
  $options:
  - auto: Across from the taskbar
  - bottom: Bottom
  - top: Top
  - left: Left
  - right: Right
- bottomGap: 8
  $name: Gap from the screen edge
  $description: 'Space between the dock and its edge of the screen, or the taskbar when they share an edge. 0 to 48 (Suggested: 8).'
- iconSize: 36
  $name: Icon size
  $description: 'Size of each app icon in pixels at 100% scaling. 24 to 64 (Suggested: 36).'
- spacing: 6
  $name: Space between icons
  $description: '0 to 24 (Suggested: 6).'
- iconLift: 3
  $name: Lift on hover
  $description: 'How far an icon rises while you point at it, in pixels. 0 to 10 (Suggested: 3).'
- showOpenApps: true
  $name: Show open apps
  $description: When on, apps you have open but did not pin show after a thin line. When off, the dock shows pinned apps only.
- recycleBin: true
  $name: Recycle Bin in the dock
  $description: Shows the Recycle Bin at the end of the dock. Click it to open it, right-click it to empty it.
- previews: true
  $name: Window previews
  $description: When on, resting the pointer on an open app shows live pictures of its windows.
- previewSize: 208
  $name: Preview size
  $description: 'Width of each window picture in the preview, in pixels at 100% scaling. 140 to 360 (Suggested: 208).'
- hoverDelay: 350
  $name: Preview delay
  $description: 'How long the pointer rests on an icon before the preview opens, in milliseconds. 0 to 2000 (Suggested: 350).'
- surfaceOpacity: 60
  $name: Glass tint
  $description: 'How much Mocha color sits over the blur, in percent. 30 to 100 (Suggested: 60).'
- edgeColor: "#585b70"
  $name: Edge color
  $description: 'Color of the dock edge while the pointer is away, as a hex color (Suggested: #585b70).'
- hoverColorFrom: "#89b4fa"
  $name: Hover edge start color
  $description: 'The edge fades from this color to the end color while you point at the dock (Suggested: #89b4fa).'
- hoverColorTo: "#cba6f7"
  $name: Hover edge end color
  $description: 'End color of the hover edge, as a hex color (Suggested: #cba6f7).'
- edgeWidth: 2
  $name: Edge width
  $description: 'Edge thickness in pixels at 100% scaling. 0 to 6 (Suggested: 2).'
- fadeMs: 150
  $name: Fade time
  $description: 'How long hover colors take to fade, in milliseconds. 0 to 1000 (Suggested: 150).'
- font: FiraCode Nerd Font
  $name: Font
  $description: 'Font for app names in previews and menus (Suggested: FiraCode Nerd Font).'
- showTitle: true
  $name: Window title on the top bar
  $description: When your taskbar sits at the top of the screen, its middle shows the app and title of the window you are using.
- titleMaxWidth: 720
  $name: Title width
  $description: 'The widest the top bar title may grow before long titles are cut short, in pixels at 100% scaling. 200 to 1400 (Suggested: 720).'
- reserveSpace: true
  $name: Keep windows clear of the dock
  $description: When on, maximized windows stop at the dock. When off, the dock floats over them.
- hideOnFullscreen: true
  $name: Hide for full screen apps
  $description: When on, the dock hides while a game or video fills the screen.
*/
// ==/WindhawkModSettings==

#include <windows.h>
#include <windowsx.h>
#include <dwmapi.h>
#include <d2d1.h>
#include <d2d1helper.h>
#include <dwrite.h>
#include <shellapi.h>
#include <shellscalingapi.h>
#include <shlobj.h>
#include <shobjidl.h>
#include <shlwapi.h>
#include <propsys.h>
#include <wincodec.h>
#include <wrl/client.h>

#include <algorithm>
#include <cmath>
#include <functional>
#include <map>
#include <set>
#include <string>
#include <unordered_map>
#include <vector>

using Microsoft::WRL::ComPtr;

namespace dock {

// ---------------------------------------------------------------------------
// Settings
// ---------------------------------------------------------------------------
struct Settings {
    int iconSize = 36, spacing = 6, bottomGap = 8, hoverDelay = 350, opacity = 60, edgeWidth = 2, fadeMs = 150;
    int iconLift = 3, previewW = 208, titleMaxW = 720;
    bool reserve = true, showOpen = true, previews = true, hideFull = true, showTitle = true, recycle = true;
    bool lineOpen = true, lineBin = true;  // the lines before the open apps and the Recycle Bin
    int place = 0;  // Place: 0 across from the taskbar, 1 bottom, 2 top, 3 left, 4 right
    UINT edge = 0x585B70, from = 0x89B4FA, to = 0xCBA6F7;
    std::wstring font = L"FiraCode Nerd Font";
} S;

constexpr UINT kBase = 0x1E1E2E, kSurface0 = 0x313244, kSurface1 = 0x45475A, kText = 0xCDD6F4,
               kSubtext = 0xA6ADC8, kOverlay = 0x6C7086, kPeach = 0xFAB387, kRed = 0xF38BA8;

int Clamp(int v, int lo, int hi) { return v < lo ? lo : v > hi ? hi : v; }

UINT ParseHex(PCWSTR s, UINT def) {
    if (!s) return def;
    while (*s == L' ' || *s == L'#') s++;
    wchar_t* end = nullptr;
    unsigned long v = wcstoul(s, &end, 16);
    if (end - s != 6) return def;
    return (UINT)v;
}

UINT ColorSetting(PCWSTR name, UINT def) {
    PCWSTR v = Wh_GetStringSetting(name);
    UINT c = ParseHex(v, def);
    Wh_FreeStringSetting(v);
    return c;
}

// The dock's menu and the taskbar's menu change position, Recycle Bin and title on
// the go. Those picks are kept as stored values; changing the setting itself in
// Windhawk wins again and clears the pick.
int Overridable(const std::wstring& name, int settingVal) {
    std::wstring seen = L"seen." + name, ov = L"ov." + name;
    if (Wh_GetIntValue(seen.c_str(), -999) != settingVal) {
        Wh_SetIntValue(seen.c_str(), settingVal);
        Wh_SetIntValue(ov.c_str(), -1);
    }
    int v = Wh_GetIntValue(ov.c_str(), -1);
    return v < 0 ? settingVal : v;
}

void SetOverride(const std::wstring& name, int v) { Wh_SetIntValue((L"ov." + name).c_str(), v); }

int PlaceSetting() {
    PCWSTR v = Wh_GetStringSetting(L"position");
    int r = 0;
    if (v) {
        if (!wcscmp(v, L"bottom")) r = 1;
        else if (!wcscmp(v, L"top")) r = 2;
        else if (!wcscmp(v, L"left")) r = 3;
        else if (!wcscmp(v, L"right")) r = 4;
    }
    Wh_FreeStringSetting(v);
    return r;
}

void LoadSettings() {
    S.iconSize = Clamp(Wh_GetIntSetting(L"iconSize"), 24, 64);
    S.spacing = Clamp(Wh_GetIntSetting(L"spacing"), 0, 24);
    S.bottomGap = Clamp(Wh_GetIntSetting(L"bottomGap"), 0, 48);
    S.reserve = Wh_GetIntSetting(L"reserveSpace") != 0;
    S.showOpen = Wh_GetIntSetting(L"showOpenApps") != 0;
    S.previews = Wh_GetIntSetting(L"previews") != 0;
    S.hoverDelay = Clamp(Wh_GetIntSetting(L"hoverDelay"), 0, 2000);
    S.hideFull = Wh_GetIntSetting(L"hideOnFullscreen") != 0;
    S.showTitle = Overridable(L"showTitle", Wh_GetIntSetting(L"showTitle") != 0) != 0;
    S.recycle = Overridable(L"recycleBin", Wh_GetIntSetting(L"recycleBin") != 0) != 0;
    S.place = Clamp(Overridable(L"position", PlaceSetting()), 0, 4);
    S.lineOpen = Wh_GetIntValue(L"lineOpen", 1) != 0;
    S.lineBin = Wh_GetIntValue(L"lineBin", 1) != 0;
    S.opacity = Clamp(Wh_GetIntSetting(L"surfaceOpacity"), 30, 100);
    S.edge = ColorSetting(L"edgeColor", 0x585B70);
    S.from = ColorSetting(L"hoverColorFrom", 0x89B4FA);
    S.to = ColorSetting(L"hoverColorTo", 0xCBA6F7);
    S.edgeWidth = Clamp(Wh_GetIntSetting(L"edgeWidth"), 0, 6);
    S.fadeMs = Clamp(Wh_GetIntSetting(L"fadeMs"), 0, 1000);
    // New in 0.3.2: an install that never saved them reads 0, so 0 means the default.
    int lift = Wh_GetIntSetting(L"iconLift"), pw = Wh_GetIntSetting(L"previewSize"),
        tw = Wh_GetIntSetting(L"titleMaxWidth");
    S.iconLift = Clamp(lift, 0, 10);
    S.previewW = pw ? Clamp(pw, 140, 360) : 208;
    S.titleMaxW = tw ? Clamp(tw, 200, 1400) : 720;
    PCWSTR f = Wh_GetStringSetting(L"font");
    S.font = (f && *f) ? f : L"FiraCode Nerd Font";
    Wh_FreeStringSetting(f);
}

// Window corners come from Custom Window Corner Radius when it is on; DWM clips our
// windows at that radius, so every edge we draw sits on the same value.
int LiveRadius() {
    HKEY k;
    int r = 8;
    if (RegOpenKeyExW(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Windhawk\\Engine\\Mods\\custom-corner-radius", 0, KEY_READ,
                      &k) == ERROR_SUCCESS) {
        DWORD disabled = 0, size = sizeof(disabled);
        bool off = RegGetValueW(k, nullptr, L"Disabled", RRF_RT_REG_DWORD, nullptr, &disabled, &size) ==
                       ERROR_SUCCESS &&
                   disabled;
        DWORD v = 0;
        size = sizeof(v);
        if (!off && RegGetValueW(k, L"Settings", L"radius", RRF_RT_REG_DWORD, nullptr, &v, &size) == ERROR_SUCCESS &&
            v > 0 && v < 64)
            r = (int)v;
        RegCloseKey(k);
    }
    return r;
}

bool TransparencyOn() {
    DWORD v = 1, size = sizeof(v);
    RegGetValueW(HKEY_CURRENT_USER, L"Software\\Microsoft\\Windows\\CurrentVersion\\Themes\\Personalize",
                 L"EnableTransparency", RRF_RT_REG_DWORD, nullptr, &v, &size);
    return v != 0;
}

// ---------------------------------------------------------------------------
// Small helpers
// ---------------------------------------------------------------------------
std::wstring Lower(std::wstring s) {
    CharLowerBuffW(s.data(), (DWORD)s.size());
    return s;
}

std::wstring FileName(const std::wstring& p) {
    size_t i = p.find_last_of(L"\\/");
    return i == std::wstring::npos ? p : p.substr(i + 1);
}

std::wstring StripExt(std::wstring s) {
    size_t i = s.find_last_of(L'.');
    if (i != std::wstring::npos && i > 0) s.resize(i);
    return s;
}

const PROPERTYKEY kPKeyAumid = {{0x9F4C2855, 0x9F79, 0x4B39, {0xA8, 0xD0, 0xE1, 0xD4, 0x2D, 0xE1, 0xD5, 0xF3}}, 5};

std::wstring ReadAumid(IPropertyStore* ps) {
    std::wstring out;
    if (!ps) return out;
    PROPVARIANT pv;
    PropVariantInit(&pv);
    if (SUCCEEDED(ps->GetValue(kPKeyAumid, &pv)) && pv.vt == VT_LPWSTR && pv.pwszVal) out = pv.pwszVal;
    PropVariantClear(&pv);
    return out;
}

std::wstring WindowAumid(HWND h) {
    ComPtr<IPropertyStore> ps;
    if (FAILED(SHGetPropertyStoreForWindow(h, IID_PPV_ARGS(&ps)))) return L"";
    return ReadAumid(ps.Get());
}

std::wstring ExeOfPid(DWORD pid) {
    HANDLE p = OpenProcess(PROCESS_QUERY_LIMITED_INFORMATION, FALSE, pid);
    if (!p) return L"";
    wchar_t buf[MAX_PATH * 2];
    DWORD n = ARRAYSIZE(buf);
    std::wstring out;
    if (QueryFullProcessImageNameW(p, 0, buf, &n)) out.assign(buf, n);
    CloseHandle(p);
    return out;
}

std::wstring FileDescription(const std::wstring& path) {
    DWORD handle = 0;
    DWORD n = GetFileVersionInfoSizeW(path.c_str(), &handle);
    if (!n) return L"";
    std::vector<BYTE> buf(n);
    if (!GetFileVersionInfoW(path.c_str(), 0, n, buf.data())) return L"";
    struct LangCp {
        WORD lang, cp;
    }* tr = nullptr;
    UINT len = 0;
    if (!VerQueryValueW(buf.data(), L"\\VarFileInfo\\Translation", (void**)&tr, &len) || len < sizeof(LangCp))
        return L"";
    wchar_t q[80];
    swprintf_s(q, L"\\StringFileInfo\\%04x%04x\\FileDescription", tr[0].lang, tr[0].cp);
    wchar_t* v = nullptr;
    if (VerQueryValueW(buf.data(), q, (void**)&v, &len) && v && len > 1) return v;
    return L"";
}

std::wstring ShellDisplayName(const std::wstring& parsing) {
    ComPtr<IShellItem> item;
    if (FAILED(SHCreateItemFromParsingName(parsing.c_str(), nullptr, IID_PPV_ARGS(&item)))) return L"";
    PWSTR name = nullptr;
    std::wstring out;
    if (SUCCEEDED(item->GetDisplayName(SIGDN_NORMALDISPLAY, &name)) && name) out = name;
    CoTaskMemFree(name);
    return out;
}

std::wstring WindowTitle(HWND h) {
    wchar_t buf[512];
    int n = InternalGetWindowText(h, buf, ARRAYSIZE(buf));
    return std::wstring(buf, std::max(0, n));
}

// Windhawk runs each tool mod in its own windhawk-mod.exe, so the program's own
// name is "Windhawk mod" for all of them. The mod's id is on the process's
// command line, and its name is in the mod's source header.
bool IsModHost(const std::wstring& exeLower) {
    return FileName(exeLower).rfind(L"windhawk-mod", 0) == 0;
}

std::wstring ModIdOfPid(DWORD pid) {
    using NtQip = LONG(NTAPI*)(HANDLE, ULONG, PVOID, ULONG, PULONG);
    static NtQip query = (NtQip)GetProcAddress(GetModuleHandleW(L"ntdll.dll"), "NtQueryInformationProcess");
    if (!query) return L"";
    HANDLE p = OpenProcess(PROCESS_QUERY_LIMITED_INFORMATION, FALSE, pid);
    if (!p) return L"";
    constexpr ULONG kCommandLine = 60;  // ProcessCommandLineInformation
    std::vector<BYTE> buf(8192);
    ULONG got = 0;
    LONG st = query(p, kCommandLine, buf.data(), (ULONG)buf.size(), &got);
    if (st < 0 && got > buf.size()) {
        buf.resize(got);
        st = query(p, kCommandLine, buf.data(), (ULONG)buf.size(), &got);
    }
    CloseHandle(p);
    if (st < 0) return L"";
    struct Ustr {
        USHORT len, max;
        PWSTR text;
    };
    auto* us = (Ustr*)buf.data();
    if (!us->text || !us->len) return L"";
    std::wstring cmd(us->text, us->len / sizeof(wchar_t));
    size_t i = cmd.find(L"-tool-mod ");
    if (i == std::wstring::npos) return L"";
    i += 10;
    while (i < cmd.size() && cmd[i] == L' ') i++;
    wchar_t end = L' ';
    if (i < cmd.size() && cmd[i] == L'"') {
        end = L'"';
        i++;
    }
    size_t e = cmd.find(end, i);
    return cmd.substr(i, e == std::wstring::npos ? std::wstring::npos : e - i);
}

std::wstring ModNameOfId(const std::wstring& id) {
    static std::unordered_map<std::wstring, std::wstring> cache;
    if (id.empty()) return L"";
    auto c = cache.find(id);
    if (c != cache.end()) return c->second;
    std::wstring name;
    wchar_t pd[MAX_PATH] = {};
    if (GetEnvironmentVariableW(L"ProgramData", pd, MAX_PATH)) {
        std::wstring path = std::wstring(pd) + L"\\Windhawk\\ModsSource\\" + id + L".wh.cpp";
        HANDLE f = CreateFileW(path.c_str(), GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
                               nullptr, OPEN_EXISTING, 0, nullptr);
        if (f != INVALID_HANDLE_VALUE) {
            char head[8192];
            DWORD n = 0;
            if (ReadFile(f, head, sizeof(head) - 1, &n, nullptr)) {
                std::string h(head, n);
                size_t at = h.find("// @name ");
                if (at != std::string::npos) {
                    at += 9;
                    size_t e = h.find_first_of("\r\n", at);
                    std::string v = h.substr(at, e == std::string::npos ? std::string::npos : e - at);
                    size_t a = v.find_first_not_of(" \t"), b = v.find_last_not_of(" \t");
                    if (a != std::string::npos) {
                        v = v.substr(a, b - a + 1);
                        int wn = MultiByteToWideChar(CP_UTF8, 0, v.data(), (int)v.size(), nullptr, 0);
                        name.resize(wn);
                        MultiByteToWideChar(CP_UTF8, 0, v.data(), (int)v.size(), name.data(), wn);
                    }
                }
            }
            CloseHandle(f);
        }
    }
    cache[id] = name;
    return name;
}

// The mod's name, or the window's title without a trailing " settings" when the
// mod can't be told (an elevated mod hides its command line).
std::wstring ModWindowName(const std::wstring& id, HWND h) {
    std::wstring n = ModNameOfId(id);
    if (!n.empty()) return n;
    n = WindowTitle(h);
    constexpr PCWSTR tail = L" settings";
    size_t tl = wcslen(tail);
    if (n.size() > tl && _wcsicmp(n.c_str() + n.size() - tl, tail) == 0) n.resize(n.size() - tl);
    return n;
}

// Apps Windows draws without an icon file of their own, given the icon Mocha App
// Icons puts on their window.
std::wstring ThemedIconFile(const std::wstring& src) {
    if (Lower(src).find(L"windows.immersivecontrolpanel_cw5n1h2txyewy!") == std::wstring::npos) return L"";
    wchar_t la[MAX_PATH] = {};
    if (!GetEnvironmentVariableW(L"LOCALAPPDATA", la, MAX_PATH)) return L"";
    std::wstring path = std::wstring(la) + L"\\Mocha App Icons\\Settings\\Settings-Catppuccin.ico";
    return GetFileAttributesW(path.c_str()) == INVALID_FILE_ATTRIBUTES ? L"" : path;
}

UINT MonitorDpi(HMONITOR mon) {
    UINT x = 96, y = 96;
    if (FAILED(GetDpiForMonitor(mon, MDT_EFFECTIVE_DPI, &x, &y))) return 96;
    return x;
}

D2D1_COLOR_F Col(UINT rgb, float a = 1.f) {
    return D2D1::ColorF(((rgb >> 16) & 255) / 255.f, ((rgb >> 8) & 255) / 255.f, (rgb & 255) / 255.f, a);
}

float Lerp(float a, float b, float t) { return a + (b - a) * t; }

// ---------------------------------------------------------------------------
// Direct2D
// ---------------------------------------------------------------------------
ComPtr<ID2D1Factory> g_d2d;
ComPtr<IDWriteFactory> g_dw;

bool EnsureFactories() {
    if (!g_d2d && FAILED(D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, __uuidof(ID2D1Factory), nullptr,
                                           (void**)g_d2d.GetAddressOf())))
        return false;
    if (!g_dw && FAILED(DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory),
                                            (IUnknown**)g_dw.GetAddressOf())))
        return false;
    return true;
}

struct Surface {
    HWND hwnd = nullptr;
    ComPtr<ID2D1HwndRenderTarget> rt;
    ComPtr<ID2D1GradientStopCollection> stops;
    UINT gen = 1;
    bool Ensure() {
        if (rt) return true;
        if (!hwnd || !EnsureFactories()) return false;
        RECT rc;
        GetClientRect(hwnd, &rc);
        float dpi = (float)GetDpiForWindow(hwnd);
        auto props = D2D1::RenderTargetProperties(
            D2D1_RENDER_TARGET_TYPE_DEFAULT,
            D2D1::PixelFormat(DXGI_FORMAT_B8G8R8A8_UNORM, D2D1_ALPHA_MODE_PREMULTIPLIED), dpi, dpi);
        auto hp = D2D1::HwndRenderTargetProperties(
            hwnd, D2D1::SizeU(std::max<LONG>(1, rc.right), std::max<LONG>(1, rc.bottom)));
        if (FAILED(g_d2d->CreateHwndRenderTarget(&props, &hp, rt.GetAddressOf()))) return false;
        D2D1_GRADIENT_STOP gs[2] = {{0.f, Col(S.from)}, {1.f, Col(S.to)}};
        rt->CreateGradientStopCollection(gs, 2, stops.GetAddressOf());
        rt->SetTextAntialiasMode(D2D1_TEXT_ANTIALIAS_MODE_GRAYSCALE);
        return true;
    }
    void Resize() {
        if (!rt) return;
        RECT rc;
        GetClientRect(hwnd, &rc);
        rt->Resize(D2D1::SizeU(std::max<LONG>(1, rc.right), std::max<LONG>(1, rc.bottom)));
        float dpi = (float)GetDpiForWindow(hwnd);
        rt->SetDpi(dpi, dpi);
    }
    void Discard() {
        rt.Reset();
        stops.Reset();
        gen++;
    }
    float Scale() const { return hwnd ? GetDpiForWindow(hwnd) / 96.f : 1.f; }
    ComPtr<ID2D1SolidColorBrush> Solid(UINT rgb, float a = 1.f) {
        ComPtr<ID2D1SolidColorBrush> b;
        rt->CreateSolidColorBrush(Col(rgb, a), b.GetAddressOf());
        return b;
    }
    // Blue at the bottom left fading to mauve at the top right, like the window borders.
    ComPtr<ID2D1LinearGradientBrush> Grad(D2D1_RECT_F r, float opacity) {
        ComPtr<ID2D1LinearGradientBrush> b;
        if (stops)
            rt->CreateLinearGradientBrush(D2D1::LinearGradientBrushProperties(D2D1::Point2F(r.left, r.bottom),
                                                                              D2D1::Point2F(r.right, r.top)),
                                          D2D1::BrushProperties(opacity), stops.Get(), b.GetAddressOf());
        return b;
    }
};

void StrokeRound(Surface& s, D2D1_RECT_F r, float radius, float w, ID2D1Brush* b) {
    if (!b || w <= 0) return;
    D2D1_RECT_F in{r.left + w / 2, r.top + w / 2, r.right - w / 2, r.bottom - w / 2};
    float maxR = std::min(in.right - in.left, in.bottom - in.top) / 2;
    float rr = std::min(maxR, std::max(0.f, radius - w / 2));
    s.rt->DrawRoundedRectangle(D2D1::RoundedRect(in, rr, rr), b, w);
}

std::map<std::pair<int, int>, ComPtr<IDWriteTextFormat>> g_formats;

IDWriteTextFormat* Format(float size, DWRITE_FONT_WEIGHT weight, bool icons = false) {
    auto key = std::make_pair((int)(size * 10) + (icons ? 100000 : 0), (int)weight);
    auto it = g_formats.find(key);
    if (it != g_formats.end()) return it->second.Get();
    ComPtr<IDWriteTextFormat> f;
    if (!EnsureFactories() ||
        FAILED(g_dw->CreateTextFormat(icons ? L"Segoe Fluent Icons" : S.font.c_str(), nullptr, weight,
                                      DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, size, L"",
                                      f.GetAddressOf())))
        return nullptr;
    f->SetWordWrapping(DWRITE_WORD_WRAPPING_NO_WRAP);
    f->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
    if (icons) f->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
    DWRITE_TRIMMING trim{DWRITE_TRIMMING_GRANULARITY_CHARACTER, 0, 0};
    ComPtr<IDWriteInlineObject> sign;
    g_dw->CreateEllipsisTrimmingSign(f.Get(), sign.GetAddressOf());
    f->SetTrimming(&trim, sign.Get());
    g_formats[key] = f;
    return f.Get();
}

float TextWidth(const std::wstring& t, IDWriteTextFormat* f) {
    ComPtr<IDWriteTextLayout> l;
    if (!f || FAILED(g_dw->CreateTextLayout(t.c_str(), (UINT32)t.size(), f, 4000, 100, l.GetAddressOf()))) return 0;
    DWRITE_TEXT_METRICS m{};
    l->GetMetrics(&m);
    return m.widthIncludingTrailingWhitespace;
}

void DrawText(Surface& s, const std::wstring& t, IDWriteTextFormat* f, D2D1_RECT_F r, UINT rgb, float a = 1.f) {
    if (!f || t.empty()) return;
    auto b = s.Solid(rgb, a);
    s.rt->DrawText(t.c_str(), (UINT32)t.size(), f, r, b.Get(), D2D1_DRAW_TEXT_OPTIONS_CLIP);
}

// ---------------------------------------------------------------------------
// Glass
// ---------------------------------------------------------------------------
struct AccentPolicyData {
    int state, flags, color, animation;
};
struct WindowCompositionData {
    DWORD attrib;
    PVOID data;
    SIZE_T size;
};

void SetAccent(HWND h, int state, DWORD abgr) {
    using Fn = BOOL(WINAPI*)(HWND, WindowCompositionData*);
    static Fn fn = (Fn)(void*)GetProcAddress(GetModuleHandleW(L"user32.dll"), "SetWindowCompositionAttribute");
    if (!fn) return;
    AccentPolicyData a{state, state ? 2 : 0, (int)abgr, 0};
    WindowCompositionData d{19 /* WCA_ACCENT_POLICY */, &a, sizeof(a)};
    fn(h, &d);
}

// The house glass sheet: the same acrylic the clipboard and launcher popups use; our
// Direct2D tint colors it. Windows drops the blur on windows that live for hours and
// ignores the same accent sent again, so the accent goes off first, then on. Runs on
// every show and every two minutes while the dock is up (0.3.16, owner: "I can see
// straight through them").
void ApplyBackdrop(HWND h) {
    if (!h) return;
    BOOL dark = TRUE;
    DwmSetWindowAttribute(h, 20 /* DWMWA_USE_IMMERSIVE_DARK_MODE */, &dark, sizeof(dark));
    int none_backdrop = 1;  // DWMSBT_NONE: never the system's light frost
    DwmSetWindowAttribute(h, 38 /* DWMWA_SYSTEMBACKDROP_TYPE */, &none_backdrop, sizeof(none_backdrop));
    SetAccent(h, 0, 0);
    int corner = 2;  // DWMWCP_ROUND
    DwmSetWindowAttribute(h, 33 /* DWMWA_WINDOW_CORNER_PREFERENCE */, &corner, sizeof(corner));
    COLORREF none = 0xFFFFFFFE;  // DWMWA_COLOR_NONE: we draw our own edge
    DwmSetWindowAttribute(h, 34 /* DWMWA_BORDER_COLOR */, &none, sizeof(none));
    DwmSetWindowAttribute(h, 35 /* DWMWA_CAPTION_COLOR */, &none, sizeof(none));
    MARGINS m{0, 0, 0, 0};
    DwmExtendFrameIntoClientArea(h, &m);
    DWM_BLURBEHIND bb{};
    bb.dwFlags = DWM_BB_ENABLE | DWM_BB_BLURREGION;
    bb.fEnable = TRUE;
    bb.hRgnBlur = CreateRectRgn(0, 0, -1, -1);
    DwmEnableBlurBehindWindow(h, &bb);
    if (bb.hRgnBlur) DeleteObject(bb.hRgnBlur);
    SetAccent(h, 4 /* ACCENT_ENABLE_ACRYLICBLURBEHIND */, 0x01000000 | 0x2E1E1E);
    SetWindowPos(h, nullptr, 0, 0, 0, 0, SWP_FRAMECHANGED | SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE);
}

// The Mocha tint over the blur. With transparency effects off Windows drops the blur, so
// the tint goes opaque rather than leaving a clear window.
float TintAlpha() { return TransparencyOn() ? S.opacity / 100.f : 1.f; }

// ---------------------------------------------------------------------------
// Pins
// ---------------------------------------------------------------------------
struct Pin {
    std::wstring kind, value;  // lnk | aumid | exe
    std::wstring name, exeLower, aumid, procStart, iconSrc;
    bool sepAfter = false;  // a separator line after this pin
};
std::vector<Pin> g_pins;

void ResolvePin(Pin& p) {
    p.name.clear();
    p.exeLower.clear();
    p.aumid.clear();
    p.procStart.clear();
    if (p.kind == L"lnk") {
        p.name = StripExt(FileName(p.value));
        p.iconSrc = p.value;
        ComPtr<IShellLinkW> sl;
        ComPtr<IPersistFile> pf;
        if (SUCCEEDED(CoCreateInstance(CLSID_ShellLink, nullptr, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&sl))) &&
            SUCCEEDED(sl.As(&pf)) && SUCCEEDED(pf->Load(p.value.c_str(), STGM_READ))) {
            wchar_t buf[MAX_PATH * 2] = {};
            if (SUCCEEDED(sl->GetPath(buf, ARRAYSIZE(buf), nullptr, 0)) && *buf) p.exeLower = Lower(buf);
            wchar_t args[1024] = {};
            if (SUCCEEDED(sl->GetArguments(args, ARRAYSIZE(args)))) {
                std::wstring a = Lower(args);
                size_t i = a.find(L"--processstart");
                if (i != std::wstring::npos) {
                    i += 14;
                    while (i < a.size() && (a[i] == L' ' || a[i] == L'"' || a[i] == L'=')) i++;
                    size_t e = i;
                    while (e < a.size() && a[e] != L' ' && a[e] != L'"') e++;
                    p.procStart = a.substr(i, e - i);
                }
            }
            ComPtr<IPropertyStore> ps;
            if (SUCCEEDED(sl.As(&ps))) p.aumid = ReadAumid(ps.Get());
        }
    } else if (p.kind == L"aumid") {
        p.aumid = p.value;
        p.iconSrc = L"shell:AppsFolder\\" + p.value;
        p.name = ShellDisplayName(p.iconSrc);
    } else {
        p.exeLower = Lower(p.value);
        p.iconSrc = p.value;
        p.name = FileDescription(p.value);
    }
    if (p.name.empty()) p.name = StripExt(FileName(p.value));
}

// Separators are kept apart from the pins, so an older dock still reads the pin list.
void SavePins() {
    std::wstring s, seps;
    for (auto& p : g_pins) {
        s += p.kind + L":" + p.value + L"\n";
        if (p.sepAfter) seps += p.kind + L":" + p.value + L"\n";
    }
    Wh_SetStringValue(L"pins", s.c_str());
    Wh_SetStringValue(L"seps", seps.c_str());
}

// The taskbar's own pins, in its order: the Taskband blob names each pinned shortcut in
// order; a shortcut file the blob never names is not pinned any more.
std::vector<Pin> TaskbarPins() {
    std::vector<Pin> out;
    PWSTR appdata = nullptr;
    if (FAILED(SHGetKnownFolderPath(FOLDERID_RoamingAppData, 0, nullptr, &appdata))) return out;
    std::wstring dir = std::wstring(appdata) + L"\\Microsoft\\Internet Explorer\\Quick Launch\\User Pinned\\TaskBar\\";
    CoTaskMemFree(appdata);

    std::vector<BYTE> blob;
    DWORD size = 0;
    const wchar_t* key = L"Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\Taskband";
    if (RegGetValueW(HKEY_CURRENT_USER, key, L"Favorites", RRF_RT_REG_BINARY, nullptr, nullptr, &size) ==
            ERROR_SUCCESS &&
        size) {
        blob.resize(size);
        if (RegGetValueW(HKEY_CURRENT_USER, key, L"Favorites", RRF_RT_REG_BINARY, nullptr, blob.data(), &size) !=
            ERROR_SUCCESS)
            blob.clear();
    }

    auto find = [&](const std::wstring& name) -> size_t {
        if (blob.empty()) return 0;
        std::wstring low = Lower(name);
        size_t best = SIZE_MAX;
        // UTF-16 copy of the name.
        for (size_t i = 0; i + low.size() * 2 <= blob.size(); i++) {
            bool ok = true;
            for (size_t j = 0; j < low.size() && ok; j++) {
                wchar_t c = (wchar_t)(blob[i + j * 2] | (blob[i + j * 2 + 1] << 8));
                ok = towlower(c) == low[j];
            }
            if (ok) {
                best = i;
                break;
            }
        }
        // 8-bit copy of the name.
        for (size_t i = 0; i + low.size() <= blob.size() && i < best; i++) {
            bool ok = true;
            for (size_t j = 0; j < low.size() && ok; j++) ok = towlower((wchar_t)blob[i + j]) == low[j];
            if (ok) {
                best = i;
                break;
            }
        }
        return best;
    };

    std::vector<std::pair<size_t, Pin>> found;
    WIN32_FIND_DATAW fd;
    HANDLE h = FindFirstFileW((dir + L"*.lnk").c_str(), &fd);
    if (h != INVALID_HANDLE_VALUE) {
        do {
            if (fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) continue;
            size_t at = find(fd.cFileName);
            if (at == SIZE_MAX) continue;
            Pin p;
            p.kind = L"lnk";
            p.value = dir + fd.cFileName;
            found.push_back({at, p});
        } while (FindNextFileW(h, &fd));
        FindClose(h);
    }
    std::stable_sort(found.begin(), found.end(), [](auto& a, auto& b) { return a.first < b.first; });
    for (auto& f : found) out.push_back(f.second);
    return out;
}

void LoadPins() {
    g_pins.clear();
    if (!Wh_GetIntValue(L"pinsSeeded", 0)) {
        g_pins = TaskbarPins();
        SavePins();
        Wh_SetIntValue(L"pinsSeeded", 1);
    } else {
        std::vector<wchar_t> buf(32768);
        Wh_GetStringValue(L"pins", buf.data(), buf.size());
        std::wstring all = buf.data();
        size_t start = 0;
        while (start < all.size()) {
            size_t e = all.find(L'\n', start);
            if (e == std::wstring::npos) e = all.size();
            std::wstring line = all.substr(start, e - start);
            start = e + 1;
            size_t c = line.find(L':');
            if (c == std::wstring::npos || c == 0) continue;
            Pin p;
            p.kind = line.substr(0, c);
            p.value = line.substr(c + 1);
            if (p.kind != L"lnk" && p.kind != L"aumid" && p.kind != L"exe") continue;
            if (p.kind == L"lnk" && GetFileAttributesW(p.value.c_str()) == INVALID_FILE_ATTRIBUTES) continue;
            g_pins.push_back(p);
        }
    }
    std::vector<wchar_t> sb(32768);
    Wh_GetStringValue(L"seps", sb.data(), sb.size());
    std::wstring seps = L"\n" + std::wstring(sb.data());
    for (auto& p : g_pins) {
        ResolvePin(p);
        p.sepAfter = seps.find(L"\n" + p.kind + L":" + p.value + L"\n") != std::wstring::npos;
    }
}

// ---------------------------------------------------------------------------
// Icons
// ---------------------------------------------------------------------------
struct Icon {
    std::vector<UINT32> px;
    int w = 0, h = 0;
    D2D1_RECT_F src{};
    ComPtr<ID2D1Bitmap> bmp;
    UINT gen = 0;
    ULONGLONG retryAt = 0;  // a failed load is tried again after this tick
};
std::unordered_map<std::wstring, Icon> g_icons;

bool PixelsFromHBitmap(HBITMAP bitmap, Icon& ic) {
    BITMAP bm{};
    if (!GetObjectW(bitmap, sizeof(bm), &bm) || bm.bmWidth <= 0) return false;
    int w = bm.bmWidth, h = std::abs(bm.bmHeight);
    std::vector<UINT32> px((size_t)w * h);
    BITMAPINFO bi{};
    bi.bmiHeader.biSize = sizeof(bi.bmiHeader);
    bi.bmiHeader.biWidth = w;
    bi.bmiHeader.biHeight = -h;
    bi.bmiHeader.biPlanes = 1;
    bi.bmiHeader.biBitCount = 32;
    bi.bmiHeader.biCompression = BI_RGB;
    HDC dc = GetDC(nullptr);
    int lines = GetDIBits(dc, bitmap, 0, h, px.data(), &bi, DIB_RGB_COLORS);
    ReleaseDC(nullptr, dc);
    if (!lines) return false;
    if (std::none_of(px.begin(), px.end(), [](UINT32 p) { return (p >> 24) != 0; }))
        for (auto& p : px) p |= 0xFF000000;
    bool premultiplied = std::none_of(px.begin(), px.end(), [](UINT32 p) {
        UINT a = p >> 24;
        return ((p >> 16) & 0xFF) > a || ((p >> 8) & 0xFF) > a || (p & 0xFF) > a;
    });
    if (!premultiplied) {
        for (auto& p : px) {
            UINT a = p >> 24;
            p = (a << 24) | ((((p >> 16) & 0xFF) * a / 255) << 16) | ((((p >> 8) & 0xFF) * a / 255) << 8) |
                ((p & 0xFF) * a / 255);
        }
    }
    // Icons drawn small inside a big transparent square get their content scaled up, so
    // every icon reads at the same size.
    int l = w, t = h, r = -1, b = -1;
    for (int y = 0; y < h; y++)
        for (int x = 0; x < w; x++)
            if ((px[(size_t)y * w + x] >> 24) > 8) {
                l = std::min(l, x);
                r = std::max(r, x);
                t = std::min(t, y);
                b = std::max(b, y);
            }
    ic.src = D2D1::RectF(0, 0, (float)w, (float)h);
    if (r >= l && b >= t) {
        float content = (float)std::max(r - l + 1, b - t + 1);
        if (content < w * 0.8f) {
            float side = std::min((float)w, content / 0.92f);
            float cx = (l + r + 1) / 2.f, cy = (t + b + 1) / 2.f;
            ic.src = D2D1::RectF(cx - side / 2, cy - side / 2, cx + side / 2, cy + side / 2);
        }
    }
    ic.px = std::move(px);
    ic.w = w;
    ic.h = h;
    return true;
}

bool IconFromShell(const std::wstring& src, int size, Icon& ic) {
    if (src.empty()) return false;
    // A program with no icon inside it gets the shell's blank page; the window's
    // own icon is better then.
    if (src.size() > 4 && _wcsicmp(src.c_str() + src.size() - 4, L".exe") == 0 &&
        ExtractIconExW(src.c_str(), -1, nullptr, nullptr, 0) == 0)
        return false;
    ComPtr<IShellItem> item;
    ComPtr<IShellItemImageFactory> f;
    HBITMAP bmp = nullptr;
    if (FAILED(SHCreateItemFromParsingName(src.c_str(), nullptr, IID_PPV_ARGS(&item))) ||
        FAILED(item.As(&f)) || FAILED(f->GetImage(SIZE{size, size}, SIIGBF_ICONONLY, &bmp)) || !bmp)
        return false;
    bool ok = PixelsFromHBitmap(bmp, ic);
    DeleteObject(bmp);
    return ok;
}

bool IconFromHicon(HICON hi, int size, Icon& ic) {
    if (!hi) return false;
    BITMAPINFO bi{};
    bi.bmiHeader.biSize = sizeof(bi.bmiHeader);
    bi.bmiHeader.biWidth = size;
    bi.bmiHeader.biHeight = -size;
    bi.bmiHeader.biPlanes = 1;
    bi.bmiHeader.biBitCount = 32;
    void* bits = nullptr;
    HDC dc = CreateCompatibleDC(nullptr);
    HBITMAP dib = CreateDIBSection(dc, &bi, DIB_RGB_COLORS, &bits, nullptr, 0);
    if (!dib) {
        DeleteDC(dc);
        return false;
    }
    HGDIOBJ old = SelectObject(dc, dib);
    DrawIconEx(dc, 0, 0, hi, size, size, 0, nullptr, DI_NORMAL);
    SelectObject(dc, old);
    bool ok = PixelsFromHBitmap(dib, ic);
    DeleteObject(dib);
    DeleteDC(dc);
    return ok;
}

bool IconFromFile(const std::wstring& path, int size, Icon& ic) {
    HICON hi = (HICON)LoadImageW(nullptr, path.c_str(), IMAGE_ICON, size, size, LR_LOADFROMFILE);
    if (!hi) return false;
    bool ok = IconFromHicon(hi, size, ic);
    DestroyIcon(hi);
    return ok;
}

bool IconFromWindow(HWND h, int size, Icon& ic) {
    DWORD_PTR r = 0;
    HICON hi = nullptr;
    if (SendMessageTimeoutW(h, WM_GETICON, ICON_BIG, 0, SMTO_ABORTIFHUNG, 100, &r) && r) hi = (HICON)r;
    if (!hi) hi = (HICON)GetClassLongPtrW(h, GCLP_HICON);
    return IconFromHicon(hi, size, ic);
}

// The shell's own empty and full Recycle Bin icons, so the dock matches the
// desktop and the icon theme.
bool IconFromRecycle(bool full, int size, Icon& ic) {
    SHSTOCKICONINFO si{sizeof(si)};
    if (FAILED(SHGetStockIconInfo(full ? SIID_RECYCLERFULL : SIID_RECYCLER, SHGSI_ICONLOCATION, &si))) return false;
    HICON hi = nullptr;
    if (FAILED(SHDefExtractIconW(si.szPath, si.iIcon, 0, &hi, nullptr, MAKELONG(size, 0))) || !hi) return false;
    bool ok = IconFromHicon(hi, size, ic);
    DestroyIcon(hi);
    return ok;
}

// Windows' own Store apps (Terminal, Calculator, Paint...) get their Catppuccin icon from
// UWP Assets Redirect Plus, but only inside Explorer and Start. The dock runs in its own
// process, so it reads the same icon theme itself: package family name -> theme file.
std::unordered_map<std::wstring, std::wstring> g_themeIcons;
bool g_themeRead = false;

std::wstring RegText(const wchar_t* key, const wchar_t* value) {
    wchar_t buf[512] = {};
    DWORD cb = sizeof(buf);
    if (RegGetValueW(HKEY_LOCAL_MACHINE, key, value, RRF_RT_REG_SZ, nullptr, buf, &cb) != ERROR_SUCCESS)
        return {};
    return buf;
}

std::wstring ReadTextFile(const std::wstring& path) {
    HANDLE f = CreateFileW(path.c_str(), GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, nullptr,
                           OPEN_EXISTING, 0, nullptr);
    if (f == INVALID_HANDLE_VALUE) return {};
    std::string bytes;
    LARGE_INTEGER size{};
    if (GetFileSizeEx(f, &size) && size.QuadPart > 0 && size.QuadPart < (1 << 20)) {
        bytes.resize((size_t)size.QuadPart);
        DWORD got = 0;
        if (!ReadFile(f, bytes.data(), (DWORD)bytes.size(), &got, nullptr)) got = 0;
        bytes.resize(got);
    }
    CloseHandle(f);
    if (bytes.size() >= 2 && (unsigned char)bytes[0] == 0xFF && (unsigned char)bytes[1] == 0xFE)
        return std::wstring((const wchar_t*)(bytes.data() + 2), (bytes.size() - 2) / 2);
    size_t skip = bytes.rfind("\xEF\xBB\xBF", 0) == 0 ? 3 : 0;
    int n = MultiByteToWideChar(CP_UTF8, 0, bytes.data() + skip, (int)(bytes.size() - skip), nullptr, 0);
    std::wstring text(n, L'\0');
    MultiByteToWideChar(CP_UTF8, 0, bytes.data() + skip, (int)(bytes.size() - skip), text.data(), n);
    return text;
}

void ReadIconTheme() {
    g_themeRead = true;
    const wchar_t* modKey = L"SOFTWARE\\Windhawk\\Engine\\Mods\\local@uwp-assets-redirect-plus";
    HKEY k = nullptr;
    if (RegOpenKeyExW(HKEY_LOCAL_MACHINE, modKey, 0, KEY_READ, &k) != ERROR_SUCCESS) return;
    RegCloseKey(k);
    DWORD off = 0, cb = sizeof(off);
    if (RegGetValueW(HKEY_LOCAL_MACHINE, modKey, L"Disabled", RRF_RT_REG_DWORD, nullptr, &off, &cb) ==
            ERROR_SUCCESS && off)
        return;
    std::wstring theme =
        RegText(L"SOFTWARE\\Windhawk\\Engine\\Mods\\local@uwp-assets-redirect-plus\\Settings", L"icon-theme");
    if (theme.empty()) return;
    std::replace(theme.begin(), theme.end(), L'/', L'\\');
    // Mod storage folders sit side by side; ours tells where the theme mod's is.
    std::vector<std::wstring> roots;
    wchar_t own[MAX_PATH * 2] = {};
    if (Wh_GetModStoragePath(own, ARRAYSIZE(own))) {
        std::wstring r = own;
        while (!r.empty() && (r.back() == L'\\' || r.back() == L'/')) r.pop_back();
        size_t cut = r.find_last_of(L"\\/");
        if (cut != std::wstring::npos) roots.push_back(r.substr(0, cut));
    }
    roots.push_back(L"C:\\ProgramData\\Windhawk\\Engine\\ModsWritable\\mod-storage");
    std::wstring dir, text;
    for (auto& r : roots) {
        dir = r + L"\\local@uwp-assets-redirect-plus\\icon-themes\\" + theme;
        text = ReadTextFile(dir + L"\\theme.ini");
        if (!text.empty()) break;
    }
    if (text.empty()) return;

    auto trim = [](const std::wstring& s) {
        size_t a = s.find_first_not_of(L" \t\r\n");
        size_t b = s.find_last_not_of(L" \t\r\n");
        return a == std::wstring::npos ? std::wstring() : s.substr(a, b - a + 1);
    };
    std::wstring section;
    size_t pos = 0;
    while (pos <= text.size()) {
        size_t e = text.find(L'\n', pos);
        if (e == std::wstring::npos) e = text.size();
        std::wstring line = trim(text.substr(pos, e - pos));
        pos = e + 1;
        if (line.empty() || line[0] == L';' || line[0] == L'#') continue;
        if (line[0] == L'[') {
            section = Lower(trim(line.substr(1, line.find(L']') - 1)));
            continue;
        }
        size_t eq = line.find(L'=');
        if (eq == std::wstring::npos) continue;
        std::wstring key = Lower(trim(line.substr(0, eq)));
        std::wstring val = trim(line.substr(eq + 1));
        if (val.rfind(L".\\", 0) == 0 || val.rfind(L"./", 0) == 0) val = dir + L"\\" + val.substr(2);
        // "Family|folder" entries cover one app inside a shared package; only a whole
        // package maps to a dock icon.
        if ((section == L"windows-apps" || section == L"system-apps") && key.find(L'|') == std::wstring::npos)
            g_themeIcons[key] = val;
    }
}

bool IconFromPng(const std::wstring& path, int size, Icon& ic) {
    ComPtr<IWICImagingFactory> wic;
    ComPtr<IWICBitmapDecoder> dec;
    ComPtr<IWICBitmapFrameDecode> frame;
    ComPtr<IWICBitmapScaler> scaler;
    ComPtr<IWICFormatConverter> conv;
    if (FAILED(CoCreateInstance(CLSID_WICImagingFactory, nullptr, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&wic))) ||
        FAILED(wic->CreateDecoderFromFilename(path.c_str(), nullptr, GENERIC_READ,
                                              WICDecodeMetadataCacheOnDemand, &dec)) ||
        FAILED(dec->GetFrame(0, &frame)) || FAILED(wic->CreateBitmapScaler(&scaler)) ||
        FAILED(scaler->Initialize(frame.Get(), size, size, WICBitmapInterpolationModeFant)) ||
        FAILED(wic->CreateFormatConverter(&conv)) ||
        FAILED(conv->Initialize(scaler.Get(), GUID_WICPixelFormat32bppBGRA, WICBitmapDitherTypeNone, nullptr, 0,
                                WICBitmapPaletteTypeCustom)))
        return false;
    BITMAPINFO bi{};
    bi.bmiHeader.biSize = sizeof(bi.bmiHeader);
    bi.bmiHeader.biWidth = size;
    bi.bmiHeader.biHeight = -size;
    bi.bmiHeader.biPlanes = 1;
    bi.bmiHeader.biBitCount = 32;
    void* bits = nullptr;
    HBITMAP dib = CreateDIBSection(nullptr, &bi, DIB_RGB_COLORS, &bits, nullptr, 0);
    if (!dib) return false;
    bool ok = SUCCEEDED(conv->CopyPixels(nullptr, size * 4, size * size * 4, (BYTE*)bits)) &&
              PixelsFromHBitmap(dib, ic);
    DeleteObject(dib);
    return ok;
}

// The package family of an app id (Family_publisher!App) or of a program inside a
// WindowsApps package folder (...\WindowsApps\Family_1.2.3.0_x64__publisher\app.exe).
std::wstring PackageFamilyOf(const std::wstring& s) {
    std::wstring l = Lower(s);
    const std::wstring apps = L"shell:appsfolder\\";
    if (l.rfind(apps, 0) == 0) {
        std::wstring id = l.substr(apps.size());
        size_t us = id.find(L'_');
        return us == std::wstring::npos ? L"" : id.substr(0, us);
    }
    const std::wstring wa = L"\\windowsapps\\";
    size_t at = l.find(wa);
    if (at == std::wstring::npos) return L"";
    std::wstring rest = l.substr(at + wa.size());
    size_t us = rest.find(L'_'), sl = rest.find(L'\\');
    if (us == std::wstring::npos || (sl != std::wstring::npos && sl < us)) return L"";
    return rest.substr(0, us);
}

bool IconFromTheme(const std::wstring& src, int size, Icon& ic) {
    std::wstring fam = PackageFamilyOf(src);
    if (fam.empty()) return false;
    if (!g_themeRead) ReadIconTheme();
    auto it = g_themeIcons.find(fam);
    if (it == g_themeIcons.end()) return false;
    const std::wstring& path = it->second;
    DWORD attr = GetFileAttributesW(path.c_str());
    if (attr == INVALID_FILE_ATTRIBUTES) return false;
    if (attr & FILE_ATTRIBUTE_DIRECTORY) {
        // A folder of Store-style logos: take the biggest plain one.
        for (const wchar_t* pat : {L"*targetsize-256_altform-unplated.png", L"*targetsize-256*.png", L"*.png"}) {
            WIN32_FIND_DATAW fd;
            HANDLE h = FindFirstFileW((path + L"\\" + pat).c_str(), &fd);
            if (h == INVALID_HANDLE_VALUE) continue;
            FindClose(h);
            return IconFromPng(path + L"\\" + fd.cFileName, size, ic);
        }
        return false;
    }
    if (path.size() > 4 && _wcsicmp(path.c_str() + path.size() - 4, L".png") == 0)
        return IconFromPng(path, size, ic);
    return IconFromFile(path, size, ic);
}

Icon* GetIcon(const std::wstring& src, const std::wstring& alt, HWND win, int size) {
    std::wstring key = src + L"|" + alt + L"|" + std::to_wstring(size);
    auto it = g_icons.find(key);
    if (it != g_icons.end()) {
        if (!it->second.px.empty()) return &it->second;
        // An app that was still installing or a drive that was asleep: try again
        // now and then, never on every frame.
        if (GetTickCount64() < it->second.retryAt) return nullptr;
    }
    Icon ic;
    std::wstring themed = ThemedIconFile(src);
    if (src.rfind(L"recycle:", 0) == 0) {
        IconFromRecycle(src == L"recycle:full", size, ic);
    } else if (src.rfind(L"win:", 0) == 0) {
        if (win) IconFromWindow(win, size, ic);
    } else if (!themed.empty() && IconFromFile(themed, size, ic)) {
        // the themed icon
    } else if (IconFromTheme(src, size, ic) || IconFromTheme(alt, size, ic)) {
        // a Store app's Catppuccin icon
    } else if (!IconFromShell(src, size, ic) && !IconFromShell(alt, size, ic) && win) {
        IconFromWindow(win, size, ic);
    }
    auto& slot = g_icons[key];
    slot = std::move(ic);
    if (slot.px.empty()) slot.retryAt = GetTickCount64() + 30000;
    return slot.px.empty() ? nullptr : &slot;
}

ID2D1Bitmap* IconBitmap(Surface& s, Icon* ic) {
    if (!ic || ic->px.empty()) return nullptr;
    if (ic->bmp && ic->gen == s.gen) return ic->bmp.Get();
    ic->bmp.Reset();
    s.rt->CreateBitmap(D2D1::SizeU(ic->w, ic->h), ic->px.data(), ic->w * 4,
                       D2D1::BitmapProperties(
                           D2D1::PixelFormat(DXGI_FORMAT_B8G8R8A8_UNORM, D2D1_ALPHA_MODE_PREMULTIPLIED), 96, 96),
                       ic->bmp.GetAddressOf());
    ic->gen = s.gen;
    return ic->bmp.Get();
}

// ---------------------------------------------------------------------------
// Open windows and dock items
// ---------------------------------------------------------------------------
struct WinMeta {
    std::wstring aumid, exe, mod;  // mod: the Windhawk mod's id, for windhawk-mod.exe windows
};
std::unordered_map<HWND, WinMeta> g_winMeta;
std::set<HWND> g_flash;

struct Item {
    std::wstring key, name, iconSrc, iconAlt;
    std::wstring launchKind, launchValue;  // lnk | aumid | exe
    int pin = -1;
    bool recycle = false;    // the Recycle Bin at the end of the dock
    std::vector<HWND> wins;  // stable order
    HWND top = nullptr;      // most recently used
    bool active = false, flash = false;
    float hoverT = 0, activeT = 0, openT = 0;
    ULONGLONG launchUntil = 0;
};
std::vector<Item> g_items;
int g_pinnedCount = 0;

HWND g_dock, g_pop, g_menu;

// ---------------------------------------------------------------------------
// Recycle Bin
// ---------------------------------------------------------------------------
bool g_recycleFull = false;
ULONG g_recycleNotify = 0;
constexpr UINT kRecycleMsg = WM_APP + 3;
const wchar_t kRecycleFolder[] = L"::{645FF040-5081-101B-9F08-00AA002F954E}";

bool RecycleHasFiles() {
    SHQUERYRBINFO q{sizeof(q)};
    return SUCCEEDED(SHQueryRecycleBinW(nullptr, &q)) && q.i64NumItems > 0;
}

// Asking the bin reads every drive's bin folder, and a sleeping disk or a network
// drive can hold that for seconds. So it runs on its own thread and posts the answer.
constexpr UINT kRecycleDone = WM_APP + 4;
volatile LONG g_recycleBusy = 0, g_recycleAgain = 0;
HANDLE g_recycleThread = nullptr;

DWORD WINAPI RecycleWorker(void*) {
    HRESULT hr = CoInitializeEx(nullptr, COINIT_MULTITHREADED);
    bool full = RecycleHasFiles();
    if (SUCCEEDED(hr)) CoUninitialize();
    HWND d = g_dock;
    InterlockedExchange(&g_recycleBusy, 0);
    if (d) PostMessageW(d, kRecycleDone, full ? 1 : 0, 0);
    return 0;
}

void CheckRecycleAsync() {
    if (InterlockedCompareExchange(&g_recycleBusy, 1, 0) != 0) {
        InterlockedExchange(&g_recycleAgain, 1);
        return;
    }
    if (g_recycleThread) CloseHandle(g_recycleThread);
    g_recycleThread = CreateThread(nullptr, 0, RecycleWorker, nullptr, 0, nullptr);
    if (!g_recycleThread) InterlockedExchange(&g_recycleBusy, 0);
}

void OpenRecycleBin() {
    ShellExecuteW(nullptr, L"open", L"explorer.exe", L"shell:RecycleBinFolder", nullptr, SW_SHOWNORMAL);
}

// Windows asks "Are you sure?" first, the same as on the desktop.
void EmptyRecycleBin() { SHEmptyRecycleBinW(g_dock, nullptr, 0); }

// The shell tells us when the bin changes; we only look at it then.
void WatchRecycle(bool on) {
    if (on && !g_recycleNotify && g_dock) {
        PIDLIST_ABSOLUTE pidl = nullptr;
        if (SUCCEEDED(SHGetKnownFolderIDList(FOLDERID_RecycleBinFolder, 0, nullptr, &pidl))) {
            SHChangeNotifyEntry e{pidl, TRUE};
            g_recycleNotify = SHChangeNotifyRegister(
                g_dock, SHCNRF_ShellLevel | SHCNRF_InterruptLevel | SHCNRF_NewDelivery,
                SHCNE_CREATE | SHCNE_DELETE | SHCNE_MKDIR | SHCNE_RMDIR | SHCNE_UPDATEDIR | SHCNE_UPDATEITEM |
                    SHCNE_RENAMEITEM | SHCNE_RENAMEFOLDER | SHCNE_UPDATEIMAGE,
                kRecycleMsg, 1, &e);
            CoTaskMemFree(pidl);
        }
    } else if (!on && g_recycleNotify) {
        SHChangeNotifyDeregister(g_recycleNotify);
        g_recycleNotify = 0;
    }
}

bool Eligible(HWND h) {
    if (!IsWindowVisible(h)) return false;
    DWORD pid = 0;
    GetWindowThreadProcessId(h, &pid);
    if (pid == GetCurrentProcessId()) return false;
    LONG_PTR ex = GetWindowLongPtrW(h, GWL_EXSTYLE);
    bool appWin = ex & WS_EX_APPWINDOW;
    if (!appWin) {
        if (ex & (WS_EX_TOOLWINDOW | WS_EX_NOACTIVATE)) return false;
        if (GetWindow(h, GW_OWNER)) return false;
    }
    int cloaked = 0;
    DwmGetWindowAttribute(h, DWMWA_CLOAKED, &cloaked, sizeof(cloaked));
    if (cloaked) return false;
    wchar_t cls[64];
    GetClassNameW(h, cls, ARRAYSIZE(cls));
    // "Ghost" is the stand-in Windows draws over a frozen app. The frozen window
    // itself stays in the list, so the app keeps its one icon, as on the taskbar.
    for (PCWSTR bad : {L"Progman", L"WorkerW", L"Shell_TrayWnd", L"Shell_SecondaryTrayWnd", L"Ghost"})
        if (!wcscmp(cls, bad)) return false;
    wchar_t t[2];
    if (!appWin && InternalGetWindowText(h, t, 2) == 0) return false;
    return true;
}

bool IsHostExe(const std::wstring& exeLower) {
    return exeLower.find(L"\\windowsapps\\") != std::wstring::npos ||
           FileName(exeLower) == L"applicationframehost.exe";
}

// The window's program sits inside the pinned program's own install folder. Steam's
// windows come from steamwebhelper.exe under Steam's folder and Windhawk's from
// UI\Windhawk.exe under Windhawk's, while their pins start steam.exe and windhawk.exe.
// Shared folders (Windows, Program Files itself) and Windhawk's mod host, which shows
// windows for every mod, never count.
bool InPinFolder(const std::wstring& pinExeLower, const std::wstring& exeLower) {
    size_t slash = pinExeLower.rfind(L'\\');
    if (slash == std::wstring::npos || exeLower.empty()) return false;
    std::wstring dir = pinExeLower.substr(0, slash + 1);
    if (std::count(dir.begin(), dir.end(), L'\\') < 3) return false;
    static std::wstring win;
    if (win.empty()) {
        wchar_t buf[MAX_PATH] = {};
        GetWindowsDirectoryW(buf, MAX_PATH);
        win = Lower(buf) + L"\\";
    }
    if (dir.rfind(win, 0) == 0) return false;
    // windhawk-mod.exe and windhawk-mod-elevated.exe
    if (FileName(exeLower).rfind(L"windhawk-mod", 0) == 0) return false;
    return exeLower.size() > dir.size() && exeLower.compare(0, dir.size(), dir) == 0;
}

bool PinMatches(const Pin& p, const WinMeta& m, const std::wstring& exeLower) {
    if (!p.aumid.empty() && !m.aumid.empty()) return _wcsicmp(p.aumid.c_str(), m.aumid.c_str()) == 0;
    if (!p.exeLower.empty() && p.exeLower == exeLower) return true;
    if (!p.procStart.empty() && FileName(exeLower) == p.procStart) return true;
    if (!p.exeLower.empty() && InPinFolder(p.exeLower, exeLower)) return true;
    return false;
}

void Relayout(bool forceBar = false);
void UpdateTitle(bool force = false);

BOOL CALLBACK CollectWin(HWND h, LPARAM lp) {
    if (Eligible(h)) ((std::vector<HWND>*)lp)->push_back(h);
    return TRUE;
}

// What the dock draws for its items. Equal means nothing on screen would change.
std::wstring ItemsSig(const std::vector<Item>& v) {
    std::wstring sig;
    for (auto& it : v) {
        sig += it.key + L'\x1f' + it.name + L'\x1f' + it.iconSrc + L'\x1f' + it.iconAlt;
        sig += it.active ? L'A' : L'a';
        sig += it.flash ? L'F' : L'f';
        for (HWND h : it.wins) sig += std::to_wstring((UINT_PTR)h) + L',';
        sig += L'\x1e';
    }
    return sig;
}

// Returns false when the items came out the same, so nothing is laid out or
// repainted. Windows show and hide all the time (tooltips, pop-ups) and most of
// those events change nothing the dock shows.
struct NameInfo {
    std::wstring name;
    bool knownId = false;
};
std::unordered_map<std::wstring, NameInfo> g_names;  // by item key; cleared on settings reload

bool Rebuild(bool force = false) {
    std::vector<HWND> zorder;
    EnumWindows(CollectWin, (LPARAM)&zorder);

    std::unordered_map<HWND, WinMeta> meta;
    std::unordered_map<DWORD, std::wstring> exeByPid, modByPid;
    for (HWND h : zorder) {
        auto it = g_winMeta.find(h);
        // An empty answer is looked up again: the window may have been too new to tell.
        if (it != g_winMeta.end() && (!it->second.aumid.empty() || !it->second.exe.empty())) {
            meta[h] = it->second;
            continue;
        }
        DWORD pid = 0;
        GetWindowThreadProcessId(h, &pid);
        auto e = exeByPid.find(pid);
        if (e == exeByPid.end()) e = exeByPid.emplace(pid, ExeOfPid(pid)).first;
        WinMeta wm{WindowAumid(h), e->second};
        if (IsModHost(Lower(wm.exe))) {
            auto md = modByPid.find(pid);
            if (md == modByPid.end()) md = modByPid.emplace(pid, ModIdOfPid(pid)).first;
            wm.mod = md->second;
        }
        meta[h] = wm;
    }
    g_winMeta = meta;

    std::vector<Item> items;
    for (size_t i = 0; i < g_pins.size(); i++) {
        Item it;
        it.pin = (int)i;
        it.key = L"pin:" + g_pins[i].kind + L":" + Lower(g_pins[i].value);
        it.name = g_pins[i].name;
        it.iconSrc = g_pins[i].iconSrc;
        it.launchKind = g_pins[i].kind;
        it.launchValue = g_pins[i].value;
        items.push_back(it);
    }
    g_pinnedCount = (int)items.size();

    HWND fg = GetForegroundWindow();
    HWND fgRoot = fg ? GetAncestor(fg, GA_ROOTOWNER) : nullptr;

    for (HWND h : zorder) {
        const WinMeta& m = meta[h];
        std::wstring exeLower = Lower(m.exe);
        int at = -1;
        for (int i = 0; i < g_pinnedCount && at < 0; i++)
            if (PinMatches(g_pins[i], m, exeLower)) at = i;
        if (at < 0) {
            // With neither an id nor a program, each window stands alone; an empty
            // "e:" would fold every unknown window into one icon.
            // Every mod's window comes from windhawk-mod.exe; each mod is an app of its own.
            bool modHost = m.aumid.empty() && IsModHost(exeLower);
            std::wstring key = !m.aumid.empty() ? L"a:" + Lower(m.aumid)
                               : modHost   ? (!m.mod.empty() ? L"m:" + Lower(m.mod)
                                                             : L"w:" + std::to_wstring((UINT_PTR)h))
                               : !exeLower.empty() ? L"e:" + exeLower
                                                   : L"w:" + std::to_wstring((UINT_PTR)h);
            for (int i = g_pinnedCount; i < (int)items.size() && at < 0; i++)
                if (items[i].key == key) at = i;
            if (at < 0) {
                if (!S.showOpen) continue;
                Item it;
                it.key = key;
                bool host = IsHostExe(exeLower);
                bool knownId = false;
                if (!m.aumid.empty()) it.iconSrc = L"shell:AppsFolder\\" + m.aumid;
                if (!host) it.iconAlt = m.exe;
                if (modHost) {
                    it.iconSrc = L"win:" + key;  // the mod's own window icon
                    it.iconAlt.clear();
                }
                // Asking the shell and reading the program's version info is slow, and
                // Rebuild runs on every window event. Look each app up once.
                auto nm = g_names.find(key);
                if (nm == g_names.end()) {
                    NameInfo ni;
                    if (modHost) ni.name = ModWindowName(m.mod, h);
                    if (!m.aumid.empty()) {
                        ni.name = ShellDisplayName(it.iconSrc);
                        ni.knownId = !ni.name.empty();
                    }
                    if (ni.name.empty() && !host && !modHost) ni.name = FileDescription(m.exe);
                    nm = g_names.emplace(key, ni).first;
                }
                it.name = nm->second.name;
                knownId = nm->second.knownId;
                if (it.name.empty()) it.name = WindowTitle(h);
                if (it.name.empty()) it.name = StripExt(FileName(m.exe));
                // An app the Start menu knows by its id starts (and pins) by that id,
                // not by a helper program such as Steam's steamwebhelper.exe.
                if (!m.aumid.empty() && (host || knownId)) {
                    it.launchKind = L"aumid";
                    it.launchValue = m.aumid;
                } else {
                    it.launchKind = L"exe";
                    it.launchValue = m.exe;
                }
                items.push_back(it);
                at = (int)items.size() - 1;
            }
        }
        Item& it = items[at];
        if (!it.top) it.top = h;
        it.wins.push_back(h);
        if (h == fgRoot) it.active = true;
        if (g_flash.count(h)) it.flash = true;
        if (it.iconSrc.empty() && it.iconAlt.empty() && it.pin < 0) it.iconAlt = m.exe;
    }

    if (S.recycle) {
        static std::wstring name;
        if (name.empty()) name = ShellDisplayName(kRecycleFolder);
        if (name.empty()) name = L"Recycle Bin";
        Item it;
        it.key = L"special:recycle";
        it.name = name;
        it.recycle = true;
        it.iconSrc = g_recycleFull ? L"recycle:full" : L"recycle:empty";
        items.push_back(it);
    }

    // Keep animation state and the order windows were first seen in.
    for (auto& it : items) {
        for (auto& old : g_items) {
            if (old.key != it.key) continue;
            it.hoverT = old.hoverT;
            it.activeT = old.activeT;
            it.openT = old.openT;
            it.launchUntil = it.wins.empty() ? old.launchUntil : 0;
            std::vector<HWND> ordered;
            for (HWND h : old.wins)
                if (std::find(it.wins.begin(), it.wins.end(), h) != it.wins.end()) ordered.push_back(h);
            for (HWND h : it.wins)
                if (std::find(ordered.begin(), ordered.end(), h) == ordered.end()) ordered.push_back(h);
            it.wins = ordered;
            break;
        }
    }
    for (auto it = g_flash.begin(); it != g_flash.end();)
        it = IsWindow(*it) ? std::next(it) : g_flash.erase(it);

    if (!force && items.size() == g_items.size() && ItemsSig(items) == ItemsSig(g_items)) {
        for (size_t i = 0; i < items.size(); i++) g_items[i].top = items[i].top;
        UpdateTitle();
        return false;
    }
    g_items = std::move(items);
    Relayout();
    UpdateTitle();
    return true;
}

// ---------------------------------------------------------------------------
// Layout
// ---------------------------------------------------------------------------
// L.w is the dock's length along its edge and L.h its depth. On a side edge the
// window turns: it is L.h wide and L.w tall.
struct Layout {
    float s = 1, plate = 48, icon = 36, gap = 6, padX = 10, padTop = 8, dotArea = 10, w = 100, h = 66;
    float radius = 16, plateR = 12, lift = 3;
    std::vector<float> x;     // where each item starts along the dock
    std::vector<float> divs;  // thin lines: separators, before the open apps and the Recycle Bin
    std::vector<int> divItem;  // the item each line comes before
    int iconPx = 36;
} L;

HMONITOR g_mon;
RECT g_monRect{}, g_barRect{}, g_tbRect{};
UINT g_edge = ABE_BOTTOM;  // the screen edge the dock sits on
int g_tbEdge = -1;         // the taskbar's edge, -1 when there is none
int g_outerWant = 0;       // the line the dock stands on: its screen edge, or the taskbar's inner side
bool g_tbSolidSeen = false;
bool g_appbar = false, g_fullscreen = false;
int g_dragIndex = -1;
float g_dragX = 0, g_dragGrab = 0;

constexpr UINT kAppBarMsg = WM_APP + 2, kReloadMsg = WM_APP + 1;
UINT g_shellMsg, g_taskbarCreatedMsg, g_ctlMsg;

// Appbar calls are sent to Explorer and wait for it. A stuck shell would freeze the
// dock with it, so ask first whether it answers at all.
bool ShellResponds() {
    HWND tray = FindWindowW(L"Shell_TrayWnd", nullptr);
    if (!tray) return false;
    DWORD_PTR r = 0;
    return SendMessageTimeoutW(tray, WM_NULL, 0, 0, SMTO_ABORTIFHUNG | SMTO_BLOCK, 300, &r) != 0;
}

bool Vertical() { return g_edge == ABE_LEFT || g_edge == ABE_RIGHT; }

// Along and depth to window points. Depth 0 is the dock's inner side, toward the
// middle of the screen. It grows toward the screen edge, where the open dots sit;
// a pointed-at icon lifts the other way.
D2D1_RECT_F Place(float a0, float d0, float a1, float d1) {
    float T = L.h;
    switch (g_edge) {
        case ABE_TOP:
            return D2D1::RectF(a0, T - d1, a1, T - d0);
        case ABE_RIGHT:
            return D2D1::RectF(d0, a0, d1, a1);
        case ABE_LEFT:
            return D2D1::RectF(T - d1, a0, T - d0, a1);
    }
    return D2D1::RectF(a0, d0, a1, d1);
}

D2D1_POINT_2F PlacePt(float a, float d) {
    D2D1_RECT_F r = Place(a, d, a, d);
    return D2D1::Point2F(r.left, r.top);
}

void Unplace(POINT px, float& a, float& d) {
    float x = px.x / L.s, y = px.y / L.s, T = L.h;
    switch (g_edge) {
        case ABE_TOP:
            a = x, d = T - y;
            return;
        case ABE_RIGHT:
            a = y, d = x;
            return;
        case ABE_LEFT:
            a = y, d = T - x;
            return;
    }
    a = x, d = y;
}

float WinW() { return Vertical() ? L.h : L.w; }
float WinH() { return Vertical() ? L.w : L.h; }

// Which edge the taskbar is on, from where its window sits. `solid` is false when
// it hides itself, so nothing needs to make room for it.
int TaskbarEdge(RECT& r, bool& solid) {
    solid = false;
    HWND tray = FindWindowW(L"Shell_TrayWnd", nullptr);
    if (!tray || !GetWindowRect(tray, &r)) return -1;
    APPBARDATA abd{sizeof(abd)};
    bool autoHide = ShellResponds() ? (SHAppBarMessage(ABM_GETSTATE, &abd) & ABS_AUTOHIDE) != 0 : !g_tbSolidSeen;
    int w = r.right - r.left, h = r.bottom - r.top;
    solid = IsWindowVisible(tray) && !autoHide && std::min(w, h) > 4;
    int cx = (r.left + r.right) / 2, cy = (r.top + r.bottom) / 2;
    int mx = (g_monRect.left + g_monRect.right) / 2, my = (g_monRect.top + g_monRect.bottom) / 2;
    if (w >= h) return cy < my ? ABE_TOP : ABE_BOTTOM;
    return cx < mx ? ABE_LEFT : ABE_RIGHT;
}

UINT ChosenEdge() {
    switch (S.place) {
        case 1:
            return ABE_BOTTOM;
        case 2:
            return ABE_TOP;
        case 3:
            return ABE_LEFT;
        case 4:
            return ABE_RIGHT;
    }
    switch (g_tbEdge) {
        case ABE_BOTTOM:
            return ABE_TOP;
        case ABE_LEFT:
            return ABE_RIGHT;
        case ABE_RIGHT:
            return ABE_LEFT;
    }
    return ABE_BOTTOM;
}

// Where a line may sit before item i: 1 after a pinned app (a separator you add),
// 2 before the open apps, 3 before the Recycle Bin, 0 nowhere.
int SlotKind(int i) {
    if (i <= 0 || i >= (int)g_items.size()) return 0;
    if (g_items[i].recycle) return 3;
    if (i == g_pinnedCount) return 2;
    if (i < g_pinnedCount) return 1;
    return 0;
}

bool SlotOn(int i) {
    switch (SlotKind(i)) {
        case 1: {
            int p = g_items[i - 1].pin;
            return p >= 0 && p < (int)g_pins.size() && g_pins[p].sepAfter;
        }
        case 2:
            return S.lineOpen;
        case 3:
            return S.lineBin;
    }
    return false;
}

void ComputeLayout(float maxLen) {
    L.s = MonitorDpi(g_mon) / 96.f;
    float k = 1;
    for (int pass = 0; pass < 2; pass++) {
        L.icon = S.iconSize * k;
        L.plate = L.icon + 12 * k;
        L.gap = S.spacing * k;
        L.padX = 10;
        L.padTop = 8;
        L.dotArea = 10;
        L.plateR = std::min(12.f, L.plate / 4);
        L.lift = (float)S.iconLift;
        L.x.assign(g_items.size(), 0);
        L.divs.clear();
        L.divItem.clear();
        float x = L.padX;
        for (size_t i = 0; i < g_items.size(); i++) {
            if (i > 0) x += L.gap;
            if (SlotOn((int)i)) {
                // The same room on both sides: gap, pad, the line, pad, gap.
                float dp = std::max(4.f, L.gap);
                L.divs.push_back(x + dp);
                L.divItem.push_back((int)i);
                x += dp * 2 + 1 + L.gap;
            }
            L.x[i] = x;
            x += L.plate;
        }
        if (g_items.empty()) x += L.plate;
        L.w = x + L.padX;
        L.h = L.padTop + L.plate + L.dotArea;
        if (L.w * L.s <= maxLen || pass == 1) break;
        k = std::max(0.4f, maxLen / (L.w * L.s));
    }
    L.iconPx = std::max(16, (int)std::lround(L.icon * L.s));
    L.radius = (float)LiveRadius();
}

void AppBarSetPos(int depthPx, bool force = false);

int ReservePx() {
    int gapPx = (int)std::lround(S.bottomGap * L.s);
    // Reserve up to the dock's inner side only. The window manager adds its own
    // gap past that, so tiled windows sit as far from the dock as from every
    // other screen edge.
    return (int)std::ceil(L.h * L.s) + gapPx;
}

Surface g_dockSurf, g_popSurf, g_menuSurf;
void HidePopup();
void CloseMenu();

void RelayoutOnce(bool forceBar);

// SetWindowPos and the appbar calls inside a relayout can send messages that ask
// for another one. Run those after this one ends, not inside it.
void Relayout(bool forceBar) {
    static bool busy = false, again = false, againForce = false;
    if (busy) {
        again = true;
        againForce |= forceBar;
        return;
    }
    busy = true;
    RelayoutOnce(forceBar);
    for (int n = 0; again && n < 3; n++) {
        bool f = againForce;
        again = againForce = false;
        RelayoutOnce(f);
    }
    again = againForce = false;
    busy = false;
}

void RelayoutOnce(bool forceBar) {
    if (!g_dock) return;
    HMONITOR mon = MonitorFromPoint(POINT{0, 0}, MONITOR_DEFAULTTOPRIMARY);
    MONITORINFO mi{sizeof(mi)};
    if (!mon || !GetMonitorInfoW(mon, &mi)) return;
    g_mon = mon;
    g_monRect = mi.rcMonitor;
    bool tbSolid = false;
    g_tbEdge = TaskbarEdge(g_tbRect, tbSolid);
    g_tbSolidSeen = tbSolid;
    UINT edge = ChosenEdge();
    if (edge != g_edge) {
        g_edge = edge;
        forceBar = true;
        HidePopup();
        CloseMenu();
    }
    bool share = tbSolid && g_tbEdge == (int)g_edge;

    // A taskbar on a side edge takes its end of the dock's run.
    RECT span = g_monRect;
    if (tbSolid && !share) {
        if (!Vertical() && g_tbEdge == ABE_LEFT) span.left = std::max(span.left, g_tbRect.right);
        if (!Vertical() && g_tbEdge == ABE_RIGHT) span.right = std::min(span.right, g_tbRect.left);
        if (Vertical() && g_tbEdge == ABE_TOP) span.top = std::max(span.top, g_tbRect.bottom);
        if (Vertical() && g_tbEdge == ABE_BOTTOM) span.bottom = std::min(span.bottom, g_tbRect.top);
    }
    ComputeLayout((float)(Vertical() ? span.bottom - span.top : span.right - span.left) - 32);
    int W = (int)std::ceil(WinW() * L.s), H = (int)std::ceil(WinH() * L.s);

    // Sharing an edge with the taskbar, the dock stands just inside it.
    int outer = g_edge == ABE_TOP     ? (int)g_monRect.top
                : g_edge == ABE_LEFT  ? (int)g_monRect.left
                : g_edge == ABE_RIGHT ? (int)g_monRect.right
                                      : (int)g_monRect.bottom;
    if (share) {
        if (g_edge == ABE_TOP) outer = std::max(outer, (int)g_tbRect.bottom);
        if (g_edge == ABE_LEFT) outer = std::max(outer, (int)g_tbRect.right);
        if (g_edge == ABE_RIGHT) outer = std::min(outer, (int)g_tbRect.left);
        if (g_edge == ABE_BOTTOM) outer = std::min(outer, (int)g_tbRect.top);
    }
    g_outerWant = outer;
    if (S.reserve) {
        AppBarSetPos(ReservePx(), forceBar);
        if (g_appbar) {
            if (g_edge == ABE_TOP) outer = std::max(outer, (int)g_barRect.top);
            if (g_edge == ABE_LEFT) outer = std::max(outer, (int)g_barRect.left);
            if (g_edge == ABE_RIGHT) outer = std::min(outer, (int)g_barRect.right);
            if (g_edge == ABE_BOTTOM) outer = std::min(outer, (int)g_barRect.bottom);
        }
    }
    int gapPx = (int)std::lround(S.bottomGap * L.s);
    int x, y;
    if (Vertical()) {
        y = span.top + (span.bottom - span.top - H) / 2;
        x = g_edge == ABE_LEFT ? outer + gapPx : outer - gapPx - W;
    } else {
        x = span.left + (span.right - span.left - W) / 2;
        y = g_edge == ABE_TOP ? outer + gapPx : outer - gapPx - H;
    }
    bool show = !g_fullscreen;
    SetWindowPos(g_dock, HWND_TOPMOST, x, y, W, H, SWP_NOACTIVATE | (show ? SWP_SHOWWINDOW : SWP_HIDEWINDOW));
    g_dockSurf.Resize();
    InvalidateRect(g_dock, nullptr, FALSE);
}

// ---------------------------------------------------------------------------
// Appbar: maximized windows stop at the dock
// ---------------------------------------------------------------------------
// Only talk to the shell when the reserved strip really changed. Every SETPOS
// tells the other bars to move, and their answer comes back as ABN_POSCHANGED.
int g_barHeightSent = -1, g_barOuterSent = 0;
UINT g_barEdgeSent = ABE_BOTTOM;
RECT g_barMonSent{};
bool g_inBarSetPos = false;

// The taskbar our reserved strip was registered with. A TaskbarCreated
// broadcast only means Explorer restarted when this changed.
HWND g_appbarTray = nullptr;
DWORD g_appbarTrayPid = 0;

void CurrentTray(HWND* tray, DWORD* pid) {
    *tray = FindWindowW(L"Shell_TrayWnd", nullptr);
    *pid = 0;
    if (*tray) GetWindowThreadProcessId(*tray, pid);
}

void AppBarRegister() {
    if (g_appbar || !g_dock || !ShellResponds()) return;
    APPBARDATA abd{sizeof(abd)};
    abd.hWnd = g_dock;
    abd.uCallbackMessage = kAppBarMsg;
    g_appbar = SHAppBarMessage(ABM_NEW, &abd) != 0;
    if (!g_appbar) {
        // The shell may still hold us from before a restart: let go and ask once more.
        SHAppBarMessage(ABM_REMOVE, &abd);
        g_appbar = SHAppBarMessage(ABM_NEW, &abd) != 0;
    }
    if (g_appbar) CurrentTray(&g_appbarTray, &g_appbarTrayPid);
}

void AppBarRemove() {
    if (!g_appbar) return;
    APPBARDATA abd{sizeof(abd)};
    abd.hWnd = g_dock;
    if (ShellResponds()) SHAppBarMessage(ABM_REMOVE, &abd);
    g_appbar = false;
    g_barHeightSent = -1;
}

// Keep the strip depthPx deep from its outer side, whatever the shell moved.
void ShapeStrip(RECT& rc, int depthPx) {
    if (g_edge == ABE_TOP) rc.bottom = rc.top + depthPx;
    else if (g_edge == ABE_LEFT) rc.right = rc.left + depthPx;
    else if (g_edge == ABE_RIGHT) rc.left = rc.right - depthPx;
    else rc.top = rc.bottom - depthPx;
}

void AppBarSetPos(int depthPx, bool force) {
    AppBarRegister();
    if (!g_appbar || g_inBarSetPos) return;
    bool same = depthPx == g_barHeightSent && g_edge == g_barEdgeSent && g_outerWant == g_barOuterSent &&
                EqualRect(&g_barMonSent, &g_monRect);
    if (!force && same) return;
    if (!ShellResponds()) return;  // the heal tries again once the shell answers
    g_inBarSetPos = true;
    APPBARDATA abd{sizeof(abd)};
    abd.hWnd = g_dock;
    abd.uEdge = g_edge;
    abd.rc = g_monRect;
    if (g_edge == ABE_TOP) abd.rc.top = g_outerWant;
    else if (g_edge == ABE_LEFT) abd.rc.left = g_outerWant;
    else if (g_edge == ABE_RIGHT) abd.rc.right = g_outerWant;
    else abd.rc.bottom = g_outerWant;
    ShapeStrip(abd.rc, depthPx);
    SHAppBarMessage(ABM_QUERYPOS, &abd);
    ShapeStrip(abd.rc, depthPx);
    if (force && same && EqualRect(&abd.rc, &g_barRect)) {
        // Another bar moved but our strip is still right: say nothing, or we echo forever.
        g_inBarSetPos = false;
        return;
    }
    SHAppBarMessage(ABM_SETPOS, &abd);
    g_barRect = abd.rc;
    g_barHeightSent = depthPx;
    g_barEdgeSent = g_edge;
    g_barOuterSent = g_outerWant;
    g_barMonSent = g_monRect;
    g_inBarSetPos = false;
}

// ---------------------------------------------------------------------------
// Actions
// ---------------------------------------------------------------------------
void Activate(HWND h) {
    if (IsIconic(h)) ShowWindowAsync(h, SW_RESTORE);
    if (!SetForegroundWindow(h)) SwitchToThisWindow(h, TRUE);
}

void Minimize(HWND h) { PostMessageW(h, WM_SYSCOMMAND, SC_MINIMIZE, 0); }

void CloseWin(HWND h) { PostMessageW(h, WM_SYSCOMMAND, SC_CLOSE, 0); }

void StartAnim();

void Launch(Item& it) {
    std::wstring file = it.launchKind == L"aumid" ? L"shell:AppsFolder\\" + it.launchValue : it.launchValue;
    if (file.empty()) return;
    SHELLEXECUTEINFOW sei{sizeof(sei)};
    sei.fMask = SEE_MASK_FLAG_NO_UI;
    sei.lpVerb = L"open";
    sei.lpFile = file.c_str();
    sei.nShow = SW_SHOWNORMAL;
    if (ShellExecuteExW(&sei)) {
        it.launchUntil = GetTickCount64() + 4000;
        StartAnim();
    }
}

void ClickItem(int i, bool middle) {
    if (i < 0 || i >= (int)g_items.size()) return;
    Item& it = g_items[i];
    if (it.recycle) {
        OpenRecycleBin();
        return;
    }
    if (middle || it.wins.empty()) {
        Launch(it);
        return;
    }
    HWND fg = GetForegroundWindow();
    HWND fgRoot = fg ? GetAncestor(fg, GA_ROOTOWNER) : nullptr;
    auto pos = std::find(it.wins.begin(), it.wins.end(), fgRoot);
    if (it.wins.size() == 1) {
        if (pos != it.wins.end() && !IsIconic(fgRoot))
            Minimize(fgRoot);
        else
            Activate(it.wins[0]);
        return;
    }
    if (pos != it.wins.end())
        Activate(it.wins[(pos - it.wins.begin() + 1) % it.wins.size()]);
    else
        Activate(it.top ? it.top : it.wins[0]);
}

void PinItem(const std::wstring& key) {
    for (auto& it : g_items) {
        if (it.key != key || it.pin >= 0 || it.launchValue.empty()) continue;
        Pin p;
        p.kind = it.launchKind;
        p.value = it.launchValue;
        ResolvePin(p);
        g_pins.push_back(p);
        SavePins();
        Rebuild(true);
        return;
    }
}

void UnpinItem(const std::wstring& key) {
    for (auto& it : g_items) {
        if (it.key != key || it.pin < 0) continue;
        g_pins.erase(g_pins.begin() + it.pin);
        SavePins();
        Rebuild(true);
        return;
    }
}

int FindItem(const std::wstring& key) {
    for (size_t i = 0; i < g_items.size(); i++)
        if (g_items[i].key == key) return (int)i;
    return -1;
}

// ---------------------------------------------------------------------------
// Hover state and animation
// ---------------------------------------------------------------------------
int g_hover = -1, g_press = -1;
bool g_pressMiddle = false;
POINT g_pressPt{};
float g_dockT = 0;
ULONGLONG g_lastAnim = 0, g_outSince = 0;
std::wstring g_popKey;  // item the preview shows

constexpr UINT_PTR kTimerRebuild = 1, kTimerAnim = 2, kTimerHover = 3, kTimerTrack = 4, kTimerFull = 5,
                   kTimerRecycle = 6, kTimerTitle = 7;
ULONGLONG g_recycleChecked = 0;
bool g_rebuildPending = false;

void ScheduleRebuild(UINT ms) {
    if (g_rebuildPending || !g_dock) return;
    g_rebuildPending = true;
    SetTimer(g_dock, kTimerRebuild, ms, nullptr);
}

bool PopupVisible() { return g_pop && IsWindowVisible(g_pop); }
bool MenuOpen() { return g_menu && IsWindowVisible(g_menu); }

void StartAnim() {
    g_lastAnim = GetTickCount64();
    SetTimer(g_dock, kTimerAnim, 15, nullptr);
}

bool StepAnim() {
    ULONGLONG now = GetTickCount64();
    float dt = (float)(now - g_lastAnim);
    g_lastAnim = now;
    float step = S.fadeMs ? dt / S.fadeMs : 1.f;
    bool busy = false;
    auto move = [&](float& v, float target) {
        if (v < target) v = std::min(target, v + step);
        else if (v > target) v = std::max(target, v - step);
        if (v != target) busy = true;
    };
    bool inside = g_hover >= 0 || PopupVisible() || MenuOpen();
    move(g_dockT, inside ? 1.f : 0.f);
    for (size_t i = 0; i < g_items.size(); i++) {
        Item& it = g_items[i];
        bool hot = (int)i == g_hover || (PopupVisible() && it.key == g_popKey) || (int)i == g_dragIndex;
        move(it.hoverT, hot ? 1.f : 0.f);
        move(it.activeT, it.active ? 1.f : 0.f);
        move(it.openT, it.wins.empty() ? 0.f : 1.f);
        if (it.launchUntil > now) busy = true;
    }
    return busy;
}

// ---------------------------------------------------------------------------
// Dock painting
// ---------------------------------------------------------------------------
float PlateAlong(int i) { return i == g_dragIndex ? g_dragX - g_dragGrab : L.x[i]; }

D2D1_RECT_F PlateRect(int i) {
    float a = PlateAlong(i);
    float d = L.padTop - L.lift * g_items[i].hoverT;
    return Place(a, d, a + L.plate, d + L.plate);
}

void PaintDock() {
    Surface& s = g_dockSurf;
    if (!s.Ensure()) return;
    s.rt->BeginDraw();
    s.rt->Clear(D2D1::ColorF(0, 0));
    D2D1_RECT_F all = D2D1::RectF(0, 0, WinW(), WinH());
    auto tint = s.Solid(kBase, TintAlpha());
    s.rt->FillRectangle(all, tint.Get());

    float ew = (float)S.edgeWidth;
    if (ew > 0) {
        if (g_dockT < 1) StrokeRound(s, all, L.radius, ew, s.Solid(S.edge, 1 - g_dockT).Get());
        if (g_dockT > 0) StrokeRound(s, all, L.radius, ew, s.Grad(all, g_dockT).Get());
    }

    for (float dv : L.divs) {
        float h = L.plate * 0.6f;
        float cd = L.padTop + L.plate / 2;
        s.rt->FillRectangle(Place(dv, cd - h / 2, dv + 1, cd + h / 2), s.Solid(kSurface1).Get());
    }

    ULONGLONG now = GetTickCount64();
    auto drawItem = [&](int i) {
        Item& it = g_items[i];
        D2D1_RECT_F r = PlateRect(i);
        float fillA = Lerp(0.72f, 0.86f, std::max(it.hoverT, it.activeT));
        UINT fill = it.activeT > 0.5f || it.hoverT > 0.5f ? kSurface1 : kSurface0;
        s.rt->FillRoundedRectangle(D2D1::RoundedRect(r, L.plateR, L.plateR), s.Solid(fill, fillA).Get());
        // Open apps carry the gradient outline the top bar's app buttons have; a pinned app
        // that is not open sits on a quiet grey edge until you point at it.
        float gradA = std::max(it.openT, it.hoverT);
        if (gradA < 1) StrokeRound(s, r, L.plateR, 2, s.Solid(kSurface1, 1 - gradA).Get());
        if (gradA > 0) StrokeRound(s, r, L.plateR, 2, s.Grad(r, gradA).Get());

        Icon* ic = GetIcon(it.iconSrc, it.iconAlt, it.top, L.iconPx);
        float cx = (r.left + r.right) / 2, cy = (r.top + r.bottom) / 2;
        D2D1_RECT_F ir = D2D1::RectF(cx - L.icon / 2, cy - L.icon / 2, cx + L.icon / 2, cy + L.icon / 2);
        if (ID2D1Bitmap* b = IconBitmap(s, ic)) {
            s.rt->DrawBitmap(b, ir, 1.f, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, ic->src);
        } else {
            std::wstring letter = it.name.empty() ? L"?" : it.name.substr(0, 1);
            auto* f = Format(L.icon * 0.55f, DWRITE_FONT_WEIGHT_SEMI_BOLD);
            if (f) f->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
            DrawText(s, letter, f, ir, kText);
            if (f) f->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_LEADING);
        }

        // The open dots sit between the icon and the screen edge.
        float dotD = L.padTop + L.plate + L.dotArea / 2;
        D2D1_POINT_2F dot = PlacePt(PlateAlong(i) + L.plate / 2, dotD);
        if (it.launchUntil > now && it.wins.empty()) {
            float a = 0.35f + 0.65f * (0.5f + 0.5f * std::sin((float)(now % 100000) / 140.f));
            s.rt->FillEllipse(D2D1::Ellipse(dot, 2, 2), s.Solid(S.from, a).Get());
        } else if (!it.wins.empty()) {
            if (it.flash) {
                s.rt->FillEllipse(D2D1::Ellipse(dot, 2.5f, 2.5f), s.Solid(kPeach).Get());
            } else {
                float half = Lerp(2, 7, it.activeT);
                float da = PlateAlong(i) + L.plate / 2;
                D2D1_RECT_F d = Place(da - half, dotD - 2, da + half, dotD + 2);
                if (it.activeT > 0.01f)
                    s.rt->FillRoundedRectangle(D2D1::RoundedRect(d, 2, 2), s.Grad(d, 1).Get());
                else
                    s.rt->FillEllipse(D2D1::Ellipse(dot, 2, 2), s.Solid(S.from).Get());
            }
        }
    };
    for (int i = 0; i < (int)g_items.size(); i++)
        if (i != g_dragIndex) drawItem(i);
    if (g_dragIndex >= 0 && g_dragIndex < (int)g_items.size()) drawItem(g_dragIndex);

    if (s.rt->EndDraw() == D2DERR_RECREATE_TARGET) {
        s.Discard();
        InvalidateRect(s.hwnd, nullptr, FALSE);
    }
}

int ItemAt(POINT pxPt) {
    float a, d;
    Unplace(pxPt, a, d);
    if (d < 0 || d > L.h) return -1;
    for (size_t i = 0; i < g_items.size(); i++) {
        float l = L.x[i] - L.gap / 2, r = L.x[i] + L.plate + L.gap / 2;
        if (a >= l && a < r) return (int)i;
    }
    return -1;
}

// The line under the point, as an index into L.divs: the room between the two icons.
int DivAt(POINT pxPt) {
    float a, d;
    Unplace(pxPt, a, d);
    if (d < 0 || d > L.h) return -1;
    for (size_t k = 0; k < L.divs.size() && k < L.divItem.size(); k++) {
        int i = L.divItem[k];
        if (i <= 0 || i >= (int)L.x.size()) continue;
        float l = L.x[i - 1] + L.plate + L.gap / 2, r = L.x[i] - L.gap / 2;
        if (a >= l && a < r) return (int)k;
    }
    return -1;
}

// Where a W x H window beside the dock goes: on the screen side of the dock,
// centred on the item at `along` (dock points), kept on the monitor.
POINT BesideDock(float along, int W, int H) {
    RECT dr;
    GetWindowRect(g_dock, &dr);
    int c = (int)std::lround(along * L.s), gap = (int)std::lround(8 * L.s);
    RECT m = g_monRect;
    POINT p{};
    if (Vertical()) {
        p.y = std::clamp((int)dr.top + c - H / 2, (int)m.top + 8, std::max((int)m.top + 8, (int)m.bottom - H - 8));
        p.x = g_edge == ABE_LEFT ? dr.right + gap : dr.left - gap - W;
    } else {
        p.x = std::clamp((int)dr.left + c - W / 2, (int)m.left + 8, std::max((int)m.left + 8, (int)m.right - W - 8));
        p.y = g_edge == ABE_TOP ? dr.bottom + gap : dr.top - gap - H;
    }
    return p;
}

// ---------------------------------------------------------------------------
// Preview popup
// ---------------------------------------------------------------------------
struct Thumb {
    HWND src = nullptr;
    HTHUMBNAIL th = nullptr;
    D2D1_RECT_F box{}, img{}, close{};
    std::wstring title;
};
struct Pop {
    std::vector<Thumb> thumbs;
    std::wstring name;
    float w = 0, h = 0, s = 1;
    int hot = -1;
    bool hotClose = false;
} P;

void UnregisterThumbs() {
    for (auto& t : P.thumbs)
        if (t.th) DwmUnregisterThumbnail(t.th);
    P.thumbs.clear();
}

void HidePopup() {
    UnregisterThumbs();
    if (g_pop) ShowWindow(g_pop, SW_HIDE);
    g_popKey.clear();
    StartAnim();
}

void ShowPopup(int i) {
    if (!g_pop || i < 0 || i >= (int)g_items.size() || MenuOpen() || g_dragIndex >= 0) return;
    Item& it = g_items[i];
    UnregisterThumbs();
    g_popKey = it.key;
    P.name = it.name;
    P.hot = -1;
    P.s = L.s;
    const float pad = 10;
    if (it.wins.empty() || !S.previews) {
        auto* f = Format(12, DWRITE_FONT_WEIGHT_MEDIUM);
        P.w = std::ceil(TextWidth(P.name, f)) + 24;
        P.h = 28;
    } else {
        size_t n = std::min<size_t>(it.wins.size(), 8);
        float bw = (float)S.previewW, imgH = std::round(bw * 118.f / 208.f), titleH = 26, gap = 8;
        float maxW = (g_monRect.right - g_monRect.left) / L.s - 32 - (Vertical() ? WinW() + 16 : 0);
        float need = pad * 2 + n * bw + (n - 1) * gap;
        if (need > maxW) bw = std::max(120.f, (maxW - pad * 2 - (n - 1) * gap) / n);
        P.w = pad * 2 + n * bw + (n - 1) * gap;
        P.h = pad + 24 + imgH + titleH + pad;
        for (size_t k = 0; k < n; k++) {
            Thumb t;
            t.src = it.wins[k];
            t.title = WindowTitle(t.src);
            float x = pad + k * (bw + gap);
            t.box = D2D1::RectF(x, pad + 24, x + bw, pad + 24 + imgH + titleH);
            t.img = D2D1::RectF(x + 6, t.box.top + 6, x + bw - 6, t.box.top + imgH);
            t.close = D2D1::RectF(x + bw - 26, t.box.bottom - titleH, x + bw - 4, t.box.bottom - 2);
            P.thumbs.push_back(t);
        }
    }
    int W = (int)std::ceil(P.w * L.s), H = (int)std::ceil(P.h * L.s);
    POINT at = BesideDock(L.x[i] + L.plate / 2, W, H);
    SetWindowPos(g_pop, HWND_TOPMOST, at.x, at.y, W, H, SWP_NOACTIVATE | SWP_SHOWWINDOW);
    ApplyBackdrop(g_pop);
    g_popSurf.Resize();
    for (auto& t : P.thumbs) {
        if (FAILED(DwmRegisterThumbnail(g_pop, t.src, &t.th))) {
            t.th = nullptr;
            continue;
        }
        SIZE src{};
        DwmQueryThumbnailSourceSize(t.th, &src);
        float bw = t.img.right - t.img.left, bh = t.img.bottom - t.img.top;
        float k = (src.cx > 0 && src.cy > 0) ? std::min(bw * L.s / src.cx, bh * L.s / src.cy) : 0;
        int tw = (int)(src.cx * k), th = (int)(src.cy * k);
        int ix = (int)std::lround(t.img.left * L.s) + ((int)std::lround(bw * L.s) - tw) / 2;
        int iy = (int)std::lround(t.img.top * L.s) + ((int)std::lround(bh * L.s) - th) / 2;
        DWM_THUMBNAIL_PROPERTIES tp{};
        tp.dwFlags = DWM_TNP_RECTDESTINATION | DWM_TNP_VISIBLE | DWM_TNP_OPACITY | DWM_TNP_SOURCECLIENTAREAONLY;
        tp.rcDestination = RECT{ix, iy, ix + tw, iy + th};
        tp.fVisible = TRUE;
        tp.opacity = 255;
        tp.fSourceClientAreaOnly = FALSE;
        DwmUpdateThumbnailProperties(t.th, &tp);
    }
    InvalidateRect(g_pop, nullptr, FALSE);
    StartAnim();
}

void PaintPopup() {
    Surface& s = g_popSurf;
    if (!s.Ensure()) return;
    s.rt->BeginDraw();
    s.rt->Clear(D2D1::ColorF(0, 0));
    D2D1_RECT_F all = D2D1::RectF(0, 0, P.w, P.h);
    s.rt->FillRectangle(all, s.Solid(kBase, TintAlpha()).Get());
    if (S.edgeWidth > 0) StrokeRound(s, all, L.radius, (float)S.edgeWidth, s.Grad(all, 1).Get());
    if (P.thumbs.empty()) {
        auto* f = Format(12, DWRITE_FONT_WEIGHT_MEDIUM);
        DrawText(s, P.name, f, D2D1::RectF(12, 0, P.w - 10, P.h), kText);
    } else {
        auto* hf = Format(13, DWRITE_FONT_WEIGHT_SEMI_BOLD);
        DrawText(s, P.name, hf, D2D1::RectF(14, 8, P.w - 14, 32), kText);
        auto* tf = Format(12, DWRITE_FONT_WEIGHT_NORMAL);
        auto* gf = Format(10, DWRITE_FONT_WEIGHT_NORMAL, true);
        HWND fg = GetForegroundWindow();
        HWND fgRoot = fg ? GetAncestor(fg, GA_ROOTOWNER) : nullptr;
        for (size_t k = 0; k < P.thumbs.size(); k++) {
            Thumb& t = P.thumbs[k];
            bool hot = (int)k == P.hot;
            if (hot || t.src == fgRoot)
                s.rt->FillRoundedRectangle(D2D1::RoundedRect(t.box, 10, 10),
                                           s.Solid(kSurface0, hot ? 0.75f : 0.4f).Get());
            if (hot) StrokeRound(s, t.box, 10, 2, s.Grad(t.box, 1).Get());
            if (!t.th) DrawText(s, L"No preview", tf, t.img, kOverlay);
            D2D1_RECT_F tr = D2D1::RectF(t.box.left + 8, t.close.top, t.close.left - 2, t.close.bottom);
            DrawText(s, t.title, tf, tr, hot ? kText : kSubtext);
            if (hot) {
                if (P.hotClose)
                    s.rt->FillRoundedRectangle(D2D1::RoundedRect(t.close, 6, 6), s.Solid(kRed, 0.85f).Get());
                DrawText(s, L"\xE8BB", gf, t.close, P.hotClose ? 0x11111B : kText);
            }
        }
    }
    if (s.rt->EndDraw() == D2DERR_RECREATE_TARGET) {
        s.Discard();
        InvalidateRect(s.hwnd, nullptr, FALSE);
    }
}

// ---------------------------------------------------------------------------
// Right-click menu
// ---------------------------------------------------------------------------
struct MenuRow {
    std::wstring text, glyph;
    bool sep = false, header = false;
    std::function<void()> run;
    float top = 0, bottom = 0;
};
struct Menu {
    std::vector<MenuRow> rows;
    float w = 220, h = 100;
    int hot = -1;
    std::wstring key;
} M;

HWND g_menuFgAtOpen = nullptr;

void CloseMenu() {
    if (g_menu && IsWindowVisible(g_menu)) ShowWindow(g_menu, SW_HIDE);
    M.rows.clear();
    M.hot = -1;
    StartAnim();
}

void ShowMenu(float along) {
    auto* f = Format(14, DWRITE_FONT_WEIGHT_MEDIUM);
    float textW = 0;
    for (auto& r : M.rows)
        if (!r.sep) textW = std::max(textW, TextWidth(r.text, f));
    M.w = std::clamp(textW + 6 + 10 + 28 + 18 + 6, 200.f, 420.f);
    float y = 6;
    for (auto& r : M.rows) {
        r.top = y;
        y += r.sep ? 9 : 30;
        r.bottom = y;
    }
    M.h = y + 6;

    float s = L.s;
    int W = (int)std::ceil(M.w * s), H = (int)std::ceil(M.h * s);
    POINT at = BesideDock(along, W, H);
    SetWindowPos(g_menu, HWND_TOPMOST, at.x, at.y, W, H, SWP_SHOWWINDOW);
    ApplyBackdrop(g_menu);
    g_menuSurf.Resize();
    SetForegroundWindow(g_menu);
    // When Windows refuses the focus, the menu never hears that it lost it. The
    // dock's 1 s tick closes it once something else comes to the front.
    g_menuFgAtOpen = GetForegroundWindow();
    InvalidateRect(g_menu, nullptr, FALSE);
    StartAnim();
}

// ---------------------------------------------------------------------------
// Changing the dock on the go, from its own menu or from the taskbar's
// ---------------------------------------------------------------------------
void SetPlace(int v) {
    S.place = Clamp(v, 0, 4);
    SetOverride(L"position", S.place);
    Relayout(true);
}

void SetRecycleOn(bool on) {
    S.recycle = on;
    SetOverride(L"recycleBin", on ? 1 : 0);
    if (on) CheckRecycleAsync();
    WatchRecycle(on);
    Rebuild(true);
}

void SetTitleOn(bool on) {
    S.showTitle = on;
    SetOverride(L"showTitle", on ? 1 : 0);
    UpdateTitle(true);
}

// Turns the line before item i on or off. A separator after a pin is saved with the
// pins; the lines before the open apps and the Recycle Bin are kept as stored values.
void SetSlot(int i, bool on) {
    switch (SlotKind(i)) {
        case 1: {
            int p = g_items[i - 1].pin;
            if (p < 0 || p >= (int)g_pins.size()) return;
            g_pins[p].sepAfter = on;
            SavePins();
            break;
        }
        case 2:
            S.lineOpen = on;
            Wh_SetIntValue(L"lineOpen", on ? 1 : 0);
            break;
        case 3:
            S.lineBin = on;
            Wh_SetIntValue(L"lineBin", on ? 1 : 0);
            break;
        default:
            return;
    }
    Rebuild(true);
}

// Menus run after the dock may have changed, so they name the item by its key:
// the line goes after it (after = true) or before it.
void SetSepBy(const std::wstring& key, bool after, bool on) {
    int j = FindItem(key);
    if (j >= 0) SetSlot(after ? j + 1 : j, on);
}

constexpr wchar_t kCheck[] = L"\xE73E", kAddGlyph[] = L"\xE710", kRemoveGlyph[] = L"\xE738";

void OpenDockMenu(float along);

void AddDockRow(float along) {
    M.rows.push_back(MenuRow{L"", L"", true});
    M.rows.push_back(MenuRow{L"Dock options", L"\xE713", false, false, [along] { OpenDockMenu(along); }});
}

void OpenDockMenu(float along) {
    if (!g_menu) return;
    HidePopup();
    M.rows.clear();
    M.key.clear();
    M.hot = -1;
    M.rows.push_back(MenuRow{L"Seamless Dock", L"", false, true, nullptr});
    M.rows.push_back(MenuRow{L"", L"", true});
    M.rows.push_back(MenuRow{L"Position", L"", false, true, nullptr});
    const wchar_t* names[] = {L"Across from the taskbar", L"Bottom", L"Top", L"Left", L"Right"};
    for (int v = 0; v < 5; v++)
        M.rows.push_back(MenuRow{names[v], S.place == v ? kCheck : L"", false, false, [v] { SetPlace(v); }});
    M.rows.push_back(MenuRow{L"", L"", true});
    M.rows.push_back(MenuRow{L"Recycle Bin in the dock", S.recycle ? kCheck : L"", false, false,
                             [] { SetRecycleOn(!S.recycle); }});
    M.rows.push_back(MenuRow{L"Window title on the top bar", S.showTitle ? kCheck : L"", false, false,
                             [] { SetTitleOn(!S.showTitle); }});
    M.rows.push_back(MenuRow{L"", L"", true});
    M.rows.push_back(MenuRow{L"Separators", L"", false, true, nullptr});
    M.rows.push_back(MenuRow{L"Before open apps", S.lineOpen ? kCheck : L"", false, false, [] {
                                 S.lineOpen = !S.lineOpen;
                                 Wh_SetIntValue(L"lineOpen", S.lineOpen ? 1 : 0);
                                 Rebuild(true);
                             }});
    M.rows.push_back(MenuRow{L"Before the Recycle Bin", S.lineBin ? kCheck : L"", false, false, [] {
                                 S.lineBin = !S.lineBin;
                                 Wh_SetIntValue(L"lineBin", S.lineBin ? 1 : 0);
                                 Rebuild(true);
                             }});
    ShowMenu(along);
}

// Right-click on a line: remove it.
void OpenSepMenu(int k) {
    if (!g_menu || k < 0 || k >= (int)L.divs.size() || k >= (int)L.divItem.size()) return;
    int i = L.divItem[k];
    if (i <= 0 || i >= (int)g_items.size()) return;
    HidePopup();
    M.rows.clear();
    M.key.clear();
    M.hot = -1;
    float along = L.divs[k];
    std::wstring key = g_items[i].key;
    M.rows.push_back(MenuRow{L"Separator", L"", false, true, nullptr});
    M.rows.push_back(MenuRow{L"", L"", true});
    M.rows.push_back(MenuRow{L"Remove separator", kRemoveGlyph, false, false, [key] { SetSepBy(key, false, false); }});
    AddDockRow(along);
    ShowMenu(along);
}

void OpenRecycleMenu(int i) {
    Item& it = g_items[i];
    float along = L.x[i] + L.plate / 2;
    // The bin is watched, so the last answer is current; refresh it for next time.
    CheckRecycleAsync();
    M.rows.push_back(MenuRow{it.name, L"", false, true, nullptr});
    M.rows.push_back(MenuRow{L"", L"", true});
    M.rows.push_back(MenuRow{L"Open", L"\xE838", false, false, [] { OpenRecycleBin(); }});
    M.rows.push_back(MenuRow{L"Empty Recycle Bin", L"\xE74D", false, false, [] {
                                     EmptyRecycleBin();
                                     if (g_dock) SetTimer(g_dock, kTimerRecycle, 250, nullptr);
                                 }});
    M.rows.push_back(MenuRow{L"Remove from dock", L"\xE77A", false, false, [] { SetRecycleOn(false); }});
    if (SlotKind(i)) {
        bool on = SlotOn(i);
        std::wstring key = it.key;
        M.rows.push_back(MenuRow{on ? L"Remove separator before" : L"Add separator before",
                                 on ? kRemoveGlyph : kAddGlyph, false, false,
                                 [key, on] { SetSepBy(key, false, !on); }});
    }
    AddDockRow(along);
    ShowMenu(along);
}

void OpenMenu(int i) {
    if (!g_menu || i < 0 || i >= (int)g_items.size()) return;
    HidePopup();
    Item& it = g_items[i];
    if (it.recycle) {
        M.rows.clear();
        M.key = it.key;
        M.hot = -1;
        OpenRecycleMenu(i);
        return;
    }
    M.rows.clear();
    M.key = it.key;
    M.hot = -1;
    std::wstring key = it.key;
    M.rows.push_back(MenuRow{it.name, L"", false, true, nullptr});
    std::vector<HWND> wins = it.wins;
    if (!wins.empty()) {
        M.rows.push_back(MenuRow{L"", L"", true});
        for (size_t k = 0; k < wins.size() && k < 10; k++) {
            HWND h = wins[k];
            std::wstring t = WindowTitle(h);
            if (t.empty()) t = it.name;
            M.rows.push_back(MenuRow{t, L"\xE737", false, false, [h] { Activate(h); }});
        }
    }
    M.rows.push_back(MenuRow{L"", L"", true});
    M.rows.push_back(MenuRow{wins.empty() ? L"Open" : L"New window", L"\xE8A7", false, false, [key] {
                                 int j = FindItem(key);
                                 if (j >= 0) Launch(g_items[j]);
                             }});
    if (it.pin >= 0)
        M.rows.push_back(MenuRow{L"Unpin from dock", L"\xE77A", false, false, [key] { UnpinItem(key); }});
    else
        M.rows.push_back(MenuRow{L"Pin to dock", L"\xE718", false, false, [key] { PinItem(key); }});
    if (SlotKind(i + 1)) {
        bool on = SlotOn(i + 1);
        M.rows.push_back(MenuRow{on ? L"Remove separator after" : L"Add separator after",
                                 on ? kRemoveGlyph : kAddGlyph, false, false,
                                 [key, on] { SetSepBy(key, true, !on); }});
    }
    std::wstring where = it.pin >= 0 && it.pin < (int)g_pins.size() ? g_pins[it.pin].exeLower
                         : it.launchKind == L"exe"                 ? it.launchValue
                                                                   : L"";
    if (!where.empty() && GetFileAttributesW(where.c_str()) != INVALID_FILE_ATTRIBUTES)
        M.rows.push_back(MenuRow{L"Open file location", L"\xE838", false, false, [where] {
                                     PIDLIST_ABSOLUTE pidl = ILCreateFromPathW(where.c_str());
                                     if (pidl) {
                                         SHOpenFolderAndSelectItems(pidl, 0, nullptr, 0);
                                         ILFree(pidl);
                                     }
                                 }});
    if (!wins.empty()) {
        M.rows.push_back(MenuRow{L"", L"", true});
        M.rows.push_back(MenuRow{wins.size() > 1 ? L"Close all windows" : L"Close window", L"\xE8BB", false, false,
                                 [wins] {
                                     for (HWND h : wins) CloseWin(h);
                                 }});
    }
    AddDockRow(L.x[i] + L.plate / 2);
    ShowMenu(L.x[i] + L.plate / 2);
}

void PaintMenu() {
    Surface& s = g_menuSurf;
    if (!s.Ensure()) return;
    s.rt->BeginDraw();
    s.rt->Clear(D2D1::ColorF(0, 0));
    D2D1_RECT_F all = D2D1::RectF(0, 0, M.w, M.h);
    s.rt->FillRectangle(all, s.Solid(kBase, TintAlpha()).Get());
    if (S.edgeWidth > 0) StrokeRound(s, all, L.radius, (float)S.edgeWidth, s.Grad(all, 1).Get());
    auto* f = Format(14, DWRITE_FONT_WEIGHT_MEDIUM);
    auto* hf = Format(12, DWRITE_FONT_WEIGHT_SEMI_BOLD);
    auto* gf = Format(14, DWRITE_FONT_WEIGHT_NORMAL, true);
    for (size_t k = 0; k < M.rows.size(); k++) {
        MenuRow& r = M.rows[k];
        if (r.sep) {
            float cy = (r.top + r.bottom) / 2;
            s.rt->FillRectangle(D2D1::RectF(14, cy, M.w - 14, cy + 1), s.Solid(kSurface1).Get());
            continue;
        }
        D2D1_RECT_F rr = D2D1::RectF(6, r.top, M.w - 6, r.bottom);
        if (r.header) {
            DrawText(s, r.text, hf, D2D1::RectF(16, r.top, M.w - 14, r.bottom), kSubtext);
            continue;
        }
        bool hot = (int)k == M.hot;
        if (hot) {
            s.rt->FillRoundedRectangle(D2D1::RoundedRect(rr, 8, 8), s.Solid(kSurface0, 0.8f).Get());
            StrokeRound(s, rr, 8, 1.5f, s.Grad(rr, 1).Get());
        }
        DrawText(s, r.glyph, gf, D2D1::RectF(rr.left + 6, r.top, rr.left + 34, r.bottom), hot ? S.from : kSubtext);
        DrawText(s, r.text, f, D2D1::RectF(rr.left + 40, r.top, rr.right - 12, r.bottom), kText);
    }
    if (s.rt->EndDraw() == D2DERR_RECREATE_TARGET) {
        s.Discard();
        InvalidateRect(s.hwnd, nullptr, FALSE);
    }
}

int MenuRowAt(LPARAM lp) {
    float y = GET_Y_LPARAM(lp) / g_menuSurf.Scale();
    for (size_t k = 0; k < M.rows.size(); k++)
        if (!M.rows[k].sep && !M.rows[k].header && y >= M.rows[k].top && y < M.rows[k].bottom) return (int)k;
    return -1;
}

void RunMenuRow(int k) {
    if (k < 0 || k >= (int)M.rows.size() || !M.rows[k].run) return;
    auto run = M.rows[k].run;
    CloseMenu();
    run();
}

LRESULT CALLBACK MenuProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) {
    switch (msg) {
        case WM_NCCALCSIZE:
            return 0;
        case WM_ERASEBKGND:
            return 1;
        case WM_PAINT: {
            PAINTSTRUCT ps;
            BeginPaint(hwnd, &ps);
            PaintMenu();
            EndPaint(hwnd, &ps);
            return 0;
        }
        case WM_ACTIVATE:
            if (LOWORD(wp) == WA_INACTIVE) CloseMenu();
            return 0;
        case WM_MOUSEMOVE: {
            int k = MenuRowAt(lp);
            if (k != M.hot) {
                M.hot = k;
                InvalidateRect(hwnd, nullptr, FALSE);
            }
            TRACKMOUSEEVENT tme{sizeof(tme), TME_LEAVE, hwnd, 0};
            TrackMouseEvent(&tme);
            return 0;
        }
        case WM_MOUSELEAVE:
            M.hot = -1;
            InvalidateRect(hwnd, nullptr, FALSE);
            return 0;
        case WM_LBUTTONUP:
            RunMenuRow(MenuRowAt(lp));
            return 0;
        case WM_KEYDOWN: {
            if (wp == VK_ESCAPE) {
                CloseMenu();
            } else if (wp == VK_UP || wp == VK_DOWN) {
                int n = (int)M.rows.size(), k = M.hot;
                for (int step = 0; step < n; step++) {
                    k = wp == VK_DOWN ? (k + 1) % n : (k - 1 + n) % n;
                    if (!M.rows[k].sep && !M.rows[k].header) break;
                }
                M.hot = k;
                InvalidateRect(hwnd, nullptr, FALSE);
            } else if (wp == VK_RETURN) {
                RunMenuRow(M.hot);
            }
            return 0;
        }
        case WM_SIZE:
            g_menuSurf.Resize();
            return 0;
    }
    return DefWindowProcW(hwnd, msg, wp, lp);
}

int PopThumbAt(LPARAM lp, bool* onClose) {
    float x = GET_X_LPARAM(lp) / P.s, y = GET_Y_LPARAM(lp) / P.s;
    for (size_t k = 0; k < P.thumbs.size(); k++) {
        auto& b = P.thumbs[k].box;
        if (x >= b.left && x < b.right && y >= b.top && y < b.bottom) {
            auto& c = P.thumbs[k].close;
            *onClose = x >= c.left && x < c.right && y >= c.top && y < c.bottom;
            return (int)k;
        }
    }
    *onClose = false;
    return -1;
}

LRESULT CALLBACK PopProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) {
    switch (msg) {
        case WM_NCCALCSIZE:
            return 0;
        case WM_ERASEBKGND:
            return 1;
        case WM_MOUSEACTIVATE:
            return MA_NOACTIVATE;
        case WM_PAINT: {
            PAINTSTRUCT ps;
            BeginPaint(hwnd, &ps);
            PaintPopup();
            EndPaint(hwnd, &ps);
            return 0;
        }
        case WM_MOUSEMOVE: {
            bool onClose;
            int k = PopThumbAt(lp, &onClose);
            if (k != P.hot || onClose != P.hotClose) {
                P.hot = k;
                P.hotClose = onClose;
                InvalidateRect(hwnd, nullptr, FALSE);
            }
            TRACKMOUSEEVENT tme{sizeof(tme), TME_LEAVE, hwnd, 0};
            TrackMouseEvent(&tme);
            return 0;
        }
        case WM_MOUSELEAVE:
            P.hot = -1;
            P.hotClose = false;
            InvalidateRect(hwnd, nullptr, FALSE);
            return 0;
        case WM_LBUTTONUP:
        case WM_MBUTTONUP: {
            bool onClose;
            int k = PopThumbAt(lp, &onClose);
            if (k < 0) return 0;
            HWND src = P.thumbs[k].src;
            if (onClose || msg == WM_MBUTTONUP) {
                CloseWin(src);
                ScheduleRebuild(400);
                HidePopup();
            } else {
                HidePopup();
                Activate(src);
            }
            return 0;
        }
        case WM_SIZE:
            g_popSurf.Resize();
            return 0;
    }
    return DefWindowProcW(hwnd, msg, wp, lp);
}

// ---------------------------------------------------------------------------
// Full screen apps
// ---------------------------------------------------------------------------
bool FullscreenInFront() {
    HWND fg = GetForegroundWindow();
    if (!fg || fg == g_dock || fg == g_pop || fg == g_menu) return false;
    wchar_t cls[64];
    GetClassNameW(fg, cls, ARRAYSIZE(cls));
    for (PCWSTR c : {L"Progman", L"WorkerW", L"Shell_TrayWnd", L"Shell_SecondaryTrayWnd"})
        if (!wcscmp(cls, c)) return false;
    if (MonitorFromWindow(fg, MONITOR_DEFAULTTONULL) != g_mon) return false;
    // A maximized window with a title bar is just a big window, even when its frame
    // reaches past the screen edge.
    if (IsZoomed(fg) && (GetWindowLongPtrW(fg, GWL_STYLE) & WS_CAPTION) == WS_CAPTION) return false;
    RECT r;
    if (!GetWindowRect(fg, &r)) return false;
    return r.left <= g_monRect.left && r.top <= g_monRect.top && r.right >= g_monRect.right &&
           r.bottom >= g_monRect.bottom;
}

void CheckFullscreen() {
    bool full = S.hideFull && FullscreenInFront();
    if (full == g_fullscreen) return;
    g_fullscreen = full;
    if (full) {
        HidePopup();
        CloseMenu();
        ShowWindow(g_dock, SW_HIDE);
    } else {
        ShowWindow(g_dock, SW_SHOWNOACTIVATE);
        ApplyBackdrop(g_dock);
        SetWindowPos(g_dock, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
    }
    UpdateTitle();
}

// ---------------------------------------------------------------------------
// Top bar title: the app and title of the window in use, in the middle of a
// taskbar along the top of the screen (its app buttons moved to the dock). It
// copies the bar's own pills: clear inside with a grey edge, so the bar's glass
// shows through and nothing doubles it.
// ---------------------------------------------------------------------------
HWND g_title = nullptr, g_titleWin = nullptr;
ComPtr<ID2D1DCRenderTarget> g_titleRt;
ComPtr<ID2D1GradientStopCollection> g_titleStops;
// After a click on the bar, the bar lifts itself a moment after it turns active,
// so one raise on the event lands too early, and the dock thread may be busy
// rebuilding right then. A small thread of its own re-checks every 2 ms for a
// short burst. It only reorders the pill; everything else stays on the dock thread.
HANDLE g_raiseTimer = nullptr, g_zThread = nullptr, g_zReady = nullptr;
DWORD g_zThreadId = 0;
ULONGLONG g_raiseUntil = 0;
// Menus the taskbar and its mods open live in this same process, so the hooks
// that skip it never saw them. They are watched here while they stay open.
HWND g_zWatch[4] = {};
bool g_raiseSlow = false;
// The pill is owned by the taskbar, so Windows raises both in one step when the
// bar is clicked. An owned window shares input with its owner's thread, so the
// pill lives on the small guard thread, never on the busy dock thread.
bool g_titleLost = false, g_zQuitting = false;
std::wstring g_titleKey, g_titleApp, g_titleSrc, g_titleAlt;
// What the pill shows now, so a hover fade can paint it again, and where it sits.
std::wstring g_titleShownApp, g_titleShownText;
RECT g_titleBar{}, g_titleRect{};
float g_titleHoverT = 0;
ULONGLONG g_titleTick = 0;

// Size and corner of the bar's own pills, and the bar's inner top margin that
// pushes its content down from the window's top edge.
constexpr float kTitleH = 34, kTitleR = 10, kBarInnerTop = 6;

// Seamless Taskbar puts the screen x where its tray group starts (plus 1) on the bar, so the
// centred title can stop short of it. 0 when the taskbar does not say.
int TrayLeft() {
    HWND tray = FindWindowW(L"Shell_TrayWnd", nullptr);
    INT_PTR v = tray ? (INT_PTR)GetPropW(tray, L"SeamlessTrayLeft") : 0;
    return v > 0 ? (int)(v - 1) : 0;
}
int g_titleTrayLeft = 0;

bool TopBarRect(RECT& r) {
    HWND tray = FindWindowW(L"Shell_TrayWnd", nullptr);
    if (!tray || !IsWindowVisible(tray) || !GetWindowRect(tray, &r)) return false;
    int monW = g_monRect.right - g_monRect.left, monH = g_monRect.bottom - g_monRect.top;
    return r.top <= g_monRect.top + 2 && r.bottom > g_monRect.top + 20 && r.bottom - r.top < monH / 4 &&
           r.right - r.left > monW / 2;
}

bool IsDesktop(HWND h) {
    wchar_t cls[64];
    GetClassNameW(h, cls, ARRAYSIZE(cls));
    return !wcscmp(cls, L"Progman") || !wcscmp(cls, L"WorkerW");
}

// The window to name. A click on the bar, a tray flyout or a dialog keeps the
// window it belongs to; the desktop clears it.
HWND TitleWindow() {
    HWND fg = GetForegroundWindow();
    if (fg && IsDesktop(fg)) return nullptr;
    if (fg && Eligible(fg)) return fg;
    HWND root = fg ? GetAncestor(fg, GA_ROOTOWNER) : nullptr;
    if (root && root != fg && Eligible(root)) return root;
    if (g_titleWin && IsWindow(g_titleWin) && Eligible(g_titleWin)) return g_titleWin;
    for (HWND h = GetTopWindow(nullptr); h; h = GetWindow(h, GW_HWNDNEXT))
        if (Eligible(h) && !IsIconic(h)) return h;
    return nullptr;
}

void TitleApp(HWND h) {
    g_titleApp.clear();
    g_titleSrc.clear();
    g_titleAlt.clear();
    for (auto& it : g_items)
        if (std::find(it.wins.begin(), it.wins.end(), h) != it.wins.end()) {
            g_titleApp = it.name;
            g_titleSrc = it.iconSrc;
            g_titleAlt = it.iconAlt;
            return;
        }
    auto m = g_winMeta.find(h);
    if (m == g_winMeta.end() || m->second.exe.empty()) return;
    if (IsModHost(Lower(m->second.exe))) {
        g_titleSrc = L"win:" + std::to_wstring((UINT_PTR)h);
        g_titleApp = ModWindowName(m->second.mod, h);
        return;
    }
    g_titleAlt = m->second.exe;
    g_titleApp = FileDescription(m->second.exe);
    if (g_titleApp.empty()) g_titleApp = StripExt(FileName(m->second.exe));
}

// "Report.docx - Word" names the app twice; drop the tail the app name covers.
std::wstring TitleText(HWND h, const std::wstring& app) {
    std::wstring t = WindowTitle(h);
    if (app.empty()) return t;
    if (_wcsicmp(t.c_str(), app.c_str()) == 0) return L"";
    for (PCWSTR sep : {L" - ", L" \x2014 ", L" \x2013 ", L" | "}) {
        std::wstring tail = sep + app;
        if (t.size() > tail.size() && _wcsicmp(t.c_str() + t.size() - tail.size(), tail.c_str()) == 0) {
            t.resize(t.size() - tail.size());
            break;
        }
    }
    return t;
}

void OwnTitle() {
    HWND tray = FindWindowW(L"Shell_TrayWnd", nullptr);
    if (g_title && tray && GetWindow(g_title, GW_OWNER) != tray)
        SetWindowLongPtrW(g_title, GWLP_HWNDPARENT, (LONG_PTR)tray);
}

void HideTitle() {
    if (g_title && IsWindowVisible(g_title)) ShowWindow(g_title, SW_HIDE);
    g_titleKey.clear();
    g_titleHoverT = 0;
    g_titleRect = RECT{};
}

// Clicking the bar lifts it over us; come back just above it. Not to the very
// top: the taskbar's own menu opens above the bar and must stay above the pill.
// The pill belongs to the bar, so Windows can also carry it over a menu the bar
// opened. A visible window that overlaps the pill but sits between it and the
// bar is such a menu (or its shadow): step down under it.
bool TitleOverMenu(HWND tray) {
    RECT pr;
    if (!GetWindowRect(g_title, &pr)) return false;
    int n = 0;
    for (HWND w = GetWindow(g_title, GW_HWNDNEXT); w && w != tray && n < 64; w = GetWindow(w, GW_HWNDNEXT), n++) {
        if (!IsWindowVisible(w)) continue;
        RECT r;
        if (!GetWindowRect(w, &r) || !IntersectRect(&r, &r, &pr)) continue;
        BOOL cloaked = FALSE;
        DwmGetWindowAttribute(w, DWMWA_CLOAKED, &cloaked, sizeof(cloaked));
        if (!cloaked) return true;
    }
    return false;
}

bool OverPill(HWND w) {
    RECT pr, r;
    return w && IsWindowVisible(w) && GetWindowRect(g_title, &pr) && GetWindowRect(w, &r) &&
           IntersectRect(&r, &r, &pr);
}

bool IsBelow(HWND a, HWND b) {
    int n = 0;
    for (HWND w = GetWindow(a, GW_HWNDNEXT); w && n < 256; w = GetWindow(w, GW_HWNDNEXT), n++)
        if (w == b) return true;
    return false;
}

// The lowest open bar menu that covers the pill. The pill goes right under it,
// wherever it sits, so the bar lifting itself or the pill can never leave the
// pill drawn on top of the menu.
// Always-on-top only: a menu over the bar is, and a plain Explorer window
// dragged over the bar must never pull the pill under the bar.
HWND LowestMenuOverPill() {
    HWND low = nullptr;
    for (HWND m : g_zWatch)
        if (OverPill(m) && (GetWindowLongW(m, GWL_EXSTYLE) & WS_EX_TOPMOST) && (!low || IsBelow(low, m)))
            low = m;
    return low;
}

void RaiseTitle() {
    if (!g_title || !IsWindowVisible(g_title)) return;
    if (HWND menu = LowestMenuOverPill()) {
        if (GetWindow(menu, GW_HWNDNEXT) != g_title)
            SetWindowPos(g_title, menu, 0, 0, 0, 0,
                         SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE | SWP_NOOWNERZORDER | SWP_NOSENDCHANGING);
        return;
    }
    HWND tray = FindWindowW(L"Shell_TrayWnd", nullptr);
    if (!tray) return;
    bool under = false;
    for (HWND w = GetWindow(g_title, GW_HWNDPREV); w; w = GetWindow(w, GW_HWNDPREV))
        if (w == tray) {
            under = true;
            break;
        }
    if (!under && !TitleOverMenu(tray)) return;
    HWND above = GetWindow(tray, GW_HWNDPREV);
    if (above == g_title) return;
    // NOSENDCHANGING: from the guard thread the reorder must not wait on
    // a busy dock thread to answer WM_WINDOWPOSCHANGING first.
    SetWindowPos(g_title, above ? above : HWND_TOPMOST, 0, 0, 0, 0,
                 SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE | SWP_NOOWNERZORDER | SWP_NOSENDCHANGING);
}

// Guard thread only from here to ZGuardThread.
void StopRaiseBurst() {
    if (g_raiseTimer) CancelWaitableTimer(g_raiseTimer);
    g_raiseUntil = 0;
}

void ArmRaiseTimer(bool slow) {
    LARGE_INTEGER due;
    due.QuadPart = slow ? -150000 : -20000;  // every 15 ms while a menu stays open, else 2 ms
    SetWaitableTimer(g_raiseTimer, &due, slow ? 15 : 2, nullptr, nullptr, FALSE);
    g_raiseSlow = slow;
}

void StartRaiseBurst() {
    if (!g_title || !g_raiseTimer || !IsWindowVisible(g_title)) return;
    bool running = g_raiseUntil != 0;
    g_raiseUntil = GetTickCount64() + 500;
    if (running && !g_raiseSlow) return;
    ArmRaiseTimer(false);
}

// Only a watched window that covers the pill keeps the 15 ms check going.
bool MenuWatchOpen() {
    bool any = false;
    for (HWND& w : g_zWatch) {
        if (w && !IsWindowVisible(w)) w = nullptr;
        if (OverPill(w)) any = true;
    }
    return any;
}

void WatchMenu(HWND h) {
    for (HWND w : g_zWatch)
        if (w == h) return;
    for (HWND& w : g_zWatch)
        if (!w || !IsWindowVisible(w)) {
            w = h;
            return;
        }
    for (HWND& w : g_zWatch)
        if (!OverPill(w)) {
            w = h;
            return;
        }
    g_zWatch[0] = h;
}

// After the 2 ms burst: keep going at 15 ms while a watched menu is open,
// since hovering a submenu can make Windows lift the pill again.
void RaiseTick() {
    RaiseTitle();
    if (GetTickCount64() < g_raiseUntil) return;
    if (!MenuWatchOpen()) {
        StopRaiseBurst();
        g_raiseSlow = false;
    } else if (!g_raiseSlow) {
        ArmRaiseTimer(true);
    }
}

void CALLBACK ZEventProc(HWINEVENTHOOK, DWORD ev, HWND h, LONG idObj, LONG idChild, DWORD, DWORD) {
    if (!h) return;
    if (ev != EVENT_SYSTEM_MENUPOPUPSTART && (idObj != OBJID_WINDOW || idChild != CHILDID_SELF)) return;
    RaiseTitle();
    StartRaiseBurst();
}

// Same process: our own windows and the taskbar's menus. A menu can open small
// or off to the side and move over the pill a moment later, so any always-on-top
// popup counts; RaiseTitle only acts on the ones that end up over the pill.
void CALLBACK ZOwnEventProc(HWINEVENTHOOK, DWORD ev, HWND h, LONG idObj, LONG idChild, DWORD, DWORD) {
    if (!h || h == g_title || !g_title || !IsWindowVisible(g_title)) return;
    if (ev == EVENT_OBJECT_SHOW || ev == EVENT_SYSTEM_MENUPOPUPSTART) {
        if (ev == EVENT_OBJECT_SHOW && (idObj != OBJID_WINDOW || idChild != CHILDID_SELF)) return;
        HWND root = GetAncestor(h, GA_ROOT);
        if (!root || root == g_title || root == g_dock) return;  // the dock never covers the bar
        if (!OverPill(root) && (!(GetWindowLongW(root, GWL_EXSTYLE) & WS_EX_TOPMOST) ||
                                !(GetWindowLongW(root, GWL_STYLE) & WS_POPUP)))
            return;
        WatchMenu(root);
    } else if (idObj != OBJID_WINDOW || idChild != CHILDID_SELF) {
        return;
    }
    RaiseTitle();
    StartRaiseBurst();
}

HWND MakeTitle() {
    // Click-through and never focused: clicks land on the bar under it.
    const DWORD ex = WS_EX_TOOLWINDOW | WS_EX_TOPMOST | WS_EX_NOACTIVATE | WS_EX_LAYERED | WS_EX_TRANSPARENT;
    // The tool process puts its always-on-top windows on a layer above the
    // taskbar's, where no reorder can slip the pill under the bar's menu.
    // Make it on the desktop layer (1), the same one as the bar and its menus.
    using CreateWindowInBand_t = HWND(WINAPI*)(DWORD, LPCWSTR, LPCWSTR, DWORD, int, int, int, int, HWND, HMENU,
                                                HINSTANCE, LPVOID, DWORD);
    static auto inBand = reinterpret_cast<CreateWindowInBand_t>(
        GetProcAddress(GetModuleHandleW(L"user32.dll"), "CreateWindowInBand"));
    if (inBand) {
        if (HWND h = inBand(ex, L"SeamlessDockTitle", L"Seamless Dock title", WS_POPUP, 0, 0, 10, 10, nullptr,
                            nullptr, GetModuleHandleW(nullptr), nullptr, 1))
            return h;
    }
    return CreateWindowExW(ex, L"SeamlessDockTitle", L"Seamless Dock title", WS_POPUP, 0, 0, 10, 10, nullptr, nullptr,
                           GetModuleHandleW(nullptr), nullptr);
}

DWORD WINAPI ZGuardThread(void*) {
    MSG m;
    PeekMessageW(&m, nullptr, 0, 0, PM_NOREMOVE);  // make the queue before saying ready
    g_zQuitting = false;
    g_title = MakeTitle();
    // 0x2 = CREATE_WAITABLE_TIMER_HIGH_RESOLUTION; older systems refuse it.
    g_raiseTimer = CreateWaitableTimerExW(nullptr, nullptr, 0x2, TIMER_ALL_ACCESS);
    if (!g_raiseTimer) g_raiseTimer = CreateWaitableTimerExW(nullptr, nullptr, 0, TIMER_ALL_ACCESS);
    DWORD pid = GetCurrentProcessId();
    HWINEVENTHOOK hooks[6] = {
        SetWinEventHook(EVENT_SYSTEM_FOREGROUND, EVENT_SYSTEM_FOREGROUND, nullptr, ZEventProc, 0, 0,
                        WINEVENT_OUTOFCONTEXT | WINEVENT_SKIPOWNPROCESS),
        SetWinEventHook(EVENT_SYSTEM_CAPTURESTART, EVENT_SYSTEM_CAPTURESTART, nullptr, ZEventProc,
                        0, 0, WINEVENT_OUTOFCONTEXT | WINEVENT_SKIPOWNPROCESS),
        SetWinEventHook(EVENT_SYSTEM_MENUPOPUPSTART, EVENT_SYSTEM_MENUPOPUPSTART, nullptr, ZEventProc,
                        0, 0, WINEVENT_OUTOFCONTEXT | WINEVENT_SKIPOWNPROCESS),
        SetWinEventHook(EVENT_SYSTEM_FOREGROUND, EVENT_SYSTEM_FOREGROUND, nullptr, ZOwnEventProc, pid, 0,
                        WINEVENT_OUTOFCONTEXT),
        SetWinEventHook(EVENT_SYSTEM_MENUPOPUPSTART, EVENT_SYSTEM_MENUPOPUPSTART, nullptr, ZOwnEventProc,
                        pid, 0, WINEVENT_OUTOFCONTEXT),
        SetWinEventHook(EVENT_OBJECT_SHOW, EVENT_OBJECT_SHOW, nullptr, ZOwnEventProc, pid, 0,
                        WINEVENT_OUTOFCONTEXT)};
    SetEvent(g_zReady);
    for (bool quit = false; !quit;) {
        if (g_raiseUntil && g_raiseTimer) {
            DWORD r = MsgWaitForMultipleObjectsEx(1, &g_raiseTimer, INFINITE, QS_ALLINPUT,
                                                  MWMO_INPUTAVAILABLE);
            if (r == WAIT_OBJECT_0) {
                RaiseTick();
                continue;
            }
            while (PeekMessageW(&m, nullptr, 0, 0, PM_REMOVE)) {
                if (m.message == WM_QUIT) { quit = true; break; }
                DispatchMessageW(&m);
            }
        } else if (GetMessageW(&m, nullptr, 0, 0) <= 0) {
            break;
        } else {
            DispatchMessageW(&m);
        }
        if (g_titleLost && !quit) {
            g_titleLost = false;
            g_title = MakeTitle();
            Wh_Log(L"title pill made again after its owner went away");
        }
    }
    g_zQuitting = true;
    if (HWND t = g_title) {
        g_title = nullptr;
        DestroyWindow(t);
    }
    for (HWINEVENTHOOK h : hooks)
        if (h) UnhookWinEvent(h);
    StopRaiseBurst();
    if (g_raiseTimer) {
        CloseHandle(g_raiseTimer);
        g_raiseTimer = nullptr;
    }
    return 0;
}

void StartZGuard() {
    g_zReady = CreateEventW(nullptr, TRUE, FALSE, nullptr);
    g_zThread = CreateThread(nullptr, 0, ZGuardThread, nullptr, 0, &g_zThreadId);
    if (g_zThread) WaitForSingleObject(g_zReady, 2000);
}

void StopZGuard() {
    if (g_zThread) {
        PostThreadMessageW(g_zThreadId, WM_QUIT, 0, 0);
        WaitForSingleObject(g_zThread, 3000);
        CloseHandle(g_zThread);
        g_zThread = nullptr;
    }
    if (g_zReady) {
        CloseHandle(g_zReady);
        g_zReady = nullptr;
    }
}

bool PaintTitle(const std::wstring& app, const std::wstring& title, Icon* ic, const RECT& bar) {
    if (!EnsureFactories()) return false;
    float sc = MonitorDpi(g_mon) / 96.f;
    IDWriteTextFormat* fApp = Format(13 * sc, DWRITE_FONT_WEIGHT_SEMI_BOLD);
    IDWriteTextFormat* fTitle = Format(13 * sc, DWRITE_FONT_WEIGHT_NORMAL);
    if (!fApp || !fTitle) return false;
    float pad = std::round(12 * sc), iconSz = std::round(18 * sc), gap = std::round(8 * sc);
    float sepGap = std::round(12 * sc);
    int Hi = (int)std::lround(kTitleH * sc);
    float appW = std::ceil(TextWidth(app, fApp));
    float titleW = title.empty() ? 0 : std::ceil(TextWidth(title, fTitle));
    float fixed = 2 * pad + (ic ? iconSz + gap : 0) + (title.empty() ? 0 : sepGap);
    float room = std::round((float)S.titleMaxW * sc) - fixed;
    // Stay centred, but never reach the tray group on the right.
    int trayLeft = TrayLeft();
    int mid = (bar.left + bar.right) / 2;
    if (trayLeft > mid) {
        float half = (float)(trayLeft - mid) - std::round(8 * sc);
        room = std::min(room, std::max(0.f, 2 * half - fixed));
    }
    if (appW + titleW > room) {
        float appCap = title.empty() ? room : std::max(room * 0.4f, room - titleW);
        appW = std::min(appW, appCap);
        titleW = std::max(0.f, room - appW);
    }
    int W = (int)std::ceil(fixed + appW + titleW);
    int top = (int)std::lround(kBarInnerTop * sc);
    int x0 = (bar.left + bar.right - W) / 2;
    int y0 = bar.top + top + (bar.bottom - bar.top - top - Hi) / 2;

    HDC screen = GetDC(nullptr);
    HDC mem = CreateCompatibleDC(screen);
    BITMAPINFO bi{};
    bi.bmiHeader.biSize = sizeof(bi.bmiHeader);
    bi.bmiHeader.biWidth = W;
    bi.bmiHeader.biHeight = -Hi;
    bi.bmiHeader.biPlanes = 1;
    bi.bmiHeader.biBitCount = 32;
    void* bits = nullptr;
    HBITMAP dib = CreateDIBSection(screen, &bi, DIB_RGB_COLORS, &bits, nullptr, 0);
    HGDIOBJ old = dib ? SelectObject(mem, dib) : nullptr;
    bool ok = false;
    if (dib) {
        if (!g_titleRt) {
            auto props = D2D1::RenderTargetProperties(
                D2D1_RENDER_TARGET_TYPE_DEFAULT,
                D2D1::PixelFormat(DXGI_FORMAT_B8G8R8A8_UNORM, D2D1_ALPHA_MODE_PREMULTIPLIED), 96, 96);
            if (SUCCEEDED(g_d2d->CreateDCRenderTarget(&props, g_titleRt.GetAddressOf())))
                g_titleRt->SetTextAntialiasMode(D2D1_TEXT_ANTIALIAS_MODE_GRAYSCALE);
        }
        RECT rc{0, 0, W, Hi};
        if (g_titleRt && FAILED(g_titleRt->BindDC(mem, &rc))) {
            g_titleRt.Reset();
            g_titleStops.Reset();
        }
        if (g_titleRt) {
            ID2D1DCRenderTarget* rt = g_titleRt.Get();
            rt->BeginDraw();
            rt->Clear(D2D1::ColorF(0, 0, 0, 0));
            float w = std::max(1.f, std::round(2 * sc));
            D2D1_RECT_F r{w / 2, w / 2, W - w / 2, Hi - w / 2};
            float rr = std::max(0.f, kTitleR * sc - w / 2);
            ComPtr<ID2D1SolidColorBrush> edge, text, sub;
            float h = g_titleHoverT;
            // Same rest edge and fill as the bar's docks (#45475A at 0.9 over Mocha base).
            rt->CreateSolidColorBrush(Col(0x45475A, 0.9f * (1 - h)), edge.GetAddressOf());
            rt->CreateSolidColorBrush(Col(kText), text.GetAddressOf());
            rt->CreateSolidColorBrush(Col(kSubtext), sub.GetAddressOf());
            ComPtr<ID2D1SolidColorBrush> fill;
            rt->CreateSolidColorBrush(Col(0x1E1E2E, 0.92f), fill.GetAddressOf());
            if (fill) rt->FillRoundedRectangle(D2D1::RoundedRect(r, rr, rr), fill.Get());
            if (h < 1) rt->DrawRoundedRectangle(D2D1::RoundedRect(r, rr, rr), edge.Get(), w);
            // Pointing at it fades in the blue to mauve edge the bar's other pills have.
            if (h > 0) {
                if (!g_titleStops) {
                    D2D1_GRADIENT_STOP gs[2] = {{0.f, Col(S.from)}, {1.f, Col(S.to)}};
                    rt->CreateGradientStopCollection(gs, 2, g_titleStops.GetAddressOf());
                }
                ComPtr<ID2D1LinearGradientBrush> grad;
                if (g_titleStops)
                    rt->CreateLinearGradientBrush(
                        D2D1::LinearGradientBrushProperties(D2D1::Point2F(0, (float)Hi), D2D1::Point2F((float)W, 0)),
                        D2D1::BrushProperties(h), g_titleStops.Get(), grad.GetAddressOf());
                if (grad) rt->DrawRoundedRectangle(D2D1::RoundedRect(r, rr, rr), grad.Get(), w);
            }
            float x = pad;
            if (ic && ic->w > 0 && ic->h > 0) {
                ComPtr<ID2D1Bitmap> bmp;
                rt->CreateBitmap(D2D1::SizeU(ic->w, ic->h), ic->px.data(), ic->w * 4,
                                 D2D1::BitmapProperties(
                                     D2D1::PixelFormat(DXGI_FORMAT_B8G8R8A8_UNORM, D2D1_ALPHA_MODE_PREMULTIPLIED),
                                     96, 96),
                                 bmp.GetAddressOf());
                float iy = std::round((Hi - iconSz) / 2);
                if (bmp)
                    rt->DrawBitmap(bmp.Get(), D2D1::RectF(x, iy, x + iconSz, iy + iconSz), 1.f,
                                   D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, ic->src);
                x += iconSz + gap;
            } else if (ic) {
                x += iconSz + gap;
            }
            rt->DrawText(app.c_str(), (UINT32)app.size(), fApp, D2D1::RectF(x, 0, x + appW, (float)Hi), text.Get(),
                         D2D1_DRAW_TEXT_OPTIONS_CLIP);
            x += appW + sepGap;
            if (!title.empty() && titleW > 0)
                rt->DrawText(title.c_str(), (UINT32)title.size(), fTitle, D2D1::RectF(x, 0, x + titleW, (float)Hi),
                             sub.Get(), D2D1_DRAW_TEXT_OPTIONS_CLIP);
            ok = SUCCEEDED(rt->EndDraw());
            if (!ok) {
                g_titleRt.Reset();
                g_titleStops.Reset();
            }
        }
    }
    if (ok) {
        POINT dst{x0, y0}, src{0, 0};
        SIZE sz{W, Hi};
        BLENDFUNCTION bf{AC_SRC_OVER, 0, 255, AC_SRC_ALPHA};
        ok = UpdateLayeredWindow(g_title, screen, &dst, &sz, mem, &src, 0, &bf, ULW_ALPHA) != FALSE;
        if (ok) g_titleRect = RECT{x0, y0, x0 + W, y0 + Hi};
        else {
            g_titleRt.Reset();
            g_titleStops.Reset();
        }
    }
    if (old) SelectObject(mem, old);
    if (dib) DeleteObject(dib);
    DeleteDC(mem);
    ReleaseDC(nullptr, screen);
    return ok;
}

void UpdateTitle(bool force) {
    if (!g_title) return;
    RECT bar;
    if (!S.showTitle || g_fullscreen || !TopBarRect(bar)) {
        HideTitle();
        return;
    }
    OwnTitle();
    HWND h = TitleWindow();
    if (!h) {
        g_titleWin = nullptr;
        HideTitle();
        return;
    }
    if (h != g_titleWin || force || g_titleApp.empty()) {
        g_titleWin = h;
        TitleApp(h);
    }
    std::wstring title = TitleText(h, g_titleApp);
    std::wstring app = g_titleApp;
    if (app.empty()) app.swap(title);
    if (app.empty()) {
        HideTitle();
        return;
    }
    UINT dpi = MonitorDpi(g_mon);
    std::wstring key = app + L"\n" + title + L"\n" + std::to_wstring(bar.left) + L"," + std::to_wstring(bar.top) +
                       L"," + std::to_wstring(bar.right) + L"," + std::to_wstring(bar.bottom) + L"," +
                       std::to_wstring(dpi) + L"," + std::to_wstring((UINT_PTR)h) + L"," +
                       std::to_wstring(TrayLeft());
    bool shown = IsWindowVisible(g_title) != FALSE;
    if (!force && shown && key == g_titleKey) {
        RaiseTitle();
        return;
    }
    Icon* ic = GetIcon(g_titleSrc, g_titleAlt, h, (int)std::lround(32 * dpi / 96.f));
    if (!PaintTitle(app, title, ic, bar)) return;
    g_titleKey = key;
    g_titleShownApp = app;
    g_titleShownText = title;
    g_titleBar = bar;
    if (!shown) {
        ShowWindow(g_title, SW_SHOWNOACTIVATE);
        SetWindowPos(g_title, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
        RaiseTitle();  // a menu may already be open over the spot
        SetTimer(g_dock, kTimerTitle, 50, nullptr);
    } else {
        RaiseTitle();
    }
}

// The pill lets clicks through to the bar, so it never hears the mouse. Watch
// the pointer instead: 20 times a second while resting, every frame while the
// edge fades.
void TitleHoverTick() {
    if (!g_title || !IsWindowVisible(g_title) || IsRectEmpty(&g_titleRect)) {
        KillTimer(g_dock, kTimerTitle);
        g_titleTick = 0;
        return;
    }
    // Backstop, at most 50 ms late: whatever lifted the pill, put it back.
    RaiseTitle();
    // The tray group grew or shrank (a timer started, a pill appeared): fit again.
    int trayLeft = TrayLeft();
    if (trayLeft != g_titleTrayLeft) {
        g_titleTrayLeft = trayLeft;
        UpdateTitle();
        if (!g_title || !IsWindowVisible(g_title)) return;
    }
    POINT pt;
    GetCursorPos(&pt);
    float target = PtInRect(&g_titleRect, pt) ? 1.f : 0.f;
    ULONGLONG now = GetTickCount64();
    if (g_titleHoverT == target) {
        if (g_titleTick) SetTimer(g_dock, kTimerTitle, 50, nullptr);
        g_titleTick = 0;
        return;
    }
    if (!g_titleTick) {
        g_titleTick = now;
        SetTimer(g_dock, kTimerTitle, 15, nullptr);
        if (S.fadeMs) return;
    }
    float step = S.fadeMs ? (float)(now - g_titleTick) / S.fadeMs : 1.f;
    g_titleTick = now;
    g_titleHoverT = target > g_titleHoverT ? std::min(target, g_titleHoverT + step)
                                           : std::max(target, g_titleHoverT - step);
    UINT dpi = MonitorDpi(g_mon);
    Icon* ic = g_titleWin ? GetIcon(g_titleSrc, g_titleAlt, g_titleWin, (int)std::lround(32 * dpi / 96.f)) : nullptr;
    PaintTitle(g_titleShownApp, g_titleShownText, ic, g_titleBar);
}

LRESULT CALLBACK TitleProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) {
    if (msg == WM_NCHITTEST) return HTTRANSPARENT;
    // A shell restart can take the pill down with its owner; the guard makes a new one.
    if (msg == WM_NCDESTROY && hwnd == g_title && !g_zQuitting) {
        g_title = nullptr;
        g_titleLost = true;
    }
    if (msg == WM_MOUSEACTIVATE) return MA_NOACTIVATE;
    return DefWindowProcW(hwnd, msg, wp, lp);
}

// ---------------------------------------------------------------------------
// Dock window
// ---------------------------------------------------------------------------
std::vector<HWINEVENTHOOK> g_hooks;

void CALLBACK WinEventProc(HWINEVENTHOOK, DWORD ev, HWND h, LONG idObj, LONG idChild, DWORD, DWORD) {
    if (idObj != OBJID_WINDOW || idChild != CHILDID_SELF || !h) return;
    // A click on the bar (its right-click menu most of all) lifts the bar over
    // the pill. Climb back at once, not after the rebuild's wait, or the pill
    // blinks under the bar's glass for a moment.
    if (ev == EVENT_SYSTEM_FOREGROUND || ev == EVENT_OBJECT_SHOW) RaiseTitle();
    if (ev == EVENT_SYSTEM_FOREGROUND) {
        ScheduleRebuild(30);
        CheckFullscreen();
        return;
    }
    if (GetAncestor(h, GA_ROOT) != h) return;
    ScheduleRebuild(120);
}

void StartTracking() { SetTimer(g_dock, kTimerTrack, 60, nullptr); }

void SetHover(int i) {
    if (i == g_hover) return;
    g_hover = i;
    KillTimer(g_dock, kTimerHover);
    if (i >= 0) {
        if (PopupVisible())
            ShowPopup(i);
        else
            SetTimer(g_dock, kTimerHover, std::max(1, S.hoverDelay), nullptr);
        StartTracking();
    }
    StartAnim();
}

void EndDrag(bool save) {
    if (g_dragIndex >= 0 && save) SavePins();
    g_dragIndex = -1;
    InvalidateRect(g_dock, nullptr, FALSE);
}

void DragTo(float x) {
    g_dragX = x;
    // The nearest pinned place; separators make the spacing uneven.
    float c = x - g_dragGrab + L.plate / 2, best = 1e9f;
    int slot = -1;
    for (int j = 0; j < g_pinnedCount && j < (int)L.x.size() && j < (int)g_pins.size(); j++) {
        float dd = std::fabs(L.x[j] + L.plate / 2 - c);
        if (dd < best) {
            best = dd;
            slot = j;
        }
    }
    if (slot != g_dragIndex && slot >= 0 && g_dragIndex < (int)g_pins.size()) {
        // Separators keep their places; only the app moves between them.
        std::vector<bool> seps;
        for (auto& q : g_pins) seps.push_back(q.sepAfter);
        Pin p = g_pins[g_dragIndex];
        g_pins.erase(g_pins.begin() + g_dragIndex);
        g_pins.insert(g_pins.begin() + slot, p);
        for (size_t j = 0; j < g_pins.size(); j++) g_pins[j].sepAfter = seps[j];
        Item it = g_items[g_dragIndex];
        g_items.erase(g_items.begin() + g_dragIndex);
        g_items.insert(g_items.begin() + slot, it);
        for (int i = 0; i < g_pinnedCount; i++) g_items[i].pin = i;
        g_dragIndex = slot;
        g_hover = slot;
    }
    InvalidateRect(g_dock, nullptr, FALSE);
}

// The taskbar's menu asks and sets through "SeamlessDock.Control":
// 1 = what is set (bits 0-2 position, bit 4 Recycle Bin, bit 5 title, bits 8+ edge + 1),
// 2 = set position (0 across from the taskbar, 1 bottom, 2 top, 3 left, 4 right),
// 3 = Recycle Bin on or off, 4 = title on or off, 5 = the taskbar moved.
LRESULT DockControl(WPARAM wp, LPARAM lp) {
    switch (wp) {
        case 2:
            SetPlace((int)lp);
            break;
        case 3:
            SetRecycleOn(lp != 0);
            break;
        case 4:
            SetTitleOn(lp != 0);
            break;
        case 5:
            Relayout(true);
            break;
    }
    return 0x40000000 | S.place | (S.recycle ? 0x10 : 0) | (S.showTitle ? 0x20 : 0) | ((LRESULT)(g_edge + 1) << 8);
}

void CheckRecycle() {
    g_recycleChecked = GetTickCount64();
    CheckRecycleAsync();
}

void RecycleAnswered(bool full) {
    if (InterlockedExchange(&g_recycleAgain, 0)) CheckRecycleAsync();
    if (full == g_recycleFull) return;
    g_recycleFull = full;
    if (S.recycle) Rebuild(true);
}

LRESULT CALLBACK DockProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) {
    if (msg == g_ctlMsg && g_ctlMsg) return DockControl(wp, lp);
    if (msg == g_shellMsg && g_shellMsg) {
        HWND h = (HWND)lp;
        if (wp == HSHELL_FLASH) {
            g_flash.insert(h);
        } else if ((wp & 0x7FFF) == HSHELL_WINDOWACTIVATED) {
            g_flash.erase(h);
            CheckFullscreen();
        }
        ScheduleRebuild(wp == HSHELL_WINDOWCREATED ? 150 : 60);
        return 0;
    }
    if (msg == g_taskbarCreatedMsg && g_taskbarCreatedMsg) {
        HWND tray;
        DWORD trayPid;
        CurrentTray(&tray, &trayPid);
        if (g_appbar && tray && tray == g_appbarTray && trayPid == g_appbarTrayPid) {
            // Same Explorer: a stray broadcast from some app. Keep the reserved
            // strip, or windows dip under the dock while it is taken back.
            Wh_Log(L"TaskbarCreated from the same shell (pid %u): strip kept", trayPid);
            RegisterShellHookWindow(hwnd);
            WatchRecycle(false);
            WatchRecycle(S.recycle);
            return 0;
        }
        // Explorer restarted: the appbar and the shell hook went with it.
        Wh_Log(L"TaskbarCreated from a new shell (pid %u): strip taken back", trayPid);
        g_appbar = false;
        g_barHeightSent = -1;
        g_barRect = RECT{};
        RegisterShellHookWindow(hwnd);
        WatchRecycle(false);
        WatchRecycle(S.recycle);
        Relayout(true);
        UpdateTitle(true);
        return 0;
    }
    switch (msg) {
        case WM_NCCALCSIZE:
            return 0;
        case WM_ERASEBKGND:
            return 1;
        case WM_MOUSEACTIVATE:
            return MA_NOACTIVATE;
        case WM_PAINT: {
            PAINTSTRUCT ps;
            BeginPaint(hwnd, &ps);
            PaintDock();
            EndPaint(hwnd, &ps);
            return 0;
        }
        case WM_SIZE:
            g_dockSurf.Resize();
            return 0;
        case WM_MOUSEMOVE: {
            POINT pt{GET_X_LPARAM(lp), GET_Y_LPARAM(lp)};
            float along, depth, pressAlong;
            Unplace(pt, along, depth);
            Unplace(g_pressPt, pressAlong, depth);
            if (g_press >= 0 && g_dragIndex < 0 && g_press < g_pinnedCount && !g_pressMiddle &&
                std::abs(along - pressAlong) > 6) {
                g_dragIndex = g_press;
                g_dragGrab = pressAlong - L.x[g_press];
                HidePopup();
                KillTimer(hwnd, kTimerHover);
            }
            if (g_dragIndex >= 0) {
                DragTo(along);
                StartAnim();
                return 0;
            }
            SetHover(ItemAt(pt));
            TRACKMOUSEEVENT tme{sizeof(tme), TME_LEAVE, hwnd, 0};
            TrackMouseEvent(&tme);
            return 0;
        }
        case WM_MOUSELEAVE:
            if (g_dragIndex < 0 && !PopupVisible()) SetHover(-1);
            return 0;
        case WM_LBUTTONDOWN:
        case WM_MBUTTONDOWN:
            g_press = ItemAt(POINT{GET_X_LPARAM(lp), GET_Y_LPARAM(lp)});
            g_pressMiddle = msg == WM_MBUTTONDOWN;
            g_pressPt = POINT{GET_X_LPARAM(lp), GET_Y_LPARAM(lp)};
            if (g_press >= 0) SetCapture(hwnd);
            KillTimer(hwnd, kTimerHover);
            HidePopup();
            if (MenuOpen()) CloseMenu();
            return 0;
        case WM_LBUTTONUP:
        case WM_MBUTTONUP: {
            int pressed = g_press;
            g_press = -1;
            // Letting go of the mouse ends a drag through WM_CAPTURECHANGED, so look
            // first: a drag dropped back on its own place is not a click.
            bool wasDrag = g_dragIndex >= 0;
            if (GetCapture() == hwnd) ReleaseCapture();
            if (wasDrag) {
                if (g_dragIndex >= 0) EndDrag(true);
                return 0;
            }
            int at = ItemAt(POINT{GET_X_LPARAM(lp), GET_Y_LPARAM(lp)});
            if (at >= 0 && at == pressed) ClickItem(at, msg == WM_MBUTTONUP);
            return 0;
        }
        case WM_CAPTURECHANGED:
            if (g_dragIndex >= 0 && (HWND)lp != hwnd) EndDrag(true);
            g_press = -1;
            return 0;
        case WM_RBUTTONUP: {
            POINT pt{GET_X_LPARAM(lp), GET_Y_LPARAM(lp)};
            int at = ItemAt(pt);
            int dv = at >= 0 ? -1 : DivAt(pt);
            if (at >= 0) {
                OpenMenu(at);
            } else if (dv >= 0) {
                OpenSepMenu(dv);
            } else {
                float along, depth;
                Unplace(pt, along, depth);
                OpenDockMenu(along);
            }
            return 0;
        }
        case WM_TIMER:
            switch (wp) {
                case kTimerRebuild:
                    KillTimer(hwnd, kTimerRebuild);
                    g_rebuildPending = false;
                    if (Rebuild()) StartAnim();
                    break;
                case kTimerAnim:
                    if (!StepAnim()) KillTimer(hwnd, kTimerAnim);
                    InvalidateRect(hwnd, nullptr, FALSE);
                    if (PopupVisible()) InvalidateRect(g_pop, nullptr, FALSE);
                    break;
                case kTimerHover:
                    KillTimer(hwnd, kTimerHover);
                    if (g_hover >= 0 && g_press < 0) ShowPopup(g_hover);
                    break;
                case kTimerTrack: {
                    POINT pt;
                    GetCursorPos(&pt);
                    RECT dr, pr{};
                    GetWindowRect(hwnd, &dr);
                    if (PopupVisible()) GetWindowRect(g_pop, &pr);
                    bool in = PtInRect(&dr, pt) || (PopupVisible() && PtInRect(&pr, pt));
                    // The strip between the dock and its preview counts as inside.
                    if (PopupVisible()) {
                        RECT gapStrip = g_edge == ABE_TOP     ? RECT{pr.left, dr.bottom, pr.right, pr.top}
                                        : g_edge == ABE_LEFT  ? RECT{dr.right, pr.top, pr.left, pr.bottom}
                                        : g_edge == ABE_RIGHT ? RECT{pr.right, pr.top, dr.left, pr.bottom}
                                                              : RECT{pr.left, pr.bottom, pr.right, dr.top};
                        if (PtInRect(&gapStrip, pt)) in = true;
                    }
                    ULONGLONG now = GetTickCount64();
                    if (in || g_dragIndex >= 0) {
                        g_outSince = 0;
                    } else if (!g_outSince) {
                        g_outSince = now;
                    } else if (now - g_outSince > 220) {
                        g_outSince = 0;
                        KillTimer(hwnd, kTimerTrack);
                        HidePopup();
                        SetHover(-1);
                    }
                    break;
                }
                case kTimerFull: {
                    CheckFullscreen();
                    UpdateTitle();
                    // Keep the glass alive on the always-up dock (see ApplyBackdrop).
                    static ULONGLONG glassAt = GetTickCount64();
                    if (!g_fullscreen && GetTickCount64() - glassAt > 120000) {
                        glassAt = GetTickCount64();
                        ApplyBackdrop(g_dock);
                    }
                    if (MenuOpen()) {
                        HWND fg = GetForegroundWindow();
                        if (fg && fg != g_menu && fg != g_menuFgAtOpen) CloseMenu();
                    }
                    // The taskbar moved or changed size: follow it.
                    RECT r{};
                    bool solid = false;
                    int e = TaskbarEdge(r, solid);
                    if (e != g_tbEdge || solid != g_tbSolidSeen || (solid && !EqualRect(&r, &g_tbRect)))
                        Relayout(true);
                    // The shell can drop the reserved strip without telling us (a shell
                    // restart, a display change). Then windows and the window manager's
                    // tiles run under the dock. Every 5 s, if the work area reaches into
                    // the strip, register it again.
                    // Three heals in a row that did not stick (another bar fighting for
                    // the space, a shell that keeps resetting) slow it to once a minute.
                    static ULONGLONG stripChecked = 0;
                    static int heals = 0;
                    ULONGLONG every = heals >= 3 ? 60000 : 5000;
                    if (S.reserve && !g_fullscreen && GetTickCount64() - stripChecked > every) {
                        stripChecked = GetTickCount64();
                        bool healed = true;
                        MONITORINFO mi{sizeof(mi)};
                        if (g_mon && GetMonitorInfoW(g_mon, &mi) && !IsRectEmpty(&g_barRect)) {
                            const RECT& w = mi.rcWork;
                            bool lost = g_edge == ABE_TOP     ? w.top < g_barRect.bottom
                                        : g_edge == ABE_LEFT  ? w.left < g_barRect.right
                                        : g_edge == ABE_RIGHT ? w.right > g_barRect.left
                                                              : w.bottom > g_barRect.top;
                            if (lost || !g_appbar) {
                                AppBarRemove();
                                g_barRect = RECT{};
                                Relayout(true);
                            } else {
                                healed = false;
                            }
                        } else if (!g_appbar || IsRectEmpty(&g_barRect)) {
                            g_barHeightSent = -1;
                            Relayout(true);
                        } else {
                            healed = false;
                        }
                        heals = healed ? heals + 1 : 0;
                    }
                    // A slow backup in case the shell's change notices never arrive.
                    if (S.recycle && GetTickCount64() - g_recycleChecked > 15000) CheckRecycle();
                    break;
                }
                case kTimerRecycle:
                    KillTimer(hwnd, kTimerRecycle);
                    CheckRecycle();
                    break;
                case kTimerTitle:
                    TitleHoverTick();
                    break;
            }
            return 0;
        case kRecycleMsg: {
            PIDLIST_ABSOLUTE* pidls = nullptr;
            LONG ev = 0;
            HANDLE lock = SHChangeNotification_Lock((HANDLE)wp, (DWORD)lp, &pidls, &ev);
            if (lock) SHChangeNotification_Unlock(lock);
            SetTimer(hwnd, kTimerRecycle, 250, nullptr);
            return 0;
        }
        case kRecycleDone:
            RecycleAnswered(wp != 0);
            return 0;
        case kAppBarMsg:
            if (wp == ABN_POSCHANGED) {
                Relayout(true);
            } else if (wp == ABN_FULLSCREENAPP) {
                CheckFullscreen();
            }
            return 0;
        case WM_WINDOWPOSCHANGED:
            if (g_appbar && ShellResponds()) {
                APPBARDATA abd{sizeof(abd)};
                abd.hWnd = hwnd;
                SHAppBarMessage(ABM_WINDOWPOSCHANGED, &abd);
            }
            break;
        case 0x031E /* WM_DWMCOMPOSITIONCHANGED */:
            ApplyBackdrop(g_dock);
            return 0;
        case WM_DPICHANGED:
        case WM_DISPLAYCHANGE:
            ApplyBackdrop(g_dock);
            g_icons.clear();
            g_formats.clear();
            Relayout();
            UpdateTitle(true);
            return 0;
        case WM_SETTINGCHANGE:
            if (lp && !wcscmp((PCWSTR)lp, L"ImmersiveColorSet")) InvalidateRect(hwnd, nullptr, FALSE);
            if (wp == SPI_SETWORKAREA) break;
            return 0;
        case kReloadMsg: {
            LoadSettings();
            g_icons.clear();
            g_formats.clear();
            g_dockSurf.Discard();
            g_popSurf.Discard();
            g_menuSurf.Discard();
            g_titleRt.Reset();
            g_titleStops.Reset();
            if (!S.reserve) AppBarRemove();
            g_names.clear();
            if (S.recycle) CheckRecycleAsync();
            WatchRecycle(S.recycle);
            Rebuild(true);
            Relayout(true);
            UpdateTitle(true);
            return 0;
        }
        case WM_CLOSE:
            DestroyWindow(hwnd);
            return 0;
        case WM_DESTROY:
            for (auto h : g_hooks) UnhookWinEvent(h);
            g_hooks.clear();
            DeregisterShellHookWindow(hwnd);
            WatchRecycle(false);
            AppBarRemove();
            UnregisterThumbs();
            if (g_pop) DestroyWindow(g_pop);
            if (g_menu) DestroyWindow(g_menu);
            // The guard thread owns the pill and destroys it when it stops.
            if (g_title) ShowWindow(g_title, SW_HIDE);
            g_pop = g_menu = nullptr;
            PostQuitMessage(0);
            return 0;
    }
    return DefWindowProcW(hwnd, msg, wp, lp);
}

HANDLE g_thread, g_ready;

DWORD WINAPI DockThread(void*) {
    SetThreadDpiAwarenessContext(DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2);
    CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED);
    HINSTANCE inst = GetModuleHandleW(nullptr);

    WNDCLASSEXW wc{sizeof(wc)};
    wc.hInstance = inst;
    wc.hCursor = LoadCursorW(nullptr, IDC_ARROW);
    wc.lpfnWndProc = DockProc;
    wc.lpszClassName = L"SeamlessDock";
    RegisterClassExW(&wc);
    wc.lpfnWndProc = PopProc;
    wc.lpszClassName = L"SeamlessDockPreview";
    RegisterClassExW(&wc);
    wc.lpfnWndProc = MenuProc;
    wc.lpszClassName = L"SeamlessDockMenu";
    RegisterClassExW(&wc);
    wc.lpfnWndProc = TitleProc;
    wc.lpszClassName = L"SeamlessDockTitle";
    RegisterClassExW(&wc);

    LoadSettings();
    LoadPins();
    g_mon = MonitorFromPoint(POINT{0, 0}, MONITOR_DEFAULTTOPRIMARY);

    g_dock = CreateWindowExW(WS_EX_TOOLWINDOW | WS_EX_TOPMOST | WS_EX_NOACTIVATE, L"SeamlessDock", L"Seamless Dock",
                             WS_POPUP, 0, 0, 10, 10, nullptr, nullptr, inst, nullptr);
    g_pop = CreateWindowExW(WS_EX_TOOLWINDOW | WS_EX_TOPMOST | WS_EX_NOACTIVATE, L"SeamlessDockPreview",
                            L"Seamless Dock preview", WS_POPUP, 0, 0, 10, 10, nullptr, nullptr, inst, nullptr);
    g_menu = CreateWindowExW(WS_EX_TOOLWINDOW | WS_EX_TOPMOST, L"SeamlessDockMenu", L"Seamless Dock menu", WS_POPUP,
                             0, 0, 10, 10, nullptr, nullptr, inst, nullptr);
    // The pill is made on the guard thread (see OwnTitle).
    StartZGuard();
    if (!g_dock || !g_pop || !g_menu) {
        Wh_Log(L"CreateWindow failed: %u", GetLastError());
        StopZGuard();
        // Leave nothing half made: the init check reads g_dock to say we failed.
        for (HWND* h : {&g_menu, &g_pop, &g_dock})
            if (*h) {
                DestroyWindow(*h);
                *h = nullptr;
            }
        SetEvent(g_ready);
        CoUninitialize();
        return 1;
    }
    g_dockSurf.hwnd = g_dock;
    g_popSurf.hwnd = g_pop;
    g_menuSurf.hwnd = g_menu;
    ApplyBackdrop(g_dock);
    ApplyBackdrop(g_pop);
    ApplyBackdrop(g_menu);

    g_shellMsg = RegisterWindowMessageW(L"SHELLHOOK");
    g_taskbarCreatedMsg = RegisterWindowMessageW(L"TaskbarCreated");
    ChangeWindowMessageFilterEx(g_dock, g_taskbarCreatedMsg, MSGFLT_ALLOW, nullptr);
    // The dock runs with full rights; the taskbar's menu and the shell's change
    // notices come from a normal-rights Explorer.
    g_ctlMsg = RegisterWindowMessageW(L"SeamlessDock.Control");
    ChangeWindowMessageFilterEx(g_dock, g_ctlMsg, MSGFLT_ALLOW, nullptr);
    ChangeWindowMessageFilterEx(g_dock, kRecycleMsg, MSGFLT_ALLOW, nullptr);
    ChangeWindowMessageFilterEx(g_dock, kAppBarMsg, MSGFLT_ALLOW, nullptr);
    RegisterShellHookWindow(g_dock);
    const DWORD ranges[][2] = {{EVENT_SYSTEM_FOREGROUND, EVENT_SYSTEM_FOREGROUND},
                               {EVENT_SYSTEM_MINIMIZESTART, EVENT_SYSTEM_MINIMIZEEND},
                               {EVENT_OBJECT_SHOW, EVENT_OBJECT_HIDE},
                               {EVENT_OBJECT_CLOAKED, EVENT_OBJECT_UNCLOAKED}};
    for (auto& r : ranges) {
        HWINEVENTHOOK h = SetWinEventHook(r[0], r[1], nullptr, WinEventProc, 0, 0,
                                          WINEVENT_OUTOFCONTEXT | WINEVENT_SKIPOWNPROCESS);
        if (h) g_hooks.push_back(h);
    }

    if (S.recycle) CheckRecycleAsync();
    g_recycleChecked = GetTickCount64();
    WatchRecycle(S.recycle);
    Rebuild(true);
    CheckFullscreen();
    SetTimer(g_dock, kTimerFull, 1000, nullptr);
    SetEvent(g_ready);

    MSG m;
    while (GetMessageW(&m, nullptr, 0, 0) > 0) {
        TranslateMessage(&m);
        DispatchMessageW(&m);
    }
    StopZGuard();

    // A bin check still running posts to a window that is gone; wait for it briefly.
    if (g_recycleThread) {
        WaitForSingleObject(g_recycleThread, 3000);
        CloseHandle(g_recycleThread);
        g_recycleThread = nullptr;
    }
    g_dockSurf.Discard();
    g_popSurf.Discard();
    g_menuSurf.Discard();
    g_titleStops.Reset();
    g_titleRt.Reset();
    g_icons.clear();
    g_formats.clear();
    g_d2d.Reset();
    g_dw.Reset();
    g_dock = nullptr;
    CoUninitialize();
    return 0;
}

}  // namespace dock

using namespace dock;

// Runs only in the dedicated windhawk.exe tool process.
BOOL WhTool_ModInit() {
    g_ready = CreateEventW(nullptr, TRUE, FALSE, nullptr);
    g_thread = CreateThread(nullptr, 0, DockThread, nullptr, 0, nullptr);
    if (!g_thread) {
        Wh_Log(L"CreateThread failed: %u", GetLastError());
        return FALSE;
    }
    WaitForSingleObject(g_ready, 10000);
    return g_dock != nullptr;
}

void WhTool_ModSettingsChanged() {
    if (g_dock) PostMessageW(g_dock, kReloadMsg, 0, 0);
}

void WhTool_ModUninit() {
    if (g_dock) PostMessageW(g_dock, WM_CLOSE, 0, 0);
    if (g_thread) {
        WaitForSingleObject(g_thread, 5000);
        CloseHandle(g_thread);
        g_thread = nullptr;
    }
}

// Windhawk 2 ships the tool mod launcher as a header. Windhawk 1.x does not,
// so it gets the launcher at the end of this file.
#if __has_include(<windhawk_tool_mod.h>)
#include <windhawk_tool_mod.h>
#else

////////////////////////////////////////////////////////////////////////////////
// Windhawk tool mod implementation for mods which don't need to inject to other
// processes or hook other functions. Context:
// https://github.com/ramensoftware/windhawk/wiki/Mods-as-tools:-Running-mods-in-a-dedicated-process

bool g_isToolModProcessLauncher;
HANDLE g_toolModProcessMutex;

void WINAPI EntryPoint_Hook() {
    Wh_Log(L">");
    ExitThread(0);
}

BOOL Wh_ModInit() {
    DWORD sessionId;
    if (ProcessIdToSessionId(GetCurrentProcessId(), &sessionId) && sessionId == 0) {
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
        if (wcscmp(argv[i], L"-service") == 0 || wcscmp(argv[i], L"-service-start") == 0 ||
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
        g_toolModProcessMutex = CreateMutex(nullptr, TRUE, L"windhawk-tool-mod_" WH_MOD_ID);
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

        IMAGE_DOS_HEADER* dosHeader = (IMAGE_DOS_HEADER*)GetModuleHandle(nullptr);
        IMAGE_NT_HEADERS* ntHeaders = (IMAGE_NT_HEADERS*)((BYTE*)dosHeader + dosHeader->e_lfanew);

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
    switch (GetModuleFileName(nullptr, currentProcessPath, ARRAYSIZE(currentProcessPath))) {
        case 0:
        case ARRAYSIZE(currentProcessPath):
            Wh_Log(L"GetModuleFileName failed");
            return;
    }

    WCHAR
    commandLine[MAX_PATH + 2 + (sizeof(L" -tool-mod \"" WH_MOD_ID "\"") / sizeof(WCHAR)) - 1];
    swprintf_s(commandLine, L"\"%s\" -tool-mod \"%s\"", currentProcessPath, WH_MOD_ID);

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
        LPSECURITY_ATTRIBUTES lpProcessAttributes, LPSECURITY_ATTRIBUTES lpThreadAttributes, WINBOOL bInheritHandles,
        DWORD dwCreationFlags, LPVOID lpEnvironment, LPCWSTR lpCurrentDirectory, LPSTARTUPINFOW lpStartupInfo,
        LPPROCESS_INFORMATION lpProcessInformation, PHANDLE hRestrictedUserToken);
    CreateProcessInternalW_t pCreateProcessInternalW =
        (CreateProcessInternalW_t)GetProcAddress(kernelModule, "CreateProcessInternalW");
    if (!pCreateProcessInternalW) {
        Wh_Log(L"No CreateProcessInternalW");
        return;
    }

    STARTUPINFO si{
        .cb = sizeof(STARTUPINFO),
        .dwFlags = STARTF_FORCEOFFFEEDBACK,
    };
    PROCESS_INFORMATION pi;
    if (!pCreateProcessInternalW(nullptr, currentProcessPath, commandLine, nullptr, nullptr, FALSE,
                                 NORMAL_PRIORITY_CLASS, nullptr, nullptr, &si, &pi, nullptr)) {
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

#endif
