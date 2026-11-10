# Seamless Color Picker (local@seamless-color-picker) 1.0.0

Date: 2026-11-10 to 2026-11-11. Thread 73aed2d6.

## What it is

A Windhawk tool mod (runs in its own windhawk-mod.exe) that ports ShareX's Color picker
(ColorPickerForm) in full: colour box and hue slider, New/Old swatches, HSB, RGB, CMYK, Hex,
Decimal and screen position fields, recent colours, a Mocha palette row, pick from screen with a
magnifier, from clipboard, copy in many formats (custom format tokens too), and a toast on copy.
Look: Catppuccin Mocha, blue accent, blue to mauve gradients, optional glass. Settings window is
the universal Launchpad settings GUI (gear in the picker), plus every option in Windhawk settings.

Hotkey: Alt+Win+C opens the picker (customizable). A second, optional hotkey goes straight to the
screen magnifier (empty by default).

## Source and build

- Work folder: `work\2026-11-10-color-picker\` (src, gen.py, assemble.py, check.py, harness).
- Build file: `work\2026-11-10-color-picker\build\seamless-color-picker.wh.cpp`.
- Offline compile clean; the harness rendered every view to `harness\shots\`.
- Trap hit: Windhawk's settings YAML parser rejects unquoted values with ": " or "#"
  ("(Suggested: 16)" failed install). Check with yaml.safe_load before installing.

## ShareX

ShareX's own hotkey config has no Color picker entry and ShareX registers only its 5 other
hotkeys, so Alt+Win+C was free. No ShareX file was changed. Before install the key could be
registered; after install it is held by the mod.

## Install and rollback

- Install: `scripts\2026-11-10-seamless-color-picker.ps1 -Install` (elevated).
  Engine key: version 1.0.0, enabled. Host windhawk-mod.exe started 6:43 am 2026-11-11.
  Explorer unaffected.
- Rollback: same script with `-Rollback` (disables, then uninstalls). Nothing else to restore.
- Logs: `reports\2026-11-11-seamless-color-picker-*.log`.

## Live check

Opened through the mod's own hotkey message (no typing, no cursor movement), captured and
recorded the window, closed it. Proof in `work\2026-11-10-color-picker\live\`.
