// ==WindhawkMod==
// @id              seamless-compiz-cube
// @name            Seamless Compiz Cube
// @description     Rounded 3D desktop cube with Mocha borders, switching desktops through Seamless Window Manager
// @version         1.0.10
// @author          DavidHiFi, Soham
// @github          https://github.com/DavidHiFi
// @homepage        https://github.com/DavidHiFi/davids-windhawk-mods
// @donateUrl       https://ko-fi.com/DavidHiFi
// @license         MIT
// @include         explorer.exe
// @architecture    x86-64
// @compilerOptions -lole32 -loleaut32 -lwindowsapp -ldwmapi -luuid -luser32 -lgdi32 -lcomctl32 -ld3d11 -ld2d1 -ldxgi -ldxguid -ldwrite -lshell32 -luxtheme -lcomdlg32 -limm32 -lpropsys -lwindowscodecs -lshcore -ladvapi32 -lshlwapi
// ==/WindhawkMod==

// Based on Compiz Desktop Cube for Windows 11 by Soham (MIT License):
// https://windhawk.net/mods/compiz-desktop-cube
//
// For bug reports and feature requests, please open an issue here:
// https://github.com/DavidHiFi/davids-windhawk-mods/issues

// ==WindhawkModReadme==
/*
# Seamless Compiz Cube

A 3D glass desktop cube for Windows 11 with rounded faces, blue and mauve borders and FiraCode text. Turning the cube switches workspaces through Seamless Window Manager.

![Seamless Compiz Cube preview](https://raw.githubusercontent.com/DavidHiFi/davids-windhawk-mods/main/media/previews/seamless-compiz-cube.gif)

This is a fork of Soham's Compiz Desktop Cube. The cube itself, the live desktop capture and the gestures are Soham's work. This version adds the look, the borders, the font options, the settings window and the Seamless Window Manager switching.

## Features
- **Rounded faces.** Every face is clipped to a rounded rectangle. The radius is a setting (16 by default) and grows with the cube as it opens, so the full-screen desktop stays square until you start dragging.
- **Borders that react.** Each face has a resting border. The face you point at, and the face the cube will land on, get a blue to mauve gradient border that fades in and out. You choose the width, the colors and which faces light up.
- **Switches through Seamless Window Manager.** When the cube lands on a face, it sends that desktop's "Switch to desktop N" hotkey from Seamless Window Manager. If that mod is off or its hotkey does nothing, the cube falls back to the normal Windows shortcut.
- **Fonts.** The badges, labels and toasts use FiraCode Nerd Font Medium at 13 by default. Family, weight and size are settings. If the font is not installed, Segoe UI is used.
- **Mocha colors.** Face accents, the window switcher glow, badges, the add and remove zones and the toasts all use the same palette as the rest of the desktop.
- **Settings window.** Right-click the tray icon and choose Settings, or open the mod's settings in Windhawk. Same layout as the other Seamless mods.

## How to use
1. Press and hold the left mouse button on empty space of the taskbar.
2. Drag up. The desktop shrinks into the cube.
3. Drag left or right to turn it. After a moment, up or down tilts it. The mouse wheel zooms.
4. Release. The cube snaps to the nearest face and switches to that desktop. A quick flick also switches. Escape cancels.
5. While the cube is open, right-click the right edge of the screen to add a desktop, or the left edge to remove the last one.

## Setup
- Windows 11 and Windhawk 1.4 or newer.
- For switching through Seamless Window Manager, install and enable it. Leave its "Switch to desktop N" hotkeys on their defaults (Ctrl+Alt+Shift+1 to 9) or set them to anything with at least one modifier. Desktops 10 and up use the Windows shortcut.

## Notes
- Seamless Window Manager has no workspace layer of its own. It only has the "Switch to desktop N" hotkeys, so that is what the cube uses. Adding and removing desktops still uses the Windows shortcuts.
- The real taskbar is hidden from the capture, so every face is the full desktop. The taskbar comes back as soon as the gesture ends.
- The live desktop is streamed into the front face and the blurred background. Other desktops are rebuilt from the wallpaper and a capture of each window. Windows cannot render apps of other desktops, so those faces cannot be live.
- The overlay is hidden from screenshots and recorders on purpose. Turn on "Screen Recording Mode" to make it visible.
- The Windows slide animation is hidden only while the cube switches desktops. Your Windows animation setting is never changed.
- If you still see a slide, raise "Switch Settle Delay".

## Credits
- Compiz Desktop Cube for Windows 11 by Soham (MIT License), which this mod is based on.
- Styling, borders, fonts, settings window and Seamless Window Manager switching by DavidHiFi.
*/
// ==/WindhawkModReadme==

// ==WindhawkModSettings==
/*
- CornerRadius: 16
  $name: Corner radius
  $description: "0 to 48 (Suggested: 16). How round the faces are, in pixels. It grows with the cube as it opens."
- BorderWidth: 3
  $name: Border width
  $description: "0 to 8 (Suggested: 3). Thickness of the border around each face. 0 turns the borders off."
- RestingBorderColor: "#CC7F849C"
  $name: Resting border color
  $description: "The border of a face that is not hovered or selected. In hexadecimal, like #CC7F849C."
- ActiveBorderStart: "#89B4FA"
  $name: Selected border start color
  $description: "First color of the hovered and selected border gradient. In hexadecimal, like #89B4FA."
- ActiveBorderEnd: "#CBA6F7"
  $name: Selected border end color
  $description: "Second color of the hovered and selected border gradient. In hexadecimal, like #CBA6F7."
- BorderHighlight: "0"
  $name: Highlighted faces
  $description: Which faces get the gradient border.
  $options:
  - "0": Hovered and selected
  - "1": Hovered only
  - "2": Selected only
- BorderFadeMs: 150
  $name: Border fade time
  $description: "0 to 1000 (Suggested: 150). Milliseconds for the border to fade between resting and selected."
- SwitchMethod: "0"
  $name: Switch desktops with
  $description: Seamless Window Manager sends its own "Switch to desktop N" hotkey. If it is off or does not react, the Windows shortcut is used.
  $options:
  - "0": Seamless Window Manager
  - "1": Windows shortcut only
- FontFamily: FiraCode Nerd Font
  $name: Font
  $description: Font for badges, labels and toasts. If it is not installed, Segoe UI is used.
- FontWeight: "500"
  $name: Font weight
  $description: Weight of the cube text.
  $options:
  - "100": Thin
  - "200": Extra light
  - "300": Light
  - "350": Semi light
  - "400": Normal
  - "500": Medium
  - "600": Semi bold
  - "700": Bold
  - "800": Extra bold
  - "900": Black
  - "950": Extra black
- FontSize: 13
  $name: Font size
  $description: "8 to 24 (Suggested: 13). Size of the cube text, in pixels at 100% scaling."
- ActivationThreshold: 10
  $name: Drag activation distance (px)
  $description: Distance you must drag away from the taskbar before the shrink starts.
- HorizontalSensitivity: 45
  $name: Horizontal rotation sensitivity (%)
  $description: Degrees of yaw per pixel of horizontal mouse movement.
- VerticalSensitivity: 35
  $name: Vertical tilt sensitivity (%)
  $description: Degrees of pitch per pixel of vertical mouse movement.
- EnableVerticalRotation: true
  $name: Enable vertical tilt
  $description: Allow tilting the cube up and down.
- MaxTiltAngle: 60
  $name: Maximum tilt angle (degrees)
  $description: How far the cube can be tilted. It springs back to level on release.
- InvertHorizontal: false
  $name: Invert horizontal drag
  $description: By default dragging right shows the desktop on the left (like grabbing the cube). Enable to reverse.
- InvertVertical: false
  $name: Invert vertical drag
  $description: Reverse the tilt direction.
- WrapAround: true
  $name: Wrap around
  $description: Treat the desktops as a loop. When off, the cube stops (rubber band) at the first and last desktop.
- FaceSize: 66
  $name: Cube face size (% of screen width)
  $description: Width of each face of a 4 sided cube. Prisms with other face counts are sized to match. 30 to 90.
- ShrinkDistance: 260
  $name: Shrink distance (px)
  $description: How far you drag up for the desktop to shrink completely into the cube.
- AutoHideTaskbarFix: true
  $name: Re-hide auto-hide taskbar
  $description: After the gesture, an auto-hide taskbar is hidden again right away and ready for the next gesture.
- RecordingMode: false
  $name: Screen recording mode
  $description: Makes the cube visible to screen recorders and screenshots. Normally the cube hides itself from capture so the live view never films itself. In this mode the desktop on the front face is a still picture instead of live.
- Perspective: 1100
  $name: Camera perspective distance (px)
  $description: Lower values give stronger 3D distortion. Minimum 700.
- DragSmoothing: 35
  $name: Drag smoothing (ms)
  $description: How softly the cube follows the mouse. 0 means it sticks to the mouse exactly.
- SnapSpeed: 90
  $name: Snap speed (%)
  $description: Speed of the snap-to-face spring.
- SnapBounce: 30
  $name: Snap bounce (%)
  $description: Overshoot when the cube settles on a face. 0 is no bounce.
- ZoomAnimation: true
  $name: Zoom open and close animation
  $description: The desktop shrinks gradually into the cube while you drag and grows back on release.
- ZoomSpeed: 90
  $name: Zoom speed (%)
  $description: Speed of the open and close zoom.
- CloseFadeDuration: 140
  $name: Close fade duration (ms)
  $description: Final crossfade from the cube to the real desktop. 0 for instant.
- FlickToSwitch: true
  $name: Flick to switch
  $description: A fast flick switches desktops even if the cube was not rotated far enough.
- FlickStrength: 100
  $name: Flick strength (%)
  $description: How strongly mouse speed at release pushes the cube to the next face.
- SwitchAngle: 25
  $name: Switch angle (degrees)
  $description: Rotation needed before the cube commits to the next face when you release slowly.
- BackgroundBlur: true
  $name: Enable background blur
  $description: Blur the desktop behind the cube using a GPU Gaussian blur.
- BlurStrength: 28
  $name: Blur strength
  $description: Standard deviation of the background blur.
- BackgroundDim: 25
  $name: Background dim (%)
  $description: Dark tint over the blurred background.
- BackgroundParallax: true
  $name: Background parallax
  $description: The blurred background drifts slightly as the cube turns.
- FaceBrightness: 100
  $name: Face shading (%)
  $description: How much faces turning away are darkened. The front face is never darkened.
- ShowDesktopLabels: true
  $name: Show desktop badges
  $description: Show a "Desktop N" badge at the top of each face.
- FaceGap: 14
  $name: Gap between faces (%)
  $description: Empty space between neighbouring faces. 0 closes the prism.
- FrontFaceOpacity: 100
  $name: Front face opacity (%)
  $description: How solid the face looking at you is.
- SideFaceOpacity: 55
  $name: Side face opacity (%)
  $description: Opacity of the faces at the sides (translucent glass).
- BackFaceOpacity: 10
  $name: Far faces opacity (%)
  $description: Opacity of the faces on the far side (seen through the gap).
- HorizontalFirst: true
  $name: Horizontal first
  $description: The cube first only turns left/right. Vertical tilt unlocks afterwards.
- VerticalUnlockDelay: 350
  $name: Vertical unlock delay (ms)
  $description: Time after the cube opens before up/down tilting is enabled.
- ShowShadow: true
  $name: Show floor shadow
  $description: Soft shadow below the cube.
- TextureQuality: 100
  $name: Face texture quality (%)
  $description: Resolution of face textures relative to your screen (capped at 1920 wide). 25 to 100.
- SuppressSystemAnimation: true
  $name: Suppress Windows desktop slide animation
  $description: Hides the Windows desktop slide animation only while the cube switches desktops. Your Windows "Animation effects" setting is never changed.
- SwitchSettleDelay: 120
  $name: Switch settle delay (ms)
  $description: Extra time the overlay stays up after Windows reports the new desktop.
- FrameRateLimit: 0
  $name: Frame rate limit (FPS)
  $description: 0 means match the monitor refresh rate exactly (recommended).
- WheelAction: "0"
  $name: Mouse wheel action
  $description: What the mouse wheel does while you drag the cube. 0 zooms the cube in and out. 1 is the Alt+Tab style window switcher (uses more resources). 2 leaves the wheel alone.
  $options:
  - "0": Zoom the cube
  - "1": Window switcher
  - "2": Off
- EdgeDesktopControl: true
  $name: Right-click edges to add / remove desktops
  $description: While the cube is open, right-click the right edge to add a desktop and the left edge to remove the last one.
- EdgeZoneWidth: 10
  $name: Edge zone width (% of screen width)
  $description: Width of the add / remove zones once they have appeared. 4 to 25.
- EdgeRevealWidth: 40
  $name: Edge reveal distance (pixels)
  $description: The zones stay invisible until the pointer is this close to the left or right screen edge. 4 to 300.
- WheelZoomStep: 10
  $name: Wheel zoom step (%)
  $description: How much one wheel notch zooms the cube.
- RememberZoom: false
  $name: Remember zoom level
  $description: Keep the wheel zoom for the next time you open the cube.
- BackgroundRefreshRate: 15
  $name: Blurred background refresh (Hz)
  $description: How often the blurred live background is redrawn. Lower saves power and GPU time. 1 to 60.
- IdlePowerSave: true
  $name: Idle power saving
  $description: While the cube is held still and nothing moves, the render loop slows to about 30 Hz. It returns to full refresh as soon as anything moves.
- AltTabLift: 90
  $name: Window lift (px)
  $description: How far the windows rise off the face in the window switcher. The selected one rises most.
- LiveMethod: "0"
  $name: Live capture method
  $description: Troubleshooting. 0 tries Desktop Duplication then GDI. 2 forces the slower but simpler GDI capture.
  $options:
  - "0": Automatic
  - "1": Desktop Duplication
  - "2": GDI
- SettingsWindow:
  - settingsGlass: true
    $name: Blurred settings window
    $description: On, the settings window is see-through glass with Windows acrylic behind it. Off, it is solid. Applies when you save.
  - nativeSettingsTitleBar: false
    $name: Native Windows title bar
    $description: Use the Windows title bar and window buttons for this settings window. Applies when you save.
  - settingsTrayIcon: true
    $name: Tray icon
    $description: A cube icon in the system tray. Click it to open these settings, right-click it for a menu.
  $name: Settings window
- EnableDebugLogging: false
  $name: Enable diagnostic logging
  $description: Write detailed traces to the Windhawk log.
*/
// ==/WindhawkModSettings==

// Target Windows 10 and later. Defined here (before any SDK header) instead of through compiler flags.
#ifndef WINVER
#define WINVER 0x0A00
#endif
#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0A00
#endif

#include <windows.h>
#include <windowsx.h>
#include <dwmapi.h>
#include <commctrl.h>
#include <shobjidl.h>
#include <shellapi.h>
#include <uiautomation.h>
#include <wincodec.h>
#include <d3d11.h>
#include <d2d1_1.h>
#include <d2d1effects.h>
#include <dwrite.h>
#include <dxgi.h>
#include <dxgi1_2.h>

#include <windhawk_api.h>

#include <windhawk_utils.h>

#ifndef WS_EX_NOREDIRECTIONBITMAP
#define WS_EX_NOREDIRECTIONBITMAP 0x00200000L
#endif
#ifndef WDA_EXCLUDEFROMCAPTURE
#define WDA_EXCLUDEFROMCAPTURE 0x00000011
#endif
#ifndef PW_RENDERFULLCONTENT
#define PW_RENDERFULLCONTENT 0x00000002
#endif

#include <atomic>
#include <cmath>
#include <cstdint>
#include <chrono>
#include <string>
#include <vector>
#include <memory>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>
#include <mutex>
#include <optional>
#include <cwctype>
#ifndef RRF_SUBKEY_WOW64_64KEY
#define RRF_SUBKEY_WOW64_64KEY 0x00010000
#endif

// ===========================================================================
// Settings window: the Seamless Launchpad settings GUI, the standard for every
// DavidHiFi mod. Generated by work\2026-11-12-compiz-cube\fork\setgen.py.
// ===========================================================================
#include <map>
#include <atomic>
#include <memory>
#include <set>
#ifndef SCC_SETTINGS_NO_IMAGEBASE

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

