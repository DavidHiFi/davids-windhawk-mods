# Fullscreen Start Plus

Replaces the Start menu with a fullscreen grid of all your apps, in the style
of the macOS Launchpad, with instant search and a blurred background.

![Fullscreen Start Plus preview](../../../media/previews/fullscreen-start-plus.png)

## Features

- **Fullscreen.** Fills the monitor the mouse is on, or one monitor you pick.
  It leaves the taskbar, side bars and the Standalone Dock visible, or covers
  the whole screen if you turn that on.
- **Your choice of apps.** The "All apps" list of Start, your desktop icons,
  both together, or only the apps you pinned to Start.
- **Scroll or pages.** One list that scrolls, or pages that flip left and
  right with dots below, like Launchpad.
- **Instant search.** Just type. Case and accents don't matter, and names that
  start with your text come first.
- **Adjustable blur.** Pick the blur type, strength, opacity and color of the
  background.
- **Opens like Start.** The Windows key, Ctrl+Esc and the Start button of the
  taskbar or the Standalone Dock all open it.
- **Your own Windows key.** The Windows key, Shift + Windows key and the Start
  button can each open this grid, the original Start, or a program of your
  choice, such as a launcher. The program starts even when it isn't running,
  so this replaces the same feature of Open-Shell.

## Keyboard and mouse

| Key | Action |
| --- | --- |
| Type | Search |
| Backspace, Ctrl+Backspace | Delete a letter, or the last word |
| Ctrl+V | Paste |
| Arrows, Enter | Pick an app and open it. While searching, the first result is already picked |
| Esc | Clear the search, or close when the search is empty |
| Mouse wheel, Page Up, Page Down | Scroll, or flip pages |
| Sideways scroll, page dots | Flip pages |

Clicking outside the icons or switching to another window closes it.

## Notes

- Disable the original Fullscreen Start (Launchpad style) before you enable
  this mod. Both replace Start, so only one should run.
- Set **Windows key**, **Shift + Windows key** or **Start button** to "Open
  the original Start" to get the normal Start menu for that action. Shift +
  Windows key opens it by default.
- If Open-Shell or another Start replacement also takes the Windows key, turn
  that feature off there, or it gets the key first.
- The first time the mod loads, Windhawk downloads the symbols of
  `twinui.pcshell.dll`, which can take a minute.

## Install

1. Install [Windhawk](https://windhawk.net/).
2. Choose **Create a new mod**, paste [fullscreen-start-plus.wh.cpp](fullscreen-start-plus.wh.cpp) and click **Compile**.

## Credits

Based on [Fullscreen Start (Launchpad style)](https://windhawk.net/mods/fullscreen-start)
by [Rafael Mendes](https://github.com/RafaelMendes1407), who also made the
preview image. MIT.
