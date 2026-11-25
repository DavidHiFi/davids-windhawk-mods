# 2026-11-24: short right-click menu for the tray drawer folders (Seamless Taskbar 0.4.53)

Owner: the folder menu was "an ugly bloated giant list". A folder should just hold the tray
icons dragged onto it; right-click should offer empty, change icon and other options.

## What changed

- The tick list of every tray icon is gone (old `ShowGroupMenu`, header "<name>: tick the
  icons this folder holds").
- New right-click menu on each folder:
  - "Drag tray icons here" (greyed hint, only while the folder is empty)
  - Empty folder: puts every icon back in the drawer (clears the folder's stored keys and
    removes them from the collection, then refreshes)
  - Icon: Folder, Star, Three dots, Grid, Heart, Clock (current one ticked)
  - Color: nine Mocha colours, each item shows the folder glyph in that colour
  - Settings: opens the mod's settings window
- A pick from the menu takes effect at once with no mod reload: it is kept in mod storage
  (`<collection key>.look<slot>`, tab-separated: picked glyph, picked colour, settings
  glyph, settings colour). If the settings window value changes later, the settings
  window wins again.
- Clicking an empty folder no longer opens the tick list; dragging an icon onto a folder
  files it there (unchanged, `kCollectDroppedIconMessage`).
- Setting help text now reads "Drag a tray icon onto it to put it there. Right-click it to
  empty it or change its icon and color".

## Install

- Built as 0.4.52 on 0.4.51, but the wallpaper switcher thread landed its own 0.4.52 first
  (4:20 am). Rebased with `work\2026-11-24-tray-folder-menu\patch.py` on the live file and
  installed as 0.4.53 at 5:00 am.
- Syntax: `scripts\port-tray-menu.py syntax` compiles (after moving the
  `UpdateDrawerAppearance` forward declaration above `ApplyFolderLooks`).
- Install-StagedMod: registry v0.4.53, cli exit 0, 60 s watch "desktop fine", dock line-up
  ok, published (mods 121e5f7, feed 334c19f). Backup:
  `local@seamless-taskbar-20261124-0500.wh.cpp` in the installer backups.

## Trap found

- Through Invoke-Elevated, an Install-StagedMod `throw` leaves an empty log and exit 1: the
  throw stops the `| Out-File` pipeline before anything is written. Wrap the call in a
  small script in C:\Users\Public with try/catch writing to its own file to see the error.
- The big taskbar source (4.3 MB) took longer than the 120 s CLI limit while the PC was
  busy. `-TimeoutSec 480` fixed it.

## Footer buttons fix (0.4.54 plan, ships as 0.4.56 or next free)

- Owner screenshot: the first folder tile's outline touched the drawer's left border.
- Cause: `AlignFooterToIcons` lets the footer grid margin go negative (down to -40) so the
  end buttons centre on the first and last icon columns. With few columns that pushes the
  end button onto the panel edge.
- Fix: clamp both side margins at -3 (footer padding 8 minus 3 = about 5 px, the same as
  the gap under the buttons). The end buttons can sit a few px off the icon centres.
- Staged by `work\2026-11-24-tray-folder-menu\patch-0454.py` on the live 0.4.53 (CRLF
  kept), installed by `install-0454.ps1`.
- Second owner report (via thread 0abc5424, 7:00 am): a white outline round a folder
  spilled past the drawer. It is the system focus ring after a click, drawn 3 px outside
  the button. Fix: `UseSystemFocusVisuals(false)` on the three folder buttons and the
  overflow button, and all four shrink from 40 x 32 to 32 x 28 (height follows
  footer height minus 12). Hover keeps the blue to mauve edge.
- Version clash: 0abc5424 was installing 0.4.55, so the 0.4.54 install was stopped.
  `patch-gap.py` now patches any base and `pipeline.sh` waits for the live file to move,
  rebases, checks and installs as live + 1.
- Before capture: menu.png, the folder outline 2 px from the drawer's left border.
- Trap: the first patch wrote LF line endings and the file shrank by about 97 KB. Write
  with `newline=chr(13)+chr(10)` and compare sizes before staging.
- 7:51 am: neither 0.4.55 nor 0.4.56 landed in time, so 862b5548 installs its wallpaper
  motion as 0.4.57 on live 0.4.53. This fix rebases on that and ships as live + 1
  (expected 0.4.58). On a gate refusal the syntax check runs through
  `skipqueue-syntax.py` (a copy of the skip-queue runner) instead of looping.

- 25 Nov 11:45 pm: the 0.4.58 build passed its check, but live had moved (LIVE MOVED,
  nothing installed). Thread b8772f21 shipped 0.4.58 at 1:47 am and is installing 0.4.59
  with its own side-gap clamp (`pad.Bottom - pad.Left`). `patch-gap.py` now keeps that
  clamp and adds only the smaller buttons and no focus ring.
- 26 Nov 2:29 am: `run-0460.py` (hidden one-shot scheduled task) waits for the engine
  lock, then under it rebases on live, runs the check and installs as live + 1 (0.4.60).
- 26 Nov 3:02 am: installed 0.4.60 on 0.4.59. Check compiles, registry v0.4.60, cli exit 0,
  60 s watch "desktop fine", dock line-up ok, published (mods 0adcd59, feed 83ef343).
  Backup `local@seamless-taskbar-20261126-0253.wh.cpp`. Live hash equals the staged file.
- Trap: the coop lock lasts 30 minutes; a check plus install under it took 33. Take the
  lock just before the install step, or renew it, on jobs that long.
- After captures (`drawer-capture.py`) waited for the desktop lock while the owner played.
  At 3:05 am the owner said skip the queue: `drawer-after.png`, `after-left-4x.png` and
  `after-right-4x.png` show the end folders clear of both side borders at rest. The click
  outline is not captured (that needs the cursor); it is off in code on all four buttons.
- Trap: invoking the tray button a second time left the drawer open. A posted Escape to
  the drawer and its input child closed it; `drawer-capture.py` now does that.

## Drawer icon focus ring (0.4.61)

- 26 Nov 3:10 am, owner screenshot: a white rounded outline round the top-left icon inside
  the drawer, cut off by the drawer's top and left edge.
- Cause: the mod never styles the drawer's own icons (`ApplyTrayChrome` only walks the
  taskbar and `SystemTrayFrameGrid`), so the stock system focus ring shows. It draws 3 px
  outside the icon.