extern "C" IMAGE_DOS_HEADER __ImageBase;
#endif
namespace sccset {
// The settings window, from the tray icon and Windhawk. It shows the same settings as
// Windhawk's page for this mod and saves them through windhawk-cli, so the two
// stay in step. Writing a mod's settings takes admin rights, so the save runs
// the CLI elevated (silently where UAC prompts are off).

constexpr WCHAR kSettingsClass[] = L"WindhawkSeamlessCompizCubeSettings";
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
// Generated by test-settings\gen_table.py from src\00-header.cpp.
static std::vector<SetField> Set_MakeFields() {
    using K = SetField;
    return {
{K::Number, L"CornerRadius", L"Corner radius", L"0 to 48 (Suggested: 16). How round the faces are, in pixels. It grows with the cube as it opens.", L"16", {}, 0, 48, 0, L"Faces and borders"},
{K::Number, L"BorderWidth", L"Border width", L"0 to 8 (Suggested: 3). Thickness of the border around each face. 0 turns the borders off.", L"3", {}, 0, 8, 0, L"Faces and borders"},
{K::Choice, L"BorderHighlight", L"Highlighted faces", L"Which faces get the gradient border.", L"0", {{L"0", L"Hovered and selected"}, {L"1", L"Hovered only"}, {L"2", L"Selected only"}}, 0, 100, 0, L"Faces and borders"},
{K::Number, L"BorderFadeMs", L"Border fade time", L"0 to 1000 (Suggested: 150). Milliseconds for the border to fade between resting and selected.", L"150", {}, 0, 1000, 0, L"Faces and borders"},
{K::Color, L"RestingBorderColor", L"Resting border color", L"The border of a face that is not hovered or selected. In hexadecimal, like #CC7F849C.", L"#CC7F849C", {}, 0, 100, 0, L"Faces and borders"},
{K::Color, L"ActiveBorderStart", L"Selected border start color", L"First color of the hovered and selected border gradient. In hexadecimal, like #89B4FA.", L"#89B4FA", {}, 0, 100, 0, L"Faces and borders"},
{K::Color, L"ActiveBorderEnd", L"Selected border end color", L"Second color of the hovered and selected border gradient. In hexadecimal, like #CBA6F7.", L"#CBA6F7", {}, 0, 100, 0, L"Faces and borders"},
{K::Number, L"FaceSize", L"Cube face size (% of screen width)", L"Width of each face of a 4 sided cube. Prisms with other face counts are sized to match. 30 to 90.", L"66", {}, 30, 90, 0, L"Faces"},
{K::Number, L"FaceGap", L"Gap between faces (%)", L"Empty space between neighbouring faces. 0 closes the prism.", L"14", {}, 0, 60, 0, L"Faces"},
{K::Number, L"FaceBrightness", L"Face shading (%)", L"How much faces turning away are darkened. The front face is never darkened.", L"100", {}, 0, 100, 0, L"Faces"},
{K::Number, L"FrontFaceOpacity", L"Front face opacity (%)", L"How solid the face looking at you is.", L"100", {}, 10, 100, 0, L"Faces"},
{K::Number, L"SideFaceOpacity", L"Side face opacity (%)", L"Opacity of the faces at the sides (translucent glass).", L"55", {}, 0, 100, 0, L"Faces"},
{K::Number, L"BackFaceOpacity", L"Far faces opacity (%)", L"Opacity of the faces on the far side (seen through the gap).", L"10", {}, 0, 100, 0, L"Faces"},
{K::Check, L"ShowShadow", L"Show floor shadow", L"Soft shadow below the cube.", L"1", {}, 0, 100, 0, L"Faces"},
{K::Check, L"ShowDesktopLabels", L"Show desktop badges", L"Show a \"Desktop N\" badge at the top of each face.", L"1", {}, 0, 100, 0, L"Faces"},
{K::Number, L"TextureQuality", L"Face texture quality (%)", L"Resolution of face textures relative to your screen (capped at 1920 wide). 25 to 100.", L"100", {}, 25, 100, 0, L"Faces"},
{K::Check, L"BackgroundBlur", L"Enable background blur", L"Blur the desktop behind the cube using a GPU Gaussian blur.", L"1", {}, 0, 100, 0, L"Backdrop"},
{K::Number, L"BlurStrength", L"Blur strength", L"Standard deviation of the background blur.", L"28", {}, 1, 200, 0, L"Backdrop"},
{K::Number, L"BackgroundDim", L"Background dim (%)", L"Dark tint over the blurred background.", L"25", {}, 0, 100, 0, L"Backdrop"},
{K::Check, L"BackgroundParallax", L"Background parallax", L"The blurred background drifts slightly as the cube turns.", L"1", {}, 0, 100, 0, L"Backdrop"},
{K::Number, L"BackgroundRefreshRate", L"Blurred background refresh (Hz)", L"How often the blurred live background is redrawn. Lower saves power and GPU time. 1 to 60.", L"15", {}, 1, 60, 0, L"Backdrop"},
{K::Text, L"FontFamily", L"Font", L"Font for badges, labels and toasts. If it is not installed, Segoe UI is used.", L"FiraCode Nerd Font", {}, 0, 100, 1, L"Cube text"},
{K::Choice, L"FontWeight", L"Font weight", L"Weight of the cube text.", L"500", {{L"100", L"Thin"}, {L"200", L"Extra light"}, {L"300", L"Light"}, {L"350", L"Semi light"}, {L"400", L"Normal"}, {L"500", L"Medium"}, {L"600", L"Semi bold"}, {L"700", L"Bold"}, {L"800", L"Extra bold"}, {L"900", L"Black"}, {L"950", L"Extra black"}}, 0, 100, 1, L"Cube text"},
{K::Number, L"FontSize", L"Font size", L"8 to 24 (Suggested: 13). Size of the cube text, in pixels at 100% scaling.", L"13", {}, 8, 24, 1, L"Cube text"},
{K::Number, L"ActivationThreshold", L"Drag activation distance (px)", L"Distance you must drag away from the taskbar before the shrink starts.", L"10", {}, 1, 600, 2, L"Dragging"},
{K::Number, L"HorizontalSensitivity", L"Horizontal rotation sensitivity (%)", L"Degrees of yaw per pixel of horizontal mouse movement.", L"45", {}, 1, 1000, 2, L"Dragging"},
{K::Number, L"VerticalSensitivity", L"Vertical tilt sensitivity (%)", L"Degrees of pitch per pixel of vertical mouse movement.", L"35", {}, 1, 1000, 2, L"Dragging"},
{K::Check, L"EnableVerticalRotation", L"Enable vertical tilt", L"Allow tilting the cube up and down.", L"1", {}, 0, 100, 2, L"Dragging"},
{K::Number, L"MaxTiltAngle", L"Maximum tilt angle (degrees)", L"How far the cube can be tilted. It springs back to level on release.", L"60", {}, 5, 85, 2, L"Dragging"},
{K::Check, L"InvertHorizontal", L"Invert horizontal drag", L"By default dragging right shows the desktop on the left (like grabbing the cube). Enable to reverse.", L"0", {}, 0, 100, 2, L"Dragging"},
{K::Check, L"InvertVertical", L"Invert vertical drag", L"Reverse the tilt direction.", L"0", {}, 0, 100, 2, L"Dragging"},
{K::Check, L"HorizontalFirst", L"Horizontal first", L"The cube first only turns left/right. Vertical tilt unlocks afterwards.", L"1", {}, 0, 100, 2, L"Dragging"},
{K::Number, L"VerticalUnlockDelay", L"Vertical unlock delay (ms)", L"Time after the cube opens before up/down tilting is enabled.", L"350", {}, 0, 3000, 2, L"Dragging"},
{K::Check, L"WrapAround", L"Wrap around", L"Treat the desktops as a loop. When off, the cube stops (rubber band) at the first and last desktop.", L"1", {}, 0, 100, 2, L"Dragging"},
{K::Check, L"FlickToSwitch", L"Flick to switch", L"A fast flick switches desktops even if the cube was not rotated far enough.", L"1", {}, 0, 100, 2, L"Flick and landing"},
{K::Number, L"FlickStrength", L"Flick strength (%)", L"How strongly mouse speed at release pushes the cube to the next face.", L"100", {}, 0, 500, 2, L"Flick and landing"},
{K::Number, L"SwitchAngle", L"Switch angle (degrees)", L"Rotation needed before the cube commits to the next face when you release slowly.", L"25", {}, 5, 85, 2, L"Flick and landing"},
{K::Choice, L"WheelAction", L"Mouse wheel action", L"What the mouse wheel does while you drag the cube. 0 zooms the cube in and out. 1 is the Alt+Tab style window switcher (uses more resources). 2 leaves the wheel alone.", L"0", {{L"0", L"Zoom the cube"}, {L"1", L"Window switcher"}, {L"2", L"False"}}, 0, 100, 2, L"Wheel and edges"},
{K::Number, L"WheelZoomStep", L"Wheel zoom step (%)", L"How much one wheel notch zooms the cube.", L"10", {}, 1, 50, 2, L"Wheel and edges"},
{K::Check, L"RememberZoom", L"Remember zoom level", L"Keep the wheel zoom for the next time you open the cube.", L"0", {}, 0, 100, 2, L"Wheel and edges"},
{K::Check, L"EdgeDesktopControl", L"Right-click edges to add / remove desktops", L"While the cube is open, right-click the right edge to add a desktop and the left edge to remove the last one.", L"1", {}, 0, 100, 2, L"Wheel and edges"},
{K::Number, L"EdgeZoneWidth", L"Edge zone width (% of screen width)", L"Width of the add / remove zones once they have appeared. 4 to 25.", L"10", {}, 4, 25, 2, L"Wheel and edges"},
{K::Number, L"EdgeRevealWidth", L"Edge reveal distance (pixels)", L"The zones stay invisible until the pointer is this close to the left or right screen edge. 4 to 300.", L"40", {}, 4, 300, 2, L"Wheel and edges"},
{K::Number, L"AltTabLift", L"Window lift (px)", L"How far the windows rise off the face in the window switcher. The selected one rises most.", L"90", {}, 10, 300, 2, L"Wheel and edges"},
{K::Number, L"Perspective", L"Camera perspective distance (px)", L"Lower values give stronger 3D distortion. Minimum 700.", L"1100", {}, 700, 6000, 3, L"Camera"},
{K::Number, L"ShrinkDistance", L"Shrink distance (px)", L"How far you drag up for the desktop to shrink completely into the cube.", L"260", {}, 60, 1200, 3, L"Camera"},
{K::Number, L"DragSmoothing", L"Drag smoothing (ms)", L"How softly the cube follows the mouse. 0 means it sticks to the mouse exactly.", L"35", {}, 0, 400, 3, L"Speed"},
{K::Number, L"SnapSpeed", L"Snap speed (%)", L"Speed of the snap-to-face spring.", L"90", {}, 10, 500, 3, L"Speed"},
{K::Number, L"SnapBounce", L"Snap bounce (%)", L"Overshoot when the cube settles on a face. 0 is no bounce.", L"30", {}, 0, 100, 3, L"Speed"},
{K::Check, L"ZoomAnimation", L"Zoom open and close animation", L"The desktop shrinks gradually into the cube while you drag and grows back on release.", L"1", {}, 0, 100, 3, L"Speed"},
{K::Number, L"ZoomSpeed", L"Zoom speed (%)", L"Speed of the open and close zoom.", L"90", {}, 10, 500, 3, L"Speed"},
{K::Number, L"CloseFadeDuration", L"Close fade duration (ms)", L"Final crossfade from the cube to the real desktop. 0 for instant.", L"140", {}, 0, 1500, 3, L"Speed"},
{K::Choice, L"SwitchMethod", L"Switch desktops with", L"Seamless Window Manager sends its own \"Switch to desktop N\" hotkey. If it is off or does not react, the Windows shortcut is used.", L"0", {{L"0", L"Seamless Window Manager"}, {L"1", L"Windows shortcut only"}}, 0, 100, 4, L"Desktop switching"},
{K::Check, L"SuppressSystemAnimation", L"Suppress Windows desktop slide animation", L"Hides the Windows desktop slide animation only while the cube switches desktops. Your Windows \"Animation effects\" setting is never changed.", L"1", {}, 0, 100, 4, L"Desktop switching"},
{K::Number, L"SwitchSettleDelay", L"Switch settle delay (ms)", L"Extra time the overlay stays up after Windows reports the new desktop.", L"120", {}, 0, 2000, 4, L"Desktop switching"},
{K::Check, L"AutoHideTaskbarFix", L"Re-hide auto-hide taskbar", L"After the gesture, an auto-hide taskbar is hidden again right away and ready for the next gesture.", L"1", {}, 0, 100, 4, L"Desktop switching"},
{K::Number, L"FrameRateLimit", L"Frame rate limit (FPS)", L"0 means match the monitor refresh rate exactly (recommended).", L"0", {}, 0, 1000, 4, L"Performance"},
{K::Check, L"IdlePowerSave", L"Idle power saving", L"While the cube is held still and nothing moves, the render loop slows to about 30 Hz. It returns to full refresh as soon as anything moves.", L"1", {}, 0, 100, 4, L"Performance"},
{K::Choice, L"LiveMethod", L"Live capture method", L"Troubleshooting. 0 tries Desktop Duplication then GDI. 2 forces the slower but simpler GDI capture.", L"0", {{L"0", L"Automatic"}, {L"1", L"Desktop Duplication"}, {L"2", L"GDI"}}, 0, 100, 4, L"Performance"},
{K::Check, L"SettingsWindow.settingsGlass", L"Blurred settings window", L"On, the settings window is see-through glass with Windows acrylic behind it. Off, it is solid. Applies when you save.", L"1", {}, 0, 100, 0, L"Settings window"},
{K::Check, L"SettingsWindow.nativeSettingsTitleBar", L"Native Windows title bar", L"Use the Windows title bar and window buttons for this settings window. Applies when you save.", L"0", {}, 0, 100, 0, L"Settings window"},
{K::Check, L"SettingsWindow.settingsTrayIcon", L"Tray icon", L"A cube icon in the system tray. Click it to open these settings, right-click it for a menu.", L"1", {}, 0, 100, 0, L"Settings window"},
{K::Check, L"RecordingMode", L"Screen recording mode", L"Makes the cube visible to screen recorders and screenshots. Normally the cube hides itself from capture so the live view never films itself. In this mode the desktop on the front face is a still picture instead of live.", L"0", {}, 0, 100, 4, L"Debug"},
{K::Check, L"EnableDebugLogging", L"Enable diagnostic logging", L"Write detailed traces to the Windhawk log.", L"0", {}, 0, 100, 4, L"Debug"}
    };
}

struct SetPageInfo {
    PCWSTR name, intro;
    WCHAR glyph;
};
static const SetPageInfo kSetPages[] = {
{L"Look", L"Rounded faces, borders, shading and the backdrop.", 0xE790},
{L"Text", L"Font, weight and size of the badges, labels and toasts.", 0xE8D2},
{L"Gesture", L"How you drag, tilt, flick and use the wheel and the edges.", 0xE7C9},
{L"Motion", L"Camera, speed, bounce and the open and close animation.", 0xE916},
{L"Behavior", L"Switching desktops, performance, this window and debug tools.", 0xE713},
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
constexpr float kSetEdgeW = 2, kSetRadius = 16;
constexpr int kSetChipCount = 10;
constexpr UINT32 kSetChips[kSetChipCount] = {mocha::blue,   mocha::sapphire, mocha::teal, mocha::green, mocha::yellow,
                                             mocha::peach,  mocha::red,      mocha::pink, mocha::mauve, mocha::lavender};
constexpr UINT_PTR kSetTimerId = 1;
constexpr float kSetAutoDead = 10, kSetAutoR = 18, kSetAutoGain = 0.14f, kSetAutoMax = 56;
constexpr PCWSTR kSetAutoProp = L"SeamlessOwnAutoscroll";  // Seamless Autoscroll skips this window.
constexpr PCWSTR kSetKofiUrl = L"https://ko-fi.com/DavidHiFi";
constexpr PCWSTR kSetAuthorUrl = L"https://github.com/DavidHiFi";
constexpr PCWSTR kSetDittoUrl = L"https://windhawk.net/mods/compiz-desktop-cube";
constexpr PCWSTR kSetRepoUrl = L"https://github.com/DavidHiFi/davids-windhawk-mods";
constexpr PCWSTR kSetBugUrl =
    L"https://github.com/DavidHiFi/davids-windhawk-mods/issues/new?title=%5BSeamless%20Compiz%20Cube%5D%20";
constexpr PCWSTR kSetTitle = L"Seamless Compiz Cube";
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
        if (w.fRailName && Set_TextW(w.fRailName.get(), L"Compiz Cube") <= railW) break;
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
    if ((text.size() != 7 && text.size() != 9) || text[0] != L'#') return false;
    UINT32 v = 0;
    for (size_t i = 1; i < text.size(); i++) {
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

// Same colour text, keeping the alpha byte of an #AARRGGBB value.
static std::wstring Set_HexLike(const std::wstring& like, UINT32 rgb) {
    WCHAR text[16];
    if (like.size() == 9) swprintf_s(text, L"#%02X%06X", (rgb >> 24) & 0xFF, rgb & 0xFFFFFF);
    else swprintf_s(text, L"#%06X", rgb & 0xFFFFFF);
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
        case SetField::Color: return 378;
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
            p.box = {r - 112, mid - h, r, mid + h};
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
        add(SetItem::Link, 56, L"Based on Compiz Desktop Cube by Soham", L"The original Windhawk mod, MIT license", kSetDittoUrl);
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
    const float rad = Set_Rad(box);
    p.Round(box, rad, kSetBoxFill);
    float g = std::max(Set_GlowOf(w, 6000 + k), active ? 1.0f : 0.0f);
    p.Edge(box, rad, mocha::overlay0, 0.7f * (1 - g));
    p.GradRing(box, rad, g);
}

static void Set_DrawRow(SetPaint& p, SetWindow& w, const SetItem& it) {
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
    p.Round(row, kSetRadius, mocha::base);
    p.Round(row, kSetRadius, mocha::surface0, 0.32f);
    p.Edge(row, kSetRadius, mocha::surface2, 0.55f * (1 - hov));
}

static void Set_DrawLinkRow(SetPaint& p, SetWindow& w, const SetItem& it, int idx) {
    D2D1_RECT_F row = Set_RowRect(w, it);
    float hov = Set_GlowOf(w, 3000 + idx);
    Set_DrawCard(p, row, hov);
    p.GradFill(row, kSetRadius, 0.13f * hov);
    p.GradRing(row, kSetRadius, hov);
    p.Text(w.fLabel.get(), it.text, {row.left + kSetRowPad, row.top + 9, row.right - 50, row.top + 30}, mocha::text);
    p.Text(w.fHint.get(), it.sub, {row.left + kSetRowPad, row.top + 30, row.right - 50, row.bottom - 4}, mocha::subtext0);
    p.Glyph(w.fIcon.get(), 0xE8A7, {row.right - 46, row.top, row.right - 12, row.bottom}, mocha::subtext1);
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
        const WCHAR glyph = 0xF158;
        auto br = p.G({mc.x - 19, mc.y - 19, mc.x + 19, mc.y + 19});
        if (br) p.rt->DrawText(&glyph, 1, w.fIconL.get(), mark, br.get());
        p.rt->SetTransform(old);
    }
    float x = mark.right + 20;
    p.Text(w.fBig.get(), L"Seamless Compiz Cube", {x, row.top + 18, row.right - 16, row.top + 46}, mocha::text);
#ifdef WH_MOD_VERSION
    std::wstring ver = std::wstring(L"Version ") + WH_MOD_VERSION + L"  \u00B7  MIT license  \u00B7  A Windhawk mod";
#else
    std::wstring ver = L"MIT license  \u00B7  A Windhawk mod";
#endif
    p.Text(w.fHint.get(), ver, {x, row.top + 48, row.right - 16, row.top + 68}, mocha::subtext0);
    p.Text(w.fHint.get(), L"A 3D glass desktop cube with rounded faces and blue to mauve borders.",
           {x, row.top + 72, row.right - 16, row.top + 110}, mocha::subtext1);
    p.Text(w.fHint.get(), L"Made by DavidHiFi, based on Compiz Desktop Cube by Soham.",
           {x, row.top + 112, row.right - 16, row.bottom - 8}, mocha::overlay2);
}

static void Set_DrawBanner(SetPaint& p, SetWindow& w, const SetItem& it) {
    D2D1_RECT_F r = Set_RowRect(w, it);
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
    p.Text(w.fRailName.get(), L"Compiz Cube", {d.left + 90, d.top + 32, d.left + w.railW - 10, d.top + 56}, mocha::text, textA);
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
    p.GradRing(d, rad, 0.92f + 0.08f * w.footGlow);
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
    const WCHAR mark = 0xF158;
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
                    f.cur = Set_HexLike(text, rgb);
                    Set_SetStatus(w, L"");
                } else {
                    Set_SetStatus(w, L"Use a color like #89B4FA, or #FF89B4FA with opacity first.", true);
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
    SendMessageW(w.edit, EM_SETLIMITTEXT, f.kind == SetField::Number ? 6 : f.kind == SetField::Color ? 9 : 260, 0);
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
                {
                    UINT32 old = 0xFF000000;
                    Set_ParseHex(f.cur, old);
                    f.cur = Set_HexLike(f.cur, (f.cur.size() == 9 ? (old & 0xFF000000) : 0) | kSetChips[hit->b]);
                }
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
    const bool native = Set_FieldOn(w, L"SettingsWindow.nativeSettingsTitleBar", false), glass = Set_FieldOn(w, L"SettingsWindow.settingsGlass", true);
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
    HWND hwnd = CreateWindowExW(0, kSettingsClass, L"Seamless Compiz Cube settings", style,
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
}  // namespace sccset

// ============================================================================
// Tray icon: a cube on a blue to mauve rounded square. Click opens the settings window,
// right-click shows a menu. It lives on its own hidden window and thread, and only in the
// explorer.exe process that owns the taskbar (Explorer runs this mod in each of its processes).
// ============================================================================
namespace scctray {
constexpr UINT WM_TRAY = WM_APP + 21;
constexpr UINT WM_QUIT_HOST = WM_APP + 22;
constexpr UINT WM_REFRESH = WM_APP + 23;
constexpr UINT TrayIconId() {
    UINT hash = 2166136261u;
    for (PCWSTR p = WH_MOD_ID; *p; p++) hash = (hash ^ (UINT)*p) * 16777619u;
    return hash | 0x80000000u;
}
constexpr UINT kTrayId = TrayIconId();
constexpr UINT_PTR kTimerFind = 1;
constexpr wchar_t kHostClass[] = L"WindhawkSeamlessCompizCubeTray";

static HANDLE g_thread = nullptr;
static std::atomic<HWND> g_host{nullptr};
static HICON g_icon = nullptr;
static bool g_shown = false;
static int g_tries = 0;
static UINT g_taskbarCreated = 0;

static bool OwnsTaskbar() {
    DWORD pid = 0;
    HWND tray = FindWindowW(L"Shell_TrayWnd", nullptr);
    return tray && GetWindowThreadProcessId(tray, &pid) && pid == GetCurrentProcessId();
}

static bool WantIcon() { return Wh_GetIntSetting(L"SettingsWindow.settingsTrayIcon") != 0; }

static float SegDist(float px, float py, float ax, float ay, float bx, float by) {
    float dx = bx - ax, dy = by - ay;
    float t = ((px - ax) * dx + (py - ay) * dy) / (dx * dx + dy * dy);
    t = t < 0 ? 0 : (t > 1 ? 1 : t);
    float qx = ax + t * dx - px, qy = ay + t * dy - py;
    return std::sqrt(qx * qx + qy * qy);
}

// Per pixel, 4x4 supersampled: gradient #89B4FA to #CBA6F7 square, a crust (#11111B) hexagon with
// the three inner edges of an isometric cube.
static HICON MakeIcon_Big(int size) {
    BITMAPV5HEADER bi{};
    bi.bV5Size = sizeof(bi); bi.bV5Width = size; bi.bV5Height = -size; bi.bV5Planes = 1;
    bi.bV5BitCount = 32; bi.bV5Compression = BI_BITFIELDS;
    bi.bV5RedMask = 0x00FF0000; bi.bV5GreenMask = 0x0000FF00; bi.bV5BlueMask = 0x000000FF; bi.bV5AlphaMask = 0xFF000000;
    void* bits = nullptr;
    HDC dc = GetDC(nullptr);
    HBITMAP color = CreateDIBSection(dc, (BITMAPINFO*)&bi, DIB_RGB_COLORS, &bits, nullptr, 0);
    ReleaseDC(nullptr, dc);
    if (!color) return nullptr;
    auto px = (UINT32*)bits;
    const float n = (float)size, zoom = 1 / 1.2f;  // The cube alone, scaled up about the centre to fill the room the plate had.
    const int ss = 4;
    const float R = n * 0.30f, cx0 = n * 0.5f, cy0 = n * 0.5f, half = std::max(0.045f * n, 0.6f);
    float vx[6], vy[6];
    for (int i = 0; i < 6; i++) {
        float a = (-90.0f + 60.0f * i) * 3.14159265f / 180.0f;
        vx[i] = cx0 + R * std::cos(a);
        vy[i] = cy0 + R * std::sin(a);
    }
    auto inCube = [&](float x, float y) {
        for (int i = 0; i < 6; i++) {
            int j = (i + 1) % 6;
            if (SegDist(x, y, vx[i], vy[i], vx[j], vy[j]) <= half) return true;
        }
        // centre to the bottom, upper-left and upper-right corners
        const int spokes[3] = {3, 5, 1};
        for (int s : spokes)
            if (SegDist(x, y, cx0, cy0, vx[s], vy[s]) <= half) return true;
        return false;
    };
    for (int y = 0; y < size; y++)
        for (int x = 0; x < size; x++) {
            float cover = 0;
            for (int sy = 0; sy < ss; sy++)
                for (int sx = 0; sx < ss; sx++) {
                    float fx = x + (sx + 0.5f) / ss, fy = y + (sy + 0.5f) / ss;
                    if (inCube(n * 0.5f + (fx - n * 0.5f) * zoom, n * 0.5f + (fy - n * 0.5f) * zoom)) cover++;
                }
            cover /= ss * ss;
            float t = std::clamp((x + y) / (2.0f * n), 0.0f, 1.0f);
            // The cube's lines in 0x89B4FA to 0xCBA6F7 on a clear background.
            float r = (0x89 + (0xCB - 0x89) * t), g = (0xB4 + (0xA6 - 0xB4) * t), b = (0xFA + (0xF7 - 0xFA) * t);
            BYTE a = (BYTE)(cover * 255 + 0.5f);
            px[y * size + x] = ((UINT32)a << 24) | ((UINT32)(r * cover) << 16) | ((UINT32)(g * cover) << 8) | (UINT32)(b * cover);
        }
    HBITMAP mask = CreateBitmap(size, size, 1, 1, nullptr);
    ICONINFO ii{TRUE, 0, 0, mask, color};
    HICON icon = CreateIconIndirect(&ii);
    DeleteObject(mask);
    DeleteObject(color);
    return icon;
}

// Drawn at 4x and shrunk, so the icon is smooth at the size it is shown.
static HICON MakeIcon(int size) { return Crisp_ShrinkIcon(MakeIcon_Big((size > 0 ? size : 16) * 4), 4); }

static void Update(HWND hwnd) {
    NOTIFYICONDATAW nid{sizeof(nid)};
    nid.hWnd = hwnd;
    nid.uID = kTrayId;
    if (!WantIcon()) {
        if (g_shown) Shell_NotifyIconW(NIM_DELETE, &nid);
        g_shown = false;
        return;
    }
    if (!g_icon) g_icon = MakeIcon(GetSystemMetricsForDpi(SM_CXICON, GetDpiForSystem()));
    nid.uFlags = NIF_MESSAGE | NIF_ICON | NIF_TIP | NIF_SHOWTIP;
    nid.uCallbackMessage = WM_TRAY;
    nid.hIcon = g_icon;
    wcscpy_s(nid.szTip, L"Seamless Compiz Cube");
    if (g_shown && Shell_NotifyIconW(NIM_MODIFY, &nid)) return;
    g_shown = Shell_NotifyIconW(NIM_ADD, &nid) != FALSE;
    if (g_shown) {
        nid.uVersion = NOTIFYICON_VERSION_4;
        Shell_NotifyIconW(NIM_SETVERSION, &nid);
    }
}

static void Remove(HWND hwnd) {
    if (g_shown) {
        NOTIFYICONDATAW nid{sizeof(nid)};
        nid.hWnd = hwnd;
        nid.uID = kTrayId;
        Shell_NotifyIconW(NIM_DELETE, &nid);
        g_shown = false;
    }
    if (g_icon) { DestroyIcon(g_icon); g_icon = nullptr; }
}

static LRESULT CALLBACK HostProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    if (g_taskbarCreated && msg == g_taskbarCreated) {
        g_shown = false;  // the new taskbar has no icons yet
        if (OwnsTaskbar()) Update(hwnd);
        return 0;
    }
    switch (msg) {
        case WM_TIMER:
            if (wParam == kTimerFind) {
                if (OwnsTaskbar()) {
                    KillTimer(hwnd, kTimerFind);
                    Update(hwnd);
                } else if (++g_tries >= 30) {
                    KillTimer(hwnd, kTimerFind);
                }
            }
            return 0;
        case WM_REFRESH:
            if (OwnsTaskbar()) Update(hwnd);
            return 0;
        case WM_TRAY:
            switch (LOWORD(lParam)) {
                case NIN_SELECT:
                case NIN_KEYSELECT:
                    sccset::OpenSettingsWindow();
                    break;
                case WM_CONTEXTMENU: {
                    POINT pt{GET_X_LPARAM(wParam), GET_Y_LPARAM(wParam)};
                    int cmd = sccset::Set_TrayMenu(hwnd, {sccset::Set_MenuRow(1, L"", L"Settings")}, &pt);
                    if (cmd == 1) sccset::OpenSettingsWindow();
                    break;
                }
            }
            return 0;
        case WM_QUIT_HOST:
            Remove(hwnd);
            DestroyWindow(hwnd);
            return 0;
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
    }
    return DefWindowProcW(hwnd, msg, wParam, lParam);
}

static DWORD WINAPI HostThread(void*) {
    SetThreadDpiAwarenessContext(DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2);
    WNDCLASSW wc{};
    wc.lpfnWndProc = HostProc;
    wc.hInstance = (HINSTANCE)&__ImageBase;
    wc.lpszClassName = kHostClass;
    RegisterClassW(&wc);
    g_taskbarCreated = RegisterWindowMessageW(L"TaskbarCreated");
    HWND hwnd = CreateWindowExW(WS_EX_TOOLWINDOW, kHostClass, L"Seamless Compiz Cube tray", WS_POPUP, 0, 0, 0, 0,
                                nullptr, nullptr, (HINSTANCE)&__ImageBase, nullptr);
    if (hwnd) {
        ChangeWindowMessageFilterEx(hwnd, g_taskbarCreated, MSGFLT_ALLOW, nullptr);
        g_host.store(hwnd);
        SetTimer(hwnd, kTimerFind, 2000, nullptr);
        PostMessageW(hwnd, WM_REFRESH, 0, 0);
        MSG msg;
        while (GetMessageW(&msg, nullptr, 0, 0) > 0) {
            TranslateMessage(&msg);
            DispatchMessageW(&msg);
        }
        g_host.store(nullptr);
    }
    UnregisterClassW(kHostClass, (HINSTANCE)&__ImageBase);
    return 0;
}

static void Start() {
    if (g_thread) return;
    g_tries = 0;
    g_thread = CreateThread(nullptr, 0, HostThread, nullptr, 0, nullptr);
}

static void Refresh() {
    if (HWND h = g_host.load()) PostMessageW(h, WM_REFRESH, 0, 0);
}

static void Stop() {
    if (!g_thread) return;
    if (HWND h = g_host.load()) {
        DWORD_PTR ignored;
        SendMessageTimeoutW(h, WM_CANCELMODE, 0, 0, SMTO_ABORTIFHUNG, 500, &ignored);  // closes an open menu
        PostMessageW(h, WM_QUIT_HOST, 0, 0);
    }
    WaitForSingleObject(g_thread, 5000);
    CloseHandle(g_thread);
    g_thread = nullptr;
}
}  // namespace scctray


#include <winrt/base.h>
#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.Foundation.Collections.h>
#include <winrt/Windows.Foundation.Numerics.h>
#include <winrt/Windows.System.h>
#include <winrt/Windows.UI.Composition.h>
#include <winrt/Windows.UI.Composition.Desktop.h>
#include <winrt/Windows.Graphics.DirectX.h>

using namespace winrt;
using namespace winrt::Windows::UI::Composition;
using namespace winrt::Windows::UI::Composition::Desktop;
using namespace winrt::Windows::Foundation::Numerics;
using namespace winrt::Windows::Graphics::DirectX;

// ============================================================================
// Composition interop definitions (custom names to avoid SDK header clashes)
// ============================================================================

// ICompositorInterop {25297D5C-3AD4-4C9C-B5CF-E36A38512330}
struct ICompositorInteropX : public IUnknown {
    virtual HRESULT STDMETHODCALLTYPE CreateCompositionSurfaceForHandle(HANDLE, void**) = 0;
    virtual HRESULT STDMETHODCALLTYPE CreateCompositionSurfaceForSwapChain(IUnknown*, void**) = 0;
    virtual HRESULT STDMETHODCALLTYPE CreateGraphicsDevice(IUnknown*, void**) = 0;
};
static const IID IID_ICompositorInteropX =
    {0x25297D5C, 0x3AD4, 0x4C9C, {0xB5, 0xCF, 0xE3, 0x6A, 0x38, 0x51, 0x23, 0x30}};

// ICompositionDrawingSurfaceInterop {FD04E6E3-FE0C-4C3C-AB19-A07601A576EE}
struct ICompositionDrawingSurfaceInteropX : public IUnknown {
    virtual HRESULT STDMETHODCALLTYPE BeginDraw(const RECT* updateRect, REFIID iid, void** updateObject, POINT* updateOffset) = 0;
    virtual HRESULT STDMETHODCALLTYPE EndDraw() = 0;
    virtual HRESULT STDMETHODCALLTYPE Resize(SIZE sizePixels) = 0;
    virtual HRESULT STDMETHODCALLTYPE Scroll(const RECT* scrollRect, const RECT* clipRect, int offsetX, int offsetY) = 0;
    virtual HRESULT STDMETHODCALLTYPE SuspendDraw() = 0;
    virtual HRESULT STDMETHODCALLTYPE ResumeDraw() = 0;
};
static const IID IID_ICompositionDrawingSurfaceInteropX =
    {0xFD04E6E3, 0xFE0C, 0x4C3C, {0xAB, 0x19, 0xA0, 0x76, 0x01, 0xA5, 0x76, 0xEE}};

// ICompositorDesktopInterop {29E691FA-4567-4DCA-B319-D0F207EB6807}
struct ICompositorDesktopInteropX : public IUnknown {
    virtual HRESULT STDMETHODCALLTYPE CreateDesktopWindowTarget(HWND hwndTarget, BOOL isTopmost, void** result) = 0;
};
static const IID IID_ICompositorDesktopInteropX =
    {0x29E691FA, 0x4567, 0x4DCA, {0xB3, 0x19, 0xD0, 0xF2, 0x07, 0xEB, 0x68, 0x07}};

// DispatcherQueue creation (CoreMessaging.dll)
struct DispatcherQueueOptionsX {
    DWORD dwSize;
    int threadType;      // DQTYPE_THREAD_CURRENT = 2
    int apartmentType;   // DQTAT_COM_NONE = 0
};

// WIC constants defined locally so no extra import libraries are needed
static const GUID kPixelFormat32bppBGR =
    {0x6fddc324, 0x4e03, 0x4bfe, {0xb1, 0x85, 0x3d, 0x77, 0x76, 0x8d, 0xc9, 0x0e}};
static const CLSID kClsidWICImagingFactory =
    {0xcacaf262, 0x9370, 0x4615, {0xa1, 0x3b, 0x9f, 0x55, 0x39, 0xda, 0x4c, 0x0a}};

// ============================================================================
// Logging
// ============================================================================
static bool g_debugLog = false;

#define LOG_DBG(fmt, ...) \
    do { if (g_debugLog) { Wh_Log(L"[Cube] " fmt, ##__VA_ARGS__); } } while (0)
#define LOG_INF(fmt, ...) Wh_Log(L"[Cube] " fmt, ##__VA_ARGS__)
#define LOG_ERR(fmt, ...) Wh_Log(L"[Cube ERROR] " fmt, ##__VA_ARGS__)

// Set at the very start of Wh_ModUninit. Once set, no new thread may be started and no gesture may begin.
static std::atomic<bool> g_unloading{ false };

// Handle of THIS mod's module (not explorer.exe's). Used to register the overlay window class.
static HMODULE GetThisModuleHandle() {
    HMODULE h = nullptr;
    GetModuleHandleExW(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS | GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT,
                       (LPCWSTR)&GetThisModuleHandle, &h);
    return h;
}

// ============================================================================
// Settings
// ============================================================================
struct ModSettings {
    int   activationThreshold = 10;
    float hSens = 0.45f;
    float vSens = 0.35f;
    bool  verticalRotation = true;
    float maxTilt = 60.0f;
    bool  invertH = false;
    bool  invertV = false;
    bool  wrap = true;
    float faceSize = 0.66f;
    float shrinkDist = 260.0f;
    bool  wheelZoom = true;
    float wheelStep = 0.10f;
    bool  rememberZoom = false;
    bool  autoHideFix = true;
    float sideOpacity = 0.55f;
    float perspective = 1100.0f;
    int   dragSmoothMs = 35;
    float snapSpeed = 0.9f;
    float bounce = 0.3f;
    bool  zoomAnim = true;
    float zoomSpeed = 0.9f;
    int   fadeMs = 140;
    bool  flick = true;
    float flickStrength = 1.0f;
    float switchAngle = 25.0f;
    bool  blur = true;
    float blurStrength = 28.0f;
    int   dim = 25;
    bool  parallax = true;
    int   brightness = 100;
    bool  labels = true;
    float faceGap = 0.14f;
    float frontOpacity = 1.0f;
    float backOpacity = 0.10f;
    bool  horizFirst = true;
    int   vUnlockMs = 350;
    bool  shadow = true;
    int   texQuality = 100;
    bool  suppressSysAnim = true;
    int   settleMs = 120;
    int   fpsLimit = 0;
    int   liveMethod = 0;
    bool  altTab = false;
    int   bgHz = 15;
    bool  idleSave = true;
    bool  recordingMode = false;
    bool  edgeEdit = true;
    float edgeZone = 0.10f;
    int   edgeReveal = 40;
    float altLift = 90.0f;
    bool  useSwm = true;
    float cornerRadius = 16.0f;
    float borderWidth = 2.0f;
    uint32_t restColor = 0xCC7F849Cu;
    uint32_t actStart = 0xFF89B4FAu;
    uint32_t actEnd = 0xFFCBA6F7u;
    int   borderMode = 0;
    int   borderFadeMs = 150;
    std::wstring fontFamily = L"FiraCode Nerd Font";
    int   fontWeight = 500;
    float fontSize = 13.0f;
};
static ModSettings g_settings;
static float g_userZoom = 1.0f;   // remembered wheel zoom
static const float kMinUserZoom = 0.30f;
static const float kMaxUserZoom = 1.60f;
static const int kMaxFaces = 6;
static const int kMaxDesktops = 16;

static int GetIntSetting(PCWSTR name, int def, int lo, int hi) {
    int v = Wh_GetIntSetting(name);
    if (v < lo || v > hi) return def;
    return v;
}

// A choice stored as text such as "2" or "500". Anything unreadable or out of range gives the default.
static int GetChoiceSetting(PCWSTR name, int def, int lo, int hi) {
    PCWSTR raw = Wh_GetStringSetting(name);
    if (!raw) return def;
    wchar_t* end = nullptr;
    long v = wcstol(raw, &end, 10);
    bool ok = end != raw && *end == 0 && v >= lo && v <= hi;
    Wh_FreeStringSetting(raw);
    return ok ? (int)v : def;
}

// "#RRGGBB" or "#AARRGGBB" to 0xAARRGGBB. Anything else gives the default.
static uint32_t GetColorSetting(PCWSTR name, uint32_t def) {
    PCWSTR raw = Wh_GetStringSetting(name);
    uint32_t out = def;
    if (raw) {
        const wchar_t* p = raw;
        while (*p == L' ') p++;
        if (*p == L'#') p++;
        size_t n = 0;
        uint32_t v = 0;
        bool ok = true;
        for (; p[n] && p[n] != L' '; n++) {
            wchar_t c = p[n];
            int d = (c >= L'0' && c <= L'9') ? c - L'0'
                  : (c >= L'a' && c <= L'f') ? c - L'a' + 10
                  : (c >= L'A' && c <= L'F') ? c - L'A' + 10 : -1;
            if (d < 0 || n >= 8) { ok = false; break; }
            v = (v << 4) | (uint32_t)d;
        }
        if (ok && n == 6) out = 0xFF000000u | v;
        else if (ok && n == 8) out = v;
        Wh_FreeStringSetting(raw);
    }
    return out;
}

static std::wstring GetTextSetting(PCWSTR name, const wchar_t* def) {
    PCWSTR raw = Wh_GetStringSetting(name);
    std::wstring out = def;
    if (raw) {
        std::wstring v = raw;
        Wh_FreeStringSetting(raw);
        size_t a = v.find_first_not_of(L" \t");
        size_t b = v.find_last_not_of(L" \t");
        if (a != std::wstring::npos) out = v.substr(a, b - a + 1);
    }
    return out;
}

static void LoadSettings() {
    ModSettings s;
    s.activationThreshold = GetIntSetting(L"ActivationThreshold", 10, 1, 600);
    s.hSens = GetIntSetting(L"HorizontalSensitivity", 45, 1, 1000) / 100.0f;
    s.vSens = GetIntSetting(L"VerticalSensitivity", 35, 1, 1000) / 100.0f;
    s.verticalRotation = Wh_GetIntSetting(L"EnableVerticalRotation") != 0;
    s.maxTilt = (float)GetIntSetting(L"MaxTiltAngle", 60, 5, 85);
    s.invertH = Wh_GetIntSetting(L"InvertHorizontal") != 0;
    s.invertV = Wh_GetIntSetting(L"InvertVertical") != 0;
    s.wrap = Wh_GetIntSetting(L"WrapAround") != 0;
    s.faceSize = GetIntSetting(L"FaceSize", 66, 30, 90) / 100.0f;
    s.shrinkDist = (float)GetIntSetting(L"ShrinkDistance", 260, 60, 1200);
    s.autoHideFix = Wh_GetIntSetting(L"AutoHideTaskbarFix") != 0;
    s.recordingMode = Wh_GetIntSetting(L"RecordingMode") != 0;
    s.sideOpacity = GetIntSetting(L"SideFaceOpacity", 55, 0, 100) / 100.0f;
    s.perspective = (float)GetIntSetting(L"Perspective", 1100, 700, 6000);
    s.dragSmoothMs = GetIntSetting(L"DragSmoothing", 35, 0, 400);
    s.snapSpeed = GetIntSetting(L"SnapSpeed", 90, 10, 500) / 100.0f;
    s.bounce = GetIntSetting(L"SnapBounce", 30, 0, 100) / 100.0f;
    s.zoomAnim = Wh_GetIntSetting(L"ZoomAnimation") != 0;
    s.zoomSpeed = GetIntSetting(L"ZoomSpeed", 90, 10, 500) / 100.0f;
    s.fadeMs = GetIntSetting(L"CloseFadeDuration", 140, 0, 1500);
    s.flick = Wh_GetIntSetting(L"FlickToSwitch") != 0;
    s.flickStrength = GetIntSetting(L"FlickStrength", 100, 0, 500) / 100.0f;
    s.switchAngle = (float)GetIntSetting(L"SwitchAngle", 25, 5, 85);
    s.blur = Wh_GetIntSetting(L"BackgroundBlur") != 0;
    s.blurStrength = (float)GetIntSetting(L"BlurStrength", 28, 1, 200);
    s.dim = GetIntSetting(L"BackgroundDim", 25, 0, 100);
    s.parallax = Wh_GetIntSetting(L"BackgroundParallax") != 0;
    s.brightness = GetIntSetting(L"FaceBrightness", 100, 0, 100);
    s.labels = Wh_GetIntSetting(L"ShowDesktopLabels") != 0;
    s.faceGap = GetIntSetting(L"FaceGap", 14, 0, 60) / 100.0f;
    s.frontOpacity = GetIntSetting(L"FrontFaceOpacity", 100, 10, 100) / 100.0f;
    s.backOpacity = GetIntSetting(L"BackFaceOpacity", 10, 0, 100) / 100.0f;
    s.horizFirst = Wh_GetIntSetting(L"HorizontalFirst") != 0;
    s.vUnlockMs = GetIntSetting(L"VerticalUnlockDelay", 350, 0, 3000);
    s.shadow = Wh_GetIntSetting(L"ShowShadow") != 0;
    s.texQuality = GetIntSetting(L"TextureQuality", 100, 25, 100);
    s.suppressSysAnim = Wh_GetIntSetting(L"SuppressSystemAnimation") != 0;
    s.settleMs = GetIntSetting(L"SwitchSettleDelay", 120, 0, 2000);
    s.fpsLimit = GetIntSetting(L"FrameRateLimit", 0, 0, 1000);
    s.liveMethod = GetChoiceSetting(L"LiveMethod", 0, 0, 2);
    {
        int wa = GetChoiceSetting(L"WheelAction", 0, 0, 2);
        s.wheelZoom = (wa == 0);
        s.altTab = (wa == 1);
    }
    s.wheelStep = GetIntSetting(L"WheelZoomStep", 10, 1, 50) / 100.0f;
    s.rememberZoom = Wh_GetIntSetting(L"RememberZoom") != 0;
    s.bgHz = GetIntSetting(L"BackgroundRefreshRate", 15, 1, 60);
    s.idleSave = Wh_GetIntSetting(L"IdlePowerSave") != 0;
    s.edgeEdit = Wh_GetIntSetting(L"EdgeDesktopControl") != 0;
    s.edgeZone = GetIntSetting(L"EdgeZoneWidth", 10, 4, 25) / 100.0f;
    s.edgeReveal = GetIntSetting(L"EdgeRevealWidth", 40, 4, 300);
    s.altLift = (float)GetIntSetting(L"AltTabLift", 90, 10, 300);
    s.useSwm = GetChoiceSetting(L"SwitchMethod", 0, 0, 1) == 0;
    s.cornerRadius = (float)GetIntSetting(L"CornerRadius", 16, 0, 48);
    s.borderWidth = (float)GetIntSetting(L"BorderWidth", 3, 0, 8);
    s.restColor = GetColorSetting(L"RestingBorderColor", 0xCC7F849Cu);
    s.actStart = GetColorSetting(L"ActiveBorderStart", 0xFF89B4FAu);
    s.actEnd = GetColorSetting(L"ActiveBorderEnd", 0xFFCBA6F7u);
    s.borderMode = GetChoiceSetting(L"BorderHighlight", 0, 0, 2);
    s.borderFadeMs = GetIntSetting(L"BorderFadeMs", 150, 0, 1000);
    s.fontFamily = GetTextSetting(L"FontFamily", L"FiraCode Nerd Font");
    s.fontWeight = GetChoiceSetting(L"FontWeight", 500, 100, 950);
    s.fontSize = (float)GetIntSetting(L"FontSize", 13, 8, 24);
    g_debugLog = Wh_GetIntSetting(L"EnableDebugLogging") != 0;
    g_settings = s;

    LOG_INF(L"Settings loaded: threshold=%d blur=%d wrap=%d", s.activationThreshold, (int)s.blur, (int)s.wrap);
}

// ============================================================================
// Math
// ============================================================================
static const float kPi = 3.14159265f;

struct Vec3 { float x, y, z; };

// Row-vector convention (as used by Windows.UI.Composition).
struct Mat4 {
    float m[4][4];

    static Mat4 Identity() {
        Mat4 r{};
        for (int i = 0; i < 4; ++i) r.m[i][i] = 1.0f;
        return r;
    }
    static Mat4 Translation(float x, float y, float z) {
        Mat4 r = Identity();
        r.m[3][0] = x; r.m[3][1] = y; r.m[3][2] = z;
        return r;
    }
    static Mat4 RotationY(float rad) {
        Mat4 r = Identity();
        float c = std::cos(rad), s = std::sin(rad);
        r.m[0][0] = c;  r.m[0][2] = -s;
        r.m[2][0] = s;  r.m[2][2] = c;
        return r;
    }
    static Mat4 RotationX(float rad) {
        Mat4 r = Identity();
        float c = std::cos(rad), s = std::sin(rad);
        r.m[1][1] = c;  r.m[1][2] = -s;
        r.m[2][1] = s;  r.m[2][2] = c;
        return r;
    }
    static Mat4 Perspective(float d) {
        Mat4 r = Identity();
        if (d > 1.0f) r.m[2][3] = -1.0f / d;
        return r;
    }
    Mat4 operator*(const Mat4& o) const {
        Mat4 r{};
        for (int i = 0; i < 4; ++i)
            for (int j = 0; j < 4; ++j) {
                float sum = 0.0f;
                for (int k = 0; k < 4; ++k) sum += m[i][k] * o.m[k][j];
                r.m[i][j] = sum;
            }
        return r;
    }
    float4x4 ToWinRT() const {
        return {
            m[0][0], m[0][1], m[0][2], m[0][3],
            m[1][0], m[1][1], m[1][2], m[1][3],
            m[2][0], m[2][1], m[2][2], m[2][3],
            m[3][0], m[3][1], m[3][2], m[3][3]
        };
    }
};

// Damped spring. omega = natural frequency (rad/s), zeta = damping ratio (1 = critical).
struct Spring {
    float x = 0.0f;
    float v = 0.0f;
    void Step(float target, float omega, float zeta, float dt) {
        const float maxStep = 1.0f / 360.0f;
        while (dt > 0.0f) {
            float h = std::min(dt, maxStep);
            float a = omega * omega * (target - x) - 2.0f * zeta * omega * v;
            v += a * h;
            x += v * h;
            dt -= h;
        }
    }
};

static float RubberBand(float v, float lo, float hi, float range) {
    if (v < lo) return lo - range * (1.0f - std::exp(-(lo - v) / range));
    if (v > hi) return hi + range * (1.0f - std::exp(-(v - hi) / range));
    return v;
}

static float SmoothStep(float t) {
    t = std::clamp(t, 0.0f, 1.0f);
    return t * t * (3.0f - 2.0f * t);
}

// ============================================================================
// MODULE 1: VDManager (registry enumeration + hotkey based switching)
// ============================================================================
namespace VDManager {

    struct DesktopItem {
        int index = 0;
        GUID id{};
        std::wstring name;
    };

    struct DesktopList {
        int currentIndex = 0;
        std::vector<DesktopItem> items;
        int TotalCount() const { return (int)items.size(); }
    };

    struct WindowCard {
        std::wstring title;
        RECT rect{};
        HWND hwnd = nullptr;
        bool minimized = false;
    };

    static bool ReadDesktopsFromKey(const wchar_t* subKey, DesktopList& out, bool* pHaveCurrent) {
        HKEY hKey = nullptr;
        if (RegOpenKeyExW(HKEY_CURRENT_USER, subKey, 0, KEY_READ, &hKey) != ERROR_SUCCESS) {
            return false;
        }

        bool ok = false;
        DWORD type = 0, size = 0;
        if (RegQueryValueExW(hKey, L"VirtualDesktopIDs", nullptr, &type, nullptr, &size) == ERROR_SUCCESS &&
            size >= sizeof(GUID)) {
            std::vector<BYTE> buf(size);
            if (RegQueryValueExW(hKey, L"VirtualDesktopIDs", nullptr, &type, buf.data(), &size) == ERROR_SUCCESS) {
                int count = (int)(size / sizeof(GUID));
                GUID* guids = (GUID*)buf.data();

                GUID cur{};
                DWORD curSize = sizeof(cur);
                bool haveCur = RegQueryValueExW(hKey, L"CurrentVirtualDesktop", nullptr, nullptr,
                                                (LPBYTE)&cur, &curSize) == ERROR_SUCCESS &&
                               curSize == sizeof(GUID);
                if (pHaveCurrent) *pHaveCurrent = haveCur;

                for (int i = 0; i < count; ++i) {
                    DesktopItem item;
                    item.index = i;
                    item.id = guids[i];
                    wchar_t name[64];
                    swprintf_s(name, L"Desktop %d", i + 1);
                    item.name = name;
                    out.items.push_back(item);
                    if (haveCur && IsEqualGUID(item.id, cur)) out.currentIndex = i;
                }
                ok = !out.items.empty();
            }
        }
        RegCloseKey(hKey);
        return ok;
    }

    static bool QueryDesktopsRegistry(DesktopList& out, bool& haveCurrent) {
        out.items.clear();
        out.currentIndex = 0;
        haveCurrent = false;

        DWORD session = 0;
        ProcessIdToSessionId(GetCurrentProcessId(), &session);
        wchar_t sessionKey[256];
        swprintf_s(sessionKey,
            L"Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\SessionInfo\\%lu\\VirtualDesktops",
            session);

        bool ok = ReadDesktopsFromKey(sessionKey, out, &haveCurrent);
        if (!ok) {
            out.items.clear();
            out.currentIndex = 0;
            haveCurrent = false;
            ok = ReadDesktopsFromKey(
                L"Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\VirtualDesktops", out, &haveCurrent);
        }
        return ok;
    }

    static bool QueryDesktops(DesktopList& out) {
        bool haveCur = false;
        bool ok = QueryDesktopsRegistry(out, haveCur);

        if (!ok) {
            out.items.clear();
            DesktopItem item;
            item.index = 0;
            item.name = L"Desktop 1";
            out.items.push_back(item);
            out.currentIndex = 0;
        }

        // Cross-check the current desktop using the documented API on the foreground window.
        if (out.TotalCount() > 1) {
            com_ptr<IVirtualDesktopManager> vdm;
            if (SUCCEEDED(CoCreateInstance(CLSID_VirtualDesktopManager, nullptr, CLSCTX_INPROC_SERVER,
                                           IID_PPV_ARGS(vdm.put()))) && vdm) {
                HWND fg = GetForegroundWindow();
                GUID wid{};
                if (fg && SUCCEEDED(vdm->GetWindowDesktopId(fg, &wid))) {
                    for (const auto& it : out.items) {
                        if (IsEqualGUID(it.id, wid)) {
                            out.currentIndex = it.index;
                            break;
                        }
                    }
                }
            }
        }

        LOG_DBG(L"Desktops: total=%d current=%d", out.TotalCount(), out.currentIndex);
        return !out.items.empty();
    }

    static bool ReadCurrentIndex(int& idx) {
        DesktopList tmp;
        bool haveCur = false;
        if (QueryDesktopsRegistry(tmp, haveCur) && haveCur) {
            idx = tmp.currentIndex;
            return true;
        }
        return false;
    }

    static void SendSwitchStep(int dir) {
        WORD key = dir > 0 ? VK_RIGHT : VK_LEFT;
        INPUT in[6]{};
        for (auto& x : in) x.type = INPUT_KEYBOARD;
        in[0].ki.wVk = VK_LWIN;
        in[1].ki.wVk = VK_LCONTROL;
        in[2].ki.wVk = key;
        in[2].ki.dwFlags = KEYEVENTF_EXTENDEDKEY;
        in[3].ki.wVk = key;
        in[3].ki.dwFlags = KEYEVENTF_EXTENDEDKEY | KEYEVENTF_KEYUP;
        in[4].ki.wVk = VK_LCONTROL;
        in[4].ki.dwFlags = KEYEVENTF_KEYUP;
        in[5].ki.wVk = VK_LWIN;
        in[5].ki.dwFlags = KEYEVENTF_KEYUP;
        SendInput(6, in, sizeof(INPUT));
    }

    // Win+Ctrl+D: new desktop (Windows also switches to it). Win+Ctrl+F4: close the current desktop.
    static void SendWinCtrlKey(WORD vk) {
        INPUT in[6]{};
        for (auto& x : in) x.type = INPUT_KEYBOARD;
        in[0].ki.wVk = VK_LWIN;
        in[1].ki.wVk = VK_LCONTROL;
        in[2].ki.wVk = vk;
        in[3].ki.wVk = vk;
        in[3].ki.dwFlags = KEYEVENTF_KEYUP;
        in[4].ki.wVk = VK_LCONTROL;
        in[4].ki.dwFlags = KEYEVENTF_KEYUP;
        in[5].ki.wVk = VK_LWIN;
        in[5].ki.dwFlags = KEYEVENTF_KEYUP;
        SendInput(6, in, sizeof(INPUT));
    }
    static void SendAddDesktop() { SendWinCtrlKey('D'); }
    static void SendCloseDesktop() { SendWinCtrlKey(VK_F4); }

    // ---- Seamless Window Manager bridge ----
    // Seamless Window Manager has no workspace layer of its own. Its workspace switch is the "Switch to desktop N" hotkeys
    // (hotkeyDesktop1..9). The cube sends the key combination the user set there, then confirms through the registry
    // exactly like the Windows shortcut path. If the mod is missing, disabled, or does not react, the callers fall back.
    namespace SwmBridge {
        static const wchar_t* const kModKey = L"SOFTWARE\\Windhawk\\Engine\\Mods\\local@seamless-window-manager";
        static const DWORD kCtrl = 1, kAlt = 2, kShift = 4, kWin = 8;

        static bool IsAvailable() {
            HKEY h = nullptr;
            if (RegOpenKeyExW(HKEY_LOCAL_MACHINE, kModKey, 0, KEY_READ | KEY_WOW64_64KEY, &h) != ERROR_SUCCESS) return false;
            DWORD disabled = 0, cb = sizeof(disabled), type = 0;
            LSTATUS st = RegQueryValueExW(h, L"Disabled", nullptr, &type, (BYTE*)&disabled, &cb);
            RegCloseKey(h);
            return !(st == ERROR_SUCCESS && type == REG_DWORD && disabled == 1);
        }

        // Same grammar as Seamless Window Manager's own parser: "Ctrl+Alt+Shift+1", or a number (key | flags << 8).
        static void ParseHotkey(const wchar_t* value, int* key, DWORD* mods) {
            *key = 0;
            *mods = 0;
            if (!value || !*value) return;
            wchar_t* end = nullptr;
            unsigned long encoded = wcstoul(value, &end, 10);
            if (end != value && *end == 0 && encoded <= 0xFFFF) {
                *key = (int)(encoded & 0xFF);
                unsigned long flags = encoded >> 8;
                if (flags & MOD_ALT) *mods |= kAlt;
                if (flags & MOD_CONTROL) *mods |= kCtrl;
                if (flags & MOD_SHIFT) *mods |= kShift;
                if (flags & MOD_WIN) *mods |= kWin;
                if (!*mods) *key = 0;
                return;
            }
            std::wstring part;
            auto parsePart = [&](const std::wstring& tk) {
                if (tk == L"ALT") *mods |= kAlt;
                else if (tk == L"CTRL" || tk == L"CONTROL") *mods |= kCtrl;
                else if (tk == L"SHIFT") *mods |= kShift;
                else if (tk == L"WIN" || tk == L"WINDOWS") *mods |= kWin;
                else if (tk.size() == 1 && tk[0] >= L'A' && tk[0] <= L'Z') *key = tk[0];
                else if (tk.size() == 1 && tk[0] >= L'0' && tk[0] <= L'9') *key = tk[0];
                else if (tk[0] == L'F' && tk.size() <= 3) {
                    int number = _wtoi(tk.c_str() + 1);
                    if (number >= 1 && number <= 24) *key = VK_F1 + number - 1;
                } else if (tk == L"SPACE") *key = VK_SPACE;
                else if (tk == L"TAB") *key = VK_TAB;
                else if (tk == L"ESC" || tk == L"ESCAPE") *key = VK_ESCAPE;
                else if (tk == L"DELETE" || tk == L"DEL") *key = VK_DELETE;
                else if (tk == L"INSERT" || tk == L"INS") *key = VK_INSERT;
                else if (tk == L"HOME") *key = VK_HOME;
                else if (tk == L"END") *key = VK_END;
                else if (tk == L"PAGEUP" || tk == L"PGUP") *key = VK_PRIOR;
                else if (tk == L"PAGEDOWN" || tk == L"PGDN") *key = VK_NEXT;
                else if (tk == L"LEFT") *key = VK_LEFT;
                else if (tk == L"RIGHT") *key = VK_RIGHT;
                else if (tk == L"UP") *key = VK_UP;
                else if (tk == L"DOWN") *key = VK_DOWN;
            };
            for (const wchar_t* p = value;; p++) {
                if (*p == L'+' || *p == 0) {
                    if (!part.empty()) parsePart(part);
                    part.clear();
                    if (!*p) break;
                } else if (!iswspace(*p)) {
                    part += (wchar_t)towupper(*p);
                }
            }
            if (!*mods) *key = 0;   // A shortcut without modifiers would be ordinary typing.
        }

        // Hotkey of "Switch to desktop <idx0 + 1>". An absent value means the mod's default, Ctrl+Alt+Shift+N.
        static bool GetHotkey(int idx0, int* key, DWORD* mods) {
            wchar_t name[32], path[320], buf[128]{};
            swprintf_s(name, L"hotkeyDesktop%d", idx0 + 1);
            swprintf_s(path, L"%ls\\Settings", kModKey);
            DWORD cb = sizeof(buf) - sizeof(wchar_t);
            LSTATUS st = RegGetValueW(HKEY_LOCAL_MACHINE, path, name, RRF_RT_REG_SZ | RRF_SUBKEY_WOW64_64KEY,
                                      nullptr, buf, &cb);
            if (st == ERROR_SUCCESS) {
                ParseHotkey(buf, key, mods);
            } else {
                wchar_t def[32];
                swprintf_s(def, L"Ctrl+Alt+Shift+%d", idx0 + 1);
                ParseHotkey(def, key, mods);
            }
            return *key != 0;
        }

        // Presses the combination. Modifiers are released in reverse order with Ctrl last, so Alt alone never opens a menu.
        static bool SendDesktopHotkey(int idx0) {
            if (idx0 < 0 || idx0 > 8) return false;
            int key = 0;
            DWORD mods = 0;
            if (!GetHotkey(idx0, &key, &mods)) return false;
            INPUT in[12]{};
            int n = 0;
            auto add = [&](WORD vk, bool up, bool ext) {
                in[n].type = INPUT_KEYBOARD;
                in[n].ki.wVk = vk;
                in[n].ki.dwFlags = (up ? KEYEVENTF_KEYUP : 0) | (ext ? KEYEVENTF_EXTENDEDKEY : 0);
                n++;
            };
            const bool ext = key == VK_LEFT || key == VK_RIGHT || key == VK_UP || key == VK_DOWN || key == VK_HOME ||
                             key == VK_END || key == VK_PRIOR || key == VK_NEXT || key == VK_INSERT || key == VK_DELETE;
            if (mods & kCtrl) add(VK_LCONTROL, false, false);
            if (mods & kAlt) add(VK_LMENU, false, false);
            if (mods & kShift) add(VK_LSHIFT, false, false);
            if (mods & kWin) add(VK_LWIN, false, false);
            add((WORD)key, false, ext);
            add((WORD)key, true, ext);
            if (mods & kWin) add(VK_LWIN, true, false);
            if (mods & kShift) add(VK_LSHIFT, true, false);
            if (mods & kAlt) add(VK_LMENU, true, false);
            if (mods & kCtrl) add(VK_LCONTROL, true, false);
            return SendInput((UINT)n, in, sizeof(INPUT)) == (UINT)n;
        }
    }

    static bool ReadTotalCount(int& total) {
        DesktopList tmp;
        bool haveCur = false;
        if (QueryDesktopsRegistry(tmp, haveCur)) { total = tmp.TotalCount(); return true; }
        return false;
    }

    // The user's "Animation effects" setting is never changed. While this flag is set, the SystemParametersInfoW hook
    // (see the taskbar hooking section) answers FALSE to SPI_GETCLIENTAREAANIMATION, which is the check explorer.exe makes
    // to decide whether the desktop slide animation plays.
    static std::atomic<bool> s_animSuppressed{ false };
    static void SuppressSystemAnimation(bool on) {
        if (s_animSuppressed.exchange(on) != on) {
            if (on) LOG_DBG(L"Desktop slide animation suppressed");
            else LOG_DBG(L"Desktop slide animation restored");
        }
    }

    static bool IsWindowOnCurrentDesktop(HWND h) {
        com_ptr<IVirtualDesktopManager> vdm;
        if (FAILED(CoCreateInstance(CLSID_VirtualDesktopManager, nullptr, CLSCTX_INPROC_SERVER,
                                    IID_PPV_ARGS(vdm.put()))) || !vdm) return true;
        BOOL on = TRUE;
        if (SUCCEEDED(vdm->IsWindowOnCurrentVirtualDesktop(h, &on))) return on != FALSE;
        return true;
    }

    struct EnumCardsCtx {
        const GUID* targetId;
        IVirtualDesktopManager* pVdm;
        std::vector<WindowCard>* pOut;
    };

    // Windows that belong to the shell / input stack (emoji panel, touch keyboard, Start, Search, overlays).
    // They are not real app windows and must never be painted onto a desktop face.
    static bool IsShellHelperWindow(HWND hWnd, const WCHAR* cls, const WCHAR* title, LONG exStyle) {
        static const wchar_t* kClasses[] = {
            L"Windows.UI.Core.CoreWindow", L"XamlExplorerHostIslandWindow", L"ForegroundStaging",
            L"NotifyIconOverflowWindow", L"TopLevelWindowForOverflowXamlIsland", L"Xaml_WindowedPopupClass",
            L"MultitaskingViewFrame", L"TaskListThumbnailWnd", L"TaskListOverlayWnd", L"ApplicationManager_ImmersiveShellWindow",
            L"IPTip_Main_Window", L"IPTip_Window", L"ImeUIWndTouch", L"TipbarGripper", L"TIPBand",
            L"Windows.UI.Input.InputSite.WindowClass", L"EdgeUiInputTopWndClass",
        };
        for (const wchar_t* k : kClasses) if (_wcsicmp(cls, k) == 0) return true;

        static const wchar_t* kTitles[] = {
            L"Windows Input Experience", L"Microsoft Text Input Application", L"Text input", L"Emoji",
            L"NVIDIA GeForce Overlay", L"Windows Shell Experience Host", L"Task Switching", L"Task View",
        };
        for (const wchar_t* t : kTitles) if (_wcsicmp(title, t) == 0) return true;

        // Click-through / non-activating windows that are not explicitly app windows are overlays, not apps.
        if ((exStyle & WS_EX_NOACTIVATE) && !(exStyle & WS_EX_APPWINDOW)) return true;
        if ((exStyle & WS_EX_TRANSPARENT) && (exStyle & WS_EX_LAYERED) && !(exStyle & WS_EX_APPWINDOW)) return true;

        DWORD pid = 0;
        GetWindowThreadProcessId(hWnd, &pid);
        if (pid) {
            HANDLE hp = OpenProcess(PROCESS_QUERY_LIMITED_INFORMATION, FALSE, pid);
            if (hp) {
                WCHAR path[MAX_PATH]{};
                DWORD n = MAX_PATH;
                bool hit = false;
                if (QueryFullProcessImageNameW(hp, 0, path, &n)) {
                    const WCHAR* base = wcsrchr(path, L'\\');
                    base = base ? base + 1 : path;
                    static const wchar_t* kProcs[] = {
                        L"TextInputHost.exe", L"SearchHost.exe", L"SearchApp.exe", L"StartMenuExperienceHost.exe",
                        L"ShellExperienceHost.exe", L"ShellHost.exe", L"LockApp.exe", L"ctfmon.exe", L"Widgets.exe",
                        L"WidgetService.exe", L"dwm.exe", L"SecurityHealthSystray.exe", L"PhoneExperienceHost.exe",
                    };
                    for (const wchar_t* pn : kProcs) if (_wcsicmp(base, pn) == 0) { hit = true; break; }
                }
                CloseHandle(hp);
                if (hit) return true;
            }
        }
        return false;
    }

    static BOOL CALLBACK EnumWindowsCardsProc(HWND hWnd, LPARAM lParam) {
        EnumCardsCtx* c = (EnumCardsCtx*)lParam;
        if (!IsWindowVisible(hWnd)) return TRUE;
        const bool iconic = IsIconic(hWnd) != 0;

        LONG exStyle = GetWindowLongW(hWnd, GWL_EXSTYLE);
        if (exStyle & WS_EX_TOOLWINDOW) return TRUE;

        DWORD cloaked = 0;
        if (SUCCEEDED(DwmGetWindowAttribute(hWnd, DWMWA_CLOAKED, &cloaked, sizeof(cloaked)))) {
            // 2 = DWM_CLOAKED_SHELL (hidden because it lives on another virtual desktop)
            if (cloaked != 0 && cloaked != 2) return TRUE;
        }

        RECT rc{};
        if (iconic) {
            WINDOWPLACEMENT wp{};
            wp.length = sizeof(wp);
            if (!GetWindowPlacement(hWnd, &wp)) return TRUE;
            rc = wp.rcNormalPosition;
        } else if (FAILED(DwmGetWindowAttribute(hWnd, DWMWA_EXTENDED_FRAME_BOUNDS, &rc, sizeof(rc)))) {
            GetWindowRect(hWnd, &rc);
        }
        if ((rc.right - rc.left) < 100 || (rc.bottom - rc.top) < 100) return TRUE;

        if (!c->pVdm) return TRUE;   // cannot tell which desktop it is on: show nothing rather than the wrong thing
        {
            // A window whose desktop cannot be determined (or is "none") used to be painted onto EVERY desktop.
            GUID wId{};
            if (FAILED(c->pVdm->GetWindowDesktopId(hWnd, &wId))) return TRUE;
            if (IsEqualGUID(wId, GUID{}) || !IsEqualGUID(wId, *c->targetId)) return TRUE;
        }

        WCHAR title[256]{};
        GetWindowTextW(hWnd, title, ARRAYSIZE(title));
        if (wcslen(title) == 0) return TRUE;

        WCHAR cls[128]{};
        GetClassNameW(hWnd, cls, ARRAYSIZE(cls));
        if (IsShellHelperWindow(hWnd, cls, title, exStyle)) return TRUE;
        if (_wcsicmp(cls, L"Progman") == 0 || _wcsicmp(cls, L"WorkerW") == 0 ||
            _wcsicmp(cls, L"Shell_TrayWnd") == 0 || _wcsicmp(cls, L"Shell_SecondaryTrayWnd") == 0 ||
            _wcsicmp(cls, L"SeamlessCompizCubeOverlayWindow") == 0) {
            return TRUE;
        }

        WindowCard card;
        card.title = title;
        card.rect = rc;
        card.hwnd = hWnd;
        card.minimized = iconic;
        c->pOut->push_back(card);
        return c->pOut->size() < 16;
    }

    // Windows are returned top-most first.
    static void GetWindowsForDesktop(const GUID& desktopId, std::vector<WindowCard>& outCards) {
        outCards.clear();
        com_ptr<IVirtualDesktopManager> vdm;
        CoCreateInstance(CLSID_VirtualDesktopManager, nullptr, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(vdm.put()));
        EnumCardsCtx ctx = { &desktopId, vdm.get(), &outCards };
        EnumWindows(EnumWindowsCardsProc, (LPARAM)&ctx);
    }

} // namespace VDManager

// ============================================================================
// MODULE 2: DesktopCaptureManager (shared snapshots, versioned)
// ============================================================================
namespace DesktopCaptureManager {

    struct SnapshotData {
        int width = 0;
        int height = 0;
        std::vector<uint32_t> pixels;   // BGRA, alpha forced to 0xFF
        bool composed = false;          // true: rebuilt from wallpaper + window captures
        ULONGLONG tick = 0;
    };
    using SnapPtr = std::shared_ptr<const SnapshotData>;

    struct Entry {
        SnapPtr data;
        uint64_t version = 0;
    };

    static std::mutex s_mutex;
    static std::unordered_map<std::wstring, Entry> s_cache;
    static uint64_t s_versionCounter = 0;

    // Faces are never drawn wider than this (the texture quality cap) and the background uses a quarter scale,
    // so stored snapshots never need more pixels than this.
    static constexpr int kSnapMaxW = 1920;

    // Box-filter downscale of a BGRA image (tw <= w, th <= h). Alpha is forced to 0xFF.
    static void BoxDownscale(const uint32_t* src, int w, int h, std::vector<uint32_t>& dst, int tw, int th) {
        dst.resize((size_t)tw * th);
        std::vector<int> xs((size_t)tw + 1);
        for (int x = 0; x <= tw; ++x) xs[x] = (int)((int64_t)x * w / tw);
        for (int y = 0; y < th; ++y) {
            const int y0 = (int)((int64_t)y * h / th);
            int y1 = (int)((int64_t)(y + 1) * h / th);
            if (y1 <= y0) y1 = y0 + 1;
            if (y1 > h) y1 = h;
            uint32_t* d = &dst[(size_t)y * tw];
            for (int x = 0; x < tw; ++x) {
                const int x0 = xs[x];
                int x1 = xs[x + 1];
                if (x1 <= x0) x1 = x0 + 1;
                if (x1 > w) x1 = w;
                uint32_t b = 0, g = 0, r = 0;
                for (int yy = y0; yy < y1; ++yy) {
                    const uint32_t* row = src + (size_t)yy * w;
                    for (int xx = x0; xx < x1; ++xx) {
                        const uint32_t px = row[xx];
                        b += px & 0xFFu; g += (px >> 8) & 0xFFu; r += (px >> 16) & 0xFFu;
                    }
                }
                const uint32_t n = (uint32_t)((y1 - y0) * (x1 - x0));
                d[x] = 0xFF000000u | ((r / n) << 16) | ((g / n) << 8) | (b / n);
            }
        }
    }

    // Nearest-neighbour scale (used to expand the cached, reduced wallpaper back to the monitor size).
    static void NearestScale(const uint32_t* src, int sw, int sh, std::vector<uint32_t>& dst, int w, int h) {
        dst.resize((size_t)w * h);
        std::vector<int> xmap((size_t)w);
        for (int x = 0; x < w; ++x) xmap[x] = (int)((int64_t)x * sw / w);
        for (int y = 0; y < h; ++y) {
            const uint32_t* row = src + (size_t)((int64_t)y * sh / h) * sw;
            uint32_t* d = &dst[(size_t)y * w];
            for (int x = 0; x < w; ++x) d[x] = row[xmap[x]];
        }
    }

    // Copies a w*h BGRA image into a snapshot that is at most kSnapMaxW wide (alpha forced to 0xFF).
    static std::shared_ptr<SnapshotData> MakeCompactSnapshot(const uint32_t* px, int w, int h, bool composed, ULONGLONG tick) {
        if (!px || w <= 0 || h <= 0) return nullptr;
        auto out = std::make_shared<SnapshotData>();
        out->composed = composed;
        out->tick = tick;
        if (w > kSnapMaxW) {
            const int tw = kSnapMaxW;
            const int th = std::max(1, (int)((int64_t)h * tw / w));
            out->width = tw;
            out->height = th;
            BoxDownscale(px, w, h, out->pixels, tw, th);
        } else {
            out->width = w;
            out->height = h;
            out->pixels.assign(px, px + (size_t)w * h);
            for (auto& v : out->pixels) v |= 0xFF000000u;
        }
        return out;
    }

    static std::wstring GuidToString(const GUID& id) {
        wchar_t sz[48]{};
        swprintf_s(sz, L"{%08lX-%04hX-%04hX-%02X%02X-%02X%02X%02X%02X%02X%02X}",
            id.Data1, id.Data2, id.Data3,
            (unsigned)id.Data4[0], (unsigned)id.Data4[1], (unsigned)id.Data4[2], (unsigned)id.Data4[3],
            (unsigned)id.Data4[4], (unsigned)id.Data4[5], (unsigned)id.Data4[6], (unsigned)id.Data4[7]);
        return sz;
    }

    static std::shared_ptr<SnapshotData> CaptureMonitorScreen(RECT rcMon) {
        int w = rcMon.right - rcMon.left;
        int h = rcMon.bottom - rcMon.top;
        if (w <= 0 || h <= 0) return nullptr;

        HDC hdcScreen = GetDC(nullptr);
        if (!hdcScreen) return nullptr;
        HDC hdcMem = CreateCompatibleDC(hdcScreen);
        if (!hdcMem) { ReleaseDC(nullptr, hdcScreen); return nullptr; }

        BITMAPINFO bmi{};
        bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
        bmi.bmiHeader.biWidth = w;
        bmi.bmiHeader.biHeight = -h;
        bmi.bmiHeader.biPlanes = 1;
        bmi.bmiHeader.biBitCount = 32;
        bmi.bmiHeader.biCompression = BI_RGB;

        void* bits = nullptr;
        HBITMAP dib = CreateDIBSection(hdcScreen, &bmi, DIB_RGB_COLORS, &bits, nullptr, 0);
        if (!dib || !bits) {
            DeleteDC(hdcMem);
            ReleaseDC(nullptr, hdcScreen);
            return nullptr;
        }

        HGDIOBJ old = SelectObject(hdcMem, dib);
        BitBlt(hdcMem, 0, 0, w, h, hdcScreen, rcMon.left, rcMon.top, SRCCOPY | CAPTUREBLT);

        auto out = std::make_shared<SnapshotData>();
        out->width = w;
        out->height = h;
        out->pixels.resize((size_t)w * h);
        memcpy(out->pixels.data(), bits, (size_t)w * h * sizeof(uint32_t));
        for (auto& px : out->pixels) px |= 0xFF000000;
        out->composed = false;
        out->tick = GetTickCount64();

        SelectObject(hdcMem, old);
        DeleteObject(dib);
        DeleteDC(hdcMem);
        ReleaseDC(nullptr, hdcScreen);
        return out;
    }

    static void Store(const GUID& id, std::shared_ptr<SnapshotData> d) {
        if (!d) return;
        // The caller may hand in a full-resolution capture (it keeps its own copy for the live feed's first frame).
        // The cache only ever holds the compact version.
        if (d->width > kSnapMaxW && !d->pixels.empty()) {
            auto small = MakeCompactSnapshot(d->pixels.data(), d->width, d->height, d->composed, d->tick);
            if (small) d = small;
        }
        std::lock_guard<std::mutex> lock(s_mutex);
        Entry& e = s_cache[GuidToString(id)];
        // A recent exact screenshot beats a rebuilt one.
        if (e.data && !e.data->composed && d->composed &&
            (GetTickCount64() - e.data->tick) < 120000ULL) {
            return;
        }
        e.data = d;
        e.version = ++s_versionCounter;
    }

    static SnapPtr Get(const GUID& id, uint64_t* ver = nullptr) {
        std::lock_guard<std::mutex> lock(s_mutex);
        auto it = s_cache.find(GuidToString(id));
        if (it != s_cache.end() && it->second.data && !it->second.data->pixels.empty()) {
            if (ver) *ver = it->second.version;
            return it->second.data;
        }
        if (ver) *ver = 0;
        return nullptr;
    }

    static uint64_t Version(const GUID& id) {
        std::lock_guard<std::mutex> lock(s_mutex);
        auto it = s_cache.find(GuidToString(id));
        return it != s_cache.end() ? it->second.version : 0;
    }

    static void Clear() {
        std::lock_guard<std::mutex> lock(s_mutex);
        s_cache.clear();
    }

    // Drops snapshots of desktops that no longer exist and snapshots older than maxAgeMs.
    static void Prune(const VDManager::DesktopList& list, ULONGLONG maxAgeMs) {
        std::lock_guard<std::mutex> lock(s_mutex);
        const ULONGLONG now = GetTickCount64();
        for (auto it = s_cache.begin(); it != s_cache.end();) {
            bool keep = false;
            for (const auto& item : list.items) {
                if (GuidToString(item.id) == it->first) { keep = true; break; }
            }
            if (keep && it->second.data && (now - it->second.data->tick) > maxAgeMs) keep = false;
            if (keep) ++it; else it = s_cache.erase(it);
        }
    }

} // namespace DesktopCaptureManager

// ============================================================================
// MODULE 2b: Wallpaper loader (WIC) and desktop composer (PrintWindow)
// ============================================================================
namespace WallpaperLoader {

    static std::mutex s_mtx;
    static std::wstring s_cachePath;
    static int s_cw = 0, s_ch = 0;       // size that was requested
    static int s_sw = 0, s_sh = 0;       // size of the stored (reduced) copy
    static std::vector<uint32_t> s_cache;

    static int GetStyle(bool& tile) {
        tile = false;
        int style = 10;
        HKEY h = nullptr;
        if (RegOpenKeyExW(HKEY_CURRENT_USER, L"Control Panel\\Desktop", 0, KEY_READ, &h) == ERROR_SUCCESS) {
            wchar_t buf[16]{};
            DWORD sz = sizeof(buf);
            if (RegQueryValueExW(h, L"WallpaperStyle", nullptr, nullptr, (LPBYTE)buf, &sz) == ERROR_SUCCESS) {
                style = _wtoi(buf);
            }
            wchar_t tbuf[16]{};
            sz = sizeof(tbuf);
            if (RegQueryValueExW(h, L"TileWallpaper", nullptr, nullptr, (LPBYTE)tbuf, &sz) == ERROR_SUCCESS) {
                tile = _wtoi(tbuf) != 0;
            }
            RegCloseKey(h);
        }
        return style;
    }

    // Fills out with a w*h BGRA image of the wallpaper (or a solid desktop colour).
    static bool Load(int w, int h, std::vector<uint32_t>& out) {
        COLORREF bg = GetSysColor(COLOR_DESKTOP);
        uint32_t bgPx = 0xFF000000u | (GetRValue(bg) << 16) | (GetGValue(bg) << 8) | GetBValue(bg);
        out.assign((size_t)w * h, bgPx);

        WCHAR path[MAX_PATH]{};
        if (!SystemParametersInfoW(SPI_GETDESKWALLPAPER, MAX_PATH, path, 0) || !path[0]) return false;

        {
            std::lock_guard<std::mutex> lk(s_mtx);
            if (s_cw == w && s_ch == h && s_cachePath == path && !s_cache.empty()) {
                if (s_sw == w && s_sh == h) out = s_cache;
                else DesktopCaptureManager::NearestScale(s_cache.data(), s_sw, s_sh, out, w, h);
                return true;
            }
        }

        bool tile = false;
        int style = GetStyle(tile);

        com_ptr<IWICImagingFactory> fac;
        if (FAILED(CoCreateInstance(kClsidWICImagingFactory, nullptr, CLSCTX_INPROC_SERVER,
                                    IID_PPV_ARGS(fac.put()))) || !fac) return false;

        com_ptr<IWICBitmapDecoder> dec;
        if (FAILED(fac->CreateDecoderFromFilename(path, nullptr, GENERIC_READ,
                                                  WICDecodeMetadataCacheOnDemand, dec.put())) || !dec) return false;
        com_ptr<IWICBitmapFrameDecode> frame;
        if (FAILED(dec->GetFrame(0, frame.put())) || !frame) return false;

        UINT iw = 0, ih = 0;
        frame->GetSize(&iw, &ih);
        if (iw == 0 || ih == 0) return false;

        double sx = (double)w / iw, sy = (double)h / ih;
        UINT tw = iw, th = ih;
        if (style == 2) {                 // stretch
            tw = (UINT)w; th = (UINT)h;
        } else if (style == 6) {          // fit
            double s = std::min(sx, sy);
            tw = std::max<UINT>(1, (UINT)std::lround(iw * s));
            th = std::max<UINT>(1, (UINT)std::lround(ih * s));
        } else if (style == 10 || style == 22) {   // fill / span
            double s = std::max(sx, sy);
            tw = std::max<UINT>(1, (UINT)std::lround(iw * s));
            th = std::max<UINT>(1, (UINT)std::lround(ih * s));
        }                                 // else: center, no scaling

        com_ptr<IWICBitmapSource> src = frame;
        com_ptr<IWICBitmapScaler> scaler;
        if (tw != iw || th != ih) {
            if (SUCCEEDED(fac->CreateBitmapScaler(scaler.put())) && scaler &&
                SUCCEEDED(scaler->Initialize(frame.get(), tw, th, WICBitmapInterpolationModeFant))) {
                src = scaler;
            } else {
                return false;
            }
        }

        com_ptr<IWICFormatConverter> conv;
        if (FAILED(fac->CreateFormatConverter(conv.put())) || !conv) return false;
        if (FAILED(conv->Initialize(src.get(), kPixelFormat32bppBGR, WICBitmapDitherTypeNone,
                                    nullptr, 0.0, WICBitmapPaletteTypeCustom))) return false;

        int dx = ((int)w - (int)tw) / 2;
        int dy = ((int)h - (int)th) / 2;
        int srcX = std::max(0, -dx), srcY = std::max(0, -dy);
        int dstX = std::max(0, dx), dstY = std::max(0, dy);
        int cw = std::min((int)tw - srcX, w - dstX);
        int ch = std::min((int)th - srcY, h - dstY);
        if (cw <= 0 || ch <= 0) return false;

        std::vector<uint32_t> tmp((size_t)cw * ch);
        WICRect rc{ srcX, srcY, cw, ch };
        if (FAILED(conv->CopyPixels(&rc, cw * 4, (UINT)(tmp.size() * 4), (BYTE*)tmp.data()))) return false;

        for (int y = 0; y < ch; ++y) {
            uint32_t* d = &out[(size_t)(dstY + y) * w + dstX];
            const uint32_t* s = &tmp[(size_t)y * cw];
            for (int x = 0; x < cw; ++x) d[x] = s[x] | 0xFF000000u;
        }

        {
            // Keep only a reduced copy (at most 1920 px wide) between gestures, not a full-resolution one.
            std::vector<uint32_t> reduced;
            int rw = w, rh = h;
            if (w > DesktopCaptureManager::kSnapMaxW) {
                rw = DesktopCaptureManager::kSnapMaxW;
                rh = std::max(1, (int)((int64_t)h * rw / w));
                DesktopCaptureManager::BoxDownscale(out.data(), w, h, reduced, rw, rh);
            } else {
                reduced = out;
            }
            std::lock_guard<std::mutex> lk(s_mtx);
            s_cachePath = path;
            s_cw = w; s_ch = h;
            s_sw = rw; s_sh = rh;
            s_cache = std::move(reduced);
        }
        return true;
    }

    static void ClearCache() {
        std::lock_guard<std::mutex> lk(s_mtx);
        std::vector<uint32_t>().swap(s_cache);
        s_cachePath.clear();
        s_cw = s_ch = s_sw = s_sh = 0;
    }

} // namespace WallpaperLoader

namespace Composer {

    static std::atomic<bool> s_abort{ false };

    struct Job {
        RECT mon{};
        VDManager::DesktopList list;
    };

    static bool LooksBlank(const uint32_t* bits, int w, int h) {
        int nonBlack = 0;
        for (int gy = 0; gy < 12; ++gy)
            for (int gx = 0; gx < 12; ++gx) {
                int x = (w - 1) * gx / 11, y = (h - 1) * gy / 11;
                if ((bits[(size_t)y * w + x] & 0x00FFFFFFu) != 0) ++nonBlack;
            }
        return nonBlack == 0;
    }

    static std::shared_ptr<DesktopCaptureManager::SnapshotData> ComposeDesktop(
        const Job& job, const std::vector<uint32_t>& wall, const GUID& id) {

        const int w = job.mon.right - job.mon.left;
        const int h = job.mon.bottom - job.mon.top;

        std::vector<VDManager::WindowCard> cards;
        VDManager::GetWindowsForDesktop(id, cards);

        HDC hdcScreen = GetDC(nullptr);
        if (!hdcScreen) return nullptr;
        HDC mem = CreateCompatibleDC(hdcScreen);
        BITMAPINFO bmi{};
        bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
        bmi.bmiHeader.biWidth = w;
        bmi.bmiHeader.biHeight = -h;
        bmi.bmiHeader.biPlanes = 1;
        bmi.bmiHeader.biBitCount = 32;
        bmi.bmiHeader.biCompression = BI_RGB;
        void* bits = nullptr;
        HBITMAP dib = CreateDIBSection(hdcScreen, &bmi, DIB_RGB_COLORS, &bits, nullptr, 0);
        if (!mem || !dib || !bits) {
            if (dib) DeleteObject(dib);
            if (mem) DeleteDC(mem);
            ReleaseDC(nullptr, hdcScreen);
            return nullptr;
        }
        HGDIOBJ old = SelectObject(mem, dib);

        if (wall.size() == (size_t)w * h) memcpy(bits, wall.data(), (size_t)w * h * 4);
        else memset(bits, 0x20, (size_t)w * h * 4);

        int captured = 0;
        for (auto it = cards.rbegin(); it != cards.rend(); ++it) {
            if (s_abort.load()) break;
            if (it->minimized) continue;
            if (IsHungAppWindow(it->hwnd)) continue;   // PrintWindow would block on it, and unload waits for this thread

            RECT wr{};
            if (!GetWindowRect(it->hwnd, &wr)) continue;
            RECT fb = it->rect;     // visible frame bounds
            int ww = wr.right - wr.left, wh = wr.bottom - wr.top;
            if (ww <= 0 || wh <= 0 || ww > 8192 || wh > 8192) continue;

            HDC hw = CreateCompatibleDC(hdcScreen);
            BITMAPINFO wb{};
            wb.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
            wb.bmiHeader.biWidth = ww;
            wb.bmiHeader.biHeight = -wh;
            wb.bmiHeader.biPlanes = 1;
            wb.bmiHeader.biBitCount = 32;
            wb.bmiHeader.biCompression = BI_RGB;
            void* wbits = nullptr;
            HBITMAP wdib = CreateDIBSection(hdcScreen, &wb, DIB_RGB_COLORS, &wbits, nullptr, 0);
            if (!hw || !wdib || !wbits) {
                if (wdib) DeleteObject(wdib);
                if (hw) DeleteDC(hw);
                continue;
            }
            HGDIOBJ wold = SelectObject(hw, wdib);
            memset(wbits, 0, (size_t)ww * wh * 4);

            BOOL ok = PrintWindow(it->hwnd, hw, PW_RENDERFULLCONTENT);
            bool blank = !ok || LooksBlank((const uint32_t*)wbits, ww, wh);

            int dstX = fb.left - job.mon.left;
            int dstY = fb.top - job.mon.top;
            int fw = fb.right - fb.left, fh = fb.bottom - fb.top;

            if (!blank) {
                int sx = fb.left - wr.left, sy = fb.top - wr.top;
                if (sx < 0) sx = 0;
                if (sy < 0) sy = 0;
                BitBlt(mem, dstX, dstY, fw, fh, hw, sx, sy, SRCCOPY);
                ++captured;
            }
            // else: PrintWindow could not render this app. Leave the wallpaper visible
            // instead of drawing a black placeholder card.

            SelectObject(hw, wold);
            DeleteObject(wdib);
            DeleteDC(hw);
        }

        auto out = DesktopCaptureManager::MakeCompactSnapshot((const uint32_t*)bits, w, h, true, GetTickCount64());

        SelectObject(mem, old);
        DeleteObject(dib);
        DeleteDC(mem);
        ReleaseDC(nullptr, hdcScreen);
        LOG_DBG(L"Composed desktop: %d windows captured of %d", captured, (int)cards.size());
        return out;
    }

    static DWORD WINAPI Proc(LPVOID p) {
        std::unique_ptr<Job> job((Job*)p);
        bool com = SUCCEEDED(CoInitializeEx(nullptr, COINIT_MULTITHREADED));
        SetThreadPriority(GetCurrentThread(), THREAD_MODE_BACKGROUND_BEGIN);   // low CPU, I/O and memory priority

        try {
            const int w = job->mon.right - job->mon.left;
            const int h = job->mon.bottom - job->mon.top;
            std::vector<uint32_t> wall;
            WallpaperLoader::Load(w, h, wall);

            // Desktops next to the current one first.
            int total = job->list.TotalCount();
            std::vector<int> order;
            for (int dstep = 1; dstep < total; ++dstep) {
                int a = (job->list.currentIndex + dstep) % total;
                int b = ((job->list.currentIndex - dstep) % total + total) % total;
                if (std::find(order.begin(), order.end(), a) == order.end()) order.push_back(a);
                if (std::find(order.begin(), order.end(), b) == order.end()) order.push_back(b);
            }

            for (int idx : order) {
                if (s_abort.load()) break;
                if (idx == job->list.currentIndex) continue;
                const GUID& id = job->list.items[idx].id;
                auto existing = DesktopCaptureManager::Get(id);
                if (existing && (GetTickCount64() - existing->tick) <
                                    (existing->composed ? 20000ULL : 120000ULL)) continue;   // fresh enough, skip the expensive re-capture

                auto snap = ComposeDesktop(*job, wall, id);
                if (snap) DesktopCaptureManager::Store(id, snap);
            }
        } catch (...) {
        }

        SetThreadPriority(GetCurrentThread(), THREAD_MODE_BACKGROUND_END);
        if (com) CoUninitialize();
        return 0;
    }

    static HANDLE Start(std::unique_ptr<Job> job) {
        return CreateThread(nullptr, 0, Proc, job.release(), 0, nullptr);
    }

} // namespace Composer

// ============================================================================
// Gesture state + cross-module forward declarations
// ============================================================================
enum class GestureState { Idle, Arming, ActiveDrag, Committing };

namespace GestureController {
    void OnSnapCompleted();
    void OnCancel();
    GestureState GetState();
    void AttachHooks();
    void DetachHooks();
    void ResyncMouse();
    void OnActiveMouseUp();
    void RescaleYaw(float k);
}

// ============================================================================
// Direct2D helpers
// ============================================================================
template <typename F>
static bool DrawToSurface(CompositionDrawingSurface const& surface, F&& fn) {
    if (!surface) return false;
    ICompositionDrawingSurfaceInteropX* si = nullptr;
    IUnknown* unk = (IUnknown*)winrt::get_abi(surface);
    if (FAILED(unk->QueryInterface(IID_ICompositionDrawingSurfaceInteropX, (void**)&si)) || !si) {
        return false;
    }

    bool ok = false;
    ID2D1DeviceContext* ctx = nullptr;
    POINT offset{};
    HRESULT hr = si->BeginDraw(nullptr, __uuidof(ID2D1DeviceContext), (void**)&ctx, &offset);
    if (SUCCEEDED(hr) && ctx) {
        ctx->SetDpi(96.0f, 96.0f);
        fn(ctx, offset);
        ctx->SetTransform(D2D1::Matrix3x2F::Identity());
        si->EndDraw();
        ctx->Release();
        ok = true;
    } else {
        LOG_ERR(L"BeginDraw failed 0x%08X", (unsigned)hr);
    }
    si->Release();
    return ok;
}

static bool CreateBitmapFromSnapshot(ID2D1DeviceContext* ctx,
                                     const DesktopCaptureManager::SnapshotData& snap,
                                     ID2D1Bitmap1** outBitmap) {
    D2D1_BITMAP_PROPERTIES1 props = D2D1::BitmapProperties1(
        D2D1_BITMAP_OPTIONS_NONE,
        D2D1::PixelFormat(DXGI_FORMAT_B8G8R8A8_UNORM, D2D1_ALPHA_MODE_PREMULTIPLIED),
        96.0f, 96.0f);
    return SUCCEEDED(ctx->CreateBitmap(
        D2D1::SizeU(snap.width, snap.height),
        snap.pixels.data(),
        snap.width * sizeof(uint32_t),
        props,
        outBitmap));
}

struct FaceColor { uint8_t r, g, b; };
static const FaceColor kFaceAccents[kMaxFaces] = {
    { 137, 180, 250 },  // blue   #89B4FA
    { 203, 166, 247 },  // mauve  #CBA6F7
    { 250, 179, 135 },  // peach  #FAB387
    { 148, 226, 213 },  // teal   #94E2D5
    { 245, 194, 231 },  // pink   #F5C2E7
    { 249, 226, 175 }   // yellow #F9E2AF
};

#ifdef SCC_TEST
static std::atomic<int> g_testCurX{ -1000000 };
static std::atomic<int> g_testCurY{ -1000000 };
#endif
static bool ReadCursorPos(POINT* p) {
#ifdef SCC_TEST
    if (g_testCurX.load() != -1000000) { p->x = g_testCurX.load(); p->y = g_testCurY.load(); return true; }
#endif
    return GetCursorPos(p) != 0;
}
static winrt::Windows::UI::Color ArgbColor(uint32_t c) {
    return winrt::Windows::UI::Color{ (uint8_t)(c >> 24), (uint8_t)(c >> 16), (uint8_t)(c >> 8), (uint8_t)c };
}

// ============================================================================
// MODULE 3: CubeRenderer
//
// One PERSISTENT render thread (window, compositor, D3D/D2D devices stay warm between
// gestures). Per gesture it builds the scene, runs a vblank-locked loop and tears the scene down.
// Mouse input is read on this thread (not on the busy taskbar thread).
// ============================================================================
static const float kBadgeW = 280.0f;
static const int kMaxAlt = 12;

// One live thumbnail card per window of the switcher.
struct AltSurf {
    CompositionDrawingSurface surf{ nullptr };
    RECT box{};          // window area inside the work-area texture (pixels)
    int w = 0, h = 0;    // thumbnail size
    bool ok = false;
    // Real per-window capture (PrintWindow), used when another window covers this one on screen
    std::vector<BYTE> snap;
    int snapW = 0, snapH = 0;
    RECT snapSrc{};
    ULONGLONG snapTick = 0;
    bool snapValid = false;
};

struct AltWin {
    HWND hwnd = nullptr;
    RECT r{};                 // visible part on this monitor (screen coordinates)
    std::wstring title;
};

// Brings a window to the front like Alt+Tab does.
static void ActivateWindowNow(HWND h) {
    if (!h || !IsWindow(h)) return;
    if (IsIconic(h)) ShowWindow(h, SW_RESTORE);
    // Allows to steal focus. An empty SendInput right before SetForegroundWindow is the supported way
    // (no AttachThreadInput: attached threads share one input queue, so a hung app would freeze this thread).
    INPUT input{};
    SendInput(1, &input, sizeof(INPUT));
    BringWindowToTop(h);
    SetForegroundWindow(h);
}

// True when a window above this one in the Alt+Tab order overlaps it, so a screen crop would show the wrong content.
static bool AltIsOccluded(const std::vector<AltWin>& v, int i) {
    for (int j = 0; j < i && j < (int)v.size(); ++j) {
        RECT x{};
        if (IntersectRect(&x, &v[j].r, &v[i].r)) return true;
    }
    return false;
}

// Captures the window's own pixels (works even when it is covered). Returns false if the app is hung or the capture fails.
static bool CaptureWindowPixels(HWND hw, const RECT& visible, AltSurf& s) {
    if (!hw || !IsWindow(hw) || IsHungAppWindow(hw)) return false;
    RECT wr{};
    if (!GetWindowRect(hw, &wr)) return false;
    const int bw = wr.right - wr.left, bh = wr.bottom - wr.top;
    if (bw < 16 || bh < 16 || bw > 8192 || bh > 8192) return false;

    HDC scr = GetDC(nullptr);
    HDC mem = CreateCompatibleDC(scr);
    BITMAPINFO bi{};
    bi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
    bi.bmiHeader.biWidth = bw;
    bi.bmiHeader.biHeight = -bh;   // top-down
    bi.bmiHeader.biPlanes = 1;
    bi.bmiHeader.biBitCount = 32;
    bi.bmiHeader.biCompression = BI_RGB;
    void* bits = nullptr;
    HBITMAP dib = CreateDIBSection(scr, &bi, DIB_RGB_COLORS, &bits, nullptr, 0);
    bool ok = false;
    if (dib && bits && mem) {
        HGDIOBJ old = SelectObject(mem, dib);
        memset(bits, 0, (size_t)bw * bh * 4);
        ok = PrintWindow(hw, mem, 0x00000002 /*PW_RENDERFULLCONTENT*/) != 0;
        SelectObject(mem, old);
        if (ok) {
            s.snap.assign((BYTE*)bits, (BYTE*)bits + (size_t)bw * bh * 4);
            s.snapW = bw; s.snapH = bh;
            s.snapSrc = { std::clamp((int)(visible.left - wr.left), 0, bw), std::clamp((int)(visible.top - wr.top), 0, bh),
                          std::clamp((int)(visible.right - wr.left), 0, bw), std::clamp((int)(visible.bottom - wr.top), 0, bh) };
            s.snapValid = (s.snapSrc.right - s.snapSrc.left >= 16 && s.snapSrc.bottom - s.snapSrc.top >= 16);
            ok = s.snapValid;
        }
    }
    if (dib) DeleteObject(dib);
    if (mem) DeleteDC(mem);
    if (scr) ReleaseDC(nullptr, scr);
    return ok;
}

// Hides the taskbar from every capture API (the mod runs inside explorer.exe, so the window is ours to flag).
// The live feed and the snapshots then show the plain desktop where the taskbar is, so no cropping is needed.
static std::vector<HWND> g_excludedTaskbars;
static bool ExcludeTaskbarsFromCapture() {
    std::vector<HWND> list;
    if (HWND t = FindWindowW(L"Shell_TrayWnd", nullptr)) list.push_back(t);
    HWND sec = nullptr;
    while ((sec = FindWindowExW(nullptr, sec, L"Shell_SecondaryTrayWnd", nullptr)) != nullptr) list.push_back(sec);
    if (list.empty()) return false;
    bool all = true;
    for (HWND h : list) {
        if (SetWindowDisplayAffinity(h, WDA_EXCLUDEFROMCAPTURE)) g_excludedTaskbars.push_back(h);
        else all = false;
    }
    return all;
}
static void RestoreTaskbarCapture() {
    for (HWND h : g_excludedTaskbars) if (IsWindow(h)) SetWindowDisplayAffinity(h, 0 /*WDA_NONE*/);
    g_excludedTaskbars.clear();
}

static const float kBadgeH = 32.0f;

class CubeRenderer {
public:
    // The one instance lives in g_renderer (below), created in Wh_ModInit and destroyed in Wh_ModUninit.
    static CubeRenderer& Instance();

    CubeRenderer() = default;
    ~CubeRenderer() = default;

    void Prewarm();
    bool Start(POINT anchorPoint, float userZoom);
    void SubmitInput(float yawDeg, float pitchDeg, float shrink01) {
        m_inYaw.store(yawDeg);
        m_inPitch.store(pitchDeg);
        m_inZoom.store(shrink01);
        Wake();
    }
    void SubmitUserZoom(float z) { m_inUserZoom.store(z); Wake(); }
    void SubmitWheelSelect(int steps) { m_selSteps.fetch_add(steps); Wake(); }
    void Commit(float flickVelDegPerSec) {
        m_inFlick.store(flickVelDegPerSec);
        m_cmd.store(1);
        Wake();
    }
    void Cancel() { m_cmd.store(2); Wake(); }
    // Right click while the cube is open. Returns true when the click hit an edge zone (and must be swallowed).
    bool OnRightDown(POINT pt);
    // Leaves the idle (power saving) pace right away.
    void Wake() {
        // Only the idle (30 Hz) pacer waits on this event. At full rate the call is two atomic ops, no syscall.
        if (m_idle.exchange(false) && m_wakeEvent) SetEvent(m_wakeEvent);
    }
    void Shutdown();
    bool IsActive() const { return m_sceneActive.load(); }

private:
    // thread plumbing
    bool EnsureThread();
    static DWORD WINAPI ThreadEntry(LPVOID p);
    static DWORD WINAPI PacerEntry(LPVOID p);
    static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
    DWORD ThreadMain();
    void PacerLoop();
    bool WarmInit();
    void Teardown();
    void RunScene();
    bool BeginScene();
    void EndScene();
    void RunLoop();
    bool Frame();
    void UpdateIdle();

    // ---- add / remove desktops, edge zones, effects ----
    void ComputeGeometry(int total);
    void BuildFaceVisuals();
    void RebuildPrism();
    void BuildOverlayFx();
    void DrawZoneSurface(bool right);
    void ShowToast(const wchar_t* text);
    void StepFx(float dt);
    void StartVdOp(int kind);
    void UpdateVdOp();
    void FinishVdOp(bool ok);
    void ApplyDesktopCountChange(const VDManager::DesktopList& nl, int oldTotal);
    void KickComposer();

    // setup
    bool EnsureDispatcherQueue();
    bool InitializeGraphicsDevice();
    void FindOutput();
    CompositionDrawingSurface MakeSurface(int w, int h);
    void BuildVisuals();
    void BuildBackground();
    ID2D1Bitmap1* GetDesktopBitmap(ID2D1DeviceContext* ctx, int dIdx);

    // drawing
    void RenderFace(int i, int dIdx);
    void RenderShadow();
    ID2D1Bitmap1* FaceBitmap(ID2D1DeviceContext* ctx, int dIdx);

    // live capture
    bool StartLive(const DesktopCaptureManager::SnapshotData* initial);
    void StopLive();
    bool CreateDuplication(int* outW, int* outH);
    bool PollLive(bool wantTex);
    void DistributeFrame(ID3D11Texture2D* src, bool wantTex);
    void DrawLive();
    bool CreateCompSwapChain(int w, int h, IDXGISwapChain1** outSc, ICompositionSurface* outSurf);
    void ComputeWorkArea(const RECT& mon, const RECT& work);

    // alt+tab style switcher
    void CollectAltWindows();
    void BuildAltVisuals();
    bool EnsureAltSurfaces();
    void DrawThumb(int i);
    void UpdateThumbs();
    void UpdateAltTab(float dt);
    void LayoutAlt(const Mat4& view, float faceDeg, float lifeEase);
    void HideAlt();
    void RedrawLabel();

    // animation
    float ComputeYawTarget(float rawYaw) const;
    void BeginCommit(bool cancel);
    void UpdateSwitching();
    void ApplyTransforms();
    int DesktopForOffset(int k) const;

    // ---- persistent thread / sync ----
    std::mutex m_threadMutex;
    HANDLE m_thread = nullptr;
    HANDLE m_goEvent = nullptr;
    HANDLE m_quitEvent = nullptr;
    HANDLE m_frameEvent = nullptr;
    HANDLE m_wakeEvent = nullptr;

    struct ZoneVisual {
        SpriteVisual vis{ nullptr };
        CompositionDrawingSurface surf{ nullptr };
        float op = 0.0f;
        float pulse = 0.0f;
        float baseX = 0.0f;     // resting x offset of the visual
        bool  shown = false;    // revealed by the pointer (read by the mouse hook, benign race)
    };
    ZoneVisual m_zoneL, m_zoneR;
    SpriteVisual m_toast{ nullptr };
    CompositionDrawingSurface m_toastSurface{ nullptr };
    float m_toastT = 0.0f;                  // 1 -> 0 while the toast is shown
    float m_zoneW = 192.0f;
    std::chrono::steady_clock::time_point m_zoneQuietUntil{};
    std::chrono::steady_clock::time_point m_vdCooldown{};
    std::atomic<int> m_pendingVdOp{ 0 };   // 0 none, 1 add, 2 remove. Set by the mouse hook, consumed in Frame().
    Spring m_kick, m_pop;                   // spin and pop when the prism is rebuilt
    int   m_bornDesktop = -1;
    float m_bornT = 1.0f;
    bool  m_fxDirty = false;
    bool  m_composeRestart = false;
    struct VdTask {
        bool active = false;
        int kind = 0;                       // 1 add, 2 remove
        int stage = 0;                      // 0 go to start desktop, 1 act, 2 wait for count, 3 go back
        int oldTotal = 0, origCur = 0, goalA = 0, goalC = 0;
        bool waiting = false;
        int waitCur = -1;
        bool jumpSent = false;              // the Seamless Window Manager hotkey was sent for this leg
        bool swmFailed = false;             // not available or did not react: use the Windows shortcut
        int jumpStartCur = -1;
        std::chrono::steady_clock::time_point jumpAt;
        std::chrono::steady_clock::time_point nextAt, deadline, waitDeadline, actDeadline;
    } m_vd;
    std::atomic<bool> m_idle{ false };      // pacer runs at a low rate while nothing moves
    int  m_idleFrames = 0;
    bool m_busy = false;                    // something changed in this frame
    bool m_presentPending = false;          // a live Present was refused (GPU busy), retry next frame
    std::atomic<bool> m_sceneActive{ false };
    std::atomic<int> m_cmd{ 0 };            // 1 = commit, 2 = cancel
    std::atomic<float> m_inYaw{ 0.0f };
    std::atomic<float> m_inPitch{ 0.0f };
    std::atomic<float> m_inZoom{ 0.0f };
    std::atomic<float> m_inFlick{ 0.0f };
    std::atomic<float> m_inUserZoom{ 1.0f };

    ModSettings m_cfg;
    POINT m_anchor{};

    // ---- persistent overlay objects (render thread only) ----
    HWND m_hwnd = nullptr;
    Compositor m_compositor{ nullptr };
    DesktopWindowTarget m_target{ nullptr };
    ContainerVisual m_emptyRoot{ nullptr };
    CompositionGraphicsDevice m_graphicsDevice{ nullptr };
    winrt::Windows::System::DispatcherQueueController m_dqController{ nullptr };

    ID3D11Device* m_d3dDevice = nullptr;
    ID2D1Factory1* m_d2dFactory = nullptr;
    ID2D1Device* m_d2dDevice = nullptr;
    IDWriteFactory* m_dwriteFactory = nullptr;
    IDWriteTextFormat* m_textFormatBadge = nullptr;
    std::wstring m_fontSig;
    void EnsureTextFormat();

    // ---- per-scene objects ----
    ContainerVisual m_rootVisual{ nullptr };
    SpriteVisual m_backdropVisual{ nullptr };
    SpriteVisual m_backgroundVisual{ nullptr };
    CompositionDrawingSurface m_bgSurface{ nullptr };
    SpriteVisual m_shadowVisual{ nullptr };
    CompositionDrawingSurface m_shadowSurface{ nullptr };
    ContainerVisual m_cubeContainer{ nullptr };

    IDXGIOutput* m_output = nullptr;       // used for vblank pacing (any adapter)
    IDXGIOutput* m_dupOutput = nullptr;    // same adapter as the D3D device (duplication)
    bool m_canExclude = false;
    void ApplyCaptureAffinity(bool recordingMode);
    float m_monitorHz = 0.0f;
    int m_bgW = 0, m_bgH = 0;

    // ---- live desktop feed ----
    enum class LiveSource { None, Dup, Gdi };
    LiveSource m_liveSource = LiveSource::None;
    IDXGIOutputDuplication* m_dup = nullptr;
    ID3D11DeviceContext* m_d3dCtx = nullptr;
    ID3D11Texture2D* m_liveTex = nullptr;
    ID2D1Bitmap1* m_liveBmp = nullptr;
    int m_liveW = 0, m_liveH = 0;
    int m_liveDesktop = -1;
    bool m_liveHasFrame = false;
    int m_liveFrames = 0;
    ULONGLONG m_dupRetryAt = 0;
    ULONGLONG m_gdiNext = 0;
    HDC m_gdiMem = nullptr;
    HBITMAP m_gdiDib = nullptr;
    HGDIOBJ m_gdiOld = nullptr;
    void* m_gdiBits = nullptr;
    int m_fpsFrames = 0;
    const wchar_t* m_liveStatus = L"STATIC";
    IDXGISwapChain1* m_sc = nullptr;
    ICompositionSurface m_liveSurface{ nullptr };
    LONGLONG m_bgNext = 0;
    bool m_texFresh = false;               // m_liveTex holds a frame the blurred background has not drawn yet
    ID3D11Texture2D* m_gdiTex = nullptr;   // GDI fallback frame (full monitor)
    RECT m_workPx{};                       // work area (no taskbar) in capture pixels
    RECT m_workRect{};                     // work area in screen coordinates
    int m_workW = 0, m_workH = 0;
    std::vector<AltSurf> m_altSurf;
    bool m_thumbFresh = false;
    int m_thumbRR = 0;

    // work area (taskbar removed) as fractions of the monitor
    float m_wl = 0.0f, m_wt = 0.0f, m_wr = 1.0f, m_wb = 1.0f;

    // alt+tab switcher state
    std::vector<AltWin> m_alt;
    bool m_altReady = false;
    bool m_altAttached = false;
    bool m_altShown = false;
    bool m_altOrderDirty = true;
    bool m_altDirty = false;
    bool m_selMode = false;
    int m_selIdx = 0;
    int m_labelIdx = -1;
    float m_selT = 0.0f;
    std::atomic<int> m_selSteps{ 0 };
    std::vector<SpriteVisual> m_winVis;
    std::vector<CompositionSurfaceBrush> m_winBrush;
    float m_winLift[kMaxAlt] = {};
    float m_winOp[kMaxAlt] = {};
    SpriteVisual m_glow{ nullptr };
    SpriteVisual m_label{ nullptr };
    CompositionDrawingSurface m_labelSurface{ nullptr };
    CompositionSurfaceBrush m_labelBrush{ nullptr };
    LARGE_INTEGER m_fpsT0{};
    HANDLE m_pacerThread = nullptr;
    std::atomic<bool> m_pacerStop{ false };
    HANDLE m_composeThread = nullptr;

    struct CachedBitmap {
        ID2D1Bitmap1* bmp = nullptr;
        uint64_t ver = 0;
    };
    std::unordered_map<int, CachedBitmap> m_bitmapCache;

    struct FaceVisuals {
        ContainerVisual container{ nullptr };
        SpriteVisual background{ nullptr };
        SpriteVisual shade{ nullptr };
        SpriteVisual rim{ nullptr };
        SpriteVisual layer{ nullptr };
        CompositionDrawingSurface surface{ nullptr };
        CompositionDrawingSurface layerSurface{ nullptr };
        CompositionSurfaceBrush brush{ nullptr };
        CompositionSurfaceBrush layerBrush{ nullptr };
        int renderedDesktop = -99;
        uint64_t renderedVersion = 0;
        CompositionSurfaceBrush liveBrush{ nullptr };
        bool usingLive = false;
        // Last values written to the compositor. Re-writing an identical value still dirties the visual tree.
        float cBg = -1.0f, cRim = -1.0f, cShade = -1.0f, cLayer = -1.0f;
        signed char cVisContainer = -1, cVisShade = -1, cVisLayer = -1, cVisRim = -1;
        // Rounded clip and the two border rings (resting colour, blue to mauve gradient).
        CompositionGeometricClip clip{ nullptr };
        CompositionRoundedRectangleGeometry clipGeo{ nullptr };
        ShapeVisual borderRest{ nullptr };
        ShapeVisual borderAct{ nullptr };
        CompositionRoundedRectangleGeometry geoRest{ nullptr };
        CompositionRoundedRectangleGeometry geoAct{ nullptr };
        CompositionSpriteShape shapeRest{ nullptr };
        CompositionSpriteShape shapeAct{ nullptr };
        bool clipOn = false;
        float bAmt = 0.0f, bTarget = 0.0f;               // eased highlight amount and where it is heading
        float cRad = -1.0f, cBw = -1.0f, cBr = -1.0f, cBa = -1.0f;
        signed char cVisBr = -1, cVisBa = -1;
    };
    FaceVisuals m_faces[kMaxFaces];
    void MakeFaceBorder(FaceVisuals& f);
    void UpdateFaceShape(FaceVisuals& f, float rf, float bwF);
    POINT m_hoverLast{ -32768, -32768 };
    int m_zOrder[kMaxFaces] = { 0, 1, 2, 3, 4, 5 };
    bool m_zOrderValid = false;

    // ---- geometry ----
    int m_faceCount = 4;
    float m_stepDeg = 90.0f;
    float m_D = 300.0f;
    float m_faceWidth = 480.0f;
    float m_faceHeight = 320.0f;
    float m_screenWidth = 1920.0f;
    float m_screenHeight = 1080.0f;
    int m_texW = 1920;
    int m_texH = 1080;
    float m_zoomRelease = 1.0f;
    float m_applied[4] = { 1e9f, 1e9f, 1e9f, 1e9f };
    float m_shadowW = 600.0f;
    float m_shadowH = 150.0f;
    int m_frameCounter = 0;

    VDManager::DesktopList m_desktopList;
    RECT m_monitorRect{};
    HMONITOR m_hMonitor = nullptr;

    // ---- animation state ----
    enum class Phase { Drag, Settle, Fade };
    Phase m_phase = Phase::Drag;
    Spring m_yaw, m_pitch, m_zoom, m_uz;
    float m_snapYaw = 0.0f;
    LARGE_INTEGER m_qpcFreq{};
    LARGE_INTEGER m_lastQpc{};
    std::chrono::steady_clock::time_point m_settleStart;
    std::chrono::steady_clock::time_point m_fadeStart;

    // ---- desktop switch state ----
    bool m_needSwitch = false;
    bool m_switchConfirmed = false;
    int m_targetDesktop = -1;
    int m_stepsLeft = 0;
    int m_stepDir = 0;
    int m_stepIntervalMs = 45;
    int m_switchTimeoutMs = 1500;
    std::chrono::steady_clock::time_point m_switchStart;
    std::chrono::steady_clock::time_point m_nextStep;
    std::chrono::steady_clock::time_point m_lastStepSent;
    std::chrono::steady_clock::time_point m_nextPoll;
    bool m_swmMode = false;              // this switch goes through Seamless Window Manager's hotkey
    bool m_swmSent = false;
    int  m_swmStartIdx = -1;
    std::chrono::steady_clock::time_point m_swmSentAt;
    std::chrono::steady_clock::time_point m_confirmTime;
};

// Only touched on the render thread (registered in WarmInit, unregistered in Teardown).
static bool g_overlayClassRegistered = false;
static const wchar_t* kOverlayClassName = L"SeamlessCompizCubeOverlayWindow";

// The one renderer. [[clang::no_destroy]]: when explorer.exe itself exits Wh_ModUninit is not called, the render thread
// is already gone, and the C++ runtime must not destroy Composition objects of a dead thread under the loader lock.
[[clang::no_destroy]] static std::optional<CubeRenderer> g_renderer;

CubeRenderer& CubeRenderer::Instance() {
    return *g_renderer;
}

// ---------------------------------------------------------------------------
// Public API
// ---------------------------------------------------------------------------
bool CubeRenderer::EnsureThread() {
    std::lock_guard<std::mutex> lk(m_threadMutex);
    // Checked under the same mutex Shutdown() uses to read m_thread: either Shutdown sees the thread created here,
    // or this call sees the flag and refuses. A thread nobody waits for can never start during unload.
    if (g_unloading.load()) return false;
    if (m_thread) {
        if (WaitForSingleObject(m_thread, 0) == WAIT_OBJECT_0) {
            CloseHandle(m_thread);
            m_thread = nullptr;
        } else {
            return true;
        }
    }
    if (!m_goEvent) m_goEvent = CreateEventW(nullptr, FALSE, FALSE, nullptr);
    if (!m_quitEvent) m_quitEvent = CreateEventW(nullptr, TRUE, FALSE, nullptr);
    if (!m_frameEvent) m_frameEvent = CreateEventW(nullptr, FALSE, FALSE, nullptr);
    if (!m_wakeEvent) m_wakeEvent = CreateEventW(nullptr, FALSE, FALSE, nullptr);
    if (!m_goEvent || !m_quitEvent || !m_frameEvent || !m_wakeEvent) return false;
    ResetEvent(m_quitEvent);
    m_thread = CreateThread(nullptr, 0, ThreadEntry, this, 0, nullptr);
    return m_thread != nullptr;
}

void CubeRenderer::Prewarm() {
    EnsureThread();
}

bool CubeRenderer::Start(POINT anchorPoint, float userZoom) {
    if (m_sceneActive.load()) return false;
    if (!EnsureThread()) return false;

    m_cfg = g_settings;
    m_anchor = anchorPoint;
    m_inYaw.store(0.0f);
    m_inPitch.store(0.0f);
    m_inZoom.store(0.0f);
    m_inFlick.store(0.0f);
    m_inUserZoom.store(userZoom);
    m_cmd.store(0);

    m_sceneActive.store(true);
    SetEvent(m_goEvent);
    return true;
}

void CubeRenderer::Shutdown() {
    Composer::s_abort.store(true);
    HANDLE t = nullptr;
    {
        std::lock_guard<std::mutex> lk(m_threadMutex);
        t = m_thread;
    }
    if (t) {
        if (m_quitEvent) SetEvent(m_quitEvent);
        // No timeout: the mod image must not be unmapped while this thread (or the pacer / composer it waits for) still runs.
        WaitForSingleObject(t, INFINITE);
        std::lock_guard<std::mutex> lk(m_threadMutex);
        CloseHandle(m_thread);
        m_thread = nullptr;
    }
    if (m_goEvent) { CloseHandle(m_goEvent); m_goEvent = nullptr; }
    if (m_quitEvent) { CloseHandle(m_quitEvent); m_quitEvent = nullptr; }
    if (m_frameEvent) { CloseHandle(m_frameEvent); m_frameEvent = nullptr; }
    if (m_wakeEvent) { CloseHandle(m_wakeEvent); m_wakeEvent = nullptr; }
    m_sceneActive.store(false);
}

// ---------------------------------------------------------------------------
// Thread
// ---------------------------------------------------------------------------
DWORD WINAPI CubeRenderer::ThreadEntry(LPVOID p) {
    return ((CubeRenderer*)p)->ThreadMain();
}

DWORD CubeRenderer::ThreadMain() {
    bool comInit = false;
    try {
        winrt::init_apartment(winrt::apartment_type::single_threaded);
        comInit = true;
    } catch (...) {
    }

    // Slightly raised priority + the light "Window Manager" MMCSS profile (not "Games", which keeps the CPU/GPU clocks high).
    SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_ABOVE_NORMAL);
    {
        HMODULE hAv = LoadLibraryW(L"avrt.dll");
        if (hAv) {
            typedef HANDLE(WINAPI* AvSetFn)(LPCWSTR, LPDWORD);
            auto fn = (AvSetFn)GetProcAddress(hAv, "AvSetMmThreadCharacteristicsW");
            if (fn) {
                DWORD idx = 0;
                fn(L"Window Manager", &idx);
            }
        }
    }

    bool ok = false;
    try {
        ok = WarmInit();
    } catch (winrt::hresult_error const& e) {
        LOG_ERR(L"WinRT exception in warm init 0x%08X", (unsigned)e.code().value);
    } catch (...) {
        LOG_ERR(L"Unknown exception in warm init");
    }

    if (!ok) {
        if (m_sceneActive.exchange(false)) GestureController::OnSnapCompleted();
    } else {
        LOG_INF(L"Render thread warm");
        for (;;) {
            HANDLE h[2] = { m_goEvent, m_quitEvent };
            DWORD r = MsgWaitForMultipleObjectsEx(2, h, INFINITE, QS_ALLINPUT, MWMO_INPUTAVAILABLE);
            if (r == WAIT_OBJECT_0 + 2) {
                MSG msg;
                while (PeekMessageW(&msg, nullptr, 0, 0, PM_REMOVE)) {
                    TranslateMessage(&msg);
                    DispatchMessageW(&msg);
                }
                continue;
            }
            if (r == WAIT_OBJECT_0 + 1) break;
            if (r == WAIT_OBJECT_0) {
                RunScene();
                if (WaitForSingleObject(m_quitEvent, 0) == WAIT_OBJECT_0) break;
            }
        }
    }

    try { Teardown(); } catch (...) {}
    VDManager::SuppressSystemAnimation(false);
    if (comInit) {
        try { winrt::uninit_apartment(); } catch (...) {}
    }
    return 0;
}

void CubeRenderer::RunScene() {
    bool ok = false;
    timeBeginPeriod(1);   // only while the cube is on screen
    try {
        ok = BeginScene();
    } catch (winrt::hresult_error const& e) {
        LOG_ERR(L"WinRT exception in BeginScene 0x%08X", (unsigned)e.code().value);
    } catch (...) {
        LOG_ERR(L"Unknown exception in BeginScene");
    }

    if (ok) {
        try {
            RunLoop();
        } catch (winrt::hresult_error const& e) {
            LOG_ERR(L"WinRT exception in loop 0x%08X", (unsigned)e.code().value);
        } catch (...) {
            LOG_ERR(L"Unknown exception in loop");
        }
    }

    try { EndScene(); } catch (...) {}
    timeEndPeriod(1);
    VDManager::SuppressSystemAnimation(false);
    m_sceneActive.store(false);
    GestureController::OnSnapCompleted();
}

bool CubeRenderer::EnsureDispatcherQueue() {
    if (winrt::Windows::System::DispatcherQueue::GetForCurrentThread()) return true;

    HMODULE hCore = LoadLibraryExW(L"CoreMessaging.dll", nullptr, LOAD_LIBRARY_SEARCH_SYSTEM32);
    if (!hCore) return false;

    typedef HRESULT(WINAPI* CreateDQCFn)(DispatcherQueueOptionsX, void**);
    auto fn = (CreateDQCFn)GetProcAddress(hCore, "CreateDispatcherQueueController");
    if (!fn) return false;

    DispatcherQueueOptionsX opts{ sizeof(opts), 2 /*CURRENT*/, 0 /*COM_NONE*/ };
    HRESULT hr = fn(opts, winrt::put_abi(m_dqController));
    if (FAILED(hr)) {
        LOG_ERR(L"CreateDispatcherQueueController failed 0x%08X", (unsigned)hr);
        return false;
    }
    return winrt::Windows::System::DispatcherQueue::GetForCurrentThread() != nullptr;
}

bool CubeRenderer::InitializeGraphicsDevice() {
    if (m_graphicsDevice) return true;

    // Use the GPU that actually drives the monitor under the mouse. With "high performance" set for
    // explorer.exe (or on a hybrid laptop) the default adapter can be a different GPU, which breaks
    // fast screen capture and adds a copy across GPUs for every frame.
    IDXGIAdapter1* chosen = nullptr;
    {
        POINT cp{};
        GetCursorPos(&cp);
        HMONITOR hm = MonitorFromPoint(cp, MONITOR_DEFAULTTOPRIMARY);
        IDXGIFactory1* fac = nullptr;
        if (SUCCEEDED(CreateDXGIFactory1(IID_PPV_ARGS(&fac))) && fac) {
            for (UINT a = 0; !chosen; ++a) {
                IDXGIAdapter1* ad = nullptr;
                if (FAILED(fac->EnumAdapters1(a, &ad)) || !ad) break;
                bool match = false;
                for (UINT o = 0; !match; ++o) {
                    IDXGIOutput* out = nullptr;
                    if (FAILED(ad->EnumOutputs(o, &out)) || !out) break;
                    DXGI_OUTPUT_DESC od{};
                    if (SUCCEEDED(out->GetDesc(&od)) && od.Monitor == hm) match = true;
                    out->Release();
                }
                if (match) chosen = ad; else ad->Release();
            }
            fac->Release();
        }
    }

    D3D_FEATURE_LEVEL levels[] = { D3D_FEATURE_LEVEL_11_0 };
    HRESULT hr = E_FAIL;
    if (chosen) {
        hr = D3D11CreateDevice(chosen, D3D_DRIVER_TYPE_UNKNOWN, nullptr, D3D11_CREATE_DEVICE_BGRA_SUPPORT,
                               levels, 1, D3D11_SDK_VERSION, &m_d3dDevice, nullptr, nullptr);
        DXGI_ADAPTER_DESC1 ad1{};
        if (SUCCEEDED(chosen->GetDesc1(&ad1))) {
            LOG_INF(L"GPU for the cube: %s (%u MB dedicated)", ad1.Description, (unsigned)(ad1.DedicatedVideoMemory >> 20));
        }
        chosen->Release();
    }
    if (FAILED(hr) || !m_d3dDevice) {
        hr = D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr,
                               D3D11_CREATE_DEVICE_BGRA_SUPPORT,
                               levels, 1, D3D11_SDK_VERSION,
                               &m_d3dDevice, nullptr, nullptr);
    }
    if (FAILED(hr) || !m_d3dDevice) {
        LOG_ERR(L"D3D11CreateDevice failed 0x%08X", (unsigned)hr);
        return false;
    }

    IDXGIDevice* dxgiDevice = nullptr;
    m_d3dDevice->QueryInterface(IID_PPV_ARGS(&dxgiDevice));
    if (!dxgiDevice) return false;

    D2D1_FACTORY_OPTIONS options{};
    D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, __uuidof(ID2D1Factory1), &options, (void**)&m_d2dFactory);
    if (m_d2dFactory) m_d2dFactory->CreateDevice(dxgiDevice, &m_d2dDevice);
    dxgiDevice->SetGPUThreadPriority(7);   // our GPU work wins against other apps on a busy iGPU
    {
        IDXGIDevice1* d1 = nullptr;
        if (SUCCEEDED(dxgiDevice->QueryInterface(IID_PPV_ARGS(&d1))) && d1) { d1->SetMaximumFrameLatency(3); d1->Release(); }
    }
    dxgiDevice->Release();
    if (!m_d2dDevice) {
        LOG_ERR(L"Direct2D device creation failed");
        return false;
    }

    DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory), (IUnknown**)&m_dwriteFactory);
    EnsureTextFormat();

