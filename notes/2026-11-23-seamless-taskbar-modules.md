# Seamless Taskbar 0.4.46: Modules menu, tray corner, hide all app buttons (2026-11-23)

Installed 5:44 am, published (mods 5e2727b, feed 7f4bbcc). Thread a65eb88a.

## What changed
- Right-click on empty taskbar space: a Modules submenu with on/off for every module
  (tray icons, Logitech battery, AI usage, date and time, system stats, media and the
  rest) and a Dock position choice (auto, bottom, top, left, right) that talks to
  Seamless Dock over its SeamlessDock.Control message (wp 1 state, 2 place, 3 Recycle
  Bin, 4 title, 5 taskbar moved).
- utils.modules.showTray hides the whole right corner. utils.modules.showClock hides
  only the date and time.
- apps.HideAllButtons hides every app button, running ones too. Done in the apps module
  (TaskListButton_IsRunning answers false, ApplyToFrame forces collapse), never with a
  Taskbar Styler rule: the Styler collapse of TaskListButton froze the taskbar at 3:08 am.
- 0.4.46 sits on another thread's 0.4.45 (text boxes on the settings card). The readme
  now has an "Earlier: 0.4.45" line for it.
- The dock (seamless-dock) is NOT part of this; thread 9036a277 owns it (0.3.1).

## Proof
- Test PC run (net on for symbols), D:\Agent Work\2026-11-23-modular-bar-vm\results:
  A defaults, B hide all, C tray off, D tray on and clock off, E back. Explorer the same
  process the whole run, 0 crash dumps, 0 error events.
- At 1024 wide (test PC only), hide all with tray and clock both on pushed the tray and
  clock off the right edge. Fine at 2560 on the tower. Watch for it on narrow screens.
- Tower after install: Install-StagedMod watched 60 s, desktop fine; check-dock-align ok.
  apps.HideAllButtons set to 1 at 5:48 am (was absent = off). Top strip shows no app
  buttons with the tray, battery and clock still there; Explorer pids unchanged.
  Capture: work\2026-11-23-modular-bar\after-hideall.png.

## Rollback
- Setting: work\2026-11-23-modular-bar\hide-all.ps1 -On 0 (elevated), or the Modules menu.
- Mod: backup local@seamless-taskbar-20261123-0544.wh.cpp from Install-StagedMod.
