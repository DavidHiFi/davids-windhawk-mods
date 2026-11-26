# Title bar menus black in tool mods (2026-11-24)

## Problem

The owner saw the title bar menu (right-click the title, or Alt+Space) of the Seamless
Download Manager settings window come up pitch black: the Mocha pill and separators were
there, but no blur and no acrylic. Every other menu in the same window looked right.

## Cause

`C:\Program Files\Windhawk\Compiler\include\windhawk_tool_mod.h`: the tool mod entry point
calls `WhTool_ModInit` on the process's main thread, then `CallModEntryPoint(); ExitThread(0);`.
Windows removes a thread's WinEvent hooks when that thread ends. SeamlessMenuRoom::Init set its
`EVENT_OBJECT_CREATE` and `EVENT_SYSTEM_MENUSTART/END` in-context hooks on that thread, so they
died right after start.

- Menus opened through TrackPopupMenu still got the look: the CBT hook path calls ApplyEffects.
- Title bar (system) menus are opened by DefWindowProc inside the kernel. They only got the
  process-wide DrawThemeBackground skin and a painted black body. ApplyEffects (dark mode, blur
  behind, acrylic accent 0xA01B1111, round corners) never ran.

## Fix

`work/2026-11-24-menu-hook-thread/patch.py <src> <dst> <ver|+|=>` moves the two hooks onto a
small thread (`HookThreadProc`) with its own message queue that lives until Uninit. Uninit
posts WM_QUIT, the thread removes its own hooks and ends. Adds a "What's new" bullet.

`batch.py` ships it to the 16 tool mods that use the shared watcher, one at a time under the
engine lock, trailing the clean-icons rollout per mod and patching the live source at install
time (restage.py first when the settings engine is behind). Log: `batch.log`.

Left out on purpose: Seamless Flyouts starts the watcher in every process (`@include *`), so the
extra thread would land in every app. Seamless Title Bars, Window Manager and Task Manager start
it only from `WhTool_ModInit`, so they are included.

## Rollback

Each mod: reinstall the previous version from the Workshop repo history (git in
davids-windhawk-mods), or for the Download Manager `work/2026-11-24-menu-hook-thread/sdm-1.0.7.wh.cpp`.

## Result of the first fix: not enough

Download Manager 1.0.9 (hook-thread fix) still opened the title bar menu black. Live proof
(`prove.py`): the menu window had none of the skin props. `events.py` (out-of-context
listener) showed EVENT_OBJECT_CREATE and SHOW do fire for the #32768 window, so the in-context
hook simply never delivers it to the mod. Cause of that not pinned down; not needed.
The first batch shipped the thread fix to Download Manager 1.0.9, Better Volume Mixer Plus,
Task Manager and Window Manager before it was stopped at 8:33 am. Harmless, but not the fix.

## Second fix (patch2.py)

`patch2.py <src> <dst> <+|=>` hooks DefWindowProcW in SeamlessMenuSkin::Init and wraps the
messages that open the title bar menu (WM_SYSCOMMAND SC_KEYMENU / SC_MOUSEMENU,
WM_CONTEXTMENU, WM_POPUPSYSTEMMENU 0x313) with BeginTrack + the CBT hook, exactly like
TrackPopupMenu_hook. The menu is skinned on its own thread before the first paint. Marker:
`SysMenuDefProc_hook`. Replaces the single "What's new" section.

Seamless Title Bars has its own DefWindowProcW hook, but only in app processes (its dispatch
skips windhawk.exe); the skin hook only runs in its tool process, so the two never meet.

`batch.py` now runs patch2.py (old one kept as batch1.py).

## Result of second fix (batch ended 11:06 am, 2026-11-26)

Already had it: download manager, volume mixer, Halo Launcher, recycle bin tray, autoclicker,
crosshair, dictate, Explorer search, key click. Installed: crash watch 1.3.3 (now 1.3.4),
snipper 0.7.6, sound manager 1.0.10, window manager 2.8.12, windows firewall 1.2.6,
task manager 1.0.3. 12:07 pm registry check: all on those versions and switched on.
Earlier refusals (exit 75 desktop busy, exit 4 engine lock taken) were all retried to success.
