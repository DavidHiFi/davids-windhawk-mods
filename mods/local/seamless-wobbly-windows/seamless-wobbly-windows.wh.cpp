// ==WindhawkMod==
// @id              seamless-wobbly-windows
// @name            Seamless Wobbly Windows
// @description     Jelly window dragging that keeps Snap, works with Seamless Window Manager's Alt-drag, wobbles the Seamless Borders ring and can add animated color glows behind see-through windows
// @version         1.2.9
// @author          DavidHiFi, HeyJeay, HaVeN80, lalimatyus
// @github          https://github.com/DavidHiFi
// @homepage        https://github.com/DavidHiFi/davids-windhawk-mods
// @donateUrl       https://ko-fi.com/DavidHiFi
// @license         GPL-3.0-or-later
// @include         *
// @include         windhawk.exe
// @exclude         dwm.exe
// @exclude         sihost.exe
// @exclude         RuntimeBroker.exe
// @exclude         StartMenuExperienceHost.exe
// @exclude         ShellExperienceHost.exe
// @exclude         SearchHost.exe
// @exclude         TextInputHost.exe
// @exclude         ApplicationFrameHost.exe
// @exclude         NVDisplay.Container.exe
// @compilerOptions -ldwmapi -lgdi32 -ladvapi32 -lole32 -loleaut32 -lruntimeobject -lshcore -lshell32 -ld2d1 -Wl,--delayload=d2d1.dll -Wl,--delayload=ole32.dll -Wl,--delayload=oleaut32.dll -Wl,--delayload=shcore.dll -Wl,--delayload=shell32.dll -Wl,--delayload=api-ms-win-core-winrt-l1-1-0.dll -Wl,--delayload=api-ms-win-core-winrt-string-l1-1-0.dll -Wl,--delayload=api-ms-win-core-winrt-error-l1-1-1.dll
// ==/WindhawkMod==

// ==WindhawkModReadme==
/*
# Seamless Wobbly Windows

Grab a window and it moves like jelly, with the same springs as the original
Window Wobble. The title bar keeps up with the pointer, the body trails
behind, and it settles with a wobble when you let go.

![Seamless Wobbly Windows](https://raw.githubusercontent.com/DavidHiFi/davids-windhawk-mods/main/media/previews/seamless-wobbly-windows.gif)

## What it adds

- **Windows still does the moving.** The wobble rides on top of the normal
  move, so Snap, Snap Layouts, drag-to-restore and shake all keep working.
- **Alt-drag wobbles too.** Moves started by Seamless Window Manager's held
  key wobble the same way as a title bar drag.
- **The border wobbles with the window.** If Seamless Borders is on, its ring
  is drawn into the wobble, so it bends with the window instead of standing
  still or vanishing.
- **Smooth bends.** The window's edges and the border curve smoothly as
  they bend.
- **Corners match.** The rounded corners follow Custom Window Corner Radius
  when that mod is on, and the Windows 11 default when it is not.
- **Light on the PC.** It all runs on the graphics card. Only the part of the
  screen the window covers is redrawn each frame, and the graphics memory is
  given back a few seconds after the last drag.
- **Color glows.** Soft light behind see-through (acrylic) windows shows
  through their blur. By default it is a calm blue to mauve gradient that
  sways slowly; glows, light beams, drifting orbs and waves are there too. Grab the window and the glow stays in
  it, bending with the wobble, then hands back to the real glow when you let
  go, without a flash.
- **Real glass while you drag.** On see-through windows the frosted blur stays
  live under the wobble and bends with it, so what is behind the window shows
  through blurred as it moves, the same as when it sits still.

## Color glows

The glow runs in a small Windhawk process of its own and draws with the
Windows compositor, so it costs almost nothing while it is still. It only
shows on windows that are see-through: Mica and solid backgrounds hide it.

- **Which windows** picks the listed apps, any window Windows reports as
  acrylic, or both. Brave and Helium are listed to start with.
- **Animate** and **Glow power saving** keep the graphics work down: only the
  active window can move, and glows hold still on battery saver, in games and
  when Windows animations are off.
- **Speed up with sound** reads only the output level, the same value the
  Windows volume mixer shows. Nothing is recorded.

While you wobble a window, the glow is painted onto the window's background
color, so text and buttons on top keep their own color. If it looks stronger
or weaker than the real glow, change **Glow strength while wobbling**.

## Settings

Pick how wobbly it feels with **Wobbliness**. Choose **Custom** to set the
springs yourself. Hold the bypass key (Shift by default) while you grab a
title bar to move a window without the wobble.

## Good to know

- The window shows a still picture of itself while you hold it, so a video
  looks paused until you let go.
- Nothing is loaded into dwm.exe. The effect runs inside each app.
- Turn off the other wobble mods (Wobbly Windows, Window Wobble) before using
  this one.

## What's new in 1.2.9
- Checks for the frosted glass during a drag (no change in look).

## What's new in 1.2.8
- The frosted glass under a dragged window no longer turns dark on windows
  that have their own frosted background.

## What's new in 1.2.7
- Game guard: wobbly windows and glows no longer load into games or their
  anti-cheat. Launchers keep the effect. Turn it off or add your own lists in
  the new "Game guard" settings.

## Credits

Based on [Window Wobble](https://github.com/heyjeay/window-wobble) by HeyJeay
(GPL-3.0-or-later), with ideas from lalimatyus's Wobbly Windows. The color
glows are [Acrylic Color Glows](https://windhawk.net/mods/acrylic-color-glows)
by [HaVeN80](https://github.com/haven80) (GPL-3.0), merged in.
*/
// ==/WindhawkModReadme==

// ==WindhawkModSettings==
/*
- wobbliness: medium
  $name: Wobbliness
  $description: How much the window bends and how long it takes to settle. Suggested Medium.
  $options:
  - veryLow: Very low
  - low: Low
  - medium: Medium
  - high: High
  - veryHigh: Very high
  - custom: Custom (use the values below)
- custom:
  - stiffness: 200
    $name: Stiffness
    $description: How hard the window pulls toward the pointer. 50 to 600, suggested 200.
  - softness: 65
    $name: Body softness (%)
    $description: How much softer the bottom edge is than the title bar. Lower trails more. 10 to 100, suggested 65.
  - rigidity: 30
    $name: Rigidity (x10)
    $description: How much the window holds its shape. 0 to 100, suggested 30.
  - friction: 140
    $name: Friction (x10)
    $description: Higher settles sooner with fewer wobbles. 20 to 400, suggested 140.
  - kick: 12
    $name: Kick (x100)
    $description: Extra bounce when you change direction. 0 to 50, suggested 12.
  $name: Custom wobble
  $description: Used only when Wobbliness is set to Custom.
- borders: true
  $name: Wobble the Seamless Borders ring
  $description: Draws the border ring into the wobble so it bends with the window. Only used when Seamless Borders is on.
- windowManager: true
  $name: Wobble Seamless Window Manager moves
  $description: Moves started by the window manager's held key wobble too.
- bypassKey: shift
  $name: Bypass key
  $description: Hold this while grabbing a title bar to move the window without the wobble.
  $options:
  - shift: Shift
  - ctrl: Ctrl
  - alt: Alt
  - none: None
- meshSize: 16
  $name: Smoothness
  $description: Grid cells per side. Higher bends more smoothly. 4 to 32, suggested 16.
- revealHoldMs: 90
  $name: Landing hold (ms)
  $description: How long the still picture stays up after you let go while the window redraws under it. Raise it if you see a flash. 0 to 500, suggested 90.
- idleReleaseSec: 5
  $name: Free graphics memory after (seconds)
  $description: Idle time after a drag before the graphics memory is given back. 0 keeps it. 0 to 600, suggested 5.
- glow:
  - enabled: true
    $name: Color glows behind see-through windows
    $description: Soft animated light behind acrylic windows, blurred into their background. Turn off to run the wobble only.
  - effect: gradient
    $name: Effect
    $options:
    - gradient: Gradient (color 1 to color 2)
    - glows: Glows
    - beams: Light beams
    - orbs: Drifting orbs
    - waves: Waves
  - mode: combined
    $name: Which windows
    $options:
    - selected: Only the apps listed below
    - automatic: Any window Windows reports as acrylic
    - combined: The listed apps and any acrylic window
  - color1: "#89B4FA"
    $name: Color 1
    $description: Hex color. Suggested #89B4FA (blue). The gradient starts here.
  - color2: "#CBA6F7"
    $name: Color 2
    $description: Hex color. Suggested #CBA6F7 (mauve). The gradient ends here.
  - color3: "#B4BEFE"
    $name: Color 3
    $description: Hex color. Suggested #B4BEFE (lavender). Not used by the gradient.
  - seconds: 12
    $name: Cycle length (seconds)
    $description: Higher is slower. The gradient sways once every two cycles. 2 to 120, suggested 12.
  - opacity: 32
    $name: Strength (%)
    $description: 1 to 100, suggested 32.
  - size: 380
    $name: Size
    $description: Glow and orb width, and how thick beams and waves are. 80 to 1600, suggested 380.
  - inDrag: true
    $name: Keep the glow while wobbling
    $description: Paints the glow into the wobbling window, so it moves and bends with it.
  - dragStrength: 100
    $name: Glow strength while wobbling (%)
    $description: 100 matches the glow seen through the window when it rests. Lower is fainter, higher is brighter. 0 to 200, suggested 100.
  $name: Color glows
- glowApps:
  - helium.exe
  - brave.exe
  $name: Glow apps
  $description: Program names, like brave.exe. A program's own product name works too, so helium.exe finds Helium although its file is chrome.exe. No paths or wildcards.
- glowExcluded:
  - windhawk.exe
  $name: Never glow these apps
  $description: Wins over the list and the acrylic check.
- glowMotion:
  - animate: all
    $name: Animate
    $description: Fewer moving glows means less graphics work.
    $options:
    - all: All windows
    - active: Only the active window
    - none: Still glows, no motion
  - smoothness: full
    $name: Motion updates
    $options:
    - full: Every screen refresh
    - reduced: About 30 a second (saves power)
  - maxWindows: 20
    $name: Most windows with a glow
    $description: 1 to 100, suggested 20.
  $name: Glow motion
- glowAudio:
  - reactive: false
    $name: Speed up with sound
    $description: Reads only the output level, never the sound itself.
  - fastestSeconds: 3
    $name: Cycle length at full volume (seconds)
    $description: 1 to 120, suggested 3.
  - sensitivity: 100
    $name: Sound sensitivity (%)
    $description: Raise it if the glow barely reacts. 25 to 400, suggested 100.
  $name: Glow and sound
- glowPower:
  - batterySaver: true
    $name: Hold still on battery saver
  - fullscreen: true
    $name: Hold still while a game or full-screen app is in front
  - reduceMotion: true
    $name: Hold still when Windows animations are off
  - transparency: true
    $name: Hide when Windows transparency is off
  $name: Glow power saving
- glowBeams:
  - count: 3
    $name: Number of beams
    $description: Colors 1 to 3 in turn. 1 to 8, suggested 3.
  - origin: top
    $name: Beams come from
    $options:
    - top: Top edge
    - bottom: Bottom edge
    - left: Left edge
    - right: Right edge
  - sweep: 30
    $name: Sweep (degrees)
    $description: 0 keeps the beams still. 0 to 80, suggested 30.
  $name: Light beams
- glowOrbs:
  - - color: "#89B4FA"
      $name: Color
    - angle: 30
      $name: Direction (degrees)
      $description: 0 right, 90 up, 180 left, 270 down.
    - speed: 100
      $name: Speed (%)
      $description: 10 to 400, suggested 100.
  - - color: "#CBA6F7"
      $name: Color
    - angle: 150
      $name: Direction (degrees)
      $description: 0 right, 90 up, 180 left, 270 down.
    - speed: 70
      $name: Speed (%)
      $description: 10 to 400, suggested 70.
  - - color: "#B4BEFE"
      $name: Color
    - angle: 250
      $name: Direction (degrees)
      $description: 0 right, 90 up, 180 left, 270 down.
    - speed: 130
      $name: Speed (%)
      $description: 10 to 400, suggested 130.
  $name: Drifting orbs
  $description: Up to 12. An orb with no color ends the list.
- glowOrbEdges: bounce
  $name: Orbs at the edges
  $options:
  - bounce: Bounce back
  - wrap: Wrap around
- glowWaves:
  - amplitude: 18
    $name: Wave height (% of the window)
    $description: 2 to 45, suggested 18.
  - length: 100
    $name: Wave length (% of the window)
    $description: 25 to 400, suggested 100.
  $name: Waves
- gameGuard:
  - enabled: true
    $name: Stay out of games
    $description: 'On, this mod does not load into games or their anti-cheat, so it cannot cause stutter or a ban. Launchers such as Steam keep the look. Applies the next time an app starts. Suggested: on.'
  - allow: ""
    $name: Always allow these apps
    $description: 'Apps to style even when they look like a game. Process names separated by commas, for example MyTool.exe, Editor*.exe. The * works as a wildcard.'
  - skip: ""
    $name: Also skip these apps
    $description: 'Extra apps to leave alone, written the same way.'
  $name: Game guard
*/
// ==/WindhawkModSettings==

// Seamless Wobbly Windows - spring-physics window dragging for Windows.
// Copyright (C) 2026 heyjeay (Window Wobble)
// Copyright (C) 2026 DavidHiFi (follow mode, borders, window manager, renderer)
// Copyright (C) 2026 HaVeN80 (Acrylic Color Glows)
//
// This program is free software: you can redistribute it and/or modify it
// under the terms of the GNU General Public License as published by the Free
// Software Foundation, either version 3 of the License, or (at your option)
// any later version.
//
// This program is distributed in the hope that it will be useful, but
// WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General
// Public License for more details <https://www.gnu.org/licenses/>.

#include <windhawk_utils.h>

#include <windows.h>
#include <dwmapi.h>
#include <d3d11_1.h>
#include <dxgi1_3.h>
#include <dcomp.h>
#include <d2d1.h>
#include <sddl.h>
#include <shellapi.h>
#include <shellscalingapi.h>
#include <mmdeviceapi.h>

#include <algorithm>
#include <array>
#include <atomic>
#include <chrono>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <cwctype>
#include <initializer_list>
#include <memory>
#include <optional>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.Foundation.Collections.h>
#include <winrt/Windows.Foundation.Numerics.h>
#include <winrt/Windows.System.h>
#include <winrt/Windows.Graphics.h>
#include <winrt/Windows.Graphics.Effects.h>
#include <winrt/Windows.UI.h>
#include <winrt/Windows.UI.Composition.h>
#include <winrt/Windows.UI.Composition.Desktop.h>

EXTERN_C IMAGE_DOS_HEADER __ImageBase;
#define MOD_HINSTANCE (reinterpret_cast<HINSTANCE>(&__ImageBase))

// -----------------------------------------------------------------------------
// Glow hand-off
// -----------------------------------------------------------------------------
// The glow runs in the mod's own windhawk.exe process. It publishes its clock
// and the windows it decorates here, so a wobble in an app process paints the
// same glow at the same moment; the window property tells the glow process a
// window is being wobbled, so it keeps the clock going and shows its own glow
// at once when the window lands.

static constexpr wchar_t  kGlowDragProp[] = L"SeamlessWobblyWindows.Glow";
// A test window sets this on itself; the glow process then reports in the map's
// watch field how far that window got through its checks.
static constexpr wchar_t  kGlowWatchProp[] = L"SeamlessWobblyWindows.GlowWatch";
static constexpr wchar_t  kGlowMapName[]  = L"Local\\SeamlessWobblyWindows.Glow";
static constexpr uint32_t kGlowMapVersion = 1;
static constexpr int      kGlowMaxEntries = 100;

struct GlowShared {
    volatile LONG seq;         // odd while being written
    uint32_t version;
    uint32_t running;          // the shared clock is moving
    uint32_t animated;         // 1: the compositor drives it, 0: advanced by hand
    int64_t  baseQpc;          // animated: when T was 0
    double   manualTime;       // by hand: T at manualQpc
    int64_t  manualQpc;
    double   rate;             // by hand: seconds of T per second
    uint32_t count;
    uint32_t watch;            // test aid: which checks the window marked kGlowWatchProp passed
    struct Entry { uint32_t hwnd, live; float offset, frozen; } e[kGlowMaxEntries];
};
static_assert(offsetof(GlowShared, baseQpc) == 16, "glow map layout");
static_assert(offsetof(GlowShared, e) == 56, "glow map layout");
static_assert(sizeof(GlowShared) == 56 + 16 * kGlowMaxEntries, "glow map layout");


#ifndef EVENT_OBJECT_CLOAKED
#define EVENT_OBJECT_CLOAKED 0x8017
#endif
#ifndef EVENT_OBJECT_UNCLOAKED
#define EVENT_OBJECT_UNCLOAKED 0x8018
#endif
#ifndef SPI_GETCLIENTAREAANIMATION
#define SPI_GETCLIENTAREAANIMATION 0x1042
#endif

// Acrylic Color Glows by HaVeN80 (GPL-3.0), ported into this mod. It runs only
// in the mod's own windhawk.exe tool process; app processes never call it.
namespace glowtool {

namespace wc = winrt::Windows::UI::Composition;
using winrt::Windows::UI::Color;

namespace {

////////////////////////////////////////////////////////////////////////////////
// Constants

// Documented DWM values, used numerically so the mod doesn't depend on how
// recent the SDK headers are.
constexpr DWORD kDwmaTransitionsForceDisabled = 3;
constexpr DWORD kDwmaWindowCornerPreference = 33;
constexpr DWORD kDwmaBorderColor = 34;
constexpr DWORD kDwmaSystemBackdropType = 38;
constexpr int kCornerDoNotRound = 1;
constexpr int kCornerRound = 2;
constexpr int kBackdropTransientWindow = 3;
constexpr COLORREF kColorNone = 0xFFFFFFFE;
constexpr DWORD kCloakedShell = 0x2;

constexpr UINT kPollIntervalMs = 2000;
constexpr UINT kSettleDelayMs = 250;
constexpr int kFadeInMs = 180;
constexpr UINT_PTR kPollTimerId = 1;
constexpr UINT_PTR kSettleTimerId = 2;
constexpr UINT_PTR kFrameTimerId = 3;  // Clock advanced by the worker.
// USER timers fire on the system tick (15.6 ms by default), so these land on
// one and two ticks: about 64 and 32 updates per second.
constexpr UINT kFrameIntervalMs = 15;
constexpr UINT kReducedFrameIntervalMs = 30;
constexpr double kMaxFrameStepSeconds = 0.25;  // Don't leap ahead after a stall.
constexpr double kAudioAttackSeconds = 0.12;   // Level smoothing when it rises.
constexpr double kAudioReleaseSeconds = 0.9;   // ...and when it falls.
constexpr ULONGLONG kAudioRetryMs = 3000;      // Retry a missing output device.
constexpr UINT kRefreshMessage = WM_APP + 1;
constexpr UINT kSettingsMessage = WM_APP + 2;
constexpr int kMinTargetSize = 32;             // Physical pixels.
constexpr ULONGLONG kFailedRetryMs = 60000;    // Retry windows that failed before.
constexpr ULONGLONG kDesktopsRetryMs = 10000;  // Retry the virtual desktop manager.
constexpr DWORD kStopTimeoutMs = 10000;
constexpr wchar_t kClassName[] = L"SeamlessWobblyGlow";

constexpr float kPi = 3.14159265f;
constexpr float kTwoPi = 2.0f * kPi;
// Shared clock period. Every clock-driven motion completes a whole number of
// cycles in this time, so nothing jumps when the clock wraps around.
constexpr float kLoopSeconds = 600.0f;
constexpr int kMaxOrbs = 12;
constexpr int kWaveCount = 3;
constexpr int kWaveBlobs = 10;
// Gradient: blue (color 1) to mauve (color 2) across the window, swaying
// gently around the top-left to bottom-right diagonal. A linear gradient
// looks the same before and after the acrylic blur, so the copy painted
// inside the wobble matches the real one exactly.
constexpr float kGradientAngle = 45.0f;  // Degrees, clockwise from left to right.
constexpr float kGradientSweep = 20.0f;  // Degrees either side.
constexpr float kGradientAlpha = 2.5f;   // Times the opacity, capped at full: the acrylic shows about a quarter of it.
// One sway every two cycles: slow enough to stay calm.
float GradientFrequency(int seconds);

const PCWSTR kExcludedClasses[] = {
    L"Progman",
    L"WorkerW",
    L"Shell_TrayWnd",
    L"Shell_SecondaryTrayWnd",
    L"NotifyIconOverflowWindow",
    L"TopLevelWindowForOverflowXamlIsland",
    L"XamlExplorerHostIslandWindow",
    L"MultitaskingViewFrame",
    L"ForegroundStaging",
    L"TaskListThumbnailWnd",
    L"Windows.UI.Core.CoreWindow",
    L"Shell_InputSwitchTopLevelWindow",
    L"Xaml_WindowedPopupClass",
    L"#32768",
    L"tooltips_class32",
    L"SysShadow",
    L"Ghost",
    L"Shell_LightDismissOverlay",
    L"EdgeUiInputTopWndClass",
    L"ApplicationManager_ImmersiveShellWindow",
    L"Windows.Internal.Shell.TabProxyWindow",
    L"Microsoft.UI.Content.PopupWindowSiteBridge",
    L"PopupHost",
    L"ComboLBox",
    L"DropDown",
    L"Net UI Tool Window",
    L"SeamlessWobblyOverlay",
    L"SeamlessBordersPart",
    kClassName,
};

struct HookRange {
    DWORD first;
    DWORD last;
};

const HookRange kHookRanges[] = {
    {EVENT_SYSTEM_FOREGROUND, EVENT_SYSTEM_FOREGROUND},
    {EVENT_SYSTEM_MINIMIZESTART, EVENT_SYSTEM_MINIMIZEEND},
    {EVENT_OBJECT_DESTROY, EVENT_OBJECT_REORDER},
    {EVENT_OBJECT_LOCATIONCHANGE, EVENT_OBJECT_LOCATIONCHANGE},
    {EVENT_OBJECT_CLOAKED, EVENT_OBJECT_UNCLOAKED},
};

////////////////////////////////////////////////////////////////////////////////
// COM interfaces declared locally, so the mod doesn't depend on optional SDK
// headers. Layouts and IDs are documented by Microsoft.

// ICompositorDesktopInterop
struct DesktopInterop : ::IUnknown {
    virtual HRESULT STDMETHODCALLTYPE CreateDesktopWindowTarget(HWND hwndTarget,
                                                                BOOL isTopmost,
                                                                void** result) = 0;
    virtual HRESULT STDMETHODCALLTYPE EnsureOnThread(DWORD threadId) = 0;
};
constexpr GUID kDesktopInteropIid = {
    0x29E691FA, 0x4567, 0x4DCA, {0xB3, 0x19, 0xD0, 0xF2, 0x07, 0xEB, 0x68, 0x07}};

// IVirtualDesktopManager
struct VirtualDesktopManager : ::IUnknown {
    virtual HRESULT STDMETHODCALLTYPE IsWindowOnCurrentVirtualDesktop(HWND window,
                                                                      BOOL* result) = 0;
    virtual HRESULT STDMETHODCALLTYPE GetWindowDesktopId(HWND window, GUID* desktopId) = 0;
    virtual HRESULT STDMETHODCALLTYPE MoveWindowToDesktop(HWND window, REFGUID desktopId) = 0;
};
constexpr GUID kVirtualDesktopManagerClsid = {
    0xAA509086, 0x5CA9, 0x4C25, {0x8F, 0x95, 0x58, 0x9D, 0x3C, 0x07, 0xB4, 0x8A}};
constexpr GUID kVirtualDesktopManagerIid = {
    0xA5CD92FF, 0x29BE, 0x454C, {0x8D, 0x04, 0xD8, 0x28, 0x79, 0xFB, 0x3F, 0x1B}};

// IAudioMeterInformation. The compiler's endpointvolume.h only forward-declares
// it, so the documented layout is declared here.
struct AudioMeterInformation : ::IUnknown {
    virtual HRESULT STDMETHODCALLTYPE GetPeakValue(float* peak) = 0;
    virtual HRESULT STDMETHODCALLTYPE GetMeteringChannelCount(UINT* channelCount) = 0;
    virtual HRESULT STDMETHODCALLTYPE GetChannelsPeakValues(UINT32 channelCount,
                                                            float* peakValues) = 0;
    virtual HRESULT STDMETHODCALLTYPE QueryHardwareSupport(DWORD* hardwareSupportMask) = 0;
};

// MMDeviceEnumerator, IMMDeviceEnumerator and IAudioMeterInformation, so the
// mod doesn't need the uuid library.
constexpr GUID kMMDeviceEnumeratorClsid = {
    0xBCDE0395, 0xE52F, 0x467C, {0x8E, 0x3D, 0xC4, 0x57, 0x92, 0x91, 0x69, 0x2E}};
constexpr GUID kMMDeviceEnumeratorIid = {
    0xA95664D2, 0x9614, 0x4F35, {0xA7, 0x46, 0xDE, 0x8D, 0xB6, 0x36, 0x17, 0xE6}};
constexpr GUID kAudioMeterInformationIid = {
    0xC02216F6, 0x8C67, 0x4B5B, {0x9D, 0x00, 0xD0, 0x08, 0xE7, 0x3E, 0x00, 0x64}};

// DispatcherQueueOptions / CreateDispatcherQueueController
struct DispatcherQueueOptionsAbi {
    DWORD dwSize;
    int threadType;
    int apartmentType;
};
constexpr int kDispatcherQueueThreadCurrent = 2;  // DQTYPE_THREAD_CURRENT
constexpr int kDispatcherQueueComSta = 2;         // DQTAT_COM_STA
using CreateDispatcherQueueController_t =
    HRESULT(WINAPI*)(DispatcherQueueOptionsAbi options, void** controller);

////////////////////////////////////////////////////////////////////////////////
// Settings

enum class Mode { Selected, Automatic, Combined };
enum class Effect { Gradient, Glows, Beams, Orbs, Waves };
enum class Origin { Top, Bottom, Left, Right };
enum class Edges { Bounce, Wrap };
enum class Animate { All, Active, None };

struct Orb {
    Color color{};
    int angle = 0;
    int speed = 100;
};

struct Settings {
    bool enabled = true;
    bool inDrag = true;
    int dragStrength = 100;  // Percent of the glow painted inside the wobble.
    Effect effect = Effect::Gradient;
    Mode mode = Mode::Selected;
    std::vector<std::wstring> include;
    std::vector<std::wstring> exclude;
    std::array<Color, 3> colors{};
    int seconds = 12;
    int opacity = 32;
    int diameter = 380;
    int maxWindows = 20;
    int beamCount = 3;
    Origin beamOrigin = Origin::Top;
    int beamSweep = 30;
    std::vector<Orb> orbs;
    Edges orbEdges = Edges::Bounce;
    int waveAmplitude = 18;
    int waveLength = 100;
    Animate animate = Animate::All;
    bool reducedSmoothness = false;
    struct {
        bool batterySaver = true;
        bool fullscreen = true;
        bool reduceMotion = true;
        bool transparency = true;
    } power;
    struct {
        bool reactive = false;
        int fastestSeconds = 3;
        int sensitivity = 100;
    } audio;
};

// Owned by the worker thread: loaded and read only there.
Settings g_settings;

// Everything that defines the shape of the effect. When it changes, effect
// windows are rebuilt; otherwise colors are updated in place.
struct Layout {
    Effect effect;
    int seconds;
    int diameter;
    int beamCount;
    Origin beamOrigin;
    int beamSweep;
    std::vector<std::pair<int, int>> orbs;  // angle, speed
    Edges orbEdges;
    int waveAmplitude;
    int waveLength;
    bool reducedSmoothness;
    bool audioReactive;  // Changes how the clock is driven.

    bool operator==(Layout const& other) const {
        return effect == other.effect && seconds == other.seconds &&
               diameter == other.diameter && beamCount == other.beamCount &&
               beamOrigin == other.beamOrigin && beamSweep == other.beamSweep &&
               orbs == other.orbs && orbEdges == other.orbEdges &&
               waveAmplitude == other.waveAmplitude && waveLength == other.waveLength &&
               reducedSmoothness == other.reducedSmoothness &&
               audioReactive == other.audioReactive;
    }
    bool operator!=(Layout const& other) const { return !(*this == other); }
};

Layout CurrentLayout() {
    Layout layout{g_settings.effect,     g_settings.seconds,   g_settings.diameter,
                  g_settings.beamCount,  g_settings.beamOrigin, g_settings.beamSweep,
                  {},                    g_settings.orbEdges,  g_settings.waveAmplitude,
                  g_settings.waveLength, g_settings.reducedSmoothness,
                  g_settings.audio.reactive};
    for (auto const& orb : g_settings.orbs) {
        layout.orbs.emplace_back(orb.angle, orb.speed);
    }
    return layout;
}

std::wstring ToLower(std::wstring value) {
    for (auto& c : value) {
        c = static_cast<wchar_t>(towlower(c));
    }
    return value;
}

std::wstring Trim(std::wstring const& text, PCWSTR characters = L" \t") {
    size_t first = text.find_first_not_of(characters);
    if (first == std::wstring::npos) {
        return {};
    }
    size_t last = text.find_last_not_of(characters);
    return text.substr(first, last - first + 1);
}

std::wstring NormalizeProcessName(std::wstring const& text) {
    std::wstring name = Trim(text, L" \t\"");
    size_t slash = name.find_last_of(L"\\/");
    if (slash != std::wstring::npos) {
        name.erase(0, slash + 1);
    }
    return ToLower(std::move(name));
}

std::wstring TakeString(PCWSTR raw) {
    std::wstring result = raw ? raw : L"";
    if (raw) {
        Wh_FreeStringSetting(raw);
    }
    return result;
}

enum class NameList { Applications, Excluded };

std::vector<std::wstring> ReadNameList(NameList list) {
    std::vector<std::wstring> result;
    for (int i = 0; i < 1000; i++) {
        // Literal format strings only: never pass a variable as the format.
        std::wstring entry = TakeString(list == NameList::Excluded
                                            ? Wh_GetStringSetting(L"glowExcluded[%d]", i)
                                            : Wh_GetStringSetting(L"glowApps[%d]", i));
        if (entry.empty()) {
            break;
        }

        // Also accept "a.exe;b.exe" inside a single entry.
        size_t start = 0;
        while (start <= entry.size()) {
            size_t end = entry.find(L';', start);
            if (end == std::wstring::npos) {
                end = entry.size();
            }
            std::wstring name = NormalizeProcessName(entry.substr(start, end - start));
            if (!name.empty() &&
                std::find(result.begin(), result.end(), name) == result.end()) {
                result.push_back(std::move(name));
            }
            start = end + 1;
        }
    }
    return result;
}

Color ParseColor(std::wstring const& raw, unsigned fallback) {
    std::wstring text = Trim(raw, L" \t#");
    unsigned value = fallback;
    if (text.size() == 6) {
        unsigned candidate = 0;
        bool valid = true;
        for (wchar_t c : text) {
            int digit = c >= L'0' && c <= L'9'   ? c - L'0'
                        : c >= L'a' && c <= L'f' ? c - L'a' + 10
                        : c >= L'A' && c <= L'F' ? c - L'A' + 10
                                                 : -1;
            if (digit < 0) {
                valid = false;
                break;
            }
            candidate = (candidate << 4) | static_cast<unsigned>(digit);
        }
        if (valid) {
            value = candidate;
        }
    }
    return {255, static_cast<uint8_t>(value >> 16), static_cast<uint8_t>(value >> 8),
            static_cast<uint8_t>(value)};
}

void LoadSettings() {
    Settings& s = g_settings;

    s.enabled = Wh_GetIntSetting(L"glow.enabled") != 0;
    s.inDrag = Wh_GetIntSetting(L"glow.inDrag") != 0;
    s.dragStrength = std::clamp(Wh_GetIntSetting(L"glow.dragStrength"), 0, 200);

    std::wstring effect =TakeString(Wh_GetStringSetting(L"glow.effect"));
    s.effect = effect == L"glows"   ? Effect::Glows
               : effect == L"beams" ? Effect::Beams
               : effect == L"orbs"  ? Effect::Orbs
               : effect == L"waves" ? Effect::Waves
                                    : Effect::Gradient;

    std::wstring mode = TakeString(Wh_GetStringSetting(L"glow.mode"));
    s.mode = mode == L"automatic"  ? Mode::Automatic
             : mode == L"combined" ? Mode::Combined
                                   : Mode::Selected;

    s.include = ReadNameList(NameList::Applications);
    s.exclude = ReadNameList(NameList::Excluded);
    s.colors = {ParseColor(TakeString(Wh_GetStringSetting(L"glow.color1")), 0x89B4FA),
                ParseColor(TakeString(Wh_GetStringSetting(L"glow.color2")), 0xCBA6F7),
                ParseColor(TakeString(Wh_GetStringSetting(L"glow.color3")), 0xB4BEFE)};
    s.seconds = std::clamp(Wh_GetIntSetting(L"glow.seconds"), 2, 120);
    s.opacity = std::clamp(Wh_GetIntSetting(L"glow.opacity"), 1, 100);
    s.diameter = std::clamp(Wh_GetIntSetting(L"glow.size"), 80, 1600);
    s.maxWindows = std::clamp(Wh_GetIntSetting(L"glowMotion.maxWindows"), 1, 100);

    s.beamCount = std::clamp(Wh_GetIntSetting(L"glowBeams.count"), 1, 8);
    std::wstring origin = TakeString(Wh_GetStringSetting(L"glowBeams.origin"));
    s.beamOrigin = origin == L"bottom" ? Origin::Bottom
                   : origin == L"left" ? Origin::Left
                   : origin == L"right" ? Origin::Right
                                        : Origin::Top;
    s.beamSweep = std::clamp(Wh_GetIntSetting(L"glowBeams.sweep"), 0, 80);

    s.orbs.clear();
    for (int i = 0; i < kMaxOrbs; i++) {
        std::wstring color = Trim(TakeString(Wh_GetStringSetting(L"glowOrbs[%d].color", i)));
        if (color.empty()) {
            break;
        }
        Orb orb;
        orb.color = ParseColor(color, 0xFFFFFF);
        orb.angle = ((Wh_GetIntSetting(L"glowOrbs[%d].angle", i) % 360) + 360) % 360;
        orb.speed = std::clamp(Wh_GetIntSetting(L"glowOrbs[%d].speed", i), 10, 400);
        s.orbs.push_back(orb);
    }
    s.orbEdges = TakeString(Wh_GetStringSetting(L"glowOrbEdges")) == L"wrap" ? Edges::Wrap
                                                                         : Edges::Bounce;

    s.waveAmplitude = std::clamp(Wh_GetIntSetting(L"glowWaves.amplitude"), 2, 45);
    s.waveLength = std::clamp(Wh_GetIntSetting(L"glowWaves.length"), 25, 400);

    std::wstring animate = TakeString(Wh_GetStringSetting(L"glowMotion.animate"));
    s.animate = animate == L"active" ? Animate::Active
                : animate == L"none" ? Animate::None
                                     : Animate::All;
    s.reducedSmoothness = TakeString(Wh_GetStringSetting(L"glowMotion.smoothness")) == L"reduced";
    s.power.batterySaver = Wh_GetIntSetting(L"glowPower.batterySaver") != 0;
    s.power.fullscreen = Wh_GetIntSetting(L"glowPower.fullscreen") != 0;
    s.power.reduceMotion = Wh_GetIntSetting(L"glowPower.reduceMotion") != 0;
    s.power.transparency = Wh_GetIntSetting(L"glowPower.transparency") != 0;

    s.audio.reactive = Wh_GetIntSetting(L"glowAudio.reactive") != 0;
    s.audio.fastestSeconds = std::clamp(Wh_GetIntSetting(L"glowAudio.fastestSeconds"), 1, 120);
    s.audio.sensitivity = std::clamp(Wh_GetIntSetting(L"glowAudio.sensitivity"), 25, 400);
}

bool Contains(std::vector<std::wstring> const& list, std::wstring const& name) {
    return std::find(list.begin(), list.end(), name) != list.end();
}

////////////////////////////////////////////////////////////////////////////////
// Motion helpers

float Frac(float value) {
    return value - std::floor(value);
}

// Angular speed (radians per second) close to one cycle every `seconds`,
// rounded so a whole number of cycles fits the clock loop.
float LoopFrequency(float seconds) {
    float cycles = std::max(1.0f, std::round(kLoopSeconds / std::max(seconds, 0.1f)));
    return kTwoPi * cycles / kLoopSeconds;
}

float GradientFrequency(int seconds) {
    return LoopFrequency(2.0f * static_cast<float>(seconds));
}

// Brings a time back into [0, kLoopSeconds).
float WrapTime(float seconds) {
    float wrapped = std::fmod(seconds, kLoopSeconds);
    return wrapped < 0 ? wrapped + kLoopSeconds : wrapped;
}

// Rounds a velocity (in periods per second) so the motion repeats exactly when
// the clock wraps around.
float QuantizeVelocity(float velocity, float period) {
    return std::round(velocity * kLoopSeconds / period) * period / kLoopSeconds;
}

////////////////////////////////////////////////////////////////////////////////
// Globals

HMODULE g_module = nullptr;
HANDLE g_workerThread = nullptr;
HANDLE g_stopEvent = nullptr;
// Published by the worker so settings changes can be posted to it.
std::atomic<HWND> g_controller{nullptr};

////////////////////////////////////////////////////////////////////////////////
// Composition resources shared by every effect window

struct GradientBrush {
    wc::CompositionBrush brush{nullptr};
    std::vector<wc::CompositionColorGradientStop> stops;
};

struct Resources {
    wc::Compositor compositor{nullptr};
    // "T": shared time in seconds, 0 to kLoopSeconds. It only runs while at
    // least one effect is live; frozen effects keep their own time.
    wc::CompositionPropertySet clock{nullptr};
    std::array<GradientBrush, 3> glowBrushes;  // Glows and waves.
    std::array<GradientBrush, 3> beamBrushes;
    std::vector<GradientBrush> orbBrushes;
    GradientBrush gradientBrush;
    wc::ScalarKeyFrameAnimation fadeIn{nullptr};

    void Create() {
        compositor = wc::Compositor();

        clock = compositor.CreatePropertySet();
        clock.InsertScalar(L"T", 0.0f);
        clockRunning_ = false;

        for (size_t i = 0; i < 3; i++) {
            glowBrushes[i] = MakeRadialBrush();
            beamBrushes[i] = MakeBeamBrush();
        }
        gradientBrush = MakeLinearBrush();
        orbBrushes.clear();
        for (size_t i = 0; i < g_settings.orbs.size(); i++) {
            orbBrushes.push_back(MakeRadialBrush());
        }
        ApplyColors();

        fadeIn = compositor.CreateScalarKeyFrameAnimation();
        fadeIn.InsertKeyFrame(0.0f, 0.0f);
        fadeIn.InsertKeyFrame(1.0f, 1.0f);
        fadeIn.Duration(std::chrono::milliseconds(kFadeInMs));
    }

