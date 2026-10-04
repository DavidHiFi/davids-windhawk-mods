# Window Manager

Move, resize and snap windows from anywhere, and send them to another monitor,
with the mouse or the keyboard. Works on administrator windows too.

![Window Manager preview](https://raw.githubusercontent.com/DavidHiFi/davids-windhawk-mods/main/media/previews/window-manager.gif)

## Features

- **Alt+drag to move.** Grab a window anywhere, not just by its title bar.
- **Alt+right-drag to resize** from the nearest edge or corner.
- **Snap with the keyboard** to halves, quarters, the center or almost
  maximized, with optional gaps around windows.
- **Send to another monitor** with a hotkey. Maximized windows stay maximized
  on the new screen.
- **Quick actions:** maximize, minimize, close or open the window menu without
  reaching for the title bar.
- **Auto-snap rules** place chosen apps in a set position.
- **Works on elevated windows** such as Task Manager and Task Scheduler.

## Default shortcuts

| Shortcut | Action |
| --- | --- |
| Alt + left drag | Move the window |
| Alt + right drag | Resize the window |
| Alt + Q / W / E / R | Left, right, top or bottom half |
| Alt + U / I / J / K | Top-left, top-right, bottom-left or bottom-right quarter |
| Alt + T | Center half |
| Alt + H / Y / G | Maximize, almost maximize, center |
| Alt + ] / [ | Next or previous monitor |
| Ctrl + Alt + arrow keys | Monitor in that direction |
| Alt + Z | Undo the snap |
| Alt + F | Toggle maximize |
| Alt + M | Minimize |
| Alt + Shift + Q | Close |
| Alt + middle click | Window menu |

Every shortcut can be changed or turned off in the settings. For Alt+arrow
snapping like the preview, set the four half keys to `left`, `right`, `up` and
`down`.

## Notes

- This mod replaces AltDrag, AltSnap, Snap Commander and Move Window to
  Monitor. Disable those before you enable it.
- Keyboard shortcuts run in a small elevated Windhawk helper, which is what
  lets them move administrator windows.

## Credits

Combines [AltDrag](https://windhawk.net/mods/alt-drag) by m417z (inspired by
[AltSnap](https://github.com/RamonUnch/AltSnap) by RamonUnch),
[Snap Commander](https://windhawk.net/mods/snap-commander) by Asteski and
[Move Window to Monitor](https://windhawk.net/mods/move-window-to-monitor) by
TomberWolf. GPL-3.0, following AltDrag.

## Install

1. Install [Windhawk](https://windhawk.net/).
2. Choose **Create a new mod**, paste [window-manager.wh.cpp](window-manager.wh.cpp) and click **Compile**.

To build the DLLs offline with Windhawk's bundled compiler, run `Build.ps1`.

License: GPL-3.0, see [COPYING](COPYING).