    ICompositorInteropX* ci = nullptr;
    IUnknown* compUnk = (IUnknown*)winrt::get_abi(m_compositor);
    if (SUCCEEDED(compUnk->QueryInterface(IID_ICompositorInteropX, (void**)&ci)) && ci) {
        hr = ci->CreateGraphicsDevice(m_d2dDevice, winrt::put_abi(m_graphicsDevice));
        ci->Release();
        if (FAILED(hr)) {
            LOG_ERR(L"CreateGraphicsDevice failed 0x%08X", (unsigned)hr);
            return false;
        }
    } else {
        LOG_ERR(L"ICompositorInterop not available");
        return false;
    }
    return m_graphicsDevice != nullptr;
}

void CubeRenderer::FindOutput() {
    if (m_output) { m_output->Release(); m_output = nullptr; }
    if (m_dupOutput) { m_dupOutput->Release(); m_dupOutput = nullptr; }
    if (!m_d3dDevice) return;

    IDXGIDevice* dd = nullptr;
    if (SUCCEEDED(m_d3dDevice->QueryInterface(IID_PPV_ARGS(&dd))) && dd) {
        IDXGIAdapter* ad = nullptr;
        if (SUCCEEDED(dd->GetAdapter(&ad)) && ad) {
            for (UINT o = 0; ; ++o) {
                IDXGIOutput* out = nullptr;
                if (FAILED(ad->EnumOutputs(o, &out)) || !out) break;
                DXGI_OUTPUT_DESC od{};
                if (SUCCEEDED(out->GetDesc(&od)) && od.Monitor == m_hMonitor) {
                    m_dupOutput = out;
                    m_output = out;
                    m_output->AddRef();
                    break;
                }
                out->Release();
            }
            ad->Release();
        }
        dd->Release();
    }

    // Hybrid GPU: the monitor hangs off another adapter. Still pace on its vblank.
    if (!m_output) {
        IDXGIFactory1* fac = nullptr;
        if (SUCCEEDED(CreateDXGIFactory1(IID_PPV_ARGS(&fac))) && fac) {
            for (UINT a = 0; !m_output; ++a) {
                IDXGIAdapter1* ad1 = nullptr;
                if (FAILED(fac->EnumAdapters1(a, &ad1)) || !ad1) break;
                for (UINT o = 0; ; ++o) {
                    IDXGIOutput* out = nullptr;
                    if (FAILED(ad1->EnumOutputs(o, &out)) || !out) break;
                    DXGI_OUTPUT_DESC od{};
                    if (SUCCEEDED(out->GetDesc(&od)) && od.Monitor == m_hMonitor) { m_output = out; break; }
                    out->Release();
                }
                ad1->Release();
            }
            fac->Release();
        }
    }
    LOG_DBG(L"VBlank source: %s, duplication output: %s",
            m_output ? L"DXGI output" : L"DwmFlush", m_dupOutput ? L"yes" : L"no (GDI fallback)");
}

