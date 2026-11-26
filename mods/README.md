# Mods

- `local/` holds my current mods. Each folder has the source and any helper files it
  needs.
- `catalog/` holds copies of the catalog mods in this setup, one `.wh.cpp` per
  mod, as installed. [catalog/README.md](catalog/README.md) lists authors,
  versions and licenses.

The tables below mirror [manifest.json](../manifest.json), grouped the same way as
[categories.json](categories.json). `retired/` keeps the last source of mods that
now live inside another mod; [retired/README.md](retired/README.md) says where.

## Local mods

### Taskbar

| Mod | What it does | Version | License |
| --- | --- | --- | --- |
| [Seamless Taskbar](local/seamless-taskbar) | The whole riced taskbar in one mod: system info, media, apps dock, clock, tray, AI usage and right-click tools, each with its own switch | 0.4.28 | GPL-3.0 |
| [Seamless Taskbar Badge Counter](local/seamless-taskbar-badge-counter) | See how many windows each taskbar app has open, on a Catppuccin Mocha badge with a gradient edge | 1.0.3 | GPL-3.0 |
| [Recycle Bin Tray Plus](local/recycle-bin-tray-plus) | Adds an interactive Recycle Bin icon to the Windows 11 system tray with live state updates, drag-and-drop support, theme-aware rendering, multiple icon styles, and configurable mouse actions. | 1.0.8 | GPL-3.0 |
| [Better Volume Mixer Plus](local/better-volume-mixer-plus) | A compact tray volume mixer with per-app volume up to 1000%, a per-app compressor, and per-app output and input devices | 1.4.33 | MIT |
| [Power Options Button Plus](local/power-options-button-plus) | Tray icon to switch between Windows power plans with the mouse wheel. The icon is the house tray badge with a glyph for each plan. | 1.1.0 | MIT |
| [Network Speed Test Plus](local/network-speedtest-plus) | Tray speed test button next to the network icon, plus the Windows 11 network menu speed test as a native flyout: ping, jitter, download and upload measured against Cloudflare, live gauge, results chart with copy. Mocha glass, FiraCode, gradient hover. No browser, no separate app. | 2.3.3 |  |

### Explorer

| Mod | What it does | Version | License |
| --- | --- | --- | --- |
| [Windows 11 File Explorer Styler Plus](local/windows-11-file-explorer-styler-plus) | Customize the File Explorer with themes contributed by others or create your own | 1.10.22 |  |
| [Seamless Explorer View](local/seamless-explorer-view) | GPU-accelerated Explorer views with smooth scrolling and right-click submenus that populate fully | 2.0.7 | GPL-2.0 |
| [Seamless Explorer Search](local/seamless-explorer-search) | Start typing in any File Explorer window, or any app's Open or Save window, to search it and every drive with Everything | 2.1.0 | MIT |
| [Explorer Tags Plus](local/explorer-tags-plus) | Colored tags panel in File Explorer's navigation pane, plus a Tags submenu in the right-click menu | 0.8.7 | MIT |
| [File Operation Styler Plus](local/file-operation-styler-plus) | Modern copy, move, delete and recycle progress window for File Explorer | 1.6.6 | GPL-3.0 |
| [Peek](local/peek) | Select a file in File Explorer and press Space to preview it, like PowerToys Peek | 1.5.2 | MIT |
| [Shell Font Changer Plus](local/shell-font-changer-plus) | Any installed font in File Explorer, Start, Search, Settings and the shell, with icons and emoji left intact | 2.0.0 | MIT |

### Windows and menus

