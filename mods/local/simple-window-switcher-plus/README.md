# Simple Window Switcher Plus

Vista's animated live-window layouts and blurred background, with Simple Window Switcher's configurable layout and shared appearance controls.

![Preview](https://raw.githubusercontent.com/DavidHiFi/davids-windhawk-mods/main/media/previews/simple-window-switcher-plus.gif)

## Features

- Vista Flip 3D, Cascade, Cover Flow and the other original animated layouts.
- Simple layout preserves the original grouping, badge, corners, dimensions and navigation settings.
- Shared title font, icon visibility, window exclusions, monitor filtering and minimized-window ordering in Vista mode.
- Custom or accent selection borders and background tint in Vista mode.
- Dedicated administrator host handles shortcuts while elevated apps have focus.
- Ctrl+Alt+Tab sticky mode and Q, Delete or Ctrl+W to close the selected window.
- Change layouts in Settings without restarting Explorer.

## Settings

Choose the switcher layout first. Animation and background settings control Vista mode. Style, Theme, Appearance, Dimensions, Grouping and Accessibility control Simple mode. Vista also uses the shared font, icon/title visibility, theme border/background colors, exclusions, per-monitor filtering and minimized-window sorting. Badge layouts, grouping and thumbnail corner settings apply to Simple mode.

Disable other Alt+Tab replacements before enabling this mod. Administrator hosting requests Windows elevation when needed. It does not replace shortcuts on the secure UAC desktop. Windows that block capture show an icon card.

Hold Alt and press Tab to cycle. Shift reverses direction. Release Alt to switch, or press Escape to cancel. Ctrl+Alt+Tab stays open until Enter, a click or Escape.

## Install

In Windhawk, choose Create a new mod, paste `simple-window-switcher-plus.wh.cpp` and compile. Disable the original Simple Window Switcher and Alt+Tab Flip 3D mods first. Your existing preferences can be entered in the new mod's Settings.

`Build.ps1` also builds both architectures with Windhawk's installed compiler. The DLLs go in the ignored `build` folder.

## Credits

Based on Simple Window Switcher 2.1 by Lone, with improvements by Asteski and bropines, and the original Simple Window Switcher by valinet. Vista rendering is from Alt+Tab Flip 3D 1.5.3 by caliberda. The combined mod is GPL-2.0; the Vista source retains its MIT notice in the source file.
