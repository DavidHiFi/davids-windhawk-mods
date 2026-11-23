# Seamless Taskbar 0.4.50: right-click Modules menu on Windows 26200

Date: 2026-11-23. Job folder: `D:\Agent Work\2026-11-23-modules-menu-vm\`.

## What was wrong

On the test PC (Windows 26200) right-clicking empty taskbar space showed only the stock
rows. No Modules, no Dock position, no utility rows. Three causes, found by offline
disassembly of that build's Taskbar.View.dll with its symbols:

1. `ContextMenus::ShowTaskbarSettingsContextMenu` has 3 inputs on 26200 (no TaskbarSettings).
   The mod only knew the 4-input form, so the whole Taskbar.View hook set failed.
2. 26200 adds the stock rows through inlined vector calls, so the `Append` hook never fires
   and our rows were never inserted.
3. `modmenu::Append` refused to run unless `tps::g_hostProcess` was set. On 26200 the
   taskbar-position hooks do not resolve, so that flag stays false.

## Fix (0.4.50)

- Both forms of `ShowTaskbarSettingsContextMenu` are hooked, each optional. Install fails
  with "Taskbar settings menu not found" only if neither resolves.
- New optional hook on `ShowFlyoutAtPointerPosition` (4-input form): while the settings
  menu is being built and nothing was injected yet, it lifts the stock rows out, adds ours
  first, then puts the stock rows back, themed.
- The host-process check in `modmenu::Append` is gone; only the taskbar's own menu reaches it.
- On the tower (26300) the show hook does not resolve (that build passes a placement mode
  too), so the tower keeps the old Append path. Nothing changes there.

Patch script: `patch-0449.py` in the job folder (builds 0.4.50 from live 0.4.49).

## Proof (test PC, 26200, 10:29 pm)

- Menu: Modules, Restart Explorer, Clean Temp, Reduce Memory, Restart Graphics Driver,
  Get IP Address, Rebuild Icon & Thumbnail Cache, Clean DNS Cache, Auto-hide taskbar,
  Add separator, Task Manager, Taskbar settings.
- Modules submenu lists all 14 modules. Capture: `results\out\sub-modules.png`.
- Debug build log: `show flyout depth=1 injected=1`. No Explorer crash dumps.

## Known limits

- Dock position is missing in the test PC only because Seamless Dock is not running there.
- The Taskbar position submenu is still unavailable on 26200: "Taskbar position hooks:
  unavailable" (one of TrayUI::WndProc or TaskbarSettings::Location does not resolve).
  Separate job.

## Install

Installed through `install-0450.ps1` (Install-StagedMod under the windhawk-engine lock,
base hash check, auto-publish), held until the owner stopped playing. Live hash C4BEF9CA....

## Tower incident (10:44 to 11:30 pm)

- From about 10:44 pm the engine inside Explorer stopped taking mod changes (0.4.50 and
  wobbly 1.2.13 both never reached it). Off and on did not help.
- One guarded restart at 10:54 pm. It did restart, then threw "STOP: expected one plain
  shell, found 2" (it counted the `-tool-mod` Explorer 14844). No second restart was run.
- The new shell (29264) never built its tray: Seamless Taskbar logged "no SystemTrayFrameGrid"
  every 5 s, then the log stopped at 10:58:30.
- Cause of the blank bar: the taskbar's main thread crashed at about 10:58:30. Stack: XAML
  raising an event to a handler that was already freed (access violation in
  `ComPtr<IEventHandler>::InternalAddRef`), then a fail-fast. Windows error reporting does
  not finish the crash, so the process sits on a csrss box "explorer.exe - System Error /
  Exception Processing Message 0xc0000005". `IsHungAppWindow` true, PrintWindow hangs.
- The crash came before Seamless Taskbar was switched off (11:00:10 pm), so it is not an
  unload crash. Which mod owned the freed handler is not proven; the stack shows only XAML
  frames (autoscroll's PeekMessage hook is a pass-through).
- Recovery: `recover-when-clear.ps1` waits for the owner to stop playing, then
  `C:\Users\Public\recover-shell.ps1` (elevated) presses OK on the box, lets Windows start a
  fresh shell with Seamless Taskbar off, checks it answers, switches the mod on through
  Set-ModState and checks again (turns it off if the shell stops answering). Log:
  `recover-shell.log`.
- Ran at 12:12 am on 11-24 (owner said get it done, so no waiting): box closed by posted
  BM_CLICK, old shell exited, Windows started shell 11956, it answered with the mod off,
  Seamless Taskbar 0.4.50 switched on (gate watched 60 s: desktop fine), shell still
  answering 90 s later. Full bar captured: `tower-top-fixed.png`.
- Lesson: a blank bar with a frozen UI thread waiting on LpcReply can be a fail-fast stuck
  on a hidden crash box. List `#32770` windows owned by csrss before anything else.
