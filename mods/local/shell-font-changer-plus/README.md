# Shell Font Changer Plus

[☕ Support on Ko-fi](https://ko-fi.com/DavidHiFi)

Change the text font in File Explorer, Start, Search and Settings to any font
you have installed. Icons and emoji keep their own glyphs, so buttons never
turn into empty boxes.

![Shell Font Changer Plus preview](https://raw.githubusercontent.com/DavidHiFi/davids-windhawk-mods/main/media/previews/shell-font-changer-plus.png)

## Features

- **Shell-wide text.** File Explorer, Start, Search and Settings all follow the
  font you pick.
- **Icons and emoji stay intact.** Symbol and icon fonts keep their own glyphs,
  so buttons never show empty boxes.
- **Weight is kept.** Semibold and bold text stays semibold and bold.
- **Classic, themed and modern text.** GDI text, visual-style themes and
  DirectWrite layouts are all covered.
- **Text fits its controls.** Text that would overflow shrinks a little, to no
  less than 85% of its height or 80% of its width. If it still overflows, the
  original UI font draws it.
- **Clean to remove.** The mod writes nothing to the registry, so turning it off
  leaves nothing behind.

## How to use

Type an installed font family name in the settings, such as `FiraCode Nerd Font`
or `Inter`. Leave the field empty, or type `None`, to turn the mod off.

If the font is not installed, or its name is 32 characters or longer, the mod
does not start. The Windhawk log says why.

Some apps, like Chrome and Edge, draw text with their own fonts and keep them.
Windows that were already open may need to be reopened.

Turn off the original Explorer Font Changer before you turn this one on.

## Credits

Based on [Explorer Font Changer](https://windhawk.net/mods/explorer-font-changer)
by Gabriela Cristei. MIT.

## Install

1. Install [Windhawk](https://windhawk.net/).
2. Choose **Create a new mod**, paste [shell-font-changer-plus.wh.cpp](shell-font-changer-plus.wh.cpp) and click **Compile**.

To build the DLLs offline with Windhawk's bundled compiler, run `Build.ps1`.

`Build.ps1 -Test` also builds and runs the regression tests in [tests](tests).

License: MIT.