| Mod | What it does | Version | License |
| --- | --- | --- | --- |
| [Seamless Title Bars](local/seamless-title-bars) | One title bar look everywhere: colours, caption buttons, a glass title dock and native frames in every kind of app | 1.3.11 | MIT |
| [Seamless Borders](local/seamless-borders) | Colored borders around windows, menus and notification banners | 1.0.5 | GPL-3.0 |
| [Seamless Flyouts](local/seamless-flyouts) | Blurred, rounded Catppuccin menus and flyouts that match the taskbar, plus acrylic and Mica for Windows 11 apps | 2.0.18 |  |
| [Seamless Window Manager](local/seamless-window-manager) | Move, resize, snap and focus windows with the mouse or keyboard, with app rules, gaps and a pause key | 2.6.7 | GPL-3.0 |
| [Seamless Wobbly Windows](local/seamless-wobbly-windows) | Jelly window dragging that keeps Snap, works with Seamless Window Manager's Alt-drag, wobbles the Seamless Borders ring and can add animated color glows behind see-through windows | 1.2.6 | GPL-3.0-or-later |
| [Seamless Compiz Cube](local/seamless-compiz-cube) | Rounded 3D desktop cube with Mocha borders, switching desktops through Seamless Window Manager | 1.0.6 | MIT |
| [Simple Window Switcher Plus](local/simple-window-switcher-plus) | Customizable Alt+Tab with Vista animations, background blur and elevated app support | 1.0.7 | GPL-2.0 |
| [Always On Top Plus](local/always-on-top-plus) | Pin any window above all others with a hotkey, with a highlight border, opacity and sounds | 2.4.1 | MIT |
| [Seamless Launchpad](local/seamless-launchpad) | A fullscreen GPU rendered grid of all your apps in place of Start, with instant search, adjustable blur, wiggle edit mode and power buttons | 2.6.5 | MIT |
| [Halo Launcher](local/halo-launcher) | Press a key, type a few letters, press Enter: apps, files, sums, web searches and every module | 0.6.5 | MIT |
| [Notification Center Styler Plus](local/notification-center-styler-plus) | Customize the Notification Center and Action Center with themes contributed by others or create your own | 1.8.4 |  |
| [Seamless Settings Styler](local/seamless-settings-styler) | Catppuccin Mocha for Windows Settings: glass that matches the title bar, edges on every card, a side menu that folds to icons | 2.0.1 | GPL-3.0 |
| [Seamless Share](local/seamless-share) | Restyles the Windows 11 share window: blurred glass, your font, soft gradient hover edges | 1.0.2 | MIT |
| [Theme Tool Plus](local/theme-tool-plus) | Switch Windows themes from the settings tab. Comes with the Main 01 Catppuccin theme, cursors and sounds | 1.2.0 |  |
| [UWP Assets Redirect Plus](local/uwp-assets-redirect-plus) | Swap the icons of Store and system apps, with a built-in Catppuccin icon theme | 1.2 | GPL-3.0 |
| [Seamless Power Action Countdown](local/seamless-power-action-countdown) | Mocha glass countdown before shutdown, restart, sleep or hibernation. Any key or click cancels | 2.0.3 | MIT |
| [WinTips OSD Plus](local/wintips-osd-plus) | Pop-up cards for Caps, Num and Scroll Lock, Insert, copy, paste and cut, with a Catppuccin Mocha look | 1.4.1 | MIT |
| [Windhawk Enhanced Styler](local/windhawk-enhanced-styler) | Theme Windhawk itself with your own colors, gradients, font, transparency and blur | 2.2.18 | MIT |

### Tools

| Mod | What it does | Version | License |
| --- | --- | --- | --- |
| [Seamless Workshop](local/seamless-workshop) | One window to install, update, turn on and off, and set up DavidHiFi's Windhawk mods | 1.1.1 | MIT |
| [Seamless Clipboard Manager](local/seamless-clipboard-manager) | Keeps everything you copy, text and images, in a searchable list you open with Win+V | 1.4.6 | GPL-3.0 |
| [Seamless Snipper](local/seamless-snipper) | Snip a region, a window or the whole screen: frozen screen, window snapping, a pixel magnifier, straight to the clipboard and your folder. Plus Magic Pointer: shake the mouse, point at anything and ask AI about it | 0.6.7 | GPL-3.0 |
| [Seamless Color Picker](local/seamless-color-picker) | A full color picker on a hotkey, with a screen magnifier, recent colors and one-click copy | 1.1.15 |  |
| [Seamless Dictate](local/seamless-dictate) | Press a shortcut, speak, and your words are typed where the cursor is, in any app: transcribed and cleaned up by AI in your style (natural, professional, prompt) or translated, with a free key (Groq, Gemini, Mistral and more). It also polishes text you typed and reads selected text aloud | 1.3.7 | MIT |
| [ZoomIt](local/zoomit) | Zoom, draw and read text bigger under the mouse with a hotkey, like Sysinternals ZoomIt | 1.2.3 |  |
| [Seamless Crosshair](local/seamless-crosshair) | A crosshair over any game: presets or your own design, any color and size, shortcuts and a tray icon | 1.2.7 | MIT |
| [Seamless AutoClicker](local/seamless-autoclicker) | Hold a side mouse button and left click keeps clicking, with a lock, a tray switch and its own settings window | 1.6.11 | GPL-3.0 |
| [Seamless Autoscroll](local/seamless-autoscroll) | Hold the middle mouse button and move to scroll, like in a browser, with a frosted glass indicator, in every app | 2.0.0 |  |
| [Seamless Key Click](local/seamless-key-click) | Mechanical keyboard and mouse sounds as you type and click, with every Keyboard Sounds pack, shortcuts and a tray icon | 1.1.5 | GPL-3.0 |
| [Pointer Afterimage Plus](local/pointer-afterimage-plus) | A real motion blur for the mouse pointer, made of fading afterimages of your own cursor, with an optional particle trail and click ripples | 1.3.3 | Unlicense |
| [Keyboard Shortcut Actions Plus](local/keyboard-shortcut-actions-plus) | Global shortcuts for apps and Windows actions that work on any PC and offer a download when an app is missing | 1.1.2 |  |
| [Seamless Sound Manager](local/seamless-sound-manager) | Change every Windows sound with a scheme: 161 presets, startup and logon sounds. A port of Sound Manager | 1.0.7 | CDDL-1.0 |
| [Startup Control](local/startup-control) | Manage startup apps, scheduled tasks and Windows startup locations. | 0.1.7 |  |
| [Seamless Crash Watch](local/seamless-crash-watch) | A notice when a program crashes. Click it and an AI agent in a terminal finds out why, like Omarchy | 1.2.9 | MIT |

