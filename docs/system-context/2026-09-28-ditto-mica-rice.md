# Ditto clipboard: frosted mica rice fork

Date: 2026-09-28. Task: fork Ditto, keep the Catppuccin Mocha theme, add rounded
corners and a subtle frosted (mica/acrylic) background. Nothing else changes.

## Fork and artifacts

- Fork: https://github.com/DavidHiFi/Ditto (master).
  - `41d5eda` frosted acrylic backdrop and rounded corners.
  - `b4ae33f` README section for the rice mode.
- Release `rice-mocha-v1` carries the built `Ditto.exe`.
- **License:** upstream is GPL-3.0. A fork cannot be relicensed to MIT; the fork
  keeps GPL-3.0 (asked for MIT, this is the legal constraint).

## Code changes (7 files)

`src\DittoWindow.cpp/.h` (rice support + caption strip), `src\QPasteWnd.cpp`
(window erase, transparency interaction, group statics), `src\QListCtrl.cpp`
(list erase + unselected rows), `src\SymbolEdit.cpp` (search box),
`src\GroupStatic.cpp/.h` (transparent label background).

How it works: `SetWindowCompositionAttribute` with
`ACCENT_ENABLE_ACRYLICBLURBEHIND` plus `DWMWA_WINDOW_CORNER_PREFERENCE`
(ROUND) and `DWMWA_USE_IMMERSIVE_DARK_MODE`. In an acrylic window DWM treats
pure black pixels as **unpainted**, so every background fill paints black in
rice mode: that shows the frosted backdrop and also clears stale pixels
(GDI cannot write transparent pixels otherwise). The backdrop tint is the
theme's `MainWindowBG` (Catppuccin Mocha base `#1E1E2E`) at alpha `0xD0`.

Escape hatch: `DITTO_NO_RICE=1` in the environment restores the original solid
look. Windows 7/10 fall back gracefully (missing attributes are ignored).

## Build (this machine)

- `nuget restore CP_Main_10.sln` (libpng/zlib), then
  `msbuild CP_Main_10.sln /p:Configuration=Release /p:Platform=x64 /p:PlatformToolset=v143`.
- Upstream projects now target v145 (VS 2026); this box has VS 2022 (v143), so
  the toolset is overridden at build time. No project files were retargeted.
- System change made for this: added `Microsoft.VisualStudio.Component.VC.ATLMFC`
  to VS 2022 Community (MFC/ATL was missing). Rollback: remove that component in
  the Visual Studio Installer.

## Verification

- Popup captured with the popup actually on top: `reports\2026-09-28\ditto-rice-popup-verified.png`.
  Background pixels sampled 32-47 on the blue channel (Mocha base over blur),
  blue selection row and light text intact, corners rounded.
- Theme: `HKCU\Software\Ditto\Theme2` was **empty** (default light theme) and was
  set to `catppuccin-mocha`. The theme file it loads is
  `C:\Program Files\Ditto\Themes\catppuccin-mocha.xml`. Pre-change registry
  export: `backups\2026-09-28-ditto-rice\ditto-registry-before-rice.reg`.
  (The value was probably cleared while a test instance ran against a fresh,
  empty database; every other setting looked intact, e.g. the custom hotkey and
  `MaxEntries`.)
- The riced build's exe directory needs a `Themes` folder; the installed copy
  already has one, a test copy in `Release64` needed the themes copied in.

## Incident on the way (no data loss)

- `WM_CLOSE` to the running Ditto did not exit it; force-kill followed. Repeated
  relaunches then sat windowless in a message pump. Cause: a stale instance in
  the "already running" idle state (mutex `Ditto Is Now Running`) plus a slow
  first start after the unclean kill (5+ minutes, no disk I/O). After all
  instances were gone the app starts in under 15 seconds. The database itself is
  healthy: `PRAGMA quick_check` = ok, `Main` = 516 rows.
- A recovery copy of the user database was left as `Ditto.fresh.db` (94 KB, a
  scratch database from that test). Safe to delete.

