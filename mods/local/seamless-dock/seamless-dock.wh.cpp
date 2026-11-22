// ==WindhawkMod==
// @id              seamless-dock
// @name            Seamless Dock
// @description     A floating dock at the bottom of the screen for your pinned and open apps
// @version         0.1.0
// @author          DavidHiFi
// @github          https://github.com/DavidHiFi
// @homepage        https://github.com/DavidHiFi/davids-windhawk-mods
// @donateUrl       https://ko-fi.com/DavidHiFi
// @license         GPL-3.0
// @include         windhawk.exe
// @compilerOptions -lole32 -loleaut32 -luuid -ld2d1 -ldwrite -ldwmapi -luser32 -lgdi32 -lshell32 -lshlwapi -lshcore -lversion -ladvapi32
// ==/WindhawkMod==

// Source code is published under The GNU General Public License v3.0.
//
// For bug reports and feature requests, please open an issue here:
// https://github.com/DavidHiFi/davids-windhawk-mods/issues

// ==WindhawkModReadme==
/*
# Seamless Dock

A floating dock at the bottom of the screen with your pinned apps and the apps
you have open. Your taskbar stays where it is, so you get a clean bar on top
and a dock below, like a Linux desktop.

![Seamless Dock preview](https://raw.githubusercontent.com/DavidHiFi/davids-windhawk-mods/main/media/previews/seamless-dock.png)

## What's new in 0.1.0

- First release: pinned apps, open apps after a thin line, live window
  previews, its own right-click menu, and windows that stop above the dock.
- Works with Seamless Window Manager: tiled windows keep the same gap above
  the dock as they do on the other three sides of the screen.

## Features

- **Pinned apps first.** The dock starts with the apps pinned to your taskbar,
  in the same order. Drag an icon to move it. Pin or unpin from the right-click
  menu.
- **Open apps too.** Apps you have open but did not pin sit after a thin line.
  A dot under an icon means the app is open, and a wider dot marks the one you
  are using.
- **Click like a dock.** Click to open or switch to an app, click again to hide
  it, click an app with several windows to go through them. Middle-click opens
  a new window.
- **Live previews.** Rest the pointer on an open app to see its windows. Click
  one to go to it, or close it from there.
- **Windows stop above it.** Maximized windows end above the dock, so it never
  covers anything. Turn this off to let the dock float over windows instead.
- **Out of the way for games.** The dock hides while a game or video fills the
  screen.
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
- iconSize: 36
  $name: Icon size
  $description: 'Size of each app icon in pixels at 100% scaling. 24 to 64 (Suggested: 36).'
- spacing: 6
  $name: Space between icons
  $description: '0 to 24 (Suggested: 6).'
- bottomGap: 8
  $name: Gap below the dock
  $description: 'Space between the dock and the bottom of the screen. 0 to 48 (Suggested: 8).'
- reserveSpace: true
  $name: Keep windows above the dock
  $description: When on, maximized windows stop above the dock. When off, the dock floats over them.
- showOpenApps: true
  $name: Show open apps
  $description: When on, apps you have open but did not pin show after a thin line. When off, the dock shows pinned apps only.
- previews: true
  $name: Window previews
  $description: When on, resting the pointer on an open app shows live pictures of its windows.
- hoverDelay: 350
  $name: Preview delay
  $description: 'How long the pointer rests on an icon before the preview opens, in milliseconds. 0 to 2000 (Suggested: 350).'
- hideOnFullscreen: true
  $name: Hide for full screen apps
  $description: When on, the dock hides while a game or video fills the screen.
- surfaceOpacity: 60
  $name: Glass tint
  $description: 'How much Mocha color sits over the blur, in percent. 30 to 100 (Suggested: 60).'
- edgeColor: "#585b70"
  $name: Edge color
  $description: Color of the dock edge while the pointer is away, as a hex color.
- hoverColorFrom: "#89b4fa"
  $name: Hover edge start color
  $description: The edge fades from this color to the end color while you point at the dock.
- hoverColorTo: "#cba6f7"
  $name: Hover edge end color
  $description: End color of the hover edge, as a hex color.
- edgeWidth: 2
  $name: Edge width
  $description: 'Edge thickness in pixels at 100% scaling. 0 to 6 (Suggested: 2).'
- fadeMs: 150
  $name: Fade time
  $description: 'How long hover colors take to fade, in milliseconds. 0 to 1000 (Suggested: 150).'
- font: FiraCode Nerd Font
  $name: Font
  $description: Font for app names in previews and menus.
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
    bool reserve = true, showOpen = true, previews = true, hideFull = true;
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

void LoadSettings() {
    S.iconSize = Clamp(Wh_GetIntSetting(L"iconSize"), 24, 64);
    S.spacing = Clamp(Wh_GetIntSetting(L"spacing"), 0, 24);
    S.bottomGap = Clamp(Wh_GetIntSetting(L"bottomGap"), 0, 48);
    S.reserve = Wh_GetIntSetting(L"reserveSpace") != 0;
    S.showOpen = Wh_GetIntSetting(L"showOpenApps") != 0;
    S.previews = Wh_GetIntSetting(L"previews") != 0;
    S.hoverDelay = Clamp(Wh_GetIntSetting(L"hoverDelay"), 0, 2000);
    S.hideFull = Wh_GetIntSetting(L"hideOnFullscreen") != 0;
    S.opacity = Clamp(Wh_GetIntSetting(L"surfaceOpacity"), 30, 100);
    S.edge = ColorSetting(L"edgeColor", 0x585B70);
    S.from = ColorSetting(L"hoverColorFrom", 0x89B4FA);
    S.to = ColorSetting(L"hoverColorTo", 0xCBA6F7);
    S.edgeWidth = Clamp(Wh_GetIntSetting(L"edgeWidth"), 0, 6);
    S.fadeMs = Clamp(Wh_GetIntSetting(L"fadeMs"), 0, 1000);
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

// The same acrylic the clipboard and launcher popups use; our Direct2D tint colors it.
void ApplyBackdrop(HWND h) {
    BOOL dark = TRUE;
    DwmSetWindowAttribute(h, 20 /* DWMWA_USE_IMMERSIVE_DARK_MODE */, &dark, sizeof(dark));
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

