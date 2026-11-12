// ==WindhawkMod==
// @id              seamless-color-picker
// @name            Seamless Color Picker
// @description     A full color picker on a hotkey, with a screen magnifier, recent colors and one-click copy
// @version         1.1.3
// @author          DavidHiFi, Jaex, ShareX contributors
// @github          https://github.com/DavidHiFi
// @homepage        https://github.com/DavidHiFi/davids-windhawk-mods
// @donateUrl       https://ko-fi.com/DavidHiFi
// @include         windhawk-mod.exe
// @compilerOptions -ld2d1 -ldwrite -lwindowscodecs -lole32 -loleaut32 -luuid -lgdi32 -luser32 -lshell32 -lshlwapi -ladvapi32 -ldwmapi -lcomctl32 -luxtheme -lcomdlg32 -limm32
// ==/WindhawkMod==

// ==WindhawkModReadme==
/*
# Seamless Color Picker

Press a hotkey and a color picker opens, laid out like the one in ShareX: a
color box, a slider, every color value you need, and a magnifier that picks any
pixel on your screen. It runs on its own, so ShareX doesn't need to be open.

![Seamless Color Picker preview](https://raw.githubusercontent.com/DavidHiFi/davids-windhawk-mods/main/media/previews/seamless-color-picker.png)

## Features
- **The ShareX layout.** Color box and slider on the left, new and old color,
  then hue, saturation, brightness, red, green, blue, alpha, CMYK, hex and
  decimal. Pick which value the slider controls.
- **Pick from the screen.** A frozen copy of the screen with a zoomed
  magnifier, a pixel grid and the color under the cross. Arrow keys move one
  pixel at a time.
- **Live sampling.** Hold Ctrl while the picker is open to follow the color
  under the mouse.
- **One-click copy.** Copy as hex, RGB, CSS, HSV, HSL, CMYK, decimal or your own
  pattern. A small card shows what was copied.
- **Recent colors.** The last colors you copied stay one click away, with the
  Catppuccin palette beside them.
- **Frosted glass look.** Catppuccin Mocha with blue to mauve gradients, and you
  can change the colors, the glass and the corners.

## Default shortcuts
| Key | What it does |
|---|---|
| Alt + Win + C | Open the color picker |
| Ctrl + C or Enter | Copy the color |
| Ctrl + V | Take a color from the clipboard |
| P | Pick from the screen |
| Hold Ctrl | Follow the color under the mouse |
| Esc | Close |

In the screen picker: click or Enter picks, right click or Esc cancels, the
arrow keys move one pixel (ten with Shift), the mouse wheel zooms.

## Notes
- Turn off the color picker hotkey in ShareX (or any other app) first. Two
  apps can't use the same hotkey.
- Write hotkeys like `Alt+Win+C` or `Ctrl+Shift+P`. Leave one empty to turn it
  off.
- 8-digit hex codes read as `#AARRGGBB`, the Windows order.

## Credits
Based on the color picker in [ShareX](https://github.com/ShareX/ShareX) by
Jaex and the ShareX contributors (GPL-3.0). Written again in C++ for Windhawk.
*/
// ==/WindhawkModReadme==