    // Brushes are shared by all effect windows, so this recolors them all at
    // once without recreating anything.
    void ApplyColors() {
        auto alpha = static_cast<float>(g_settings.opacity * 255 / 100);
        for (size_t i = 0; i < 3; i++) {
            Tint(glowBrushes[i], g_settings.colors[i], alpha, {1.0f, 1.0f / 3.0f, 0.0f});
            Tint(beamBrushes[i], g_settings.colors[i], alpha, {0.0f, 0.35f, 1.0f, 0.35f, 0.0f});
        }
        for (size_t i = 0; i < orbBrushes.size() && i < g_settings.orbs.size(); i++) {
            Tint(orbBrushes[i], g_settings.orbs[i].color, alpha, {1.0f, 1.0f / 3.0f, 0.0f});
        }
        // Both stops share one alpha, so straight and premultiplied blending
        // give the same colors in between.
        if (gradientBrush.stops.size() == 2) {
            for (size_t i = 0; i < 2; i++) {
                Color color = g_settings.colors[i];
                color.A = static_cast<uint8_t>(
                    std::clamp(alpha * kGradientAlpha + 0.5f, 0.0f, 255.0f));
                gradientBrush.stops[i].Color(color);
            }
        }
    }

    bool ClockRunning() const { return clockRunning_; }

    // Animated: the compositor advances the clock at the monitor's refresh
    // rate. Otherwise the worker advances it from a timer (TickClock), at a
    // speed that may change over time without any jump.
    void StartClock(bool animated) {
        clockStart_ = std::chrono::steady_clock::now();
        lastTick_ = clockStart_;
        manualTime_ = 0.0;
        LARGE_INTEGER qpc;
        QueryPerformanceCounter(&qpc);
        baseQpc_ = qpc.QuadPart;
        manualQpc_ = qpc.QuadPart;
        lastRate_ = 1.0;
        clockAnimated_ = animated;
        clockRunning_ = true;
        clock.InsertScalar(L"T", 0.0f);
        if (animated) {
            auto linear = compositor.CreateLinearEasingFunction();
            auto tick = compositor.CreateScalarKeyFrameAnimation();
            tick.InsertKeyFrame(0.0f, 0.0f, linear);
            tick.InsertKeyFrame(1.0f, kLoopSeconds, linear);
            tick.Duration(std::chrono::seconds(static_cast<int>(kLoopSeconds)));
            tick.IterationBehavior(wc::AnimationIterationBehavior::Forever);
            clock.StartAnimation(L"T", tick);
        }
    }

    void StopClock() noexcept {
        if (clockRunning_ && clockAnimated_ && clock) {
            try {
                clock.StopAnimation(L"T");
            } catch (...) {
            }
        }
        clockRunning_ = false;
    }

    // Advances a worker-driven clock by the time elapsed since the last tick,
    // multiplied by `rate` (1 = normal speed).
    void TickClock(double rate) {
        if (!clockRunning_ || clockAnimated_) {
            return;
        }
        auto now = std::chrono::steady_clock::now();
        double step = std::chrono::duration<double>(now - lastTick_).count();
        lastTick_ = now;
        step = std::clamp(step, 0.0, kMaxFrameStepSeconds);
        manualTime_ = std::fmod(manualTime_ + step * rate, static_cast<double>(kLoopSeconds));
        clock.InsertScalar(L"T", static_cast<float>(manualTime_));
        LARGE_INTEGER qpc;
        QueryPerformanceCounter(&qpc);
        manualQpc_ = qpc.QuadPart;
        lastRate_ = rate;
    }

    // What the wobble needs to rebuild the clock in another process.
    bool ClockAnimated() const { return clockAnimated_; }
    LONGLONG BaseQpc() const { return baseQpc_; }
    double ManualTime() const { return manualTime_; }
    LONGLONG ManualQpc() const { return manualQpc_; }
    double LastRate() const { return lastRate_; }

    // Current clock time, used to freeze and resume effects without a jump.
    // For the animated clock it's a CPU-side estimate.
    float ClockNow() const {
        if (!clockRunning_) {
            return 0.0f;
        }
        if (!clockAnimated_) {
            return static_cast<float>(manualTime_);
        }
        std::chrono::duration<double> elapsed = std::chrono::steady_clock::now() - clockStart_;
        return static_cast<float>(std::fmod(elapsed.count(), static_cast<double>(kLoopSeconds)));
    }

    // Optional, only used to follow targets across virtual desktops. Created
    // lazily and dropped on failure, so it recovers after an Explorer restart.
    VirtualDesktopManager* Desktops() {
        if (desktops_) {
            return desktops_.get();
        }
        ULONGLONG now = GetTickCount64();
        if (now < desktopsRetryAt_) {
            return nullptr;
        }
        HRESULT hr = CoCreateInstance(kVirtualDesktopManagerClsid, nullptr, CLSCTX_ALL,
                                      kVirtualDesktopManagerIid, desktops_.put_void());
        if (FAILED(hr)) {
            desktops_ = nullptr;
            desktopsRetryAt_ = now + kDesktopsRetryMs;
            if (!desktopsErrorLogged_) {
                Wh_Log(L"Virtual desktop manager unavailable: %08X", static_cast<unsigned>(hr));
                desktopsErrorLogged_ = true;
            }
            return nullptr;
        }
        return desktops_.get();
    }

    void ResetDesktops() {
        desktops_ = nullptr;
        desktopsRetryAt_ = GetTickCount64() + kDesktopsRetryMs;
    }

    void Release() noexcept {
        StopClock();
        clock = nullptr;
        for (auto& brush : glowBrushes) {
            brush = GradientBrush{};
        }
        for (auto& brush : beamBrushes) {
            brush = GradientBrush{};
        }
        gradientBrush = GradientBrush{};
        orbBrushes.clear();
        fadeIn = nullptr;
        desktops_ = nullptr;
        if (compositor) {
            try {
                compositor.Close();
            } catch (...) {
            }
            compositor = nullptr;
        }
    }

   private:
    static void Tint(GradientBrush& target, Color color, float alpha,
                     std::initializer_list<float> factors) {
        size_t i = 0;
        for (float factor : factors) {
            if (i >= target.stops.size()) {
                break;
            }
            color.A = static_cast<uint8_t>(std::clamp(alpha * factor + 0.5f, 0.0f, 255.0f));
            target.stops[i++].Color(color);
        }
    }

    // Soft disc: full color in the middle, fading out to the edge.
    GradientBrush MakeRadialBrush() {
        GradientBrush result;
        auto brush = compositor.CreateRadialGradientBrush();
        brush.EllipseCenter({0.5f, 0.5f});
        brush.EllipseRadius({0.5f, 0.5f});
        for (float offset : {0.0f, 0.55f, 1.0f}) {
            auto stop = compositor.CreateColorGradientStop();
            stop.Offset(offset);
            brush.ColorStops().Append(stop);
            result.stops.push_back(stop);
        }
        result.brush = brush;
        return result;
    }

    // Color 1 on the left edge to color 2 on the right edge.
    GradientBrush MakeLinearBrush() {
        GradientBrush result;
        auto brush = compositor.CreateLinearGradientBrush();
        brush.StartPoint({0.0f, 0.0f});
        brush.EndPoint({1.0f, 0.0f});
        for (float offset : {0.0f, 1.0f}) {
            auto stop = compositor.CreateColorGradientStop();
            stop.Offset(offset);
            brush.ColorStops().Append(stop);
            result.stops.push_back(stop);
        }
        result.brush = brush;
        return result;
    }

    // Beam: bright core fading to the sides, masked so it also fades out
    // along its length, away from the source.
    GradientBrush MakeBeamBrush() {
        GradientBrush result;
        auto across = compositor.CreateLinearGradientBrush();
        across.StartPoint({0.0f, 0.0f});
        across.EndPoint({1.0f, 0.0f});
        for (float offset : {0.0f, 0.35f, 0.5f, 0.65f, 1.0f}) {
            auto stop = compositor.CreateColorGradientStop();
            stop.Offset(offset);
            across.ColorStops().Append(stop);
            result.stops.push_back(stop);
        }

        Color opaque{255, 255, 255, 255};
        Color clear{0, 255, 255, 255};
        auto along = compositor.CreateLinearGradientBrush();
        along.StartPoint({0.0f, 0.0f});
        along.EndPoint({0.0f, 1.0f});
        along.ColorStops().Append(compositor.CreateColorGradientStop(0.0f, opaque));
        along.ColorStops().Append(compositor.CreateColorGradientStop(1.0f, clear));

        auto mask = compositor.CreateMaskBrush();
        mask.Source(across);
        mask.Mask(along);
        result.brush = mask;
        return result;
    }

    std::chrono::steady_clock::time_point clockStart_{};
    std::chrono::steady_clock::time_point lastTick_{};
    double manualTime_ = 0.0;
    LONGLONG baseQpc_ = 0;
    LONGLONG manualQpc_ = 0;
    double lastRate_ = 1.0;
    bool clockRunning_ = false;
    bool clockAnimated_ = false;
    winrt::com_ptr<VirtualDesktopManager> desktops_;
    ULONGLONG desktopsRetryAt_ = 0;
    bool desktopsErrorLogged_ = false;
};

////////////////////////////////////////////////////////////////////////////////
// One effect window placed directly below a target window

class Backdrop {
   public:
    Backdrop(HWND target, DWORD targetPid, Resources& resources)
        : target_(target), targetPid_(targetPid), resources_(resources) {
        try {
            // Deliberately unowned: owned windows always stay above their owner.
            // WS_EX_LAYERED + WS_EX_TRANSPARENT makes it click-through for every
            // process. WS_EX_TRANSPARENT alone (or HTTRANSPARENT) only passes
            // clicks to windows of the same thread, so while the effect briefly
            // lags behind a moving window it would swallow clicks.
            window_ = CreateWindowExW(WS_EX_NOREDIRECTIONBITMAP | WS_EX_TOOLWINDOW |
                                          WS_EX_NOACTIVATE | WS_EX_TRANSPARENT |
                                          WS_EX_LAYERED,
                                      kClassName, L"", WS_POPUP, 0, 0, 1, 1, nullptr,
                                      nullptr, g_module, nullptr);
            if (!window_) {
                winrt::throw_last_error();
            }
            if (!SetLayeredWindowAttributes(window_, 0, 255, LWA_ALPHA)) {
                winrt::throw_last_error();
            }

            BOOL disableTransitions = TRUE;
            DwmSetWindowAttribute(window_, kDwmaTransitionsForceDisabled, &disableTransitions,
                                  sizeof(disableTransitions));
            COLORREF border = kColorNone;
            DwmSetWindowAttribute(window_, kDwmaBorderColor, &border, sizeof(border));

            winrt::com_ptr<DesktopInterop> interop;
            winrt::check_hresult(
                static_cast<::IUnknown*>(winrt::get_abi(resources_.compositor))
                    ->QueryInterface(kDesktopInteropIid, interop.put_void()));
            winrt::check_hresult(interop->CreateDesktopWindowTarget(
                window_, FALSE, winrt::put_abi(compositionTarget_)));

            root_ = resources_.compositor.CreateContainerVisual();
            compositionTarget_.Root(root_);

            // Per-window values read by the expressions: "Scale" is DPI / 96
            // and "T" this window's time, linked to the shared clock while live
            // and fixed while frozen.
            frozenTime_ = resources_.ClockNow();
            env_ = resources_.compositor.CreatePropertySet();
            env_.InsertScalar(L"Scale", scale_);
            env_.InsertScalar(L"T", frozenTime_);

            switch (g_settings.effect) {
                case Effect::Gradient:
                    BuildGradient();
                    break;
                case Effect::Glows:
                    BuildGlows();
                    break;
                case Effect::Beams:
                    BuildBeams();
                    break;
                case Effect::Orbs:
                    BuildOrbs();
                    break;
                case Effect::Waves:
                    BuildWaves();
                    break;
            }
        } catch (...) {
            // A constructor that throws doesn't run the destructor.
            Release();
            throw;
        }
    }

    ~Backdrop() { Release(); }

    Backdrop(Backdrop const&) = delete;
    Backdrop& operator=(Backdrop const&) = delete;

    DWORD TargetPid() const { return targetPid_; }
    bool Shown() const { return shown_; }
    bool Live() const { return live_; }
    float Offset() const { return offset_; }
    float Frozen() const { return frozenTime_; }
    // Set by the wobble on a window it is dragging: the wobble paints this
    // glow, and the real one must come back at once when the drag ends.
    bool InDrag() const { return GetPropW(target_, kGlowDragProp) != nullptr; }

    // Live: the effect follows the shared clock. Frozen: it stays still, and
    // later resumes from the same point. `now` is the shared clock time.
    void SetLive(bool live, float now) {
        if (live == live_) {
            return;
        }
        if (live) {
            // The first time, join the shared clock so windows stay in sync.
            float offset = neverLive_ ? 0.0f : WrapTime(now - frozenTime_);
            auto link = resources_.compositor.CreateExpressionAnimation(
                L"Mod(clock.T - offset + 2 * loop, loop)");
            link.SetReferenceParameter(L"clock", resources_.clock);
            link.SetScalarParameter(L"offset", offset);
            link.SetScalarParameter(L"loop", kLoopSeconds);
            env_.StartAnimation(L"T", link);
            offset_ = offset;
            neverLive_ = false;
        } else {
            frozenTime_ = WrapTime(now - offset_);
            env_.StopAnimation(L"T");
            env_.InsertScalar(L"T", frozenTime_);
        }
        live_ = live;
    }

    void Hide() {
        if (shown_ && window_) {
            ShowWindow(window_, SW_HIDE);
        }
        shown_ = false;
        settleUntil_ = 0;
    }

    // Returns true if the caller should refresh again after the settle delay.
    bool Update(ULONGLONG now) {
        DWORD cloaked = 0;
        if (FAILED(DwmGetWindowAttribute(target_, DWMWA_CLOAKED, &cloaked, sizeof(cloaked)))) {
            cloaked = 0;
        }
        if (!IsWindow(target_) || !IsWindowVisible(target_) || IsIconic(target_) || cloaked) {
            Hide();
            zoomState_ = -1;
            return false;
        }

        RECT rect{};
        if (FAILED(DwmGetWindowAttribute(target_, DWMWA_EXTENDED_FRAME_BOUNDS, &rect,
                                         sizeof(rect))) ||
            IsRectEmpty(&rect)) {
            if (!GetWindowRect(target_, &rect)) {
                Hide();
                return false;
            }
        }

        // A maximized window extends past its monitor; only the work area is
        // visible, so never let the effect spill onto a neighbor monitor or the
        // taskbar.
        int zoomed = IsZoomed(target_) ? 1 : 0;
        if (zoomed) {
            MONITORINFO info{};
            info.cbSize = sizeof(info);
            if (GetMonitorInfoW(MonitorFromWindow(target_, MONITOR_DEFAULTTONEAREST), &info)) {
                IntersectRect(&rect, &rect, &info.rcWork);
            }
        }

        int width = rect.right - rect.left;
        int height = rect.bottom - rect.top;
        if (width <= 0 || height <= 0) {
            Hide();
            return false;
        }

        // DWM animates maximize/restore after the window already has its final
        // rectangle. Hide during the animation instead of showing the effect
        // early.
        if (shown_ && zoomState_ != -1 && zoomed != zoomState_) {
            zoomState_ = zoomed;
            Hide();
            settleUntil_ = now + kSettleDelayMs;
            return true;
        }
        zoomState_ = zoomed;

        // Same for opening and restoring from the taskbar. Not after a
        // wobble drag: the wobble showed the glow all along.
        bool handoff = InDrag();
        if (!shown_ && !handoff) {
            if (!settleUntil_) {
                settleUntil_ = now + kSettleDelayMs;
            }
            if (now < settleUntil_) {
                return true;
            }
        }

        int corner = zoomed ? kCornerDoNotRound : kCornerRound;
        if (corner != cornerState_) {
            DwmSetWindowAttribute(window_, kDwmaWindowCornerPreference, &corner, sizeof(corner));
            cornerState_ = corner;
        }

        // The worker thread is per-monitor DPI aware, so rect is in physical
        // pixels and the monitor DPI is the right scale for sizes in DIP.
        UINT dpiX = 96;
        UINT dpiY = 96;
        if (FAILED(GetDpiForMonitor(MonitorFromRect(&rect, MONITOR_DEFAULTTONEAREST),
                                    MDT_EFFECTIVE_DPI, &dpiX, &dpiY)) ||
            !dpiX) {
            dpiX = 96;
        }
        float scale = static_cast<float>(dpiX) / 96.0f;
        if (scale != scale_) {
            env_.InsertScalar(L"Scale", scale);
            scale_ = scale;
        }

        // Every sprite size and position is an expression of the root size, so
        // resizing the root is all a layout change needs.
        float w = static_cast<float>(width);
        float h = static_cast<float>(height);
        auto rootSize = root_.Size();
        if (rootSize.x != w || rootSize.y != h) {
            root_.Size({w, h});
        }

        bool wasShown = shown_;
        if (handoff) {
            root_.StopAnimation(L"Opacity");
            root_.Opacity(1.0f);
        } else if (!wasShown) {
            root_.Opacity(0.0f);
            root_.StartAnimation(L"Opacity", resources_.fadeIn);
        }

        bool moved = !EqualRect(&rect, &bounds_);
        bool orderChanged = GetWindow(target_, GW_HWNDNEXT) != window_;
        if (moved || orderChanged || !wasShown) {
            if (!SetWindowPos(window_, target_, rect.left, rect.top, width, height,
                              SWP_NOACTIVATE | SWP_NOOWNERZORDER | SWP_SHOWWINDOW)) {
                return false;
            }
            bounds_ = rect;
        }
        shown_ = true;
        settleUntil_ = 0;

        SyncVirtualDesktop();
        return false;
    }

   private:
    wc::SpriteVisual AddSprite(wc::CompositionBrush const& brush) {
        auto sprite = resources_.compositor.CreateSpriteVisual();
        sprite.Brush(brush);
        root_.Children().InsertAtTop(sprite);
        sprites_.push_back(sprite);
        return sprite;
    }

    // Starts an expression on a sprite property. Every expression can use
    // "area" (the window), "env" (per-window values, env.T is the time in
    // seconds) and "blob" (the sprite itself).
    // Extra references must be set before starting: they aren't picked up later.
    void Animate(wc::SpriteVisual const& sprite, PCWSTR property, PCWSTR expression,
                 std::initializer_list<std::pair<PCWSTR, float>> values,
                 std::initializer_list<std::pair<PCWSTR, wc::CompositionObject>> references = {}) {
        auto animation = resources_.compositor.CreateExpressionAnimation(expression);
        animation.SetReferenceParameter(L"area", root_);
        animation.SetReferenceParameter(L"env", env_);
        animation.SetReferenceParameter(L"blob", sprite);
        for (auto const& [name, value] : values) {
            animation.SetScalarParameter(name, value);
        }
        for (auto const& [name, object] : references) {
            animation.SetReferenceParameter(name, object);
        }
        sprite.StartAnimation(property, animation);
    }

    // One square, as wide as the window's diagonal so it always covers the
    // window, turning slowly about the window's center.
    void BuildGradient() {
        auto sprite = AddSprite(resources_.gradientBrush.brush);
        Animate(sprite, L"Size", L"Vector2(Length(area.Size), Length(area.Size))", {});
        Animate(sprite, L"Offset",
                L"Vector3((area.Size.X - blob.Size.X) * 0.5, (area.Size.Y - blob.Size.Y) * 0.5, 0)",
                {});
        Animate(sprite, L"CenterPoint", L"Vector3(blob.Size.X * 0.5, blob.Size.Y * 0.5, 0)", {});
        Animate(sprite, L"RotationAngleInDegrees", L"angle + sweep * Sin(env.T * omega)",
                {{L"angle", kGradientAngle},
                 {L"sweep", kGradientSweep},
                 {L"omega", GradientFrequency(g_settings.seconds)}});
    }

    // Each glow travels left and right at constant speed along a triangle wave
    // of period 2 (0 -> 1 -> 0), starting a third of the way apart.
    void BuildGlows() {
        float base = static_cast<float>(g_settings.diameter);
        for (size_t i = 0; i < 3; i++) {
            float roundTrip = static_cast<float>(g_settings.seconds) + 1.7f * i;
            auto sprite = AddSprite(resources_.glowBrushes[i].brush);
            Animate(sprite, L"Size",
                    L"Vector2(base * env.Scale, Max(base * env.Scale, area.Size.Y * 1.8))",
                    {{L"base", base}});
            Animate(sprite, L"Offset",
                    L"Vector3(area.Size.X * (1 - Abs(Mod(phase + rate * env.T, 2) - 1)) - "
                    L"blob.Size.X * 0.5, (area.Size.Y - blob.Size.Y) * 0.5, 0)",
                    {{L"phase", static_cast<float>(i) / 3.0f},
                     {L"rate", QuantizeVelocity(2.0f / roundTrip, 2.0f)}});
        }
    }

    // Beams start at evenly spaced points on one edge, fan out slightly and
    // sweep back and forth around their source point.
    void BuildBeams() {
        auto const& s = g_settings;
        float base = static_cast<float>(s.diameter);
        int count = s.beamCount;
        for (int k = 0; k < count; k++) {
            float t = (static_cast<float>(k) + 0.5f) / static_cast<float>(count);
            float ax = 0, ay = 0, heading = 0, fan = 0;
            switch (s.beamOrigin) {
                case Origin::Top:
                    ax = t, ay = 0, heading = 0, fan = (t - 0.5f) * 30.0f;
                    break;
                case Origin::Bottom:
                    ax = t, ay = 1, heading = 180, fan = (0.5f - t) * 30.0f;
                    break;
                case Origin::Left:
                    ax = 0, ay = t, heading = -90, fan = (0.5f - t) * 30.0f;
                    break;
                case Origin::Right:
                    ax = 1, ay = t, heading = 90, fan = (t - 0.5f) * 30.0f;
                    break;
            }

            auto sprite = AddSprite(resources_.beamBrushes[k % 3].brush);
            Animate(sprite, L"Size", L"Vector2(base * env.Scale * 0.5, Length(area.Size) * 1.25)",
                    {{L"base", base}});
            // The pivot is the middle of the beam's source end.
            Animate(sprite, L"CenterPoint", L"Vector3(blob.Size.X * 0.5, 0, 0)", {});
            Animate(sprite, L"Offset",
                    L"Vector3(ax * area.Size.X - blob.Size.X * 0.5, ay * area.Size.Y, 0)",
                    {{L"ax", ax}, {L"ay", ay}});
            Animate(sprite, L"RotationAngleInDegrees", L"heading + sweep * Sin(env.T * omega + phase)",
                    {{L"heading", heading + fan},
                     {L"sweep", static_cast<float>(s.beamSweep)},
                     {L"omega", LoopFrequency(s.seconds * (1.0f + 0.23f * k))},
                     {L"phase", 2.4f * k}});
        }
    }

    // Orbs move in straight lines. Positions are in "periods": with bounce, a
    // triangle wave of period 2 maps them back and forth between the edges;
    // with wrap, the fractional part maps them across and around.
    void BuildOrbs() {
        auto const& s = g_settings;
        float base = static_cast<float>(s.diameter);
        bool wrap = s.orbEdges == Edges::Wrap;
        float period = wrap ? 1.0f : 2.0f;
        PCWSTR offset =
            wrap ? L"Vector3("
                   L"(area.Size.X + blob.Size.X) * Mod(Mod(sx + vx * env.T, 1) + 1, 1) - "
                   L"blob.Size.X, "
                   L"(area.Size.Y + blob.Size.Y) * Mod(Mod(sy + vy * env.T, 1) + 1, 1) - "
                   L"blob.Size.Y, 0)"
                 : L"Vector3("
                   L"(area.Size.X - blob.Size.X) * Abs(Mod(Abs(sx + vx * env.T), 2) - 1), "
                   L"(area.Size.Y - blob.Size.Y) * Abs(Mod(Abs(sy + vy * env.T), 2) - 1), 0)";

        for (size_t j = 0; j < s.orbs.size() && j < resources_.orbBrushes.size(); j++) {
            auto const& orb = s.orbs[j];
            // One full back-and-forth (bounce) or crossing (wrap) per cycle at
            // 100% speed.
            float speed = period / static_cast<float>(s.seconds) * orb.speed / 100.0f;
            float radians = static_cast<float>(orb.angle) * kPi / 180.0f;
            float vx = QuantizeVelocity(std::cos(radians) * speed, period);
            float vy = QuantizeVelocity(-std::sin(radians) * speed, period);  // Screen y is down.
            float fj = static_cast<float>(j);

            auto sprite = AddSprite(resources_.orbBrushes[j].brush);
            Animate(sprite, L"Size", L"Vector2(base * env.Scale, base * env.Scale)",
                    {{L"base", base}});
            Animate(sprite, L"Offset", offset,
                    {{L"sx", Frac(0.21f + 0.618034f * fj) * period},
                     {L"sy", Frac(0.67f + 0.381966f * fj) * period},
                     {L"vx", vx},
                     {L"vy", vy}});
        }
    }

    // Each wave is a row of overlapping soft discs whose heights follow a
    // traveling sine; behind the blur they merge into one flowing band.
    void BuildWaves() {
        auto const& s = g_settings;
        float base = static_cast<float>(s.diameter);
        float amplitude = s.waveAmplitude / 100.0f;
        float spatial = kTwoPi / (s.waveLength / 100.0f);
        float span = 1.1f * 2.4f / static_cast<float>(kWaveBlobs - 1);
        for (int k = 0; k < kWaveCount; k++) {
            float direction = k % 2 ? -1.0f : 1.0f;
            float w = direction * LoopFrequency(s.seconds * (1.0f + 0.25f * k));
            for (int j = 0; j < kWaveBlobs; j++) {
                float x = -0.05f + 1.1f * static_cast<float>(j) / (kWaveBlobs - 1);
                auto sprite = AddSprite(resources_.glowBrushes[k].brush);
                Animate(sprite, L"Size", L"Vector2(area.Size.X * span, base * env.Scale * 0.6)",
                        {{L"span", span}, {L"base", base}});
                Animate(sprite, L"Offset",
                        L"Vector3(area.Size.X * px - blob.Size.X * 0.5, "
                        L"area.Size.Y * (py + amp * Sin(kx * px - omega * env.T + phase)) - "
                        L"blob.Size.Y * 0.5, 0)",
                        {{L"px", x},
                         {L"py", 0.3f + 0.2f * k},
                         {L"amp", amplitude},
                         {L"kx", spatial},
                         {L"omega", w},
                         {L"phase", 1.9f * k}});
            }
        }
    }

    // The effect window belongs to the virtual desktop it was created on. If
    // the shell cloaks it because the target lives on another desktop, move it.
    void SyncVirtualDesktop() {
        // Cheap local check first: the cross-process COM call below only runs
        // when the shell actually cloaked the effect window.
        DWORD ownCloak = 0;
        if (FAILED(DwmGetWindowAttribute(window_, DWMWA_CLOAKED, &ownCloak, sizeof(ownCloak))) ||
            !(ownCloak & kCloakedShell)) {
            return;
        }
        VirtualDesktopManager* desktops = resources_.Desktops();
        if (!desktops) {
            return;
        }
        GUID desktop{};
        GUID none{};
        HRESULT hr = desktops->GetWindowDesktopId(target_, &desktop);
        if (SUCCEEDED(hr) && !IsEqualGUID(desktop, none)) {
            hr = desktops->MoveWindowToDesktop(window_, desktop);
        }
        if (FAILED(hr)) {
            // Typically a stale proxy after Explorer restarted.
            resources_.ResetDesktops();
        }
    }

    void Release() noexcept {
        try {
            for (auto const& sprite : sprites_) {
                sprite.StopAnimation(L"Offset");
                sprite.StopAnimation(L"Size");
                sprite.StopAnimation(L"CenterPoint");
                sprite.StopAnimation(L"RotationAngleInDegrees");
            }
            if (env_) {
                env_.StopAnimation(L"T");
            }
            if (root_) {
                root_.StopAnimation(L"Opacity");
                root_.Children().RemoveAll();
            }
            if (compositionTarget_) {
                compositionTarget_.Root(nullptr);
            }
        } catch (...) {
        }
        sprites_.clear();
        env_ = nullptr;
        root_ = nullptr;
        compositionTarget_ = nullptr;
        if (window_) {
            DestroyWindow(window_);
            window_ = nullptr;
        }
    }

    HWND target_;
    DWORD targetPid_;
    Resources& resources_;
    HWND window_ = nullptr;
    wc::Desktop::DesktopWindowTarget compositionTarget_{nullptr};
    wc::ContainerVisual root_{nullptr};
    wc::CompositionPropertySet env_{nullptr};
    std::vector<wc::SpriteVisual> sprites_;
    float scale_ = 1.0f;
    float frozenTime_ = 0.0f;
    float offset_ = 0.0f;
    bool live_ = false;
    bool neverLive_ = true;
    RECT bounds_{};
    bool shown_ = false;
    int cornerState_ = -1;
    int zoomState_ = -1;
    ULONGLONG settleUntil_ = 0;
};

////////////////////////////////////////////////////////////////////////////////
// Worker state. Everything below runs on the worker thread only.

// Holding the process handle keeps the PID from being reused by another
// process while its name is cached.
class ProcessEntry {
   public:
    ProcessEntry() = default;
    ~ProcessEntry() {
        if (handle_) {
            CloseHandle(handle_);
        }
    }
    ProcessEntry(ProcessEntry const&) = delete;
    ProcessEntry& operator=(ProcessEntry const&) = delete;

    void Open(DWORD pid);
    bool IsOpen() const { return handle_ != nullptr; }
    std::wstring const& Name() const { return name_; }
    // The product name from the program's version info as "<product>.exe" (Helium's
    // chrome.exe gives helium.exe); empty when it has none or it equals Name().
    std::wstring const& Alias() const { return alias_; }

   private:
    HANDLE handle_ = nullptr;
    std::wstring name_;
    std::wstring alias_;
};

// Peak level of the default output device: the value behind the bar in the
// Windows volume mixer. No audio data is captured.
class AudioMeter {
   public:
    // 0 to 1; 0 when there's no output device or it can't be read.
    float Peak() {
        if (!meter_ && !Connect()) {
            return 0.0f;
        }
        float peak = 0.0f;
        if (FAILED(meter_->GetPeakValue(&peak))) {
            Disconnect();  // Device removed or disabled.
            return 0.0f;
        }
        return std::clamp(peak, 0.0f, 1.0f);
    }

    // Follows a change of the default device (headphones plugged in, and so
    // on). Called from the periodic refresh, only while connected.
    void CheckDefaultDevice() {
        if (meter_ && DefaultDeviceId() != deviceId_) {
            Disconnect();
            retryAt_ = 0;  // Reconnect on the next read.
        }
    }

    // COM objects must be released before the apartment goes away.
    void Release() noexcept {
        meter_ = nullptr;
        enumerator_ = nullptr;
        deviceId_.clear();
        retryAt_ = 0;
    }

   private:
    bool Connect() {
        ULONGLONG now = GetTickCount64();
        if (now < retryAt_) {
            return false;
        }
        retryAt_ = now + kAudioRetryMs;

        HRESULT hr = S_OK;
        if (!enumerator_) {
            hr = CoCreateInstance(kMMDeviceEnumeratorClsid, nullptr, CLSCTX_ALL,
                                  kMMDeviceEnumeratorIid, enumerator_.put_void());
        }
        winrt::com_ptr<IMMDevice> device;
        if (SUCCEEDED(hr)) {
            hr = enumerator_->GetDefaultAudioEndpoint(eRender, eMultimedia, device.put());
        }
        if (SUCCEEDED(hr)) {
            hr = device->Activate(kAudioMeterInformationIid, CLSCTX_ALL, nullptr,
                                  meter_.put_void());
        }
        if (FAILED(hr)) {
            meter_ = nullptr;
            // No output device at all is normal: don't log it.
            if (hr != HRESULT_FROM_WIN32(ERROR_NOT_FOUND) && !errorLogged_) {
                Wh_Log(L"Audio level unavailable: %08X", static_cast<unsigned>(hr));
                errorLogged_ = true;
            }
            return false;
        }
        deviceId_ = DeviceId(device.get());
        Wh_Log(L"Audio level: reading the default output device");
        return true;
    }

    void Disconnect() {
        meter_ = nullptr;
        deviceId_.clear();
    }

    static std::wstring DeviceId(IMMDevice* device) {
        LPWSTR id = nullptr;
        std::wstring result;
        if (SUCCEEDED(device->GetId(&id)) && id) {
            result = id;
            CoTaskMemFree(id);
        }
        return result;
    }

    std::wstring DefaultDeviceId() {
        winrt::com_ptr<IMMDevice> device;
        if (!enumerator_ ||
            FAILED(enumerator_->GetDefaultAudioEndpoint(eRender, eMultimedia, device.put()))) {
            return {};
        }
        return DeviceId(device.get());
    }

    winrt::com_ptr<IMMDeviceEnumerator> enumerator_;
    winrt::com_ptr<AudioMeterInformation> meter_;
    std::wstring deviceId_;
    ULONGLONG retryAt_ = 0;
    bool errorLogged_ = false;
};

// Conditions read from Windows on every refresh.
struct PowerState {
    bool freeze = false;  // Keep effects visible but still.
    bool hide = false;    // Remove effects: they couldn't be seen anyway.
};

// When a wobble was last seen (its overlay up, or a glowing window cloaked or
// uncloaked by a drag). Windows keeps reporting "busy" for a moment after the
// overlay hides, so a refresh right after a drag would freeze the glow.
std::atomic<ULONGLONG> g_wobbleSeenAt{0};
constexpr ULONGLONG kWobbleGraceMs = 3000;

bool WobbleOverlayExists(bool* visible) {
    HWND overlay = FindWindowW(L"SeamlessWobblyOverlay", nullptr);
    if (visible) {
        *visible = overlay && IsWindowVisible(overlay);
    }
    return overlay != nullptr;
}

PowerState QueryPowerState() {
    auto const& power = g_settings.power;
    PowerState state;

    if (power.transparency) {
        DWORD value = 1;
        DWORD size = sizeof(value);
        if (RegGetValueW(HKEY_CURRENT_USER,
                         L"Software\\Microsoft\\Windows\\CurrentVersion\\Themes\\Personalize",
                         L"EnableTransparency", RRF_RT_REG_DWORD, nullptr, &value,
                         &size) == ERROR_SUCCESS &&
            value == 0) {
            state.hide = true;
        }
    }

    if (power.batterySaver) {
        SYSTEM_POWER_STATUS status{};
        // The 4th byte is SystemStatusFlag (named Reserved1 in older headers):
        // 1 means battery saver is on.
        if (GetSystemPowerStatus(&status) && reinterpret_cast<BYTE const*>(&status)[3] == 1) {
            state.freeze = true;
        }
    }

    if (power.reduceMotion) {
        BOOL animations = TRUE;
        if (SystemParametersInfoW(SPI_GETCLIENTAREAANIMATION, 0, &animations, 0) && !animations) {
            state.freeze = true;
        }
    }

    if (power.fullscreen) {
        QUERY_USER_NOTIFICATION_STATE notification{};
        if (SUCCEEDED(SHQueryUserNotificationState(&notification)) &&
            (notification == QUNS_BUSY || notification == QUNS_RUNNING_D3D_FULL_SCREEN ||
             notification == QUNS_PRESENTATION_MODE)) {
            // The wobble's overlay is a topmost window over every screen, so
            // Windows reports "busy" during each drag and for a moment after.
            // That is not a game.
            bool wobbling = false;
            WobbleOverlayExists(&wobbling);
            const ULONGLONG now = GetTickCount64();
            if (wobbling) {
                g_wobbleSeenAt.store(now);
            }
            const ULONGLONG seen = g_wobbleSeenAt.load();
            const bool recent = seen != 0 && now - seen < kWobbleGraceMs;
            if (!((wobbling || recent) && notification == QUNS_BUSY)) {
                state.freeze = true;
            }
        }
    }

    return state;
}

struct Worker {
    Resources resources;  // Declared first: destroyed after the backdrops.
    std::unordered_map<HWND, std::unique_ptr<Backdrop>> backdrops;
    std::unordered_set<HWND> failed;
    std::unordered_map<DWORD, ProcessEntry> processes;
    HWND controller = nullptr;
    PowerState power;
    AudioMeter meter;
    double audioLevel = 0.0;  // Smoothed, 0 to 1.
    std::chrono::steady_clock::time_point audioSampledAt{};
    ULONGLONG failedResetAt = 0;
    bool refreshQueued = false;
    bool settingsPending = false;
    bool busy = false;
};

Worker* g_worker = nullptr;

struct BusyScope {
    explicit BusyScope(bool& flag) : flag_(flag) { flag_ = true; }
    ~BusyScope() { flag_ = false; }
    BusyScope(BusyScope const&) = delete;
    BusyScope& operator=(BusyScope const&) = delete;