bool CubeRenderer::WarmInit() {
    // Registered with the mod's own module handle. ANY failure (including ERROR_CLASS_ALREADY_EXISTS) is an error:
    // an existing class could still point at a window procedure inside an earlier, unloaded copy of the mod.
    const HMODULE hMod = GetThisModuleHandle();
    if (!hMod) {
        LOG_ERR(L"Cannot get the mod module handle: %lu", GetLastError());
        return false;
    }
    if (!g_overlayClassRegistered) {
        WNDCLASSEXW wc{ sizeof(wc) };
        wc.lpfnWndProc = WndProc;
        wc.hInstance = hMod;
        wc.lpszClassName = kOverlayClassName;
        wc.hCursor = LoadCursorW(nullptr, IDC_ARROW);
        if (!RegisterClassExW(&wc)) {
            LOG_ERR(L"RegisterClassExW failed: %lu", GetLastError());
            return false;
        }
        g_overlayClassRegistered = true;
    }

    m_hwnd = CreateWindowExW(
        WS_EX_TOPMOST | WS_EX_TOOLWINDOW | WS_EX_NOACTIVATE | WS_EX_NOREDIRECTIONBITMAP | WS_EX_TRANSPARENT,
        kOverlayClassName, L"Seamless Compiz Cube", WS_POPUP,
        0, 0, 16, 16, nullptr, nullptr, hMod, this);
    if (!m_hwnd) {
        LOG_ERR(L"CreateWindowExW failed: %lu", GetLastError());
        return false;
    }
    ApplyCaptureAffinity(false);

    if (!EnsureDispatcherQueue()) {
        LOG_ERR(L"No DispatcherQueue on render thread");
        return false;
    }

    m_compositor = Compositor();

    IUnknown* compUnk = (IUnknown*)winrt::get_abi(m_compositor);
    ICompositorDesktopInteropX* interop = nullptr;
    HRESULT hr = compUnk->QueryInterface(IID_ICompositorDesktopInteropX, (void**)&interop);
    if (FAILED(hr) || !interop) {
        LOG_ERR(L"ICompositorDesktopInterop unavailable 0x%08X", (unsigned)hr);
        return false;
    }
    hr = interop->CreateDesktopWindowTarget(m_hwnd, TRUE, winrt::put_abi(m_target));
    interop->Release();
    if (FAILED(hr) || !m_target) {
        LOG_ERR(L"CreateDesktopWindowTarget failed 0x%08X", (unsigned)hr);
        return false;
    }

    m_emptyRoot = m_compositor.CreateContainerVisual();
    m_target.Root(m_emptyRoot);

    if (!InitializeGraphicsDevice()) return false;

    QueryPerformanceFrequency(&m_qpcFreq);
    return true;
}

CompositionDrawingSurface CubeRenderer::MakeSurface(int w, int h) {
    return m_graphicsDevice.CreateDrawingSurface(
        { (float)w, (float)h },
        DirectXPixelFormat::B8G8R8A8UIntNormalized,
        DirectXAlphaMode::Premultiplied);
}

ID2D1Bitmap1* CubeRenderer::GetDesktopBitmap(ID2D1DeviceContext* ctx, int dIdx) {
    if (dIdx < 0 || dIdx >= m_desktopList.TotalCount()) return nullptr;

    uint64_t ver = 0;
    auto snap = DesktopCaptureManager::Get(m_desktopList.items[dIdx].id, &ver);
    if (!snap) return nullptr;

    auto it = m_bitmapCache.find(dIdx);
    if (it != m_bitmapCache.end()) {
        if (it->second.ver == ver) return it->second.bmp;
        if (it->second.bmp) it->second.bmp->Release();
        m_bitmapCache.erase(it);
    }

    ID2D1Bitmap1* bmp = nullptr;
    if (!CreateBitmapFromSnapshot(ctx, *snap, &bmp) || !bmp) return nullptr;
    CachedBitmap cb;
    cb.bmp = bmp;
    cb.ver = ver;
    m_bitmapCache[dIdx] = cb;
    return bmp;
}

void CubeRenderer::BuildBackground() {
    int cur = m_desktopList.currentIndex;
    float sw = m_screenWidth, sh = m_screenHeight;
    bool blur = m_cfg.blur;
    float sigma = m_cfg.blurStrength;

    if (!DesktopCaptureManager::Get(m_desktopList.items[cur].id)) return;

    const float bgScale = 0.25f;
    m_bgW = (int)(sw * bgScale); m_bgH = (int)(sh * bgScale);
    m_bgSurface = MakeSurface(m_bgW, m_bgH);
    bool ok = DrawToSurface(m_bgSurface, [&](ID2D1DeviceContext* ctx, POINT off) {
        ctx->Clear(D2D1::ColorF(0.04f, 0.05f, 0.08f, 1.0f));

        ID2D1Bitmap1* bmp = GetDesktopBitmap(ctx, cur);
        if (!bmp) return;
        // Snapshots are stored at most 1920 px wide: kx / ky map bitmap pixels back to screen pixels.
        const D2D1_SIZE_U bps = bmp->GetPixelSize();
        const float bw = (float)std::max<UINT32>(1, bps.width), bh = (float)std::max<UINT32>(1, bps.height);
        const float kx = sw / bw, ky = sh / bh;
        ctx->SetTransform(D2D1::Matrix3x2F::Scale(bgScale * kx, bgScale * ky) *
                          D2D1::Matrix3x2F::Translation((float)off.x, (float)off.y));

        bool drawn = false;
        if (blur) {
            ID2D1Effect* fx = nullptr;
            if (SUCCEEDED(ctx->CreateEffect(CLSID_D2D1GaussianBlur, &fx)) && fx) {
                fx->SetInput(0, bmp);
                fx->SetValue(D2D1_GAUSSIANBLUR_PROP_STANDARD_DEVIATION, sigma / kx);
                fx->SetValue(D2D1_GAUSSIANBLUR_PROP_BORDER_MODE, (UINT32)D2D1_BORDER_MODE_SOFT);

                ID2D1Image* out = nullptr;
                fx->GetOutput(&out);
                if (out) {
                    D2D1_POINT_2F pt = D2D1::Point2F(0.0f, 0.0f);
                    D2D1_RECT_F src = D2D1::RectF(0.0f, 0.0f, bw, bh);
                    ctx->DrawImage(out, &pt, &src, D2D1_INTERPOLATION_MODE_LINEAR, D2D1_COMPOSITE_MODE_SOURCE_OVER);
                    out->Release();
                    drawn = true;
                }
                fx->Release();
            }
        }
        if (!drawn) ctx->DrawBitmap(bmp, D2D1::RectF(0.0f, 0.0f, bw, bh));

        ID2D1SolidColorBrush* dimBrush = nullptr;
        ctx->CreateSolidColorBrush(D2D1::ColorF(8.0f / 255.0f, 10.0f / 255.0f, 16.0f / 255.0f, (float)m_cfg.dim / 100.0f), &dimBrush);
        if (dimBrush) {
            ctx->SetTransform(D2D1::Matrix3x2F::Translation((float)off.x, (float)off.y));
            ctx->FillRectangle(D2D1::RectF(0.0f, 0.0f, sw * bgScale, sh * bgScale), dimBrush);
            dimBrush->Release();
        }
    });

    if (ok) {
        m_backgroundVisual = m_compositor.CreateSpriteVisual();
        m_backgroundVisual.Size({ sw, sh });
        m_backgroundVisual.CenterPoint({ sw * 0.5f, sh * 0.5f, 0.0f });
        m_backgroundVisual.Brush(m_compositor.CreateSurfaceBrush(m_bgSurface));
        m_rootVisual.Children().InsertAtTop(m_backgroundVisual);
    }
}

