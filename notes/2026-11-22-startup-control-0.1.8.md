# Startup Control 0.1.8 (2026-11-22)

Owner asked: taskbar shows a blank Windows icon, tray right-click menu is broken, and a way
to open the window from the mod's Settings tab in Windhawk.

## Causes and fixes

- Taskbar icon: the window runs in windhawk-mod-elevated.exe. Explorer runs at normal rights
  and cannot ask an elevated window for its icon, so it falls back to the class icon, and the
  class had none (the exe has no icon either). Fix in `SC_Message` (mod-own code, no template
  drift): every WM_SETICON is also written to the class (GCLP_HICON / GCLP_HICONSM), and both
  class icons are cleared on WM_NCDESTROY before the engine destroys the icons.
- Tray right-click: with NOTIFYICON_VERSION_4 a right click sends WM_RBUTTONUP and then
  WM_CONTEXTMENU. The handler opened the menu on both. The second call hit `Set_TrayMenu`'s
  "menu already open, close it" guard, so the menu shut at once. Now only WM_CONTEXTMENU opens
  it, at the point in wParam. A left click acts on NIN_SELECT only (WM_LBUTTONUP dropped too).
- Open from Windhawk: Windhawk's settings schema has no button type. New Windhawk-only setting
  `openSettingsWindow` at the top of the list: flip it either way and press Save, the window
  opens. The mod keeps the last seen value in its own storage (`openSettingsWindowSeen`), so
  any flip counts. Not shown in the window's own settings page.

- 0.1.9 (2026-11-23): the tray menu's two icons were Segoe symbol codes, but the menu draws
  its icons with FiraCode Nerd Font, so they showed as stray shapes. Now codicons ``
  (monitor) and `` (refresh), the same set the Halo menu uses.

## Live proof (2026-11-23, 1:51 to 2:04 am, under the desktop lock)

- Switch: writing `openSettingsWindow` and bumping SettingsChangeTime (what Save does) opened
  the window in 750 ms. Flipping it back did not open a second one.
- Taskbar icon: the open window's class icons are set (nonzero from a normal-rights process),
  and the taskbar dock shows the monitor icon. `proof\icon-crop.png`.
- Tray menu: Explorer's right-click pair opens the menu, it takes the foreground and stays
  open 4 s, and a second right-click closes it. `proof\menu-crop.png` (0.1.9 icons).
- Test traps: from PowerShell, `FindWindowW(cls, $null)` passes "" and finds nothing; use
  `[NullString]::Value`. A menu left open by one run gets closed by the next run's first
  right-click (that is the toggle working), so check for a leftover first. Scripts:
  `live-test.ps1`, `menu-test.ps1` in the job folder.
- `2026-11-10-tool-mod-restart.ps1` reports "running: 0" for elevated mods: it only looks at
  windhawk-mod.exe. Check with `probe-live.ps1` instead.

## Files

- Source of truth: `work\startup-control\gen.py`, `src\lifecycle.inc`, `src\management.inc`.
  Backups: `work\startup-control\backups-20261122-0658\`.
- Install: `work\2026-11-22-startup-control-fixes\install.ps1` (gate, engine lock, Public copy).

## Rollback

Reinstall the previous source: `C:\ProgramData\Windhawk\ModsSource\local@startup-control.wh.cpp`
backups (`.bak-*`) or restore the three files above from the backup folder and run gen.py.

## Open idea

A real button on the Windhawk page would need Enhanced Styler to draw one that flips the
switch and presses Save. Not done; offered to the owner.