   private:
    bool& flag_;
};

void QueueRefresh(Worker& worker) {
    if (worker.refreshQueued || !worker.controller) {
        return;
    }
    if (PostMessageW(worker.controller, kRefreshMessage, 0, 0)) {
        worker.refreshQueued = true;
    }
}

void ArmSettleTimer(Worker& worker) {
    if (worker.controller) {
        SetTimer(worker.controller, kSettleTimerId, kSettleDelayMs + 20, nullptr);
    }
}

// The compositor can't change the speed of a running animation, so with audio
// reactivity (or reduced smoothness) the worker advances the clock itself.
void StartClock(Worker& worker) {
    auto const& s = g_settings;
    bool workerDriven = s.reducedSmoothness || s.audio.reactive;
    worker.resources.StartClock(!workerDriven);
    worker.audioLevel = 0.0;
    worker.audioSampledAt = std::chrono::steady_clock::now();
    if (workerDriven && worker.controller) {
        SetTimer(worker.controller, kFrameTimerId,
                 s.reducedSmoothness ? kReducedFrameIntervalMs : kFrameIntervalMs, nullptr);
    }
}

// Clock speed for this frame: 1 in silence, up to "Cycle duration" divided by
// "Cycle duration at full volume" at the loudest level.
double ClockRate(Worker& worker) {
    auto const& s = g_settings;
    if (!s.audio.reactive) {
        return 1.0;
    }

    auto now = std::chrono::steady_clock::now();
    double step = std::chrono::duration<double>(now - worker.audioSampledAt).count();
    worker.audioSampledAt = now;
    step = std::clamp(step, 0.0, kMaxFrameStepSeconds);

    // The square root follows loudness as heard more closely than the raw
    // peak, so music at a normal or low volume still visibly speeds things up.
    double target = std::clamp(std::sqrt(static_cast<double>(worker.meter.Peak())) *
                                   s.audio.sensitivity / 100.0,
                               0.0, 1.0);
    double smoothing = target > worker.audioLevel ? kAudioAttackSeconds : kAudioReleaseSeconds;
    worker.audioLevel += (target - worker.audioLevel) * (1.0 - std::exp(-step / smoothing));

    double duration =
        s.seconds + (s.audio.fastestSeconds - s.seconds) * worker.audioLevel;
    return s.seconds / std::max(duration, 0.5);
}

void StopClock(Worker& worker) {
    if (worker.controller) {
        KillTimer(worker.controller, kFrameTimerId);
    }
    worker.resources.StopClock();
}

// Shared with the wobble in app processes, so the glow it paints during a drag
// runs on this clock and lines up with the real glow when the window lands.
HANDLE g_sharedMap = nullptr;
GlowShared* g_shared = nullptr;

// The watch field (see kGlowWatchProp). Bits 0-3: the BasicReject code.
constexpr uint32_t kWatchRejectMask = 0x0000000F;
constexpr uint32_t kWatchNotSeen = 0x00000010;       // not in the last EnumWindows
constexpr uint32_t kWatchNamed = 0x00000020;         // its process name was read
constexpr uint32_t kWatchMatched = 0x00000040;       // the mode and lists want it
constexpr uint32_t kWatchSkipped = 0x00000080;       // window limit or failed list
constexpr uint32_t kWatchCantCreate = 0x00000100;    // hidden, cloaked or too small
constexpr uint32_t kWatchHasEffect = 0x00000200;
constexpr uint32_t kWatchThrew = 0x00000400;         // creating its effect failed
constexpr uint32_t kWatchNoCompositor = 0x00000800;
constexpr uint32_t kWatchHidden = 0x00001000;        // power settings hide every effect
constexpr uint32_t kWatchFrozen = 0x00002000;
constexpr uint32_t kWatchPassOne = 0x00010000;       // bits 16-23 count refreshes
constexpr uint32_t kWatchPassMask = 0x00FF0000;      // bits 24-31: its backdrop type
HWND g_watch = nullptr;
uint32_t g_watchBits = kWatchNotSeen;

void OpenShared() {
    if (g_shared) {
        return;
    }
    // Readable by every process of the session, including low integrity
    // ones; writable only by this one (it holds the creating handle).
    PSECURITY_DESCRIPTOR sd = nullptr;
    SECURITY_ATTRIBUTES sa{sizeof(sa), nullptr, FALSE};
    if (ConvertStringSecurityDescriptorToSecurityDescriptorW(
            L"D:(A;;GR;;;WD)(A;;GA;;;SY)(A;;GA;;;BA)S:(ML;;NW;;;LW)", SDDL_REVISION_1, &sd,
            nullptr)) {
        sa.lpSecurityDescriptor = sd;
    }
    g_sharedMap = CreateFileMappingW(INVALID_HANDLE_VALUE, &sa, PAGE_READWRITE, 0,
                                     sizeof(GlowShared), kGlowMapName);
    if (sd) {
        LocalFree(sd);
    }
    if (!g_sharedMap) {
        Wh_Log(L"Shared clock unavailable: %u", GetLastError());
        return;
    }
    g_shared = static_cast<GlowShared*>(
        MapViewOfFile(g_sharedMap, FILE_MAP_WRITE, 0, 0, sizeof(GlowShared)));
    if (!g_shared) {
        CloseHandle(g_sharedMap);
        g_sharedMap = nullptr;
    }
}

void ClearShared() {
    if (GlowShared* m = g_shared) {
        InterlockedIncrement(&m->seq);
        m->running = 0;
        m->count = 0;
        InterlockedIncrement(&m->seq);
    }
}

void CloseShared() {
    ClearShared();
    if (g_shared) {
        UnmapViewOfFile(g_shared);
        g_shared = nullptr;
    }
    if (g_sharedMap) {
        CloseHandle(g_sharedMap);
        g_sharedMap = nullptr;
    }
}

// Seqlock: odd while writing. The Interlocked calls are full barriers.
void PublishShared(Worker& worker) {
    GlowShared* m = g_shared;
    if (!m) {
        return;
    }
    auto const& r = worker.resources;
    InterlockedIncrement(&m->seq);
    m->version = kGlowMapVersion;
    m->running = r.ClockRunning() ? 1 : 0;
    m->animated = r.ClockAnimated() ? 1 : 0;
    m->baseQpc = r.BaseQpc();
    m->manualTime = r.ManualTime();
    m->manualQpc = r.ManualQpc();
    m->rate = r.LastRate();
    uint32_t n = 0;
    for (auto const& [hwnd, backdrop] : worker.backdrops) {
        if (n >= static_cast<uint32_t>(kGlowMaxEntries)) {
            break;
        }
        m->e[n++] = {static_cast<uint32_t>(reinterpret_cast<UINT_PTR>(hwnd)),
                     backdrop->Live() ? 1u : 0u, backdrop->Offset(), backdrop->Frozen()};
    }
    m->count = n;
    m->watch = g_watchBits;
    InterlockedIncrement(&m->seq);
}

// Decides which effects move. Hidden effects, and the ones the user or the
// power settings want still, are frozen; the clock runs only if needed.
void UpdateLiveness(Worker& worker) {
    auto const& s = g_settings;
    HWND foreground = GetForegroundWindow();
    HWND foregroundRoot = foreground ? GetAncestor(foreground, GA_ROOTOWNER) : nullptr;

    std::vector<std::pair<Backdrop*, bool>> states;
    states.reserve(worker.backdrops.size());
    bool anyLive = false;
    for (auto const& [hwnd, backdrop] : worker.backdrops) {
        // A window being wobbled is cloaked, so its glow is hidden, but the
        // wobble paints it from this clock: keep it moving.
        bool shown = backdrop->Shown() || backdrop->InDrag();
        bool live = !worker.power.freeze && s.animate != Animate::None && shown &&
                    (s.animate == Animate::All || hwnd == foreground || hwnd == foregroundRoot);
        anyLive = anyLive || live;
        states.emplace_back(backdrop.get(), live);
    }

    if (anyLive && !worker.resources.ClockRunning()) {
        StartClock(worker);
    }
    // Freeze before the clock can stop: freezing reads the current time.
    float now = worker.resources.ClockNow();
    for (auto const& [backdrop, live] : states) {
        if (!live) {
            backdrop->SetLive(false, now);
        }
    }
    for (auto const& [backdrop, live] : states) {
        if (live) {
            backdrop->SetLive(true, now);
        }
    }
    if (!anyLive && worker.resources.ClockRunning()) {
        StopClock(worker);
    }
    PublishShared(worker);
}

std::wstring QueryProcessPath(HANDLE process) {
    std::wstring path(MAX_PATH, L'\0');
    DWORD size = static_cast<DWORD>(path.size());
    BOOL ok = QueryFullProcessImageNameW(process, 0, path.data(), &size);
    if (!ok && GetLastError() == ERROR_INSUFFICIENT_BUFFER) {
        path.assign(32768, L'\0');
        size = static_cast<DWORD>(path.size());
        ok = QueryFullProcessImageNameW(process, 0, path.data(), &size);
    }
    if (!ok) {
        return {};
    }
    path.resize(size);
    return path;
}

// version.dll is loaded on first use; read once per new process.
std::wstring QueryProductAlias(std::wstring const& path) {
    using SizeFn = DWORD(WINAPI*)(LPCWSTR, LPDWORD);
    using InfoFn = BOOL(WINAPI*)(LPCWSTR, DWORD, DWORD, LPVOID);
    using QueryFn = BOOL(WINAPI*)(LPCVOID, LPCWSTR, LPVOID*, PUINT);
    static HMODULE module = LoadLibraryExW(L"version.dll", nullptr, LOAD_LIBRARY_SEARCH_SYSTEM32);
    static auto getSize = module ? (SizeFn)GetProcAddress(module, "GetFileVersionInfoSizeW") : nullptr;
    static auto getInfo = module ? (InfoFn)GetProcAddress(module, "GetFileVersionInfoW") : nullptr;
    static auto query = module ? (QueryFn)GetProcAddress(module, "VerQueryValueW") : nullptr;
    if (!getSize || !getInfo || !query || path.empty()) {
        return {};
    }
    DWORD ignored = 0;
    DWORD size = getSize(path.c_str(), &ignored);
    if (!size || size > (1u << 20)) {
        return {};
    }
    std::vector<BYTE> data(size);
    if (!getInfo(path.c_str(), 0, size, data.data())) {
        return {};
    }
    struct Translation { WORD language, codePage; };
    Translation* list = nullptr;
    UINT bytes = 0;
    std::vector<Translation> tries;
    if (query(data.data(), L"\\VarFileInfo\\Translation", reinterpret_cast<LPVOID*>(&list), &bytes) && list) {
        tries.assign(list, list + bytes / sizeof(Translation));
    }
    tries.push_back({0x0409, 0x04B0});
    for (auto const& t : tries) {
        wchar_t key[64];
        swprintf_s(key, L"\\StringFileInfo\\%04x%04x\\ProductName", t.language, t.codePage);
        wchar_t* text = nullptr;
        UINT length = 0;
        if (query(data.data(), key, reinterpret_cast<LPVOID*>(&text), &length) && text && length) {
            std::wstring product = Trim(std::wstring(text), L" \t");
            if (product.empty() || product.find_first_of(L"\\/") != std::wstring::npos) {
                return {};
            }
            return ToLower(std::move(product)) + L".exe";
        }
    }
    return {};
}

void ProcessEntry::Open(DWORD pid) {
    handle_ = OpenProcess(PROCESS_QUERY_LIMITED_INFORMATION, FALSE, pid);
    if (handle_) {
        std::wstring path = QueryProcessPath(handle_);
        name_ = path.empty() ? std::wstring() : NormalizeProcessName(path);
        alias_ = QueryProductAlias(path);
        if (alias_ == name_) {
            alias_.clear();
        }
    }
}

// 0 when the window can carry an effect, otherwise which check turned it down
// (reported for a watched window, see kGlowWatchProp).
int BasicReject(Worker const& worker, HWND hwnd) {
    if (!hwnd || !IsWindow(hwnd) || GetAncestor(hwnd, GA_ROOT) != hwnd) {
        return 1;
    }

    // Ignore invisible helper windows, but keep tracked targets so minimizing
    // can hide their effect without recreating it.
    if (!IsWindowVisible(hwnd) && !worker.backdrops.count(hwnd)) {
        return 2;
    }

    DWORD pid = 0;
    GetWindowThreadProcessId(hwnd, &pid);
    if (!pid || pid == GetCurrentProcessId()) {
        return 3;
    }

    LONG_PTR style = GetWindowLongPtrW(hwnd, GWL_STYLE);
    LONG_PTR exStyle = GetWindowLongPtrW(hwnd, GWL_EXSTYLE);
    // Click-through windows are overlays, not app windows.
    if ((style & WS_CHILD) || (exStyle & (WS_EX_TOOLWINDOW | WS_EX_TRANSPARENT))) {
        return 4;
    }
    // Only app windows and dialogs: they have a caption or a sizing frame, or
    // stand on their own in the taskbar. Tooltips, menus, flyouts and drop-down
    // lists are borderless popups, usually owned or topmost, and never take
    // activation; an effect window behind them shows up as a stray shape.
    if (exStyle & WS_EX_NOACTIVATE) {
        return 5;
    }
    bool framed = (style & WS_CAPTION) == WS_CAPTION || (style & WS_THICKFRAME);
    bool owned = GetWindow(hwnd, GW_OWNER) != nullptr;
    if (!framed && !(exStyle & WS_EX_APPWINDOW) && (owned || (exStyle & WS_EX_TOPMOST))) {
        return 6;
    }
    if (exStyle & WS_EX_LAYERED) {
        BYTE alpha = 255;
        DWORD flags = 0;
        if (GetLayeredWindowAttributes(hwnd, nullptr, &alpha, &flags) && (flags & LWA_ALPHA) &&
            alpha == 0) {
            return 7;  // Fully transparent window.
        }
    }

    wchar_t className[256]{};
    if (!GetClassNameW(hwnd, className, ARRAYSIZE(className))) {
        return 8;
    }
    for (PCWSTR blocked : kExcludedClasses) {
        if (_wcsicmp(className, blocked) == 0) {
            return 9;
        }
    }
    return 0;
}

bool IsBasicCandidate(Worker const& worker, HWND hwnd) {
    return BasicReject(worker, hwnd) == 0;
}

bool Matches(HWND hwnd, ProcessEntry const& process) {
    std::wstring const& name = process.Name();
    std::wstring const& alias = process.Alias();
    auto inList = [&](std::vector<std::wstring> const& list) {
        return Contains(list, name) || (!alias.empty() && Contains(list, alias));
    };
    if (name.empty() || inList(g_settings.exclude)) {
        return false;
    }

    bool listed = inList(g_settings.include);
    if (g_settings.mode == Mode::Selected) {
        return listed;
    }
    if (g_settings.mode == Mode::Combined && listed) {
        return true;
    }

    int backdropType = 0;
    return SUCCEEDED(DwmGetWindowAttribute(hwnd, kDwmaSystemBackdropType, &backdropType,
                                           sizeof(backdropType))) &&
           backdropType == kBackdropTransientWindow;
}

bool CanCreateFor(HWND hwnd) {
    if (!IsWindowVisible(hwnd) || IsIconic(hwnd)) {
        return false;
    }
    DWORD cloaked = 0;
    if (FAILED(DwmGetWindowAttribute(hwnd, DWMWA_CLOAKED, &cloaked, sizeof(cloaked)))) {
        cloaked = 0;
    }
    if (cloaked) {
        return false;
    }
    // Skip tiny helper windows: a composition target each would be wasted.
    RECT rect{};
    if (!GetWindowRect(hwnd, &rect)) {
        return false;
    }
    return rect.right - rect.left >= kMinTargetSize && rect.bottom - rect.top >= kMinTargetSize;
}

struct EnumContext {
    Worker* worker;
    std::vector<HWND> targets;
    std::unordered_set<DWORD> seenPids;
};

BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM param) {
    auto& context = *reinterpret_cast<EnumContext*>(param);
    try {
        bool watched = GetPropW(hwnd, kGlowWatchProp) != nullptr;
        int reject = BasicReject(*context.worker, hwnd);
        if (watched) {
            g_watch = hwnd;
            g_watchBits = (g_watchBits & ~kWatchRejectMask & ~kWatchNotSeen) |
                          static_cast<uint32_t>(reject);
        }
        if (reject) {
            return TRUE;
        }
        DWORD pid = 0;
        GetWindowThreadProcessId(hwnd, &pid);
        context.seenPids.insert(pid);

        // Cached across refreshes; pruned when the PID is no longer seen.
        auto [it, inserted] = context.worker->processes.try_emplace(pid);
        if (inserted) {
            it->second.Open(pid);
        }
        bool match = Matches(hwnd, it->second);
        if (watched) {
            int backdropType = 0;
            DwmGetWindowAttribute(hwnd, kDwmaSystemBackdropType, &backdropType,
                                  sizeof(backdropType));
            g_watchBits |= (it->second.Name().empty() ? 0 : kWatchNamed) |
                           (match ? kWatchMatched : 0) |
                           (static_cast<uint32_t>(backdropType & 0xFF) << 24);
        }
        if (match) {
            context.targets.push_back(hwnd);
        }
    } catch (...) {
    }
    return TRUE;
}

void Refresh(Worker& worker) {
    if (worker.busy) {
        QueueRefresh(worker);
        return;
    }
    BusyScope scope(worker.busy);
    g_watch = nullptr;
    g_watchBits = kWatchNotSeen | ((g_watchBits + kWatchPassOne) & kWatchPassMask);

    // Composition resources are missing only after a failed settings change.
    if (!worker.resources.compositor) {
        g_watchBits |= kWatchNoCompositor;
        worker.backdrops.clear();
        worker.failed.clear();
        StopClock(worker);
        PublishShared(worker);
        return;
    }

    if (g_settings.audio.reactive && worker.resources.ClockRunning()) {
        worker.meter.CheckDefaultDevice();
    }

    worker.power = QueryPowerState();
    if (worker.power.freeze) {
        g_watchBits |= kWatchFrozen;
    }
    if (worker.power.hide) {
        g_watchBits |= kWatchHidden;
        worker.backdrops.clear();
        worker.failed.clear();
        StopClock(worker);
        PublishShared(worker);
        return;
    }

    EnumContext context{&worker, {}, {}};
    EnumWindows(EnumWindowsProc, reinterpret_cast<LPARAM>(&context));

    // Entries that couldn't be opened don't pin their PID, so they are never
    // trusted across refreshes and are simply queried again.
    for (auto it = worker.processes.begin(); it != worker.processes.end();) {
        if (context.seenPids.count(it->first) && it->second.IsOpen()) {
            ++it;
        } else {
            it = worker.processes.erase(it);
        }
    }

    std::unordered_set<HWND> wanted(context.targets.begin(), context.targets.end());

    for (auto it = worker.backdrops.begin(); it != worker.backdrops.end();) {
        DWORD pid = 0;
        GetWindowThreadProcessId(it->first, &pid);
        if (wanted.count(it->first) && pid == it->second->TargetPid()) {
            ++it;
        } else {
            it = worker.backdrops.erase(it);
        }
    }

    ULONGLONG now = GetTickCount64();
    if (now >= worker.failedResetAt) {
        // Transient failures (e.g. after a GPU reset) shouldn't be permanent.
        worker.failed.clear();
        worker.failedResetAt = now + kFailedRetryMs;
    }
    for (auto it = worker.failed.begin(); it != worker.failed.end();) {
        if (wanted.count(*it)) {
            ++it;
        } else {
            it = worker.failed.erase(it);
        }
    }

    // EnumWindows is in z-order, so when the limit is reached, existing effects
    // keep their slot and new windows nearer the top are served first.
    // If the limit was lowered, drop the effects lowest in z-order first.
    size_t limit = static_cast<size_t>(g_settings.maxWindows);
    for (auto it = context.targets.rbegin();
         it != context.targets.rend() && worker.backdrops.size() > limit; ++it) {
        worker.backdrops.erase(*it);
    }

    bool settle = false;
    for (HWND hwnd : context.targets) {
        bool watched = hwnd == g_watch;
        try {
            auto it = worker.backdrops.find(hwnd);
            if (it == worker.backdrops.end()) {
                if (worker.backdrops.size() >= limit || worker.failed.count(hwnd)) {
                    if (watched) {
                        g_watchBits |= kWatchSkipped;
                    }
                    continue;
                }
                if (!CanCreateFor(hwnd)) {
                    if (watched) {
                        g_watchBits |= kWatchCantCreate;
                    }
                    continue;
                }
                DWORD pid = 0;
                GetWindowThreadProcessId(hwnd, &pid);
                it = worker.backdrops
                         .emplace(hwnd, std::make_unique<Backdrop>(hwnd, pid, worker.resources))
                         .first;
                wchar_t className[128]{};
                GetClassNameW(hwnd, className, ARRAYSIZE(className));
                Wh_Log(L"Effect added to window %p (%s)", hwnd, className);
            }
            if (it->second->Update(now)) {
                settle = true;
            }
            if (watched) {
                g_watchBits |= kWatchHasEffect;
            }
        } catch (...) {
            // Don't retry every second and flood the log.
            Wh_Log(L"Can't show the effect for window %p: %08X", hwnd,
                   static_cast<unsigned>(winrt::to_hresult()));
            if (watched) {
                g_watchBits |= kWatchThrew;
            }
            worker.backdrops.erase(hwnd);
            worker.failed.insert(hwnd);
        }
    }

    UpdateLiveness(worker);

    if (settle) {
        ArmSettleTimer(worker);
    }
}

// A settings change that arrived while busy (for example dispatched by a COM
// modal loop during a cross-process call) is applied right after.
void FlushPendingSettings(Worker& worker) {
    if (worker.settingsPending && !worker.busy && worker.controller &&
        PostMessageW(worker.controller, kSettingsMessage, 0, 0)) {
        worker.settingsPending = false;
    }
}

void SafeRefresh(Worker& worker) {
    try {
        Refresh(worker);
    } catch (...) {
        Wh_Log(L"Refresh error: %08X", static_cast<unsigned>(winrt::to_hresult()));
    }
    FlushPendingSettings(worker);
}

void CALLBACK OnWinEvent(HWINEVENTHOOK, DWORD event, HWND hwnd, LONG idObject, LONG idChild,
                         DWORD, DWORD) {
    Worker* worker = g_worker;
    if (!worker || !hwnd || idObject != OBJID_WINDOW || idChild != CHILDID_SELF) {
        return;
    }

    try {
        auto it = worker->backdrops.find(hwnd);
        bool tracked = it != worker->backdrops.end();

        // The wobble cloaks a window for its drag and uncloaks it at the end.
        if (tracked && (event == EVENT_OBJECT_CLOAKED || event == EVENT_OBJECT_UNCLOAKED) &&
            WobbleOverlayExists(nullptr)) {
            g_wobbleSeenAt.store(GetTickCount64());
        }

        switch (event) {
            case EVENT_OBJECT_LOCATIONCHANGE:
                // Fast path: follow a tracked window without enumerating.
                if (!tracked) {
                    return;
                }
                if (worker->busy) {
                    QueueRefresh(*worker);
                    return;
                }
                {
                    BusyScope scope(worker->busy);
                    bool wasShown = it->second->Shown();
                    if (it->second->Update(GetTickCount64())) {
                        ArmSettleTimer(*worker);
                    }
                    if (it->second->Shown() != wasShown) {
                        QueueRefresh(*worker);  // Updates which effects move.
                    }
                }
                FlushPendingSettings(*worker);
                return;

            case EVENT_OBJECT_DESTROY:
            case EVENT_OBJECT_HIDE:
            case EVENT_OBJECT_CLOAKED:
            case EVENT_SYSTEM_MINIMIZESTART:
                if (tracked) {
                    if (!worker->busy) {
                        it->second->Hide();
                    }
                    QueueRefresh(*worker);
                }
                return;

            default:
                // Any foreground change matters: with "active window only" the
                // previous window must freeze even if the new one isn't ours.
                if (event == EVENT_SYSTEM_FOREGROUND || tracked ||
                    IsBasicCandidate(*worker, hwnd)) {
                    QueueRefresh(*worker);
                }
                return;
        }
    } catch (...) {
    }
}

void ApplySettings(Worker& worker) {
    try {
        Layout before = CurrentLayout();
        LoadSettings();
        worker.failed.clear();  // Give previously failed windows another chance.
        if (CurrentLayout() != before || !worker.resources.compositor) {
            // The shape of the effect changed: rebuild every effect window.
            // They fade back in after the usual settle delay.
            worker.backdrops.clear();
            StopClock(worker);
            worker.resources.Release();
            worker.resources.Create();
        } else {
            worker.resources.ApplyColors();
        }
        if (!g_settings.audio.reactive) {
            worker.meter.Release();
        }
        Wh_Log(L"Settings applied");
    } catch (...) {
        Wh_Log(L"Can't apply settings: %08X", static_cast<unsigned>(winrt::to_hresult()));
        // Leave a clean state: the next settings change rebuilds from scratch.
        worker.backdrops.clear();
        StopClock(worker);
        worker.resources.Release();
    }
    SafeRefresh(worker);
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    Worker* worker = g_worker;
    if (worker && hwnd == worker->controller) {
        if (msg == kSettingsMessage) {
            if (worker->busy) {
                worker->settingsPending = true;
            } else {
                ApplySettings(*worker);
            }
            return 0;
        }
        if (msg == kRefreshMessage) {
            worker->refreshQueued = false;
            SafeRefresh(*worker);
            return 0;
        }
        if (msg == WM_TIMER && wParam == kFrameTimerId) {
            // Reading the audio level is a COM call that may dispatch messages,
            // so the tick counts as busy like a refresh.
            if (!worker->busy) {
                {
                    BusyScope scope(worker->busy);
                    try {
                        worker->resources.TickClock(ClockRate(*worker));
                        PublishShared(*worker);
                    } catch (...) {
                    }
                }
                FlushPendingSettings(*worker);
            }
            return 0;
        }
        if (msg == WM_TIMER && (wParam == kPollTimerId || wParam == kSettleTimerId)) {
            if (wParam == kSettleTimerId) {
                KillTimer(hwnd, kSettleTimerId);
            }
            SafeRefresh(*worker);
            return 0;
        }
        return DefWindowProcW(hwnd, msg, wParam, lParam);
    }

    // Effect windows: never take clicks or activation.
    switch (msg) {
        case WM_NCHITTEST:
            return HTTRANSPARENT;
        case WM_MOUSEACTIVATE:
            return MA_NOACTIVATE;
    }
    return DefWindowProcW(hwnd, msg, wParam, lParam);
}

void RunMessageLoop() {
    for (;;) {
        DWORD result = MsgWaitForMultipleObjectsEx(1, &g_stopEvent, INFINITE, QS_ALLINPUT,
                                                   MWMO_INPUTAVAILABLE);
        if (result != WAIT_OBJECT_0 + 1) {
            return;  // Stop requested or wait failed.
        }
        MSG msg;
        while (PeekMessageW(&msg, nullptr, 0, 0, PM_REMOVE)) {
            if (msg.message == WM_QUIT) {
                return;
            }
            TranslateMessage(&msg);
            DispatchMessageW(&msg);
        }
    }
}

// Returns false if the queue may still be running.
bool ShutdownQueue(winrt::Windows::System::DispatcherQueueController const& queue) {
    using winrt::Windows::Foundation::AsyncStatus;
    try {
        auto operation = queue.ShutdownQueueAsync();
        ULONGLONG deadline = GetTickCount64() + 5000;
        while (operation.Status() == AsyncStatus::Started && GetTickCount64() < deadline) {
            MsgWaitForMultipleObjectsEx(0, nullptr, 50, QS_ALLINPUT, MWMO_INPUTAVAILABLE);
            MSG msg;
            while (PeekMessageW(&msg, nullptr, 0, 0, PM_REMOVE)) {
                TranslateMessage(&msg);
                DispatchMessageW(&msg);
            }
        }
        if (operation.Status() == AsyncStatus::Started) {
            Wh_Log(L"Dispatcher queue shutdown timed out");
            return false;
        }
        operation.GetResults();
    } catch (...) {
        Wh_Log(L"Dispatcher queue shutdown error: %08X",
               static_cast<unsigned>(winrt::to_hresult()));
    }
    return true;
}

DWORD WINAPI WorkerThread(void*) {
    // DWM reports bounds in physical pixels; position in the same space.
    SetThreadDpiAwarenessContext(DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2);

    Worker worker;
    std::vector<HWINEVENTHOOK> hooks;
    bool apartment = false;
    bool registered = false;
    HMODULE coreMessaging = nullptr;
    winrt::Windows::System::DispatcherQueueController queue{nullptr};

    try {
        winrt::init_apartment(winrt::apartment_type::single_threaded);
        apartment = true;

        // Composition needs a dispatcher queue on this thread.
        coreMessaging =
            LoadLibraryExW(L"CoreMessaging.dll", nullptr, LOAD_LIBRARY_SEARCH_SYSTEM32);
        if (!coreMessaging) {
            winrt::throw_last_error();
        }
        auto createQueue = reinterpret_cast<CreateDispatcherQueueController_t>(
            GetProcAddress(coreMessaging, "CreateDispatcherQueueController"));
        if (!createQueue) {
            winrt::throw_last_error();
        }
        DispatcherQueueOptionsAbi options{sizeof(DispatcherQueueOptionsAbi),
                                          kDispatcherQueueThreadCurrent,
                                          kDispatcherQueueComSta};
        winrt::check_hresult(createQueue(options, winrt::put_abi(queue)));

        WNDCLASSEXW windowClass{};
        windowClass.cbSize = sizeof(windowClass);
        windowClass.lpfnWndProc = WindowProc;
        windowClass.hInstance = g_module;
        windowClass.lpszClassName = kClassName;
        if (!RegisterClassExW(&windowClass)) {
            winrt::throw_last_error();
        }
        registered = true;

        g_worker = &worker;
        worker.controller = CreateWindowExW(0, kClassName, L"", 0, 0, 0, 0, 0, HWND_MESSAGE,
                                            nullptr, g_module, nullptr);
        if (!worker.controller) {
            winrt::throw_last_error();
        }

        // Publish the controller before loading settings, so a change made in
        // the meantime is still delivered afterwards.
        g_controller = worker.controller;
        LoadSettings();
        OpenShared();

        worker.resources.Create();

        for (auto const& range : kHookRanges) {
            HWINEVENTHOOK hook =
                SetWinEventHook(range.first, range.last, nullptr, OnWinEvent, 0, 0,
                                WINEVENT_OUTOFCONTEXT | WINEVENT_SKIPOWNPROCESS);
            if (hook) {
                hooks.push_back(hook);
            } else {
                Wh_Log(L"SetWinEventHook %04X failed, relying on polling", range.first);
            }
        }

        SetTimer(worker.controller, kPollTimerId, kPollIntervalMs, nullptr);
        SafeRefresh(worker);
        RunMessageLoop();
    } catch (...) {
        Wh_Log(L"Worker error: %08X", static_cast<unsigned>(winrt::to_hresult()));
    }

    for (HWINEVENTHOOK hook : hooks) {
        UnhookWinEvent(hook);
    }
    if (worker.controller) {
        KillTimer(worker.controller, kPollTimerId);
        KillTimer(worker.controller, kSettleTimerId);
    }
    StopClock(worker);

    // Composition objects must go before the dispatcher queue, and every COM
    // object before the apartment.
    worker.backdrops.clear();
    worker.failed.clear();
    worker.resources.Release();
    worker.meter.Release();
    CloseShared();

    g_controller = nullptr;
    if (worker.controller) {
        DestroyWindow(worker.controller);
        worker.controller = nullptr;
    }
    g_worker = nullptr;
    if (registered) {
        UnregisterClassW(kClassName, g_module);
    }

    bool queueStopped = !queue || ShutdownQueue(queue);
    if (!queueStopped) {
        // Leak deliberately: unloading CoreMessaging or tearing down the
        // apartment under a live queue could crash the process.
        winrt::detach_abi(queue);
        return 0;
    }
    queue = nullptr;
    if (coreMessaging) {
        FreeLibrary(coreMessaging);
    }
    if (apartment) {
        winrt::uninit_apartment();
    }
    return 0;
}

// Returns false if the worker didn't exit in time. Its handles are then kept,
// because the thread may still use the stop event.
bool StopWorker() {
    if (g_workerThread) {
        SetEvent(g_stopEvent);
        if (WaitForSingleObject(g_workerThread, kStopTimeoutMs) != WAIT_OBJECT_0) {
            Wh_Log(L"Worker didn't stop within %u ms", kStopTimeoutMs);
            return false;
        }
        CloseHandle(g_workerThread);
        g_workerThread = nullptr;
    }
    if (g_stopEvent) {
        CloseHandle(g_stopEvent);
        g_stopEvent = nullptr;
    }
    return true;
}

void StartWorker() {
    if (g_workerThread) {
        return;
    }

    if (!g_module) {
        GetModuleHandleExW(
            GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS | GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT,
            reinterpret_cast<LPCWSTR>(&WorkerThread), &g_module);
    }

    g_stopEvent = CreateEventW(nullptr, TRUE, FALSE, nullptr);
    if (!g_stopEvent) {
        Wh_Log(L"CreateEvent failed: %u", GetLastError());
        return;
    }

    g_workerThread = CreateThread(nullptr, 0, WorkerThread, nullptr, 0, nullptr);
    if (!g_workerThread) {
        Wh_Log(L"CreateThread failed: %u", GetLastError());
        CloseHandle(g_stopEvent);
        g_stopEvent = nullptr;
    }
}

}  // namespace

////////////////////////////////////////////////////////////////////////////////
// Tool mod callbacks

bool GlowEnabledSetting() {
    return Wh_GetIntSetting(L"glow.enabled") != 0;
}

BOOL WhTool_ModInit() {
    // The worker loads the settings itself. With the glow turned off the
    // process stays up but idle, ready for it to be turned back on.
    if (GlowEnabledSetting()) {
        StartWorker();
    }
    return TRUE;
}

void WhTool_ModSettingsChanged() {
    if (!GlowEnabledSetting()) {
        StopWorker();
        return;
    }
    if (!g_workerThread) {
        StartWorker();
        return;
    }
    // Applied on the worker thread: no thread restart, and nothing blocks
    // Windhawk's callback.
    HWND controller = g_controller;
    if (!controller || !PostMessageW(controller, kSettingsMessage, 0, 0)) {
        Wh_Log(L"Worker not available, restarting it");
        if (StopWorker()) {
            StartWorker();
        }
    }
}

void WhTool_ModUninit() {
    // If the worker is stuck, the ExitProcess that follows ends it anyway.
    StopWorker();
}

}  // namespace glowtool


// -----------------------------------------------------------------------------
// Settings
// -----------------------------------------------------------------------------

struct Settings {
    float springK      = 200.0f;
    float bottomRatio  = 0.65f;
    float meshK        = 3.0f;
    float damping      = 14.0f;
    float impulse      = 0.12f;
    // Critically damped pair used to finish the landing quickly.
    float settleK      = 12000.0f;
    float settleD      = 210.0f;
    int   mesh         = 16;
    int   bypassVk     = VK_SHIFT;
    int   revealHoldMs = 90;
    int   idleReleaseMs = 5000;
    bool  borders      = true;
    bool  windowManager = true;
    // The glow's own settings, read here so the wobble paints the same glow.
    glowtool::Settings glow;
};

static Settings g_cfg;
static SRWLOCK  g_cfgLock = SRWLOCK_INIT;
// Read by the hooks on app threads without the lock.
static std::atomic<int>  g_bypassVk{VK_SHIFT};
static std::atomic<bool> g_windowManager{true};
static std::atomic<int>  g_idleReleaseMs{5000};

static Settings SnapshotSettings() {
    AcquireSRWLockShared(&g_cfgLock);
    Settings s = g_cfg;
    ReleaseSRWLockShared(&g_cfgLock);
    return s;
}

static int ClampInt(int v, int lo, int hi) { return v < lo ? lo : (v > hi ? hi : v); }

static void LoadSettings() {
    Settings s;

    struct Preset { const wchar_t* name; int k, soft, rig, fric, kick; };
    static const Preset kPresets[] = {
        { L"veryLow",  320, 85, 50, 180,  6 },
        { L"low",      260, 75, 40, 160,  9 },
        { L"medium",   200, 65, 30, 140, 12 },
        { L"high",     150, 55, 22, 115, 15 },
        { L"veryHigh", 110, 45, 15,  95, 18 },
    };
    int k = 200, soft = 65, rig = 30, fric = 140, kick = 12;
    {
        PCWSTR w = Wh_GetStringSetting(L"wobbliness");
        if (w && !wcscmp(w, L"custom")) {
            k    = ClampInt(Wh_GetIntSetting(L"custom.stiffness"), 50, 600);
            soft = ClampInt(Wh_GetIntSetting(L"custom.softness"), 10, 100);
            rig  = ClampInt(Wh_GetIntSetting(L"custom.rigidity"), 0, 100);
            fric = ClampInt(Wh_GetIntSetting(L"custom.friction"), 20, 400);
            kick = ClampInt(Wh_GetIntSetting(L"custom.kick"), 0, 50);
        } else {
            for (const Preset& p : kPresets) {
                if (w && !wcscmp(w, p.name)) {
                    k = p.k; soft = p.soft; rig = p.rig; fric = p.fric; kick = p.kick;
                }
            }
        }
        if (w) Wh_FreeStringSetting(w);
    }
    s.springK     = (float)k;
    s.bottomRatio = soft / 100.0f;
    s.meshK       = rig / 10.0f;
    s.damping     = fric / 10.0f;
    s.impulse     = kick / 100.0f;

    s.borders       = Wh_GetIntSetting(L"borders") != 0;
    s.windowManager = Wh_GetIntSetting(L"windowManager") != 0;

    {
        PCWSTR b = Wh_GetStringSetting(L"bypassKey");
        // Unknown values fall back to Shift, so a typo never removes the escape.
        s.bypassVk = !b                   ? VK_SHIFT
                   : !wcscmp(b, L"ctrl")  ? VK_CONTROL
                   : !wcscmp(b, L"alt")   ? VK_MENU
                   : !wcscmp(b, L"none")  ? 0
                                          : VK_SHIFT;
        if (b) Wh_FreeStringSetting(b);
    }

    s.mesh          = ClampInt(Wh_GetIntSetting(L"meshSize"), 4, 32);
    s.revealHoldMs  = ClampInt(Wh_GetIntSetting(L"revealHoldMs"), 0, 500);
    s.idleReleaseMs = ClampInt(Wh_GetIntSetting(L"idleReleaseSec"), 0, 600) * 1000;

    // Only app processes come here; in windhawk.exe the glow's worker owns
    // glowtool::g_settings, and no worker runs in an app process.
    glowtool::LoadSettings();
    s.glow = glowtool::g_settings;

    AcquireSRWLockExclusive(&g_cfgLock);
    g_cfg = s;
    ReleaseSRWLockExclusive(&g_cfgLock);
    g_bypassVk.store(s.bypassVk);
    g_windowManager.store(s.windowManager);
    g_idleReleaseMs.store(s.idleReleaseMs);

    Wh_Log(L"settings: k=%d soft=%d%% rig=%d fric=%d kick=%d mesh=%d borders=%d swm=%d "
           L"glow=%d inDrag=%d strength=%d",
           k, soft, rig, fric, kick, s.mesh, s.borders, s.windowManager,
           s.glow.enabled, s.glow.inDrag, s.glow.dragStrength);
}

// -----------------------------------------------------------------------------
// Small helpers
// -----------------------------------------------------------------------------

template <class T>
struct Com {
    T* p = nullptr;
    ~Com() { reset(); }
    Com() = default;
    Com(const Com&) = delete;
    Com& operator=(const Com&) = delete;
    T** operator&() { reset(); return &p; }
    T* operator->() const { return p; }
    operator T*() const { return p; }
    void reset() { if (p) { p->Release(); p = nullptr; } }
};

struct Vec2 { float x, y; };

static double NowSeconds() {
    static LARGE_INTEGER freq = [] { LARGE_INTEGER f; QueryPerformanceFrequency(&f); return f; }();
    LARGE_INTEGER c; QueryPerformanceCounter(&c);
    return (double)c.QuadPart / (double)freq.QuadPart;
}

