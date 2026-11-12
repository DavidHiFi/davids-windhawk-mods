# Seamless Crash Watch (2026-11-11 to 2026-11-12)

A port of Omarchy's crash notice to a Windhawk tool mod: "Process crashed: <name>" and
"Click to diagnose with AI" at the top right. Clicking opens Windows Terminal with Claude Code
(default; Codex, OpenCode, Gemini or a custom command) and a crash report. Catppuccin Mocha,
grey edge at rest, blue to mauve gradient border and glow on hover, frosted glass.

- Mod: `local@seamless-crash-watch` 1.1.2, enabled, runs in its own `windhawk-mod.exe`.
- Sources: `work\2026-11-11-crash-toast\` (`src\core.cpp`, `gen.py` makes the settings window
  from the Launchpad one, `assemble.py` writes `build\seamless-crash-watch.wh.cpp`).
- Public: DavidHiFi/davids-windhawk-mods 3badc23 (source, preview, manifest).

## Findings

- Windows Error Reporting is off on this PC (HKLM ...\Windows Error Reporting Disabled = 1,
  WerSvc disabled), so no Application Error 1000 events are written. Left unchanged.
- The tool mod host runs as the user, not elevated, so WMI process-stop events are denied
  (0x80041003). Crashes are caught from exit codes instead: a watcher holds a handle to each
  program (Toolhelp snapshot every 500 ms) and reads the exit code when it ends. Programs it
  cannot open (88 of about 440, mostly system ones) and programs that live under half a second
  can slip past. Event-log crashes still count when WER is on; duplicates are merged.
- Trace log: `%LOCALAPPDATA%\SeamlessCrashWatch\watch.log` (rotates at 64 KB). Each caught exit
  and the reason a notice was or was not shown.
- First click per PC: Claude Code asks once whether to trust the reports folder
  (`%LOCALAPPDATA%\SeamlessCrashWatch\reports`). Its default is "No, exit"; pick "Yes" once.
- Installing a tool mod stops its process; restart with `scripts\2026-11-10-tool-mod-restart.ps1`.

## 1.1.1 (2026-11-12): settings glass standard

Old: accent `{4, 0, 0xD82E1E1E, 0}`, tint 0.42 fading from clear at the top.
New: accent `{4, 2, 0x012E1E1E, 0}` (the launcher grid's), flat 0.55 tint, no title band.
`settings-material.py check` now says ok. `gen.py` writes the new values too.
Backup: `C:\ProgramData\Windhawk\ModsSource\local@seamless-crash-watch.wh.cpp.bak-20261112-0114`.

## 1.1.2 (2026-11-12): border corners cut off

Owner's report: "the borders cut off". Zoomed, the four straight edges were whole (2 px) but
the corner curves were missing for about 11 px from each corner.
Cause: the `custom-corner-radius` mod (in dwm.exe) sets every window's corner radius to 16
here, so Windows clipped the notice at 16 px while the border was drawn at 8 px; the curve
fell outside the window.
Old: border radius fixed at 8 (round) or 4 (small).
New: `RefreshSystemRadius()` reads `HKLM\SOFTWARE\Windhawk\Engine\Mods\custom-corner-radius`
(skipped when Disabled = 1) `Settings\radius` and `smallRadius`; -1 or missing keeps 8 / 4.
Read on every new notice and on settings change. Per-corner radius and its excluded-programs
list are not followed.
Proof: `live\cut\corners-before-after.png` (owner's corners, then rest and hover at 8x),
`media\crash-watch-corners.mp4/.gif`.
Rollback: the installer's backup in `backups\settings-material\` or `ModsSource\...bak-*`.

## Proof

`work\2026-11-11-crash-toast\media\`: live crash (real crash-test.exe, WER off), hover, click
(the agent terminal opens), settings glass. Test copy: `harness\harness.cpp` shows one notice
and drives hover and click on a timer, so the cursor is never moved.

## Rollback

- 1.1.1 only: install the `.bak-20261112-0114` copy with `windhawk-cli mod install --file`.
- The whole mod: `scripts\2026-11-11-seamless-crash-watch.ps1 -Rollback` (elevated) disables
  and removes it. Nothing else on the system was changed.
