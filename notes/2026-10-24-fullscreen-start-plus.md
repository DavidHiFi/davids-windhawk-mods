# Fullscreen Start Plus: base and roadmap (2026-10-24)

Our fork of Fullscreen Start (Launchpad style) 1.0.0 by Rafael Mendes. It
replaces WinLaunch Enhanced, which the owner retired the same morning
(`H:\System Configuration\notes\2026-10-24-winlaunch-retired.md`). New launcher
ideas go here, not into WinLaunch.

## Where things are

| What | Where |
| --- | --- |
| Mod source | `work\2026-10-24-fullscreen-start-plus\repo\mods\local\fullscreen-start-plus\fullscreen-start-plus.wh.cpp` (worktree of `davids-windhawk-mods`, branch `fullscreen-start-plus`) |
| Upstream copy | `work\2026-10-24-fullscreen-start-plus\upstream\fullscreen-start.wh.cpp` |
| Build | `scripts\2026-10-24-fullscreen-start-plus-build.ps1`, output in `work\2026-10-24-fullscreen-start-plus\build\` |

## Base state (checked 2026-10-24, about 5:30 AM)

- Upstream pin: `ramensoftware/windhawk-mods` commit `6cea3b6` (2026-10-22,
  "Add Fullscreen Start (Launchpad style) (#6378)"), file sha256
  `95623d029039aefa35664256516c349923d4e848f98bf307835f40b46a19ab51`. Same text as the 1.0.0 the owner installed at
  2:46 AM (only line endings differ).
- Changes from upstream, nothing else: header (`@id fullscreen-start-plus`,
  name, description, `@author DavidHiFi, Rafael Mendes`, `@github`,
  `@homepage`, `@donateUrl https://ko-fi.com/DavidHiFi`), readme rewritten to
  `docs\mod-style-guide.md`, and the two window classes renamed to
  `WindhawkFullscreenStartPlus` / `...PlusBackdrop` so both mods can coexist
  without sharing a class name. Settings and code are untouched.
- Build: OK with Windhawk's clang against engine 2.0.0, 159,232 bytes,
  sha256 `A6911C799040E8003442651CA00B6E0A1378F7387BF932DD5EED7844301D6FA5`. The DLL imports `windhawk.dll`, exports
  `Wh_ModInit` and carries the Plus class names (checked by reading the bytes).
- Preview image: Rafael Mendes' upstream screenshot, credited. Replace it with
  our own once the first Plus feature changes the look.
- Repo: committed on branch `fullscreen-start-plus`, not pushed. The base is a
  near copy of a two-day-old catalog mod, so it ships (push + PR, per
  `github-repo-standard`) together with the first real enhancement.

## Not installed yet, on purpose

