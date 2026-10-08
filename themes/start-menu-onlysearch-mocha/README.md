# OnlySearch Mocha

A [Windows 11 Start Menu Styler](https://windhawk.net/mods/windows-11-start-menu-styler)
theme for the redesigned Start menu. It merges two themes from the
[styling guide](https://github.com/ramensoftware/windows-11-start-menu-styling-guide):
the [OnlySearch](https://github.com/ramensoftware/windows-11-start-menu-styling-guide/blob/main/Themes/OnlySearch/README.md)
layout, and the rounded borders and power row from
[RosePine](https://github.com/ramensoftware/windows-11-start-menu-styling-guide/blob/main/Themes/RosePine/README.md).
The colors come from [Catppuccin Mocha](https://github.com/catppuccin/catppuccin)
instead of Rosé Pine.

The Start menu shrinks to the search box and a bottom row with settings and
power buttons. Pinned apps, recommendations and the side panel are hidden.

| Part | Mocha color |
| --- | --- |
| Background (blurred) | base `#1E1E2E` |
| Border, icons | blue `#89B4FA` |
| Search box, buttons | surface0 `#313244` |
| App names | text `#CDD6F4` |
| Settings icons | lavender `#B4BEFE` |
| Search placeholder | overlay0 `#6C7086` |

## Install

1. Install the Windows 11 Start Menu Styler mod in Windhawk (made on 1.7).
2. Open the mod's **Settings** tab and switch to **Textual mode**.
3. Replace everything with the contents of
   [onlysearch-mocha.yaml](onlysearch-mocha.yaml) and click **Save settings**.
4. In **Settings > Personalization > Start > Folders**, turn off every folder
   except Settings, as the RosePine theme asks. Extra folders crowd the power
   button.

The search placeholder uses JetBrainsMono Nerd Font (`JetBrainsMono NF`). Without
it, Windows falls back to the default font.

## With Everything Start menu Plus

Use [onlysearch-mocha-everything-plus.yaml](onlysearch-mocha-everything-plus.yaml) with [Everything & Power Tools in the Start Menu Plus](../../mods/local/start-everything-plus). It leaves room for expanded search results and uses one power glyph per icon slot. The mod keeps the idle menu compact. If Start Menu Size is installed, set its fixed menu height to 0.

The original theme and glyph repair script below remain for the standalone theme.

## Power row icons

The power row relabels the power button with four Segoe Fluent Icons glyphs:
lock `U+E72E`, sleep `U+E708`, power `U+E7E8` and restart `U+E777`. Two more
selectors match the settings glyphs `U+F78B` and `U+E713`. These are
private-use characters, so they look blank in most editors.

Some browsers and editors drop these characters when the file is copied as text.
If the power button shows the wrong label after saving, download the raw file
rather than copying it from a rendered page. You can also write the four values
straight to the registry with
[set-power-glyphs.ps1](set-power-glyphs.ps1) from an elevated shell.

## License

The layout comes from the OnlySearch theme by
[jonas-usx](https://github.com/jonas-usx) and the RosePine theme by
[asev](https://github.com/lunar-os). Both are distributed with the styling
guide. The palette is Catppuccin's, MIT.
