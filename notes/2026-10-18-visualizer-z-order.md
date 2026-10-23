# Taskbar audio visualizer: strip sits in the taskbar's z-order (2026-10-18)

Live mod: `taskbar-audio-visualizer`, now running revision `1.3.2_3`
(previous: `1.3.2_1`). Registry key: `HKLM\SOFTWARE\Windhawk\Engine\Mods\local@taskbar-audio-visualizer`.

## What was wrong

- The strip was a topmost popup owned by the taskbar (`WS_EX_TOPMOST`). The taskbar went behind a
  covering window, but the topmost popup stayed in front of it. That is the floating you saw.
- The earlier fix in the previous thread edited `work\davids-audio-publish\...davids-audio-visualizer`,
  which is not the mod Windhawk runs. Its `IsTaskbarHiddenOrOverlapped` function had no caller. Nothing
  from that edit was live. `reports\...` and `work\reports\2026-10-18-audio-viz-taskbar-overlap-fix.md`
  describe that edit and are wrong about what is live.
- The registry `Include` value was `windhawk.exe` when I backed it up at 4:35 PM, before my first install
  (`backups\2026-10-18-visualizer-z-order\mod-key-before.reg`). A mod with `Include=windhawk.exe` does not
  load into Explorer, so no strip was running after that point. I did not find what set it.

## What changed (live source: `C:\ProgramData\Windhawk\ModsSource\local@taskbar-audio-visualizer.wh.cpp`)

- The strip is created as a `WS_CHILD` window of `Shell_TrayWnd`, with no topmost flag, sized to the
  taskbar's client area. Its coordinates are unchanged because the layout is already taskbar-relative.
- Placement uses `HWND_TOP` among siblings, not `HWND_TOPMOST`.
- The one-second watch timer re-raises the strip above other taskbar child windows when needed.
- `UpdateTaskbarFollow` skips its own reveal and slide model when the strip is a child. The shell moves
  the taskbar, and the strip moves with it. This path is untested (see below).
- The header `@include` and the registry `Include` are both `explorer.exe` now.

## Evidence

- Registry after install: `LibraryFileName=local@taskbar-audio-visualizer_1.3.2_3.dll`, `Include=explorer.exe`,
  `Disabled=0`.
- Explorer lists `DesktopAudioVisOverlay_local@taskbar-audio-visualizer` as a child of `Shell_TrayWnd`,
  visible, with no `WS_EX_TOPMOST` (exstyle `0x82800A0`).
- Bars render with audio playing: `reports\2026-10-18-visualizer-z-order\strip-with-audio.png`.
- Covering test: a black topmost window over the screen did not cover the taskbar (the shell keeps the
  taskbar above app windows), so the bars stayed visible: `reports\...\strip-topmost-cover.png`.
  This did not reproduce the game case, where the taskbar itself goes behind the game.

## Not verified

- The Lossless Scaling and borderless game case. Needs one real run: play, watch the strip.
- Auto-hide taskbar. The follow path changed, and I did not test it.
- The media controls strip (`DesktopAudioVisMedia_...`). It is still a topmost popup. Not changed.
- The repo copy `davids-windhawk-mods\mods\local\taskbar-audio-visualizer` is still version 1.3.1
  and does not match the live source. Not synced yet.

## Rollback

    Invoke-Elevated.ps1 -File "H:\Windhawk Configuration\scripts\2026-10-18-visualizer-z-order.ps1" -ArgumentList "-Rollback"

This switches the library back to `1.3.2_1` (the old topmost popup). It does not restore `Include`.
To restore the registry, import `backups\2026-10-18-visualizer-z-order\mod-key-before.reg`, which
includes `Include=windhawk.exe` as it was. Keep `Include=explorer.exe` if you want the strip in Explorer.
The original source is `backups\2026-10-18-visualizer-z-order\local@taskbar-audio-visualizer.wh.cpp`.

## Files

- Work copy with the changes: `work\taskbar-audio-visualizer-z-order\taskbar-audio-visualizer.wh.cpp`
- Build scripts and logs: `backups\2026-10-18-visualizer-z-order\build\`
- Deploy script (Audit, Install, Rollback): `scripts\2026-10-18-visualizer-z-order.ps1`
- Receipt: `backups\2026-10-18-visualizer-z-order\receipt.json`
