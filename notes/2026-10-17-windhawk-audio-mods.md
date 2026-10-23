# Windhawk audio mods: both load, visualizer settings YAML repaired (2026-10-17)

Owner-approved plan item 3 ("Windhawk 2.0 broken mods"). Item claimed two broken mods,
`taskbar-audio-visualizer` and `better-volume-mixer-plus`. The investigation found they were
not broken in the way the old audit assumed, and the one real defect was narrower than
expected.

## Verdict

Both mods load and inject today. The only defect was that the visualizer's settings YAML
failed to parse, so the Windhawk UI/CLI could not read or edit its settings. That is fixed.

## What was actually wrong

The 2026-10-08 audit recorded "OPEN: these mods still don't load - both want to be hosted in
`windhawk.exe` and 2.0 no longer hosts user mods there." That is no longer true. The rehost to
`windhawk-mod.exe` hosts fixed it:

| Mod | Host pid | Module loaded | Window class present |
| --- | --- | --- | --- |
| `local@taskbar-audio-visualizer` 1.3.2 | 12268 (`windhawk-mod.exe`) | `local@taskbar-audio-visualizer_1.3.2_1.dll` | `DesktopAudioVisOverlay_…`, `DesktopAudioVisMedia_…`, `DesktopAudioVisMessage_…` |
| `local@better-volume-mixer-plus` 1.1.0 | 11832 (`windhawk-mod.exe`) | `local@better-volume-mixer-plus_1.1.0_971983.dll` | `WindhawkBetterTaskbarVolumeMixer` |

Both hosts started 10/17/2026 11:19:57 AM and are still alive. The windows are hidden right now
because a fullscreen game covers the taskbar.

The real defect: `windhawk-cli mod show local@taskbar-audio-visualizer` returned
`Failed to parse settings: mapping values are not allowed in this context at byte 8211 line 213
column 12`. Windhawk 2.0 uses a strict YAML parser; the settings block embeds a YAML document,
and the `followTaskbarAutoHide` setting's `$description` contained an unquoted colon:

```
state: while the taskbar behaves as a permanent bar …
```

In a plain multi-line YAML scalar, `: ` starts a mapping, hence "mapping values are not allowed
in this context." The other mod and the styler have no such colon and parsed fine.

The offending line is file line 272 of `local@taskbar-audio-visualizer.wh.cpp` (the settings
block starts at the `// ==WindhawkModSettings==` marker on line 58); the CLI's reported
"line 213" is relative to the YAML body.

## Fix

One word: `state: while…` → `state. While…`.

- Live source: `C:\ProgramData\Windhawk\ModsSource\local@taskbar-audio-visualizer.wh.cpp`
  (admin-owned; written through `scripts\Invoke-Elevated.ps1` with
  `reports\2026-10-17-audio-mods\fix-modssource-viz-yaml.ps1`).
  SHA256 `0E0EFB21…B0AF` → `7B681475…4DAD`, length 304914, BOM unchanged (none).
- Fork source: `davids-windhawk-mods\mods\local\taskbar-audio-visualizer\taskbar-audio-visualizer.wh.cpp`
  (uncommitted, not published), same SHA256 `7B681475…4DAD`. The two files are now byte-identical.

No recompile was needed. The compiled DLL does not carry the `$description` text at all: in
`local@taskbar-audio-visualizer_1.3.2_1.dll` the strings `behaves`, `while the taskbar` and
`WindhawkModSettings` are absent in UTF-8, UTF-16 and raw ASCII, and `followTaskbarAutoHide`
appears once (UTF-16) as a settings key, not a description. The settings schema the CLI and UI
read comes from the source file, so a source edit alone clears the error. `mod compile` remains
available if a future change needs the DLL rebuilt.

## Verification (measured)

- `windhawk-cli mod show local@taskbar-audio-visualizer` → exit 0, full metadata + README, no parse error.
- `windhawk-cli mod settings get local@taskbar-audio-visualizer` → exit 0, real runtime values
  (`appearance.barCount=32`, `appearance.color=#FFCBA6F7`, `audio.captureMode=all`, …).
- `windhawk-cli mod settings get local@better-volume-mixer-plus` → exit 0.
- `windhawk-cli mod settings defaults local@taskbar-audio-visualizer` → exit 0 (declared-defaults path validates the whole schema).
- `windhawk-cli mod list` → exit 0, 127 lines; both mods listed `enabled`.
- Validator `check-mod-settings-yaml.py`: live ModsSource OK, fork copy OK, bvm ModsSource OK,
  and the pre-fix backup FAILs at file line 272. That is a clean before/after on one word.
- Window-class scan (`reports\2026-10-17-audio-mods\list-mod-windows.py`) found the four classes
  above, owned by the two hosts.

## Limits

- Live rendering of the strip and the mixer tray was **not** observed: a fullscreen game
  (`2560x1440` at 0,0) covers the top taskbar, and the visualizer hides during fullscreen by
  design. A taskbar screenshot comes back black. So "the mods inject and hold their windows" is
  measured; "the bars draw correctly on screen" is not.
- The change is a description string only, so the running mods need no reload and their behaviour
  is unchanged.

## Notes and known oddities

- Windhawk is 2.0.0-alpha.7. The CURRENT-STATUS entry for 2026-10-08 claimed the source had
  already been patched then, but the live ModsSource copy carried the broken text today. The
  likely cause is a core update (alpha.6 → alpha.7) or a mod reinstall re-writing ModsSource
  from the original source. This is inferred, not measured. The fix is re-applied and verified.
- The registry stores `Version=1.3.1` for the visualizer while the source `@version` and the DLL
  name are 1.3.2. Cosmetic; left alone.
- The registry `Include` for both mods is still `windhawk.exe`, yet the mods run under the
  `windhawk-mod.exe` hosts. That mapping is handled by the engine; left alone.

## Backups and rollback

- `backups\2026-10-17\audio-mods\` holds `ModsSource-taskbar-audio-visualizer.wh.cpp.bak`
  (byte-identical to the live file before the edit, SHA256 `0E0EFB21…B0AF`) plus the bvm source
  backups and `reg-viz.reg` / `reg-bvm.reg` registry exports.
- To roll back the ModsSource edit, copy that `.bak` back over
  `C:\ProgramData\Windhawk\ModsSource\local@taskbar-audio-visualizer.wh.cpp` (elevated). That
  restores the parse error as well, so roll back only if something else breaks.
