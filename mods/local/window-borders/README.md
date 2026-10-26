# Window Borders

[☕ Support on Ko-fi](https://ko-fi.com/DavidHiFi)

Replaces the thin Windows 11 window border with a smooth, rounded one. By
default the window you're using gets a 2 px ring that fades from your accent
color to Catppuccin Mocha mauve at an angle, and background windows get none.
It works like tacky-borders, but runs inside Windhawk, so there's no separate
app to keep open.

![Window Borders preview](https://raw.githubusercontent.com/DavidHiFi/davids-windhawk-mods/main/media/previews/window-borders.png)

## Features
- **Two styles.** **Overlay** (the default) draws its own border with any
  width, corner radius and gap, a solid color or a gradient, and a fade when
  focus moves. **Thin** only recolors the 1 px line Windows already draws.
- **Follows your accent.** The active border uses your Windows accent color and
  updates when you change it. Any hex color like #89b4fa works too.
- **Hides when it should.** No border on maximized, minimized or fullscreen
  windows, or on windows on another virtual desktop.
- **Never in the way.** Clicks pass through the border and it never takes
  focus.
- **Clean off switch.** Turning the mod off removes every border and brings
  back the Windows default line.

## How to install
1. In Windhawk, click **Create a new mod**.
2. Replace the code with [window-borders.wh.cpp](window-borders.wh.cpp).
3. Click **Compile Mod**, then **Exit Editing Mode**.
4. If another mod already colors the window border in some app (a blur or
   title bar mod, for example), add that app to this mod's exclusion list in
   Windhawk so the two don't fight.

Needs Windows 11 22H2 or newer.

## Credits
Based on [Windows 11 Accent Window Border](https://windhawk.net/mods/win11-accent-border)
by [Guerra24](https://github.com/Guerra24), the border re-apply approach from
[GlazeWM](https://github.com/glzr-io/glazewm), and the overlay design of
[tacky-borders](https://github.com/luke-you/tacky-borders) by luke-you and
[cute-borders](https://github.com/keifufu/cute-borders) by keifufu (both MIT).
Plus changes by DavidHiFi. GPL-3.0 license.
