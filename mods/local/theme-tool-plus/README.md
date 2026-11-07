# Theme Tool Plus

[☕ Support on Ko-fi](https://ko-fi.com/DavidHiFi)

Switch Windows themes from the mod's settings tab. It comes with Main 01
(Catppuccin Mocha Night with matching cursors, sounds and wallpaper) and the
six Catppuccin themes. Custom themes that aren't signed by Microsoft work
without patching system files or running a separate theme tool.

![Theme Tool Plus preview](https://raw.githubusercontent.com/DavidHiFi/davids-windhawk-mods/main/media/previews/theme-tool-plus.png)

## Features
- **Comes with themes.** The first time the mod runs, it downloads Main 01
  and the Catppuccin themes, with their cursors, sounds and wallpaper. They
  show up in the theme list next to your own themes. Your current theme
  doesn't change until you pick one.
- **Switch from the settings tab.** Pick a theme from a list and save.
- **Custom themes just work.** Themes that aren't signed by Microsoft load as
  they are. No system file is changed, and Secure Boot isn't affected.
- **Keep what you like.** Switch themes but keep your own wallpaper, cursor,
  desktop icons, colors, sounds or screensaver.
- **Stays after a restart.** The sign-in and lock screens get the same
  colors, so the theme is still there after a reboot.
- **No extra app.** Everything runs inside the mod. You can uninstall
  ThemeToolSharp.
- **No Settings pop-up.** Can stop the Settings app from opening after each
  theme switch.

## How to use

Open the mod's settings tab.

1. Under **Theme**, pick the theme you want. Pick **Main 01** for the full
   look: window style, wallpaper, cursor and sounds.
2. Turn on **Switch theme when I save**.
3. Click **Save settings**. The theme switches right away.

To use a theme you added yourself, pick **A theme not in this list** and type
its name in the box below it. To see every installed theme in a small window,
set **Also do this when I save** to **Open the theme picker window** and save.

## Notes
- The included themes go into `C:\Windows\Resources\Themes\Theme Tool Plus`,
  because Windows only loads a theme's window style from that folder. The
  download is checked before it is unpacked. A theme you already have with
  the same file name is never replaced. Turn off **Download the themes that
  come with this mod** to skip the download.
- The theme Windows calls **Unsaved Theme** (your current mix of changes)
  can't be picked. Switching to it would overwrite your saved changes, so the
  mod skips it.
- Use themes made for your version of Windows. Put your own themes in
  `C:\Windows\Resources\Themes` so they show up in the list.
- Before you remove the mod, switch to a built-in Windows theme. Otherwise a
  custom theme may not load the next time you sign in.
- Doesn't work on ARM PCs.

## Credits
Catppuccin window styles and cursors from [niivu](https://www.deviantart.com/niivu) and
the [Catppuccin](https://github.com/catppuccin) palette.
Based on [UXTheme hook](https://windhawk.net/mods/uxtheme-hook) by rounk-ctrl.
Theme engine research from [SecureUxTheme](https://github.com/namazso/SecureUxTheme)
and [ThemeToolSharp](https://github.com/namazso/ThemeToolSharp) by namazso,
LGPL-2.1.