void CubeRenderer::RenderShadow() {
    m_shadowW = m_faceWidth * 1.35f;
    m_shadowH = m_faceWidth * 0.28f;
    m_shadowSurface = MakeSurface((int)m_shadowW, (int)m_shadowH);
    float w = m_shadowW, h = m_shadowH;

    DrawToSurface(m_shadowSurface, [&](ID2D1DeviceContext* ctx, POINT off) {
        ctx->Clear(D2D1::ColorF(0.0f, 0.0f, 0.0f, 0.0f));
        ctx->SetTransform(D2D1::Matrix3x2F::Translation((float)off.x, (float)off.y));

        D2D1_GRADIENT_STOP stops[2] = {
            { 0.0f, D2D1::ColorF(0.0f, 0.0f, 0.0f, 0.75f) },
            { 1.0f, D2D1::ColorF(0.0f, 0.0f, 0.0f, 0.0f) }
        };
        ID2D1GradientStopCollection* gs = nullptr;
        ctx->CreateGradientStopCollection(stops, 2, &gs);
        if (gs) {
            ID2D1RadialGradientBrush* rb = nullptr;
            ctx->CreateRadialGradientBrush(
                D2D1::RadialGradientBrushProperties(D2D1::Point2F(w * 0.5f, h * 0.5f), D2D1::Point2F(0.0f, 0.0f), w * 0.5f, h * 0.5f),
                gs, &rb);
            if (rb) {
                ctx->FillRectangle(D2D1::RectF(0.0f, 0.0f, w, h), rb);
                rb->Release();
            }
            gs->Release();
        }
    });

    m_shadowVisual = m_compositor.CreateSpriteVisual();
    m_shadowVisual.Size({ m_shadowW, m_shadowH });
    m_shadowVisual.CenterPoint({ m_shadowW * 0.5f, m_shadowH * 0.5f, 0.0f });
    m_shadowVisual.Brush(m_compositor.CreateSurfaceBrush(m_shadowSurface));
    m_shadowVisual.Opacity(0.0f);
    m_rootVisual.Children().InsertAtTop(m_shadowVisual);
}

ID2D1Bitmap1* CubeRenderer::FaceBitmap(ID2D1DeviceContext* ctx, int dIdx) {
    if (m_liveBmp && m_liveHasFrame && dIdx == m_liveDesktop) return m_liveBmp;
    return GetDesktopBitmap(ctx, dIdx);
}

// Builds the shared text format from the Font settings. A missing family falls back to Segoe UI.
// Runs on the render thread (graphics init and every scene build), so the format is never swapped mid-draw.
void CubeRenderer::EnsureTextFormat() {
    if (!m_dwriteFactory) return;
    const int weight = std::clamp(m_cfg.fontWeight, 100, 950);
    const float size = std::clamp(m_cfg.fontSize, 8.0f, 24.0f);
    wchar_t sig[256];
    swprintf_s(sig, L"%ls|%d|%.1f", m_cfg.fontFamily.c_str(), weight, size);
    if (m_textFormatBadge && m_fontSig == sig) return;

    std::wstring family = m_cfg.fontFamily.empty() ? L"FiraCode Nerd Font" : m_cfg.fontFamily;
    {
        IDWriteFontCollection* coll = nullptr;
        BOOL found = FALSE;
        UINT32 idx = 0;
        if (SUCCEEDED(m_dwriteFactory->GetSystemFontCollection(&coll, FALSE)) && coll) {
            coll->FindFamilyName(family.c_str(), &idx, &found);
            coll->Release();
        }
        if (!found) {
            LOG_INF(L"Font '%ls' is not installed, using Segoe UI", family.c_str());
            family = L"Segoe UI";
        }
    }

    IDWriteTextFormat* fmt = nullptr;
    m_dwriteFactory->CreateTextFormat(family.c_str(), nullptr,
        (DWRITE_FONT_WEIGHT)weight, DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL,
        size, L"en-us", &fmt);
    if (!fmt) return;
    fmt->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_CENTER);
    fmt->SetParagraphAlignment(DWRITE_PARAGRAPH_ALIGNMENT_CENTER);
    fmt->SetWordWrapping(DWRITE_WORD_WRAPPING_NO_WRAP);
    IDWriteInlineObject* ellipsis = nullptr;
    if (SUCCEEDED(m_dwriteFactory->CreateEllipsisTrimmingSign(fmt, &ellipsis)) && ellipsis) {
        DWRITE_TRIMMING trim{ DWRITE_TRIMMING_GRANULARITY_CHARACTER, 0, 0 };
        fmt->SetTrimming(&trim, ellipsis);
        ellipsis->Release();
    }
    if (m_textFormatBadge) m_textFormatBadge->Release();
    m_textFormatBadge = fmt;
    m_fontSig = sig;
}

void CubeRenderer::RenderFace(int i, int dIdx) {
    auto& f = m_faces[i];
    f.renderedDesktop = dIdx;
    if (!f.surface) f.surface = MakeSurface(m_texW, m_texH);
    if (!f.layerSurface) f.layerSurface = MakeSurface((int)(kBadgeW * 2.0f), (int)(kBadgeH * 2.0f));

    int total = m_desktopList.TotalCount();
    bool valid = dIdx >= 0 && dIdx < total;
    uint64_t ver = 0;
    DesktopCaptureManager::SnapPtr snap;
    if (valid) snap = DesktopCaptureManager::Get(m_desktopList.items[dIdx].id, &ver);
    f.renderedVersion = ver;
    const bool haveImage = (snap != nullptr) || (m_liveBmp && m_liveHasFrame && dIdx == m_liveDesktop);

    FaceColor accent = kFaceAccents[i % kMaxFaces];
    const float faceW = m_faceWidth, faceH = m_faceHeight;
    const bool showLabels = m_cfg.labels;

    // ---- base plane: the desktop image (live for the desktop you are on) ----
    bool ok = DrawToSurface(f.surface, [&](ID2D1DeviceContext* ctx, POINT off) {
        ctx->SetTextAntialiasMode(D2D1_TEXT_ANTIALIAS_MODE_GRAYSCALE);
        ctx->Clear(D2D1::ColorF(0.1176f, 0.1176f, 0.1804f, 1.0f));
        float k = (float)m_texW / faceW;
        ctx->SetTransform(D2D1::Matrix3x2F::Scale(k, k) *
                          D2D1::Matrix3x2F::Translation((float)off.x, (float)off.y));

        ID2D1SolidColorBrush* textBrush = nullptr;
        ctx->CreateSolidColorBrush(D2D1::ColorF(0.8039f, 0.8392f, 0.9569f, 1.0f), &textBrush);
        ctx->PushAxisAlignedClip(D2D1::RectF(0.0f, 0.0f, faceW, faceH), D2D1_ANTIALIAS_MODE_ALIASED);

        ID2D1Bitmap1* bmp = haveImage ? FaceBitmap(ctx, dIdx) : nullptr;
        if (bmp) {
            D2D1_SIZE_U ps = bmp->GetPixelSize();
            D2D1_RECT_F srcR = (bmp == m_liveBmp)
                ? D2D1::RectF(0.0f, 0.0f, (float)ps.width, (float)ps.height)
                : D2D1::RectF(m_wl * (float)ps.width, m_wt * (float)ps.height,
                              m_wr * (float)ps.width, m_wb * (float)ps.height);
            ctx->DrawBitmap(bmp, D2D1::RectF(0.0f, 0.0f, faceW, faceH), 1.0f,
                            D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, &srcR);
        } else if (textBrush && m_textFormatBadge) {
            const wchar_t* msg = !valid ? L"No desktop" : L"Loading desktop...";
            ctx->DrawText(msg, (UINT32)wcslen(msg), m_textFormatBadge,
                          D2D1::RectF(0.0f, faceH * 0.40f, faceW, faceH * 0.60f),
                          textBrush, D2D1_DRAW_TEXT_OPTIONS_NONE);
        }

        ctx->PopAxisAlignedClip();
        if (textBrush) textBrush->Release();
    });
    if (ok && !f.brush) {
        f.brush = m_compositor.CreateSurfaceBrush(f.surface);
        f.background.Brush(f.brush);
        f.usingLive = false;
    }

    // ---- badge: a small separate visual ("Desktop N") ----
    DrawToSurface(f.layerSurface, [&](ID2D1DeviceContext* ctx, POINT off) {
        ctx->SetTextAntialiasMode(D2D1_TEXT_ANTIALIAS_MODE_GRAYSCALE);
        ctx->Clear(D2D1::ColorF(0.0f, 0.0f, 0.0f, 0.0f));
        ctx->SetTransform(D2D1::Matrix3x2F::Scale(2.0f, 2.0f) *
                          D2D1::Matrix3x2F::Translation((float)off.x, (float)off.y));
        if (!(showLabels && valid && m_textFormatBadge)) return;

        ID2D1SolidColorBrush* textBrush = nullptr;
        ID2D1SolidColorBrush* pillBrush = nullptr;
        ID2D1SolidColorBrush* accentBrush = nullptr;
        ctx->CreateSolidColorBrush(D2D1::ColorF(0.8039f, 0.8392f, 0.9569f, 1.0f), &textBrush);
        ctx->CreateSolidColorBrush(D2D1::ColorF(0.0941f, 0.0941f, 0.1451f, 0.94f), &pillBrush);
        ctx->CreateSolidColorBrush(D2D1::ColorF(accent.r / 255.0f, accent.g / 255.0f, accent.b / 255.0f, 1.0f), &accentBrush);
        if (textBrush && pillBrush && accentBrush) {
            // Mocha mantle pill, radius 16 (a full pill at this height), blue to mauve border.
            ctx->FillRoundedRectangle(D2D1::RoundedRect(D2D1::RectF(0.0f, 0.0f, kBadgeW, kBadgeH), 16.0f, 16.0f), pillBrush);
            {
                auto toF = [](uint32_t c) {
                    return D2D1::ColorF(((c >> 16) & 0xFF) / 255.0f, ((c >> 8) & 0xFF) / 255.0f, (c & 0xFF) / 255.0f, 1.0f);
                };
                D2D1_GRADIENT_STOP gs[2] = { { 0.0f, toF(m_cfg.actStart) }, { 1.0f, toF(m_cfg.actEnd) } };
                ID2D1GradientStopCollection* coll = nullptr;
                ID2D1LinearGradientBrush* gb = nullptr;
                if (SUCCEEDED(ctx->CreateGradientStopCollection(gs, 2, &coll))) {
                    ctx->CreateLinearGradientBrush(
                        D2D1::LinearGradientBrushProperties(D2D1::Point2F(0.0f, 0.0f), D2D1::Point2F(kBadgeW, kBadgeH)),
                        coll, &gb);
                }
                if (gb) {
                    ctx->DrawRoundedRectangle(D2D1::RoundedRect(D2D1::RectF(1.0f, 1.0f, kBadgeW - 1.0f, kBadgeH - 1.0f), 15.0f, 15.0f), gb, 2.0f);
                    gb->Release();
                }
                if (coll) coll->Release();
            }
            ctx->FillEllipse(D2D1::Ellipse(D2D1::Point2F(20.0f, kBadgeH * 0.5f), 4.5f, 4.5f), accentBrush);
            wchar_t label[96];
            if (dIdx == m_liveDesktop) swprintf_s(label, L"Desktop %d  -  %s", dIdx + 1, m_liveStatus);
            else swprintf_s(label, L"Desktop %d", dIdx + 1);
            ctx->DrawText(label, (UINT32)wcslen(label), m_textFormatBadge,
                          D2D1::RectF(30.0f, 0.0f, kBadgeW - 12.0f, kBadgeH),
                          textBrush, D2D1_DRAW_TEXT_OPTIONS_NONE);
        }
        if (textBrush) textBrush->Release();
        if (pillBrush) pillBrush->Release();
        if (accentBrush) accentBrush->Release();
    });

    if (!f.layerBrush && f.layer) {
        f.layerBrush = m_compositor.CreateSurfaceBrush(f.layerSurface);
        f.layer.Brush(f.layerBrush);
    }
}

// ---------------------------------------------------------------------------
// Live desktop feed
// ---------------------------------------------------------------------------
bool CubeRenderer::CreateDuplication(int* outW, int* outH) {
    if (!m_dupOutput || !m_d3dDevice) return false;
    IDXGIOutput1* o1 = nullptr;
    if (FAILED(m_dupOutput->QueryInterface(IID_PPV_ARGS(&o1))) || !o1) return false;
    IDXGIOutputDuplication* dup = nullptr;
    HRESULT hr = o1->DuplicateOutput(m_d3dDevice, &dup);
    o1->Release();
    if (FAILED(hr) || !dup) {
        LOG_INF(L"DuplicateOutput failed 0x%08X", (unsigned)hr);
        return false;
    }
    DXGI_OUTDUPL_DESC dd{};
    dup->GetDesc(&dd);
    if (dd.ModeDesc.Format != DXGI_FORMAT_B8G8R8A8_UNORM || dd.ModeDesc.Width == 0 || dd.ModeDesc.Height == 0) {
        LOG_INF(L"Duplication format %d not supported (HDR?)", (int)dd.ModeDesc.Format);
        dup->Release();
        return false;
    }
    if (outW) *outW = (int)dd.ModeDesc.Width;
    if (outH) *outH = (int)dd.ModeDesc.Height;
    m_dup = dup;
    return true;
}

bool CubeRenderer::CreateCompSwapChain(int w, int h, IDXGISwapChain1** outSc, ICompositionSurface* outSurf) {
    IDXGIDevice* dd = nullptr;
    IDXGIAdapter* ad = nullptr;
    IDXGIFactory2* fac = nullptr;
    IDXGISwapChain1* sc = nullptr;
    bool ok = false;
    if (SUCCEEDED(m_d3dDevice->QueryInterface(IID_PPV_ARGS(&dd))) && dd &&
        SUCCEEDED(dd->GetAdapter(&ad)) && ad &&
        SUCCEEDED(ad->GetParent(IID_PPV_ARGS(&fac))) && fac) {
        DXGI_SWAP_CHAIN_DESC1 sd{};
        sd.Width = (UINT)w;
        sd.Height = (UINT)h;
        sd.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
        sd.SampleDesc.Count = 1;
        sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
        sd.BufferCount = 2;
        sd.Scaling = DXGI_SCALING_STRETCH;
        sd.SwapEffect = DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL;
        sd.AlphaMode = DXGI_ALPHA_MODE_IGNORE;
        if (SUCCEEDED(fac->CreateSwapChainForComposition(m_d3dDevice, &sd, nullptr, &sc)) && sc) {
            ICompositorInteropX* ci = nullptr;
            IUnknown* compUnk = (IUnknown*)winrt::get_abi(m_compositor);
            if (SUCCEEDED(compUnk->QueryInterface(IID_ICompositorInteropX, (void**)&ci)) && ci) {
                ICompositionSurface surf{ nullptr };
                HRESULT hr = ci->CreateCompositionSurfaceForSwapChain(sc, winrt::put_abi(surf));
                ci->Release();
                if (SUCCEEDED(hr) && surf) { *outSurf = surf; ok = true; }
            }
        }
    }
    if (fac) fac->Release();
    if (ad) ad->Release();
    if (dd) dd->Release();
    if (ok) *outSc = sc; else if (sc) sc->Release();
    return ok;
}

static bool MakeLiveTexture(ID3D11Device* dev, int w, int h, ID3D11Texture2D** out) {
    D3D11_TEXTURE2D_DESC td{};
    td.Width = (UINT)w; td.Height = (UINT)h;
    td.MipLevels = 1; td.ArraySize = 1;
    td.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
    td.SampleDesc.Count = 1;
    td.Usage = D3D11_USAGE_DEFAULT;
    td.BindFlags = D3D11_BIND_SHADER_RESOURCE;
    return SUCCEEDED(dev->CreateTexture2D(&td, nullptr, out)) && *out;
}

bool CubeRenderer::StartLive(const DesktopCaptureManager::SnapshotData* initial) {
    StopLive();
    m_liveFrames = 0;
    m_liveStatus = L"STATIC";
    if (!m_canExclude) {
        m_liveStatus = m_cfg.recordingMode ? L"STATIC (recording mode)" : L"STATIC (cannot hide overlay)";
        return false;
    }
    if (!m_d3dDevice || !m_d2dDevice) { m_liveStatus = L"STATIC (no GPU device)"; return false; }

    int w = (int)m_screenWidth, h = (int)m_screenHeight;
    if (m_cfg.liveMethod != 2 && CreateDuplication(&w, &h)) m_liveSource = LiveSource::Dup;
    else m_liveSource = LiveSource::Gdi;
    if (w < 128 || h < 128) { StopLive(); return false; }
    m_liveW = w; m_liveH = h;

    // Everything below the taskbar line is cut away right here, so the taskbar can never show up.
    m_workPx.left = std::clamp((int)std::lround(m_wl * (float)w), 0, w - 64);
    m_workPx.top = std::clamp((int)std::lround(m_wt * (float)h), 0, h - 64);
    m_workPx.right = std::clamp((int)std::lround(m_wr * (float)w), (int)m_workPx.left + 64, w);
    m_workPx.bottom = std::clamp((int)std::lround(m_wb * (float)h), (int)m_workPx.top + 64, h);
    m_workW = m_workPx.right - m_workPx.left;
    m_workH = m_workPx.bottom - m_workPx.top;

    m_d3dDevice->GetImmediateContext(&m_d3dCtx);
    if (!m_d3dCtx || !MakeLiveTexture(m_d3dDevice, m_workW, m_workH, &m_liveTex)) {
        m_liveStatus = L"STATIC (texture failed)";
        StopLive();
        return false;
    }

    bool haveInitial = false;
    if (initial && initial->width == w && initial->height == h && !initial->pixels.empty()) {
        const uint8_t* base = (const uint8_t*)initial->pixels.data() +
                              ((size_t)m_workPx.top * (size_t)w + (size_t)m_workPx.left) * 4;
        m_d3dCtx->UpdateSubresource(m_liveTex, 0, nullptr, base, (UINT)w * 4, 0);
        haveInitial = true;
    }

    IDXGISurface* surf = nullptr;
    ID2D1DeviceContext* dc = nullptr;
    bool ok = false;
    if (SUCCEEDED(m_liveTex->QueryInterface(IID_PPV_ARGS(&surf))) && surf &&
        SUCCEEDED(m_d2dDevice->CreateDeviceContext(D2D1_DEVICE_CONTEXT_OPTIONS_NONE, &dc)) && dc) {
        D2D1_BITMAP_PROPERTIES1 bp = D2D1::BitmapProperties1(
            D2D1_BITMAP_OPTIONS_NONE,
            D2D1::PixelFormat(DXGI_FORMAT_B8G8R8A8_UNORM, D2D1_ALPHA_MODE_IGNORE), 96.0f, 96.0f);
        ok = SUCCEEDED(dc->CreateBitmapFromDxgiSurface(surf, &bp, &m_liveBmp)) && m_liveBmp;
    }
    if (dc) dc->Release();
    if (surf) surf->Release();
    if (!ok) {
        m_liveStatus = L"STATIC (bitmap failed)";
        StopLive();
        return false;
    }

    if (!CreateCompSwapChain(m_workW, m_workH, &m_sc, &m_liveSurface)) {
        m_liveStatus = L"STATIC (swapchain failed)";
        LOG_ERR(L"Live swap chain creation failed");
        StopLive();
        return false;
    }
    if (haveInitial) {
        ID3D11Texture2D* bb = nullptr;
        if (SUCCEEDED(m_sc->GetBuffer(0, IID_PPV_ARGS(&bb))) && bb) {
            m_d3dCtx->CopyResource(bb, m_liveTex);
            bb->Release();
            m_sc->Present(0, 0);
        }
    }

    if (m_liveSource == LiveSource::Gdi) {
        HDC scr = GetDC(nullptr);
        m_gdiMem = scr ? CreateCompatibleDC(scr) : nullptr;
        BITMAPINFO bmi{};
        bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
        bmi.bmiHeader.biWidth = w;
        bmi.bmiHeader.biHeight = -h;
        bmi.bmiHeader.biPlanes = 1;
        bmi.bmiHeader.biBitCount = 32;
        bmi.bmiHeader.biCompression = BI_RGB;
        if (m_gdiMem) m_gdiDib = CreateDIBSection(scr, &bmi, DIB_RGB_COLORS, &m_gdiBits, nullptr, 0);
        if (scr) ReleaseDC(nullptr, scr);
        if (!m_gdiMem || !m_gdiDib || !m_gdiBits || !MakeLiveTexture(m_d3dDevice, w, h, &m_gdiTex)) {
            m_liveStatus = L"STATIC (GDI failed)";
            StopLive();
            return false;
        }
        m_gdiOld = SelectObject(m_gdiMem, m_gdiDib);
    }

    m_liveHasFrame = haveInitial;
    m_texFresh = haveInitial;
    m_liveStatus = (m_liveSource == LiveSource::Dup) ? L"LIVE" : L"LIVE (GDI)";
    LOG_INF(L"Live capture: %s %dx%d, work area %dx%d", m_liveSource == LiveSource::Dup ? L"Desktop Duplication" : L"GDI fallback",
            w, h, m_workW, m_workH);
    return true;
}

void CubeRenderer::StopLive() {
    m_liveHasFrame = false;
    m_texFresh = false;
    m_presentPending = false;
    m_liveSource = LiveSource::None;
    m_altSurf.clear();
    if (m_liveBmp) { m_liveBmp->Release(); m_liveBmp = nullptr; }
    if (m_dup) { m_dup->Release(); m_dup = nullptr; }
    if (m_sc) { m_sc->Release(); m_sc = nullptr; }
    m_liveSurface = nullptr;
    if (m_liveTex) { m_liveTex->Release(); m_liveTex = nullptr; }
    if (m_gdiTex) { m_gdiTex->Release(); m_gdiTex = nullptr; }
    if (m_d3dCtx) { m_d3dCtx->Release(); m_d3dCtx = nullptr; }
    if (m_gdiMem) {
        if (m_gdiOld) SelectObject(m_gdiMem, m_gdiOld);
        DeleteDC(m_gdiMem);
    }
    if (m_gdiDib) DeleteObject(m_gdiDib);
    m_gdiMem = nullptr; m_gdiDib = nullptr; m_gdiOld = nullptr; m_gdiBits = nullptr;
}

// One new screen frame: crop it once (taskbar gone) and hand it to the compositor.
// Extra copies only happen when something needs them (background at 30 Hz, switcher windows).
void CubeRenderer::DistributeFrame(ID3D11Texture2D* src, bool wantTex) {
    const D3D11_BOX box{ (UINT)m_workPx.left, (UINT)m_workPx.top, 0, (UINT)m_workPx.right, (UINT)m_workPx.bottom, 1 };
    ID3D11Texture2D* bb = nullptr;
    if (m_sc && SUCCEEDED(m_sc->GetBuffer(0, IID_PPV_ARGS(&bb))) && bb) {
        m_d3dCtx->CopySubresourceRegion(bb, 0, 0, 0, 0, src, 0, &box);
        bb->Release();
        // Never block the render thread: if the GPU is behind, keep the (already copied) frame and retry next frame.
        m_presentPending = (m_sc->Present(0, DXGI_PRESENT_DO_NOT_WAIT) == DXGI_ERROR_WAS_STILL_DRAWING);
    }
    if (wantTex || m_selMode) {
        m_d3dCtx->CopySubresourceRegion(m_liveTex, 0, 0, 0, 0, src, 0, &box);
        m_texFresh = true;
    }
    if (m_selMode) m_thumbFresh = true;
}

// Returns true when a NEW frame was received.
bool CubeRenderer::PollLive(bool wantTex) {
    if (!m_liveTex || !m_d3dCtx) return false;

    if (m_liveSource == LiveSource::Gdi) {
        ULONGLONG now = GetTickCount64();
        if (now < m_gdiNext) return false;
        m_gdiNext = now + 33;
        HDC scr = GetDC(nullptr);
        if (!scr) return false;
        BitBlt(m_gdiMem, 0, 0, m_liveW, m_liveH, scr, m_monitorRect.left, m_monitorRect.top, SRCCOPY | CAPTUREBLT);
        ReleaseDC(nullptr, scr);
        m_d3dCtx->UpdateSubresource(m_gdiTex, 0, nullptr, m_gdiBits, (UINT)m_liveW * 4, 0);
        ++m_liveFrames;
        DistributeFrame(m_gdiTex, wantTex);
        return true;
    }
    if (m_liveSource != LiveSource::Dup) return false;

    if (!m_dup) {   // lost (mode change, UAC, lock screen): retry now and then
        ULONGLONG now = GetTickCount64();
        if (now < m_dupRetryAt) return false;
        m_dupRetryAt = now + 400;
        int w = 0, h = 0;
        if (!CreateDuplication(&w, &h)) return false;
        if (w != m_liveW || h != m_liveH) { m_dup->Release(); m_dup = nullptr; return false; }
    }

    DXGI_OUTDUPL_FRAME_INFO fi{};
    IDXGIResource* res = nullptr;
    HRESULT hr = m_dup->AcquireNextFrame(0, &fi, &res);
    if (hr == DXGI_ERROR_WAIT_TIMEOUT) return false;
    if (FAILED(hr)) {
        m_dup->Release(); m_dup = nullptr;
        m_dupRetryAt = GetTickCount64() + 400;
        return false;
    }
    bool got = false;
    if (fi.LastPresentTime.QuadPart != 0 && res) {
        ID3D11Texture2D* t = nullptr;
        if (SUCCEEDED(res->QueryInterface(IID_PPV_ARGS(&t))) && t) {
            DistributeFrame(t, wantTex);
            t->Release();
            got = true;
        }
    }
    if (res) res->Release();
    m_dup->ReleaseFrame();
    if (got) ++m_liveFrames;
    return got;
}

// Blurred live background, drawn small and throttled (the blur hides everything a high rate would show).
void CubeRenderer::DrawLive() {
    if (!m_liveBmp || !m_bgSurface || m_bgW <= 0) return;
    const float sigma = m_cfg.blurStrength;
    const bool blur = m_cfg.blur;
    DrawToSurface(m_bgSurface, [&](ID2D1DeviceContext* ctx, POINT off) {
        D2D1_SIZE_U ps = m_liveBmp->GetPixelSize();
        ctx->SetTransform(D2D1::Matrix3x2F::Scale((float)m_bgW / (float)ps.width, (float)m_bgH / (float)ps.height) *
                          D2D1::Matrix3x2F::Translation((float)off.x, (float)off.y));
        bool drawn = false;
        if (blur) {
            ID2D1Effect* fx = nullptr;
            if (SUCCEEDED(ctx->CreateEffect(CLSID_D2D1GaussianBlur, &fx)) && fx) {
                fx->SetInput(0, m_liveBmp);
                fx->SetValue(D2D1_GAUSSIANBLUR_PROP_STANDARD_DEVIATION, sigma);
                fx->SetValue(D2D1_GAUSSIANBLUR_PROP_BORDER_MODE, (UINT32)D2D1_BORDER_MODE_SOFT);
                ID2D1Image* out = nullptr;
                fx->GetOutput(&out);
                if (out) {
                    D2D1_POINT_2F pt = D2D1::Point2F(0.0f, 0.0f);
                    D2D1_RECT_F srcR = D2D1::RectF(0.0f, 0.0f, (float)ps.width, (float)ps.height);
                    ctx->DrawImage(out, &pt, &srcR, D2D1_INTERPOLATION_MODE_LINEAR, D2D1_COMPOSITE_MODE_SOURCE_OVER);
                    out->Release();
                    drawn = true;
                }
                fx->Release();
            }
        }
        if (!drawn) ctx->DrawBitmap(m_liveBmp, D2D1::RectF(0.0f, 0.0f, (float)ps.width, (float)ps.height));

        ID2D1SolidColorBrush* dimBrush = nullptr;
        ctx->CreateSolidColorBrush(D2D1::ColorF(8.0f / 255.0f, 10.0f / 255.0f, 16.0f / 255.0f, (float)m_cfg.dim / 100.0f), &dimBrush);
        if (dimBrush) {
            ctx->SetTransform(D2D1::Matrix3x2F::Translation((float)off.x, (float)off.y));
            ctx->FillRectangle(D2D1::RectF(0.0f, 0.0f, (float)m_bgW, (float)m_bgH), dimBrush);
            dimBrush->Release();
        }
    });
}

// Work area = monitor minus the taskbar (also when an auto-hide taskbar is currently shown).
void CubeRenderer::ComputeWorkArea(const RECT& mon, const RECT& work) {
    const float SW = (float)(mon.right - mon.left), SH = (float)(mon.bottom - mon.top);
    float l = (float)(work.left - mon.left), t = (float)(work.top - mon.top);
    float r = (float)(mon.right - work.right), b = (float)(mon.bottom - work.bottom);

    auto consider = [&](HWND tray) {
        if (!tray || !IsWindowVisible(tray)) return;
        if (MonitorFromWindow(tray, MONITOR_DEFAULTTONEAREST) != m_hMonitor) return;
        RECT tb{}, x{};
        if (!GetWindowRect(tray, &tb) || !IntersectRect(&x, &tb, &mon)) return;
        int tw = x.right - x.left, th = x.bottom - x.top;
        if (tw >= (mon.right - mon.left) - 4 && (float)th < SH / 3.0f) {
            if (x.top <= mon.top + 2) t = std::max(t, (float)(x.bottom - mon.top));
            else if (x.bottom >= mon.bottom - 2) b = std::max(b, (float)(mon.bottom - x.top));
        } else if (th >= (mon.bottom - mon.top) - 4 && (float)tw < SW / 3.0f) {
            if (x.left <= mon.left + 2) l = std::max(l, (float)(x.right - mon.left));
            else if (x.right >= mon.right - 2) r = std::max(r, (float)(mon.right - x.left));
        }
    };
    consider(FindWindowW(L"Shell_TrayWnd", nullptr));
    HWND sec = nullptr;
    while ((sec = FindWindowExW(nullptr, sec, L"Shell_SecondaryTrayWnd", nullptr)) != nullptr) consider(sec);

    l = std::clamp(l, 0.0f, SW * 0.4f); r = std::clamp(r, 0.0f, SW * 0.4f);
    t = std::clamp(t, 0.0f, SH * 0.4f); b = std::clamp(b, 0.0f, SH * 0.4f);
    m_wl = l / SW; m_wt = t / SH; m_wr = 1.0f - r / SW; m_wb = 1.0f - b / SH;
    m_workRect = { mon.left + (LONG)l, mon.top + (LONG)t, mon.right - (LONG)r, mon.bottom - (LONG)b };
}

// ---------------------------------------------------------------------------
// Alt+Tab style window switcher
// ---------------------------------------------------------------------------
struct AltEnumCtx {
    std::vector<AltWin>* out;
    RECT mon;
    HWND self;
    IVirtualDesktopManager* vdm;
};

static BOOL CALLBACK AltEnumProc(HWND h, LPARAM lp) {
    AltEnumCtx* c = (AltEnumCtx*)lp;
    if (c->out->size() >= (size_t)kMaxAlt) return FALSE;
    if (h == c->self || !IsWindowVisible(h) || IsIconic(h)) return TRUE;

    LONG ex = GetWindowLongW(h, GWL_EXSTYLE);
    const bool app = (ex & WS_EX_APPWINDOW) != 0;
    if (!app && (ex & (WS_EX_TOOLWINDOW | WS_EX_NOACTIVATE))) return TRUE;
    if (!app && GetWindow(h, GW_OWNER)) return TRUE;

    DWORD cloaked = 0;
    DwmGetWindowAttribute(h, DWMWA_CLOAKED, &cloaked, sizeof(cloaked));
    if (cloaked) return TRUE;

    if (ex & WS_EX_LAYERED) {
        BYTE a = 255; DWORD fl = 0;
        if (GetLayeredWindowAttributes(h, nullptr, &a, &fl) && (fl & LWA_ALPHA) && a < 8) return TRUE;
    }

    WCHAR title[256]{};
    GetWindowTextW(h, title, ARRAYSIZE(title));
    if (!title[0]) return TRUE;

    WCHAR cls[128]{};
    GetClassNameW(h, cls, ARRAYSIZE(cls));
    static const wchar_t* kSkip[] = { L"Progman", L"WorkerW", L"Shell_TrayWnd", L"Shell_SecondaryTrayWnd",
        L"Windows.UI.Core.CoreWindow", L"XamlExplorerHostIslandWindow", L"NotifyIconOverflowWindow",
        L"TopLevelWindowForOverflowXamlIsland" };
    for (const wchar_t* s : kSkip) if (_wcsicmp(cls, s) == 0) return TRUE;
    if (_wcsicmp(cls, kOverlayClassName) == 0) return TRUE;

    RECT rc{};
    if (FAILED(DwmGetWindowAttribute(h, DWMWA_EXTENDED_FRAME_BOUNDS, &rc, sizeof(rc)))) GetWindowRect(h, &rc);
    RECT cl{};
    if (!IntersectRect(&cl, &rc, &c->mon)) return TRUE;
    if ((cl.right - cl.left) < 120 || (cl.bottom - cl.top) < 80) return TRUE;

    if (c->vdm) {
        BOOL on = TRUE;
        if (SUCCEEDED(c->vdm->IsWindowOnCurrentVirtualDesktop(h, &on)) && !on) return TRUE;
    }

    AltWin w;
    w.hwnd = h;
    w.r = cl;
    w.title = title;
    c->out->push_back(w);
    return TRUE;
}

void CubeRenderer::CollectAltWindows() {
    m_alt.clear();
    if (!m_cfg.altTab) return;
    com_ptr<IVirtualDesktopManager> vdm;
    CoCreateInstance(CLSID_VirtualDesktopManager, nullptr, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(vdm.put()));
    AltEnumCtx ctx{ &m_alt, m_workRect, m_hwnd, vdm.get() };
    EnumWindows(AltEnumProc, (LPARAM)&ctx);   // top-most first, like the Alt+Tab list
    LOG_DBG(L"Window switcher: %d windows", (int)m_alt.size());
}

// Window visuals are created now, their live surfaces on the first scroll notch.
void CubeRenderer::BuildAltVisuals() {
    m_altReady = false;
    m_altAttached = false;
    m_altShown = false;
    m_altOrderDirty = true;
    m_labelIdx = -1;
    m_selMode = false;
    m_selT = 0.0f;
    m_selIdx = 0;
    m_selSteps.store(0);
    m_winVis.clear();
    m_winBrush.clear();
    if (!m_cfg.altTab || !m_liveSurface || m_alt.empty()) return;

    for (int i = 0; i < (int)m_alt.size() && i < kMaxAlt; ++i) {
        SpriteVisual v = m_compositor.CreateSpriteVisual();
        v.IsVisible(false);
        m_winVis.push_back(v);
        m_winLift[i] = 0.0f;
        m_winOp[i] = 0.6f;
    }
    m_winBrush.assign(m_winVis.size(), CompositionSurfaceBrush{ nullptr });
    m_glow = m_compositor.CreateSpriteVisual();
    {
        auto gb = m_compositor.CreateLinearGradientBrush();
        gb.MappingMode(CompositionMappingMode::Relative);
        gb.StartPoint({ 0.0f, 0.0f });
        gb.EndPoint({ 1.0f, 1.0f });
        gb.ColorStops().Append(m_compositor.CreateColorGradientStop(0.0f, winrt::Windows::UI::Color{ 235, (uint8_t)(m_cfg.actStart >> 16), (uint8_t)(m_cfg.actStart >> 8), (uint8_t)m_cfg.actStart }));
        gb.ColorStops().Append(m_compositor.CreateColorGradientStop(1.0f, winrt::Windows::UI::Color{ 235, (uint8_t)(m_cfg.actEnd >> 16), (uint8_t)(m_cfg.actEnd >> 8), (uint8_t)m_cfg.actEnd }));
        m_glow.Brush(gb);
    }
    m_glow.IsVisible(false);

    m_label = m_compositor.CreateSpriteVisual();
    m_label.Size({ 280.0f, 22.0f });
    m_labelSurface = MakeSurface(560, 44);
    m_labelBrush = m_compositor.CreateSurfaceBrush(m_labelSurface);
    m_label.Brush(m_labelBrush);
    m_label.IsVisible(false);
    m_altReady = true;
}

// Every window of the switcher gets a thumbnail card, drawn from the live screen frame.
// (It shows what is visible on screen, so a part hidden behind another window shows that window.)
bool CubeRenderer::EnsureAltSurfaces() {
    if (!m_altSurf.empty() && m_altSurf.size() == m_winVis.size()) return true;
    m_altSurf.clear();
    if (!m_liveBmp) return false;

    const float sx = (float)m_liveW / m_screenWidth, sy = (float)m_liveH / m_screenHeight;
    bool any = false;
    for (size_t i = 0; i < m_winVis.size(); ++i) {
        AltSurf s;
        const RECT r = m_alt[i].r;
        int x0 = (int)std::lround((float)(r.left - m_monitorRect.left) * sx) - (int)m_workPx.left;
        int y0 = (int)std::lround((float)(r.top - m_monitorRect.top) * sy) - (int)m_workPx.top;
        int x1 = (int)std::lround((float)(r.right - m_monitorRect.left) * sx) - (int)m_workPx.left;
        int y1 = (int)std::lround((float)(r.bottom - m_monitorRect.top) * sy) - (int)m_workPx.top;
        x0 = std::clamp(x0, 0, m_workW); x1 = std::clamp(x1, 0, m_workW);
        y0 = std::clamp(y0, 0, m_workH); y1 = std::clamp(y1, 0, m_workH);
        if (x1 - x0 >= 16 && y1 - y0 >= 16) {
            const float k = std::min(1.0f, 960.0f / (float)(x1 - x0));
            s.w = std::max(16, (int)((float)(x1 - x0) * k));
            s.h = std::max(16, (int)((float)(y1 - y0) * k));
            s.surf = MakeSurface(s.w, s.h);
            if (s.surf) { s.box = { x0, y0, x1, y1 }; s.ok = true; }
        }
        m_altSurf.push_back(s);
        if (s.ok) {
            DrawThumb((int)i);
            m_winBrush[i] = m_compositor.CreateSurfaceBrush(s.surf);
            m_winBrush[i].Stretch(CompositionStretch::Fill);
            m_winVis[i].Brush(m_winBrush[i]);
            any = true;
        }
    }
    LOG_DBG(L"Window switcher: %d thumbnail cards", (int)m_altSurf.size());
    return any;
}