### Fixes

| Mod | What it does | Version | License |
| --- | --- | --- | --- |
| [Explorer Tree Guard](local/explorer-tree-guard) | Stops File Explorer windows crashing when the folder tree gets a request from a thread that already gave up | 1.0.0 |  |
| [Helium Acrylic](local/helium-acrylic) | Keeps Helium's acrylic surface, Catppuccin colors and system-drawn frame working after browser updates | 3.8.0 |  |
| [Ableton Glass Fill](local/ableton-glass-fill) | Matches Ableton's menu bar and Settings window to its title bar glass, and keeps the glass tint Mocha | 1.5.1 |  |

## Installing a mod

Open Windhawk, click "Create new mod", paste the source, and hit Compile. You
can also copy a `.wh.cpp` to `C:\ProgramData\Windhawk\ModsSource\` and open it
from the mod editor.

## Building with Windhawk's compiler

A Windhawk mod is one C++ file built against the engine's `windhawk.lib`.
Windhawk ships a matching clang:

```powershell
& 'C:\Program Files\Windhawk\Compiler\bin\clang++.exe' `
  -std=c++23 -O2 -shared -target x86_64-w64-mingw32 -DUNICODE -D_UNICODE `
  -DWINVER=0x0A00 -D_WIN32_WINNT=0x0A00 -D_WIN32_IE=0x0A00 `
  -DNTDDI_VERSION=0x0A000008 -D__USE_MINGW_ANSI_STDIO=0 -DWH_MOD `
  -include windhawk_api.h `
  -I 'C:\Program Files\Windhawk\Compiler\include' `
  -Wno-pragma-pack -Wno-pragma-system-header-outside-header `
  -Wl,--export-all-symbols mod.wh.cpp `
  'C:\Program Files\Windhawk\Engine\<engine-version>\64\windhawk.lib' `
  -lcomctl32 -o mod.dll
```

Replace `<engine-version>` with the folder under `C:\Program Files\Windhawk\Engine`.

Three things that will bite you:

- `WH_MOD` only. `-DWH_EDITING` is the editor's syntax mode: every `Wh_*` call
  becomes a no-op, the DLL imports nothing from `windhawk.dll`, and the mod
  silently does nothing.
- The mod id normally goes on the command line as `-DWH_MOD_ID=L"..."`, and
  Windows PowerShell 5.1 mangles the quotes. Mods that need it, like `peek`,
  define it in a force-included `*-modid.h` header instead.
- Install a local mod by copying the DLL into
  `C:\ProgramData\Windhawk\Engine\Mods\{64,32}` and pointing `LibraryFileName`
  under `HKLM\SOFTWARE\Windhawk\Engine\Mods\<id>` at it. Give each build a new
  file name: the engine keeps the previous DLL mapped, so overwriting the same
  name fails.
