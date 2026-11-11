#include <shlwapi.h>
// ==WindhawkMod==
// @id              seamless-window-manager
// @name            Seamless Window Manager
// @description     Move, resize, snap and focus windows with the mouse or keyboard, with app rules, gaps and a pause key
// @version         2.4.1
// @author          DavidHiFi, m417z, Asteski, TomberWolf, RamonUnch, Stefan Sundin
// @github          https://github.com/DavidHiFi
// @homepage        https://github.com/DavidHiFi/davids-windhawk-mods
// @license         GPL-3.0
// @include         *
// @include         windhawk.exe
// @compilerOptions -luser32 -ldwmapi -lgdi32 -lshcore -lcomctl32 -lshell32 -lshlwapi -ladvapi32 -ld2d1 -luxtheme -ldwrite -lole32
// @donateUrl       https://ko-fi.com/DavidHiFi
// ==/WindhawkMod==

// ==WindhawkModReadme==
/*
# Seamless Window Manager

Move, resize, snap and focus windows from anywhere, with the mouse or the
keyboard. Set rules for your apps, add gaps, and pause it all with one key
when a game needs Alt. Works on administrator windows too.

![Seamless Window Manager preview](https://raw.githubusercontent.com/DavidHiFi/davids-windhawk-mods/main/media/previews/seamless-window-manager.gif)

## Features

- **Alt+drag to move.** Grab a window anywhere, not just by its title bar.
- **Alt+right-drag to resize** from the nearest edge or corner, including
  borderless windows such as Ditto and Flow Launcher.
- **Snap with the keyboard** to halves, quarters, the center or almost
  maximized.
- **Gaps** around snapped windows, in pixels or as a share of the screen,
  and optionally scaled for high-DPI monitors.
- **Resize with the keyboard.** Press Alt+Shift+R, then use the arrow keys.
  Hold Shift to move the window instead. Press Esc when you're done.
- **Send to another monitor** with Ctrl+Shift+arrow keys. Down is the main
  monitor, and the other arrows pick the monitor above, left or right of it.
  Maximized windows stay maximized, and the mouse pointer can come along.
- **Tiling.** New windows fill the screen side by side, like GlazeWM.
  Move them around with Alt+Shift+arrow keys, grow them with
  Ctrl+Alt+Shift+arrow keys, and float one with Alt+T. The half and quarter
  keys rearrange the tiles around the window. Dragging a tiled window onto
  another swaps them, and dragging an edge resizes its neighbours too.
- **Fill and borderless.** Alt+F fills the screen but keeps the gaps around
  the window. Ctrl+Shift+F takes the title bar and borders off and covers the
  whole monitor, taskbar included. Press either again to go back.
- **Focus by direction.** Alt+arrow keys switch to the nearest window on that
  side, on any monitor, and the mouse pointer jumps with you.
- **Focus follows the mouse**, if you want it, and the pointer can jump to
  the window you switch to with the keyboard.
- **App rules** place, pin, fade or skip chosen apps. Match by app name,
  window title or class, with plain text or a regex.
- **Pause** with Ctrl+Shift+P. Everything stops until you press it again,
  and a small popup tells you which state you're in.
- **Background window opacity** makes inactive windows slightly see-through.
  Off by default.
- **Drag File Explorer by its title strip** instead of grabbing a tab.

## Default shortcuts

| Shortcut | Action |
| --- | --- |
| Alt + left drag | Move the window |
| Alt + right drag | Resize the window |
| Alt + arrow keys | Focus the window on that side |
| Alt + Shift + arrow keys | Move the window that way |
| Ctrl + Alt + Shift + arrow keys | Grow the window that way |
| Alt + T | Tile or float the window |
| Alt + Q / W / E / R | Left, right, top or bottom half |
| Alt + U / I / J / K | Top-left, top-right, bottom-left or bottom-right quarter |
| Alt + C | Center half |
| Alt + H / Y / G | Maximize, almost maximize, center |
| Alt + ] / [ | Next or previous monitor |
| Alt + 1 / 2 / 3 / 4 | Focus monitor 1 to 4 (left, main, right, top) |
| Alt + Shift + 1 / 2 / 3 / 4 | Send the window to that monitor |
| Ctrl + Alt + Shift + 1 to 9 | Switch virtual desktop |
| Ctrl + Alt + left drag | Move with magnetic edges |
| Alt + Z | Undo the snap |
| Alt + F | Fill the screen inside the gaps |
| Ctrl + Shift + F | Borderless fullscreen |
| Alt + M | Minimize |
| Alt + Shift + Q | Close |
| Alt + Shift + R | Resize with the keyboard |
| Ctrl + Shift + P | Pause or resume |
| Alt + middle click | Window menu |

You can change or turn off every shortcut in the settings. Alt+Left and
Alt+Right replace Back and Forward in browsers and File Explorer; pick other
keys if you need those. Windows glide into place instead of jumping; the
length is under Look. When a snap or monitor shortcut matches one of
the keys above, the key above wins.

## App rule examples

| Goal | App names | Title | Class | Match | Action |
| --- | --- | --- | --- | --- | --- |
| Center dialogs | `*` | | `#32770` | Is exactly | Center, only when it opens |
| Leave a game alone | `eldenring` | | | | Leave this app alone |
| Keep picture-in-picture on top | `chrome; firefox` | `picture.in.picture` | | Regex | Leave the position alone, Keep on top |
| Notepad top-right | `notepad` | | | | Top-right quarter, Keep the size |

## Notes

- This mod replaces Window Manager Plus, AltDrag, AltSnap, Snap Commander
  and Move Window to Monitor. Turn those off before you turn this on.
- Keyboard shortcuts, rules and effects run in a small elevated Windhawk
  helper, which is what lets them reach administrator windows.
- Search, Start, the lock screen and the snipping overlay are always left
  alone.
- Window borders come from Seamless Borders and corner shapes from Custom
  Window Corner Radius, so this mod doesn't repeat them.
- Background opacity skips windows that already use Mica or acrylic, and
  apps that handle their own transparency.
- Other mods that put windows back where they were can fight the tiling.
  Turn their restore option off, or list the app under Apps that never tile.
- Focus follows the mouse uses the Windows setting of the same name and puts
  it back the way it was when you turn the mod off.

## Credits

Combines [AltDrag](https://windhawk.net/mods/alt-drag) by m417z (inspired by
[AltSnap](https://github.com/RamonUnch/AltSnap) by Stefan Sundin and
RamonUnch), [Snap Commander](https://windhawk.net/mods/snap-commander) by
Asteski and [Move Window to Monitor](https://windhawk.net/mods/move-window-to-monitor)
by TomberWolf. Tiling and its keys, and several options, including gaps,
keyboard resize, pause, focus follows the mouse, the cursor jump and the rule
matching, follow
[GlazeWM](https://github.com/glzr-io/glazewm) by Lars Berger and contributors.
That covers behaviour, ideas and option names only; no GlazeWM code is used.
GPL-3.0, following AltDrag.
*/
// ==/WindhawkModReadme==


/*
Third-party notices

AltDrag: m417z, based on AltSnap by RamonUnch and AltDrag by Stefan Sundin.
The combined mod is distributed under GPL-3.0.

Snap Commander: Copyright (c) Asteski.
Move Window to Monitor: Copyright (c) TomberWolf.
These components are available under the MIT license:

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

// Merged from the installed sources:
//   local@alt-snap-drag.wh.cpp <- drag
//   snap-commander.wh.cpp <- snap
//   move-window-to-monitor.wh.cpp <- move

#include <commctrl.h>
#include <algorithm>
#include <atomic>
#include <bit>
#include <cstdlib>
#include <array>
#include <cwctype>
#include <memory>
#include <mutex>
#include <string>
#include <unordered_set>
#include <windhawk_utils.h>
#include <windows.h>
#include <dwmapi.h>
#include <deque>
#include <unordered_map>
#include <vector>
#include <shellscalingapi.h>
#include <regex>

// Used by both monitor-move paths: when the "Move the cursor with the window"
// setting is on, put the pointer in the middle of the window that was just sent
// to another monitor. A minimized window has no useful position, so it is skipped.
static void MoveCursorToWindow(HWND hwnd) {
    if (!Wh_GetIntSetting(L"cursorFollowsWindow") || IsIconic(hwnd)) return;
    RECT rc;
    if (GetWindowRect(hwnd, &rc))
        SetCursorPos((rc.left + rc.right) / 2, (rc.top + rc.bottom) / 2);
}

// Alt+Shift+M brings these back: windows minimized while the mod runs, newest
// last. Filled and read on the tiling thread only.
std::vector<HWND> g_minimizedWindows;
namespace swm {
inline std::atomic<bool> g_paused{false};
// Last mouse button press or release seen by the helper's low level hook.
inline std::atomic<ULONGLONG> g_lastMouseButtonTick{0};
inline std::atomic<int> g_resizeStepPct{2};
// Glide length for snaps and tiles; 0 is off. g_animOff > 0 skips it on a thread.
inline std::atomic<int> g_animMs{180};
inline thread_local int g_animOff = 0;
// Ctrl+Alt drag: how close an edge must come to cling, and the gap kept.
inline std::atomic<int> g_magnetPx{20};
inline std::atomic<int> g_magnetGap{20};
// Marks the zero-distance mouse input sent to unlock SetForegroundWindow.
constexpr ULONG_PTR kFocusInputExtraInfo = 0x53574D31;
constexpr UINT kPauseChangedMessage = WM_APP + 300;
bool IsPaused();
bool OnResizeKey(WPARAM message, const KBDLLHOOKSTRUCT* key);
bool OnLowLevelThreadMessage(const MSG& msg);
void RegisterModeKeys();
void UnregisterModeKeys();
void LeaveResizeMode();
void ApplyRuleLook(HWND hWnd, BYTE alpha, bool onTop);
bool IsReservedHotkey(UINT mods, UINT vk);
bool IsTiledWindow(HWND hWnd);
void PostTileRegion(int region);
}  // namespace swm
namespace snapCommander {
static RECT GappedWorkArea(HMONITOR monitor, const RECT& work);
void LoadIgnoreRules();
bool IsIgnoredWindow(HWND hWnd, PCWSTR exeName);
}  // namespace snapCommander

//////// drag ////////
namespace altSnapDrag {

void LoadSettings();
bool g_globalInput = false;
std::wstring g_globalExclusions;


// A fork of the alt-drag mod by m417z (https://github.com/m417z/my-windhawk-mods),
// which is based on AltSnap by RamonUnch (https://github.com/RamonUnch/AltSnap)
// and the original AltDrag by Stefan Sundin. Modified in 2026 by DavidHiFi to
// add configurable AltSnap mouse actions and keyboard shortcuts.
//
// Source code is published under The GNU General Public License v3.0, like the
// original. For bug reports and feature requests, please open an issue here:
// https://github.com/DavidHiFi/davids-windhawk-mods/issues



// A drag is started by taking the button press away from the target window as
// it's retrieved from the message queue, and posting a request to the root
// window, which the mod instance in the root window's thread turns into the
// system command a title bar or border drag generates. Intercepting at
// retrieval time means the window procedure never sees the press, so it
// doesn't matter how the program handles mouse input, and the system size/move
// loop provides snapping, DWM animations and maximized window handling the
// same way a title bar drag does. The root window may belong to another
// process, e.g. ApplicationFrameHost.exe hosting a UWP app's CoreWindow, so
// the request is a registered message which is allowed through the UIPI
// message filter.
//
// The loop is made for the left button: it starts only with that button down
// in the thread's synchronized key state, and ends only on WM_LBUTTONUP, which
// the release of any other button is turned into as the loop retrieves it. A
// release within the drag threshold ends it before it got going, and the
// press taken for it is then replayed as a click, simulated at the cursor, so
// that a click with the keys held keeps whatever meaning the program gives it.
// A press held for the drag delay is taken from the queue right away and
// turned into the request once the delay is over, posted back as a click if
// the button was released before that, or handed back in place of the move
// which left the drag threshold before that, the drag being the program's own.
//
// The interception is done with a WH_GETMESSAGE hook per thread. Threads which
// retrieve messages are discovered by hooking the win32u syscall stubs, which
// every message loop goes through, including user32's internal modal loops such
// as DialogBox2 which bypass the exported PeekMessage. The stub hooks only
// install the thread hooks and then tail call the original function, so no mod
// frame is left on the stack while a thread waits for a message, which would
// otherwise prevent unloading the mod.
//
// Pointer input (WM_POINTER*, used by XAML and other mouse-in-pointer windows)
// is delivered straight to the window procedure and is never seen by
// WH_GETMESSAGE or WH_CALLWNDPROC hooks, so it's intercepted by subclassing. A
// WH_CALLWNDPROC hook subclasses the window under the pointer while a
// trigger's keys are held, and the subclass routes a contact those keys
// started to DefWindowProc, which promotes it to the legacy mouse messages the
// retrieval hook handles. A trigger with no keys is armed all the time, so it
// keeps the window under the pointer subclassed all the same.
//
// Content hosted in a composition input sink, such as a WinUI XAML island,
// receives its pointer input over a side channel and produces no window message
// at all, so neither hook nor subclass sees the press, and it reaches the
// island, which turns the release into a click. Only input which hasn't been
// routed yet can be taken away from it, so while a trigger's keys are held a
// low level mouse hook swallows the press over composition hosted content,
// recognized by the class of the hosting window, and moves or resizes the
// window itself with SetWindowPos. A trigger with no keys has the process
// which owns the foreground window hold the hook instead, which keeps it to
// one hook rather than one per process; being global, that one serves a drag
// of any window. The cursor shown over such content is
// chosen by the content, on every move it sees, from a thread of its own, so
// nothing set from outside sticks. For the duration of the drag, and ahead of
// it from the end of the drag delay, a small invisible topmost window of the
// hook's thread follows the cursor instead: it receives the moves, and with
// them the right to choose the cursor. Windows
// which deliver the press as a message are left to the paths above and keep
// the system loop, which is of no use here: it retrieves no mouse input while
// the sink owns the contact, so it starts and then tracks nothing. With keys
// to hold, the hook exists only while they are, keeping it out of the input
// path the rest of the time.
//
// The hook is global, and the island of a window which isn't focused belongs to
// a process which never saw the keys go down and so has no hook of its own. The
// process which does hold the hook therefore handles any window, not just its
// own, and moves it asynchronously since it doesn't own it.
//
// A root window is dragged only if its thread runs the mod's hooks: a request
// to it would otherwise go unserved, and a program the mod isn't loaded in,
// e.g. one excluded from it, keeps its input as is, as it does for a press in
// its own windows, which no hook sees. Each hooked thread marks its top level
// windows with a window property, readable from any thread and process, and
// the low level hook checks it like the message paths do. That hook is the
// focused thread's, so while a program without the mod is focused there is
// none, and composition hosted content elsewhere gets the press as a click,
// which moves the focus there.
//
// A swallowed press never reaches the input queue, so as far as the system is
// concerned Alt, when it's among the keys, was tapped on its own, and
// DefWindowProc turns the release into SC_KEYMENU, activating the menu bar.
// The Alt release which ends such a drag is therefore taken as well. A
// swallowed press which isn't followed by a drag is replayed on the release
// as a click, like a press taken for the loop.
//
// The Start menu, which a Win key tapped on its own opens, is put off by
// another key alone, not by a press, swallowed or not. The Win release ending
// a drag is therefore masked by a low level keyboard hook of the thread
// running the drag, the way AutoHotkey masks menu keys: it's swallowed and
// sent again behind a tap of an unassigned key.



enum : DWORD {
    kModifierCtrl = 1 << 0,
    kModifierAlt = 1 << 1,
    kModifierShift = 1 << 2,
    kModifierWin = 1 << 3,
};

// The button, as its virtual key, the modifier keys to hold with it, and the
// time to hold it for before the drag starts.
struct TriggerSettings {
    std::atomic<int> button;
    std::atomic<DWORD> modifiers;
    std::atomic<int> delay;
};

enum class WindowAction : int {
    None,
    Menu,
    Maximize,
    Minimize,
    Close,
    Topmost,
    Lower,
    Center,
    SideSnap,
};

struct KeyBinding {
    std::atomic<int> key;
    std::atomic<DWORD> modifiers;
};

constexpr std::array<WindowAction, 8> kHotkeyActions{
    WindowAction::Maximize, WindowAction::Minimize, WindowAction::Close,
    WindowAction::Menu, WindowAction::Topmost, WindowAction::Lower,
    WindowAction::Center, WindowAction::SideSnap};
constexpr std::array<PCWSTR, 8> kHotkeyNames{
    L"hotkeyMaximize", L"hotkeyMinimize", L"hotkeyClose", L"hotkeyMenu",
    L"hotkeyTopmost", L"hotkeyLower", L"hotkeyCenter", L"hotkeySideSnap"};

struct {
    TriggerSettings moveTrigger;
    TriggerSettings sizeTrigger;
    std::atomic<bool> dragWindowsWithoutTitleBar;
    std::atomic<bool> explorerTitleStripDrag;
    std::atomic<bool> sizeWindowsWithoutSizingBorder;
    std::atomic<WindowAction> middleAction;
    std::atomic<WindowAction> rightClickAction;
    std::atomic<WindowAction> x1Action;
    std::atomic<WindowAction> x2Action;
    std::atomic<WindowAction> leftDoubleAction;
    std::atomic<WindowAction> middleDoubleAction;
    std::atomic<WindowAction> rightDoubleAction;
    std::array<KeyBinding, kHotkeyActions.size()> hotkeys;
} g_settings;

std::atomic<bool> g_uninitializing;
std::atomic<int> g_hookRefCount;

// A drag is identified by the system command it amounts to: SC_MOVE |
// HTCAPTION for a move, SC_SIZE | WMSZ_* for a resize from that edge or corner.
bool IsSizeCommand(UINT command) {
    return (command & 0xFFF0) == SC_SIZE;
}

const TriggerSettings& TriggerOfCommand(UINT command) {
    return IsSizeCommand(command) ? g_settings.sizeTrigger
                                  : g_settings.moveTrigger;
}

UINT g_sizeMoveRequestMessage =
    RegisterWindowMessage(L"Windhawk_SizeMoveRequest_" WH_MOD_ID);
UINT g_unsubclassRegisteredMessage =
    RegisterWindowMessage(L"Windhawk_Unsubclass_" WH_MOD_ID);
UINT g_replayPressMessage =
    RegisterWindowMessage(L"Windhawk_ReplayPress_" WH_MOD_ID);
UINT g_dragUpdateMessage =
    RegisterWindowMessage(L"Windhawk_DragUpdate_" WH_MOD_ID);
// The helper asks an app's own copy of the mod to pin its window: Windows
// often ignores a pin from another process that isn't in the foreground.
UINT g_pinRequestMessage =
    RegisterWindowMessage(L"Windhawk_PinRequest_" WH_MOD_ID);

thread_local bool g_threadHooksAttempted;
thread_local HHOOK g_getMessageHook;
thread_local HHOOK g_callWndProcHook;
std::mutex g_allThreadHooksMutex;
std::unordered_set<HHOOK> g_allThreadHooks;

// The drag this thread was asked to run, from the request's retrieval until
// the loop is seen to be over. It's dragged once the loop got going: a move
// past the threshold wait the caption drag holds the capture through, a resize
// once the pointer leaves the drag threshold, the size loop having no such
// wait. Until then a release is a click.
thread_local struct {
    UINT command;
    int button;
    HWND hWnd;
    POINT startPt;
    bool dragged;
    bool fromHook;
} g_loop;

// A press taken from this thread's queue for as long as the drag delay runs.
thread_local struct {
    UINT_PTR timerId;
    MSG downMsg;
    int button;
    UINT command;
    HWND hRootWnd;
} g_delayedPress;

// The button of the last press taken from this thread's queue, whose release
// is taken as well unless a loop consumes it.
thread_local int g_takenPressButton;
thread_local int g_actionButton;
thread_local int g_actionKey;

// Set while the press of a replayed click is posted and yet to be retrieved,
// so that it's passed on rather than taken again.
thread_local bool g_replayedPressPending;

thread_local HWND g_lastSubclassedWnd;
std::mutex g_subclassedWindowsMutex;
std::unordered_set<HWND> g_subclassedWindows;

// The pointer contact being routed to DefWindowProc, if any.
thread_local HWND g_contactWnd;
thread_local UINT g_contactPointerId;
thread_local int g_contactButton;

// The low level mouse hook, installed only while a trigger's keys are held, by
// whichever thread retrieves the press. The mutex guards the handle and the
// thread, and keeps an installation from slipping past the removal at uninit.
// It's taken from DllMain as well, under the loader lock, so nothing may call
// into the loader while holding it, which would invert the two.
std::mutex g_lowLevelMouseHookMutex;
HHOOK g_lowLevelMouseHook;
DWORD g_lowLevelMouseHookThreadId;
// The hook is installed on a thread of the mod's own, one per process. A low
// level hook is called on the thread which installed it, and the thread which
// retrieves the trigger's keys is the foreground window's: busy painting the
// window being dragged, it held up every move of the pointer on the way to the
// system, and the cursor trailed a drag which the system's loop ran smoothly.
HANDLE g_lowLevelMouseHookThread;
DWORD g_lowLevelMouseHookOwnThreadId;
DPI_AWARENESS_CONTEXT g_lowLevelMouseHookDpiContext =
    DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2;
constexpr UINT kInstallLowLevelMouseHookMessage = WM_APP + 1;
// Set when a press was swallowed during the current hold with Alt held.
std::atomic<bool> g_swallowedPress;

// Marks the input sent by the mod, which the hooks let through.
constexpr ULONG_PTR kOwnInputExtraInfo = 0x57484152;

// The low level keyboard hook masking the Win release which ends a drag,
// installed by the thread running the drag and removed with that release. The
// mutex carries the same rule as the one above.
std::mutex g_winKeyMaskHookMutex;
HHOOK g_winKeyMaskHook;
DWORD g_winKeyMaskHookThreadId;

// Unassigned, the key AutoHotkey masks menu keys with (A_MenuMaskKey).
constexpr WORD kMenuMaskKey = 0xE8;

// The press the low level hook swallowed, until its release: the root window
// a drag takes hold of and the drag it amounts to, a candidate for one until
// the pointer leaves the drag threshold with the delay over. Touched only on
// the hook's thread, which its callback runs on, and reset with the hook
// gone: at uninit once the callbacks are waited out, and at the start of a
// hold.
HWND g_llRootWnd;
UINT g_llCommand;
int g_llButton;
POINT g_llDownPt;
DWORD g_llDownTime;
bool g_llDragging;
// Where the drag started: a move takes its grab from it, a resize measures
// from it.
POINT g_llDragStartPt;
// Where a move holds the window relative to its origin.
POINT g_llDragGrab;
// The window's rect when a resize started.
RECT g_llDragStartRect;
// Whether the work a drag starts with has been done. The callback decides
// that a drag is on, the message loop then sets it up.
bool g_llDragSetUp;
// Where the drag last saw the pointer, and whether an update for it is queued.
POINT g_llDragPt;
bool g_llDragUpdatePosted;
HWND g_llDragOverlayWnd;
// Times the drag delay of a candidate for the cursor at its end. The drag
// itself waits for a move, timed from the press. A timer is its thread's, and
// only that thread can kill it.
thread_local UINT_PTR g_llDelayTimerId;

constexpr WCHAR kDragOverlayClassName[] = L"Windhawk_AltDragOverlay_" WH_MOD_ID;

// Sized for the cursor alone: a window covering a monitor counts as a full
// screen one, which the taskbar and notifications make way for.
constexpr int kDragOverlaySize = 32;

// The monitor the pointer was last seen on, in physical coordinates and in
// those of this thread, which are scaled per monitor unless the thread is per
// monitor DPI aware.
struct {
    RECT physicalRect;
    RECT logicalRect;
} g_llMonitor;

void ReplayPress(int button, bool asClick);
void MaskWinKeyReleaseIfNeeded(UINT command);
void OnLowLevelDragDelayElapsed();
void OnDragUpdate();
void RemoveLowLevelMouseHook();
void InstallLowLevelMouseHookIfNeeded();
void RemoveLowLevelMouseHookIfIdle();

auto HookRefCountScope() {
    g_hookRefCount++;
    return std::unique_ptr<decltype(g_hookRefCount),
                           void (*)(decltype(g_hookRefCount)*)>{
        &g_hookRefCount, [](auto hookRefCount) { (*hookRefCount)--; }};
}

void TakeMessage(MSG* msg) {
    msg->message = WM_NULL;
    msg->wParam = 0;
    msg->lParam = 0;
}

void SetSyncKeyState(int vk, bool down) {
    BYTE keyState[256];
    if (GetKeyboardState(keyState)) {
        if (down) {
            keyState[vk] |= 0x80;
        } else {
            keyState[vk] &= ~0x80;
        }
        SetKeyboardState(keyState);
    }
}

// The modifier keys held, from GetKeyState or GetAsyncKeyState.
DWORD HeldModifiers(SHORT(WINAPI* getKeyState)(int)) {
    DWORD held = 0;
    if (getKeyState(VK_CONTROL) < 0) {
        held |= kModifierCtrl;
    }
    if (getKeyState(VK_MENU) < 0) {
        held |= kModifierAlt;
    }
    if (getKeyState(VK_SHIFT) < 0) {
        held |= kModifierShift;
    }
    if (getKeyState(VK_LWIN) < 0 || getKeyState(VK_RWIN) < 0) {
        held |= kModifierWin;
    }
    return held;
}

DWORD ModifierOfKey(WPARAM vk) {
    switch (vk) {
        case VK_CONTROL:
            return kModifierCtrl;
        case VK_MENU:
            return kModifierAlt;
        case VK_SHIFT:
            return kModifierShift;
        case VK_LWIN:
        case VK_RWIN:
            return kModifierWin;
    }

    return 0;
}

// Other keys held along with the trigger's don't get in the way, so that AltGr,
// which is Ctrl+Alt, counts as Alt.
bool IsTriggerHeld(const TriggerSettings& trigger, DWORD held) {
    DWORD modifiers = trigger.modifiers;
    return (held & modifiers) == modifiers;
}

// Whether a trigger's keys are held, for the paths their hold gates. A
// trigger with no keys is never held this way: it's armed all the time, and
// what it needs is kept up for as long as it's configured.
bool IsModifierTriggerHeld(const TriggerSettings& trigger, DWORD held) {
    return trigger.modifiers && IsTriggerHeld(trigger, held);
}

bool IsAnyModifierTriggerHeld(DWORD held) {
    return IsModifierTriggerHeld(g_settings.moveTrigger, held) ||
           IsModifierTriggerHeld(g_settings.sizeTrigger, held);
}

bool IsAnyTriggerKeyless() {
    return !g_settings.moveTrigger.modifiers ||
           !g_settings.sizeTrigger.modifiers;
}

// The low level hook of a keyless trigger is held by the process which owns
// the foreground window, so that one hook is in the input path rather than one
// per process. Activation is what puts it up and takes it down, the way a key
// press and release do for a trigger which has keys.
bool ShouldHoldKeylessHook() {
    if (!IsAnyTriggerKeyless()) {
        return false;
    }

    DWORD processId = 0;
    GetWindowThreadProcessId(GetForegroundWindow(), &processId);
    return processId == GetCurrentProcessId();
}

// Whether this process is File Explorer. Cached: the image of a running
// process never changes.
bool IsExplorerProcess() {
    static bool isExplorer = [] {
        WCHAR path[MAX_PATH];
        DWORD len = GetModuleFileName(nullptr, path, ARRAYSIZE(path));
        if (!len || len >= ARRAYSIZE(path)) {
            return false;
        }
        PCWSTR name = wcsrchr(path, L'\\');
        name = name ? name + 1 : path;
        return _wcsicmp(name, L"explorer.exe") == 0;
    }();
    return isExplorer;
}

// The button of a client or non-client button message, or 0 for any other
// message. An X button is told by the high word of wParam, or of mouseData for
// the messages of the low level hook.
int ButtonOfMessage(UINT message, WORD xButton, bool* down) {
    switch (message) {
        case WM_LBUTTONDOWN:
        case WM_LBUTTONDBLCLK:
        case WM_NCLBUTTONDOWN:
        case WM_NCLBUTTONDBLCLK:
            *down = true;
            return VK_LBUTTON;

        case WM_LBUTTONUP:
        case WM_NCLBUTTONUP:
            *down = false;
            return VK_LBUTTON;

        case WM_RBUTTONDOWN:
        case WM_RBUTTONDBLCLK:
        case WM_NCRBUTTONDOWN:
        case WM_NCRBUTTONDBLCLK:
            *down = true;
            return VK_RBUTTON;

        case WM_RBUTTONUP:
        case WM_NCRBUTTONUP:
            *down = false;
            return VK_RBUTTON;

        case WM_MBUTTONDOWN:
        case WM_MBUTTONDBLCLK:
        case WM_NCMBUTTONDOWN:
        case WM_NCMBUTTONDBLCLK:
            *down = true;
            return VK_MBUTTON;

        case WM_MBUTTONUP:
        case WM_NCMBUTTONUP:
            *down = false;
            return VK_MBUTTON;

        case WM_XBUTTONDOWN:
        case WM_XBUTTONDBLCLK:
        case WM_NCXBUTTONDOWN:
        case WM_NCXBUTTONDBLCLK:
            *down = true;
            break;

        case WM_XBUTTONUP:
        case WM_NCXBUTTONUP:
            *down = false;
            break;

        default:
            return 0;
    }

    switch (xButton) {
        case XBUTTON1:
            return VK_XBUTTON1;
        case XBUTTON2:
            return VK_XBUTTON2;
    }

    return 0;
}

UINT ButtonUpMessageOf(UINT downMessage) {
    switch (downMessage) {
        case WM_LBUTTONDOWN:
        case WM_LBUTTONDBLCLK:
            return WM_LBUTTONUP;
        case WM_NCLBUTTONDOWN:
        case WM_NCLBUTTONDBLCLK:
            return WM_NCLBUTTONUP;
        case WM_RBUTTONDOWN:
        case WM_RBUTTONDBLCLK:
            return WM_RBUTTONUP;
        case WM_NCRBUTTONDOWN:
        case WM_NCRBUTTONDBLCLK:
            return WM_NCRBUTTONUP;
        case WM_MBUTTONDOWN:
        case WM_MBUTTONDBLCLK:
            return WM_MBUTTONUP;
        case WM_NCMBUTTONDOWN:
        case WM_NCMBUTTONDBLCLK:
            return WM_NCMBUTTONUP;
        case WM_XBUTTONDOWN:
        case WM_XBUTTONDBLCLK:
            return WM_XBUTTONUP;
        case WM_NCXBUTTONDOWN:
        case WM_NCXBUTTONDBLCLK:
            return WM_NCXBUTTONUP;
    }

    return 0;
}

// The MK_* flag of the button in the wParam of a client mouse message.
WPARAM ButtonMask(int button) {
    switch (button) {
        case VK_LBUTTON:
            return MK_LBUTTON;
        case VK_RBUTTON:
            return MK_RBUTTON;
        case VK_MBUTTON:
            return MK_MBUTTON;
        case VK_XBUTTON1:
            return MK_XBUTTON1;
        case VK_XBUTTON2:
            return MK_XBUTTON2;
    }

    return 0;
}

bool IsNonClientMessage(UINT message) {
    return message < WM_MOUSEFIRST;
}

bool IsPastDragThreshold(POINT from, POINT to) {
    return abs(to.x - from.x) >= GetSystemMetrics(SM_CXDRAG) ||
           abs(to.y - from.y) >= GetSystemMetrics(SM_CYDRAG);
}

bool IsPointerMessage(UINT message) {
    return message >= WM_NCPOINTERUPDATE && message <= WM_POINTERROUTEDRELEASED;
}

bool IsPointerButtonDown(WPARAM wParam, int button) {
    switch (button) {
        case VK_LBUTTON:
            return IS_POINTER_FIRSTBUTTON_WPARAM(wParam);
        case VK_RBUTTON:
            return IS_POINTER_SECONDBUTTON_WPARAM(wParam);
        case VK_MBUTTON:
            return IS_POINTER_THIRDBUTTON_WPARAM(wParam);
        case VK_XBUTTON1:
            return IS_POINTER_FOURTHBUTTON_WPARAM(wParam);
        case VK_XBUTTON2:
            return IS_POINTER_FIFTHBUTTON_WPARAM(wParam);
    }

    return false;
}

// The button a new contact was made with, or 0 for any other message. The
// mouse is in contact while any of its buttons is down, so at that point it's
// the only one.
int ButtonOfPointerDownMessage(UINT message, WPARAM wParam) {
    switch (message) {
        case WM_POINTERDOWN:
        case WM_NCPOINTERDOWN:
            for (int button : {VK_LBUTTON, VK_RBUTTON, VK_MBUTTON, VK_XBUTTON1,
                               VK_XBUTTON2}) {
                if (IsPointerButtonDown(wParam, button)) {
                    return button;
                }
            }
            break;
    }

    return 0;
}

bool IsPointerContactEndMessage(UINT message) {
    switch (message) {
        case WM_POINTERUP:
        case WM_NCPOINTERUP:
        case WM_POINTERCAPTURECHANGED:
            return true;
    }

    return false;
}

// A message showing that a contact is no longer this window's: the pointer
// left, e.g. captured by the move loop, or the button is up already, the
// release having gone elsewhere.
bool IsPointerContactGoneMessage(UINT message, WPARAM wParam, int button) {
    switch (message) {
        case WM_POINTERLEAVE:
            return true;

        case WM_POINTERUPDATE:
        case WM_NCPOINTERUPDATE:
            return !IsPointerButtonDown(wParam, button);
    }

    return false;
}

// Set on the top level windows of a thread which runs the mod's hooks.
constexpr WCHAR kHookedWindowProp[] = L"Windhawk_Hooked_" WH_MOD_ID;

void MarkHookedWindow(HWND hWnd) {
    if (!SetProp(hWnd, kHookedWindowProp, (HANDLE)1)) {
        Wh_Log(L"SetProp error for %08X: %u", (DWORD)(ULONG_PTR)hWnd,
               GetLastError());
    }
}

// This thread's hooks are in place, another thread's are told by the mark.
bool IsRootWindowHooked(HWND hRootWnd) {
    return GetWindowThreadProcessId(hRootWnd, nullptr) ==
               GetCurrentThreadId() ||
           GetProp(hRootWnd, kHookedWindowProp);
}

// The engine never injects mods into Windhawk's own interface, so its window
// carries no hooks of ours. The actions only post to the window's thread
// (ShowWindowAsync) rather than replaying input, so they are safe there, and
// the interface is the window this mod gets used on the most.
bool IsWindhawkUiWindow(HWND hWnd) {
    WCHAR cls[128]{};
    if (GetClassNameW(hWnd, cls, ARRAYSIZE(cls)) &&
        wcscmp(cls, L"AIVoiceTypingSettings_local@seamless-dictate") == 0) return true;
    static std::atomic<DWORD> s_pid{0};
    static std::atomic<bool> s_isUi{false};
    DWORD pid = GetWindowThreadProcessId(hWnd, nullptr);
    if (pid != 0 && pid == s_pid.load(std::memory_order_relaxed)) {
        return s_isUi.load(std::memory_order_relaxed);
    }

    bool isUi = false;
    if (HANDLE hProcess =
            OpenProcess(PROCESS_QUERY_LIMITED_INFORMATION, FALSE, pid)) {
        WCHAR path[MAX_PATH];
        DWORD size = ARRAYSIZE(path);
        if (QueryFullProcessImageNameW(hProcess, 0, path, &size)) {
            for (DWORD i = 0; i < size; ++i) {
                path[i] = static_cast<WCHAR>(towlower(path[i]));
            }
            path[size < MAX_PATH ? size : MAX_PATH - 1] = L'\0';
            isUi = wcsstr(path, L"\\windhawk\\ui\\") != nullptr;
        }
        CloseHandle(hProcess);
    }

    s_pid.store(pid, std::memory_order_relaxed);
    s_isUi.store(isUi, std::memory_order_relaxed);
    return isUi;
}

bool IsExcludedRootWindow(HWND hRootWnd) {
    if (!hRootWnd || !IsWindow(hRootWnd)) return true;
    std::wstring exeName;
    if (g_globalInput) {
        DWORD pid = 0;
        GetWindowThreadProcessId(hRootWnd, &pid);
        if (pid == GetCurrentProcessId()) return true;
        HANDLE process = OpenProcess(PROCESS_QUERY_LIMITED_INFORMATION, FALSE, pid);
        if (!process) return true;
        WCHAR path[32768];
        DWORD size = ARRAYSIZE(path);
        bool queried = QueryFullProcessImageNameW(process, 0, path, &size);
        CloseHandle(process);
        if (!queried) return true;
        PCWSTR name = PathFindFileNameW(path);
        exeName = name;
        size_t begin = 0;
        while (begin < g_globalExclusions.size()) {
            size_t end = g_globalExclusions.find(L'|', begin);
            std::wstring pattern = g_globalExclusions.substr(begin, end - begin);
            if (!pattern.empty() && (PathMatchSpecW(name, pattern.c_str()) ||
                                     PathMatchSpecW(path, pattern.c_str()))) return true;
            if (end == std::wstring::npos) break;
            begin = end + 1;
        }
    } else if (!IsRootWindowHooked(hRootWnd) && !IsWindhawkUiWindow(hRootWnd)) {
        return true;
    } else {
        static const std::wstring ownExe = [] {
            WCHAR own[MAX_PATH]{};
            GetModuleFileNameW(nullptr, own, ARRAYSIZE(own));
            return std::wstring(PathFindFileNameW(own));
        }();
        DWORD pid = 0;
        GetWindowThreadProcessId(hRootWnd, &pid);
        if (pid == GetCurrentProcessId()) {
            exeName = ownExe;
        } else if (HANDLE process = OpenProcess(PROCESS_QUERY_LIMITED_INFORMATION, FALSE, pid)) {
            WCHAR path[MAX_PATH]{};
            DWORD size = ARRAYSIZE(path);
            if (QueryFullProcessImageNameW(process, 0, path, &size)) exeName = PathFindFileNameW(path);
            CloseHandle(process);
        }
    }

    WCHAR className[64];
    if (!GetClassName(hRootWnd, className, ARRAYSIZE(className))) {
        return true;
    }

    // The taskbar, the desktop, and the mod's own drag overlay and popup.
    if (_wcsicmp(className, L"Shell_TrayWnd") == 0 ||
        _wcsicmp(className, L"Shell_SecondaryTrayWnd") == 0 ||
        _wcsicmp(className, L"Progman") == 0 ||
        _wcsicmp(className, L"WorkerW") == 0 ||
        _wcsicmp(className, L"SeamlessWM_Osd") == 0 ||
        _wcsicmp(className, kDragOverlayClassName) == 0) {
        return true;
    }
    return snapCommander::IsIgnoredWindow(hRootWnd, exeName.c_str());
}

bool CanMoveRootWindow(HWND hRootWnd) {
    if (IsExcludedRootWindow(hRootWnd)) {
        return false;
    }

    if (g_settings.dragWindowsWithoutTitleBar) {
        return true;
    }

    LONG style = GetWindowLong(hRootWnd, GWL_STYLE);
    return (style & WS_CAPTION) == WS_CAPTION;
}

bool CanSizeRootWindow(HWND hRootWnd) {
    if (IsExcludedRootWindow(hRootWnd)) {
        return false;
    }

    LONG style = GetWindowLong(hRootWnd, GWL_STYLE);
    if (style & WS_MAXIMIZE) {
        return false;
    }

    return g_settings.sizeWindowsWithoutSizingBorder ||
           (style & WS_THICKFRAME);
}

bool CanActOnRootWindow(HWND hWnd) {
    return hWnd && GetAncestor(hWnd, GA_ROOT) == hWnd &&
           !IsExcludedRootWindow(hWnd) &&
           (GetWindowLong(hWnd, GWL_STYLE) & WS_CHILD) == 0;
}

WindowAction ActionFromSetting(PCWSTR value) {
    if (_wcsicmp(value, L"menu") == 0) return WindowAction::Menu;
    if (_wcsicmp(value, L"maximize") == 0) return WindowAction::Maximize;
    if (_wcsicmp(value, L"minimize") == 0) return WindowAction::Minimize;
    if (_wcsicmp(value, L"close") == 0) return WindowAction::Close;
    if (_wcsicmp(value, L"topmost") == 0) return WindowAction::Topmost;
    if (_wcsicmp(value, L"lower") == 0) return WindowAction::Lower;
    if (_wcsicmp(value, L"center") == 0) return WindowAction::Center;
    if (_wcsicmp(value, L"sideSnap") == 0) return WindowAction::SideSnap;
    return WindowAction::None;
}

void RunWindowMenu(HWND hWnd, HWND owner, POINT pt);
bool RunWindowActionNow(HWND hWnd, WindowAction action, POINT pt);

bool RunWindowAction(HWND hWnd, WindowAction action, POINT pt) {
    if (action == WindowAction::None || swm::IsPaused() ||
        !CanActOnRootWindow(hWnd)) return false;

    if (action == WindowAction::Menu) {
        // The menu loop is modal, so it gets a thread of its own: on the
        // input thread it would hold up the mouse and drop queued work.
        struct MenuRequest { HWND hWnd; POINT pt; };
        auto request = new MenuRequest{hWnd, pt};
        HANDLE thread = CreateThread(nullptr, 0, [](void* p) WINAPI -> DWORD {
            std::unique_ptr<MenuRequest> r((MenuRequest*)p);
            HWND owner = CreateWindowEx(WS_EX_TOOLWINDOW, L"STATIC", L"", WS_POPUP,
                                        r->pt.x, r->pt.y, 0, 0, nullptr, nullptr,
                                        nullptr, nullptr);
            if (!owner) return 0;
            SetForegroundWindow(owner);
            RunWindowMenu(r->hWnd, owner, r->pt);
            DestroyWindow(owner);
            return 0;
        }, request, 0, nullptr);
        if (!thread) { delete request; return false; }
        CloseHandle(thread);
        return true;
    }
    return RunWindowActionNow(hWnd, action, pt);
}

void RunWindowMenu(HWND hWnd, HWND owner, POINT pt) {
    {
        HMENU menu = CreatePopupMenu();
        if (!menu) return;
        constexpr std::array<std::pair<WindowAction, PCWSTR>, 7> items{{
            {WindowAction::Maximize, L"Maximize / restore"},
            {WindowAction::Minimize, L"Minimize"},
            {WindowAction::Topmost, L"Always on top"},
            {WindowAction::Lower, L"Lower"},
            {WindowAction::Center, L"Center"},
            {WindowAction::SideSnap, L"Snap to side"},
            {WindowAction::Close, L"Close"},
        }};
        for (size_t i = 0; i < items.size(); i++) {
            if (items[i].first == WindowAction::Close) AppendMenu(menu, MF_SEPARATOR, 0, nullptr);
            UINT flags = MF_STRING;
            if (items[i].first == WindowAction::Topmost &&
                (GetWindowLongPtr(hWnd, GWL_EXSTYLE) & WS_EX_TOPMOST)) flags |= MF_CHECKED;
            AppendMenu(menu, flags, i + 1, items[i].second);
        }
        int selected = TrackPopupMenuEx(menu, TPM_RETURNCMD | TPM_RIGHTBUTTON,
                                        pt.x, pt.y, owner, nullptr);
        DestroyMenu(menu);
        if (selected > 0 && selected <= (int)items.size() &&
            CanActOnRootWindow(hWnd))
            RunWindowActionNow(hWnd, items[selected - 1].first, pt);
    }
}

bool RunWindowActionNow(HWND hWnd, WindowAction action, POINT pt) {
    if (action == WindowAction::Maximize) {
        ShowWindowAsync(hWnd, IsZoomed(hWnd) ? SW_RESTORE : SW_MAXIMIZE);
    } else if (action == WindowAction::Minimize) {
        ShowWindowAsync(hWnd, SW_MINIMIZE);
    } else if (action == WindowAction::Close) {
        PostMessage(hWnd, WM_CLOSE, 0, 0);
    } else if (action == WindowAction::Topmost) {
        HWND order = (GetWindowLongPtr(hWnd, GWL_EXSTYLE) & WS_EX_TOPMOST)
                         ? HWND_NOTOPMOST : HWND_TOPMOST;
        SetWindowPos(hWnd, order, 0, 0, 0, 0,
                     SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE | SWP_ASYNCWINDOWPOS);
    } else if (action == WindowAction::Lower) {
        SetWindowPos(hWnd, HWND_BOTTOM, 0, 0, 0, 0,
                     SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE | SWP_ASYNCWINDOWPOS);
    } else if (action == WindowAction::Center || action == WindowAction::SideSnap) {
        MONITORINFO monitor{.cbSize = sizeof(monitor)};
        RECT rc;
        if (!GetMonitorInfo(MonitorFromWindow(hWnd, MONITOR_DEFAULTTONEAREST),
                            &monitor) || !GetWindowRect(hWnd, &rc)) return false;
        if (IsZoomed(hWnd)) {
            // The restore lands later, so size by the restored rectangle.
            WINDOWPLACEMENT wp{sizeof(wp)};
            if (GetWindowPlacement(hWnd, &wp)) rc = wp.rcNormalPosition;
            ShowWindowAsync(hWnd, SW_RESTORE);
        }
        const RECT& work = monitor.rcWork;
        int width = rc.right - rc.left;
        int height = rc.bottom - rc.top;
        if (action == WindowAction::Center) {
            SetWindowPos(hWnd, nullptr,
                         work.left + ((work.right - work.left) - width) / 2,
                         work.top + ((work.bottom - work.top) - height) / 2,
                         0, 0, SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE | SWP_ASYNCWINDOWPOS);
        } else {
            int half = (work.right - work.left) / 2;
            bool right = pt.x >= work.left + half;
            SetWindowPos(hWnd, nullptr, right ? work.left + half : work.left,
                         work.top, right ? work.right - work.left - half : half,
                         work.bottom - work.top, SWP_NOZORDER | SWP_NOACTIVATE | SWP_ASYNCWINDOWPOS);
        }
    }
    return true;
}

WindowAction MouseActionForMessage(UINT message, int button) {
    bool dbl = message == WM_LBUTTONDBLCLK || message == WM_NCLBUTTONDBLCLK ||
               message == WM_RBUTTONDBLCLK || message == WM_NCRBUTTONDBLCLK ||
               message == WM_MBUTTONDBLCLK || message == WM_NCMBUTTONDBLCLK ||
               message == WM_XBUTTONDBLCLK || message == WM_NCXBUTTONDBLCLK;
    if (dbl) {
        if (button == VK_LBUTTON) return g_settings.leftDoubleAction;
        if (button == VK_MBUTTON) return g_settings.middleDoubleAction;
        if (button == VK_RBUTTON) return g_settings.rightDoubleAction;
    } else {
        if (button == VK_MBUTTON) return g_settings.middleAction;
        if (button == VK_XBUTTON1) return g_settings.x1Action;
        if (button == VK_XBUTTON2) return g_settings.x2Action;
    }
    return WindowAction::None;
}

bool HandleActionMouseMessage(MSG* msg, int button, bool down) {
    // A press of the same button means its release was never seen here.
    if (down && button == g_actionButton) g_actionButton = 0;
    if (!down && button == g_actionButton) {
        g_actionButton = 0;
        TakeMessage(msg);
        return true;
    }
    if (!down || !button || !(HeldModifiers(GetKeyState) & kModifierAlt)) return false;
    WindowAction action = MouseActionForMessage(msg->message, button);
    if (action == WindowAction::None && button == VK_RBUTTON &&
        g_settings.rightClickAction != WindowAction::None) {
        HWND root = GetAncestor(msg->hwnd, GA_ROOT);
        if (root && IsZoomed(root)) action = g_settings.rightClickAction;
    }
    if (action == WindowAction::None) return false;
    HWND root = GetAncestor(msg->hwnd, GA_ROOT);
    if (!RunWindowAction(root, action, msg->pt)) return false;
    g_actionButton = button;
    g_swallowedPress = GetAsyncKeyState(VK_MENU) < 0;
    TakeMessage(msg);
    return true;
}

bool HandleActionKeyMessage(MSG* msg) {
    bool down = msg->message == WM_KEYDOWN || msg->message == WM_SYSKEYDOWN;
    if (!down && msg->wParam == (WPARAM)g_actionKey) {
        g_actionKey = 0;
        TakeMessage(msg);
        return true;
    }
    if (!down || msg->wParam == 0) return false;
    if (g_actionKey == (int)msg->wParam) {
        // Only auto-repeats belong to the press that ran the action; a fresh
        // press means the release went elsewhere.
        if (msg->lParam & (1 << 30)) {
            TakeMessage(msg);
            return true;
        }
        g_actionKey = 0;
    }
    DWORD modifiers = HeldModifiers(GetKeyState);
    for (size_t i = 0; i < g_settings.hotkeys.size(); i++) {
        if (g_settings.hotkeys[i].key == (int)msg->wParam &&
            g_settings.hotkeys[i].modifiers == modifiers) {
            HWND root = GetAncestor(msg->hwnd, GA_ROOT);
            if (!root || !RunWindowAction(root, kHotkeyActions[i], msg->pt)) return false;
            g_actionKey = (int)msg->wParam;
            g_swallowedPress = GetAsyncKeyState(VK_MENU) < 0;
            TakeMessage(msg);
            return true;
        }
    }
    return false;
}

// The edge or corner a resize which grabs the window at pt takes hold of, from
// a 3x3 grid over the window. The center cell resizes from the bottom right
// corner.
UINT SizeCommandAtPoint(HWND hRootWnd, POINT pt) {
    RECT rc;
    if (!GetWindowRect(hRootWnd, &rc) || IsRectEmpty(&rc)) {
        return SC_SIZE | WMSZ_BOTTOMRIGHT;
    }

    int col =
        std::clamp<int>((pt.x - rc.left) * 3 / (rc.right - rc.left), 0, 2);
    int row = std::clamp<int>((pt.y - rc.top) * 3 / (rc.bottom - rc.top), 0, 2);

    static constexpr UINT kEdges[3][3] = {
        {WMSZ_TOPLEFT, WMSZ_TOP, WMSZ_TOPRIGHT},
        {WMSZ_LEFT, WMSZ_BOTTOMRIGHT, WMSZ_RIGHT},
        {WMSZ_BOTTOMLEFT, WMSZ_BOTTOM, WMSZ_BOTTOMRIGHT},
    };
    return SC_SIZE | kEdges[row][col];
}

// A press inside the File Explorer title strip band, where the styler's
// full-width tab pill swallows every press as a tab grab. The strip is the
// top band of the Explorer XAML island child; the caption button scaffolding
// at the right end stays clickable. The logical point is measured against a
// physical window rect, the way SizeCommandAtPoint already does; this build
// targets a 100% scale display.
bool IsExplorerTitleStripPress(HWND hRootWnd, POINT pt) {
    WCHAR className[64];
    if (!GetClassName(hRootWnd, className, ARRAYSIZE(className)) ||
        _wcsicmp(className, L"CabinetWClass") != 0) {
        return false;
    }

    HWND island = FindWindowExW(hRootWnd, nullptr,
                                L"Microsoft.UI.Content.DesktopChildSiteBridge",
                                nullptr);
    if (!island) {
        return false;
    }

    RECT rc;
    if (!GetWindowRect(island, &rc)) {
        return false;
    }

    int stripHeight = MulDiv(36, GetDpiForWindow(hRootWnd), 96);
    if (pt.y < rc.top || pt.y >= rc.top + stripHeight) {
        return false;
    }

    // The caption buttons live in their own child window; presses there keep
    // doing their job.
    HWND scaffolding = FindWindowExW(
        hRootWnd, nullptr, L"TITLE_BAR_SCAFFOLDING_WINDOW_CLASS", nullptr);
    if (scaffolding && GetWindowRect(scaffolding, &rc) && PtInRect(&rc, pt)) {
        return false;
    }

    return true;
}

// The drag a press of the button starts, given the modifier keys held, or 0.
// When the press fits both triggers, the one with more keys is the closer fit.
UINT DragCommandForPress(int button, DWORD held, HWND hRootWnd, POINT pt) {
    if (swm::IsPaused()) return 0;
    bool move = button == g_settings.moveTrigger.button &&
                IsTriggerHeld(g_settings.moveTrigger, held) &&
                CanMoveRootWindow(hRootWnd);
    bool size = button == g_settings.sizeTrigger.button &&
                IsTriggerHeld(g_settings.sizeTrigger, held) &&
                CanSizeRootWindow(hRootWnd);
    if (move && size &&
        std::popcount<DWORD>(g_settings.sizeTrigger.modifiers) >
            std::popcount<DWORD>(g_settings.moveTrigger.modifiers)) {
        move = false;
    }

    if (move) {
        return SC_MOVE | HTCAPTION;
    }

    if (size) {
        return SizeCommandAtPoint(hRootWnd, pt);
    }

    return 0;
}

PCWSTR CursorOfCommand(UINT command) {
    switch (command) {
        case SC_SIZE | WMSZ_LEFT:
        case SC_SIZE | WMSZ_RIGHT:
            return IDC_SIZEWE;
        case SC_SIZE | WMSZ_TOP:
        case SC_SIZE | WMSZ_BOTTOM:
            return IDC_SIZENS;
        case SC_SIZE | WMSZ_TOPLEFT:
        case SC_SIZE | WMSZ_BOTTOMRIGHT:
            return IDC_SIZENWSE;
        case SC_SIZE | WMSZ_TOPRIGHT:
        case SC_SIZE | WMSZ_BOTTOMLEFT:
            return IDC_SIZENESW;
    }

    return IDC_SIZEALL;
}

PCWSTR NameOfCommand(UINT command) {
    return IsSizeCommand(command) ? L"resize" : L"move";
}

// Windows which host their content in a composition input sink, such as a WinUI
// XAML island. Their pointer input never becomes a window message.
bool IsCompositionHostedWindow(HWND hWnd) {
    WCHAR className[64];
    if (!GetClassName(hWnd, className, ARRAYSIZE(className))) {
        return false;
    }

    return _wcsnicmp(className, L"Microsoft.UI.Content.",
                     ARRAYSIZE(L"Microsoft.UI.Content.") - 1) == 0 ||
           _wcsnicmp(className, L"Windows.UI.Composition.",
                     ARRAYSIZE(L"Windows.UI.Composition.") - 1) == 0 ||
           _wcsnicmp(className, L"Windows.UI.Input.InputSite.",
                     ARRAYSIZE(L"Windows.UI.Input.InputSite.") - 1) == 0 ||
           _wcsicmp(className, L"InputSiteWindowClass") == 0;
}

// Found by geometry alone, from the desktop window down. WindowFromPoint sends
// WM_NCHITTEST to windows of other threads, and from the low level hook a
// program which stopped responding a moment ago would hold up the mouse
// system wide. An island host commonly answers that message with HTTRANSPARENT
// anyway, to do its own hit testing, which would stop the lookup at the host.
// What geometry misses is per pixel transparency of layered windows, behind
// which nothing is found.
HWND CompositionHostedWindowFromPoint(POINT pt) {
    HWND hWnd = GetDesktopWindow();
    for (int depth = 0; depth < 9; depth++) {
        POINT clientPt = pt;
        if (!ScreenToClient(hWnd, &clientPt)) {
            break;
        }

        HWND hChildWnd = ChildWindowFromPointEx(
            hWnd, clientPt,
            CWP_SKIPINVISIBLE | CWP_SKIPDISABLED | CWP_SKIPTRANSPARENT);
        if (!hChildWnd || hChildWnd == hWnd) {
            break;
        }

        hWnd = hChildWnd;
        if (IsCompositionHostedWindow(hWnd)) {
            return hWnd;
        }
    }

    return g_globalInput && hWnd != GetDesktopWindow() ? hWnd : nullptr;
}

// Whether the system size/move loop is running on this thread.
bool IsInMoveLoop() {
    GUITHREADINFO gti{.cbSize = sizeof(gti)};
    return GetGUIThreadInfo(GetCurrentThreadId(), &gti) &&
           (gti.flags & GUI_INMOVESIZE);
}

bool BeginSdlDrag(HWND window, UINT command, int button, POINT point);
bool HandleSdlDragMessage(MSG* msg);

// Posted messages are retrieved before input, so a button release that's
// already queued is seen by the loop rather than by the program.
// Marks the button of a request for a press a low level hook took.
constexpr int kTakenInHookFlag = 0x8000;

bool PostSizeMoveRequest(HWND hRootWnd, UINT command, int button, POINT pt) {
    if (!PostMessage(hRootWnd, g_sizeMoveRequestMessage,
                     MAKEWPARAM(command, button), MAKELPARAM(pt.x, pt.y))) {
        Wh_Log(L"PostMessage error: %u", GetLastError());
        return false;
    }

    return true;
}

// A request carries the command, the button and the window from another
// process, and the command is handed to DefWindowProc, so each is held to
// what the mod itself asks for. The filter which lets the message through
// from any integrity level is meant for a drag and for nothing else: any
// other command, SC_CLOSE or one of the program's own among them, would
// otherwise be the sender's to send.
bool IsRequestAcceptable(UINT command, int button, HWND hRootWnd) {
    if (!ButtonMask(button) || GetAncestor(hRootWnd, GA_ROOT) != hRootWnd) {
        return false;
    }

    if (command == (SC_MOVE | HTCAPTION)) {
        return CanMoveRootWindow(hRootWnd);
    }

    UINT edge = command & 0xF;
    return IsSizeCommand(command) && edge >= WMSZ_LEFT &&
           edge <= WMSZ_BOTTOMRIGHT && CanSizeRootWindow(hRootWnd);
}

// Turns a request retrieved by the root window's thread into the system
// command. The loop only starts if this thread's synchronized state has the
// left button down: it isn't when the press was retrieved by another thread,
// and it's the left button which counts whichever button is really held.
void OnSizeMoveRequestRemoved(MSG* msg) {
    UINT command = LOWORD(msg->wParam);
    int button = HIWORD(msg->wParam) & ~kTakenInHookFlag;
    bool takenInHook = HIWORD(msg->wParam) & kTakenInHookFlag;

    if (!IsRequestAcceptable(command, button, msg->hwnd)) {
        Wh_Log(L"Dropping the request %04X %02X for %08X", command, button,
               (DWORD)(ULONG_PTR)msg->hwnd);
        TakeMessage(msg);
        return;
    }

    // A low level hook passes its press on and posts the request ahead of it,
    // so the request can arrive before the system has recorded the press.
    if (takenInHook) {
        for (int i = 0; i < 100 && GetAsyncKeyState(button) >= 0; i++) {
            Sleep(1);
        }
    }

    if (GetAsyncKeyState(button) >= 0) {
        // Released already, a loop would stick to the cursor, and short of a
        // held button nothing backs the request.
        Wh_Log(L"Request to %s %08X, button already released",
               NameOfCommand(command), (DWORD)(ULONG_PTR)msg->hwnd);
        TakeMessage(msg);
        return;
    }

    // SDL's event pump can leave DefWindowProc's modal move loop holding
    // capture after button-up. Never enter that loop for these windows.
    if (BeginSdlDrag(msg->hwnd, command, button,
                     POINT{(short)LOWORD(msg->lParam),
                           (short)HIWORD(msg->lParam)})) {
        TakeMessage(msg);
        return;
    }

    // A press taken in a low level hook never activated the window.
    if (GetForegroundWindow() != msg->hwnd) {
        SetForegroundWindow(msg->hwnd);
    }

    if (GetKeyState(VK_LBUTTON) >= 0) {
        SetSyncKeyState(VK_LBUTTON, true);
    }

    Wh_Log(L"Request to %s %08X, starting the loop", NameOfCommand(command),
           (DWORD)(ULONG_PTR)msg->hwnd);

    g_loop = {
        .command = command,
        .button = button,
        .hWnd = msg->hwnd,
        .startPt = msg->pt,
        .fromHook = takenInHook,
    };

    msg->message = WM_SYSCOMMAND;
    msg->wParam = command;
}

// Runs for the messages the loop retrieves, and ahead of it the wait for the
// drag threshold, which inLoop tells apart.
void OnLoopMessageRemoved(MSG* msg, bool inLoop) {
    if (!g_loop.dragged) {
        // A resize starts the loop with GUI_INMOVESIZE already set, so the
        // pointer leaving the drag threshold is what tells it apart from a
        // click; a move waits at the threshold and sets GUI_INMOVESIZE then.
        bool started = IsSizeCommand(g_loop.command)
                           ? IsPastDragThreshold(g_loop.startPt, msg->pt)
                           : inLoop;
        if (started) {
            g_loop.dragged = true;
            MaskWinKeyReleaseIfNeeded(g_loop.command);
        }
    }

    if (msg->message == WM_MOUSEMOVE) {
        // A release the loop never sees, e.g. one a hook further along the
        // chain swallowed, would leave the window stuck to the cursor.
        if (GetAsyncKeyState(g_loop.button) >= 0) {
            Wh_Log(L"Button %02X is up with no release seen, ending the loop",
                   g_loop.button);
            msg->message = WM_LBUTTONUP;
            msg->wParam = 0;
            if (GetAsyncKeyState(VK_LBUTTON) >= 0 &&
                GetKeyState(VK_LBUTTON) < 0) {
                SetSyncKeyState(VK_LBUTTON, false);
            }
            g_loop = {};
            g_takenPressButton = 0;
            return;
        }

        // The loop retrieves the moves itself, without dispatching them,
        // holds an internal capture for which no WM_SETCURSOR is sent, and
        // shows the class cursor. A title strip drag keeps the arrow, as a
        // title bar drag does.
        if (!g_loop.fromHook) {
            SetCursor(LoadCursor(nullptr, CursorOfCommand(g_loop.command)));
        }
        return;
    }

    bool down;
    int button = ButtonOfMessage(msg->message, HIWORD(msg->wParam), &down);

    // Same as AltSnap: while a window is being moved, the right button toggles
    // its maximized state. A maximized window is handled by the action path in
    // OnMessageRemoved, which runs first; this covers the half where a normal
    // window is maximized.
    //
    // The loop is ended at this press rather than left running: moving a
    // maximized window restores it, and the loop is cancelled, which restores
    // the window as well, if the Alt release gets through and opens the menu.
    // Ending the loop with the release it consumes, and keeping that Alt
    // release from reaching the window, leaves the toggled state as the last
    // thing that happened to the window.
    if (down && button == VK_RBUTTON && g_loop.dragged &&
        !IsSizeCommand(g_loop.command)) {
        HWND hRootWnd = g_loop.hWnd;
        POINT pt = msg->pt;

        if (IsNonClientMessage(msg->message)) {
            msg->message = WM_NCLBUTTONUP;
        } else {
            msg->message = WM_LBUTTONUP;
            msg->wParam = 0;
        }

        g_swallowedPress = GetAsyncKeyState(VK_MENU) < 0;

        if (RunWindowAction(hRootWnd, WindowAction::Maximize, pt)) {
            Wh_Log(
                L"Right button while moving: toggled the maximized state of "
                L"%08X",
                (DWORD)(ULONG_PTR)hRootWnd);
        }
        return;
    }

    if (button != g_loop.button || down) {
        return;
    }

    if (button != VK_LBUTTON) {
        Wh_Log(L"Ending the loop with the release of button %02X", button);
        if (IsNonClientMessage(msg->message)) {
            msg->message = WM_NCLBUTTONUP;
        } else {
            msg->message = WM_LBUTTONUP;
            msg->wParam = 0;
        }

        if (GetAsyncKeyState(VK_LBUTTON) >= 0) {
            SetSyncKeyState(VK_LBUTTON, false);
        }
    }

    // A press passed on by a low level hook was never taken.
    if (!g_loop.dragged && !g_loop.fromHook) {
        if (button == VK_RBUTTON &&
            RunWindowAction(g_loop.hWnd, g_settings.rightClickAction, msg->pt)) {
            g_swallowedPress = GetAsyncKeyState(VK_MENU) < 0;
        } else {
            Wh_Log(L"Released within the drag threshold, replaying the click");
            ReplayPress(button, true);
        }
    }

    // The loop consumes the release.
    g_loop = {};
    g_takenPressButton = 0;
}

// The loop ended without its release being seen, e.g. cancelled with Esc.
void OnLoopOver() {
    if (GetAsyncKeyState(VK_LBUTTON) >= 0 && GetKeyState(VK_LBUTTON) < 0) {
        SetSyncKeyState(VK_LBUTTON, false);
    }

    g_loop = {};
}

// Posts the press taken for the drag delay back to its window, followed by a
// release, as the click it turned out to be.
void ReplayDelayedPress() {
    const MSG& down = g_delayedPress.downMsg;
    WPARAM upWParam = IsNonClientMessage(down.message)
                          ? down.wParam
                          : down.wParam & ~ButtonMask(g_delayedPress.button);

    Wh_Log(L"Replaying the press %04X for %08X as a click", down.message,
           (DWORD)(ULONG_PTR)down.hwnd);

    g_replayedPressPending = true;
    if (!PostMessage(down.hwnd, down.message, down.wParam, down.lParam)) {
        Wh_Log(L"PostMessage error: %u", GetLastError());
        g_replayedPressPending = false;
        return;
    }

    PostMessage(down.hwnd, ButtonUpMessageOf(down.message), upWParam,
                down.lParam);
}

void EndDragDelay() {
    KillTimer(nullptr, g_delayedPress.timerId);
    g_delayedPress = {};
}

// The mouse left the drag threshold before the delay was over: the drag is
// the program's own, e.g. a selection, so the press is handed back in place
// of this move, ahead of the moves which follow, and its release is left
// alone.
void HandDelayedPressBack(MSG* msg) {
    Wh_Log(
        L"Moved before the drag delay elapsed, handing the press %04X for "
        L"%08X back",
        g_delayedPress.downMsg.message,
        (DWORD)(ULONG_PTR)g_delayedPress.downMsg.hwnd);

    *msg = g_delayedPress.downMsg;
    g_takenPressButton = 0;
    EndDragDelay();
}

bool StartDragDelay(const MSG* downMsg,
                    int button,
                    UINT command,
                    HWND hRootWnd,
                    int delay) {
    UINT_PTR timerId = SetTimer(nullptr, 0, delay, nullptr);
    if (!timerId) {
        Wh_Log(L"SetTimer error: %u", GetLastError());
        return false;
    }

    Wh_Log(L"Message %04X for %08X, holding the press for %d ms",
           downMsg->message, (DWORD)(ULONG_PTR)downMsg->hwnd, delay);

    g_delayedPress = {
        .timerId = timerId,
        .downMsg = *downMsg,
        .button = button,
        .command = command,
        .hRootWnd = hRootWnd,
    };
    return true;
}

void OnDragDelayElapsed() {
    if (GetAsyncKeyState(g_delayedPress.button) < 0 &&
        PostSizeMoveRequest(g_delayedPress.hRootWnd, g_delayedPress.command,
                            g_delayedPress.button, g_delayedPress.downMsg.pt)) {
        Wh_Log(L"Drag delay elapsed, requesting a %s of root window %08X",
               NameOfCommand(g_delayedPress.command),
               (DWORD)(ULONG_PTR)g_delayedPress.hRootWnd);

        // Shown from here on, ahead of the first move the loop sets it for:
        // the window under the cursor is this thread's, which retrieved the
        // press.
        SetCursor(LoadCursor(nullptr, CursorOfCommand(g_delayedPress.command)));
    } else {
        ReplayDelayedPress();
    }

    EndDragDelay();
}

// Tracks the modifier keys so the low level mouse hook exists only while a
// trigger's keys are held.
void OnModifierKeyMessageRemoved(MSG* msg, DWORD modifier) {
    bool down = msg->message == WM_KEYDOWN || msg->message == WM_SYSKEYDOWN;

    // GetKeyState reflects the state at the time of the retrieved message.
    DWORD held = HeldModifiers(GetKeyState);
    bool triggerHeld = IsAnyModifierTriggerHeld(held);

    if (down) {
        // Bit 30 of lParam is set for the auto repeats which arrive while
        // the key is held, including throughout a drag.
        constexpr LPARAM kPreviousKeyStateDown = 1 << 30;
        if (!(msg->lParam & kPreviousKeyStateDown) && triggerHeld &&
            !IsAnyModifierTriggerHeld(held & ~modifier)) {
            // A hold starts with this key. A keyless trigger keeps its own
            // hook, and with it whatever drag is under way.
            g_swallowedPress = false;
            if (!IsAnyTriggerKeyless()) {
                RemoveLowLevelMouseHook();
            }
        }
    }

    if (triggerHeld) {
        InstallLowLevelMouseHookIfNeeded();
    } else {
        RemoveLowLevelMouseHookIfIdle();
    }

    // The app saw the Alt press, so it must see the release too. Only the
    // helper masks the menu; here the flag is just cleared.
    if (!down && msg->wParam == VK_MENU) {
        g_swallowedPress = false;
    }
}

// Runs for every message removed from the queue of the current thread, before
// the program sees it.
void OnMessageRemoved(MSG* msg) {
    if (msg->message == g_replayPressMessage) {
        ReplayPress((int)msg->wParam, msg->lParam != 0);
        TakeMessage(msg);
        return;
    }

    if (msg->message == g_dragUpdateMessage) {
        OnDragUpdate();
        TakeMessage(msg);
        return;
    }

    if (msg->message == WM_TIMER && !msg->hwnd) {
        if (g_delayedPress.timerId && msg->wParam == g_delayedPress.timerId) {
            OnDragDelayElapsed();
            TakeMessage(msg);
            return;
        }

        if (g_llDelayTimerId && msg->wParam == g_llDelayTimerId) {
            OnLowLevelDragDelayElapsed();
            TakeMessage(msg);
            return;
        }
    }

    if (!msg->hwnd) {
        return;
    }

    if (HandleSdlDragMessage(msg)) {
        return;
    }

    if (msg->message == g_sizeMoveRequestMessage) {
        OnSizeMoveRequestRemoved(msg);
        return;
    }

    if (msg->message == g_pinRequestMessage) {
        HWND hWnd = msg->hwnd;
        TakeMessage(msg);
        if (hWnd && GetAncestor(hWnd, GA_ROOT) == hWnd) {
            SetWindowPos(hWnd, HWND_TOPMOST, 0, 0, 0, 0,
                         SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
        }
        return;
    }

    if (msg->message == WM_SYSKEYDOWN || msg->message == WM_KEYDOWN ||
        msg->message == WM_SYSKEYUP || msg->message == WM_KEYUP) {
        if (DWORD modifier = ModifierOfKey(msg->wParam)) {
            OnModifierKeyMessageRemoved(msg, modifier);
        } else {
            HandleActionKeyMessage(msg);
        }
        return;
    }

    bool actionDown;
    int actionButton = ButtonOfMessage(msg->message, HIWORD(msg->wParam),
                                       &actionDown);
    if (actionButton && HandleActionMouseMessage(msg, actionButton, actionDown))
        return;

    if (g_loop.command) {
        // Ahead of the loop is the wait for the drag threshold, during which
        // the window holds the capture.
        bool inLoop = IsInMoveLoop();
        if (inLoop || GetCapture() == g_loop.hWnd) {
            OnLoopMessageRemoved(msg, inLoop);
            return;
        }

        OnLoopOver();
    }

    if (g_delayedPress.timerId &&
        (msg->message == WM_MOUSEMOVE || msg->message == WM_NCMOUSEMOVE) &&
        IsPastDragThreshold(g_delayedPress.downMsg.pt, msg->pt)) {
        HandDelayedPressBack(msg);
        return;
    }

    bool down;
    int button = ButtonOfMessage(msg->message, HIWORD(msg->wParam), &down);
    if (!button) {
        return;
    }
    if (g_delayedPress.timerId) {
        if (button == g_delayedPress.button && !down) {
            Wh_Log(L"Released before the drag delay elapsed");
            ReplayDelayedPress();
            EndDragDelay();
            TakeMessage(msg);
        }
        return;
    }

    if (!down) {
        if (button == g_takenPressButton) {
            g_takenPressButton = 0;
            Wh_Log(
                L"Message %04X for %08X, taking the release of a taken press",
                msg->message, (DWORD)(ULONG_PTR)msg->hwnd);
            TakeMessage(msg);
        }
        return;
    }

    // A new press: the release of the last one, if it's still awaited, went
    // elsewhere.
    if (button == g_takenPressButton) {
        g_takenPressButton = 0;
    }

    if (g_replayedPressPending) {
        g_replayedPressPending = false;
        return;
    }

    // The extra info of a retrieved input message is the thread's until the
    // next one.
    if (GetMessageExtraInfo() == kOwnInputExtraInfo) {
        return;
    }

    HWND hRootWnd = GetAncestor(msg->hwnd, GA_ROOT);
    if (!hRootWnd) {
        return;
    }

    UINT command = DragCommandForPress(button, HeldModifiers(GetKeyState),
                                       hRootWnd, msg->pt);
    if (!command) {
        return;
    }

    g_takenPressButton = button;

    // A press on the title bar or the border isn't held: DefWindowProc
    // answers such a press, when replayed, with a drag wait of its own which
    // only a client release ends.
    int delay = TriggerOfCommand(command).delay;
    if (delay > 0 && !IsNonClientMessage(msg->message) &&
        StartDragDelay(msg, button, command, hRootWnd, delay)) {
        TakeMessage(msg);
        return;
    }

    Wh_Log(L"Message %04X for %08X, requesting a %s of root window %08X",
           msg->message, (DWORD)(ULONG_PTR)msg->hwnd, NameOfCommand(command),
           (DWORD)(ULONG_PTR)hRootWnd);

    if (!PostSizeMoveRequest(hRootWnd, command, button, msg->pt)) {
        g_takenPressButton = 0;
        return;
    }

    TakeMessage(msg);
}

LRESULT CALLBACK GetMsgProc(int nCode, WPARAM wParam, LPARAM lParam) {
    auto hookScope = HookRefCountScope();

    if (nCode == HC_ACTION && (wParam & PM_REMOVE) && lParam &&
        !g_uninitializing) {
        OnMessageRemoved((MSG*)lParam);
    }

    return CallNextHookEx(nullptr, nCode, wParam, lParam);
}

void UnsubclassWindow(HWND hWnd);

LRESULT CALLBACK SubclassProc(HWND hWnd,
                              UINT uMsg,
                              WPARAM wParam,
                              LPARAM lParam,
                              UINT_PTR uIdSubclass,
                              DWORD_PTR dwRefData) {
    auto hookScope = HookRefCountScope();

    if (uMsg == WM_NCDESTROY) {
        if (hWnd == g_contactWnd) {
            g_contactWnd = nullptr;
        }

        UnsubclassWindow(hWnd);
    } else if (uMsg == g_unsubclassRegisteredMessage) {
        UnsubclassWindow(hWnd);
        return 0;
    } else if (!IsAnyTriggerKeyless() &&
               !IsAnyModifierTriggerHeld(HeldModifiers(GetAsyncKeyState)) &&
               hWnd != g_contactWnd) {
        // Needed only while a trigger's keys are held or a contact is being
        // routed. The hit test preceding the next press puts it back.
        UnsubclassWindow(hWnd);
    } else if (IsPointerMessage(uMsg)) {
        UINT pointerId = GET_POINTERID_WPARAM(wParam);
        bool tracked = hWnd == g_contactWnd && pointerId == g_contactPointerId;

        if (int button = ButtonOfPointerDownMessage(uMsg, wParam)) {
            // A new contact, the mouse reuses its pointer id for every one.
            if (tracked) {
                g_contactWnd = nullptr;
            }

            HWND hRootWnd = GetAncestor(hWnd, GA_ROOT);
            POINT pt{(short)LOWORD(lParam), (short)HIWORD(lParam)};
            if (hRootWnd && !g_uninitializing &&
                DragCommandForPress(button, HeldModifiers(GetAsyncKeyState),
                                    hRootWnd, pt)) {
                Wh_Log(
                    L"Message %04X for %08X, routing pointer %u to "
                    L"DefWindowProc",
                    uMsg, (DWORD)(ULONG_PTR)hWnd, pointerId);
                g_contactWnd = hWnd;
                g_contactPointerId = pointerId;
                g_contactButton = button;
                return DefWindowProc(hWnd, uMsg, wParam, lParam);
            }
        } else if (tracked &&
                   IsPointerContactGoneMessage(uMsg, wParam, g_contactButton)) {
            // The program saw the pointer enter, so it gets to see this.
            g_contactWnd = nullptr;
        } else if (tracked) {
            if (IsPointerContactEndMessage(uMsg)) {
                g_contactWnd = nullptr;
            }

            return DefWindowProc(hWnd, uMsg, wParam, lParam);
        }
    }

    return DefSubclassProc(hWnd, uMsg, wParam, lParam);
}

void UnsubclassWindow(HWND hWnd) {
    RemoveWindowSubclass(hWnd, SubclassProc, 0);

    if (hWnd == g_lastSubclassedWnd) {
        g_lastSubclassedWnd = nullptr;
    }

    std::lock_guard<std::mutex> guard(g_subclassedWindowsMutex);
    g_subclassedWindows.erase(hWnd);
}

void SubclassWindowIfNeeded(HWND hWnd) {
    if (hWnd == g_lastSubclassedWnd) {
        return;
    }

    HWND hRootWnd = GetAncestor(hWnd, GA_ROOT);
    if (!hRootWnd ||
        (!CanMoveRootWindow(hRootWnd) && !CanSizeRootWindow(hRootWnd))) {
        return;
    }

    std::lock_guard<std::mutex> guard(g_subclassedWindowsMutex);
    if (g_uninitializing) {
        return;
    }

    if (!g_subclassedWindows.contains(hWnd)) {
        if (!SetWindowSubclass(hWnd, SubclassProc, 0, 0)) {
            Wh_Log(L"SetWindowSubclass error for %08X", (DWORD)(ULONG_PTR)hWnd);
            return;
        }

        g_subclassedWindows.insert(hWnd);
    }

    g_lastSubclassedWnd = hWnd;
}

// The File Explorer title strip, where the styler's full-width tab pill takes
// every press as a tab grab. Its island never turns pointer input into window
// messages, so a press there is taken in a low level hook and handed to the
// system's own move loop: the stock drag, Aero Snap and arrow cursor. A double
// click toggles the maximized state and a right click opens the system menu,
// as on any title bar.
//
// The hook has a thread of its own. A low level hook is called on the thread
// which installed it, for every mouse event on the desktop, and an Explorer
// window thread that's busy painting would hold up the cursor everywhere.
HANDLE g_stripHookThread;
DWORD g_stripHookThreadId;

// Touched by the strip hook's thread only.
struct {
    HWND hRootWnd;
    DWORD time;
    POINT pt;
} g_stripLastPress;
HWND g_stripRightPressRootWnd;
bool g_stripSwallowLeftUp;

constexpr UINT kPopupSystemMenuMessage = 0x0313;  // WM_POPUPSYSTEMMENU

// Starts the system's move loop on the window's thread, the way a title bar
// press does. The press itself is passed on: the request, being posted, is
// retrieved ahead of it, and the loop then takes it and the release, which
// keeps the button state real.
bool HandOffMoveToSystemLoop(HWND hRootWnd, int button, POINT pt) {
    if (button != VK_LBUTTON) {
        return false;
    }

    DWORD processId = 0;
    GetWindowThreadProcessId(hRootWnd, &processId);
    AllowSetForegroundWindow(processId);
    if (!PostSizeMoveRequest(hRootWnd, SC_MOVE | HTCAPTION,
                             button | kTakenInHookFlag, pt)) {
        return false;
    }

    return true;
}

bool IsStripDoubleClick(HWND hRootWnd, const MSLLHOOKSTRUCT* ms) {
    return hRootWnd == g_stripLastPress.hRootWnd &&
           ms->time - g_stripLastPress.time <= GetDoubleClickTime() &&
           abs(ms->pt.x - g_stripLastPress.pt.x) <=
               GetSystemMetrics(SM_CXDOUBLECLK) / 2 &&
           abs(ms->pt.y - g_stripLastPress.pt.y) <=
               GetSystemMetrics(SM_CYDOUBLECLK) / 2;
}

LRESULT CALLBACK StripLowLevelMouseProc(int nCode,
                                        WPARAM wParam,
                                        LPARAM lParam) {
    auto hookScope = HookRefCountScope();

    if (nCode != HC_ACTION || g_uninitializing) {
        return CallNextHookEx(nullptr, nCode, wParam, lParam);
    }

    const MSLLHOOKSTRUCT* ms = (const MSLLHOOKSTRUCT*)lParam;
    if (ms->dwExtraInfo == kOwnInputExtraInfo ||
        !g_settings.explorerTitleStripDrag) {
        return CallNextHookEx(nullptr, nCode, wParam, lParam);
    }

    // The double-click press was swallowed, so its release goes too.
    if (wParam == WM_LBUTTONUP && g_stripSwallowLeftUp) {
        g_stripSwallowLeftUp = false;
        return 1;
    }
    if (wParam == WM_LBUTTONDOWN) g_stripSwallowLeftUp = false;

    if (wParam == WM_RBUTTONUP && g_stripRightPressRootWnd) {
        HWND hRootWnd = g_stripRightPressRootWnd;
        g_stripRightPressRootWnd = nullptr;
        PostMessage(hRootWnd, kPopupSystemMenuMessage, 0,
                    MAKELPARAM(ms->pt.x, ms->pt.y));
        return 1;
    }

    if ((wParam != WM_LBUTTONDOWN && wParam != WM_RBUTTONDOWN) ||
        HeldModifiers(GetAsyncKeyState) || swm::IsPaused()) {
        return CallNextHookEx(nullptr, nCode, wParam, lParam);
    }

    HWND hWnd = CompositionHostedWindowFromPoint(ms->pt);
    HWND hRootWnd = hWnd ? GetAncestor(hWnd, GA_ROOT) : nullptr;
    if (!hRootWnd || !IsExplorerTitleStripPress(hRootWnd, ms->pt)) {
        return CallNextHookEx(nullptr, nCode, wParam, lParam);
    }

    if (wParam == WM_RBUTTONDOWN) {
        g_stripRightPressRootWnd = hRootWnd;
        return 1;
    }

    if (!CanMoveRootWindow(hRootWnd)) {
        return CallNextHookEx(nullptr, nCode, wParam, lParam);
    }

    if (IsStripDoubleClick(hRootWnd, ms)) {
        g_stripLastPress = {};
        PostMessage(hRootWnd, WM_SYSCOMMAND,
                    IsZoomed(hRootWnd) ? SC_RESTORE : SC_MAXIMIZE, 0);
        g_stripSwallowLeftUp = true;
        return 1;
    }

    g_stripLastPress = {hRootWnd, ms->time, ms->pt};
    HandOffMoveToSystemLoop(hRootWnd, VK_LBUTTON, ms->pt);
    return CallNextHookEx(nullptr, nCode, wParam, lParam);
}

// Physical coordinates throughout, as the hook reports them.
DWORD WINAPI StripHookThreadProc(void*) {
    SetThreadDpiAwarenessContext(DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2);

    MSG msg;
    PeekMessage(&msg, nullptr, WM_USER, WM_USER, PM_NOREMOVE);

    HHOOK hook = SetWindowsHookEx(WH_MOUSE_LL, StripLowLevelMouseProc,
                                  GetModuleHandle(nullptr), 0);
    if (!hook) {
        Wh_Log(L"SetWindowsHookEx(WH_MOUSE_LL) error for the strip: %u",
               GetLastError());
        return 0;
    }

    while (GetMessage(&msg, nullptr, 0, 0) > 0) {
        DispatchMessage(&msg);
    }

    UnhookWindowsHookEx(hook);
    return 0;
}

// Started by the first File Explorer window of the process. Explorer runs
// many processes without one, and each hook in the chain is a stop for every
// mouse event on the desktop.
std::mutex g_stripHookThreadMutex;
std::atomic<bool> g_stripHookThreadStarted;

bool IsFileExplorerWindow(HWND hWnd) {
    WCHAR className[32];
    return GetClassName(hWnd, className, ARRAYSIZE(className)) &&
           _wcsicmp(className, L"CabinetWClass") == 0;
}

void StartStripHookThreadIfNeeded(HWND hWnd) {
    if (g_stripHookThreadStarted || !IsExplorerProcess() ||
        !IsFileExplorerWindow(hWnd)) {
        return;
    }

    std::lock_guard<std::mutex> guard(g_stripHookThreadMutex);
    if (g_stripHookThreadStarted || g_uninitializing) {
        return;
    }

    g_stripHookThreadStarted = true;
    g_stripHookThread = CreateThread(nullptr, 0, StripHookThreadProc, nullptr,
                                     0, &g_stripHookThreadId);
    if (!g_stripHookThread) {
        Wh_Log(L"CreateThread error: %u", GetLastError());
    }
}

void StopStripHookThread() {
    HANDLE thread;
    {
        std::lock_guard<std::mutex> guard(g_stripHookThreadMutex);
        thread = g_stripHookThread;
        g_stripHookThread = nullptr;
    }

    if (!thread) {
        return;
    }

    // The queue exists once the thread has started.
    while (WaitForSingleObject(thread, 0) == WAIT_TIMEOUT &&
           !PostThreadMessage(g_stripHookThreadId, WM_QUIT, 0, 0)) {
        Sleep(10);
    }

    WaitForSingleObject(thread, INFINITE);
    CloseHandle(thread);
}

LRESULT CALLBACK CallWndProc(int nCode, WPARAM wParam, LPARAM lParam) {
    auto hookScope = HookRefCountScope();

    if (nCode == HC_ACTION && lParam) {
        const CWPSTRUCT* cwp = (const CWPSTRUCT*)lParam;
        if (cwp->message == WM_NCCREATE) {
            // The mark is looked up on root windows, so a child window goes
            // without.
            const CREATESTRUCT* cs = (const CREATESTRUCT*)cwp->lParam;
            if (!(cs->style & WS_CHILD) && g_getMessageHook) {
                MarkHookedWindow(cwp->hwnd);
            }
            if (!(cs->style & WS_CHILD)) {
                StartStripHookThreadIfNeeded(cwp->hwnd);
            }
        }

        if (cwp->message == WM_NCHITTEST &&
            (IsAnyTriggerKeyless() ||
                    IsAnyModifierTriggerHeld(
                        HeldModifiers(GetAsyncKeyState)))) {
            // The thread's synchronized key state is stale if the window
            // isn't active yet, e.g. a click on a background window.
            SubclassWindowIfNeeded(cwp->hwnd);
        } else if (cwp->message == WM_ACTIVATEAPP && IsAnyTriggerKeyless()) {
            // Told by the message rather than by the foreground window, which
            // the two processes see change at their own times.
            if (cwp->wParam) {
                InstallLowLevelMouseHookIfNeeded();
            } else {
                RemoveLowLevelMouseHookIfIdle();
            }
        }
    }

    return CallNextHookEx(nullptr, nCode, wParam, lParam);
}

// Where the window is held relative to its origin. A maximized window is
// restored first, like a title bar drag does, keeping the grab proportional to
// the size it restores to. The restore is queued rather than performed: this
// runs while the input thread waits, and the window's thread may be busy. The
// move which follows queues up behind it.
POINT CalcDragGrab(HWND hRootWnd, POINT ptDown) {
    RECT rc;
    GetWindowRect(hRootWnd, &rc);

    WINDOWPLACEMENT placement{.length = sizeof(placement)};
    if (!GetWindowPlacement(hRootWnd, &placement) ||
        placement.showCmd != SW_SHOWMAXIMIZED) {
        return POINT{ptDown.x - rc.left, ptDown.y - rc.top};
    }

    const RECT& normal = placement.rcNormalPosition;
    POINT grab{
        MulDiv(ptDown.x - rc.left, normal.right - normal.left,
               rc.right - rc.left),
        MulDiv(ptDown.y - rc.top, normal.bottom - normal.top,
               rc.bottom - rc.top),
    };

    // For a window of this thread the move is applied at once, so the restore
    // has to be as well.
    if (GetWindowThreadProcessId(hRootWnd, nullptr) == GetCurrentThreadId()) {
        ShowWindow(hRootWnd, SW_RESTORE);
    } else {
        ShowWindowAsync(hRootWnd, SW_RESTORE);
    }

    return grab;
}

// The global helper places dragged windows from a thread of its own. Posted
// moves pile up in a busy program's queue and the window trails the pointer;
// this thread only ever applies the newest position, waiting for each to land,
// so the window keeps up at whatever rate the program can repaint. A hung
// program gets a posted move instead, and the input thread never waits.
namespace mover {
std::mutex g_lock;
HWND g_wnd;
RECT g_rect;
UINT g_flags;
bool g_pending;
bool g_quit;
HANDLE g_event;
HANDLE g_thread;

DWORD WINAPI ThreadProc(void*) {
    SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_ABOVE_NORMAL);
    while (WaitForSingleObject(g_event, INFINITE) == WAIT_OBJECT_0) {
        for (;;) {
            HWND wnd;
            RECT rc;
            UINT flags;
            {
                std::lock_guard<std::mutex> guard(g_lock);
                if (g_quit) return 0;
                if (!g_pending) break;
                g_pending = false;
                wnd = g_wnd;
                rc = g_rect;
                flags = g_flags;
            }
            if (IsHungAppWindow(wnd)) flags |= SWP_ASYNCWINDOWPOS;
            else flags &= ~SWP_ASYNCWINDOWPOS;
            SetWindowPos(wnd, nullptr, rc.left, rc.top, rc.right - rc.left,
                         rc.bottom - rc.top, flags);
        }
    }
    return 0;
}

void Queue(HWND wnd, const RECT& rc, UINT flags) {
    std::lock_guard<std::mutex> guard(g_lock);
    if (!g_thread) {
        g_event = CreateEvent(nullptr, FALSE, FALSE, nullptr);
        if (g_event) g_thread = CreateThread(nullptr, 0, ThreadProc, nullptr, 0, nullptr);
        if (!g_thread) {
            SetWindowPos(wnd, nullptr, rc.left, rc.top, rc.right - rc.left,
                         rc.bottom - rc.top, flags | SWP_ASYNCWINDOWPOS);
            return;
        }
    }
    g_wnd = wnd;
    g_rect = rc;
    g_flags = flags;
    g_pending = true;
    SetEvent(g_event);
}

void Stop() {
    HANDLE thread;
    {
        std::lock_guard<std::mutex> guard(g_lock);
        g_quit = true;
        thread = g_thread;
        g_thread = nullptr;
    }
    if (!thread) return;
    SetEvent(g_event);
    // A move into a program that hangs right then can hold the thread; it is
    // left to finish rather than blocking the unload for long.
    WaitForSingleObject(thread, 3000);
    CloseHandle(thread);
}
}  // namespace mover

void PlaceDraggedWindow(HWND hRootWnd, const RECT& rc, UINT flags) {
    if (g_globalInput) {
        mover::Queue(hRootWnd, rc, flags);
        return;
    }
    // SWP_ASYNCWINDOWPOS posts the request when the window belongs to another
    // thread, which keeps a busy owner from blocking the caller.
    SetWindowPos(hRootWnd, nullptr, rc.left, rc.top, rc.right - rc.left,
                 rc.bottom - rc.top, flags | SWP_ASYNCWINDOWPOS);
}

// Ctrl+Alt drag: the window's edges cling to the screen edges and to other
// windows' edges when they come close, like Hyprland's magnetic edges. The
// other windows are read once per drag.
namespace magnet {
struct Cache {
    HWND wnd = nullptr;
    ULONGLONG tick = 0;
    RECT margin{};
    SIZE size{};
    std::vector<RECT> windows;
    std::vector<RECT> areas;
};
Cache g_cache;

BOOL CALLBACK WindowProc(HWND hWnd, LPARAM param) {
    auto* cache = reinterpret_cast<Cache*>(param);
    if (hWnd == cache->wnd || !IsWindowVisible(hWnd) || IsIconic(hWnd) || IsZoomed(hWnd) ||
        (GetWindowLongPtrW(hWnd, GWL_EXSTYLE) & (WS_EX_TOOLWINDOW | WS_EX_NOACTIVATE)) ||
        !CanActOnRootWindow(hWnd)) {
        return TRUE;
    }
    DWORD cloaked = 0;
    RECT frame{};
    if ((SUCCEEDED(DwmGetWindowAttribute(hWnd, DWMWA_CLOAKED, &cloaked, sizeof(cloaked))) &&
         cloaked) ||
        FAILED(DwmGetWindowAttribute(hWnd, DWMWA_EXTENDED_FRAME_BOUNDS, &frame,
                                     sizeof(frame))) ||
        frame.right - frame.left < 50 || frame.bottom - frame.top < 50) {
        return TRUE;
    }
    cache->windows.push_back(frame);
    return cache->windows.size() < 64;
}

BOOL CALLBACK AreaProc(HMONITOR monitor, HDC, LPRECT, LPARAM param) {
    auto* cache = reinterpret_cast<Cache*>(param);
    MONITORINFO mi{sizeof(mi)};
    if (GetMonitorInfoW(monitor, &mi)) {
        cache->areas.push_back(mi.rcWork);
        RECT gapped = snapCommander::GappedWorkArea(monitor, mi.rcWork);
        if (!EqualRect(&gapped, &mi.rcWork)) cache->areas.push_back(gapped);
    }
    return TRUE;
}

// Moves the window's top-left so the nearest edge in reach lines up.
void Apply(HWND hWnd, POINT* pos) {
    int reach = swm::g_magnetPx;
    if (reach <= 0) return;
    ULONGLONG now = GetTickCount64();
    if (g_cache.wnd != hWnd || now - g_cache.tick > 500) {
        Cache cache;
        cache.wnd = hWnd;
        RECT wr{}, fr{};
        if (!GetWindowRect(hWnd, &wr)) return;
        if (FAILED(DwmGetWindowAttribute(hWnd, DWMWA_EXTENDED_FRAME_BOUNDS, &fr, sizeof(fr)))) {
            fr = wr;
        }
        cache.margin = {fr.left - wr.left, fr.top - wr.top, wr.right - fr.right,
                        wr.bottom - fr.bottom};
        cache.size = {wr.right - wr.left, wr.bottom - wr.top};
        EnumWindows(WindowProc, reinterpret_cast<LPARAM>(&cache));
        EnumDisplayMonitors(nullptr, nullptr, AreaProc, reinterpret_cast<LPARAM>(&cache));
        g_cache = std::move(cache);
    }
    g_cache.tick = now;
    const Cache& c = g_cache;
    int gap = swm::g_magnetGap;
    RECT v{pos->x + c.margin.left, pos->y + c.margin.top, 0, 0};
    v.right = v.left + c.size.cx - c.margin.left - c.margin.right;
    v.bottom = v.top + c.size.cy - c.margin.top - c.margin.bottom;
    int bestX = reach + 1, bestY = reach + 1, dx = 0, dy = 0;
    auto tryX = [&](LONG target, LONG edge) {
        int d = (int)(target - edge);
        if (std::abs(d) < bestX) bestX = std::abs(d), dx = d;
    };
    auto tryY = [&](LONG target, LONG edge) {
        int d = (int)(target - edge);
        if (std::abs(d) < bestY) bestY = std::abs(d), dy = d;
    };
    for (const RECT& a : c.areas) {
        if (v.top < a.bottom && v.bottom > a.top) tryX(a.left, v.left), tryX(a.right, v.right);
        if (v.left < a.right && v.right > a.left) tryY(a.top, v.top), tryY(a.bottom, v.bottom);
    }
    for (const RECT& w : c.windows) {
        bool level = v.top < w.bottom + reach && v.bottom > w.top - reach;
        bool across = v.left < w.right + reach && v.right > w.left - reach;
        if (level) {
            tryX(w.right + gap, v.left);
            tryX(w.left - gap, v.right);
            tryY(w.top, v.top);
            tryY(w.bottom, v.bottom);
        }
        if (across) {
            tryY(w.bottom + gap, v.top);
            tryY(w.top - gap, v.bottom);
            tryX(w.left, v.left);
            tryX(w.right, v.right);
        }
    }
    if (bestX <= reach) pos->x += dx;
    if (bestY <= reach) pos->y += dy;
}
}  // namespace magnet

void MoveDraggedWindow(HWND hRootWnd, POINT grab, POINT pt) {
    POINT pos{pt.x - grab.x, pt.y - grab.y};
    if (g_globalInput && GetAsyncKeyState(VK_CONTROL) < 0) {
        magnet::Apply(hRootWnd, &pos);
    }
    RECT rc{pos.x, pos.y, pos.x, pos.y};
    PlaceDraggedWindow(hRootWnd, rc, SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE);
}

// The edges the command takes hold of follow the pointer from where the drag
// started, the others stay put. SetWindowPos doesn't ask the window for its
// minimum size, so the system's minimum is kept instead.
void SizeDraggedWindow(HWND hRootWnd,
                       UINT command,
                       const RECT& rcStart,
                       POINT ptStart,
                       POINT pt) {
    UINT edge = command & 0xF;
    LONG dx = pt.x - ptStart.x;
    LONG dy = pt.y - ptStart.y;
    LONG minWidth = GetSystemMetrics(SM_CXMINTRACK);
    LONG minHeight = GetSystemMetrics(SM_CYMINTRACK);

    RECT rc = rcStart;
    switch (edge) {
        case WMSZ_LEFT:
        case WMSZ_TOPLEFT:
        case WMSZ_BOTTOMLEFT:
            rc.left = std::min(rcStart.left + dx, rc.right - minWidth);
            break;
        case WMSZ_RIGHT:
        case WMSZ_TOPRIGHT:
        case WMSZ_BOTTOMRIGHT:
            rc.right = std::max(rcStart.right + dx, rc.left + minWidth);
            break;
    }

    switch (edge) {
        case WMSZ_TOP:
        case WMSZ_TOPLEFT:
        case WMSZ_TOPRIGHT:
            rc.top = std::min(rcStart.top + dy, rc.bottom - minHeight);
            break;
        case WMSZ_BOTTOM:
        case WMSZ_BOTTOMLEFT:
        case WMSZ_BOTTOMRIGHT:
            rc.bottom = std::max(rcStart.bottom + dy, rc.top + minHeight);
            break;
    }

    PlaceDraggedWindow(hRootWnd, rc, SWP_NOZORDER | SWP_NOACTIVATE);
}

thread_local struct {
    HWND window;
    UINT command;
    int button;
    POINT start;
    POINT grab;
    RECT rectangle;
    bool started;
} g_sdlDrag;

bool BeginSdlDrag(HWND window, UINT command, int button, POINT point) {
    WCHAR name[64];
    if (!GetClassName(window, name, ARRAYSIZE(name)) ||
        _wcsicmp(name, L"SDL_app") != 0) {
        return false;
    }
    g_sdlDrag = {.window = window, .command = command,
                 .button = button, .start = point};
    SetCapture(window);
    return true;
}

bool HandleSdlDragMessage(MSG* msg) {
    if (!g_sdlDrag.window) {
        return false;
    }
    bool down = false;
    int button = ButtonOfMessage(msg->message, HIWORD(msg->wParam), &down);
    bool released = button == g_sdlDrag.button && !down;
    // As in the modal loop: the right button while moving toggles the
    // maximized state and ends the drag. Its release and the Alt release are
    // kept from the window.
    if (down && button == VK_RBUTTON && g_sdlDrag.started &&
        !IsSizeCommand(g_sdlDrag.command)) {
        HWND window = g_sdlDrag.window;
        g_sdlDrag = {};
        if (GetCapture() == window) {
            ReleaseCapture();
        }
        g_takenPressButton = VK_RBUTTON;
        g_swallowedPress = GetAsyncKeyState(VK_MENU) < 0;
        TakeMessage(msg);
        if (RunWindowAction(window, WindowAction::Maximize, msg->pt)) {
            Wh_Log(L"Right button while moving SDL window %08X: toggled "
                   L"maximize",
                   (DWORD)(ULONG_PTR)window);
        }
        return true;
    }
    bool cancelled = msg->message == WM_CANCELMODE ||
                     (msg->message == WM_KEYDOWN && msg->wParam == VK_ESCAPE) ||
                     GetCapture() != g_sdlDrag.window;
    if (released || cancelled || GetAsyncKeyState(g_sdlDrag.button) >= 0) {
        HWND window = g_sdlDrag.window;
        g_sdlDrag = {};
        if (GetCapture() == window) {
            ReleaseCapture();
        }
        if (released) {
            g_takenPressButton = 0;
            TakeMessage(msg);
            return true;
        }
        return false;
    }
    if (msg->message != WM_MOUSEMOVE && msg->message != WM_NCMOUSEMOVE) {
        return false;
    }
    if (!g_sdlDrag.started && IsPastDragThreshold(g_sdlDrag.start, msg->pt)) {
        g_sdlDrag.started = true;
        if (IsSizeCommand(g_sdlDrag.command)) {
            GetWindowRect(g_sdlDrag.window, &g_sdlDrag.rectangle);
        } else {
            g_sdlDrag.grab = CalcDragGrab(g_sdlDrag.window, g_sdlDrag.start);
        }
        g_swallowedPress = GetAsyncKeyState(VK_MENU) < 0;
    }
    if (g_sdlDrag.started) {
        if (IsSizeCommand(g_sdlDrag.command)) {
            SizeDraggedWindow(g_sdlDrag.window, g_sdlDrag.command,
                              g_sdlDrag.rectangle, g_sdlDrag.start, msg->pt);
        } else {
            MoveDraggedWindow(g_sdlDrag.window, g_sdlDrag.grab, msg->pt);
        }
    }
    SetCursor(LoadCursor(nullptr, CursorOfCommand(g_sdlDrag.command)));
    TakeMessage(msg);
    return true;
}

void DragWindowTo(POINT pt) {
    if (IsSizeCommand(g_llCommand)) {
        SizeDraggedWindow(g_llRootWnd, g_llCommand, g_llDragStartRect,
                          g_llDragStartPt, pt);
    } else {
        MoveDraggedWindow(g_llRootWnd, g_llDragGrab, pt);
    }
}

// The class supplies the cursor, and with DefWindowProc as the window procedure
// no mod code is on the window's call path.
HWND CreateDragOverlay(POINT pt, PCWSTR cursor) {
    WNDCLASS wc{
        .lpfnWndProc = DefWindowProc,
        .hInstance = GetModuleHandle(nullptr),
        .hCursor = LoadCursor(nullptr, cursor),
        .lpszClassName = kDragOverlayClassName,
    };
    if (!RegisterClass(&wc) && GetLastError() != ERROR_CLASS_ALREADY_EXISTS) {
        Wh_Log(L"RegisterClass error: %u", GetLastError());
        return nullptr;
    }

    HWND hWnd = CreateWindowEx(
        WS_EX_TOPMOST | WS_EX_TOOLWINDOW | WS_EX_NOACTIVATE | WS_EX_LAYERED,
        kDragOverlayClassName, nullptr, WS_POPUP, pt.x - kDragOverlaySize / 2,
        pt.y - kDragOverlaySize / 2, kDragOverlaySize, kDragOverlaySize,
        nullptr, nullptr, wc.hInstance, nullptr);
    if (!hWnd) {
        Wh_Log(L"CreateWindowEx error: %u", GetLastError());
        return nullptr;
    }

    // The class is registered once and kept, with the cursor of that time.
    SetClassLongPtr(hWnd, GCLP_HCURSOR, (LONG_PTR)wc.hCursor);

    // As good as invisible, while an alpha of zero would let the mouse through.
    SetLayeredWindowAttributes(hWnd, 0, 1, LWA_ALPHA);
    ShowWindow(hWnd, SW_SHOWNOACTIVATE);
    return hWnd;
}

void PlaceDragOverlay(POINT pt) {
    if (g_llDragOverlayWnd) {
        SetWindowPos(g_llDragOverlayWnd, nullptr, pt.x - kDragOverlaySize / 2,
                     pt.y - kDragOverlaySize / 2, 0, 0,
                     SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE);
    }
}

// Through DefWindowProc, so on the window's own thread wherever this runs.
void DestroyDragOverlay() {
    if (HWND hOverlayWnd = g_llDragOverlayWnd) {
        g_llDragOverlayWnd = nullptr;
        PostMessage(hOverlayWnd, WM_CLOSE, 0, 0);
    }
}

void KillLowLevelDelayTimer() {
    if (g_llDelayTimerId) {
        KillTimer(nullptr, g_llDelayTimerId);
        g_llDelayTimerId = 0;
    }
}

void ResetLowLevelDragState() {
    g_llRootWnd = nullptr;
    g_llButton = 0;
    g_llDragging = false;
    g_llDragSetUp = false;
    g_llDragUpdatePosted = false;
    KillLowLevelDelayTimer();
    DestroyDragOverlay();
}

// Display settings are never scaled, so they give the physical side.
BOOL CALLBACK FindMonitorEnumProc(HMONITOR hMonitor,
                                  HDC hdc,
                                  LPRECT lprcMonitor,
                                  LPARAM lParam) {
    MONITORINFOEX monitorInfo;
    monitorInfo.cbSize = sizeof(monitorInfo);
    DEVMODE mode{};
    mode.dmSize = sizeof(mode);
    if (!GetMonitorInfo(hMonitor, &monitorInfo) ||
        !EnumDisplaySettings(monitorInfo.szDevice, ENUM_CURRENT_SETTINGS,
                             &mode)) {
        return TRUE;
    }

    RECT physicalRect{mode.dmPosition.x, mode.dmPosition.y,
                      mode.dmPosition.x + (LONG)mode.dmPelsWidth,
                      mode.dmPosition.y + (LONG)mode.dmPelsHeight};
    if (!PtInRect(&physicalRect, *(const POINT*)lParam)) {
        return TRUE;
    }

    g_llMonitor.physicalRect = physicalRect;
    g_llMonitor.logicalRect = monitorInfo.rcMonitor;
    return FALSE;
}

bool FindMonitorForPhysicalPoint(POINT physicalPt) {
    g_llMonitor = {};
    EnumDisplayMonitors(nullptr, nullptr, FindMonitorEnumProc,
                        (LPARAM)&physicalPt);
    return !IsRectEmpty(&g_llMonitor.physicalRect);
}

// The hook reports physical coordinates, while this thread looks windows up
// and places them in its own.
POINT ToLogicalPoint(POINT physicalPt) {
    if (!PtInRect(&g_llMonitor.physicalRect, physicalPt) &&
        !FindMonitorForPhysicalPoint(physicalPt)) {
        return physicalPt;
    }

    const RECT& physical = g_llMonitor.physicalRect;
    const RECT& logical = g_llMonitor.logicalRect;
    return POINT{
        logical.left + MulDiv(physicalPt.x - physical.left,
                              logical.right - logical.left,
                              physical.right - physical.left),
        logical.top + MulDiv(physicalPt.y - physical.top,
                             logical.bottom - logical.top,
                             physical.bottom - physical.top),
    };
}

// Simulates the press of the button at the cursor, and its release too for a
// click. Runs from a message loop, never from the low level mouse hook's
// callback: input sent from within a low level hook callback isn't processed
// until the hook's timeout has run out, and the callbacks arriving in the
// meantime see state the callback hasn't updated yet. Since this press does
// enter the input queue, the Alt release needs no swallowing on its account.
void ReplayPress(int button, bool asClick) {
    DWORD downFlag;
    DWORD upFlag;
    DWORD mouseData = 0;
    switch (button) {
        case VK_RBUTTON:
            downFlag = MOUSEEVENTF_RIGHTDOWN;
            upFlag = MOUSEEVENTF_RIGHTUP;
            break;
        case VK_MBUTTON:
            downFlag = MOUSEEVENTF_MIDDLEDOWN;
            upFlag = MOUSEEVENTF_MIDDLEUP;
            break;
        case VK_XBUTTON1:
        case VK_XBUTTON2:
            downFlag = MOUSEEVENTF_XDOWN;
            upFlag = MOUSEEVENTF_XUP;
            mouseData = button == VK_XBUTTON1 ? XBUTTON1 : XBUTTON2;
            break;
        default:
            downFlag = MOUSEEVENTF_LEFTDOWN;
            upFlag = MOUSEEVENTF_LEFTUP;
            break;
    }

    INPUT inputs[2]{};
    inputs[0].type = INPUT_MOUSE;
    inputs[0].mi.dwFlags = downFlag;
    inputs[0].mi.mouseData = mouseData;
    inputs[0].mi.dwExtraInfo = kOwnInputExtraInfo;
    inputs[1].type = INPUT_MOUSE;
    inputs[1].mi.dwFlags = upFlag;
    inputs[1].mi.mouseData = mouseData;
    inputs[1].mi.dwExtraInfo = kOwnInputExtraInfo;
    UINT count = asClick ? 2 : 1;
    if (SendInput(count, inputs, sizeof(inputs[0])) == count) {
        g_swallowedPress = false;
    } else {
        Wh_Log(L"SendInput error: %u", GetLastError());
    }
}

// Hands a replay over to the message loop of this thread, where it's retrieved
// ahead of the input which follows, including an Alt release.
void PostReplayPress(int button, bool asClick) {
    HWND hFocusWnd = GetFocus();
    if (!hFocusWnd ||
        !PostMessage(hFocusWnd, g_replayPressMessage, button, asClick)) {
        PostThreadMessage(GetCurrentThreadId(), g_replayPressMessage, button,
                          asClick);
    }
}

// The press of a trigger's button over composition hosted content. Returns
// whether it was swallowed.
bool OnLowLevelButtonDown(const MSLLHOOKSTRUCT* ms, int button) {
    // Looked up afresh in case the display layout changed.
    g_llMonitor = {};
    POINT pt = ToLogicalPoint(ms->pt);

    HWND hWnd = CompositionHostedWindowFromPoint(pt);
    if (!hWnd) {
        // Delivered as a message, so the paths above handle it and keep the
        // system loop.
        return false;
    }

    HWND hRootWnd = GetAncestor(hWnd, GA_ROOT);
    if (!hRootWnd) {
        return false;
    }

    UINT command = DragCommandForPress(button, HeldModifiers(GetAsyncKeyState),
                                       hRootWnd, pt);
    if (!command) {
        return false;
    }

    Wh_Log(L"Swallowed the press of button %02X over %08X, root window %08X",
           button, (DWORD)(ULONG_PTR)hWnd, (DWORD)(ULONG_PTR)hRootWnd);

    g_llRootWnd = hRootWnd;
    g_llCommand = command;
    g_llButton = button;
    g_llDownPt = pt;
    g_llDownTime = ms->time;
    if (GetAsyncKeyState(VK_MENU) < 0) {
        g_swallowedPress = GetAsyncKeyState(VK_MENU) < 0;
    }

    // A timer may be left from a candidate reset on another thread.
    KillLowLevelDelayTimer();
    if (int delay = TriggerOfCommand(command).delay; delay > 0) {
        g_llDelayTimerId = SetTimer(nullptr, 0, delay, nullptr);
        if (!g_llDelayTimerId) {
            Wh_Log(L"SetTimer error: %u", GetLastError());
        }
    }

    return true;
}

// Puts the overlay up for a press which is still a candidate, if this is
// still the hook's thread: the timer is this thread's, the press the hook's.
// The press being held is what the state means, its release clearing it; the
// key state can't tell, a swallowed press never reaching it.
void OnLowLevelDragDelayElapsed() {
    KillLowLevelDelayTimer();

    {
        std::lock_guard<std::mutex> guard(g_lowLevelMouseHookMutex);
        if (GetCurrentThreadId() != g_lowLevelMouseHookThreadId) {
            return;
        }
    }

    POINT pt;
    if (!g_llRootWnd || g_llDragging || !GetCursorPos(&pt)) {
        return;
    }

    Wh_Log(L"Drag delay elapsed, showing the %s cursor",
           NameOfCommand(g_llCommand));
    g_llDragOverlayWnd = CreateDragOverlay(pt, CursorOfCommand(g_llCommand));
}

// The first move past the drag threshold, once the drag delay is over. Only
// what a low level hook callback can afford is done here, the rest waiting for
// the update this leaves to be posted.
void BeginLowLevelDrag(POINT pt) {
    Wh_Log(L"Starting a %s of root window %08X", NameOfCommand(g_llCommand),
           (DWORD)(ULONG_PTR)g_llRootWnd);

    g_llDragging = true;
    g_llDragStartPt = pt;
    KillLowLevelDelayTimer();
}

// The work a drag starts with, none of which belongs in the callback: the
// restore of a maximized window runs the program's layout, and it runs inline
// when the window is of the hook's own thread, which the foreground process's
// window commonly is.
void SetUpLowLevelDrag() {
    if (IsSizeCommand(g_llCommand)) {
        GetWindowRect(g_llRootWnd, &g_llDragStartRect);
    } else {
        g_llDragGrab = CalcDragGrab(g_llRootWnd, g_llDragStartPt);
    }

    // The press was swallowed, so the window wasn't brought to the front the
    // way a click on it would have been. Allowed because the process holding
    // the hook is the foreground one.
    DWORD processId = 0;
    GetWindowThreadProcessId(g_llRootWnd, &processId);
    if (!SetForegroundWindow(g_llRootWnd)) {
        Wh_Log(L"SetForegroundWindow error: %u", GetLastError());
    } else if (processId != GetCurrentProcessId()) {
        // The Alt release goes there now, and a later one here isn't to be
        // taken for it.
        if (!g_globalInput) g_swallowedPress = false;
    }

    MaskWinKeyReleaseIfNeeded(g_llCommand);

    if (!g_llDragOverlayWnd) {
        g_llDragOverlayWnd =
            CreateDragOverlay(g_llDragStartPt, CursorOfCommand(g_llCommand));
    }
}

// Runs on the hook's thread once the update posted for it is retrieved. The
// press may be over by then, its release having reset the state.
void OnDragUpdate() {
    g_llDragUpdatePosted = false;

    if (!g_llRootWnd) {
        return;
    }

    if (g_llDragging && !g_llDragSetUp) {
        g_llDragSetUp = true;
        SetUpLowLevelDrag();
    }

    PlaceDragOverlay(g_llDragPt);

    if (g_llDragging) {
        DragWindowTo(g_llDragPt);
    }
}

// The callback records where the pointer is and leaves the windows to the
// message loop: a low level hook which takes too long to return is dropped by
// the system, and moving or resizing a window of the hook's own thread runs
// the program's handlers inline. One update is queued at a time, and it acts
// on whatever position the last move left.
void PostDragUpdate(POINT pt) {
    g_llDragPt = pt;
    if (g_llDragUpdatePosted) {
        return;
    }

    // GetFocus is of this thread, so the update is retrieved here, where the
    // drag state belongs.
    HWND hFocusWnd = GetFocus();
    if (hFocusWnd && PostMessage(hFocusWnd, g_dragUpdateMessage, 0, 0)) {
        g_llDragUpdatePosted = true;
    } else if (PostThreadMessage(GetCurrentThreadId(), g_dragUpdateMessage, 0,
                                 0)) {
        g_llDragUpdatePosted = true;
    }
}

// A low level hook must return at once or the system drops it, so an action
// picked in the callback (a menu, or a move a hung program would block) runs
// from the hook thread's queue instead.
// The action rides in the message number, which keeps the point whole in
// lParam on 32-bit builds too.
// Read by the helper's watchdog to tell a hook the system dropped.
POINT g_llLastCallbackPt;
DWORD g_llLastCallbackTick;

constexpr UINT kWindowActionMessage = WM_APP + 100;
constexpr UINT kWindowActionMessageEnd = kWindowActionMessage + 64;
bool PostWindowAction(HWND hWnd, WindowAction action, POINT pt) {
    if (action == WindowAction::None || !CanActOnRootWindow(hWnd)) return false;
    return PostThreadMessage(GetCurrentThreadId(),
                             kWindowActionMessage + (UINT)action, (WPARAM)hWnd,
                             MAKELPARAM((WORD)(short)pt.x, (WORD)(short)pt.y));
}

// Runs for mouse input before it's routed anywhere, which is the only point at
// which a press can be taken away from composition hosted content. Moves are
// never swallowed: that would stop the cursor.
LRESULT CALLBACK LowLevelMouseProc(int nCode, WPARAM wParam, LPARAM lParam) {
    auto hookScope = HookRefCountScope();

    if (nCode != HC_ACTION || g_uninitializing) {
        return CallNextHookEx(nullptr, nCode, wParam, lParam);
    }

    const MSLLHOOKSTRUCT* ms = (const MSLLHOOKSTRUCT*)lParam;
    g_llLastCallbackPt = ms->pt;
    g_llLastCallbackTick = GetTickCount();

    if (ms->dwExtraInfo == kOwnInputExtraInfo ||
        ms->dwExtraInfo == swm::kFocusInputExtraInfo) {
        return CallNextHookEx(nullptr, nCode, wParam, lParam);
    }

    // Focus can move away while the keys are held, e.g. Alt+Tab, and their
    // release then goes to another process. Drop the hook here instead of
    // keeping it for the rest of the process's life.
    RemoveLowLevelMouseHookIfIdle();

    bool down;
    int button = ButtonOfMessage((UINT)wParam, HIWORD(ms->mouseData), &down);
    if (button) swm::g_lastMouseButtonTick = GetTickCount64();
    if (button && down) {
        // A press of the drag's button again means its release was missed.
        if (button == g_llButton) {
            ResetLowLevelDragState();
        } else if (button == VK_RBUTTON && g_llRootWnd && g_llDragging &&
                   !IsSizeCommand(g_llCommand)) {
            // Same as AltSnap: while a window is being moved, the right button
            // toggles its maximized state. The drag ends with the toggle, as
            // the moves which follow it would drag the window off the fitted
            // state the toggle leaves. The Alt release of the drag is kept
            // from reaching the window, which would open its menu.
            HWND hRootWnd = g_llRootWnd;
            if (PostWindowAction(hRootWnd, WindowAction::Maximize,
                                 ToLogicalPoint(ms->pt))) {
                g_swallowedPress = GetAsyncKeyState(VK_MENU) < 0;
                ResetLowLevelDragState();
                Wh_Log(L"Right button while moving %08X: toggled the "
                       L"maximized state",
                       (DWORD)(ULONG_PTR)hRootWnd);
                return 1;
            }
        }

        if (!g_llRootWnd && OnLowLevelButtonDown(ms, button)) {
            return 1;
        }
    } else if (button && button == g_llButton) {
        // The reset goes first: it closes the overlay, if the delay put one
        // up, with a message queued ahead of the replay, which would
        // otherwise land on it.
        bool dragging = g_llDragging;
        HWND root = g_llRootWnd;
        ResetLowLevelDragState();
        if (!dragging) {
            if (button == VK_RBUTTON &&
                PostWindowAction(root, g_settings.rightClickAction,
                                 ToLogicalPoint(ms->pt))) {
                g_swallowedPress = GetAsyncKeyState(VK_MENU) < 0;
            } else {
                PostReplayPress(button, true);
            }
        }

        return 1;
    } else if (wParam == WM_MOUSEMOVE && g_llRootWnd) {
        POINT pt = ToLogicalPoint(ms->pt);

        DWORD delay = TriggerOfCommand(g_llCommand).delay;

        if (g_llDragging || !IsPastDragThreshold(g_llDownPt, pt)) {
            PostDragUpdate(pt);
        } else if (ms->time - g_llDownTime >= delay) {
            BeginLowLevelDrag(pt);
            PostDragUpdate(pt);
        } else {
            // The drag is the program's own, so the press goes back to it,
            // where the cursor is by now. The release then follows on its
            // own.
            Wh_Log(L"Moved before the drag delay elapsed, replaying the press");
            int pressButton = g_llButton;
            ResetLowLevelDragState();
            PostReplayPress(pressButton, false);
        }
    }

    return CallNextHookEx(nullptr, nCode, wParam, lParam);
}

// A hook left over from before is discarded. The release ending a drag may
// never arrive: a hook further along the chain can swallow it, and the system
// drops a hook which took too long to return. What is left then keeps the
// hook, or a dead handle, in place for good. The drag state it leaves behind
// is cleared by the next installation, on the thread which then owns it.
void RemoveLowLevelMouseHook() {
    std::lock_guard<std::mutex> guard(g_lowLevelMouseHookMutex);

    if (g_lowLevelMouseHook) {
        UnhookWindowsHookEx(g_lowLevelMouseHook);
        g_lowLevelMouseHook = nullptr;
    }
}

// Runs on the hook's own thread.
void InstallLowLevelMouseHookOnThisThread() {
    // Outside the lock, the loader being out of bounds while it's held.
    HMODULE module = GetModuleHandle(nullptr);

    SetThreadDpiAwarenessContext(g_lowLevelMouseHookDpiContext);

    std::lock_guard<std::mutex> guard(g_lowLevelMouseHookMutex);
    if (g_lowLevelMouseHook || g_uninitializing) {
        return;
    }

    // With no hook there's no thread the drag state belongs to, so whatever a
    // discarded hook left behind is cleared here, before the callbacks of the
    // new one start reading it on this thread.
    ResetLowLevelDragState();

    g_lowLevelMouseHook =
        SetWindowsHookEx(WH_MOUSE_LL, LowLevelMouseProc, module, 0);
    if (g_lowLevelMouseHook) {
        g_lowLevelMouseHookThreadId = GetCurrentThreadId();
    } else {
        Wh_Log(L"SetWindowsHookEx(WH_MOUSE_LL) error: %u", GetLastError());
    }
}

// The thread installs the hook as it starts and again whenever asked. Its
// messages go through the mod's message hook like any thread's, which handles
// the drag updates, timers and replays posted to it.
HHOOK g_globalAltHook;
LRESULT CALLBACK GlobalAltProc(int code, WPARAM message, LPARAM data) {
    if (code == HC_ACTION) {
        auto key = reinterpret_cast<KBDLLHOOKSTRUCT*>(data);
        if (swm::OnResizeKey(message, key)) return 1;
        // Never swallow the Alt release: Windows would then keep Alt held,
        // which eats typing and makes plain drags act as Alt drags. A dummy
        // key tap ahead of the real release stops the window menu opening.
        // Input sent from the callback is processed before the release.
        bool altKey = key->vkCode == VK_LMENU || key->vkCode == VK_RMENU;
        bool injected = key->flags & LLKHF_INJECTED;
        if (altKey && !injected && (message == WM_KEYDOWN || message == WM_SYSKEYDOWN)) {
            g_swallowedPress = false;
        } else if (altKey && (message == WM_KEYUP || message == WM_SYSKEYUP) &&
                   g_swallowedPress.exchange(false)) {
            INPUT in[2]{};
            for (auto& i : in) {
                i.type = INPUT_KEYBOARD;
                i.ki.wVk = kMenuMaskKey;
                i.ki.dwExtraInfo = kOwnInputExtraInfo;
            }
            in[1].ki.dwFlags = KEYEVENTF_KEYUP;
            SendInput(2, in, sizeof(INPUT));
        }
    }
    return CallNextHookEx(nullptr, code, message, data);
}

DWORD WINAPI LowLevelMouseHookThreadProc(void*) {
    MSG msg;
    PeekMessage(&msg, nullptr, WM_USER, WM_USER, PM_NOREMOVE);

    InstallLowLevelMouseHookOnThisThread();
    std::array<bool, kHotkeyActions.size()> registered{};
    auto registerActions = [&] {
        if (swm::IsPaused()) return;
        for (size_t i = 0; i < registered.size(); ++i) {
            if (registered[i] || !g_settings.hotkeys[i].key) continue;
            DWORD held = g_settings.hotkeys[i].modifiers;
            UINT mods = ((held & kModifierCtrl) ? MOD_CONTROL : 0) |
                        ((held & kModifierAlt) ? MOD_ALT : 0) |
                        ((held & kModifierShift) ? MOD_SHIFT : 0) |
                        ((held & kModifierWin) ? MOD_WIN : 0);
            registered[i] = RegisterHotKey(nullptr, 0x6000 + i, mods | MOD_NOREPEAT,
                                            g_settings.hotkeys[i].key);
        }
    };
    UINT_PTR retry = 0;
    if (g_globalInput) {
        g_globalAltHook = SetWindowsHookEx(WH_KEYBOARD_LL, GlobalAltProc, GetModuleHandle(nullptr), 0);
        registerActions();
        swm::RegisterModeKeys();
        retry = SetTimer(nullptr, 0, 2000, nullptr);
    }
    auto unregisterActions = [&] {
        for (size_t i = 0; i < registered.size(); ++i) {
            if (registered[i]) UnregisterHotKey(nullptr, 0x6000 + i);
            registered[i] = false;
        }
    };

    while (GetMessage(&msg, nullptr, 0, 0) > 0) {
        if (g_globalInput) {
            if (msg.message == WM_APP + 91 && !msg.hwnd) {
                ResetLowLevelDragState();
                swm::LeaveResizeMode();
                unregisterActions();
                swm::UnregisterModeKeys();
                LoadSettings();
                registerActions();
                swm::RegisterModeKeys();
                continue;
            }
            if (msg.message == swm::kPauseChangedMessage && !msg.hwnd) {
                if (swm::IsPaused()) unregisterActions();
                else registerActions();
                swm::RegisterModeKeys();
                continue;
            }
            if (swm::OnLowLevelThreadMessage(msg)) continue;
            if (msg.message == WM_TIMER && !msg.hwnd && msg.wParam == retry) {
                registerActions();
                swm::RegisterModeKeys();
                // The system drops a low level hook that once ran too long,
                // without telling it. The pointer having moved with no
                // callback for a while means that happened: hook again.
                POINT now{};
                // A drag whose button is no longer down is stale too.
                bool stale = !g_llRootWnd || GetAsyncKeyState(g_llButton) >= 0;
                if (stale && GetPhysicalCursorPos(&now) &&
                    (now.x != g_llLastCallbackPt.x || now.y != g_llLastCallbackPt.y) &&
                    GetTickCount() - g_llLastCallbackTick > 2000) {
                    Wh_Log(L"Mouse hook went quiet, reinstalling");
                    ResetLowLevelDragState();
                    RemoveLowLevelMouseHook();
                    InstallLowLevelMouseHookOnThisThread();
                    if (g_globalAltHook) UnhookWindowsHookEx(g_globalAltHook);
                    g_globalAltHook = SetWindowsHookEx(WH_KEYBOARD_LL, GlobalAltProc,
                                                       GetModuleHandle(nullptr), 0);
                    g_llLastCallbackPt = now;
                    g_llLastCallbackTick = GetTickCount();
                }
                continue;
            }
            if (msg.message == WM_HOTKEY && !msg.hwnd &&
                msg.wParam >= 0x6000 && msg.wParam < 0x6000 + registered.size()) {
                POINT pt{};
                GetCursorPos(&pt);
                RunWindowAction(GetAncestor(GetForegroundWindow(), GA_ROOT),
                                kHotkeyActions[msg.wParam - 0x6000], pt);
                continue;
            }
            OnMessageRemoved(&msg);
        }
        if (!msg.hwnd && msg.message >= kWindowActionMessage &&
            msg.message < kWindowActionMessageEnd) {
            POINT pt{(short)LOWORD(msg.lParam), (short)HIWORD(msg.lParam)};
            RunWindowAction((HWND)msg.wParam,
                            (WindowAction)(msg.message - kWindowActionMessage), pt);
            continue;
        }
        if (!msg.hwnd && msg.message == kInstallLowLevelMouseHookMessage) {
            InstallLowLevelMouseHookOnThisThread();
            continue;
        }

        DispatchMessage(&msg);
    }

    {
        std::lock_guard<std::mutex> guard(g_lowLevelMouseHookMutex);
        if (g_lowLevelMouseHook &&
            GetCurrentThreadId() == g_lowLevelMouseHookThreadId) {
            UnhookWindowsHookEx(g_lowLevelMouseHook);
            g_lowLevelMouseHook = nullptr;
        }
    }

    if (g_globalInput) {
        swm::LeaveResizeMode();
        swm::UnregisterModeKeys();
    }
    if (g_globalAltHook) UnhookWindowsHookEx(g_globalAltHook);
    if (retry) KillTimer(nullptr, retry);
    for (size_t i = 0; i < registered.size(); ++i)
        if (registered[i]) UnregisterHotKey(nullptr, 0x6000 + i);
    ResetLowLevelDragState();
    return 0;
}

// Called by whichever thread retrieves the trigger's keys, which takes its DPI
// awareness to the hook's thread: the hook places windows in its coordinates.
constexpr wchar_t kHelperMutexName[] = L"windhawk-seamless-window-manager-global";

void InstallLowLevelMouseHookIfNeeded() {
    if (!g_globalInput) {
        HANDLE helper = OpenMutex(SYNCHRONIZE, FALSE, kHelperMutexName);
        if (helper) { CloseHandle(helper); return; }
        // An older helper's mutex was admin-only; denied still means it runs.
        if (GetLastError() == ERROR_ACCESS_DENIED) return;
    }
    DPI_AWARENESS_CONTEXT dpiContext = GetThreadDpiAwarenessContext();

    std::lock_guard<std::mutex> guard(g_lowLevelMouseHookMutex);
    if (g_lowLevelMouseHook || g_uninitializing) {
        return;
    }

    g_lowLevelMouseHookDpiContext = dpiContext;

    if (g_lowLevelMouseHookThread) {
        // Fails until the thread's queue exists, the thread then installing
        // the hook as it starts.
        PostThreadMessage(g_lowLevelMouseHookOwnThreadId,
                          kInstallLowLevelMouseHookMessage, 0, 0);
        return;
    }

    g_lowLevelMouseHookThread =
        CreateThread(nullptr, 0, LowLevelMouseHookThreadProc, nullptr, 0,
                     &g_lowLevelMouseHookOwnThreadId);
    if (!g_lowLevelMouseHookThread) {
        Wh_Log(L"CreateThread error: %u", GetLastError());
    }
}

void StopLowLevelMouseHookThread() {
    HANDLE thread;
    DWORD threadId;
    {
        std::lock_guard<std::mutex> guard(g_lowLevelMouseHookMutex);
        thread = g_lowLevelMouseHookThread;
        threadId = g_lowLevelMouseHookOwnThreadId;
        g_lowLevelMouseHookThread = nullptr;
    }

    if (!thread) {
        return;
    }

    while (WaitForSingleObject(thread, 0) == WAIT_TIMEOUT &&
           !PostThreadMessage(threadId, WM_QUIT, 0, 0)) {
        Sleep(10);
    }

    WaitForSingleObject(thread, INFINITE);
    CloseHandle(thread);
}

void RemoveLowLevelMouseHookIfIdle() {
    if (g_globalInput) return;
    std::lock_guard<std::mutex> guard(g_lowLevelMouseHookMutex);

    // Only the hook's thread can tell whether a press is being held or a drag
    // is in progress, which keep the hook, as do the keys and, for a keyless
    // trigger, this process being the foreground one. A key release or a
    // deactivation retrieved elsewhere leaves the removal to the callback,
    // which checks on the next mouse event.
    if (!g_lowLevelMouseHook ||
        GetCurrentThreadId() != g_lowLevelMouseHookThreadId || g_llRootWnd ||
        IsAnyModifierTriggerHeld(HeldModifiers(GetAsyncKeyState)) ||
        ShouldHoldKeylessHook()) {
        return;
    }

    UnhookWindowsHookEx(g_lowLevelMouseHook);
    g_lowLevelMouseHook = nullptr;
}

void RemoveWinKeyMaskHook() {
    std::lock_guard<std::mutex> guard(g_winKeyMaskHookMutex);

    if (g_winKeyMaskHook) {
        UnhookWindowsHookEx(g_winKeyMaskHook);
        g_winKeyMaskHook = nullptr;
    }
}

// Sends the release again behind a tap of the mask key. Returns whether the
// original is to be swallowed, which it is only with the whole sequence sent:
// short of the release the key would stay down, e.g. with SendInput refused
// while an elevated window is in the foreground.
bool ResendWinKeyReleaseMasked(const KBDLLHOOKSTRUCT* kbd) {
    INPUT inputs[3]{};
    inputs[0].type = INPUT_KEYBOARD;
    inputs[0].ki.wVk = kMenuMaskKey;
    inputs[1].type = INPUT_KEYBOARD;
    inputs[1].ki.wVk = kMenuMaskKey;
    inputs[1].ki.dwFlags = KEYEVENTF_KEYUP;
    // The Win keys are extended keys, and a release without the flag may not
    // register, leaving the key down.
    inputs[2].type = INPUT_KEYBOARD;
    inputs[2].ki.wVk = (WORD)kbd->vkCode;
    inputs[2].ki.wScan = (WORD)kbd->scanCode;
    inputs[2].ki.dwFlags = KEYEVENTF_KEYUP;
    if (kbd->flags & LLKHF_EXTENDED) {
        inputs[2].ki.dwFlags |= KEYEVENTF_EXTENDEDKEY;
    }

    if (SendInput(ARRAYSIZE(inputs), inputs, sizeof(inputs[0])) !=
        ARRAYSIZE(inputs)) {
        Wh_Log(L"SendInput error: %u", GetLastError());
        return false;
    }

    return true;
}

// Keyboard input sent from within the callback is processed on the spot, the
// hook included, which is where the injected flag matters.
LRESULT CALLBACK WinKeyMaskProc(int nCode, WPARAM wParam, LPARAM lParam) {
    auto hookScope = HookRefCountScope();

    if (nCode != HC_ACTION || g_uninitializing) {
        return CallNextHookEx(nullptr, nCode, wParam, lParam);
    }

    const KBDLLHOOKSTRUCT* kbd = (const KBDLLHOOKSTRUCT*)lParam;
    if ((kbd->vkCode != VK_LWIN && kbd->vkCode != VK_RWIN) ||
        (kbd->flags & LLKHF_INJECTED)) {
        return CallNextHookEx(nullptr, nCode, wParam, lParam);
    }

    if (wParam == WM_KEYUP || wParam == WM_SYSKEYUP) {
        Wh_Log(L"Masking the Win release of a drag");
        bool swallow = ResendWinKeyReleaseMasked(kbd);
        RemoveWinKeyMaskHook();
        if (swallow) {
            return 1;
        }
    } else if (GetAsyncKeyState(kbd->vkCode) >= 0) {
        // The key state is updated once the hook lets the event through, so
        // the key shows up for an auto repeat and not for a new hold, which
        // means the release the hook was installed for went by unseen.
        RemoveWinKeyMaskHook();
    }

    return CallNextHookEx(nullptr, nCode, wParam, lParam);
}

// The Start menu is armed by every auto repeat of the held key, so the mask
// has to go right before the release, and the hook is installed on the drag
// thread to see it. One left over from an earlier drag is replaced.
void InstallWinKeyMaskHook() {
    // Outside the lock, the loader being out of bounds while it's held.
    HMODULE module = GetModuleHandle(nullptr);

    std::lock_guard<std::mutex> guard(g_winKeyMaskHookMutex);
    if (g_uninitializing) {
        return;
    }

    if (g_winKeyMaskHook) {
        UnhookWindowsHookEx(g_winKeyMaskHook);
    }

    g_winKeyMaskHook =
        SetWindowsHookEx(WH_KEYBOARD_LL, WinKeyMaskProc, module, 0);
    if (g_winKeyMaskHook) {
        g_winKeyMaskHookThreadId = GetCurrentThreadId();
    } else {
        Wh_Log(L"SetWindowsHookEx(WH_KEYBOARD_LL) error: %u", GetLastError());
    }
}

// For a drag started with a trigger which has Win among its keys.
void MaskWinKeyReleaseIfNeeded(UINT command) {
    const TriggerSettings& trigger = TriggerOfCommand(command);
    if ((trigger.modifiers & kModifierWin) &&
        (HeldModifiers(GetAsyncKeyState) & kModifierWin)) {
        InstallWinKeyMaskHook();
    }
}

void SetThreadHooksIfNeeded() {
    if (g_threadHooksAttempted) {
        return;
    }

    g_threadHooksAttempted = true;

    std::unique_lock<std::mutex> guard(g_allThreadHooksMutex);
    if (g_uninitializing) {
        return;
    }

    DWORD dwThreadId = GetCurrentThreadId();

    g_getMessageHook =
        SetWindowsHookEx(WH_GETMESSAGE, GetMsgProc, nullptr, dwThreadId);
    if (g_getMessageHook) {
        g_allThreadHooks.insert(g_getMessageHook);
    } else {
        Wh_Log(L"SetWindowsHookEx(WH_GETMESSAGE) error for thread %u: %u",
               dwThreadId, GetLastError());
    }

    g_callWndProcHook =
        SetWindowsHookEx(WH_CALLWNDPROC, CallWndProc, nullptr, dwThreadId);
    if (g_callWndProcHook) {
        g_allThreadHooks.insert(g_callWndProcHook);
    } else {
        Wh_Log(L"SetWindowsHookEx(WH_CALLWNDPROC) error for thread %u: %u",
               dwThreadId, GetLastError());
    }

    if (g_getMessageHook && g_callWndProcHook) {
        Wh_Log(L"SetWindowsHookEx succeeded for thread %u", dwThreadId);
    }

    if (g_getMessageHook) {
        // The windows the thread has by now, later ones are marked as created.
        EnumThreadWindows(
            dwThreadId,
            [](HWND hWnd, LPARAM) WINAPI -> BOOL {
                MarkHookedWindow(hWnd);
                return TRUE;
            },
            0);
    }

    guard.unlock();

    // A process which is the foreground one already sees no activation to put
    // the hook of a keyless trigger up on.
    if (ShouldHoldKeylessHook()) {
        InstallLowLevelMouseHookIfNeeded();
    }
}

using NtUserGetMessage_t = BOOL(WINAPI*)(MSG* pMsg,
                                         HWND hWnd,
                                         UINT wMsgFilterMin,
                                         UINT wMsgFilterMax);
NtUserGetMessage_t NtUserGetMessage_Original;
BOOL WINAPI NtUserGetMessage_Hook(MSG* pMsg,
                                  HWND hWnd,
                                  UINT wMsgFilterMin,
                                  UINT wMsgFilterMax) {
    SetThreadHooksIfNeeded();

    [[clang::musttail]] return NtUserGetMessage_Original(
        pMsg, hWnd, wMsgFilterMin, wMsgFilterMax);
}

// The last parameter is a flags value which user32 sets from the calling
// PeekMessage variant.
using NtUserPeekMessage_t = BOOL(WINAPI*)(MSG* pMsg,
                                          HWND hWnd,
                                          UINT wMsgFilterMin,
                                          UINT wMsgFilterMax,
                                          UINT wRemoveMsg,
                                          UINT flags);
NtUserPeekMessage_t NtUserPeekMessage_Original;
BOOL WINAPI NtUserPeekMessage_Hook(MSG* pMsg,
                                   HWND hWnd,
                                   UINT wMsgFilterMin,
                                   UINT wMsgFilterMax,
                                   UINT wRemoveMsg,
                                   UINT flags) {
    SetThreadHooksIfNeeded();

    [[clang::musttail]] return NtUserPeekMessage_Original(
        pMsg, hWnd, wMsgFilterMin, wMsgFilterMax, wRemoveMsg, flags);
}

BOOL WINAPI DragDllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpReserved) {
    switch (fdwReason) {
        case DLL_PROCESS_ATTACH:
            break;

        case DLL_THREAD_ATTACH:
            break;

        case DLL_THREAD_DETACH:
            if (g_getMessageHook || g_callWndProcHook) {
                std::lock_guard<std::mutex> guard(g_allThreadHooksMutex);

                for (HHOOK hook : {g_getMessageHook, g_callWndProcHook}) {
                    auto it = g_allThreadHooks.find(hook);
                    if (it != g_allThreadHooks.end()) {
                        UnhookWindowsHookEx(hook);
                        g_allThreadHooks.erase(it);
                    }
                }
            }

            // The low level hooks and the overlay go away with their
            // thread. The drag state is this thread's to clear, the hook
            // being this thread's.
            {
                std::lock_guard<std::mutex> guard(g_lowLevelMouseHookMutex);

                if (g_lowLevelMouseHook &&
                    GetCurrentThreadId() == g_lowLevelMouseHookThreadId) {
                    g_lowLevelMouseHook = nullptr;
                    g_llRootWnd = nullptr;
                    g_llButton = 0;
                    g_llDragging = false;
                    g_llDragSetUp = false;
                    g_llDragUpdatePosted = false;
                    g_llDragOverlayWnd = nullptr;
                }
            }

            {
                std::lock_guard<std::mutex> guard(g_winKeyMaskHookMutex);

                if (g_winKeyMaskHook &&
                    GetCurrentThreadId() == g_winKeyMaskHookThreadId) {
                    g_winKeyMaskHook = nullptr;
                }
            }
            break;

        case DLL_PROCESS_DETACH:
            break;
    }

    return TRUE;
}

int ButtonFromSetting(PCWSTR value) {
    if (_wcsicmp(value, L"right") == 0) {
        return VK_RBUTTON;
    }
    if (_wcsicmp(value, L"middle") == 0) {
        return VK_MBUTTON;
    }
    if (_wcsicmp(value, L"x1") == 0) {
        return VK_XBUTTON1;
    }
    if (_wcsicmp(value, L"x2") == 0) {
        return VK_XBUTTON2;
    }
    return VK_LBUTTON;
}

void LoadTriggerSettings(TriggerSettings& trigger, PCWSTR name) {
    PCWSTR button = Wh_GetStringSetting(L"%ls.button", name);
    trigger.button = ButtonFromSetting(button);
    Wh_FreeStringSetting(button);

    DWORD modifiers = 0;
    if (Wh_GetIntSetting(L"%ls.ctrl", name)) {
        modifiers |= kModifierCtrl;
    }
    if (Wh_GetIntSetting(L"%ls.alt", name)) {
        modifiers |= kModifierAlt;
    }
    if (Wh_GetIntSetting(L"%ls.shift", name)) {
        modifiers |= kModifierShift;
    }
    if (Wh_GetIntSetting(L"%ls.win", name)) {
        modifiers |= kModifierWin;
    }
    trigger.modifiers = modifiers;

    trigger.delay = std::max(Wh_GetIntSetting(L"%ls.delay", name), 0);
}

void LoadActionSetting(std::atomic<WindowAction>& action, PCWSTR name) {
    PCWSTR value = Wh_GetStringSetting(L"%ls", name);
    action = ActionFromSetting(value);
    Wh_FreeStringSetting(value);
}

void ParseHotkey(PCWSTR value, int* key, DWORD* modifiers) {
    *key = 0;
    *modifiers = 0;
    if (!value || !*value) return;

    WCHAR* end = nullptr;
    unsigned long encoded = wcstoul(value, &end, 10);
    if (end != value && *end == 0 && encoded <= 0xFFFF) {
        *key = encoded & 0xFF;
        unsigned long flags = encoded >> 8;
        if (flags & MOD_ALT) *modifiers |= kModifierAlt;
        if (flags & MOD_CONTROL) *modifiers |= kModifierCtrl;
        if (flags & MOD_SHIFT) *modifiers |= kModifierShift;
        if (flags & MOD_WIN) *modifiers |= kModifierWin;
        return;
    }

    std::wstring part;
    auto parsePart = [&](const std::wstring& token) {
        if (token == L"ALT") *modifiers |= kModifierAlt;
        else if (token == L"CTRL" || token == L"CONTROL") *modifiers |= kModifierCtrl;
        else if (token == L"SHIFT") *modifiers |= kModifierShift;
        else if (token == L"WIN" || token == L"WINDOWS") *modifiers |= kModifierWin;
        else if (token.size() == 1 && token[0] >= L'A' && token[0] <= L'Z') *key = token[0];
        else if (token.size() == 1 && token[0] >= L'0' && token[0] <= L'9') *key = token[0];
        else if (token[0] == L'F' && token.size() <= 3) {
            int number = _wtoi(token.c_str() + 1);
            if (number >= 1 && number <= 24) *key = VK_F1 + number - 1;
        } else if (token == L"SPACE") *key = VK_SPACE;
        else if (token == L"TAB") *key = VK_TAB;
        else if (token == L"ESC" || token == L"ESCAPE") *key = VK_ESCAPE;
        else if (token == L"DELETE" || token == L"DEL") *key = VK_DELETE;
        else if (token == L"INSERT" || token == L"INS") *key = VK_INSERT;
        else if (token == L"HOME") *key = VK_HOME;
        else if (token == L"END") *key = VK_END;
        else if (token == L"PAGEUP" || token == L"PGUP") *key = VK_PRIOR;
        else if (token == L"PAGEDOWN" || token == L"PGDN") *key = VK_NEXT;
        else if (token == L"LEFT") *key = VK_LEFT;
        else if (token == L"RIGHT") *key = VK_RIGHT;
        else if (token == L"UP") *key = VK_UP;
        else if (token == L"DOWN") *key = VK_DOWN;
    };
    for (PCWSTR p = value;; p++) {
        if (*p == L'+' || *p == 0) {
            if (!part.empty()) parsePart(part);
            part.clear();
            if (!*p) break;
        } else if (!iswspace(*p)) {
            part += (WCHAR)towupper(*p);
        }
    }
    // A shortcut without modifiers would intercept ordinary typing.
    if (!*modifiers) *key = 0;
}

void LoadSettings() {
    LoadTriggerSettings(g_settings.moveTrigger, L"moveTrigger");
    LoadTriggerSettings(g_settings.sizeTrigger, L"sizeTrigger");
    g_settings.dragWindowsWithoutTitleBar =
        Wh_GetIntSetting(L"dragWindowsWithoutTitleBar");
    g_settings.explorerTitleStripDrag =
        Wh_GetIntSetting(L"explorerTitleStripDrag");
    g_settings.sizeWindowsWithoutSizingBorder =
        Wh_GetIntSetting(L"sizeWindowsWithoutSizingBorder");
    LoadActionSetting(g_settings.middleAction, L"middleAction");
    LoadActionSetting(g_settings.rightClickAction, L"rightClickAction");
    LoadActionSetting(g_settings.x1Action, L"x1Action");
    LoadActionSetting(g_settings.x2Action, L"x2Action");
    LoadActionSetting(g_settings.leftDoubleAction, L"leftDoubleAction");
    LoadActionSetting(g_settings.middleDoubleAction, L"middleDoubleAction");
    LoadActionSetting(g_settings.rightDoubleAction, L"rightDoubleAction");
    for (size_t i = 0; i < kHotkeyNames.size(); i++) {
        PCWSTR value = Wh_GetStringSetting(L"%ls", kHotkeyNames[i]);
        int key;
        DWORD modifiers;
        ParseHotkey(value, &key, &modifiers);
        Wh_FreeStringSetting(value);
        g_settings.hotkeys[i].key = key;
        g_settings.hotkeys[i].modifiers = modifiers;
    }
    snapCommander::LoadIgnoreRules();
}

BOOL ModInit() {
    Wh_Log(L">");

    LoadSettings();

    HMODULE win32uModule = GetModuleHandle(L"win32u.dll");
    if (!win32uModule) {
        // Apps whose exe has no user32 in its import table (Electron 43
        // bootstrappers such as Tidal 2.47+) reach this point before
        // anything has mapped win32u, and bailing here would leave them
        // without the drag hooks for good. Load it instead: it is a
        // KnownDLL the process maps again on its own when user32 arrives.
        win32uModule = LoadLibrary(L"win32u.dll");
    }
    if (!win32uModule) {
        Wh_Log(L"win32u.dll isn't loaded");
        return FALSE;
    }

    void* pNtUserGetMessage =
        (void*)GetProcAddress(win32uModule, "NtUserGetMessage");
    void* pNtUserPeekMessage =
        (void*)GetProcAddress(win32uModule, "NtUserPeekMessage");
    if (!pNtUserGetMessage || !pNtUserPeekMessage) {
        Wh_Log(L"NtUserGetMessage or NtUserPeekMessage not found");
        return FALSE;
    }

    Wh_SetFunctionHook(pNtUserGetMessage, (void*)NtUserGetMessage_Hook,
                       (void**)&NtUserGetMessage_Original);
    Wh_SetFunctionHook(pNtUserPeekMessage, (void*)NtUserPeekMessage_Hook,
                       (void**)&NtUserPeekMessage_Original);

    // Lets a lower integrity process, e.g. a UWP app, request a drag of a root
    // window in this process.
    ChangeWindowMessageFilter(g_sizeMoveRequestMessage, MSGFLT_ADD);
    ChangeWindowMessageFilter(g_pinRequestMessage, MSGFLT_ADD);

    if (IsExplorerProcess()) {
        EnumWindows(
            [](HWND hWnd, LPARAM) WINAPI -> BOOL {
                DWORD processId = 0;
                GetWindowThreadProcessId(hWnd, &processId);
                if (processId == GetCurrentProcessId()) {
                    StartStripHookThreadIfNeeded(hWnd);
                }
                return TRUE;
            },
            0);
    }

    return TRUE;
}

void ModUninit() {
    Wh_Log(L">");

    g_uninitializing = true;

    StopStripHookThread();

    std::unordered_set<HWND> subclassedWindows;
    {
        std::lock_guard<std::mutex> guard(g_subclassedWindowsMutex);
        subclassedWindows = std::move(g_subclassedWindows);
        g_subclassedWindows.clear();
    }

    for (HWND hWnd : subclassedWindows) {
        SendMessage(hWnd, g_unsubclassRegisteredMessage, 0, 0);
    }

    {
        std::lock_guard<std::mutex> guard(g_allThreadHooksMutex);

        for (HHOOK hook : g_allThreadHooks) {
            UnhookWindowsHookEx(hook);
        }

        g_allThreadHooks.clear();
    }

    ChangeWindowMessageFilter(g_sizeMoveRequestMessage, MSGFLT_REMOVE);
    ChangeWindowMessageFilter(g_pinRequestMessage, MSGFLT_REMOVE);

    {
        std::lock_guard<std::mutex> guard(g_lowLevelMouseHookMutex);

        if (g_lowLevelMouseHook) {
            UnhookWindowsHookEx(g_lowLevelMouseHook);
            g_lowLevelMouseHook = nullptr;
        }
    }

    RemoveWinKeyMaskHook();

    StopLowLevelMouseHookThread();

    while (g_hookRefCount > 0) {
        Sleep(200);
    }

    // With the hooks gone, no window is marked from here on.
    EnumWindows(
        [](HWND hWnd, LPARAM) WINAPI -> BOOL {
            DWORD processId = 0;
            GetWindowThreadProcessId(hWnd, &processId);
            if (processId == GetCurrentProcessId()) {
                RemoveProp(hWnd, kHookedWindowProp);
            }
            return TRUE;
        },
        0);

    // The class may outlive the window, and is then found in place next time.
    DestroyDragOverlay();
    UnregisterClass(kDragOverlayClassName, GetModuleHandle(nullptr));
}

void ModSettingsChanged() {
    Wh_Log(L">");

    LoadSettings();
}
}  // namespace altSnapDrag

//////// snap ////////
namespace snapCommander {





enum class Action {
    None,
    LeftHalf,
    RightHalf,
    TopHalf,
    BottomHalf,
    CenterHalf,
    TopLeft,
    TopRight,
    BottomLeft,
    BottomRight,
    Maximize,
    AlmostMaximize,
    Center,
    Minimize,
    NextDisplay,
    PreviousDisplay,
    MakeSmaller,
    MakeLarger,
    RestorePrevious,
};

constexpr UINT MOD_F_ALT = 0x1;
constexpr UINT MOD_F_CTRL = 0x2;
constexpr UINT MOD_F_SHIFT = 0x4;
constexpr UINT MOD_F_WIN = 0x8;

constexpr int ACTION_COUNT = 18;

// Posted to the hook thread after settings load, so it can re-register the hotkeys
// and install/remove the auto-snap WinEvent hook (both must run on that thread).
constexpr UINT WM_APP_SETTINGS_CHANGED = WM_APP + 1;

// Gaps (in pixels) left on each side of a snapped window.
static int g_gapTop = 0;
static int g_gapBottom = 0;
static int g_gapLeft = 0;
static int g_gapRight = 0;

// How the gap on a window side is sized depending on whether that side touches a
// screen edge (outer) or borders another tiled window (inner divider):
//   Even   - outer sides get the full gap, inner sides get half, so two adjacent
//            windows show the same total gap as a single window at the edge.
//   Full   - every side gets the full gap (adjacent windows show a doubled gap).
//   Screen - only sides touching a screen edge get a gap; inner sides get none.
enum class GapMode { Even, Full, Screen };
static GapMode g_gapMode = GapMode::Even;

// Gaps as a percent of the work area (left and right of its width, top and
// bottom of its height) instead of pixels, and pixel gaps scaled by the
// monitor's DPI. Almost maximize may use its own gap on all four sides; -1
// means it uses the gaps above.
static bool g_gapUnitPercent = false;
static bool g_gapScaleDpi = false;
static int g_almostMaxGap = -1;

// Target size for the Center action; 0 means keep the window's current size.
static int g_centerWidth = 0;
static int g_centerHeight = 0;

// Step (percentage of the monitor work area) by which Make smaller / larger
// grow or shrink the active window.
static int g_resizeStepPercent = 5;

// Per-action trigger key and required modifier mask; both indexes line up with
// g_actionByIndex below. A key of 0 means the action is unbound. The mask uses the
// MOD_F_* bits, which deliberately match RegisterHotKey's MOD_ALT/CONTROL/SHIFT/WIN
// values, so it can be passed straight to RegisterHotKey as the fsModifiers.
static UINT g_actionKeys[ACTION_COUNT] = {};
static UINT g_actionMods[ACTION_COUNT] = {};
static const Action g_actionByIndex[ACTION_COUNT] = {
    Action::LeftHalf,    Action::RightHalf,     Action::TopHalf,
    Action::BottomHalf,  Action::CenterHalf,    Action::TopLeft,
    Action::TopRight,    Action::BottomLeft,    Action::BottomRight,
    Action::Maximize,    Action::AlmostMaximize, Action::Center,
    Action::Minimize,    Action::NextDisplay,    Action::PreviousDisplay,
    Action::MakeSmaller, Action::MakeLarger,     Action::RestorePrevious,
};

// Setting names for each action's shortcut, lined up with g_actionByIndex. Used both
// to read the bindings and to name a binding in the log when it can't be registered.
static const PCWSTR g_keyNames[ACTION_COUNT] = {
    L"shortcuts.keyLeftHalf",       L"shortcuts.keyRightHalf",
    L"shortcuts.keyTopHalf",        L"shortcuts.keyBottomHalf",
    L"shortcuts.keyCenterHalf",     L"shortcuts.keyTopLeft",
    L"shortcuts.keyTopRight",       L"shortcuts.keyBottomLeft",
    L"shortcuts.keyBottomRight",    L"shortcuts.keyMaximize",
    L"shortcuts.keyAlmostMaximize", L"shortcuts.keyCenter",
    L"shortcuts.keyMinimize",       L"shortcuts.keyNextDisplay",
    L"shortcuts.keyPrevDisplay",    L"shortcuts.keySmaller",
    L"shortcuts.keyLarger",         L"shortcuts.keyRestore",
};

// Which hotkey ids are currently registered. Touched only on the hook thread.
static bool g_hotkeyRegistered[ACTION_COUNT] = {};

// Window placement captured before the first snap, so RestorePrevious can revert.
// Accessed only from the worker thread, so no synchronization is needed.
static std::unordered_map<HWND, WINDOWPLACEMENT> g_savedPlacements;

// App rules: a window matching the app names, title and class gets the rule's
// placement, keep-on-top and opacity, or is left alone completely (ignore).
enum class MatchMode { Contains, Equals, Regex, NotRegex };
enum class ApplyWhen { Open, New, Title };
struct AppRule {
    std::vector<std::wstring> executables;  // Lowercase; * and ? are wildcards.
    std::wstring title;  // Lowercase for Contains and Equals.
    std::wstring cls;
    MatchMode mode = MatchMode::Contains;
    std::shared_ptr<const std::wregex> titlePattern;
    std::shared_ptr<const std::wregex> clsPattern;
    Action action = Action::None;
    bool ignore = false;
    bool noResize = false;  // Move the window into the region but keep its size.
    ApplyWhen when = ApplyWhen::Open;
    bool onTop = false;
    BYTE alpha = 255;
};
using RuleList = std::vector<AppRule>;
// Swapped whole on a settings change, so readers keep a consistent list.
static std::shared_ptr<const RuleList> g_appRules;
static std::mutex g_appRulesMutex;
// Ignore rules only. Read by every process the mod runs in.
static std::shared_ptr<const RuleList> g_ignoreRules;
static std::mutex g_ignoreRulesMutex;
// One bit per rule index already applied to a window, so a rule runs once per
// window however many show or title events it raises.
static std::unordered_map<HWND, uint64_t> g_ruleHandledWindows;
static std::mutex g_ruleHandledMutex;
constexpr size_t kMaxRules = 64;

static std::shared_ptr<const RuleList> GetRules() {
    std::lock_guard<std::mutex> lock(g_appRulesMutex);
    return g_appRules;
}

static HWINEVENTHOOK g_winEventHook = nullptr;
static HWINEVENTHOOK g_nameChangeHook = nullptr;
static HANDLE g_hookThread = nullptr;
static DWORD g_hookThreadId = 0;
static HANDLE g_hookReadyEvent = nullptr;

// Work queue drained by the worker thread; producers are the hotkey/window-event
// hooks, so it is guarded by a mutex. A "cleanup" item carries no action and just
// tells the worker (the sole owner of g_savedPlacements) to drop a destroyed window.
struct WorkItem {
    HWND hWnd;
    Action action;
    bool noResize;
    bool cleanup;
    bool nudge = false;
    bool move = false;
    int dx = 0;
    int dy = 0;
};
static std::deque<WorkItem> g_workQueue;
static std::mutex g_workQueueMutex;

static HANDLE g_workerThread = nullptr;
static HANDLE g_workEvent = nullptr;
static std::atomic<bool> g_quit{false};

static void EnqueueWork(HWND hWnd, Action action, bool noResize = false) {
    if (!hWnd || action == Action::None) {
        return;
    }
    {
        std::lock_guard<std::mutex> lock(g_workQueueMutex);
        g_workQueue.push_back({hWnd, action, noResize, false});
    }
    SetEvent(g_workEvent);
}

// Ask the worker thread to forget a window's saved placement once it's destroyed,
// so the map doesn't grow without bound and a recycled HWND can't inherit a stale
// placement.
static void EnqueueCleanup(HWND hWnd) {
    if (!hWnd) {
        return;
    }
    {
        std::lock_guard<std::mutex> lock(g_workQueueMutex);
        g_workQueue.push_back({hWnd, Action::None, false, true});
    }
    SetEvent(g_workEvent);
}

// A keyboard resize step for the worker: dx and dy are -1, 0 or 1.
void EnqueueNudge(HWND hWnd, int dx, int dy, bool move) {
    if (!hWnd || !g_workEvent) {
        return;
    }
    {
        std::lock_guard<std::mutex> lock(g_workQueueMutex);
        WorkItem item{hWnd, Action::None, false, false};
        item.nudge = true;
        item.move = move;
        item.dx = dx;
        item.dy = dy;
        g_workQueue.push_back(item);
    }
    SetEvent(g_workEvent);
}

static std::wstring ToLower(std::wstring s) {
    for (auto& c : s) {
        c = (wchar_t)towlower(c);
    }
    return s;
}

static std::wstring Trim(const std::wstring& s) {
    size_t start = 0;
    while (start < s.size() && iswspace(s[start])) {
        start++;
    }
    size_t end = s.size();
    while (end > start && iswspace(s[end - 1])) {
        end--;
    }
    return s.substr(start, end - start);
}

static UINT GetVkFromKeyName(const std::wstring& name) {
    if (name == L"left") {
        return VK_LEFT;
    }
    if (name == L"right") {
        return VK_RIGHT;
    }
    if (name == L"up") {
        return VK_UP;
    }
    if (name == L"down") {
        return VK_DOWN;
    }
    // Punctuation keys, by symbol or by word. Note: the shortcut parser splits
    // on "+", so the plus key must be written as "plus" (or "=" / "equals").
    if (name == L"[" || name == L"lbracket" || name == L"leftbracket") {
        return VK_OEM_4;
    }
    if (name == L"]" || name == L"rbracket" || name == L"rightbracket") {
        return VK_OEM_6;
    }
    if (name == L"-" || name == L"minus") {
        return VK_OEM_MINUS;
    }
    if (name == L"+" || name == L"plus" || name == L"=" || name == L"equals") {
        return VK_OEM_PLUS;
    }
    if (name.size() == 1) {
        wchar_t c = name[0];
        if (c >= L'a' && c <= L'z') {
            return (UINT)(L'A' + (c - L'a'));
        }
        if (c >= L'0' && c <= L'9') {
            return (UINT)c;
        }
    }
    return 0;
}

static UINT ParseModifierMask(const std::wstring& value) {
    if (value == L"none") {
        return 0;
    }
    if (value == L"alt") {
        return MOD_F_ALT;
    }
    if (value == L"ctrl") {
        return MOD_F_CTRL;
    }
    if (value == L"shift") {
        return MOD_F_SHIFT;
    }
    if (value == L"win") {
        return MOD_F_WIN;
    }
    if (value == L"alt_ctrl") {
        return MOD_F_ALT | MOD_F_CTRL;
    }
    if (value == L"alt_shift") {
        return MOD_F_ALT | MOD_F_SHIFT;
    }
    if (value == L"ctrl_shift") {
        return MOD_F_CTRL | MOD_F_SHIFT;
    }
    if (value == L"win_alt") {
        return MOD_F_WIN | MOD_F_ALT;
    }
    if (value == L"win_ctrl") {
        return MOD_F_WIN | MOD_F_CTRL;
    }
    if (value == L"win_shift") {
        return MOD_F_WIN | MOD_F_SHIFT;
    }
    return MOD_F_ALT;
}

// Maps a single modifier word (alt/ctrl/shift/win and common aliases) to its bit.
// Returns true and sets *bit if the token is a recognised modifier.
static bool ParseModifierToken(const std::wstring& token, UINT* bit) {
    if (token == L"alt" || token == L"menu") {
        *bit = MOD_F_ALT;
        return true;
    }
    if (token == L"ctrl" || token == L"control") {
        *bit = MOD_F_CTRL;
        return true;
    }
    if (token == L"shift") {
        *bit = MOD_F_SHIFT;
        return true;
    }
    if (token == L"win" || token == L"super" || token == L"meta" ||
        token == L"cmd") {
        *bit = MOD_F_WIN;
        return true;
    }
    return false;
}

// Parses a "[mod+]...key" shortcut string into a key code and modifier mask.
// Returns true only if a key token was found; modifier-only strings are invalid.
static bool ParseShortcut(const std::wstring& text, UINT* outVk, UINT* outMods) {
    *outVk = 0;
    *outMods = 0;
    bool haveKey = false;

    size_t start = 0;
    while (start <= text.size()) {
        size_t pos = text.find(L'+', start);
        std::wstring token = ToLower(Trim(
            pos == std::wstring::npos ? text.substr(start)
                                      : text.substr(start, pos - start)));

        if (!token.empty()) {
            UINT bit = 0;
            if (ParseModifierToken(token, &bit)) {
                *outMods |= bit;
            } else {
                UINT vk = GetVkFromKeyName(token);
                if (vk != 0) {
                    *outVk = vk;
                    haveKey = true;
                }
            }
        }

        if (pos == std::wstring::npos) {
            break;
        }
        start = pos + 1;
    }

    return haveKey;
}

// File name portion of a path (handles both slash styles).
static std::wstring BaseName(const std::wstring& path) {
    size_t pos = path.find_last_of(L"\\/");
    return pos == std::wstring::npos ? path : path.substr(pos + 1);
}

// Reduces a user-entered executable reference to a bare lowercase file name,
// e.g. `"C:\Windows\notepad"` -> `notepad.exe`.
static std::wstring NormalizeExecutableName(std::wstring name) {
    name = Trim(name);
    if (name.size() >= 2 && name.front() == L'"' && name.back() == L'"') {
        name = name.substr(1, name.size() - 2);
    }
    if (name.empty()) {
        return name;
    }
    name = ToLower(Trim(BaseName(name)));
    if (!name.empty() && name.find(L'.') == std::wstring::npos) {
        name += L".exe";
    }
    return name;
}

// Splits a comma/semicolon/pipe-separated list of executable names, normalizing
// and de-duplicating each entry.
static std::vector<std::wstring> SplitExecutableList(const std::wstring& value) {
    std::vector<std::wstring> result;
    size_t start = 0;
    while (start <= value.size()) {
        size_t pos = value.find_first_of(L",;|", start);
        std::wstring part = pos == std::wstring::npos
                                ? value.substr(start)
                                : value.substr(start, pos - start);

        std::wstring normalized = NormalizeExecutableName(part);
        if (!normalized.empty() &&
            std::find(result.begin(), result.end(), normalized) ==
                result.end()) {
            result.push_back(normalized);
        }

        if (pos == std::wstring::npos) {
            break;
        }
        start = pos + 1;
    }
    return result;
}

static Action ParseActionName(const std::wstring& value) {
    std::wstring v = ToLower(Trim(value));
    if (v == L"left-half") return Action::LeftHalf;
    if (v == L"right-half") return Action::RightHalf;
    if (v == L"top-half") return Action::TopHalf;
    if (v == L"bottom-half") return Action::BottomHalf;
    if (v == L"center-half") return Action::CenterHalf;
    if (v == L"top-left") return Action::TopLeft;
    if (v == L"top-right") return Action::TopRight;
    if (v == L"bottom-left") return Action::BottomLeft;
    if (v == L"bottom-right") return Action::BottomRight;
    if (v == L"maximize") return Action::Maximize;
    if (v == L"almost-maximize") return Action::AlmostMaximize;
    if (v == L"center") return Action::Center;
    if (v == L"minimize") return Action::Minimize;
    return Action::None;
}

// Bare lowercase executable name of the process that owns the window.
static std::wstring GetWindowProcessExeName(HWND hWnd) {
    DWORD pid = 0;
    GetWindowThreadProcessId(hWnd, &pid);
    if (!pid) {
        return L"";
    }

    HANDLE process =
        OpenProcess(PROCESS_QUERY_LIMITED_INFORMATION, FALSE, pid);
    if (!process) {
        return L"";
    }

    wchar_t path[MAX_PATH] = {};
    DWORD size = ARRAYSIZE(path);
    std::wstring result;
    if (QueryFullProcessImageNameW(process, 0, path, &size)) {
        result = ToLower(BaseName(std::wstring(path, size)));
    }
    CloseHandle(process);
    return result;
}

static bool TextMatches(const std::wstring& text,
                        const std::shared_ptr<const std::wregex>& pattern,
                        MatchMode mode, const std::wstring& value) {
    if (text.empty()) {
        return true;
    }
    if (mode == MatchMode::Regex || mode == MatchMode::NotRegex) {
        if (!pattern) {
            return false;
        }
        bool found = false;
        try {
            found = std::regex_search(value, *pattern);
        } catch (...) {
            return false;
        }
        return mode == MatchMode::Regex ? found : !found;
    }
    std::wstring lower = ToLower(value);
    return mode == MatchMode::Equals ? lower == text
                                     : lower.find(text) != std::wstring::npos;
}

static bool ExeMatches(const AppRule& rule, const std::wstring& exe) {
    if (rule.executables.empty()) {
        return true;
    }
    if (exe.empty()) {
        return false;
    }
    for (const auto& name : rule.executables) {
        bool wildcard = name.find_first_of(L"*?") != std::wstring::npos;
        if (wildcard ? PathMatchSpecW(exe.c_str(), name.c_str()) : name == exe) {
            return true;
        }
    }
    return false;
}

// What the rules look at, the title and class read only when a rule needs them.
// InternalGetWindowText never sends the window a message, so a hung window
// can't hold up the caller.
struct WindowFacts {
    std::wstring exe;
    std::wstring title;
    std::wstring cls;
    bool haveText = false;
};

static bool RuleMatches(const AppRule& rule, HWND hWnd, WindowFacts& facts) {
    if (!ExeMatches(rule, facts.exe)) {
        return false;
    }
    if (rule.title.empty() && rule.cls.empty()) {
        return true;
    }
    if (!facts.haveText) {
        facts.haveText = true;
        WCHAR buffer[512];
        int length = InternalGetWindowText(hWnd, buffer, ARRAYSIZE(buffer));
        facts.title.assign(buffer, length > 0 ? length : 0);
        length = GetClassNameW(hWnd, buffer, ARRAYSIZE(buffer));
        facts.cls.assign(buffer, length > 0 ? length : 0);
    }
    return TextMatches(rule.title, rule.titlePattern, rule.mode, facts.title) &&
           TextMatches(rule.cls, rule.clsPattern, rule.mode, facts.cls);
}

// Reads the rules list. A rule needs something to match on and something to
// do; the list ends after three blank entries in a row.
static RuleList ParseRules(bool ignoreOnly) {
    RuleList rules;
    int lastUsed = -1;
    for (int i = 0; i <= 255 && rules.size() < kMaxRules; i++) {
        auto read = [i](PCWSTR field) {
            return std::wstring(
                WindhawkUtils::StringSetting::make(L"rules[%d].%ls", i, field).get());
        };
        std::wstring exeNames = read(L"executable_names");
        std::wstring title = read(L"window_title");
        std::wstring cls = read(L"window_class");
        std::wstring actionName = ToLower(Trim(read(L"action")));
        if (Trim(exeNames).empty() && title.empty() && cls.empty() &&
            actionName.empty()) {
            if (i - lastUsed > 2) {
                break;
            }
            continue;
        }
        lastUsed = i;

        AppRule rule;
        rule.ignore = actionName == L"ignore";
        if (ignoreOnly && !rule.ignore) {
            continue;
        }
        rule.executables = SplitExecutableList(exeNames);
        if (rule.executables.empty() && title.empty() && cls.empty()) {
            continue;
        }

        std::wstring mode = ToLower(Trim(read(L"match_mode")));
        rule.mode = mode == L"equals"      ? MatchMode::Equals
                    : mode == L"regex"     ? MatchMode::Regex
                    : mode == L"not_regex" ? MatchMode::NotRegex
                                           : MatchMode::Contains;
        if (rule.mode == MatchMode::Regex || rule.mode == MatchMode::NotRegex) {
            try {
                auto flags = std::regex_constants::ECMAScript |
                             std::regex_constants::icase;
                if (!title.empty()) {
                    rule.titlePattern = std::make_shared<const std::wregex>(title, flags);
                }
                if (!cls.empty()) {
                    rule.clsPattern = std::make_shared<const std::wregex>(cls, flags);
                }
            } catch (...) {
                Wh_Log(L"Rule %d has a pattern that does not work; skipping it", i + 1);
                continue;
            }
            rule.title = title;
            rule.cls = cls;
        } else {
            rule.title = ToLower(title);
            rule.cls = ToLower(cls);
        }

        if (!rule.ignore) {
            rule.action = ParseActionName(actionName);
            rule.noResize = Wh_GetIntSetting(L"rules[%d].no_resize", i) != 0;
            std::wstring when = ToLower(Trim(read(L"apply_when")));
            rule.when = when == L"new"     ? ApplyWhen::New
                        : when == L"title" ? ApplyWhen::Title
                                           : ApplyWhen::Open;
            rule.onTop = Wh_GetIntSetting(L"rules[%d].on_top", i) != 0;
            int opacity = Wh_GetIntSetting(L"rules[%d].opacity", i);
            if (opacity <= 0 || opacity > 100) {
                opacity = 100;
            }
            opacity = std::max(opacity, 30);
            rule.alpha = (BYTE)((opacity * 255 + 50) / 100);
            if (rule.action == Action::None && !rule.onTop && rule.alpha == 255) {
                continue;
            }
        }
        rules.push_back(std::move(rule));
    }
    return rules;
}

void LoadIgnoreRules() {
    auto rules = std::make_shared<const RuleList>(ParseRules(true));
    std::lock_guard<std::mutex> lock(g_ignoreRulesMutex);
    g_ignoreRules = std::move(rules);
}

// Shell surfaces that are never dragged, snapped or faded, plus the windows an
// ignore rule names.
bool IsIgnoredWindow(HWND hWnd, PCWSTR exeName) {
    static constexpr PCWSTR kShellHosts[] = {
        L"searchhost.exe",           L"searchapp.exe",
        L"shellexperiencehost.exe",  L"startmenuexperiencehost.exe",
        L"screenclippinghost.exe",   L"lockapp.exe",
    };
    std::wstring exe = ToLower(exeName ? exeName : L"");
    for (PCWSTR host : kShellHosts) {
        if (exe == host) {
            return true;
        }
    }
    std::shared_ptr<const RuleList> rules;
    {
        std::lock_guard<std::mutex> lock(g_ignoreRulesMutex);
        rules = g_ignoreRules;
    }
    if (!rules || rules->empty()) {
        return false;
    }
    WindowFacts facts;
    facts.exe = exe;
    for (const auto& rule : *rules) {
        if (RuleMatches(rule, hWnd, facts)) {
            return true;
        }
    }
    return false;
}

static bool IsEligibleWindow(HWND hWnd) {
    if (altSnapDrag::g_globalInput) return altSnapDrag::CanActOnRootWindow(hWnd);
    if (!hWnd || !IsWindow(hWnd)) {
        return false;
    }

    if (GetAncestor(hWnd, GA_ROOT) != hWnd) {
        return false;
    }

    LONG_PTR exStyle = GetWindowLongPtrW(hWnd, GWL_EXSTYLE);
    if (exStyle & WS_EX_TOOLWINDOW) {
        return false;
    }

    LONG_PTR style = GetWindowLongPtrW(hWnd, GWL_STYLE);
    if (!(style & WS_CAPTION)) {
        return false;
    }

    return true;
}

// Position the window so its *visible* bounds match the given screen rectangle.
// GetWindowRect/SetWindowPos coordinates include the invisible drop-shadow border
// that DWM draws around a window, so measure it and expand the target accordingly.
static void ApplyVisibleRect(HWND hWnd, int x, int y, int w, int h) {
    RECT windowRect = {};
    RECT frameRect = {};
    int marginLeft = 0, marginTop = 0, marginRight = 0, marginBottom = 0;
    if (GetWindowRect(hWnd, &windowRect) &&
        SUCCEEDED(DwmGetWindowAttribute(hWnd, DWMWA_EXTENDED_FRAME_BOUNDS,
                                        &frameRect, sizeof(frameRect)))) {
        marginLeft = frameRect.left - windowRect.left;
        marginTop = frameRect.top - windowRect.top;
        marginRight = windowRect.right - frameRect.right;
        marginBottom = windowRect.bottom - frameRect.bottom;
    }

    SetWindowPos(hWnd, nullptr,
                 x - marginLeft,
                 y - marginTop,
                 w + marginLeft + marginRight,
                 h + marginTop + marginBottom,
                 SWP_NOZORDER | SWP_NOOWNERZORDER | SWP_NOACTIVATE);
}

// Glides the windows from where they are to their new visible rectangles, all
// together, easing out, so a snap or a new layout doesn't just jump. It goes by
// the clock, so a slow app gets fewer frames, not a longer glide. The caller
// still places each window exactly afterwards.
static void AnimateRects(const std::vector<std::pair<HWND, RECT>>& moves) {
    int ms = swm::g_animMs;
    if (ms <= 0 || swm::g_animOff > 0 || moves.empty()) return;
    struct Item {
        HWND wnd;
        RECT from, to, margin;
    };
    std::vector<Item> items;
    for (const auto& move : moves) {
        HWND wnd = move.first;
        const RECT& to = move.second;
        if (!IsWindow(wnd) || !IsWindowVisible(wnd) || IsIconic(wnd) || IsZoomed(wnd) ||
            IsHungAppWindow(wnd) || IsRectEmpty(&to)) {
            continue;
        }
        DWORD cloaked = 0;
        RECT wr{}, fr{};
        if ((SUCCEEDED(DwmGetWindowAttribute(wnd, DWMWA_CLOAKED, &cloaked, sizeof(cloaked))) &&
             cloaked) ||
            !GetWindowRect(wnd, &wr) ||
            FAILED(DwmGetWindowAttribute(wnd, DWMWA_EXTENDED_FRAME_BOUNDS, &fr, sizeof(fr))) ||
            EqualRect(&fr, &to)) {
            continue;
        }
        items.push_back({wnd, fr, to,
                         {fr.left - wr.left, fr.top - wr.top, wr.right - fr.right,
                          wr.bottom - fr.bottom}});
    }
    if (items.empty()) return;
    LARGE_INTEGER freq{}, start{}, now{};
    QueryPerformanceFrequency(&freq);
    QueryPerformanceCounter(&start);
    for (int frame = 0; frame < 240; frame++) {
        QueryPerformanceCounter(&now);
        double t = (double)(now.QuadPart - start.QuadPart) * 1000.0 /
                   ((double)freq.QuadPart * ms);
        if (t >= 1.0) break;
        double u = 1.0 - t;
        double e = 1.0 - u * u * u;
        auto lerp = [e](LONG a, LONG b) { return (int)(a + (b - a) * e + 0.5); };
        for (const Item& it : items) {
            int l = lerp(it.from.left, it.to.left);
            int tp = lerp(it.from.top, it.to.top);
            int r = lerp(it.from.right, it.to.right);
            int b = lerp(it.from.bottom, it.to.bottom);
            // No copied bits: apps like Explorer otherwise leave old copies
            // of their panes behind while they shrink.
            SetWindowPos(it.wnd, nullptr, l - it.margin.left, tp - it.margin.top,
                         r - l + it.margin.left + it.margin.right,
                         b - tp + it.margin.top + it.margin.bottom,
                         SWP_NOZORDER | SWP_NOOWNERZORDER | SWP_NOACTIVATE | SWP_NOCOPYBITS);
            RedrawWindow(it.wnd, nullptr, nullptr, RDW_INVALIDATE | RDW_ERASE | RDW_ALLCHILDREN);
        }
        if (FAILED(DwmFlush())) Sleep(8);
    }
    // Land exactly and repaint everything once, so nothing stale stays.
    for (const Item& it : items) {
        SetWindowPos(it.wnd, nullptr, it.to.left - it.margin.left, it.to.top - it.margin.top,
                     it.to.right - it.to.left + it.margin.left + it.margin.right,
                     it.to.bottom - it.to.top + it.margin.top + it.margin.bottom,
                     SWP_NOZORDER | SWP_NOOWNERZORDER | SWP_NOACTIVATE | SWP_NOCOPYBITS);
        RedrawWindow(it.wnd, nullptr, nullptr,
                     RDW_INVALIDATE | RDW_ERASE | RDW_FRAME | RDW_ALLCHILDREN);
    }
}

static void AnimateVisibleRect(HWND hWnd, int x, int y, int w, int h) {
    AnimateRects({{hWnd, RECT{x, y, x + w, y + h}}});
    ApplyVisibleRect(hWnd, x, y, w, h);
}

// Same, for a target given as the whole window rectangle.
static void AnimateWindowRect(HWND hWnd, const RECT& target) {
    RECT wr{}, fr{};
    if (!GetWindowRect(hWnd, &wr) ||
        FAILED(DwmGetWindowAttribute(hWnd, DWMWA_EXTENDED_FRAME_BOUNDS, &fr, sizeof(fr)))) {
        return;
    }
    RECT visible{target.left + (fr.left - wr.left), target.top + (fr.top - wr.top),
                 target.right - (wr.right - fr.right), target.bottom - (wr.bottom - fr.bottom)};
    AnimateRects({{hWnd, visible}});
}

// Current visible bounds of the window (excludes the invisible drop-shadow border).
static void GetVisibleRect(HWND hWnd, RECT* rect) {
    if (FAILED(DwmGetWindowAttribute(hWnd, DWMWA_EXTENDED_FRAME_BOUNDS, rect,
                                     sizeof(*rect)))) {
        GetWindowRect(hWnd, rect);
    }
}

// Current visible size of the window (excludes the invisible drop-shadow border).
static void GetVisibleSize(HWND hWnd, int* width, int* height) {
    RECT rect = {};
    GetVisibleRect(hWnd, &rect);
    *width = rect.right - rect.left;
    *height = rect.bottom - rect.top;
}

static BOOL CALLBACK CollectMonitorsProc(HMONITOR hMonitor, HDC, LPRECT,
                                         LPARAM lParam) {
    auto* works = reinterpret_cast<std::vector<RECT>*>(lParam);
    MONITORINFO mi = {};
    mi.cbSize = sizeof(mi);
    if (GetMonitorInfoW(hMonitor, &mi)) {
        works->push_back(mi.rcWork);
    }
    return TRUE;
}

// Moves the window to the next/previous monitor (direction +1/-1, wrapping),
// keeping its size and position relative to the work area (scaled if the target
// monitor has a different work-area size). Preserves a maximized state.
static void MoveToAdjacentDisplay(HWND hWnd, int direction) {
    std::vector<RECT> works;
    EnumDisplayMonitors(nullptr, nullptr, CollectMonitorsProc,
                        reinterpret_cast<LPARAM>(&works));
    if (works.size() < 2) {
        return;  // Nothing to move to.
    }

    // Order monitors left-to-right, then top-to-bottom, for predictable cycling.
    std::sort(works.begin(), works.end(), [](const RECT& a, const RECT& b) {
        if (a.left != b.left) {
            return a.left < b.left;
        }
        return a.top < b.top;
    });

    MONITORINFO cur = {};
    cur.cbSize = sizeof(cur);
    if (!GetMonitorInfoW(MonitorFromWindow(hWnd, MONITOR_DEFAULTTONEAREST),
                         &cur)) {
        return;
    }

    int curIndex = -1;
    for (size_t i = 0; i < works.size(); i++) {
        if (EqualRect(&works[i], &cur.rcWork)) {
            curIndex = (int)i;
            break;
        }
    }
    if (curIndex < 0) {
        return;
    }

    const int n = (int)works.size();
    const RECT& src = works[curIndex];
    const RECT& dst = works[((curIndex + direction) % n + n) % n];

    const int srcW = src.right - src.left;
    const int srcH = src.bottom - src.top;
    const int dstW = dst.right - dst.left;
    const int dstH = dst.bottom - dst.top;
    if (srcW <= 0 || srcH <= 0 || dstW <= 0 || dstH <= 0) {
        return;
    }

    const bool wasZoomed = IsZoomed(hWnd) != FALSE;
    if (wasZoomed || IsIconic(hWnd)) {
        ShowWindow(hWnd, SW_RESTORE);
    }

    RECT vis = {};
    GetVisibleRect(hWnd, &vis);

    // Map the window rect from the source work area to the destination one.
    auto mapX = [&](LONG x) {
        return dst.left + (int)((double)(x - src.left) * dstW / srcW);
    };
    auto mapY = [&](LONG y) {
        return dst.top + (int)((double)(y - src.top) * dstH / srcH);
    };

    int x = mapX(vis.left);
    int y = mapY(vis.top);
    int w = (int)((double)(vis.right - vis.left) * dstW / srcW);
    int h = (int)((double)(vis.bottom - vis.top) * dstH / srcH);
    if (w < 1) w = 1;
    if (h < 1) h = 1;

    AnimateVisibleRect(hWnd, x, y, w, h);

    if (wasZoomed) {
        ShowWindow(hWnd, SW_MAXIMIZE);  // Re-maximize on the new monitor.
    }
    MoveCursorToWindow(hWnd);
}

struct Gaps {
    int left, top, right, bottom;
};

// The gap on each side for this monitor, in pixels.
static Gaps ResolveGaps(HMONITOR monitor, const RECT& work, Action action) {
    Gaps gaps{g_gapLeft, g_gapTop, g_gapRight, g_gapBottom};
    bool percent = g_gapUnitPercent;
    if (action == Action::AlmostMaximize && g_almostMaxGap >= 0) {
        gaps = {g_almostMaxGap, g_almostMaxGap, g_almostMaxGap, g_almostMaxGap};
        percent = false;
    }
    if (percent) {
        const int w = work.right - work.left;
        const int h = work.bottom - work.top;
        gaps = {MulDiv(w, gaps.left, 100), MulDiv(h, gaps.top, 100),
                MulDiv(w, gaps.right, 100), MulDiv(h, gaps.bottom, 100)};
    } else if (g_gapScaleDpi) {
        UINT dpiX = 96, dpiY = 96;
        if (FAILED(GetDpiForMonitor(monitor, MDT_EFFECTIVE_DPI, &dpiX, &dpiY)) ||
            !dpiX) {
            dpiX = 96;
        }
        gaps = {MulDiv(gaps.left, dpiX, 96), MulDiv(gaps.top, dpiX, 96),
                MulDiv(gaps.right, dpiX, 96), MulDiv(gaps.bottom, dpiX, 96)};
    }
    return gaps;
}

// The work area with the outer gaps taken off.
static RECT GappedWorkArea(HMONITOR monitor, const RECT& work) {
    const Gaps gaps = ResolveGaps(monitor, work, Action::Center);
    RECT r{work.left + gaps.left, work.top + gaps.top, work.right - gaps.right,
           work.bottom - gaps.bottom};
    if (r.right - r.left < 100 || r.bottom - r.top < 100) {
        return work;
    }
    return r;
}

// One keyboard resize step. Resizing keeps the top-left corner where it is;
// moving keeps the size. Both stay inside the gapped work area, and a window
// already smaller than the minimum is never grown by shrinking it.
static void NudgeWindow(HWND hWnd, int dx, int dy, bool move) {
    if (!IsWindow(hWnd) || IsIconic(hWnd) || IsZoomed(hWnd)) {
        return;
    }
    HMONITOR monitor = MonitorFromWindow(hWnd, MONITOR_DEFAULTTONEAREST);
    MONITORINFO mi = {};
    mi.cbSize = sizeof(mi);
    if (!GetMonitorInfoW(monitor, &mi)) {
        return;
    }
    const RECT work = GappedWorkArea(monitor, mi.rcWork);
    const int pct = swm::g_resizeStepPct;
    const int stepX = std::max(1, (int)(work.right - work.left) * pct / 100);
    const int stepY = std::max(1, (int)(work.bottom - work.top) * pct / 100);

    RECT vis = {};
    GetVisibleRect(hWnd, &vis);
    const int w = vis.right - vis.left;
    const int h = vis.bottom - vis.top;

    if (move) {
        int x = vis.left + dx * stepX;
        int y = vis.top + dy * stepY;
        x = std::max((int)work.left, std::min(x, std::max((int)work.left, (int)work.right - w)));
        y = std::max((int)work.top, std::min(y, std::max((int)work.top, (int)work.bottom - h)));
        ApplyVisibleRect(hWnd, x, y, w, h);
        return;
    }

    int newW = w + dx * stepX;
    int newH = h + dy * stepY;
    if (dx < 0) newW = std::max(newW, std::min(w, 250));
    if (dy < 0) newH = std::max(newH, std::min(h, 140));
    if (dx > 0) newW = std::min(newW, std::max(w, (int)work.right - (int)vis.left));
    if (dy > 0) newH = std::min(newH, std::max(h, (int)work.bottom - (int)vis.top));
    if (newW == w && newH == h) {
        return;
    }
    ApplyVisibleRect(hWnd, vis.left, vis.top, newW, newH);
}

// Grows or shrinks the window about its center by the configured step
// (direction +1 = larger, -1 = smaller), clamped to the gapped work area.
static void ResizeFromCenter(HWND hWnd, int direction) {
    if (IsIconic(hWnd) || IsZoomed(hWnd)) {
        ShowWindow(hWnd, SW_RESTORE);
    }

    RECT vis = {};
    GetVisibleRect(hWnd, &vis);
    const int w = vis.right - vis.left;
    const int h = vis.bottom - vis.top;
    const int cx = vis.left + w / 2;
    const int cy = vis.top + h / 2;

    MONITORINFO mi = {};
    mi.cbSize = sizeof(mi);
    HMONITOR monitor = MonitorFromWindow(hWnd, MONITOR_DEFAULTTONEAREST);
    if (!GetMonitorInfoW(monitor, &mi)) {
        return;
    }
    const RECT work = GappedWorkArea(monitor, mi.rcWork);
    const int workW = work.right - work.left;
    const int workH = work.bottom - work.top;

    int stepX = workW * g_resizeStepPercent / 100;
    int stepY = workH * g_resizeStepPercent / 100;
    if (stepX < 1) stepX = 1;
    if (stepY < 1) stepY = 1;

    int newW = w + direction * stepX;
    int newH = h + direction * stepY;

    // Clamp between a small minimum and the full work area.
    const int minW = 200;
    const int minH = 150;
    newW = std::max(minW, std::min(newW, workW));
    newH = std::max(minH, std::min(newH, workH));

    int x = cx - newW / 2;
    int y = cy - newH / 2;
    if (x < work.left) x = work.left;
    if (y < work.top) y = work.top;
    if (x + newW > work.right) x = work.right - newW;
    if (y + newH > work.bottom) y = work.bottom - newH;

    ApplyVisibleRect(hWnd, x, y, newW, newH);
}

static void SavePlacementIfNew(HWND hWnd) {
    if (g_savedPlacements.find(hWnd) != g_savedPlacements.end()) {
        return;
    }
    WINDOWPLACEMENT wp = {};
    wp.length = sizeof(wp);
    if (GetWindowPlacement(hWnd, &wp)) {
        g_savedPlacements[hWnd] = wp;
    }
}

static void RestorePreviousPlacement(HWND hWnd) {
    auto it = g_savedPlacements.find(hWnd);
    if (it == g_savedPlacements.end()) {
        return;
    }
    SetWindowPlacement(hWnd, &it->second);
    g_savedPlacements.erase(it);
}

static void SnapWindow(HWND hWnd, Action action, bool noResize) {
    if (action == Action::None || !IsEligibleWindow(hWnd)) {
        return;
    }

    if (action == Action::RestorePrevious) {
        RestorePreviousPlacement(hWnd);
        return;
    }

    // Remember where the window was before its first snap so it can be restored.
    SavePlacementIfNew(hWnd);

    if (action == Action::Minimize) {
        ShowWindow(hWnd, SW_MINIMIZE);
        return;
    }

    // Maximize fills the work area; with "don't resize" it instead keeps its
    // size and is centered in the work area (handled by the cell logic below).
    if (action == Action::Maximize && !noResize) {
        ShowWindow(hWnd, SW_MAXIMIZE);
        return;
    }

    if (action == Action::NextDisplay || action == Action::PreviousDisplay) {
        MoveToAdjacentDisplay(hWnd, action == Action::NextDisplay ? 1 : -1);
        return;
    }

    if (action == Action::MakeSmaller || action == Action::MakeLarger) {
        ResizeFromCenter(hWnd, action == Action::MakeLarger ? 1 : -1);
        return;
    }

    if (IsIconic(hWnd) || IsZoomed(hWnd)) {
        ShowWindow(hWnd, SW_RESTORE);
    }

    HMONITOR monitor = MonitorFromWindow(hWnd, MONITOR_DEFAULTTONEAREST);
    MONITORINFO mi = {};
    mi.cbSize = sizeof(mi);
    if (!GetMonitorInfoW(monitor, &mi)) {
        return;
    }

    const RECT& work = mi.rcWork;
    const int fullWidth = work.right - work.left;
    const int fullHeight = work.bottom - work.top;
    const int halfWidth = fullWidth / 2;
    const int midX = work.left + halfWidth;
    const int midY = work.top + fullHeight / 2;

    if (action == Action::Center) {
        int curW = 0, curH = 0;
        GetVisibleSize(hWnd, &curW, &curH);
        int w = (!noResize && g_centerWidth > 0) ? g_centerWidth : curW;
        int h = (!noResize && g_centerHeight > 0) ? g_centerHeight : curH;
        int x = work.left + (fullWidth - w) / 2;
        int y = work.top + (fullHeight - h) / 2;
        AnimateVisibleRect(hWnd, x, y, w, h);
        return;
    }

    // The region of the work area this action targets, before gaps.
    RECT cell = work;
    switch (action) {
        case Action::LeftHalf:
            cell = {work.left, work.top, midX, work.bottom};
            break;
        case Action::RightHalf:
            cell = {midX, work.top, work.right, work.bottom};
            break;
        case Action::TopHalf:
            cell = {work.left, work.top, work.right, midY};
            break;
        case Action::BottomHalf:
            cell = {work.left, midY, work.right, work.bottom};
            break;
        case Action::CenterHalf: {
            int left = work.left + (fullWidth - halfWidth) / 2;
            cell = {left, work.top, left + halfWidth, work.bottom};
            break;
        }
        case Action::TopLeft:
            cell = {work.left, work.top, midX, midY};
            break;
        case Action::TopRight:
            cell = {midX, work.top, work.right, midY};
            break;
        case Action::BottomLeft:
            cell = {work.left, midY, midX, work.bottom};
            break;
        case Action::BottomRight:
            cell = {midX, midY, work.right, work.bottom};
            break;
        case Action::AlmostMaximize:
        case Action::Maximize:  // Only reached with noResize; ignores gaps.
            cell = work;
            break;
        default:
            return;
    }

    // Inset each side by its gap. Maximize ignores gaps entirely. Inner sides
    // (those not coinciding with the work-area edge) are sized per the gap mode:
    // full gap (doubles between windows), half gap (even spacing), or none.
    if (action != Action::Maximize) {
        const Gaps gaps = ResolveGaps(monitor, work, action);
        auto sideGap = [](bool atScreenEdge, int gap) -> int {
            if (atScreenEdge) {
                return gap;
            }
            switch (g_gapMode) {
                case GapMode::Even:
                    return gap / 2;
                case GapMode::Screen:
                    return 0;
                case GapMode::Full:
                default:
                    return gap;
            }
        };
        cell.left += sideGap(cell.left == work.left, gaps.left);
        cell.top += sideGap(cell.top == work.top, gaps.top);
        cell.right -= sideGap(cell.right == work.right, gaps.right);
        cell.bottom -= sideGap(cell.bottom == work.bottom, gaps.bottom);
    }
    if (cell.right <= cell.left || cell.bottom <= cell.top) {
        return;
    }

    if (!noResize) {
        AnimateVisibleRect(hWnd, cell.left, cell.top, cell.right - cell.left,
                           cell.bottom - cell.top);
        return;
    }

    // Keep the window's size and anchor it within the target cell. The anchor
    // edge follows the action (e.g. top-right -> top and right edges of the
    // cell), so the unresized window sits in the matching corner/side.
    int w = 0, h = 0;
    GetVisibleSize(hWnd, &w, &h);
    const int cellW = cell.right - cell.left;
    const int cellH = cell.bottom - cell.top;

    int ax = 0, ay = 0;  // -1 = left/top, 0 = center, 1 = right/bottom.
    switch (action) {
        case Action::LeftHalf:   ax = -1; ay = 0;  break;
        case Action::RightHalf:  ax = 1;  ay = 0;  break;
        case Action::TopHalf:    ax = 0;  ay = -1; break;
        case Action::BottomHalf: ax = 0;  ay = 1;  break;
        case Action::TopLeft:    ax = -1; ay = -1; break;
        case Action::TopRight:   ax = 1;  ay = -1; break;
        case Action::BottomLeft: ax = -1; ay = 1;  break;
        case Action::BottomRight:ax = 1;  ay = 1;  break;
        default:                 ax = 0;  ay = 0;  break;  // CenterHalf, (Almost)Maximize.
    }

    int x = ax < 0 ? cell.left
            : ax > 0 ? cell.right - w
                     : cell.left + (cellW - w) / 2;
    int y = ay < 0 ? cell.top
            : ay > 0 ? cell.bottom - h
                     : cell.top + (cellH - h) / 2;

    if (x < work.left) {
        x = work.left;
    }
    if (y < work.top) {
        y = work.top;
    }

    AnimateVisibleRect(hWnd, x, y, w, h);
}

// Drops every currently-registered hotkey. Must run on the hook thread (the thread
// that called RegisterHotKey owns the hotkeys and receives their WM_HOTKEY messages).
static void UnregisterHotkeys() {
    for (int i = 0; i < ACTION_COUNT; i++) {
        if (g_hotkeyRegistered[i]) {
            UnregisterHotKey(nullptr, i);
            g_hotkeyRegistered[i] = false;
        }
    }
}

// (Re)registers a thread-global hotkey per bound action, using the action index as the
// hotkey id. Consuming the whole combo avoids the stray-modifier side effects of a
// low-level keyboard hook. Must run on the hook thread.
//
// Every process that loads this mod registers the combos on its hook thread, so one
// process owns each combo at a time. A combo is released when its owner's thread
// exits, and RetryMissingHotkeys takes it back in another process. Close is posted as
// a message (WM_CLOSE), which UIPI can block from a lower-integrity owner. Maximize,
// minimize and restore are direct window calls. Drag and resize interception are
// per-process and unaffected.
static void RegisterHotkeys() {
    UnregisterHotkeys();
    for (int i = 0; i < ACTION_COUNT; i++) {
        if (g_actionKeys[i] == 0) {
            continue;
        }
        // MOD_NOREPEAT: one action per physical press, not once per auto-repeat.
        if (RegisterHotKey(nullptr, i, g_actionMods[i] | MOD_NOREPEAT,
                           g_actionKeys[i])) {
            g_hotkeyRegistered[i] = true;
        } else {
            Wh_Log(L"'%s' could not be registered (error %lu); the combination may "
                   L"be reserved or already claimed by another app",
                   g_keyNames[i], GetLastError());
        }
    }
}

static UINT_PTR g_hotkeyRetryTimer = 0;

// Takes back each combo this process does not hold, for example after its owner exited.
static void RetryMissingHotkeys() {
    for (int i = 0; i < ACTION_COUNT; i++) {
        if (g_actionKeys[i] == 0 || g_hotkeyRegistered[i]) {
            continue;
        }
        if (RegisterHotKey(nullptr, i, g_actionMods[i] | MOD_NOREPEAT, g_actionKeys[i])) {
            g_hotkeyRegistered[i] = true;
        }
    }
}

enum class RuleEvent { Show, Existing, TitleChange };

// True when a rule places or ignores this window, so tiling leaves it alone.
bool HasPlacementRule(HWND hWnd) {
    auto rules = GetRules();
    if (!rules || rules->empty()) {
        return false;
    }
    WindowFacts facts;
    facts.exe = GetWindowProcessExeName(hWnd);
    for (const AppRule& rule : *rules) {
        if ((rule.ignore || rule.action != Action::None) && RuleMatches(rule, hWnd, facts)) {
            return true;
        }
    }
    return false;
}

// Applies the first matching rule to a window, once per window. Windows open
// when the mod starts only get "open" rules, and title changes only "title"
// rules.
static void TryApplyRuleToWindow(HWND hWnd, RuleEvent event) {
    if (!hWnd || swm::IsPaused()) {
        return;
    }
    auto rules = GetRules();
    if (!rules || rules->empty() || !IsEligibleWindow(hWnd)) {
        return;
    }

    WindowFacts facts;
    facts.exe = GetWindowProcessExeName(hWnd);
    for (size_t i = 0; i < rules->size(); i++) {
        const AppRule& rule = (*rules)[i];
        if (rule.ignore) {
            continue;
        }
        if (event == RuleEvent::Existing && rule.when != ApplyWhen::Open) {
            continue;
        }
        if (event == RuleEvent::TitleChange && rule.when != ApplyWhen::Title) {
            continue;
        }
        if (!RuleMatches(rule, hWnd, facts)) {
            continue;
        }
        {
            std::lock_guard<std::mutex> lock(g_ruleHandledMutex);
            uint64_t& done = g_ruleHandledWindows[hWnd];
            if (done & (1ull << i)) {
                return;
            }
            done |= 1ull << i;
        }
        Wh_Log(L"Rule %zu applies to %p: action %d, on top %d, alpha %d", i + 1,
               hWnd, (int)rule.action, rule.onTop ? 1 : 0, rule.alpha);
        if (rule.action != Action::None) {
            EnqueueWork(hWnd, rule.action, rule.noResize);
        }
        if (rule.onTop || rule.alpha < 255) {
            swm::ApplyRuleLook(hWnd, rule.alpha, rule.onTop);
        }
        return;
    }
}

void CALLBACK WinEventProc(HWINEVENTHOOK, DWORD event, HWND hWnd, LONG idObject,
                           LONG idChild, DWORD, DWORD) {
    if (idObject != OBJID_WINDOW || idChild != CHILDID_SELF || !hWnd) {
        return;
    }

    if (event == EVENT_OBJECT_DESTROY) {
        {
            std::lock_guard<std::mutex> lock(g_ruleHandledMutex);
            g_ruleHandledWindows.erase(hWnd);
        }
        EnqueueCleanup(hWnd);  // Drop any saved placement for this window.
        return;
    }

    TryApplyRuleToWindow(hWnd, event == EVENT_OBJECT_NAMECHANGE
                                   ? RuleEvent::TitleChange
                                   : RuleEvent::Show);
}

// The show/destroy hook runs only while a rule can act, and the title hook
// only while a "title" rule exists: both events fire for every window in every
// process. Must run on the hook thread, which owns the hooks.
static void UpdateWinEventHook() {
    auto rules = GetRules();
    bool wantHook = false;
    bool wantTitle = false;
    if (rules) {
        for (const auto& rule : *rules) {
            if (rule.ignore) {
                continue;
            }
            wantHook = true;
            wantTitle = wantTitle || rule.when == ApplyWhen::Title;
        }
    }

    if (wantHook && !g_winEventHook) {
        g_winEventHook = SetWinEventHook(
            EVENT_OBJECT_DESTROY, EVENT_OBJECT_SHOW, nullptr, WinEventProc, 0, 0,
            WINEVENT_OUTOFCONTEXT | WINEVENT_SKIPOWNPROCESS);
        if (!g_winEventHook) {
            Wh_Log(L"SetWinEventHook failed, error=%lu", GetLastError());
        }
    } else if (!wantHook && g_winEventHook) {
        UnhookWinEvent(g_winEventHook);
        g_winEventHook = nullptr;
    }

    if (wantTitle && !g_nameChangeHook) {
        g_nameChangeHook = SetWinEventHook(
            EVENT_OBJECT_NAMECHANGE, EVENT_OBJECT_NAMECHANGE, nullptr,
            WinEventProc, 0, 0, WINEVENT_OUTOFCONTEXT | WINEVENT_SKIPOWNPROCESS);
    } else if (!wantTitle && g_nameChangeHook) {
        UnhookWinEvent(g_nameChangeHook);
        g_nameChangeHook = nullptr;
    }
}

static BOOL CALLBACK EnumExistingWindowsProc(HWND hWnd, LPARAM) {
    if (IsWindowVisible(hWnd)) {
        TryApplyRuleToWindow(hWnd, RuleEvent::Existing);
    }
    return TRUE;
}

// Applies "open" rules to windows already on screen, on init and after a
// settings change.
static void ApplyRulesToExistingWindows() {
    auto rules = GetRules();
    if (!rules || rules->empty()) {
        return;
    }
    EnumWindows(EnumExistingWindowsProc, 0);
}

static void LoadSettings() {
    // Wh_GetStringSetting never returns NULL (an unset value comes back as L""),
    // and WindhawkUtils::StringSetting frees the string for us on scope exit.
    UINT modifierMask =
        ParseModifierMask(WindhawkUtils::StringSetting::make(L"modifier").get());

    g_gapUnitPercent =
        ToLower(WindhawkUtils::StringSetting::make(L"dimensions.gapUnit").get()) ==
        L"percent";
    g_gapScaleDpi =
        ToLower(WindhawkUtils::StringSetting::make(L"dimensions.gapScaling").get()) ==
        L"dpi";
    const int maxGap = g_gapUnitPercent ? 25 : 100;
    g_gapTop = std::clamp(Wh_GetIntSetting(L"dimensions.gapTop"), 0, maxGap);
    g_gapBottom = std::clamp(Wh_GetIntSetting(L"dimensions.gapBottom"), 0, maxGap);
    g_gapLeft = std::clamp(Wh_GetIntSetting(L"dimensions.gapLeft"), 0, maxGap);
    g_gapRight = std::clamp(Wh_GetIntSetting(L"dimensions.gapRight"), 0, maxGap);
    std::wstring almostGap = Trim(
        WindhawkUtils::StringSetting::make(L"dimensions.almostMaximizeGap").get());
    g_almostMaxGap =
        almostGap.empty() ? -1 : std::clamp(_wtoi(almostGap.c_str()), 0, 200);

    std::wstring gapModeValue =
        WindhawkUtils::StringSetting::make(L"dimensions.gapMode").get();
    if (gapModeValue == L"full") {
        g_gapMode = GapMode::Full;
    } else if (gapModeValue == L"screen") {
        g_gapMode = GapMode::Screen;
    } else {
        g_gapMode = GapMode::Even;
    }

    g_centerWidth =
        _wtoi(WindhawkUtils::StringSetting::make(L"dimensions.centerWidth").get());
    g_centerHeight =
        _wtoi(WindhawkUtils::StringSetting::make(L"dimensions.centerHeight").get());

    g_resizeStepPercent = Wh_GetIntSetting(L"dimensions.resizeStep");
    if (g_resizeStepPercent < 1) {
        g_resizeStepPercent = 1;
    }
    if (g_resizeStepPercent > 50) {
        g_resizeStepPercent = 50;
    }

    for (int i = 0; i < ACTION_COUNT; i++) {
        WindhawkUtils::StringSetting value =
            WindhawkUtils::StringSetting::make(g_keyNames[i]);

        UINT vk = 0, textMods = 0;
        if (ParseShortcut(value.get(), &vk, &textMods)) {
            g_actionKeys[i] = vk;
            // The global modifier is required on top of whatever the shortcut typed.
            g_actionMods[i] = modifierMask | textMods;
        } else {
            g_actionKeys[i] = 0;  // Unbound or invalid.
            g_actionMods[i] = 0;
        }
    }

    // De-duplicate bindings: if two actions resolve to the same key+modifier
    // combination, only the first one (in g_keyNames order) stays bound. Later
    // duplicates are disabled so a single keypress doesn't fire two actions.
    for (int i = 0; i < ACTION_COUNT; i++) {
        if (g_actionKeys[i] == 0) {
            continue;
        }
        for (int j = 0; j < i; j++) {
            if (g_actionKeys[j] == g_actionKeys[i] &&
                g_actionMods[j] == g_actionMods[i]) {
                Wh_Log(L"'%s' duplicates '%s' (same key+modifier); disabling '%s'",
                       g_keyNames[i], g_keyNames[j], g_keyNames[i]);
                g_actionKeys[i] = 0;
                g_actionMods[i] = 0;
                break;
            }
        }
    }

    // Focus, move, resize and the other window manager keys come first.
    for (int i = 0; i < ACTION_COUNT; i++) {
        if (g_actionKeys[i] && swm::IsReservedHotkey(g_actionMods[i], g_actionKeys[i])) {
            Wh_Log(L"'%s' uses a window manager key; disabling '%s'", g_keyNames[i],
                   g_keyNames[i]);
            g_actionKeys[i] = 0;
            g_actionMods[i] = 0;
        }
    }

    auto newRules = std::make_shared<const RuleList>(ParseRules(false));
    {
        std::lock_guard<std::mutex> lock(g_appRulesMutex);
        g_appRules = std::move(newRules);
    }
    {
        std::lock_guard<std::mutex> lock(g_ruleHandledMutex);
        g_ruleHandledWindows.clear();
    }
}

static DWORD WINAPI WorkerThreadProc(LPVOID) {
    for (;;) {
        WaitForSingleObject(g_workEvent, INFINITE);

        for (;;) {
            WorkItem item;
            {
                std::lock_guard<std::mutex> lock(g_workQueueMutex);
                if (g_workQueue.empty()) {
                    break;
                }
                item = g_workQueue.front();
                g_workQueue.pop_front();
            }
            if (item.cleanup) {
                g_savedPlacements.erase(item.hWnd);
            } else if (item.nudge) {
                NudgeWindow(item.hWnd, item.dx, item.dy, item.move);
            } else {
                SnapWindow(item.hWnd, item.action, item.noResize);
            }
        }

        if (g_quit.load()) {
            break;
        }
    }
    return 0;
}

static DWORD WINAPI HookThreadProc(LPVOID) {
    // Register the shortcut hotkeys on this thread; WM_HOTKEY (for a NULL window)
    // is posted to the queue of the thread that called RegisterHotKey. The auto-snap
    // WinEvent hook is installed here too, but only if any rules are configured.
    if (!swm::IsPaused()) {
        RegisterHotkeys();
    }
    g_hotkeyRetryTimer = SetTimer(nullptr, 0, 2000, nullptr);
    UpdateWinEventHook();

    SetEvent(g_hookReadyEvent);

    MSG msg;
    while (!g_quit.load()) {
        BOOL gm = GetMessageW(&msg, nullptr, 0, 0);
        if (gm == 0 || gm == -1) {
            break;
        }
        // WM_HOTKEY and our settings-changed signal are thread messages (no window),
        // so handle them here rather than via DispatchMessage.
        if (msg.hwnd == nullptr) {
            if (msg.message == WM_HOTKEY) {
                int idx = (int)msg.wParam;
                if (idx >= 0 && idx < ACTION_COUNT) {
                    HWND fg = GetForegroundWindow();
                    HWND root = fg ? GetAncestor(fg, GA_ROOT) : nullptr;
                    int region = -1;
                    switch (g_actionByIndex[idx]) {
                        case Action::LeftHalf: region = 0; break;
                        case Action::RightHalf: region = 1; break;
                        case Action::TopHalf: region = 2; break;
                        case Action::BottomHalf: region = 3; break;
                        case Action::TopLeft: region = 4; break;
                        case Action::TopRight: region = 5; break;
                        case Action::BottomLeft: region = 6; break;
                        case Action::BottomRight: region = 7; break;
                        case Action::AlmostMaximize: region = 8; break;
                        default: break;
                    }
                    // A tiled window rearranges the tiles instead of leaving them.
                    if (region >= 0 && root && swm::IsTiledWindow(root)) {
                        swm::PostTileRegion(region);
                    } else {
                        EnqueueWork(fg, g_actionByIndex[idx]);
                    }
                }
                continue;
            }
            if (msg.message == WM_TIMER && msg.wParam == g_hotkeyRetryTimer) {
                if (!swm::IsPaused()) {
                    RetryMissingHotkeys();
                }
                continue;
            }
            if (msg.message == WM_APP_SETTINGS_CHANGED ||
                msg.message == swm::kPauseChangedMessage) {
                if (swm::IsPaused()) {
                    UnregisterHotkeys();
                } else {
                    RegisterHotkeys();
                }
                UpdateWinEventHook();
                continue;
            }
        }
        TranslateMessage(&msg);
        DispatchMessageW(&msg);
    }

    UnregisterHotkeys();
    if (g_winEventHook) {
        UnhookWinEvent(g_winEventHook);
        g_winEventHook = nullptr;
    }
    if (g_nameChangeHook) {
        UnhookWinEvent(g_nameChangeHook);
        g_nameChangeHook = nullptr;
    }
    return 0;
}

BOOL ToolModInit() {
    LoadSettings();

    g_quit = false;

    g_workEvent = CreateEventW(nullptr, FALSE, FALSE, nullptr);
    if (!g_workEvent) {
        Wh_Log(L"CreateEvent (work) failed");
        return FALSE;
    }

    g_workerThread = CreateThread(nullptr, 0, WorkerThreadProc, nullptr, 0, nullptr);
    if (!g_workerThread) {
        Wh_Log(L"CreateThread (worker) failed");
        CloseHandle(g_workEvent);
        g_workEvent = nullptr;
        return FALSE;
    }

    g_hookReadyEvent = CreateEventW(nullptr, TRUE, FALSE, nullptr);
    if (!g_hookReadyEvent) {
        Wh_Log(L"CreateEvent (hook ready) failed");
        g_quit = true;
        SetEvent(g_workEvent);
        WaitForSingleObject(g_workerThread, 2000);
        CloseHandle(g_workerThread);
        g_workerThread = nullptr;
        CloseHandle(g_workEvent);
        g_workEvent = nullptr;
        return FALSE;
    }

    g_hookThread = CreateThread(nullptr, 0, HookThreadProc, nullptr, 0,
                               &g_hookThreadId);
    if (!g_hookThread) {
        Wh_Log(L"CreateThread (hook) failed");
        CloseHandle(g_hookReadyEvent);
        g_hookReadyEvent = nullptr;
        g_quit = true;
        SetEvent(g_workEvent);
        WaitForSingleObject(g_workerThread, 2000);
        CloseHandle(g_workerThread);
        g_workerThread = nullptr;
        CloseHandle(g_workEvent);
        g_workEvent = nullptr;
        return FALSE;
    }

    WaitForSingleObject(g_hookReadyEvent, 3000);
    CloseHandle(g_hookReadyEvent);
    g_hookReadyEvent = nullptr;

    ApplyRulesToExistingWindows();

    return TRUE;
}

void ToolModSettingsChanged() {
    LoadSettings();
    // Reflect the new bindings/rules on the hook thread (it owns the hotkeys and the
    // WinEvent hook).
    if (g_hookThreadId) {
        PostThreadMessageW(g_hookThreadId, WM_APP_SETTINGS_CHANGED, 0, 0);
    }
    ApplyRulesToExistingWindows();
}

void ToolModUninit() {
    g_quit = true;

    if (g_hookThreadId) {
        PostThreadMessageW(g_hookThreadId, WM_QUIT, 0, 0);
    }
    if (g_hookThread) {
        WaitForSingleObject(g_hookThread, 2000);
        CloseHandle(g_hookThread);
        g_hookThread = nullptr;
        g_hookThreadId = 0;
    }

    if (g_workEvent) {
        SetEvent(g_workEvent);
    }
    if (g_workerThread) {
        WaitForSingleObject(g_workerThread, 2000);
        CloseHandle(g_workerThread);
        g_workerThread = nullptr;
    }
    if (g_workEvent) {
        CloseHandle(g_workEvent);
        g_workEvent = nullptr;
    }

    if (g_winEventHook) {
        UnhookWinEvent(g_winEventHook);
        g_winEventHook = nullptr;
    }

    g_savedPlacements.clear();
    {
        std::lock_guard<std::mutex> lock(g_workQueueMutex);
        g_workQueue.clear();
    }
    {
        std::lock_guard<std::mutex> lock(g_ruleHandledMutex);
        g_ruleHandledWindows.clear();
    }
}

////////////////////////////////////////////////////////////////////////////////
}  // namespace snapCommander

//////// move ////////
namespace moveToMonitor {




#define HOTKEY_UP    1
#define HOTKEY_DOWN  2
#define HOTKEY_LEFT  3
#define HOTKEY_RIGHT 4

// Custom message posted from ToolModSettingsChanged to the hotkey thread
// so that (Un)RegisterHotKey always runs on the thread that owns the window.
#define WM_APP_SETTINGS_CHANGED (WM_APP + 1)

struct ModSettings {
    UINT modifierKeys = MOD_CONTROL | MOD_SHIFT;
    bool aroundMain   = true;
    int  targetUp     = -1;
    int  targetDown   = -1;
    int  targetLeft   = -1;
    int  targetRight  = -1;
    bool keepSize     = true;
    bool centerOnMove = false;
};

static ModSettings       g_settings;
static HANDLE            g_hThread = nullptr;
static HWND              g_hMsgWnd = nullptr;
static std::atomic<bool> g_running{false};

// ── settings ──────────────────────────────────────────────────────────────────

static UINT SettingToMod(const wchar_t* v) {
    if (wcscmp(v, L"none")           == 0) return 0;
    if (wcscmp(v, L"ctrl_alt")       == 0) return MOD_CONTROL | MOD_ALT;
    if (wcscmp(v, L"alt_shift")      == 0) return MOD_ALT     | MOD_SHIFT;
    if (wcscmp(v, L"ctrl_alt_shift") == 0) return MOD_CONTROL | MOD_ALT | MOD_SHIFT;
    return MOD_CONTROL | MOD_SHIFT;
}

static void LoadSettings() {
    PCWSTR s = Wh_GetStringSetting(L"modifierKeys");
    g_settings.modifierKeys = SettingToMod(s);
    Wh_FreeStringSetting(s);
    g_settings.targetUp     = Wh_GetIntSetting(L"targetUp");
    g_settings.targetDown   = Wh_GetIntSetting(L"targetDown");
    g_settings.targetLeft   = Wh_GetIntSetting(L"targetLeft");
    g_settings.targetRight  = Wh_GetIntSetting(L"targetRight");
    g_settings.keepSize     = Wh_GetIntSetting(L"keepSize") != 0;
    g_settings.centerOnMove = Wh_GetIntSetting(L"centerOnMove") != 0;
    g_settings.aroundMain   = Wh_GetIntSetting(L"aroundMain") != 0;
}

// ── monitor enumeration ───────────────────────────────────────────────────────

struct MonitorInfo {
    HMONITOR hMon;
    RECT     rcWork;
    RECT     rcMonitor;
    UINT     dpiX;
    UINT     dpiY;
};

static BOOL CALLBACK MonitorEnumProc(HMONITOR hMon, HDC, LPRECT, LPARAM lParam) {
    auto* list = reinterpret_cast<std::vector<MonitorInfo>*>(lParam);
    MONITORINFO mi = { sizeof(mi) };
    if (!GetMonitorInfo(hMon, &mi)) return TRUE;

    MonitorInfo info;
    info.hMon   = hMon;
    info.rcWork = mi.rcWork;
    info.rcMonitor = mi.rcMonitor;
    info.dpiX   = 96;
    info.dpiY   = 96;

    typedef HRESULT (WINAPI* GetDpiForMonitorFn)(HMONITOR, int, UINT*, UINT*);
    static auto fn = reinterpret_cast<GetDpiForMonitorFn>(
        GetProcAddress(GetModuleHandle(L"shcore.dll"), "GetDpiForMonitor"));
    if (fn) fn(hMon, 0 /*MDT_EFFECTIVE_DPI*/, &info.dpiX, &info.dpiY);

    list->push_back(info);
    return TRUE;
}

static std::vector<MonitorInfo> GetAllMonitors() {
    std::vector<MonitorInfo> list;
    EnumDisplayMonitors(nullptr, nullptr, MonitorEnumProc,
                        reinterpret_cast<LPARAM>(&list));
    std::sort(list.begin(), list.end(), [](const MonitorInfo& a, const MonitorInfo& b) {
        if (a.rcWork.left != b.rcWork.left)
            return a.rcWork.left < b.rcWork.left;
        return a.rcWork.top < b.rcWork.top;
    });
    return list;
}

static POINT RectCenter(const RECT& r) {
    return { (r.left + r.right) / 2, (r.top + r.bottom) / 2 };
}

static int FindMonitorIndex(const std::vector<MonitorInfo>& monitors, HMONITOR hMon) {
    for (int i = 0; i < (int)monitors.size(); i++)
        if (monitors[i].hMon == hMon) return i;
    return -1;
}

static void LogAllMonitors(const std::vector<MonitorInfo>& monitors) {
    Wh_Log(L"=== Move Window to Monitor v6: %d monitor(s) detected ===",
           (int)monitors.size());
    Wh_Log(L"Sorted left-to-right, then top-to-bottom:");
    for (int i = 0; i < (int)monitors.size(); i++) {
        const auto& m = monitors[i];
        int w = m.rcWork.right  - m.rcWork.left;
        int h = m.rcWork.bottom - m.rcWork.top;
        Wh_Log(L"  Index %d | pos (%d, %d) | size %dx%d | DPI %u",
               i, m.rcWork.left, m.rcWork.top, w, h, m.dpiX);
    }
    Wh_Log(L"Settings: UP=%d DOWN=%d LEFT=%d RIGHT=%d  keepSize=%d  center=%d",
           g_settings.targetUp, g_settings.targetDown,
           g_settings.targetLeft, g_settings.targetRight,
           (int)g_settings.keepSize, (int)g_settings.centerOnMove);
}

// ── window moving ─────────────────────────────────────────────────────────────

enum class Direction { Up, Down, Left, Right };

// rcNormalPosition is in workspace coordinates (offset by the work area of
// the window's monitor) unless the window is a tool window, which uses screen
// coordinates.
static POINT WorkspaceOffset(HWND hwnd, const MonitorInfo& mon) {
    if (GetWindowLongPtr(hwnd, GWL_EXSTYLE) & WS_EX_TOOLWINDOW) return { 0, 0 };
    return { mon.rcWork.left - mon.rcMonitor.left, mon.rcWork.top - mon.rcMonitor.top };
}

static void MoveWindowToMonitor(HWND hwnd, const MonitorInfo& src, const MonitorInfo& dst) {
    if (!altSnapDrag::CanActOnRootWindow(hwnd)) return;
    // Maximized and minimized windows: move the restored rectangle with
    // SetWindowPlacement so the window keeps its state on the new monitor.
    bool usePlacement = IsZoomed(hwnd) || IsIconic(hwnd);

    WINDOWPLACEMENT wp = { sizeof(wp) };
    RECT rcWin = {};
    if (usePlacement) {
        if (!GetWindowPlacement(hwnd, &wp)) return;
        rcWin = wp.rcNormalPosition;
        POINT ofs = WorkspaceOffset(hwnd, src);
        OffsetRect(&rcWin, ofs.x, ofs.y);
    } else {
        GetWindowRect(hwnd, &rcWin);
        // Borderless fullscreen: cover the destination monitor instead.
        if (EqualRect(&rcWin, &src.rcMonitor)) {
            const RECT& m = dst.rcMonitor;
            SetWindowPos(hwnd, nullptr, m.left, m.top, m.right - m.left,
                         m.bottom - m.top, SWP_NOZORDER | SWP_NOACTIVATE);
            return;
        }
    }

    int ww   = rcWin.right  - rcWin.left;
    int wh   = rcWin.bottom - rcWin.top;
    int srcW = src.rcWork.right  - src.rcWork.left;
    int srcH = src.rcWork.bottom - src.rcWork.top;
    int dstW = dst.rcWork.right  - dst.rcWork.left;
    int dstH = dst.rcWork.bottom - dst.rcWork.top;

    float relX = srcW > 0 ? (float)(rcWin.left - src.rcWork.left) / srcW : 0.0f;
    float relY = srcH > 0 ? (float)(rcWin.top  - src.rcWork.top)  / srcH : 0.0f;

    int newW, newH;
    if (g_settings.keepSize) {
        float dpiScaleX = (dst.dpiX > 0 && src.dpiX > 0)
                          ? (float)dst.dpiX / src.dpiX : 1.0f;
        float dpiScaleY = (dst.dpiY > 0 && src.dpiY > 0)
                          ? (float)dst.dpiY / src.dpiY : 1.0f;
        newW = (int)(ww * dpiScaleX);
        newH = (int)(wh * dpiScaleY);
    } else {
        newW = (int)(ww * (float)dstW / srcW);
        newH = (int)(wh * (float)dstH / srcH);
    }

    int newX, newY;
    if (g_settings.centerOnMove) {
        newX = dst.rcWork.left + (dstW - newW) / 2;
        newY = dst.rcWork.top  + (dstH - newH) / 2;
    } else {
        newX = dst.rcWork.left + (int)(relX * dstW);
        newY = dst.rcWork.top  + (int)(relY * dstH);
    }

    if (newX + newW > dst.rcWork.right)  newX = dst.rcWork.right  - newW;
    if (newY + newH > dst.rcWork.bottom) newY = dst.rcWork.bottom - newH;
    if (newX < dst.rcWork.left)          newX = dst.rcWork.left;
    if (newY < dst.rcWork.top)           newY = dst.rcWork.top;

    if (!usePlacement) {
        snapCommander::AnimateWindowRect(hwnd, RECT{newX, newY, newX + newW, newY + newH});
        SetWindowPos(hwnd, nullptr, newX, newY, newW, newH,
                     SWP_NOZORDER | SWP_NOACTIVATE);
        return;
    }

    POINT ofs = WorkspaceOffset(hwnd, dst);
    wp.rcNormalPosition = { newX - ofs.x, newY - ofs.y,
                            newX - ofs.x + newW, newY - ofs.y + newH };
    wp.flags &= ~WPF_SETMINPOSITION;
    SetWindowPlacement(hwnd, &wp);

    // If the window stayed maximized on the old monitor, restore (onto the new
    // normal rectangle) and re-maximize synchronously.
    if (IsZoomed(hwnd) && MonitorFromWindow(hwnd, MONITOR_DEFAULTTONEAREST) != dst.hMon) {
        ShowWindow(hwnd, SW_RESTORE);
        ShowWindow(hwnd, SW_MAXIMIZE);
    }
}

static void MoveActiveWindowInDirection(Direction dir) {
    HWND hwnd = GetForegroundWindow();
    if (!hwnd) return;

    HMONITOR hCurrent = MonitorFromWindow(hwnd, MONITOR_DEFAULTTONEAREST);
    MONITORINFO miCurrent = { sizeof(miCurrent) };
    if (!GetMonitorInfo(hCurrent, &miCurrent)) return;

    auto monitors = GetAllMonitors();
    int  curIdx   = FindMonitorIndex(monitors, hCurrent);
    if (curIdx < 0) return;

    int fixedIndex = -1;
    switch (dir) {
        case Direction::Up:    fixedIndex = g_settings.targetUp;    break;
        case Direction::Down:  fixedIndex = g_settings.targetDown;  break;
        case Direction::Left:  fixedIndex = g_settings.targetLeft;  break;
        case Direction::Right: fixedIndex = g_settings.targetRight; break;
    }

    if (fixedIndex >= (int)monitors.size()) fixedIndex = -1; // Missing saved display: use spatial movement.
    int dstIdx = -1;

    if (fixedIndex >= 0 && fixedIndex < (int)monitors.size()) {
        if (fixedIndex != curIdx)
            dstIdx = fixedIndex;
    }

    // Around the main screen: Down is the main monitor itself, the other arrows
    // the monitor on that side of it, wherever the window is now.
    int fromIdx = curIdx;
    int mainIdx = FindMonitorIndex(monitors, MonitorFromPoint({0, 0}, MONITOR_DEFAULTTOPRIMARY));
    if (fixedIndex < 0 && g_settings.aroundMain && mainIdx >= 0) fromIdx = mainIdx;

    if (dstIdx < 0 && fixedIndex < 0) {
        POINT curCenter = RectCenter(monitors[fromIdx].rcWork);
        int   bestScore = INT_MAX;

        for (int i = 0; i < (int)monitors.size(); i++) {
            if (i == fromIdx) continue;
            POINT c  = RectCenter(monitors[i].rcWork);
            int   dx = c.x - curCenter.x;
            int   dy = c.y - curCenter.y;
            bool  candidate = false;
            int   primary   = 0;

            switch (dir) {
                case Direction::Up:
                    candidate = (dy < 0) && (abs(dy) >= abs(dx)); primary = -dy; break;
                case Direction::Down:
                    candidate = (dy > 0) && (abs(dy) >= abs(dx)); primary = dy;  break;
                case Direction::Left:
                    candidate = (dx < 0) && (abs(dx) >= abs(dy)); primary = -dx; break;
                case Direction::Right:
                    candidate = (dx > 0) && (abs(dx) >= abs(dy)); primary = dx;  break;
            }

            if (candidate && primary < bestScore) {
                bestScore = primary;
                dstIdx    = i;
            }
        }
    }

    if (dstIdx < 0 && fixedIndex < 0 && fromIdx != curIdx) dstIdx = fromIdx;
    if (dstIdx < 0 || dstIdx == curIdx) return;
    MoveWindowToMonitor(hwnd, monitors[curIdx], monitors[dstIdx]);
    MoveCursorToWindow(hwnd);
}

// ── hotkey thread ─────────────────────────────────────────────────────────────

static void RegisterHotkeys(HWND hwnd) {
    if (!g_settings.modifierKeys) return;  // Off: Alt+Shift+number sends instead.
    UINT mod = g_settings.modifierKeys | MOD_NOREPEAT;
    const std::pair<int, UINT> keys[] = {
        {HOTKEY_UP, VK_UP}, {HOTKEY_DOWN, VK_DOWN}, {HOTKEY_LEFT, VK_LEFT}, {HOTKEY_RIGHT, VK_RIGHT}};
    for (const auto& key : keys) {
        if (swm::IsReservedHotkey(g_settings.modifierKeys, key.second)) {
            Wh_Log(L"Send to monitor: a window manager key uses this arrow; skipped");
            continue;
        }
        RegisterHotKey(hwnd, key.first, mod, key.second);
    }
}

static void UnregisterHotkeys(HWND hwnd) {
    UnregisterHotKey(hwnd, HOTKEY_UP);
    UnregisterHotKey(hwnd, HOTKEY_DOWN);
    UnregisterHotKey(hwnd, HOTKEY_LEFT);
    UnregisterHotKey(hwnd, HOTKEY_RIGHT);
}

static LRESULT CALLBACK HotkeyWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    if (msg == WM_HOTKEY) {
        switch ((int)wParam) {
            case HOTKEY_UP:    MoveActiveWindowInDirection(Direction::Up);    break;
            case HOTKEY_DOWN:  MoveActiveWindowInDirection(Direction::Down);  break;
            case HOTKEY_LEFT:  MoveActiveWindowInDirection(Direction::Left);  break;
            case HOTKEY_RIGHT: MoveActiveWindowInDirection(Direction::Right); break;
        }
        return 0;
    }

    if (msg == WM_APP_SETTINGS_CHANGED) {
        // (Un)RegisterHotKey must run on the thread that owns the window
        UnregisterHotkeys(hwnd);
        LoadSettings();
        auto monitors = GetAllMonitors();
        LogAllMonitors(monitors);
        if (!swm::IsPaused()) RegisterHotkeys(hwnd);
        return 0;
    }

    if (msg == swm::kPauseChangedMessage) {
        UnregisterHotkeys(hwnd);
        if (!swm::IsPaused()) RegisterHotkeys(hwnd);
        return 0;
    }

    return DefWindowProc(hwnd, msg, wParam, lParam);
}

static void HotkeyThreadProc() {
    const wchar_t CLASS_NAME[] = L"WH_MoveToMonitor_MsgWnd";
    WNDCLASSEX wc = {};
    wc.cbSize        = sizeof(wc);
    wc.lpfnWndProc   = HotkeyWndProc;
    wc.hInstance     = GetModuleHandle(nullptr);
    wc.lpszClassName = CLASS_NAME;
    RegisterClassEx(&wc);

    HWND hwnd = CreateWindowEx(0, CLASS_NAME, nullptr, 0, 0, 0, 0, 0,
                               HWND_MESSAGE, nullptr, GetModuleHandle(nullptr), nullptr);
    if (!hwnd) { Wh_Log(L"Failed to create message window"); return; }

    g_hMsgWnd = hwnd;
    RegisterHotkeys(hwnd);

    MSG msg;
    while (g_running && GetMessage(&msg, nullptr, 0, 0) > 0) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    UnregisterHotkeys(hwnd);
    DestroyWindow(hwnd);
    g_hMsgWnd = nullptr;
    UnregisterClass(CLASS_NAME, GetModuleHandle(nullptr));
}

static DWORD WINAPI HotkeyThreadEntry(LPVOID) {
    HotkeyThreadProc();
    return 0;
}

// ── Tool mod callbacks (renamed as required by the tool mod pattern) ──────────

BOOL ToolModInit() {
    Wh_Log(L"MoveWindowToMonitor v6: Init");
    LoadSettings();
    auto monitors = GetAllMonitors();
    LogAllMonitors(monitors);
    g_running = true;
    g_hThread = CreateThread(nullptr, 0, HotkeyThreadEntry, nullptr, 0, nullptr);
    return g_hThread != nullptr;
}

void ToolModSettingsChanged() {
    Wh_Log(L"MoveWindowToMonitor: Settings changed, notifying hotkey thread");
    if (g_hMsgWnd) PostMessage(g_hMsgWnd, WM_APP_SETTINGS_CHANGED, 0, 0);
}

void ToolModUninit() {
    g_running = false;
    if (g_hMsgWnd) PostMessage(g_hMsgWnd, WM_QUIT, 0, 0);
    if (g_hThread) {
        WaitForSingleObject(g_hThread, 3000);
        CloseHandle(g_hThread);
        g_hThread = nullptr;
    }
}

////////////////////////////////////////////////////////////////////////////////
}  // namespace moveToMonitor

// ==WindhawkModSettings==
/*
- modifier: alt
  $name: Snap shortcut modifier
  $description: >-
    Added to every snap shortcut below. Choose None to use only the keys typed
    into each shortcut.
  $options:
    - none: None
    - alt: Alt
    - ctrl: Ctrl
    - shift: Shift
    - win: Win
    - alt_ctrl: Alt + Ctrl
    - alt_shift: Alt + Shift
    - ctrl_shift: Ctrl + Shift
    - win_alt: Win + Alt
    - win_ctrl: Win + Ctrl
    - win_shift: Win + Shift
- shortcuts:
    - keyLeftHalf: q
      $name: Left half
      $description: >-
        Type a key such as "q", "left" or "ctrl+q". The modifier above is added
        on top. Leave empty to turn the shortcut off. Same for every key below.
    - keyRightHalf: w
      $name: Right half
    - keyTopHalf: e
      $name: Top half
    - keyBottomHalf: r
      $name: Bottom half
    - keyCenterHalf: c
      $name: Center half
      $description: A half-width strip in the middle of the screen, full height.
    - keyTopLeft: u
      $name: Top-left quarter
    - keyTopRight: i
      $name: Top-right quarter
    - keyBottomLeft: j
      $name: Bottom-left quarter
    - keyBottomRight: k
      $name: Bottom-right quarter
    - keyMaximize: h
      $name: Maximize
      $description: Fills the whole screen and ignores the gaps.
    - keyAlmostMaximize: y
      $name: Almost maximize
      $description: Fills the screen but keeps the gaps around the window.
    - keyCenter: g
      $name: Center
      $description: Moves the window to the middle of the screen. Keeps its size unless you set one under Layout.
    - keyMinimize: ""
      $name: Minimize
      $description: Off by default, because the Minimize shortcut further down already uses Alt+M.
    - keyNextDisplay: "]"
      $name: Next monitor
    - keyPrevDisplay: "["
      $name: Previous monitor
    - keySmaller: "-"
      $name: Make smaller
      $description: Shrinks the window around its middle.
    - keyLarger: plus
      $name: Make larger
      $description: >-
        Grows the window around its middle. Write this key as "plus" or "=",
        because "+" joins the keys of a shortcut.
    - keyRestore: z
      $name: Undo snap
      $description: Puts the window back where it was before the first snap.
  $name: Snap shortcuts
  $description: Keys that snap the active window to a part of the screen.
- hotkeyMaximize: ''
  $name: Toggle maximize
  $description: >-
    Type the whole shortcut, such as "Alt+X" or "Ctrl+Alt+X". It must include
    at least one of Alt, Ctrl, Shift or Win. Leave empty to turn it off. Same
    for every shortcut below. Off by default: Alt+F fills the screen instead
    (see Fill the screen).
- hotkeyMinimize: Alt+M
  $name: Minimize
- hotkeyRestoreMinimized: Alt+Shift+M
  $name: Restore minimized window
  $description: >-
    Brings back the window you minimized last, at its old size and place.
    Press again for the one before it.
- hotkeyMRUUp: Alt+PageUp
  $name: Bring back the window sent behind
  $description: >-
    Undoes one step of the key below: the window at the back of the stack
    comes to the front.
- hotkeyMRUDown: Alt+PageDown
  $name: Show the window behind
  $description: >-
    When windows are stacked on top of each other, brings up the one behind
    the active window and sends the active one to the back. Press again to
    walk the whole stack. Windows tiled beside it are left alone.
- hotkeyClose: Alt+Shift+Q
  $name: Close
- hotkeyMenu: ''
  $name: Open the window menu
- hotkeyTopmost: ''
  $name: Toggle always on top
- hotkeyLower: ''
  $name: Send window to the back
- hotkeyCenter: ''
  $name: Center window
- hotkeySideSnap: ''
  $name: Snap to the nearest screen side
- hotkeyPause: Ctrl+Shift+P
  $name: Pause the window manager
  $description: >-
    Turns every drag, shortcut and rule off until you press it again. Handy in
    games and drawing apps that need Alt. Ctrl+Shift+P is also the command
    palette in VS Code and a private window in Firefox.
- hotkeyResizeMode: Alt+Shift+R
  $name: Resize with the keyboard
  $description: >-
    Arrow keys or H J K L then resize the active window. Hold Shift to move it
    instead. Press Esc or Enter when you are done.
- hotkeyFocusLeft: Alt+Left
  $name: Focus the window to the left
  $description: >-
    Switches to the nearest window on that side, even on another monitor, and
    the mouse pointer jumps to it. Taking Alt+Left and Alt+Right means browsers
    and File Explorer lose them for Back and Forward.
- hotkeyFocusRight: Alt+Right
  $name: Focus the window to the right
- hotkeyFocusUp: Alt+Up
  $name: Focus the window above
- hotkeyFocusDown: Alt+Down
  $name: Focus the window below
- hotkeyMoveLeft: Alt+Shift+Left
  $name: Move the window left
  $description: >-
    A tiled window trades places with its neighbour, or moves into the next
    column or monitor. A floating window snaps to that half of the screen.
- hotkeyMoveRight: Alt+Shift+Right
  $name: Move the window right
- hotkeyMoveUp: Alt+Shift+Up
  $name: Move the window up
- hotkeyMoveDown: Alt+Shift+Down
  $name: Move the window down
- hotkeyGrowLeft: Ctrl+Alt+Shift+Left
  $name: Grow the window to the left
  $description: >-
    Pushes that edge of the window out. Hold the keys to keep going. At the
    edge of the screen, the far edge comes in instead.
- hotkeyGrowRight: Ctrl+Alt+Shift+Right
  $name: Grow the window to the right
- hotkeyGrowUp: Ctrl+Alt+Shift+Up
  $name: Grow the window upward
- hotkeyGrowDown: Ctrl+Alt+Shift+Down
  $name: Grow the window downward
- hotkeyToggleTiling: Alt+T
  $name: Tile or float the window
  $description: >-
    Takes the active window out of the tiles so you can place it anywhere, or
    puts a floating window back in.
- hotkeyTilingDirection: ''
  $name: Switch the tiling direction
  $description: >-
    Turns the active window's group from side by side to stacked, or back.
    Example: "Alt+V".
- hotkeyFill: Alt+F
  $name: Fill the screen
  $description: >-
    Like GlazeWM's fullscreen: the window fills the screen but keeps the gaps
    around it. Press again to put it back in its tile or old spot.
- hotkeyBorderless: Ctrl+Shift+F
  $name: Borderless fullscreen
  $description: >-
    Like ShareX's "Make active window borderless": no title bar or borders, and
    the window covers the whole monitor, taskbar included. Press again to give
    the window its frame and size back. If another app already uses the
    shortcut, it starts working once that app lets go of it.
- hotkeyMonitor1: Alt+1
  $name: Focus monitor 1
  $description: >-
    Like GlazeWM's workspace keys, one per monitor. Monitors count left to
    right along the main monitor's row, then the ones above or below. With a
    left, main, right and top screen: 1 left, 2 main, 3 right, 4 top. The front
    window there gets focus and the pointer goes with it.
- hotkeyMonitor2: Alt+2
  $name: Focus monitor 2
- hotkeyMonitor3: Alt+3
  $name: Focus monitor 3
- hotkeyMonitor4: Alt+4
  $name: Focus monitor 4
- hotkeySendMonitor1: Alt+Shift+1
  $name: Send the window to monitor 1
  $description: >-
    A tiled window takes a tile there; a floating one keeps its size and spot
    on the new screen.
- hotkeySendMonitor2: Alt+Shift+2
  $name: Send the window to monitor 2
- hotkeySendMonitor3: Alt+Shift+3
  $name: Send the window to monitor 3
- hotkeySendMonitor4: Alt+Shift+4
  $name: Send the window to monitor 4
- hotkeyDesktop1: Ctrl+Alt+Shift+1
  $name: Switch to desktop 1
  $description: >-
    Windows virtual desktops, each with its own tiles. A desktop that doesn't
    exist yet is made. The switch happens when you let go of the keys.
- hotkeyDesktop2: Ctrl+Alt+Shift+2
  $name: Switch to desktop 2
- hotkeyDesktop3: Ctrl+Alt+Shift+3
  $name: Switch to desktop 3
- hotkeyDesktop4: Ctrl+Alt+Shift+4
  $name: Switch to desktop 4
- hotkeyDesktop5: Ctrl+Alt+Shift+5
  $name: Switch to desktop 5
- hotkeyDesktop6: Ctrl+Alt+Shift+6
  $name: Switch to desktop 6
- hotkeyDesktop7: Ctrl+Alt+Shift+7
  $name: Switch to desktop 7
- hotkeyDesktop8: Ctrl+Alt+Shift+8
  $name: Switch to desktop 8
- hotkeyDesktop9: Ctrl+Alt+Shift+9
  $name: Switch to desktop 9
- tiling:
    - enabled: true
      $name: Tile new windows
      $description: >-
        New app windows fill the screen side by side, like GlazeWM. Dialogs,
        small windows and windows on top stay floating.
    - existing: true
      $name: Tile windows already open
      $description: When on, the windows already open are tiled when the mod starts.
    - innerGap: 20
      $name: Gap between windows (px)
      $description: >-
        Space between tiled windows. The space at the screen edges comes from
        the Layout gaps. 0 to 100 (Suggested: 20).
    - resizeStep: 5
      $name: Grow step (%)
      $description: >-
        How far each press of a grow key moves the edge, as a share of the
        screen. 1 to 20 (Suggested: 5).
    - floatApps: [""]
      $name: Apps that never tile
      $description: >-
        One app name per entry, such as "steam" or "obs64". These open
        floating. Apps with a placement rule never tile either.
  $name: Tiling
  $description: Which windows tile, and the space between them.
- resizeMode:
    - step: 2
      $name: Step size (%)
      $description: >-
        How far each key press resizes or moves the window, as a share of the
        screen. 1 to 20 (Suggested: 2).
    - timeout: 10
      $name: Finish after (seconds)
      $description: >-
        Leaves resize mode on its own when you stop pressing keys. 3 to 60
        (Suggested: 10).
  $name: Keyboard resize
  $description: How the "Resize with the keyboard" shortcut behaves.
- moveTrigger:
  - button: left
    $name: Mouse button
    $options:
    - left: Left button
    - right: Right button
    - middle: Middle button
    - x1: Back button
    - x2: Forward button
  - ctrl: false
    $name: Hold Ctrl
  - alt: true
    $name: Hold Alt
  - shift: false
    $name: Hold Shift
  - win: false
    $name: Hold Win
  - delay: 0
    $name: Hold time (ms)
    $description: >-
      How long to hold the button before the window starts moving. A shorter
      press goes to the window as a normal click. 0 to 500 (Suggested: 0).
  - magnet: 20
    $name: Magnetic edges with Ctrl (px)
    $description: >-
      Hold Ctrl as well while you drag, and the window's edges cling to the
      screen edges and to other windows once they come this close. 0 turns it
      off. 0 to 60 (Suggested: 20).
  $name: Move with the mouse
  $description: The mouse button and keys to hold while you drag a window.
- sizeTrigger:
  - button: right
    $name: Mouse button
    $options:
    - left: Left button
    - right: Right button
    - middle: Middle button
    - x1: Back button
    - x2: Forward button
  - ctrl: false
    $name: Hold Ctrl
  - alt: true
    $name: Hold Alt
  - shift: false
    $name: Hold Shift
  - win: false
    $name: Hold Win
  - delay: 0
    $name: Hold time (ms)
    $description: >-
      How long to hold the button before the window starts resizing. A shorter
      press goes to the window as a normal click. 0 to 500 (Suggested: 0).
  $name: Resize with the mouse
  $description: >-
    The mouse button and keys to hold while you resize a window. The edge or
    corner nearest to where you press follows the mouse.
- dragWindowsWithoutTitleBar: false
  $name: Move windows without a title bar
  $description: >-
    Also move popups, launchers and flyouts that have no title bar. When off,
    only normal windows move.
- explorerTitleStripDrag: true
  $name: Move File Explorer by its title strip
  $description: >-
    Pressing the empty strip at the top of a File Explorer window moves the
    window instead of grabbing the tab.
- sizeWindowsWithoutSizingBorder: true
  $name: Resize windows without a border
  $description: >-
    Also resize borderless windows such as the Ditto and Flow Launcher popups.
    A short click still runs the click action below.
- middleAction: menu
  $name: Middle click
  $description: What a middle click does while you hold the move keys.
  $options:
    - menu: Open the window menu
    - maximize: Toggle maximize
    - minimize: Minimize
    - close: Close
    - topmost: Toggle always on top
    - lower: Send to the back
    - center: Center
    - sideSnap: Snap to the nearest side
    - none: Nothing
- rightClickAction: maximize
  $name: Right click without dragging
  $description: A short right click. Dragging with the right button still resizes.
  $options:
    - menu: Open the window menu
    - maximize: Toggle maximize
    - minimize: Minimize
    - close: Close
    - topmost: Toggle always on top
    - lower: Send to the back
    - center: Center
    - sideSnap: Snap to the nearest side
    - none: Nothing
- x1Action: none
  $name: Back button click
  $options:
    - menu: Open the window menu
    - maximize: Toggle maximize
    - minimize: Minimize
    - close: Close
    - topmost: Toggle always on top
    - lower: Send to the back
    - center: Center
    - sideSnap: Snap to the nearest side
    - none: Nothing
- x2Action: none
  $name: Forward button click
  $options:
    - menu: Open the window menu
    - maximize: Toggle maximize
    - minimize: Minimize
    - close: Close
    - topmost: Toggle always on top
    - lower: Send to the back
    - center: Center
    - sideSnap: Snap to the nearest side
    - none: Nothing
- leftDoubleAction: none
  $name: Left double click
  $options:
    - menu: Open the window menu
    - maximize: Toggle maximize
    - minimize: Minimize
    - close: Close
    - topmost: Toggle always on top
    - lower: Send to the back
    - center: Center
    - sideSnap: Snap to the nearest side
    - none: Nothing
- middleDoubleAction: none
  $name: Middle double click
  $options:
    - menu: Open the window menu
    - maximize: Toggle maximize
    - minimize: Minimize
    - close: Close
    - topmost: Toggle always on top
    - lower: Send to the back
    - center: Center
    - sideSnap: Snap to the nearest side
    - none: Nothing
- rightDoubleAction: none
  $name: Right double click
  $options:
    - menu: Open the window menu
    - maximize: Toggle maximize
    - minimize: Minimize
    - close: Close
    - topmost: Toggle always on top
    - lower: Send to the back
    - center: Center
    - sideSnap: Snap to the nearest side
    - none: Nothing
- dimensions:
    - gapTop: 0
      $name: Top gap
      $description: "Space above a snapped window. 0 to 100 (Suggested: 8)."
    - gapBottom: 0
      $name: Bottom gap
      $description: "Space below a snapped window. 0 to 100 (Suggested: 8)."
    - gapLeft: 0
      $name: Left gap
      $description: "Space to the left of a snapped window. 0 to 100 (Suggested: 8)."
    - gapRight: 0
      $name: Right gap
      $description: "Space to the right of a snapped window. 0 to 100 (Suggested: 8)."
    - gapUnit: px
      $name: Gap unit
      $description: >-
        Percent sizes each gap by the screen, so 1 means 1% of the screen width
        for left and right gaps and 1% of the height for top and bottom gaps.
      $options:
        - px: Pixels
        - percent: Percent of the screen
    - gapScaling: exact
      $name: Gap scaling
      $description: >-
        Scale with display makes pixel gaps grow on monitors set above 100%
        scale, so they look the same size on every screen.
      $options:
        - exact: Exact pixels
        - dpi: Scale with display
    - gapMode: even
      $name: Gaps between windows
      $description: >-
        Even keeps the gap between two windows the same as the gap at the screen
        edge. Full puts the whole gap on every side, so it doubles between
        windows. Screen edges only lets side-by-side windows touch.
      $options:
        - even: Even
        - full: Full on every side
        - screen: Screen edges only
    - almostMaximizeGap: ""
      $name: Almost maximize gap
      $description: >-
        A gap for Almost maximize only, on all four sides. Leave empty to use
        the gaps above. 0 to 200 (Suggested: empty).
    - centerWidth: ""
      $name: Center width (pixels)
      $description: Width for the Center action. Leave empty to keep the window's width.
    - centerHeight: ""
      $name: Center height (pixels)
      $description: Height for the Center action. Leave empty to keep the window's height.
    - resizeStep: 5
      $name: Make smaller or larger step (%)
      $description: >-
        How much Make smaller and Make larger change the window on each press.
        1 to 50 (Suggested: 5).
  $name: Layout
  $description: Gaps around snapped windows and sizes for Center.
- modifierKeys: "none"
  $name: Send to monitor with arrow keys
  $description: >-
    Hold these and press an arrow key to send the active window to another
    monitor. Off by default, since Alt+Shift+number does it. Ctrl + Shift also
    selects text word by word in editors.
  $options:
    - none: "Off"
    - ctrl_alt: Ctrl + Alt
    - ctrl_shift: Ctrl + Shift
    - alt_shift: Alt + Shift
    - ctrl_alt_shift: Ctrl + Alt + Shift
- aroundMain: true
  $name: Arrows pick the screens around the main one
  $description: >-
    When on, Down sends the window to the main monitor and the other arrows to
    the monitor above, left or right of it, wherever the window is now. When
    off, the arrows go from the window's current monitor.
- targetUp: -1
  $name: Monitor for the Up arrow
  $description: >-
    -1 picks the nearest monitor above. 0 or more picks that monitor number
    (Suggested: -1).
- targetDown: -1
  $name: Monitor for the Down arrow
  $description: -1 picks the nearest monitor below. 0 or more picks that monitor number.
- targetLeft: -1
  $name: Monitor for the Left arrow
  $description: -1 picks the nearest monitor to the left. 0 or more picks that monitor number.
- targetRight: -1
  $name: Monitor for the Right arrow
  $description: -1 picks the nearest monitor to the right. 0 or more picks that monitor number.
- keepSize: true
  $name: Keep the window size
  $description: When off, the window grows or shrinks to match the new monitor.
- centerOnMove: false
  $name: Center on the new monitor
  $description: When off, the window keeps the same spot relative to the screen.
- cursorFollowsWindow: false
  $name: Bring the mouse along
  $description: >-
    When you send a window to another monitor with the keyboard, the mouse
    pointer jumps to the middle of that window.
- focus:
    - followCursor: windows
      $name: Focus follows the mouse
      $description: >-
        Hovering a window makes it the active one, so you can type into it
        without clicking. Leave as Windows has it keeps your Windows setting.
      $options:
        - windows: Leave as Windows has it
        - hover: On, keep the window where it is
        - raise: On, and bring the window to the front
    - followDelay: 150
      $name: Hover time (ms)
      $description: >-
        How long the mouse rests on a window before it becomes active.
        10 to 1000 (Suggested: 150).
    - cursorJump: never
      $name: Move the mouse to the active window
      $description: >-
        After you switch windows with the keyboard, such as Alt+Tab, the mouse
        pointer jumps to the middle of the new window. It never moves while a
        mouse button is down or when the pointer is already on that window.
      $options:
        - never: Never
        - monitor: Only when the window is on another monitor
        - window: Every time the active window changes
  $name: Focus and mouse
  $description: Which window is active, and where the mouse pointer goes.
- effects:
    - animation: 180
      $name: Animation length (ms)
      $description: >-
        How long windows take to glide into place when they tile, float, fill,
        snap or go borderless. 0 turns it off. 0 to 400 (Suggested: 180).
    - inactiveOpacity: 100
      $name: Background window opacity (%)
      $description: >-
        Makes every window except the active one see-through. 100 turns this
        off. 50 to 100 (Suggested: 92).
    - statusPopup: show
      $name: Status popup
      $description: >-
        A small popup when you pause or resume, and while keyboard resize is
        on.
      $options:
        - show: Show
        - hide: Hide
  $name: Look
  $description: >-
    Window borders come from Seamless Borders and corners from Custom Window
    Corner Radius, so they are not repeated here.
- rules:
    - - executable_names: ""
        $name: App names
        $description: >-
          One or more app file names, split by commas, such as "notepad;
          calc.exe". Upper or lower case both work and ".exe" is optional. Use
          * for every app. Leave empty to match by title or class only.
      - window_title: ""
        $name: Window title
        $description: Text in the window's title. Leave empty to match any title.
      - window_class: ""
        $name: Window class
        $description: >-
          The window's class name, for advanced use. Leave empty to match any
          class.
      - match_mode: contains
        $name: How the title and class match
        $options:
          - contains: Contains the text
          - equals: Is exactly the text
          - regex: Matches a pattern (regex)
          - not_regex: Does not match a pattern (regex)
      - action: maximize
        $name: Action
        $options:
          - left-half: Left half
          - right-half: Right half
          - top-half: Top half
          - bottom-half: Bottom half
          - center-half: Center half
          - top-left: Top-left quarter
          - top-right: Top-right quarter
          - bottom-left: Bottom-left quarter
          - bottom-right: Bottom-right quarter
          - maximize: Maximize
          - almost-maximize: Almost maximize
          - center: Center
          - minimize: Minimize
          - none: Leave the position alone
          - ignore: Leave this app alone completely
      - no_resize: false
        $name: Keep the window size
        $description: >-
          Moves the window into place but keeps its size. Has no effect on
          Minimize.
      - apply_when: open
        $name: When to apply
        $options:
          - open: When it opens, and to open windows when the mod starts
          - new: Only when it opens
          - title: When it opens or its title changes
      - on_top: false
        $name: Keep on top
        $description: Keeps the window above other windows.
      - opacity: 100
        $name: Opacity (%)
        $description: >-
          Makes the window see-through. 100 leaves it solid. 30 to 100
          (Suggested: 100).
  $name: App rules
  $description: >-
    Place, pin or skip chosen apps automatically. "Leave this app alone" turns
    off every drag, shortcut and effect for it, which helps with games. Add
    one item per rule; the first rule that matches wins.
*/
// ==/WindhawkModSettings==


// One elevated tool owns global input. Per-app hooks retain Explorer's title-strip behavior.
#include <sddl.h>
#include <windhawk_tool_mod.h>

static bool g_packDragInited;
static HANDLE g_globalMutex;


// ---------------------------------------------------------------------------------------------
// Seamless menu look for this mod's own menus.
// Windhawk runs tool mods in their own process, where Seamless Flyouts cannot reach, so the
// menus this mod shows get the same look here: blurred Catppuccin Mocha body, rounded corners,
// roomy rows, separators that run to the border, one soft hover with a blue outline, and
// submenus that open beside their parent with a small gap. Only this process is touched.
// ---------------------------------------------------------------------------------------------
#include <d2d1.h>
#include <dwmapi.h>
#include <uxtheme.h>
#include <vssym32.h>
#include <commctrl.h>

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
static thread_local HHOOK g_cbt = nullptr;
static thread_local INT g_depth = 0;

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

static LRESULT CALLBACK CbtProc(INT code, WPARAM wParam, LPARAM lParam)
{
    if (code == HCBT_CREATEWND && IsMenuWindow((HWND)wParam))
        SetWindowSubclass((HWND)wParam, MenuProc, kSubclassId, 0);
    return CallNextHookEx(nullptr, code, wParam, lParam);
}
static VOID BeginMenu()
{
    if (g_depth++ == 0) g_cbt = SetWindowsHookExW(WH_CBT, CbtProc, nullptr, GetCurrentThreadId());
}
static VOID EndMenu()
{
    if (--g_depth == 0 && g_cbt) { UnhookWindowsHookEx(g_cbt); g_cbt = nullptr; }
}

static BOOL WINAPI TrackPopupMenu_hook(HMENU m, UINT f, INT x, INT y, INT r, HWND h, const RECT* rc)
{
    BeginMenu();
    BOOL ret = TrackPopupMenu_orig(m, f, x, y, r, h, rc);
    EndMenu();
    return ret;
}
static BOOL WINAPI TrackPopupMenuEx_hook(HMENU m, UINT f, INT x, INT y, HWND h, LPTPMPARAMS p)
{
    BeginMenu();
    BOOL ret = TrackPopupMenuEx_orig(m, f, x, y, h, p);
    EndMenu();
    return ret;
}

// Returns TRUE when the menu part was drawn here.
static BOOL PaintMenuPart(HDC hdc, INT part, INT state, LPCRECT pRect, LPCRECT pClip)
{
    if (part == 26) { part = 27; state = 2; }                   // keyboard focus: same hover
    if ((part == 27 || part == MENU_POPUPITEM) && state == 2) {
        if (!g_hoverDC) g_hoverDC = MakeCache(18, 18, FALSE);
        if (!g_hoverDC) return FALSE;
        // Keep the same gap above and below as at the sides, so the first and last rows'
        // rounded hover stays clear of the menu's own rounded corners.
        RECT rc = *pRect;
        InflateRect(&rc, 0, -MulDiv(2, Dpi(), USER_DEFAULT_SCREEN_DPI));
        NineGrid(hdc, g_hoverDC, &rc, 9, 9, 8, 8);
        return TRUE;
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
        else if (prop == 10000) *m = {0, 0, 8, 8};
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
}

static VOID Uninit()
{
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

// ---------------------------------------------------------------------------------------------
// Pause, keyboard resize, focus, background window opacity, mouse jump and the status popup.
// Everything here runs in the elevated helper, except IsPaused, which the per-app parts call
// too and which then reads the helper's named event.
// ---------------------------------------------------------------------------------------------
#include <dwrite.h>
#include <cmath>
#include <shobjidl.h>

namespace swm {

// Defined after the tiling namespace, forward-declared so callers in it see it.
void FocusWindow(HWND hWnd);

constexpr WCHAR kPauseEventName[] = L"windhawk-seamless-window-manager-paused";
constexpr int kModeKeyBase = 0x6100;  // One id per entry in kModeKeyNames.
constexpr UINT kEffectsReloadMessage = WM_APP + 301;
constexpr UINT kRuleAlphaMessage = WM_APP + 302;
constexpr UINT kOsdShowMessage = WM_APP + 310;
constexpr UINT kOsdHideMessage = WM_APP + 311;
constexpr WCHAR kOsdClassName[] = L"SeamlessWM_Osd";

enum class FollowMode { Windows, Hover, Raise };
enum class JumpMode { Never, Monitor, Window };
enum OsdState : WPARAM { kOsdRunning, kOsdPaused, kOsdResize };

struct ModeKey {
    int key = 0;
    DWORD modifiers = 0;
};
// Directions run left, right, up, down.
constexpr PCWSTR kModeKeyNames[] = {
    L"hotkeyPause",     L"hotkeyResizeMode", L"hotkeyFocusLeft",       L"hotkeyFocusRight",
    L"hotkeyFocusUp",   L"hotkeyFocusDown",  L"hotkeyMoveLeft",        L"hotkeyMoveRight",
    L"hotkeyMoveUp",    L"hotkeyMoveDown",   L"hotkeyGrowLeft",        L"hotkeyGrowRight",
    L"hotkeyGrowUp",    L"hotkeyGrowDown",   L"hotkeyToggleTiling",    L"hotkeyTilingDirection",
    L"hotkeyFill",      L"hotkeyBorderless",
    L"hotkeyMonitor1",  L"hotkeyMonitor2",   L"hotkeyMonitor3",        L"hotkeyMonitor4",
    L"hotkeySendMonitor1", L"hotkeySendMonitor2", L"hotkeySendMonitor3", L"hotkeySendMonitor4",
    L"hotkeyDesktop1",  L"hotkeyDesktop2",   L"hotkeyDesktop3",        L"hotkeyDesktop4",
    L"hotkeyDesktop5",  L"hotkeyDesktop6",   L"hotkeyDesktop7",        L"hotkeyDesktop8",
    L"hotkeyDesktop9",
    L"hotkeyMRUUp",     L"hotkeyMRUDown",    L"hotkeyRestoreMinimized",
};
constexpr int kFirstMonitorKey = 18;
constexpr int kFirstSendMonitorKey = 22;
constexpr int kFirstDesktopKey = 26;
constexpr size_t kModeKeyCount = ARRAYSIZE(kModeKeyNames);
constexpr size_t kFirstGrowKey = 10;
constexpr size_t kLastGrowKey = 13;

struct Settings {
    std::array<ModeKey, kModeKeyCount> keys{};
    bool tiling = true;
    bool tileExisting = true;
    int innerGap = 20;
    int tileStep = 5;
    std::vector<std::wstring> floatApps;
    int resizeTimeoutMs = 10000;
    FollowMode follow = FollowMode::Windows;
    int followDelay = 150;
    JumpMode jump = JumpMode::Never;
    BYTE inactiveAlpha = 255;
    bool popup = true;
};
Settings g_swmSettings;
std::mutex g_swmSettingsMutex;

Settings GetSettings() {
    std::lock_guard<std::mutex> lock(g_swmSettingsMutex);
    return g_swmSettings;
}

UINT ToHotkeyMods(DWORD held) {
    return ((held & altSnapDrag::kModifierCtrl) ? MOD_CONTROL : 0) |
           ((held & altSnapDrag::kModifierAlt) ? MOD_ALT : 0) |
           ((held & altSnapDrag::kModifierShift) ? MOD_SHIFT : 0) |
           ((held & altSnapDrag::kModifierWin) ? MOD_WIN : 0);
}

// The snap and monitor keys skip any combination these keys already use.
bool IsReservedHotkey(UINT mods, UINT vk) {
    mods &= MOD_ALT | MOD_CONTROL | MOD_SHIFT | MOD_WIN;
    Settings s = GetSettings();
    for (const ModeKey& key : s.keys) {
        if (key.key && (UINT)key.key == vk && ToHotkeyMods(key.modifiers) == mods) {
            return true;
        }
    }
    return false;
}

//////// pause ////////

HANDLE g_pauseEvent;                        // Helper: created and owned.
std::atomic<HANDLE> g_openedPauseEvent{};   // Per-app: opened from the helper.
std::atomic<ULONGLONG> g_pauseOpenTick{0};

bool IsPaused() {
    if (altSnapDrag::g_globalInput) {
        return g_paused;
    }
    HANDLE event = g_openedPauseEvent.load();
    if (!event) {
        // No helper yet: look again every 2 s at most.
        ULONGLONG now = GetTickCount64();
        ULONGLONG last = g_pauseOpenTick;
        if (last && now - last < 2000) {
            return false;
        }
        g_pauseOpenTick = now;
        event = OpenEventW(SYNCHRONIZE, FALSE, kPauseEventName);
        if (!event) {
            return false;
        }
        HANDLE expected = nullptr;
        if (!g_openedPauseEvent.compare_exchange_strong(expected, event)) {
            CloseHandle(event);
            event = expected;
        }
    }
    return WaitForSingleObject(event, 0) == WAIT_OBJECT_0;
}

void CreatePauseEvent() {
    // Same access as the helper mutex: everyone may wait on it.
    SECURITY_ATTRIBUTES sa{sizeof(sa)};
    if (!ConvertStringSecurityDescriptorToSecurityDescriptorW(
            L"D:(A;;GA;;;SY)(A;;GA;;;BA)(A;;0x00100000;;;WD)S:(ML;;NW;;;LW)",
            SDDL_REVISION_1, &sa.lpSecurityDescriptor, nullptr)) {
        return;
    }
    g_pauseEvent = CreateEventW(&sa, TRUE, FALSE, kPauseEventName);
    LocalFree(sa.lpSecurityDescriptor);
    if (g_pauseEvent) {
        ResetEvent(g_pauseEvent);
    }
}

void ClosePauseEvent() {
    if (g_pauseEvent) {
        ResetEvent(g_pauseEvent);
        CloseHandle(g_pauseEvent);
        g_pauseEvent = nullptr;
    }
    if (HANDLE event = g_openedPauseEvent.exchange(nullptr)) {
        CloseHandle(event);
    }
}

//////// settings ////////

void LoadSettings() {
    Settings s;
    for (size_t i = 0; i < s.keys.size(); i++) {
        WindhawkUtils::StringSetting value =
            WindhawkUtils::StringSetting::make(L"%ls", kModeKeyNames[i]);
        altSnapDrag::ParseHotkey(value.get(), &s.keys[i].key, &s.keys[i].modifiers);
    }

    int step = Wh_GetIntSetting(L"resizeMode.step");
    g_resizeStepPct = std::clamp(step > 0 ? step : 2, 1, 20);
    int timeout = Wh_GetIntSetting(L"resizeMode.timeout");
    s.resizeTimeoutMs = std::clamp(timeout > 0 ? timeout : 10, 3, 60) * 1000;

    auto text = [](PCWSTR name) {
        std::wstring value = WindhawkUtils::StringSetting::make(L"%ls", name).get();
        for (auto& c : value) c = (WCHAR)towlower(c);
        return value;
    };
    std::wstring follow = text(L"focus.followCursor");
    s.follow = follow == L"hover"   ? FollowMode::Hover
               : follow == L"raise" ? FollowMode::Raise
                                    : FollowMode::Windows;
    int delay = Wh_GetIntSetting(L"focus.followDelay");
    s.followDelay = std::clamp(delay > 0 ? delay : 150, 10, 1000);
    std::wstring jump = text(L"focus.cursorJump");
    s.jump = jump == L"monitor"  ? JumpMode::Monitor
             : jump == L"window" ? JumpMode::Window
                                 : JumpMode::Never;
    int opacity = Wh_GetIntSetting(L"effects.inactiveOpacity");
    opacity = std::clamp(opacity > 0 ? opacity : 100, 50, 100);
    s.inactiveAlpha = (BYTE)((opacity * 255 + 50) / 100);
    s.popup = text(L"effects.statusPopup") != L"hide";

    s.tiling = Wh_GetIntSetting(L"tiling.enabled") != 0;
    s.tileExisting = Wh_GetIntSetting(L"tiling.existing") != 0;
    s.innerGap = std::clamp(Wh_GetIntSetting(L"tiling.innerGap"), 0, 100);
    g_animMs = std::clamp(Wh_GetIntSetting(L"effects.animation"), 0, 400);
    g_magnetPx = std::clamp(Wh_GetIntSetting(L"moveTrigger.magnet"), 0, 60);
    g_magnetGap = s.innerGap;
    int tileStep = Wh_GetIntSetting(L"tiling.resizeStep");
    s.tileStep = std::clamp(tileStep > 0 ? tileStep : 5, 1, 20);
    for (int i = 0; i < 200; i++) {
        std::wstring entry =
            WindhawkUtils::StringSetting::make(L"tiling.floatApps[%d]", i).get();
        for (auto& c : entry) c = (WCHAR)towlower(c);
        for (auto& name : snapCommander::SplitExecutableList(entry)) {
            if (std::find(s.floatApps.begin(), s.floatApps.end(), name) == s.floatApps.end()) {
                s.floatApps.push_back(name);
            }
        }
    }

    std::lock_guard<std::mutex> lock(g_swmSettingsMutex);
    g_swmSettings = s;
}

//////// shared helpers ////////

// Monitors in the order the number keys use: the main monitor's row from
// left to right, then the rest from the top down. A left, main, right and top
// screen come out as 1 left, 2 main, 3 right, 4 top.
std::vector<moveToMonitor::MonitorInfo> OrderedMonitors() {
    auto list = moveToMonitor::GetAllMonitors();
    MONITORINFO pmi{sizeof(pmi)};
    if (!GetMonitorInfoW(MonitorFromPoint({0, 0}, MONITOR_DEFAULTTOPRIMARY), &pmi)) return list;
    const RECT p = pmi.rcMonitor;
    auto inRow = [&](const moveToMonitor::MonitorInfo& m) {
        LONG c = (m.rcMonitor.top + m.rcMonitor.bottom) / 2;
        return c >= p.top && c < p.bottom;
    };
    std::stable_sort(list.begin(), list.end(),
                     [&](const moveToMonitor::MonitorInfo& a, const moveToMonitor::MonitorInfo& b) {
                         bool ra = inRow(a), rb = inRow(b);
                         if (ra != rb) return ra;
                         if (!ra && a.rcMonitor.top != b.rcMonitor.top) {
                             return a.rcMonitor.top < b.rcMonitor.top;
                         }
                         return a.rcMonitor.left < b.rcMonitor.left;
                     });
    return list;
}

bool IsCloaked(HWND hWnd) {
    DWORD cloaked = 0;
    return SUCCEEDED(DwmGetWindowAttribute(hWnd, DWMWA_CLOAKED, &cloaked,
                                           sizeof(cloaked))) &&
           cloaked;
}

bool GetFrame(HWND hWnd, RECT* rect) {
    if (SUCCEEDED(DwmGetWindowAttribute(hWnd, DWMWA_EXTENDED_FRAME_BOUNDS, rect,
                                        sizeof(*rect)))) {
        return true;
    }
    return GetWindowRect(hWnd, rect) != FALSE;
}

bool StartThread(LPTHREAD_START_ROUTINE proc, HANDLE* thread, DWORD* id) {
    HANDLE ready = CreateEventW(nullptr, TRUE, FALSE, nullptr);
    if (!ready) {
        return false;
    }
    *thread = CreateThread(nullptr, 0, proc, ready, 0, id);
    if (*thread) {
        // The thread's queue exists once it signals, so posts don't get lost.
        WaitForSingleObject(ready, 2000);
    }
    CloseHandle(ready);
    return *thread != nullptr;
}

void StopThread(HANDLE* thread, DWORD* id) {
    if (!*thread) {
        return;
    }
    PostThreadMessageW(*id, WM_QUIT, 0, 0);
    if (WaitForSingleObject(*thread, 2000) != WAIT_OBJECT_0) {
        Wh_Log(L"A worker thread did not stop in time");
    }
    CloseHandle(*thread);
    *thread = nullptr;
    *id = 0;
}

//////// status popup ////////

HANDLE g_osdThread;
DWORD g_osdThreadId;

void ShowOsd(OsdState state) {
    if (g_osdThreadId && GetSettings().popup) {
        PostThreadMessageW(g_osdThreadId, kOsdShowMessage, state, 0);
    }
}

void HideOsd() {
    if (g_osdThreadId) {
        PostThreadMessageW(g_osdThreadId, kOsdHideMessage, 0, 0);
    }
}

namespace osd {

HWND g_window;
ID2D1Factory* g_d2d;
IDWriteFactory* g_dwrite;
HDC g_memDC;
HBITMAP g_bitmap;
HGDIOBJ g_oldBitmap;
POINT g_pos;
SIZE g_size;
bool g_sticky;
int g_fadeStep;
constexpr UINT_PTR kHideTimer = 1;
constexpr UINT_PTR kFadeTimer = 2;
constexpr int kFadeSteps = 10;  // 150 ms in 15 ms steps.
constexpr BYTE kOpaque = 255;

void FreeBitmap() {
    if (g_memDC) {
        SelectObject(g_memDC, g_oldBitmap);
        DeleteDC(g_memDC);
        g_memDC = nullptr;
    }
    if (g_bitmap) {
        DeleteObject(g_bitmap);
        g_bitmap = nullptr;
    }
}

void Hide() {
    if (g_window) {
        KillTimer(g_window, kHideTimer);
        KillTimer(g_window, kFadeTimer);
        ShowWindow(g_window, SW_HIDE);
    }
    FreeBitmap();
}

void Present(BYTE alpha) {
    HDC screen = GetDC(nullptr);
    POINT source{};
    BLENDFUNCTION blend{AC_SRC_OVER, 0, alpha, AC_SRC_ALPHA};
    UpdateLayeredWindow(g_window, screen, &g_pos, &g_size, g_memDC, &source, 0,
                        &blend, ULW_ALPHA);
    ReleaseDC(nullptr, screen);
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    if (msg == WM_TIMER && wParam == kHideTimer) {
        KillTimer(hWnd, kHideTimer);
        g_fadeStep = 0;
        SetTimer(hWnd, kFadeTimer, 15, nullptr);
        return 0;
    }
    if (msg == WM_TIMER && wParam == kFadeTimer) {
        if (++g_fadeStep >= kFadeSteps || !g_memDC) {
            Hide();
        } else {
            Present((BYTE)(kOpaque * (kFadeSteps - g_fadeStep) / kFadeSteps));
        }
        return 0;
    }
    if (msg == WM_MOUSEACTIVATE) {
        return MA_NOACTIVATE;
    }
    return DefWindowProcW(hWnd, msg, wParam, lParam);
}

bool EnsureWindow() {
    if (g_window) {
        return true;
    }
    if (!g_d2d && FAILED(D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED,
                                           &g_d2d))) {
        return false;
    }
    if (!g_dwrite &&
        FAILED(DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED,
                                   __uuidof(IDWriteFactory),
                                   reinterpret_cast<IUnknown**>(&g_dwrite)))) {
        return false;
    }
    WNDCLASSEXW wc{sizeof(wc)};
    wc.lpfnWndProc = WndProc;
    wc.hInstance = GetModuleHandleW(nullptr);
    wc.lpszClassName = kOsdClassName;
    wc.hCursor = LoadCursorW(nullptr, IDC_ARROW);
    RegisterClassExW(&wc);
    g_window = CreateWindowExW(WS_EX_TOPMOST | WS_EX_TOOLWINDOW | WS_EX_NOACTIVATE |
                                   WS_EX_TRANSPARENT | WS_EX_LAYERED,
                               kOsdClassName, L"", WS_POPUP, 0, 0, 0, 0, nullptr,
                               nullptr, wc.hInstance, nullptr);
    return g_window != nullptr;
}

D2D1_COLOR_F Rgb(UINT32 rgb, float a = 1.0f) {
    return D2D1::ColorF(rgb, a);
}

void Show(OsdState state) {
    if (!EnsureWindow()) {
        return;
    }
    Hide();

    PCWSTR text = state == kOsdPaused   ? L"Window manager paused"
                  : state == kOsdResize ? L"Resize: arrows size, Shift+arrows move, Esc ends"
                                        : L"Window manager on";
    UINT32 dotColor = state == kOsdPaused   ? 0x6c7086
                      : state == kOsdResize ? 0xcba6f7
                                            : 0x89b4fa;

    // On the monitor of the active window, or else of the mouse.
    HWND fg = GetForegroundWindow();
    POINT cursor{};
    GetCursorPos(&cursor);
    HMONITOR monitor = fg ? MonitorFromWindow(fg, MONITOR_DEFAULTTONEAREST)
                          : MonitorFromPoint(cursor, MONITOR_DEFAULTTONEAREST);
    MONITORINFO mi{sizeof(mi)};
    GetMonitorInfoW(monitor, &mi);
    UINT dpiX = 96, dpiY = 96;
    if (FAILED(GetDpiForMonitor(monitor, MDT_EFFECTIVE_DPI, &dpiX, &dpiY)) || !dpiX) {
        dpiX = 96;
    }
    const float scale = dpiX / 96.0f;

    IDWriteTextFormat* format = nullptr;
    IDWriteTextLayout* layout = nullptr;
    if (FAILED(g_dwrite->CreateTextFormat(
            L"Segoe UI Variable Text", nullptr, DWRITE_FONT_WEIGHT_SEMI_BOLD,
            DWRITE_FONT_STYLE_NORMAL, DWRITE_FONT_STRETCH_NORMAL, 13.0f * scale,
            L"en-us", &format))) {
        return;
    }
    format->SetWordWrapping(DWRITE_WORD_WRAPPING_NO_WRAP);
    HRESULT hr = g_dwrite->CreateTextLayout(text, (UINT32)wcslen(text), format,
                                            4000.0f, 200.0f, &layout);
    format->Release();
    if (FAILED(hr)) {
        return;
    }
    DWRITE_TEXT_METRICS metrics{};
    layout->GetMetrics(&metrics);

    const float height = 36.0f * scale;
    const float pad = 16.0f * scale;
    const float dot = 6.0f * scale;
    const float gap = 10.0f * scale;
    const float width = pad + dot + gap + metrics.width + pad;
    g_size = {(LONG)std::ceil(width), (LONG)std::ceil(height)};
    const RECT& work = mi.rcWork;
    g_pos = {work.left + ((work.right - work.left) - g_size.cx) / 2,
             work.bottom - (LONG)(48.0f * scale) - g_size.cy};

    BITMAPINFO bi{};
    bi.bmiHeader.biSize = sizeof(bi.bmiHeader);
    bi.bmiHeader.biWidth = g_size.cx;
    bi.bmiHeader.biHeight = -g_size.cy;
    bi.bmiHeader.biPlanes = 1;
    bi.bmiHeader.biBitCount = 32;
    bi.bmiHeader.biCompression = BI_RGB;
    void* bits = nullptr;
    HDC screen = GetDC(nullptr);
    g_memDC = CreateCompatibleDC(screen);
    g_bitmap = CreateDIBSection(screen, &bi, DIB_RGB_COLORS, &bits, nullptr, 0);
    ReleaseDC(nullptr, screen);
    if (!g_memDC || !g_bitmap) {
        layout->Release();
        FreeBitmap();
        return;
    }
    g_oldBitmap = SelectObject(g_memDC, g_bitmap);

    D2D1_RENDER_TARGET_PROPERTIES props = D2D1::RenderTargetProperties(
        D2D1_RENDER_TARGET_TYPE_DEFAULT,
        D2D1::PixelFormat(DXGI_FORMAT_B8G8R8A8_UNORM, D2D1_ALPHA_MODE_PREMULTIPLIED),
        96.0f, 96.0f);
    ID2D1DCRenderTarget* target = nullptr;
    bool drawn = false;
    if (SUCCEEDED(g_d2d->CreateDCRenderTarget(&props, &target))) {
        RECT bounds{0, 0, g_size.cx, g_size.cy};
        if (SUCCEEDED(target->BindDC(g_memDC, &bounds))) {
            target->SetTextAntialiasMode(D2D1_TEXT_ANTIALIAS_MODE_GRAYSCALE);
            target->BeginDraw();
            target->Clear(D2D1::ColorF(0, 0.0f));
            ID2D1SolidColorBrush* brush = nullptr;
            if (SUCCEEDED(target->CreateSolidColorBrush(Rgb(0x1e1e2e, 0.92f), &brush))) {
                const float radius = height / 2.0f;
                target->FillRoundedRectangle(
                    D2D1::RoundedRect(D2D1::RectF(0, 0, (float)g_size.cx, height),
                                      radius, radius),
                    brush);
                brush->SetColor(Rgb(dotColor));
                target->FillEllipse(
                    D2D1::Ellipse(D2D1::Point2F(pad + dot / 2.0f, height / 2.0f),
                                  dot / 2.0f, dot / 2.0f),
                    brush);
                brush->SetColor(Rgb(0xcdd6f4));
                target->DrawTextLayout(
                    D2D1::Point2F(pad + dot + gap, (height - metrics.height) / 2.0f),
                    layout, brush);
                brush->Release();
            }
            drawn = SUCCEEDED(target->EndDraw());
        }
        target->Release();
    }
    layout->Release();
    if (!drawn) {
        FreeBitmap();
        return;
    }

    Present(kOpaque);
    SetWindowPos(g_window, HWND_TOPMOST, 0, 0, 0, 0,
                 SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE | SWP_SHOWWINDOW);
    g_sticky = state == kOsdResize;
    if (!g_sticky) {
        SetTimer(g_window, kHideTimer, 1200, nullptr);
    }
}

DWORD WINAPI ThreadProc(LPVOID ready) {
    SetThreadDpiAwarenessContext(DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2);
    MSG msg;
    PeekMessageW(&msg, nullptr, WM_USER, WM_USER, PM_NOREMOVE);
    SetEvent((HANDLE)ready);
    while (GetMessageW(&msg, nullptr, 0, 0) > 0) {
        if (!msg.hwnd && msg.message == kOsdShowMessage) {
            Show((OsdState)msg.wParam);
            continue;
        }
        if (!msg.hwnd && msg.message == kOsdHideMessage) {
            // Only the resize popup waits to be hidden; the others time out.
            if (g_sticky) {
                g_sticky = false;
                Hide();
            }
            continue;
        }
        DispatchMessageW(&msg);
    }
    Hide();
    if (g_window) {
        DestroyWindow(g_window);
        g_window = nullptr;
    }
    UnregisterClassW(kOsdClassName, GetModuleHandleW(nullptr));
    if (g_dwrite) {
        g_dwrite->Release();
        g_dwrite = nullptr;
    }
    if (g_d2d) {
        g_d2d->Release();
        g_d2d = nullptr;
    }
    return 0;
}

}  // namespace osd

//////// focus follows the mouse ////////

std::atomic<bool> g_stopping{false};

// Uses the Windows setting itself. The values it had are kept in the mod's
// storage, so they come back when this is turned off, paused or the mod stops,
// and after a crash on the next start.
void ApplyFocusTracking() {
    Settings s = GetSettings();
    bool want = s.follow != FollowMode::Windows && !IsPaused() && !g_stopping;
    bool saved = Wh_GetIntValue(L"ffcSaved", 0) != 0;
    if (want) {
        if (!saved) {
            BOOL track = FALSE, raise = FALSE;
            DWORD timeout = 0;
            SystemParametersInfoW(SPI_GETACTIVEWINDOWTRACKING, 0, &track, 0);
            SystemParametersInfoW(SPI_GETACTIVEWNDTRKZORDER, 0, &raise, 0);
            SystemParametersInfoW(SPI_GETACTIVEWNDTRKTIMEOUT, 0, &timeout, 0);
            Wh_SetIntValue(L"ffcTrack", track ? 1 : 0);
            Wh_SetIntValue(L"ffcZ", raise ? 1 : 0);
            Wh_SetIntValue(L"ffcTimeout", (int)timeout);
            Wh_SetIntValue(L"ffcSaved", 1);
        }
        SystemParametersInfoW(SPI_SETACTIVEWINDOWTRACKING, 0, (PVOID)(UINT_PTR)TRUE,
                              SPIF_SENDCHANGE);
        SystemParametersInfoW(SPI_SETACTIVEWNDTRKZORDER, 0,
                              (PVOID)(UINT_PTR)(s.follow == FollowMode::Raise),
                              SPIF_SENDCHANGE);
        SystemParametersInfoW(SPI_SETACTIVEWNDTRKTIMEOUT, 0,
                              (PVOID)(UINT_PTR)s.followDelay, SPIF_SENDCHANGE);
    } else if (saved) {
        SystemParametersInfoW(SPI_SETACTIVEWINDOWTRACKING, 0,
                              (PVOID)(UINT_PTR)(Wh_GetIntValue(L"ffcTrack", 0) != 0),
                              SPIF_SENDCHANGE);
        SystemParametersInfoW(SPI_SETACTIVEWNDTRKZORDER, 0,
                              (PVOID)(UINT_PTR)(Wh_GetIntValue(L"ffcZ", 0) != 0),
                              SPIF_SENDCHANGE);
        SystemParametersInfoW(SPI_SETACTIVEWNDTRKTIMEOUT, 0,
                              (PVOID)(UINT_PTR)(DWORD)Wh_GetIntValue(L"ffcTimeout", 0),
                              SPIF_SENDCHANGE);
        Wh_DeleteValue(L"ffcTrack");
        Wh_DeleteValue(L"ffcZ");
        Wh_DeleteValue(L"ffcTimeout");
        Wh_DeleteValue(L"ffcSaved");
    }
}

//////// effects: background window opacity, rule opacity, mouse jump ////////

HANDLE g_effectsThread;
DWORD g_effectsThreadId;

namespace effects {

struct Layer {
    bool added = false;    // We set WS_EX_LAYERED, so we take it off again.
    bool layered = false;  // We are driving its alpha.
    BYTE ruleAlpha = 255;
    BYTE applied = 255;
};
std::unordered_map<HWND, Layer> g_layers;

struct PendingLook {
    BYTE alpha = 255;
    bool onTop = false;
    int tries = 0;
};
std::unordered_map<HWND, PendingLook> g_pendingLooks;
UINT_PTR g_lookTimer = 0;
constexpr int kLookTries = 20;  // 100 ms apart

// Which check keeps a window from fading, for the log.
PCWSTR FadeBlocker(HWND hWnd) {
    if (!IsWindowVisible(hWnd)) return L"hidden";
    if (IsIconic(hWnd)) return L"minimized";
    if (GetAncestor(hWnd, GA_ROOT) != hWnd) return L"not top level";
    if (IsCloaked(hWnd)) return L"cloaked";
    if (!altSnapDrag::CanActOnRootWindow(hWnd)) return L"excluded";
    return L"none";
}
HWINEVENTHOOK g_foregroundHook;
HWINEVENTHOOK g_lifeHook;
HWND g_lastForeground;

bool IsFullscreen(HWND hWnd) {
    RECT r{};
    GetWindowRect(hWnd, &r);
    MONITORINFO mi{sizeof(mi)};
    GetMonitorInfoW(MonitorFromWindow(hWnd, MONITOR_DEFAULTTONEAREST), &mi);
    return r.left <= mi.rcMonitor.left && r.top <= mi.rcMonitor.top &&
           r.right >= mi.rcMonitor.right && r.bottom >= mi.rcMonitor.bottom;
}

bool CanFade(HWND hWnd, bool forRule) {
    if (!IsWindowVisible(hWnd) || IsIconic(hWnd) || GetAncestor(hWnd, GA_ROOT) != hWnd ||
        IsCloaked(hWnd) || !altSnapDrag::CanActOnRootWindow(hWnd)) {
        return false;
    }
    if (forRule) {
        return true;
    }
    LONG style = GetWindowLong(hWnd, GWL_STYLE);
    LONG ex = GetWindowLong(hWnd, GWL_EXSTYLE);
    return (style & WS_CAPTION) == WS_CAPTION &&
           !(ex & (WS_EX_TOOLWINDOW | WS_EX_NOACTIVATE)) && !IsFullscreen(hWnd);
}

void Restore(HWND hWnd, Layer& layer) {
    if (!layer.layered) {
        return;
    }
    SetLayeredWindowAttributes(hWnd, 0, 255, LWA_ALPHA);
    if (layer.added) {
        SetWindowLongPtrW(hWnd, GWL_EXSTYLE,
                          GetWindowLongPtrW(hWnd, GWL_EXSTYLE) & ~WS_EX_LAYERED);
        RedrawWindow(hWnd, nullptr, nullptr,
                     RDW_ERASE | RDW_INVALIDATE | RDW_FRAME | RDW_ALLCHILDREN);
    }
    layer.layered = false;
    layer.added = false;
    layer.applied = 255;
}

void Refresh(HWND hWnd, const Settings& s, HWND foreground) {
    auto it = g_layers.find(hWnd);
    BYTE ruleAlpha = it != g_layers.end() ? it->second.ruleAlpha : 255;
    BYTE target = 255;
    if (ruleAlpha < 255 && CanFade(hWnd, true)) {
        target = ruleAlpha;
    }
    if (s.inactiveAlpha < 255 && !IsPaused() && hWnd != foreground &&
        CanFade(hWnd, false)) {
        target = std::min(target, s.inactiveAlpha);
    }

    if (target == 255) {
        if (it != g_layers.end()) {
            Restore(hWnd, it->second);
            if (it->second.ruleAlpha == 255) {
                g_layers.erase(it);
            }
        }
        return;
    }
    if (it == g_layers.end()) {
        it = g_layers.emplace(hWnd, Layer{}).first;
    }
    Layer& layer = it->second;
    if (!layer.layered) {
        LONG_PTR ex = GetWindowLongPtrW(hWnd, GWL_EXSTYLE);
        if (ex & WS_EX_LAYERED) {
            return;  // Its app draws it layered; leave it alone.
        }
        SetWindowLongPtrW(hWnd, GWL_EXSTYLE, ex | WS_EX_LAYERED);
        layer.added = true;
        layer.layered = true;
        layer.applied = 0;
    }
    if (layer.applied != target) {
        SetLayeredWindowAttributes(hWnd, 0, target, LWA_ALPHA);
        layer.applied = target;
    }
}

BOOL CALLBACK CollectProc(HWND hWnd, LPARAM param) {
    if (IsWindowVisible(hWnd)) {
        reinterpret_cast<std::vector<HWND>*>(param)->push_back(hWnd);
    }
    return TRUE;
}

void RefreshAll() {
    Settings s = GetSettings();
    HWND foreground = GetAncestor(GetForegroundWindow(), GA_ROOT);
    std::vector<HWND> windows;
    for (const auto& entry : g_layers) {
        windows.push_back(entry.first);
    }
    if (s.inactiveAlpha < 255 && !IsPaused()) {
        EnumWindows(CollectProc, reinterpret_cast<LPARAM>(&windows));
    }
    for (HWND hWnd : windows) {
        if (!IsWindow(hWnd)) {
            g_layers.erase(hWnd);
        } else {
            Refresh(hWnd, s, foreground);
        }
    }
}

void RestoreAll() {
    for (auto& entry : g_layers) {
        if (IsWindow(entry.first)) {
            Restore(entry.first, entry.second);
        }
    }
    g_layers.clear();
}

void MaybeJumpCursor(HWND hWnd, const Settings& s) {
    if (s.jump == JumpMode::Never || IsPaused() || altSnapDrag::g_llRootWnd) {
        return;
    }
    // Only for keyboard switches: no button down and none just used.
    for (int button : {VK_LBUTTON, VK_RBUTTON, VK_MBUTTON, VK_XBUTTON1, VK_XBUTTON2}) {
        if (GetAsyncKeyState(button) < 0) {
            return;
        }
    }
    if (GetTickCount64() - g_lastMouseButtonTick < 400) {
        return;
    }
    if (!IsWindowVisible(hWnd) || IsIconic(hWnd) || IsCloaked(hWnd) ||
        !altSnapDrag::CanActOnRootWindow(hWnd)) {
        return;
    }
    RECT frame{};
    POINT pt{};
    if (!GetFrame(hWnd, &frame) || !GetCursorPos(&pt) || PtInRect(&frame, pt)) {
        return;
    }
    if (s.jump == JumpMode::Monitor &&
        MonitorFromPoint(pt, MONITOR_DEFAULTTONEAREST) ==
            MonitorFromWindow(hWnd, MONITOR_DEFAULTTONEAREST)) {
        return;
    }
    SetCursorPos((frame.left + frame.right) / 2, (frame.top + frame.bottom) / 2);
}

void CALLBACK EventProc(HWINEVENTHOOK, DWORD event, HWND hWnd, LONG idObject,
                        LONG idChild, DWORD, DWORD) {
    if (idObject != OBJID_WINDOW || idChild != CHILDID_SELF || !hWnd) {
        return;
    }
    if (event == EVENT_OBJECT_DESTROY) {
        g_layers.erase(hWnd);
        return;
    }
    if (GetAncestor(hWnd, GA_ROOT) != hWnd) {
        return;
    }
    Settings s = GetSettings();
    if (event == EVENT_SYSTEM_FOREGROUND) {
        HWND previous = g_lastForeground;
        g_lastForeground = hWnd;
        if (previous && previous != hWnd && IsWindow(previous)) {
            Refresh(previous, s, hWnd);
        }
        Refresh(hWnd, s, hWnd);
        MaybeJumpCursor(hWnd, s);
        return;
    }
    Refresh(hWnd, s, GetAncestor(GetForegroundWindow(), GA_ROOT));
}

// Each hook only while something needs it: they fire for every window.
void UpdateHooks() {
    Settings s = GetSettings();
    bool paused = IsPaused();
    bool fade = s.inactiveAlpha < 255 && !paused;
    bool wantForeground = !paused && (fade || s.jump != JumpMode::Never);
    bool wantLife = fade || !g_layers.empty();
    if (wantForeground && !g_foregroundHook) {
        g_foregroundHook = SetWinEventHook(
            EVENT_SYSTEM_FOREGROUND, EVENT_SYSTEM_FOREGROUND, nullptr, EventProc, 0, 0,
            WINEVENT_OUTOFCONTEXT | WINEVENT_SKIPOWNPROCESS);
    } else if (!wantForeground && g_foregroundHook) {
        UnhookWinEvent(g_foregroundHook);
        g_foregroundHook = nullptr;
    }
    if (wantLife && !g_lifeHook) {
        g_lifeHook = SetWinEventHook(EVENT_OBJECT_DESTROY, EVENT_OBJECT_SHOW, nullptr,
                                     EventProc, 0, 0,
                                     WINEVENT_OUTOFCONTEXT | WINEVENT_SKIPOWNPROCESS);
    } else if (!wantLife && g_lifeHook) {
        UnhookWinEvent(g_lifeHook);
        g_lifeHook = nullptr;
    }
    g_lastForeground = GetAncestor(GetForegroundWindow(), GA_ROOT);
}

// A new window can still be hidden or cloaked when its rule fires, so the
// pin and the fade wait for it, up to two seconds.
void TryPendingLooks() {
    HWND foreground = GetAncestor(GetForegroundWindow(), GA_ROOT);
    bool changed = false;
    for (auto it = g_pendingLooks.begin(); it != g_pendingLooks.end();) {
        HWND hWnd = it->first;
        PendingLook& look = it->second;
        if (!IsWindow(hWnd)) {
            it = g_pendingLooks.erase(it);
            continue;
        }
        bool ready = CanFade(hWnd, true);
        if (ready && look.alpha < 255) {
            g_layers[hWnd].ruleAlpha = look.alpha;
            Refresh(hWnd, GetSettings(), foreground);
            look.alpha = 255;
            changed = true;
        }
        if (ready && look.onTop) {
            if (GetWindowLongPtrW(hWnd, GWL_EXSTYLE) & WS_EX_TOPMOST) {
                look.onTop = false;
            } else {
                // Even tries ask the app's own copy of the mod; odd tries pin
                // from here, for apps the mod isn't loaded in.
                if (look.tries % 2 == 0) {
                    PostMessageW(hWnd, altSnapDrag::g_pinRequestMessage, 0, 0);
                } else if (!IsHungAppWindow(hWnd)) {
                    SetWindowPos(hWnd, HWND_TOPMOST, 0, 0, 0, 0,
                                 SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE |
                                     SWP_ASYNCWINDOWPOS);
                }
            }
        }
        if (look.alpha == 255 && !look.onTop) {
            it = g_pendingLooks.erase(it);
            continue;
        }
        if (++look.tries > kLookTries) {
            Wh_Log(L"Rule look for %p gave up: blocked by %s, still on top %d, opacity %d",
                   hWnd, FadeBlocker(hWnd), look.onTop ? 1 : 0, look.alpha);
            it = g_pendingLooks.erase(it);
            continue;
        }
        ++it;
    }
    if (changed) {
        UpdateHooks();
    }
    if (g_pendingLooks.empty()) {
        if (g_lookTimer) {
            KillTimer(nullptr, g_lookTimer);
            g_lookTimer = 0;
        }
    } else if (!g_lookTimer) {
        g_lookTimer = SetTimer(nullptr, 0, 100, nullptr);
    }
}

DWORD WINAPI ThreadProc(LPVOID ready) {
    SetThreadDpiAwarenessContext(DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2);
    MSG msg;
    PeekMessageW(&msg, nullptr, WM_USER, WM_USER, PM_NOREMOVE);
    SetEvent((HANDLE)ready);
    UpdateHooks();
    RefreshAll();
    while (GetMessageW(&msg, nullptr, 0, 0) > 0) {
        if (!msg.hwnd && msg.message == kRuleAlphaMessage) {
            HWND hWnd = (HWND)msg.wParam;
            if (IsWindow(hWnd)) {
                PendingLook look;
                look.alpha = (BYTE)(msg.lParam & 0xFF);
                look.onTop = (msg.lParam & 0x100) != 0;
                g_pendingLooks[hWnd] = look;
                TryPendingLooks();
            }
            continue;
        }
        if (!msg.hwnd && msg.message == WM_TIMER && g_lookTimer &&
            msg.wParam == g_lookTimer) {
            TryPendingLooks();
            continue;
        }
        if (!msg.hwnd && msg.message == kEffectsReloadMessage) {
            // The rules apply their opacity again after a settings change.
            for (auto& entry : g_layers) {
                entry.second.ruleAlpha = 255;
            }
            RefreshAll();
            UpdateHooks();
            continue;
        }
        if (!msg.hwnd && msg.message == kPauseChangedMessage) {
            UpdateHooks();
            RefreshAll();
            continue;
        }
        DispatchMessageW(&msg);
    }
    if (g_foregroundHook) UnhookWinEvent(g_foregroundHook);
    if (g_lifeHook) UnhookWinEvent(g_lifeHook);
    g_foregroundHook = g_lifeHook = nullptr;
    if (g_lookTimer) KillTimer(nullptr, g_lookTimer);
    g_lookTimer = 0;
    g_pendingLooks.clear();
    RestoreAll();
    return 0;
}

}  // namespace effects

void ApplyRuleLook(HWND hWnd, BYTE alpha, bool onTop) {
    if (g_effectsThreadId) {
        PostThreadMessageW(g_effectsThreadId, kRuleAlphaMessage, (WPARAM)hWnd,
                           alpha | (onTop ? 0x100 : 0));
    }
}

//////// tiling ////////

constexpr UINT kTilingCommandMessage = WM_APP + 320;
constexpr UINT kTilingReloadMessage = WM_APP + 321;
constexpr UINT kTilingEventMessage = WM_APP + 322;
enum TilingCommand : WPARAM {
    kTileMove, kTileGrow, kTileToggle, kTileFlip, kTileRegion, kTileFill, kTileBorderless,
    kTileSendMonitor, kTileCycleFocus, kTileRestoreMinimized
};

HANDLE g_tilingThread;
DWORD g_tilingThreadId;

// The tiled windows and their tiles, copied out for focus by direction on the
// input thread. A maximized window counts as its tile.
std::mutex g_tiledMutex;
std::vector<std::pair<HWND, RECT>> g_tiledWindows;

void PostTilingCommand(TilingCommand command, int direction) {
    if (g_tilingThreadId) {
        PostThreadMessageW(g_tilingThreadId, kTilingCommandMessage, command, direction);
    }
}

bool IsTiledWindow(HWND hWnd) {
    std::lock_guard<std::mutex> lock(g_tiledMutex);
    for (const auto& entry : g_tiledWindows) {
        if (entry.first == hWnd) return true;
    }
    return false;
}

// 0-3 halves (left, right, top, bottom), 4-7 quarters, 8 fill.
void PostTileRegion(int region) {
    PostTilingCommand(kTileRegion, region);
}

namespace tiling {

// DIAG: temporary trace kept in the mod's storage (read with reg query).
std::wstring g_diag;
void TLog(const wchar_t* fmt, ...) {
    wchar_t line[300];
    va_list args;
    va_start(args, fmt);
    _vsnwprintf_s(line, _TRUNCATE, fmt, args);
    va_end(args);
    Wh_Log(L"%s", line);
    wchar_t stamp[24];
    swprintf_s(stamp, L"%llu ", GetTickCount64() % 1000000);
    g_diag += stamp;
    g_diag += line;
    g_diag += L" | ";
    if (g_diag.size() > 6000) g_diag.erase(0, g_diag.size() - 4000);
    Wh_SetStringValue(L"diag", g_diag.c_str());
}

enum Direction { kLeft, kRight, kUp, kDown };

// A window (hWnd set) or a split that lays its children side by side, or
// stacked when vertical. Leaf nodes are never freed while their window stays
// tiled, so pointers to them survive any change to the tree around them.
struct Node {
    HWND hWnd = nullptr;
    bool vertical = false;
    double weight = 1.0;  // Share of the parent; siblings add up to 1.
    Node* parent = nullptr;
    std::vector<std::unique_ptr<Node>> children;
    RECT target{};     // Where the layout wants it.
    RECT placedFor{};  // The target it was last placed for.
    RECT placed{};     // The frame read back after placing.
    ULONGLONG placedTick = 0;
    int fights = 0;
    RECT slot{};           // The whole tile, before the insets.
    int inset[4]{};        // Edges pulled in by the grow keys, per Direction.
    bool fill = false;     // Fills the screen inside the gaps (Alt+F).
    bool hidden = false;   // Maximized: out of the layout until restored.
};

// One tree per monitor and virtual desktop. Kept until the thread stops, so
// a pointer to one stays good.
struct Workspace {
    HMONITOR monitor = nullptr;
    GUID desktop{};
    std::unique_ptr<Node> root;
    HWND lastFocused = nullptr;
};

struct Leaf {
    Node* node;
    Workspace* ws;
};

struct Event {
    DWORD event;
    HWND hWnd;
};

constexpr GUID kDesktopManagerClsid = {
    0xaa509086, 0x5ca9, 0x4c25, {0x8f, 0x95, 0x58, 0x9d, 0x3c, 0x07, 0xb4, 0x8a}};
constexpr GUID kDesktopManagerIid = {
    0xa5cd92ff, 0x29be, 0x454c, {0x8d, 0x04, 0xd8, 0x28, 0x79, 0xfb, 0x3c, 0x1b}};

std::vector<std::unique_ptr<Workspace>> g_workspaces;
std::unordered_map<HWND, Leaf> g_leaves;
std::unordered_set<HWND> g_floated;           // Floated with the key; left alone after.
std::unordered_map<HWND, int> g_pending;      // Shown windows settling, with ticks waited.
std::unordered_map<HWND, int> g_cloakCheck;   // Tiled windows that were just cloaked.
// Borderless fullscreen windows and what to give back when it ends.
struct Borderless {
    LONG_PTR style;
    LONG_PTR ex;
    RECT rect;
    RECT frame;  // Visible bounds before, for the glide back.
    bool zoomed;
    bool tiled;
};
std::unordered_map<HWND, Borderless> g_borderless;
std::unordered_map<HWND, RECT> g_fillRestore;  // Floating windows filled with Alt+F.

std::vector<Event> g_events;
IVirtualDesktopManager* g_desktops;
GUID g_currentDesktop{};
std::array<HWINEVENTHOOK, 4> g_hooks{};
UINT_PTR g_pendingTimer;
UINT_PTR g_enforceTimer;
bool g_active;
Settings g_config;

int Width(const RECT& r) { return r.right - r.left; }
int Height(const RECT& r) { return r.bottom - r.top; }
bool SameRect(const RECT& a, const RECT& b) { return EqualRect(&a, &b) != FALSE; }
POINT Center(const RECT& r) { return {(r.left + r.right) / 2, (r.top + r.bottom) / 2}; }

void Axis(int dir, long long dx, long long dy, long long* primary, long long* orth) {
    switch (dir) {
        case kLeft: *primary = -dx; *orth = dy; break;
        case kRight: *primary = dx; *orth = dy; break;
        case kUp: *primary = -dy; *orth = dx; break;
        default: *primary = dy; *orth = dx; break;
    }
}

size_t IndexOf(Node* node) {
    auto& list = node->parent->children;
    for (size_t i = 0; i < list.size(); i++) {
        if (list[i].get() == node) return i;
    }
    return 0;
}

void Normalize(Node* split) {
    double sum = 0;
    for (auto& child : split->children) sum += child->weight;
    for (auto& child : split->children) {
        child->weight = sum > 0 ? child->weight / sum : 1.0 / split->children.size();
    }
}

void SwapLooks(Node* a, Node* b) {
    std::swap(a->fill, b->fill);
    std::swap(a->inset, b->inset);
}

void CollectLeaves(Node* node, std::vector<Node*>* out) {
    if (node->hWnd) {
        out->push_back(node);
        return;
    }
    for (auto& child : node->children) CollectLeaves(child.get(), out);
}

void PublishTiled() {
    std::vector<std::pair<HWND, RECT>> list;
    list.reserve(g_leaves.size());
    for (auto& entry : g_leaves) {
        const Node* node = entry.second.node;
        list.push_back({entry.first, node->hidden ? RECT{} : node->target});
    }
    std::lock_guard<std::mutex> lock(g_tiledMutex);
    g_tiledWindows = std::move(list);
}

GUID DesktopOf(HWND hWnd) {
    GUID id{};
    if (g_desktops && SUCCEEDED(g_desktops->GetWindowDesktopId(hWnd, &id)) &&
        id != GUID{}) {
        return id;
    }
    return g_currentDesktop;
}

bool OnCurrentDesktop(HWND hWnd) {
    BOOL on = TRUE;
    if (!g_desktops || FAILED(g_desktops->IsWindowOnCurrentVirtualDesktop(hWnd, &on))) {
        return true;
    }
    return on != FALSE;
}

Workspace* GetWorkspace(HMONITOR monitor, const GUID& desktop) {
    for (auto& ws : g_workspaces) {
        if (ws->monitor == monitor && ws->desktop == desktop) return ws.get();
    }
    auto ws = std::make_unique<Workspace>();
    ws->monitor = monitor;
    ws->desktop = desktop;
    ws->root = std::make_unique<Node>();
    MONITORINFO mi{sizeof(mi)};
    if (GetMonitorInfoW(monitor, &mi)) {
        // A portrait monitor stacks windows; a wide one puts them side by side.
        ws->root->vertical = Height(mi.rcWork) > Width(mi.rcWork);
    }
    g_workspaces.push_back(std::move(ws));
    return g_workspaces.back().get();
}

int InnerGap(HMONITOR monitor) {
    int gap = g_config.innerGap;
    if (snapCommander::g_gapScaleDpi) {
        UINT dpiX = 96, dpiY = 96;
        if (SUCCEEDED(GetDpiForMonitor(monitor, MDT_EFFECTIVE_DPI, &dpiX, &dpiY)) && dpiX) {
            gap = MulDiv(gap, dpiX, 96);
        }
    }
    return gap;
}

//////// the tree ////////

Node* InsertLeaf(Workspace* ws, Node* split, size_t index, HWND hWnd) {
    auto leaf = std::make_unique<Node>();
    leaf->hWnd = hWnd;
    leaf->parent = split;
    size_t count = split->children.size();
    double share = 1.0 / (count + 1);
    for (auto& child : split->children) child->weight *= 1.0 - share;
    leaf->weight = share;
    Node* raw = leaf.get();
    split->children.insert(split->children.begin() + std::min(index, count), std::move(leaf));
    g_leaves[hWnd] = {raw, ws};
    return raw;
}

// Puts a split's children in its place in the parent (same direction).
void FlattenChild(Node* split, size_t index) {
    std::unique_ptr<Node> child = std::move(split->children[index]);
    split->children.erase(split->children.begin() + index);
    for (size_t i = 0; i < child->children.size(); i++) {
        auto& grand = child->children[i];
        grand->weight *= child->weight;
        grand->parent = split;
        split->children.insert(split->children.begin() + index + i, std::move(grand));
    }
}

// Tidies the tree after a split lost a child: a split left with one child is
// replaced by it, and an empty one goes away. The root stays a split.
void Collapse(Workspace* ws, Node* split) {
    while (split) {
        Node* parent = split->parent;
        if (!parent) {
            if (split->children.size() == 1 && !split->children[0]->hWnd) {
                std::unique_ptr<Node> child = std::move(split->children[0]);
                child->parent = nullptr;
                child->weight = 1.0;
                ws->root = std::move(child);
            }
            return;
        }
        size_t index = IndexOf(split);
        if (split->children.empty()) {
            parent->children.erase(parent->children.begin() + index);
            Normalize(parent);
        } else if (split->children.size() == 1) {
            std::unique_ptr<Node> child = std::move(split->children[0]);
            child->weight = split->weight;
            child->parent = parent;
            Node* raw = child.get();
            parent->children[index] = std::move(child);
            if (!raw->hWnd && raw->vertical == parent->vertical) {
                FlattenChild(parent, index);
            }
        } else {
            return;
        }
        split = parent;
    }
}

void RemoveNode(Workspace* ws, Node* node) {
    Node* parent = node->parent;
    parent->children.erase(parent->children.begin() + IndexOf(node));
    Normalize(parent);
    Collapse(ws, parent);
}

Workspace* RemoveWindow(HWND hWnd) {
    auto it = g_leaves.find(hWnd);
    if (it == g_leaves.end()) return nullptr;
    Leaf leaf = it->second;
    g_leaves.erase(it);
    if (leaf.ws->lastFocused == hWnd) leaf.ws->lastFocused = nullptr;
    RemoveNode(leaf.ws, leaf.node);
    return leaf.ws;
}

// Moves a tiled window to a new spot. The new leaf goes in before the old one
// comes out, so the split it goes into can't be tidied away first.
void Relocate(HWND hWnd, Workspace* dest, Node* split, size_t index) {
    Leaf old = g_leaves[hWnd];
    InsertLeaf(dest, split, index, hWnd);
    if (old.ws != dest && old.ws->lastFocused == hWnd) old.ws->lastFocused = nullptr;
    RemoveNode(old.ws, old.node);
    dest->lastFocused = hWnd;
}

//////// layout ////////

// A maximized window steps out of the layout, like GlazeWM, so the windows
// beside it close up; it gets its tile back when it is restored.
bool Hidden(const Node* node) {
    if (node->children.empty()) return node->hWnd && !node->fill && IsZoomed(node->hWnd);
    for (const auto& child : node->children) {
        if (!Hidden(child.get())) return false;
    }
    return true;
}

void ComputeNode(Node* node, const RECT& rect, int gap) {
    node->target = rect;
    size_t count = node->children.size();
    if (!count) {
        node->slot = rect;
        node->hidden = Hidden(node);
        if (!node->hWnd) return;
        // Edges the grow keys pulled in, keeping at least 150 px.
        int* in = node->inset;
        int spareX = std::max(0, Width(rect) - 150), spareY = std::max(0, Height(rect) - 150);
        in[kLeft] = std::min(in[kLeft], spareX);
        in[kRight] = std::min(in[kRight], spareX - in[kLeft]);
        in[kUp] = std::min(in[kUp], spareY);
        in[kDown] = std::min(in[kDown], spareY - in[kUp]);
        node->target = {rect.left + in[kLeft], rect.top + in[kUp], rect.right - in[kRight],
                        rect.bottom - in[kDown]};
        return;
    }
    std::vector<Node*> shown;
    double total = 0;
    for (auto& child : node->children) {
        if (Hidden(child.get())) {
            ComputeNode(child.get(), rect, gap);
        } else {
            shown.push_back(child.get());
            total += child->weight;
        }
    }
    count = shown.size();
    if (!count) return;
    if (total <= 0.001) total = 1.0;
    int start = node->vertical ? rect.top : rect.left;
    int length = (node->vertical ? Height(rect) : Width(rect)) - gap * (int)(count - 1);
    length = std::max(length, (int)count);
    double before = 0;
    for (size_t i = 0; i < count; i++) {
        double after = before + shown[i]->weight / total;
        int a = start + (int)std::lround(before * length) + gap * (int)i;
        int b = i + 1 == count ? start + length + gap * (int)i
                               : start + (int)std::lround(after * length) + gap * (int)i;
        RECT r = rect;
        if (node->vertical) {
            r.top = a;
            r.bottom = b;
        } else {
            r.left = a;
            r.right = b;
        }
        ComputeNode(shown[i], r, gap);
        before = after;
    }
}

bool ComputeLayout(Workspace* ws) {
    MONITORINFO mi{sizeof(mi)};
    if (!GetMonitorInfoW(ws->monitor, &mi)) return false;
    RECT area = snapCommander::GappedWorkArea(ws->monitor, mi.rcWork);
    ComputeNode(ws->root.get(), area, InnerGap(ws->monitor));
    std::vector<Node*> leaves;
    CollectLeaves(ws->root.get(), &leaves);
    for (Node* leaf : leaves) {
        if (leaf->fill) leaf->target = area;
    }
    return true;
}

bool CanPlace(HWND hWnd) {
    return IsWindow(hWnd) && !IsIconic(hWnd) && !IsZoomed(hWnd) && !IsHungAppWindow(hWnd) &&
           !effects::IsFullscreen(hWnd);
}

void PlaceLeaf(Node* leaf) {
    leaf->placedFor = leaf->target;
    HWND hWnd = leaf->hWnd;
    if (!CanPlace(hWnd)) {
        leaf->placed = {};
        return;
    }
    const RECT& t = leaf->target;
    RECT frame{};
    GetFrame(hWnd, &frame);
    for (int pass = 0; pass < 2 && !SameRect(frame, t); pass++) {
        // A second pass fixes the border size after crossing to a monitor
        // with another scale.
        snapCommander::ApplyVisibleRect(hWnd, t.left, t.top, Width(t), Height(t));
        GetFrame(hWnd, &frame);
        leaf->placedTick = GetTickCount64();
    }
    leaf->placed = frame;
}

// The tiles glide to their new places together, then land exactly.
void PlaceLeaves(const std::vector<Node*>& leaves) {
    std::vector<std::pair<HWND, RECT>> moves;
    for (Node* leaf : leaves) {
        if (CanPlace(leaf->hWnd)) moves.push_back({leaf->hWnd, leaf->target});
    }
    snapCommander::AnimateRects(moves);
    for (Node* leaf : leaves) PlaceLeaf(leaf);
}

void Layout(std::initializer_list<Workspace*> list) {
    std::vector<Node*> leaves;
    for (Workspace* ws : list) {
        if (ws && ComputeLayout(ws)) CollectLeaves(ws->root.get(), &leaves);
    }
    PlaceLeaves(leaves);
}

void Layout(Workspace* ws) {
    Layout({ws});
}

void LayoutAll() {
    for (auto& ws : g_workspaces) Layout(ws.get());
}

//////// which windows tile ////////

bool CanTile(HWND hWnd, bool forced) {
    if (!hWnd || !IsWindow(hWnd) || GetAncestor(hWnd, GA_ROOT) != hWnd ||
        !IsWindowVisible(hWnd) || IsIconic(hWnd)) {
        return false;
    }
    DWORD pid = 0;
    GetWindowThreadProcessId(hWnd, &pid);
    if (pid == GetCurrentProcessId()) return false;
    LONG_PTR style = GetWindowLongPtrW(hWnd, GWL_STYLE);
    LONG_PTR ex = GetWindowLongPtrW(hWnd, GWL_EXSTYLE);
    if ((style & WS_CHILD) || (ex & (WS_EX_TOOLWINDOW | WS_EX_NOACTIVATE))) return false;
    static constexpr PCWSTR kNeverTile[] = {
        L"#32770",
        L"Windows.UI.Core.CoreWindow",
        L"XamlExplorerHostIslandWindow",
        L"MultitaskingViewFrame",
        L"ForegroundStaging",
        L"TopLevelWindowForOverflowXamlIsland",
        L"NotifyIconOverflowWindow",
        L"OperationStatusWindow",
    };
    WCHAR cls[96] = {};
    GetClassNameW(hWnd, cls, ARRAYSIZE(cls));
    for (PCWSTR name : kNeverTile) {
        if (wcscmp(cls, name) == 0) return false;
    }
    if (!altSnapDrag::CanActOnRootWindow(hWnd)) return false;
    if (forced) return true;
    // Ordinary app windows only: resizable, with a title bar or maximize box,
    // not pinned on top, not a dialog and not owned by another window.
    if (!(style & WS_THICKFRAME)) return false;
    if ((style & WS_CAPTION) != WS_CAPTION && !(style & WS_MAXIMIZEBOX)) return false;
    if ((ex & (WS_EX_TOPMOST | WS_EX_DLGMODALFRAME)) || GetWindow(hWnd, GW_OWNER)) return false;
    if (!IsZoomed(hWnd)) {
        RECT frame{};
        if (effects::IsFullscreen(hWnd) || !GetFrame(hWnd, &frame) || Width(frame) < 200 ||
            Height(frame) < 150) {
            return false;
        }
    }
    if (!g_config.floatApps.empty()) {
        std::wstring exe = snapCommander::GetWindowProcessExeName(hWnd);
        if (std::find(g_config.floatApps.begin(), g_config.floatApps.end(), exe) !=
            g_config.floatApps.end()) {
            return false;
        }
    }
    return !snapCommander::HasPlacementRule(hWnd);
}

// Quick check at event time; CanTile decides once the window settles.
bool LooksTileable(HWND hWnd) {
    if (GetAncestor(hWnd, GA_ROOT) != hWnd) return false;
    LONG_PTR style = GetWindowLongPtrW(hWnd, GWL_STYLE);
    LONG_PTR ex = GetWindowLongPtrW(hWnd, GWL_EXSTYLE);
    return !(style & WS_CHILD) && !(ex & WS_EX_TOOLWINDOW) &&
           (style & (WS_THICKFRAME | WS_CAPTION));
}

Workspace* AddWindow(HWND hWnd) {
    if (g_leaves.count(hWnd)) return g_leaves[hWnd].ws;
    HMONITOR monitor = MonitorFromWindow(hWnd, MONITOR_DEFAULTTONEAREST);
    Workspace* ws = GetWorkspace(monitor, DesktopOf(hWnd));
    // Like GlazeWM: a new window goes right after the one that had focus.
    auto anchor = ws->lastFocused ? g_leaves.find(ws->lastFocused) : g_leaves.end();
    if (anchor != g_leaves.end() && anchor->second.ws == ws) {
        Node* node = anchor->second.node;
        InsertLeaf(ws, node->parent, IndexOf(node) + 1, hWnd);
    } else {
        InsertLeaf(ws, ws->root.get(), ws->root->children.size(), hWnd);
    }
    // The next window opens beside this one if it has focus now.
    if (GetAncestor(GetForegroundWindow(), GA_ROOT) == hWnd) ws->lastFocused = hWnd;
    TLog(L"Tiling: added %p", hWnd);
    return ws;
}

BOOL CALLBACK CollectTileableProc(HWND hWnd, LPARAM param) {
    if (!g_leaves.count(hWnd) && !g_floated.count(hWnd) && !g_borderless.count(hWnd) &&
        !IsCloaked(hWnd) && CanTile(hWnd, false)) {
        reinterpret_cast<std::vector<HWND>*>(param)->push_back(hWnd);
    }
    return TRUE;
}

// Tiles the windows already open, left to right as they sit now.
void Reconcile() {
    std::vector<HWND> found;
    EnumWindows(CollectTileableProc, reinterpret_cast<LPARAM>(&found));
    std::vector<std::pair<RECT, HWND>> items;
    for (HWND hWnd : found) {
        RECT frame{};
        GetFrame(hWnd, &frame);
        items.push_back({frame, hWnd});
    }
    std::stable_sort(items.begin(), items.end(), [](const auto& a, const auto& b) {
        return a.first.left != b.first.left ? a.first.left < b.first.left
                                            : a.first.top < b.first.top;
    });
    for (auto& item : items) {
        HMONITOR monitor = MonitorFromWindow(item.second, MONITOR_DEFAULTTONEAREST);
        Workspace* ws = GetWorkspace(monitor, DesktopOf(item.second));
        InsertLeaf(ws, ws->root.get(), ws->root->children.size(), item.second);
    }
    if (!items.empty()) TLog(L"Tiling: %d open windows tiled", (int)items.size());
    LayoutAll();
    PublishTiled();
}

void ClearAll() {
    g_leaves.clear();
    g_workspaces.clear();
    g_pending.clear();
    g_cloakCheck.clear();
    PublishTiled();
}

//////// keys ////////

struct MonitorSearch {
    RECT from;
    int dir;
    HMONITOR best;
    long long score;
};

// A monitor counts only when it starts past that edge of this one and the two
// overlap along the edge, so the screen beside isn't picked for Down.
BOOL CALLBACK MonitorSearchProc(HMONITOR monitor, HDC, LPRECT rect, LPARAM param) {
    auto* s = reinterpret_cast<MonitorSearch*>(param);
    const RECT& f = s->from;
    const RECT& r = *rect;
    constexpr int kSlack = 16;
    bool beyond, overlap;
    switch (s->dir) {
        case kLeft:
            beyond = r.right <= f.left + kSlack;
            overlap = r.top < f.bottom && r.bottom > f.top;
            break;
        case kRight:
            beyond = r.left >= f.right - kSlack;
            overlap = r.top < f.bottom && r.bottom > f.top;
            break;
        case kUp:
            beyond = r.bottom <= f.top + kSlack;
            overlap = r.left < f.right && r.right > f.left;
            break;
        default:
            beyond = r.top >= f.bottom - kSlack;
            overlap = r.left < f.right && r.right > f.left;
            break;
    }
    if (!beyond || !overlap || EqualRect(&r, &f)) return TRUE;
    POINT a = Center(f), b = Center(r);
    long long d = (long long)(b.x - a.x) * (b.x - a.x) + (long long)(b.y - a.y) * (b.y - a.y);
    if (!s->best || d < s->score) {
        s->best = monitor;
        s->score = d;
    }
    return TRUE;
}

HMONITOR MonitorInDirection(HMONITOR from, int dir) {
    MonitorSearch search{};
    MONITORINFO mi{sizeof(mi)};
    if (!GetMonitorInfoW(from, &mi)) return nullptr;
    search.from = mi.rcMonitor;
    search.dir = dir;
    EnumDisplayMonitors(nullptr, nullptr, MonitorSearchProc, reinterpret_cast<LPARAM>(&search));
    return search.best;
}

void JumpCursor(HWND hWnd) {
    RECT frame{};
    if (GetAsyncKeyState(VK_LBUTTON) < 0 || GetAsyncKeyState(VK_RBUTTON) < 0 ||
        !GetFrame(hWnd, &frame)) {
        return;
    }
    POINT c = Center(frame);
    SetCursorPos(c.x, c.y);
}

HWND ActiveRoot() {
    HWND hWnd = GetAncestor(GetForegroundWindow(), GA_ROOT);
    return hWnd && altSnapDrag::CanActOnRootWindow(hWnd) ? hWnd : nullptr;
}

// A maximized window is restored first, so it can take its new tile.
void Unzoom(HWND hWnd) {
    if (!IsZoomed(hWnd)) return;
    // A hung app would block this thread, so it only gets the async call.
    if (IsHungAppWindow(hWnd)) {
        ShowWindowAsync(hWnd, SW_RESTORE);
    } else {
        ShowWindow(hWnd, SW_RESTORE);
    }
}

size_t LeafCount(Workspace* ws) {
    std::vector<Node*> leaves;
    CollectLeaves(ws->root.get(), &leaves);
    return leaves.size();
}

// True when some split above the window already lines windows up that way.
bool Lined(Node* leaf, bool vertical) {
    for (Node* split = leaf->parent; split; split = split->parent) {
        if (split->vertical == vertical && split->children.size() > 1) return true;
    }
    return false;
}

// Puts the whole tree inside a new root going that way.
void WrapRoot(Workspace* ws, bool vertical) {
    auto root = std::make_unique<Node>();
    root->vertical = vertical;
    ws->root->parent = root.get();
    ws->root->weight = 1.0;
    root->children.push_back(std::move(ws->root));
    ws->root = std::move(root);
}

void MoveCommand(int dir) {
    HWND hWnd = ActiveRoot();
    if (!hWnd) return;
    auto it = g_leaves.find(hWnd);
    if (it != g_leaves.end()) {
        Unzoom(hWnd);
        it->second.node->fill = false;
    }
    if (it == g_leaves.end()) {
        // A floating window snaps to that half instead.
        static constexpr snapCommander::Action kHalves[] = {
            snapCommander::Action::LeftHalf, snapCommander::Action::RightHalf,
            snapCommander::Action::TopHalf, snapCommander::Action::BottomHalf};
        snapCommander::EnqueueWork(hWnd, kHalves[dir]);
        return;
    }
    Workspace* ws = it->second.ws;
    Node* leaf = it->second.node;
    bool vertical = dir == kUp || dir == kDown;
    bool forward = dir == kRight || dir == kDown;

    // The nearest split going that way with something on that side.
    Node* child = leaf;
    Node* split = leaf->parent;
    while (split) {
        if (split->vertical == vertical) {
            size_t i = IndexOf(child);
            if (forward ? i + 1 < split->children.size() : i > 0) break;
        }
        child = split;
        split = split->parent;
    }

    Workspace* other = nullptr;
    if (split) {
        size_t i = IndexOf(child);
        Node* sibling = split->children[forward ? i + 1 : i - 1].get();
        if (child == leaf && sibling->hWnd) {
            // Trade places with the neighbour.
            HWND neighbour = sibling->hWnd;
            sibling->hWnd = hWnd;
            leaf->hWnd = neighbour;
            sibling->fights = leaf->fights = 0;
            SwapLooks(sibling, leaf);
            g_leaves[hWnd] = {sibling, ws};
            g_leaves[neighbour] = {leaf, ws};
        } else if (child == leaf) {
            // Join the stack next door, beside the part level with this window.
            POINT c = Center(leaf->target);
            long mine = sibling->vertical ? c.y : c.x;
            size_t index = sibling->children.size();
            for (size_t k = 0; k < sibling->children.size(); k++) {
                POINT m = Center(sibling->children[k]->target);
                if (mine < (sibling->vertical ? m.y : m.x)) {
                    index = k;
                    break;
                }
            }
            Relocate(hWnd, ws, sibling, index);
        } else {
            Relocate(hWnd, ws, split, forward ? i + 1 : i);
        }
    } else if (!Lined(leaf, vertical) && LeafCount(ws) >= 2) {
        // Like GlazeWM: stacked windows go side by side first (or the other
        // way round), and only then on to the next monitor.
        WrapRoot(ws, vertical);
        Relocate(hWnd, ws, ws->root.get(), forward ? 1 : 0);
    } else if (HMONITOR next = MonitorInDirection(ws->monitor, dir)) {
        // Off the edge: on to the next monitor, at its near side.
        other = GetWorkspace(next, ws->desktop);
        Node* root = other->root.get();
        Relocate(hWnd, other, root,
                 root->vertical == vertical && forward ? 0 : root->children.size());
    } else if (ws->root->vertical == vertical) {
        if (leaf->parent == ws->root.get()) return;
        Relocate(hWnd, ws, ws->root.get(), forward ? ws->root->children.size() : 0);
    } else {
        if (LeafCount(ws) < 2) {
            Layout(ws);
            return;
        }
        // Wrap everything in a new split going that way, this window on that side.
        WrapRoot(ws, vertical);
        Relocate(hWnd, ws, ws->root.get(), forward ? 1 : 0);
    }
    Layout(ws);
    if (other && other != ws) Layout(other);
    PublishTiled();
    JumpCursor(hWnd);
}

// Moves the edge of a tiled window on that side by px (negative shrinks).
bool AdjustEdge(Workspace* ws, Node* leaf, int dir, int px) {
    bool vertical = dir == kUp || dir == kDown;
    bool forward = dir == kRight || dir == kDown;
    for (Node* node = leaf; node->parent; node = node->parent) {
        Node* split = node->parent;
        if (split->vertical != vertical) continue;
        size_t i = IndexOf(node);
        if (forward ? i + 1 >= split->children.size() : i == 0) continue;
        Node* sibling = split->children[forward ? i + 1 : i - 1].get();
        double avail = (vertical ? Height(split->target) : Width(split->target)) -
                       (double)InnerGap(ws->monitor) * (split->children.size() - 1);
        if (avail < 1) return true;
        double minShare = std::min(0.45, 150.0 / avail);
        double low = minShare - node->weight;
        double high = sibling->weight - minShare;
        if (low <= high) {
            double delta = std::max(low, std::min(high, px / avail));
            node->weight += delta;
            sibling->weight -= delta;
        }
        return true;
    }
    return false;
}

void GrowCommand(int dir) {
    HWND hWnd = ActiveRoot();
    if (!hWnd || IsIconic(hWnd) || g_borderless.count(hWnd)) return;
    Unzoom(hWnd);
    HMONITOR monitor = MonitorFromWindow(hWnd, MONITOR_DEFAULTTONEAREST);
    MONITORINFO mi{sizeof(mi)};
    if (!GetMonitorInfoW(monitor, &mi)) return;
    RECT work = snapCommander::GappedWorkArea(monitor, mi.rcWork);
    bool vertical = dir == kUp || dir == kDown;
    int px = std::max(1, (vertical ? Height(work) : Width(work)) * g_config.tileStep / 100);

    auto it = g_leaves.find(hWnd);
    if (it != g_leaves.end()) {
        // Push that edge out; at the screen edge, pull the far edge in instead.
        static constexpr int kOpposite[] = {kRight, kLeft, kDown, kUp};
        Workspace* ws = it->second.ws;
        Node* node = it->second.node;
        node->fill = false;
        if (node->inset[dir] > 0) {
            // That edge was pulled in earlier: push it back out first.
            node->inset[dir] = std::max(0, node->inset[dir] - px);
        } else if (!AdjustEdge(ws, node, dir, px) &&
                   !AdjustEdge(ws, node, kOpposite[dir], -px)) {
            // Nothing beside it that way (one row, or alone on the screen):
            // the far edge comes in, like a floating window at the screen edge.
            int size = vertical ? Height(node->slot) : Width(node->slot);
            int room = std::max(0, size - 150 - node->inset[dir]);
            node->inset[kOpposite[dir]] = std::min(room, node->inset[kOpposite[dir]] + px);
        }
        Layout(ws);
        PublishTiled();
        return;
    }
    if (!altSnapDrag::CanSizeRootWindow(hWnd)) return;
    RECT f{};
    GetFrame(hWnd, &f);
    constexpr int kMin = 150;
    switch (dir) {
        case kLeft:
            if (f.left > work.left) f.left = std::max(work.left, f.left - px);
            else f.right = std::max(f.left + kMin, f.right - px);
            break;
        case kRight:
            if (f.right < work.right) f.right = std::min(work.right, f.right + px);
            else f.left = std::min(f.right - kMin, f.left + px);
            break;
        case kUp:
            if (f.top > work.top) f.top = std::max(work.top, f.top - px);
            else f.bottom = std::max(f.top + kMin, f.bottom - px);
            break;
        default:
            if (f.bottom < work.bottom) f.bottom = std::min(work.bottom, f.bottom + px);
            else f.top = std::min(f.bottom - kMin, f.top + px);
            break;
    }
    snapCommander::ApplyVisibleRect(hWnd, f.left, f.top, Width(f), Height(f));
}

void ToggleCommand() {
    HWND hWnd = ActiveRoot();
    if (!hWnd || g_borderless.count(hWnd)) return;
    if (Workspace* ws = RemoveWindow(hWnd)) {
        g_floated.insert(hWnd);
        Layout(ws);
        PublishTiled();
        MONITORINFO mi{sizeof(mi)};
        if (!IsZoomed(hWnd) && GetMonitorInfoW(ws->monitor, &mi)) {
            RECT work = snapCommander::GappedWorkArea(ws->monitor, mi.rcWork);
            int w = Width(work) * 60 / 100;
            int h = Height(work) * 70 / 100;
            snapCommander::AnimateVisibleRect(hWnd, work.left + (Width(work) - w) / 2,
                                              work.top + (Height(work) - h) / 2, w, h);
        }
        TLog(L"Tiling: %p floats", hWnd);
        return;
    }
    if (!g_active) return;
    if (!CanTile(hWnd, true)) {
        TLog(L"Tiling: %p can't be tiled", hWnd);
        return;
    }
    g_floated.erase(hWnd);
    g_pending.erase(hWnd);
    g_fillRestore.erase(hWnd);
    Unzoom(hWnd);
    Layout(AddWindow(hWnd));
    PublishTiled();
    JumpCursor(hWnd);
}

// Makes the root split go that way. A root going the other way with more than
// one child ends up inside a new root.
void EnsureRoot(Workspace* ws, bool vertical) {
    if (ws->root->vertical == vertical) return;
    if (ws->root->children.size() <= 1) {
        ws->root->vertical = vertical;
        return;
    }
    WrapRoot(ws, vertical);
}

// Puts a split going that way around a node, in the node's place.
Node* WrapInSplit(Node* node, bool vertical) {
    Node* parent = node->parent;
    size_t index = IndexOf(node);
    auto split = std::make_unique<Node>();
    split->vertical = vertical;
    split->parent = parent;
    split->weight = node->weight;
    std::unique_ptr<Node> owned = std::move(parent->children[index]);
    owned->parent = split.get();
    owned->weight = 1.0;
    split->children.push_back(std::move(owned));
    Node* raw = split.get();
    parent->children[index] = std::move(split);
    return raw;
}

// Gives a node that share of its split; the others keep their proportions.
void SetShare(Node* node, double share) {
    Node* split = node->parent;
    if (!split || split->children.size() < 2) return;
    double rest = 1.0 - node->weight;
    double others = (double)(split->children.size() - 1);
    for (auto& child : split->children) {
        if (child.get() == node) continue;
        child->weight = rest > 0.001 ? child->weight / rest * (1.0 - share) : (1.0 - share) / others;
    }
    node->weight = share;
}

// Takes the window to the edge of the root split as its own column or row.
Node* ToRootEdge(HWND hWnd, Workspace* ws, bool forward) {
    Node* root = ws->root.get();
    Node* leaf = g_leaves[hWnd].node;
    size_t edge = forward ? root->children.size() - 1 : 0;
    if (leaf->parent != root || IndexOf(leaf) != edge) {
        Relocate(hWnd, ws, root, forward ? root->children.size() : 0);
    }
    return g_leaves[hWnd].node;
}

void FillCommand();

// Alt+Q/W/E/R and Alt+U/I/J/K on a tiled window: the tiles rearrange so the
// window takes that half or quarter, with the others beside it.
void RegionCommand(int region) {
    if (region == 8) {
        FillCommand();
        return;
    }
    HWND hWnd = ActiveRoot();
    auto it = hWnd ? g_leaves.find(hWnd) : g_leaves.end();
    if (it == g_leaves.end()) return;
    Workspace* ws = it->second.ws;
    Unzoom(hWnd);
    it->second.node->fill = false;
    size_t count = LeafCount(ws);
    bool quarter = region >= 4 && count >= 3;
    if (region >= 4 && !quarter) region = (region == 4 || region == 6) ? kLeft : kRight;
    if (count >= 2 && !quarter) {
        bool vertical = region == kUp || region == kDown;
        bool forward = region == kRight || region == kDown;
        EnsureRoot(ws, vertical);
        SetShare(ToRootEdge(hWnd, ws, forward), 0.5);
    } else if (quarter) {
        bool right = region == 5 || region == 7;
        bool bottom = region >= 6;
        EnsureRoot(ws, false);
        Node* own = ToRootEdge(hWnd, ws, right);
        Node* root = ws->root.get();
        size_t n = root->children.size();
        Node* column = nullptr;
        if (n >= 3) {
            // Share the next column over, which then sits at the edge.
            Node* next = root->children[right ? n - 2 : 1].get();
            if (next->hWnd || !next->vertical) next = WrapInSplit(next, true);
            Relocate(hWnd, ws, next, bottom ? next->children.size() : 0);
            column = next;
        } else if (n == 2) {
            // Two columns: borrow the window nearest that corner from the other.
            ComputeLayout(ws);
            std::vector<Node*> others;
            CollectLeaves(root->children[right ? 0 : 1].get(), &others);
            Node* partner = nullptr;
            long long best = 0;
            RECT area = root->target;
            POINT corner{right ? area.right : area.left, bottom ? area.top : area.bottom};
            for (Node* other : others) {
                POINT c = Center(other->target);
                long long d = (long long)(c.x - corner.x) * (c.x - corner.x) +
                              (long long)(c.y - corner.y) * (c.y - corner.y);
                if (!partner || d < best) {
                    partner = other;
                    best = d;
                }
            }
            if (partner && others.size() >= 2) {
                column = WrapInSplit(own, true);
                Relocate(partner->hWnd, ws, column, bottom ? 0 : 1);
            }
        }
        if (column) {
            SetShare(column, 0.5);
            SetShare(g_leaves[hWnd].node, 0.5);
        } else {
            SetShare(g_leaves[hWnd].node, 0.5);
        }
    }
    Layout(ws);
    PublishTiled();
    JumpCursor(hWnd);
}

// Alt+F: fill the screen inside the gaps, like GlazeWM's fullscreen. A tiled
// window keeps its tile and goes back to it on the next press.
void FillCommand() {
    HWND hWnd = ActiveRoot();
    if (!hWnd || IsIconic(hWnd) || g_borderless.count(hWnd)) return;
    auto it = g_leaves.find(hWnd);
    if (it != g_leaves.end()) {
        Node* leaf = it->second.node;
        bool want = !leaf->fill || IsZoomed(hWnd);
        Unzoom(hWnd);
        leaf->fill = want;
        Layout(it->second.ws);
        PublishTiled();
        if (want) {
            SetWindowPos(hWnd, HWND_TOP, 0, 0, 0, 0,
                         SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE | SWP_ASYNCWINDOWPOS);
        }
        return;
    }
    if (!altSnapDrag::CanSizeRootWindow(hWnd)) return;
    HMONITOR monitor = MonitorFromWindow(hWnd, MONITOR_DEFAULTTONEAREST);
    MONITORINFO mi{sizeof(mi)};
    if (!GetMonitorInfoW(monitor, &mi)) return;
    RECT area = snapCommander::GappedWorkArea(monitor, mi.rcWork);
    RECT frame{};
    auto saved = g_fillRestore.find(hWnd);
    if (!IsZoomed(hWnd) && saved != g_fillRestore.end() && GetFrame(hWnd, &frame) &&
        SameRect(frame, area)) {
        RECT r = saved->second;
        g_fillRestore.erase(saved);
        snapCommander::AnimateVisibleRect(hWnd, r.left, r.top, Width(r), Height(r));
        return;
    }
    Unzoom(hWnd);
    if (!GetFrame(hWnd, &frame)) return;
    g_fillRestore[hWnd] = frame;
    snapCommander::AnimateVisibleRect(hWnd, area.left, area.top, Width(area), Height(area));
}

// With glide on, the frame comes back where the window is and it shrinks to
// its old spot; a window going back to a tile is left to the tiling glide.
void RestoreBorders(HWND hWnd, const Borderless& b, bool glide = false, bool retile = false) {
    if (!IsWindow(hWnd)) return;
    SetWindowLongPtrW(hWnd, GWL_STYLE, b.style);
    SetWindowLongPtrW(hWnd, GWL_EXSTYLE, b.ex);
    if (glide) {
        SetWindowPos(hWnd, nullptr, 0, 0, 0, 0,
                     SWP_FRAMECHANGED | SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER |
                         SWP_NOOWNERZORDER | SWP_NOACTIVATE);
        if (retile) return;
        if (!b.zoomed && !IsRectEmpty(&b.frame)) snapCommander::AnimateRects({{hWnd, b.frame}});
    }
    SetWindowPos(hWnd, nullptr, b.rect.left, b.rect.top, Width(b.rect), Height(b.rect),
                 SWP_FRAMECHANGED | SWP_NOZORDER | SWP_NOOWNERZORDER | SWP_NOACTIVATE);
    if (b.zoomed) ShowWindow(hWnd, SW_MAXIMIZE);
}

// Ctrl+Shift+F: no title bar or borders, stretched over the whole monitor,
// taskbar included (ShareX's "make active window borderless"). Press again to
// give the window its frame, size and tile back.
void BorderlessCommand() {
    HWND hWnd = ActiveRoot();
    if (!hWnd) return;
    auto saved = g_borderless.find(hWnd);
    if (saved != g_borderless.end()) {
        Borderless b = saved->second;
        g_borderless.erase(saved);
        bool retile = b.tiled && g_active && CanTile(hWnd, true);
        RestoreBorders(hWnd, b, true, retile);
        if (retile) {
            g_floated.erase(hWnd);
            Layout(AddWindow(hWnd));
            PublishTiled();
        }
        return;
    }
    if (!altSnapDrag::CanActOnRootWindow(hWnd)) return;
    if (IsIconic(hWnd)) ShowWindow(hWnd, SW_RESTORE);
    Borderless b{};
    b.zoomed = IsZoomed(hWnd) != FALSE;
    Unzoom(hWnd);
    b.style = GetWindowLongPtrW(hWnd, GWL_STYLE);
    b.ex = GetWindowLongPtrW(hWnd, GWL_EXSTYLE);
    if (!GetWindowRect(hWnd, &b.rect)) return;
    if (!GetFrame(hWnd, &b.frame)) b.frame = b.rect;
    g_fillRestore.erase(hWnd);
    if (Workspace* ws = RemoveWindow(hWnd)) {
        b.tiled = true;
        Layout(ws);
        PublishTiled();
    }
    g_borderless[hWnd] = b;
    MONITORINFO mi{sizeof(mi)};
    GetMonitorInfoW(MonitorFromWindow(hWnd, MONITOR_DEFAULTTONEAREST), &mi);
    const RECT& m = mi.rcMonitor;
    SetWindowLongPtrW(hWnd, GWL_STYLE,
                      b.style & ~(WS_CAPTION | WS_THICKFRAME | WS_SYSMENU | WS_MINIMIZEBOX |
                                  WS_MAXIMIZEBOX));
    SetWindowLongPtrW(hWnd, GWL_EXSTYLE,
                      b.ex & ~(WS_EX_DLGMODALFRAME | WS_EX_CLIENTEDGE | WS_EX_STATICEDGE |
                               WS_EX_WINDOWEDGE));
    // The frame goes first, over the spot the window had, then it grows out
    // to cover the monitor.
    SetWindowPos(hWnd, HWND_TOP, b.frame.left, b.frame.top, Width(b.frame), Height(b.frame),
                 SWP_FRAMECHANGED | SWP_NOOWNERZORDER | SWP_NOACTIVATE);
    snapCommander::AnimateRects({{hWnd, m}});
    SetWindowPos(hWnd, HWND_TOP, m.left, m.top, Width(m), Height(m),
                 SWP_FRAMECHANGED | SWP_NOOWNERZORDER | SWP_NOACTIVATE);
    TLog(L"Tiling: %p borderless", hWnd);
}

// Alt+Shift+number: like GlazeWM's move to workspace, one per monitor.
void SendMonitorCommand(int index) {
    HWND hWnd = ActiveRoot();
    if (!hWnd || g_borderless.count(hWnd)) return;
    auto monitors = OrderedMonitors();
    if (index >= (int)monitors.size()) return;
    const auto& dst = monitors[index];
    HMONITOR here = MonitorFromWindow(hWnd, MONITOR_DEFAULTTONEAREST);
    if (here == dst.hMon) return;
    auto it = g_leaves.find(hWnd);
    if (it != g_leaves.end() && !IsZoomed(hWnd)) {
        Workspace* ws = it->second.ws;
        Workspace* dest = GetWorkspace(dst.hMon, ws->desktop);
        Relocate(hWnd, dest, dest->root.get(), dest->root->children.size());
        Layout({ws, dest});
        PublishTiled();
        JumpCursor(hWnd);
        return;
    }
    // Floating or maximized: the move keeps its state; the enforcer re-homes
    // a maximized tile.
    for (const auto& src : monitors) {
        if (src.hMon == here) {
            moveToMonitor::MoveWindowToMonitor(hWnd, src, dst);
            JumpCursor(hWnd);
            return;
        }
    }
}

void FlipCommand() {
    HWND hWnd = ActiveRoot();
    auto it = hWnd ? g_leaves.find(hWnd) : g_leaves.end();
    if (it == g_leaves.end()) return;
    Workspace* ws = it->second.ws;
    Node* split = it->second.node->parent;
    split->vertical = !split->vertical;
    for (size_t i = 0; i < split->children.size();) {
        Node* child = split->children[i].get();
        if (!child->hWnd && child->vertical == split->vertical) {
            size_t count = child->children.size();
            FlattenChild(split, i);
            i += count;
        } else {
            i++;
        }
    }
    if (split->parent && split->parent->vertical == split->vertical) {
        FlattenChild(split->parent, IndexOf(split));
    }
    Layout(ws);
}

// Alt+PageDown / Alt+PageUp: walk the windows stacked behind the active one.
struct CycleFocusEnumData {
    RECT current;
    std::vector<HWND>* out;
};

LONG RectArea(const RECT& r) {
    return std::max(0L, r.right - r.left) * std::max(0L, r.bottom - r.top);
}

BOOL CALLBACK CycleFocusProc(HWND hWnd, LPARAM param) {
    auto* d = reinterpret_cast<CycleFocusEnumData*>(param);
    if (!IsWindowVisible(hWnd) || IsIconic(hWnd) || IsCloaked(hWnd) ||
        (GetWindowLongPtrW(hWnd, GWL_EXSTYLE) & (WS_EX_TOOLWINDOW | WS_EX_NOACTIVATE)) ||
        !altSnapDrag::CanActOnRootWindow(hWnd)) {
        return TRUE;
    }
    RECT frame{};
    if (!GetFrame(hWnd, &frame) || frame.right - frame.left < 2 ||
        frame.bottom - frame.top < 2) {
        return TRUE;
    }
    // Only windows stacked behind this one: at least half of the smaller of the
    // two must overlap, so tiles beside it are left to the focus keys.
    RECT overlap{};
    IntersectRect(&overlap, &frame, &d->current);
    if (RectArea(overlap) * 2 < std::min(RectArea(frame), RectArea(d->current))) {
        return TRUE;
    }
    d->out->push_back(hWnd);
    return TRUE;
}

void CycleFocusCommand(int direction) {
    HWND hCur = ActiveRoot();
    if (!hCur) return;
    CycleFocusEnumData data{};
    if (!GetFrame(hCur, &data.current)) return;
    std::vector<HWND> stack;
    data.out = &stack;
    EnumWindows(CycleFocusProc, reinterpret_cast<LPARAM>(&data));
    // EnumWindows walks top to bottom. The active window goes first.
    stack.erase(std::remove(stack.begin(), stack.end(), hCur), stack.end());
    if (stack.empty()) return;
    if (direction >= 0) {
        // Behind: bring up the next window and send this one to the back, so
        // pressing again walks the whole stack instead of swapping two.
        FocusWindow(stack.front());
        SetWindowPos(hCur, HWND_BOTTOM, 0, 0, 0, 0,
                     SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE | SWP_NOOWNERZORDER);
    } else {
        // Back: the window at the very back comes up, undoing one step.
        FocusWindow(stack.back());
    }
}

// Windows minimized while the mod runs, newest last. Kept on the tiling thread,
// which sees every minimize, whichever app's key or button did it.
void RememberMinimized(HWND hWnd) {
    g_minimizedWindows.erase(
        std::remove(g_minimizedWindows.begin(), g_minimizedWindows.end(), hWnd),
        g_minimizedWindows.end());
    g_minimizedWindows.push_back(hWnd);
    if (g_minimizedWindows.size() > 64) {
        g_minimizedWindows.erase(g_minimizedWindows.begin());
    }
}

// Alt+Shift+M: bring back the most recently minimized window. Windows restores
// it to the size and place it had before.
void RestoreMinimizedCommand() {
    while (!g_minimizedWindows.empty()) {
        HWND hMin = g_minimizedWindows.back();
        g_minimizedWindows.pop_back();
        if (IsWindow(hMin) && IsIconic(hMin)) {
            FocusWindow(hMin);
            return;
        }
    }
}

void RunCommand(TilingCommand command, int arg) {
    if (arg < -1 || arg > 8) return;
    TLog(L"Tiling: command %d arg %d", (int)command, arg);
    switch (command) {
        case kTileMove: if (arg <= 3) MoveCommand(arg); break;
        case kTileGrow:
            // Held down it repeats, so it doesn't wait for a glide.
            g_animOff++;
            if (arg <= 3) GrowCommand(arg);
            g_animOff--;
            break;
        case kTileToggle: ToggleCommand(); break;
        case kTileFlip: FlipCommand(); break;
        case kTileRegion: RegionCommand(arg); break;
        case kTileFill: FillCommand(); break;
        case kTileBorderless: BorderlessCommand(); break;
        case kTileSendMonitor: SendMonitorCommand(arg); break;
        case kTileCycleFocus: CycleFocusCommand(arg); break;
        case kTileRestoreMinimized: RestoreMinimizedCommand(); break;
    }
}

//////// window events ////////

void QueuePending(HWND hWnd) {
    if (g_active && !g_leaves.count(hWnd) && !g_floated.count(hWnd) && !g_pending.count(hWnd) &&
        !g_borderless.count(hWnd)) {
        g_pending[hWnd] = 0;
    }
}

// A tiled window moved to another virtual desktop goes to that desktop's tree.
void CheckDesktop(HWND hWnd) {
    auto it = g_leaves.find(hWnd);
    GUID id{};
    if (it == g_leaves.end() || !g_desktops ||
        FAILED(g_desktops->GetWindowDesktopId(hWnd, &id)) || id == GUID{} ||
        id == it->second.ws->desktop) {
        return;
    }
    Workspace* from = it->second.ws;
    Workspace* dest = GetWorkspace(from->monitor, id);
    Relocate(hWnd, dest, dest->root.get(), dest->root->children.size());
    Layout(from);
    Layout(dest);
    PublishTiled();
}

void HandleEvent(const Event& e) {
    HWND hWnd = e.hWnd;
    if (e.event == EVENT_SYSTEM_MINIMIZESTART) RememberMinimized(hWnd);
    switch (e.event) {
        case EVENT_OBJECT_DESTROY:
            g_floated.erase(hWnd);
            g_pending.erase(hWnd);
            g_cloakCheck.erase(hWnd);
            g_borderless.erase(hWnd);
            g_fillRestore.erase(hWnd);
            [[fallthrough]];
        case EVENT_OBJECT_HIDE:
        case EVENT_SYSTEM_MINIMIZESTART:
            if (Workspace* ws = RemoveWindow(hWnd)) {
                TLog(L"Tiling: %p left the tiles (event 0x%x)", hWnd, e.event);
                Layout(ws);
                PublishTiled();
            }
            break;
        case EVENT_OBJECT_SHOW:
        case EVENT_SYSTEM_MINIMIZEEND:
            if (LooksTileable(hWnd)) QueuePending(hWnd);
            break;
        case EVENT_OBJECT_UNCLOAKED:
            g_cloakCheck.erase(hWnd);
            if (g_leaves.count(hWnd)) {
                CheckDesktop(hWnd);
            } else if (LooksTileable(hWnd)) {
                QueuePending(hWnd);
            }
            break;
        case EVENT_OBJECT_CLOAKED:
            if (g_leaves.count(hWnd)) g_cloakCheck[hWnd] = 0;
            break;
        case EVENT_SYSTEM_FOREGROUND: {
            GUID id{};
            if (g_desktops && !IsCloaked(hWnd) &&
                SUCCEEDED(g_desktops->GetWindowDesktopId(hWnd, &id)) && id != GUID{}) {
                g_currentDesktop = id;
            }
            auto it = g_leaves.find(hWnd);
            if (it != g_leaves.end()) {
                it->second.ws->lastFocused = hWnd;
                CheckDesktop(hWnd);
            } else if (LooksTileable(hWnd)) {
                QueuePending(hWnd);
            }
            break;
        }
    }
}

// Events can arrive while a SetWindowPos call is waiting on another app, in
// the middle of a layout, so they queue and run from the message loop.
void CALLBACK EventProc(HWINEVENTHOOK, DWORD event, HWND hWnd, LONG idObject, LONG idChild,
                        DWORD, DWORD) {
    if (!hWnd || idObject != OBJID_WINDOW || idChild != CHILDID_SELF || !g_active) return;
    if (g_events.empty()) {
        PostThreadMessageW(GetCurrentThreadId(), kTilingEventMessage, 0, 0);
    }
    g_events.push_back({event, hWnd});
}

void DrainEvents() {
    std::vector<Event> events;
    events.swap(g_events);
    for (const Event& e : events) {
        if (g_active) HandleEvent(e);
    }
}

void OnPendingTimer() {
    std::vector<Workspace*> touched;
    for (auto it = g_pending.begin(); it != g_pending.end();) {
        HWND hWnd = it->first;
        int ticks = ++it->second;
        if (ticks < 3) {
            ++it;
            continue;
        }
        if (!IsWindow(hWnd) || g_leaves.count(hWnd) || g_floated.count(hWnd)) {
            it = g_pending.erase(it);
            continue;
        }
        bool cloaked = IsCloaked(hWnd);
        if (!cloaked && CanTile(hWnd, false)) {
            touched.push_back(AddWindow(hWnd));
            it = g_pending.erase(it);
        } else if ((cloaked || !IsWindowVisible(hWnd)) && ticks < 30) {
            ++it;
        } else {
            it = g_pending.erase(it);
        }
    }
    std::vector<HWND> checks;
    for (auto it = g_cloakCheck.begin(); it != g_cloakCheck.end();) {
        if (++it->second < 5) {
            ++it;
        } else {
            checks.push_back(it->first);
            it = g_cloakCheck.erase(it);
        }
    }
    for (HWND hWnd : checks) {
        if (!g_leaves.count(hWnd) || !IsCloaked(hWnd)) continue;
        CheckDesktop(hWnd);
        auto it = g_leaves.find(hWnd);
        // Hidden in place rather than parked on another desktop: untile it.
        if (it != g_leaves.end() && it->second.ws->desktop == DesktopOf(hWnd) &&
            OnCurrentDesktop(hWnd)) {
            TLog(L"Tiling: %p hidden in place", hWnd);
            touched.push_back(RemoveWindow(hWnd));
        }
    }
    std::sort(touched.begin(), touched.end());
    touched.erase(std::unique(touched.begin(), touched.end()), touched.end());
    for (Workspace* ws : touched) Layout(ws);
    if (!touched.empty()) PublishTiled();
}

Node* LeafAt(Workspace* ws, POINT pt, HWND skip) {
    if (!ComputeLayout(ws)) return nullptr;
    std::vector<Node*> leaves;
    CollectLeaves(ws->root.get(), &leaves);
    for (Node* leaf : leaves) {
        if (leaf->hWnd != skip && PtInRect(&leaf->target, pt)) return leaf;
    }
    return nullptr;
}

// A tiled window ended up somewhere else. Returns true when the tree changed.
bool OnWindowMoved(Workspace* ws, Node* leaf, const RECT& frame, bool byMouse) {
    HWND hWnd = leaf->hWnd;
    const RECT old = leaf->placed;
    HMONITOR monitor = MonitorFromRect(&frame, MONITOR_DEFAULTTONEAREST);
    if (!byMouse) {
        if (monitor != ws->monitor) {
            // Sent to another monitor with a key: tile it there.
            Workspace* dest = GetWorkspace(monitor, ws->desktop);
            Relocate(hWnd, dest, dest->root.get(), dest->root->children.size());
            Layout(ws);
            Layout(dest);
            PublishTiled();
            return true;
        }
        if (++leaf->fights > 3) {
            leaf->placed = frame;  // The app insists on its own size; let it be.
            return false;
        }
        PlaceLeaf(leaf);
        return false;
    }
    bool left = frame.left != old.left, right = frame.right != old.right;
    bool top = frame.top != old.top, bottom = frame.bottom != old.bottom;
    if ((left && right) || (top && bottom)) {
        // Dragged: drop it on the tile under the pointer.
        POINT pt{};
        GetCursorPos(&pt);
        if (!PtInRect(&frame, pt)) pt = Center(frame);
        Workspace* dest =
            GetWorkspace(MonitorFromPoint(pt, MONITOR_DEFAULTTONEAREST), ws->desktop);
        Node* under = LeafAt(dest, pt, hWnd);
        if (under && dest == ws) {
            HWND neighbour = under->hWnd;
            under->hWnd = hWnd;
            leaf->hWnd = neighbour;
            SwapLooks(under, leaf);
            g_leaves[hWnd] = {under, ws};
            g_leaves[neighbour] = {leaf, ws};
        } else if (under) {
            Relocate(hWnd, dest, under->parent, IndexOf(under) + 1);
        } else if (dest != ws) {
            Relocate(hWnd, dest, dest->root.get(), dest->root->children.size());
        }
        Layout(ws);
        if (dest != ws) Layout(dest);
        PublishTiled();
        return true;
    }
    // Resized by an edge: the neighbours make room.
    if (left) AdjustEdge(ws, leaf, kLeft, old.left - frame.left);
    if (right) AdjustEdge(ws, leaf, kRight, frame.right - old.right);
    if (top) AdjustEdge(ws, leaf, kUp, old.top - frame.top);
    if (bottom) AdjustEdge(ws, leaf, kDown, frame.bottom - old.bottom);
    Layout(ws);
    return true;
}

// Every 250 ms while windows are tiled: keeps them in their tiles, and turns a
// drag or an edge resize into a change to the layout.
void OnEnforceTimer() {
    for (auto& wsp : g_workspaces) {
        MONITORINFO mi{sizeof(mi)};
        if (wsp->root->children.empty() || GetMonitorInfoW(wsp->monitor, &mi)) continue;
        // The display went away: its windows tile wherever they are now.
        TLog(L"Tiling: a display went away");
        std::vector<Node*> leaves;
        CollectLeaves(wsp->root.get(), &leaves);
        std::vector<HWND> windows;
        for (Node* leaf : leaves) windows.push_back(leaf->hWnd);
        for (HWND hWnd : windows) RemoveWindow(hWnd);
        for (HWND hWnd : windows) {
            if (IsWindow(hWnd) && IsWindowVisible(hWnd) && !IsIconic(hWnd)) AddWindow(hWnd);
        }
        LayoutAll();
        PublishTiled();
        return;
    }
    if (GetAsyncKeyState(VK_LBUTTON) < 0 || GetAsyncKeyState(VK_RBUTTON) < 0 ||
        GetAsyncKeyState(VK_MBUTTON) < 0 || altSnapDrag::g_llRootWnd) {
        return;
    }
    ULONGLONG now = GetTickCount64();
    ULONGLONG button = g_lastMouseButtonTick;
    if (button && now - button < 200) return;
    bool byMouse = button && now - button < 2000;

    std::vector<HWND> gone;
    for (auto& entry : g_leaves) {
        HWND hWnd = entry.first;
        if (!IsWindow(hWnd) || !IsWindowVisible(hWnd) || IsIconic(hWnd)) gone.push_back(hWnd);
    }
    if (!gone.empty()) {
        TLog(L"Tiling: %d windows closed or hidden", (int)gone.size());
        std::vector<Workspace*> touched;
        for (HWND hWnd : gone) touched.push_back(RemoveWindow(hWnd));
        std::sort(touched.begin(), touched.end());
        touched.erase(std::unique(touched.begin(), touched.end()), touched.end());
        for (Workspace* ws : touched) Layout(ws);
        PublishTiled();
        return;
    }

    for (auto& wsp : g_workspaces) {
        Workspace* ws = wsp.get();
        if (ws->root->children.empty() || !ComputeLayout(ws)) continue;
        std::vector<Node*> leaves;
        CollectLeaves(ws->root.get(), &leaves);
        std::vector<Node*> changed;
        for (Node* leaf : leaves) {
            if (!SameRect(leaf->target, leaf->placedFor)) changed.push_back(leaf);
        }
        if (!changed.empty()) {
            // The work area, the gaps or a maximized neighbour changed.
            PlaceLeaves(changed);
            PublishTiled();
            continue;
        }
        for (Node* leaf : leaves) {
            HWND hWnd = leaf->hWnd;
            if (IsZoomed(hWnd)) {
                HMONITOR now = MonitorFromWindow(hWnd, MONITOR_DEFAULTTONEAREST);
                if (now != ws->monitor) {
                    // Sent to another monitor while maximized: re-home its tile.
                    Workspace* dest = GetWorkspace(now, ws->desktop);
                    Relocate(hWnd, dest, dest->root.get(), dest->root->children.size());
                    Layout({ws, dest});
                    PublishTiled();
                    return;
                }
                continue;
            }
            if (IsCloaked(hWnd) || IsHungAppWindow(hWnd) || effects::IsFullscreen(hWnd)) {
                continue;
            }
            RECT frame{};
            if (!GetFrame(hWnd, &frame)) continue;
            if (SameRect(frame, leaf->target) || SameRect(frame, leaf->placed)) {
                leaf->fights = 0;
                continue;
            }
            if (now - leaf->placedTick < 500) continue;  // Still animating into place.
            if (IsRectEmpty(&leaf->placed)) {
                PlaceLeaf(leaf);
                continue;
            }
            if (OnWindowMoved(ws, leaf, frame, byMouse)) return;
        }
    }
}

//////// thread ////////

void Hook(bool on) {
    if (on && !g_hooks[0]) {
        constexpr DWORD kFlags = WINEVENT_OUTOFCONTEXT | WINEVENT_SKIPOWNPROCESS;
        g_hooks[0] = SetWinEventHook(EVENT_SYSTEM_FOREGROUND, EVENT_SYSTEM_FOREGROUND, nullptr,
                                     EventProc, 0, 0, kFlags);
        g_hooks[1] = SetWinEventHook(EVENT_SYSTEM_MINIMIZESTART, EVENT_SYSTEM_MINIMIZEEND,
                                     nullptr, EventProc, 0, 0, kFlags);
        g_hooks[2] = SetWinEventHook(EVENT_OBJECT_DESTROY, EVENT_OBJECT_HIDE, nullptr,
                                     EventProc, 0, 0, kFlags);
        g_hooks[3] = SetWinEventHook(EVENT_OBJECT_CLOAKED, EVENT_OBJECT_UNCLOAKED, nullptr,
                                     EventProc, 0, 0, kFlags);
    } else if (!on) {
        for (auto& hook : g_hooks) {
            if (hook) UnhookWinEvent(hook);
            hook = nullptr;
        }
        g_events.clear();
    }
}

void SetTimerState(UINT_PTR* timer, bool want, UINT ms) {
    if (want && !*timer) {
        *timer = SetTimer(nullptr, 0, ms, nullptr);
    } else if (!want && *timer) {
        KillTimer(nullptr, *timer);
        *timer = 0;
    }
}

void UpdateTimers() {
    SetTimerState(&g_enforceTimer, g_active && !g_leaves.empty(), 250);
    SetTimerState(&g_pendingTimer, g_active && (!g_pending.empty() || !g_cloakCheck.empty()),
                  100);
}

// Start, settings change, pause and resume all come here.
void Apply() {
    g_config = GetSettings();
    bool want = g_config.tiling && !IsPaused() && !g_stopping;
    if (!want) {
        if (g_active) TLog(L"Tiling: off");
        g_active = false;
        Hook(false);
        ClearAll();
        return;
    }
    g_active = true;
    Hook(true);
    if (g_config.tileExisting) {
        Reconcile();
    } else {
        LayoutAll();
    }
}

DWORD WINAPI ThreadProc(LPVOID ready) {
    SetThreadDpiAwarenessContext(DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2);
    HRESULT com = CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED);
    if (FAILED(CoCreateInstance(kDesktopManagerClsid, nullptr, CLSCTX_ALL, kDesktopManagerIid,
                                reinterpret_cast<void**>(&g_desktops)))) {
        g_desktops = nullptr;
    }
    MSG msg;
    PeekMessageW(&msg, nullptr, WM_USER, WM_USER, PM_NOREMOVE);
    SetEvent((HANDLE)ready);
    Apply();
    UpdateTimers();
    while (GetMessageW(&msg, nullptr, 0, 0) > 0) {
        if (msg.hwnd) {
            DispatchMessageW(&msg);
            continue;
        }
        if (msg.message == kTilingEventMessage) {
            DrainEvents();
        } else if (msg.message == WM_TIMER && g_pendingTimer && msg.wParam == g_pendingTimer) {
            DrainEvents();
            OnPendingTimer();
        } else if (msg.message == WM_TIMER && g_enforceTimer && msg.wParam == g_enforceTimer) {
            DrainEvents();
            if (g_active) OnEnforceTimer();
        } else if (msg.message == kTilingCommandMessage) {
            DrainEvents();
            if (!IsPaused()) RunCommand((TilingCommand)msg.wParam, (int)msg.lParam);
        } else if (msg.message == kTilingReloadMessage || msg.message == kPauseChangedMessage) {
            Apply();
        } else {
            DispatchMessageW(&msg);
        }
        UpdateTimers();
    }
    g_active = false;
    Hook(false);
    ClearAll();
    g_floated.clear();
    for (auto& entry : g_borderless) RestoreBorders(entry.first, entry.second);
    g_borderless.clear();
    g_fillRestore.clear();
    SetTimerState(&g_enforceTimer, false, 0);
    SetTimerState(&g_pendingTimer, false, 0);
    if (g_desktops) {
        g_desktops->Release();
        g_desktops = nullptr;
    }
    if (SUCCEEDED(com)) CoUninitialize();
    return 0;
}

}  // namespace tiling

//////// focus by direction ////////

struct FocusSearch {
    HWND from;
    RECT frame;
    int direction;  // 0 left, 1 right, 2 up, 3 down.
    const std::vector<std::pair<HWND, RECT>>* only;  // When set, only these tiles count.
    HMONITOR monitor;  // When set, only windows on this monitor count.
    HWND best;
    double bestScore;
};

// A window level with this one wins by the gap between the facing edges, the
// way GlazeWM picks; anything off to the side only counts when nothing is level.
BOOL CALLBACK FocusSearchProc(HWND hWnd, LPARAM param) {
    auto* search = reinterpret_cast<FocusSearch*>(param);
    if (hWnd == search->from || !IsWindowVisible(hWnd) || IsIconic(hWnd) ||
        IsCloaked(hWnd) || !altSnapDrag::CanActOnRootWindow(hWnd)) {
        return TRUE;
    }
    if (GetWindowLongPtrW(hWnd, GWL_EXSTYLE) & (WS_EX_TOOLWINDOW | WS_EX_NOACTIVATE)) {
        return TRUE;
    }
    RECT frame{};
    if (search->only) {
        auto it = std::find_if(search->only->begin(), search->only->end(),
                               [hWnd](const auto& tile) { return tile.first == hWnd; });
        if (it == search->only->end()) {
            return TRUE;
        }
        frame = it->second;
    } else if (!GetFrame(hWnd, &frame)) {
        return TRUE;
    }
    if (frame.right - frame.left < 2 || frame.bottom - frame.top < 2) {
        return TRUE;
    }
    if (search->monitor && MonitorFromRect(&frame, MONITOR_DEFAULTTONEAREST) != search->monitor) {
        return TRUE;
    }
    const RECT& me = search->frame;
    long long dx = (frame.left + frame.right) / 2 - (me.left + me.right) / 2;
    long long dy = (frame.top + frame.bottom) / 2 - (me.top + me.bottom) / 2;
    long long primary, orth, gap;
    bool level;
    switch (search->direction) {
        case 0:
            primary = -dx, orth = dy, gap = me.left - frame.right;
            level = frame.top < me.bottom && frame.bottom > me.top;
            break;
        case 1:
            primary = dx, orth = dy, gap = frame.left - me.right;
            level = frame.top < me.bottom && frame.bottom > me.top;
            break;
        case 2:
            primary = -dy, orth = dx, gap = me.top - frame.bottom;
            level = frame.left < me.right && frame.right > me.left;
            break;
        default:
            primary = dy, orth = dx, gap = frame.top - me.bottom;
            level = frame.left < me.right && frame.right > me.left;
            break;
    }
    if (primary <= 0) {
        return TRUE;
    }
    double score = level ? (double)std::max<long long>(0, gap)
                         : 1e6 + primary + 2.0 * (orth < 0 ? -orth : orth);
    // Windows come front to back, so on a tie the one in front wins.
    if (!search->best || score < search->bestScore) {
        search->best = hWnd;
        search->bestScore = score;
    }
    return TRUE;
}

// Focus a window and take the pointer along, like GlazeWM.
void FocusWindow(HWND hWnd) {
    if (IsIconic(hWnd)) {
        ShowWindow(hWnd, SW_RESTORE);
    }
    if (!SetForegroundWindow(hWnd)) {
        // A zero-distance mouse input counts as user input and unlocks it.
        INPUT input{};
        input.type = INPUT_MOUSE;
        input.mi.dwFlags = MOUSEEVENTF_MOVE;
        input.mi.dwExtraInfo = kFocusInputExtraInfo;
        SendInput(1, &input, sizeof(input));
        SetForegroundWindow(hWnd);
    }
    RECT frame{};
    if (GetAsyncKeyState(VK_LBUTTON) >= 0 && GetAsyncKeyState(VK_RBUTTON) >= 0 &&
        GetFrame(hWnd, &frame)) {
        SetCursorPos((frame.left + frame.right) / 2, (frame.top + frame.bottom) / 2);
    }
}

void FocusInDirection(int direction) {
    DPI_AWARENESS_CONTEXT old =
        SetThreadDpiAwarenessContext(DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2);
    FocusSearch search{};
    search.direction = direction;
    search.from = GetAncestor(GetForegroundWindow(), GA_ROOT);
    if (!search.from || !GetFrame(search.from, &search.frame)) {
        POINT pt{};
        GetCursorPos(&pt);
        search.frame = {pt.x, pt.y, pt.x + 1, pt.y + 1};
    }
    std::vector<std::pair<HWND, RECT>> tiled;
    {
        std::lock_guard<std::mutex> lock(g_tiledMutex);
        tiled = g_tiledWindows;
    }
    auto mine = std::find_if(tiled.begin(), tiled.end(),
                             [&](const auto& tile) { return tile.first == search.from; });
    auto find = [&](HMONITOR monitor) {
        search.monitor = monitor;
        if (search.from && mine != tiled.end() && !IsRectEmpty(&mine->second)) {
            // From a tiled window, the tiles come first, so a floating window
            // lying on top doesn't steal the move.
            RECT fromFrame = search.frame;
            search.frame = mine->second;
            search.only = &tiled;
            EnumWindows(FocusSearchProc, reinterpret_cast<LPARAM>(&search));
            search.only = nullptr;
            search.frame = fromFrame;
        }
        if (!search.best) {
            EnumWindows(FocusSearchProc, reinterpret_cast<LPARAM>(&search));
        }
    };
    // Like GlazeWM: a window on this monitor first, else the monitor that
    // really lies on that side, else nothing.
    HMONITOR here = MonitorFromRect(&search.frame, MONITOR_DEFAULTTONEAREST);
    find(here);
    if (!search.best) {
        if (HMONITOR next = tiling::MonitorInDirection(here, direction)) find(next);
    }
    if (search.best) {
        FocusWindow(search.best);
    }
    if (old) {
        SetThreadDpiAwarenessContext(old);
    }
}

struct TopSearch {
    HMONITOR monitor;
    HWND best;
};

BOOL CALLBACK TopWindowProc(HWND hWnd, LPARAM param) {
    auto* search = reinterpret_cast<TopSearch*>(param);
    if (!IsWindowVisible(hWnd) || IsIconic(hWnd) || IsCloaked(hWnd) ||
        (GetWindowLongPtrW(hWnd, GWL_EXSTYLE) & (WS_EX_TOOLWINDOW | WS_EX_NOACTIVATE)) ||
        !altSnapDrag::CanActOnRootWindow(hWnd)) {
        return TRUE;
    }
    RECT frame{};
    if (!GetFrame(hWnd, &frame) || frame.right - frame.left < 2 ||
        frame.bottom - frame.top < 2 ||
        MonitorFromRect(&frame, MONITOR_DEFAULTTONEAREST) != search->monitor) {
        return TRUE;
    }
    search->best = hWnd;
    return FALSE;
}

// Alt+number: the front window on that monitor, or just the pointer when it
// has none.
void FocusMonitor(int index) {
    DPI_AWARENESS_CONTEXT old =
        SetThreadDpiAwarenessContext(DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2);
    auto monitors = OrderedMonitors();
    if (index < (int)monitors.size()) {
        TopSearch search{monitors[index].hMon, nullptr};
        EnumWindows(TopWindowProc, reinterpret_cast<LPARAM>(&search));
        if (search.best) {
            FocusWindow(search.best);
        } else if (GetAsyncKeyState(VK_LBUTTON) >= 0 && GetAsyncKeyState(VK_RBUTTON) >= 0) {
            const RECT& w = monitors[index].rcWork;
            SetCursorPos((w.left + w.right) / 2, (w.top + w.bottom) / 2);
        }
    }
    if (old) {
        SetThreadDpiAwarenessContext(old);
    }
}

//////// virtual desktops ////////

int g_desktopTarget = -1;
UINT_PTR g_desktopTimer;
ULONGLONG g_desktopTick;

bool ReadDesktops(int* count, int* current) {
    HKEY key;
    if (RegOpenKeyExW(HKEY_CURRENT_USER,
                      L"Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\VirtualDesktops",
                      0, KEY_QUERY_VALUE, &key) != ERROR_SUCCESS) {
        return false;
    }
    std::vector<BYTE> ids(16 * 64);
    DWORD size = (DWORD)ids.size();
    GUID now{};
    DWORD nowSize = sizeof(now);
    if (RegQueryValueExW(key, L"VirtualDesktopIDs", nullptr, nullptr, ids.data(), &size) !=
        ERROR_SUCCESS) {
        size = 0;
    }
    bool haveNow = RegQueryValueExW(key, L"CurrentVirtualDesktop", nullptr, nullptr,
                                    (BYTE*)&now, &nowSize) == ERROR_SUCCESS &&
                   nowSize == sizeof(now);
    RegCloseKey(key);
    int n = (int)(size / 16);
    *count = std::max(1, n);
    *current = 0;
    for (int i = 0; haveNow && i < n; i++) {
        if (memcmp(ids.data() + i * 16, &now, sizeof(now)) == 0) *current = i;
    }
    return true;
}

// Ctrl+Win+Left or Right as often as needed, and Ctrl+Win+D for each desktop
// that doesn't exist yet (each new one comes at the end and is switched to).
void SwitchDesktopNow(int target) {
    int count = 1, current = 0;
    if (!ReadDesktops(&count, &current)) return;
    std::vector<INPUT> inputs;
    auto key = [&](WORD vk, bool up) {
        INPUT in{};
        in.type = INPUT_KEYBOARD;
        in.ki.wVk = vk;
        in.ki.dwFlags = up ? KEYEVENTF_KEYUP : 0;
        if (vk == VK_LEFT || vk == VK_RIGHT || vk == VK_LWIN) {
            in.ki.dwFlags |= KEYEVENTF_EXTENDEDKEY;
        }
        in.ki.dwExtraInfo = kFocusInputExtraInfo;
        inputs.push_back(in);
    };
    int steps = (target < count ? target : count - 1) - current;
    key(VK_LCONTROL, false);
    key(VK_LWIN, false);
    for (int i = 0; i < std::abs(steps); i++) {
        key(steps < 0 ? VK_LEFT : VK_RIGHT, false);
        key(steps < 0 ? VK_LEFT : VK_RIGHT, true);
    }
    for (int i = count; i <= target; i++) {
        key('D', false);
        key('D', true);
    }
    key(VK_LWIN, true);
    key(VK_LCONTROL, true);
    if (inputs.size() > 4) {
        Wh_Log(L"Desktop: %d of %d to %d", current + 1, count, target + 1);
        SendInput((UINT)inputs.size(), inputs.data(), sizeof(INPUT));
    }
}

// Ctrl+Alt+Shift+number: the keys held for it would change the meaning of
// the Ctrl+Win keys sent, so the switch waits until they are let go.
void StartDesktopSwitch(int target) {
    g_desktopTarget = target;
    g_desktopTick = GetTickCount64();
    g_desktopTimer = SetTimer(nullptr, g_desktopTimer, 30, nullptr);
}

void OnDesktopTimer() {
    bool held = false;
    for (int vk : {VK_CONTROL, VK_MENU, VK_SHIFT, VK_LWIN, VK_RWIN}) {
        if (GetAsyncKeyState(vk) < 0) held = true;
    }
    if (held && GetTickCount64() - g_desktopTick < 1500) return;
    KillTimer(nullptr, g_desktopTimer);
    g_desktopTimer = 0;
    int target = g_desktopTarget;
    g_desktopTarget = -1;
    if (!held && target >= 0) SwitchDesktopNow(target);
}

//////// mode keys and keyboard resize (the helper's input thread) ////////

std::array<bool, kModeKeyCount> g_modeKeyRegistered{};
std::array<bool, kModeKeyCount> g_modeKeyFailLogged{};
bool g_resizeActive;
HWND g_resizeTarget;
UINT_PTR g_resizeTimer;
std::array<bool, 256> g_swallowedKeys{};

void UnregisterModeKeys() {
    for (size_t i = 0; i < g_modeKeyRegistered.size(); i++) {
        if (g_modeKeyRegistered[i]) {
            UnregisterHotKey(nullptr, kModeKeyBase + (int)i);
            g_modeKeyRegistered[i] = false;
        }
    }
    g_modeKeyFailLogged = {};
}

// Registers what is missing. While paused only the pause key stays.
void RegisterModeKeys() {
    if (!altSnapDrag::g_globalInput) {
        return;
    }
    Settings s = GetSettings();
    bool paused = IsPaused();
    for (size_t i = 0; i < g_modeKeyRegistered.size(); i++) {
        bool want = s.keys[i].key && (!paused || i == 0);
        if (!want) {
            if (g_modeKeyRegistered[i]) {
                UnregisterHotKey(nullptr, kModeKeyBase + (int)i);
                g_modeKeyRegistered[i] = false;
            }
            continue;
        }
        if (g_modeKeyRegistered[i]) {
            continue;
        }
        UINT mods = ToHotkeyMods(s.keys[i].modifiers);
        // Holding a grow key keeps growing.
        if (i < kFirstGrowKey || i > kLastGrowKey) {
            mods |= MOD_NOREPEAT;
        }
        g_modeKeyRegistered[i] =
            RegisterHotKey(nullptr, kModeKeyBase + (int)i, mods, s.keys[i].key) != FALSE;
        if (!g_modeKeyRegistered[i] && !g_modeKeyFailLogged[i]) {
            g_modeKeyFailLogged[i] = true;
            Wh_Log(L"%ls: another app already uses this key (%lu)", kModeKeyNames[i],
                   GetLastError());
        }
    }
}

void RestartResizeTimer() {
    g_resizeTimer =
        SetTimer(nullptr, g_resizeTimer, GetSettings().resizeTimeoutMs, nullptr);
}

void EnterResizeMode() {
    HWND target = GetAncestor(GetForegroundWindow(), GA_ROOT);
    if (!target || IsIconic(target) || IsZoomed(target) ||
        !altSnapDrag::CanSizeRootWindow(target)) {
        return;
    }
    g_resizeTarget = target;
    g_resizeActive = true;
    RestartResizeTimer();
    ShowOsd(kOsdResize);
}

void LeaveResizeMode() {
    if (!g_resizeActive) {
        return;
    }
    g_resizeActive = false;
    g_resizeTarget = nullptr;
    if (g_resizeTimer) {
        KillTimer(nullptr, g_resizeTimer);
        g_resizeTimer = 0;
    }
    HideOsd();
}

// From the keyboard hook. Swallows the keys resize mode uses, and later their
// releases even if the mode ended in between; every other key passes.
bool OnResizeKey(WPARAM message, const KBDLLHOOKSTRUCT* key) {
    DWORD vk = key->vkCode;
    if (vk > 255) {
        return false;
    }
    bool down = message == WM_KEYDOWN || message == WM_SYSKEYDOWN;
    if (!down) {
        if (g_swallowedKeys[vk]) {
            g_swallowedKeys[vk] = false;
            return true;
        }
        return false;
    }
    if (!g_resizeActive) {
        return false;
    }
    int dx = 0, dy = 0;
    bool leave = false;
    switch (vk) {
        case VK_LEFT: case 'H': dx = -1; break;
        case VK_RIGHT: case 'L': dx = 1; break;
        case VK_UP: case 'K': dy = -1; break;
        case VK_DOWN: case 'J': dy = 1; break;
        case VK_ESCAPE: case VK_RETURN: leave = true; break;
        default: return false;
    }
    if (!IsWindow(g_resizeTarget) ||
        GetAncestor(GetForegroundWindow(), GA_ROOT) != g_resizeTarget) {
        LeaveResizeMode();
        return false;
    }
    g_swallowedKeys[vk] = true;
    if (leave) {
        LeaveResizeMode();
    } else {
        snapCommander::EnqueueNudge(g_resizeTarget, dx, dy,
                                    GetAsyncKeyState(VK_SHIFT) < 0);
        RestartResizeTimer();
    }
    altSnapDrag::g_swallowedPress = GetAsyncKeyState(VK_MENU) < 0;
    return true;
}

void TogglePause() {
    bool paused = !g_paused;
    g_paused = paused;
    if (g_pauseEvent) {
        paused ? SetEvent(g_pauseEvent) : ResetEvent(g_pauseEvent);
    }
    if (paused) {
        LeaveResizeMode();
    }
    PostThreadMessageW(GetCurrentThreadId(), kPauseChangedMessage, 0, 0);
    if (snapCommander::g_hookThreadId) {
        PostThreadMessageW(snapCommander::g_hookThreadId, kPauseChangedMessage, 0, 0);
    }
    if (moveToMonitor::g_hMsgWnd) {
        PostMessageW(moveToMonitor::g_hMsgWnd, kPauseChangedMessage, 0, 0);
    }
    if (g_effectsThreadId) {
        PostThreadMessageW(g_effectsThreadId, kPauseChangedMessage, 0, 0);
    }
    if (g_tilingThreadId) {
        PostThreadMessageW(g_tilingThreadId, kPauseChangedMessage, 0, 0);
    }
    ApplyFocusTracking();
    ShowOsd(paused ? kOsdPaused : kOsdRunning);
    Wh_Log(L"%ls", paused ? L"Paused" : L"Resumed");
}

bool OnLowLevelThreadMessage(const MSG& msg) {
    if (!altSnapDrag::g_globalInput || msg.hwnd) {
        return false;
    }
    if (msg.message == WM_TIMER && g_resizeTimer && msg.wParam == g_resizeTimer) {
        LeaveResizeMode();
        return true;
    }
    if (msg.message == WM_TIMER && g_desktopTimer && msg.wParam == g_desktopTimer) {
        OnDesktopTimer();
        return true;
    }
    if (msg.message != WM_HOTKEY || msg.wParam < (WPARAM)kModeKeyBase ||
        msg.wParam >= (WPARAM)kModeKeyBase + g_modeKeyRegistered.size()) {
        return false;
    }
    int id = (int)msg.wParam - kModeKeyBase;
    if (id == 0) {
        TogglePause();
    } else if (!IsPaused()) {
        if (id == 1) {
            if (g_resizeActive) {
                LeaveResizeMode();
            } else {
                EnterResizeMode();
            }
        } else if (id <= 5) {
            FocusInDirection(id - 2);
        } else if (id <= 9) {
            PostTilingCommand(kTileMove, id - 6);
        } else if (id <= 13) {
            PostTilingCommand(kTileGrow, id - 10);
        } else if (id == 14) {
            PostTilingCommand(kTileToggle, 0);
        } else if (id == 15) {
            PostTilingCommand(kTileFlip, 0);
        } else if (id == 16) {
            PostTilingCommand(kTileFill, 0);
        } else if (id == 17) {
            PostTilingCommand(kTileBorderless, 0);
        } else if (id < kFirstSendMonitorKey) {
            FocusMonitor(id - kFirstMonitorKey);
        } else if (id < kFirstDesktopKey) {
            PostTilingCommand(kTileSendMonitor, id - kFirstSendMonitorKey);
        } else if (id == 35) {
            PostTilingCommand(kTileCycleFocus, 1);
        } else if (id == 36) {
            PostTilingCommand(kTileCycleFocus, -1);
        } else if (id == 37) {
            PostTilingCommand(kTileRestoreMinimized, 0);
        } else {
            StartDesktopSwitch(id - kFirstDesktopKey);
        }
    }
    // The Alt release that follows must not open the app's menu bar.
    altSnapDrag::g_swallowedPress = GetAsyncKeyState(VK_MENU) < 0;
    return true;
}

//////// helper lifecycle ////////

void Start() {
    StartThread(effects::ThreadProc, &g_effectsThread, &g_effectsThreadId);
    StartThread(osd::ThreadProc, &g_osdThread, &g_osdThreadId);
}

// Last, once the snap part has read its gaps and rules.
void StartTiling() {
    if (!g_tilingThread) {
        StartThread(tiling::ThreadProc, &g_tilingThread, &g_tilingThreadId);
    }
}

void ReloadTiling() {
    if (g_tilingThreadId) {
        PostThreadMessageW(g_tilingThreadId, kTilingReloadMessage, 0, 0);
    }
}

void OnSettingsChanged() {
    if (g_effectsThreadId) {
        PostThreadMessageW(g_effectsThreadId, kEffectsReloadMessage, 0, 0);
    }
    ApplyFocusTracking();
}

void Stop() {
    g_stopping = true;
    StopThread(&g_tilingThread, &g_tilingThreadId);
    StopThread(&g_effectsThread, &g_effectsThreadId);
    StopThread(&g_osdThread, &g_osdThreadId);
    ApplyFocusTracking();
}

}  // namespace swm
// ---------------------------------------------------------------------------------------------

BOOL WhTool_ModInit() {
    SeamlessMenuSkin::Init();
    using namespace altSnapDrag;
    HANDLE token;
    TOKEN_ELEVATION elevation{};
    DWORD bytes = 0;
    if (!OpenProcessToken(GetCurrentProcess(), TOKEN_QUERY, &token)) return FALSE;
    bool queried = GetTokenInformation(token, TokenElevation, &elevation, sizeof(elevation), &bytes);
    CloseHandle(token);
    if (!queried) return FALSE;
    if (!elevation.TokenIsElevated) {
        SHELLEXECUTEINFOW launch{sizeof(launch)};
        launch.fMask = SEE_MASK_FLAG_NO_UI;
        launch.lpVerb = L"runas";
        WCHAR self[MAX_PATH];
        if (!GetModuleFileNameW(nullptr, self, MAX_PATH)) return FALSE;
        launch.lpFile = self;
        launch.lpParameters = L"-windhawk-tool-mod \"" WH_MOD_ID L"\"";
        launch.nShow = SW_HIDE;
        ShellExecuteExW(&launch);
        return FALSE;
    }
    g_globalInput = true;
    // Everyone may open it, so the unelevated per-app parts see the helper
    // and leave the global input to it.
    SECURITY_ATTRIBUTES sa{sizeof(sa)};
    if (!ConvertStringSecurityDescriptorToSecurityDescriptorW(
            L"D:(A;;GA;;;SY)(A;;GA;;;BA)(A;;0x00100000;;;WD)S:(ML;;NW;;;LW)",
            SDDL_REVISION_1, &sa.lpSecurityDescriptor, nullptr)) return FALSE;
    g_globalMutex = CreateMutex(&sa, FALSE, kHelperMutexName);
    DWORD mutexError = GetLastError();
    LocalFree(sa.lpSecurityDescriptor);
    if (!g_globalMutex) return FALSE;
    if (mutexError == ERROR_ALREADY_EXISTS) {
        CloseHandle(g_globalMutex);
        g_globalMutex = nullptr;
        return FALSE;
    }
    swm::CreatePauseEvent();
    LoadSettings();
    swm::LoadSettings();
    swm::Start();
    swm::ApplyFocusTracking();
    HKEY key;
    if (RegOpenKeyExW(HKEY_LOCAL_MACHINE, L"SOFTWARE\\Windhawk\\Engine\\Mods\\" WH_MOD_ID,
                      0, KEY_QUERY_VALUE, &key) == ERROR_SUCCESS) {
        for (PCWSTR name : {L"Exclude", L"ExcludeCustom"}) {
            WCHAR value[32768]{};
            DWORD bytes = sizeof(value);
            if (RegQueryValueExW(key, name, nullptr, nullptr, (BYTE*)value, &bytes) == ERROR_SUCCESS) {
                value[ARRAYSIZE(value) - 1] = 0;
                g_globalExclusions += L"|";
                g_globalExclusions += value;
            }
        }
        RegCloseKey(key);
    }
    InstallLowLevelMouseHookIfNeeded();
    bool ok = g_lowLevelMouseHookThread != nullptr;
    bool snapOk = ok && snapCommander::ToolModInit();
    if (snapOk && moveToMonitor::ToolModInit()) {
        swm::StartTiling();
        return TRUE;
    }
    // A helper which fails partway leaves nothing running behind it.
    g_uninitializing = true;
    StopLowLevelMouseHookThread();
    if (snapOk) snapCommander::ToolModUninit();
    swm::Stop();
    swm::ClosePauseEvent();
    CloseHandle(g_globalMutex);
    g_globalMutex = nullptr;
    return FALSE;
}

void WhTool_ModSettingsChanged() {
    swm::LoadSettings();
    swm::OnSettingsChanged();
    PostThreadMessage(altSnapDrag::g_lowLevelMouseHookOwnThreadId, WM_APP + 91, 0, 0);
    snapCommander::ToolModSettingsChanged();
    moveToMonitor::ToolModSettingsChanged();
    swm::ReloadTiling();
}

void WhTool_ModUninit() {
    SeamlessMenuSkin::Uninit();
    swm::Stop();
    altSnapDrag::g_uninitializing = true;
    altSnapDrag::StopLowLevelMouseHookThread();
    altSnapDrag::mover::Stop();
    snapCommander::ToolModUninit();
    moveToMonitor::ToolModUninit();
    swm::ClosePauseEvent();
    if (g_globalMutex) CloseHandle(g_globalMutex);
}

BOOL WhToolLauncher_ModInit(BOOL* launch) {
    WCHAR path[MAX_PATH]{};
    GetModuleFileNameW(nullptr, path, ARRAYSIZE(path));
    *launch = _wcsicmp(PathFindFileNameW(path), L"windhawk.exe") == 0;
    g_packDragInited = altSnapDrag::ModInit();
    return g_packDragInited;
}

void WhToolLauncher_ModUninit() {
    if (g_packDragInited) altSnapDrag::ModUninit();
    swm::ClosePauseEvent();
}

void WhToolLauncher_ModSettingsChanged(BOOL* reload) {
    *reload = TRUE;
    if (g_packDragInited) altSnapDrag::ModSettingsChanged();
}

BOOL WINAPI DllMain(HINSTANCE module, DWORD reason, LPVOID reserved) {
    return altSnapDrag::DragDllMain(module, reason, reserved);
}