void SavePins() {
    std::wstring s;
    for (auto& p : g_pins) s += p.kind + L":" + p.value + L"\n";
    Wh_SetStringValue(L"pins", s.c_str());
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
    for (auto& p : g_pins) ResolvePin(p);
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

bool IconFromWindow(HWND h, int size, Icon& ic) {
    DWORD_PTR r = 0;
    HICON hi = nullptr;
    if (SendMessageTimeoutW(h, WM_GETICON, ICON_BIG, 0, SMTO_ABORTIFHUNG, 100, &r) && r) hi = (HICON)r;
    if (!hi) hi = (HICON)GetClassLongPtrW(h, GCLP_HICON);
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

Icon* GetIcon(const std::wstring& src, const std::wstring& alt, HWND win, int size) {
    std::wstring key = src + L"|" + alt + L"|" + std::to_wstring(size);
    auto it = g_icons.find(key);
    if (it != g_icons.end()) return it->second.px.empty() ? nullptr : &it->second;
    Icon ic;
    if (!IconFromShell(src, size, ic) && !IconFromShell(alt, size, ic) && win) IconFromWindow(win, size, ic);
    auto& slot = g_icons[key];
    slot = std::move(ic);
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
    std::wstring aumid, exe;
};
std::unordered_map<HWND, WinMeta> g_winMeta;
std::set<HWND> g_flash;

struct Item {
    std::wstring key, name, iconSrc, iconAlt;
    std::wstring launchKind, launchValue;  // lnk | aumid | exe
    int pin = -1;
    std::vector<HWND> wins;  // stable order
    HWND top = nullptr;      // most recently used
    bool active = false, flash = false;
    float hoverT = 0, activeT = 0, openT = 0;
    ULONGLONG launchUntil = 0;
};
std::vector<Item> g_items;
int g_pinnedCount = 0;

HWND g_dock, g_pop, g_menu;

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
    for (PCWSTR bad : {L"Progman", L"WorkerW", L"Shell_TrayWnd", L"Shell_SecondaryTrayWnd"})
        if (!wcscmp(cls, bad)) return false;
    wchar_t t[2];
    if (!appWin && InternalGetWindowText(h, t, 2) == 0) return false;
    return true;
}

bool IsHostExe(const std::wstring& exeLower) {
    return exeLower.find(L"\\windowsapps\\") != std::wstring::npos ||
           FileName(exeLower) == L"applicationframehost.exe";
}

bool PinMatches(const Pin& p, const WinMeta& m, const std::wstring& exeLower) {
    if (!p.aumid.empty() && !m.aumid.empty()) return _wcsicmp(p.aumid.c_str(), m.aumid.c_str()) == 0;
    if (!p.exeLower.empty() && p.exeLower == exeLower) return true;
    if (!p.procStart.empty() && FileName(exeLower) == p.procStart) return true;
    return false;
}

void Relayout(bool forceBar = false);

BOOL CALLBACK CollectWin(HWND h, LPARAM lp) {
    if (Eligible(h)) ((std::vector<HWND>*)lp)->push_back(h);
    return TRUE;
}

void Rebuild() {
    std::vector<HWND> zorder;
    EnumWindows(CollectWin, (LPARAM)&zorder);

    std::unordered_map<HWND, WinMeta> meta;
    std::unordered_map<DWORD, std::wstring> exeByPid;
    for (HWND h : zorder) {
        auto it = g_winMeta.find(h);
        if (it != g_winMeta.end()) {
            meta[h] = it->second;
            continue;
        }
        DWORD pid = 0;
        GetWindowThreadProcessId(h, &pid);
        auto e = exeByPid.find(pid);
        if (e == exeByPid.end()) e = exeByPid.emplace(pid, ExeOfPid(pid)).first;
        meta[h] = WinMeta{WindowAumid(h), e->second};
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
            std::wstring key = !m.aumid.empty() ? L"a:" + Lower(m.aumid) : L"e:" + exeLower;
            for (int i = g_pinnedCount; i < (int)items.size() && at < 0; i++)
                if (items[i].key == key) at = i;
            if (at < 0) {
                if (!S.showOpen) continue;
                Item it;
                it.key = key;
                bool host = IsHostExe(exeLower);
                if (!m.aumid.empty()) {
                    it.iconSrc = L"shell:AppsFolder\\" + m.aumid;
                    it.name = ShellDisplayName(it.iconSrc);
                }
                if (!host) it.iconAlt = m.exe;
                if (it.name.empty() && !host) it.name = FileDescription(m.exe);
                if (it.name.empty()) it.name = WindowTitle(h);
                if (it.name.empty()) it.name = StripExt(FileName(m.exe));
                if (host && !m.aumid.empty()) {
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

    g_items = std::move(items);
    Relayout();
}

// ---------------------------------------------------------------------------
// Layout
// ---------------------------------------------------------------------------
struct Layout {
    float s = 1, plate = 48, icon = 36, gap = 6, padX = 10, padTop = 8, dotArea = 10, w = 100, h = 66;
    float divX = -1, radius = 16, plateR = 12, lift = 3;
    std::vector<float> x;
    int iconPx = 36;
} L;

HMONITOR g_mon;
RECT g_monRect{}, g_barRect{};
bool g_appbar = false, g_fullscreen = false;
int g_dragIndex = -1;
float g_dragX = 0, g_dragGrab = 0;

constexpr UINT kAppBarMsg = WM_APP + 2, kReloadMsg = WM_APP + 1;
UINT g_shellMsg, g_taskbarCreatedMsg;

void ComputeLayout(float maxW) {
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
        L.lift = 3;
        L.x.assign(g_items.size(), 0);
        L.divX = -1;
        float x = L.padX;
        for (size_t i = 0; i < g_items.size(); i++) {
            if (i > 0) x += L.gap;
            if ((int)i == g_pinnedCount && g_pinnedCount > 0) {
                float dp = std::max(4.f, L.gap);
                L.divX = x + dp;
                x += dp * 2 + 1;
            }
            L.x[i] = x;
            x += L.plate;
        }
        if (g_items.empty()) x += L.plate;
        L.w = x + L.padX;
        L.h = L.padTop + L.plate + L.dotArea;
        if (L.w * L.s <= maxW || pass == 1) break;
        k = std::max(0.4f, maxW / (L.w * L.s));
    }
    L.iconPx = std::max(16, (int)std::lround(L.icon * L.s));
    L.radius = (float)LiveRadius();
}

void AppBarSetPos(int heightPx, bool force = false);

int ReservePx() {
    int gapPx = (int)std::lround(S.bottomGap * L.s);
    // Reserve up to the dock's top edge only. The window manager adds its own
    // gap above that, so tiled windows sit as far from the dock as from every
    // other screen edge.
    return (int)std::ceil(L.h * L.s) + gapPx;
}

Surface g_dockSurf, g_popSurf, g_menuSurf;

void Relayout(bool forceBar) {
    if (!g_dock) return;
    g_mon = MonitorFromPoint(POINT{0, 0}, MONITOR_DEFAULTTOPRIMARY);
    MONITORINFO mi{sizeof(mi)};
    GetMonitorInfoW(g_mon, &mi);
    g_monRect = mi.rcMonitor;
    ComputeLayout((float)(g_monRect.right - g_monRect.left) - 32);
    int W = (int)std::ceil(L.w * L.s), H = (int)std::ceil(L.h * L.s);
    int bottom = g_monRect.bottom;
    if (S.reserve) {
        AppBarSetPos(ReservePx(), forceBar);
        if (g_appbar) bottom = g_barRect.bottom;
    }
    int gapPx = (int)std::lround(S.bottomGap * L.s);
    int x = g_monRect.left + (g_monRect.right - g_monRect.left - W) / 2;
    int y = bottom - gapPx - H;
    bool show = !g_fullscreen;
    SetWindowPos(g_dock, HWND_TOPMOST, x, y, W, H,
                 SWP_NOACTIVATE | (show ? SWP_SHOWWINDOW : SWP_HIDEWINDOW));
    g_dockSurf.Resize();
    InvalidateRect(g_dock, nullptr, FALSE);
}

// ---------------------------------------------------------------------------
// Appbar: maximized windows stop above the dock
// ---------------------------------------------------------------------------
// Only talk to the shell when the reserved strip really changed. Every SETPOS
// tells the other bars to move, and their answer comes back as ABN_POSCHANGED.
int g_barHeightSent = -1;
RECT g_barMonSent{};
bool g_inBarSetPos = false;

void AppBarRegister() {
    if (g_appbar || !g_dock) return;
    APPBARDATA abd{sizeof(abd)};
    abd.hWnd = g_dock;
    abd.uCallbackMessage = kAppBarMsg;
    g_appbar = SHAppBarMessage(ABM_NEW, &abd) != 0;
}

void AppBarRemove() {
    if (!g_appbar) return;
    APPBARDATA abd{sizeof(abd)};
    abd.hWnd = g_dock;
    SHAppBarMessage(ABM_REMOVE, &abd);
    g_appbar = false;
    g_barHeightSent = -1;
}

void AppBarSetPos(int heightPx, bool force) {
    AppBarRegister();
    if (!g_appbar || g_inBarSetPos) return;
    if (!force && heightPx == g_barHeightSent && EqualRect(&g_barMonSent, &g_monRect)) return;
    g_inBarSetPos = true;
    APPBARDATA abd{sizeof(abd)};
    abd.hWnd = g_dock;
    abd.uEdge = ABE_BOTTOM;
    abd.rc = g_monRect;
    abd.rc.top = abd.rc.bottom - heightPx;
    SHAppBarMessage(ABM_QUERYPOS, &abd);
    abd.rc.top = abd.rc.bottom - heightPx;
    if (force && heightPx == g_barHeightSent && EqualRect(&abd.rc, &g_barRect)) {
        // Another bar moved but our strip is still right: say nothing, or we echo forever.
        g_inBarSetPos = false;
        return;
    }
    SHAppBarMessage(ABM_SETPOS, &abd);
    g_barRect = abd.rc;
    g_barHeightSent = heightPx;
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
        Rebuild();
        return;
    }
}

void UnpinItem(const std::wstring& key) {
    for (auto& it : g_items) {
        if (it.key != key || it.pin < 0) continue;
        g_pins.erase(g_pins.begin() + it.pin);
        SavePins();
        Rebuild();
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

constexpr UINT_PTR kTimerRebuild = 1, kTimerAnim = 2, kTimerHover = 3, kTimerTrack = 4, kTimerFull = 5;
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
D2D1_RECT_F PlateRect(int i) {
    float x = L.x[i];
    if (i == g_dragIndex) x = g_dragX - g_dragGrab;
    float y = L.padTop - L.lift * g_items[i].hoverT;
    return D2D1::RectF(x, y, x + L.plate, y + L.plate);
}

void PaintDock() {
    Surface& s = g_dockSurf;
    if (!s.Ensure()) return;
    s.rt->BeginDraw();
    s.rt->Clear(D2D1::ColorF(0, 0));
    D2D1_RECT_F all = D2D1::RectF(0, 0, L.w, L.h);
    auto tint = s.Solid(kBase, TintAlpha());
    s.rt->FillRectangle(all, tint.Get());

    float ew = (float)S.edgeWidth;
    if (ew > 0) {
        if (g_dockT < 1) StrokeRound(s, all, L.radius, ew, s.Solid(S.edge, 1 - g_dockT).Get());
        if (g_dockT > 0) StrokeRound(s, all, L.radius, ew, s.Grad(all, g_dockT).Get());
    }

    if (L.divX >= 0) {
        float h = L.plate * 0.6f;
        float cy = L.padTop + L.plate / 2;
        s.rt->FillRectangle(D2D1::RectF(L.divX, cy - h / 2, L.divX + 1, cy + h / 2), s.Solid(kSurface1).Get());
    }

    ULONGLONG now = GetTickCount64();
    auto drawItem = [&](int i) {
        Item& it = g_items[i];
        D2D1_RECT_F r = PlateRect(i);
        float fillA = Lerp(0.55f, 0.8f, std::max(it.hoverT, it.activeT));
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

        float dotY = L.padTop + L.plate + L.dotArea / 2;
        float ox = (L.x[i] + L.plate / 2);
        if (i == g_dragIndex) ox = cx;
        if (it.launchUntil > now && it.wins.empty()) {
            float a = 0.35f + 0.65f * (0.5f + 0.5f * std::sin((float)(now % 100000) / 140.f));
            s.rt->FillEllipse(D2D1::Ellipse(D2D1::Point2F(ox, dotY), 2, 2), s.Solid(S.from, a).Get());
        } else if (!it.wins.empty()) {
            if (it.flash) {
                s.rt->FillEllipse(D2D1::Ellipse(D2D1::Point2F(ox, dotY), 2.5f, 2.5f), s.Solid(kPeach).Get());
            } else {
                float half = Lerp(2, 7, it.activeT);
                D2D1_RECT_F d = D2D1::RectF(ox - half, dotY - 2, ox + half, dotY + 2);
                if (it.activeT > 0.01f)
                    s.rt->FillRoundedRectangle(D2D1::RoundedRect(d, 2, 2), s.Grad(d, 1).Get());
                else
                    s.rt->FillEllipse(D2D1::Ellipse(D2D1::Point2F(ox, dotY), 2, 2), s.Solid(S.from).Get());
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
    float x = pxPt.x / L.s, y = pxPt.y / L.s;
    if (y < 0 || y > L.h) return -1;
    for (size_t i = 0; i < g_items.size(); i++) {
        float l = L.x[i] - L.gap / 2, r = L.x[i] + L.plate + L.gap / 2;
        if (x >= l && x < r) return (int)i;
    }
    return -1;
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
        float bw = 208, imgH = 118, titleH = 26, gap = 8;
        float maxW = (g_monRect.right - g_monRect.left) / L.s - 32;
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
    RECT dr;
    GetWindowRect(g_dock, &dr);
    int cx = dr.left + (int)std::lround((L.x[i] + L.plate / 2) * L.s);
    int x = std::clamp(cx - W / 2, (int)g_monRect.left + 8, (int)g_monRect.right - W - 8);
    int y = dr.top - (int)std::lround(8 * L.s) - H;
    SetWindowPos(g_pop, HWND_TOPMOST, x, y, W, H, SWP_NOACTIVATE | SWP_SHOWWINDOW);
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

void CloseMenu() {
    if (g_menu && IsWindowVisible(g_menu)) ShowWindow(g_menu, SW_HIDE);
    M.rows.clear();
    M.hot = -1;
    StartAnim();
}

void OpenMenu(int i) {
    if (!g_menu || i < 0 || i >= (int)g_items.size()) return;
    HidePopup();
    Item& it = g_items[i];
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
    if (!wins.empty()) {
        M.rows.push_back(MenuRow{L"", L"", true});
        M.rows.push_back(MenuRow{wins.size() > 1 ? L"Close all windows" : L"Close window", L"\xE8BB", false, false,
                                 [wins] {
                                     for (HWND h : wins) CloseWin(h);
                                 }});
    }

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
    RECT dr;
    GetWindowRect(g_dock, &dr);
    int cx = dr.left + (int)std::lround((L.x[i] + L.plate / 2) * s);
    int x = std::clamp(cx - W / 2, (int)g_monRect.left + 8, (int)g_monRect.right - W - 8);
    int yy = dr.top - (int)std::lround(8 * s) - H;
    SetWindowPos(g_menu, HWND_TOPMOST, x, yy, W, H, SWP_SHOWWINDOW);
    g_menuSurf.Resize();
    SetForegroundWindow(g_menu);
    InvalidateRect(g_menu, nullptr, FALSE);
    StartAnim();
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
        SetWindowPos(g_dock, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
    }
}

// ---------------------------------------------------------------------------
// Dock window
// ---------------------------------------------------------------------------
std::vector<HWINEVENTHOOK> g_hooks;

void CALLBACK WinEventProc(HWINEVENTHOOK, DWORD ev, HWND h, LONG idObj, LONG idChild, DWORD, DWORD) {
    if (idObj != OBJID_WINDOW || idChild != CHILDID_SELF || !h) return;
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
    float unit = L.plate + L.gap;
    int slot = std::clamp((int)std::floor((x - g_dragGrab + L.plate / 2 - L.padX + L.gap / 2) / unit), 0,
                          g_pinnedCount - 1);
    if (slot != g_dragIndex && slot >= 0) {
        Pin p = g_pins[g_dragIndex];
        g_pins.erase(g_pins.begin() + g_dragIndex);
        g_pins.insert(g_pins.begin() + slot, p);
        Item it = g_items[g_dragIndex];
        g_items.erase(g_items.begin() + g_dragIndex);
        g_items.insert(g_items.begin() + slot, it);
        for (int i = 0; i < g_pinnedCount; i++) g_items[i].pin = i;
        g_dragIndex = slot;
        g_hover = slot;
    }
    InvalidateRect(g_dock, nullptr, FALSE);
}

LRESULT CALLBACK DockProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) {
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
        // Explorer restarted: the appbar and the shell hook went with it.
        g_appbar = false;
        RegisterShellHookWindow(hwnd);
        Relayout();
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
            if (g_press >= 0 && g_dragIndex < 0 && g_press < g_pinnedCount && !g_pressMiddle &&
                std::abs(pt.x - g_pressPt.x) > 6 * L.s) {
                g_dragIndex = g_press;
                g_dragGrab = g_pressPt.x / L.s - L.x[g_press];
                HidePopup();
                KillTimer(hwnd, kTimerHover);
            }
            if (g_dragIndex >= 0) {
                DragTo(pt.x / L.s);
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
            return 0;
        case WM_LBUTTONUP:
        case WM_MBUTTONUP: {
            int pressed = g_press;
            g_press = -1;
            if (GetCapture() == hwnd) ReleaseCapture();
            if (g_dragIndex >= 0) {
                EndDrag(true);
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
        case WM_RBUTTONUP:
            OpenMenu(ItemAt(POINT{GET_X_LPARAM(lp), GET_Y_LPARAM(lp)}));
            return 0;
        case WM_TIMER:
            switch (wp) {
                case kTimerRebuild:
                    KillTimer(hwnd, kTimerRebuild);
                    g_rebuildPending = false;
                    Rebuild();
                    StartAnim();
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
                    if (PopupVisible() && pt.y >= pr.bottom && pt.y < dr.top && pt.x >= pr.left && pt.x < pr.right)
                        in = true;
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
                case kTimerFull:
                    CheckFullscreen();
                    break;
            }
            return 0;
        case kAppBarMsg:
            if (wp == ABN_POSCHANGED) {
                Relayout(true);
            } else if (wp == ABN_FULLSCREENAPP) {
                CheckFullscreen();
            }
            return 0;
        case WM_WINDOWPOSCHANGED:
            if (g_appbar) {
                APPBARDATA abd{sizeof(abd)};
                abd.hWnd = hwnd;
                SHAppBarMessage(ABM_WINDOWPOSCHANGED, &abd);
            }
            break;
        case WM_DPICHANGED:
        case WM_DISPLAYCHANGE:
            g_icons.clear();
            g_formats.clear();
            Relayout();
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
            if (!S.reserve) AppBarRemove();
            Rebuild();
            return 0;
        }
        case WM_CLOSE:
            DestroyWindow(hwnd);
            return 0;
        case WM_DESTROY:
            for (auto h : g_hooks) UnhookWinEvent(h);
            g_hooks.clear();
            DeregisterShellHookWindow(hwnd);
            AppBarRemove();
            UnregisterThumbs();
            if (g_pop) DestroyWindow(g_pop);
            if (g_menu) DestroyWindow(g_menu);
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

    LoadSettings();
    LoadPins();
    g_mon = MonitorFromPoint(POINT{0, 0}, MONITOR_DEFAULTTOPRIMARY);

    g_dock = CreateWindowExW(WS_EX_TOOLWINDOW | WS_EX_TOPMOST | WS_EX_NOACTIVATE, L"SeamlessDock", L"Seamless Dock",
                             WS_POPUP, 0, 0, 10, 10, nullptr, nullptr, inst, nullptr);
    g_pop = CreateWindowExW(WS_EX_TOOLWINDOW | WS_EX_TOPMOST | WS_EX_NOACTIVATE, L"SeamlessDockPreview",
                            L"Seamless Dock preview", WS_POPUP, 0, 0, 10, 10, nullptr, nullptr, inst, nullptr);
    g_menu = CreateWindowExW(WS_EX_TOOLWINDOW | WS_EX_TOPMOST, L"SeamlessDockMenu", L"Seamless Dock menu", WS_POPUP,
                             0, 0, 10, 10, nullptr, nullptr, inst, nullptr);
    if (!g_dock || !g_pop || !g_menu) {
        Wh_Log(L"CreateWindow failed: %u", GetLastError());
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

    Rebuild();
    CheckFullscreen();
    SetTimer(g_dock, kTimerFull, 1000, nullptr);
    SetEvent(g_ready);

    MSG m;
    while (GetMessageW(&m, nullptr, 0, 0) > 0) {
        TranslateMessage(&m);
        DispatchMessageW(&m);
    }

    g_dockSurf.Discard();
    g_popSurf.Discard();
    g_menuSurf.Discard();
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
