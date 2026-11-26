# Windows' own app icons: Catppuccin everywhere (2026-11-26)

Owner: "fix the terminal icon ... it needs to be riced Catppuccin Mocha just like everything
else, and extensively audit all other similar native Windows app icons."

## Why Terminal looked stock

UWP Assets Redirect Plus swaps a packaged app's icon by catching file reads in the shell
processes only (Explorer, Start, search). Our tool mods run in `windhawk-mod.exe`, and
Alt-Tab runs its own lookup, so any of them that pull the icon out of the app's exe got
the stock one. Widening the redirect to `windhawk-mod.exe` was rejected: about 40
processes would each hook every file open.

Fix, per mod: read the redirect's own theme file (`icon-themes\<theme>\theme.ini`, UTF-16,
sections `[windows-apps]` and `[system-apps]`, `Package=.\icons\x.ico`), take the package
name from the exe's `\WindowsApps\<Package>_...` folder, and load that `.ico` first.
Entries with `|` cover one part of a package and are skipped. Nothing happens when the
redirect mod is off or has no theme.

## Audit

| Surface | Before | Fix |
|---|---|---|
| Taskbar, Start, Launchpad, Explorer | themed by the redirect | none needed |
| Seamless Dock: Windhawk and mod windows | stale stock icon | done in 0.3.13 (mod window identity) |
| Seamless Dock | stock Terminal, Notepad, Paint | 0.3.14: theme lookup before the shell icon |
| Alt-Tab (Simple Window Switcher Plus) | stock for packaged desktop apps | 1.0.10: theme lookup after the Explorer one |
| Seamless Volume Mixer | stock for Store app audio (Media Player) | 1.4.37: theme lookup inside ExtractSizedIcon |
| Halo Launcher | stock in results | 0.6.16 by the Halo thread: theme first for WindowsApps and shell:AppsFolder items |
| Seamless Title Bars | Terminal, Notepad, Paint draw their own title bars | not applicable |
| Explorer Search, Peek | file icons, not app icons | not applicable |

## Install state

Filled in below as each install lands.

- 8:20 am: the first three runners all locked as `native-icons` at once (same name, so the
  lock let all three in) and another thread's cleanup stopped two of the installs. Lesson:
  one runner per lock name. Replaced by `run-all.sh`: one install at a time, each restaged
  from the live source after the lock is taken (the stagers bump whatever version is live).
- The mixer moved on to 1.4.37 (crisp icons) and 1.4.38 (menu fix, from the menu batch)
  while waiting; the stager now skips the menu patch when the live source already has it.
- Halo Launcher 0.6.16 went live from the Halo thread (8:40 am, published).
- Finished 10:51 am, all published by the installer: Seamless Dock 0.3.14 (9:21), Alt-Tab
  (simple-window-switcher-plus) 1.0.10 (10:23), Seamless Volume Mixer 1.4.39 (10:51).
  12:07 pm registry check: dock 0.3.15 (later work by another thread on top), Alt-Tab 1.0.10,
  mixer 1.4.39, all switched on. Dock proof for the Terminal tile not captured this turn:
  no Terminal window was open; the dock's lookup itself was proved for Explorer instead
  (notes\2026-11-26-explorer-blue-icon.md).
