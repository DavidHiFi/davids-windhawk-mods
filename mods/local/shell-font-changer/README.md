# Shell Font Changer

Replace the font used across File Explorer and the Windows shell with any font
you have installed.

![Shell Font Changer preview](https://raw.githubusercontent.com/DavidHiFi/davids-windhawk-mods/main/media/previews/shell-font-changer.png)

## Features

- **Changes text in File Explorer, Start, Search and Settings.**
- **Icons and emoji stay intact.** Symbol and icon fonts keep their own
  glyphs, so buttons never turn into empty boxes.
- **Keeps font weights.** Semibold and bold text stays semibold and bold.
- **Covers classic, themed and modern text**, including DirectWrite layouts.
- **Fits text to controls.** Keeps normal text size. Shrinks slightly when a fixed box would clip, and uses the original UI font where Fira Code cannot fit readably.
- **Nothing is written to the registry**, so turning it off is fully clean.

## How to use

Type an installed font family name in the settings, such as
`FiraCode Nerd Font` or `Inter`. Leave it empty to turn the mod off.

Some apps, such as Chromium browsers, draw text with their own fonts and keep
them. Windows that were already open may need to be reopened.

Disable the original Explorer Font Changer before enabling this mod.

## Credits

Based on [Explorer Font Changer](https://windhawk.net/mods/explorer-font-changer)
by Gabriela Cristei. MIT.

## Install

1. Install [Windhawk](https://windhawk.net/).
2. Choose **Create a new mod**, paste [shell-font-changer.wh.cpp](shell-font-changer.wh.cpp) and click **Compile**.

To build the DLLs offline with Windhawk's bundled compiler, run `Build.ps1`.

`Build.ps1 -Test` also builds and runs the regression tests in [tests](tests).

License: MIT.