// Raised to retire the worker. Every loop checks it.
static HANDLE g_quitSignal = nullptr;

static bool QuitRequested() {
    return g_quitSignal && WaitForSingleObject(g_quitSignal, 0) == WAIT_OBJECT_0;
}

static int PrimaryButtonVk() {
    return GetSystemMetrics(SM_SWAPBUTTON) ? VK_RBUTTON : VK_LBUTTON;
}

static bool PrimaryButtonDown() {
    return (GetAsyncKeyState(PrimaryButtonVk()) & 0x8000) != 0;
}

static bool SameSize(const RECT& a, const RECT& b) {
    return a.right - a.left == b.right - b.left && a.bottom - a.top == b.bottom - b.top;
}

static bool SamePos(const RECT& a, const RECT& b) {
    return a.left == b.left && a.top == b.top;
}

// Sleep(1) sleeps a whole 15.6 ms tick at the default timer resolution. A
// high resolution waitable timer waits the asked time without raising the
// system timer for everyone. Owned by the worker thread.
static HANDLE g_waitTimer = nullptr;

static void PumpMessages() {
    MSG msg;
    while (PeekMessageW(&msg, nullptr, 0, 0, PM_REMOVE)) {
        if (msg.message == WM_QUIT) { PostQuitMessage((int)msg.wParam); return; }
        TranslateMessage(&msg);
        DispatchMessageW(&msg);
    }
}

// Waits about `ms` while keeping the worker's queue serviced. Returns false
// if the mod is unloading.
static bool WaitMs(double ms) {
    if (!g_waitTimer) {
        g_waitTimer = CreateWaitableTimerExW(nullptr, nullptr,
                                             CREATE_WAITABLE_TIMER_HIGH_RESOLUTION,
                                             TIMER_ALL_ACCESS);
        if (!g_waitTimer)
            g_waitTimer = CreateWaitableTimerExW(nullptr, nullptr, 0, TIMER_ALL_ACCESS);
    }
    const double until = NowSeconds() + ms / 1000.0;
    for (;;) {
        PumpMessages();
        if (QuitRequested()) return false;
        const double left = (until - NowSeconds()) * 1000.0;
        if (left <= 0.0) return true;
        if (g_waitTimer) {
            LARGE_INTEGER due;
            due.QuadPart = -(LONGLONG)(left * 10000.0);
            if (due.QuadPart > -1) due.QuadPart = -1;
            SetWaitableTimer(g_waitTimer, &due, 0, nullptr, nullptr, FALSE);
            HANDLE h[2] = { g_waitTimer, g_quitSignal };
            MsgWaitForMultipleObjects(2, h, FALSE, 50, QS_ALLINPUT);
        } else {
            Sleep(1);
        }
    }
}

// shcore is loaded lazily from System32 and freed at unload.
static HMODULE g_shcore = nullptr;
using GetDpiForMonitor_t = HRESULT(WINAPI*)(HMONITOR, MONITOR_DPI_TYPE, UINT*, UINT*);
static GetDpiForMonitor_t g_getDpiForMonitor = nullptr;
static bool g_shcoreTried = false;

// The monitor's DPI, not the window's: a DPI-unaware window reports 96 on
// every monitor, while Seamless Borders and corner rounding use the monitor's.
static float MonitorScale(const RECT& r) {
    if (!g_shcoreTried) {
        g_shcoreTried = true;
        g_shcore = LoadLibraryExW(L"shcore.dll", nullptr, LOAD_LIBRARY_SEARCH_SYSTEM32);
        if (g_shcore)
            g_getDpiForMonitor = (GetDpiForMonitor_t)GetProcAddress(g_shcore, "GetDpiForMonitor");
    }
    UINT dx = 96, dy = 96;
    if (g_getDpiForMonitor) {
        HMONITOR m = MonitorFromRect(&r, MONITOR_DEFAULTTONEAREST);
        if (FAILED(g_getDpiForMonitor(m, MDT_EFFECTIVE_DPI, &dx, &dy)) || !dx) dx = 96;
    }
    return dx / 96.0f;
}

// -----------------------------------------------------------------------------
// Other mods' settings
// -----------------------------------------------------------------------------

static const wchar_t kModsKey[] = L"SOFTWARE\\Windhawk\\Engine\\Mods\\";

static bool ModEnabled(const wchar_t* id) {
    std::wstring path = std::wstring(kModsKey) + id;
    HKEY key = nullptr;
    if (RegOpenKeyExW(HKEY_LOCAL_MACHINE, path.c_str(), 0,
                      KEY_QUERY_VALUE | KEY_WOW64_64KEY, &key) != ERROR_SUCCESS)
        return false;
    DWORD v = 0, size = sizeof(v), type = 0;
    const LSTATUS st = RegQueryValueExW(key, L"Disabled", nullptr, &type, (BYTE*)&v, &size);
    RegCloseKey(key);
    // A missing Disabled value means enabled.
    return st != ERROR_SUCCESS || type != REG_DWORD || v == 0;
}

struct ModSettingsKey {
    HKEY key = nullptr;
    explicit ModSettingsKey(const wchar_t* id) {
        std::wstring path = std::wstring(kModsKey) + id + L"\\Settings";
        if (RegOpenKeyExW(HKEY_LOCAL_MACHINE, path.c_str(), 0,
                          KEY_QUERY_VALUE | KEY_WOW64_64KEY, &key) != ERROR_SUCCESS)
            key = nullptr;
    }
    ~ModSettingsKey() { if (key) RegCloseKey(key); }
    int Int(const wchar_t* name, int fallback) const {
        if (!key) return fallback;
        DWORD v = 0, size = sizeof(v), type = 0;
        if (RegQueryValueExW(key, name, nullptr, &type, (BYTE*)&v, &size) != ERROR_SUCCESS ||
            type != REG_DWORD)
            return fallback;
        return (int)v;
    }
    std::wstring Str(const wchar_t* name) const {
        if (!key) return L"";
        wchar_t buf[128] = {};
        DWORD size = sizeof(buf) - sizeof(wchar_t), type = 0;
        if (RegQueryValueExW(key, name, nullptr, &type, (BYTE*)buf, &size) != ERROR_SUCCESS ||
            type != REG_SZ)
            return L"";
        std::wstring s = buf;
        const size_t a = s.find_first_not_of(L' ');
        if (a == std::wstring::npos) return L"";
        return s.substr(a, s.find_last_not_of(L' ') - a + 1);
    }
};

// -----------------------------------------------------------------------------
// Seamless Borders ring renderer (copied verbatim from Seamless Borders)
// -----------------------------------------------------------------------------

struct Ring {
    float r = 0, g = 0, b = 0, a = 0;
};

static COLORREF ParseHex(const std::wstring& text, COLORREF fallback) {
    std::wstring hex = !text.empty() && text[0] == L'#' ? text.substr(1) : text;
    if (hex.size() != 6) {
        return fallback;
    }
    wchar_t* end = nullptr;
    unsigned long v = wcstoul(hex.c_str(), &end, 16);
    if (*end) {
        return fallback;
    }
    return RGB((v >> 16) & 0xff, (v >> 8) & 0xff, v & 0xff);
}

// BEGIN RING RENDERER
static float Clamp01(float v) {
    return v < 0 ? 0 : (v > 1 ? 1 : v);
}

static Ring LerpColor(const Ring& x, const Ring& y, float t) {
    return {x.r + (y.r - x.r) * t, x.g + (y.g - x.g) * t, x.b + (y.b - x.b) * t,
            x.a + (y.a - x.a) * t};
}

// Rows/columns from each canvas edge that can hold ring pixels.
static int RingBand(int pad, float radius, float offset) {
    float inside = (offset < 0 ? -offset : 0) + 1;
    return pad + (int)ceilf(radius > inside ? radius : inside) + 1;
}

// The canvas is the window frame grown by pad on every side (fw x fh pixels).
// Draws the part of the ring inside the strip (sx, sy, sw, sh) into a zeroed,
// top-down, premultiplied BGRA buffer. The ring spans [offset, offset + width]
// outside the frame edge.
static void RenderRing(uint32_t* px, int sx, int sy, int sw, int sh, int fw, int fh, int pad,
                       float radius, float offset, float width, Ring c1, Ring c2, float angleDeg) {
    float cx = fw / 2.0f, cy = fh / 2.0f;
    float hx = fw / 2.0f - pad, hy = fh / 2.0f - pad;
    if (hx <= 0 || hy <= 0) {
        return;
    }
    float r = radius;
    if (r > hx) r = hx;
    if (r > hy) r = hy;

    float rad = angleDeg * 3.14159265f / 180.0f;
    float dx = cosf(rad), dy = sinf(rad);
    float span = fabsf(hx * dx) + fabsf(hy * dy) + pad;
    bool solid = c1.r == c2.r && c1.g == c2.g && c1.b == c2.b && c1.a == c2.a;

    for (int y = 0; y < sh; y++) {
        for (int x = 0; x < sw; x++) {
            float fx = sx + x + 0.5f - cx, fy = sy + y + 0.5f - cy;
            float qx = fabsf(fx) - (hx - r), qy = fabsf(fy) - (hy - r);
            float ox = qx > 0 ? qx : 0, oy = qy > 0 ? qy : 0;
            float inner = qx > qy ? qx : qy;
            float d = sqrtf(ox * ox + oy * oy) + (inner < 0 ? inner : 0) - r;
            float cov = Clamp01(d - offset + 0.5f) * Clamp01(offset + width - d + 0.5f);
            if (cov <= 0) {
                continue;
            }
            Ring c = solid ? c1
                           : LerpColor(c1, c2, Clamp01((fx * dx + fy * dy) / span * 0.5f + 0.5f));
            float a = c.a * cov;
            px[y * sw + x] = ((uint32_t)(a * 255 + 0.5f) << 24) |
                             ((uint32_t)(c.r * a * 255 + 0.5f) << 16) |
                             ((uint32_t)(c.g * a * 255 + 0.5f) << 8) |
                             (uint32_t)(c.b * a * 255 + 0.5f);
        }
    }
}

// Splits the canvas into top, bottom, left and right strips. Returns how many
// are non-empty (left and right vanish on very short windows).
static int RingStrips(int fw, int fh, int band, RECT out[4]) {
    if (band * 2 >= fh) {
        band = (fh + 1) / 2;
    }
    out[0] = {0, 0, fw, band};
    out[1] = {0, fh - band, fw, fh};
    out[2] = {0, band, band, fh - band};
    out[3] = {fw - band, band, fw, fh - band};
    return fh - band * 2 > 0 ? 4 : 2;
}
// END RING RENDERER

static Ring ToRing(COLORREF c) {
    return {GetRValue(c) / 255.0f, GetGValue(c) / 255.0f, GetBValue(c) / 255.0f, 1.0f};
}

static COLORREF AccentRgb() {
    DWORD argb = 0;
    BOOL opaque = FALSE;
    if (FAILED(DwmGetColorizationColor(&argb, &opaque))) {
        return RGB(0x89, 0xb4, 0xfa);
    }
    return RGB((argb >> 16) & 0xff, (argb >> 8) & 0xff, argb & 0xff);
}

// The ring as Seamless Borders would draw it for this window right now.
struct RingSpec {
    bool  on = false;
    int   pad = 0, width = 0, offset = 0;
    float radius = 0, angle = 45;
    Ring  c1, c2;
};

static RingSpec ReadRingSpec(float scale, bool focused) {
    RingSpec s;
    ModSettingsKey k(L"local@seamless-borders");
    const int w   = ClampInt(k.Int(L"width", 2), 1, 32);
    const int gap = ClampInt(k.Int(L"gap", -1), -8, 32);   // 0xffffffff reads as -1
    int radius    = k.Int(L"radius", 16);
    radius        = radius < 0 ? 8 : (radius > 64 ? 64 : radius);
    const bool gradient = k.Int(L"gradient", 1) != 0;
    s.angle       = (float)ClampInt(k.Int(L"gradientAngle", 45), 0, 360);

    std::wstring fc = k.Str(L"focusedColor");
    const bool accent = fc.empty() || _wcsicmp(fc.c_str(), L"accent") == 0;
    const COLORREF focusedC   = accent ? AccentRgb() : ParseHex(fc, RGB(0x89, 0xb4, 0xfa));
    const COLORREF focusedTo  = ParseHex(k.Str(L"focusedColorTo"), RGB(0xcb, 0xa6, 0xf7));
    const COLORREF unfocusedC = ParseHex(k.Str(L"unfocusedColor"), RGB(0x58, 0x5b, 0x70));
    const COLORREF unfocusedTo = ParseHex(k.Str(L"unfocusedColorTo"), RGB(0x58, 0x5b, 0x70));

    s.c1 = ToRing(focused ? focusedC : unfocusedC);
    s.c2 = gradient ? ToRing(focused ? focusedTo : unfocusedTo) : s.c1;

    s.width  = (int)ceilf(w * scale);
    s.offset = (int)roundf(gap * scale);
    s.pad    = s.width + (s.offset > 0 ? s.offset : 0) + 1;
    s.radius = radius * scale;
    s.on     = true;
    return s;
}

// The border worker stacks its four parts immediately above their target.
static bool BordersRingShown(HWND hwnd, const RECT& vis, int pad, int tolerance) {
    HWND part = GetWindow(hwnd, GW_HWNDPREV);
    for (int i = 0; part && i < 4; ++i, part = GetWindow(part, GW_HWNDPREV)) {
        wchar_t cls[32];
        if (!GetClassNameW(part, cls, ARRAYSIZE(cls)) ||
            wcscmp(cls, L"SeamlessBordersPart")) break;
        RECT r{};
        if (!IsWindowVisible(part) || !GetWindowRect(part, &r)) continue;
        if (abs((r.right - r.left) - (vis.right - vis.left + 2 * pad)) <= 1 &&
            abs(r.left - vis.left + pad) <= tolerance &&
            abs(r.top - vis.top + pad) <= tolerance) return true;
    }
    return false;
}

// -----------------------------------------------------------------------------
// Corners
// -----------------------------------------------------------------------------

static bool SystemRoundsCorners() {
    static const bool rounded = [] {
        struct VerInfo {
            ULONG size, major, minor, build, platform;
            WCHAR csd[128];
        } vi{};
        vi.size = sizeof(vi);
        HMODULE nt = GetModuleHandleW(L"ntdll.dll");
        if (!nt) return true;
        auto get = (LONG(WINAPI*)(VerInfo*))GetProcAddress(nt, "RtlGetVersion");
        if (!get || get(&vi) != 0) return true;
        return vi.build >= 22000;
    }();
    return rounded;
}

// The radius DWM draws this window's corners with.
static float CornerRadius(HWND hwnd, float scale) {
    if (IsZoomed(hwnd) || !SystemRoundsCorners()) return 0.0f;
    DWORD pref = 0;
    bool small = false;
    if (SUCCEEDED(DwmGetWindowAttribute(hwnd, DWMWA_WINDOW_CORNER_PREFERENCE,
                                        &pref, sizeof(pref)))) {
        if (pref == DWMWCP_DONOTROUND) return 0.0f;
        small = pref == DWMWCP_ROUNDSMALL;
    }
    if (ModEnabled(L"custom-corner-radius")) {
        ModSettingsKey k(L"custom-corner-radius");
        const int r = small ? k.Int(L"smallRadius", 4) : k.Int(L"radius", 8);
        return (float)ClampInt(r, 0, 64) * scale;
    }
    return (small ? 4.0f : 8.0f) * scale;
}

// -----------------------------------------------------------------------------
// Capture
// -----------------------------------------------------------------------------

// The texture: the window at (P, P) with its corners carved, the ring around
// it, all premultiplied, in a canvas P pixels larger on every side. The spare
// pixels keep bilinear filtering from smearing the edge when the mesh bends.
struct Canvas {
    int w = 0, h = 0;          // canvas size
    int P = 0;                 // window inset inside the canvas
    RECT outer{};              // GetWindowRect at capture
    RECT vis{};                // visible frame at capture
    int frameDx = 0, frameDy = 0;   // vis - outer, left and top
    std::vector<uint32_t> px;
};

// Visible frame and window rect read as a consistent pair: DWM's frame bounds
// lag a resize, so a pair taken mid-change disagrees about the size.
static bool ReadFramePair(HWND hwnd, RECT& outer, RECT& vis) {
    for (int attempt = 0; attempt < 40; ++attempt) {
        RECT o1{}, o2{}, v{};
        if (!GetWindowRect(hwnd, &o1)) return false;
        if (FAILED(DwmGetWindowAttribute(hwnd, DWMWA_EXTENDED_FRAME_BOUNDS, &v, sizeof(v))))
            v = o1;
        if (!GetWindowRect(hwnd, &o2)) return false;
        const LONG dl = v.left - o1.left, dt = v.top - o1.top;
        const LONG dr = o1.right - v.right, db = o1.bottom - v.bottom;
        if (EqualRect(&o1, &o2) && dl >= 0 && dt >= 0 && dr >= 0 && db >= 0 &&
            dl <= 32 && dt <= 32 && dr <= 32 && db <= 32) {
            outer = o1; vis = v;
            return true;
        }
        if (QuitRequested()) return false;
        WaitMs(1);
    }
    return false;
}

static void RoundCornersAt(Canvas& c, int x0, int y0, int w, int h, float radius) {
    if (radius < 1.0f) return;
    const int r = (int)ceilf(radius);
    if (r * 2 > w || r * 2 > h) return;
    for (int cy = 0; cy < r; ++cy) {
        for (int cx = 0; cx < r; ++cx) {
            const float dx = (float)r - (float)cx - 0.5f;
            const float dy = (float)r - (float)cy - 0.5f;
            const float d  = sqrtf(dx * dx + dy * dy) - ((float)r - radius);
            float a = radius - d + 0.5f;
            a = a < 0.0f ? 0.0f : (a > 1.0f ? 1.0f : a);
            if (a >= 1.0f) continue;
            const uint32_t alpha = (uint32_t)(a * 255.0f + 0.5f);
            const int xs[4] = { x0 + cx, x0 + w - 1 - cx, x0 + cx, x0 + w - 1 - cx };
            const int ys[4] = { y0 + cy, y0 + cy, y0 + h - 1 - cy, y0 + h - 1 - cy };
            for (int i = 0; i < 4; ++i) {
                uint32_t& p = c.px[(size_t)ys[i] * c.w + xs[i]];
                const uint32_t b = ((p & 0xFF) * alpha + 127) / 255;
                const uint32_t g = (((p >> 8) & 0xFF) * alpha + 127) / 255;
                const uint32_t rr = (((p >> 16) & 0xFF) * alpha + 127) / 255;
                p = (alpha << 24) | (rr << 16) | (g << 8) | b;
            }
        }
    }
}

static bool BuildCanvas(HWND hwnd, const RingSpec& ring, Canvas& out) {
    RECT outer{};
    if (!GetWindowRect(hwnd, &outer)) return false;
    const int ow = outer.right - outer.left, oh = outer.bottom - outer.top;
    if (ow < 1 || oh < 1 || ow > 16384 || oh > 16384) return false;

    BITMAPINFO bi{};
    bi.bmiHeader.biSize        = sizeof(BITMAPINFOHEADER);
    bi.bmiHeader.biWidth       = ow;
    bi.bmiHeader.biHeight      = -oh;
    bi.bmiHeader.biPlanes      = 1;
    bi.bmiHeader.biBitCount    = 32;
    bi.bmiHeader.biCompression = BI_RGB;

    void* bits = nullptr;
    HBITMAP hbm = CreateDIBSection(nullptr, &bi, DIB_RGB_COLORS, &bits, nullptr, 0);
    if (!hbm) return false;
    HDC mem = CreateCompatibleDC(nullptr);
    HGDIOBJ old = SelectObject(mem, hbm);
    const BOOL printed = PrintWindow(hwnd, mem, PW_RENDERFULLCONTENT);
    SelectObject(mem, old);
    DeleteDC(mem);
    if (!printed) { DeleteObject(hbm); return false; }

    RECT o2{}, vis{};
    if (!ReadFramePair(hwnd, o2, vis) || !SameSize(o2, outer)) {
        DeleteObject(hbm);
        return false;
    }
    const int dx = vis.left - o2.left, dy = vis.top - o2.top;
    const int vw = vis.right - vis.left, vh = vis.bottom - vis.top;
    if (vw < 1 || vh < 1) { DeleteObject(hbm); return false; }

    const int P = (ring.on ? ring.pad : 0) + 2;
    out.P = P;
    out.w = vw + 2 * P;
    out.h = vh + 2 * P;
    if (out.w > 16384 || out.h > 16384) { DeleteObject(hbm); return false; }
    out.outer = o2;
    out.vis = vis;
    out.frameDx = dx;
    out.frameDy = dy;
    out.px.assign((size_t)out.w * out.h, 0);

    const uint32_t* src = (const uint32_t*)bits;
    for (int y = 0; y < vh; ++y) {
        const int sy = y + dy;
        if (sy < 0 || sy >= oh) continue;
        uint32_t* d = &out.px[(size_t)(y + P) * out.w + P];
        const uint32_t* s = &src[(size_t)sy * ow + dx];
        const int n = std::min(vw, ow - dx);
        for (int x = 0; x < n; ++x) d[x] = s[x] | 0xFF000000u;
    }
    DeleteObject(hbm);

    const float scale = MonitorScale(vis);
    RoundCornersAt(out, P, P, vw, vh, CornerRadius(hwnd, scale));

    if (ring.on) {
        // Seamless Borders' own geometry: a canvas of the frame grown by pad,
        // drawn as four strips, composited "over" the window.
        const int fw = vw + 2 * ring.pad, fh = vh + 2 * ring.pad;
        RECT strips[4];
        const int count = RingStrips(fw, fh, RingBand(ring.pad, ring.radius, (float)ring.offset),
                                     strips);
        const int ox = P - ring.pad, oy = P - ring.pad;
        std::vector<uint32_t> tmp;
        for (int i = 0; i < count; ++i) {
            const RECT& st = strips[i];
            const int sw = st.right - st.left, sh = st.bottom - st.top;
            if (sw <= 0 || sh <= 0) continue;
            tmp.assign((size_t)sw * sh, 0);
            RenderRing(tmp.data(), st.left, st.top, sw, sh, fw, fh, ring.pad, ring.radius,
                       (float)ring.offset, (float)ring.width, ring.c1, ring.c2, ring.angle);
            for (int y = 0; y < sh; ++y) {
                uint32_t* d = &out.px[(size_t)(oy + st.top + y) * out.w + ox + st.left];
                const uint32_t* s = &tmp[(size_t)y * sw];
                for (int x = 0; x < sw; ++x) {
                    const uint32_t r = s[x];
                    const uint32_t a = r >> 24;
                    if (!a) continue;
                    const uint32_t inv = 255 - a;
                    const uint32_t q = d[x];
                    const uint32_t A = a + ((q >> 24) * inv + 127) / 255;
                    const uint32_t R = ((r >> 16) & 0xFF) + (((q >> 16) & 0xFF) * inv + 127) / 255;
                    const uint32_t G = ((r >> 8) & 0xFF) + (((q >> 8) & 0xFF) * inv + 127) / 255;
                    const uint32_t B = (r & 0xFF) + ((q & 0xFF) * inv + 127) / 255;
                    d[x] = (std::min(A, 255u) << 24) | (std::min(R, 255u) << 16) |
                           (std::min(G, 255u) << 8) | std::min(B, 255u);
                }
            }
        }
    }
    return true;
}

// -----------------------------------------------------------------------------
// Spring mesh
// -----------------------------------------------------------------------------
// The original Window Wobble's sheet, unchanged: a control spring pulls each
// node to its rest spot, stiff along the title bar and softer down the rows,
// which is what makes the body trail; springs between neighbours keep the
// sheet together. Integrated in fixed 1/480 s steps so a long frame can't
// blow it up.

struct Mesh {

    int nx = 0, ny = 0;
    float W = 0, H = 0;
    std::vector<Vec2> rest, pos, vel, force;
    std::vector<float> kScale;          // per-row stiffness factor
    bool  settled = true;
    float bandK = 0.0f, bandD = 0.0f;   // non-zero while finishing the landing
    Settings cfg;

    void Setup(const Settings& c, int cells, float x, float y, float w, float h) {
        cfg = c;
        nx = ny = cells + 1;
        W = w; H = h;
        const size_t n = (size_t)nx * ny;
        rest.resize(n); pos.resize(n); force.resize(n); kScale.resize(n);
        vel.assign(n, Vec2{0, 0});
        for (int j = 0; j < ny; ++j) {
            const float t = (ny > 1) ? (float)j / (ny - 1) : 0.0f;
            for (int i = 0; i < nx; ++i) {
                const Vec2 p{ x + w * i / (nx - 1), y + h * j / (ny - 1) };
                rest[(size_t)j * nx + i] = p;
                pos[(size_t)j * nx + i]  = p;
                kScale[(size_t)j * nx + i] = 1.0f + (cfg.bottomRatio - 1.0f) * t;
            }
        }
        settled = false;
        bandK = bandD = 0.0f;
    }

    // Rest spot of the top-left node.
    Vec2 Origin() const { return rest[0]; }

    void MoveRest(float x, float y) {
        const float dx = x - rest[0].x, dy = y - rest[0].y;
        if (dx == 0.0f && dy == 0.0f) return;
        for (auto& p : rest) { p.x += dx; p.y += dy; }
        settled = false;
    }

    void Kick(float vx, float vy) {
        const float speed = sqrtf(vx * vx + vy * vy);
        if (speed < 2.0f || cfg.impulse <= 0.0f) return;
        const float norm = fabsf(vx) + fabsf(vy) + 1e-6f;
        for (int j = 0; j < ny; ++j) {
            const float fy = (float)j / (ny - 1);
            for (int i = 0; i < nx; ++i) {
                const float fx = (float)i / (nx - 1);
                // The trailing edge, opposite the travel, gets kicked most.
                const float wx = (vx > 0) ? (1.0f - fx) : fx;
                const float wy = (vy > 0) ? (1.0f - fy) : fy;
                const float w  = (wx * fabsf(vx) + wy * fabsf(vy)) / norm;
                Vec2& v = vel[(size_t)j * nx + i];
                v.x -= vx * w * cfg.impulse;
                v.y -= vy * w * cfg.impulse;
            }
        }
        settled = false;
    }

    void SettleFast() {
        bandK = cfg.settleK;
        bandD = cfg.settleD;
        settled = false;
    }

    void Snap() {
        pos = rest;
        std::fill(vel.begin(), vel.end(), Vec2{0, 0});
        bandK = bandD = 0.0f;
        settled = true;
    }

    // One fixed step. Returns true once the sheet is at rest.
    bool Step(float dt) {
        const bool band = bandK > 0.0f;
        const float d = band ? bandD : cfg.damping;
        std::vector<Vec2>& f = force;
        const size_t n = pos.size();

        for (size_t i = 0; i < n; ++i) {
            const float k = band ? bandK : cfg.springK * kScale[i];
            f[i] = Vec2{ -k * (pos[i].x - rest[i].x), -k * (pos[i].y - rest[i].y) };
        }
        if (cfg.meshK > 0.0f) {
            const float km = cfg.meshK;
            for (int j = 0; j < ny; ++j)
                for (int i = 0; i + 1 < nx; ++i) {
                    const size_t a = (size_t)j * nx + i, b = a + 1;
                    const float dxv = (pos[b].x - pos[a].x) - (rest[b].x - rest[a].x);
                    const float dyv = (pos[b].y - pos[a].y) - (rest[b].y - rest[a].y);
                    f[a].x += km * dxv; f[a].y += km * dyv;
                    f[b].x -= km * dxv; f[b].y -= km * dyv;
                }
            for (int j = 0; j + 1 < ny; ++j)
                for (int i = 0; i < nx; ++i) {
                    const size_t a = (size_t)j * nx + i, b = a + nx;
                    const float dxv = (pos[b].x - pos[a].x) - (rest[b].x - rest[a].x);
                    const float dyv = (pos[b].y - pos[a].y) - (rest[b].y - rest[a].y);
                    f[a].x += km * dxv; f[a].y += km * dyv;
                    f[b].x -= km * dxv; f[b].y -= km * dyv;
                }
        }

        // As the original: the displacement is measured before the move.
        float maxDisp = 0.0f, maxVel = 0.0f;
        bool finite = true;
        for (size_t i = 0; i < n; ++i) {
            Vec2& v = vel[i];
            Vec2& p = pos[i];
            maxDisp = fmaxf(maxDisp, fmaxf(fabsf(p.x - rest[i].x), fabsf(p.y - rest[i].y)));
            v.x += (f[i].x - d * v.x) * dt;
            v.y += (f[i].y - d * v.y) * dt;
            p.x += v.x * dt;
            p.y += v.y * dt;
            maxVel = fmaxf(maxVel, fmaxf(fabsf(v.x), fabsf(v.y)));
            finite = finite && isfinite(p.x) && isfinite(p.y);
        }
        // Runaway guard: a NaN or a sheet far off its spot drops flat at rest.
        if (!finite || !(maxDisp < 1.0e5f) || !(maxVel < 1.0e7f)) return true;
        return maxDisp < 2.5f && maxVel < 20.0f;
    }

    // The original's stepping, unchanged: the frame's own time, split into
    // equal steps no longer than a quarter of the longest stable one for the
    // stiffest spring a node sees (k*h*h + 2*d*h < 4). The landing pair
    // (k 12000, d 210) is only stable below 7.8 ms, so a fixed 1/120 s step
    // shook it. Returns true if anything moved.
    bool Advance(float dt) {
        if (settled) return false;
        dt = std::min(dt, 0.05f);
        if (dt <= 0.0f) return true;
        const bool  band = bandK > 0.0f;
        const float d0   = band ? bandD : cfg.damping;
        const float kRow = band ? bandK : cfg.springK * fmaxf(1.0f, cfg.bottomRatio);
        const float k0   = fmaxf(kRow + 8.0f * fmaxf(cfg.meshK, 0.0f), 1e-3f);
        const float maxStep = 0.25f * (sqrtf(d0 * d0 + 4.0f * k0) - d0) / k0;
        int steps = std::max(1, (int)ceilf(dt / maxStep));
        float h = dt / (float)steps;
        if (steps > 64) { steps = 64; h = maxStep; }
        bool rested = false;
        for (int s = 0; s < steps && !rested; ++s) rested = Step(h);
        if (rested) Snap();
        return true;
    }
};

// -----------------------------------------------------------------------------
// Renderer: D3D11 + DirectComposition
// -----------------------------------------------------------------------------
// d3d11.dll and dcomp.dll load on the first drag, never at injection, so a
// process that never drags a window never pays for them. Shaders are compiled
// offline and embedded.

struct D3DApi {
    using PFN_D3D11CreateDevice = HRESULT(WINAPI*)(
        IDXGIAdapter*, D3D_DRIVER_TYPE, HMODULE, UINT, const D3D_FEATURE_LEVEL*,
        UINT, UINT, ID3D11Device**, D3D_FEATURE_LEVEL*, ID3D11DeviceContext**);
    using PFN_DCompositionCreateDevice = HRESULT(WINAPI*)(IDXGIDevice*, REFIID, void**);

    HMODULE d3d11 = nullptr;
    HMODULE dcomp = nullptr;
    PFN_D3D11CreateDevice        CreateDevice     = nullptr;
    PFN_DCompositionCreateDevice CreateCompDevice = nullptr;
    bool tried = false, ok = false;

    bool Load() {
        if (tried) return ok;
        tried = true;
        d3d11 = LoadLibraryExW(L"d3d11.dll", nullptr, LOAD_LIBRARY_SEARCH_SYSTEM32);
        dcomp = LoadLibraryExW(L"dcomp.dll", nullptr, LOAD_LIBRARY_SEARCH_SYSTEM32);
        if (!d3d11 || !dcomp) {
            Wh_Log(L"d3d11/dcomp load failed");
            return false;
        }
        CreateDevice     = (PFN_D3D11CreateDevice)GetProcAddress(d3d11, "D3D11CreateDevice");
        CreateCompDevice = (PFN_DCompositionCreateDevice)GetProcAddress(dcomp, "DCompositionCreateDevice");
        ok = CreateDevice && CreateCompDevice;
        return ok;
    }

    void Free() {
        if (d3d11) FreeLibrary(d3d11);
        if (dcomp) FreeLibrary(dcomp);
        d3d11 = dcomp = nullptr;
        CreateDevice = nullptr;
        CreateCompDevice = nullptr;
        tried = ok = false;
    }
};
static D3DApi g_api;

// cbuffer CB { float2 origin; float2 size; };
// VS: (pos - origin) / size * 2 - 1, y flipped; uv passed through.
// PS: tex.Sample(smp, uv) - the texture is already premultiplied.
// Source: wobble.hlsl, fxc /T vs_4_0 /E VS /O3 and /T ps_4_0 /E PS /O3.
static const BYTE kVS[] =
{
     68,  88,  66,  67, 209, 143, 
    100,  37, 232, 133, 137, 114, 
     65, 139, 149, 146,  35, 249, 
    248, 234,   1,   0,   0,   0, 
    116,   3,   0,   0,   5,   0, 
      0,   0,  52,   0,   0,   0, 
     12,   1,   0,   0,  96,   1, 
      0,   0, 184,   1,   0,   0, 
    248,   2,   0,   0,  82,  68, 
     69,  70, 208,   0,   0,   0, 
      1,   0,   0,   0,  64,   0, 
      0,   0,   1,   0,   0,   0, 
     28,   0,   0,   0,   0,   4, 
    254, 255,   0, 129,   0,   0, 
    165,   0,   0,   0,  60,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   1,   0, 
      0,   0,   1,   0,   0,   0, 
     67,  66,   0, 171,  60,   0, 
      0,   0,   2,   0,   0,   0, 
     88,   0,   0,   0,  16,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0, 136,   0, 
      0,   0,   0,   0,   0,   0, 
      8,   0,   0,   0,   2,   0, 
      0,   0, 144,   0,   0,   0, 
      0,   0,   0,   0, 160,   0, 
      0,   0,   8,   0,   0,   0, 
      8,   0,   0,   0,   2,   0, 
      0,   0, 144,   0,   0,   0, 
      0,   0,   0,   0, 111, 114, 
    105, 103, 105, 110,   0, 171, 
      1,   0,   3,   0,   1,   0, 
      2,   0,   0,   0,   0,   0, 
      0,   0,   0,   0, 115, 105, 
    122, 101,   0,  77, 105,  99, 
    114, 111, 115, 111, 102, 116, 
     32,  40,  82,  41,  32,  72, 
     76,  83,  76,  32,  83, 104, 
     97, 100, 101, 114,  32,  67, 
    111, 109, 112, 105, 108, 101, 
    114,  32,  49,  48,  46,  49, 
      0, 171, 171, 171,  73,  83, 
     71,  78,  76,   0,   0,   0, 
      2,   0,   0,   0,   8,   0, 
      0,   0,  56,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   3,   0,   0,   0, 
      0,   0,   0,   0,   3,   3, 
      0,   0,  65,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   3,   0,   0,   0, 
      1,   0,   0,   0,   3,   3, 
      0,   0,  80,  79,  83,  73, 
     84,  73,  79,  78,   0,  84, 
     69,  88,  67,  79,  79,  82, 
     68,   0, 171, 171,  79,  83, 
     71,  78,  80,   0,   0,   0, 
      2,   0,   0,   0,   8,   0, 
      0,   0,  56,   0,   0,   0, 
      0,   0,   0,   0,   1,   0, 
      0,   0,   3,   0,   0,   0, 
      0,   0,   0,   0,  15,   0, 
      0,   0,  68,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   3,   0,   0,   0, 
      1,   0,   0,   0,   3,  12, 
      0,   0,  83,  86,  95,  80, 
     79,  83,  73,  84,  73,  79, 
     78,   0,  84,  69,  88,  67, 
     79,  79,  82,  68,   0, 171, 
    171, 171,  83,  72,  68,  82, 
     56,   1,   0,   0,  64,   0, 
      1,   0,  78,   0,   0,   0, 
     89,   0,   0,   4,  70, 142, 
     32,   0,   0,   0,   0,   0, 
      1,   0,   0,   0,  95,   0, 
      0,   3,  50,  16,  16,   0, 
      0,   0,   0,   0,  95,   0, 
      0,   3,  50,  16,  16,   0, 
      1,   0,   0,   0, 103,   0, 
      0,   4, 242,  32,  16,   0, 
      0,   0,   0,   0,   1,   0, 
      0,   0, 101,   0,   0,   3, 
     50,  32,  16,   0,   1,   0, 
      0,   0, 104,   0,   0,   2, 
      1,   0,   0,   0,   0,   0, 
      0,   9,  50,   0,  16,   0, 
      0,   0,   0,   0,  70,  16, 
     16,   0,   0,   0,   0,   0, 
     70, 128,  32, 128,  65,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,  14,   0, 
      0,   8,  50,   0,  16,   0, 
      0,   0,   0,   0,  70,   0, 
     16,   0,   0,   0,   0,   0, 
    230, 138,  32,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
     50,   0,   0,  15,  50,   0, 
     16,   0,   0,   0,   0,   0, 
     70,   0,  16,   0,   0,   0, 
      0,   0,   2,  64,   0,   0, 
      0,   0,   0,  64,   0,   0, 
      0,  64,   0,   0,   0,   0, 
      0,   0,   0,   0,   2,  64, 
      0,   0,   0,   0, 128, 191, 
      0,   0, 128, 191,   0,   0, 
      0,   0,   0,   0,   0,   0, 
     54,   0,   0,   6,  34,  32, 
     16,   0,   0,   0,   0,   0, 
     26,   0,  16, 128,  65,   0, 
      0,   0,   0,   0,   0,   0, 
     54,   0,   0,   5,  18,  32, 
     16,   0,   0,   0,   0,   0, 
     10,   0,  16,   0,   0,   0, 
      0,   0,  54,   0,   0,   8, 
    194,  32,  16,   0,   0,   0, 
      0,   0,   2,  64,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0, 128,  63,  54,   0, 
      0,   5,  50,  32,  16,   0, 
      1,   0,   0,   0,  70,  16, 
     16,   0,   1,   0,   0,   0, 
     62,   0,   0,   1,  83,  84, 
     65,  84, 116,   0,   0,   0, 
      8,   0,   0,   0,   1,   0, 
      0,   0,   0,   0,   0,   0, 
      4,   0,   0,   0,   4,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   1,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   3,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0,   0,   0,   0,   0, 
      0,   0
};

