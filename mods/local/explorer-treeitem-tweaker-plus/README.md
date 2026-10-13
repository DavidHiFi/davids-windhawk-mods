# Explorer TreeItem Tweaker Plus

![Explorer TreeItem Tweaker Plus preview](https://raw.githubusercontent.com/DavidHiFi/davids-windhawk-mods/main/media/previews/explorer-treeitem-tweaker-plus.png)

**Explorer TreeItem Tweaker** is a Windhawk mod that customizes the appearance of tree items in the left navigation pane of Windows Explorer.

It is designed for people who want the navigation tree to look cleaner, more polished, and more comfortable to use.

**Recommended setup**  
For the best Explorer navigation pane experience, it is recommended to use this mod together with **[Explorer Navigation Tree Offset](https://windhawk.net/mods/explorer-navigation-pane-tweaks)** and **[Explorer TreeLine Killer](https://windhawk.net/mods/explorer-treeline-killer)**.

## ⚠️ Important: dark theme defaults

**The default settings are designed for the dark Windows system theme.**

For a correct and clean appearance on the light Windows theme, adjust the mod settings manually, especially the text color.

For example, for light theme text, try:

`R = 0, G = 0, B = 0`

## Before / After
![Before / After](https://raw.githubusercontent.com/Languster/assets-windhawk-mods/main/mods_assets/explorer-tree-item-tweaker-before-after.jpg)

## Width mode note
System Width mode (0) uses the original TreeView menu item background width and is not recommended if you use **Explorer Navigation Tree Offset**, in order to avoid background clipping.

Use **Width By Text** or **One Width For All** instead.

## Features
- customize background, border, and text colors for these states:
  - Hot
  - Selected
  - Selected Not Focus
  - Hot Selected
  - Normal Text
- adjust:
  - width
  - corner radius
  - vertical insets
  - item height
  - icon size
  - icon-text gap
  - Quick Access pin button hiding
  - custom font face and size
  - color
  - background opacity
  - border opacity
  - text color

## Why this is better than editing msstyles
Editing `msstyles` does not come close to this level of flexibility.

With this mod, you can:
- change settings directly in Windhawk
- control colors, opacity, and states much more precisely
- get cleaner shapes and smoother rounded corners
- avoid editing system theme resources

In practice, this is a much faster, more convenient, and more powerful way to customize the navigation tree.

## Compatibility
Tested and confirmed compatible with **Windows 11 versions 23H2 through 25H2**.
Other versions have not been tested.

## Important
- this mod changes only the tree view in the left navigation pane of Explorer
- it does not change the Explorer window background
- background, border, and text can be customized independently
- optional layout controls can change item height, icon size, and icon-text gap
- **Item Height** changes the total row height of tree items
- **Icon Size** changes the width and height of the navigation icons
- **Icon-Text Gap** adds space between the icon and the text
- **Hide Pin Button** hides the Quick Access pin button in the navigation tree
- **Custom Font** changes the tree item text font face and size
- **Text Font Weight** and **Text Font Style** can be configured separately for each text state

## Layout controls
- **Item Height** increases or decreases the total height of each navigation row
- **Icon-Text Gap** controls the horizontal spacing between the icon and the text
- **Icon Size** controls the width and height of navigation icons

Most layout options have their own enable switch.
When a switch is off, that option is not applied.

## Custom Font
The **Custom Font** block controls the common tree item font face and size before per-state text settings.

This block does not need a separate enable switch. Empty or `0` values keep the native Explorer font and the custom font code is not applied.

- **Font Face**: leave empty to keep the native Explorer font family
- **Font Size**: `0` = default/native size

Text weight and style are configured inside each text state block:

- **Font Weight**: `0` = default, `1` = semibold, `2` = bold
- **Font Style**: `0` = default, `1` = italic, `2` = underline, `3` = italic + underline

## Credits

Based on [Explorer TreeItem Tweaker](https://windhawk.net/mods/explorer-treeitem-tweaker) by [Languster](https://github.com/Languster). Plus changes by DavidHiFi.

Thanks to [crazyboyybs](https://github.com/crazyboyybs) for extending the functionality.
Thanks to [valinet](https://github.com/valinet) for the Hide Pin Button function.
