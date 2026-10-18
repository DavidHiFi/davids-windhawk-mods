# Theme Tool Plus

[? Support on Ko-fi](https://ko-fi.com/DavidHiFi)

Apply and switch custom Windows themes from a hotkey picker. The theme
signature patch from UXTheme hook is built in, so unsigned themes load
without patching system files or running a separate theme tool.

![Theme Tool Plus preview](https://raw.githubusercontent.com/DavidHiFi/davids-windhawk-mods/main/media/previews/theme-tool-plus.png)

## Features

[? Support on Ko-fi](https://ko-fi.com/DavidHiFi)

- **Hotkey picker.** Press Ctrl+Alt+Y for a compact theme list; click or
  press Enter to apply. Works even without Explorer running (the picker lives
  in the Windhawk engine process).
- **Unsigned theme support.** Custom .msstyles load as-is; no system file is
  touched and Secure Boot stays happy.
- **Fine-grained apply options.** Ignore background, cursor, desktop icons,
  colors, sounds or the screensaver when applying.
- **Survives restarts.** Logon and lock screen colors are kept in sync so the
  theme survives a reboot.
- **No extra app.** Everything runs inside the mod; ThemeToolSharp and its
  process inclusion entry can go.
- **Settings blocker.** Optionally stop the Settings app from opening on
  every theme apply.

## How to use

[? Support on Ko-fi](https://ko-fi.com/DavidHiFi)

| Key | Action |
| --- | --- |
| Ctrl+Alt+Y | Open or close the theme picker |
| Click / Enter | Apply the selected theme |
| Esc / click elsewhere | Close the picker |

To drive the mod without the picker, set **Theme to apply** and turn on
**Apply on settings save**; saving the mod's settings applies that theme.
The **Action on settings save** selector can also refresh the theme list or
re-initialize the theme manager.

## Notes

[? Support on Ko-fi](https://ko-fi.com/DavidHiFi)

- The active custom theme, named **Unsaved Theme**, can't be re-applied from the
  picker or from settings. Applying it rewrites your saved `Custom.theme`, so the
  mod skips it and logs the skip.
- Pick themes made for your Windows version. The picker lists the same themes
  Windows shows, from `C:\Windows\Resources\Themes`.
- Before uninstalling the mod, switch to a stock theme; otherwise the next
  logon re-verifies theme signatures and a custom theme may fail to load.
- ARM64 is not supported (Windhawk does not hook ARM64EC).

## Credits

[? Support on Ko-fi](https://ko-fi.com/DavidHiFi)

Based on [UXTheme hook](https://windhawk.net/mods/uxtheme-hook) by rounk-ctrl.
Theme engine research from [SecureUxTheme](https://github.com/namazso/SecureUxTheme)
and [ThemeToolSharp](https://github.com/namazso/ThemeToolSharp) by namazso,
LGPL-2.1.