static const BYTE kPS[] =
{
     68,  88,  66,  67,  75,  48,
    140, 251, 181, 222,  61,  35,
    104,   5,   9, 240, 208,  74,
    219,  89,   1,   0,   0,   0,
     16,  17,   0,   0,   5,   0,
      0,   0,  52,   0,   0,   0,
    216,   1,   0,   0,  48,   2,
      0,   0, 100,   2,   0,   0,
    148,  16,   0,   0,  82,  68,
     69,  70, 156,   1,   0,   0,
      1,   0,   0,   0, 140,   0,
      0,   0,   3,   0,   0,   0,
     28,   0,   0,   0,   0,   4,
    255, 255,   0, 129,   0,   0,
    116,   1,   0,   0, 124,   0,
      0,   0,   3,   0,   0,   0,
      0,   0,   0,   0,   0,   0,
      0,   0,   0,   0,   0,   0,
      0,   0,   0,   0,   1,   0,
      0,   0,   1,   0,   0,   0,
    128,   0,   0,   0,   2,   0,
      0,   0,   5,   0,   0,   0,
      4,   0,   0,   0, 255, 255,
    255, 255,   0,   0,   0,   0,
      1,   0,   0,   0,  13,   0,
      0,   0, 132,   0,   0,   0,
      0,   0,   0,   0,   0,   0,
      0,   0,   0,   0,   0,   0,
      0,   0,   0,   0,   1,   0,
      0,   0,   1,   0,   0,   0,
      1,   0,   0,   0, 115, 109,
    112,   0, 116, 101, 120,   0,
     71, 108, 111, 119,   0, 171,
    171, 171, 132,   0,   0,   0,
      6,   0,   0,   0, 164,   0,
      0,   0,  80,   6,   0,   0,
      0,   0,   0,   0,   0,   0,
      0,   0,  52,   1,   0,   0,
      0,   0,   0,   0,  16,   0,
      0,   0,   2,   0,   0,   0,
     56,   1,   0,   0,   0,   0,
      0,   0,  72,   1,   0,   0,
     16,   0,   0,   0,  16,   0,
      0,   0,   2,   0,   0,   0,
     56,   1,   0,   0,   0,   0,
      0,   0,  76,   1,   0,   0,
     32,   0,   0,   0,  16,   0,
      0,   0,   2,   0,   0,   0,
     56,   1,   0,   0,   0,   0,
      0,   0,  81,   1,   0,   0,
     48,   0,   0,   0,  16,   0,
      0,   0,   2,   0,   0,   0,
     56,   1,   0,   0,   0,   0,
      0,   0,  88,   1,   0,   0,
     64,   0,   0,   0,  16,   0,
      0,   0,   2,   0,   0,   0,
     56,   1,   0,   0,   0,   0,
      0,   0,  93,   1,   0,   0,
     80,   0,   0,   0,   0,   6,
      0,   0,   2,   0,   0,   0,
    100,   1,   0,   0,   0,   0,
      0,   0, 104, 100, 114,   0,
      1,   0,   3,   0,   1,   0,
      4,   0,   0,   0,   0,   0,
      0,   0,   0,   0, 107, 101,
    121,   0,  98, 111, 100, 121,
      0,  99,  97, 110, 118,  97,
    115,   0, 102, 105, 108, 108,
      0, 115, 112, 114,   0, 171,
    171, 171,   1,   0,   3,   0,
      1,   0,   4,   0,  96,   0,
      0,   0,   0,   0,   0,   0,
     77, 105,  99, 114, 111, 115,
    111, 102, 116,  32,  40,  82,
     41,  32,  72,  76,  83,  76,
     32,  83, 104,  97, 100, 101,
    114,  32,  67, 111, 109, 112,
    105, 108, 101, 114,  32,  49,
     48,  46,  49,   0,  73,  83,
     71,  78,  80,   0,   0,   0,
      2,   0,   0,   0,   8,   0,
      0,   0,  56,   0,   0,   0,
      0,   0,   0,   0,   1,   0,
      0,   0,   3,   0,   0,   0,
      0,   0,   0,   0,  15,   0,
      0,   0,  68,   0,   0,   0,
      0,   0,   0,   0,   0,   0,
      0,   0,   3,   0,   0,   0,
      1,   0,   0,   0,   3,   3,
      0,   0,  83,  86,  95,  80,
     79,  83,  73,  84,  73,  79,
     78,   0,  84,  69,  88,  67,
     79,  79,  82,  68,   0, 171,
    171, 171,  79,  83,  71,  78,
     44,   0,   0,   0,   1,   0,
      0,   0,   8,   0,   0,   0,
     32,   0,   0,   0,   0,   0,
      0,   0,   0,   0,   0,   0,
      3,   0,   0,   0,   0,   0,
      0,   0,  15,   0,   0,   0,
     83,  86,  95,  84,  65,  82,
     71,  69,  84,   0, 171, 171,
     83,  72,  68,  82,  40,  14,
      0,   0,  64,   0,   0,   0,
    138,   3,   0,   0,  89,   8,
      0,   4,  70, 142,  32,   0,
      1,   0,   0,   0, 101,   0,
      0,   0,  90,   0,   0,   3,
      0,  96,  16,   0,   0,   0,
      0,   0,  88,  24,   0,   4,
      0, 112,  16,   0,   0,   0,
      0,   0,  85,  85,   0,   0,
     98,  16,   0,   3,  50,  16,
     16,   0,   1,   0,   0,   0,
    101,   0,   0,   3, 242,  32,
     16,   0,   0,   0,   0,   0,
    104,   0,   0,   2,   7,   0,
      0,   0,  69,   0,   0,   9,
    242,   0,  16,   0,   0,   0,
      0,   0,  70,  16,  16,   0,
      1,   0,   0,   0,  70, 126,
     16,   0,   0,   0,   0,   0,
      0,  96,  16,   0,   0,   0,
      0,   0,  27,   0,   0,   6,
     18,   0,  16,   0,   1,   0,
      0,   0,  10, 128,  32,   0,
      1,   0,   0,   0,   0,   0,
      0,   0,  33,   0,   0,   7,
     34,   0,  16,   0,   1,   0,
      0,   0,   1,  64,   0,   0,
      0,   0,   0,   0,  10,   0,
     16,   0,   1,   0,   0,   0,
     29,   0,   0,   7,  66,   0,
     16,   0,   1,   0,   0,   0,
      1,  64,   0,   0,   0,   0,
      0,   0,  58,   0,  16,   0,
      0,   0,   0,   0,  60,   0,
      0,   7,  34,   0,  16,   0,
      1,   0,   0,   0,  42,   0,
     16,   0,   1,   0,   0,   0,
     26,   0,  16,   0,   1,   0,
      0,   0,  31,   0,   4,   3,
     26,   0,  16,   0,   1,   0,
      0,   0,  54,   0,   0,   5,
    242,  32,  16,   0,   0,   0,
      0,   0,  70,  14,  16,   0,
      0,   0,   0,   0,  62,   0,
      0,   1,  21,   0,   0,   1,
     56,   0,   0,   8,  98,   0,
     16,   0,   1,   0,   0,   0,
      6,  17,  16,   0,   1,   0,
      0,   0,   6, 129,  32,   0,
      1,   0,   0,   0,   3,   0,
      0,   0,  49,   0,   0,   8,
     50,   0,  16,   0,   2,   0,
      0,   0, 150,   5,  16,   0,
      1,   0,   0,   0,  70, 128,
     32,   0,   1,   0,   0,   0,
      2,   0,   0,   0,  60,   0,
      0,   7, 130,   0,  16,   0,
      1,   0,   0,   0,  26,   0,
     16,   0,   2,   0,   0,   0,
     10,   0,  16,   0,   2,   0,
      0,   0,  49,   0,   0,   8,
     98,   0,  16,   0,   1,   0,
      0,   0, 166, 139,  32,   0,
      1,   0,   0,   0,   2,   0,
      0,   0,  86,   6,  16,   0,
      1,   0,   0,   0,  60,   0,
      0,   7,  34,   0,  16,   0,
      1,   0,   0,   0,  26,   0,
     16,   0,   1,   0,   0,   0,
     58,   0,  16,   0,   1,   0,
      0,   0,  60,   0,   0,   7,
     34,   0,  16,   0,   1,   0,
      0,   0,  42,   0,  16,   0,
      1,   0,   0,   0,  26,   0,
     16,   0,   1,   0,   0,   0,
     31,   0,   4,   3,  26,   0,
     16,   0,   1,   0,   0,   0,
     54,   0,   0,   5, 242,  32,
     16,   0,   0,   0,   0,   0,
     70,  14,  16,   0,   0,   0,
      0,   0,  62,   0,   0,   1,
     21,   0,   0,   1,  14,   0,
      0,   7, 226,   0,  16,   0,
      1,   0,   0,   0,   6,   9,
     16,   0,   0,   0,   0,   0,
    246,  15,  16,   0,   0,   0,
      0,   0,   0,   0,   0,   9,
    226,   0,  16,   0,   1,   0,
      0,   0,  86,  14,  16,   0,
      1,   0,   0,   0,   6, 137,
     32, 128,  65,   0,   0,   0,
      1,   0,   0,   0,   1,   0,
      0,   0,  16,   0,   0,   7,
     34,   0,  16,   0,   1,   0,
      0,   0, 150,   7,  16,   0,
      1,   0,   0,   0, 150,   7,
     16,   0,   1,   0,   0,   0,
     75,   0,   0,   5,  34,   0,
     16,   0,   1,   0,   0,   0,
     26,   0,  16,   0,   1,   0,
      0,   0,  56,   0,   0,   8,
     66,   0,  16,   0,   1,   0,
      0,   0,  42, 128,  32,   0,
      1,   0,   0,   0,   0,   0,
      0,   0,   1,  64,   0,   0,
      0,   0,   0,  63,  50,   0,
      0,  11,  34,   0,  16,   0,
      1,   0,   0,   0,  42, 128,
     32, 128,  65,   0,   0,   0,
      1,   0,   0,   0,   0,   0,
      0,   0,   1,  64,   0,   0,
      0,   0,   0,  63,  26,   0,
     16,   0,   1,   0,   0,   0,
     14,   0,   0,  10,  66,   0,
     16,   0,   1,   0,   0,   0,
      2,  64,   0,   0,   0,   0,
    128,  63,   0,   0, 128,  63,
      0,   0, 128,  63,   0,   0,
    128,  63,  42,   0,  16,   0,
      1,   0,   0,   0,  56,  32,
      0,   7,  34,   0,  16,   0,
      1,   0,   0,   0,  42,   0,
     16,   0,   1,   0,   0,   0,
     26,   0,  16,   0,   1,   0,
      0,   0,  50,   0,   0,   9,
     66,   0,  16,   0,   1,   0,
      0,   0,  26,   0,  16,   0,
      1,   0,   0,   0,   1,  64,
      0,   0,   0,   0,   0, 192,
      1,  64,   0,   0,   0,   0,
     64,  64,  56,   0,   0,   7,
     34,   0,  16,   0,   1,   0,
      0,   0,  26,   0,  16,   0,
      1,   0,   0,   0,  26,   0,
     16,   0,   1,   0,   0,   0,
     50,   0,   0,  10,  34,   0,
     16,   0,   1,   0,   0,   0,
     42,   0,  16, 128,  65,   0,
      0,   0,   1,   0,   0,   0,
     26,   0,  16,   0,   1,   0,
      0,   0,   1,  64,   0,   0,
      0,   0, 128,  63,  29,   0,
      0,   7,  66,   0,  16,   0,
      1,   0,   0,   0,   1,  64,
      0,   0,   0,   0,   0,   0,
     26,   0,  16,   0,   1,   0,
      0,   0,  31,   0,   4,   3,
     42,   0,  16,   0,   1,   0,
      0,   0,  54,   0,   0,   5,
    242,  32,  16,   0,   0,   0,
      0,   0,  70,  14,  16,   0,
      0,   0,   0,   0,  62,   0,
      0,   1,  21,   0,   0,   1,
     49,   0,   0,   8,  66,   0,
     16,   0,   1,   0,   0,   0,
      1,  64,   0,   0,   0,   0,
    192,  63,  58, 128,  32,   0,
      1,   0,   0,   0,   4,   0,
      0,   0,  31,   0,   4,   3,
     42,   0,  16,   0,   1,   0,
      0,   0,   0,  32,   0,   8,
    130,   0,  16,   0,   2,   0,
      0,   0,  58, 128,  32,   0,
      1,   0,   0,   0,   4,   0,
      0,   0,   1,  64,   0,   0,
      0,   0,   0, 192,  56,   0,
      0,   8, 114,   0,  16,   0,
      2,   0,   0,   0, 246,  15,
     16,   0,   2,   0,   0,   0,
     70, 130,  32,   0,   1,   0,
      0,   0,   4,   0,   0,   0,
     50,   0,   0,  10, 242,   0,
     16,   0,   2,   0,   0,   0,
     70,  14,  16,   0,   2,   0,
      0,   0, 246,  15,  16,   0,
      0,   0,   0,   0,  70,  14,
     16, 128,  65,   0,   0,   0,
      0,   0,   0,   0,  50,   0,
      0,   9, 242,  32,  16,   0,
      0,   0,   0,   0,  86,   5,
     16,   0,   1,   0,   0,   0,
     70,  14,  16,   0,   2,   0,
      0,   0,  70,  14,  16,   0,
      0,   0,   0,   0,  62,   0,
      0,   1,  21,   0,   0,   1,
     56,   0,   0,   8,  66,   0,
     16,   0,   1,   0,   0,   0,
     26,   0,  16,   0,   1,   0,
      0,   0,  58, 128,  32,   0,
      1,   0,   0,   0,   4,   0,
      0,   0,  50,   0,   0,  11,
    114,   0,  16,   0,   2,   0,
      0,   0,  70, 130,  32,   0,
      1,   0,   0,   0,   4,   0,
      0,   0, 246,  15,  16,   0,
      0,   0,   0,   0,  70,   2,
     16, 128,  65,   0,   0,   0,
      0,   0,   0,   0,  50,   0,
      0,   9, 114,   0,  16,   0,
      0,   0,   0,   0, 166,  10,
     16,   0,   1,   0,   0,   0,
     70,   2,  16,   0,   2,   0,
      0,   0,  70,   2,  16,   0,
      0,   0,   0,   0,  56,   0,
      0,   8,  34,   0,  16,   0,
      1,   0,   0,   0,  26,   0,
     16,   0,   1,   0,   0,   0,
     26, 128,  32,   0,   1,   0,
      0,   0,   0,   0,   0,   0,
     29,   0,   0,   7,  66,   0,
     16,   0,   1,   0,   0,   0,
      1,  64,   0,   0,   0,   0,
      0,   0,  26,   0,  16,   0,
      1,   0,   0,   0,  31,   0,
      4,   3,  42,   0,  16,   0,
      1,   0,   0,   0,  54,   0,
      0,   5, 130,  32,  16,   0,
      0,   0,   0,   0,  58,   0,
     16,   0,   0,   0,   0,   0,
     54,   0,   0,   5, 114,  32,
     16,   0,   0,   0,   0,   0,
     70,   2,  16,   0,   0,   0,
      0,   0,  62,   0,   0,   1,
     21,   0,   0,   1,  50,   0,
      0,  12, 194,   0,  16,   0,
      1,   0,   0,   0,   6,  20,
     16,   0,   1,   0,   0,   0,
      6, 132,  32,   0,   1,   0,
      0,   0,   3,   0,   0,   0,
      6, 132,  32, 128,  65,   0,
      0,   0,   1,   0,   0,   0,
      2,   0,   0,   0,  49,   0,
      0,  11,  50,   0,  16,   0,
      2,   0,   0,   0,   2,  64,
      0,   0,   0,   0,   0,  63,
      0,   0, 192,  63,   0,   0,
      0,   0,   0,   0,   0,   0,
    246, 143,  32,   0,   1,   0,
      0,   0,   0,   0,   0,   0,
      0,   0,   0,   9, 194,   0,
     16,   0,   2,   0,   0,   0,
    166,  14,  16,   0,   1,   0,
      0,   0,   6, 132,  32, 128,
     65,   0,   0,   0,   1,   0,
      0,   0,   5,   0,   0,   0,
      0,   0,   0,   9, 194,   0,
     16,   0,   2,   0,   0,   0,
    166,  14,  16,   0,   2,   0,
      0,   0, 166, 142,  32, 128,
     65,   0,   0,   0,   1,   0,
      0,   0,   7,   0,   0,   0,
     15,   0,   0,   8,  66,   0,
     16,   0,   2,   0,   0,   0,
     70, 128,  32,   0,   1,   0,
      0,   0,   7,   0,   0,   0,
    230,  10,  16,   0,   2,   0,
      0,   0,   0,   0,   0,   8,
     66,   0,  16,   0,   2,   0,
      0,   0,  42,   0,  16,   0,
      2,   0,   0,   0,  42, 128,
     32,   0,   1,   0,   0,   0,
      7,   0,   0,   0,  14,  32,
      0,   8,  66,   0,  16,   0,
      2,   0,   0,   0,  42,   0,
     16,   0,   2,   0,   0,   0,
     42, 128,  32,   0,   1,   0,
      0,   0,   5,   0,   0,   0,
      0,   0,   0,  10, 242,   0,
     16,   0,   3,   0,   0,   0,
     54, 137,  32, 128,  65,   0,
      0,   0,   1,   0,   0,   0,
      6,   0,   0,   0,  54, 137,
     32,   0,   1,   0,   0,   0,
      9,   0,   0,   0,  50,   0,
      0,  10, 242,   0,  16,   0,
      3,   0,   0,   0, 166,  10,
     16,   0,   2,   0,   0,   0,
    150,   3,  16,   0,   3,   0,
      0,   0,  70, 142,  32,   0,
      1,   0,   0,   0,   6,   0,
      0,   0,  56,   0,   0,   7,
    114,   0,  16,   0,   3,   0,
      0,   0, 246,  15,  16,   0,
      3,   0,   0,   0,  70,   2,
     16,   0,   3,   0,   0,   0,
      1,   0,   0,   7, 242,   0,
     16,   0,   3,   0,   0,   0,
     86,   5,  16,   0,   2,   0,
      0,   0,  70,  14,  16,   0,
      3,   0,   0,   0,  55,   0,
      0,   9,  18,   0,  16,   0,
      1,   0,   0,   0,  26,   0,
     16,   0,   2,   0,   0,   0,
      1,  64,   0,   0,   0,   0,
      0,   0,  10,   0,  16,   0,
      1,   0,   0,   0,  54,   0,
      0,   5, 242,   0,  16,   0,
      4,   0,   0,   0,  70,  14,
     16,   0,   3,   0,   0,   0,
     54,   0,   0,   5,  34,   0,
     16,   0,   2,   0,   0,   0,
      1,  64,   0,   0,   0,   0,
      0,   0,  48,   0,   0,   1,
     33,   0,   0,   7,  66,   0,
     16,   0,   2,   0,   0,   0,
     26,   0,  16,   0,   2,   0,
      0,   0,  10,   0,  16,   0,
      1,   0,   0,   0,   3,   0,
      4,   3,  42,   0,  16,   0,
      2,   0,   0,   0,  38,   0,
      0,   8,   0, 208,   0,   0,
     66,   0,  16,   0,   2,   0,
      0,   0,  26,   0,  16,   0,
      2,   0,   0,   0,   1,  64,
      0,   0,   3,   0,   0,   0,
     35,   0,   0,  15,  50,   0,
     16,   0,   5,   0,   0,   0,
     86,   5,  16,   0,   2,   0,
      0,   0,   2,  64,   0,   0,
      3,   0,   0,   0,   3,   0,
      0,   0,   0,   0,   0,   0,
      0,   0,   0,   0,   2,  64,
      0,   0,   1,   0,   0,   0,
      2,   0,   0,   0,   0,   0,
      0,   0,   0,   0,   0,   0,
      0,   0,   0,  11, 194,   0,
     16,   0,   5,   0,   0,   0,
    166,  14,  16,   0,   1,   0,
      0,   0,   6, 132,  32, 134,
     65,   0,   0,   0,   1,   0,
      0,   0,   5,   0,   0,   0,
     42,   0,  16,   0,   2,   0,
      0,   0,   0,   0,   0,  11,
    194,   0,  16,   0,   5,   0,
      0,   0, 166,  14,  16,   0,
      5,   0,   0,   0, 166, 142,
     32, 134,  65,   0,   0,   0,
      1,   0,   0,   0,   5,   0,
      0,   0,  26,   0,  16,   0,
      5,   0,   0,   0,  15,   0,
      0,  10,  18,   0,  16,   0,
      6,   0,   0,   0,  70, 128,
     32,   6,   1,   0,   0,   0,
      5,   0,   0,   0,  26,   0,
     16,   0,   5,   0,   0,   0,
    230,  10,  16,   0,   5,   0,
      0,   0,  56,   0,   0,  10,
    130,   0,  16,   0,   2,   0,
      0,   0,  58,   0,  16,   0,
      5,   0,   0,   0,  10, 128,
     32,   6,   1,   0,   0,   0,
      5,   0,   0,   0,  26,   0,
     16,   0,   5,   0,   0,   0,
     50,   0,   0,  13,  34,   0,
     16,   0,   6,   0,   0,   0,
     26, 128,  32, 134,  65,   0,
      0,   0,   1,   0,   0,   0,
      5,   0,   0,   0,  26,   0,
     16,   0,   5,   0,   0,   0,
     42,   0,  16,   0,   5,   0,
      0,   0,  58,   0,  16,   0,
      2,   0,   0,   0,   0,   0,
      0,  10,  98,   0,  16,   0,
      5,   0,   0,   0,   6,   1,
     16,   0,   6,   0,   0,   0,
    166, 139,  32,   6,   1,   0,
      0,   0,   5,   0,   0,   0,
     26,   0,  16,   0,   5,   0,
      0,   0,  14,   0,   0,  10,
    194,   0,  16,   0,   2,   0,
      0,   0,  86,   9,  16,   0,
      5,   0,   0,   0, 166, 142,
     32,   6,   1,   0,   0,   0,
      5,   0,   0,   0,  42,   0,
     16,   0,   2,   0,   0,   0,
     49,   0,   0,  10,  98,   0,
     16,   0,   5,   0,   0,   0,
    166,  11,  16,   0,   2,   0,
      0,   0,   2,  64,   0,   0,
      0,   0,   0,   0,   0,   0,
      0,   0,   0,   0,   0,   0,
      0,   0,   0,   0,  60,   0,
      0,   7,  34,   0,  16,   0,
      5,   0,   0,   0,  42,   0,
     16,   0,   5,   0,   0,   0,
     26,   0,  16,   0,   5,   0,
      0,   0,  49,   0,   0,  10,
    114,   0,  16,   0,   6,   0,
      0,   0,   2,  64,   0,   0,
      0,   0, 128,  63,   0,   0,
    128,  63,   0,   0,   0,  63,
      0,   0,   0,   0, 230,  10,
     16,   0,   2,   0,   0,   0,
     60,   0,   0,   7,  66,   0,
     16,   0,   5,   0,   0,   0,
     26,   0,  16,   0,   6,   0,
      0,   0,  10,   0,  16,   0,
      6,   0,   0,   0,  60,   0,
      0,   7,  34,   0,  16,   0,
      5,   0,   0,   0,  42,   0,
     16,   0,   5,   0,   0,   0,
     26,   0,  16,   0,   5,   0,
      0,   0,   0,   0,   0,  11,
    194,   0,  16,   0,   5,   0,
      0,   0, 166,  14,  16, 128,
     65,   0,   0,   0,   2,   0,
      0,   0,   2,  64,   0,   0,
      0,   0,   0,   0,   0,   0,
      0,   0,   0,   0, 128,  63,
      0,   0, 128,  63,  55,   0,
      0,   9,  66,   0,  16,   0,
      5,   0,   0,   0,  42,   0,
     16,   0,   6,   0,   0,   0,
     42,   0,  16,   0,   5,   0,
      0,   0,  42,   0,  16,   0,
      2,   0,   0,   0,  49,   0,
      0,   7,  18,   0,  16,   0,
      6,   0,   0,   0,  42,   0,
     16,   0,   5,   0,   0,   0,
      1,  64,   0,   0,  51,  51,
    179,  62,  56,   0,   0,   7,
     34,   0,  16,   0,   6,   0,
      0,   0,  42,   0,  16,   0,
      5,   0,   0,   0,   1,  64,
      0,   0,   0,   0, 128,  63,
      0,   0,   0,   7,  66,   0,
     16,   0,   5,   0,   0,   0,
     42,   0,  16,   0,   5,   0,
      0,   0,   1,  64,   0,   0,
     51,  51, 179, 190,  50,   0,
      0,   9,  66,   0,  16,   0,
      5,   0,   0,   0,  42,   0,
     16,   0,   5,   0,   0,   0,
      1,  64,   0,   0, 170, 170,
    138,  64,   1,  64,   0,   0,
     51,  51, 179,  62,  55,   0,
      0,   9,  66,   0,  16,   0,
      5,   0,   0,   0,  10,   0,
     16,   0,   6,   0,   0,   0,
     26,   0,  16,   0,   6,   0,
      0,   0,  42,   0,  16,   0,
      5,   0,   0,   0,  56,   0,
      0,   7,  66,   0,  16,   0,
      5,   0,   0,   0,  58,   0,
     16,   0,   5,   0,   0,   0,
     42,   0,  16,   0,   5,   0,
      0,   0,  55,   0,   0,   9,
     34,   0,  16,   0,   5,   0,
      0,   0,  26,   0,  16,   0,
      5,   0,   0,   0,   1,  64,
      0,   0,   0,   0,   0,   0,
     42,   0,  16,   0,   5,   0,
      0,   0,  50,   0,   0,  15,
    194,   0,  16,   0,   2,   0,
      0,   0, 166,  14,  16,   0,
      2,   0,   0,   0,   2,  64,
      0,   0,   0,   0,   0,   0,
      0,   0,   0,   0,   0,   0,
      0,  64,   0,   0,   0,  64,
      2,  64,   0,   0,   0,   0,
      0,   0,   0,   0,   0,   0,
      0,   0, 128, 191,   0,   0,
    128, 191,  15,   0,   0,   7,
     66,   0,  16,   0,   2,   0,
      0,   0, 230,  10,  16,   0,
      2,   0,   0,   0, 230,  10,
     16,   0,   2,   0,   0,   0,
     75,   0,   0,   5,  66,   0,
     16,   0,   2,   0,   0,   0,
     42,   0,  16,   0,   2,   0,
      0,   0,  49,   0,   0,   7,
    130,   0,  16,   0,   2,   0,
      0,   0,  42,   0,  16,   0,
      2,   0,   0,   0,   1,  64,
      0,   0, 205, 204,  12,  63,
     50,   0,   0,   9,  66,   0,
     16,   0,   5,   0,   0,   0,
     42,   0,  16,   0,   2,   0,
      0,   0,   1,  64,   0,   0,
    201,  38, 155, 191,   1,  64,
      0,   0,   0,   0, 128,  63,
      0,   0,   0,   7,  66,   0,
     16,   0,   2,   0,   0,   0,
     42,   0,  16,   0,   2,   0,
      0,   0,   1,  64,   0,   0,
    205, 204,  12, 191,  50,   0,
      0,   9,  66,   0,  16,   0,
      2,   0,   0,   0,  42,   0,
     16,   0,   2,   0,   0,   0,
      1,  64,   0,   0,  48, 161,
     61, 191,   1,  64,   0,   0,
    171, 170, 170,  62,  52,   0,
      0,   7,  66,   0,  16,   0,
      2,   0,   0,   0,  42,   0,
     16,   0,   2,   0,   0,   0,
      1,  64,   0,   0,   0,   0,
      0,   0,  55,   0,   0,   9,
     66,   0,  16,   0,   2,   0,
      0,   0,  58,   0,  16,   0,
      2,   0,   0,   0,  42,   0,
     16,   0,   5,   0,   0,   0,
     42,   0,  16,   0,   2,   0,
      0,   0,  55,   0,   0,   9,
     66,   0,  16,   0,   2,   0,
      0,   0,  10,   0,  16,   0,
      2,   0,   0,   0,  26,   0,
     16,   0,   5,   0,   0,   0,
     42,   0,  16,   0,   2,   0,
      0,   0,  56,   0,   0,  10,
    130,   0,  16,   0,   6,   0,
      0,   0,  42,   0,  16,   0,
      2,   0,   0,   0,  58, 128,
     32,   6,   1,   0,   0,   0,
      5,   0,   0,   0,  10,   0,
     16,   0,   5,   0,   0,   0,
     56,   0,   0,  10, 114,   0,
     16,   0,   6,   0,   0,   0,
    246,  15,  16,   0,   6,   0,
      0,   0,  70, 130,  32,   6,
      1,   0,   0,   0,   5,   0,
      0,   0,  10,   0,  16,   0,
      5,   0,   0,   0,  50,   0,
      0,  13,  66,   0,  16,   0,
      2,   0,   0,   0,  58, 128,
     32, 134,  65,   0,   0,   0,
      1,   0,   0,   0,   5,   0,
      0,   0,  10,   0,  16,   0,
      5,   0,   0,   0,  42,   0,
     16,   0,   2,   0,   0,   0,
      1,  64,   0,   0,   0,   0,
    128,  63,  50,   0,   0,   9,
    242,   0,  16,   0,   4,   0,
      0,   0,  70,  14,  16,   0,
      4,   0,   0,   0, 166,  10,
     16,   0,   2,   0,   0,   0,
     70,  14,  16,   0,   6,   0,
      0,   0,  30,   0,   0,   7,
     34,   0,  16,   0,   2,   0,
      0,   0,  26,   0,  16,   0,
      2,   0,   0,   0,   1,  64,
      0,   0,   1,   0,   0,   0,
     22,   0,   0,   1,  56,   0,
      0,   7, 242,   0,  16,   0,
      1,   0,   0,   0,  86,   5,
     16,   0,   1,   0,   0,   0,
     70,  14,  16,   0,   4,   0,
      0,   0,  49,   0,   0,   7,
     18,   0,  16,   0,   2,   0,
      0,   0,   1,  64,   0,   0,
      0,   0, 128,  63,  58,   0,
     16,   0,   1,   0,   0,   0,
     14,   0,   0,   7, 242,   0,
     16,   0,   3,   0,   0,   0,
     70,  14,  16,   0,   1,   0,
      0,   0, 246,  15,  16,   0,
      1,   0,   0,   0,  55,   0,
      0,   9, 242,   0,  16,   0,
      1,   0,   0,   0,   6,   0,
     16,   0,   2,   0,   0,   0,
     70,  14,  16,   0,   3,   0,
      0,   0,  70,  14,  16,   0,
      1,   0,   0,   0,  49,   0,
      0,   8,  18,   0,  16,   0,
      2,   0,   0,   0,   1,  64,
      0,   0,   0,   0,   0,  63,
     58, 128,  32,   0,   1,   0,
      0,   0,   4,   0,   0,   0,
     31,   0,   4,   3,  10,   0,
     16,   0,   2,   0,   0,   0,
     50,   0,   0,   9, 114,   0,
     16,   0,   2,   0,   0,   0,
     70,   2,  16,   0,   1,   0,
      0,   0, 246,  15,  16,   0,
      0,   0,   0,   0,  70,   2,
     16,   0,   0,   0,   0,   0,
     51,   0,   0,   7, 114,  32,
     16,   0,   0,   0,   0,   0,
    246,  15,  16,   0,   0,   0,
      0,   0,  70,   2,  16,   0,
      2,   0,   0,   0,  54,   0,
      0,   5, 130,  32,  16,   0,
      0,   0,   0,   0,  58,   0,
     16,   0,   0,   0,   0,   0,
     62,   0,   0,   1,  21,   0,
      0,   1,   0,   0,   0,   8,
    130,   0,  16,   0,   1,   0,
      0,   0,  58,   0,  16, 128,
     65,   0,   0,   0,   1,   0,
      0,   0,   1,  64,   0,   0,
      0,   0, 128,  63,  56,   0,
      0,   7, 114,   0,  16,   0,
      1,   0,   0,   0, 246,  15,
     16,   0,   0,   0,   0,   0,
     70,   2,  16,   0,   1,   0,
      0,   0,  50,   0,   0,   9,
    114,  32,  16,   0,   0,   0,
      0,   0,  70,   2,  16,   0,
      0,   0,   0,   0, 246,  15,
     16,   0,   1,   0,   0,   0,
     70,   2,  16,   0,   1,   0,
      0,   0,  54,   0,   0,   5,
    130,  32,  16,   0,   0,   0,
      0,   0,  58,   0,  16,   0,
      0,   0,   0,   0,  62,   0,
      0,   1,  83,  84,  65,  84,
    116,   0,   0,   0, 125,   0,
      0,   0,   7,   0,   0,   0,
      0,   0,   0,   0,   2,   0,
      0,   0,  72,   0,   0,   0,
      5,   0,   0,   0,   8,   0,
      0,   0,   7,   0,   0,   0,
      7,   0,   0,   0,   0,   0,
      0,   0,   0,   0,   0,   0,
      0,   0,   0,   0,   0,   0,
      0,   0,   0,   0,   0,   0,
      1,   0,   0,   0,   0,   0,
      0,   0,   0,   0,   0,   0,
      0,   0,   0,   0,   0,   0,
      0,   0,   9,   0,   0,   0,
      7,   0,   0,   0,   1,   0,
      0,   0,   0,   0,   0,   0,
      0,   0,   0,   0,   0,   0,
      0,   0,   0,   0,   0,   0,
      0,   0,   0,   0,   0,   0,
      0,   0,   0,   0,   0,   0
};

// The pixel shader's glow constants (cbuffer Glow, b1). Waves are the most
// sprites any effect uses: 3 rows of 10.
static constexpr int kGlowMaxSprites = 32;
struct GlowCB {
    float hdr[4];       // sprite count, strength, key tolerance, 1 = beams
    float key[4];       // the backdrop's colour as captured
    float body[4];      // the window inside the canvas, in texels
    float canvas[4];    // texture size
    float fill[4];      // rgb: the live glass, painted over the key; w 1 = use it
    float spr[kGlowMaxSprites * 3][4];
};
static_assert(sizeof(GlowCB) == 1616, "matches cbuffer Glow in wobble.hlsl");

// Lives on the worker's stack, never as a global: Windhawk doesn't call
// Wh_ModUninit at process exit, and releasing DXGI objects from DllMain under
// the loader lock is what Microsoft warns against.
struct Device {
    Com<ID3D11Device>         dev;
    Com<ID3D11DeviceContext>  ctx;
    Com<ID3D11DeviceContext1> ctx1;     // ClearView; null on old runtimes
    Com<ID3D11VertexShader>   vs;
    Com<ID3D11PixelShader>    ps;
    Com<ID3D11InputLayout>    layout;
    Com<ID3D11SamplerState>   sampler;
    Com<ID3D11BlendState>     blend;
    Com<ID3D11Buffer>         cb;
    Com<ID3D11Buffer>         cbGlow;
    bool ok = false;
    bool warmed = false;
    bool glowSet = false;      // cbGlow holds sprites, not a zero count
    HRESULT glowHr = S_OK;     // DIAG 1.2.9
    unsigned glowWrites = 0;   // DIAG 1.2.9

    // nullptr turns the glow off (a zero count), written once.
    void SetGlow(const GlowCB* g) {
        if (!g && !glowSet) return;
        D3D11_MAPPED_SUBRESOURCE map{};
        glowHr = ctx->Map(cbGlow, 0, D3D11_MAP_WRITE_DISCARD, 0, &map);    // DIAG 1.2.9
        if (FAILED(glowHr)) return;
        ++glowWrites;
        if (g) memcpy(map.pData, g, sizeof(GlowCB));
        else   memset(map.pData, 0, sizeof(GlowCB));
        ctx->Unmap(cbGlow, 0);
        glowSet = g != nullptr;
    }

    bool Init() {
        if (ok) return true;
        if (!g_api.Load()) return false;

        const UINT flags = D3D11_CREATE_DEVICE_BGRA_SUPPORT | D3D11_CREATE_DEVICE_SINGLETHREADED;
        D3D_FEATURE_LEVEL got{};
        HRESULT hr = g_api.CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, flags,
                                        nullptr, 0, D3D11_SDK_VERSION, &dev, &got, &ctx);
        if (FAILED(hr)) {
            Wh_Log(L"D3D11 hardware device failed hr=0x%08X, trying WARP", hr);
            hr = g_api.CreateDevice(nullptr, D3D_DRIVER_TYPE_WARP, nullptr, flags,
                                    nullptr, 0, D3D11_SDK_VERSION, &dev, &got, &ctx);
        }
        if (FAILED(hr)) { Wh_Log(L"D3D11CreateDevice failed hr=0x%08X", hr); return false; }

        ctx->QueryInterface(__uuidof(ID3D11DeviceContext1), (void**)&ctx1);
        {
            // One frame queued at most: the wobble is drawn from the newest
            // window position, never from one a frame old.
            Com<IDXGIDevice1> dxgi1;
            if (SUCCEEDED(dev->QueryInterface(__uuidof(IDXGIDevice1), (void**)&dxgi1)))
                dxgi1->SetMaximumFrameLatency(1);
        }

        if (FAILED(dev->CreateVertexShader(kVS, sizeof(kVS), nullptr, &vs))) return false;
        if (FAILED(dev->CreatePixelShader(kPS, sizeof(kPS), nullptr, &ps)))  return false;