The freeze-8 hunt holds the `windhawk-engine` coop lock ("do not change mod
flags, install mods or restart the engine"), and the owner ordered no engine
changes without an explicit go. When that lock is free:

1. Disable the original `fullscreen-start` (both hook the same Start function).
2. Windhawk > Create a new mod, paste the `.wh.cpp`, Compile. Or copy it to
   `C:\ProgramData\Windhawk\ModsSource\` and compile from the editor.
3. Verify: Ctrl+Esc opens the Plus grid; mod log shows the `>` init line.
4. Rollback: disable Plus, re-enable the original.

Win key conflict (read 2026-10-24, 5:35 AM): Flow Launcher's hotkey is still
`LWin` (`%APPDATA%\FlowLauncher\Settings\Settings.json` line 2) and
`hide-start-button` is enabled, so the Windows key most likely opens Flow
Launcher, not this grid (inferred, not tested). Ctrl+Esc and Shift+Win should
reach it. Decide with the owner whether the Windows key moves to the grid.

## How it works (for whoever adds features)

- Hooks `XamlLauncher::ShowStartView` in `twinui.pcshell.dll` and posts a
  toggle to its own window instead of opening Start.
- One UI thread with a Direct2D layered window plus a backdrop window for the
  DWM blur modes. Custom blur = screenshot at open, blurred in D2D.
- Apps come from `shell:AppsFolder` on a worker thread, with icons, sorted by
  name. Reloaded on open when older than 60 seconds.
- One scrolling list. No pages, folders, context menu, pinning or hiding yet.

## Upstream sync

Diff the new upstream file against ours from the line after
`// ==/WindhawkModReadme==`; the only expected code difference is the two
class names. Re-apply our header and readme on top.

## Enhancement backlog (candidates, owner picks; nothing started)

From WinLaunch Enhanced, the things it did that this mod does not:

- Pages with page dots, swipe, Ctrl+Left/Right, instead of one long scroll.
- Folders: drop an app on another, folder preview of the first nine apps.
- Drag to rearrange, an edit mode (wiggle) with remove and undo.
- Hide apps, add custom tiles (files, folders, web links).
- Right-click menu: run as administrator, open file location, uninstall, hide.
- Ctrl+Shift+Enter opens the top result as administrator.
- Search keywords per app, optional most-used ranking, calculator in search.
- Themes: Catppuccin Mocha by default, plus Latte, Tokyo Night, Nord, Rose Pine.
- Background from the wallpaper, solid colour, dim strength.
- Other ways to open it: hot corner, double-tap Ctrl, and stay closed while a
  game or video is fullscreen.
- Layout controls: rows, label font and size, alphabetical or custom order.

Its saved layout is still in `%APPDATA%\WinLaunch\Items.xml` (and backed up),
if an import of the old tile order and folders is ever wanted.

## 1.1.0 (2026-10-24, about 6:05 AM): cover the whole screen + monitor choice

- New settings: `coverScreen` (off by default; on = full monitor rectangle,
  taskbar included, Standalone Dock not raised) and `monitor` (`mouse`, `1` main,
  `2`-`4` the rest left to right; a missing monitor falls back to the mouse).
- Installed live with `scripts\2026-10-24-fullscreen-start-plus-install.ps1`
  (6:01 AM): original `fullscreen-start` disabled, `local@fullscreen-start-plus`
  enabled with the original's settings plus coverScreen=1, monitor=mouse.
  Explorer loads `local@fullscreen-start-plus_1.1.0_1.dll` (module list).
  Rollback: the same script with `-Rollback`.
- Live test (`scripts\2026-10-24-fullscreen-start-plus-livecheck.ps1`, opens it
  with the mod's own toggle message): monitor=1 with the mouse on the left screen
  opened on DISPLAY2 at 0,0-2560,1440 (work area starts at y=50), screenshot
  `reports\2026-10-24-fullscreen-start-plus\live-main-monitor.png` shows no top
  bar. monitor=mouse opened on the mouse's screen. Setting put back to mouse.
- Change one setting from a script: `scripts\2026-10-24-fullscreen-start-plus-set.ps1`.
- Ctrl+Esc sent by keybd_event from a script does not open it (same as the
  2026-10-11 gotcha); real key presses are untested by me.

## 1.2.0 (2026-10-24, about 6:30 AM): Apps to show

- New `appSource` setting: `allApps` (default), `desktop` (user + public
  desktop, hidden items skipped), `both` (merged; same-name desktop shortcut
  dropped), `pinned` (Start pins in Start's order).
- Pins: read with Windows' `Export-StartLayout` (hidden powershell.exe, 30 s cap).
  start2.bin is AES-encrypted; a read-only decrypt
  (`work\2026-10-24-fullscreen-start-plus\research\decrypt_start2.py`) agreed
  with the export: this PC has 0 pins (`"pinnedList":[]`), so the pinned view
  shows "No apps are pinned to Start". Pinned entries themselves are untested
  live (scripts cannot pin: the Pin to Start verb returns access denied).
- Names ending in .lnk/.url lose the ending (this PC shows extensions).
- Installed `local@fullscreen-start-plus_1.2.0_2.dll`; live screenshots
  `reports\2026-10-24-fullscreen-start-plus\live-source-*.png`. Setting left
  at allApps.
