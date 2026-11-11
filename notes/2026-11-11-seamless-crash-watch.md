# Seamless Crash Watch (2026-11-11 to 2026-11-12)

A port of Omarchy's crash notice to a Windhawk tool mod: "Process crashed: <name>" and
"Click to diagnose with AI" at the top right. Clicking opens Windows Terminal with Claude Code
(default; Codex, OpenCode, Gemini or a custom command) and a crash report. Catppuccin Mocha,
grey edge at rest, blue to mauve gradient border and glow on hover, frosted glass.

- Mod: `local@seamless-crash-watch` 1.1.1, enabled, runs in its own `windhawk-mod.exe`.
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

## Proof

`work\2026-11-11-crash-toast\media\`: live crash (real crash-test.exe, WER off), hover, click
(the agent terminal opens), settings glass. Test copy: `harness\harness.cpp` shows one notice
and drives hover and click on a timer, so the cursor is never moved.

## Rollback

- 1.1.1 only: install the `.bak-20261112-0114` copy with `windhawk-cli mod install --file`.
- The whole mod: `scripts\2026-11-11-seamless-crash-watch.ps1 -Rollback` (elevated) disables
  and removes it. Nothing else on the system was changed.
