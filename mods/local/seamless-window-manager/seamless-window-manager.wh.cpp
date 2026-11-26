// ==WindhawkMod==
// @id              seamless-window-manager
// @name            Seamless Window Manager
// @description     Move, resize, snap and focus windows with the mouse or keyboard, with app rules, gaps and a pause key
// @version         2.8.14
// @author          DavidHiFi, m417z, Asteski, TomberWolf, RamonUnch, Stefan Sundin
// @github          https://github.com/DavidHiFi
// @homepage        https://github.com/DavidHiFi/davids-windhawk-mods
// @license         GPL-3.0
// @include         *
// @include         windhawk.exe
// @exclude         cloudflared.exe
// @exclude         ollama.exe
// @exclude         ollama app.exe
// @exclude         tailscale-ipn.exe
// @exclude         esbuild.exe
// @compilerOptions -luser32 -ldwmapi -lgdi32 -lshcore -lcomctl32 -lshell32 -lshlwapi -ladvapi32 -ld2d1 -luxtheme -ldwrite -lole32 -loleaut32 -luuid -lwindowscodecs -lcomdlg32 -limm32
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
- **Tiling.** New windows fill the screen side by side, like GlazeWM. A new
  window takes half of the biggest tile, so nothing opens as a thin strip.
  Over a full-screen game it opens in the middle instead and joins the tiles
  once the game closes. Move them around with Alt+Shift+arrow keys, grow them with
  Ctrl+Alt+Shift+arrow keys, and float one with Alt+T. The half and quarter
  keys rearrange the tiles around the window. Dragging a tiled window onto
  another swaps them, and dragging an edge resizes its neighbours too. A tile
  never shrinks below the app's own smallest size, so nothing spills onto the
  next monitor.
- **Fill and borderless.** Alt+F fills the screen but keeps the gaps around
  the window. Ctrl+Shift+F takes the title bar and borders off and covers the
  whole monitor, taskbar included. Press either again to go back.
- **Hide the title bar** with Ctrl+Win+Alt+T. The window keeps its size and
  place; press again to bring the title bar back.
- **Hidden windows.** Alt+PageDown brings up the window hidden behind the
  ones in front, even one behind two tiles side by side. Press again for the
  one behind that, and once more to come back round. Alt+PageUp goes the
  other way.
- **Focus by direction.** Alt+arrow keys switch to the nearest window on that
  side, on any monitor, and the mouse pointer jumps with you. The window you
  land on gets a soft blue to mauve ring that closes in on its edge and
  fades (or a zoom, or nothing: pick under Animation and fade).
- **Focus follows the mouse**, if you want it, and the pointer can jump to
  the window you switch to with the keyboard.
- **App rules** place, pin, fade or skip chosen apps. Match by app name,
  window title or class, with plain text or a regex.
- **Pause** with Alt+Shift+P. Everything stops until you press it again,
  and a small popup tells you which state you're in.
