# 2026-10-26: Flow Launcher added to translucent-windows

Owner asked for Flow Launcher to get the blur look. Flow.Launcher.exe was not in the
blur mod's custom app list, so its own half-done backdrop showed as a two-tone bar.

## Change (8:19 PM)

`scripts\2026-10-26-flow-launcher-blur.ps1`, elevated, under the windhawk-engine lock:
- translucent-windows: `Flow.Launcher.exe` added to IncludeCustom and as RuledPrograms[31]
  (acrylicblur, tint AA1E1E2E, ThemeBackground 0, AccentColorControls 0, like Terminal).
- local@window-borders: Flow.Launcher.exe added to Exclude (freeze rule: one window-look mod per app).
- Flow Launcher restarted.

## Evidence (measured)

- Readback: IncludeCustom and window-borders Exclude both contain Flow.Launcher.exe; rule at index 31.
- Modules in the new Flow process: translucent-windows_1.8.2 loaded, window-borders gone.
- Screenshot `reports\2026-10-26-flow-launcher-blur\after-full.png`: bar is one even tone,
  RGB 28-31 / 29-31 / 43-45, close to the other blur apps (Discord 26-42 in tw-full-look).

## Rollback

Elevated: `scripts\2026-10-26-flow-launcher-blur.ps1 -Action Rollback`, then restart Flow Launcher.