void CubeRenderer::DrawThumb(int i) {
    if (i < 0 || i >= (int)m_altSurf.size() || !m_liveBmp) return;
    AltSurf& s = m_altSurf[i];
    if (!s.ok) return;
    const D2D1_RECT_F src = D2D1::RectF((float)s.box.left, (float)s.box.top, (float)s.box.right, (float)s.box.bottom);
    if (s.snapValid && !s.snap.empty() && AltIsOccluded(m_alt, i)) {   // covered window: show its real pixels
        DrawToSurface(s.surf, [&](ID2D1DeviceContext* ctx, POINT off) {
            ctx->SetTransform(D2D1::Matrix3x2F::Translation((float)off.x, (float)off.y));
            ID2D1Bitmap* sb = nullptr;
            if (SUCCEEDED(ctx->CreateBitmap(D2D1::SizeU(s.snapW, s.snapH), s.snap.data(), (UINT32)s.snapW * 4,
                    D2D1::BitmapProperties(D2D1::PixelFormat(DXGI_FORMAT_B8G8R8A8_UNORM, D2D1_ALPHA_MODE_IGNORE)), &sb)) && sb) {
                const D2D1_RECT_F ss = D2D1::RectF((float)s.snapSrc.left, (float)s.snapSrc.top, (float)s.snapSrc.right, (float)s.snapSrc.bottom);
                ctx->DrawBitmap(sb, D2D1::RectF(0.0f, 0.0f, (float)s.w, (float)s.h), 1.0f, D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, &ss);
                sb->Release();
            }
        });
        return;
    }
    DrawToSurface(s.surf, [&](ID2D1DeviceContext* ctx, POINT off) {
        ctx->SetTransform(D2D1::Matrix3x2F::Translation((float)off.x, (float)off.y));
        ctx->DrawBitmap(m_liveBmp, D2D1::RectF(0.0f, 0.0f, (float)s.w, (float)s.h), 1.0f,
                        D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, &src);
    });
}

// Selected card every frame, one other card per frame (round robin).
void CubeRenderer::UpdateThumbs() {
    if (!m_selMode) return;
    const int n = (int)m_altSurf.size();
    if (n <= 0) return;
    if (m_selIdx >= 0 && m_selIdx < n && m_altSurf[m_selIdx].ok && m_selIdx < (int)m_alt.size() && AltIsOccluded(m_alt, m_selIdx)) {
        // The selected window is covered: grab its own pixels (once on selection, then about 3 times a second).
        AltSurf& ss = m_altSurf[m_selIdx];
        const ULONGLONG t = GetTickCount64();
        if (ss.snapTick == 0 || t - ss.snapTick > 300) {
            ss.snapTick = t;
            if (CaptureWindowPixels(m_alt[m_selIdx].hwnd, m_alt[m_selIdx].r, ss)) DrawThumb(m_selIdx);
        }
    }
    if (!m_thumbFresh) return;
    m_thumbFresh = false;
    DrawThumb(m_selIdx);
    if (n > 1 && (m_frameCounter & 3) == 0) {
        m_thumbRR = (m_thumbRR + 1) % n;
        if (m_thumbRR == m_selIdx) m_thumbRR = (m_thumbRR + 1) % n;
        DrawThumb(m_thumbRR);
    }
}

void CubeRenderer::RedrawLabel() {
    m_labelIdx = m_selIdx;
    if (!m_labelSurface || m_selIdx < 0 || m_selIdx >= (int)m_alt.size()) return;
    const std::wstring title = m_alt[m_selIdx].title;
    DrawToSurface(m_labelSurface, [&](ID2D1DeviceContext* ctx, POINT off) {
        ctx->SetTextAntialiasMode(D2D1_TEXT_ANTIALIAS_MODE_GRAYSCALE);
        ctx->Clear(D2D1::ColorF(0.0f, 0.0f, 0.0f, 0.0f));
        ctx->SetTransform(D2D1::Matrix3x2F::Scale(2.0f, 2.0f) *
                          D2D1::Matrix3x2F::Translation((float)off.x, (float)off.y));
        ID2D1SolidColorBrush* pill = nullptr;
        ID2D1SolidColorBrush* txt = nullptr;
        ctx->CreateSolidColorBrush(D2D1::ColorF(0.0667f, 0.0667f, 0.1059f, 0.92f), &pill);
        ctx->CreateSolidColorBrush(D2D1::ColorF(0.8039f, 0.8392f, 0.9569f, 1.0f), &txt);
        if (pill && txt && m_textFormatBadge) {
            ctx->FillRoundedRectangle(D2D1::RoundedRect(D2D1::RectF(0.0f, 0.0f, 280.0f, 22.0f), 11.0f, 11.0f), pill);
            ctx->DrawText(title.c_str(), (UINT32)title.length(), m_textFormatBadge,
                          D2D1::RectF(10.0f, 0.0f, 270.0f, 22.0f), txt, D2D1_DRAW_TEXT_OPTIONS_CLIP);
        }
        if (pill) pill->Release();
        if (txt) txt->Release();
    });
}

void CubeRenderer::UpdateAltTab(float dt) {
    if (!m_altReady) return;
    const int n = (int)m_alt.size();
    int st = m_selSteps.exchange(0);
    if (st != 0 && m_phase == Phase::Drag && n > 0) {
        if (!m_selMode) {
            if (!EnsureAltSurfaces()) return;
            m_selMode = true;
            m_selIdx = 0;
            for (int i = 0; i < n; ++i) { m_winLift[i] = 0.0f; m_winOp[i] = 0.6f; }
        }
        m_selIdx = ((m_selIdx + st) % n + n) % n;
        m_altOrderDirty = true;
        m_altDirty = true;
    }

    const float target = (m_selMode && m_phase == Phase::Drag) ? 1.0f : 0.0f;
    const float k = 1.0f - std::exp(-dt * 16.0f);
    const float prev = m_selT;
    m_selT += (target - m_selT) * k;
    if (std::fabs(target - m_selT) < 0.003f) m_selT = target;
    bool moved = (m_selT != prev);

    for (int i = 0; i < n && i < kMaxAlt; ++i) {
        float tl = m_selMode ? ((i == m_selIdx) ? m_cfg.altLift : m_cfg.altLift * 0.35f) : 0.0f;
        float to = (i == m_selIdx) ? 1.0f : 0.35f;
        float nl = m_winLift[i] + (tl - m_winLift[i]) * k;
        float no = m_winOp[i] + (to - m_winOp[i]) * k;
        if (std::fabs(nl - m_winLift[i]) > 0.01f || std::fabs(no - m_winOp[i]) > 0.001f) moved = true;
        m_winLift[i] = nl;
        m_winOp[i] = no;
    }
    if (moved) m_altDirty = true;
}

void CubeRenderer::HideAlt() {
    if (!m_altShown) return;
    for (auto& v : m_winVis) if (v) v.IsVisible(false);
    if (m_glow) m_glow.IsVisible(false);
    if (m_label) m_label.IsVisible(false);
    m_altShown = false;
}

void CubeRenderer::LayoutAlt(const Mat4& view, float faceDeg, float lifeEase) {
    if (!m_altReady || !m_cubeContainer) return;
    const int n = std::min((int)m_winVis.size(), kMaxAlt);
    if (n <= 0 || m_selIdx < 0 || m_selIdx >= n || (int)m_altSurf.size() < n) return;

    const float W = m_faceWidth, H = m_faceHeight, D = m_D;
    const float workW = (float)(m_workRect.right - m_workRect.left);
    const float workH = (float)(m_workRect.bottom - m_workRect.top);
    if (workW < 2.0f || workH < 2.0f) return;

    if (!m_altAttached || m_altOrderDirty) {
        auto ch = m_cubeContainer.Children();
        if (m_altAttached) {
            for (int i = 0; i < n; ++i) { try { ch.Remove(m_winVis[i]); } catch (...) {} }
            try { ch.Remove(m_glow); } catch (...) {}
            try { ch.Remove(m_label); } catch (...) {}
        }
        for (int i = n - 1; i >= 0; --i) if (i != m_selIdx) ch.InsertAtTop(m_winVis[i]);
        ch.InsertAtTop(m_glow);
        ch.InsertAtTop(m_winVis[m_selIdx]);
        ch.InsertAtTop(m_label);
        m_altAttached = true;
        m_altOrderDirty = false;
    }
    if (m_labelIdx != m_selIdx) RedrawLabel();

    Mat4 rotFace = Mat4::RotationY(faceDeg * kPi / 180.0f);
    float selX = 0.0f, selY = 0.0f, selW = 0.0f, selLift = 0.0f;
    for (int i = 0; i < n; ++i) {
        auto& v = m_winVis[i];
        if (!m_altSurf[i].ok) { v.IsVisible(false); continue; }
        const RECT rc = m_alt[i].r;
        float fw = (float)(rc.right - rc.left) / workW * W, fh = (float)(rc.bottom - rc.top) / workH * H;
        float fx = (float)(rc.left - m_workRect.left) / workW * W;
        float fy = (float)(rc.top - m_workRect.top) / workH * H;
        if (i == m_selIdx) {   // the selected card grows a little around its centre
            const float gs = 1.0f + 0.08f * m_selT;
            fx -= fw * (gs - 1.0f) * 0.5f; fy -= fh * (gs - 1.0f) * 0.5f;
            fw *= gs; fh *= gs;
        }

        v.Size({ fw, fh });
        const float lift = m_winLift[i] * lifeEase;
        v.TransformMatrix((Mat4::Translation(-W * 0.5f + fx, -H * 0.5f + fy, 0.0f) *
                           Mat4::Translation(0.0f, 0.0f, D + lift) * rotFace * view).ToWinRT());
        v.Opacity(std::clamp(m_winOp[i] * m_selT, 0.0f, 1.0f));
        v.IsVisible(true);
        if (i == m_selIdx) { selX = fx; selY = fy; selW = fw; selLift = lift; m_glow.Size({ fw + 24.0f, fh + 24.0f }); }
    }

    // highlight frame just under the selected window, name tag above it
    m_glow.TransformMatrix((Mat4::Translation(-W * 0.5f + selX - 12.0f, -H * 0.5f + selY - 12.0f, 0.0f) *
                            Mat4::Translation(0.0f, 0.0f, D + selLift - 0.5f) * rotFace * view).ToWinRT());
    m_glow.Opacity(std::clamp(1.0f * m_selT, 0.0f, 1.0f));
    m_glow.IsVisible(true);

    float ly = selY - 30.0f;
    if (ly < 4.0f) ly = selY + 8.0f;
    m_label.TransformMatrix((Mat4::Translation(-W * 0.5f + selX + selW * 0.5f - 140.0f, -H * 0.5f + ly, 0.0f) *
                             Mat4::Translation(0.0f, 0.0f, D + selLift + 2.0f) * rotFace * view).ToWinRT());
    m_label.Opacity(std::clamp(m_selT, 0.0f, 1.0f));
    m_label.IsVisible(true);
    m_altShown = true;
}

void CubeRenderer::BuildVisuals() {
    EnsureTextFormat();
    BuildBackground();
    if (!m_backgroundVisual) {   // only needed when there is no blurred background
        m_backdropVisual = m_compositor.CreateSpriteVisual();
        m_backdropVisual.Size({ m_screenWidth, m_screenHeight });
        m_backdropVisual.Brush(m_compositor.CreateColorBrush({ 255, 17, 17, 27 }));
        m_rootVisual.Children().InsertAtBottom(m_backdropVisual);
    }

    if (m_cfg.shadow) RenderShadow();

    m_cubeContainer = m_compositor.CreateContainerVisual();
    m_cubeContainer.Size({ m_screenWidth, m_screenHeight });
    m_rootVisual.Children().InsertAtTop(m_cubeContainer);

    BuildFaceVisuals();
    BuildOverlayFx();
}

// The face clip and its two rings. The rings sit above the shade so the dimming never touches them.
void CubeRenderer::MakeFaceBorder(FaceVisuals& f) {
    const float W = m_faceWidth, H = m_faceHeight;
    f.clipGeo = m_compositor.CreateRoundedRectangleGeometry();
    f.clipGeo.Size({ W, H });
    f.clipGeo.CornerRadius({ 0.0f, 0.0f });
    f.clip = m_compositor.CreateGeometricClip(f.clipGeo);
    f.clipOn = false;

    auto ring = [&](ShapeVisual& vis, CompositionRoundedRectangleGeometry& geo, CompositionSpriteShape& shape,
                    CompositionBrush const& br) {
        geo = m_compositor.CreateRoundedRectangleGeometry();
        geo.Size({ W, H });
        shape = m_compositor.CreateSpriteShape(geo);
        shape.StrokeBrush(br);
        shape.StrokeThickness(1.0f);
        vis = m_compositor.CreateShapeVisual();
        vis.Size({ W, H });
        vis.Shapes().Append(shape);
        vis.Opacity(0.0f);
        vis.IsVisible(false);
        f.container.Children().InsertAtTop(vis);
    };
    ring(f.borderRest, f.geoRest, f.shapeRest, m_compositor.CreateColorBrush(ArgbColor(m_cfg.restColor)));

    auto grad = m_compositor.CreateLinearGradientBrush();
    grad.MappingMode(CompositionMappingMode::Relative);
    grad.StartPoint({ 0.0f, 0.0f });
    grad.EndPoint({ 1.0f, 1.0f });
    grad.ColorStops().Append(m_compositor.CreateColorGradientStop(0.0f, ArgbColor(m_cfg.actStart)));
    grad.ColorStops().Append(m_compositor.CreateColorGradientStop(1.0f, ArgbColor(m_cfg.actEnd)));
    ring(f.borderAct, f.geoAct, f.shapeAct, grad);
    f.cRad = -1.0f; f.cBw = -1.0f; f.cBr = -1.0f; f.cBa = -1.0f;
    f.cVisBr = -1; f.cVisBa = -1;
}

// rf = corner radius in face units, bwF = ring width in face units.
void CubeRenderer::UpdateFaceShape(FaceVisuals& f, float rf, float bwF) {
    const float W = m_faceWidth, H = m_faceHeight;
    if (rf > 0.25f) {
        f.clipGeo.CornerRadius({ rf, rf });
        if (!f.clipOn) { f.container.Clip(f.clip); f.clipOn = true; }
    } else if (f.clipOn) {
        f.container.Clip(nullptr);
        f.clipOn = false;
    }
    // The ring is drawn inside the face edge: inset by half the stroke, radius shrinks with it.
    const float inset = bwF * 0.5f;
    const float rr = std::max(rf - inset, 0.0f);
    for (int k = 0; k < 2; ++k) {
        auto& geo = k ? f.geoAct : f.geoRest;
        auto& shape = k ? f.shapeAct : f.shapeRest;
        geo.Offset({ inset, inset });
        geo.Size({ std::max(W - bwF, 1.0f), std::max(H - bwF, 1.0f) });
        geo.CornerRadius({ rr, rr });
        shape.StrokeThickness(std::max(bwF, 0.01f));
    }
}

void CubeRenderer::BuildFaceVisuals() {
    const float W = m_faceWidth, H = m_faceHeight;
    for (int i = 0; i < m_faceCount; ++i) {
        auto& f = m_faces[i];
        f.container = m_compositor.CreateContainerVisual();
        f.container.Size({ W, H });

        f.background = m_compositor.CreateSpriteVisual();
        f.background.Size({ W, H });
        f.background.Brush(m_compositor.CreateColorBrush({ 255, 30, 30, 46 }));
        f.container.Children().InsertAtBottom(f.background);

        f.shade = m_compositor.CreateSpriteVisual();
        f.shade.Size({ W, H });
        f.shade.Brush(m_compositor.CreateColorBrush({ 255, 0, 0, 0 }));
        f.shade.Opacity(0.0f);
        f.container.Children().InsertAtTop(f.shade);
        MakeFaceBorder(f);

        f.container.IsVisible(false);
        m_cubeContainer.Children().InsertAtTop(f.container);

        f.layer = m_compositor.CreateSpriteVisual();
        f.layer.Size({ kBadgeW, kBadgeH });
        f.layer.Opacity(0.0f);
        f.layer.IsVisible(false);
        m_cubeContainer.Children().InsertAtTop(f.layer);
    }
    m_zOrderValid = false;
}


// ---------------------------------------------------------------------------
// Add / remove desktops from the cube
// ---------------------------------------------------------------------------
// Rebuilds the prism for the current desktop count. The face textures survive, only the visuals change size.
void CubeRenderer::RebuildPrism() {
    if (!m_cubeContainer) return;
    FaceVisuals keep[kMaxFaces];
    for (int i = 0; i < kMaxFaces; ++i) keep[i] = m_faces[i];

    ComputeGeometry(m_desktopList.TotalCount());

    m_cubeContainer.Children().RemoveAll();
    m_altAttached = false;
    for (int i = 0; i < kMaxFaces; ++i) m_faces[i] = FaceVisuals{};
    BuildFaceVisuals();

    for (int i = 0; i < m_faceCount; ++i) {
        auto& f = m_faces[i];
        const auto& o = keep[i];
        f.surface = o.surface;
        f.layerSurface = o.layerSurface;
        f.brush = o.brush;
        f.layerBrush = o.layerBrush;
        f.liveBrush = o.liveBrush;
        f.renderedDesktop = o.renderedDesktop;
        f.renderedVersion = o.renderedVersion;
        f.usingLive = false;
        f.bAmt = o.bAmt; f.bTarget = o.bTarget;
        if (f.brush) f.background.Brush(f.brush);
        if (f.layerBrush && f.layer) f.layer.Brush(f.layerBrush);
    }
    m_zOrderValid = false;
    for (auto& a : m_applied) a = 1e9f;
}

void CubeRenderer::KickComposer() {
    const int total = m_desktopList.TotalCount();
    if (total <= 1) return;
    bool busy = m_composeThread && WaitForSingleObject(m_composeThread, 0) == WAIT_TIMEOUT;
    if (busy) { m_composeRestart = true; return; }
    if (m_composeThread) { CloseHandle(m_composeThread); m_composeThread = nullptr; }
    Composer::s_abort.store(false);
    auto job = std::make_unique<Composer::Job>();
    job->mon = m_monitorRect;
    job->list = m_desktopList;
    m_composeThread = Composer::Start(std::move(job));
    m_composeRestart = false;
}

void CubeRenderer::DrawZoneSurface(bool right) {
    ZoneVisual& z = right ? m_zoneR : m_zoneL;
    if (!z.surf) return;
    const float w = m_zoneW, h = m_screenHeight;
    DrawToSurface(z.surf, [&](ID2D1DeviceContext* ctx, POINT off) {
        ctx->SetTextAntialiasMode(D2D1_TEXT_ANTIALIAS_MODE_GRAYSCALE);
        ctx->Clear(D2D1::ColorF(0.0f, 0.0f, 0.0f, 0.0f));
        ctx->SetTransform(D2D1::Matrix3x2F::Translation((float)off.x, (float)off.y));

        // Frosted gray gradient: strongest at the screen edge, gone towards the cube.
        D2D1_GRADIENT_STOP stops[3] = {
            { 0.0f, D2D1::ColorF(0.3451f, 0.3569f, 0.4392f, 0.78f) },
            { 0.55f, D2D1::ColorF(0.3451f, 0.3569f, 0.4392f, 0.30f) },
            { 1.0f, D2D1::ColorF(0.3451f, 0.3569f, 0.4392f, 0.0f) }
        };
        ID2D1GradientStopCollection* gs = nullptr;
        ctx->CreateGradientStopCollection(stops, 3, &gs);
        if (gs) {
            const float x0 = right ? w : 0.0f, x1 = right ? 0.0f : w;
            ID2D1LinearGradientBrush* lb = nullptr;
            ctx->CreateLinearGradientBrush(
                D2D1::LinearGradientBrushProperties(D2D1::Point2F(x0, 0.0f), D2D1::Point2F(x1, 0.0f)), gs, &lb);
            if (lb) { ctx->FillRectangle(D2D1::RectF(0.0f, 0.0f, w, h), lb); lb->Release(); }
            gs->Release();
        }

        // Round button with + or - and a caption.
        const float cx = w * 0.5f, cy = h * 0.5f, r = 30.0f;
        ID2D1SolidColorBrush* fill = nullptr;
        ID2D1SolidColorBrush* line = nullptr;
        ID2D1SolidColorBrush* txt = nullptr;
        ctx->CreateSolidColorBrush(D2D1::ColorF(0.1922f, 0.1961f, 0.2667f, 0.88f), &fill);
        ctx->CreateSolidColorBrush(D2D1::ColorF(0.5373f, 0.7059f, 0.9804f, 1.0f), &line);
        ctx->CreateSolidColorBrush(D2D1::ColorF(0.8039f, 0.8392f, 0.9569f, 1.0f), &txt);
        if (fill && line && txt) {
            ctx->FillEllipse(D2D1::Ellipse(D2D1::Point2F(cx, cy), r, r), fill);
            ctx->DrawEllipse(D2D1::Ellipse(D2D1::Point2F(cx, cy), r, r), line, 2.0f);
            ctx->FillRoundedRectangle(D2D1::RoundedRect(D2D1::RectF(cx - 13.0f, cy - 2.0f, cx + 13.0f, cy + 2.0f), 2.0f, 2.0f), line);
            if (right) {
                ctx->FillRoundedRectangle(D2D1::RoundedRect(D2D1::RectF(cx - 2.0f, cy - 13.0f, cx + 2.0f, cy + 13.0f), 2.0f, 2.0f), line);
            }
            if (m_textFormatBadge) {
                const wchar_t* cap = right ? L"Add desktop" : L"Remove desktop";
                ctx->DrawText(cap, (UINT32)wcslen(cap), m_textFormatBadge,
                              D2D1::RectF(0.0f, cy + r + 8.0f, w, cy + r + 32.0f), txt, D2D1_DRAW_TEXT_OPTIONS_NONE);
                const wchar_t* hint = L"right-click";
                ctx->DrawText(hint, (UINT32)wcslen(hint), m_textFormatBadge,
                              D2D1::RectF(0.0f, cy + r + 30.0f, w, cy + r + 52.0f), txt, D2D1_DRAW_TEXT_OPTIONS_NONE);
            }
        }
        if (fill) fill->Release();
        if (line) line->Release();
        if (txt) txt->Release();
    });
}

void CubeRenderer::BuildOverlayFx() {
    m_zoneL = ZoneVisual{};
    m_zoneR = ZoneVisual{};
    m_toast = nullptr;
    m_toastSurface = nullptr;
    m_toastT = 0.0f;
    if (!m_cfg.edgeEdit) return;

    m_zoneW = std::clamp(m_screenWidth * m_cfg.edgeZone, 120.0f, 360.0f);
    for (int side = 0; side < 2; ++side) {
        ZoneVisual& z = side ? m_zoneR : m_zoneL;
        z.surf = MakeSurface((int)m_zoneW, (int)m_screenHeight);
        z.vis = m_compositor.CreateSpriteVisual();
        z.vis.Size({ m_zoneW, m_screenHeight });
        z.vis.CenterPoint({ side ? m_zoneW : 0.0f, m_screenHeight * 0.5f, 0.0f });
        z.baseX = side ? m_screenWidth - m_zoneW : 0.0f;
        z.vis.Offset({ z.baseX + (side ? 1.0f : -1.0f) * m_zoneW * 0.3f, 0.0f, 0.0f });   // starts hidden, slightly off screen
        auto br = m_compositor.CreateSurfaceBrush(z.surf);
        br.Stretch(CompositionStretch::Fill);
        z.vis.Brush(br);
        z.vis.Opacity(0.0f);
        DrawZoneSurface(side != 0);
        m_rootVisual.Children().InsertAtTop(z.vis);
    }

    m_toastSurface = MakeSurface(640, 56);
    m_toast = m_compositor.CreateSpriteVisual();
    m_toast.Size({ 320.0f, 28.0f });
    m_toast.Offset({ (m_screenWidth - 320.0f) * 0.5f, 36.0f, 0.0f });
    auto tb = m_compositor.CreateSurfaceBrush(m_toastSurface);
    tb.Stretch(CompositionStretch::Fill);
    m_toast.Brush(tb);
    m_toast.Opacity(0.0f);
    m_rootVisual.Children().InsertAtTop(m_toast);
}

void CubeRenderer::ShowToast(const wchar_t* text) {
    if (!m_toastSurface || !m_toast) return;
    std::wstring msg = text;
    DrawToSurface(m_toastSurface, [&](ID2D1DeviceContext* ctx, POINT off) {
        ctx->SetTextAntialiasMode(D2D1_TEXT_ANTIALIAS_MODE_GRAYSCALE);
        ctx->Clear(D2D1::ColorF(0.0f, 0.0f, 0.0f, 0.0f));
        ctx->SetTransform(D2D1::Matrix3x2F::Scale(2.0f, 2.0f) *
                          D2D1::Matrix3x2F::Translation((float)off.x, (float)off.y));
        ID2D1SolidColorBrush* pill = nullptr;
        ID2D1SolidColorBrush* txt = nullptr;
        ctx->CreateSolidColorBrush(D2D1::ColorF(0.0667f, 0.0667f, 0.1059f, 0.92f), &pill);
        ctx->CreateSolidColorBrush(D2D1::ColorF(0.8039f, 0.8392f, 0.9569f, 1.0f), &txt);
        if (pill && txt && m_textFormatBadge) {
            ctx->FillRoundedRectangle(D2D1::RoundedRect(D2D1::RectF(0.0f, 0.0f, 320.0f, 28.0f), 14.0f, 14.0f), pill);
            ctx->DrawText(msg.c_str(), (UINT32)msg.length(), m_textFormatBadge,
                          D2D1::RectF(10.0f, 0.0f, 310.0f, 28.0f), txt, D2D1_DRAW_TEXT_OPTIONS_CLIP);
        }
        if (pill) pill->Release();
        if (txt) txt->Release();
    });
    m_toastT = 1.0f;
}

// Zones fade in at the edges, flash when used and then vanish for a moment. Also steps spin / pop / birth.
void CubeRenderer::StepFx(float dt) {
    bool moving = false;

    if (m_kick.x != 0.0f || m_kick.v != 0.0f) {
        m_kick.Step(0.0f, 9.0f, 0.55f, dt);
        if (std::fabs(m_kick.x) < 0.01f && std::fabs(m_kick.v) < 0.05f) { m_kick.x = 0.0f; m_kick.v = 0.0f; }
        moving = true;
    }
    if (m_pop.x != 0.0f || m_pop.v != 0.0f) {
        m_pop.Step(0.0f, 11.0f, 0.5f, dt);
        if (std::fabs(m_pop.x) < 0.0005f && std::fabs(m_pop.v) < 0.005f) { m_pop.x = 0.0f; m_pop.v = 0.0f; }
        moving = true;
    }
    if (m_bornT < 1.0f) {
        m_bornT = std::min(1.0f, m_bornT + dt / 0.6f);
        moving = true;
    }
    {   // border highlight easing
        const float step = dt / std::max(0.001f * (float)m_cfg.borderFadeMs, 0.001f);
        for (int i = 0; i < m_faceCount; ++i) {
            auto& f = m_faces[i];
            if (f.bAmt == f.bTarget) continue;
            if (m_cfg.borderFadeMs <= 0 || std::fabs(f.bTarget - f.bAmt) <= step) f.bAmt = f.bTarget;
            else f.bAmt += (f.bTarget > f.bAmt) ? step : -step;
            moving = true;
        }
    }
    if (m_phase == Phase::Drag) {   // the pointer moved: the hovered face may have changed
        POINT hp{};
        if (ReadCursorPos(&hp) && (hp.x != m_hoverLast.x || hp.y != m_hoverLast.y)) {
            m_hoverLast = hp;
            m_fxDirty = true;
        }
    }
    if (moving) m_fxDirty = true;

    if (m_toast && m_toastT > 0.0f) {
        m_toastT = std::max(0.0f, m_toastT - dt / 1.6f);
        float a = std::min(1.0f, m_toastT * 6.0f) * std::min(1.0f, (1.0f - m_toastT) * 10.0f + 0.001f);
        m_toast.Opacity(m_toastT > 0.0f ? a : 0.0f);
        moving = true;
    }

    if (m_zoneL.vis && m_zoneR.vis) {
        POINT cp{};
        GetCursorPos(&cp);
        const bool inY = cp.y >= m_monitorRect.top && cp.y < m_monitorRect.bottom;
        const LONG distL = cp.x - m_monitorRect.left;           // distance to the left screen edge
        const LONG distR = m_monitorRect.right - 1 - cp.x;      // distance to the right screen edge
        const LONG revealW = (LONG)std::min<float>((float)m_cfg.edgeReveal, m_zoneW);
        const bool open = m_phase == Phase::Drag && m_zoom.x > 0.6f && !m_vd.active &&
                          std::chrono::steady_clock::now() >= m_zoneQuietUntil;
        const float kIn = 1.0f - std::exp(-dt * 14.0f);
        const float kOut = 1.0f - std::exp(-dt * 9.0f);
        for (int side = 0; side < 2; ++side) {
            ZoneVisual& z = side ? m_zoneR : m_zoneL;
            const LONG d = side ? distR : distL;
            // Reveal when the pointer touches the edge strip, keep it while the pointer stays inside the zone.
            if (!open || !inY || d < 0 || d >= (LONG)m_zoneW) z.shown = false;
            else if (d < revealW) z.shown = true;
            const float target = z.shown ? 1.0f : 0.0f;
            const float prevOp = z.op, prevPulse = z.pulse;
            z.op += (target - z.op) * (target > z.op ? kIn : kOut);
            if (std::fabs(target - z.op) < 0.003f) z.op = target;
            z.pulse *= std::exp(-dt * 4.5f);
            if (z.pulse < 0.01f) z.pulse = 0.0f;
            if (z.op != prevOp || z.pulse != prevPulse) {
                const float vis = std::min(1.0f, z.op + z.pulse * 0.6f);
                z.vis.Opacity(vis);
                z.vis.IsVisible(vis > 0.002f);   // fully hidden zones cost nothing
                const float slide = (1.0f - z.op) * m_zoneW * 0.3f;
                z.vis.Offset({ z.baseX + (side ? slide : -slide), 0.0f, 0.0f });
                z.vis.Scale({ 1.0f + 0.7f * z.pulse, 1.0f, 1.0f });
                moving = true;
            }
        }
    }

    if (moving) m_busy = true;
}

bool CubeRenderer::OnRightDown(POINT pt) {
    if (!m_cfg.edgeEdit || !m_sceneActive.load() || !m_zoneL.vis) return false;
    if (m_phase != Phase::Drag || m_zoom.x < 0.8f) return false;
    if (pt.y < m_monitorRect.top || pt.y >= m_monitorRect.bottom) return false;
    const bool L = pt.x >= m_monitorRect.left && pt.x < m_monitorRect.left + (LONG)m_zoneW;
    const bool R = pt.x < m_monitorRect.right && pt.x >= m_monitorRect.right - (LONG)m_zoneW;
    if (!L && !R) return false;
    // A zone that is not showing is not clickable (no invisible buttons).
    if (!(R ? m_zoneR : m_zoneL).shown || (R ? m_zoneR : m_zoneL).op < 0.35f) return false;
    if (m_vd.active || m_pendingVdOp.load() != 0 || std::chrono::steady_clock::now() < m_vdCooldown) return true;   // swallowed, ignored
    (R ? m_zoneR : m_zoneL).pulse = 1.0f;
    m_zoneQuietUntil = std::chrono::steady_clock::now() + std::chrono::milliseconds(1300);
    // This runs inside the WH_MOUSE_LL callback, so it must return at once. Only record the request,
    // Frame() does the actual work (COM, registry, drawing).
    m_pendingVdOp.store(R ? 1 : 2);
    Wake();
    return true;
}

void CubeRenderer::StartVdOp(int kind) {
    VDManager::DesktopList now;
    VDManager::QueryDesktops(now);
    const int T = now.TotalCount();
    int c = now.currentIndex;
    int rc = -1;
    if (VDManager::ReadCurrentIndex(rc) && rc >= 0 && rc < T) c = rc;

    if (kind == 1 && T >= kMaxDesktops) { ShowToast(L"Desktop limit reached"); return; }
    if (kind == 2 && T <= 1) { ShowToast(L"Can't remove the only desktop"); return; }

    const auto t = std::chrono::steady_clock::now();
    m_vd = VdTask{};
    m_vd.active = true;
    m_vd.kind = kind;
    m_vd.oldTotal = T;
    m_vd.origCur = c;
    m_vd.goalA = (kind == 1) ? c : (T - 1);   // adding acts where we are, removing acts on the last desktop
    m_vd.stage = 0;
    m_vd.nextAt = t;
    m_vd.deadline = t + std::chrono::milliseconds(4500);
    m_vd.swmFailed = !(m_cfg.useSwm && VDManager::SwmBridge::IsAvailable());
    if (m_cfg.suppressSysAnim) VDManager::SuppressSystemAnimation(true);
    LOG_DBG(L"Desktop %s: total=%d current=%d", kind == 1 ? L"add" : L"remove", T, c);
}

// Runs every frame while an add / remove is in progress. All of it happens under the opaque overlay.
void CubeRenderer::UpdateVdOp() {
    if (!m_vd.active) return;
    const auto now = std::chrono::steady_clock::now();
    const bool timedOut = now > m_vd.deadline;
    if (now < m_vd.nextAt && !timedOut) return;
    const auto ms = [](int v) { return std::chrono::milliseconds(v); };

    if (m_vd.stage == 0 || m_vd.stage == 3) {
        const int goal = (m_vd.stage == 0) ? m_vd.goalA : m_vd.goalC;
        int cur = -1;
        if (!VDManager::ReadCurrentIndex(cur)) cur = goal;
        if (m_vd.waiting) {
            if (cur != m_vd.waitCur) m_vd.waiting = false;
            else if (now > m_vd.waitDeadline || timedOut) { FinishVdOp(false); return; }
            else { m_vd.nextAt = now + ms(8); return; }
        }
        if (cur == goal || timedOut) {
            if (m_vd.stage == 3 || timedOut) { FinishVdOp(!timedOut); return; }
            m_vd.stage = 1;
        } else {
            // Seamless Window Manager first (desktops 1 to 9), the Windows shortcut if it does not react.
            if (!m_vd.swmFailed && goal >= 0 && goal <= 8) {
                if (!m_vd.jumpSent) {
                    m_vd.jumpStartCur = cur;
                    if (VDManager::SwmBridge::SendDesktopHotkey(goal)) {
                        m_vd.jumpSent = true;
                        m_vd.jumpAt = now;
                        m_vd.nextAt = now + ms(8);
                        return;
                    }
                    m_vd.swmFailed = true;
                } else {
                    const int waited = (int)std::chrono::duration_cast<std::chrono::milliseconds>(now - m_vd.jumpAt).count();
                    if (waited <= (cur != m_vd.jumpStartCur ? 1800 : 1200)) { m_vd.nextAt = now + ms(8); return; }
                    m_vd.swmFailed = true;
                    LOG_INF(L"Seamless Window Manager did not switch, using the Windows shortcut");
                }
            }
            VDManager::SendSwitchStep(goal > cur ? 1 : -1);
            m_vd.waiting = true;
            m_vd.waitCur = cur;
            m_vd.waitDeadline = now + ms(900);
            m_vd.nextAt = now + ms(45);
            return;
        }
    }

    if (m_vd.stage == 1) {
        if (m_vd.kind == 1) VDManager::SendAddDesktop(); else VDManager::SendCloseDesktop();
        m_vd.stage = 2;
        m_vd.actDeadline = now + ms(1600);
        m_vd.nextAt = now + ms(40);
        return;
    }

    if (m_vd.stage == 2) {
        int total = -1;
        const int want = (m_vd.kind == 1) ? m_vd.oldTotal + 1 : m_vd.oldTotal - 1;
        if (VDManager::ReadTotalCount(total) && total == want) {
            int cur = -1;
            VDManager::ReadCurrentIndex(cur);
            if (m_vd.kind == 1) m_vd.goalC = m_vd.origCur;
            else m_vd.goalC = (m_vd.origCur < m_vd.oldTotal - 1) ? m_vd.origCur : (cur >= 0 ? cur : 0);
            m_vd.stage = 3;
            m_vd.waiting = false;
            m_vd.jumpSent = false;
            m_vd.nextAt = now + ms(40);
        } else if (now > m_vd.actDeadline || timedOut) {
            FinishVdOp(false);
        } else {
            m_vd.nextAt = now + ms(10);
        }
    }
}

void CubeRenderer::FinishVdOp(bool ok) {
    m_vd.active = false;
    if (m_cfg.suppressSysAnim) VDManager::SuppressSystemAnimation(false);
    m_vdCooldown = std::chrono::steady_clock::now() + std::chrono::milliseconds(300);

    VDManager::DesktopList nl;
    VDManager::QueryDesktops(nl);
    int rc = -1;
    if (VDManager::ReadCurrentIndex(rc) && rc >= 0 && rc < nl.TotalCount()) nl.currentIndex = rc;

    if (nl.TotalCount() != m_vd.oldTotal) {
        ApplyDesktopCountChange(nl, m_vd.oldTotal);
    } else {
        ShowToast(m_vd.kind == 1 ? L"Could not add a desktop" : L"Could not remove the desktop");
        m_desktopList = nl;
        if (m_liveDesktop != nl.currentIndex) { m_liveDesktop = nl.currentIndex; m_applied[0] = 1e9f; }
    }
    (void)ok;
}

void CubeRenderer::ApplyDesktopCountChange(const VDManager::DesktopList& nl, int oldTotal) {
    const bool added = nl.TotalCount() > oldTotal;
    const int oldFaces = m_faceCount;
    const float oldStep = m_stepDeg;

    m_desktopList = nl;
    const int total = nl.TotalCount();
    if (m_liveDesktop != nl.currentIndex) m_liveDesktop = nl.currentIndex;

    if (std::clamp(total, 1, kMaxFaces) != oldFaces) {
        RebuildPrism();
        const float k = (oldStep > 0.0f) ? m_stepDeg / oldStep : 1.0f;   // the same face stays in front
        m_yaw.x *= k; m_yaw.v *= k;
        GestureController::RescaleYaw(k);
    }

    m_kick.x = (added ? 1.0f : -1.0f) * m_stepDeg * 0.9f;
    m_kick.v = 0.0f;
    m_pop.x = -0.30f;
    m_pop.v = 0.0f;
    if (added) { m_bornDesktop = total - 1; m_bornT = 0.0f; } else { m_bornDesktop = -1; m_bornT = 1.0f; }
    m_fxDirty = true;
    m_busy = true;
    m_zOrderValid = false;
    for (auto& a : m_applied) a = 1e9f;

    KickComposer();

    wchar_t msg[96];
    if (added) swprintf_s(msg, L"Desktop %d added   (%d desktops)", total, total);
    else swprintf_s(msg, L"Desktop %d removed   (%d desktops)", oldTotal, total);
    ShowToast(msg);
    LOG_INF(L"Desktops now %d (faces %d)", total, m_faceCount);
}