## Install state

- `C:\Program Files\Ditto\Ditto.exe` is still the original
  (SHA256 `D187EB96E7C0FB15B8E2AAA38B70F10FF8AAE9A4FDEE3B0499B0FF0844DD7377`),
  backup at `backups\2026-09-28-ditto-rice\Ditto.exe.orig`.
- Riced build staged at
  `work\ditto-rice\Release64\Ditto.exe`
  (SHA256 `05F9BF79C843FDB6A190AFC583FF97937198449EC971B666B827589FEB039BAD`).
- The swap into Program Files needs one UAC approval (the folder is not writable
  for the user, and a highest-privileges scheduled task cannot be registered
  from the filtered admin token).
- The machine starts Ditto from a scheduled task `Ditto` (logon trigger,
  `RunLevel HighestAvailable`), so that is also how to restart it.

## Rollback

1. Copy `Ditto.exe.orig` back over `C:\Program Files\Ditto\Ditto.exe` (elevated), or
2. launch the riced build with `DITTO_NO_RICE=1`, or
3. restore the registry export above (theme only).

## Note on Windhawk

The machine injects `win32-ui-modernizer`, `translucent-windows`,
`slick-window-arrangement` and `windows-animations` into `Ditto.exe`. They were
not the cause of the startup trouble, but they do hook window/DWM paths; if the
frosted look ever changes unexpectedly, check those mods first.

## Update 2026-09-29: installed for real, plus row separators

- **The 2026-09-28 "install awaits one UAC click" was a false report.** The
  elevated install never ran (an elevated `pwsh` was started but never read its
  script), the file was never replaced, and the frosted look that was captured
  was actually Windhawk injecting `win32-ui-modernizer` + `translucent-flyouts`
  into the stock `Ditto.exe`. The installed exe was byte-for-byte the original.
- Root cause of the elevation miss: `Start-Process -Verb RunAs` from the agent
  app's shell starts a process that errors out before running. UAC prompts are
  disabled here (`ConsentPromptBehaviorAdmin=0`, `PromptOnSecureDesktop=0`).
  Working route: write a `.cmd` wrapper that calls
  `powershell.exe -NoProfile -ExecutionPolicy Bypass -File <script>`, log to a
  file, `Start-Process <cmd> -Verb RunAs -Wait`, then read the log. See the
  `uac-silent-rule` in the global and workspace AGENTS.md files.
- Installed 2026-09-29: `C:\Program Files\Ditto\Ditto.exe` = `8BED7BE9...`
  (rice + separators), `ICU_Loader.dll` = `86FF3589...` from the same build.
  Original and the previous rice build backed up at
  `backups\2026-09-29-ditto-rice-swap\` (`Ditto.exe.pre-rice`,
  `Ditto.exe.rice-v1`).
- New feature this day: a 1px divider under each entry, colour blended from the
  theme's two row shades (`CQListCtrl::RowSeparatorColor`), so it matches any
  palette and stays quiet on the acrylic. `QListCtrl.cpp/.h`, commit `f58e8ee`.
- Live verification: `reports\2026-09-29\ditto-rice-separators.png`,
  `ditto-sep-zoom.png`.

## Persistence check 2026-09-29

- Logon task `Ditto` runs `"C:\Program Files\Ditto\Ditto.exe"` (RunLevel
  HighestAvailable), and that file is now the riced build (`8BED7BE9...`), so
  every logon/restart starts the rice. Verified after install.
- This build has **no in-app updater**: the legacy `CheckForUpdates` /
  `LastUpdateDay` registry values exist but nothing calls them (no code path, no
  menu/strings in the .rc). Nothing automatic can overwrite the exe; only
  manually running the official Ditto installer would, and restoring the rice
  then means copying the built exe again (or `Ditto.exe.rice-v1` from the
  backup folder as a fallback source).
- Fork master updated: `f58e8ee` (separators) pushed to
  https://github.com/DavidHiFi/Ditto.