        // Positions change every frame, texture coordinates never: two
        // streams, so only half the data is uploaded per frame.
        D3D11_INPUT_ELEMENT_DESC el[] = {
            {"POSITION", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
            {"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 1, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
        };
        if (FAILED(dev->CreateInputLayout(el, 2, kVS, sizeof(kVS), &layout))) return false;

        D3D11_SAMPLER_DESC sd{};
        sd.Filter   = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
        sd.AddressU = sd.AddressV = sd.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
        sd.MaxLOD   = D3D11_FLOAT32_MAX;
        if (FAILED(dev->CreateSamplerState(&sd, &sampler))) return false;

        D3D11_BLEND_DESC bd{};
        bd.RenderTarget[0].BlendEnable           = TRUE;
        bd.RenderTarget[0].SrcBlend              = D3D11_BLEND_ONE;
        bd.RenderTarget[0].DestBlend             = D3D11_BLEND_INV_SRC_ALPHA;
        bd.RenderTarget[0].BlendOp               = D3D11_BLEND_OP_ADD;
        bd.RenderTarget[0].SrcBlendAlpha         = D3D11_BLEND_ONE;
        bd.RenderTarget[0].DestBlendAlpha        = D3D11_BLEND_INV_SRC_ALPHA;
        bd.RenderTarget[0].BlendOpAlpha          = D3D11_BLEND_OP_ADD;
        bd.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
        if (FAILED(dev->CreateBlendState(&bd, &blend))) return false;

        D3D11_BUFFER_DESC cbd{};
        cbd.ByteWidth      = 16;
        cbd.Usage          = D3D11_USAGE_DYNAMIC;
        cbd.BindFlags      = D3D11_BIND_CONSTANT_BUFFER;
        cbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
        if (FAILED(dev->CreateBuffer(&cbd, nullptr, &cb))) return false;

        static const GlowCB kNoGlow{};
        D3D11_SUBRESOURCE_DATA gz{}; gz.pSysMem = &kNoGlow;
        cbd.ByteWidth = sizeof(GlowCB);
        if (FAILED(dev->CreateBuffer(&cbd, &gz, &cbGlow))) return false;
        glowSet = false;

        ok = true;
        return true;
    }

    bool Lost() const {
        return dev.p && FAILED(dev->GetDeviceRemovedReason());
    }
};

enum class DrawResult { Ok, DeviceLost, Failed };

// The swapchain spans the virtual desktop and never moves: a window-sized one
// moved with DirectComposition offsets lands its moves and its pixels on
// different frames, and the window then trails the pointer. Instead only the
// part the mesh covers is cleared, drawn and presented each frame.
struct LiveGlass;

struct Overlay {
    Device* d = nullptr;
    LiveGlass* glass = nullptr;     // the live blur under the copy, when it runs
    HWND hwnd = nullptr;
    Com<IDXGISwapChain1>          swap;
    Com<ID3D11RenderTargetView>   rtv;
    Com<IDCompositionDevice>      dcomp;
    Com<IDCompositionTarget>      target;
    Com<IDCompositionVisual>      visual;
    Com<ID3D11Texture2D>          tex;
    Com<ID3D11ShaderResourceView> srv;
    Com<ID3D11Buffer>             posVb;     // dynamic, the smooth grid's float2
    Com<ID3D11Buffer>             uvVb;      // static
    Com<ID3D11Buffer>             ib;        // static, 16-bit
    int  gridCells = 0;             // spring cells per side
    int  sub = 1;                   // drawn cells per spring cell
    UINT indexCount = 0;
    std::vector<Vec2> rows, smooth; // Draw's scratch: no allocation per frame

    int vx = 0, vy = 0, vw = 0, vh = 0;
    bool presentWarmed = false;
    int  fullFrames = 2;            // frames still to clear and present whole
    RECT hist[2] = {};              // drawn bounds of the last two frames

    ~Overlay() { Destroy(); }

    bool EnsureWindow();
    bool EnsureSurface();
    bool DisplayChanged() const;
    void WarmPipeline();
    void WarmPresent();
    bool SetContent(const Canvas& c, int cells);
    void ResetHistory() { fullFrames = 2; hist[0] = hist[1] = RECT{}; }
    void Show();
    void Hide();
    void Destroy();
    DrawResult Draw(const Mesh& m);
    DrawResult PresentClear();
};

static const wchar_t kOverlayClass[] = L"SeamlessWobblyOverlay";
static std::atomic<bool> g_classRegistered{false};

static bool EnsureClass() {
    if (g_classRegistered.load()) return true;
    WNDCLASSEXW wc{};
    wc.cbSize        = sizeof(wc);
    wc.lpfnWndProc   = DefWindowProcW;
    wc.hInstance     = MOD_HINSTANCE;
    wc.lpszClassName = kOverlayClass;
    if (!RegisterClassExW(&wc)) {
        Wh_Log(L"overlay: RegisterClassEx failed err=%u", GetLastError());
        return false;
    }
    g_classRegistered.store(true);
    return true;
}

bool Overlay::DisplayChanged() const {
    return vx != GetSystemMetrics(SM_XVIRTUALSCREEN) ||
           vy != GetSystemMetrics(SM_YVIRTUALSCREEN) ||
           vw != GetSystemMetrics(SM_CXVIRTUALSCREEN) ||
           vh != GetSystemMetrics(SM_CYVIRTUALSCREEN);
}

bool Overlay::EnsureWindow() {
    if (hwnd && !DisplayChanged()) return true;
    if (hwnd) {
        Wh_Log(L"overlay: display geometry changed, rebuilding");
        Destroy();
    }
    if (!EnsureClass()) return false;

    vx = GetSystemMetrics(SM_XVIRTUALSCREEN);
    vy = GetSystemMetrics(SM_YVIRTUALSCREEN);
    vw = GetSystemMetrics(SM_CXVIRTUALSCREEN);
    vh = GetSystemMetrics(SM_CYVIRTUALSCREEN);
    if (vw < 1 || vh < 1) return false;

    hwnd = CreateWindowExW(
        WS_EX_NOREDIRECTIONBITMAP | WS_EX_TRANSPARENT | WS_EX_TOPMOST |
            WS_EX_TOOLWINDOW | WS_EX_NOACTIVATE,
        kOverlayClass, L"", WS_POPUP, vx, vy, vw, vh,
        nullptr, nullptr, MOD_HINSTANCE, nullptr);
    if (!hwnd) {
        Wh_Log(L"overlay: CreateWindowEx failed err=%u", GetLastError());
        return false;
    }
    return true;
}

bool Overlay::EnsureSurface() {
    if (!d || !d->Init()) { Wh_Log(L"overlay: D3D device init failed"); return false; }
    if (!EnsureWindow()) return false;
    if (swap.p) return true;
    presentWarmed = false;
    ResetHistory();

    const bool built = [&] {
        Com<IDXGIDevice> dxgiDev;
        if (FAILED(d->dev->QueryInterface(__uuidof(IDXGIDevice), (void**)&dxgiDev)))
            return false;
        Com<IDXGIAdapter> adapter;
        if (FAILED(dxgiDev->GetAdapter(&adapter))) return false;
        Com<IDXGIFactory2> factory;
        if (FAILED(adapter->GetParent(__uuidof(IDXGIFactory2), (void**)&factory)))
            return false;

        DXGI_SWAP_CHAIN_DESC1 sd{};
        sd.Width            = vw;
        sd.Height           = vh;
        sd.Format           = DXGI_FORMAT_B8G8R8A8_UNORM;
        sd.SampleDesc.Count = 1;
        sd.BufferUsage      = DXGI_USAGE_RENDER_TARGET_OUTPUT;
        sd.BufferCount      = 2;
        sd.SwapEffect       = DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL;
        sd.AlphaMode        = DXGI_ALPHA_MODE_PREMULTIPLIED;
        HRESULT hr = factory->CreateSwapChainForComposition(d->dev, &sd, nullptr, &swap);
        if (FAILED(hr)) {
            Wh_Log(L"overlay: swapchain failed hr=0x%08X (%dx%d)", hr, vw, vh);
            return false;
        }

        Com<ID3D11Texture2D> back;
        if (FAILED(swap->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&back)))
            return false;
        if (FAILED(d->dev->CreateRenderTargetView(back, nullptr, &rtv))) return false;

        if (!dcomp.p) {
            hr = g_api.CreateCompDevice(dxgiDev, __uuidof(IDCompositionDevice), (void**)&dcomp);
            if (FAILED(hr)) {
                Wh_Log(L"overlay: DCompositionCreateDevice failed hr=0x%08X", hr);
                return false;
            }
            hr = dcomp->CreateTargetForHwnd(hwnd, TRUE, &target);
            if (FAILED(hr)) {
                Wh_Log(L"overlay: CreateTargetForHwnd failed hr=0x%08X", hr);
                return false;
            }
            if (FAILED(dcomp->CreateVisual(&visual))) return false;
            target->SetRoot(visual);
        }
        visual->SetContent(swap);
        dcomp->Commit();
        return true;
    }();

    if (!built) Destroy();
    return built;
}

void Overlay::WarmPipeline() {
    if (!d || !d->ok || d->warmed) return;
    d->warmed = true;

    // Offscreen, because a hidden overlay's presents are skipped by the
    // driver; a query makes the shader setup happen now, not on frame one.
    const UINT kSide = 64;
    D3D11_TEXTURE2D_DESC rt{};
    rt.Width = rt.Height = kSide;
    rt.MipLevels = rt.ArraySize = 1;
    rt.Format           = DXGI_FORMAT_B8G8R8A8_UNORM;
    rt.SampleDesc.Count = 1;
    rt.Usage            = D3D11_USAGE_DEFAULT;
    rt.BindFlags        = D3D11_BIND_RENDER_TARGET;
    Com<ID3D11Texture2D> rtTex;
    Com<ID3D11RenderTargetView> rtView;
    if (FAILED(d->dev->CreateTexture2D(&rt, nullptr, &rtTex)))           return;
    if (FAILED(d->dev->CreateRenderTargetView(rtTex, nullptr, &rtView))) return;

    const uint32_t pixel = 0xFF808080;
    D3D11_TEXTURE2D_DESC td{};
    td.Width = td.Height = 1;
    td.MipLevels = td.ArraySize = 1;
    td.Format           = DXGI_FORMAT_B8G8R8A8_UNORM;
    td.SampleDesc.Count = 1;
    td.Usage            = D3D11_USAGE_IMMUTABLE;
    td.BindFlags        = D3D11_BIND_SHADER_RESOURCE;
    D3D11_SUBRESOURCE_DATA srd{}; srd.pSysMem = &pixel; srd.SysMemPitch = 4;
    Com<ID3D11Texture2D> t;
    Com<ID3D11ShaderResourceView> v;
    if (FAILED(d->dev->CreateTexture2D(&td, &srd, &t)))           return;
    if (FAILED(d->dev->CreateShaderResourceView(t, nullptr, &v))) return;

    const Vec2 pos[3] = { {0, 0}, {(float)kSide, 0}, {0, (float)kSide} };
    const Vec2 uv[3]  = { {0, 0}, {1, 0}, {0, 1} };
    D3D11_BUFFER_DESC vbd{};
    vbd.ByteWidth = sizeof(pos);
    vbd.Usage     = D3D11_USAGE_IMMUTABLE;
    vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    D3D11_SUBRESOURCE_DATA p0{}; p0.pSysMem = pos;
    D3D11_SUBRESOURCE_DATA p1{}; p1.pSysMem = uv;
    Com<ID3D11Buffer> b0, b1;
    if (FAILED(d->dev->CreateBuffer(&vbd, &p0, &b0))) return;
    if (FAILED(d->dev->CreateBuffer(&vbd, &p1, &b1))) return;

    auto* ctx = d->ctx.p;
    struct CB { float ox, oy, sw, sh; } cbv{ 0, 0, (float)kSide, (float)kSide };
    D3D11_MAPPED_SUBRESOURCE map{};
    if (SUCCEEDED(ctx->Map(d->cb, 0, D3D11_MAP_WRITE_DISCARD, 0, &map))) {
        memcpy(map.pData, &cbv, sizeof(cbv));
        ctx->Unmap(d->cb, 0);
    }

    const float clear[4] = { 0, 0, 0, 0 };
    ID3D11RenderTargetView* rts[] = { rtView.p };
    ctx->OMSetRenderTargets(1, rts, nullptr);
    ctx->ClearRenderTargetView(rtView, clear);
    D3D11_VIEWPORT vp{ 0, 0, (float)kSide, (float)kSide, 0, 1 };
    ctx->RSSetViewports(1, &vp);
    UINT strides[2] = { sizeof(Vec2), sizeof(Vec2) }, offsets[2] = { 0, 0 };
    ID3D11Buffer* vbs[2] = { b0.p, b1.p };
    ctx->IASetVertexBuffers(0, 2, vbs, strides, offsets);
    ctx->IASetInputLayout(d->layout);
    ctx->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    ctx->VSSetShader(d->vs, nullptr, 0);
    ID3D11Buffer* cbs[] = { d->cb.p };
    ctx->VSSetConstantBuffers(0, 1, cbs);
    ctx->PSSetShader(d->ps, nullptr, 0);
    ID3D11Buffer* pcbs[] = { d->cbGlow.p };
    ctx->PSSetConstantBuffers(1, 1, pcbs);
    ID3D11ShaderResourceView* srvs[] = { v.p };
    ctx->PSSetShaderResources(0, 1, srvs);
    ID3D11SamplerState* smps[] = { d->sampler.p };
    ctx->PSSetSamplers(0, 1, smps);
    const float bf[4] = { 0, 0, 0, 0 };
    ctx->OMSetBlendState(d->blend, bf, 0xFFFFFFFF);
    ctx->Draw(3, 0);

    D3D11_QUERY_DESC qd{}; qd.Query = D3D11_QUERY_EVENT;
    Com<ID3D11Query> q;
    if (SUCCEEDED(d->dev->CreateQuery(&qd, &q))) {
        ctx->End(q);
        ctx->Flush();
        BOOL done = FALSE;
        const double limit = NowSeconds() + 1.0;
        while (ctx->GetData(q, &done, sizeof(done), 0) != S_OK &&
               NowSeconds() < limit && !QuitRequested())
            Sleep(0);
    } else {
        ctx->Flush();
    }
    ID3D11ShaderResourceView* none[] = { nullptr };
    ctx->PSSetShaderResources(0, 1, none);
}

void Overlay::WarmPresent() {
    if (!swap.p || !hwnd || !d || presentWarmed) return;
    presentWarmed = true;
    ShowWindow(hwnd, SW_SHOWNOACTIVATE);
    PresentClear();
    ShowWindow(hwnd, SW_HIDE);
}

bool Overlay::SetContent(const Canvas& c, int cells) {
    if (!d || !d->ok) return false;
    srv.reset();
    tex.reset();

    D3D11_TEXTURE2D_DESC td{};
    td.Width            = c.w;
    td.Height           = c.h;
    td.MipLevels        = 1;
    td.ArraySize        = 1;
    td.Format           = DXGI_FORMAT_B8G8R8A8_UNORM;
    td.SampleDesc.Count = 1;
    td.Usage            = D3D11_USAGE_IMMUTABLE;
    td.BindFlags        = D3D11_BIND_SHADER_RESOURCE;
    D3D11_SUBRESOURCE_DATA srd{};
    srd.pSysMem     = c.px.data();
    srd.SysMemPitch = c.w * 4;
    HRESULT hr = d->dev->CreateTexture2D(&td, &srd, &tex);
    if (FAILED(hr)) {
        Wh_Log(L"overlay: texture %dx%d failed hr=0x%08X", c.w, c.h, hr);
        return false;
    }
    if (FAILED(d->dev->CreateShaderResourceView(tex, nullptr, &srv))) return false;

    if (cells == gridCells && posVb.p && uvVb.p && ib.p) return true;
    posVb.reset(); uvVb.reset(); ib.reset();
    gridCells = 0;

    // The springs move a coarse grid; the drawn grid is about 64 cells per
    // side, laid on smooth curves through the springs (SmoothGrid), so a bent
    // edge or border never shows a sharp fold. 65 x 65 vertices fit 16-bit indices.
    sub = std::max(1, 64 / cells);
    const int rc = cells * sub;
    const int n = rc + 1;
    std::vector<Vec2> uv((size_t)n * n);
    for (int j = 0; j < n; ++j)
        for (int i = 0; i < n; ++i)
            uv[(size_t)j * n + i] = Vec2{ (float)i / rc, (float)j / rc };
    rows.resize((size_t)(cells + 1) * n);
    smooth.resize(uv.size());
    std::vector<uint16_t> idx;
    idx.reserve((size_t)rc * rc * 6);
    for (int j = 0; j < rc; ++j)
        for (int i = 0; i < rc; ++i) {
            const uint16_t a = (uint16_t)(j * n + i), b = (uint16_t)(a + 1);
            const uint16_t c2 = (uint16_t)(a + n),    dd = (uint16_t)(c2 + 1);
            idx.insert(idx.end(), { a, b, c2, b, dd, c2 });
        }

    D3D11_BUFFER_DESC bd{};
    bd.ByteWidth      = (UINT)(sizeof(Vec2) * uv.size());
    bd.Usage          = D3D11_USAGE_DYNAMIC;
    bd.BindFlags      = D3D11_BIND_VERTEX_BUFFER;
    bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
    if (FAILED(d->dev->CreateBuffer(&bd, nullptr, &posVb))) return false;

    D3D11_BUFFER_DESC ud{};
    ud.ByteWidth = bd.ByteWidth;
    ud.Usage     = D3D11_USAGE_IMMUTABLE;
    ud.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    D3D11_SUBRESOURCE_DATA us{}; us.pSysMem = uv.data();
    if (FAILED(d->dev->CreateBuffer(&ud, &us, &uvVb))) return false;

    D3D11_BUFFER_DESC id{};
    id.ByteWidth = (UINT)(sizeof(uint16_t) * idx.size());
    id.Usage     = D3D11_USAGE_IMMUTABLE;
    id.BindFlags = D3D11_BIND_INDEX_BUFFER;
    D3D11_SUBRESOURCE_DATA is{}; is.pSysMem = idx.data();
    if (FAILED(d->dev->CreateBuffer(&id, &is, &ib))) return false;

    gridCells  = cells;
    indexCount = (UINT)idx.size();
    return true;
}

// Catmull-Rom through p1 and p2 at t in [0, 1]: passes through every spring
// node, bends smoothly between them and keeps straight lines straight.
static inline Vec2 CatmullRom(const Vec2& p0, const Vec2& p1, const Vec2& p2, const Vec2& p3,
                              float t) {
    const float t2 = t * t, t3 = t2 * t;
    const float a = -0.5f * t3 + t2 - 0.5f * t;
    const float b =  1.5f * t3 - 2.5f * t2 + 1.0f;
    const float c = -1.5f * t3 + 2.0f * t2 + 0.5f * t;
    const float d =  0.5f * t3 - 0.5f * t2;
    return Vec2{ a * p0.x + b * p1.x + c * p2.x + d * p3.x,
                 a * p0.y + b * p1.y + c * p2.y + d * p3.y };
}

// Node k of a line of n (stride apart), continued straight past either end.
static inline Vec2 LineNode(const Vec2* line, int stride, int n, int k) {
    if (k < 0) {
        const Vec2 a = line[0], b = line[stride];
        return Vec2{ 2 * a.x - b.x, 2 * a.y - b.y };
    }
    if (k >= n) {
        const Vec2 a = line[(size_t)(n - 1) * stride], b = line[(size_t)(n - 2) * stride];
        return Vec2{ 2 * a.x - b.x, 2 * a.y - b.y };
    }
    return line[(size_t)k * stride];
}

// Spring grid (n x n nodes) to the drawn grid ((n-1)*sub+1 per side): along
// each spring row first, then down each drawn column.
static void SmoothGrid(const std::vector<Vec2>& pos, int n, int sub, std::vector<Vec2>& rows,
                       std::vector<Vec2>& out) {
    const int rn = (n - 1) * sub + 1;
    for (int j = 0; j < n; ++j) {
        const Vec2* line = &pos[(size_t)j * n];
        Vec2* dst = &rows[(size_t)j * rn];
        for (int I = 0; I < rn; ++I) {
            const int k = std::min(I / sub, n - 2);
            const float t = (float)(I - k * sub) / sub;
            dst[I] = CatmullRom(LineNode(line, 1, n, k - 1), line[k], line[k + 1],
                                LineNode(line, 1, n, k + 2), t);
        }
    }
    for (int I = 0; I < rn; ++I) {
        const Vec2* col = &rows[I];
        for (int J = 0; J < rn; ++J) {
            const int k = std::min(J / sub, n - 2);
            const float t = (float)(J - k * sub) / sub;
            out[(size_t)J * rn + I] =
                CatmullRom(LineNode(col, rn, n, k - 1), col[(size_t)k * rn],
                           col[(size_t)(k + 1) * rn], LineNode(col, rn, n, k + 2), t);
        }
    }
}

// -----------------------------------------------------------------------------
// Live glass
// -----------------------------------------------------------------------------
// The copy is a picture, so its glass could only be a flat colour. Under the
// overlay sits a click-through window holding the real blur of what is behind
// it (the host backdrop, blurred), clipped every frame to the bent outline of
// the window. The copy then paints only the glass's tint over it.

namespace liveglass {

// IGeometrySource2DInterop
struct GeometryInterop : ::IUnknown {
    virtual HRESULT STDMETHODCALLTYPE GetGeometry(ID2D1Geometry** value) = 0;
    virtual HRESULT STDMETHODCALLTYPE TryGetGeometryUsingFactory(ID2D1Factory* factory,
                                                                 ID2D1Geometry** value) = 0;
};

// IGraphicsEffectD2D1Interop
struct EffectInterop : ::IUnknown {
    virtual HRESULT STDMETHODCALLTYPE GetEffectId(GUID* id) = 0;
    virtual HRESULT STDMETHODCALLTYPE GetNamedPropertyMapping(LPCWSTR name, UINT* index,
                                                              int* mapping) = 0;
    virtual HRESULT STDMETHODCALLTYPE GetPropertyCount(UINT* count) = 0;
    virtual HRESULT STDMETHODCALLTYPE GetProperty(UINT index, void** value) = 0;
    virtual HRESULT STDMETHODCALLTYPE GetSource(UINT index, void** source) = 0;
    virtual HRESULT STDMETHODCALLTYPE GetSourceCount(UINT* count) = 0;
};

}  // namespace liveglass

template <> inline constexpr winrt::guid winrt::impl::guid_v<liveglass::GeometryInterop>{
    0x0657AF73, 0x53FD, 0x47CF, {0x84, 0xFF, 0xC8, 0x49, 0x2D, 0x2A, 0x80, 0xA3}};
template <> inline constexpr winrt::guid winrt::impl::guid_v<liveglass::EffectInterop>{
    0x2FC57384, 0xA068, 0x44D7, {0xA3, 0x31, 0x30, 0x98, 0x2F, 0xCF, 0x71, 0x77}};

namespace liveglass {

namespace WUC = winrt::Windows::UI::Composition;
namespace WGE = winrt::Windows::Graphics::Effects;

// Hands a D2D path to composition as a CompositionPath.
struct PathSource : winrt::implements<PathSource, winrt::Windows::Graphics::IGeometrySource2D,
                                      GeometryInterop> {
    ID2D1Geometry* g;
    explicit PathSource(ID2D1Geometry* geo) : g(geo) { g->AddRef(); }
    ~PathSource() { g->Release(); }
    HRESULT STDMETHODCALLTYPE GetGeometry(ID2D1Geometry** v) override {
        g->AddRef(); *v = g; return S_OK;
    }
    HRESULT STDMETHODCALLTYPE TryGetGeometryUsingFactory(ID2D1Factory*, ID2D1Geometry** v) override {
        *v = nullptr; return E_NOTIMPL;
    }
};

// D2D Gaussian blur, hard edges (the clip makes the edge).
struct Blur : winrt::implements<Blur, WGE::IGraphicsEffect, WGE::IGraphicsEffectSource,
                                EffectInterop> {
    float sigma;
    WGE::IGraphicsEffectSource src;
    winrt::hstring name = L"Blur";
    Blur(float s, WGE::IGraphicsEffectSource x) : sigma(s), src(std::move(x)) {}
    winrt::hstring Name() { return name; }
    void Name(winrt::hstring const& n) { name = n; }
    HRESULT STDMETHODCALLTYPE GetEffectId(GUID* id) override {
        *id = {0x1FEB6D69, 0x2FE6, 0x4AC9, {0x8C, 0x58, 0x1D, 0x7F, 0x93, 0xE7, 0xA6, 0xA5}};
        return S_OK;
    }
    HRESULT STDMETHODCALLTYPE GetNamedPropertyMapping(LPCWSTR, UINT*, int*) override {
        return E_INVALIDARG;
    }
    HRESULT STDMETHODCALLTYPE GetPropertyCount(UINT* c) override { *c = 3; return S_OK; }
    HRESULT STDMETHODCALLTYPE GetProperty(UINT i, void** v) override {
        using winrt::Windows::Foundation::PropertyValue;
        winrt::Windows::Foundation::IInspectable x;
        if (i == 0) x = PropertyValue::CreateSingle(sigma);
        else if (i == 1) x = PropertyValue::CreateUInt32(1);     // quality: balanced
        else if (i == 2) x = PropertyValue::CreateUInt32(1);     // border: hard
        else return E_INVALIDARG;
        *v = winrt::detach_abi(x.as<winrt::Windows::Foundation::IPropertyValue>());
        return S_OK;
    }
    HRESULT STDMETHODCALLTYPE GetSource(UINT i, void** s) override {
        if (i) return E_INVALIDARG;
        auto c = src;
        *s = winrt::detach_abi(c);
        return S_OK;
    }
    HRESULT STDMETHODCALLTYPE GetSourceCount(UINT* c) override { *c = 1; return S_OK; }
};

LRESULT CALLBACK GlassProc(HWND h, UINT m, WPARAM w, LPARAM l) {
    if (m == WM_NCHITTEST) return HTTRANSPARENT;
    return DefWindowProcW(h, m, w, l);
}

const wchar_t kClass[] = L"SeamlessWobblyGlass";

}  // namespace liveglass

struct LiveGlass {
    bool failed = false;        // could not be built here: the flat glass stays
    bool active = false;        // this drag uses it
    bool shown = false;
    bool com = false, registered = false;
    int step = 0;               // how far the last setup got, for the drag's note
    HRESULT lastHr = S_OK;
    HMODULE coreMessaging = nullptr;
    winrt::Windows::System::DispatcherQueueController queue{nullptr};
    liveglass::WUC::Compositor comp{nullptr};
    liveglass::WUC::Desktop::DesktopWindowTarget target{nullptr};
    liveglass::WUC::ContainerVisual root{nullptr};
    liveglass::WUC::SpriteVisual sprite{nullptr};
    liveglass::WUC::CompositionPathGeometry path{nullptr};
    Com<ID2D1Factory> d2d;
    HWND hwnd = nullptr;
    int vx = 0, vy = 0, vw = 0, vh = 0;
    float cw = 1, ch = 1;       // canvas size, texels
    std::vector<Vec2> outline;  // the window's rounded outline, in canvas texels

    ~LiveGlass() { Destroy(); }

    bool Ensure();
    bool Start(const Canvas& c, float radius, int cells, int sub);
    void Update(const std::vector<Vec2>& smooth, int rn, HWND above);
    void Hide();
    void Destroy();
    void DropWindow();
};

void LiveGlass::DropWindow() {
    sprite = nullptr; path = nullptr; root = nullptr; target = nullptr;
    if (hwnd) { DestroyWindow(hwnd); hwnd = nullptr; }
    shown = false;
}

bool LiveGlass::Ensure() {
    if (failed) return false;
    const int x = GetSystemMetrics(SM_XVIRTUALSCREEN), y = GetSystemMetrics(SM_YVIRTUALSCREEN);
    const int w = GetSystemMetrics(SM_CXVIRTUALSCREEN), h = GetSystemMetrics(SM_CYVIRTUALSCREEN);
    if (hwnd && x == vx && y == vy && w == vw && h == vh) return true;
    DropWindow();
    if (w < 1 || h < 1) return false;
    try {
        step = 1;
        if (!com) {
            const HRESULT hr = CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED);
            if (hr == RPC_E_CHANGED_MODE) {
                // The thread already has COM of the other kind: use it as it is.
            } else if (FAILED(hr)) {
                Wh_Log(L"glass: no apartment hr=0x%08X", hr);
                lastHr = hr;
                failed = true;
                return false;
            } else {
                com = true;
            }
        }
        step = 2;
        if (!queue) {
            if (!coreMessaging)
                coreMessaging = LoadLibraryExW(L"CoreMessaging.dll", nullptr,
                                               LOAD_LIBRARY_SEARCH_SYSTEM32);
            if (!coreMessaging) winrt::throw_last_error();
            auto create = reinterpret_cast<glowtool::CreateDispatcherQueueController_t>(
                GetProcAddress(coreMessaging, "CreateDispatcherQueueController"));
            if (!create) winrt::throw_last_error();
            glowtool::DispatcherQueueOptionsAbi o{sizeof(o),
                                                  glowtool::kDispatcherQueueThreadCurrent,
                                                  com ? glowtool::kDispatcherQueueComSta : 0};
            winrt::check_hresult(create(o, winrt::put_abi(queue)));
        }
        step = 3;
        if (!comp) comp = liveglass::WUC::Compositor();
        step = 4;
        if (!d2d.p) winrt::check_hresult(D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &d2d));
        step = 5;
        if (!registered) {
            WNDCLASSEXW wc{};
            wc.cbSize = sizeof(wc);
            wc.lpfnWndProc = liveglass::GlassProc;
            wc.hInstance = MOD_HINSTANCE;
            wc.lpszClassName = liveglass::kClass;
            if (!RegisterClassExW(&wc) && GetLastError() != ERROR_CLASS_ALREADY_EXISTS)
                winrt::throw_last_error();
            registered = true;
        }
        vx = x; vy = y; vw = w; vh = h;
        step = 6;
        hwnd = CreateWindowExW(WS_EX_NOREDIRECTIONBITMAP | WS_EX_LAYERED | WS_EX_TRANSPARENT |
                                   WS_EX_TOPMOST | WS_EX_TOOLWINDOW | WS_EX_NOACTIVATE,
                               liveglass::kClass, L"", WS_POPUP, vx, vy, vw, vh, nullptr, nullptr,
                               MOD_HINSTANCE, nullptr);
        if (!hwnd) winrt::throw_last_error();
        SetLayeredWindowAttributes(hwnd, 0, 255, LWA_ALPHA);
        BOOL on = TRUE;
        DwmSetWindowAttribute(hwnd, 17 /* DWMWA_USE_HOSTBACKDROPBRUSH */, &on, sizeof(on));
        DwmSetWindowAttribute(hwnd, DWMWA_TRANSITIONS_FORCEDISABLED, &on, sizeof(on));

        step = 7;
        winrt::com_ptr<glowtool::DesktopInterop> interop;
        winrt::check_hresult(winrt::get_unknown(comp)->QueryInterface(glowtool::kDesktopInteropIid,
                                                                      interop.put_void()));
        step = 8;
        winrt::check_hresult(interop->CreateDesktopWindowTarget(hwnd, TRUE, winrt::put_abi(target)));
        step = 9;
        root = comp.CreateContainerVisual();
        root.RelativeSizeAdjustment({1, 1});
        target.Root(root);

        sprite = comp.CreateSpriteVisual();
        sprite.RelativeSizeAdjustment({1, 1});
        try {
            auto fx = winrt::make<liveglass::Blur>(
                18.0f, liveglass::WUC::CompositionEffectSourceParameter(L"B"));
            auto brush = comp.CreateEffectFactory(fx).CreateBrush();
            brush.SetSourceParameter(L"B", comp.CreateHostBackdropBrush());
            sprite.Brush(brush);
        } catch (...) {
            // The host backdrop alone is still Windows' own blur, only lighter.
            Wh_Log(L"glass: blur effect failed hr=0x%08X, plain backdrop",
                   (unsigned)winrt::to_hresult());
            sprite.Brush(comp.CreateHostBackdropBrush());
        }
        path = comp.CreatePathGeometry();
        sprite.Clip(comp.CreateGeometricClip(path));
        sprite.IsVisible(false);
        root.Children().InsertAtTop(sprite);
        step = 10;
        return true;
    } catch (...) {
        lastHr = winrt::to_hresult();
        Wh_Log(L"glass: setup failed at %d hr=0x%08X", step, (unsigned)lastHr);
        failed = true;
        DropWindow();
        return false;
    }
}

// The window's outline in canvas texels: its rounded rect, a hair inside, so
// the blur never shows past the copy's own edge.
bool LiveGlass::Start(const Canvas& c, float radius, int cells, int sub) {
    active = false;
    if (!Ensure()) return false;
    cw = (float)c.w; ch = (float)c.h;
    const float in = 1.0f;
    const float x0 = c.P + in, y0 = c.P + in, x1 = c.w - c.P - in, y1 = c.h - c.P - in;
    if (x1 - x0 < 4 || y1 - y0 < 4) return false;
    const float r = std::clamp(radius - in, 0.0f, std::min(x1 - x0, y1 - y0) * 0.5f);
    // Points about every half drawn cell, so the outline bends with the mesh.
    const float step = std::max(2.0f, std::min(cw, ch) / (float)std::max(1, cells * sub) * 0.5f);
    outline.clear();
    auto edge = [&](float ax, float ay, float bx, float by) {
        const float len = hypotf(bx - ax, by - ay);
        const int n = std::max(1, (int)ceilf(len / step));
        for (int i = 0; i < n; ++i) {
            const float t = (float)i / n;
            outline.push_back(Vec2{ax + (bx - ax) * t, ay + (by - ay) * t});
        }
    };
    auto arc = [&](float cx, float cy, float a0) {
        if (r <= 0.5f) { outline.push_back(Vec2{cx + r * cosf(a0), cy + r * sinf(a0)}); return; }
        const int n = 8;
        for (int i = 0; i < n; ++i) {
            const float a = a0 + 1.5707963f * i / n;
            outline.push_back(Vec2{cx + r * cosf(a), cy + r * sinf(a)});
        }
    };
    const float pi = 3.14159265f;
    edge(x0 + r, y0, x1 - r, y0);  arc(x1 - r, y0 + r, -pi / 2);
    edge(x1, y0 + r, x1, y1 - r);  arc(x1 - r, y1 - r, 0);
    edge(x1 - r, y1, x0 + r, y1);  arc(x0 + r, y1 - r, pi / 2);
    edge(x0, y1 - r, x0, y0 + r);  arc(x0 + r, y0 + r, pi);
    active = true;
    return true;
}

// Bends the outline with the drawn grid (the same two triangles per cell the
// overlay draws) and sets it as the blur's clip, before the overlay presents.
void LiveGlass::Update(const std::vector<Vec2>& smooth, int rn, HWND above) {
    if (!active || !hwnd || rn < 2 || smooth.size() < (size_t)rn * rn) return;
    const int rc = rn - 1;
    auto map = [&](const Vec2& t) {
        const float u = std::clamp(t.x / cw, 0.0f, 1.0f) * rc;
        const float v = std::clamp(t.y / ch, 0.0f, 1.0f) * rc;
        const int i = std::min((int)u, rc - 1), j = std::min((int)v, rc - 1);
        const float fx = u - i, fy = v - j;
        const Vec2 a = smooth[(size_t)j * rn + i], b = smooth[(size_t)j * rn + i + 1];
        const Vec2 c = smooth[(size_t)(j + 1) * rn + i], d = smooth[(size_t)(j + 1) * rn + i + 1];
        Vec2 p;
        if (fx + fy <= 1.0f) {
            p = Vec2{a.x + fx * (b.x - a.x) + fy * (c.x - a.x), a.y + fx * (b.y - a.y) + fy * (c.y - a.y)};
        } else {
            const float gx = 1.0f - fx, gy = 1.0f - fy;
            p = Vec2{d.x + gx * (c.x - d.x) + gy * (b.x - d.x), d.y + gx * (c.y - d.y) + gy * (b.y - d.y)};
        }
        return D2D1_POINT_2F{p.x - vx, p.y - vy};
    };
    try {
        Com<ID2D1PathGeometry> g;
        if (FAILED(d2d->CreatePathGeometry(&g))) return;
        Com<ID2D1GeometrySink> s;
        if (FAILED(g->Open(&s))) return;
        s->BeginFigure(map(outline[0]), D2D1_FIGURE_BEGIN_FILLED);
        for (size_t k = 1; k < outline.size(); ++k) s->AddLine(map(outline[k]));
        s->EndFigure(D2D1_FIGURE_END_CLOSED);
        if (FAILED(s->Close())) return;
        path.Path(liveglass::WUC::CompositionPath(winrt::make<liveglass::PathSource>(g.p)));
        if (!shown) {
            sprite.IsVisible(true);
            SetWindowPos(hwnd, above ? above : HWND_TOPMOST, 0, 0, 0, 0,
                         SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE | SWP_SHOWWINDOW);
            shown = true;
        }
    } catch (...) {
        Wh_Log(L"glass: update failed hr=0x%08X", (unsigned)winrt::to_hresult());
        active = false;
        return;
    }
    PumpMessages();     // composition commits from the thread's queue
}

void LiveGlass::Hide() {
    active = false;
    if (!shown) return;
    shown = false;
    try { if (sprite) sprite.IsVisible(false); } catch (...) {}
    if (hwnd) ShowWindow(hwnd, SW_HIDE);
    PumpMessages();
}

void LiveGlass::Destroy() {
    active = false;
    try { DropWindow(); } catch (...) {}
    comp = nullptr;
    d2d.reset();
    outline.clear(); outline.shrink_to_fit();
    if (registered) { UnregisterClassW(liveglass::kClass, MOD_HINSTANCE); registered = false; }
    bool stopped = true;
    if (queue) {
        stopped = glowtool::ShutdownQueue(queue);
        if (stopped) queue = nullptr;
        else winrt::detach_abi(queue);   // still running: leak it rather than crash
    }
    if (com && stopped) { CoUninitialize(); com = false; }
    failed = false;
}

void Overlay::Show() {
    if (hwnd) ShowWindow(hwnd, SW_SHOWNOACTIVATE);
}

void Overlay::Hide() {
    if (glass) glass->Hide();
    if (hwnd) ShowWindow(hwnd, SW_HIDE);
}

void Overlay::Destroy() {
    srv.reset(); tex.reset(); posVb.reset(); uvVb.reset(); ib.reset(); rtv.reset();
    rows.clear(); rows.shrink_to_fit(); smooth.clear(); smooth.shrink_to_fit();
    visual.reset(); target.reset(); dcomp.reset(); swap.reset();
    if (hwnd) { DestroyWindow(hwnd); hwnd = nullptr; }
    presentWarmed = false;
    gridCells = 0;
    indexCount = 0;
    ResetHistory();
}

static RECT UnionRect3(const RECT& a, const RECT& b, const RECT& c) {
    RECT u = a;
    for (const RECT* r : { &b, &c }) {
        if (r->right <= r->left || r->bottom <= r->top) continue;
        if (u.right <= u.left || u.bottom <= u.top) { u = *r; continue; }
        u.left = std::min(u.left, r->left);     u.top = std::min(u.top, r->top);
        u.right = std::max(u.right, r->right);  u.bottom = std::max(u.bottom, r->bottom);
    }
    return u;
}

static DrawResult CheckPresent(HRESULT hr, int& fullFrames) {
    if (hr == DXGI_ERROR_DEVICE_REMOVED || hr == DXGI_ERROR_DEVICE_RESET) {
        Wh_Log(L"overlay: device lost on present hr=0x%08X", hr);
        return DrawResult::DeviceLost;
    }
    if (hr != S_OK) {
        // Occluded or failed: the buffers can't be trusted to hold what we
        // think, so the next two frames are drawn whole.
        fullFrames = 2;
        if (FAILED(hr)) {
            Wh_Log(L"overlay: present failed hr=0x%08X", hr);
            return DrawResult::Failed;
        }
    }
    return DrawResult::Ok;
}

// A fully transparent frame, so a later Show never flashes the last drag.
DrawResult Overlay::PresentClear() {
    if (!d || !d->ok || !swap.p || !rtv.p) return DrawResult::Failed;
    const float clear[4] = { 0, 0, 0, 0 };
    ID3D11RenderTargetView* rts[] = { rtv.p };
    d->ctx->OMSetRenderTargets(1, rts, nullptr);
    d->ctx->ClearRenderTargetView(rtv, clear);
    ResetHistory();
    return CheckPresent(swap->Present(0, 0), fullFrames);
}