void CubeRenderer::ComputeGeometry(int total) {
    m_faceCount = std::clamp(total, 1, kMaxFaces);
    m_stepDeg = 360.0f / (float)m_faceCount;

    // Prism geometry. Face width is chosen so the prism footprint matches a 4 sided cube.
    float W4 = m_screenWidth * m_cfg.faceSize;
    float R4 = W4 * 0.70711f;
    float W;
    if (m_faceCount >= 3) W = 2.0f * R4 * std::sin(kPi / (float)m_faceCount);
    else W = W4 * 1.15f;
    W = std::clamp(W, m_screenWidth * 0.30f, m_screenWidth * 0.94f);
    m_faceWidth = W;
    m_faceHeight = W * (m_screenHeight / m_screenWidth);
    float gapMul = 1.0f + m_cfg.faceGap * 2.0f;
    if (m_faceCount >= 3) m_D = (W * 0.5f) / std::tan(kPi / (float)m_faceCount) * gapMul;
    else if (m_faceCount == 2) m_D = W * 0.10f * gapMul;
    else m_D = W * 0.04f;
}

// Normally the overlay is hidden from every capture API so the live feed never films itself.
// In recording mode it stays visible to capture; the live feed is then off (m_canExclude == false) and the
// taskbar is not hidden from capture either, so a recording shows exactly what is on screen.
void CubeRenderer::ApplyCaptureAffinity(bool recordingMode) {
    if (!m_hwnd) return;
    if (recordingMode) {
        SetWindowDisplayAffinity(m_hwnd, 0 /*WDA_NONE*/);
        m_canExclude = false;
        return;
    }
    m_canExclude = SetWindowDisplayAffinity(m_hwnd, WDA_EXCLUDEFROMCAPTURE) != 0;
    if (!m_canExclude) LOG_INF(L"WDA_EXCLUDEFROMCAPTURE unavailable (needs Windows 10 2004+), live capture off");
}

bool CubeRenderer::BeginScene() {
    ApplyCaptureAffinity(m_cfg.recordingMode);
    // ---- monitor / geometry ----
    m_hMonitor = MonitorFromPoint(m_anchor, MONITOR_DEFAULTTONEAREST);
    MONITORINFOEXW mi{};
    mi.cbSize = sizeof(mi);
    if (!GetMonitorInfoW(m_hMonitor, &mi)) return false;
    m_monitorRect = mi.rcMonitor;
    int monW = mi.rcMonitor.right - mi.rcMonitor.left;
    int monH = mi.rcMonitor.bottom - mi.rcMonitor.top;
    if (monW <= 0 || monH <= 0) return false;

    m_screenWidth = (float)monW;
    m_screenHeight = (float)monH;
    {
        DEVMODEW dm{};
        dm.dmSize = sizeof(dm);
        m_monitorHz = EnumDisplaySettingsW(mi.szDevice, ENUM_CURRENT_SETTINGS, &dm) ? (float)dm.dmDisplayFrequency : 0.0f;
    }
    ComputeWorkArea(mi.rcMonitor, mi.rcWork);
    if (m_canExclude && ExcludeTaskbarsFromCapture()) {
        // Taskbar is invisible to capture now: the faces use the whole screen, nothing is cropped.
        m_wl = 0.0f; m_wt = 0.0f; m_wr = 1.0f; m_wb = 1.0f;
        m_workRect = mi.rcMonitor;
        DwmFlush(); DwmFlush();   // let DWM drop the taskbar from the next captured frame
        LOG_INF(L"Taskbar hidden from capture, faces are uncropped");
    } else {
        RestoreTaskbarCapture();   // also undoes the flag from an earlier gesture made without recording mode
        LOG_INF(L"Taskbar not hidden from capture (recording mode or unsupported), using cropped work area");
    }

    // ---- desktops, then the face count follows the desktop count ----
    VDManager::QueryDesktops(m_desktopList);
    int total = m_desktopList.TotalCount();
    DesktopCaptureManager::Prune(m_desktopList, 10ULL * 60ULL * 1000ULL);   // removed desktops / very old snapshots
    ComputeGeometry(total);

    float q = (float)m_cfg.texQuality / 100.0f;
    m_texW = std::clamp((int)(m_screenWidth * q), 320, 1920);
    m_texH = std::max(180, (int)((float)m_texW * m_screenHeight / m_screenWidth));

    // ---- capture BEFORE the overlay is visible so it never appears in its own snapshot ----
    auto currentSnap = DesktopCaptureManager::CaptureMonitorScreen(m_monitorRect);
    if (currentSnap && m_desktopList.currentIndex >= 0 && m_desktopList.currentIndex < total) {
        DesktopCaptureManager::Store(m_desktopList.items[m_desktopList.currentIndex].id, currentSnap);
    }

    // ---- kick off the background composer for the other desktops ----
    if (total > 1 && currentSnap) {
        bool busy = m_composeThread && WaitForSingleObject(m_composeThread, 0) == WAIT_TIMEOUT;
        if (!busy) {
            if (m_composeThread) { CloseHandle(m_composeThread); m_composeThread = nullptr; }
            Composer::s_abort.store(false);
            auto job = std::make_unique<Composer::Job>();
            job->mon = m_monitorRect;
            job->list = m_desktopList;
            m_composeThread = Composer::Start(std::move(job));
        }
    }

    // ---- window / scene ----
    SetWindowPos(m_hwnd, HWND_TOPMOST, m_monitorRect.left, m_monitorRect.top, monW, monH,
                 SWP_NOACTIVATE);
    FindOutput();

    m_rootVisual = m_compositor.CreateContainerVisual();
    m_rootVisual.Size({ m_screenWidth, m_screenHeight });
    BuildVisuals();
    m_target.Root(m_rootVisual);

    m_liveDesktop = m_desktopList.currentIndex;
    StartLive(currentSnap.get());
    CollectAltWindows();
    BuildAltVisuals();

    m_yaw = Spring{};
    m_pitch = Spring{};
    m_zoom = Spring{};
    m_uz = Spring{};
    m_kick = Spring{}; m_pop = Spring{};
    m_bornDesktop = -1; m_bornT = 1.0f; m_fxDirty = false; m_composeRestart = false;
    m_vd = VdTask{};
    m_zoneQuietUntil = std::chrono::steady_clock::time_point{};
    m_vdCooldown = std::chrono::steady_clock::time_point{};
    m_pendingVdOp.store(0);
    m_uz.x = std::clamp(m_inUserZoom.load(), kMinUserZoom, kMaxUserZoom);
    m_zoom.x = m_cfg.zoomAnim ? 0.0f : 1.0f;
    m_phase = Phase::Drag;
    m_zoomRelease = 1.0f;
    m_needSwitch = false;
    m_switchConfirmed = false;
    m_frameCounter = 0;
    m_fpsFrames = 0;
    QueryPerformanceCounter(&m_fpsT0);
    for (auto& a : m_applied) a = 1e9f;

    QueryPerformanceCounter(&m_lastQpc);
    ApplyTransforms();
    m_applied[0] = m_yaw.x; m_applied[1] = m_pitch.x; m_applied[2] = m_zoom.x; m_applied[3] = m_uz.x;

    ShowWindow(m_hwnd, SW_SHOWNA);

    // ---- frame pacer + input hooks (both live on / feed this thread) ----
    m_pacerStop.store(false);
    m_idle.store(false);
    m_idleFrames = 0;
    m_busy = false;
    m_presentPending = false;
    m_pacerThread = CreateThread(nullptr, 0, PacerEntry, this, 0, nullptr);

    GestureController::AttachHooks();
    GestureController::ResyncMouse();

    LOG_INF(L"Scene started: %dx%d faces=%d desktops=%d refresh=%.0fHz live=%d", monW, monH, m_faceCount, total, m_monitorHz, (int)(m_liveBmp != nullptr));
    return true;
}

DWORD WINAPI CubeRenderer::PacerEntry(LPVOID p) {
    ((CubeRenderer*)p)->PacerLoop();
    return 0;
}

void CubeRenderer::PacerLoop() {
    SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_HIGHEST);
    bool useDxgi = (m_output != nullptr);
    while (!m_pacerStop.load()) {
        if (m_idle.load()) {
            // Idle: no vblank wake-ups. ~30 Hz, and Wake() ends the wait instantly.
            WaitForSingleObject(m_wakeEvent, 33);
            SetEvent(m_frameEvent);
            continue;
        }
        LARGE_INTEGER a, b;
        QueryPerformanceCounter(&a);
        bool waited = false;
        if (useDxgi && m_output) {
            if (SUCCEEDED(m_output->WaitForVBlank())) waited = true;
            else useDxgi = false;
        }
        if (!waited) {
            if (FAILED(DwmFlush())) Sleep(4);
        }
        QueryPerformanceCounter(&b);
        double ms = (double)(b.QuadPart - a.QuadPart) * 1000.0 / (double)m_qpcFreq.QuadPart;
        if (ms < 0.5) Sleep(1);   // vblank source that returns instantly (display asleep etc.)
        SetEvent(m_frameEvent);
    }
}

void CubeRenderer::EndScene() {
    GestureController::DetachHooks();
    StopLive();

    m_pacerStop.store(true);
    if (m_wakeEvent) SetEvent(m_wakeEvent);
    if (m_frameEvent) SetEvent(m_frameEvent);
    if (m_pacerThread) {
        WaitForSingleObject(m_pacerThread, INFINITE);   // see Shutdown(): never leave a thread running in the mod image
        CloseHandle(m_pacerThread);
        m_pacerThread = nullptr;
    }
    if (m_output) { m_output->Release(); m_output = nullptr; }
    if (m_dupOutput) { m_dupOutput->Release(); m_dupOutput = nullptr; }

    if (m_hwnd) ShowWindow(m_hwnd, SW_HIDE);
    RestoreTaskbarCapture();
    if (m_target && m_emptyRoot) m_target.Root(m_emptyRoot);

    m_backgroundVisual = nullptr;
    m_backdropVisual = nullptr;
    m_bgSurface = nullptr;
    m_shadowVisual = nullptr;
    m_shadowSurface = nullptr;
    m_cubeContainer = nullptr;
    m_rootVisual = nullptr;
    for (int i = 0; i < kMaxFaces; ++i) m_faces[i] = FaceVisuals{};
    m_zOrderValid = false;
    m_winVis.clear();
    m_winBrush.clear();
    m_glow = nullptr; m_label = nullptr; m_labelSurface = nullptr; m_labelBrush = nullptr;
    m_zoneL = ZoneVisual{}; m_zoneR = ZoneVisual{};
    m_toast = nullptr; m_toastSurface = nullptr; m_toastT = 0.0f;
    m_vd.active = false;
    m_alt.clear();
    m_altReady = false; m_altAttached = false; m_altShown = false; m_selMode = false; m_selT = 0.0f;

    for (auto& kv : m_bitmapCache) {
        if (kv.second.bmp) kv.second.bmp->Release();
    }
    m_bitmapCache.clear();
}

void CubeRenderer::Teardown() {
    try { EndScene(); } catch (...) {}

    Composer::s_abort.store(true);
    if (m_composeThread) {
        WaitForSingleObject(m_composeThread, INFINITE);   // see Shutdown(): never leave a thread running in the mod image
        CloseHandle(m_composeThread);
        m_composeThread = nullptr;
    }

    m_target = nullptr;
    m_emptyRoot = nullptr;
    m_graphicsDevice = nullptr;

    if (m_textFormatBadge) { m_textFormatBadge->Release(); m_textFormatBadge = nullptr; }
    if (m_dwriteFactory) { m_dwriteFactory->Release(); m_dwriteFactory = nullptr; }
    if (m_d2dDevice) { m_d2dDevice->Release(); m_d2dDevice = nullptr; }
    if (m_d2dFactory) { m_d2dFactory->Release(); m_d2dFactory = nullptr; }
    if (m_d3dDevice) { m_d3dDevice->Release(); m_d3dDevice = nullptr; }

    HWND h = m_hwnd;
    m_hwnd = nullptr;
    if (h && IsWindow(h)) DestroyWindow(h);
    // Right after the window is gone, on the thread that owns it, so this can never run while the window still exists.
    if (g_overlayClassRegistered) {
        if (!UnregisterClassW(kOverlayClassName, GetThisModuleHandle())) {
            LOG_ERR(L"UnregisterClassW failed: %lu", GetLastError());
        }
        g_overlayClassRegistered = false;
    }

    m_compositor = nullptr;
    if (m_dqController) {
        try { m_dqController.ShutdownQueueAsync(); } catch (...) {}
        m_dqController = nullptr;
    }
}

// ---------------------------------------------------------------------------
// Render loop
// ---------------------------------------------------------------------------
void CubeRenderer::RunLoop() {
    HANDLE h[1] = { m_frameEvent };
    for (;;) {
        // Waking for input messages too keeps the low-level mouse hook responsive.
        DWORD r = MsgWaitForMultipleObjectsEx(1, h, 100, QS_ALLINPUT, MWMO_INPUTAVAILABLE);

        MSG msg;
        while (PeekMessageW(&msg, nullptr, 0, 0, PM_REMOVE)) {
            TranslateMessage(&msg);
            DispatchMessageW(&msg);
        }
        if (WaitForSingleObject(m_quitEvent, 0) == WAIT_OBJECT_0) break;

        if (r == WAIT_OBJECT_0 || r == WAIT_TIMEOUT) {
            if (!Frame()) break;
            UpdateIdle();
        }
    }
}

// Power saving: after about half a second without any change the pacer drops to ~30 Hz.
// Any input, commit or change brings it straight back to the full refresh rate.
void CubeRenderer::UpdateIdle() {
    if (!m_cfg.idleSave || m_phase != Phase::Drag || m_busy || m_presentPending || m_cmd.load() != 0) {
        m_idleFrames = 0;
        if (m_idle.load()) m_idle.store(false);
    } else if (++m_idleFrames > 40) {
        m_idle.store(true);
    }
    m_busy = false;
}

float CubeRenderer::ComputeYawTarget(float rawYaw) const {
    int total = m_desktopList.TotalCount();
    if (m_faceCount <= 1) return RubberBand(rawYaw, -28.0f, 28.0f, 14.0f);
    if (m_cfg.wrap) return rawYaw;
    int cur = m_desktopList.currentIndex;
    float lo = -(float)(total - 1 - cur) * m_stepDeg;   // dragging left goes to higher desktops
    float hi = (float)cur * m_stepDeg;                  // dragging right goes to lower desktops
    return RubberBand(rawYaw, lo, hi, 35.0f);
}

bool CubeRenderer::Frame() {
    LARGE_INTEGER now;
    QueryPerformanceCounter(&now);
    float dt = (float)((double)(now.QuadPart - m_lastQpc.QuadPart) / (double)m_qpcFreq.QuadPart);

    if (m_cfg.fpsLimit > 0 && dt < (1.0f / (float)m_cfg.fpsLimit) * 0.85f) return true;
    m_lastQpc = now;
    dt = std::clamp(dt, 0.0005f, 0.05f);
    ++m_frameCounter;

    // ---- live desktop feed: newest real screen frame goes straight to the compositor ----
    if (m_liveBmp) {
        const int prevLive = m_liveDesktop;
        if (m_needSwitch && m_switchConfirmed) m_liveDesktop = m_targetDesktop;   // the real screen now shows the target
        if (prevLive != m_liveDesktop) m_applied[0] = 1e9f;
        const bool hold = (m_needSwitch && !m_switchConfirmed) || m_vd.active;    // do not film Windows mid-switch
        const bool bgDue = m_zoom.x > 0.01f && now.QuadPart >= m_bgNext;
        if (!hold && PollLive(bgDue)) {
            m_liveHasFrame = true;
            m_busy = true;
        } else if (m_presentPending && m_sc) {
            if (m_sc->Present(0, DXGI_PRESENT_DO_NOT_WAIT) != DXGI_ERROR_WAS_STILL_DRAWING) m_presentPending = false;
            m_busy = true;
        }
        if (m_texFresh && bgDue) {
            DrawLive();                                                           // small blurred background, low rate on purpose
            m_texFresh = false;
            m_bgNext = now.QuadPart + m_qpcFreq.QuadPart / (LONGLONG)std::max(1, m_cfg.bgHz);
        }
    }
    UpdateAltTab(dt);
    UpdateThumbs();
    {
        const int pendingOp = m_pendingVdOp.exchange(0);
        if (pendingOp != 0 && m_phase == Phase::Drag && !m_vd.active) StartVdOp(pendingOp);
    }
    if (m_phase == Phase::Drag) UpdateVdOp();
    if (m_vd.active) m_busy = true;

    ++m_fpsFrames;
    {
        double sec = (double)(now.QuadPart - m_fpsT0.QuadPart) / (double)m_qpcFreq.QuadPart;
        if (sec >= 2.0) {
            LOG_DBG(L"Render rate %.1f fps (monitor %.0f Hz), live frames %d", (double)m_fpsFrames / sec, m_monitorHz, m_liveFrames);
            m_fpsFrames = 0;
            m_liveFrames = 0;
            m_fpsT0 = now;
        }
    }

    const float zoomOmega = 18.0f * m_cfg.zoomSpeed;

    // User (wheel) zoom follows its target in every phase.
    m_uz.Step(std::clamp(m_inUserZoom.load(), kMinUserZoom, kMaxUserZoom), 16.0f, 1.0f, dt);
    StepFx(dt);

    auto applyIfChanged = [&]() {
        bool changed = std::fabs(m_yaw.x - m_applied[0]) > 2e-3f ||
                       std::fabs(m_pitch.x - m_applied[1]) > 2e-3f ||
                       std::fabs(m_zoom.x - m_applied[2]) > 1e-4f ||
                       std::fabs(m_uz.x - m_applied[3]) > 1e-4f || m_altDirty || m_fxDirty;
        if (changed) {
            m_busy = true;
            ApplyTransforms();
            m_altDirty = false;
            m_fxDirty = false;
            m_applied[0] = m_yaw.x; m_applied[1] = m_pitch.x; m_applied[2] = m_zoom.x; m_applied[3] = m_uz.x;
        }
    };

    // Newly composed desktop images arrive in the background: refresh one face per check.
    if ((m_frameCounter % 6) == 0) {
        if (m_composeRestart) KickComposer();
        for (int i = 0; i < m_faceCount; ++i) {
            auto& f = m_faces[i];
            int d = f.renderedDesktop;
            if (d < 0 || d >= m_desktopList.TotalCount()) continue;
            uint64_t v = DesktopCaptureManager::Version(m_desktopList.items[d].id);
            if (v != f.renderedVersion) {
                RenderFace(i, d);
                m_busy = true;
                m_applied[0] = 1e9f;   // force a transform refresh (lift / blur flags may have changed)
                break;
            }
        }
    }

    if (m_phase == Phase::Drag) {
        // Safety net: a button release that happened before the hook was attached.
        if (GestureController::GetState() == GestureState::ActiveDrag &&
            !(GetAsyncKeyState(VK_LBUTTON) & 0x8000)) {
            GestureController::OnActiveMouseUp();
        }
        int cmd = m_vd.active ? 0 : m_cmd.exchange(0);   // finish the desktop operation first
        if (cmd != 0) {
            GestureController::DetachHooks();
            BeginCommit(cmd == 2);
        }
    }

    if (m_phase == Phase::Drag) {
        float tYaw = ComputeYawTarget(m_inYaw.load());
        float tPitch = m_cfg.verticalRotation
            ? RubberBand(m_inPitch.load(), -m_cfg.maxTilt, m_cfg.maxTilt, 18.0f)
            : 0.0f;

        if (m_cfg.dragSmoothMs <= 0) {
            m_yaw.x = tYaw;     m_yaw.v = 0.0f;
            m_pitch.x = tPitch; m_pitch.v = 0.0f;
        } else {
            float om = 5.8f / ((float)m_cfg.dragSmoothMs * 0.001f);
            m_yaw.Step(tYaw, om, 1.0f, dt);
            m_pitch.Step(tPitch, om, 1.0f, dt);
        }

        if (m_cfg.zoomAnim) {
            float tZoom = std::clamp(m_inZoom.load(), 0.0f, 1.0f);
            float omZ = 5.8f / ((float)std::max(m_cfg.dragSmoothMs, 50) * 0.001f);
            m_zoom.Step(tZoom, omZ, 1.0f, dt);
        } else {
            m_zoom.x = 1.0f; m_zoom.v = 0.0f;
        }

        applyIfChanged();
        return true;
    }

    // Settle and Fade
    float omS = 24.0f * m_cfg.snapSpeed;
    float zeta = std::clamp(1.0f - 0.6f * m_cfg.bounce, 0.4f, 1.0f);
    m_yaw.Step(m_snapYaw, omS, zeta, dt);
    m_pitch.Step(0.0f, omS, std::max(zeta, 0.65f), dt);

    float yawErr = std::fabs(m_yaw.x - m_snapYaw);
    float zErr = std::max(yawErr, std::fabs(m_pitch.x)) / 30.0f;
    float zt = m_cfg.zoomAnim ? std::clamp((zErr - 0.2f) / 0.8f, 0.0f, 1.0f) : 1.0f;
    zt = std::min(zt, m_zoomRelease);
    m_zoom.Step(zt, zoomOmega, 1.0f, dt);

    auto tnow = std::chrono::steady_clock::now();

    if (m_phase == Phase::Settle) {
        UpdateSwitching();

        bool covered = m_cfg.zoomAnim ? (m_zoom.x < 0.05f) : true;
        bool aligned = yawErr < 0.6f && std::fabs(m_pitch.x) < 0.6f;
        bool switchDone = !m_needSwitch ||
            (m_switchConfirmed &&
             std::chrono::duration_cast<std::chrono::milliseconds>(tnow - m_confirmTime).count() >= m_cfg.settleMs);
        bool tooLong = std::chrono::duration_cast<std::chrono::milliseconds>(tnow - m_settleStart).count() > 5000;

        if ((covered && aligned && switchDone) || tooLong) {
            m_phase = Phase::Fade;
            m_fadeStart = tnow;
            LOG_DBG(L"Settle -> Fade");
        }
        applyIfChanged();
        return true;
    }

    // Fade
    float elapsed = (float)std::chrono::duration_cast<std::chrono::microseconds>(tnow - m_fadeStart).count() / 1000.0f;
    float t = m_cfg.fadeMs > 0 ? elapsed / (float)m_cfg.fadeMs : 1.0f;
    applyIfChanged();
    if (t >= 1.0f) {
        VDManager::SuppressSystemAnimation(false);
        if (m_rootVisual) m_rootVisual.Opacity(0.0f);
        return false;
    }
    if (m_rootVisual) m_rootVisual.Opacity(1.0f - SmoothStep(t));
    return true;
}

void CubeRenderer::BeginCommit(bool cancel) {
    m_zoomRelease = std::clamp(m_zoom.x, 0.0f, 1.0f);

    int total = m_desktopList.TotalCount();
    int cur = m_desktopList.currentIndex;

    int n = 0;   // number of steps (of m_stepDeg) the prism rotates by, positive = to the right
    if (!cancel && m_faceCount > 1) {
        float yawT = ComputeYawTarget(m_inYaw.load());
        float vel = m_cfg.flick ? m_inFlick.load() : 0.0f;
        float proj = yawT + vel * 0.16f * m_cfg.flickStrength;
        float p = proj / m_stepDeg;
        int base = (int)std::trunc(p);
        float frac = p - (float)base;
        float thr = std::min(m_cfg.switchAngle / m_stepDeg, 0.45f);
        if (std::fabs(frac) > thr) base += (frac > 0.0f ? 1 : -1);
        n = base;
        // A quick, short flick always moves one face, even if the cube was barely turned.
        if (m_cfg.flick && n == 0 && std::fabs(vel) > 240.0f / std::max(m_cfg.flickStrength, 0.25f)) n = vel > 0.0f ? 1 : -1;
        n = std::clamp(n, -m_faceCount, m_faceCount);

        if (total <= 1) {
            n = 0;
        } else if (!m_cfg.wrap) {
            int d = std::clamp(-n, -cur, total - 1 - cur);
            n = -d;
        }
    }

    // Window switcher: releasing activates the selected window and stays on this desktop.
    if (!cancel && m_selMode && m_selIdx >= 0 && m_selIdx < (int)m_alt.size()) {
        n = 0;
        ActivateWindowNow(m_alt[m_selIdx].hwnd);
    }

    m_snapYaw = (float)n * m_stepDeg;

    // Rotating the prism to the right by one face brings the PREVIOUS desktop to the front.
    int target = cur;
    if (n != 0 && total > 0) {
        int d = -n;
        if (m_cfg.wrap) target = (((cur + d) % total) + total) % total;
        else target = std::clamp(cur + d, 0, total - 1);
    }

    m_targetDesktop = target;
    m_needSwitch = (target != cur);
    m_switchConfirmed = false;

    auto tnow = std::chrono::steady_clock::now();
    m_settleStart = tnow;

    if (m_needSwitch) {
        int delta = target - cur;
        m_stepDir = delta > 0 ? 1 : -1;
        m_stepsLeft = std::abs(delta);
        m_stepIntervalMs = m_cfg.suppressSysAnim ? 45 : 120;
        m_switchTimeoutMs = 800 + 350 * m_stepsLeft;
        // Seamless Window Manager has a hotkey for desktops 1 to 9. Anything else, or SWM missing, uses the Windows shortcut.
        m_swmMode = m_cfg.useSwm && target >= 0 && target <= 8 && VDManager::SwmBridge::IsAvailable();
        m_swmSent = false;
        m_swmStartIdx = cur;
        if (m_swmMode) {
            m_stepsLeft = 0;
            m_switchTimeoutMs = 2600 + 350 * std::abs(delta);
        }
        m_switchStart = tnow;
        m_nextStep = tnow;
        m_lastStepSent = tnow;
        m_nextPoll = tnow;
        if (m_cfg.suppressSysAnim) VDManager::SuppressSystemAnimation(true);
    }

    LOG_INF(L"Commit: cancel=%d steps=%d cur=%d target=%d switch=%d", (int)cancel, n, cur, target, (int)m_needSwitch);
    m_phase = Phase::Settle;
}

// The desktop switch runs UNDER the opaque overlay, so the slide animation is never seen.
void CubeRenderer::UpdateSwitching() {
    if (!m_needSwitch || m_switchConfirmed) return;
    auto now = std::chrono::steady_clock::now();
    const auto msSince = [&](std::chrono::steady_clock::time_point t0) {
        return (int)std::chrono::duration_cast<std::chrono::milliseconds>(now - t0).count();
    };

    // Seamless Window Manager path: press its hotkey once, then watch the registry. If the desktop has not moved at all
    // after 900 ms (the mod is off or its hotkey is taken), step with the Windows shortcut instead.
    if (m_swmMode) {
        int rc = -1;
        const bool haveIdx = VDManager::ReadCurrentIndex(rc);
        bool fallback = false;
        if (!m_swmSent) {
            if (haveIdx) m_swmStartIdx = rc;
            if (VDManager::SwmBridge::SendDesktopHotkey(m_targetDesktop)) {
                m_swmSent = true;
                m_swmSentAt = now;
                m_lastStepSent = now;
                LOG_INF(L"Switch to desktop %d through Seamless Window Manager", m_targetDesktop + 1);
            } else {
                fallback = true;
            }
        } else if (haveIdx && rc == m_swmStartIdx && msSince(m_swmSentAt) > 900) {
            fallback = true;
        }
        if (fallback) {
            LOG_INF(L"Seamless Window Manager did not switch, using the Windows shortcut");
            m_swmMode = false;
            int from = haveIdx ? rc : m_swmStartIdx;
            int delta = m_targetDesktop - from;
            m_stepDir = delta > 0 ? 1 : -1;
            m_stepsLeft = std::abs(delta);
            m_nextStep = now;
            m_switchTimeoutMs += 800 + 350 * m_stepsLeft;
        }
    }

    if (m_stepsLeft > 0 && now >= m_nextStep) {
        VDManager::SendSwitchStep(m_stepDir);
        --m_stepsLeft;
        m_lastStepSent = now;
        m_nextStep = now + std::chrono::milliseconds(m_stepIntervalMs);
    }

    if (m_stepsLeft == 0 && now >= m_nextPoll) {
        m_nextPoll = now + std::chrono::milliseconds(12);
        int idx = -1;
        if (VDManager::ReadCurrentIndex(idx)) {
            if (idx == m_targetDesktop) {
                m_switchConfirmed = true;
                m_confirmTime = now;
                LOG_DBG(L"Switch confirmed (registry)");
            }
        } else if (std::chrono::duration_cast<std::chrono::milliseconds>(now - m_lastStepSent).count() > 160) {
            m_switchConfirmed = true;
            m_confirmTime = now;
            LOG_DBG(L"Switch assumed (no registry value)");
        }
    }

    if (!m_switchConfirmed &&
        std::chrono::duration_cast<std::chrono::milliseconds>(now - m_switchStart).count() > m_switchTimeoutMs) {
        m_switchConfirmed = true;
        m_confirmTime = now;
        LOG_INF(L"Switch timed out, continuing");
    }
}

int CubeRenderer::DesktopForOffset(int k) const {
    int total = m_desktopList.TotalCount();
    if (total <= 0) return -1;
    int idx = m_desktopList.currentIndex + k;
    if (m_cfg.wrap) {
        idx %= total;
        if (idx < 0) idx += total;
        return idx;
    }
    return (idx >= 0 && idx < total) ? idx : -1;
}

// ---------------------------------------------------------------------------
// Per-frame scene update
// ---------------------------------------------------------------------------
void CubeRenderer::ApplyTransforms() {
    if (!m_rootVisual || !m_cubeContainer) return;

    const int F = m_faceCount;
    const float W = m_faceWidth, H = m_faceHeight;
    const float D = m_D;
    const float d = m_cfg.perspective;
    const float zoom = std::clamp(m_zoom.x, 0.0f, 1.2f);
    const float yaw = m_yaw.x + m_kick.x;
    const float pitch = m_pitch.x;
    const float yawR = yaw * kPi / 180.0f;
    const float pitchR = pitch * kPi / 180.0f;
    const float cx = m_screenWidth * 0.5f, cy = m_screenHeight * 0.5f;

    // zoom 0: the front face exactly fills the screen. zoom 1: the open prism at the user's wheel zoom.
    int liveFace = -1;
    bool liveBack = false;

    const float sf = std::max(m_screenWidth / W, 1.0f);
    const float uz = std::clamp(m_uz.x * (1.0f + m_pop.x), 0.25f, 1.9f);
    const float sNow = std::max(sf + (uz - sf) * zoom, 0.2f);
    const float frontZ = d * (1.0f - 1.0f / sNow);

    Mat4 view = Mat4::RotationY(yawR) * Mat4::RotationX(pitchR) *
                Mat4::Translation(0.0f, 0.0f, -D + frontZ) *
                Mat4::Perspective(d) * Mat4::Translation(cx, cy, 0.0f);

    const float cp = std::cos(pitchR), sp = std::sin(pitchR);
    const float bright = (float)m_cfg.brightness / 100.0f;
    auto S01 = [](float t) { return SmoothStep(t); };

    float depthOut = 0.0f;
    auto facingOf = [&](Vec3 c0, Vec3 n0, float yawTotalR, float& outFacing) -> bool {
        float cs = std::cos(yawTotalR), sn = std::sin(yawTotalR);
        auto rot = [&](Vec3 v) -> Vec3 {
            float x1 = v.x * cs + v.z * sn;
            float z1 = -v.x * sn + v.z * cs;
            float y2 = v.y * cp + z1 * sp;
            float z2 = -v.y * sp + z1 * cp;
            return Vec3{ x1, y2, z2 };
        };
        Vec3 c = rot(c0);
        Vec3 n = rot(n0);
        c.z += -D + frontZ;
        depthOut = c.z;
        Vec3 v{ -c.x, -c.y, d - c.z };
        if (v.z < 5.0f) return false;
        float len = std::sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
        if (len < 1e-3f) return false;
        outFacing = (n.x * v.x + n.y * v.y + n.z * v.z) / len;
        return outFacing > 0.02f;
    };

    const float nc = -yaw / m_stepDeg;
    float faceDepth[kMaxFaces] = { 0, 0, 0, 0, 0, 0 };
    Mat4 faceMs[kMaxFaces] = {};
    bool faceBack[kMaxFaces] = {};
    float faceFac[kMaxFaces] = {};
    float faceA[kMaxFaces] = {};
    auto setOp = [](auto& vis, float& cache, float v) {
        if (std::fabs(v - cache) > 0.0015f || (v == 0.0f) != (cache == 0.0f)) { vis.Opacity(v); cache = v; }
    };
    auto setVis = [](auto& vis, signed char& cache, bool v) {
        const signed char n = v ? 1 : 0;
        if (cache != n) { vis.IsVisible(v); cache = n; }
    };

    for (int i = 0; i < F; ++i) {
        auto& f = m_faces[i];
        if (!f.container) continue;

        // Faces that swing behind the prism are re-mapped so every desktop stays reachable.
        int q = (int)std::lround((nc - (float)i) / (float)F);
        int k = i + F * q;
        int dIdx = DesktopForOffset(k);
        if (dIdx != f.renderedDesktop) RenderFace(i, dIdx);

        // The face that shows the desktop you are on samples the live swap chain directly.
        {
            const bool wantLive = m_liveSurface && m_liveHasFrame && f.renderedDesktop == m_liveDesktop;
            if (wantLive) {
                if (!f.liveBrush) {
                    f.liveBrush = m_compositor.CreateSurfaceBrush(m_liveSurface);
                    f.liveBrush.Stretch(CompositionStretch::Fill);
                }
                if (!f.usingLive) { f.background.Brush(f.liveBrush); f.usingLive = true; }
            } else if (f.usingLive && f.brush) {
                f.background.Brush(f.brush);
                f.usingLive = false;
            }
        }

        float faceDeg = (float)i * m_stepDeg;
        float fac = 0.0f;
        depthOut = 0.0f;
        facingOf(Vec3{ 0.0f, 0.0f, D }, Vec3{ 0.0f, 0.0f, 1.0f }, (faceDeg + yaw) * kPi / 180.0f, fac);
        faceDepth[i] = depthOut;

        bool backSide = fac <= 0.02f;
        if (f.usingLive && liveFace < 0) { liveFace = i; liveBack = backSide; }
        Mat4 baseLocal = Mat4::Translation(-W * 0.5f, -H * 0.5f, 0.0f);
        if (backSide) {
            Mat4 flip = Mat4::Identity();
            flip.m[0][0] = -1.0f;
            baseLocal = baseLocal * flip;
        }
        Mat4 rotFace = Mat4::RotationY(faceDeg * kPi / 180.0f);
        const Mat4 faceM = baseLocal * Mat4::Translation(0.0f, 0.0f, D) * rotFace * view;
        f.container.TransformMatrix(faceM.ToWinRT());
        faceMs[i] = faceM;
        faceBack[i] = backSide;
        faceFac[i] = fac;

        float a;
        if (backSide) {
            a = m_cfg.backOpacity;
        } else {
            a = m_cfg.backOpacity + (m_cfg.sideOpacity - m_cfg.backOpacity) * S01(fac / 0.30f);
            a += (m_cfg.frontOpacity - m_cfg.sideOpacity) * S01((fac - 0.55f) / 0.43f);
        }
        a = std::clamp(a, 0.0f, 1.0f);
        if (dIdx == m_bornDesktop && m_bornT < 1.0f) a *= SmoothStep(m_bornT);   // new desktop fades in
        // Opacity lives on the sprites, not on the container: a group opacity would force an
        // extra full-size offscreen pass for every translucent face.
        faceA[i] = a;
        setOp(f.background, f.cBg, a);
        setVis(f.container, f.cVisContainer, a > 0.02f);

        float facP = std::max(fac, 0.0f);
        float shadeOp = std::clamp(bright * 0.55f * (1.0f - facP), 0.0f, 0.85f);
        if (f.usingLive) shadeOp = std::max(shadeOp, 0.50f * m_selT);   // dim the desktop under the raised windows
        if (f.rim) {
            const float rimOp = a * 0.28f * (0.4f + 0.6f * facP) * std::min(zoom, 1.0f);
            setOp(f.rim, f.cRim, rimOp);
            setVis(f.rim, f.cVisRim, rimOp > 0.01f);   // hidden rims cost no GPU fill
        }
        setOp(f.shade, f.cShade, shadeOp * a);
        setVis(f.shade, f.cVisShade, shadeOp * a > 0.01f);

        if (f.layer) {
            const bool showBadge = m_cfg.labels && a > 0.01f;
            setVis(f.layer, f.cVisLayer, showBadge);
            if (showBadge) {
                Mat4 badgeLocal = Mat4::Translation(-kBadgeW * 0.5f, -H * 0.5f + 10.0f, 0.0f);
                if (backSide) {
                    Mat4 fl = Mat4::Identity();
                    fl.m[0][0] = -1.0f;
                    badgeLocal = badgeLocal * fl;
                }
                f.layer.TransformMatrix((badgeLocal * Mat4::Translation(0.0f, 0.0f, D) * rotFace * view).ToWinRT());
                setOp(f.layer, f.cLayer, a * (0.75f + 0.25f * facP));
            }
        }
    }

    // ---- rounded corners, hover and the two border rings ----
    {
        int frontIdx = -1;
        float bestFac = 0.02f;
        for (int i = 0; i < F; ++i) {
            if (!m_faces[i].container || faceBack[i] || faceA[i] <= 0.02f) continue;
            if (faceFac[i] > bestFac) { bestFac = faceFac[i]; frontIdx = i; }
        }

        // Hovered face: project the four corners to the screen and test the pointer against the quad.
        int hoverIdx = -1;
        POINT hc{};
        const LONG monW = m_monitorRect.right - m_monitorRect.left;
        const LONG monH = m_monitorRect.bottom - m_monitorRect.top;
        if (m_phase == Phase::Drag && monW > 0 && monH > 0 && ReadCursorPos(&hc)) {
            const float px = (float)(hc.x - m_monitorRect.left) * m_screenWidth / (float)monW;
            const float py = (float)(hc.y - m_monitorRect.top) * m_screenHeight / (float)monH;
            float bestDepth = -1e30f;
            const float qxs[4] = { 0.0f, W, W, 0.0f };
            const float qys[4] = { 0.0f, 0.0f, H, H };
            for (int i = 0; i < F; ++i) {
                if (!m_faces[i].container || faceBack[i] || faceA[i] <= 0.02f) continue;
                const Mat4& M = faceMs[i];
                float sx[4], sy[4];
                bool okq = true;
                for (int k = 0; k < 4 && okq; ++k) {
                    const float w = qxs[k] * M.m[0][3] + qys[k] * M.m[1][3] + M.m[3][3];
                    if (w < 1e-3f) { okq = false; break; }
                    sx[k] = (qxs[k] * M.m[0][0] + qys[k] * M.m[1][0] + M.m[3][0]) / w;
                    sy[k] = (qxs[k] * M.m[0][1] + qys[k] * M.m[1][1] + M.m[3][1]) / w;
                }
                if (!okq) continue;
                bool pos = false, neg = false;
                for (int k = 0; k < 4; ++k) {
                    const int j = (k + 1) & 3;
                    const float cr = (sx[j] - sx[k]) * (py - sy[k]) - (sy[j] - sy[k]) * (px - sx[k]);
                    if (cr > 0.0f) pos = true; else if (cr < 0.0f) neg = true;
                }
                if (!(pos && neg) && faceDepth[i] > bestDepth) { bestDepth = faceDepth[i]; hoverIdx = i; }
            }
        }

        const float zf = S01(std::min(zoom, 1.0f));
        const float bwF = std::clamp(m_cfg.borderWidth, 0.0f, 8.0f) / sNow;
        const float rf = std::clamp(m_cfg.cornerRadius, 0.0f, 48.0f) * zf / sNow;
        for (int i = 0; i < F; ++i) {
            auto& f = m_faces[i];
            if (!f.container || !f.clip) continue;
            const bool hl = (i == frontIdx && m_cfg.borderMode != 1) || (i == hoverIdx && m_cfg.borderMode != 2);
            f.bTarget = hl ? 1.0f : 0.0f;
            if (std::fabs(rf - f.cRad) > 0.05f || std::fabs(bwF - f.cBw) > 0.005f) {
                UpdateFaceShape(f, rf, bwF);
                f.cRad = rf;
                f.cBw = bwF;
            }
            const bool ringOn = bwF > 0.001f && faceA[i] > 0.02f && zf > 0.01f;
            const float restOp = ringOn ? faceA[i] * zf : 0.0f;
            const float actOp = ringOn ? faceA[i] * zf * S01(f.bAmt) : 0.0f;
            setOp(f.borderRest, f.cBr, restOp);
            setVis(f.borderRest, f.cVisBr, restOp > 0.01f);
            setOp(f.borderAct, f.cBa, actOp);
            setVis(f.borderAct, f.cVisBa, actOp > 0.01f);
        }
    }

    // Composition does not depth sort, so keep the child order far -> near.
    {
        int order[kMaxFaces];
        for (int i = 0; i < F; ++i) order[i] = i;
        std::sort(order, order + F, [&](int a, int b) { return faceDepth[a] < faceDepth[b]; });
        bool same = m_zOrderValid;
        for (int k2 = 0; k2 < F && same; ++k2) if (order[k2] != m_zOrder[k2]) same = false;
        if (!same) {
            auto children = m_cubeContainer.Children();
            children.RemoveAll();
            m_altAttached = false;
            for (int k2 = 0; k2 < F; ++k2) {
                m_zOrder[k2] = order[k2];
                if (m_faces[order[k2]].container) children.InsertAtTop(m_faces[order[k2]].container);
                if (m_faces[order[k2]].layer) children.InsertAtTop(m_faces[order[k2]].layer);
            }
            m_zOrderValid = true;
        }
    }

    if (m_selT > 0.002f && liveFace >= 0 && !liveBack && m_liveSurface && m_altReady) {
        LayoutAlt(view, (float)liveFace * m_stepDeg, SmoothStep(std::min(zoom, 1.0f) / 0.4f));
    } else {
        HideAlt();
    }

    float z1 = std::min(zoom, 1.0f);
    if (m_backgroundVisual) {
        float s = 1.0f + 0.08f * z1;
        float px = 0.0f, py = 0.0f;
        if (m_cfg.parallax) {
            px = -std::sin(yawR) * 26.0f * z1;
            py = -std::sin(pitchR) * 20.0f * z1;
        }
        m_backgroundVisual.Scale({ s, s, 1.0f });
        m_backgroundVisual.Offset({ px, py, 0.0f });
    }

    if (m_shadowVisual) {
        float scaleF = d / std::max(d - frontZ, 1.0f);
        float sy = cy + (H * 0.5f + 34.0f) * scaleF;
        float tiltFade = std::clamp(1.0f - std::fabs(pitch) / 40.0f, 0.0f, 1.0f);
        m_shadowVisual.Scale({ scaleF, scaleF, 1.0f });
        m_shadowVisual.Offset({ cx - m_shadowW * 0.5f, sy - m_shadowH * 0.5f, 0.0f });
        m_shadowVisual.Opacity(z1 * tiltFade * 0.9f);
    }
}

