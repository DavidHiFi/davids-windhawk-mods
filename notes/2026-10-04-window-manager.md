# 2026-10-04 Window Manager (renamed from David Window Pack)

## What changed

- Mod id `local@david-window-pack` 1.0.0 became `local@window-manager` 1.1.0
  (name "Window Manager"). The header and readme came from the mod-polish thread.
- Fixed move-to-monitor (Alt+Shift+arrows on this machine) for maximized
  windows, which used to jump to the target monitor and straight back.

## Root cause

`MoveWindowToMonitor` called `ShowWindowAsync(SW_RESTORE)`, read the still
maximized rect, moved the window, then called `ShowWindowAsync(SW_MAXIMIZE)`.
The async restore landed after the move and put the window back at its old
normal position, and the async maximize then maximized it on the original
monitor.

## Fix (`window-manager.wh.cpp`)

- `MonitorInfo` now carries `rcMonitor` (lines 3977, 3990).
- New `WorkspaceOffset` (line 4049): `rcNormalPosition` is in workspace
  coordinates, offset by the work area of the window's own monitor (not the
  primary). Measured here: on the primary with its top taskbar the offset is
  (0, 50); on the secondaries it is 0. Tool windows use screen coordinates.
- `MoveWindowToMonitor` (line 4054):
  - Maximized or minimized: read `GetWindowPlacement`, map the normal rect to
    the destination with the existing size/center logic, write it back with
    `SetWindowPlacement`. The window stays maximized and nothing flashes. If it
    is still maximized on the old monitor afterwards, it gets a synchronous
    `ShowWindow(SW_RESTORE)` plus `ShowWindow(SW_MAXIMIZE)`, as in Snap
    Commander's display move.
  - Borderless fullscreen (window rect equals the source monitor rect): resized
    to cover the destination monitor rect.
  - Restored windows: unchanged.

The first build (rev 1) offset by the primary monitor's work area, and the
restored rect landed 50 px high on secondary monitors. Rev 2 is the installed one.

## Install

- Build: `Windhawk\window-pack\Build-window-manager.ps1` (WH_MOD only, id through
  `modid-window-manager.h`, engine lib 1.7.3_2).
  - x64 `local@window-manager_1.1.0_2.dll` AE35322453E061234793671F45799F742BB2AC2EAFAD527B4F095E80B06AA3BE
  - x86 `local@window-manager_1.1.0_2.dll` B03B48702BD1A73CBD3331C52C6BBF64F44A5168C255A2D56B29982F6B7CB04B
- `scripts\2026-10-04-window-manager.ps1 -Install` (elevated through
  `2026-10-04-window-manager-install.cmd`) does the following:
  1. Backs up the old key, source and DLLs to `backups\2026-10-04\window-manager\`.
  2. Disables the old key.
  3. Waits for the old tool process to exit.
  4. Copies the DLLs and source.
  5. Copies the old key, including its 65 Settings values, to the new id.
  6. Sets `LibraryFileName`, `Version` and `SettingsChangeTime`, then enables the new key.
- Trap: start the new tool process only after the old one has exited. One
  install started the new process while the old one was still alive, so its
  `RegisterHotKey` calls failed and no shortcut worked. The script now polls
  until the old process is gone.
- Trap: the installed DLL stays mapped, so copying over it fails. The script
  skips the copy when the hashes already match.

## Verification

- Registry read back: new key Disabled=0, Version 1.1.0, LibraryFileName
  `local@window-manager_1.1.0_2.dll`. Old key Disabled=1.
- Elevated process list shows exactly one `-tool-mod "local@window-manager"` and
  no `local@david-window-pack` tool process. Explorer maps the new DLL only.
- Live test (`reports\2026-10-04-window-manager\live-test.json`, Tk test windows
  that I owned): a maximized window moved 0 to 2, 2 to 1 and 1 to 0 and stayed
  zoomed on the target 3.5 s later. Restore after a move lands centered on the
  destination. Moving restored windows, borderless fullscreen 0 to 2 to 0,
  Alt+Left, Alt+U, minimize and restore, Alt+drag and Alt+F all passed.
- Preview GIF: `davids-windhawk-mods\media\previews\window-manager.gif`
  (864x486, 9.75 s, 868 KB). It shows half and quarter snaps, Alt+drag and the
  Alt+F maximize toggle. There is no center snap because this machine's
  settings leave `keyCenter` unbound.

## Rollback

`scripts\2026-10-04-window-manager.ps1 -Rollback`, run elevated. It disables
`local@window-manager`, waits for its tool process to exit, then re-enables
`local@david-window-pack`. The old key, source and DLLs were left in place.
