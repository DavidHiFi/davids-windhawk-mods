# Seamless Color Picker (local@seamless-color-picker) 1.0.0 → 1.1.0

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
  Engine key: version 1.1.0, enabled. First install 6:43 am 2026-11-11; reinstalled
  4:09 pm with the drift fix (new DLL `..._1.1.0_128149.dll`). Explorer unaffected.
- Rollback: same script with `-Rollback` (disables, then uninstalls). Nothing else to restore.
- Logs: `reports\2026-11-11-seamless-color-picker-*.log`.

## Live check

Opened through the mod's own hotkey message (no typing, no cursor movement), captured and
recorded the window, closed it. Proof in `work\2026-11-10-color-picker\live\`.

## 1.1.0 (2026-11-11): darker background, hover glow, drift fix

- Darker fill: glass tint factor in `DrawPicker` (core.cpp) raised `* 0.62f` → `* 0.92f`,
  tint slider meaning unchanged (60-100, default 85). Page background pixel went
  RGB(50,49,54) → RGB(31,31,39), matching Mocha base #1E1E2E while staying frosted.
  After still: `live\after-1.1.0.png`.
- Hover glow verified live: `live\glow-153656\` (share.mp4, glow.gif, 4x zooms, diff stills).
  Idle button has a plain grey border; hovered shows the blue→mauve gradient ring.
  Sampled saturation: Copy 0.32 → 0.49, Pick 0.32 → 0.51.
- Trap: the mod host runs High integrity, so medium-integrity SendInput was filtered —
  earlier hover tests moved nothing. Also `SendInput` silently fails with a wrong-size
  INPUT struct (48 bytes); 40 bytes works. Working injection: `live\hover.py`.
- Position drift fixed (same release): rememberPos saved GetWindowPlacement's
  rcNormalPosition but the open path restores with SetWindowPos — different coordinate
  spaces, so the window crept up each open/close. SavePickerState now stores the
  GetWindowRect left/top, the same numbers the open path sets. Live proof: three
  open/close cycles reopen at the same top-left (`live\drift.py`, verdict STABLE;
  the parked spot came back exactly twice). Still: `live\after-1.1.0-driftfix.png`,
  background RGB(31,31,39) unchanged.

## 1.1.1 to 1.1.3 (2026-11-12): one dark base, house glass

- Owner: no light band at the top, just the dark Mocha base, real blur like usual.
- 1.1.1: page fill made flat (`DrawPicker`, the crust fade at the top removed). Live check
  showed the band was really the native title bar: raw acrylic RGB(84,84,84) above a page of
  RGB(41,41,54).
- 1.1.2 (settings-GUI thread bd0ca06f, 12:40 am): settings window moved to the standard glass.
- 1.1.3 (1:04 am), built on 1.1.2:
  - Client area now covers the caption (WM_NCCALCSIZE keeps the top, DwmDefWindowProc for
    the caption buttons, HTCAPTION in the strip so drag, right-click and Alt-drag still work).
    The picker paints its own icon and title in the strip; content, mouse, wheel and the edit
    box are offset by the caption height.
  - Picker window uses the same glass as the settings standard: accent acrylic
    {4, 2, 0x012E1E1E, 0}, backdrop none, full blur-behind, flat Mocha base tint on top.
  - Settings window pieces copied from 1.1.2; `scripts\settings-material.py check`: ok.
- Live: every row of the window, title strip included, samples RGB(30,30,47) (Mocha base
  #1E1E2E). Still: `work\2026-11-10-color-picker\live\after-1.1.3-full.png`.
- Install: `scripts\Install-StagedMod.ps1` (hash-guarded), backup in
  `backups\settings-material\local@seamless-color-picker-20261112-0103.wh.cpp`. The host did
  not restart after install; one disable + enable started it (pid 28772).
- Rollback: reinstall that backup with the same script, or `-Rollback` to remove the mod.
- Source backups: `src\core.cpp.bak-20261112-0056`, `src\settings-*.cpp.bak-20261112-*`.
- Public repo: commit e6b482c (source, preview, manifest 1.1.3); raw URL returns 200.
