# Seamless Dock 0.2.0: top bar title, app buttons off the top bar (2026-11-23)

The owner asked for this in the bottom dock job (2026-11-22). Item 4: the top bar's middle shows
the active window's app and title, in place of the app buttons.

## What changed

- **Seamless Dock 0.2.0** (`work\2026-11-22-bottom-dock\seamless-dock.wh.cpp`; the 0.1.0 copy is
  `seamless-dock-0.1.0.wh.cpp`).
  - A new click-through layered window, `SeamlessDockTitle`, sits centred on a top Shell_TrayWnd.
    It copies the look of the bar's pills: 34 px tall, corner radius 10, a 2 px Surface1 edge
    and a clear inside. It shows the app icon, the app name (Text, semibold) and the window
    title (Subtext). It is refreshed from Rebuild and once a second, and repaints only when
    its text changes.
  - New setting `showTitle` ("Window title on the top bar"), on by default.
  - Idle redraw fix, reported by the "find why window drawing is busy" thread: Rebuild now
    compares an item signature and skips the layout and the repaint when nothing changed.
    Before, every tooltip or pop-up anywhere repainted the dock (about 20 frames a second
    while idle).
- **Taskbar Styler** (HKLM\SOFTWARE\Windhawk\Engine\Mods\windows-11-taskbar-styler\Settings)
  - old: `controlStyles[5].styles[1]` not present (rule 5 = `Taskbar.TaskListButton#TaskListButton`, styles[0] `Margin=0`)
  - new: `controlStyles[5].styles[1] = Visibility=Collapsed`
  - Seamless Taskbar's apps island hides itself when no task buttons are visible.
  - **Result: reverted.** The buttons never hid, and the taskbar thread of the shell froze
    (one core busy, memory climbing past 2.5 GB, Shell_TrayWnd hung). Windows restarted the
    shell at 3:08 am. The value was deleted at 3:08 am (`reg delete`, since
    Remove-ItemProperty reads `[5]` as a wildcard and deleted nothing on the first try).
    Backup: `backups\taskbar-styler-settings.bak-20261123-0258.reg`. The 40 s check after the
    write looked at the wrong Explorer (pid 4112, not the shell): always find the shell pid
    from Shell_TrayWnd.
  - Never hide task buttons with a styler rule while Seamless Taskbar runs. The hide was
    handed to the "Make taskbar and dock modular" thread as an "App buttons" module inside
    Seamless Taskbar.
- **Dock showTitle** (HKLM\...\local@seamless-dock\Settings): old 1, new 0, 3:11 am, so the
  pill does not cover the bar's app buttons. Turn back on once the buttons are gone.
- **Found after the restart:** 0.2.0 does not take its reserved strip back after a shell
  restart (TaskbarCreated reset `g_appbar` but kept `g_barHeightSent`, so SETPOS was skipped).
  The work area went back to the full screen.

## 0.2.1 (staged, checked offline, not installed yet)

- TaskbarCreated also clears `g_barHeightSent` and `g_barRect`, so the strip is set again.
- TitleWindow falls back to the top eligible, not minimized window in z-order (tray menus and
  the hidden icons panel left the pill empty).
- Install waits until the owner stops gaming (engine lock, Install-StagedMod, base hash of the
  0.2.0 source). 0.2.0 copy: `seamless-dock-0.2.0.wh.cpp`.

## Handoff (owner gaming, install held)

- The dock file went to the "Make taskbar and dock modular" thread (fa897eef). It installs
  0.2.1 inside its 0.3.0, so the dock reloads once. It also hides the top bar's app buttons
  as a Seamless Taskbar module, then sets showTitle back to 1.

## 0.3.1 (installed 4:56 am, published, mods b4cdfca, feed b29cbfe)

The dock came back to this thread. 0.3.1 is 0.3.0 (place control for the taskbar's
Modules and Dock position menus, wp 1-5 kept) plus:

- Pinned apps no longer show twice. A window now matches a pin when its program sits in
  the pin's own folder (Steam's steamwebhelper.exe, Windhawk's UI\Windhawk.exe). The
  Windows folder and windhawk-mod.exe never match, and the folder must be 3 levels deep.
- Unpinned windows whose app id is in the Apps folder launch and pin by that id.
- The strip heals itself: every 5 s, if the work area reaches into the dock again or the
  appbar went away (shell restart), the dock drops and re-adds its strip.