DrawResult Overlay::Draw(const Mesh& m) {
    if (!d || !d->ok || !swap.p || !rtv.p || !posVb.p || m.nx - 1 != gridCells)
        return DrawResult::Failed;
    auto* ctx = d->ctx.p;

    if (smooth.empty()) return DrawResult::Failed;
    SmoothGrid(m.pos, m.nx, sub, rows, smooth);
    D3D11_MAPPED_SUBRESOURCE map{};
    if (FAILED(ctx->Map(posVb, 0, D3D11_MAP_WRITE_DISCARD, 0, &map))) return DrawResult::Failed;
    memcpy(map.pData, smooth.data(), sizeof(Vec2) * smooth.size());
    ctx->Unmap(posVb, 0);

    struct CB { float ox, oy, sw, sh; } cbv{ (float)vx, (float)vy, (float)vw, (float)vh };
    if (SUCCEEDED(ctx->Map(d->cb, 0, D3D11_MAP_WRITE_DISCARD, 0, &map))) {
        memcpy(map.pData, &cbv, sizeof(cbv));
        ctx->Unmap(d->cb, 0);
    }

    // What this frame covers, in surface pixels, with a margin for filtering.
    // The curves can bulge a little past the spring nodes, so measure them.
    float minX = smooth[0].x, maxX = minX, minY = smooth[0].y, maxY = minY;
    for (const Vec2& p : smooth) {
        minX = fminf(minX, p.x); maxX = fmaxf(maxX, p.x);
        minY = fminf(minY, p.y); maxY = fmaxf(maxY, p.y);
    }
    RECT now{
        std::max(0L, (LONG)floorf(minX) - vx - 2),
        std::max(0L, (LONG)floorf(minY) - vy - 2),
        std::min((LONG)vw, (LONG)ceilf(maxX) - vx + 2),
        std::min((LONG)vh, (LONG)ceilf(maxY) - vy + 2) };
    if (now.right < now.left) now.right = now.left;
    if (now.bottom < now.top) now.bottom = now.top;

    // Two buffers in flight: the one being drawn still holds the frame from
    // two presents ago, so its area is cleared along with last frame's.
    const bool partial = fullFrames <= 0 && d->ctx1.p;
    const RECT dirty = UnionRect3(now, hist[0], hist[1]);
    const float clear[4] = { 0, 0, 0, 0 };
    ID3D11RenderTargetView* rts[] = { rtv.p };
    ctx->OMSetRenderTargets(1, rts, nullptr);
    if (partial) {
        if (dirty.right > dirty.left && dirty.bottom > dirty.top)
            d->ctx1->ClearView(rtv, clear, &dirty, 1);
    } else {
        ctx->ClearRenderTargetView(rtv, clear);
    }

    D3D11_VIEWPORT vp{ 0, 0, (float)vw, (float)vh, 0, 1 };
    ctx->RSSetViewports(1, &vp);
    UINT strides[2] = { sizeof(Vec2), sizeof(Vec2) }, offsets[2] = { 0, 0 };
    ID3D11Buffer* vbs[2] = { posVb.p, uvVb.p };
    ctx->IASetVertexBuffers(0, 2, vbs, strides, offsets);
    ctx->IASetIndexBuffer(ib, DXGI_FORMAT_R16_UINT, 0);
    ctx->IASetInputLayout(d->layout);
    ctx->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    ctx->VSSetShader(d->vs, nullptr, 0);
    ID3D11Buffer* cbs[] = { d->cb.p };
    ctx->VSSetConstantBuffers(0, 1, cbs);
    ctx->PSSetShader(d->ps, nullptr, 0);
    ID3D11Buffer* pcbs[] = { d->cbGlow.p };
    ctx->PSSetConstantBuffers(1, 1, pcbs);
    ID3D11ShaderResourceView* srvs[] = { srv.p };
    ctx->PSSetShaderResources(0, 1, srvs);
    ID3D11SamplerState* smps[] = { d->sampler.p };
    ctx->PSSetSamplers(0, 1, smps);
    const float bf[4] = { 0, 0, 0, 0 };
    ctx->OMSetBlendState(d->blend, bf, 0xFFFFFFFF);
    ctx->DrawIndexed(indexCount, 0, 0);
    if (glass) glass->Update(smooth, gridCells * sub + 1, hwnd);

    HRESULT hr;
    if (partial && dirty.right > dirty.left && dirty.bottom > dirty.top) {
        RECT dr = dirty;
        DXGI_PRESENT_PARAMETERS pp{};
        pp.DirtyRectsCount = 1;
        pp.pDirtyRects     = &dr;
        hr = swap->Present1(1, 0, &pp);
    } else {
        hr = swap->Present(1, 0);
        if (fullFrames > 0) --fullFrames;
    }
    hist[1] = hist[0];
    hist[0] = now;
    return CheckPresent(hr, fullFrames);
}

// -----------------------------------------------------------------------------
// Hiding the real window
// -----------------------------------------------------------------------------
// Cloaking takes the window out of composition without moving or hiding it, so
// its taskbar button stays and Windows keeps moving it as usual underneath.

struct HideState {
    bool  cloaked   = false;
    bool  hadCorner = false;
    DWORD corner    = 0;
    bool  dropped   = false;    // its own backdrop was switched off for the drag
    DWORD backdrop  = 0;
};

static void SaveCorners(HWND hwnd, HideState& st) {
    DWORD corner = 0;
    if (SUCCEEDED(DwmGetWindowAttribute(hwnd, DWMWA_WINDOW_CORNER_PREFERENCE,
                                        &corner, sizeof(corner)))) {
        st.hadCorner = true;
        st.corner    = corner;
    }
}

static void RestoreCorners(HWND hwnd, const HideState& st) {
    if (!st.hadCorner) return;
    DWORD corner = st.corner;
    DwmSetWindowAttribute(hwnd, DWMWA_WINDOW_CORNER_PREFERENCE, &corner, sizeof(corner));
}

// A cloaked window's own system backdrop can land in the live blur's backdrop
// as black. With the live blur on, switch that backdrop off for the drag and
// put it back after.
static bool HideWindowInPlace(HWND hwnd, HideState& st, bool dropBackdrop = false) {
    SaveCorners(hwnd, st);
    if (dropBackdrop) {
        DWORD type = 0;
        if (SUCCEEDED(DwmGetWindowAttribute(hwnd, 38 /*DWMWA_SYSTEMBACKDROP_TYPE*/, &type, sizeof(type))) &&
            type > 1) {
            DWORD none = 1;
            if (SUCCEEDED(DwmSetWindowAttribute(hwnd, 38 /*DWMWA_SYSTEMBACKDROP_TYPE*/, &none, sizeof(none)))) {
                st.dropped  = true;
                st.backdrop = type;
            }
        }
    }
    BOOL on = TRUE;
    if (FAILED(DwmSetWindowAttribute(hwnd, DWMWA_CLOAK, &on, sizeof(on)))) {
        if (st.dropped) {
            DwmSetWindowAttribute(hwnd, 38 /*DWMWA_SYSTEMBACKDROP_TYPE*/, &st.backdrop, sizeof(st.backdrop));
            st.dropped = false;
        }
        return false;
    }
    st.cloaked = true;
    return true;
}

// An activation change that lands while the window is hidden can leave its
// glass in the wrong look (T3 went see-through, 2026-11-14 11:55). Telling the
// window its real active state again makes DWM redraw the backdrop. Same fix as
// Seamless Window Manager's RefreshBackdropAfterUncloak.
static void RefreshBackdropAfterShow(HWND hwnd) {
    const BOOL active = GetForegroundWindow() == hwnd;
    DWORD_PTR result = 0;
    SendMessageTimeoutW(hwnd, WM_NCACTIVATE, active, 0, SMTO_ABORTIFHUNG | SMTO_NORMAL, 100,
                        &result);
    SetWindowPos(hwnd, nullptr, 0, 0, 0, 0,
                 SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE | SWP_FRAMECHANGED |
                     SWP_ASYNCWINDOWPOS);
}

static void ShowWindowInPlace(HWND hwnd, HideState& st) {
    if (!st.cloaked) return;
    st.cloaked = false;
    BOOL off = FALSE;
    if (st.dropped) {
        DwmSetWindowAttribute(hwnd, 38 /*DWMWA_SYSTEMBACKDROP_TYPE*/, &st.backdrop, sizeof(st.backdrop));
        st.dropped = false;
    }
    DwmSetWindowAttribute(hwnd, DWMWA_CLOAK, &off, sizeof(off));
    RestoreCorners(hwnd, st);
    if (IsWindow(hwnd)) RefreshBackdropAfterShow(hwnd);
}

static bool CanHideReliably(HWND hwnd) {
    BOOL off = FALSE;
    return SUCCEEDED(DwmSetWindowAttribute(hwnd, DWMWA_CLOAK, &off, sizeof(off)));
}

// -----------------------------------------------------------------------------
// The drag
// -----------------------------------------------------------------------------

struct DragRequest { HWND hwnd = nullptr; bool external = false; };

static std::atomic<bool> g_dragging{false};
static std::atomic<bool> g_shuttingDown{false};
static HANDLE      g_worker     = nullptr;
static HANDLE      g_dragSignal = nullptr;
static DragRequest g_pending;

// A press that came while the last drag was still landing. Picked up the
// moment the landing ends, so a quick second grab still wobbles.
static SRWLOCK     g_queueLock = SRWLOCK_INIT;
static DragRequest g_queued;
static double      g_queuedAt = 0.0;

// Seamless Window Manager swallows the press and the release of its held-key
// moves, so the button is invisible here. It posts this message instead:
// wParam 1 when its move starts, 0 when it ends.
static UINT g_extMsg = 0;
static std::atomic<HWND> g_extHwnd{nullptr};
static std::atomic<bool> g_extDown{false};
static std::atomic<unsigned> g_extStarts{0};

// True while a released drag is wobbling out; only then is a new grab queued.
static std::atomic<bool> g_landing{false};

// Set when Windows' move loop for this window has ended.
static std::atomic<HWND> g_exitHwnd{nullptr};

static bool BypassHeld() {
    const int vk = g_bypassVk.load();
    return vk && (GetAsyncKeyState(vk) & 0x8000);
}

static bool Eligible(HWND hwnd) {
    if (!hwnd || !IsWindowVisible(hwnd) || IsIconic(hwnd)) return false;
    if (GetWindowLongPtrW(hwnd, GWL_STYLE) & WS_CHILD) return false;
    if (GetAncestor(hwnd, GA_ROOT) != hwnd) return false;
    wchar_t cls[64];
    if (GetClassNameW(hwnd, cls, 64)) {
        static const wchar_t* const kSkip[] = {
            L"Shell_TrayWnd", L"Shell_SecondaryTrayWnd", L"Progman", L"WorkerW",
            kOverlayClass, L"SeamlessBordersPart",
        };
        for (const wchar_t* s : kSkip)
            if (!wcscmp(cls, s)) return false;
    }
    RECT r{};
    if (FAILED(DwmGetWindowAttribute(hwnd, DWMWA_EXTENDED_FRAME_BOUNDS, &r, sizeof(r))))
        GetWindowRect(hwnd, &r);
    return (r.right - r.left) >= 100 && (r.bottom - r.top) >= 60;
}

static bool HeldFor(const DragRequest& rq) {
    if (rq.external) return g_extDown.load() && g_extHwnd.load() == rq.hwnd;
    return PrimaryButtonDown() && g_exitHwnd.load() != rq.hwnd;
}

// Any new grab since `starts` was read: a press of the button, or a window
// manager move that began.
static bool NewGrab(unsigned starts) {
    return PrimaryButtonDown() || g_extStarts.load() != starts;
}

// -----------------------------------------------------------------------------
// The glow inside the wobble
// -----------------------------------------------------------------------------
// The glow process hides its glow while the window is cloaked, so the wobble
// paints the same sprites, from the same clock, onto the copy's see-through
// backdrop. The window property tells the glow process to bring its own glow
// back at once, without the fade, when the window lands.

// Worker thread only. The property outlives the drag by a moment, so the glow
// process still sees it when the window is uncloaked.
static HWND   g_glowPropHwnd  = nullptr;
static double g_glowPropUntil = 0.0;

static void ClearGlowProp() {
    if (!g_glowPropHwnd) return;
    if (IsWindow(g_glowPropHwnd)) RemovePropW(g_glowPropHwnd, kGlowDragProp);
    g_glowPropHwnd = nullptr;
}

// How much of the glow behind the window shows through it: 0 when it isn't
// see-through. An acrylic system backdrop, or the older accent blur that
// tools like Translucent Windows set.
static float GlowSeeThrough(HWND hwnd) {
    int backdrop = 0;
    if (SUCCEEDED(DwmGetWindowAttribute(hwnd, 38 /*DWMWA_SYSTEMBACKDROP_TYPE*/,
                                        &backdrop, sizeof(backdrop))) && backdrop == 3)
        return 0.28f;    // the acrylic's tint lets through about 28% (measured live)
    struct Accent { int state, flags; DWORD color; int anim; };
    struct Data { DWORD attr; PVOID data; ULONG size; };
    using Get_t = BOOL(WINAPI*)(HWND, Data*);
    static Get_t get = [] {
        HMODULE u = GetModuleHandleW(L"user32.dll");
        return u ? (Get_t)GetProcAddress(u, "GetWindowCompositionAttribute") : nullptr;
    }();
    if (!get) return 0.0f;
    Accent a{};
    Data d{ 19 /*WCA_ACCENT_POLICY*/, &a, sizeof(a) };
    if (!get(hwnd, &d) || a.state < 2 || a.state > 4) return 0.0f;
    // The tint colour is AABBGGRR: its alpha is what covers the backdrop.
    return std::clamp(1.0f - (float)(a.color >> 24) / 255.0f, 0.1f, 1.0f);
}

// The flat colour the capture shows where the backdrop is: the commonest
// colour along the top of the window (title bar and tabs), which must cover
// a fair share of it.
static bool FindGlowKey(const Canvas& c, float scale, float key[3]) {
    const int vw = c.w - 2 * c.P, vh = c.h - 2 * c.P;
    const int margin = 6;
    const int band = std::min(vh - 2 * margin, (int)(40.0f * scale));
    if (band < 4 || vw < 2 * margin + 16) return false;
    std::vector<uint16_t> counts(32768, 0);
    int total = 0, best = -1, bestCount = 0;
    for (int y = c.P + margin; y < c.P + margin + band; y += 4) {
        const uint32_t* row = &c.px[(size_t)y * c.w];
        for (int x = c.P + margin; x < c.P + vw - margin; x += 4) {
            const uint32_t p = row[x];
            if ((p >> 24) != 255) continue;
            const int b = (int)(((p >> 19) & 31) << 10 | ((p >> 11) & 31) << 5 | ((p >> 3) & 31));
            ++total;
            if (counts[b] < 65535 && ++counts[b] > bestCount) { bestCount = counts[b]; best = b; }
        }
    }
    if (best < 0 || bestCount * 10 < total * 3) return false;
    double sr = 0, sg = 0, sb = 0;
    int n = 0;
    for (int y = c.P + margin; y < c.P + margin + band; y += 4) {
        const uint32_t* row = &c.px[(size_t)y * c.w];
        for (int x = c.P + margin; x < c.P + vw - margin; x += 4) {
            const uint32_t p = row[x];
            if ((p >> 24) != 255) continue;
            const int b = (int)(((p >> 19) & 31) << 10 | ((p >> 11) & 31) << 5 | ((p >> 3) & 31));
            if (b != best) continue;
            sr += (p >> 16) & 0xFF; sg += (p >> 8) & 0xFF; sb += p & 0xFF;
            ++n;
        }
    }
    if (!n) return false;
    key[0] = (float)(sr / n / 255.0); key[1] = (float)(sg / n / 255.0); key[2] = (float)(sb / n / 255.0);
    return true;
}

// A read-only view of the glow process's clock and windows.
struct GlowMap {
    HANDLE map = nullptr;
    const GlowShared* m = nullptr;
    GlowMap() = default;
    GlowMap(const GlowMap&) = delete;
    GlowMap& operator=(const GlowMap&) = delete;
    ~GlowMap() { Close(); }
    bool Open() {
        map = OpenFileMappingW(FILE_MAP_READ, FALSE, kGlowMapName);
        if (!map) return false;
        m = (const GlowShared*)MapViewOfFile(map, FILE_MAP_READ, 0, 0, sizeof(GlowShared));
        if (!m) { Close(); return false; }
        return true;
    }
    void Close() {
        if (m) { UnmapViewOfFile(m); m = nullptr; }
        if (map) { CloseHandle(map); map = nullptr; }
    }
};

struct GlowClock {
    uint32_t running = 0, animated = 0;
    int64_t  baseQpc = 0, manualQpc = 0;
    double   manualTime = 0, rate = 1;
    GlowShared::Entry e{};
};

// Seqlock read: retried while the writer is mid-update. False when the glow
// process has no glow on this window (or is gone).
static bool ReadGlowClock(const GlowShared* m, HWND hwnd, GlowClock& out) {
    const uint32_t want = (uint32_t)(UINT_PTR)hwnd;
    for (int attempt = 0; attempt < 64; ++attempt) {
        const LONG s1 = m->seq;
        if (s1 & 1) { YieldProcessor(); continue; }
        MemoryBarrier();
        GlowClock c;
        const uint32_t version = m->version;
        c.running    = m->running;
        c.animated   = m->animated;
        c.baseQpc    = m->baseQpc;
        c.manualTime = m->manualTime;
        c.manualQpc  = m->manualQpc;
        c.rate       = m->rate;
        const uint32_t count = std::min<uint32_t>(m->count, (uint32_t)kGlowMaxEntries);
        bool found = false;
        for (uint32_t i = 0; i < count; ++i) {
            if (m->e[i].hwnd == want) { c.e = m->e[i]; found = true; break; }
        }
        MemoryBarrier();
        if (m->seq != s1) continue;
        if (version != kGlowMapVersion || !found) return false;
        out = c;
        return true;
    }
    return false;
}

// This window's glow time, as the glow process's compositor has it now.
static float GlowTime(const GlowClock& c) {
    const float loop = glowtool::kLoopSeconds;
    if (!c.running || !c.e.live) return c.e.frozen;
    LARGE_INTEGER q, f;
    QueryPerformanceCounter(&q);
    QueryPerformanceFrequency(&f);
    double t;
    if (c.animated) {
        t = (double)(q.QuadPart - c.baseQpc) / (double)f.QuadPart;
    } else {
        const double since = std::clamp((double)(q.QuadPart - c.manualQpc) / (double)f.QuadPart,
                                        0.0, 0.25);
        t = c.manualTime + since * c.rate;
    }
    t = fmod(t, (double)loop);
    if (t < 0) t += loop;
    return (float)fmod(t - c.e.offset + 2.0 * loop, (double)loop);
}

// The same sprites the glow process builds (glowtool::Backdrop::Build*), for
// a window of W x H physical pixels at monitor scale S, at time T.
static int GlowSprites(const glowtool::Settings& s, float W, float H, float S, float T,
                       GlowCB& cb) {
    using namespace glowtool;
    const float base  = (float)s.diameter;
    const float alpha = (float)(s.opacity * 255 / 100) / 255.0f;
    int n = 0;
    auto put = [&](float ox, float oy, float sx, float sy, Color col,
                   float angleDeg = 0.0f, float px = 0.0f, float py = 0.0f) {
        if (n >= kGlowMaxSprites || sx <= 0.0f || sy <= 0.0f) return;
        const float a = angleDeg * kPi / 180.0f;
        float* p = cb.spr[n * 3];
        p[0] = ox; p[1] = oy; p[2] = sx; p[3] = sy;
        p = cb.spr[n * 3 + 1];
        p[0] = col.R / 255.0f; p[1] = col.G / 255.0f; p[2] = col.B / 255.0f; p[3] = alpha;
        p = cb.spr[n * 3 + 2];
        p[0] = cosf(a); p[1] = sinf(a); p[2] = px; p[3] = py;
        ++n;
    };

    switch (s.effect) {
        case Effect::Gradient: {
            // glowtool::Backdrop::BuildGradient: a square as wide as the
            // diagonal, turning about the window's center.
            const float L = sqrtf(W * W + H * H);
            const float angle = kGradientAngle +
                kGradientSweep * sinf(T * GradientFrequency(s.seconds));
            put((W - L) * 0.5f, (H - L) * 0.5f, L, L, s.colors[0], angle, L * 0.5f, L * 0.5f);
            put((W - L) * 0.5f, (H - L) * 0.5f, L, L, s.colors[1], angle, L * 0.5f, L * 0.5f);
            // The glow process rounds the stops' alpha to whole steps.
            const float a = std::clamp(std::floor(alpha * 255.0f * kGradientAlpha + 0.5f),
                                       0.0f, 255.0f) / 255.0f;
            cb.spr[1][3] = a;
            cb.spr[4][3] = a;
            break;
        }
        case Effect::Glows:
            for (int i = 0; i < 3; ++i) {
                const float sx = base * S, sy = std::max(base * S, H * 1.8f);
                const float rate = QuantizeVelocity(2.0f / ((float)s.seconds + 1.7f * i), 2.0f);
                const float ph = fmodf((float)i / 3.0f + rate * T, 2.0f);
                put(W * (1.0f - fabsf(ph - 1.0f)) - sx * 0.5f, (H - sy) * 0.5f, sx, sy,
                    s.colors[i]);
            }
            break;
        case Effect::Beams:
            for (int k = 0; k < s.beamCount; ++k) {
                const float t = ((float)k + 0.5f) / (float)s.beamCount;
                float ax = 0, ay = 0, heading = 0, fan = 0;
                switch (s.beamOrigin) {
                    case Origin::Top:    ax = t; ay = 0; heading = 0;   fan = (t - 0.5f) * 30.0f; break;
                    case Origin::Bottom: ax = t; ay = 1; heading = 180; fan = (0.5f - t) * 30.0f; break;
                    case Origin::Left:   ax = 0; ay = t; heading = -90; fan = (0.5f - t) * 30.0f; break;
                    case Origin::Right:  ax = 1; ay = t; heading = 90;  fan = (t - 0.5f) * 30.0f; break;
                }
                const float sx = base * S * 0.5f, sy = sqrtf(W * W + H * H) * 1.25f;
                const float angle = heading + fan + (float)s.beamSweep *
                    sinf(T * LoopFrequency((float)s.seconds * (1.0f + 0.23f * k)) + 2.4f * k);
                put(ax * W - sx * 0.5f, ay * H, sx, sy, s.colors[k % 3], angle, sx * 0.5f, 0.0f);
            }
            break;
        case Effect::Orbs: {
            const bool wrap = s.orbEdges == Edges::Wrap;
            const float period = wrap ? 1.0f : 2.0f;
            for (size_t j = 0; j < s.orbs.size(); ++j) {
                const auto& orb = s.orbs[j];
                const float speed = period / (float)s.seconds * orb.speed / 100.0f;
                const float rad = (float)orb.angle * kPi / 180.0f;
                const float vx = QuantizeVelocity(cosf(rad) * speed, period);
                const float vy = QuantizeVelocity(-sinf(rad) * speed, period);
                const float fj = (float)j;
                const float sx0 = Frac(0.21f + 0.618034f * fj) * period;
                const float sy0 = Frac(0.67f + 0.381966f * fj) * period;
                const float sz = base * S;
                float ox, oy;
                if (wrap) {
                    ox = (W + sz) * fmodf(fmodf(sx0 + vx * T, 1.0f) + 1.0f, 1.0f) - sz;
                    oy = (H + sz) * fmodf(fmodf(sy0 + vy * T, 1.0f) + 1.0f, 1.0f) - sz;
                } else {
                    ox = (W - sz) * fabsf(fmodf(fabsf(sx0 + vx * T), 2.0f) - 1.0f);
                    oy = (H - sz) * fabsf(fmodf(fabsf(sy0 + vy * T), 2.0f) - 1.0f);
                }
                put(ox, oy, sz, sz, orb.color);
            }
            break;
        }
        case Effect::Waves: {
            const float amp     = s.waveAmplitude / 100.0f;
            const float spatial = kTwoPi / (s.waveLength / 100.0f);
            const float span    = 1.1f * 2.4f / (float)(kWaveBlobs - 1);
            for (int k = 0; k < kWaveCount; ++k) {
                const float dir = (k % 2) ? -1.0f : 1.0f;
                const float w = dir * LoopFrequency((float)s.seconds * (1.0f + 0.25f * k));
                for (int j = 0; j < kWaveBlobs; ++j) {
                    const float px = -0.05f + 1.1f * (float)j / (kWaveBlobs - 1);
                    const float sx = W * span, sy = base * S * 0.6f;
                    put(W * px - sx * 0.5f,
                        H * (0.3f + 0.2f * k + amp * sinf(spatial * px - w * T + 1.9f * k)) - sy * 0.5f,
                        sx, sy, s.colors[k]);
                }
            }
            break;
        }
    }
    cb.hdr[0] = (float)n;
    cb.hdr[3] = s.effect == Effect::Beams ? 1.0f : s.effect == Effect::Gradient ? 2.0f : 0.0f;
    return n;
}

// One drag's glow: decided once after the capture, then refreshed per frame.
// The glow at one backdrop pixel, as the pixel shader paints it (fully
// matching key colour). Same maths as Radial, Beam and the gradient branch in
// wobble.hlsl; px, py are pixel centres relative to the visible frame.
static float RadialAt(float ux, float uy) {
    const float t = hypotf(ux * 2.0f - 1.0f, uy * 2.0f - 1.0f);
    return t < 0.55f ? 1.0f + (1.0f / 3.0f - 1.0f) * (t / 0.55f)
                     : std::max(0.0f, (1.0f / 3.0f) * (1.0f - (t - 0.55f) / 0.45f));
}
static float BeamAt(float ux, float uy) {
    if (ux < 0.0f || uy < 0.0f || ux > 1.0f || uy > 1.0f) return 0.0f;
    const float x = ux > 0.5f ? 1.0f - ux : ux;
    const float across = x < 0.35f ? x : 0.35f + 0.65f * (x - 0.35f) / 0.15f;
    return across * (1.0f - uy);
}
static void GlowAt(const GlowCB& cb, float px, float py, float g[4]) {
    g[0] = g[1] = g[2] = g[3] = 0.0f;
    int n = (int)cb.hdr[0];
    auto local = [&](int k, float& lx, float& ly) {
        const float* a = cb.spr[k * 3];
        const float* r = cb.spr[k * 3 + 2];
        const float qx = px - a[0] - r[2], qy = py - a[1] - r[3];
        lx = r[2] + r[0] * qx + r[1] * qy;
        ly = r[3] - r[1] * qx + r[0] * qy;
    };
    if (cb.hdr[3] > 1.5f) {
        if (n < 2) return;
        float lx, ly;
        local(0, lx, ly);
        const float x = std::clamp(lx / cb.spr[0][2], 0.0f, 1.0f);
        const float* c1 = cb.spr[1];
        const float* c2 = cb.spr[4];
        const float al = c1[3] + (c2[3] - c1[3]) * x;
        for (int k = 0; k < 3; ++k) g[k] = (c1[k] + (c2[k] - c1[k]) * x) * al;
        g[3] = al;
        n = 0;
    }
    const bool beams = cb.hdr[3] > 0.5f;
    for (int k = 0; k < n; ++k) {
        const float* a = cb.spr[k * 3];
        const float* b = cb.spr[k * 3 + 1];
        float lx, ly;
        local(k, lx, ly);
        const float ux = lx / a[2], uy = ly / a[3];
        const float al = b[3] * (beams ? BeamAt(ux, uy) : RadialAt(ux, uy));
        for (int c = 0; c < 3; ++c) g[c] = b[c] * al + g[c] * (1.0f - al);
        g[3] = al + g[3] * (1.0f - al);
    }
    for (int k = 0; k < 4; ++k) g[k] *= cb.hdr[1];
    if (g[3] > 1.0f) for (int k = 0; k < 4; ++k) g[k] /= g[3];
}

// One picture of the window as the screen shows it, glass and all. Taken
// while the real window is still up, in a single read: every screen read waits
// for a display frame (about 10 ms), so small reads add up.
struct GlassShot {
    bool tried = false, ok = false;
    RECT vis{};
    int  w = 0, h = 0;
    std::vector<uint32_t> px;
};

static void ShootGlass(HWND hwnd, GlassShot& out) {
    out.tried = true;
    RECT o1{}, v1{}, o2{}, v2{};
    if (!ReadFramePair(hwnd, o1, v1)) return;
    const int w = v1.right - v1.left, h = v1.bottom - v1.top;
    if (w <= 0 || h <= 0 || (long long)w * h > 3840LL * 2400LL) return;
    HDC screen = GetDC(nullptr);
    if (!screen) return;
    HDC mem = CreateCompatibleDC(screen);
    BITMAPINFO bi{};
    bi.bmiHeader.biSize = sizeof(bi.bmiHeader);
    bi.bmiHeader.biWidth = w;
    bi.bmiHeader.biHeight = -h;
    bi.bmiHeader.biPlanes = 1;
    bi.bmiHeader.biBitCount = 32;
    bi.bmiHeader.biCompression = BI_RGB;
    void* bits = nullptr;
    HBITMAP hbm = mem ? CreateDIBSection(mem, &bi, DIB_RGB_COLORS, &bits, nullptr, 0) : nullptr;
    bool read = false;
    if (hbm && bits) {
        HGDIOBJ old = SelectObject(mem, hbm);
        read = BitBlt(mem, 0, 0, w, h, screen, v1.left, v1.top, SRCCOPY) != FALSE;
        GdiFlush();
        SelectObject(mem, old);
    }
    // The window moving meanwhile leaves no way to tell which spot was read.
    if (read && ReadFramePair(hwnd, o2, v2) && EqualRect(&v1, &v2)) {
        const uint32_t* p = (const uint32_t*)bits;
        out.px.assign(p, p + (size_t)w * h);
        out.vis = v1;
        out.w = w;
        out.h = h;
        out.ok = true;
    }
    if (hbm) DeleteObject(hbm);
    if (mem) DeleteDC(mem);
    ReleaseDC(nullptr, screen);
}

// The capture draws the see-through backdrop as a flat stand-in, a shade off
// the live glass, so the copy would brighten at the grab and dim at the
// release. From the screen picture, on a 7 x 7 grid of small squares where the
// capture shows the stand-in, take the glow back out and hand the shader the
// median: it paints that over the stand-in and adds the glow on top, as the
// real window does.
static void MatchGlass(const GlassShot& shot, const Canvas& c, GlowCB& cb) {
    cb.fill[3] = 0.0f;
    constexpr int T = 16, kGrid = 7;
    const int vw = c.w - 2 * c.P, vh = c.h - 2 * c.P;
    if (!shot.ok || shot.w != vw || shot.h != vh) {
        Wh_Log(L"glow: no glass picture");
        return;
    }
    const int margin = (int)(8.0f * MonitorScale(c.vis));
    if (vw < 2 * margin + kGrid * T || vh < 2 * margin + kGrid * T) return;
    std::vector<int> ch[3];
    for (auto& v : ch) v.reserve(kGrid * kGrid * T * T);
    for (int ty = 0; ty < kGrid; ++ty)
        for (int tx = 0; tx < kGrid; ++tx) {
            const int x0 = margin + (vw - 2 * margin - T) * tx / (kGrid - 1);
            const int y0 = margin + (vh - 2 * margin - T) * ty / (kGrid - 1);
            for (int y = y0; y < y0 + T; ++y)
                for (int x = x0; x < x0 + T; ++x) {
                    const uint32_t cp = c.px[(size_t)(c.P + y) * c.w + c.P + x];
                    if ((cp >> 24) != 255) continue;
                    const float dr = ((cp >> 16) & 255) / 255.0f - cb.key[0];
                    const float dg = ((cp >> 8) & 255) / 255.0f - cb.key[1];
                    const float db = (cp & 255) / 255.0f - cb.key[2];
                    if (dr * dr + dg * dg + db * db > 0.03f * 0.03f) continue;
                    float g[4];
                    GlowAt(cb, x + 0.5f, y + 0.5f, g);
                    if (g[3] > 0.9f) continue;
                    const uint32_t lp = shot.px[(size_t)y * shot.w + x];
                    const float lv[3] = { ((lp >> 16) & 255) / 255.0f, ((lp >> 8) & 255) / 255.0f,
                                          (lp & 255) / 255.0f };
                    // The real glow adds its light over the glass, so the
                    // glass is the screen minus the glow.
                    for (int q = 0; q < 3; ++q) {
                        const float base = lv[q] - g[q];
                        ch[q].push_back((int)std::clamp(base * 255.0f + 0.5f, 0.0f, 255.0f));
                    }
                }
        }
    const size_t got = ch[0].size();
    if (got < 64) {
        Wh_Log(L"glow: glass not read (%u px)", (unsigned)got);
        return;
    }
    int med[3];
    for (int q = 0; q < 3; ++q) {
        std::vector<int> v = ch[q];
        auto mid = v.begin() + got / 2;
        std::nth_element(v.begin(), mid, v.end());
        med[q] = *mid;
    }
    // Glass is one even colour once the glow is out. If most samples disagree,
    // something else covers the window: keep the capture's own colour.
    size_t agree = 0;
    for (size_t i = 0; i < got; ++i)
        if (abs(ch[0][i] - med[0]) <= 8 && abs(ch[1][i] - med[1]) <= 8 && abs(ch[2][i] - med[2]) <= 8)
            ++agree;
    const float f[3] = { med[0] / 255.0f, med[1] / 255.0f, med[2] / 255.0f };
    if (agree * 2 < got) {
        Wh_Log(L"glow: glass %.3f %.3f %.3f uneven (%u of %u agree), kept", f[0], f[1], f[2],
               (unsigned)agree, (unsigned)got);
        return;
    }
    cb.fill[0] = f[0]; cb.fill[1] = f[1]; cb.fill[2] = f[2]; cb.fill[3] = 1.0f;
    Wh_Log(L"glow: glass %.3f %.3f %.3f from %u px, %u agree", f[0], f[1], f[2], (unsigned)got,
           (unsigned)agree);
}

// A glass window with no glow: the capture shows a flat stand-in where the
// glass is, a shade off the live glass, so the copy brightened at the grab and
// dimmed at the drop. Paint the glass read from the screen over the stand-in;
// strength 0 adds no glow.
static bool GlassOnly(const Canvas& c, const GlassShot& shot, GlowCB& cb, bool* even = nullptr) {
    // No screen read (the move began first): only the live blur can stand in.
    if (!shot.ok && !even) return false;
    float key[3];
    if (!FindGlowKey(c, MonitorScale(c.vis), key)) return false;
    cb = GlowCB{};
    cb.hdr[0] = 1.0f;                       // one idle sprite: the shader's glass path runs
    cb.hdr[2] = 0.06f;
    cb.spr[0][2] = cb.spr[0][3] = 1.0f;     // a real size, so nothing divides by zero
    cb.spr[2][0] = 1.0f;
    cb.key[0] = key[0]; cb.key[1] = key[1]; cb.key[2] = key[2]; cb.key[3] = 1.0f;
    cb.body[0] = (float)c.P;         cb.body[1] = (float)c.P;
    cb.body[2] = (float)(c.w - c.P); cb.body[3] = (float)(c.h - c.P);
    cb.canvas[0] = (float)c.w;       cb.canvas[1] = (float)c.h;
    MatchGlass(shot, c, cb);
    if (even) *even = cb.fill[3] > 0.5f;
    if (cb.fill[3] > 0.5f) return true;
    if (!even) return false;
    // Busy background: no single colour for the glass. Only the live blur can
    // stand in for it, tinted with the capture's own stand-in colour.
    cb.fill[0] = key[0]; cb.fill[1] = key[1]; cb.fill[2] = key[2];
    return true;
}

struct DragGlow {
    bool     on = false;
    GlowMap  map;
    HWND     hwnd = nullptr;
    float    W = 0, H = 0, S = 1;
    GlowCB   cb{};
    glowtool::Settings s;
    bool     live = false;      // the clock moves: redraw while holding still
    double   lastDraw = 0.0;
    double   lastPoll = 0.0;

    bool Start(HWND h, const Settings& cfg, const Canvas& c, const GlassShot& shot) {
        on = false;
        const auto& g = cfg.glow;
        if (!g.enabled || !g.inDrag || g.dragStrength <= 0) return false;
        const float through = GlowSeeThrough(h);
        if (through <= 0.0f || !map.Open()) return false;
        GlowClock clk;
        if (!ReadGlowClock(map.m, h, clk)) { map.Close(); return false; }
        S = MonitorScale(c.vis);
        float key[3];
        if (!FindGlowKey(c, S, key)) { map.Close(); return false; }
        hwnd = h;
        s = g;
        W = (float)(c.w - 2 * c.P);
        H = (float)(c.h - 2 * c.P);
        cb = GlowCB{};
        // 100% looks like the real glow seen through the window.
        cb.hdr[1] = g.dragStrength / 100.0f * through;
        cb.hdr[2] = 0.06f;
        cb.key[0] = key[0]; cb.key[1] = key[1]; cb.key[2] = key[2]; cb.key[3] = 1.0f;
        cb.body[0] = (float)c.P;     cb.body[1] = (float)c.P;
        cb.body[2] = (float)c.P + W; cb.body[3] = (float)c.P + H;
        cb.canvas[0] = (float)c.w;   cb.canvas[1] = (float)c.h;
        GlowSprites(s, W, H, S, GlowTime(clk), cb);
        MatchGlass(shot, c, cb);
        live = clk.running && clk.e.live;
        lastPoll = NowSeconds();
        on = true;
        Wh_Log(L"glow: on, key %.3f %.3f %.3f, effect %d, through %.2f", key[0], key[1], key[2],
               (int)g.effect, through);
        return true;
    }

    // Refreshes the constants for this moment. False: the glow went away.
    bool Update(Device& dev) {
        if (!on) return false;
        GlowClock clk;
        if (!ReadGlowClock(map.m, hwnd, clk)) { Stop(dev); return false; }
        live = clk.running && clk.e.live;
        GlowSprites(s, W, H, S, GlowTime(clk), cb);
        dev.SetGlow(&cb);
        lastDraw = NowSeconds();
        return true;
    }

    // Due for a frame of its own while the window is held still. A frozen
    // glow is checked four times a second, so it starts moving again on its
    // own when the glow process unfreezes it.
    bool Due() {
        if (!on) return false;
        const double now = NowSeconds();
        if (!live && now - lastPoll >= 0.25) {
            lastPoll = now;
            GlowClock clk;
            if (!ReadGlowClock(map.m, hwnd, clk)) return true;    // gone: the draw drops it
            if (clk.running && clk.e.live) return true;
        }
        return live && now - lastDraw >= 1.0 / 60.0;
    }