- **Fade windows you are not using** makes inactive windows slightly see-through.
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
| Alt + H / Y | Maximize, or maximize with a margin |
| Alt + ] / [ | Send to the next or previous monitor |
| Alt + 1 / 2 / 3 / 4 | Focus monitor 1 to 4 (left, main, right, top) |
| Alt + Shift + 1 / 2 / 3 / 4 | Send the window to that monitor |
| Ctrl + Alt + Shift + 1 to 9 | Switch virtual desktop |
| Ctrl + Alt + left drag | Move with magnetic edges |
| Alt + Z | Undo the snap |
| Alt + F | Fill the screen inside the gaps |
| Ctrl + Shift + F | Fullscreen without a title bar |
| Alt + M | Minimize |
| Alt + Shift + Q | Close |
| Alt + Shift + R | Resize with the keyboard |
| Alt + Shift + P | Pause or resume |
| Alt + middle click | Window menu |

You can change or turn off every shortcut in the settings. Alt+Left and
Alt+Right replace Back and Forward in browsers and File Explorer; pick other
keys if you need those. Windows glide into place instead of jumping; the
length is under Animation and fade. When a snap or monitor shortcut matches one of
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
- Fading skips windows that already use Mica or acrylic, and
  apps that handle their own transparency.
- Other mods that put windows back where they were can fight the tiling.
  Turn their restore option off, or list the app under Apps that never tile.
- Focus follows the mouse uses the Windows setting of the same name and puts
  it back the way it was when you turn the mod off.
- An app that stops responding keeps its tile and its own title bar. While
  tiling is on, Windows doesn't swap in its pale stand-in window, so a busy
  app no longer flickers. Apps started before tiling was turned on keep the
  stand-in until they restart.

## What's new in 2.8.12

- Title bar menus (right-click the title bar, or Alt+Space) now really get the same
  blurred Mocha body as every other menu. They opened pitch black before.

## What's new in 2.8.8
- Two windows that can't both fit in one column no longer make every tiled
  window bounce. A window that grows back to its own smallest size is no
  longer taken for one you resized by hand just because you clicked
  somewhere in the last two seconds.

## What's new in 2.8.7
- The walk keys log less: one line per step, and nothing for a plain Page Up
  or Page Down. 2.8.5 wrote a line for every press of those keys.

## What's new in 2.8.6
- Alt+PageDown and Alt+PageUp no longer stop working after a remote desktop
  window catches the moment you let go of the key.

## What's new in 2.8.5
- Alt+PageDown and Alt+PageUp note each step in the mod's log, to track down
  a PC where they do nothing over a full-screen remote desktop window.

## What's new in 2.8.4
- Alt+PageDown and Alt+PageUp now work when a remote desktop window (like
  RustDesk) is in front. Those apps used to send the keys to the other PC,
  so the walk got stuck on them. Every other key still goes to the other PC.

## What's new in 2.8.3
- Agent windows: only the agent that was let use the mouse and keys gets them.
  Other agents running at the same time stay hands-off.

## What's new in 2.8.2
- Agent windows: when an agent has been let use the mouse and keys because you
  stepped away, it loses them the moment you touch the mouse or keyboard again.

## What's new in 2.8.1
- Game guard: the per-app part (window dragging, snapping, wobble) no longer
  loads into games or their anti-cheat, so it cannot add stutter or a ban risk
  there. Launchers such as Steam keep it. Turn it off or add your own lists in
  the new "Game guard" settings.

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

#include <shlwapi.h>
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
#include <shobjidl.h>

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
// The tray icon's window; a pause or resume tells it to redraw.
inline std::atomic<HWND> g_trayWnd{nullptr};
constexpr UINT kTrayUpdateMessage = WM_APP + 46;
// Last mouse button press or release seen by the helper's low level hook.
inline std::atomic<ULONGLONG> g_lastMouseButtonTick{0};
// The last window moved or sized by hand (title bar drag, edge resize or Alt drag), and when.
// Only that window's change counts as the owner's own; a click anywhere else does not.
inline std::atomic<HWND> g_handMovedWnd{nullptr};
inline std::atomic<ULONGLONG> g_handMovedTick{0};
inline std::atomic<int> g_resizeStepPct{2};
// Glide length for snaps and tiles; 0 is off. g_animOff > 0 skips it on a thread.
inline std::atomic<int> g_animMs{180};
inline thread_local int g_animOff = 0;
// Focus animation length; 0 is off. g_focusRing: the ring (drawn by the
// helper) rather than the zoom (played inside the app).
inline std::atomic<int> g_focusAnimMs{450};
inline std::atomic<bool> g_focusRing{true};
// Ctrl+Alt drag: how close an edge must come to cling, and the gap kept.
inline std::atomic<int> g_magnetPx{20};
inline std::atomic<int> g_magnetGap{20};
// Marks the zero-distance mouse input sent to unlock SetForegroundWindow.
constexpr ULONG_PTR kFocusInputExtraInfo = 0x53574D31;
constexpr UINT kPauseChangedMessage = WM_APP + 300;
bool IsPaused();
bool OnResizeKey(WPARAM message, const KBDLLHOOKSTRUCT* key);
bool OnWalkKey(WPARAM message, const KBDLLHOOKSTRUCT* key);
bool OnLowLevelThreadMessage(const MSG& msg);
void RegisterModeKeys();
void UnregisterModeKeys();
void LeaveResizeMode();
void ApplyRuleLook(HWND hWnd, BYTE alpha, bool onTop);
bool IsReservedHotkey(UINT mods, UINT vk);
bool IsTiledWindow(HWND hWnd);
void PostTileRegion(int region);
void MoveToMonitorNumber(HWND hWnd, int index);
// The tiling thread, told when a mouse button comes up so it checks the
// tiles soon instead of at its slow pace.
inline std::atomic<DWORD> g_tilingNudgeThread{0};
constexpr UINT kTilingNudgeMessage = WM_APP + 323;

// The image path of a process, cached by pid and start time so a reused pid
// misses. Opening the process is cheap; turning its image into a path is not.
inline std::wstring ProcessImagePath(DWORD pid) {
    HANDLE process = OpenProcess(PROCESS_QUERY_LIMITED_INFORMATION, FALSE, pid);
    if (!process) return L"";
    FILETIME created{}, exited{}, kernel{}, user{};
    ULONGLONG start = 0;
    if (GetProcessTimes(process, &created, &exited, &kernel, &user)) {
        start = ((ULONGLONG)created.dwHighDateTime << 32) | created.dwLowDateTime;
    }
    static std::mutex lock;
    static std::unordered_map<DWORD, std::pair<ULONGLONG, std::wstring>> cache;
    if (start) {
        std::lock_guard<std::mutex> guard(lock);
        auto it = cache.find(pid);
        if (it != cache.end() && it->second.first == start) {
            CloseHandle(process);
            return it->second.second;
        }
    }
    std::wstring path(1024, L'\0');
    DWORD size = (DWORD)path.size();
    if (QueryFullProcessImageNameW(process, 0, path.data(), &size)) {
        path.resize(size);
    } else {
        path.clear();
    }
    CloseHandle(process);
    if (start && !path.empty()) {
        std::lock_guard<std::mutex> guard(lock);
        if (cache.size() > 256) cache.clear();
        cache[pid] = {start, path};
    }
    return path;
}
}  // namespace swm
namespace snapCommander {
static void AnimateRects(const std::vector<std::pair<HWND, RECT>>& moves);
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
    DragMaximize,
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
// Tells Seamless Wobbly Windows that a held-key move of this window started
// (wParam 1) or ended (wParam 0). The press and release are swallowed here, so
// the window's process can't see the button on its own.
UINT g_wobbleDragMessage =
    RegisterWindowMessage(L"SeamlessWobblyWindows_ExternalDrag");
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
// The helper asks an app's own copy of the mod to play the focus animation on
// its window (wParam: length in ms).
UINT g_focusPulseMessage =
    RegisterWindowMessage(L"Windhawk_FocusPulse_" WH_MOD_ID);
// The helper asks an app's own copy of the mod to move its window to another
// virtual desktop (wParam: desktop index). Windows only lets a process move
// its own windows.
UINT g_desktopRequestMessage =
    RegisterWindowMessage(L"Windhawk_DesktopRequest_" WH_MOD_ID);

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
        std::wstring fullPath = swm::ProcessImagePath(pid);
        if (fullPath.empty()) return true;
        PCWSTR path = fullPath.c_str();
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
        } else {
            std::wstring path = swm::ProcessImagePath(pid);
            if (!path.empty()) exeName = PathFindFileNameW(path.c_str());
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
namespace mover { bool QueueDragMaximize(HWND wnd); }

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
    if (action == WindowAction::DragMaximize && mover::QueueDragMaximize(hWnd)) {
        return true;
    }
    if (action == WindowAction::Maximize || action == WindowAction::DragMaximize) {
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
// at the right end stays clickable. The point, the rect and the strip height
// are all in the calling thread's pixels.
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

    UINT dpi = 96;
    switch (GetAwarenessFromDpiAwarenessContext(GetThreadDpiAwarenessContext())) {
        case DPI_AWARENESS_PER_MONITOR_AWARE: dpi = GetDpiForWindow(hRootWnd); break;
        case DPI_AWARENESS_SYSTEM_AWARE: dpi = GetDpiForSystem(); break;
        default: break;
    }
    int stripHeight = MulDiv(36, dpi ? dpi : 96, 96);
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

//////// focus animation ////////
// When a focus key lands on a window, the helper posts g_focusPulseMessage to
// it. This app's own copy of the mod hides the real window for a moment and
// shows a live picture of it zooming in from 94% while it fades in, the same
// look as the Alt+Tab animation. Only the app's own process may hide (cloak)
// its windows, which is why this runs here and not in the helper.

constexpr PCWSTR kFocusPulseProp = L"SeamlessWM.FocusPulseV1";
// Windows Animations' own Alt+Tab zoom: if it took this window, stand down.
constexpr PCWSTR kSwitchAnimationProp = L"windows-animations.SwitchAnimationActiveV1";

std::mutex g_focusPulseMutex;
std::vector<HANDLE> g_focusPulseThreads;
std::atomic<bool> g_focusPulseStop{false};

// An activation change that lands while the window is cloaked can leave Mica
// in its darker inactive look (Explorer's header and command bar). Telling the
// window its real active state again makes DWM redraw the backdrop to match.
// The old fix set the same backdrop and accent values again; DWM ignores that.
void RefreshBackdropAfterUncloak(HWND hWnd) {
    BOOL active = GetForegroundWindow() == hWnd;
    DWORD_PTR result = 0;
    SendMessageTimeoutW(hWnd, WM_NCACTIVATE, active, 0, SMTO_ABORTIFHUNG | SMTO_NORMAL, 100,
                        &result);
    SetWindowPos(hWnd, nullptr, 0, 0, 0, 0,
                 SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE | SWP_FRAMECHANGED |
                     SWP_ASYNCWINDOWPOS);
}

struct FocusPulseJob {
    HWND hWnd;
    int ms;
};

DWORD WINAPI FocusPulseThread(LPVOID param) {
    std::unique_ptr<FocusPulseJob> job((FocusPulseJob*)param);
    HWND hWnd = job->hWnd;
    // This thread pumps messages for its picture window; it needs none of the
    // mod's drag hooks.
    g_threadHooksAttempted = true;
    SetThreadDpiAwarenessContext(DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2);
    BOOL cloak = FALSE;
    auto finish = [&](HWND ghost, HTHUMBNAIL thumb) {
        if (cloak && IsWindow(hWnd)) {
            BOOL off = FALSE;
            DwmSetWindowAttribute(hWnd, DWMWA_CLOAK, &off, sizeof(off));
            RefreshBackdropAfterUncloak(hWnd);
            DwmFlush();
        }
        if (thumb) DwmUnregisterThumbnail(thumb);
        if (ghost) DestroyWindow(ghost);
        if (IsWindow(hWnd)) RemovePropW(hWnd, kFocusPulseProp);
        return 0;
    };

    // Give Windows Animations its moment: on Explorer with Alt held it runs
    // its own zoom, and two at once would look doubled.
    Sleep(20);
    // Let the activation finish first (up to 80 ms more), so Mica switches to
    // its active look while the window can still be seen.
    for (int i = 0; i < 8 && GetForegroundWindow() != hWnd && !g_focusPulseStop; i++) {
        Sleep(10);
    }
    BOOL cloaked = FALSE;
    if (g_focusPulseStop || !IsWindow(hWnd) || !IsWindowVisible(hWnd) || IsIconic(hWnd) ||
        GetPropW(hWnd, kSwitchAnimationProp) ||
        (SUCCEEDED(DwmGetWindowAttribute(hWnd, DWMWA_CLOAKED, &cloaked, sizeof(cloaked))) &&
         cloaked)) {
        return finish(nullptr, nullptr);
    }
    RECT win{}, ext{};
    if (!GetWindowRect(hWnd, &win) ||
        FAILED(DwmGetWindowAttribute(hWnd, DWMWA_EXTENDED_FRAME_BOUNDS, &ext, sizeof(ext)))) {
        return finish(nullptr, nullptr);
    }
    int W = ext.right - ext.left, H = ext.bottom - ext.top;
    if (W < 8 || H < 8) return finish(nullptr, nullptr);
    HWND ghost = CreateWindowExW(
        WS_EX_NOREDIRECTIONBITMAP | WS_EX_TOOLWINDOW | WS_EX_NOACTIVATE | WS_EX_TRANSPARENT,
        L"STATIC", nullptr, WS_POPUP, ext.left, ext.top, W, H, nullptr, nullptr, nullptr,
        nullptr);
    if (!ghost) return finish(nullptr, nullptr);
    HTHUMBNAIL thumb = nullptr;
    if (FAILED(DwmRegisterThumbnail(ghost, hWnd, &thumb))) return finish(ghost, nullptr);
    // Only the visible frame, not the invisible resize border around it.
    RECT source{ext.left - win.left, ext.top - win.top, ext.left - win.left + W,
                ext.top - win.top + H};
    auto frame = [&](float scale, BYTE opacity) {
        DWM_THUMBNAIL_PROPERTIES p{};
        p.dwFlags = DWM_TNP_VISIBLE | DWM_TNP_OPACITY | DWM_TNP_RECTDESTINATION |
                    DWM_TNP_RECTSOURCE | DWM_TNP_SOURCECLIENTAREAONLY;
        p.fVisible = TRUE;
        p.fSourceClientAreaOnly = FALSE;
        p.opacity = opacity;
        p.rcSource = source;
        int w = (int)(W * scale + 0.5f), h = (int)(H * scale + 0.5f);
        p.rcDestination = {(W - w) / 2, (H - h) / 2, (W - w) / 2 + w, (H - h) / 2 + h};
        DwmUpdateThumbnailProperties(thumb, &p);
    };
    frame(0.94f, 0);
    ShowWindow(ghost, SW_SHOWNOACTIVATE);
    // The picture sits just above the window, below anything pinned on top.
    SetWindowPos(ghost, HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
    cloak = TRUE;
    SetPropW(hWnd, kFocusPulseProp, (HANDLE)1);
    DwmSetWindowAttribute(hWnd, DWMWA_CLOAK, &cloak, sizeof(cloak));
    DwmFlush();

    LARGE_INTEGER freq, start, now;
    QueryPerformanceFrequency(&freq);
    QueryPerformanceCounter(&start);
    for (;;) {
        MSG m;
        while (PeekMessageW(&m, nullptr, 0, 0, PM_REMOVE)) DispatchMessageW(&m);
        QueryPerformanceCounter(&now);
        double t = (now.QuadPart - start.QuadPart) * 1000.0 / freq.QuadPart / job->ms;
        bool last = t >= 1.0 || g_focusPulseStop || !IsWindow(hWnd);
        float p = last ? 1.0f : (float)t;
        float ease = 1.0f - (1.0f - p) * (1.0f - p) * (1.0f - p);
        frame(0.94f + 0.06f * ease, (BYTE)(255.0f * ease));
        if (last) break;
        DwmFlush();
    }
    return finish(ghost, thumb);
}

void StartFocusPulse(HWND hWnd, int ms) {
    if (!hWnd || GetAncestor(hWnd, GA_ROOT) != hWnd || GetPropW(hWnd, kFocusPulseProp) ||
        g_focusPulseStop) {
        return;
    }
    std::lock_guard<std::mutex> lock(g_focusPulseMutex);
    // Forget the ones that finished.
    std::erase_if(g_focusPulseThreads, [](HANDLE h) {
        if (WaitForSingleObject(h, 0) != WAIT_OBJECT_0) return false;
        CloseHandle(h);
        return true;
    });
    if (g_focusPulseThreads.size() >= 4) return;
    auto* job = new FocusPulseJob{hWnd, std::clamp(ms, 60, 600)};
    HANDLE thread = CreateThread(nullptr, 0, FocusPulseThread, job, 0, nullptr);
    if (thread) {
        g_focusPulseThreads.push_back(thread);
    } else {
        delete job;
    }
}

struct DesktopMoveJob {
    HWND hWnd;
    int index;
};

DWORD WINAPI DesktopMoveThread(LPVOID param) {
    std::unique_ptr<DesktopMoveJob> job((DesktopMoveJob*)param);
    HKEY key;
    if (RegOpenKeyExW(HKEY_CURRENT_USER,
                      L"Software\\Microsoft\\Windows\\CurrentVersion\\Explorer\\VirtualDesktops",
                      0, KEY_QUERY_VALUE, &key) != ERROR_SUCCESS) {
        return 0;
    }
    std::vector<BYTE> ids(16 * 64);
    DWORD size = (DWORD)ids.size();
    bool read = RegQueryValueExW(key, L"VirtualDesktopIDs", nullptr, nullptr, ids.data(),
                                 &size) == ERROR_SUCCESS;
    RegCloseKey(key);
    if (!read || job->index < 0 || (DWORD)(job->index + 1) * 16 > size) return 0;
    GUID id{};
    memcpy(&id, ids.data() + job->index * 16, sizeof(id));
    static constexpr GUID kClsid = {
        0xaa509086, 0x5ca9, 0x4c25, {0x8f, 0x95, 0x58, 0x9d, 0x3c, 0x07, 0xb4, 0x8a}};
    static constexpr GUID kIid = {
        0xa5cd92ff, 0x29be, 0x454c, {0x8d, 0x04, 0xd8, 0x28, 0x79, 0xfb, 0x3f, 0x1b}};
    HRESULT com = CoInitializeEx(nullptr, COINIT_MULTITHREADED);
    IVirtualDesktopManager* manager = nullptr;
    if (SUCCEEDED(CoCreateInstance(kClsid, nullptr, CLSCTX_ALL, kIid,
                                   reinterpret_cast<void**>(&manager)))) {
        HRESULT hr = manager->MoveWindowToDesktop(job->hWnd, id);
        Wh_Log(L"Send %p to desktop %d: %08lX", job->hWnd, job->index + 1, (unsigned long)hr);
        manager->Release();
    }
    if (SUCCEEDED(com)) CoUninitialize();
    return 0;
}

void StartDesktopMove(HWND hWnd, int index) {
    if (!hWnd || GetAncestor(hWnd, GA_ROOT) != hWnd || g_focusPulseStop) return;
    std::lock_guard<std::mutex> lock(g_focusPulseMutex);
    std::erase_if(g_focusPulseThreads, [](HANDLE h) {
        if (WaitForSingleObject(h, 0) != WAIT_OBJECT_0) return false;
        CloseHandle(h);
        return true;
    });
    if (g_focusPulseThreads.size() >= 4) return;
    auto* job = new DesktopMoveJob{hWnd, index};
    HANDLE thread = CreateThread(nullptr, 0, DesktopMoveThread, job, 0, nullptr);
    if (thread) {
        g_focusPulseThreads.push_back(thread);
    } else {
        delete job;
    }
}

// Before the mod unloads, the pictures finish and the windows come back.
void StopFocusPulses() {
    g_focusPulseStop = true;
    std::lock_guard<std::mutex> lock(g_focusPulseMutex);
    for (HANDLE h : g_focusPulseThreads) {
        WaitForSingleObject(h, 2000);
        CloseHandle(h);
    }
    g_focusPulseThreads.clear();
}

// Runs for every message removed from the queue of the current thread, before
// the program sees it.
void OnMessageRemoved(MSG* msg) {
    if (msg->message == g_focusPulseMessage) {
        HWND hWnd = msg->hwnd;
        int ms = (int)msg->wParam;
        TakeMessage(msg);
        StartFocusPulse(hWnd, ms);
        return;
    }
    if (msg->message == g_desktopRequestMessage) {
        HWND hWnd = msg->hwnd;
        int index = (int)msg->wParam;
        TakeMessage(msg);
        StartDesktopMove(hWnd, index);
        return;
    }

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

// Waits for a mod thread to end. Unloading while it still runs would crash
// the app, so there is no limit, but a slow wait goes in the log.
void WaitForModThread(HANDLE thread, PCWSTR name) {
    if (WaitForSingleObject(thread, 3000) == WAIT_TIMEOUT) {
        Wh_Log(L"Unload: still waiting for the %s thread", name);
        WaitForSingleObject(thread, INFINITE);
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

    WaitForModThread(thread, L"strip hook");
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
HWND g_maximizeWnd;
RECT g_rect;
UINT g_flags;
bool g_pending;
bool g_quit;
HANDLE g_event;
HANDLE g_thread;

void MaximizeAfterDrag(HWND wnd) {
    if (!CanActOnRootWindow(wnd)) return;
    if (IsZoomed(wnd)) {
        ShowWindowAsync(wnd, SW_RESTORE);
        return;
    }
    if (swm::g_animMs <= 0 || IsIconic(wnd) || IsHungAppWindow(wnd) ||
        !(GetWindowLongPtr(wnd, GWL_STYLE) & WS_MAXIMIZEBOX)) {
        ShowWindowAsync(wnd, SW_MAXIMIZE);
        return;
    }

    auto dpi = SetThreadDpiAwarenessContext(DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2);
    WINDOWPLACEMENT placement{sizeof(placement)};
    MONITORINFO monitor{sizeof(monitor)};
    // Wobble draws a stand-in while the real window is app-cloaked.
    DWORD cloaked = 0;
    ULONGLONG revealDeadline = GetTickCount64() + 325;
    while (SUCCEEDED(DwmGetWindowAttribute(wnd, DWMWA_CLOAKED, &cloaked,
                                            sizeof(cloaked))) &&
           cloaked == DWM_CLOAKED_APP && GetTickCount64() < revealDeadline) {
        Sleep(8);
    }
    if (GetWindowPlacement(wnd, &placement) &&
        GetMonitorInfo(MonitorFromWindow(wnd, MONITOR_DEFAULTTONEAREST), &monitor)) {
        snapCommander::AnimateRects({{wnd, monitor.rcWork}});
        // Commit the maximize with the original restore rectangle.
        placement.showCmd = SW_MAXIMIZE;
        if (!SetWindowPlacement(wnd, &placement)) ShowWindowAsync(wnd, SW_MAXIMIZE);
    } else {
        ShowWindowAsync(wnd, SW_MAXIMIZE);
    }
    if (dpi) SetThreadDpiAwarenessContext(dpi);
}

DWORD WINAPI ThreadProc(void*) {
    SetThreadPriority(GetCurrentThread(), THREAD_PRIORITY_ABOVE_NORMAL);
    while (WaitForSingleObject(g_event, INFINITE) == WAIT_OBJECT_0) {
        for (;;) {
            HWND wnd;
            RECT rc;
            UINT flags;
            bool maximize;
            {
                std::lock_guard<std::mutex> guard(g_lock);
                if (g_quit) return 0;
                maximize = !g_pending;
                if (maximize) {
                    wnd = std::exchange(g_maximizeWnd, nullptr);
                    if (!wnd) break;
                } else {
                    g_pending = false;
                    wnd = g_wnd;
                    rc = g_rect;
                    flags = g_flags;
                }
            }
            if (maximize) {
                MaximizeAfterDrag(wnd);
                continue;
            }
            if (IsHungAppWindow(wnd)) flags |= SWP_ASYNCWINDOWPOS;
            else flags &= ~SWP_ASYNCWINDOWPOS;
            SetWindowPos(wnd, nullptr, rc.left, rc.top, rc.right - rc.left,
                         rc.bottom - rc.top, flags);
        }
    }
    return 0;
}

bool StartIfNeeded() {
    if (g_thread) return true;
    g_event = CreateEvent(nullptr, FALSE, FALSE, nullptr);
    if (!g_event) return false;
    g_thread = CreateThread(nullptr, 0, ThreadProc, nullptr, 0, nullptr);
    if (!g_thread) {
        CloseHandle(g_event);
        g_event = nullptr;
    }
    return g_thread != nullptr;
}

bool QueueDragMaximize(HWND wnd) {
    std::lock_guard<std::mutex> guard(g_lock);
    if (g_quit || g_maximizeWnd || !StartIfNeeded()) return false;
    g_maximizeWnd = wnd;
    SetEvent(g_event);
    return true;
}

void Queue(HWND wnd, const RECT& rc, UINT flags) {
    std::lock_guard<std::mutex> guard(g_lock);
    if (!StartIfNeeded()) {
        SetWindowPos(wnd, nullptr, rc.left, rc.top, rc.right - rc.left,
                     rc.bottom - rc.top, flags | SWP_ASYNCWINDOWPOS);
        return;
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

void PostWobbleDragEnd() {
    if (g_llRootWnd && g_llDragSetUp && !IsSizeCommand(g_llCommand)) {
        PostMessage(g_llRootWnd, g_wobbleDragMessage, 0, 0);
    }
}

void ResetLowLevelDragState() {
    PostWobbleDragEnd();
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
    swm::g_handMovedWnd = hRootWnd;
    swm::g_handMovedTick = GetTickCount64();
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

    if (!IsSizeCommand(g_llCommand)) {
        PostMessage(g_llRootWnd, g_wobbleDragMessage, 1, 0);
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
    if (button && g_llRootWnd) swm::g_handMovedTick = GetTickCount64();  // The Alt drag's release.
    if (button && !down) {
        if (DWORD tiling = swm::g_tilingNudgeThread) {
            PostThreadMessageW(tiling, swm::kTilingNudgeMessage, 0, 0);
        }
    }
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
            if (PostWindowAction(hRootWnd, WindowAction::DragMaximize,
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
        if (swm::OnWalkKey(message, key)) return 1;
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

// The newest keyboard hook runs first. Apps like RustDesk hook the keyboard
// when their window comes to the front and keep the walk keys, so the hook is
// put back on top each time the front window changes, and twice more shortly
// after in case the app hooks a moment late. The new hook goes in before the
// old one comes out, so no key slips past.
UINT_PTR g_rehookTimer;
int g_rehooksLeft;
void RehookGlobalAlt() {
    HHOOK fresh = SetWindowsHookEx(WH_KEYBOARD_LL, GlobalAltProc, GetModuleHandle(nullptr), 0);
    if (!fresh) return;
    if (g_globalAltHook) UnhookWindowsHookEx(g_globalAltHook);
    g_globalAltHook = fresh;
}
void CALLBACK OnForegroundForHook(HWINEVENTHOOK, DWORD, HWND, LONG, LONG, DWORD, DWORD) {
    RehookGlobalAlt();
    g_rehooksLeft = 2;
    g_rehookTimer = SetTimer(nullptr, g_rehookTimer, 400, nullptr);
}

DWORD WINAPI LowLevelMouseHookThreadProc(void*) {
    MSG msg;
    PeekMessage(&msg, nullptr, WM_USER, WM_USER, PM_NOREMOVE);

    InstallLowLevelMouseHookOnThisThread();
    std::array<bool, kHotkeyActions.size()> registered{};
    std::array<bool, kHotkeyActions.size()> warned{};
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
            if (!registered[i] && !warned[i]) {
                warned[i] = true;
                Wh_Log(L"Shortcut %d (mods 0x%x, key 0x%x) is taken by another app or "
                       L"another key of this mod; trying again every 2 s",
                       (int)i, mods, (UINT)g_settings.hotkeys[i].key);
            }
        }
    };
    UINT_PTR retry = 0;
    HWINEVENTHOOK foregroundHook = nullptr;
    if (g_globalInput) {
        g_globalAltHook = SetWindowsHookEx(WH_KEYBOARD_LL, GlobalAltProc, GetModuleHandle(nullptr), 0);
        registerActions();
        swm::RegisterModeKeys();
        retry = SetTimer(nullptr, 0, 2000, nullptr);
        foregroundHook = SetWinEventHook(EVENT_SYSTEM_FOREGROUND, EVENT_SYSTEM_FOREGROUND,
                                         nullptr, OnForegroundForHook, 0, 0,
                                         WINEVENT_OUTOFCONTEXT | WINEVENT_SKIPOWNPROCESS);
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
                warned = {};
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
            if (msg.message == WM_TIMER && !msg.hwnd && g_rehookTimer &&
                msg.wParam == g_rehookTimer) {
                RehookGlobalAlt();
                if (--g_rehooksLeft <= 0) {
                    KillTimer(nullptr, g_rehookTimer);
                    g_rehookTimer = 0;
                }
                continue;
            }
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
    if (foregroundHook) UnhookWinEvent(foregroundHook);
    if (g_rehookTimer) KillTimer(nullptr, g_rehookTimer);
    g_rehookTimer = 0;
    if (g_globalAltHook) UnhookWindowsHookEx(g_globalAltHook);
    g_globalAltHook = nullptr;
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

    WaitForModThread(thread, L"mouse hook");
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
                    PostWobbleDragEnd();
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
        else if (token == L"[") *key = VK_OEM_4;
        else if (token == L"]") *key = VK_OEM_6;
        else if (token == L"-" || token == L"MINUS") *key = VK_OEM_MINUS;
        else if (token == L"PLUS" || token == L"=") *key = VK_OEM_PLUS;
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
    ChangeWindowMessageFilter(g_focusPulseMessage, MSGFLT_ADD);
    ChangeWindowMessageFilter(g_desktopRequestMessage, MSGFLT_ADD);

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
    ChangeWindowMessageFilter(g_focusPulseMessage, MSGFLT_REMOVE);
    ChangeWindowMessageFilter(g_desktopRequestMessage, MSGFLT_REMOVE);
    StopFocusPulses();

    {
        std::lock_guard<std::mutex> guard(g_lowLevelMouseHookMutex);

        if (g_lowLevelMouseHook) {
            UnhookWindowsHookEx(g_lowLevelMouseHook);
            g_lowLevelMouseHook = nullptr;
        }
    }

    RemoveWinKeyMaskHook();

    StopLowLevelMouseHookThread();

    for (int waits = 0; g_hookRefCount > 0; waits++) {
        if (waits == 15) Wh_Log(L"Unload: a hook callback is still running");
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
    LeftThird,
    CenterThird,
    RightThird,
    // Rules only, no key.
    Monitor1,
    Monitor2,
    Monitor3,
    Monitor4,
};

constexpr UINT MOD_F_ALT = 0x1;
constexpr UINT MOD_F_CTRL = 0x2;
constexpr UINT MOD_F_SHIFT = 0x4;
constexpr UINT MOD_F_WIN = 0x8;

constexpr int ACTION_COUNT = 21;

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
    Action::LeftThird,   Action::CenterThird,    Action::RightThird,
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
    L"shortcuts.keyLeftThird",      L"shortcuts.keyCenterThird",
    L"shortcuts.keyRightThird",
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
    bool floating = false;  // Never tiles, stays where the app puts it.
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
    if (name.size() >= 2 && name.size() <= 3 && name[0] == L'f') {
        int number = _wtoi(name.c_str() + 1);
        if (number >= 1 && number <= 24) return VK_F1 + number - 1;
    }
    static const std::pair<PCWSTR, UINT> named[] = {
        {L"space", VK_SPACE}, {L"tab", VK_TAB}, {L"esc", VK_ESCAPE}, {L"escape", VK_ESCAPE},
        {L"delete", VK_DELETE}, {L"del", VK_DELETE}, {L"insert", VK_INSERT}, {L"ins", VK_INSERT},
        {L"home", VK_HOME}, {L"end", VK_END}, {L"pageup", VK_PRIOR}, {L"pgup", VK_PRIOR},
        {L"pagedown", VK_NEXT}, {L"pgdn", VK_NEXT}};
    for (const auto& [n, vk] : named)
        if (name == n) return vk;
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
    if (v == L"left-third") return Action::LeftThird;
    if (v == L"center-third") return Action::CenterThird;
    if (v == L"right-third") return Action::RightThird;
    if (v.size() == 9 && v.rfind(L"monitor-", 0) == 0 && v[8] >= L'1' && v[8] <= L'4') {
        return (Action)((int)Action::Monitor1 + (v[8] - L'1'));
    }
    return Action::None;
}

// Bare lowercase executable name of the process that owns the window.
static std::wstring GetWindowProcessExeName(HWND hWnd) {
    DWORD pid = 0;
    GetWindowThreadProcessId(hWnd, &pid);
    if (!pid) {
        return L"";
    }

    std::wstring path = swm::ProcessImagePath(pid);
    return path.empty() ? std::wstring() : ToLower(BaseName(path));
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
            rule.floating = actionName == L"float";
            if (rule.action == Action::None && !rule.onTop && rule.alpha == 255 &&
                !rule.floating) {
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
        RECT from, to, margin, last;
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
                          wr.bottom - fr.bottom},
                         fr});
    }
    if (items.empty()) return;
    LARGE_INTEGER freq{}, start{}, now{}, last{};
    QueryPerformanceFrequency(&freq);
    // No more frames than the screen shows.
    LONGLONG period = freq.QuadPart / 60;
    DWM_TIMING_INFO timing{};
    timing.cbSize = sizeof(timing);
    if (SUCCEEDED(DwmGetCompositionTimingInfo(nullptr, &timing)) && timing.qpcRefreshPeriod) {
        period = (LONGLONG)timing.qpcRefreshPeriod;
    }
    QueryPerformanceCounter(&start);
    for (int frame = 0; frame < 240; frame++) {
        QueryPerformanceCounter(&now);
        if (frame && now.QuadPart - last.QuadPart < period * 8 / 10) {
            Sleep((DWORD)((period - (now.QuadPart - last.QuadPart)) * 1000 / freq.QuadPart));
            QueryPerformanceCounter(&now);
        }
        last = now;
        double t = (double)(now.QuadPart - start.QuadPart) * 1000.0 /
                   ((double)freq.QuadPart * ms);
        if (t >= 1.0) break;
        double u = 1.0 - t;
        double e = 1.0 - u * u * u;
        auto lerp = [e](LONG a, LONG b) { return (int)(a + (b - a) * e + 0.5); };
        for (Item& it : items) {
            int l = lerp(it.from.left, it.to.left);
            int tp = lerp(it.from.top, it.to.top);
            int r = lerp(it.from.right, it.to.right);
            int b = lerp(it.from.bottom, it.to.bottom);
            RECT step{l, tp, r, b};
            if (EqualRect(&step, &it.last)) continue;
            it.last = step;
            // No copied bits: apps like Explorer otherwise leave old copies
            // of their panes behind while they shrink. That already makes
            // the app repaint, so the full repaint waits for the landing.
            SetWindowPos(it.wnd, nullptr, l - it.margin.left, tp - it.margin.top,
                         r - l + it.margin.left + it.margin.right,
                         b - tp + it.margin.top + it.margin.bottom,
                         SWP_NOZORDER | SWP_NOOWNERZORDER | SWP_NOACTIVATE | SWP_NOCOPYBITS);
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

    if (action >= Action::Monitor1 && action <= Action::Monitor4) {
        swm::MoveToMonitorNumber(hWnd, (int)action - (int)Action::Monitor1);
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

    // A left or right third pressed again, on a window already a third wide
    // at that edge, makes it two thirds wide.
    const int third = fullWidth / 3;
    bool wide = false;
    if (action == Action::LeftThird || action == Action::RightThird) {
        RECT now{};
        GetVisibleRect(hWnd, &now);
        constexpr int kSlack = 48;  // Room for the gaps.
        bool atEdge = action == Action::LeftThird ? now.left - work.left <= kSlack
                                                  : work.right - now.right <= kSlack;
        wide = atEdge && std::abs((now.right - now.left) - third) <= kSlack &&
               now.top - work.top <= kSlack && work.bottom - now.bottom <= kSlack;
    }

    // The region of the work area this action targets, before gaps.
    RECT cell = work;
    switch (action) {
        case Action::LeftThird:
            cell = {work.left, work.top, work.left + third * (wide ? 2 : 1), work.bottom};
            break;
        case Action::CenterThird:
            cell = {work.left + third, work.top, work.right - third, work.bottom};
            break;
        case Action::RightThird:
            cell = {work.right - third * (wide ? 2 : 1), work.top, work.right, work.bottom};
            break;
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
        case Action::LeftThird:  ax = -1; ay = 0;  break;
        case Action::RightThird: ax = 1;  ay = 0;  break;
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
        bool places = rule.action != Action::None &&
                      (rule.action < Action::Monitor1 || rule.action > Action::Monitor4);
        if ((rule.ignore || rule.floating || places) && RuleMatches(rule, hWnd, facts)) {
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
                    Action action = g_actionByIndex[idx];
                    bool third = action == Action::LeftThird ||
                                 action == Action::CenterThird ||
                                 action == Action::RightThird;
                    // A tiled window rearranges the tiles instead of leaving them.
                    if (region >= 0 && root && swm::IsTiledWindow(root)) {
                        swm::PostTileRegion(region);
                    } else if (third && root && swm::IsTiledWindow(root)) {
                        // Thirds don't fit the tiles; a tiled window stays put.
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
  $name: Hold these for the snap keys
  $description: >-
    Added to every snap key below, so each snap key is just the key itself.
    Choose None to type the whole shortcut into each one.
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
        Type a key such as "q" or "left". The keys held above are added on
        top. Leave empty to turn it off. Same for every key below.
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
      $name: Maximize with a margin
      $description: Fills the screen but keeps the gaps around the window.
    - keyNextDisplay: "]"
      $name: Send to the next monitor
    - keyPrevDisplay: "["
      $name: Send to the previous monitor
    - keySmaller: "-"
      $name: Shrink by one step
      $description: Shrinks the window around its middle.
    - keyLarger: plus
      $name: Grow by one step
      $description: >-
        Grows the window around its middle. Write this key as "plus" or "=",
        because "+" joins the keys of a shortcut.
    - keyRestore: z
      $name: Undo snap
      $description: Puts the window back where it was before the first snap.
    - keyLeftThird: ""
      $name: Left third
      $description: >-
        Press again for the left two thirds. Empty means off. Tiled windows
        don't take thirds.
    - keyCenterThird: ""
      $name: Middle third
      $description: The middle third of the screen. Empty means off.
    - keyRightThird: ""
      $name: Right third
      $description: Press again for the right two thirds.
  $name: Snap keys
  $description: Keys that snap the active window to a part of the screen.
- hotkeyMaximize: ''
  $name: Maximize or restore
  $description: >-
    Type the whole shortcut, such as "Alt+X" or "Ctrl+Alt+X". It needs at
    least one of Alt, Ctrl, Shift or Win. Leave empty to turn it off. Same for
    every shortcut below. Off by default, because Alt+F fills the screen.
- hotkeyMinimize: Alt+M
  $name: Minimize
- hotkeyRestoreMinimized: Alt+Shift+M
  $name: Restore minimized window
  $description: >-
    Brings back the window you minimized last, at its old size and place.
    Press again for the one before it.
- hotkeyMRUUp: Alt+PageUp
  $name: Go back up the hidden windows
  $description: >-
    Walks the same windows as the key below, the other way round.
- hotkeyMRUDown: Alt+PageDown
  $name: Bring up a hidden window
  $description: >-
    Brings up the window hidden behind the ones in front on this monitor, even
    one behind two tiles side by side. Press again for the one behind that,
    and once more to come back to where you started. Windows in plain view
    are left to the focus keys.
- hotkeyClose: Alt+Shift+Q
  $name: Close
- hotkeyMenu: ''
  $name: Open the window menu
- hotkeyTopmost: ''
  $name: Toggle always on top
- hotkeyLower: ''
  $name: Send to the back
- hotkeyCenter: ''
  $name: Center the window
  $description: Moves the window to the middle of its screen and keeps its size.
- hotkeySideSnap: ''
  $name: Snap to the nearest side
- hotkeyPause: Alt+Shift+P
  $name: Pause the window manager
  $description: >-
    Turns every drag, shortcut and rule off until you press it again. Handy in
    games and drawing apps that need Alt.
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
  $name: Flip the split
  $description: >-
    The next window opens below instead of beside, or back again. Turns the
    active window's group from side by side to stacked. Try Alt+V.
- hotkeyFill: Alt+F
  $name: Fill the screen (tiled window)
  $description: >-
    The window fills the screen but keeps the gaps around it, like GlazeWM's
    fullscreen. Press again to put it back in its tile or old spot.
- hotkeyBorderless: Ctrl+Shift+F
  $name: Fullscreen without a title bar
  $description: >-
    No title bar or borders, like ShareX's "Make active window borderless", and
    the window covers the whole monitor, taskbar included. Press again to give
    the window its frame and size back. If another app already uses the
    shortcut, it starts working once that app lets go of it.
- hotkeyHideTitleBar: Ctrl+Win+Alt+T
  $name: Hide the title bar
  $description: >-
    The active window loses its title bar, like GlazeWM's hide title bar, but
    keeps its size, place and resize edges. Press again to bring the title bar
    back. Apps that draw their own title bar may not change.
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
  $name: Send to monitor 1
  $description: >-
    A tiled window takes a tile there; a floating one keeps its size and spot
    on the new screen.
- hotkeySendMonitor2: Alt+Shift+2
  $name: Send to monitor 2
- hotkeySendMonitor3: Alt+Shift+3
  $name: Send to monitor 3
- hotkeySendMonitor4: Alt+Shift+4
  $name: Send to monitor 4
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
- desktopSend: send
  $name: Send a window to a desktop
  $description: >-
    Add Win to a desktop key, such as Ctrl+Win+Alt+Shift+2, to send the active
    window to that desktop. Only desktops that already exist.
  $options:
    - "off": "Off"
    - send: Send the window
    - follow: Send the window and go with it
- hotkeyRetile: Alt+Shift+E
  $name: Even out and retile
  $description: >-
    Makes every tile on this monitor the same size again and tiles the windows
    that dropped out.
- hotkeyFocusLast: Alt+Shift+L
  $name: Focus the last window
  $description: Goes back to the window you used before. Press again to come back.
- tiling:
    - enabled: true
      $name: Tile new windows
      $description: >-
        New app windows fill the screen side by side, like GlazeWM. A new one
        takes half of the biggest tile. Over a full-screen game it opens in
        the middle and tiles once the game is gone. Dialogs, small windows and
        windows on top stay floating.
    - existing: true
      $name: Tile windows already open
      $description: When on, the windows already open are tiled when the mod starts.
    - innerGap: 20
      $name: Space between tiled windows (px)
      $description: >-
        Always pixels. The space at the screen edges comes from the screen-edge
        gaps. 0 to 100 (Suggested: 20).
    - resizeStep: 5
      $name: "Tile grow keys: step (%)"
      $description: >-
        How far each press of a grow key moves the edge, as a share of the
        screen. 1 to 20 (Suggested: 5).
    - singleNoGaps: false
      $name: No gaps around a window alone
      $description: A window alone on its monitor fills it with no gaps.
    - offMonitors: ""
      $name: Monitors that never tile
      $description: >-
        Monitor numbers, such as "3" or "2, 4", counted like the monitor keys.
        Windows there float.
    - floatApps: [""]
      $name: Apps that never tile
      $description: >-
        One app name per entry, such as "steam" or "obs64". These always open
        floating. Apps with a placement rule never tile either.
  $name: Tiling
  $description: Which windows tile, and the space between them.
- resizeMode:
    - step: 2
      $name: "Keyboard resize mode: step (%)"
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
      $name: Gap at the top screen edge
      $description: "Space between a snapped window and the top of the screen, in the gap unit below. 0 to 100 (Suggested: 0)."
    - gapBottom: 0
      $name: Gap at the bottom screen edge
      $description: "Space between a snapped window and the bottom of the screen, in the gap unit below. 0 to 100 (Suggested: 0)."
    - gapLeft: 0
      $name: Gap at the left screen edge
      $description: "Space between a snapped window and the left of the screen, in the gap unit below. 0 to 100 (Suggested: 0)."
    - gapRight: 0
      $name: Gap at the right screen edge
      $description: "Space between a snapped window and the right of the screen, in the gap unit below. 0 to 100 (Suggested: 0)."
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
        scale, so they look the same size on every screen. Only used with
        Pixels.
      $options:
        - exact: Exact pixels
        - dpi: Scale with display
    - gapMode: even
      $name: Gap style for snapped windows
      $description: >-
        Even keeps the gap between two windows the same as the gap at the screen
        edge. Full puts the whole gap on every side, so it doubles between
        windows. Screen edges only lets side-by-side windows touch.
      $options:
        - even: Even
        - full: Full on every side
        - screen: Screen edges only
    - almostMaximizeGap: ""
      $name: Gap for Maximize with a margin
      $description: >-
        The same gap on all four sides. 0 to 200. Leave empty to use the
        screen-edge gaps.
    - centerWidth: ""
      $name: Width after Center (px)
      $description: >-
        Used by the Center app rule. 100 up to the screen width. Leave empty to
        keep the window's width.
    - centerHeight: ""
      $name: Height after Center (px)
      $description: >-
        Used by the Center app rule. 100 up to the screen height. Leave empty
        to keep the window's height.
    - resizeStep: 5
      $name: "Smaller and larger keys: step (%)"
      $description: >-
        How much Shrink by one step and Grow by one step change the window on
        each press. 1 to 20 (Suggested: 5).
  $name: Gaps and sizes
  $description: Gaps around snapped windows and the size for Center.
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
  $name: Treat the main monitor as the middle
  $description: >-
    When on, Down sends the window to the main monitor and the other arrows to
    the monitor above, left or right of it, wherever the window is now. When
    off, the arrows go from the window's current monitor.
- targetUp: -1
  $name: Up arrow goes to monitor
  $description: >-
    -1 picks the nearest monitor above. 0 is the first monitor Windows
    lists, 1 the second, and so on. -1 to 9 (Suggested: -1).
- targetDown: -1
  $name: Down arrow goes to monitor
  $description: >-
    -1 picks the nearest monitor below. 0 is the first monitor Windows
    lists, 1 the second, and so on. -1 to 9 (Suggested: -1).
- targetLeft: -1
  $name: Left arrow goes to monitor
  $description: >-
    -1 picks the nearest monitor to the left. 0 is the first monitor Windows
    lists, 1 the second, and so on. -1 to 9 (Suggested: -1).
- targetRight: -1
  $name: Right arrow goes to monitor
  $description: >-
    -1 picks the nearest monitor to the right. 0 is the first monitor Windows
    lists, 1 the second, and so on. -1 to 9 (Suggested: -1).
- keepSize: true
  $name: Keep size when sent to another monitor
  $description: When off, the window grows or shrinks to match the new monitor.
- centerOnMove: false
  $name: Center when sent to another monitor
  $description: When off, the window keeps the same spot relative to the screen.
- cursorFollowsWindow: false
  $name: Move the pointer with a sent window
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
- agentWindows:
    - enabled: true
      $name: Keep agent windows out of the way
      $description: >-
        Windows that coding agents open, and everything they start, never take
        the keyboard, the mouse or the window in front. They open on a monitor
        you are not using. Clicking one still makes it active as normal.
    - screen: side
      $name: Where agent windows open
      $description: >-
        Never the monitor with the window you are using or the mouse pointer.
      $options:
        - side: The biggest other monitor
        - left: The leftmost other monitor
        - right: The rightmost other monitor
        - top: The highest other monitor
        - none: Where the app puts them
    - apps: claude.exe, codex.exe, opencode.exe, gemini.exe, grok.exe
      $name: Agent programs
      $description: >-
        Everything these programs start counts as an agent window. Separate
        names with commas. Agents T3 Code runs through node also count.
  $name: Agent windows
  $description: Windows your coding agents open stay out of your way.
- effects:
    - animation: 180
      $name: Animation length (ms)
      $description: >-
        How long windows take to glide into place when they tile, float, fill,
        snap or go borderless. 0 turns it off. 0 to 400 (Suggested: 180).
    - focusAnimation: ring
      $name: Focus animation
      $description: >-
        What the window you jump to with the focus keys (Alt+arrows, Alt+1 to
        4, Alt+Page Up or Down) does. Ring: a blue to mauve outline closes in
        on its edge and fades, and the window itself stays still. Zoom in: the
        window grows in from slightly smaller, like Alt+Tab.
      $options:
        - ring: Ring
        - zoom: Zoom in
        - "off": "Off"
    - inactiveOpacity: 100
      $name: Fade windows you are not using (%)
      $description: >-
        Makes every window except the active one see-through. 100 turns this
        off. 30 to 100 (Suggested: 92).
    - statusPopup: show
      $name: Show a popup when pausing
      $description: >-
        A small popup when you pause or resume, and while keyboard resize is
        on.
      $options:
        - show: Show
        - hide: Hide
  $name: Animation and fade
  $description: >-
    Window borders come from Seamless Borders and corners from Custom Window
    Corner Radius, so they are not repeated here.
- rules:
    - - executable_names: ""
        $name: App file names
        $description: >-
          One or more app file names, separate with semicolons, such as
          "notepad; calc.exe". Upper or lower case both work and ".exe" is optional. Use
          * for every app. Leave empty to match by title or class only.
      - window_title: ""
        $name: Window title
        $description: Text in the window's title. Leave empty to match any title.
      - window_class: ""
        $name: Window class (advanced)
        $description: Leave empty to match any class.
      - match_mode: contains
        $name: Title and class match
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
          - left-third: Left third
          - center-third: Middle third
          - right-third: Right third
          - monitor-1: Monitor 1
          - monitor-2: Monitor 2
          - monitor-3: Monitor 3
          - monitor-4: Monitor 4
          - float: Never tile, leave it floating
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
          - open: On open, and for windows already open
          - new: On open only
          - title: On open and when the title changes
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
- settingsGlass: true
  $name: Blurred settings window
  $description: On, the settings window is see-through glass with Windows acrylic behind it. Off, it is solid. Applies when you save.
- nativeSettingsTitleBar: false
  $name: Native Windows title bar
  $description: Use the Windows title bar and window buttons for this settings window. Applies when you save.
- settingsTrayIcon: true
  $name: Tray icon
  $description: A window manager icon in the system tray. Click it to open these settings, right-click it for a menu.
*/
// ==/WindhawkModSettings==


// One elevated tool owns global input. Per-app hooks retain Explorer's title-strip behavior.
#include <sddl.h>
#include <windhawk_tool_mod.h>

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


static bool g_packDragInited;
static HANDLE g_globalMutex;


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
constexpr UINT kFocusRingMessage = WM_APP + 312;
constexpr WCHAR kFocusRingClassName[] = L"SeamlessWM_FocusRing";

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
    L"hotkeyHideTitleBar",
    L"hotkeyRetile",    L"hotkeyFocusLast",
};
constexpr int kFirstMonitorKey = 18;
constexpr int kFirstSendMonitorKey = 22;
constexpr int kFirstDesktopKey = 26;
constexpr int kDesktopKeyCount = 9;
constexpr int kRetileKey = 39;
constexpr int kFocusLastKey = 40;
// The desktop keys with Win added send the active window there.
constexpr int kSendDesktopBase = 0x6180;
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
    uint32_t offMonitors = 0;  // Bit n: monitor n+1 never tiles.
    bool singleNoGaps = false;
    int desktopSend = 0;       // 0 off, 1 send, 2 send and follow.
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
    opacity = std::clamp(opacity > 0 ? opacity : 100, 30, 100);
    s.inactiveAlpha = (BYTE)((opacity * 255 + 50) / 100);
    s.popup = text(L"effects.statusPopup") != L"hide";

    s.tiling = Wh_GetIntSetting(L"tiling.enabled") != 0;
    s.tileExisting = Wh_GetIntSetting(L"tiling.existing") != 0;
    s.innerGap = std::clamp(Wh_GetIntSetting(L"tiling.innerGap"), 0, 100);
    s.singleNoGaps = Wh_GetIntSetting(L"tiling.singleNoGaps") != 0;
    {
        int number = 0;
        for (WCHAR c : text(L"tiling.offMonitors") + L" ") {
            if (c >= L'0' && c <= L'9') {
                number = std::min(number * 10 + (c - L'0'), 99);
            } else {
                if (number >= 1 && number <= 32) s.offMonitors |= 1u << (number - 1);
                number = 0;
            }
        }
    }
    {
        std::wstring send = text(L"desktopSend");
        s.desktopSend = send == L"follow" ? 2 : send == L"send" ? 1 : 0;
    }
    g_animMs = std::clamp(Wh_GetIntSetting(L"effects.animation"), 0, 400);
    {
        std::wstring mode = text(L"effects.focusAnimation");
        g_focusRing = mode != L"zoom";
        g_focusAnimMs = mode == L"off" ? 0 : mode == L"zoom" ? 200 : 450;
    }
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

std::vector<moveToMonitor::MonitorInfo> OrderedMonitors();

// A rule's "Monitor N": the window keeps its size and spot on that screen.
void MoveToMonitorNumber(HWND hWnd, int index) {
    auto monitors = OrderedMonitors();
    if (index < 0 || index >= (int)monitors.size()) return;
    HMONITOR here = MonitorFromWindow(hWnd, MONITOR_DEFAULTTONEAREST);
    if (here == monitors[index].hMon) return;
    for (const auto& src : monitors) {
        if (src.hMon == here) {
            moveToMonitor::MoveWindowToMonitor(hWnd, src, monitors[index]);
            return;
        }
    }
}

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

// The focus ring around a window the focus keys just moved to.
void ShowFocusRing(HWND hWnd, int ms) {
    if (g_osdThreadId) {
        PostThreadMessageW(g_osdThreadId, kFocusRingMessage, (WPARAM)hWnd, ms);
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

//////// focus ring ////////
// A gradient outline that starts a little outside the window, closes in on
// its edge, holds a moment and fades. It lands where Seamless Borders draws
// the active border, so the hand-off is seamless when that mod is on. Only
// this click-through window moves; the app is never hidden or redrawn.
namespace ring {

HWND g_window;
HWND g_target;
HDC g_dc;
HBITMAP g_bitmap;
HGDIOBJ g_oldBitmap;
ID2D1DCRenderTarget* g_rt;
ID2D1LinearGradientBrush* g_brush;
RECT g_frame;  // the target's visible frame when last laid out
POINT g_pos;
SIZE g_size;
float g_scale = 1.0f;
float g_radius = 8.0f;  // the window's corner radius, physical pixels
bool g_inset;           // maximized: drawn just inside the screen edge
LONGLONG g_start, g_freq;
int g_ms;
float g_drawnOffset = -1.0f;

constexpr float kTravel = 14.0f;  // DIPs outside the edge where it starts
constexpr float kWidth = 2.0f;
constexpr float kGlow = 7.0f;

void FreeSurface() {
    if (g_brush) {
        g_brush->Release();
        g_brush = nullptr;
    }
    if (g_rt) {
        g_rt->Release();
        g_rt = nullptr;
    }
    if (g_dc) {
        SelectObject(g_dc, g_oldBitmap);
        DeleteDC(g_dc);
        g_dc = nullptr;
    }
    if (g_bitmap) {
        DeleteObject(g_bitmap);
        g_bitmap = nullptr;
    }
}

void Stop() {
    g_target = nullptr;
    if (g_window) {
        ShowWindow(g_window, SW_HIDE);
    }
    FreeSurface();
}

bool Active() {
    return g_target != nullptr;
}

// The corner radius windows really have: the Custom Corner Radius mod's value
// when it is on, else Windows' own 8.
float CornerRadiusDip() {
    HKEY key;
    DWORD radius = 8;
    if (RegOpenKeyExW(HKEY_LOCAL_MACHINE,
                      L"SOFTWARE\\Windhawk\\Engine\\Mods\\custom-corner-radius", 0,
                      KEY_READ, &key) == ERROR_SUCCESS) {
        DWORD disabled = 0, value = 0, size = sizeof(DWORD);
        RegGetValueW(key, nullptr, L"Disabled", RRF_RT_REG_DWORD, nullptr, &disabled,
                     &size);
        size = sizeof(DWORD);
        if (!disabled &&
            RegGetValueW(key, L"Settings", L"radius", RRF_RT_REG_DWORD, nullptr, &value,
                         &size) == ERROR_SUCCESS &&
            value <= 64) {
            radius = value;
        }
        RegCloseKey(key);
    }
    return (float)radius;
}

bool ReadFrame(RECT* frame) {
    return SUCCEEDED(DwmGetWindowAttribute(g_target, DWMWA_EXTENDED_FRAME_BOUNDS, frame,
                                           sizeof(*frame))) &&
           frame->right > frame->left && frame->bottom > frame->top;
}

bool EnsureWindow() {
    if (g_window) {
        return true;
    }
    WNDCLASSEXW wc{sizeof(wc)};
    wc.lpfnWndProc = DefWindowProcW;
    wc.hInstance = GetModuleHandleW(nullptr);
    wc.lpszClassName = kFocusRingClassName;
    RegisterClassExW(&wc);
    g_window = CreateWindowExW(
        WS_EX_TOOLWINDOW | WS_EX_NOACTIVATE | WS_EX_TRANSPARENT | WS_EX_LAYERED,
        kFocusRingClassName, L"", WS_POPUP, 0, 0, 0, 0, nullptr, nullptr, wc.hInstance,
        nullptr);
    return g_window != nullptr;
}

// Sizes the surface to the frame plus room for the travel and the glow.
bool Layout(const RECT& frame) {
    FreeSurface();
    g_frame = frame;
    UINT dpi = GetDpiForWindow(g_target);
    g_scale = (dpi ? dpi : 96) / 96.0f;
    g_inset = IsZoomed(g_target) != FALSE;
    LONG pad = g_inset ? 0 : (LONG)std::ceil((kTravel + kGlow + 2.0f) * g_scale);
    g_pos = {frame.left - pad, frame.top - pad};
    g_size = {frame.right - frame.left + 2 * pad, frame.bottom - frame.top + 2 * pad};

    BITMAPINFO bi{};
    bi.bmiHeader.biSize = sizeof(bi.bmiHeader);
    bi.bmiHeader.biWidth = g_size.cx;
    bi.bmiHeader.biHeight = -g_size.cy;
    bi.bmiHeader.biPlanes = 1;
    bi.bmiHeader.biBitCount = 32;
    bi.bmiHeader.biCompression = BI_RGB;
    void* bits = nullptr;
    HDC screen = GetDC(nullptr);
    g_dc = CreateCompatibleDC(screen);
    g_bitmap = CreateDIBSection(screen, &bi, DIB_RGB_COLORS, &bits, nullptr, 0);
    ReleaseDC(nullptr, screen);
    if (!g_dc || !g_bitmap) {
        return false;
    }
    g_oldBitmap = SelectObject(g_dc, g_bitmap);

    D2D1_RENDER_TARGET_PROPERTIES props = D2D1::RenderTargetProperties(
        D2D1_RENDER_TARGET_TYPE_DEFAULT,
        D2D1::PixelFormat(DXGI_FORMAT_B8G8R8A8_UNORM, D2D1_ALPHA_MODE_PREMULTIPLIED),
        96.0f, 96.0f);
    RECT bounds{0, 0, g_size.cx, g_size.cy};
    if (FAILED(g_d2d->CreateDCRenderTarget(&props, &g_rt)) ||
        FAILED(g_rt->BindDC(g_dc, &bounds))) {
        return false;
    }
    D2D1_GRADIENT_STOP stops[2] = {{0.0f, D2D1::ColorF(0x89b4fa)},
                                   {1.0f, D2D1::ColorF(0xcba6f7)}};
    ID2D1GradientStopCollection* collection = nullptr;
    if (FAILED(g_rt->CreateGradientStopCollection(stops, 2, &collection))) {
        return false;
    }
    // 45 degrees across the window, blue top left to mauve bottom right.
    float w = (float)g_size.cx, h = (float)g_size.cy, d = (w + h) / 4.0f;
    HRESULT hr = g_rt->CreateLinearGradientBrush(
        D2D1::LinearGradientBrushProperties(D2D1::Point2F(w / 2 - d, h / 2 - d),
                                            D2D1::Point2F(w / 2 + d, h / 2 + d)),
        collection, &g_brush);
    collection->Release();
    g_drawnOffset = -1.0f;
    return SUCCEEDED(hr);
}

// Draws the ring `offset` DIPs out from the edge (in from it when inset).
bool Draw(float offset) {
    const float s = g_scale;
    // A rounded rect `c` pixels outside the frame edge (negative: inside),
    // its radius kept concentric with the window's own corners.
    auto shape = [&](float c) {
        float left = (float)(g_frame.left - g_pos.x) - c;
        float top = (float)(g_frame.top - g_pos.y) - c;
        float right = (float)(g_frame.right - g_pos.x) + c;
        float bottom = (float)(g_frame.bottom - g_pos.y) + c;
        float r = g_inset ? 0.0f : std::max(0.0f, g_radius + c);
        return D2D1::RoundedRect(D2D1::RectF(left, top, right, bottom), r, r);
    };
    const float dir = g_inset ? -1.0f : 1.0f;
    const float o = offset * s;
    g_rt->BeginDraw();
    g_rt->Clear(D2D1::ColorF(0, 0.0f));
    // A soft glow just outside the line. The line spans 1 px either side of
    // the edge, where the active border sits; inset, it lies just inside.
    g_brush->SetOpacity(0.08f);
    g_rt->DrawRoundedRectangle(shape(dir * (o + kGlow * s / 2)), g_brush, kGlow * s);
    g_brush->SetOpacity(0.14f);
    g_rt->DrawRoundedRectangle(shape(dir * (o + kGlow * s / 4)), g_brush, kGlow * s / 2);
    g_brush->SetOpacity(1.0f);
    g_rt->DrawRoundedRectangle(shape(g_inset ? -(o + kWidth * s / 2) : o), g_brush,
                               kWidth * s);
    return SUCCEEDED(g_rt->EndDraw());
}

void Present(BYTE alpha, bool content) {
    BLENDFUNCTION blend{AC_SRC_OVER, 0, alpha, AC_SRC_ALPHA};
    if (!content) {
        // Same picture at a new strength: nothing to copy.
        UpdateLayeredWindow(g_window, nullptr, nullptr, nullptr, nullptr, nullptr, 0,
                            &blend, ULW_ALPHA);
        return;
    }
    HDC screen = GetDC(nullptr);
    POINT source{};
    UpdateLayeredWindow(g_window, screen, &g_pos, &g_size, g_dc, &source, 0, &blend,
                        ULW_ALPHA);
    ReleaseDC(nullptr, screen);
}

void Start(HWND target, int ms) {
    Stop();
    if (!target || !IsWindow(target) || !g_d2d || !EnsureWindow()) {
        return;
    }
    g_target = target;
    g_ms = std::clamp(ms, 150, 2000);
    UINT dpi = GetDpiForWindow(target);
    g_radius = CornerRadiusDip() * (dpi ? dpi : 96) / 96.0f;
    RECT frame;
    if (!ReadFrame(&frame) || !Layout(frame) || !Draw(kTravel)) {
        Stop();
        return;
    }
    g_drawnOffset = kTravel;
    Present(0, true);
    QueryPerformanceFrequency((LARGE_INTEGER*)&g_freq);
    QueryPerformanceCounter((LARGE_INTEGER*)&g_start);
    // Just above the window it marks, so whatever is in front of that window
    // (a topmost toolbar, a menu) stays in front of the ring too.
    bool topmost = (GetWindowLongPtrW(target, GWL_EXSTYLE) & WS_EX_TOPMOST) != 0;
    SetWindowPos(g_window, topmost ? HWND_TOPMOST : HWND_NOTOPMOST, 0, 0, 0, 0,
                 SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
    SetWindowPos(g_window, HWND_TOP, 0, 0, 0, 0,
                 SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE | SWP_SHOWWINDOW);
}

// One frame: closes in over the first 45%, holds, fades over the last 40%.
void Step() {
    if (!g_target) {
        return;
    }
    LONGLONG now;
    QueryPerformanceCounter((LARGE_INTEGER*)&now);
    float t = (float)((now - g_start) * 1000.0 / g_freq) / g_ms;
    RECT frame;
    if (t >= 1.0f || !IsWindowVisible(g_target) || IsIconic(g_target) ||
        !ReadFrame(&frame)) {
        Stop();
        return;
    }
    bool content = false;
    if (!EqualRect(&frame, &g_frame)) {
        // The window is still gliding into place: follow it.
        if (!Layout(frame)) {
            Stop();
            return;
        }
        content = true;
    }
    float in = std::min(t / 0.45f, 1.0f);
    float ease = 1.0f - (1.0f - in) * (1.0f - in) * (1.0f - in);
    float offset = kTravel * (1.0f - ease);
    float alpha = ease;
    if (t > 0.6f) {
        float out = (t - 0.6f) / 0.4f;
        alpha = 1.0f - out * out * (3.0f - 2.0f * out);
    }
    if (content || std::fabs(offset - g_drawnOffset) > 0.05f) {
        if (!Draw(offset)) {
            Stop();
            return;
        }
        g_drawnOffset = offset;
        content = true;
    }
    Present((BYTE)std::lround(alpha * 255.0f), content);
}

void Destroy() {
    Stop();
    if (g_window) {
        DestroyWindow(g_window);
        g_window = nullptr;
    }
    UnregisterClassW(kFocusRingClassName, GetModuleHandleW(nullptr));
}

}  // namespace ring

// Windows Animations plays its switch zoom (the window vanishes, then fades
// in) on any focus change made while Alt is held, so our Alt hotkeys got it
// too. It asks a window switcher's note window first: a fresh note that
// names no source means "not a switch", and it plays nothing. Real Alt+Tab
// leaves no note, so it keeps its zoom.
namespace switchNote {

constexpr PCWSTR kClass = L"WindhawkSWS_Switcher";
constexpr PCWSTR kTitle = L"WindhawkSWS_InputEndpoint";
constexpr PCWSTR kVersion = L"WindhawkSWS.SelectionProtocolV1";
constexpr PCWSTR kToken = L"WindhawkSWS.SelectionTokenV1";
constexpr PCWSTR kTick = L"WindhawkSWS.SelectionTickV1";
std::atomic<HWND> g_endpoint{nullptr};
std::atomic<DWORD> g_token{0};

void Create() {
    // A real switcher already owns the note window: leave it alone.
    if (FindWindowW(kClass, kTitle)) return;
    WNDCLASSEXW wc{sizeof(wc)};
    wc.lpfnWndProc = DefWindowProcW;
    wc.hInstance = GetModuleHandleW(nullptr);
    wc.lpszClassName = kClass;
    RegisterClassExW(&wc);
    HWND endpoint = CreateWindowExW(WS_EX_TOOLWINDOW | WS_EX_NOACTIVATE, kClass, kTitle,
                                    WS_POPUP, 0, 0, 0, 0, nullptr, nullptr, wc.hInstance,
                                    nullptr);
    if (!endpoint) return;
    SetPropW(endpoint, kVersion, (HANDLE)(ULONG_PTR)1);
    g_endpoint = endpoint;
}

// Called just before one of our focus moves.
void Mark() {
    HWND endpoint = g_endpoint;
    if (!endpoint) return;
    DWORD token = ++g_token;
    if (!token) token = ++g_token;
    // Tick before token: the reader checks the token first.
    SetPropW(endpoint, kTick, (HANDLE)(ULONG_PTR)GetTickCount());
    SetPropW(endpoint, kToken, (HANDLE)(ULONG_PTR)token);
}

void Destroy() {
    HWND endpoint = g_endpoint.exchange(nullptr);
    if (endpoint) {
        for (PCWSTR prop : {kVersion, kToken, kTick}) RemovePropW(endpoint, prop);
        DestroyWindow(endpoint);
    }
    UnregisterClassW(kClass, GetModuleHandleW(nullptr));
}

}  // namespace switchNote

DWORD WINAPI ThreadProc(LPVOID ready) {
    SetThreadDpiAwarenessContext(DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2);
    MSG msg;
    PeekMessageW(&msg, nullptr, WM_USER, WM_USER, PM_NOREMOVE);
    switchNote::Create();
    SetEvent((HANDLE)ready);
    if (!g_d2d) D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &g_d2d);
    auto handle = [](const MSG& msg) {
        if (!msg.hwnd && msg.message == kOsdShowMessage) {
            Show((OsdState)msg.wParam);
        } else if (!msg.hwnd && msg.message == kOsdHideMessage) {
            // Only the resize popup waits to be hidden; the others time out.
            if (g_sticky) {
                g_sticky = false;
                Hide();
            }
        } else if (!msg.hwnd && msg.message == kFocusRingMessage) {
            ring::Start((HWND)msg.wParam, (int)msg.lParam);
        } else {
            DispatchMessageW(&msg);
        }
    };
    for (bool running = true; running;) {
        if (ring::Active()) {
            // Animating: one frame per screen refresh, messages in between.
            while (PeekMessageW(&msg, nullptr, 0, 0, PM_REMOVE)) {
                if (msg.message == WM_QUIT) {
                    running = false;
                    break;
                }
                handle(msg);
            }
            if (!running) break;
            ring::Step();
            if (FAILED(DwmFlush())) Sleep(8);
            continue;
        }
        if (GetMessageW(&msg, nullptr, 0, 0) <= 0) break;
        handle(msg);
    }
    switchNote::Destroy();
    ring::Destroy();
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
    kTileSendMonitor, kTileCycleFocus, kTileRestoreMinimized, kTileHideTitle, kTileRetile
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
    ULONGLONG fightTick = 0;  // The last time the app refused its place.
    RECT slot{};           // The whole tile, before the insets.
    int inset[4]{};        // Edges pulled in by the grow keys, per Direction.
    bool fill = false;     // Fills the screen inside the gaps (Alt+F).
    bool hidden = false;   // Maximized: out of the layout until restored.
    int minW = 0, minH = 0;  // The smallest size the app agreed to, once it refused one.
};

// One tree per monitor and virtual desktop. Kept until the thread stops, so
// a pointer to one stays good.
struct Workspace {
    HMONITOR monitor = nullptr;
    std::wstring device;  // The display's name, which outlives its handle.
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
std::unordered_set<HWND> g_noTile;            // Checked and never tile; until hidden.
std::unordered_map<HWND, std::wstring> g_homes;  // Display each one left when it went away.
int g_monitorCount = 0;
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
std::unordered_map<HWND, LONG_PTR> g_noTitle;  // Title bar hidden; the style to give back.

std::vector<Event> g_events;
IVirtualDesktopManager* g_desktops;
GUID g_currentDesktop{};
std::array<HWINEVENTHOOK, 5> g_hooks{};
UINT_PTR g_pendingTimer;
UINT_PTR g_enforceTimer;
UINT g_enforceMs;
ULONGLONG g_enforceFastUntil;  // Quick checks until then, after anything happens.
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
    // The smallest size belongs to the app, so it moves with the window.
    std::swap(a->minW, b->minW);
    std::swap(a->minH, b->minH);
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
    MONITORINFOEXW mi{};
    mi.cbSize = sizeof(mi);
    if (GetMonitorInfoW(monitor, &mi)) {
        ws->device = mi.szDevice;
        // A portrait monitor stacks windows; a wide one puts them side by side.
        ws->root->vertical = Height(mi.rcWork) > Width(mi.rcWork);
    }
    g_workspaces.push_back(std::move(ws));
    return g_workspaces.back().get();
}

// The smallest a tile gets: 150 px at 100% scale.
int MinTile(HMONITOR monitor) {
    UINT dpiX = 96, dpiY = 96;
    if (FAILED(GetDpiForMonitor(monitor, MDT_EFFECTIVE_DPI, &dpiX, &dpiY)) || !dpiX) dpiX = 96;
    return MulDiv(150, dpiX, 96);
}
int g_minTile = 150;  // For the layout pass under way; ComputeLayout sets it.

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

// Asks the app for its smallest size before its first placement, so the
// layout makes room for it the first time instead of after it refuses a tile.
// Only sizes the app sets itself count: the struct starts zeroed.
void QueryMinSize(Node* leaf) {
    MINMAXINFO mmi{};
    DWORD_PTR result = 0;
    if (!SendMessageTimeoutW(leaf->hWnd, WM_GETMINMAXINFO, 0, (LPARAM)&mmi,
                             SMTO_ABORTIFHUNG | SMTO_NORMAL, 10, &result)) {
        return;
    }
    RECT win{}, frame{};
    if (!GetWindowRect(leaf->hWnd, &win) || !GetFrame(leaf->hWnd, &frame)) return;
    // The app answers in window size; tiles are in visible frame size.
    int w = mmi.ptMinTrackSize.x - (Width(win) - Width(frame));
    int h = mmi.ptMinTrackSize.y - (Height(win) - Height(frame));
    if (w > 150 && w < 4000) leaf->minW = std::max(leaf->minW, w);
    if (h > 150 && h < 4000) leaf->minH = std::max(leaf->minH, h);
}

Node* InsertLeaf(Workspace* ws, Node* split, size_t index, HWND hWnd, bool ask = true) {
    auto leaf = std::make_unique<Node>();
    leaf->hWnd = hWnd;
    if (ask) QueryMinSize(leaf.get());
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
    // Same monitor: what the app taught about its smallest size still holds.
    bool same = old.ws->monitor == dest->monitor;
    Node* fresh = InsertLeaf(dest, split, index, hWnd, !same);
    if (same) {
        fresh->minW = old.node->minW;
        fresh->minH = old.node->minH;
    }
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

// An app that stopped responding can't be resized. Its tile takes the window's
// real size until it wakes, so the tiles beside it close up instead of leaving
// a gap. Returns 0 for every other window.
int FrozenLength(const Node* node, bool vertical) {
    if (!node->hWnd || !node->children.empty() || node->fill ||
        !IsHungAppWindow(node->hWnd) || IsZoomed(node->hWnd)) {
        return 0;
    }
    RECT frame{};
    if (!GetFrame(node->hWnd, &frame)) return 0;
    return vertical ? Height(frame) : Width(frame);
}

void ComputeNode(Node* node, const RECT& rect, int gap) {
    node->target = rect;
    size_t count = node->children.size();
    if (!count) {
        node->slot = rect;
        node->hidden = Hidden(node);
        if (!node->hWnd) return;
        // Edges the grow keys pulled in, keeping at least the smallest tile.
        int* in = node->inset;
        int spareX = std::max(0, Width(rect) - g_minTile);
        int spareY = std::max(0, Height(rect) - g_minTile);
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
    std::vector<int> frozen(count, 0);
    int frozenSum = 0;
    double spare = 0;
    for (size_t i = 0; i < count; i++) {
        frozen[i] = FrozenLength(shown[i], node->vertical);
        if (frozen[i]) {
            frozenSum += frozen[i];
        } else {
            spare += shown[i]->weight;
        }
    }
    if (frozenSum && (spare <= 0.001 || frozenSum > length - g_minTile)) {
        frozen.assign(count, 0);  // Nothing left to close up with.
        frozenSum = 0;
    }
    if (!frozenSum) spare = total;
    int rest = length - frozenSum;
    double before = 0;
    int frozenBefore = 0;
    for (size_t i = 0; i < count; i++) {
        double after = frozen[i] ? before : before + shown[i]->weight / spare;
        int frozenAfter = frozenBefore + frozen[i];
        int a = start + frozenBefore + (int)std::lround(before * rest) + gap * (int)i;
        int b = i + 1 == count
                    ? start + length + gap * (int)i
                    : start + frozenAfter + (int)std::lround(after * rest) + gap * (int)i;
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
        frozenBefore = frozenAfter;
    }
}

bool ComputeLayout(Workspace* ws) {
    MONITORINFO mi{sizeof(mi)};
    if (!GetMonitorInfoW(ws->monitor, &mi)) return false;
    RECT area = snapCommander::GappedWorkArea(ws->monitor, mi.rcWork);
    g_minTile = MinTile(ws->monitor);
    ComputeNode(ws->root.get(), area, InnerGap(ws->monitor));
    std::vector<Node*> leaves;
    CollectLeaves(ws->root.get(), &leaves);
    Node* only = nullptr;
    int shown = 0;
    for (Node* leaf : leaves) {
        if (leaf->fill) leaf->target = area;
        if (!leaf->hidden) {
            only = leaf;
            shown++;
        }
    }
    // One window alone on the screen: no gaps around it.
    if (g_config.singleNoGaps && shown == 1) only->target = mi.rcWork;
    return true;
}

// The monitors "Monitors that never tile" names, looked up again every 2 s.
std::vector<HMONITOR> g_offMonitors;
ULONGLONG g_offMonitorsTick = 0;

bool TilingOffOn(HMONITOR monitor) {
    if (!g_config.offMonitors) return false;
    ULONGLONG now = GetTickCount64();
    if (!g_offMonitorsTick || now - g_offMonitorsTick > 2000) {
        g_offMonitorsTick = now;
        g_offMonitors.clear();
        auto list = OrderedMonitors();
        for (size_t i = 0; i < list.size() && i < 32; i++) {
            if (g_config.offMonitors & (1u << i)) g_offMonitors.push_back(list[i].hMon);
        }
    }
    return std::find(g_offMonitors.begin(), g_offMonitors.end(), monitor) !=
           g_offMonitors.end();
}

bool CanPlace(HWND hWnd) {
    return IsWindow(hWnd) && !IsIconic(hWnd) && !IsZoomed(hWnd) && !IsHungAppWindow(hWnd) &&
           !effects::IsFullscreen(hWnd);
}

// Counts the times an app refused to get as small as its tile.
int g_minLearned = 0;

// An app that won't go smaller than its minimum size keeps its top-left corner
// and grows past the target, out over the next monitor. Slide it back inside
// the gapped work area of the monitor it belongs on.
void KeepInside(HWND hWnd, const RECT& target, RECT* frame) {
    HMONITOR monitor = MonitorFromRect(&target, MONITOR_DEFAULTTONEAREST);
    MONITORINFO mi{sizeof(mi)};
    if (!GetMonitorInfoW(monitor, &mi)) return;
    RECT work = snapCommander::GappedWorkArea(monitor, mi.rcWork);
    int dx = 0, dy = 0;
    if (frame->right > work.right) dx = work.right - frame->right;
    if (frame->left + dx < work.left) dx = work.left - frame->left;
    if (frame->bottom > work.bottom) dy = work.bottom - frame->bottom;
    if (frame->top + dy < work.top) dy = work.top - frame->top;
    if (!dx && !dy) return;
    snapCommander::ApplyVisibleRect(hWnd, frame->left + dx, frame->top + dy, Width(*frame),
                                    Height(*frame));
    GetFrame(hWnd, frame);
}

// The tile, grown to the app's own smallest size once it showed one. Asking for less
// only makes the app grow back, and the two then trade sizes for good.
RECT Wanted(const Node* leaf) {
    RECT t = leaf->target;
    if (leaf->minW > Width(t)) t.right = t.left + leaf->minW;
    if (leaf->minH > Height(t)) t.bottom = t.top + leaf->minH;
    return t;
}

void PlaceLeaf(Node* leaf) {
    leaf->placedFor = leaf->target;
    HWND hWnd = leaf->hWnd;
    if (!CanPlace(hWnd)) {
        leaf->placed = {};
        return;
    }
    const RECT t = Wanted(leaf);
    RECT frame{};
    GetFrame(hWnd, &frame);
    for (int pass = 0; pass < 2 && !SameRect(frame, t); pass++) {
        // A second pass fixes the border size after crossing to a monitor
        // with another scale.
        snapCommander::ApplyVisibleRect(hWnd, t.left, t.top, Width(t), Height(t));
        GetFrame(hWnd, &frame);
        leaf->placedTick = GetTickCount64();
    }
    // Bigger than asked: that is the app's minimum. Remember it so the
    // layout gives this tile at least that much from now on.
    if (Width(frame) > Width(t) + 2 && Width(frame) > leaf->minW) {
        leaf->minW = Width(frame);
        g_minLearned++;
    }
    if (Height(frame) > Height(t) + 2 && Height(frame) > leaf->minH) {
        leaf->minH = Height(frame);
        g_minLearned++;
    }
    KeepInside(hWnd, t, &frame);
    leaf->placed = frame;
}

// The tiles glide to their new places together, then land exactly.
void PlaceLeaves(const std::vector<Node*>& leaves) {
    std::vector<std::pair<HWND, RECT>> moves;
    for (Node* leaf : leaves) {
        if (CanPlace(leaf->hWnd)) moves.push_back({leaf->hWnd, Wanted(leaf)});
    }
    snapCommander::AnimateRects(moves);
    for (Node* leaf : leaves) PlaceLeaf(leaf);
}

// The smallest this part of the tree can be along one axis: 150 px a window
// at 100% scale, or the app's own minimum once it refused to go smaller.
int MinAlong(Workspace* ws, Node* node, bool vertical) {
    if (node->hWnd) return std::max(MinTile(ws->monitor), vertical ? node->minH : node->minW);
    int total = 0;
    for (auto& child : node->children) {
        int m = MinAlong(ws, child.get(), vertical);
        total = node->vertical == vertical ? total + m : std::max(total, m);
    }
    if (node->vertical == vertical && node->children.size() > 1) {
        total += InnerGap(ws->monitor) * (int)(node->children.size() - 1);
    }
    return total;
}

// Gives every tile at least its smallest size, taken from the siblings that
// have room to spare. Returns true if any share changed.
bool RespectMins(Workspace* ws, Node* split) {
    if (split->hWnd) return false;
    bool changed = false;
    size_t n = split->children.size();
    double avail = (split->vertical ? Height(split->target) : Width(split->target)) -
                   (double)InnerGap(ws->monitor) * (n > 0 ? n - 1 : 0);
    if (n > 1 && avail >= 1) {
        std::vector<double> mins(n);
        double sum = 0;
        for (size_t i = 0; i < n; i++) {
            mins[i] = MinAlong(ws, split->children[i].get(), split->vertical) / avail;
            sum += mins[i];
        }
        for (size_t i = 0; sum <= 1.0 && i < n; i++) {
            Node* child = split->children[i].get();
            if (child->weight >= mins[i]) continue;
            double spare = 0;
            for (size_t j = 0; j < n; j++) {
                if (j != i) spare += std::max(0.0, split->children[j]->weight - mins[j]);
            }
            if (spare <= 0) break;
            double take = std::min(mins[i] - child->weight, spare);
            for (size_t j = 0; j < n; j++) {
                if (j == i) continue;
                Node* other = split->children[j].get();
                other->weight -= take * std::max(0.0, other->weight - mins[j]) / spare;
            }
            child->weight += take;
            changed = true;
        }
    }
    for (auto& child : split->children) changed |= RespectMins(ws, child.get());
    return changed;
}

void Layout(std::initializer_list<Workspace*> list) {
    std::vector<Node*> leaves;
    for (Workspace* ws : list) {
        if (ws && ComputeLayout(ws)) CollectLeaves(ws->root.get(), &leaves);
    }
    int learned = g_minLearned;
    PlaceLeaves(leaves);
    if (g_minLearned == learned) return;
    // An app refused its tile. Make room for it now, once, so nothing is
    // left overlapping or hanging off the screen.
    leaves.clear();
    for (Workspace* ws : list) {
        if (ws && RespectMins(ws, ws->root.get()) && ComputeLayout(ws)) {
            CollectLeaves(ws->root.get(), &leaves);
        }
    }
    if (!leaves.empty()) PlaceLeaves(leaves);
}

void Layout(Workspace* ws) {
    Layout({ws});
}

void LayoutAll() {
    for (auto& ws : g_workspaces) Layout(ws.get());
}

//////// which windows tile ////////

// lasting: set when the answer is no for as long as the window stays shown.
bool CanTile(HWND hWnd, bool forced, bool* lasting = nullptr) {
    if (!hWnd || !IsWindow(hWnd) || GetAncestor(hWnd, GA_ROOT) != hWnd ||
        !IsWindowVisible(hWnd) || IsIconic(hWnd)) {
        return false;
    }
    auto never = [lasting] {
        if (lasting) *lasting = true;
        return false;
    };
    DWORD pid = 0;
    GetWindowThreadProcessId(hWnd, &pid);
    if (pid == GetCurrentProcessId()) return never();
    LONG_PTR style = GetWindowLongPtrW(hWnd, GWL_STYLE);
    LONG_PTR ex = GetWindowLongPtrW(hWnd, GWL_EXSTYLE);
    if ((style & WS_CHILD) || (ex & (WS_EX_TOOLWINDOW | WS_EX_NOACTIVATE))) return never();
    static constexpr PCWSTR kNeverTile[] = {
        L"#32770",
        L"Windows.UI.Core.CoreWindow",
        L"XamlExplorerHostIslandWindow",
        L"MultitaskingViewFrame",
        L"ForegroundStaging",
        L"TopLevelWindowForOverflowXamlIsland",
        L"NotifyIconOverflowWindow",
        L"OperationStatusWindow",
        L"Ghost",  // Windows' stand-in for an app that stopped responding.
    };
    WCHAR cls[96] = {};
    GetClassNameW(hWnd, cls, ARRAYSIZE(cls));
    for (PCWSTR name : kNeverTile) {
        if (wcscmp(cls, name) == 0) return never();
    }
    if (!altSnapDrag::CanActOnRootWindow(hWnd)) return never();
    if (TilingOffOn(MonitorFromWindow(hWnd, MONITOR_DEFAULTTONEAREST))) return false;
    if (forced) return true;
    // Ordinary app windows only: resizable, with a title bar or maximize box,
    // not pinned on top, not a dialog and not owned by another window.
    if (!(style & WS_THICKFRAME)) return never();
    if ((style & WS_CAPTION) != WS_CAPTION && !(style & WS_MAXIMIZEBOX)) return never();
    if ((ex & WS_EX_DLGMODALFRAME) || GetWindow(hWnd, GW_OWNER)) return never();
    if (ex & WS_EX_TOPMOST) return false;
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
            return never();
        }
    }
    return !snapCommander::HasPlacementRule(hWnd) || never();
}

// Quick check at event time; CanTile decides once the window settles.
bool LooksTileable(HWND hWnd) {
    if (GetAncestor(hWnd, GA_ROOT) != hWnd) return false;
    WCHAR cls[8] = {};
    if (GetClassNameW(hWnd, cls, ARRAYSIZE(cls)) && wcscmp(cls, L"Ghost") == 0) return false;
    LONG_PTR style = GetWindowLongPtrW(hWnd, GWL_STYLE);
    LONG_PTR ex = GetWindowLongPtrW(hWnd, GWL_EXSTYLE);
    return !(style & WS_CHILD) && !(ex & WS_EX_TOOLWINDOW) &&
           (style & (WS_THICKFRAME | WS_CAPTION));
}

// Windows covers an app that stopped responding with a stand-in window and
// reports the app as hidden, though it never was. It keeps its tile.
bool StillShown(HWND hWnd) {
    return IsWindow(hWnd) && !IsIconic(hWnd) &&
           (IsWindowVisible(hWnd) || IsHungAppWindow(hWnd));
}

// A new window takes half of the biggest tile, cut along its long side, so it
// never opens as a thin strip beside the others (a spiral layout).
void InsertSplit(Workspace* ws, HWND hWnd) {
    ComputeLayout(ws);
    std::vector<Node*> leaves;
    CollectLeaves(ws->root.get(), &leaves);
    Node* best = nullptr;
    long long bestArea = -1;
    for (Node* leaf : leaves) {
        if (leaf->hidden || leaf->fill) continue;
        long long area = (long long)Width(leaf->slot) * Height(leaf->slot);
        // On a tie, the one that had focus gives up its half.
        if (area > bestArea || (area == bestArea && leaf->hWnd == ws->lastFocused)) {
            best = leaf;
            bestArea = area;
        }
    }
    if (!best) {
        InsertLeaf(ws, ws->root.get(), ws->root->children.size(), hWnd);
        return;
    }
    bool vertical = Height(best->slot) > Width(best->slot);
    Node* parent = best->parent;
    if (parent->vertical == vertical) {
        // Already cut this way: the two halves share its old place.
        std::vector<double> weights;
        for (auto& child : parent->children) weights.push_back(child->weight);
        size_t index = IndexOf(best);
        Node* leaf = InsertLeaf(ws, parent, index + 1, hWnd);
        for (size_t i = 0, j = 0; i < parent->children.size(); i++) {
            if (parent->children[i].get() == leaf) continue;
            parent->children[i]->weight = weights[j++];
        }
        best->weight /= 2;
        leaf->weight = best->weight;
        return;
    }
    // Cut the other way: the tile becomes a split of the old window and the new one.
    size_t index = IndexOf(best);
    auto split = std::make_unique<Node>();
    split->vertical = vertical;
    split->weight = best->weight;
    split->parent = parent;
    Node* raw = split.get();
    std::unique_ptr<Node> old = std::move(parent->children[index]);
    old->parent = raw;
    old->weight = 1.0;
    raw->children.push_back(std::move(old));
    parent->children[index] = std::move(split);
    InsertLeaf(ws, raw, 1, hWnd);
}

// A full-screen app (a game, a video) in front on this monitor, other than hWnd.
struct FullscreenSearch {
    HMONITOR monitor;
    HWND skip;
    HWND found;
};

BOOL CALLBACK FullscreenSearchProc(HWND hWnd, LPARAM param) {
    auto* s = reinterpret_cast<FullscreenSearch*>(param);
    if (hWnd == s->skip || !IsWindowVisible(hWnd) || IsIconic(hWnd) || IsZoomed(hWnd) ||
        IsCloaked(hWnd) || GetAncestor(hWnd, GA_ROOT) != hWnd) {
        return TRUE;
    }
    LONG_PTR ex = GetWindowLongPtrW(hWnd, GWL_EXSTYLE);
    // Overlays and the click-through layers other mods draw don't count.
    if (ex & (WS_EX_TOOLWINDOW | WS_EX_NOACTIVATE | WS_EX_TRANSPARENT)) return TRUE;
    DWORD pid = 0;
    GetWindowThreadProcessId(hWnd, &pid);
    if (pid == GetCurrentProcessId()) return TRUE;
    WCHAR cls[32] = {};
    GetClassNameW(hWnd, cls, ARRAYSIZE(cls));
    if (!wcscmp(cls, L"Progman") || !wcscmp(cls, L"WorkerW")) return TRUE;
    if (MonitorFromWindow(hWnd, MONITOR_DEFAULTTONEAREST) != s->monitor ||
        !effects::IsFullscreen(hWnd)) {
        return TRUE;
    }
    s->found = hWnd;
    return FALSE;
}

HWND FullscreenOn(HMONITOR monitor, HWND skip) {
    FullscreenSearch s{monitor, skip, nullptr};
    EnumWindows(FullscreenSearchProc, reinterpret_cast<LPARAM>(&s));
    return s.found;
}

// Over a game: opens in the middle at a good size, and joins the tiles once
// the game closes or leaves full screen.
std::unordered_set<HWND> g_waiting;
int g_waitTicks = 0;

void FloatCentered(HWND hWnd, HMONITOR monitor) {
    MONITORINFO mi{sizeof(mi)};
    RECT win{}, frame{};
    if (!GetMonitorInfoW(monitor, &mi) || !GetWindowRect(hWnd, &win) || !GetFrame(hWnd, &frame)) {
        return;
    }
    Node probe{};
    probe.hWnd = hWnd;
    QueryMinSize(&probe);
    const RECT& work = mi.rcWork;
    int w = std::min(Width(work), std::max(MulDiv(Width(work), 3, 5), probe.minW));
    int h = std::min(Height(work), std::max(MulDiv(Height(work), 3, 4), probe.minH));
    int x = work.left + (Width(work) - w) / 2;
    int y = work.top + (Height(work) - h) / 2;
    // The app's window is a little bigger than what shows (its invisible edges).
    SetWindowPos(hWnd, nullptr, x - (frame.left - win.left), y - (frame.top - win.top),
                 w + Width(win) - Width(frame), h + Height(win) - Height(frame),
                 SWP_NOZORDER | SWP_NOACTIVATE | SWP_NOOWNERZORDER | SWP_ASYNCWINDOWPOS);
}

Workspace* AddWindow(HWND hWnd) {
    if (g_leaves.count(hWnd)) return g_leaves[hWnd].ws;
    g_waiting.erase(hWnd);
    HMONITOR monitor = MonitorFromWindow(hWnd, MONITOR_DEFAULTTONEAREST);
    Workspace* ws = GetWorkspace(monitor, DesktopOf(hWnd));
    InsertSplit(ws, hWnd);
    // On a tie for the biggest tile, the next window splits this one.
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
        g_waiting.erase(item.second);
        InsertSplit(ws, item.second);
    }
    if (!items.empty()) TLog(L"Tiling: %d open windows tiled", (int)items.size());
    LayoutAll();
    PublishTiled();
}

// A tile that ended up on a monitor that never tiles floats there.
void DropOffMonitorTiles() {
    std::vector<HWND> drop;
    for (auto& entry : g_leaves) {
        if (TilingOffOn(entry.second.ws->monitor)) drop.push_back(entry.first);
    }
    for (HWND hWnd : drop) RemoveWindow(hWnd);
    if (!drop.empty()) {
        TLog(L"Tiling: %d windows on a monitor that never tiles", (int)drop.size());
        LayoutAll();
        PublishTiled();
    }
}

// Even sizes again, and the windows that fell out of the tiles come back.
void Equalize(Node* node) {
    std::fill(std::begin(node->inset), std::end(node->inset), 0);
    node->fights = 0;
    for (auto& child : node->children) {
        child->weight = 1.0 / (double)node->children.size();
        Equalize(child.get());
    }
}

void RetileCommand() {
    if (!g_active) return;
    HWND hWnd = GetAncestor(GetForegroundWindow(), GA_ROOT);
    POINT pt{};
    GetCursorPos(&pt);
    HMONITOR monitor = hWnd ? MonitorFromWindow(hWnd, MONITOR_DEFAULTTONEAREST)
                            : MonitorFromPoint(pt, MONITOR_DEFAULTTONEAREST);
    for (auto& ws : g_workspaces) {
        if (ws->monitor == monitor) Equalize(ws->root.get());
    }
    g_noTile.clear();
    Reconcile();
}

void ClearAll() {
    g_leaves.clear();
    g_workspaces.clear();
    g_pending.clear();
    g_cloakCheck.clear();
    g_waiting.clear();
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
        // Neither side may go below its smallest size (an app's own minimum
        // counts), or that app overflows its tile onto the next monitor.
        double low = MinAlong(ws, node, vertical) / avail - node->weight;
        double high = sibling->weight - MinAlong(ws, sibling, vertical) / avail;
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
            int least = std::max(MinTile(ws->monitor), vertical ? node->minH : node->minW);
            int room = std::max(0, size - least - node->inset[dir]);
            node->inset[kOpposite[dir]] = std::min(room, node->inset[kOpposite[dir]] + px);
        }
        Layout(ws);
        PublishTiled();
        return;
    }
    if (!altSnapDrag::CanSizeRootWindow(hWnd)) return;
    RECT f{};
    GetFrame(hWnd, &f);
    const int kMin = MinTile(MonitorFromWindow(hWnd, MONITOR_DEFAULTTONEAREST));
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
    // An app at its minimum size grows past the edge instead: pull it back.
    RECT now{};
    if (GetFrame(hWnd, &now)) KeepInside(hWnd, work, &now);
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
    g_noTile.erase(hWnd);
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

// Gives a window a new style and lets it redraw its frame, keeping its size and
// place.
void SetTitleStyle(HWND hWnd, LONG_PTR style) {
    if (!IsWindow(hWnd)) return;
    SetWindowLongPtrW(hWnd, GWL_STYLE, style);
    SetWindowPos(hWnd, nullptr, 0, 0, 0, 0,
                 SWP_FRAMECHANGED | SWP_NOMOVE | SWP_NOSIZE | SWP_NOZORDER |
                     SWP_NOOWNERZORDER | SWP_NOACTIVATE);
}

// Ctrl+Win+Alt+T: hide the active window's title bar and keep its resize edges,
// size and place (GlazeWM's hide title bar). Press again to bring it back.
void HideTitleCommand() {
    HWND hWnd = ActiveRoot();
    if (!hWnd || g_borderless.count(hWnd)) return;
    auto saved = g_noTitle.find(hWnd);
    if (saved != g_noTitle.end()) {
        LONG_PTR style = saved->second;
        g_noTitle.erase(saved);
        SetTitleStyle(hWnd, style);
    } else {
        if (!altSnapDrag::CanActOnRootWindow(hWnd)) return;
        LONG_PTR style = GetWindowLongPtrW(hWnd, GWL_STYLE);
        if ((style & WS_CAPTION) != WS_CAPTION) return;  // No title bar to hide.
        g_noTitle[hWnd] = style;
        // A fixed-size window keeps a thin edge, so it still shows where it
        // ends; a resizable one keeps its resize border.
        LONG_PTR edge = (style & WS_THICKFRAME) ? 0 : WS_BORDER;
        SetTitleStyle(hWnd, (style & ~WS_CAPTION) | edge);
    }
    // A tiled window goes back into its tile with the new frame.
    auto leaf = g_leaves.find(hWnd);
    if (leaf != g_leaves.end()) Layout(leaf->second.ws);
    TLog(L"Tiling: %p title bar %ls", hWnd, g_noTitle.count(hWnd) ? L"hidden" : L"back");
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

// Alt+PageDown / Alt+PageUp: walk the windows hidden behind the ones in front,
// on this monitor: behind the active window, or mostly covered by any windows
// above it (say one window behind two tiles side by side).
struct CycleFocusEnumData {
    RECT current;
    HMONITOR monitor;
    HRGN above;  // Everything in front of the window being looked at.
    std::vector<HWND>* out;
};

LONG RectArea(const RECT& r) {
    return std::max(0L, r.right - r.left) * std::max(0L, r.bottom - r.top);
}

long long RegionArea(HRGN rgn) {
    DWORD size = GetRegionData(rgn, 0, nullptr);
    if (!size) return 0;
    std::vector<BYTE> buffer(size);
    auto* data = reinterpret_cast<RGNDATA*>(buffer.data());
    if (!GetRegionData(rgn, size, data)) return 0;
    long long area = 0;
    const RECT* rects = reinterpret_cast<const RECT*>(data->Buffer);
    for (DWORD i = 0; i < data->rdh.nCount; i++) area += RectArea(rects[i]);
    return area;
}

BOOL CALLBACK CycleFocusProc(HWND hWnd, LPARAM param) {
    auto* d = reinterpret_cast<CycleFocusEnumData*>(param);
    if (!IsWindowVisible(hWnd) || IsIconic(hWnd) || IsCloaked(hWnd) ||
        (GetWindowLongPtrW(hWnd, GWL_EXSTYLE) & (WS_EX_TOOLWINDOW | WS_EX_NOACTIVATE)) ||
        !altSnapDrag::CanActOnRootWindow(hWnd)) {
        return TRUE;
    }
    WCHAR cls[32] = {};
    GetClassNameW(hWnd, cls, ARRAYSIZE(cls));
    if (!wcscmp(cls, L"Progman") || !wcscmp(cls, L"WorkerW") || !wcscmp(cls, L"Shell_TrayWnd")) {
        return TRUE;
    }
    RECT frame{};
    if (!GetFrame(hWnd, &frame) || frame.right - frame.left < 2 ||
        frame.bottom - frame.top < 2 ||
        MonitorFromWindow(hWnd, MONITOR_DEFAULTTONEAREST) != d->monitor) {
        return TRUE;
    }
    // Behind this one: at least half of the smaller of the two overlaps.
    RECT overlap{};
    IntersectRect(&overlap, &frame, &d->current);
    bool behind = RectArea(overlap) * 2 >= std::min(RectArea(frame), RectArea(d->current));
    // Or at least half of it is out of sight under the windows in front. A tile
    // beside this one is in plain view, so it stays with the focus keys.
    HRGN mine = CreateRectRgnIndirect(&frame);
    HRGN covered = CreateRectRgn(0, 0, 0, 0);
    bool hidden = false;
    if (mine && covered && CombineRgn(covered, mine, d->above, RGN_AND) != ERROR) {
        hidden = RegionArea(covered) * 2 >= RectArea(frame);
    }
    if (behind || hidden) d->out->push_back(hWnd);
    if (mine) CombineRgn(d->above, d->above, mine, RGN_OR);
    if (covered) DeleteObject(covered);
    if (mine) DeleteObject(mine);
    return TRUE;
}

// One walk: the windows found on the first press, front to back, with the one
// that was active first. Pressing again goes on down the same list, so a window
// brought up doesn't shuffle the rest; it lasts while our pick keeps the focus.
std::vector<HWND> g_cycleList;
size_t g_cycleAt = 0;

void CycleFocusCommand(int direction) {
    HWND hCur = ActiveRoot();
    if (!hCur) return;
    bool fresh = g_cycleList.size() < 2 || g_cycleAt >= g_cycleList.size() ||
                 g_cycleList[g_cycleAt] != hCur;
    if (!fresh) {
        for (HWND hWnd : g_cycleList) {
            if (!IsWindow(hWnd) || !IsWindowVisible(hWnd) || IsIconic(hWnd)) fresh = true;
        }
    }
    if (fresh) {
        CycleFocusEnumData data{};
        if (!GetFrame(hCur, &data.current)) return;
        data.monitor = MonitorFromWindow(hCur, MONITOR_DEFAULTTONEAREST);
        data.above = CreateRectRgn(0, 0, 0, 0);
        if (!data.above) return;
        std::vector<HWND> stack;
        data.out = &stack;
        // EnumWindows walks front to back.
        EnumWindows(CycleFocusProc, reinterpret_cast<LPARAM>(&data));
        DeleteObject(data.above);
        stack.erase(std::remove(stack.begin(), stack.end(), hCur), stack.end());
        if (stack.empty()) return;
        g_cycleList.clear();
        g_cycleList.push_back(hCur);
        g_cycleList.insert(g_cycleList.end(), stack.begin(), stack.end());
        g_cycleAt = 0;
    }
    size_t count = g_cycleList.size();
    g_cycleAt = direction >= 0 ? (g_cycleAt + 1) % count : (g_cycleAt + count - 1) % count;
    FocusWindow(g_cycleList[g_cycleAt]);
    TLog(L"Walk: to %p, front now %p", g_cycleList[g_cycleAt], GetForegroundWindow());
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
        case kTileHideTitle: HideTitleCommand(); break;
        case kTileRetile: RetileCommand(); break;
    }
}

//////// window events ////////

void QueuePending(HWND hWnd) {
    if (g_active && !g_leaves.count(hWnd) && !g_floated.count(hWnd) && !g_pending.count(hWnd) &&
        !g_borderless.count(hWnd) && !g_noTile.count(hWnd) && !g_waiting.count(hWnd)) {
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
    if (e.event == EVENT_SYSTEM_MOVESIZESTART || e.event == EVENT_SYSTEM_MOVESIZEEND) {
        g_handMovedWnd = hWnd;
        g_handMovedTick = GetTickCount64();
    }
    if (e.event == EVENT_SYSTEM_MINIMIZESTART) RememberMinimized(hWnd);
    if (e.event == EVENT_OBJECT_DESTROY || e.event == EVENT_OBJECT_HIDE ||
        e.event == EVENT_SYSTEM_MINIMIZESTART) {
        g_noTile.erase(hWnd);
        if (e.event != EVENT_OBJECT_HIDE || !StillShown(hWnd)) g_waiting.erase(hWnd);
    }
    switch (e.event) {
        case EVENT_OBJECT_DESTROY:
            g_floated.erase(hWnd);
            g_homes.erase(hWnd);
            g_pending.erase(hWnd);
            g_cloakCheck.erase(hWnd);
            g_borderless.erase(hWnd);
            g_fillRestore.erase(hWnd);
            g_noTitle.erase(hWnd);
            [[fallthrough]];
        case EVENT_OBJECT_HIDE:
        case EVENT_SYSTEM_MINIMIZESTART:
            if (e.event == EVENT_OBJECT_HIDE && StillShown(hWnd)) break;
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
        bool cloaked = IsCloaked(hWnd), lasting = false;
        if (!cloaked && CanTile(hWnd, false, &lasting)) {
            HMONITOR monitor = MonitorFromWindow(hWnd, MONITOR_DEFAULTTONEAREST);
            if (HWND game = FullscreenOn(monitor, hWnd)) {
                TLog(L"Tiling: %p waits over full-screen %p", hWnd, game);
                FloatCentered(hWnd, monitor);
                g_waiting.insert(hWnd);
            } else {
                touched.push_back(AddWindow(hWnd));
            }
            it = g_pending.erase(it);
        } else if ((cloaked || !IsWindowVisible(hWnd)) && ticks < 30) {
            ++it;
        } else {
            if (lasting) g_noTile.insert(hWnd);
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
    // Once a second: the windows waiting over a game tile when it's gone.
    if (!g_waiting.empty() && ++g_waitTicks >= 10) {
        g_waitTicks = 0;
        std::vector<HWND> ready;
        for (auto it = g_waiting.begin(); it != g_waiting.end();) {
            HWND hWnd = *it;
            if (!IsWindow(hWnd) || g_leaves.count(hWnd) || g_floated.count(hWnd) ||
                !IsWindowVisible(hWnd) || IsIconic(hWnd)) {
                it = g_waiting.erase(it);
                continue;
            }
            if (!IsCloaked(hWnd) &&
                !FullscreenOn(MonitorFromWindow(hWnd, MONITOR_DEFAULTTONEAREST), hWnd)) {
                ready.push_back(hWnd);
            }
            ++it;
        }
        for (HWND hWnd : ready) {
            g_waiting.erase(hWnd);
            if (CanTile(hWnd, false)) {
                TLog(L"Tiling: %p joins the tiles, the full-screen app is gone", hWnd);
                touched.push_back(AddWindow(hWnd));
            }
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
            g_homes.erase(hWnd);
            Workspace* dest = GetWorkspace(monitor, ws->desktop);
            Relocate(hWnd, dest, dest->root.get(), dest->root->children.size());
            Layout(ws);
            Layout(dest);
            PublishTiled();
            return true;
        }
        leaf->fightTick = GetTickCount64();
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
        g_homes.erase(hWnd);
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

HMONITOR MonitorByDevice(const std::wstring& device) {
    struct Find {
        const std::wstring* name;
        HMONITOR found;
    } find{&device, nullptr};
    EnumDisplayMonitors(
        nullptr, nullptr,
        [](HMONITOR monitor, HDC, LPRECT, LPARAM param) WINAPI -> BOOL {
            auto* f = reinterpret_cast<Find*>(param);
            MONITORINFOEXW mi{};
            mi.cbSize = sizeof(mi);
            if (GetMonitorInfoW(monitor, &mi) && *f->name == mi.szDevice) {
                f->found = monitor;
                return FALSE;
            }
            return TRUE;
        },
        (LPARAM)&find);
    return find.found;
}

// A display came back: the windows that tiled on it before it went away go
// back to it. Returns true when the layout changed.
bool ReturnHomes() {
    std::vector<Workspace*> touched;
    for (auto it = g_homes.begin(); it != g_homes.end();) {
        HWND hWnd = it->first;
        auto leaf = g_leaves.find(hWnd);
        if (leaf == g_leaves.end()) {
            it = g_homes.erase(it);
            continue;
        }
        HMONITOR home = MonitorByDevice(it->second);
        if (!home) {
            ++it;  // Another display came, not this one.
            continue;
        }
        Workspace* from = leaf->second.ws;
        if (from->monitor != home) {
            Workspace* dest = GetWorkspace(home, from->desktop);
            Relocate(hWnd, dest, dest->root.get(), dest->root->children.size());
            touched.push_back(from);
            touched.push_back(dest);
        }
        it = g_homes.erase(it);
    }
    if (touched.empty()) return false;
    TLog(L"Tiling: a display came back, its windows return");
    std::sort(touched.begin(), touched.end());
    touched.erase(std::unique(touched.begin(), touched.end()), touched.end());
    for (Workspace* ws : touched) Layout(ws);
    PublishTiled();
    return true;
}

// Four times a second for a few seconds after anything happens, and once a
// second otherwise, while windows are tiled: keeps them in their tiles, and
// turns a drag or an edge resize into a change to the layout.
void OnEnforceTimer() {
    int monitors = GetSystemMetrics(SM_CMONITORS);
    if (monitors != g_monitorCount) {
        bool more = g_monitorCount && monitors > g_monitorCount;
        g_monitorCount = monitors;
        if (more && !g_homes.empty() && ReturnHomes()) return;
    }
    for (auto& wsp : g_workspaces) {
        MONITORINFO mi{sizeof(mi)};
        if (wsp->root->children.empty() || GetMonitorInfoW(wsp->monitor, &mi)) continue;
        // The display went away: its windows tile wherever they are now, and
        // go back when it returns.
        TLog(L"Tiling: a display went away");
        std::vector<Node*> leaves;
        CollectLeaves(wsp->root.get(), &leaves);
        std::vector<HWND> windows;
        for (Node* leaf : leaves) windows.push_back(leaf->hWnd);
        if (!wsp->device.empty()) {
            for (HWND hWnd : windows) g_homes[hWnd] = wsp->device;
        }
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
        if (!StillShown(hWnd)) gone.push_back(hWnd);
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
                // A window that sits still for a moment and then grows again is still fighting.
                if (now - leaf->fightTick > 10000) leaf->fights = 0;
                continue;
            }
            if (now - leaf->placedTick < 500) continue;  // Still animating into place.
            if (IsRectEmpty(&leaf->placed)) {
                PlaceLeaf(leaf);
                continue;
            }
            // Moved by the mouse only if this window had the drag: an app that grows back to
            // its own minimum while the owner clicks in a game must not move its neighbours.
            bool byHand = byMouse && hWnd == g_handMovedWnd.load() && now - g_handMovedTick < 2000;
            if (OnWindowMoved(ws, leaf, frame, byHand)) return;
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
        // Only to wake the checks: a title bar drag or an edge resize.
        g_hooks[4] = SetWinEventHook(EVENT_SYSTEM_MOVESIZESTART, EVENT_SYSTEM_MOVESIZEEND,
                                     nullptr, EventProc, 0, 0, kFlags);
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
    bool want = g_active && !g_leaves.empty();
    UINT ms = GetTickCount64() < g_enforceFastUntil ? 250 : 1000;
    if (want && g_enforceTimer && ms != g_enforceMs) SetTimerState(&g_enforceTimer, false, 0);
    if (want && !g_enforceTimer) g_enforceMs = ms;
    SetTimerState(&g_enforceTimer, want, ms);
    SetTimerState(&g_pendingTimer,
                  g_active && (!g_pending.empty() || !g_cloakCheck.empty() || !g_waiting.empty()),
                  100);
}

// Start, settings change, pause and resume all come here.
void Apply() {
    g_config = GetSettings();
    g_offMonitorsTick = 0;
    bool want = g_config.tiling && !IsPaused() && !g_stopping;
    g_noTile.clear();
    if (!want) {
        if (g_active) TLog(L"Tiling: off");
        g_active = false;
        Hook(false);
        ClearAll();
        g_homes.clear();
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
    swm::g_tilingNudgeThread = GetCurrentThreadId();
    SetEvent((HANDLE)ready);
    Apply();
    UpdateTimers();
    while (GetMessageW(&msg, nullptr, 0, 0) > 0) {
        if (msg.hwnd) {
            DispatchMessageW(&msg);
            continue;
        }
        // An event, a key, a button release: check closely for a while.
        if (msg.message != WM_TIMER) g_enforceFastUntil = GetTickCount64() + 3000;
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
        if (g_active && g_config.offMonitors) DropOffMonitorTiles();
        UpdateTimers();
    }
    swm::g_tilingNudgeThread = 0;
    g_active = false;
    Hook(false);
    ClearAll();
    g_floated.clear();
    g_noTile.clear();
    g_homes.clear();
    for (auto& entry : g_borderless) RestoreBorders(entry.first, entry.second);
    g_borderless.clear();
    for (auto& entry : g_noTitle) SetTitleStyle(entry.first, entry.second);
    g_noTitle.clear();
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
    HWND root = GetAncestor(hWnd, GA_ROOT);
    // A minimized window already plays the restore animation.
    bool moved = root && !IsIconic(root) && GetAncestor(GetForegroundWindow(), GA_ROOT) != root;
    if (IsIconic(hWnd)) {
        ShowWindow(hWnd, SW_RESTORE);
    }
    bool animate = moved && g_focusAnimMs > 0 && !effects::IsFullscreen(root);
    // Zoom: the app's own copy of the mod plays it (see FocusPulseThread).
    // Posted first: the app reads it once it has redrawn as the active window.
    if (animate && !g_focusRing) {
        PostMessageW(root, altSnapDrag::g_focusPulseMessage, g_focusAnimMs, 0);
    }
    osd::switchNote::Mark();
    if (!SetForegroundWindow(hWnd)) {
        // A zero-distance mouse input counts as user input and unlocks it.
        INPUT input{};
        input.type = INPUT_MOUSE;
        input.mi.dwFlags = MOUSEEVENTF_MOVE;
        input.mi.dwExtraInfo = kFocusInputExtraInfo;
        SendInput(1, &input, sizeof(input));
        SetForegroundWindow(hWnd);
    }
    // Ring: drawn by this helper once the window is in front.
    if (animate && g_focusRing) {
        ShowFocusRing(root, g_focusAnimMs);
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
std::array<bool, kDesktopKeyCount> g_sendDesktopRegistered{};
std::array<bool, kDesktopKeyCount> g_sendDesktopFailLogged{};
bool g_resizeActive;
HWND g_resizeTarget;
UINT_PTR g_resizeTimer;
std::array<bool, 256> g_swallowedKeys{};
// The two walk keys, for the keyboard hook on this same thread. Empty while
// paused or unbound. g_walkKeyHeld is the walk key down right now.
constexpr int kWalkUpKey = 35;
std::array<ModeKey, 2> g_walkKeys{};
DWORD g_walkKeyHeld;
// When the held walk key last came down. Key repeat keeps it fresh; a press after a gap
// is a new press, so a release another app ate never leaves the key stuck.
DWORD g_walkKeyTick;

void UnregisterModeKeys() {
    g_walkKeys = {};
    for (size_t i = 0; i < g_modeKeyRegistered.size(); i++) {
        if (g_modeKeyRegistered[i]) {
            UnregisterHotKey(nullptr, kModeKeyBase + (int)i);
            g_modeKeyRegistered[i] = false;
        }
    }
    g_modeKeyFailLogged = {};
    for (int j = 0; j < kDesktopKeyCount; j++) {
        if (g_sendDesktopRegistered[j]) UnregisterHotKey(nullptr, kSendDesktopBase + j);
        g_sendDesktopRegistered[j] = false;
    }
    g_sendDesktopFailLogged = {};
}

// Registers what is missing. While paused only the pause key stays.
void RegisterModeKeys() {
    if (!altSnapDrag::g_globalInput) {
        return;
    }
    Settings s = GetSettings();
    bool paused = IsPaused();
    for (int w = 0; w < 2; w++) {
        g_walkKeys[w] = paused ? ModeKey{} : s.keys[kWalkUpKey + w];
    }
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
    // Send to desktop: the desktop key with Win added, unless it has Win already.
    for (int j = 0; j < kDesktopKeyCount; j++) {
        const ModeKey& key = s.keys[kFirstDesktopKey + j];
        UINT mods = ToHotkeyMods(key.modifiers);
        bool want = s.desktopSend && key.key && !paused && !(mods & MOD_WIN);
        if (!want) {
            if (g_sendDesktopRegistered[j]) {
                UnregisterHotKey(nullptr, kSendDesktopBase + j);
                g_sendDesktopRegistered[j] = false;
            }
            continue;
        }
        if (g_sendDesktopRegistered[j]) continue;
        g_sendDesktopRegistered[j] = RegisterHotKey(nullptr, kSendDesktopBase + j,
                                                    mods | MOD_WIN | MOD_NOREPEAT,
                                                    key.key) != FALSE;
        if (!g_sendDesktopRegistered[j] && !g_sendDesktopFailLogged[j]) {
            g_sendDesktopFailLogged[j] = true;
            Wh_Log(L"Send to desktop %d: another app already uses this key (%lu)", j + 1,
                   GetLastError());
        }
    }
}

// The window used before this one: the next app window down the stack, like
// a quick Alt+Tab. Pressed again, it comes back.
void FocusLastCommand() {
    HWND active = GetAncestor(GetForegroundWindow(), GA_ROOT);
    HWND hWnd = active ? GetWindow(active, GW_HWNDNEXT) : GetTopWindow(nullptr);
    for (int i = 0; hWnd && i < 1000; i++, hWnd = GetWindow(hWnd, GW_HWNDNEXT)) {
        if (!IsWindowVisible(hWnd) || IsIconic(hWnd) || IsCloaked(hWnd) ||
            GetWindow(hWnd, GW_OWNER)) {
            continue;
        }
        LONG_PTR ex = GetWindowLongPtrW(hWnd, GWL_EXSTYLE);
        RECT frame{};
        if ((ex & (WS_EX_TOOLWINDOW | WS_EX_NOACTIVATE)) ||
            !altSnapDrag::CanActOnRootWindow(hWnd) || !GetFrame(hWnd, &frame) ||
            frame.right - frame.left < 50 || frame.bottom - frame.top < 50) {
            continue;
        }
        DWORD pid = 0;
        GetWindowThreadProcessId(hWnd, &pid);
        if (pid == GetCurrentProcessId()) continue;
        FocusWindow(hWnd);
        return;
    }
}

void SendToDesktop(int index) {
    HWND hWnd = GetAncestor(GetForegroundWindow(), GA_ROOT);
    int count = 1, current = 0;
    if (!hWnd || !altSnapDrag::CanActOnRootWindow(hWnd) || !ReadDesktops(&count, &current) ||
        index >= count || index == current) {
        return;
    }
    // Only the window's own process may move it: its copy of the mod does.
    PostMessageW(hWnd, altSnapDrag::g_desktopRequestMessage, index, 0);
    if (GetSettings().desktopSend == 2) StartDesktopSwitch(index);
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

// From the keyboard hook: the walk keys are taken here, ahead of any app
// whose own keyboard hook would keep them (a remote desktop window sends
// every key to the other PC). One step per press; the release is kept too.
// Those apps keep Alt too, and a kept key never reaches GetAsyncKeyState, so
// the hook notes the modifiers itself. A held key repeats, so a note older
// than 1.5 s is a release that never came (the secure desktop eats those).
std::array<DWORD, 4> g_modifierDownTick{};
bool OnWalkKey(WPARAM message, const KBDLLHOOKSTRUCT* key) {
    DWORD vk = key->vkCode;
    bool down = message == WM_KEYDOWN || message == WM_SYSKEYDOWN;
    int modifier = -1;
    switch (vk) {
        case VK_CONTROL: case VK_LCONTROL: case VK_RCONTROL: modifier = 0; break;
        case VK_MENU: case VK_LMENU: case VK_RMENU: modifier = 1; break;
        case VK_SHIFT: case VK_LSHIFT: case VK_RSHIFT: modifier = 2; break;
        case VK_LWIN: case VK_RWIN: modifier = 3; break;
    }
    if (modifier >= 0) {
        if (key->dwExtraInfo != altSnapDrag::kOwnInputExtraInfo) {
            g_modifierDownTick[modifier] = down ? (GetTickCount() | 1) : 0;
        }
        return false;
    }
    if (!down) {
        if (g_walkKeyHeld && vk == g_walkKeyHeld) {
            g_walkKeyHeld = 0;
            return true;
        }
        return false;
    }
    if (key->dwExtraInfo == altSnapDrag::kOwnInputExtraInfo) {
        return false;
    }
    if (g_walkKeyHeld && vk == g_walkKeyHeld) {
        DWORD gap = GetTickCount() - g_walkKeyTick;
        if (gap < 1100) {  // the longest key repeat delay is 1 s
            g_walkKeyTick = GetTickCount();
            return true;
        }
        Wh_Log(L"Walk: key %u was stuck held %u ms, new press", vk, gap);
        g_walkKeyHeld = 0;
    }
    DWORD held = altSnapDrag::HeldModifiers(GetAsyncKeyState);
    constexpr DWORD kBits[] = {altSnapDrag::kModifierCtrl, altSnapDrag::kModifierAlt,
                               altSnapDrag::kModifierShift, altSnapDrag::kModifierWin};
    DWORD now = GetTickCount();
    for (int m = 0; m < 4; m++) {
        if (g_modifierDownTick[m] && now - g_modifierDownTick[m] < 1500) held |= kBits[m];
    }
    for (int w = 0; w < 2; w++) {
        const ModeKey& walk = g_walkKeys[w];
        if (!walk.key || (DWORD)walk.key != vk || walk.modifiers != held) {
            continue;
        }
        g_walkKeyHeld = vk;
        g_walkKeyTick = GetTickCount();
        PostThreadMessageW(GetCurrentThreadId(), WM_HOTKEY,
                           kModeKeyBase + kWalkUpKey + w, 0);
        return true;
    }
    return false;
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
    if (HWND tray = g_trayWnd) PostMessageW(tray, kTrayUpdateMessage, 0, 0);
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
    if (msg.message == WM_HOTKEY && msg.wParam >= (WPARAM)kSendDesktopBase &&
        msg.wParam < (WPARAM)(kSendDesktopBase + kDesktopKeyCount)) {
        if (!IsPaused()) SendToDesktop((int)msg.wParam - kSendDesktopBase);
        altSnapDrag::g_swallowedPress = GetAsyncKeyState(VK_MENU) < 0;
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
            // Bring back the window sent behind: the back of the stack comes up.
            PostTilingCommand(kTileCycleFocus, -1);
        } else if (id == 36) {
            // Show the window behind: the next one comes up, this one goes back.
            PostTilingCommand(kTileCycleFocus, 1);
        } else if (id == 37) {
            PostTilingCommand(kTileRestoreMinimized, 0);
        } else if (id == 38) {
            PostTilingCommand(kTileHideTitle, 0);
        } else if (id == kRetileKey) {
            PostTilingCommand(kTileRetile, 0);
        } else if (id == kFocusLastKey) {
            FocusLastCommand();
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

// ==== SWM settings window (generated) begin ====
#include <d2d1_1.h>
#include <d2d1helper.h>
#include <wincodec.h>
#include <imm.h>
#include <shellapi.h>
#include <shlobj.h>
#include <windowsx.h>
#include <map>
#include <set>

// The text a key box writes for a recorded key. Both key readers in this mod understand it:
// ParseHotkey for the hotkey* settings and ParseShortcut for the snap keys.
static std::wstring Hotkey_Format(UINT mods, UINT vk) {
    std::wstring s;
    if (mods & MOD_CONTROL) s += L"Ctrl+";
    if (mods & MOD_ALT) s += L"Alt+";
    if (mods & MOD_SHIFT) s += L"Shift+";
    if (mods & MOD_WIN) s += L"Win+";
    if ((vk >= 'A' && vk <= 'Z') || (vk >= '0' && vk <= '9')) return s + (WCHAR)vk;
    if (vk >= VK_F1 && vk <= VK_F24) return s + L"F" + std::to_wstring(vk - VK_F1 + 1);
    switch (vk) {
        case VK_SPACE: return s + L"Space";
        case VK_TAB: return s + L"Tab";
        case VK_ESCAPE: return s + L"Esc";
        case VK_DELETE: return s + L"Delete";
        case VK_INSERT: return s + L"Insert";
        case VK_HOME: return s + L"Home";
        case VK_END: return s + L"End";
        case VK_PRIOR: return s + L"PageUp";
        case VK_NEXT: return s + L"PageDown";
        case VK_LEFT: return s + L"Left";
        case VK_RIGHT: return s + L"Right";
        case VK_UP: return s + L"Up";
        case VK_DOWN: return s + L"Down";
        case VK_OEM_4: return s + L"[";
        case VK_OEM_6: return s + L"]";
        case VK_OEM_MINUS: return s + L"-";
        case VK_OEM_PLUS: return s + L"plus";
    }
    // Anything else is stored as the number ParseHotkey reads: key | modifiers << 8.
    return std::to_wstring(vk | (mods & (MOD_ALT | MOD_CONTROL | MOD_SHIFT | MOD_WIN)) << 8);
}
// Settings window: the Seamless Launchpad settings GUI, the standard for every DavidHiFi mod.
// Generated by work\2026-11-09-seamless-window-manager\gen_settings.py. Edit the generator.
extern "C" IMAGE_DOS_HEADER __ImageBase;
namespace swmset {
// The settings window, from the tray icon. It shows the same settings as
// Windhawk's page for this mod and saves them through windhawk-cli, so the two
// stay in step. Writing a mod's settings takes admin rights, so the save runs
// the CLI elevated (silently where UAC prompts are off).

constexpr WCHAR kSettingsClass[] = L"WindhawkSeamlessWindowManagerSettings";
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
// Generated by work\2026-11-09-seamless-window-manager\gen_settings.py from the settings block.
static void Dyn_AddFields(std::vector<SetField>& out);
static bool Dyn_IsVirtual(PCWSTR key);
static std::vector<SetField> Set_MakeFields() {
    using K = SetField;
    std::vector<SetField> out = {
{K::Choice, L"modifier", L"Hold these for the snap keys", L"Added to every snap key below, so each snap key is just the key itself. Choose None to type the whole shortcut into each one.", L"alt", {{L"none", L"None"}, {L"alt", L"Alt"}, {L"ctrl", L"Ctrl"}, {L"shift", L"Shift"}, {L"win", L"Win"}, {L"alt_ctrl", L"Alt + Ctrl"}, {L"alt_shift", L"Alt + Shift"}, {L"ctrl_shift", L"Ctrl + Shift"}, {L"win_alt", L"Win + Alt"}, {L"win_ctrl", L"Win + Ctrl"}, {L"win_shift", L"Win + Shift"}}, 0, 100, 0, L"Snap keys"},
{K::Hotkey, L"shortcuts.keyLeftHalf", L"Left half", L"Type a key such as \"q\" or \"left\". The keys held above are added on top. Leave empty to turn it off. Same for every key below.", L"q", {}, 0, 100, 0, L"Snap keys"},
{K::Hotkey, L"shortcuts.keyRightHalf", L"Right half", L"", L"w", {}, 0, 100, 0, L"Snap keys"},
{K::Hotkey, L"shortcuts.keyTopHalf", L"Top half", L"", L"e", {}, 0, 100, 0, L"Snap keys"},
{K::Hotkey, L"shortcuts.keyBottomHalf", L"Bottom half", L"", L"r", {}, 0, 100, 0, L"Snap keys"},
{K::Hotkey, L"shortcuts.keyCenterHalf", L"Center half", L"A half-width strip in the middle of the screen, full height.", L"c", {}, 0, 100, 0, L"Snap keys"},
{K::Hotkey, L"shortcuts.keyTopLeft", L"Top-left quarter", L"", L"u", {}, 0, 100, 0, L"Snap keys"},
{K::Hotkey, L"shortcuts.keyTopRight", L"Top-right quarter", L"", L"i", {}, 0, 100, 0, L"Snap keys"},
{K::Hotkey, L"shortcuts.keyBottomLeft", L"Bottom-left quarter", L"", L"j", {}, 0, 100, 0, L"Snap keys"},
{K::Hotkey, L"shortcuts.keyBottomRight", L"Bottom-right quarter", L"", L"k", {}, 0, 100, 0, L"Snap keys"},
{K::Hotkey, L"shortcuts.keyMaximize", L"Maximize", L"Fills the whole screen and ignores the gaps.", L"h", {}, 0, 100, 0, L"Snap keys"},
{K::Hotkey, L"shortcuts.keyAlmostMaximize", L"Maximize with a margin", L"Fills the screen but keeps the gaps around the window.", L"y", {}, 0, 100, 0, L"Snap keys"},
{K::Hotkey, L"shortcuts.keyNextDisplay", L"Send to the next monitor", L"", L"]", {}, 0, 100, 0, L"Snap keys"},
{K::Hotkey, L"shortcuts.keyPrevDisplay", L"Send to the previous monitor", L"", L"[", {}, 0, 100, 0, L"Snap keys"},
{K::Hotkey, L"shortcuts.keySmaller", L"Shrink by one step", L"Shrinks the window around its middle.", L"-", {}, 0, 100, 0, L"Snap keys"},
{K::Hotkey, L"shortcuts.keyLarger", L"Grow by one step", L"Grows the window around its middle. Write this key as \"plus\" or \"=\", because \"+\" joins the keys of a shortcut.", L"plus", {}, 0, 100, 0, L"Snap keys"},
{K::Hotkey, L"shortcuts.keyRestore", L"Undo snap", L"Puts the window back where it was before the first snap.", L"z", {}, 0, 100, 0, L"Snap keys"},
{K::Hotkey, L"shortcuts.keyLeftThird", L"Left third", L"Press again for the left two thirds. Empty means off. Tiled windows don't take thirds.", L"", {}, 0, 100, 0, L"Snap keys"},
{K::Hotkey, L"shortcuts.keyCenterThird", L"Middle third", L"The middle third of the screen. Empty means off.", L"", {}, 0, 100, 0, L"Snap keys"},
{K::Hotkey, L"shortcuts.keyRightThird", L"Right third", L"Press again for the right two thirds.", L"", {}, 0, 100, 0, L"Snap keys"},
{K::Hotkey, L"hotkeyMaximize", L"Maximize or restore", L"Type the whole shortcut, such as \"Alt+X\" or \"Ctrl+Alt+X\". It needs at least one of Alt, Ctrl, Shift or Win. Leave empty to turn it off. Same for every shortcut below. Off by default, because Alt+F fills the screen.", L"", {}, 0, 100, 0, L"Window keys"},
{K::Hotkey, L"hotkeyMinimize", L"Minimize", L"", L"Alt+M", {}, 0, 100, 0, L"Window keys"},
{K::Hotkey, L"hotkeyRestoreMinimized", L"Restore minimized window", L"Brings back the window you minimized last, at its old size and place. Press again for the one before it.", L"Alt+Shift+M", {}, 0, 100, 0, L"Window keys"},
{K::Hotkey, L"hotkeyMRUUp", L"Go back up the hidden windows", L"Walks the same windows as the key below, the other way round.", L"Alt+PageUp", {}, 0, 100, 0, L"Window keys"},
{K::Hotkey, L"hotkeyMRUDown", L"Bring up a hidden window", L"Brings up the window hidden behind the ones in front on this monitor, even one behind two tiles side by side. Press again for the one behind that, and once more to come back to where you started. Windows in plain view are left to the focus keys.", L"Alt+PageDown", {}, 0, 100, 0, L"Window keys"},
{K::Hotkey, L"hotkeyClose", L"Close", L"", L"Alt+Shift+Q", {}, 0, 100, 0, L"Window keys"},
{K::Hotkey, L"hotkeyMenu", L"Open the window menu", L"", L"", {}, 0, 100, 0, L"Window keys"},
{K::Hotkey, L"hotkeyTopmost", L"Toggle always on top", L"", L"", {}, 0, 100, 0, L"Window keys"},
{K::Hotkey, L"hotkeyLower", L"Send to the back", L"", L"", {}, 0, 100, 0, L"Window keys"},
{K::Hotkey, L"hotkeyCenter", L"Center the window", L"Moves the window to the middle of its screen and keeps its size.", L"", {}, 0, 100, 0, L"Window keys"},
{K::Hotkey, L"hotkeySideSnap", L"Snap to the nearest side", L"", L"", {}, 0, 100, 0, L"Window keys"},
{K::Hotkey, L"hotkeyPause", L"Pause the window manager", L"Turns every drag, shortcut and rule off until you press it again. Handy in games and drawing apps that need Alt.", L"Alt+Shift+P", {}, 0, 100, 0, L"Window keys"},
{K::Hotkey, L"hotkeyFill", L"Fill the screen (tiled window)", L"The window fills the screen but keeps the gaps around it, like GlazeWM's fullscreen. Press again to put it back in its tile or old spot.", L"Alt+F", {}, 0, 100, 0, L"Window keys"},
{K::Hotkey, L"hotkeyBorderless", L"Fullscreen without a title bar", L"No title bar or borders, like ShareX's \"Make active window borderless\", and the window covers the whole monitor, taskbar included. Press again to give the window its frame and size back. If another app already uses the shortcut, it starts working once that app lets go of it.", L"Ctrl+Shift+F", {}, 0, 100, 0, L"Window keys"},
{K::Hotkey, L"hotkeyHideTitleBar", L"Hide the title bar", L"The active window loses its title bar, like GlazeWM's hide title bar, but keeps its size, place and resize edges. Press again to bring the title bar back. Apps that draw their own title bar may not change.", L"Ctrl+Win+Alt+T", {}, 0, 100, 0, L"Window keys"},
{K::Hotkey, L"hotkeyResizeMode", L"Resize with the keyboard", L"Arrow keys or H J K L then resize the active window. Hold Shift to move it instead. Press Esc or Enter when you are done.", L"Alt+Shift+R", {}, 0, 100, 0, L"Keyboard resize"},
{K::Number, L"resizeMode.step", L"Keyboard resize mode: step (%)", L"How far each key press resizes or moves the window, as a share of the screen. 1 to 20 (Suggested: 2).", L"2", {}, 1, 20, 0, L"Keyboard resize"},
{K::Number, L"resizeMode.timeout", L"Finish after (seconds)", L"Leaves resize mode on its own when you stop pressing keys. 3 to 60 (Suggested: 10).", L"10", {}, 3, 60, 0, L"Keyboard resize"},
{K::Choice, L"moveTrigger.button", L"Mouse button", L"", L"left", {{L"left", L"Left button"}, {L"right", L"Right button"}, {L"middle", L"Middle button"}, {L"x1", L"Back button"}, {L"x2", L"Forward button"}}, 0, 100, 1, L"Move with the mouse"},
{K::Check, L"moveTrigger.ctrl", L"Hold Ctrl", L"", L"0", {}, 0, 100, 1, L"Move with the mouse"},
{K::Check, L"moveTrigger.alt", L"Hold Alt", L"", L"1", {}, 0, 100, 1, L"Move with the mouse"},
{K::Check, L"moveTrigger.shift", L"Hold Shift", L"", L"0", {}, 0, 100, 1, L"Move with the mouse"},
{K::Check, L"moveTrigger.win", L"Hold Win", L"", L"0", {}, 0, 100, 1, L"Move with the mouse"},
{K::Number, L"moveTrigger.delay", L"Hold time (ms)", L"How long to hold the button before the window starts moving. A shorter press goes to the window as a normal click. 0 to 500 (Suggested: 0).", L"0", {}, 0, 500, 1, L"Move with the mouse"},
{K::Number, L"moveTrigger.magnet", L"Magnetic edges with Ctrl (px)", L"Hold Ctrl as well while you drag, and the window's edges cling to the screen edges and to other windows once they come this close. 0 turns it off. 0 to 60 (Suggested: 20).", L"20", {}, 0, 60, 1, L"Move with the mouse"},
{K::Choice, L"sizeTrigger.button", L"Mouse button", L"", L"right", {{L"left", L"Left button"}, {L"right", L"Right button"}, {L"middle", L"Middle button"}, {L"x1", L"Back button"}, {L"x2", L"Forward button"}}, 0, 100, 1, L"Resize with the mouse"},
{K::Check, L"sizeTrigger.ctrl", L"Hold Ctrl", L"", L"0", {}, 0, 100, 1, L"Resize with the mouse"},
{K::Check, L"sizeTrigger.alt", L"Hold Alt", L"", L"1", {}, 0, 100, 1, L"Resize with the mouse"},
{K::Check, L"sizeTrigger.shift", L"Hold Shift", L"", L"0", {}, 0, 100, 1, L"Resize with the mouse"},
{K::Check, L"sizeTrigger.win", L"Hold Win", L"", L"0", {}, 0, 100, 1, L"Resize with the mouse"},
{K::Number, L"sizeTrigger.delay", L"Hold time (ms)", L"How long to hold the button before the window starts resizing. A shorter press goes to the window as a normal click. 0 to 500 (Suggested: 0).", L"0", {}, 0, 500, 1, L"Resize with the mouse"},
{K::Check, L"dragWindowsWithoutTitleBar", L"Move windows without a title bar", L"Also move popups, launchers and flyouts that have no title bar. When off, only normal windows move.", L"0", {}, 0, 100, 1, L"Windows without a title bar or border"},
{K::Check, L"explorerTitleStripDrag", L"Move File Explorer by its title strip", L"Pressing the empty strip at the top of a File Explorer window moves the window instead of grabbing the tab.", L"1", {}, 0, 100, 1, L"Windows without a title bar or border"},
{K::Check, L"sizeWindowsWithoutSizingBorder", L"Resize windows without a border", L"Also resize borderless windows such as the Ditto and Flow Launcher popups. A short click still runs the click action below.", L"1", {}, 0, 100, 1, L"Windows without a title bar or border"},
{K::Choice, L"middleAction", L"Middle click", L"What a middle click does while you hold the move keys.", L"menu", {{L"menu", L"Open the window menu"}, {L"maximize", L"Toggle maximize"}, {L"minimize", L"Minimize"}, {L"close", L"Close"}, {L"topmost", L"Toggle always on top"}, {L"lower", L"Send to the back"}, {L"center", L"Center"}, {L"sideSnap", L"Snap to the nearest side"}, {L"none", L"Nothing"}}, 0, 100, 1, L"Clicks"},
{K::Choice, L"rightClickAction", L"Right click without dragging", L"A short right click. Dragging with the right button still resizes.", L"maximize", {{L"menu", L"Open the window menu"}, {L"maximize", L"Toggle maximize"}, {L"minimize", L"Minimize"}, {L"close", L"Close"}, {L"topmost", L"Toggle always on top"}, {L"lower", L"Send to the back"}, {L"center", L"Center"}, {L"sideSnap", L"Snap to the nearest side"}, {L"none", L"Nothing"}}, 0, 100, 1, L"Clicks"},
{K::Choice, L"x1Action", L"Back button click", L"", L"none", {{L"menu", L"Open the window menu"}, {L"maximize", L"Toggle maximize"}, {L"minimize", L"Minimize"}, {L"close", L"Close"}, {L"topmost", L"Toggle always on top"}, {L"lower", L"Send to the back"}, {L"center", L"Center"}, {L"sideSnap", L"Snap to the nearest side"}, {L"none", L"Nothing"}}, 0, 100, 1, L"Clicks"},
{K::Choice, L"x2Action", L"Forward button click", L"", L"none", {{L"menu", L"Open the window menu"}, {L"maximize", L"Toggle maximize"}, {L"minimize", L"Minimize"}, {L"close", L"Close"}, {L"topmost", L"Toggle always on top"}, {L"lower", L"Send to the back"}, {L"center", L"Center"}, {L"sideSnap", L"Snap to the nearest side"}, {L"none", L"Nothing"}}, 0, 100, 1, L"Clicks"},
{K::Choice, L"leftDoubleAction", L"Left double click", L"", L"none", {{L"menu", L"Open the window menu"}, {L"maximize", L"Toggle maximize"}, {L"minimize", L"Minimize"}, {L"close", L"Close"}, {L"topmost", L"Toggle always on top"}, {L"lower", L"Send to the back"}, {L"center", L"Center"}, {L"sideSnap", L"Snap to the nearest side"}, {L"none", L"Nothing"}}, 0, 100, 1, L"Clicks"},
{K::Choice, L"middleDoubleAction", L"Middle double click", L"", L"none", {{L"menu", L"Open the window menu"}, {L"maximize", L"Toggle maximize"}, {L"minimize", L"Minimize"}, {L"close", L"Close"}, {L"topmost", L"Toggle always on top"}, {L"lower", L"Send to the back"}, {L"center", L"Center"}, {L"sideSnap", L"Snap to the nearest side"}, {L"none", L"Nothing"}}, 0, 100, 1, L"Clicks"},
{K::Choice, L"rightDoubleAction", L"Right double click", L"", L"none", {{L"menu", L"Open the window menu"}, {L"maximize", L"Toggle maximize"}, {L"minimize", L"Minimize"}, {L"close", L"Close"}, {L"topmost", L"Toggle always on top"}, {L"lower", L"Send to the back"}, {L"center", L"Center"}, {L"sideSnap", L"Snap to the nearest side"}, {L"none", L"Nothing"}}, 0, 100, 1, L"Clicks"},
{K::Check, L"tiling.enabled", L"Tile new windows", L"New app windows fill the screen side by side, like GlazeWM. A new one takes half of the biggest tile. Over a full-screen game it opens in the middle and tiles once the game is gone. Dialogs, small windows and windows on top stay floating.", L"1", {}, 0, 100, 2, L"Tiling"},
{K::Check, L"tiling.existing", L"Tile windows already open", L"When on, the windows already open are tiled when the mod starts.", L"1", {}, 0, 100, 2, L"Tiling"},
{K::Number, L"tiling.innerGap", L"Space between tiled windows (px)", L"Always pixels. The space at the screen edges comes from the screen-edge gaps. 0 to 100 (Suggested: 20).", L"20", {}, 0, 100, 2, L"Tiling"},
{K::Number, L"tiling.resizeStep", L"Tile grow keys: step (%)", L"How far each press of a grow key moves the edge, as a share of the screen. 1 to 20 (Suggested: 5).", L"5", {}, 1, 20, 2, L"Tiling"},
{K::Check, L"tiling.singleNoGaps", L"No gaps around a window alone", L"A window alone on its monitor fills it with no gaps.", L"0", {}, 0, 100, 2, L"Tiling"},
{K::Text, L"tiling.offMonitors", L"Monitors that never tile", L"Monitor numbers, such as \"3\" or \"2, 4\", counted like the monitor keys. Windows there float.", L"", {}, 0, 100, 2, L"Tiling"},
{K::Number, L"dimensions.gapTop", L"Gap at the top screen edge", L"Space between a snapped window and the top of the screen, in the gap unit below. 0 to 100 (Suggested: 0).", L"0", {}, 0, 100, 2, L"Gaps and sizes"},
{K::Number, L"dimensions.gapBottom", L"Gap at the bottom screen edge", L"Space between a snapped window and the bottom of the screen, in the gap unit below. 0 to 100 (Suggested: 0).", L"0", {}, 0, 100, 2, L"Gaps and sizes"},
{K::Number, L"dimensions.gapLeft", L"Gap at the left screen edge", L"Space between a snapped window and the left of the screen, in the gap unit below. 0 to 100 (Suggested: 0).", L"0", {}, 0, 100, 2, L"Gaps and sizes"},
{K::Number, L"dimensions.gapRight", L"Gap at the right screen edge", L"Space between a snapped window and the right of the screen, in the gap unit below. 0 to 100 (Suggested: 0).", L"0", {}, 0, 100, 2, L"Gaps and sizes"},
{K::Choice, L"dimensions.gapUnit", L"Gap unit", L"Percent sizes each gap by the screen, so 1 means 1% of the screen width for left and right gaps and 1% of the height for top and bottom gaps.", L"px", {{L"px", L"Pixels"}, {L"percent", L"Percent of the screen"}}, 0, 100, 2, L"Gaps and sizes"},
{K::Choice, L"dimensions.gapScaling", L"Gap scaling", L"Scale with display makes pixel gaps grow on monitors set above 100% scale, so they look the same size on every screen. Only used with Pixels.", L"exact", {{L"exact", L"Exact pixels"}, {L"dpi", L"Scale with display"}}, 0, 100, 2, L"Gaps and sizes"},
{K::Choice, L"dimensions.gapMode", L"Gap style for snapped windows", L"Even keeps the gap between two windows the same as the gap at the screen edge. Full puts the whole gap on every side, so it doubles between windows. Screen edges only lets side-by-side windows touch.", L"even", {{L"even", L"Even"}, {L"full", L"Full on every side"}, {L"screen", L"Screen edges only"}}, 0, 100, 2, L"Gaps and sizes"},
{K::Text, L"dimensions.almostMaximizeGap", L"Gap for Maximize with a margin", L"The same gap on all four sides. 0 to 200. Leave empty to use the screen-edge gaps.", L"", {}, 0, 100, 2, L"Gaps and sizes"},
{K::Text, L"dimensions.centerWidth", L"Width after Center (px)", L"Used by the Center app rule. 100 up to the screen width. Leave empty to keep the window's width.", L"", {}, 0, 100, 2, L"Gaps and sizes"},
{K::Text, L"dimensions.centerHeight", L"Height after Center (px)", L"Used by the Center app rule. 100 up to the screen height. Leave empty to keep the window's height.", L"", {}, 0, 100, 2, L"Gaps and sizes"},
{K::Number, L"dimensions.resizeStep", L"Smaller and larger keys: step (%)", L"How much Shrink by one step and Grow by one step change the window on each press. 1 to 20 (Suggested: 5).", L"5", {}, 1, 20, 2, L"Gaps and sizes"},
{K::Hotkey, L"hotkeyMoveLeft", L"Move the window left", L"A tiled window trades places with its neighbour, or moves into the next column or monitor. A floating window snaps to that half of the screen.", L"Alt+Shift+Left", {}, 0, 100, 2, L"Tiling keys"},
{K::Hotkey, L"hotkeyMoveRight", L"Move the window right", L"", L"Alt+Shift+Right", {}, 0, 100, 2, L"Tiling keys"},
{K::Hotkey, L"hotkeyMoveUp", L"Move the window up", L"", L"Alt+Shift+Up", {}, 0, 100, 2, L"Tiling keys"},
{K::Hotkey, L"hotkeyMoveDown", L"Move the window down", L"", L"Alt+Shift+Down", {}, 0, 100, 2, L"Tiling keys"},
{K::Hotkey, L"hotkeyGrowLeft", L"Grow the window to the left", L"Pushes that edge of the window out. Hold the keys to keep going. At the edge of the screen, the far edge comes in instead.", L"Ctrl+Alt+Shift+Left", {}, 0, 100, 2, L"Tiling keys"},
{K::Hotkey, L"hotkeyGrowRight", L"Grow the window to the right", L"", L"Ctrl+Alt+Shift+Right", {}, 0, 100, 2, L"Tiling keys"},
{K::Hotkey, L"hotkeyGrowUp", L"Grow the window upward", L"", L"Ctrl+Alt+Shift+Up", {}, 0, 100, 2, L"Tiling keys"},
{K::Hotkey, L"hotkeyGrowDown", L"Grow the window downward", L"", L"Ctrl+Alt+Shift+Down", {}, 0, 100, 2, L"Tiling keys"},
{K::Hotkey, L"hotkeyToggleTiling", L"Tile or float the window", L"Takes the active window out of the tiles so you can place it anywhere, or puts a floating window back in.", L"Alt+T", {}, 0, 100, 2, L"Tiling keys"},
{K::Hotkey, L"hotkeyTilingDirection", L"Flip the split", L"The next window opens below instead of beside, or back again. Turns the active window's group from side by side to stacked. Try Alt+V.", L"", {}, 0, 100, 2, L"Tiling keys"},
{K::Hotkey, L"hotkeyRetile", L"Even out and retile", L"Makes every tile on this monitor the same size again and tiles the windows that dropped out.", L"Alt+Shift+E", {}, 0, 100, 2, L"Tiling keys"},
{K::Hotkey, L"hotkeyMonitor1", L"Focus monitor 1", L"Like GlazeWM's workspace keys, one per monitor. Monitors count left to right along the main monitor's row, then the ones above or below. With a left, main, right and top screen: 1 left, 2 main, 3 right, 4 top. The front window there gets focus and the pointer goes with it.", L"Alt+1", {}, 0, 100, 3, L"Monitor keys"},
{K::Hotkey, L"hotkeyMonitor2", L"Focus monitor 2", L"", L"Alt+2", {}, 0, 100, 3, L"Monitor keys"},
{K::Hotkey, L"hotkeyMonitor3", L"Focus monitor 3", L"", L"Alt+3", {}, 0, 100, 3, L"Monitor keys"},
{K::Hotkey, L"hotkeyMonitor4", L"Focus monitor 4", L"", L"Alt+4", {}, 0, 100, 3, L"Monitor keys"},
{K::Hotkey, L"hotkeySendMonitor1", L"Send to monitor 1", L"A tiled window takes a tile there; a floating one keeps its size and spot on the new screen.", L"Alt+Shift+1", {}, 0, 100, 3, L"Monitor keys"},
{K::Hotkey, L"hotkeySendMonitor2", L"Send to monitor 2", L"", L"Alt+Shift+2", {}, 0, 100, 3, L"Monitor keys"},
{K::Hotkey, L"hotkeySendMonitor3", L"Send to monitor 3", L"", L"Alt+Shift+3", {}, 0, 100, 3, L"Monitor keys"},
{K::Hotkey, L"hotkeySendMonitor4", L"Send to monitor 4", L"", L"Alt+Shift+4", {}, 0, 100, 3, L"Monitor keys"},
{K::Hotkey, L"hotkeyDesktop1", L"Switch to desktop 1", L"Windows virtual desktops, each with its own tiles. A desktop that doesn't exist yet is made. The switch happens when you let go of the keys.", L"Ctrl+Alt+Shift+1", {}, 0, 100, 3, L"Desktop keys"},
{K::Hotkey, L"hotkeyDesktop2", L"Switch to desktop 2", L"", L"Ctrl+Alt+Shift+2", {}, 0, 100, 3, L"Desktop keys"},
{K::Hotkey, L"hotkeyDesktop3", L"Switch to desktop 3", L"", L"Ctrl+Alt+Shift+3", {}, 0, 100, 3, L"Desktop keys"},
{K::Hotkey, L"hotkeyDesktop4", L"Switch to desktop 4", L"", L"Ctrl+Alt+Shift+4", {}, 0, 100, 3, L"Desktop keys"},
{K::Hotkey, L"hotkeyDesktop5", L"Switch to desktop 5", L"", L"Ctrl+Alt+Shift+5", {}, 0, 100, 3, L"Desktop keys"},
{K::Hotkey, L"hotkeyDesktop6", L"Switch to desktop 6", L"", L"Ctrl+Alt+Shift+6", {}, 0, 100, 3, L"Desktop keys"},
{K::Hotkey, L"hotkeyDesktop7", L"Switch to desktop 7", L"", L"Ctrl+Alt+Shift+7", {}, 0, 100, 3, L"Desktop keys"},
{K::Hotkey, L"hotkeyDesktop8", L"Switch to desktop 8", L"", L"Ctrl+Alt+Shift+8", {}, 0, 100, 3, L"Desktop keys"},
{K::Hotkey, L"hotkeyDesktop9", L"Switch to desktop 9", L"", L"Ctrl+Alt+Shift+9", {}, 0, 100, 3, L"Desktop keys"},
{K::Choice, L"desktopSend", L"Send a window to a desktop", L"Add Win to a desktop key, such as Ctrl+Win+Alt+Shift+2, to send the active window to that desktop. Only desktops that already exist.", L"send", {{L"off", L"Off"}, {L"send", L"Send the window"}, {L"follow", L"Send the window and go with it"}}, 0, 100, 3, L"Desktop keys"},
{K::Check, L"keepSize", L"Keep size when sent to another monitor", L"When off, the window grows or shrinks to match the new monitor.", L"1", {}, 0, 100, 3, L"Sending a window"},
{K::Check, L"centerOnMove", L"Center when sent to another monitor", L"When off, the window keeps the same spot relative to the screen.", L"0", {}, 0, 100, 3, L"Sending a window"},
{K::Check, L"cursorFollowsWindow", L"Move the pointer with a sent window", L"When you send a window to another monitor with the keyboard, the mouse pointer jumps to the middle of that window.", L"0", {}, 0, 100, 3, L"Sending a window"},
{K::Choice, L"modifierKeys", L"Send to monitor with arrow keys", L"Hold these and press an arrow key to send the active window to another monitor. Off by default, since Alt+Shift+number does it. Ctrl + Shift also selects text word by word in editors.", L"none", {{L"none", L"Off"}, {L"ctrl_alt", L"Ctrl + Alt"}, {L"ctrl_shift", L"Ctrl + Shift"}, {L"alt_shift", L"Alt + Shift"}, {L"ctrl_alt_shift", L"Ctrl + Alt + Shift"}}, 0, 100, 3, L"Monitor keys with arrows (old way)"},
{K::Check, L"aroundMain", L"Treat the main monitor as the middle", L"When on, Down sends the window to the main monitor and the other arrows to the monitor above, left or right of it, wherever the window is now. When off, the arrows go from the window's current monitor.", L"1", {}, 0, 100, 3, L"Monitor keys with arrows (old way)"},
{K::Number, L"targetUp", L"Up arrow goes to monitor", L"-1 picks the nearest monitor above. 0 is the first monitor Windows lists, 1 the second, and so on. -1 to 9 (Suggested: -1).", L"-1", {}, -1, 9, 3, L"Monitor keys with arrows (old way)"},
{K::Number, L"targetDown", L"Down arrow goes to monitor", L"-1 picks the nearest monitor below. 0 is the first monitor Windows lists, 1 the second, and so on. -1 to 9 (Suggested: -1).", L"-1", {}, -1, 9, 3, L"Monitor keys with arrows (old way)"},
{K::Number, L"targetLeft", L"Left arrow goes to monitor", L"-1 picks the nearest monitor to the left. 0 is the first monitor Windows lists, 1 the second, and so on. -1 to 9 (Suggested: -1).", L"-1", {}, -1, 9, 3, L"Monitor keys with arrows (old way)"},
{K::Number, L"targetRight", L"Right arrow goes to monitor", L"-1 picks the nearest monitor to the right. 0 is the first monitor Windows lists, 1 the second, and so on. -1 to 9 (Suggested: -1).", L"-1", {}, -1, 9, 3, L"Monitor keys with arrows (old way)"},
{K::Choice, L"focus.followCursor", L"Focus follows the mouse", L"Hovering a window makes it the active one, so you can type into it without clicking. Leave as Windows has it keeps your Windows setting.", L"windows", {{L"windows", L"Leave as Windows has it"}, {L"hover", L"On, keep the window where it is"}, {L"raise", L"On, and bring the window to the front"}}, 0, 100, 4, L"Focus"},
{K::Number, L"focus.followDelay", L"Hover time (ms)", L"How long the mouse rests on a window before it becomes active. 10 to 1000 (Suggested: 150).", L"150", {}, 10, 1000, 4, L"Focus"},
{K::Choice, L"focus.cursorJump", L"Move the mouse to the active window", L"After you switch windows with the keyboard, such as Alt+Tab, the mouse pointer jumps to the middle of the new window. It never moves while a mouse button is down or when the pointer is already on that window.", L"never", {{L"never", L"Never"}, {L"monitor", L"Only when the window is on another monitor"}, {L"window", L"Every time the active window changes"}}, 0, 100, 4, L"Focus"},
{K::Hotkey, L"hotkeyFocusLeft", L"Focus the window to the left", L"Switches to the nearest window on that side, even on another monitor, and the mouse pointer jumps to it. Taking Alt+Left and Alt+Right means browsers and File Explorer lose them for Back and Forward.", L"Alt+Left", {}, 0, 100, 4, L"Focus keys"},
{K::Hotkey, L"hotkeyFocusRight", L"Focus the window to the right", L"", L"Alt+Right", {}, 0, 100, 4, L"Focus keys"},
{K::Hotkey, L"hotkeyFocusUp", L"Focus the window above", L"", L"Alt+Up", {}, 0, 100, 4, L"Focus keys"},
{K::Hotkey, L"hotkeyFocusDown", L"Focus the window below", L"", L"Alt+Down", {}, 0, 100, 4, L"Focus keys"},
{K::Hotkey, L"hotkeyFocusLast", L"Focus the last window", L"Goes back to the window you used before. Press again to come back.", L"Alt+Shift+L", {}, 0, 100, 4, L"Focus keys"},
{K::Check, L"agentWindows.enabled", L"Keep agent windows out of the way", L"Windows that coding agents open, and everything they start, never take the keyboard, the mouse or the window in front. They open on a monitor you are not using. Clicking one still makes it active as normal.", L"1", {}, 0, 100, 4, L"Agent windows"},
{K::Choice, L"agentWindows.screen", L"Where agent windows open", L"Never the monitor with the window you are using or the mouse pointer.", L"side", {{L"side", L"The biggest other monitor"}, {L"left", L"The leftmost other monitor"}, {L"right", L"The rightmost other monitor"}, {L"top", L"The highest other monitor"}, {L"none", L"Where the app puts them"}}, 0, 100, 4, L"Agent windows"},
{K::Text, L"agentWindows.apps", L"Agent programs", L"Everything these programs start counts as an agent window. Separate names with commas. Agents T3 Code runs through node also count.", L"claude.exe, codex.exe, opencode.exe, gemini.exe, grok.exe", {}, 0, 100, 4, L"Agent windows"},
{K::Number, L"effects.animation", L"Animation length (ms)", L"How long windows take to glide into place when they tile, float, fill, snap or go borderless. 0 turns it off. 0 to 400 (Suggested: 180).", L"180", {}, 0, 400, 5, L"Animation and fade"},
{K::Choice, L"effects.focusAnimation", L"Focus animation", L"What the window you jump to with the focus keys (Alt+arrows, Alt+1 to 4, Alt+Page Up or Down) does. Ring: a blue to mauve outline closes in on its edge and fades, and the window itself stays still. Zoom in: the window grows in from slightly smaller, like Alt+Tab.", L"ring", {{L"ring", L"Ring"}, {L"zoom", L"Zoom in"}, {L"off", L"Off"}}, 0, 100, 5, L"Animation and fade"},
{K::Number, L"effects.inactiveOpacity", L"Fade windows you are not using (%)", L"Makes every window except the active one see-through. 100 turns this off. 30 to 100 (Suggested: 92).", L"100", {}, 30, 100, 5, L"Animation and fade"},
{K::Choice, L"effects.statusPopup", L"Show a popup when pausing", L"A small popup when you pause or resume, and while keyboard resize is on.", L"show", {{L"show", L"Show"}, {L"hide", L"Hide"}}, 0, 100, 5, L"Animation and fade"},
{K::Check, L"gameGuard.enabled", L"Stay out of games", L"On, the per-app part of this mod does not load into games or their anti-cheat, so it cannot cause stutter or a ban. Launchers such as Steam keep it. Applies the next time an app starts (Suggested: on).", L"1", {}, 0, 100, 7, L"Game guard"},
{K::Text, L"gameGuard.allow", L"Always allow these apps", L"Apps to keep even when they look like a game. Process names separated by commas, for example MyTool.exe, Editor*.exe. The * works as a wildcard.", L"", {}, 0, 100, 7, L"Game guard"},
{K::Text, L"gameGuard.skip", L"Also skip these apps", L"Extra apps to leave alone, written the same way.", L"", {}, 0, 100, 7, L"Game guard"},
{K::Check, L"settingsGlass", L"Blurred settings window", L"On, the settings window is see-through glass with Windows acrylic behind it. Off, it is solid. Applies when you save.", L"1", {}, 0, 100, 7, L"Settings window"},
{K::Check, L"nativeSettingsTitleBar", L"Native Windows title bar", L"Use the Windows title bar and window buttons for this settings window. Applies when you save.", L"0", {}, 0, 100, 7, L"Settings window"},
{K::Check, L"settingsTrayIcon", L"Tray icon", L"A window manager icon in the system tray. Click it to open these settings, right-click it for a menu.", L"1", {}, 0, 100, 7, L"Settings window"}
    };
    Dyn_AddFields(out);
    return out;
}

struct SetPageInfo {
    PCWSTR name, intro;
    WCHAR glyph;
};
static const SetPageInfo kSetPages[] = {
{L"Keys", L"Snap keys and window keys. To record a key the mod already uses, pause the window manager first.", 0xE765},
{L"Mouse", L"Move and resize windows with the mouse, and what clicks do.", 0xE962},
{L"Tiling and gaps", L"How windows tile, and the space around them.", 0xF0E2},
{L"Monitors", L"Monitor and desktop keys, and windows sent to another monitor.", 0xE7F4},
{L"Focus", L"Which window is active, and keys to move between windows.", 0xE8B0},
{L"Animation and fade", L"Gliding windows, the focus effect and see-through background windows.", 0xE945},
{L"Rules", L"Place, pin or skip chosen apps automatically.", 0xE71C},
{L"Look", L"How this window looks, and its tray icon.", 0xE790},
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
// Middle-click autoscroll: no movement inside kSetAutoDead, then speed grows with distance.
constexpr float kSetAutoDead = 10, kSetAutoR = 18, kSetAutoGain = 0.14f, kSetAutoMax = 56;
constexpr PCWSTR kSetAutoProp = L"SeamlessOwnAutoscroll";  // Seamless Autoscroll skips this window.
constexpr PCWSTR kSetKofiUrl = L"https://ko-fi.com/DavidHiFi";
constexpr PCWSTR kSetAuthorUrl = L"https://github.com/DavidHiFi";
constexpr PCWSTR kSetDittoUrl = L"https://windhawk.net/mods/alt-drag";
constexpr PCWSTR kSetSnapUrl = L"https://windhawk.net/mods/snap-commander";
constexpr PCWSTR kSetMonitorUrl = L"https://windhawk.net/mods/move-window-to-monitor";
constexpr PCWSTR kSetGlazeUrl = L"https://github.com/glzr-io/glazewm";
constexpr PCWSTR kSetRepoUrl = L"https://github.com/DavidHiFi/davids-windhawk-mods";
constexpr PCWSTR kSetBugUrl =
    L"https://github.com/DavidHiFi/davids-windhawk-mods/issues/new?title=%5BSeamless%20Window%20Manager%5D%20";
constexpr PCWSTR kSetTitle = L"Seamless Window Manager";
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
        if (w.fRailName && Set_TextW(w.fRailName.get(), L"Window Manager") <= railW) break;
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
        if (Dyn_IsVirtual(f.key)) {  // The blank new entry and the remove switches.
            Set_PutValue(f, f.def);
            f.value = Set_FieldValue(f);
            continue;
        }
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
        add(SetItem::Link, 56, L"Based on AltDrag by m417z", L"Inspired by AltSnap by Stefan Sundin and RamonUnch", kSetDittoUrl);
        add(SetItem::Link, 56, L"Snap Commander by Asteski", L"The snap keys", kSetSnapUrl);
        add(SetItem::Link, 56, L"Move Window to Monitor by TomberWolf", L"The monitor keys", kSetMonitorUrl);
        add(SetItem::Link, 56, L"Tiling ideas from GlazeWM", L"By Lars Berger and contributors. No GlazeWM code is used.", kSetGlazeUrl);
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
        const WCHAR glyph = 0xF0E2;
        auto br = p.G({mc.x - 19, mc.y - 19, mc.x + 19, mc.y + 19});
        if (br) p.rt->DrawText(&glyph, 1, w.fIconL.get(), mark, br.get());
        p.rt->SetTransform(old);
    }
    float x = mark.right + 20;
    p.Text(w.fBig.get(), L"Seamless Window Manager", {x, row.top + 18, row.right - 16, row.top + 46}, mocha::text);
#ifdef WH_MOD_VERSION
    std::wstring ver = std::wstring(L"Version ") + WH_MOD_VERSION + L"  \u00B7  MIT license  \u00B7  A Windhawk mod";
#else
    std::wstring ver = L"MIT license  \u00B7  A Windhawk mod";
#endif
    p.Text(w.fHint.get(), ver, {x, row.top + 48, row.right - 16, row.top + 68}, mocha::subtext0);
    p.Text(w.fHint.get(), L"Move, resize, snap, tile and focus windows with the mouse or keyboard.",
           {x, row.top + 72, row.right - 16, row.top + 110}, mocha::subtext1);
    p.Text(w.fHint.get(), L"Made by DavidHiFi, based on AltDrag, Snap Commander and Move Window to Monitor.",
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
    p.Text(w.fRailName.get(), L"Window Manager", {d.left + 90, d.top + 32, d.left + w.railW - 10, d.top + 56}, mocha::text, textA);
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
    const WCHAR mark = 0xF0E2;
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

// ---- The two lists: app rules and apps that never tile -----------------------------------------
// Each stored entry gets its own rows and one blank entry adds a new one. A list entry's
// "suggested" value is what is stored, so Reset to suggested never wipes the lists.
static PCWSTR Dyn_Str(const std::wstring& s) {
    static std::set<std::wstring> pool;  // Field keys and labels must outlive every rebuild.
    return pool.insert(s).first->c_str();
}
static bool Dyn_Blank(const std::wstring& s) { return s.find_first_not_of(L" \t") == std::wstring::npos; }
static std::wstring Dyn_Rule(int i, PCWSTR field) {
    return GetStringSetting((L"rules[" + std::to_wstring(i) + L"]." + field).c_str());
}
// Rows show the stored rules up to the last one that matches something; ParseRules reads the
// same way and stops after three blank entries in a row.
static int Dyn_RuleCount() {
    int last = -1, lastUsed = -1;
    for (int i = 0; i <= 255; i++) {
        bool match = !Dyn_Blank(Dyn_Rule(i, L"executable_names")) || !Dyn_Rule(i, L"window_title").empty() ||
                     !Dyn_Rule(i, L"window_class").empty();
        if (!match && Dyn_Rule(i, L"action").empty()) {
            if (i - lastUsed > 2) break;
            continue;
        }
        lastUsed = i;
        if (match) last = i;
    }
    return last + 1;
}
static int Dyn_AppCount() {
    int last = -1;
    for (int i = 0; i < 200; i++)
        if (!Dyn_Blank(GetStringSetting((L"tiling.floatApps[" + std::to_wstring(i) + L"]").c_str()))) last = i;
    return last + 1;
}
static bool Dyn_IsVirtual(PCWSTR key) { return wcsstr(key, L"[new]") || wcsstr(key, L".__"); }

static void Dyn_AddFields(std::vector<SetField>& out) {
    using K = SetField;
    static const std::vector<SetField> proto = {
{K::Text, L"executable_names", L"App file names", L"One or more app file names, separate with semicolons, such as \"notepad; calc.exe\". Upper or lower case both work and \".exe\" is optional. Use * for every app. Leave empty to match by title or class only.", L"", {}, 0, 100, 6, L""},
{K::Text, L"window_title", L"Window title", L"Text in the window's title. Leave empty to match any title.", L"", {}, 0, 100, 6, L""},
{K::Text, L"window_class", L"Window class (advanced)", L"Leave empty to match any class.", L"", {}, 0, 100, 6, L""},
{K::Choice, L"match_mode", L"Title and class match", L"", L"contains", {{L"contains", L"Contains the text"}, {L"equals", L"Is exactly the text"}, {L"regex", L"Matches a pattern (regex)"}, {L"not_regex", L"Does not match a pattern (regex)"}}, 0, 100, 6, L""},
{K::Choice, L"action", L"Action", L"", L"maximize", {{L"left-half", L"Left half"}, {L"right-half", L"Right half"}, {L"top-half", L"Top half"}, {L"bottom-half", L"Bottom half"}, {L"center-half", L"Center half"}, {L"top-left", L"Top-left quarter"}, {L"top-right", L"Top-right quarter"}, {L"bottom-left", L"Bottom-left quarter"}, {L"bottom-right", L"Bottom-right quarter"}, {L"maximize", L"Maximize"}, {L"almost-maximize", L"Almost maximize"}, {L"center", L"Center"}, {L"minimize", L"Minimize"}, {L"left-third", L"Left third"}, {L"center-third", L"Middle third"}, {L"right-third", L"Right third"}, {L"monitor-1", L"Monitor 1"}, {L"monitor-2", L"Monitor 2"}, {L"monitor-3", L"Monitor 3"}, {L"monitor-4", L"Monitor 4"}, {L"float", L"Never tile, leave it floating"}, {L"none", L"Leave the position alone"}, {L"ignore", L"Leave this app alone completely"}}, 0, 100, 6, L""},
{K::Check, L"no_resize", L"Keep the window size", L"Moves the window into place but keeps its size. Has no effect on Minimize.", L"0", {}, 0, 100, 6, L""},
{K::Choice, L"apply_when", L"When to apply", L"", L"open", {{L"open", L"On open, and for windows already open"}, {L"new", L"On open only"}, {L"title", L"On open and when the title changes"}}, 0, 100, 6, L""},
{K::Check, L"on_top", L"Keep on top", L"Keeps the window above other windows.", L"0", {}, 0, 100, 6, L""},
{K::Number, L"opacity", L"Opacity (%)", L"Makes the window see-through. 100 leaves it solid. 30 to 100 (Suggested: 100).", L"100", {}, 30, 100, 6, L""}
    };
    int rules = Dyn_RuleCount();
    for (int i = 0; i <= rules; i++) {
        bool add = i == rules;
        std::wstring prefix = add ? L"rules[new]." : L"rules[" + std::to_wstring(i) + L"].";
        PCWSTR group = Dyn_Str(add ? std::wstring(L"Add a rule") : L"Rule " + std::to_wstring(i + 1));
        for (const SetField& p : proto) {
            SetField f = p;
            f.key = Dyn_Str(prefix + p.key);
            f.group = group;
            if (!add) {
                bool isInt = f.kind == K::Number || f.kind == K::Check;
                f.def = Dyn_Str(isInt ? std::to_wstring(Wh_GetIntSetting(f.key)) : GetStringSetting(f.key));
            }
            if (i > 0 && f.desc && !add) f.desc = L"";
            out.push_back(f);
        }
        if (!add)
            out.push_back({K::Check, Dyn_Str(prefix + L"__remove"), L"Remove this rule",
                           L"Turn on and press Save to delete this rule.", L"0", {}, 0, 100, 6, group});
    }
    int apps = Dyn_AppCount();
    for (int i = 0; i <= apps; i++) {
        bool add = i == apps;
        PCWSTR key = Dyn_Str(add ? std::wstring(L"tiling.floatApps[new]") : L"tiling.floatApps[" + std::to_wstring(i) + L"]");
        out.push_back({K::Text, key, Dyn_Str(add ? std::wstring(L"Add an app") : L"App " + std::to_wstring(i + 1)),
                       i == 0 ? L"One app name per entry, such as \"steam\" or \"obs64\". These always open floating. Apps with a placement rule never tile either." : L"",
                       add ? L"" : Dyn_Str(GetStringSetting(key)), {}, 0, 100, 6, L"Apps that never tile"});
    }
}

// Writes both lists back packed: removed and emptied entries drop out, the new one goes last,
// only values that differ from what is stored are sent, and leftover entries at the end are
// emptied (a rule with nothing to match on is skipped).
static void Dyn_Params(SetWindow& w, std::wstring& params, int& changed) {
    auto put = [&](const std::wstring& key, const std::wstring& value) {
        params += L" " + Set_QuoteArg(key + L"=" + value);
        changed++;
    };
    std::map<int, std::map<std::wstring, const SetField*>> rules;  // Index (-1 = the new one), field.
    std::map<int, const SetField*> apps;
    for (const auto& f : w.fields) {
        std::wstring k = f.key;
        bool isRule = k.rfind(L"rules[", 0) == 0, isApp = k.rfind(L"tiling.floatApps[", 0) == 0;
        if (!isRule && !isApp) continue;
        size_t open = k.find(L'['), close = k.find(L']');
        std::wstring idx = k.substr(open + 1, close - open - 1);
        int i = idx == L"new" ? -1 : _wtoi(idx.c_str());
        if (isRule) rules[i][k.substr(close + 2)] = &f;
        else apps[i] = &f;
    }
    auto val = [](const std::map<std::wstring, const SetField*>& m, PCWSTR name) {
        auto it = m.find(name);
        return it == m.end() ? std::wstring() : Set_FieldValue(*it->second);
    };
    std::vector<const std::map<std::wstring, const SetField*>*> keep;
    int stored = 0;
    for (const auto& [i, m] : rules) {
        if (i < 0) continue;
        stored = i + 1;
        if (val(m, L"__remove") != L"1") keep.push_back(&m);
    }
    if (auto it = rules.find(-1); it != rules.end()) {
        const auto& m = it->second;
        if (!Dyn_Blank(val(m, L"executable_names")) || !val(m, L"window_title").empty() || !val(m, L"window_class").empty())
            keep.push_back(&m);
    }
    for (int j = 0; j < (int)keep.size(); j++) {
        auto old = rules.find(j);
        for (const auto& [name, f] : *keep[j]) {
            if (name == L"__remove") continue;
            std::wstring v = Set_FieldValue(*f);
            const SetField* o = nullptr;
            if (old != rules.end()) {
                auto it = old->second.find(name);
                if (it != old->second.end()) o = it->second;
            }
            if (!o || o->value != v) put(L"rules[" + std::to_wstring(j) + L"]." + name, v);
        }
    }
    for (int j = (int)keep.size(); j < stored; j++)
        for (PCWSTR name : {L"executable_names", L"window_title", L"window_class"})
            if (!rules[j].count(name) || !rules[j][name]->value.empty())
                put(L"rules[" + std::to_wstring(j) + L"]." + name, L"");

    std::vector<std::wstring> list;
    int storedApps = 0;
    for (const auto& [i, f] : apps) {
        if (i >= 0) storedApps = i + 1;
        std::wstring v = Set_FieldValue(*f);
        if (!Dyn_Blank(v) && i >= 0) list.push_back(v);
    }
    if (auto it = apps.find(-1); it != apps.end() && !Dyn_Blank(Set_FieldValue(*it->second)))
        list.push_back(Set_FieldValue(*it->second));
    for (int j = 0; j < std::max((int)list.size(), storedApps); j++) {
        std::wstring v = j < (int)list.size() ? list[j] : L"";
        auto it = apps.find(j);
        if (it == apps.end() || it->second->value != v) put(L"tiling.floatApps[" + std::to_wstring(j) + L"]", v);
    }
}

static std::wstring Set_ChangedParams(SetWindow& w, int& changed) {
    std::wstring params = L"--quiet mod settings set " + Set_QuoteArg(WH_MOD_ID);
    changed = 0;
    for (auto& f : w.fields) {
        if (wcschr(f.key, L'[')) continue;  // The two lists, written below.
        std::wstring value = Set_FieldValue(f);
        if (value != f.value) {
            params += L" " + Set_QuoteArg(std::wstring(f.key) + L"=" + value);
            changed++;
        }
    }
    Dyn_Params(w, params, changed);
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
        w.fields = Set_MakeFields();  // The lists may have grown or shrunk.
        w.focus = -1;
        Set_LoadFields(w);  // Shows what was stored.
        Set_BuildAndClamp(w);
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
                Set_CommitEdit(*w, false);
                Set_StopRecording(*w);
                Set_ClosePopup(*w);
                w->fields = Set_MakeFields();
                w->focus = -1;
                Set_LoadFields(*w);
                Set_BuildAndClamp(*w);
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
    HWND hwnd = CreateWindowExW(0, kSettingsClass, L"Seamless Window Manager settings", style,
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
}  // namespace swmset

// ---- Tray icon -----------------------------------------------------------------------------
// Runs in the elevated helper only, on its own thread. Click: the settings window. Right-click:
// the shared menu (Set_TrayMenu). Grey while the window manager is paused.
namespace swmtray {
constexpr UINT kTrayMsg = WM_APP + 45;
constexpr UINT kTrayId = 1;
HANDLE g_thread;
DWORD g_threadId;
HWND g_wnd;
UINT g_taskbarCreated;
bool g_added;
HICON g_icon;

static HICON MakeTrayIcon_Big(bool off) {
    int size = GetSystemMetricsForDpi(SM_CXICON, GetDpiForSystem()) * 4;
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
    SetBkMode(dc, TRANSPARENT);
    SetTextColor(dc, RGB(255, 255, 255));
    RECT r{0, 0, size, size};
    WCHAR g[2] = {(WCHAR)0xF0E2, 0};  // Tiles: the window manager.
    DrawTextW(dc, g, 1, &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE | DT_NOPREFIX);
    GdiFlush();
    SelectObject(dc, oldFont);
    DeleteObject(font);
    SelectObject(dc, old);
    DeleteDC(dc);

    // The glyph: blue 0x89B4FA to mauve 0xCBA6F7, grey while paused.
    const float c0[3] = {off ? 0x6C / 255.f : 0x89 / 255.f, off ? 0x70 / 255.f : 0xB4 / 255.f, off ? 0x86 / 255.f : 0xFA / 255.f};
    const float c1[3] = {off ? 0x58 / 255.f : 0xCB / 255.f, off ? 0x5B / 255.f : 0xA6 / 255.f, off ? 0x70 / 255.f : 0xF7 / 255.f};
    uint32_t* px = (uint32_t*)bits;
    const uint32_t* gp = (const uint32_t*)glyphBits;
    for (int y = 0; y < size; y++)
        for (int x = 0; x < size; x++) {
            float t = std::clamp((x + y) / (2.0f * (size - 1)), 0.0f, 1.0f);
            float cov = ((gp[y * size + x] >> 8) & 0xFF) / 255.0f;
            float rgb[3];
            for (int i = 0; i < 3; i++) {
                float base = c0[i] + (c1[i] - c0[i]) * t;
                rgb[i] = base * cov;
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

// Drawn at 4x and shrunk, so the icon is smooth at the size it is shown.
static HICON MakeTrayIcon(bool off) { return Crisp_ShrinkIcon(MakeTrayIcon_Big(off), 4); }

static void Update(bool add) {
    NOTIFYICONDATAW nid{sizeof(nid)};
    nid.hWnd = g_wnd;
    nid.uID = kTrayId;
    if (!Wh_GetIntSetting(L"settingsTrayIcon")) {
        if (g_added) Shell_NotifyIconW(NIM_DELETE, &nid);
        g_added = false;
        return;
    }
    bool paused = swm::g_paused;
    HICON icon = MakeTrayIcon(paused);
    nid.uFlags = NIF_MESSAGE | NIF_ICON | NIF_TIP | NIF_SHOWTIP;
    nid.uCallbackMessage = kTrayMsg;
    nid.hIcon = icon ? icon : LoadIconW(nullptr, IDI_APPLICATION);
    wcsncpy_s(nid.szTip, paused ? L"Seamless Window Manager: paused" : L"Seamless Window Manager", _TRUNCATE);
    if (!g_added || add) {
        if (g_added) Shell_NotifyIconW(NIM_DELETE, &nid);
        g_added = Shell_NotifyIconW(NIM_ADD, &nid) != FALSE;
        if (g_added) {
            nid.uVersion = NOTIFYICON_VERSION_4;
            Shell_NotifyIconW(NIM_SETVERSION, &nid);
        }
    } else {
        Shell_NotifyIconW(NIM_MODIFY, &nid);
    }
    if (g_icon) DestroyIcon(g_icon);
    g_icon = icon;
}

static void ShowMenu(POINT at) {
    using namespace swmset;
    bool paused = swm::g_paused;
    std::wstring key = GetStringSetting(L"hotkeyPause");
    int pick = Set_TrayMenu(g_wnd, {Set_MenuRow(1, L"\uEB51", L"Settings"), Set_MenuSep(),
                                    Set_MenuRow(2, paused ? L"\uE768" : L"\uE769",
                                                paused ? L"Resume the window manager" : L"Pause the window manager",
                                                false, false, key.c_str())},
                            &at);
    if (pick == 1) OpenSettingsWindow();
    // The pause key's own path, so the pause runs on the thread that owns it.
    if (pick == 2 && altSnapDrag::g_lowLevelMouseHookOwnThreadId)
        PostThreadMessageW(altSnapDrag::g_lowLevelMouseHookOwnThreadId, WM_HOTKEY, swm::kModeKeyBase, 0);
}

static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp) {
    if (msg == g_taskbarCreated && g_taskbarCreated) {
        g_added = false;
        Update(true);
        return 0;
    }
    switch (msg) {
        case swm::kTrayUpdateMessage:
            Update(false);
            return 0;
        case kTrayMsg:
            switch (LOWORD(lp)) {
                case NIN_SELECT:
                case NIN_KEYSELECT: swmset::OpenSettingsWindow(); break;
                case WM_CONTEXTMENU: ShowMenu(POINT{GET_X_LPARAM(wp), GET_Y_LPARAM(wp)}); break;
            }
            return 0;
        case WM_CLOSE:
            DestroyWindow(hwnd);
            return 0;
        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;
    }
    return DefWindowProcW(hwnd, msg, wp, lp);
}

static DWORD WINAPI Thread(LPVOID) {
    SetThreadDpiAwarenessContext(DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2);
    HRESULT com = CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED);
    HINSTANCE inst = (HINSTANCE)&__ImageBase;
    WNDCLASSW wc{};
    wc.lpfnWndProc = WndProc;
    wc.hInstance = inst;
    wc.lpszClassName = L"SeamlessWindowManagerTray";
    RegisterClassW(&wc);
    g_wnd = CreateWindowExW(WS_EX_TOOLWINDOW, wc.lpszClassName, L"Seamless Window Manager", WS_POPUP, 0, 0, 0, 0,
                            nullptr, nullptr, inst, nullptr);
    if (g_wnd) {
        g_taskbarCreated = RegisterWindowMessageW(L"TaskbarCreated");
        ChangeWindowMessageFilterEx(g_wnd, g_taskbarCreated, MSGFLT_ALLOW, nullptr);
        swm::g_trayWnd = g_wnd;
        Update(true);
        MSG msg;
        while (GetMessageW(&msg, nullptr, 0, 0) > 0) {
            TranslateMessage(&msg);
            DispatchMessageW(&msg);
        }
    }
    swm::g_trayWnd = nullptr;
    if (g_added) {
        NOTIFYICONDATAW nid{sizeof(nid)};
        nid.hWnd = g_wnd;
        nid.uID = kTrayId;
        Shell_NotifyIconW(NIM_DELETE, &nid);
        g_added = false;
    }
    if (g_icon) DestroyIcon(g_icon);
    g_icon = nullptr;
    if (g_wnd && IsWindow(g_wnd)) DestroyWindow(g_wnd);
    g_wnd = nullptr;
    UnregisterClassW(wc.lpszClassName, inst);
    if (SUCCEEDED(com)) CoUninitialize();
    return 0;
}

static void Start() {
    if (!g_thread) g_thread = CreateThread(nullptr, 0, Thread, nullptr, 0, &g_threadId);
}

static void Stop() {
    if (!g_thread) return;
    if (HWND w = g_wnd) PostMessageW(w, WM_CLOSE, 0, 0);
    else PostThreadMessageW(g_threadId, WM_QUIT, 0, 0);
    if (WaitForSingleObject(g_thread, 5000) == WAIT_TIMEOUT) Wh_Log(L"Tray thread did not stop in 5 seconds");
    CloseHandle(g_thread);
    g_thread = nullptr;
    g_threadId = 0;
}

static void OnSettingsChanged() {
    if (HWND w = g_wnd) PostMessageW(w, swm::kTrayUpdateMessage, 0, 0);
    if (HWND s = swmset::g_settingsWnd) PostMessageW(s, WM_APP + 1 /* WM_APP_SETTINGS_RELOAD */, 0, 0);
}
}  // namespace swmtray
// ==== SWM settings window (generated) end ====

// After the elevated relaunch, Windhawk can load this mod a moment late when
// the PC is busy. windhawk-mod.exe then shows a false "Running the tool mod
// failed" box although the mod loads and works. Close that box, only in this
// process, during the first 15 seconds.
static BOOL CALLBACK CloseFalseFailureBox(HWND hwnd, LPARAM) {
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

static DWORD WINAPI FalseFailureBoxThreadProc(LPVOID) {
    for (int i = 0; i < 60; i++) {
        EnumWindows(CloseFalseFailureBox, 0);
        Sleep(250);
    }
    return 0;
}

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
        // Returning FALSE exits with code 1, which Windhawk reports as a
        // failed tool mod. The admin copy takes over, so leave cleanly.
        if (ShellExecuteExW(&launch)) ExitProcess(0);
        return FALSE;
    }
    if (HANDLE boxThread = CreateThread(nullptr, 0, FalseFailureBoxThreadProc, nullptr, 0, nullptr)) {
        CloseHandle(boxThread);
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
        swmtray::Start();
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
    swmtray::OnSettingsChanged();
}

void WhTool_ModUninit() {
    swmset::CloseSettingsWindow();
    swmtray::Stop();
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

// ==== Agent windows ====
// Windows that coding agents (and everything they start) open never take the keyboard, the mouse
// or the foreground, and they open on a monitor the owner is not using. Runs in every process; the
// hooks go in only where the process descends from an agent program. SWM_AGENT_QUIET=1 is passed
// down to children so a broken parent chain still counts, and =0 opts a launch out on purpose.
// While an agent holds the coop desktop lock with --input (owner away, not gaming), focus and
// input are let through.
namespace agentQuiet {

bool g_active = false;
bool g_enabled = false;
// Input pass of this process: the lock's acquire time, that time as a tick, and the tick of this
// process's own last injected input.
double g_passAcquired = 0;
DWORD g_passTick = 0;
DWORD g_agentTick = 0;
bool g_touchLogged = false;
int g_screen = 0;  // 0 side, 1 left, 2 right, 3 top, -1 leave where the app puts it
std::vector<std::wstring> g_apps;
std::vector<DWORD> g_ancestors;

constexpr WCHAR kEnv[] = L"SWM_AGENT_QUIET";
constexpr WCHAR kPlaced[] = L"SwmAgentPlaced";

// The owner's shell and Windows' own UI never go quiet, and they drop the marker so apps the
// owner opens from an Explorer an agent restarted still behave normally.
constexpr PCWSTR kNeverQuiet[] = {
    L"explorer.exe", L"dwm.exe", L"sihost.exe", L"windhawk.exe", L"shellexperiencehost.exe",
    L"startmenuexperiencehost.exe", L"searchhost.exe", L"textinputhost.exe", L"ctfmon.exe",
    L"applicationframehost.exe", L"lockapp.exe", L"logonui.exe", L"consent.exe",
    L"credentialuibroker.exe", L"t3 code.exe", L"t3 code (nightly).exe",
};

std::wstring Lower(std::wstring s) {
    for (auto& c : s) c = (WCHAR)towlower(c);
    return s;
}

std::wstring Trim(const std::wstring& s) {
    size_t a = s.find_first_not_of(L" \t\r\n"), b = s.find_last_not_of(L" \t\r\n");
    return a == std::wstring::npos ? L"" : s.substr(a, b - a + 1);
}

std::wstring ExeOf(HANDLE process) {
    WCHAR path[MAX_PATH]{};
    DWORD n = ARRAYSIZE(path);
    if (!QueryFullProcessImageNameW(process, 0, path, &n)) return L"";
    return Lower(PathFindFileNameW(path));
}

std::wstring StringSetting(PCWSTR name) {
    PCWSTR p = Wh_GetStringSetting(name);
    std::wstring s = p ? p : L"";
    if (p) Wh_FreeStringSetting(p);
    return s;
}

void LoadSettings() {
    g_enabled = Wh_GetIntSetting(L"agentWindows.enabled") != 0;
    std::wstring screen = StringSetting(L"agentWindows.screen");
    g_screen = screen == L"left" ? 1 : screen == L"right" ? 2 : screen == L"top" ? 3
             : screen == L"none" ? -1 : 0;
    std::wstring apps = StringSetting(L"agentWindows.apps");
    g_apps.clear();
    size_t i = 0;
    while (i <= apps.size()) {
        size_t j = apps.find_first_of(L",;", i);
        if (j == std::wstring::npos) j = apps.size();
        std::wstring t = Lower(Trim(apps.substr(i, j - i)));
        if (!t.empty()) {
            if (t.size() < 4 || t.compare(t.size() - 4, 4, L".exe") != 0) t += L".exe";
            g_apps.push_back(t);
        }
        i = j + 1;
    }
}

bool IsAgentExe(const std::wstring& exe) {
    for (auto& a : g_apps)
        if (exe == a) return true;
    return false;
}

struct BasicInfo {
    PVOID exitStatus;
    PVOID peb;
    ULONG_PTR affinity;
    PVOID basePriority;
    ULONG_PTR pid;
    ULONG_PTR parent;
};
using NtQueryInformationProcess_t = LONG(NTAPI*)(HANDLE, ULONG, PVOID, ULONG, PULONG);

// Walks up the parent chain. A parent created after its child is a reused process id: stop.
bool FromAgent() {
    auto query = (NtQueryInformationProcess_t)GetProcAddress(GetModuleHandleW(L"ntdll.dll"),
                                                             "NtQueryInformationProcess");
    if (!query) return false;
    FILETIME created{}, x1, x2, x3;
    if (!GetProcessTimes(GetCurrentProcess(), &created, &x1, &x2, &x3)) return false;
    std::wstring below = ExeOf(GetCurrentProcess());
    HANDLE h = GetCurrentProcess();
    bool own = false, found = false;
    for (int depth = 0; depth < 24 && !found; depth++) {
        BasicInfo bi{};
        LONG st = query(h, 0, &bi, sizeof(bi), nullptr);
        if (own) CloseHandle(h);
        own = false;
        if (st < 0 || !bi.parent) break;
        HANDLE p = OpenProcess(PROCESS_QUERY_LIMITED_INFORMATION, FALSE, (DWORD)bi.parent);
        if (!p) break;
        h = p;
        own = true;
        FILETIME pc{};
        if (!GetProcessTimes(p, &pc, &x1, &x2, &x3) || CompareFileTime(&pc, &created) > 0) break;
        created = pc;
        std::wstring exe = ExeOf(p);
        g_ancestors.push_back((DWORD)bi.parent);
        // Agents T3 Code runs through node or bun (Halo's harness) count as agents too.
        if (IsAgentExe(exe) ||
            ((below == L"node.exe" || below == L"bun.exe") && exe.rfind(L"t3 code", 0) == 0))
            found = true;
        below = exe;
    }
    if (own) CloseHandle(h);
    return found;
}

// --- When to stand aside -----------------------------------------------------------------------

DWORD LastInputAgeMs() {
    LASTINPUTINFO li{sizeof(li)};
    if (!GetLastInputInfo(&li)) return MAXDWORD;
    return GetTickCount() - li.dwTime;
}

// The owner is already in this app, or just clicked something in the app that started it
// (for example a link in T3 Code): then the window behaves normally.
bool OwnerIntent() {
    HWND fg = GetForegroundWindow();
    if (!fg) return false;
    DWORD pid = 0;
    GetWindowThreadProcessId(fg, &pid);
    if (pid == GetCurrentProcessId()) return true;
    if (LastInputAgeMs() > 1500) return false;
    for (DWORD a : g_ancestors)
        if (a == pid) return true;
    return false;
}

std::string ReadSmall(const std::wstring& path) {
    HANDLE f = CreateFileW(path.c_str(), GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE,
                           nullptr, OPEN_EXISTING, 0, nullptr);
    if (f == INVALID_HANDLE_VALUE) return "";
    char buf[4096];
    DWORD n = 0;
    BOOL ok = ReadFile(f, buf, sizeof(buf) - 1, &n, nullptr);
    CloseHandle(f);
    return ok ? std::string(buf, n) : "";
}

double JsonNumber(const std::string& s, const char* key) {
    size_t k = s.find(key);
    if (k == std::string::npos) return -1;
    size_t c = s.find(':', k);
    return c == std::string::npos ? -1 : strtod(s.c_str() + c + 1, nullptr);
}

bool JsonTrue(const std::string& s, const char* key) {
    size_t k = s.find(key);
    if (k == std::string::npos) return false;
    size_t c = s.find(':', k);
    if (c == std::string::npos) return false;
    size_t v = s.find_first_not_of(" \t\r\n", c + 1);
    return v != std::string::npos && s.compare(v, 4, "true") == 0;
}

// The pass belongs to the thread that took the lock: the lock's holder must be one of the
// thread ids in this process's environment (T3 and coop hand these down to everything an agent
// starts). Another thread's programs, and programs that carry no id, stay quiet.
bool LockIsMine(const std::string& lock) {
    size_t k = lock.find("\"agent\"");
    if (k == std::string::npos) return false;
    size_t c = lock.find(':', k);
    if (c == std::string::npos) return false;
    size_t q1 = lock.find('"', c + 1);
    if (q1 == std::string::npos) return false;
    size_t q2 = lock.find('"', q1 + 1);
    if (q2 == std::string::npos || q2 == q1 + 1) return false;
    std::string holder = lock.substr(q1 + 1, q2 - q1 - 1);
    for (const char* name : {"COOP_AGENT", "T3CODE_THREAD_ID", "T3_THREAD_ID", "CLAUDE_CODE_SESSION_ID",
                             "CLAUDE_SESSION_ID"}) {
        char v[256];
        DWORD n = GetEnvironmentVariableA(name, v, sizeof(v));
        if (n > 0 && n < sizeof(v) && holder == std::string(v, n)) return true;
    }
    return false;
}

// An agent holds the coop desktop lock with --input (owner away a minute) and the owner is not
// gaming: focus and input pass. Checked at most once a second.
bool InputPass() {
    static ULONGLONG lastCheck = 0;
    static bool last = false;
    ULONGLONG tick = GetTickCount64();
    if (lastCheck && tick - lastCheck < 1000) return last;
    lastCheck = tick;
    last = false;
    WCHAR base[MAX_PATH]{};
    WCHAR home[MAX_PATH]{};
    std::wstring dir;
    if (GetEnvironmentVariableW(L"COOP_HOME", home, MAX_PATH)) dir = home;
    else if (GetEnvironmentVariableW(L"LOCALAPPDATA", base, MAX_PATH)) dir = std::wstring(base) + L"\\agent-coop";
    else return false;
    std::string lock = ReadSmall(dir + L"\\projects\\machine\\locks\\desktop\\owner.json");
    if (lock.empty() || !JsonTrue(lock, "\"input\"")) return false;
    if (!LockIsMine(lock)) return false;
    FILETIME ft;
    GetSystemTimeAsFileTime(&ft);
    double unixNow = (double)((((ULONGLONG)ft.dwHighDateTime << 32) | ft.dwLowDateTime) -
                              116444736000000000ULL) / 1e7;
    double acquired = JsonNumber(lock, "\"acquired\""), ttl = JsonNumber(lock, "\"ttl\"");
    if (acquired <= 0 || ttl <= 0 || acquired + ttl < unixNow) return false;
    if (JsonTrue(ReadSmall(dir + L"\\guard.json"), "\"hands_off\"")) return false;
    if (acquired != g_passAcquired) {
        g_passAcquired = acquired;
        g_passTick = GetTickCount() - (DWORD)((unixNow - acquired) * 1000);
        g_agentTick = g_passTick;
        g_touchLogged = false;
    }
    last = true;
    return true;
}

// The owner touched the mouse or keys since the pass began: the session's last input is newer
// than this process's own last click, key or cursor move (100 ms slack, as Windows counts
// injected input a moment after the call returns). The lock is only granted after a minute
// without input, so anything later that is not ours is the owner, remote play and macro
// tools included. Works with an elevated window in front, where raw input never arrives.
// Once touched, the pass stays closed until the thread takes the lock again.
bool OwnerTouched() {
    LASTINPUTINFO li{sizeof(li)};
    if (!GetLastInputInfo(&li)) return true;
    if ((LONG)(li.dwTime - g_agentTick) <= 100) return false;
    if (!g_touchLogged) {
        g_touchLogged = true;
        Wh_Log(L"agent windows: owner touched the PC, input pass closed");
    }
    return true;
}

void MarkAgentInput() {
    if (g_passAcquired > 0) g_agentTick = GetTickCount();
}

bool Quiet() { return g_enabled && !OwnerIntent() && (!InputPass() || OwnerTouched()); }

// Only top-level windows take the foreground; child windows keep their own behaviour.
bool TopLevel(HWND h) { return h && !(GetWindowLongW(h, GWL_STYLE) & WS_CHILD); }

// --- Where new windows open --------------------------------------------------------------------

struct Mon {
    HMONITOR h;
    RECT work;
    bool primary;
};

BOOL CALLBACK AddMonitor(HMONITOR h, HDC, LPRECT, LPARAM lp) {
    MONITORINFO mi{sizeof(mi)};
    if (GetMonitorInfoW(h, &mi))
        ((std::vector<Mon>*)lp)->push_back({h, mi.rcWork, (mi.dwFlags & MONITORINFOF_PRIMARY) != 0});
    return TRUE;
}

// A monitor away from the window in front and from the mouse pointer.
bool TargetWork(RECT* out) {
    std::vector<Mon> mons;
    EnumDisplayMonitors(nullptr, nullptr, AddMonitor, (LPARAM)&mons);
    if (mons.size() < 2) return false;
    HWND fg = GetForegroundWindow();
    HMONITOR busy = fg ? MonitorFromWindow(fg, MONITOR_DEFAULTTOPRIMARY)
                       : MonitorFromPoint(POINT{0, 0}, MONITOR_DEFAULTTOPRIMARY);
    POINT pt{};
    GetCursorPos(&pt);
    HMONITOR pointer = MonitorFromPoint(pt, MONITOR_DEFAULTTONEAREST);
    std::vector<Mon> pick;
    for (auto& m : mons)
        if (m.h != busy && m.h != pointer) pick.push_back(m);
    if (pick.empty())
        for (auto& m : mons)
            if (m.h != busy) pick.push_back(m);
    if (pick.empty()) return false;
    auto area = [](const RECT& r) { return (LONGLONG)(r.right - r.left) * (r.bottom - r.top); };
    const Mon* best = &pick[0];
    for (auto& m : pick) {
        bool better = false;
        switch (g_screen) {
            case 1: better = m.work.left < best->work.left; break;
            case 2: better = m.work.right > best->work.right; break;
            case 3: better = m.work.top < best->work.top; break;
            default:
                better = area(m.work) > area(best->work) ||
                         (area(m.work) == area(best->work) && best->primary && !m.primary);
        }
        if (better) best = &m;
    }
    *out = best->work;
    return true;
}

// A hidden, unowned top-level window about to be shown for the first time.
bool Eligible(HWND h) {
    if (g_screen < 0 || !h || !IsWindow(h) || IsWindowVisible(h)) return false;
    LONG style = GetWindowLongW(h, GWL_STYLE), ex = GetWindowLongW(h, GWL_EXSTYLE);
    if ((style & WS_CHILD) || (ex & (WS_EX_TOOLWINDOW | WS_EX_NOACTIVATE))) return false;
    if (GetWindow(h, GW_OWNER) || GetPropW(h, kPlaced)) return false;
    return !IsZoomed(h) && !IsIconic(h);
}

// Where the window goes, keeping its size inside the target monitor. False: leave it alone.
bool Spot(HWND h, int* x, int* y, int* w, int* hh) {
    SetPropW(h, kPlaced, (HANDLE)1);
    RECT r{};
    if (!GetWindowRect(h, &r)) return false;
    int cw = *w > 0 ? *w : r.right - r.left, ch = *hh > 0 ? *hh : r.bottom - r.top;
    if (cw < 120 || ch < 80) return false;
    RECT work{};
    if (!TargetWork(&work)) return false;
    cw = std::min<int>(cw, work.right - work.left);
    ch = std::min<int>(ch, work.bottom - work.top);
    *x = work.left + (work.right - work.left - cw) / 2;
    *y = work.top + (work.bottom - work.top - ch) / 2;
    *w = cw;
    *hh = ch;
    return true;
}

// --- Hooks ---------------------------------------------------------------------------------------

using SetWindowPos_t = BOOL(WINAPI*)(HWND, HWND, int, int, int, int, UINT);
using ShowWindow_t = BOOL(WINAPI*)(HWND, int);
using SetForegroundWindow_t = BOOL(WINAPI*)(HWND);
using SwitchToThisWindow_t = void(WINAPI*)(HWND, BOOL);
using AllowSetForegroundWindow_t = BOOL(WINAPI*)(DWORD);
using SendInput_t = UINT(WINAPI*)(UINT, LPINPUT, int);
using SetCursorPos_t = BOOL(WINAPI*)(int, int);
using CreateWindowExW_t = HWND(WINAPI*)(DWORD, LPCWSTR, LPCWSTR, DWORD, int, int, int, int, HWND, HMENU, HINSTANCE, LPVOID);
using CreateWindowExA_t = HWND(WINAPI*)(DWORD, LPCSTR, LPCSTR, DWORD, int, int, int, int, HWND, HMENU, HINSTANCE, LPVOID);

SetWindowPos_t SetWindowPos_Orig;
ShowWindow_t ShowWindow_Orig;
ShowWindow_t ShowWindowAsync_Orig;
SetForegroundWindow_t SetForegroundWindow_Orig;
SwitchToThisWindow_t SwitchToThisWindow_Orig;
AllowSetForegroundWindow_t AllowSetForegroundWindow_Orig;
SendInput_t SendInput_Orig;
SetCursorPos_t SetCursorPos_Orig;
CreateWindowExW_t CreateWindowExW_Orig;
CreateWindowExA_t CreateWindowExA_Orig;

void PlaceHidden(HWND h) {
    if (!Eligible(h) || OwnerIntent()) return;
    int x, y, w = 0, hh = 0;
    if (Spot(h, &x, &y, &w, &hh))
        SetWindowPos_Orig(h, nullptr, x, y, w, hh, SWP_NOZORDER | SWP_NOOWNERZORDER | SWP_NOACTIVATE);
}

int QuietShowCmd(int cmd) {
    switch (cmd) {
        case SW_SHOWNORMAL: case SW_SHOWMAXIMIZED: case SW_RESTORE: case SW_SHOWDEFAULT:
            return SW_SHOWNOACTIVATE;
        case SW_SHOW: return SW_SHOWNA;
        case SW_SHOWMINIMIZED: return SW_SHOWMINNOACTIVE;
        default: return cmd;
    }
}

bool Shows(int cmd) { return cmd != SW_HIDE && cmd != SW_MINIMIZE && cmd != SW_FORCEMINIMIZE; }

BOOL WINAPI ShowWindow_Hook(HWND h, int cmd) {
    if (!TopLevel(h)) return ShowWindow_Orig(h, cmd);
    if (Shows(cmd)) PlaceHidden(h);
    if (Quiet()) cmd = QuietShowCmd(cmd);
    return ShowWindow_Orig(h, cmd);
}

BOOL WINAPI ShowWindowAsync_Hook(HWND h, int cmd) {
    if (!TopLevel(h)) return ShowWindowAsync_Orig(h, cmd);
    if (Shows(cmd)) PlaceHidden(h);
    if (Quiet()) cmd = QuietShowCmd(cmd);
    return ShowWindowAsync_Orig(h, cmd);
}

BOOL WINAPI SetWindowPos_Hook(HWND h, HWND after, int x, int y, int cx, int cy, UINT flags) {
    if ((flags & SWP_SHOWWINDOW) && Eligible(h) && !OwnerIntent()) {
        int nx, ny, w = (flags & SWP_NOSIZE) ? 0 : cx, hh = (flags & SWP_NOSIZE) ? 0 : cy;
        if (Spot(h, &nx, &ny, &w, &hh)) {
            x = nx;
            y = ny;
            flags &= ~SWP_NOMOVE;
            if (!(flags & SWP_NOSIZE)) { cx = w; cy = hh; }
        }
    }
    if (!(flags & SWP_NOACTIVATE) && TopLevel(h) && Quiet()) flags |= SWP_NOACTIVATE;
    return SetWindowPos_Orig(h, after, x, y, cx, cy, flags);
}

BOOL WINAPI SetForegroundWindow_Hook(HWND h) {
    if (Quiet()) {
        Wh_Log(L"agent window: kept %p from taking the foreground", h);
        return FALSE;
    }
    return SetForegroundWindow_Orig(h);
}

void WINAPI SwitchToThisWindow_Hook(HWND h, BOOL altTab) {
    if (Quiet()) return;
    SwitchToThisWindow_Orig(h, altTab);
}

// Handing foreground rights to another app (how a browser or Explorer window jumps in front
// after an agent opens a link or folder) is declined quietly.
BOOL WINAPI AllowSetForegroundWindow_Hook(DWORD pid) {
    if (Quiet()) return TRUE;
    return AllowSetForegroundWindow_Orig(pid);
}

UINT WINAPI SendInput_Hook(UINT count, LPINPUT inputs, int size) {
    if (Quiet()) {
        Wh_Log(L"agent window: blocked %u synthetic inputs", count);
        SetLastError(ERROR_ACCESS_DENIED);
        return 0;
    }
    UINT sent = SendInput_Orig(count, inputs, size);
    MarkAgentInput();
    return sent;
}

BOOL WINAPI SetCursorPos_Hook(int x, int y) {
    if (Quiet()) {
        SetLastError(ERROR_ACCESS_DENIED);
        return FALSE;
    }
    BOOL ok = SetCursorPos_Orig(x, y);
    MarkAgentInput();
    return ok;
}

// A top-level window created visible would show and activate inside the create call; make it
// hidden, place it, then show it without activating.
bool HoldVisible(DWORD style) {
    return g_enabled && !(style & WS_CHILD) && (style & WS_VISIBLE) &&
           !(style & (WS_MAXIMIZE | WS_MINIMIZE)) && !OwnerIntent();
}

void ShowHeld(HWND h) {
    if (!h) return;
    PlaceHidden(h);
    ShowWindow_Orig(h, Quiet() ? SW_SHOWNA : SW_SHOW);
}

HWND WINAPI CreateWindowExW_Hook(DWORD ex, LPCWSTR cls, LPCWSTR name, DWORD style, int x, int y, int w,
                                 int h, HWND parent, HMENU menu, HINSTANCE inst, LPVOID param) {
    if (!HoldVisible(style)) return CreateWindowExW_Orig(ex, cls, name, style, x, y, w, h, parent, menu, inst, param);
    HWND hwnd = CreateWindowExW_Orig(ex, cls, name, style & ~WS_VISIBLE, x, y, w, h, parent, menu, inst, param);
    ShowHeld(hwnd);
    return hwnd;
}

HWND WINAPI CreateWindowExA_Hook(DWORD ex, LPCSTR cls, LPCSTR name, DWORD style, int x, int y, int w,
                                 int h, HWND parent, HMENU menu, HINSTANCE inst, LPVOID param) {
    if (!HoldVisible(style)) return CreateWindowExA_Orig(ex, cls, name, style, x, y, w, h, parent, menu, inst, param);
    HWND hwnd = CreateWindowExA_Orig(ex, cls, name, style & ~WS_VISIBLE, x, y, w, h, parent, menu, inst, param);
    ShowHeld(hwnd);
    return hwnd;
}

template <typename T>
bool Hook(HMODULE module, const char* name, T hook, T* orig) {
    void* p = module ? (void*)GetProcAddress(module, name) : nullptr;
    if (!p) return false;
    return Wh_SetFunctionHook(p, (void*)hook, (void**)orig);
}

// The syscall stubs in win32u catch the calls user32 makes internally too (message boxes,
// dialogs); user32 is the fallback where a stub is missing.
bool ModInit() {
    WCHAR self[MAX_PATH]{};
    GetModuleFileNameW(nullptr, self, ARRAYSIZE(self));
    std::wstring exe = Lower(PathFindFileNameW(self));
    for (PCWSTR n : kNeverQuiet)
        if (exe == n) {
            SetEnvironmentVariableW(kEnv, nullptr);
            return false;
        }
    WCHAR v[8]{};
    DWORD n = GetEnvironmentVariableW(kEnv, v, ARRAYSIZE(v));
    if (n == 1 && v[0] == L'0') return false;
    LoadSettings();
    if (!g_enabled) return false;
    bool marked = n == 1 && v[0] == L'1';
    if (!marked && !FromAgent()) return false;
    if (!marked) SetEnvironmentVariableW(kEnv, L"1");

    HMODULE u = LoadLibraryW(L"win32u.dll");
    HMODULE user = LoadLibraryW(L"user32.dll");
    bool ok = true;
    ok &= Hook(u, "NtUserSetWindowPos", SetWindowPos_Hook, &SetWindowPos_Orig) ||
          Hook(user, "SetWindowPos", SetWindowPos_Hook, &SetWindowPos_Orig);
    ok &= Hook(u, "NtUserShowWindow", ShowWindow_Hook, &ShowWindow_Orig) ||
          Hook(user, "ShowWindow", ShowWindow_Hook, &ShowWindow_Orig);
    ok &= Hook(u, "NtUserShowWindowAsync", ShowWindowAsync_Hook, &ShowWindowAsync_Orig) ||
          Hook(user, "ShowWindowAsync", ShowWindowAsync_Hook, &ShowWindowAsync_Orig);
    ok &= Hook(u, "NtUserSetForegroundWindow", SetForegroundWindow_Hook, &SetForegroundWindow_Orig) ||
          Hook(user, "SetForegroundWindow", SetForegroundWindow_Hook, &SetForegroundWindow_Orig);
    ok &= Hook(u, "NtUserSendInput", SendInput_Hook, &SendInput_Orig) ||
          Hook(user, "SendInput", SendInput_Hook, &SendInput_Orig);
    Hook(user, "SwitchToThisWindow", SwitchToThisWindow_Hook, &SwitchToThisWindow_Orig);
    Hook(user, "AllowSetForegroundWindow", AllowSetForegroundWindow_Hook, &AllowSetForegroundWindow_Orig);
    Hook(user, "SetCursorPos", SetCursorPos_Hook, &SetCursorPos_Orig);
    Hook(user, "CreateWindowExW", CreateWindowExW_Hook, &CreateWindowExW_Orig);
    Hook(user, "CreateWindowExA", CreateWindowExA_Hook, &CreateWindowExA_Orig);
    g_active = ok;
    Wh_Log(L"agent windows: quiet in %s (%s)", exe.c_str(), ok ? L"hooked" : L"hook failed");
    return ok;
}

}  // namespace agentQuiet

bool g_agentQuietInited = false;

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

BOOL WhToolLauncher_ModInit(BOOL* launch) {
    WCHAR path[MAX_PATH]{};
    GetModuleFileNameW(nullptr, path, ARRAYSIZE(path));
    *launch = _wcsicmp(PathFindFileNameW(path), L"windhawk.exe") == 0;
    if (gameguard::ShouldSkipProcess()) return FALSE;
    g_packDragInited = altSnapDrag::ModInit();
    g_agentQuietInited = agentQuiet::ModInit();
    return g_packDragInited || g_agentQuietInited;
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
