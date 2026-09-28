# Mods

- `local/` is my work: alt-snap-drag, taskbar-ai-quota-opencode,
  npp-taskdlg-textcolor and translucent-flyouts. Each folder holds the source
  it was built from.
- `catalog/` holds copies of the catalog mods in this setup, one flat `.wh.cpp`
  per mod, exactly as they are on my machine. The table in
  [catalog/README.md](catalog/README.md) lists authors, versions and licenses.

## Local mods

| Mod | What it does | Version | License |
| --- | --- | --- | --- |
| [alt-snap-drag](local/alt-snap-drag) | Alt-drag and resize with AltSnap shortcuts; replaces the stock AltDrag mod and the AltSnap app. | 1.2.2 | GPL-3.0 |
| [taskbar-ai-quota-opencode](local/taskbar-ai-quota-opencode) | Taskbar AI quota bars with an OpenCode Go provider. | 1.6.5.1 | MIT |
| [npp-taskdlg-textcolor](local/npp-taskdlg-textcolor) | Readable text in Notepad++ dark-mode Save and confirm dialogs. | 1.0.1 | MIT |
| [translucent-flyouts](local/translucent-flyouts) | The archived TranslucentFlyouts engine reimplemented as one self-contained mod: acrylic/blur/transparent menus, tooltips and dropdown lists, no helper app. | 0.6.1 | LGPL-3.0 |

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