// ============================================================================
// MODULE 4: GestureController
// ============================================================================
namespace GestureController {

    static std::atomic<GestureState> s_state{ GestureState::Idle };
    static POINT s_startPoint{};
    static POINT s_activationPoint{};
    static POINT s_prevMousePoint{};
    static float s_yaw = 0.0f;
    static float s_pitch = 0.0f;
    static bool s_vUnlocked = false;
    static bool s_open = false;
    static float s_prog = 0.0f;
    static float s_userZoom = 1.0f;
    static int s_inwardSign = -1;
    static DWORD s_openTick = 0;
    static float s_flickVel = 0.0f;
    static DWORD s_lastMoveTick = 0;
    struct YawSample { DWORD t; float yaw; };
    static YawSample s_samples[24];
    static int s_sampleN = 0, s_sampleHead = 0;
    static HWND s_anchorTaskbar = nullptr;

    static HHOOK s_hKeyboardHook = nullptr;
    static HHOOK s_hMouseHook = nullptr;
    // No destructor at process exit (it would release COM objects during loader-lock shutdown). Reset in Shutdown().
    [[clang::no_destroy]] static com_ptr<IUIAutomation> s_pUIAutomation;
    static constexpr UINT_PTR TIMER_ARMING_CHECK = 1002;

    void OnActiveMouseMove(POINT pt, DWORD tick);

    GestureState GetState() { return s_state.load(); }

    static bool InitUIAutomation() {
        if (!s_pUIAutomation) {
            CoCreateInstance(CLSID_CUIAutomation, nullptr, CLSCTX_INPROC_SERVER,
                             IID_IUIAutomation, s_pUIAutomation.put_void());
        }
        return s_pUIAutomation != nullptr;
    }

    static bool IsTaskbarClass(const WCHAR* cls) {
        // Only the real taskbar windows. The generic XAML island classes (InputSite, DesktopWindowContentBridge)
        // are shared with Task View, Alt+Tab, Snap and others and must not count as the taskbar.
        return _wcsicmp(cls, L"Shell_TrayWnd") == 0 ||
               _wcsicmp(cls, L"Shell_SecondaryTrayWnd") == 0;
    }

    static bool WindowChainIsTaskbar(HWND h) {
        while (h) {
            WCHAR cls[128]{};
            GetClassNameW(h, cls, ARRAYSIZE(cls));
            if (IsTaskbarClass(cls)) return true;
            HWND parent = GetParent(h);
            if (!parent || parent == h) break;
            h = parent;
        }
        return false;
    }

    static bool IsEmptyTaskbarSpace(HWND hWndOrigin, POINT pt) {
        HWND hTarget = WindowFromPoint(pt);
        HWND hCheck = hTarget ? hTarget : hWndOrigin;
        if (!hCheck) return false;

        bool isTaskbar = WindowChainIsTaskbar(hCheck) || (hWndOrigin && WindowChainIsTaskbar(hWndOrigin));
        if (!isTaskbar) {
            LOG_DBG(L"Rejected: 0x%p is not the taskbar", hCheck);
            return false;
        }

        HWND hRoot = GetAncestor(hCheck, GA_ROOT);
        HWND hTaskbar = hRoot ? hRoot : hCheck;

        HWND hTray = FindWindowExW(hTaskbar, nullptr, L"TrayNotifyWnd", nullptr);
        if (hTray && IsWindowVisible(hTray)) {
            RECT rc{};
            GetWindowRect(hTray, &rc);
            if (PtInRect(&rc, pt)) return false;
        }

        HWND hStart = FindWindowExW(hTaskbar, nullptr, L"Start", nullptr);
        if (hStart && IsWindowVisible(hStart)) {
            RECT rc{};
            GetWindowRect(hStart, &rc);
            if (PtInRect(&rc, pt)) return false;
        }

        HWND hMenu = FindWindowW(L"#32768", nullptr);
        if (hMenu && IsWindowVisible(hMenu)) return false;

        if (InitUIAutomation()) {
            com_ptr<IUIAutomationElement> element;
            if (SUCCEEDED(s_pUIAutomation->ElementFromPoint(pt, element.put())) && element) {
                BSTR bstr = nullptr;
                element->get_CurrentClassName(&bstr);
                std::wstring cn = bstr ? bstr : L"";
                if (bstr) SysFreeString(bstr);

                if (cn == L"Taskbar.TaskListButtonAutomationPeer" ||
                    cn == L"Taskbar.SearchBoxButtonAutomationPeer" ||
                    cn == L"Taskbar.TaskViewButtonAutomationPeer" ||
                    cn == L"Taskbar.WidgetsButtonAutomationPeer" ||
                    cn == L"Taskbar.ShowDesktopButtonAutomationPeer" ||
                    cn == L"Start" || cn == L"StartButton" ||
                    cn.find(L"NotifyIcon") != std::wstring::npos ||
                    cn.find(L"Clock") != std::wstring::npos) {
                    LOG_DBG(L"Rejected: UIA class %s", cn.c_str());
                    return false;
                }
            }
        }

        LOG_DBG(L"Taskbar hit accepted at (%ld, %ld)", pt.x, pt.y);
        return true;
    }

    // ---- auto-hide taskbar: hide it again after the gesture so it is ready for the next one ----
    struct FocusSearch { HWND found = nullptr; };

    static BOOL CALLBACK EnumFocusTarget(HWND h, LPARAM lp) {
        FocusSearch* fs = (FocusSearch*)lp;
        if (!IsWindowVisible(h) || IsIconic(h)) return TRUE;
        LONG ex = GetWindowLongW(h, GWL_EXSTYLE);
        if (ex & (WS_EX_TOOLWINDOW | WS_EX_NOACTIVATE)) return TRUE;
        DWORD cloaked = 0;
        DwmGetWindowAttribute(h, DWMWA_CLOAKED, &cloaked, sizeof(cloaked));
        if (cloaked != 0) return TRUE;
        WCHAR cls[128]{};
        GetClassNameW(h, cls, ARRAYSIZE(cls));
        if (IsTaskbarClass(cls) || _wcsicmp(cls, L"Progman") == 0 || _wcsicmp(cls, L"WorkerW") == 0 ||
            _wcsicmp(cls, L"SeamlessCompizCubeOverlayWindow") == 0) return TRUE;
        WCHAR title[8]{};
        if (GetWindowTextW(h, title, ARRAYSIZE(title)) == 0) return TRUE;
        if (!VDManager::IsWindowOnCurrentDesktop(h)) return TRUE;
        fs->found = h;
        return FALSE;
    }

    static void RehideTaskbar() {
        if (!g_settings.autoHideFix) return;
        APPBARDATA abd{};
        abd.cbSize = sizeof(abd);
        UINT_PTR st = SHAppBarMessage(ABM_GETSTATE, &abd);
        if (!(st & ABS_AUTOHIDE)) return;

        Sleep(60);

        HWND tray = FindWindowW(L"Shell_TrayWnd", nullptr);
        POINT pt{};
        GetCursorPos(&pt);
        if (tray) {
            RECT rc{};
            if (GetWindowRect(tray, &rc) && PtInRect(&rc, pt)) return;   // mouse is on it, leave it
        }

        // An auto-hide taskbar stays up while it owns the focus (we clicked it to start the gesture).
        HWND fg = GetForegroundWindow();
        bool taskbarHasFocus = false;
        if (!fg) {
            taskbarHasFocus = true;
        } else {
            WCHAR cls[128]{};
            GetClassNameW(fg, cls, ARRAYSIZE(cls));
            taskbarHasFocus = IsTaskbarClass(cls) || _wcsicmp(cls, L"Windows.UI.Core.CoreWindow") == 0;
        }
        if (!taskbarHasFocus) return;

        FocusSearch fs;
        EnumWindows(EnumFocusTarget, (LPARAM)&fs);
        HWND target = fs.found ? fs.found : GetShellWindow();
        if (target) {
            SetForegroundWindow(target);
            LOG_DBG(L"Re-hide taskbar: focus moved to 0x%p", target);
        }
    }

    static void CancelArming() {
        if (s_state.load() == GestureState::Arming) {
            if (s_anchorTaskbar && IsWindow(s_anchorTaskbar)) KillTimer(s_anchorTaskbar, TIMER_ARMING_CHECK);
            s_state.store(GestureState::Idle);
            LOG_INF(L"ARMING cancelled -> IDLE");
        }
    }

    static void ActivateCube(POINT pt) {
        if (s_state.load() != GestureState::Arming) return;
        if (g_unloading.load()) { CancelArming(); return; }

        if (s_anchorTaskbar && IsWindow(s_anchorTaskbar)) KillTimer(s_anchorTaskbar, TIMER_ARMING_CHECK);

        s_state.store(GestureState::ActiveDrag);
        s_activationPoint = pt;
        s_prevMousePoint = pt;
        s_yaw = 0.0f;
        s_pitch = 0.0f;
        s_vUnlocked = false;
        s_open = false;
        s_prog = 0.0f;
        s_openTick = GetTickCount();
        s_flickVel = 0.0f;
        s_lastMoveTick = s_openTick;
        s_userZoom = g_settings.rememberZoom ? std::clamp(g_userZoom, kMinUserZoom, kMaxUserZoom) : 1.0f;
        s_sampleN = 0; s_sampleHead = 0;
        {
            RECT rcBar{};
            if (s_anchorTaskbar && IsWindow(s_anchorTaskbar)) GetWindowRect(s_anchorTaskbar, &rcBar);
            s_inwardSign = (rcBar.top > 100) ? -1 : 1;   // bottom taskbar: up is inward (dy < 0)
        }
        LOG_INF(L"ARMING -> ACTIVE_DRAG at (%ld, %ld)", pt.x, pt.y);

        // Asynchronous: the render thread builds the scene and attaches the input hooks itself.
        if (!CubeRenderer::Instance().Start(pt, s_userZoom)) {
            LOG_ERR(L"Failed to start cube overlay");
            s_state.store(GestureState::Idle);
        }
    }

    bool OnMouseDown(HWND hWnd, POINT pt) {
        if (g_unloading.load() || !g_renderer) return false;
        if (s_state.load() != GestureState::Idle || CubeRenderer::Instance().IsActive()) return false;

        if (IsEmptyTaskbarSpace(hWnd, pt)) {
            s_state.store(GestureState::Arming);
            s_startPoint = pt;
            s_prevMousePoint = pt;
            s_anchorTaskbar = hWnd;
            SetTimer(hWnd, TIMER_ARMING_CHECK, 8, nullptr);
            CubeRenderer::Instance().Prewarm();   // devices are ready by the time the drag threshold is crossed
            LOG_INF(L"IDLE -> ARMING at (%ld, %ld)", pt.x, pt.y);
            return true;
        }
        return false;
    }

    static int GetInwardDragDistance(POINT pt) {
        RECT rcBar{};
        if (s_anchorTaskbar && IsWindow(s_anchorTaskbar)) GetWindowRect(s_anchorTaskbar, &rcBar);
        return (rcBar.top > 100) ? (s_startPoint.y - pt.y) : (pt.y - s_startPoint.y);
    }

    void OnArmingMouseMove(POINT pt) {
        if (s_state.load() != GestureState::Arming) return;
        if (!(GetAsyncKeyState(VK_LBUTTON) & 0x8000)) { CancelArming(); return; }
        if (GetInwardDragDistance(pt) >= g_settings.activationThreshold) ActivateCube(pt);
    }

    void OnArmingTimerTick() {
        if (s_state.load() != GestureState::Arming) {
            if (s_anchorTaskbar && IsWindow(s_anchorTaskbar)) KillTimer(s_anchorTaskbar, TIMER_ARMING_CHECK);
            return;
        }
        if (!(GetAsyncKeyState(VK_LBUTTON) & 0x8000)) { CancelArming(); return; }

        POINT pt{};
        GetCursorPos(&pt);
        if (GetInwardDragDistance(pt) >= g_settings.activationThreshold) ActivateCube(pt);
    }

    void OnArmingMouseUp() {
        if (s_state.load() == GestureState::Arming) CancelArming();
    }

    // Called on the render thread right after the hooks are attached: catch up with where
    // the mouse is now, so the first frame does not jump.
    void ResyncMouse() {
        POINT cur{};
        GetCursorPos(&cur);
        s_prevMousePoint = cur;
        s_lastMoveTick = GetTickCount();
        s_openTick = s_lastMoveTick;

        if (g_settings.zoomAnim) {
            float prog = (float)(s_inwardSign * (cur.y - s_activationPoint.y)) / g_settings.shrinkDist;
            s_prog = std::clamp(prog, 0.0f, 1.0f);
            if (s_prog >= 0.999f) { s_prog = 1.0f; s_open = true; }
        } else {
            s_prog = 1.0f;
            s_open = true;
        }
        CubeRenderer::Instance().SubmitInput(s_yaw, s_pitch, s_prog);
    }

    void OnActiveMouseMove(POINT pt, DWORD tick) {
        if (s_state.load() != GestureState::ActiveDrag) return;

        int dx = pt.x - s_prevMousePoint.x;
        int dy = pt.y - s_prevMousePoint.y;
        s_prevMousePoint = pt;
        if (dx == 0 && dy == 0) return;

        // Stage 1: dragging inward shrinks the desktop gradually (and reverses if you drag back).
        if (!s_open) {
            if (g_settings.zoomAnim) {
                s_prog = std::clamp(s_prog + (float)(s_inwardSign * dy) / g_settings.shrinkDist, 0.0f, 1.0f);
                if (s_prog >= 0.999f) { s_prog = 1.0f; s_open = true; s_openTick = tick; }
            } else {
                s_prog = 1.0f; s_open = true; s_openTick = tick;
            }
        }
        float gate = std::clamp((s_prog - 0.35f) / 0.5f, 0.0f, 1.0f);
        gate = gate * gate * (3.0f - 2.0f * gate);

        float dYaw = (float)dx * g_settings.hSens * (g_settings.invertH ? -1.0f : 1.0f) * gate;
        float dPitch = (float)dy * g_settings.vSens * (g_settings.invertV ? -1.0f : 1.0f);
        s_yaw += dYaw;
        if (s_open && g_settings.verticalRotation) {
            if (!s_vUnlocked) {
                if (!g_settings.horizFirst || std::fabs(s_yaw) > 6.0f ||
                    (tick - s_openTick) >= (DWORD)g_settings.vUnlockMs) {
                    s_vUnlocked = true;
                }
            } else {
                s_pitch += dPitch;
            }
        }

        // Flick speed = yaw travelled over the last ~100 ms (stable even with 1000 Hz mice).
        s_samples[s_sampleHead] = { tick, s_yaw };
        s_sampleHead = (s_sampleHead + 1) % 24;
        if (s_sampleN < 24) ++s_sampleN;
        {
            float v = 0.0f;
            for (int k = 2; k <= s_sampleN; ++k) {
                const YawSample& o = s_samples[(s_sampleHead - k + 48) % 24];
                DWORD age = tick - o.t;
                if (age > 100) break;
                if (age >= 16) v = (s_yaw - o.yaw) / (float)age * 1000.0f;
            }
            s_flickVel = std::clamp(v, -3500.0f, 3500.0f);
        }
        s_lastMoveTick = tick;

        CubeRenderer::Instance().SubmitInput(s_yaw, s_pitch, s_prog);
    }

    static void OnWheelEvent(int delta) {
        if (g_settings.wheelZoom) {
            // Scroll up = closer. Multiplicative, so every notch feels the same at any size; high-res wheels give fractions of a notch.
            float notches = (float)delta / 120.0f;
            s_userZoom = std::clamp(s_userZoom * std::pow(1.0f + g_settings.wheelStep, notches), kMinUserZoom, kMaxUserZoom);
            if (g_settings.rememberZoom) g_userZoom = s_userZoom;
            CubeRenderer::Instance().SubmitUserZoom(s_userZoom);
        } else if (g_settings.altTab) {
            int notches = std::max(1, std::abs(delta) / 120);
            CubeRenderer::Instance().SubmitWheelSelect(delta > 0 ? -notches : notches);
        }
    }

    void OnActiveMouseUp() {
        if (s_state.load() != GestureState::ActiveDrag) return;

        float vel = (GetTickCount() - s_lastMoveTick < 90) ? s_flickVel : 0.0f;
        LOG_INF(L"ACTIVE_DRAG -> COMMITTING yaw=%.2f pitch=%.2f flick=%.1f", s_yaw, s_pitch, vel);
        s_state.store(GestureState::Committing);
        CubeRenderer::Instance().Commit(vel);   // the render thread detaches the hooks on its next frame
    }

    void OnSnapCompleted() {
        s_state.store(GestureState::Idle);
        LOG_INF(L"Gesture finished -> IDLE");
        RehideTaskbar();
    }

    void OnCancel() {
        GestureState st = s_state.load();
        if (st == GestureState::Arming) {
            CancelArming();
        } else if (st == GestureState::ActiveDrag) {
            LOG_INF(L"Escape: cancelling cube gesture");
            s_state.store(GestureState::Committing);
            CubeRenderer::Instance().Cancel();
        }
    }

    static bool s_swallowRUp = false;

    void RescaleYaw(float k) {
        s_yaw *= k;
        s_sampleN = 0; s_sampleHead = 0;
        s_flickVel = 0.0f;
        CubeRenderer::Instance().SubmitInput(s_yaw, s_pitch, s_prog);
    }

    static LRESULT CALLBACK LowLevelMouseProc(int nCode, WPARAM wParam, LPARAM lParam) {
        if (nCode == HC_ACTION && wParam == WM_RBUTTONUP && s_swallowRUp) {
            s_swallowRUp = false;
            return 1;
        }
        if (nCode == HC_ACTION && s_state.load() == GestureState::ActiveDrag) {
            MSLLHOOKSTRUCT* ms = (MSLLHOOKSTRUCT*)lParam;
            if (ms) {
                if (wParam == WM_MOUSEMOVE) {
                    OnActiveMouseMove(ms->pt, ms->time);
                } else if (wParam == WM_LBUTTONUP) {
                    // Not swallowed: the XAML taskbar must see the release or it keeps mouse capture.
                    OnActiveMouseUp();
                } else if (wParam == WM_RBUTTONDOWN) {
                    if (CubeRenderer::Instance().OnRightDown(ms->pt)) {
                        s_swallowRUp = true;
                        return 1;   // right click on an edge zone: add / remove desktop, apps never see it
                    }
                } else if (wParam == WM_MOUSEWHEEL && (g_settings.wheelZoom || g_settings.altTab)) {
                    OnWheelEvent((int)(short)HIWORD(ms->mouseData));
                    return 1;   // swallow so windows under the cursor do not scroll
                }
            }
        }
        return CallNextHookEx(s_hMouseHook, nCode, wParam, lParam);
    }

    static LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) {
        if (nCode == HC_ACTION && (wParam == WM_KEYDOWN || wParam == WM_SYSKEYDOWN)) {
            KBDLLHOOKSTRUCT* kb = (KBDLLHOOKSTRUCT*)lParam;
            if (kb && kb->vkCode == VK_ESCAPE && s_state.load() == GestureState::ActiveDrag) {
                OnCancel();
                return 1;
            }
        }
        return CallNextHookEx(s_hKeyboardHook, nCode, wParam, lParam);
    }

    // Hooks are attached and detached by the render thread, which pumps messages every frame.
    void AttachHooks() {
        HMODULE hMod = nullptr;
        GetModuleHandleExW(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS | GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT,
                           (LPCWSTR)&LowLevelMouseProc, &hMod);
        if (!s_hMouseHook) s_hMouseHook = SetWindowsHookExW(WH_MOUSE_LL, LowLevelMouseProc, hMod, 0);
        if (!s_hKeyboardHook) s_hKeyboardHook = SetWindowsHookExW(WH_KEYBOARD_LL, LowLevelKeyboardProc, hMod, 0);
        LOG_DBG(L"Hooks attached mouse=0x%p kbd=0x%p", s_hMouseHook, s_hKeyboardHook);
    }

    void DetachHooks() {
        if (s_hMouseHook) { UnhookWindowsHookEx(s_hMouseHook); s_hMouseHook = nullptr; }
        if (s_hKeyboardHook) { UnhookWindowsHookEx(s_hKeyboardHook); s_hKeyboardHook = nullptr; }
    }

    // Used on mod unload (after the render thread has stopped).
    void Shutdown() {
        if (s_anchorTaskbar && IsWindow(s_anchorTaskbar)) KillTimer(s_anchorTaskbar, TIMER_ARMING_CHECK);
        s_state.store(GestureState::Idle);
        s_pUIAutomation = nullptr;
    }

} // namespace GestureController

// ============================================================================
// Overlay window procedure
// ============================================================================
LRESULT CALLBACK CubeRenderer::WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch (msg) {
        case WM_MOUSEACTIVATE:
            return MA_NOACTIVATE;
        case WM_ERASEBKGND:
            return 1;
        case WM_CAPTURECHANGED:
        case WM_CANCELMODE:
            return 0;
        case WM_CLOSE:
            DestroyWindow(hwnd);
            return 0;
    }
    return DefWindowProcW(hwnd, msg, wParam, lParam);
}

// ============================================================================
// Taskbar hooking
// ============================================================================
using CreateWindowInBand_t = HWND(WINAPI*)(DWORD, LPCWSTR, LPCWSTR, DWORD, int, int, int, int, HWND, HMENU, HINSTANCE, LPVOID, DWORD);
using CreateWindowExW_t = HWND(WINAPI*)(DWORD, LPCWSTR, LPCWSTR, DWORD, int, int, int, int, HWND, HMENU, HINSTANCE, LPVOID);

static CreateWindowInBand_t CreateWindowInBand_orig = nullptr;
static CreateWindowExW_t CreateWindowExW_orig = nullptr;

// All InputSite windows of explorer.exe (taskbar, Task View, Alt+Tab, Snap, ...) share ONE window procedure, so a
// single flag says whether it is hooked. The hook then reacts only to windows whose root is a taskbar.
static std::atomic<bool> g_inputSiteProcHooked{ false };
static std::mutex g_taskbarMutex;                       // guards g_subclassedTaskbars (windows are created on many threads)
static std::unordered_set<HWND> g_subclassedTaskbars;
static WNDPROC InputSiteWindowProc_Original = nullptr;
static std::atomic<bool> g_isWhInitialized{ false };

// Returns the root window when hWnd belongs to a taskbar (Shell_TrayWnd / Shell_SecondaryTrayWnd), otherwise nullptr.
static HWND GetTaskbarRoot(HWND hWnd) {
    WCHAR cls[32];
    HWND root = GetAncestor(hWnd, GA_ROOT);
    if (root && GetClassNameW(root, cls, ARRAYSIZE(cls)) &&
        (_wcsicmp(cls, L"Shell_TrayWnd") == 0 || _wcsicmp(cls, L"Shell_SecondaryTrayWnd") == 0)) {
        return root;
    }
    return nullptr;
}

static bool IsTaskbarRoot(HWND hWnd) {
    return GetTaskbarRoot(hWnd) != nullptr;
}

static LRESULT CALLBACK InputSiteWindowProc_Hook(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
        case WM_POINTERDOWN:
            if (IS_POINTER_FIRSTBUTTON_WPARAM(wParam) && !g_unloading.load()) {
                if (HWND hRoot = GetTaskbarRoot(hWnd)) {
                    POINT pt{ GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam) }; // screen coords
                    GestureController::OnMouseDown(hRoot, pt);
                }
            }
            break;

        case WM_POINTERUPDATE:
            if (GestureController::GetState() == GestureState::Arming && IsTaskbarRoot(hWnd)) {
                POINT pt{ GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam) };
                GestureController::OnArmingMouseMove(pt);
            }
            break;

        case WM_POINTERUP:
            if (IS_POINTER_FIRSTBUTTON_WPARAM(wParam) && GestureController::GetState() == GestureState::Arming &&
                IsTaskbarRoot(hWnd)) {
                GestureController::OnArmingMouseUp();
            }
            break;

        case WM_LBUTTONDOWN:
            if (!g_unloading.load()) {
                if (HWND hRoot = GetTaskbarRoot(hWnd)) {
                    POINT pt{ GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam) };
                    ClientToScreen(hWnd, &pt);
                    GestureController::OnMouseDown(hRoot, pt);
                }
            }
            break;

        case WM_MOUSEMOVE:
            if (GestureController::GetState() == GestureState::Arming && IsTaskbarRoot(hWnd)) {
                POINT pt{ GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam) };
                ClientToScreen(hWnd, &pt);
                GestureController::OnArmingMouseMove(pt);
            }
            break;

        case WM_LBUTTONUP:
            if (GestureController::GetState() == GestureState::Arming && IsTaskbarRoot(hWnd)) {
                GestureController::OnArmingMouseUp();
            }
            break;
    }
    return InputSiteWindowProc_Original(hWnd, uMsg, wParam, lParam);
}

// While a desktop switch is in progress, explorer's "client area animation" check says no. The user's real setting
// is never touched (see VDManager::SuppressSystemAnimation).
using SystemParametersInfoW_t = decltype(&SystemParametersInfoW);
static SystemParametersInfoW_t SystemParametersInfoW_orig = nullptr;
static BOOL WINAPI SystemParametersInfoW_hook(UINT uiAction, UINT uiParam, PVOID pvParam, UINT fWinIni) {
    if (uiAction == SPI_GETCLIENTAREAANIMATION && pvParam && VDManager::s_animSuppressed.load()) {
        *(BOOL*)pvParam = FALSE;
        return TRUE;
    }
    return SystemParametersInfoW_orig(uiAction, uiParam, pvParam, fWinIni);
}

static LRESULT CALLBACK TaskbarSubclassProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, DWORD_PTR) {
    switch (uMsg) {
        case WM_LBUTTONDOWN: {
            POINT pt{ GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam) };
            ClientToScreen(hWnd, &pt);
            GestureController::OnMouseDown(hWnd, pt);
            break;
        }
        case WM_MOUSEMOVE:
            if (GestureController::GetState() == GestureState::Arming) {
                POINT pt{ GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam) };
                ClientToScreen(hWnd, &pt);
                GestureController::OnArmingMouseMove(pt);
            }
            break;
        case WM_LBUTTONUP:
            if (GestureController::GetState() == GestureState::Arming) GestureController::OnArmingMouseUp();
            break;
        case WM_TIMER:
            if (wParam == 1002 /* TIMER_ARMING_CHECK */) {
                GestureController::OnArmingTimerTick();
                return 0;
            }
            break;
    }
    return DefSubclassProc(hWnd, uMsg, wParam, lParam);
}

static void HookInputSiteWindow(HWND hWnd) {
    // Only a taskbar's InputSite window may trigger the hook (the procedure itself is shared by every XAML island).
    if (!hWnd || g_unloading.load() || !IsTaskbarRoot(hWnd) || g_inputSiteProcHooked.exchange(true)) return;

    void* wndProc = (void*)GetWindowLongPtrW(hWnd, GWLP_WNDPROC);
    if (!wndProc) {
        g_inputSiteProcHooked.store(false);
        return;
    }

    if (Wh_SetFunctionHook(wndProc, (void*)InputSiteWindowProc_Hook, (void**)&InputSiteWindowProc_Original)) {
        if (g_isWhInitialized.load()) Wh_ApplyHookOperations();
        LOG_INF(L"Hooked InputSite wndproc %p", wndProc);
    } else {
        g_inputSiteProcHooked.store(false);
        LOG_ERR(L"Failed to hook InputSite wndproc %p", wndProc);
    }
}

static BOOL CALLBACK EnumChildFindInputSite(HWND hChild, LPARAM) {
    WCHAR cls[128]{};
    if (GetClassNameW(hChild, cls, ARRAYSIZE(cls)) &&
        _wcsicmp(cls, L"Windows.UI.Input.InputSite.WindowClass") == 0) {
        HookInputSiteWindow(hChild);
    }
    return TRUE;
}

static void SubclassTaskbar(HWND hWnd) {
    if (!hWnd || g_unloading.load()) return;
    bool already = false;
    {
        std::lock_guard<std::mutex> lk(g_taskbarMutex);
        already = g_subclassedTaskbars.contains(hWnd);
    }
    if (!already) {
        // Not under the lock: this call can wait for the window's thread.
        if (WindhawkUtils::SetWindowSubclassFromAnyThread(hWnd, TaskbarSubclassProc, 0)) {
            bool unloadingNow = false;
            {
                std::lock_guard<std::mutex> lk(g_taskbarMutex);
                // Wh_ModUninit sets g_unloading before it takes this lock to collect the windows, so either it
                // collects this one, or we see the flag here and remove the subclass ourselves.
                unloadingNow = g_unloading.load();
                if (!unloadingNow) g_subclassedTaskbars.insert(hWnd);
            }
            if (unloadingNow) {
                WindhawkUtils::RemoveWindowSubclassFromAnyThread(hWnd, TaskbarSubclassProc);
                return;
            }
            LOG_INF(L"Subclassed taskbar window 0x%p", hWnd);
        }
    }
    EnumChildWindows(hWnd, EnumChildFindInputSite, 0);
}

static void HandleCreatedWindow(HWND hWnd, LPCWSTR lpClassName) {
    if (!hWnd || !lpClassName || IS_INTRESOURCE(lpClassName)) return;
    if (_wcsicmp(lpClassName, L"Windows.UI.Input.InputSite.WindowClass") == 0) {
        HookInputSiteWindow(hWnd);
    } else if (_wcsicmp(lpClassName, L"Shell_TrayWnd") == 0 ||
               _wcsicmp(lpClassName, L"Shell_SecondaryTrayWnd") == 0) {
        SubclassTaskbar(hWnd);
    }
}

static HWND WINAPI CreateWindowInBand_hook(DWORD dwExStyle, LPCWSTR lpClassName, LPCWSTR lpWindowName, DWORD dwStyle,
    int X, int Y, int nWidth, int nHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance, LPVOID lpParam, DWORD dwBand) {
    HWND hWnd = CreateWindowInBand_orig(dwExStyle, lpClassName, lpWindowName, dwStyle, X, Y, nWidth, nHeight,
                                        hWndParent, hMenu, hInstance, lpParam, dwBand);
    HandleCreatedWindow(hWnd, lpClassName);
    return hWnd;
}

static HWND WINAPI CreateWindowExW_hook(DWORD dwExStyle, LPCWSTR lpClassName, LPCWSTR lpWindowName, DWORD dwStyle,
    int X, int Y, int nWidth, int nHeight, HWND hWndParent, HMENU hMenu, HINSTANCE hInstance, LPVOID lpParam) {
    HWND hWnd = CreateWindowExW_orig(dwExStyle, lpClassName, lpWindowName, dwStyle, X, Y, nWidth, nHeight,
                                     hWndParent, hMenu, hInstance, lpParam);
    HandleCreatedWindow(hWnd, lpClassName);
    return hWnd;
}

static BOOL CALLBACK EnumWindowsInitProc(HWND hWnd, LPARAM) {
    WCHAR cls[128]{};
    if (GetClassNameW(hWnd, cls, ARRAYSIZE(cls)) &&
        (_wcsicmp(cls, L"Shell_TrayWnd") == 0 || _wcsicmp(cls, L"Shell_SecondaryTrayWnd") == 0)) {
        SubclassTaskbar(hWnd);
    }
    return TRUE;
}

static bool InitMod() {
    HMODULE hUser32 = GetModuleHandleW(L"user32.dll");
    if (hUser32) {
        Wh_SetFunctionHook((void*)GetProcAddress(hUser32, "CreateWindowExW"),
                           (void*)CreateWindowExW_hook, (void**)&CreateWindowExW_orig);

        void* pBand = (void*)GetProcAddress(hUser32, "CreateWindowInBand");
        if (pBand) {
            Wh_SetFunctionHook(pBand, (void*)CreateWindowInBand_hook, (void**)&CreateWindowInBand_orig);
        }

        void* pSpi = (void*)GetProcAddress(hUser32, "SystemParametersInfoW");
        if (pSpi && !Wh_SetFunctionHook(pSpi, (void*)SystemParametersInfoW_hook, (void**)&SystemParametersInfoW_orig)) {
            SystemParametersInfoW_orig = nullptr;
            LOG_ERR(L"Could not hook SystemParametersInfoW, the desktop slide animation will not be suppressed");
        }
    }
    EnumWindows(EnumWindowsInitProc, 0);
    return true;
}

// ============================================================================
// Windhawk lifecycle
// ============================================================================
BOOL Wh_ModInit() {
    LOG_INF(L"Seamless Compiz Cube initializing");
    g_unloading.store(false);
    g_renderer.emplace();
    LoadSettings();
    if (!InitMod()) {
        LOG_ERR(L"Failed to initialize mod");
        g_renderer.reset();
        return FALSE;
    }
    g_isWhInitialized = true;
    scctray::Start();
    return TRUE;
}

void Wh_ModUninit() {
    LOG_INF(L"Seamless Compiz Cube uninitializing");

    // The settings window and the tray icon go first: they run on their own threads.
    sccset::CloseSettingsWindow();
    scctray::Stop();

    // 1. Stop new work first: no new render thread (EnsureThread refuses), no new gesture, no new subclass.
    g_unloading.store(true);
    g_isWhInitialized = false;

    // 2. Remove the taskbar subclasses so no more mouse messages reach the mod.
    std::vector<HWND> taskbars;
    {
        std::lock_guard<std::mutex> lk(g_taskbarMutex);
        taskbars.assign(g_subclassedTaskbars.begin(), g_subclassedTaskbars.end());
        g_subclassedTaskbars.clear();
    }
    for (HWND hWnd : taskbars) {
        if (IsWindow(hWnd)) {
            WindhawkUtils::RemoveWindowSubclassFromAnyThread(hWnd, TaskbarSubclassProc);
        }
    }

    // 3. Stop the render thread and wait for it (and the pacer and composer threads it owns) without a timeout.
    //    The render thread detaches the input hooks, destroys the overlay window and unregisters its class.
    CubeRenderer::Instance().Shutdown();

    RestoreTaskbarCapture();
    GestureController::Shutdown();
    VDManager::SuppressSystemAnimation(false);
    DesktopCaptureManager::Clear();
    WallpaperLoader::ClearCache();

    // 4. Every thread is gone and Teardown released all WinRT / D3D objects on the render thread: only memory is left.
    g_renderer.reset();
}

void Wh_ModSettingsChanged() {
    LOG_INF(L"Settings changed, reloading");
    LoadSettings();
    if (HWND w = sccset::g_settingsWnd) PostMessageW(w, sccset::WM_APP_SETTINGS_RELOAD, 0, 0);
    scctray::Refresh();
}
