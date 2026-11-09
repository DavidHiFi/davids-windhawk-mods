# Mods

- `local/` holds my mods. Each folder has the source, a readme and install
  steps.
- `catalog/` holds copies of the catalog mods in this setup, one `.wh.cpp` per
  mod, as installed. [catalog/README.md](catalog/README.md) lists authors,
  versions and licenses.

## Local mods

| Mod | What it does | Version | License |
| --- | --- | --- | --- |
| [Pointer Afterimage Plus](local/pointer-afterimage-plus) | A real motion blur for the mouse pointer, drawn on the GPU. | 1.2.1 | Unlicense |
| [File Operation Styler Plus](local/file-operation-styler-plus) | A modern copy, move, delete and recycle window for Explorer, drawn on the GPU. | 1.5.0 | GPL-3.0 |
| [WinTips OSD Plus](local/wintips-osd-plus) | Pop-up cards for Caps, Num and Scroll Lock, Insert, copy, paste and cut, drawn on the GPU. | 1.4.0 | MIT |
| [Windhawk Enhanced Styler](local/windhawk-enhanced-styler) | Colors, gradients, fonts, frosted dialogs and a matching title bar for Windhawk 2.0. | 2.1.0 | MIT |
| [Seamless Dictate](local/seamless-dictate) | Hold Ctrl+Win and speak to type in any app, with AI cleanup and mic privacy. | 1.0.4 | MIT |
| [Ditto Styler](local/ditto-styler) | Rounded dark glass, glass tooltips and a bottom dock for the Ditto clipboard manager. | 1.1.11 | MIT |
| [Seamless Autoscroll](local/seamless-autoscroll) | Hold the middle mouse button and move to scroll, with a frosted glass indicator. | 1.0.0 |  |
| [Window Borders](local/window-borders) | Smooth, rounded borders on every window, with an accent-to-mauve gradient on the active one. | 1.0.0 | GPL-3.0 |
| [Window Manager Plus](local/window-manager) | Move, resize, snap and send windows to other monitors with Alt+drag and keyboard shortcuts. | 1.3.1 | GPL-3.0 |
| [AltSnap](local/alt-snap-drag) | Alt+drag to move and resize any window, plus AltSnap's window shortcuts. | 1.2.2 | GPL-3.0 |
| [Seamless Media Player](local/seamless-media-player) | A taskbar media player with live spectrum bars beside or behind it. | 1.9.6 | MIT |
| [Taskbar Audio Visualizer](local/taskbar-audio-visualizer) | A live audio spectrum with media controls on the taskbar. | 1.3.0 | MIT |
| [Taskbar Weather](local/taskbar-weather) | Current weather on the taskbar with a details card on hover. | 1.4.0 | MIT |
| [Taskbar Elastic WinUI Pill Plus](local/taskbar-elastic-pill-plus) | An animated pill that slides under the app you use, with an option to mark open apps. | 2.1.0 | MIT |
| [Taskbar Collapse to Running Plus](local/taskbar-collapse-to-running-plus) | Hide idle pinned apps and reveal them with a smooth hover transition. | 1.1.5 | MIT |
| [Taskbar System Info Plus](local/taskbar-system-info-weather) | CPU, GPU, RAM, VRAM, temperatures and network speed on the taskbar. | 1.4.18 | GPL-3.0 |
| [Taskbar AI Quota Bars Plus](local/taskbar-ai-quota-opencode) | Claude, Codex, Antigravity and OpenCode Go usage limits on the taskbar. | 1.6.5.1 | MIT |
| [Seamless Volume Mixer](local/better-volume-mixer-plus) | Tray volume mixer with per-app volume up to 1000%, a per-app compressor, and per-app devices. | 1.4.1 | MIT |
| [Translucent Flyouts](local/translucent-flyouts) | Acrylic, Mica and blur menus, dropdowns and tooltips in every app. | 0.6.6 | LGPL-3.0 |
| [Shell Font Changer Plus](local/shell-font-changer-plus) | Any installed font in Explorer, Start, Search and Settings, with icons and emoji left intact. | 1.3.3 | MIT |
| [Everything & Power Tools in the Start Menu Plus](local/start-everything-plus) | Compact Start menu search with Everything, preview, apps, settings, power tools. | 1.1.0 | GPL-3.0 |
| [Explorer TreeItem Tweaker Plus](local/explorer-treeitem-tweaker-plus) | Rounded, colored highlights for folders in Explorer's left pane, no restart popup. | 1.1.5 | MIT |
| [GPU Accelerated Explorer View Plus](local/gpu-accelerated-explorer-view-plus) | GPU-rendered file lists and icon grids, with right-click submenus that open fully populated. | 1.0.0 | GPL-2.0 |
| [File Explorer Styler Plus](local/windows-11-file-explorer-styler-plus) | Themes for File Explorer, plus a rounded status bar dock with Mocha view buttons. | 1.9.2 | GPL-3.0 |
| [Fullscreen Start Plus](local/fullscreen-start-plus) | A fullscreen grid of all your apps in place of Start, with instant search and blur. | 1.6.3 | MIT |
| [Settings Styler Plus](local/settings-styler-plus) | Themes for the Settings app, with the normal title bar and a blur that stays when unfocused. | 1.2.0 | GPL-3.0 |
| [Notepad++ Dark Dialog Fix](local/npp-taskdlg-textcolor) | Readable text in Notepad++ dark-mode dialogs. | 1.0.1 | MIT |
| [Seamless Flyouts](local/seamless-flyouts) | Blurred, rounded Catppuccin menus and flyouts that match the taskbar, in every app. | 2.0.0 |  |
| [Recycle Bin Tray Plus](local/recycle-bin-tray-plus) | A Recycle Bin icon in the tray, with a menu that matches Seamless Flyouts. | 1.0.1 | GPL-3.0 |
| [Magic Pointer Plus](local/magic-pointer-plus) | Shake the pointer, then point at anything and ask an AI about it, with matching menus. | 1.0.5 |  |

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
  Windows PowerShell 5.1 mangles the quotes. `alt-snap-drag` defines it in the
  force-included `altsnap-modid.h` instead.
- Install a local mod by copying the DLL into
  `C:\ProgramData\Windhawk\Engine\Mods\{64,32}` and pointing `LibraryFileName`
  under `HKLM\SOFTWARE\Windhawk\Engine\Mods\<id>` at it. Give each build a new
  file name: the engine keeps the previous DLL mapped, so overwriting the same
  name fails.