- New menu row "Open file location". Menu already had: window list, Open/New window,
  Pin to dock / Unpin from dock, Close window(s), Dock options. Bin: Open, Empty, Remove.
- Defaults written: position auto, recycleBin 1. showTitle stays 0 until the top bar's
  app buttons are off (Seamless Taskbar 0.4.45, the other thread installs it).
- Backup of the live 0.2.0 source: `local@seamless-dock-20261123-0456.wh.cpp`.

Proof (`D:\Agent Work\seamless-dock\proof\fix-031\`):
- dock.png: seven pins, one icon each, running dots under T3, Steam, Helium; one
  unpinned app after the divider; Recycle Bin at the end.
- Work area 0,56,2560,1366; dock edge at y 1366 by pixel.
- tile.log: a test window moved onto the main screen (no focus, no input) was tiled by
  Seamless Window Manager to 20,76,2540,1346, so 20 px above the dock, same as the sides.

## Title back on (5:50 am)

- Seamless Taskbar 0.4.46 with apps.HideAllButtons=1 went live at 5:48 am (thread fa897eef).
- Dock control message wp 4, lp 1: state 0x40000410 to 0x40000430. Title window 1187,14,1373,48.
- **Dock showTitle** (HKLM\...\local@seamless-dock\Settings): old 0, new 1, SettingsChangeTime bumped.
  Backup: `backups\seamless-dock-settings.bak-20261123-0550.reg`. Rollback: `elevated-title-off.ps1`.
- Proof `D:\Agent Work\seamless-dock\proof\title-1123\`: topbar.png, title.png. check-dock-align ok,
  work area still 0,56,2560,1366, Explorer 4112 unchanged.
- Right-click menus captured live 7:20 am (desktop lock, posted WM_RBUTTONUP from an elevated
  script, closed with a posted Escape): `D:\Agent Work\seamless-dock\proof\menu-1123\`
  steam-menu.png (Steam, New window, Unpin from dock, Open file location, Close window, Dock
  options) and bin-menu.png (Open, Remove from dock, Dock options; Empty shows only when the bin
  has something in it). Script: `menu-capture.ps1 -Mon N -X -Y`.
- The PC rebooted at 7:10 am (not from this job). After it: work area 0,56,2560,1366, taskbar
  0.4.47 with hide-all 1, dock title 1 showing, dock and bin back. The main screen's capture
  index moved from 3 to 1; probe it every time.
- The 120 s lock ran out before the bin capture; another thread held the desktop by then. Use a
  longer ttl (300) for multi-step captures.

## 0.3.2: audit fixes and new settings (installed 7:02 pm, published)

Live health at 0.3.1, before the change (`health-sample.ps1`, `idle-watch.ps1` in
`work\2026-11-22-bottom-dock\`): handles flat at 589, GDI 43, USER 21-22 over 2.5 min, about
32 MB in use, about 2% of one core while the owner worked, 0.4 redraws a second idle.

Source: `work\2026-11-23-modular-bar\seamless-dock.wh.cpp`; 0.3.1 copy `seamless-dock-0.3.1.wh.cpp`.

- Every appbar call first checks that Explorer answers (WM_NULL, 300 ms, abort if hung). If
  ABM_NEW fails while it answers, ABM_REMOVE and try once more.
- Strip heal backs off: after 3 heals in a row it checks once a minute, not every 5 s.
- kAppBarMsg allowed through the message filter (the dock runs elevated).
- App names (shell name, file description) cached per item key, cleared on settings reload.
- Recycle Bin query on its own thread (kRecycleDone = WM_APP+4); startup, reload, the bin
  menu and turning the bin on no longer wait on it. Teardown waits up to 3 s for it.
- A failed icon load is retried after 30 s, not cached forever.
- Drag fix: ReleaseCapture ended the drag through WM_CAPTURECHANGED, then the button-up
  saw no drag and clicked the item. A drag dropped on its own place opened or hid the app.
- Window meta with no app id and no program is looked up again; such windows key as `w:`+hwnd.
- Relayout guarded against running inside itself (queued, at most 3 more passes).
- A maximized window with a caption no longer counts as full screen.
- GetMonitorInfoW checked; a failed window creation leaves no half-made dock.
- Clicking the dock closes its menu; the 1 s tick closes a menu Windows would not focus
  once another window comes to the front.
- New settings: `iconLift` (0-10, 3), `previewSize` (140-360, 208, image height scales),
  `titleMaxWidth` (200-1400, 720). Settings regrouped: place and size, what shows, look,
  title, behavior. Keys unchanged. Menu row renamed "Window title on the top bar".
- After install, `elevated-dock-032-defaults.ps1` writes the three new values when missing
  (checked live: iconLift 3, previewSize 208, titleMaxWidth 720).

Install incident: Install-StagedMod's "tool process came back" check saw the old pid, which
then exited, and no new dock process started. The dock was gone until I ran
`2026-11-10-tool-mod-restart.ps1` by hand. Fix in Install-StagedMod (uncommitted, the file also
holds other threads' edits): it records the tool pids before the compile and only a pid that
was not there before counts. Coop note posted. Also: an elevated script's `coop lock` lands on
a private System32 board unless it first does `Set-Location 'H:\Windhawk Configuration'`.

Health after 0.3.2: handles flat 577-584, GDI 43, USER 20-21, about 2.4% of one core idle.

7:36-7:46 pm: another thread's cut-off cdb peek left Explorer suspended, and Seamless Taskbar
was turned off (0.4.48, disabled). Right after, the work area bottom read 1440 (dock space
lost); by 7:55 pm the dock's heal had it back at 1366 without help. Ghost readings from that
window are not a dock fault.

## 0.3.3: ghost and icon fixes (staged, syntax checked, install held while the owner games)

Found in the 0.3.2 dock capture (`D:\Agent Work\seamless-dock\proof\v032\`): Yapfast twice,
a folder icon and a blank page among the open apps.

- Class `Ghost` skipped in Eligible. Windows draws a Ghost window (owned by dwm.exe, no icon,
  so the shell's blank page) over a frozen app; Yapfast had hung, so it showed twice.
- `windhawk-mod*.exe` never matches a pin by the program folder, so Startup Control and other
  mod windows get their own item instead of lighting up the Windhawk pin.
- IconFromShell refuses an .exe with no icon resources (ExtractIconExW count 0), so GetIcon
  falls through to the window's own icon instead of the blank page.
- Install: `work\2026-11-23-modular-bar\install-dock-033.ps1` (refuses unless live = 0.3.2).

Owner, 2026-11-24, with a screenshot: "that line separator is miss-aligned, it should be properly
centered also adding separators for the dock, i should be able to right click and remove
separators/add separators". Folded into 0.3.3 (never installed):

- Centring: the line had gap + pad on its left and only pad on its right, so it sat 3 px right
  of the middle (measured 490 vs 487 and 611 vs 608 in the screenshot). Now gap + pad on both
  sides; the block is one gap wider.
- Own separators: `sepAfter` on a pin, saved in a new stored value `seps` (kind:value lines),
  apart from `pins` so 0.3.2 still reads the pin list on a rollback. Right-click a pinned app:
  "Add separator after" / "Remove separator after". Right-click a line (the room between two
  icons): "Remove separator". The bin menu: "Add/Remove separator before".
- The two built-in lines can go too: stored values `lineOpen` and `lineBin` (missing = on, not
  settings, so no defaults script is needed). Dock options has a Separators group with both.
- Drag uses the nearest pinned place (spacing is uneven now); separators keep their places while
  an app moves between them.

Installed 1:12 am 2026-11-24 (install-dock-033.ps1, syntax check clean, mods 363db46, feed
284a378). The installer again missed the tool restart and restarted it itself (new pid 18248);
desktop fine after 60 s. Live source equals the work copy (line endings aside). Work area still
0,56,2560,1366. Main screen capture index is 1.

Proof `D:\Agent Work\seamless-dock\proof\sep-1124\`: dock-after.png, measure.py on row 32: both
lines have 12 px of room on each side (382-393 | 394 | 395-406 and 455-466 | 467 | 468-479).
Menu test (`sep-test.ps1`, elevated, posted messages only) is queued for the desktop lock
(another thread held it at 1:20 am): run it under `coop lock desktop --input`, check
sep-test.log and the menu-*.png / dock-*.png captures.

## Rollback

- Dock 0.3.3: install `seamless-dock-0.3.2.wh.cpp` with Install-StagedMod.
- Dock 0.3.2: install `seamless-dock-0.3.1.wh.cpp` with Install-StagedMod.
- Styler: already rolled back. `reg import` the backup to see the old state.
- Dock: install `seamless-dock-0.1.0.wh.cpp` (or `-0.2.0`) with Install-StagedMod.
- Title: set `showTitle` to 1 and bump `SettingsChangeTime`.
