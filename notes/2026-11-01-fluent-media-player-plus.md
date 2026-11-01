# Taskbar Fluent Media Player Plus (2026-11-01)

Our fork of Taskbar Fluent Media Player 1.6.0 (Salyts, MIT), with our Taskbar Audio Visualizer 1.3.3 merged in. Mod id `local@taskbar-fluent-media-player-plus`, live version 1.7.2.

## What it does

- The player runs inside the taskbar's Explorer process. The visualizer still runs in its own `-tool-mod` Explorer process, as it did before the merge.
- The player sits after Taskbar System Info, reading `WindhawkTaskbarSystemInfoRightDip` from Shell_TrayWnd. It publishes its own right edge as `WindhawkTaskbarMediaPlayerRightDip`, and the visualizer draws its bars from that edge.
- The fluent mod's own visualizer is forced off and its settings are gone. Its code is still in the source but never runs.
- 1.7.1 changes:
  - The right-click menu is a native Win32 popup menu, the same kind the visualizer uses, so both menus look the same.
  - When nothing is playing, the album box shows the music-note icon. Before, it showed a pause sign on a black box.
- 1.7.2 change: the visualizer's device menu now opens in the taskbar process.
  - Before, the tool process drew it, and the menu styling and shell font mods don't reach that process. It had a flat fill and Segoe UI.
  - Now the bars' input window posts `WindhawkFluentPlusShowCaptureMenu` to a hidden message window (`WindhawkFluentPlusMenuHost`) on the taskbar thread. The menu opens through `TrackNativeMenu`, the same function the player menu uses.
  - The chosen device is saved as `captureEndpointId`. The taskbar side then posts `WindhawkFluentPlusCaptureChanged` back to the bars, and they reopen capture.

## Owner settings (applied by the install script)

- Catppuccin Mocha colors:
  - text 205 214 244
  - artist line in blue 137 180 250
  - buttons, empty icon and menu icons in mauve 203 166 247
  - background in surface0 49 50 68 at 60% opacity, radius 10
- Fira Code Nerd Font for the title (size 11, Medium) and the artist (size 10).
- Always visible (`hideWhenNoMedia` 0).
- Slim size: height 36, art 28, text 116, buttons 26. The player went from 298 to 264 DIPs wide.

## Evidence (measured 2026-11-01, 9:46 to 9:59 pm)

- The 1.7.1 DLL is loaded in the taskbar Explorer and in the `-tool-mod local@taskbar-fluent-media-player-plus` process. The old player and old visualizer DLLs are no longer loaded.
- Shell_TrayWnd properties: sysinfo right edge 353, player right edge 617.
- Screenshots:
  - `reports\2026-11-01-fluent-media-player-plus\taskbar-full-171.png`
  - `reports\2026-11-01-fluent-media-player-plus\menu-probe.png`: the menu opened from a right-click, closed with Escape, and Explorer kept running.
- The 9:45 pm crash event (`local@taskbar-audio-visualizer_1.3.3_7.dll`, 0xc0000005) came from the old visualizer's tool process exiting when it was disabled. The 9:53 pm shell restart came from another thread swapping in Simple Window Switcher Plus, not from this mod.

## Evidence for 1.7.2 (measured 2026-11-01, 10:35 to 10:40 pm)

- The 1.7.2 DLL is loaded in the taskbar Explorer and in the tool process. The menu host window exists, and it belongs to the taskbar Explorer process.
- A right-click on the bars opened the menu with blur, the mauve border, rounded corners and Fira Code. The Input device submenu listed the active devices. Both Explorer processes kept running.
  - Screenshots: `reports\2026-11-01-fluent-media-player-plus\visualizer-menu-172.png` and `visualizer-submenu-172.png`.
- Choosing a device and the bars reopening capture: not checked yet. I didn't change the owner's capture source to test it.

## Files

- Merge script: `work\2026-11-01-fluent-media-player-plus\merge.py` (`python -I merge.py`).
- Build: `scripts\2026-10-27-taskbar-visualizer-build.ps1 -Source ... -ModId local@taskbar-fluent-media-player-plus -LibName local@taskbar-fluent-media-player-plus_1.7.2_1.dll`.
- Install, audit, rollback: `scripts\2026-11-01-fluent-media-player-plus-install.ps1`.
- Menu probe: `scripts\2026-11-01-fluent-menu-probe.ps1` (run under `coop lock desktop`).
- Backups of both original keys and sources: `backups\2026-11-01-fluent-media-player-plus\`.
- Readme preview: `davids-windhawk-mods\media\previews\taskbar-fluent-media-player-plus.png` (not pushed).

## Rollback

Run `Invoke-Elevated.ps1 -File scripts\2026-11-01-fluent-media-player-plus-install.ps1 -ArgumentList "-Mode Rollback"`. It turns Plus off and turns the original player and visualizer back on. The originals are disabled, not deleted.

## Open items

- The original catalog player and the standalone visualizer are still installed (disabled). They can be removed later.