    void Stop(Device& dev) {
        on = false;
        live = false;
        map.Close();
        dev.SetGlow(nullptr);
    }
};

// Sets the drag property for the glow process; leaves it a moment after the
// drag (worker timer) so the landing hand-off still sees it.
struct GlowProp {
    HWND h = nullptr;
    void Set(HWND hwnd) {
        if (g_glowPropHwnd && g_glowPropHwnd != hwnd) ClearGlowProp();
        if (SetPropW(hwnd, kGlowDragProp, (HANDLE)1)) { h = hwnd; g_glowPropHwnd = hwnd; }
    }
    void Drop() {
        if (h) { ClearGlowProp(); h = nullptr; }
    }
    ~GlowProp() {
        if (h) g_glowPropUntil = NowSeconds() + 0.5;
    }
};

// Follows the window Windows (or the window manager) is moving, drawing the
// wobble in its place. Never moves the window itself.
static void RunDrag(Device& dev, Overlay& ov, const DragRequest rq) {
    const HWND hwnd = rq.hwnd;
    const Settings cfg = SnapshotSettings();
    g_landing.store(false);

    if (!ov.EnsureSurface()) { Wh_Log(L"abort: no overlay surface"); return; }
    ov.WarmPipeline();
    ov.WarmPresent();

    // Ring: does Seamless Borders draw one on this window right now?
    RECT startOuter{}, startVis{};
    if (!ReadFramePair(hwnd, startOuter, startVis)) return;
    const bool bordersOn = cfg.borders && ModEnabled(L"local@seamless-borders");
    const bool startZoomed = IsZoomed(hwnd) != 0;
    bool ringShown = false;
    if (bordersOn && !startZoomed) {
        const RingSpec probe = ReadRingSpec(MonitorScale(startVis), true);
        ringShown = BordersRingShown(hwnd, startVis, probe.pad, 2);
    }

    // The live glass of a see-through window (glow or not): read once the
    // press has had a frame or two to show the window active, or as the move
    // begins.
    GlassShot glass;
    const bool wantGlass = GlowSeeThrough(hwnd) > 0.0f;

    // Wait for the move to begin: a press alone is a click.
    const double waitStart = NowSeconds();
    RECT last = startOuter;
    double sizeStableSince = NowSeconds();
    for (;;) {
        if (!HeldFor(rq)) return;
        if (QuitRequested() || !IsWindow(hwnd) || IsHungAppWindow(hwnd)) return;
        if (NowSeconds() - waitStart > 10.0) return;
        RECT r{};
        if (!GetWindowRect(hwnd, &r)) return;
        if (!SameSize(r, last)) sizeStableSince = NowSeconds();
        last = r;
        const bool moved = !EqualRect(&r, &startOuter);
        if (moved && !IsZoomed(hwnd)) {
            // A restore from maximized or snapped changes the size first;
            // let it finish before taking the picture.
            if (SameSize(r, startOuter) || NowSeconds() - sizeStableSince >= 0.033) break;
        }
        if (wantGlass && !glass.tried && NowSeconds() - waitStart >= 0.04) ShootGlass(hwnd, glass);
        if (!WaitMs(1)) return;
    }
    if (wantGlass && !glass.ok) ShootGlass(hwnd, glass);

    // Picture, then a final check that the size held still meanwhile.
    Canvas canvas;
    RingSpec ring;
    bool built = false;
    for (int attempt = 0; attempt < 3 && !built; ++attempt) {
        if (!HeldFor(rq) || QuitRequested()) return;
        RECT o{}, v{};
        if (!ReadFramePair(hwnd, o, v)) return;
        ring = RingSpec{};
        if (bordersOn) {
            const RingSpec probe = ReadRingSpec(MonitorScale(v), GetForegroundWindow() == hwnd);
            if (ringShown || BordersRingShown(hwnd, v, probe.pad, 48)) ring = probe;
        }
        if (!BuildCanvas(hwnd, ring, canvas)) continue;
        RECT now{};
        if (!GetWindowRect(hwnd, &now) || !SameSize(now, canvas.outer)) continue;
        built = true;
    }
    if (!built) { Wh_Log(L"abort: capture failed"); return; }

    RECT now{};
    GetWindowRect(hwnd, &now);
    const float W = (float)canvas.w, H = (float)canvas.h;
    // Rest of the canvas's top-left corner for a given window rect.
    auto restX = [&](const RECT& r) { return (float)(r.left + canvas.frameDx - canvas.P); };
    auto restY = [&](const RECT& r) { return (float)(r.top + canvas.frameDy - canvas.P); };

    Mesh mesh;
    mesh.Setup(cfg, cfg.mesh, restX(canvas.outer), restY(canvas.outer), W, H);

    // The glow, when this window has one: painted onto the copy's backdrop.
    DragGlow glow;
    GlowCB glassCb;
    bool liveGlass = false, evenGlass = true;
    // A note on the window of how its glass went this drag, for checking it
    // from outside: stage * 100 + setup step, then the last error.
    auto note = [&](int stage) {
        const int s = ov.glass ? ov.glass->step : 0;
        const uint32_t hr = ov.glass ? (uint32_t)ov.glass->lastHr : 0;
        SetPropW(hwnd, L"SeamlessWobblyGlassNote",
                 (HANDLE)(((uintptr_t)(stage * 100 + (glass.ok ? 0 : 50) + s) << (sizeof(void*) > 4 ? 32 : 16)) |
                          (sizeof(void*) > 4 ? hr : (hr & 0xFFFF))));
    };
    if (!glow.Start(hwnd, cfg, canvas, glass)) {
        dev.SetGlow(nullptr);
        if (GlassOnly(canvas, glass, glassCb, &evenGlass)) {
            // The real blur under the copy, which then paints only the tint.
            if (ov.glass && ov.glass->Start(canvas, CornerRadius(hwnd, MonitorScale(canvas.vis)),
                                            cfg.mesh, std::max(1, 64 / std::max(1, cfg.mesh)))) {
                glassCb.fill[3] = 2.0f + (1.0f - GlowSeeThrough(hwnd));
                liveGlass = true;
                note(4);
                {   // DIAG 1.2.9: the constants the copy is drawn with.
                    int bd = -1;
                    DwmGetWindowAttribute(hwnd, 38, &bd, sizeof(bd));
                    auto b8 = [](float v) { return (uint64_t)std::clamp((int)(v * 255.0f + 0.5f), 0, 255); };
                    const uint64_t v =
                        (uint64_t)std::clamp((int)(glassCb.fill[3] * 1000.0f), 0, 65535) |
                        (b8(glassCb.key[0]) << 16) | (b8(glassCb.key[1]) << 24) | (b8(glassCb.key[2]) << 32) |
                        ((uint64_t)(bd & 255) << 40) |
                        ((uint64_t)std::clamp((int)glassCb.hdr[0], 0, 255) << 48) |
                        ((uint64_t)std::clamp((int)(glassCb.hdr[2] * 1000.0f), 0, 255) << 56);
                    SetPropW(hwnd, L"SeamlessWobblyGlassFill", (HANDLE)(uintptr_t)v);
                }
                dev.SetGlow(&glassCb);
                SetPropW(hwnd, L"SeamlessWobblyGlassMap",
                         (HANDLE)(((uintptr_t)dev.glowWrites << (sizeof(void*) > 4 ? 32 : 16)) | (uint32_t)dev.glowHr));
            } else if (!evenGlass) {
                note(3);
                return;     // no live blur and no single colour: keep the native drag
            } else {
                note(3);
            }
            dev.SetGlow(&glassCb);
        } else if (wantGlass) {
            note(2);
            // Keep the native drag when the capture would replace glass with a dark fill.
            return;
        }
    }
    if (wantGlass && glow.on && glow.cb.fill[3] <= 0.5f) return;
    std::vector<uint32_t>().swap(glass.px);
    auto draw = [&] {
        glow.Update(dev);
        return ov.Draw(mesh);
    };
    GlowProp glowProp;    // before reveal: it outlives the uncloak

    if (!ov.SetContent(canvas, cfg.mesh)) { Wh_Log(L"abort: overlay content failed"); return; }
    ov.ResetHistory();
    // The overlay is shown while still transparent (its last frame was a
    // clear one), so its first picture is on screen before the window is
    // cloaked and there is never a frame with neither.
    ov.Show();
    GetWindowRect(hwnd, &now);
    if (!SameSize(now, canvas.outer)) {
        ov.Hide();
        return;
    }
    mesh.MoveRest(restX(now), restY(now));
    mesh.pos = mesh.rest;
    if (draw() != DrawResult::Ok) {
        Wh_Log(L"abort: first frame failed");
        ov.PresentClear();
        ov.Hide();
        return;
    }
    // Cloak in the same compositor frame as the first picture: waiting a
    // frame first let the real window slide out from under the copy (1.0.x).
    HideState hide;
    if (glow.on) glowProp.Set(hwnd);
    if (!HideWindowInPlace(hwnd, hide, liveGlass)) {
        glowProp.Drop();
        Wh_Log(L"abort: cannot cloak window");
        ov.PresentClear();
        ov.Hide();
        return;
    }
    DwmFlush();
    struct Reveal {
        HWND h; HideState& st;
        ~Reveal() { ShowWindowInPlace(h, st); }
    } reveal{hwnd, hide};

    RECT lastRect = now;
    double lastT = NowSeconds();
    double lastChange = lastT;
    double lastMoveT = lastT;
    float  prevVx = 0, prevVy = 0;
    bool   lostDevice = false;
    bool   resized = false;
    const double deadline = NowSeconds() + 120.0;

    auto followFrame = [&](bool kick) -> bool {
        PumpMessages();
        const double t = NowSeconds();
        const float dt = (float)std::min(t - lastT, 0.05);
        lastT = t;

        RECT r{};
        if (!GetWindowRect(hwnd, &r)) return false;
        if (!SameSize(r, lastRect)) { resized = true; return false; }
        bool changed = false;
        if (!SamePos(r, lastRect)) {
            const float frameDt = (float)std::max(t - lastMoveT, 1e-4);
            const float rawVx = (r.left - lastRect.left) / frameDt;
            const float rawVy = (r.top - lastRect.top) / frameDt;
            const float a = 0.35f;
            const float vxs = a * rawVx + (1 - a) * prevVx;
            const float vys = a * rawVy + (1 - a) * prevVy;
            mesh.MoveRest(restX(r), restY(r));
            if (kick) {
                if (prevVx * vxs < 0 || prevVy * vys < 0) {
                    mesh.Kick(vxs, vys);
                } else if (sqrtf(vxs * vxs + vys * vys) > 80.0f) {
                    mesh.Kick(vxs * 0.4f, vys * 0.4f);    // as the original, every moved frame
                }
            }
            prevVx = vxs; prevVy = vys;
            lastRect = r;
            lastMoveT = t;
            lastChange = t;
            changed = true;
        }
        const bool moving = mesh.Advance(dt);
        if (changed || moving || glow.Due()) {
            const DrawResult dr = draw();
            if (dr == DrawResult::DeviceLost) { lostDevice = true; return false; }
        } else {
            DwmFlush();    // holding still: wait a frame without drawing
        }
        return true;
    };

    while (HeldFor(rq)) {
        if (QuitRequested() || NowSeconds() > deadline || !IsWindow(hwnd)) break;
        if (rq.external &&
            (IsHungAppWindow(hwnd) || NowSeconds() - lastChange > 5.0)) {
            // The end message may never come (window manager turned off
            // mid-move); don't leave the move marked as held.
            HWND expect = hwnd;
            if (g_extHwnd.compare_exchange_strong(expect, nullptr)) g_extDown.store(false);
            break;
        }
        if (!followFrame(true)) break;
    }
    g_landing.store(true);
    // Let go as the original does: one last flick in the travel direction,
    // then the stiff landing springs pull it home with a single wobble.
    mesh.Kick(prevVx * 0.5f, prevVy * 0.5f);
    mesh.SettleFast();
    const double releasedAt = NowSeconds();
    const unsigned startsAtRelease = g_extStarts.load();

    if (resized || lostDevice || QuitRequested() || !IsWindow(hwnd)) {
        // Snapped or resized: the picture no longer fits. Show the window.
        ShowWindowInPlace(hwnd, hide);
        if (!lostDevice) ov.PresentClear();
        ov.Hide();
        return;
    }

    // Landing: Windows may still move or snap the window after the release.
    {
        const double until = NowSeconds() + 0.15;
        int still = 0;
        while (NowSeconds() < until && still < 2 && !QuitRequested()) {
            const RECT before = lastRect;
            if (!followFrame(false)) break;
            still = EqualRect(&before, &lastRect) ? still + 1 : 0;
        }
        if (resized || lostDevice) {
            ShowWindowInPlace(hwnd, hide);
            if (!lostDevice) ov.PresentClear();
            ov.Hide();
            return;
        }
    }

    // The landing springs finish within the original's 0.3 s.
    bool regrab = false;
    {
        const double hard = releasedAt + 0.30;
        while (!mesh.settled && NowSeconds() < hard && !QuitRequested()) {
            if (NewGrab(startsAtRelease)) { regrab = true; break; }
            if (!followFrame(false)) break;
        }
        if (resized || lostDevice) {
            ShowWindowInPlace(hwnd, hide);
            if (!lostDevice) ov.PresentClear();
            ov.Hide();
            return;
        }
    }

    // One exact frame at rest, then the window comes back underneath it.
    mesh.Snap();
    // An even glass lands under the flat colour read at the grab, then the live
    // blur goes. A busy one has no flat colour: the live blur stays until the
    // real window is back under it.
    const bool flatLanding = liveGlass && evenGlass;
    if (flatLanding) {
        glassCb.fill[3] = 1.0f;
        dev.SetGlow(&glassCb);
    }
    if (draw() == DrawResult::DeviceLost) lostDevice = true;
    if (flatLanding && ov.glass) {
        DwmFlush();
        ov.glass->Hide();
    }
    ShowWindowInPlace(hwnd, hide);
    if (!regrab && !lostDevice) WaitMs(cfg.revealHoldMs);
    if (!lostDevice) ov.PresentClear();
    ov.Hide();      // takes the live blur with it
}

// -----------------------------------------------------------------------------
// Worker thread
// -----------------------------------------------------------------------------
// One per process, created on first use: the overlay window belongs to it, and
// the device and overlay live on its stack so they are released here, not
// from DllMain at process exit.

static bool TakeQueued(DragRequest& out) {
    AcquireSRWLockExclusive(&g_queueLock);
    const DragRequest q = g_queued;
    const double at = g_queuedAt;
    g_queued = DragRequest{};
    ReleaseSRWLockExclusive(&g_queueLock);
    if (!q.hwnd || NowSeconds() - at > 1.0) return false;
    out = q;
    return true;
}

static DWORD WINAPI WorkerProc(LPVOID) {
    SetThreadDpiAwarenessContext(DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2);

    LiveGlass glass;                 // outlives the overlay, which points at it
    std::optional<Device>  dev;
    std::optional<Overlay> ov;
    double idleSince = 0.0;

    HANDLE waits[2] = { g_dragSignal, g_quitSignal };
    for (;;) {
        DWORD timeout = INFINITE;
        const int idleMs = g_idleReleaseMs.load();
        if (ov && idleMs > 0) {
            const double elapsed = (NowSeconds() - idleSince) * 1000.0;
            timeout = elapsed >= idleMs ? 0 : (DWORD)(idleMs - elapsed);
        }
        if (g_glowPropHwnd) {
            const double left = (g_glowPropUntil - NowSeconds()) * 1000.0;
            timeout = std::min<DWORD>(timeout, left <= 0 ? 0 : (DWORD)left + 1);
        }

        const DWORD r = MsgWaitForMultipleObjects(2, waits, FALSE, timeout, QS_ALLINPUT);
        if (r == WAIT_OBJECT_0) {
            DragRequest rq = g_pending;
            for (;;) {
                if (!dev) dev.emplace();
                if (!ov) { ov.emplace(); ov->d = &*dev; ov->glass = &glass; }
                RunDrag(*dev, *ov, rq);
                if (dev->Lost()) {
                    Wh_Log(L"worker: device lost, releasing");
                    ov.reset();
                    dev.reset();
                }
                // A grab that came while this one was landing.
                DragRequest next;
                if (QuitRequested() || !TakeQueued(next) || !HeldFor(next) ||
                    !Eligible(next.hwnd) || !CanHideReliably(next.hwnd))
                    break;
                rq = next;
            }
            g_dragging.store(false);
            // After g_dragging: a press in between takes the normal path.
            g_landing.store(false);
            idleSince = NowSeconds();
        } else if (r == WAIT_OBJECT_0 + 1) {
            break;
        } else if (r == WAIT_TIMEOUT) {
            if (g_glowPropHwnd && NowSeconds() >= g_glowPropUntil) ClearGlowProp();
            if ((ov || dev) && idleMs > 0 && (NowSeconds() - idleSince) * 1000.0 >= idleMs) {
                Wh_Log(L"worker: idle, releasing GPU resources");
                ov.reset();
                dev.reset();
                glass.Destroy();
            }
        } else {
            PumpMessages();
        }
    }

    ClearGlowProp();
    ov.reset();
    dev.reset();
    glass.Destroy();
    if (g_waitTimer) { CloseHandle(g_waitTimer); g_waitTimer = nullptr; }
    return 0;
}

static bool EnsureWorker() {
    if (g_worker) return true;
    if (!g_dragSignal || !g_quitSignal) return false;
    g_worker = CreateThread(nullptr, 0, WorkerProc, nullptr, 0, nullptr);
    return g_worker != nullptr;
}

// Runs on the app's thread inside its message pump, so it only checks and
// hands over; the press itself always goes on to Windows untouched.
static void Arm(HWND hwnd, bool external) {
    if (g_shuttingDown.load()) return;
    // The same press reaches us more than once (dispatch, then the
    // NCLBUTTONDOWN and SC_MOVE that DefWindowProc handles); while a drag is
    // live those repeats are ignored before anything touches the window.
    const bool busy = g_dragging.load();
    if (busy && !g_landing.load()) return;
    if (external) {
        if (!g_windowManager.load()) return;
    } else {
        if (!PrimaryButtonDown()) return;   // keyboard Move has no pointer to follow
        g_exitHwnd.store(nullptr);
    }
    // Alt is the window manager's own key, so it can't also mean "bypass" there.
    if (!(external && g_bypassVk.load() == VK_MENU) && BypassHeld()) return;
    if (!Eligible(hwnd)) return;
    if (!busy && !CanHideReliably(hwnd)) return;

    bool expected = false;
    if (busy || !g_dragging.compare_exchange_strong(expected, true)) {
        // Landing: queue it. The window may be the one still cloaked, so the
        // cloak test waits until the worker picks this up.
        if (!g_landing.load()) return;
        AcquireSRWLockExclusive(&g_queueLock);
        g_queued = DragRequest{ hwnd, external };
        g_queuedAt = NowSeconds();
        ReleaseSRWLockExclusive(&g_queueLock);
        return;
    }
    if (!EnsureWorker()) {
        g_dragging.store(false);
        Wh_Log(L"skip: no worker thread");
        return;
    }
    g_pending = DragRequest{ hwnd, external };
    SetEvent(g_dragSignal);
}

static bool HandleExternal(HWND hwnd, WPARAM wp) {
    if (wp == 1) {
        g_extHwnd.store(hwnd);
        g_extDown.store(true);
        g_extStarts.fetch_add(1);
        Arm(hwnd, true);
    } else if (g_extHwnd.load() == hwnd) {
        g_extDown.store(false);
    }
    return true;
}

// -----------------------------------------------------------------------------
// Hooks
// -----------------------------------------------------------------------------

using DispatchMessage_t = LRESULT(WINAPI*)(const MSG*);
static DispatchMessage_t DispatchMessageW_orig;
static DispatchMessage_t DispatchMessageA_orig;

static bool OnDispatch(const MSG* msg) {
    if (!msg) return false;
    if (g_extMsg && msg->message == g_extMsg) {
        HandleExternal(msg->hwnd, msg->wParam);
        return true;      // ours; nothing else wants it
    }
    if (msg->message == WM_NCLBUTTONDOWN && msg->wParam == HTCAPTION)
        Arm(msg->hwnd, false);
    return false;
}

static LRESULT WINAPI DispatchMessageW_hook(const MSG* msg) {
    if (OnDispatch(msg)) return 0;
    return DispatchMessageW_orig(msg);
}

static LRESULT WINAPI DispatchMessageA_hook(const MSG* msg) {
    if (OnDispatch(msg)) return 0;
    return DispatchMessageA_orig(msg);
}

using DefWindowProc_t = LRESULT(WINAPI*)(HWND, UINT, WPARAM, LPARAM);
static DefWindowProc_t DefWindowProcW_orig;
static DefWindowProc_t DefWindowProcA_orig;

// Returns true if the message was ours and is fully handled.
static bool OnDefWindowProc(HWND hWnd, UINT msg, WPARAM wp) {
    if (g_extMsg && msg == g_extMsg) {
        HandleExternal(hWnd, wp);
        return true;
    }
    switch (msg) {
        case WM_NCLBUTTONDOWN:
            if (wp == HTCAPTION) Arm(hWnd, false);
            break;
        case WM_SYSCOMMAND:
            if ((wp & 0xFFF0) == SC_MOVE) Arm(hWnd, false);
            break;
        case WM_EXITSIZEMOVE:
            g_exitHwnd.store(hWnd);
            break;
    }
    return false;
}

static LRESULT WINAPI DefWindowProcW_hook(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp) {
    if (OnDefWindowProc(hWnd, msg, wp)) return 0;
    return DefWindowProcW_orig(hWnd, msg, wp, lp);
}

static LRESULT WINAPI DefWindowProcA_hook(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp) {
    if (OnDefWindowProc(hWnd, msg, wp)) return 0;
    return DefWindowProcA_orig(hWnd, msg, wp, lp);
}

// -----------------------------------------------------------------------------
// Entry points
// -----------------------------------------------------------------------------

// The mod runs in two kinds of process. In apps it wobbles windows. In
// windhawk.exe it starts, and then is, the glow process (a Windhawk tool
// mod, as Acrylic Color Glows was): one process that draws every glow.

enum class Role { Wobble, GlowLauncher, GlowTool, None };
static Role   g_role = Role::Wobble;
static HANDLE g_toolMutex = nullptr;
static constexpr wchar_t kGlowToolMutex[] = L"windhawk-tool-mod_" WH_MOD_ID;

static bool InWindhawkExe() {
    wchar_t path[MAX_PATH];
    const DWORD n = GetModuleFileNameW(nullptr, path, ARRAYSIZE(path));
    if (!n || n >= ARRAYSIZE(path)) return false;
    const wchar_t* base = wcsrchr(path, L'\\');
    return _wcsicmp(base ? base + 1 : path, L"windhawk.exe") == 0;
}

static void WINAPI ToolEntryPoint_Hook() {
    Wh_Log(L">");
    ExitThread(0);
}

static Role GlowRoleInit() {
    DWORD session = 0;
    if (ProcessIdToSessionId(GetCurrentProcessId(), &session) && session == 0)
        return Role::None;
    int argc = 0;
    LPWSTR* argv = CommandLineToArgvW(GetCommandLineW(), &argc);
    if (!argv) { Wh_Log(L"glow: no command line"); return Role::None; }
    bool service = false, tool = false, ours = false;
    for (int i = 1; i < argc; ++i) {
        if (!wcscmp(argv[i], L"-service") || !wcscmp(argv[i], L"-service-start") ||
            !wcscmp(argv[i], L"-service-stop")) { service = true; break; }
    }
    for (int i = 1; i < argc - 1; ++i) {
        if (!wcscmp(argv[i], L"-tool-mod")) {
            tool = true;
            ours = !wcscmp(argv[i + 1], WH_MOD_ID);
            break;
        }
    }
    LocalFree(argv);
    if (service) return Role::None;
    if (!ours) return tool ? Role::None : Role::GlowLauncher;

    // Owning the mutex, not creating it, makes this the glow process. After an update the
    // old glow process may still be closing, so wait for it a little.
    g_toolMutex = CreateMutexW(nullptr, FALSE, kGlowToolMutex);
    if (!g_toolMutex) { Wh_Log(L"glow: CreateMutex failed"); ExitProcess(1); }
    const DWORD owned = WaitForSingleObject(g_toolMutex, 8000);
    if (owned != WAIT_OBJECT_0 && owned != WAIT_ABANDONED) {
        Wh_Log(L"glow: tool already running");
        ExitProcess(1);
    }
    if (!glowtool::WhTool_ModInit()) ExitProcess(1);
    // The process exists only for the mod: windhawk.exe's own main never runs.
    auto* dos = (IMAGE_DOS_HEADER*)GetModuleHandleW(nullptr);
    auto* nt = (IMAGE_NT_HEADERS*)((BYTE*)dos + dos->e_lfanew);
    Wh_SetFunctionHook((BYTE*)dos + nt->OptionalHeader.AddressOfEntryPoint,
                       (void*)ToolEntryPoint_Hook, nullptr);
    return Role::GlowTool;
}

// True while a glow process owns the mutex. Taking a free one for a moment is harmless:
// a glow process that is starting waits for it.
static bool GlowToolRunning() {
    HANDLE m = OpenMutexW(SYNCHRONIZE | MUTEX_MODIFY_STATE, FALSE, kGlowToolMutex);
    if (!m) return false;
    const DWORD w = WaitForSingleObject(m, 0);
    if (w == WAIT_OBJECT_0 || w == WAIT_ABANDONED) ReleaseMutex(m);
    CloseHandle(m);
    return w == WAIT_TIMEOUT;
}

// afterLoad: the mod was just loaded or updated. The old glow process may still own the
// mutex while it closes, so start a new one anyway; it waits, and leaves if the old one stays.
static void StartGlowTool(bool afterLoad) {
    if (!glowtool::GlowEnabledSetting()) return;
    if (!afterLoad && GlowToolRunning()) return;
    wchar_t exe[MAX_PATH];
    const DWORD n = GetModuleFileNameW(nullptr, exe, ARRAYSIZE(exe));
    if (!n || n >= ARRAYSIZE(exe)) { Wh_Log(L"glow: GetModuleFileName failed"); return; }
    wchar_t cmd[MAX_PATH + 64];
    swprintf_s(cmd, L"\"%s\" -tool-mod \"%s\"", exe, WH_MOD_ID);
    HMODULE k = GetModuleHandleW(L"kernelbase.dll");
    if (!k) k = GetModuleHandleW(L"kernel32.dll");
    using CreateProcessInternalW_t = BOOL(WINAPI*)(
        HANDLE, LPCWSTR, LPWSTR, LPSECURITY_ATTRIBUTES, LPSECURITY_ATTRIBUTES, BOOL, DWORD,
        LPVOID, LPCWSTR, LPSTARTUPINFOW, LPPROCESS_INFORMATION, PHANDLE);
    auto create = k ? (CreateProcessInternalW_t)GetProcAddress(k, "CreateProcessInternalW")
                    : nullptr;
    if (!create) { Wh_Log(L"glow: no CreateProcessInternalW"); return; }
    STARTUPINFOW si{};
    si.cb = sizeof(si);
    si.dwFlags = STARTF_FORCEOFFFEEDBACK;
    PROCESS_INFORMATION pi{};
    if (!create(nullptr, exe, cmd, nullptr, nullptr, FALSE, NORMAL_PRIORITY_CLASS,
                nullptr, nullptr, &si, &pi, nullptr)) {
        Wh_Log(L"glow: CreateProcess failed (%u)", GetLastError());
        return;
    }
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
    Wh_Log(L"glow: tool process started");
}

static BOOL WobbleInit() {
    LoadSettings();

    g_extMsg = RegisterWindowMessageW(L"SeamlessWobblyWindows_ExternalDrag");
    g_dragSignal = CreateEventW(nullptr, FALSE, FALSE, nullptr);
    g_quitSignal = CreateEventW(nullptr, TRUE,  FALSE, nullptr);
    if (!g_dragSignal || !g_quitSignal) {
        Wh_Log(L"init: could not create events");
        return FALSE;
    }

    const BOOL w  = WindhawkUtils::SetFunctionHook(DefWindowProcW, DefWindowProcW_hook, &DefWindowProcW_orig);
    const BOOL a  = WindhawkUtils::SetFunctionHook(DefWindowProcA, DefWindowProcA_hook, &DefWindowProcA_orig);
    const BOOL dw = WindhawkUtils::SetFunctionHook(DispatchMessageW, DispatchMessageW_hook, &DispatchMessageW_orig);
    const BOOL da = WindhawkUtils::SetFunctionHook(DispatchMessageA, DispatchMessageA_hook, &DispatchMessageA_orig);
    Wh_Log(L"init: hooks defW=%d defA=%d dispW=%d dispA=%d", w, a, dw, da);
    return TRUE;
}

static void WobbleSettingsChanged() {
    LoadSettings();
}

static void WobbleBeforeUninit() {
    g_shuttingDown.store(true);
    if (g_quitSignal) SetEvent(g_quitSignal);
}

static void WobbleUninit() {
    if (g_worker) {
        WaitForSingleObject(g_worker, INFINITE);
        CloseHandle(g_worker);
        g_worker = nullptr;
    }
    if (g_dragSignal) { CloseHandle(g_dragSignal); g_dragSignal = nullptr; }
    if (g_quitSignal) { CloseHandle(g_quitSignal); g_quitSignal = nullptr; }
    if (g_classRegistered.exchange(false))
        UnregisterClassW(kOverlayClass, MOD_HINSTANCE);
    g_api.Free();
    if (g_shcore) { FreeLibrary(g_shcore); g_shcore = nullptr; }
    g_getDpiForMonitor = nullptr;
    g_shcoreTried = false;
    Wh_Log(L"uninit: done");
}

// ---- Game guard: keeps this mod out of games ----
// Decides from this process's own exe path and the files next to it. It never
// opens or looks at other processes. About a dozen file lookups, once, at init.
#include <wctype.h>
#include <string>

namespace gameguard {

// Case-insensitive match where * stands for any run of characters.
static bool Wild(PCWSTR pat, PCWSTR s) {
    for (;;) {
        if (*pat == L'*') {
            while (*pat == L'*') pat++;
            if (!*pat) return true;
            for (;; s++) {
                if (Wild(pat, s)) return true;
                if (!*s) return false;
            }
        }
        if (!*pat || !*s) return *pat == *s;
        if (towlower(*pat) != towlower(*s)) return false;
        pat++;
        s++;
    }
}

// Names separated by commas, semicolons or new lines.
static bool InList(PCWSTR list, PCWSTR exe) {
    if (!list) return false;
    PCWSTR p = list;
    while (*p) {
        while (*p == L',' || *p == L';' || *p == L' ' || *p == L'\t' || *p == L'\r' || *p == L'\n') p++;
        PCWSTR b = p;
        while (*p && *p != L',' && *p != L';' && *p != L'\r' && *p != L'\n') p++;
        PCWSTR e = p;
        while (e > b && (e[-1] == L' ' || e[-1] == L'\t')) e--;
        if (e > b && e - b < 260) {
            wchar_t t[260];
            wmemcpy(t, b, e - b);
            t[e - b] = 0;
            if (Wild(t, exe)) return true;
        }
    }
    return false;
}

static bool Exists(const std::wstring& dir, PCWSTR name) {
    return GetFileAttributesW((dir + L"\\" + name).c_str()) != INVALID_FILE_ATTRIBUTES;
}

// True when something in dir matches the pattern (one lookup, no recursion).
static bool Has(const std::wstring& dir, PCWSTR pattern) {
    WIN32_FIND_DATAW fd;
    HANDLE h = FindFirstFileExW((dir + L"\\" + pattern).c_str(), FindExInfoBasic, &fd,
                                FindExSearchNameMatch, nullptr, 0);
    if (h == INVALID_HANDLE_VALUE) return false;
    FindClose(h);
    return true;
}

static bool Contains(const std::wstring& lowPath, PCWSTR part) {
    return lowPath.find(part) != std::wstring::npos;
}

// Anti-cheat files beside the exe or one folder up.
static PCWSTR AntiCheatIn(const std::wstring& dir) {
    if (dir.size() < 4) return nullptr;
    static const PCWSTR pats[] = {
        L"EasyAntiCheat*", L"BattlEye", L"BEClient*.dll", L"vanguard*", L"vgc.exe",
        L"xigncode*", L"x3.xem", L"nProtect*", L"GameGuard*", L"npgg*", L"PnkBstr*",
    };
    for (PCWSTR pat : pats) {
        if (Has(dir, pat)) return L"anti-cheat files next to it";
    }
    if (Exists(dir, L"pb\\pbcl.dll")) return L"PunkBuster files next to it";
    if (Exists(dir, L".build.info")) return L"Battle.net game folder";
    return nullptr;
}

// Returns a short reason when this process is a game, or nullptr.
static PCWSTR Reason(PCWSTR path, PCWSTR exe, PCWSTR skipList) {
    std::wstring low(path);
    for (auto& c : low) c = (wchar_t)towlower(c);

    // Never block the shell, Windhawk itself, Windows programs and game launchers.
    static const PCWSTR never[] = {
        L"explorer.exe", L"dwm.exe", L"windhawk.exe", L"windhawk-mod.exe",
        L"windhawk-mod-uiaccess.exe", L"windhawk-mod-elevated.exe", L"windhawk-ui.exe",
        L"steam.exe", L"steamwebhelper.exe", L"steamservice.exe",
        L"epicgameslauncher.exe", L"epicwebhelper.exe", L"unrealcefsubprocess.exe",
        L"battle.net.exe", L"agent.exe", L"galaxyclient.exe", L"galaxyclient helper.exe",
        L"riotclientservices.exe", L"riotclientux.exe", L"riotclientuxrender.exe",
        L"eadesktop.exe", L"eabackgroundservice.exe", L"upc.exe", L"ubisoftconnect.exe",
    };
    for (PCWSTR n : never) {
        if (_wcsicmp(exe, n) == 0) return nullptr;
    }
    if (_wcsnicmp(exe, L"battle.net", 10) == 0) return nullptr;
    wchar_t win[MAX_PATH];
    UINT wl = GetWindowsDirectoryW(win, MAX_PATH);
    if (wl && wl < MAX_PATH) {
        std::wstring w(win);
        for (auto& c : w) c = (wchar_t)towlower(c);
        w += L"\\";
        if (low.compare(0, w.size(), w) == 0) return nullptr;
    }
    static const PCWSTR launcherDirs[] = {
        L"\\epic games\\launcher\\", L"\\riot games\\riot client\\",
        L"\\rockstar games\\launcher\\", L"\\rockstar games\\social club\\",
    };
    for (PCWSTR d : launcherDirs) {
        if (Contains(low, d)) return nullptr;
    }

    if (InList(skipList, exe)) return L"on your skip list";

    static const PCWSTR libraries[] = {
        L"\\steamapps\\common\\", L"\\epic games\\", L"\\xboxgames\\", L"\\riot games\\",
        L"\\gog galaxy\\games\\", L"\\gog games\\", L"\\ubisoft game launcher\\games\\",
        L"\\ea games\\", L"\\battle.net\\", L"\\rockstar games\\",
    };
    for (PCWSTR d : libraries) {
        if (Contains(low, d)) return L"inside a game library folder";
    }

    std::wstring dir(path);
    size_t cut = dir.rfind(L'\\');
    if (cut == std::wstring::npos) return nullptr;
    dir.resize(cut);
    std::wstring parent = dir;
    cut = parent.rfind(L'\\');
    if (cut != std::wstring::npos) parent.resize(cut);

    if (Contains(low, L"\\windowsapps\\") &&
        (Exists(dir, L"MicrosoftGame.config") || Exists(parent, L"MicrosoftGame.config"))) {
        return L"Store game (MicrosoftGame.config)";
    }
    if (PCWSTR r = AntiCheatIn(dir)) return r;
    if (PCWSTR r = AntiCheatIn(parent)) return r;
    if (Exists(dir, L"UnityPlayer.dll") || Exists(dir, L"GameAssembly.dll")) return L"Unity game files next to it";
    static const wchar_t kShip[] = L"-win64-shipping.exe";
    size_t el = wcslen(exe);
    if ((el > ARRAYSIZE(kShip) - 1 && _wcsicmp(exe + el - (ARRAYSIZE(kShip) - 1), kShip) == 0) ||
        Contains(low, L"\\binaries\\win64\\")) {
        return L"Unreal Engine game layout";
    }
    return nullptr;
}

// TRUE when this process is a game and the mod should not load into it.
static BOOL ShouldSkipProcess() {
    if (!Wh_GetIntSetting(L"gameGuard.enabled")) return FALSE;
    wchar_t path[2 * MAX_PATH];
    DWORD len = GetModuleFileNameW(nullptr, path, ARRAYSIZE(path));
    if (!len || len >= ARRAYSIZE(path)) return FALSE;
    PCWSTR exe = wcsrchr(path, L'\\');
    exe = exe ? exe + 1 : path;

    PCWSTR allow = Wh_GetStringSetting(L"gameGuard.allow");
    bool allowed = InList(allow, exe);
    Wh_FreeStringSetting(allow);
    if (allowed) return FALSE;

    PCWSTR skip = Wh_GetStringSetting(L"gameGuard.skip");
    PCWSTR why = Reason(path, exe, skip);
    Wh_FreeStringSetting(skip);
    if (!why) return FALSE;
    Wh_Log(L"Game guard: %s stays unstyled (%s)", exe, why);
    return TRUE;
}

}  // namespace gameguard
// ---- end of game guard ----

BOOL Wh_ModInit() {
    if (gameguard::ShouldSkipProcess()) return FALSE;
    if (!InWindhawkExe()) return WobbleInit();
    g_role = GlowRoleInit();
    return g_role == Role::None ? FALSE : TRUE;
}

void Wh_ModAfterInit() {
    if (g_role == Role::GlowLauncher) StartGlowTool(true);
}

void Wh_ModSettingsChanged() {
    switch (g_role) {
        case Role::Wobble:       WobbleSettingsChanged(); break;
        case Role::GlowLauncher: StartGlowTool(false); break;
        case Role::GlowTool:     glowtool::WhTool_ModSettingsChanged(); break;
        case Role::None:         break;
    }
}

void Wh_ModBeforeUninit() {
    if (g_role == Role::Wobble) WobbleBeforeUninit();
}

void Wh_ModUninit() {
    switch (g_role) {
        case Role::Wobble: WobbleUninit(); break;
        case Role::GlowTool:
            glowtool::WhTool_ModUninit();
            ExitProcess(0);
        default: break;
    }
}
