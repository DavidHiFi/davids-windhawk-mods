# input-overlay 5.0.6 -> 5.1.0 update (2026-09-25)

Change record for the OBS keyboard-hook log spam fix requested by the owner. Companion to `notes/2026-09-25-obs-replay-buffer-optimization.md` item 7.

## Problem (observed)

input-overlay 5.0.6 spams the OBS log on every keyboard hook event:

- `get_keyboard_layout_file [473]: RegOpenKeyEx failed to open key: "SYSTEM\CurrentControlSet\Control\Keyboard Layouts\0"!`
- `refresh_locale_list [653]: Could not find keyboard map for locale 0000000004090409!` (plus the 0809 and 0C09 layouts)

Measured: ~49,000 of each line per session (3 layouts x ~16,000 key events), 4 log lines per key press, log files up to 20 MB per session. This is upstream issue https://github.com/univrsal/input-overlay/issues/447 ("Log spam: RegOpenKeyEx failed to open key"), fixed in release 5.1.0 (2025-04-06, notes: "Fixed log spam #447").

## What changed

| Item | Before | After |
|---|---|---|
| `C:\Program Files\obs-studio\obs-plugins\64bit\input-overlay.dll` | 5.0.6, 250,880 bytes, SHA256 `3d19d219c6b81deef15f9c08d4fce9fe902f46547fa8b1835ceac9760fc6cd52` | 5.1.0 build (log: `v5.0.6-HEAD (a2d856e) build time 2025.04.06 13:42`), 256,512 bytes, SHA256 `e7dd2395b17387868818980bf157edc0f43d5a58c0a532420c96c3e39ce439c1` (file version property still reads 5.0.6; upstream did not bump it) |
| `obs-plugins\64bit\SDL2.dll` | 2.30.4.0 (from 5.0.6 package) | SDL2 from the 5.1.0 package (runtime still reports 2.30.4) |
| `data\obs-plugins\input-overlay\` | 20 files, 5.0.6 | replaced with 5.1.0 data folder (locale, overlay_render, html) |

Source of files: `input-overlay-5.1.0-windows-x64.zip` from the official GitHub release, SHA256 verified against the published checksum `38b5d7539f863269f317a0afbb10d0fa647f57883367ad7d821a597c8aeea078`.

Timestamp: 2026-09-25 08:59:53 (file swap, elevated script `obs-input-overlay-swap.log`). OBS restarted; the owner's own relaunch at 09:03:03 loaded the new build.

## Test result

- New session log `2026-09-25 09-03-03.txt`: 0 occurrences of `get_keyboard_layout_file` or `refresh_locale_list`, at startup and after a real hotkey press (virtual camera hotkey at 09:03:08). Old build produced 3 such lines at startup alone and 4 lines per key press.
- Plugin loads clean: `Loading v5.0.6-HEAD (a2d856e)`, PS5 controller found, replay buffer and virtual camera started normally.
- Keyboard and DualSense overlay sources loaded and auto-converted their key codes to the 5.1.0 format. One element did not convert: `Failed to convert keycode 0x0029 for element '~'` in `qwerty_arrow_keys.json`, so the tilde key will not highlight on the on-screen keyboard until that preset is updated. Everything else converts. **Fixed same day — see the preset section below.**

## Rollback

1. Close OBS.
2. Restore from `H:\System Configuration\backups\2026-09-25\obs-input-overlay-5.0.6\`: copy `input-overlay.dll` and `SDL2.dll` into `C:\Program Files\obs-studio\obs-plugins\64bit\`, delete `C:\Program Files\obs-studio\data\obs-plugins\input-overlay\`, copy the backup's `data\` content back.
3. Start OBS. The 5.0.6 build returns; the spam returns with it.

## Side notes

- The elevated swap run showed an `Error` dialog from the first relaunch (OBS started from the elevated script with `--startvirtualcam`); it produced no log and was dismissed. Later diagnosed: it was a wrong-working-directory launch, not the flag — see the launch procedure section below.

## `~` key preset fix (2026-09-25, before 09:55 relaunch)

The optional follow-up above was done, but by patching the existing preset rather than swapping to the new presets zip (the shipped 5.1.0 presets still use old key codes; the plugin converts them at load, and conversion is what dropped `~`).

- File: `D:\_Archive\01-Backups\OBS Plugins\input-overlay-5.0.6-presets\qwerty_arrow_keys\qwerty_arrow_keys.json` (path kept for history; contents are now 5.1.0-format).
- Original backed up to `H:\System Configuration\backups\2026-09-25\obs-input-overlay-5.0.6\presets\qwerty_arrow_keys.json`.
- All 73 type-1 elements converted from old set-1 scancodes to uiohook `VC_*` codes using `keyCodeMap` from 5.1.0 source (`src/util/overlay.cpp`); `~` (old 0x0029) became `VC_BACK_QUOTE` = 0x00C0. Added `"version": 508` so the plugin's auto-conversion is skipped (re-running conversion on already-converted codes would corrupt them).
- Verified against `include/uiohook.h`: esc=0x001B, q=0x0051, lwin=0xA09D, arrows=0x0025.. all valid `VC_*` values; file is UTF-8 without BOM.
- Result in session log `2026-09-25 09-55-00.txt`: exactly 1 `older version` conversion warning (the DualSense preset, still old-format — gamepad codes, harmless), 0 `Failed to convert` lines, 0 key-layout spam lines.

## How to start and stop OBS on this machine (learned 2026-09-25 — follow this)

The owner controls OBS with the hotkey **Ctrl+Shift+F10** (Windhawk "Keyboard Shortcut Actions") which runs `D:\_Archive\01-Backups\OBS Plugins\Toggle-OBS.vbs`:

- **Running ->** `taskkill /F /T obs64.exe` (hard kill, no dialogs), then clears the `.sentinel` / `safe_mode` markers so the next start skips the Safe Mode prompt.
- **Not running ->** clears those markers, sets `CurrentDirectory` to the obs64 folder, starts `obs64.exe --startreplaybuffer --multi`.
- The Desktop and Start Menu "OBS Studio" shortcuts both point at `obs_start.vbs` (same launcher logic, flags `--startreplaybuffer`).

**Rules for agents (the owner saw "failed to open locale" style errors when these were broken):**

1. Never start `obs64.exe` with a bare `Start-Process`. The working directory must be the folder containing obs64.exe (`C:\Program Files\obs-studio\bin\64bit`) — the launcher scripts set `CurrentDirectory` for exactly this reason ("OBS needs it to find its plugins and data files"). My launches without `-WorkingDirectory` failed twice (08:59 elevated, 09:54 plain); every launcher-script launch succeeded.
2. Never launch OBS elevated/UAC.
3. Only use the flag set the scripts use: `--startreplaybuffer --multi`. Do not add `--startvirtualcam` on the command line; the owner toggles the virtual camera with its own hotkey.
4. To close OBS: use the toggle script (`cscript //nologo "D:\_Archive\01-Backups\OBS Plugins\Toggle-OBS.vbs" /close`) or leave it to the owner's hotkey. It force-kills and cleans the crash markers afterwards. A bare `Stop-Process` skips the marker cleanup.
5. If OBS must be restarted by an agent, prefer `Toggle-OBS.vbs /close` then `/open`.

Incident record: agent restart attempt 2026-09-25 09:54 (force kill + bare `Start-Process` with `--startvirtualcam`) died at startup with no log; the owner re-opened via their hotkey at 09:55:00 (args in log confirm `--startreplaybuffer --multi`) and turned the virtual camera on at 09:59:24. Current state after recovery: OBS running, replay buffer running, virtual camera running, all changes (5.1.0 + tilde fix) active and clean in the log.
