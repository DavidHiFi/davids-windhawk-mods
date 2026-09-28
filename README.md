# David's Windhawk mods

Local [Windhawk](https://windhawk.net) mods I use on my machine. They are forks
of published mods, changed to fit how I work. MIT licensed.

## Mods

### alt-snap-drag

Window dragging in the style of [AltDrag](https://windhawk.net/mods/alt-drag),
plus the [AltSnap](https://github.com/RamonUnch/AltSnap) shortcuts I use. Hold
Alt and:

| Gesture | Action |
| --- | --- |
| left drag | move the window |
| right drag | resize from the edge or corner nearest where the drag starts |
| F | toggle maximize |
| M | minimize |
| Shift+Q | close |
| middle click | window menu |
| right click while moving | toggle the maximized state, which stays toggled |

The drag itself comes from [m417z's
AltDrag](https://github.com/m417z/my-windhawk-mods). AltSnap is by
[RamonUnch](https://github.com/RamonUnch/AltSnap); the original AltDrag is by
Stefan Sundin.

### taskbar-ai-quota-opencode

Taskbar bars for AI subscription quotas, with an OpenCode Go provider added on
top of [Cleroth's taskbar-ai-quota](https://github.com/Cleroth).

## Building

A Windhawk mod is one C++ file. Either drop the `.wh.cpp` into
`C:\ProgramData\Windhawk\ModsSource\` and compile it in the Windhawk editor, or
build it with the compiler Windhawk ships:

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

Three things that will bite you:

- `WH_MOD` only. `-DWH_EDITING` is the editor's syntax mode: every `Wh_*` call
  becomes a no-op, the DLL imports nothing from `windhawk.dll`, and the mod
  silently does nothing.
- The mod id is normally passed as `-DWH_MOD_ID=L"..."`, and Windows PowerShell
  5.1 mangles the quotes. `alt-snap-drag` defines it in the force-included
  `altsnap-modid.h` instead.
- Install as a local mod by copying the DLL into
  `C:\ProgramData\Windhawk\Engine\Mods\{64,32}` and pointing `LibraryFileName`
  under `HKLM\SOFTWARE\Windhawk\Engine\Mods\<id>` at it. Give each build a new
  file name: the engine keeps the previous DLL mapped, so overwriting the same
  name fails.

## License

MIT, see [LICENSE](LICENSE). Each mod carries its own license header, and the
forks keep the license of what they came from.
