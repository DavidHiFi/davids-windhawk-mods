# AltSnap

Move and resize any window by holding Alt, and maximize, minimize or close it
with AltSnap-style shortcuts. Everything AltSnap does day to day, with no
separate app running.

![AltSnap preview](https://raw.githubusercontent.com/DavidHiFi/davids-windhawk-mods/main/media/previews/alt-snap-drag.gif)

## Features

- **Alt+drag to move.** Grab a window anywhere, not just by its title bar.
- **Alt+right-drag to resize** from the edge or corner nearest the cursor.
- **Window shortcuts** to maximize, minimize and close the active window.
- **Mouse actions** for middle, double and X-button clicks, such as opening
  the window menu or toggling always on top.
- **Right-click while moving** to toggle maximize, just like AltSnap.
- **Fully configurable** buttons, keys and an optional hold delay, so normal
  clicks keep working. Shortcuts accept `Alt+F` or the values from
  `AltSnap.ini`.

## Default controls

| Hold Alt and... | Action |
| --- | --- |
| Left drag | Move the window |
| Right drag | Resize the window |
| Press F | Toggle maximize |
| Press M | Minimize |
| Press Shift+Q | Close |
| Middle click | Window menu |
| Right click while moving | Toggle maximize |

## Notes

- Disable AltDrag before enabling this mod.
- To exclude a program, add it to the custom exclusion list in this mod's
  Advanced tab.
- Slick Window Arrangement uses Alt to pause snapping by default. Change that
  key in its settings if you want windows to snap while you Alt+drag them.
- For keyboard snapping and monitor hotkeys as well, use Window Manager, which
  includes everything in this mod.

## Credits

Based on [AltDrag](https://windhawk.net/mods/alt-drag) by m417z, with
shortcuts and gestures from [AltSnap](https://github.com/RamonUnch/AltSnap) by
RamonUnch. Both trace back to the original
[AltDrag](https://stefansundin.github.io/altdrag/) by Stefan Sundin. GPL-3.0.

## Install

1. Install [Windhawk](https://windhawk.net/).
2. Choose **Create a new mod**, paste [alt-snap.wh.cpp](alt-snap.wh.cpp) and click **Compile**.

License: GPL-3.0.