// ==WindhawkModSettings==
/*
- Keys:
  - hotkey: Alt+Win+C
    $name: Open the picker
    $description: The hotkey that opens the color picker. Press it again to close it. Leave empty to turn it off.
  - screenHotkey: ""
    $name: Pick from the screen
    $description: A hotkey that goes straight to the screen magnifier, like Ctrl+Shift+C. Leave empty to turn it off.
  - screenPickAction: copy
    $name: After a screen pick
    $description: What the screen hotkey does with the color you pick.
    $options:
    - copy: Copy it
    - copyopen: Copy it and open the picker
    - open: Open the picker with it
  $name: Keys
- Picker:
  - startColor: last
    $name: Starting color
    $description: The color the picker shows when it opens.
    $options:
    - last: The last color you used
    - clipboard: A color on the clipboard, else the last one
    - custom: The color below
  - customStartColor: "#89B4FA"
    $name: Custom starting color
    $description: 'Used when Starting color is "The color below". As #RRGGBB.'
  - sliderMode: hue
    $name: Slider controls
    $description: Which value the tall slider changes. The box shows the other two.
    $options:
    - hue: Hue
    - saturation: Saturation
    - brightness: Brightness
    - red: Red
    - green: Green
    - blue: Blue
  - recentCount: 16
    $name: Recent colors
    $description: 'How many recent colors to keep. 0 to 24 (Suggested: 16). 0 hides the row.'
  - showPalette: true
    $name: Show the Mocha palette
    $description: A row of Catppuccin Mocha colors under the recent ones.
  - livePick: true
    $name: Hold Ctrl to sample
    $description: While the picker is in front, holding Ctrl follows the color under the mouse.
  - alwaysOnTop: true
    $name: Always on top
    $description: Keep the picker above other windows.
  - rememberPosition: true
    $name: Remember where it was
    $description: Open where you left it. Off, it opens beside the mouse.
  $name: Picker
- Screen:
  - magnifierShape: circle
    $name: Magnifier shape
    $description: The shape of the zoomed view.
    $options:
    - circle: Circle
    - square: Rounded square
  - magnifierPixels: 15
    $name: Pixels across
    $description: 'How many screen pixels the magnifier shows across. 7 to 31 (Suggested: 15). Even numbers go up by one.'
  - magnifierZoom: 10
    $name: Zoom
    $description: 'How big each pixel is drawn. 4 to 24 (Suggested: 10). The mouse wheel changes it while picking.'
  - showGrid: true
    $name: Pixel grid
    $description: Thin lines between the zoomed pixels.
  - showCrosshair: true
    $name: Crosshair
    $description: Faint lines across the whole screen through the mouse.
  - showInfo: true
    $name: Color and position card
    $description: Shows the hex code and the X and Y position under the magnifier.
  $name: Screen picker
- Copying:
  - copyFormat: hex
    $name: Copy as
    $description: The format the Copy button, Enter and Ctrl+C use.
    $options:
    - hex: "#89B4FA"
    - hexplain: 89B4FA
    - hexalpha: "#FF89B4FA (with opacity)"
    - rgb: 137, 180, 250
    - cssrgb: rgb(137, 180, 250)
    - cssrgba: rgba(137, 180, 250, 1)
    - hsv: hsv(217, 45%, 98%)
    - hsl: hsl(217, 92%, 76%)
    - cmyk: 45%, 28%, 0%, 2%
    - decimal: "9024762"
    - custom: My own pattern
  - customFormat: "{hex}"
    $name: My own pattern
    $description: Used when Copy as is "My own pattern". Words in braces are filled in, {hex} {r} {g} {b} {a} {h} {s} {v} {c} {m} {y} {k} {dec}, and {px} {py} for the screen position. {y} is yellow.
  - upperCase: true
    $name: Capital hex letters
    $description: "On, #89B4FA. Off, #89b4fa."
  - closeAfterCopy: false
    $name: Close after copying
    $description: Close the picker once you copy with the Copy button, Enter or Ctrl+C.
  - showToast: true
    $name: Show what was copied
    $description: A small card near the mouse with the copied color.
  $name: Copying
- Look:
  - accent: "#89B4FA"
    $name: Accent color
    $description: "Where the gradients start. Suggested Mocha blue, #89B4FA."
  - accent2: "#CBA6F7"
    $name: Second accent color
    $description: "Where the gradients end. Suggested Mocha mauve, #CBA6F7."
  - glass: true
    $name: Frosted glass
    $description: On, the picker is blurred glass. Off, it is solid Mocha.
  - glassTint: 85
    $name: Glass tint
    $description: 'How dark the glass is. 60 to 100 (Suggested: 85). Higher hides more of what is behind.'
  - cornerRadius: 8
    $name: Corner roundness
    $description: 'For boxes, buttons and swatches. 2 to 14 (Suggested: 8).'
  - glow: true
    $name: Hover glow
    $description: A soft blue to mauve glow around the box you point at.
  - animations: true
    $name: Animations
    $description: Short fades on hover. Off, changes are instant.
  - font: FiraCode Nerd Font
    $name: Font
    $description: Any installed font. Falls back to Segoe UI.
  $name: Look
- SettingsWindow:
  - settingsGlass: true
    $name: Blurred settings window
    $description: On, the settings window is see-through glass with Windows acrylic behind it. Off, it is solid. Save, then reopen settings to apply.
  - nativeSettingsTitleBar: false
    $name: Native Windows title bar
    $description: Use the Windows title bar and window buttons for this settings window. Save, then reopen settings to apply.
  $name: Settings window
*/
// ==/WindhawkModSettings==

