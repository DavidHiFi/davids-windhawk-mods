# Mods

- `local/` holds my mods. Each folder has the source, a readme and install
  steps.
- `catalog/` holds copies of the catalog mods in this setup, one `.wh.cpp` per
  mod, as installed. [catalog/README.md](catalog/README.md) lists authors,
  versions and licenses.

## Local mods

| Mod | What it does | Version | License |
| --- | --- | --- | --- |
| [Window Manager](local/window-manager) | Move, resize, snap and send windows to other monitors with Alt+drag and keyboard shortcuts. | 1.1.0 | GPL-3.0 |
| [AltSnap](local/alt-snap-drag) | Alt+drag to move and resize any window, plus AltSnap's window shortcuts. | 1.2.2 | GPL-3.0 |
| [Taskbar Audio Visualizer](local/taskbar-audio-visualizer) | A live audio spectrum with media controls on the taskbar. | 1.2.0 | MIT |
| [Taskbar Weather](local/taskbar-weather) | Current weather on the taskbar with a details card on hover. | 1.4.0 | MIT |
| [Taskbar System Info Plus](local/taskbar-system-info-weather) | CPU, GPU, RAM, VRAM, temperatures and network speed on the taskbar. | 1.2.3 | GPL-3.0 |
| [Taskbar AI Quota Bars Plus](local/taskbar-ai-quota-opencode) | Claude, Codex, Antigravity and OpenCode Go usage limits on the taskbar. | 1.6.5.1 | MIT |
| [Better Volume Mixer Plus](local/better-volume-mixer-plus) | Tray volume mixer with per-app output and input devices. | 1.0.0 | MIT |
| [Translucent Flyouts](local/translucent-flyouts) | Acrylic, Mica and blur menus, dropdowns and tooltips in every app. | 0.6.6 | LGPL-3.0 |
| [Shell Font Changer](local/shell-font-changer) | Any font in Explorer, Start, Search and Settings, with icons intact. | 1.1.0 | MIT |
| [Notepad++ Dark Dialog Fix](local/npp-taskdlg-textcolor) | Readable text in Notepad++ dark-mode dialogs. | 1.0.1 | MIT |
| [Center Titlebar Fork](local/center-titlebar-fork) | Unfinished prototype of a Windows 11 title-centering fix. Not installed. | 3.4 | MIT |

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