- Fix (`patch-focus.py`): `HookQuietFocus` on the drawer root, the inner drawer and the
  folder view. A tree pass turns `UseSystemFocusVisuals` off on every control inside a
  `SystemTray.*IconView`, again after each collection refresh, and a `GotFocus` handler
  catches icons made later. `RemoveDrawer` revokes the handlers and clears the values.
- Check compiles. Installed by `run-0461.py` (hidden one-shot task `tray-focus-0461`).
- 3:26 am: the first run reached the install step, then died with the T3 restart before
  anything changed (live stayed 0.4.60, empty install log). Restarted at 3:58 am.
- The taskbar stats thread also staged a 0.4.61 (C:\Users\Public\seamless-taskbar-0461).
  Whichever lands first keeps the number; `run-0461.py` rebases on live as live + 1.
- Trap: in a generic lambda, `args.OriginalSource().try_as<T>()` fails to compile
  ("use 'template' keyword"). Give the handler its real `RoutedEventArgs` type.
- 26 Nov 4:30 am: installed 0.4.61 on 0.4.60. Registry v0.4.61, cli exit 0, 60 s watch
  "desktop fine", dock line-up ok. Live hash equals the staged file. Backup
  `local@seamless-taskbar-20261126-0420.wh.cpp`. The installer's publish step timed out
  at 180 s after pushing the mod source (e64b1bb); a rerun of `publish-mods.py --mod`
  pushed the feed (70301f5).
- Proof (`drawer-key-capture.py`, under `coop lock desktop --input`): drawer opened by
  accessibility, Right then Left put keyboard focus on Seamless Windows Firewall, the
  top-left icon from the owner's screenshot. `after-focus\key-focus.png` and
  `key-focus-topleft-4x.png`: no outline, the icon sits clear of the edge.
- Trap: accessibility SetFocus on a drawer icon sends focus to the "Show Hidden Icons"
  button and the drawer closes. Use arrow keys under the input lock instead.
- `C:\Users\Public\taskbar-0.4.61.wh.cpp` belongs to the taskbar stats thread; left alone.

## Undo

Install the backup above (0.4.52) with Install-StagedMod, or turn the menu change back by
restaging 0.4.52 from `work\2026-11-24-tray-folder-menu\seamless-taskbar-0.4.52.wh.cpp`.
